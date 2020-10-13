


//总：智能指针管理的是动态内存，与静态内存以及栈内存无关
//    new初始化智能指针以及make_shared函数均是分配的动态内存
//    对于自定义的指针类型，在将其绑定到智能指针上时，必须提供删除器deleter
//    (可以绑定的前提是这个指针必须指向动态内存且指向的类型相同)
//
//
//1、静态内存与栈内存 
//
//   全局对象在程序启动时分配，在程序结束时销毁。
//   局部自动对象，当我们进入其定义所在的程序块时被创建，在离开块时销毁
//   局部static对象在第一次使用前分配，在程序结束时销毁
//
//   静态内存：保存局部static对象、类static数据成员以及定义在任何函数之外的变量（全局变量）
//   栈内存：保存定义在函数内的非static对象
//   分配在静态内存或栈内存中的对象由编译器自动创建和销毁
//
//2、内存池
//
//   除了静态内存和栈内存，每个程序还拥有一个内存池（堆），程序用堆来进行动态分配
//   动态内存：显式创建、显式销毁
//   为什么使用它？ ->  程序需要在多个对象间共享数据/程序不知道自己需要使用多少对象/程序不知道所需对象的准确类型
//                  ->   智能指针可以提供对动态分配的内存安全而又方便的管理
//
//
//   内存池包含两种智能指针：shared_ptr和unique_ptr
//   定义的头文件：memory
//
//   定位new表达式：
//   int* p = new (nothrow) int; 如果分配失败，不要抛出异常，返回一个空指针即可
//
//   new-delete：原始的动态分配方式
//               默认初始化：int* p = new int;   *p的值未定义
//               值初始化    int* p = new int(); *p的为0
//                           int* p = new int(5); *p的为5
//   new-delete的常规指针的缺点:
//   
//   void use_factory(T arg)
//   {
//        Foo* p = new Foo(arg);
//        //使用p但不delete它
//   } //p离开了它的作用域，但它所指向的内存没有被释放
//   在这个程序中，一旦use_factory被返回，程序就没有办法释放这块内存了
//   根据整个程序的逻辑，修正这个错误的正确方法是在use_factory中记得释放内存delete
//
//   与之相比
//   shared_ptr use_factory(T arg)
//   {
//        shared_ptr<Foo>p = make_shared<Foo>(arg);
//        return p;  //当我们返回p时，引用计数进行了递增操作
//   }p离开了作用域，但是它所指向的内存不会被释放掉
//   在这个智能指针版本中，use_factory中的return语句向此函数的调用者返回一个p的拷贝
//   拷贝一个shard_ptr会增加所管理对象的引用计数值（重点：引用计数值绑定在管理对象身上而不是指针本体）
//   现在，当p被销毁时，它所指向的对象还有其他的使用者(重点：p指针是会被销毁，但是因为引用计数机制，它指向的内存没有被销毁)
//   对于一块内存，shared_ptr类保证只要有任何shared_ptr对象使用它，它就不会被释放掉
//
//
//   为什么要使用智能指针而不建议使用new-delete？
//   答案：
//   delete:销毁指针对象，释放对应内存
//   shared_ptr引用计数为0：销毁指针对象，释放对应内存
//  （如果引用计数还不为0 即使销毁了指针对象，但是也不会释放内存，从而可以实现数据共享）
//
//   建议：1、坚决只使用智能指针
//         2、不要混合使用普通指针与内置指针
//         3、不要使用get初始化另一个智能指针或者为智能指针赋值
//
//3、shared_ptr
//   shared_ptr<T> sp;    空智能指针，指向类型为T的对象
//   mske_shared<T>(args);返回一个shared_ptr，指向一个 动态分配 的类型为T的对象，使用args初始化此对象
//   shared_ptr<T>p(q);   p是shared_ptr q的拷贝，此操作会递增q的计数器，q的指针必须能转换为T*
//   shared_ptr<T>p(q,d)  p接管了内置指针q所指向对象的所有权 q必须能转换为T*类型 p将使用可调用对象d来代替delete
//   p = q;               p和q都是shared_ptr，所保存的指针必须能相互转换
//                        此操作递减p的引用计数，递增q的引用计数(若p的引用计数变为0，则将其管理的原内存释放)
//   p.use_count()        返回与p共享对象的智能指针数量
//   p.unique()           若p.use_count()为1 返回true 否则返回false
//   p.reset()            若p是唯一指向其对象的shared_ptr，reset会释放此对象 若传递了可选的参数内置指针q 会令p指向q
//   p.reset(q,d)         若还传递了参数d，将会调用d而不是delete来释放q
//
//   shared_ptr<T>p(q);   p管理内置指针q所指向的对象，q必须指向new分配的内存，且能够转换为T*类型
//   shared_ptr<T>p(q,d); p管理内置指针q所指向的对象，q必须指向new分配的内存，且能够转换为T*类型
//                        并且p将使用可调用对象d来代替delete
//
//   
//   (1)创建：
//   
//      建议：最安全的分配和使用动态内存的方法是调用make_shared函数
//      
//      make_shared函数：在动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr
//      
//      举例：
//      shared_ptr<int> p = make_shared<int>(42);
//      auto p = make_shared<int>(42);
//
//      或者利用new返回的指针来显式的初始化智能指针
//      shared_ptr<int>p(new int(42));
//   
//   (2)拷贝或赋值： 通过简单的对智能指针的拷贝或者赋值就可以实现二者指向的是相同的对象 
//                   并且存在引用计数机制(防止空悬指针的发生) 我认为这是智能指针存在的意义
//                   (即智能指针可以通过引用计数机制记录有多少个shared_ptr指向相同的对象，因此可以在恰当的时候自动释放对象)
//      
//      每个shared_ptr都有一个关联的计数器，被称为引用计数
//      
//      这个引用计数值是绑定到shared_ptr所指向的管理对象身上的
//     
//     计数器递增情况：
//      拷贝一个shared_ptr 
//      用这个shared_ptr初始化另一个shared_ptr
//      将这个shared_ptr作为参数传递给一个函数
//      将shared_ptr作为一个函数的返回值(返回的值是智能指针的拷贝，拷贝会触发引用递增机制)
//
//      计数器递减情况：
//      给shared_ptr赋予一个新值
//      shared_ptr被销毁
//
//      一旦一个shared_ptr的计数器变为0，它就会自动释放自己所管理的对象
//      （销毁指针 释放内存）
//
//   (3)智能指针案例详解
//      Blob    内含普通指针 指向vector  vector<string>* ptr;
//      StrBlob 内含智能指针 指向vector  shared_ptr<vector<string>> Sptr;
//
//      Blob<string> b1; //空Blob
//      {
//            Blob<string>b2 = {"a","an","the"};
//            b1 = b2; //b1和b2共享相同的元素 (vector指针ptr浅拷贝)
//      }  //b2离开了作用域被销毁了，此时b2中的ptr指向的vector中的元素被销毁了
//      //因此b1指向的元素也同样被销毁了 
//      (假定ptr使用new来分配动态内存 则离开作用域后，虽然p不会被销毁，但是在外也不可调用，形成内存泄漏/或者重复释放内存 带来很多问题)
//
//      StrBlob b1;
//      {
//            StrBlob b2 = {"a","an","the"};
//            b1 = b2;  
//            //利用引用计数机制，b1所指向的原对象的引用数变为0被销毁，此时b1指向的新对象是b2中保存的vector
//            //通过拷贝实现了智能指针的数据共享，此时b1和b2指向的是同一个vector，b2的引用次数为2
//            b2.push_back("about");
//            //此时b2包含的共享的vector对象有4个元素,所以b1有4个元素
//            //b2指针被自动销毁，但是它指向的动态内存空间的引用数在销毁后为1(注意是内存对象的引用数，也就是原b2指针指向的对象的引用数) 
//            //                  因此不会被自动释放
//      }
//
//   (4)智能指针陷阱
//      
//      默认情况下，一个用来初始化智能指针的普通内置指针必须指向动态内存(也就是new初始化)
//     （不选择普通指针初始化智能指针则选择使用make_shared函数，make_shared函数同样分配动态内存，这是最安全的）
//      因为智能指针默认使用delete来释放它所指向的对象。
//      我们也可以将一个智能指针绑定到一个指向其他类型的资源的指针上(比如自定义的类而非内置类int等)（重点区分是自定义类，与动态内存无关）
//      但是为了这样做，我们必须提供自己的操作来代替delete    -> 这就是智能指针陷阱
//
//      语法：shared_ptr<T>p(q,d); p管理内置指针q所指向的对象，q必须指向new分配的内存(q是一个指针)，且能够转换为T*类型
//                                 并且p将使用可调用对象d来代替delete
//      经典案例：
//      struct connection
//      {
//        string ip;
//        int port;
//        connection(string ip_,int port_):ip(ip_),port(port_){}
//      };
//
//      struct destination
//      {
//        string ip;
//        int port;
//        destination(string ip_, int port_):ip(ip_), port(port_){}
//      };
//
//      connection connect(destination* pDest) //创建连接
//      {
//        shared_ptr<connection>pConn(new connection(pDest->ip, pDest->port));
//
//        //shared_ptr<connection>pConn = make_shared<connection>(pDest->ip, pDest->port);
//        //二者均为动态分配的内存
//        cout << "creating connection(" << pConn.use_count() << ")" << endl;
//        return *pConn;
//      }
//
//      void disconnect(connection pConn)  //关闭连接
//      {
//        cout << "connection close(" << pConn.ip << ":" << pConn.port << ")" << endl;
//      }
//
//      void end_connection(connection* pConn) //自定义删除器
//      {
//        disconnect(*pConn);
//      }
//
//      void f(destination& d)
//      {
//        connection conn = connect(&d);
//        shared_ptr<connection>p(&conn, end_connection);//这里传入的是函数的指针
//        cout << "connection now(" << p.use_count() << ")" << endl;
//      }
//
//      int main()
//      {
//        destination dest("202.118.176.67", 3316);
//        f(dest);
//      }
//
//4、unique_ptr
//   
//   一个unique_ptr拥有它所指向的对象 某个时刻只能有一个unique_ptr指向一个给定对象
//   当unique_ptr被销毁时，它所指向的对象也被销毁
//   
//   (1)创建：
//       
//      当我们定义一个unique_ptr时，需要将其绑定到一个new返回的指针上，且必须采用直接初始化形式
//      unique_ptr<int>p(new int(42));
//
//   (2)拷贝赋值：
//    
//      unique_ptr不支持常规拷贝与赋值
//
//      但是支持所有权转换
//      unique_ptr<string>p2(p1.release()); 将所有权从p1转移给p2，且p1被置为空
//     
//      unique_ptr<string>p3(new string("hello"));
//      p2.reset(p3.release());   将所有权从p3转移给p2 并且释放p2原来指向的内存
//
//     可以拷贝一个将要被销毁的unique_ptr 比如从函数中返回一个unique_ptr
//
//
//
//
//   (3)常规操作：
//
//      unique_ptr<T>u1;    空unique_ptr，指向类型为T的对象，使用delete来释放它的指针
//      unique_ptr<T,D>u2;  空unique_ptr，u2使用一个类型为D的可调用对象来释放它的指针
//      unique_ptr<T,D>u(d);空unique_ptr，指向类型为T的对象，用类型为D的对象d来代替delete
//
//      u.release();        u放弃对指针的控制权(切断unique_ptr和它所管理的对象的联系)，返回当前保存的指针，并将u置为空
//                          返回的指针通常被用来初始化另一个智能指针或给另一个智能指针赋值
//      u.reset();          释放u指向的对象
//      u.reset(q);         如果提供了内置指针q，令u指向这个对象(且释放原来指向的内存)，否则置为空
//
//      unique_ptr<T[]>u;   u指向一个动态分配的数组，数组元素类型为T
//      unique_ptr<T[]>u(p);u指向内置指针p所指向的动态分配的数组，p必须能够转换为类型T*
//      u[i]                返回u拥有的数组中位置i出的对象
//
//  (4)删除
//   
//     与shared_ptr不同，必须在尖括号内标明删除器的对象类型
//    
//     unique_ptr<objT,delT>p(new objT,fcn);
//     p指向一个类型为objT的对象，并使用一个类型为delT的对象来释放objT对象
//     它会调用一个名为fcn的delT类型对象来执行删除操作
//
//     重写shared_ptr中的删除器 应该写成如下形式
//
//    unique_ptr<connection,decltype(end_connection)*>p(&c,end_connection);
//    decltype<end_connection>*是一个函数指针类型，与end_connection相同(函数名等价于函数指针)
//    (同时函数指针就是一个可调用对象)
//
//补充、weak_ptr
//   
//   不控制所指向对象生存期的智能指针，指向一个由shared_ptr管理的对象
//   将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放（即使有weak_ptr指向对象）
//   常规操作：
//
//      weak_ptr<T>w;       空weak_ptr，指向类型为T的对象
//      weak_ptr<T>w(sp);   与shared_ptr sp指向相同的对象的weak_ptr T必须能够转换为sp指向的类型
//      w=p;                p可以是一个shared_ptr或weak_ptr 赋值后w与p共享对象
//      w.reset();          将w置为空
//      w.use_count();      与w共享对象的shared_ptr的数量
//      w.expired();        若w.use_count()为0，返回true,否则返回false
//      w.lock();           如果expired为true,返回一个空shared_ptr;否则返回一个指向w对象的shared_ptr

