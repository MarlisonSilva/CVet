#include <time.h>
typedef struct appointment Appointment;
struct appointment {
    int id_appointment;
    int animal_id;
    char worker_cpf[12];    
    int service_id;
    struct tm date;
    int activated;
};
int choose_service();
int choose_animal();
int save_appointment(Appointment* ap);
void insert_appointment(char client_cpf[], int animal_id, int service_id);
void print_appointment(Appointment* ap);
void list_appointments(void);
void find_appointment(char search[]);
void remove_appointment(char search[]);
Appointment* get_appointment(int appointment_id);