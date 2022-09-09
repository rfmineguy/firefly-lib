#include "../include/Resource/Sound.h"
#include "../include/IO/Log.h"
#include "../libs/openal/include/AL/al.h"
#include "../libs/openal/include/AL/alc.h"
#include <stdio.h>
#include <stdlib.h>

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources

typedef struct _Sound {
  uint32_t samples;
  int16_t *data;
  ALuint buffer;
} Sound;

typedef struct _SoundSource {
  vec3 position;
  float gain, pitch;
  ALuint id;
} SoundSource;

typedef struct _SoundMaster {
  ALCdevice* pDevice;
  ALCcontext* pContext;
} SoundMaster;

SoundMaster gSoundMaster;

void InitSoundMaster() {
  gSoundMaster.pDevice = alcOpenDevice(NULL);
  gSoundMaster.pContext = NULL;
  if (!gSoundMaster.pDevice) {
    LOG_CRITICAL("Failed to OpenAL device");
    return;
  }
  gSoundMaster.pContext = alcCreateContext(gSoundMaster.pDevice, NULL);
  if (!gSoundMaster.pContext || alcMakeContextCurrent(gSoundMaster.pContext) == AL_FALSE) {
    if (gSoundMaster.pContext != NULL) {
      alcDestroyContext(gSoundMaster.pContext);
    }
    alcCloseDevice(gSoundMaster.pDevice);
    LOG_CRITICAL("Failed to set an OpenAL context {pContext=%p, pDevice=%p}", gSoundMaster.pContext, gSoundMaster.pDevice);
    return;
  }
  LOG_INFO("Initialized OpenAL");
}
void DeinitSoundMaster() {
  ALCdevice *device;
  ALCcontext *context;
  
  context = alcGetCurrentContext();
  if (context == NULL)
    return;
  device = alcGetContextsDevice(context);
  
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device); 
}

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
    LOG_CRITICAL("Failed to open wav file {%s}", path);
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

  LOG_INFO("riff =[%c%c%c%c]", riff[0], riff[1], riff[2], riff[3]);
  LOG_INFO("wave =[%c%c%c%c]", wave[0], wave[1], wave[2], wave[3]);
  LOG_INFO("fmt =[%c%c%c%c]", fmt[0], fmt[1], fmt[2], fmt[3]);
  LOG_INFO("file_size = [%d]", file_size);
  LOG_INFO("format_len = [%d]", format_length);
  LOG_INFO("format_type = [%d]", format_type);
  LOG_INFO("num_channels = [%d]", num_channels);
  LOG_INFO("sample_rate = [%d]", sample_rate);
  LOG_INFO("bytes_per_second = [%d]", bytes_per_second);
  LOG_INFO("block_align = [%d]", block_align);
  LOG_INFO("bits_per_sample = [%d]", bits_per_sample);
  LOG_INFO("data = [%c%c%c%c]", data[0], data[1], data[2], data[3]);
  LOG_INFO("data_size = [%d]", data_size);
  pSound->data = malloc(data_size);
  if (pSound->data == NULL) {
    LOG_CRITICAL("Failed to allocate memory for sound data");
    free(pSound->data);
    pSound->data = NULL;
    free(pSound);
    pSound = NULL;
    return false;
  }
  
  if (fread(pSound->data, 1, data_size, f) != data_size) {
    LOG_CRITICAL("Failed to read data bytes from [%s]", path);
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

Sound* LoadSound(const char* path) {
  Sound* pSound = malloc(sizeof(Sound));

  int16_t format;
  int32_t sample_rate, data_size;

  ReadWAV(pSound, path, &format, &data_size, &sample_rate);
  LOG_INFO("actual = %d, actual + MONO8 = %d", format, format + AL_FORMAT_MONO8);
  alGenBuffers(1, &pSound->buffer);
  alBufferData(pSound->buffer, format + AL_FORMAT_MONO8, pSound->data, data_size, sample_rate);
  
  ALenum err = alGetError();
  LOG_ERROR("Errror :%s", alGetString(err));

  free(pSound->data);
  pSound->data = NULL;
  return pSound;
} //setup sound with default settings

void FreeSound(Sound *pSound) {
  alDeleteBuffers(1, &pSound->buffer);
  free(pSound->data);
  pSound->data = NULL;
  free(pSound);
  pSound = NULL;
}

void SoundMasterSetListener(vec3 position, vec3 velocity) {
  alListener3f(AL_POSITION, position[0], position[1], position[2]);
  alListener3f(AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
}

SoundSource* SoundSourceCreate() {
  SoundSource* s = malloc(sizeof(SoundSource));
  alGenSources(1, &s->id);
  SoundSourceFull(s, 1, 1, (vec3){0, 0, 0}, false);
  return s;
}

void SoundSourceDestroy(SoundSource *pSource) {
  SoundSourceStop(pSource);
  alDeleteSources(1, &pSource->id);
  free(pSource);
  pSource = NULL;
}

void SoundSourceFull(SoundSource *pSource, float gain, float pitch, vec3 pos, bool looping) {
  SoundSourceSetGain(pSource, gain);
  SoundSourceSetPitch(pSource, pitch);
  SoundSourceSetPos(pSource, pos);
  SoundSourceSetLooping(pSource, looping);
}

void SoundSourceSetGain(SoundSource *pSource, float gain) {
  if (gain > 1) {
    float chosen = gain;
    gain = 1;
    LOG_WARN("Audio gain level [%0.4f] chosen. This is a dangerous volume, so its been lowered to %0.4f.", chosen, gain);    
  }
  alSourcef(pSource->id, AL_GAIN, gain);
}

void SoundSourceSetPitch(SoundSource *pSource, float pitch) {
  alSourcef(pSource->id, AL_PITCH, pitch);
}

void SoundSourceSetPos(SoundSource *pSource, vec3 pos) {
  alSource3f(pSource->id, AL_POSITION, pos[0], pos[1], pos[2]);  
}

void SoundSourceSetLooping(SoundSource *pSource, bool looping) {
  alSourcei(pSource->id, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
}

void SoundSourcePlay(SoundSource *pSource, Sound* pSound) {
  SoundSourceStop(pSource);
  alSourcei(pSource->id, AL_BUFFER, pSound->buffer);
  alSourcePlay(pSource->id);
}

void SoundSourcePause(SoundSource *pSource) {
  alSourcePause(pSource->id);
}

void SoundSourceUnpause(SoundSource *pSource) {
  alSourcePlay(pSource->id);  
}

void SoundSourceStop(SoundSource *pSource) {
  alSourceStop(pSource->id);
}

bool SoundSourcePlaying(SoundSource *pSource) {
  ALint state;
  alGetSourcei(pSource->id, AL_SOURCE_STATE, &state);
  return state == AL_PLAYING;
}
