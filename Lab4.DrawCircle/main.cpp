
#include "basewin.hpp"
#include "geometry.hpp"
#include "memdc.hpp"
#include "windowsx.h"
#include "wingdi.h"

#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>

#pragma comment(lib, "msimg32")

class DrawWindow : public BaseWindow<DrawWindow> {
public:
  DrawWindow() {
    mode = CIRCLE;
    is_drawing = false;
    is_holding = false;
    pen_color = RGB(200, 60, 0);
  }

  PCWSTR ClassName() const override { return L"Draw Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

  void OnLButtonDown(int x, int y, DWORD flags);
  void OnRButtonDown(int x, int y, DWORD flags);
  void OnLButtonUp(int x, int y, DWORD flags);
  void OnMouseMove(int x, int y, DWORD flags);
  void OnPaint();

  enum DrawMode { EMPTY, BRUSH, LINE, CIRCLE, ELLIPSE };

  enum { MASK_COLOR = RGB(255, 255, 255) };

private:
  MemoryDC background;
  MemoryDC preview;
  MemoryDC buffer;

  DrawMode mode;
  bool is_drawing;
  bool is_holding;
  int src_x, src_y;
  int dst_x, dst_y;
  std::vector<std::pair<int, int>> pixel_buffer;

  // @TODO: Implement a brush class to control the drawing thickness, color and other attributes
  COLORREF pen_color;
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine,
                    int nCmdShow) {
  DrawWindow win;

  if (!win.Create(L"Lab3.DrawCircle", WS_OVERLAPPEDWINDOW)) {
    return 0;
  }

  ShowWindow(win.Window(), nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

// Implement your window process here
LRESULT DrawWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE: {
    RECT rc;
    GetClientRect(m_hwnd, &rc);

    buffer.resize(rc.right, rc.bottom);
    preview.resize(rc.right, rc.bottom);
    background.resize(rc.right, rc.bottom);

    rc = {0, 0, background.get_width(), background.get_height()};
    FillRect(background, &rc, (HBRUSH)GetStockObject(LTGRAY_BRUSH));

    rc = {0, 0, preview.get_width(), preview.get_height()};
    FillRect(preview, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
    return 0;
  }

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_RBUTTONDOWN:
    OnRButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
    return 0;

  case WM_PAINT:
    OnPaint();
    return 0;

  case WM_LBUTTONDOWN:
    OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
    return 0;

  case WM_LBUTTONUP:
    OnLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
    return 0;

    // https://stackoverflow.com/questions/53958727/performance-efficient-way-of-setting-pixels-in-gdi
  case WM_MOUSEMOVE:
    OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
    return 0;

  case WM_MBUTTONDOWN:
    mode = DrawMode((mode + 1) % 5);
    return 0;

  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return TRUE;
}

void DrawWindow::OnLButtonDown(int x, int y, DWORD flags) {
  if (mode == EMPTY)
    return;

  if (is_drawing) {
    // end up drawing
    is_drawing = false;
    dst_x = x, dst_y = y;
    // set preview layer to background
    TransparentBlt(background, 0, 0, preview.get_width(), preview.get_height(),
                   preview, 0, 0, preview.get_width(), preview.get_height(),
                   MASK_COLOR);
  } else {
    // start up drawing
    src_x = x, src_y = y;
    is_drawing = true;
    is_holding = true;
  }
}

void DrawWindow::OnLButtonUp(int x, int y, DWORD flags) {
  if (is_holding) {
    is_holding = false;

    if (mode == BRUSH) {
      // set preview layer to background
      is_drawing = false;
      TransparentBlt(background, 0, 0, preview.get_width(),
                     preview.get_height(), preview, 0, 0, preview.get_width(),
                     preview.get_height(), MASK_COLOR);
    }
  }
}

void DrawWindow::OnMouseMove(int x, int y, DWORD flags) {
  if (is_drawing) {

    if (mode != BRUSH) {
      RECT rc = {0, 0, preview.get_width(), preview.get_height()};
      FillRect(preview, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
      pixel_buffer.resize(0);
    }

    switch (mode) {
    case LINE:
      draw_line(src_x, src_y, x, y, pixel_buffer);
      break;

    case CIRCLE: {
      int xc = (x + src_x) / 2;
      int yc = (y + src_y) / 2;
      int rx = abs(x - src_x);
      int ry = abs(y - src_y);
      draw_circle_simple(xc, yc, std::sqrt(rx * rx + ry * ry) / 2,
                                     pixel_buffer);
//      draw_circle_midpoint_bresenham(xc, yc, std::sqrt(rx * rx + ry * ry) / 2,
//                                       pixel_buffer);
      break;
    }

    case ELLIPSE: {
      int xc = (x + src_x) / 2;
      int yc = (y + src_y) / 2;
      int rx = abs(x - src_x) / 2;
      int ry = abs(y - src_y) / 2;
      draw_ellipse_midpoint_bresenham(xc, yc, rx, ry, pixel_buffer);
      break;
    }

    case BRUSH: {
      // still not work right for now
      if (is_holding) {
        SetPixelV(preview, x, y, pen_color);
      }
    }
    }

    for (auto &i : pixel_buffer) {
      SetPixelV(preview, i.first, i.second, pen_color);
    }

    InvalidateRect(m_hwnd, NULL, FALSE);
  }
}
void DrawWindow::OnPaint() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hwnd, &ps);

  BitBlt(buffer, 0, 0, background.get_width(), background.get_height(),
         background, 0, 0, SRCCOPY);

  TransparentBlt(buffer, 0, 0, preview.get_width(), preview.get_height(),
                 preview, 0, 0, preview.get_width(), preview.get_height(),
                 MASK_COLOR);

  BitBlt(hdc, 0, 0, buffer.get_width(), buffer.get_height(), buffer, 0, 0,
         SRCCOPY);
  EndPaint(m_hwnd, &ps);
}

void DrawWindow::OnRButtonDown(int x, int y, DWORD flags) {
  // cancel drawing
  if (is_drawing) {
    is_drawing = false;

    // flush preview layer
    RECT rc = {0, 0, preview.get_width(), preview.get_height()};
    FillRect(preview, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
    InvalidateRect(m_hwnd, NULL, FALSE);
  }
}
