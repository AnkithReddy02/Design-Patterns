#include <cstdint>
#include <iostream>

/*
Usually, common things are placed in Director class. with parameter as concreteBuilder
Refer again.
*/

class House {
public:
    // IHouseBuilder doesn't work because friendship is not inherited. However, this works if IHouseBuilder is accesisng private members.
    friend class ConcreteHouseBuilder;
    House() = default;
    ~House() = default;

    House(std::string_view name, int32_t numDoors, int32_t numGates, int32_t numWindows) : m_name(name), m_numGates(numGates), m_numWindows(numWindows), m_numDoors(numDoors) {}

    void getHouseInfo() {
        std::cout << "House: " << std::endl;
        std::cout << "  name: " << m_name << std::endl;
        std::cout << "  windows: " << m_numWindows << std::endl;
        std::cout << "  doors: " << m_numDoors << std::endl;
        std::cout << "  gates: " << m_numGates << std::endl;
    }

private:
    std::string_view m_name;
    int32_t m_numWindows;
    int32_t m_numDoors;
    int32_t m_numGates;
};

class IHouseBuilder {
public:
    virtual ~IHouseBuilder() = default;

    virtual IHouseBuilder* addWindows(int numWindows) = 0;
    virtual IHouseBuilder* addDoors(int numDoors) = 0;
    virtual IHouseBuilder* addGates(int numGates) = 0;
    virtual IHouseBuilder* addHouseName(std::string_view name) = 0;
    virtual House* build() = 0;
};

class ConcreteHouseBuilder : public IHouseBuilder {
public:
    ConcreteHouseBuilder() = default;

    ~ConcreteHouseBuilder() = default;

    IHouseBuilder* addDoors(int numDoors) override {
        m_numDoors = numDoors;
        return this;
    }

    IHouseBuilder* addWindows(int numWindows) override {
        m_numWindows = numWindows;
        return this;
    }

    IHouseBuilder* addHouseName(std::string_view name) override {
        m_name = name;
        return this;
    }

    IHouseBuilder* addGates(int numGates) override {
        m_numGates = numGates;
        return this;
    }


    House* build() override {
        return new House(m_name, m_numDoors, m_numGates, m_numWindows);
    }

private:
    std::string_view m_name;
    int32_t m_numWindows;
    int32_t m_numDoors;
    int32_t m_numGates;
};

int main() {
    IHouseBuilder* builder = (new ConcreteHouseBuilder())->addHouseName("ankith")->addDoors(4)->addGates(3);
    House* house = builder->build();

    house->getHouseInfo();

    delete house;
    delete builder;
}