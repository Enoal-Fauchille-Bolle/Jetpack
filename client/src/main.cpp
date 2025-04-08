/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** main
*/

int main(int ac, char **av)
{
    if (ac != 2) {
        return 84;
    }
    if (av[1][0] == '-' && av[1][1] == 'h') {
        return 0;
    }
    // Initialize the game
    // Game game(av[1]);
    // game.run();
    return 0;
}