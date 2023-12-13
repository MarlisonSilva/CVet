#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "../utils.h"
#include "ctrl_client.h"
#include "ctrl_sale.h"
#include "ctrl_product.h"

#define true 1
#define false 0

int has_client(char cpf[]) {
    FILE* p_file;
    Client* cl;

    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "r+b");
    if (p_file == NULL) {
        return false;
    }

    while(fread(cl, sizeof(Client), 1, p_file)) {
        if ((strcmp(cl->cpf, cpf) == 0)) {
            fclose(p_file);
            free(cl);
            return true;
        }
    }

    fclose(p_file);
    free(cl);
    return false;
}

// salva o cliente em um arquivo
int save_client(Client* cl) {
    FILE *p_file; // cria variável ponteiro para o arquivo

    //abrindo o arquivo com tipo de abertura w
    p_file = fopen("db_clients.dat", "ab");

    //testando se o arquivo foi realmente criado
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }

    if (has_client(cl->cpf)) {
        fclose(p_file);
        printf("Erro! Cliente já cadastrado! \n");
        return 1;
    }

    cl->next = NULL;
    fwrite(cl, sizeof(Client), 1, p_file);
    fclose(p_file);
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Dados gravados:                                              |||\n");
    printf("|||            >> CADASTRADO FINALIZADO COM SUCESSO!                        |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    return 0;
}

// Trata os dados para salvar no cliente
void insert_client(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born) {
    Client* new_client = (Client*)malloc(sizeof(Client));

    strcpy(new_client->cpf, cpf);
    strcpy(new_client->name, name);
    strcpy(new_client->email, email);
    strcpy(new_client->phone, phone);
    new_client->day_born = day_born;
    new_client->month_born = month_born;
    new_client->year_born = year_born;
    new_client->activated = 1;
    save_client(new_client);
    free(new_client);
}

// Função para imprimir um cliente
void print_client(Client* cl) {
    
    if ((cl == NULL)) {
        printf("||| = = = = = = = = = = = = = CLIENTE INEXISTENTE = = = = = = = = = = = = = |||\n");
    } else {
        printf("||| = = = = = = = = = = = = = = = = CLIENTE = = = = = = = = = = = = = = = = |||\n");
        printf("|||                                                                         |||\n");
        printf("|||            CPF: %s\n", cl->cpf);
        printf("|||            Nome: %s\n", cl->name);
        printf("|||            E-mail: %s\n", cl->email);
        printf("|||            Telefone: %s\n", cl->phone);
        printf("|||            Data de nascimento: %02d/%02d/%d\n", cl->day_born, cl->month_born, cl->year_born);

        if (cl->activated) {
            printf("|||            Situação do cliente: Ativo \n");
        } else {
            printf("|||            Situação do cliente: Inativo \n");
        }
        printf("|||                                                                         |||\n");
        printf("||| = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = |||\n");
        
    }
}

// Função para listar todos os clientes
void list_clients(void) {
    FILE* p_file;
    Client* cl;
    int found = 0;
    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- VERIFIQUE SE HÁ CLIENTES CADASTRADOS! ---------        |||\n");
        return;
    }

    while(fread(cl, sizeof(Client), 1, p_file)) {
        if (cl->activated) {
            printf("|||        %s | %-30.30s | %02d/%02d/%04d        |||", cl->cpf, cl->name, cl->day_born, cl->month_born, cl->year_born);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("|||        --------------- NENHUM CLIENTE CADASTRADO ---------------        |||\n");
    }
    
    free(cl);
    fclose(p_file);
}


void find_client(char cpf[]) {
    FILE* p_file;
    Client* cl;
    int found = 0;
    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- Verifique se há clientes cadastrados! ---------        |||\n");
        return;
    }

    while(fread(cl, sizeof(Client), 1, p_file)) {
        if ((strcmp(cl->cpf, cpf) == 0) && (cl->activated)) {
            print_client(cl);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("|||        --------------- NENHUM CLIENTE CADASTRADO ---------------        |||\n");
    }
    
    fclose(p_file);
    free(cl);
}

