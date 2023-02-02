/**
 * B ‑ Zip
 * La compressione ZIP usa anche la seguente intuizione. Se posso costruire una lista di sotto‑stringhe fre‑
 * quenti, allora posso comprimere un testo memorizzando solo una identificazione di queste sotto‑stringhe.
 * Implementare una funzione di decompressione ZIP con i seguenti parametri: stringa di codifica, array delle
 * posizioni iniziali, array delle lunghezze. La decodifica è definita dal seguente esempio:
 */

#include <stdio.h>
#include <stdlib.h>

char *
es6(char *enc, int *starts, int *lens, int size)
{
    char *s = (char *)malloc(1);
    int i, j, l = 0;
    for (i = 0; i < size; i++)
    {
        s = realloc(s, l + lens[i] + 1);
        for (j = 0; j < lens[i]; j++)
            s[l++] = enc[starts[i] + j];
    }
    s[l] = '\0';
    return s;
}

int main()
{
    char *enc_text = " over and";
    int starts[] = {1, 0};
    int lens[] = {8, 5};
    printf("%s \n", es6(enc_text, starts, lens, 2));
    return 0;
}
