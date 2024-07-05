#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>


#define MAX_STRING_LEN 100 // maximum length of a person's name
#define MIN_STRING_LEN 5 
#define ART_SIZE 2000
#define TOTAL_SCORE 100
#define MAX_COURSES 3
#define PASS_THRESHOLD 55
#define TOTAL_SCORE 100

const char *LOGO_FILE_NAME = "logo.txt";

// Enum for data types
enum DataType {
    STRING,
    INTEGER,
    FLOAT,
    SCORE
};

// Structure for a student object
struct Student {
    char name[MAX_STRING_LEN];
    char department[MAX_STRING_LEN];
    char courses[MAX_COURSES][MAX_STRING_LEN];
    int roll_number;
    float scores[MAX_COURSES];
    float average;
    char grade[MIN_STRING_LEN];
};

//Global variables
struct Student *students = NULL;
int student_count = 0;

// Function prototypes
void clear_terminal();
void print_logo();
void show_error_art(char *msg);
void get_user_name(char *user_name);
void convert_to_upper(char *str);
void validate_input_choices(char *prompt, enum DataType type, void *target, int *user_choice_input, int len_target);
void validate_input_data(const char *prompt, void *input_buffer, enum DataType type, int max_length, int min_length);
void add_student(struct Student **students_array, int *student_count);
int get_main_program_choice();

