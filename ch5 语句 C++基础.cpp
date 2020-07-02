/*

1、switch的内部的控制流
   理解程序在case标签之间的执行流程非常重要，如果某个case标签匹配成功
   就从该标签开始往后顺序执行所有case分支，除非程序显式的中断了这一进程
   否则直到switch的结尾处才会停下来，因此需要在每个case标签后加入break中断

2、传统for语句
   for(initializer;condition;expression)
        statement
   init-statement负责初始化一个值
   condition作为循环控制的条件 
   expression负责修改初始化后的变量
   
   注意点：修改发生在每次循环之后！！！！

   等价于：
   initializer;
   while(condition)
        expression;

3、范围for语句
   for(declaration : expression)
        statement;

   expression:表示的是一个序列：比如用一个花括号括起来的初始值列表、数组、vector或者string对象等
   expression的共同特点：拥有能返回迭代器的begin和end

   declaration:定义一个变量，序列中的每个元素都能转换成该变量的类型 一般使用auto修饰符修饰

4、跳转语句
  (1)break:
   作用：负责终止离它最近的while、do while、switch、for语句
   并从这些语句之后的第一条语句开始继续执行
  (2)continue:
    作用：禁止最近的循环中的当前迭代并立即开始下一次迭代
5、异常处理(exception)
   try
   {
        .....;
        throw error;  抛出异常
   }
   catch(error)
   {
        ....;    进行异常处理
   }
*/

/*

p164 t 5.10

#include<iostream>
#include<string>
using namespace std;
int main()
{
    unsigned int a_cnt = 0, e_cnt = 0, i_cnt = 0, o_cnt = 0, u_cnt = 0;
    char ch;
    while (cin >> ch && ch != '0')
    {
        switch (ch)
        {
        case 'a':
        case 'A':
            a_cnt++;
            break;
        case 'e':
        case 'E':
            e_cnt++;
            break;
        case 'i':
        case 'I':
            i_cnt++;
            break;
        case 'o':
        case 'O':
            o_cnt++;
            break;
        case 'u':
        case 'U':
            u_cnt++;
            break;

        }
    }
    cout << "Number of vowel a(A): \t" << a_cnt << '\n'
        << "Number of vowel e(E): \t" << e_cnt << '\n'
        << "Number of vowel i(I): \t" << i_cnt << '\n'
        << "Number of vowel o(O): \t" << o_cnt << '\n'
        << "Number of vowel u(U): \t" << u_cnt << endl;

    return 0;
}
*/

/*
#include<iostream>
#include<string>
using namespace std;
int main()
{
    pair<string, int>max_count;
    int count = 0;
    for (string str, prestr; cin >> str; prestr = str)
    {
        if (str == prestr)++count;
        else count = 0;
        if (count > max_count.second)max_count = { prestr, count };
    }
    if (max_count.first.empty()) cout << "There's no duplicated string." << endl;
    else cout << "the word " << max_count.first << " occurred " << max_count.second + 1 << " times. " << endl;
    return 0;
}
*/

/*
#include<iostream>
#include<string>
#include<exception>
using namespace std;
int main()
{
    int i, j;
    while (cin >> i >> j)
    {
        cout << "please input two int:" << endl;
        try
        {
            if (j == 0)
                throw runtime_error("division is 0");
            cout << i / j << endl;
        }
        catch(runtime_error err)
        {
            cout << err.what() << "\nTry again? Enter y or n" << endl;
            char c;
            cin >> c;
            if (!cin || c == 'n')
                break;

        }
    }
    return 0;
}
*/