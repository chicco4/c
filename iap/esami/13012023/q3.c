#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int diag(int *M, int n_rows, int n_cols)
{
    int sum = 0;
    for (int i = 0; i < n_rows; i++)
        for (int j = 0; j < n_cols; j++)
            sum += M[i + i * n_cols];
    return sum;
}

int main()
{

    return 0;
}
/*per calcolare la somma degli elementi sulla diagonale di una matrice quadrata non basta eliminare il
secondo for*/