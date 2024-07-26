#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#define MAX_SEMESTERS 3
#define MAX_COURSES 2
#define MAX_STUDENTS 10000


//Global variabla declaration
char studentID[11];

//Declare structures for course detail and student detail
struct Course {
    char code[10];
    int creditHour;
    char grade[3];

};

struct Student {
    char studentCode[10];
    char studentName[50];
    int numSemesters;
    struct Course courseData[MAX_SEMESTERS][MAX_COURSES];
    double gpa[MAX_SEMESTERS];
    double cgpa[MAX_SEMESTERS];
};

struct Student students[MAX_STUDENTS];

// Declare of functions
int determineStudentID();
int calculateGPACGPA();
void staffMode();
void studentMode();

//Main function
int main() {
    //Variable declaration
    int studentCount = 0;
    int choice;
    int staffchoice;
    char staffIDentered[11];
    char staffPasswordentered[11];
    char staffID[] = "STAFFPASAR";
    char staffpassword[] = "PSKL057@#";

    do {
        //Logo
        printf("\n\t\t\t\t---------------------------------------------------------------------------------\n");
        printf("\t\t\t\t\t  _  _____  _     _____     _     ____   _    ____    _    ____  \n");
        printf("\t\t\t\t\t | |/ / _ \\| |   | ____|   | |   |  _ \\ / \\  / ___|  / \\  |  _ \\ \n");
        printf("\t\t\t\t\t | ' / | | | |   |  _|  _  | |   | |_) / _ \\ \\___ \\ / _ \\ | |_) |\n");
        printf("\t\t\t\t\t | . \\ |_| | |___| |__ | |_| |   |  __/ ___ \\ ___) / ___ \\|  _ < \n");
        printf("\t\t\t\t\t |_|\\_\\___/|_____|_____|\\___/    |_| /_/   \\_\\____/_/   \\_\\_| \\_\\\n");
        printf("\t\t\t\t\t                                                               \n");

        printf("\t\t\t\t---------------------------------------------------------------------------------\n");
        printf("\n\t\t\t\t\t\t\t--------------------------");
        printf("\n\t\t\t\t\t\t\t| Welcome to Kolej Pasar |");
        printf("\n\t\t\t\t\t\t\t--------------------------");
        printf("\n\t\t\t\t\t\t\t[1] Staff Mode");
        printf("\n\t\t\t\t\t\t\t[2] Student Mode");
        printf("\n\t\t\t\t\t\t\t[3] Quit");
        printf("\n\t\t\t\t\t\t\tEnter your choice : ");
        rewind(stdin);
        (void)scanf("%d", &choice);

        switch (choice) {
        case 1:
            do {
                printf("\n\t\t\t\t\t Please enter your staff ID : ");
                rewind(stdin);
                (void)scanf("%[^\n]", &staffIDentered);


                printf("\t\t\t\t\t Please enter your password : ");
                rewind(stdin);
                (void)scanf("%[^\n]", &staffPasswordentered);

                if (strcmp(staffIDentered, staffID) == 0) {
                    if (strcmp(staffPasswordentered, staffpassword) == 0) {
                        printf("\t\t\t\t\t Log in successful!!!\n");
                    }
                    else {
                        printf("\t\t\t\t\t Your staff ID or password invalid!!!\n");
                    }
                }
                else {
                    printf("\t\t\t\t\t Your staff ID or password invalid!!!\n");
                }

            } while (strcmp(staffIDentered, staffID) != 0 || strcmp(staffPasswordentered, staffpassword) != 0);

            do {
                printf("\n\t\t\t\t---------------------------------------------------------------------------------\n");
                printf("\n\t\t\t\t\t\t    ---------------------------------------");
                printf("\n\t\t\t\t\t\t    | Kolej Pasar STAFF Administrator Mode |");
                printf("\n\t\t\t\t\t\t    ---------------------------------------");
                printf("\n\t\t\t\t\t\t    [1] Generate");
                printf("\n\t\t\t\t\t\t    [2] View");
                printf("\n\t\t\t\t\t\t    [3] Back to Menu");
                printf("\n\t\t\t\t\t\t    Enter your choice : ");
                rewind(stdin);
                (void)scanf("%d", &staffchoice);
                printf("\n");
                switch (staffchoice) {
                case 1:
                    staffMode(students, &studentCount);
                    break;
                case 2:
                    studentMode(students, studentCount, studentID);
                    break;
                case 3:
                    printf("\t\t\t\t\t\t    Back to main menu.\n\n");
                    break;
                default:
                    printf("\t\t\t\t\t\t    Invalid choice. Please try again.\n");
                    break;
                }
            } while (staffchoice != 3);
            break;
        case 2:
            printf("\n\t\t\t\t---------------------------------------------------------------------------------\n");
            printf("\n\t\t\t\t\t\t\t\b----------------------------");
            printf("\n\t\t\t\t\t\t\t\b| Kolej Pasar Student Mode |");
            printf("\n\t\t\t\t\t\t\t\b----------------------------");
            studentMode(students, studentCount, studentID);
            break;
        case 3:
            printf("\n\t\t\t\t\t\t\tExiting the program.\n\n");
            //exit(0);
            break;
        default:
            printf("\n\t\t\t\t\t\t\tInvalid choice. Please try again.\n\n");
            break;
        }
    } while (choice != 3);

    return 0;
}

