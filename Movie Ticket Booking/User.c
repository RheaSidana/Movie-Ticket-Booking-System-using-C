#include "myHeader.h"
#include <stdio.h>

/*
File : userData.txt
*/

struct user getUser(int id) {
	struct user u;
	u.user_id = id;
	printf("\n Enter the User Name  : ");
	gets(u.name);
	printf("\n Enter the User Email  : ");
	gets(u.email);
	printf("\n Enter the User Gender(M/F/O)  : ");
	scanf_s("%c",&u.gender,1);
	printf("\n Enter the User Age  : ");
	scanf_s("%d", &u.age);
	int x = getchar();
	printf("\n Enter the User Mobile Number  : ");
	char arr[11] = {'\0'};
	gets(arr);
	for (int i = 0; i < 10; i++) {
		u.mobileno[i]=(int)arr[i]-(int)'0';
	}
	return u;
}

void displayUser(struct user u) {
	printf("\n \n Displaying User : \n ");
	printf(" User ID            : %d \n ", u.user_id);
	printf(" User Name          : %s \n ", u.name);
	printf(" User Email         : %s \n ", u.email);
	printf(" User Gender        : %c \n ", u.gender);
	printf(" User Age           : %d \n ", u.age);
	printf(" User Mobile Number : ");
	for (int i = 0; i < 10; i++) {
		printf("%d", u.mobileno[i]);
	}
	printf("\n");
}

void writeToUserFile(FILE* fpu,struct user u) {
	fprintf(fpu, "%d %d %c ", u.user_id, u.age, u.gender);
	for (int i = 0; i < 10; i++) {
		fprintf(fpu, "%d", u.mobileno[i]);
	}
	fprintf(fpu, "\n");
	fputs(u.name, fpu); fprintf(fpu, "\n");
	fputs(u.email, fpu); fprintf(fpu, "\n");
}

struct user readFromUserFile(FILE* fpu) {
	struct user u;
	char temp[12];
	fscanf(fpu, "%d %d %c ", &u.user_id, &u.age, &u.gender);
	fgets(temp, 12, fpu);
	for (int i = 0; i < 10; i++) {
		u.mobileno[i] = temp[i]-'0';
	}
	fscanf(fpu, "\n");
	fgets(u.name, 60, fpu); fscanf(fpu, "\n");
	fgets(u.email, 80, fpu); fscanf(fpu, "\n");

	int len = strlen(u.name);
	if (u.name[len - 1] == '\n')u.name[len - 1] = '\0';
	len = strlen(u.email);
	if (u.email[len - 1] == '\n')u.email[len - 1] = '\0';
	return u;
}

struct user addUser() {
	int id;
	struct user u;
	u.user_id = 0;
	FILE* fpu;
	fpu = fopen("userData.txt", "a");
	if (fpu == NULL) fileNotFound();
	else {
		fseek(fpu, 0, SEEK_END);
		int size = ftell(fpu);
		if (0 != size) {
			FILE* fpu2;
			fpu2 = fopen("userData.txt", "r");
			while (!feof(fpu2)) {
				u = readFromUserFile(fpu2);
			}
			fclose(fpu2);
		}
		u.user_id++;
		u = getUser(u.user_id);
		writeToUserFile(fpu,u);
		printf("\n User Added \n");
	}
	fclose(fpu);
	return u;
}

void viewAllUser() {
	heading(1);
	printf("\n Displaying all the Users: ");
	FILE* fpu;
	fpu = fopen("userData.txt", "r");
	if (fpu == NULL) fileNotFound();
	else {
		struct user u;
		while (!(feof(fpu))) {
			u = readFromUserFile(fpu);
			displayUser(u);
		}
	}
	fclose(fpu);
}

void viewMovieUser() {

}

void findUser() {
	heading(1);
	printf("\n Displaying the user: \n");
	int flag = 0;
	FILE* fpu;
	fpu = fopen("userData.txt", "r");
	if (fpu == NULL) fileNotFound();
	else {
		int id; 
		printf("Enter the User ID : ");
		scanf_s("%d", &id);
		struct user u;
		while (!(feof(fpu))) {
			u = readFromUserFile(fpu);
			if (u.user_id == id) {
				flag = 1;
				displayUser(u);
				break;
			}
		}
	}
	if (flag == 0) {
		printf("\n User not found");
	}
	fclose(fpu);
}

