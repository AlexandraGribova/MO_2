#include <iostream>
#include<cmath>
using namespace std;
int count_f;
struct point
{
    double x;//координата х
    double y;//координата y
    double f;//значение функции в точке
   
};

double function(double x, double y)
{
   //return -1 * (3 / (1 + pow(x - 2, 2) + pow((y - 2) / 2, 2)) + 2 / (1 + pow((x - 2) / 3, 2) + pow(y - 3, 2)));
   return 100*(y-x)*(y-x)+(1-x)*(1-x);
   //return x * x - x * y + y * y - 6 * y + 9 * x + 20;
}
double eps_f = 1E-3;
double eps_i = 1E-3;

#include"Method_0.h"
#include"Method_variable_metric.h"
int main()
{
    point point;
    std::cout << "Enter X0: ";
    std::cin >> point.x>>point.y;
    method_0 create_method0(point);
    //method_variable_metric create_metod_variable(point);
    cout << endl<<count_f << endl;
}
