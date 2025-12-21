#ifndef GLOB_H
#define GLOB_H

#include <windows.h>
#include <stdbool.h>
#include "../types.h"

/* ========= render-context ========= */
void SetRenderHDC(HDC hdc);

/* ========= font stuff ========= */
void SetFontSize(unsigned char size);
void SetFontFace(char* face);
void SetFontBold(bool val);
void SetFontItalic(bool val);
void SetFontColor(rgb888 color);

/* ========= text ========= */
void RePositionText(unsigned int x, unsigned int y);
void PrintText(char *text);

/* ========= backbuffer ========= */
typedef struct {
    int width;
    int height;
    HBITMAP bitmap;
    void* pixels;
} SoftwareBitmap;

extern SoftwareBitmap g_backbuffer;

// global draw color (bgrx)
extern unsigned int g_draw_color;

void CreateBackbuffer(HDC hdc, int width, int height);
void ClearBackbuffer(unsigned int color);
void PresentBackbuffer(HDC hdc);

/* ========= bitmap ========= */
// 1d byte mask → 2d pixels
void RenderByteBitmap(
    unsigned int x,
    unsigned int y,
    unsigned int width,
    unsigned int height,
    unsigned char* bytes
);

#endif
