#pragma once
#include <type_traits>
#include <typeinfo>
#include "IUnit.hpp"
#include "MageUnit.hpp"

class Wall
{
	// hp - health points
public:
    int getHp() const { return hp; }
	void substractHp(int h) { hp -= h; }
private:
	int hp = 1000;
};
// WallUnit - adapter
// Wall - adaptee
// IUnit - target
// Army - client
template<typename T>
class WallUnit : public IUnit, CanBeCloned
{
	static_assert(std::is_base_of<Wall, T>::value, "");
public:
    WallUnit(const T& ct) : IUnit(ct.getHp(), 0, 1, 90), CanBeCloned()
    {
        t = std::make_unique<T>(ct) ;
    }
    WallUnit() : IUnit(1000, 0, 1, 90), CanBeCloned()
    {
	}
    WallUnit(const WallUnit& other) : WallUnit()
    {
        t = other.t;
    }
	bool hit(int str = 0) override
	{
        t->substractHp(str);
        return t->getHp() < 0;
	}
    // prototype
    std::unique_ptr<IUnit> clone() override
    {
        return std::make_unique<WallUnit>(*this);
	}
	int getHealth() override
    {
        return t->getHp();
	}
private:
    std::shared_ptr<T> t = std::make_shared<T>();
};
