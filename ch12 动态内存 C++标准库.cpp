


//�ܣ�����ָ�������Ƕ�̬�ڴ棬�뾲̬�ڴ��Լ�ջ�ڴ��޹�
//    new��ʼ������ָ���Լ�make_shared�������Ƿ���Ķ�̬�ڴ�
//    �����Զ����ָ�����ͣ��ڽ���󶨵�����ָ����ʱ�������ṩɾ����deleter
//    (���԰󶨵�ǰ�������ָ�����ָ��̬�ڴ���ָ���������ͬ)
//
//
//1����̬�ڴ���ջ�ڴ� 
//
//   ȫ�ֶ����ڳ�������ʱ���䣬�ڳ������ʱ���١�
//   �ֲ��Զ����󣬵����ǽ����䶨�����ڵĳ����ʱ�����������뿪��ʱ����
//   �ֲ�static�����ڵ�һ��ʹ��ǰ���䣬�ڳ������ʱ����
//
//   ��̬�ڴ棺����ֲ�static������static���ݳ�Ա�Լ��������κκ���֮��ı�����ȫ�ֱ�����
//   ջ�ڴ棺���涨���ں����ڵķ�static����
//   �����ھ�̬�ڴ��ջ�ڴ��еĶ����ɱ������Զ�����������
//
//2���ڴ��
//
//   ���˾�̬�ڴ��ջ�ڴ棬ÿ������ӵ��һ���ڴ�أ��ѣ��������ö������ж�̬����
//   ��̬�ڴ棺��ʽ��������ʽ����
//   Ϊʲôʹ������ ->  ������Ҫ�ڶ������乲������/����֪���Լ���Ҫʹ�ö��ٶ���/����֪����������׼ȷ����
//                  ->   ����ָ������ṩ�Զ�̬������ڴ氲ȫ���ַ���Ĺ���
//
//
//   �ڴ�ذ�����������ָ�룺shared_ptr��unique_ptr
//   �����ͷ�ļ���memory
//
//   ��λnew���ʽ��
//   int* p = new (nothrow) int; �������ʧ�ܣ���Ҫ�׳��쳣������һ����ָ�뼴��
//
//   new-delete��ԭʼ�Ķ�̬���䷽ʽ
//               Ĭ�ϳ�ʼ����int* p = new int;   *p��ֵδ����
//               ֵ��ʼ��    int* p = new int(); *p��Ϊ0
//                           int* p = new int(5); *p��Ϊ5
//   new-delete�ĳ���ָ���ȱ��:
//   
//   void use_factory(T arg)
//   {
//        Foo* p = new Foo(arg);
//        //ʹ��p����delete��
//   } //p�뿪�����������򣬵�����ָ����ڴ�û�б��ͷ�
//   ����������У�һ��use_factory�����أ������û�а취�ͷ�����ڴ���
//   ��������������߼�����������������ȷ��������use_factory�мǵ��ͷ��ڴ�delete
//
//   ��֮���
//   shared_ptr use_factory(T arg)
//   {
//        shared_ptr<Foo>p = make_shared<Foo>(arg);
//        return p;  //�����Ƿ���pʱ�����ü��������˵�������
//   }p�뿪�������򣬵�������ָ����ڴ治�ᱻ�ͷŵ�
//   ���������ָ��汾�У�use_factory�е�return�����˺����ĵ����߷���һ��p�Ŀ���
//   ����һ��shard_ptr�������������������ü���ֵ���ص㣺���ü���ֵ���ڹ���������϶�����ָ�뱾�壩
//   ���ڣ���p������ʱ������ָ��Ķ�����������ʹ����(�ص㣺pָ���ǻᱻ���٣�������Ϊ���ü������ƣ���ָ����ڴ�û�б�����)
//   ����һ���ڴ棬shared_ptr�ౣֻ֤Ҫ���κ�shared_ptr����ʹ���������Ͳ��ᱻ�ͷŵ�
//
//
//   ΪʲôҪʹ������ָ���������ʹ��new-delete��
//   �𰸣�
//   delete:����ָ������ͷŶ�Ӧ�ڴ�
//   shared_ptr���ü���Ϊ0������ָ������ͷŶ�Ӧ�ڴ�
//  ��������ü�������Ϊ0 ��ʹ������ָ����󣬵���Ҳ�����ͷ��ڴ棬�Ӷ�����ʵ�����ݹ���
//
//   ���飺1�����ֻʹ������ָ��
//         2����Ҫ���ʹ����ָͨ��������ָ��
//         3����Ҫʹ��get��ʼ����һ������ָ�����Ϊ����ָ�븳ֵ
//
//3��shared_ptr
//   shared_ptr<T> sp;    ������ָ�룬ָ������ΪT�Ķ���
//   mske_shared<T>(args);����һ��shared_ptr��ָ��һ�� ��̬���� ������ΪT�Ķ���ʹ��args��ʼ���˶���
//   shared_ptr<T>p(q);   p��shared_ptr q�Ŀ������˲��������q�ļ�������q��ָ�������ת��ΪT*
//   p = q;               p��q����shared_ptr���������ָ��������໥ת��
//                        �˲����ݼ�p�����ü���������q�����ü���(��p�����ü�����Ϊ0����������ԭ�ڴ��ͷ�)
//   p.use_count()        ������p������������ָ������
//   p.unique()           ��p.use_count()Ϊ1 ����true ���򷵻�false
//   p.reset()            ��p��Ψһָ��������shared_ptr��reset���ͷŴ˶��� �������˿�ѡ�Ĳ�������ָ��q ����pָ��q
//
//
//   shared_ptr<T>p(q);   p��������ָ��q��ָ��Ķ���q����ָ��new������ڴ棬���ܹ�ת��ΪT*����
//   shared_ptr<T>p(q,d); p��������ָ��q��ָ��Ķ���q����ָ��new������ڴ棬���ܹ�ת��ΪT*����
//                        ����p��ʹ�ÿɵ��ö���d������delete
//
//   
//   (1)������
//   
//      ���飺�ȫ�ķ����ʹ�ö�̬�ڴ�ķ����ǵ���make_shared����
//      
//      make_shared�������ڶ�̬�ڴ��з���һ�����󲢳�ʼ����������ָ��˶����shared_ptr
//      
//      ������
//      shared_ptr<int> p = make_shared<int>(42);
//      auto p = make_shared<int>(42);
//
//      ��������new���ص�ָ������ʽ�ĳ�ʼ������ָ��
//      shared_ptr<int>p(new int(42));
//   
//   (2)������ֵ�� ͨ���򵥵Ķ�����ָ��Ŀ������߸�ֵ�Ϳ���ʵ�ֶ���ָ�������ͬ�Ķ��� 
//                   ���Ҵ������ü�������(��ֹ����ָ��ķ���) ����Ϊ��������ָ����ڵ�����
//                   (������ָ�����ͨ�����ü������Ƽ�¼�ж��ٸ�shared_ptrָ����ͬ�Ķ�����˿�����ǡ����ʱ���Զ��ͷŶ���)
//      
//      ÿ��shared_ptr����һ�������ļ�����������Ϊ���ü���
//      
//      ������ü���ֵ�ǰ󶨵�shared_ptr��ָ��Ĺ���������ϵ�
//     
//     ���������������
//      ����һ��shared_ptr 
//      �����shared_ptr��ʼ����һ��shared_ptr
//      �����shared_ptr��Ϊ�������ݸ�һ������
//      ��shared_ptr��Ϊһ�������ķ���ֵ(���ص�ֵ������ָ��Ŀ����������ᴥ�����õ�������)
//
//      �������ݼ������
//      ��shared_ptr����һ����ֵ
//      shared_ptr������
//
//      һ��һ��shared_ptr�ļ�������Ϊ0�����ͻ��Զ��ͷ��Լ�������Ķ���
//      ������ָ�� �ͷ��ڴ棩
//
//   (3)����ָ�밸�����
//      Blob    �ں���ָͨ�� ָ��vector  vector<string>* ptr;
//      StrBlob �ں�����ָ�� ָ��vector  shared_ptr<vector<string>> Sptr;
//
//      Blob<string> b1; //��Blob
//      {
//            Blob<string>b2 = {"a","an","the"};
//            b1 = b2; //b1��b2������ͬ��Ԫ�� (vectorָ��ptrǳ����)
//      }  //b2�뿪�������������ˣ���ʱb2�е�ptrָ���vector�е�Ԫ�ر�������
//      //���b1ָ���Ԫ��Ҳͬ���������� 
//      (�ٶ�ptrʹ��new�����䶯̬�ڴ� ���뿪���������Ȼp���ᱻ���٣���������Ҳ���ɵ��ã��γ��ڴ�й©/�����ظ��ͷ��ڴ� �����ܶ�����)
//
//      StrBlob b1;
//      {
//            StrBlob b2 = {"a","an","the"};
//            b1 = b2;  
//            //�������ü������ƣ�b1��ָ���ԭ�������������Ϊ0�����٣���ʱb1ָ����¶�����b2�б����vector
//            //ͨ������ʵ��������ָ������ݹ�����ʱb1��b2ָ�����ͬһ��vector��b2�����ô���Ϊ2
//            b2.push_back("about");
//            //��ʱb2�����Ĺ����vector������4��Ԫ��,����b1��4��Ԫ��
//            //b2ָ�뱻�Զ����٣�������ָ��Ķ�̬�ڴ�ռ�������������ٺ�Ϊ1(ע�����ڴ�������������Ҳ����ԭb2ָ��ָ��Ķ����������) 
//            //                  ��˲��ᱻ�Զ��ͷ�
//      }
//
//   (4)����ָ������
//      
//      Ĭ������£�һ��������ʼ������ָ�����ͨ����ָ�����ָ��̬�ڴ�(Ҳ����new��ʼ��)
//     ����ѡ����ָͨ���ʼ������ָ����ѡ��ʹ��make_shared������make_shared����ͬ�����䶯̬�ڴ棬�����ȫ�ģ�
//      ��Ϊ����ָ��Ĭ��ʹ��delete���ͷ�����ָ��Ķ���
//      ����Ҳ���Խ�һ������ָ��󶨵�һ��ָ���������͵���Դ��ָ����(�����Զ���������������int��)���ص��������Զ����࣬�붯̬�ڴ��޹أ�
//      ����Ϊ�������������Ǳ����ṩ�Լ��Ĳ���������delete    -> ���������ָ������
//
//      �﷨��shared_ptr<T>p(q,d); p��������ָ��q��ָ��Ķ���q����ָ��new������ڴ�(q��һ��ָ��)�����ܹ�ת��ΪT*����
//                                 ����p��ʹ�ÿɵ��ö���d������delete
//      ���䰸����
//      struct connection
//      {
//        string ip;
//        int port;
//        connection(string ip_,int port_):ip(ip_),port(port_){}
//      };
//
//      struct destination
//      {
//        string ip;
//        int port;
//        destination(string ip_, int port_):ip(ip_), port(port_){}
//      };
//
//      connection connect(destination* pDest) //��������
//      {
//        shared_ptr<connection>pConn(new connection(pDest->ip, pDest->port));
//
//        //shared_ptr<connection>pConn = make_shared<connection>(pDest->ip, pDest->port);
//        //���߾�Ϊ��̬������ڴ�
//        cout << "creating connection(" << pConn.use_count() << ")" << endl;
//        return *pConn;
//      }
//
//      void disconnect(connection pConn)  //�ر�����
//      {
//        cout << "connection close(" << pConn.ip << ":" << pConn.port << ")" << endl;
//      }
//
//      void end_connection(connection* pConn) //�Զ���ɾ����
//      {
//        disconnect(*pConn);
//      }
//
//      void f(destination& d)
//      {
//        connection conn = connect(&d);
//        shared_ptr<connection>p(&conn, end_connection);//���ﴫ����Ǻ�����ָ��
//        cout << "connection now(" << p.use_count() << ")" << endl;
//      }
//
//      int main()
//      {
//        destination dest("202.118.176.67", 3316);
//        f(dest);
//      }
//
//4��unique_ptr
//   
//   һ��unique_ptrӵ������ָ��Ķ��� ĳ��ʱ��ֻ����һ��unique_ptrָ��һ����������
//   ��unique_ptr������ʱ������ָ��Ķ���Ҳ������
//   
//   (1)������
//       
//      �����Ƕ���һ��unique_ptrʱ����Ҫ����󶨵�һ��new���ص�ָ���ϣ��ұ������ֱ�ӳ�ʼ����ʽ
//      unique_ptr<int>p(new int(42));
//
//   (2)������ֵ��
//    
//      unique_ptr��֧�ֳ��濽���븳ֵ
//
//      ����֧������Ȩת��
//      unique_ptr<string>p2(p1.release()); ������Ȩ��p1ת�Ƹ�p2����p1����Ϊ��
//     
//      unique_ptr<string>p3(new string("hello"));
//      p2.reset(p3.release());   ������Ȩ��p3ת�Ƹ�p2 �����ͷ�p2ԭ��ָ����ڴ�
//
//     ���Կ���һ����Ҫ�����ٵ�unique_ptr ����Ӻ����з���һ��unique_ptr
//
//
//
//
//   (3)���������
//
//      unique_ptr<T>u1;    ��unique_ptr��ָ������ΪT�Ķ���ʹ��delete���ͷ�����ָ��
//      unique_ptr<T,D>u2;  ��unique_ptr��u2ʹ��һ������ΪD�Ŀɵ��ö������ͷ�����ָ��
//      unique_ptr<T,D>u(d);��unique_ptr��ָ������ΪT�Ķ���������ΪD�Ķ���d������delete
//
//      u.release();        u������ָ��Ŀ���Ȩ(�ж�unique_ptr����������Ķ������ϵ)�����ص�ǰ�����ָ�룬����u��Ϊ��
//                          ���ص�ָ��ͨ����������ʼ����һ������ָ������һ������ָ�븳ֵ
//      u.reset();          �ͷ�uָ��Ķ���
//      u.reset(q);         ����ṩ������ָ��q����uָ���������(���ͷ�ԭ��ָ����ڴ�)��������Ϊ��
//
//      unique_ptr<T[]>u;   uָ��һ����̬��������飬����Ԫ������ΪT
//      unique_ptr<T[]>u(p);uָ������ָ��p��ָ��Ķ�̬��������飬p�����ܹ�ת��Ϊ����T*
//      u[i]                ����uӵ�е�������λ��i���Ķ���
//
//  (4)ɾ��
//   
//     ��shared_ptr��ͬ�������ڼ������ڱ���ɾ�����Ķ�������
//    
//     unique_ptr<objT,delT>p(new objT,fcn);
//     pָ��һ������ΪobjT�Ķ��󣬲�ʹ��һ������ΪdelT�Ķ������ͷ�objT����
//     �������һ����Ϊfcn��delT���Ͷ�����ִ��ɾ������
//
//     ��дshared_ptr�е�ɾ���� Ӧ��д��������ʽ
//
//    unique_ptr<connection,decltype(end_connection)*>p(&c,end_connection);
//    decltype<end_connection>*��һ������ָ�����ͣ���end_connection��ͬ(�������ȼ��ں���ָ��)
//    (ͬʱ����ָ�����һ���ɵ��ö���)
//
//5����̬����
//   
//   �����Ӧ��Ӧ��ʹ�ñ�׼�����������Ƕ�̬��������飬ʹ��������Ϊ�򵥡��������׳����ڴ����������и��õ�����
//  
//   �﷨��int* p = new int[42]; pָ��һ��������42��int������
//         ����һ������������õ�����һ��Ԫ�����͵�ָ�루��̬���鲻��һ�����飩
//   ֵ��ʼ����
//         int* p = new int[10];  10��δ��ʼ����int
//         int* p = new int[10]();10��ֵ��ʼ��Ϊ0��int
//         int* p = new int[10]{1,2,3,4,5,6,7,8,9,10}; ����Ԫ��
//   �ͷŶ�̬���飺delete[] p;
//
//6������ָ��Ͷ�̬����
//
//   unique_ptr<int[]>up(new int[10]);  upָ��һ������10��δ��ʼ��int������
//   up.release(); �Զ�ʹ��delete[]��������ָ��
//
//   shared_ptr<int>sp(new int[10],[](int* p){ delete[] p;};
//   shared_ptr��ֱ��֧�ֹ���̬���飬���Ҫʹ�ã��ͱ����ṩ�Լ������ɾ����
//
//7��allocator��
//
//   ����ͷ�ļ�:memory
//   ���ã��������ǽ��ڴ����Ͷ�������뿪,������ڴ���ԭʼ��δ�����
//   (new�����һ����ڴ潫�ڴ�ķ���Ͷ���Ĺ����������һ�𣬻ᵼ�²���Ҫ���˷ѣ�����û��Ĭ�Ϲ��캯������Ͳ��ܽ��ж�̬��������)
//
//   ��׼������
//   
//   allocator<T>a;      ����һ����Ϊa��allocator����Ϊ����ΪT�Ķ�������ڴ�
//   a.allocate(n);      ����һ��ԭʼ�ġ�δ������ڴ棬����n������ΪT�Ķ���
//
//   a.deallocate(p,n);  �ͷŴ�T*ָ��p�е�ַ��ʼ���ڴ棬����ڴ汣����n������ΪT�Ķ���
//                       p������һ����ǰ��allocate���ص�ָ����n������p����ʱ��Ҫ��Ĵ�С
//                       �ڵ���deallocate֮ǰ���û������ÿ��������ڴ��д����Ķ������destroy
//
//   a.construct(p,args);p������һ������ΪT*��ָ�룬ָ��һ��ԭʼ�ڴ棬
//                       args�����ݸ�����ΪT�Ĺ��캯����������pָ����ڴ��й���һ������
//   a.destroy(p);       pΪT*���͵�ָ�룬���㷨��pָ��Ķ���ִ����������
//
//   ������
//    
//   allocator<string>alloc;           ���Է���string��allocator����
//   auto const p = alloc.allocate(n); ����n��δ��ʼ����string
//   auto q = p;                       qָ��������Ԫ��֮���λ�ã�qָ��������Ԫ��֮���λ�ã�
//   alloc.construct(q++);             *qΪ���ַ���
//   alloc.construct(q++,10,'c');      *qΪcccccccccc
//   alloc.construct(q++,"hi");        *qΪhi
//   while(q != p)
//    alloc.destroy(--q);              ���ٹ����Ԫ�� ��һ�ε���destroyʱ��qָ�����һ�������Ԫ��֮���λ��
//                                    ��ֻ�ܶ����������˵�Ԫ�ؽ���destroy������
//
//   alloc.deallocate(p,n);            �ͷ��ڴ�
//
//   unitialized_copy(b,e,b2);         �ӵ�����b��eָ�������뷶Χ�п���Ԫ�ص�������b2ָ����δ�����ԭʼ�ڴ���
//                                     ���û᷵��һ��ָ�� ָ�����һ�������Ԫ��֮���λ��
//
//   ���ӣ�
//   void input_reverse_output_string(int n)
//   {
//       allocator<string>alloc;
//       auto const p = alloc.allocate(n);
//       string s;
//       auto q = p; //��ʱδ���� qָ��p�ڴ�Ŀ�ͷλ��
//       while(q != p + n && cin >> s)
//              alloc.construct(q++,s);
//       while(q != p)
//              cout<< *--q << " ";alloc.destroy(q);
//       alloc.destroy(p,n);
//   }

