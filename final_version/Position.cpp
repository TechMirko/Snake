//
// Gabriele Preti
//

#include "Position.hpp"

//snake_length

Position::Position() {
    int j = (cols - 1)/2 - snake_length/2;
    for (int i = 0; i < snake_length; i++) {
        coord[i][0] = (rows - 1)/2;
        coord[i][1] = j;
        j++;
    }
}

void Position::debug() {
    for (int i = 0; i < snake_length; i++) {
        cout << "( "<< coord[i][0] << " : ";
        cout << coord[i][1] << " )" << endl;
    }
}
void Position::Shift() {
    for (int i = snake_length-1; i > 0; i--) {
        coord[i][0]= coord[i-1][0];
        coord[i][1] = coord[i-1][1];
    }
    coord[0][0] = 0;
    coord[0][1] = 0;
}

void Position::Push(int row_coord, int col_coord) {
    coord[0][0] = row_coord;
    coord[0][1] = col_coord;
}

void Position::Pop() {
    coord[snake_length-1][0] = 0;
    coord[snake_length-1][1] = 0;
    Shift();
}

bool Position::Dups() {
    for (int i = 0; i < snake_length - 1; i++) {
        for (int j = i + 1; j < snake_length; j++) {
            if (coord[i][0] == coord[j][0] && coord[i][1] == coord[j][1]) {
                return true;
            }
        }
    }
    return false;
}

