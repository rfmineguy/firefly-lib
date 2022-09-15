#ifndef CORE_INIT_H
#define CORE_INIT_H

typedef enum {
  AUDIO=0x1, INPUT=0x2, RENDERING=0x4, RESOURCE=0x8, ALL=0xF
} Feature;

void InitializeFeatures(Feature);
void DeInitializeFeatures();

#endif