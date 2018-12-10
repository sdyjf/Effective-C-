/*
条款09：绝不在构造和析构过程中调用 virtual 函数

在构造和析构函数期间不要调用 virtual 函数，因为这类调用从不下降至 derived class（比起当前执行构造函数和析构函数的那层）
*/

#include <string>

class Tran{
public:
    Tran();
    virtual void logTran() const;
};

Tran::Tran(){
    logTran();
}

class BuyTran:public Tran{
    virtual void logTran() const;
};

//当执行初始化时
BuyTran b;

/*
derived class 对象内的 base class 成分会在 derived class 自身成分被构造之前构造妥当
此时被调用的是 Tran 的版本

最根本的原因是，在 derived class 对象的 base class 构造期间，对象类型是 base class 而不是 derived class
不只 virtual 函数会被编译器解析至 base class，若使用运行时类型信息（dynamic_cast typeid)也会把对象视为 base class.

对象在 derived class 构造函数开始执行之前不会成为一个 derived class 对象
*/

//解决方案为：

class Tran2{
public:
    explicit Tran2(const std::string &logInfo);
    void logTran2(const std::string &logInfo);
};

Tran2::Tran2(const std::string &logInfo){
    logTran2(logInfo);
}

class BuyTran2:public Tran2{
public:
    BuyTran2(const std::string &Info)
    :Tran2(createLogString())
    {};
private:
    static std::string createLogString();
};

/*
你可以令 derived class 将必要的构造信息向上传递至 base class 构造函数

比起在成员初值列内给予 base class 所需数据，利用辅助函数创建一个创建一个值传给 base class 构造函数往往比较方便（也比较可读）.
*/