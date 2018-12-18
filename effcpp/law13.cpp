/*
条款13:以对象管理资源

1.为防止资源泄露,请使用RAII对象,它们在构造函数中获得资源并在析构函数中释放资源

2.两个常用的 RAII classes 分别是 shared_ptr 和 unique_ptr.
前者通常是较佳选择,因为其 copy 行为比较直观.若选择 unique_ptr,复制动作会使它(被复制物)指向 null
*/

#include <memory>

//投资体系的 root class
class Investment{

};

//进一步假设,这个程序库通过一个工厂函数 ,供应我们某特定的 Investment 对象

Investment * creatInvestment();

/*
为了`防止区域内过早的 return 语句或者抛出的异常,控制流将不会到达 delete 语句.

我们可以把资源放进对象内,我们便可以依赖 C++ 的"析构函数自动调用机制"确保资源被释放
*/

void f(){           //任意一个控制流
        std::unique_ptr<Investment> pInv(creatInvestment());
        //调用 factor 函数
        //一如既往的使用pInv
        //经由 unique_ptr 的析构函数自动删除 pInv
}

/*

1.获得对象后立刻放进管理对象内:
实际上,"以对象管理资源"的观念常被称为"资源取得时机便是初始化时机" (RAII),
因为我们几乎总是在获得一笔资源后于同一语句内以它初始化某个管理对象.

2.管理对象运用析构函数确保资源被释放

*/

/*
最后批注,我们必须指出, createInvestment 返回的"未加工指针" (raw pointer)简直是对资源泄露的一个死亡邀约,
因为调用者极易在这个指针身上忘记调用 delete
*/

