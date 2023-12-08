#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "database/ctrl_worker.h"

#include "aux_functions.h"
#include "utils.h"


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
    printf("|||            2. Listar todos os funcionários                              |||\n");
    printf("|||            3. Pesquisar os dados de um funcionário                      |||\n");
    printf("|||            4. Atualizar o cadastro de um funcionário                    |||\n");
    printf("|||            5. Excluir um funcionário do sistema                         |||\n");
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


void create_worker() {
    char caractere; 
    char cpf[12] = "", name[100] = "", email[255] = "", phone[13] = "";
    int day = 0, month = 0, year = 0;
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = =  Cadastrar Funcionário  = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    do
    {
        printf("|||            CPF (apenas números): ");
        scanf("%[0-9]", cpf);
        while ((caractere = getchar()) != '\n' && caractere != EOF);  
        is_valid = validate_cpf(cpf);
        if (is_valid && !has_worker(cpf)){
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
        } else if(has_worker(cpf)){
            printf("|||            CPF já registrado. Tente outro!                              |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!(is_valid) || (has_worker(cpf)));
    
    do
    {
        printf("|||            Nome completo: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", name);
        // fgets(name, 100, stdin);
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
            int i = 0;
            do
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
                i++;
            } while (phone[i] != '\0');
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
    insert_worker(cpf, name, email, phone, day, month, year);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}

void all_workers() {
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = =  Lista de Funcionários  = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||        --- CPF --- | ---- Nome do Funcionário ----- | Data Nasc.        |||\n");
    list_workers();
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void search_worker() {
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = =  Pesquisar Funcionário  = = = = = =              |||\n");
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
    find_worker(cpf);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_worker() {
    char caractere; 
    char cpf[12];
    int is_valid = 0;
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = =  Alterar Funcionário  = = = = = = =              |||\n");
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
    update_worker(cpf);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_worker() {
    char caractere; 
    int is_valid = 0;
    char cpf[12];
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = = = = = Excluir Funcionário = = = = = = =              |||\n");
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
    remove_worker(cpf);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void filtered_workers() {
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
    printf("|||            = = = = = =  Pesquisar Funcionário  = = = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    
    while (!exit && !is_valid) {
        printf("|||            Escolha um filtro para a listagem:                           |||\n");
        printf("|||            1- Nome do funcionário                                       |||\n");
        printf("|||            2- E-mail do Funcionário                                     |||\n");
        printf("|||            3- Funcionário desativados                                   |||\n");
        printf("|||            4- Funcionários e número de vendas este mês                  |||\n");
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
    find_workers_by(search, op);
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void all_workers_az() {
    system("clear||cls");
    printf("\n");
    header();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||            = = = =  Lista de Funcionários por Nome = = = =              |||\n");
    printf("|||            = = = = = = = = = = = = = = = = = = = = = = = =              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||        --- CPF --- | ---- Nome do Funcionário ----- | Data Nasc.        |||\n");
    list_workers();
    printf("|||                                                                         |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}