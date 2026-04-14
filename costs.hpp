#include <math.h>
#include <iomanip>

#ifndef COSTS_H
#define COSTS_H



long double found_cost(Point A, Point B, char cost_parametr) //поиск цены
{
    switch(cost_parametr){
        case 's':
            long double z;
            float x;
            z = B.z_cord - A.z_cord;
            if ((A.x_cord != B.x_cord) and (A.y_cord != B.y_cord)){
                //x = sqrt(2);
                //cout << x << endl;
                x = 2;
            }
            else
            {
                x = 1;
            }
            return sqrt(pow(x, 2) + pow(z, 2));
            break;

        default:
            return 1;
            break;
    }
}
#endif
