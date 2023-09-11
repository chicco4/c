#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int process_array(int *v, size_t v_len)
{
    if (v_len == 1)
        return 0;

    return v[1] + process_array(v + 1, v_len - 1);
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    printf("%d", process_array(a, 5));
    return 0;
}
// il codice calcola la somma dei valori nell’array tranne il primo