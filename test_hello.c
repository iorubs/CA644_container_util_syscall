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

int manage_option(int i) {
	
        int container_id_size = 20;
    	char container_id[container_id_size];
    	long int ret_code;
	int manage_choice;	

	if(i == 2) {
		printf("Start Container With Id : ");
    		scanf("%s", container_id);
		printf("\nStarting Container...\n\n");
                ret_code = syscall(333, i, container_id);
      
	}else if(i == 3) {
		printf("Delete Container With Id : ");
    		scanf("%d", &manage_choice);
		printf("\nDeleting Container...\n\n");
		ret_code = syscall(333, i, container_id);

	}else if(i == 4) {
		printf("List services inside container With Id : ");
    		scanf("%s", container_id);
		ret_code = syscall(333, i, container_id);


	}else if(i == 5) {
		printf("Create Container With Id : ");
    		scanf("%s", container_id);
                chdir("ca644_alpine");
		char *arg[] = {"runc", "create", container_id, NULL};
                printf("\nCreating Container...\n\n");
                return execvp(arg[0], arg);	
	}else {
        	printf("\nInvalid Choice Exiting...\n\n");
        	return 0;
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
    printf("2. Start Container\n");
    printf("3. Delete Container\n");
    printf("4. List services inside Container\n");
    printf("5. Create Container\n");
    printf("Choose Option From Menu Above 1-5: ");
    scanf("%d", &menu_option);

    switch(menu_option) {
        case(1):
            printf("\n --- List Containers --- \n\n");
            ret_code = syscall(333, menu_option, NULL);
            display_file("/tmp/ca644_util_log");
            break;
        case(2):
            printf("\n --- Start Container --- \n\n");
	    manage_option(menu_option);
            break;
        case(3):
            printf("\n --- Delete Container --- \n\n");
	    manage_option(menu_option);

            break;
        case(4):
            printf("\n --- List services inside container --- \n\n");
            manage_option(menu_option);
            break;
        case(5):
            printf("\n --- Create Container --- \n\n");
            manage_option(menu_option);
            break;
        default:
            printf("\n Invalid Choice! \n");
    }
}
