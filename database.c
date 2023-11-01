#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include "utils.h"

#define true 1
#define false 0

typedef struct client Client;

struct client {
    char cpf[12];
    char name[100];
    char email[255];
    char phone[12];
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
    
    if ((cl == NULL)) {
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
    int found = 0;
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
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Sem clientes! \n");
    }
    
    free(cl);
    fclose(p_file);
}


void find_client(char cpf[]) {
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
        if ((strcmp(cl->cpf, cpf) == 0) && (cl->activated)) {
            print_client(cl);
            printf("\n");
        }
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
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
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
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    

    while(fread(cl, sizeof(Client), 1, p_file)) {
        if ((strcmp(cl->cpf, cpf) == 0) && (cl->activated)) {
            found = 1;
            cl->activated = 0;
            fseek(p_file, -1*sizeof(Client), SEEK_CUR);
            fwrite(cl, sizeof(Client), 1, p_file);
            printf("\nCliente excluído!\n");
        }
    }

    if (!found) {
        printf("\nCliente não encontrado!\n");
    }

    fclose(p_file);
    free(cl);
}

typedef struct animal Animal;

struct animal {
    char cpf[12];
    char name[100];
    char species[100];
    char race[100];
    float weight;
    int day_born;
    int month_born;
    int year_born;
    int activated;
};

// salva o animal em um arquivo
int save_animal(Animal* an) {
    FILE *p_file; // cria variável ponteiro para o arquivo

    //abrindo o arquivo com tipo de abertura w
    p_file = fopen("db_animals.dat", "ab");

    //testando se o arquivo foi realmente criado
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }

    fwrite(an, sizeof(Animal), 1, p_file);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");

    return 0;
}

// Trata os dados para salvar no animal
void insert_animal(char cpf[], char name[], char species[], char race[], float weight, int day_born, int month_born, int year_born) {
    Animal* new_animal = (Animal*)malloc(sizeof(Animal));

    strcpy(new_animal->cpf, cpf);
    strcpy(new_animal->name, name);
    strcpy(new_animal->species, species);
    strcpy(new_animal->race, race);
    new_animal->weight = weight;
    new_animal->day_born = day_born;
    new_animal->month_born = month_born;
    new_animal->year_born = year_born;
    new_animal->activated = 1;

    save_animal(new_animal);
    free(new_animal);
}

// Função para imprimir um animal
void print_animal(Animal* an) {
    
    if ((an == NULL)) {
        printf("\n= = = ANIMAL INEXISTENTE = = =\n");
    } else {
        printf("Animal: \n");
        printf("CPF do tutor: %s\n", an->cpf);
        printf("Nome: %s\n", an->name);
        printf("Espécie: %s\n", an->species);
        printf("Raça: %s\n", an->race);
        printf("Peso: %f\n", an->weight);
        printf("Data de nascimento: %02d/%02d/%d\n", an->day_born, an->month_born, an->year_born);

        if (an->activated) {
            printf("Situação do animal: Ativo \n");
        } else {
            printf("Situação do animal: Inativo \n");
        }
        
    }
}

