#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

typedef struct {
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    int emergency; 
} Patient;

void mainMenu();
void adminLogin();
void adminPanel();
void patientPanel();

void addPatient();
void addEmergencyPatient();
void viewPatients();
void searchPatient();
void updatePatient();
void deletePatient();

void bookAppointment();
void checkDoctorAvailability();
void deleteAppointment();



int main() {
    mainMenu();
    return 0;
}


void mainMenu() {
    int choice;
    while (1) {
        printf("\n====================================");
        printf("\n        HOSPITAL MANAGEMENT");
        printf("\n====================================");
        printf("\n1. Admin Login");
        printf("\n2. Patient Section");
        printf("\n3. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: adminLogin(); break;
            case 2: patientPanel(); break;
            case 3: exit(0);
            default: printf(RED "\nInvalid choice!\n" RESET);
        }
    }
}



void adminLogin() {
    char user[30], pass[30];

    printf("\n===== ADMIN LOGIN =====");
    printf("\nUsername: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin") == 0) {
        printf(GREEN "\nLogin Successful!\n" RESET);
        adminPanel();
    } else {
        printf(RED "\nInvalid Credentials!\n" RESET);
    }
}

// -------------------------------------------------------
void adminPanel() {
    int choice;

    while (1) {
        printf("\n=========== ADMIN PANEL ===========");
        printf("\n1. Add Patient");
        printf("\n2. Add Emergency Patient");
        printf("\n3. View All Patients");
        printf("\n4. Search Patient");
        printf("\n5. Update Patient");
        printf("\n6. Delete Patient");
        printf("\n7. Back to Main Menu");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addPatient(); break;
            case 2: addEmergencyPatient(); break;
            case 3: viewPatients(); break;
            case 4: searchPatient(); break;
            case 5: updatePatient(); break;
            case 6: deletePatient(); break;
            case 7: return;
            default: printf(RED "\nInvalid choice!\n" RESET);
        }
    }
}

void patientPanel() {
    int choice;

    while (1) {
        printf("\n========== PATIENT PANEL ==========");
        printf("\n1. Book Appointment");
        printf("\n2. Check Doctor Availability");
        printf("\n3. Delete Appointment");
        printf("\n4. Back to Main Menu");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: bookAppointment(); break;
            case 2: checkDoctorAvailability(); break;
            case 3: deleteAppointment(); break;
            case 4: return;
            default: printf(RED "\nInvalid choice!\n" RESET);
        }
    }
}

void addPatient() {
    Patient p;
    FILE *fp = fopen("patients.txt", "a");
    if (!fp) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }

    printf("\nEnter Patient Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();
    printf("Enter Gender: ");
    scanf("%s", p.gender);
    getchar();
    printf("Enter Disease: ");
    scanf(" %[^\n]", p.disease);

    p.emergency = 0;

    fprintf(fp, "%s|%d|%s|%s|%d\n", p.name, p.age, p.gender, p.disease, p.emergency);
    fclose(fp);

    printf(GREEN "\nPatient added successfully!\n" RESET);
}

void addEmergencyPatient() {
    Patient p;
    FILE *fp = fopen("patients.txt", "a");
    if (!fp) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }

    printf("\nEnter Emergency Patient Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();
    printf("Enter Gender: ");
    scanf("%s", p.gender);
    getchar();
    printf("Enter Disease: ");
    scanf(" %[^\n]", p.disease);

    p.emergency = 1;

    fprintf(fp, "%s|%d|%s|%s|%d\n", p.name, p.age, p.gender, p.disease, p.emergency);
    fclose(fp);

    printf(GREEN "\nEmergency Patient added successfully!\n" RESET);
}

void viewPatients() {
    FILE *fp = fopen("patients.txt", "r");
    if (!fp) {
        printf(RED "\nNo patients found!\n" RESET);
        return;
    }

    Patient p;
    char line[200];

    printf("\n===== PATIENT LIST =====\n");
    printf("%-20s %-5s %-10s %-20s %-10s\n", "Name", "Age", "Gender", "Disease", "Status");
    printf("-----------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%[^|]|%d|%[^|]|%[^|]|%d",
                   p.name, &p.age, p.gender, p.disease, &p.emergency) == 5) {
            printf("%-20s %-5d %-10s %-20s ", p.name, p.age, p.gender, p.disease);
            if (p.emergency)
                printf(RED "%-10s\n" RESET, "Emergency");
            else
                printf("%-10s\n", "Normal");
        }
    }

    fclose(fp);
}

void searchPatient() {
    FILE *fp = fopen("patients.txt", "r");
    if (!fp) {
        printf(RED "\nNo patients found!\n" RESET);
        return;
    }

    Patient p;
    char name[50];
    int found = 0;

    printf("\nEnter name to search: ");
    scanf(" %[^\n]", name);

    while (fscanf(fp, " %[^|]|%d|%[^|]|%[^|]|%d",
                  p.name, &p.age, p.gender, p.disease, &p.emergency) != EOF) {
        if (strcasecmp(name, p.name) == 0) {
            printf(GREEN "\n✔ Record Found:\n" RESET);
            printf("\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nStatus: %s\n",
                   p.name, p.age, p.gender, p.disease,
                   p.emergency ? "Emergency" : "Normal");
            found = 1;
            break;
        }
    }

    if (!found) printf(RED "\nPatient not found!\n" RESET);

    fclose(fp);
}

