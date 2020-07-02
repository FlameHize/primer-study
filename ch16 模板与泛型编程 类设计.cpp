/*
1������ģ��
    
  ����ģ�壺

  (1)ģ�����Ͳ���T

     ����ģ�����ǰ����ʹ�ùؼ���class��typename

  template<typename T>
  int compare(const T& v1,const T& v2)
  {
        if(v1 < v2) return -1;
        if(v1 > v2) return 1;
        return 0;
  }
  ģ�����T��ʾ��������������õ������ͻ�ֵ����ʹ��ģ��ʱ�����ǿ���
  ��ʽ�Ļ�����ʽ��ָ��ģ��ʵ�Σ�����󶨵�ģ�������

  //ʵ������int compare(const int&,const int&);
  cout << compare(1,0) << endl;  T��ʽ�ƶ�Ϊint

  //ʵ������int compare(const vector<int>&,const vector<int>&);
  vector<int>vec(1,2,3),vec2(4,5,6);
  cout << compare(vec1,vec2) << endl; T��ʽ�ƶ�Ϊvector<int>

  ���Ǳ��������ɵ������汾���������汾ͳ��Ϊģ���ʵ��

  (2)������ģ�����

     ������ģ�������ʾһ��ֵ������һ������
     ͨ��һ���ض��������������ǹؼ���class��typename��ָ����ģ�����

     ������
     template<unsigned N,unsigned M>
     int compare(const char (&p1)[N],const char (&p2)[M])
     {
            return strcmp(p1,p2);
     }
     ���ã�compare("hello","world");
     ʵ�����İ汾:
       int compare(const char (&p1)[3],const char (&p2)[4])

    ��չ��������ģ����������������������͡�������һ��ָ�����������͵�ָ�������
          �󶨵����������Ͳ�����ʵ�α�����һ���������ʽ(����׶�ȷ�����)

  (3)ģ��ı���
     ������������һ��ģ�嶨��ʱ�����������ɴ��룬ֻ�е�����ʵ������ģ���һ���ض��汾ʱ
     �������Ż����ɴ���
     Ҳ����˵��������ʹ�ö����Ƕ���ģ��ʱ���������Ż����ɴ���

     Ϊ��ʵ������һ���汾����������Ҫ���պ���ģ�����ģ���Ա�����Ķ���
     ��ˣ����ģ����벻ͬ��ģ���ͷ�ļ�ͨ����������������

  ��ģ�壺
    
    ���ã����������ͼ
    �뺯��ģ��Ĳ�ͬ������������Ϊ��ģ���ƶ�ģ���������
    Ϊ��ʹ����ģ�壬������ģ������ļ��������ṩ������Ϣ(����ģ�������ģ��ʵ���б�)

    ��������ģ��֮��ĳ�Ա���������Թؼ���template��ʼ �����ģ������б�
    ������
    template<typename T>
    Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

    �涨�������Ǵ���һ����ģ�����������ʱ������������ģ����������ʱ
          �ͺ��������Ѿ��ṩ����ģ�����ƥ���ʵ��һ��

          Ҳ����˵����һ����ģ����������ڣ����ǿ���ֱ��ʹ��ģ����������ָ��ģ��ʵ��

          ������ģ��template<typename T>class Blob��
          д Blob& operator++();
          ����Ҫд Blob<T>& operator++();
    
  (4)��ģ�����Ԫ
     
     ���һ����ģ�����һ����ģ����Ԫ������Ԫ����Ȩ���Է�������ģ��ʵ��
     �����Ԫ������ģ�壬�������Ȩ��������Ԫģ��ʵ����Ҳ����ֻ��Ȩ ���ض�ʵ��

     ����ʹ��using ���� typedef��Ϊģ�嶨��һ�����ͱ���

     template<typename T> using twin = pair<T,T>;
     twin<string>authors;

     ��Ԫ�����ã�

     ����1��һ��һ��Ԫ��ϵ

     template <typename>class BlobPtr;   //������Ϊģ��
     template <typename>class Blob;
     template <typename T>
     bool operator==(const Blob<T>&,const Blob<T>&);

     template<typename T>
     class Blob
     {
        friend class BlobPtr<T>;
        friend bool operator==<T>(const Blob<T>&,const Blob<T>&);
     }

     ����2��ͨ����Ԫ��ϵ
     template<typename T> class Pal;
     class C
     {
        friend class Pal<C>;  //����Cʵ������Pal��C��һ����Ԫ
        template<typename T> friend class Pal2; 
        //Pal2������ʵ������C����Ԫ���������������ǰ������
     }
    
  (5)��ģ��ľ�̬��Ա

      template<typename T>
      class Foo
      {
        public:
            static std::size_t count(){ return ctr;}
        private:
            static std::size_t ctr;
      }

      template<typename T>
      size_t Foo<T>::ctr = 0; // ģ�����ÿ��static���ݳ�Ա�������ҽ���һ������
      //���Ҫ��static���ݳ�Ա����Ϊģ��

      ÿ��Fooʵ���������Լ���static��Աʵ��
      ���������������X������һ��Foo<X>X::ctr��һ��Foo<X>::count��Ա
      ����Foo<X>���͵Ķ�������ͬ��ctr�����count����
      (ע�������������ĸ���)
  
      Foo<string>fs;
      //ʵ����static��ԱFoo<string>::ctr ��Foo<string>::count

      Foo<int>f1,f2,f3;
      //����������������ͬ��Foo<int>::ctr ��Foo<int>::count��Ա
    
  (6)ģ�����
     
     һ��ģ���������һ���ض�ģ������б���ֻ�ܳ���һ��

     template<typename V,typename V> //����

     ģ�������붨���е����ֲ�����ͬ ��ʽ��ͬ����

     Ĭ������£�C++���Լٶ�ͨ����������������ʵ����ֲ������ͣ��������ݳ�Ա��
     ���ϣ��ʹ��һ��ģ�����Ͳ��������ͳ�Ա���ͱ�����ʽ�ĸ��߱�������������һ������
     ������ʹ��typename�ؼ���

     template<typename T>
     typename T::value_type top(const T& c)
     {
            if(!c.empty())
                return c.back();
            else
                return typename T::value_type();
     }
     ������ϣ��֪ͨ������һ�����ֱ�ʾ����ʱ������ʹ�ùؼ���typename


     Ĭ��ģ��ʵ�����⣺���º�����Ӧ�ã�

     ������compare��һ��Ĭ��ģ��ʵ��less<T>��һ��Ĭ�Ϻ���ʵ��F()
     template<typename T,typename F = less<T>>
     int compare(const T& v1,const T& v2,F f = F())
     {
        if(f(v1,v2))return -1;
        if(f(v2,v1))return 1;
        return 0;
     }
     ����������У�Ϊģ������˵ڶ������Ͳ���������ΪF����ʾ�ɵ��ö���
     ��������һ���µĺ�������f���󶨵�һ���ɵ��ö�����
     (Ϊ��ģ������ṩ��Ĭ��ʵ�Σ���Ϊ���Ӧ�ĺ�������Ҳ�ṩ��Ĭ��ʵ��)
     
     ->Ĭ��ģ��ʵ��ָ��compare��ʹ�ñ�׼���less����������
       Ĭ�Ϻ���ʵ��ָ��f������F��һ��Ĭ�ϳ�ʼ���Ķ���

     ���ã�
     bool i = compare(0,42); ����-1 T = int F = less<int>
     
     Sales_data item1(cin),item2(cin);
     bool j = compare(item1,item2,compareIsbn); //�����Լ��ıȽϲ���
     compareIsbn��������һ���ɵ��ö���(����������ָ�롢lambda�������������) 
     T = Sales_data     F = compareIsbn (ִ�пɵ��ö���compareIsbn��Ĭ�ϳ�ʼ��)

     .....................

     template<class T = int> 
     class Number
     {
          ......һϵ�ж��弰����
     }
     Number<double>lots_of_precision;
     Number<>average_precision;    
     ��<>��ʾ����ϣ��ʹ��Ĭ������


  (7)��Աģ��
    
     һ������������ͨ�໹����ģ�壬���԰���������ģ��ĳ�Ա����
     ���ֳ�Ա����Ϊ��Աģ��

     ����1����ͨ��ĳ�Աģ��--����һ��ɾ����
     class DebugDelete
     {
        public:
            DebugDelete(ostream& s = cerr):os(s){}

            template<typename T>
            void operator()(T* p)const //T�������ɱ������ƶ�(������������������ǿɵ��ö���)
                { os << "deleting unique_ptr " << endl; delete p;}
        private:
            ostream& os;
     }

     ���ã�double* p = new double;
           DebugDelete d;      //�Զ����һ��ɾ���� ����delete���ʽһ��ʹ�õĶ���
           d(p);  //����DebugDelete::operator()(double*) �ͷ�p
           int *ip = new int;
           //��һ����ʱDebugDelete�����ϵ���operator()(int*)
           DebugDelete()(ip);

           ��������unique_ptr��ɾ����
           unique_ptr<int,DebugDelete>p(new int,DebugDelete()); //DebugDelete()���ṩ���������ʵ�� ��һ��Ĭ�ϳ�ʼ���Ķ���

    ����2��������ģ���ٶ����Աģ��
           template<typename T>
           class Blob
           {
                template<typename It>
                Blob(It b,It e);
           }

           ���ⶨ��˳�Ա������ͬʱ�ṩ��ͺ���ģ���ʵ��
           template<typename T>
           template<typename It>
           Blob<T>::Blob(It b,It e):data(make_shared<vector<T>(b,e)){}
           
           ���ã�
           int ia[] = {1,2,3,4,5};
           Blob<int>a(begin(ia),end(ia));
           T = int It = int* 


  (8)����extern��ʽ����ʵ��������ģ�忪��

     extern template declaration; ����һ��ʵ��������(Ҳ���������������ط��������ж��extern����)
     ��������ļ�����Ҫ�õ��ĸ�ʵ������ע��extern����(����Ӿ����ģ��ʵ�� ��int��)��
     template declaration;        ����һ��ʵ�����Ķ��壨һ��ģ��ֻ����һ�����壩

     //����
     extern template class Blob<string>; //���� �����������Ҫ�õ�Blob<string> ���Ƕ����ڱ�
     template int compare(const int&,const int&); //���� ��һ��ʵ������������(һ��ʵ��������ֻ����һ������)

     ���ģ�����������externģ������ʱ�������ٱ��ļ�������ʵ��������
     ֻ��Ҫ���������ļ���ʵ��ģ�嶨�弴�� �������Դ��ļ����ڴ濪��

     ������
     �ļ� Application.cc

     extern template class Blob<string>;
     extern template int compare(const int&,const int&);
     Blob<string>sa1,sa2; //Blob<string>ʵ��������������λ��

     //Blob<int>�������initializer_list�Ĺ��캯���ڱ��ļ���ʵ����
     //ԭ����Ϊû������extern <int>���� �����ڴ�ʵ����
     Blob<int>a1 = {1,2,3,4,5};
     Blob<int>a2(a1); //��������ʵ����

     int i = compare(a1[0],a2[0]); //ǰ����extern���� ����ʵ��������������λ��

     �����ļ�Application.ccֻ����Blob<int>��ʵ���������initializer_list�������캯���Ϳ������캯��
     compare<int>������Blob<string>�಻�ڱ��ļ�ʵ��������Щģ��Ķ�������ڳ���������ļ���


     �ļ� templateBuild.cc
     //ʵ�����ļ�Ϊÿ���������ļ�������Ϊextern�����ͺͺ����ṩһ����extern�Ķ���
     template class Blob<string>;
     template int compare(const int&,const int&);

     ���գ��ļ�templateBuild.cc�������compare<int>��ʵ����Blob<string>��Ķ���
     �����Ǳ����Ӧ�ó���ʱ�����뽫templateBuild.cc��Application.cc���ӵ�һ��

     ���䣺һ����ģ���ʵ������ʵ������ģ������г�Ա
          Ҳ����˵����ʹ���ǲ�����ĳ����Ա����Ҳ�ᱻʵ����
          (����������ʽʵ��������ģ������ͱ���������ģ������г�Ա)

2��ģ��ʵ���ƶ�

   ���壺�Ӻ���ʵ����ȷ������ģ��ʵ�εĹ���

   (1)����ת����ģ�����Ͳ�����
   ���ڵ�����Ӧ���ں���ģ���ֻ���������ת����������Ӧ���ں���ģ��
   1��constת�� 
   ��һ����const��������û�ָ��ʵ�δ��ݸ�һ��const�����û�ָ���β�
   2���������ָ��ת��(����������)
   һ������ʵ�ο���ת��Ϊһ��ָ������Ԫ�ص�ָ�룬һ������ʵ�ο���ת��Ϊһ���ú������͵�ָ��

   ������
   template<typename T>T fobj(T,T); //ֵ������ʽ ʵ�α�����
   template<typename T>T fref(const T&,const T&);//���ô���
   string s1("hello");
   const string s2("slam");
   
   fobj(s1,s2);  //����fobj(string,string) s2��ʵ�ζ���const������
   fref(s1,s2);  //����fref(const string&,const string&) ��ʵ��s1ת��Ϊconst����������� (�ײ�const���Խ��ܷǳ�������)

   int a[10],b[42];
   fobj(a,b);    //����f(int*,int*)
   fref(a,b);    //���� ���鲻�ܴ�����������������

   ���磺
   f(int& arr[10]);   ���� ���ܽ�arr���������õ����� �����β���const T&��һ������������ ������ 
   f(int (&arr)[10]); ��ȷ arr�Ǿ���10���������������������

   �ܽ᣺
   ��ʵ�δ��ݸ���ģ�����͵ĺ����β�ʱ���ܹ��Զ�Ӧ�õ�����ת��ֻ��constת��
   �Լ����ݻ�����ָ���ת��

   (2)����ģ����ʽʵ��

    template<typename T1,typename T2,typename T3>
    T1 sum(T2,T3);
    û���κκ���ʵ�ε����Ϳ������ƶ�T1������ ��˱����ṩ��ʽģ��ʵ��
    int a;
    double b;
    float c;

    �������ֵ�����ʽ����

    auto val = sum<float>(a,b); //float sum(int,double);
    //�˵�����ʽ��ָ��T1��T2 T3�ɱ������ƶϵó�
    auto val = sum<float,int,double>(a,b);
    //�˵�����ʽ��ָ������ģ�����

   (3)β�÷�������������ת��
    
      Ϊʲôʹ��β�÷������ͣ�
      ԭ���ڱ��������������Ĳ����б�֮ǰ���޷�ȷ�����ص����� ��˱���ʹ��β�÷�������
            β�÷������ͳ����ڲ����б�֮�󣬿���ʹ�ú����Ĳ���
      ������
      template<typename It>
      auto fcn(It beg,It end��->decltype(*beg)
      {
        //�������
        return *beg;  //�ȼ��ڷ��������е�һ��Ԫ�ص�����
      }
      ������ĳ����У���������β�÷�������֪ͨ������fcn��ʵ�ʷ���������
      ������beg�����Ľ��������ͬ ���ҽ�������������ص���һ����ֵ
      ���ͨ��decltype�ƶϵ�����Ϊbeg��ʾ��Ԫ�ص����͵�����

      ���ñ�׼��ģ�����������ת��
      ͷ�ļ���type_traits
      ����remove_reference�����Ԫ������
      ������һ��ģ�����Ͳ�����һ����Ϊtype�����ͳ�Ա
      �﷨��remove_reference<int&> ��õ�type��Ա��int
      ������remove_reference<decltype(*beg)>::type ���beg���õ�Ԫ�ص�����
      decltype(*beg)����Ԫ�����͵���������  remove_reference::type��ȥ���� ʣ��Ԫ�����ͱ���

      ������Ĵ�����д���
      template<typename It>
      auto fcn2(It beg,It  end)->typename remove_reference<decltype(*beg)>::type
      {
            return *beg;  //ʵ�ʷ��ص��������е�һ��Ԫ�صĿ���
      }
      Ϊʲô��typename?
      ԭ��type��һ����ĳ�Ա(������һ��ģ�����)
      ��ˣ���ǰ���ᵽ����ͬ�������ڷ������͵�������ʹ��typename�ؼ�����֪ͨ������ type��һ������
      (����typename�ؼ���ϣ��ʹ��һ��ģ�����Ͳ��������ͳ�Ա)

      remove_pointer<T*>::type    ����T
      remove_reference<T&>::type  ����T

   (4)����ָ���ʵ���ƶ�

     template<typename T>
     int compare(const T&,const T&); 

     int (*pf1)(const int&,const int&) = compare;  //��ȷ ����ָ��pf1ָ��compare��int�汾ʵ��
     void func(int(*)(const string&,const string&);//��ȷ ����һ��TΪstring�ĺ���ָ����Ϊ�β�
     void func(compare);   //���� û��ָ��ģ��������� ��֪��ʹ����һ��ʵ��
     void func(compare<int>); // ��ȷ ����compare(const int&,const int&)

     ����const��ʵ���ƶ��е��жϣ�
        
        1����һ������������ģ�����Ͳ�����һ����ͨ��ֵ����ʱ(T&),�󶨹���������ǣ�ֻ�ܴ��ݸ���һ����ֵ
        ʵ�ο�����const���ͣ�Ҳ���Բ���
        ���ʵ����const�ģ���T�����ƶ�Ϊconst����
        template<typename T>
        void f1(T&);
        f1(i); i��һ��int T=int
        f1(ci);ciʱһ��const int  T = const int
        f1(5); ���� ������һ����ֵ ������ֵ

        2����һ������������ģ�����Ͳ�����һ��const����ʱ(const T&)
        ���Դ��ݸ���һ��const����һ����const����һ����ʱ�������һ�����泣��ֵ
        ����T���ƶϽ��������һ��const���� ��Ϊconst�����Ѿ��Ǻ����������͵�һ����
        template<typename T>
        void f2(const T&);
        f1(i); i��һ��int T=int
        f1(ci);ciʱһ��const int  T =int
        f1(5); ������һ��const&�󶨵���ֵ ����T = int

        3����һ��������������ֵ����ʱ(T&&) �ƶϳ���T����ֵʵ��
        template<typename T>
        void f3(T&&);
        f3(42);   T = int

        ������һ�����⣺�����һ����ֵ�����βΰ��ϵ�ʵ������ֵ�ᷢ��ʲô��
        �𰸣������۵�
        ������C++�������󶨹���֮�ⶨ���������ģ��󶨹���--�����۵�
        f3(i);  ʵ����һ����ֵ��Ҳ���Ǳ�����ʽ�� ģ�����T = int&
        f3(ci); ʵ����һ����ֵ ģ�����T��һ��const int&

        �����۵�����(������ģ������)��
        ���һ������������һ�� ָ��ģ�����Ͳ�������ֵ����T&&���������Ա��󶨵�һ����ֵ
        �����ʵ����һ����ֵ ���ƶϳ���ģ��ʵ�����ͽ���һ����ֵ����
        �Һ�����������ʵ����Ϊһ����ͨ��ֵ���ò���T&
        (Ҳ����˵�����ǿ��Խ��������͵�ʵ�δ��ݸ�T&&���͵ĺ�������)

        ʹ����ֵ���õĺ���ģ��ͨ��ʹ��֮ǰ������ֵ����ֵ���õķ�ʽ��������
        template<typename T>void f(T&&);     ģ����԰��������� ��ȷƥ��󶨵���const��ֵ
        template<typename T>void f(const T&);ģ����԰��������� ��ȷƥ��󶨵���ֵ��const��ֵ

   (5)std::move����� �ص�
      
      ֮ǰ��Ӧ�ã�
      int&& r1 = 42;            ��ȷ
      int&& r2 = r1;            ���� ���ܽ�һ����ֵ���ð󶨵���һ����ֵ���ñ����� ��Ϊ��������ֵ
      int&& r2 = std::move(r1); ��ȷ ��ʾ�Ľ�һ���������ֵת��Ϊ��ֵ��������(��ð󶨵�һ����ֵ�ϵ���ֵ����)

      std::moveԴ����
      template<typename T>
      typename remove_reference<T>::type&& move(T&& t)
      {
          return static_cast<typename remove_reference<T>::type&&>(t);
      }
      string s1("hello"),s2;
      s2 = std::move(string("slam"));
      s2 = std::move(s1);

      �ڵ�һ������s2 = std::move(string("slam"))�� ���ݸ�move��ʵ����string�Ĺ��캯������ֵ���
      ����ƶϳ���T��string
      remove_reference��string����ʵ����
      remove_reference<string>type��Ա��string
      move�ķ���������string&&
      move�ĺ�������t��������string&&

      �����γɵ�ʵ������string&& move(string&& t);
      ������õĽ�������������ܵ���ֵ����

      �ڵڶ�������s2 = std::move(s1)�� ���ݸ�move��ʵ��s1��һ����ֵ(����)
      ����ƶϳ���T��������string&(�����۵�����)
      remove_reference��string&����ʵ����
      remove_reference<string&>type��Ա��string
      move�ķ���������string&&
      move�ĺ�������t��ʵ����Ϊstring& &&,���۵�Ϊstring&

      �����γɵ�ʵ������string&& move(string& t);
      Ҳ���ǽ�һ����ֵ���ð󶨵���һ����ֵ
      ���ʵ�����ĺ����巵��static_cast<string&&>(t)
      t��������һ��string&,cast����ת��Ϊstring&&
      (C++������static_cast��ʽ�Ľ�һ����ֵת��Ϊһ����ֵ����)

   (6)ģ���е�ת������ �ص㣡

      ���ã�һЩ������Ҫ����һ������ʵ����ͬ���Ͳ����ת������������
            ��ת��������£���Ҫ���ֱ�ת��ʵ�ε���������(�Ƿ���const/�Ƿ�����ֵ��ֵ)

      ģ�����ܱ���������Ϣ�ĺ���������ָ��ģ�����Ͳ�������ֵ����T&&
      template<typename F,typename T1,typename T2>
      void filp2(F f,T1&& t1,T2&& t2)
      {
            f(t2,t1);  //f(T v1,T& v2)
      }
      ����filp2(f,j,42) ���ݸ�����t1һ����ֵj ���������۵������Ƴ�T = int& && = int&
      t1���󶨵�j�ϣ���filp2����fʱ f�е����ò���v2���󶨵�t1 Ҳ����j ��v2�ı�ʱͬʱ��ı�j

      ȱ�㣺�������������ĺ���file2(g,i,42); //g(T1&& v2,T2& v1)
            ���ݸ�g����filp2����Ϊt2�Ĳ���  (T2&& t2 = 42)
            ���������������κα���һ��������ֵ���ʽ
            ����C++�涨������ʽ�Ľ�һ����ֵ�󶨵�һ����ֵ������ ��������������ֵ����ʱ�ᷢ������
            (int&& r1 = 42; int&& r2 = r1; ����Ǵ���ģ�
      
      �Ľ�������ʹ��std::forward��׼�⺯����ͷ�ļ�Ϊutility��
      �÷���ͨ����ʽ��ģ�������� ������ʽʵ�����͵���ֵ���� forward<T>����T&&

      template<typename F,typename T1,typename T2>
      void filp(F f,T1&& t1.T2&& t2)
      {
        f(std::forward<T2>(t2),std::forward<T1>(t1);
      }
      ������ݸ�T1λ�õ�ʵ����һ����ֵ ��ôT1������Ϊһ����ͨ����������
      forwarf<T1>�᷵��T1&&
      ������ݸ�T1λ�õ�ʵ����һ����ֵ ��ôͨ�������۵� T1������һ����ֵ��������
      ����������� forward<T1>�ķ���������һ��ָ����ֵ�������͵���ֵ����& &&
      ���ٴδ��������۵����� ����һ����ֵ��������

      �������filp(g,i,42) ��ôi����int&�����ʹ��ݸ�g 42��int&&�����ʹ��ݸ�g

   (7)ģ������
      
      ����
      1�����ͬ���õĺ�����ֻ��һ���Ƿ�ģ���������ѡ��˺���
      2�����ͬ���õĺ�����û�з�ģ�庯���������ж������ģ�壬������һ��ģ�������ģ�������������ѡ���ģ��
      ���������������ϣ����û��������

      template<typename T>string debug_rep(const T& t);
      template<typename T>string debug_rep(T* p);

      const string* sp = &s;
      cout << debug_bug(sp) << endl;

      ��������ģ�� ������ ������õڶ���
      debug_rep(const string*&) T = string*
      debug_rep(const string*)  T = const string

      Ϊʲô���������Ĺ��򣬲��һ���õڶ���

      ���û���������Ļ������޷���һ��const��ָ����ø�ָ��汾��debug_rep
      ��Ϊģ��debug_rep(const T&)��������˵�����������κ�����(����ָ��)
      ���ģ���debug_rep(T*)��ͨ�ã�����ֻ������ָ������
      ���ѡ�����������ָ��汾

      �ڶ����κκ���֮ǰ�������Ҫ�õ��ض��ĺ������ذ汾���ǵ�����������Ҫ�õ������غ����汾
      �����Ͳ��õ���ϣ�����õĺ�����ʵ��������������Ҫ�İ汾

3���ɱ����ģ��
    
    ���壺���ܿɱ���Ŀ������ģ�庯����ģ���� 
          �ɱ���Ŀ�Ĳ�������Ϊ������(����ģ��������뺯��������)
          ���ű�ʾ:...ʡ�Ժ�  typename.../class...

          ������
          template<typename T,typename...Args>         //Args ģ�������
          void foo(const T& t,const Args&... rest);    //args ����������

          �������Ӻ�����ʵ���ƶ�ģ���������
          ����һ���ɱ����ģ�壬�����������ƶϰ��в�������Ŀ
          int i = 0;double d = 3.14;string s = "hello,slam";
          foo(i,s,42,d);   //����3������
          foo(s,42,"h1");  //����2������
          foo(d,s);        //����1������
          foo("hi");       //�հ�
                                             //42�����۵�
          void foo(const int&,const string&,const int&,const double&)
          void foo(const string&,const int&,const char[3]&);
          void foo(const double&,const string&);
          void foo(const char[3]&);

          size_of...����� 
          ���ã�������е�Ԫ������
          sizeof...(Args); ���Ͳ�������Ŀ
          sizeof...(args); ������������Ŀ

          �ɱ��������ת�����ʹ��    ����ת������������
          template<typename...Args>
          void StrVec::emplace_back(Args&&...args)
          {
                check_n_alloc();
                alloc.construct(first_free++,std::forward<Args>(args)...);
                //��emplace_back������ʵ��ת������һ����Ϊconstruct�ĺ��� �������ʵ�ʹ���
          }
          ��ģʽ����������ʽ��Ԫ��
          std::forward<Ti>(ti);
          ����Ti��ʾģ��������ĵ�i��Ԫ�ص����� ti��ʾ�����������е�i��Ԫ��

4��ģ��������
   
   ���壺�������汾��ģ��һ�������Ķ��� ������һ������ģ�������ָ��Ϊ�ض�������
   ǰ�᣺ԭģ���������������������
   �﷨��template<> ָ��ҪΪԭģ�������ģ������ṩʵ��
   ���ʣ�һ��ʵ��(Ϊԭģ���һ������ʵ���ṩ����)������������

   ������
   template<typename T>
   int compare(const T&,const T&);

   template<>int compare(const int&,const int&);


   ������������
   template<typename T>class remove_reference;
   template<typename T>class reomve_reference<T&>;  //��������������ֵ���ð汾
   template<typename T>class reomve_reference<T&&>; //��������������ֵ���ð汾


    */




