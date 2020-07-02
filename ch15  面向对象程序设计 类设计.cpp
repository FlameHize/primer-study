/*
1、三大基本概念：数据抽象 继承 动态绑定
	
   数据抽象：将类的接口与实现分离
   继承：定义相似的类型并对其相似关系建模
   动态绑定：在一定程度上忽略相似类的区别，而以统一的方式使用它们的对象
   
   建议：基类通常都应该定义一个虚析构函数，即使该函数不执行任何实际操作也是如此
  
   设计理念：遵循基类的接口
   每个类负责定义各自的接口，要想与类的对象交互必须使用该类的接口，即使这个对象是派生类的基类部分也是一样
   因此，派生类不能直接初始化基类的成员（尽管从语法上面来说可以这么做）
   和使用基类的其他场合一样，派生类应该遵循基类的接口，并且通过调用基类的构造函数来初始化哪些从基类中继承而来的成员


2、基类、派生类与动态绑定   
   
   (1)定义基类和派生类
      
      在C++中，基类必须将它的两种成员函数区分开来
      
      一种是基类希望其派生类进行覆盖的函数
      
      通常将其定义为虚函数 在成员函数前面加上virtual关键字
      (virtual关键字只能出现在类内部的声明语句之前而不能用于外部的函数定义)
      当我们使用指针或引用调用该虚函数时，该调用将动态绑定，根据引用或指针所绑定的类型不同
      该调用可能执行基类的版本，也可能执行某个派生类的版本
      
      C++11新标准允许派生类显式的注明它将使用哪个成员函数改写基类的虚函数
      具体措施是在该函数的形参列表之后增加一个override关键字
      
      派生类成员函数后加入override关键字：标注显式继承虚函数
      该关键字的另外一个作用：
        如果派生类定义了一个函数与基类中虚函数的名字相同但是形参列表不同
        这仍然是合法的行为，但是编译器将认为这个新定义的这个函数与基类中原有的函数是相互独立的
        这是，派生类的函数并没有覆盖掉基类的版本(很大可能发生错误)(但是很难发现以及处理)
        如果我们使用override标明了某个函数，但该函数并没有覆盖已存在的虚函数，此时编译器将报错

      
      另一种是基类希望派生类直接继承而不要改变的函数
      

      派生类的构造函数：

        尽管在派生类对象中含有从基类继承而来的成员，但是派生类并不能直接初始化
        这些成员，派生类必须使用基类的构造函数来初始化它的基类部分
        举例：
        Buik_quote(const string& book, double p, size_t qty, double disc):
        Quote(book,p),min_qty(qty),discount(disc){}
        首先构造基类的部分，然后按照声明的顺序依次初始化派生类的成员
   
   (2)派生类对象到基类的隐式转换
      
      当我们用一个派生类对象为一个基类对象初始化或者赋值时，只有该派生类对象中的
      基类部分会被拷贝、移动或者赋值，它的派生类部分将会被忽略掉

      举例：
      Quote item;
      Bulk_Quote bulk;
      Quote* p = &item;   p指向Quote对象
      p = &bulk;          p指向bulk的Quote部分
      Quote& r = bulk;    r绑定到bulk的Quote部分


      动态绑定：我们可以将基类的指针或引用绑定到派生类对象上
      且从派生类向基类的类型转换只对指针或者引用类型有效
      (当我们使用基类的指针或引用时，实际上我们并不清楚
      该引用或者指针所绑定对象的真实类型，该对象可能是基类的对象，也可能是派生类的对象)
   
      为什么可以进行这种绑定？
      原因：因为每个派生类对象都包含一个基类部分，而基类的引用或者指针可以绑定到该基类部分上

      也因此，不存在从基类向派生类的隐式类型转换(否则我们可能会使用派生类指针访问基类中不存在的成员)

   (3)继承与静态成员
      
      如果基类定义了一个静态成员，那么在整个继承体系中只存在该成员的唯一定义
      不论从基类中派生出来多少个派生类，对于每个静态成员来说都只存在唯一的实例

      举例：
      class Base
      {
        public:
            static void statmem();
      }
      class Dervied : public Base
      {
        void f(const Dervied&);
      }
      
      void Dervied::f(const Dervied& dervied_obj)
      {
        Base::statmem();      正确 Base定义了statmem
        Dervied::statmem();   正确 Derived定义了statmem   
        dervied_obj.statmem();正确 通过Derived对象访问
        statmem();            正确 通过this对象访问
      }
   
   (4)如何防止继承的发生？
      在类名后面加入final关键字
      我们当然也可以把某个函数定义为final
      如果我们已经把函数定义成final的了
      则之后任何尝试覆盖掉该函数的操作都将引发编译错误

   (5)虚函数与默认实参
      
      如果某次函数调用使用了默认实参，则该实参值由本次调用的静态类型决定
      换句话说，这与动态绑定思想相违背
      如果我们通过基类的指针或引用调用了函数，则使用基类中定义的默认实参
      即使实际运行的是派生类的函数版本(传入的是基类的默认实参而不是动态绑定的派生类)
      
      建议：最好不要使用默认实参 (虚函数非要使用的话,则基类和派生类中定义的默认实参最好一致)


      如何回避虚函数的机制? 使用作用域解析符进行显式调用
      double undiscounted = baseP->Quote::net_price(42);
      

3、抽象基类--数据抽象

   抽象基类：表示一个抽象的概念，不能直接创建具体的实例对象
             也就是不能创建抽象基类的对象

   什么样的类是抽象基类？
   答案：含有(或者未经覆盖直接继承)纯虚函数的类是抽象基类

   纯虚函数：一个在类内声明的没有定义的虚函数，在分号之前加 =0 即可
   (纯虚函数只能出现在类内部的声明中)
   举例：virtual double net_price(size_t )const  = 0;
   
4、访问控制和继承
   
   某个类对其继承而来的成员的访问权限受两个因素影响
     1、在基类中该成员的访问说明符（控制子类成员内部对父类数据的访问权限）
     2、在派生类的派生列表中的访问说明符（控制子类外部用户对于父类成员的访问权限）

   (1)protected:

    声明那些希望与派生类分享但是不想被其他公共访问使用的成员
    (和私有成员类似，受保护的成员对于类的用户来说是不可访问的
    和公有成员类似，受保护的成员对于派生类的成员和友元来说是可访问的)
    
    派生类的成员或友元只能通过派生类对象来访问基类的protected成员
   
   (2)公有、私有和保护继承
            
      公有继承：成员将遵循其原有的类内访问说明符 ！！！ 重点
      (公有继承中，派生类反映与基类的“是一种”关系 也就是IS A)
      
      私有继承：派生类的继承而来的成员全部都是私有的

      保护继承：基类的的所有公有成员对它的派生类来说都是受保护的
      
      友元关系不可以继承

      举例：
      class Base
      {
        public:
            void pub_num();
        protected:
            int prot_num;
        private:
            char priv_num;
      }
      struct Pub_Derv : public Base
      {
        inf f() { return prot_num;}  //正确 派生类能够访问父类protected成员
        char g() { return priv_num;} //错误 派生类不能访问基类的private成员
      }
      struct Priv_Derv : private Base
      {
        inf f1() { return prot_num;}  //正确 派生类能够访问父类的protected成员
                                      //private继承与派生类的内部访问权限无关
      }

      注意类内部与类外部的区别 一个是成员 一个是用户

      派生类的内部成员（及友元）能否访问其直接基类的成员
      只与基类成员的访问说明符有关，而与派生列表的访问说明符无关

      派生访问说明符的目的：
      控制派生类的外部用户（包括派生类的派生类）
      对于基类成员的访问权限

      Pub_Derv d1;   public继承Base
      Priv_Derv d2;  private继承Base
      d1.pub_num();  正确 pub_num在派生类中是public的
      d2.pub_num();  错误 pub_num在派生类中是private的

      派生类向基类转换的可访问性：
      只有当D公有的继承B时，用户代码才能使用派生类向基类的转换
      不论D以什么方式继承B，D的成员函数和友元都能使用派生类向基类的转换


      总结(重点)：

      不考虑继承的话：
        一个类有两个不同的用户：普通用户和类的实现者
         普通用户：编写的代码使用类的对象(如使用封装好的STL)
                   这部分代码只能访问类的公有(接口)成员
         类的实现者：负责编写类的成员和友元的代码 
                     成员和友元既能访问类的公有部分，也能访问类的私有(实现)部分（一般将用到的数据变量设置为私有的，防止外部访问和篡改）
      
      考虑继承的话： 
        出现第三者用户 即派生类
         派生类：基类把它希望派生类能够使用的部分声明为保护的
                 普通用户不能访问受保护的成员，而派生类及其友元仍旧不能访问基类的私有成员（因为需要访问的都设计成protected）
      
      因此，一个基类应该做到：
        将接口成员声明为公有的
        将属于其实现的部分分成两组：
             可供派生类访问，声明为受保护的
             只能由基类及其友元访问，声明为私有的
      
      类的派生列表访问说明符：最好设置为公有继承，不改变基类内部原有的访问说明符

      
      问题：如何改变个别成员的可访问性？
      答案：使用using说明

      class Base
      {
        public:
            size_t size() const{ return n;}
        protected:
            size_t n;
      }
      class Derived : private Base
      {
        public:
            using Base::size;
        protected:
            using Base::n;
      }

      因为使用了私有继承，所以继承的成员size和n在默认下都是
      派生类Derived的私有成员 
      通过在类的内部使用using声明语句，可以改变成员的可访问性
      Derived的外部用户将可以使用size成员 
      而Derived的派生类将能够使用n

5、继承中的类作用域
   
   (1)总则：当存在继承关系时，派生类的作用域嵌套在其基类的作用域之内
         如果一个名字在派生类的作用域中无法正确解析，则编译器将继续在外层的基类作用域中寻找该名字的定义
         (关键：从派生类向基类依次向上搜索)
   
   (2)名字查找的时间：在编译时进行名字查找
       因此，一个对象、引用或者指针的静态类型决定了该对象的哪些成员是可见的。
       即使静态类型与动态类型可能不一致，但是我们能使用哪种成员仍然是由静态类型决定的
       举例：
       class Disc_quote : public Quote
       {
        public:
            pair<size_t,double> discount_policy()const
                { return {quantity,discount};}
       };

       Bulk_quote bulk;
       Bulk_quote* bulkp = &bulk; //静态类型与动态类型一致
       Quote* itemP =  &bulk;     //静态类型与动态类型不一致
       bulkP->discount_policy();  //正确
       itemP->discount_policy();  //错误

       (Quote->Disc_quote->Bulk_quote)
       itemP   discount_policy()   bulk
       尽管在bulk中确实有 一个discount_policy的成员，
       但是该成员对于其间接基类-Quote itemP是不可见的
       itemP的静态类型是Quote的指针
       因此对discount_policy的搜索将从Quote开始 找不到 就引发错误
       (名字查找只会向上查找 而不会向下查找)
   
   (3)名字冲突
       定义在内层作用域(派生类)的名字会隐藏定义在外层作用域(基类)中的名字
       想调用基类的话可以通过显式的作用域解析符进行调用

       举例：
       class Base
       {
          int memfcn();
       }
       class Derived : public Base
       {
          int memfcn(int);
       }
       Derived d,Base b;
       b.memfcn();
       d.memfcn(10);
       d.memfcn();          错误 参数列表为空的memfcn成员被隐藏了
       d.Base::memfcn();    正确 调用Base::memfcn

       为了解析d.memfcn()这条语句，编译器首先在Derived中查找名字memfcn
       因为Derived确实定义了一个名为memfcn的成员 所以查找过程停止
       一旦名字找到，编译器就不再继续查找了
       Derived的memfcn版本需要一个int实参，而当前的调用语句无法提供任何实参
       所以该调用语句是错误的

       也因为这个名字冲突原因，所以基类与派生类的虚函数必须有相同的形参列表
       (如果列表不同，则虚函数会被隐藏掉)


   (4)总结的关键概念--名字查找与继承
      
      先名字检查，再类型检查，再看是否是虚函数调用

      步骤：(调用p->mem() / obj.mem())

      1、首先确定p或obj的静态类型
      2、在p或obj的静态类型对应的类中查找mem，如果找不到，则依次在直接基类中不断查找直至达到继承链的顶端，如果找遍了该类及其基类仍然找不到，则编译器将报错
      3、一旦找到mem，就进行常规的类型检查(参数类型、返回类型等)，以确认对于本次找到的mem,本次调用是否合法
      4、调用合法 进行判断
          (1)如果mem是虚函数 且 是通过指针或引用进行的调用
             则编译器依据对象运行的动态类型确定运行虚函数的哪个版本
          (2)如果mem不是虚函数或者我们是通过对象而不是引用或指针进行的调用
             则产生一个常规函数的调用
             （注意这里的 且 和 或）

6、构造函数与拷贝控制

   (1)虚析构函数
      基类的析构函数应该定义成虚析构函数（确保动态类型执行正确的析构函数版本）
      确保我们delete基类指针时将运行正确的析构函数版本

      举例：
      Quote* itemP = new Quote;   //静态类型与动态类型一致
      delete itemP;               // 调用Quote的析构函数
      itemP = new Bulk_quote;     //静态类型与动态类型不一致
      delete itemP;               //调用Bulk_quote的析构函数
      (如果基类的析构函数不是虚函数，则delete一个指向派生类对象的基类指针将会产生未定义的行为)

      在Quote继承体系中，所有类都使用默认的合成析构函数，其中
      派生类隐式的使用而基类通过将析构函数定义成=delfault而显式的使用
      对于派生类的析构函数来说，它除了销毁派生类自己的成员外，还负责销毁派生类的直接基类
      该直接基类又销毁它自己的直接基类，以此类推直至继承连的顶端
      （析构函数只负责销毁派生类自己分配的资源）

      析构顺序：与构造相反，派生类析构首先执行，然后是基类的析构
      以此类推，沿着继承体系的反方向直至终止
      （因为存在时间前后问题，所以如果我们定义的构造或者析构函数调用了某个虚函数
      则我们应该执行与构造函数或析构函数所属类型相对应的虚函数版本）

   (2)派生类中删除的拷贝控制与基类的关系
       
       如果基类中的默认构造、拷贝构造、移动构造、拷贝赋值运算符或析构函数
       是被删除的函数或不可访问，则派生类中对应的成员是删除的

       如果基类中有一个不可访问或者删除的析构函数，则派生类中合成的
       默认和拷贝构造、移动构造函数是删除的，因为编译器无法销毁派生类对象的基类部分

       如果一个类定义了自己的拷贝构造函数、拷贝赋值运算符或者析构函数
       编译器就不会为它合成移动构造函数和移动赋值运算符了 
       这点在继承中也一样，如果基类删除了自己的显式拷贝构造，且派生类没有重新
       定义自己的移动构造或者拷贝构造 则派生类不能进行拷贝和移动
       
       定义了一个移动构造函数或移动赋值运算符的类必须也定义自己的拷贝操作
       否则这些移动的操作默认的被定义成删除的

       最好的方法：全部默认定义出来  六个基本函数
       class Quote
       {
        public:
            Quote() = default;                       对成员进行默认初始化
            Quote(const Quote&) = default;           对成员依次拷贝
            Quote(Quote&&) = default;                对成员依次移动拷贝
            Quote& operator=(const Quote&) = default;拷贝赋值
            Quote& operator=(Quote&&) = default;     移动赋值
            virtual ~Quote() = default;              虚析构
       }
       除非Quote的派生类中含有排斥移动的成员，否则它将自动的获得合成的移动操作

   (3)派生类的拷贝控制成员

      当派生类定义了拷贝或者移动操作时，该操作负责拷贝或移动包括基类部分成员在内的整个对象
      所以通常在派生类的构造函数初始化列表中使用基类的构造函数来初始化对象的基类部分

      class Base;
      class D : public Base
      {
        public:
            D(const D& d) : Base(d),/D自己分配的成员初始化/
            D(D&& d) : Base(std::move(d)),/D自己分配的成员初始化/
      }
      D类型的对象d将被绑定到该构造函数的const Base&形参或者Base&&形参
      Base的拷贝构造或者移动构造函数负责将d的基类部分进行拷贝或者移动初始化操作

      同样的，派生类的赋值运算符也必须显式的为基类部分赋值
      D& D::operatr=(const D& rhs)
      {
            Base::operator=(rhs); //显式的为基类赋值
            //派生类自己的成员赋值
            //析构
            return *this;
      }

   (4)继承的构造函数
      只能继承直接基类的构造函数
      方法：提供一条注明了直接基类名的using语句
      class Bulk_quote : public Disc_quote
      {
        public:
            using Disc_quote::Disc_quote;  //继承Disc_quote的构造函数
            double net_price(size_t) const;
      }
      对于基类的每个构造函数，编译器都生成一个与之对于的派生类构造函数

      等价于
      Bulk_quote(const string& book,double price,size_t qty,double disc)
      : Disc_quote(book,price,qty,disc){}

      如果派生类有自己的数据成员，则这些成员被默认初始化


   */


