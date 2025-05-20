#ifndef UTTT
#define UTTT

#include "BoardGame_Classes.h"


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define GREY   "\033[30m"


template <typename T>
class UTTT_Board:public Board<T> {
public:
    UTTT_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};



class ui_utt{
public:

void main();


};

template <typename T>
class UTTT_Player : public Player<T> {
public:
    UTTT_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class UTTT_Random_Player : public RandomPlayer<T>{
public:
    UTTT_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
UTTT_Board<T>::UTTT_Board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool UTTT_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void UTTT_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {

        if(i == 0){
            cout << "\n---------------------------------------------------------------------------------------------";
        }

        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            //condition of the left side
            if(this->board[i][j] == 0 && j == 0){
                cout << " (" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
                continue;
            }
            //condition of the normal empty cell
            else if(this->board[i][j] == 0){
            cout << "  (" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
            if(j == 2 || j == 5){
                cout << "|";
            }
            }
            //condition of the non empty left sided cell
            else if(this->board[i][j] == 'X' && j == 0){
                cout << "   " << CYAN << this->board[i][j] << RESET << "    |";
            }

            else if(this->board[i][j] == 'O' && j == 0){
                cout << "   " << RED << this->board[i][j] << RESET << "    |";
            }

            //condition of the other non empty cell
            else if(this->board[i][j] == 'X'){
                cout << "    " << CYAN << this->board[i][j] << RESET << "    |";
                if(j == 2 || j ==5){
                    cout << "|";
                }
            }

            else if(this->board[i][j] == '#'){
                cout << "    " << GREY << this->board[i][j] << RESET << "    |";
                if(j == 2 || j == 5){
                    cout << "|";
                }
            }

            else{
                cout << "    " << RED << this->board[i][j] << RESET << "    |";
                if(j == 2 || j == 5){
                    cout << "|";
                }
            }
        }
        cout << "\n---------------------------------------------------------------------------------------------";
        if(i == 2 || i == 5){
            cout << "\n---------------------------------------------------------------------------------------------";
        }
    }
    cout << endl;
}




template <typename T>
bool UTTT_Board<T>::is_win() {
    char bigBoard[9] = {0};

    // Iterate over 3x3 sub-boards
    for (int t = 0; t < 3; t++) {
        for (int k = 0; k < 3; k++) {
            char winner = 0;

            // Check rows in the sub-board
            for (int i = 0; i < 3; i++) {
                if (this->board[t * 3 + i][k * 3 + 0] == this->board[t * 3 + i][k * 3 + 1] &&
                    this->board[t * 3 + i][k * 3 + 1] == this->board[t * 3 + i][k * 3 + 2] &&
                    this->board[t * 3 + i][k * 3 + 0] != 0) {
                    winner = this->board[t * 3 + i][k * 3 + 0];
                }
            }

            // Check columns in the sub-board
            for (int i = 0; i < 3; i++) {
                if (this->board[t * 3 + 0][k * 3 + i] == this->board[t * 3 + 1][k * 3 + i] &&
                    this->board[t * 3 + 1][k * 3 + i] == this->board[t * 3 + 2][k * 3 + i] &&
                    this->board[t * 3 + 0][k * 3 + i] != 0) {
                    winner = this->board[t * 3 + 0][k * 3 + i];
                }
            }

            // Check diagonals in the sub-board
            if (this->board[t * 3 + 0][k * 3 + 0] == this->board[t * 3 + 1][k * 3 + 1] &&
                this->board[t * 3 + 1][k * 3 + 1] == this->board[t * 3 + 2][k * 3 + 2] &&
                this->board[t * 3 + 0][k * 3 + 0] != 0) {
                winner = this->board[t * 3 + 0][k * 3 + 0];
            }

            if (this->board[t * 3 + 0][k * 3 + 2] == this->board[t * 3 + 1][k * 3 + 1] &&
                this->board[t * 3 + 1][k * 3 + 1] == this->board[t * 3 + 2][k * 3 + 0] &&
                this->board[t * 3 + 0][k * 3 + 2] != 0) {
                winner = this->board[t * 3 + 0][k * 3 + 2];
            }

            // If a winner is found, update the big board and all elements in the small board
            if (winner != 0) {
                bigBoard[t * 3 + k] = winner;

                // Update all elements of the small board to the winner's symbol
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        this->board[t * 3 + i][k * 3 + j] = winner;
                    }
                }
            }
        }
    }

    // Check for a win condition in the big board
    for (int i = 0; i < 3; i++) {
        // Row check
        if (bigBoard[i * 3 + 0] == bigBoard[i * 3 + 1] &&
            bigBoard[i * 3 + 1] == bigBoard[i * 3 + 2] &&
            bigBoard[i * 3 + 0] != 0) {
            this->display_board();
            return true;
        }

        // Column check
        if (bigBoard[0 * 3 + i] == bigBoard[1 * 3 + i] &&
            bigBoard[1 * 3 + i] == bigBoard[2 * 3 + i] &&
            bigBoard[0 * 3 + i] != 0) {
            this->display_board();
            return true;
        }
    }

    // Diagonal checks
    if (bigBoard[0] == bigBoard[4] && bigBoard[4] == bigBoard[8] && bigBoard[0] != 0) {
        this->display_board();
        return true;
    }

    if (bigBoard[2] == bigBoard[4] && bigBoard[4] == bigBoard[6] && bigBoard[2] != 0) {
        this->display_board();
        return true;
    }

    return false;
}







