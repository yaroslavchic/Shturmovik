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
