/*
1.将某些东西声明为const可以帮助编译器侦测出错误用法。
const可被施加于任何作用域内的对象、函数参数、函数返回类型、成员函数本体
2.编译器强制实施bitwise constness，但你编写程序时应该使用“概念上的常量性”
3.当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可以避免代码重复
*/

#include <iostream>
#include <vector>
#include <string>

const char * const p="Hello 301!\n";    //const pointer,const data

std::vector<int> vec;

const std::vector<int>::iterator iter=vec.begin();      //const iterator

std::vector<int>::const_iterator cIter=vec.begin();     //const data

/*
令函数返回一个常量值，往往可以降低因客户错误而造成的意外，而又不至于放弃安全性和高效性
*/

class Raitonal{

};

const Raitonal operator *(const Raitonal &lhs, const Raitonal &rhs);

/*如果不返回一个const 对象，客户可能会：
Raitonal a,b,c;
if(a*b=c)
良好的用户自定义类型的特征是他们避免无端的和内置类型不兼容
*/

/*
const成员函数：
1.它们使class接口比较容易被理解。
因为，得知哪个函数可以改动对象内容而哪个函数不行，这是很重要。
2.它们使“操作const对象”成为可能。
*/

/*
bitwise constness
logical constness
*/
class CTextBlock{
public:
    char &operator[](std::size_t pos)const          //bitwise声明
    {return pText[pos];}                            //但其实不适当
private:
    char *pText;
};

/*
    const CTextBlock cctb("Hello");
    char *pc=&cctb[0];

    *pc='J';                                        //你创建一个常量对象并设以某值，而且只对它调用const成员函数。但你终究改变了值
*/