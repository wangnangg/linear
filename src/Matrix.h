//
// Created by wangnan on 16-9-20.
//

#ifndef CPP_MATRIX_H
#define CPP_MATRIX_H

#include <vector>
#include <exception>
#include <iostream>

typedef double EntryT;
typedef double ScalarT;
typedef unsigned long SizeT;


class DimException : std::exception
{

};
class OutOfBoundException : std::exception
{

};


class Matrix
{
    std::vector<EntryT> entries;
    SizeT row_count;
    SizeT col_count;
public:
    Matrix(SizeT row_count, SizeT col_count):row_count(row_count), col_count(col_count), entries(row_count*col_count){}
    Matrix(std::initializer_list<std::initializer_list<EntryT>> lst):Matrix(lst.size(),lst.begin()->size())
    {
        SizeT ri=0;
        for(const auto &col:lst)
        {
            SizeT ci=0;
            for(const auto &v:col)
            {
                Entry(ri, ci) = v;
                ci+=1;
            }
            if( ci != col_count)
            {
                throw DimException{};
            }
            ri += 1;
        }
    }
    Matrix Row(SizeT index) const;
    Matrix Col(SizeT index) const;
    EntryT &Entry(SizeT row_index, SizeT col_index) { return entries[row_index*col_count+col_index]; }
    const EntryT &Entry(SizeT row_index, SizeT col_index) const { return entries[row_index*col_count+col_index]; }
    SizeT RowCount() const
    { return row_count; }
    SizeT ColCount() const
    { return col_count; }

    Matrix operator*(Matrix const &mr) const;
    Matrix operator+(Matrix const &mr) const;
    bool operator==(Matrix const &mr) const;
    bool operator!=(Matrix const &mr) const;

};

std::ostream& operator<<(std::ostream& out, const Matrix& m);
#endif //CPP_MATRIX_H
