#include <windows.h>

// Global variables to control the triangle color
COLORREF triangleColor = RGB(0, 0, 0);  // Starts Black
int r = 0, g = 0, b = 0;  // RGB values

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

    // Register the window class with Windows
    RegisterClassExW(&wc);

    // Create the window
    HWND hwnd = CreateWindowExW(
        0,                              // Extended window style
        CLASS_NAME,                     // Window class name
        L"My Triangle",                // Window title
        WS_OVERLAPPEDWINDOW,           // Window style (standard window with title bar, etc.)
        CW_USEDEFAULT, CW_USEDEFAULT,  // Position (Windows will choose)
        800, 600,                      // Size (width, height)
        nullptr,                       // Parent window (none)
        nullptr,                       // Menu (none)
        hInstance,                     // Application instance handle
        nullptr                        // Additional data (none)
    );

    // Check if window creation failed
    if (hwnd == nullptr) {
        return 0;
    }

    // Show and update the window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Set up a timer to change the triangle color every 500ms
    SetTimer(hwnd, 0.1, 33, nullptr);

    // Message loop - handles all Windows messages
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);    // Translates keyboard messages
        DispatchMessage(&msg);     // Sends message to WindowProc
    }

    return 0;
}

// Window procedure - handles all window messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);    // Quit the application
            return 0;

        case WM_TIMER:
        {
            // Update the triangle color
            static bool increasing = true;
            static int currentColor = 0;  // 0 = blue, 1 = green, 2 = red
            
            if (currentColor == 0) {
                // Handle blue color
                if (increasing) {
                    b++;
                    if (b >= 255) {
                        b = 255;
                        currentColor = 1;
                        increasing = true;
                    }
                } else {
                    b--;
                    if (b <= 0) {
                        b = 0;
                        currentColor = 1;
                        increasing = false;
                    }
                }
            }
            else if (currentColor == 1) {
                // Handle green color
                if (increasing) {
                    g++;
                    if (g >= 255) {
                        g = 255;
                        currentColor = 2;
                        increasing = true;
                    }
                } else {
                    g--;
                    if (g <= 0) {
                        g = 0;
                        currentColor = 2;
                        increasing = false;
                    }
                }
            }
            else if (currentColor == 2) {
                // Handle red color
                if (increasing) {
                    r++;
                    if (r >= 255) {
                        r = 255;
                        currentColor = 0;
                        increasing = false;
                    }
                } else {
                    r--;
                    if (r <= 0) {
                        r = 0;
                        currentColor = 0;
                        increasing = true;
                    }
                }
            }
            
            triangleColor = RGB(r, g, b);
            InvalidateRect(hwnd, nullptr, TRUE);
            return 0;
        }

        case WM_PAINT:
        {
            // Begin painting
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Create and select a brush with the current color
            HBRUSH hBrush = CreateSolidBrush(triangleColor);
            SelectObject(hdc, hBrush);

            // Define triangle vertices
            POINT points[3] = {
                {400, 100},  // Top vertex
                {200, 500},  // Bottom left vertex
                {600, 500}   // Bottom right vertex
            };

            // Draw the triangle
            Polygon(hdc, points, 3);

            // Set text color to black for better visibility
            SetTextColor(hdc, RGB(0, 0, 0));
            
            // Create text buffer for RGB values
            wchar_t text[50];
            wsprintfW(text, L"R: %d\n G: %d\n B: %d", r, g, b);
            
            // Draw the text
            TextOutW(hdc, 20, 20, text, wcslen(text));

            // Clean up resources
            DeleteObject(hBrush);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_SIZE:
            InvalidateRect(hwnd, nullptr, TRUE);  // Force window repaint when resized
            return 0;
    }

    // Handle default window messages
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}