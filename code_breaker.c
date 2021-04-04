/*Written by: Robert Colanardi
  Last Updated: Oct-07-2020
*/
#include <stdio.h>
#include "code_breaker.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*contains game functions for the code_breaker game*/

int start_menu(){
    print_game_header();
    int game_mode = game_mode_select();
    return(game_mode);
}

void print_game_header(){
    char * game_header =
    "  _____ ____  _____  ______   ____  _____  ______          _  ________ _____  \n"
    " / ____/ __ \\|  __ \\|  ____| |  _ \\|  __ \\|  ____|   /\\   | |/ /  ____|  __ \\ \n"
    "| |   | |  | | |  | | |__    | |_) | |__) | |__     /  \\  | ' /| |__  | |__) |\n"
    "| |   | |  | | |  | |  __|   |  _ <|  _  /|  __|   / /\\ \\ |  < |  __| |  _  /\n"
    "| |___| |__| | |__| | |____  | |_) | | \\ \\| |____ / ____ \\| . \\| |____| | \\ \\\n"
    " \\_____\\____/|_____/|______| |____/|_|  \\_\\______/_/    \\_\\_|\\_\\______|_|  \\_\\\n";
    printf("%s",game_header);
}

int game_mode_select(){
    printf("\t\t\tSelect an option from the menu:\n\t\t\t\t1:Single player"
    "\n\t\t\t\t2:Instructions\n\t\t\t\t3:exit\n\t\t\t\t\tselect: ");
    int user_selected_mode;
    if (fscanf(stdin,"%d",&user_selected_mode) != 0){
        if (user_selected_mode != 1 && user_selected_mode != 2 &&
            user_selected_mode != 3){
                printf("You must choose an option from the menu (1-3).\n");
        }
    } else {
        printf("Input can not be blank. try again.\n");
    }
    char line = ' ';
    line = getchar(); //gets rid of hte leftover newline
    return(user_selected_mode);
}

int single_player_game(){
    int guess_log[10][4]; //store all the guesses
    int guess_correctness_log[10]; //store the correctnesses of all guesses
    int game_key[4] = {-1,-1,-1,-1};
    int guess[4] = {-1,-1,-1,-1};
    generate_code(game_key);
    //printf("generated key: %d%d%d%d\n",game_key[0],game_key[1],game_key[2],game_key[3]);

    int game_over = 0;
    int turn_number = 0;
    int guess_correctness = 0;
    while (game_over == 0){
        //printf("The is turn: %d\n",turn_number);
        //print the game board
        clear_screen(); //clear the console
        print_game_board(game_key,guess_log,guess_correctness_log, turn_number);
        turn_number++;
        //get a guess from the user
        get_guess(guess);
        //printf("guess = {%d,%d,%d,%d}\n",guess[0],guess[1],guess[2],guess[3]);
        for ( int i =0; i < 4; i++){
            guess_log[turn_number-1][i] = guess[i];
        }
        //check the guesses guess_correctness
        guess_correctness = check_guess(game_key, guess);
        //printf("guess_correctness = %d\n",guess_correctness);
        guess_correctness_log[turn_number-1] = guess_correctness;

        if ( guess_correctness == 100){
            //the user was totally correct
            game_over = 1;
        }
        if ( turn_number == 10){
            print_game_board(game_key,guess_log,guess_correctness_log, turn_number);
            game_over = -1;
        }

    }
    if (game_over == 1){
        printf("\n\n\t\tGreat Work, You Win!\n"
        "\t\tThe answer this time was %d%d%d%d\n",
            game_key[0],game_key[1],game_key[2],game_key[3]);
    }
    else{
        printf("\n\n\t\tUnfortunate, next game you'll win for sure!\n"
               "\t\t\tThe answer this time was %d%d%d%d\n",
           game_key[0],game_key[1],game_key[2],game_key[3]);
    }
    return(game_over);
}

/*generate a random 4 digit code of the numbers 0-7*/
void generate_code(int* key){
    /*generate an array of 4 ints from 0-7*/
    for (int i = 0; i < 4; i++) {
        key[i] = (rand()%8);
    }
}

