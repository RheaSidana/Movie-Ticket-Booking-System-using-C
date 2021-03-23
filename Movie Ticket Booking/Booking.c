#include "myHeader.h"
#include <stdio.h>

/*
File : Booking.txt
Refund File : BookingRefund.txt
*/

int calBookingCost(int perCost, int noOfSeats)
{
	return (perCost * noOfSeats);
}

void generateBookingID(struct booking* b) {
	struct booking book;
	book.booking_id = 0;
	FILE* fpb;
	fpb = fopen("Booking.txt", "a");
	if (fpb == NULL) fileNotFound();
	else {
		fseek(fpb, 0, SEEK_END);
		int size = ftell(fpb);
		if (size != 0) {
			FILE* fpb2;
			fpb2 = fopen("Booking.txt", "r");
			while (!feof(fpb2)) {
				book = readFromBookingFile(fpb2);
			}
			fclose(fpb2);
		}
		b->booking_id = book.booking_id+1;
	}
	fclose(fpb);
	//printf("\n Booking ID : %d-%d-%d-%d",b->booking_id,b->movie_id,b->hall_id,b->user_id);
}

void extractBookingID(struct booking* temp) {
	char bookingID[20] = { '\0' };
	int count = 0;
	//struct booking temp;
	temp->booking_id = 0;
	temp->movie_id = 0;
	temp->hall_id = 0;
	printf("\n Enter the Booking ID : ");
	gets(bookingID);
	for (int i = 0; bookingID[i] != '\0'; i++) {
		if (bookingID[i] == '-') {
			count++;
			continue;
		}
		if (bookingID[i] != '-' && count == 0) {
			temp->booking_id = temp->booking_id * 10 + (int)bookingID[i] - (int)'0';
		}
		else if (bookingID[i] != '-' && count == 1) {
			temp->movie_id = temp->movie_id * 10 + (int)bookingID[i] - (int)'0';
		}
		else if (bookingID[i] != '-' && count == 2) {
			temp->hall_id = temp->hall_id * 10 + (int)bookingID[i] - (int)'0';
		}
	}
}

struct movie MovieBooking() {
	struct movie m;
	while (1) {
		m = getMovieIdForBooking();
		displayMovie(m);
		char ans;
		int x = getchar();
		printf("\n Do you want to book tickets for this movie? (y/n) \n");
		scanf_s("%c", &ans, 1);
		if (ans == 'y' || ans == 'Y')break;
	}
	return m;
}

struct booking getBooking(int uid){
	struct booking b;
	struct movie m; 
	m.movie_id = 0;
	m = MovieBooking();

	b.user_id = uid;
	b.movie_id = m.movie_id;
	
	//select hall according to movie, time and date
	//create array of sub_hall 
	//choose the appropriate sub_hall 
	//return the particular sub_hall
	struct sub_hall subhall;
	subhall.hall_id = 0;
	getHallForBooking(b.movie_id, &subhall);
	 
	b.hall_id = subhall.hall_id;

	b.noOfSeats = 0;
	getSeatBooked(&b.noOfSeats,b.seatno,subhall,b.movie_id);
	
	b.bookingCost = calBookingCost(m.movie_price, b.noOfSeats);

	calDateTime(&b.t, &b.d);
	generateBookingID(&b);

	sortSeatArray(b.seatno, b.noOfSeats);
	return b;
}

void displayBooking(struct booking b){
	printf("\n Displaying Booking Details: ");
	printf("\n 1.  Booking ID                : %d-%d-%d-%d", b.booking_id, b.movie_id, b.hall_id, b.user_id);
	printf("\n 2.  Booking User              : %d", b.user_id);
	struct movie m = findMovieById(b.movie_id);
	printf("\n 3.  Booking Movie             : %s", m.movieName);
	printf("\n 4.  Booking Hall Number       : %d", b.hall_id);
	printf("\n 5.  Booking Date              : %d-%d-%d", b.d.d,b.d.m,b.d.y);
	printf("\n 6.  Booking Time              : %02d:%02d", b.t.h, b.t.m);
	printf("\n 7.  Booking Number of Seats   : %d", b.noOfSeats);
	printf("\n 8.  Booking Seat Numbers      : ");
	for (int i = 0; i < b.noOfSeats; i++) {
		printf("%d ", b.seatno[i].seat_id);
	}
	printf("\n 9.  Movie Date                : %d-%d-%d", b.seatno[0].d.d, b.seatno[0].d.m, b.seatno[0].d.y);
	printf("\n 10. Movie Time                : %02d:%02d", b.seatno[0].t.h, b.seatno[0].t.m);
	printf("\n 11. Booking Cost              : %d\n", b.bookingCost);
}

