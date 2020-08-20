#ifndef Planet_H
#define Planet_H
#include <iostream>
#include <iomanip>
#include <math.h>

//Rubic_2 Code is organized into classses
//Rubic_3 Data members are specified as private, public, or protected
class Planet
{
private:
  double orbital_radius {1.0};
  int orbital_zone {1}; //1 = inner, 2 = habitable, 3 = outer
  double core {1.0};
  double diameter{1.0};
  double density {1.0};
  int atmo {0};
  double atmo_pressure {0.0};
  double mass {0.0};
  double gravity {0.0};
  double mmwr {0.0}; //minimum molecular weight retained
  double volume_sphere{0.0};
  double temperature{0.0};
  std::string  atmos_type {"vacuum"};
  std::string world_type {"Rock"};//1=rock,2=ice ball, 3=desert, 4= failed core,5=hot house, 6= Garden, 7 = gas giant, 8=chunk
  int num_moons {0};
  //constants
  double const pi {3.1415};
  double const volume_of_earth {1.062e+12};
  double const radius_of_earth {6378.1};//in kilometers
  double const mass_of_earth {5.98e24};
  double const G {6.67e-11};// gravitational constants
  double const earth_g {9.81};//earth gravity

  /*atmosphere types
    The integer is the smallest molecular weight of gas that the planet will retain.
    So 1 would be hydrogen, 8 is oxygen, 24 is carbon dioxide , etc.
    A planet that can retain hydrogen and helium will tend to be gigantic like Jupiter.
    Where as a small planet, like Mars, will only retain heavy gasses like carbon dioxide.

  */
  int const atmo_mas = 4;//massive like Jupiter
  int const atmo_den = 19;//dense like Venus
  int const atmo_sta = 39;//standard like Earth
  int const atmo_thi = 79;//thin like Mercury
  int const atmo_vth = 119;//very thin like Ceres
  int const atmo_vac = 170;//vacuum like the Moon
  
  //ouput constraints from std::setw
  const int orbit_width = 12;//3
  const int zone_width = 12;//1
  const int diameter_width = 12;//6
  const int mass_width = 12;//4
  const int gravity_width = 12;//4
  const int temperature_width = 12;//5
  const int type_width = 10;//10
  const std::string sep = " | ";

  public:
  // Constructors
  Planet(double cr, double dm, double dy)  : core {cr}, diameter {dm}, density {dy}{};

  //current constructer
  Planet(double orb, int oz, double cr, double dm, double dy, double lm) ;
  
  // No-arg constructor
  Planet() = default;                               

  double volume() const;                        

  void listTitle() const;//generates title bar for list of Planets
  void listPlanets() const;//generates list of Planets
};
#endif