//基类和派生类初探

/*

#include<iostream>
#include<string>
using namespace std;

class Quote
{
public:
    Quote() = default;
    Quote(const string& book,double sales_price):
        bookNo(book),price(sales_price){}
    string isbn() const { return bookNo; }
    virtual double net_price(size_t n)const //虚函数，派生类负责改写并使用不同的折扣计算方法
    {
        return n * price;
    }
    virtual ~Quote() = default;   //必须对析构函数进行动态绑定
       
private:
    string bookNo;
protected:
    double price = 0.0;
};

class Bulk_quote : public Quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const string& book, double p, size_t qty, double disc):
        Quote(book,p),min_qty(qty),discount(disc){}

    double net_price(size_t)const override;
    //覆盖基类的函数版本以实现基于大量购买的折扣政策

private:
    size_t min_qty = 0;  //适用折扣政策的最低购买量
    double discount = 0.0;  //以小数表示的折扣额
};

double Bulk_quote::net_price(size_t cnt)const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

*/



//利用抽象基类进行重构

/*

#include<iostream>
#include<string>
#include<memory>
#include<set>

using namespace std;

class Quote
{
public:
    Quote() = default;
    Quote(const string& book, double sales_price) :
        bookNo(book), price(sales_price) {}
    string isbn() const { return bookNo; }
    virtual double net_price(size_t n)const //虚函数，派生类负责改写并使用不同的折扣计算方法
    {
        return n * price;
    }
    virtual ~Quote() = default;   //必须对析构函数进行动态绑定

private:
    string bookNo;
protected:
    double price = 0.0;
};

class Disc_quote : public Quote
{
public:
    Disc_quote() = default;
    Disc_quote(const string& book,double price,size_t qty,double disc):
        Quote(book,price),quantity(qty),discount(disc){}

    //纯虚函数 有了这个函数才表示这个类是抽象基类
    virtual double net_price(size_t) const = 0;

protected:
    size_t quantity = 0;  //折扣适用的购买量
    double discount = 0.0; //表示折扣的小数值
};

class Bulk_quote : public Disc_quote //直接基类Disc_quote 间接基类Quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const string& book,double price,size_t qty,double disc):
        Disc_quote(book,price,qty,disc){}   //注意初始化的是四个成员(还都不是自己的)

    //覆盖掉基类中的函数虚函数版本以实现一种新的折扣策略
    virtual double net_price(size_t n)const override;
};

double Bulk_quote::net_price(size_t cnt)const
{
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}
//Bulk_quote的构造函数接受四个参数，该构造函数将它的实参传递给
//Disc_quote的构造函数，随后Disc_quote的构造函数继续调用Quote的构造函数
//Quote的构造函数首先初始化bulk的bookNo和price成员，当Quote的构造函数结束后
//开始运行Disc_quote的构造函数并初始化quantity和discount成员
//最后运行Bulk_quote的构造函数，该函数无须执行实际的初始化或其他工作

//再定义一个表示购物篮的类 利用容器来进行一些操作
class Basket
{
public:
    void add_item(const shared_ptr<Quote>& sale)
    {
        items.insert(sale); //蕴含动态绑定技术 可以将派生类的指针自动转换为基类的指针
    }
    //打印每本书的总价和购物篮中的书的总价
    double total_receipt(ostream&)const;
private:
    //比较函数定义成一个静态函数 所有的实例化类都只用这一个进行比较
    static bool compare(const shared_ptr<Quote>& lhs, const shared_ptr<Quote>& rhs)
    {
        return lhs->isbn() < rhs->isbn();
    }
    multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
    //初始化需要添加所需操作的函数指针并用该指针进行容器的初始化
    //从左向右读，该语句定义了一个指向Quote对象的shared_ptr的mulitset
    //这个multiset将使用一个与compare成员类型相同的函数来对其中的元素进行排序
    //multiset成员的名字是items，初始化items并令其使用compare函数
};
double print_total(std::ostream& os, const Quote& item, size_t n)
{
    double ret = item.net_price(n);

    os << "ISBN:" << item.isbn()
        << "# sold: " << n << " total due: " << ret << std::endl;

    return ret;
}


double Basket::total_receipt(ostream& os)const
{
    double sum = 0.0;
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
    {                                                      //调用upper_bound函数令我们跳过与当前关键字相同的所有元素,返回一个所有相等的元素之后一个位置的迭代器
        sum += print_total(os, **iter, items.count(*iter));//也就是指向下一本书籍
    }                           //解引用得到Quote或其派生类对象 采用动态绑定
    os << "Total Sale:" << sum << endl;
    return sum;
    //shared_ptr的地址，如果指向相同的对象 是相同的 因此可以通过*iter来判断
}

int main()
{
    Basket basket;

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(make_shared<Bulk_quote>("Bible", 20.6, 20, 0.3));

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(make_shared<Bulk_quote>("C++Primer", 30.9, 5, 0.4));

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(make_shared<Quote>("CLRS", 40.1));

    
    basket.total_receipt(cout);
    return 0;
}

*/



