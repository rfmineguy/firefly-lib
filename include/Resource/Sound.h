#ifndef FL_RES_SOUND_H
#define FL_RES_SOUND_H
#include <cglm/cglm.h>
#include <AL/alc.h>
#include <AL/al.h>
#include <stdbool.h>

typedef struct _FF_Sound {
  uint32_t samples;
  int16_t *data;
  ALuint buffer;
} FF_Sound;

typedef struct _FF_SoundSource {
  vec3 position;
  float gain, pitch;
  ALuint id;
  bool looping;
  ALuint playing_buffer_id;
} FF_SoundSource;

// Opaque type
typedef struct _FF_AudioSystem FF_AudioSystem;
typedef struct _SoundMaster SoundMaster;

FF_AudioSystem* FF_CreateAudioSystem();
void FF_DestroyAudioSystem(FF_AudioSystem*);
void FF_SetAudioListener(FF_AudioSystem*, vec3, vec3);

FF_Sound FF_LoadSound(const char*);
void FF_FreeSound(FF_Sound);

FF_SoundSource FF_CreateSoundSource(FF_AudioSystem*);
FF_SoundSource FF_CreateSoundSourceEx(FF_AudioSystem*, float, float, vec3, bool);
void FF_SoundSourceSetGain(FF_SoundSource*, float);
void FF_SoundSourceSetPitch(FF_SoundSource*, float);
void FF_SoundSourceSetPos(FF_SoundSource*, vec3);
void FF_SoundSourceSetLooping(FF_SoundSource*, bool);

void FF_SoundSourcePlay(FF_SoundSource, FF_Sound);
void FF_SoundSourcePause(FF_SoundSource);
void FF_SoundSourceUnpause(FF_SoundSource);
void FF_SoundSourceStop(FF_SoundSource);

bool FF_SoundSourcePlaying(FF_SoundSource);

#endif
