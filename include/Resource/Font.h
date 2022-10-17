#ifndef FF_RESOURCE_FONT_H
#define FF_RESOURCE_FONT_H

typedef struct _FF_Font FF_Font;
typedef struct _FF_Char FF_Char;

void FF_InitFontSystem();
void FF_DeinitFontSystem();

FF_Font FF_LoadFont(const char*);

#endif