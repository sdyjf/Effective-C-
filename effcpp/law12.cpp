/*
条款12：复制对象时勿忘记其每一个成分

1.Copying 函数应该确保复制“对象内的所有成员变量”以及“所有 base class成分”

2.不要尝试以某个 copying 函数实现另一个 copying 函数.
应该将共同机能放进第三个函数中，并由两个 copying 函数共同调用
*/

//当我们声明自己的 copying函数，意思就是告诉编译器你并不喜欢缺省实现中的某些行为

#include <string>

class Customer{
public:
    Customer(const Customer &rhs);
    Customer()=default;
    Customer& operator=(const Customer &rhs);
private:
    std::string name;
};

class PriCustomer:public Customer{
public:
    PriCustomer(const PriCustomer &rhs);
    PriCustomer& operator=(const PriCustomer &rhs);
private:
    int pri;
};

PriCustomer::PriCustomer(const PriCustomer &rhs)
:pri(rhs.pri)
{}

PriCustomer& PriCustomer::operator=(const PriCustomer &rhs){
    pri=rhs.pri;
    return *this;
}

/*
这个构造函数并没有复制所继承的 Customer 成员变量
copy函数并没有指定实参传给其 base class 构造函数，因此 PriCustomer 对象的 Customer 成分会被不带实参
的 Customer 的 default 函数执行缺省的初始化动作

以上事态在 PriCustomer 的 copy assignment操作符身上只有轻微不同。
它不曾企图修改 base class 的成员，所以那些成员变量保持不变
*/

//解决办法：让 derived class 的copying 函数调用相应的 base class 函数

PriCustomer::PriCustomer(const PriCustomer &rhs)
:Customer(rhs),pri(rhs.pri)
{}

PriCustomer& PriCustomer::operator=(const PriCustomer &rhs){
    Customer::operator=(rhs);
    pri=rhs.pri;
    return *this;
}

/*
注：
令 copy assignment操作符调用 copy 构造函数是不合理的，因为这就像试图构造一个已经存在的对象

反方向——令 copy 构造函数调用 copy assignment 操作符同样没有意义。构造函数用来初始化新对象，而 assignment
操作符只施行于已初始化的对象身上
*/
