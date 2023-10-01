#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "aux_functions.h"

char caractere;

// Produtos
/////////////////////////////////////////////////////////////////////////
char product_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Menu Produto = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            1. Cadastrar um novo produto                                 |||\n");
    printf("|||            2. Pesquisar os dados de um produto                          |||\n");
    printf("|||            3. Atualizar o cadastro de um produto                        |||\n");
    printf("|||            4. Excluir um produto do sistema                             |||\n");
    printf("|||            0. Voltar ao menu anterior                                   |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Escolha a opção desejada: ");
    scanf(" %c", &op);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); getchar();
    return op;
}


void create_product() {
    char description[100], type[100];
    float price;
    int day, month, year;
    
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Cadastrar Produto  = = = = = = =              |||\n");
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
    printf("|||            Validade (dd/mm/aaaa): ");
    scanf("%d%*c%d%*c%d", &day, &month, &year);
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


void search_product() {
    
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Pesquisar Produto  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe a descrição do produto: ");
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


void edit_product() {
    
    char search[100];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Alterar Produto  = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe a descrição do produto: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("    buscado: %s\n", search);
    printf("    = = Produto 1 = = \n");
    printf("    Descrição: Dipirona 500g \n");
    printf("    Tipo: Medicamento \n");
    printf("    Preço: R$ 27,00 \n");
    printf("    Data de validade: 29/11/2023 \n");
    printf("|||                                                                         |||\n");
    printf("    >> Insira o nº do Produto: \n");
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
    printf("Produto alterado! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_product() {
    
    char search[100];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = Excluir Produto = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe sobre o produto: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("    buscado: %s\n", search);
    printf("    = = Produto 1 = = \n");
    printf("    Descrição: Dipirona 500g \n");
    printf("    Tipo: Medicamento \n");
    printf("    Preço: R$ 27,00 \n");
    printf("    Data de validade: 29/11/2023 \n");
    printf("|||                                                                         |||\n");
    printf("    >> Insira o nº do Produto: \n");
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Produto deletado! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}