#include "glob.h"
#include "../types.h"
#include <math.h>
#include <string.h>

/* globals */
static HDC g_hdc = NULL;
static HFONT g_font = NULL;

static int g_x = 0;
static int g_y = 0;

static int g_fontSize = 16;
static bool g_bold = false;
static bool g_italic = false;
static char g_fontFace[LF_FACESIZE] = "Arial";
static rgb888 g_color = {255, 255, 255};

/* internal */
static void UpdateFont(void)
{
    if (!g_hdc)
        return;

    if (g_font)
        DeleteObject(g_font);

    g_font = CreateFontA(
        g_fontSize,
        0, 0, 0,
        g_bold ? FW_BOLD : FW_NORMAL,
        g_italic,
        FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        g_fontFace
    );

    SelectObject(g_hdc, g_font);
    SetTextColor(g_hdc, RGB(g_color.r, g_color.g, g_color.b));
    SetBkMode(g_hdc, TRANSPARENT);
}

void SetRenderHDC(HDC hdc)
{
    g_hdc = hdc;
    UpdateFont();
}

void SetFontSize(unsigned char size)
{
    g_fontSize = size;
    UpdateFont();
}

void SetFontFace(char* face)
{
    strncpy(g_fontFace, face, LF_FACESIZE - 1);
    g_fontFace[LF_FACESIZE - 1] = 0;
    UpdateFont();
}

void SetFontBold(bool val)
{
    g_bold = val;
    UpdateFont();
}

void SetFontItalic(bool val)
{
    g_italic = val;
    UpdateFont();
}

void SetFontColor(rgb888 color)
{
    g_color = color;
    if (g_hdc)
        SetTextColor(g_hdc, RGB(color.r, color.g, color.b));
}

void RePositionText(unsigned int x, unsigned int y)
{
    g_x = (int)x;
    g_y = (int)y;
}

void PrintText(char *text)
{
    if (!g_hdc || !text)
        return;

    TextOutA(g_hdc, g_x, g_y, text, (int)strlen(text));
}