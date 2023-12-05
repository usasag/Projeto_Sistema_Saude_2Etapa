#ifndef FILE_LIST_FUNCTIONS_H
#define FILE_LIST_FUNCTIONS.H
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


void checkIfFileWasCreated() {
    FILE *file = fopen("patients.bin", "rb");
    if (file == NULL) {
        printf("Arquivo nao foi criado, memoria cheia.\n");
        exit(1);
    }
}

void buildList(Patient **patients, int *numPatients) {
    // Abrir o arquivo
    FILE *file = fopen("patients.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Ler o número de pacientes
    fread(numPatients, sizeof(int), 1, file);

    // Alocar memória para a lista de pacientes
    *patients = malloc((*numPatients) * sizeof(Patient));

    // Ler os pacientes do arquivo
    fread(*patients, sizeof(Patient), *numPatients, file);

    // Fechar o arquivo
    fclose(file);
}

void destroyList(Patient **patients, int *numPatients) {
    // Liberar memória da lista de pacientes
    free(*patients);

    // Resetar o número de pacientes
    *numPatients = 0;
}

void fromListToDisk(Patient *patients, int numPatients) {
    checkIfFileExists();
    FILE *file = fopen("patients.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
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
void fromDiskToList(Patient **patients, int *numPatients) {
        checkIfFileExists();
        FILE *patientsFile = fopen("patients.bin", "rb");
        if (patientsFile == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }
        fread(numPatients, sizeof(int), 1, patientsFile);
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

#endif // FILE_LIST_FUNCTIONS_H