#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "database/ctrl_client.h"
#include "database/ctrl_worker.h"
#include "database/ctrl_sale.h"

#include "utils.h"
#include "aux_functions.h"


// Vendas
/////////////////////////////////////////////////////////////////////////
char sale_menu() {
    int op = -1;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = =  Menu Venda = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            1. Cadastrar um novo venda                                   |||\n");
    printf("|||            2. Listar todas as vendas                                    |||\n");
    printf("|||            3. Pesquisar os dados de um venda                            |||\n");
    printf("|||            4. Excluir um venda do sistema                               |||\n");
    printf("|||            5. Listagem filtrada                                         |||\n");
    printf("|||            6. Listagem ordenada por data                                |||\n");
    printf("|||            0. Voltar ao menu anterior                                   |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Escolha a opção desejada: ");
    scanf("%d", &op);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); getchar();
    return op;
}


void create_sale() {
    char caractere; 
    char client_cpf[12], worker_cpf[12];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = Cadastrar Venda = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            CPF do cliente (apenas números): ");
        scanf("%[0-9]", client_cpf);

        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(client_cpf);
        if (is_valid && has_client(client_cpf)){
            printf("|||            CPF digitado: ");
            int i = 0;
            do
            {
                if (isalnum(client_cpf[i]))
                {
                    printf("%c",client_cpf[i]);
                    if (i==2 || i==5)
                    {
                        printf(".");
                    } else if (i==8)
                    {
                        printf("-");
                    }   
                }
                i++;
            } while (client_cpf[i] != '\0');

            printf("                                 |||\n");
            printf("|||                                                                         |||\n");
        } else if (!has_client(client_cpf))
        {
            printf("|||            CPF digitado inválido. Cliente INEXISTENTE!                  |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!(is_valid && has_client(client_cpf)));

    do
    {
        printf("|||            CPF do funcionário (apenas números): ");
        scanf("%[0-9]", worker_cpf);

        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(worker_cpf);
        if (is_valid && has_worker(worker_cpf)){
            printf("|||            CPF digitado: ");
            int i = 0;
            do
            {
                if (isalnum(worker_cpf[i]))
                {
                    printf("%c",worker_cpf[i]);
                    if (i==2 || i==5)
                    {
                        printf(".");
                    } else if (i==8)
                    {
                        printf("-");
                    }   
                }
                i++;
            } while (worker_cpf[i] != '\0');

            printf("                                 |||\n");
            printf("|||                                                                         |||\n");
        } else if (!has_worker(worker_cpf))
        {
            printf("|||            CPF digitado inválido. Funcionário INEXISTENTE!              |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!(is_valid && has_worker(worker_cpf)));

    insert_sale(client_cpf, worker_cpf, choose_product());
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");

    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_sale() {
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = Pesquisar Venda = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
    printf("|||            CPF do funcionário (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid && has_worker(cpf)){
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
        } else if (!has_worker(cpf))
        {
            printf("|||            CPF digitado inválido. Funcionário INEXISTENTE!              |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!(is_valid && has_worker(cpf)));
    find_sale(cpf);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void all_sales() {
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = Lista de Vendas = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||        - Cliente - | Funcionário | --- Produto ---- | -- Data --        |||\n");
    list_sales();
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void delete_sale() {    
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Excluir Venda  = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
   do
    {
    printf("|||            CPF do funcionário (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid && has_worker(cpf)){
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
        } else if (!has_worker(cpf))
        {
            printf("|||            CPF digitado inválido. Funcionário INEXISTENTE!              |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!(is_valid && has_worker(cpf)));
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    remove_sale(cpf);

    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void filtered_sales() {
    char caractere;
    int is_valid = 0;
    char search[255];
    int exit = 0;
    int op = -1;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = Pesquisar Venda = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    
    while (!exit && !is_valid) {
        printf("|||            Escolha um filtro para a listagem:                           |||\n");
        printf("|||            1- Vendas de hoje                                            |||\n");
        printf("|||            2- Vendas deste mês                                          |||\n");
        printf("|||            3- Vendas desativadas                                        |||\n");
        printf("|||            4- Por nome do funcionário                                   |||\n");
        printf("|||                                                                         |||\n");
        printf("|||            >> Insira: ");
        scanf("%d", &op);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        if (op < 1 || op > 4) {
            printf("|||                                                                         |||\n");
            printf("|||            >> Opção inválida/inexistente!                               |||\n");
            printf("|||                                                                         |||\n");
            printf("|||            Tentar novamente? (s/n) ");
            char opc = 's';
            scanf(" %c", &opc);
            getchar();
            if (opc == 'n')
            {
                exit = 1;
            }
            printf("|||                                                                         |||\n");
        } else {
            is_valid = 1;
        }
        
    }
    is_valid = 0;
    while (!exit && !is_valid && op != 1 && op != 2 && op != 3) {
        printf("|||            Informe o termo buscado: ");
        scanf("%s", search);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  

        printf("|||                                                                         |||\n");
        printf("|||            Está certo disto? (s/n) ");
        char opc = 'n';
        scanf(" %c", &opc);
        getchar();
        if (opc == 's')
        {
            is_valid = 1;
        }
        printf("|||                                                                         |||\n");
    }
    find_sales_by(search, op);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void all_sales_date() {
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = =  Lista de Vendas por Data = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||        - Cliente - | Funcionário | --- Produto ---- | -- Data --        |||\n");
    list_sales_date();
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}