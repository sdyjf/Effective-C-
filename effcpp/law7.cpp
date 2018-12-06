/*
条款07：为多态基类声明 vitural 函数

1.polymorphic base classes 应该声明一个 vitural 函数。
如果 class 带有任何 virtual 函数，它就应该拥有一个 vitural 函数。

2.Classes 的设计目的如果不是作为 base classes 使用，或者不是为了具备多态性，就不应该声明 vitural 函数

*/

/*
当 derived class 对象经由一个 base class 指针被删除，而该 base class 带着一个 non-vitural函数，其结果未有定义，
实际执行时通常发生的是对象 derived 成分没被销毁。于是造成了一个诡异的 ”局部销毁“ 对象。
*/

#include <string>

//标准 string 不含任何 vitural 函数

class SpecialString: public std::string{
public:
    SpecialString(const std::string & s):word(s){}
    ~SpecialString(){}

private:
    std::string word;
};

/*
    SpecialString *pps= new SpecialString("Fuck!\n");
    std::string *ps;

    ps=pps;

    delete ps;          //未定义，因为SpecialString的析构函数并未被调用，资源会泄露
*/