void writeToBookingFile(FILE* fpb,struct booking b){
	fprintf(fpb, "%d %d %d %d",b.booking_id,b.user_id,b.movie_id,b.hall_id);
	fprintf(fpb, " %d \n%d %d %d ", b.bookingCost,b.d.d,b.d.m,b.d.y);
	fprintf(fpb, "%d %d ", b.t.h, b.t.m);
	fprintf(fpb, "%d \n", b.noOfSeats);
	fprintf(fpb, "%d %d %d ",b.seatno[0].d.d, b.seatno[0].d.m, b.seatno[0].d.y);
	fprintf(fpb, "%d %d ", b.seatno[0].t.h, b.seatno[0].t.m);
	for (int i = 0; i < b.noOfSeats; i++) {
		fprintf(fpb, "%d ", b.seatno[i].seat_id);
	}
	fprintf(fpb, "\n");
}

struct booking readFromBookingFile(FILE* fpb){
	struct booking b;
	fscanf(fpb, "%d %d %d %d", &b.booking_id, &b.user_id, &b.movie_id, &b.hall_id);
	fscanf(fpb, " %d \n%d %d %d ", &b.bookingCost, &b.d.d, &b.d.m, &b.d.y);
	fscanf(fpb, "%d %d ", &b.t.h, &b.t.m);
	fscanf(fpb, "%d \n", &b.noOfSeats);
	fscanf(fpb, "%d %d %d ", &b.seatno[0].d.d, &b.seatno[0].d.m, &b.seatno[0].d.y);
	fscanf(fpb, "%d %d ", &b.seatno[0].t.h, &b.seatno[0].t.m);
	for (int i = 0; i < b.noOfSeats; i++) {
		fscanf(fpb, "%d ", &b.seatno[i].seat_id);
		b.seatno[i].d = b.seatno[0].d;
		b.seatno[i].t = b.seatno[0].t;
	}
	fscanf(fpb, "\n");
	return b;
}

/*
  1. parameter : user
  2. search movie 
  3. search hall according to the number of seats the user want to book
  4. select hall
  5. select the seat numbers you want to book
  6. confirm booking
  7. display booking id (Hall-Movie-date-time-User-BNO)
*/
void addBooking(struct user u) {
	struct booking b;
	b.booking_id = 0;
	b = getBooking(u.user_id);
	displayBooking(b);
	
	FILE* fpb;
	fpb = fopen("Booking.txt", "a");
	if (fpb == NULL) fileNotFound();
	else {
		writeToBookingFile(fpb, b);
	}
	fclose(fpb);
}

void viewBooking(struct user u) {
	struct booking temp;
	temp.booking_id = 0;
	extractBookingID(&temp);
	
	struct booking b;
	int flag = 0;
	FILE* fpb;
	fpb = fopen("Booking.txt", "r");
	if (fpb == NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			if (b.booking_id == temp.booking_id && b.user_id == u.user_id && b.movie_id==temp.movie_id && b.hall_id==temp.hall_id)
			{
				flag = 1;
				displayBooking(b);
				break;
			}
		}
	}
	if (flag == 0) {
		printf("\n Booking Not Found \n");
		viewInRefundBooking(u, temp);
	}
	fclose(fpb);
}

