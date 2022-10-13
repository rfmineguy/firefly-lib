#ifndef FL_RES_SOUND_H
#define FL_RES_SOUND_H
#include <cglm/cglm.h>
#include <AL/alc.h>
#include <AL/al.h>
#include <stdbool.h>

typedef struct _Sound {
  uint32_t samples;
  int16_t *data;
  ALuint buffer;
} Sound;

typedef struct _SoundSource {
  vec3 position;
  float gain, pitch;
  ALuint id;
  bool looping;
  ALuint playing_buffer_id;
} SoundSource;

typedef struct _SoundMaster SoundMaster;

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources

void FF_InitAudioSystem();
void FF_DeinitAudioSystem();
SoundMaster* FF_int_GetSoundMaster();

Sound FF_LoadSound(const char*);
void FF_FreeSound(Sound);

void FF_SoundListener(vec3, vec3);
SoundSource FF_SoundSource();        //store sound source ids in the SoundMaster
SoundSource FF_SoundSourceEx(float, float, vec3, bool);
void FF_SoundSourceSetGain(SoundSource*, float);
void FF_SoundSourceSetPitch(SoundSource*, float);
void FF_SoundSourceSetPos(SoundSource*, vec3);
void FF_SoundSourceSetLooping(SoundSource*, bool);

void FF_SoundSourcePlay(SoundSource, Sound);
void FF_SoundSourcePause(SoundSource);
void FF_SoundSourceUnpause(SoundSource);
void FF_SoundSourceStop(SoundSource);
bool FF_SoundSourcePlaying(SoundSource);

#endif
