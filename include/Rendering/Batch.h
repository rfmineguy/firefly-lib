#ifndef FL_REND_BATCH_H
#define FL_REND_BATCH_H
#include "../Resource/Shader.h"

void BeginBatch();
void BeginBatchEx(Shader*);
void EndBatch();
void RenderBatch();

#endif
