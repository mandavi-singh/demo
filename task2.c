#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 1000

typedef struct {
    char studentName[100];
    char courseName[100];
    int credits;
    char grade[3];
} Record;

// Function to swap records
void swap(Record *a, Record *b) {
    Record temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print records
void print_records(Record records[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s,%s,%d,%s\n", records[i].studentName, records[i].courseName, records[i].credits, records[i].grade);
    }
}

int main() {
    FILE *studentsFile, *coursesFile, *gradesFile;
    Record records[MAX_RECORDS];
    int recordCount = 0;
    char line[256];

    // Open the files
    studentsFile = fopen("students01.csv", "r");
    coursesFile = fopen("courses01.csv", "r");
    gradesFile = fopen("grades01.csv", "r");

    if (studentsFile == NULL || coursesFile == NULL || gradesFile == NULL) {
        perror("Error opening one of the files");
        return 1;
    }

    // Read students data
    while (fgets(line, sizeof(line), studentsFile)) {
        char studentName[100];
        char rollNumber[20];
        sscanf(line, "%[^,],%s", studentName, rollNumber);
        
        // Read courses and grades data, here assume simplified processing
        FILE *gradesFile = fopen("grades01.csv", "r");
        while (fgets(line, sizeof(line), gradesFile)) {
            char roll[20], courseNumber[20], grade[3];
            sscanf(line, "%[^,],%[^,],%s", roll, courseNumber, grade);
            
            // Find the course data
            FILE *coursesFile = fopen("courses01.csv", "r");
            while (fgets(line, sizeof(line), coursesFile)) {
                char semester[5], courseNumberFile[20], courseName[100];
                int lectureHours, tutorialHours, practicalHours, credits;
                sscanf(line, "%d,%[^,],%[^,],%d,%d,%d,%d", &semester, courseNumberFile, courseName, &lectureHours, &tutorialHours, &practicalHours, &credits);
                
                if (strcmp(courseNumber, courseNumberFile) == 0) {
                    // Add to records
                    strcpy(records[recordCount].studentName, studentName);
                    strcpy(records[recordCount].courseName, courseName);
                    records[recordCount].credits = credits;
                    strcpy(records[recordCount].grade, grade);
                    recordCount++;
                    break;
                }
            }
            fclose(coursesFile);
        }
        fclose(gradesFile);
    }
    fclose(studentsFile);

    // Quick Sort Logic
    {
        // Example of simple partition function for quicksort
        int partition(Record arr[], int low, int high) {
            Record pivot = arr[high];
            int i = (low - 1);
            
            for (int j = low; j < high; j++) {
                if (strcmp(arr[j].studentName, pivot.studentName) < 0 ||
                    (strcmp(arr[j].studentName, pivot.studentName) == 0 && arr[j].credits > pivot.credits)) {
                    i++;
                    swap(&arr[i], &arr[j]);
                }
            }
            swap(&arr[i + 1], &arr[high]);
            return (i + 1);
        }

        void quicksort(Record arr[], int low, int high) {
            if (low < high) {
                int pi = partition(arr, low, high);
                quicksort(arr, low, pi - 1);
                quicksort(arr, pi + 1, high);
            }
        }

        quicksort(records, 0, recordCount - 1);

        // Output sorted data (Quick Sort)
        printf("Sorted data (Quick Sort):\n");
        print_records(records, recordCount);
    }

    // Bubble Sort Logic
    {
        for (int i = 0; i < recordCount - 1; i++) {
            for (int j = 0; j < recordCount - i - 1; j++) {
                if (strcmp(records[j].studentName, records[j + 1].studentName) > 0 ||
                    (strcmp(records[j].studentName, records[j + 1].studentName) == 0 && records[j].credits < records[j + 1].credits)) {
                    swap(&records[j], &records[j + 1]);
                }
            }
        }

        // Output sorted data (Bubble Sort)
        printf("\nSorted data (Bubble Sort):\n");
        print_records(records, recordCount);
    }

    return 0;
}