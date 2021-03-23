#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <conio.h>
#include <stdio.h>
#include <string.h>
#define MAX 15

struct date {
	int d, m, y;
};

struct timings {
	int h, m;
};

struct user {
	char name[60], email[80], gender;
	int age, mobileno[10], user_id;
};

struct movie {
	int movie_id, movie_price;
	char language[80], mtype[80], movieName[150];
	struct date release;
};

struct movie_seat {
	int seat_id;
	struct date d;
	struct timings t;
};

struct seating_arrangement {
	int count, mat[3][5];
};

struct hall {
	int hall_id ;
	struct timings t1, t2, t3, t4;
	struct date d;
	int m1, m2, m3, m4;
	struct seating_arrangement s1, s2, s3, s4;
};

struct sub_hall {
	int hall_id,mid;
	struct timings t;
	struct date d;
	struct seating_arrangement s;
};

struct booking {
	int booking_id, user_id, movie_id, hall_id;
	struct date d;		//booking date
	struct timings t;	//booking time 
	int noOfSeats;				//number of seats booked
	struct movie_seat seatno[MAX];
	int bookingCost;
};

/*Main Functions*/
int userType();
void admin();
void login();
void customer();

/*Heading*/
void heading(int i);

/*Misc Functions*/
void invalidOption();
void endingProgram();
void fileNotFound();
void calDateTime(struct timings* t, struct date *d);

/*Admin Functions*/
void MovieOperations();
void HallOperations();
void UserFunctions();
void UpdateHallOperations();
void BookingOperations();

/*Movie Functions*/
struct movie getMovie();
struct movie readMovieFromFile(FILE* fpm);
void displayMovie(struct movie m);
void writeToFile(FILE* fpm, struct movie m);
struct movie findMovieById(int id);
void addMovie();
void viewAllMovie();
void viewMovie();
void deleteMovie();
void updateMovie();
void viewAllMovieHistory();
void viewAllAvailableMovie();
void viewMovieStatus();
struct movie getMovieIdForBooking();

/*Hall Functions*/
struct hall getHall();
void displayHall(struct hall h);
void writeToHallFile(FILE* fph, struct hall h);
struct hall readHallFromFile(FILE* fph);
void displayAvailableMovieHall(struct hall h);
void addHall();
void viewHall();
void viewAllHall();
void viewAllAvailableHall();
void updateHall();
void deleteHall();
void displayAvailableHallMovie( struct timings t, int count, struct date d);
void viewAvailableHallOfMovie(int mid,struct sub_hall sub[10],int *count);
struct sub_hall assignHallToSubHall(int hid, int mid, struct date d, struct timings t, struct seating_arrangement s);
void getHallForBooking(int mid, struct sub_hall* subhall);
struct seating_arrangement assignSeatingArrangement(int hid, int mid, struct date d, struct timings t);

/*seat*/
int totalAvailableSeatsOfMovie(int movie_id);
void viewSeatingArrangment(int mat[3][5]);
void viewAvailableSeats(int h_id, int m_id, struct date d);
void viewAvailableSeatHallMovie();
int seatInSeatMatrix(int mat[3][5], int seat);
int SeatAvailable(int hall_id, struct date d, struct timings t, int seatNo);
void bookSeat(int mat[][5], int seat,int val);
void updateSeatMatrixAfterBooking(struct movie_seat s, int hall_id);
struct movie_seat addSeat(int hall_id, struct date dt, struct timings t);
void showBookedSeats(struct movie_seat* seat, int n);
void viewSeat(struct movie_seat *seat,int n);
int SearchSeatNo(struct movie_seat* seat, int n, int id);
void removeSeat(struct movie_seat* seat, int** n, int status);
void updateSeatMatrixAfterDelete(struct movie_seat s, int hall_id);
void deleteSeat(struct movie_seat* seat, int* n, int hall_id);
void sortSeatArray(struct movie_seat* seat, int n);
void swap(int* xp, int* yp);
void getSeatBooked(int* n, struct movie_seat* seat, struct sub_hall subhall, int mid);
void viewAvailableSeatsForBooking(int h_id, int m_id, struct date d, struct timings t);

/*User*/
struct user getUser(int id);
void displayUser(struct user u);
struct user readFromUserFile(FILE* fpu);
void writeToUserFile(FILE* fpu, struct user u);
int isUser(struct user* u);
struct user loginUser();
struct user addUser();
void viewAllUser();
void viewMovieUser();
void findUser();
void viewUserBooking();
void updateUser();
void deleteUser();
struct user findUserById(int id);

/*Booking*/
struct movie MovieBooking();
int calBookingCost(int perCost, int noOfSeats);
struct booking getBooking(int uid);
void displayBooking(struct booking b);
void writeToBookingFile(FILE* fpb, struct booking b);
struct booking readFromBookingFile(FILE* fpb);
void generateBookingID(struct booking* b);
struct user loginOrRegisterUser();
void addBooking(struct user u);
void viewAllBooking();
void viewBooking(struct user u);
void viewUserAllBookings(struct user u);
void updateBooking(struct user u);
void deleteBooking(struct user u);
void updateHallId_Bookings(struct hall h, int now);
void refundOfBookings(int hid, struct date d, struct timings t,struct hall *h);
void viewInRefundBooking(struct user u, struct booking temp);
void viewHallBookingDateTime(int hid, struct date d, struct timings t);
void viewMovieBookingDate(int mid, struct date d);
void callViewMovieBookingDate();
void callViewHallBookingDateTime();
void callViewUserAllBookings();


#endif