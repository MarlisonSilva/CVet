#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "worker.h"
#include "aux_functions.h"


// Funcionários
/////////////////////////////////////////////////////////////////////////
char worker_menu() {
    int op = -1;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Menu Funcionário = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            1. Cadastrar um novo funcionário                             |||\n");
    printf("|||            2. Pesquisar os dados de um funcionário                      |||\n");
    printf("|||            3. Atualizar o cadastro de um funcionário                    |||\n");
    printf("|||            4. Excluir um funcionário do sistema                         |||\n");
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


void create_worker() {
    char caractere; 
    char cpf[11], name[100], email[255], phone[13];
    int day, month, year;
    
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = =  Cadastrar Funcionário  = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            CPF (apenas números): ");
    scanf("%s", cpf);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||            Nome completo: ");
    scanf("%[^\n]%*c", name);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||            E-mail: ");
    scanf("%s", email);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||            Data de Nascimento (dd/mm/aaaa): ");
    scanf("%d%*c%d%*c%d", &day, &month, &year);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||            Celular (apenas números): ");
    scanf("%s", phone);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    // saveData();
    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_worker() {
    char caractere; 
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = =  Pesquisar Funcionário  = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe o CPF (apenas números): ");
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


void edit_worker() {
    char caractere; 
    char cpf_worker[11];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = =  Alterar Funcionário  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe o CPF (apenas números): ");
    scanf("%s", cpf_worker);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Escolha a informação que deseja alterar:                     |||\n");
    printf("|||            1- Nome: Pessoa da Silva                                     |||\n");
    printf("|||            2- E-mail: pessoa@gmail.com                                  |||\n");
    printf("|||            3- Data de nascimento: 26/08/2023                            |||\n");
    printf("|||            4- Nº de telefone: 84999999999                               |||\n");
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("CPF do funcionário alterado: %s", cpf_worker);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_worker() {
    char caractere; 
    char cpf_worker[11];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = Excluir Funcionário = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Informe o CPF (apenas números): ");
    scanf("%s", cpf_worker);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("CPF do funcionário alterado: %s", cpf_worker);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}