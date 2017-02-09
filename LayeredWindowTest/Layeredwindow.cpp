#include "stdafx.h"

#include "Layeredwindow.h"
#include "Resource.h"

LayeredWindow::LayeredWindow() {

}

LayeredWindow::~LayeredWindow() {

}

void LayeredWindow::Draw() {
  RECT layeredRect;
  GetClientRect(&layeredRect);
  int layeredWidth = layeredRect.right - layeredRect.left;
  int layeredHeight = layeredRect.bottom - layeredRect.top;

  HDC presentDC = ::CreateCompatibleDC(NULL);
  BITMAPINFOHEADER bih = { 0 };
  bih.biBitCount = 32;
  bih.biSize = sizeof(BITMAPINFOHEADER);
  bih.biWidth = layeredWidth;
  bih.biHeight = -layeredHeight;
  bih.biPlanes = 1;
  bih.biSizeImage = layeredWidth * layeredHeight * 4;
  bih.biCompression = BI_RGB;
  RGBQUAD* pBits = NULL;
  HBITMAP bmp = ::CreateDIBSection(presentDC, (BITMAPINFO*)&bih, 0, (void**)&pBits, NULL, 0);

  for (int j = 0; j < layeredHeight; j++) {
    for (int i = 0; i < layeredWidth; i++) {
      if (i < layeredWidth / 2) {
        //pBits[i + j * layeredHeight] = 0xffffffff;
        memset((void*)&pBits[i + j * layeredWidth], 0x0, sizeof(RGBQUAD));
      }
      else {
       // pBits[i + j * layeredHeight] = 0;
        memset((void*)&pBits[i + j * layeredWidth], 0, sizeof(RGBQUAD));
      }
    }
  }

  HBITMAP hOldBitmap = (HBITMAP)::SelectObject(presentDC, (HGDIOBJ)bmp);

  SIZE size = { 0 };
  size.cx = layeredWidth;
  size.cy = layeredHeight;
  BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

  POINT ptSrc = { 0, 0 };

  UpdateLayeredWindow(m_hWnd, NULL, NULL, &size, presentDC, &ptSrc, 0, &blend, ULW_ALPHA);

  bmp = (HBITMAP)::SelectObject(presentDC, (HGDIOBJ)hOldBitmap);
  ::DeleteObject(bmp);
  ::DeleteDC(presentDC);
}