#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

struct Student {
    char name[MAX_NAME_LENGTH];
    int grade;
    int id;
    int age;
    char gender;
    char password[MAX_PASSWORD_LENGTH];
    struct Student* next;
};

struct StudentList {
    struct Student* head;
};

struct StudentList* createStudentList() {
    struct StudentList* newList = (struct StudentList*)malloc(sizeof(struct StudentList));
    newList->head = NULL;
    return newList;
}

void main_screen();
void adminMode();
void userMode();
void addStudent();
void removeStudent();
void viewStudentRecord();
void viewAllRecords();
void editAdminPassword();
void editStudentGrade();
char adminPassword[MAX_PASSWORD_LENGTH] = "1234";

void clearScreen()
{
    system("cls");
}

void delay(int milliseconds)
{
    usleep(milliseconds * 1000); // usleep takes time in microseconds, so we multiply milliseconds by 1000
}

void PrintStudentById(struct StudentList* list, int id) {
    struct Student* current = list->head;
    while (current != NULL) {
        if (current->id == id) {
            printStudentDetails(current);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found.\n", id);
}
void PrintGradeById(struct StudentList* list, int id) {
    struct Student* current = list->head;
    while (current != NULL) {
        if (current->id == id) {
            view_your_grade(current);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found.\n", id);
    delay(1500);
    clearScreen();
    view_student_mode(list);
}

void editStudentGrade(struct StudentList* students) {
    int newgrade;
    int id;
    printf("Enter the ID of the student you want to edit: ");
    scanf("%d", &id);
    printf("Enter the new grade: ");
    scanf("%d", &newgrade);
    struct Student* current = students->head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Student found. Editing Grade...\n");
            printf("Student details before editing:\n");
            printStudentDetails(current);
            current->grade = newgrade;
            printf("Student details after editing:\n");
            printStudentDetails(current);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found.\n", id);
}

void edit_your_password(struct StudentList* student){
    char newpass[MAX_PASSWORD_LENGTH];
    int id;
    printf("Enter your ID: ");
    scanf("%d", &id);
    printf("Enter the new password: ");
    scanf("%s", newpass);
    struct Student* current = student->head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Student found. Editing password...\n");
            delay(500);
            printf("Student details before editing:\n");
            printStudentDetails(current);
            strcpy(current->password, newpass);
            printf("Student details after editing:\n");
            printStudentDetails(current);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found.\n", id);
}

void edit_your_name(struct StudentList* student){
    char newname[MAX_NAME_LENGTH];
    int id;
    printf("Enter your ID: ");
    scanf("%d", &id);
    printf("Enter the new name: ");
    scanf("%s", newname);
    struct Student* current = student->head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Student found. Editing name...\n");
            delay(500);
            printf("Student details before editing:\n");
            printStudentDetails(current);
            strcpy(current->name, newname);
            printf("Student details after editing:\n");
            printStudentDetails(current);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found.\n", id);
}
void view_your_grade(struct Student* student){
    printf("Name: %s\n", student->name);
    printf("Grade: %d\n", student->grade);
}

void printStudentDetails(struct Student* student) {
    printf("Name: %s\n", student->name);
    printf("Grade: %d\n", student->grade);
    printf("ID: %d\n", student->id);
    printf("Age: %d\n", student->age);
    printf("Gender: %c\n", student->gender);
    printf("Password: %s\n\n", student->password);
}

void check_pass_id(struct StudentList* student){
    int id;
    char pass[MAX_PASSWORD_LENGTH];
    printf("Enter The ID: ");
    scanf("%d", &id);
    printf("Enter The Password: ");
    scanf("%s", &pass);
    struct Student* current = student->head;
    while (current != NULL) {
        if (current->id == id && strcmp(current->password, pass) == 0) {
            printf("Student found.\n");
            delay(2000);
            clearScreen();
            return;
        }
        current = current->next;
    }
        printf("Student not found.\n");
        delay(2000);
        clearScreen();
        main_screen(student);
}

void view_student_mode(struct StudentList* student){
    check_pass_id(student);
    int option;
    printf("__________________________STUDENT MODE__________________________\n\n");
    printf("Choose an option (1-4)\n");
    printf("1- VIEW YOUR GRADE\n");
    printf("2- EDIT YOUR PASSWORD\n");
    printf("3- EDIT YOUR NAME\n");
    printf("4- GO TO MAIN\n");
    scanf("%d", &option);
    if(option == 1){
        int id;
        printf("Enter your id: ");
        scanf("%d", &id);
        PrintGradeById(student, id);
        main_screen(student);
    }
    if(option == 2){
        edit_your_password(student);
        main_screen(student);
    }
    if(option== 3){
        edit_your_name(student);
        main_screen(student);
    }
    if(option== 4){
        clearScreen();
        delay(500);
        main_screen(student);
    }
}

void main_screen(struct Student* students){
    int mode;
    printf("__________________________STUDENT RECORD SYSTEM__________________________\n\n");
    printf("___Select Your Mode___\n");
    printf(" select (1) for USER MODE \n select (2) for STUDENT MODE\n select (3) for exit the program\n");
    scanf("%d", &mode);
    clearScreen();
    delay(500);
    if(mode == 1){

        adminMode();
    }
    else if(mode == 2){
        view_student_mode(students);
    }
    else if(mode ==3){
        exit(0);
    }
    else{
        printf("wrong choice!  Try again");
        delay(2000);
        clearScreen();
        main_screen(students);
    }
}

void adminMode() {
    struct StudentList* students = createStudentList();
    char password[MAX_PASSWORD_LENGTH];
    int attempts = 3;
    while (attempts > 0) {
        printf("Enter admin password: ");
        scanf("%s", password);
        if (strcmp(password, adminPassword) == 0) {
            printf("Login successful\n");
            delay(500);
            clearScreen();
            int choice;
            do {
                printf("\n_________________________Admin Menu:________________________\n");
                printf("1. Add student record\n");
                printf("2. Remove student record\n");
                printf("3. View student record\n");
                printf("4. View all records\n");
                printf("5. Edit admin password\n");
                printf("6. Edit student grade\n");
                printf("0. Exit\n");
                printf("Enter choice: ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        clearScreen();
                        handleAddingStudents(students);
                        break;
                    case 2:
                        clearScreen();
                        handleRemovingStudent(students);
                        break;
                    case 3:
                        clearScreen();
                            int id;
                            printf("Enter the ID of the student you want to print details for (or 0 to print all): ");
                            scanf("%d", &id);
                            if (id == 0) {
                                printStudents(students);
                            } else {
                                PrintStudentById(students, id);
                            }
                        break;
                    case 4:
                        clearScreen();
                        printStudents(students);
                        break;
                    case 5:
                        clearScreen();
                        editAdminPassword();
                        break;
                    case 6:
                        clearScreen();
                        editStudentGrade(students);
                        break;
                    case 0:
                        printf("Exiting admin mode\n");
                        clearScreen();
                        main_screen(students);
                        break;
                    default:
                        printf("Invalid choice\n");
                }
            } while (choice != 0);
            break;
        } else {
            attempts--;
            if (attempts > 0) {
                printf("Invalid password. %d attempts left.\n", attempts);
            } else {
                printf("Too many failed attempts. Exiting.\n");
            }
        }
    }
}

struct Student* createStudent(char name[], int grade, int id, int age, char gender, char password[]) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->grade = grade;
    newStudent->id = id;
    newStudent->age = age;
    newStudent->gender = gender;
    strcpy(newStudent->password, password);
    newStudent->next = NULL;
    return newStudent;
}

void addStudent(struct StudentList* list, struct Student* newStudent) {
    if (list->head == NULL) {
        list->head = newStudent;
    } else {
        struct Student* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
}

void handleAddingStudents(struct StudentList* students) {
        char choice;
        char name[MAX_NAME_LENGTH];
        int grade, id, age;
        char gender;
        char password[MAX_PASSWORD_LENGTH];
        printf("Enter name of the student: ");
        scanf("%s", name);

        printf("Enter grade of the student: ");
        scanf("%d", &grade);
        if(grade > 100){
            printf("Invalid choice Try Again! ");
            delay(1000);
            clearScreen();
            handleAddingStudents(students);
        }

        printf("Enter ID of the student: ");
        scanf("%d", &id);
        struct Student* current = students->head;
        while (current != NULL) {
            if (current->id == id) {
                clearScreen();
                printf("Invalid choice Try Again! ");
                delay(1000);
                clearScreen();
                handleAddingStudents(students);
        }
        current = current->next;
        }

        printf("Enter age of the student: ");
        scanf("%d", &age);

        printf("Enter gender of the student(m/f): ");
        scanf(" %c", &gender);
        if(gender == 'm' || gender == 'M' || gender == 'f' || gender == 'F'){
        }
        else{
            clearScreen();
            printf("Invalid choice Try Again! ");
            delay(1000);
            clearScreen();
            handleAddingStudents(students);
        }

        printf("Enter password of the student: ");
        scanf("%s", password);

        struct Student* newStudent = createStudent(name, grade, id, age, gender, password);
        addStudent(students, newStudent);
        printf("Student Added Successfully");
        delay(1000);
        clearScreen();
}

void printStudents(struct StudentList* list) {
    struct Student* current = list->head;
    printf("\nDetails of the students:\n");
    while (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("Grade: %d\n", current->grade);
        printf("ID: %d\n", current->id);
        printf("Age: %d\n", current->age);
        printf("Gender: %c\n", current->gender);
        printf("Password: %s\n\n", current->password);
        current = current->next;
    }
}

void handleRemovingStudent(struct StudentList* students) {
    char choice;
    int idToRemove;
    do {
        printf("Do you want to remove any student? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y') {
            printf("Enter the ID of the student you want to remove: ");
            scanf("%d", &idToRemove);
            removeStudent(students, idToRemove);
            printStudents(students);
        }
    } while (choice == 'y');
}

void removeStudent(struct StudentList* list, int idToRemove) {
    struct Student* current = list->head;
    struct Student* previous = NULL;

    while (current != NULL) {
        if (current->id == idToRemove) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Student with ID %d removed successfully.\n", idToRemove);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Student with ID %d not found.\n", idToRemove);
}

void editAdminPassword() {
    printf("Enter new admin password: ");
    scanf("%s", adminPassword);
    printf("Admin password updated successfully.\n");
}


int main()
{
    struct StudentList* students = createStudentList();
    main_screen(students);
    return 0;
}
