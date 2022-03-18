#include <iostream>
#include<cmath>
using namespace std;
struct point
{
    double x;//координата х
    double y;//координата y
    double f;//значение функции в точке
   
};

double function(double x, double y)
{
    //return x * x + x * y + y * y - 6 * x - 9 * y;
    return x * x - x * y + y * y + 9 * x - 6 * y + 20;
    //return -1 * (3 / (1 + pow(x - 2, 2) + pow((y - 2) / 2, 2)) + 2 / (1 + pow((x - 2) / 3, 2) + pow(y - 3, 2)));
}
double eps = 0.0001;


#include"Method_0.h"
#include"Method_variable_metric.h"
int main()
{
    point point;
    double eps_f, eps_i;
    std::cout << "Enter X0: ";
    std::cin >> point.x>>point.y;
    method_0 create_method0(point);
    method_variable_metric create_metod_variable(point);
}
