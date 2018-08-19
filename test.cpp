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

    HDC black_hole = txLoadImage("Черная дыра.bmp");
    HDC jaguar = txLoadImage("ягуар.bmp");
    Hero face = {450, 600, 450, 600, 169, 200, 4, txLoadImage("Лицо.bmp")};

    //Заполняем вопросы нормально
    {
    que[count_questions++] = {"Куда ты прыгнешь?",
        {{"", true, black_hole},
         {"", false, black_hole}},
        jaguar
    };
    que[count_questions++] = {"Это невопрос. Все ответы правильные",
        {{"Это ответ1", true},
         {"Это ответ2", true}}
    };
    que[count_questions++] = {"Выберите число",
        {{"2", true},
         {"Вася", false}}
    };
    que[count_questions++] = {"Выберите число",
        {{"2", true},
         {"15", true}}
    };
    }


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

            que[nomer].ans[otvet].x1 = 100 + otvet * shirina_otveta;
            que[nomer].ans[otvet].x2 = que[nomer].ans[otvet].x1 + shirina_otveta - 200;

            que[nomer].ans[otvet].y1 = 300;
            que[nomer].ans[otvet].y2 = 500;
        }
    }

    //Рисуем вопросы
    int nomer_voprosa = 0;
    while (nomer_voprosa < count_questions)
    {
        txBegin();
        txSetFillColor(TX_BLACK);
        txClear();
        drawQuestion(que[nomer_voprosa]);

        txTransparentBlt (txDC(), face.x - face.width / 2, face.y - face.height / 2, face.width, face.height, face.pic, 0, 0, TX_WHITE);

        move_hero(&face);


        sprintf(stroka_dlya_kolichestvo_pravilnyh,
            "Количество правильных ответов %d из %d",
            kolichestvo_pravilnyh,
            nomer_voprosa);
        txTextOut(30, 100, stroka_dlya_kolichestvo_pravilnyh);

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

        txSleep(3);
        txEnd();
    }

    //Результат
    {
    txSetFillColor(TX_BLACK);
    txClear();
    sprintf(stroka_dlya_kolichestvo_pravilnyh,
        "Количество правильных ответов %d из %d",
        kolichestvo_pravilnyh,
        nomer_voprosa);
    txTextOut(30, 100, stroka_dlya_kolichestvo_pravilnyh);

    if ((100 * kolichestvo_pravilnyh) / nomer_voprosa > 80)
    {
        txTextOut(30, 400, "Вы гений");
    }
    else
    {
        txTextOut(30, 400, "Вы идиот");
    }
    }

    txDeleteDC(face.pic);
    txDeleteDC(jaguar);
    txDeleteDC(black_hole);

    return 0;
}
