#include <iostream>
#include <map>
#include <functional>
using namespace std;
class Connections
{
public:
    //按名称“建立映射关系”
    void connect(const std::string &name, const std::function<void()> &callback)
    {
        m_callbackMap[name] = callback;
    }
    //按名称“调用”
    void invok(const std::string &name)
    {
        auto it = m_callbackMap.find(name);
        //迭代器判断
        if (it != m_callbackMap.end()) {
            //迭代器有效的情况，直接调用
            it->second();
        }
    }
private:
    std::map<std::string, std::function<void()>> m_callbackMap;
};
//全局共享的Connections。
static Connections s_connections;

//Tom的定义
class Tom
{
public:
    //猫叫
    void Miaow()
    {
        cout << "喵!" << endl;
        //调用一下名字为mouse的回调
        s_connections.invok("mouse");
    }
};
//Jerry的定义
class Jerry
{
public:
    Jerry()
    {
        //构造函数中，建立映射关系。std::bind属于基本用法。
        s_connections.connect("mouse", std::bind(&Jerry::RunAway, this));
    }
    //逃跑
    void RunAway()
    {
        cout << "那只猫又来了，快溜！" << endl;
    }

};
int main(int argc, char *argv[])
{
    //模拟嵌套层级很深的场景，外部不能直接访问到tom
    struct A {
        struct B {
            struct C {
                private:
                    //Tom在很深的结构中
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
    //模拟嵌套层级很深的场景，外部不能直接访问到jerry
    struct D {
        struct E {
            struct F {
                private:
                    //jerry在很深的结构中
                    Jerry jerry;
            }f;
        }e;
    }d;

    //A间接调用tom的MiaoW，发出猫叫声
    a.Miao();

    return 0;
}
