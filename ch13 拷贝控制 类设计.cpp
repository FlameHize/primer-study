/*
1��һ��������������Ա�������������Ʋ�����
   
   �������캯��
   ������ֵ�����
   �ƶ����캯��
   �ƶ���ֵ�����
   ��������

   �������ƶ����캯�������˵�ʹ��ͬ���͵���һ�������ʼ��������ʱ��ʲô
   �������ƶ���ֵ����������˽�һ��������ͬ���͵���һ������ʱ��ʲô
   �������������˵������Ͷ�������ʱ��ʲô

2���������캯��
    
   (1)���ܵĵ�һ������������һ���������������(��������const������)
   ԭ��
      1���������������������ͣ��������Զ����ɹ�
         Ϊ�˵��ÿ������캯�������Ǳ��뿽������ʵ�Σ���Ϊ�˿���ʵ�Σ���������Ҫ���ÿ������캯���������������ѭ��
         Sales_data(Sales_data s) ���ûᴴ��һ�������β�s�ĸ������൱�ڵ�����s����Ŀ������캯����������ȥ����ѭ��
      
      2������const�����൱�������˵ײ�const��ʹ�øÿ���������κβ���������Ӱ�쵽ԭ�������������

   (2)������ʼ����ֱ�ӳ�ʼ��������
   ������ʹ��ֱ�ӳ�ʼ��ʱ������ʵ������Ҫ�������ʹ����ͨ�ĺ���ƥ����ѡ���������ṩ�Ĳ�����ƥ��Ĺ��캯��
   ������ʹ�ÿ�����ʼ��ʱ(����=��)������Ҫ����������Ҳ�������󿽱��� ���ڴ����Ķ��� �У������Ҫ�Ļ���Ҫ��������ת��
                                                                 ��������ֵ�����ͨ���������Ѿ������ģ������Ҫ����������          
   (3)������ʼ���ķ��������

    1��ʹ��=�������ʱ ������
    2����һ��������Ϊʵ�δ��ݸ�һ�����������͵��β�
    3����һ����������Ϊ���������͵ĺ�������һ������
    4���û������б��ʼ��һ�������е�Ԫ�ػ�һ���ۺ���ĳ�Ա

   (4)�ص㣺�������쿽�����Ƿ�static��Ա ��������̬��Ա

   (5)ʹ��=default:
      
      ���ã���ʽҪ����������ɺϳ�(Ҳ����Ĭ�ϵ�)���캯�� ���ںϳɵĺ�������ʽ������Ϊ����
      �涨��ֻ�ܶԺϳɰ汾�ĳ�Ա����ʹ��=default(��Ĭ�Ϲ��캯�����߿������Ƴ�Ա)
   
   (6)�����ֹ������  =delete
      ���������������캯���Ϳ�����ֵ���������Ϊɾ���ĺ���
      ɾ���ĺ�����������Ȼ���������ǣ����������κη�ʽʹ������
      =delete:֪ͨ�����������ǲ�ϣ��������Щ��Ա
      =delete:��������ں�����һ��������ʱ��
      ָ����Χ�����Զ����⺯��ָ��Ϊ=delete����Ȼ��������������
      ���ӣ�
      sturct NoCopy
      {
        NoCopy() = default;  ʹ�úϳɵ�Ĭ�Ϲ��캯��
        NoCopy(const NoCopy&) = delete;  ��ֹ����
        NoCopy& operator=(const NoCopy&) = delete; ��ֹ��ֵ
        ~NoCopy() = default;    ʹ�úϳɵ��������� 
     }

3��������ֵ�����
   
   (1)ͨ������£�Ӧ�÷���һ��ָ�������������������
   
   (2)��д�������������ʱ����������Ҫע�⣺
      
      �����һ����������������ֵ����������ܹ���ȷ�Ĺ��� ����һ��ʵ�����������ԣ�
      �������ֵ�������������������Ϳ������캯���Ĺ���
   
   (3)��дģʽ���Ƚ��Ҳ���󿽱���һ���ֲ���ʱ�����У�
                ��������ɺ�������������������г�Ա���ǰ�ȫ����
                һ���������������Դ�����٣���ֻʣ�½����ݴ���ʱ���󿽱�������������ĳ�Ա����

4����������
    
   ִ���빹�캯���෴�Ĳ���
   ���������ͷŶ���ʹ�õ���Դ �����ٶ���ķ�static���ݳ�Ա
   
   �ص���⣺����������������ֱ�����ٳ�Ա����Ա��������������֮�� �����������׶��б����ٵ�
   
   ���������ĵ���ʱ����

   1�������뿪������ʱ������
   2����һ����������ʱ�����Ա������
   3������������ʱ����Ԫ�ر�����
   4�����ڶ�̬����Ķ��󣬵�����ָ��Ӧ��deleteʱ������
   5��������ʱ���󣬵����������������ʽ����ʱ������

   ���飺���һ������Ҫ�Զ��������������������Կ϶���Ҳ��Ҫ�Զ��忽����ֵ������Ϳ������캯��(��������ظ�ɾ��ָ����߷���ǳ��������)
         ��֮��Ȼ��
   
5���������ƺ���Դ����   
   
   (1)����ȷ�������Ͷ���Ŀ������壺ʹ�����Ϊ��һ��ֵ����һ��ָ��
      �����Ϊ��һ��ֵ����ӵ���Լ���״̬��������ԭ��������ȫ�����ģ��ı丱�������ԭ�������κ�Ӱ��
      �����Ϊ��һ��ָ�룺���ʵ������֮�乲��״̬�������ǿ���һ��������Ķ���ʱ��������ԭ����ʹ����ͬ�ĵײ����ݣ��ı丱��Ҳ��ı�ԭ����

   (2)��Ϊ��ֵ���ࣺ
      ������������Դ��ÿ������Ӧ��ӵ��һ���Լ��Ŀ���
      ��ζ�Ŷ���psָ���string��ÿ��HasPtr���󶼱������Լ��Ŀ���
      1�����忽�����캯�������string�������Ŀ����������ǿ���ָ�뱾��
      2������һ�������������ͷ�string
      3������һ��������ֵ��������ͷŵ�ǰ��string�������Ҳ��������������string
      
     ������
     #include<iostream>
     #include<string>
     using namespace std;

     class HasPtr
     {
       public:
        HasPtr(const string& s = string()):
            ps(new string(s)),i(0){}
        //��psָ���string��ÿ��HasPtr�������Լ��Ŀ���

        HasPtr(const HasPtr& p)://�����Լ���string����
            ps(new string(*p.ps)),i(p.i){}
        //����new����������ǳ�����ظ��ͷŵ�����
        HasPtr& operator=(const HasPtr&);
        ~HasPtr() { delete ps; }
       private:
        string* ps;
        int i;
      };
      HasPtr&
      HasPtr::operator=(const HasPtr& rhs)
      {
        auto newp = new string(*rhs.ps); //�����ײ��string
        delete ps;//�ͷžɵ��ڴ�
        ps = newp;//���Ҳ�������󿽱����ݵ�������
        i = rhs.i;
        return *this;
      }

   (3)��Ϊ��ָ����ࣺ
      ���忽�����캯���Ϳ�����ֵ�������������ָ���Ա�����������ָ���string
      ���������������ͷŽ���string�����Ĺ��캯��������ڴ�

      ��ϸ������·�p457

6�������ƶ� C++11��׼����
    
   �����������Ե�ԭ������Щʱ���ƶ����ǿ�����������ȵ��������ܣ������·����ڴ�Ĺ����У��Ӿ��ڴ潫Ԫ�ؿ��������ڴ��ǲ���Ҫ�ģ����õķ�ʽ���ƶ�Ԫ�أ�
   (һЩ����IO����unique_ptr�����������Թ������Դ�������Щ��Ķ����ܿ������ǿ����ƶ�)
   (1)std::move��׼�⺯��
      �����ͷ�ļ���utility
      ��⣺����move:���������������Ϣ��ϣ��ʹ���ƶ����캯�������ǿ������캯��
      (���߿���������Ϊ�������ڸ��߱�������������һ����ֵ��������ϣ����һ����ֵһ����������)
           
     ���ã���ʽ�Ľ�һ����ֵת��Ϊ��Ӧ����ֵ��������
      (ͨ�����øú�������ð󶨵���ֵ�ϵ���ֵ����)
      ������
      int&& rr1 = 42;            ��ȷ ���泣������ֵ
      int&& rr2 = rr1;           ���� rr1���ʽ����ֵ����Ϊ����һ��������
      int&& rr3 = std::move(rr1);��ȷ ��ʽ�Ľ�һ����ֵת��Ϊ��Ӧ����ֵ��������
      (�������������ζ�ŶԱ�������ŵ�����˶�rr1��ֵ�����������⣬���ǽ�������ʹ����)
   
   (2)��ֵ���� �ص㣡

      Ŀ�ģ�֧���ƶ�����
      ���ʣ�����󶨵���ֵ�����ã����仰˵ֻ�ܰ󶨵�һ����Ҫ���ٵĶ���
      �﷨��&&
      ��������ǿ������ɵĽ�һ����ֵ���õ���Դ�ƶ�����һ��������

      ���֣�
      ��ֵ����ʾ��������(��ַ) �Ƚϳ־�
      ��ֵ����ʾ�����ֵ         �Ƚ϶��ݣ�Ҫô�����泣����Ҫô���ڱ��ʽ��ֵ�����д�������ʱ����
      
      �õ���ֵ�������
      1����ֵ�������Ҫһ���ǳ�����ֵ��Ϊ�����������󣬵õ��Ľ����Ȼ��һ����ֵ
      2�����ý�������������±�����������������������������ֵ���������ֵ
      3���������ͺ͵������ĵ����ݼ��������������ֵ���������ǰ�ð汾��++i�����õĽ������ֵ
      4����������������Ϊһ����ֵ��������������ǰ󶨵���ֵ�ϣ�
      �õ���ֵ�������
      ȡ��ַ��������һ����ֵ������󣬷���һ��ָ�����������ָ�룬���ָ����һ����ֵ
      
      
      ��ֵ���ã����ܰ󶨵�Ҫ��ת���ı��ʽ�����泣��(������������ 10,3.14,'c'�ȣ�ȫ������ֵ)��������ֵ�ı��ʽ����
      ���԰󶨵�������ֵ���õĺ�������ͬ��ֵ���±ꡢ�����ú�ǰ�õ������ݼ������           
      
      ��ֵ���ã�����ֱ�Ӱ󶨵�һ����ֵ��
      ���԰󶨵����ط��������͵ĺ�������ͬ������������ϵ��λ�Լ����õ������ݼ������(const��ֵ����Ҳ���԰���Щ������һ������)
      
      ������
      int i = 42;
      int& r = i;            ��ȷ
      int&& rr = i;          ���� ���ܽ�һ����ֵ����ֱ�Ӱ󶨵�һ����ֵ��
      int& r2 = i * 42;      ���� i*42��һ����ֵ
      const int& r3 = i * 42;��ȷ ���Խ�һ��const����ֵ���ð󶨵�һ����ֵ��
      int&& rr2 = i * 42;    ��ȷ ��׼��ֵ����
    
   (3)�ƶ����캯�����ƶ���ֵ�����
      
    ���ƶ�Ӧ�Ŀ��������������ǴӸ���������ȡ��Դ�����ǿ����������Դ
    ��Ӧ�����βΣ���ֵ����
    ע��㣺�ƶ����Դ��������������һ������Ϊ��ָ�룩
    
    1���ƶ����캯������ڿ������캯����Ҫ��ӵĲ��������ƶ����Դ�������ã�ʹ�䲻��ָ���ƶ�����Դ
    �Ӷ���֤����ЩԴ�������������Ӱ�쵽���ƶ�����Դ
    ������
    StrVec::StrVec(StrVec&& s)noxecept //noxecept��ŵһ���������׳��쳣
    : elements(s.elements),first_free(s.first_free),cap(s.cap)
    {
        s.elements = s.first_free = s.cap = nullptr�� 
        //�ƶ�������Ϊ��ָ�룬ȷ�������ǽ��������ǰ�ȫ��
    }

    //noexcept ��ŵ�������׳��쳣 �����������Ͷ�����ͬʱ�궨
    
    Ϊʲôʹ��noexcept?
    ��ʽ�ĸ��߱�׼�����ǵ��ƶ����캯�����԰�ȫʹ��

    2���ƶ���ֵ�����
    StrVec& StrVec::operator=(StrVec&& rhs)noexcept
    {
        if(this != & rhs)
        {
            free();
            elements = rhs.elements;
            first_free = rhs.first_free();
            cap = rhs.cap();
            //֮��rhs���ڿ�����״̬
            rhs.elements = rhs.first_free = rhs.cap = nullptr;
        }
        return *this;
    }

    3���ϳ�(Ĭ��)���ƶ�����
       
       ֻ�е�һ����û�ж����κ��Լ��汾�Ŀ������Ƴ�Ա�������ÿ����static���ݳ�Ա�������ƶ�ʱ��
       �������Ż�Ϊ���ϳ��ƶ����캯�����ƶ���ֵ�����

    4���ƶ���ֵ ������ֵ ����֮�����ϵ
    
       (1)һ����ͬʱ���ƶ����캯���Ϳ������캯����
          �������캯���βΣ�const StrVec&
          ͨ������ײ�const���Կ����������Խ��ܳ�����ǳ����汾����ֵ����(�ײ�const���԰󶨵�һ���ǳ�����)
          ����Ϊconst&���԰���ֵ�����Ը��β�ͬ�����Խ�����ֵ����
          ��ˣ�����βο��������κο���ת��ΪStrVec������

          �ƶ����캯���βΣ�StrVec&&
          ֻ������ʵ������ֵ������

          ������StrVec v1,v2;
                v1 = v2;                    v2����ֵ(����)��ʹ�õ��ǿ�����ֵ
                StrVec getVec(istream& i);  ����������ص��Ǹ�������һ����ֵ
                v2 = getVec(cin);           getVec(cin)��һ����ֵ����ȷƥ���ʹ���ƶ�����
        //���һ�п�����������ÿ�����ֵ�������Ҫ����һ�ηǳ�����const��ת������StrVec&&���Ǿ�ȷƥ��
        //��ˣ��ڶ�����ֵ��ʹ���ƶ���ֵ�����
       
       (2)һ�����п������캯������δ�����ƶ����캯��
          ����������£�����������ϳ��ƶ����캯��
          ͨ������ƥ����ƣ���֤�����͵Ķ���ᱻ��������ʹ������ͼͨ������move���ƶ�����Ҳ��һ����

          �ص㣺�ÿ������캯�������ƶ����캯�������϶��ǰ�ȫ��

          ������class Foo
          {
            public:
                Foo() = default;
                Foo(const Foo&);
          }
          Foo x;
          Foo y(x);             �������캯����x��һ����ֵ
          Foo z(std::move(x));  �������캯������Ϊδ�����ƶ����캯��
          //move(x)����һ���󶨵�x��Foo&&��Foo&&��ʽ��ת��Ϊһ��const Foo&��const&���԰���ֵ���ã�����˵��õ��ǿ�������

       (3)���ߵĽ��-����/�ƶ���ֵ�����
          ������class HastPtr
               {
                public:
                    HasPtr(HasPtr&& p)noxecept : ps(p.ps),i(p.i){p.ps = 0;}
                    //��ӵ��ƶ����캯��
                    HasPtr(const HasPtr& p): ps(p.ps),i(p.i){}

                    HasPtr& operator(HasPtr rhs) //ע���Ƿ����ò���
                    {swap(*this,rhs);return *this;}
               }
               ������汾�У�����������ƶ����캯�������캯���彫������HasPtrָ����Ϊ��
               �Ӷ�ȷ�����ٺ�Դ�����ǰ�ȫ�ģ����ұ�עnoxeceptȷ���˺������׳��쳣

               �ø�ֵ�������һ�������ò�������ζ�Ų���Ҫ���п�����ʼ��
               ������ʵ�ε����ͣ�������ʼ��Ҫôʹ�ÿ������캯����Ҫôʹ���ƶ����캯��
               ��ֵ����������ֵ���ƶ�
               ��ˣ���һ�ĸ�ֵ�������ʵ���˿�����ֵ��������ƶ���������ֹ���

          ������hp = hp2;    hp2��һ����ֵ��hp2ͨ���������캯��������
                hp = std::move(hp2);�ƶ����캯���ƶ�hp2

    5���ƶ�������(move_iterator)
       ���ã����������������һ����ֵ������
       ���ɷ�����make_move_iterator(iterator) ��һ����ͨ������ת��Ϊһ���ƶ�������

       StrVec::reallocate()
       {
    
        auto newcapacity = size() ? 2 * size() : 1;
    
        auto first = alloc.allocate(newcapacity);
        //�ƶ�Ԫ��
        auto last = unitialized_copy(make_move_iterator(begin()),
                                     make)move_iterator(end()),
                                     first);
        free();  //�ͷž��ڴ�
        elements = first;   //����ָ��
        first_free = last;
        cap = elements + newcapacity;
    
        }
        unitialized_copy�����������е�ÿ��Ԫ�ص���construct����Ԫ��"����"��Ŀ��λ��
        ���㷨ʹ�õ������Ľ������������������������ȡԪ�أ��������Ǵ��ݸ��������ƶ�������
        ��˽�������������ɵ���һ����ֵ����
        ����ζ��construct��ʹ���ƶ����캯��������Ԫ��

    6����ֵ�������Ա����

        ���飺һ����Ա�������ͬʱ�ṩ�������ƶ������汾
        һ���汾����һ��ָ��const����ֵ���ã����Խ��ܴ˶�����κ����ͣ�  �ص㣡����
        �ڶ����汾����һ��ָ���const����ֵ����(ֻ������ֵ����)
       
       void push_back(const T&);  �󶨵��������͵�T
        void push_back(T&&);       ֻ�ܰ󶨵�����T�Ŀ��޸ĵ���ֵ

        �����޶�����&��&&���ֱ�ָ��this����ָ��һ����ֵ����ֵ(����const�޶���)
        ���ͬʱ��const��&�޶��� ��д��Ϊ const &

        ������
        class Foo
        {
          public:
            Foo sorted()&&;  ָ��һ���ɸı����ֵ
            Foo sorted()const &;  �������κ����͵�Foo
          private:
            vector<int>data;
        }
        Foo Foo::sorted()&&
        {
            sort(data.begin(),data/end());  ����������ֵ����˿���ԭַ����
            return *this;
        }
        Foo Foo::sorted()const &
        {
            //��������ƥ����const������һ����ֵ�������Խ���ԭַ����ֻ�ܷ��ظ���
            Foo ret(*this);   ����һ������
            sort(ret.data.begin(),ret.data.end()); ���򸱱�
            return ret;    ���ظ���
        }
        */


