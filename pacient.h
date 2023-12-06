#ifndef PROJETO_SISTEMA_SAUDE_2ETAPA_PACIENT_H
#define PROJETO_SISTEMA_SAUDE_2ETAPA_PACIENT_H
#include "file_list_functions.h"


void getRequiredInput(char *input, const char *fieldName, int maxLength);
void addPatient(Patient **patients, int *numPatients);
void removePatient(Patient **patients, int *numPatients);
void showAllPatientsWithSameBloodType(Patient *patients, int numPatients);
void showAllPatientsSortedByName(Patient *patients, int numPatients);
void bubbleSort(Patient *patients, int numPatients);
void showPatientsWithAppointmentsInADay(Patient *patients, int numPatients, Appointment *appointments, int numAppointments);
void editPatientInfo(Patient *patients, int numPatients);
void listAllPatientsInfo(Patient *patients, int numPatients);
void printOnePatientInfo(Patient *patients, int numPatients);

int compareDates(const char *date1, const char *date2);
void checkIfPatientsExist(int numPatients);
void clearBuffer();
int generatePatientCode(Patient *patients, int numPatients);
int findPatient(const Patient *patients, int numPatients, int code);


void clearBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
}

int generatePatientCode(Patient *patients, int numPatients) {
        if (numPatients == 0) {
            return 1;
        }

        int maxCode = 0;
        for (int i = 0; i < numPatients; i++) {
            if (patients[i].code > maxCode) {
                maxCode = patients[i].code;
            }
        }

        return maxCode + 1;
    }

void checkIfPatientsExist(int numPatients) {
        if (numPatients == 0) {
            printf("Nao existem pacientes cadastrados. Adicione um paciente e tente novamente.\n");
            return;
        }
    }

void getRequiredInput(char *input, const char *fieldName, int maxLength) {
        do {
            clearBuffer();
            printf("Informe %s: ", fieldName);
            scanf("%s", input);

            if (strlen(input) == 0 || strlen(input) >= maxLength) {
                printf("Esta informacao e obrigatoria, por favor informe %s.\n", fieldName);
            }
        } while (strlen(input) == 0 || strlen(input) >= maxLength);
    }

void addPatient(Patient **patients, int *numPatients) {
    // Alocar memória para novo paciente
    *patients = realloc(*patients, (*numPatients + 1) * sizeof(Patient));

    // Acessar o ultimo elemento no array para colocar o novo paciente
    Patient *newPatient = &(*patients)[*numPatients];

    // Pegar informação do paciente
    getRequiredInput(newPatient->name, "nome do paciente*", 50);

    printf("Informe o RG do paciente: ");
    scanf("%s", newPatient->RG);

    getRequiredInput(newPatient->CPF, "CPF do paciente*", 12);

    // Checar CPF duplicado
    for (int i = 0; i < *numPatients; i++) {
        if (strcmp((*patients)[i].CPF, newPatient->CPF) == 0) {
            printf("CPF ja existe, por favor verifique o CPF e tente novamente.\n");
            *patients = realloc(*patients, (*numPatients) * sizeof(Patient));
            return;
        }
    }

    // Pegar tipo sanguíneo
    printf("Informe o tipo sanguineo do paciente"
           "\n1. A"
           "\n2. B"
           "\n3. AB"
           "\n4. O"
           "\n");
    int bloodTypeInput;
    scanf("%d", &bloodTypeInput);

    switch (bloodTypeInput) {
        case 1:
            newPatient->bloodType = A;
            break;
        case 2:
            newPatient->bloodType = B;
            break;
        case 3:
            newPatient->bloodType = AB;
            break;
        case 4:
            newPatient->bloodType = O;
            break;
        default:
            printf("Tipo sanguineo nao informado, informacao sera deixada em branco.\n");
            break;
    }

    // Pegar fator RH
    printf("Informe o Fator RH (+/-): ");
    int rhFactorInput;
    scanf(" %d", &rhFactorInput);

    switch (rhFactorInput) {
        case 1:
            newPatient->rhFactor = Positive;
            break;
        case 2:
            newPatient->rhFactor = Negative;
            break;
        default:
            printf("Fator RH nao informado, informacao sera deixada em branco.\n");
            break;
    }

    // Pegar o endereço do paciente
    
        printf("Informe o endereço do paciente: ");
        scanf("%s", newPatient->address);
    do {
                    getRequiredInput(newPatient->dob, "data de nascimento do paciente (dd/mm/aaaa)*", 11);
                    if (!isValidDate(newPatient->dob)) {
                        printf("Data invalida! Por favor digite uma data valida!\n"
                               "Formato: (dd/mm/aaaa)\n"
                               "Exemplo: 01/01/2000\n");
                    }
                } while(!isValidDate(newPatient->dob));

    newPatient->code = generatePatientCode(newPatient, *numPatients);

    (*numPatients)++;

    // Confirmação que adicionou e printar o código
    printf("Paciente adicionado com sucesso.\n Codigo do paciente: %d\n", newPatient->code);
}

