#pragma once
#include "IUnit.hpp"
#include "Strategy.hpp"
#include <deque>
#include <iterator>
#include <vector>
#include <memory>
#include <utility>

enum class StrategyVariant
{
	LINE,
	COLUMN,
	RANK
};

class Army
{
	friend class LineStrategy;
	friend class ColumnStrategy;
	friend class RankStrategy;
public:
    virtual ~Army();
	static std::shared_ptr<Army> Create(int max_cost = 10000);
    Army() = default;
    Army(const Army& other)
    {
        for(auto& i: other.army)
        {
            this->army.push_back(i->clone());
        }
		this->setStrategy(other.variant);
    }
    size_t getCount() 
	{
		return army.size();
	}
	void show();
    void phase(Army & other, size_t range);
    void addUnit(const std::shared_ptr<IUnit>& unit) { army.push_back(unit); }
	void setStrategy(StrategyVariant);
protected:
    std::deque<std::shared_ptr<IUnit>> army;
	// this methods will be gone, go in strategy
    /*virtual void specialPhase(Army & other, size_t range);
    virtual void meleePhase(Army&);*/
	std::unique_ptr <Strategy> strategy = nullptr;
	StrategyVariant variant;
};
