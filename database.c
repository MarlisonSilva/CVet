#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define true 1
#define false 0

typedef struct client Client;

struct client {
    char cpf[11];
    char name[100];
    char email[255];
    char phone[13];
    int day_born;
    int month_born;
    int year_born;
    int activated;
};

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

    fwrite(cl, sizeof(Client), 1, p_file);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");

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
    
    if ((cl == NULL) || !(cl->activated)) {
        printf("\n= = = CLIENTE INEXISTENTE = = =\n");
    } else {
        printf("Cliente: \n");
        printf("CPF: %s\n", cl->cpf);
        printf("Nome: %s\n", cl->name);
        printf("E-mail: %s\n", cl->email);
        printf("Telefone: %s\n", cl->phone);
        printf("Data de nascimento: %02d/%02d/%d\n", cl->day_born, cl->month_born, cl->year_born);

        if (cl->activated) {
            printf("Situação do cliente: Ativo \n");
        } else {
            printf("Situação do cliente: Inativo \n");
        }
        
    }
}

// Função para listar todos os clientes
void list_clients(void) {
    FILE* p_file;
    Client* cl;
    cl = (Client*) malloc(sizeof(Client));
    p_file = fopen("db_clients.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }

    while(fread(cl, sizeof(Client), 1, p_file)) {
        if (cl->activated) {
            print_client(cl);
            printf("\n");
        }
    }
    free(cl);
    fclose(p_file);
}

// Função para imprimir os elementos da lista
// void print_clients(Client* list) {
//     Client* current = list;
//     while (current != NULL) {
//         printf("Cliente: \n");
//         printf("CPF: %s\n", current->cpf);
//         printf("Nome: %s\n", current->name);
//         printf("E-mail: %s\n", current->email);
//         printf("Telefone: %s\n", current->phone);
//         printf("Data de nascimento: %02d/%02d/%d\n", current->day_born, current->month_born, current->year_born);
//         current = current->next;
//     }
//     printf("\n");
// }

// Conversão da lista de struct para String
// char* client_to_string(Client* list) {
//     char* result = (char*)malloc(1);  // Inicializa a string vazia
//     result[0] = '\0';  // Garante que a string está terminada corretamente

//     Client* current = list;
//     while (current != NULL) {
//         char temp[100];
//         sprintf(temp, "%s, %s, %s, %s, %d, %d, %d \n", current->cpf, current->name, current->email, current->phone, current->day_born, current->month_born, current->year_born);
//         result = (char*)realloc(result, strlen(result) + strlen(temp) + 1);
//         strcat(result, temp);
//         current = current->next;
//     }

//     return result;
// }

typedef struct animal Animal;

struct animal {
    char cpf[11];
    char name[100];
    char species[100];
    char race[100];
    float weight;
    int day_born;
    int month_born;
    int year_born;
    int activated;
};

typedef struct product Product;

struct product {
    char description[100];
    char type[100];
    float price;
    int day_expiration;
    int month_expiration;
    int year_expiration;
    int activated;
};

typedef struct service Service;

struct service {
    char description[100];
    char type[100];
    float price;
    int activated;
};

typedef struct sale Sale;

struct sale {
    int item_id;
    int worker_id;
    int client_id;
    int activated;
};

typedef struct worker Worker;

struct worker {
    char cpf[11];
    char name[100];
    char email[255];
    char phone[13];
    int day_born;
    int month_born;
    int year_born;
    int activated;
};
