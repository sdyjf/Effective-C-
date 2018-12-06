/*
使用newdef.c中定义的newdef函数，但没有进行函数原型声明

命令：gcc main.c newdef.c -o test

实际运行结果：
float:-0.000000
char:13

解释：
没有原形的函数会按照“K&R C”的规则进行类型转换

float 会被先升级为 double 类型，然而newdef函数参数类型为 float
这意味这newdef函数会把传入的 double 类型解释为 float 类型，即发生了截断(只解释前32位)

而 char 即使发生了这种“二次”转换后(第一次是真正的转换，第二次只是截断解释)，其值的确可以被正确解释

注：printf函数的“%f“占位符对于 float 和 double 都可以使用，并不影响精度(gcc对此并不警告)
*/

int main(){
    float d=1999.0718;
    char j=19;

    newdef(d,j);

    return 0;
}