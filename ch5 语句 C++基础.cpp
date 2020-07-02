/*

1��switch���ڲ��Ŀ�����
   ��������case��ǩ֮���ִ�����̷ǳ���Ҫ�����ĳ��case��ǩƥ��ɹ�
   �ʹӸñ�ǩ��ʼ����˳��ִ������case��֧�����ǳ�����ʽ���ж�����һ����
   ����ֱ��switch�Ľ�β���Ż�ͣ�����������Ҫ��ÿ��case��ǩ�����break�ж�

2����ͳfor���
   for(initializer;condition;expression)
        statement
   init-statement�����ʼ��һ��ֵ
   condition��Ϊѭ�����Ƶ����� 
   expression�����޸ĳ�ʼ����ı���
   
   ע��㣺�޸ķ�����ÿ��ѭ��֮�󣡣�����

   �ȼ��ڣ�
   initializer;
   while(condition)
        expression;

3����Χfor���
   for(declaration : expression)
        statement;

   expression:��ʾ����һ�����У�������һ���������������ĳ�ʼֵ�б����顢vector����string�����
   expression�Ĺ�ͬ�ص㣺ӵ���ܷ��ص�������begin��end

   declaration:����һ�������������е�ÿ��Ԫ�ض���ת���ɸñ��������� һ��ʹ��auto���η�����

4����ת���
  (1)break:
   ���ã�������ֹ���������while��do while��switch��for���
   ������Щ���֮��ĵ�һ����俪ʼ����ִ��
  (2)continue:
    ���ã���ֹ�����ѭ���еĵ�ǰ������������ʼ��һ�ε���
5���쳣����(exception)
   try
   {
        .....;
        throw error;  �׳��쳣
   }
   catch(error)
   {
        ....;    �����쳣����
   }
*/

/*

p164 t 5.10

#include<iostream>
#include<string>
using namespace std;
int main()
{
    unsigned int a_cnt = 0, e_cnt = 0, i_cnt = 0, o_cnt = 0, u_cnt = 0;
    char ch;
    while (cin >> ch && ch != '0')
    {
        switch (ch)
        {
        case 'a':
        case 'A':
            a_cnt++;
            break;
        case 'e':
        case 'E':
            e_cnt++;
            break;
        case 'i':
        case 'I':
            i_cnt++;
            break;
        case 'o':
        case 'O':
            o_cnt++;
            break;
        case 'u':
        case 'U':
            u_cnt++;
            break;

        }
    }
    cout << "Number of vowel a(A): \t" << a_cnt << '\n'
        << "Number of vowel e(E): \t" << e_cnt << '\n'
        << "Number of vowel i(I): \t" << i_cnt << '\n'
        << "Number of vowel o(O): \t" << o_cnt << '\n'
        << "Number of vowel u(U): \t" << u_cnt << endl;

    return 0;
}
*/

/*
#include<iostream>
#include<string>
using namespace std;
int main()
{
    pair<string, int>max_count;
    int count = 0;
    for (string str, prestr; cin >> str; prestr = str)
    {
        if (str == prestr)++count;
        else count = 0;
        if (count > max_count.second)max_count = { prestr, count };
    }
    if (max_count.first.empty()) cout << "There's no duplicated string." << endl;
    else cout << "the word " << max_count.first << " occurred " << max_count.second + 1 << " times. " << endl;
    return 0;
}
*/

/*
#include<iostream>
#include<string>
#include<exception>
using namespace std;
int main()
{
    int i, j;
    while (cin >> i >> j)
    {
        cout << "please input two int:" << endl;
        try
        {
            if (j == 0)
                throw runtime_error("division is 0");
            cout << i / j << endl;
        }
        catch(runtime_error err)
        {
            cout << err.what() << "\nTry again? Enter y or n" << endl;
            char c;
            cin >> c;
            if (!cin || c == 'n')
                break;

        }
    }
    return 0;
}
*/