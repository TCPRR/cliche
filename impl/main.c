#include <windows.h>
#include "glob.h"
#include "../types.h"

// 8x8 smiley
unsigned char bmp[64] = {
    0,1,1,0,0,1,1,0,
    1,0,0,1,1,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,1,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,1,
    0,1,0,0,0,0,1,0,
    0,0,1,1,1,1,0,0
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_PAINT:
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    static int init = 0;
    if (!init)
    {
        CreateBackbuffer(hdc, 640, 480);
        init = 1;
    }

    ClearBackbuffer(0x00000000); // black

    // draw bitmap
    g_draw_color = 0x00FFC800;
    RenderByteBitmap(20, 60, 8, 8, bmp);

    // blit backbuffer
    PresentBackbuffer(hdc);

    // draw text on top
    SetRenderHDC(hdc);
    SetFontFace("Consolas");
    SetFontSize(20);
    SetFontBold(true);
    SetFontColor((rgb888){0,200,255});
    RePositionText(20, 20);
    PrintText("Herroowww from OwO-C :3");

    EndPaint(hwnd, &ps);
}

        return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShow)
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "win32_test";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowA(
        "win32_test",
        "ay mi gatito meow meow",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        640, 480,
        NULL, NULL, hInst, NULL
    );

    ShowWindow(hwnd, nShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
