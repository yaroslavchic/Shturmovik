#include "TXLib.h"

struct Knopka
{
    int x;
    int y;
    const char* text;
};

struct Kartinka
{
    int x;
    int y;
    int shirina;
    int vysota;
    HDC picture;
    string chast;
    int shirina_bmp;
    int vysota_bmp;
    bool clicked;
};

void risovatKnopka(Knopka knopka1, string chast)
{
    txSetColor(TX_WHITE);
    if (chast == knopka1.text)
    {
        txSetColor(TX_RED);
    }
    txTextOut (knopka1.x, knopka1.y, knopka1.text);
}


bool clickNaKnopku(int x, int y)
{
        if (txMouseButtons() == 1 &&
            txMouseX() > x &&
            txMouseY() > y)
            {
                return true;
            }
            else
            {
                return false;
            }
}

bool clickNaKnopka(Kartinka kart, string vybrannaya_chast)
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


string getChast(Knopka knopka1, string chast)
{
    if (txMouseButtons() == 1 &&
        txMouseX() < knopka1.x + 200 &&
        txMouseY() > knopka1.y - 20 &&
        txMouseY() < knopka1.y + 20)
    {
        chast = knopka1.text;
    }

    return chast;
}
const int VYSOTA_SHLEM= 165;
const int SHIRINA_SHLEM = 155;
const int VYSOTA_BRONI = 180;
const int SHIRINA_BRONI = 225;
const int VYSOTA_LAPKI = 190;
const int SHIRINA_LAPKI = 180;

int main()
{
    txCreateWindow (800, 600);

    HDC fon = txLoadImage("Pics\\Ôîí.bmp");
    HDC picture = txLoadImage("Pics\\Øòóðìîâèê1.bmp");

    Knopka knopka[3];
    knopka[0] = {50, 50, "ØËÅÌ"};
    knopka[1] = {50, 150, "ÁÐÎÍß"};
    knopka[2] = {50, 250, "ËÀÏÊÈ"};

    Kartinka kart[9];
     kart[0] = {655,     0, 100, 100, txLoadImage("Pics\\øëåì1.bmp"), "ØËÅÌ", 120, 136};
     kart[1] = {655,  200, 100, 100,  txLoadImage("Pics\\øëåì2.bmp"), "ØËÅÌ", 142, 136};
     kart[2] = {655,  400, 100, 100, txLoadImage("Pics\\ØëÅì.bmp"), "ØËÅÌ", 140, 130};
     kart[3] = {655,     0, 100, 100 , txLoadImage("Pics\\áðîíÿ1.bmp"), "ÁÐÎÍß", 157, 139};
     kart[4] = {655,  200, 100, 100 , txLoadImage("Pics\\áðîíÿ2.bmp"), "ÁÐÎÍß", 150, 164};
     kart[5] = {655,  400, 100, 100 , txLoadImage("Pics\\áðîíÿ3.bmp"), "ÁÐÎÍß", 38, 39};
     kart[6] = {655,      0, 100, 100, txLoadImage("Pics\\ëàïêè1.bmp"), "ËÀÏÊÈ", 121, 84};
     kart[7] = {655,  200, 100, 100, txLoadImage("Pics\\ëàïêè2.bmp"), "ËÀÏÊÈ", 100, 123};
     kart[8] = {655,  400, 100, 100, txLoadImage("Pics\\ëàïêè3.bmp"), "ËÀÏÊÈ", 100, 123};

 Kartinka pictr[9];
    pictr[0] = {320, 130, SHIRINA_SHLEM, VYSOTA_SHLEM};
    pictr[1] = {320, 130, SHIRINA_SHLEM, VYSOTA_SHLEM};
    pictr[2] = {320, 130, SHIRINA_SHLEM, VYSOTA_SHLEM};
    pictr[3] = {280,  285, SHIRINA_BRONI, VYSOTA_BRONI };
    pictr[4] = {280,  285, SHIRINA_BRONI, VYSOTA_BRONI};
    pictr[5] = {280,  285, SHIRINA_BRONI, VYSOTA_BRONI};
    pictr[6] = {330,  400, SHIRINA_LAPKI, VYSOTA_LAPKI};
    pictr[7] = {330,  400, SHIRINA_LAPKI, VYSOTA_LAPKI};
    pictr[8] = {330,  400, SHIRINA_LAPKI, VYSOTA_LAPKI};

        for (int i = 0; i < 9; i = i + 1)
        {
            pictr[i].picture = kart[i].picture;
            pictr[i].chast = kart[i].chast;
            pictr[i].shirina_bmp = kart[i].shirina_bmp;
            pictr[i].vysota_bmp = kart[i].vysota_bmp;
        }




    string chast = "";

    while(true)
    {
        txBegin();

        txBitBlt(txDC(), 0, 0, 800, 600,  fon, 0, 0);
        for (int i = 0; i < 3; i = i + 1)
        {
            risovatKnopka(knopka[i], chast);
        }


          txTransparentBlt(txDC(), 275, 135, 250, 450,  picture, 0, 0, TX_WHITE);




    for (int i = 0; i < 9; i = i + 1)
        {
        if (pictr[i].clicked)
        {
            Win32::TransparentBlt(txDC(), pictr[i].x, pictr[i].y, pictr[i].shirina, pictr[i].vysota, pictr[i].picture, 0, 0, pictr[i].shirina_bmp, pictr[i].vysota_bmp, TX_WHITE);
        }

         }



        for (int i = 0; i < 3; i = i + 1)
        {
        chast = getChast(knopka[i], chast);
        }


    for (int i = 0; i < 9; i = i + 1)
        {
        if(chast== kart[i].chast)
        {
            Win32::TransparentBlt(txDC(), kart[i].x,   kart[i].y, kart[i].shirina, kart[i].vysota, kart[i].picture,  0, 0, kart[i].shirina_bmp, kart[i].vysota_bmp, TX_WHITE);
        }
    }

    for (int i = 0; i < 9; i = i + 1)
        {
        if (clickNaKnopka(kart[i], chast))
        {
            pictr[i].clicked = true;
        }
        else if (txMouseButtons() == 1)
        {
            pictr[i].clicked = false;
        }
        }

        txSleep(10);
        txEnd();
    }


    return 0;
}
