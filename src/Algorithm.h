//
// Created by wangnan on 16-9-20.
//

#ifndef CPP_ALGORITHM_H
#define CPP_ALGORITHM_H
#include "Matrix.h"
namespace Linear
{
    enum QRMethod
    {
        GramSchimdt,
        HouseholderReflection,
    };
    void QRFactorization(const Matrix &mi, Matrix &mq, Matrix &mr, QRMethod method);
    void QRFactorizationGS(const Matrix &mi, Matrix &mq, Matrix &mr);
    void QRFactorizationHR(const Matrix &mi, Matrix &mq, Matrix &mr);
}

#endif //CPP_ALGORITHM_H
