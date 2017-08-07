#pragma once
#include "ISpecialAbility.hpp"
#include "CanBe.hpp"
#include <random>
#include <chrono>


class SquireUnit : public ISpecialAbility
{
public:
    SquireUnit() : ISpecialAbility(9, 6, 1, 100, 1, 1)
    {
        std::default_random_engine generator;
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        auto distr = std::uniform_int_distribution<size_t>(0,3);
        art.pt = static_cast<ArtPoint>(distr(generator));
        art.arm_mod = distr(generator);
        art.str_mod = distr(generator);
    }
    SquireUnit(const SquireUnit& other): SquireUnit()
    {
         art = other.art;
    }
    std::unique_ptr<IUnit> clone() override
    {
        return std::make_unique<SquireUnit>(*this);
    }
protected:
	void cast(Army&, IUnit& other) override
	{
        if ((other.getFlags() & UNIT_IS_HERO) && !equip)
		{
            auto& cl = dynamic_cast<IsHero&>(other);
            equip = cl.equip(art);
		}
	}
private:
    bool equip = false;
	Artifact art;
};
