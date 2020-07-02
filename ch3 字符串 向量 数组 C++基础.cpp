/*
1��ͷ�ļ���Ӧ�ð���using���� ��ֹ��������Ҫ��������ͻ

2��string��size�������ص���һ���޷����������� �����Զ��������� string::size_type

3��vector
  (1)��ʼ����
		vector<int>v1(10);   v1��10��Ԫ�� ÿ��ֵ��Ϊ0
		vector<int>v2{10};   v2��1��Ԫ�� ֵΪ10
		vector<int>v3(10,1); v3��10��Ԫ�� ÿ��ֵ��Ϊ1
		vector<int>v4{10,1}; v4��2��Ԫ�� ֵΪ10��1
		����Բ��������������� ���������������б��ʼ��

		����ʹ����������ʼ��vector����
		int ia[] = {1,2,3,4,5};
		vector<int>v(begin(ia),end(ia));  ֻ��Ҫ����Ҫ�������������Ԫ�ص�ַ��βԪ�ص�ַ����
		vector<int>v(ia+1,ia+4); ����������ĵ�2������5��Ԫ�� �ֲ�����

  (2)size_type���ͣ���vector����ֵ������
	 Ҫʹ��size_type���ͣ���Ҫ����ָ���������������Ͷ���� vector������������ǰ�����Ԫ�ص�����
	 ������vector<int>::size_type
  (3)������iterator end��β������� ָ������ĩβԪ�ص���һ��λ��
	 ������������� �õ����ǵ������ľ��� ������difference_type����������������
	 ����������ֻ�м������� û�мӺ����� ���������Ҫע��

4������
	(1)�����Ԫ�ض��Ƕ�����˲��������õ����� ��������Ҳ���ܽ��п���
	
	(2)����������ĸ������� --�Ƽ����������Ķ�
	   Ҫ������������ĺ��壬��õķ����Ǵ���������ֿ�ʼ�������������˳���Ķ�
	   
	   int(*PArray)[10] = &arr;
	   ������Բ�����������Ĳ��֣�*PArray��ζ��PArray��һ��ָ�룬�������۲��ұߣ�
	   ����֪��PArray��ָ��һ����СΪ10�������ָ�룬���۲���ߣ�֪�������Ԫ��������int
	   ���պ��壺PArray��һ��ָ�룬ָ��һ����СΪ10��Ԫ������Ϊint������

	   int(&arrRef)[10] = arr;
	   arrRef��һ�����ã������õĶ�����һ����СΪ10�����飬�����Ԫ��������Int

	   int*(&arry)[10] = ptrs;
	   arry��һ�����ã��۲��ұ߿���֪�����õĶ�����һ����СΪ10�����飬�۲���߿���֪�������
	   ������int ���arry����һ������10��int��ָ������������
	
	(3)�����±�����ͣ�size_t ��������ص��޷������ͣ��ܱ�ʾ�ڴ����������Ĵ�С��

	(4)�����Ĭ�ϳ�ʼ��ֵ��Ϊ0 int[10] a;  a��10��Ԫ�ؾ�Ϊ0

	(5)������ָ��Ĺ�ϵ
	   ���ԣ������� = ָ��������Ԫ�ص�ָ��
	   nums[] = {"hello","slam"};
	   string* p2 = nums;   �ȼ���p2 = &nums[0];

	   �ڴ�����ı��ʽ�У�ʹ���������͵Ķ�����ʵ����ʹ��һ��ָ���������Ԫ�ص�ָ��
	   ע��㣺1����ʹ��auto����������Զ������ƶ�ʱ���ƶϳ�����ָ�����������
	           2����ʹ��decltype���з��������ƶ�ʱ����ת�������ᷢ�������ص�������Ȼ�����������ָ��

	   ����ָ�����㣺ָ����ϻ��߼�ȥĳ��intֵ����Ȼ��һ��ָ��
	   constexpr size_t sz = 5;
	   int arr[sz] = {1,2,3,4,5};
	   int* ip = arr;                   �ȼ���int* ip = &arr[0];
	   int* ip2 = ip + 4;               �ȼ���int* ip2 = &arr[4];
	   
	   int last = *(arr+4)              �����ã��ó�last = arr[4] = 5   Ҳ���ǽ�����������ָ��ʹ��
	   int k = ip[2];                   �ȼ���k = arr[2] = 3            Ҳ���ǽ�ָ�뵱��������ʹ�� 

	   ����ָ�������������ptrdiff_t��׼������ ��һ�ִ���������(�����и�)

	   
	(6)�����еı�׼��begin��end
	   int ia[] = {1,2,3,4,5,6,7,8,9,10};
	   int* beg = begin(ia);
	   int* end = end(ia);
	   ���鲻�������ͣ���˲���ʹ�ó�Ա��������ʽ�����е��ã���ȷ��������ʹ������������Ϊ���ǵĲ���

5����ά����
   
   C++primer:��ð��մ��������˳�����Ķ�

   int arr[3][4];
   �Ķ��������Զ��������������arr,��Ȼarr��һ������3��Ԫ�ص����飬�ٽ��Ź۲��ұ߷��֣�
   arr�����ÿ��Ԫ��Ҳ���Լ���ά�ȣ���Ԫ�ر������ǰ������ĸ�Ԫ�ص����飬�ٹ۲���߷��֣�
   �����洢����СԪ��������
   ��ˣ��ó����ۣ�arr��������һ����СΪ3�����飬�������ÿ��Ԫ�ض��ǰ���4��Ԫ�ص�����

   int (&row)[4] = arr[1];   ��row�����һ������4��int��������ã�Ȼ����󶨵�arr�ĵڶ���

   ���������÷�Χfor���
   for(const auto &row : arr) 
	for(auto col : row)
		cout << col << endl;
   �����ѭ���Ŀ��Ʊ����������������ͣ���ֹ�䷢��auto���Դ������鵽ָ�������ת��
   ���飺Ҫʹ�÷�Χfor��䴦���ά���飬�������ڲ��ѭ���⣬��������ѭ����Ӧ��ʹ����������

   ��ά�����ָ�����
   for(auto p = arr; p != arr + 3;++p)
     for(auto q = *p, q != *p + 4;++q)
		cout << *q << "";
   cout << endl;
   ʹ��auto����������ǰ�����һ��ָ�������� ��Ϊauto���Զ�����������ת��Ϊָ������
   auto p = arr �õ���p��һ��ָ��
   auto q = *p   *p�ǽ����õõ��İ����ĸ�Ԫ�ص����� p��ͨ��autoת��Ϊָ���������Ԫ�ص�ָ��
   q != *p + 4   *p = arr[i] ��Ȼ���Ա�����������һ��ָ�� ����*p + 4Ҳ��һ��ָ��   ��������������ָ��ʹ�ã�
*/

