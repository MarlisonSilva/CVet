///////////////////////////////////////////////////////////////////////////////
///             Universidade Federal do Rio Grande do Norte                 ///
///                 Centro de Ensino Superior do Seridó                     ///
///               Departamento de Computação e Tecnologia                   ///
///                  Disciplina DCT1106 -- Programação                      ///
///          Projeto Sistema de Gestão de Clínica Veterinária               ///
///           Desenvolvido por @iamrlison -- desde Ago, 2023                ///
///////////////////////////////////////////////////////////////////////////////
///                                Semana 2                                 ///
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define true 1
#define false 0

///////////////////////////////////////////////////////////////////////////////
// Variáveis globais
char caractere;
// Definição da estrutura do nó da lista de clientes
struct Client {
    char cpf[11];
    char name[100];
    char email[255];
    char phone[13];
    int dayBorn, monthBorn, yearBorn;
    struct Client* next;
};

struct Client* listClients = NULL; // Lista de clientes

/////
// Assinatura das funções
// Menu principal
char main_menu();
void about_soft();
void about_dev();
// Menu cliente
char client_menu();
void create_client();
void search_client();
void edit_client();
void delete_client();
// Menu animal
char animal_menu();
void create_animal();
void search_animal();
void edit_animal();
void delete_animal();
// Menu produto
char product_menu();
void create_product();
void search_product();
void edit_product();
void delete_product();
// Menu venda  
char sale_menu();
void create_sale();
void search_sale();
void delete_sale();
// Menu funcionário
char worker_menu();
void create_worker();
void search_worker();
void edit_worker();
void delete_worker();

void header();
void header_complete();
void no_operation();
void insertClient(struct Client** list, char cpf[], char name[], char email[], char phone[], int dayBorn, int monthBorn, int yearBorn);
int saveData();
char* clientToString(struct Client* list);

/////
// Programa principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brasil");
    int isRunning = true;
    while (isRunning){
        char op = main_menu();
        char inMenu = false;
        char sub_op;
        switch (op)
        {
        case '0': // FECHAR PROGRAMA
            isRunning = false;
            break;
        case '1': // CLIENTES
            inMenu = true;
            while(inMenu) { 
                sub_op = client_menu();
                if (sub_op == '0') { // Sair clientes
                    inMenu = false;
                } else if (sub_op == '1') { // Cadastrar cliente
                    create_client();
                } else if (sub_op == '2') { // Pesquisar cliente
                    search_client();
                } else if (sub_op == '3') { // Atualizar cliente
                    edit_client();
                } else if (sub_op == '4') { // Remover cliente
                    delete_client();
                } else {
                    no_operation("Menu Cliente");
                }
            }
            break;
        case '2': // ANIMAIS
            inMenu = true;
            while(inMenu) { 
                sub_op = animal_menu();
                if (sub_op == '0') { // Sair animal
                    inMenu = false;
                } else if (sub_op == '1') { // Cadastrar animal
                    create_animal();
                } else if (sub_op == '2') { // Pesquisar animal
                    search_animal();
                } else if (sub_op == '3') { // Atualizar animal
                    edit_animal();
                } else if (sub_op == '4') { // Remover animal
                    delete_animal();
                } else {
                    no_operation("Menu Animal");
                }
            }
            break;
        
        case '3': // PRODUTOS e SERVIÇOS
            inMenu = true;
            while(inMenu) { 
                sub_op = product_menu();
                if (sub_op == '0') { // Sair animal
                    inMenu = false;
                } else if (sub_op == '1') { // Cadastrar produtos e serviços
                    create_product();
                } else if (sub_op == '2') { // Pesquisar produtos e serviços
                    search_product();
                } else if (sub_op == '3') { // Atualizar produtos e serviços
                    edit_product();
                } else if (sub_op == '4') { // Remover produtos e serviços
                    delete_product();
                } else {
                    no_operation("Menu Produtos e serviços");
                }
            }
            break;

        case '4': // VENDAS
            inMenu = true;
            while(inMenu) { 
                sub_op = sale_menu();
                if (sub_op == '0') { // Sair venda
                    inMenu = false;
                } else if (sub_op == '1') { // Cadastrar venda
                    create_sale();
                } else if (sub_op == '2') { // Pesquisar venda
                    search_sale();
                } else if (sub_op == '3') { // Remover venda
                    delete_sale();
                } else {
                    no_operation("Menu Venda");
                }
            }
            break;
        case '5': // FUNCIONÁRIOS 
            inMenu = true;
            while(inMenu) { 
                sub_op = worker_menu();
                if (sub_op == '0') { // Sair funcionário
                    inMenu = false;
                } else if (sub_op == '1') { // Cadastrar funcionário
                    create_worker();
                } else if (sub_op == '2') { // Pesquisar funcionário
                    search_worker();
                } else if (sub_op == '3') { // Atualizar funcionário
                    edit_worker();
                } else if (sub_op == '4') { // Remover funcionário
                    delete_worker();
                } else {
                    no_operation("Menu Funcionário");
                }
            }
            break;
        
        case '6':
            about_soft();
            break;
        case '7':
            about_dev();
            break;
        default:
            no_operation("Menu Principal");
            break;
        }
          
    }
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Funções

