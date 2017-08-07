#pragma once
#include "ISpecialAbility.hpp"
#include "CanBe.hpp"
#include <typeinfo>

class ClericUnit : public ISpecialAbility
{
public:
    ClericUnit() : ISpecialAbility(9,-6,1,50,1,0.6) {}
    void cast(Army&, IUnit& other) override;
    std::unique_ptr<IUnit> clone() override
    {
        return std::make_unique<ClericUnit>(*this);
	}
};
