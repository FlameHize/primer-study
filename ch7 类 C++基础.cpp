/*
1�����������ڲ��ĺ�������ʽ��inline����
   ����������ı���˳�����ȱ����Ա��������ֱ����ȫ���ɼ�
   Ȼ���ٱ����Ա�����壨��˳�Ա��������������ʹ����ĳ�Ա�����ù��ĳ��ֵ�˳��
   �����������������ȫ������֮��Żᴦ���Ա�����Ķ���

   ���������class ClassName; ǰ������ ָ��ClassName��һ�������ͣ��޶���֮ǰ��һ�ֲ���ȫ���ͣ�
   һ��һ��������ֳ���֮�����ͱ���Ϊ����������

   ������п��԰�����������û�����ָ�룬���ǲ��ܰ����Լ�  ������

   �����������ò�������һ����ʱ��
   ��⣺���һ����������һ����const��ʽ���룬��ô�������ͻ���Ϊ����Ա���ں������޸����ֵ��
         ������Ϊ��ʱ�����������ԣ�����Ա�����ܲ�����ʱ���������������ʱ����������ʱ���ᱻ�ͷŵ���
         ����һ����˵�޸���ʱ������������ģ����C++�������涨ֻ��ʹ�ó���������������ʱ����
   
2��this
   (1)
   �κζ����Ա��ֱ�ӷ��ʶ���������this����ʽ����
   this��Ŀ������ָ�������������this��һ������ָ�루����const ������һ��������
   ���ǲ���������Ըı�this�б���ĵ�ַ
   
   (2)
   Ĭ������£�this��ָ�������ͷǳ����汾�ĳ���ָ�� Ҳ���� *const������const���ǵײ�const) 
   �ɾ����� const double i = 42;
			double* p = &i;   ���� �ײ�const�����Ա�����
   ��֪��������һ��thisָ����ָ�����ĳ����汾����Ϊ�ײ�const�����Ա����ԣ�

   ��һ���Ҳ����ζ�����ǲ�����һ�������汾�ϵ��ö�����ĳ�Ա����
   
   ->��õĴ���취������this��ǰ�����const�ؼ��ָ�Ϊָ�����ĳ���ָ��Ӷ��볣��������ƥ�䣨ͬʱҲ����ƥ��ǳ�������
   
   C++����������const�ؼ��ַ��ڳ�Ա�����Ĳ����б�֮�󡣣���ʱ�������ڲ����б�����const��ʾthis��һ��ָ������ָ�룩
              ������ʹ��const�ĳ�Ա��������������Ա������������Ա�������ܸı�������Ķ�������ݣ�
    
    ���䰸����p248 const��Ա�����ͷ�const��Ա���������� (���õײ�const��д��������) 
   ����Ա�������const��ζ��const*thisָ��(����const)ת��Ϊ const * const thisָ��(Ҳ���Ǳ���˵ײ�+����const) �����ײ�const �γ�����
    ���У�������Ա���غ�������ƥ�䳣���Լ��ǳ�������  ��ͨ���س�Ա����ֻ����ƥ��ǳ�������
    ����ǳ�������ĵ��ú��������õľ��ǳ�����Ա���غ���(Ψһƥ��),����Ƿǳ������󣬵��õľ�����ͨ��Ա���غ���(��ȷƥ��)

   һ��const��Ա������������Ա��������������õ���ʽ����*this,��ô���ķ�������Ҳ�����ǳ�������const& ����Ϊ�ײ�const�����Ա�����)������
   
   ���������еĿɱ����ݳ�Ա�����Ҫ���޸ĳ�����Ա����������ض�������ֵ������ͨ���ں����������ڸñ���ǰ���mutable�ؼ�����ʵ��

   �������õĺ�������ֵ�ģ����෵�صľ�Ϊ��ֵ

3��IO�಻���Ա����� ��������ֻ����IO������
   ���ң���Ϊ��ȡ�����������ı��������ݣ����������������ܵĶ�����ͨ���ã����ǶԳ���������

4�����캯��
   
   (1)Sales_data(const std::string& s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(p*n) {}
      ���캯����ʼֵ�б�����Ϊ�´����Ķ�������ݳ�Ա��ֵ ����Ϊ���﷨��ʽ
    
    �ϳɵ�Ĭ�Ϲ��캯��:ClassName() = default;
    
   (2)���캯����ʼ�������ֳ�ʼ���б�͸�ֵ����
        �����Ա��const�������õĻ�������ʹ�ó�ʼ���б������г�ʼ��
        ���飺�Ƽ�ʹ�ó�ʼ���б�����Ǹ�ֵ����(��Ȼ��������Ч��Ҳ����)
        (��Ա�ĳ�ʼ��˳�������������ж����˳����һ�µ�)

   (3)ί�й��캯��(delegating constructor)
      
      ���ã�����ʹ��������������������캯��ִ�����Լ��ĳ�ʼ�����̣�Ҳ���ǰ��Լ���ְ��ί�и����������캯����

      ������
      class Sales_data
      {
         public:
            //��ί�й��캯��ʹ�ö�Ӧ��ʵ�γ�ʼ����Ա
            Sales_data(const std::string& s, unsigned cnt, double price)
            : bookNo(s), units_sold(cnt), revenue(price*cnt) {}
            //���๹�캯��ȫ��ί�и���һ�����캯��
            
            Sales_data() : Sales_data(" ",0,0){}
            //�����Ĭ�Ϲ��캯��ʹ���������Ĺ��캯����ɳ�ʼ���Ĺ���

            Sales_data(istream& is) : Sales_data(){ read(is,*this);}
            //�ý���istream&�Ĺ��캯��Ҳ��ί�й��캯������ί�и���Ĭ�Ϲ��캯����
            Ĭ�Ϲ��캯���ֽ���ί�и������������캯��
            ����Щ��ί�еĹ��캯��ִ����󣬽���ִ��istream&���캯���������
            (������ί�еĹ��캯���к�����Ļ�������ִ��������ִ��ί���ߵĺ�����)
      }

   (4)���캯��explicit�ؼ��֣�C++�е�explicit�ؼ���ֻ����������ֻ��һ������
     ����ֻ��һ��������������ΪĬ�ϲ��������๹�캯��,���������Ǳ����ù��캯������ʾ��,������ʽ��
      �Ӷ���ֹ������ʽת��
      �ҵ�������explicit�ؼ����������캯��ʱ��ֻ����ֱ�ӳ�ʼ������ʽʹ�ã�����ʹ�ÿ�����ʼ��
      
   (5)constexpr���캯����һ��Ϊ�� �����ʼ���������ݳ�Ա(��ʼ������ʹ��constexpr���캯����������һ���������ʽ)

   5�����ʿ��ƺͷ�װ
   
   (1):������public˵����֮��ĳ�Ա�����������ڿɱ�����
       public��Ա������Ľӿ�

       ������private˵����֮��ĳ�Ա���Ա���ĳ�Ա�������ʣ�
       private���ַ�װ�����ʵ��ϸ��

   (2):������Ԫfriend����ʹ����ĺ����������ڵ�˽�г�Ա����
        
        ������Ԫ������һ����Ԫ�� ����Ԫ��ĳ�Ա�������Է���������˽�г�Ա

        A��ĳ�Ա����F����Ԫ��ֻ��A�ĳ�Ա�������Է��������B��˽�г�Ա
        ���������ȶ���A�࣬��������F���������ǲ��ܶ����� ��Fʹ��B�ĳ�Ա֮ǰ����������B
              ����������B ��������F����Ԫ����
              �����F ��ʱ���ſ���ʹ��B�ĳ�Ա
        
        ���غ�������Ԫ����Ҫ��ÿһ���������зֱ�����

        ��Ԫ�����е�������������ڸ��������е������������������������ſɵ���

   (3)������
      :: ����ȫ��������
      ClassName:: ������������
      �ڲ��������������¶�������������е����֣���������ʱ�����ڲ�������������������������

      ���飺�������Ķ��������Ŀ�ʼ����ȷ������ʹ�ø����͵ĳ�Ա�������������Ķ���֮��

      ��Ա����֮ǰ����ͨ����������ֲ���(p255)
      1�����ȣ��ڳ�Ա�����ڲ��Ҹ����ֵ�������ֻ���ں���ʹ��֮ǰ���ֵ������Żᱻ���ǣ�
      2������ڳ�Ա�����ڲ�û���ҵ����������ڼ������� ��ʱ��������г�Ա�����Ա�����
      3���������Ҳû���ҵ������ֵ����������ڳ�Ա��������֮ǰ��������������ֲ���

6����ľ�̬��Ա
   
   ������class Account
   {
      public:
        void calculate(){amount += amount * interestRate;}
        static double rate(){return interestRate;}
        static void rate(double);
      private:
        string owner;
        double amount;
        static double interestRate;
        static double initRate();
        
        //ÿ��Account����ʵ����ֻ�����������ݳ�Ա��owner �� amount
        //ֻ����һ��interestRate���������������Account������

        //��̬��Աһ�㱻���Ϊһ������ �����ǵ���������
    }
    ��ľ�̬��Ա(static�ؼ��ֱ�ע)�������κ�ʵ������֮�⣬�����в������κ��뾲̬��Ա�йص�����
    ���ң���̬��Ա���������κζ���󶨵�һ�𣬲�����thisָ�룬ͬʱ��̬��Ա�������ܱ�����Ϊconst

    Ҫ����ʾ�̬��Աһ��ʹ�������������ֱ�ӷ���  ��ȻҲ����ʹ��thisָ����� �����Ǿ�̬��Ա����������ʹ��thisָ�룩
    double r;
    r = Account::rate();
                                  �����ǵȼ۵�
    Account ac1;
    r = ac1.rate();

    ���岢��ʼ��һ����̬��Ա����
    double Account::interestRate = initRate();   
    ��������ΪinterestRate�Ķ��󣬸ö�����Account��ľ�̬��Ա����������double
    (��������ʼ��������������ʣ�ಿ�־�λ����������������ˣ���˿���ֱ�ӵ���initRate()����)
    

    ���⣺��ζ��徲̬��Ա��
    �𰸣�������ⲿ���徲̬��Աʱ������ʹ��static�ؼ��֣��ùؼ���ֻ���������ڵ����������
          һ��������ⲿ����ͳ�ʼ����̬��Ա �������������ڿ����캯����ʼ�� ���Ǵ���� ��Ϊ��̬��Ա�������౾��
          (static constexpr��̬��Ա���������ڶ���)
    �ܽ᣺��̬��Ա���ݶ������κκ���֮�⣬һ�������壬��һֱ�����ڳ������������������

    ����Ӧ�ã�
    ��̬���ݳ�Ա��������������������ͣ����Ǿ�̬��Ա���ܵ����ƣ�ֻ�����������������ָ���������
    ��̬���ݳ�Ա������ΪĬ��ʵ�Σ��Ǿ�̬�����ԣ���Ϊ�Ǿ�̬���ݳ�Ա�����һ���֣�����̬�Ƕ����ģ�

7���ۺ���
    ֻ���й��г�Ա���࣬����û�����ڳ�ʼֵ���߹��캯��
    �ۺ���ĳ�Աһ��ʹ�û������������ĳ�ʼֵ�б���г�ʼ��
    �������Ϊһ���򵥵�struct
    
    
    */


