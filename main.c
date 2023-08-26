///////////////////////////////////////////////////////////////////////////////
///             Universidade Federal do Rio Grande do Norte                 ///
///                 Centro de Ensino Superior do Seridó                     ///
///               Departamento de Computação e Tecnologia                   ///
///                  Disciplina DCT1106 -- Programação                      ///
///          Projeto Sistema de Gestão de Clínica Veterinária               ///
///           Desenvolvido por @iamrlison -- desde Ago, 2023                ///
///////////////////////////////////////////////////////////////////////////////
///                                Semana 1                                 ///
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define true 1
#define false 0

/////
// Assinatura das funções
char main_menu();
void about_soft();
void about_dev();
char client_menu();
void create_client();
void search_client();
void edit_client();
void delete_client();
void header();
void header_complete();
void no_operation();

/////
// Programa principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brasil");
    int isRunning = true;
    while (isRunning){
        char op = main_menu();
        char sub_op;
        if (op == '0'){ // Sair
            isRunning = false;
        } else if(op == '1') { // Clientes
            char inMenu = true;
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
        } else if (op == '6'){ // Sobre o software
            about_soft();
        } else if (op == '7'){ // Sobre o desenvolvedor
            about_dev();
        } else {
            no_operation("Menu Principal");
        }
    }
    return 0;
}


/////
// Funções

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
    printf("///            4. Módulo Funcionários                                       ///\n");
    printf("///            5. Módulo Vendas                                             ///\n");
    printf("///            6. Sobre o software                                          ///\n");
    printf("///            7. Sobre o desenvolvedor                                     ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///            Escolha a opção desejada: ");
    scanf("%c", &op);

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
    scanf("%c", &op);
    
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar(); getchar();
    return op;
}


void create_client() {
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Cadastrar Cliente  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF (apenas números):                                        ///\n");
    printf("///            Nome completo:                                               ///\n");
    printf("///            E-mail:                                                      ///\n");
    printf("///            Data de Nascimento (dd/mm/aaaa):                             ///\n");
    printf("///            Celular (apenas números):                                    ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void search_client() {
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Pesquisar Cliente  = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números):                              ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void edit_client() {
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = =  Alterar Cliente  = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números):                              ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void delete_client() {
    system("clear||cls");
    printf("\n");
    header();
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///            = = = = = = = = Excluir Cliente = = = = = = = =              ///\n");
    printf("///            = = = = = = = = = = = = = = = = = = = = = = = =              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Informe o CPF (apenas números):                              ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
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