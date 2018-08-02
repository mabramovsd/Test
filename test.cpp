#include "TXLib.h"

void drawQuestion(const char* text)
{
    txSetFillColor(TX_RED);
    txRectangle(100, 0, 800, 100);
    txDrawText(100, 0, 800, 100, text);
}

void drawAnswer(int x1, int y1, int x2, int y2, const char* text)
{
    txRectangle(x1, y1, x2, y2);
    txDrawText(x1, y1, x2, y2, text);
}

int main()
{
    txCreateWindow(900, 600);

    //����� �������
    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("��� ������");
    drawAnswer(100, 250, 300, 350, "��� �����1");
    drawAnswer(600, 250, 800, 350, "��� �����2");
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("��� ������2");
    drawAnswer(100, 250, 300, 350, " �����1");
    drawAnswer(600, 250, 800, 350, " �����2");
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    drawQuestion("��� ������3");
    drawAnswer(100, 250, 300, 350, "��� �����1");
    drawAnswer(600, 250, 800, 350, "��� �����2");
    txSleep(3000);


    return 0;
}