/*
//文本查询程序2.0版本 支持逻辑运算符 1.0版本在ch12

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
    os << qr.sought << "occurs" << qr.lines->size() << endl;  //qr.lines是一个指向set<line_no>容器的指针
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


//之前是1.0版本内容 下面加入查询类以支持不同的运算符



//这是一个抽象基类，具体的查询类型从中派生，所有的成员都是私有的
class Query_base
{
    friend class Query;
    //因为我们不希望用户或者派生类可以直接使用Query_base 所以它没有public成员
protected:
    typedef TextQuery::line_no line_no;
    virtual ~Query_base() = default;
private:
    //eval返回与当前Query匹配的QueryResult
    virtual QueryResult eval(const TextQuery&)const = 0;
    virtual string rep() const = 0; //生成查询的string文本
};

//这是一个管理Query_base继承体系的接口类
class Query
{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const string&); //构建一个新的wordQuery

    QueryResult eval(const TextQuery& t)const 
    { return q->eval(t); }
    string rep()const { return q->rep(); }
    //定义接口函数，调用对于的Query_base操作

private:
    
    Query(shared_ptr<Query_base>query) : q(query){}
    //利用智能指针进行初始化的构造函数
    //Query操作使用它的Query_base指针来调用各自的Query_base虚函数
    //实际调用哪个函数版本将由q所指向的对象类型决定(动态绑定技术)
    shared_ptr<Query_base>q; //每个Query对象都包含一个指向Query_base对象的智能指针
};



//Query的输出运算符
ostream& operator<<(ostream& os, const Query& query)
{
    return os << query.rep();
}


//wordQuery及其相关类的实现
class WordQuery : public Query_base
{   
    //无公有成员
    friend class Query; //利用接口来简化代码
    WordQuery(const string& s) : query_word(s){}
    //WordQuery是一个具体的类 因此将定义所有继承而来的纯虚函数
    QueryResult eval(const TextQuery &t)const
    {
        return t.query(query_word);
    }
    string rep() const { return query_word; }
    string query_word;  //要查找的单词
};

inline Query::Query(const string& s) : q(new WordQuery(s)) { }

class NotQuery : public Query_base
{
    friend Query operator~(const Query&);
    NotQuery(const Query& q) :query(q){}

    //具体的类 NotQuery将定义所有继承而来的纯虚函数
    string rep()const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery& t)const;
    
    Query query;
};

inline Query operator~(const Query& operand)
{
    return shared_ptr<Query_base>(new NotQuery(operand));
    //这个return语句隐式的使用接受一个shared_ptr<Query_base>的Query构造函数
}

class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query& l, const Query& r, string s):
        lhs(l),rhs(r),opSym(s){}
    //抽象类，BinaryQuery不定义eval
    string rep() const 
    {
        return "(" + lhs.rep() + " "+ opSym + " " + rhs.rep() + ")";
    }
    //对rep的调用最终是对rhs和lhs所指Query_base对象的rep函数的调用
    Query lhs, rhs;//左侧和右侧运算对象
    string opSym;  //运算符的名字
};

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query&, const Query&);
    
    AndQuery(const Query& left, const Query& right) :
        BinaryQuery(left, right, "&"){ }

    //具体的类 AndQuery继承了rep并且定义了其他纯虚函数
    QueryResult eval(const TextQuery&)const;
};

inline Query operator&(const Query& lhs, const Query& rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
    //return语句负责将shared_ptr转换成Query
}
//这两个类均定义了一个构造函数通过运算符创建BinaryQuery的基类部分
//它们都继承了BinaryQuery的rep函数 但是覆盖了eval函数

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query&, const Query&);

    OrQuery(const Query& left, const Query& right) :
        BinaryQuery(left, right, "|") { }

    //具体的类 AndQuery继承了rep并且定义了其他纯虚函数
    QueryResult eval(const TextQuery&)const;
};

inline Query operator|(const Query& lhs, const Query& rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}


int main()
{
    ifstream file("C:\\Users\Administrator\Desktop\123.docx");
    runQueries(file);
}
*/