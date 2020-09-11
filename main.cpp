// test comment for github

#include <cstdlib>                     // For random number generation
#include <ctime>                       // For the std::time() function
#include "Solar.h"

// Function to generate a random integer between 1 and count
inline unsigned random(size_t count)
{
  return 1 + static_cast<unsigned>(std::rand() / (RAND_MAX / count + 1));//RAND_MAX is a const declared in <cstdlib> in (stdlib.h)
}

//generates a rough Gausian distribution for the number of planets (3 to 18 peaking at 10.5)
inline unsigned numberPlanets()
{
  return random(6)+random(6)+random(6);
}

/*
  Randomly generates a planet. If it is the outer zone it can be either rocky or icy. Otherwise,
  it must be rocky. Other dimensions like diameter and density are randomly determined based on zone.
*/
inline SharedPlanet generatePlanet(double orbit,int zone,double luminosity,std::string star_name)
{
  
  double core{1};//default 1 = rocky else 2 = icy
  double diameter {0};
  double density;
  //generate core type
  if(zone==3&&(random(6))>2)
  {
    core = 2;//make core icy
  }
  //generate diameter
  if(core==1)//core = rocky
  {
    int y = random(6);
    if (y==0){y=1;}//make random number 1 thru 6 where 1 and 2 are the same
    for(int i=0;i<y;i++)
    {
      diameter = diameter + random(6)*1000;
    }
  }
  else//core = icy
  {
    int y = random(6);
    if (y==6){y=8;}//make random number 1,2,3,4,6,8
    if (y==5){y=6;}
    for(int i=0;i<y;i++)
    {
      diameter = diameter + random(6)*1000;
    }
  }
  //generate density
  if(core==1)//rocky
  {
    density = (random(10)*(0.1)) + 0.3;
  }
  else//icy
  {
    density = random(6)*(0.1);
  }
  //Planet(double orbital_radius, int orbital_zone, double core, double diameter, double density);
 
  return std::make_shared<Planet>(orbit, zone, core, diameter, density,luminosity);
  
  
}//end generatePlanet

int main()  
{
  // Initialize the random number generator
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  std::vector<Solar> Systems;                     // Create an empty list
  //Solar star;
  Solar load1;
  Solar load2[10];
  
  int number_stars = 1;
  load1.addStar("AlphaCentauri G2",'G',2,5);
  Systems.push_back(load1);

  //load1.addStar("Alpha Centauri K0",'K',0,5);
  //load1.push_back(star);
  //load1.addStar("Proxima Centauri",'M',5,5);
  //load1.push_back(star);
  //load1.addStar("Tau Ceti",'G',8,5);
  //load1.push_back(star);
  //load1.addStar("Epsilon Eridani K2",'K',2,5);
  //load1.push_back(star);
  //load1.addStar("Epsilon Indi",'K',5,5);
  //load1.push_back(star);
  
  
    load1.listStar();
    load1.generateZones();

    // Add random Planet objects to the list
    unsigned int number_planets {1};
    number_planets = numberPlanets();//generates 3d6 planets
    
   
    const size_t PlanetCount {number_planets};

    /*
      The orbit of the first planet is determined randomly.
      The rest of the orbits need to take into account the prior planet's orbit. Otherwise, the 
      orbits might sit on top of each other. This would lead to planetary collisions. Fun,
      but not useful.
    */
    load1.getFirstOrbit();
    //Rubic_1 Loops and functions
    for (size_t i {} ; i < PlanetCount -1 ; ++i)
    {
      load1.getNextOrbit();
    }
    load1.listOrbits();
    for (size_t i {} ; i < PlanetCount ; ++i)
    {
      double orbit = load1.orbits.at(i);
      int zone =load1.zone.at(i);
      load1.addPlanet(generatePlanet(orbit,zone,load1.getLuminosity(),load1.getStarName()));
    }
  
  
  
  load1.listPlanets();
  Systems.push_back(load1);
  //std::cout<<Systems[0].returnStar()<<std::endl;
  //Systems[0].listPlanets();
  

  /*
    Below is unused code that may be added in a later version. Please ignore.
  */

  /*
  std::cout << "The first list:\n";
  load1.listPlanets();

  // Copy the Solar
  Solar copy{ load1 };
  std::cout << "The copied Solar:\n";
  copy.listPlanets();
  load1.listStar();
  // Find the largest Planet in the list
  SharedPlanet largestPlanet{load1.getFirstPlanet()};

  SharedPlanet nextPlanet{load1.getNextPlanet()};
  */
  /*while (nextPlanet)
  {
    if (nextPlanet->compare(*largestPlanet) > 0)
        largestPlanet = nextPlanet;
    nextPlanet = load1.getNextPlanet();
  }*/
  /*
  std::cout << "\nThe largest Planet in the first list is ";
  largestPlanet->listPlanets();
  std::cout << std::endl;
  load1.removePlanet(largestPlanet);
  std::cout << "\nAfter deleting the largest Planet, the list contains:\n";
  load1.listPlanets();

  const size_t nPlanets {20};            // Number of vector elements
  std::vector<SharedPlanet> Planets;        // Array of Planet objects

  for (size_t i {} ; i < nPlanets ; ++i)
    Planets.push_back(randomPlanet());

  Solar load2{Planets};
  std::cout << "\nThe second list:\n";
  load2.listPlanets();

  auto smallestPlanet {load2.getFirstPlanet()};
  */
  /*for (auto nextPlanet{ load2.getNextPlanet() }; nextPlanet; nextPlanet = load2.getNextPlanet())
    if (nextPlanet->compare(*smallestPlanet) > 0)
      smallestPlanet = nextPlanet;
  */
  /*
  std::cout << "\nThe smallest Planet in the second list is ";
  smallestPlanet->listPlanets();
  */
}