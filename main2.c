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

    printf("Enter the patient code: ");
    AddService.ServiceType = (char *)malloc(sizeof(char[10]));
    scanf("%i", &AddService.PatientCode);

    AddService.ServiceDate = (char *)malloc(sizeof(char[12]));

    printf("Select the type of service:\n");
    printf("1 - Query\n2 - Return\n");
    scanf("%i", &AddService.serviceType);

    switch(AddService.serviceType)
    {
        case 1:
            AddService.ServiceType = "Query";
            break;
        case 2:
            AddService.ServiceType = "Return";
            break;
        default:
            printf("Please enter a valid option!");
            return -1;
    }

    printf("Select a status option: ");
    printf("\n1 - Scheduled\n2 - Waiting\n3 - In service\n4 - Serviced\n");
    scanf("%i", &AddService.Status);

    switch(AddService.Status)
    {
        case 1:
            AddService.status = "Scheduled";
            break;
        case 2:
            AddService.status = "Waiting";
            break;
        case 3:
            AddService.status = "In service";
            break;
        case 4:
            AddService.status = "Serviced";
            break;
        default: 
            printf("Please enter a valid option!");
            return -2;
    }
    
    addService(AddService.CodeService, AddService.PatientCode, 
            AddService.ServiceType, AddService.ServiceDate, AddService.status);

}