/*

1、函数的返回类型不能是数组或者函数类型，但是可以是指向数组或者函数的指针

2、局部对象与局部静态对象
   局部对象：形参和函数体内部定义的变量，仅在函数体的内部可见，同时可以覆盖外作用域的同名变量
   当函数执行完毕后被销毁
   局部静态对象：函数内部通过static修饰的变量 在程序的执行路径第一次经过对象语句时对其初始化，
   并且直到整个程序终止才会被销毁，在此期间即时该对象所在的函数结束执行也不会对它有影响。

3、C++中，建议使用引用类型的形参代替指针
   当函数无须修改引用参数的值时最好使用常量引用
   一个函数只能返回一个值，然而有时候函数需要返回多个值，引用形参为我们返回多个值提供了一个有效途径

4、函数中的顶层const(作用于本身的const)                              ！！！！！
   引入：当执行对象的拷贝工作时，常量是顶层const还是底层const是区别明显的
   int i = 0;
   int* const p1 = &i;   顶层const 
   const int ci = 42;
   const int* p2 = &ci;  底层const
   const int* const p3 = p2; 顶层const在拷贝中可以忽略 但是拷贝的双方必须具有相同的底层const资格
   const int& r = ci;    底层const
   
   在拷贝中，顶层const不会受到影响 但是底层const会受到限制(可以使用一个非常量对象来初始化一个底层const对象，但是反过来不行 因为底层const不能被忽略)
   i = ci; 正确 拷贝ci的值 ci是一个顶层const  但是对此操作无影响
   p2 = p3;正确 p2和p3都是指向常量的指针 具有相同的底层const资格 p3的顶层const部分在拷贝中可以忽略
   int* p = p3; 错误 p3是一个底层const但是p不是
   

   
   当用实参初始化形参时会忽略顶层const,换句话说，形参的顶层const被忽略掉了，
   当形参有顶层const时，传递给它常量或者非常量对象都是可以的

   函数的重载不能忽略顶层const 一个拥有顶层const的形参无法和另一个没有顶层const的形参区分开来
   但是函数的重载可以区分底层const

   可以使用一个非常量对象来初始化一个底层const对象，但是反过来不行 因为底层const不能被忽略
   int i = 42;
   const int* p = &i; 正确 但是p不能改变i
   const int& r = i;  正确 但是r不能改变i

   const int i = 42;
   int* p = &i 错误 底层const不可以被忽略

   int& r = i  错误 底层const不可以被忽略

   建议：尽量使用常量引用 
   举例：如果函数的形参是int*，传入的实参是const int*，就会发生错误 （底层const不可忽略）
         如果函数的形参是const int*，传入的实参是int*,是可以的，因为可以使用一个非常量对象来初始化一个底层const对象
   因此，使用引用而非常量引用会极大的限制函数所能接受的实参类型
   
   补充：p208
   利用const int* /const int&的形参可以接受常量以及非常量对象 
   利用int* / int&的形参只可以接受非常量对象

5、数组形参

   概述：数组的两个特殊性质对我们定义和使用在数组上作用的函数有影响
   (1)不允许拷贝数组                            无法以值传递的方式来使用数组参数
   (2)数组使用时通常会被拷贝为指针              为函数传入一个数组时，实际上传入的是指向数组首元素的指针

   int arr[10] = {1,2,3,4,5,6,7,8,9,10};
   
   print(const int*);
   print(const int[]);                            这四个函数是等价的  实际上传入的都是const int*  
   print(const int[10]);
   print(arr);    arr转换成const int*并指向arr[0]
   
   ！如果我们传给print函数的参数是一个数组，则实参会自动的转换成指向数组首元素的指针

   数组的大小对数组的调用是没有影响的

   以下是几种传入不同形参类型的print函数的定义方式
    void print(const char* cp)
    {
        if (cp)
        while (*cp)
            cout << *cp++;
    }
    void print(const int* begin, const int* end)
    {
        while (begin != end)
            cout << *begin++ << endl;
    }
    print(begin(arr), end(arr));

    void print(const int arr[], size_t len)
    {
        for (size_t i = 0; i != len; i++)
            cout << arr[i] << endl;
    }
    void print(const int(&arr)[10])
    {
        for(auto elem : arr)
            cout << elem << endl;
    }

6、main 处理命令行选项
   main(int agrc,char* *argv)
   第一个形参表示数组中字符串（实际上是命令行字符串）的数量
   第二个形参argv实质上是一个数组的首元素的指针
   (argv是指向数组首元素的指针 解引用*argv得到该首元素char* 
   因为该首元素是一个指针元素 再次解引用会得到指向的存储值char,也就是输入的命令行字符串)
   
   argv这个指向数组首元素的指针编译器理解为数组名字（保存的数组元素为char*指针）
   argv[1]、argv[2]等即是数组的第二个、第三个char*元素
   且char *c = "hello";可以直接表示命令行字符串

   当使用argv的实参时，记得可选的实参从argv[1]开始 argv[0]保存程序的名字、而不是用户的输入

7、函数的可变形参initializer_list   ！！！

   应用场景：如果函数的实参数量未知但是全部实参的类型都相同
   initializer_list 标准库类型，用于表示某种特定类型的值的数组
   应用：initializer_list<T> il;
   特点：initializer_list对象中的元素永远是常量值 不可以被改变

   如果想向initializer_list形参中传递一个值的序列，则必须把序列放入一对花括号中
   
   举例：
   void error_msg(initializer_list<string>i1)
   {
        for(auto begin = i1.begin();begin != i1.end();i1++)
            cout << *begin++ << endl;
   }
   //expected和actual都是string对象
   error_msg({"functionX","expected","actual"});

8、return语句
   (1)return;
   return expression; 返回表达式的值    这个实际中比较常用

   (2)规则：不要返回局部对象的引用（因为函数结束后局部对象会被销毁）

   (3)问题：返回的是否是左值？
      答案：调用一个返回引用的函数会返回左值，其余的都返回右值

   (4)C++11的新规定：函数可以返回一个花括号包围的值的列表 即使这个是一个空列表（代表返回一个空对象）

   (5)函数返回数组的指针:
   1、利用类型别名来返回一个指向数组的指针
      typedef int arrT[10]   /  using arrT = int[10];
      arrT* func(int i);   返回一个arrT*指针 指向数组别名arrT
   
   2、复杂形式 Type(*function(parameter_list))[dimension]
      Type表示元素的类型 dimension表示数组的大小
      举例：int(*func(int i))[10]
   
   3、使用尾置返回类型           ！！！(用来简化函数返回指针或者引用的写法)

      尾置返回类型跟在形参列表的后面并以一个->开头 
      为了表示函数真正的返回类型跟在形参列表的后面，在本应该放返回类型的地方放入一个auto
      auto func(int i) -> int(*)[10];   表示函数返回的是一个指针 指针指向大小为10的int数组

   4、使用decltype
      decltype并不负责把数组转化成指针，其返回的结果是一个数组，要想表示返回的是指针还必须在函数声明时加一个*符号

9、特殊用途语言特性
   
   (1)默认形参：
      当设计含有任意实参的函数时，其中一项任务是合理设置形参的顺序，尽量让
      不怎么使用默认值的形参出现在前面，而让那些经常使用默认值的形参出现在后面
   
   (2)内联函数inline:可以避免函数调用的开销
      一般用于优化规模较小、流程直接、频繁调用的函数

   (3)定义constexpr函数：能用于常量表达式的函数
      函数的返回类型及所有形参的类型都必须是字面值类型
      
      constexpr int new_sz(){return 42;}
      constexpr int foo = new_sz();  new_sz()返回的是一个常量表达式 因此可以被赋值 
   
   (4)assert预处理宏
      assert(expression);
      对expression求值，如果表达式为假，assert输出信息并停止程序执行 如果为真，则什么也不做

    __FILE__ 存放文件名的字符串数组值
    __LINE__ 存放当前行号的整型字面值
    __TIME__ 存放文件编译时间的字符串字面值
    __DATE__ 存放文件编译日期的字符串字面值

10、函数指针
    (1)
    函数指针指向的是函数而不是对象
    bool lengthCompare(const string& ,const string&);
    
    要想声明一个指向函数的指针，只需要用指针替换函数名即可
    bool (*pf)(const string& ,const string&);

    (2)如何使用函数指针？
    pf = lengthCompare;   
    重点：当我们把函数名作为一个值使用时，该函数自动的转换为指针
    bool b1 = pf("hello","slam");
                                           二者是等价的
    pf = &lengthCompare;
    bool b1 = (*pf)("hello","slam");

    (3)如何重载函数指针？
    void ff(int*);
    void ff(unsigned int);

    void (*pf)(unsigned int) = ff;   pf指向ff(unsigned int)

    (4)如何将函数作为形参使用？

    直接将函数作为实参使用即可，此时它会自动的转换为指针
    IsBigger(s1,s2,lengthCompare);

    (5)如何返回指向函数的指针

       最简单办法：用类型别名
       using pf = int(*)(int,int); pf是指针类型
       pf ff(int,int)； pf是指向函数的指针 ff返回指向函数的指针

       其他方法：（可忽略）
       int (*ff(int,int))(int,int);
       auto ff(int,int)->int(*)(int,int);
       decltype(ff)* ff(int,int);
   */

