#include "../include/Core/Init.h"
#include "../include/IO/IO.h"
#include "../include/Resource/Resource.h"
#include "../include/Core/Core.h"
#include "../include/Rendering/Rendering.h"

Feature initialized_feaures;
void InitializeFeatures(Feature flags) {
  static int initialized = 0;
  if (initialized == 1)
    return;

  SetLogStream(stdout);
  LOG_DEBUG("Initializing features %d", flags);
  if (flags & AUDIO) {
    InitSoundMaster();
    LOG_INFO("Initialized SoundMaster");
  }
  if (flags & INPUT) {
    InitKeybindHT();
    LOG_INFO("Initialized Input");
  }
  if (flags & RENDERING) {
    InitWindowGL();
    InitRendering();
    LOG_INFO("Initialized Rendering");
  }
  if (flags & RESOURCE) {
    InitResourcePool();
    LOG_INFO("Initialized Resource");
  }
  initialized = 1;
  initialized_feaures = flags;
}

void DeInitializeFeatures() {
  if (initialized_feaures & AUDIO) {
    DeinitSoundMaster();
    initialized_feaures &= ~AUDIO;
  }
  if (initialized_feaures & INPUT) {
    DeinitKeybindHT();
    initialized_feaures &= ~INPUT;
  }
  if (initialized_feaures & RENDERING) {
    DestroyWindowGL();
    FreeRendering();
    initialized_feaures &= ~RENDERING;
  }
  if (initialized_feaures & RESOURCE) {
    DestroyResourcePool();
    initialized_feaures &= ~RESOURCE;
  }
}