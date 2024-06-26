#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_CHARS 100 // maximum length of a person's name



const char *logo_file_name = "logo.txt";
void clear_terminal();
void get_user_name();
void convert_to_upper(char *str);

int main(){
    /*
        this is the main function that runs the entire program

    */

    clear_terminal(); // clear the terminal and print logo

    char user_name[MAX_NAME_CHARS];
    get_user_name(user_name); // Get the username
    convert_to_upper(user_name);

    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<--WELCOME ABOARD %s! WHAT WOULD YOU LIKE TO DO?-->>>>>>>>>>>>>>>>>>>>>>>>>>>\n", user_name);


}

void print_logo(){
    /*
        This function prints the program's logo from a file named
        logo.txt
    */

    char line[256];  // store each line of the file in a string
    FILE *inFile;

    // Open the file
    inFile = fopen(logo_file_name, "r");
    // Check if the file is available to be loaded
    if (inFile == NULL) {
        printf("!!!File failed to load!!!\n");
        printf("!!!No logo displayed!!!\n");
        return;
    }

    // Read and print each line
    while (fgets(line, sizeof(line), inFile) != NULL) {
        printf("%s", line);
    }

    // Close the file
    fclose(inFile);
}

void clear_terminal(){
    /*
        This function clears the terminal console using the expression
        printf("\e[1;1H\e[2J")

        basically:
            - \e is the escape character in ASCII
            - [1;1H is an escape sequence that moves the cursor to row 1, column 1 (the top-left corner of the screen).
            - [2J: This is an escape sequence that clears the entire screen

        so by saying printf("\e[1;1H\e[2J"), we tell the terminal to to move the cursor to the top-left corner and clear the screen
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
    printf("\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<--HI, THIS IS THE STUDENT RECORD SYSTEM-->>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("--> Enter your name to proceed: ");
    scanf("%s",user_name);
}
    