#include "../include/Resource/Sound.h"
#include "../include/IO/Log.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_SOUND_SOURCES 100

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources

typedef struct _SoundMaster {
  ALCdevice* pDevice;
  ALCcontext* pContext;
  ALuint sourceIds[MAX_SOUND_SOURCES];
  int idCount;
} SoundMaster;

SoundMaster gSoundMaster = (SoundMaster){0};

bool ReadWAV(Sound *pSound, const char* path, int16_t *fmt_out, int32_t *data_size_out, int32_t *sample_rate_out) {
  FILE *f;
  char riff[4], wave[4], fmt[4], data[4];
  int32_t file_size;
  int32_t format_length;
  int16_t format_type;
  int16_t num_channels;
  int32_t sample_rate;
  int32_t bytes_per_second;
  int16_t block_align;
  int16_t bits_per_sample;
  int32_t data_size;
  
  f = fopen(path, "rb");
  if (f == NULL) {
    LOG_CRITICAL("[Sound] => Failed to open wav file {%s}", path);
    return false;
  }
  
  fread(riff, 1, 4, f);          //read the magic header (if this isn't "RIFF" then the file isn't a wav)
  fread(&file_size, 4, 1, f);
  fread(wave, 1, 4, f);        //read magic header (if this isn't "WAVE" then the file isn't a wav)
  fread(fmt, 1, 4, f);
  fread(&format_length, 4, 1, f);
  fread(&format_type, 2, 1, f);
  fread(&num_channels, 2, 1, f);  
  fread(&sample_rate, 4, 1, f);  
  fread(&bytes_per_second, 4, 1, f);
  fread(&block_align, 2, 1, f);
  fread(&bits_per_sample, 2, 1, f);
  fread(data, 1, 4, f);
  fread(&data_size, 4, 1, f);
  
  // check RIFF
  if (riff[0] != 'R' || riff[1] != 'I' || riff[2] != 'F' || riff[3] != 'F') {
    LOG_CRITICAL("[Sound] => \"RIFF\" portion of wav file incorrect. It is [%c%c%c%c]", riff[0], riff[1], riff[2], riff[3]);
    return false;
  }
  
  //check WAVE
  if (wave[0] != 'W' || wave[1] != 'A' || wave[2] != 'V' || wave[3] != 'E') {
    LOG_CRITICAL("[Sound] => \"WAVE\" portion of wav file incorrect. It is [%c%c%c%c]", wave[0], wave[1], wave[2], wave[3]);
    return false;
  }
  
  //check FMT
  if (fmt[0] != 'f' || fmt[1] != 'm' || fmt[2] != 't' || fmt[3] != ' ') {
    LOG_CRITICAL("[Sound] => \"fmt \" portion of wav file incorrect. It is [%c%c%c%c]", fmt[0], fmt[1], fmt[2], fmt[3]);
    return false;
  }

  pSound->data = malloc(data_size);
  if (pSound->data == NULL) {
    LOG_CRITICAL("[Sound] => Failed to allocate memory for sound data");
    free(pSound->data);
    pSound->data = NULL;
    free(pSound);
    pSound = NULL;
    return false;
  }
  
  if (fread(pSound->data, 1, data_size, f) != data_size) {
    LOG_CRITICAL("[Sound] => Failed to read data bytes from [%s]", path);
    free(pSound->data);
    pSound->data = NULL;
    free(pSound);
    pSound = NULL;
    return NULL;
  }

  pSound->samples = data_size / 2;
  *sample_rate_out = sample_rate;
  *fmt_out = format_type;
  *data_size_out = data_size;
  fclose(f);
  return true;
}

SoundMaster* FF_int_GetSoundMaster() {
  return &gSoundMaster;
}

void FF_InitAudioSystem() {
  gSoundMaster.pDevice = alcOpenDevice(NULL);
  gSoundMaster.pContext = NULL;
  if (!gSoundMaster.pDevice) {
    LOG_CRITICAL("[Sound] => Failed to open OpenAL device");
    return;
  }
  gSoundMaster.pContext = alcCreateContext(gSoundMaster.pDevice, NULL);
  if (!gSoundMaster.pContext || alcMakeContextCurrent(gSoundMaster.pContext) == AL_FALSE) {
    if (gSoundMaster.pContext != NULL) {
      alcDestroyContext(gSoundMaster.pContext);
    }
    alcCloseDevice(gSoundMaster.pDevice);
    LOG_CRITICAL("[Sound] => Failed to set OpenAL context");
    return;
  }
  LOG_INFO("[Sound] => Initialized OpenAL");
}

