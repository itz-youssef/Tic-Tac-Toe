#ifndef _CONNECT_4_H
#define _CONNECT_4_H

#include "BoardGame_Classes.h"

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <string>
#include <sstream> // for stringstream

using namespace std;

template <typename T>
class Connect4_Board: public Board<T> {
public:
    Connect4_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board ();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool Connect4_Random_Player();
};
class connect_4{
public:
    void main();
};
template <typename T>
class Connect4_Player : public Player<T> {
public:
    Connect4_Player (string name, T symbol);
    void getmove(int& x , int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for ConnectFour_Board
template <typename T>
Connect4_Board<T>::Connect4_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize all cells to 0
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Connect4_Board<T>::update_board(int x, int y, T mark) {
    if (y < 0 || y >= this->columns+1 || x < 0 || x >= this->rows+2) {
        return false; // Invalid index
    }

    for (int i = this->rows - 1; i >= -1; --i) { // Start from the bottom row
        if (this->board[i][y] == 0) { // Find the first empty cell in the column
            this->board[i][y] = toupper(mark); // Place the mark
            this->n_moves++;
            return true;
        }
    }
    return false; // Column is full
}

template <typename T>
void Connect4_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0)
                cout << "| . |";
            else
                cout << "| " << this->board[i][j] << " |"; // X or O
        }
        cout << endl;
    }
    cout << "===================================" << endl;
    cout << "  1    2    3    4    5    6    7 \n";
}

template <typename T>
bool Connect4_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j+1] &&
                this->board[i][j] == this->board[i][j+2] &&
                this->board[i][j] == this->board[i][j+3]) {
                return true;
            }
        }
    }

    for (int i = 0; i < this->rows - 3; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j] &&
                this->board[i][j] == this->board[i+2][j] &&
                this->board[i][j] == this->board[i+3][j]) {
                return true;
            }
        }
    }

    for (int i = 0; i < this->rows - 3; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j+1] &&
                this->board[i][j] == this->board[i+2][j+2] &&
                this->board[i][j] == this->board[i+3][j+3]) {
                return true;
            }
        }
    }

    for (int i = 3; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i-1][j+1] &&
                this->board[i][j] == this->board[i-2][j+2] &&
                this->board[i][j] == this->board[i-3][j+3]) {
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool Connect4_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool Connect4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for ConnectFour_Player
template <typename T>
Connect4_Player<T>::Connect4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Connect4_Player<T>::getmove(int& move, int& z) {
    string input;
    while (true) {
        cout << "\nPlease enter a column number from 1 to 7: ";
        cin >> input;

        stringstream ss(input);
        int column;
        if (ss >> column && column >= 1 && column <= 7) {
            if (column > 7) {
                cout << "Error: Column number cannot be greater than 7.\n";
            } else {
                move = column;
                z = column - 1; // Map to index
                break;
            }
        } else {
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
        }
    }
}

// Constructor for ConnectFour_Random_Player
template <typename T>
class Connect4_Random_Player : public RandomPlayer<T> {
public:
    Connect4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}
    void getmove(int& x, int& y) override {
        x = rand() % 6;
        y = rand() % 7 ;
    }
};
void connect_4::main(){
    string choose;
    int choice;
    Player<char>* players[2];
    string playerXName, player2Name;

    cout << "Welcome to Connect 4!\n";
    Connect4_Board<char>* B = new Connect4_Board<char>();

    // Set up Player X
    cout << "Enter Player X's name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    if (choice == 1) {
        players[0] = new Connect4_Player<char>(playerXName, 'X');
    } else if (choice == 2) {
        players[0] = new Connect4_Random_Player<char>('X');
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
        players[1] = new Connect4_Player<char>(player2Name, 'O');
    } else if (choice == 2) {
        players[1] = new Connect4_Random_Player<char>('O');
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
#endif
