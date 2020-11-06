/*
1、定义模板
    
  函数模板：

  (1)模板类型参数T

     类型模板参数前必须使用关键字class或typename

  template<typename T>
  int compare(const T& v1,const T& v2)
  {
        if(v1 < v2) return -1;
        if(v1 > v2) return 1;
        return 0;
  }
  模板参数T表示在类或函数定义中用到的类型或值，当使用模板时，我们可以
  隐式的或者显式的指定模板实参，将其绑定到模板参数上

  //实例化出int compare(const int&,const int&);
  cout << compare(1,0) << endl;  T隐式推断为int

  //实例化出int compare(const vector<int>&,const vector<int>&);
  vector<int>vec(1,2,3),vec2(4,5,6);
  cout << compare(vec1,vec2) << endl; T隐式推断为vector<int>

  这是编译器生成的两个版本，这两个版本统称为模板的实例

  (2)非类型模板参数

     非类型模板参数表示一个值而不是一个类型
     通过一个特定的类型名而不是关键字class和typename来指定非模板参数

     举例：
     template<unsigned N,unsigned M>
     int compare(const char (&p1)[N],const char (&p2)[M])
     {
            return strcmp(p1,p2);
     }
     调用：compare("hello","world");
     实例化的版本:
       int compare(const char (&p1)[3],const char (&p2)[4])

    扩展：非类型模板参数可以是内置数据类型、或者是一个指向对象或函数类型的指针或引用
          绑定到非类型整型参数的实参必须是一个常量表达式(编译阶段确定结果)

  (3)模板的编译
     当编译器遇到一个模板定义时，它并不生成代码，只有当我们实例化出模板的一个特定版本时
     编译器才会生成代码
     也就是说，当我们使用而不是定义模板时，编译器才会生成代码

     为了实例化出一个版本，编译器需要掌握函数模板或类模板成员函数的定义
     因此，与非模板代码不同，模板的头文件通常包括声明及定义

  类模板：
    
    作用：生成类的蓝图
    与函数模板的不同：编译器不能为类模板推断模板参数类型
    为了使用类模板，必须在模板名后的尖括号中提供额外信息(代替模板参数的模板实参列表)

    定义在类模板之外的成员函数必须以关键字template开始 后接类模板参数列表
    举例：
    template<typename T>
    Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

    规定：当我们处于一个类模板的作用域中时，编译器处理模板自身引用时
          就好像我们已经提供了与模板参数匹配的实参一样

          也就是说，在一个类模板的作用域内，我们可以直接使用模板名而不必指定模板实参

          比如在模板template<typename T>class Blob中
          写 Blob& operator++();
          而不要写 Blob<T>& operator++();
    
  (4)类模板和友元
     
     如果一个类模板包含一个非模板友元，则友元被授权可以访问所有模板实例
     如果友元自身是模板，类可以授权给所有友元模板实例，也可以只授权 给特定实例

     可以使用using 或者 typedef来为模板定义一个类型别名

     template<typename T> using twin = pair<T,T>;
     twin<string>authors;

     友元的设置：

     举例1：一对一友元关系

     template <typename>class BlobPtr;   //均声明为模板
     template <typename>class Blob;
     template <typename T>
     bool operator==(const Blob<T>&,const Blob<T>&);

     template<typename T>
     class Blob
     {
        friend class BlobPtr<T>;
        friend bool operator==<T>(const Blob<T>&,const Blob<T>&);
     }

     举例2：通用友元关系
     template<typename T> class Pal;
     class C
     {
        friend class Pal<C>;  //用类C实例化的Pal是C的一个友元
        template<typename T> friend class Pal2; 
        //Pal2的所有实例都是C的友元，这种情况下无须前置声明
     }
    
  (5)类模板的静态成员

      template<typename T>
      class Foo
      {
        public:
            static std::size_t count(){ return ctr;}
        private:
            static std::size_t ctr;
      }

      template<typename T>
      size_t Foo<T>::ctr = 0; // 模板类的每个static数据成员必须有且仅有一个定义
      //因此要将static数据成员定义为模板

      每个Foo实例都有其自己的static成员实例
      对于任意给定类型X，都有一个Foo<X>X::ctr和一个Foo<X>::count成员
      所有Foo<X>类型的对象共享相同的ctr对象和count函数
      (注意区分类与对象的概念)
  
      Foo<string>fs;
      //实例化static成员Foo<string>::ctr 和Foo<string>::count

      Foo<int>f1,f2,f3;
      //所有三个对象共享相同的Foo<int>::ctr 和Foo<int>::count成员
    
  (6)模板参数
     
     一个模板参数名在一个特定模板参数列表中只能出现一次

     template<typename V,typename V> //错误

     模板声明与定义中的名字不必相同 形式相同即可

     默认情况下，C++语言假定通过作用域运算符访问的名字不是类型（而是数据成员）
     如果希望使用一个模板类型参数的类型成员，就必须显式的告诉编译器该名字是一个类型
     方法：使用typename关键字

     template<typename T>
     typename T::value_type top(const T& c)
     {
            if(!c.empty())
                return c.back();
            else
                return typename T::value_type();
     }
     当我们希望通知编译器一个名字表示类型时，必须使用关键字typename


     默认模板实参问题：（仿函数的应用）

     举例：compare有一个默认模板实参less<T>和一个默认函数实参F()
     template<typename T,typename F = less<T>>
     int compare(const T& v1,const T& v2,F f = F())
     {
        if(f(v1,v2))return -1;
        if(f(v2,v1))return 1;
        return 0;
     }
     在这段例子中，为模板添加了第二个类型参数，名字为F，表示可调用对象
     并定义了一个新的函数参数f，绑定到一个可调用对象上
     (为此模板参数提供了默认实参，并为其对应的函数参数也提供了默认实参)
     
     ->默认模板实参指出compare将使用标准库的less函数对象类
       默认函数实参指出f是类型F的一个默认初始化的对象

     调用：
     bool i = compare(0,42); 返回-1 T = int F = less<int>
     
     Sales_data item1(cin),item2(cin);
     bool j = compare(item1,item2,compareIsbn); //调用自己的比较操作
     compareIsbn的类型是一个可调用对象(函数、函数指针、lambda、重载运算符类) 
     T = Sales_data     F = compareIsbn (执行可调用对象compareIsbn的默认初始化)

     .....................

     template<class T = int> 
     class Number
     {
          ......一系列定义及操作
     }
     Number<double>lots_of_precision;
     Number<>average_precision;    
     空<>表示我们希望使用默认类型


  (7)成员模板
    
     一个类无论是普通类还是类模板，可以包含本身是模板的成员函数
     这种成员被称为成员模板

     举例1：普通类的成员模板--定义一个删除器
     class DebugDelete
     {
        public:
            DebugDelete(ostream& s = cerr):os(s){}

            template<typename T>
            void operator()(T* p)const //T的类型由编译器推断(重载括号运算符的类是可调用对象)
                { os << "deleting unique_ptr " << endl; delete p;}
        private:
            ostream& os;
     }

     调用：double* p = new double;
           DebugDelete d;      //自定义的一个删除器 可像delete表达式一样使用的对象
           d(p);  //调用DebugDelete::operator()(double*) 释放p
           int *ip = new int;
           //在一个临时DebugDelete对象上调用operator()(int*)
           DebugDelete()(ip);

           或者用作unique_ptr的删除器
           unique_ptr<int,DebugDelete>p(new int,DebugDelete()); //DebugDelete()是提供的这种类的实例 是一个默认初始化的对象

    举例2：对于类模板再定义成员模板
           template<typename T>
           class Blob
           {
                template<typename It>
                Blob(It b,It e);
           }

           类外定义此成员：必须同时提供类和函数模板的实参
           template<typename T>
           template<typename It>
           Blob<T>::Blob(It b,It e):data(make_shared<vector<T>(b,e)){}
           
           调用：
           int ia[] = {1,2,3,4,5};
           Blob<int>a(begin(ia),end(ia));
           T = int It = int* 


  (8)利用extern显式控制实例化缩减模板开销

     extern template declaration; 代表一个实例化声明(也就是声明在其他地方，可以有多个extern声明)
     （在这个文件中需要用到哪个实例化就注明extern声明(里面加具体的模板实参 如int等)）
     template declaration;        代表一个实例化的定义（一个模板只能有一个定义）

     //比如
     extern template class Blob<string>; //声明 这个程序中需要用到Blob<string> 但是定义在别处
     template int compare(const int&,const int&); //定义 对一个实例化做出定义(一个实例化对象只能有一个定义)

     核心：编译器遇到extern模板声明时，不会再本文件中生成实例化代码
     只需要链接其他文件的实例模板定义即可 这样可以大大的减少内存开销

     举例：
     文件 Application.cc

     extern template class Blob<string>;
     extern template int compare(const int&,const int&);
     Blob<string>sa1,sa2; //Blob<string>实例化出现在其他位置

     //Blob<int>及其接受initializer_list的构造函数在本文件中实例化
     //原因：因为没有声明extern <int>类型 所以在此实例化
     Blob<int>a1 = {1,2,3,4,5};
     Blob<int>a2(a1); //拷贝构造实例化

     int i = compare(a1[0],a2[0]); //前面有extern声明 所以实例化出现在其他位置

     最终文件Application.cc只包含Blob<int>的实例及其接受initializer_list参数构造函数和拷贝构造函数
     compare<int>函数和Blob<string>类不在本文件实例化，这些模板的定义出现在程序的其他文件中


     文件 templateBuild.cc
     //实例化文件为每个在其他文件中声明为extern的类型和函数提供一个非extern的定义
     template class Blob<string>;
     template int compare(const int&,const int&);

     最终，文件templateBuild.cc将会包含compare<int>的实例和Blob<string>类的定义
     当我们编译此应用程序时，必须将templateBuild.cc和Application.cc连接到一起

     补充：一个类模板的实例化会实例化该模板的所有成员
          也就是说，即使我们不适用某个成员，它也会被实例化
          (所以用来显式实例化的类模板的类型必须能用于模板的所有成员)

2、模板实参推断

   定义：从函数实参来确定函数模板实参的过程

   (1)类型转换与模板类型参数：
   能在调用中应用于函数模板的只有两项，其他转换均不可以应用于函数模板
   1、const转换 
   将一个非const对象的引用或指针实参传递给一个const的引用或指针形参
   2、数组或函数指针转换(非引用类型)
   一个数组实参可以转换为一个指向其首元素的指针，一个函数实参可以转换为一个该函数类型的指针

   举例：
   template<typename T>T fobj(T,T); //值传递形式 实参被拷贝
   template<typename T>T fref(const T&,const T&);//引用传递
   string s1("hello");
   const string s2("slam");
   
   fobj(s1,s2);  //调用fobj(string,string) s2的实参顶层const被忽略
   fref(s1,s2);  //调用fref(const string&,const string&) 将实参s1转换为const类型是允许的 (底层const可以接受非常量对象)

   int a[10],b[42];
   fobj(a,b);    //调用f(int*,int*)
   fref(a,b);    //错误 数组不能传入这样的引用类型

   例如：
   f(int& arr[10]);   错误 不能将arr声明成引用的数组 上述形参是const T&是一个单纯的引用 即错误 
   f(int (&arr)[10]); 正确 arr是具有10个整数的整型数组的引用

   总结：
   将实参传递给带模板类型的函数形参时，能够自动应用的类型转换只有const转换
   以及数据或函数到指针的转换

   (2)函数模板显式实参

    template<typename T1,typename T2,typename T3>
    T1 sum(T2,T3);
    没有任何函数实参的类型可用来推断T1的类型 因此必须提供显式模板实参
    int a;
    double b;
    float c;

    下面两种调用形式均可

    auto val = sum<float>(a,b); //float sum(int,double);
    //此调用显式的指定T1，T2 T3由编译器推断得出
    auto val = sum<float,int,double>(a,b);
    //此调用显式的指定三种模板参数

   (3)尾置返回类型与类型转换
    
      为什么使用尾置返回类型？
      原因：在编译器遇到函数的参数列表之前，无法确定返回的类型 因此必须使用尾置返回类型
            尾置返回类型出现在参数列表之后，可以使用函数的参数
      举例：
      template<typename It>
      auto fcn(It beg,It end）->decltype(*beg)
      {
        //处理代码
        return *beg;  //等价于返回序列中的一个元素的引用
      }
      在上面的程序中，我们利用尾置返回类型通知编译器fcn的实际返回类型与
      解引用beg参数的结果类型相同 而且解引用运算符返回的是一个左值
      因此通过decltype推断的类型为beg表示的元素的类型的引用

      利用标准库模板类进行类型转换
      头文件：type_traits
      利用remove_reference来获得元素类型
      包括：一个模板类型参数和一个名为type的类型成员
      语法：remove_reference<int&> 获得的type成员是int
      举例：remove_reference<decltype(*beg)>::type 获得beg引用的元素的类型
      decltype(*beg)返回元素类型的引用类型  remove_reference::type脱去引用 剩下元素类型本身

      对上面的代码进行处理
      template<typename It>
      auto fcn2(It beg,It  end)->typename remove_reference<decltype(*beg)>::type
      {
            return *beg;  //实际返回的是序列中的一个元素的拷贝
      }
      为什么加typename?
      原因：type是一个类的成员(依赖于一个模板参数)
      因此，与前面提到的相同，必须在返回类型的声明中使用typename关键字来通知编译器 type是一个类型
      (加入typename关键字希望使用一个模板类型参数的类型成员)

      remove_pointer<T*>::type    返回T
      remove_reference<T&>::type  返回T

   (4)函数指针和实参推断

     template<typename T>
     int compare(const T&,const T&); 

     int (*pf1)(const int&,const int&) = compare;  //正确 函数指针pf1指向compare的int版本实例
     void func(int(*)(const string&,const string&);//正确 接受一个T为string的函数指针作为形参
     void func(compare);   //错误 没有指明模板参数类型 不知道使用哪一种实例
     void func(compare<int>); // 正确 传递compare(const int&,const int&)

     关于const在实参推断中的判断：
        
        1、当一个函数参数是模板类型参数的一个普通左值引用时(T&),绑定规则告诉我们，只能传递给它一个左值
        实参可以是const类型，也可以不是
        如果实参是const的，则T将被推断为const类型
        template<typename T>
        void f1(T&);
        f1(i); i是一个int T=int
        f1(ci);ci时一个const int  T = const int
        f1(5); 错误 必须是一个左值 而非右值

        2、当一个函数参数是模板类型参数的一个const引用时(const T&)
        可以传递给它一个const或者一个非const对象、一个临时对象或者一个字面常量值
        但是T的推断结果不会是一个const类型 因为const类型已经是函数参数类型的一部分
        template<typename T>
        void f2(const T&);
        f1(i); i是一个int T=int
        f1(ci);ci时一个const int  T =int
        f1(5); 可以用一个const&绑定到右值 所以T = int

        3、当一个函数参数是右值引用时(T&&) 推断出的T是右值实参
        template<typename T>
        void f3(T&&);
        f3(42);   T = int

        引出的一个问题：如果给一个右值引用形参绑定上的实参是左值会发生什么？
        答案：引用折叠
        方法：C++在正常绑定规则之外定义了特殊的模板绑定规则--引用折叠
        f3(i);  实参是一个左值（也就是变量形式） 模板参数T = int&
        f3(ci); 实参是一个左值 模板参数T是一个const int&

        引用折叠规则(必须是模板类型)：
        如果一个函数参数是一个 指向模板类型参数的右值引用T&&，则它可以被绑定到一个左值
        且如果实参是一个左值 则推断出的模板实参类型将是一个左值引用
        且函数参数将被实例化为一个普通左值引用参数T&
        (也就是说，我们可以将任意类型的实参传递给T&&类型的函数参数)

        使用右值引用的函数模板通常使用之前关于左值与右值引用的方式进行重载
        template<typename T>void f(T&&);     模板可以绑定任意类型 精确匹配绑定到非const左值
        template<typename T>void f(const T&);模板可以绑定任意类型 精确匹配绑定到左值和const右值

   (5)std::move的理解 重点
      
      之前的应用：
      int&& r1 = 42;            正确
      int&& r2 = r1;            错误 不能将一个右值引用绑定到另一个右值引用变量上 因为变量是左值
      int&& r2 = std::move(r1); 正确 显示的将一个传入的左值转换为右值引用类型(获得绑定到一个左值上的右值引用)

      std::move源代码
      template<typename T>
      typename remove_reference<T>::type&& move(T&& t)
      {
          return static_cast<typename remove_reference<T>::type&&>(t);
      }
      string s1("hello"),s2;
      s2 = std::move(string("slam"));
      s2 = std::move(s1);

      在第一个调用s2 = std::move(string("slam"))中 传递给move的实参是string的构造函数的右值结果
      因此推断出的T是string
      remove_reference用string进行实例化
      remove_reference<string>type成员是string
      move的返回类型是string&&
      move的函数参数t的类型是string&&

      调用形成的实例化：string&& move(string&& t);
      这个调用的结果就是它所接受的右值引用

      在第二个调用s2 = std::move(s1)中 传递给move的实参s1是一个左值(变量)
      因此推断出的T的类型是string&(引用折叠机制)
      remove_reference用string&进行实例化
      remove_reference<string&>type成员是string
      move的返回类型是string&&
      move的函数参数t的实例化为string& &&,被折叠为string&

      调用形成的实例化：string&& move(string& t);
      也就是将一个右值引用绑定到了一个左值
      这个实例化的函数体返回static_cast<string&&>(t)
      t的类型是一个string&,cast将其转换为string&&
      (C++可以用static_cast显式的将一个左值转换为一个右值引用)

   (6)模板中的转发机制 重点！

      作用：一些函数需要将其一个或多个实参连同类型不变地转发给其他函数
            在转发的情况下，需要保持被转发实参的所有性质(是否是const/是否是左值右值)

      模板中能保持类型信息的函数参数：指向模板类型参数的右值引用T&&
      template<typename F,typename T1,typename T2>
      void filp2(F f,T1&& t1,T2&& t2)
      {
            f(t2,t1);  //f(T v1,T& v2)
      }
      调用filp2(f,j,42) 传递给参数t1一个左值j 利用引用折叠机制推出T = int& && = int&
      t1被绑定到j上，当filp2调用f时 f中的引用参数v2被绑定到t1 也就是j 当v2改变时同时会改变j

      缺点：调用形如这样的函数file2(g,i,42); //g(T1&& v2,T2& v1)
            传递给g的是filp2中名为t2的参数  (T2&& t2 = 42)
            函数参数与其他任何变量一样都是左值表达式
            但是C++规定不能隐式的将一个左值绑定到一个右值引用上 因此这个程序在右值引用时会发生问题
            (int&& r1 = 42; int&& r2 = r1; 这个是错误的）
      
      改进方法：使用std::forward标准库函数（头文件为utility）
      该方法通过显式的模板来调用 返回显式实参类型的右值引用 forward<T>返回T&&

      template<typename F,typename T1,typename T2>
      void filp(F f,T1&& t1.T2&& t2)
      {
        f(std::forward<T2>(t2),std::forward<T1>(t1);
      }
      如果传递给T1位置的实参是一个右值 那么T1的类型为一个普通非引用类型
      forwarf<T1>会返回T1&&
      如果传递给T1位置的实参是一个左值 那么通过引用折叠 T1本身是一个左值引用类型
      在这个基础上 forward<T1>的返回类型是一个指向左值引用类型的右值引用& &&
      会再次触发引用折叠机制 返回一个左值引用类型

      如果调用filp(g,i,42) 那么i会以int&的类型传递给g 42以int&&的类型传递给g

   (7)模板重载
      
      规则：
      1、如果同样好的函数中只有一个是非模板参数，则选择此函数
      2、如果同样好的函数中没有非模板函数，而且有多个函数模板，且其中一个模板比其他模板更特例化，则选择此模板
      以上两条均不符合，调用会产生歧义

      template<typename T>string debug_rep(const T& t);
      template<typename T>string debug_rep(T* p);

      const string* sp = &s;
      cout << debug_bug(sp) << endl;

      产生两个模板 均可行 但会调用第二个
      debug_rep(const string*&) T = string*
      debug_rep(const string*)  T = const string

      为什么会有这样的规则，并且会调用第二个

      如果没有这个规则的话，将无法对一个const的指针调用该指针版本的debug_rep
      因为模板debug_rep(const T&)本质上来说可以适用于任何类型(包括指针)
      这个模板比debug_rep(T*)更通用，后者只适用于指针类型
      因此选择更特例化的指针版本

      在定义任何函数之前，如果需要用到特定的函数重载版本，记得声明所有需要用到的重载函数版本
      这样就不用担心希望调用的函数的实例化不是你所需要的版本

3、可变参数模板
    
    定义：接受可变数目参数的模板函数或模板类 
          可变数目的参数被称为参数包(包括模板参数包与函数参数包)
          符号表示:...省略号  typename.../class...

          举例：
          template<typename T,typename...Args>         //Args 模板参数包
          void foo(const T& t,const Args&... rest);    //args 函数参数包

          编译器从函数的实参推断模板参数类型
          对于一个可变参数模板，编译器还会推断包中参数的数目
          int i = 0;double d = 3.14;string s = "hello,slam";
          foo(i,s,42,d);   //包中3个参数
          foo(s,42,"h1");  //包中2个参数
          foo(d,s);        //包中1个参数
          foo("hi");       //空包
                                             //42引用折叠
          void foo(const int&,const string&,const int&,const double&)
          void foo(const string&,const int&,const char[3]&);
          void foo(const double&,const string&);
          void foo(const char[3]&);

          size_of...运算符 
          作用：解算包中的元素数量
          sizeof...(Args); 类型参数的数目
          sizeof...(args); 函数参数的数目

          可变参数包与转发结合使用    经典转发案例！！！
          template<typename...Args>
          void StrVec::emplace_back(Args&&...args)
          {
                check_n_alloc();
                alloc.construct(first_free++,std::forward<Args>(args)...);
                //将emplace_back的所有实参转发给另一个名为construct的函数 完成所有实际工作
          }
          此模式生成如下形式的元素
          std::forward<Ti>(ti);
          其中Ti表示模板参数包的第i个元素的类型 ti表示函数参数包中第i个元素

4、模板特例化
   
   定义：特例化版本是模板一个独立的定义 在其中一个或多个模板参数被指定为特定的类型
   前提：原模板的声明必须在作用域中
   语法：template<> 指出要为原模板的所有模板参数提供实参
   本质：一个实例(为原模板的一个特殊实例提供定义)，而不是重载

   举例：
   template<typename T>
   int compare(const T&,const T&);

   template<>int compare(const int&,const int&);


   部分特例化：
   template<typename T>class remove_reference;
   template<typename T>class reomve_reference<T&>;  //部分特例化出左值引用版本
   template<typename T>class reomve_reference<T&&>; //部分特例化出右值引用版本


    */




