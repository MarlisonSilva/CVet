#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "appointment.h"
#include "utils.h"
#include "aux_functions.h"


// Consultas
/////////////////////////////////////////////////////////////////////////
char appointment_menu() {
    int op = -1;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Menu Consulta  = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            1. Cadastrar uma nova consulta                               |||\n");
    printf("|||            2. Pesquisar os dados de uma consulta                        |||\n");
    printf("|||            3. Excluir uma consulta do sistema                           |||\n");
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


void create_appointment() {
    char caractere; 
    char cpf[12], service[255], animal[100];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Cadastrar Consulta = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
    printf("|||            CPF do funcionário (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid){
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
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    
    do
    {
        printf("|||            Serviço: ");
        scanf("%[^\n]%*c", service);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(service);
        if (is_valid){
            printf("|||            Serviço digitado: %s\n", service);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Serviço digitado inválido.                                   |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);

    do
    {
        printf("|||            Animal: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", animal);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(animal);
        if (is_valid){
            printf("|||            Animal digitado: %s\n", animal);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Animal digitado inválido. Digite apenas letras e espaços.    |||\n");
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


void search_appointment() {
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Pesquisar Consulta = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
    printf("|||            CPF do cliente ou funcionário (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid){
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
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("buscado: %s", cpf);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_appointment() {    
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Excluir Consulta = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
    printf("|||            CPF do cliente ou funcionário (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid){
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
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("    buscado: %s", cpf);
    printf("    = = Consulta 1 = = \n");
    printf("    Cliente: Marlison \n");
    printf("    Funcionário: Juan Vitório \n");
    printf("    Produto: Dipirona 500g - Medicamento \n");
    printf("    Valor: R$ 27,00 \n");
    printf("    Data da venda: 29/11/2023 \n");
    printf("|||                                                                         |||\n");
    printf("    >> Insira o nº da venda: \n");
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Consulta desfeita! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}