void update_client(char cpf[]) {
    FILE* p_file;
    Client* cl;
    int found = 0;
    int is_valid = 0;
    char caractere;
    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "r+b");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------------- Não é possível continuar! ---------------        |||\n");
        return;
    }
    
    while(fread(cl, sizeof(Client), 1, p_file)) {
        if ((strcmp(cl->cpf, cpf) == 0) && (cl->activated)) {
            found = 1;
            int updating = 1;
            do
            {
                int op;
                printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                printf("|||                                                                         |||\n");
                printf("|||            Qual informação deseja editar?                               |||\n");
                printf("|||            [1] Nome: %s\n", cl->name);
                printf("|||            [2] E-mail: %s\n", cl->email);
                printf("|||            [3] Telefone: %s\n", cl->phone);
                printf("|||            [4] Data de nascimento: %02d/%02d/%d\n", cl->day_born, cl->month_born, cl->year_born);
                printf("|||            [0] Finalizar edição                                         |||\n");
                printf("|||                                                                         |||\n");
                printf("|||            >> Opção: ");
                scanf("%d", &op);
                getchar();

                switch (op) {
                    case 1:
                        do
                        {
                            printf("|||            Novo nome: ");
                            scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", cl->name);

                            while ((caractere = getchar()) != '\n' && caractere != EOF);  
                            is_valid = validate_name(cl->name);
                            if (is_valid){
                                printf("|||            Nome digitado: %s\n", cl->name);
                                printf("|||                                                                         |||\n");
                            } else {
                                printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
                                printf("|||                                                                         |||\n");
                            }
                        } while (!is_valid);
                        break;

                    case 2:
                        do
                        {
                            printf("|||            E-mail: ");
                            scanf("%[-._@A-Za-z0-9]", cl->email);
                            while ((caractere = getchar()) != '\n' && caractere != EOF);
                            is_valid = validate_email(cl->email);
                            if (is_valid){
                                printf("|||            E-mail digitado: %s\n", cl->email);
                                printf("|||                                                                         |||\n");
                            } else {
                                printf("|||            E-mail digitado inválido.                                    |||\n");
                                printf("|||                                                                         |||\n");
                            }
                        } while (!is_valid);
                        break;

                    case 3:
                        do
                        {
                            printf("|||            Celular (apenas números | ex.: 84999776655): ");
                            scanf("%[0-9]", cl->phone);
                            while ((caractere = getchar()) != '\n' && caractere != EOF);
                            is_valid = validate_phone(cl->phone);
                            if (is_valid){
                                printf("|||            Telefone digitado: ");
                                int i = 0;
                                do
                                {
                                    if (isalnum(cl->phone[i])) {
                                        printf("%c",cl->phone[i]);
                                        if (i==1)
                                        {
                                            printf(" ");
                                        } else if (i==6)
                                        {
                                            printf("-");
                                        }   
                                    }
                                    i++;
                                } while (cl->phone[i] != '\0');
                                printf("                             |||\n");
                                printf("|||                                                                         |||\n");
                            } else {
                                printf("|||            Telefone digitado inválido. Lembre do DDD do estado e o 9.   |||\n");
                                printf("|||                                                                         |||\n");
                            }
                        } while (!is_valid);
                        break;

                    case 4:
                        do
                        {
                            printf("|||            Data de Nascimento (dd/mm/aaaa): ");
                            scanf("%d%*c%d%*c%d", &cl->day_born, &cl->month_born, &cl->year_born);
                            while ((caractere = getchar()) != '\n' && caractere != EOF);
                            is_valid = validate_date(cl->day_born, cl->month_born, cl->year_born);
                            if (is_valid){
                                printf("|||            Data digitada: %02d/%02d/%04d                                    |||\n", cl->day_born, cl->month_born, cl->year_born);
                                printf("|||                                                                         |||\n");
                            } else {
                                printf("|||            Data digitada inválida.                                      |||\n");
                                printf("|||                                                                         |||\n");
                            }
                        } while (!is_valid);
                        break;

                    case 0:
                        printf("|||            >> Edição finalizada!                                        |||\n");
                        printf("|||                                                                         |||\n");
                        updating = 0;
                        break;
                    default:
                        printf("|||            >> Opção inexistente!                                        |||\n");
                        printf("|||                                                                         |||\n");
                        break;
                }
                
                fseek(p_file, -1*sizeof(Client), SEEK_CUR);
                fwrite(cl, sizeof(Client), 1, p_file);
            } while (updating);
            
            
        }
    }

    if (!found) {        
        printf("|||            >> Cliente não encontrado!                                   |||\n");
        
    }
    fclose(p_file);
    free(cl);
}

void remove_client(char cpf[]) {
    FILE* p_file;
    Client* cl;
    int found = 0;

    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "r+b");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------------- Não é possível continuar! ---------------        |||\n");
        return;
    }
    

    while(fread(cl, sizeof(Client), 1, p_file)) {
        if ((strcmp(cl->cpf, cpf) == 0) && (cl->activated)) {
            found = 1;
            cl->activated = 0;
            fseek(p_file, -1*sizeof(Client), SEEK_CUR);
            fwrite(cl, sizeof(Client), 1, p_file);
            printf("|||            Cliente excluído!                                          |||\n");
        }
    }

    if (!found) {
        printf("|||            Cliente não encontrado!                                    |||\n");
    }

    fclose(p_file);
    free(cl);
}


