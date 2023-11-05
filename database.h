
/*
OK Cliente:
    cpf [primaria] 
    dados comuns

OK Animal:
    id [primaria]
    cpf cliente [estrangeira]
    dados comuns

OK Produto:
    id [primaria]
    dados comuns

OK Serviço:
    id [primaria]
    dados comuns

OK Funcionário:
    cpf [primaria]
    dados comuns

Vendas:
    id [primaria]
    cpf cliente [estrangeira]
    cpf funcionário [estrangeira]
    id produto [estrangeira]
    dados comuns

Consultas:
    id [primaria]
    cpf funcionário [estrangeira]
    id animal [estrangeira]
    id serviço [estrangeira]
    dados comuns

*/


typedef struct client Client;
struct client;
int save_client(Client* cl);
void insert_client(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born);
void print_client(Client* cl);
void list_clients(void);
void find_client(char cpf[]);
void update_client(char cpf[]); 
void remove_client(char cpf[]);
int has_client(char cpf[]);

typedef struct animal Animal;
struct animal;
int save_animal(Animal* an);
void insert_animal(char cpf[], char name[], char species[], char race[], float weight, int day_born, int month_born, int year_born);
void print_animal(Animal* an);
void list_animals(void);
void find_animal(char cpf[], char search[]);
void update_animal(char cpf[], char search[]); 
void remove_animal(char cpf[]);

typedef struct product Product;
struct product;
int save_product(Product* pr);
void insert_product(char description[], char type[], float price, int day_expiration, int month_expiration, int year_expiration);
void print_product(Product* pr);
void list_products(void);
void find_product(char search[]);
void update_product(char search[]); 
void remove_product(char search[]);

typedef struct service Service;
struct service;
int save_service(Service* sr);
void insert_service(char description[], char type[], float price);
void print_service(Service* sr);
void list_services(void);
void find_service(char search[]);
void update_service(char search[]); 
void remove_service(char search[]);

typedef struct sale Sale;
struct sale;
int choose_product();
int save_sale(Sale* sl);
void insert_sale(char client_cpf[], char worker_cpf[], int product_id);
void print_sale(Sale* sl);
void list_sales(void);
void find_sale(char search[]);
void remove_sale(char search[]);

typedef struct worker Worker;
struct worker;
int save_worker(Worker* wk);
void insert_worker(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born);
void print_worker(Worker* wk);
void list_workers(void);
void find_worker(char cpf[]);
void update_worker(char cpf[]); 
void remove_worker(char cpf[]);
int has_worker(char cpf[]);