#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define BLACK   0
#define BLUE1   1
#define GREEN1   2
#define CYAN1   3
#define RED1   4
#define MAGENTA1 5
#define YELLOW1   6
#define GRAY1   7
#define GRAY2   8
#define BLUE2   9
#define GREEN2   10
#define CYAN2   11
#define RED2   12
#define MAGENTA2 13
#define YELLOW2   14
#define WHITE   15

#define WIDTH 70
#define HEIGHT 40
#define MAX_TIME 3
#define SIZE 12

#define LEFT 0x4b
#define RIGHT 0x4d
#define ENTER 13

typedef struct {
    COORD data[SIZE];
    int  front, rear;
} QueueType;

typedef struct RECORD {
    char rank;
    int rtime;
    char name[20];
    int tryNum;
}RECORD;

void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
    return (q->front == q->rear);
}

void enqueue(QueueType* q, COORD item)
{
    q->rear = (q->rear + 1) % SIZE;
    q->data[q->rear] = item;
}

COORD dequeue(QueueType* q)
{
    q->front = (q->front + 1) % SIZE;
    return q->data[q->front];
}

COORD lastQueue(QueueType* q) 
{
    return q->data[q->rear];
}


//무한의 계단 타이틀
char infinitestair[9][70] = {
   "=================================================================",
   " _          __  _         _  _               _           _       ",
   "(_)        / _|(_)       (_)| |             | |         (_)      ",
   " _  _ __  | |_  _  _ __   _ | |_   ___  ___ | |_   __ _  _  _ __ ",
   "| || '_ \\ |  _|| || '_ \\ | || __| / _ \\/ __|| __| / _` || || '__|",
   "| || | | || |  | || | | || || |_ |  __/\\__ \\| |_ | (_| || || | ",
   "|_||_| |_||_|  |_||_| |_||_| \\__| \\___||___/ \\__| \\__,_||_||_|",
   "                                                                 ",
   "=================================================================" };

//캐릭터
char player[21][15] = {
   "     :###     ",
   "    ~#####    ",
   "    :#####.   ",
   "     =###:    ",
   "      -:,     ",
   "      ~$;     ",
   "    ~####=,   ",
   "    ####$#=.  ",
   "   # #### ;##,",
   " .#  ####  ,##",
   "~#   ;###     ",
   "      ###     ",
   "     :###*,   ",
   "      ####$   ",
   "      ##*$$*  ",
   "    .##   #=! ",
   "    ;##   =#  ",
   "    ##    ### ",
   "   ##;        ",
   " .##,         ",
   " .###          " };

//계단
char block[3][9] = {
   "-------:",
   "::::::: ",
   "::::::: ",
};

//숫자
int number[10][20] = {
    { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1 } };

void cls(int text_color, int bg_color)
{
    char cmd[100];
    system("cls");
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}

void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void removeCursor(void)
{
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//계단 부분 클리어
void clear()
{
    for (int i = 0; i < HEIGHT - 9; i++) {
        gotoxy(0, 9 + i);
        printf("                                                                      ");
    }
}

//계단 그리기
void printStair(int m, int n)
{
    COORD pos;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 8; x++) {
            pos.X = m * 9 + x;
            pos.Y = n * 3 + y + 1;
            if (pos.X < 0 || pos.X >= WIDTH || pos.Y < 0 || pos.Y >= HEIGHT)
                continue;//화면 범위를 벗어나면 넘어감
            gotoxy(pos.X, pos.Y);
            textcolor(GRAY1, BLACK);
            if (block[y][x] != ' ')//빈칸이면 출력하지 않는다
                printf("%c", block[y][x]);
        }
}

//플레이어 그리기
void printPlayer(int reverse)
{
    COORD pos;
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 15; x++) {
            pos.X = 29 + x;
            pos.Y = 13 + y;
            gotoxy(pos.X, pos.Y);
            textcolor(YELLOW2, BLACK);
            if (reverse) { //거꾸로 출력하기
                if (player[y][14 - x] != ' ')//빈칸이면 출력하지 않는다
                    printf("%c", player[y][14 - x]);
            }
            else {
                if (player[y][x] != ' ')
                    printf("%c", player[y][x]);
            }
        }
    }
}

