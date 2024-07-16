#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function prototypes
void welcomeUser();
void addStudent();
void modifyStudent();
void displayStudents();
void saveToFile();
void loadFromFile();
void searchStudent();
void calculateAverageMarks();
void sortStudents(int ascending);

// Struct for storing student information
typedef struct {
    char name[50];
    int rollNumber;
    float marks;
} Student;


Student* students = NULL;
int studentCount = 0;
const float PASSING_MARKS = 40.0;

int main() {
    welcomeUser();
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Modify Student\n");
        printf("3. Display Students\n");
        printf("4. Save to File\n");
        printf("5. Load from File\n");
        printf("6. Search Student\n");
        printf("7. Calculate Average Marks\n");
        printf("8. Sort Students by Marks\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: modifyStudent(); break;
            case 3: displayStudents(); break;
            case 4: saveToFile(); break;
            case 5: loadFromFile(); break;
            case 6: searchStudent(); break;
            case 7: calculateAverageMarks(); break;
            case 8: 
                printf("Sort by Marks: 1. Ascending 2. Descending\n");
                int order;
                scanf("%d", &order);
                sortStudents(order == 1);
                break;
            case 9: exit(0); break;
            default: printf("Invalid choice!\n");
        }
    }
    
    return 0;
}

void welcomeUser() {
    char name[50];
    printf("Welcome to the Miva Student Record System\n");
    printf("Please enter your name: ");
    scanf("%s", name);
    printf("Hello, %s!\n", name);
}



void addStudent() {
    studentCount++;
    students = (Student*) realloc(students, studentCount * sizeof(Student));
    
    printf("Enter name: ");
    scanf("%s", students[studentCount - 1].name);
    printf("Enter roll number: ");
    scanf("%d", &students[studentCount - 1].rollNumber);
    printf("Enter marks: ");
    scanf("%f", &students[studentCount - 1].marks);
    
    if (students[studentCount - 1].marks >= PASSING_MARKS) {
        printf("%s has passed.\n", students[studentCount - 1].name);
    } else {
        printf("%s has failed.\n", students[studentCount - 1].name);
    }
}


void modifyStudent() {
    int rollNumber, found = -1;
    printf("Enter roll number to modify: ");
    scanf("%d", &rollNumber);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            found = i;
            break;
        }
    }
    
    if (found != -1) {
        printf("Enter new name: ");
        scanf("%s", students[found].name);
        printf("Enter new marks: ");
        scanf("%f", &students[found].marks);
    } else {
        printf("Student not found!\n");
    }
}

void displayStudents() {
    for (int i = 0; i < studentCount; i++) {
        printf("Name: %s, Roll Number: %d, Marks: %.2f\n", students[i].name, students[i].rollNumber, students[i].marks);
    }
}


void saveToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %d %.2f\n", students[i].name, students[i].rollNumber, students[i].marks);
    }
    
    fclose(file);
    printf("Records saved to file.\n");
}

void loadFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    studentCount = 0;
    free(students);
    students = NULL;
    
    while (!feof(file)) {
        studentCount++;
        students = (Student*) realloc(students, studentCount * sizeof(Student));
        fscanf(file, "%s %d %f", students[studentCount - 1].name, &students[studentCount - 1].rollNumber, &students[studentCount - 1].marks);
    }
    
    fclose(file);
    printf("Records loaded from file.\n");
}


void searchStudent() {
    int rollNumber, found = -1;
    printf("Enter roll number to search: ");
    scanf("%d", &rollNumber);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            found = i;
            break;
        }
    }
    
    if (found != -1) {
        printf("Name: %s, Roll Number: %d, Marks: %.2f\n", students[found].name, students[found].rollNumber, students[found].marks);
    } else {
        printf("Student not found!\n");
    }
}


void calculateAverageMarks() {
    float totalMarks = 0;
    for (int i = 0; i < studentCount; i++) {
        totalMarks += students[i].marks;
    }
    
    printf("Average Marks: %.2f\n", totalMarks / studentCount);
}

int compareAsc(const void *a, const void *b) {
    return ((Student*)a)->marks - ((Student*)b)->marks;
}

int compareDesc(const void *a, const void *b) {
    return ((Student*)b)->marks - ((Student*)a)->marks;
}

void sortStudents(int acending) {
    if (ascending) {
        qsort(students, studentCount, sizeof(Student), compareAsc);
    } else {
        qsort(students, studentCount, sizeof(Student), compareDesc);
    }
    printf("Students sorted.\n");
}

