#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definition for student details
struct student {
    char name[50];
    int roll_number;
    char address[100];
    char class_name[20]; // 'class' is a reserved keyword in C++, changed to class_name
    int age;
    float quarterly_marks;
    float halfyearly_marks;
    float annual_marks;
    float total_marks;
    float percentage;
    char grade;
};

void createNewDatabase();
void viewOrEditDatabase();
void viewStudentDetails(int roll_number);
void editStudentDetails(int roll_number);
float calculatePercentage(float marks, float total);
char calculateGrade(float percentage);

int main() {
    char choice;

    do {
        printf("\nMain Menu:\n");
        printf("1. Create new student database\n");
        printf("2. View or edit an existing student database\n");
        printf("3. Exit\n");
        printf("Enter your choice (1/2/3): ");
        scanf(" %c", &choice);

        switch(choice) {
            case '1':
                createNewDatabase();
                break;
            case '2':
                viewOrEditDatabase();
                break;
            case '3':
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    } while(choice != '3');

    return 0;
}

void createNewDatabase() {
    struct student newStudent;

    // Input details from user
    printf("\nEnter details of the new student:\n");
    printf("Name: ");
    scanf(" %[^\n]", newStudent.name);
    printf("Roll Number: ");
    scanf("%d", &newStudent.roll_number);
    printf("Address: ");
    scanf(" %[^\n]", newStudent.address);
    printf("Class: ");
    scanf(" %[^\n]", newStudent.class_name);
    printf("Age: ");
    scanf("%d", &newStudent.age);
    printf("Quarterly Marks: ");
    scanf("%f", &newStudent.quarterly_marks);
    printf("Half Yearly Marks: ");
    scanf("%f", &newStudent.halfyearly_marks);
    printf("Annual Marks: ");
    scanf("%f", &newStudent.annual_marks);

    // Calculate total marks, percentage and grade
    newStudent.total_marks = newStudent.quarterly_marks + newStudent.halfyearly_marks + newStudent.annual_marks;
    newStudent.percentage = calculatePercentage(newStudent.total_marks, 300.0); // Assuming total marks is 300
    newStudent.grade = calculateGrade(newStudent.percentage);

    // Save data to file named after roll number
    char filename[20];
    sprintf(filename, "%d.txt", newStudent.roll_number);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating file.\n");
        return;
    }
    fprintf(fp, "Name: %s\n", newStudent.name);
    fprintf(fp, "Roll Number: %d\n", newStudent.roll_number);
    fprintf(fp, "Address: %s\n", newStudent.address);
    fprintf(fp, "Class: %s\n", newStudent.class_name);
    fprintf(fp, "Age: %d\n", newStudent.age);
    fprintf(fp, "Quarterly Marks: %.2f\n", newStudent.quarterly_marks);
    fprintf(fp, "Half Yearly Marks: %.2f\n", newStudent.halfyearly_marks);
    fprintf(fp, "Annual Marks: %.2f\n", newStudent.annual_marks);
    fprintf(fp, "Total Marks: %.2f\n", newStudent.total_marks);
    fprintf(fp, "Percentage: %.2f\n", newStudent.percentage);
    fprintf(fp, "Grade: %c\n", newStudent.grade);
    fclose(fp);

    printf("\nData saved successfully for roll number %d.\n", newStudent.roll_number);
}

void viewOrEditDatabase() {
    int roll_number;
    char choice;

    printf("Enter roll number of the student: ");
    scanf("%d", &roll_number);

    printf("1. View student details\n");
    printf("2. Edit student details\n");
    printf("Enter your choice (1/2): ");
    scanf(" %c", &choice);

    switch(choice) {
        case '1':
            viewStudentDetails(roll_number);
            break;
        case '2':
            editStudentDetails(roll_number);
            break;
        default:
            printf("Invalid choice. Please enter 1 or 2.\n");
    }
}