template <typename T>
bool UTTT_Board<T>::is_draw() {
    bool overallDraw = true; // Assume the game is a draw unless proven otherwise

    // Iterate over each small board (3x3)
    for (int t = 0; t < 3; t++) {
        for (int k = 0; k < 3; k++) {
            bool isFull = true;
            char winner = 0;

            // Check rows and columns for a winner in the small board
            for (int i = 0; i < 3; i++) {
                // Row check
                if (this->board[t * 3 + i][k * 3 + 0] == this->board[t * 3 + i][k * 3 + 1] &&
                    this->board[t * 3 + i][k * 3 + 1] == this->board[t * 3 + i][k * 3 + 2] &&
                    this->board[t * 3 + i][k * 3 + 0] != 0) {
                    winner = this->board[t * 3 + i][k * 3 + 0];
                }

                // Column check
                if (this->board[t * 3 + 0][k * 3 + i] == this->board[t * 3 + 1][k * 3 + i] &&
                    this->board[t * 3 + 1][k * 3 + i] == this->board[t * 3 + 2][k * 3 + i] &&
                    this->board[t * 3 + 0][k * 3 + i] != 0) {
                    winner = this->board[t * 3 + 0][k * 3 + i];
                }
            }

            // Check diagonals for a winner in the small board
            if (this->board[t * 3 + 0][k * 3 + 0] == this->board[t * 3 + 1][k * 3 + 1] &&
                this->board[t * 3 + 1][k * 3 + 1] == this->board[t * 3 + 2][k * 3 + 2] &&
                this->board[t * 3 + 0][k * 3 + 0] != 0) {
                winner = this->board[t * 3 + 0][k * 3 + 0];
            }

            if (this->board[t * 3 + 0][k * 3 + 2] == this->board[t * 3 + 1][k * 3 + 1] &&
                this->board[t * 3 + 1][k * 3 + 1] == this->board[t * 3 + 2][k * 3 + 0] &&
                this->board[t * 3 + 0][k * 3 + 2] != 0) {
                winner = this->board[t * 3 + 0][k * 3 + 2];
            }

            // Check if the small board is full
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (this->board[t * 3 + i][k * 3 + j] == 0) {
                        isFull = false;
                    }
                }
            }

            // If the small board is full and has no winner, mark it as a draw
            if (isFull && winner == 0) {
                // Update all cells in the small board to '#'
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        this->board[t * 3 + i][k * 3 + j] = '#';
                        this->display_board();
                    }
                }
            }

            // If a small board isn't full or has a winner, the game isn't a draw yet
            if (!isFull || winner != 0) {
                overallDraw = false;
            }
        }
    }


    bool allIndexSet = true;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
        {
            if(this->board[i][j] == 0){
                allIndexSet = false;
            }
        }
    }
    if(allIndexSet && !is_win()){
        return true;
    }
    
    return overallDraw;
    
}




template <typename T>
bool UTTT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
UTTT_Player<T>::UTTT_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void UTTT_Player<T>::getmove(int& x, int& y) {
    cout << '\n' << this->name <<"Please enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
UTTT_Random_Player<T>::UTTT_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9; 
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void UTTT_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


#endif


void ui_utt :: main(){

    char choice;
    
    Player<char>* players[2];
    UTTT_Board<char>* B = new UTTT_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to Ultimate tic tac toe Game. :)\n";

    
    cout << "Enter Player 1 name: ";
    cin >> player1Name;


    while(true){

        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if(choice == '1'){
            players[0] = new UTTT_Player<char>(player1Name, 'X');
            break;
        }
        else if(choice == '2'){
            players[0] = new UTTT_Random_Player<char>('X');
            break;
        }

        cout << "Invalid choice for Player 1. Please enter a valid input.\n";
    }




    
    cout << "Enter Player 2 name: ";
    cin >> player2Name;



    while(true){

        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        if(choice == '1'){
            players[1] = new UTTT_Player<char>(player2Name, 'O');
            break;
        }
        else if(choice == '2'){
            players[1] = new UTTT_Random_Player<char>('O');
            break;
        }
        cout << "Invalid choice for Player 2. Please enter a valid input.\n\n";

    }


    GameManager<char> UTTT_game(B, players);
    UTTT_game.run();

    
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }





}
