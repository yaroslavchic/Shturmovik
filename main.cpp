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
const int VYSOTA_SHLEM= 120;
const int SHIRINA_SHLEM = 100;
const int VYSOTA_BRONI = 120;
const int SHIRINA_BRONI = 100;
const int VYSOTA_LAPKI = 120;
const int SHIRINA_LAPKI = 100;

int main()
{
    txCreateWindow (800, 600);

    HDC fon = txLoadImage("Pics\\Ôîí.bmp");
    HDC picture = txLoadImage("Pics\\øòóðìîâèê1.bmp");

    Knopka knopka[3];
    knopka[0] = {50, 50, "ØËÅÌ"};
    knopka[1] = {50, 150, "ÁÐÎÍß"};
    knopka[2] = {50, 250, "ËÀÏÊÈ"};

    Kartinka kart[9];
     kart[0] = {655,     0, SHIRINA_SHLEM, VYSOTA_SHLEM, txLoadImage("Pics\\øëåì1.bmp"), "ØËÅÌ", 120, 136};
     kart[1] = {655,  200, SHIRINA_SHLEM, VYSOTA_SHLEM,  txLoadImage("Pics\\øëåì2.bmp"), "ØËÅÌ", 142, 136};
     kart[2] = {655,  400, SHIRINA_SHLEM, VYSOTA_SHLEM, txLoadImage("Pics\\ØëÅì.bmp"), "ØËÅÌ", 140, 130};
     kart[3] = {655,     0, SHIRINA_BRONI, VYSOTA_BRONI , txLoadImage("Pics\\áðîíÿ1.bmp"), "ÁÐÎÍß", 157, 139};
     kart[4] = {655,  200, SHIRINA_BRONI, VYSOTA_BRONI , txLoadImage("Pics\\áðîíÿ2.bmp"), "ÁÐÎÍß", 150, 183};
     kart[5] = {655,  400, SHIRINA_BRONI, VYSOTA_BRONI , txLoadImage("Pics\\áðîíÿ3.bmp"), "ÁÐÎÍß", 38, 39};
     kart[6] = {655,      0, SHIRINA_LAPKI, VYSOTA_LAPKI, txLoadImage("Pics\\ëàïêè1.bmp"), "ËÀÏÊÈ", 84, 121};
     kart[7] = {655,  200, SHIRINA_LAPKI, VYSOTA_LAPKI, txLoadImage("Pics\\ëàïêè2.bmp"), "ËÀÏÊÈ", 100, 123};
     kart[8] = {655,  400, SHIRINA_LAPKI, VYSOTA_LAPKI, txLoadImage("Pics\\ëàïêè3.bmp"), "ËÀÏÊÈ", 100, 123};


    Kartinka pictr1 = {300, 200, SHIRINA_SHLEM, VYSOTA_SHLEM, kart[0].picture, "ØËÅÌ"};
    Kartinka pictr2 = {300, 200, SHIRINA_SHLEM, VYSOTA_SHLEM, kart[1].picture, "ØËÅÌ"};
    Kartinka pictr3 = {300, 200, SHIRINA_SHLEM, VYSOTA_SHLEM, kart[2].picture, "ØËÅÌ"};



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


        if (pictr1.clicked)
        {
            Win32::TransparentBlt(txDC(), pictr1.x, pictr1.y, pictr1.shirina, pictr1.vysota, pictr1.picture, 0, 0, 120, 136, TX_WHITE);
        }
        if (pictr2.clicked)
        {
            Win32::TransparentBlt(txDC(), pictr2.x, pictr2.y, pictr2.shirina, pictr2.vysota, pictr2.picture, 0, 0, 142, 136, TX_WHITE);
        }
         if (pictr3.clicked)
        {
            Win32::TransparentBlt(txDC(), pictr3.x, pictr3.y, pictr3.shirina, pictr3.vysota, pictr3.picture, 0, 0, 140, 130, TX_WHITE);
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

        if (clickNaKnopka(kart[0], chast))
        {
            pictr1.clicked = true;
        }
        else if (txMouseButtons() == 1)
        {
            pictr1.clicked = false;
        }

        if (clickNaKnopka(kart[1], chast))
        {
            pictr2.clicked = true;
        }
        else if (txMouseButtons() == 1)
        {
            pictr2.clicked = false;
        }

        if (clickNaKnopka(kart[2], chast))
        {
            pictr3.clicked = true;
        }
        else if (txMouseButtons() == 1)
        {
            pictr3.clicked = false;
        }

        txSleep(10);
        txEnd();
    }







    return 0;
}

