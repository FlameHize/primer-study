/*
1、头文件不应该包含using声明 防止发生不必要的命名冲突

2、string的size函数返回的是一个无符号类型整数 它的自定义类型是 string::size_type

3、vector
  (1)初始化：
		vector<int>v1(10);   v1有10个元素 每个值都为0
		vector<int>v2{10};   v2有1个元素 值为10
		vector<int>v3(10,1); v3有10个元素 每个值都为1
		vector<int>v4{10,1}; v4有2个元素 值为10和1
		区别：圆括号用来构造对象 花括号用来进行列表初始化

		允许使用数组来初始化vector对象
		int ia[] = {1,2,3,4,5};
		vector<int>v(begin(ia),end(ia));  只需要声明要拷贝的数组的首元素地址与尾元素地址即可
		vector<int>v(ia+1,ia+4); 拷贝了数组的第2个到第5个元素 局部拷贝

  (2)size_type类型：是vector返回值的类型
	 要使用size_type类型，需要首先指定它是由哪种类型定义的 vector对象的类型总是包含着元素的类型
	 举例：vector<int>::size_type
  (3)迭代器iterator end是尾后迭代器 指向容器末尾元素的下一个位置
	 两个迭代器相减 得到的是迭代器的距离 类型是difference_type（带符号整型数）
	 迭代器运算只有减号重载 没有加号重载 这个问题需要注意

4、数组
	(1)数组的元素都是对象，因此不存在引用的数组 另外数组也不能进行拷贝
	
	(2)如何理解数组的复杂声明 --推荐从内向外阅读
	   要理解数组声明的含义，最好的方法是从数组的名字开始按照由内向外的顺序阅读
	   
	   int(*PArray)[10] = &arr;
	   首先是圆括号括起来的部分，*PArray意味着PArray是一个指针，接下来观察右边，
	   可以知道PArray是指向一个大小为10的数组的指针，最后观察左边，知道数组的元素类型是int
	   最终含义：PArray是一个指针，指向一个大小为10，元素类型为int的数组

	   int(&arrRef)[10] = arr;
	   arrRef是一个引用，其引用的对象是一个大小为10的数组，数组的元素类型是Int

	   int*(&arry)[10] = ptrs;
	   arry是一个引用，观察右边可以知道引用的对象是一个大小为10的数组，观察左边可以知道数组的
	   类型是int 因此arry就是一个含有10个int型指针的数组的引用
	
	(3)数组下标的类型：size_t （机器相关的无符号类型，能表示内存中任意对象的大小）

	(4)数组的默认初始化值均为0 int[10] a;  a的10个元素均为0

	(5)数组与指针的关系
	   特性：数组名 = 指向数组首元素的指针
	   nums[] = {"hello","slam"};
	   string* p2 = nums;   等价于p2 = &nums[0];

	   在大多数的表达式中，使用数组类型的对象其实就是使用一个指向该数组首元素的指针
	   注意点：1、当使用auto进行数组的自动类型推断时，推断出的是指针而不是数组
	           2、当使用decltype进行返回类型推断时，该转换并不会发生，返回的类型仍然是数组而不是指针

	   数组指针运算：指针加上或者减去某个int值后，仍然是一个指针
	   constexpr size_t sz = 5;
	   int arr[sz] = {1,2,3,4,5};
	   int* ip = arr;                   等价于int* ip = &arr[0];
	   int* ip2 = ip + 4;               等价于int* ip2 = &arr[4];
	   
	   int last = *(arr+4)              解引用，得出last = arr[4] = 5   也就是将数组名当成指针使用
	   int k = ip[2];                   等价于k = arr[2] = 3            也就是将指针当成数组名使用 

	   两个指针相减的类型是ptrdiff_t标准库类型 是一种带符号类型(有正有负)

	   
	(6)数组中的标准库begin和end
	   int ia[] = {1,2,3,4,5,6,7,8,9,10};
	   int* beg = begin(ia);
	   int* end = end(ia);
	   数组不是类类型，因此不能使用成员函数的形式来进行调用，正确的做法是使用素数组名作为他们的参数

5、多维数组
   
   C++primer:最好按照从内向外的顺序来阅读

   int arr[3][4];
   阅读：我们自定义的数组名字是arr,显然arr是一个包含3个元素的数组，再接着观察右边发现，
   arr数组的每个元素也有自己的维度，其元素本身又是包含了四个元素的数组，再观察左边发现，
   真正存储的最小元素是整数
   因此，得出结论：arr它定义了一个大小为3的数组，该数组的每个元素都是包含4个元素的数组

   int (&row)[4] = arr[1];   将row定义成一个含有4个int数组的引用，然后将其绑定到arr的第二行

   遍历：利用范围for语句
   for(const auto &row : arr) 
	for(auto col : row)
		cout << col << endl;
   将外层循环的控制变量声明成引用类型，防止其发生auto中自带的数组到指针的类型转换
   建议：要使用范围for语句处理多维数组，除了最内层的循环外，其余所有循环都应该使用引用类型

   多维数组的指针调用
   for(auto p = arr; p != arr + 3;++p)
     for(auto q = *p, q != *p + 4;++q)
		cout << *q << "";
   cout << endl;
   使用auto避免在数组前面加入一个指针类型了 因为auto会自动将数组类型转换为指针类型
   auto p = arr 得到的p是一个指针
   auto q = *p   *p是解引用得到的包含四个元素的数组 p是通过auto转换为指向该数组首元素的指针
   q != *p + 4   *p = arr[i] 仍然可以被编译器理解成一个指针 所以*p + 4也是一个指针   （将数组名当成指针使用）
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

