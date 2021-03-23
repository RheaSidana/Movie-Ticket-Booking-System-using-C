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
	start();
return 0;
}