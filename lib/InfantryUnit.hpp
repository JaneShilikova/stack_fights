#pragma once
#include "IUnit.hpp"
#include "MageUnit.hpp"
#include "CanBe.hpp"
#include <typeinfo>
class InfantryUnit :public IUnit, CanBeCloned, CanBeHealed
{
public:
    InfantryUnit() : IUnit(9, 5, 1, 15), CanBeCloned()
	{
	}
	InfantryUnit(const InfantryUnit& other) = default;
	virtual InfantryUnit& operator=(const InfantryUnit& other) = default;
	// prototype
    std::unique_ptr<IUnit> clone() override
    {
        return std::make_unique<InfantryUnit>(*this);
	}
};
