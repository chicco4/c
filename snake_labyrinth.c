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

int i, j, height, width;
int gameover, score;
int snakei, snakej, fruiti, fruitj, flag;

// Function to generate the fruit within the boundary
void setup()
{
    gameover = 0;
    height = 10;
    width = 20;
    snakei = height / 2;
    snakej = width / 2;
    score = 0;

    srand(time(NULL));
    fruiti = (rand() % ((height - 1) - 1)) + 1;
    fruitj = (rand() % ((width - 1) - 1)) + 1;
}

// Function to draw the boundaries
void draw()
{
    system("clear");
    // printf("snakei= %d, snakej= %d\n", snakei, snakej);// DEBUG
    // printf("fruiti= %d, fruitj= %d\n", fruiti, fruitj);// DEBUG
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                printf("#");
            else if (i == snakei && j == snakej)
                printf("o");
            else if (i == fruiti && j == fruitj)
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

// Function for the logic behind each movement
void logic()
{
    switch (flag)
    {
    case 1: /* N */
        snakei--;
        break;
    case 2: /* S */
        snakei++;
        break;
    case 3: /* O */
        snakej--;
        break;
    case 4: /* E */
        snakej++;
        break;
    default:
        break;
    }

    // If the game is over
    if (snakei <= 0 || snakei >= height - 1 || snakej <= 0 || snakej >= width - 1)
        gameover = 1;

    // If snake reaches the fruit, then update the score
    if (snakei == fruiti && snakej == fruitj)
    {
        score++;
        // After eating the above fruit, generate new fruit
        srand(time(NULL));
        fruiti = (rand() % ((height - 1) - 1)) + 1;
        fruitj = (rand() % ((width - 1) - 1)) + 1;
    }

    flag = 0;
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
