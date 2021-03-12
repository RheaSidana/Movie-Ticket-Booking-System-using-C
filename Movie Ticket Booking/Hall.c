#include "myHeader.h"
#include <stdio.h>
#include<conio.h>


/*
  file: "HallData.txt"
*/

struct hall getHall() {
	struct hall h;
	h.s1.count = h.s2.count = h.s3.count = h.s4.count = 15;
	printf("\n Enter the Hall Id: ");
	scanf_s("%d", &h.hall_id);
	//hall date init
	printf("\n Enter the Date(dd/mm/yyyy) : ");
	scanf_s("%d%d%d", &h.d.d, &h.d.m, &h.d.y);
	//hall timings 
	h.t1.h = 10; h.t1.m = 0;  //10:00 to 01:00
	h.t2.h = 1; h.t2.m = 0;	  //01:00 to 04:00
	h.t3.h = 4; h.t3.m = 0;   //04:00 to 07:00
	h.t4.h = 7; h.t4.m = 0;   //07:00 to 10:00
	//movies 
	printf("\n Enter the Movie Ids respectively : ");
	scanf_s("%d%d%d%d", &h.m1,&h.m2,&h.m3,&h.m4);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			h.s1.mat[i][j] = h.s2.mat[i][j] = h.s3.mat[i][j] = h.s4.mat[i][j] = 0;
		}
	}
	return h;
}

void displayHall(struct hall h) {
	printf("\n\n  Hall Details : ");
	printf("\n  1.Hall Id : %d ",h.hall_id );
	printf("\n  2.Date : %d-%d-%d", h.d.d, h.d.m, h.d.y);
	printf("\n  3.Hall Timings  :  \n    a. %02d : %02d - %02d : %02d \tMovie Id: %d", h.t1.h,h.t1.m,h.t1.h+3-12,h.t1.m, h.m1);
	printf("\tAvailable Seats: %d", h.s1.count);
	printf("\n    b. %02d : %02d - %02d : %02d \tMovie Id: %d", h.t2.h, h.t2.m, h.t2.h + 3 , h.t2.m, h.m2);
	printf("\tAvailable Seats: %d", h.s2.count);
	printf("\n    c. %02d : %02d - %02d : %02d \tMovie Id: %d", h.t3.h, h.t3.m, h.t3.h + 3, h.t3.m, h.m3);
	printf("\tAvailable Seats: %d", h.s3.count);
	printf("\n    d. %02d : %02d - %02d : %02d \tMovie Id: %d", h.t4.h, h.t4.m, h.t4.h + 3, h.t4.m, h.m4);
	printf("\tAvailable Seats: %d\n", h.s4.count);
	//printf("\n  3.Date : %d-%d-%d", h.d.d, h.d.m, h.d.y);
	//printf("\n  4. Movie Id : %d , %d , %d ,%d ", h.m1, h.m2, h.m3, h.m4);
}

void writeToHallFile(FILE* fph, struct hall h) {
	fprintf(fph, "%d %d %d %d %d ", h.hall_id, h.s1.count, h.s2.count, h.s3.count, h.s4.count);
	fprintf(fph, "%d %d %d %d ", h.m1,h.m2,h.m3,h.m4);
	fprintf(fph, "%d %d %d ",h.d.d,h.d.m,h.d.y);
	fprintf(fph, "\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			fprintf(fph, "%d ", h.s1.mat[i][j]);
		}
		fprintf(fph, "\n");
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			fprintf(fph, "%d ", h.s2.mat[i][j]);
		}
		fprintf(fph, "\n");
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			fprintf(fph, "%d ", h.s3.mat[i][j]);
		}
		fprintf(fph, "\n");
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			fprintf(fph, "%d ", h.s4.mat[i][j]);
		}
		fprintf(fph, "\n");
	}
	fprintf(fph, "%d %d %d %d %d %d %d %d \n",h.t1.h,h.t1.m, h.t2.h, h.t2.m, h.t3.h, h.t3.m, h.t4.h, h.t4.m);
}

