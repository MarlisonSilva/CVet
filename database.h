typedef struct client Client;
struct client;
void insert_client(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born);
void print_clients();
int save_client(Client* client_to_save);
char* client_to_string(Client* list);