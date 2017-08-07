#pragma once
#include <fstream>
#include <iostream>
#include <string>

class IUnit;

class Observer
{
public:
    virtual void Update(IUnit& unit) = 0;
protected:
    Observer() = default;
};

class ObserverLog : public Observer
{
public:
    void Update(IUnit& unit) override;
};

class ObserverBeep : public Observer
{
public:
    void Update(IUnit& unit)
    {

        std::cout << "\7";
    }
};