// Adaptado do ChatGPT 3.5
// Função para inserir um elemento no final da lista de clientes
void insertClient(struct Client** list, char cpf[], char name[], char email[], char phone[], int dayBorn, int monthBorn, int yearBorn) {
    struct Client* newClient = (struct Client*)malloc(sizeof(struct Client));

    strcpy(newClient->cpf, cpf);
    strcpy(newClient->name, name);
    strcpy(newClient->email, email);
    strcpy(newClient->phone, phone);
    newClient->dayBorn = dayBorn;
    newClient->monthBorn = monthBorn;
    newClient->yearBorn = yearBorn;
    newClient->next = NULL;

    if (*list == NULL) {
        *list = newClient;
    } else {
        struct Client* current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newClient;
    }
}

// Função para imprimir os elementos da lista
void printClients(struct Client* list) {
    struct Client* current = list;
    while (current != NULL) {
        printf("Cliente: \n");
        printf("CPF: %s\n", current->cpf);
        printf("Nome: %s\n", current->name);
        printf("E-mail: %s\n", current->email);
        printf("Telefone: %s\n", current->phone);
        printf("Data de nascimento: %02d/%02d/%d\n", current->dayBorn, current->monthBorn, current->yearBorn);
        current = current->next;
    }
    printf("\n");
}

// Adaptado de linguagemc.com.br
// salva os dados cadastrados em um arquivo
int saveData() {
    FILE *pont_arq; // cria variável ponteiro para o arquivo
    
    //abrindo o arquivo com tipo de abertura w
    pont_arq = fopen("db_cvet.txt", "w");
    
    //testando se o arquivo foi realmente criado
    if(pont_arq == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    
    char* list = clientToString(listClients);
    printf("Lista: %s\n", list);

    //usando fprintf para armazenar a string no arquivo
    fprintf(pont_arq, "%s", list);
    
    //usando fclose para fechar o arquivo
    fclose(pont_arq);
    
    printf("Dados gravados com sucesso! \n");

    // Libera a memória alocada
    free(list);

    return 0;
}

// Adaptado do ChatGPT
// Conversão da lista de struct para String
char* clientToString(struct Client* list) {
    char* result = (char*)malloc(1);  // Inicializa a string vazia
    result[0] = '\0';  // Garante que a string está terminada corretamente
    
    struct Client* current = list;
    while (current != NULL) {
        char temp[100];
        printf(temp, "%s, %s, %s, %s, %d, %d, %d \n", current->cpf, current->name, current->email, current->phone, current->dayBorn, current->monthBorn, current->yearBorn);
        result = (char*)realloc(result, strlen(result) + strlen(temp) + 1);
        strcat(result, temp);
        current = current->next;
    }

    return result;
}

char main_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header_complete();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = =      Clínica Veterinária CVet      = = = =           ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Módulo Clientes                                           ///\n");
    printf("///            2. Módulo Animais                                            ///\n");
    printf("///            3. Módulo Produtos e Serviços                                ///\n");
    printf("///            4. Módulo Vendas                                             ///\n");
    printf("///            5. Módulo Funcionários                                       ///\n");
    printf("///            6. Sobre o software                                          ///\n");
    printf("///            7. Sobre o desenvolvedor                                     ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a opção desejada: ");
    scanf(" %c", &op);
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); getchar();
    return op;
}