void viewUserBooking() {

}

int isUser(struct user *u) {
	char email[80] = {'\0'}, temp[11] = { '\0' };
	printf("\n Enter the email : ");
	gets(email);
	printf("\n Enter the number : ");
	gets(temp);

	int flag = 0;
	FILE* fpu;
	fpu = fopen("userData.txt", "r");
	if (fpu == NULL) fileNotFound();
	else {
		while (!(feof(fpu))) {
			*u = readFromUserFile(fpu);
			if (strcmp(u->email, email) == 0) {
				for (int i = 0; i < 10; i++) {
					if (u->mobileno[i] == (temp[i]-'0')) {
						flag = 1;
					}
					else { flag = 0; break; }
				}
				if (flag == 1)break;
			}
		}
	}
	fclose(fpu);
	return flag;
}

struct user loginUser() {
	heading(2);
	printf("\n Logging in User : \n");
	struct user u;
	int user = isUser(&u);
	if (user == 1) {
		printf("\n User Logged in successfully !! \n");
	}
	else { 
		printf("\n Not a User !! \n");
		u.user_id = 0;
	}
	//displayUser(u);
	return u;
}

void updateUser() {
	heading(2);
	printf("\n Updating User : \n\n");
	int flag = 0;
	FILE* fpu, * tm;
	fpu = fopen("userData.txt", "r");
	tm = fopen("Temporary.txt", "a");
	if (fpu == NULL || tm == NULL) fileNotFound();
	else {
		struct user u = loginUser();
		while (!feof(fpu)) {
			struct user temp = readFromUserFile(fpu);
			if (temp.user_id==u.user_id) {
				printf("\n Enter your choice : (USER) ");
				int ch,x;
				char val[80] = { '\0' };
				printf("\n 1.Name \n 2.Email \n 3.Age \n 4.Mobile Nummber \n 5.Gender \n ");
				scanf_s("%d", &ch);
				switch (ch) {
				case 1: x = getchar();
					printf("\n Enter the new Name : ");
					gets(val);
					strcpy(temp.name, val);
					break;
				case 2:x = getchar();
					printf("\n Enter the new Email : ");
					gets(val);
					strcpy(temp.email, val);
					break;
				case 3:printf("\n Enter the new Age : ");
					scanf_s("%d", &temp.age);
					break;
				case 4:x = getchar();
					printf("\n Enter the new Mobile Number : ");
					gets(val);
					for (int i = 0; i < 10; i++) {
						temp.mobileno[i] = val[i]-'0';
					}
					break;
				case 5:x = getchar();
					printf("\n Enter the new Gender : ");
					scanf_s("%c", &temp.gender,1);
					break;
				default: invalidOption();
					break;
				}
				flag = 1;
			}
			writeToUserFile(tm, temp);
		}
	}
	fclose(fpu);
	fclose(tm);
	if (flag == 0) {
		printf(" User not found ");
	}
	int r;
	r = remove("userData.txt");
	r = rename("Temporary.txt", "userData.txt");
}

void deleteUser() {
	heading(2);
	printf("\n Deleting User : \n");
	int flag = 0,del=0;
	FILE* fpu, * tm;
	fpu = fopen("userData.txt", "r");
	tm = fopen("Temporary.txt", "a");
	if (fpu == NULL || tm == NULL) fileNotFound();
	else {
		struct user u = loginUser();
		while (!feof(fpu)) {
			struct user temp = readFromUserFile(fpu);
			if (temp.user_id == u.user_id) {
				flag = 1;
				char ans;
				printf("\nAre you sure? (Y/N) \n");
				scanf_s("%c", &ans, 1);
				if (ans == 'y' || ans == 'Y') {
					del = 1;
				}
				else del = 0;
			}
			else if (del==0) {
				writeToUserFile(tm, temp);
			}
			if (del == 1) {
				del = 0;
				printf(" User Deleted ");
			}
		}
	}
	fclose(fpu);
	fclose(tm);
	if (flag == 0) {
		printf(" User not found ");
	}
	int r;
	r = remove("userData.txt");
	r = rename("Temporary.txt", "userData.txt");
}