void find_clients_by(char search[], int opc) {
    FILE* p_file;
    Client* cl;
    int found = 0;
    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- Verifique se há clientes cadastrados! ---------        |||\n");
        return;
    }

    if (opc < 4)
    {
        printf("|||        --- CPF --- | ------ Nome do Cliente ------- | Data Nasc.        |||\n");
    } else {
        printf("|||        --- CPF --- | -- Cliente -- | -- Produto -- | Data Compra        |||\n");

    }
    
    while(fread(cl, sizeof(Client), 1, p_file)) {
        switch (opc) {
        case 1:
            if ((strncmp(cl->name, search, strlen(search)) == 0) && (cl->activated)) {
                printf("|||        %s | %-30.30s | %02d/%02d/%04d        |||", cl->cpf, cl->name, cl->day_born, cl->month_born, cl->year_born);
                found++;
                printf("\n");
            } 
            break;
        case 2:
            if ((strncmp(cl->email, search, strlen(search)) == 0) && (cl->activated)) {
                printf("|||        %s | %-30.30s | %02d/%02d/%04d        |||", cl->cpf, cl->name, cl->day_born, cl->month_born, cl->year_born);
                found++;
                printf("\n");
            } 
            break;
        case 3:
            if (!(cl->activated)) {
                printf("|||        %s | %-30.30s | %02d/%02d/%04d        |||", cl->cpf, cl->name, cl->day_born, cl->month_born, cl->year_born);
                found++;
                printf("\n");
            } 
            break;
        case 4:
           if (cl->activated) {
                FILE* p_file_sl;
                Sale* sl;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                sl = (Sale*) malloc(sizeof(Sale));
                p_file_sl = fopen("db_sales.dat", "rb");
                if (p_file_sl == NULL) {
                    printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
                    printf("|||        ---------- Verifique se há vendas cadastrados! ----------        |||\n");
                    return;
                }
                while(fread(sl, sizeof(Sale), 1, p_file_sl)){
                    if (((sl->date.tm_year + 1900) == (tm.tm_year + 1900)) && (sl->date.tm_mon == tm.tm_mon))
                    {
                        printf("|||        %s | %-13.13s | %-13.13s | %02d/%02d-%02d:%02d        |||", cl->cpf, cl->name, get_product(sl->product_id)->description, sl->date.tm_mday, (sl->date.tm_mon + 1), sl->date.tm_hour, sl->date.tm_min);
                        found++;
                        printf("\n");
                    }
                    
                }
                fclose(p_file_sl);
                free(sl);
                
            }

        default:
            break;
        }
        
    }
    if (found == 0)
    {
        printf("|||                        NENHUM CLIENTE ENCONTRADO                        |||\n");

    }
    
    fclose(p_file);
    free(cl);
}

void list_clients_az(void) {
    FILE* p_file;
    Client* cl;
    Client* clients = NULL;
    Client* aux_cl;
    int found = 0;
    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- VERIFIQUE SE HÁ CLIENTES CADASTRADOS! ---------        |||\n");
        return;
    }

    while(fread(cl, sizeof(Client), 1, p_file)) {
        if (cl->activated) {
            if ((clients == NULL) || (strcmp(cl->name, clients->name) < 0)) {
                // substitui o topo da lista
                cl->next = clients;
                clients = cl;
            } else {
                Client* prev = clients;
                Client* curr = clients->next;
                while ((curr != NULL) && (strcmp(curr->name, cl->name) < 0)) {
                    prev = curr;
                    curr = curr->next;
                }
                prev->next = cl;
                cl->next = curr;
            }
            cl = (Client *) malloc(sizeof(Client));
            found++;
        }
    }

    free(cl);
    fclose(p_file);
    aux_cl = clients;
    do {
        printf("|||        %s | %-30.30s | %02d/%02d/%04d        |||", aux_cl->cpf, aux_cl->name, aux_cl->day_born, aux_cl->month_born, aux_cl->year_born);
        printf("\n");
        aux_cl = aux_cl->next;
    } while (aux_cl != NULL);
    
    if (found == 0) {
        printf("|||        --------------- NENHUM CLIENTE CADASTRADO ---------------        |||\n");
    }
    clear_client(clients);
}

void clear_client(Client* cl){
    Client* aux_cl;
  
    while (cl != NULL) {
        aux_cl = cl;
        cl = cl->next;
        free(aux_cl);
    }  
}

Client* get_client(char client_cpf[]) {
    FILE* p_file;
    Client* cl;
    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- Verifique se há clientes cadastrados! ---------        |||\n");
        return NULL;
    }
    while(fread(cl, sizeof(Client), 1, p_file) && (cl->cpf != client_cpf));
    fclose(p_file);
    return cl; 
}