/*Last Update: Oct-07-2020 */

/*contains function definitions for the code_breaker game*/
#ifndef CODE_BREAKER_H
#define CODE_BREAKER_H

/*allows user to select a 1 player or 2 player game, or view the rules*/
int start_menu();

/*displays the game header*/
void print_game_header();

/*displays the gameplay rules/instructions*/
int game_rules();

/*gets the desired gameplay option from the user through the start menu*/
int game_mode_select();
/*player guesses computer generated code*/
int single_player_game();

/*generate an array of 4 integers to use as game's key*/
void generate_code(int* key);

/*get the user to input a 4 digit code consisting of digits 0-7*/
void get_guess(int * guess);

/*check how many of the digits in the guess match up to those in the key*/
int check_guess(int *game_key, int *guess);
/*print the instructions to the game*/

/*print the board that the game is played on*/
void print_game_board(int* game_key,int guess_log[10][4], int* guess_correctness_log, int turn_number);

//use a regex to clear the console
void clear_screen();


void print_instructions();



#endif
