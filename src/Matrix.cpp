//
// Created by wangnan on 16-9-20.
//

#include "Matrix.h"
Linear::BlockView Linear::Matrix::Row(SizeT index)
{
    if(index >= row_count)
    {
       throw OutOfBoundException{};
    }
    return BlockView{*this, index, 0, 1, col_count};
}
Linear::BlockView Linear::Matrix::Col(SizeT index)
{
    if(index >= col_count)
    {
       throw OutOfBoundException{};
    }
    return BlockView(*this, 0, index, row_count, 1);
}
Linear::Matrix Linear::Matrix::operator*(const MatrixView &mr) const
{
    const Matrix& ml = *this;
    if(ml.ColCount() != mr.RowCount())
    {
        throw DimException{};
    }
    Matrix result_m{ml.RowCount(), mr.ColCount()};

    for(SizeT ri=0; ri < result_m.RowCount(); ri ++ )
    {
        for(SizeT ci=0; ci < result_m.ColCount(); ci++)
        {
            EntryT dot_product = 0;
            for(SizeT i=0; i < ml.ColCount(); i++)
            {
                dot_product += ml.Entry(ri, i) * mr.Entry(i, ci);
            }
            result_m.Entry(ri, ci) = dot_product;
        }
    }

    return std::move(result_m);
}

Linear::Matrix Linear::Matrix::operator+(const MatrixView &mr) const
{
    const Matrix& ml = *this;
    if(ml.RowCount() != mr.RowCount() || ml.ColCount() != mr.ColCount())
    {
        throw DimException{};
    }
    Matrix result_m{ml.RowCount(), ml.ColCount()};

    for(SizeT ri=0; ri < result_m.RowCount(); ri ++ )
    {
        for(SizeT ci=0; ci < result_m.ColCount(); ci++)
        {
            result_m.Entry(ri, ci) = ml.Entry(ri, ci) + mr.Entry(ri, ci);
        }
    }

    return std::move(result_m);
}

Linear::Matrix::Matrix(std::initializer_list<std::initializer_list<EntryT>> lst):
    MatrixView(lst.size(), lst.begin()->size()),
    entries(row_count*col_count)
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
Linear::Matrix::Matrix(const Linear::MatrixView &mv):
    MatrixView(mv.RowCount(), mv.ColCount()), entries(mv.RowCount()*mv.ColCount())
{
    for(SizeT ri=0; ri < this->RowCount(); ri++)
    {
        for(SizeT ci=0; ci < this->ColCount(); ci++)
        {
            this->Entry(ri, ci) = mv.Entry(ri, ci);
        }
    }
}

std::ostream &Linear::operator<<(std::ostream &out, const MatrixView &m)
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
Linear::Matrix Linear::operator*(const ScalarT &s, const MatrixView &m)
{
    Matrix r_m(m.RowCount(), m.ColCount());
    for(SizeT ri=0; ri < m.RowCount(); ri++)
    {
        for(SizeT ci=0; ci < m.ColCount(); ci++)
        {
            r_m.Entry(ri, ci) = m.Entry(ri, ci)*s;
        }
    }
    return std::move(r_m);
}
Linear::Matrix Linear::operator*(const MatrixView &m, const ScalarT &s)
{
    return operator*(s, m);
}
bool Linear::MatrixView::operator==(const Linear::MatrixView &mr) const
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
Linear::MatrixView &Linear::MatrixView::operator=(const Linear::MatrixView &mr)
{
    if(this->RowCount() != mr.RowCount() || this->ColCount() != mr.ColCount())
    {
        throw DimException{};
    }
    for(SizeT ri=0; ri < this->RowCount(); ri++)
    {
        for(SizeT ci=0; ci < this->ColCount(); ci++)
        {
            this->Entry(ri, ci) = mr.Entry(ri, ci);
        }
    }
    return *this;
}