//5、动态数组
//   
//   大多数应用应该使用标准库容器而不是动态分配的数组，使用容器更为简单、更不容易出现内存管理错误并且有更好的性能
//  
//   语法：int* p = new int[42]; p指向一个分配了42个int的数组
//         分配一个这样的数组得到的是一个元素类型的指针（动态数组不是一个数组）
//   值初始化：
//         int* p = new int[10];  10个未初始化的int
//         int* p = new int[10]();10个值初始化为0的int
//         int* p = new int[10]{1,2,3,4,5,6,7,8,9,10}; 分配元素
//   释放动态数组：delete[] p;
//
//6、智能指针和动态数组
//
//   unique_ptr<int[]>up(new int[10]);  up指向一个包含10个未初始化int的数组
//   up.release(); 自动使用delete[]来销毁其指针
//
//   shared_ptr<int>sp(new int[10],[](int* p){ delete[] p;};
//   shared_ptr不直接支持管理动态数组，如果要使用，就必须提供自己定义的删除器
//
//7、allocator类
//
//   定义头文件:memory
//   作用：帮助我们将内存分配和对象构造分离开,分配的内存是原始的未构造的
//   (new分配的一大段内存将内存的分配和对象的构造组合在了一起，会导致不必要的浪费，并且没有默认构造函数的类就不能进行动态分配数组)
//
//   标准操作：
//   
//   allocator<T>a;      定义一个名为a的allocator对象，为类型为T的对象分配内存
//   a.allocate(n);      分配一段原始的、未构造的内存，保存n个类型为T的对象
//
//   a.deallocate(p,n);  释放从T*指针p中地址开始的内存，这块内存保存了n个类型为T的对象
//                       p必须是一个先前由allocate返回的指针且n必须是p创建时所要求的大小
//                       在调用deallocate之前，用户必须对每个在这块内存中创建的对象调用destroy
//
//   a.construct(p,args);p必须是一个类型为T*的指针，指向一块原始内存，
//                       args被传递给类型为T的构造函数，用来在p指向的内存中构造一个对象
//   a.destroy(p);       p为T*类型的指针，此算法对p指向的对象执行析构函数
//
//   举例：
//    
//   allocator<string>alloc;           可以分配string的allocator对象
//   auto const p = alloc.allocate(n); 分配n个未初始化的string
//   auto q = p;                       q指向最后构造的元素之后的位置（q指向最后构造的元素之后的位置）
//   alloc.construct(q++);             *q为空字符串
//   alloc.construct(q++,10,'c');      *q为cccccccccc
//   alloc.construct(q++,"hi");        *q为hi
//   while(q != p)
//    alloc.destroy(--q);              销毁构造的元素 第一次调用destroy时，q指向最后一个构造的元素之后的位置
//                                    （只能对真正构造了的元素进行destroy操作）
//
//   alloc.deallocate(p,n);            释放内存
//
//   unitialized_copy(b,e,b2);         从迭代器b和e指出的输入范围中拷贝元素到迭代器b2指定的未构造的原始内存中
//                                     调用会返回一个指针 指向最后一个构造的元素之后的位置
//
//   例子：
//   void input_reverse_output_string(int n)
//   {
//       allocator<string>alloc;
//       auto const p = alloc.allocate(n);
//       string s;
//       auto q = p; //此时未构造 q指向p内存的开头位置
//       while(q != p + n && cin >> s)
//              alloc.construct(q++,s);
//       while(q != p)
//              cout<< *--q << " ";alloc.destroy(q);
//       alloc.destroy(p,n);
//   }

