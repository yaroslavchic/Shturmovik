#include "TXLib.h"
#include "knopka.cpp"
#include <string>

using namespace std;

struct Kartinka
{
    int y;
    string adress;
    HDC picture;
    string chast;
    int shirina_bmp;
    int vysota_bmp;
    int x;
    int shirina;
    int vysota;
    bool clicked;
};

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

    Knopka knopka[4];
    knopka[0] = {50, 50, "ØËÅÌ"};
    knopka[1] = {50, 150, "ÁÐÎÍß"};
    knopka[2] = {50, 250, "ËÀÏÊÈ"};
    knopka[3] = {50, 300, "Cïðàâî÷å÷êà"};

    Kartinka kart[9];
    kart[0] = {     0,   "Pics\\øëåì1.bmp", txLoadImage("Pics\\øëåì1.bmp"), "ØËÅÌ", 120};
    kart[1] = {  200, "Pics\\øëåì2.bmp", txLoadImage("Pics\\øëåì2.bmp"), "ØËÅÌ", 142};
    kart[2] = {  400,  "Pics\\ØëÅì.bmp",txLoadImage("Pics\\ØëÅì.bmp"), "ØËÅÌ", 140};
    kart[3] = {     0,  "Pics\\áðîíÿ1.bmp", txLoadImage("Pics\\áðîíÿ1.bmp"), "ÁÐÎÍß", 157};
    kart[4] = {  200,  "Pics\\áðîíÿ2.bmp",txLoadImage("Pics\\áðîíÿ2.bmp"), "ÁÐÎÍß", 159};
    kart[5] = {  400,   "Pics\\áðîíÿ3.bmp", txLoadImage("Pics\\áðîíÿ3.bmp"), "ÁÐÎÍß", 38};
    kart[6] = {     0,  "Pics\\ëàïêè1.bmp",txLoadImage("Pics\\ëàïêè1.bmp"), "ËÀÏÊÈ", 104};
    kart[7] = {  200, "Pics\\ëàïêè2.bmp", txLoadImage("Pics\\ëàïêè2.bmp"), "ËÀÏÊÈ", 100};
    kart[8] = {  400, "Pics\\ëàïêè3.bmp", txLoadImage("Pics\\ëàïêè3.bmp"), "ËÀÏÊÈ", 100};

    for (int i = 0; i < 9; i = i + 1)
    {
        kart[i].shirina = 100;
        kart[i].vysota = 100;
        kart[i].x = 655;
        kart[i].vysota_bmp = get_height(kart[i].adress);
        kart[i].shirina_bmp = get_widht(kart[i].adress);
    }

    Kartinka pictr[9];
    for (int i = 0; i < 9; i = i + 1)
    {
        pictr[i].picture = kart[i].picture;
        pictr[i].clicked = false;
        pictr[i].chast = kart[i].chast;
        pictr[i].shirina_bmp = kart[i].shirina_bmp;
        pictr[i].vysota_bmp = kart[i].vysota_bmp;

        if (pictr[i].chast == "ËÀÏÊÈ")
        {
            pictr[i].x = 330;
            pictr[i].y = 400;
            pictr[i].shirina = SHIRINA_LAPKI;
            pictr[i].vysota = VYSOTA_LAPKI;
        }
        if (pictr[i].chast == "ØËÅÌ")
        {
            pictr[i].x = 320;
            pictr[i].y = 80;
            pictr[i].shirina = SHIRINA_SHLEM;
            pictr[i].vysota = VYSOTA_SHLEM;
        }
        if (pictr[i].chast == "ÁÐÎÍß")
        {
            pictr[i].x = 280;
            pictr[i].y = 235;
            pictr[i].shirina = SHIRINA_BRONI;
            pictr[i].vysota = VYSOTA_BRONI;
        }
    }






    string chast = "";
    bool spravka_vyzvana = false;
    int nomer_vybrannoi_chasti = -10;

    while(true)
    {
        txBegin();

        txBitBlt(txDC(), 0, 0, 800, 600,  fon, 0, 0);
        for (int i = 0; i < 4; i = i + 1)
        {
            risovatKnopka(knopka[i], chast);
        }


          //txTransparentBlt(txDC(), 275, 135, 250, 450,  picture, 0, 0, TX_WHITE);


        for (int vybor = 0; vybor < 9; vybor = vybor + 1)
        {
            if (clickNaKartinka(pictr[vybor]))
            {
                nomer_vybrannoi_chasti = vybor;
            }
        }

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
            }

            if (GetAsyncKeyState(VK_OEM_MINUS))
            {
                pictr[nomer_vybrannoi_chasti].shirina = pictr[nomer_vybrannoi_chasti].shirina / 1.02;
            }
        }


        for (int i = 0; i < 9; i = i + 1)
        {
            if (pictr[i].clicked)
            {
                Win32::TransparentBlt(txDC(), pictr[i].x, pictr[i].y, pictr[i].shirina, pictr[i].vysota, pictr[i].picture, 0, 0, pictr[i].shirina_bmp, pictr[i].vysota_bmp, TX_WHITE);
            }
         }



        for (int i = 0; i <4; i = i + 1)
        {
        chast = getChast(knopka[i], chast);
        }

    if (txMouseButtons() == 1 &&
        txMouseX() < knopka[3].x + 200 &&
        txMouseY() > knopka[3].y - 20 &&
        txMouseY() < knopka[3].y + 20)
        {
            spravka_vyzvana = !spravka_vyzvana;
            txSleep(200);
        }

        if (spravka_vyzvana)
        {
           txSetColor     (TX_BLACK);
            txRectangle (100, 200, 300, 400);
            txDrawText  (100, 200, 300, 400,
                "Ñîçäàòåëü ßðîñëàâ\n"
                "Â ýòîé ïðîãðàììå âû\n "
                "ñìîæåòå ñîçäàòü\n  "
                "øòóðìîâèêà èç\n"
                "Çâ¸çäíûõ Âîéí");
        }


        for (int i = 0; i < 9; i = i + 1)
            {
            if(chast== kart[i].chast)
            {
                Win32::TransparentBlt(txDC(), kart[i].x,   kart[i].y, kart[i].shirina, kart[i].vysota, kart[i].picture,  0, 0, kart[i].shirina_bmp, kart[i].vysota_bmp, TX_WHITE);
            }
        }

        for (int vybor = 0; vybor < 9; vybor = vybor + 1)
        {
            if (clickNaKnopka(kart[vybor], chast))
            {
                 for (int nomer = 0; nomer < 9; nomer = nomer + 1)
                 {
                     if (pictr[vybor].chast == pictr[nomer].chast)
                     {
                        pictr[nomer].clicked = false;
                     }
                 }

                 pictr[vybor].clicked = true;
            }
        }

        txSleep(10);
        txEnd();
    }

    return 0;
}