void viewStudentDetails(int roll_number) {
    char filename[20];
    sprintf(filename, "%d.txt", roll_number);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Student with roll number %d does not exist.\n", roll_number);
        return;
    }

    struct student s;
    fscanf(fp, "Name: %[^\n]\n", s.name);
    fscanf(fp, "Roll Number: %d\n", &s.roll_number);
    fscanf(fp, "Address: %[^\n]\n", s.address);
    fscanf(fp, "Class: %[^\n]\n", s.class_name);
    fscanf(fp, "Age: %d\n", &s.age);
    fscanf(fp, "Quarterly Marks: %f\n", &s.quarterly_marks);
    fscanf(fp, "Half Yearly Marks: %f\n", &s.halfyearly_marks);
    fscanf(fp, "Annual Marks: %f\n", &s.annual_marks);
    fscanf(fp, "Total Marks: %f\n", &s.total_marks);
    fscanf(fp, "Percentage: %f\n", &s.percentage);
    fscanf(fp, "Grade: %c\n", &s.grade);

    fclose(fp);

    // Display details
    printf("\nStudent details:\n");
    printf("Name: %s\n", s.name);
    printf("Roll Number: %d\n", s.roll_number);
    printf("Address: %s\n", s.address);
    printf("Class: %s\n", s.class_name);
    printf("Age: %d\n", s.age);
    printf("Quarterly Marks: %.2f\n", s.quarterly_marks);
    printf("Half Yearly Marks: %.2f\n", s.halfyearly_marks);
    printf("Annual Marks: %.2f\n", s.annual_marks);
    printf("Total Marks: %.2f\n", s.total_marks);
    printf("Percentage: %.2f\n", s.percentage);
    printf("Grade: %c\n", s.grade);
}

void editStudentDetails(int roll_number) {
    char filename[20];
    sprintf(filename, "%d.txt", roll_number);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Student with roll number %d does not exist.\n", roll_number);
        return;
    }

    // Read existing details
    struct student s;
    fscanf(fp, "Name: %[^\n]\n", s.name);
    fscanf(fp, "Roll Number: %d\n", &s.roll_number);
    fscanf(fp, "Address: %[^\n]\n", s.address);
    fscanf(fp, "Class: %[^\n]\n", s.class_name);
    fscanf(fp, "Age: %d\n", &s.age);
    fscanf(fp, "Quarterly Marks: %f\n", &s.quarterly_marks);
    fscanf(fp, "Half Yearly Marks: %f\n", &s.halfyearly_marks);
    fscanf(fp, "Annual Marks: %f\n", &s.annual_marks);

    fclose(fp);

    // Display existing details
    printf("\nExisting details:\n");
    printf("Name: %s\n", s.name);
    printf("Address: %s\n", s.address);
    printf("Class: %s\n", s.class_name);
    printf("Age: %d\n", s.age);
    printf("Quarterly Marks: %.2f\n", s.quarterly_marks);
    printf("Half Yearly Marks: %.2f\n", s.halfyearly_marks);
    printf("Annual Marks: %.2f\n", s.annual_marks);

    // Input new details
    printf("\nEnter new details:\n");
    printf("Name: ");
    scanf(" %[^\n]", s.name);
    printf("Address: ");
    scanf(" %[^\n]", s.address);
    printf("Class: ");
    scanf(" %[^\n]", s.class_name);
    printf("Age: ");
    scanf("%d", &s.age);
    printf("Quarterly Marks: ");
    scanf("%f", &s.quarterly_marks);
    printf("Half Yearly Marks: ");
    scanf("%f", &s.halfyearly_marks);
    printf("Annual Marks: ");
    scanf("%f", &s.annual_marks);

    // Calculate total marks, percentage, and grade
    s.total_marks = s.quarterly_marks + s.halfyearly_marks + s.annual_marks;
    s.percentage = calculatePercentage(s.total_marks, 500.0); // Assuming total marks is 300
    s.grade = calculateGrade(s.percentage);

    // Save updated details to file
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error updating file.\n");
        return;
    }
    fprintf(fp, "Name: %s\n", s.name);
    fprintf(fp, "Roll Number: %d\n", s.roll_number);
    fprintf(fp, "Address: %s\n", s.address);
    fprintf(fp, "Class: %s\n", s.class_name);
    fprintf(fp, "Age: %d\n", s.age);
    fprintf(fp, "Quarterly Marks: %.2f\n", s.quarterly_marks);
    fprintf(fp, "Half Yearly Marks: %.2f\n", s.halfyearly_marks);
    fprintf(fp, "Annual Marks: %.2f\n", s.annual_marks);
    fprintf(fp, "Total Marks: %.2f\n", s.total_marks);
    fprintf(fp, "Percentage: %.2f\n", s.percentage);
    fprintf(fp, "Grade: %c\n", s.grade);
    fclose(fp);

    printf("\nData updated and saved successfully for roll number %d.\n", s.roll_number);
}

float calculatePercentage(float marks, float total) {
    return (marks / total) * 100;
}

char calculateGrade(float percentage) {
    if (percentage >= 90) {
        return 'A';
    } else if (percentage >= 75) {
        return 'B';
    } else if (percentage >= 50) {
        return 'C';
    } else if (percentage >= 35) {
        return 'D';
    } else {
        return 'F';
    }
}
