#include<bits/stdc++.h>
using namespace std;

class IRoom {

public:
    virtual void addMessage(const string&) = 0;
    //virtual void displayMessages() = 0;
    virtual ~IRoom() = default;
};

class BasicRoom: public IRoom {
private:
    vector<string> messages;
public:
    void addMessage(const string& message) {
        messages.push_back(message);
        cout << "Added: " << message << endl;
    }
};

class IDecorator: public IRoom {
public:
    virtual ~IDecorator() {}
};

class BadWords: public IDecorator {
private:
    IRoom* room;
    vector<string> words = {"bad", "spam", "attack", "random"};
public:
    BadWords(IRoom* room) : room(room) {

    }

    void addMessage(const string& message) {
        for(string& word : words) {
            if(word == message) {
                cout << "Can't add \"" << message << "\" --> Bad words are not allowed!!" << endl;
                return;
            }
        }

        room->addMessage(message);
    }
};

class MinLenWords: public IDecorator {
public:
    IRoom* room;
    MinLenWords(IRoom* room) : room(room) {

    }

    void addMessage(const string& message) {
        if(message.length() <= 2) {
            cout << "Can't add \"" << message << '\"' << " --> Min length is 3" << endl;
            return;
        }

        room->addMessage(message);
    }
};

int main() {
    IRoom* room = new MinLenWords(new BadWords(new BasicRoom()));

    room->addMessage("bade");
    room->addMessage("spam");
    room->addMessage("es");
    room->addMessage("random");
    room->addMessage("okay");
}