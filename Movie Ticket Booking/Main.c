#include "myHeader.h"
#include <stdlib.h>

void start() {
	int user_type = userType();
	switch (user_type)
	{
	case 1:admin();
		break;
	case 2: customer();
		break;
	case 3:endingProgram();
		exit(0);
		break;
	default: invalidOption();
		int m = _getch();
		break;
	}
}

int main() {
	//start();

	//testing first

	//movie
	//updateMovie();
	//addMovie();
	//viewAllMovie();
	//viewMovie();
	//deleteMovie();
	//viewAllMovieHistory();

	//hall
	//addHall();
	//viewHall();
	//viewAllHall();
	//viewAllAvailableHall();
	//viewAllAvailableMovie();
	//updateHall(); //not fully completed 
	//deleteHall();  //not fully completed 
	//viewMovieStatus();
	//viewAvailableSeats();
	//viewAvailableSeatHallMovie();

	//user
	//writeToUserFile(fpu, u);
	//addUser(); 
	//viewAllUser(); 
	//findUser();
	//struct user u = loginUser();
	//updateUser();
	//deleteUser();
	struct user u= loginOrRegisterUser();

}