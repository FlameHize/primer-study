/*
1、一个类的五种特殊成员函数（拷贝控制操作）
   
   拷贝构造函数
   拷贝赋值运算符
   移动构造函数
   移动赋值运算符
   析构函数

   拷贝和移动构造函数定义了当使用同类型的另一个对象初始化本对象时做什么
   拷贝和移动赋值运算符定义了将一个对象赋予同类型的另一个对象时做什么
   析构函数定义了当此类型对象销毁时做什么

2、拷贝构造函数
    
   (1)接受的第一个参数必须是一个自身的引用类型(几乎总是const的引用)
   原因：
      1、如果其参数不是引用类型，则调用永远不会成功
         为了调用拷贝构造函数，我们必须拷贝它的实参，但为了拷贝实参，我们又需要调用拷贝构造函数，如此陷入无限循环
         Sales_data(Sales_data s) 调用会创建一个传入形参s的副本，相当于调用了s对象的拷贝构造函数，这样下去无限循环
      
      2、加入const引用相当于引入了底层const，使得该拷贝构造的任何操作都不会影响到原被拷贝类的数据

   (2)拷贝初始化与直接初始化的区别：
   当我们使用直接初始化时，我们实际上是要求编译器使用普通的函数匹配来选择与我们提供的参数最匹配的构造函数
   当我们使用拷贝初始化时(利用=号)，我们要求编译器将右侧运算对象拷贝到 正在创建的对象 中，如果需要的话还要进行类型转换
                                                                 （拷贝赋值运算符通常对象是已经创建的，因此需要加入析构）          
   (3)拷贝初始化的发生情况：

    1、使用=定义变量时 ！！！
    2、将一个对象作为实参传递给一个非引用类型的形参
    3、从一个返回类型为非引用类型的函数返回一个对象
    4、用花括号列表初始化一个数组中的元素或一个聚合类的成员

   (4)重点：拷贝构造拷贝的是非static成员 不拷贝静态成员

   (5)使用=default:
      
      作用：显式要求编译器生成合成(也就是默认的)构造函数 类内合成的函数将隐式的声明为内联
      规定：只能对合成版本的成员函数使用=default(即默认构造函数或者拷贝控制成员)
   
   (6)如何阻止拷贝？  =delete
      方法：将拷贝构造函数和拷贝赋值运算符定义为删除的函数
      删除的函数：我们虽然定义了它们，但不能以任何方式使用它们
      =delete:通知编译器，我们不希望定义这些成员
      =delete:必须出现在函数第一次声明的时候
      指定范围：可以对任意函数指定为=delete（当然除了析构函数）
      例子：
      sturct NoCopy
      {
        NoCopy() = default;  使用合成的默认构造函数
        NoCopy(const NoCopy&) = delete;  阻止拷贝
        NoCopy& operator=(const NoCopy&) = delete; 阻止赋值
        ~NoCopy() = default;    使用合成的析构函数 
     }

3、拷贝赋值运算符
   
   (1)通常情况下，应该返回一个指向其左侧运算对象的引用
   
   (2)编写拷贝构造运算符时，有两点需要注意：
      
      如果将一个对象赋予它自身，赋值运算符必须能够正确的工作 （这一点实质上用来测试）
      大多数赋值运算符组合了析构函数和拷贝构造函数的工作
   
   (3)编写模式：先将右侧对象拷贝到一个局部临时对象中，
                当拷贝完成后，销毁左侧运算对象的现有成员就是安全的了
                一旦左侧运算对象的资源被销毁，就只剩下将数据从临时对象拷贝到左侧运算对象的成员中了

4、析构函数
    
   执行与构造函数相反的操作
   析构函数释放对象使用的资源 并销毁对象的非static数据成员
   
   重点理解：析构函数体自身并不直接销毁成员，成员是在析构函数体之后 隐含的析构阶段中被销毁的
   
   析构函数的调用时机：

   1、变量离开作用域时被销毁
   2、当一个对象被销毁时，其成员被销毁
   3、容器被销毁时，其元素被销毁
   4、对于动态分配的对象，当对其指针应用delete时被销毁
   5、对于临时对象，当创建它的完整表达式结束时被销毁

   建议：如果一个类需要自定义析构函数，几乎可以肯定它也需要自定义拷贝赋值运算符和拷贝构造函数(否则可以重复删除指针或者发生浅拷贝操作)
         反之亦然。
   
5、拷贝控制和资源管理   
   
   (1)首先确定此类型对象的拷贝语义：使类的行为像一个值或者一个指针
      类的行为像一个值：类拥有自己的状态，副本和原对象是完全独立的，改变副本不会对原对象有任何影响
      类的行为像一个指针：类的实例对象之间共享状态，当我们拷贝一个这种类的对象时，副本和原对象使用相同的底层数据，改变副本也会改变原对象

   (2)行为像值的类：
      对于类管理的资源，每个对象都应该拥有一份自己的拷贝
      意味着对于ps指向的string，每个HasPtr对象都必须有自己的拷贝
      1、定义拷贝构造函数，完成string管理对象的拷贝，而不是拷贝指针本身
      2、定义一个析构函数来释放string
      3、定义一个拷贝赋值运算符来释放当前的string，并从右侧运算对象来拷贝string
      
     举例：
     #include<iostream>
     #include<string>
     using namespace std;

     class HasPtr
     {
       public:
        HasPtr(const string& s = string()):
            ps(new string(s)),i(0){}
        //对ps指向的string，每个HasPtr对象都有自己的拷贝

        HasPtr(const HasPtr& p)://分配自己的string副本
            ps(new string(*p.ps)),i(p.i){}
        //利用new的深拷贝来解决浅拷贝重复释放的问题
        HasPtr& operator=(const HasPtr&);
        ~HasPtr() { delete ps; }
       private:
        string* ps;
        int i;
      };
      HasPtr&
      HasPtr::operator=(const HasPtr& rhs)
      {
        auto newp = new string(*rhs.ps); //拷贝底层的string
        delete ps;//释放旧的内存
        ps = newp;//从右侧运算对象拷贝数据到本对象
        i = rhs.i;
        return *this;
      }

   (3)行为像指针的类：
      定义拷贝构造函数和拷贝赋值运算符，来拷贝指针成员本身而不是它指向的string
      定义析构函数来释放接受string参数的构造函数分配的内存

      详细程序见下方p457

6、对象移动 C++11标准特性
    
   引入这种特性的原因：在有些时候，移动而非拷贝对象会大幅度的提升性能（在重新分配内存的过程中，从旧内存将元素拷贝到新内存是不必要的，更好的方式是移动元素）
   (一些类如IO或者unique_ptr都不包含可以共享的资源，因此这些类的对象不能拷贝但是可以移动)
   (1)std::move标准库函数
      定义的头文件：utility
      理解：调用move:传达给编译器的信息：希望使用移动构造函数而不是拷贝构造函数
      (或者可以这样认为，这是在告诉编译器：我们有一个左值，但我们希望像一个右值一样来处理它)
           
     作用：显式的将一个左值转换为对应的右值引用类型
      (通过调用该函数来获得绑定到左值上的右值引用)
      举例：
      int&& rr1 = 42;            正确 字面常量是右值
      int&& rr2 = rr1;           错误 rr1表达式是左值（因为这是一个变量）
      int&& rr3 = std::move(rr1);正确 显式的将一个左值转换为对应的右值引用类型
      (调用这个函数意味着对编译器承诺，除了对rr1赋值或者销毁它外，我们将不能再使用它)
   
   (2)右值引用 重点！

      目的：支持移动操作
      性质：必须绑定到右值的引用（换句话说只能绑定到一个将要销毁的对象）
      语法：&&
      结果：我们可以自由的将一个右值引用的资源移动到另一个对象中

      区分：
      左值：表示对象的身份(地址) 比较持久
      右值：表示对象的值         比较短暂（要么是字面常量，要么是在表达式求值过程中创建的临时对象）
      
      用到左值的情况：
      1、赋值运算符需要一个非常量左值作为其左侧运算对象，得到的结果仍然是一个左值
      2、内置解引用运算符、下标运算符、迭代器解引用运算符的求值结果都是左值
      3、内置类型和迭代器的递增递减运算符作用域左值运算对象，其前置版本（++i）所得的结果是左值
      4、变量基本可以视为一个左值（哪怕这个变量是绑定到右值上）
      用到右值的情况：
      取地址符作用于一个左值运算对象，返回一个指向该运算对象的指针，这个指针是一个右值
      
      
      左值引用：不能绑定到要求转换的表达式、字面常量(内置数据类型 10,3.14,'c'等，全是字面值)、返回右值的表达式身上
      可以绑定到返回左值引用的函数、连同赋值、下标、解引用和前置递增、递减运算符           
      
      右值引用：不能直接绑定到一个左值上
      可以绑定到返回非引用类型的函数、连同它的算术、关系、位以及后置递增、递减运算符(const左值引用也可以绑定这些，这是一个例外)
      
      举例：
      int i = 42;
      int& r = i;            正确
      int&& rr = i;          错误 不能将一个右值引用直接绑定到一个左值上
      int& r2 = i * 42;      错误 i*42是一个右值
      const int& r3 = i * 42;正确 可以将一个const的左值引用绑定到一个右值上
      int&& rr2 = i * 42;    正确 标准右值引用
    
   (3)移动构造函数和移动赋值运算符
      
    类似对应的拷贝操作，但它们从给定对象窃取资源而不是拷贝与分配资源
    对应函数形参：右值引用
    注意点：移动后的源对象必须可析构（一般设置为空指针）
    
    1、移动构造函数相比于拷贝构造函数需要多加的操作：将移动后的源对象重置，使其不再指向被移动的资源
    从而保证对这些源对象的析构不会影响到被移动的资源
    举例：
    StrVec::StrVec(StrVec&& s)noxecept //noxecept承诺一个函数不抛出异常
    : elements(s.elements),first_free(s.first_free),cap(s.cap)
    {
        s.elements = s.first_free = s.cap = nullptr； 
        //移动完重置为空指针，确保对它们进行销毁是安全的
    }

    //noexcept 承诺函数不抛出异常 必须在声明和定义中同时标定
    
    为什么使用noexcept?
    显式的告诉标准库我们的移动构造函数可以安全使用

    2、移动赋值运算符
    StrVec& StrVec::operator=(StrVec&& rhs)noexcept
    {
        if(this != & rhs)
        {
            free();
            elements = rhs.elements;
            first_free = rhs.first_free();
            cap = rhs.cap();
            //之后将rhs置于可析构状态
            rhs.elements = rhs.first_free = rhs.cap = nullptr;
        }
        return *this;
    }

    3、合成(默认)的移动操作
       
       只有当一个类没有定义任何自己版本的拷贝控制成员，且类的每个非static数据成员都可以移动时，
       编译器才会为它合成移动构造函数或移动赋值运算符

    4、移动右值 拷贝左值 两者之间的联系
    
       (1)一个类同时有移动构造函数和拷贝构造函数：
          拷贝构造函数形参：const StrVec&
          通过这个底层const可以看出，它可以接受常量与非常量版本的左值对象(底层const可以绑定到一个非常量上)
          又因为const&可以绑定右值，所以该形参同样可以接受右值对象
          因此，这个形参可以用于任何可以转换为StrVec的类型

          移动构造函数形参：StrVec&&
          只能用于实参是右值的类型

          举例：StrVec v1,v2;
                v1 = v2;                    v2是左值(变量)，使用的是拷贝赋值
                StrVec getVec(istream& i);  这个函数返回的是副本，是一个右值
                v2 = getVec(cin);           getVec(cin)是一个右值，精确匹配会使用移动构造
        //最后一行看出，如果调用拷贝赋值运算符需要进行一次非常量到const的转换，而StrVec&&则是精确匹配
        //因此，第二个赋值会使用移动赋值运算符
       
       (2)一个类有拷贝构造函数但是未定义移动构造函数
          在这种情况下，编译器不会合成移动构造函数
          通过函数匹配机制，保证该类型的对象会被拷贝，即使我们试图通过调用move来移动它们也是一样的

          重点：用拷贝构造函数代替移动构造函数几乎肯定是安全的

          举例：class Foo
          {
            public:
                Foo() = default;
                Foo(const Foo&);
          }
          Foo x;
          Foo y(x);             拷贝构造函数，x是一个左值
          Foo z(std::move(x));  拷贝构造函数，因为未定义移动构造函数
          //move(x)返回一个绑定到x的Foo&&，Foo&&隐式的转换为一个const Foo&（const&可以绑定右值引用），因此调用的是拷贝构造

       (3)二者的结合-拷贝/移动赋值运算符
          举例：class HastPtr
               {
                public:
                    HasPtr(HasPtr&& p)noxecept : ps(p.ps),i(p.i){p.ps = 0;}
                    //添加的移动构造函数
                    HasPtr(const HasPtr& p): ps(p.ps),i(p.i){}

                    HasPtr& operator(HasPtr rhs) //注意是非引用参数
                    {swap(*this,rhs);return *this;}
               }
               在这个版本中，我们添加了移动构造函数，构造函数体将给定的HasPtr指针置为空
               从而确保销毁后源对象是安全的，并且标注noxecept确保此函数不抛出异常

               该赋值运算符有一个非引用参数，意味着参数要进行拷贝初始化
               依赖于实参的类型，拷贝初始化要么使用拷贝构造函数，要么使用移动构造函数
               左值被拷贝，右值被移动
               因此，单一的赋值运算符就实现了拷贝赋值运算符和移动运算符两种功能

          举例：hp = hp2;    hp2是一个左值，hp2通过拷贝构造函数来拷贝
                hp = std::move(hp2);移动构造函数移动hp2

    5、移动迭代器(move_iterator)
       作用：解引用运算符生成一个右值的引用
       生成方法：make_move_iterator(iterator) 将一个普通迭代器转换为一个移动迭代器

       StrVec::reallocate()
       {
    
        auto newcapacity = size() ? 2 * size() : 1;
    
        auto first = alloc.allocate(newcapacity);
        //移动元素
        auto last = unitialized_copy(make_move_iterator(begin()),
                                     make)move_iterator(end()),
                                     first);
        free();  //释放旧内存
        elements = first;   //更新指针
        first_free = last;
        cap = elements + newcapacity;
    
        }
        unitialized_copy对输入序列中的每个元素调用construct来将元素"拷贝"到目的位置
        此算法使用迭代器的解引用运算符从输入序列中提取元素，由于我们传递给它的是移动迭代器
        因此解引用运算符生成的是一个右值引用
        这意味着construct将使用移动构造函数来构造元素

    6、右值引用与成员函数

        建议：一个成员函数最好同时提供拷贝和移动两个版本
        一个版本接受一个指向const的左值引用（可以接受此对象的任何类型）  重点！！！
        第二个版本接受一个指向非const的右值引用(只接受右值类型)
       
       void push_back(const T&);  绑定到任意类型的T
        void push_back(T&&);       只能绑定到类型T的可修改的右值

        引用限定符：&和&&，分别指出this可以指向一个左值或右值(类似const限定符)
        如果同时有const和&限定符 则写法为 const &

        举例：
        class Foo
        {
          public:
            Foo sorted()&&;  指向一个可改变的右值
            Foo sorted()const &;  可用于任何类型的Foo
          private:
            vector<int>data;
        }
        Foo Foo::sorted()&&
        {
            sort(data.begin(),data/end());  本对象是右值，因此可以原址排序
            return *this;
        }
        Foo Foo::sorted()const &
        {
            //本函数的匹配是const或者是一个左值，不可以进行原址排序，只能返回副本
            Foo ret(*this);   拷贝一个副本
            sort(ret.data.begin(),ret.data.end()); 排序副本
            return ret;    返回副本
        }
        */


