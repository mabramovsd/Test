struct Answer
{
    //Обязательные
    const char* text;
    bool pravilnyi;
    //Необязательные
    HDC pic;
    int x1;
    int y1;
    int x2;
    int y2;
};

void drawAnswer(Answer ans)
{
    if (ans.pic != nullptr)
    {
        txTransparentBlt (txDC(), ans.x1, ans.y1, ans.x2 - ans.x1, ans.y2 - ans.y1, ans.pic, 0, 0, TX_WHITE);
    }
    else
    {
        txSetFillColor(TX_RED);
        txRectangle(ans.x1, ans.y1, ans.x2, ans.y2);
    }
    txDrawText(ans.x1, ans.y1, ans.x2, ans.y2, ans.text);
}

struct Question
{
    //Обязательные
    const char* text;
    Answer ans[100];
    //Необязательные
    HDC pic;
    int count_answers;
};

void drawQuestion(Question que)
{
    if (que.pic != nullptr)
    {
        txTransparentBlt (txDC(), 0, 0, txGetExtentX(), txGetExtentY(), que.pic, 0, 0, TX_WHITE);
    }
    else
    {
        txSetFillColor(TX_RED);
        txRectangle(100, 0, 800, 100);
    }
    txDrawText(100, 0, 800, 100, que.text);

    for (int nomer = 0; nomer < que.count_answers; nomer++)
    {
        drawAnswer(que.ans[nomer]);
    }
}
