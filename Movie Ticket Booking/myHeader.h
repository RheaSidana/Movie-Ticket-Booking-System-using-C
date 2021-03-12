#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <conio.h>
#include <stdio.h>
#include <string.h>
#define MAX 100

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
	int movie_id, seat_id,hall_id;
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

struct booking {
	int b_id, u_id;
	struct date d; //booking date
	struct timings t; //booking time 
	int n;
	struct movie_seat seatno[MAX];
	int bcost;
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

/*Admin Functions*/
void MovieOperations();
void HallOperations();
void UserFunctions();
void UpdateHallOperations();

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

/*Hall Functions*/
struct hall getHall();
void displayHall(struct hall h);
void writeToHallFile(FILE* fph, struct hall h);
struct hall readHallFromFile(FILE* fph);
void displayAvailableMovieHall(struct hall h);
int totalAvailableSeatsOfMovie(int movie_id);
void viewSeatingArrangment(int mat[3][5]);
void addHall();
void viewHall();
void viewAllHall();
void viewAllAvailableHall();
void updateHall();
void deleteHall();
void viewAvailableSeats(int h_id, int m_id, struct date d);
void viewAvailableSeatHallMovie();

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

/*Booking*/
struct booking getBooking();
void displayBooking(struct booking b);
void writeToBookingFile(FILE* fpb, struct booking b);
struct booking readFromBookingFile(FILE* fpb);
void generateBookingID(struct booking* b);
struct user loginOrRegisterUser();
void addBooking();
void viewBooking();
void updateBooking();
void deleteBooking();
void viewAllBooking();
void refundOfBookings();


#endif