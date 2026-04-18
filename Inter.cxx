#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <math.h>
#include <iomanip>
#include "common_types.hpp"
#include "map_looker.hpp"
#include "algoritm.hpp"


using namespace std;

int main(){
    setlocale(LC_ALL, "Russian");                   //Локализация и приветствие 
    cout << endl << "Ways         " << endl << "Эта программа строит оптимальный путь на местности." << endl << "============================================" << endl << endl;

     Point star, fin;

    //Map map("map4.png");

    Map map(100, 100);


    cout << "Координаты старта:" << "\n";
    cin >> star.x_cord;
    cin >> star.y_cord;

    cout << "\nКоординаты финиша" << "\n";
    cin >> fin.x_cord;
    cin >> fin.y_cord;
    cout <<endl;



    if ((star.x_cord < 0) or (star.y_cord < 0) or (star.x_cord > map.width) or (star.y_cord > map.height))
    {
        cerr <<"Error: Начало пути за пределом карты."<< endl;
        return 0;
    }
    if ((fin.x_cord < 0) or (fin.y_cord < 0) or (fin.x_cord > map.width) or (fin.y_cord > map.height))
    {
        cerr <<"Error: Финиш пути за пределом карты."<< endl;
        return 0;
    }
    star.z_cord = map.at(star.y_cord, star.x_cord).z_cord;
    star.steps = 0;
    map.at(star.y_cord, star.x_cord).steps = 0;
    fin.z_cord = map.at(fin.y_cord, fin.x_cord).z_cord;

    found_way(map, star, fin, 's');


    //logs
    // for (int i = 20; i >= 0; i--){
    //     for (int j = 20; j >= 0; j--){
    //         cout << map.at(i, j).steps << ";";
    //     }
    //     cout << "\n";
    // }
}
