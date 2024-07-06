#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>



#define MAX_STRING_LEN 100 // maximum length of a person's name
#define MAX_MSG_LEN 256
#define MIN_STRING_LEN 5 
#define ART_SIZE 1262
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
char yes_no_options[] = { 'y','n'};
int student_count = 0;
bool greet_user = true;
char *auto_sort_order;
bool auto_sort;
bool auto_save;


// Function prototypes
bool repeat_action(char *action, int *response);
void clear_terminal();
void sort_students(char *order);
void auto_sort_save();
void sort_operation();
void show_success_message( char *msg);
void update_course(struct Student *student, bool update_name);
void modify_student_data();
void show_not_found_err_msg();
void show_no_data_err(char *action);
void show_header_art(char *header_string);
void print_logo();
void show_error_message(char *msg);
void get_user_name(char *user_name);
void convert_to_upper(char *str);
void validate_input_choices(char *prompt, enum DataType type, void *target, int *user_choice_input, int len_target);
void validate_input_data(const char *prompt, void *input_buffer, enum DataType type, int max_length, int min_length);
void add_student(struct Student **students_array, int *student_count);
void display_all_students();
void display_student_info(struct Student *student, int student_index);
int get_main_program_choice();
int search_by_roll(char *purpose);
void clear_input_buffer() ;
void show_found_student();
void delete_action();
void show_info_message(char *msg);

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

    while (true)
    {
        int selected_operation = get_main_program_choice();
        // printf("Selected option %d\n", selected_operation);
        greet_user = false;
        switch (selected_operation)
        {
            case 1:
                add_student(&students,&student_count);
                break;
            case 2:
                modify_student_data();
                break;
            case 3:
                display_all_students();
                break;
            case 4:
                delete_action();
                break;
            case 5:
                show_found_student();
                break;
            case 6:
                sort_operation();
                break;
            default:
                break;
        }

        int do_action_again_response;
        if(!repeat_action("perform another action",&do_action_again_response)){
            break;
        }
    }
    free(students);

    return 0;
}

/**
 * @brief Shows the header art for an action to be performed(such as add, modify,etc)
 * 
 * @param header_string The message inside the header
*/
void show_header_art(char *header_string){
    printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@@                                                                                @@\n");
    printf("%s\n",header_string);
    printf("@@                                                                                @@\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

/**
 * @brief Clears new line from character input buffer
 * When using scanf to get a character from the user, the compiler automatically adds a newline
 * This function removes the newline to prevent errors in operation
 * 
*/
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
        show_error_message(
            "!!!                          File failed to load                         !!!\n"
            "!!!                          No logo displayed                           !!!\n"

        );
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
            *user_choice_input = tolower(*user_choice_input);
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
            char error_msg[MAX_MSG_LEN];
            sprintf(
                error_msg,
                "\n!!!                          Invalid input                              !!!"
                "\n!!!                                                                     !!!"
                  "\n        Please enter a valid %s from the options provided            ",
                target_string);
            show_error_message(error_msg);

        }
    }
}