/*

p190

#include<iostream>
#include<string>
using namespace std;
string::size_type find_char(const string& s, char c, string::size_type& occurs)
{
    occurs = 0;
    auto ret = s.size();
    for (decltype(ret) i = 0; i != s.size(); ++i)
    {
        if (c == s[i])
        {
            if (ret == s.size())
                ret = i;
            ++occurs;
        }
    }
    return ret;
}
int main()
{   
    string::size_type ctr;
    auto result = find_char("hello,world", 'o', ctr);
    cout << result << endl;
    cout << ctr << endl;
    return 0;
}
*/

/*

p192

#include<iostream>
#include<string>
using namespace std;

void fcn(const int& r)
{   
    cout << r << endl;
}
int main()
{
    int i = 42;
    fcn(i);
    return 0;
}
*/

/*

p196 t6.22 交换指针的值

#include<iostream>
#include<string>
using namespace std;

void swap(int*& lhs, int*& rhs)
{
    auto temp = lhs;
    lhs = rhs;
    rhs = temp;
}
int main()
{
    int i = 10;
    int j = 20;
    int* lft = &i;
    int* rft = &j;
    swap(lft, rft);
    cout << *lft << " " << *rft << endl;
    return 0;
}
*/

/*

p199 t 6.27

#include<iostream>
#include<string>
using namespace std;

int printsum(initializer_list<int>i1)
{
    int sum = 0;
    for (auto& m : i1)
    {
        sum += m;
    }
    return sum;
}
int main()
{
    int result = printsum({ 1,2,3,4,5,6,7,8,9 });
    cout << result << endl;
    return 0;
}
*/