void updatePatient() {
    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }

    Patient p;
    char name[50];
    int found = 0;

    printf("\nEnter name to update: ");
    scanf(" %[^\n]", name);

    while (fscanf(fp, " %[^|]|%d|%[^|]|%[^|]|%d",
                  p.name, &p.age, p.gender, p.disease, &p.emergency) != EOF) {

        if (strcasecmp(name, p.name) == 0) {
            found = 1;
            printf("\nEnter new Age: ");
            scanf("%d", &p.age);
            getchar();
            printf("Enter new Gender: ");
            scanf("%s", p.gender);
            getchar();
            printf("Enter new Disease: ");
            scanf(" %[^\n]", p.disease);
            getchar();
            printf("Is Emergency (1 = Yes, 0 = No): ");
            scanf("%d", &p.emergency);
            getchar();
        }
        fprintf(temp, "%s|%d|%s|%s|%d\n", p.name, p.age, p.gender, p.disease, p.emergency);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) printf(GREEN "\nRecord Updated!\n" RESET);
    else printf(RED "\nPatient not found!\n" RESET);
}

void deletePatient() {
    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }

    Patient p;
    char name[50];
    int found = 0;

    printf("\nEnter name to delete: ");
    scanf(" %[^\n]", name);

    while (fscanf(fp, " %[^|]|%d|%[^|]|%[^|]|%d",
                  p.name, &p.age, p.gender, p.disease, &p.emergency) != EOF) {

        if (strcasecmp(name, p.name) != 0)
            fprintf(temp, "%s|%d|%s|%s|%d\n", p.name, p.age, p.gender, p.disease, p.emergency);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) printf(GREEN "\nRecord Deleted!\n" RESET);
    else printf(RED "\nPatient not found!\n" RESET);
}

void bookAppointment() {
    FILE *fp = fopen("appointments.txt", "a+");
    char patientName[50], doctor[50], date[20];
    char p[50], d[50], dt[20];
    int count = 0;

    printf("\nEnter Patient Name: ");
    scanf(" %[^\n]", patientName);
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", doctor);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", date);

    rewind(fp);
    while (fscanf(fp, " %[^|]|%[^|]|%[^\n]", p, d, dt) != EOF) {
        if (strcasecmp(d, doctor) == 0 && strcmp(dt, date) == 0)
            count++;
    }

    if (count >= 2) {
        printf(RED "\nMaximum 2 appointments per doctor per day reached!\n" RESET);
        fclose(fp);
        return;
    }

    fprintf(fp, "%s|%s|%s\n", patientName, doctor, date);
    fclose(fp);

    printf(GREEN "\nAppointment booked successfully!\n" RESET);
}
void checkDoctorAvailability() {
    FILE *fp = fopen("appointments.txt", "r");
    char doctorInput[50], p[50], d[50], date[20];
    int count = 0;

    printf("\nEnter Doctor Name: ");
    scanf(" %[^\n]", doctorInput);

    if (!fp) {
        printf(GREEN "\nNo appointments found. Doctor is AVAILABLE.\n" RESET);
        return;
    }

    while (fscanf(fp, " %[^|]|%[^|]|%[^\n]", p, d, date) != EOF) {
        if (strcasecmp(d, doctorInput) == 0)
            count++;
    }

    fclose(fp);

    printf("\n==== Doctor Availability ====\n");

    if (count == 0)
        printf(GREEN "Doctor %s has NO appointments. Doctor is AVAILABLE.\n" RESET, doctorInput);
    else if (count < 2)
        printf(GREEN "Doctor %s has %d appointment(s). Doctor is AVAILABLE.\n" RESET,
               doctorInput, count);
    else
        printf(RED "Doctor %s already has 2 appointments. Doctor is NOT AVAILABLE.\n" RESET,
               doctorInput);
}

void deleteAppointment() {
    FILE *fp = fopen("appointments.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char patientName[50], doctor[50], date[20];
    char p[50], d[50], dt[20];
    int found = 0;

    printf("\nEnter Patient Name: ");
    scanf(" %[^\n]", patientName);
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", doctor);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", date);

    while (fscanf(fp, " %[^|]|%[^|]|%[^\n]", p, d, dt) != EOF) {
        if (strcasecmp(p, patientName) == 0 &&
            strcasecmp(d, doctor) == 0 &&
            strcmp(dt, date) == 0) {
            found = 1;
        } else {
            fprintf(temp, "%s|%s|%s\n", p, d, dt);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    if (found) printf(GREEN "\nAppointment Deleted!\n" RESET);
    else printf(RED "\nNo such appointment found!\n" RESET);
}
