// #define PROJETO_SISTEMA_SAUDE_TRABALHO_ATENDIMENTO_H
#include "pacientes.h"


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

void limparBuffer() { //função para limpar buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int CodeGenerator(int code) //função para geração de código
{
    srand(time(NULL));
    code = rand() % 900 + 100;

    return code;
}

int CodeCheck(int Code) //função para verificação de divergencia para codigo de atendimento
{
    
    CodeGenerator(Code);
    int *matrixArmaz = NULL;
    static int count = 0;
    matrixArmaz = (int *)malloc(50 * sizeof(int));
    while (Code == *matrixArmaz)
        CodeGenerator(Code);
    matrixArmaz[count] = Code;
    count++;
    free(matrixArmaz);

    return Code;
}

void atualTime(char *AtualData) //função que verifica a data do dia em tempo de execução
{
    time_t AtualTime;
    struct tm *infoTime;
    time(&AtualTime);
    infoTime = localtime(&AtualTime);
    strftime(AtualData, 12, "%Y-%m-%d", infoTime);

}

int addService(int CodeService, int PatientCode, char TypeService[], char ServiceDate[],
                char status[]) //função para adicionar novo atendimento
{
    atualTime(ServiceDate);

    CodeService =  CodeCheck(CodeService);
    printf("%i", CodeService);

    FILE *newService;
    newService = fopen("Services.txt", "w");
    fprintf(newService, "%d\n", CodeService);

    newService = fopen("Services.txt", "a");
    fprintf(newService, "%d\n", PatientCode);

    newService = fopen("Services.txt", "a");
    fprintf(newService, "%s\n", TypeService);

    newService = fopen("Services.txt", "a");
    fprintf(newService, "%s\n", ServiceDate);

    newService = fopen("Services.txt", "a");
    fprintf(newService, "%s\n", status);


    
}
