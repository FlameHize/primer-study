/*
1�� int& r = i &�������������֣���������͵�һ���֣�r��һ������
	r = & i    &�����ڱ��ʽ�У������һ��ȡ��ַ��

2��externǰ׺ 
   ���ڽ��б�����������ֻ�����������ж��壩
   һ���ļ������ʹ�ñ𴦶�������������������Ǹ����ֵ�����
   ��������ֻ�ܱ�����һ�Σ����ǿ��Ա��������

3��void*ָ��   
   void*��һ�������ָ�����ͣ��������ڴ���������Ͷ���ĵ�ַ

4�����ñ�����һ��������˲��ܶ���һ��ָ�����õ�ָ�룬����ָ���Ƕ������Կ��Զ���һ��ָ�������
					int* p = i;
					int* &r = p;
   Ҫ���r�����͵�����ʲô����Ҫ���������Ķ�r�Ķ��壬�����������ķ��ŶԱ��������;�����ֱ�ӵ�Ӱ�죡������
   ����r��һ�����ã���������������������˵��r������������ʲô������*˵��r���õ���һ��ָ��

5�����ֻ��һ���ļ��ж���const������������������ļ���������ʹ������
   ����취������const�����������������Ƕ��嶼���extern�ؼ��� ����ֻ��Ҫ����һ�ξͿ�����
   extern��ָ���������Ǳ��ļ����У���ֻ��һ�����������Ķ��彫�ڱ𴦳���
   ������ڶ���ļ�֮�乲��const����������ڱ����Ķ���֮ǰ���extern�ؼ���

6��const
   
   ��1����const������ ���Ϊ��������

   ��2������const�����ð󶨵���const���͵����� ��֮����
   
   ��3��ָ������ָ�룺�ײ�const �������ڸı�����ָ�����ֵ������Ҫ����ͨ����ָ��ı�����ֵ����û�й涨�Ǹ������ֵ����ͨ������·���ı䣩
        ����ָ�룺      ����const ָ�뱾��Ϊ���� ������const���Ա�ʾ����Ķ����ǳ�����
       ����ѭ�Ĺ��򣺴��������Ķ���

   ��4��ִ�п�������������ı䱻���������ֵ����ˣ�����Ϳ����Ķ����Ƿ��ǳ�����û��Ӱ��ģ�����const��Ӱ�죩
        ���ǣ��ײ�const�����Ʋ��ܺ��ӣ���ִ�ж���Ŀ�������ʱ������Ϳ����Ķ�����������ͬ�ĵײ�const�ʸ�

    ������ϰ�⣺p58 ��2.30 2.31
        
7��constexpr�������ʽ

    ���壺�������ʽ��ֵָ����ı䲢���ڱ�������о��ܵõ�����ı��ʽ
    Ӧ�ã������Ϊ������һ���������ʽ���ͽ�������Ϊconstexpr����
    C++11�У�����������Ϊconstexpr�����Ա��ɱ���������֤������ֵ�Ƿ���һ���������ʽ
    ����Ϊconstexpr�ı���һ����һ������ ���ұ����ó������ʽ����ʼ��
    constexpr int mf = 20; �������ʽ
    constexpr int limit = mf + 1;�������ʽ
    constexpr int sz = size(); ֻ�е�size()��һ��constexpr����ʱ����һ����ȷ���������
    C++11������һ�������constexpr���������ֺ����㹻�򵥴Ӷ�ʹ�ñ�������оͿ��Եõ�������
    �����Ϳ���ʹ��constexpr��������ʼ��constexpr������
    
    �������⣺ʲô�������㹻�򵥵ĺ��� ---Ӧ����ֻ������ֵ���͵ĺ���
    ����ֵ���ͣ�ָ�롢���á���������   �Զ�������Ͳ���������ֵ����

    constexpr���ε�ָ�����ָ����Ч����ָ����ָ��Ķ����޹�(�����ζ�����Ϊ����const)
    ������    const int* p = nullptr;      p��һ��ָ�����ͳ�����ָ��
              constexpr int* q = nullptr;  q��һ��ָ�������ĳ���ָ��

              constexpr const int* p = &i; p�ǳ���ָ�� ָ�����ͳ���i
              constexpr int* q = &j;       q�ǳ���ָ�� ָ������j
8��ָ�� ���� ���ͱ���
              typedef char *pstring;
              const pstring cstr = 0;  cstr��ָ��const�ĳ���ָ��
              const pstring *ps;       ps��һ��ָ�룬���Ķ�����ָ��char�ĳ���ָ��

              �ص㣺Ҫ�������ط��Ļ�������������const pstring  const�ǶԸ������͵�����
              pstringʵ������ָ��char��ָ�� 
              ���� const pstring��ָ��const�ĳ���ָ�룬������ָ��const������ָ��
9��auto �Զ������ƶ�
    һ�����Զ���const �ָ�����const�Ļ���Ҫ���������͸�Ϊconst auto

10��decltype����ָʾ��
    ���ã�ѡ�񲢷��ز��������������ͣ��ڴ˹����У��������������ʽ������������ͣ�ȴ������ʵ�ʱ��ʽ��ֵ��
    ������decltype(f()) sum  = x; sum�����;��Ǻ���f�ķ�������

    �ص㣺1����������const����������
          
          2��������ʽ�������ǽ����ò�������decltype���õ���������
             decltype(*p)���ص�������int& ������int
          3��decltype(variable))(ע����˫������)���صĽ����Զ�����ã���decltype(variable)�Ľ��
             ֻ�е�variable�������һ������ʱ�ŷ���һ����������
11��Ԥ������ 
    ���ã�ȷ��ͷ�ļ���ΰ���������Ȼ���԰�ȫ����
    #ifndef SALES_DATA_H
    #define SALES_DATA_H
    .......
    #endif

    */

//Sales_data��ʼ����

#include<iostream>
#include<string>
using namespace std;

struct Sales_data
{
    string bookNo;
    unsigned unit_solds = 0;
    double revenue = 0.0;
};

int main()
{
    Sales_data total;
    double totalPrice;
    if (cin >> total.bookNo >> total.unit_solds >> totalPrice)
    {
        total.revenue = total.unit_solds * totalPrice;

        Sales_data trans;
        double transPrice;
        while (cin >> trans.bookNo >> trans.unit_solds >> transPrice)
        {
            trans.revenue = trans.unit_solds * transPrice;

            if (total.bookNo == trans.bookNo)
            {
                total.unit_solds += trans.unit_solds;
                total.revenue += trans.revenue;
            }
            else
            {
                cout << total.bookNo << " " << total.unit_solds << " " << total.revenue << " ";
                if (total.unit_solds != 0)
                    cout << total.revenue / total.unit_solds << endl;
                else
                    cout << " no sales" << endl;

                total.bookNo = trans.bookNo;
                total.unit_solds = trans.unit_solds;
                total.revenue = trans.revenue;
            }
        }
        cout << total.bookNo << " " << total.unit_solds << " " << total.revenue << " ";
        if (total.unit_solds != 0)
            cout << total.revenue / total.unit_solds << endl;
        else
            cout << " no sales" << endl;
        return 0;
    }
    else
    {
        cerr << "no data" << endl;
        return -1;
   
    }
}


