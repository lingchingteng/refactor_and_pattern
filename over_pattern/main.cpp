#include <string>
#include <iostream>

class DefaultFactory;
class MessageStrategy;
class MessageBody;

class MessageBody
{
public:
    std::string getPayload()
    {
        return mPayLoad;
    }
    void configure(std::string payload)
    {
        mPayLoad = payload;
    }
    void send(MessageStrategy *ms);
    MessageBody(){};
    ~MessageBody(){};

private:
    std::string mPayLoad;
};

class MessageStrategyBase
{
public:
    virtual void sendMessage(){};
    MessageStrategyBase(){};
    ~MessageStrategyBase(){};
};

class MessageStrategy : MessageStrategyBase
{
public:
    MessageStrategy(MessageBody *mb)
    {
        mBody = mb;
    };
    void sendMessage()
    {
        std::string m = mBody->getPayload();
        std::cout << m << std::endl;
    };
    MessageStrategy(){};
    ~MessageStrategy(){};

private:
    MessageBody *mBody;
};

void MessageBody::send(MessageStrategy *ms)
{
    ms->sendMessage();
}

class AbstractStrategyFactory
{
public:
    virtual MessageStrategy createStrategy(MessageBody mb) = 0;
    AbstractStrategyFactory() = default;
    ~AbstractStrategyFactory() = default;
};

class DefaultFactory : AbstractStrategyFactory
{
public:
    MessageStrategy createStrategy(MessageBody mb)
    {
        return MessageStrategy(&mb);
    }
    static DefaultFactory *getInstance()
    {
        if (sInstance == nullptr)
        {
            sInstance = new DefaultFactory();
        }
        return sInstance;
    }
    ~DefaultFactory(){};

private:
    static DefaultFactory *sInstance;
    DefaultFactory(){};
};
DefaultFactory *DefaultFactory::sInstance = NULL;

int main(int argc, char const *argv[])
{
    MessageBody mb = MessageBody();
    mb.configure("Hello, World!");
    AbstractStrategyFactory *asf = (AbstractStrategyFactory *)DefaultFactory::getInstance();
    MessageStrategy ms = asf->createStrategy(mb);
    ms.sendMessage();
    return 0;
}
