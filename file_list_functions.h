#ifndef PROJETO_SISTEMA_SAUDE_2ETAPA_FILE_LIST_FUNCTIONS_H
#define PROJETO_SISTEMA_SAUDE_2ETAPA_FILE_LIST_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

enum BloodType {
    A, B, AB, O
};

enum RHFactor {
    Positive, Negative
};

typedef struct {
    int code;
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

void checkIfFileExists();
void checkIfFileWasCreated();
void fromListToDisk(Patient *patients, int numPatients);
void fromDiskToList(Patient **patients, int *numPatients);
void writeInfoInFile(Patient *patients, int numPatients);
void readInfoFromFile(Patient *patients, int numPatients);

void buildPatientListsFromFile(Patient **patients, int *numPatients);
void buildAppointmentListsFromFile(Appointment **appointments, int *numAppointments);
bool isValidDate(const char* date);
void removeAllAppointmentsOfAPatient(Appointment **appointments, int *numAppointments, int patientCode);


void checkIfFileWasCreated() {
    FILE *file = fopen("patients.bin", "rb");
    if (file == NULL) {
        printf("Arquivo nao foi criado, memoria cheia.\n");
        exit(1);
    }
}

void fromListToDisk(Patient *patients, int numPatients) {
    checkIfFileExists();
    FILE *file = fopen("patients.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
}
    

void fromDiskToList(Patient **patients, int *numPatients) {
    checkIfFileExists();
    FILE *patientsFile = fopen("patients.bin", "rb");
    fread(numPatients, sizeof(int), 1, patientsFile);
}

void checkIfFileExists() {
        FILE *patientsFile = fopen("patients.bin", "rb");
        if (patientsFile == NULL) {
            printf("Arquivo nao existe, criando arquivo...\n");
            patientsFile = fopen("patients.bin", "wb+");
            checkIfFileWasCreated();
            fclose(patientsFile);
        }
}

void writeInfoInFile(Patient *patients, int numPatients) {
        checkIfFileExists();
        FILE *patientsFile = fopen("patients.bin", "wb");
        if (patientsFile == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }
        fwrite(&numPatients, sizeof(int), 1, patientsFile);
        for (int i = 0; i < numPatients; i++) {
            fprintf(patientsFile, "%d\n", patients[i].code);
            fprintf(patientsFile, "%s\n", patients[i].name);
            fprintf(patientsFile, "%s\n", patients[i].RG);
            fprintf(patientsFile, "%s\n", patients[i].CPF);
            fprintf(patientsFile, "%d\n", patients[i].bloodType);
            fprintf(patientsFile, "%d\n", patients[i].rhFactor);
            fprintf(patientsFile, "%s\n", patients[i].address);
            fprintf(patientsFile, "%s\n", patients[i].dob);
        }
        fclose(patientsFile);
}

void readInfoFromFile(Patient *patients, int numPatients) {
    checkIfFileExists();
    FILE *patientsFile = fopen("patients.bin", "rb");
    if (patientsFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fread(&numPatients, sizeof(int), 1, patientsFile);
    for (int i = 0; i < numPatients; i++) {
        fscanf(patientsFile, "%d", &patients[i].code);
        fscanf(patientsFile, "%s", patients[i].name);
        fscanf(patientsFile, "%s", patients[i].RG);
        fscanf(patientsFile, "%s", patients[i].CPF);
        fscanf(patientsFile, "%d", &patients[i].bloodType);
        fscanf(patientsFile, "%d", &patients[i].rhFactor);
        fscanf(patientsFile, "%s", patients[i].address);
        fscanf(patientsFile, "%s", patients[i].dob);
    }
    fclose(patientsFile);
}

void buildPatientListsFromFile(Patient **patients, int *numPatients) {
    checkIfFileExists();
    FILE *patientsFile = fopen("patients.bin", "rb");
    if (patientsFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fread(numPatients, sizeof(int), 1, patientsFile);
    *patients = (Patient *) malloc(*numPatients * sizeof(Patient));
    for (int i = 0; i < *numPatients; i++) {
        fscanf(patientsFile, "%d", &(*patients)[i].code);
        fscanf(patientsFile, "%s", (*patients)[i].name);
        fscanf(patientsFile, "%s", (*patients)[i].RG);
        fscanf(patientsFile, "%s", (*patients)[i].CPF);
        fscanf(patientsFile, "%d", &(*patients)[i].bloodType);
        fscanf(patientsFile, "%d", &(*patients)[i].rhFactor);
        fscanf(patientsFile, "%s", (*patients)[i].address);
        fscanf(patientsFile, "%s", (*patients)[i].dob);
    }
    fclose(patientsFile);
}

void buildAppointmentListsFromFile(Appointment **appointments, int *numAppointments) {
    checkIfFileExists();
    FILE *appointmentsFile = fopen("appointments.bin", "rb");
    if (appointmentsFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fread(numAppointments, sizeof(int), 1, appointmentsFile);
    *appointments = (Appointment *) malloc(*numAppointments * sizeof(Appointment));
    for (int i = 0; i < *numAppointments; i++) {
        fscanf(appointmentsFile, "%d", &(*appointments)[i].code);
        fscanf(appointmentsFile, "%d", &(*appointments)[i].patientCode);
        fscanf(appointmentsFile, "%d", &(*appointments)[i].appointmentType);
        fscanf(appointmentsFile, "%s", (*appointments)[i].date);
        fscanf(appointmentsFile, "%d", &(*appointments)[i].status);
        fscanf(appointmentsFile, "%f", &(*appointments)[i].price);
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

#endif // PROJETO_SISTEMA_SAUDE_2ETAPA_FILE_LIST_FUNCTIONS_H