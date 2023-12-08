#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "../utils.h"
#include "ctrl_service.h"
#include "ctrl_client.h"
#include "ctrl_animal.h"
#include "ctrl_appointment.h"

#define true 1
#define false 0

// salva o serviço em um arquivo
int save_service(Service* sr) {
    FILE *p_file; 
    p_file = fopen("db_services.dat", "rb");
    int found = 0;
    if(p_file != NULL) {
        Service* aux_sr;
        aux_sr = (Service*)malloc(sizeof(Service));
        while(fread(aux_sr, sizeof(Service), 1, p_file)) {
            found = aux_sr->id_service;
        }
        free(aux_sr);
        fclose(p_file);
    }

    p_file = fopen("db_services.dat", "ab");    
    
    sr->id_service = found + 1;
    sr->next = NULL;
    fwrite(sr, sizeof(Service), 1, p_file);
    
    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Dados gravados:                                              |||\n");
    printf("|||            >> CADASTRADO FINALIZADO COM SUCESSO!                        |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    return 0;
}

// Trata os dados para salvar no serviço
void insert_service(char description[], char type[], float price) {
    Service* new_service = (Service*)malloc(sizeof(Service));

    strcpy(new_service->description, description);
    strcpy(new_service->type, type);
    new_service->price = price;
    new_service->activated = 1;
    save_service(new_service);
    free(new_service);
}

// Função para imprimir um serviço
void print_service(Service* sr) {
    if ((sr == NULL)) {
        printf("\n= = = SERVIÇO INEXISTENTE = = =\n");
    } else {
        printf(" = = = SERVIÇO = = = \n");
        printf("Descrição: %s\n", sr->description);
        printf("Tipo: %s\n", sr->type);
        printf("Preço: %.2f\n", sr->price);
        
        if (sr->activated) {
            printf("Situação do serviço: Ativo \n");
        } else {
            printf("Situação do serviço: Inativo \n");
        }
        
    }
}

// Função para listar todos os serviços
void list_services(void) {
    FILE* p_file;
    Service* sr;
    int found = 0;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- VERIFIQUE SE HÁ SERVIÇOS CADASTRADOS! ---------        |||\n");
        return;
    }

    while(fread(sr, sizeof(Service), 1, p_file)) {
        if (sr->activated) {
            printf("|||        %-23.23s | %-14.14s | R$ %11.2f        |||", sr->description, sr->type, sr->price);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("|||        --------------- NENHUM SERVIÇO CADASTRADO ---------------        |||\n");

    }
    
    free(sr);
    fclose(p_file);
}


void find_service(char search[]) {
    FILE* p_file;
    Service* sr;
    int found = 0;
    char aux[100] = "";
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há serviços cadastrados!\n");
        return;
    }

    while(fread(sr, sizeof(Service), 1, p_file)) {
        strcpy(aux, sr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
            print_service(sr);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhum serviço encontrado! \n");
    }
    fclose(p_file);
    free(sr);
}


void update_service(char search[]) {
    FILE* p_file;
    Service* sr;
    int found = 0;
    char aux[100] = "";
    int is_valid = 0;
    char caractere;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    while(fread(sr, sizeof(Service), 1, p_file)) {
        strcpy(aux, sr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_service(sr);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_services.dat", "r+b");
    if (found) {  
        printf("Qual serviço gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) {
            getchar();
            found = 0;
            while(fread(sr, sizeof(Service), 1, p_file)) {
                strcpy(aux, sr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
                    found++;
                    if (found == id)
                    {
                        int updating = 1;
                        do
                        {
                            int op;
                            printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                            printf("|||                                                                         |||\n");
                            printf("|||            Qual informação deseja editar?                               |||\n");
                            printf("|||            [1] Descrição: %s\n", sr->description);
                            printf("|||            [2] Tipo do serviço: %s\n", sr->type);
                            printf("|||            [3] Preço: %.2f\n", sr->price);
                            printf("|||            [0] Finalizar edição                                         |||\n");
                            printf("|||                                                                         |||\n");
                            printf("|||            >> Opção: ");
                            scanf("%d", &op);
                            getchar();

                            switch (op) {
                                case 1:
                                    do
                                    {
                                        printf("|||            Descrição: ");
                                        scanf("%[^\n]%*c", sr->description);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(sr->description);
                                        if (is_valid){
                                            printf("|||            Descrição digitada: %s\n", sr->description);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Descrição digitada inválida.                                 |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 2:
                                    do
                                    {
                                        printf("|||            Tipo/categoria: ");
                                        scanf("%[^\n]%*c", sr->type);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(sr->type);
                                        if (is_valid){
                                            printf("|||            Tipo/categoria digitado: %s\n", sr->type);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Tipo/categoria digitada inválida.                            |||\n");
                                            printf("|||            Digite apenas letras e espaços.                              |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 3:
                                    do
                                    {
                                        printf("|||            Preço: ");
                                        scanf("%f", &(sr->price));

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_price(sr->price);
                                        if (is_valid){
                                            printf("|||            Preço digitado: %.2f\n", sr->price);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Preço digitado inválido. Verifique se é maior que 0.         |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 0:
                                    printf("|||            >> Edição finalizada!                                        |||\n");
                                    printf("|||                                                                         |||\n");
                                    updating = 0;
                                    break;
                                default:
                                    printf("|||            >> Opção inexistente!                                        |||\n");
                                    printf("|||                                                                         |||\n");
                                    break;
                            }
                            
                            fseek(p_file, -1*sizeof(Service), SEEK_CUR);
                            fwrite(sr, sizeof(Service), 1, p_file);
                        } while (updating);
                    }
                }
            }
        } else {
            printf("|||                                                                         |||\n");
            printf("|||            >> Opção não encontrada!                                     |||\n");

        }
        
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Serviço não encontrado!                                    |||\n");
    }

    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    fclose(p_file);
    free(sr);
}

void remove_service(char search[]) {
    FILE* p_file;
    Service* sr;
    int found = 0;
    char aux[100] = "";

    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    
    while(fread(sr, sizeof(Service), 1, p_file)) {
        strcpy(aux, sr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_service(sr);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_services.dat", "r+b");
    if (found) {  
        printf("Qual serviço gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) 
        {
            getchar();
            found = 0;
            while(fread(sr, sizeof(Service), 1, p_file)) {
                strcpy(aux, sr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            sr->activated = 0;
                            fseek(p_file, -1*sizeof(Service), SEEK_CUR);
                            fwrite(sr, sizeof(Service), 1, p_file);
                            printf("\nServiço excluído!\n");
                        } else {
                            printf("\nOperação cancelada!\n");

                        }
                    }
                }
            }
        }
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Serviço não encontrado!                                    |||\n");
    }

    fclose(p_file);
    free(sr);
}

void find_services_by(char search[], int opc){
    FILE* p_file;
    Service* sr;
    int found = 0;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há produtos cadastrados!\n");
        return;
    }

    if (opc == 3) {
        printf("|||        ------- Serviço ------- | ---- Tipo ---- | Nº de Consult.        |||\n");
    } else if (opc == 4) {
        printf("|||        ------- Serviço ------- | --- Animal --- | Data Consulta         |||\n");
    } else {
        printf("|||        ------- Serviço ------- | ---- Tipo ---- | - Preço Uni. -        |||\n");
    }
    
    while(fread(sr, sizeof(Service), 1, p_file)) {
        switch (opc) {
        case 1:
            if ((strncmp(sr->type, search, strlen(search)) == 0) && (sr->activated)) {
                printf("|||        %-23.23s | %-14.14s | R$ %11.2f        |||", sr->description, sr->type, sr->price);
                found++;
                printf("\n");
            } 
            break;
        case 2:
            if (!(sr->activated)) {
                printf("|||        %-23.23s | %-14.14s | R$ %11.2f        |||", sr->description, sr->type, sr->price);
                found++;
                printf("\n");
            } 
            break;
        case 3:
           if (sr->activated) {
                int count = 0;
                FILE* p_file_ap;
                Appointment* ap;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                ap = (Appointment*) malloc(sizeof(Appointment));
                p_file_ap = fopen("db_appointments.dat", "rb");
                if (p_file_ap == NULL) {
                    printf("Ops! Erro na abertura do arquivo!\n");
                    printf("Verifique se há consultas cadastradas!\n");
                    return;
                }
                while(fread(ap, sizeof(Appointment), 1, p_file_ap)){
                    if (((ap->date.tm_year + 1900) == (tm.tm_year + 1900)) && (ap->date.tm_mon == tm.tm_mon) && (ap->activated) && (ap->service_id == sr->id_service)) {
                        count++;
                    }
                }
                fclose(p_file_ap);
                if (count > 0)
                {
                    printf("|||        %-23.23s | %-14.14s |    %11d        |||", sr->description, sr->type, count);
                    found++;
                    printf("\n");
                }
                free(ap);
            }
            break;
        case 4:
           if (sr->activated) {
                FILE* p_file_ap;
                Appointment* ap;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                ap = (Appointment*) malloc(sizeof(Appointment));
                p_file_ap = fopen("db_appointments.dat", "rb");
                if (p_file_ap == NULL) {
                    printf("Ops! Erro na abertura do arquivo!\n");
                    printf("Verifique se há consultas cadastradas!\n");
                    return;
                }
                while(fread(ap, sizeof(Appointment), 1, p_file_ap)){
                    if (((ap->date.tm_year + 1900) == (tm.tm_year + 1900)) && (ap->date.tm_mon == tm.tm_mon) && (ap->activated) && (ap->service_id == sr->id_service)) {
                        printf("|||        %-23.23s | %-14.14s |    %02d/%02d/%04d         |||", sr->description, get_animal(ap->animal_id)->name, ap->date.tm_mday, (ap->date.tm_mon + 1), (ap->date.tm_year + 1900));
                        found++;
                        printf("\n");
                    }
                }
                fclose(p_file_ap);
                free(ap);
            }
            break;
        default:
            break;
        }
        
    }
    if (found == 0)
    {
        printf("|||                        NENHUM SERVIÇO ENCONTRADO                        |||\n");
    }
    
    fclose(p_file);
    free(sr);
}

void list_services_az(void) {
    FILE* p_file;
    Service* sr;
    Service* services = NULL;
    Service* aux_sr;
    int found = 0;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- VERIFIQUE SE HÁ SERVIÇOS CADASTRADOS! ---------        |||\n");
        return;
    }

    while(fread(sr, sizeof(Service), 1, p_file)) {
        if (sr->activated) {
            if ((services == NULL) || (strcmp(sr->description, services->description) < 0)) {
                // substitui o topo da lista
                sr->next = services;
                services = sr;
            } else {
                Service* prev = services;
                Service* curr = services->next;
                while ((curr != NULL) && (strcmp(curr->description, sr->description) < 0)) {
                    prev = curr;
                    curr = curr->next;
                }
                prev->next = sr;
                sr->next = curr;
            }
            sr = (Service *) malloc(sizeof(Service));
            found++;
        }
    }

    free(sr);
    fclose(p_file);
    aux_sr = services;
    do {
        printf("|||        %-23.23s | %-14.14s | R$ %11.2f        |||", aux_sr->description, aux_sr->type, aux_sr->price);
        printf("\n");
        aux_sr = aux_sr->next;
    } while (aux_sr != NULL);
    
    if (found == 0) {
        printf("|||        --------------- NENHUM SERVIÇO CADASTRADO ---------------        |||\n");
    }
    clear_service(services);
}

void clear_service(Service* sr){
    Service* aux_sr;

    while (sr != NULL) {
        aux_sr = sr;
        sr = sr->next;
        free(aux_sr);
    }  
}

Service* get_service(int service_id) {
    FILE* p_file;
    Service* sr;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há serviços cadastrados!\n");
        return NULL;
    }
    while(fread(sr, sizeof(Service), 1, p_file) && (sr->id_service != service_id));
    fclose(p_file);
    return sr;
}