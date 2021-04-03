#ifndef UNICODE
#define UNICODE
#endif

#include <cstdio>
#include <vector>
#include <windows.h>
#include <windowsx.h>
#include <wingdi.h>

#include "global.h"
#include "line.h"

struct StateInfo {
  bool is_draw;
  Point p_src, p_dst;
  std::vector<std::pair<Point, COLORREF>> pixels_cache;
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  // Register the window class.
  const wchar_t CLASS_NAME[] = L"Sample Window Class";

  WNDCLASS wc = {};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);

  RegisterClass(&wc);

  // Create the window.
  auto pState = new StateInfo();

  HWND hwnd = CreateWindowEx(0,                   // Optional window styles.
                             CLASS_NAME,          // Window class
                             L"Lab1.DrawLine", // Window text
                             WS_OVERLAPPEDWINDOW, // Window style

                             // Size and position
                             CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

                             NULL,      // Parent window
                             NULL,      // Menu
                             hInstance, // Instance handle
                             pState     // Additional application data
  );

  if (hwnd == NULL) {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  // Run the message loop.
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  delete pState;
  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  StateInfo *pState;

  if (uMsg == WM_CREATE) {
    CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
    pState = reinterpret_cast<StateInfo *>(pCreate->lpCreateParams);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
  } else {
    pState =
        reinterpret_cast<StateInfo *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
  }

  switch (uMsg) {
  case WM_DESTROY:
    PostQuitMessage(0);

  case WM_MOUSEMOVE: {

    if (pState->is_draw) {
      Point p = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};

      if (pState->p_dst.x != p.x || pState->p_dst.y != p.y) {
        auto res_add = draw_line_DDA(pState->p_src, p);
        //auto res_add = draw_line_bresenham(pState->p_src, p);
        pState->p_dst = p;
        // Restore previous line
        auto hdc = GetDC(hwnd);
        for (int i = 0; i < pState->pixels_cache.size(); i++) {
          SetPixel(hdc, pState->pixels_cache[i].first.x,
                   pState->pixels_cache[i].first.y,
                   pState->pixels_cache[i].second);
        }

        // Draw new line
        pState->pixels_cache.clear();
        for (int i = 0; i < res_add.size(); i++) {
          // Save covered pixels
          pState->pixels_cache.emplace_back(
              res_add[i], GetPixel(hdc, res_add[i].x, res_add[i].y));

          SetPixel(hdc, res_add[i].x, res_add[i].y, RGB(0, 0, 0));
        }
        ReleaseDC(hwnd, hdc);
      }
    }
  }
    return 0;

  case WM_LBUTTONUP:
    return 0;

  case WM_LBUTTONDOWN: {
    if (!pState->is_draw) {
      pState->is_draw = true;
      pState->p_src.x = GET_X_LPARAM(lParam);
      pState->p_src.y = GET_Y_LPARAM(lParam);
    } else {
      // Stop drawing when mouse is moving
      pState->is_draw = false;
      pState->pixels_cache.clear();
    }
  }
    return 0;

  case WM_RBUTTONDOWN: {
    // Cancel draw
    if (pState->is_draw) {
      pState->is_draw = false;
      auto hdc = GetDC(hwnd);
      for (int i = 0; i < pState->pixels_cache.size(); i++) {
        SetPixel(hdc, pState->pixels_cache[i].first.x,
                 pState->pixels_cache[i].first.y,
                 pState->pixels_cache[i].second);
      }
      ReleaseDC(hwnd, hdc);
      pState->pixels_cache.clear();
    }
  }

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(hwnd, &ps);
  }
    return 0;

  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }


  return TRUE;
}