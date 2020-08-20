
#ifndef SOLAR_H
#define SOLAR_H


#include <iostream>
#include "Planet.h"
#include <vector>
#include <memory>          // For std::shared_ptr<>
#include <string>
#include <math.h>

/*
   Solar generates a solar system with a central star and a group of planets.
  The star is real, taken from a subset of Gilese's Catalog of Nearby Stars.
  The planets are a simulation based on current educated guesses about planetary formation.

   addStar takes a line of the Catalog as input. An example would be
  "AlphaCentauri G2",'G',2,5" where Alpha Centauri is the name, G2 is the spectral class type
  and number, and 5 is the size. G2 5 is used to calculate the three zones (inner, habitable, and outer).
  The line between habitable and outer is the point where most gases become solid due to temperature.
  The line between inner and habitable is slightly outside of Venus's orbit in our solar system.

   Different types of planets appear depending on what zone it is in. For instance, if Earth formed
   in the inner zone the oceans would have boiled off leaving a world like Venus. If it formed
   in the outer system it would have accumulated mass from gases that would have boiled off
   in the inner system. Leaving a world like Neptune. 

*/

using SharedPlanet = std::shared_ptr<Planet>;

class Solar
{
private:
  
  double star_radius {};
  double star_mass {};
  double star_lumin {};
  double star_temp {};
  

  //tables

  /*
  To generate the zones, one needs a surface temperature of the star. You would hope that 
  this could be determined by a simple equation based on the star's spectral type and size.
  But no, these are somewhat arbitrary numbers used by astronomers, and are not handy for 
  generating a surface temperature. So a series of tables are used. Each table is a 2 dimesional array.
  There is one table for each spectral number. So for "AlphaCentauri G2",'G',2,5", the 
  correct luminosity is located in G[5][2]. G is the spectral letter, 5 is the size, and 2 is 
  the spectral type.

  */
  //spectral class letter followed by size for each array. The luminosity values in the array are by spectral class number.
  //Example a G2 3 stars luminosity is array G3 element 2. Note that the two numbers, 2 and 3, are reversed. 
  //Yes, confusing but that is the way the data is organized in Gilese's Catalog


  //stellar sizes 1a and 1b are changed to 0 and 1 for simplicity.

  double F[7][6] {{61000,58000,56000,54000,52500,51000},
  {7400,6700,6300,5900,5500,5100},
  {600,570,555,540,525,510},
  {53,51,49,47,45,43},
  {19,18,16,15,14,12},
  {8.1,7.1,6.2,5.3,4.4,3.5},
  {0,0,0,0,0,0}};

  double G[7][6] {{67000,71000,74000,78000,83000,89000},
  {6100,6400,6700,7100,7600,8100},
  {560,590,620,650,680,740},
  {50,55,60,65,70,75},
  {6.5,6.18,5.86,5.54,22,4.9},
  {1.21,1.10,0.99,0.88,0.77,0.67},
  {0.32,0.29,0.26,0.23,0.20,0.186},
  };
  

  double K[7][6] {{97000,99000,101000,103000,105000,107000},
  {11700,13400,15000,16700,18400,20400},
  {890,1202,1514,1826,2138,2450},
  {95,140,185,230,275,320},
  {4.67,4.67,4.67,4.67,4.67,4.67},
  {0.42,0.35,0.28,0.21,0.14,0.08},
  {0.117,0.10,0.08,0.06,0.04,0.025},
  };
  

  double M[7][10] {{117000,120000,123000,126000,129000,132000,135000,138000,140000,141000},
  {46000,54000,62000,70000,77000,85000,93000,100000,108000,117000},
  {4600,5850,7100,8350,9600,10850,12100,13350,12600,16200},
  {470,720,970,1220,1470,1720,1970,2220,2470,2690},
  {0,0,0,0,0,0,0,0,0,0},
  {0.04,0.0354,0.0311,0.0268,0.0225,0.0182,0.0139,0.0096,0.0053,0.001},
  {0.011,0.0096,0.0084,0.0072,0.0060,0.0048,0.0036,0.0024,0.0012,0.00006},
  };
  
 
 
  
  std::string star_name;
  char spectral_class_letter {};
  int spectral_class_number {};
  int stellar_size {}; 
  double luminosity {};//correct variable name is star_lumin
  double inner_habitable {}; //inner boundary of the habitable zone
  double outer_habitable {}; //outer boundary of the habitable zone
  double inner_multiplier {0.72};
  double outer_multiplier {1.45};  
  
  
/*
  Orbit is the distance from the star to the planet that it orbits. It contains pointers to the next orbit, and the planet in its location.
*/
  class Orbit
  {
  public:
    SharedPlanet pPlanet;             // Pointer to the Planet object contained in this Orbit
    Orbit* pNext;             // Pointer to the next Orbit in the list

    Orbit(SharedPlanet pb) : pPlanet{pb}, pNext{nullptr} {}     // Constructor
    ~Orbit() { delete pNext; }                            // Destructor
  private:
    double orbit_radius {0.0};

  };

  Orbit* pHead {};                               // First in the list
  Orbit* pTail {};                               // Last in the list
  Orbit* pCurrent {};                            // Last retrieved from the list

public:
  std::vector<double>  orbits;
  std::vector<int> zone;

  Solar() = default;                           // Default constructor - empty Solar

  Solar(SharedPlanet pPlanet)                        // Constructor - one Planet
  {  pHead = pTail = new Orbit{pPlanet}; }

  Solar(const std::vector<SharedPlanet>& Planets);  // Constructor - vector of Planets

  Solar(const Solar& src);                 // Copy constructor
  
  ~Solar() { delete pHead; }                   // Destructor: clean up the list
  

  //lists the star's name and type
  void listStar()
  {
    std::cout<<star_name<<" "<<spectral_class_number<<spectral_class_letter<<" "<<stellar_size<<std::endl;
  }
  std::string getStarName()
  {
    return star_name;
  }
  SharedPlanet getFirstPlanet();                         // Get the first Planet
  SharedPlanet getNextPlanet();                          // Get the next Planet
  void addPlanet(SharedPlanet pPlanet);                     // Add a new Planet
  bool removePlanet(SharedPlanet pPlanet);                  // Remove a Planet from the Solar System
  void listPlanets() const;                          // Outputs the Planets
  void addStar(std::string name, char letter,int number, int size);//adds a star to the list
  //void listStar();
  void generateZones();
  void getFirstOrbit();//Randomly generates the first orbit.
  void getNextOrbit();//Uses the prior orbit as a seed to generate the next orbit.
  void listOrbits();
  double getLuminosity();
  
};

#endif