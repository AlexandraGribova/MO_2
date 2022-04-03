#pragma once
#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;

class method_0
{
    double d1(double t)
    {
        return((2 * t + sqrt(t) - t) / 2 * sqrt(2));
    }
    double d2(double t)
    {
        return(t/(2*sqrt(2)*(sqrt(3)-1)));
    }

    point create_point(point point0, point vector)//создание доп 2 точек
    {
        point0.x = point0.x + 0.05*vector.x;
        point0.y = point0.y + 0.05* vector.y;
        return point0;
    }
    void sort(point* point_array)
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
    point elongation(point new_point, point mid, double gamma)//растяжение
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
            point_array[i].x = point_array[0].x + 0.5 * (point_array[i].x - point_array[0].x);
            point_array[i].y = point_array[0].y + 0.5 * (point_array[i].y - point_array[0].y);
        }
        point_array[1].f = function(point_array[1].x, point_array[1].y);
        point_array[2].f = function(point_array[2].x, point_array[2].y);
    }

    point compression(point worst, point mid, double betta)
    {
        worst.x = mid.x + betta * (worst.x - mid.x);
        worst.y = mid.y + betta * (worst.y - mid.y);
        worst.f = function(worst.x, worst.y);
        count_f++;
        return worst;
    }

    void reflection(double alpha, double betta, double gamma, point mid, point* point_array) //отражение худшей точки относительно mid
    {
        point new_point, point;//надо ли point вообще?
        new_point.x = mid.x + alpha * (mid.x - point_array[2].x);
        new_point.y = mid.y + alpha * (mid.y - point_array[2].y);
        new_point.f = function(new_point.x, new_point.y);
        count_f++;
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
    
public:
    method_0(point point1)
    {
        point point_array[3], mid, point_prew_array[3];//массив нужен чтобы потом сделать в нем сортровку
        int iter;
        double flag1;
        double alpha = 1;
        double betta = 0.5;
        double gamma = 2;
        bool flag_i= true, flag_f=true;
        int k = 0;
        double t = 1;
        point_array[0] = point1;
       point_array[1] = { point_array[0].x+d1(t),point_array[0].y + d2(t) };
        point_array[2] = { point_array[0].x + d2(t),point_array[0].y + d1(t) };
        point_array[0].f = function(point_array[0].x, point_array[0].y);
        point_array[1].f = function(point_array[1].x, point_array[1].y);
        point_array[2].f = function(point_array[2].x, point_array[2].y);
        count_f = 3;
        for (iter = 1; flag_f; iter++)
        {
            
            sort(point_array);//сортировка по возрастанию (0 эл-т самый маленький)
            for (int i = 0; i < 3; i++) point_prew_array[i] = point_array[i];
            mid = { (point_array[0].x + point_array[1].x) / 2, (point_array[0].y + point_array[1].y) / 2 };//середина отрезка по меньшим точкам
            mid.f = function(mid.x, mid.y);
            count_f++;
            reflection(alpha, betta, gamma, mid, point_array);
            flag1 = sqrt(pow(point_array[0].f,2) - pow(mid.f,2))/3;
            if (flag1 < eps_f) flag_f = false;
            cout << iter<<": Direction: (" << mid.x - point_array[2].x << " , " << mid.x - point_array[2].x << ") "<<endl;
            for(int i=0; i<3; i++) cout << setprecision(11)<< " (" << abs(point_array[i].x - point_prew_array[i].x) << ", " << abs(point_array[i].y - point_prew_array[i].y) << " , " << abs(point_array[i].f - point_prew_array[i].f)<<")  "<<endl;
            cout << setprecision(11) <<"("<< point_array[0].x << ", " << point_array[0].y << ") " << point_array[0].f << endl;
           
        }
        cout << setprecision(11) << point_array[0].x << " " << point_array[0].y << " " << point_array[0].f<<endl;
        std::cout << "Iter: " << iter;
    }

};

