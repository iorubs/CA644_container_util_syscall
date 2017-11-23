#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

static void display_file(const char *file_name) {
    FILE *f_ptr = fopen(file_name, "r");
    if (f_ptr != NULL) {
        int ch;
        while ((ch = fgetc(f_ptr)) != EOF) {
            putchar(ch);
        }
        fclose(f_ptr);
    }
}

void getContainerID(char* container_id) {
    printf("Enter Container ID: ");
    fgets(container_id, 40 , stdin);
    container_id[strlen(container_id) - 1] = '\0';
}

int manage_option(int option) {
    int container_id_size = 20;
    char container_id[container_id_size];

    if (option == 1) { printf("\n --- List Containers --- \n\n"); }
    else if(option == 2) {
        printf("\n --- Create Container --- \n\n");
        getContainerID(container_id);
        chdir("ca644_alpine");
        char *arg[] = {"runc", "create", container_id, NULL};
        return execvp(arg[0], arg);
    }
    else if(option == 3) { printf("\n --- Get Container State --- \n\n"); }
    else if(option == 4) { printf("\n --- Start Container --- \n\n"); }
    else if(option == 5) { printf("\n --- List services inside container --- \n\n"); }
    else if(option == 6) { printf("\n --- Pause Container Execution --- \n\n"); }
    else if(option == 7) { printf("\n --- Resume Container Execution --- \n\n"); }
    else if(option == 8) { printf("\n --- Kill Container --- \n\n"); }
    else if(option == 9) { printf("\n --- Delete Stopped Container --- \n\n"); }

    if(option != 1)
        getContainerID(container_id);

    int ret_code = syscall(333, option, container_id);

    if(ret_code == 0 && (option == 1 || option == 3 || option == 5))
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
    int container_id_size = 20;
    int menu_option, ret_code;
    char container_id[container_id_size];

    menu_option = startMenu();

    if (menu_option >= 1 && menu_option <= 9) {
        ret_code = manage_option(menu_option);
    }
    else {
        printf("\n Invalid Choice! \n");
        return 1;
    }

    if(ret_code != 0) {
        printf("\n OH OH Something went wrong! \n");

        if (menu_option >= 2 && menu_option <= 9) {
            display_file("/tmp/ca644_util_log");
        }

        return 1;
    }

    return 0;
}
