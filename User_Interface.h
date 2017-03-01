#include "Polynomial.h"
#include <iostream>
#include <string>
#include <limits>

using std::cout;
using std::cin;
using std::string;

class User_Interface{
public:
	void menu_process(){
		string commands[] = {
			"", // menu starts at 1
			"Add Polynomial",
			"Display Result",
			"Clear Inputs",
			"Exit" };
		const size_t MENU_CHOICES = 5;
		char choice = '0';
		do{
			for (size_t i = 1; i < MENU_CHOICES; i++){
				cout << "Select: " << i << " " << commands[i] << "\n";
			}
			cout << "_________________\n";
			cout << "Enter selection : ";
			cin >> choice;
			cout << "_________________________________\n";
			cin.ignore(INT_MAX, '\n');
			cin.clear();
			switch (choice) {
			case '1': do_add_poly(); break;
			case '2': do_display_poly(); break;
			case '3': do_clear_inputs(); break;
			case '4': break;
			default: cout << "Please try again.\n"; 
			}
		} while (choice != '4'); // loop menu choices until Exit requested
	}	

	void do_add_poly(){		
		
		try
		{
			
			while (user_poly_input.empty()){
				cout << "Please use the following format with no spaces or nested expressions:  3X^3-X^2+1 \n";
				cout << "Enter polynomial: ";
				getline(cin, user_poly_input);

				//  initial error checking:  validating input
				if ((user_poly_input.find_first_not_of("0123456789-+^X", 0) < user_poly_input.size()
					|| user_poly_input.at(0) == '^'
					|| user_poly_input.find("XX") < user_poly_input.size()
					|| user_poly_input.find("^X") < user_poly_input.size()
					|| user_poly_input.find("++") < user_poly_input.size()
					|| user_poly_input.find("--") < user_poly_input.size()
					|| user_poly_input.find("^^") < user_poly_input.size()
					|| user_poly_input.find("-+") < user_poly_input.size()
					|| user_poly_input.find("+-") < user_poly_input.size()
					|| user_poly_input.at(user_poly_input.size() - 1) == '^'))
				{
					cout << "<<<Invalid input. Please try again.>>> \n";
					user_poly_input.erase();
				}
			} // end while	
			
			the_polynomial.setPolynomial(user_poly_input);
			the_polynomial.createTerms();
			cout << "Polynomial added.";
			cout << "\n\n_________________________________\n";
			user_poly_input.erase();
		}				

		catch (std::exception &e)
		{
			cout << e.what();			
			do_clear_inputs();			
		}
	}

	void do_display_poly(){
		if (!the_polynomial.isEmpty()){
			the_polynomial.sortTerms();
			the_polynomial.addTerms();
			cout << "The result: ";
			the_polynomial.printTerms();
		}
		else
			cout << "No terms to display.";
		
		cout << "\n\n_________________________________\n";
	}

	void do_clear_inputs(){
		the_polynomial.clearTerms();
		cout << "Polynomial terms cleared.";
		cout << "\n\n_________________________________\n";
	}

	User_Interface(Polynomial& the_polynomial) : the_polynomial(the_polynomial){}
	
private:
	string user_poly_input;
	Polynomial the_polynomial;
};