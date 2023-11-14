#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "../utils.h"
#include "ctrl_client.h"
#include "ctrl_animal.h"

#define true 1
#define false 0

typedef struct service Service;

struct service {
    int id_service;
    char description[100];
    char type[100];
    float price;
    int activated;
};


// salva o serviço em um arquivo
int save_service(Service* sr) {
    FILE *p_file; // cria variável ponteiro para o arquivo
    p_file = fopen("db_services.dat", "ab");
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    int found = 0;
    Service* aux_sr = (Service*)malloc(sizeof(Service));
    while(fread(aux_sr, sizeof(Service), 1, p_file)) {
        found++;
    }
    free(aux_sr);

    sr->id_service = found + 1;

    fwrite(sr, sizeof(Service), 1, p_file);
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");
    printf("CADASTRADO COM SUCESSO!!\n");
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