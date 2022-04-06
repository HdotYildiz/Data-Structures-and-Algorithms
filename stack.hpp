#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

class StackArray
{
private:
    int* array_;
    size_t array_size_=0;
    int top_index_=-1;

public:
	StackArray(int maxsize);

    void push(int data);
    void pop();
    int top();
    bool is_empty();
    void print();
};

#endif