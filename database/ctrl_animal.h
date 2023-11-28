typedef struct animal Animal;
struct animal {
    int id_animal;
    char cpf[12];
    char name[100];
    char species[100];
    char race[100];
    float weight;
    int day_born;
    int month_born;
    int year_born;
    int activated;
};
int save_animal(Animal* an);
void insert_animal(char cpf[], char name[], char species[], char race[], float weight, int day_born, int month_born, int year_born);
void print_animal(Animal* an);
void list_animals(void);
void find_animal(char cpf[], char search[]);
void update_animal(char cpf[], char search[]); 
void remove_animal(char cpf[], char search[]); 
Animal* get_animal(int animal_id);