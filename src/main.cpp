#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMSG, WPARAM wparam, LPARAM lparam) {
  switch (uMSG) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    const char* text = "Tasknet Core UI";
    TextOutA(hdc, 10, 10, text, lstrlenA(text));

    EndPaint(hwnd, &ps);
    return 0;
  }
  default:
    break;
  }

  return DefWindowProc(hwnd, uMSG, wparam, lparam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  (void) hPrevInstance;
  (void) lpCmdLine;

  const char ClASS_NAME[] = "Taskent window class";

  WNDCLASSA wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = ClASS_NAME;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

  if (!RegisterClassA(&wc)) {
    MessageBoxA(nullptr, "Failed to register window class.", "Error", MB_ICONERROR);
    return 1;
  }

  HWND hwnd = CreateWindowExA(0, ClASS_NAME, "Tasknet", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);

  if (hwnd == nullptr) {
    MessageBoxA(nullptr, "Failed to create window.", "Error", MB_ICONERROR);
    return 1;
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  MSG msg = {};
  while (GetMessage(&msg, nullptr, 0,0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}