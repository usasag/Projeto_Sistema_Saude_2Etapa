#ifndef PROJETO_SISTEMA_SAUDE_2ETAPA_ATENDIMENTO_H
#define PROJETO_SISTEMA_SAUDE_2ETAPA_ATENDIMENTO_H

#include <stdbool.h>
#include "pacient.h"

void addAppointment(Appointment **appointments, int *numAppointments, const Patient *patients, int numPatients);
void removeAppointment(Appointment **appointments, int *numAppointments);
void editAppointment(Appointment *appointments, int numAppointments);

void showAppointmentsForAPatient(const Appointment *appointments, int numAppointments);
void showSumOfAppointmentPricesInADay(const Appointment *appointments, int numAppointments);
void showSumOfAppointmentPricesInAPeriod(const Appointment *appointments, int numAppointments);
void showSumOfAppointmentPricesOfPatient(const Appointment *appointments, int numAppointments);
void showAllAppointmentsSortedByDecrescentDate(const Appointment *appointments, int numAppointments);

int generateAppointmentCode(const Appointment *appointments, int numAppointments);
int findAppointment(const Appointment *appointments, int numAppointments, int code);
bool isValidDate(const char* date);
void checkIfAppointmentsExist(int numAppointments);

void checkIfAppointmentsExist(int numAppointments) {
    if (numAppointments == 0) {
        printf("Nao ha consultas agendadas! Adicione uma consulta e tente novamente.\n");
        exit(1);
    }
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

int generateAppointmentCode(const Appointment *appointments, int numAppointments) {
    int maxCode = 0;
    for (int i = 0; i < numAppointments; i++) {
        if (appointments[i].code >= maxCode) {
            maxCode = appointments[i].code + 1;
        }
    }
    return maxCode;
}

void addAppointment(Appointment **appointments, int *numAppointments, const Patient *patients, int numPatients) {

    Appointment appointment;

    int patientCode;
    printf("Digite o codigo do paciente: ");
    scanf("%d", &patientCode);
    
    if (findPatient(patients, numPatients, patientCode) == -1) {
        printf("Paciente nao encontrado!\n");
        return;
    }

    appointment.code = generateAppointmentCode(*appointments, *numAppointments);
    appointment.patientCode = patientCode;

    do {
        int appointmentType;
    printf("Digite o tipo de consulta\n"
    "0 - Consulta\n"
    "1 - Retorno\n "
    "Digite sua escolha: ");
    scanf("%d", &appointmentType);
    switch (appointmentType)
    {
    case 0:
        appointment.appointmentType = Consulta;
        break;
    case 1:
        appointment.appointmentType = Retorno;
        break;
    default:
        printf("Tipo de consulta invalido! Por favor escolha um tipo valido\n");
    }
    } while (appointment.appointmentType != Consulta && appointment.appointmentType != Retorno);
    
    do {
        printf("Digite a data da consulta (dd/mm/aaaa): ");
        scanf("%s", appointment.date);
        if (!isValidDate(appointment.date)) {
            printf("Data invalida! Por favor digite uma data valida!\n"
                 "Formato: (dd/mm/aaaa)\n"
                 "Exemplo: 01/01/2000\n");
        }
    } while (!isValidDate(appointment.date));
    appointment.status = Agendado;

    printf("Digite o preco da consulta: ");
    scanf("%f", &appointment.price);

    *numAppointments += 1;
    *appointments = (Appointment *) realloc(*appointments, *numAppointments * sizeof(Appointment));
    (*appointments)[*numAppointments - 1] = appointment;

    printf("Consulta cadastrada com sucesso! Codigo do atendimento: %d\n", appointment.code);
}

int findAppointment(const Appointment *appointments, int numAppointments, int code) {
    checkIfAppointmentsExist(numAppointments);
    for (int i = 0; i < numAppointments; i++) {
        if (appointments[i].code == code) {
            return i;
        }
    }
    return -1;
}

void removeAppointment(Appointment **appointments, int *numAppointments) {
    checkIfAppointmentsExist(*numAppointments);
    int code;
    printf("Digite o codigo do atendimento: ");
    scanf("%d", &code);
    int index = findAppointment(*appointments, *numAppointments, code);
    if (index == -1) {
        printf("Atendimento nao encontrado!\n");
        return;
    }
    for (int i = index; i < *numAppointments - 1; i++) {
        (*appointments)[i] = (*appointments)[i + 1];
    }
    *numAppointments -= 1;
    *appointments = (Appointment *) realloc(*appointments, *numAppointments * sizeof(Appointment));
    printf("Atendimento removido com sucesso!\n");
}

void editAppointment(Appointment *appointments, int numAppointments) {
    checkIfAppointmentsExist(numAppointments);
    int code;
    printf("Digite o codigo do atendimento: ");
    scanf("%d", &code);

    int index = findAppointment(appointments, numAppointments, code);
    if (index == -1) {
        printf("Atendimento nao encontrado!\n");
        return;
    }

    int choice;
    printf("Selecione qual informacao deseja alterar:\n");
    printf("1. Tipo de consulta\n");
    printf("2. Data da consulta\n");
    printf("3. Preco da consulta\n");
    printf("--------------------\n");
    printf("0. Cancelar\n\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Digite o novo tipo de consulta (0 - Consulta, 1 - Retorno): ");
            scanf("%d", &appointments[index].appointmentType);
            break;
        case 2:
            printf("Digite a nova data da consulta (dd/mm/aaaa): ");
            scanf("%s", appointments[index].date);
            break;
        case 3:
            printf("Digite o novo preco da consulta: ");
            scanf("%f", &appointments[index].price);
            break;
        default:
            printf("Saindo...\n");
            return;
    }

    printf("Atendimento editado com sucesso!\n");
}

