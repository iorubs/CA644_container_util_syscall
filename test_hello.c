#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

static void display_file(const char *file_name)
{
  FILE *f = fopen(file_name, "r");
  if (f != NULL)
  {
    int c;
    while ((c = fgetc(f)) != EOF)
    {
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
	scanf("%d",&manage_choice);

 	if(manage_choice == 1) {
  	printf("\nKilling Container With Id: %d\n\n",i);
  	long int amma = syscall(333,container_id,container_action_1);
  	return amma;
 	}
 	else if(manage_choice == 2){
  	printf("\nStoping Container With Id: %d\n\n",i);
  	long int amma = syscall(333,container_id,container_action_2);
  	return amma;
 	}
 	else if(manage_choice == 3){
  	printf("\nStarting Container With Id: %d\n\n",i);
  	long int amma = syscall(333,container_id,container_action_3);
  	return amma;
 	}
 	else {
  	printf("\nInvalid Choice Exiting...\n\n");
  	return 0;
 	}
}

int create_container(int i) {

    char container_action[12];
    sprintf(container_action, "%d", i);
    char *container_id = "0";

    if(i == 1) {
     printf("\nCreating Busy Box...\n\n");
     long int amma = syscall(333,container_id,container_action);
     return amma;
    }
    else if(i == 2) {
     printf("\nCreating Alpine Box...\n\n");
     long int amma = syscall(333,container_id,container_action);
     return 0;
    }
    else {
     printf("\nInvalid Choice Exiting...\n\n");
     return 0;
    }
}

int main() {

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
        printf("\n --- Choose Container Type --- \n\n");
        printf("1. New Busy Box \n");
        printf("2. New Apline Box \n");
        printf("\nChoose Option From Menu Above 1-2: ");
        scanf("%d",&new_container_choice);
        create_container(new_container_choice);
			break;

			case(2):
				printf("\n --- Manage Containers --- \n\n");
	      char *initial = "0";
	      long int amma = syscall(333,initial,initial);
				display_file("/tmp/container_util");
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
