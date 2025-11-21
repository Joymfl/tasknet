#include "WindowHandler/WindowHandler.h"

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMSG, WPARAM wparam,
                            LPARAM lparam) {
  switch (uMSG) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_HOTKEY:
    PostQuitMessage(0);
    return 0;
  default:
    break;
  }

  return DefWindowProc(hwnd, uMSG, wparam, lparam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
  constexpr char CLASS_NAME[] = "HiddenClass";
  WNDCLASSA wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  if (!RegisterClass(&wc)) {
    MessageBoxA(nullptr, "Failed to register window class", "ERROR",
                MB_ICONERROR);
    return 1;
  }

  HWND hwnd = CreateWindowEx(0, CLASS_NAME, "", 0, 0, 0, 0, 0, nullptr, nullptr,
                             hInstance, nullptr);
  if (hwnd == nullptr) {
    return -1;
  }

  RegisterHotKey(hwnd, 2, MOD_WIN | MOD_SHIFT, 'Q');
  MSG msg;
  WindowHandler window_handler = WindowHandler(hInstance, nCmdShow);
  while (GetMessage(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  UnregisterHotKey(hwnd, 2);
  return 0;
}