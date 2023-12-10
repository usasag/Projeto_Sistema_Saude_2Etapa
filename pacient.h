#ifndef PROJETO_SISTEMA_SAUDE_2ETAPA_PACIENT_H
#define PROJETO_SISTEMA_SAUDE_2ETAPA_PACIENT_H

#include "atendimento.h"


void getRequiredInput(char *input, const char *fieldName, int maxLength);
void addPatient(Patient **patients, int *numPatients);
void removePatient(Patient **patients, int *numPatients, Appointment **appointments, int *numAppointments);
void showAllPatientsWithSameBloodType(Patient *patients, int numPatients);
void showAllPatientsSortedByName(Patient *patients, int numPatients);
void bubbleSort(Patient *patients, int numPatients);
void showPatientsWithAppointmentsInADay(Patient *patients, int numPatients, Appointment *appointments, int numAppointments);
void editPatientInfo(Patient *patients, int numPatients);
void listAllPatientsInfo(Patient *patients, int numPatients);
void printOnePatientInfo(Patient *patients, int numPatients);

bool checkIfPatientsExist(int numPatients);
void clearBuffer();
int generatePatientCode(Patient *patients, int numPatients);


void clearBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
}

int generatePatientCode(Patient *patients, int numPatients) {
    srand(time(NULL)); // Seeda o gerador de números aleatórios com o tempo atual

    int newCode;
    int unique;

    do {
        unique = 1;
        newCode = rand() % 90000 + 10000; // Gerar um número aleatório entre 10000 e 99999

        for (int i = 0; i < numPatients; i++) {
            if (patients[i].code == newCode) {
                unique = 0;
                break;
            }
        }
    } while (unique == 0);

    return newCode;
}

bool checkIfPatientsExist(int numPatients) {
        if (numPatients == 0) {
            return false;
        } else {
            return true;
        }
    }

void getRequiredInput(char *input, const char *fieldName, int maxLength) {
    do {
        printf("Informe %s: ", fieldName);
        fgets(input, maxLength, stdin);

        // Remove o \n da string
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            printf("Esta informacao e obrigatoria, por favor informe %s.\n", fieldName);
        } else if (strlen(input) >= maxLength - 1) {
            printf("Limite de caracteres (%d) ultrapassado, verifique a informacao e tente novamente.\n", maxLength - 1);
        }
    } while (strlen(input) == 0 || strlen(input) >= maxLength - 1);
}

void addPatient(Patient **patients, int *numPatients) {
    // Alocar memória para novo paciente
    *patients = realloc(*patients, (*numPatients + 1) * sizeof(Patient));

    // Acessar o ultimo elemento no array para colocar o novo paciente
    Patient *newPatient = &(*patients)[*numPatients];

    // Pegar nome do paciente
    getRequiredInput(newPatient->name, "nome do paciente*", 50);

    // Pegar o genero do paciente
    printf("Informe o genero biologico do paciente:\n"
           "1. Masculino\n"
           "2. Feminino\n"
           "Digite qualquer outro numero caso nao informado...\n"
    );
    int genderInput;
    scanf("%d", &genderInput);

    switch (genderInput) {
        case 1:
            newPatient->gender = Male;
            break;
        case 2:
            newPatient->gender = Female;
            break;
        default:
            printf("Genero nao informado, informacao sera dada como indefinida.\n");
            newPatient->gender = UNDEFINED_GENDER;
            break;
    }

    // Pegar RG do paciente
    clearBuffer();
    printf("Informe o RG do paciente: ");
    if (fgets(newPatient->RG, sizeof(newPatient->RG), stdin) != NULL) {
        newPatient->RG[strcspn(newPatient->RG, "\n")] = '\0';
    }
    if (strlen(newPatient->RG) == 0) {
        printf("RG nao informado, informacao sera deixada em branco.\n");
    }

    // Pegar CPF do paciente
    do {
        getRequiredInput(newPatient->CPF, "CPF do paciente*", 12);
        if (strlen(newPatient->CPF) != 11) {
            printf("CPF deve conter 11 digitos. Por favor, informe novamente.\n");
        }
    } while (strlen(newPatient->CPF) != 11);

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
           "\nDigite qualquer outro numero caso nao informado...\n");
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
            newPatient->bloodType = UNDEFINED_BLOOD;
            break;
    }
    clearBuffer();

    // Pegar fator RH
    if (newPatient->bloodType == UNDEFINED_BLOOD) {
        printf("O tipo sanguineo e indefinido, logo o fator RH nao pode ser definido.\n");
        newPatient->rhFactor = UNDEFINED_RH;
    } else {
        printf("Informe o Fator RH: \n"
               "1. + (Positivo)\n"
               "2. - (Negativo)\n"
               "Digite qualquer outro numero caso nao informado...\n");
        int rhFactorInput;
        scanf("%d", &rhFactorInput);

        switch (rhFactorInput) {
            case 1:
                newPatient->rhFactor = Positive;
                break;
            case 2:
                newPatient->rhFactor = Negative;
                break;
            default:
                printf("Fator RH nao informado, informacao sera deixada em branco.\n");
                newPatient->rhFactor = UNDEFINED_RH;
                break;
        }
        clearBuffer();
    }

    // Pegar o endereço do paciente
    printf("Informe o endereco do paciente: ");
    if (fgets(newPatient->address, sizeof(newPatient->address), stdin) != NULL) {
        newPatient->address[strcspn(newPatient->address, "\n")] = '\0';
    }
    if (strlen(newPatient->address) == 0) {
        printf("Endereco nao informado, informacao sera deixada em branco.\n");
    }

    // Pegar a data de nascimento do paciente
    while (1) {
        getRequiredInput(newPatient->dob, "data de nascimento do paciente (dd/mm/aaaa)*", 11);
        if (isValidDate(newPatient->dob)) {
            break;
        }
        printf("Data invalida! Por favor digite uma data valida!\n"
               "Formato: (dd/mm/aaaa)\n"
               "Exemplo: 01/01/2000\n");
    }

    newPatient->code = generatePatientCode(newPatient, *numPatients);

    (*numPatients)++;

    // Confirmação que adicionou e printar o código
    printf("Paciente adicionado com sucesso.\n Codigo do paciente: %d\n", newPatient->code);
}