/*

Sales_data 1.0�汾

#include<iostream>
#include<string>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

struct Sales_data
{	
	//����Ĳ���
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price()const;
	
	//���ݳ�Ա
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

double  Sales_data::avg_price()const
{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}
Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream& read(istream& is, Sales_data& item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream& print(ostream& os, Sales_data& item)
{
    os  << item.isbn() << " "
        << item.units_sold << " "
        << item.revenue << " "
        << item.avg_price();
    return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

int main()
{
    Sales_data total;
    if (read(cin, total))
    {
        Sales_data trans;
 
        while (read(cin,trans))
        {   
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(cout, trans);
                total = trans;
            }
            
        }
        print(cout, total);
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;
}
*/

/*

Sales_data 2.0�汾

#include<iostream>
#include<string>
struct Sales_data
{
    Sales_data() = default;
    Sales_data(const std::string& s) : bookNo(s){}
    Sales_data(const std::string& s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(p*n) {};
    Sales_data(std::istream& s) { return read(is, *this); }
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price()const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// nonmember functions
std::istream& read(std::istream& is, Sales_data& item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item)
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

*/


/*

Sales_data 3.0�汾 ��Ԫ��

#include<iostream>
#include<string>
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
    Sales_data(const string& s) : bookNo(s){}
    Sales_data(istream& is) {  read(is, *this); }
    
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

*/