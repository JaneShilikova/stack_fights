#include "IUnitCreator.hpp"
#include "InfantryUnit.hpp"
#include "ArcherUnit.hpp"
#include "ArmoredUnit.hpp"
#include "cleric.hpp"
#include "siege_unit.hpp"
#include "MageUnit.hpp"

#include <chrono>

RandomUnitCreator::RandomUnitCreator() noexcept
{
    vect.push_back(std::make_unique<IUnitCreator<InfantryUnit>>());
    vect.push_back(std::make_unique<IHeroCreator<ArmoredUnit>>());
    vect.push_back(std::make_unique<IUnitCreator<ArcherUnit>>());
    vect.push_back(std::make_unique<IUnitCreator<ArmoredUnit>>());
    vect.push_back(std::make_unique<IUnitCreator<ClericUnit>>());
    vect.push_back(std::make_unique<IUnitCreator<MageUnit>>());
    vect.push_back(std::make_unique<IUnitCreator<WallUnit<Wall>>>());
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    distr = std::uniform_int_distribution<size_t>(0,vect.size()-1);
} 

std::shared_ptr<IUnit> RandomUnitCreator::getUnit()
{
	auto rand = distr(generator);
    auto unit = vect[rand]->getUnit();
    unit->attach(obs.first);
    unit->attach(obs.second);
    return unit;
}
