#ifndef FL_RES_SOUND_H
#define FL_RES_SOUND_H
#include "../Core/Vec.h"

typedef struct {
	float pitch;
	float gain;
	Vec2f position;
	Vec2f velocity;
	bool looping;
} Sound;

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources

Sound* LoadSound(const char*); //setup sound with default settings
void FreeSound(Sound*);

void SoundSettingsDefault(Sound*);
void SoundSettings(Sound*, float, float, Vec2f, Vec2f, bool);

void PlaySound(Sound*);
void StopSound(Sound*);

#endif
