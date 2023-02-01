/**
 * @file snake_labyrinth.c
 * @author federico scaggiante
 * @brief a simple game where a snake tries to escape from a labyrinth
 * @mainpage main snake_labyrinth program
 *
 * @section intro_sec Introduzione
 *
 * This program is a snake game that take place in a labyrinth.<br>
 *
 * @subsection rules Regole del gioco
 * @code{.c}
19
10
###################
o    #          $ #
#    #          $ #
#    #   ! #    $ #
#    #     #    $ #
#   T#     #      _
#    #     #      #
#          #      #
#    $$$$  #      #
###################
 * @endcode
 *
 * La figura sopra rappresenta un labirinto dove il nostro protagonista Snake o deve trovare l’uscita _.<br>
 * Snake percorre il labirinto raccogliendo o evitando gli oggetti nel piano di gioco finché non raggiunge l’uscita.<br>
 * Ogni oggetto può aumentare o diminuire il punteggio del nostro eroe. Anche la lunghezza del percorso è importante perché Snake vuole uscire il prima possibile.<br>
 * <b>L’obiettivo del gioco è di trovare il miglior percorso che porta all’uscita del labirinto.</b><br>
 * Per migliore si intende il percorso che produce il punteggio più elevato.<br>
 * Ciò significa che il percorso migliore non è semplicemente il più breve.<br>
 * @subsubsection moves Mosse possibili
 * Inizialmente Snake ha 1000 punti.<br>
 * Ad ogni turno le mosse possibili sono:<br>
 * • N: un passo verso l’alto (Nord)<br>
 * • S: un passo verso il basso (Sud)<br>
 * • O: un passo a sinistra (Ovest)<br>
 * • E: un passo a destra (Est)<br>
 * Ogni passo costa 1 punto.<br>
 * @subsubsection prizes Premi e Ostacoli
 * Durante il percorso Snake può incontrare:<br>
 * • # pareti che non possono essere attraversate;<br>
 * • $ monete, ciascuna del valore di 10 punti e che inoltre incrementano la sua lunghezza;<br>
 * • ! imprevisti, che se incontrati dimezzano (divisione intera) il numero di monete raccolte, e la sua lunghezza;<br>
 * • T trapano che permette di perforare le pareti. Al trapano è associato un numero di usi disponibili
 * inizialmente pari a 0. Ogni vola che viene raccolta una T, il numero di usi disponibili del trapano
 * aumenta di 3. Ogni volta che Snake entra in una casella con una parete il numero di usi diminuisce di
 * 1, e la casella diventa vuota, cioè la parete nella casella scompare. Se il numero di usi è pari a 0, snake
 * non può entrare in una cella con una parete. Le pareti esterne possono essere trapanate, ma non si
 * possono superare i bordi del gioco.<br>
 * <br>
 * Gli oggetti scompaiono dopo la prima interazione con Snake.<br>
 * Una volta raccolta una moneta, questa viene rimossa dal piano di gioco e non può essere raccolta due volte.<br>
 * In modo simile per gli imprevisti. Snake non può occupare una cella dove si trova una parete #, e quindi le pareti non scompaiono mai, a meno che non venga usato il trapano.<br>
 * Una volta trovata l’uscita, il punteggio è dato dal punteggio iniziale più la somma dei valori delle monete possedute all’uscita meno il numero di passi eseguiti.<br>
 *
 * @subsection install_sec Installazione
 *
 * @subsubsection step1 install gcc:
 * sudo dnf install gcc
 *
 * @subsubsection step2 build the program:
 * gcc -o snake_labyrinth snake_labyrinth.c
 *
 * @subsubsection step3 generate doxygen doc:
 * sudo dnf install doxygen<br>
 * doxygen Doxyfile
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
    printf("Welcome to the snake_labyrint game :)\n");
    // wait 3 sec
    usleep(3000000);
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
        // init moves array
        moves_lenght = 1;
        moves = (int *)malloc(1 * sizeof(int));
    }
}

void logic()
{
    int moving = 0;
    coordinates tmp = snake_head;

    // clear snake
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
            // check collision with borders
            if (board[snake_head.i - 1][snake_head.j] == '#')
            {
                // use drill to pass through
                if (drill_usages > 0)
                {
                    drill_usages--;
                }
                else
                {
                    break;
                }
            }
            snake_head.i--;
            moving = 1;
        }
        break;
    case 2: /* S */
        if (snake_head.i < rows - 1)
        {
            // check collision with borders
            if (board[snake_head.i + 1][snake_head.j] == '#')
            {
                // use drill to pass through
                if (drill_usages > 0)
                {
                    drill_usages--;
                }
                else
                {
                    break;
                }
            }
            snake_head.i++;
            moving = 1;
        }
        break;
    case 3: /* O */
        if (snake_head.j > 0)
        {
            // check collision with borders
            if (board[snake_head.i][snake_head.j - 1] == '#')
            {
                // use drill to pass through
                if (drill_usages > 0)
                {
                    drill_usages--;
                }
                else
                {
                    break;
                }
            }
            snake_head.j--;
            moving = 1;
        }
        break;
    case 4: /* E */
        if (snake_head.j < cols - 1)
        {
            // check collision with borders
            if (board[snake_head.i][snake_head.j + 1] == '#')
            {
                // use drill to pass through
                if (drill_usages > 0)
                {
                    drill_usages--;
                }
                else
                {
                    break;
                }
            }
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
    int *tmp = (int *)malloc((moves_lenght + 1) * sizeof(int));
    for (size_t i = 0; i < moves_lenght; i++)
    {
        tmp[i] = moves[i];
    }
    moves = tmp;
    moves[moves_lenght - 1] = direction;
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