void showAppointmentsForAPatient(const Appointment *appointments, int numAppointments) {
    checkIfAppointmentsExist(numAppointments);
    int patientCode;
    printf("Digite o codigo do paciente: ");
    scanf("%d", &patientCode);

    printf("Codigo\tCodigo do Paciente\tTipo de Consulta\tData\tStatus\tPreco\n");
    for (int i = 0; i < numAppointments; i++) {
        if (appointments[i].patientCode == patientCode) {
            printf("%d\t%d\t%d\t%s\t%d\t%.2f\n", appointments[i].code, appointments[i].patientCode, appointments[i].appointmentType, appointments[i].date, appointments[i].status, appointments[i].price);
        }
    }
}

void showSumOfAppointmentPricesInAPeriod(const Appointment *appointments, int numAppointments) {
    checkIfAppointmentsExist(numAppointments);
    char startDate[11], endDate[11];
    printf("Digite a data inicial: ");
    scanf("%s", startDate);
    while (!isValidDate(startDate)) {
        printf("Data invalida. Digite novamente a data inicial: ");
        scanf("%s", startDate);
    }

    printf("Digite a data final: ");
    scanf("%s", endDate);
    while (!isValidDate(endDate)) {
        printf("Data invalida. Digite novamente a data final: ");
        scanf("%s", endDate);
    }

    float sum = 0;
    for (int i = 0; i < numAppointments; i++) {
        if (strcmp(appointments[i].date, startDate) >= 0 && strcmp(appointments[i].date, endDate) <= 0) {
            sum += appointments[i].price;
        }
    }
    printf("Soma dos precos das consultas no periodo: %.2f\n", sum);
}

void showSumOfAppointmentPricesOfPatient(const Appointment *appointments, int numAppointments) {
    checkIfAppointmentsExist(numAppointments);
    int patientCode;
    printf("Digite o codigo do paciente: ");
    scanf("%d", &patientCode);

    float sum = 0.0;
    for (int i = 0; i < numAppointments; i++) {
        if (appointments[i].patientCode == patientCode) {
            sum += appointments[i].price;
        }
    }
    printf("Soma dos precos das consultas do paciente: %.2f\n", sum);
}

int compareDates(const char *date1, const char *date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1, "%d/%d/%d", &day1, &month1, &year1);
    sscanf(date2, "%d/%d/%d", &day2, &month2, &year2);

    if (year1 != year2) {
        return year2 - year1;
    }
    if (month1 != month2) {
        return month2 - month1;
    }
    return day2 - day1;
}

void showAllAppointmentsSortedByDecrescentDate(const Appointment *appointments, int numAppointments) {
    checkIfAppointmentsExist(numAppointments);
    Appointment *sortedAppointments = (Appointment *) malloc(numAppointments * sizeof(Appointment));
    for (int i = 0; i < numAppointments; i++) {
        sortedAppointments[i] = appointments[i];
    }

    for (int i = 0; i < numAppointments; i++) {
        for (int j = i + 1; j < numAppointments; j++) {
            if (compareDates(sortedAppointments[i].date, sortedAppointments[j].date) < 0) {
                Appointment temp = sortedAppointments[i];
                sortedAppointments[i] = sortedAppointments[j];
                sortedAppointments[j] = temp;
            }
        }
    }

    printf("Codigo\tCodigo do Paciente\tTipo de Consulta\tData\tStatus\tPreco\n");
    for (int i = 0; i < numAppointments; i++) {
        printf("%d\t%d\t%d\t%s\t%d\t%.2f\n", sortedAppointments[i].code, sortedAppointments[i].patientCode, sortedAppointments[i].appointmentType, sortedAppointments[i].date, sortedAppointments[i].status, sortedAppointments[i].price);
    }
    free(sortedAppointments);
}

void showSumOfAppointmentPricesInADay(const Appointment *appointments, int numAppointments) {
    checkIfAppointmentsExist(numAppointments);
    char date[11];
    printf("Digite a data: ");
    scanf("%s", date);

    float sum = 0;
    for (int i = 0; i < numAppointments; i++) {
        if (compareDates(appointments[i].date, date) == 0) {
            sum += appointments[i].price;
        }
    }
    printf("Soma dos precos das consultas no dia: %.2f\n", sum);
}

#endif //PROJETO_SISTEMA_SAUDE_2ETAPA_ATENDIMENTO_H