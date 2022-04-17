#pragma once

#include "AircraftFactory.hpp"
#include "aircraft.hpp"

#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts = std::vector<std::unique_ptr<Aircraft>>();
    AircraftFactory aircraftFactory;

public:
    bool move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);

    int getNumberOfAircraft(int i);

    int get_required_fuel() const;
};