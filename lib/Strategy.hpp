#pragma once
#include <random>
#include <memory>
#include <algorithm>

using std::shared_ptr;

class Army;

class Strategy
{
public:
    Strategy() = default;
	virtual ~Strategy() = default;
    virtual void meleePhase(Army&,Army&) = 0;
    virtual void specialPhase(Army&,Army&,size_t) = 0;
};

class LineStrategy : public Strategy
{
public:
    LineStrategy() : Strategy(){}
    void meleePhase(Army&,Army&)  override;
    void specialPhase(Army&,Army&,size_t)override;
};

class ColumnStrategy : public Strategy
{
public:
    ColumnStrategy() : Strategy(){}
    void meleePhase(Army&,Army&)  override;
    void specialPhase(Army&,Army&,size_t) override;
};

class RankStrategy : public Strategy
{
public:
    RankStrategy() : Strategy(){}
    void meleePhase(Army&,Army&)  override;
    void specialPhase(Army&,Army&,size_t) override;
};
