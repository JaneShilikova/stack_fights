#include "Observer.hpp"
#include "IUnit.hpp"

extern std::string getUnitType(const IUnit&);

void ObserverLog::Update(IUnit& unit)
{
    std::ofstream to;
    to.open("DeadLog.txt", std::ios_base::app);
    to << "The death of " << typeid(unit).name() << "\n";
    to.close();
}
