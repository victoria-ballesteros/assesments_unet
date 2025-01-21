#include <iostream>
#include <iomanip>
#include <locale>

using namespace std;

int index1;
char board[9] = {'*', '*', '*', '*', '*', '*', '*', '*', '*'}; // Single array represents the board '*' means empty box in board

bool isFull() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == '*') {
            return false;
        }
    }
    return true;
}

bool userWon() {
    for (int i = 0; i < 9; i += 3) {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == 'O')) {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == 'O')) {
            return true;
        }
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'O')) {
        return true;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 'O')) {
        return true;
    }
    return false;
}

bool cpuWon() {
    for (int i = 0; i < 9; i += 3) {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == 'X')) {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == 'X')) {
            return true;
        }
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'X')) {
        return true;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 'X')) {
        return true;
    }
    return false;
}

void drawBoard() {
    cout << setw(65)<< "-------------------------TIC TAC TOE-------------------------" << endl;
    cout << setw(25) << "USUARIO--->(O)" << setw(25) << "CPU------>(X)" << endl;
    cout << endl;
    cout << setw(27) << "       " << board[0] << "   |   " << board[1] << "   |   " << board[2] << endl;
    cout << setw(45) << "     -----+-------+-----" << endl;
    cout << setw(27) << "       " << board[3] << "   |   " << board[4] << "   |   " << board[5] << endl;
    cout << setw(45) << "     -----+-------+-----" << endl;
    cout << setw(27) << "       " << board[6] << "   |   " << board[7] << "   |   " << board[8] << endl;
}

int minimax(bool isCpu, int alpha, int beta) {
    if (cpuWon()) return 10;
    if (userWon()) return -10;
    if (isFull()) return 0;
    
    int bestIndex;

    for (int i = 0; i < 9; i++) {
        if (board[i] == '*') {
            board[i] = isCpu ? 'X' : 'O';
            int value = minimax(!isCpu, alpha, beta);
            board[i] = '*';
            if (isCpu) {
                if (value > alpha) {
                    alpha = value;
                    bestIndex = i;
                }
            } else {
                if (value < beta) {
                    beta = value;
                    bestIndex = i;
                }
            }
            if (alpha >= beta) {
                break; // Poda alfa-beta
            }
        }
    }
    if (isCpu) {
        index1 = bestIndex;
        return alpha;
    } else {
        return beta;
    }
}

void playerMove() {
    int move;
    while (true) {
        cout << "\nEnter your move (1-9): ";
        cin >> move;
        if (move >= 1 && move <= 9 && board[move - 1] == '*') {
            board[move - 1] = 'O';
            break;
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
    system("cls");
    drawBoard();
}

void cpuMove() {
    minimax(true, -10, 10);
    cout << "\nCPU will place an 'X' in position " << (index1 + 1) << "." << endl << endl;
    system("pause"); // Wait for user input before clearing the screen
    board[index1] = 'X';
    system("cls");
    drawBoard();
}

void resetBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = '*';
    }
}

bool playAgain() {
    char choice;
    cout << "\nQuieres jugar otra vez? (s/n): ";
    cin >> choice;
    if (choice == 's' || choice == 'S') {
        return true;
    } else {
        cout << "\nGracias por jugar! Nos vemos pronto!" << endl;
        return false;
    }
}

int main() {
    int choice;
    setlocale(LC_ALL, "spanish");
    do {
        system("cls");
		cout << setw(65) << "-------------------------TIC TAC TOE-------------------------" << endl;
		cout << setw(26) << "USUARIO--->(O)" << setw(25) << "CPU------>(X)" << endl << endl;
		cout << "\t\tQuien debe iniciar primero la partida?:" << endl;
		cout << "\t\t1 -> Usuario" << endl << "\t\t2 -> CPU" << endl << "\t\t3 -> Salir" << endl << endl << "\t\tSeleccione: ";
		cin >> choice;

        if (choice == 1) {
            system("cls");
            drawBoard();
            playerMove();
        } else if (choice == 3){
        	cout << "\n\nHasta luego!" << endl;
        	break;
		}

        while (true) {
            cpuMove();
            if (cpuWon()) {
                system("cls");
                cout << endl;
                cout << "###############################################" << endl;
                cout << "#                                             #" << endl;
                cout << "#                  ¡GAME OVER!                #" << endl;
                cout << "#                                             #" << endl;
                cout << "#                 " << setw(10) << "¡La CPU GANO!" << setw(10) << "               #" << endl;
                cout << "#                                             #" << endl;
                cout << "###############################################" << endl;
                break;
            }
            if (isFull()) {
                system("cls");
                cout << endl;
                cout << "---------------------------------------" << endl;
                cout << "|                                     |" << endl;
                cout << "|             ¡EMPATE!                |" << endl;
                cout << "|                                     |" << endl;
                cout << "---------------------------------------" << endl;
                cout << endl;
                break;
            }

            playerMove();
            if (userWon()) {
                system("cls");
                cout << endl;
                cout << "***************************************" << endl;
                cout << "*                                     *" << endl;
                cout << "*            ¡FELICIDADES!            *" << endl;
                cout << "*                                     *" << endl;
                cout << "*            ¡HAS GANADO!             *" << endl;
                cout << "*                                     *" << endl;
                cout << "***************************************" << endl;
                cout << endl;
                break;
            }
            if (isFull()) {
                system("cls");
                cout << endl;
                cout << "---------------------------------------" << endl;
                cout << "|                                     |" << endl;
                cout << "|             ¡EMPATE!                |" << endl;
                cout << "|                                     |" << endl;
                cout << "---------------------------------------" << endl;
                cout << endl;
                break;
            }
        }
    } while (playAgain() && choice != 3);
    return 0;
}