// Função para listar todos os animais
void list_animals(void) {
    FILE* p_file;
    Animal* an;
    int found = 0;
    an = (Animal*) malloc(sizeof(Animal));
    p_file = fopen("db_animals.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }

    while(fread(an, sizeof(Animal), 1, p_file)) {
        if (an->activated) {
            print_animal(an);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Sem animais cadastrados! \n");
    }
    
    free(an);
    fclose(p_file);
}


void find_animal(char cpf[], char search[]) {
    FILE* p_file;
    Animal* an;
    int found = 0;
    an = (Animal*) malloc(sizeof(Animal));
    p_file = fopen("db_animals.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }

    while(fread(an, sizeof(Animal), 1, p_file)) {
        if ((strcmp(an->cpf, cpf) == 0) && (an->activated)) {
            if (strncmp(str_to_lower(an->name), str_to_lower(search), strlen(search)) == 0) {
                found = 1;
                print_animal(an);
                printf("\n");    
            }
        }
    }
    if (!found) {        
        printf("|||                                                                         |||\n");
        printf("|||            >> Animal não encontrado!                                    |||\n");
        
    }
    fclose(p_file);
    free(an);
}

void update_animal(char cpf[], char search[]) {
    FILE* p_file;
    Animal* an;
    int found = 0;
    int is_valid = 0;
    char caractere;
    an = (Animal*) malloc(sizeof(Animal));
    p_file = fopen("db_animals.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    while(fread(an, sizeof(Animal), 1, p_file)) {
        if ((strcmp(an->cpf, cpf) == 0) && (an->activated)) {
            if (strncmp(str_to_lower(an->name), str_to_lower(search), strlen(search)) == 0) {
                found++;
                printf(">> ID [%d] \n", found);
                print_animal(an);
                printf("\n");
            }
        }
    }
    fclose(p_file);
    p_file = fopen("db_animals.dat", "r+b");
    if (found) {  
        printf("Qual animal gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) {
            getchar();
            found = 0;
            while(fread(an, sizeof(Animal), 1, p_file)) {
                if ((strcmp(an->cpf, cpf) == 0) && (an->activated)) {
                    found++;
                    if (found == id)
                    {
                        int updating = 1;
                        do
                        {
                            int op;
                            printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                            printf("|||                                                                         |||\n");
                            printf("|||            Qual informação deseja editar?                               |||\n");
                            printf("|||            [1] Nome: %s\n", an->name);
                            printf("|||            [2] Espécie: %s\n", an->species);
                            printf("|||            [3] Raça: %s\n", an->race);
                            printf("|||            [4] Peso: %f\n", an->weight);
                            printf("|||            [5] Data de nascimento: %02d/%02d/%d\n", an->day_born, an->month_born, an->year_born);
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
                                        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", an->name);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);  
                                        is_valid = validate_name(an->name);
                                        if (is_valid){
                                            printf("|||            Nome digitado: %s\n", an->name);
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
                                        printf("|||            Espécie: ");
                                        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", an->species);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(an->species);
                                        if (is_valid){
                                            printf("|||            Espécie digitada: %s\n", an->species);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Espécie digitada inválida. Digite apenas letras e espaços.   |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 3:
                                    do
                                    {
                                        printf("|||            Raça: ");
                                        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", an->race);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(an->race);
                                        if (is_valid){
                                            printf("|||            Raça digitada: %s\n", an->race);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Raça digitada inválida. Digite apenas letras e espaços.      |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 4:
                                    do
                                    {
                                        printf("|||            Peso: ");
                                        scanf("%f", &(an->weight));

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_weight(an->weight);
                                        if (is_valid){
                                            printf("|||            Peso digitado: %.3f\n", an->weight);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Peso digitado inválido. Verifique se é maior que 0.          |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 5:
                                    do
                                    {
                                        printf("|||            Data de Nascimento (dd/mm/aaaa): ");
                                        scanf("%d%*c%d%*c%d", &an->day_born, &an->month_born, &an->year_born);
                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_date(an->day_born, an->month_born, an->year_born);
                                        if (is_valid){
                                            printf("|||            Data digitada: %02d/%02d/%04d                                    |||\n", an->day_born, an->month_born, an->year_born);
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
                            
                            fseek(p_file, -1*sizeof(Animal), SEEK_CUR);
                            fwrite(an, sizeof(Animal), 1, p_file);
                        } while (updating);   
                    }
                }
            }
        } else {
            printf("|||                                                                         |||\n");
            printf("|||            >> Opção não encontrada!                                     |||\n");

        }
        
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Animal não encontrado!                                    |||\n");
    }

    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    fclose(p_file);
    free(an);
}

void remove_animal(char cpf[]) {
    FILE* p_file;
    Animal* an;
    int found = 0;

    an = (Animal*) malloc(sizeof(Animal));
    p_file = fopen("db_animals.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    

    while(fread(an, sizeof(Animal), 1, p_file)) {
        if ((strcmp(an->cpf, cpf) == 0) && (an->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_animal(an);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_animals.dat", "r+b");
    if (found) {  
        printf("Qual animal gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) 
        {
            getchar();
            found = 0;
            while(fread(an, sizeof(Animal), 1, p_file)) {
                if ((strcmp(an->cpf, cpf) == 0) && (an->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            an->activated = 0;
                            fseek(p_file, -1*sizeof(Animal), SEEK_CUR);
                            fwrite(an, sizeof(Animal), 1, p_file);
                            printf("\nAnimal excluído!\n");
                        } else {
                            printf("\nOperação cancelada!\n");

                        }
                    }
                }
            }
        }
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Animal não encontrado!                                    |||\n");
    }

    fclose(p_file);
    free(an);
}

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
    char cpf[12];
    char name[100];
    char email[255];
    char phone[13];
    int day_born;
    int month_born;
    int year_born;
    int activated;
};


// salva o funcionário em um arquivo
int save_worker(Worker* wk) {
    FILE *p_file; // cria variável ponteiro para o arquivo

    //abrindo o arquivo com tipo de abertura w
    p_file = fopen("db_workers.dat", "ab");

    //testando se o arquivo foi realmente criado
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }

    fwrite(wk, sizeof(Worker), 1, p_file);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");

    return 0;
}

// Trata os dados para salvar no funcionário
void insert_worker(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born) {
    Worker* new_worker = (Worker*)malloc(sizeof(Worker));

    strcpy(new_worker->cpf, cpf);
    strcpy(new_worker->name, name);
    strcpy(new_worker->email, email);
    strcpy(new_worker->phone, phone);
    new_worker->day_born = day_born;
    new_worker->month_born = month_born;
    new_worker->year_born = year_born;
    new_worker->activated = 1;

    save_worker(new_worker);
    free(new_worker);
}

// Função para imprimir um funcionário
void print_worker(Worker* wk) {
    
    if ((wk == NULL)) {
        printf("\n= = = FUNCIONÁRIO INEXISTENTE = = =\n");
    } else {
        printf("Funcionário: \n");
        printf("CPF: %s\n", wk->cpf);
        printf("Nome: %s\n", wk->name);
        printf("E-mail: %s\n", wk->email);
        printf("Telefone: %s\n", wk->phone);
        printf("Data de nascimento: %02d/%02d/%d\n", wk->day_born, wk->month_born, wk->year_born);

        if (wk->activated) {
            printf("Situação do funcionário: Ativo \n");
        } else {
            printf("Situação do funcionário: Inativo \n");
        }
        
    }
}

// Função para listar todos os funcionários
void list_workers(void) {
    FILE* p_file;
    Worker* wk;
    int found = 0;
    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }

    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if (wk->activated) {
            print_worker(wk);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Sem funcionários! \n");
    }
    
    free(wk);
    fclose(p_file);
}


void find_worker(char cpf[]) {
    FILE* p_file;
    Worker* wk;
    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }

    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if ((strcmp(wk->cpf, cpf) == 0) && (wk->activated)) {
            print_worker(wk);
            printf("\n");
        }
    }
    fclose(p_file);
    free(wk);
}

void update_worker(char cpf[]) {
    FILE* p_file;
    Worker* wk;
    int found = 0;
    int is_valid = 0;
    char caractere;
    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    
    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if ((strcmp(wk->cpf, cpf) == 0) && (wk->activated)) {
            found = 1;
            int updating = 1;
            do
            {
                int op;
                printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                printf("|||                                                                         |||\n");
                printf("|||            Qual informação deseja editar?                               |||\n");
                printf("|||            [1] Nome: %s\n", wk->name);
                printf("|||            [2] E-mail: %s\n", wk->email);
                printf("|||            [3] Telefone: %s\n", wk->phone);
                printf("|||            [4] Data de nascimento: %02d/%02d/%d\n", wk->day_born, wk->month_born, wk->year_born);
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
                            scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", wk->name);

                            while ((caractere = getchar()) != '\n' && caractere != EOF);  
                            is_valid = validate_name(wk->name);
                            if (is_valid){
                                printf("|||            Nome digitado: %s\n", wk->name);
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
                            scanf("%[-._@A-Za-z0-9]", wk->email);
                            while ((caractere = getchar()) != '\n' && caractere != EOF);
                            is_valid = validate_email(wk->email);
                            if (is_valid){
                                printf("|||            E-mail digitado: %s\n", wk->email);
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
                            scanf("%[0-9]", wk->phone);
                            while ((caractere = getchar()) != '\n' && caractere != EOF);
                            is_valid = validate_phone(wk->phone);
                            if (is_valid){
                                printf("|||            Telefone digitado: ");
                                int i = 0;
                                do
                                {
                                    if (isalnum(wk->phone[i])) {
                                        printf("%c",wk->phone[i]);
                                        if (i==1)
                                        {
                                            printf(" ");
                                        } else if (i==6)
                                        {
                                            printf("-");
                                        }   
                                    }
                                    i++;
                                } while (wk->phone[i] != '\0');
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
                            scanf("%d%*c%d%*c%d", &wk->day_born, &wk->month_born, &wk->year_born);
                            while ((caractere = getchar()) != '\n' && caractere != EOF);
                            is_valid = validate_date(wk->day_born, wk->month_born, wk->year_born);
                            if (is_valid){
                                printf("|||            Data digitada: %02d/%02d/%04d                                    |||\n", wk->day_born, wk->month_born, wk->year_born);
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
                
                fseek(p_file, -1*sizeof(Worker), SEEK_CUR);
                fwrite(wk, sizeof(Worker), 1, p_file);
            } while (updating);
            
            
        }
    }

    if (!found) {        
        printf("|||            >> Funcionário não encontrado!                                   |||\n");
        
    }
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    fclose(p_file);
    free(wk);
}

void remove_worker(char cpf[]) {
    FILE* p_file;
    Worker* wk;
    int found = 0;

    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    

    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if ((strcmp(wk->cpf, cpf) == 0) && (wk->activated)) {
            found = 1;
            wk->activated = 0;
            fseek(p_file, -1*sizeof(Worker), SEEK_CUR);
            fwrite(wk, sizeof(Worker), 1, p_file);
            printf("\nFuncionário excluído!\n");
        }
    }

    if (!found) {
        printf("\nFuncionário não encontrado!\n");
    }

    fclose(p_file);
    free(wk);
}