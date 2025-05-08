#include <iostream>

class Library {
private:
    Library() {

    }

public:
    static Library* getInstance() {
        if(m_library == nullptr) {
            return (m_library = new Library());
        }

        return m_library;
    }

private:
    static Library* m_library;
};

// Initialize
Library* Library::m_library = nullptr;

int main() {
    Library* lib1 = Library::getInstance();
    Library* lib2 = Library::getInstance();

    std::cout << (lib1 == lib2 ? "Same Instance" : "Different Instance") << std::endl;

    return 0;
}