/*
p94 t 3.17

#include<iostream>
#include<string>
#include<vector>

using namespace std;
int main()
{
	vector<string>vec;
	for (string word; cin >> word; vec.push_back(word))
	{
		for (auto str : vec)
			for (auto c : str)
				c = toupper(c);
	}
	for (string::size_type i = 0; i != vec.size(); i++)
	{
		cout << vec[i] <<" ";
	}
	cout << endl;
	return 0;
}

*/

/*
#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main()
{
	int arr[10];
	for (auto i = 0; i < 10; ++i)
		arr[i] = i;
	int arr2[10];
	for (auto i = 0; i < 10; ++i)
		arr2[i] = arr[i];
	vector<int>v1(10);
	for (auto i = 0; i != 10; ++i)
		v1[i] = arr[i];
	vector<int>v2(v1);
	for (auto i : v2)
		cout << i << " ";
	cout << endl;
	return 0;
}
*/

/*
p116 t3.43-t.45

#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main()
{
	int arr[3][4] =
	{
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};

	for (const int(&row)[4] : arr)
		for (int col : row) 
			std::cout << col << " ";
	std::cout << endl;

	for (size_t i = 0; i != 3; ++i)
		for (size_t j = 0; j != 4; ++j)
			std::cout << arr[i][j] << " ";
	std::cout << endl;
	
	for (int(*row)[4] = arr; row != arr + 3; ++row)
		for (int* col = *row; col != *row + 4; ++col)
			std::cout << *col << " ";
	std::cout << endl;

	for (int(*row)[4] = begin(arr); row != std::end(arr); row++)
		for (int* col = begin(*row); col != std::end(*row); col++)
			std::cout << *col << " ";
	std::cout << endl;

	for (auto row = arr; row != arr + 3; row++)
		for (auto col = *row; col != *row + 4; col++)
			std::cout << *col << " ";
	std::cout << endl;
	return 0;

}
*/

