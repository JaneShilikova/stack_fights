#include "Strategy.hpp"
#include "Army.hpp"
#include "IUnit.hpp"
#include "IUnitCreator.hpp"
#include "ISpecialAbility.hpp"
#include <iostream>
#include <memory>
#include <deque>
#include <iterator>
#include <typeinfo>
#include <random>

//Factory Method
std::shared_ptr<Army> Army::Create(int max_cost)
{
	std::shared_ptr<Army> new_army = std::make_shared<Army>();
	int cost = 0;
	RandomUnitCreator cr;
	while (cost <= max_cost)
	{
        new_army->army.push_front(cr.getUnit());
        cost += new_army->army.front()->getCost();
	}
	new_army->army.pop_front();
	return new_army;
}

void Army::show()
{
    for (auto i : this->army)
    {
        IUnit& unit = *i;
        std::cout << typeid (unit).name() << std::endl;
    }
	std::cout << std::endl;
}

void Army::phase(Army& other, size_t range)
{
    if (range < 1)
    {
        strategy->meleePhase(*this,other);
        //this->meleePhase(other);
        return;
    }
    else if (range >= army.size())
        return;
    strategy->specialPhase(*this,other,range);
    //this->specialPhase(other, range);
}

/*void Army::meleePhase(Army& other)
{
    bool res = this->army.front()->meleeAttack(*other.army.front());
	if (res)
		other.army.pop_front();
}*/

/*void Army::specialPhase(Army& other, size_t range)
{
    IUnit& unit = *this->army.at(range);
    if (unit.getFlags() & UNIT_IS_SPECIAL)
	{
		ISpecialAbility& sp_unit = static_cast<ISpecialAbility&>(unit);
		std::default_random_engine generator;
        if (sp_unit.getRange() > range)
        {
            std::uniform_int_distribution<size_t> dist(0, sp_unit.getRange() - range);
            size_t index = dist(generator);
            if (sp_unit.getStrength() > 0)
                sp_unit.useAbility(other, *other.army.at(index > range ? range : index));
            else
                sp_unit.useAbility(*this, *this->army.at(index));
        }
	}
}*/

void Army::setStrategy(StrategyVariant strategy)
{
	this->variant = strategy;
	switch (strategy)
	{
	case StrategyVariant::LINE:
        this->strategy = std::make_unique<LineStrategy>();
		break;
	case StrategyVariant::COLUMN:
        this->strategy = std::make_unique<ColumnStrategy>();
		break;
	case StrategyVariant::RANK:
        this->strategy = std::make_unique<RankStrategy>();
		break;
	default:
		std::cout << "Incorrect strategy" << std::endl;
	}
}

Army::~Army()
{

}
