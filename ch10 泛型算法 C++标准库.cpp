/*
1、泛型算法：本身不会执行容器上的操作，它们只会运行在迭代器之上，执行迭代器的操作 
             也就是说，算法永远不会改变底层容器的大小

2、向算法传递的函数---谓词
   
   谓词：一个可调用的表达式，其返回结果是一个能用作条件的值 （返回可以转换为bool类型的值的函数）
   包括一元谓词(接受单一参数)和二元谓词(接受两个参数)
   接受谓词参数的算法一般都有_if前缀
   举例：
   bool predicate(const string& s)
   {
    return s.size() >= 5;

   }
   int main()
   {
    vector<string>ss{ "aaaaaa","bbbbbb","cccc","ddd","e" };
    auto pivot = partition(ss.begin(), ss.end(), predicate);
    for (auto iter = ss.begin(); iter != pivot; iter++)
        cout << *iter << endl;
    return 0;
   }
   predicate就是一个一元谓词

   写到额外目的空间的算法都在名字后面附加一个_copy

3、lambda表达式   重点
   
   基本概念：一个lambda表达式表示一个可调用的代码单元，可以将其理解为一个未命名的内联函数

         auto f = []{reutrn 42;};      
         这个例子中，我们定义了一个可调用对象f，它不接受参数，返回42
         cout << f() << endl;  打印42
         lambda的调用方式与普通函数的调用方式相同 都是使用调用运算符
         （     调用运算符：()    ） 使用()来调用一个函数

   语法：[捕获列表](参数列表)->返回类型{函数体};
         捕获列表：lambda所在函数中定义的局部变量的列表
         一个lambda表达式只有在其捕获列表中捕获一个它所在函数的局部变量，才能在函数体中使用该变量
         其他与函数函数一样，不同的是lambda必须使用尾置类型返回
   
   一个lambda表达式必须要有的元素：捕获列表和函数体  其他可以忽略不写

   lambda不存在默认参数 且如果lambda的函数体包含任何单一return语句之外的内容，且未指定返回类型。则返回void

   举例：sort(words.begin(),words.end(),
              [](const string& a,const string& b)
              { retutn a.size() < b.size();});
   当sort需要比较两个元素时，就会调用这个lambda表达式

   举例：
   vector<string>words = {"aa","bb","ccc"};   
   int sz = 2;    
   auto wc = find_if(words.begin(),words.end(),
   [sz](const string &a){return a.size() > sz;});   
   cout << *wc << endl;

   注意：捕获列表只用于局部非static变量，lambda可以直接使用局部static变量
   和它在所在函数之外声明的名字

   关于lambda的捕获与返回：
   当定义一个lambda时，编译器生成一个与lambda对应的新的未命名的类类型
   (auto f = []{return 42;}相当于给这个未命名的可调用对象加上名字，因此也可以理解为一个未命名的内联函数)

   当向一个函数传递一个lambda时，同时定义了一个新类型和该类型的一个对象
   默认情况下，从lambda生成的类都包含一个对应这个lambda所捕获的变量的数据成员

   两种捕获方式：值捕获与引用捕获
   (1)值捕获：变量在lambda创建时拷贝，而不是调用时拷贝
      由于被捕获的变量是在lambda创建时拷贝，因此随后对其修改不会影响到lambda内对应的值
      举例：
      void fcn1()
      {
         size_t v1 = 42;
         auto f = [v1]{return v1;};
         v1 = 0;
         auto j = f();    j等于42 f保存了我们创建它时v1的拷贝
      }
   (2)引用捕获：当我们在lambda函数体内使用此变量时，实际上使用的是引用所绑定的对象
      举例：
      void fcn2()
      {
         size_t v1 = 42;
         auto f2 = [&v1]{return v1;};
         v1 = 0;
         auto j = f2();    j等于0 f2保存v1的引用 而不是拷贝
      }
      注意：当以引用方式捕获一个变量时，必须保证在lambda执行时变量时存在的

   (3)隐式捕获： [&]采用捕获引用方式 [=]采用值捕获方式
      当我们混合使用隐式捕获和显式捕获时，捕获列表的第一个元素必须是&或者=
      此符号指定了默认捕获方式为引用或值
      
      [names] 默认情况下，捕获列表中的变量都是被拷贝，名字前如果使用了&，则采用引用捕获方式
      [&] 隐式捕获列表 采用引用捕获方式
      [=] 隐式捕获列表 采用值捕获方式
      [&,identifier_list] 任何隐式捕获的变量都采用引用方式捕获 identifier_list采用值捕获 
      [=,identifier_list] 任何隐式捕获的变量都采用值方式捕获 identifier_list采用引用捕获
      

   (4)可变Lambda
      默认情况下，对于一个值被拷贝的变量，lambda不会改变这个值 如果要改变，就在参数列表首加上关键字mutable
      一个引用捕获的变量是否可以修改依赖于此引用指向的是一个const类型还是一个非const类型
     
4、标准库bind函数
     实质：函数适配器 
     作用：接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表
     包含头文件:functional
     包含声明：using namespace std::placeholders
     调用形式：auto newCallable = bind(callable,arg_list);
     当我们调用newCallable时，newCallable会调用callable,并传递给callable arg_list的参数

     arg_list 按从左至右排序，为其在callable形参中的位置
     不同的是，这些参数中可能包含_n的名字，也就是占位符
     (占位符_n表示 newCallable的参数，
     他们占据了newCalable的参数位置，并传递给callable)
     _1 newCallable的第一个参数传递到callable这个位置上来
     _2 newCallable的第二个参数传递到callable这个位置上来
     
     举例：
     (1)
     auto check6 = bind(check_size,_1,6);
     含义：check6只接受一个参数(_1) 这个参数传递到check_size的_1所在的位置上（也就是从左至右数的第一个形参）
     调用check6(s) 就等价于调用check_size(s,6);
     (2)
     auto g = bind(f,a,b,_2,c,_1);
     调用g(_1,_2) 等价于调用f(a,b,_2,c,_1);
     将g的第一个参数传入f的第五个参数位置 将g的第二个参数传递f的第三个形参位置
     f的第一个形参与a绑定 第二个形参与b绑定 第四个形参与c绑定 
     换句话说
     调用g(X,Y)    等价于调用f(a,b,Y,c,X);
     

     问题：如何绑定引用的参数？
     (默认情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中)
     答案：对该参数使用ref 即ref(s) 来返回s的引用

     举例：
     ostream& print(ostream& os,const string& s,char c)
     {
        return os << s << c;
     }
     for_each(words.begin(),words.end(),bind(print,ref(os),_1,""));
     */   



