/*
1、通常，使用vector是最好的选择，除非你有很好的理由选择其他容器
   一个容器的元素类型可以是另一种容器

   vector的模板类写法 vector<noDefault>(10,init);  无默认构造函数 写时再判别
   相当于我们可以自定义一个保存这种类型对象的容器
   
   iterator        此容器类型的迭代器类型
   const iterator  可以读取元素，但是不能修改元素的迭代器类型
   size_type       带符号整数类型，足够保存这种容器类型最大可能容器的大小
   value_type      元素类型
   difference_type 带符号整数类型，足够保存两个迭代器之间的距离
   reference       元素的左值类型 相当于&value_type

   带r的迭代器版本返回反向迭代器
   带c的迭代器版本返回const迭代器
   当不需要写访问时，应该使用cbegin和cend

   vector具体操作 见p295

   operator < 不能应用在list容器的迭代器中需要改为！=

   将一个容器初始化为另一个容器的拷贝时，两个容器的容器类型和元素类型必须相同

   顺序容器使用assign方法，允许我们从一个容器不同但是相容的类型相同赋值
   list<string>names;
   vector<const char*>oldstyle;
   names.assign(oldstyle.cbegin(),oldstyle.cend());
   缺点：由于其旧元素被替换。因此传递给assign的迭代器不能指向调用assign的容器
   
   关键概念：容器元素是拷贝
   当我们用一个对象来初始化容器时，或者将一个对象插入到容器中时，实际上
   放入到容器中的是对象值的一个拷贝，而不是对象本身
 

2、顺序容器操作
   
   (1)向顺序容器添加元素：push_back push_front insert
      
      c.insert(p,t)
      在迭代器p指向的元素之前创建一个值为t的元素，返回指向新添加的元素的迭代器
      c.insert(p,n,t)
      在迭代器p指向的元素之前插入n个值为t的元素，返回指向新添加的第一个元素的迭代器
      在新标准下，接受元素个数或范围的insert版本返回指向新添加的第一个元素的迭代器
    
   (2)使用emplace操作
     emplace_front emplace_back emplace分别对应push_front push_back insert
     与之前三个操作的区别：这三个操作在容器中直接构造元素而不是拷贝元素
     也就是在容器管理的内存空间中直接创建对象
     而调用push等操作会创建一个局部临时对象，并将其压入容器中
   
   重点
   (3)访问元素 在容器中访问元素的成员函数返回的都是引用
      如果容器是一个const对象 则返回值是const的引用
      c.back()  返回c中尾元素的引用
      c.front() 返回c中首元素的引用
      c[n]      返回c中下标为n的元素的引用
      c.at(n)   返回下标为n的元素的引用

      auto& 与 auto的区别！！！
      if(!c.empty())
      {
        c.front() = 42;
        auto &v = c.back(); 获得指向最后一个元素的引用
        v = 1024;           改变c中的元素
        auto v2 = c.back(); v2不是一个引用，它是c.back()的一个拷贝
        v2 = 0;             未改变c中的元素
      }
      如果我们使用auto变量来保存这些函数的返回值，并且希望
      使用此变量来改变元素的值，必须记得将变量定义为引用类型(auto&)
   
   (4)删除元素 pop_back pop_front erase clear
      
      c.erase(p) 删除迭代器p所指向的元素 返回一个指向被删元素之后的元素的迭代器
      c.erase(b,e)删除迭代器b和e所指定范围的元素 返回一个指向最后一个被删除元素之后的迭代器
      c.clear() 删除c中的所有元素
      删除元素一般都会使容器中原有的迭代器、指针和引用失效

   (5)改变容器大小
      c.resize(n) 调整c的大小为n个元素 若n < c.size() 则多出的元素被丢弃 否则添加新元素 并进行值初始化
      c.resize(n,t)调整c的大小为n个元素 任何新添加的元素值都初始化为t


      建议：不要保存end返回的迭代器 因为大部分操作都会使原容器中的迭代器失效
 
3、vector容器原理
   
   c.size()     容器中已经保存的元素的数目
   c.capacity() 不重新分配内存的话 容器最多可以保存多少元素
   c.reserve(n) 分配至少能容纳n个元素的空间(并不改变容器中元素的数量 仅影响预先分配的内存空间)
 
   vector分配内存空间的策略：每次需要新分配内存空间时将当前容量翻倍
 
 4、数值转换
    int i = 42;
    string s = to_string(i); 将整数i转换为字符表示形式
    double d = stod(s);      将字符串s转换为浮点数

5、容器适配器
   顺序容器适配器 stack(栈适配器) queue(队列适配器) priority_queue
   适配器的本质：一种机制，使某种事物的行为看起来像另一种事物一样
   一个容器适配器接受一种已有的容器类型，使其行为看起来像另一种不同的类型
   
   举例：stack适配器接受一个顺序容器，并使其操作起来像一个stack一样
   利用deque来初始化一个新的stack
   deque<int>deq;
   stack<int>stk(deq); 从deq拷贝元素到stk

   (1)stack

   栈默认基于deque实现 也可以在list或者vector上实现
   stack<int>intStack;  空栈
   for(size_t ix = 0; ix != 10;++ix)
        intStack.push(ix); 填满栈 保存0-9 10个数
   while(!intStack.empty())
   {
        int value = intStack.top(); 使用栈的顶值
        intStack.pop();             弹出栈顶元素 继续循环
   }

   由上述案例可知，每个容器适配器都基于底层容器类型的操作定义了自己的特殊操作
   我们只可以使用适配器操作，而不能使用底层容器类型的操作

   (2)queue

   队列适配器默认基于deque实现 生成一个类型，使我们能将新元素添加到末尾，从头部删除元素
   标准库queue使用先进先出策略FIFO
   
   
*/