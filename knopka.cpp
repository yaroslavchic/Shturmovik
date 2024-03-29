#include "TXLib.h"

struct Knopka
{
    int x;
    int y;
    const char* text;
};

void risovatKnopka(Knopka knopka1, string chast)
{
    txSelectFont("Arial", 24);
    txSetColor(TX_GREEN);
    if (chast == knopka1.text)
    {
        txSetColor(TX_RED);
    }
    txDrawText (knopka1.x, knopka1.y, knopka1.x + 120, knopka1.y + 40, knopka1.text);
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

string getChast(Knopka knopka1, string chast)
{
    if (txMouseButtons() == 1 &&
        txMouseX() < knopka1.x + 120 &&
        txMouseY() > knopka1.y &&
        txMouseY() < knopka1.y + 40)
    {
        chast = knopka1.text;
    }

    return chast;
}
