//
// Created by joydm on 20-11-2025.
//

#include "WindowHandler.h"
#include <dwmapi.h>

#include <exception>
#include <iostream>

WindowHandler::WindowHandler(HINSTANCE hInstance, int nCmdShow) {
  bIsWindowHidden = false;
  constexpr char ClASS_NAME[] = "Tasknet window class";

  WNDCLASSA wc = {};
  wc.lpfnWndProc = SearchBarWinProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = ClASS_NAME;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

  if (!RegisterClassA(&wc)) {
    MessageBoxA(nullptr, "Failed to register window class.", "Error",
                MB_ICONERROR);
    std::throw_with_nested("Failed to create window class");
  }

  HWND hwnd =
      CreateWindowExA(WS_EX_LAYERED | WS_EX_NOREDIRECTIONBITMAP |
                          WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
                      ClASS_NAME, "Tasknet", WS_POPUP | WS_VISIBLE, 2160, 520,
                      800, 400, nullptr, nullptr, hInstance, nullptr);

  if (hwnd == nullptr) {
    MessageBoxA(nullptr, "Failed to create window.", "Error", MB_ICONERROR);
    std::throw_with_nested("Failed to create window");
  }
  hwnd_ = hwnd;
  nCmdShow_ = nCmdShow;

  int res = RegisterHotKey(hwnd, 1, MOD_WIN | MOD_SHIFT, 'K');
  std::cout << "Hotkey registered" << res << std::endl;
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);
}
WindowHandler::~WindowHandler() { UnregisterHotKey(hwnd_, 1); }

LRESULT WindowHandler::SearchBarWinProc(HWND hwnd, UINT uMsg, WPARAM wparam,
                                        LPARAM lparam) {
  switch (uMsg) {
  case WM_CREATE: {
    DWM_BLURBEHIND bb = {0};
    bb.fEnable = TRUE;
    bb.dwFlags = DWM_BB_ENABLE;
    bb.hRgnBlur = nullptr;
    HRESULT res = DwmEnableBlurBehindWindow(hwnd, &bb);
    std::cout << res << std::endl;
    break;
  }
  case WM_HOTKEY: {
    // WindowHandler();
    MessageBeep(MB_ICONERROR); // TODO: Replace
    break;
  }
  case WM_DESTROY:
    return 0;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    const char *text = "Tasknet Core UI";
    TextOutA(hdc, 10, 10, text, lstrlenA(text));

    EndPaint(hwnd, &ps);
    return 0;
  }
  default:
    break;
  }

  return DefWindowProc(hwnd, uMsg, wparam, lparam);
}
