#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <math.h>
#include <iomanip>

#include "common_types.hpp"
#include "map_looker.hpp"
#include "costs.hpp"

using namespace std;

#ifndef ALGORITM_H
#define ALGORITM_H

void Brezenhem(Map map, vector<Point>& order, Point point0, Point point1)
{
  int x0 = point0.x_cord;
  int y0 = point0.y_cord;
  int x1 = point1.x_cord;
  int y1 = point1.y_cord;
  int A, B, sign;
  A = y1 - y0;
  B = x0 - x1;
  if (abs(A) > abs(B))
    sign = 1;
  else
    sign = -1;
  int signa, signb;
  if (A < 0)
    signa = -1;
  else
    signa = 1;
  if (B < 0)
    signb = -1;
  else
    signb = 1;
  int f = 0;
  order.push_back(map.at(y0, x0));
  int x = x0, y = y0;
  if (sign == -1)
  {
    do {
      f += A * signa;
      if (f > 0)
      {
        f -= B * signb;
        y += signa;
      }
      x -= signb;
      order.push_back(map.at(y, x));
    } while (x != x1 || y != y1);
  }
  else
  {
    do {
      f += B * signb;
      if (f > 0) {
        f -= A * signa;
        x -= signb;
      }
      y += signa;
      order.push_back(map.at(y, x));
    } while (x != x1 || y != y1);
  }
}

 void step(Map& map, Queue& queue, Point point, Point point_new, char cost_parametr){
    long double step;
    step = point.steps + (found_cost(point, point_new, cost_parametr));
    if ((point_new.steps > step ) or (point_new.steps == -1)){
        map.at(point_new.y_cord, point_new.x_cord).steps = step;
        map.at(point_new.y_cord, point_new.x_cord).from = point_new.from;
        if (point_new.visited == false){
            queue.enqueue(map.at(point_new.y_cord, point_new.x_cord));
            map.at(point_new.y_cord, point_new.x_cord).visited = true;
        }
    }
 }

 void build_way(Map& map, vector<Point>& way, Point& fin)
{
    Point temp;
    temp = map.at(fin.y_cord, fin.x_cord);
    way.push_back(temp);
    while (temp.from != Directs::NONE)
    {

        switch(temp.from)
        {
            case Directs::DOWN:
                temp = map.at(temp.y_cord - 1, temp.x_cord);
                break;
            case Directs::UP:
                temp = map.at(temp.y_cord + 1, temp.x_cord);
                break;
            case Directs::LEFT:
                temp = map.at(temp.y_cord, temp.x_cord - 1);
                break;
            case Directs::RIGHT:
                temp = map.at(temp.y_cord, temp.x_cord + 1);
                break;
            case Directs::UP_R:
                temp = map.at(temp.y_cord + 1, temp.x_cord + 1);
                break;
            case Directs::UP_L:
                temp = map.at(temp.y_cord + 1, temp.x_cord - 1);
                break;
            case Directs::DOWN_L:
                temp = map.at(temp.y_cord - 1, temp.x_cord - 1);
                break;
            case Directs::DOWN_R:
                temp = map.at(temp.y_cord - 1, temp.x_cord + 1);
                break;
        }
        way.push_back(temp);
    }
}

void aprocs(Map& map,  vector<Point>& way){
    vector<Point> new_way;
    int first_i = 0;
    while(true){
        int i = first_i + 2;
        if (i >= way.size()){
            for (int j = first_i; j < way.size(); j++ ){
                new_way.push_back(way[j]);
            }
            break;
        }
        float first_ugle = way[first_i].z_cord - way[first_i + 1].z_cord;
        vector<Point> last_order;
        while(true){
            vector<Point> order;
            Brezenhem(map, order, way[first_i], way[i]);
//
//
            bool check = true;
            for (int j = 0; j < order.size() - 1; j++){
                float actual_ugle = order[j].z_cord - order[j + 1].z_cord;
                if (actual_ugle != first_ugle){
                    check = false;
                    break;
                }
            }
            if (check == false){break;}
            i++;
            last_order.clear();
            last_order = order;
            if (i == way.size()){break;}
        }
//

        for(int j = 0; j < last_order.size(); j ++){
            new_way.push_back(last_order[j]);
        }
        last_order.clear();
//

        first_i = i;
    }
    way = new_way;
}

void found_way(Map& map, Point& star, Point fin, char cost_parametr)
{
    Queue queue;
    Point temp;
    vector<Point> order;
    queue.enqueue(star);
    while (!queue.isEmpty()){
        temp = queue.peek();
        Point temp_2;
        queue.dequeue();
        temp.visited = false;
        order.clear();
        if ((temp.from != Directs::RIGHT) and (temp.x_cord + 1 < map.width))
        {
            temp_2 = map.at(temp.y_cord, temp.x_cord + 1);
            temp_2.from = Directs::LEFT;
            order.push_back(temp_2);
        };

        if ((temp.from != Directs::UP) and (temp.y_cord + 1 < map.height))
        {
            temp_2 = map.at(temp.y_cord + 1, temp.x_cord);
            temp_2.from = Directs::DOWN;
            order.push_back(temp_2);
        }

        if ((temp.from != Directs::LEFT) and (temp.x_cord - 1 >= 0))
        {
            temp_2 = map.at(temp.y_cord, temp.x_cord - 1);
            temp_2.from = Directs::RIGHT;
            order.push_back(temp_2);
        }

        if ((temp.from != Directs::DOWN) and (temp.y_cord - 1 >= 0))
        {
            temp_2 = map.at(temp.y_cord - 1, temp.x_cord);
            temp_2.from = Directs::UP;
            order.push_back(temp_2);
        }

        if ((temp.from != Directs::UP_R) and (temp.x_cord + 1 < map.width) and (temp.y_cord + 1 < map.height))
        {
            temp_2 = map.at(temp.y_cord + 1, temp.x_cord + 1);
            temp_2.from = Directs::DOWN_L;
            order.push_back(temp_2);
        }

        if ((temp.from != Directs::DOWN_R) and (temp.x_cord + 1 < map.height) and (temp.y_cord - 1 >= 0))
        {
            temp_2 = map.at( temp.y_cord - 1, temp.x_cord + 1);
            temp_2.from = Directs::UP_L;
            order.push_back(temp_2);
        }

        if ((temp.from != Directs::DOWN_L) and (temp.x_cord - 1 >= 0) and  (temp.y_cord - 1 >= 0))
        {
            temp_2 = map.at(temp.y_cord - 1, temp.x_cord - 1);
            temp_2.from = Directs::UP_R;
            order.push_back(temp_2);
        }

        if ((temp.from != Directs::UP_L) and (temp.x_cord - 1 >= 0) and (temp.y_cord + 1 < map.height))
        {
            temp_2 = map.at(temp.y_cord + 1, temp.x_cord - 1);
            temp_2.from = Directs::DOWN_R;
            order.push_back(temp_2);
        }
        
        for (int i = 0; i < order.size(); i++)
        {
            step(map, queue, temp, order[i], cost_parametr);
        }
    }
    vector<Point> way;
    build_way(map, way, fin);

    aprocs(map, way);
    cout<<"Полученный путь: "<<endl;
    cout << "============" << endl;
    for (int i = 0; i < way.size(); i++){
        cout<<way[i].x_cord<<";"<<way[i].y_cord<<endl;
    }
}

#endif
