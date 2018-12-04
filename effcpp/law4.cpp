/*
条款04:确定对象被使用前已先被初始化

1.为内置型对象进行手工初始化,因为C++不保证初始化它们.

2.构造函数最好使用成员初值列,而不要在构造函数本体内使用赋值操作.
初值列列出的成员变量,其排列次序应该和它们在class中的声明次序相同

3.为免除"跨编译单元之初始化次序"问题,请以local static替换non-local static对象
*/

#include <vector>
#include <string>

/*
如果你使用C part of C++,而且初始化可能招致运行期成本,那就不保证发生初始化.
一旦进入non-C parts of C++,规则有些变化.
如:
array(来自C part of C++)不保障其内容被初始化
而vector(来自STL part of C++)却有此保证
*/

//永远在使用对象之前先将它初始化

int x=0;                                            //对int进行手工初始化
const char *text="A c-style string";                //对指针进行手工初始化

/*
至于内置类型以外的任何其他东西,初始化责任落在构造函数身上,对象的成员变量的初始化发生在进入构造函数本体之前
成员初始列:调用copy构造函数而不是赋值
如果成员是const或references,它们就一定需要初始值,不能被赋值
*/

class PhoneInf{
public:
    PhoneInf()=default;
    PhoneInf(const std::string &Name,const std::vector<int> &Num):PhoneName(Name),PhoneNum(Num){}
private:
    const std::string PhoneName;
    std::vector<int> PhoneNum;
};

//总是使用成员初始列,这样做有时候绝对必要,且往往比赋值更高效,而且最好总是以其声明次序为次序

/*
不同编译单元内定义之"non-local static对象"的初始化次序
static对象:
global对象,定义于namespace作用域内的对象,在class内,在函数内,以及在file作用域被声明为static的对象
函数内的static对象称为local static对象,其他static对象称为non-local static对象.

问题在于:
如果某编译单元内的某个non-local static对象的初始化动作使用了另一个编译单元内的某个non-local static对象,
它所用到的这个对象可能尚未被初始化.
*/

PhoneInf &tempPhone(){
    static PhoneInf temp;
    return temp;
}

/*
将每个non-local static对象搬到自己的专属函数内
这是Singleton模式的一个常见的实现手法
C++保证,函数内的local static对象会在"该函数被调用期间""首次遇上该对象之定义式"时被初始化
但注意在多线程情况下可能会出现初始化的race condition
*/

