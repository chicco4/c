#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 10
#define WIDTH 20

int gameover, score, direction, snake_lenght;
char board[HEIGHT][WIDTH];

typedef struct
{
    int i;
    int j;
} coordinates;

coordinates snake[HEIGHT * WIDTH]; // snake as array of coordinates
coordinates fruit;

void setup()
{
    srand(time(NULL));
    gameover = 0;
    score = 0;

    // setup empty board and borders
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
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

    // adding fruit to the board
    fruit.i = (rand() % ((HEIGHT - 1) - 1)) + 1;
    fruit.j = (rand() % ((WIDTH - 1) - 1)) + 1;
    board[fruit.i][fruit.j] = '$';

    // adding snake to the board
    snake[0].i = HEIGHT / 2;
    snake[0].j = WIDTH / 2;
    snake_lenght = 1;
    board[snake[0].i][snake[0].j] = 'O';
}

// Function for the logic behind each movement
void logic()
{
    board[snake[0].i][snake[0].j] = ' ';

    // FIXME dovrei ciclare tutte la tail per farle andare verso sinistra
    switch (direction)
    {
    case 1: /* N */
        snake[0].i--;
        break;
    case 2: /* S */
        snake[0].i++;
        break;
    case 3: /* O */
        snake[0].j--;
        break;
    case 4: /* E */
        snake[0].j++;
        break;
    default:
        break;
    }
    direction = 0;

    board[snake[0].i][snake[0].j] = 'O';

    if (snake[0].i == fruit.i && snake[0].j == fruit.j)
    {
        score++;
        // spawn new fruit
        fruit.i = (rand() % ((HEIGHT - 1) - 1)) + 1;
        fruit.j = (rand() % ((WIDTH - 1) - 1)) + 1;
        board[fruit.i][fruit.j] = '$';
        snake_lenght++;
    }
}

// FIXME add a way to draw the tail of the snake
void draw()
{
    system("clear");
    printf("fruiti = %d, fruitj = %d\n", fruit.i, fruit.j);       // DEBUG
    printf("snakei = %d, snakej = %d\n", snake[0].i, snake[0].j); // DEBUG
    // print board
    for (size_t i = 0; i < HEIGHT; i++) // height
    {
        for (size_t j = 0; j < WIDTH; j++) // width
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    // Print the score after the game ends
    printf("score = %d\n", score);
    printf("press x to quit the game\n");
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

void main()
{
    setup();

    // Until the game is over
    while (!gameover)
    {

        // Function Calls
        draw();
        input();
        logic();
    }
}
