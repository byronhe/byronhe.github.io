#include <stdint.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include "patch_elf.h"
using namespace std;


int print_op(void * addr,int leng){
    unsigned char * op=(unsigned char *) addr;
    cout<<endl<<"addr:"<<addr<<" code:"<<endl;
    for(int i=0;i<leng;++i){
        cout<<"0x"<<hex<<(unsigned int)op[i]<<" ";
    }
    cout<<endl;
    return 0;
}

int patch_func(void  * original,void * mock){
    /*
    cout<<endl<<"----------------------------------------------------------------------"
        <<endl<<__func__<<" ,i am going to patch "<<original<<" to "<<mock
        <<endl;
        */

    //rax 用于保存函数调用的返回值，所以可以占用
    //4010e1:       b8 20 0c 40 00          mov    $0x400c20,%eax
    //4010e6:       ff e0                   jmpq   *%rax

    uint32_t addr=(uint32_t)(uint64_t)mock;
    const int code_len=7;
    char inject_code[code_len]={0xb8,0x00,0x00,0x00,0x00,0xff,0xe0};
    memcpy(&inject_code[1],(char*)&addr,4);

    //print_op(inject_code,code_len);

    //接下来，把inject_code复制到original这个位置
    //print_op(original,100);
    
    //首先，要改掉内存的权限，增加写权限
    const size_t length = sysconf(_SC_PAGESIZE);
    void * code_addr= (void*) ( ( (long) original/length)*length );
    int ret=mprotect(code_addr, length, PROT_READ | PROT_WRITE | PROT_EXEC);
    if ( 0!=ret ) {
        cerr<<"mprotect failed! ret="<<ret<<endl;
    }

    //修改代码
    memcpy( original,inject_code,code_len);

    //再去掉写权限
    ret=mprotect(code_addr, length, PROT_READ |  PROT_EXEC);
    if ( 0!=ret ) {
        cerr<<"mprotect failed! ret="<<ret<<endl;
    }

    //print_op(original,100);
    //cout<<"----------------------------------------------------------------------"
    //  <<endl<<endl;
    return 0;
}
