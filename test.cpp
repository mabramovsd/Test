#include "TXLib.h"

int main()
{
    txCreateWindow(900, 600);

    //����� �������
    txSetFillColor(TX_RED);
    txRectangle(100, 0, 800, 100);
    txDrawText(100, 0, 800, 100, "��� ������");

    //����� ������ 1
    txRectangle(100, 250, 300, 350);
    txDrawText(100, 250, 300, 350, "��� �����1");

    //����� ������ 2
    txRectangle(600, 250, 800, 350);
    txDrawText(600, 250, 800, 350, "��� �����2");

    return 0;
}
