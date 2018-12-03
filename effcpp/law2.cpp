/*
条款02:尽量以const,enum,inline替换#define
1.对于单纯常量,最好以const对象或enums替换#defines
2.对于形似函数的宏(macros),最好用inline函数替换#defines
*/

/*用常量替换宏,常量会被编译看到,进入记号表内.
此外,对于浮点常量而言,使用常量可能会比使用#define导致较小的码
*/

#define PI 3.14

const double Pi=3.14;


/*
StuNum是一个声明式,虽然C++要求你对你使用的任何东西提供一个定义式,
但如果它是个class专属常量又是static且为整数类型(ints,chars,bools),则需特殊处理.
只要不取地址,你可以使用它们而无需提供定义式.
#define无法创建class专属常量,不能提供任何封装性
*/
class ClassInf{
private:
    static const int StuNum=1702019;
    int scores[StuNum];
};

class ClassInf2{
private:
    static const double StuS;           //static class常量声明
};

const double ClassInf2::StuS=1.8;       //定义

/*
编译器坚持必须在编译期间知道数组的大小,"the enum hack"
不可以取enum的地址
*/
class ClassInf3{
private:
    enum{StuN=1702019};
    int scores[StuN];
};

/*
函数宏可以用template inline函数替代
*/
#define CALL_WITH_MAX(a,b) ((a)>(b)?(a):(b))

//但CALL_WITH_MAX(++a,b) 会使a被累加2次

template<typename T>
inline T callWithMax(const T &a,const T &b){
    return (a>b?a:b);
}

