typedef struct product Product;
struct product {
    int id_product;
    char description[100];
    char type[100];
    float price;
    int day_expiration;
    int month_expiration;
    int year_expiration;
    int activated;
};
int save_product(Product* pr);
void insert_product(char description[], char type[], float price, int day_expiration, int month_expiration, int year_expiration);
void print_product(Product* pr);
void list_products(void);
void find_product(char search[]);
void update_product(char search[]); 
void remove_product(char search[]);