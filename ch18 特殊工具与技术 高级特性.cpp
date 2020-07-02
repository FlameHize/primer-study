/*

1、定位new表达式

   new (place_address) type(initializers)
   作用：在指定的地址分配以及构造对象

   place_address 指针(在这个地址上进行内存分配与构造)
   ininitalizers 初始值列表(用于构造新分配的对象)

   一条new表达式的执行过程总是先调用operator new函数以获取内存空间 然后在得到的内存空间中构造对象
   与之相反 一条delete表达式的执行过程总是先销毁对象 然后调用operator delete函数释放对象所占的空间

2、运行时类型识别RTTI
    
   重要运算符：
   tyopeid:返回表达式的类型
   dynamic_cast:用于将基类的指针或引用安全地转换成派生类的指针或引用

   适用情况：我们想使用基类对象的指针或引用执行某个派生类操作并且该操作不是虚函数
   
   (1)dynamic_cast：动态类型转换
        
     dynamic_cast<type*>(e);
     dynamic_cast<type&>(e);
     dynamic_cast<type&&>(e);
     
     e必须是三种情况之一：e是type类型的公有基类、公有派生类或本类型
   
     指针类型的dynamic_cast

        举例：
        假定Base类至少有一个虚函数，Derived是它的公有派生类
        指针bp指向Base，则我们可以在运行时将它转换成指向Derived的指针

        if(Derived* dp = dynamic_cast<Derived*>(bp))
            //使用dp指向的Derived对象
        else //bp指向一个Base对象
            //使用bp指向的Base对象
     
     我们可以对一个空指针执行dynamic_cast 结果是所需类型的空指针

     引用类型的dynamic_cast
      
     发生错误时，抛出std::bad_cast异常
   
     void f(const Base& b)
     {
        try
        {
            const Derived& d = dynamic_cast<const Derived&>(b);
        }
        catch(bad_cast)
        {
            //处理失败情况
        }
     }
   
   
   (2)typeid运算符（作用于对象）

      作用：允许程序向表达式提问：你是什么类型？
      形式：typeid(e) e可以是任意表达式或类的名字 返回的结果是一个常量对象的引用
            如果表达式是一个引用 则返回该引用所引对象的类型
      
      当运算对象是定义了至少一个虚函数的类的左值时，返回的结果直到运行时求得
      当运算对象不属于类类型 或者 运算对象是一个不包含任何虚函数的类时 返回的结果是运算对象的静态类型
      当运算对象是一个指针时，返回的结果是该指针的静态编译类型

      举例：
      Derived* dp = new Derived;
      Base* bp = new Base;
      //接下来在运行时比较两个对象的类型
      if(typeid(*bp) == typeid(*dp))
      {
            //bp和dp是指向同一类型的对象
      }
      if(typeid(*bp) == typeid(Derived))
      {
            //bp实际指向Derived的对象
      }
   
     总结：
     typeid是否需要运行时检查决定了表达式是否会被求值
     只有当类型含有虚函数时，编译器才会对表达式求值
     反之，如果类型不含有虚函数
     则typeid返回表达式的静态类型(编译器无须对表达式求值也能直到表达式的静态类型)
   
   
     举例：
     class Base
     {
            friend bool operator(const Base&,const Base&);
        public:
            //Base的接口成员
        protected:
            virtual bool equal(const Base&)const;
     }

     class Derived : public Base
     {
        public:
            //Derived的其他接口成员
        protected:
            bool euqal(const Base&)const;
            //Derived的数据成员和其他用于实现的成员
     }

     //接下来定义整体的运算符 比较两个具有继承关系的类
     bool operator==(const Base& lhs,const Base& rhs)
     {
        //如果typeid不相同，返回false 否则虚调用equal
        return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
     }
     在这个运算符中，如果运算对象的类型不同返回false
     如果相同 则运算符将工作委托给虚函数equal
     当运算对象是Base对象时，调用Base::euqal
     当运算对象是Derived对象时，调用Derived::equal

     bool Derived::euqal(const Base& rhs)const
     {
        //清楚这两个类型相等，所以转换不会抛出异常(但是这一步类型转换是必不可少的)
        auto r = dynamic_cast<const Derived&>(rhs);
        //执行了这个类型转换之后，当前函数才能访问rhs的所有成员 否则只能访问基类成员
        //执行比较两个Derived对象的操作并返回结果
     }
     bool Base::equal(const Base& rhs)const
     {
        //执行比较Base对象的操作
     }

     1、在operator==函数中，利用Base&形参来进行接收，基类的指针可以指向派生类 这是可以的
     2、利用typeid进行动态类型分析 (包含虚函数的类) 正确
     3、调用lhs的虚函数 根据动态绑定规则 会根据实际动态对象的类型进行调用 正确
     4、rhs仍是一个基类的指针或引用 在名字查找中向上查找 因此不能访问派生类的特有成员
        因此需要使用dynamic_cast将其转换为派生类的指针 可以访问派生类的所有成员

3、枚举类型
   两类：
   限定作用域的枚举类型 enum class name{}；
   不限定作用域的枚举类型 enum name{}；

   默认情况下，枚举值从0开始，每次加1 可以使用=定制专门的值
   枚举类型是const 不可改变

   enum class open_modes{input,output,append}; 定义一个名为open_modes的枚举类型 包含3个成员
   enum color{red,yellow,green}; 定义了一个不限定作用域的枚举类型color

   color eyes = green; //正确 
   color hair = color::red; //正确 允许显式的访问该成员

   open_modes list = green; //错误 open_modes的枚举成员不在有效的作用域中
   open_modes list = open_modes::input;//正确 使用open_modes的input
   
   
   如何制定enum的大小？

   enum intValues : unsigned long long; //不限定作用域，必须指定成员类型

   enum intValues : unsigned long long   //类似继承的方式
   {
        charTyp = 255.short Typ = 65535,
        longTyp = 429496725UL
   };

   //对于限定作用域的枚举，它的默认大小为int


4、成员指针

   成员指针必须包括成员所属的类，因此必须在*前面添加classname::
   用来表示当前定义的指针可以指向classname的成员  重点！！！

   (1)数据成员指针
   const string Screen::*pdata; //pdata指向一个Screen(常量或者非常量)对象的string成员
   pdata = &Screen::contents;   //令pdta指向某个非特定Screen对象的contents成员
   其中 将取地址运算符作用于类的成员而不是实例化对象

   将前面两句结合为一句：
   auto pdata = &Screen::contents;

   使用数据成员指针：.* and ->*
   Screen myScreen;
   *pScreen = &myScreen;
   auto s = myScreen.*pdta;
   s = pScreen->*pdata;
   运算符执行两步操作：
   1、首先解引用成员指针以得到所需的成员
   2、然后像成员访问运算符一样，通过.或者->来获取成员

   返回数据成员指针的函数：
   (因为类的数据成员一般是私有的)
   class Screen
   {
        //data是一个静态成员 返回一个成员的指针
        static const string Screen::* data()
        {
            return &Screen::contents;
        }
   }
   //data返回的是一个指向Screen类的const string成员的指针（注意是类而不是对象 因此将函数声明为静态的）

   (2)成员函数指针

      指向成员函数的指针必须指定目标函数的返回类型和形参列表 
      如果成员函数是const成员或者引用成员 则我们必须将const限定符或引用限定符包含进来
      举例：
      char (Screen::*pmf)(Screen::pos,Screen::pos)const;
      pmf = &Screen::get;
      //pmf2是成员函数指针 Screen::*是成员函数指针的类型 char是函数返回的类型 与函数指针的区别就是括号内多了Screen::*

      Screen myScreen;
      *pScreen = &myScreen;
      char c = (pScreen->*pmf)(0,0); //通过pScreen对象将实参0,0传给有两个形参的get函数
      括号是必不可少的

      类型别名：
      using Action = char (Screen::*)(Screen::pos,Screen::pos)const;
      Action get = &Screen::get; //Action是指向Screen类的常量成员函数的指针

      Screen& action(Screen&,Action = &Screen:grt);
      //action接受一个Screen的引用 和一个指向Screen成员函数的指针

      调用：
      action(myScreen);             //使用默认形参
      action(myScreen,get);         //使用get也就是函数指针
      action(myScreen,&Screen::get);//显式的传入地址

      成员函数指针表：

      class Screen
      {
        public:
            Screen& home();    //均为光标移动函数
            Screen& forward();
            Screen& back();
            Screen& up();
            Screen& down();

            //Action是一个指针 可以用任意一个光标移动函数对其赋值
            using Action = Screen& (Screen::*)();
            //指定具体移动的方向 
            enum Directions{HOME,FORWARD,BACK,UP,DOWN};// 0 1 2 3 4 
            Screen& move(Directions);
        private:
            static Action Menu[]; //成员函数指针表
            //数组Menu依次保存每个光标移动函数的指针
      }
      Screen::Action Screen::Menu[] = {&Screen::home,&Screen::forward,&Screen::back,
      &Screen::up,&Screen::down};

      Screen& Screen::move(Directions cm)
      {
            //运行this对象中索引值为cm的元素
            return (this->*Menu[cm])();;//Menu[cm]指向一个成员函数
      }
      调用原理：获取索引值为cm的Menu元素 该元素是指向Screen成员函数的指针
                根据this所指向的对象调用该元素所指的成员函数
      
      调用：
      Screen myScreen;
      myScreen.move(Screen::HOME);
      //Screen::HOME是枚举类型Directions中的第一个元素 值为0
      //调用this->*Menu[0]() 也就是解引用home函数的指针 得到home函数 调用home()

      使用function生成一个可调用对象

        成员指针不是一个可调用对象，这样的指针不支持函数调用运算符 
        所以使用function模板转换为可调用对象

        function<bool (const string&) > fcn = &string::empty;
        find_if(svec.begin(),svec.end(),fcn);
        //利用function模板告诉编译器 empty是一个接受string参数并返回bool值的函数

        当我们定义一个function对象时，必须指定该对象所能表示的函数类型 即可调用对象的形式
        如果可调用对象是一个成员函数 则第一个形参必须表示该成员是在哪个对象上执行的
        同时 我们提供给function的形式中还必须指明对象是否以指针或引用的形式传入
        举例：
        vector<string*>pvec;
        function<bool (const string*)>fp = &string::empty;
        //必须制定function接受string*指针 与pvec的存储对象一致
        find_if(pvec.begin(),pvec.end(),fp);

    C++支持几种固有的不可移植的特性，其中位域和volatile使得程序更容易访问硬件
    链接指示使得程序更容易访问用其他语言编写的代码

   */