struct hall readHallFromFile(FILE* fph) {
	struct hall h;
	fscanf(fph, "%d %d %d %d %d ", &h.hall_id, &h.s1.count, &h.s2.count, &h.s3.count, &h.s4.count);
	fscanf(fph, "%d %d %d %d ", &h.m1, &h.m2, &h.m3, &h.m4);
	fscanf(fph, "%d %d %d ", &h.d.d, &h.d.m, &h.d.y);
	fscanf(fph, "\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			fscanf(fph, "%d ", &h.s1.mat[i][j]);
		}
		fscanf(fph, "\n");
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			fscanf(fph, "%d ", &h.s2.mat[i][j]);
		}
		fscanf(fph, "\n");
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			fscanf(fph, "%d ", &h.s3.mat[i][j]);
		}
		fscanf(fph, "\n");
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			fscanf(fph, "%d ", &h.s4.mat[i][j]);
		}
		fscanf(fph, "\n");
	}
	fscanf(fph, "\n%d %d %d %d %d %d %d %d \n", &h.t1.h, &h.t1.m, &h.t2.h, &h.t2.m, &h.t3.h, &h.t3.m, &h.t4.h, &h.t4.m);
	return h;
}

void displayAvailableMovieHall(struct hall h) {
	struct movie m;
	printf("\n\n  Hall Details : ");
	printf("\n  1.Hall Id : %d ", h.hall_id);
	printf("\n  2.Date : %d-%d-%d", h.d.d, h.d.m, h.d.y);
	printf("\n  3.Hall Timings  :  ");
	if (h.s1.count != 0){
		printf("\n    a. %02d : %02d - %02d : %02d \tMovie Id: %d", h.t1.h, h.t1.m, h.t1.h + 3 - 12, h.t1.m, h.m1);
		printf("\tAvailable Seats: %d   ", h.s1.count);
		m = findMovieById(h.m1);
		printf(" Movie Name   : %s ", m.movieName);
	}
	if (h.s2.count != 0) {
		printf("\n    b. %02d : %02d - %02d : %02d \tMovie Id: %d", h.t2.h, h.t2.m, h.t2.h + 3, h.t2.m, h.m2);
		printf("\tAvailable Seats: %d   ", h.s2.count);
		m = findMovieById(h.m2);
		printf(" Movie Name   : %s ", m.movieName);
	}
	if (h.s3.count != 0) {
		printf("\n    c. %02d : %02d - %02d : %02d \tMovie Id: %d", h.t3.h, h.t3.m, h.t3.h + 3, h.t3.m, h.m3);
		printf("\tAvailable Seats: %d   ", h.s3.count);
		m = findMovieById(h.m3);
		printf(" Movie Name   : %s ", m.movieName);
	}
	if (h.s4.count != 0) {
		printf("\n    d. %02d : %02d - %02d : %02d \tMovie Id: %d", h.t4.h, h.t4.m, h.t4.h + 3, h.t4.m, h.m4);
		printf("\tAvailable Seats: %d   ", h.s4.count);
		m = findMovieById(h.m2);
		printf(" Movie Name   : %s ", m.movieName);
	} 
	printf("\n");
}

int totalAvailableSeatsOfMovie(int movie_id) {
	int count = -1;
	FILE* fph;
	fph = fopen("HallData.txt", "r");
	if (fph == NULL) fileNotFound();
	else {
		while (!feof(fph)) {
			struct hall h = readHallFromFile(fph);
			if (h.m1 == movie_id) {
				if (count == -1)count = h.s1.count;
				else count+= h.s1.count;
			}
			if (h.m2 == movie_id) {
				if (count == -1)count = h.s2.count;
				else count += h.s2.count;
			}
			if (h.m3 == movie_id) {
				if (count == -1)count = h.s3.count;
				else count+= h.s3.count;
			}
			if (h.m4 == movie_id) {
				if (count == -1)count = h.s4.count;
				else count+= h.s4.count;
			}
		}
	}
	fclose(fph);
	return count;
}

