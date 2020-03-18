#include <iostream>
#include <map>
#include <functional>
using namespace std;
class Connections
{
public:
    //�����ơ�����ӳ���ϵ��
    void connect(const std::string &name, const std::function<void()> &callback)
    {
        m_callbackMap[name] = callback;
    }
    //�����ơ����á�
    void invok(const std::string &name)
    {
        auto it = m_callbackMap.find(name);
        //�������ж�
        if (it != m_callbackMap.end()) {
            //��������Ч�������ֱ�ӵ���
            it->second();
        }
    }
private:
    std::map<std::string, std::function<void()>> m_callbackMap;
};
//ȫ�ֹ����Connections��
static Connections s_connections;

//Tom�Ķ���
class Tom
{
public:
    //è��
    void Miaow()
    {
        cout << "��!" << endl;
        //����һ������Ϊmouse�Ļص�
        s_connections.invok("mouse");
    }
};
//Jerry�Ķ���
class Jerry
{
public:
    Jerry()
    {
        //���캯���У�����ӳ���ϵ��std::bind���ڻ����÷���
        s_connections.connect("mouse", std::bind(&Jerry::RunAway, this));
    }
    //����
    void RunAway()
    {
        cout << "��ֻè�����ˣ����" << endl;
    }

};
int main(int argc, char *argv[])
{
    //ģ��Ƕ�ײ㼶����ĳ������ⲿ����ֱ�ӷ��ʵ�tom
    struct A {
        struct B {
            struct C {
                private:
                    //Tom�ں���Ľṹ��
                    Tom tom;
                public:
                    void MiaoMiaoMiao()
                    {
                        tom.Miaow();
                    }
            }c;
            void MiaoMiao()
            {
                c.MiaoMiaoMiao();
            }
        }b;
        void Miao()
        {
            b.MiaoMiao();
        }
    }a;
    //ģ��Ƕ�ײ㼶����ĳ������ⲿ����ֱ�ӷ��ʵ�jerry
    struct D {
        struct E {
            struct F {
                private:
                    //jerry�ں���Ľṹ��
                    Jerry jerry;
            }f;
        }e;
    }d;

    //A��ӵ���tom��MiaoW������è����
    a.Miao();

    return 0;
}
