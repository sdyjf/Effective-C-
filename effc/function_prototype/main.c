/*
使用newdef.c中定义的newdef函数，但没有进行函数原型声明

命令：gcc main.c newdef.c -o test

实际运行结果：
float:-0.000000
char:13
*/

int main(){
    float d=1999.0718;
    char j=19;

    newdef(d,j);

    return 0;
}