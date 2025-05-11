#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <time.h>
/*
    console screen size 960x480
*/
#define PIPES 50
#define MINPIPESIZE 50
#define PIPEWIDTH 60
#define PIPEYDISTANCE 80
#define PIPEXDISTANCE 150
#define SCREENY 480
#define SCREENX 960
#define PIXELMINUSATFRAME 3



typedef struct {
    int x;
    int topPipeY;
    int botPipeY;
} Pipe;

Pipe pipe[PIPES];

void pipeset(){
    srand(time(NULL));
    for(int i = 0; i < PIPES; i++){
        pipe[i].topPipeY = rand() % (SCREENY - MINPIPESIZE + 1);
        pipe[i].botPipeY = pipe[i].topPipeY + PIPEYDISTANCE;
    }
    pipe[0].x = SCREENX;
    for(int i = 1; i < PIPES; i++){
        pipe[i].x = pipe[i-1].x + PIPEWIDTH + PIPEXDISTANCE;
    }
}

void test(){
    for(int i = 0; i < 50; i++){
        printf("pipe num: %d; x: %d; topPipeY: %d; botPipeY: %d\n", i, pipe[i].x, pipe[i].topPipeY, pipe[i].botPipeY);
    }
}

void piperender(HDC dc){
    for(int i = 0; i < PIPES; i++){
        if(pipe[i].x < 1100 && pipe[i].x > -40)
        {
            Rectangle(dc, pipe[i].x, 0, pipe[i].x + PIPEWIDTH, pipe[i].topPipeY);
            Rectangle(dc, pipe[i].x, pipe[i].topPipeY + PIPEYDISTANCE, pipe[i].x + PIPEWIDTH, SCREENY);
        }
        pipe[i].x -= PIXELMINUSATFRAME;
    }
}

void resetframe(HDC bgc){
    Rectangle(bgc, 0, 0, SCREENX, SCREENY);
}

int main() {
    ///////////////////////////////////////////////////////////////////////////////
    HWND hwnd = GetConsoleWindow();
    HDC dc = GetDC(hwnd);
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc,RGB(84, 255, 64));

    HDC bgc = GetDC(hwnd);
    SelectObject(bgc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(bgc,RGB(64, 171, 255));
    ///////////////////////////////////////////////////////////////////////////////
    pipeset();
    
    while(1){
        piperender(dc);
        Sleep(16);
        resetframe(bgc);
    }
    ReleaseDC(hwnd, dc);

    return 0;
}