#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service.h"
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
    
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Cadastrar Serviço  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Descrição: ");
    scanf("%[^\n]%*c", description);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||            Tipo: ");
    scanf("%[^\n]%*c", type);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||            Preço: ");
    scanf("%f", &price);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
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
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Pesquisar Serviço  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe a descrição do serviço: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
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
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Alterar Serviço  = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe a descrição do serviço: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
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
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = Excluir Serviço = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe sobre o serviço: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
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