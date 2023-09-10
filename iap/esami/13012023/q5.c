#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *get_vowels(char *s)
{
    char *new_s = (char *)malloc(strlen(s) + 1);

    if (!new_s)
        exit(EXIT_FAILURE);

    char *new_s_temp = new_s;
    while (*s)
    {
        bool is_vowel = *s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u' || *s == 'A' || *s == 'E' || *s == 'I' || *s == 'O' || *s == 'U';
        if (is_vowel)
            *(new_s_temp++) = *(s);
        *(s++);
    }
    *(new_s_temp++) = '\0';
    return new_s;
}

int main()
{
    char greeting[] = "ciao come stai bella?";
    printf("%s\n", greeting);

    printf("%s\n", get_vowels(greeting));

    return 0;
}
