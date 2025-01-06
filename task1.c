#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student details
struct Student {
    char name[100];
    int roll_number;
};

// Structure to store course details
struct Course {
    int semester;
    char course_code[20];
    char course_name[100];
    int lecture_hours;
    int tutorial_hours;
    int practical_hours;
    int credits;
};

// Structure to store grades details
struct Grades {
    int student_roll_number;
    char course_code[20];
    char grade[3];
};

int main() {
    // Task 1: Reading students01.csv
    FILE *student_file = fopen("students01.csv", "r");
    if (!student_file) {
        printf("Error opening students01.csv\n");
        return 1;
    }

    struct Student students[200]; // Assuming at most 200 students
    int student_count = 0;

    while (fscanf(student_file, "%99[^,], %d\n", students[student_count].name, &students[student_count].roll_number) != EOF) {
        student_count++;
    }

    fclose(student_file);
    printf("Successfully read %d students.\n", student_count);

    // Task 1: Reading courses01.csv
    FILE *course_file = fopen("courses01.csv", "r");
    if (!course_file) {
        printf("Error opening courses01.csv\n");
        return 1;
    }

    struct Course courses[100]; // Assuming at most 100 courses
    int course_count = 0;

    while (fscanf(course_file, "%d, %19[^,], %99[^,], %d, %d, %d, %d\n", 
                    &courses[course_count].semester, 
                    courses[course_count].course_code, 
                    courses[course_count].course_name, 
                    &courses[course_count].lecture_hours, 
                    &courses[course_count].tutorial_hours, 
                    &courses[course_count].practical_hours, 
                    &courses[course_count].credits) != EOF) {
        course_count++;
    }

    fclose(course_file);
    printf("Successfully read %d courses.\n", course_count);

    // Task 1: Reading grades01.csv
    FILE *grades_file = fopen("grades01.csv", "r");
    if (!grades_file) {
        printf("Error opening grades01.csv\n");
        return 1;
    }

    struct Grades grades[10000]; // Assuming at most 10,000 grades
    int grades_count = 0;

    while (fscanf(grades_file, "%d, %19[^,], %2s\n", &grades[grades_count].student_roll_number, grades[grades_count].course_code, grades[grades_count].grade) != EOF) {
        grades_count++;
    }

    fclose(grades_file);
    printf("Successfully read %d grades.\n", grades_count);

    // Output data to check if reading is successful
    printf("\nSample Data (First 3 Students):\n");
    for (int i = 0; i < 3 && i < student_count; i++) {
        printf("Student: %s, Roll Number: %d\n", students[i].name, students[i].roll_number);
    }

    printf("\nSample Data (First 3 Courses):\n");
    for (int i = 0; i < 3 && i < course_count; i++) {
        printf("Course: %s, Code: %s, Credits: %d\n", courses[i].course_name, courses[i].course_code, courses[i].credits);
    }

    printf("\nSample Data (First 3 Grades):\n");
    for (int i = 0; i < 3 && i < grades_count; i++) {
        printf("Roll Number: %d, Course: %s, Grade: %s\n", grades[i].student_roll_number, grades[i].course_code, grades[i].grade);
    }
}
