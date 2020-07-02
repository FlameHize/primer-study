/*

1、getline函数：从一个给定的istream读取一行数据，存入一个给定的string对象中

2、fstream 读写命名文件的类型

3、IO对象无拷贝和赋值 进行IO操作的函数通常以引用方式传递和返回流

4、while(cin >> word)
   while表达式返回流的状态 如果输入操作成功，流保持有效状态，则条件为真，否则为假

5、流状态管理
   s.rdstate()  返回流s的当前状态
   s.setstate() 将流s中的对应条件状态位置位
   s.clear()    将流s中的所有条件状态位置位 将流的状态设置为有效
   s.eof()      若流s的eofbit置位(eofbit用来指出流达到了文件结束)，则返回ture
   s.good()     若流s处于有效状态 则返回true
   s.bad()      若流s的badbit置位(badbit用来指出流已经崩溃) 则返回true
   s.fail()     若流s的badibit或者failbit(failbit用来指出一个IO操作失败)置位，则返回true

6、文件输入输出
   
   fstream 读写给定文件
   ifstream 读给定文件
   ofstream 写给定文件

   fstream fs;    创建一个未绑定的文件流fs
   fstream fs(s); 创建一个fstream流fs，并打开名为s的文件

   举例：ifstream input(argv[1]);
         ofstream output(argv[2]);
         Sales_data total;
         if(read(input,total))
         {
            Sales_data trans;
            while(read(input,trans))
            {
                if(total.isbn() == trans.isbn())
                    total.combine(trans);
                else
                {
                    print(output,total) << endl;
                    total = trans;
                }
            }
            print(output,total) << endl;
         }
   因为fstream是iostream的子类，因此需要使用iostream&的地方都可以用fstream来代替（通过父类的指针访问子类对象）

7、文件模式
   
   in      以读方式打开
   out     以写方式打开
   app     每次写操作前均定位到文件的末尾
   ate     打开文件后立即定位到文件的末尾
   trunc   截断文件 
   binary  以二进制进行IO

   具体详见：p286

   注意：默认情况下，当我们打开一个ofstream时，文件的已有内容会被丢弃
         阻止一个ofstream清空给定文件内容的方法是同时指定app模式
         (保留被ofstram打开的文件已有数据的唯一方法是显式指定app或者in)
         ofstram out("filename",ofstram::out | ofstram::app)
   
   调用open打开的隐含模式是输出和截断
   
8、string流
    
   定义的头文件:sstream
   istringstream从string读入数据 ostringstream向string写入数据
   
   举例：
   struct PersonInfo
   {
        string name;
        vector<string>phones;
   }
   
   string line,word; //分别保存来自输入的一行和单词
   vector<PersonInfo>people;
   while(getline(cin,line))
   {
        PersonInfo info;
        istringstream record(line); //将记录绑定到刚输入的行
        record >> info.name;        //读取名字
        while(record >> word)       //读取电话号码
            info.phones.push.back(word);
        people.push_back(info);
   }

   string容器操作：p323
   
   substr(pos,n)返回一个string,包含s中从pos开始的n个字符的拷贝
   s.find(args) 查找字符串args 返回第一个匹配位置的下标
   */


/*

p285 t8.4

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

void ReadFileToVec(const string& filename, vector<string>& vec)
{
    ifstream ifs(filename);
    while (ifs)
    {
        string buf;
        while (getline(ifs, buf))
            vec.push_back(buf);
    }
}

*/