//StrBlob的模板写法

/*
#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<functional>

using namespace std;

template<typename T>
class Blob
{
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    Blob();
    Blob(initializer_list<T> i1);

    size_type size()const { return data->size(); }
    bool empty()const { return data->empty; }

    void push_back(const T& t) { data->push_back(t); }
    void push_back(T&& t) { data->push_back(std::move(t)); }
    
    void pop_back();

    T& back();
    T& operator[](size_type i);
    
private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string& msg)const;
};

template<typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

template<typename T>
void Blob<T>::check(size_type i, const string& msg)const
{
    if (i >= data->size())
        throw out_of_range(msg);
}

template<typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template<typename T>
Blob<T>::Blob(initializer_list<T> i1):
    data(make_shared<vector<T>>(i1)){}

int main()
{
    Blob<string> articles = { "a","b","cc" };
    int num = articles.size();
    cout << num << endl;
    cout << articles[2] << endl;
    return 0;
}

*/

/*

//重点：自己构建的智能指针shared_ptr

#include<iostream>
#include<string>
#include<functional>

template<typename T>class SharedPointer;

struct Delete     //自定义的删除器
{
    template<typename T>
    auto operator()(T* p)const
    {
        delete p;
    }
};

template<typename T>
auto swap(SharedPointer<T>& lhs,SharedPointer<T>& rhs)
{
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.ref_count, rhs.ref_count);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T>
class SharedPointer
{
    friend auto swap<T>(SharedPointer<T>&, SharedPointer<T>&); //友元的声明关系
public:
    SharedPointer():
        ptr(nullptr),ref_count(new std::size_t(1)),deleter(Delete()){}
    //Delete()是一个默认初始化的可调用对象 传入泛化的模板中deleter
    explicit SharedPointer(T* raw_ptr): //利用非智能指针进行构造
        ptr(raw_ptr),ref_count(new std::size_t(1)),deleter(Delete()){}

    SharedPointer(const SharedPointer& other):
        ptr(other.ptr),ref_count(other.ref_count),deleter(other.deleter)
    {
        ++* ref_count; //先初始拷贝构造 再加1 相当于ref_count两者共同指向的size_t（也就是引用次数+1）
    }
    SharedPointer(SharedPointer&& other)noexcept:  //noexcept保证不抛出异常
        ptr(other.ptr),ref_count(other.ref_count),deleter(std::move(other.deleter))
    {
        other.ptr = nullptr; //处理掉移动后的源对象
        other.ref_count = nullptr;
        //只有deleter删除器是真正的移动了 其他两个指针还是拷贝 无效率问题 只要处理将其置空即可
    }

    SharedPointer& operator=(const SharedPointer& rhs) //拷贝赋值运算符重载
    {
        ++* rhs.ref_count;
        decrement_and_destroy(); //如果自己是最后一个指针 就执行析构
        ptr = rhs.ptr, ref_count = rhs.ref_count, deleter = rhs.deleter;
        return *this;
    }
    SharedPointer& operator=(SharedPointer&& rhs) noexcept  //移动赋值运算符重载
    {
        ::swap(*this,rhs);
        rhs.decrement_and_destroy();
        return *this;
    }
    auto swap(SharedPointer& rhs)
    {
        ::swap(*this, rhs);
    }

    T& operator*()const
    {
        return *ptr;
    }
    T* operator->()const
    {
        return &*ptr;
    }
    auto use_count()const
    {
        return *ref_count;
    }
    auto get()const
    {
        return ptr;
    }
    auto unique()const
    {
        return 1 == *ref_count;
    }


    //下面是重置
    auto reset()
    {
        decrement_and_destroy();
    }
    auto reset(T* pointer)
    {
        decrement_and_destroy();
        ptr = pointer;
        ref_count = new std::size_t(1);
    }
    auto reset(T* pointer, const std::function<void(T*)>& d) //传入一个删除器
    {
        reset(pointer);
        deleter = d; //相当于重构删除器
    }
    ~SharedPointer()
    {
        decrement_and_destroy();
    }

private:
    T* ptr;
    std::size_t* ref_count;
    std::function<void(T*)>deleter; //类模版std::function是一种通用、多态的函数封装。std::function的实例可以对任何可以调用的目标实体进行存储、复制、和调用操作，这些目标实体包括普通函数、Lambda表达式、函数指针、以及其它函数对象等
    //C++11中推出std::function是为了泛化函数对象，函数指针，引用函数，成员函数的指针

    auto decrement_and_destroy() //执行最后一个引用指针的销毁工作
    {
        if (ptr && 0 == -- * ref_count)
        {
            delete ref_count;
            delete ptr;
        }
        else if (!ptr)
            delete ref_count;
        ref_count = nullptr;
        ptr = nullptr;
    }
};

int main()
{
    auto foo = SharedPointer<int>{ new int(42) };
    auto bar(foo);
    auto boo = SharedPointer<int>{ new int(40) };
    boo.swap(foo);
    std::cout << *foo << std::endl;
    std::cout << foo.use_count() << std::endl;

    auto string_ptr = SharedPointer<std::string>{ new std::string{ "Yue" } };
    std::cout << *string_ptr << std::endl;
    std::cout << string_ptr->size() << std::endl;

    return 0;
}

*/


