#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include "../utils.h"
#include "ctrl_worker.h"
#include "ctrl_animal.h"
#include "ctrl_sale.h"

#define true 1
#define false 0

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

    wk->next = NULL;
    fwrite(wk, sizeof(Worker), 1, p_file);

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
        printf("||| = = = = = = = = = = = = FUNCIONÁRIO INEXISTENTE = = = = = = = = = = = = |||\n");
    } else {
        printf("||| = = = = = = = = = = = = = = = FUNCIONÁRIO = = = = = = = = = = = = = = = |||\n");
        printf("|||                                                                         |||\n");
        printf("|||            CPF: %s\n", wk->cpf);
        printf("|||            Nome: %s\n", wk->name);
        printf("|||            E-mail: %s\n", wk->email);
        printf("|||            Telefone: %s\n", wk->phone);
        printf("|||            Data de nascimento: %02d/%02d/%d\n", wk->day_born, wk->month_born, wk->year_born);

        if (wk->activated) {
            printf("|||            Situação do funcionário: Ativo \n");
        } else {
            printf("|||            Situação do funcionário: Inativo \n");
        }
        printf("|||                                                                         |||\n");
        printf("||| = FIM FUNCIONÁRIO = = = = = = = = = = = = = = = = = = = = = = = = = = = |||\n");
        
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
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        ------- VERIFIQUE SE HÁ FUNCIONÁRIOS CADASTRADOS! -------        |||\n");
        return;
    }

    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if (wk->activated) {
            printf("|||        %s | %-30.30s | %02d/%02d/%04d        |||", wk->cpf, wk->name, wk->day_born, wk->month_born, wk->year_born);
            found++;
            printf("\n");
        }
    }
    if (found == 0)
    {
        printf("|||        ------------- NENHUM FUNCIONÁRIO CADASTRADO -------------        |||\n");
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
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        ------- Verifique se há funcionários cadastrados! -------        |||\n");
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
        printf("|||            Nenhum funcionário encontrado!                             |||\n");
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
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------------- Não é possível continuar! ---------------        |||\n");
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
        printf("|||            >> Funcionário não encontrado!                               |||\n");
        
    }
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
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        --------------- Não é possível continuar! ---------------        |||\n");
        return;
    }
    
    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if ((strcmp(wk->cpf, cpf) == 0) && (wk->activated)) {
            found = 1;
            wk->activated = 0;
            fseek(p_file, -1*sizeof(Worker), SEEK_CUR);
            fwrite(wk, sizeof(Worker), 1, p_file);
            printf("|||            Funcionário excluído!                                        |||\n");
        }
    }

    if (!found) {
        printf("|||            Funcionário não encontrado!                                  |||\n");
    }

    fclose(p_file);
    free(wk);
}

void find_workers_by(char search[], int opc){
    FILE* p_file;
    Worker* wk;
    int found = 0;
    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        ------- Verifique se há funcionários cadastrados! -------        |||\n");
        return;
    }

    if (opc == 4) {
        printf("|||        --- CPF --- | - Funcionário -- | -- E-mail -- | Nº vendas        |||\n");
    }  else {
        printf("|||        --- CPF --- | - Funcionário - | -- E-mail -- | Data Nasc.        |||\n");

    }
    
    while(fread(wk, sizeof(Worker), 1, p_file)) {
        switch (opc) {
        case 1:
            if ((strncmp(wk->name, search, strlen(search)) == 0) && (wk->activated)) {
                printf("|||        %s | %-15.15s | %-12.12s | %02d/%02d/%04d        |||", wk->cpf, wk->name, wk->email, wk->day_born, wk->month_born, wk->year_born);
                found++;
                printf("\n");
            } 
            break;
        case 2:
            if ((strncmp(wk->email, search, strlen(search)) == 0) && (wk->activated)) {
                printf("|||        %s | %-15.15s | %-12.12s | %02d/%02d/%04d        |||", wk->cpf, wk->name, wk->email, wk->day_born, wk->month_born, wk->year_born);
                found++;
                printf("\n");
            } 
            break;
        case 3:
            if (!(wk->activated)) {
                printf("|||        %s | %-15.15s | %-12.12s | %02d/%02d/%04d        |||", wk->cpf, wk->name, wk->email, wk->day_born, wk->month_born, wk->year_born);
                found++;
                printf("\n");
            } 
            break;
        case 4:
           if (wk->activated) {
                int count = 0;
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
                    if (((sl->date.tm_year + 1900) == (tm.tm_year + 1900)) && (sl->date.tm_mon == tm.tm_mon) && (sl->activated) && (strcmp(sl->worker_cpf, wk->cpf) == 0)) {
                        count++;
                    }
                }
                fclose(p_file_sl);
                free(sl);
                if (count > 0)
                {
                    printf("|||        %s | %-16.16s | %-12.12s | %9d        |||", wk->cpf, wk->name, wk->email, count);
                    found++;
                    printf("\n");
                }
            }

        default:
            break;
        }
        
    }
    if (found == 0)
    {
        printf("|||                      NENHUM FUNCIONÁRIO ENCONTRADO                      |||\n");
    }
    
    fclose(p_file);
    free(wk);
}

void list_workers_az(void) {
    FILE* p_file;
    Worker* wk;
    Worker* workers = NULL;
    Worker* aux_wk;
    int found = 0;
    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        ------- VERIFIQUE SE HÁ FUNCIONÁRIOS CADASTRADOS! -------        |||\n");
        return;
    }

    while(fread(wk, sizeof(Worker), 1, p_file)) {
        if (wk->activated) {
            if ((workers == NULL) || (strcmp(wk->name, workers->name) < 0)) {
                // substitui o topo da lista
                wk->next = workers;
                workers = wk;
            } else {
                Worker* prev = workers;
                Worker* curr = workers->next;
                while ((curr != NULL) && (strcmp(curr->name, wk->name) < 0)) {
                    prev = curr;
                    curr = curr->next;
                }
                prev->next = wk;
                wk->next = curr;
            }
            wk = (Worker *) malloc(sizeof(Worker));
            found++;
        }
    }

    free(wk);
    fclose(p_file);
    aux_wk = workers;
    do {
        printf("|||        %s | %-30.30s | %02d/%02d/%04d        |||", aux_wk->cpf, aux_wk->name, aux_wk->day_born, aux_wk->month_born, aux_wk->year_born);
        printf("\n");
        aux_wk = aux_wk->next;
    } while (aux_wk != NULL);
    
    if (found == 0) {
        printf("|||        ------------- NENHUM FUNCIONÁRIO CADASTRADO -------------        |||\n");
    }
    clear_worker(workers);
}

void clear_worker(Worker* wk){
    Worker* aux_wk;
  
    while (wk != NULL) {
        aux_wk = wk;
        wk = wk->next;
        free(aux_wk);
    }  
}

Worker* get_worker(char worker_cpf[]) {
    FILE* p_file;
    Worker* wk;
    wk = (Worker*) malloc(sizeof(Worker));
    p_file = fopen("db_workers.dat", "rb");
    if (p_file == NULL) {
        printf("|||        ----------- Ops! Erro na abertura do arquivo! -----------        |||\n");
        printf("|||        ------- Verifique se há funcionários cadastrados! -------        |||\n");
        return NULL;
    }
    while(fread(wk, sizeof(Worker), 1, p_file) && (wk->cpf != worker_cpf));
    fclose(p_file);
    return wk; 
}