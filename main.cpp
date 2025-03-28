#include <windows.h>

// Window callback function - handles all window messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class
    const wchar_t CLASS_NAME[] = L"Triangle Window Class";
    
    // Initialize window class structure
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);        // Size of the structure
    wc.lpfnWndProc = WindowProc;            // Pointer to the window procedure
    wc.hInstance = hInstance;               // Handle to the application instance
    wc.lpszClassName = CLASS_NAME;          // Name of the window class
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);  // Default cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Background color

    RegisterClassExW(&wc);

    // Create the window
    HWND hwnd = CreateWindowExW(
        0,                              // Extended window style
        CLASS_NAME,                     // Window class name
        L"Triangle Window",            // Window title (ASCII only)
        WS_OVERLAPPEDWINDOW,           // Window style (standard window with title bar, etc.)
        CW_USEDEFAULT, CW_USEDEFAULT,  // Position (Windows will choose)
        800, 600,                      // Size (width, height)
        nullptr,                       // Parent window (none)
        nullptr,                       // Menu (none)
        hInstance,                     // Application instance handle
        nullptr                        // Additional data (none)
    );

    if (hwnd == nullptr)
    {
        return 0;
    }

    // Set the window title explicitly
    SetWindowTextW(hwnd, L"Triangle Window");

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window callback function - handles all window messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
} 