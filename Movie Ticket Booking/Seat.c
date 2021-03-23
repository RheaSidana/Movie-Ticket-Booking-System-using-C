#include "myHeader.h"
#include <stdio.h>

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
				else count += h.s1.count;
			}
			if (h.m2 == movie_id) {
				if (count == -1)count = h.s2.count;
				else count += h.s2.count;
			}
			if (h.m3 == movie_id) {
				if (count == -1)count = h.s3.count;
				else count += h.s3.count;
			}
			if (h.m4 == movie_id) {
				if (count == -1)count = h.s4.count;
				else count += h.s4.count;
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
			if (mat[i][j] != 0) {
				printf("   %d%d   ", row, col);
			}
			else {
				printf("   %d%d*  ", row, col);
			}
		}
		printf("\n");
	}
}

void viewAvailableSeats(int h_id, int m_id, struct date d) {
	printf("\n Printing the Hall Details ");
	FILE* fph;
	fph = fopen("HallData.txt", "r");
	if (fph == NULL) fileNotFound();
	else {
		struct hall h;
		while (!feof(fph)) {
			h = readHallFromFile(fph);
			if (h.hall_id == h_id && h.d.d==d.d && h.d.m==d.m && h.d.y==d.y ) {
				int count = 0;
				int t = 0;
				if (h.m1 == m_id) {
					count++;
					t = 1;
					printf("\n  1. Timing : %02d:%02d-%02d:%02d", h.t1.h, h.t1.m, h.t2.h, h.t2.m);
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
					printf("\n  4. Timing : %02d:%02d-%02d:%02d", h.t4.h, h.t4.m, h.t4.h + 3, h.t4.m);
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

int seatInSeatMatrix(int mat[3][5], int seat) {
	int i, j, no;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			no = ((i + 1) * 10) + (j + 1);
			if (no == seat) {
				if (mat[i][j] == 0)
					return 1;
			}
		}
	}
	return 0;
}

int SeatAvailable(int hall_id, struct date d, struct timings t, int seatNo) {
	int confirm=0;
	FILE* fph;
	fph = fopen("HallData.txt", "r");
	if (fph == NULL) fileNotFound();
	else {
		struct hall h;
		while (!feof(fph)) {
			h = readHallFromFile(fph);
			if (h.hall_id == hall_id && h.d.d == d.d && h.d.m == d.m && h.d.y == d.y) {
				if (h.t1.h == t.h) {
					confirm=seatInSeatMatrix(h.s1.mat, seatNo);
					break;
				}
				else if (h.t2.h == t.h) {
					confirm = seatInSeatMatrix(h.s2.mat, seatNo);
					break;
				}
				else if (h.t3.h == t.h) {
					confirm = seatInSeatMatrix(h.s3.mat, seatNo);
					break;
				}
				else if (h.t4.h == t.h) {
					confirm = seatInSeatMatrix(h.s4.mat, seatNo);
					break;
				}
			}
		}
	}
	fclose(fph);
	return confirm;
}

void bookSeat(int mat[][5], int seat,int val) {
	int no;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			no = ((i + 1) * 10) + (j + 1);
			if (no == seat) {
				mat[i][j] = val;
				return;
			}
		}
	}
}

void updateSeatMatrixAfterBooking(struct movie_seat s, int hall_id) {
	int r;
	FILE* fph, * tm;
	fph = fopen("HallData.txt", "r");
	tm = fopen("temporary.txt", "a");
	if (fph == NULL || tm == NULL) fileNotFound();
	else {
		struct hall h;
		while (!(feof(fph))) {
			h = readHallFromFile(fph);
			if (h.hall_id == hall_id && h.d.d==s.d.d && h.d.m==s.d.m && h.d.y==s.d.y) {
				if (h.t1.h == s.t.h) {
					bookSeat(h.s1.mat,s.seat_id,1);
					h.s1.count--;
				}
				else if (h.t2.h == s.t.h) {
					bookSeat(h.s2.mat, s.seat_id,1);
					h.s2.count--;
				}
				else if (h.t3.h == s.t.h) {
					bookSeat(h.s3.mat, s.seat_id,1);
					h.s3.count--;
				}
				else if (h.t4.h == s.t.h) {
					bookSeat(h.s4.mat, s.seat_id,1);
					h.s4.count--;
				}
			}
			writeToHallFile(tm, h);
		}
	}
	fclose(fph);
	fclose(tm);
	r = remove("HallData.txt");
	r = rename("temporary.txt", "HallData.txt");
}

struct movie_seat addSeat(int hall_id,struct date dt,struct timings t) {
	struct movie_seat seat;
	seat.seat_id = 0;
	int seatNo;
	do {
		printf("\nEnter the seat number : \n");
		scanf_s("%d", &seatNo);
		int isSeat = 0;
		isSeat = SeatAvailable(hall_id, dt, t, seatNo);
		if (isSeat == 1) {
			seat.seat_id = seatNo;
			seat.d.d = dt.d;
			seat.d.m = dt.m;
			seat.d.y = dt.y;
			seat.t.h = t.h;
			seat.t.m = t.m;
			printf("\n Seat Added \n");
			updateSeatMatrixAfterBooking(seat, hall_id);
			break;
		}
		else {
			printf("\n Seat Already Booked \n");
		}
	} while (1);
	return seat;
}

void showBookedSeats(struct movie_seat *seat,int  n) {
	printf("\n Displaying your booked ticket according to the Hall Seating arrangement \n");
	int i=0;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 5; k++) {
				int no = ((j + 1) * 10) + (k + 1);
				if (no == seat[i].seat_id) {
					printf("   %d*   ",no);
					if(i<n)i++;
				}
				else {
					printf("   %d    ", no);
				}
			}
			printf("\n");
		}
}

