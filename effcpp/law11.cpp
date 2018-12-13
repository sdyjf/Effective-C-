/*
条款11：在 operator= 中处理“自我赋值“

1.确保当对象自我赋值时 operator= 有良好的行为。其中技术包括比较”来源对象“和”目标对象“的地址、
精心周到的语句顺序、以及 copy-and-swap

2.确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确

*/

//注：如果使用“资源管理对象”，你的赋值操作符可能是“自我赋值安全”的

class BitMap{

};

class Wiget{
private:
    BitMap *bp;
};

Wiget& Wiget::operator=(const Wiget &rhs){
    delete bp;
    bp=new BitMap(*rhs.bp);
    return *this;
}

/*
如果 *this 和 rhs 是同一个对象。那 delete 就不只是销毁当前对象的 bitmap，它也销毁了 rhs 的 bitmap

可以在函数首添加证同测试:
    if(this==&rhs) return *this;

但这个新版本依旧没有解决“异常问题”
即如果 “new” 导致异常，Wiget 最终会持有一个指针指向一块被删除的 bitmap

令人高兴的是，让 operator=具备“异常安全性”往往自动获得“自我赋值安全”的回报
因此，越来越多的人对“自我赋值”的态度是倾向于不去管它，把焦点放在实现“异常安全性”上
*/

Wiget& Wiget::operator=(const Wiget &rhs){
    BitMap* porig=bp;
    bp=new BitMap(*rhs.bp);
    delete porig;
    return *this;
}
