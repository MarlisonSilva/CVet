#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "utils.h"

#define true 1
#define false 0

typedef struct client Client;

struct client {
    char cpf[12]; // "primária"
    char name[100];
    char email[255];
    char phone[12];
    int day_born;
    int month_born;
    int year_born;
    int activated;
};

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

    fwrite(cl, sizeof(Client), 1, p_file);
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");
    printf("CADASTRADO COM SUCESSO!!\n");
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
        printf(" = = = CLIENTE = = = \n");
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
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- VERIFIQUE SE HÁ CLIENTES CADASTRADOS! ---------        |||\n");
        return;
    }

    while(fread(cl, sizeof(Client), 1, p_file)) {
        if (cl->activated) {
            printf("|||        %s | %-30s | %02d/%02d/%04d        |||", cl->cpf, cl->name, cl->day_born, cl->month_born, cl->year_born);
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
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há clientes cadastrados!\n");
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
        printf("Nenhum cliente cadastrado! \n");
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
    int id_animal;
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
    
    int found = 0;
    Animal* aux_an = (Animal*)malloc(sizeof(Animal));
    while(fread(aux_an, sizeof(Animal), 1, p_file)) {
        found++;
    }
    free(aux_an);

    an->id_animal = found + 1;

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
        printf(" = = = ANIMAL = = = \n");
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
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------- VERIFIQUE SE HÁ ANIMAIS CADASTRADOS! ----------        |||\n");
        return;
    }

    while(fread(an, sizeof(Animal), 1, p_file)) {
        if (an->activated) {
            printf("|||        %s | %-14.14s | %-13.13s | %02d/%02d/%04d        |||", an->cpf, an->name, an->species, an->day_born, an->month_born, an->year_born);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("|||        --------------- NENHUM ANIMAL CADASTRADO ----------------        |||\n");
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
        printf("Verifique se há animais cadastrados!\n");
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
        printf("Qual animal gostaria de remover (ID)? ");
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
    int id_product;
    char description[100];
    char type[100];
    float price;
    int day_expiration;
    int month_expiration;
    int year_expiration;
    int activated;
};

// salva o produto em um arquivo
int save_product(Product* pr) {
    FILE *p_file; // cria variável ponteiro para o arquivo

    //abrindo o arquivo com tipo de abertura w

    //testando se o arquivo foi realmente criado
    p_file = fopen("db_products.dat", "ab");
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    int found = 0;
    Product* aux_pr = (Product*)malloc(sizeof(Product));
    while(fread(aux_pr, sizeof(Product), 1, p_file)) {
        found++;
    }
    free(aux_pr);

    pr->id_product = found + 1;
    fwrite(pr, sizeof(Product), 1, p_file);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");
    printf("CADASTRADO COM SUCESSO!!\n");
    return 0;
}

// Trata os dados para salvar no produto
void insert_product(char description[], char type[], float price, int day_expiration, int month_expiration, int year_expiration) {
    Product* new_product = (Product*)malloc(sizeof(Product));

    strcpy(new_product->description, description);
    strcpy(new_product->type, type);
    new_product->price = price;
    new_product->day_expiration = day_expiration;
    new_product->month_expiration = month_expiration;
    new_product->year_expiration = year_expiration;
    new_product->activated = 1;
    save_product(new_product);
    free(new_product);
}

// Função para imprimir um produto
void print_product(Product* pr) {
    
    if ((pr == NULL)) {
        printf("\n= = = PRODUTO INEXISTENTE = = =\n");
    } else {
        printf(" = = = PRODUTO = = = \n");
        printf("Descrição: %s\n", pr->description);
        printf("Tipo: %s\n", pr->type);
        printf("Preço: %.2f\n", pr->price);
        printf("Data de validade: %02d/%02d/%d\n", pr->day_expiration, pr->month_expiration, pr->year_expiration);

        if (pr->activated) {
            printf("Situação do produto: Ativo \n");
        } else {
            printf("Situação do produto: Inativo \n");
        }
        
    }
}

// Função para listar todos os produtos
void list_products(void) {
    FILE* p_file;
    Product* pr;
    int found = 0;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há produtos cadastrados!\n");
        return;
    }

    while(fread(pr, sizeof(Product), 1, p_file)) {
        if (pr->activated) {
            print_product(pr);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhum produto encontrado! \n");
    }
    
    free(pr);
    fclose(p_file);
}


void find_product(char search[]) {
    FILE* p_file;
    Product* pr;
    char aux[100] = "";
    int found = 0;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há produtos cadastrados!\n");
        return;
    }

    while(fread(pr, sizeof(Product), 1, p_file)) {
        strcpy(aux, pr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
            print_product(pr);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhum produto encontrado! \n");
    }
    fclose(p_file);
    free(pr);
}


void update_product(char search[]) {
    FILE* p_file;
    Product* pr;
    int found = 0;
    char aux[100] = "";
    int is_valid = 0;
    char caractere;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    while(fread(pr, sizeof(Product), 1, p_file)) {
        strcpy(aux, pr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_product(pr);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_products.dat", "r+b");
    if (found) {  
        printf("Qual produto gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) {
            getchar();
            found = 0;
            while(fread(pr, sizeof(Product), 1, p_file)) {
                strcpy(aux, pr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
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
                            printf("|||            [1] Descrição: %s\n", pr->description);
                            printf("|||            [2] Tipo do produto: %s\n", pr->type);
                            printf("|||            [3] Preço: %.2f\n", pr->price);
                            printf("|||            [4] Data de validade: ");
                            if ((pr->day_expiration == 0) && (pr->month_expiration) && (pr->year_expiration)) {
                                printf("INDETERMINADA\n");
                            } else {
                                printf("%02d/%02d/%d\n", pr->day_expiration, pr->month_expiration, pr->year_expiration);
                            }
                            
                            printf("|||            [0] Finalizar edição                                         |||\n");
                            printf("|||                                                                         |||\n");
                            printf("|||            >> Opção: ");
                            scanf("%d", &op);
                            getchar();

                            switch (op) {
                                case 1:
                                    do
                                    {
                                        printf("|||            Descrição: ");
                                        scanf("%[^\n]%*c", pr->description);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(pr->description);
                                        if (is_valid){
                                            printf("|||            Descrição digitada: %s\n", pr->description);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Descrição digitada inválida.                                 |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 2:
                                    do
                                    {
                                        printf("|||            Tipo/categoria: ");
                                        scanf("%[^\n]%*c", pr->type);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(pr->type);
                                        if (is_valid){
                                            printf("|||            Tipo/categoria digitado: %s\n", pr->type);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Tipo/categoria digitada inválida.                            |||\n");
                                            printf("|||            Digite apenas letras e espaços.                              |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 3:
                                    do
                                    {
                                        printf("|||            Preço: ");
                                        scanf("%f", &(pr->price));

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_price(pr->price);
                                        if (is_valid){
                                            printf("|||            Preço digitado: %.2f\n", pr->price);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Preço digitado inválido. Verifique se é maior que 0.         |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 4:
                                    do
                                    {
                                        printf("|||            Validade (dd/mm/aaaa):                                       |||\n");
                                        printf("|||            (NOTA: insira 00/00/0000 para datas indeterminadas)          |||\n");
                                        printf("|||            Digite: ");
                                        scanf("%d%*c%d%*c%d", &(pr->day_expiration), &(pr->month_expiration), &(pr->year_expiration));

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_expiration_date(pr->day_expiration, pr->month_expiration, pr->year_expiration);
                                        if (is_valid){
                                            if (pr->year_expiration == 0 && pr->month_expiration == 0 && pr->day_expiration == 0)
                                            {
                                                printf("|||            Data inserida como \"INDETERMINADA\"                               |||\n");

                                            } else {
                                                printf("|||            Data digitada: %02d/%02d/%04d                                    |||\n", pr->day_expiration, pr->month_expiration, pr->year_expiration);

                                            }
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
                            
                            fseek(p_file, -1*sizeof(Product), SEEK_CUR);
                            fwrite(pr, sizeof(Product), 1, p_file);
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
        printf("|||            >> Produto não encontrado!                                    |||\n");
    }

    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    fclose(p_file);
    free(pr);
}

void remove_product(char search[]) {
    FILE* p_file;
    Product* pr;
    int found = 0;
    char aux[100] = "";

    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    
    while(fread(pr, sizeof(Product), 1, p_file)) {
        strcpy(aux, pr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_product(pr);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_products.dat", "r+b");
    if (found) {  
        printf("Qual produto gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) 
        {
            getchar();
            found = 0;
            while(fread(pr, sizeof(Product), 1, p_file)) {
                strcpy(aux, pr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            pr->activated = 0;
                            fseek(p_file, -1*sizeof(Product), SEEK_CUR);
                            fwrite(pr, sizeof(Product), 1, p_file);
                            printf("\nProduto excluído!\n");
                        } else {
                            printf("\nOperação cancelada!\n");

                        }
                    }
                }
            }
        }
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Produto não encontrado!                                    |||\n");
    }

    fclose(p_file);
    free(pr);
}

typedef struct service Service;

struct service {
    int id_service;
    char description[100];
    char type[100];
    float price;
    int activated;
};


// salva o serviço em um arquivo
int save_service(Service* sr) {
    FILE *p_file; // cria variável ponteiro para o arquivo
    p_file = fopen("db_services.dat", "ab");
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    int found = 0;
    Service* aux_sr = (Service*)malloc(sizeof(Service));
    while(fread(aux_sr, sizeof(Service), 1, p_file)) {
        found++;
    }
    free(aux_sr);

    sr->id_service = found + 1;

    fwrite(sr, sizeof(Service), 1, p_file);
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");
    printf("CADASTRADO COM SUCESSO!!\n");
    return 0;
}

// Trata os dados para salvar no serviço
void insert_service(char description[], char type[], float price) {
    Service* new_service = (Service*)malloc(sizeof(Service));

    strcpy(new_service->description, description);
    strcpy(new_service->type, type);
    new_service->price = price;
    new_service->activated = 1;
    save_service(new_service);
    free(new_service);
}

// Função para imprimir um serviço
void print_service(Service* sr) {
    if ((sr == NULL)) {
        printf("\n= = = SERVIÇO INEXISTENTE = = =\n");
    } else {
        printf(" = = = SERVIÇO = = = \n");
        printf("Descrição: %s\n", sr->description);
        printf("Tipo: %s\n", sr->type);
        printf("Preço: %.2f\n", sr->price);
        
        if (sr->activated) {
            printf("Situação do serviço: Ativo \n");
        } else {
            printf("Situação do serviço: Inativo \n");
        }
        
    }
}

// Função para listar todos os serviços
void list_services(void) {
    FILE* p_file;
    Service* sr;
    int found = 0;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há serviços cadastrados!\n");
        return;
    }

    while(fread(sr, sizeof(Service), 1, p_file)) {
        if (sr->activated) {
            print_service(sr);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhum serviço encontrado! \n");
    }
    
    free(sr);
    fclose(p_file);
}


void find_service(char search[]) {
    FILE* p_file;
    Service* sr;
    int found = 0;
    char aux[100] = "";
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há serviços cadastrados!\n");
        return;
    }

    while(fread(sr, sizeof(Service), 1, p_file)) {
        strcpy(aux, sr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
            print_service(sr);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhum serviço encontrado! \n");
    }
    fclose(p_file);
    free(sr);
}


void update_service(char search[]) {
    FILE* p_file;
    Service* sr;
    int found = 0;
    char aux[100] = "";
    int is_valid = 0;
    char caractere;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    while(fread(sr, sizeof(Service), 1, p_file)) {
        strcpy(aux, sr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_service(sr);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_services.dat", "r+b");
    if (found) {  
        printf("Qual serviço gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) {
            getchar();
            found = 0;
            while(fread(sr, sizeof(Service), 1, p_file)) {
                strcpy(aux, sr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
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
                            printf("|||            [1] Descrição: %s\n", sr->description);
                            printf("|||            [2] Tipo do serviço: %s\n", sr->type);
                            printf("|||            [3] Preço: %.2f\n", sr->price);
                            printf("|||            [0] Finalizar edição                                         |||\n");
                            printf("|||                                                                         |||\n");
                            printf("|||            >> Opção: ");
                            scanf("%d", &op);
                            getchar();

                            switch (op) {
                                case 1:
                                    do
                                    {
                                        printf("|||            Descrição: ");
                                        scanf("%[^\n]%*c", sr->description);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(sr->description);
                                        if (is_valid){
                                            printf("|||            Descrição digitada: %s\n", sr->description);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Descrição digitada inválida.                                 |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 2:
                                    do
                                    {
                                        printf("|||            Tipo/categoria: ");
                                        scanf("%[^\n]%*c", sr->type);

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_name(sr->type);
                                        if (is_valid){
                                            printf("|||            Tipo/categoria digitado: %s\n", sr->type);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Tipo/categoria digitada inválida.                            |||\n");
                                            printf("|||            Digite apenas letras e espaços.                              |||\n");
                                            printf("|||                                                                         |||\n");
                                        }
                                    } while (!is_valid);
                                    break;

                                case 3:
                                    do
                                    {
                                        printf("|||            Preço: ");
                                        scanf("%f", &(sr->price));

                                        while ((caractere = getchar()) != '\n' && caractere != EOF);
                                        is_valid = validate_price(sr->price);
                                        if (is_valid){
                                            printf("|||            Preço digitado: %.2f\n", sr->price);
                                            printf("|||                                                                         |||\n");
                                        } else {
                                            printf("|||            Preço digitado inválido. Verifique se é maior que 0.         |||\n");
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
                            
                            fseek(p_file, -1*sizeof(Service), SEEK_CUR);
                            fwrite(sr, sizeof(Service), 1, p_file);
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
        printf("|||            >> Serviço não encontrado!                                    |||\n");
    }

    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    fclose(p_file);
    free(sr);
}

void remove_service(char search[]) {
    FILE* p_file;
    Service* sr;
    int found = 0;
    char aux[100] = "";

    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return;
    }
    
    while(fread(sr, sizeof(Service), 1, p_file)) {
        strcpy(aux, sr->description);
        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_service(sr);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_services.dat", "r+b");
    if (found) {  
        printf("Qual serviço gostaria de editar (ID)? ");
        int id = 0;
        scanf("%d", &id);
        if ((id > 0) & (id <= found)) 
        {
            getchar();
            found = 0;
            while(fread(sr, sizeof(Service), 1, p_file)) {
                strcpy(aux, sr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            sr->activated = 0;
                            fseek(p_file, -1*sizeof(Service), SEEK_CUR);
                            fwrite(sr, sizeof(Service), 1, p_file);
                            printf("\nServiço excluído!\n");
                        } else {
                            printf("\nOperação cancelada!\n");

                        }
                    }
                }
            }
        }
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Serviço não encontrado!                                    |||\n");
    }

    fclose(p_file);
    free(sr);
}

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

int has_worker(char cpf[]) {
    FILE* p_file;
    Worker* wk;

    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "r+b");
    if (p_file == NULL) {
        return false;
    }

    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if ((strcmp(wk->cpf, cpf) == 0)) {
            fclose(p_file);
            free(wk);
            return true;
        }
    }

    fclose(p_file);
    free(wk);
    return false;
}

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

    if (has_worker(wk->cpf)) {
        fclose(p_file);
        printf("Erro! Funcionário já cadastrado! \n");
        return 1;
    }

    fwrite(wk, sizeof(Worker), 1, p_file);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");
    printf("CADASTRADO COM SUCESSO!!\n");

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
        printf(" = = = FUNCIONÁRIO = = = \n");
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
        printf("Verifique se há funcionários cadastrados!\n");
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
        printf("Nenhum funcionário encontrado! \n");
    }
    
    free(wk);
    fclose(p_file);
}


void find_worker(char cpf[]) {
    FILE* p_file;
    Worker* wk;
    int found = 0;
    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há funcionários cadastrados!\n");
        return;
    }

    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if ((strcmp(wk->cpf, cpf) == 0) && (wk->activated)) {
            print_worker(wk);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhum funcionário encontrado! \n");
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

typedef struct sale Sale;

struct sale {
    int id_sale;
    char client_cpf[12];
    char worker_cpf[12];    
    int product_id;
    struct tm date;
    int activated;
};

int choose_product() {
    FILE* p_file;
    Product* pr;
    int found = 0;
    char aux[100] = "";
    char search[255] = "";
    int is_valid = 0;
    char caractere;
    int aux_return = 0;
    pr = (Product*) malloc(sizeof(Product));
    p_file = fopen("db_products.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return 0;
    }
    do
    {
        printf("|||            Nome do produto: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
            while(fread(pr, sizeof(Product), 1, p_file)) {
                strcpy(aux, pr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
                    found++;
                    printf(">> ID [%d] \n", found);
                    print_product(pr);
                    printf("\n");
                }
            }
            fclose(p_file);
            p_file = fopen("db_products.dat", "rb");
            if (found) {  
                printf("Qual produto está sendo comprado (ID)? (Digite 0 para buscar novamente) ");
                int id = 0;
                scanf("%d", &id);
                if ((id > 0) & (id <= found)) {
                    getchar();
                    found = 0;
                    while(fread(pr, sizeof(Product), 1, p_file)) {
                        strcpy(aux, pr->description);
                        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (pr->activated)) {
                            found++;
                            if (found == id)
                            {
                                print_product(pr);
                                aux_return = pr->id_product;
                            }
                        }
                    }
                } else {
                    printf("|||                                                                         |||\n");
                    printf("|||            >> Opção não encontrada!                                     |||\n");
                }
                
            } else {
                printf("|||                                                                         |||\n");
                printf("|||            >> Produto não encontrado!                                    |||\n");
            }

        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    fclose(p_file);
    free(pr);
    return aux_return;
}

// salva a venda em um arquivo
int save_sale(Sale* sl) {
    FILE *p_file; // cria variável ponteiro para o arquivo

    p_file = fopen("db_sales.dat", "ab");
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    int found = 0;
    Sale* aux_sl = (Sale*)malloc(sizeof(Sale));
    while(fread(aux_sl, sizeof(Sale), 1, p_file)) {
        found++;
    }
    free(aux_sl);
    
    sl->id_sale = found + 1;

    fwrite(sl, sizeof(Sale), 1, p_file);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");

    return 0;
}


// Trata os dados para salvar na venda
void insert_sale(char client_cpf[], char worker_cpf[], int product_id) {
    Sale* new_sale = (Sale*)malloc(sizeof(Sale));

    strcpy(new_sale->client_cpf, client_cpf);
    strcpy(new_sale->worker_cpf, worker_cpf);
    new_sale->product_id = product_id;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);    
    new_sale->date = tm;
    new_sale->activated = 1;

    save_sale(new_sale);
    free(new_sale);
}

// Função para imprimir uma venda
void print_sale(Sale* sl) {
    if ((sl == NULL)) {
        printf("\n= = = VENDA INEXISTENTE = = =\n");
    } else {
        printf(" = = = VENDA = = = \n");
        printf("CPF do Funcionário: %s\n", sl->worker_cpf);
        printf("CPF do Cliente: %s\n", sl->client_cpf);
        FILE* p_file;
        Product* pr;
        pr = (Product*) malloc(sizeof(Product));
        p_file = fopen("db_products.dat", "rb");
        if (p_file == NULL) {
            printf("Ops! Erro na abertura do arquivo!\n");
            printf("Não é possível continuar...\n");
            return;
        }

        while(fread(pr, sizeof(Product), 1, p_file)) {
            if ((sl->product_id == pr->id_product) && (pr->activated)) {
                print_product(pr);
            }
        }
        fclose(p_file);
        free(pr);

        printf("Vendido(a) em: %02d/%02d/%d - %02d:%02d:%02d\n", sl->date.tm_mday, sl->date.tm_mon, (sl->date.tm_year + 1900), sl->date.tm_hour, sl->date.tm_min, sl->date.tm_sec);

        if (sl->activated) {
            printf("Situação da venda: Ativo \n");
        } else {
            printf("Situação da venda: Inativo \n");
        }        
        printf(" = = = = = = = = = \n");
    }
}

// Função para listar todos os funcionários
void list_sales(void) {
    FILE* p_file;
    Sale* sl;
    int found = 0;
    sl = (Sale*) malloc(sizeof(Sale));
    p_file = fopen("db_sales.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há vendas cadastradas!\n");
        return;
    }

    while(fread(sl, sizeof(Sale), 1, p_file)) {
        if (sl->activated) {
            print_sale(sl);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhuma venda encontrada! \n");
    }
    
    free(sl);
    fclose(p_file);
}


void find_sale(char cpf[]) {
    Sale* sl;
    int found = 0;
    sl = (Sale*) malloc(sizeof(Sale));
    FILE* p_file;
    p_file = fopen("db_sales.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há vendas cadastradas!\n");
        return;
    }
    while(fread(sl, sizeof(Sale), 1, p_file)) {
        if ((strcmp(sl->worker_cpf, cpf) == 0) && (sl->activated)) {
            print_sale(sl);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhuma venda encontrada! \n");
    }
    fclose(p_file);
    free(sl);
}

void remove_sale(char cpf[]) {
    FILE* p_file;
    Sale* sl;
    int found = 0;

    sl = (Sale*) malloc(sizeof(Sale));
    p_file = fopen("db_sales.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Verifique se há vendas cadastradas!\n");
        return;
    }
    
    while(fread(sl, sizeof(Sale), 1, p_file)) {
        if ((strcmp(sl->worker_cpf, cpf) == 0) && (sl->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_sale(sl);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_sales.dat", "r+b");
    if (found) {  
        printf("Qual venda gostaria de remover (ID)? ");
        int id = 0;
        scanf("%d", &id);
        getchar();
        if ((id > 0) & (id <= found)) 
        {
            found = 0;
            while(fread(sl, sizeof(Sale), 1, p_file)) {
                if ((strcmp(sl->worker_cpf, cpf) == 0) && (sl->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            sl->activated = 0;
                            fseek(p_file, -1*sizeof(Sale), SEEK_CUR);
                            fwrite(sl, sizeof(Sale), 1, p_file);
                            printf("\nVenda excluída!\n");
                        } else {
                            printf("\nOperação cancelada!\n");

                        }
                    }
                }
            }
        } else {
            printf("Opção inválida! \n");
        }
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Venda não encontrada!                                     |||\n");
    }

    fclose(p_file);
    free(sl);
}

typedef struct appointment Appointment;

struct appointment {
    int id_appointment;
    int animal_id;
    char worker_cpf[12];    
    int service_id;
    struct tm date;
    int activated;
};

int choose_service() {
    FILE* p_file;
    Service* sr;
    int found = 0;
    char aux[100] = "";
    char search[255] = "";
    int is_valid = 0;
    char caractere;
    int aux_return = 0;
    sr = (Service*) malloc(sizeof(Service));
    p_file = fopen("db_services.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return 0;
    }
    do
    {
        printf("|||            Nome do serviço: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
            found = 0;
            while(fread(sr, sizeof(Service), 1, p_file)) {
                strcpy(aux, sr->description);
                if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
                    found++;
                    printf(">> ID [%d] \n", found);
                    print_service(sr);
                    printf("\n");
                }
            }
            fclose(p_file);
            p_file = fopen("db_services.dat", "rb");
            if (found) {  
                printf("Qual serviço está sendo adquirido (ID)? (Digite 0 para buscar novamente) ");
                int id = 0;
                scanf("%d", &id);
                getchar();
                if ((id > 0) & (id <= found)) {
                    found = 0;
                    while(fread(sr, sizeof(Service), 1, p_file)) {
                        strcpy(aux, sr->description);
                        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (sr->activated)) {
                            found++;
                            if (found == id)
                            {
                                print_service(sr);
                                aux_return = sr->id_service;
                            }
                        }
                    }
                } else if (id == 0) {
                    is_valid = false;
                } else {
                    printf("|||                                                                         |||\n");
                    printf("|||            >> Opção não encontrada!                                     |||\n");
                }
                
            } else {
                printf("|||                                                                         |||\n");
                printf("|||            >> Serviço não encontrado!                                    |||\n");
                printf("Tentar novamente? (s/n)");
                char opc = 'n';
                scanf(" %c", &opc);
                getchar();
                if (opc == 's')
                {
                    is_valid = false;
                }
            }

        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    fclose(p_file);
    free(sr);
    return aux_return;
}

int choose_animal() {
    FILE* p_file;
    Animal* an;
    int found = 0;
    char aux[100] = "";
    char search[255] = "";
    int is_valid = 0;
    char caractere;
    int aux_return = 0;
    char cpf[12] = "";
    do
    {
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
        } else if (!has_client(cpf))
        {
            printf("|||            CPF digitado inválido. Cliente INEXISTENTE!                  |||\n");
            printf("|||                                                                         |||\n");
        } else {
            printf("|||            CPF digitado inválido. Lembre-se de digitar apenas números!  |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!(is_valid && has_client(cpf)));

    an = (Animal*) malloc(sizeof(Animal));
    p_file = fopen("db_animals.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Não é possível continuar...\n");
        return 0;
    }
    do
    {
        printf("|||            Nome do animal: ");
        scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", search);

        while ((caractere = getchar()) != '\n' && caractere != EOF);
        is_valid = validate_name(search);
        if (is_valid){
            printf("|||            Nome digitado: %s\n", search);
            printf("|||                                                                         |||\n");
            found = 0;
            while(fread(an, sizeof(Animal), 1, p_file)) {
                if ((strcmp(an->cpf, cpf) == 0) && (an->activated)) {
                    strcpy(aux, an->name);
                    if (strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) {
                        found++;
                        printf(">> ID [%d] \n", found);
                        print_animal(an);
                        printf("\n");
                    }
                }
            }
            fclose(p_file);
            p_file = fopen("db_animals.dat", "rb");
            if (found) {  
                printf("Qual animal está adquirindo o serviço (ID)? (Digite 0 para buscar novamente) ");
                int id = 0;
                scanf("%d", &id);
                getchar();
                if ((id > 0) & (id <= found)) {
                    found = 0;
                    while(fread(an, sizeof(Animal), 1, p_file)) {
                        strcpy(aux, an->name);
                        if ((strncmp(str_to_lower(aux), str_to_lower(search), strlen(search)) == 0) && (an->activated)) {
                            found++;
                            if (found == id)
                            {
                                print_animal(an);
                                aux_return = an->id_animal;
                            }
                        }
                    }
                } else if (id == 0) {
                    is_valid = false;
                } else {
                    printf("|||            >> Opção não encontrada!                                     |||\n");
                    printf("|||                                                                         |||\n");
                }
                
            } else {
                printf("|||            >> Animal não encontrado!                                    |||\n");
                printf("|||                                                                         |||\n");
                printf("Tentar novamente? (s/n)");
                char opc = 'n';
                scanf(" %c", &opc);
                getchar();
                if (opc == 's')
                {
                    is_valid = false;
                }
                
            }

        } else {
            printf("|||            Nome digitado inválido. Digite apenas letras e espaços.      |||\n");
            printf("|||                                                                         |||\n");
        }
    } while (!is_valid);
    fclose(p_file);
    free(an);
    return aux_return;
}

// salva a consulta em um arquivo
int save_appointment(Appointment* sl) {
    FILE *p_file; // cria variável ponteiro para o arquivo

    p_file = fopen("db_appointments.dat", "ab");
    if(p_file == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    } 
    int found = 0;
    Appointment* aux_sl = (Appointment*)malloc(sizeof(Appointment));
    while(fread(aux_sl, sizeof(Appointment), 1, p_file)) {
        found++;
    }
    free(aux_sl);
    
    sl->id_appointment = found + 1;

    fwrite(sl, sizeof(Appointment), 1, p_file);

    //usando fclose para fechar o arquivo
    fclose(p_file);
    printf("Dados gravados com sucesso! \n");
    printf("CADASTRADO COM SUCESSO!!\n");
    return 0;
}

// Trata os dados para salvar na venda
void insert_appointment(char worker_cpf[], int animal_id, int service_id) {
    Appointment* new_appointment = (Appointment*)malloc(sizeof(Appointment));

    strcpy(new_appointment->worker_cpf, worker_cpf);
    new_appointment->animal_id = animal_id;
    new_appointment->service_id = service_id;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);    
    new_appointment->date = tm;
    new_appointment->activated = 1;

    save_appointment(new_appointment);
    free(new_appointment);
}

// Função para imprimir uma venda
void print_appointment(Appointment* ap) {
    if ((ap == NULL)) {
        printf("\n= = = CONSULTA INEXISTENTE = = =\n");
    } else {
        printf(" = = = CONSULTA = = = \n");
        printf("CPF do Funcionário: %s\n", ap->worker_cpf);
        FILE* p_file;
        Animal* an;
        an = (Animal*) malloc(sizeof(Animal));
        p_file = fopen("db_animals.dat", "rb");
        if (p_file == NULL) {
            printf("Ops! Erro na abertura do arquivo!\n");
            printf("Não é possível continuar...\n");
            return;
        }

        while(fread(an, sizeof(Animal), 1, p_file)) {
            if ((ap->animal_id == an->id_animal) && (an->activated)) {
                print_animal(an);
            }
        }
        fclose(p_file);
        free(an);

        Service* sr;
        sr = (Service*) malloc(sizeof(Service));
        p_file = fopen("db_services.dat", "rb");
        if (p_file == NULL) {
            printf("Ops! Erro na abertura do arquivo!\n");
            printf("Não é possível continuar...\n");
            return;
        }

        while(fread(sr, sizeof(Service), 1, p_file)) {
            if ((ap->service_id == sr->id_service) && (sr->activated)) {
                print_service(sr);
            }
        }
        fclose(p_file);
        free(sr);

        printf("Realizado em: %02d/%02d/%d - %02d:%02d:%02d\n", ap->date.tm_mday, ap->date.tm_mon, (ap->date.tm_year + 1900), ap->date.tm_hour, ap->date.tm_min, ap->date.tm_sec);

        if (ap->activated) {
            printf("Situação da consulta: Ativo \n");
        } else {
            printf("Situação da consulta: Inativo \n");
        }        
        printf(" = = = = = = = = = \n");
    }
}

// Função para listar todos os funcionários
void list_appointments(void) {
    FILE* p_file;
    Appointment* ap;
    int found = 0;
    ap = (Appointment*) malloc(sizeof(Appointment));
    p_file = fopen("db_appointments.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há consultas cadastradas!\n");
        return;
    }

    while(fread(ap, sizeof(Appointment), 1, p_file)) {
        if (ap->activated) {
            print_appointment(ap);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhuma consulta encontrada! \n");
    }
    
    free(ap);
    fclose(p_file);
}


void find_appointment(char cpf[]) {
    Appointment* ap;
    int found = 0;
    ap = (Appointment*) malloc(sizeof(Appointment));
    FILE* p_file;
    p_file = fopen("db_appointments.dat", "rb");
    if (p_file == NULL) {
        printf("Ops! Erro na abertura do arquivo!\n");
        printf("Verifique se há consultas cadastradas!\n");
        return;
    }
    while(fread(ap, sizeof(Appointment), 1, p_file)) {
        if ((strcmp(ap->worker_cpf, cpf) == 0) && (ap->activated)) {
            print_appointment(ap);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("Nenhuma consulta encontrada! \n");
    }
    fclose(p_file);
    free(ap);
}

void remove_appointment(char cpf[]) {
    FILE* p_file;
    Appointment* ap;
    int found = 0;

    ap = (Appointment*) malloc(sizeof(Appointment));
    p_file = fopen("db_appointments.dat", "r+b");
    if (p_file == NULL) {
        printf("Ops! Erro abertura do arquivo!\n");
        printf("Verifique se há consultas cadastradas!\n");
        return;
    }
    
    while(fread(ap, sizeof(Appointment), 1, p_file)) {
        if (((strcmp(ap->worker_cpf, cpf) == 0)) && (ap->activated)) {
            found++;
            printf(">> ID [%d] \n", found);
            print_appointment(ap);
            printf("\n");
        }
    }
    fclose(p_file);
    p_file = fopen("db_appointments.dat", "r+b");
    if (found) {  
        printf("Qual consulta gostaria de remover (ID)? ");
        int id = 0;
        scanf("%d", &id);
        getchar();
        if ((id > 0) & (id <= found)) 
        {
            found = 0;
            while(fread(ap, sizeof(Appointment), 1, p_file)) {
                if ((strcmp(ap->worker_cpf, cpf) == 0) && (ap->activated)) {
                    found++;
                    if (found == id)
                    {
                        printf(">> Confirma remoção? (s/n)");
                        char finish = 'n';
                        scanf(" %c", &finish);
                        getchar();
                        
                        if (tolower(finish) == 's'){
                            ap->activated = 0;
                            fseek(p_file, -1*sizeof(Appointment), SEEK_CUR);
                            fwrite(ap, sizeof(Appointment), 1, p_file);
                            printf("\nConsulta excluída!\n");
                        } else {
                            printf("\nOperação cancelada!\n");

                        }
                    }
                }
            }
        } else {
            printf("Opção inválida! \n");
        }
    } else {
        printf("|||                                                                         |||\n");
        printf("|||            >> Consulta não encontrada!                                     |||\n");
    }

    fclose(p_file);
    free(ap);
}
