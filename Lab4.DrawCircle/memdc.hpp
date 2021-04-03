//
// Created by Metal on 2021/3/29.
// https://stackoverflow.com/questions/53958727/performance-efficient-way-of-setting-pixels-in-gdi
//
#pragma once
#ifndef CG2021SPRING_ECNU_MEMDC_HPP
#define CG2021SPRING_ECNU_MEMDC_HPP

#include "windows.h"

class MemoryDC {
public:
    operator HDC() { return hdc; }

     MemoryDC() : hdc(nullptr), hbitmap(nullptr) {}
    ~MemoryDC() { clear(); }

    void clear() {
        if (hdc != nullptr) {
            SelectObject(hdc, holdbitmap);
            DeleteObject(hbitmap);
            DeleteDC(hdc);
        }
    }

    void resize(int new_width, int new_height) {
        clear();
        width = new_width;
        height = new_height;

        HDC hdesktop = GetDC(nullptr);
        hdc = CreateCompatibleDC(hdesktop);
        hbitmap = CreateCompatibleBitmap(hdesktop, width, height);
        holdbitmap = (HBITMAP) SelectObject(hdc, hbitmap);
        ReleaseDC(nullptr, hdc);
    }

    int get_width() const { return width; }
    int get_height() const { return height; }

private:
    HDC hdc;
    HBITMAP hbitmap;
    HBITMAP holdbitmap;
    int width, height;

};


#endif //CG2021SPRING_ECNU_MEMDC_HPP
