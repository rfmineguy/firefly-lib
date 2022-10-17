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

typedef struct _FF_AudioSystem {
  ALCdevice *pDevice;
  ALCcontext *pContext;
  FF_SoundSource sources[MAX_SOUND_SOURCES];
  int sourcesCount;
} FF_AudioSystem;

bool ReadWAV(FF_Sound *pSound, const char* path, int16_t *fmt_out, int32_t *data_size_out, int32_t *sample_rate_out) {
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

FF_AudioSystem* FF_CreateAudioSystem() {
  FF_AudioSystem* pAudioSystem = malloc(sizeof(FF_AudioSystem));

  // Device creation
  pAudioSystem->pDevice = alcOpenDevice(NULL);
  pAudioSystem->pContext = NULL;
  if (!pAudioSystem->pDevice) {
    LOG_CRITICAL("[AudioSystem] Failed to open OpenAL device, %p");
    alcCloseDevice(pAudioSystem->pDevice);
    free(pAudioSystem);
    pAudioSystem = NULL;
    return NULL;
  }
  
  // Context creation
  pAudioSystem->pContext = alcCreateContext(pAudioSystem->pDevice, NULL);
  if (!pAudioSystem->pContext || alcMakeContextCurrent(pAudioSystem->pContext) == AL_FALSE) {
    LOG_CRITICAL("[AudioSystem] Failed to set OpenAL context");
    if (pAudioSystem->pContext != NULL) {
      alcDestroyContext(pAudioSystem->pContext);
    }
    alcCloseDevice(pAudioSystem->pDevice);
    free(pAudioSystem);
    pAudioSystem = NULL;
    return NULL;
  }
  
  FF_SetAudioListener(pAudioSystem, (vec3){0, 0, 0},  (vec3){0, 0, 0});
  LOG_INFO("[AudioSystem] Created successfully.");
  return pAudioSystem;
}

void FF_DestroyAudioSystem(FF_AudioSystem* pAudioSystem) {
  for (int i = 0; i < pAudioSystem->sourcesCount; i++) {
    FF_SoundSourceStop(pAudioSystem->sources[i]);
    alDeleteSources(1, &pAudioSystem->sources[i].id);
  }
  
  alcMakeContextCurrent(pAudioSystem->pContext);
  alcDestroyContext(pAudioSystem->pContext);
  pAudioSystem->pContext = NULL;
  alcCloseDevice(pAudioSystem->pDevice);
  pAudioSystem->pDevice = NULL;
  
  free(pAudioSystem);
  pAudioSystem = NULL;
  LOG_INFO("[AudioSystem] Destroyed successfully.");
}

void FF_SetAudioListener(FF_AudioSystem* pAudioSystem, vec3 pos, vec3 vel) {
  alListener3f(AL_POSITION, pos[0], pos[1], pos[2]);
  alListener3f(AL_VELOCITY, vel[0], vel[1], vel[2]);
}

FF_Sound FF_LoadSound(const char* filepath) {
  FF_Sound sound;
  int16_t format;
  int32_t sampleRate, dataSize;
  ReadWAV(&sound, filepath, &format, &dataSize, &sampleRate);
  alGenBuffers(1, &sound.buffer);
  alBufferData(sound.buffer, format + AL_FORMAT_MONO8, sound.data, dataSize, sampleRate);
  free(sound.data);
  sound.data = NULL;
  return sound;
}

void FF_FreeSound(FF_Sound sound) {
  alDeleteBuffers(1, &sound.buffer);
  free(sound.data);
  sound.data = NULL;
}

FF_SoundSource FF_CreateSoundSource(FF_AudioSystem* pAudioSystem) {
  return FF_CreateSoundSourceEx(pAudioSystem, 1.0f, 1.0f, (vec3){0}, false);
}

FF_SoundSource FF_CreateSoundSourceEx(FF_AudioSystem* pAudioSystem, float pitch, float gain, vec3 pos, bool looping) {
  FF_SoundSource source;
  alGenSources(1, &source.id);
  FF_SoundSourceSetGain(&source, gain);
  FF_SoundSourceSetPitch(&source, pitch);
  FF_SoundSourceSetPos(&source, pos);
  FF_SoundSourceSetLooping(&source, looping);
  source.gain = gain;
  pAudioSystem->sources[pAudioSystem->sourcesCount++] = source;
  LOG_DEBUG("SoundSource : Created");
  return source;
}

void FF_SoundSourceSetGain(FF_SoundSource* pSource, float gain) {
  if (gain > 1) {
    gain = 1;
  }
  pSource->gain = gain;
  alSourcef(pSource->id, AL_GAIN, gain);
}

void FF_SoundSourceSetPitch(FF_SoundSource* pSource, float pitch) {
  pSource->pitch = pitch;
  alSourcef(pSource->id, AL_PITCH, pitch);
}

void FF_SoundSourceSetPos(FF_SoundSource* pSource, vec3 pos) {
  glm_vec3_copy(pSource->position, pos);
  alSource3f(pSource->id, AL_POSITION, pos[0], pos[1], pos[2]);
}

void FF_SoundSourceSetLooping(FF_SoundSource* pSource, bool looping) {
  pSource->looping = looping;
  alSourcei(pSource->id, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
}

void FF_SoundSourcePlay(FF_SoundSource source, FF_Sound sound) {
  FF_SoundSourceStop(source);
  alSourcei(source.id, AL_BUFFER, sound.buffer);
  alSourcePlay(source.id);
  source.playing_buffer_id = sound.buffer;
}

void FF_SoundSourcePause(FF_SoundSource source) {
  alSourcePause(source.id);
}

void FF_SoundSourceUnpause(FF_SoundSource source) {
  alSourcei(source.id, AL_BUFFER, source.playing_buffer_id);
  alSourcePlay(source.id);
}

void FF_SoundSourceStop(FF_SoundSource source) {
  alSourceStop(source.id);
}

bool FF_SoundSourcePlaying(FF_SoundSource source) {
  ALint state;
  alGetSourcei(source.id, AL_SOURCE_STATE, &state);
  return state == AL_PLAYING;
}