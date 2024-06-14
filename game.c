/*written by: Robert Colanardi
  Last updated: June-14-2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "code_breaker.h"

int main(int argc, char const *argv[])
{
    /*use the current time as the seed for random number generation*/
    srand(time(0));
    int game_mode = 0;
    int end_program = 0;
    clear_screen(); // clear the screen of compilation text
    game_mode = start_menu();
    // printf("Game mode = %d\n",game_mode);
    while (end_program == 0)
    {
        if (game_mode == 1)
        {
            // printf("Single PLayer\n");
            char playing = 'Y';
            while (playing == 'Y')
            {
                single_player_game();
                int i = 0;
                while (i == 0)
                {
                    printf("Would you like to play again (Y/N): ");
                    playing = getchar();
                    getchar();
                    if (playing != 'Y' && playing != 'y' && playing != 'n' && playing != 'N')
                    {
                        printf("Sorry I didn't catch that.\n");
                    }
                    else
                    {
                        i = -1;
                    }
                }
                if (playing == 'y')
                {
                    playing = 'Y';
                }
            }
            end_program = 1;
        }
        else if (game_mode == 2)
        {
            // printf("Instructions\n");
            clear_screen();
            print_instructions();
            game_mode = game_mode_select();
        }
        else
        {
            printf("Thank you for playing. Have a lovely day.\n");
            end_program = 1;
        }
    }

    // printf("END OF PROGRAM\n");
    return 0;
}
