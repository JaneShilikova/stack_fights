#pragma once
#include "IUnit.hpp"
#include "MageUnit.hpp"
#include <typeinfo>
class ArmoredUnit : public IUnit, CanBeCloned
{
public:
    ArmoredUnit() : IUnit(13, 2, 2, 80)
	{

    }
	ArmoredUnit(const ArmoredUnit& other) = default;
	virtual ArmoredUnit& operator=(const ArmoredUnit& other) = default;
	// prototype
    std::unique_ptr<IUnit> clone() override
    {
        return std::make_unique<ArmoredUnit>(*this);
	}
};
