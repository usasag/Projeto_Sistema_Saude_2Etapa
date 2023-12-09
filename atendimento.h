// #define PROJETO_SISTEMA_SAUDE_TRABALHO_ATENDIMENTO_H
#include "pacientes.h"
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"
#define MAXcode 1000


/*Variáveis para cada atendimento:
- código* (do atendimento)
- código do paciente*
- tipo* (consulta/retorno)
- data atendimento*
- status (agendado/esperando/em atendimento/atendido)
- preço da consulta (R$)*/

/*As funcionalidades para atendimento são:
- inserir um novo atendimento
- alterar um atendimento existente
- excluir um atendimento
- mostrar/imprimir dados de um atendimento com base no código do atendimento
- mostrar/imprimir todos os atendimentos de uma paciente com base no código desse
paciente
- mostrar/imprimir todos os atendimentos em ordem de data de atendimento*/

/*Outros requisitos para atendimento:
- o código do atendimento não pode estar repetido, ou seja, dois atendimentos não
podem ter o mesmo código. Logo, verifique se já há um atendimento com esse código
ao tentar inserir.
- dois atendimentos de uma mesma pessoa não podem ser marcados para a mesma
data.
- as variáveis com "*" não podem estar vazios ou em branco para um atendimento.*/

/*Funcionalidades gerais:
- mostrar/imprimir a soma das consultas pagas por um determinado paciente
- mostrar/imprimir a soma das consultas pagas para os atendimentos de uma
determinada data de atendimento
- mostrar/imprimir a soma das consultas pagas para os atendimentos de um
determinado período de atendimento (entre uma data inicial e final).*/

int *matrixCode;
void inicializandoMatrixCode()
{
    matrixCode = (int *)malloc(MAXcode * sizeof(int));
}

void limparBuffer() { //função para limpar buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int count = 0;

int CodeGenerator() //função para geração de código
{
    int code = rand() % 99999;
    return code;
}

int CodeCheck(int Code) //função para verificação de divergencia para codigo de atendimento
{
    while(Code == matrixCode[count])
        Code = CodeGenerator();

    matrixCode[count] = Code;
    count++;

    return Code;
}

void atualTime(char *AtualData) //função que verifica a data do dia em tempo de execução
{
    int count = 0;
    time_t AtualTime;
    struct tm *infoTime;
    time(&AtualTime);
    infoTime = localtime(&AtualTime);
    strftime(AtualData, 12, "%Y-%m-%d", infoTime);

}

void addService(int CodeService, int PatientCode, char TypeService[], char ServiceDate[],
                char *status, char *price) //função para adicionar novo atendimento
{
    int typeService, Status;
    CodeCheck(CodeService);
    printf("Seu codigo de atendimento eh: %i\n", &CodeService);

    printf("Insira o codigo do paciente: ");
    scanf("%i", &PatientCode);

    while(typeService != 1 && typeService != 2)
    {
        printf("Selecione o tipo de atendimento: (1) Consulta | (2) Retorno - ");
        scanf("%d", &typeService);
    }

    if(typeService == 1)
        strcpy(TypeService, "Consulta");
    else 
        strcpy(TypeService, "Retorno");

    printf("Insira a data do atendimento: ");
    scanf("%s", ServiceDate);

    while(Status != 1 && Status != 2 && Status != 3 && Status != 4)
    {
        printf("Selecione o status do atendimento: ");
        printf("(1) Agendado | (2) Esperando | (3) Em atendimento | (4) Atendido - ");
        scanf("%i", &Status);
    }

    switch(Status)
    {
        case 1:
            strcpy(status, "Agendado");
            break;
        case 2:
            strcpy(status, "Esperando");
            break;
        case 3:
            strcpy(status, "Em atendimento");
            break;
        case 4:
            strcpy(status, "Atendido");
            break;
    }

    printf("%s\n", status);

    printf("Insira o valor da consulta: ");
    scanf("%s", price);

    printf("\n----------INFORMACOES DO ATENDIMENTO----------\n");
    printf("Codigo do atendimento: %i\n", CodeService);
    printf("Codigo do paciente: %i\n", PatientCode);
    printf("Tipo de atendimento: %s\n", TypeService);
    printf("Data do atendimento: %s\n", ServiceDate);
    printf("Status do atendimento: %s\n", status);
    printf("Preco do atendimento: R$ %s\n", price);


}