/*

p344 t10.9
包含函数尾置类型推断与模板 底层const的应用

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

template<typename Sequence>
auto print(Sequence const& seq) -> ostream&
{
    for (auto const& elem : seq)
        cout << elem << " ";
    return cout << endl;
}

auto eliminate_duplicates(vector<string>& vs) -> vector<string>&
{
    sort(vs.begin(), vs.end());
    print(vs);
    auto new_end = unique(vs.begin(), vs.end());
    print(vs);

    vs.erase(new_end, vs.end());
    return vs;
}

int main()
{
    vector<string>vs{ "a", "v", "a", "s", "v", "a", "a" };
    print(vs);
    print(eliminate_duplicates(vs));
    return 0;
}

*/


/*

p345 t10.12

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
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
    Sales_data(const string& s) : bookNo(s) {}
    Sales_data(istream& is) { read(is, *this); }

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


inline bool comapareIsbn(const Sales_data& sd1, const Sales_data& sd2)
{
    return sd1.isbn().size() < sd2.isbn().size();
}

int main()
{
    Sales_data d1("aa"), d2("aaaa"), d3("aaa"), d4("z"), d5("aaaaz");
    vector<Sales_data> v{ d1, d2, d3, d4, d5 };

    // @note   the elements the iterators pointing to
    //         must match the parameters of the predicate.
    sort(v.begin(), v.end(), comapareIsbn);

    for (const auto& element : v)
        cout << element.isbn() << " ";
    cout << endl;

    return 0;
}

*/

/*

p345 t10.13

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

bool predicate(const string& s)
{
    return s.size() >= 5;
        
}
int main()
{
    vector<string>ss{ "aaaaaa","bbbbbb","cccc","ddd","e" };
    auto pivot = partition(ss.begin(), ss.end(), predicate);
    for (auto iter = ss.begin(); iter != pivot; iter++)
        cout << *iter << endl;
    return 0;
}
*/


/*

p349 完整程序 t10.16

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

void elimDups(vector<std::string>&s)
{
    sort(s.begin(), s.end());
    auto new_end = unique(s.begin(), s.end());
    s.erase(new_end, s.end());

}

void biggies(vector<std::string>& words, vector<std::string>::size_type sz)
{
    elimDups(words); //排列元素 消除重复的单词
    stable_sort(words.begin(), words.end(),
        [](const std::string& a, const std::string& b)
        {return a.size() < b.size(); });
    //按长度排序，长度相同的单词维持字典序

    auto wc = find_if(words.begin(), words.end(),
        [sz](const std::string& a) {return a.size() >= sz; });
    //获取一个迭代器，指向第一个满足size() >= sz的元素

    auto count = words.end() - wc; //计算满足条件的元素的个数
    
    for_each(wc, words.end(), [](const std::string& s)
        {std::cout << s << " "; });
    std::cout << std::endl;
}
int main()
{ 
    vector<std::string>v = { "1234","1234","1234","hi~", "alan", "alan", "cp" }; 
    biggies(v, 3);  
    std::cout << std::endl;  
    return 0; 
}

*/