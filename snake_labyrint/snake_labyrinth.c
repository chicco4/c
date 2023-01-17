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

    // init board
    board = (char **)malloc(rows * sizeof(char *));
    for (size_t i = 0; i < rows; i++)
    {
        board[i] = (char *)malloc(cols * sizeof(char));
    }
    // FIXME should be remade every time init snake_tail
    snake_tail = (coordinates *)malloc(100 * sizeof(coordinates));

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
            // setup snake_head
            if (tmp == 'o')
            {
                snake_head.i = i;
                snake_head.j = j;
            }
        }
    }
}

// function for the logic behind each movement
void logic()
{
    int moving = 0;
    coordinates tmp = snake_head;

    // move snake_head
    switch (direction)
    {
    case 1: /* N */
        board[snake_head.i][snake_head.j] = ' ';
        snake_head.i--;
        moving = 1;
        break;
    case 2: /* S */
        board[snake_head.i][snake_head.j] = ' ';
        snake_head.i++;
        moving = 1;
        break;
    case 3: /* O */
        board[snake_head.i][snake_head.j] = ' ';
        snake_head.j--;
        moving = 1;
        break;
    case 4: /* E */
        board[snake_head.i][snake_head.j] = ' ';
        snake_head.j++;
        moving = 1;
        break;
    default:
        break;
    }
    direction = 0;

    board[snake_head.i][snake_head.j] = 'o';

    // if snake reaches the fruit
    // if (snake_head.i == fruit.i && snake_head.j == fruit.j)
    // {
    //     // update score
    //     score++;

    //     // add tail
    //     tail_lenght++;
    // }

    // if snake is moving
    if (moving && tail_lenght > 0)
    {
        // slide tail
        for (size_t i = tail_lenght - 1; i > 0; i--)
        {
            snake_tail[i] = snake_tail[i - 1];
        }
        snake_tail[0] = tmp;
    }

    // check collision with borders
    // if (snake_head.i == 0 || snake_head.i == rows - 1 || snake_head.j == 0 || snake_head.j == cols - 1)
    // {
    //     gameover = 1;
    // }

    // check collision with snake_tail
    for (size_t i = 0; i < tail_lenght; i++)
    {
        if (snake_head.i == snake_tail[i].i && snake_head.j == snake_tail[i].j)
        {
            gameover = 1;
        }
    }
}

// refresh the board and draw it
void draw()
{
    system("clear");
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    // print the score after the game ends
    printf("score = %d\n", score);
    printf("press x to quit the game\n");
}

// function to take the input
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

// free the matrix
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

    // until the game is over
    while (!gameover)
    {
        draw();
        input();
        logic();
    }

    free_memory();
}