//StrBlob��ģ��д��

/*
#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<functional>

using namespace std;

template<typename T>
class Blob
{
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    Blob();
    Blob(initializer_list<T> i1);

    size_type size()const { return data->size(); }
    bool empty()const { return data->empty; }

    void push_back(const T& t) { data->push_back(t); }
    void push_back(T&& t) { data->push_back(std::move(t)); }
    
    void pop_back();

    T& back();
    T& operator[](size_type i);
    
private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string& msg)const;
};

template<typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

template<typename T>
void Blob<T>::check(size_type i, const string& msg)const
{
    if (i >= data->size())
        throw out_of_range(msg);
}

template<typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template<typename T>
Blob<T>::Blob(initializer_list<T> i1):
    data(make_shared<vector<T>>(i1)){}

int main()
{
    Blob<string> articles = { "a","b","cc" };
    int num = articles.size();
    cout << num << endl;
    cout << articles[2] << endl;
    return 0;
}

*/

/*

//�ص㣺�Լ�����������ָ��shared_ptr

#include<iostream>
#include<string>
#include<functional>

template<typename T>class SharedPointer;

struct Delete     //�Զ����ɾ����
{
    template<typename T>
    auto operator()(T* p)const
    {
        delete p;
    }
};

template<typename T>
auto swap(SharedPointer<T>& lhs,SharedPointer<T>& rhs)
{
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.ref_count, rhs.ref_count);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T>
class SharedPointer
{
    friend auto swap<T>(SharedPointer<T>&, SharedPointer<T>&); //��Ԫ��������ϵ
public:
    SharedPointer():
        ptr(nullptr),ref_count(new std::size_t(1)),deleter(Delete()){}
    //Delete()��һ��Ĭ�ϳ�ʼ���Ŀɵ��ö��� ���뷺����ģ����deleter
    explicit SharedPointer(T* raw_ptr): //���÷�����ָ����й���
        ptr(raw_ptr),ref_count(new std::size_t(1)),deleter(Delete()){}

    SharedPointer(const SharedPointer& other):
        ptr(other.ptr),ref_count(other.ref_count),deleter(other.deleter)
    {
        ++* ref_count; //�ȳ�ʼ�������� �ټ�1 �൱��ref_count���߹�ָͬ���size_t��Ҳ�������ô���+1��
    }
    SharedPointer(SharedPointer&& other)noexcept:  //noexcept��֤���׳��쳣
        ptr(other.ptr),ref_count(other.ref_count),deleter(std::move(other.deleter))
    {
        other.ptr = nullptr; //������ƶ����Դ����
        other.ref_count = nullptr;
        //ֻ��deleterɾ�������������ƶ��� ��������ָ�뻹�ǿ��� ��Ч������ ֻҪ�������ÿռ���
    }

    SharedPointer& operator=(const SharedPointer& rhs) //������ֵ���������
    {
        ++* rhs.ref_count;
        decrement_and_destroy(); //����Լ������һ��ָ�� ��ִ������
        ptr = rhs.ptr, ref_count = rhs.ref_count, deleter = rhs.deleter;
        return *this;
    }
    SharedPointer& operator=(SharedPointer&& rhs) noexcept  //�ƶ���ֵ���������
    {
        ::swap(*this,rhs);
        rhs.decrement_and_destroy();
        return *this;
    }
    auto swap(SharedPointer& rhs)
    {
        ::swap(*this, rhs);
    }

    T& operator*()const
    {
        return *ptr;
    }
    T* operator->()const
    {
        return &*ptr;
    }
    auto use_count()const
    {
        return *ref_count;
    }
    auto get()const
    {
        return ptr;
    }
    auto unique()const
    {
        return 1 == *ref_count;
    }


    //����������
    auto reset()
    {
        decrement_and_destroy();
    }
    auto reset(T* pointer)
    {
        decrement_and_destroy();
        ptr = pointer;
        ref_count = new std::size_t(1);
    }
    auto reset(T* pointer, const std::function<void(T*)>& d) //����һ��ɾ����
    {
        reset(pointer);
        deleter = d; //�൱���ع�ɾ����
    }
    ~SharedPointer()
    {
        decrement_and_destroy();
    }

private:
    T* ptr;
    std::size_t* ref_count;
    std::function<void(T*)>deleter; //��ģ��std::function��һ��ͨ�á���̬�ĺ�����װ��std::function��ʵ�����Զ��κο��Ե��õ�Ŀ��ʵ����д洢�����ơ��͵��ò�������ЩĿ��ʵ�������ͨ������Lambda���ʽ������ָ�롢�Լ��������������
    //C++11���Ƴ�std::function��Ϊ�˷����������󣬺���ָ�룬���ú�������Ա������ָ��

    auto decrement_and_destroy() //ִ�����һ������ָ������ٹ���
    {
        if (ptr && 0 == -- * ref_count)
        {
            delete ref_count;
            delete ptr;
        }
        else if (!ptr)
            delete ref_count;
        ref_count = nullptr;
        ptr = nullptr;
    }
};

int main()
{
    auto foo = SharedPointer<int>{ new int(42) };
    auto bar(foo);
    auto boo = SharedPointer<int>{ new int(40) };
    boo.swap(foo);
    std::cout << *foo << std::endl;
    std::cout << foo.use_count() << std::endl;

    auto string_ptr = SharedPointer<std::string>{ new std::string{ "Yue" } };
    std::cout << *string_ptr << std::endl;
    std::cout << string_ptr->size() << std::endl;

    return 0;
}

*/


