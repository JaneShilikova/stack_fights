#include "ArcherUnit.hpp"
#include "cleric.hpp"
#include "MageUnit.hpp"
#include "SquireUnit.hpp"

void ArcherUnit::cast(Army&, IUnit& other_unit)
{
    if (other_unit.hit(this->getSpecialStrength()))
		// for pattern Observer
		other_unit.notify();
}

void ClericUnit::cast(Army&, IUnit& other)
{
    if (other.getFlags() & UNIT_CAN_BE_HEALED)
    {
        if (other.hit(this->getSpecialStrength()))
            // for pattern Observer
            other.notify();
    }
}
