#pragma once
#include "ISpecialAbility.hpp"
#include "MageUnit.hpp"
#include <string>
#include <unordered_set>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <fstream>
#include <typeinfo>
#include <map>

/*
 * Decorator pattern
 * Hero is abstract decorator
 * T is concrete component (from IUnit)
 * Hero <T> is concrete decorator
 * IUnit is common base class
 */
template <typename T>
class Hero : public T, IsHero
{
public:
    static_assert(std::is_base_of<IUnit, T>::value, "");
public:
	Hero() : T() {}
	Hero(const T& x) : T(x) {}
    bool equip(const Artifact& art) override
    {
        bool eq =  arts[art.pt] < (art);
        if (eq)
            arts[art.pt] = art;
        return eq;
    }
    void unequip(ArtPoint pt) override
    {
        arts.erase(pt);
    }
    int getStrength() override
    {
        int ret = T::getStrength();
        for(auto art: arts)
            ret += art.second.str_mod;
        return ret;
    }
    int getArmor() override
    {
        int ret = T::getArmor();
        for(auto art: arts)
            ret += art.second.arm_mod;
        return ret;
    }
    std::unique_ptr<IUnit> clone() override
    {
        return std::make_unique<Hero<T>>(*this);
    }
//private
protected:
    std::map<ArtPoint,Artifact> arts;
};

//Decoration function
template<class T> 
Hero<T> makeHeroic(T& unit) 
{
    return Hero<T>(unit);
}

//proxy
template <typename T>
class HeroPtr : public T, IsHero
{
public:
	static_assert(std::is_base_of<IUnit, T>::value, "");
public:
	HeroPtr() : T() {}
	HeroPtr(const T& x) : T(x) {}
    HeroPtr(const Hero<T>& other)
    {
        this->hero = std::make_shared<Hero<T>>(other);
    }
    bool meleeAttack(IUnit& other) override
    {
        to.open("output.txt", std::ios_base::app);
        to << "Hero hits " << typeid(other).name() << " on "
            << hero->getStrength() / other.getArmor() << "\n";
        to.close();
        auto ret =  hero->meleeAttack(other);
        if (ret)
            IUnit::notify();
        return ret;
    }
	bool hit(int str = 0) override
	{
        to.open("output.txt", std::ios_base::app);
		to << "Hero gets hit on " << str << "\n";
		to.close();
		return hero->hit(str);
	}
    std::unique_ptr<IUnit> clone() override
    {
        return std::make_unique<HeroPtr<T>>(*this->hero);
    }
    virtual bool equip(const Artifact& art) override
    {
        return hero->equip(art);
    }
    virtual void unequip(ArtPoint art_name) override
    {
        hero->unequip(art_name);
    }
protected:
	std::shared_ptr<Hero<T>> getHero()
	{
		return hero;
	}
	void setHero(std::shared_ptr<Hero<T>> hero)
	{
		this->hero = hero;
	}
private:
    std::shared_ptr<Hero<T>> hero = std::make_shared<Hero<T>>();
	std::ofstream to;
};
