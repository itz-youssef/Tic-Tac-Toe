#include<iostream>
#include"PTTT.h"
#include"3x3X_O.h"
#include"5x5X_O.h"
#include"BoardGame_Classes.h"
#include"WTTT.h"
#include"UTTT.h"
#include"tic_tac_toe_even_odd_7.h"
#include"connect4.h"
#include"tic_tac_toe_4x4.h"
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


void showMenu() {
    cout<< GREEN <<"||===========================||"<<endl<<RESET;
    cout << GREEN << "||========== MENU ===========||"<<endl <<RESET;
    cout<< GREEN <<"||===========================||"<<endl<< RESET;
    cout<< YELLOW << "choose a game from the following :"<< endl <<RESET;
    cout << BLUE << "  1. pyramid tic tac toe\n" << RESET;
    cout << BLUE<< "  2. four in a row \n" << RESET;
    cout << BLUE << "  3. 5x5 tic tac toe\n" << RESET;
    cout << BLUE << "  4. word tic tac toe\n" << RESET ;
    cout << BLUE <<"  5. Numerical tic tac toe\n" << RESET ;
    cout << BLUE <<"  6. misere tic tac toe\n"<< RESET ;
    cout << BLUE << "  7. 4x4 tic tac toe\n"<< RESET ;
    cout << BLUE << "  8. ultimate tic tac toe\n"<< RESET ;    
    cout << BLUE << "  9. Exit\n" << RESET ;
    cout << GREEN<< "==========================\n" << RESET;
    cout << CYAN << "Enter your choice: " << RESET ;
}

int main() {
    int choice = 0;
    while (choice != 9) {
        showMenu();
        cin >> choice;
        cin.ignore();
                
        if (choice == 1) {
            cout << GREEN << "running game 1 (pyramic tic tac toe)... \n" << RESET ;
            ui_ptt pTTT;
            pTTT.main()  ;


        } else if (choice == 2) {
            cout << GREEN << "running game 2 (3x3 inverse tic tac toe)... \n" << RESET ;
            connect_4 game2;
            game2.main();


        } else if (choice == 3) {
            cout << GREEN << "running game 3 (5x5 tic tac toe)... \n" << RESET ;
            ui5x5 x_o_main ;
            x_o_main.main()  ;               

        } else if (choice == 4) {
            cout << GREEN << "running game 4( Word tic tac toe) ...\n"<< RESET;
            ui_wtt word ;
            word.main()  ;
            


        } else if (choice == 5) {
            cout << GREEN << "running game 5( Numerical tic tac toe ...\n" << RESET ;
            numerical_TTT game5;
            game5.main();


        } else if (choice == 6) {
            cout << GREEN << "running game 6( Misere tic tac toe ...\n" << RESET;
            inverse3x3o x_o_main ;
            x_o_main.main()  ;
    


        } else if (choice == 7) {
            cout << GREEN << "running game 7( 4x4 tic tac toe ...\n" << RESET ;
            ui4x4 game7;
            game7.main();
            

        } else if (choice == 8) {
            cout << GREEN << "running game 8( Ultimate tic tac toe ...\n" << RESET ;
             ui_utt ultimate;
             ultimate.main();



        } else if (choice == 9) {
            cout << RED << "Exiting the program. Goodbye!\n" << RESET ;
        } else {
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
