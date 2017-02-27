#include "User_Interface.h"

int main()
{
	Polynomial the_polynomial;
	User_Interface userinterface(the_polynomial);
	userinterface.menu_process();

	return 0;
}