#include "AircraftManager.hpp"

#include <numeric>
bool AircraftManager::move()
{

    std::sort(aircrafts.begin(), aircrafts.end(),
              [](const std::unique_ptr<Aircraft>& a, const std::unique_ptr<Aircraft>& b)
              {
                  if (a->has_terminal())
                  {
                      return true;
                  }
                  if (b->has_terminal())
                  {
                      return false;
                  }
                  return a->getFuel() < b->getFuel();
              });

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](const auto& aircraft) { return !aircraft->move(); }),
                    aircrafts.end());

    // for (auto it = aircrafts.begin(); it != aircrafts.end();)
    // {
    //     if (!(*it)->move())
    //     {
    //         it = aircrafts.erase(it);
    //     }
    //     else
    //     {
    //         it++;
    //     }
    // }
    return true;
}

void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    assert(aircraft != nullptr);
    aircrafts.push_back(std::move(aircraft));
}

int AircraftManager::getNumberOfAircraft(int i)
{
    const std::string& airline = aircraftFactory.airlines[i];

    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [airline](const auto& aircraft)
                         { return (*aircraft).get_flight_num().rfind(airline) == 0; });
}

int AircraftManager::get_required_fuel() const
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
                           [](unsigned int acc, const std::unique_ptr<Aircraft>& aircraft)
                           {
                               if (aircraft->is_low_on_fuel() && (!aircraft->has_refuel()))
                               {
                                   return acc + (3000 - aircraft->getFuel());
                               }
                               return acc;
                           });
}