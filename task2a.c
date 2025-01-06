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

// Structure to hold merged data for sorting
struct StudentRecord {
    char student_name[100];
    char course_name[100];
    int credits;
    char grade[3];
};

// Global arrays and counters
struct Student students[200];
struct Course courses[100];
struct Grades grades[10000];
struct StudentRecord student_records[10000];
int student_count = 0, course_count = 0, grades_count = 0, record_count = 0;

// Function to find the course by course code
struct Course* find_course_by_code(char *course_code) {
    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].course_code, course_code) == 0) {
            return &courses[i];
        }
    }
    return NULL;
}

// Function to find the student by roll number
struct Student* find_student_by_roll(int roll_number) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_number == roll_number) {
            return &students[i];
        }
    }
    return NULL;
}

// Task 1: Load data from files
void load_data() {
    FILE *student_file = fopen("students01.csv", "r");
    FILE *course_file = fopen("courses01.csv", "r");
    FILE *grades_file = fopen("grades01.csv", "r");

    // Load students01.csv
    while (fscanf(student_file, "%99[^,], %d\n", students[student_count].name, &students[student_count].roll_number) != EOF) {
        student_count++;
    }
    fclose(student_file);

    // Load courses01.csv
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

    // Load grades01.csv
    while (fscanf(grades_file, "%d, %19[^,], %2s\n", &grades[grades_count].student_roll_number, grades[grades_count].course_code, grades[grades_count].grade) != EOF) {
        grades_count++;
    }
    fclose(grades_file);
}

// Merge student, course, and grade data into student_records array
void merge_data() {
    for (int i = 0; i < grades_count; i++) {
        struct Student *student = find_student_by_roll(grades[i].student_roll_number);
        struct Course *course = find_course_by_code(grades[i].course_code);

        if (student && course) {
            strcpy(student_records[record_count].student_name, student->name);
            strcpy(student_records[record_count].course_name, course->course_name);
            student_records[record_count].credits = course->credits;
            strcpy(student_records[record_count].grade, grades[i].grade);
            record_count++;
        }
    }
}

// Bubble Sort on student name in ascending order
void bubble_sort() {
    for (int i = 0; i < record_count - 1; i++) {
        for (int j = 0; j < record_count - i - 1; j++) {
            if (strcmp(student_records[j].student_name, student_records[j + 1].student_name) > 0) {
                struct StudentRecord temp = student_records[j];
                student_records[j] = student_records[j + 1];
                student_records[j + 1] = temp;
            }
        }
    }
}

// Partition function for Quick Sort
int partition(int low, int high) {
    struct StudentRecord pivot = student_records[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(student_records[j].student_name, pivot.student_name) < 0) {
            i++;
            struct StudentRecord temp = student_records[i];
            student_records[i] = student_records[j];
            student_records[j] = temp;
        }
    }
    struct StudentRecord temp = student_records[i + 1];
    student_records[i + 1] = student_records[high];
    student_records[high] = temp;
    return (i + 1);
}

// Quick Sort on student name in ascending order
void quick_sort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quick_sort(low, pi - 1);
        quick_sort(pi + 1, high);
    }
}

// Output the sorted data
void output_sorted_data() {
    for (int i = 0; i < record_count; i++) {
        printf("%s, %s, %d, %s\n", student_records[i].student_name, student_records[i].course_name, student_records[i].credits, student_records[i].grade);
    }
}

int main() {
    // Task 1: Load the data
    load_data();

    // Merge the data
    merge_data();

    // Task 2a: Sort by student name using Bubble Sort
    printf("Sorted by student name using Bubble Sort:\n");
    bubble_sort();
    output_sorted_data();

    // Task 2a: Sort by student name using Quick Sort
    printf("\nSorted by student name using Quick Sort:\n");
    quick_sort(0, record_count - 1);
    output_sorted_data();

    return 0;
}