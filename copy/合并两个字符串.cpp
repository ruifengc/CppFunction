// 请编写一个函数将字符串s2添加到字符串s1的末端，函数不受s1、s2空间大小的限制。可以利用常用字符串函数strlen,strcpy,strcat,strcmp,strstr实现。

// 常用字符串函数简单描述:
// strlen(char *str) : 求字符串长度。
// strcpy(char *dest, char *src) : 把src拷贝到dest。
// strcat(char *dest, char *src) : 把src连接到dest后面。
// strcmp(char *s1, char *s2) : 按照各个字符（ascii）比较s1和s2，相等则返回0，否则返回ascii相减的结果。
// strstr(char *s1, char *s2) : 在s1中查找s2，返回找到的位置，若找不到则返回NULL。
#include<cstring>
char* append(char*str1,char*str2)
 
{
 
char* temp;
 
int length=strlen(str1)+strlen(str2);     //计算str1与str2总共的和
 
temp=new char[length+1];        //申请一段足够容下str1和str2的字符串空间
 
strcpy(temp,str1);           //先将str1复制到字符指针temp指向的内存的起始位置
 
strcat(temp,str2);      //再将str2链接到str1的位置
 
return temp;
 
}