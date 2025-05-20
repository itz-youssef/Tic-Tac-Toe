#ifndef _INVERSE3X3X_O_H
#define _INVERSE3X3X_O_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>



#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

bool second_loop = false;
int player1_count = 0, player2_count = 0;
bool draw_check=false;
class inverse3x3o{
public:

    void main();


};
template <typename T>
class inverseX_O_Board : public Board<T> {
public:
    inverseX_O_Board();
    ~inverseX_O_Board();

    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

    static Player<T>* Ptr[2];
    static void Set_ptr(Player<T>* P[]);
};

template <typename T>
class inverseX_O_player : public Player<T> {
public:
    inverseX_O_player(std::string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class inverseX_O_Random_Player : public RandomPlayer<T> {
public:
    inverseX_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};



using namespace std;

// Constructor for X_O_Board
template <typename T>
inverseX_O_Board<T>::inverseX_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns]();
    }
    this->n_moves = 0;
}


template <typename T>
inverseX_O_Board<T>::~inverseX_O_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}


template <typename T>
bool inverseX_O_Board<T>::update_board(int x, int y, T mark) {
    if (!second_loop) {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && (this->board[x][y] == 0 || mark == 0)) {
            if (mark == 0) {
                this->n_moves--;
                this->board[x][y] = 0;
            } else {
                this->n_moves++;
                this->board[x][y] = toupper(mark);
            }
            return true;
        }
        return false;
    }
    return true;
}

// Display the board
template <typename T>
void inverseX_O_Board<T>::display_board() {
    if (!second_loop) {
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(8) << (this->board[i][j] ? this->board[i][j] : ' ') << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }
}


template <typename T>

bool inverseX_O_Board<T>::is_win() {
    if(this->n_moves==9){
        for (int i = 0; i < 3; i++) {
            // Check rows
            if (this->board[i][0] == this->board[i][1] &&
                this->board[i][1] == this->board[i][2] &&
                this->board[i][0] != 0) {
                if (this->board[i][0] == 'X') {
                    player1_count++;
                } else if (this->board[i][0] == 'O') {
                    player2_count++;
                }
                }

            // Check columns
            if (this->board[0][i] == this->board[1][i] &&
                this->board[1][i] == this->board[2][i] &&
                this->board[0][i] != 0) {
                if (this->board[0][i] == 'X') {
                    player1_count++;
                } else if (this->board[0][i] == 'O') {
                    player2_count++;
                }
                }
        }

        // Check main diagonal
        if (this->board[0][0] == this->board[1][1] &&
            this->board[1][1] == this->board[2][2] &&
            this->board[0][0] != 0) {
            if (this->board[0][0] == 'X') {
                player1_count++;
            } else if (this->board[0][0] == 'O') {
                player2_count++;
            }
            }

        // Check anti-diagonal
        if (this->board[0][2] == this->board[1][1] &&
            this->board[1][1] == this->board[2][0] &&
            this->board[0][2] != 0) {
            if (this->board[0][2] == 'X') {
                player1_count++;
            } else if (this->board[0][2] == 'O') {
                player2_count++;
            }
            }

        if(second_loop==true) {
            return true;
        }
        if(player1_count<player2_count) {
            return true;
        }else if(player2_count<player1_count) {
            second_loop=true;
            return false;
        }else {
            draw_check=true;
        }
        return false;
    }else {
        return false;
    }

}

template <typename T>
bool inverseX_O_Board<T>::is_draw() {
    return (draw_check== true&& !is_win());
}


template <typename T>
bool inverseX_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


template <typename T>
void inverseX_O_Board<T>::Set_ptr(Player<T>* P[]) {
    Ptr[0] = P[0];
    Ptr[1] = P[1];
}

template <typename T>
Player<T>* inverseX_O_Board<T>::Ptr[2] = {nullptr, nullptr};




template <typename T>
inverseX_O_player<T>::inverseX_O_player(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void inverseX_O_player<T>::getmove(int& x, int& y) {
    if (!second_loop) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
    }
}


template <typename T>
inverseX_O_Random_Player<T>::inverseX_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}


template <typename T>
void inverseX_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}
void inverse3x3o::main(){
    int choice;
    Player<char>* players[2];
    inverseX_O_Board<char>::Set_ptr(players);
    inverseX_O_Board<char>* B = new inverseX_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Misrie X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new inverseX_O_player<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new inverseX_O_Random_Player<char>('X');
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
            players[1] = new inverseX_O_player<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new inverseX_O_Random_Player<char>('O');
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

#endif
