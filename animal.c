#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"
#include "aux_functions.h"

char caractere;

// Animais
///////////////////////////////////////////////////////////////////////////////
char animal_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = =  Menu Animal  = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar um novo animal                                  ///\n");
    printf("///            2. Pesquisar os dados de um animal                           ///\n");
    printf("///            3. Atualizar o cadastro de um animal                         ///\n");
    printf("///            4. Excluir um animal do sistema                              ///\n");
    printf("///            0. Voltar ao menu anterior                                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a opção desejada: ");
    scanf(" %c", &op);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); getchar();
    return op;
}


void create_animal() {
    char cpf[11], name[100], especie[100],race[100];
    float weight;
    int day, month, year;
    
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =   Cadastrar Animal  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF do tutor (apenas números): ");
    scanf("%s", cpf);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Nome do animal: ");
    scanf("%[^\n]%*c", name);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Espécie: ");
    scanf("%s", especie);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Raça: ");
    scanf("%s", race);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Peso: ");
    scanf("%f", &weight);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Data de Nascimento (dd/mm/aaaa): ");
    scanf("%d%*c%d%*c%d", &day, &month, &year);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    // insertClient(&listAnimals, client, name, especie, race, weight, day, month, year);
    // saveData();
    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_animal() {
    char search[14];
    char cpf_client[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Pesquisar Animal  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF do tutor: ");
    scanf("%s", cpf_client);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Informe o nome do animal: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("buscado: %s de %s", search, cpf_client);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_animal() {
    char cpf_client[11];
    char search[100];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =   Alterar Animal  = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números): ");
    scanf("%s", cpf_client);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Informe o nome do animal: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("    buscado: %s de %s \n", search, cpf_client);
    printf("    = = Animal 1 = = \n");
    printf("    Nome: Choco \n");
    printf("    Espécie: Cachorro \n");
    printf("    Raça: Vira-lata \n");
    printf("    Peso: 27,0 Kg \n");
    printf("    Data de nasc.: 01/02/2022 \n");
    printf("///                                                                         ///\n");
    printf("    >> Insira o nº do Animal: \n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a informação que deseja alterar:                     ///\n");
    printf("///            1- Nome: Choco                                               ///\n");
    printf("///            2- Espécie: Cachorro                                         ///\n");
    printf("///            3- Raça: Vira-lata                                           ///\n");
    printf("///            4- Peso: 27,0 Kg                                             ///\n");
    printf("///            5- Data de nascimento: 01/02/2022                            ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("Animal alterado! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_animal() {
    
    char cpf_client[11];
    char search[100];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = =  Excluir Animal = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números): ");
    scanf("%s", cpf_client);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Informe o nome do animal: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("    buscado: %s de %s \n", search, cpf_client);
    printf("    = = Animal 1 = = \n");
    printf("    Nome: Choco \n");
    printf("    Espécie: Cachorro \n");
    printf("    Raça: Vira-lata \n");
    printf("    Peso: 27,0 Kg \n");
    printf("    Data de nasc.: 01/02/2022 \n");
    printf("///                                                                         ///\n");
    printf("    >> Insira o nº do Animal: \n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("Animal deletado!");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
} 