/**
 * @brief Shows error message for invalid input using predefined art
 * @param msg The message string to include inside the art
 * 
*/
void show_error_message(char *msg){
    printf("\n\033[1;31m"); // Set text color to red
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!!!                                                                     !!!\n");
    printf("!!!                              ERROR:                                 !!!");
    printf("%s", msg);
    printf("\n!!!                                                                     !!!\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
     printf("\033[0m"); // Reset text color
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
    char error_msg[MAX_MSG_LEN *2];

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
                    sprintf(error_msg,
                                    "\n!!!                          Invalid input                              !!!"
                                    "\n!!!                                                                     !!!"
                                    "\n!!!        Please enter a string with length between %d and %d,         !!!"
                                    "\n!!!        containing only alphabetic or alphanumeric characters        !!!",MIN_STRING_LEN,MAX_STRING_LEN);
                    show_error_message(error_msg);
                }
                break;

            case INTEGER:
                // Validate integer input
                if (sscanf(buffer, "%d", (int *)input_buffer) == 1 && !is_alphanumeric_or_alphabetic(buffer)) {
                    valid = true;
                } else {
                    show_error_message(
                                    "\n!!!                          Invalid input                              !!!"
                                    "\n!!!                                                                     !!!"
                                    "\n!!!                    Please enter a valid integer                     !!!");
                }
                break;

            case FLOAT:
                // Validate float input
                if (sscanf(buffer, "%f", (float *)input_buffer) == 1 && !is_alphanumeric_or_alphabetic(buffer)) {
                    valid = true;
                } else {
                    show_error_message(
                                    "\n!!!                          Invalid input                              !!!"
                                    "\n!!!                                                                     !!!"
                                    "\n!!!                  Please enter a valid float number                  !!!");
                }
                break;

            case SCORE:
                // Validate score input (numeric and within range)
                if (sscanf(buffer, "%f", &score) == 1 && score <= TOTAL_SCORE && !is_alphanumeric_or_alphabetic(buffer)) {
                    *(float *)input_buffer = score;
                    valid = true;
                } else {
                    sprintf(
                        error_msg,
                        "\n!!!                          Invalid input                              !!!"
                        "\n!!!                                                                     !!!"
                        "\n!!!      Please enter a numerical value less than or equal to %d       !!!",
                        TOTAL_SCORE
                    );
                    show_error_message(error_msg);
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
 * @return The number the user enters which represents the action they want to perform.
 */
int get_main_program_choice() {

    int userselection;
    int options[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len_options = sizeof(options) / sizeof(options[0]);
    char option_art[ART_SIZE];
    // printf("len opt: %d", len_options);
    // Store the ASCII art in the buffer
    if(!greet_user){
        clear_terminal();
    }
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
    validate_input_choices(prompt, STRING, yes_no_options, response, sizeof(yes_no_options));

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
        show_error_message("!!!                       Memory allocation failed                        !!!");
        // printf("Memory allocation failed!\n");
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
        error_msg = 
                    "\n!!!                          Invalid input                              !!!"
                    "\n!!!                                                                     !!!"
                    "\n!!!           A student with this roll number already exists            !!!"
                    "\n!!!                  Please enter a unique roll number                  !!!";
        show_error_message(error_msg);
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
            error_msg = 
                        "\n!!!                          Invalid input                              !!!"
                        "\n!!!                                                                     !!!"
                        "\n!!!                     That course already exists                      !!!"
                        "\n!!!                   Please enter a unique course name                 !!!";
            show_error_message(error_msg);
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
    show_success_message("*             Successfully added the student to the database            *");
    auto_sort_save();// auto sort and save the records after adding new record(auto save is coming soon!!!!!)
    if (repeat_action("add another record",&add_again)){
        add_student(students_array,student_count);
    }
    //auto_sort_save_record(*students_array, *student_count); // Sort and save student records(coming soon...)
}


/**
 * @brief Display information of all students.
 * 
 */
void display_all_students() {
    int display_again;
    char *header_msg;
    clear_terminal();
    if (student_count <= 0) {
        show_no_data_err("display");
        return;
    }
    header_msg = "@@                  ----< DISPLAYING ALL THE STUDENTS RECORD >----                @@";
    show_header_art(header_msg);
    printf("\n");
    for (int i = 0; i < student_count; i++) {
        display_student_info(&students[i], i);
    }
}

/**
 * @brief Display information of a single student in a formatted way.
 *This is what the format mean ( please note that the formatting not perfect and may change depending on the actual value of variables):
    %-25c:
        %-: Left-align the string in the given field.
        25: Minimum field width of 15 characters.
        s: Format as a character.
    %-15s:
        %-: Left-align the string in the given field.
        15: Minimum field width of 15 characters.
        s: Format as a string.
 * 
 * @param student Pointer to the student structure.
 * @param student_index Index of the student in the array.
 */
void display_student_info(struct Student *student, int student_index) {
   
    printf("\n================================================================================\n");
    printf("                          STUDENT %d: %s                          \n", student_index + 1, student->name);
    printf("================================================================================\n");
    printf("%-25c  %-15s: %s \n", ' ',"Department", student->department);
    printf("%-25c  %-15s: %d \n", ' ',"Roll Number", student->roll_number);
    printf("================================================================================\n");
    printf("                           COURSES AND SCORES                               \n");
    printf("--------------------------------------------------------------------------------\n");

    for (int j = 0; j < MAX_COURSES; j++) {
        printf("%-25c  %-15s : %.2f \n", ' ',student->courses[j], student->scores[j]);
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("%-25c  %-15s: %.2f \n", ' ',"Average", student->average);
    printf("%-25c  %-15s: %s \n", ' ',"Grade", student->grade);
    printf("================================================================================\n");
}

/**
 * @brief Searches for a student by their roll number in the  array of students.
 * 
 * This function prompts the user to enter a roll number and searches through the array
 * of available students to find a match. It prints a visual indication of progress
 * while searching and returns the index of the student if found, otherwise returns -1.
 * 
 * @param purpose The reason why we are searching. This is necessary because when we want to
 * modify or delete a record, we have to first search for that record by roll number, hence, this function can be 
 * reused for those other purposes
 * 
 * @return int Index of the student in the array if found, -1 if not found or no students available.
 */
int search_by_roll(char *purpose) {
    if (student_count > 0) {
        int roll_num_to_search;
        // char *error_msg;
        char prompt[MAX_STRING_LEN];
        
        // Prompt user for roll number input
        sprintf(prompt,"\n--> Enter the roll number to %s: ",purpose);
        validate_input_data(prompt, &roll_num_to_search, INTEGER, 0, 0);
        
        printf("\n<<<<<<<<-- Please wait while I query the database: "); // Print initial message

        // Simulate querying delay with visual feedback
        bool found = false;
        for (int i = 0; i < student_count; i++) {
            printf("* "); // Visual feedback to indicate progress
            fflush(stdout); // Flush stdout to ensure immediate printing of '*'
            sleep(1);   // Simulate querying delay (replace with appropriate delay function)
            
            if (roll_num_to_search == students[i].roll_number) {
                found = true;
                return i; // Return index of the student if found
            }
        }
        
        // Print error message if student with roll number not found
        if (!found) {
            show_not_found_err_msg();
        }
    } else {
        show_no_data_err("search");
    }
    
    return -1; // Return -1 indicating no match found
}

void show_not_found_err_msg(){
    char *error_msg;
    error_msg = "\n!!!                          Invalid input                              !!!"
                "\n!!!                                                                     !!!"
                "\n!!!              There is no student with that roll number              !!!"
                "\n!!!                    Please confirm and try again                     !!!" ;
    show_error_message(error_msg);

}

/**
 * @brief Searches for a student by roll number and displays their information if found.
 * 
 * This function calls search_by_roll() to find a student by their roll number.
 * If a student is found, it retrieves the student's information and displays it using
 * display_student_info().
 */
void show_found_student() {
    char *header_msg;
    int search_again;
    header_msg = "@@                 ---< SEARCHING FOR A STUDENT BY ROLL NUMBER >---               @@";
    clear_terminal();
    show_header_art(header_msg);
    int student_index = search_by_roll("search for"); //get the index of the student by their roll number
    if (student_index != -1) {
        struct Student *found_student = &(students[student_index]);
        display_student_info(found_student, student_index);
    }

    if (repeat_action("search for another record",&search_again)){
            show_found_student();
        }
}

/**
 * Modifies student data based on user input.
 *
 * The function first searches for the student by roll number, displays the student information
 * Then user can modify whatever they want
 */
void modify_student_data() {
    char *error_msg,*header_msg;
    int update_options[] = {1,2,3,4,5,6};
    int modify_again;

    header_msg = "@@                 ----< MODIFYING A STUDENT'S RECORD >----                       @@";
    clear_terminal();
    show_header_art(header_msg);
    
    if (student_count > 0){
            // Find student by roll number
        int student_index = search_by_roll("modify");
        if (student_index != -1) {
            struct Student *student = &(students[student_index]);
            // Display student information
            display_student_info(student,student_index);

            // Get user choice for modification
            int choice;
            char option_art[ART_SIZE];
            
            sprintf(option_art,
            "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
            "@@                                                                                @@\n"
            "@@                            SELECT WHAT TO UPDATE                               @@\n"
            "@@                            ---------------------                               @@\n"
            "@@                            1. Student's name                                   @@\n"
            "@@                            2. Student's department                             @@\n"
            "@@                            3. Student's roll number                            @@\n"
            "@@                            4. Course name                                      @@\n"
            "@@                            5. Course score                                     @@\n"
            "@@                            6. Exit                                             @@\n"
            "@@                                                                                @@\n"
            "           --> Please type a number to select an option from above: ");
            validate_input_choices(option_art,INTEGER,update_options,&choice,sizeof(update_options)/sizeof(update_options[0]));

            // Update based on user choice
            switch (choice) {
                case 1:
                    validate_input_data("\n--> Enter new name: ",student->name,STRING,MAX_STRING_LEN,MIN_STRING_LEN);
                    break;
                case 2:
                    validate_input_data("\n--> Enter new department: ",student->department,STRING,MAX_STRING_LEN,MIN_STRING_LEN);
                    break;
                case 3: {
                    int new_roll;
                    while (true) {
                        validate_input_data("\n--> Enter new roll number: ",&new_roll,INTEGER,0,0);
                        if (!is_duplicate_roll_num( new_roll)) {
                            student->roll_number = new_roll;
                            break;
                        } else {
                            error_msg = "\n!!!                          Invalid input                              !!!"
                                        "\n!!!                                                                     !!!"
                                        "\n!!!           A student with this roll number already exists            !!!"
                                        "\n!!!                  Please enter a unique roll number                  !!!";
                            show_error_message(error_msg);
                        }
                    }
                    break;
                }
                case 4:
                    update_course(student, true);//modify the name of a course
                    break;
                case 5:
                    update_course(student, false);//modify the score of a course
                    auto_sort_save();// auto sort and save the records after modifying score(s) of the course(s) of a student's record(auto save is coming soon!!!!!)
                    break;
                case 6:
                    exit(1);
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
            }
            show_success_message("*               Successfully updated the student's record               *");
            if (repeat_action("modify a record again",&modify_again)){
                modify_student_data();
            }
        }else {
            show_not_found_err_msg(); //the student whose roll number was entered is not in the database
        }
    }else {
        show_no_data_err("modify");
    }
    
}

/**
 * Updates a course's name or score for a given student.
 *
 * @param student Pointer to the student to be updated.
 * @param update_name Boolean indicating whether to update the course name (true) or score (false).
 */
void update_course(struct Student *student, bool update_name) {
    int course_num;
    int course_options[] = {1,2,3};
    char *header_msg;
    char prompt[MAX_MSG_LEN];

    // Display courses and their scores
    header_msg = "@@                  ----< SELECT THE COURSE TO UPDATE >----                        @@\n";
    clear_terminal();
    printf("\n====================================================================================\n");
    printf("                                 COURSES AND SCORES                                  \n");
    printf("-------------------------------------------------------------------------------------\n");
    show_header_art(header_msg);
    printf("\n");
    for (int j = 0; j < MAX_COURSES; j++) {
        printf("%-25c %d. %-15s : %-15.2f \n", ' ', j + 1,student->courses[j], student->scores[j]);
    }
    
    validate_input_choices( "\n--> Please type a number to select an option from above: ",INTEGER,course_options,&course_num,sizeof(course_options)/sizeof(course_options[0]));
    course_num--;  // Convert to 0-based index

    // Update course name or score based on input
    if (update_name) {
        header_msg = "@@                     ----<  UPDATING COURSE NAME  >----                          @@";
        show_header_art(header_msg);
        sprintf(prompt,"\n--> Enter new course name (old name is %s): ",student->courses[course_num]);
        validate_input_data(prompt,student->courses[course_num],STRING,MAX_STRING_LEN,MIN_STRING_LEN);
    } else {
        header_msg = "@@                  ----<   UPDATING THE COURSE SCORE  >----                       @@";
        show_header_art(header_msg);
        sprintf(prompt,"\n--> Enter new course name (old score for the course %s is %.2f): ",student->courses[course_num],student->scores[course_num]);
        validate_input_data(prompt,&student->scores[course_num],SCORE,sizeof(float),0);

    }

    // Update average score and grade
    student->average = 0.0f;
    for (int i = 0; i < MAX_COURSES; i++) {
        student->average += student->scores[i];
    }
    student->average /= MAX_COURSES;

    strcpy(student->grade, student->average >= PASS_THRESHOLD ? "Pass" : "Fail");
   
}

/**
 * Deletes a single student from the list of students.
 *
 */
void delete_a_student() {
    int user_response;
    int delete_again;

    int index_of_student;
    char warning_msg[MAX_MSG_LEN * 3],*header_msg;
    header_msg ="@@                 ----< DELETING RECORD(S) FROM THE DATABASE >----                @@";

    clear_terminal();
    show_header_art(header_msg);
    index_of_student = search_by_roll("delete");
    // printf("%d", index_of_student);

    if (index_of_student > -1){
        struct Student *student = &(students[index_of_student]);

        // Display student information
        display_student_info(student,index_of_student);
        printf("\n\033[1;33m"); // Set text color to yellow
        sprintf(warning_msg,
            "\n\033[1;33m" // Set text color to yellow
            "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
            "\n!!!                                                                     !!!"
            "\n!!!                              WARINING:                              !!!"
            "\n!!!                                                                     !!!"
            "\n                 This will delete %s's data permanently                      "
            "\n                   Do you want to proceed!!!? Y/N: "
            "\033[0m",
            student->name
        );
        
        validate_input_choices(warning_msg,STRING,yes_no_options,&user_response,sizeof(yes_no_options)/sizeof(yes_no_options[0]));
        
        if (user_response == 'y') {
            printf("\n=============================================================================\n");
            printf("\n                   DELETING %s FROM THE DATABASE                   \n", student->name);
            printf("\n=============================================================================\n");

            for (int i = index_of_student; i < student_count - 1; i++) {
                (students)[i] = (students)[i + 1];
            }
            struct Student *new_student_list = realloc(students, (student_count - 1) * sizeof(struct Student)); // Reallocate memory to shrink the list
            if (!new_student_list && (student_count - 1) > 0) {
                show_error_message("!!!                       Memory allocation failed                        !!!");
                return;
            }

            students = new_student_list;
            (student_count)--; // Decrement the total number of students
            show_success_message("*                     Student removed successfully!                      *");
            auto_sort_save(); // auto sort and save the records after deleting(auto save is coming soon!!!!!)
        } else {
            show_info_message("*                           Deletion canceled!                           *");
        }
    }else {
        show_not_found_err_msg();
    }
    
    if (repeat_action("delete another record",&delete_again)){
        delete_a_student();
    }    
}

/**
 * Deletes all students from the list of students.
 * 
 * This function prompts the user with a warning message about deleting all student records permanently.
 * If the user confirms the action by typing 'y', it frees the memory allocated for the student records,
 * sets the student list to NULL, and updates the student count to 0. If the user cancels the action by typing 'n',
 * it displays a cancellation message.
 */
void delete_all_students() {
    int user_response;
    char warning_msg[MAX_MSG_LEN * 2]; // Buffer for the warning message
    char *header_msg = "@@                 ----< DELETING RECORD(S) FROM THE DATABASE >----               @@";

    clear_terminal();  // Clear the terminal screen
    show_header_art(header_msg);  // Display the header art

    // Create the warning message with yellow text color
    sprintf(warning_msg,
        "\n\033[1;33m" // Set text color to yellow
        "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
        "\n!!!                                                                     !!!"
        "\n!!!                              WARNING:                              !!!"
        "\n!!!                                                                     !!!"
        "\n!!!              This will delete all records permanently               !!!"
        "\n                     Do you want to proceed!!!? Y/N: "
        "\033[0m" // Reset text color
    );
    
    // Validate the user's input choice (Y/N)
    validate_input_choices(warning_msg, STRING, yes_no_options, &user_response, 2);

    // Check user's response
    if (user_response == 'y') {
        // User confirmed the deletion
        printf("\n=============================================================================\n");
        printf("\n                   DELETING ALL STUDENTS FROM THE DATABASE                   \n");
        printf("\n=============================================================================\n");

        free(students);  // Free the memory allocated for the student records
        students = NULL;  // Set the student list to NULL
        student_count = 0;  // Reset the student count to 0

        // Display success message
        show_success_message("*                   All students deleted successfully!                   *");
    } else {
        // User canceled the deletion
        show_info_message("*                           Deletion canceled!                           *");
    } 
}

/**
 * Handles the deletion actions based on user input: delete a single student or all students.
 *
 */
void delete_action() {
    int selection;
    int valid_choices[] = {1, 2,3};
    char option_art[ART_SIZE];
        
    sprintf(option_art,
    "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
    "@@                                                                                @@\n"
    "@@                            SELECT WHAT TO DELETE                               @@\n"
    "@@                            ---------------------                               @@\n"
    "@@                            1. Delete a student                                 @@\n"
    "@@                            2. Delete all students                              @@\n"
    "@@                            3. Exit                                             @@\n"
    "@@                                                                                @@\n"
    "           --> Please type a number to select an option from above: ");
    if (student_count > 0) {
        validate_input_choices(option_art,INTEGER,valid_choices,&selection,sizeof(valid_choices)/sizeof(valid_choices[0]));
        switch (selection) {
            case 1:
                delete_a_student();
                break;
            case 2:
                delete_all_students();
                break;
            case 3:
                exit(1);
                break;
            default:
                printf("Invalid choice.\n"); //this line is negligible because checking for invalid option 
                                             //is already handled inside the validate_input_choices function
                break;
        }
    } else {
        show_no_data_err("delete");
    }
}

void show_success_message(char *msg) {
    printf("\n\033[1;32m"); // Set text color to green
    printf("*************************************************************************\n");
    printf("*                                                                       *\n");
    printf("*                          SUCCESS:                                     *\n");
    printf("*                                                                       *\n");
    printf("%s\n", msg);
    printf("*                                                                       *\n");
    printf("*************************************************************************\n");
    printf("\033[0m"); // Reset text color
}

void show_info_message(char *msg) {
    printf("\n\033[1;34m"); // Set text color to blue
    printf("*************************************************************************\n");
    printf("*                                                                       *\n");
    printf("*                          INFORMATION:                                 *\n");
    printf("*                                                                       *\n");
    printf("    %s\n", msg);
    printf("*                                                                       *\n");
    printf("*************************************************************************\n");
    printf("\033[0m"); // Reset text color
}

/**
 * @brief Display error message for empty student record
 * 
 * If user tries to display,modify,delete or search records and the student array is empty(no record added),
 * This function tells user that no data exists for the action to be performed.
 * @param action The action being performed, e.g., display , delete, modify and search.
*/
void show_no_data_err(char *action){
    printf("\n\033[1;31m"); // Set text color to red
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!!!                                                                     !!!\n");
    printf("!!!                              ERROR:                                 !!!\n");
    printf("!!!                                                                     !!!\n");
    if(strlen(action) == 7){// if action is display(len display is 7)
        printf("!!!                      Cannot %s record(s)                       !!!\n",action);

    }else if (strlen(action)==6){ // actions with lenght 6 such as delete,search,modify
        printf("!!!                       Cannot %s record(s)                       !!!\n",action);

    }else if (strlen(action) == 4){// actions with lenght 4 such as sort
        printf("!!!                        Cannot %s record(s)                        !!!\n",action);
    }
    printf("!!!                          No data available                          !!!\n");
    printf("!!!                                                                     !!!\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
     printf("\033[0m"); // Reset text color
}

/**
 * Compare function for sorting students in ascending order based on average.
 * 
 * @param a Pointer to the first student.
 * @param b Pointer to the second student.
 * @return 1 if the average of 'b' is less than 'a', -1 if greater, 0 if equal.
 */
int compare_funct_ascend(const void *a, const void *b) {
    float avg_a = ((struct Student *)a)->average;
    float avg_b = ((struct Student *)b)->average;

    if (avg_b < avg_a) {
        return 1;   // Return 1 to indicate 'b' should come after 'a' (ascending order)
    } else if (avg_b > avg_a) {
        return -1;  // Return -1 to indicate 'b' should come before 'a' (ascending order)
    } else {
        return 0;   // Return 0 if averages are equal
    }
}

/**
 * Compare function for sorting students in descending order based on average.
 * 
 * @param a Pointer to the first student.
 * @param b Pointer to the second student.
 * @return 1 if the average of 'a' is less than 'b', -1 if greater, 0 if equal.
 */
int compare_funct_descend(const void *a, const void *b) {
    float avg_a = ((struct Student *)a)->average;
    float avg_b = ((struct Student *)b)->average;

    if (avg_a < avg_b) {
        return 1;   // Return 1 to indicate 'a' should come after 'b' (descending order)
    } else if (avg_a > avg_b) {
        return -1;  // Return -1 to indicate 'a' should come before 'b' (descending order)
    } else {
        return 0;   // Return 0 if averages are equal
    }
}

/**
 * Sorts an array of students based on their average score.
 * 
 * @param order The order to sort by: 1 for ascending, 2 for descending.
 * @param all_stud Pointer to the array of students.
 * @param tot_stud_num Total number of students in the array.
 * @return A string indicating the sort order ("ascending" or "descending"), or NULL if no students to sort.
 */
void sort_students(char *order) {
    // Sort the students based on the specified order
    if (strcmp(order, "ascending") == 0) {  // Sort in ascending order
        // Use qsort to sort students in ascending order of their average score
        qsort(students, student_count, sizeof(struct Student), compare_funct_ascend);
    } else if (strcmp(order, "descending") == 0) {  // Sort in descending order
        // Use qsort to sort students in descending order of their average score
        qsort(students, student_count, sizeof(struct Student), compare_funct_descend);
    } else {
        // If an invalid order is specified, print an error message and return NULL
        printf("\n!!!Invalid Sort Order!!!\n!!!Please choose 1 for ascending or 2 for descending!!!\n");
    }
}

void sort_operation(){
    char *header_msg, *prompt;
    int user_order;
    int order_options[] = {1,2,3};
    int sort_again;
    char success_msg[MAX_MSG_LEN];

    clear_terminal();
    header_msg = "@@             ----< SORTING THE STUDENTS BY ORDER OF AVERAGE MARK >----           @@\n";
    show_header_art(header_msg);

    // Check if there are any students to sort
    if (student_count > 0) {
        prompt = 
            "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
            "@@                                                                                @@\n"
            "@@                            SELECT THE SORT ORDER                               @@\n"
            "@@                            ---------------------                               @@\n"
            "@@                            1. Ascending order                                  @@\n"
            "@@                            2. Descending order                                 @@\n"
            "@@                            3. Exit                                             @@\n"
            "@@                                                                                @@\n"
            "           --> Please type a number to select an option from above: ";

        validate_input_choices(prompt,INTEGER,order_options,&user_order,3);
        auto_sort = true;
        if (user_order == 1){
            auto_sort_order = "ascending";
            sort_students(auto_sort_order);
        }else if (user_order == 2){
            auto_sort_order = "descending";
            sort_students(auto_sort_order);
        }
        sprintf(success_msg,"*      Successfully sorted the student records in %s order      *",auto_sort_order);
        show_success_message(success_msg);
        if (repeat_action("sort records by a different order",&sort_again)){
            sort_operation();
        }
    }else {
        show_no_data_err("sort");
    }
    
}

void auto_sort_save(){
    if (auto_sort){
        sort_students(auto_sort_order);
    }
}