void FF_DeinitAudioSystem() {
  for (int i = 0; i < FF_int_GetSoundMaster()->idCount; i++) {
    ALuint id = FF_int_GetSoundMaster()->sourceIds[i];
    alDeleteSources(1, &id);
    LOG_DEBUG("[Sound] => Deleted sound source id [%d]", id);
  }
  
  ALCdevice *device;
  ALCcontext *ctx;
  ctx = alcGetCurrentContext();
  if (ctx == NULL)
    return;
  
  device = alcGetContextsDevice(ctx);
  if (device == NULL)
    return;
  
  alcMakeContextCurrent(NULL);
  alcDestroyContext(ctx);
  alcCloseDevice(device);
}

Sound FF_LoadSound(const char* path) {
  Sound s;
  int16_t format;
  int32_t sample_rate, data_size;
  ReadWAV(&s, path, &format, &data_size, &sample_rate);
  alGenBuffers(1, &s.buffer);
  alBufferData(s.buffer, format + AL_FORMAT_MONO8, s.data, data_size, sample_rate);
  
  LOG_INFO("[Sound] => Loaded Sound from \"%s\"", path);
  free(s.data);
  s.data = NULL;
  return s;
}

void FF_FreeSound(Sound s) {
  alDeleteBuffers(1, &s.buffer);
  free(s.data);
  s.data = NULL;
}

void FF_SoundListener(vec3 pos, vec3 vel) {
  alListener3f(AL_POSITION, pos[0], pos[1], pos[2]);
  alListener3f(AL_VELOCITY, vel[0], vel[1], vel[2]);
}

SoundSource FF_SoundSource() {
  return FF_SoundSourceEx(1.0f, 1.0f, (vec3){0, 0, 0}, false);
}

SoundSource FF_SoundSourceEx(float pitch, float gain, vec3 pos, bool looping) {
  SoundSource source = (SoundSource){.pitch=pitch, .gain=gain, .position[0] = pos[0], .position[1] = pos[1], .position[2] = pos[2], .looping=looping};
  alGenSources(1, &source.id);
  FF_int_GetSoundMaster()->sourceIds[FF_int_GetSoundMaster()->idCount++] = source.id;
  LOG_INFO("[Sound] => Creating sound Source with id %d", source.id);
  return source;
}

void FF_SoundSourceSetGain(SoundSource *src, float gain) {
  src->gain = gain;
  alSourcef(src->id, AL_GAIN, gain);
}

void FF_SoundSourceSetPitch(SoundSource *src, float pitch) {
  src->pitch = pitch;
  alSourcef(src->id, AL_PITCH, pitch);
}

void FF_SoundSourceSetPos(SoundSource *src, vec3 pos) {
  glm_vec3_copy(pos, src->position);
  alSource3f(src->id, AL_POSITION, pos[0], pos[1], pos[2]);
}

void FF_SoundSourceSetLooping(SoundSource *src, bool looping) {
  src->looping = looping;
  alSourcei(src->id, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
}

void FF_SoundSourcePlay(SoundSource src, Sound sound) {
  FF_SoundSourceStop(src);
  alSourcei(src.id, AL_BUFFER, sound.buffer);
  alSourcePlay(src.id);
  src.curr_sound = sound;
}

void FF_SoundSourcePause(SoundSource src) {
  alSourcePause(src.id);
}

void FF_SoundSourceUnpause(SoundSource src) {
  alSourcei(src.id, AL_BUFFER, src.curr_sound.buffer);
  alSourcePlay(src.id);
}

void FF_SoundSourceStop(SoundSource src) {
  alSourceStop(src.id);
}

bool FF_SoundSourcePlaying(SoundSource src) {
  ALint state;
  alGetSourcei(src.id, AL_SOURCE_STATE, &state);
  return state == AL_PLAYING;
}
