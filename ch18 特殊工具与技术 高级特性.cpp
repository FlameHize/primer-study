/*

1����λnew���ʽ

   new (place_address) type(initializers)
   ���ã���ָ���ĵ�ַ�����Լ��������

   place_address ָ��(�������ַ�Ͻ����ڴ�����빹��)
   ininitalizers ��ʼֵ�б�(���ڹ����·���Ķ���)

   һ��new���ʽ��ִ�й��������ȵ���operator new�����Ի�ȡ�ڴ�ռ� Ȼ���ڵõ����ڴ�ռ��й������
   ��֮�෴ һ��delete���ʽ��ִ�й������������ٶ��� Ȼ�����operator delete�����ͷŶ�����ռ�Ŀռ�

2������ʱ����ʶ��RTTI
    
   ��Ҫ�������
   tyopeid:���ر��ʽ������
   dynamic_cast:���ڽ������ָ������ð�ȫ��ת�����������ָ�������

   ���������������ʹ�û�������ָ�������ִ��ĳ��������������Ҹò��������麯��
   
   (1)dynamic_cast����̬����ת��
        
     dynamic_cast<type*>(e);
     dynamic_cast<type&>(e);
     dynamic_cast<type&&>(e);
     
     e�������������֮һ��e��type���͵Ĺ��л��ࡢ���������������
   
     ָ�����͵�dynamic_cast

        ������
        �ٶ�Base��������һ���麯����Derived�����Ĺ���������
        ָ��bpָ��Base�������ǿ���������ʱ����ת����ָ��Derived��ָ��

        if(Derived* dp = dynamic_cast<Derived*>(bp))
            //ʹ��dpָ���Derived����
        else //bpָ��һ��Base����
            //ʹ��bpָ���Base����
     
     ���ǿ��Զ�һ����ָ��ִ��dynamic_cast ������������͵Ŀ�ָ��

     �������͵�dynamic_cast
      
     ��������ʱ���׳�std::bad_cast�쳣
   
     void f(const Base& b)
     {
        try
        {
            const Derived& d = dynamic_cast<const Derived&>(b);
        }
        catch(bad_cast)
        {
            //����ʧ�����
        }
     }
   
   
   (2)typeid������������ڶ���

      ���ã������������ʽ���ʣ�����ʲô���ͣ�
      ��ʽ��typeid(e) e������������ʽ��������� ���صĽ����һ���������������
            ������ʽ��һ������ �򷵻ظ������������������
      
      ����������Ƕ���������һ���麯���������ֵʱ�����صĽ��ֱ������ʱ���
      ������������������� ���� ���������һ���������κ��麯������ʱ ���صĽ�����������ľ�̬����
      �����������һ��ָ��ʱ�����صĽ���Ǹ�ָ��ľ�̬��������

      ������
      Derived* dp = new Derived;
      Base* bp = new Base;
      //������������ʱ�Ƚ��������������
      if(typeid(*bp) == typeid(*dp))
      {
            //bp��dp��ָ��ͬһ���͵Ķ���
      }
      if(typeid(*bp) == typeid(Derived))
      {
            //bpʵ��ָ��Derived�Ķ���
      }
   
     �ܽ᣺
     typeid�Ƿ���Ҫ����ʱ�������˱��ʽ�Ƿ�ᱻ��ֵ
     ֻ�е����ͺ����麯��ʱ���������Ż�Ա��ʽ��ֵ
     ��֮��������Ͳ������麯��
     ��typeid���ر��ʽ�ľ�̬����(����������Ա��ʽ��ֵҲ��ֱ�����ʽ�ľ�̬����)
   
   
     ������
     class Base
     {
            friend bool operator(const Base&,const Base&);
        public:
            //Base�Ľӿڳ�Ա
        protected:
            virtual bool equal(const Base&)const;
     }

     class Derived : public Base
     {
        public:
            //Derived�������ӿڳ�Ա
        protected:
            bool euqal(const Base&)const;
            //Derived�����ݳ�Ա����������ʵ�ֵĳ�Ա
     }

     //�������������������� �Ƚ��������м̳й�ϵ����
     bool operator==(const Base& lhs,const Base& rhs)
     {
        //���typeid����ͬ������false ���������equal
        return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
     }
     �����������У���������������Ͳ�ͬ����false
     �����ͬ �������������ί�и��麯��equal
     �����������Base����ʱ������Base::euqal
     �����������Derived����ʱ������Derived::equal

     bool Derived::euqal(const Base& rhs)const
     {
        //���������������ȣ�����ת�������׳��쳣(������һ������ת���Ǳز����ٵ�)
        auto r = dynamic_cast<const Derived&>(rhs);
        //ִ�����������ת��֮�󣬵�ǰ�������ܷ���rhs�����г�Ա ����ֻ�ܷ��ʻ����Ա
        //ִ�бȽ�����Derived����Ĳ��������ؽ��
     }
     bool Base::equal(const Base& rhs)const
     {
        //ִ�бȽ�Base����Ĳ���
     }

     1����operator==�����У�����Base&�β������н��գ������ָ�����ָ�������� ���ǿ��Ե�
     2������typeid���ж�̬���ͷ��� (�����麯������) ��ȷ
     3������lhs���麯�� ���ݶ�̬�󶨹��� �����ʵ�ʶ�̬��������ͽ��е��� ��ȷ
     4��rhs����һ�������ָ������� �����ֲ��������ϲ��� ��˲��ܷ�������������г�Ա
        �����Ҫʹ��dynamic_cast����ת��Ϊ�������ָ�� ���Է�������������г�Ա

3��ö������
   ���ࣺ
   �޶��������ö������ enum class name{}��
   ���޶��������ö������ enum name{}��

   Ĭ������£�ö��ֵ��0��ʼ��ÿ�μ�1 ����ʹ��=����ר�ŵ�ֵ
   ö��������const ���ɸı�

   enum class open_modes{input,output,append}; ����һ����Ϊopen_modes��ö������ ����3����Ա
   enum color{red,yellow,green}; ������һ�����޶��������ö������color

   color eyes = green; //��ȷ 
   color hair = color::red; //��ȷ ������ʽ�ķ��ʸó�Ա

   open_modes list = green; //���� open_modes��ö�ٳ�Ա������Ч����������
   open_modes list = open_modes::input;//��ȷ ʹ��open_modes��input
   
   
   ����ƶ�enum�Ĵ�С��

   enum intValues : unsigned long long; //���޶������򣬱���ָ����Ա����

   enum intValues : unsigned long long   //���Ƽ̳еķ�ʽ
   {
        charTyp = 255.short Typ = 65535,
        longTyp = 429496725UL
   };

   //�����޶��������ö�٣�����Ĭ�ϴ�СΪint


4����Աָ��

   ��Աָ����������Ա�������࣬��˱�����*ǰ�����classname::
   ������ʾ��ǰ�����ָ�����ָ��classname�ĳ�Ա  �ص㣡����

   (1)���ݳ�Աָ��
   const string Screen::*pdata; //pdataָ��һ��Screen(�������߷ǳ���)�����string��Ա
   pdata = &Screen::contents;   //��pdtaָ��ĳ�����ض�Screen�����contents��Ա
   ���� ��ȡ��ַ�������������ĳ�Ա������ʵ��������

   ��ǰ��������Ϊһ�䣺
   auto pdata = &Screen::contents;

   ʹ�����ݳ�Աָ�룺.* and ->*
   Screen myScreen;
   *pScreen = &myScreen;
   auto s = myScreen.*pdta;
   s = pScreen->*pdata;
   �����ִ������������
   1�����Ƚ����ó�Աָ���Եõ�����ĳ�Ա
   2��Ȼ�����Ա���������һ����ͨ��.����->����ȡ��Ա

   �������ݳ�Աָ��ĺ�����
   (��Ϊ������ݳ�Աһ����˽�е�)
   class Screen
   {
        //data��һ����̬��Ա ����һ����Ա��ָ��
        static const string Screen::* data()
        {
            return &Screen::contents;
        }
   }
   //data���ص���һ��ָ��Screen���const string��Ա��ָ�루ע����������Ƕ��� ��˽���������Ϊ��̬�ģ�

   (2)��Ա����ָ��

      ָ���Ա������ָ�����ָ��Ŀ�꺯���ķ������ͺ��β��б� 
      �����Ա������const��Ա�������ó�Ա �����Ǳ��뽫const�޶����������޶�����������
      ������
      char (Screen::*pmf)(Screen::pos,Screen::pos)const;
      pmf = &Screen::get;
      //pmf2�ǳ�Ա����ָ�� Screen::*�ǳ�Ա����ָ������� char�Ǻ������ص����� �뺯��ָ���������������ڶ���Screen::*

      Screen myScreen;
      *pScreen = &myScreen;
      char c = (pScreen->*pmf)(0,0); //ͨ��pScreen����ʵ��0,0�����������βε�get����
      �����Ǳز����ٵ�

      ���ͱ�����
      using Action = char (Screen::*)(Screen::pos,Screen::pos)const;
      Action get = &Screen::get; //Action��ָ��Screen��ĳ�����Ա������ָ��

      Screen& action(Screen&,Action = &Screen:grt);
      //action����һ��Screen������ ��һ��ָ��Screen��Ա������ָ��

      ���ã�
      action(myScreen);             //ʹ��Ĭ���β�
      action(myScreen,get);         //ʹ��getҲ���Ǻ���ָ��
      action(myScreen,&Screen::get);//��ʽ�Ĵ����ַ

      ��Ա����ָ���

      class Screen
      {
        public:
            Screen& home();    //��Ϊ����ƶ�����
            Screen& forward();
            Screen& back();
            Screen& up();
            Screen& down();

            //Action��һ��ָ�� ����������һ������ƶ��������丳ֵ
            using Action = Screen& (Screen::*)();
            //ָ�������ƶ��ķ��� 
            enum Directions{HOME,FORWARD,BACK,UP,DOWN};// 0 1 2 3 4 
            Screen& move(Directions);
        private:
            static Action Menu[]; //��Ա����ָ���
            //����Menu���α���ÿ������ƶ�������ָ��
      }
      Screen::Action Screen::Menu[] = {&Screen::home,&Screen::forward,&Screen::back,
      &Screen::up,&Screen::down};

      Screen& Screen::move(Directions cm)
      {
            //����this����������ֵΪcm��Ԫ��
            return (this->*Menu[cm])();;//Menu[cm]ָ��һ����Ա����
      }
      ����ԭ����ȡ����ֵΪcm��MenuԪ�� ��Ԫ����ָ��Screen��Ա������ָ��
                ����this��ָ��Ķ�����ø�Ԫ����ָ�ĳ�Ա����
      
      ���ã�
      Screen myScreen;
      myScreen.move(Screen::HOME);
      //Screen::HOME��ö������Directions�еĵ�һ��Ԫ�� ֵΪ0
      //����this->*Menu[0]() Ҳ���ǽ�����home������ָ�� �õ�home���� ����home()

      ʹ��function����һ���ɵ��ö���

        ��Աָ�벻��һ���ɵ��ö���������ָ�벻֧�ֺ������������ 
        ����ʹ��functionģ��ת��Ϊ�ɵ��ö���

        function<bool (const string&) > fcn = &string::empty;
        find_if(svec.begin(),svec.end(),fcn);
        //����functionģ����߱����� empty��һ������string����������boolֵ�ĺ���

        �����Ƕ���һ��function����ʱ������ָ���ö������ܱ�ʾ�ĺ������� ���ɵ��ö������ʽ
        ����ɵ��ö�����һ����Ա���� ���һ���βα����ʾ�ó�Ա�����ĸ�������ִ�е�
        ͬʱ �����ṩ��function����ʽ�л�����ָ�������Ƿ���ָ������õ���ʽ����
        ������
        vector<string*>pvec;
        function<bool (const string*)>fp = &string::empty;
        //�����ƶ�function����string*ָ�� ��pvec�Ĵ洢����һ��
        find_if(pvec.begin(),pvec.end(),fp);

    C++֧�ּ��ֹ��еĲ�����ֲ�����ԣ�����λ���volatileʹ�ó�������׷���Ӳ��
    ����ָʾʹ�ó�������׷������������Ա�д�Ĵ���

   */