/*
#include<iostream>
#include<string>
using namespace std;

class Sales_data
{
public:
    Sales_data(const Sales_data&);//自定义的拷贝构造函数
    Sales_data& operator=(const Sales_data&);//自定义的拷贝赋值运算符
private:
    string bookNo;
    int units_sold = 0;
    double revenue = 0;
};

Sales_data::Sales_data(const Sales_data& orig):
    bookNo(orig.bookNo),
    units_sold(orig.units_sold),
    revenue(orig.revenue) {}  //空函数体

Sales_data&
Sales_data::operator=(const Sales_data& rhs)
{
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
}
*/

/*

p449 t13.1.4

#include<iostream>
#include<string>

class numbered
{
public:
    numbered()
    {
        mysn = unique++;
    }
    numbered(const numbered& n)
    {
        mysn = unique++;
    }
    int mysn;
    static int unique;
};
int numbered::unique = 10;

void f(const numbered& s)
{
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}
*/


/*

//拷贝控制与资源管理的应用程序 p457 定义一个使用引用计数的类
#include<iostream>
#include<string>
using namespace std;

class HasPtr
{
public:
    HasPtr(const string& s = string()):
        ps(new string(s)),use(new size_t(1)){}

    //拷贝构造函数拷贝所有三个数据成员 并递增计数器
    HasPtr(const HasPtr& p):
        ps(p.ps), i(p.i), use(p.use) { ++*use;};
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
private:
    string* ps;
    int i;
    size_t* use; //用来记录有多少个对象共享*ps的成员
};

HasPtr::~HasPtr()
{
    if (-- * use == 0) //如果引用计数变为0 这里已经提前-1
    {
        delete ps;  //释放string内存
        delete use; //释放计数器内存
    }
}

HasPtr&
HasPtr::operator=(const HasPtr& rhs)
{
    ++* rhs.use; //递增右侧运算对象的引用次数
    if (-- * use == 0) //然后递减本对象的引用次数
    {
        delete ps;    //如果没有其他用户就释放本对象分配的成员了，  
        delete use;   //否则还是保留，只更改该指针指向的值（因为原管理资源还有其他成员引用）
    }                 //至于释放原指针指向的new的内存的问题，交给最后一个需要释放这个内存的析构对象来解决。
   
   //这一步相当于拷贝赋值运算符包含析构函数
   
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}
*/


