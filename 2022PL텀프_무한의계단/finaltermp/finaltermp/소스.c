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


//������ ��� Ÿ��Ʋ
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

//ĳ����
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

//���
char block[3][9] = {
   "-------:",
   "::::::: ",
   "::::::: ",
};

//����
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
//��� �κ� Ŭ����
void clear()
{
    for (int i = 0; i < HEIGHT - 9; i++) {
        gotoxy(0, 9 + i);
        printf("                                                                      ");
    }
}

//��� �׸���
void printStair(int m, int n)
{
    COORD pos;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 8; x++) {
            pos.X = m * 9 + x;
            pos.Y = n * 3 + y + 1;
            if (pos.X < 0 || pos.X >= WIDTH || pos.Y < 0 || pos.Y >= HEIGHT)
                continue;//ȭ�� ������ ����� �Ѿ
            gotoxy(pos.X, pos.Y);
            textcolor(GRAY1, BLACK);
            if (block[y][x] != ' ')//��ĭ�̸� ������� �ʴ´�
                printf("%c", block[y][x]);
        }
}

//�÷��̾� �׸���
void printPlayer(int reverse)
{
    COORD pos;
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 15; x++) {
            pos.X = 29 + x;
            pos.Y = 13 + y;
            gotoxy(pos.X, pos.Y);
            textcolor(YELLOW2, BLACK);
            if (reverse) { //�Ųٷ� ����ϱ�
                if (player[y][14 - x] != ' ')//��ĭ�̸� ������� �ʴ´�
                    printf("%c", player[y][14 - x]);
            }
            else {
                if (player[y][x] != ' ')
                    printf("%c", player[y][x]);
            }
        }
    }
}

