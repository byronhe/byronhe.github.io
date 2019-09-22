#include <stdint.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "func.h"
using namespace std;

int original_func(ST1 * para1,ST1 para2,void * para3){
    cout<<__func__<<"\tcalled! "
        <<" a+a "<<para1->a+para2.a
        <<" b+b "<<para1->b+para2.b
        <<" c+c "<<para1->c<<para2.c
        <<" d+d "<<para1->d+para2.d
        <<" e+e "<<para1->e<<para2.e
        <<para3
        <<endl;
    return 0;
}


int mock_func(ST1 * para1,ST1 para2,void * para3){
    cout<<__func__<<"\tcalled!"
        <<endl;
    return 0;
}

int ref_func(ST1 * para1,ST1 para2,void * para3){
    return mock_func(para1,para2,para3);
}

int ST1::member_func(){
    cout<<__func__<<" called! "
        <<" a="<< this->a
        <<" b="<< this->b
        <<" c="<< this->c
        <<" d="<< this->d
        <<endl;
    return 0;
}

int ST1::member_func_mock(){
    cout<<__func__<<" called! i do nothing."
        <<endl;
    return 0;
}

int member_func_extern(ST1 * st){
    cout<<__func__<<" called! i am not member function."
        <<endl;
    return 0;
}
