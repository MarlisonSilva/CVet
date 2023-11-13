typedef struct sale Sale;
struct sale;
int choose_product();
int save_sale(Sale* sl);
void insert_sale(char client_cpf[], char worker_cpf[], int product_id);
void print_sale(Sale* sl);
void list_sales(void);
void find_sale(char search[]);
void remove_sale(char search[]);