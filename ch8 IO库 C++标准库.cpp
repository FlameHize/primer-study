/*

1��getline��������һ��������istream��ȡһ�����ݣ�����һ��������string������

2��fstream ��д�����ļ�������

3��IO�����޿����͸�ֵ ����IO�����ĺ���ͨ�������÷�ʽ���ݺͷ�����

4��while(cin >> word)
   while���ʽ��������״̬ �����������ɹ�����������Ч״̬��������Ϊ�棬����Ϊ��

5����״̬����
   s.rdstate()  ������s�ĵ�ǰ״̬
   s.setstate() ����s�еĶ�Ӧ����״̬λ��λ
   s.clear()    ����s�е���������״̬λ��λ ������״̬����Ϊ��Ч
   s.eof()      ����s��eofbit��λ(eofbit����ָ�����ﵽ���ļ�����)���򷵻�ture
   s.good()     ����s������Ч״̬ �򷵻�true
   s.bad()      ����s��badbit��λ(badbit����ָ�����Ѿ�����) �򷵻�true
   s.fail()     ����s��badibit����failbit(failbit����ָ��һ��IO����ʧ��)��λ���򷵻�true

6���ļ��������
   
   fstream ��д�����ļ�
   ifstream �������ļ�
   ofstream д�����ļ�

   fstream fs;    ����һ��δ�󶨵��ļ���fs
   fstream fs(s); ����һ��fstream��fs��������Ϊs���ļ�

   ������ifstream input(argv[1]);
         ofstream output(argv[2]);
         Sales_data total;
         if(read(input,total))
         {
            Sales_data trans;
            while(read(input,trans))
            {
                if(total.isbn() == trans.isbn())
                    total.combine(trans);
                else
                {
                    print(output,total) << endl;
                    total = trans;
                }
            }
            print(output,total) << endl;
         }
   ��Ϊfstream��iostream�����࣬�����Ҫʹ��iostream&�ĵط���������fstream�����棨ͨ�������ָ������������

7���ļ�ģʽ
   
   in      �Զ���ʽ��
   out     ��д��ʽ��
   app     ÿ��д����ǰ����λ���ļ���ĩβ
   ate     ���ļ���������λ���ļ���ĩβ
   trunc   �ض��ļ� 
   binary  �Զ����ƽ���IO

   ���������p286

   ע�⣺Ĭ������£������Ǵ�һ��ofstreamʱ���ļ����������ݻᱻ����
         ��ֹһ��ofstream��ո����ļ����ݵķ�����ͬʱָ��appģʽ
         (������ofstram�򿪵��ļ��������ݵ�Ψһ��������ʽָ��app����in)
         ofstram out("filename",ofstram::out | ofstram::app)
   
   ����open�򿪵�����ģʽ������ͽض�
   
8��string��
    
   �����ͷ�ļ�:sstream
   istringstream��string�������� ostringstream��stringд������
   
   ������
   struct PersonInfo
   {
        string name;
        vector<string>phones;
   }
   
   string line,word; //�ֱ𱣴����������һ�к͵���
   vector<PersonInfo>people;
   while(getline(cin,line))
   {
        PersonInfo info;
        istringstream record(line); //����¼�󶨵����������
        record >> info.name;        //��ȡ����
        while(record >> word)       //��ȡ�绰����
            info.phones.push.back(word);
        people.push_back(info);
   }

   string����������p323
   
   substr(pos,n)����һ��string,����s�д�pos��ʼ��n���ַ��Ŀ���
   s.find(args) �����ַ���args ���ص�һ��ƥ��λ�õ��±�
   */


/*

p285 t8.4

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

void ReadFileToVec(const string& filename, vector<string>& vec)
{
    ifstream ifs(filename);
    while (ifs)
    {
        string buf;
        while (getline(ifs, buf))
            vec.push_back(buf);
    }
}

*/