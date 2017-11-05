#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

int manage_container(int i) {

	int manage_choice;

	printf("\n --- Manage Container %d --- \n\n",i);
	printf("1. Kill Container\n\n");
	printf("Manage Choice : ");
	scanf("%d",&manage_choice);

	return 0;
}

int main() {

	//long int amma = syscall(333);
	//printf("System call sys_hello returned %ld\n", amma);

	printf("\n------------------------------------------\n");
	printf("        Container Util Tool\n");
  printf("------------------------------------------\n\n");

	int menu_option;
	int new_container_choice;
	int container_id_choice;

    printf("1. Create Container\n");
    printf("2. Manage Containers\n");
		printf("3. Exit\n\n");
    printf("Choose Option From Menu Above 1-3: ");
    scanf("%d",&menu_option);

		switch(menu_option){

			case(1):
			printf("\n --- Create Container --- \n\n");
			printf("1. New Busy Box\n");
			printf("2. New Alpine Box\n\n");
			printf("Choose Option From Menu Above 1-2: ");
			scanf("%d",&new_container_choice);
			break;

			case(2):
			printf("\n --- Manage Containers --- \n\n");
			system("docker ps");
			printf("\nManage Container With ID : ");
			scanf("%d",&container_id_choice);
			manage_container(container_id_choice);
			break;

			case(3):
			printf("\n --- Bye --- \n");
			break;

			default:
			printf("\n Invalid Choice! \n");
			break;
		}

}