int findPatient(const Patient *patients, int numPatients, int code) {
    checkIfPatientsExist(numPatients);
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].code == code) {
            return i;
        }
    }
    return -1;
}

void removePatient(Patient **patients, int *numPatients) {
    checkIfPatientsExist(*numPatients);
    // Pegar o código do paciente
    int code;
    printf("Informe o codigo do paciente: ");
    scanf("%d", &code);

    // Procurar o paciente pelo código
    int index = findPatient(*patients, *numPatients, code);
   
    // Se não encontrar, mostrar mensagem de erro e retornar
    if (index == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    // Se encontrar, remover o paciente
    for (int i = index; i < *numPatients - 1; i++) {
        (*patients)[i] = (*patients)[i + 1];
    }

    // Diminuir o número de pacientes
    *patients = realloc(*patients, (*numPatients - 1) * sizeof(Patient));
    (*numPatients)--;

    // Mostrar mensagem de sucesso
    printf("Paciente removido com sucesso.\n");
}

void editPatientInfo(Patient *patients, int numPatients) {
    checkIfPatientsExist(numPatients);
    // Pegar o código do paciente
    int code;
    printf("Informe o codigo do paciente: ");
    scanf("%d", &code);

    // Procurar o paciente pelo código
    int index = findPatient(patients, numPatients, code);

    // Se não encontrar, mostrar mensagem de erro e retornar
    if (index == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    int field;
    do {
        // Se encontrar, pegar a informação que deseja editar
        printf("Informe o campo que deseja editar: "
               "\n1. Nome"
               "\n2. RG"
               "\n3. CPF"
               "\n4. Tipo sanguineo"
               "\n5. Fator RH"
               "\n6. Endereco"
               "\n7. Data de nascimento"
               "\nEnter para sair da edicao..."
               "\n");
        scanf("%d", &field);

        // Pegar a nova informação
        switch (field) {
            case 1:
                getRequiredInput(patients[index].name, "nome do paciente", 50);
                break;
            case 2:
                getRequiredInput(patients[index].RG, "RG do paciente", 15);
                break;
            case 3:
                getRequiredInput(patients[index].CPF, "CPF do paciente", 12);
                break;
            case 4:
                printf("Informe o tipo sanguineo do paciente"
                       "\n1. A"
                       "\n2. B"
                       "\n3. AB"
                       "\n4. O"
                       "\n");
                int bloodTypeInput;
                scanf("%d", &bloodTypeInput);

                switch (bloodTypeInput) {
                    case 1:
                        patients[index].bloodType = A;
                        break;
                    case 2:
                        patients[index].bloodType = B;
                        break;
                    case 3:
                        patients[index].bloodType = AB;
                        break;
                    case 4:
                        patients[index].bloodType = O;
                        break;
                    default:
                        printf("Tipo sanguineo nao informado, informacao sera deixada em branco.\n");
                        break;
                }
                break;
            case 5:
                printf("Informe o tipo sanguineo do paciente: ");
                int rhFactorInput;
                scanf("%d", &rhFactorInput);

                switch (rhFactorInput) {
                    case 1:
                        patients[index].rhFactor = Positive;
                        break;
                    case 2:
                        patients[index].rhFactor = Negative;
                        break;
                    default:
                        printf("Fator RH nao informado, informacao sera deixada em branco.\n");
                        break;
                }
                break;
            case 6:
                printf("Informe o endereço do paciente: ");
                scanf("%s", patients[index].address);
                if (strlen(patients[index].address) == 0) {
                    printf("Endereco nao informado, informacao sera deixada em branco.\n");
                }
                break;
            case 7:
                do {
                    getRequiredInput(patients[index].dob, "data de nascimento do paciente (dd/mm/aaaa)*", 11);
                    if (!isValidDate(patients[index].dob)) {
                        printf("Data invalida! Por favor digite uma data valida!\n"
                               "Formato: (dd/mm/aaaa)\n"
                               "Exemplo: 01/01/2000\n");
                    }
                } while(!isValidDate(patients[index].dob));
                break;
            default:
                printf("Saindo...\n");
                break;
        }
    } while (field != 0);

    // Mostrar mensagem de sucesso
    printf("Paciente editado com sucesso.\n");
}

void listAllPatientsInfo(Patient *patients, int numPatients) {
    checkIfPatientsExist(numPatients);
    printf("\n-----------------\n"); // Divisor
    for (int i = 0; i < numPatients; i++) {
        printf("Codigo: %d\n", patients[i].code);
        printf("Nome: %s\n", patients[i].name);
        printf("CPF: %s\n", patients[i].CPF);
        printf("Data de nascimento: %s\n", patients[i].dob);
        printf("\n-----------------\n"); // Divisor
    }
}

void printOnePatientInfo(Patient *patients, int numPatients) {
    checkIfPatientsExist(numPatients);
    // Pegar o código do paciente
    int code;
    printf("Informe o codigo do paciente: ");
    scanf("%d", &code);

    // Procurar o paciente pelo código
    int index = findPatient(patients, numPatients, code);

    // Se não encontrar, mostrar mensagem de erro e retornar
    if (index == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    // Se encontrar, mostrar as informações do paciente
    printf("Codigo: %d\n", patients[index].code);
    printf("Nome: %s\n", patients[index].name);
    printf("RG: %s\n", patients[index].RG);
    printf("CPF: %s\n", patients[index].CPF);
    printf("Tipo sanguineo: %d\n", patients[index].bloodType);
    printf("Fator RH: %d\n", patients[index].rhFactor);
    printf("Endereco: %s\n", patients[index].address);
    printf("Data de nascimento: %s\n", patients[index].dob);
    printf("\n");
}

void showAllPatientsWithSameBloodType(Patient *patients, int numPatients) {
    checkIfPatientsExist(numPatients);
    // Pegar o tipo sanguíneo
    printf("Informe o tipo sanguineo a ser procurado"
           "\n1. A"
           "\n2. B"
           "\n3. AB"
           "\n4. O"
           "\n");
    int bloodTypeInput;
    scanf("%d", &bloodTypeInput);

    // Mostrar todos os pacientes com o tipo sanguíneo informado
    // CPF nao e relevante pra essa lista
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].bloodType == bloodTypeInput) {
            printf("Codigo: %d\n", patients[i].code);
            printf("Nome: %s\n", patients[i].name);
            printf("Tipo sanguineo: %d\n", patients[i].bloodType);
            printf("Data de nascimento: %s\n", patients[i].dob); 
            printf("\n-----------------\n"); // Divisor
        }
    }
}

