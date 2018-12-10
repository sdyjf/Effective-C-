/*
条款10：令 operator= 返回一个 reference to *this

令赋值操作符返回一个 reference to *this
*/

//关于赋值，有趣的是你可以把它写成连锁形式：

int main(){

int x,y,z;

x=y=z=15;   

x=(y=(z=15));   //等价形式

}   
//注：对变量的赋值一般不能放在函数外，只有定义全局变量的初始化时才被允许

//为了实现“连锁赋值”，赋值操作符必须返回一个 reference 指向操作符左侧实参。

class My{
public:
    My& operator+=(const My &rhs){
        return *this;
    }
    My& operator=(const My &rhs){
        return *this;
    }
};

//注意，这只是个协议，并无强制性。这份协议被所有内置类型和标准程序库提供的类型共同遵守。