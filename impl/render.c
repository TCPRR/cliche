#include "glob.h"
#include <string.h>

SoftwareBitmap g_backbuffer = {0};
unsigned int g_draw_color = 0x00FFC800; // default cyan (NOT teal)

/* ========= backbuffer ========= */
void CreateBackbuffer(HDC hdc, int width, int height)
{
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    g_backbuffer.bitmap = CreateDIBSection(
        hdc,
        &bmi,
        DIB_RGB_COLORS,
        &g_backbuffer.pixels,
        NULL,
        0
    );

    g_backbuffer.width = width;
    g_backbuffer.height = height;
}

void ClearBackbuffer(unsigned int color)
{
    if (!g_backbuffer.pixels) return;
    unsigned int* p = (unsigned int*)g_backbuffer.pixels;
    int count = g_backbuffer.width * g_backbuffer.height;
    for (int i = 0; i < count; i++)
        p[i] = color;
}

void PresentBackbuffer(HDC hdc)
{
    HDC memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc, g_backbuffer.bitmap);

    BitBlt(
        hdc,
        0, 0,
        g_backbuffer.width,
        g_backbuffer.height,
        memdc,
        0, 0,
        SRCCOPY
    );

    DeleteDC(memdc);
}

/* ========= byte bitmap ========= */
void RenderByteBitmap(
    unsigned int x,
    unsigned int y,
    unsigned int width,
    unsigned int height,
    unsigned char* bytes
)
{
    if (!g_backbuffer.pixels || !bytes) return;

    unsigned int* pixels = (unsigned int*)g_backbuffer.pixels;

    for (unsigned int iy = 0; iy < height; iy++)
    {
        for (unsigned int ix = 0; ix < width; ix++)
        {
            if (!bytes[iy * width + ix]) continue;

            unsigned int px = x + ix;
            unsigned int py = y + iy;

            if (px >= (unsigned)g_backbuffer.width || py >= (unsigned)g_backbuffer.height)
                continue;

            pixels[py * g_backbuffer.width + px] = g_draw_color;
        }
    }
}
