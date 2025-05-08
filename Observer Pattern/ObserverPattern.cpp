/*
Use cases:
1. Notification
2. Two approaches: push vs. pull
3. This is push approach.

Observer triggers subscribe() and unsubscribe().
*/
#include <list>
#include <iostream>

using namespace std;

class ISubscriber;

class IPublisher {
public:
   virtual ~IPublisher() = default;
   virtual void addSubscriber(ISubscriber *subscriber) = 0;
   virtual void removeSubscriber(ISubscriber *susbcriber) = 0;
   virtual void notify() = 0;
};

class ISubscriber {
public:
    virtual ~ISubscriber() = default;
    virtual void update(string_view message) = 0;
    virtual void unsubscribe() = 0;
};

class EmailSubscriber : public ISubscriber {
public:
    EmailSubscriber(IPublisher *publisher, string_view idStr) : m_publisher(publisher), m_idStr(idStr) {
        publisher->addSubscriber(this);
    }
    ~EmailSubscriber() = default;

    void update(string_view message) override {
        std::cout << "Id: " << m_idStr << " | Update: " << message << std::endl;
    }

    void unsubscribe() override {
        m_publisher->removeSubscriber(this);
    }

private:
    IPublisher *m_publisher;
    string m_idStr;
};

class TemperaturePublisher : public IPublisher {
public:
    TemperaturePublisher() = default;
    ~TemperaturePublisher() = default;

    void addSubscriber(ISubscriber *subscriber) override {
        m_subscribersList.push_back(subscriber);
    }

    void removeSubscriber(ISubscriber *subscriber) override {
        for(list<ISubscriber*>::iterator it = m_subscribersList.begin(); it != m_subscribersList.end(); it++) {
            if(*it == subscriber) {
                m_subscribersList.erase(it);
                break;
            }
        }
    }

    void notify() override {
        for(ISubscriber *subscriber : m_subscribersList) {
            subscriber->update("Temperature is changed to : " + to_string(m_temperature));
        }

        return;
    }

    void updateTemperature(int64_t temperature) {
        m_temperature = temperature;
        notify();
    }


private:
    std::list<ISubscriber*> m_subscribersList;
    int64_t m_temperature;
};

int main() {
    TemperaturePublisher *publisher = new TemperaturePublisher();
    ISubscriber *subscriber1 = new EmailSubscriber(publisher, "345671");
    ISubscriber *subscriber2 = new EmailSubscriber(publisher, "345672");
    ISubscriber *subscriber3 = new EmailSubscriber(publisher, "345673");

    publisher->updateTemperature(30);

    subscriber1->unsubscribe();

    publisher->updateTemperature(20);

    delete subscriber1;
    delete subscriber2;
    delete subscriber3;


}