#include <stdio.h>
#include <stdlib.h>

/**
 * quadrata di interi (disposta in memoria come un array flattened / appiattito) di n righe e n colonne, che
 * riempia la matrice m con valori 1 e 0 formando una diagonale principale (da sinistra a destra) con uno
 * spessore pari a k come negli esempi che seguono.
 */

void fill(int *m, int n, int k)
{
    int row, col;
    int diff = k - 1;
    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            if (abs(col - row) <= diff)
            {
                m[row * n + col] = 1;
            }
            else
            {
                m[row * n + col] = 0;
            }
        }
    }
}

int main()
{
    int m[5][5];
    fill(&m[0][0], 5, 2);

    // print matrix
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    return 0;
}