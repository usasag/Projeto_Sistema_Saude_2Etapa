#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "atendimento.h"

int main()
{
    srand(time(NULL)); 
    
    struct Service
    {
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

    // Aloca espaço para as strings
    AddService.ServiceType = (char *)malloc(50 * sizeof(char));
    AddService.ServiceDate = (char *)malloc(12 * sizeof(char));
    AddService.status = (char *)malloc(20 * sizeof(char));
    AddService.ConsultationValue = (char *)malloc(10 * sizeof(char));

    addService(AddService.CodeService, AddService.PatientCode, AddService.ServiceType,
               AddService.ServiceDate, AddService.status, AddService.ConsultationValue);

    // Libera a memória alocada para as strings
    free(AddService.ServiceType);
    free(AddService.ServiceDate);
    free(AddService.status);
    free(AddService.ConsultationValue);

    return 0;
}
