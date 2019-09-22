#include <stdint.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "func.h"
#include "patch_elf.h"

using namespace std;


int test(){
    ST1 s1,s2;
    char str[]="hello";
    s1.a=s1.b=s1.d=1;
    s1.e=NULL;

    s2.a=s2.b=s2.d=2;
    s1.e=NULL;

    cout<<"----------------------------------------------------------------------"<<endl;

    //mock original_func，替换成mock_func
    original_func(&s1,s2,&str[0]);

    patch_func((void*)&original_func, (void*)&mock_func);

    original_func(&s1,s2,&str[0]);

    cout<<"----------------------------------------------------------------------"<<endl;

    //mock inline 函数貌似不行
    int a=s1.a, b=s1.b;
    inline_func(a,b);
    patch_func( (void*) &inline_func, (void*) &inline_func_mock);
    inline_func(a,b);

    cout<<"----------------------------------------------------------------------"<<endl;

    s1.member_func();
    patch_func( (void*) &ST1::member_func, (void*) &ST1::member_func_mock);
    s1.member_func();
    patch_func( (void*) &ST1::member_func, (void*) &member_func_extern);
    s1.member_func();

    cout<<"----------------------------------------------------------------------"<<endl;

    get_member_a(s1);
    patch_func( (void*) & get_member_a<ST1> , (void*) & get_member_b<ST1>);
    get_member_a(s1);

    return 0;
}

int main(){
    test();
    return 0;
}
