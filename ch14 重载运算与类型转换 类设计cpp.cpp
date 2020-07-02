/*
1、基本概念
   如果一个运算符函数是成员函数，则它的第一个左侧运算符对象绑定到隐式的this指针上
   因此，成员运算符函数的显式参数数量比运算符的运算对象总数少一个

   举例：
   data1 += data2;
   data1.operator+=(data2);
   这两条语句都调用了成员函数operator+=,将this绑定到data1的地址、将data2作为实参传入了函数

2、重载输入和输出运算符
    IO流无拷贝，只能使用引用
    通常情况下，第一个形参时一个非常量ostream对象的引用
    (原因：向流写入或者写出会改变其状态，而该形参是引用是因为我们无法直接复制一个ostream对象)
    
    返回类型：返回IO流的引用

    输入输出重载运算符必须是非成员函数！！！

3、赋值运算符与下标运算符
   
   规则：1、都必须定义为成员函数
         2、如果一个类包含下标运算符，则它通常定义两个版本
            一个返回普通引用、另一个是类的常量成员并且返回常量引用

   举例：
   StrVec& StrVec::operator=(initializer_list<string>i1)
   {
        auto data = alloc_n_copy(i1.begin(),i1.end());
        free();
        elements = data.first;
        first_free = cap = data.second;
        return *this;
   }

   class StrVec
   {
     public:
        string& operator[](size_t n)
            {return elements[n];}
        const string& operator[](size_t n)const
            {return elements[n];}
     private:
        string* elements;
   }

4、前置和后置运算符
    重载前置运算符返回的类型是一个引用
    重载后置运算符返回的类型是一个值 
    这与前面所讲的前置以及后置的左值与右值返回类型是一致的

    重载时，区分前置和后置的区别：
    规定后置运算符接受一个额外的不被使用的int类型的形参
    前置运算符无限制
    
    p.operator++(0);  调用后置版本的重载
    p.operator++();   调用前置版本的重载

5、成员访问运算符
    
    class StrBlobPtr
    {
      public:
        string& operator*()const
        {
            auto p = check(curr,"dereference past end");
            return (*p)[curr]; //*p是对象所指的vector
        }
        string* operator()->const
        {
            //将实际工作委托给解引用运算符
            return &this->operator*();//实际返回的是vector某元素的地址
        }
        重载的箭头运算符必须返回类的指针或者自定义了箭头运算符的某个类的对象
    }
6、函数调用运算符

    (1)举例：struct absInt
    {
        int operator(int val)const
        {return val < 0 ? -val : val;}
    }
    我们使用调用运算符的方式是令一个absInt对象作用于一个实参列表
    这一过程看起来非常像调用函数的过程
    int i = 42;
    absInt absObj;      //含有函数调用运算符的对象
    int u = absObj(i);  //将i传递给absObj.operator()

    即使absObj只是一个对象而非函数，我们也能"调用"该对象
    调用对象实际上是在运行重载的调用运算符，
    这个被调用的对象称为函数对象(对象的行为像函数一样)
    
    函数调用运算符必须是成员函数

   (2)含有状态的函数对象类
     
     举例：
     class PrintString
     {
      public:
        PrintString(ostream& o = cout,char c = ''):
            os(o),sep(c){}
        void operator()(const string& s)const{os << s << sep;}
      private:
        ostream& os; //用于写入的目的流
        char sep;    //用于将不同输出隔开的字符
     }

     PrintString printer;            使用默认值 打印到cout
     printer(s);                     在cout中打印s，后面跟一个空格
     PrintString errors(cerr,'\n');
     errors(s);                      在cerr中打印s，后面跟一个换行符
  
   (3)lambda表达式是一个函数对象
     
     对于编译器来说，会将lambda表达式翻译成一个未命名类的未命名对象
     在lambda表达式产生的类中含有一个重载的函数调用运算符

     举例：下面二者是等价的

     stable_sort(words.begin(),words.end(),
     [](const string& a,const string& b)
     {return a.size() < b.size();});

     class ShorterString
     {
      public:
        bool operator()(const string& s1,const string& s2)const
        {return s1.size() < s2.size();};
     }
     stable_sort(words.begin(),words.end(),ShorterString());
    
     举例：表示lambda及相应捕获行为的类
           通过引用捕获--编译器可以直接使用该引用而无需在Lambda产生的类中将其存储为数据成员
           通过值捕获 -- 这种Lambda产生的类必须为每个值捕获的变量建立对应的数据成员，同时创建构造函数，令其使用捕获变量的值来初始化数据成员
     
     下面二者是等价的
     auto wc = find_if(words.begin(),words.end(),
               [sz](const string& a)
               {return a.size() >= sz;});
    
    class SizeComp
    {
        SizeComp(size_t n) : sz(n){} //该形参对应捕获的变量
        //下面调用运算符的返回类型、形参和函数体都与lambda一致
        bool operator()(const string& s)const
        {return s.size() >= sz;}

      private:
        size_t sz;   //该数据成员对应通过值捕获的变量      
    }
    auto wc = find_if(words.begin(),words.end(),SizeComp(sz));
  
   (4)可调用对象与function

      C++中的可调用对象：五类
        函数
        函数指针
        lambda表达式
        bind创建的对象
        重载了函数调用运算符的类

      问题：如何使不同类型的可调用对象共享同一种的调用形式？

      例如

      int add(int i,int j){ return i + j;};      //普通函数
      
      auto mod = [](int i,int j){ return i % j;};//lambda产生的一个未命名的函数对象类

      struct divide                              //函数对象类
      {
        int operator()(int denominatior,int divisor)
        { return denominator / divisor;}
      }

      上面这三种可调用对象分别对其参数执行了不同的算术运算
      尽管它们的类型各不相同，但是共享同一种调用形式
      int(int,int)

      如何共享？一种思路是定义一个函数表用于存储指向这些可调用对象的指针

      需要的标准库支持操作：function

      function<T>f;  f是一个用来存储可调用对象的空function，这些可调用对象的调用形式应该与函数类型T相同
                     注意这里的T是result_type(args) 函数形式
     
      f(args);       调用f中的对象，参数是args

      function是一个模板
      例如 function<int(int,int)> 声明一个function类型，它可以接受两个int、返回一个int的可调用对象

      function<int(int,int)> f1 = add;    函数指针                 
      function<int(int,int)> f2 = divide();   函数对象类的对象
      function<int(int,int)> f3 = [](int i,int j){return i * j;}; lambda

      cout << f1(4,2) << endl;  打印6
      cout << f2(4,2) << endl;  打印2
      cout << f3(4,2) << endl;  打印8

      使用这个function类型可以定义一个函数表map
      map<string,function<int(int,int)>>binops;

      进行添加操作

      map<string,function<int(int,int)>>binops = 
      {
        {"+",add},                            函数指针
        {"-",std::minus<int>()},              标准库函数对象
        {"/",divide()},                       用户定义的函数对象
        {"*",[](int i,int j){ return i * j;}},未命名的lambda
        {"%",mod}                             命令了的lambda对象
      };

      调用这个函数表map

      binops["+"](10,5);   使用add(10,5)
      binops["-"](10,5);   调用minus<int>对象的调用运算符
      binops["/"](10,5);   调用divide对象的调用运算符
      binops["*"](10,5);   调用lambda对象
      binops["%"](10,5);   调用lambda对象

      问题：如何解决重载函数与function之间存在的冲突
      答案：多使用lambda对象或者函数指针来解决

      例如
      int add(int i,int j){ return i + j;}   函数add
      Sales_data add(const Sales_data&,const Sales_data&); 类add
      map<string,function<int(int,int)>>binops;
      binops.insert({"+",add });   //错误 存在二义性冲突

      int (*fp)(int,int) = add;
      binops.insert({"+",fp});  正确 fp指向一个正确的函数add版本

7、重载、类型转换与运算符


   (1)类型转换运算符
       
       作用：将一个类类型的值转换成其他类型
       语法: operator type()const;  type表示要转换的类型

       举例：
       class SmallInt
       {
        public:
            SmallInt(int i = 0) : val(i)
            {
                if(i < 0 || i > 255)
                    throw std::out_of_range("Bad value");
            }
            operator int() const { return val;} //返回类型与type要一致
        private:
            std::size_t val;
       }
        
       SmallInt s;
       s = 4; 首先调用构造函数将4隐式的转换为SmallInt
       s + 3; 将SmallInt转换为int 然后执行整数的加法


       与显式构造函数限制一样
       在类型转换运算符前面加入explicit关键字，防止发生隐式类类型转换

       改为：explicit operator int() const {return val;}
       
       s = 4; 首先调用构造函数将4隐式的转换为SmallInt
       s + 3; 发生错误 此处需要隐式的类型转换 但是类的运算符是显式的
       static_cast<int>(s) + 3;  正确 显式的请求类型转换
  
  */



