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

void Brezenhem(Map& map, vector<Point>& order, Point point0, Point point1) {
    int x0 = point0.x_cord, y0 = point0.y_cord;
    int x1 = point1.x_cord, y1 = point1.y_cord;

    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    int x = x0, y = y0;
    while (true) {
        // проверка границ
        order.push_back(map.at(y, x));

        if (x == x1 && y == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx)  { err += dx; y += sy; }
    }
}

void Brezenhem2(Map map, vector<Point>& order, Point point0, Point point1)
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
        if (map.at(point_new.y_cord, point_new.x_cord).visited == false){
            map.at(point_new.y_cord, point_new.x_cord).visited = true;
            queue.enqueue(map.at(point_new.y_cord, point_new.x_cord));
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

void massravmass(vector<Point>& a, vector<Point> b){
    a.clear();
    for(int i = 0; i < b.size(); i++){
        a.push_back(b[i]);
    }
}

void aprocs(Map& map, vector<Point>& way){
    cout<<way[0].x_cord << " ; " << way[0].y_cord << endl;
    int i = 0;
    int j = i + 2;
    while (j < way.size() ){
        bool check = true;
        while (check and j < way.size()){
            vector<Point> brh;
            Brezenhem(map, brh, way[i], way[j]);
            float first_ugle = brh[0].z_cord - brh[1].z_cord;
            for (int n = 1; n < brh.size() - 1; n++){
                float actual_ugle = brh[n].z_cord - brh[n + 1].z_cord;
                if (actual_ugle != first_ugle){
                    check = false;
                    break;
                }
            }
            j++;
            brh.clear();
        }
        j--;
        if ((check == false) and (j - i > 2)){
            vector<Point> way_new;
            for (int r = 0; r < i; r++){
                way_new.push_back(way[r]);
            }
            vector<Point> brh;
            Brezenhem(map, brh, way[i], way[j - 1]);
            for (int r = 0; r < brh.size(); r++){
                way_new.push_back(brh[r]);
            }
            for (int r = j; r < way.size(); r++){
                way_new.push_back(way[r]);
            }
            massravmass(way, way_new);
            way_new.clear();
            cout<<"way = " << way.size() <<" i = " << i << " j = " << j <<endl;
        }
        else if (check == true){
            cout<<"!"<<endl;
            vector<Point> way_new;
            for (int r = 0; r < i; r++){
                way_new.push_back(way[r]);
            }
            vector<Point> brh;
            Brezenhem(map, brh, way[i], way[j]);
            cout<<brh.size()<<endl;
            for (int r = 0; r < brh.size(); r++){
                way_new.push_back(brh[r]);
            }
            massravmass(way, way_new);
            way_new.clear();
            break;
        }
    i++;
    j = i + 2;
    }
}

void found_way(Map& map, Point& star, Point fin, char cost_parametr)
{
    cout<<"<   > Построение сетки" << endl;
    Queue queue;
    Point temp;
    vector<Point> order;
    queue.enqueue(star);
    while (!queue.isEmpty()){
        temp = queue.peek();
        Point temp_2;
        queue.dequeue();
        //temp.visited = false;
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

        if ((temp.from != Directs::DOWN_R) and (temp.x_cord + 1 < map.width) and (temp.y_cord - 1 >= 0))
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
    cout<<"<=  > Поиск обратного пути..." << endl;
    vector<Point> way;
    build_way(map, way, fin);
    cout<<"<== > Сглаживание..." << endl;
    aprocs(map, way);
    cout<<"<===> Готово!" << endl;
    cout<<"Полученный путь: "<<endl;
    cout << "============================" << endl;
    ofstream file("way.obj");
    for (int i = 0; i < way.size(); i++){
        file<<way[i].x_cord<<";"<<way[i].y_cord<<endl;
        //cout<<way[i].x_cord<<";"<<way[i].y_cord<<endl;
    }
    file.close();
}

#endif
