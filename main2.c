#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "atendimento.h"

int main()
{
    struct Service{
        int CodeService;
        int PatientCode;
        int serviceType; 
        char *ServiceType;
        char *ServiceDate;
        int Status;
        char *status;
        char *ConsultationValue;
    };
    typedef struct Service service;
    service AddService;

    // int mainMenu, secondMenu;
    // printf("-----MENU-----\n");
    // printf("(1) - New service\n");
    // printf("(2) - Change service\n");
    // printf("(3) - Delete service\n");
    // printf("(4) - Show service data with code\n");
    // printf("(4) - Show all patient visits\n");
    // printf("(4) - Show all calls based on day\n");
    // printf("Select the desired option: ");
    // scanf("%i", &mainMenu);

    addService(AddService.CodeService, AddService.PatientCode, AddService.ServiceType,
                AddService.ServiceDate, AddService.status, AddService.ConsultationValue);

    
    

    

}