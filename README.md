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

If you are running on Windows, it may be a bit difficult. Reference the json-c repository [here](https://github.com/json-c/json-c).
However, the easiest solution may be to enable Windows subsystem for Linux (WSL) on your Windows PC and install a Linux distro in the WSL.

## Run Program

You can easily run the program by using the command:
```bash
git clone https://github.com/COS1-Group/Student-Record-System.git
```
But note that only collaborators can have access to this repository. Then compile the program like so:

```bash
gcc Student_Record_System.c -o Student_Record_System.exe -ljson-c # the flag -ljson-c is essential to link the json-c API to the program
```

Then to run the program:

```bash
./Student_Record_System.exe
```