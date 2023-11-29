#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum BloodType {
    A, B, AB, O
};

enum RHFactor {
    Positive, Negative
};

enum AppStatus {
    Scheduled, InProgress, Waiting, Completed
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

typedef struct {
    int code;
    int patientCode;
    enum { App, ReturnApp } appType;
    char date[11];
    enum AppStatus status;
    float price;
} Appointment;

void addPatient(Patient **patients, int *numPatients);
void removePatient(Patient **patients, int *numPatients);
void editPatient(Patient *patients, int numPatients);
void printPatient(const Patient *patient); // Incompleta, ainda vou ver como faço

void addAppointment(Appointment **appointments, int *numAppointments, const Patient *patients, int numPatients);
void removeAppointment(Appointment **appointments, int *numAppointments);
void editAppointment(Appointment *appointments, int numAppointments);
void printAppointment(const Appointment *appointment); // Incompleta, ainda vou ver como faço

int generatePatientCode(const Patient *patients, int numPatients);
int generateAppointmentCode(const Appointment *appointments, int numAppointments);

int main()
{
    Patient *patients = NULL;
    int numPatients = 0;

    Appointment *appointments = NULL;
    int numAppointments = 0;

    while (1) {
        printf("--------------------------------------------\n");
        printf("Pacientes:\n");
        printf("\n1. Adicionar Paciente\n");
        printf("2. Remover Paciente\n");
        printf("3. Editar Informacoes do Paciente\n");
        printf("4. Exibir Informacoes do Paciente\n");
        printf("5. Listar Pacientes com Informacoes\n");
        printf("6. Listar Pacientes com Consultas em um Dia\n");
        printf("7. Listar Pacientes por Tipo Sanguineo\n");
        printf("8. Listar Pacientes por Ordem Alfabetica\n");
        printf("\n--------------------------------------------\n");
        printf("Atendimentos:\n");
        printf("\n9. Adicionar Atendimento\n");
        printf("10. Remover Atendimento\n");
        printf("11. Editar Atendimentos\n");
        printf("12. Exibir Atendimentos\n");
        printf("13. Listar Soma dos Atendimentos Pagos por Paciente\n");
        printf("14. Listar Soma dos Atendimentos Pagos em um Dia\n");
        printf("15. Listar Soma dos Atendimentos Pagos por Periodo\n");
        printf("16. Listar Todos os Atendimentos por Ordem de Data Decrescente\n");
        printf("--------------------------------------------\n");
        printf("0. Sair\n");
        printf("--------------------------------------------\n");

        int choice;
        printf("Digite sua escolha: ");
        scanf("%d \n", &choice);

        switch (choice) {
            case 1:
               addPatient(&patients,&numPatients);
                break;
            case 2:
               removePatient(&patients, &numPatients);
                break;
            case 3:
                editPatient(patients, numPatients);
                break;
            case 4:
                // Mostrar as informaçoes do paciente
                break;
            case 5:
                // Exibir lista de pacientes com informações;
                break;
            case 6:
                // Exibir consultas por data;
                break;
            case 7:
                // Mostrar pacientes por tipo sanguineo;
                break;
            case 8:
                // Mostrar pacientes ordenados alfabeticamente;
                break;
            case 9:
                addAppointment(&appointments, &numAppointments, patients, numPatients);
                break;
            case 10:
                removeAppointment(&appointments, &numAppointments);
                break;
            case 11:
                editAppointment(appointments, numAppointments);
                break;
            case 12:
                // Exibir atendimentos;
                break;
            case 13:
                // Mostrar a soma dos valores das consultas por paciente;
                break;
            case 14:
                // Mostrar a soma dos valores das consultas numa data;
                break;
            case 15:
                // Mostrar a soma dos valores das consultas em um periodo especifico;
                break;
            case 16:
                // Mostrar todos os atendimentos por data decrescente;
                break;
            default:
                exit(0);
        }
        free(patients);
        free(appointments);

        return 0;
    }
}
// Função para adicionar paciente
void addPatient(Patient **patients, int *numPatients) {
    // Alocar memória para novo paciente
    *patients = realloc(*patients, (*numPatients + 1) * sizeof(Patient));

    // Acessar o ultimo elemento no array para colocar o novo paciente
    Patient *newPatient = &(*patients)[*numPatients];

    // TODO: Pegar a informação nova do usuário

    // Setar o código do paciente automaticamente
    // TODO: Alguma lógica pra esse código.
    newPatient->code = generatePatientCode(*patients, *numPatients);

    (*numPatients)++;

    // Confirmação que adicionou e o código
    printf("Paciente adicionado com sucesso.\n Codigo do paciente: %d\n", newPatient->code);
}

// Função para editar as infos do paciente
void editPatient(Patient *patients, int numPatients) {
    // TODO: Pegar o código do paciente a ser editado
    // ...

    // TODO: Achar o paciente na array de structs (pelo código)
    // ...

    // TODO: Pedir as informações novas do usuário
    // TODO: Menu com as informações editáveis no mesmo estilo da função "addPatient"
    // ...

    // Print confirmando
    printf("Informacao do paciente editada com sucesso.\n");
}

// Função para remover paciente
void removePatient(Patient **patients, int *numPatients) {
    // TODO Pegar o código do paciente a ser removido
    // ...

    // TODO Achar o paciente na array (pelo código)
    // ...

    // TODO Remover o paciente (deslocar elementos na array)
    // ...

    // Redimensionar a array
    *patients = realloc(*patients, (*numPatients - 1) * sizeof(Patient));

    // Decrementar o número de pacientes
    (*numPatients)--;

    // Print confirmando
    printf("Paciente removido com sucesso.\n");
}

// Função para mostrar informações do paciente
void printPatient(const Patient *patient) {
    // TODO Mostrar informações do paciente
    // ...
}

// Função para adicionar atendimento
void addAppointment(Appointment **appointments, int *numAppointments, const Patient *patients, int numPatients) {
    // Alocar memória para novo atendimento
    *appointments = realloc(*appointments, (*numAppointments + 1) * sizeof(Appointment));

    // Acessar o ultimo elemento no array para colocar o novo atendimento
    Appointment *newAppointment = &(*appointments)[*numAppointments];

    // TODO Pegar informações do atendimento do usuário
    // ...

    // Setar o código do atendimento automaticamente TODO Criar uma lógica pra esse código
    newAppointment->code = generateAppointmentCode(*appointments, *numAppointments);

    // Incrementar o número de atendimentos total
    (*numAppointments)++;

    // Print confirmando e o código do atendimento
    printf("Atendimento adicionado com sucesso.\n Codigo do atendimento: %d\n", newAppointment->code);
}

// Função para editar atendimentos
void editAppointment(Appointment *appointments, int numAppointments) {
    // TODO Pegar o código do atendimento a ser editado
    // ...

    // TODO Achar o atendimento na array de structs
    // ...

    // TODO Pegar as informações novas do usuário
    // TODO Menu com as informações editáveis no mesmo estilo da função "addPatient"
    // ...

    // Print confirmando
    printf("Informação editada com sucesso.\n");
}

// Função para remover um atendimento
void removeAppointment(Appointment **appointments, int *numAppointments) {
    // TODO Pegar o código do atendimento a ser removido
    // ...

    // TODO Achar o atendimento na array de structs
    // ...

    // TODO Remover o atendimento (deslocar os elementos na array)
    // ...

    // Redimensionar a array
    *appointments = realloc(*appointments, (*numAppointments - 1) * sizeof(Appointment));

    // Decrementar o número total de atendimentos
    (*numAppointments)--;

    // Print pra confirmar
    printf("Atendimento removido com sucesso.\n");
}

// Função para mostrar as infos do atendimento
void printAppointment(const Appointment *appointment) {
    // TODO: Mostrar informações do atendimento
    // ...
}

// Função para gerar código único para paciente
int generatePatientCode(const Patient *patients, int numPatients) {
    // TODO: Gerar um código que não exista ainda (comparar pra ver se existe)
    // ...
}

// Função para gerar código único para atendimento
int generateAppointmentCode(const Appointment *appointments, int numAppointments) {
    // TODO: Gerar um código que não exista ainda (comparar pra ver se existe)
    // ...
}
