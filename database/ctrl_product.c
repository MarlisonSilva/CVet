#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "../utils.h"
#include "ctrl_client.h"
#include "ctrl_animal.h"
#include "ctrl_sale.h"

#define true 1
#define false 0

typedef struct product Product;

struct product {
    int id_product;
    char description[100];
    char type[100];
    float price;
    int day_expiration;
    int month_expiration;
    int year_expiration;
    int activated;
};

// salva o produto em um arquivo
int save_product(Product* pr) {
    FILE *p_file; 
    p_file = fopen("db_products.dat", "rb");
    int found = 0;
    if(p_file == NULL) {
        found = 1;
    } else {
        Product* aux_pr;
        aux_pr = (Product*)malloc(sizeof(Product));
        while(fread(aux_pr, sizeof(Product), 1, p_file)) {
            found++;
        }
        free(aux_pr);
        fclose(p_file);
    }

    p_file = fopen("db_products.dat", "ab");    
    
    pr->id_product = found + 1;
    fwrite(pr, sizeof(Product), 1, p_file);
    
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

// Trata os dados para salvar no produto
void insert_product(char description[], char type[], float price, int day_expiration, int month_expiration, int year_expiration) {
    Product* new_product = (Product*)malloc(sizeof(Product));

    strcpy(new_product->description, description);
    strcpy(new_product->type, type);
    new_product->price = price;
    new_product->day_expiration = day_expiration;
    new_product->month_expiration = month_expiration;
    new_product->year_expiration = year_expiration;
    new_product->activated = 1;
    save_product(new_product);
    free(new_product);
}

// Função para imprimir um produto
void print_product(Product* pr) {
    
    if ((pr == NULL)) {
        printf("\n= = = PRODUTO INEXISTENTE = = =\n");
    } else {
        printf(" = = = PRODUTO = = = \n");
        printf("ID: %d\n", pr->id_product);
        printf("Descrição: %s\n", pr->description);
        printf("Tipo: %s\n", pr->type);
        printf("Preço: %.2f\n", pr->price);
        printf("Data de validade: %02d/%02d/%04d\n", pr->day_expiration, pr->month_expiration, pr->year_expiration);

        if (pr->activated) {
            printf("Situação do produto: Ativo \n");
        } else {
            printf("Situação do produto: Inativo \n");
        }
        
    }
}

// Função para listar todos os produtos
void list_products(void) {
    FILE* p_file;
    Product* pr;
    int found = 0;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- VERIFIQUE SE HÁ PRODUTOS CADASTRADOS! ---------        |||\n");
        return;
    }

    while(fread(pr, sizeof(Product), 1, p_file)) {
        if (pr->activated) {
            printf("|||        %-23.23s | %-14.14s | R$ %11.2f        |||", pr->description, pr->type, pr->price);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("|||        --------------- NENHUM PRODUTO CADASTRADO ---------------        |||\n");
    }
    
    free(pr);
    fclose(p_file);
}


void find_product(char search[]) {
    FILE* p_file;
    Product* pr;
    char aux[100] = "";
    int found = 0;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há produtos cadastrados!\n");
        return;
    }

    while(fread(pr, sizeof(Product), 1, p_file)) {
        strcpy(aux, pr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
            print_product(pr);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhum produto encontrado! \n");
    }
    fclose(p_file);
    free(pr);
}


void update_product(char search[]) {
    FILE* p_file;
    Product* pr;
    int found = 0;
    char aux[100] = "";
    int is_valid = 0;
    char caractere;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
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
    p_file = fopen("db_products.dat", "r+b");
    if (found) {  
        printf("Qual produto gostaria de editar (ID)? ");
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
                        int updating = 1;
                        do
                        {
                            int op;
                            printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                            printf("|||                                                                         |||\n");
                            printf("|||            Qual informação deseja editar?                               |||\n");
                            printf("|||            [1] Descrição: %s\n", pr->description);
                            printf("|||            [2] Tipo do produto: %s\n", pr->type);
                            printf("|||            [3] Preço: %.2f\n", pr->price);
                            printf("|||            [4] Data de validade: ");
                            if ((pr->day_expiration == 0) && (pr->month_expiration) && (pr->year_expiration)) {
                                printf("INDETERMINADA\n");
                            } else {
                                printf("%02d/%02d/%d\n", pr->day_expiration, pr->month_expiration, pr->year_expiration);
                            }
                            
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
                                        scanf("%[^\n]%*c", pr->description);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(pr->description);
                                        if (is_valid){
                                            printf("|||            Descrição digitada: %s\n", pr->description);
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
                                        scanf("%[^\n]%*c", pr->type);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(pr->type);
                                        if (is_valid){
                                            printf("|||            Tipo/categoria digitado: %s\n", pr->type);
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
                                        scanf("%f", &(pr->price));

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_price(pr->price);
                                        if (is_valid){
                                            printf("|||            Preço digitado: %.2f\n", pr->price);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Preço digitado inválido. Verifique se é maior que 0.         |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 4:
                                    do
                                    {
                                        printf("|||            Validade (dd/mm/aaaa):                                       |||\n");
                                        printf("|||            (NOTA: insira 00/00/0000 para datas indeterminadas)          |||\n");
                                        printf("|||            Digite: ");
                                        scanf("%d%*c%d%*c%d", &(pr->day_expiration), &(pr->month_expiration), &(pr->year_expiration));

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_expiration_date(pr->day_expiration, pr->month_expiration, pr->year_expiration);
                                        if (is_valid){
                                            if (pr->year_expiration == 0 && pr->month_expiration == 0 && pr->day_expiration == 0)
                                            {
                                                printf("|||            Data inserida como \"INDETERMINADA\"                               |||\n");

                                            } else {
                                                printf("|||            Data digitada: %02d/%02d/%04d                                    |||\n", pr->day_expiration, pr->month_expiration, pr->year_expiration);

                                            }
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Data digitada inválida.                                      |||\n");
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
                            
                            fseek(p_file, -1*sizeof(Product), SEEK_CUR);
                            fwrite(pr, sizeof(Product), 1, p_file);
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
        printf("|||            >> Produto não encontrado!                                    |||\n");
    }

    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    fclose(p_file);
    free(pr);
}

void remove_product(char search[]) {
    FILE* p_file;
    Product* pr;
    int found = 0;
    char aux[100] = "";

    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    
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
    p_file = fopen("db_products.dat", "r+b");
    if (found) {  
        printf("Qual produto gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) 
        {
            getchar();
            found = 0;
            while(fread(pr, sizeof(Product), 1, p_file)) {
                strcpy(aux, pr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            pr->activated = 0;
                            fseek(p_file, -1*sizeof(Product), SEEK_CUR);
                            fwrite(pr, sizeof(Product), 1, p_file);
                            printf("\nProduto excluído!\n");
                        } else {
                            printf("\nOperação cancelada!\n");

                        }
                    }
                }
            }
        }
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Produto não encontrado!                                    |||\n");
    }

    fclose(p_file);
    free(pr);
}

void find_products_by(char search[], int opc){
    FILE* p_file;
    Product* pr;
    int found = 0;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há produtos cadastrados!\n");
        return;
    }

    if (opc == 4)
    {
        printf("|||        ------ Descrição ------ | ---- Tipo ---- |  Nº de Vendas         |||\n");
    } else {
        printf("|||        ------ Descrição ------ | ---- Tipo ---- | - Preço Uni. -        |||\n");
    }
    
    while(fread(pr, sizeof(Product), 1, p_file)) {
        switch (opc) {
        case 1:
            if ((strncmp(pr->type, search, strlen(search)) == 0) && (pr->activated)) {
                printf("|||        %-23.23s | %-14.14s | R$ %11.2f        |||", pr->description, pr->type, pr->price);
                found++;
                printf("\n");
            } 
            break;
        case 2:
            if ((pr->day_expiration == 0 && pr->month_expiration == 0 && pr->year_expiration == 0) && (pr->activated)) {
                printf("|||        %-23.23s | %-14.14s | R$ %11.2f        |||", pr->description, pr->type, pr->price);
                found++;
                printf("\n");
            } 
            break;
        case 3:
            if (!(pr->activated)) {
                printf("|||        %-23.23s | %-14.14s | R$ %11.2f        |||", pr->description, pr->type, pr->price);
                found++;
                printf("\n");
            } 
            break;
        case 4:
            if (pr->activated) {
                int count = 0;
                FILE* p_file_sl;
                Sale* sl;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                sl = (Sale*) malloc(sizeof(Sale));
                p_file_sl = fopen("db_sales.dat", "rb");
                if (p_file_sl == NULL) {
                    printf("Ops! Erro na abertura do arquivo!\n");
                    printf("Verifique se há vendas cadastradas!\n");
                    return;
                }
                while(fread(sl, sizeof(Sale), 1, p_file_sl)){
                    if (((sl->date.tm_year + 1900) == (tm.tm_year + 1900)) && (sl->date.tm_mon == tm.tm_mon) && (sl->activated) && (sl->product_id == pr->id_product)) {
                        count++;
                    }
                }
                fclose(p_file_sl);
                free(sl);
                if (count > 0)
                {
                    printf("|||        %-23.23s | %-14.14s |    %11d        |||", pr->description, pr->type, count);
                    found++;
                    printf("\n");
                }
            }
        default:
            break;
        }
        
    }
    if (found == 0)
    {
        printf("|||                        NENHUM PRODUTO ENCONTRADO                        |||\n");
    }
    
    fclose(p_file);
    free(pr);
}

Product* get_product(int product_id) {
    FILE* p_file;
    Product* pr;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há produtos cadastrados!\n");
        return NULL;
    }
    while(fread(pr, sizeof(Product), 1, p_file) && (pr->id_product != product_id));
    fclose(p_file);
    return pr;
}