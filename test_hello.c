#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
extern FILE *stdin;

static void display_file(const char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (f != NULL) {
        int c;
        while ((c = fgetc(f)) != EOF) {
            putchar(c);
        }
        fclose(f);
    }
}

void validate(char *input) {
    if(strlen(input) < 0 || strlen(input) > 20 || input == NULL || input == "\n") {
        printf("\nOps, Invalid Container Id.. Exiting\n\n");
        exit(0);
    }
} 

int manage_option(int option) {
    int container_id_size = 20;
    char container_id[container_id_size];

    if(option == 2) {
        printf("\n --- Create Container --- \n\n");
        printf("Enter Container ID: ");
	scanf("%s", container_id);
        validate(container_id);
	chdir("ca644_alpine");
        char *arg[] = {"runc", "create", container_id, NULL};
        printf("\nCreating Container...\n\n");
        return execvp(arg[0], arg);    
    }
    else if(option == 3) {
        printf("\n --- Get Container State --- \n\n");
        printf("Enter Container ID: ");
        scanf("%s", container_id);
        validate(container_id);
        return syscall(333, option, container_id);
    }
    else if(option == 4) {
        printf("\n --- Start Container --- \n\n");
        printf("Enter Container ID: ");
        scanf("%s", container_id);
        validate(container_id);
        printf("\nStarting Container...\n\n");
        return syscall(333, option, container_id);
    }
    else if(option == 5) {
        printf("\n --- List services inside container --- \n\n");
        printf("Enter Container ID: ");
        scanf("%s", container_id);
        validate(container_id);
        int ret_code = syscall(333, option, container_id);

        if(ret_code == 0) {
            display_file("/tmp/ca644_util_log");
        }

        return ret_code;
    }
    else if(option == 6) {
        printf("\n --- Pause Container Execution --- \n\n");
        printf("Enter Container ID: ");
        scanf("%s", container_id);
        validate(container_id);
        printf("Pausing Container...\n\n");
        return syscall(333, option, container_id);
    }
    else if(option == 7) {
        printf("\n --- Resume Container Execution --- \n\n");
        printf("Enter Container ID: ");
        scanf("%s", container_id);
        validate(container_id);
        printf("Resuming Container Execution...\n\n");
        return syscall(333, option, container_id);
    }
    else if(option == 8) {
        printf("\n --- Kill Container --- \n\n");
        printf("Enter Container ID: ");
        scanf("%s", container_id);
        validate(container_id);
        printf("\nKilling Container...\n\n");
        return syscall(333, option, container_id);
    }
    else if(option == 9) {
        printf("\n --- Delete Stopped Container --- \n\n");
        printf("Enter Container ID: ");
        scanf("%s", container_id);
        validate(container_id);
        printf("\nDeleting Container...\n\n");
        return syscall(333, option, container_id);
    }
    else if(option == 4) {

    }
}

int main() {
    printf("------------------------------------------\n");
    printf("        Container Util - System Call      \n");
    printf("------------------------------------------\n\n");

    int menu_option;
    int container_id_size = 20;
    char container_id[container_id_size];
    long int ret_code;

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
    scanf("%d1", &menu_option);

    if (menu_option == 1) {
        printf("\n --- List Containers --- \n\n");
        ret_code = syscall(333, menu_option, NULL);
        display_file("/tmp/ca644_util_log");
    }
    else if (menu_option >= 2 && menu_option <= 9) {
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
