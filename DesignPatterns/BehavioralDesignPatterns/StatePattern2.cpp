/*
 * @Author: xx xx@ubuntu.com
 * @Date: 2022-07-03 20:06:06
 * @LastEditors: xx xx@ubuntu.com
 * @LastEditTime: 2022-07-23 22:32:05
 * @FilePath: /DesignPatternsBasic/DesignPatterns/BehavioralDesignPatterns/StatePattern2.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// 1. 情景与意图
//   一个对象可以有很多的状态，不同的状态，对象就会有不同的行为。比如文件如果是只读的状态，那么就只能读不能写入，如果是只写的，那就不能读，再或者是读写的。在对象的状态改变时，其可以支持的行为也应该改变。
//   如何实现这个设计——状态模式。

// 2. 状态模式
//   允许对象在内部状态发生改变时改变它的行为，对象看起来好像修改了它的类。
//   其实就是说，不同状态不同行为切换。行为可以是表现形式，支持的时间等等。

// 3. 文件的状态
//   下面我们简单的实现一个场景。比如我们知道网络有WiFi，蜂窝，等等，对于应用程序来说，是离不开网络请求的。此时我们对于当前APP的网络状态做一个状态模式的实现。
//   状态模式的实现，就是将枚举的状态，抽象成对象。首先我们先定义状态。

#include <string>

class Context;

class DPNetworkState
{
public:
    virtual void doAction(Context* context) = 0;
    virtual std::string descriptionString() = 0;
};

// WIFI
class DPNetworkStateWIFI : public DPNetworkState
{
public:
    virtual void doAction(Context* context) override;
    virtual std::string descriptionString();
};


// 蜂窝
class DPNetworkStateCellular : public DPNetworkState
{
public:
    virtual void doAction(Context* context) override;
    virtual std::string descriptionString();
};


    
// 未知
class DPNetworkStateUnknow : public DPNetworkState
{
public:
    virtual void doAction(Context* context) override;
    virtual std::string descriptionString();
};


// // 举例其中一个具体实现
// std::string DPNetworkStateWIFI::descriptionString()
// {
//     return std::string("wifi");
// }
// void DPNetworkStateWIFI::doAction(Context* context) override
// {

// }

// 下面就是具有这些状态的具体对象，会根据状态的改变，改变其行为。
class Context
{
protected:
    DPNetworkState *pNetworkState;

public:
    void setNetworkState(DPNetworkState *networkState)
    {

    }
    void printState()
    {
        pNetworkState->descriptionString();
    }
};


void DPNetworkStateWIFI::doAction(Context* context)
{
    context->setNetworkState(this);
}
std::string DPNetworkStateWIFI::descriptionString()
{
    return std::string("wifi");
}




void DPNetworkStateCellular::doAction(Context* context)
{
    context->setNetworkState(this);
}
std::string DPNetworkStateCellular::descriptionString()
{
    return std::string("Cellular");
}



void DPNetworkStateUnknow::doAction(Context* context)
{
    context->setNetworkState(this);
}
std::string DPNetworkStateUnknow::descriptionString()
{
    return std::string("Unknow");
}


int main()
{
    Context* context = new Context();
    DPNetworkState *state = new DPNetworkStateWIFI();
    state->doAction(context);
    context->printState();

    state = new DPNetworkStateCellular();
    state->doAction(context);
    context->printState();

    state = new DPNetworkStateUnknow();
    state->doAction(context);
    context->printState();

    return 0;
}

// 4. 总结
//   状态模式就是先将状态抽象，然后将与状态关联的行为放在子状态类中，再状态切换时，切换与之相应的对象，只是维护一个抽象的接口。看着像对象内部在改变。
//   状态一定就是项目’网络demo‘的这种离散的，还有一种是有关联的状态的改变，比如状态变化后，到达另一个状态等。具体例子不在这里展示，见下方源码。

// https://blog.csdn.net/Void_leng/article/details/117402519