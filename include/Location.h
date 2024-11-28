#pragma once

struct Location
{
    int row;
    int col;

    bool isEqual(const Location &other)
    {
        return (*this).row == other.row && (*this).col == other.col; 
    }

    int returnRow(int sign)
    {
        return sign + (*this).row;
    }

    int returnCol(int sign)
    {
        return sign + (*this).col;
    }

};
