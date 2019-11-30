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
    txSetColor(TX_YELLOW);
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