//�÷��̾� ������
void fall(int reverse)
{
    COORD pos;
    for (int i = 0; i < 40; i++) {
        clear();//Ŭ����
        for (int y = 0; y < 21; y++) {
            for (int x = 0; x < 15; x++) {
                pos.X = 29 + x;
                pos.Y = 13 + y + i;//��ĭ�� �������鼭 ���
                if (pos.X < 0 || pos.X >= WIDTH || pos.Y < 0 || pos.Y >= HEIGHT)
                    continue; //ȭ�� ���� ����� �Ѿ
                gotoxy(pos.X, pos.Y);
                textcolor(YELLOW2, BLACK);
                if (reverse) { //�Ųٷ� ���
                    if (player[y][14 - x] != ' ') //��ĭ�̸� ��¾���
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

//Ÿ�̸� ���
void printTimeBar(time_t time)
{
    gotoxy(2, 1);
    textcolor(RED1, BLACK);
    int n = WIDTH / 6 * time / CLOCKS_PER_SEC;
    for (int i = 0; i < WIDTH / 6 * MAX_TIME - n - 2; i++)
        printf("��");
    for (int i = 0; i < n; i++)
        printf("  ");
}

//���� ���
void printNumber(int num, int x, int y) {
    COORD pos;
    textcolor(WHITE, BLACK);
    for (int i = 0; i < 20; i++)
        if (number[num][i] == 1) {
            pos.X = i % 4 * 2 + x;
            pos.Y = i / 4 + y;
            gotoxy(pos.X, pos.Y);
            printf("��");
        }
}

//���� �ڸ��� ������ 
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
 //���ӿ��� ȭ��
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

//�ʱ�ȭ��
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

//��� ť�� ����Ѵ�
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

//�����ϰ� ��� ����
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

//���� ����� x �� ����
int currentStair(QueueType* q)
{
    return q->data[(q->front + 3) % SIZE].X;
}

//�������� �̵�
void moveLeft(QueueType* q)
{
    int i = q->front;
    do {
        i = (i + 1) % (SIZE);
        q->data[i].X++;//����� ���������� �ű��
        q->data[i].Y++;
        if (i == q->rear)
            break;
    } while (i != q->front);
    i = q->front;
    if (currentStair(q) == 4)//�ݴ���� �̵��̸�
        do {
            i = (i + 1) % (SIZE);
            q->data[i].X--;
            if (i == q->rear)
                break;
        } while (i != q->front);
}

//���������� �̵�
void moveRight(QueueType* q)
{
    int i = q->front;
    do {
        i = (i + 1) % (SIZE);
        q->data[i].X--;//����� �������� �ű��
        q->data[i].Y++;
        if (i == q->rear)
            break;
    } while (i != q->front);
    i = q->front;
    if (currentStair(q) == 3)//�ݴ� �������� �̵�
        do {
            i = (i + 1) % (SIZE);
            q->data[i].X++;
            if (i == q->rear)
                break;
        } while (i != q->front);
}

// ���� ����
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
    init_queue(&q); // ť ����

    // �ʱ� ��� ����
    for (int i = 0; i < 10; i++) {
        pos.X = i + 2;
        pos.Y = 12 - i;
        enqueue(&q, pos);
    }

    // ĳ���Ϳ� ��� ���
    printQueueStair(&q);
    printPlayer(0);

    srand(time(NULL));
    start = clock();
    while (1) {
        if (_kbhit()) {
            ch = _getch();
            switch (ch) {
            case 75: // LEFT Ű
                start = clock();
                clear();
                dequeue(&q);
                moveLeft(&q);
                randomStair(&q);
                printQueueStair(&q);
                printPlayer(1);
                if (currentStair(&q) != 3) { // �߸� �Է��� ���
                    fall(1);
                    return step;
                }
                printStep(step++);
                break;
            case 77: // RIGHT Ű �Է�
                start = clock();
                clear();
                dequeue(&q);
                moveRight(&q);
                randomStair(&q);
                printQueueStair(&q);
                printPlayer(0);
                if (currentStair(&q) != 4) { // �߸� �Է��� ���
                    fall(0);
                    return step;
                }
                printStep(step++);
                break;
            }
        }
        // Ÿ�̸�
        now = clock() - start;
        timer = MAX_TIME - (now / CLOCKS_PER_SEC);
        if (timer < 1) return step;
        printTimeBar(now); // Ÿ�̸� ���
        Sleep(1);
    }
}

// ����
void draw_help()
{
    system("cls");
    textcolor(WHITE, BLACK);
    gotoxy(15, 8);
    printf("-------------HOW TO PLAY----------");
    gotoxy(15, 10);
    printf("������ ����� ��ư�� ���� ����� �ö󰡴� ������ �����̵� �����Դϴ�.");
    gotoxy(15, 13);
    printf("�������� ���� �հ����� �Ǵܷ����� �� ���� ������ ����� ���� �ö󺸼���!");
    gotoxy(15, 16);
    printf("������ �����ٺ��� ���߷��� ����!! �հ����� ưư!!");
    gotoxy(15, 18);
    printf("ȭ�鿡 �ߴ� ������ ����� ����");
    gotoxy(15, 20);
    printf("�������� �ö󰡰� ������ ����� <- ");
    gotoxy(15, 22);
    printf("���������� �ö󰡰� ������ ����� -> ");
    gotoxy(15, 24);
    printf("Ÿ�̸� �ð� �ȿ� �ö󰡾� �մϴ�!");
    gotoxy(15, 26);
    printf("����Ű�� �߸� �����ų� �ð� �ȿ� ����� ������ ���ϸ�");
    gotoxy(15, 28);
    printf("GAME OVER...");
    gotoxy(15, 30);
    printf("!!!!!!!���� ���� �غ� ������ ENTER Ŭ��!!!!!!");
    gotoxy(15, 33);
    printf("2171335 �ڽ���");
    _getch();
    system("cls");
}

// ���� �Լ�
int main(void)
{
    int score;
    cls(WHITE, BLACK);
    removeCursor(); // Ŀ�� �����

    printMain();
    system("cls");
    draw_help();

    score = startGame();
    printEnd(score);

    system("cls");
    gotoxy(10, 30);
    printf("GAME OUT!!\n");
}