/*
1�������㷨��������ִ�������ϵĲ���������ֻ�������ڵ�����֮�ϣ�ִ�е������Ĳ��� 
             Ҳ����˵���㷨��Զ����ı�ײ������Ĵ�С

2�����㷨���ݵĺ���---ν��
   
   ν�ʣ�һ���ɵ��õı��ʽ���䷵�ؽ����һ��������������ֵ �����ؿ���ת��Ϊbool���͵�ֵ�ĺ�����
   ����һԪν��(���ܵ�һ����)�Ͷ�Ԫν��(������������)
   ����ν�ʲ������㷨һ�㶼��_ifǰ׺
   ������
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
   predicate����һ��һԪν��

   д������Ŀ�Ŀռ���㷨�������ֺ��渽��һ��_copy

3��lambda���ʽ   �ص�
   
   �������һ��lambda���ʽ��ʾһ���ɵ��õĴ��뵥Ԫ�����Խ������Ϊһ��δ��������������

         auto f = []{reutrn 42;};      
         ��������У����Ƕ�����һ���ɵ��ö���f���������ܲ���������42
         cout << f() << endl;  ��ӡ42
         lambda�ĵ��÷�ʽ����ͨ�����ĵ��÷�ʽ��ͬ ����ʹ�õ��������
         ��     �����������()    �� ʹ��()������һ������

   �﷨��[�����б�](�����б�)->��������{������};
         �����б�lambda���ں����ж���ľֲ��������б�
         һ��lambda���ʽֻ�����䲶���б��в���һ�������ں����ľֲ������������ں�������ʹ�øñ���
         �����뺯������һ������ͬ����lambda����ʹ��β�����ͷ���
   
   һ��lambda���ʽ����Ҫ�е�Ԫ�أ������б�ͺ�����  �������Ժ��Բ�д

   lambda������Ĭ�ϲ��� �����lambda�ĺ���������κε�һreturn���֮������ݣ���δָ���������͡��򷵻�void

   ������sort(words.begin(),words.end(),
              [](const string& a,const string& b)
              { retutn a.size() < b.size();});
   ��sort��Ҫ�Ƚ�����Ԫ��ʱ���ͻ�������lambda���ʽ

   ������
   vector<string>words = {"aa","bb","ccc"};   
   int sz = 2;    
   auto wc = find_if(words.begin(),words.end(),
   [sz](const string &a){return a.size() > sz;});   
   cout << *wc << endl;

   ע�⣺�����б�ֻ���ھֲ���static������lambda����ֱ��ʹ�þֲ�static����
   ���������ں���֮������������

   ����lambda�Ĳ����뷵�أ�
   ������һ��lambdaʱ������������һ����lambda��Ӧ���µ�δ������������
   (auto f = []{return 42;}�൱�ڸ����δ�����Ŀɵ��ö���������֣����Ҳ�������Ϊһ��δ��������������)

   ����һ����������һ��lambdaʱ��ͬʱ������һ�������ͺ͸����͵�һ������
   Ĭ������£���lambda���ɵ��඼����һ����Ӧ���lambda������ı��������ݳ�Ա

   ���ֲ���ʽ��ֵ���������ò���
   (1)ֵ���񣺱�����lambda����ʱ�����������ǵ���ʱ����
      ���ڱ�����ı�������lambda����ʱ����������������޸Ĳ���Ӱ�쵽lambda�ڶ�Ӧ��ֵ
      ������
      void fcn1()
      {
         size_t v1 = 42;
         auto f = [v1]{return v1;};
         v1 = 0;
         auto j = f();    j����42 f���������Ǵ�����ʱv1�Ŀ���
      }
   (2)���ò��񣺵�������lambda��������ʹ�ô˱���ʱ��ʵ����ʹ�õ����������󶨵Ķ���
      ������
      void fcn2()
      {
         size_t v1 = 42;
         auto f2 = [&v1]{return v1;};
         v1 = 0;
         auto j = f2();    j����0 f2����v1������ �����ǿ���
      }
      ע�⣺�������÷�ʽ����һ������ʱ�����뱣֤��lambdaִ��ʱ����ʱ���ڵ�

   (3)��ʽ���� [&]���ò������÷�ʽ [=]����ֵ����ʽ
      �����ǻ��ʹ����ʽ�������ʽ����ʱ�������б�ĵ�һ��Ԫ�ر�����&����=
      �˷���ָ����Ĭ�ϲ���ʽΪ���û�ֵ
      
      [names] Ĭ������£������б��еı������Ǳ�����������ǰ���ʹ����&����������ò���ʽ
      [&] ��ʽ�����б� �������ò���ʽ
      [=] ��ʽ�����б� ����ֵ����ʽ
      [&,identifier_list] �κ���ʽ����ı������������÷�ʽ���� identifier_list����ֵ���� 
      [=,identifier_list] �κ���ʽ����ı���������ֵ��ʽ���� identifier_list�������ò���
      

   (4)�ɱ�Lambda
      Ĭ������£�����һ��ֵ�������ı�����lambda����ı����ֵ ���Ҫ�ı䣬���ڲ����б��׼��Ϲؼ���mutable
      һ�����ò���ı����Ƿ�����޸������ڴ�����ָ�����һ��const���ͻ���һ����const����
     
4����׼��bind����
     ʵ�ʣ����������� 
     ���ã�����һ���ɵ��ö�������һ���µĿɵ��ö���������Ӧ��ԭ����Ĳ����б�
     ����ͷ�ļ�:functional
     ����������using namespace std::placeholders
     ������ʽ��auto newCallable = bind(callable,arg_list);
     �����ǵ���newCallableʱ��newCallable�����callable,�����ݸ�callable arg_list�Ĳ���

     arg_list ��������������Ϊ����callable�β��е�λ��
     ��ͬ���ǣ���Щ�����п��ܰ���_n�����֣�Ҳ����ռλ��
     (ռλ��_n��ʾ newCallable�Ĳ�����
     ����ռ����newCalable�Ĳ���λ�ã������ݸ�callable)
     _1 newCallable�ĵ�һ���������ݵ�callable���λ������
     _2 newCallable�ĵڶ����������ݵ�callable���λ������
     
     ������
     (1)
     auto check6 = bind(check_size,_1,6);
     ���壺check6ֻ����һ������(_1) ����������ݵ�check_size��_1���ڵ�λ���ϣ�Ҳ���Ǵ����������ĵ�һ���βΣ�
     ����check6(s) �͵ȼ��ڵ���check_size(s,6);
     (2)
     auto g = bind(f,a,b,_2,c,_1);
     ����g(_1,_2) �ȼ��ڵ���f(a,b,_2,c,_1);
     ��g�ĵ�һ����������f�ĵ��������λ�� ��g�ĵڶ�����������f�ĵ������β�λ��
     f�ĵ�һ���β���a�� �ڶ����β���b�� ���ĸ��β���c�� 
     ���仰˵
     ����g(X,Y)    �ȼ��ڵ���f(a,b,Y,c,X);
     

     ���⣺��ΰ����õĲ�����
     (Ĭ������£�bind����Щ����ռλ���Ĳ�����������bind���صĿɵ��ö�����)
     �𰸣��Ըò���ʹ��ref ��ref(s) ������s������

     ������
     ostream& print(ostream& os,const string& s,char c)
     {
        return os << s << c;
     }
     for_each(words.begin(),words.end(),bind(print,ref(os),_1,""));
     */   



/*

p344 t10.9
��������β�������ƶ���ģ�� �ײ�const��Ӧ��

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

p349 �������� t10.16

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
    elimDups(words); //����Ԫ�� �����ظ��ĵ���
    stable_sort(words.begin(), words.end(),
        [](const std::string& a, const std::string& b)
        {return a.size() < b.size(); });
    //���������򣬳�����ͬ�ĵ���ά���ֵ���

    auto wc = find_if(words.begin(), words.end(),
        [sz](const std::string& a) {return a.size() >= sz; });
    //��ȡһ����������ָ���һ������size() >= sz��Ԫ��

    auto count = words.end() - wc; //��������������Ԫ�صĸ���
    
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