/*
#include<iostream>
#include<string>
using namespace std;

class Sales_data
{
public:
    Sales_data(const Sales_data&);//�Զ���Ŀ������캯��
    Sales_data& operator=(const Sales_data&);//�Զ���Ŀ�����ֵ�����
private:
    string bookNo;
    int units_sold = 0;
    double revenue = 0;
};

Sales_data::Sales_data(const Sales_data& orig):
    bookNo(orig.bookNo),
    units_sold(orig.units_sold),
    revenue(orig.revenue) {}  //�պ�����

Sales_data&
Sales_data::operator=(const Sales_data& rhs)
{
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
}
*/

/*

p449 t13.1.4

#include<iostream>
#include<string>

class numbered
{
public:
    numbered()
    {
        mysn = unique++;
    }
    numbered(const numbered& n)
    {
        mysn = unique++;
    }
    int mysn;
    static int unique;
};
int numbered::unique = 10;

void f(const numbered& s)
{
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}
*/


/*

//������������Դ�����Ӧ�ó��� p457 ����һ��ʹ�����ü�������
#include<iostream>
#include<string>
using namespace std;

class HasPtr
{
public:
    HasPtr(const string& s = string()):
        ps(new string(s)),use(new size_t(1)){}

    //�������캯�����������������ݳ�Ա ������������
    HasPtr(const HasPtr& p):
        ps(p.ps), i(p.i), use(p.use) { ++*use;};
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
private:
    string* ps;
    int i;
    size_t* use; //������¼�ж��ٸ�������*ps�ĳ�Ա
};

HasPtr::~HasPtr()
{
    if (-- * use == 0) //������ü�����Ϊ0 �����Ѿ���ǰ-1
    {
        delete ps;  //�ͷ�string�ڴ�
        delete use; //�ͷż������ڴ�
    }
}

HasPtr&
HasPtr::operator=(const HasPtr& rhs)
{
    ++* rhs.use; //�����Ҳ������������ô���
    if (-- * use == 0) //Ȼ��ݼ�����������ô���
    {
        delete ps;    //���û�������û����ͷű��������ĳ�Ա�ˣ�  
        delete use;   //�����Ǳ�����ֻ���ĸ�ָ��ָ���ֵ����Ϊԭ������Դ����������Ա���ã�
    }                 //�����ͷ�ԭָ��ָ���new���ڴ�����⣬�������һ����Ҫ�ͷ�����ڴ�����������������
   
   //��һ���൱�ڿ�����ֵ�����������������
   
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}
*/


