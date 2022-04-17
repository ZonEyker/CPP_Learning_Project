#pragma once
#include "aircraft.hpp"

class Airport;

class AircraftFactory
{
private:
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Tower& tower);
    std::set<std::string> flight_numbers_used;

public:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftFactory() { init_aircraft_types(); };
    ~AircraftFactory() = default;
    std::unique_ptr<Aircraft> create_random_aircraft(Tower& tower);

    // note: textures have to be initialized after initializing glut, so we'll need
    // our own init here
    inline void init_aircraft_types()
    {
        aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
        aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
        aircraft_types[2] = new AircraftType { .02f, .1f, .02f, MediaPath { "concorde_af.png" } };
    }
};
