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

coordinates snake_head; // its simpler to separate the head from the tail
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
    printf("input cols: "); // width
    scanf("%d", &cols);
    printf("input rows: "); // height
    scanf("%d", &rows);

    board = (char **)malloc(rows * sizeof(char *));
    for (size_t i = 0; i < rows; i++)
    {
        board[i] = (char *)malloc(cols * sizeof(char));
    }

    // scanf board
    for (size_t i = 0; i < rows; i++) // height
    {
        for (size_t j = 0; j < cols; j++) // width
        {
            scanf("%c", &board[i][j]);
        }
    }
}

// Function to draw the boundaries
void draw()
{
    system("clear");
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%c ", board[i][j]);
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
    return;

    // Until the game is over
    while (!gameover)
    {

        // Function Calls
        draw();
        input();
        logic();
    }

    free_memory();
}
