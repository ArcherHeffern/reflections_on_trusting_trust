#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// Getc, gets, fgets, scanf, sscanf, getline

#define MAX_USERS 8
#define MAX_STRLEN 64

int num_users = 0;
char* usernames[MAX_USERS];
char* passwords[MAX_USERS];

void create_account(char* username, char* password) {
	if (num_users == MAX_USERS) {
		fprintf(stderr, "Max users created\n");
		return;
	}
	for (int i = 0; i < num_users; i++) {
		if (strcasecmp(usernames[i], username) == 0) {
			printf("%d:%s:%s\n", i, usernames[i], username);
			fprintf(stderr, "User already exists\n");	
			return;
		}
	}
	usernames[num_users] = username;
	passwords[num_users] = password;
	num_users++;
}

void login(char* username, char* password) {
	int user_index = -1;
	for (int i = 0; i < num_users; i++) {
		if (strcasecmp(usernames[i], username) == 0) {
			user_index = i;
			break;
		}
	}
	if (user_index == -1) {
		fprintf(stderr, "Username not found\n");
		return;
	}
	if (strcmp(passwords[user_index], password) == 0) {
		printf("logged in!\n");
	} else {
		fprintf(stderr, "Bad password\n");
	}
}

void list_users() {
	for (int i = 0; i < num_users; i++) {
		printf("%s ", usernames[i]);
	}
	printf("\n");
}

void prompt(char* msg, char* buf) {
	printf("%s", msg);
	if (fgets(buf, MAX_STRLEN, stdin) == NULL) {
		fprintf(stderr, "Failed to read from stdin\n");
		exit(1);
	}
	int n_read = strlen(buf);
	if (n_read != 0 && buf[n_read-1] == '\n') {
		buf[n_read-1] = 0;
	}
}

int main() {
	char op[MAX_STRLEN];
	while (1) {
		char* username = malloc(MAX_STRLEN);
		char* password = malloc(MAX_STRLEN);
		prompt("Operation? (Create, Login, List, Quit): ", op);
		if (strcasecmp(op, "create") == 0) {
			prompt("Username: ", username);
			prompt("Password: ", password);
			create_account(username, password);
		} else if (strcasecmp(op, "login") == 0) {
			prompt("Username: ", username);
			prompt("Password: ", password);
			login(username, password);
		} else if (strcasecmp(op, "list") == 0) {
			list_users();
		} else if (strcasecmp(op, "quit") == 0) {
			break;
		} else {
			fprintf(stderr, "Unrecognized command\n");
		}
	}
	printf("Exiting...\n");
	for (int i = 0; i < num_users; i++) {
		free(usernames[i]);
		free(passwords[i]);
	}
}
