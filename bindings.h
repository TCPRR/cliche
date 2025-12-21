#include "types.h"
extern void SetFontSize(unsigned char size);
extern void SetFontFace(char* face);
extern void SetFontBold(bool val);
extern void SetFontItalic(bool val);
extern void SetFontColor(rgb888 color);
extern void PrintText(char *text);
extern void RePositionText(unsigned int x, unsigned int y);
extern void RenderByteBitmap(unsigned int x, unsigned int y, unsigned char* bytes, unsigned long size);
extern unsigned int GetTextWidth(char* text);
extern unsigned int GetTextHeight(char *text);
unsigned int CurrentX;
unsigned int CurrentY;