void bubbleSort(Patient *patients, int numPatients) {
    for (int i = 0; i < numPatients - 1; i++) {
        for (int j = 0; j < numPatients - i - 1; j++) {
            if (strcmp(patients[j].name, patients[j + 1].name) > 0) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }
}

void showAllPatientsSortedByName(Patient *patients, int numPatients) {
    checkIfPatientsExist(numPatients);
    bubbleSort(patients, numPatients);
    listAllPatientsInfo(patients, numPatients);
}

void showPatientsWithAppointmentsInADay(Patient *patients, int numPatients, Appointment *appointments, int numAppointments) {
    checkIfPatientsExist(numPatients);
    // Pegar a data
    char date[11];
    getRequiredInput(date, "data (dd/mm/aaaa)", 11);

    // Mostrar todos os pacientes com consultas na data informada
    for (int i = 0; i < numAppointments; i++) {
        if (compareDates(appointments[i].date, date) == 0) {
            int patientIndex = findPatient(patients, numPatients, appointments[i].patientCode);
            if (patientIndex != -1) {
                printf("Codigo: %d\n", patients[patientIndex].code);
                printf("Nome: %s\n", patients[patientIndex].name);
                printf("Data: %s\n", appointments[i].date);
                printf("Preco: %.2f\n", appointments[i].price);
                printf("\n-----------------\n"); // Divisor
            }
        }
    }
}

#endif // PROJETO_SISTEMA_SAUDE_2ETAPA_PACIENT_H