#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#define SYS_CALL 333
#define ID_LEN 20
#define LIST 1
#define CREATE 2
#define STATE 3
#define START 4
#define PS 5
#define PAUSE 6
#define RESUME 7
#define KILL 8
#define DELETE 9

static void display_file(const char *file_name) {
    FILE *f_ptr = fopen(file_name, "r");
    if (f_ptr != NULL) {
        int ch;
        while ((ch = fgetc(f_ptr)) != EOF) {
            putchar(ch);
        }
        fclose(f_ptr);
    }

    printf("\n");
}

void getContainerID(char* container_id) {
    printf("Enter Container ID: ");
    fgets(container_id, ID_LEN , stdin);
    container_id[strlen(container_id) - 1] = '\0';
}

int manage_option(int option) {
    int container_id_size = ID_LEN;
    char container_id[container_id_size];

    if (option == LIST) { printf("\n --- List Containers --- \n\n"); }
    else if(option == CREATE) {
        printf("\n --- Create Container --- \n\n");
        getContainerID(container_id);
        chdir("ca644_alpine");
        char *arg[] = {"runc", "create", container_id, NULL};
        return execvp(arg[0], arg);
    }
    else if(option == STATE) { printf("\n --- Get Container State --- \n\n"); }
    else if(option == START) { printf("\n --- Start Container --- \n\n"); }
    else if(option == PS) { printf("\n --- List services inside container --- \n\n"); }
    else if(option == PAUSE) { printf("\n --- Pause Container Execution --- \n\n"); }
    else if(option == RESUME) { printf("\n --- Resume Container Execution --- \n\n"); }
    else if(option == KILL) { printf("\n --- Kill Container --- \n\n"); }
    else if(option == DELETE) { printf("\n --- Delete Stopped Container --- \n\n"); }

    if(option != LIST)
        getContainerID(container_id);

    int ret_code = syscall(SYS_CALL, option, container_id);

    if(ret_code == 0 && (option == LIST || option == STATE || option == PS))
        display_file("/tmp/ca644_util_log");

    return ret_code;
}

int startMenu() {
    printf("------------------------------------------\n");
    printf("        Container Util - System Call      \n");
    printf("------------------------------------------\n\n");

    char menu_option[10];

    printf("1. List Containers\n");
    printf("2. Create Container\n");
    printf("3. Get Container State\n");
    printf("4. Start Container\n");
    printf("5. List services running inside Container\n");
    printf("6. Pause Container Execution\n");
    printf("7. Resume Container Execution\n");
    printf("8. Kill Container\n");
    printf("9. Delete Stopped Container\n");
    printf("Choose Option From Menu Above 1-9: ");

    fgets(menu_option, 10 , stdin);

    return atoi(menu_option);
}

int main() {
    int container_id_size = ID_LEN;
    int menu_option, ret_code;
    char container_id[container_id_size];

    menu_option = startMenu();

    if (menu_option >= LIST && menu_option <= DELETE) {
        ret_code = manage_option(menu_option);
    }
    else {
        printf("\n Invalid Choice! \n");
        return 1;
    }

    if(ret_code != 0) {
        printf("\n OH OH Something went wrong! \n");

        if (menu_option != CREATE) {
            display_file("/tmp/ca644_util_log");
        }

        return 1;
    }

    return 0;
}
