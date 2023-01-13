#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 10

struct Snake
{
    int x, y;
    struct Snake *next;
};

struct Snake *head;

void setup()
{
    // Initialize the game board
    printf("\033[2J\033[1;1H"); // clear the screen

    // Initialize the snake
    head = (struct Snake *)malloc(sizeof(struct Snake));
    head->x = BOARD_WIDTH / 2;
    head->y = BOARD_HEIGHT / 2;
    head->next = NULL;
}
void input()
{
    char direction;
    scanf("%c", &direction);

    // Update the snake's position based on the player's input
    switch (direction)
    {
    case 'w':
        head->y--;
        break;
    case 'a':
        head->x--;
        break;
    case 's':
        head->y++;
        break;
    case 'd':
        head->x++;
        break;
    }
}
void draw()
{
    system("clear");
    // Draw the game board
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (i == 0 || i == BOARD_HEIGHT - 1 || j == 0 || j == BOARD_WIDTH - 1)
            {
                printf("#");
            }
            else
            {
                // Check if the current cell is occupied by the snake
                bool is_snake_present = false;
                struct Snake *current = head;
                while (current != NULL)
                {
                    if (current->y == i && current->x == j)
                    {
                        printf("O");
                        is_snake_present = true;
                        break;
                    }
                    current = current->next;
                }
                if (!is_snake_present)
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("\033[%d;%dH", BOARD_HEIGHT, 0); // move cursor to the bottom of the screen
}

void logic()
{
    // Check if the snake has collided with the border
    if (head->x <= 0 || head->x >= BOARD_WIDTH - 1 || head->y <= 0 || head->y >= BOARD_HEIGHT - 1)
    {
        printf("Game Over!\n");
        exit(0);
    }

    // Check if the snake has collided with itself
    struct Snake *current = head->next;
    while (current != NULL)
    {
        if (current->x == head->x && current->y == head->y)
        {
            printf("Game Over!\n");
            exit(0);
        }
        current = current->next;
    }
}
int main()
{
    setup();

    while (true)
    {
        draw();
        input();
        logic();
        // Add a delay to slow down the game
        usleep(100000); // 100ms delay
    }

    return 0;
}
