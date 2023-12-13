typedef struct client Client;
struct client {
    char cpf[12]; // "primária"
    char name[100];
    char email[255];
    char phone[12];
    int day_born;
    int month_born;
    int year_born;
    int activated;
    Client* next;
};
int save_client(Client* cl);
void insert_client(char cpf[], char name[], char email[], char phone[], int day_born, int month_born, int year_born);
void print_client(Client* cl);
void list_clients(void);
void find_client(char cpf[]);
void update_client(char cpf[]); 
void remove_client(char cpf[]);
int has_client(char cpf[]);
void find_clients_by(char search[], int opc);
void list_clients_az();
void clear_client(Client* cl);
Client* get_client(char client_cpf[]);