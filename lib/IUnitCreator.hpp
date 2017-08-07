#pragma once
#include "IUnit.hpp"
#include "InfantryUnit.hpp"
#include "hero.hpp"
#include <vector>
#include <memory>
#include <random>
class UnitCreatorBase
{
public:
    virtual std::shared_ptr<IUnit> getUnit() = 0;
    virtual ~UnitCreatorBase() = default;
};
//ConcreteFactory
template<typename T>
class IUnitCreator : public UnitCreatorBase
{
    static_assert(std::is_base_of<IUnit, T>::value, "");
public:
    std::shared_ptr<IUnit> getUnit()
	{
        return std::make_shared<T>();
	}
};

//ConcreteFactory for Heroes
template <typename T>
class IHeroCreator : public UnitCreatorBase
{
    static_assert(std::is_base_of<IUnit, T>::value, "");
public:
    std::shared_ptr<IUnit> getUnit() 
	{
		return std::make_shared<HeroPtr<T>>();
    }
};

//AbstractFactory
class RandomUnitCreator: UnitCreatorBase
{
public:
    RandomUnitCreator() noexcept;
    std::shared_ptr<IUnit> getUnit();
private:
    std::vector<std::unique_ptr<UnitCreatorBase> > vect;
    std::default_random_engine generator;
    std::uniform_int_distribution<size_t> distr;
    std::pair<std::shared_ptr<Observer>,std::shared_ptr<Observer>> obs = {std::make_shared<ObserverBeep>(), std::make_shared<ObserverLog>()};
};
