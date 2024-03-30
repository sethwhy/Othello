#include <iostream>
#include <fstream>
#ifndef PIECE_H
#define PIECE_H

using namespace std;

class piece
{
public:
    piece();
    void set_piece_color(const char c);
    void flip();
    char getColor() const;
    char current_color() const;
    friend ostream &operator<<(ostream &outs, piece p);
    void isWhite() const;
    bool is_White() const;
    bool is_Empty() const;
    void isBlack() const;
    void isEmpty() const;
    bool is_Black() const;

private:
    char color;
};
#endif