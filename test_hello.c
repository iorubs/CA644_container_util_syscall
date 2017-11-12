#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

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

int manage_container(int i) {
    int manage_choice;
    char container_id[12];
    sprintf(container_id, "%d", i);
    char *container_action_1 = "1";
    char *container_action_2 = "2";
    char *container_action_3 = "3";

    printf("\n --- Manage Container %d --- \n\n",i);
    printf("1. Kill Container\n");
    printf("2. Stop Container\n");
    printf("3. Start Container\n\n");
    printf("Manage Choice : ");
    scanf("%d", &manage_choice);

    if(manage_choice == 1) {
        printf("\nKilling Container With Id: %d\n\n",i);
        long int ret_code = syscall(333, container_action_1, container_id);
        return ret_code;
    }
    else if(manage_choice == 2){
        printf("\nStoping Container With Id: %d\n\n",i);
        long int ret_code = syscall(333, container_action_2, container_id);
        return ret_code;
    }
    else if(manage_choice == 3){
        printf("\nStarting Container With Id: %d\n\n",i);
        long int ret_code = syscall(333, container_action_3, container_id);
        return ret_code;
    }
    else {
        printf("\nInvalid Choice Exiting...\n\n");
        return 0;
    }
}

int create_container(int i) {
    char *container_type = "none";

    if(i == 1) {
        printf("\nCreating BusyBox container...\n\n");
        container_type = "alpine"
    }
    else if(i == 2) {
        printf("\nCreating new Alpine container...\n\n");
        container_type = "busybox"
    }

    return syscall(333, 1, container_type);
}

int main() {
    printf("------------------------------------------\n");
    printf("        Container Util - System Call      \n");
    printf("------------------------------------------\n\n");

    int menu_option, new_container_choice, container_id_choice;
    long int ret_code;

    printf("1. Create Container\n");
    printf("2. List Containers\n");
    printf("3. Manage Containers\n\n");
    printf("Choose Option From Menu Above 1-3: ");
    scanf("%d", &menu_option);

    switch(menu_option) {
        case(1):
            printf("\n --- Choose New Container Type --- \n\n");
            printf("1. BusyBox Container \n");
            printf("2. Apline Container \n");
            printf("\nChoose Option From Menu Above 1-2: ");
            scanf("%d", &new_container_choice);
            create_container(new_container_choice);
            break;

        case(2):
            printf("\n --- List Containers --- \n\n");
            ret_code = syscall(333, 2, NULL);
            display_file("/tmp/ca644_container_util/log");
            break;
        case(3):
            printf("\nEnter Container ID : ");
            scanf("%d", &container_id_choice);
            manage_container(container_id_choice);
            break;

        default:
            printf("\n Invalid Choice! \n");
            break;
    }
}
