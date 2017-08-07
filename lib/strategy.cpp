#include "Army.hpp"
#include "ISpecialAbility.hpp"
#include "Command.hpp"
#include <algorithm>

void LineStrategy::meleePhase(Army& ally, Army& enemy)
{
    bool res = ally.army.front()->meleeAttack(*enemy.army.front());
	if (res)
        enemy.army.pop_front();
}

void LineStrategy::specialPhase(Army& ally, Army& enemy, size_t range)
{
    IUnit& unit = *ally.army.at(range);
	if (unit.getFlags() & UNIT_IS_SPECIAL)
	{
		ISpecialAbility& sp_unit = static_cast<ISpecialAbility&>(unit);
		std::default_random_engine generator;
		if (sp_unit.getSpecialStrength() > 0)
		{
			if (sp_unit.getRange() > range)
			{
				std::uniform_int_distribution<size_t> dist(0, sp_unit.getRange() - range);
				size_t index = dist(generator);
                sp_unit.useAbility(enemy, *enemy.army.at(index > range ? range : index));
			}
		} 
		else 
		{
			std::uniform_int_distribution<size_t> dist(0, sp_unit.getRange() + range);
			size_t index = dist(generator);
            sp_unit.useAbility(ally, *ally.army.at(index));
		}
	}
}

void ColumnStrategy::meleePhase(Army& ally, Army& enemy)
{
	int min = std::min(ally.army.size(), enemy.army.size());
	auto len = min < 3 ? min : 3;
    for (int i = 0; i < len; i++)
	{
        bool res = ally.army.at(i)->meleeAttack(*enemy.army.at(i));
		if (res)
        {
            enemy.army.erase(enemy.army.begin() + i);
            len--;
        }
	}
	/*for (int i = len - 1; i <= 0; i--)
	{
		if (enemy.army.at(i)->getHealth() <= 0)
			enemy.army.erase(enemy.army.begin() + i);
	}*/
}

void ColumnStrategy::specialPhase(Army& ally, Army& enemy, size_t range)
{
	size_t effectiveRange = range;
    auto maxRange = ally.army.size() / 3;
	if (range > maxRange)
		return;
    auto maxEffectiveUnit = range == maxRange ? ally.army.size() % 3 : 2;
	for (auto effectiveUnit = 0; effectiveUnit < maxEffectiveUnit; effectiveUnit++)
	{
        IUnit& unit = *ally.army.at(range * 3 + effectiveUnit);
		if (unit.getFlags() & UNIT_IS_SPECIAL)
		{
			ISpecialAbility& sp_unit = static_cast<ISpecialAbility&>(unit);
			std::default_random_engine generator;
			std::uniform_int_distribution<size_t> dist(0, 2);
			auto actUnit = dist(generator);
			auto unitRange = sp_unit.getRange();
			if (((effectiveUnit - actUnit) == 2) || ((effectiveUnit - actUnit) == -2))
				unitRange -= 2;
			if (((effectiveUnit - actUnit) == 1) || ((effectiveUnit - actUnit) == -1))
				unitRange--;
			if (sp_unit.getSpecialStrength() > 0)
			{
				if (unitRange > range)
				{
					std::uniform_int_distribution<size_t> dist(0, unitRange - range);
					size_t index = dist(generator)*3 + actUnit;
                    sp_unit.useAbility(enemy, *enemy.army.at(index > enemy.army.size() -1 ? enemy.army.size() - 1 : index));
				}
			}
			else
			{
				if (unitRange >= 0)
				{
					std::uniform_int_distribution<size_t> dist(0, unitRange + range);
					size_t index = dist(generator) * 3 + actUnit;
                    sp_unit.useAbility(ally, *ally.army.at(index > ally.army.size() - 1 ? ally.army.size() - 1 : index));
				}
			}
		}
	}
}

void RankStrategy::meleePhase(Army& ally, Army& enemy)
{
	// select len as smallest length from 2 armies
	// use meleeAttack from 0 to len 
	int len;
    len = std::min(ally.army.size(),
        enemy.army.size());
	for (int i = 0; i < len; i++)
	{
        bool res = ally.army.at(i)->meleeAttack(*enemy.army.at(i));
		if (res)
		{
			enemy.army.erase(enemy.army.begin() + i);
			len--;
		}
	}
	/*for (int i = len - 1; i <= 0; i--)
	{
		if (enemy.army.at(i)->getHealth() <= 0)
			enemy.army.erase(enemy.army.begin() + i);
	}*/
}

void RankStrategy::specialPhase(Army& ally, Army& enemy, size_t range)
{
	// if ally is largest army, use special attack
	// think about range
    if (ally.army.size() > enemy.army.size())
	{
        auto len = ally.army.size() - enemy.army.size();
		if (range > 1)
			return;
		for (int i = 0; i < len; i++)
		{
            IUnit& unit = *ally.army.at(enemy.army.size()+i);
			if (unit.getFlags() & UNIT_IS_SPECIAL)
			{
				ISpecialAbility& sp_unit = static_cast<ISpecialAbility&>(unit);
				std::default_random_engine generator;
				if (sp_unit.getStrength() > 0)
				{
					if (i < sp_unit.getRange())
						// can hit someone from len - range + 1
						// till the end of enemy`s army 
						// with some probability
					{
                        std::uniform_int_distribution<size_t> dist(enemy.army.size()-sp_unit.getRange() + i, enemy.army.size());
						size_t index = dist(generator);
                        sp_unit.useAbility(enemy, *enemy.army.at(index));
					}
				}
				else
				{
                    auto max_range = enemy.army.size() + i + sp_unit.getRange() >= len ? len -1  : enemy.army.size() + i + sp_unit.getRange();
                    std::uniform_int_distribution<size_t> dist(enemy.army.size()+i-sp_unit.getRange(), max_range);
					size_t index = dist(generator);
                    sp_unit.useAbility(ally, *ally.army.at(index));
				}

			}
		}
	}
}
