//
// Created by wangnan on 16-9-20.
//

#include "Matrix.h"
Matrix Matrix::Row(SizeT index) const
{
    if(index >= row_count)
    {
       throw OutOfBoundException{};
    }
    Matrix result_m{1, col_count};
    for(SizeT ci=0; ci < result_m.col_count; ci++)
    {
        result_m.Entry(0, ci) = Entry(index, ci);
    }
}
Matrix Matrix::Col(SizeT index) const
{
    if(index >= col_count)
    {
       throw OutOfBoundException{};
    }
    Matrix result_m{row_count, 1};
    for(SizeT ri=0; ri < result_m.row_count; ri++)
    {
        result_m.Entry(ri, 0) = Entry(ri, index);
    }
}
Matrix Matrix::operator*(Matrix const &mr) const
{
    const Matrix& ml = *this;
    if(ml.col_count != mr.row_count)
    {
        throw DimException{};
    }
    Matrix result_m{ml.row_count, mr.col_count};

    for(SizeT ri=0; ri < result_m.row_count; ri ++ )
    {
        for(SizeT ci=0; ci < result_m.col_count; ci++)
        {
            EntryT dot_product = 0;
            for(SizeT i=0; i < ml.col_count; i++)
            {
                dot_product += ml.Entry(ri, i) * mr.Entry(i, ci);
            }
            result_m.Entry(ri, ci) = dot_product;
        }
    }

    return std::move(result_m);
}
bool Matrix::operator==(Matrix const &mr) const
{
    if(this->RowCount() != mr.RowCount() or this->ColCount() != mr.ColCount())
    {
        return false;
    }
    for(SizeT ri=0; ri < this->RowCount(); ri++)
    {
        for(SizeT ci=0; ci < this->ColCount(); ci++)
        {
            if(this->Entry(ri, ci) != mr.Entry(ri, ci))
            {
                return false;
            }
        }
    }
    return true;
}
bool Matrix::operator!=(Matrix const &mr) const
{
    return !(*this == mr);
}
Matrix Matrix::operator+(Matrix const &mr) const
{
    const Matrix& ml = *this;
    if(ml.RowCount() != mr.RowCount() || ml.ColCount() != mr.ColCount())
    {
        throw DimException{};
    }
    Matrix result_m{ml.row_count, ml.col_count};

    for(SizeT ri=0; ri < result_m.row_count; ri ++ )
    {
        for(SizeT ci=0; ci < result_m.col_count; ci++)
        {
            result_m.Entry(ri, ci) = ml.Entry(ri, ci) + mr.Entry(ri, ci);
        }
    }

    return std::move(result_m);
}
std::ostream &operator<<(std::ostream &out, const Matrix &m)
{
    out << "{\n";
    for(SizeT ri=0; ri < m.RowCount(); ri++)
    {
        out << "{";
        for(SizeT ci=0; ci < m.ColCount(); ci++)
        {
            out << m.Entry(ri, ci) << ",";
        }
        out << "}\n";
    }
    out << "}\n";
}