void updateBooking(struct user u) {
	struct booking temp;
	temp.booking_id = 0;
	extractBookingID(&temp);

	struct booking b;
	int flag = 0;
	FILE* fpb,*tm;
	fpb = fopen("Booking.txt", "r");
	tm= fopen("BookingTemp.txt", "a");
	if (fpb == NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			if (b.booking_id == temp.booking_id && b.user_id == u.user_id && b.movie_id == temp.movie_id && b.hall_id == temp.hall_id)
			{
				flag = 1;
				int ch,n;
				struct movie m;
				m.movie_id = 0;
				m = findMovieById(b.movie_id);
				struct sub_hall subhall;
				subhall.hall_id = b.hall_id;
				subhall.d = b.seatno[0].d;
				subhall.mid = b.movie_id;
				subhall.t = b.seatno[0].t;
				//assign seat arrangement to subhall
				subhall.s = assignSeatingArrangement(subhall.hall_id, subhall.mid, subhall.d, subhall.t);
				printf("\n\n Enter your choice : (Booking) \n ");
				printf("1. Add seat \n 2. Delete seat \n ");
				scanf_s("%d", &ch);
				switch (ch) {
				case 1:
					n = b.noOfSeats;
					getSeatBooked(&b.noOfSeats, b.seatno, subhall, b.movie_id);
					n = b.noOfSeats - n;
					n = calBookingCost(m.movie_price, n);
					printf(" \n Booking Cost (of currently added seats) : %d \n",n);
					b.bookingCost += n;
					calDateTime(&b.t, &b.d);
					sortSeatArray(b.seatno, b.noOfSeats);
					break;
				case 2:
					/*
					step 1 : remove the seat no 
					step 2 : cal booking cost and assign booking cost
					3: cal date time and sort seatno
					*/
					n = b.noOfSeats;
					deleteSeat(b.seatno, &b.noOfSeats, b.hall_id);
					n -= b.noOfSeats;
					n = calBookingCost(m.movie_price, n);
					printf(" \n Booking Cost (of currently deleted seats) : %d \n", n);
					b.bookingCost -= n;
					calDateTime(&b.t, &b.d);
					sortSeatArray(b.seatno, b.noOfSeats);
					break;
				default:
					break;
				}
				displayBooking(b);
			}
			writeToBookingFile(tm, b);
		}
	}
	if (flag == 0) {
		printf("Booking Not Found ");
	}
	fclose(fpb);
	fclose(tm);
	int r;
	r = remove("Booking.txt");
	r = rename("BookingTemp.txt", "Booking.txt");
}

/*
1: search booking 
2: confirm delete 
3: initiate refund 
4: don't add the deleting booking in the temp file 
*/
void deleteBooking(struct user u) {
	struct booking temp;
	temp.booking_id = 0;
	extractBookingID(&temp);
	
	struct booking b;
	int flag = 0, confirm = 0;
	FILE* fpb, * tm;
	fpb = fopen("Booking.txt", "r");
	tm = fopen("BookingTemp.txt", "a");
	if (fpb == NULL || tm==NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			if (b.booking_id == temp.booking_id && b.user_id == u.user_id && b.movie_id == temp.movie_id && b.hall_id == temp.hall_id)
			{
				flag = 1;
				char ans;
				printf("Are you sure you want to delete the booking ?(y/n) \n");
				scanf_s("%c", &ans, 1);
				if (ans == 'y' || ans == 'Y') {
					displayBooking(b);
					confirm = 1;
					printf("\n Booking Cost %d refund initiated \n",b.bookingCost);
					for (int i = 0; i < b.noOfSeats; i++) {
						updateSeatMatrixAfterDelete(b.seatno[i], b.hall_id);
					}
				}
			}
			if(confirm==0){
				writeToBookingFile(tm, b);
			}
			confirm = 0;
		}
	}
	if (flag == 0) {
		printf("Booking Not Found ");
	}
	fclose(fpb);
	fclose(tm);
	int r;
	r = remove("Booking.txt");
	r = rename("BookingTemp.txt", "Booking.txt");
}

void viewAllBooking() {
	heading(1);
	struct booking b;
	FILE* fpb;
	fpb = fopen("Booking.txt", "r");
	if (fpb == NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			displayBooking(b);
		}
	}
	fclose(fpb);
}
/*
1:hall -> id date time 
2:search all booking of the hall in accordance with the date and time 
3: delete and print UserID bookingID Refund 
*/
//add one more parameter as whole hall using pointers 
//and timeSlot number 
void refundOfBookings(int hid,struct date d,struct timings t,struct hall *h) {
	struct user u;
	u.user_id = 0;
	struct booking b;
	b.booking_id = 0;
	FILE* fpb,*tm,*fprb;
	fpb = fopen("Booking.txt", "r");
	tm = fopen("BookingTemp.txt", "a");
	fprb = fopen("BookingRefund.txt", "a");
	if (fpb == NULL || tm==NULL || fprb==NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			if (b.hall_id == hid && b.seatno[0].t.h == t.h && b.seatno[0].d.d == d.d && b.seatno[0].d.m == d.m && b.seatno[0].d.y == d.y) {
				writeToBookingFile(fprb, b);
				displayBooking(b);
				if (h->t1.h == t.h) {
					for (int i = 0; i < b.noOfSeats; i++) {
						bookSeat(h->s1.mat, b.seatno[i].seat_id, 0);
						h->s1.count++;
					}
				}
				else if (h->t2.h == t.h) {
					for (int i = 0; i < b.noOfSeats; i++) {
						bookSeat(h->s2.mat, b.seatno[i].seat_id, 0);
						h->s2.count++;
					}
				}
				else if (h->t3.h == t.h) {
					for (int i = 0; i < b.noOfSeats; i++) {
						bookSeat(h->s3.mat, b.seatno[i].seat_id, 0);
						h->s3.count++;
					}
				}
				else if (h->t4.h == t.h) {
					for (int i = 0; i < b.noOfSeats; i++) {
						bookSeat(h->s4.mat, b.seatno[i].seat_id, 0);
						h->s4.count++;
					}
				}
			}
			else {
				if(b.booking_id>0)
				writeToBookingFile(tm, b);
			}
		}
	}
	fclose(fpb);
	fclose(tm);
	int r;
	r = remove("Booking.txt");
	r = rename("BookingTemp.txt", "Booking.txt");
}

