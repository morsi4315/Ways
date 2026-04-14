#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <math.h>
#include <iomanip>
#include "common_types.hpp"

using namespace std;

#ifndef ALGORITM_ORDER_NEIGHBOR_H
#define ALGORITM_ORDER_NEIGHBOR_H

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


 //Первый предложенный, но не работающий метод
void add_in_order(vector<Point>& order, Point fin, Point point, Directs from){
    int pos = 0;
    for (int i = 0; i < order.size(); i++){
        int d_new_i = abs(point.x_cord - fin.x_cord);
        int d_new_j = abs(point.y_cord - fin.y_cord);
        int d_old_i = abs(order[i].x_cord - fin.x_cord);
        int d_old_j = abs(order[i].y_cord - fin.y_cord);
        int d_i = d_old_i - d_new_i;
        int d_j = d_old_j - d_new_j;
        if (((d_i >= 0) and (d_j >= 0)) or (d_i == (-1)*d_j)) {break;};
        pos++;
    }
    point.from = from;
    order.insert(order.begin() + pos, point);
}

/*
void order_neighbor(vector<Point>& order, Map map, Point fin, Point point){

    if ((point.from != Directs::RIGHT) and (point.x_cord + 1 < map.width))
    { add_in_order(order, fin, map.at(point.y_cord, point.x_cord + 1), Directs::LEFT); };

    if ((point.from != Directs::UP_R) and (point.x_cord + 1 < map.width) and (point.y_cord + 1 < map.height))
    { add_in_order(order, fin, map.at(point.y_cord + 1, point.x_cord + 1), Directs::DOWN_L); };

    if ((point.from != Directs::DOWN_R) and (point.x_cord + 1 < map.height) and (point.y_cord - 1 >= 0))
    { add_in_order(order, fin, map.at(point.y_cord - 1, point.x_cord + 1), Directs::UP_L); };

    if ((point.from != Directs::UP) and (point.y_cord + 1 < map.height))
    { add_in_order(order, fin, map.at(point.y_cord + 1, point.x_cord), Directs::DOWN); };

    if ((point.from != Directs::DOWN) and (point.y_cord - 1 >= 0))
    { add_in_order(order, fin, map.at(point.y_cord - 1, point.x_cord), Directs::UP); };

    if ((point.from != Directs::LEFT) and (point.x_cord - 1 >= 0))
    { add_in_order(order, fin, map.at(point.y_cord, point.x_cord - 1), Directs::RIGHT); };

    if ((point.from != Directs::UP_L) and (point.x_cord - 1 >= 0) and (point.y_cord + 1 < map.height))
    { add_in_order(order, fin, map.at(point.y_cord + 1, point.x_cord - 1), Directs::DOWN_R); };

    if ((point.from != Directs::DOWN_L) and (point.x_cord - 1 >= 0) and  (point.y_cord - 1 >= 0))
    { add_in_order(order, fin, map.at(point.y_cord - 1, point.x_cord - 1), Directs::UP_R); };
}*/

void order_neighbor(vector<Point>& order, Map map, Point fin, Point point, int order_q){
    Point temp;
    if (order_q % 2 == 0)
    {
        if ((point.from != Directs::RIGHT) and (point.x_cord + 1 < map.width))
        {
            temp = map.at(point.y_cord, point.x_cord + 1);
            temp.from = Directs::LEFT;
            order.push_back(temp);
        };

        if ((point.from != Directs::UP) and (point.y_cord + 1 < map.height))
        {
            temp = map.at(point.y_cord + 1, point.x_cord);
            temp.from = Directs::DOWN;
            order.push_back(temp);
        }

        if ((point.from != Directs::LEFT) and (point.x_cord - 1 >= 0))
        {
            temp = map.at(point.y_cord, point.x_cord - 1);
            temp.from = Directs::RIGHT;
            order.push_back(temp);
        }

        if ((point.from != Directs::DOWN) and (point.y_cord - 1 >= 0))
        {
            temp = map.at(point.y_cord - 1, point.x_cord);
            temp.from = Directs::UP;
            order.push_back(temp);
        }

        if ((point.from != Directs::UP_R) and (point.x_cord + 1 < map.width) and (point.y_cord + 1 < map.height))
        {
            temp = map.at(point.y_cord + 1, point.x_cord + 1);
            temp.from = Directs::DOWN_L;
            order.push_back(temp);
        }

        if ((point.from != Directs::DOWN_R) and (point.x_cord + 1 < map.height) and (point.y_cord - 1 >= 0))
        {
            temp = map.at( point.y_cord - 1, point.x_cord + 1);
            temp.from = Directs::UP_L;
            order.push_back(temp);
        }

        if ((point.from != Directs::DOWN_L) and (point.x_cord - 1 >= 0) and  (point.y_cord - 1 >= 0))
        {
            temp = map.at(point.y_cord - 1, point.x_cord - 1);
            temp.from = Directs::UP_R;
            order.push_back(temp);
        }

        if ((point.from != Directs::UP_L) and (point.x_cord - 1 >= 0) and (point.y_cord + 1 < map.height))
        {
            temp = map.at(point.y_cord + 1, point.x_cord - 1);
            temp.from = Directs::DOWN_R;
            order.push_back(temp);
        }
    }
    else {
            if ((point.from != Directs::UP_R) and (point.x_cord + 1 < map.width) and (point.y_cord + 1 < map.height))
        {
            temp = map.at(point.y_cord + 1, point.x_cord + 1);
            temp.from = Directs::DOWN_L;
            order.push_back(temp);
        }

        if ((point.from != Directs::DOWN_R) and (point.x_cord + 1 < map.height) and (point.y_cord - 1 >= 0))
        {
            temp = map.at( point.y_cord - 1, point.x_cord + 1);
            temp.from = Directs::UP_L;
            order.push_back(temp);
        }

        if ((point.from != Directs::DOWN_L) and (point.x_cord - 1 >= 0) and  (point.y_cord - 1 >= 0))
        {
            temp = map.at(point.y_cord - 1, point.x_cord - 1);
            temp.from = Directs::UP_R;
            order.push_back(temp);
        }

        if ((point.from != Directs::UP_L) and (point.x_cord - 1 >= 0) and (point.y_cord + 1 < map.height))
        {
            temp = map.at(point.y_cord + 1, point.x_cord - 1);
            temp.from = Directs::DOWN_R;
            order.push_back(temp);
        }

    if ((point.from != Directs::RIGHT) and (point.x_cord + 1 < map.width))
        {
            temp = map.at(point.y_cord, point.x_cord + 1 );
            temp.from = Directs::LEFT;
            order.push_back(temp);
        };

        if ((point.from != Directs::UP) and (point.y_cord + 1 < map.height))
        {
            temp = map.at(point.y_cord + 1, point.x_cord);
            temp.from = Directs::DOWN;
            order.push_back(temp);
        }

        if ((point.from != Directs::LEFT) and (point.x_cord - 1 >= 0))
        {
            temp = map.at(point.y_cord, point.x_cord - 1);
            temp.from = Directs::RIGHT;
            order.push_back(temp);
        }

        if ((point.from != Directs::DOWN) and (point.y_cord - 1 >= 0))
        {
            temp = map.at(point.y_cord - 1, point.x_cord);
            temp.from = Directs::UP;
            order.push_back(temp);
        }
    }
}


#endif
