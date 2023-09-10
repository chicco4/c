#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(int number)
{
    if (number <= 1)
    {
        return false; // I numeri minori o uguali a 1 non sono primi
    }
    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            return false; // Se il numero è divisibile per i, non è primo
        }
    }
    return true; // Se non è stato trovato un divisore, il numero è primo
}

bool no_prime(int *A, size_t A_len)
{
    bool no = true;
    for (size_t i = 0; i < A_len; i++)
    {
        if (is_prime(A[i]))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int A[] = {10, 4, 8, 11};
    printf("%d \n", no_prime(A, 4));

    int B[] = {1, 4, 8, 6, 12};
    printf("%d \n", no_prime(B, 4));
}