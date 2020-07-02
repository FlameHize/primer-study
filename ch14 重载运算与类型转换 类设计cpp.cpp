/*
1����������
   ���һ������������ǳ�Ա�����������ĵ�һ��������������󶨵���ʽ��thisָ����
   ��ˣ���Ա�������������ʽ������������������������������һ��

   ������
   data1 += data2;
   data1.operator+=(data2);
   ��������䶼�����˳�Ա����operator+=,��this�󶨵�data1�ĵ�ַ����data2��Ϊʵ�δ����˺���

2�������������������
    IO���޿�����ֻ��ʹ������
    ͨ������£���һ���β�ʱһ���ǳ���ostream���������
    (ԭ������д�����д����ı���״̬�������β�����������Ϊ�����޷�ֱ�Ӹ���һ��ostream����)
    
    �������ͣ�����IO��������

    ���������������������Ƿǳ�Ա����������

3����ֵ��������±������
   
   ����1�������붨��Ϊ��Ա����
         2�����һ��������±������������ͨ�����������汾
            һ��������ͨ���á���һ������ĳ�����Ա���ҷ��س�������

   ������
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

4��ǰ�úͺ��������
    ����ǰ����������ص�������һ������
    ���غ�����������ص�������һ��ֵ 
    ����ǰ��������ǰ���Լ����õ���ֵ����ֵ����������һ�µ�

    ����ʱ������ǰ�úͺ��õ�����
    �涨�������������һ������Ĳ���ʹ�õ�int���͵��β�
    ǰ�������������
    
    p.operator++(0);  ���ú��ð汾������
    p.operator++();   ����ǰ�ð汾������

5����Ա���������
    
    class StrBlobPtr
    {
      public:
        string& operator*()const
        {
            auto p = check(curr,"dereference past end");
            return (*p)[curr]; //*p�Ƕ�����ָ��vector
        }
        string* operator()->const
        {
            //��ʵ�ʹ���ί�и������������
            return &this->operator*();//ʵ�ʷ��ص���vectorĳԪ�صĵ�ַ
        }
        ���صļ�ͷ��������뷵�����ָ������Զ����˼�ͷ�������ĳ����Ķ���
    }
6���������������

    (1)������struct absInt
    {
        int operator(int val)const
        {return val < 0 ? -val : val;}
    }
    ����ʹ�õ���������ķ�ʽ����һ��absInt����������һ��ʵ���б�
    ��һ���̿������ǳ�����ú����Ĺ���
    int i = 42;
    absInt absObj;      //���к�������������Ķ���
    int u = absObj(i);  //��i���ݸ�absObj.operator()

    ��ʹabsObjֻ��һ��������Ǻ���������Ҳ��"����"�ö���
    ���ö���ʵ���������������صĵ����������
    ��������õĶ����Ϊ��������(�������Ϊ����һ��)
    
    ������������������ǳ�Ա����

   (2)����״̬�ĺ���������
     
     ������
     class PrintString
     {
      public:
        PrintString(ostream& o = cout,char c = ''):
            os(o),sep(c){}
        void operator()(const string& s)const{os << s << sep;}
      private:
        ostream& os; //����д���Ŀ����
        char sep;    //���ڽ���ͬ����������ַ�
     }

     PrintString printer;            ʹ��Ĭ��ֵ ��ӡ��cout
     printer(s);                     ��cout�д�ӡs�������һ���ո�
     PrintString errors(cerr,'\n');
     errors(s);                      ��cerr�д�ӡs�������һ�����з�
  
   (3)lambda���ʽ��һ����������
     
     ���ڱ�������˵���Ὣlambda���ʽ�����һ��δ�������δ��������
     ��lambda���ʽ���������к���һ�����صĺ������������

     ��������������ǵȼ۵�

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
    
     ��������ʾlambda����Ӧ������Ϊ����
           ͨ�����ò���--����������ֱ��ʹ�ø����ö�������Lambda���������н���洢Ϊ���ݳ�Ա
           ͨ��ֵ���� -- ����Lambda�����������Ϊÿ��ֵ����ı���������Ӧ�����ݳ�Ա��ͬʱ�������캯��������ʹ�ò��������ֵ����ʼ�����ݳ�Ա
     
     ��������ǵȼ۵�
     auto wc = find_if(words.begin(),words.end(),
               [sz](const string& a)
               {return a.size() >= sz;});
    
    class SizeComp
    {
        SizeComp(size_t n) : sz(n){} //���βζ�Ӧ����ı���
        //�������������ķ������͡��βκͺ����嶼��lambdaһ��
        bool operator()(const string& s)const
        {return s.size() >= sz;}

      private:
        size_t sz;   //�����ݳ�Ա��Ӧͨ��ֵ����ı���      
    }
    auto wc = find_if(words.begin(),words.end(),SizeComp(sz));
  
   (4)�ɵ��ö�����function

      C++�еĿɵ��ö�������
        ����
        ����ָ��
        lambda���ʽ
        bind�����Ķ���
        �����˺����������������

      ���⣺���ʹ��ͬ���͵Ŀɵ��ö�����ͬһ�ֵĵ�����ʽ��

      ����

      int add(int i,int j){ return i + j;};      //��ͨ����
      
      auto mod = [](int i,int j){ return i % j;};//lambda������һ��δ�����ĺ���������

      struct divide                              //����������
      {
        int operator()(int denominatior,int divisor)
        { return denominator / divisor;}
      }

      ���������ֿɵ��ö���ֱ�������ִ���˲�ͬ����������
      �������ǵ����͸�����ͬ�����ǹ���ͬһ�ֵ�����ʽ
      int(int,int)

      ��ι���һ��˼·�Ƕ���һ�����������ڴ洢ָ����Щ�ɵ��ö����ָ��

      ��Ҫ�ı�׼��֧�ֲ�����function

      function<T>f;  f��һ�������洢�ɵ��ö���Ŀ�function����Щ�ɵ��ö���ĵ�����ʽӦ���뺯������T��ͬ
                     ע�������T��result_type(args) ������ʽ
     
      f(args);       ����f�еĶ��󣬲�����args

      function��һ��ģ��
      ���� function<int(int,int)> ����һ��function���ͣ������Խ�������int������һ��int�Ŀɵ��ö���

      function<int(int,int)> f1 = add;    ����ָ��                 
      function<int(int,int)> f2 = divide();   ����������Ķ���
      function<int(int,int)> f3 = [](int i,int j){return i * j;}; lambda

      cout << f1(4,2) << endl;  ��ӡ6
      cout << f2(4,2) << endl;  ��ӡ2
      cout << f3(4,2) << endl;  ��ӡ8

      ʹ�����function���Ϳ��Զ���һ��������map
      map<string,function<int(int,int)>>binops;

      ������Ӳ���

      map<string,function<int(int,int)>>binops = 
      {
        {"+",add},                            ����ָ��
        {"-",std::minus<int>()},              ��׼�⺯������
        {"/",divide()},                       �û�����ĺ�������
        {"*",[](int i,int j){ return i * j;}},δ������lambda
        {"%",mod}                             �����˵�lambda����
      };

      �������������map

      binops["+"](10,5);   ʹ��add(10,5)
      binops["-"](10,5);   ����minus<int>����ĵ��������
      binops["/"](10,5);   ����divide����ĵ��������
      binops["*"](10,5);   ����lambda����
      binops["%"](10,5);   ����lambda����

      ���⣺��ν�����غ�����function֮����ڵĳ�ͻ
      �𰸣���ʹ��lambda������ߺ���ָ�������

      ����
      int add(int i,int j){ return i + j;}   ����add
      Sales_data add(const Sales_data&,const Sales_data&); ��add
      map<string,function<int(int,int)>>binops;
      binops.insert({"+",add });   //���� ���ڶ����Գ�ͻ

      int (*fp)(int,int) = add;
      binops.insert({"+",fp});  ��ȷ fpָ��һ����ȷ�ĺ���add�汾

7�����ء�����ת���������


   (1)����ת�������
       
       ���ã���һ�������͵�ֵת������������
       �﷨: operator type()const;  type��ʾҪת��������

       ������
       class SmallInt
       {
        public:
            SmallInt(int i = 0) : val(i)
            {
                if(i < 0 || i > 255)
                    throw std::out_of_range("Bad value");
            }
            operator int() const { return val;} //����������typeҪһ��
        private:
            std::size_t val;
       }
        
       SmallInt s;
       s = 4; ���ȵ��ù��캯����4��ʽ��ת��ΪSmallInt
       s + 3; ��SmallIntת��Ϊint Ȼ��ִ�������ļӷ�


       ����ʽ���캯������һ��
       ������ת�������ǰ�����explicit�ؼ��֣���ֹ������ʽ������ת��

       ��Ϊ��explicit operator int() const {return val;}
       
       s = 4; ���ȵ��ù��캯����4��ʽ��ת��ΪSmallInt
       s + 3; �������� �˴���Ҫ��ʽ������ת�� ����������������ʽ��
       static_cast<int>(s) + 3;  ��ȷ ��ʽ����������ת��
  
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
    Sales_data() : Sales_data(" ",0,0.0f){}//ί�й��캯��
    Sales_data(const string& s) : Sales_data(s,0,0.0f){}//ί�й��캯��
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

Sales_data::Sales_data(istream& is) : Sales_data() //����ί�й��캯��
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
    return is; //IO��ֻ�ܽ������� û�п���
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