/*
条款08：别让异常逃离析构函数

1.析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，
然后吞下它们（不传播）或结束程序.

2.如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么 class 应该提供一个普通函数（而非在析构函数中）执行该操作.
*/

class DBConnection{
public:
    static DBConnection create();
    void close();
};

//为了确保客户不忘记在 DBConnection 对象身上调用 close() 一个合理的想法是创建一个用来管理 DBConnection 的类

class DBConn{
public:
    ~DBConn(){
        db.close();   
    }
private:
    DBConnection db;
};

/*
只要调用成功，一切美好。但如果该调用导致异常， DBConn 析构函数会传播该异常，也就是允许它离开这个析构函数，
那会抛出麻烦（一个异常如果没有被捕获，则它将终止当前的程序）

有两种办法可以避免这个问题：
*/

/*如果 close 抛出异常就结束该程序，通常通过调用 abort 完成：

DBConn::~DBConn(){
    try{ db.close(); }
    catch(...){
        std::abort();
    }
}

*/

/*吞下 close 引发的异常
DBConn::~DBConn(){
    try{ db.close(); }
    catch(...){
        记录下对 close 调用的失败
    }
}
*/

/*
然而这些方法都没有什么吸引力，二者都无法对“导致 close 抛出异常”的情况做出反应

我们可以由客户自己调用 close ，给他们一个处理错误的机会
*/

/*
class DBConn{
public:
    void close( ){
        db.close();
        closed=true;
    }
    ~DBConn(){
        if(!closed){
            try{
                db.close();
            }
            catch(...){
                记录下来并结束程序或者吞下异常
            }
        }
    }
private:
    DBConnection db;
    bool closed;
}
*/