void viewSeatingArrangment(int mat[3][5]) {
	printf("\n  Available Seats are stared n* : \n");
	int i, j, row, col;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			row = i + 1;
			col = j + 1;
			if (mat[i][j] != 0){
				printf("   %d%d   ", row, col);
			}
			else {
				printf("   %d%d*  " , row, col);
			}
		}
		printf("\n");
	}
}

void addHall() {
	system("cls");
	heading(1);
	struct hall h = getHall();

	displayHall(h);
	
	FILE* fph;
	fph = fopen("HallData.txt", "a");
	if (fph == NULL) fileNotFound();
	else {
		writeToHallFile(fph, h);
		printf("\n\n Content added to the file.\n");
	}
	fclose(fph);
}

void viewHall() {
	FILE* fph;
	fph = fopen("HallData.txt", "r");
	if (fph == NULL) fileNotFound();
	else {
		struct hall h;
		int id;
		printf(" Enter the Hall id you want to view : ");
		scanf_s("%d", &id);

		while (!(feof(fph))) {
			h = readHallFromFile(fph);
			if ( id == h.hall_id )
			{
				displayHall(h);
				break;
			}
		}
	}
	fclose(fph);
}

void viewAllHall() {
	heading(1);
	printf("\n Printing the Hall Details ");
	FILE* fph;
	fph = fopen("HallData.txt", "r");
	if (fph == NULL) fileNotFound();
	else {
		struct hall h;
		while (!feof(fph)) {
			h = readHallFromFile(fph);
			displayHall(h);
		}
	}
	fclose(fph);
}

void viewAllAvailableHall() {
	heading(1);
	FILE* fph;
	fph = fopen("HallData.txt", "r");
	if (fph == NULL) fileNotFound();
	else {
		struct hall h;
		while (!feof(fph)) {
			h = readHallFromFile(fph);
			if (h.s1.count != 0 || h.s2.count != 0 || h.s3.count != 0 || h.s4.count != 0) {
				displayAvailableMovieHall(h);
			}
		}
	}
	fclose(fph);
}

void updateHall() {
	int ch;
	heading(1);
	FILE* fph, * tm;
	fph = fopen("HallData.txt", "r");
	tm = fopen("temporary.txt", "a");
	int flag = 0;
	if (fph == NULL || tm == NULL) fileNotFound();
	else {
		int id;
		printf("\n Enter the Hall ID you want to update : ");
		scanf_s("%d", &id);
		while (!(feof(fph))) {
			struct hall h = readHallFromFile(fph);
			if (h.hall_id == id) {
				flag = 1;
				//int val;
				displayHall(h);
				printf("\n\n Enter your choice : (HALL)\n ");
				printf("1.ID \n 2.Movie_ID 1 \n 3.Movie_ID 2 \n 4.Movie_ID 3 \n 5.Movie_ID 4 \n 6.Date \n ");
				scanf_s("%d", &ch);
				switch (ch) {
				case 1:
					printf("\n Enter the new ID: ");
					scanf_s("%d", &h.hall_id);
					break;
				case 2:
					printf("\n Enter the new Movie_ID 1: ");
					scanf_s("%d", &h.m1);
					//refund to users 
					break;
				case 3: 
					printf("\n Enter the new Movie_ID 2: ");
					scanf_s("%d", &h.m2);
					//refund to users 
					break;
				case 4: 
					printf("\n Enter the new Movie_ID 3: ");
					scanf_s("%d", &h.m3);
					//refund to users 
					break;
				case 5: 
					printf("\n Enter the new Movie_ID 4: ");
					scanf_s("%d", &h.m4);
					//refund to users 
					break;
				case 6: 
					printf("\n Enter the new Date: ");
					scanf_s("%d%d%d", &h.d.d,&h.d.m,&h.d.y);
					break;
				default: invalidOption();
					break;
				}
				printf("\n");
				displayHall(h);
			}
			writeToHallFile(tm, h);
		}
	}
	fclose(fph);
	fclose(tm);
	if (flag == 0) {
		printf(" Movie not found ");
	}
	int r;
	r = remove("HallData.txt");
	r = rename("temporary.txt", "HallData.txt");
}

