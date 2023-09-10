#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to check if two strings 'a' and 'b' match character by character.
bool is_match(char *a, char *b)
{
    while (*b)
    {
        if (*a != *b)
            return false;
        a++;
        b++;
    }
    return true;
}

// Function to duplicate string 'a' while replacing occurrences of 'b' with duplicates of 'b'.
char *str_dup(char *a, char *b)
{
    // Calculate the length of string 'b'.
    size_t b_len = strlen(b);

    // Allocate memory for the new string, ensuring enough space for duplication.
    char *new_s = malloc(strlen(a) * 2 + 1); // For safety

    // Check if memory allocation was successful.
    if (!new_s)
        exit(EXIT_FAILURE); // Exit the program if allocation fails.

    // Initialize a pointer 'dest' to keep track of the current position in the new string.
    char *dest = new_s;

    while (*a)
    {
        // Check if the current portion of 'a' matches 'b'.
        if (is_match(a, b))
        {
            // If there's a match, duplicate 'b' in the new string.
            char *b_copy = b;
            while (*b_copy)
            {
                *(dest) = *(b_copy);
                *(dest + b_len) = *(b_copy);
                dest++;
                b_copy++;
            }
            dest += b_len;
            a += b_len;
        }
        else
        {
            // If there's no match, simply copy the current character from 'a' to the new string.
            *(dest++) = *(a++);
        }
    }

    // Add the null terminator at the end of the new string.
    *(dest++) = '\0';

    // Reallocate memory to trim any excess memory beyond what's needed.
    new_s = realloc(new_s, dest - new_s);

    // Return the final duplicated string.
    return new_s;
}

int main()
{
    // Test the 'str_dup' function by replacing occurrences of "love" in the input string.
    printf("%s \n", str_dup("i love coding and i love playing", "love"));

    return 0;
}
