#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int CodeGenerator(int Code)
{
    srand(time(NULL));
    for (int i = 0; i < 5; i++) 
        Code = rand();
    return Code;
}

void NewService()
{   
    int serviceStorage;
    struct Service{
        int ServiceCode, PatientCode; // Required fields
        char TypeService[10], ServiceHours[10], Status[20]; // Required fields - TypeService
        char ServiceDate; // Required fields
        float ConsultationPrice;
        char DayDate[12];
    };

    typedef struct Service NewService;

    NewService service;
    CodeGenerator(service.ServiceCode);

    printf("Enter patient code: ");
    scanf("%i", &service.PatientCode);
    limparBuffer();

    printf("Enter the service date: ");
    scanf("%c", &service.ServiceDate);
    limparBuffer();

    printf("Select the type of service: (1 - Query | 2 - Return): ");
    fgets(service.ServiceDate, sizeof(service.ServiceDate),stdin);
    limparBuffer();

    if(serviceStorage == 1)
        strcpy(service.TypeService, "Query");
    else if(serviceStorage == 2)
        strcpy(service.TypeService, "Return");
    else
        printf("Please enter a valid entry.\n");

    time_t t;
    struct tm *current_date_time;
    time(&t);
    current_date_time = localtime(&t);

    if (service.ServiceDate == current_date_time)
    {


    }
    




}