#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 10
#define WIDTH 20

int gameover, score, direction, tail_lenght;
char board[HEIGHT][WIDTH];

typedef struct
{
    int i;
    int j;
} coordinates;

coordinates snake_head;
coordinates snake_tail[HEIGHT * WIDTH];
coordinates fruit;

void setup()
{
    srand(time(NULL));
    gameover = 0;
    score = 0;

    // adding fruit to the board
    fruit.i = (rand() % (HEIGHT - 2)) + 1;
    fruit.j = (rand() % (WIDTH - 2)) + 1;

    // adding snake to the board
    snake_head.i = HEIGHT / 2;
    snake_head.j = WIDTH / 2;

    // setup tail
    tail_lenght = 0;
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
        snake_head.i--;
        moving = 1;
        break;
    case 2: /* S */
        snake_head.i++;
        moving = 1;
        break;
    case 3: /* O */
        snake_head.j--;
        moving = 1;
        break;
    case 4: /* E */
        snake_head.j++;
        moving = 1;
        break;
    default:
        break;
    }
    direction = 0;

    // check collision with borders
    if (snake_head.i == 0 || snake_head.i == HEIGHT - 1 || snake_head.j == 0 || snake_head.j == WIDTH - 1)
    {
        gameover = 1;
    }

    // check collision with snake_tail
    for (size_t i = 0; i < tail_lenght; i++)
    {
        if (snake_head.i == snake_tail[i].i && snake_head.j == snake_tail[i].j)
        {
            gameover = 1;
        }
    }

    // If snake reaches the fruit
    if (snake_head.i == fruit.i && snake_head.j == fruit.j)
    {
        // update score
        score++;

        // spawn new fruit
        fruit.i = (rand() % (HEIGHT - 2)) + 1;
        fruit.j = (rand() % (WIDTH - 2)) + 1;

        // add tail
        tail_lenght++;
    }

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
}

// refresh the board and draw it
void draw()
{
    // refresh board
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            // borders
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
    board[fruit.i][fruit.j] = '$';
    board[snake_head.i][snake_head.j] = 'S';
    for (size_t i = 0; i < tail_lenght; i++)
    {
        board[snake_tail[i].i][snake_tail[i].j] = 's';
    }

    // print board
    system("clear");
    for (size_t i = 0; i < HEIGHT; i++) // height
    {
        for (size_t j = 0; j < WIDTH; j++) // width
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
}
