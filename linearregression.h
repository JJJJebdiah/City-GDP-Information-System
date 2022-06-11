#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H


#include<QList>

class LeastSquare{
    double a, b;
public:
    LeastSquare(const QList<double>& x, const QList<double>& y);


    double getY(const double x) const
    {
        return a*x + b;
    }


};




#endif // LINEARREGRESSION_H