/*
//��������ʵ��2 ��Ϣ����

#include<iostream>
#include<string>
#include<set>
#include<memory>
using namespace std;

class Folder;//������
class Message;

class Message
{
    friend class Folder;
    friend void swap(Message& lhs, Message& rhs);
public:
    explicit Message(const string& str = " "):
        contents(str){}
    //�������Ƴ�Ա ��������ָ��Message��ָ��
    Message(const Message&);
    Message& operator=(const Message&); //������ֵ�����
    ~Message();
    void save(Folder&); //�������Folder����ӻ���ɾ��һ��Message
    void remove(Folder&);
private:
    string contents; //ʵ����Ϣ�ı�
    set<Folder*>folders; //����ָ��Message������Folder��ָ�� Ҳ���ǰ�����Message��Folder�б�

    void add_to_Folders(const Message&); //����message��ӵ�ָ��m��Folder��
    void remove_from_Folders();
};

void Message::save(Folder& f) //����Ϣ���浽��Ϣ�б���
{
    folders.insert(&f); //������Folder��ӵ����ǵ�Folder�б���
    f.addMsg(this);     //����Message��ӵ�f��Message������
}
void Message::remove(Folder& f) //����Ϣ�б���ɾ����Ϣ
{
    folders.erase(&f); //������Folder�����ǵ�Folder�б���ɾ��
    f.remMsg(this);    //����Message��f��Message������ɾ��
}
//f.addMsg ��f.remMsg�൱�ڷֱ���Ӻ�ɾ������Message��ָ��

//���� ����ָ�뿽�� ���Ҹ���Folder
void Message::add_to_Folders(const Message& m)
{
    for (auto f : m.folders) //��ÿ������m��Folder
        f->addMsg(this);   //���Folder�����һ��ָ��Message��ָ��
}
Message::Message(const Message& m) :contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

//��Folder��ɾ����Message
void Message::remove_from_Folders()
{
    for (auto f : folders)
        f->remMsg(this);
}
Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message& rhs) //�����൱�ڿ���������
{
    //ͨ����ɾ��ָ���ٲ��������������Ը�ֵ�����
    remove_from_Folders();//�������е�Folder
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);//����Message��ӵ���ЩFolder��
    return *this;
}

void swap(Message& lhs, Message& rhs)
{
    //using std::swap; //����std��swap ֮��ʹ�õ��������Զ����swap
    ////��ÿ����Ϣ��ָ�����ԭ����Folder��ɾ��
    //for (auto f : lhs.folders)
    //    f->remMsg(&lhs);
    //for (auto f : rhs.folders)
    //    f->remMsg(&rhs);

    ////����contents��Folder��ָ��set
    //swap(lhs.folders, rhs.folders); //ʹ��swap(set&,set&)
    //swap(lhs.contents, rhs.contents);
    ////��ÿ��Message��ָ����ӵ�������Folder��
    //for (auto f : lhs.folders)
    //    f->addMsg(&lhs);//���ָ��
    //for (auto f : rhs.folders)
    //    f->addMsg(&rhs);

    using std::swap;
    lhs.remove_from_Folders();
    rhs.remove_from_Folders();

    swap(lhs.folders, rhs.folders); //ʹ��swap(set&,set&)
    swap(lhs.contents, rhs.contents);

    lhs.add_to_Folders(lhs);  //�Լ������Լ�
    rhs.add_to_Folders(rhs);
}

class Folder
{
    friend class Message;
    friend void swap(Folder&, Folder&); 
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();
    void print_debug();
private:
    set<Message*>msgs;
    void add_to_Message(const Folder&);
    void remove_from_Message();

    void addMsg(Message* m) { msgs.insert(m); }
    void remMsg(Message* m) { msgs.erase(m); }
};
void swap(Folder&, Folder&);

*/