void viewSeat(struct movie_seat *seat,int n) {
	showBookedSeats(seat, n);
}

int SearchSeatNo(struct movie_seat * seat,int n,int id) {
	int beg = 0, mid,len=n-1;
	if (id<seat[beg].seat_id || id>seat[len].seat_id)return -1;
	if (id == seat[beg].seat_id)return beg;
	if (id == seat[len].seat_id)return len;
	while(beg<=len){
		mid = (beg + len) / 2;
		if (id > seat[beg].seat_id && id < seat[mid].seat_id) {
			len = mid - 1;
		}
		else if (id > seat[mid].seat_id && id < seat[len].seat_id)
		{
			beg = mid + 1;
		}
		else if (seat[mid].seat_id == id)
		{
			return mid;
		}
		else break;
	}
	return -1;
}

void removeSeat(struct movie_seat *seat,int **n,int status) {
	if (status != (**n - 1)) {
		for (int i = status; i <(**n - 1); i++) {
			seat[i].seat_id = seat[i + 1].seat_id;
		}
	}
	**n = **n - 1;
}

void updateSeatMatrixAfterDelete(struct movie_seat s,int hall_id){
	int r,val=0;
	FILE* fph, * tm;
	fph = fopen("HallData.txt", "r");
	tm = fopen("temporary.txt", "a");
	if (fph == NULL || tm == NULL) fileNotFound();
	else {
		struct hall h;
		while (!(feof(fph))) {
			h = readHallFromFile(fph);
			if (h.hall_id == hall_id && h.d.d == s.d.d && h.d.m == s.d.m && h.d.y == s.d.y) {
				if (h.t1.h == s.t.h) {
					bookSeat(h.s1.mat, s.seat_id, val);
					h.s1.count++;
				}
				else if (h.t2.h == s.t.h) {
					bookSeat(h.s2.mat, s.seat_id, val);
					h.s2.count++;
				}
				else if (h.t3.h == s.t.h) {
					bookSeat(h.s3.mat, s.seat_id, val);
					h.s3.count++;
				}
				else if (h.t4.h == s.t.h) {
					bookSeat(h.s4.mat, s.seat_id, val);
					h.s4.count++;
				}
			}
			writeToHallFile(tm, h);
		}
	}
	fclose(fph);
	fclose(tm);
	r = remove("HallData.txt");
	r = rename("temporary.txt", "HallData.txt");
}

void deleteSeat(struct movie_seat *seat,int *n,int hall_id) {
	char ans;
	int i = 0,id;
	if (*n == 1)removeSeat(seat, &n, 0);
	else {
		do {
			/*
			printf("\n");
			for (int k = 0; k < *n; k++) {
				printf("%d ",seat[k].seat_id);
			}*/
			viewSeat(seat, *n);
			printf("Enter the seat number you want to delete.\n");
			scanf_s("%d", &id);
			int status = SearchSeatNo(seat,*n,id);
			if (status != -1) {
				struct movie_seat seatRemoved = seat[status];
				removeSeat(seat, &n, status);
				printf("\n Seat Deleted \n");
				updateSeatMatrixAfterDelete(seatRemoved, hall_id);
			}
			else {
				printf("\n This Seat is not Booked by you. \n");
				break;
			}
			int x = getchar();
			printf("\n Do you want to delete more? (y/n) ");
			scanf_s("%c", &ans, 1);
			if (ans == 'n' || ans == 'N')break;
		} while (*n > 1);
	}
}

void sortSeatArray(struct movie_seat* seat, int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) 
		for (j = 0; j < n - i - 1; j++)
			if (seat[j].seat_id > seat[j + 1].seat_id)
				swap(&seat[j].seat_id, &seat[j + 1].seat_id);
}

void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void getSeatBooked(int* n, struct movie_seat* seat,struct sub_hall subhall,int mid) {
	do {
		char ans;
		viewAvailableSeatsForBooking(subhall.hall_id, mid, subhall.d,subhall.t);
		seat[*n] = addSeat(subhall.hall_id, subhall.d, subhall.t);
		*n+=1;
		int x = getchar();
		printf("\n Do you want to enter more?(y/n) ");
		scanf_s("%c", &ans, 1);
		if (ans == 'n' || ans == 'N')break;
	} while (1);
}

void viewAvailableSeatsForBooking(int h_id, int m_id, struct date d, struct timings t) {
	FILE* fph;
	fph = fopen("HallData.txt", "r");
	if (fph == NULL) fileNotFound();
	else {
		struct hall h;
		while (!feof(fph)) {
			h = readHallFromFile(fph);
			if (h.hall_id == h_id && h.d.d == d.d && h.d.m == d.m && h.d.y == d.y) {
				if (h.t1.h == t.h) {
					printf("\n  Total Seats Available : %d", h.s1.count);
					viewSeatingArrangment(h.s1.mat);
				}
				else if (h.t2.h == t.h) {
					printf("\n  Total Seats Available : %d", h.s2.count);
					viewSeatingArrangment(h.s2.mat);
				}
				else if (h.t3.h == t.h) {
					printf("\n  Total Seats Available : %d", h.s3.count);
					viewSeatingArrangment(h.s3.mat);
				}
				else if (h.t4.h == t.h) {
					printf("\n  Total Seats Available : %d", h.s4.count);
					viewSeatingArrangment(h.s4.mat);
				}
			}
		}
	}
	fclose(fph);
}