int main() {
    /*
        This is the main function that runs the entire program.
    */
    clear_terminal(); // Clear the terminal and print logo

    char user_name[MAX_STRING_LEN];
    get_user_name(user_name); // Get the username
    convert_to_upper(user_name);
    printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@@                                                                                @@\n");
    printf("          ----< WELCOME ABOARD %s! WHAT WOULD YOU LIKE TO DO? >----                 \n", user_name);
    printf("@@                                                                                @@\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

    int selected_operation = get_main_program_choice();
    printf("Selected option %d\n", selected_operation);

    switch (selected_operation)
    {
        case 1:
            add_student(&students,&student_count);
            break;
        
        default:
            break;
    }

    return 0;
}

/**
 * @brief  This function prints the program's logo from a file named
        logo.txt.
 *
*/
void print_logo() {
    char line[256];  // Store each line of the file in a string
    FILE *inFile;

    // Open the file
    inFile = fopen(LOGO_FILE_NAME, "r");
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

/**
 * @brief This function clears the terminal console using the expression
        printf("\e[1;1H\e[2J").

        Basically:
            - \e is the escape character in ASCII.
            - [1;1H is an escape sequence that moves the cursor to row 1, column 1 (the top-left corner of the screen).
            - [2J is an escape sequence that clears the entire screen.

        So by saying printf("\e[1;1H\e[2J"), we tell the terminal to move the cursor to the top-left corner and clear the screen.
 *
*/
void clear_terminal() {
    printf("\e[1;1H\e[2J"); 
    print_logo();
}

/**
 * @brief This function converts a given string to upercase
 *
 * @param str The string to convert to upper case.
*/
void convert_to_upper(char *str){
    // Implementation to convert string to uppercase
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

/**
 * @brief Gets the user name.
 *
 * @param user_name The string value of the user name.
.
*/
void get_user_name(char *user_name) {
    
    validate_input_data("\n--> Enter your name to proceed: ",user_name,STRING,MAX_STRING_LEN,MIN_STRING_LEN);
}

/**
 * @brief This function validates that the user entry is valid for the options provided.
        For example, if the user is asked to select options from 1, 2, 3, 4, this function ensures
        that the user entry is within the allowable options.

        also, if the available options is {y,n}, this function ensures
        that the user entry is within the allowable options.
 *
 * @param prompt The prompt message to display to the user.
 * @param type The datatype of values in the list of choices presented to tye user.
 * @param target The list of choices presented to tye user.
 * @param user_choice_input The value entered by the user.
 * @param len_target The length of the list of choices presented to the user.
*/
void validate_input_choices(char *prompt, enum DataType type, void *target, int *user_choice_input, int len_target) {
    bool is_valid_userchoice = false;
    char user_input[2], *target_string; // Buffer to store user input
    // printf("lenin: %d",len_target);

    while (!is_valid_userchoice) {
        printf("%s", prompt);
        scanf(" %s", user_input); // Read user input as a string
        
        if (type == INTEGER) {
            target_string = "integer";
            *user_choice_input = atoi(user_input); // Convert user input string to integer
            // printf("userin : %d\n lenin: %d", *user_choice_input,len_target);
            int *int_array = (int *)target; // If the datatype is integer, cast the target to int pointer
            for (int i = 0; i < len_target; i++) {
                // Loop through the array to check if the user's input matches any element
                if (*user_choice_input == int_array[i]) {
                    is_valid_userchoice = true;
                    break;
                }
            }
        } else if (type == STRING) { 
            target_string = "character";
            *user_choice_input = user_input[0]; // Store the first character of user input as char
            char *char_array = (char *)target; // If the datatype is character, cast the target to char pointer
            for (int i = 0; i < len_target; i++) {
                // Loop through the array to check if the user's input matches any element
                if (*user_choice_input == char_array[i]) {
                    is_valid_userchoice = true;
                    break;
                }
            }
        }

        if (!is_valid_userchoice) {
            clear_terminal();
            char error_msg[ART_SIZE];
            sprintf(error_msg,"           Please enter a valid %s from the options provided               \n",target_string);
            show_error_art(error_msg);

        }
    }
}

/**
 * @brief Shows error message using predefined art
 * @param msg The message string to include inside the art
 * 
*/
void show_error_art(char *msg){
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!!!                                                                     !!!\n");
    printf("!!!                              ERROR:                                 !!!\n");
    printf("!!!                          Invalid input                              !!!\n");
    printf("%s\n", msg);
    printf("!!!                                                                     !!!\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}

/**
 * @brief Validates user input based on the specified data type.
 *
 * @param prompt The prompt message to display to the user.
 * @param input_buffer Pointer to the buffer where the validated input will be stored.
 * @param type The data type of the input (STRING, INTEGER, FLOAT, SCORE).
 * @param max_length Maximum length allowed for strings (0 for other types).
 * @param min_length Minimum length required for strings (0 for other types).
 */
void validate_input_data(const char *prompt, void *input_buffer, enum DataType type, int max_length, int min_length) {
    bool valid = false;
    char buffer[256];
    float score;

    while (!valid) {
        printf("%s", prompt);
        char error_msg[ART_SIZE];
        fgets(buffer, sizeof(buffer), stdin);

        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        switch (type) {
            case STRING:
                // Validate string length
                if (strlen(buffer) >= min_length && strlen(buffer) <= max_length) {
                    strncpy((char *)input_buffer, buffer, max_length); // Copy up to max_length characters
                    valid = true;
                } else {
                    sprintf(error_msg,"Please enter a string with length between %d and %d characters\n", min_length, max_length);
                }
                break;
            case INTEGER:
                // Validate integer input
                if (sscanf(buffer, "%d", (int *)input_buffer) == 1) {
                    valid = true;
                } else {
                    strcat(error_msg,"                   Please enter a valid integer                    \n");
                }
                break;
            case FLOAT:
                // Validate float input
                if (sscanf(buffer, "%f", (float *)input_buffer) == 1) {
                    valid = true;
                } else {
                    strcat(error_msg,"                  Please enter a valid float number                  \n");
                }
                break;
            case SCORE:
                // Validate score input (numeric and within range)
            
                if (sscanf(buffer, "%f", &score) == 1 && score <= TOTAL_SCORE) {
                    *(float *)input_buffer = score;
                    valid = true;
                } else {
                    sprintf(error_msg,"   Please enter a numerical value less than or equal to %d   \n",TOTAL_SCORE);
                }
                break;
            default:
                // Invalid input type
                printf("!!!Invalid input type!!!\n");
                return;
        }
        if (!valid) {
            printf("%d",valid);
            show_error_art(error_msg);
        }
    }
}

/**
 * @brief Gets the integer value representing the operation a user wants to perform, e.g.,
 * If they choose, 1, it means they want to add a student, if the choose 2, they want to update a record, and so on.
 *
 */
int get_main_program_choice() {

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
    validate_input_choices(option_art, INTEGER, options, &userselection, len_options);
    return userselection;
}

/**
 * @brief Checks for duplicate roll number.
 * 
 * This function checks if the user is inputting a roll number for that is already recorded in the student array. 
 * 
 * @param current_student_roll The current roll number in the student array being checked.
 */
bool is_duplicate_roll_num(int current_student_roll) {
    if (student_count > 0) {
        for (int i = 0; i < student_count; i++) {
            return students[i].roll_number == current_student_roll;
        }
    }
    return false;
}

/**
 * @brief Checks for duplicate courses.
 * 
 * This function checks if the user is inputting a course that is already recorded for a student 
 * 
 * @param selected_student Pointer to the structure of a student in the entire student array.
 * @param course_name the name of the current course being checked.
 */
bool is_duplicate_course(struct Student *selected_student, char course_name[MAX_STRING_LEN]){
    for (int i = 0; i < MAX_COURSES; i++){
        return strcmp(selected_student->courses[i], course_name)==0;
    }
    return false;
}

/**
 * @brief Adds a new student to the students record array.
 * 
 * This function guides the user through entering details for a new student,
 * including name, department, unique roll number, courses taken, and their scores.
 * It calculates the average score and assigns a pass or fail grade based on the average.
 * The student record is then added to the system and possibly sorted and or saved to a json file.
 * 
 * @param students_array Pointer to the pointer of the array of students.
 * @param student_count Pointer to the count of students currently in the system.
 */
void add_student(struct Student **students_array, int *student_count) {
    bool duplicate_roll = false;    // Flag to check for duplicate roll numbers
    bool duplicate_course = false;  // Flag to check for duplicate course names
    int total_score = 0;            // Accumulator for total score of courses
    char course_name[MAX_STRING_LEN];  // Buffer to store course name during input
    char sen[MAX_STRING_LEN + 50];   // Buffer for constructing prompts

    // Allocate or reallocate memory for students_array array
    if (*student_count == 0) {
        *students_array = malloc(sizeof(struct Student)); // Allocate memory for the first student
    } else {
        *students_array = realloc(*students_array, (*student_count + 1) * sizeof(struct Student)); // Reallocate for additional student
    }
    if (*students_array == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Pointer to the new student record in the array
    struct Student *new_student = &(*students_array)[*student_count];

    // Prompt and validate student's name
    printf("\n@@@@@@@@@@@@ ADDING STUDENT %d TO THE DATABASE @@@@@@@@@@@@\n", *student_count + 1);
    validate_input_data("\n--> Enter student's name: ", new_student->name, STRING, MAX_STRING_LEN, MIN_STRING_LEN);

    // Prompt and validate student's department
    snprintf(sen, sizeof(sen), "--> Enter %s's department: ", new_student->name);
    validate_input_data(sen, new_student->department, STRING, MAX_STRING_LEN, MIN_STRING_LEN);

    // Check for duplicate roll number and prompt until unique
    while (true) {
        snprintf(sen, sizeof(sen), "--> Enter %s's roll number: ", new_student->name);
        validate_input_data(sen, &new_student->roll_number, INTEGER, sizeof(int), 0);
        //duplicate_roll = is_duplicate_roll_num(*students_array, *student_count, new_student->roll_number);
        if (!is_duplicate_roll_num(new_student->roll_number)) {
            break;
        }
        printf("!!! A student with this roll number already exists. Please enter a unique roll number.\n");
    }

    // Prompt and validate each course name and score
    printf("\n############ Now, input the courses %s took and their scores: ############\n", new_student->name);
    printf("!! Important: each student must take %d course(s) per session\n", MAX_COURSES);

    for (int i = 0; i < MAX_COURSES; i++) {
        // Prompt and validate course name, ensure it is unique
        while (true) {
            snprintf(sen, sizeof(sen), "--> Enter course name for course %d: ", i + 1);
            validate_input_data(sen, course_name, STRING, MAX_STRING_LEN, MIN_STRING_LEN);
            //duplicate_course = is_duplicate_course(new_student, course_name);
            if (!is_duplicate_course(new_student, course_name)) {
                strncpy(new_student->courses[i], course_name, MAX_STRING_LEN);
                break;
            }
            printf("!!! That course already exists. Please enter a unique course name.\n");
        }

        // Prompt and validate score for the course
        snprintf(sen, sizeof(sen), "--> Enter score for course %d: ", i + 1);
        validate_input_data(sen, &new_student->scores[i], SCORE, sizeof(float), 0);
        total_score += new_student->scores[i]; // Accumulate score for average calculation
    }

    // Calculate average score and determine grade
    new_student->average = (float)total_score / (float)MAX_COURSES;
    if (new_student->average >= PASS_THRESHOLD) {
        strncpy(new_student->grade, "Pass", MIN_STRING_LEN);
    } else {
        strncpy(new_student->grade, "Fail", MIN_STRING_LEN);
    }

    // Increment student count and save record
    (*student_count)++;
    //auto_sort_save_record(*students_array, *student_count); // Sort and save student records
}