//플레이어 떨어짐
void fall(int reverse)
{
    COORD pos;
    for (int i = 0; i < 40; i++) {
        clear();//클리어
        for (int y = 0; y < 21; y++) {
            for (int x = 0; x < 15; x++) {
                pos.X = 29 + x;
                pos.Y = 13 + y + i;//한칸씩 내려가면서 출력
                if (pos.X < 0 || pos.X >= WIDTH || pos.Y < 0 || pos.Y >= HEIGHT)
                    continue; //화면 범위 벗어나면 넘어감
                gotoxy(pos.X, pos.Y);
                textcolor(YELLOW2, BLACK);
                if (reverse) { //거꾸로 출력
                    if (player[y][14 - x] != ' ') //빈칸이면 출력안함
                        printf("%c", player[y][14 - x]);
                }
                else {
                    if (player[y][x] != ' ')
                        printf("%c", player[y][x]);
                }
            }
        }
        Sleep(10);
    }
}

//타이머 출력
void printTimeBar(time_t time)
{
    gotoxy(2, 1);
    textcolor(RED1, BLACK);
    int n = WIDTH / 6 * time / CLOCKS_PER_SEC;
    for (int i = 0; i < WIDTH / 6 * MAX_TIME - n - 2; i++)
        printf("■");
    for (int i = 0; i < n; i++)
        printf("  ");
}

//점수 출력
void printNumber(int num, int x, int y) {
    COORD pos;
    textcolor(WHITE, BLACK);
    for (int i = 0; i < 20; i++)
        if (number[num][i] == 1) {
            pos.X = i % 4 * 2 + x;
            pos.Y = i / 4 + y;
            gotoxy(pos.X, pos.Y);
            printf("■");
        }
}

//점수 자릿수 나누기 
void printStep(int num)
{
    int n[5];
    int digits = 0;
    n[0] = num / 10000;
    n[1] = (num % 10000) / 1000;
    n[2] = (num % 1000) / 100;
    n[3] = (num % 100) / 10;
    n[4] = (num % 10) / 1;
    for (int i = 0; i < 5; i++) {
        if (digits == 0)
            if (n[i] == 0)
                continue;
        digits++;
    }
    for (int i = 0; i < 5; i++) {
        gotoxy(0, 3 + i);
        printf("                                                                      ");
    }
    for (int i = 0; i < digits; i++)
        printNumber(n[4 - i], (WIDTH - digits * 10) / 2 + 10 * (digits - i - 1), 3);
}
 //게임오버 화면
void printEnd(score)
{
    char name[100];

    cls(WHITE, BLACK);
    gotoxy(34, 9);
    printf("GOOD JOB!! YOU SCORE IS...!!");
    textcolor(WHITE, BLACK);
    gotoxy(35, 12);
    printf("Your Name? : ");
    scanf("%s", &name);

    gotoxy(33, 16);
    printf("----------------YOUR RANK-----------------\n");
    gotoxy(38, 18);
    printf("NAME : %s, SCORE : %d\n", &name, score);
    gotoxy(43, 30);
    printf("****GAMEOVER*****");
    _getch();
    exit(1);
}

//초기화면
void printMain()
{
    char ch;
    textcolor(WHITE, BLACK);

    for (int y = 0; y < 9; y++)
        for (int x = 0; x < 70; x++) {
            gotoxy(x + 2, y + 2);
            printf("%c", infinitestair[y][x]);
        }
    for (int i = 0; i < 8; i++)
        printStair(i, 14 - i);
    printPlayer(0);

    for (int i = 1;; i++) {
        textcolor(i, BLACK);
        if (i > 14) i = 1;
        gotoxy((WIDTH - 24) / 2, HEIGHT / 3 * 2);
        printf("PRESS ENTER KEY TO START");
        if (_kbhit()) {
            ch = _getch();
            if (ch == 13)
                return;
        }
        Sleep(100);
    }
}

//계단 큐를 출력한다
void printQueueStair(QueueType* q)
{
    int i = q->front;
    do {
        i = (i + 1) % (SIZE);
        printStair(q->data[i].X, q->data[i].Y);
        if (i == q->rear)
            break;
    } while (i != q->front);
}

//랜덤하게 계단 생성
void randomStair(QueueType* q)
{
    COORD pos = lastQueue(q);
    if (rand() % 2)
        pos.X--;
    else
        pos.X++;
    pos.Y = 3;
    enqueue(q, pos);
}

//현재 계단의 x 값 리턴
int currentStair(QueueType* q)
{
    return q->data[(q->front + 3) % SIZE].X;
}

