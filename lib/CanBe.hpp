#pragma once
#include <type_traits>
#include "IUnit.hpp"

#define UNIT_IS_HERO 1 << 3
#define UNIT_CAN_BE_CLONED 1 << 2
#define UNIT_CAN_BE_HEALED 1 << 1

class CanBeCloned : virtual public FlagsIface
{
public:
    CanBeCloned()
    {
        this->flags |= UNIT_CAN_BE_CLONED;
    }
};

class CanBeHealed :virtual public FlagsIface
{
public:
    CanBeHealed()
    {
       this->flags |= UNIT_CAN_BE_HEALED;
    }
};

enum ArtPoint
{
    HORSE = 0,
    ARMOR = 1,
    SHIELD = 2,
    WEAPON = 3
};

struct Artifact
{
    ArtPoint pt;
	int str_mod;
	int arm_mod;
    bool operator < (const Artifact& other)
    {
        return ((str_mod + arm_mod) < (other.str_mod + other.arm_mod));
    }
    bool operator > (const Artifact& other)
    {
        return ((str_mod + arm_mod) > (other.str_mod + other.arm_mod));
    }
    bool operator == (const Artifact& other)
    {
        return (pt == other.pt) &&((str_mod + arm_mod) == (other.str_mod + other.arm_mod));
    }
};

class IsHero : virtual public FlagsIface
{
public:
	IsHero()
	{
		this->flags |= UNIT_IS_HERO;
        this->flags ^= UNIT_CAN_BE_CLONED;
	}
    virtual bool equip(const Artifact& art) = 0;
    virtual void unequip(ArtPoint pt) = 0;
};
