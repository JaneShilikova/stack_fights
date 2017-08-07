#pragma once
#include "ISpecialAbility.hpp"
#include "Army.hpp"
#include "MageUnit.hpp"
#include <typeinfo>
class ArcherUnit : public ISpecialAbility,  CanBeCloned, CanBeHealed
{
public:
    ArcherUnit() : ISpecialAbility(9, 6, 1, 50, 1, 0.8), CanBeCloned()
	{

    }
	ArcherUnit(const ArcherUnit& other) = default;
	virtual ArcherUnit& operator=(const ArcherUnit& other) = default;
    void cast(Army&, IUnit&) override;
	// prototype
    std::unique_ptr<IUnit> clone() override
	{
        return std::make_unique<ArcherUnit>(*this);
	}
};
