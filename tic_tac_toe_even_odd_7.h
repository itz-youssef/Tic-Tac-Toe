//
// Created by pc on 12/11/2024.
//

#ifndef TIC_TAC_TOE_EVEN_ODD_H
#define TIC_TAC_TOE_EVEN_ODD_H
#include "BoardGame_Classes.h"
string val1 ;
bool check = false;
vector<string> oddNumbers = {"1", "3", "5", "7", "9"};
vector<string> evenNumbers = {"2", "4", "6", "8"};

template <typename T>
class TIC_TAC_TOE_EVEN_ODD_Board:public Board<T> {
public:
    TIC_TAC_TOE_EVEN_ODD_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};
class numerical_TTT{
public:

    void main();


};
template <typename T>
class TIC_TAC_TOE_EVEN_ODD_Player : public Player<T> {
public:
    TIC_TAC_TOE_EVEN_ODD_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class TIC_TAC_TOE_EVEN_ODD_Random_Player : public RandomPlayer<T>{
public:
    TIC_TAC_TOE_EVEN_ODD_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};




//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <vector>
#include <algorithm>

using namespace std;

// Constructor for TIC_TAC_TOE_EVEN_ODD_Board
template <typename T>
TIC_TAC_TOE_EVEN_ODD_Board<T>::TIC_TAC_TOE_EVEN_ODD_Board() {
    this->rows = this->columns = 3;
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
bool TIC_TAC_TOE_EVEN_ODD_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)){
            if(this->n_moves%2==0) {
                oddNumbers.erase(remove(oddNumbers.begin(), oddNumbers.end(), val1), oddNumbers.end());
            }else {
                evenNumbers.erase(remove(evenNumbers.begin(), evenNumbers.end(), val1), evenNumbers.end());
            }
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = val1[0];
        }
        check=true;
        return true;

    }else {
        if(check==false) {
            cout << "invalid input , enter again\n";
        }
        return false;
    }
}
// Display the board and the pieces on it
template <typename T>
void TIC_TAC_TOE_EVEN_ODD_Board<T>::display_board() {
    for (int i = 1; i < 4; i++) {
        cout << "\n " << i  << " || ";
        for (int j = 1; j < 4; j++) {
            cout << setw(2) << this->board[i-1][j-1] << " ||";
        }
        cout << "\n   ------------------";
    }
    cout << endl;
    cout << "      1     2    3 \n";

}

// Returns true if there is any winner
template <typename T>
bool TIC_TAC_TOE_EVEN_ODD_Board<T>::is_win() {
    for (int i = 0; i < 3; i++) {
        int row_sum = 0;
        for (int j = 0; j < 3; j++) {
            row_sum += this->board[i][j]- '0';
        }
        if (row_sum == 15) {
            return true;
        }
    }

    for (int j = 0; j < 3; j++) {
        int col_sum = 0;
        for (int i = 0; i < 3; i++) {
            col_sum += this->board[i][j]- '0';
        }
        if (col_sum == 15) {
            return true;
        }
    }

    int diag1_sum = this->board[0][0]- '0' + this->board[1][1]- '0' + this->board[2][2]- '0';
    int diag2_sum = this->board[0][2] - '0'+ this->board[1][1] - '0'+ this->board[2][0]- '0';
    if (diag1_sum == 15 || diag2_sum == 15) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool TIC_TAC_TOE_EVEN_ODD_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool TIC_TAC_TOE_EVEN_ODD_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for TIC_TAC_TOE_EVEN_ODD_Player
template <typename T>
TIC_TAC_TOE_EVEN_ODD_Player<T>::TIC_TAC_TOE_EVEN_ODD_Player(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
void TIC_TAC_TOE_EVEN_ODD_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (1 to 3) separated by spaces: ";
    check=false;
    cin >> x >> y;
    x--;
    y--;
    while (!(x >= 0 && x < 3 && y >= 0 && y < 3)) {
        cout << "Invalid coordinates! They must be within the grid (1 to 3). Try again: ";
        cin >> x >> y;
        x--;
        y--;
    }


    T num;
    if (this->symbol == 'X') {
        cout << this->name << ", enter your number (odd numbers only) from = { ";
        for(int i=0 ; i<oddNumbers.size() ; i++) {
            cout << oddNumbers[i] << " ";
        }
        cout << "} :";
        cin >> val1;
        while (find(oddNumbers.begin(), oddNumbers.end(), val1) == oddNumbers.end()) {
            cout << "Invalid number! It must be odd. Try again: ";
            cin >> val1;
        }
    }
    else if (this->symbol == 'O') {
        cout << this->name << ", enter your number (even numbers only) from = { " ;
        for(int i=0 ; i<evenNumbers.size() ; i++) {
            cout << evenNumbers[i] << " ";
        }
        cout << "} :";
        cin >> val1;
        while (find(evenNumbers.begin(), evenNumbers.end(), val1) == evenNumbers.end()) {
            cout << "Invalid number! It must be even. Try again: ";
            cin >> val1;
        }
    }
}




// Constructor for TIC_TAC_TOE_EVEN_ODD_Random_Player
template <typename T>
TIC_TAC_TOE_EVEN_ODD_Random_Player<T>::TIC_TAC_TOE_EVEN_ODD_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void TIC_TAC_TOE_EVEN_ODD_Random_Player<T>::getmove(int& x, int& y) {
    check=true;
        x = rand() % 3;
        y = rand() % 3;
    if (this->symbol == 'X') {
        if (!oddNumbers.empty())
            //vector<string> oddNumbers = {"1", "3", "5", "7", "9"};
            val1 = oddNumbers[rand() % oddNumbers.size()];
    }else if(this->symbol == 'O') {
            if (!evenNumbers.empty())
                val1 = evenNumbers[rand() % evenNumbers.size()];

        }
    }
void numerical_TTT::main(){
    string choose;
    int choice;
    Player<char>* players[2];
    string playerXName, player2Name;


    cout << "Welcome to Tic Tac Toe - Even & Odd!\n";
    TIC_TAC_TOE_EVEN_ODD_Board<char>* B = new TIC_TAC_TOE_EVEN_ODD_Board<char>();

    // Set up Player X
    cout << "Enter Player X's name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    if (choice == 1) {
        players[0] = new TIC_TAC_TOE_EVEN_ODD_Player<char>(playerXName, 'X');
    } else if (choice == 2) {
        players[0] = new TIC_TAC_TOE_EVEN_ODD_Random_Player<char>('X');
    } else {
        cout << "Invalid choice. Exiting the game.\n";
    }

    // Set up Player O
    cout << "Enter Player O's name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    if (choice == 1) {
        players[1] = new TIC_TAC_TOE_EVEN_ODD_Player<char>(player2Name, 'O');
    } else if (choice == 2) {
        players[1] = new TIC_TAC_TOE_EVEN_ODD_Random_Player<char>('O');
    } else {
        cout << "Invalid choice. Exiting the game.\n";
    }

    GameManager<char> game(B, players);
    game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}









#endif //TIC_TAC_TOE_EVEN_ODD_H
