#include <windows.h>
#include "Renderer.h"
#include "vec3.h"
#include <tchar.h>
#include <wchar.h>

const char g_szClassName[] = "myWindowClass";
int width, height;
void* memory = 0;
BITMAPINFO bitmap_info;

Renderer renderer;
vec3 vector;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    wchar_t Umsg[32];
    
    switch (msg)
    {
    case WM_KEYDOWN:
        swprintf_s(Umsg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
        OutputDebugStringW(Umsg);
        std::cout << Umsg << "\n";
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        std::cout << "Hello" << "\n";
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();


    //Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    RECT rect;
    GetClientRect(hwnd, &rect);
    width = rect.right - rect.left; //equals 380 for window size = 400x400
    height = rect.bottom - rect.top; // equals 380 for window size = 400x400

    memory = VirtualAlloc(0, width * height * sizeof(unsigned int), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = width;
    bitmap_info.bmiHeader.biHeight = height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;

    uint32_t* pixel = (uint32_t*)memory;

    HDC hdc = GetDC(hwnd);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            *pixel = renderer.CalcPixel(j, i, 800, 800);
            ++pixel; 
        }
        std::clog << "\rScanlines remaining: " << (height - i) << ' ' << std::flush;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);

        StretchDIBits(hdc, 0, 0, width, height, 0, 0, width, height, memory, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);

    }

    return static_cast<int>(Msg.wParam);
}