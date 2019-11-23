#include "TXLib.h"
#include "knopka.cpp"
#include "kartinka.cpp"
#include <string>


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

const int VYSOTA_SHLEM= 165;
const int SHIRINA_SHLEM = 155;
const int VYSOTA_BRONI = 180;
const int SHIRINA_BRONI = 225;
const int VYSOTA_LAPKI = 190;
const int SHIRINA_LAPKI = 180;

int main()
{
    txCreateWindow (800, 600);

    HDC fon = txLoadImage("Pics\\Фон.bmp");
    HDC picture = txLoadImage("Pics\\Штурмовик1.bmp");

    Knopka knopka[4];
    knopka[0] = {50, 50, "шлем"};
    knopka[1] = {50, 150, "броня"};
    knopka[2] = {50, 250, "лапки"};
    knopka[3] = {50, 300, "Cправочечка"};

    Kartinka kart[9];
    kart[0] = {  "Pics\\шлем\\шлем1.bmp"};
    kart[1] = {  "Pics\\шлем\\шлем2.bmp"};
    kart[2] = {  "Pics\\шлем\\ШлЕм.bmp"};
    kart[3] = {  "Pics\\броня\\броня1.bmp"};
    kart[4] = {  "Pics\\броня\\броня2.bmp"};
    kart[5] = {  "Pics\\броня\\броня3.bmp"};
    kart[6] = {  "Pics\\лапки\\лапки1.bmp"};
    kart[7] = {  "Pics\\лапки\\лапки2.bmp"};
    kart[8] = {  "Pics\\лапки\\лапки3.bmp"};

    int yShlem = 0;
    int yBronia = 0;
    int yLapok = 0;
    for (int i = 0; i < 9; i = i + 1)
    {
        setlocale(LC_ALL,"Russian");

        string stroka = kart[i].adress;
        int pos1 = stroka.find("\\");
        int pos2 = stroka.find("\\", pos1 + 2);
        kart[i].chast = stroka.substr(pos1 + 1, pos2 - pos1 - 1);


        if (kart[i].chast == "лапки")
        {
            kart[i].y = yLapok;
            yLapok = yLapok + 200;
        }

        if (kart[i].chast == "шлем")
        {
            kart[i].y = yShlem ;
            yShlem  = yShlem  + 200;
        }

        if (kart[i].chast == "броня")
        {
            kart[i].y = yBronia;
            yBronia = yBronia + 200;
        }

         kart[i].shirina = 100;
        kart[i].vysota = 100;
        kart[i].x = 655;
        kart[i].picture = txLoadImage(kart[i].adress.c_str());

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

        if (pictr[i].chast == "лапки")
        {
            pictr[i].x = 330;
            pictr[i].y = 400;
            pictr[i].shirina = SHIRINA_LAPKI;
            pictr[i].vysota = VYSOTA_LAPKI;
        }
        if (pictr[i].chast == "шлем")
        {
            pictr[i].x = 320;
            pictr[i].y = 80;
            pictr[i].shirina = SHIRINA_SHLEM;
            pictr[i].vysota = VYSOTA_SHLEM;
        }
        if (pictr[i].chast == "броня")
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
                "Создатель Ярослав\n"
                "В этой программе вы\n "
                "сможете создать\n  "
                "штурмовика из\n"
                "Звёздных Войн");
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
            if (clickNaVariant(kart[vybor], chast))
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
