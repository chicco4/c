#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 10
#define WIDTH 20

int gameover, score, direction, snake_length;
char board[HEIGHT][WIDTH];

typedef struct
{
    int i;
    int j;
} coordinates;

coordinates snake[HEIGHT * WIDTH]; // snake as array of coordinates
coordinates fruit;

// function to initialize the board
void initBoard()
{
    int i, j;
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            board[i][j] = ' ';
        }
    }
    // place the fruit on the board
    srand(time(NULL));
    fruit.i = rand() % HEIGHT;
    fruit.j = rand() % WIDTH;
    board[fruit.i][fruit.j] = 'F';
}

// function to update the board
void updateBoard()
{
    int i, j;
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            if (i == snake[0].i && j == snake[0].j)
            {
                board[i][j] = 'S';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
    // place the fruit on the board
    board[fruit.i][fruit.j] = 'F';
    // place the snake's tail on the board
    for (i = 1; i < snake_length; i++)
    {
        board[snake[i].i][snake[i].j] = 's';
    }
}

// function to move the snake
void moveSnake()
{
    int i;
    for (i = snake_length - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }
    if (direction == 0) // move up
    {
        snake[0].i--;
    }
    else if (direction == 1) // move right
    {
        snake[0].j++;
    }
    else if (direction == 2) // move down
    {
        snake[0].i++;
    }
    else if (direction == 3) // move left
    {
        snake[0].j--;
    }
}

// function to check for collision
void checkCollision()
{
    // check for collision with walls
    if (snake[0].i == 0 || snake[0].i == HEIGHT - 1 ||
        snake[0].j == 0 || snake[0].j == WIDTH - 1)
    {
        gameover = 1;
    }
    // check for collision with snake's body
    int i;
    for (i = 1; i < snake_length; i++)
    {
        if (snake[0].i == snake[i].i &&
            snake[0].j == snake[i].j)
        {
            gameover = 1;
        }
    }
    // check for collision with fruit
    if (snake[0].i == fruit.i && snake[0].j == fruit.j)
    {
        // increase snake length and place new fruit
        snake_length++;
        fruit.i = rand() % HEIGHT;
        fruit.j = rand() % WIDTH;
        score++;
    }
}

// function to get user input
void getInput()
{
    char ch = getchar();
    if (ch == 'w' && direction != 2)
    {
        direction = 0;
    }
    else if (ch == 'd' && direction != 3)
    {
        direction = 1;
    }
    else if (ch == 's' && direction != 0)
    {
        direction = 2;
    }
    else if (ch == 'a' && direction != 1)
    {
        direction = 3;
    }
}

int main()
{
    int i;
    // initialize game variables
    gameover = 0;
    score = 0;
    direction = 1;
    snake_length = 3;
    for (i = 0; i < snake_length; i++)
    {
        snake[i].i = HEIGHT / 2;
        snake[i].j = WIDTH / 2 + i;
    }
    initBoard();
    while (!gameover)
    {
        updateBoard();
        for (i = 0; i < HEIGHT; i++)
        {
            printf("%s\n", board[i]);
        }
        printf("Score: %d\n", score);
        moveSnake();
        checkCollision();
        getInput();
    }
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}