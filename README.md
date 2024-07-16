# Student Record Management

The student record management system is an essential tool to help faculty members properly manage data relating to students. Students are identified by their roll numbers which are integer values and can have as many courses as possible.

The system automatically calculates students' average based on their scores per the course they took.

We also display some logos which were generated using an extension called  Convert To ASCII Art in vscode.

## Requirements

The only requirement for this program is the json-c library/API. This is essential for serialisation and deserialisation of data to json files. We decided to save data to json file because it is more visually appealing and easy to read and understand.

For more information about the json-c API, please read the documentation [here](https://json-c.github.io/json-c/).

If you are running your c program in a linux environment like you can easily install the library using the following commands:

```bash
# For Debian-based Distributions (like Ubuntu)
sudo apt update
sudo apt install libjson-c-dev
```

```bash
# For RedHat-based Distributions (like CentOS)
sudo yum install json-c json-c-devel
```

If you are running on Windows, it may be a bit difficult. Reference the json-c repository [here](https://github.com/json-c/json-c) on how you can install the library.
However, the easiest solution may be to enable Windows subsystem for Linux (WSL) on your Windows PC and install a Linux distro in the WSL. Then you can use any of the commands above to install the library.

## Run Program

You can easily run the program by cloning this repository (note that only collaborators can have access to this repository):

```bash
git clone https://github.com/COS1-Group/Student-Record-System.git
```

Then compile the program like so:

```bash
gcc Student_Record_System.c -o Student_Record_System.exe -ljson-c # the flag -ljson-c is essential to link the json-c API to the program
```
Then to run the program:

```bash
./Student_Record_System.exe
```


Questions
Project Title: Student Record System

Create a simple Student Record System in C that allows users to manage student information. The program should include the following functionality:

Initial Setup:
   - Create a new C project using JetBrains Clion (or your preferred development environment).

   - Write a program that displays a welcome message and prompts the user to enter their name. The program should greet the user by their name.

Data Storage:
   - Implement storage for student information, including name, roll number, and marks, using appropriate data types.

Input and Output:
   - Add a feature to input a student's marks and display whether the student has passed or failed based on a passing threshold (e.g., marks above 40 are considered passing).

Student Records Management:
   - Implement a loop that allows the user to input information for multiple students until the user decides to exit.

   - Create an array to store information for multiple students, with the ability to add, remove, and modify student records.

   - Implement functions for adding, modifying, and displaying student records. Ensure these functions take appropriate arguments and return relevant information.

Memory Management:
   - Use dynamic memory allocation for student records and ensure memory is freed when no longer needed.

File Operations:
   - Implement the ability to save student records to a text file and load student records from a text file, storing information such as name, roll number, and marks.

Search Functionality:
   - Allow users to search for a student by their roll number and display the relevant information.

Calculations and Sorting:
   - Calculate and display the average marks for all students.

   - Provide an option to sort student records based on marks in ascending or descending order.