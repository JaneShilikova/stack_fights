#pragma once
#include <deque>
#include <utility>
#include <memory>

class Engine;
class Army;

struct State
{
    size_t number; // number of turn
    
	std::deque
		<std::pair
        <std::shared_ptr<Army>, std::shared_ptr<Army>>> armies;
    auto& current ()
    {
        return armies[number];
    }
};

class Command
{
public:
	virtual void execute() = 0;
	virtual void unExecute() = 0;
};

class PhaseCommand : public Command
{
public:
	PhaseCommand(State& state) : st(state) {}
	void execute() override;
    void unExecute() override;
private:
    State& st;
};
