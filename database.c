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
    // Sugestão ChatGPT
    Client* next;
};

Client* list_clients = NULL; // Lista de clientes

// salva os dados cadastrados em um arquivo
int save_client(Client* client_to_save) {
    FILE *p_file; // cria variável ponteiro para o arquivo

    //abrindo o arquivo com tipo de abertura w
    p_file = fopen("db_clients.dat", "wb");

    //testando se o arquivo foi realmente criado
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }

    size_t tamanho = sizeof(struct client);
    fwrite(client_to_save, tamanho, 1, p_file);

    //usando fprintf para armazenar a string no arquivo
    // fprintf(p_file, client_to_save);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");

    return 0;
}

// Função para inserir um elemento no final da lista de clientes
void insert_client(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born) {
    Client* new_client = (Client*)malloc(sizeof(Client));

    strcpy(new_client->cpf, cpf);
    strcpy(new_client->name, name);
    strcpy(new_client->email, email);
    strcpy(new_client->phone, phone);
    new_client->day_born = day_born;
    new_client->month_born = month_born;
    new_client->year_born = year_born;
    new_client->next = NULL;

    if (list_clients == NULL) {
        list_clients = new_client;
    } else {
        Client* current = list_clients;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_client;
    }
    save_client(new_client);
    free(new_client);
}

// Função para imprimir os elementos da lista
void print_clients() {
    // Abra o arquivo binário para leitura
    FILE *p_file;
    p_file = fopen("db_clients.dat", "rb");

    if (p_file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Crie uma instância da struct para armazenar os dados lidos
    Client client_saved;

    // Leia a struct do arquivo binário
    size_t tamanho = sizeof(struct client);
    fread(&client_saved, tamanho, 1, p_file);

    // Feche o arquivo
    fclose(p_file);

    printf("Cliente: \n");
    printf("CPF: %s\n", client_saved.cpf);
    printf("Nome: %s\n", client_saved.name);
    printf("E-mail: %s\n", client_saved.email);
    printf("Telefone: %s\n", client_saved.phone);
    printf("Data de nascimento: %02d/%02d/%d\n", client_saved.day_born, client_saved.month_born, client_saved.year_born);

    
    printf("\n");
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
