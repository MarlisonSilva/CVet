#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "animal.h"
#include "utils.h"
#include "aux_functions.h"


// Animais
/////////////////////////////////////////////////////////////////////////
char animal_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Menu Animal  = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            1. Cadastrar um novo animal                                  |||\n");
    printf("|||            2. Pesquisar os dados de um animal                           |||\n");
    printf("|||            3. Atualizar o cadastro de um animal                         |||\n");
    printf("|||            4. Excluir um animal do sistema                              |||\n");
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


void create_animal() {
    char caractere;

    char cpf[11], name[100], especie[100],race[100];
    float weight;
    int day, month, year;
    int is_valid = 0;

    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =   Cadastrar Animal  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            CPF do tutor (apenas números): ");
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
        printf("|||            Nome do animal: ");
        scanf("%[^\n]", name);
        printf("Nome é: %s \n",name);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(name);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", name);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);

    do
    {
        printf("|||            Espécie: ");
        fgets(especie, 100, stdin);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(especie);
        if (is_valid){
            printf("|||            Espécie digitada: %s\n", especie);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Espécie digitada inválida. Digite apenas letras e espaços.   |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);

    do
    {
        printf("|||            Raça: ");
        fgets(race, 100, stdin);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(race);
        if (is_valid){
            printf("|||            Raça digitada: %s\n", race);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Raça digitada inválida. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);

    do
    {
        printf("|||            Peso: ");
        scanf("%f", &weight);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_weight(weight);
        if (is_valid){
            printf("|||            Peso digitado: %f\n", weight);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Peso digitado inválido. Verifique se é maior que 0.          |||\n");
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
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    // insertClient(&listAnimals, client, name, especie, race, weight, day, month, year);
    // saveData();
    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_animal() {
    char caractere;
    char search[100];
    char cpf[14];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Pesquisar Animal  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            CPF do tutor (apenas números): ");
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
        printf("|||            Informe o nome do animal: ");
        fgets(search, 100, stdin);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
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


void edit_animal() {
    char caractere;
    char cpf[11];
    char search[100];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =   Alterar Animal  = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            CPF do tutor (apenas números): ");
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
        printf("|||            Informe o nome do animal: ");
        fgets(search, 100, stdin);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("    buscado: %s de %s \n", search, cpf);
    printf("    = = Animal 1 = = \n");
    printf("    Nome: Choco \n");
    printf("    Espécie: Cachorro \n");
    printf("    Raça: Vira-lata \n");
    printf("    Peso: 27,0 Kg \n");
    printf("    Data de nasc.: 01/02/2022 \n");
    printf("|||                                                                         |||\n");
    printf("    >> Insira o nº do Animal: \n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Escolha a informação que deseja alterar:                     |||\n");
    printf("|||            1- Nome: Choco                                               |||\n");
    printf("|||            2- Espécie: Cachorro                                         |||\n");
    printf("|||            3- Raça: Vira-lata                                           |||\n");
    printf("|||            4- Peso: 27,0 Kg                                             |||\n");
    printf("|||            5- Data de nascimento: 01/02/2022                            |||\n");
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Animal alterado! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_animal() {
    char caractere;
    int is_valid = 0;
    char cpf[11];
    char search[100];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Excluir Animal = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            CPF do tutor (apenas números): ");
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
        printf("|||            Informe o nome do animal: ");
        fgets(search, 100, stdin);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("    buscado: %s de %s \n", search, cpf);
    printf("    = = Animal 1 = = \n");
    printf("    Nome: Choco \n");
    printf("    Espécie: Cachorro \n");
    printf("    Raça: Vira-lata \n");
    printf("    Peso: 27,0 Kg \n");
    printf("    Data de nasc.: 01/02/2022 \n");
    printf("|||                                                                         |||\n");
    printf("    >> Insira o nº do Animal: \n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Animal deletado!");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
} 