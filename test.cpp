#include "TXLib.h"
#include "answer.cpp"

struct Hero
{
    int x_start;
    int y_start;
    int x;
    int y;
    int width;
    int height;
    int speed;
    HDC pic;
};

void move_hero(Hero* man)
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        man->x -= man->speed;
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        man->x += man->speed;
    }

    if (GetAsyncKeyState(VK_UP))
    {
        man->y -= man->speed;
    }
    else if (GetAsyncKeyState(VK_DOWN))
    {
        man->y += man->speed;
    }
}

int main()
{
    txCreateWindow(900, 600);

    Question que[100];
    int count_questions = 0;
    int kolichestvo_pravilnyh = 0;
    char stroka_dlya_kolichestvo_pravilnyh[100];

    HDC hole = txLoadImage("Яма.bmp");
    HDC button = txLoadImage("Кнопка.bmp");
    HDC iguana = txLoadImage("Игуана.bmp");
    HDC agutin = txLoadImage("Агутин.bmp");
    HDC dinosaur = txLoadImage("Динозавр.bmp");
    HDC cheburek = txLoadImage("Чебурек.bmp");
    HDC explosion = txLoadImage("Взрыв.bmp");
    Hero face = {450, 600, 450, 600, 176, 257, 4, txLoadImage("Лицо.bmp")};

    txSetColor(TX_BLACK);

    //Заполняем вопросы нормально
    que[count_questions++] = {"Куда ты прыгнешь?",
        {{"", true, hole},
         {"", false, hole}},
        iguana
    };
    que[count_questions++] = {"На какую кнопку нажмешь?",
        {{"", false, button},
         {"", true, button}},
        agutin
    };


    //Считаем количество ответов и расставляем их
    for (int nomer = 0; nomer < count_questions; nomer++)
    {
        for (int otvet = 0; otvet < 100; otvet++)
        {
            if (que[nomer].ans[otvet].text == nullptr)
            {
                que[nomer].count_answers = otvet;
                break;
            }
        }

        for (int otvet = 0; otvet < que[nomer].count_answers; otvet++)
        {
            //900 - ширина экрана
            int shirina_otveta = 900 / que[nomer].count_answers;

            que[nomer].ans[otvet].x1 = 125 + otvet * shirina_otveta;
            que[nomer].ans[otvet].x2 = que[nomer].ans[otvet].x1 + shirina_otveta - 250;

            que[nomer].ans[otvet].y1 = 300;
            que[nomer].ans[otvet].y2 = 490;
        }
    }

    //Рисуем вопросы
    int nomer_voprosa = 0;
    int current_time = 0;
    while (nomer_voprosa < count_questions)
    {
        txBegin();
        txSetFillColor(TX_WHITE);
        txClear();
        drawQuestion(que[nomer_voprosa]);

        txTransparentBlt (txDC(), face.x - face.width / 2, face.y - face.height / 2, face.width, face.height, face.pic, 0, 0, TX_WHITE);
        move_hero(&face);

        for (int nomer = 0; nomer < que[nomer_voprosa].count_answers; nomer++)
        {
            if (face.x >= que[nomer_voprosa].ans[nomer].x1 and
                face.x <= que[nomer_voprosa].ans[nomer].x2 and
                face.y >= que[nomer_voprosa].ans[nomer].y1 and
                face.y <= que[nomer_voprosa].ans[nomer].y2)
            {
                if (que[nomer_voprosa].ans[nomer].pravilnyi)
                {
                    kolichestvo_pravilnyh = kolichestvo_pravilnyh + 1;
                }

                nomer_voprosa = nomer_voprosa + 1;
                face.x = face.x_start;
                face.y = face.y_start;
            }
        }

        //Динозавр ест человека
        if (current_time >= 500)
        {
            int dino_x = 1500;
            int dino_y = face.y;

            while (dino_x >= face.x)
            {
                txBegin();
                txSetFillColor(TX_WHITE);
                txClear();
                txTransparentBlt (txDC(), face.x - face.width / 2, face.y - face.height / 2, face.width, face.height, face.pic, 0, 0, TX_WHITE);
                txTransparentBlt (txDC(), dino_x-100, dino_y-200, 1000, 520, dinosaur, 0, 0, TX_WHITE);

                dino_x -= 3;
                dino_y = face.y;
                txSleep(10);
                txEnd();
            }

            return 0;
        }

        txSleep(3);
        current_time += 3;
        txEnd();
    }

    //Результат
    txSetFillColor(TX_WHITE);
    txClear();

    if (kolichestvo_pravilnyh == nomer_voprosa)
    {
        txTransparentBlt (txDC(), 0, 0, 900, 600, cheburek, 0, 0, TX_WHITE);
        txSetColor(TX_YELLOW);
        txSelectFont("Arial", 50);
        txDrawText(0, 0, 800, 100, "Норм");
    }
    else if (kolichestvo_pravilnyh == 0)
    {
        txTransparentBlt (txDC(), 0, 0, 900, 600, explosion, 0, 0, TX_WHITE);
        txSetColor(TX_YELLOW);
        txSelectFont("Arial", 50);
        txDrawText(0, 0, 800, 100, "Ты идиот");
    }

    txDeleteDC(face.pic);
    txDeleteDC(iguana);
    txDeleteDC(agutin);
    txDeleteDC(hole);
    txDeleteDC(button);
    txDeleteDC(dinosaur);
    txDeleteDC(cheburek);
    txDeleteDC(explosion);

    return 0;
}
