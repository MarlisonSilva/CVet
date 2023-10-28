typedef struct client Client;
struct client;
int save_client(Client* cl);
void insert_client(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born);
void print_client(Client* cl);
void list_clients(void);
