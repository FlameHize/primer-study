/*
1���������������ݳ��� �̳� ��̬��
	
   ���ݳ��󣺽���Ľӿ���ʵ�ַ���
   �̳У��������Ƶ����Ͳ��������ƹ�ϵ��ģ
   ��̬�󶨣���һ���̶��Ϻ�������������𣬶���ͳһ�ķ�ʽʹ�����ǵĶ���
   
   ���飺����ͨ����Ӧ�ö���һ����������������ʹ�ú�����ִ���κ�ʵ�ʲ���Ҳ�����
  
   ��������ѭ����Ľӿ�
   ÿ���ฺ������ԵĽӿڣ�Ҫ������Ķ��󽻻�����ʹ�ø���Ľӿڣ���ʹ���������������Ļ��ಿ��Ҳ��һ��
   ��ˣ������಻��ֱ�ӳ�ʼ������ĳ�Ա�����ܴ��﷨������˵������ô����
   ��ʹ�û������������һ����������Ӧ����ѭ����Ľӿڣ�����ͨ�����û���Ĺ��캯������ʼ����Щ�ӻ����м̳ж����ĳ�Ա


2�����ࡢ�������붯̬��   
   
   (1)��������������
      
      ��C++�У�������뽫�������ֳ�Ա�������ֿ���
      
      һ���ǻ���ϣ������������и��ǵĺ���
      
      ͨ�����䶨��Ϊ�麯�� �ڳ�Ա����ǰ�����virtual�ؼ���
      (virtual�ؼ���ֻ�ܳ��������ڲ����������֮ǰ�����������ⲿ�ĺ�������)
      ������ʹ��ָ������õ��ø��麯��ʱ���õ��ý���̬�󶨣��������û�ָ�����󶨵����Ͳ�ͬ
      �õ��ÿ���ִ�л���İ汾��Ҳ����ִ��ĳ��������İ汾
      
      C++11�±�׼������������ʽ��ע������ʹ���ĸ���Ա������д������麯��
      �����ʩ���ڸú������β��б�֮������һ��override�ؼ���
      
      �������Ա���������override�ؼ��֣���ע��ʽ�̳��麯��
      �ùؼ��ֵ�����һ�����ã�
        ��������ඨ����һ��������������麯����������ͬ�����β��б�ͬ
        ����Ȼ�ǺϷ�����Ϊ�����Ǳ���������Ϊ����¶������������������ԭ�еĺ������໥������
        ���ǣ�������ĺ�����û�и��ǵ�����İ汾(�ܴ���ܷ�������)(���Ǻ��ѷ����Լ�����)
        �������ʹ��override������ĳ�����������ú�����û�и����Ѵ��ڵ��麯������ʱ������������

      
      ��һ���ǻ���ϣ��������ֱ�Ӽ̳ж���Ҫ�ı�ĺ���
      

      ������Ĺ��캯����

        ����������������к��дӻ���̳ж����ĳ�Ա�����������ಢ����ֱ�ӳ�ʼ��
        ��Щ��Ա�����������ʹ�û���Ĺ��캯������ʼ�����Ļ��ಿ��
        ������
        Buik_quote(const string& book, double p, size_t qty, double disc):
        Quote(book,p),min_qty(qty),discount(disc){}
        ���ȹ������Ĳ��֣�Ȼ����������˳�����γ�ʼ��������ĳ�Ա
   
   (2)��������󵽻������ʽת��
      
      ��������һ�����������Ϊһ����������ʼ�����߸�ֵʱ��ֻ�и�����������е�
      ���ಿ�ֻᱻ�������ƶ����߸�ֵ�����������ಿ�ֽ��ᱻ���Ե�

      ������
      Quote item;
      Bulk_Quote bulk;
      Quote* p = &item;   pָ��Quote����
      p = &bulk;          pָ��bulk��Quote����
      Quote& r = bulk;    r�󶨵�bulk��Quote����


      ��̬�󶨣����ǿ��Խ������ָ������ð󶨵������������
      �Ҵ�����������������ת��ֻ��ָ���������������Ч
      (������ʹ�û����ָ�������ʱ��ʵ�������ǲ������
      �����û���ָ�����󶨶������ʵ���ͣ��ö�������ǻ���Ķ���Ҳ������������Ķ���)
   
      Ϊʲô���Խ������ְ󶨣�
      ԭ����Ϊÿ����������󶼰���һ�����ಿ�֣�����������û���ָ����԰󶨵��û��ಿ����

      Ҳ��ˣ������ڴӻ��������������ʽ����ת��(�������ǿ��ܻ�ʹ��������ָ����ʻ����в����ڵĳ�Ա)

   (3)�̳��뾲̬��Ա
      
      ������ඨ����һ����̬��Ա����ô�������̳���ϵ��ֻ���ڸó�Ա��Ψһ����
      ���۴ӻ����������������ٸ������࣬����ÿ����̬��Ա��˵��ֻ����Ψһ��ʵ��

      ������
      class Base
      {
        public:
            static void statmem();
      }
      class Dervied : public Base
      {
        void f(const Dervied&);
      }
      
      void Dervied::f(const Dervied& dervied_obj)
      {
        Base::statmem();      ��ȷ Base������statmem
        Dervied::statmem();   ��ȷ Derived������statmem   
        dervied_obj.statmem();��ȷ ͨ��Derived�������
        statmem();            ��ȷ ͨ��this�������
      }
   
   (4)��η�ֹ�̳еķ�����
      �������������final�ؼ���
      ���ǵ�ȻҲ���԰�ĳ����������Ϊfinal
      ��������Ѿ��Ѻ��������final����
      ��֮���κγ��Ը��ǵ��ú����Ĳ������������������

   (5)�麯����Ĭ��ʵ��
      
      ���ĳ�κ�������ʹ����Ĭ��ʵ�Σ����ʵ��ֵ�ɱ��ε��õľ�̬���;���
      ���仰˵�����붯̬��˼����Υ��
      �������ͨ�������ָ������õ����˺�������ʹ�û����ж����Ĭ��ʵ��
      ��ʹʵ�����е���������ĺ����汾(������ǻ����Ĭ��ʵ�ζ����Ƕ�̬�󶨵�������)
      
      ���飺��ò�Ҫʹ��Ĭ��ʵ�� (�麯����Ҫʹ�õĻ�,�������������ж����Ĭ��ʵ�����һ��)


      ��λر��麯���Ļ���? ʹ�������������������ʽ����
      double undiscounted = baseP->Quote::net_price(42);
      

3���������--���ݳ���

   ������ࣺ��ʾһ������ĸ������ֱ�Ӵ��������ʵ������
             Ҳ���ǲ��ܴ����������Ķ���

   ʲô�������ǳ�����ࣿ
   �𰸣�����(����δ������ֱ�Ӽ̳�)���麯�������ǳ������

   ���麯����һ��������������û�ж�����麯�����ڷֺ�֮ǰ�� =0 ����
   (���麯��ֻ�ܳ��������ڲ���������)
   ������virtual double net_price(size_t )const  = 0;
   
4�����ʿ��ƺͼ̳�
   
   ĳ�������̳ж����ĳ�Ա�ķ���Ȩ������������Ӱ��
     1���ڻ����иó�Ա�ķ���˵���������������Ա�ڲ��Ը������ݵķ���Ȩ�ޣ�
     2����������������б��еķ���˵���������������ⲿ�û����ڸ����Ա�ķ���Ȩ�ޣ�

   (1)protected:

    ������Щϣ��������������ǲ��뱻������������ʹ�õĳ�Ա
    (��˽�г�Ա���ƣ��ܱ����ĳ�Ա��������û���˵�ǲ��ɷ��ʵ�
    �͹��г�Ա���ƣ��ܱ����ĳ�Ա����������ĳ�Ա����Ԫ��˵�ǿɷ��ʵ�)
    
    ������ĳ�Ա����Ԫֻ��ͨ����������������ʻ����protected��Ա
   
   (2)���С�˽�кͱ����̳�
            
      ���м̳У���Ա����ѭ��ԭ�е����ڷ���˵���� ������ �ص�
      (���м̳��У������෴ӳ�����ġ���һ�֡���ϵ Ҳ����IS A)
      
      ˽�м̳У�������ļ̳ж����ĳ�Աȫ������˽�е�

      �����̳У�����ĵ����й��г�Ա��������������˵�����ܱ�����
      
      ��Ԫ��ϵ�����Լ̳�

      ������
      class Base
      {
        public:
            void pub_num();
        protected:
            int prot_num;
        private:
            char priv_num;
      }
      struct Pub_Derv : public Base
      {
        inf f() { return prot_num;}  //��ȷ �������ܹ����ʸ���protected��Ա
        char g() { return priv_num;} //���� �����಻�ܷ��ʻ����private��Ա
      }
      struct Priv_Derv : private Base
      {
        inf f1() { return prot_num;}  //��ȷ �������ܹ����ʸ����protected��Ա
                                      //private�̳�����������ڲ�����Ȩ���޹�
      }

      ע�����ڲ������ⲿ������ һ���ǳ�Ա һ�����û�

      ��������ڲ���Ա������Ԫ���ܷ������ֱ�ӻ���ĳ�Ա
      ֻ������Ա�ķ���˵�����йأ����������б�ķ���˵�����޹�

      ��������˵������Ŀ�ģ�
      ������������ⲿ�û�������������������ࣩ
      ���ڻ����Ա�ķ���Ȩ��

      Pub_Derv d1;   public�̳�Base
      Priv_Derv d2;  private�̳�Base
      d1.pub_num();  ��ȷ pub_num������������public��
      d2.pub_num();  ���� pub_num������������private��

      �����������ת���Ŀɷ����ԣ�
      ֻ�е�D���еļ̳�Bʱ���û��������ʹ��������������ת��
      ����D��ʲô��ʽ�̳�B��D�ĳ�Ա��������Ԫ����ʹ��������������ת��


      �ܽ�(�ص�)��

      �����Ǽ̳еĻ���
        һ������������ͬ���û�����ͨ�û������ʵ����
         ��ͨ�û�����д�Ĵ���ʹ����Ķ���(��ʹ�÷�װ�õ�STL)
                   �ⲿ�ִ���ֻ�ܷ�����Ĺ���(�ӿ�)��Ա
         ���ʵ���ߣ������д��ĳ�Ա����Ԫ�Ĵ��� 
                     ��Ա����Ԫ���ܷ�����Ĺ��в��֣�Ҳ�ܷ������˽��(ʵ��)���֣�һ�㽫�õ������ݱ�������Ϊ˽�еģ���ֹ�ⲿ���ʺʹ۸ģ�
      
      ���Ǽ̳еĻ��� 
        ���ֵ������û� ��������
         �����ࣺ�������ϣ���������ܹ�ʹ�õĲ�������Ϊ������
                 ��ͨ�û����ܷ����ܱ����ĳ�Ա���������༰����Ԫ�Ծɲ��ܷ��ʻ����˽�г�Ա����Ϊ��Ҫ���ʵĶ���Ƴ�protected��
      
      ��ˣ�һ������Ӧ��������
        ���ӿڳ�Ա����Ϊ���е�
        ��������ʵ�ֵĲ��ֳַ����飺
             �ɹ���������ʣ�����Ϊ�ܱ�����
             ֻ���ɻ��༰����Ԫ���ʣ�����Ϊ˽�е�
      
      ��������б����˵�������������Ϊ���м̳У����ı�����ڲ�ԭ�еķ���˵����

      
      ���⣺��θı�����Ա�Ŀɷ����ԣ�
      �𰸣�ʹ��using˵��

      class Base
      {
        public:
            size_t size() const{ return n;}
        protected:
            size_t n;
      }
      class Derived : private Base
      {
        public:
            using Base::size;
        protected:
            using Base::n;
      }

      ��Ϊʹ����˽�м̳У����Լ̳еĳ�Աsize��n��Ĭ���¶���
      ������Derived��˽�г�Ա 
      ͨ��������ڲ�ʹ��using������䣬���Ըı��Ա�Ŀɷ�����
      Derived���ⲿ�û�������ʹ��size��Ա 
      ��Derived�������ཫ�ܹ�ʹ��n

5���̳��е���������
   
   (1)���򣺵����ڼ̳й�ϵʱ���������������Ƕ����������������֮��
         ���һ������������������������޷���ȷ������������������������Ļ�����������Ѱ�Ҹ����ֵĶ���
         (�ؼ����������������������������)
   
   (2)���ֲ��ҵ�ʱ�䣺�ڱ���ʱ�������ֲ���
       ��ˣ�һ���������û���ָ��ľ�̬���;����˸ö������Щ��Ա�ǿɼ��ġ�
       ��ʹ��̬�����붯̬���Ϳ��ܲ�һ�£�����������ʹ�����ֳ�Ա��Ȼ���ɾ�̬���;�����
       ������
       class Disc_quote : public Quote
       {
        public:
            pair<size_t,double> discount_policy()const
                { return {quantity,discount};}
       };

       Bulk_quote bulk;
       Bulk_quote* bulkp = &bulk; //��̬�����붯̬����һ��
       Quote* itemP =  &bulk;     //��̬�����붯̬���Ͳ�һ��
       bulkP->discount_policy();  //��ȷ
       itemP->discount_policy();  //����

       (Quote->Disc_quote->Bulk_quote)
       itemP   discount_policy()   bulk
       ������bulk��ȷʵ�� һ��discount_policy�ĳ�Ա��
       ���Ǹó�Ա�������ӻ���-Quote itemP�ǲ��ɼ���
       itemP�ľ�̬������Quote��ָ��
       ��˶�discount_policy����������Quote��ʼ �Ҳ��� ����������
       (���ֲ���ֻ�����ϲ��� ���������²���)
   
   (3)���ֳ�ͻ
       �������ڲ�������(������)�����ֻ����ض��������������(����)�е�����
       ����û���Ļ�����ͨ����ʽ����������������е���

       ������
       class Base
       {
          int memfcn();
       }
       class Derived : public Base
       {
          int memfcn(int);
       }
       Derived d,Base b;
       b.memfcn();
       d.memfcn(10);
       d.memfcn();          ���� �����б�Ϊ�յ�memfcn��Ա��������
       d.Base::memfcn();    ��ȷ ����Base::memfcn

       Ϊ�˽���d.memfcn()������䣬������������Derived�в�������memfcn
       ��ΪDerivedȷʵ������һ����Ϊmemfcn�ĳ�Ա ���Բ��ҹ���ֹͣ
       һ�������ҵ����������Ͳ��ټ���������
       Derived��memfcn�汾��Ҫһ��intʵ�Σ�����ǰ�ĵ�������޷��ṩ�κ�ʵ��
       ���Ըõ�������Ǵ����

       Ҳ��Ϊ������ֳ�ͻԭ�����Ի�������������麯����������ͬ���β��б�
       (����б�ͬ�����麯���ᱻ���ص�)


   (4)�ܽ�Ĺؼ�����--���ֲ�����̳�
      
      �����ּ�飬�����ͼ�飬�ٿ��Ƿ����麯������

      ���裺(����p->mem() / obj.mem())

      1������ȷ��p��obj�ľ�̬����
      2����p��obj�ľ�̬���Ͷ�Ӧ�����в���mem������Ҳ�������������ֱ�ӻ����в��ϲ���ֱ���ﵽ�̳����Ķ��ˣ�����ұ��˸��༰�������Ȼ�Ҳ������������������
      3��һ���ҵ�mem���ͽ��г�������ͼ��(�������͡��������͵�)����ȷ�϶��ڱ����ҵ���mem,���ε����Ƿ�Ϸ�
      4�����úϷ� �����ж�
          (1)���mem���麯�� �� ��ͨ��ָ������ý��еĵ���
             ����������ݶ������еĶ�̬����ȷ�������麯�����ĸ��汾
          (2)���mem�����麯������������ͨ��������������û�ָ����еĵ���
             �����һ�����溯���ĵ���
             ��ע������� �� �� ��

6�����캯���뿽������

   (1)����������
      �������������Ӧ�ö����������������ȷ����̬����ִ����ȷ�����������汾��
      ȷ������delete����ָ��ʱ��������ȷ�����������汾

      ������
      Quote* itemP = new Quote;   //��̬�����붯̬����һ��
      delete itemP;               // ����Quote����������
      itemP = new Bulk_quote;     //��̬�����붯̬���Ͳ�һ��
      delete itemP;               //����Bulk_quote����������
      (���������������������麯������deleteһ��ָ�����������Ļ���ָ�뽫�����δ�������Ϊ)

      ��Quote�̳���ϵ�У������඼ʹ��Ĭ�ϵĺϳ���������������
      ��������ʽ��ʹ�ö�����ͨ�����������������=delfault����ʽ��ʹ��
      ���������������������˵�������������������Լ��ĳ�Ա�⣬�����������������ֱ�ӻ���
      ��ֱ�ӻ������������Լ���ֱ�ӻ��࣬�Դ�����ֱ���̳����Ķ���
      ����������ֻ���������������Լ��������Դ��

      ����˳���빹���෴����������������ִ�У�Ȼ���ǻ��������
      �Դ����ƣ����ż̳���ϵ�ķ�����ֱ����ֹ
      ����Ϊ����ʱ��ǰ�����⣬����������Ƕ���Ĺ��������������������ĳ���麯��
      ������Ӧ��ִ���빹�캯�����������������������Ӧ���麯���汾��

   (2)��������ɾ���Ŀ������������Ĺ�ϵ
       
       ��������е�Ĭ�Ϲ��졢�������졢�ƶ����졢������ֵ���������������
       �Ǳ�ɾ���ĺ����򲻿ɷ��ʣ����������ж�Ӧ�ĳ�Ա��ɾ����

       �����������һ�����ɷ��ʻ���ɾ�����������������������кϳɵ�
       Ĭ�ϺͿ������졢�ƶ����캯����ɾ���ģ���Ϊ�������޷��������������Ļ��ಿ��

       ���һ���ඨ�����Լ��Ŀ������캯����������ֵ�����������������
       �������Ͳ���Ϊ���ϳ��ƶ����캯�����ƶ���ֵ������� 
       ����ڼ̳���Ҳһ�����������ɾ�����Լ�����ʽ�������죬��������û������
       �����Լ����ƶ�������߿������� �������಻�ܽ��п������ƶ�
       
       ������һ���ƶ����캯�����ƶ���ֵ������������Ҳ�����Լ��Ŀ�������
       ������Щ�ƶ��Ĳ���Ĭ�ϵı������ɾ����

       ��õķ�����ȫ��Ĭ�϶������  ������������
       class Quote
       {
        public:
            Quote() = default;                       �Գ�Ա����Ĭ�ϳ�ʼ��
            Quote(const Quote&) = default;           �Գ�Ա���ο���
            Quote(Quote&&) = default;                �Գ�Ա�����ƶ�����
            Quote& operator=(const Quote&) = default;������ֵ
            Quote& operator=(Quote&&) = default;     �ƶ���ֵ
            virtual ~Quote() = default;              ������
       }
       ����Quote���������к����ų��ƶ��ĳ�Ա�����������Զ��Ļ�úϳɵ��ƶ�����

   (3)������Ŀ������Ƴ�Ա

      �������ඨ���˿��������ƶ�����ʱ���ò������𿽱����ƶ��������ಿ�ֳ�Ա���ڵ���������
      ����ͨ����������Ĺ��캯����ʼ���б���ʹ�û���Ĺ��캯������ʼ������Ļ��ಿ��

      class Base;
      class D : public Base
      {
        public:
            D(const D& d) : Base(d),/D�Լ�����ĳ�Ա��ʼ��/
            D(D&& d) : Base(std::move(d)),/D�Լ�����ĳ�Ա��ʼ��/
      }
      D���͵Ķ���d�����󶨵��ù��캯����const Base&�βλ���Base&&�β�
      Base�Ŀ�����������ƶ����캯������d�Ļ��ಿ�ֽ��п��������ƶ���ʼ������

      ͬ���ģ�������ĸ�ֵ�����Ҳ������ʽ��Ϊ���ಿ�ָ�ֵ
      D& D::operatr=(const D& rhs)
      {
            Base::operator=(rhs); //��ʽ��Ϊ���ำֵ
            //�������Լ��ĳ�Ա��ֵ
            //����
            return *this;
      }

   (4)�̳еĹ��캯��
      ֻ�ܼ̳�ֱ�ӻ���Ĺ��캯��
      �������ṩһ��ע����ֱ�ӻ�������using���
      class Bulk_quote : public Disc_quote
      {
        public:
            using Disc_quote::Disc_quote;  //�̳�Disc_quote�Ĺ��캯��
            double net_price(size_t) const;
      }
      ���ڻ����ÿ�����캯����������������һ����֮���ڵ������๹�캯��

      �ȼ���
      Bulk_quote(const string& book,double price,size_t qty,double disc)
      : Disc_quote(book,price,qty,disc){}

      ������������Լ������ݳ�Ա������Щ��Ա��Ĭ�ϳ�ʼ��


   */