void deleteHall() {
	heading(1);
	FILE* fph, * tm;
	int flag = 0;
	fph = fopen("HallData.txt", "r");
	tm = fopen("temporary.txt", "a");
	if (fph == NULL || tm == NULL) fileNotFound();
	else {
		int id;
		printf("\n Enter the hall id you want to update : ");
		scanf_s("%d", &id);
		while (!(feof(fph))) {
			struct hall h = readHallFromFile(fph);
			if (h.hall_id == id) {
				flag = 1;
				displayHall(h);
				//refund all the useers who booked the movies in this hall
				printf("\n Hall Deleted\n");
			}
			else {
				writeToHallFile(tm, h);
			}
		}
	}
	fclose(fph);
	fclose(tm);
	if (flag == 0) {
		printf("\n Hall not found \n");
	}
	int r;
	r = remove("HallData.txt");
	r = rename("temporary.txt", "HallData.txt");
}

void viewAvailableSeats(int h_id,int m_id,struct date d) {
	printf("\n Printing the Hall Details ");
	FILE* fph;
	fph = fopen("HallData.txt", "r");
	if (fph == NULL) fileNotFound();
	else {
		struct hall h;
		while (!feof(fph)) {
			h = readHallFromFile(fph);
			if (h.hall_id == h_id) {
				int count=0;
				int t=0;
				if (h.m1 == m_id) { 
					count++; 
					t = 1; 
					printf("\n  1. Timing : %02d:%02d-%02d:%02d",h.t1.h,h.t1.m, h.t2.h, h.t2.m);
				}
				if (h.m2 == m_id) {
					count++; 
					t = 2;
					printf("\n  2. Timing : %02d:%02d-%02d:%02d", h.t2.h, h.t2.m, h.t3.h, h.t3.m);
				}
				if (h.m3 == m_id) {
					count++; 
					t = 3; 
					printf("\n  3. Timing : %02d:%02d-%02d:%02d", h.t3.h, h.t3.m, h.t4.h, h.t4.m);
				}
				if (h.m4 == m_id) {
					count++; 
					t = 4; 
					printf("\n  4. Timing : %02d:%02d-%02d:%02d", h.t4.h, h.t4.m, h.t4.h+3, h.t4.m);
				}
				if (count > 1) {
					printf("\n\n  Enter the timing number : ");
					scanf_s("%d", &t);
				}
				if (t >= 1 && t <= 4) {
					if (t == 1) {
						printf("\n  Total Seats Available : %d", h.s1.count);
						viewSeatingArrangment(h.s1.mat);
					}
					else if (t == 2) {
						printf("\n  Total Seats Available : %d", h.s2.count);
						viewSeatingArrangment(h.s2.mat);
					}
					else if (t == 3) {
						printf("\n  Total Seats Available : %d", h.s3.count);
						viewSeatingArrangment(h.s3.mat);
					}
					else if (t == 4) {
						printf("\n  Total Seats Available : %d", h.s4.count);
						viewSeatingArrangment(h.s4.mat);
					}
				}
				else invalidOption();
			}
		}
	}
	fclose(fph);
}

void viewAvailableSeatHallMovie() {
	int h_id, m_id;
	struct date d;
	printf("\n Enter the Hall ID : ");
	scanf_s("%d", &h_id);
	printf("\n Enter the Movie ID : ");
	scanf_s("%d", &m_id);
	printf("\n Enter the date : ");
	scanf_s("%d%d%d", &d.d, &d.m, &d.y);
	viewAvailableSeats(h_id, m_id, d);
}

