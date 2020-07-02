/*

1、异常处理
   
   (1)抛出异常
     throw (类似于return 之后的语句不再执行) 将控制权转交给与之匹配的catch块
     会导致发生的情况：
     1、沿着调用链的函数可能会提前退出
     2、一旦程序开始执行异常处理代码，则沿着调用链创建的对象将被销毁

     发生过程：栈展开
     如果对抛出异常的函数的调用语句位于一个try语句块内，则检查与该try块关联的catch语句
     如果找到了匹配的catch，就使用该catch处理异常 否则 如果该try语句嵌套在其他try块中
     则继续检查与外层try匹配的catch语句 如果仍然没有找到匹配的catch，则退出当前这个主调函数
     继续在调用了刚刚退出的这个函数的其他函数中查找 以此类推
     (假设找到了一个匹配的catch语句，则程序就进入该语句并执行其中的代码 当执行完这个catch语句后
     找到与try块关联的最后一个catch块之后的点 并从这里继续执行
     如果一直没有找到，则退出主函数后查找过程终止--一个异常如果没有被捕获 则它将终止当前的程序)

     栈展开过程中位于调用链上的语句块可能会提前退出，对象被自动的销毁
     如何保证在这个过程中资源被正确的释放？
     使用类来控制资源的分配，类对象分配的资源将由类的析构函数负责释放
     这样能确保无论函数正常结束还是遭遇异常，资源都能被正确的释放

     当我们throw出一条表达式时，该表达式的静态编译类型决定了异常对象的类型
     如果一条throw表达式解引用一个基类指针 而该指针实际指向的是一个派生类对象
     则抛出的对象将被切掉一部分 只有基类部分被抛出

   (2)捕获异常
      
     捕获类型：值类型或左值引用类型（最好设置为左值引用）
     异常类型的静态类型将决定catch语句所能执行的操作
     例外：捕获基类的引用时，对what函数的调用将执行与异常对象动态类型对应的版本


     如果在多个catch语句的类型之间存在着继承关系，则应该把最底层的派生类放在最前面
     把最顶端的基类放在最后面

     重新抛出：
     存在的原因：一个单独的catch语句不能完整地处理某个异常，在执行了某些校正操作之后
                 当前的catch可能会决定由调用链更上一层的函数接着处理异常 因此需要重新抛出
     语法：throw;（单独一句，不包含任何表达式）
     一个重新抛出语句并不指定新的表达式，而是将当前的异常对象沿着调用链向上传递

     如何捕获所有异常？
     方法：catch(...)
     缺点：出现在捕获所有异常语句后面的catch语句将永远不会被匹配

     如何处理构造函数抛出的异常(比如初始化列表)？
     方法：将构造函数写成try语句块
     try语句块既能处理构造函数体和析构函数体，也能处理构造函数的初始化过程以及析构函数的析构过程

     举例：
     template<typename T>
     Blob<T>::Blob(initializer_list<T>i1) try : 
     data(make_shared<vector<T>>(i1){}
     catch(const bad_alloc& e){ handle_out_of_memory(e);}
     注意try出现的位置
     与这个try关联的catch既能处理构造函数体抛出的异常
     也能处理成员初始化列表抛出的异常
     (将构造函数写成try语句块也是处理构造函数初始值异常的唯一方法)


   (3)noexcept异常说明
      
      对于一个函数来说，noexcept说明要么出现在该函数的所有声明以及定义语句中，要么一次也不出现

      noexcept运算符:
      noexcept说明符接受一个可选的实参，该实参必须能转换为bool类型
      如果实参是true,则函数不会抛出异常 如果实参是false，则函数可能抛出异常
       
   (4)异常说明与虚函数机制
     
        如果一个虚函数承诺了它不会抛出异常，则后续派生出来的虚函数也必须做出同样的承诺
        反之，如果基类的虚函数允许抛出异常，则派生类的对应函数既可以抛出异常也可以不抛出异常

        //自定义的两个异常类
        class out_of_stock : public std::runtime_error
        {
        public:
            explicit out_of_stock(const std::string& s):
            std::runtime_error(s){}
        };

        class isbn_mismatch : public std::logic_error
        {
        public:
            explicit isbn_mismatch(const std::string& s):
                std::logic_error(s){}
            isbn_mismatch(const std::string& s,const std::string& lhs,const std::string& rhs)
                :std::logic_error(s),left(lhs),right(rhs){}
            const std::string left, right;
        };

        Sales_data&
        Sales_data::operator+=(const Sales_data& rhs)
        {
            if(isbn() != rhs.isbn())
                throw isbn_mismatch("wrong isbns",isbn(),rhs.isbn());
            units_sold += rhs.units_sold;
            revenue += rhs.revenue;
            return *this;
        }

        Sales_data item1,item2,sum;
        while(cin >> item1 >> item2)
        {
            try
            {
                sum = item1 + item2;
            }
            catch(const isbn_mismatch& e)
            {
                cerr << e.what() << " left isbn " << e.left << "right isbn" << e.right << endl;
            }   //e.what()执行与动态类型相对应的版本
        }

2、命名空间
    
    分割全局命名空间，其中每个命名空间是一个作用域，通过在某个命名空间中定义库的名字、作者以及用户可以避免全局命名名字带来的限制
    命名空间同样可以嵌套存在
    namespace mycpp
    {

    }最后不带分号 这是与类定义不同的地方
    
    命名空间可以是不连续的，例如上文的mycpp 
    如果之前没有名为mycpp的命名空间定义 则上述代码将创建一个新的命名空间
    否则，上述代码打开已经存在的命名空间定义并为其添加一些新成员的声明

    命名空间的组织方式类似于我们管理自定义类及函数的方式：
    1、命名空间的一部分成员的作用是定义类、以及声明作为类接口的函数及对象
    这些成员应该置于头文件中(这些头文件将会被包含在使用了这些成员的文件中)
    2、命名空间成员的定义部分则置于另外的源文件中

    举例：
    //在Sales_data.h文件中添加命名空间mycpp
    #include<string>  #include包含应该出现在打开命名空间的操作之前
    namespace mycpp
    {
        class Sales_data
        {
            //类成员数据以及成员函数的声明
        };
        Sales_data operator+(const Sales_data&,const Sales_data&);
        //Sales_data的其他接口函数的声明
    }

    //在Sales_data.cc文件中添加命名空间mycpp
    #include"Sales_data.h"
    namespace mycpp
    {
        //Sals_data成员以及其重载运算符、接口函数的定义
    }

    //用户的使用程序user.cc
    #include"Sales_data,h" //用户如果想使用自定义的库 必须包含必要的头文件
    int main()
    {
        using mycpp::Sales_data; //在用户程序中使用命名空间来获取需要的库
        Sales_data item1,item2;
        .....
        return 0;
    }

    这种程序的组织方式提供了开发者和库用户所需的模块性
    一个类的用户不需要编译与其他类相关的名字(只需要编译该头文件中自定义的库namespace即可)
    因此，库的开发者可以分别实现每一个类，相互之间没有干扰

    命名空间之外定义的成员必须使用含有前缀的名字
    mycpp::Sales_data
    mycpp::operator+(const Sales_data& lhs,const Sales_data& rhs)
    {
        Sales_data ret(lhs);
        //...
    }
    ！！！重点
    和定义在类外部的类成员相同，一旦看到含有完整前缀的名字
    我们就可以确定该名字位于命名空间的作用域内(后续遇到相同的名字就不用再加前缀了)
    在上述代码中，我们就可以直接使用Sale_data来定义函数的形参而无需添加前缀

    模板的特例化必须定义在原始模板所属的命名空间中
    举例：
    namespace std
    {
        template<> struct hash<Sales_data>; 必须将模板特例化声明成std的成员
    }


    内联命名空间：
    在关键字namespace前添加关键字inline
    作用：内联命名空间中的名字可以被外层命名空间直接使用
    也就是说，无需在内联命名空间的名字前面添加该命名空间的前缀，通过外层命名空间的名字就可以直接访问它
    关键字inline必须在命名空间第一次定义的地方，后面可写可不写

    举例：
    inline namespace Fifthprimer
    {
        class Query_base{} //primer第五版的代码
    }
    namespace Forthprimer
    {
        class Query_base{} //primer第四版的代码
    }

    namespace c++primer
    {
        #include "Fifthprimer,h"
        #include "Forthprimer.h"
    }
    c++primer::Query_base;  
    访问得到的是第五版的成员类
    如果想访问第四版的 需要这样写c++primer::Forthprimer::Query_base

    如何在文件中使用静态声明，使得变量对于整个文件都有效?
    方法：使用未命名的命名空间(定义在未命名的命名空间中的名字可以直接使用)


    使用命名空间成员

    (1)命名空间的别名
       
       namespace cplusplus_primer{}
       namespace primer = cplusplus_primer;   使用别名换成一个更易于表示的命名空间

    (2)using声明
      
       一条using声明语句一次只引入命名空间的一个成员
       它的有效范围从using声明的地方开始，一直到using声明所在的作用域结束(在此过程中，外层作用域的同名实体将被隐藏)
       (未加限定的名字只能在using声明所在的作用域以及其内层作用域中使用，在有效作用域结束后，我们必须使用完整的经过限定的名字才行)
       using std::swap;
       using声明语句声明的是一个名字，而不是一个特定的函数，这一点需要记住
       当我们为函数书写using声明时，该函数的所有版本都被引入到当前的作用域中

    (3)using指示
       
       一条using指示语句使得某个特定的命名空间中所有的名字都可见
       using namespace 关键字名字
       作用范围：从using指示开始，一直到using指示所在的作用域结束都能使用
       举例：
       namespace blip
       {
            int i = 16,j = 15, k = 23;
       }
       int j  = 0; //正确 blip的j隐藏在命名空间中
       void manip()
       {
            using namespace blip;   //manip可以直接访问blip的所有名字
            ++i;       //将blip::i设定为17
            ++j;       //二义性错误
            ++::j;     //正确 将全局的j设为
            ++blip::j; //正确 将blip::j设定为16
            int k = 97;//当前局部的k隐藏了blip::k  作用域不同
            ++k;       //将当前局部的k设定为98 
       }

       using指示中的重载
       namespace AW
       {
            int print(int);
       }
       namespace Primer
       {
            double print(double);
       }
       using namespace AW;
       using namespace Primer;
       string print(string);
       int main()
       {
            print(1);   //调用AW::print(int)
            print(3.1); //调用Primer::print(double)
            print("hi");//调用::print(string)
       }
       尽管它们的声明位于不同作用域中，但它们都属于main函数中print调用的候选函数集

    (4)使用限制
        
       头文件如果在其顶层作用域中含有using指示或using声明，则会将名字注入到所有包含了该头文件的文件中
       通常情况下，头文件应该只负责定义接口部分的名字，而不定义实现部分的名字
       因此，头文件最多只能在它的函数或命名空间内使用using指示或using声明
       相比于使用using指示，在程序中对命名空间的每个成员分别使用using声明效果更好，这样可以减少注入到命名空间中的名字数量

    (5)与作用域的关系
       
       名字查找规则：由内向外依次查找每个外层作用域，直到最外层的全局命名空间查找过程终止
                     向上查找 名字必须先声明才能使用 有编译先后顺序的区别
       举例：
       namespace A
       {
            int i;
            int k;
            
            class C1
            {
             public:
                C1():i(0),k(0){}
                int f1(){ return k;} //返回A::k
                int f2(){ return h;} //错误 h还未定义
                int f3();
             private:
                int i;   //在C1中隐藏了A::i
                int j;   
            }
            int h = i;  //用A::i进行初始化
            
       }
       int A::C1::f3(){ return h;} //正确 用A::i进行初始化

3、多重继承与虚继承
    
    (1)多重继承
        class Bear : public ZooAnimal{}
        class Panda : public Bear,public Endangered{}

        构造一个派生类的对象将同时构造并初始化它的所有基类子对象
        与从一个基类进行派生一样，多重继承的派生类的构造函数初始值也只能初始化它的直接基类
        Panda::Panda(string name,bool onExhibit)
        :Bear(name,onExhibit,"Panda"),Endangered(Endangered::critical){}
        
        派生类的构造函数初始值列表将实参分别传递给每个直接基类，其中基类的构造顺序与派生列表中基类的出现顺序保持一致

        构造顺序：ZooAnimal Bear Endangered Panda
        析构顺序：反过来

    (2)虚继承
        
       令某个类做出生命，承诺愿意共享它的基类，其中共享的基类子对象称为虚基类
       在这种机制下，不论虚基类在继承体系中出现了多少次，在派生类都只包含唯一一个共享的虚基类子对象

       class Raccoon : public virtual ZooAnimal{}
       class Bear : public virtual ZooAnimal{}
       class Panda : public Bear,public Raccoon,public Endangered{}
       //在Panda中只有一个ZooAnimal的基类部分

       与原体系不同，派生类对象的构造函数还必须负责初始化它的虚基类（即使这个虚基类不是直接基类）
       Panda::Panda(string name,bool onExhibit)
       :ZooAnimal(name,onExihibit,"Panda"),
        Bear(name,onExihibit),
        Raccoon(name,onExihibit),
        Endangered(Endangered::critical),
        sleeping_flag(false){}

        顺序：首先使用提供给最底层派生类构造函数的初始值初始化该对象的虚基类子部分
              接下来按照直接基类在派生列表中出现的次序依次对其进行初始化
              (虚基类总是先于非虚基类构造 与它们在继承体系中的次序和位置无关)
*/