void viewInRefundBooking(struct user u, struct booking temp) {
	struct booking b;
	int flag = 0;
	FILE* fprb;
	fprb = fopen("BookingRefund.txt", "r");
	if (fprb == NULL) fileNotFound();
	else {
		while (!feof(fprb)) {
			b = readFromBookingFile(fprb);
			if (b.booking_id == temp.booking_id && b.user_id == u.user_id && b.movie_id == temp.movie_id && b.hall_id == temp.hall_id)
			{
				flag = 1;
				printf("\n\n Booking Found in Refund: \n (Hall details updated)\n");
				displayBooking(b);
				printf("\n\n Booking Cost %d refund initiated \n", b.bookingCost);
				break;
			}
		}
	}
	fclose(fprb);
}

void updateHallId_Bookings(struct hall h, int now) {
	struct booking b;
	int flag = 0, confirm = 0;
	FILE* fpb, * tm;
	fpb = fopen("Booking.txt", "r");
	tm = fopen("BookingTemp.txt", "a");
	if (fpb == NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			if (b.hall_id == h.hall_id && b.seatno[0].d.d==h.d.d && b.seatno[0].d.m == h.d.m && b.seatno[0].d.y == h.d.y ) {
				b.hall_id = now;
			}
			writeToBookingFile(tm, b);
		}
	}
	fclose(fpb);
	fclose(tm);
	int r;
	r = remove("Booking.txt");
	r = rename("BookingTemp.txt", "Booking.txt");
}

void viewUserAllBookings(struct user u) {
	struct booking b;
	FILE* fpb;
	fpb = fopen("Booking.txt", "r");
	if (fpb == NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			if(b.user_id==u.user_id)
				displayBooking(b);
		}
	}
	fclose(fpb);
}

void viewMovieBookingDate(int mid, struct date d) {
	struct booking b;
	FILE* fpb;
	fpb = fopen("Booking.txt", "r");
	if (fpb == NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			if (b.movie_id == mid && b.seatno[0].d.d == d.d && b.seatno[0].d.m == d.m && b.seatno[0].d.y == d.y) {
				displayBooking(b);
			}
		}
	}
	fclose(fpb);
}

void viewHallBookingDateTime(int hid, struct date d, struct timings t) {
	struct booking b;
	FILE* fpb;
	fpb = fopen("Booking.txt", "r");
	if (fpb == NULL) fileNotFound();
	else {
		while (!feof(fpb)) {
			b = readFromBookingFile(fpb);
			if (b.hall_id == hid && b.seatno[0].t.h == t.h && b.seatno[0].d.d == d.d && b.seatno[0].d.m == d.m && b.seatno[0].d.y == d.y) {
				displayBooking(b);
			}
		}
	}
	fclose(fpb);
}


void callViewMovieBookingDate() {
	heading(1);
	int mid;
	struct date d;
	printf("\n Enter the Movie Id: ");
	scanf_s("%d", &mid);
	printf("\n Enter the date (dd/mm/yyyy) : ");
	scanf_s("%d%d%d", &d.d, &d.m, &d.y);
	viewMovieBookingDate(mid,d);
}

void callViewHallBookingDateTime() {
	heading(1);
	int hid;
	struct date d;
	struct timings t;
	printf("\n Enter the Hall Id: ");
	scanf_s("%d", &hid);
	printf("\n Enter the Date (dd/mm/yyyy) : ");
	scanf_s("%d%d%d", &d.d, &d.m, &d.y);
	printf("\n Enter the Time (hh:mm) : ");
	scanf_s("%d%d", &t.h, &t.m);
	viewHallBookingDateTime(hid,d,t);
}

void callViewUserAllBookings() {
	heading(1);
	struct user u;
	printf("\n Enter the User Id : ");
	scanf_s("%d", &u.user_id);
	viewUserAllBookings(u);
}