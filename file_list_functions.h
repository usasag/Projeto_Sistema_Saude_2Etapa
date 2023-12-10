#ifndef PROJETO_SISTEMA_SAUDE_2ETAPA_FILE_LIST_FUNCTIONS_H
#define PROJETO_SISTEMA_SAUDE_2ETAPA_FILE_LIST_FUNCTIONS_H
#define MAX_FILE_NAME 100

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <errno.h>

enum BloodType {
    A, B, AB, O, UNDEFINED_BLOOD
};

enum RHFactor {
    Positive, Negative, UNDEFINED_RH
};

enum Gender {
    Male, Female, UNDEFINED_GENDER
};


typedef struct {
    int code;
    enum Gender gender;
    char name[100];
    char RG[20];
    char CPF[15];
    enum BloodType bloodType;
    enum RHFactor rhFactor;
    char address[200];
    char dob[11];
} Patient;

enum Status {
    Agendado, Atendendo, Finalizado, Cancelado
};

enum AppointmentType {
    Consulta, Retorno
};

typedef struct {
    int code;
    int patientCode;
    enum AppointmentType appointmentType;
    char date[11];
    enum Status status;
    float price;
} Appointment;

const char *bloodTypeStrings[] = { "A", "B", "AB", "O", "Indefinido"};
const char *rhFactorStrings[] = { "Positivo", "Negativo", "Indefinido"};
const char *genderStrings[] = { "Masculino", "Feminino", "Indefinido"};

const char *statusStrings[] = { "Agendado", "Atendendo", "Finalizado", "Cancelado" };
const char *appointmentTypeStrings[] = { "Consulta", "Retorno" };

void checkIfFileExists();
void checkIfFileWasCreated();
void writePatientInfoInFile(Patient *patients, int numPatients);
void writeAppointmentInfoInFile(Appointment *appointments, int numAppointments);
void readInfoFromFile(Patient *patients, int numPatients);

void buildPatientListsFromFile(Patient **patients, int *numPatients);
void buildAppointmentListsFromFile(Appointment **appointments, int *numAppointments);
bool isValidDate(const char* date);
void removeAllAppointmentsOfAPatient(Appointment **appointments, int *numAppointments, int patientCode);

int findPatient(const Patient *patients, int numPatients, int code);
int compareDates(const char *date1, const char *date2);

void checkIfFileExists() {
    FILE *patientsFile = fopen("patients.bin", "rb");
    if (patientsFile == NULL) {
        printf("File does not exist, creating file...\n");
        patientsFile = fopen("patients.bin", "wb+");
        if (patientsFile == NULL) {
            printf("Failed to create file. Error: %s\n", strerror(errno));
            return;
        }
    }
    fclose(patientsFile);

    FILE *appointmentsFile = fopen("appointments.bin", "rb");
    if (appointmentsFile == NULL) {
        printf("File does not exist, creating file...\n");
        appointmentsFile = fopen("appointments.bin", "wb+");
        if (appointmentsFile == NULL) {
            printf("Failed to create file. Error: %s\n", strerror(errno));
            return;
        }
    }
    fclose(appointmentsFile);
}

void writePatientInfoInFile(Patient *patients, int numPatients) {
    FILE *patientFile = fopen("patients.bin", "wb");
    if (patientFile == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    fwrite(&numPatients, sizeof(int), 1, patientFile);
    for (int i = 0; i < numPatients; i++) {
        fwrite(&patients[i], sizeof(Patient), 1, patientFile);
    }
    fclose(patientFile);
}

void writeAppointmentInfoInFile(Appointment *appointments, int numAppointments) {
    FILE *appointmentsFile = fopen("appointments.bin", "wb");
    if (appointmentsFile == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    fwrite(&numAppointments, sizeof(int), 1, appointmentsFile);
    for (int i = 0; i < numAppointments; i++) {
        fwrite(&appointments[i], sizeof(Appointment), 1, appointmentsFile);
    }
    fclose(appointmentsFile);
}

void buildPatientListsFromFile(Patient **patients, int *numPatients) {
    FILE *patientFile = fopen("patients.bin", "rb");
    if (patientFile == NULL) {
        printf("Error opening the patient file. Error: %s\n", strerror(errno));
        return;
    }
    fread(numPatients, sizeof(int), 1, patientFile);
    *patients = (Patient *) malloc(*numPatients * sizeof(Patient));
    for (int i = 0; i < *numPatients; i++) {
        fread(&(*patients)[i], sizeof(Patient), 1, patientFile);
    }
    fclose(patientFile);
}

void buildAppointmentListsFromFile(Appointment **appointments, int *numAppointments) {
    FILE *appointmentsFile = fopen("appointments.bin", "rb");
    if (appointmentsFile == NULL) {
        printf("Failed to open the appointments file. Error: %s\n", strerror(errno));
        return;
    }
    fread(numAppointments, sizeof(int), 1, appointmentsFile);
    *appointments = (Appointment *) malloc(*numAppointments * sizeof(Appointment));
    for (int i = 0; i < *numAppointments; i++) {
        fread(&(*appointments)[i], sizeof(Appointment), 1, appointmentsFile);
    }
    fclose(appointmentsFile);
}

bool isValidDate(const char* date) {
    if (strlen(date) != 10) {
        return false;
    }

    if (date[2] != '/' || date[5] != '/') {
        return false;
    }

    int day = atoi(date);
    int month = atoi(date + 3);
    int year = atoi(date + 6);

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999) {
        return false;
    }

    return true;
}

void removeAllAppointmentsOfAPatient(Appointment **appointments, int *numAppointments, int patientCode) {
    for (int i = 0; i < *numAppointments; i++) {
        if ((*appointments)[i].patientCode == patientCode) {
            for (int j = i; j < *numAppointments - 1; j++) {
                (*appointments)[j] = (*appointments)[j + 1];
            }
            *numAppointments -= 1;
            *appointments = (Appointment *) realloc(*appointments, *numAppointments * sizeof(Appointment));
        }
    }
}

int findPatient(const Patient *patients, int numPatients, int code) {
    // Procurar o paciente pelo código
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].code == code) {
            return i;
        }
    }
    return -1;
}

#endif // PROJETO_SISTEMA_SAUDE_2ETAPA_FILE_LIST_FUNCTIONS_H