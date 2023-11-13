#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "../utils.h"
#include "ctrl_product.h"

#define true 1
#define false 0


typedef struct sale Sale;

struct sale {
    int id_sale;
    char client_cpf[12];
    char worker_cpf[12];    
    int product_id;
    struct tm date;
    int activated;
};

int choose_product() {
    FILE* p_file;
    Product* pr;
    int found = 0;
    char aux[100] = "";
    char search[255] = "";
    int is_valid = 0;
    char caractere;
    int aux_return = 0;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return 0;
    }
    do
    {
        printf("|||            Nome do produto: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
            while(fread(pr, sizeof(Product), 1, p_file)) {
                strcpy(aux, pr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
                    found++;
                    printf(">> ID [%d] \n", found);
                    print_product(pr);
                    printf("\n");
                }
            }
            fclose(p_file);
            p_file = fopen("db_products.dat", "rb");
            if (found) {  
                printf("Qual produto está sendo comprado (ID)? (Digite 0 para buscar novamente) ");
                int id = 0;
                scanf("%d", &id);
                if ((id > 0) & (id <= found)) {
                    getchar();
                    found = 0;
                    while(fread(pr, sizeof(Product), 1, p_file)) {
                        strcpy(aux, pr->description);
                        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
                            found++;
                            if (found == id)
                            {
                                print_product(pr);
                                aux_return = pr->id_product;
                            }
                        }
                    }
                } else {
                    printf("|||                                                                         |||\n");
                    printf("|||            >> Opção não encontrada!                                     |||\n");
                }
                
            } else {
                printf("|||                                                                         |||\n");
                printf("|||            >> Produto não encontrado!                                    |||\n");
            }

        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    fclose(p_file);
    free(pr);
    return aux_return;
}

// salva a venda em um arquivo
int save_sale(Sale* sl) {
    FILE *p_file; // cria variável ponteiro para o arquivo

    p_file = fopen("db_sales.dat", "ab");
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    int found = 0;
    Sale* aux_sl = (Sale*)malloc(sizeof(Sale));
    while(fread(aux_sl, sizeof(Sale), 1, p_file)) {
        found++;
    }
    free(aux_sl);
    
    sl->id_sale = found + 1;

    fwrite(sl, sizeof(Sale), 1, p_file);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");

    return 0;
}


// Trata os dados para salvar na venda
void insert_sale(char client_cpf[], char worker_cpf[], int product_id) {
    Sale* new_sale = (Sale*)malloc(sizeof(Sale));

    strcpy(new_sale->client_cpf, client_cpf);
    strcpy(new_sale->worker_cpf, worker_cpf);
    new_sale->product_id = product_id;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);    
    new_sale->date = tm;
    new_sale->activated = 1;

    save_sale(new_sale);
    free(new_sale);
}

// Função para imprimir uma venda
void print_sale(Sale* sl) {
    if ((sl == NULL)) {
        printf("\n= = = VENDA INEXISTENTE = = =\n");
    } else {
        printf(" = = = VENDA = = = \n");
        printf("CPF do Funcionário: %s\n", sl->worker_cpf);
        printf("CPF do Cliente: %s\n", sl->client_cpf);
        FILE* p_file;
        Product* pr;
        pr = (Product*) malloc(sizeof(Product));
        p_file = fopen("db_products.dat", "rb");
        if (p_file == NULL) {
            printf("Ops! Erro na abertura do arquivo!\n");
            printf("Não é possível continuar...\n");
            return;
        }

        while(fread(pr, sizeof(Product), 1, p_file)) {
            if ((sl->product_id == pr->id_product) && (pr->activated)) {
                print_product(pr);
            }
        }
        fclose(p_file);
        free(pr);

        printf("Vendido(a) em: %02d/%02d/%04d - %02d:%02d:%02d\n", sl->date.tm_mday, (sl->date.tm_mon + 1), (sl->date.tm_year + 1900), sl->date.tm_hour, sl->date.tm_min, sl->date.tm_sec);

        if (sl->activated) {
            printf("Situação da venda: Ativo \n");
        } else {
            printf("Situação da venda: Inativo \n");
        }        
        printf(" = = = = = = = = = \n");
    }
}

// Função para listar todos os funcionários
void list_sales(void) {
    FILE* p_file;
    Sale* sl;
    int found = 0;
    sl = (Sale*) malloc(sizeof(Sale));
    p_file = fopen("db_sales.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        ---------- VERIFIQUE SE HÁ VENDAS CADASTRADOS! ----------        |||\n");
        return;
    }

    while(fread(sl, sizeof(Sale), 1, p_file)) {
        if (sl->activated) {
            FILE* p_file;
            Product* pr;
            pr = (Product*) malloc(sizeof(Product));
            p_file = fopen("db_products.dat", "rb");
            if (p_file == NULL) {
                printf("Ops! Erro na abertura do arquivo!\n");
                printf("Não é possível continuar...\n");
                return;
            }

            while(fread(pr, sizeof(Product), 1, p_file)) {
                if ((sl->product_id == pr->id_product) && (pr->activated)) {
                    printf("|||        %s | %s | %-16.16s | %02d/%02d/%04d        |||", sl->client_cpf, sl->worker_cpf, pr->description, sl->date.tm_mday, (sl->date.tm_mon + 1), (sl->date.tm_year + 1900));
                }
            }
            fclose(p_file);
            free(pr);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("|||        ---------------- NENHUM VENDA CADASTRADA ----------------        |||\n");

    }
    
    free(sl);
    fclose(p_file);
}


void find_sale(char cpf[]) {
    Sale* sl;
    int found = 0;
    sl = (Sale*) malloc(sizeof(Sale));
    FILE* p_file;
    p_file = fopen("db_sales.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há vendas cadastradas!\n");
        return;
    }
    while(fread(sl, sizeof(Sale), 1, p_file)) {
        if ((strcmp(sl->worker_cpf, cpf) == 0) && (sl->activated)) {
            print_sale(sl);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhuma venda encontrada! \n");
    }
    fclose(p_file);
    free(sl);
}

void remove_sale(char cpf[]) {
    FILE* p_file;
    Sale* sl;
    int found = 0;

    sl = (Sale*) malloc(sizeof(Sale));
    p_file = fopen("db_sales.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Verifique se há vendas cadastradas!\n");
        return;
    }
    
    while(fread(sl, sizeof(Sale), 1, p_file)) {
        if ((strcmp(sl->worker_cpf, cpf) == 0) && (sl->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_sale(sl);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_sales.dat", "r+b");
    if (found) {  
        printf("Qual venda gostaria de remover (ID)? ");
        int id = 0;
        scanf("%d", &id);
        getchar();
        if ((id > 0) & (id <= found)) 
        {
            found = 0;
            while(fread(sl, sizeof(Sale), 1, p_file)) {
                if ((strcmp(sl->worker_cpf, cpf) == 0) && (sl->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            sl->activated = 0;
                            fseek(p_file, -1*sizeof(Sale), SEEK_CUR);
                            fwrite(sl, sizeof(Sale), 1, p_file);
                            printf("\nVenda excluída!\n");
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
        printf("|||            >> Venda não encontrada!                                     |||\n");
    }

    fclose(p_file);
    free(sl);
}