#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    printf("test\n");

    // Allocate memory for a character array of size 5
    char *s = (char *)malloc(6 * sizeof(char)); // Allocate space for 5 'a' characters and a null terminator '\0'

    if (s == NULL)
    {
        perror("Failed to allocate memory");
        return 1; // Exit with an error code
    }

    // Initialize the array with 'a' characters
    for (size_t i = 0; i < 5; i++)
    {
        s[i] = 'a';
    }

    // Null-terminate the string
    s[5] = '\0';

    printf("%s\n", s);

    // Don't forget to free the allocated memory when done
    free(s);

    return 0;
}