#include "TXLib.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int get_widht  (string adress)
{
	unsigned char info[54];
	FILE*f = fopen (adress.c_str() , "r");
	fread (info, sizeof (unsigned char), 54, f);
	int shirina =* (int*) &info[18];

	return shirina;
}
int get_height  (string adress)
{
	unsigned char info[54];
	FILE*f = fopen (adress.c_str() , "r");
	fread (info, sizeof (unsigned char), 54, f);
	int vysota =* (int*) &info[22];

	return vysota;
}

inline int GetFilePointer(HANDLE FileHandle)
{
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}


void saveToFile(const int KOLICH_KARTINOK, Kartinka pictr[])
{
    ofstream file1("1.txt");

    for (int i = 0; i < KOLICH_KARTINOK; i = i + 1)
    {
       if (pictr[i].clicked)
        {
            file1 << pictr[i].adress<< endl;
            file1 << pictr[i].x << endl;
            file1 << pictr[i].y << endl;
        }
    }
    file1.close();

    txMessageBox("���������");
}

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height)
{
    bool Success=0;
    HBITMAP OffscrBmp=NULL;
    HDC OffscrDC=NULL;
    LPBITMAPINFO lpbi=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return 0;
    if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
        return 0;
    HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
    BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return 0;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(OffscrDC, OldBmp);
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        return 0;
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((BmpFile = CreateFile(filename,
                        GENERIC_WRITE,
                        0, NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL)) == INVALID_HANDLE_VALUE)
        return 0;
    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return 0;
    if (Written < sizeof(BITMAPINFOHEADER))
        return 0;
    int PalEntries;
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
                      (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
    if(lpbi->bmiHeader.biClrUsed)
    PalEntries = lpbi->bmiHeader.biClrUsed;
    if(PalEntries){
    if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
        return 0;
        if (Written < PalEntries * sizeof(RGBQUAD))
            return 0;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
        return 0;
    if (Written < lpbi->bmiHeader.biSizeImage)
        return 0;
    bmfh.bfSize = GetFilePointer(BmpFile);
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;


    CloseHandle (BmpFile);

    delete [] (char*)lpvBits;
    delete [] lpbi;

    DeleteDC (OffscrDC);
    DeleteObject (OffscrBmp);

    return 1;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename, HWND hwnd)
{
    HDC hDC= GetDC(hwnd);
    HDC hDc = CreateCompatibleDC(hDC);

    HBITMAP hBmp = CreateCompatibleBitmap(hDC, width, height);

    HGDIOBJ old= SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, hDC, x, y, SRCCOPY);

    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);

    SelectObject(hDc, old);
    DeleteObject(hBmp);

    DeleteDC (hDc);
    ReleaseDC (hwnd, hDC);

    return ret;
}
