/*
1、定义在类内部的函数是隐式的inline函数
   编译器对类的编译顺序：首先编译成员的声明，直到类全部可见
   然后再编译成员函数体（因此成员函数体可以随意的使用类的成员而不用关心出现的顺序）
   即编译器处理完类的全部声明之后才会处理成员函数的定义

   类的声明：class ClassName; 前向声明 指明ClassName是一种类类型（无定义之前是一种不完全类型）
   一旦一个类的名字出现之后，它就被认为是声明过了

   因此类中可以包含自身的引用或者是指针，但是不能包含自己  ！！！

   可以向常量引用参数传入一个临时量
   理解：如果一个参量是以一个非const形式引入，那么编译器就会认为程序员会在函数中修改这个值，
         但是因为临时变量的特殊性，程序员并不能操作临时变量，而且这个临时变量可能随时都会被释放掉，
         所以一般来说修改临时变量是无意义的，因此C++编译器规定只能使用常量引用来传递临时变量
   
2、this
   (1)
   任何对类成员的直接访问都被看作是this的隐式调用
   this的目的总是指向这个对象，所以this是一个常量指针（顶层const 本身是一个常量）
   我们不被允许可以改变this中保存的地址
   
   (2)
   默认情况下，this是指向类类型非常量版本的常量指针 也就是 *const（顶层const，非底层const) 
   由举例： const double i = 42;
			double* p = &i;   错误 底层const不可以被忽略
   可知，不能用一个this指针来指向对象的常量版本（因为底层const不可以被忽略）

   这一情况也就意味着我们不能在一个常量版本上调用对象本身的成员函数
   
   ->最好的处理办法就是在this的前面加上const关键字改为指向常量的常量指针从而与常量对象相匹配（同时也可以匹配非常量对象）
   
   C++的做法：将const关键字放在成员函数的参数列表之后。（此时，紧跟在参数列表后面的const表示this是一个指向常量的指针）
              像这样使用const的成员函数叫做常量成员函数（常量成员函数不能改变调用它的对象的内容）
    
    经典案例：p248 const成员函数和非const成员函数的重载 (利用底层const书写函数重载) 
   （成员函数后加const意味着const*this指针(顶层const)转变为 const * const this指针(也就是变成了底层+顶层const) 包含底层const 形成重载
    其中，常量成员重载函数可以匹配常量以及非常量对象  普通重载成员函数只可以匹配非常量对象
    如果是常量对象的调用函数，调用的就是常量成员重载函数(唯一匹配),如果是非常量对象，调用的就是普通成员重载函数(精确匹配)

   一个const成员函数（常量成员函数）如果以引用的形式返回*this,那么它的返回类型也必须是常量引用const& （因为底层const不可以被忽略)！！！
   
   常量函数中的可变数据成员：如果要想修改常量成员函数里面的特定的数据值，可以通过在函数声明中在该变量前面加mutable关键字来实现

   返回引用的函数是左值的，其余返回的均为右值

3、IO类不可以被拷贝 返回类型只能是IO流引用
   并且，因为读取和输入操作会改变流的内容，所以两个函数接受的都是普通引用，而非对常量的引用

4、构造函数
   
   (1)Sales_data(const std::string& s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(p*n) {}
      构造函数初始值列表：负责为新创建的对象的数据成员赋值 上面为其语法形式
    
    合成的默认构造函数:ClassName() = default;
    
   (2)构造函数初始化：区分初始化列表和赋值操作
        如果成员是const或者引用的话，必须使用初始化列表来进行初始化
        建议：推荐使用初始化列表而不是赋值操作(当然这种做法效率也更高)
        (成员的初始化顺序与他们在类中定义的顺序是一致的)

   (3)委托构造函数(delegating constructor)
      
      作用：可以使用它所属的类的其他构造函数执行它自己的初始化过程（也就是把自己的职责委托给了其他构造函数）

      举例：
      class Sales_data
      {
         public:
            //非委托构造函数使用对应的实参初始化成员
            Sales_data(const std::string& s, unsigned cnt, double price)
            : bookNo(s), units_sold(cnt), revenue(price*cnt) {}
            //其余构造函数全部委托给另一个构造函数
            
            Sales_data() : Sales_data(" ",0,0){}
            //定义的默认构造函数使用三参数的构造函数完成初始化的过程

            Sales_data(istream& is) : Sales_data(){ read(is,*this);}
            //该接受istream&的构造函数也是委托构造函数，它委托给了默认构造函数，
            默认构造函数又接着委托给了三参数构造函数
            当这些受委托的构造函数执行完后，接着执行istream&构造函数体的内容
            (假如受委托的构造函数有函数体的话，就先执行它，再执行委托者的函数体)
      }

   (4)构造函数explicit关键字：C++中的explicit关键字只能用于修饰只有一个参数
     （或只有一个参数，其他均为默认参数）的类构造函数,它的作用是表明该构造函数是显示的,而非隐式的
      从而禁止发生隐式转换
      且当我们用explicit关键字声明构造函数时，只能以直接初始化的形式使用，不能使用拷贝初始化
      
   (5)constexpr构造函数：一般为空 必须初始化所有数据成员(初始化或者使用constexpr构造函数，或者是一条常量表达式)

   5、访问控制和封装
   
   (1):定义在public说明符之后的成员在整个程序内可被访问
       public成员定义类的接口

       定义在private说明符之后的成员可以被类的成员函数访问，
       private部分封装了类的实现细节

   (2):利用友元friend可以使类外的函数访问类内的私有成员数据
        
        类做友元：声明一个友元类 该友元类的成员函数可以访问这个类的私有成员

        A类的成员函数F做友元：只有A的成员函数可以访问这个类B的私有成员
        做法：首先定义A类，其中声明F函数，但是不能定义它 在F使用B的成员之前必须先声明B
              接下来定义B 包括对于F的友元声明
              最后定义F 此时它才可以使用B的成员
        
        重载函数做友元：需要对每一个函数进行分别声明

        友元在类中的声明不是真的在该作用域中的声明，必须在类外声明，才可调用

   (3)作用域：
      :: 代表全局作用域
      ClassName:: 代表类作用域
      内层的作用域可以重新定义外层作用域中的名字，在找名字时，从内层作用域依次向外层作用域查找

      建议：类型名的定义放在类的开始处，确保所有使用该类型的成员都出现在类名的定义之后

      成员定义之前的普通作用域的名字查找(p255)
      1、首先，在成员函数内查找该名字的声明（只有在函数使用之前出现的声明才会被考虑）
      2、如果在成员函数内部没有找到，则在类内继续查找 这时候类的所有成员都可以被考虑
      3、如果类内也没有找到该名字的声明，则在成员函数定义之前的作用域进行名字查找

6、类的静态成员
   
   举例：class Account
   {
      public:
        void calculate(){amount += amount * interestRate;}
        static double rate(){return interestRate;}
        static void rate(double);
      private:
        string owner;
        double amount;
        static double interestRate;
        static double initRate();
        
        //每个Account对象实际上只包含两个数据成员：owner 和 amount
        //只存在一个interestRate对象而且它被所有Account对象共享

        //静态成员一般被理解为一个对象 而不是单纯的数据
    }
    类的静态成员(static关键字标注)存在于任何实例对象之外，对象中不包含任何与静态成员有关的数据
    而且，静态成员函数不与任何对象绑定到一起，不包含this指针，同时静态成员函数不能被声明为const

    要想访问静态成员一般使用作用域运算符直接访问  当然也可以使用this指针访问 （但是静态成员函数本身不能使用this指针）
    double r;
    r = Account::rate();
                                  二者是等价的
    Account ac1;
    r = ac1.rate();

    定义并初始化一个静态成员举例
    double Account::interestRate = initRate();   
    定义了名为interestRate的对象，该对象是Account类的静态成员，其类型是double
    (从类名开始，这条定义语句的剩余部分就位于类的作用域类内了，因此可以直接调用initRate()函数)
    

    问题：如何定义静态成员？
    答案：在类的外部定义静态成员时，不再使用static关键字，该关键字只出现在类内的声明语句中
          一般在类的外部定义和初始化静态成员 （而不是在类内靠构造函数初始化 这是错误的 因为静态成员不属于类本身）
          (static constexpr静态成员可以在类内定义)
    总结：静态成员数据定义在任何函数之外，一旦被定义，就一直存在于程序的整个生命周期中

    特殊应用：
    静态数据成员可以是它所属的类的类型，而非静态成员则受到限制，只能声明成它所属类的指针或者引用
    静态数据成员可以作为默认实参，非静态不可以（因为非静态数据成员是类的一部分，而静态是独立的）

7、聚合类
    只含有公有成员的类，并且没有类内初始值或者构造函数
    聚合类的成员一般使用花括号括起来的初始值列表进行初始化
    可以理解为一个简单的struct
    
    
    */


