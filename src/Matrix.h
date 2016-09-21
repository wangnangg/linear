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

namespace Linear
{

class DimException : std::exception
{

};
class OutOfBoundException : std::exception
{

};

class MatrixView
{
protected:
    SizeT row_count, col_count;
public:
    MatrixView(SizeT row_count, SizeT col_count) : row_count(row_count), col_count(col_count)
    {}
    SizeT RowCount() const
    { return row_count; }
    SizeT ColCount() const
    { return col_count; }
    virtual EntryT &Entry(SizeT row_index, SizeT col_index) = 0;
    virtual const EntryT &Entry(SizeT row_index, SizeT col_index) const = 0;

    bool operator==(MatrixView const &mr) const;
    bool operator!=(MatrixView const &mr) const
    {
        return !(*this == mr);
    }
    MatrixView &operator=(MatrixView const &mr);

};

std::ostream &operator<<(std::ostream &out, const MatrixView &m);

class BlockView : public MatrixView
{
    MatrixView &inner_view;
    SizeT row_offset, col_offset;
public:
    BlockView(Linear::MatrixView &m,
              SizeT row_offset,
              SizeT col_offset,
              SizeT row_count,
              SizeT col_count) :
        MatrixView(row_count, col_count), row_offset(row_offset), col_offset(col_offset), inner_view(m)
    {
        if (row_count + row_offset > inner_view.RowCount() || col_count + col_offset > inner_view.ColCount()) {
            throw DimException{};
        }
    }
    BlockView(const BlockView &m) :
        MatrixView(m.row_count, m.col_count), row_offset(m.row_offset), col_offset(m.col_offset),
        inner_view(m.inner_view)
    {}

    virtual EntryT &Entry(SizeT row_index, SizeT col_index) override
    {
        if (row_index >= row_count || col_index >= col_count) {
            throw OutOfBoundException{};
        }
        return inner_view.Entry(row_offset + row_index, col_offset + col_index);
    }
    virtual const EntryT &Entry(SizeT row_index, SizeT col_index) const override
    {
        if (row_index >= row_count || col_index >= col_count) {
            throw OutOfBoundException{};
        }
        return inner_view.Entry(row_offset + row_index, col_offset + col_index);
    }

    BlockView &operator=(BlockView const &mr)
    {
        MatrixView::operator=(mr);
        return *this;
    }
};

class Matrix : public MatrixView
{
    std::vector<EntryT> entries;
public:
    Matrix(SizeT row_count, SizeT col_count)
        : MatrixView(row_count, col_count), entries(row_count * col_count)
    {}
    Matrix(std::initializer_list<std::initializer_list<EntryT>> lst);
    Matrix(Matrix const &m) : MatrixView(m.row_count, m.col_count), entries(m.entries)
    {}
    Matrix(Matrix &&m) : MatrixView(m.row_count, m.col_count), entries(std::move(m.entries))
    {}
    Matrix() : MatrixView(0, 0), entries(0)
    {}
    Matrix(const MatrixView &mv);

    BlockView Row(SizeT index);
    BlockView Col(SizeT index);
    virtual EntryT &Entry(SizeT row_index, SizeT col_index) override
    { return entries[row_index * col_count + col_index]; }
    virtual const EntryT &Entry(SizeT row_index, SizeT col_index) const override
    { return entries[row_index * col_count + col_index]; }

    Matrix operator*(const MatrixView &mr) const;
    Matrix operator+(const MatrixView &mr) const;

    Matrix &operator=(Matrix const &mr)
    {
        MatrixView::operator=(mr);
        return *this;
    }
};

Matrix operator*(const ScalarT &s, const MatrixView &m);
Matrix operator*(const MatrixView &m, const ScalarT &s);

}
#endif //CPP_MATRIX_H
