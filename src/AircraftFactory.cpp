#include "AircraftFactory.hpp"

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type, Tower& tower)
{
    std::string flight_number;
    do
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    while (flight_numbers_used.find(flight_number) != flight_numbers_used.end());

    flight_numbers_used.emplace(flight_number);

    const float angle   = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start = Point3D { std::sin(angle), std::cos(angle), 0.f } * 3 + Point3D { 0.f, 0.f, 2.f };
    const Point3D direction = (-start).normalize();
    return std::make_unique<Aircraft>(type, flight_number, start, direction, tower);
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Tower& tower)
{

    return create_aircraft(*(aircraft_types[rand() % NUM_AIRCRAFT_TYPES]), tower);
}
