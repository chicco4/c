/**
 * @file snake_labyrinth.c
 * @author federico scaggiante
 * @brief a simple game where a snake tries to escape from a labyrinth
 * @version 0.1
 * @date 2023-01-05
 *
 * @section install_sec installation
 * @subsection step1: install gcc
 * @subsection step2: gcc -O2 -std=c99 --pedantic *.c -o snake_labyrinth.c
 */

#include "snake_labyrinth.h"

void setup()
{
    gameover = 0;
    win = 0;
    score = 1000;
    tail_lenght = 0;
    drill_usages = 0;

    system("clear");
    printf("insert labyrint:\n");
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
    // init snake_tail
    snake_tail = (coordinates *)malloc(rows * cols * sizeof(coordinates));

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

    printf("modalità ai? (n / y)\n");
    if (getchar() == 'n')
    {
        ai_mode = 0;
    }
    if (getchar() == 'y')
    {
        ai_mode = 1;
        // arbitrary big array
        moves = (int *)malloc(rows * cols * sizeof(int));
    }
}

void logic()
{
    int moving = 0;
    coordinates tmp = snake_head;

    // clear board
    board[snake_head.i][snake_head.j] = ' ';
    for (size_t i = 0; i < tail_lenght; i++)
    {
        board[snake_tail[i].i][snake_tail[i].j] = ' ';
    }

    // move snake_head
    switch (direction)
    {
    case 1: /* N */
        if (snake_head.i > 0)
        {
            snake_head.i--;
            moving = 1;
        }
        break;
    case 2: /* S */
        if (snake_head.i < rows - 1)
        {
            snake_head.i++;
            moving = 1;
        }
        break;
    case 3: /* O */
        if (snake_head.j > 0)
        {
            snake_head.j--;
            moving = 1;
        }
        break;
    case 4: /* E */
        if (snake_head.i < cols - 1)
        {
            snake_head.j++;
            moving = 1;
        }
        break;
    default:
        break;
    }
    direction = 0;

    // every move score--
    if (moving)
    {
        score--;
    }

    // if snake reach a trap
    if (board[snake_head.i][snake_head.j] == '!')
    {
        score = score / 2;
        tail_lenght = tail_lenght / 2;
    }

    // if snake reach a drill
    if (board[snake_head.i][snake_head.j] == 'T')
    {
        drill_usages = drill_usages + 3;
    }

    // if snake reach the exit
    if (board[snake_head.i][snake_head.j] == '_')
    {
        win = 1;
        gameover = 1;
    }

    // if snake reach a coin
    if (board[snake_head.i][snake_head.j] == '$')
    {
        // update score
        score = score + 10;

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

    // check collision with borders
    if (board[snake_head.i][snake_head.j] == '#')
    {
        // use drill to not die
        if (drill_usages > 0)
        {
            drill_usages--;
        }
        else
        {
            gameover = 1;
        }
    }

    // check collision with snake_tail
    for (size_t i = 0; i < tail_lenght; i++)
    {
        if (snake_head.i == snake_tail[i].i && snake_head.j == snake_tail[i].j)
        {
            score = score - (10 * (tail_lenght - i));
            tail_lenght = tail_lenght - (tail_lenght - i);
        }
    }

    if (score <= 0)
    {
        gameover = 1;
    }

    // refresh board
    board[snake_head.i][snake_head.j] = 'o';
    for (size_t i = 0; i < tail_lenght; i++)
    {
        board[snake_tail[i].i][snake_tail[i].j] = 's';
    }
}

void draw()
{
    system("clear");
    // printf("snakehead[%d][%d]\n", snake_head.i, snake_head.j); // debug
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    // print the score after the game ends
    printf("drills = %d\n", drill_usages);
    printf("score = %d\n", score);
    if (ai_mode)
    {
        printf("ai_moves: ");
        for (size_t i = 0; i < moves_lenght; i++)
        {
            switch (moves[i])
            {
            case 1: /* N */
                printf("N");
                break;
            case 2: /* S */
                printf("S");
                break;
            case 3: /* O */
                printf("O");
                break;
            case 4: /* E */
                printf("E");
                break;
            default:
                break;
            }
        }
        printf("\n");
    }
    else
    {
        printf("press x to quit the game\n");
    }
}

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

void random_ai()
{
    // random move from 1 to 4 included
    srand(time(NULL));
    int move = (rand() % 4) + 1;

    // check if movement is possible
    if (board[snake_head.i - 1][snake_head.j] != '#' && move == 1)
    {
        direction = 1;
    }
    if (board[snake_head.i + 1][snake_head.j] != '#' && move == 2)
    {
        direction = 2;
    }
    if (board[snake_head.i][snake_head.j - 1] != '#' && move == 3)
    {
        direction = 3;
    }
    if (board[snake_head.i][snake_head.j + 1] != '#' && move == 4)
    {
        direction = 4;
    }
    moves[moves_lenght] = direction;
    moves_lenght++;
    // wait 1 sec each move
    // sleep(1);
    // wait 0.5 sec each move
    usleep(500000);
}

void wall_follow_ai()
{
    // implementation

    moves[moves_lenght] = direction;
    moves_lenght++;
    // wait 1 sec each move
    // sleep(1);
    // wait 0.5 sec each move
    usleep(500000);
}

void ending()
{
    system("clear");
    if (win)
    {
        printf("YOU WON!\n");
        printf("score = %d\n", score);
    }
    else
    {
        printf("YOU LOST!\n");
        printf("score = %d\n", score);
    }
}

void free_memory()
{
    // free board
    for (int i = 0; i < rows; i++)
    {
        free(board[i]);
    }
    free(board);

    // free snake_tail
    free(snake_tail);

    // free moves
    if (ai_mode)
    {
        free(moves);
    }
}

void main()
{
    setup();

    while (!gameover)
    {
        draw();
        if (ai_mode)
        {
            random_ai();
        }
        else
        {
            input();
        }
        logic();
    }
    ending();

    free_memory();
}
