#include "Engine.hpp"

void Engine::createArmies(int max_cost)
{
    state->armies.push_back(std::pair<std::shared_ptr<Army>,
        std::shared_ptr<Army>>(Army::Create(max_cost),
           Army::Create(max_cost)));
}

void Engine::nextTurn()
{
    redo();
}

void Engine::showArmies()
{
    auto a = getArmies().first;
	a->show();
    a = getArmies().second;
	a->show();
}

void Engine::undo()
{
    std::unique_ptr<Command> cmd = std::make_unique<PhaseCommand>(*this->state);
    cmd->unExecute();
}

void Engine::redo()
{
    std::unique_ptr<Command> cmd = std::make_unique<PhaseCommand>(*this->state);
    cmd->execute();
}

void Engine::chooseStrategy(int variant)
{
	this->state->current().first->setStrategy(static_cast<StrategyVariant>(variant - 1));
	this->state->current().second->setStrategy(static_cast<StrategyVariant>(variant - 1));
}
