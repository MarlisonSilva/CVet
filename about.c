#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "about.h"
#include "aux_functions.h"

void about_soft() {
    system("clear||cls");
    printf("\n");
    header_complete();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||            = = = =      Clínica Veterinária CVet      = = = =           |||\n");
    printf("|||                                                                         |||\n");
    printf("|||  Programa desenvolvido na disciplina DCT1106 - Programação, para fins   |||\n");
    printf("|||  de estudo. O sistema em questão, nomeado CVet, é direcionado para a    |||\n");
    printf("|||  a gestão de uma clínica veterinária. O CVet conta com módulos de:      |||\n");
    printf("|||  clientes, animais, produtos, serviços, vendas, consultas e             |||\n");
    printf("|||  funcionários. O CVet foi desenvolvido por Marlison Soares, graduando   |||\n");
    printf("|||  do Bacharelado de Sistemas de Informação.                              |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}


void about_dev() {
    system("clear||cls");
    printf("\n");
    header_complete();
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||                                                                         |||\n");
    printf("|||           = = = =      Clínica Veterinária CVet      = = = =            |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Este projeto exemplo foi desenvolvido por:                   |||\n");
    printf("|||                                                                         |||\n");
    printf("|||            Marlison Soares da Silva                                     |||\n");
    printf("|||            E-mail: marlison.silva@ufrn.edu.br                           |||\n");
    printf("|||            Redes sociais: @iamrlison                                    |||\n");
    printf("|||            Github: https://github.com/MarlisonSilva/CVet.git            |||\n");
    printf("|||            Replit: https://replit.com/@marlisonss/CVet                  |||\n");
    printf("|||                                                                         |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
    printf("\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
} 