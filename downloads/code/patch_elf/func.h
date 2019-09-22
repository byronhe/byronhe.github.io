#pragma once
#include <iostream>
#include <cstdio>
using namespace std;

class ST1{
    public:
        uint32_t a;
        uint64_t b;
        char c[200];
        double d;
        ST1 * e;

        ST1():a(0),b(0),d(0),e(0){
            c[0]=0;
        }

        //类的成员函数
        int member_func();
        int member_func_mock();
};

int member_func_extern(ST1 * st);


//一般函数
int original_func(ST1 * para1,ST1 para2,void * para3);
int mock_func(ST1 * para1,ST1 para2,void * para3);
//int ref_func(ST1 * para1,ST1 para2,void * para3);

class Base{
    private:
        uint32_t b;
        ST1 st;
    public:
        uint32_t a;

        Base():b(0),a(0){}
};

//inline 函数
inline int inline_func(int a,int b){
    int c=a+b+ 0x1111 * a + b/0x1111;
    printf("%s %d\n",__func__,c);
    return c;
}

inline int inline_func_mock(int a,int b){
    int c=a+b+100;
    printf("%s %d\n",__func__,c);
    return c;
}

//模板函数
template <typename T>
uint32_t get_member_a(T & t){
    cout<<__func__<<" a="<<t.a<<endl;
    return t.a;
}

template <typename T>
uint32_t get_member_b(T & t){
    cout<<__func__<<" b="<<t.b<<endl;
    return t.b;
}
