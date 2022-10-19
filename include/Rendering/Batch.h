#ifndef FL_REND_BATCH_H
#define FL_REND_BATCH_H
#include "../Resource/Shader.h"

// Allows for c++ to link lib
#ifdef __cplusplus
extern "C" {
#endif

void BeginBatch();
void BeginBatchEx(Shader*);
void EndBatch();
void RenderBatch();

#ifdef __cplusplus
}
#endif

#endif
