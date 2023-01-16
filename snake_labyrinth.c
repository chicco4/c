#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rows, cols, gameover, score, direction, tail_lenght, drill_usages;
char **board;

typedef struct
{
    int i;
    int j;
} coordinates;

coordinates snake_head;
coordinates *snake_tail;
coordinates *coins;
coordinates *drill;
coordinates *traps;

// in setup scanf rows of labyrinth
void setup()
{
    gameover = 0;
    score = 0;
    tail_lenght = 0;
    drill_usages = 0;

    system("clear");
    // printf("input cols: "); // width
    scanf("%d", &cols);
    // printf("input rows: "); // height
    scanf("%d", &rows);

    board = (char **)malloc(rows * sizeof(char *));
    for (size_t i = 0; i < rows; i++)
    {
        board[i] = (char *)malloc(cols * sizeof(char));
    }

    // scanf board
    // printf("input board:\n");
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            char tmp = getchar();
            while (tmp == '\n')
            {
                tmp = getchar();
            }
            board[i][j] = tmp;
        }
    }
}

// Function to draw the boundaries
void draw()
{
    // system("clear");
    printf("\nboard:\n");
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

// Function for the logic behind each movement
void logic()
{
    // FIXME dovrei ciclare tutte le coordinate e farle andare verso sinistra
    switch (direction)
    {
    case 1: /* N */
        break;
    case 2: /* S */
        break;
    case 3: /* O */
        break;
    case 4: /* E */
        break;
    default:
        break;
    }

    direction = 0;
}

// Function to take the input
void input()
{
    switch (getchar())
    {
    case 'w': /* N */
        direction = 1;
        break;
    case 's': /* S */
        direction = 2;
        break;
    case 'a': /* O */
        direction = 3;
        break;
    case 'd': /* E */
        direction = 4;
        break;
    case 'x':
        gameover = 1;
        break;
    }
}

void free_memory()
{
    for (int i = 0; i < rows; i++)
    {
        free(board[i]);
    }
    free(board);
}

void main()
{
    setup();
    draw();
}