/*
//拷贝控制实例2 消息控制

#include<iostream>
#include<string>
#include<set>
#include<memory>
using namespace std;

class Folder;//类声明
class Message;

class Message
{
    friend class Folder;
    friend void swap(Message& lhs, Message& rhs);
public:
    explicit Message(const string& str = " "):
        contents(str){}
    //拷贝控制成员 用来管理指向本Message的指针
    Message(const Message&);
    Message& operator=(const Message&); //拷贝赋值运算符
    ~Message();
    void save(Folder&); //向给定的Folder中添加或者删除一条Message
    void remove(Folder&);
private:
    string contents; //实际消息文本
    set<Folder*>folders; //保存指向本Message的所有Folder的指针 也就是包含本Message的Folder列表

    void add_to_Folders(const Message&); //将本message添加到指向m的Folder中
    void remove_from_Folders();
};

void Message::save(Folder& f) //将消息保存到消息列表中
{
    folders.insert(&f); //将给定Folder添加到我们的Folder列表中
    f.addMsg(this);     //将本Message添加到f的Message集合中
}
void Message::remove(Folder& f) //从消息列表中删除消息
{
    folders.erase(&f); //将给定Folder从我们的Folder列表中删除
    f.remMsg(this);    //将本Message从f的Message集合中删除
}
//f.addMsg 和f.remMsg相当于分别添加和删除给定Message的指针

//拷贝 采用指针拷贝 并且更新Folder
void Message::add_to_Folders(const Message& m)
{
    for (auto f : m.folders) //对每个包含m的Folder
        f->addMsg(this);   //向该Folder中添加一个指向本Message的指针
}
Message::Message(const Message& m) :contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

//从Folder中删除本Message
void Message::remove_from_Folders()
{
    for (auto f : folders)
        f->remMsg(this);
}
Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message& rhs) //作用相当于拷贝加析构
{
    //通过先删除指针再插入它们来处理自赋值的情况
    remove_from_Folders();//更新已有的Folder
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);//将本Message添加到哪些Folder中
    return *this;
}

void swap(Message& lhs, Message& rhs)
{
    //using std::swap; //声明std的swap 之后使用的是我们自定义的swap
    ////将每个消息的指针从它原来的Folder中删除
    //for (auto f : lhs.folders)
    //    f->remMsg(&lhs);
    //for (auto f : rhs.folders)
    //    f->remMsg(&rhs);

    ////交换contents和Folder的指针set
    //swap(lhs.folders, rhs.folders); //使用swap(set&,set&)
    //swap(lhs.contents, rhs.contents);
    ////将每个Message的指针添加到它的新Folder中
    //for (auto f : lhs.folders)
    //    f->addMsg(&lhs);//添加指针
    //for (auto f : rhs.folders)
    //    f->addMsg(&rhs);

    using std::swap;
    lhs.remove_from_Folders();
    rhs.remove_from_Folders();

    swap(lhs.folders, rhs.folders); //使用swap(set&,set&)
    swap(lhs.contents, rhs.contents);

    lhs.add_to_Folders(lhs);  //自己调用自己
    rhs.add_to_Folders(rhs);
}

class Folder
{
    friend class Message;
    friend void swap(Folder&, Folder&); 
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();
    void print_debug();
private:
    set<Message*>msgs;
    void add_to_Message(const Folder&);
    void remove_from_Message();

    void addMsg(Message* m) { msgs.insert(m); }
    void remMsg(Message* m) { msgs.erase(m); }
};
void swap(Folder&, Folder&);

*/