/*
智能指针经典案例 1.0版本
//我们不能在一个StrBlob对象内直接保存vector，因为一个对象的成员在销毁时也会被销毁
//假定b1和b2是StrBlob的两个对象，共享相同的vector 如果此vector保存在其中一个StrBlob中（比如b2）
//那么当b2离开作用域时，此vector也会被销毁，为了保证vector中的元素继续存在，我们将vector保存在动态内存中
//为了实现我们所希望的数据共享，我们为每个StrBlob设置一个shared_ptr来管理动态分配的vector
//此shared_ptr的成员将记录有多少个StrBlob共享相同的vector，并在vector的最后一个使用者被销毁时释放vector

#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;

class StrBlob
{
public:
    typedef vector<string>::size_type size_type;

    StrBlob();
    StrBlob(initializer_list<string>i1);

    size_type size() const { return data->size(); }
    bool empty()const { return data->empty(); }

    //添加和删除元素
    void push_back(const string& t) { data->push_back(t); }
    void pop_back();

    //元素访问
    string& front();
    const string& front()const;   //对于传入常量和非常量对象的重载
    string& back();               //重载的是底层const 顶层const不可以重载
    const string& back()const;
private:
    shared_ptr<vector<string>>data;
    void check(size_type i, const string& msg)const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()){}

StrBlob::StrBlob(initializer_list<string> i1) :
    data(make_shared<vector<string>>(i1)){}


void StrBlob::check(size_type i, const string& msg)const
{
    if (i >= data->size())
        throw out_of_range(msg);
}

string& StrBlob::front()
{
    check(0, "frotn on my empty StrBlob");
    return data->front();
}

const string& StrBlob::front() const
{
    check(0, "frotn on my empty StrBlob");
    return data->front();
}
string& StrBlob::back()
{
    check(0, "back on my empty StrBlob");
    return data->back();
}

const string& StrBlob::back()const
{
    check(0, "back on my empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on my empty StrBlob");
    data->pop_back();
}

int main()
{
    const StrBlob csb{ "hello", "world", "pezy" };
    StrBlob sb{ "hello", "world", "Mooophy" };

    cout << csb.front() << " " << csb.back() << endl;
    sb.back() = "pezy";
    cout << sb.front() << " " << sb.back() << endl;
}
*/


