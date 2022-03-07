#include <iostream>
#include<cmath>
using namespace std;
double eps=0.0001;

struct point
{
    double x;//координата х
    double y;//координата y
    double f;//значение функции в точке
};

double function(double x, double y)
{
    return x * x + x * y + y * y - 6 * x - 9 * y;
    //return 3 / (1 + pow(x - 2, 2) + pow((y - 2) / 2, 2)) + 2 / (1 + pow((x - 2) / 3, 2) + pow(y - 3, 2));
}

point create_point(point point0, point vector)//создание доп 2 точек
{
    point0.x = point0.x + 0.05 * vector.x;
    point0.y = point0.y + 0.05 * vector.y;
    return point0;
}
void sort(point * point_array)
{
    point tmp;
    for (int i = 0; i < 3; i++) {
        for (int j = 2; j >= (i + 1); j--) {
            if (point_array[j].f < point_array[j - 1].f) {
                tmp = point_array[j];
                point_array[j] = point_array[j - 1];
                point_array[j - 1] = tmp;
            }
        }
    }
}
point elongation(point new_point,point mid, double gamma)//растяжение
{
    new_point.x = mid.x + gamma * (new_point.x - mid.x);
    new_point.y = mid.y + gamma * (new_point.y - mid.y);
    new_point.f = function(new_point.x, new_point.y);
    return new_point;
}

void reduction(point *point_array)
{
    for (int i = 1; i < 3; i++)
    {
        point_array[i].x = point_array[0].x + 0.5 * (point_array[i].x- point_array[0].x);
        point_array[i].y = point_array[0].y + 0.5 * (point_array[i].y - point_array[0].y);
    }
}
point compression(point worst, point mid, double betta)
{
    worst.x = mid.x + betta * (worst.x - mid.x);
    worst.y = mid.y + betta * (worst.y - mid.y);
    worst.f = function(worst.x, worst.y);
    return worst;
}

void reflection(double alpha, double betta, double gamma, point mid, point *point_array) //отражение худшей точки относительно mid
{
    point new_point, point;//надо ли point вообще?
    new_point.x = mid.x + alpha * (mid.x - point_array[2].x);
    new_point.y = mid.y + alpha * (mid.y - point_array[2].y);
    new_point.f = function(new_point.x, new_point.y);
    while (true)
    {
        if (new_point.f >= point_array[2].f)
        { 
            reduction(point_array);//редукция
            break;
        }
        if (new_point.f <= point_array[0].f)//если меньше минимального на k-этапе
        {
            point = elongation(new_point, mid, gamma);//растяжение
            if (point.f < point_array[0].f)
            {
                point_array[2] = point_array[1];
                point_array[1] = point_array[0];
                point_array[0] = point;
            }
            else
            {
                point_array[2] = point_array[1];
                point_array[1] = point_array[0];
                point_array[0] = new_point;
            }
            break;
        }
        if (new_point.f > point_array[1].f && new_point.f <= point_array[2].f)//между двумя худшими точками
        {
            point_array[2] = compression(point_array[2], mid, betta);//сжатие надо ли возвращть вообще??
            break;
        }
        if (new_point.f > point_array[0].f && new_point.f <= point_array[1].f)
        {
            point_array[2] = new_point;
            break;
        }
    }
}

void method_0(point point1)
{
    point point_array[3], vector, mid;//массив нужен чтобы потом сделать в нем сортровку
    double alpha = 1;
    double betta = 0.5;
    double gamma = 2;
    double flag;
    int k = 0;
    point_array[0] = point1;
    point_array[1] = create_point(point1, { 0,1 });//Инициализация 2 оставшихся точек. Может быть нужно не так это делать
    point_array[2] = create_point(point1, { 1,0 });
   // point_array[0] = { 0,0 }; point_array[1] = { 1,0 }; point_array[2] = { 0,1 };//Это костыль для теста можно удалить
    point_array[0].f = function(point_array[0].x, point_array[0].y);
    point_array[1].f = function(point_array[1].x, point_array[1].y);
    point_array[2].f = function(point_array[2].x, point_array[2].y);
    for (int iter = 1, flag=1; flag > eps; iter++)
    {
        flag = 0;
        sort(point_array);//сортировка по возрастанию (0 эл-т самый маленький)
        mid = { (point_array[0].x + point_array[1].x) / 2, (point_array[0].y + point_array[1].y) / 2 };//середина отрезка по меньшим точкам
        mid.f = function(mid.x, mid.y);
        for (int i = 0; i < 3; i++)           flag += point_array[i].f - mid.f;
        flag = sqrt(flag / 3);
        reflection(alpha, betta, gamma, mid, point_array);
        std::cout << point_array[0].f << " " << point_array[1].f << " " << point_array[2].f<<endl;
    }
    std::cout << point_array[0].x << " " << point_array[0].y << " " << point_array[0].f;
}
int main()
{
    point point1;
    double eps_f, eps_i;
    std::cout << "Enter X0: ";
    std::cin >> point1.x>>point1.y;
    method_0(point1);
}