//������������̽

/*

#include<iostream>
#include<string>
using namespace std;

class Quote
{
public:
    Quote() = default;
    Quote(const string& book,double sales_price):
        bookNo(book),price(sales_price){}
    string isbn() const { return bookNo; }
    virtual double net_price(size_t n)const //�麯���������ฺ���д��ʹ�ò�ͬ���ۿۼ��㷽��
    {
        return n * price;
    }
    virtual ~Quote() = default;   //����������������ж�̬��
       
private:
    string bookNo;
protected:
    double price = 0.0;
};

class Bulk_quote : public Quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const string& book, double p, size_t qty, double disc):
        Quote(book,p),min_qty(qty),discount(disc){}

    double net_price(size_t)const override;
    //���ǻ���ĺ����汾��ʵ�ֻ��ڴ���������ۿ�����

private:
    size_t min_qty = 0;  //�����ۿ����ߵ���͹�����
    double discount = 0.0;  //��С����ʾ���ۿ۶�
};

double Bulk_quote::net_price(size_t cnt)const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

*/



//���ó����������ع�

/*

#include<iostream>
#include<string>
#include<memory>
#include<set>

using namespace std;

class Quote
{
public:
    Quote() = default;
    Quote(const string& book, double sales_price) :
        bookNo(book), price(sales_price) {}
    string isbn() const { return bookNo; }
    virtual double net_price(size_t n)const //�麯���������ฺ���д��ʹ�ò�ͬ���ۿۼ��㷽��
    {
        return n * price;
    }
    virtual ~Quote() = default;   //����������������ж�̬��

private:
    string bookNo;
protected:
    double price = 0.0;
};

class Disc_quote : public Quote
{
public:
    Disc_quote() = default;
    Disc_quote(const string& book,double price,size_t qty,double disc):
        Quote(book,price),quantity(qty),discount(disc){}

    //���麯�� ������������ű�ʾ������ǳ������
    virtual double net_price(size_t) const = 0;

protected:
    size_t quantity = 0;  //�ۿ����õĹ�����
    double discount = 0.0; //��ʾ�ۿ۵�С��ֵ
};

class Bulk_quote : public Disc_quote //ֱ�ӻ���Disc_quote ��ӻ���Quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const string& book,double price,size_t qty,double disc):
        Disc_quote(book,price,qty,disc){}   //ע���ʼ�������ĸ���Ա(���������Լ���)

    //���ǵ������еĺ����麯���汾��ʵ��һ���µ��ۿ۲���
    virtual double net_price(size_t n)const override;
};

double Bulk_quote::net_price(size_t cnt)const
{
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}
//Bulk_quote�Ĺ��캯�������ĸ��������ù��캯��������ʵ�δ��ݸ�
//Disc_quote�Ĺ��캯�������Disc_quote�Ĺ��캯����������Quote�Ĺ��캯��
//Quote�Ĺ��캯�����ȳ�ʼ��bulk��bookNo��price��Ա����Quote�Ĺ��캯��������
//��ʼ����Disc_quote�Ĺ��캯������ʼ��quantity��discount��Ա
//�������Bulk_quote�Ĺ��캯�����ú�������ִ��ʵ�ʵĳ�ʼ������������

//�ٶ���һ����ʾ���������� ��������������һЩ����
class Basket
{
public:
    void add_item(const shared_ptr<Quote>& sale)
    {
        items.insert(sale); //�̺���̬�󶨼��� ���Խ��������ָ���Զ�ת��Ϊ�����ָ��
    }
    //��ӡÿ������ܼۺ͹������е�����ܼ�
    double total_receipt(ostream&)const;
private:
    //�ȽϺ��������һ����̬���� ���е�ʵ�����඼ֻ����һ�����бȽ�
    static bool compare(const shared_ptr<Quote>& lhs, const shared_ptr<Quote>& rhs)
    {
        return lhs->isbn() < rhs->isbn();
    }
    multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
    //��ʼ����Ҫ�����������ĺ���ָ�벢�ø�ָ����������ĳ�ʼ��
    //�������Ҷ�������䶨����һ��ָ��Quote�����shared_ptr��mulitset
    //���multiset��ʹ��һ����compare��Ա������ͬ�ĺ����������е�Ԫ�ؽ�������
    //multiset��Ա��������items����ʼ��items������ʹ��compare����
};
double print_total(std::ostream& os, const Quote& item, size_t n)
{
    double ret = item.net_price(n);

    os << "ISBN:" << item.isbn()
        << "# sold: " << n << " total due: " << ret << std::endl;

    return ret;
}


double Basket::total_receipt(ostream& os)const
{
    double sum = 0.0;
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
    {                                                      //����upper_bound���������������뵱ǰ�ؼ�����ͬ������Ԫ��,����һ��������ȵ�Ԫ��֮��һ��λ�õĵ�����
        sum += print_total(os, **iter, items.count(*iter));//Ҳ����ָ����һ���鼮
    }                           //�����õõ�Quote������������� ���ö�̬��
    os << "Total Sale:" << sum << endl;
    return sum;
    //shared_ptr�ĵ�ַ�����ָ����ͬ�Ķ��� ����ͬ�� ��˿���ͨ��*iter���ж�
}

int main()
{
    Basket basket;

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(make_shared<Bulk_quote>("Bible", 20.6, 20, 0.3));

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(make_shared<Bulk_quote>("C++Primer", 30.9, 5, 0.4));

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(make_shared<Quote>("CLRS", 40.1));

    
    basket.total_receipt(cout);
    return 0;
}

*/



