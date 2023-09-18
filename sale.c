#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sale.h"
#include "aux_functions.h"

char caractere;

// Vendas
///////////////////////////////////////////////////////////////////////////////
char sale_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = =  Menu Venda = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar um novo venda                                   ///\n");
    printf("///            2. Pesquisar os dados de um venda                            ///\n");
    printf("///            3. Excluir um venda do sistema                               ///\n");
    printf("///            0. Voltar ao menu anterior                                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a opção desejada: ");
    scanf(" %c", &op);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); getchar();
    return op;
}


void create_sale() {
    char cpf[11], product[255], animal[100];
    int day, month, year;
    
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = Cadastrar Venda = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF do cliente (apenas números): ");
    scanf("%s", cpf);
    while ((caractere = getchar()) != '\n' && caractere != EOF);    
    printf("///            Produto: ");
    scanf("%s", product);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Animal (Opcional): ");
    scanf("%s", animal);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");

    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_sale() {
    
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = Pesquisar Venda = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF do cliente ou funcionário: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("buscado: %s", search);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_sale() {    
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = =  Excluir Venda  = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF do cliente ou funcionário (apenas números): ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("    buscado: %s", search);
    printf("    = = Venda 1 = = \n");
    printf("    Cliente: Marlison \n");
    printf("    Funcionário: Juan Vitório \n");
    printf("    Produto: Dipirona 500g - Medicamento \n");
    printf("    Valor: R$ 27,00 \n");
    printf("    Data da venda: 29/11/2023 \n");
    printf("///                                                                         ///\n");
    printf("    >> Insira o nº da venda: \n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("Venda desfeita! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}