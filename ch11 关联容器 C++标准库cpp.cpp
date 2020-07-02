/*
1、关联容器 set和map 元素按照关键字来保存和访问（有序容器，容器按照字典序进行排列）
   set：每个元素只包含一个关键字 支持高效的关键字查询操作
   map：每个元素包含一个关键字-值对 pair (key-value) 利用关键字来查询对应的值
   multimap:关键字可以重复出现的map
   multiset:关键字可以重复出现的set

   经典例子：单词计数程序
   map<string,size_t>word_count;
   string word;
   while(cin>>word)
       ++word_count[word]; 

   //如果word还未在map中，下标运算符会创建一个新元素，其关键
   //字为word，值为0，不管元素是否是新创建的，将其值加1

   for(const auto &w : word_count)
       cout << w.first << "occurs" << w.second << "times" <<endl;
  
2、初始化map和set
   初始化set: 只提供关键字类型即可 set<int>a = {1,2,3,4,5}; 
   
   初始化map:必须提供关键字类型和值类型 {key,value}；

3、使用关键字类型的比较函数
   
   原因：为了指定使用自定义的操作，必须在定义关联容器类型时提供此操作的类型
   方法：用尖括号指出要定义哪种类型的容器，自定义的操作类型必须在尖括号中紧跟着元素的类型给出
    
   举例：我们不能直接定义一个Sales_data的set 因此它没有自定义<运算符
   但是可以用一个compareIsbn函数来定义一个set

   bool compareIsbn(const Sales_data& lhs,const Sales_data& rhs)
   {
        return lhs.isbn() < rhs.isbn();
   }
   set<Sales_data,decltype(compareIsbn)*>bookStore(compareIsbn);   //使用函数的名字时，在需要的情况下它会自动的转化为一个指针
   定义此容器对象时，需要提供想要使用的操作的指针
   用compareIsbn来初始化bookStore对象，这表示当我们向bookStore添加元素时，
   通过调用compareIsbn来为这些元素排序(即bookStore中的元素将按它们的ISBN成员的值排序)

   泛化：
   实际上，任意类型都可以作为标准库set/multiset中的关键字类型
   但是如果要用自定义类型的话，需要额外提供能够比较这种类型的比较函数，也就是实现 < 操作
   这样就可以实现在set容器中利用自己定义类中元素以及排序规则对自定义类进行排序
  
4、pair
   头文件：utility
   一个pair保存两个数据成员，类似容器，pair是一个用来生成特定类型的模板
   pair的数据成员是public的，两个成员分别命名为first和second

   操作:make_pair(v1,v2) 返回一个用v1和v2来初始化的pair，pair的类型从v1和v2的类型推断出来

5、关联容器的类型别名与操作
   
   别名：

   key_type    此容器类型的关键字类型
   mapped_type 每个关键字关联的类型：只适用于map
   
   value_type  对于set，与key_type相同
               对于map，为pair<const key_type,mapped_type>（关键字的值不能改变）  
   
   当解引用一个关联容器迭代器时，我们会得到一个类型为容器的value_type的值的引用
   对于map而言，value_type是一个pair类型，其first成员保存const的关键字，second成员保存值
   
   对于set而言，迭代器时const的，关键字不能改变
   
   插入元素：

   向map中插入元素：
   word_count.insert(make_pair(word,1));
   map的insert的返回值：一个pair，告诉我们插入是否成功
   返回的pair的first成员是一个map的迭代器，指向具有给定关键字的元素（一个键值对）
   返回的pair的second成员是一个bool值，指出元素是插入成功还是已经存在于容器中
   
   multimap的insert返回值：返回一个指向新元素键值对的迭代器 无bool值
   具体insert操作 见p384

   删除元素：

   c.erase(k)  从c中删除每个关键字为k的元素 返回一个size_type值，指出删除的元素数量
   c.erase(p)  从c中删除迭代器p指定的元素 返回一个指向p之后元素的迭代器
   c.erase(b,e)删除迭代器对b和e所表示的范围中的元素 返回e

   下标操作：
   map下标运算符接受一个索引（即一个关键字），获取与此关键字相关联的值
   如果关键字不在map中，会为它创建一个元素并插入到map中，并且关键字将进行值初始化
   （基于这一点，一般在map中使用find代替下标操作）

   当对一个map进行下标操作时，会获得一个mapped_type对象
   当解引用一个map迭代器时，会获得一个value_type对象

   访问操作：
   c.find(k)  返回一个迭代器，指向第一个关键字为k的元素，若k不在容器中，则返回尾后迭代器
   c.count(k) 返回关键字等于k的元素的数量，对于不允许重复关键字的容器，返回值永远是0或者1
   */


/*

p378 t11.7  map容器的写法1.0

#include<string>
#include<iostream>
#include<map>
#include<vector>
using namespace std;

using Families = map<string,vector<string>>;

auto make_families()
{
    Families families;
    for (string ln; cout << "last name = "; cin >> ln && ln != "@q")
        for (string cn; cout << "children's name = "; cin >> cn && cn != "@q")
            families[ln].push_back(cn);
    return families;
}

auto print(Families const& families)
{
    for (auto const& family : families)
    {
        cout << family.first << ":\n";
        for (auto const& child : family.second)
            cout << child << " ";
        cout << "\n";
    }
}
int main()
{
    print(make_families());
    return 0;
}

*/


/*

p381 t11.14 map的写法2.0

#include<string>
#include<iostream>
#include<map>
#include<vector>
using namespace std;

class Families
{
public:
    using Child    = pair<string, string>;
    using Children = vector<Child>;
    using Data     = map<string, Children>;
    //写成容器包含类
    auto add(string const& last_name, string const& first_name, string birthday)
    {
        auto child = make_pair(first_name, birthday);
        _data[last_name].push_back(child);
    }
    auto print()const
    {
        for (auto const& pair : _data)
        {
            cout << pair.first << ":\n";
            for (auto const& child : pair.second)
                cout << child.first << " " << child.second << endl;
            cout << endl;
        }
    }
private:
    Data _data;
};

int main()
{
    Families families;
    auto msg = "Please enter last name, first name and birthday:\n";
    for (string l, f, b; cout << msg, cin >> l >> f >> b; families.add(l, f, b));
    families.print();

    return 0;
}
*/


/*

p394 t11.33 文本转换程序  经典案例

#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

//文件内的文本转换整理成一个map容器
map<string, string>buildMap(ifstream& map_file)
{
    map<string, string>trans_map;
    for (string key, value; map_file >> key && getline(map_file, value);)
        if (value.size() > 1) trans_map[key] = value.substr(1);
    return trans_map;
}

const string& transform(const string& s, const map<string, string>& m)
{
    auto map_it = m.find(s); //返回一个map的迭代器
    return map_it == m.cend() ? s : map_it->second;
}

void word_transfor(ifstream& map, ifstream& input)
{
    auto trans_map = buildMap(map);
    //trans_map为将文本转换过来的map容器
    for (string text; getline(input, text);)
    {
        //将输入的文字放入text中
        istringstream iss(text);//iss从读text数据
        for (string word; iss >> word;) //将读到的text数据放入word中
            cout << transform(word, trans_map) << " ";
        cout << endl;
    }
}
*/