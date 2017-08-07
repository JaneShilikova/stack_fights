#pragma once
#include "IUnit.hpp"
#include "Army.hpp"
#define UNIT_IS_SPECIAL 1
class ISpecialAbility : public IUnit
{
public:
    ISpecialAbility(int, int, int, int, size_t, double);
    ISpecialAbility(const ISpecialAbility& other) = default;
    virtual ~ISpecialAbility() = default;
    bool useAbility(Army&, IUnit&);
    size_t getRange() { return range; }
    virtual int getSpecialStrength() { return specialStrength; }
protected:
    virtual void cast(Army&, IUnit&) = 0;
private:
    size_t range;
	int specialStrength;
	double probability;
};