/*get the user to input a 4 digit code consisting of digits 0-7*/
void get_guess(int * guess){
    int getting_input = 0;
    int input = -1;
    char *line = NULL;
    size_t len = 8;
    while ( getting_input == 0){
        printf("Your guess must be 4 digits long and contain only 0-7.\n\tEnter you guess:");
        if (getline(&line,&len, stdin) != -1){
            //printf("line = '%s' strlen(line) = %d\n",line,strlen(line));
            if ( strlen(line) == 5 ){
                input = atoi(line);
                if (input > -1 && input <7778){
                    /*get the individual digits in the input*/
                    for ( int i =3; i > -1; i--){
                        guess[i] = input %10;
                        input = input /10;
                    }
                    /*make sure that the guess is accpetable*/
                    int bad_input = 1;
                    for ( int i =0; i < 4; i++){
                        if (guess[i] < 0 || guess[i] > 7){
                            bad_input = 0;
                        }
                    }
                    if ( bad_input == 1){
                        getting_input = 1;
                    }
                    else{
                        printf("Sorry, that guess wasn't allowed.\n");
                    }
                }
            }
        }
    }
    free(line);
}

void print_instructions(){
    char* instructions = "\n"
    "\t\t\tInstructions for Code Breaker\n\n"
    "The objective of the game is to try and decipher the computer's code.\n"
    "The code is a 4 digit sequence consisting of the numbers 0-7.\n"
    "For example: 1234\t4565\t0012 are all possible codes.\n"
    "To figure out the code after each attempt you make, the computer will tell\n"
    "you how successful your attempt was.\n\n"
    "Say the code is 1234 and you guessed 2467. The computer would tell you that\n"
    "your guess had 2 of the correct numbers but they were in the wrong positions.\n"
    "On your next guess if you tried 5241, the computer would tell you that you got\n"
    "1 in the correct position and 2 in the wrong positions. You need to use this\n"
    "information to decipher the code in 10 guesses or less.\n\n"
    "\t\t\tThink you've got what it takes?\n";
    printf("%s\n",instructions);
}

int check_guess(int *game_key, int* guess){
    int guess_correctness = 0;
    int correct_place =0;
    int wrong_place = 0;
    //matched digits are set to 9 in track_checking_array
    int track_checking_array [4] = {0,0,0,0};

    //check for the digits that match up perfectly
    for ( int i =0; i < 4; i++){
        if (game_key[i] == guess[i]){
            correct_place++;
            track_checking_array[i] = 9;
        }
    }
    if ( correct_place == 4){
        guess_correctness = 100;
    }
    else{
        guess_correctness = correct_place*10;
    }

    //check for the digits that don't match up correctly
    for ( int i =0; i < 4; i++){
        if ( track_checking_array[i] != 9){
            //check the current digit against those that aren't already matched up
            for ( int j =0; j < 4; j++){
                if (guess[i] == game_key[j] && track_checking_array[j] != 9){
                    guess_correctness++;
                    j = 4; //prevents duplicates if the key/guess have repeated values
                }
            }
        }
    }

    return (guess_correctness);
}

void print_game_board(int* game_key,int guess_log[10][4], int* guess_correctness_log, int turn_number){
    print_game_header();

    //print top border
    /*
    if (turn_number > 0){
        printf("key: %d,%d,%d,%d\nguess_correctness_log[%d] = %d\n",game_key[0],game_key[1],game_key[2],game_key[3],turn_number-1,guess_correctness_log[turn_number-1]);
    }
    */
    printf("\t __________________________________________________________\n"
    "\t/                                                          \\\n");
    printf("\t| V-wrong postion      Turns Left: %2d     Right postion-V  |\n",10-turn_number);
    printf("\t|    __________________________________________________    |\n");
    printf("\t|   /                                                  \\   |\n");

    //print unused guesses
    for ( int i = 0; i < 10-turn_number; i++){
        printf("\t|   |                                                  |   |\n");
    }


    //print already entered guesses
    for ( int i = turn_number-1; i  > -1; i--){
        printf("\t|%2d |          %d          %d          %d          %d      |%2d |\n",
                guess_correctness_log[i]%10,guess_log[i][0],guess_log[i][1],
            guess_log[i][2],guess_log[i][3],(guess_correctness_log[i]%100)/10);
    }


    //print bottom border
    if ( turn_number > 0){
        printf("\t|   \\__________________________________________________/   |\n"
        "\t|                   V  Current Guess  V                    |\n"
        "\t|          %d          %d          %d          %d              |\n",
            guess_log[turn_number-1][0],guess_log[turn_number-1][1],
            guess_log[turn_number-1][2],guess_log[turn_number-1][3]);

        printf("\t|                                                          |\n"
        "\t\\__________________________________________________________/\n");
    }
    else{
        printf("\t|   \\__________________________________________________/   |\n"
        "\t|                   V  Current Guess  V                    |\n"
        "\t|                                                          |\n"
        "\t\\__________________________________________________________/\n");
    }

}

void clear_screen(){
    for ( int i =0; i < 10000; i++){
        printf("\e[1;1H\e[2J");
    }
}