/*

//vector��ļ���ʵ��
#include<iostream>
#include<string>
#include<memory>
#include<utility>
using namespace std;

class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();

    void push_back(const string&);
    size_t size()const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

    string* begin()const { return elements; }
    string* end()const { return first_free; }

    void print()
    {
        for (auto iter = elements; iter != first_free; iter++)
            cout << *iter << endl;
    }

private:
    allocator<string>alloc; //����Ԫ��

    void chk_n_alloc()
    {
        if (size() == capacity()) reallocate();
    }

    pair<string*, string*>alloc_n_copy(const string*, const string*);

    void free();        //����Ԫ�ز��ͷ��ڴ�
    void reallocate();  //��ø����ڴ沢�������е�Ԫ��
    string* elements;   //ָ��������Ԫ�ص�ָ��
    string* first_free; //ָ�������һ������Ԫ�ص�ָ��
    string* cap;        //ָ������β��Ԫ�ص�ָ��
};

void StrVec::push_back(const string& s)
{
    chk_n_alloc(); //ȷ���пռ�������Ԫ��
    //��first_freeָ���Ԫ���й���s�ĸ���
    //a.construct(p, args); p������һ������ΪT* ��ָ�룬ָ��һ��ԭʼ�ڴ棬
    //args�����ݸ�����ΪT�Ĺ��캯����������pָ����ڴ��й���һ������
    
    alloc.construct(first_free++, s);
    
    //���ݸ�construct�ĵ�һ������������һ��ָ�룬ָ��allocate�������δ������ڴ�ռ�
    //ʣ�����ȷ�����ĸ����캯�����������
    //�õ��û���first_free��ǰֵָ���ĵ�ַ����һ�����󣬲�����first_freeָ����һ��δ�����Ԫ��
}

pair<string*, string*>
StrVec::alloc_n_copy(const string* b, const string* e)
{
    //����ռ䱣�������Χ�ڵ�Ԫ��
    auto data = alloc.allocate(e - b);
    //���ص�data��һ��ָ��  ָ����ڴ������һ�������Ԫ��֮���λ��
    //��ʼ��������һ��pair����pair��data��unititlized_copy����ֵ����
    
    return { data,uninitialized_copy(b,e,data) }; //�Ѿ�������ԭʼ�ڴ�ռ䣬������
    
    //data�Ƿ�����ڴ濪ʼ��λ�� unitialized_copy���ع�������һ��Ԫ��֮���λ��
    //��b��e��Ԫ�ؿ�����dataָ����δ������ڴ��У�����һ��ָ�룬ָ�����һ�������Ԫ�ص�֮���λ��
}

void StrVec::free()
{
    //���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ0������ʲô������
    if (elements)
    {
        //�������پ�Ԫ��
        for (auto p = first_free; p != elements; )
            alloc.destroy(--p);//�ȵݼ���������
       
       //�ͷ��ڴ�ռ�(�����Ǹ��౾���������Ѿ�������ڴ�ռ�)

        alloc.deallocate(elements, cap - elements);
        //  alloc.deallocate(p, n);  �ͷ�֮ǰ�����s����ԭʼ�ڴ�
        //���ݸ�deallocate��ָ�������֮ǰĳ��allocate���������ص�ָ��
    }
}

StrVec::StrVec(const StrVec& s)
{
    //����alloc_n_copy����ռ���������s��һ�����Ԫ��
    auto newdata = alloc_n_copy(s.begin(), s.end());
    //���ص���һ��pair ��������ָ�� 
    //��һ��ָ��ָ���һ�������Ԫ�� �ڶ���ָ��ָ�����һ�������Ԫ��֮���λ��
    elements = newdata.first;
    first_free = newdata.second;
}

StrVec::~StrVec()
{
    free();
}

StrVec&   //�൱�ڰ������Ϳ�����������һ�� �����Ը�ֵ�����в���
StrVec::operator=(const StrVec& rhs)
{
    //����alloc_n_copy�����ڴ棬��С��rhs�е�Ԫ��ռ�ÿռ�һ����
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();//�ͷ��Լ��Ŀռ䣬�����Լ��� ԭ��Ԫ��
    elements = data.first;
    first_free = cap = data.second;
    //alloc_n_copy����Ŀռ�ǡ�����ɸ�����Ԫ�أ�capҲָ�����һ�������Ԫ��֮���λ��
    return *this;
}

//�����ƶ�����ĺ���
void StrVec::reallocate()
{
    //���ǽ����䵱ǰ��С2�����ڴ�ռ�
    auto newcapacity = size() ? 2 * size() : 1;
    //�������ڴ�
    auto newdata = alloc.allocate(newcapacity);
    //���ص�newdata���״��ڴ�����λ�ã�Ҳ�����ڴ���׵�ַ�ռ�
    //�����ݴӾ��ڴ��ƶ������ڴ�
    auto dest = newdata;//ָ������������һ��δ����λ�ã�Ҳ���ǳ�ʼ��ַ
    auto elem = elements;//�������еĵ�һ����ͷԪ�ص�ָ��
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    //ע���Ǻ��õ��� �ȴ��������е�Ԫ��ֵ �ٵ���ָ��
    free(); //һ���ƶ���Ԫ�ؾ��ͷž��ڴ�ռ�
    //���ǲ�֪�����ڴ��е�string���ڰ���ʲôֵ����C++��֤������ִ��string�����������ǰ�ȫ��
    //�������������ǵ����ݽṹ��ִ����Ԫ��
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;//�̺�ָ�������

}

int main()
{
    StrVec vec,vec2;
    vec.push_back("hello");
    vec.push_back("vslam");
    vec.push_back("aaa");
    vec.push_back("bbb");
    vec.push_back("ccc");
    int size = vec.size();
    int capacity = vec.capacity();
    vec.print();
    cout << size << endl;
    cout << capacity << endl;

    
    vec2.push_back("hello");
    vec2.push_back("vslam");
    vec2.push_back("aaa");

    vec2 = vec;
    int size2 = vec2.size();
    int capacity2 = vec2.capacity();
    cout << size2 << endl;
    cout << capacity2 << endl;


    return 0;
}

*/


