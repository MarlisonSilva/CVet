#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "../utils.h"
#include "ctrl_appointment.h"
#include "ctrl_service.h"
#include "ctrl_animal.h"
#include "ctrl_client.h"

#define true 1
#define false 0


int choose_service() {
    FILE* p_file;
    Service* sr;
    int found = 0;
    char aux[100] = "";
    char search[255] = "";
    int is_valid = 0;
    char caractere;
    int aux_return = 0;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return 0;
    }
    do
    {
        printf("|||            Nome do serviço: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
            found = 0;
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
            p_file = fopen("db_services.dat", "rb");
            if (found) {  
                printf("Qual serviço está sendo adquirido (ID)? (Digite 0 para buscar novamente) ");
                int id = 0;
                scanf("%d", &id);
                getchar();
                if ((id > 0) & (id <= found)) {
                    found = 0;
                    while(fread(sr, sizeof(Service), 1, p_file)) {
                        strcpy(aux, sr->description);
                        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
                            found++;
                            if (found == id)
                            {
                                print_service(sr);
                                aux_return = sr->id_service;
                            }
                        }
                    }
                } else if (id == 0) {
                    is_valid = false;
                } else {
                    printf("|||                                                                         |||\n");
                    printf("|||            >> Opção não encontrada!                                     |||\n");
                }
                
            } else {
                printf("|||                                                                         |||\n");
                printf("|||            >> Serviço não encontrado!                                    |||\n");
                printf("Tentar novamente? (s/n)");
                char opc = 'n';
                scanf(" %c", &opc);
                getchar();
                if (opc == 's')
                {
                    is_valid = false;
                }
            }

        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    fclose(p_file);
    free(sr);
    return aux_return;
}