//Function for determine the format of studentID valid or invalid
int determineStudentID(const char* studentID) {

    // Check the length of student ID
    if (strlen(studentID) != 9) {
        printf("\t\t\t\t\t  Invalid format of student ID!!!Please enter again.\n\n");
        return 0;
    }

    // Check the first 4 characters is alphabets or not
    for (int i = 0; i < 4; i++) {
        if (!((studentID[i] >= 'A' && studentID[i] <= 'Z'))) {
            printf("\t\t\t\t\t  Invalid format of student ID!!!Please enter again.\n\n");
            return 0;
        }
    }

    // Check the last 3 characters is number or not
    for (int i = 4; i < 9; i++) {
        if (!(studentID[i] >= '0' && studentID[i] <= '9')) {
            printf("\t\t\t\t\t  Invalid format of student ID!!!Please enter again.\n\n");
            return 0;
        }
    }

    return 1;
}

//Function for staff mode
void staffMode(struct Student students[], int* studentCount) {

    if (*studentCount < MAX_STUDENTS) {

        //Loop for obtained correct format of student ID
        do {
            printf("\t\t\t\t\t  Enter student ID : ");
            rewind(stdin);
            (void)scanf("%10s", students[*studentCount].studentCode);

        } while (!determineStudentID(students[*studentCount].studentCode));

        //Get student name and number of semesters studied
        printf("\t\t\t\t\t  Enter student name : ");
        rewind(stdin);
        (void)scanf("%[^\n]", students[*studentCount].studentName);

        do {
            printf("\n\t\t\t\t\t  Enter number of semesters studied : ");
            rewind(stdin);
            (void)scanf("%d", &students[*studentCount].numSemesters);

            if (students[*studentCount].numSemesters > MAX_SEMESTERS || students[*studentCount].numSemesters <= 0) {
                printf("\t\t\t\t\t  The maximum semester is 3 !\n\n");
            }

        } while (students[*studentCount].numSemesters > MAX_SEMESTERS || students[*studentCount].numSemesters <= 0);




        //Loop for semesters
        for (int i = 0; i < students[*studentCount].numSemesters; i++) {
            printf("\n\n\t\t\t\t\t\t\t  ----------Semester %d---------\n", i + 1);

            //Loop for course code
            for (int j = 0; j < MAX_COURSES; j++) {
                char* code = students[*studentCount].courseData[i][j].code;
                printf("\n\t\t\t\t\t\t    Enter course code : ");
                rewind(stdin);
                (void)scanf("%[^\n]", students[*studentCount].courseData[i][j].code);

                printf("\t\t\t\t\t\t    Enter credit hour (positive integer) : ");
                (void)scanf("%d", &students[*studentCount].courseData[i][j].creditHour);

                //Loop for checking grade entered is valid or not
                do {
                    printf("\t\t\t\t\t\t    Enter grade (A|A-|B+|B|B-|C+|C|F) : ");
                    rewind(stdin);
                    (void)scanf("%[^\n]", &students[*studentCount].courseData[i][j].grade);


                    if (strcmp(students[*studentCount].courseData[i][j].grade, "A") != 0 &&
                        strcmp(students[*studentCount].courseData[i][j].grade, "A-") != 0 &&
                        strcmp(students[*studentCount].courseData[i][j].grade, "B+") != 0 &&
                        strcmp(students[*studentCount].courseData[i][j].grade, "B") != 0 &&
                        strcmp(students[*studentCount].courseData[i][j].grade, "B-") != 0 &&
                        strcmp(students[*studentCount].courseData[i][j].grade, "C+") != 0 &&
                        strcmp(students[*studentCount].courseData[i][j].grade, "C") != 0 &&
                        strcmp(students[*studentCount].courseData[i][j].grade, "F") != 0) {
                        printf("\t\t\t\t\t\t    Invalid grade!!! Please enter a valid grade.\n\n");
                    }
                } while (strcmp(students[*studentCount].courseData[i][j].grade, "A") != 0 &&
                    strcmp(students[*studentCount].courseData[i][j].grade, "A-") != 0 &&
                    strcmp(students[*studentCount].courseData[i][j].grade, "B+") != 0 &&
                    strcmp(students[*studentCount].courseData[i][j].grade, "B") != 0 &&
                    strcmp(students[*studentCount].courseData[i][j].grade, "B-") != 0 &&
                    strcmp(students[*studentCount].courseData[i][j].grade, "C+") != 0 &&
                    strcmp(students[*studentCount].courseData[i][j].grade, "C") != 0 &&
                    strcmp(students[*studentCount].courseData[i][j].grade, "F") != 0);

            }
            // Calculate and display GPA and CGPA for the current semester
            calculateGPACGPA(&students[*studentCount], i);
            printf("\n\t\t\t\t\t\t    GPA  : %.2lf\n", students[*studentCount].gpa[i]);
            printf("\t\t\t\t\t\t    CGPA : %.2lf\n\n", students[*studentCount].cgpa[i]);
        }
        (*studentCount)++;
        printf("\t\t\t\t\t\t    Student data added SUCCESSFULLY!!!\n");
    }
    else {
        printf("\t\t\t\t\t\t    Maximum number of students reached.\n");
    }
}


