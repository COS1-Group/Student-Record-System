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
char YES_NO_OPTIONS[] = { 'y','n'};

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
void show_no_data_err(char *action);
void show_header_art(char *header_string);
void print_logo();
void show_error_art(char *msg);
void get_user_name(char *user_name);
void convert_to_upper(char *str);
void validate_input_choices(char *prompt, enum DataType type, void *target, int *user_choice_input, int len_target);
void validate_input_data(const char *prompt, void *input_buffer, enum DataType type, int max_length, int min_length);
void add_student(struct Student **students_array, int *student_count);
void display_all_students();
void display_student_info(struct Student *student, int student_index);
int get_main_program_choice();
void clear_input_buffer() ;

int main() {
    /*
        This is the main function that runs the entire program.
    */
    clear_terminal(); // Clear the terminal and print logo

    char user_name[MAX_STRING_LEN];
    
    get_user_name(user_name); // Get the username
    convert_to_upper(user_name);
    char welcome_user_msg[90 + strlen(user_name)]; 
    sprintf(welcome_user_msg,"          ----< WELCOME ABOARD %s! WHAT WOULD YOU LIKE TO DO? >----                 \n",user_name);
    show_header_art(welcome_user_msg);

    int selected_operation = get_main_program_choice();
    printf("Selected option %d\n", selected_operation);

    switch (selected_operation)
    {
        case 1:
            add_student(&students,&student_count);
            display_all_students();
            break;
        case 2:
            display_all_students();
            break;
        default:
            break;
    }

    return 0;
}

void show_header_art(char *header_string){
    printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@@                                                                                @@\n");
    printf("%s\n",header_string);
    printf("@@                                                                                @@\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
        printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
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
        *str = toupper((char)*str);
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
        scanf("%s", user_input); // Read user input as a string
        clear_input_buffer();
        
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
            sprintf(error_msg,"!!!      Please enter a valid %s from the options provided         !!!",target_string);
            show_error_art(error_msg);

        }
    }
}

