#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NAME_CHARS 100 // maximum length of a person's name
#define ART_SIZE 2000
const char *logo_file_name = "logo.txt";

// Function prototypes
void clear_terminal();
void print_logo();
void get_user_name(char *user_name);
void convert_to_upper(char *str);
void validate_input(char *prompt, char *datatype, void *target, int *user_choice_input, int len_input);
int get_user_choice();

int main() {
    /*
        This is the main function that runs the entire program.
    */
    clear_terminal(); // Clear the terminal and print logo

    char user_name[MAX_NAME_CHARS];
    get_user_name(user_name); // Get the username
    convert_to_upper(user_name);
    printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@@                                                                                @@\n");
    printf("          ----< WELCOME ABOARD %s! WHAT WOULD YOU LIKE TO DO? >----                 \n", user_name);
    printf("@@                                                                                @@\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

    int selected_operation = get_user_choice();
    printf("Selected option %d\n", selected_operation);

    return 0;
}

void print_logo() {
    /*
        This function prints the program's logo from a file named
        logo.txt.
    */
    char line[256];  // Store each line of the file in a string
    FILE *inFile;

    // Open the file
    inFile = fopen(logo_file_name, "r");
    // Check if the file is available to be loaded
    if (inFile == NULL) {
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        printf("!!!                                          !!!\n");
        printf("!!!                ERROR:                    !!!\n");
        printf("!!!           File failed to load            !!!\n");
        printf("!!!            No logo displayed             !!!\n");
        printf("!!!                                          !!!\n");
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

        return;
    }

    // Read and print each line
    while (fgets(line, sizeof(line), inFile) != NULL) {
        printf("%s", line);
    }

    // Close the file
    fclose(inFile);
}

void clear_terminal() {
    /*
        This function clears the terminal console using the expression
        printf("\e[1;1H\e[2J").

        Basically:
            - \e is the escape character in ASCII.
            - [1;1H is an escape sequence that moves the cursor to row 1, column 1 (the top-left corner of the screen).
            - [2J is an escape sequence that clears the entire screen.

        So by saying printf("\e[1;1H\e[2J"), we tell the terminal to move the cursor to the top-left corner and clear the screen.
    */
    printf("\e[1;1H\e[2J"); 
    print_logo();
}

void convert_to_upper(char *str){
    /*
        This function converts a given string to upercase
    */
    str = strupr(str);
}

void get_user_name(char *user_name) {
    
    printf("\n--> Enter your name to proceed: ");
    scanf("%s", user_name);
}

void validate_input(char *prompt, char *datatype, void *target, int *user_choice_input, int len_input) {
    /*
        This function validates that the user entry is valid for the options provided.
        For example, if the user is asked to select options from 1, 2, 3, 4, this function ensures
        that the user entry is within the allowable options.

        also, if the available options is {y,n}, this function ensures
        that the user entry is within the allowable options.
    */
    bool is_valid_userchoice = false;
    char user_input[100]; // Buffer to store user input
    // printf("lenin: %d",len_input);

    while (!is_valid_userchoice) {
        printf("%s", prompt);
        scanf(" %s", user_input); // Read user input as a string
        
        if (strcmp(datatype, "integer") == 0) {
            *user_choice_input = atoi(user_input); // Convert user input string to integer
            // printf("userin : %d\n lenin: %d", *user_choice_input,len_input);
            int *int_array = (int *)target; // If the datatype is integer, cast the target to int pointer
            for (int i = 0; i < len_input; i++) {
                // Loop through the array to check if the user's input matches any element
                if (*user_choice_input == int_array[i]) {
                    is_valid_userchoice = true;
                    break;
                }
            }
        } else if (strcmp(datatype, "character") == 0) { 
            *user_choice_input = user_input[0]; // Store the first character of user input as char
            char *char_array = (char *)target; // If the datatype is character, cast the target to char pointer
            for (int i = 0; i < len_input; i++) {
                // Loop through the array to check if the user's input matches any element
                if (*user_choice_input == char_array[i]) {
                    is_valid_userchoice = true;
                    break;
                }
            }
        }

        if (!is_valid_userchoice) {
            clear_terminal();
            printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("!!!                                                                     !!!\n");
            printf("!!!                              ERROR:                                 !!!\n");
            printf("!!!                          Invalid input                              !!!\n");
            printf("           Please enter a valid %s from the options provided               \n", datatype);
            printf("!!!                                                                     !!!\n");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

        }
    }
}



int get_user_choice() {
    /*
        This function returns the operation number the user wants to perform.
        If they choose, 1, it means they want to add a student, if the choose 2, they want to update a record, and so on
    */

    int userselection;
    int options[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len_options = sizeof(options) / sizeof(options[0]);
    char option_art[ART_SIZE];
    // printf("len opt: %d", len_options);
    // Store the ASCII art in the buffer
    sprintf(option_art,
        "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
        "@@                                                                                @@\n"
        "@@                        SELECT AN OPERATION TO PERFORM                          @@\n"
        "@@                        ------------------------------                          @@\n"
        "@@                        1. Add new Student data                                 @@\n"
        "@@                        2. Modify student data                                  @@\n"
        "@@                        3. Display all records                                  @@\n"
        "@@                        4. Delete record(s)                                     @@\n"
        "@@                        5. Search for a student by roll number                  @@\n"
        "@@                        6. Sort the Student Record                              @@\n"
        "@@                        7. Save record                                          @@\n"
        "@@                        8. Read record from file                                @@\n"
        "@@                        9. Exit                                                 @@\n"
        "@@                                                                                @@\n"
        "           --> Please type a number to select an option from above: ");
    
    // Validate and get the user input
    validate_input(option_art, "integer", options, &userselection, len_options);
    return userselection;
}