int choose_animal() {
    FILE* p_file;
    Animal* an;
    int found = 0;
    char aux[100] = "";
    char search[255] = "";
    int is_valid = 0;
    char caractere;
    int aux_return = 0;
    char cpf[12] = "";
    do
    {
        printf("|||            CPF do tutor (apenas números): ");
        scanf("%[0-9]", cpf);

        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid && has_client(cpf)){
            printf("|||            CPF digitado: ");
            int i = 0;
            do
            {
                if (isalnum(cpf[i]))
                {
                    printf("%c",cpf[i]);
                    if (i==2 || i==5)
                    {
                        printf(".");
                    } else if (i==8)
                    {
                        printf("-");
                    }   
                }
                i++;
            } while (cpf[i] != '\0');

            printf("                                 |||\n");
            printf("|||                                                                         |||\n");
        } else if (!has_client(cpf))
        {
            printf("|||            CPF digitado inválido. Cliente INEXISTENTE!                  |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!(is_valid && has_client(cpf)));

    an = (Animal*) malloc(sizeof(Animal));
    p_file = fopen("db_animals.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return 0;
    }
    do
    {
        printf("|||            Nome do animal: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
            found = 0;
            while(fread(an, sizeof(Animal), 1, p_file)) {
                if ((strcmp(an->cpf, cpf) == 0) && (an->activated)) {
                    strcpy(aux, an->name);
                    if (strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) {
                        found++;
                        printf(">> ID [%d] \n", found);
                        print_animal(an);
                        printf("\n");
                    }
                }
            }
            fclose(p_file);
            p_file = fopen("db_animals.dat", "rb");
            if (found) {  
                printf("Qual animal está adquirindo o serviço (ID)? (Digite 0 para buscar novamente) ");
                int id = 0;
                scanf("%d", &id);
                getchar();
                if ((id > 0) & (id <= found)) {
                    found = 0;
                    while(fread(an, sizeof(Animal), 1, p_file)) {
                        strcpy(aux, an->name);
                        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (an->activated)) {
                            found++;
                            if (found == id)
                            {
                                print_animal(an);
                                aux_return = an->id_animal;
                            }
                        }
                    }
                } else if (id == 0) {
                    is_valid = false;
                } else {
                    printf("|||            >> Opção não encontrada!                                     |||\n");
                    printf("|||                                                                         |||\n");
                }
                
            } else {
                printf("|||            >> Animal não encontrado!                                    |||\n");
                printf("|||                                                                         |||\n");
                printf("Tentar novamente? (s/n)");
                char opc = 'n';
                scanf(" %c", &opc);
                getchar();
                if (opc == 's')
                {
                    is_valid = false;
                }
                
            }

        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    fclose(p_file);
    free(an);
    return aux_return;
}

// salva a consulta em um arquivo
int save_appointment(Appointment* ap) {
    FILE *p_file; 
    p_file = fopen("db_appointments.dat", "rb");
    int found = 0;
    if(p_file == NULL) {
        found = 1;
    } else {
        Appointment* aux_ap;
        aux_ap = (Appointment*)malloc(sizeof(Appointment));
        while(fread(aux_ap, sizeof(Appointment), 1, p_file)) {
            found++;
        }
        free(aux_ap);
        fclose(p_file);
    }

    p_file = fopen("db_appointments.dat", "ab");    
    
    ap->id_appointment = found + 1;
    fwrite(ap, sizeof(Appointment), 1, p_file);
    
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

// Trata os dados para salvar na venda
void insert_appointment(char worker_cpf[], int animal_id, int service_id) {
    Appointment* new_appointment = (Appointment*)malloc(sizeof(Appointment));

    strcpy(new_appointment->worker_cpf, worker_cpf);
    new_appointment->animal_id = animal_id;
    new_appointment->service_id = service_id;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);    
    new_appointment->date = tm;
    new_appointment->activated = 1;

    save_appointment(new_appointment);
    free(new_appointment);
}

// Função para imprimir uma venda
void print_appointment(Appointment* ap) {
    if ((ap == NULL)) {
        printf("\n= = = CONSULTA INEXISTENTE = = =\n");
    } else {
        printf(" = = = CONSULTA = = = \n");
        printf("CPF do Funcionário: %s\n", ap->worker_cpf);
        FILE* p_file;
        Animal* an;
        an = (Animal*) malloc(sizeof(Animal));
        p_file = fopen("db_animals.dat", "rb");
        if (p_file == NULL) {
            printf("Ops! Erro na abertura do arquivo!\n");
            printf("Não é possível continuar...\n");
            return;
        }

        while(fread(an, sizeof(Animal), 1, p_file)) {
            if ((ap->animal_id == an->id_animal) && (an->activated)) {
                print_animal(an);
            }
        }
        fclose(p_file);
        free(an);

        Service* sr;
        sr = (Service*) malloc(sizeof(Service));
        p_file = fopen("db_services.dat", "rb");
        if (p_file == NULL) {
            printf("Ops! Erro na abertura do arquivo!\n");
            printf("Não é possível continuar...\n");
            return;
        }

        while(fread(sr, sizeof(Service), 1, p_file)) {
            if ((ap->service_id == sr->id_service) && (sr->activated)) {
                print_service(sr);
            }
        }
        fclose(p_file);
        free(sr);

        printf("Realizado em: %02d/%02d/%d - %02d:%02d:%02d\n", ap->date.tm_mday, ap->date.tm_mon, (ap->date.tm_year + 1900), ap->date.tm_hour, ap->date.tm_min, ap->date.tm_sec);

        if (ap->activated) {
            printf("Situação da consulta: Ativo \n");
        } else {
            printf("Situação da consulta: Inativo \n");
        }        
        printf(" = = = = = = = = = \n");
    }
}

// Função para listar todos os funcionários
void list_appointments(void) {
    FILE* p_file;
    Appointment* ap;
    int found = 0;
    ap = (Appointment*) malloc(sizeof(Appointment));
    p_file = fopen("db_appointments.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        -------- VERIFIQUE SE HÁ CONSULTAS CADASTRADOS! ---------        |||\n");
        return;
    }

    while(fread(ap, sizeof(Appointment), 1, p_file)) {
        if (ap->activated) {
            char* animal_name = NULL;
            char* service_desc = NULL;
            FILE* p_file;
            Service* sr;
            sr = (Service*) malloc(sizeof(Service));
            p_file = fopen("db_services.dat", "rb");
            if (p_file == NULL) {
                printf("Ops! Erro na abertura do arquivo!\n");
                printf("Não é possível continuar...\n");
                return;
            }

            while(fread(sr, sizeof(Service), 1, p_file)) {
                if ((ap->service_id == sr->id_service) && (sr->activated)) {
                    service_desc = (char*) malloc(sizeof(sr->description));
                    strcpy(service_desc, sr->description);
                }
            }
            fclose(p_file);
            free(sr);
            

            Animal* an;
            an = (Animal*) malloc(sizeof(Animal));
            p_file = fopen("db_animals.dat", "rb");
            if (p_file == NULL) {
                printf("Ops! Erro na abertura do arquivo!\n");
                printf("Não é possível continuar...\n");
                return;
            }
            while(fread(an, sizeof(Animal), 1, p_file)) {
                if ((ap->animal_id == an->id_animal) && (an->activated)) {
                    animal_name = (char*) malloc(sizeof(an->name));
                    strcpy(animal_name, an->name);
                }
            }
            fclose(p_file);
            free(an);
            printf("|||        %s | %-14.14s | %-13.13s | %02d/%02d/%04d        |||", ap->worker_cpf, animal_name, service_desc, ap->date.tm_mday, (ap->date.tm_mon + 1), (ap->date.tm_year + 1900));
            
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("|||        -------------- NENHUM CONSULTA CADASTRADA ---------------        |||\n");
    }
    
    free(ap);
    fclose(p_file);
}


void find_appointment(char cpf[]) {
    Appointment* ap;
    int found = 0;
    ap = (Appointment*) malloc(sizeof(Appointment));
    FILE* p_file;
    p_file = fopen("db_appointments.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há consultas cadastradas!\n");
        return;
    }
    while(fread(ap, sizeof(Appointment), 1, p_file)) {
        if ((strcmp(ap->worker_cpf, cpf) == 0) && (ap->activated)) {
            print_appointment(ap);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhuma consulta encontrada! \n");
    }
    fclose(p_file);
    free(ap);
}

void remove_appointment(char cpf[]) {
    FILE* p_file;
    Appointment* ap;
    int found = 0;

    ap = (Appointment*) malloc(sizeof(Appointment));
    p_file = fopen("db_appointments.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Verifique se há consultas cadastradas!\n");
        return;
    }
    
    while(fread(ap, sizeof(Appointment), 1, p_file)) {
        if (((strcmp(ap->worker_cpf, cpf) == 0)) && (ap->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_appointment(ap);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_appointments.dat", "r+b");
    if (found) {  
        printf("Qual consulta gostaria de remover (ID)? ");
        int id = 0;
        scanf("%d", &id);
        getchar();
        if ((id > 0) & (id <= found)) 
        {
            found = 0;
            while(fread(ap, sizeof(Appointment), 1, p_file)) {
                if ((strcmp(ap->worker_cpf, cpf) == 0) && (ap->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            ap->activated = 0;
                            fseek(p_file, -1*sizeof(Appointment), SEEK_CUR);
                            fwrite(ap, sizeof(Appointment), 1, p_file);
                            printf("\nConsulta excluída!\n");
                        } else {
                            printf("\nOperação cancelada!\n");

                        }
                    }
                }
            }
        } else {
            printf("Opção inválida! \n");
        }
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Consulta não encontrada!                                     |||\n");
    }

    fclose(p_file);
    free(ap);
}

void find_appointments_by(char search[], int opc){
    
}

Appointment* get_appointment(int appointment_id) {
    FILE* p_file;
    Appointment* ap;
    ap = (Appointment*) malloc(sizeof(Appointment));
    p_file = fopen("db_appointments.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há consultas cadastradas!\n");
        return NULL;
    }
    while(fread(ap, sizeof(Appointment), 1, p_file) && (ap->id_appointment != appointment_id));
    fclose(p_file);
    return ap; 
}