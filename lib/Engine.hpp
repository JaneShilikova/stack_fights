#pragma once
#include "Army.hpp"
#include "Command.hpp"
#include "Observer.hpp"
#include <iostream>
#include <utility> // for pair
#include <tuple>
// Singleton
class Engine
{
private:
	Engine() = default;		// automatically
	~Engine() = default;	// automatically
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	void* operator new(std::size_t) = delete;
	void* operator new[](std::size_t) = delete;
	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;
    std::unique_ptr<State> state = std::make_unique<State>();
public:
	static Engine& getInst()
	{
		static Engine object;
		return object;
	}
	void createArmies(int max_cost = 10000);
	void chooseStrategy(int);
    void nextTurn();
    void showArmies();
	void undo();
	void redo();
    std::pair<std::shared_ptr<Army>, std::shared_ptr<Army>>& getArmies()
    {
        return state->armies[state->number];
    }
    bool finished()
    {
        return (getArmies().first->getCount() == 0 ||
            getArmies().second->getCount() == 0);
    }
};
