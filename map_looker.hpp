#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <math.h>
#include <iomanip>

#include "common_types.hpp"

using namespace std;

#ifndef MAP_LOOKER_H
#define MAP_LOOKER_H

struct Map
{
    int width;
    int height;
    int kol_verts;
    float scale;

    vector<Point> verts;

    //Map(const string& inputFilename){}

    Map(const int w, const int h){
        verts.resize(w*h);
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
            {
                //
                if ((i > 2) and (i < 5) and (j > 2) and (j < 6)){
                     verts[i*w + j].x_cord = i;
                    verts[i*w + j].y_cord = j;
                    verts[i*w + j].z_cord = 100;
                    verts[i*w + j].steps = (-1);
                }
                else {
                //
                verts[i*w + j].x_cord = i;
                verts[i*w + j].y_cord = j;
                verts[i*w + j].z_cord = 0;
                verts[i*w + j].steps = (-1);
                }

            }
        width = w;
        height = h;
        kol_verts = w*h;
    }

    Point& at(int x, int y)
    {
        return verts[y*width + x];
    }
};

#endif
