/* matrice perfetta */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_perfect(int *M, size_t n_rows, size_t n_cols)
{
    bool is_ok = true;
    for (size_t col = 0; col < n_cols; col++)
    {
        int col_sum = 0;
        for (size_t row = 0; row < n_rows; row++)
        {
            col_sum += M[row*n_cols + col];
        }
        printf("%d ", col_sum);
    }

    return is_ok;
}

int main()
{
    int A[4][3] = {{0, 1, 1},
                   {0, 2, 2},
                   {1, 1, 2},
                   {1, 0, 3}};

    printf("%d \n", is_perfect(&A[0][0], 4, 3));
    return 0;
}