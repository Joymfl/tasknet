//
// Created by joydm on 20-11-2025.
//

#ifndef TASKNET_WINDOWHANDLER_H
#define TASKNET_WINDOWHANDLER_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class WindowHandler {
public:
  WindowHandler(HINSTANCE hInstance, int nCmdShow);
  ~WindowHandler();

private:
  bool bIsWindowHidden;
  HWND hwnd_;
  int nCmdShow_;
  HWND searchBarWinHWND = nullptr;
  static LRESULT SearchBarWinProc(HWND hwnd, UINT uMsg, WPARAM wparam,
                                  LPARAM lparam);
};

#endif // TASKNET_WINDOWHANDLER_H