/*
����ָ�뾭�䰸�� 1.0�汾
//���ǲ�����һ��StrBlob������ֱ�ӱ���vector����Ϊһ������ĳ�Ա������ʱҲ�ᱻ����
//�ٶ�b1��b2��StrBlob���������󣬹�����ͬ��vector �����vector����������һ��StrBlob�У�����b2��
//��ô��b2�뿪������ʱ����vectorҲ�ᱻ���٣�Ϊ�˱�֤vector�е�Ԫ�ؼ������ڣ����ǽ�vector�����ڶ�̬�ڴ���
//Ϊ��ʵ��������ϣ�������ݹ�������Ϊÿ��StrBlob����һ��shared_ptr������̬�����vector
//��shared_ptr�ĳ�Ա����¼�ж��ٸ�StrBlob������ͬ��vector������vector�����һ��ʹ���߱�����ʱ�ͷ�vector

#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;

class StrBlob
{
public:
    typedef vector<string>::size_type size_type;

    StrBlob();
    StrBlob(initializer_list<string>i1);

    size_type size() const { return data->size(); }
    bool empty()const { return data->empty(); }

    //��Ӻ�ɾ��Ԫ��
    void push_back(const string& t) { data->push_back(t); }
    void pop_back();

    //Ԫ�ط���
    string& front();
    const string& front()const;   //���ڴ��볣���ͷǳ������������
    string& back();               //���ص��ǵײ�const ����const����������
    const string& back()const;
private:
    shared_ptr<vector<string>>data;
    void check(size_type i, const string& msg)const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()){}

StrBlob::StrBlob(initializer_list<string> i1) :
    data(make_shared<vector<string>>(i1)){}


void StrBlob::check(size_type i, const string& msg)const
{
    if (i >= data->size())
        throw out_of_range(msg);
}

string& StrBlob::front()
{
    check(0, "frotn on my empty StrBlob");
    return data->front();
}

const string& StrBlob::front() const
{
    check(0, "frotn on my empty StrBlob");
    return data->front();
}
string& StrBlob::back()
{
    check(0, "back on my empty StrBlob");
    return data->back();
}

const string& StrBlob::back()const
{
    check(0, "back on my empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on my empty StrBlob");
    data->pop_back();
}

int main()
{
    const StrBlob csb{ "hello", "world", "pezy" };
    StrBlob sb{ "hello", "world", "Mooophy" };

    cout << csb.front() << " " << csb.back() << endl;
    sb.back() = "pezy";
    cout << sb.front() << " " << sb.back() << endl;
}
*/


