/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Utilities
*/

#include <string.h>
#include <ctype.h>

/**
 * @brief Convert a string to uppercase.
 *
 * This function takes a string as input and converts all lowercase
 * letters to uppercase.
 *
 * @param str The string to convert.
 * @return char* The converted string.
 */
char *touppercase(char *str)
{
    if (str == NULL) {
        return NULL;
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
    return str;
}

/**
 * @brief Trim leading and trailing whitespace from a string.
 *
 * This function removes leading and trailing whitespace characters
 * (spaces, tabs, newlines) from the input string.
 *
 * @param str The string to trim.
 * @return char* The trimmed string.
 */
char *trim(char *str)
{
    char *start = str;
    char *end = start + strlen(start) - 1;

    if (!str || *str == '\0')
        return str;
    while (*start && isspace(*start))
        start++;
    if (*start == '\0') {
        *str = '\0';
        return str;
    }
    while (end > start && isspace(*end)) {
        *end = '\0';
        end--;
    }
    if (start != str)
        memmove(str, start, strlen(start) + 1);
    return str;
}
