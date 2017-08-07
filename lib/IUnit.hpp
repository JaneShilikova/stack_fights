#pragma once
#include <string>
#include <list>
#include <iterator>
#include <memory>
#include "Observer.hpp"

class FlagsIface
{
public:
    int getFlags() { return flags; }
protected:
    int flags = 0;
};

class IUnit : virtual public FlagsIface
{
public:
	IUnit(int, int, int, int);
    IUnit(const IUnit& other) = default;
    virtual IUnit& operator=(const IUnit& other) = default;
    virtual ~IUnit() = default;
    virtual bool meleeAttack(IUnit& other);
    int getCost() { return cost; }
	virtual int getHealth() { return health; }
    virtual int getStrength() {return strength;}
    virtual int getArmor() {return armor;}
    virtual bool hit(int str = 0)
    {
        health -= str;
        return health <= 0;
    }
	// Subject for pattern Observer
    void attach(std::shared_ptr<Observer> o)
	{
        std::list<std::shared_ptr<Observer>>::iterator it = obs.end();
        obs.insert(it, o);
	}
    void detach(std::shared_ptr<Observer> o)
	{
        std::list<std::shared_ptr<Observer>>::iterator it;
        for (it = obs.begin(); it != obs.end(); ++it)
			if (*it == o)
				break;
	}
	void notify()
	{
        std::list<std::shared_ptr<Observer>>::iterator it;
        for (it = obs.begin(); it != obs.end(); it++)
            (*it)->Update(*this);
	}
	// prototype
    virtual std::unique_ptr<IUnit> clone() = 0;
private:
    int health;
    int strength;
    int armor;
    int cost;
    std::list<std::shared_ptr<Observer>> obs;
};
