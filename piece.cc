#include "piece.h"

piece::piece()
{
    color = 'e'; // Initialize with an empty color
}

void piece::set_piece_color(const char c)
{
    if (c == 'b' || c == 'w' || c == 'e')
    {
        color = c;
    }
    else
    {
        cout << "Color does not equal b, w, or e...";
    }
}

char piece::getColor() const
{
    return color;
}

void piece::flip()
{
    if (color == 'b')
    {
        color = 'w';
    }
    else if (color == 'w')
    {
        color = 'b'; // Flip the color to the opposite color
    }
}

char piece::current_color() const
{
    return color;
}

ostream &operator<<(ostream &outs, piece p)
{
    // Ensure to output the color of the piece
    if (p.getColor() == 'w')
    {
        outs << "O"; // Represent white pieces as 'O'
    }
    else if (p.getColor() == 'b')
    {
        outs << "X"; // Represent black pieces as 'X'
    }
    else
    {
        outs << "-"; // Empty cell
    }
    return outs;
}

bool piece::is_White() const
{
    if (color == 'w')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool piece::is_Empty() const
{
    if (color == 'e')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool piece::is_Black() const
{
    if (color == 'b')
    {
        return true;
    }
    else
    {
        return false;
    }
}
