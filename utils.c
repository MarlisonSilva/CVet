// Validations:
// [ ] Nome
// [ ] CPF
// [ ] E-mail
// [ ] Data
// [ ] Telefone
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>

#include "utils.h"

#define true 1
#define false 0

int validate_name(char name[]) {    
    if (strlen(name) >= 2){
        return true;
    }
    return false; 
}

int validate_cpf(char cpf[]) {
    if (strlen(cpf) >= 11 && !has_space(cpf)){
        int i = 0;
        int n = 10;
        int soma = 0;
        int aux = 0;
        do {
            aux = cpf[i] - '0';
            soma += (aux * n);  
            n--;
            i++;
        } while (i < 9);
        int verificador = (soma*10) % 11;
        verificador = verificador == 10? 0: verificador;
        if (verificador != (cpf[i] -'0'))
        {
            return false;
        }
        i = 0;
        n = 11;
        soma = 0;
        aux = 0;
        do {
            aux = cpf[i] - '0';
            soma += (aux * n);  
            n--;
            i++;
        } while (i < 10);
        verificador = (soma*10) % 11;
        verificador = verificador == 10? 0: verificador;
        if (verificador != (cpf[i] -'0'))
        {
            return false;
        }
        
        return true;
    }
    return false;
}

int validate_email(char email[]) {
    email = str_to_lower(email);
    char aux [255];
    if (strlen(email) >= 7 && !has_space(email)) {
        aux[0] = '\0';
        // prefixo
        int pos = 0;
        do {
            aux[pos] = email[pos];
            pos++;
        } while ((email[pos] != '\0') && (email[pos] != '@'));
        aux[pos] = '\0';

        if (strlen(aux) >= 1 && strlen(aux) <= 64){
            // primeira letra não é alfa-numérica e a última é um ponto
            if(!isalnum(aux[0]) || aux[strlen(aux) - 1] == '.') {
                return false;
            }
        } else {
            return false;
        }
        
        // caso não haja mais 2 caracteres após o @
        if (strlen(email) < (pos + 2)) {
            return false;
        }

        // domínio
        pos = pos + 1;
        int i = 0;
        aux[0] = '\0';

        do {
            aux[i] = email[pos];
            pos++;
            i++;
        } while ((email[pos] != '\0') && (email[pos] != '.'));
        aux[i] = '\0';

        // domínio de tamanho incorreto
        if (strlen(aux) >= 2 && strlen(aux) <= 253){
            // primeira e última letra não é alfa-numérica
            if(!isalnum(aux[0]) || !isalnum(aux[strlen(aux) - 1])) {
                return false;
            }
        } else {
            return false;
        }

        // caso não haja mais 2 caracteres após o .
        if (strlen(email) < (pos + 2)) {
            return false;
        }
        pos = pos + 1;
        i = 0;
        aux[0] = '\0';
        do {
            aux[i] = email[pos];
            pos++;
            i++;
        } while (email[pos] != '\0');
        aux[i] = '\0';
        
        // tamanho do top level domain incorreto
        if (strlen(aux) >= 2 && strlen(aux) <= 253){
            // primeira e última letra não é alfa-numérica
            if(!isalnum(aux[0]) || !isalnum(aux[strlen(aux) - 1])) {
                return false;
            }
            
        } else {
            return false;
        }
        
        return true;

    }
    return false;
}

int validate_date(int day, int month, int year) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (year >= 1500 && year <= (tm.tm_year + 1900) && day > 0)
    {
        if (year < (tm.tm_year + 1900) || (year == (tm.tm_year + 1900) && month < tm.tm_mon + 1)) {
            switch (month){
                case 1:
                    if (day <= 31)
                    {
                        return true;
                    }
                    break;
                case 2:
                    if (year % 4 == 0){
                        if (day <= 29)
                        {
                            return true;
                        }
                    } else {
                        if (day <= 28)
                        {
                            return true;
                        } 
                    }
                    break;
                case 3:
                    if (day <= 31)
                    {
                        return true;
                    }
                    break;
                case 4:
                    if (day <= 30)
                    {
                        return true;
                    }
                    break;
                case 5:
                    if (day <= 31)
                    {
                        return true;
                    }
                    break;
                case 6:
                    if (day <= 30)
                    {
                        return true;
                    }
                    break;
                case 7:
                    if (day <= 31)
                    {
                        return true;
                    }
                    break;
                case 8:
                    if (day <= 31)
                    {
                        return true;
                    }
                    break;
                case 9:
                    if (day <= 30)
                    {
                        return true;
                    }
                    break;
                case 10:
                    if (day <= 31)
                    {
                        return true;
                    }
                    break;
                case 11:
                    if (day <= 30)
                    {
                        return true;
                    }
                    break;
                case 12:
                    if (day <= 31)
                    {
                        return true;
                    }
                    break;
                default:
                    break;
            } 
            
        } else if (month == (tm.tm_mon + 1) && day <= tm.tm_mday) {
            return true;
        }
        
        
    }
    
    
    return false;
}

int validate_phone(char phone[]) {
    if (strlen(phone) >= 11)
    {
        return true;
    }
    
    return false;
}

int validate_price(float price) {
    if (price >= 0){
        return true;
    }
    return false;
}


// auxiliares
char* str_to_lower(char* str){
    char *aux = str;
    char c = ' ';
    for (int i = 0; i < strlen(str); i++)
    {
        aux[i] = tolower(str[i]);
    } 
    return aux;
}


int has_space(char* str) {
    for (int i = 0; str[i] != '\0'; i++)
    {   
        if (isspace(str[i]))
        {
            return true;
        }
        
    }
    
    return false;
}