void removePatient(Patient **patients, int *numPatients, Appointment **appointments, int *numAppointments) {
    if (!checkIfPatientsExist(*numPatients))
    {
        printf("Nao existem pacientes cadastrados. Adicione um paciente e tente novamente.\n");
        return;
    }
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

    // Remover consultas do paciente
    removeAllAppointmentsOfAPatient(appointments, numAppointments, code);

    // Mostrar mensagem de sucesso
    printf("Paciente removido com sucesso.\n");
}

void editPatientInfo(Patient *patients, int numPatients) {
    char newCPF[12];
    if (!checkIfPatientsExist(numPatients))
    {
        printf("Nao existem pacientes cadastrados. Adicione um paciente e tente novamente.\n");
        return;
    }
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
        printf("Informe o campo que deseja editar: ");
        printf("\n1. Nome: %s", patients[index].name);
        printf("\n2. Genero: %s", genderStrings[patients[index].gender]);
        printf("\n3. RG: %s", patients[index].RG);
        printf("\n4. CPF: %s", patients[index].CPF);
        printf("\n5. Tipo sanguineo: %s", bloodTypeStrings[patients[index].bloodType]);
        printf("\n6. Fator RH: %s", rhFactorStrings[patients[index].rhFactor]);
        printf("\n7. Endereco: %s", patients[index].address);
        printf("\n8. Data de nascimento: %s", patients[index].dob);
        printf("\n0. Sair da edicao...");
        printf("\n");
        scanf("%d", &field);
        clearBuffer();

        // Pegar a nova informação
        switch (field) {
            case 1:
                getRequiredInput(patients[index].name, "nome do paciente", 50);
                break;
            case 2:
                printf("Informe o genero do paciente:\n"
                  "1. Masculino\n"
                   "2. Feminino\n"
                   "\nDigite qualquer outro numero caso nao informado...\n"
                );
                int genderInput;
                scanf("%d", &genderInput);

                switch (genderInput) {
                    case 1:
                        patients[index].gender = Male;
                        break;
                    case 2:
                        patients[index].gender = Female;
                        break;
                    default:
                        printf("Genero nao informado, informacao sera dada como indefinida.\n");
                        patients[index].gender = UNDEFINED_GENDER;
                        break;
                }
                break;
            case 3:
                printf("Informe o RG do paciente: ");
                fgets(patients->RG, sizeof(patients[index].RG), stdin);

// Remover o caractere de nova linha do final da string se estiver presente
                if (patients[index].RG[strlen(patients[index].RG) - 1] == '\n') {
                    patients[index].RG[strlen(patients[index].RG) - 1] = '\0';
                }
                break;
            case 4:
                getRequiredInput(newCPF, "CPF do paciente", 12);

                // Checar CPF duplicado
                int duplicateCPF = 0;
                for (int i = 0; i < numPatients; i++) {
                    if (i != index && strcmp(newCPF, patients[i].CPF) == 0) {
                        duplicateCPF = 1;
                        break;
                    }
                }

                if (duplicateCPF) {
                    printf("CPF ja existe. Nao foi possivel editar o CPF do paciente.\n");
                    break;
                } else {
                    strcpy(patients[index].CPF, newCPF);
                    break;
                }
            case 5:
                printf("Informe o tipo sanguineo do paciente"
                       "\n1. A"
                       "\n2. B"
                       "\n3. AB"
                       "\n4. O"
                       "\nDigite qualquer outro numero caso nao informado...\n");
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
                        printf("Opcao invalida, tipo sanguineo nao informado, informacao dada como indefinida.\n");
                        patients[index].bloodType = UNDEFINED_BLOOD;
                        patients[index].rhFactor = UNDEFINED_RH;
                        break;
                }
                break;
            case 6:
                if (patients[index].bloodType == UNDEFINED_BLOOD) {
                    printf("O tipo sanguineo nao foi informado, logo o fator RH nao pode ser definido.\n");
                    patients[index].rhFactor = UNDEFINED_RH;
                    break;
                } else {
                    printf("Informe o fator RH do paciente:\n"
                           "1. + (Positivo)\n"
                           "2. - (Negativo)\n"
                    );
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
                            printf("Fator RH nao informado, informacao sera dada como indefinida.\n");
                            patients[index].rhFactor = UNDEFINED_RH;
                            break;
                    }
                }
                break;
            case 7:
                printf("Informe o endereco do paciente: ");
                if (fgets(patients[index].address, sizeof(patients[index].address), stdin) != NULL) {
                    patients[index].address[strcspn(patients[index].address, "\n")] = '\0';
                }
                if (strlen(patients[index].address) == 0) {
                    printf("Endereco nao informado, informacao sera deixada em branco.\n");
                }
                break;
            case 8:
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
}