/*

p412 t12.6 t12.7

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<fstream>
using namespace std;

//typedef vector<int>* Ptr;
typedef shared_ptr<vector<int>>  Ptr;

auto make_point()
{
   // return new vector<int>{};
    return make_shared<vector<int> >();
}
auto populate(Ptr vec)
{
    for (int i; cout << "enter:", cin >> i; vec->push_back(i));
    return vec;
}
auto print(Ptr vec)-> ostream&
{
    for (auto& num : *vec)
        cout << num << " ";
    return cout;
}
int main()
{
    auto vec = populate(make_point());
    print(vec);
    //delete vec;
    return 0;
}

*/

/*

//�ı���ѯ���� ���µ��ص㣡����

#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<memory>
#include<fstream>
#include<sstream>

using namespace std;

class QueryResult;

class TextQuery
{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&)const;
private:
    shared_ptr<vector<string>>file; //�����ļ�

    map<string, shared_ptr<set<line_no>>>wm; //ÿ�����ʵ������ڵ��кŵļ��ϵ�ӳ��
};

TextQuery::TextQuery(ifstream& is) : file(new vector<string>)
{
    string text;
    while (getline(is, text)) //�����ļ��е�ÿһ��
    {
        file->push_back(text); //fileָ���vector��������ı�
        int n = file->size() - 1; //��ǰ���к�
        istringstream line(text); //��text��ȡ��line����Ϊÿ�����ʵ�������
        string word;
        while (line >> word) //ѭ��������һ���е�ÿ������
        {
            //������ʲ���wm�У������������Ϊ�±���wm�����һ�� �����й���ֵ��ʼ��(���ڸ������ʼ��Ϊ��ָ��)
            auto& lines = wm[word]; //lines��һ��ָ��set����������ָ�� �������Ѿ����� ��map���������ʲô��������
            if (!lines) //�����ǵ�һ�������������ʱ�����ָ����һ����ָ��
                lines.reset(new set<line_no>);//����һ��set����
            lines->insert(n);//�����кŲ���set�� �ظ���set���������ʲô��������
        }
    }
}

class QueryResult //����Ľ����
{
    friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s, shared_ptr<set<TextQuery::line_no>>p, shared_ptr<vector<string>>f)
        : sought(s), lines(p), file(f) {}
private:
    string sought; //��ѯ����
    shared_ptr<set<TextQuery::line_no>>lines; //���ֵ��к�
    shared_ptr<vector<string>>file; //�����ļ�
    
};

QueryResult TextQuery::query(const string& sought)const
{
    //���δ�ҵ�sought,����һ��ָ���set��ָ��
    static shared_ptr<set<line_no>>nodata(new set<line_no >);
    //ʹ��find�������±�����������ҵ��ʣ����⽫������ӵ�wm��
    auto loc = wm.find(sought);
    if (loc == wm.end()) //δ�ҵ� ����β��������
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);//������set����ָ���Լ�vector����ָ��
}                         //����ָ�������ѡ�񿽱����� ���������㷨��Ч��

ostream& print(ostream& os, const QueryResult& qr)
{
    //����ҵ��˵��ʣ���ӡ���ֵĴ��������г��ֵ�λ��
    os << qr.sought << "occurs" << qr.lines->size() << endl;
    //��ӡ���ֵ��ʵ�ÿһ��
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << endl;
    return os;                                   //�����ǱȽϾ���ĵ���������
}

void runQueries(std::ifstream& infile)
{
    TextQuery tq(infile);
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << std::endl;
    }
}
int main()
{
    ifstream file("../data/storyDataFile.txt");
    runQueries(file);
}
*/