/*
#include<iostream>
#include<string>
using namespace std;

class Sales_data
{
    friend istream& operator>>(istream&, Sales_data&);
    friend ostream& operator<<(ostream&, const Sales_data&);
    friend Sales_data operator+(const Sales_data&, const Sales_data&);
    friend bool operator==(const Sales_data&, const Sales_data&);
    friend bool operator!=(const Sales_data&, const Sales_data&);

public:
    Sales_data(const string& s,unsigned n,double p):
        bookNo(s),units_sold(n),revenue(p){}
    Sales_data() : Sales_data(" ",0,0.0f){}//委托构造函数
    Sales_data(const string& s) : Sales_data(s,0,0.0f){}//委托构造函数
    Sales_data(istream& is);

    Sales_data& operator+=(const Sales_data&);
    string isbn()const { return bookNo; }
private:
    inline double avg_price()const;
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

istream& operator>>(istream&, Sales_data&);
ostream& operator<<(ostream&, const Sales_data&);
Sales_data operator+(const Sales_data&, const Sales_data&);
bool operator==(const Sales_data&, const Sales_data&);
bool operator!=(const Sales_data&, const Sales_data&);

inline double Sales_data::avg_price()const
{
    return units_sold ? revenue / units_sold : 0;
}

Sales_data::Sales_data(istream& is) : Sales_data() //还是委托构造函数
{
    is >> *this;
}
Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs)
{
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}


Sales_data& Sales_data::operator+=(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream& operator>>(istream& is, Sales_data& item)
{
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)
        item.revenue = price * item.units_sold;
    else
        item = Sales_data();
    return is; //IO流只能进行引用 没有拷贝
}

ostream& operator<<(ostream& os, const Sales_data& item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

bool operator==(const Sales_data& lhs, const Sales_data& rhs)
{
    return lhs.isbn() == rhs.isbn() && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data& lhs, const Sales_data& rhs)
{
    return !(lhs == rhs);
}
int main()
{
    Sales_data s("111", 2, 5.0);
    Sales_data s2("111", 2, 5.0);
    int isequal = (s == s2);
    cout << s << endl;
    cout << isequal << endl;
    return 0;
}


*/

