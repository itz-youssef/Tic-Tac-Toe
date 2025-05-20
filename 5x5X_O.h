
#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"



int player_x_wins=0;
int player_o_wins=0;

template <typename T>
class fivex_o_board:public Board<T> {    
public:
    fivex_o_board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void check_win();
    static Player<T>* Ptr[2];
    static void Set_ptr(Player<T>* P[]);
    void small_is_win(char winner, int& player_x_wins, int& player_o_wins);
};

class ui5x5{
public:

void main();


};

template <typename T>
class five_x_o_player : public Player<T> {
public:
    five_x_o_player (string name, T symbol);
    void getmove(int& x, int& y) ;


};

template <typename T>
class fiveX_Orandomplayer : public RandomPlayer<T>{
public:
    fiveX_Orandomplayer (T symbol);
    void getmove(int &x, int &y) ;
};









using namespace std;


template <typename T>
fivex_o_board<T>::fivex_o_board() {
    this->rows = this->columns = 5;
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
bool fivex_o_board<T>::update_board(int x, int y, T mark) {
    
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
void fivex_o_board<T>::display_board() {
    cout <<"   "<< "player X"<<" : " << player_x_wins << "   |  " << "player O" << " : " << player_o_wins;
    player_o_wins=0 , player_x_wins=0;
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            if(this-> board[i][j] == 'X'){
            cout<< setw(8) << CYAN << this->board[i][j] << RESET << " |" ;

            }
            else cout << setw(8) << RED << this->board[i][j] << RESET << " |";
            
        }
        cout << "\n--------------------------------------------";
    }
    cout << endl;
}


template <typename T>
bool fivex_o_board<T>::is_win() {
    check_win();    
    if (this->n_moves == 24) {
        
        if (player_x_wins > player_o_wins) {
            fivex_o_board<T>::Ptr[1] = fivex_o_board<T>::Ptr[0];  
            return true;
        }
        // Check if player 2 wins
        else if (player_x_wins < player_o_wins) {
            fivex_o_board<T>::Ptr[0] = fivex_o_board<T>::Ptr[1]; 
            return true;
        }
    }
    return false;
}
template <typename T>
void fivex_o_board<T>::check_win() {
    
       
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j <= 2; j++) {
                if (this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j] != 0) {
                    small_is_win(this->board[i][j], player_x_wins, player_o_wins);
                }
            }
        }

        
        for (int j = 0; j < 5; j++) {
            for (int i = 0; i < 3; i++) {
                if (this->board[i][j] == this->board[i + 1][j] && this->board[i + 1][j] == this->board[i + 2][j] && this->board[i][j] != 0) {
                    small_is_win(this->board[i][j], player_x_wins, player_o_wins);
                }
            }
        }

        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (this->board[i][j] == this->board[i + 1][j + 1] && this->board[i + 1][j + 1] == this->board[i + 2][j + 2] && this->board[i][j] != 0) {
                    small_is_win(this->board[i][j], player_x_wins, player_o_wins);
                }
            }
        }

        
        for (int i = 0; i < 3; i++) {
            for (int j = 2; j < 5; j++) {
                if (this->board[i][j] == this->board[i + 1][j - 1] && this->board[i + 1][j - 1] == this->board[i + 2][j - 2] && this->board[i][j] != 0) {
                    small_is_win(this->board[i][j], player_x_wins, player_o_wins);
                }
            }
        }
    

}

template <typename T>
void fivex_o_board<T>::small_is_win(char winner, int& player_x_wins, int& player_o_wins){
    if (winner == 'X') {
        player_x_wins++; 
    } else if (winner == 'O') {
        player_o_wins++; 
    }
}




template <typename T>
bool fivex_o_board<T>::is_draw() {
    return (this->n_moves == 24 && !is_win());
}

template <typename T>
bool fivex_o_board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
void fivex_o_board<T>::Set_ptr(Player<T>* P[]) {
    Ptr[0] = P[0];  
    Ptr[1] = P[1];  
}



template <typename T>

Player<T>* fivex_o_board<T>::Ptr[2] = {nullptr, nullptr};  





template <typename T>
five_x_o_player<T>::five_x_o_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void five_x_o_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}


template <typename T>
fiveX_Orandomplayer<T>::fiveX_Orandomplayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

template <typename T>
void fiveX_Orandomplayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  
    y = rand() % this->dimension;

}
void ui5x5::main(){
    int choice;
    Player<char>* players[2];    
    fivex_o_board<char>::Set_ptr(players);
    fivex_o_board<char>* B = new fivex_o_board<char>();
    string playerXName, player2Name;

    cout << "Welcome to 5x5 tic tac toe Game. :)\n";

    
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new five_x_o_player<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new fiveX_Orandomplayer<char>('X');
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        
    }

    
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new five_x_o_player<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new fiveX_Orandomplayer<char>('O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        
    }

    
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }


}


#endif //_5X5X_O_H

 