/*

//vector类的简易实现
#include<iostream>
#include<string>
#include<memory>
#include<utility>
using namespace std;

class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();

    void push_back(const string&);
    size_t size()const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

    string* begin()const { return elements; }
    string* end()const { return first_free; }

    void print()
    {
        for (auto iter = elements; iter != first_free; iter++)
            cout << *iter << endl;
    }

private:
    allocator<string>alloc; //分配元素

    void chk_n_alloc()
    {
        if (size() == capacity()) reallocate();
    }

    pair<string*, string*>alloc_n_copy(const string*, const string*);

    void free();        //销毁元素并释放内存
    void reallocate();  //获得更多内存并拷贝已有的元素
    string* elements;   //指向数组首元素的指针
    string* first_free; //指向数组第一个空闲元素的指针
    string* cap;        //指向数组尾后元素的指针
};

void StrVec::push_back(const string& s)
{
    chk_n_alloc(); //确保有空间容纳新元素
    //在first_free指向的元素中构造s的副本
    //a.construct(p, args); p必须是一个类型为T* 的指针，指向一块原始内存，
    //args被传递给类型为T的构造函数，用来在p指向的内存中构造一个对象
    
    alloc.construct(first_free++, s);
    
    //传递给construct的第一个参数必须是一个指针，指向allocate所分配的未构造的内存空间
    //剩余参数确定用哪个构造函数来构造对象
    //该调用会在first_free当前值指定的地址构造一个对象，并递增first_free指向下一个未构造的元素
}

pair<string*, string*>
StrVec::alloc_n_copy(const string* b, const string* e)
{
    //分配空间保存给定范围内的元素
    auto data = alloc.allocate(e - b);
    //返回的data是一个指针  指向该内存中最后一个构造的元素之后的位置
    //初始化并返回一个pair，该pair由data和unititlized_copy返回值构成
    
    return { data,uninitialized_copy(b,e,data) }; //已经构造了原始内存空间，并返回
    
    //data是分配的内存开始的位置 unitialized_copy返回构造的最后一个元素之后的位置
    //将b到e的元素拷贝到data指定的未构造的内存中，返回一个指针，指向最后一个构造的元素的之后的位置
}

void StrVec::free()
{
    //不能传递给deallocate一个空指针，如果elements为0，函数什么都不做
    if (elements)
    {
        //逆序销毁旧元素
        for (auto p = first_free; p != elements; )
            alloc.destroy(--p);//先递减才能销毁
       
       //释放内存空间(含义是该类本身就有这个已经分配的内存空间)

        alloc.deallocate(elements, cap - elements);
        //  alloc.deallocate(p, n);  释放之前分配的s所有原始内存
        //传递给deallocate的指针必须是之前某次allocate调用所返回的指针
    }
}

StrVec::StrVec(const StrVec& s)
{
    //调用alloc_n_copy分配空间以容纳与s中一样多的元素
    auto newdata = alloc_n_copy(s.begin(), s.end());
    //返回的是一个pair 保存两个指针 
    //第一个指针指向第一个构造的元素 第二个指针指向最后一个构造的元素之后的位置
    elements = newdata.first;
    first_free = newdata.second;
}

StrVec::~StrVec()
{
    free();
}

StrVec&   //相当于把析构和拷贝构造结合在一起 利用自赋值来进行测试
StrVec::operator=(const StrVec& rhs)
{
    //调用alloc_n_copy分配内存，大小与rhs中的元素占用空间一样多
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();//释放自己的空间，销毁自己的 原有元素
    elements = data.first;
    first_free = cap = data.second;
    //alloc_n_copy分配的空间恰好容纳给定的元素，cap也指向最后一个构造的元素之后的位置
    return *this;
}

//包含移动构造的含义
void StrVec::reallocate()
{
    //我们将分配当前大小2倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    //分配新内存
    auto newdata = alloc.allocate(newcapacity);
    //返回的newdata是首次内存分配的位置，也就是内存的首地址空间
    //将数据从旧内存移动到新内存
    auto dest = newdata;//指向新数组中下一个未构造位置，也就是初始地址
    auto elem = elements;//旧数组中的第一个开头元素的指针
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    //注意是后置递增 先传递完现有的元素值 再递增指针
    free(); //一旦移动完元素就释放旧内存空间
    //我们不知道旧内存中的string现在包含什么值，但C++保证对它们执行string的析构函数是安全的
    //接下来更新我们的数据结构，执行新元素
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;//蕴含指针的运算

}

int main()
{
    StrVec vec,vec2;
    vec.push_back("hello");
    vec.push_back("vslam");
    vec.push_back("aaa");
    vec.push_back("bbb");
    vec.push_back("ccc");
    int size = vec.size();
    int capacity = vec.capacity();
    vec.print();
    cout << size << endl;
    cout << capacity << endl;

    
    vec2.push_back("hello");
    vec2.push_back("vslam");
    vec2.push_back("aaa");

    vec2 = vec;
    int size2 = vec2.size();
    int capacity2 = vec2.capacity();
    cout << size2 << endl;
    cout << capacity2 << endl;


    return 0;
}

*/