//왼쪽으로 이동
void moveLeft(QueueType* q)
{
    int i = q->front;
    do {
        i = (i + 1) % (SIZE);
        q->data[i].X++;//계단을 오른쪽으로 옮기기
        q->data[i].Y++;
        if (i == q->rear)
            break;
    } while (i != q->front);
    i = q->front;
    if (currentStair(q) == 4)//반대방향 이동이면
        do {
            i = (i + 1) % (SIZE);
            q->data[i].X--;
            if (i == q->rear)
                break;
        } while (i != q->front);
}

//오른쪽으로 이동
void moveRight(QueueType* q)
{
    int i = q->front;
    do {
        i = (i + 1) % (SIZE);
        q->data[i].X--;//계단을 왼쪽으로 옮기기
        q->data[i].Y++;
        if (i == q->rear)
            break;
    } while (i != q->front);
    i = q->front;
    if (currentStair(q) == 3)//반대 방향으로 이동
        do {
            i = (i + 1) % (SIZE);
            q->data[i].X++;
            if (i == q->rear)
                break;
        } while (i != q->front);
}

// 게임 시작
int startGame()
{
    clock_t start, now;
    int timer;
    int step = 1;
    char ch;
    QueueType q;
    COORD pos;

    textcolor(WHITE, BLACK);
    cls(WHITE, BLACK);
    init_queue(&q); // 큐 생성

    // 초기 계단 설정
    for (int i = 0; i < 10; i++) {
        pos.X = i + 2;
        pos.Y = 12 - i;
        enqueue(&q, pos);
    }

    // 캐릭터와 계단 출력
    printQueueStair(&q);
    printPlayer(0);

    srand(time(NULL));
    start = clock();
    while (1) {
        if (_kbhit()) {
            ch = _getch();
            switch (ch) {
            case 75: // LEFT 키
                start = clock();
                clear();
                dequeue(&q);
                moveLeft(&q);
                randomStair(&q);
                printQueueStair(&q);
                printPlayer(1);
                if (currentStair(&q) != 3) { // 잘못 입력한 경우
                    fall(1);
                    return step;
                }
                printStep(step++);
                break;
            case 77: // RIGHT 키 입력
                start = clock();
                clear();
                dequeue(&q);
                moveRight(&q);
                randomStair(&q);
                printQueueStair(&q);
                printPlayer(0);
                if (currentStair(&q) != 4) { // 잘못 입력한 경우
                    fall(0);
                    return step;
                }
                printStep(step++);
                break;
            }
        }
        // 타이머
        now = clock() - start;
        timer = MAX_TIME - (now / CLOCKS_PER_SEC);
        if (timer < 1) return step;
        printTimeBar(now); // 타이머 출력
        Sleep(1);
    }
}

// 도움말
void draw_help()
{
    system("cls");
    textcolor(WHITE, BLACK);
    gotoxy(15, 8);
    printf("-------------HOW TO PLAY----------");
    gotoxy(15, 10);
    printf("무한의 계단은 버튼을 눌러 계단을 올라가는 간단한 아케이드 게임입니다.");
    gotoxy(15, 13);
    printf("여러분의 빠른 손가락과 판단력으로 끝 없이 펼쳐진 계단의 정상에 올라보세요!");
    gotoxy(15, 16);
    printf("열심히 오르다보면 집중력이 쑥쑥!! 손가락도 튼튼!!");
    gotoxy(15, 18);
    printf("화면에 뜨는 무한의 계단을 보고");
    gotoxy(15, 20);
    printf("왼쪽으로 올라가고 싶으면 방향기 <- ");
    gotoxy(15, 22);
    printf("오른쪽으로 올라가고 싶으면 방향기 -> ");
    gotoxy(15, 24);
    printf("타이머 시간 안에 올라가야 합니다!");
    gotoxy(15, 26);
    printf("방향키를 잘못 누르거나 시간 안에 계단을 오르지 못하면");
    gotoxy(15, 28);
    printf("GAME OVER...");
    gotoxy(15, 30);
    printf("!!!!!!!게임 시작 준비 됫으면 ENTER 클릭!!!!!!");
    gotoxy(15, 33);
    printf("2171335 박시현");
    _getch();
    system("cls");
}

// 메인 함수
int main(void)
{
    int score;
    cls(WHITE, BLACK);
    removeCursor(); // 커서 지우기

    printMain();
    system("cls");
    draw_help();

    score = startGame();
    printEnd(score);

    system("cls");
    gotoxy(10, 30);
    printf("GAME OUT!!\n");
}