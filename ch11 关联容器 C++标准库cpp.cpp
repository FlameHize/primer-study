/*
1���������� set��map Ԫ�ذ��չؼ���������ͷ��ʣ��������������������ֵ���������У�
   set��ÿ��Ԫ��ֻ����һ���ؼ��� ֧�ָ�Ч�Ĺؼ��ֲ�ѯ����
   map��ÿ��Ԫ�ذ���һ���ؼ���-ֵ�� pair (key-value) ���ùؼ�������ѯ��Ӧ��ֵ
   multimap:�ؼ��ֿ����ظ����ֵ�map
   multiset:�ؼ��ֿ����ظ����ֵ�set

   �������ӣ����ʼ�������
   map<string,size_t>word_count;
   string word;
   while(cin>>word)
       ++word_count[word]; 

   //���word��δ��map�У��±�������ᴴ��һ����Ԫ�أ���ؼ�
   //��Ϊword��ֵΪ0������Ԫ���Ƿ����´����ģ�����ֵ��1

   for(const auto &w : word_count)
       cout << w.first << "occurs" << w.second << "times" <<endl;
  
2����ʼ��map��set
   ��ʼ��set: ֻ�ṩ�ؼ������ͼ��� set<int>a = {1,2,3,4,5}; 
   
   ��ʼ��map:�����ṩ�ؼ������ͺ�ֵ���� {key,value}��

3��ʹ�ùؼ������͵ıȽϺ���
   
   ԭ��Ϊ��ָ��ʹ���Զ���Ĳ����������ڶ��������������ʱ�ṩ�˲���������
   �������ü�����ָ��Ҫ�����������͵��������Զ���Ĳ������ͱ����ڼ������н�����Ԫ�ص����͸���
    
   ���������ǲ���ֱ�Ӷ���һ��Sales_data��set �����û���Զ���<�����
   ���ǿ�����һ��compareIsbn����������һ��set

   bool compareIsbn(const Sales_data& lhs,const Sales_data& rhs)
   {
        return lhs.isbn() < rhs.isbn();
   }
   set<Sales_data,decltype(compareIsbn)*>bookStore(compareIsbn);   //ʹ�ú���������ʱ������Ҫ������������Զ���ת��Ϊһ��ָ��
   �������������ʱ����Ҫ�ṩ��Ҫʹ�õĲ�����ָ��
   ��compareIsbn����ʼ��bookStore�������ʾ��������bookStore���Ԫ��ʱ��
   ͨ������compareIsbn��Ϊ��ЩԪ������(��bookStore�е�Ԫ�ؽ������ǵ�ISBN��Ա��ֵ����)

   ������
   ʵ���ϣ��������Ͷ�������Ϊ��׼��set/multiset�еĹؼ�������
   �������Ҫ���Զ������͵Ļ�����Ҫ�����ṩ�ܹ��Ƚ��������͵ıȽϺ�����Ҳ����ʵ�� < ����
   �����Ϳ���ʵ����set�����������Լ���������Ԫ���Լ����������Զ������������
  
4��pair
   ͷ�ļ���utility
   һ��pair�����������ݳ�Ա������������pair��һ�����������ض����͵�ģ��
   pair�����ݳ�Ա��public�ģ�������Ա�ֱ�����Ϊfirst��second

   ����:make_pair(v1,v2) ����һ����v1��v2����ʼ����pair��pair�����ʹ�v1��v2�������ƶϳ���

5���������������ͱ��������
   
   ������

   key_type    ���������͵Ĺؼ�������
   mapped_type ÿ���ؼ��ֹ��������ͣ�ֻ������map
   
   value_type  ����set����key_type��ͬ
               ����map��Ϊpair<const key_type,mapped_type>���ؼ��ֵ�ֵ���ܸı䣩  
   
   ��������һ����������������ʱ�����ǻ�õ�һ������Ϊ������value_type��ֵ������
   ����map���ԣ�value_type��һ��pair���ͣ���first��Ա����const�Ĺؼ��֣�second��Ա����ֵ
   
   ����set���ԣ�������ʱconst�ģ��ؼ��ֲ��ܸı�
   
   ����Ԫ�أ�

   ��map�в���Ԫ�أ�
   word_count.insert(make_pair(word,1));
   map��insert�ķ���ֵ��һ��pair���������ǲ����Ƿ�ɹ�
   ���ص�pair��first��Ա��һ��map�ĵ�������ָ����и����ؼ��ֵ�Ԫ�أ�һ����ֵ�ԣ�
   ���ص�pair��second��Ա��һ��boolֵ��ָ��Ԫ���ǲ���ɹ������Ѿ�������������
   
   multimap��insert����ֵ������һ��ָ����Ԫ�ؼ�ֵ�Եĵ����� ��boolֵ
   ����insert���� ��p384

   ɾ��Ԫ�أ�

   c.erase(k)  ��c��ɾ��ÿ���ؼ���Ϊk��Ԫ�� ����һ��size_typeֵ��ָ��ɾ����Ԫ������
   c.erase(p)  ��c��ɾ��������pָ����Ԫ�� ����һ��ָ��p֮��Ԫ�صĵ�����
   c.erase(b,e)ɾ����������b��e����ʾ�ķ�Χ�е�Ԫ�� ����e

   �±������
   map�±����������һ����������һ���ؼ��֣�����ȡ��˹ؼ����������ֵ
   ����ؼ��ֲ���map�У���Ϊ������һ��Ԫ�ز����뵽map�У����ҹؼ��ֽ�����ֵ��ʼ��
   ��������һ�㣬һ����map��ʹ��find�����±������

   ����һ��map�����±����ʱ������һ��mapped_type����
   ��������һ��map������ʱ������һ��value_type����

   ���ʲ�����
   c.find(k)  ����һ����������ָ���һ���ؼ���Ϊk��Ԫ�أ���k���������У��򷵻�β�������
   c.count(k) ���عؼ��ֵ���k��Ԫ�ص����������ڲ������ظ��ؼ��ֵ�����������ֵ��Զ��0����1
   */


/*

p378 t11.7  map������д��1.0

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

p381 t11.14 map��д��2.0

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
    //д������������
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

p394 t11.33 �ı�ת������  ���䰸��

#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

//�ļ��ڵ��ı�ת�������һ��map����
map<string, string>buildMap(ifstream& map_file)
{
    map<string, string>trans_map;
    for (string key, value; map_file >> key && getline(map_file, value);)
        if (value.size() > 1) trans_map[key] = value.substr(1);
    return trans_map;
}

const string& transform(const string& s, const map<string, string>& m)
{
    auto map_it = m.find(s); //����һ��map�ĵ�����
    return map_it == m.cend() ? s : map_it->second;
}

void word_transfor(ifstream& map, ifstream& input)
{
    auto trans_map = buildMap(map);
    //trans_mapΪ���ı�ת��������map����
    for (string text; getline(input, text);)
    {
        //����������ַ���text��
        istringstream iss(text);//iss�Ӷ�text����
        for (string word; iss >> word;) //��������text���ݷ���word��
            cout << transform(word, trans_map) << " ";
        cout << endl;
    }
}
*/