void about_soft() {
    system("clear||cls");
    printf("\n");
    header_complete();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = =      Clínica Veterinária CVet      = = = =           ///\n");
    printf("///                                                                         ///\n");
    printf("///  Programa desenvolvido na disciplina DCT1106 - Programação, para fins   ///\n");
    printf("///  de estudo. O sistema em questão, nomeado CVet, é direcionado para a    ///\n");
    printf("///  a gestão de uma clínica veterinária. O CVet conta com módulos de:      ///\n");
    printf("///  clientes, animais, produtos e serviços, funcionários e vendas. O CVet  ///\n");
    printf("///  foi desenvolvido por Marlison Soares, graduando em BSI.                ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void about_dev() {
    system("clear||cls");
    printf("\n");
    header_complete();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///           = = = =      Clínica Veterinária CVet      = = = =            ///\n");
    printf("///                                                                         ///\n");
    printf("///            Este projeto exemplo foi desenvolvido por:                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            Marlison Soares da Silva                                     ///\n");
    printf("///            E-mail: marlison.silva@ufrn.edu.br                           ///\n");
    printf("///            Redes sociais: @iamrlison                                    ///\n");
    printf("///            Git: https://github.com/kanashi-br/CVet.git                  ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
} 


//// Cliente
///////////////////////////////////////////////////////////////////////////////
char client_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = =  Menu Cliente = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar um novo cliente                                 ///\n");
    printf("///            2. Pesquisar os dados de um cliente                          ///\n");
    printf("///            3. Atualizar o cadastro de um cliente                        ///\n");
    printf("///            4. Excluir um cliente do sistema                             ///\n");
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


void create_client() {
    char cpf[11], name[100], email[255], phone[13];
    int day, month, year;
    
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Cadastrar Cliente  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF (apenas números): ");
    scanf("%s", cpf);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Nome completo: ");
    scanf("%[^\n]%*c", name);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            E-mail: ");
    scanf("%s", email);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Data de Nascimento (dd/mm/aaaa): ");
    scanf("%d%*c%d%*c%d", &day, &month, &year);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Celular (apenas números): ");
    scanf("%s", phone);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    // insertClient(&listClients, cpf, name, email, phone, day, month, year);
    // saveData();
    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_client() {
    
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Pesquisar Cliente  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números): ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("buscado: %s", search);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_client() {
    
    char cpf_client[11];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Alterar Cliente  = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números): ");
    scanf("%s", cpf_client);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a informação que deseja alterar:                     ///\n");
    printf("///            1- Nome: Pessoa da Silva                                     ///\n");
    printf("///            2- E-mail: pessoa@gmail.com                                  ///\n");
    printf("///            3- Data de nascimento: 26/08/2023                            ///\n");
    printf("///            4- Nº de telefone: 84999999999                               ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("CPF do cliente alterado: %s", cpf_client);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_client() {
    
    char cpf_client[11];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = Excluir Cliente = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números): ");
    scanf("%s", cpf_client);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("CPF do cliente alterado: %s", cpf_client);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

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

// Produtos
///////////////////////////////////////////////////////////////////////////////
char product_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = =  Menu Produto = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar um novo produto                                 ///\n");
    printf("///            2. Pesquisar os dados de um produto                          ///\n");
    printf("///            3. Atualizar o cadastro de um produto                        ///\n");
    printf("///            4. Excluir um produto do sistema                             ///\n");
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


void create_product() {
    char description[100], type[100];
    float price;
    int day, month, year;
    
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Cadastrar Produto  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Descrição: ");
    scanf("%[^\n]%*c", description);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Tipo: ");
    scanf("%[^\n]%*c", type);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Preço: ");
    scanf("%f", &price);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Validade (dd/mm/aaaa): ");
    scanf("%d%*c%d%*c%d", &day, &month, &year);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    // 
    // saveData();
    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_product() {
    
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Pesquisar Produto  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe a descrição do produto: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("buscado: %s", search);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_product() {
    
    char search[100];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Alterar Produto  = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe a descrição do produto: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("    buscado: %s\n", search);
    printf("    = = Produto 1 = = \n");
    printf("    Descrição: Dipirona 500g \n");
    printf("    Tipo: Medicamento \n");
    printf("    Preço: R$ 27,00 \n");
    printf("    Data de validade: 29/11/2023 \n");
    printf("///                                                                         ///\n");
    printf("    >> Insira o nº do Produto: \n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a informação que deseja alterar:                     ///\n");
    printf("///            1- Descrição: Dipirona 500g                                  ///\n");
    printf("///            2- Tipo: Medicamento                                         ///\n");
    printf("///            3- Preço: R$ 27,00                                           ///\n");
    printf("///            4- Data de nascimento: 01/02/2022                            ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("Produto alterado! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_product() {
    
    char search[100];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = Excluir Produto = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe sobre o produto: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("    buscado: %s\n", search);
    printf("    = = Produto 1 = = \n");
    printf("    Descrição: Dipirona 500g \n");
    printf("    Tipo: Medicamento \n");
    printf("    Preço: R$ 27,00 \n");
    printf("    Data de validade: 29/11/2023 \n");
    printf("///                                                                         ///\n");
    printf("    >> Insira o nº do Produto: \n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("Produto deletado! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

// Vendas
///////////////////////////////////////////////////////////////////////////////
char sale_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = =  Menu Venda = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar um novo venda                                   ///\n");
    printf("///            2. Pesquisar os dados de um venda                            ///\n");
    printf("///            3. Excluir um venda do sistema                               ///\n");
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


void create_sale() {
    char cpf[11], product[255], animal[100];
    int day, month, year;
    
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = Cadastrar Venda = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF do cliente (apenas números): ");
    scanf("%s", cpf);
    while ((caractere = getchar()) != '\n' && caractere != EOF);    
    printf("///            Produto: ");
    scanf("%s", product);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Animal (Opcional): ");
    scanf("%s", animal);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");

    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_sale() {
    
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = Pesquisar Venda = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF do cliente ou funcionário: ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("buscado: %s", search);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_sale() {    
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = =  Excluir Venda  = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF do cliente ou funcionário (apenas números): ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("    buscado: %s", search);
    printf("    = = Venda 1 = = \n");
    printf("    Cliente: Marlison \n");
    printf("    Funcionário: Juan Vitório \n");
    printf("    Produto: Dipirona 500g - Medicamento \n");
    printf("    Valor: R$ 27,00 \n");
    printf("    Data da venda: 29/11/2023 \n");
    printf("///                                                                         ///\n");
    printf("    >> Insira o nº da venda: \n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("Venda desfeita! ");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

// Funcionários
///////////////////////////////////////////////////////////////////////////////
char worker_menu() {
    char op;
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Menu Funcionário = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar um novo funcionário                             ///\n");
    printf("///            2. Pesquisar os dados de um funcionário                      ///\n");
    printf("///            3. Atualizar o cadastro de um funcionário                    ///\n");
    printf("///            4. Excluir um funcionário do sistema                         ///\n");
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


void create_worker() {
    char cpf[11], name[100], email[255], phone[13];
    int day, month, year;
    
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = =  Cadastrar Funcionário  = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF (apenas números): ");
    scanf("%s", cpf);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Nome completo: ");
    scanf("%[^\n]%*c", name);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            E-mail: ");
    scanf("%s", email);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Data de Nascimento (dd/mm/aaaa): ");
    scanf("%d%*c%d%*c%d", &day, &month, &year);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///            Celular (apenas números): ");
    scanf("%s", phone);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    // saveData();
    printf("CADASTRADO COM SUCESSO!!\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); 
}


void search_worker() {
    
    char search[14];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = =  Pesquisar Funcionário  = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números): ");
    scanf("%s", search);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("buscado: %s", search);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_worker() {
    
    char cpf_worker[11];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = =  Alterar Funcionário  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números): ");
    scanf("%s", cpf_worker);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a informação que deseja alterar:                     ///\n");
    printf("///            1- Nome: Pessoa da Silva                                     ///\n");
    printf("///            2- E-mail: pessoa@gmail.com                                  ///\n");
    printf("///            3- Data de nascimento: 26/08/2023                            ///\n");
    printf("///            4- Nº de telefone: 84999999999                               ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("CPF do funcionário alterado: %s", cpf_worker);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_worker() {
    
    char cpf_worker[11];
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = Excluir Funcionário = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números): ");
    scanf("%s", cpf_worker);
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("CPF do funcionário alterado: %s", cpf_worker);
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}

void header_complete () {
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///             Universidade Federal do Rio Grande do Norte                 ///\n");
    printf("///                 Centro de Ensino Superior do Seridó                     ///\n");
    printf("///               Departamento de Computação e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
    printf("///          Projeto Sistema de Gestão de Clínica Veterinária               ///\n");
    printf("///           Desenvolvido por @iamrlison -- desde Ago, 2023                ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
}

void header() {
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            ===================================================          ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = = = =          ///\n");
    printf("///            = = = =       Clínica Veterinária CVet      = = = =          ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = = = =          ///\n");
    printf("///            ===================================================          ///\n");
    printf("///              Desenvolvido por @iamrlison -- desde Ago, 2023             ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
}

void no_operation(char next[]) {
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///       = = = =  Nenhuma função definida para esta operação  = = = =      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para voltar para %s...\n", next);
    getchar();
}