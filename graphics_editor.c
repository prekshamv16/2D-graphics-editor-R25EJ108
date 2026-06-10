#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

/* Function Prototypes */
void initCanvas();
void displayCanvas();

void drawRectangle(int x, int y, int w, int h);
void drawLine(int x1, int y1, int x2, int y2);
void drawTriangle(int x, int y, int h);
void drawCircle(int xc, int yc, int r);

void deleteArea(int x1, int y1, int x2, int y2);

/* ---------------- MAIN ---------------- */
int main()
{
    int choice;

    initCanvas();

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Delete Area\n");
        printf("6. Display Canvas\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 0)
            break;

        int x, y, x1, y1, x2, y2, w, h, r;

        switch(choice)
        {
            case 1:
                printf("Enter x y width height: ");
                scanf("%d%d%d%d", &x, &y, &w, &h);
                drawRectangle(x, y, w, h);
                break;

            case 2:
                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                drawLine(x1, y1, x2, y2);
                break;

            case 3:
                printf("Enter x y height: ");
                scanf("%d%d%d", &x, &y, &h);
                drawTriangle(x, y, h);
                break;

            case 4:
                printf("Enter center_x center_y radius: ");
                scanf("%d%d%d", &x, &y, &r);
                drawCircle(x, y, r);
                break;

            case 5:
                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                deleteArea(x1, y1, x2, y2);
                break;

            case 6:
                displayCanvas();
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

/* ---------------- INIT ---------------- */
void initCanvas()
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}

/* ---------------- DISPLAY ---------------- */
void displayCanvas()
{
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

/* ---------------- RECTANGLE ---------------- */
void drawRectangle(int x, int y, int w, int h)
{
    for(int i = y; i < y + h && i < ROWS; i++)
    {
        for(int j = x; j < x + w && j < COLS; j++)
        {
            if(i == y || i == y + h - 1 || j == x || j == x + w - 1)
                canvas[i][j] = '*';
        }
    }
}

/* ---------------- LINE (BRESENHAM) ---------------- */
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        if(x1 >= 0 && x1 < COLS && y1 >= 0 && y1 < ROWS)
            canvas[y1][x1] = '*';

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

/* ---------------- TRIANGLE ---------------- */
void drawTriangle(int x, int y, int h)
{
    for(int i = 0; i < h; i++)
    {
        if(y + i < ROWS)
        {
            if(x - i >= 0)
                canvas[y + i][x - i] = '*';

            if(x + i < COLS)
                canvas[y + i][x + i] = '*';
        }
    }

    drawLine(x - h + 1, y + h - 1,
             x + h - 1, y + h - 1);
}

/* ---------------- CIRCLE ---------------- */
void drawCircle(int xc, int yc, int r)
{
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLS; x++)
        {
            int dx = x - xc;
            int dy = y - yc;

            double d = sqrt(dx*dx + dy*dy);

            if(d >= r - 0.5 && d <= r + 0.5)
                canvas[y][x] = '*';
        }
    }
}

/* ---------------- DELETE ---------------- */
void deleteArea(int x1, int y1, int x2, int y2)
{
    for(int i = y1; i <= y2 && i < ROWS; i++)
    {
        for(int j = x1; j <= x2 && j < COLS; j++)
        {
            if(i >= 0 && j >= 0)
                canvas[i][j] = '_';
        }
    }
}