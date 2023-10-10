#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "service.h"
#include "utils.h"
#include "aux_functions.h"

// Serviços
/////////////////////////////////////////////////////////////////////////
char service_menu() {
    int op = -1;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Menu Serviço = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            1. Cadastrar um novo serviço                                 |||\n");
    printf("|||            2. Pesquisar os dados de um serviço                          |||\n");
    printf("|||            3. Atualizar o cadastro de um serviço                        |||\n");
    printf("|||            4. Excluir um serviço do sistema                             |||\n");
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


void create_service() {
    char caractere; 
    char description[100], type[100];
    float price;
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Cadastrar Serviço  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            Descrição: ");
        scanf("%[^\n]%*c", description);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(description);
        if (is_valid){
            printf("|||            Descrição digitada: %s\n", description);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Descrição digitada inválida.                                 |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);

    do
    {
        printf("|||            Tipo/categoria: ");
        scanf("%[^\n]%*c", type);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(type);
        if (is_valid){
            printf("|||            Tipo/categoria digitado: %s\n", type);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Tipo/categoria digitada inválida.                            |||\n");
            printf("|||            Digite apenas letras e espaços.                              |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);

    do
    {
        printf("|||            Preço: ");
        scanf("%f", &price);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_price(price);
        if (is_valid){
            printf("|||            Preço digitado: %.2f\n", price);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Preço digitado inválido. Verifique se é maior que 0.         |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    // 
    // saveData();
    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_service() {
    char caractere; 
    char search[100];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Pesquisar Serviço  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            Informe a descrição do serviço: ");
        scanf("%[^\n]%*c", search);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Descrição digitada: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Descrição digitada inválida.                                 |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("buscado: %s", search);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_service() {
    char caractere; 
    char search[100];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Alterar Serviço  = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            Informe a descrição do serviço: ");
        scanf("%[^\n]%*c", search);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Descrição digitada: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Descrição digitada inválida.                                 |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("    buscado: %s\n", search);
    printf("    = = Serviço 1 = = \n");
    printf("    Descrição: Dipirona 500g \n");
    printf("    Tipo: Medicamento \n");
    printf("    Preço: R$ 27,00 \n");
    printf("    Data de validade: 29/11/2023 \n");
    printf("|||                                                                         |||\n");
    printf("    >> Insira o nº do Serviço: \n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Escolha a informação que deseja alterar:                     |||\n");
    printf("|||            1- Descrição: Dipirona 500g                                  |||\n");
    printf("|||            2- Tipo: Medicamento                                         |||\n");
    printf("|||            3- Preço: R$ 27,00                                           |||\n");
    printf("|||            4- Data de nascimento: 01/02/2022                            |||\n");
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Serviço alterado! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_service() {
    char caractere; 
    char search[100];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = Excluir Serviço = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            Informe a descrição do serviço: ");
        scanf("%[^\n]%*c", search);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Descrição digitada: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Descrição digitada inválida.                                 |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("    buscado: %s\n", search);
    printf("    = = Serviço 1 = = \n");
    printf("    Descrição: Dipirona 500g \n");
    printf("    Tipo: Medicamento \n");
    printf("    Preço: R$ 27,00 \n");
    printf("    Data de validade: 29/11/2023 \n");
    printf("|||                                                                         |||\n");
    printf("    >> Insira o nº do Serviço: \n");
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Serviço deletado! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}