/*

Sales_data 1.0版本

#include<iostream>
#include<string>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

struct Sales_data
{	
	//对象的操作
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price()const;
	
	//数据成员
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

double  Sales_data::avg_price()const
{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}
Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream& read(istream& is, Sales_data& item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream& print(ostream& os, Sales_data& item)
{
    os  << item.isbn() << " "
        << item.units_sold << " "
        << item.revenue << " "
        << item.avg_price();
    return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

int main()
{
    Sales_data total;
    if (read(cin, total))
    {
        Sales_data trans;
 
        while (read(cin,trans))
        {   
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(cout, trans);
                total = trans;
            }
            
        }
        print(cout, total);
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;
}
*/

/*

Sales_data 2.0版本

#include<iostream>
#include<string>
struct Sales_data
{
    Sales_data() = default;
    Sales_data(const std::string& s) : bookNo(s){}
    Sales_data(const std::string& s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(p*n) {};
    Sales_data(std::istream& s) { return read(is, *this); }
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price()const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// nonmember functions
std::istream& read(std::istream& is, Sales_data& item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue;
    return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

*/


/*

Sales_data 3.0版本 友元类

#include<iostream>
#include<string>
using namespace std;

class Sales_data
{
    friend Sales_data add(const Sales_data& lhs, const Sales_data& rhs);
    friend istream& read(istream& is, Sales_data& item);
    friend ostream& print(ostream& os, const Sales_data& item);
public:
    Sales_data() = default;
    Sales_data(const string& s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(p* n) {}
    Sales_data(const string& s) : bookNo(s){}
    Sales_data(istream& is) {  read(is, *this); }
    
    string isbn()const { return this->bookNo; }
    Sales_data& combine(const Sales_data&);

private:
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
Sales_data add(const Sales_data& lhs, const Sales_data& rhs);
istream& read(istream& is, Sales_data& item);
ostream& print(ostream& os, const Sales_data& item);

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// friend functions
istream& read(istream& is, Sales_data& item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream& print(ostream& os, const Sales_data& item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue;
    return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

*/