//
// Created by wangnan on 16-9-20.
//

#include <gtest/gtest.h>
#include <Matrix.h>
#include <iostream>

using namespace std;
using namespace Linear;

TEST(Basic, ListInit)
{
    Matrix m = {{1, 2}, {3, 4}, {5, 6}};
    ASSERT_EQ(m.RowCount(), 3);
    ASSERT_EQ(m.ColCount(), 2);
    ASSERT_EQ(m.Entry(0, 0), 1);
    ASSERT_EQ(m.Entry(1, 1), 4);
    ASSERT_EQ(m.Entry(2, 0), 5);
    ASSERT_ANY_THROW((Matrix{{1, 2}, {3}}));
    cout << m;
}

TEST(Basic, Equal)
{
    Matrix m1 = {{1, 2}, {3, 4}, {5, 6}};
    Matrix m2 = {{1, 2, 3}, {4, 5, 6}};
    Matrix m3 = {{1, 2, 3}, {4, 5, 6}};
    ASSERT_EQ(m2, m3);
    ASSERT_EQ(m3, m2);
    ASSERT_NE(m1, m2);
    ASSERT_NE(m2, m1);
}

TEST(Basic, Multiply)
{
    Matrix m1 = {{1, 2}, {3, 4}, {5, 6}};
    Matrix m2 = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    Matrix correct_m = {{11, 14, 17, 20}, {23, 30, 37, 44}, {35, 46, 57, 68}};
    ASSERT_EQ(m1 * m2, correct_m);
    ASSERT_ANY_THROW(m2 * m1);
    cout << m1 * m2;
}

TEST(Basic, Add)
{
    Matrix m1 = {{1, 2}, {3, 4}, {5, 6}};
    Matrix m2 = {{1, 2}, {3, 4}, {5, 6}};
    Matrix m3 = {{1, 2, 3}, {3, 4, 3}, {5, 6, 3}};
    Matrix correct_m = {{2, 4}, {6, 8}, {10, 12}};
    ASSERT_EQ(m1 + m2, correct_m);
    ASSERT_EQ(m2 + m1, correct_m);
    ASSERT_ANY_THROW(m1 + m3);
    cout << m1 + m2;
}

TEST(Basic, Scalar)
{
    Matrix m1 = {{1, 2}, {3, 4}, {5, 6}};
    ScalarT s = 2;
    Matrix correct_m = {{2, 4}, {6, 8}, {10, 12}};
    ASSERT_EQ(s * m1, correct_m);
    ASSERT_EQ(m1 * s, correct_m);
    cout << s * m1;
}

TEST(Basic, Combination)
{
    Matrix m1 = {{1, 2}, {3, 4}, {5, 6}};
    ScalarT s = 2;
    Matrix m2 = {{1, 2}, {3, 4}, {5, 6}};
    Matrix correct_m = {{3, 6}, {9, 12}, {15, 18}};
    ASSERT_EQ(s * m1 + m2, correct_m);
    cout << s * m1;
}

TEST(Basic, RowOperation)
{
    Matrix m1 = {{1, 2}, {3, 4}, {5, 6}};
    Matrix m2 = {{0, 0}, {-1, -1}, {-2, -2}};
    BlockView b = m2.Row(1);
    ASSERT_EQ(m2.Row(1), Matrix({{-1, -1}}));
    m1.Row(1) = m2.Row(1);
    cout << m1;
}

