//
// Created by Gabriele Preti on 02/03/25.
//
#include "Snake.hpp"
#include <iostream>
using namespace std;

Snake::Snake() : Position::Position(){
    xoff = 4;
    yoff = 6;
    get_terminal(xMax, yMax);
    snake_win = centered_win(rows + xoff, cols + yoff, xMax, yMax);
    keypad(snake_win, TRUE);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = false;
        }
    }
    for (int k = 0; k < snake_length; k++) {
        matrix[coord[k][0]][coord[k][1]] = true;
    }
    head_row = coord[0][0];
    head_col = coord[0][1];
}
void Snake::position() {
    for (int i = 0; i < snake_length; i++) {
        mvprintw(i + 2,2,"%d", coord[i][0]);
        mvprintw(i + 2,2,"%d", coord[i][1]);
    }
}

void Snake::display() {
    //wclear(snake_win);
    box(snake_win, 0, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == true) {
                wattron(snake_win, A_REVERSE);
            }
            mvwprintw(snake_win, i+ (xoff)/2, j + (yoff)/2, "%d", matrix[i][j]);
            wattroff(snake_win, A_REVERSE);
        }
    }
    wrefresh(snake_win);
}
void Snake::display_good() {
    box(snake_win, 0, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == true) {
                wattron(snake_win, A_BOLD);
                mvwprintw(snake_win, i+ (xoff)/2, j + (yoff)/2, "%s", "@");
                wattroff(snake_win, A_BOLD);
            }
            else {
                mvwprintw(snake_win, i+ (xoff)/2, j + (yoff)/2, "%s", " ");
            }
        }
    }
    wrefresh(snake_win);
}

void Snake::offsegment() {
    matrix[coord[snake_length-1][0]][coord[snake_length-1][1]] = false;
}
void Snake::onsegment() {
    matrix[coord[0][0]][coord[0][1]] = true;
}

void Snake::moveup() {
    Snake::offsegment();
    Position::Pop();
    head_row = head_row - 1;
    if (head_row < 0) {head_row = rows - 1; }
    Position::Push(head_row, head_col);
    Snake::onsegment();
}

void Snake::movedown() {
    Snake::offsegment();
    Position::Pop();
    head_row = head_row + 1;
    if (head_row > rows - 1) {head_row = 0; }
    Position::Push(head_row, head_col);
    Snake::onsegment();
}

void Snake::moveleft() {
    Snake::offsegment();
    Position::Pop();
    head_col = head_col - 1;
    if (head_col < 0) {head_col = cols - 1; }
    Position::Push(head_row, head_col);
    Snake::onsegment();
}

void Snake::moveright() {
    Snake::offsegment();
    Position::Pop();
    head_col = head_col + 1;
    if (head_col > cols - 1) {head_col = 0; }
    Position::Push(head_row, head_col);
    Snake::onsegment();
}
