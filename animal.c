#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "animal.h"
#include "database/ctrl_client.h"
#include "database/ctrl_animal.h"

#include "utils.h"
#include "aux_functions.h"


// Animais
/////////////////////////////////////////////////////////////////////////
char animal_menu() {
    int op = -1;
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
    printf("|||            2. Listar todos os animais                                   |||\n");
    printf("|||            3. Pesquisar os dados de um animal                           |||\n");
    printf("|||            4. Atualizar o cadastro de um animal                         |||\n");
    printf("|||            5. Excluir um animal do sistema                              |||\n");
    printf("|||            6. Listagem filtrada                                         |||\n");
    printf("|||            7. Listagem ordenada por nome                                |||\n");
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


void create_animal() {
    char caractere;
    char cpf[12], name[100], species[100],race[100];
    float weight;
    int day, month, year;
    int is_valid = 0;
    int exit = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =   Cadastrar Animal  = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    while (!exit && !(is_valid && has_client(cpf))) {
        printf("|||            CPF do tutor (apenas números): ");
        scanf("%[0-9]", cpf);

        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid && has_client(cpf)){
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
            if (!has_client(cpf)) {
                printf("|||            CPF digitado inválido. Cliente INEXISTENTE!                  |||\n");
                printf("|||                                                                         |||\n");
            } else {
                printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
                printf("|||                                                                         |||\n");
            }
            printf("|||            Tentar novamente? (s/n) ");
            char opc = 's';
            scanf(" %c", &opc);
            getchar();
            if (opc == 'n')
            {
                exit = 1;
            }
            printf("|||                                                                         |||\n");
        } 
    }

    is_valid = 0;
    while (!exit && !is_valid) {
        printf("|||            Nome do animal: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", name);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(name);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", name);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
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
        }
    }

    is_valid = 0;
    while (!exit && !is_valid) {
        printf("|||            Espécie: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", species);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(species);
        if (is_valid){
            printf("|||            Espécie digitada: %s\n", species);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Espécie digitada inválida. Digite apenas letras e espaços.   |||\n");
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
        }
    }

    is_valid = 0;
    while (!exit && !is_valid) {
        printf("|||            Raça: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", race);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(race);
        if (is_valid){
            printf("|||            Raça digitada: %s\n", race);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Raça digitada inválida. Digite apenas letras e espaços.      |||\n");
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
        }
    }

    is_valid = 0;
    while (!exit && !is_valid) {
        printf("|||            Peso: ");
        scanf("%f", &weight);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_weight(weight);
        if (is_valid){
            printf("|||            Peso digitado: %.3f\n", weight);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Peso digitado inválido. Verifique se é maior que 0.          |||\n");
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
        }
    }

    is_valid = 0;
    while (!exit && !is_valid) {
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
            printf("|||            Tentar novamente? (s/n) ");
            char opc = 's';
            scanf(" %c", &opc);
            getchar();
            if (opc == 'n')
            {
                exit = 1;
            }
            printf("|||                                                                         |||\n");
        }
    }
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    if (!exit) {
        insert_animal(cpf, name, species, race, weight, day, month, year);
    } else {
        printf("SAINDO!\n");
    }
    
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}

void all_animals() {
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Lista de Animais = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||         CPF tutor  | ---- Nome ---- | -- Espécie -- | Data Nasc.        |||\n");
    list_animals();
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void search_animal() {
    char caractere;
    char search[100];
    char cpf[12];
    int is_valid = 0;
    int exit = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Pesquisar Animal = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    while (!exit && !(is_valid && has_client(cpf))){
        printf("|||            CPF do tutor (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid && has_client(cpf)){
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
            if (!has_client(cpf)) {
                printf("|||            CPF digitado inválido. Cliente INEXISTENTE!                  |||\n");
                printf("|||                                                                         |||\n");
            } else {
                printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
                printf("|||                                                                         |||\n");
            }
            printf("|||            Tentar novamente? (s/n) ");
            char opc = 's';
            scanf(" %c", &opc);
            getchar();
            if (opc == 'n')
            {
                exit = 1;
            }
            printf("|||                                                                         |||\n");
        } 
    }

    is_valid = 0;
    while (!exit && !is_valid){
        printf("|||            Informe o nome do animal: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
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
        }
    }
    if (!exit) {
        find_animal(cpf, search);
    } else {
        printf("|||            >> Falta dados! Impossível buscar!                           |||\n");

    }
    
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_animal() {
    char caractere;
    char cpf[12];
    char search[100];
    int is_valid = 0;
    int exit = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =   Alterar Animal  = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    while (!exit && !(is_valid && has_client(cpf))){
        printf("|||            CPF do tutor (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid && has_client(cpf)){
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
            if (!has_client(cpf)) {
                printf("|||            CPF digitado inválido. Cliente INEXISTENTE!                  |||\n");
                printf("|||                                                                         |||\n");
            } else {
                printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
                printf("|||                                                                         |||\n");
            }
            printf("|||            Tentar novamente? (s/n) ");
            char opc = 's';
            scanf(" %c", &opc);
            getchar();
            if (opc == 'n')
            {
                exit = 1;
            }
            printf("|||                                                                         |||\n");
        } 
    }

    is_valid = 0;
    while (!exit && !is_valid){
        printf("|||            Informe o nome do animal: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
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
        }
    }
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");   
    if (!exit) {
        update_animal(cpf, search);
    } else {
        printf("SAINDO!\n");
    }
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_animal() {
    char caractere;
    int is_valid = 0;
    int exit = 0;
    char cpf[12];
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
    while (!exit && !(is_valid && has_client(cpf))){
        printf("|||            CPF do tutor (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid && has_client(cpf)){
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
            if (!has_client(cpf)) {
                printf("|||            CPF digitado inválido. Cliente INEXISTENTE!                  |||\n");
                printf("|||                                                                         |||\n");
            } else {
                printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
                printf("|||                                                                         |||\n");
            }
            printf("|||            Tentar novamente? (s/n) ");
            char opc = 's';
            scanf(" %c", &opc);
            getchar();
            if (opc == 'n')
            {
                exit = 1;
            }
            printf("|||                                                                         |||\n");
        } 
    }

    is_valid = 0;
    while (!exit && !is_valid){
        printf("|||            Informe o nome do animal: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);
        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
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
        }
    }
    if (!exit) {
        remove_animal(cpf, search);
    } else {
        printf("|||            >> Falta dados! Impossível remover!                           |||\n");
    }
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
} 

void filtered_animals() {
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
    printf("|||            = = = = = = =  Pesquisar Animal = = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    
    while (!exit && !is_valid) {
        printf("|||            Escolha um filtro para a listagem:                           |||\n");
        printf("|||            1- Por espécie do animal                                     |||\n");
        printf("|||            2- Por raça do animal                                        |||\n");
        printf("|||            3- Animais desativados                                       |||\n");
        printf("|||            4- Animais com donos desativados                             |||\n");
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
    while (!exit && !is_valid && op != 3 && op != 4) {
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
    find_animals_by(search, op);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void all_animals_az() {
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = =  Lista de Animais por Nome  = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||         CPF tutor  | ---- Nome ---- | -- Espécie -- | Data Nasc.        |||\n");
    list_az_animals();
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}