//Funtion for calculate gpa and cgpa
int calculateGPACGPA(struct Student* student, int semester) {

    //Variable declare
    double totalQualityPoints = 0.00;
    int totalCreditHours = 0;


    for (int j = 0; j < MAX_COURSES; j++) {

        //Declare data key in by staff
        char* grade = student->courseData[semester][j].grade;
        int creditHour = student->courseData[semester][j].creditHour;
        double gradePoint = 0.00;

        //Obtain grade point
        if (strcmp(grade, "A") == 0) {
            gradePoint = 4.00;
        }
        else if (strcmp(grade, "A-") == 0) {
            gradePoint = 3.75;
        }
        else if (strcmp(grade, "B+") == 0) {
            gradePoint = 3.50;
        }
        else if (strcmp(grade, "B") == 0) {
            gradePoint = 3.00;
        }
        else if (strcmp(grade, "B-") == 0) {
            gradePoint = 2.75;
        }
        else if (strcmp(grade, "C+") == 0) {
            gradePoint = 2.50;
        }
        else if (strcmp(grade, "C") == 0) {
            gradePoint = 2.00;
        }
        else if (strcmp(grade, "C-") == 0) {
            gradePoint = 1.75;
        }
        else if (strcmp(grade, "D") == 0) {
            gradePoint = 1.00;
        }
        else if (strcmp(grade, "F") == 0) {
            gradePoint = 0.00;
        }

        //Caculation
        totalQualityPoints += gradePoint * creditHour;
        totalCreditHours += creditHour;
    }

    student->gpa[semester] = totalQualityPoints / totalCreditHours;


    double totalCGPA = 0.00;
    for (int i = 0; i <= semester; i++) {
        totalCGPA += student->gpa[i];
    }

    student->cgpa[semester] = totalCGPA / (semester + 1);
    return 0;
}

// Function for student mode
void studentMode(struct Student students[], int studentCount, const char studentCode[]) {

    //Check the format of student ID and get the student ID
    do {
        printf("\n\t\t\t\t\t  Enter student ID that you want to check result : ");
        rewind(stdin);
        (void)scanf("%10s", studentID);
        printf("\n");
    } while (!determineStudentID(studentID));

    // Check whether a specific student's ID matches the student ID provided by the user
    for (int i = 0; i < studentCount; i++) {

        //Compare student ID input with student ID key in by staff 
        if (strcmp(studentID, students[i].studentCode) == 0) {
            printf("\t\t\t\t\t\t\t\b\b\b---------------------------------------\n\n");
            printf("\t\t\t\t\t\t     Student ID                  : %s\n", students[i].studentCode);
            printf("\t\t\t\t\t\t     Student Name                : %s\n", students[i].studentName);
            printf("\t\t\t\t\t\t     Number of Semesters Studied : %d\n", students[i].numSemesters);

            //Loop for display resylt by semester
            for (int j = 0; j < students[i].numSemesters; j++) {

                //Display result by semester
                printf("\n\t\t\t\t\t\t\t\b\b\b--------------Semester %d---------------\n", j + 1);
                for (int k = 0; k < MAX_COURSES; k++) {
                    printf("\t\t\t\t\t\t\t     Course Code : %s\n", students[i].courseData[j][k].code);
                    printf("\t\t\t\t\t\t\t     Credit Hour : %d\n", students[i].courseData[j][k].creditHour);
                    printf("\t\t\t\t\t\t\t     Grade       : %s\n", students[i].courseData[j][k].grade);
                    printf("\t\t\t\t\t\t\t\b\b\b---------------------------------------\n\n");
                }
                //Calculate each semester's gpa and cgpa
                calculateGPACGPA(&students[i], j);
                printf("\t\t\t\t\t\t\t     GPA         : %.2lf\n", students[i].gpa[j]);
                printf("\t\t\t\t\t\t\t     CGPA        : %.2lf\n", students[i].cgpa[j]);
                printf("\t\t\t\t\t\t\t\b\b\b---------------------------------------\n\n");
            }
            return;
        }
    }
    //If input student ID that haven't have data will show this
    printf("\t\t\t\t\t  No data found for studentID %s\n", studentID);
}