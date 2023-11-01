typedef struct client Client;
struct client;
int save_client(Client* cl);
void insert_client(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born);
void print_client(Client* cl);
void list_clients(void);
void find_client(char cpf[]);
void update_client(char cpf[]); 
void remove_client(char cpf[]);

typedef struct animal Animal;
struct animal;
int save_animal(Animal* an);
void insert_animal(char cpf[], char name[], char species[], char race[], float weight, int day_born, int month_born, int year_born);
void print_animal(Animal* an);
void list_animals(void);
void find_animal(char cpf[], char search[]);
void update_animal(char cpf[], char search[]); 
void remove_animal(char cpf[]);

typedef struct worker Worker;
struct worker;
int save_worker(Worker* wk);
void insert_worker(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born);
void print_worker(Worker* wk);
void list_workers(void);
void find_worker(char cpf[]);
void update_worker(char cpf[]); 
void remove_worker(char cpf[]);