//��������ָ��unique_ptr

/*

#include<iostream>
#include<string>
#include<functional>

template<typename T,typename D>class unique_pointer;
template<typename T,typename D>
void swap(unique_pointer<T, D>& lhs, unique_pointer<T, D>& rhs);
struct DebugDelete     //�Զ����ɾ����
{
    template<typename T>
    auto operator()(T* p)const
    {
        delete p;
    }
};

template<typename T,typename D = DebugDelete>
class unique_pointer
{
    friend void swap<T, D>(unique_pointer<T, D>& lhs, unique_pointer<T, D>& rhs);

public:
    unique_pointer(const unique_pointer&) = delete; //ɾ����������
    unique_pointer& operator=(const unique_pointer&) = delete; //ɾ��������ֵ�����

    unique_pointer() = default;
    explicit unique_pointer(T* up):ptr(up){}//���ܷ�����ָ����вι���

    //�ƶ�����
    unique_pointer(unique_pointer&& up)noexcept
        :ptr(up.ptr) {up.ptr = nullptr;} //ʵ���ϲ��õ���ָ������ƶ���ʽ ���� Ȼ������
    unique_pointer& operator=(unique_pointer&& rhs)noexcept;

    unique_pointer& operator=(std::nullptr_t n)noexcept;


    //�½���������صȳ������
    T& operator*()const { return *ptr; }
    T* operator->()const { return &this->operator*(); }
    T* get()const { return ptr; }
    void swap(unique_pointer<T, D>& rhs)
    {
        ::swap(*this, rhs);
    }
    void reset() noexcept
    {
        deleter(ptr);
        ptr = nullptr;
    }
    void reset(T* p)noexcept
    {
        deleter(ptr);
        ptr = p;
    }
    T* release();
    ~unique_pointer()
    {
        deleter(ptr); //����ɾ����ɾ��
    }
private:
    T* ptr = nullptr;
    D deleter = D();  //Ĭ�ϲ���D�ɵ��ö����Ĭ��Ĭ�ϳ�ʼ�� D�������ʵ���ǿɵ��ö���
};


template<typename T,typename D>
inline void swap(unique_pointer<T, D>& lhs, unique_pointer<T, D>& rhs)
{
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T, typename D>
inline unique_pointer<T,D>&
unique_pointer<T, D>::operator=(unique_pointer&& rhs)noexcept
{
    if (this->ptr != rhs.ptr)
    {
        deleter(ptr);
        ptr = nullptr;
        ::swap(*this, rhs);
    }
    return *this;
}

template<typename T, typename D>
inline T*
unique_pointer<T, D>::release()
{
    T* ret = ptr;
    ptr = nullptr;
    return ret;
}

int main()
{
    unique_pointer<int>p(new int(42));
    unique_pointer<int>p2(new int(40));
    p.swap(p2);
    std::cout << *p << std::endl;
    return 0;
}

*/