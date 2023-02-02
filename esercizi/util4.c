#include <stdio.h>

/**Scrivere una funzione find che dato un array a trovi l’elemento minimo il cui quadrato è maggiore di 66. Se
 * non c’è nessun elemento che soddisfa il criterio, la funzione restituisce ‑1.
 */
int find(int *a, int a_length)
{
    int res = -1;
    for (int i = 1; i < a_length; i++)
    {
        if (a[i] * a[i] > 66)
        {
            if (res == -1)
            {
                res = a[i];
            }
            else
            {
                if (a[i] < res)
                {
                    res = a[i];
                }
            }
        }
    }

    return res;
}

int main()
{

    int a[5] = {7, 8, 10, 9, 12};
    int result = find(a, 5); /* 5 C( la lunghezza dell'array */
    printf("%d\n", result);

    return 0;
}