/**
 * @brief Shows error message for invalid input using predefined art
 * @param msg The message string to include inside the art
 * 
*/
void show_error_art(char *msg){
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!!!                                                                     !!!\n");
    printf("!!!                              ERROR:                                 !!!\n");
    printf("!!!                                                                     !!!\n");
    printf("!!!                          Invalid input                              !!!\n");
    printf("%s\n", msg);
    printf("!!!                                                                     !!!\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}

/**
 * @brief Checks if a string contains only alphanumeric characters or alphabetic characters.
 * 
 * @param str The string to check.
 * @return true If the string contains only alphanumeric or alphabetic characters.
 * @return false If the string contains non-alphanumeric characters.
 */
bool is_alphanumeric_or_alphabetic(const char *str) {
    bool has_alpha = false; // Flag to track if the string has at least one alphabetic character
    bool has_digit = false; // Flag to track if the string has at least one digit

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            has_alpha = true; // Set to true if the character is alphabetic
        } else if (isdigit(str[i])) {
            has_digit = true; // Set to true if the character is a digit
        } else {
            return false; // Returns false if a non-alphanumeric character is found
        }
    }

    return has_alpha; // Return true if the string contains at least one alphabetic character
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
    char error_msg[MAX_STRING_LEN * 2];

    while (!valid) {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);

        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        switch (type) {
            case STRING:
                // Validate string length and content
                if (strlen(buffer) >= min_length && strlen(buffer) <= max_length && is_alphanumeric_or_alphabetic(buffer)) {
                    strncpy((char *)input_buffer, buffer, max_length); // Copy up to max_length characters
                    valid = true;
                } else {
                    sprintf(error_msg,"!!!        Please enter a string with length between %d and %d,         !!!\n!!!        containing only alphabetic or alphanumeric characters        !!!",MIN_STRING_LEN,MAX_STRING_LEN);
                    show_error_art(error_msg);
                }
                break;

            case INTEGER:
                // Validate integer input
                if (sscanf(buffer, "%d", (int *)input_buffer) == 1 && !is_alphanumeric_or_alphabetic(buffer)) {
                    valid = true;
                } else {
                    show_error_art("!!!                    Please enter a valid integer                     !!!");
                }
                break;

            case FLOAT:
                // Validate float input
                if (sscanf(buffer, "%f", (float *)input_buffer) == 1 && !is_alphanumeric_or_alphabetic(buffer)) {
                    valid = true;
                } else {
                    show_error_art("!!!                Please enter a valid float number               !!!");
                }
                break;

            case SCORE:
                // Validate score input (numeric and within range)
                if (sscanf(buffer, "%f", &score) == 1 && score <= TOTAL_SCORE && !is_alphanumeric_or_alphabetic(buffer)) {
                    *(float *)input_buffer = score;
                    valid = true;
                } else {
                    sprintf(error_msg,"!!!      Please enter a numerical value less than or equal to %d       !!!",TOTAL_SCORE);
                    show_error_art(error_msg);
                }
                break;

            default:
                // Invalid input type
                printf("!!!Invalid input type!!!\n");
                return;
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
bool is_duplicate_roll_num( int current_student_roll) {
    if (student_count > 0) {
        for (int i = 0; i < student_count; i++) {
            if (students[i].roll_number == current_student_roll){
                return true;
            }
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
bool is_duplicate_course(struct Student *selected_student, char course_name[MAX_STRING_LEN]) {
    for (int i = 0; i < MAX_COURSES; i++) {
        if (strcmp(selected_student->courses[i], course_name) == 0) {
            return true; // Found a duplicate course
        }
    }
    return false; // No duplicates found
}

/**
 * @brief Checks if the user wants to repeat an action.
 * 
 * This function prompts the user to enter 'Y' or 'N' to repeat an action.
 * 
 * @param action The action description to display in the prompt.
 * @param response Pointer to where the user's response ('Y' or 'N') will be stored.
 * @return true if the user wants to repeat the action, false otherwise.
 */
bool repeat_action(char *action, int *response) {
    char prompt[MAX_STRING_LEN + 50];
    sprintf(prompt, "\n-> Do you want to %s ? Y/N: ", action);

    // Validate user input for 'Y' or 'N'
    validate_input_choices(prompt, STRING, YES_NO_OPTIONS, response, sizeof(YES_NO_OPTIONS));

    // Convert response to lowercase for consistency
    *response = tolower(*response);

    return *response == 'y';
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
    bool duplicate_roll;    // Flag to check for duplicate roll numbers
    bool duplicate_course = false;  // Flag to check for duplicate course names
    int total_score = 0;            // Accumulator for total score of courses
    char course_name[MAX_STRING_LEN];  // Buffer to store course name during input
    char add_header_msg[MAX_STRING_LEN * 5];
    char sen[MAX_STRING_LEN + 50];   // Buffer for constructing prompts
    char *error_msg;
    int add_again;

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

    clear_terminal();
    // Pointer to the new student record in the array
    struct Student *new_student = &(*students_array)[*student_count];

    // Prompt and validate student's name
    sprintf(add_header_msg,"@@                  ----< ADDING STUDENT %d TO THE DATABASE >----                  @@",*student_count + 1);
    show_header_art(add_header_msg);
    validate_input_data("\n--> Enter student's name: ", new_student->name, STRING, MAX_STRING_LEN, MIN_STRING_LEN);
    convert_to_upper(new_student->name);

    // Prompt and validate student's department
    snprintf(sen, sizeof(sen), "\n--> Enter %s's department: ", new_student->name);
    validate_input_data(sen, new_student->department, STRING, MAX_STRING_LEN, MIN_STRING_LEN);

    // Check for duplicate roll number and prompt until unique
    while (true) {

        snprintf(sen, sizeof(sen), "\n--> Enter %s's roll number: ", new_student->name);
        validate_input_data(sen, &new_student->roll_number, INTEGER, sizeof(int), 0);
        duplicate_roll = is_duplicate_roll_num(new_student->roll_number);
        if (!duplicate_roll) {
            break;
        }
        error_msg = "!!!           A student with this roll number already exists            !!!\n!!!                  Please enter a unique roll number                  !!!";
        show_error_art(error_msg);
    }

    // Prompt and validate each course name and score
    sprintf(add_header_msg,"\n                Now, input the courses %s took and their scores                \n              Important: each student must take %d course(s) per session              ",new_student->name,MAX_COURSES);
    show_header_art(add_header_msg);
    // printf("\n############ Now, input the courses %s took and their scores: ############\n", new_student->name);
    // printf("!! Important: each student must take %d course(s) per session\n", MAX_COURSES);

    for (int i = 0; i < MAX_COURSES; i++) {
        // Prompt and validate course name, ensure it is unique
        while (true) {
            duplicate_roll = true;
            snprintf(sen, sizeof(sen), "\n--> Enter course name for course %d: ", i + 1);
            validate_input_data(sen, course_name, STRING, MAX_STRING_LEN, MIN_STRING_LEN);
            duplicate_course = is_duplicate_course(new_student, course_name);
            printf("%d",duplicate_course);
            if (!duplicate_course) {
                strncpy(new_student->courses[i], course_name, MAX_STRING_LEN);
                break;
            }
            error_msg = "!!!                     That course already exists                      !!!\n!!!                   Please enter a unique course name                 !!!";
            show_error_art(error_msg);
            //printf("!!! That course already exists. Please enter a unique course name.\n");
        }

        // Prompt and validate score for the course
        snprintf(sen, sizeof(sen), "\n--> Enter score for course %d: ", i + 1);
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

    if (repeat_action("add another record",&add_again)){
        add_student(students_array,student_count);
    }
    //auto_sort_save_record(*students_array, *student_count); // Sort and save student records(coming soon...)
}

/**
 * @brief Display error message for empty student record
 * 
 * If user tries to display,modify,delete or search records and the student array is empty(no record added),
 * This function tells user that no data exists for the action to be performed.
 * @param action The action being performed, e.g., display , delete, modify and search.
*/
void show_no_data_err(char *action){
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!!!                                                                     !!!\n");
    printf("!!!                              ERROR:                                 !!!\n");
    printf("!!!                                                                     !!!\n");
    if(strlen(action) == 7){// if action is display(len display is 7)
        printf("!!!                      Cannot %s record(s)                       !!!\n",action);

    }else if (strlen(action)==6){ // actions other than display(delete,search,modify)
        printf("!!!                       Cannot %s record(s)                       !!!\n",action);

    }
    printf("!!!                          No data available                          !!!\n");
    printf("!!!                                                                     !!!\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
/**
 * @brief Display information of all students.
 * 
 * 
 */
void display_all_students() {
    int display_again;
    clear_terminal();
    if (student_count <= 0) {
        show_no_data_err("display");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        display_student_info(&students[i], i);
    }
    if (repeat_action("display all records again",&display_again)){
        display_all_students();
    }
}

/**
 * @brief Display information of a single student in a formatted way.
 *This is what the format mean ( please note that the formatting not perfect and may change depending on the actual value of variables):
    %-15s:
        %-: Left-align the string in the given field.
        15: Minimum field width of 15 characters.
        s: Format as a string.
    %-10.2f:
        %-: Left-align the number in the given field.
        10: Minimum field width of 10 characters.
        .2: Display 2 digits after the decimal point.
        f: Format as a floating-point number.
    %-50s:
        %-: Left-align the string in the given field.
        50: Minimum field width of 50 characters.
        s: Format as a string.
    %-50d:
        %-: Left-align the number in the given field.
        50: Minimum field width of 50 characters.
        d: Format as an integer.
 * 
 * @param student Pointer to the student structure.
 * @param student_index Index of the student in the array.
 */
void display_student_info(struct Student *student, int student_index) {
   
    printf("\n================================================================================\n");
    printf("                          STUDENT %d: %s                          \n", student_index + 1, student->name);
    printf("================================================================================\n");
    printf("| %-15s: %-50s |\n", "Department", student->department);
    printf("| %-15s: %-50d |\n", "Roll Number", student->roll_number);
    printf("================================================================================\n");
    printf("                               COURSES AND SCORES                               \n");
    printf("--------------------------------------------------------------------------------\n");

    for (int j = 0; j < MAX_COURSES; j++) {
        printf("| %-45s : %-10.2f |\n", student->courses[j], student->scores[j]);
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("| %-15s: %-10.2f                                    \n", "Average", student->average);
    printf("| %-15s: %-50s \n", "Grade", student->grade);
    printf("================================================================================\n");
}