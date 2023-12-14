#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "database/ctrl_appointment.h"
#include "database/ctrl_worker.h"


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
    printf("|||            2. Listar todas as consultas                                 |||\n");
    printf("|||            3. Pesquisar os dados de uma consulta                        |||\n");
    printf("|||            4. Excluir uma consulta do sistema                           |||\n");
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


void create_appointment() {
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    int exit = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Cadastrar Consulta = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    while (!exit && !(is_valid && has_worker(cpf))) {
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
        } else {
            if (!has_worker(cpf)) {
                printf("|||            CPF digitado inválido. Funcionário INEXISTENTE!              |||\n");
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
    int animal_id = choose_animal();
    int service_id = choose_service();
    if (!exit && animal_id && service_id) {
        printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
        insert_appointment(cpf, animal_id, service_id);
    } else {
        printf("|||            DADOS INSUFICIENTE PARA CADASTRO!                            |||\n");
        printf("|||                                                                         |||\n");
        printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    }
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}

void all_appointments() {
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Lista de Consultas = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||        Funcionário | --- Animal --- | -- Serviço -- | Data Cons.        |||\n");
    list_appointments();
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void search_appointment() {
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    int exit = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = =  Pesquisar Consulta = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    while (!exit && !(is_valid && has_worker(cpf))) {
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
        } else {
            if (!has_worker(cpf)) {
                printf("|||            CPF digitado inválido. Funcionário INEXISTENTE!              |||\n");
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
    if (!exit){
        find_appointment(cpf);
    } else {
        printf("|||            BUSCA CANCELADA!                                             |||\n");
    }   
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_appointment() {    
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    int exit = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = =  Excluir Consulta = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    while (!exit && !(is_valid && has_worker(cpf))) {
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
        } else {
            if (!has_worker(cpf)){
               printf("|||            CPF digitado inválido. Funcionário INEXISTENTE!              |||\n");
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
    printf("|||                                                                         |||\n");
    if (!exit) {
        printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
        remove_appointment(cpf);
    } else {
        printf("|||            ATUALIZAÇÃO DE DADOS CANCELADA!                              |||\n");
        printf("|||                                                                         |||\n");
        printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    }
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void filtered_appointments() {
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
    printf("|||            = = = = = = =  Pesquisar Consulta = = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    
    while (!exit && !is_valid) {
        printf("|||            Escolha um filtro para a listagem:                           |||\n");
        printf("|||            1- Consultas de hoje                                         |||\n");
        printf("|||            2- Consultas deste mês                                       |||\n");
        printf("|||            3- Consultas desativadas                                     |||\n");
        printf("|||            4- Por nome do animal                                        |||\n");
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
    if (!exit){
        find_appointments_by(search, op);
    } else {
        printf("|||            BUSCA FILTRADA CANCELADA!                                    |||\n");
    }    
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void all_appointments_data() {
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = Lista de Consultas por Data = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||        Funcionário | --- Animal --- | -- Serviço -- | Data Cons.        |||\n");
    list_appointments_date();
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}