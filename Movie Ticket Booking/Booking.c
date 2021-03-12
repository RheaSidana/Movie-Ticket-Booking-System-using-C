#include "myHeader.h"
#include <stdio.h>

/*
File : ticketBooking.txt
*/

void generateBookingID(struct booking* b) {
	
}

struct booking getBooking(){
	struct booking b;
	generateBookingID(&b);
	return b;
}

void displayBooking(struct booking b){
	
}

void writeToBookingFile(FILE* fpb,struct booking b){
	
}

struct booking readFromBookingFile(FILE* fpb){
	struct booking b;
	b.b_id = 0;
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
void addBooking() {

}

void viewBooking() {

}

void updateBooking() {

}

void deleteBooking() {

}

void viewAllBooking() {

}

void refundOfBookings() {

}