void listAllPatientsInfo(Patient *patients, int numPatients) {
    if (!checkIfPatientsExist(numPatients))
    {
        printf("Nao existem pacientes cadastrados. Adicione um paciente e tente novamente.\n");
        return;
    }
    printf("-----------------\n"); // Divisor
    for (int i = 0; i < numPatients; i++) {
        printf("Codigo: %d\n", patients[i].code);
        printf("Nome: %s\n", patients[i].name);
        printf("Data de nascimento: %s\n", patients[i].dob);
        printf("-----------------\n"); // Divisor
    }
}

void printOnePatientInfo(Patient *patients, int numPatients) {
    if (!checkIfPatientsExist(numPatients))
    {
        printf("Nao existem pacientes cadastrados. Adicione um paciente e tente novamente.\n");
        return;
    }
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
    printf("Genero: %s\n", genderStrings[patients[index].gender]);
    printf("RG: %s\n", patients[index].RG);
    printf("CPF: %s\n", patients[index].CPF);
    printf("Tipo sanguineo: %s\n", bloodTypeStrings[patients[index].bloodType]);
    printf("Fator RH: %s\n", rhFactorStrings[patients[index].rhFactor]);
    printf("Endereco: %s\n", patients[index].address);
    printf("Data de nascimento: %s\n", patients[index].dob);
    printf("\n");
}

void showAllPatientsWithSameBloodType(Patient *patients, int numPatients) {
    if (!checkIfPatientsExist(numPatients))
    {
        printf("Nao existem pacientes cadastrados. Adicione um paciente e tente novamente.\n");
        return;
    }
    // Pegar o tipo sanguíneo
    printf("Informe o tipo sanguineo a ser procurado"
           "\n0. A"
           "\n1. B"
           "\n2. AB"
           "\n3. O"
           "\n");
    int bloodTypeInput;
    scanf("%d", &bloodTypeInput);

    // Mostrar todos os pacientes com o tipo sanguíneo informado
    // CPF nao e relevante pra essa lista
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].bloodType == bloodTypeInput) {
            printf("Codigo: %d\n", patients[i].code);
            printf("Nome: %s\n", patients[i].name);
            printf("Tipo sanguineo: %s\n", bloodTypeStrings[patients[i].bloodType]);
            printf("Fator RH: %s\n", rhFactorStrings[patients[i].rhFactor]);
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
    if (!checkIfPatientsExist(numPatients))
    {
        printf("Nao existem pacientes cadastrados. Adicione um paciente e tente novamente.\n");
        return;
    }
    bubbleSort(patients, numPatients);
    listAllPatientsInfo(patients, numPatients);
}

// TODO A função está funcionando, mas é necessário verificar se existem pacientes e consultas, caso contrário, retornar uma mensagem de erro
void showPatientsWithAppointmentsInADay(Patient *patients, int numPatients, Appointment *appointments, int numAppointments) {
    if (!checkIfPatientsExist(numPatients))
    {
        printf("Nao existem pacientes cadastrados. Adicione um paciente e tente novamente.\n");
        return;
    }
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