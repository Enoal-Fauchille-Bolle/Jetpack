/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Test File
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

TestSuite(test, .init = redirect_all_stdout);
