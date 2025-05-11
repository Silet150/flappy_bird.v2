#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
/*
    console screen size 960x480
*/
#define PIPES 50
#define MINPIPESIZE 50
#define PIPEWIDTH 60
#define PIPEYDISTANCE 100
#define PIPEXDISTANCE 150
#define SCREENY 480
#define SCREENX 960
#define PIXELMINUSATFRAME 3
#define BIRDHEIGHT 36
#define BIRDWIDTH 50

typedef struct{
    int x;
    int y;
} Bird;

typedef struct {
    float vel;
    float grav;
    float jumpP;
} Psx;

Psx psx = {0,2,-10};

Bird bird = {200, 200};

typedef struct {
    int x;
    int topPipeY;
    int botPipeY;
} Pipe;

Pipe pipe[PIPES];

int c = 0;

void birdrender(HDC brd){
    SetDCBrushColor(brd, RGB(255, 255, 0));
    Ellipse(brd, bird.x,bird.y, bird.x + BIRDWIDTH, bird.y + BIRDHEIGHT);
    //beak
    SetDCBrushColor(brd, RGB(255, 0, 0));
    Ellipse(brd, bird.x + 30 ,bird.y + 15, bird.x + 60, bird.y + 30);
    //eye
    SetDCBrushColor(brd, RGB(255, 255, 255));
    Ellipse(brd, bird.x + 35 ,bird.y + 5, bird.x + 50, bird.y + 15);
    //pupil
    SetDCBrushColor(brd, RGB(0, 0, 0));
    Ellipse(brd, bird.x + 43 ,bird.y + 8, bird.x + 49, bird.y + 11);
}

void birdphysix(bool isjump){
    if(isjump){
        psx.vel = psx.jumpP;
    }
    else{
        psx.vel += psx.grav;
    }
    bird.y += (int)psx.vel;
}

void pipeset(){
    srand(time(NULL));
    for(int i = 0; i < PIPES; i++){
        pipe[i].topPipeY = rand() % (SCREENY - MINPIPESIZE + 1);
        pipe[i].botPipeY = pipe[i].topPipeY + PIPEYDISTANCE - MINPIPESIZE;
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

void chek(){
    
}

int main() {
    ///////////////////////////////////////////////////////////////////////////////
    //pipes
    HWND hwnd = GetConsoleWindow();
    HDC dc = GetDC(hwnd);
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc,RGB(84, 255, 64));
    ///////////////////////////////////////////////////////////////////////////////
    //background
    HDC bgc = GetDC(hwnd);
    SelectObject(bgc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(bgc,RGB(64, 171, 255));
    ///////////////////////////////////////////////////////////////////////////////
    //bird
    HDC brd = GetDC(hwnd);
    SelectObject(brd, GetStockObject(DC_BRUSH));
    SetDCBrushColor(brd, RGB(255, 255, 0));
    ///////////////////////////////////////////////////////////////////////////////
    pipeset();

    for(int i = 3; i > 0; i--){
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("                                                        start: %d", i);
        Sleep(1000);
        system("cls");
    }
    while(1){
        piperender(dc);
        if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState('W') & 0x8000) {
            birdphysix(true);
        }   
        else birdphysix(false);
        birdrender(brd);
        Sleep(16);
        resetframe(bgc);
    }
    ReleaseDC(hwnd, dc);

    return 0;
}