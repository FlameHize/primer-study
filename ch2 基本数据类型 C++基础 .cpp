/*
1、 int& r = i &紧随类型名出现，因此是类型的一部分，r是一个引用
	r = & i    &出现在表达式中，因此是一个取地址符

2、extern前缀 
   用于进行变量的声明（只声明而不进行定义）
   一个文件如果想使用别处定义的名字则必须包含对那个名字的声明
   变量能且只能被定义一次，但是可以被多次声明

3、void*指针   
   void*是一种特殊的指针类型，可以用于存放任意类型对象的地址

4、引用本身不是一个对象，因此不能定义一个指向引用的指针，但是指针是对象，所以可以定义一个指针的引用
					int* p = i;
					int* &r = p;
   要理解r的类型到底是什么，需要从右向左阅读r的定义，离变量名最近的符号对变量的类型具有最直接的影响！！！！
   所以r是一个引用，声明符的其他部分用于说明r的引用类型是什么，所以*说明r引用的是一个指针

5、如何只在一个文件中定义const变量，而在其他多个文件中声明并使用它？
   解决办法：对于const变量不管是声明还是定义都添加extern关键字 这样只需要定义一次就可以了
   extern：指明变量并非本文件独有，这只是一个声明，它的定义将在别处出现
   如果想在多个文件之间共享const对象，则必须在变量的定义之前添加extern关键字

6、const
   
   （1）对const的引用 简称为常量引用

   （2）允许将const的引用绑定到非const类型的上面 反之则不行
   
   （3）指向常量的指针：底层const 不能用于改变其所指对象的值（仅仅要求不能通过该指针改变对象的值，而没有规定那个对象的值不能通过其他路径改变）
        常量指针：      顶层const 指针本身为常量 （顶层const可以表示任意的对象是常量）
       （遵循的规则：从右向左阅读）

   （4）执行拷贝操作并不会改变被拷贝对象的值，因此，拷入和拷出的对象是否是常量是没有影响的（顶层const无影响）
        但是，底层const的限制不能忽视，当执行对象的拷贝操作时，拷入和拷出的对象必须具有相同的底层const资格

    具体练习题：p58 题2.30 2.31
        
7、constexpr常量表达式

    定义：常量表达式是指值不会改变并且在编译过程中就能得到结果的表达式
    应用：如果认为变量是一个常量表达式，就将其生命为constexpr类型
    C++11中，将变量声明为constexpr类型以便由编译器来验证变量的值是否是一个常量表达式
    声明为constexpr的变量一定是一个常量 而且必须用常量表达式来初始化
    constexpr int mf = 20; 常量表达式
    constexpr int limit = mf + 1;常量表达式
    constexpr int sz = size(); 只有当size()是一个constexpr函数时才是一条正确的声明语句
    C++11允许定义一种特殊的constexpr函数，这种函数足够简单从而使得编译过程中就可以得到计算结果
    这样就可以使用constexpr函数来初始化constexpr变量了
    
    引入问题：什么才算是足够简单的函数 ---应该是只有字面值类型的函数
    字面值类型：指针、引用、算术类型   自定义的类型不属于字面值类型

    constexpr修饰的指针仅对指针有效，与指针所指向的对象无关(将修饰对象置为顶层const)
    举例：    const int* p = nullptr;      p是一个指向整型常量的指针
              constexpr int* q = nullptr;  q是一个指向整数的常量指针

              constexpr const int* p = &i; p是常量指针 指向整型常量i
              constexpr int* q = &j;       q是常量指针 指向整数j
8、指针 常量 类型别名
              typedef char *pstring;
              const pstring cstr = 0;  cstr是指向const的常量指针
              const pstring *ps;       ps是一个指针，它的对象是指向char的常量指针

              重点：要理解这个地方的基本数据类型是const pstring  const是对给定类型的修饰
              pstring实际上是指向char的指针 
              所以 const pstring是指向const的常量指针，而不是指向const常量的指针
9、auto 自动类型推断
    一般会忽略顶层const 恢复顶层const的话需要将修饰类型改为const auto

10、decltype类型指示符
    作用：选择并返回操作数的数据类型（在此过程中，编译器分析表达式并获得它的类型，却不计算实际表达式的值）
    举例：decltype(f()) sum  = x; sum的类型就是函数f的返回类型

    特点：1、保留顶层const和引用类型
          
          2、如果表达式的类型是解引用操作，则decltype将得到引用类型
             decltype(*p)返回的类型是int& 而不是int
          3、decltype(variable))(注意是双层括号)返回的结果永远是引用，而decltype(variable)的结果
             只有当variable本身就是一个引用时才返回一个引用类型
11、预处理器 
    作用：确保头文件多次包含但是仍然可以安全工作
    #ifndef SALES_DATA_H
    #define SALES_DATA_H
    .......
    #endif

    */

//Sales_data初始定义

#include<iostream>
#include<string>
using namespace std;

struct Sales_data
{
    string bookNo;
    unsigned unit_solds = 0;
    double revenue = 0.0;
};

int main()
{
    Sales_data total;
    double totalPrice;
    if (cin >> total.bookNo >> total.unit_solds >> totalPrice)
    {
        total.revenue = total.unit_solds * totalPrice;

        Sales_data trans;
        double transPrice;
        while (cin >> trans.bookNo >> trans.unit_solds >> transPrice)
        {
            trans.revenue = trans.unit_solds * transPrice;

            if (total.bookNo == trans.bookNo)
            {
                total.unit_solds += trans.unit_solds;
                total.revenue += trans.revenue;
            }
            else
            {
                cout << total.bookNo << " " << total.unit_solds << " " << total.revenue << " ";
                if (total.unit_solds != 0)
                    cout << total.revenue / total.unit_solds << endl;
                else
                    cout << " no sales" << endl;

                total.bookNo = trans.bookNo;
                total.unit_solds = trans.unit_solds;
                total.revenue = trans.revenue;
            }
        }
        cout << total.bookNo << " " << total.unit_solds << " " << total.revenue << " ";
        if (total.unit_solds != 0)
            cout << total.revenue / total.unit_solds << endl;
        else
            cout << " no sales" << endl;
        return 0;
    }
    else
    {
        cerr << "no data" << endl;
        return -1;
   
    }
}


