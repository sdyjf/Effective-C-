/*
条款06：若不想用编译器自动生成的函数，就该明确拒绝

为驳回编译器自动（暗自）提供的功能，可将相应的成员函数声明为private并且不予实现。
使用像 Uncopyable 这样的 base class 也是一种作法
*/

/*
将成员函数声明为private而且故意不实现它们，这一伎俩是如此的被大家接受，因而被用来在C++ iostream程序库中阻止 copy行为
*/

class Home{
public:
    Home(){}
    ~Home(){}
private:
    Home(const Home &);
    Home &operator=(const Home &);
};

/*
当客户拷贝Home对象时，编译器会阻挠他。
但如果不慎在member或者friend函数之内那么做，轮到连接器发出抱怨。

为了将连接期错误移至编译期，可以设计一个专门用来阻止拷贝的 base class
*/

class Uncopyable{
protected:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable &);
    Uncopyable &operator=(const Uncopyable &);
};

//为了阻止 Home2 对象被拷贝，我们只需继承Uncopyable
class Home2:private Uncopyable{

};

//注：C++11新特性，可以将函数定义为删除的 =delete