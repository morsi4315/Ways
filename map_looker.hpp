#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <math.h>
#include <iomanip>
#include "library/stb_image.h"

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

    Map(const string& inputFilename){
        int channels;
        unsigned char* data = stbi_load(inputFilename.c_str(), &width, &height, &channels, 1);

        if (!data){
            cerr << "Ошибка загрузки изображения: " << stbi_failure_reason() << endl;
            width = height = kol_verts = 0;
            scale = 1.0f;
            return;
        }

        kol_verts = width * height;
        scale = 1.0f;
        verts.resize(kol_verts);

        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                verts[y*width + x].z_cord = data[y*width + x];
                verts[y*width + x].y_cord = y;
                verts[y*width + x].x_cord = x;
            }
        }

        stbi_image_free(data);
    }

    Point& at(int y, int x)
    {
        return verts[y*width + x];
    }
};

#endif


  /*
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
    */