#include <stdio.h>
#include <stdlib.h>

void process_array(int *v, size_t v_len)
{
    if (v_len > 0)
    {
        process_array(v + 1, v_len - 1);
        printf("%d ", v[0]);
    }
}

int main(){
    
    printf("ciao\n");

    int a[4] = {1,2,3,4};

    process_array(a,4);

    return 0;
}