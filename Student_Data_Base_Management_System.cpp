#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

FILE *fp;
char name[1000];
int id, att, maths, chem, pps, bio, phy, lang, nys;

// Function to validate input
void ValidateInput(const char *prompt, int *value, int min, int max) {
    do {
        printf("%s", prompt);
        scanf("%d", value);
        if (*value < min || *value > max) {
            printf("Invalid input. Please enter a value between %d and %d.\n", min, max);
        }
    } while (*value < min || *value > max);
}

void Teacher();
void Student();

// Function to add student records
void addStudent() {
    int n;
    printf("Enter number of students to add: ");
    scanf("%d", &n);

    fp = fopen("studs.txt", "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter the name of student %d: ", i + 1);
        scanf(" %[^\n]", name);
        ValidateInput("Enter ID of student: ", &id, 1, INT_MAX);
        ValidateInput("Enter attendance percent: ", &att, 0, 100);

        fprintf(fp, "Name: %s\nID: %d\nAttendance: %d%%\n", name, id, att);

        if (att < 75) {
            printf("Not Eligible for exams.\n");
            fprintf(fp, "Not Eligible for exams.\n\n");
            continue;
        }

        printf("Enter marks for Maths, Chemistry, PPS, Biology, PSP, Philosophy, Language, NSS/Yoga:\n");
        ValidateInput("Maths: ", &maths, 0, 100);
        ValidateInput("Chemistry: ", &chem, 0, 100);
        ValidateInput("PPS: ", &pps, 0, 100);
        ValidateInput("Biology: ", &bio, 0, 100);
        ValidateInput("PSP: ", &psp, 0, 100);
        ValidateInput("Philosophy: ", &phy, 0, 100);
        ValidateInput("Language: ", &lang, 0, 100);
        ValidateInput("NSS/Yoga: ", &nys, 0, 100);

        fprintf(fp, "Maths: %d\nChemistry: %d\nPPS: %d\nBiology: %d\nPSP: %d\nPhilosophy: %d\nLanguage: %d\nNSS/Yoga: %d\n",
                maths, chem, pps, bio, psp, phy, lang, nys);

        double gd = (maths + chem + pps + bio + psp + phy + lang + nys) / 8.0;
        fprintf(fp, "Grade: ");
        if (gd >= 90)
            fprintf(fp, "A\n");
        else if (gd >= 75)
            fprintf(fp, "B\n");
        else if (gd >= 60)
            fprintf(fp, "C\n");
        else if (gd >= 50)
            fprintf(fp, "D\n");
        else
            fprintf(fp, "FAIL\n");

        fprintf(fp, "\n");
    }

    fclose(fp);
}

// Function to edit student record
void editStudent() {
    int editId;
    printf("Enter the ID of the student to edit: ");
    scanf("%d", &editId);

    FILE *tempFile = fopen("temp.txt", "w");
    fp = fopen("studs.txt", "r");
    if (!fp || !tempFile) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1000];
    int found = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        int currentId;
        if (sscanf(buffer, "ID: %d", &currentId) == 1) {
            if (currentId == editId) {
                found = 1;
                printf("Editing student %d\n", currentId);
                // Skip over the data we just read and re-prompt user for new data
                fgets(buffer, sizeof(buffer), fp); // Skip name
                printf("Enter new name: ");
                scanf(" %[^\n]", name); // Accept names with spaces

                fprintf(tempFile, "Name: %s\nID: %d\n", name, currentId);

                printf("Enter new attendance: ");
                scanf("%d", &att);
                fprintf(tempFile, "Attendance: %d%%\n", att);

                printf("Enter new marks for Maths, Chemistry, PPS, Biology, PSP, Philosophy, Language, NSS/Yoga: ");
                scanf("%d %d %d %d %d %d %d %d", &maths, &chem, &pps, &bio, &psp, &phy, &lang, &nys);
                fprintf(tempFile, "Maths: %d\nChemistry: %d\nPPS: %d\nBiology: %d\nPSP: %d\nPhilosophy: %d\nLanguage: %d\nNSS/Yoga: %d\n", 
                        maths, chem, pps, bio, psp, phy, lang, nys);

                double gd = (maths + chem + pps + bio + psp + phy + lang + nys) / 8.0;
                fprintf(tempFile, "Grade: ");
                if (gd >= 90)
                    fprintf(tempFile, "A\n");
                else if (gd >= 75)
                    fprintf(tempFile, "B\n");
                else if (gd >= 60)
                    fprintf(tempFile, "C\n");
                else if (gd >= 50)
                    fprintf(tempFile, "D\n");
                else
                    fprintf(tempFile, "FAIL\n");

                continue; // Skip the rest of the loop
            }
        }
        fprintf(tempFile, "%s", buffer); // Copy all other lines to temp file
    }

    fclose(fp);
    fclose(tempFile);

    if (found) {
        remove("studs.txt");
        rename("temp.txt", "studs.txt");
        printf("Student record updated.\n");
    } else {
        printf("Student not found.\n");
    }
}

// Function to delete student record
void deleteStudent() {
    int deleteId;
    printf("Enter the ID of the student to delete: ");
    scanf("%d", &deleteId);

    FILE *tempFile = fopen("temp.txt", "w");
    fp = fopen("studs.txt", "r");
    if (!fp || !tempFile) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1000];
    int found = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        int currentId;
        if (sscanf(buffer, "ID: %d", &currentId) == 1) {
            if (currentId == deleteId) {
                found = 1;
                continue; // Skip this student’s data
            }
        }
        fprintf(tempFile, "%s", buffer); // Copy all other lines to temp file
    }

    fclose(fp);
    fclose(tempFile);

    if (found) {
        remove("studs.txt");
        rename("temp.txt", "studs.txt");
        printf("Student record deleted.\n");
    } else {
        printf("Student not found.\n");
    }
}

// Function to view all students
void viewAllStudents() {
    fp = fopen("studs.txt", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1000];
    printf("\nAll Students Data:\n");
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }

    fclose(fp);
}

// Function for Teacher actions
void Teacher() {
    int choice;
    printf("1. Add Student Records\n2. Edit Student Record\n3. Delete Student Record\n4. Display All Records\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            editStudent();
            break;
        case 3:
            deleteStudent();
            break;
        case 4:
            viewAllStudents();
            break;
        default:
            printf("Invalid choice!\n");
    }
}

// Function for Student actions
void Student() {
    char searchName[1000];
    int searchId;
    int found = 0;

    printf("Enter your name: ");
    scanf(" %[^\n]", searchName);
    printf("Enter your ID: ");
    scanf("%d", &searchId);

    fp = fopen("studs.txt", "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }

    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "Name: %[^\n]", name) == 1) {
            fscanf(fp, "ID: %d\n", &id);
            if (strcmp(name, searchName) == 0 && id == searchId) {
                found = 1;
                printf("Student Record Found:\n");
                printf("Name: %s\n", name);
                printf("ID: %d\n", id);
                while (fgets(buffer, sizeof(buffer), fp)) {
                    printf("%s", buffer);
                    if (strstr(buffer, "Grade:") != NULL) {
                        break; // End of student record
                    }
                }
                break;
            }
        }
    }

    if (!found) {
        printf("Student record not found.\n");
    }

    fclose(fp);
}

int main() {
    int userType;
    printf("Are you a Teacher (1) or Student (2)? ");
    scanf("%d", &userType);

    if (userType == 1) {
        Teacher();
    } else if (userType == 2) {
        Student();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
