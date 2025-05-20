#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib> // for rand()

using namespace std;
bool show_message = false;
template <typename T>
class four_X_O_Board : public Board<T> {
public:

    four_X_O_Board();
    ~four_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};
class ui4x4{
public:

    void main();


};

string moves;

template <typename T>
class four_X_O_Player : public Player<T> {
public:
    four_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};
class four_X_O_game{
public:

    void main();


};
template <typename T>
class four_X_O_Random_Player : public RandomPlayer<T> {
public:
    four_X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};


template <typename T>
four_X_O_Board<T>::four_X_O_Board() {
    this->rows = this->columns = 4;
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
four_X_O_Board<T>::~four_X_O_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool four_X_O_Board<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == mark) {
        if (moves == "up" && x - 1 >= 0 && this->board[x - 1][y] == 0) {
            this->board[x - 1][y] = mark;
            this->board[x][y] = 0;
            this->n_moves++;
            return true;
        }
        if (moves == "down" && x + 1 < this->rows && this->board[x + 1][y] == 0) {
            this->board[x + 1][y] = mark;
            this->board[x][y] = 0;
            this->n_moves++;
            return true;
        }
        if (moves == "right" && y + 1 < this->columns && this->board[x][y + 1] == 0) {
            this->board[x][y + 1] = mark;
            this->board[x][y] = 0;
            this->n_moves++;
            return true;
        }
        if (moves == "left" && y - 1 >= 0 && this->board[x][y - 1] == 0) {
            this->board[x][y - 1] = mark;
            this->board[x][y] = 0;
            this->n_moves++;
            return true;
        }
    }
    if (!show_message) {
        cout << "\nInvalid input or invaild move , enter it again\n";
    }
    return false;
}

template <typename T>
void four_X_O_Board<T>::display_board() {
    if (this->n_moves == 0) {
        for (int i = 0; i < this->columns; i++) {
            if (i % 2 == 0) {
                this->board[0][i] = 'X';
                this->board[this->rows - 1][i] = 'X';
            } else {
                this->board[0][i] = 'O';
                this->board[this->rows - 1][i] = 'O';
            }
        }
    }
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout  << setw(2) << (this->board[i][j] ? this->board[i][j] : ' ') << " |";
        }
        cout << "\n-------------------";
    }
    cout << endl;
}

template <typename T>
bool four_X_O_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2] &&
                this->board[i][j] != 0) {
                return true;
                }
        }

        for (int j = 0; j <= this->rows - 3; j++) {
            if (this->board[j][i] == this->board[j + 1][i] &&
                this->board[j + 1][i] == this->board[j + 2][i] &&
                this->board[j][i] != 0) {
                return true;
                }
        }
    }

    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2] &&
                this->board[i][j] != 0) {
                return true;
                }
        }
    }

    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i + 1][j - 1] == this->board[i + 2][j - 2] &&
                this->board[i][j] != 0) {
                return true;
                }
        }
    }

    return false;
}
template <typename T>
bool four_X_O_Board<T>::is_draw() {
    return (this->n_moves >= 99999 && !is_win());
}

template <typename T>
bool four_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


template <typename T>
four_X_O_Player<T>::four_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void four_X_O_Player<T>::getmove(int& x, int& y) {
    bool valid = false;
    while (!valid) {
        cout << "\nPlease enter your move x and y (1 to 4) separated by spaces: ";
        show_message=false;
        cin >> x >> y;
        x--;
        y--;
        if (x >= 0 && x < 4 && y >= 0 && y < 4) {
            valid = true;
        } else {
            cout << "Invalid move! Please enter valid x and y values between 1 and 4.\n";
        }
    }
    cout << "Enter the move that you want (up - down - right - left): ";
    cin >> moves;
    for (int i = 0; i < moves.length(); ++i) {
        moves[i] = tolower(moves[i]);
    }
}


template <typename T>
four_X_O_Random_Player<T>::four_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void four_X_O_Random_Player<T>::getmove(int& x, int& y) {
    bool valid = false;
    show_message=true;
    while (!valid) {
        x = rand() % 4;
        y = rand() % 4;
        string directions[] = {"up", "down", "right", "left"};
        moves = directions[rand() % 4];
        if (moves == "up" && x - 1 >= 0) {
            valid = true;
        } else if (moves == "down" && x + 1 < 4) {
            valid = true;
        } else if (moves == "right" && y + 1 < 4) {
            valid = true;
        } else if (moves == "left" && y - 1 >= 0) {
            valid = true;
        }
    }
}
void ui4x4::main() {
    int choice;
    Player<char>* players[2];
    four_X_O_Board<char>* B = new four_X_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new four_X_O_Player<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new four_X_O_Random_Player<char>('X');
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";

    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new four_X_O_Player<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new four_X_O_Random_Player<char>('O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";

    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}
#endif //_3X3X_O_H
