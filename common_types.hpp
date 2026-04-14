#include <iostream>
#include <fstream>

using namespace std;

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

enum class Directs {NONE = 0, DOWN = 2, LEFT = 4, RIGHT = 6, UP = 8, UP_R = 9, UP_L = 7, DOWN_R = 3, DOWN_L = 1};

//структуры и классы
struct Point
{
    int x_cord = 0;
    int y_cord = 0;
    float z_cord = 0;

    Directs from = Directs::NONE;
    long double steps = -1;
    bool visited = false;
};

//Очередь
class Node {
public:
    Point& data;
    Node* next;

    Node(Point& value) :
    data(value), next(nullptr)
    {}
};

class Queue
{
    private:
        Node* front;
        Node* rear;
    public:
        Queue()
        {
            front=nullptr;
            rear = nullptr;
        }

    void enqueue(Point& value){    ///Добавить в очередь
        Node* newNode = new Node(value);
        if (rear == nullptr){
            front = rear = newNode;
        }else{
            rear->next = newNode;
            rear=newNode;
        }
    };

    bool isEmpty(){ /////Пустая ли очередь
        return front==nullptr;
    };

    void dequeue(){    ///// Удалить эелемент из очереди
        if(isEmpty()){
            std::cout<<"Очередь пуста"<<std::endl;
            return;
        }

        Node* temp=front;
        front=front->next;
        if (front==nullptr){
            rear=nullptr;
        }
        delete temp;
    };

    Point peek(){    ////Возвращает первый элемент очереди.
        return(front->data);
    };

};

#endif
