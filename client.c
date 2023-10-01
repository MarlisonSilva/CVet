#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "client.h"
#include "aux_functions.h"
#include "utils.h"

char caractere;

// Cliente
/////////////////////////////////////////////////////////////////////////
char client_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Menu Cliente = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            1. Cadastrar um novo cliente                                 |||\n");
    printf("|||            2. Pesquisar os dados de um cliente                          |||\n");
    printf("|||            3. Atualizar o cadastro de um cliente                        |||\n");
    printf("|||            4. Excluir um cliente do sistema                             |||\n");
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


void create_client() {
    char cpf[11] = "", name[100] = "", email[255] = "", phone[13] = "";
    int day = 0, month = 0, year = 0;
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Cadastrar Cliente  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    
    do
    {
        printf("|||            CPF (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid){
            printf("|||            CPF digitado: ");
            for (int i = 0; cpf[i] != '\0'; i++)
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
            }
            printf("                                 |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    
    do
    {
        printf("|||            Nome completo: ");
        scanf("%[A-Z a-z]", name);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(name);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", name);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Lembre-se de digitar apenas números! |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    
    do
    {
        printf("|||            E-mail: ");
        scanf("%[-._@A-Za-z0-9]", email);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_email(email);
        if (is_valid){
            printf("|||            E-mail digitado: %s\n", email);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            E-mail digitado inválido.                                    |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);

    do
    {
        printf("|||            Data de Nascimento (dd/mm/aaaa): ");
        scanf("%d%*c%d%*c%d", &day, &month, &year);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_date(day, month, year);
        if (is_valid){
            printf("|||            Data digitada: %02d/%02d/%04d                                    |||\n", day, month, year);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Data digitada inválida.                                      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    
    do
    {
        printf("|||            Celular (apenas números | ex.: 84999776655): ");
        scanf("%[0-9]", phone);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_phone(phone);
        if (is_valid){
            printf("|||            Telefone digitado: ");
            for (int i = 0; phone[i] != '\0'; i++)
            {
                if (isalnum(phone[i])) {
                    printf("%c",phone[i]);
                    if (i==1)
                    {
                        printf(" ");
                    } else if (i==6)
                    {
                        printf("-");
                    }   
                }
            }
            printf("                             |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Telefone digitado inválido. Lembre do DDD do estado e o 9.   |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_client() {
    int is_valid = 0;
    char cpf[11];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Pesquisar Cliente  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
    printf("|||            Informe o CPF (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid){
            printf("|||            CPF digitado: ");
            for (int i = 0; cpf[i] != '\0'; i++)
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
            }
            printf("                                 |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_client() {
    
    char cpf[11];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Alterar Cliente  = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
    printf("|||            Informe o CPF (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid){
            printf("|||            CPF digitado: ");
            for (int i = 0; cpf[i] != '\0'; i++)
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
            }
            printf("                                 |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);

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
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_client() {
    int is_valid = 0;
    char cpf[11];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = Excluir Cliente = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
   do
    {
    printf("|||            Informe o CPF (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid){
            printf("|||            CPF digitado: ");
            for (int i = 0; cpf[i] != '\0'; i++)
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
            }
            printf("                                 |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}