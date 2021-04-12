// 1）复制的内容不同。strcpy只能复制字符串，而memcpy可以复制任意类型的内容。strcpy只用于字符串复制，并且还会复制字符串的结束符。memcpy对于复制的内容没有限制，用途更广。
// 2）复制的方法不同。strcpy不需要指定长度，遇到结束符’\0’才会结束，所以容易溢出。memcpy则是根据第三个参数决定复制的长度
// 3）用途不同。通常在复制字符串时用strcpy，在复制其他类型数据时一般用memcpy。
#include<cassert>
#include<iostream>
using namespace std;


int strlen(const char *p){
    int n=0;
    while(*p!='\0'){
        n++;
        p++;
    }
    return n;
}

void strcpy(char *dest,char *src){
    // 难点：判断各种异常情况
    assert(dest&&src);
    // 这里如果是string创建的话 就不会出现dest根src 复制存在交集的情况吧
    if(dest==src) return;
    // dest在前面从头往后拷贝就行
    if(dest<src){
        while((*dest++ = *src++)!='\0');
    }
    else{
        int n = strlen(src);
        while(n>=0){
            *(dest+n) = *(src+n);
            n--;
        }
    }
}
void *memcpy(void *memTo,void *memFrom,int size){
    assert(memTo&&memFrom);
    if(memTo == memFrom) return;
    char *tmpTo = reinterpret_cast<char *>(memTo);
    char *tmpFrom = reinterpret_cast<char *>(memFrom);
    if(tmpTo<tmpFrom){
        while(size>0){
            *tmpTo++ = *tmpFrom++;
            size--;
        }
    }else{
        while(size>0){
            *(tmpTo+size-1) = *(tmpFrom+size-1);
            size--;
        }
    }
}

int main(){

}