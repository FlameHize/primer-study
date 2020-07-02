/*

1�������ķ������Ͳ�����������ߺ������ͣ����ǿ�����ָ��������ߺ�����ָ��

2���ֲ�������ֲ���̬����
   �ֲ������βκͺ������ڲ�����ı��������ں�������ڲ��ɼ���ͬʱ���Ը������������ͬ������
   ������ִ����Ϻ�����
   �ֲ���̬���󣺺����ڲ�ͨ��static���εı��� �ڳ����ִ��·����һ�ξ����������ʱ�����ʼ����
   ����ֱ������������ֹ�Żᱻ���٣��ڴ��ڼ伴ʱ�ö������ڵĺ�������ִ��Ҳ���������Ӱ�졣

3��C++�У�����ʹ���������͵��βδ���ָ��
   �����������޸����ò�����ֵʱ���ʹ�ó�������
   һ������ֻ�ܷ���һ��ֵ��Ȼ����ʱ������Ҫ���ض��ֵ�������β�Ϊ���Ƿ��ض��ֵ�ṩ��һ����Ч;��

4�������еĶ���const(�����ڱ����const)                              ����������
   ����ʵ�γ�ʼ���β�ʱ����Զ���const,���仰˵���βεĶ���const�����Ե��ˣ�
   ���β��ж���constʱ�����ݸ����������߷ǳ��������ǿ��Ե�

   ���������ز��ܺ��Զ���const һ��ӵ�ж���const���β��޷�����һ��û�ж���const���β����ֿ���
   ���Ǻ��������ؿ������ֵײ�const

   ����ʹ��һ���ǳ�����������ʼ��һ���ײ�const���󣬵��Ƿ��������� ��Ϊ�ײ�const���ܱ�����
   int i = 42;
   const int* p = &i; ��ȷ ����p���ܸı�i
   const int& r = i;  ��ȷ ����r���ܸı�i

   const int i = 42;
   int* p = &i ���� �ײ�const�����Ա�����

   int& r = i  ���� �ײ�const�����Ա�����

   ���飺����ʹ�ó������� 
   ����������������β���int*�������ʵ����const int*���ͻᷢ������ ���ײ�const���ɺ��ԣ�
         ����������β���const int*�������ʵ����int*,�ǿ��Եģ���Ϊ����ʹ��һ���ǳ�����������ʼ��һ���ײ�const����
   ��ˣ�ʹ�����ö��ǳ������ûἫ������ƺ������ܽ��ܵ�ʵ������
   
   ���䣺p208
   ����const int* /const int&���βο��Խ��ܳ����Լ��ǳ������� 
   ����int* / int&���β�ֻ���Խ��ܷǳ�������

5�������β�

   ����������������������ʶ����Ƕ����ʹ�������������õĺ�����Ӱ��
   (1)������������                            �޷���ֵ���ݵķ�ʽ��ʹ���������
   (2)����ʹ��ʱͨ���ᱻ����Ϊָ��              Ϊ��������һ������ʱ��ʵ���ϴ������ָ��������Ԫ�ص�ָ��

   int arr[10] = {1,2,3,4,5,6,7,8,9,10};
   
   print(const int*);
   print(const int[]);                            ���ĸ������ǵȼ۵�  ʵ���ϴ���Ķ���const int*  
   print(const int[10]);
   print(arr);    arrת����const int*��ָ��arr[0]
   
   ��������Ǵ���print�����Ĳ�����һ�����飬��ʵ�λ��Զ���ת����ָ��������Ԫ�ص�ָ��

   ����Ĵ�С������ĵ�����û��Ӱ���

   �����Ǽ��ִ��벻ͬ�β����͵�print�����Ķ��巽ʽ
    void print(const char* cp)
    {
        if (cp)
        while (*cp)
            cout << *cp++;
    }
    void print(const int* begin, const int* end)
    {
        while (begin != end)
            cout << *begin++ << endl;
    }
    print(begin(arr), end(arr));

    void print(const int arr[], size_t len)
    {
        for (size_t i = 0; i != len; i++)
            cout << arr[i] << endl;
    }
    void print(const int(&arr)[10])
    {
        for(auto elem : arr)
            cout << elem << endl;
    }

6��main ����������ѡ��
   main(int agrc,char* *argv)
   ��һ���βα�ʾ�������ַ�����ʵ�������������ַ�����������
   �ڶ����β�argvʵ������һ���������Ԫ�ص�ָ��
   (argv��ָ��������Ԫ�ص�ָ�� ������*argv�õ�����Ԫ��char* 
   ��Ϊ����Ԫ����һ��ָ��Ԫ�� �ٴν����û�õ�ָ��Ĵ洢ֵchar,Ҳ����������������ַ���)
   
   argv���ָ��������Ԫ�ص�ָ����������Ϊ�������֣����������Ԫ��Ϊchar*ָ�룩
   argv[1]��argv[2]�ȼ�������ĵڶ�����������char*Ԫ��
   ��char *c = "hello";����ֱ�ӱ�ʾ�������ַ���

   ��ʹ��argv��ʵ��ʱ���ǵÿ�ѡ��ʵ�δ�argv[1]��ʼ argv[0]�����������֡��������û�������

7�������Ŀɱ��β�initializer_list   ������

   Ӧ�ó��������������ʵ������δ֪����ȫ��ʵ�ε����Ͷ���ͬ
   initializer_list ��׼�����ͣ����ڱ�ʾĳ���ض����͵�ֵ������
   Ӧ�ã�initializer_list<T> il;
   �ص㣺initializer_list�����е�Ԫ����Զ�ǳ���ֵ �����Ա��ı�

   �������initializer_list�β��д���һ��ֵ�����У����������з���һ�Ի�������
   
   ������
   void error_msg(initializer_list<string>i1)
   {
        for(auto begin = i1.begin();begin != i1.end();i1++)
            cout << *begin++ << endl;
   }
   //expected��actual����string����
   error_msg({"functionX","expected","actual"});

8��return���
   (1)return;
   return expression; ���ر��ʽ��ֵ    ���ʵ���бȽϳ���

   (2)���򣺲�Ҫ���ؾֲ���������ã���Ϊ����������ֲ�����ᱻ���٣�

   (3)���⣺���ص��Ƿ�����ֵ��
      �𰸣�����һ���������õĺ����᷵����ֵ������Ķ�������ֵ

   (4)C++11���¹涨���������Է���һ�������Ű�Χ��ֵ���б� ��ʹ�����һ�����б�������һ���ն���

   (5)�������������ָ��:
   1���������ͱ���������һ��ָ�������ָ��
      typedef int arrT[10]   /  using arrT = int[10];
      arrT* func(int i);   ����һ��arrT*ָ�� ָ���������arrT
   
   2��������ʽ Type(*function(parameter_list))[dimension]
      Type��ʾԪ�ص����� dimension��ʾ����Ĵ�С
      ������int(*func(int i))[10]
   
   3��ʹ��β�÷�������           ������(�����򻯺�������ָ��������õ�д��)

      β�÷������͸����β��б�ĺ��沢��һ��->��ͷ 
      Ϊ�˱�ʾ���������ķ������͸����β��б�ĺ��棬�ڱ�Ӧ�÷ŷ������͵ĵط�����һ��auto
      auto func(int i) -> int(*)[10];   ��ʾ�������ص���һ��ָ�� ָ��ָ���СΪ10��int����

   4��ʹ��decltype
      decltype�������������ת����ָ�룬�䷵�صĽ����һ�����飬Ҫ���ʾ���ص���ָ�뻹�����ں�������ʱ��һ��*����

9��������;��������
   
   (1)Ĭ���βΣ�
      ����ƺ�������ʵ�εĺ���ʱ������һ�������Ǻ��������βε�˳�򣬾�����
      ����ôʹ��Ĭ��ֵ���βγ�����ǰ�棬������Щ����ʹ��Ĭ��ֵ���βγ����ں���
   
   (2)��������inline:���Ա��⺯�����õĿ���
      һ�������Ż���ģ��С������ֱ�ӡ�Ƶ�����õĺ���

   (3)����constexpr�����������ڳ������ʽ�ĺ���
      �����ķ������ͼ������βε����Ͷ�����������ֵ����
      
      constexpr int new_sz(){return 42;}
      constexpr int foo = new_sz();  new_sz()���ص���һ���������ʽ ��˿��Ա���ֵ 
   
   (4)assertԤ�����
      assert(expression);
      ��expression��ֵ��������ʽΪ�٣�assert�����Ϣ��ֹͣ����ִ�� ���Ϊ�棬��ʲôҲ����

    __FILE__ ����ļ������ַ�������ֵ
    __LINE__ ��ŵ�ǰ�кŵ���������ֵ
    __TIME__ ����ļ�����ʱ����ַ�������ֵ
    __DATE__ ����ļ��������ڵ��ַ�������ֵ

10������ָ��
    (1)
    ����ָ��ָ����Ǻ��������Ƕ���
    bool lengthCompare(const string& ,const string&);
    
    Ҫ������һ��ָ������ָ�룬ֻ��Ҫ��ָ���滻����������
    bool (*pf)(const string& ,const string&);

    (2)���ʹ�ú���ָ�룿
    pf = lengthCompare;   
    �ص㣺�����ǰѺ�������Ϊһ��ֵʹ��ʱ���ú����Զ���ת��Ϊָ��
    bool b1 = pf("hello","slam");
                                           �����ǵȼ۵�
    pf = &lengthCompare;
    bool b1 = (*pf)("hello","slam");

    (3)������غ���ָ�룿
    void ff(int*);
    void ff(unsigned int);

    void (*pf)(unsigned int) = ff;   pfָ��ff(unsigned int)

    (4)��ν�������Ϊ�β�ʹ�ã�

    ֱ�ӽ�������Ϊʵ��ʹ�ü��ɣ���ʱ�����Զ���ת��Ϊָ��
    IsBigger(s1,s2,lengthCompare);

    (5)��η���ָ������ָ��

       ��򵥰취�������ͱ���
       using pf = int(*)(int,int); pf��ָ������
       pf ff(int,int)�� pf��ָ������ָ�� ff����ָ������ָ��

       �������������ɺ��ԣ�
       int (*ff(int,int))(int,int);
       auto ff(int,int)->int(*)(int,int);
       decltype(ff)* ff(int,int);
   */