/*
#include<iostream>
#include<string>
#include<memory>
#include<initializer_list>


using namespace std;

class StrVec
{
public:
    StrVec() : elements(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec&);
    StrVec(initializer_list<string>);
    StrVec(StrVec&&)noexcept;            //移动构造函数
    StrVec& operator=(const StrVec&);
    StrVec& operator=(StrVec&&)noexcept; //移动赋值运算符
    ~StrVec();

    void push_back(const string&);
    size_t size()const { return first_free - elements; }
    size_t capacity()const { return cap - elements; }
    string* begin()const { return elements; }
    string* end()const { return first_free; }

    void reserve(size_t new_cap);
    void resize(size_t count);
    void resize(size_t count, const string&);
    void print();

private:
    pair < string*, string*>alloc_n_copy(const string*, const string*);
    
    void free();
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    void reallocate();
    void alloc_n_move(size_t new_cap);
    void range_initialize(const string*, const string*);
private:
    string* elements;
    string* first_free;
    string* cap;
    allocator<string>alloc; //内存分配器
};

void StrVec::push_back(const string& s)
{
    chk_n_alloc(); //查看需不需要重新分配内存空间
    alloc.construct(first_free++, s);
}

pair<string*,string*>
StrVec::alloc_n_copy(const string* b, const string* e)
{
    auto data = alloc.allocate(e - b); //已经构造了原始内存空间 并且返回了它的地址
    return{ data,uninitialized_copy(b,e,data) };
}

void StrVec::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
    
}

void StrVec::range_initialize(const string* first, const string* last)
{
    auto newdata = alloc_n_copy(first, last);
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(const StrVec& rhs)
{
    range_initialize(rhs.begin(), rhs.end());
}

StrVec::~StrVec()
{
    free();
}

StrVec& StrVec::operator=(const StrVec& rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::alloc_n_move(size_t new_cap)
{
    auto newdata = alloc.allocate(new_cap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + new_cap;
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    alloc_n_move(newcapacity);
}

void StrVec::reserve(size_t new_cap)
{
    if (new_cap <= capacity())return;
    alloc_n_move(new_cap);
}
void StrVec::resize(size_t count)
{
    resize(count, string());
}
void StrVec::resize(size_t count, const string& s)
{
    if (count > size())
    {
        if (count > capacity())reserve(count * 2);
        for (size_t i = size(); i != count; ++i)
            alloc.construct(first_free++, s);
    }
    else if (count < size())
    {
        while (first_free != elements + count)
            alloc.destroy(--first_free);
    }
}

void StrVec::print()
{
    for (auto iter = elements; iter != first_free;iter++)
        cout << *iter << " ";
}

StrVec::StrVec(StrVec&& s)noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}
StrVec& StrVec::operator=(StrVec&& rhs)noexcept
{
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}


int main()
{
    StrVec vec, vec2;
    vec.push_back("hello");
    vec.push_back("vslam");
    vec.push_back("aaa");
    vec.push_back("bbb");
    vec.push_back("ccc");
    int size = vec.size();
    int capacity = vec.capacity();
    vec.print();
    cout << size << endl;
    cout << capacity << endl;


    vec2.push_back("hello");
    vec2.push_back("vslam");
    vec2.push_back("aaa");

    vec2 = vec;
    int size2 = vec2.size();
    int capacity2 = vec2.capacity();
    cout << size2 << endl;
    cout << capacity2 << endl;


    return 0;
}
*/
