#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pCode;
    char name[50];
    char RG[15];
    char CPF[15];
    char bType[4];
    char gender[2];
    char rhFactor[2];
    char address[100];
    char DOB[11];
    int age;
} Paciente;

typedef struct {
    int appCode;
    char type[20];
    char date[11];
    char status[25];
    float price;
} Atendimento;

int main() {
    int totalApps = 0;
    int totalPacients = 0;
    int nextPCode = 1000; // Código inicial do paciente

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
                // Adicionar paciente;
                break;
            case 2:
                // Remover Paciente;
                break;
            case 3:
                // Editar dados do Paciente;
                break;
            case 4:
                // Exibir informações do paciente;
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
                // Adicionar atendimento;
                break;
            case 10:
                // Remover atendimentos;
                break;
            case 11:
                // Editar atendimentos;
                break;
            case 12:
                // Exibir atendimentos;
                break;
            case 13:
                // Mostrar a soma dos valores das consultas por paciente;
                break;
            case 14:
                // Mostrar a soma dos valores das consultas em uma data;
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
    }
    return 0;
}