/*

p190

#include<iostream>
#include<string>
using namespace std;
string::size_type find_char(const string& s, char c, string::size_type& occurs)
{
    occurs = 0;
    auto ret = s.size();
    for (decltype(ret) i = 0; i != s.size(); ++i)
    {
        if (c == s[i])
        {
            if (ret == s.size())
                ret = i;
            ++occurs;
        }
    }
    return ret;
}
int main()
{   
    string::size_type ctr;
    auto result = find_char("hello,world", 'o', ctr);
    cout << result << endl;
    cout << ctr << endl;
    return 0;
}
*/

/*

p192

#include<iostream>
#include<string>
using namespace std;

void fcn(const int& r)
{   
    cout << r << endl;
}
int main()
{
    int i = 42;
    fcn(i);
    return 0;
}
*/

/*

p196 t6.22 ����ָ���ֵ

#include<iostream>
#include<string>
using namespace std;

void swap(int*& lhs, int*& rhs)
{
    auto temp = lhs;
    lhs = rhs;
    rhs = temp;
}
int main()
{
    int i = 10;
    int j = 20;
    int* lft = &i;
    int* rft = &j;
    swap(lft, rft);
    cout << *lft << " " << *rft << endl;
    return 0;
}
*/

/*

p199 t 6.27

#include<iostream>
#include<string>
using namespace std;

int printsum(initializer_list<int>i1)
{
    int sum = 0;
    for (auto& m : i1)
    {
        sum += m;
    }
    return sum;
}
int main()
{
    int result = printsum({ 1,2,3,4,5,6,7,8,9 });
    cout << result << endl;
    return 0;
}
*/

