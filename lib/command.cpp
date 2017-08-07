#include "Engine.hpp"
#include <random>

void PhaseCommand::execute()
{
    Engine& engine = Engine::getInst();
    auto& temp = st.current();
    if (engine.finished())
        return;
    if (st.number >= st.armies.size() - 1) 
        st.armies.push_back(std::pair<std::shared_ptr<Army>,
            std::shared_ptr<Army>>(std::make_shared<Army>(*temp.first),
                std::make_shared<Army>(*temp.second)));
    /*else
    {
        st.armies[st.number] = std::pair<std::shared_ptr<Army>,
        std::shared_ptr<Army>>(std::make_shared<Army>(*armies.first),
            std::make_shared<Army>(*armies.second));
    }*/
	st.number++;
    auto& armies = st.current();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1);
    int first = distribution(generator);
    size_t len = armies.first->getCount() > armies.second->getCount()
        ? armies.first->getCount()
        : armies.second->getCount();
    for (size_t i = 0; i < len; i++)
    {
        if (first)
        {
            armies.first->phase(*armies.second, i);
            if (engine.finished())
                break;
            armies.second->phase(*armies.first, i);
        }
        else
        {
            armies.second->phase(*armies.first, i);
            if (engine.finished())
                break;
            armies.first->phase(*armies.second, i);
        }
    }
}

void PhaseCommand::unExecute()
{
    if (st.number == 0)
        return;
    st.number--;
}
