#include "TXLib.h"

struct Kartinka
{
    string adress;
    string chast;
    int x;
    int y;
    int shirina;
    int vysota;
    HDC picture;
    int shirina_bmp;
    int vysota_bmp;
    bool clicked;
};

bool clickNaVariant(Kartinka kart, string vybrannaya_chast)
{
        if (txMouseButtons() == 1 &&
            kart.chast == vybrannaya_chast &&
            txMouseX() > kart.x &&
            txMouseX() < kart.x + kart.shirina &&
            txMouseY() > kart.y &&
            txMouseY() < kart.y + kart.vysota)
            {
                return true;
            }
            else
            {
                return false;
            }
}


bool clickNaKartinka(Kartinka kart)
{
        if (txMouseButtons() == 1 &&
            kart.clicked &&
            txMouseX() > kart.x &&
            txMouseX() < kart.x + kart.shirina &&
            txMouseY() > kart.y &&
            txMouseY() < kart.y + kart.vysota)
            {
                return true;
            }
            else
            {
                return false;
            }
}

void  dwig(Kartinka pictr[], int nomer_vybrannoi_chasti)
{
    if (nomer_vybrannoi_chasti >= 0)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            pictr[nomer_vybrannoi_chasti].x = pictr[nomer_vybrannoi_chasti].x - 2;
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            pictr[nomer_vybrannoi_chasti].x = pictr[nomer_vybrannoi_chasti].x + 2;
        }
        if (GetAsyncKeyState(VK_UP))
        {
            pictr[nomer_vybrannoi_chasti].y = pictr[nomer_vybrannoi_chasti].y - 2;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            pictr[nomer_vybrannoi_chasti].y = pictr[nomer_vybrannoi_chasti].y + 2;
        }

        if (GetAsyncKeyState(VK_OEM_PLUS))
        {
            pictr[nomer_vybrannoi_chasti].shirina = pictr[nomer_vybrannoi_chasti].shirina * 1.02;
            pictr[nomer_vybrannoi_chasti].vysota = pictr[nomer_vybrannoi_chasti].vysota * 1.02;
        }

        if (GetAsyncKeyState(VK_OEM_MINUS))
        {
            pictr[nomer_vybrannoi_chasti].shirina = pictr[nomer_vybrannoi_chasti].shirina / 1.02;
             pictr[nomer_vybrannoi_chasti].vysota = pictr[nomer_vybrannoi_chasti].vysota / 1.02;
        }
    }
}
