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

  HWND hwnd = CreateWindowExA(WS_EX_LAYERED | WS_EX_NOREDIRECTIONBITMAP |
                                  WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
                              ClASS_NAME, "Tasknet", WS_POPUP, 2160, 520, 800,
                              400, nullptr, nullptr, hInstance, &props);

  if (hwnd == nullptr) {
    MessageBoxA(nullptr, "Failed to create window.", "Error", MB_ICONERROR);
    std::throw_with_nested("Failed to create window");
  }
  props.hwnd_ = hwnd;
  props.nCmdShow_ = nCmdShow;

  RegisterHotKey(hwnd, 1, MOD_WIN | MOD_SHIFT, 'K');
}
WindowHandler::~WindowHandler() { UnregisterHotKey(props.hwnd_, 1); }

LRESULT WindowHandler::SearchBarWinProc(HWND hwnd, UINT uMsg, WPARAM wparam,
                                        LPARAM lparam) {
  WindowProps *pState;
  switch (uMsg) {
  case WM_CREATE: {
    DWM_BLURBEHIND bb = {0};
    bb.fEnable = TRUE;
    bb.dwFlags = DWM_BB_ENABLE;
    bb.hRgnBlur = nullptr;
    HRESULT res = DwmEnableBlurBehindWindow(hwnd, &bb);
    std::cout << res << std::endl;

    CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lparam);
    pState = reinterpret_cast<WindowProps *>(pCreate->lpCreateParams);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
    break;
  }
  case WM_HOTKEY: {
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    pState = reinterpret_cast<WindowProps *>(ptr);
    pState->bVisible ^= true;
    if (pState->bVisible) {
      ShowWindow(pState->hwnd_, pState->nCmdShow_);
      UpdateWindow(pState->hwnd_);
    } else {
      ShowWindow(pState->hwnd_, SW_HIDE);
    }
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
