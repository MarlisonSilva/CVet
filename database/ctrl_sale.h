#include <time.h>
typedef struct sale Sale;
struct sale {
    int id_sale;
    char client_cpf[12];
    char worker_cpf[12];    
    int product_id;
    struct tm date;
    int activated;
    Sale* next;
};
int choose_product();
int save_sale(Sale* sl);
void insert_sale(char client_cpf[], char worker_cpf[], int product_id);
void print_sale(Sale* sl);
void list_sales(void);
void find_sale(char search[]);
void remove_sale(char search[]);
void find_sales_by(char search[], int opc);
void list_sales_date();
void clear_sale(Sale* sl);
Sale* get_sale(int sale_id);