/*
//�ı���ѯ����2.0�汾 ֧���߼������ 1.0�汾��ch12

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
    os << qr.sought << "occurs" << qr.lines->size() << endl;  //qr.lines��һ��ָ��set<line_no>������ָ��
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


//֮ǰ��1.0�汾���� ��������ѯ����֧�ֲ�ͬ�������



//����һ��������࣬����Ĳ�ѯ���ʹ������������еĳ�Ա����˽�е�
class Query_base
{
    friend class Query;
    //��Ϊ���ǲ�ϣ���û��������������ֱ��ʹ��Query_base ������û��public��Ա
protected:
    typedef TextQuery::line_no line_no;
    virtual ~Query_base() = default;
private:
    //eval�����뵱ǰQueryƥ���QueryResult
    virtual QueryResult eval(const TextQuery&)const = 0;
    virtual string rep() const = 0; //���ɲ�ѯ��string�ı�
};

//����һ������Query_base�̳���ϵ�Ľӿ���
class Query
{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const string&); //����һ���µ�wordQuery

    QueryResult eval(const TextQuery& t)const 
    { return q->eval(t); }
    string rep()const { return q->rep(); }
    //����ӿں��������ö��ڵ�Query_base����

private:
    
    Query(shared_ptr<Query_base>query) : q(query){}
    //��������ָ����г�ʼ���Ĺ��캯��
    //Query����ʹ������Query_baseָ�������ø��Ե�Query_base�麯��
    //ʵ�ʵ����ĸ������汾����q��ָ��Ķ������;���(��̬�󶨼���)
    shared_ptr<Query_base>q; //ÿ��Query���󶼰���һ��ָ��Query_base���������ָ��
};



//Query����������
ostream& operator<<(ostream& os, const Query& query)
{
    return os << query.rep();
}


//wordQuery����������ʵ��
class WordQuery : public Query_base
{   
    //�޹��г�Ա
    friend class Query; //���ýӿ����򻯴���
    WordQuery(const string& s) : query_word(s){}
    //WordQuery��һ��������� ��˽��������м̳ж����Ĵ��麯��
    QueryResult eval(const TextQuery &t)const
    {
        return t.query(query_word);
    }
    string rep() const { return query_word; }
    string query_word;  //Ҫ���ҵĵ���
};

inline Query::Query(const string& s) : q(new WordQuery(s)) { }

class NotQuery : public Query_base
{
    friend Query operator~(const Query&);
    NotQuery(const Query& q) :query(q){}

    //������� NotQuery���������м̳ж����Ĵ��麯��
    string rep()const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery& t)const;
    
    Query query;
};

inline Query operator~(const Query& operand)
{
    return shared_ptr<Query_base>(new NotQuery(operand));
    //���return�����ʽ��ʹ�ý���һ��shared_ptr<Query_base>��Query���캯��
}

class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query& l, const Query& r, string s):
        lhs(l),rhs(r),opSym(s){}
    //�����࣬BinaryQuery������eval
    string rep() const 
    {
        return "(" + lhs.rep() + " "+ opSym + " " + rhs.rep() + ")";
    }
    //��rep�ĵ��������Ƕ�rhs��lhs��ָQuery_base�����rep�����ĵ���
    Query lhs, rhs;//�����Ҳ��������
    string opSym;  //�����������
};

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query&, const Query&);
    
    AndQuery(const Query& left, const Query& right) :
        BinaryQuery(left, right, "&"){ }

    //������� AndQuery�̳���rep���Ҷ������������麯��
    QueryResult eval(const TextQuery&)const;
};

inline Query operator&(const Query& lhs, const Query& rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
    //return��为��shared_ptrת����Query
}
//���������������һ�����캯��ͨ�����������BinaryQuery�Ļ��ಿ��
//���Ƕ��̳���BinaryQuery��rep���� ���Ǹ�����eval����

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query&, const Query&);

    OrQuery(const Query& left, const Query& right) :
        BinaryQuery(left, right, "|") { }

    //������� AndQuery�̳���rep���Ҷ������������麯��
    QueryResult eval(const TextQuery&)const;
};

inline Query operator|(const Query& lhs, const Query& rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}


int main()
{
    ifstream file("C:\\Users\Administrator\Desktop\123.docx");
    runQueries(file);
}
*/