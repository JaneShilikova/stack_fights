#pragma once
#include "ISpecialAbility.hpp"
#include <type_traits>
#include <typeinfo>
#include "CanBe.hpp"

class MageUnit : public ISpecialAbility
{
public:
    MageUnit() : ISpecialAbility(9, 2, 1, 50, 1, 0.1) {}
	// prototype
    void cast(Army& other_army, IUnit& other) override
    {
		if (other.getFlags() & UNIT_CAN_BE_CLONED)
		{	
            other_army.addUnit(other.clone());
		}
    }
    std::unique_ptr<IUnit> clone() override
    {
        return std::make_unique<MageUnit>(*this);
	}
};
