# CVet

Sistema de Gerenciamento para Clínica Veterinária 

UFRN/CERES/DCT - Programação

Marlison Soares da Silva

Agosto, 2023

# Sobre o sistema

O sistema CVet conta com 7 módulos, sendo eles para: Clientes, Animais, Produtos, Serviços, Vendas, Consultas e Funcionários. 

Sobre o relacionamento entre esses módulos:

- Para o cadastro de uma consulta, é necessário que já tenha sido feito, pelo menos, o cadastro de 1 funcionário, 1 animal e 1 serviço.
- Para cadastrar um animal, é necessário que seu tutor já tenha sido cadastrado no módulo de clientes.
- Em contra partida, para cadastrar uma venda, não é necessário que haja um animal, apenas 1 cliente, 1 produto e 1 funcionário.
- Para os demais módulos, clientes, produtos, serviços e funcionários, seus registros não dependem de outros módulos.

# Execução do código

## No Linux
Primeiramente, clone o repositório:
``` PowerShell
git clone https://github.com/MarlisonSilva/CVet.git
```

Para executar o código, entre na pasta criada com o clone e insira os seguintes comandos:

1. Manualmente
   
Para compilar e executar:
``` PowerShell
gcc -c *.c database/*.c
gcc -o cvet.out *.o
./cvet.out
```

2. Com Makefile
   
Para compilar e executar:
``` PowerShell
make all
```
ou
``` PowerShell
make
```
Para apenas executar:
``` PowerShell
make run
```
Para limpar arquivos de compilação e execução:
``` PowerShell
make clean
```

## No Windows/Externamente

Disponível apenas no link abaixo, via Replit:
[Acesse o Replit](https://replit.com/@marlisonss/CVet)
