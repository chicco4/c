#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// TODO implement snake tail

int height, width, gameover, score, flag, snake_lenght;

typedef struct
{
    int i;
    int j;
} coordinates;

coordinates *snake; // snake come array di coordinate
coordinates fruit;

// Function to generate the fruit within the boundary
void setup()
{
    gameover = 0;
    height = 10;
    width = 20;
    score = 0;
    srand(time(NULL));
    fruit.i = (rand() % ((height - 1) - 1)) + 1;
    fruit.j = (rand() % ((width - 1) - 1)) + 1;

    // (width * height) massima grandezza di snake
    // snake come array di coordinate
    snake = malloc(sizeof(coordinates) * width * height);
    snake[0].i = height / 2;
    snake[0].j = width / 2;
}

// Function to draw the boundaries
void draw()
{
    system("clear");
    printf("snakei= %d, snakej= %d\n", snake[0].i, snake[0].j); // DEBUG
    printf("fruiti= %d, fruitj= %d\n", fruit.i, fruit.j);       // DEBUG
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                printf("#");
            else if (i == snake[0].i && j == snake[0].j)
                printf("o");
            else if (i == fruit.i && j == fruit.j)
                printf("$");
            else
                printf(" ");
        }
        printf("\n");
    }

    // Print the score after the game ends
    printf("score = %d\n", score);
    printf("press x to quit the game\n");
}

// Function for the logic behind each movement
void logic()
{
    switch (flag)
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

    // If the game is over
    if (snake[0].i <= 0 || snake[0].i >= height - 1 || snake[0].j <= 0 || snake[0].j >= width - 1)
        gameover = 1;

    // If snake reaches the fruit, then update the score
    if (snake[0].i == fruit.i && snake[0].j == fruit.j)
    {
        score++;
        // After eating the above fruit, generate new fruit
        srand(time(NULL));
        fruit.i = (rand() % ((height - 1) - 1)) + 1;
        fruit.j = (rand() % ((width - 1) - 1)) + 1;
    }

    flag = 0;
}

// Function to take the input
void input()
{
    switch (getchar())
    {
    case 'w': /* N */
        flag = 1;
        break;
    case 's': /* S */
        flag = 2;
        break;
    case 'a': /* O */
        flag = 3;
        break;
    case 'd': /* E */
        flag = 4;
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