/*
#include<iostream>
#include<string>
#include<memory>
#include<initializer_list>


using namespace std;

class StrVec
{
public:
    StrVec() : elements(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec&);
    StrVec(initializer_list<string>);
    StrVec(StrVec&&)noexcept;            //�ƶ����캯��
    StrVec& operator=(const StrVec&);
    StrVec& operator=(StrVec&&)noexcept; //�ƶ���ֵ�����
    ~StrVec();

    void push_back(const string&);
    size_t size()const { return first_free - elements; }
    size_t capacity()const { return cap - elements; }
    string* begin()const { return elements; }
    string* end()const { return first_free; }

    void reserve(size_t new_cap);
    void resize(size_t count);
    void resize(size_t count, const string&);
    void print();

private:
    pair < string*, string*>alloc_n_copy(const string*, const string*);
    
    void free();
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    void reallocate();
    void alloc_n_move(size_t new_cap);
    void range_initialize(const string*, const string*);
private:
    string* elements;
    string* first_free;
    string* cap;
    allocator<string>alloc; //�ڴ������
};

void StrVec::push_back(const string& s)
{
    chk_n_alloc(); //�鿴�費��Ҫ���·����ڴ�ռ�
    alloc.construct(first_free++, s);
}

pair<string*,string*>
StrVec::alloc_n_copy(const string* b, const string* e)
{
    auto data = alloc.allocate(e - b); //�Ѿ�������ԭʼ�ڴ�ռ� ���ҷ��������ĵ�ַ
    return{ data,uninitialized_copy(b,e,data) };
}

void StrVec::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
    
}

void StrVec::range_initialize(const string* first, const string* last)
{
    auto newdata = alloc_n_copy(first, last);
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(const StrVec& rhs)
{
    range_initialize(rhs.begin(), rhs.end());
}

StrVec::~StrVec()
{
    free();
}

StrVec& StrVec::operator=(const StrVec& rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::alloc_n_move(size_t new_cap)
{
    auto newdata = alloc.allocate(new_cap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + new_cap;
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    alloc_n_move(newcapacity);
}

void StrVec::reserve(size_t new_cap)
{
    if (new_cap <= capacity())return;
    alloc_n_move(new_cap);
}
void StrVec::resize(size_t count)
{
    resize(count, string());
}
void StrVec::resize(size_t count, const string& s)
{
    if (count > size())
    {
        if (count > capacity())reserve(count * 2);
        for (size_t i = size(); i != count; ++i)
            alloc.construct(first_free++, s);
    }
    else if (count < size())
    {
        while (first_free != elements + count)
            alloc.destroy(--first_free);
    }
}

void StrVec::print()
{
    for (auto iter = elements; iter != first_free;iter++)
        cout << *iter << " ";
}

StrVec::StrVec(StrVec&& s)noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}
StrVec& StrVec::operator=(StrVec&& rhs)noexcept
{
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}


int main()
{
    StrVec vec, vec2;
    vec.push_back("hello");
    vec.push_back("vslam");
    vec.push_back("aaa");
    vec.push_back("bbb");
    vec.push_back("ccc");
    int size = vec.size();
    int capacity = vec.capacity();
    vec.print();
    cout << size << endl;
    cout << capacity << endl;


    vec2.push_back("hello");
    vec2.push_back("vslam");
    vec2.push_back("aaa");

    vec2 = vec;
    int size2 = vec2.size();
    int capacity2 = vec2.capacity();
    cout << size2 << endl;
    cout << capacity2 << endl;


    return 0;
}
*/
