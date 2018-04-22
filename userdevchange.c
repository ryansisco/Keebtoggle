#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void editkeyboard(char change[2000]) {
	char choice[2000];
	char data[2000];
	printf("New device will be: %s\n", change);
	printf("Are you sure??? (y/n): ");
	scanf("%s", choice);
	if ((choice[0] != 'y') && (choice[0] != 'Y')) {
		printf("Cancelling...\n");
		exit(0);
	}
	char swap[2000] = "#define KEYBOARDNAME \""; 
	strcat(swap, change);
	strcat(swap, "\"");
	FILE *fp;
	fp = popen("keyboard.c", "w+");
	while (fgets(data, 2000, fp) != NULL) {
		if (strstr(data, "#define")) {
			fprintf(fp, "%s", swap);
		}
		else {
			fprintf(fp, "%s", data);
		}
	}
	pclose(fp);
	system("gcc keyboard.c -o keyboard");
}

int main(int argc, char* argv[]) {
	int i = 1;
	char choice[2000];
	char change[2000];
	system("xinput -list");
	printf("The current saved device is: ");
	while (argv[i]) {
		printf("%s ", argv[i]);
		i++;
	}
	printf("\nIs this correct? (y/n): ");
	scanf("%s", choice);
	if ((choice[0] == 'y') || (choice[0] == 'Y')) {
		exit(0);
	}
	if ((choice[0] == 'n') || (choice[0] == 'N')) {
		printf("New Device Name: ");
		scanf("%s", change);
	}
	else {
		printf("Bad input, exiting...\n");
		exit(1);
	}
	editkeyboard(change);
	return 0;
}