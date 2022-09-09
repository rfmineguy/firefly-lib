#ifndef FL_RES_SOUND_H
#define FL_RES_SOUND_H
#include <cglm/cglm.h>
#include <stdbool.h>

typedef struct _Sound Sound;
typedef struct _SoundSource SoundSource;

//typedef struct {
//    char name[50];
//    uint16_t *data;
//    uint32_t samples;
//    struct Sound* next;
//} Sound;

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources

void InitSoundMaster();
void SoundMasterSetListener(vec3, vec3);
void DeinitSoundMaster();

Sound* LoadSound(const char*); //setup sound with default settings
void FreeSound(Sound*);

SoundSource* SoundSourceCreate();
void SoundSourceDestroy(SoundSource*);

void SoundSourceFull(SoundSource*, float, float, vec3);
void SoundSourceSetGain(SoundSource*, float);
void SoundSourceSetPitch(SoundSource*, float);
void SoundSourceSetPos(SoundSource*, vec3);
void SoundSourcePlay(SoundSource*, Sound*);
void SoundSourceStop(SoundSource*);
bool SoundSourcePlaying(SoundSource*);

#endif
