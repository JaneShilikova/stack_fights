#include "ISpecialAbility.hpp"

#include <random>

ISpecialAbility::ISpecialAbility(int health, int specstr,
    int armor, int cost, size_t range, double probability)
	: IUnit(health, abs(specstr / 2), armor, cost), 
    range(range), specialStrength(specstr), probability(probability)
{
    flags |= UNIT_IS_SPECIAL;
}

bool ISpecialAbility::useAbility(Army& army, IUnit& other)
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 1);
	if (distribution(generator) >= probability)
	{
        cast(army, other);
		return true;
	}
	return false;
}
