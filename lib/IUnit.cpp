#include "IUnit.hpp"

IUnit::IUnit(int health, int strength, int armor, int cost)
{
	this->health = health;
	this->strength = strength;
	this->armor = armor;
	this->cost = cost;
}

bool IUnit::meleeAttack(IUnit& other)
{
	bool res;
    if ((res = other.hit(this->getStrength()/ other.getArmor())))
		// for pattern Observer
		other.notify();
	return res;
}
