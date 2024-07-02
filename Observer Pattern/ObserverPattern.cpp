/*
Use cases:
1. Notification
*/

#include<bits/stdc++.h>
using namespace std;

class WeatherObservableConcrete;

class ObserverInterface {
public:
    ObserverInterface() {}
    virtual ~ObserverInterface() {}

    virtual void update() = 0;
};

class ObserverConcrete: public ObserverInterface {
// Violates Dependency Inversion Principle.
private:
    WeatherObservableConcrete* weatherObservableConcrete;
public:
    ObserverConcrete(WeatherObservableConcrete* weatherObservableConcrete): weatherObservableConcrete(weatherObservableConcrete) {}

    void update() override {
        // Received notification, poll data.
        cout << "Received Notification" << endl;
    }
};

class WeatherObservableInterface {
public: 
    WeatherObservableInterface() {}
    virtual ~WeatherObservableInterface() {}
    virtual bool add(ObserverInterface* observerInterface) = 0;
    virtual bool remove(ObserverInterface* observerInterface) = 0;
    virtual bool notify() = 0;
};

class WeatherObservableConcrete: public WeatherObservableInterface {
private:
    vector<ObserverInterface*> observersList;
    int temperature;

public:
    bool add(ObserverInterface* observerInterface) override {
        observersList.push_back(observerInterface);
        cout << "Added Observer" << endl;
        return true;
    }

    bool remove(ObserverInterface* observerInterface) override {
        // Logic for remove.
        return true;
    }

    // It depends on who's calling this notify().
    bool notify() override {
        // Do op.
        for(ObserverInterface* oi: observersList) {
            // Push Notification
            // You can send updated details in parameter.
            // Not using any params. now.
            oi->update();
        }
        return true;
    }

    int getTemperature() {
        return temperature;
    }

    // Yet to add setter.
};

int main() {
    WeatherObservableConcrete* weatherObservableConcrete = new WeatherObservableConcrete();
    WeatherObservableInterface* weatherObservableInterface = weatherObservableConcrete;
    ObserverInterface* observer1 = new ObserverConcrete(weatherObservableConcrete);
    ObserverInterface* observer2 = new ObserverConcrete(weatherObservableConcrete);

    weatherObservableInterface->add(observer1);
    weatherObservableInterface->add(observer2);

    // Notify everyone.
    weatherObservableInterface->notify();
}
