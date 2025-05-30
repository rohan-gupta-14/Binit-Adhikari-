#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int roll_number;
    float marks;
} Student;
void add_student() {
    FILE *file = fopen("students.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Student new_student;
    printf("Enter student name: ");
    scanf(" %[^\n]s", new_student.name);
    printf("Enter roll number: ");
    scanf("%d", &new_student.roll_number);
    printf("Enter marks: ");
    scanf("%f", &new_student.marks);

    fprintf(file, "%s,%d,%.2f\n", new_student.name, new_student.roll_number, new_student.marks);
    fclose(file);
    printf("Student added successfully.\n");
}
void display_students() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Student current_student;
    char line[100];
    printf("\nStudent Records:\n");
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^,],%d,%f", current_student.name, &current_student.roll_number, &current_student.marks) == 3) {
            printf("Name: %s, Roll Number: %d, Marks: %.2f\n", current_student.name, current_student.roll_number, current_student.marks);
        }
    }
    fclose(file);
}
void search_student() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int search_roll;
    printf("Enter roll number to search: ");
    scanf("%d", &search_roll);

    Student current_student;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
       if (sscanf(line, "%[^,],%d,%f", current_student.name, &current_student.roll_number, &current_student.marks) == 3) {
            if (current_student.roll_number == search_roll) {
                printf("Student found:\n");
                printf("Name: %s, Roll Number: %d, Marks: %.2f\n", current_student.name, current_student.roll_number, current_student.marks);
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    printf("Student with roll number %d not found.\n", search_roll);
}
void delete_student() {
    int delete_roll;
    printf("Enter roll number to delete: ");
    scanf("%d", &delete_roll);

    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    FILE *temp_file = fopen("temp.txt", "w");
     if (temp_file == NULL) {
        perror("Error opening temp file");
        fclose(file);
        return;
    }

    Student current_student;
    char line[100];
    int found = 0;

   while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^,],%d,%f", current_student.name, &current_student.roll_number, &current_student.marks) == 3) {
            if (current_student.roll_number != delete_roll) {
                fprintf(temp_file, "%s", line);
            } else {
                found = 1;
            }
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
      remove("students.txt");
      rename("temp.txt", "students.txt");
        printf("Student with roll number %d deleted successfully.\n", delete_roll);
    } else {
        remove("temp.txt");
        printf("Student with roll number %d not found.\n", delete_roll);
    }
}
int main() {
    int choice;
    do {
        printf("\nStudent Record Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                delete_student();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
