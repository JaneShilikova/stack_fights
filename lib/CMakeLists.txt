set(STACKS_SOURCES
    Strategy.hpp
    strategy.cpp
    Command.hpp
    command.cpp
    Observer.hpp
    observer.cpp
    SquireUnit.hpp
    CanBe.hpp
    MageUnit.hpp
    ArcherUnit.hpp
    SpecialUnits.cpp
    Engine.cpp
    IUnit.cpp	      
    ArmoredUnit.hpp
    Engine.hpp
    IUnitCreator.cpp  
    Army.cpp
    InfantryUnit.hpp
    IUnitCreator.hpp
    Army.hpp
    ISpecialAbility.cpp
    IUnit.hpp
    ISpecialAbility.hpp
    hero.hpp
    cleric.hpp
    siege_unit.hpp
    main.cpp
)

add_executable(stacks ${STACKS_SOURCES})
set_property(TARGET stacks PROPERTY CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
