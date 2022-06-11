#include "linearregression.h"

#include <QFile>
#include <QTextStream>

LeastSquare::LeastSquare(const QList<double> &x, const QList<double> &y)
{
    {
        double t1=0, t2=0, t3=0, t4=0;
        for(int i=0; i<x.size(); ++i)
        {
            t1 += x[i]*x[i];
            t2 += x[i];
            t3 += x[i]*y[i];
            t4 += y[i];
        }
        a = (t3*x.size() - t2*t4) / (t1*x.size() - t2*t2);
        //b = (t4 - a*t2) / x.size();
        b = (t1*t4 - t2*t3) / (t1*x.size() - t2*t2);
    }
}

#define Length 10
double fun(int n, double array[Length][Length])
{
    int ii, jj, k, u;
    int iter = 0;  //记录行变换的次数（交换）
    double det1 = 1, yin;

    for (ii = 0; ii < n; ii++)
    {
        for (k = ii + 1; k < n; k++)
        {
            yin = -1 * array[k][ii] / array[ii][ii];

            for (u = 0; u < n; u++)
            {
                array[k][u] = array[k][u] + array[ii][u] * yin;
            }
        }
    }
    for (ii = 0; ii < n; ii++)  //求对角线的积 即 行列式的值
        det1 = det1 * array[ii][ii];
    //行变换偶数次符号不变
    if (iter % 2 == 1)
        det1 = -det1;
    return (det1);
}
void  LeastSquareMethod(int n, int m, double* x, double* y)
{
    int i, j;
    double temp[Length][Length];
    double d[Length], arr[Length][Length];
    double tempsumx, tempsumy;
    double sumx[Length] = { 0.0 }, sumy[Length] = { 0.0 };
    for (i = 0; i < 2 * m; i++) {
        tempsumx = 0.0;
        tempsumy = 0.0;
        for (j = 0; j < n; j++) {
            tempsumx += pow(x[j], i + 1);
            tempsumy += pow(x[j], i) * y[j];
        }
        sumx[i] = tempsumx;
        sumy[i] = tempsumy;
    }
    int a = 0;
    //上三角
    for (i = 1; i < m + 1; i++) {
        temp[0][0] = n;
        for (j = 0; j <= i; j++) {
            temp[j][i - j] = sumx[i - 1];
            a = i - 1;
        }
    }
    //下三角
    for (j = 1; j <= m; j++) {
        for (i = 0; i <= m - j; i++) {
            temp[i + j][m - i] = sumx[a + j];
        }
    }
    //临时赋值
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            arr[i][j] = temp[i][j];
        }
    }
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            arr[j][i] = sumy[j];
        }
        d[i + 1] = fun(m + 1, arr);//求行列式的值
        for (int p = 0; p <= m; p++) {
            for (int q = 0; q <= m; q++) {
                arr[p][q] = temp[p][q];//恢复被改变过的arr
            }
        }
    }
    d[0] = fun(m + 1, temp);
    double z[Length];
    for (i = 0; i <Length; i++) {
        z[i]=0;
    }
    for (i = 0; i <= m; i++) {
        z[i] = d[i + 1] / d[0];
    }
    char cha = '+';
    QTextStream cout;
    cout << "拟合数据的" << m << "次多项式为:P" << m << "(x)=" << z[0];
    for (i = 1; i <= m; i++) {
        if (z[i] < 0)
            cha = ' ';
        cout << cha << z[i] << "x^" << i;
    }
    cout << Qt::endl;
}
int op() {
    QTextStream cout,cin;
    int n, m, xi, i;
    double x[Length], y[Length];
    n = 10;
    for (i = 0; i < n; i++) {
        cout << "x[" << i << "]=";
        cin >> x[i];
        cout << "y[" << i << "]=";
        cin >> y[i];
    }
    m = 3;
    LeastSquareMethod(n, m, x, y);
    system("pause");
    return 0;
}
