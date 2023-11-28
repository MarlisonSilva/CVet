typedef struct service Service;
struct service {
    int id_service;
    char description[100];
    char type[100];
    float price;
    int activated;
};
int save_service(Service* sr);
void insert_service(char description[], char type[], float price);
void print_service(Service* sr);
void list_services(void);
void find_service(char search[]);
void update_service(char search[]); 
void remove_service(char search[]);
void find_services_by(char search[], int opc);
Service* get_service(int service_id);