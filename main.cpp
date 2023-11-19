#include <windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#define u32 uint32_t

const char g_szClassName[] = "myWindowClass";
int width, height;
void* memory;
BITMAPINFO bitmap_info;
std::string finalHEX = "";
int RGB[3] = { 1, 90, 45 };

int hexadecimalToDecimal(std::string hexVal)
{
    unsigned int x;
    std::stringstream ss;
    ss << std::hex << hexVal;
    ss >> x;
    // output it as a signed type
    return static_cast<unsigned int>(x);
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void RGBtoHex(int decimal_value)
{
    std::stringstream ss;
    ss << std::hex << decimal_value; // int decimal_value
    std::string res(ss.str());

    if (size(res) == 1)
    {
        res = "0" + res;
    }

    finalHEX += res;
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
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
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

    u32* pixel = (u32*)memory;

    HDC hdc = GetDC(hwnd);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);

        RGB[0] = rand() % 256;
        RGB[1] = rand() % 256;
        RGB[2] = rand() % 256;

        RGBtoHex(RGB[0]);
        RGBtoHex(RGB[1]);
        RGBtoHex(RGB[2]);
        *pixel = hexadecimalToDecimal(finalHEX);
        ++pixel;
        finalHEX = "";

        StretchDIBits(hdc, 0, 0, width, height, 0, 0, width, height, memory, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);

    }

    return Msg.wParam;
}