//构建智能指针unique_ptr

/*

#include<iostream>
#include<string>
#include<functional>

template<typename T,typename D>class unique_pointer;
template<typename T,typename D>
void swap(unique_pointer<T, D>& lhs, unique_pointer<T, D>& rhs);
struct DebugDelete     //自定义的删除器
{
    template<typename T>
    auto operator()(T* p)const
    {
        delete p;
    }
};

template<typename T,typename D = DebugDelete>
class unique_pointer
{
    friend void swap<T, D>(unique_pointer<T, D>& lhs, unique_pointer<T, D>& rhs);

public:
    unique_pointer(const unique_pointer&) = delete; //删除拷贝构造
    unique_pointer& operator=(const unique_pointer&) = delete; //删除拷贝赋值运算符

    unique_pointer() = default;
    explicit unique_pointer(T* up):ptr(up){}//接受非智能指针的有参构造

    //移动操作
    unique_pointer(unique_pointer&& up)noexcept
        :ptr(up.ptr) {up.ptr = nullptr;} //实际上采用的是指针简易移动方式 拷贝 然后析构
    unique_pointer& operator=(unique_pointer&& rhs)noexcept;

    unique_pointer& operator=(std::nullptr_t n)noexcept;


    //下接运算符重载等常规操作
    T& operator*()const { return *ptr; }
    T* operator->()const { return &this->operator*(); }
    T* get()const { return ptr; }
    void swap(unique_pointer<T, D>& rhs)
    {
        ::swap(*this, rhs);
    }
    void reset() noexcept
    {
        deleter(ptr);
        ptr = nullptr;
    }
    void reset(T* p)noexcept
    {
        deleter(ptr);
        ptr = p;
    }
    T* release();
    ~unique_pointer()
    {
        deleter(ptr); //利用删除器删除
    }
private:
    T* ptr = nullptr;
    D deleter = D();  //默认参数D可调用对象的默认默认初始化 D代表传入的实参是可调用对象
};


template<typename T,typename D>
inline void swap(unique_pointer<T, D>& lhs, unique_pointer<T, D>& rhs)
{
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T, typename D>
inline unique_pointer<T,D>&
unique_pointer<T, D>::operator=(unique_pointer&& rhs)noexcept
{
    if (this->ptr != rhs.ptr)
    {
        deleter(ptr);
        ptr = nullptr;
        ::swap(*this, rhs);
    }
    return *this;
}

template<typename T, typename D>
inline T*
unique_pointer<T, D>::release()
{
    T* ret = ptr;
    ptr = nullptr;
    return ret;
}

int main()
{
    unique_pointer<int>p(new int(42));
    unique_pointer<int>p2(new int(40));
    p.swap(p2);
    std::cout << *p << std::endl;
    return 0;
}

*/