/*

p412 t12.6 t12.7

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<fstream>
using namespace std;

//typedef vector<int>* Ptr;
typedef shared_ptr<vector<int>>  Ptr;

auto make_point()
{
   // return new vector<int>{};
    return make_shared<vector<int> >();
}
auto populate(Ptr vec)
{
    for (int i; cout << "enter:", cin >> i; vec->push_back(i));
    return vec;
}
auto print(Ptr vec)-> ostream&
{
    for (auto& num : *vec)
        cout << num << " ";
    return cout;
}
int main()
{
    auto vec = populate(make_point());
    print(vec);
    //delete vec;
    return 0;
}

*/

/*

//文本查询程序 本章的重点！！！

#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<memory>
#include<fstream>
#include<sstream>

using namespace std;

class QueryResult;

class TextQuery
{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&)const;
private:
    shared_ptr<vector<string>>file; //输入文件

    map<string, shared_ptr<set<line_no>>>wm; //每个单词到它所在的行号的集合的映射
};

TextQuery::TextQuery(ifstream& is) : file(new vector<string>)
{
    string text;
    while (getline(is, text)) //对于文件中的每一行
    {
        file->push_back(text); //file指向的vector保存此行文本
        int n = file->size() - 1; //当前的行号
        istringstream line(text); //从text读取到line中作为每个单词的输入流
        string word;
        while (line >> word) //循环，对于一行中的每个单词
        {
            //如果单词不在wm中，就以这个单词为下标在wm中添加一项 并进行关联值初始化(对于该项则初始化为空指针)
            auto& lines = wm[word]; //lines是一个指向set容器的智能指针 如果这个已经存在 则map的这个操作什么都不会做
            if (!lines) //在我们第一次遇见这个单词时，这个指针是一个空指针
                lines.reset(new set<line_no>);//创建一个set容器
            lines->insert(n);//将此行号插入set中 重复了set这个操作就什么都不会做
        }
    }
}

class QueryResult //保存的结果类
{
    friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s, shared_ptr<set<TextQuery::line_no>>p, shared_ptr<vector<string>>f)
        : sought(s), lines(p), file(f) {}
private:
    string sought; //查询单词
    shared_ptr<set<TextQuery::line_no>>lines; //出现的行号
    shared_ptr<vector<string>>file; //输入文件
    
};

QueryResult TextQuery::query(const string& sought)const
{
    //如果未找到sought,返回一个指向此set的指针
    static shared_ptr<set<line_no>>nodata(new set<line_no >);
    //使用find而不是下标运算符来查找单词，避免将单词添加到wm中
    auto loc = wm.find(sought);
    if (loc == wm.end()) //未找到 返回尾部迭代器
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);//保存了set智能指针以及vector智能指针
}                         //拷贝指针而不是选择拷贝容器 大大提高了算法的效率

ostream& print(ostream& os, const QueryResult& qr)
{
    //如果找到了单词，打印出现的次数和所有出现的位置
    os << qr.sought << "occurs" << qr.lines->size() << endl;
    //打印出现单词的每一行
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << endl;
    return os;                                   //这里是比较精髓的迭代器运算
}

void runQueries(std::ifstream& infile)
{
    TextQuery tq(infile);
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << std::endl;
    }
}
int main()
{
    ifstream file("../data/storyDataFile.txt");
    runQueries(file);
}
*/
