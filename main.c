// Created by: Vitor Bispo

#include "atendimento.h"

int main()
{
    Patient *patients = NULL;
    int numPatients = 0;

    Appointment *appointments = NULL;
    int numAppointments = 0;

    buildPatientListsFromFile(&patients, &numPatients);
    buildAppointmentListsFromFile(&appointments, &numAppointments);

    while (1)
    {
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
        printf("12. Exibir Atendimentos de um paciente\n");
        printf("13. Listar Soma dos Atendimentos Pagos por Paciente\n");
        printf("14. Listar Soma dos Atendimentos Pagos em um Dia\n");
        printf("15. Listar Soma dos Atendimentos Pagos por Periodo\n");
        printf("16. Listar Todos os Atendimentos por Ordem de Data Decrescente\n");
        printf("--------------------------------------------\n");
        printf("0. Salvar e sair\n");
        printf("--------------------------------------------\n");

        int choice;
        printf("Digite sua escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                writeInfoInFile(patients, numPatients);
                printf("Salvando informacoes em arquivo e saindo...\n");
                free(patients);
                free(appointments);                
                exit(0);
            case 1:
               addPatient(&patients,&numPatients);
                break;
            case 2:
               removePatient(&patients, &numPatients);
                break;
            case 3:
                editPatientInfo(patients, numPatients);
                break;
            case 4:
                printOnePatientInfo(patients, numPatients);
                break;
            case 5:
                listAllPatientsInfo(patients, numPatients);
                break;
            case 6:
                showPatientsWithAppointmentsInADay(patients, numPatients, appointments, numAppointments);
                break;
            case 7:
                showAllPatientsWithSameBloodType(patients, numPatients);
                break;
            case 8:
                showAllPatientsSortedByName(patients, numPatients);
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
                showAppointmentsForAPatient(appointments, numAppointments);
                break;
            case 13:
                showSumOfAppointmentPricesOfPatient(appointments, numAppointments);
                break;
            case 14:
                showSumOfAppointmentPricesInADay(appointments, numAppointments);
                break;
            case 15:
                showSumOfAppointmentPricesInAPeriod(appointments, numAppointments);
                break;
            case 16:
                showAllAppointmentsSortedByDecrescentDate(appointments, numAppointments);
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }
    free(patients);
    free(appointments); 
    return 0;
}