/*

//p509 t14,39


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

struct IsInRange
{
    IsInRange(std::size_t lower, std::size_t upper)
        :_lower(lower), _upper(upper)
    { }

    bool operator()(std::string const& str) const
    {
        return str.size() >= _lower && str.size() <= _upper;
    }

    std::size_t lower_limit() const
    {
        return _lower;
    }

    std::size_t upper_limit() const
    {
        return _upper;
    }
private:
    std::size_t _lower;
    std::size_t _upper;
};

int main()
{
    //create predicates with various upper limits.
    std::size_t lower = 1;
    auto uppers = { 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u };
    std::vector<IsInRange> predicates;
    for (auto upper : uppers)
        predicates.push_back(IsInRange(lower, upper));

    //create count_table to store counts 
    std::map<std::size_t, std::size_t> count_table;
    for (auto upper : uppers)
        count_table[upper] = 0;

    //read file and count
    std::ifstream fin("../data/storyDataFile.txt");
    for (std::string word; fin >> word;)
        for (auto is_size_in_range : predicates)
            if (is_size_in_range(word))
                ++count_table[is_size_in_range.upper_limit()];

    //print
    for (auto pair : count_table)
        std::cout << "count in range [1, " << pair.first << "] : " << pair.second << std::endl;

    return 0;
}


*/