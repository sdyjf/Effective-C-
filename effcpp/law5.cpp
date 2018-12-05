/*
条款05:了解C++默默编写并调用了哪些函数
编译器可以暗自为class创建default构造函数,copy函数,copy assignment操作符,以及析构函数
*/

class Empty{

};

/*
如果自己没有声明default构造,copy,析构函数.copy assignment操作符
就好像自己写下:
class Empty{
public:
    Empty(){}
    Empty(const Empty&){}
    ~Empty(){}       (non-vitural函数,除非其base class自身声明有vitural析构函数)

    Empty& operator=(const Empty&){}
}
所有这些函数都是public且inline的
*/

/*
1.对于"内含reference成员"或"内含const成员"的类,编译器不会为其生成copy assignment操作符
C++不允许让reference改指向不同对象

2.对于base classes将copy assignment操作符声明为private的derived classes,编译器你也拒绝为其生成copy assignment操作符
*/