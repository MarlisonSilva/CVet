#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "../utils.h"

#define true 1
#define false 0

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
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Dados gravados:                                              |||\n");
    printf("|||            >> CADASTRADO FINALIZADO COM SUCESSO!                        |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
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

void remove_animal(char cpf[], char search[]) {
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
                            printf("|||                                                                         |||\n");
                            printf("|||            >> Animal excluído!                                          |||\n");
                        } else {
                            printf("|||                                                                         |||\n");
                            printf("|||            >> nOperação cancelada!                                      |||\n");
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