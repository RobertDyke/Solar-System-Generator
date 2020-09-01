#include "Solar.h"
#include <iostream>
#include <cstdlib>                     // For random number generation
#include <ctime>                       // For the std::time() function

//Rubic_4 Class member functions document their effects.
//Rubic_5 Classes encapsulate behavior
// Constructor
Solar::Solar(const std::vector<SharedPlanet>& Planets)
{

  for (auto pPlanet : Planets)
  {
    addPlanet(pPlanet);
  }
}

// Copy constructor
Solar::Solar(const Solar& src)
{
  for (Orbit* Orbit{src.pHead}; Orbit; Orbit = Orbit->pNext)
  {
    addPlanet(Orbit->pPlanet);
  }
}

// Output all Planet objects in the list
void Solar::listPlanets() const
{
  const size_t PlanetsPerLine = 1;
  size_t count {};  
  int x = 0;
 
  for (Orbit* Orbit{pHead}; Orbit; Orbit = Orbit->pNext)
  {
    if(x==0){
      Orbit->pPlanet->listTitle();
      x =1;
    }
    Orbit->pPlanet->listPlanets();
    //if (! (++count % PlanetsPerLine)) std::cout << std::endl;
  }
  //if (count % PlanetsPerLine) std::cout << std::endl;
}

// Get the first Planet
SharedPlanet Solar::getFirstPlanet()
{
  // Return pHead's Planet (or nullptr if the list is empty)
  pCurrent = pHead;
  return pCurrent? pCurrent->pPlanet : nullptr;     
}

// Get the next Planet
SharedPlanet Solar::getNextPlanet()    
{
  if (!pCurrent)                                     // If there's no current...
    return getFirstPlanet();                            // ...return the 1st Planet

  pCurrent = pCurrent->pNext;                        // Move to the next Orbit
  
  return pCurrent? pCurrent->pPlanet : nullptr;         // Return its Planet (or nullptr...).
}

// Add a Planet to the list
void Solar::addPlanet(SharedPlanet pPlanet)
{
  auto pOrbit = new Orbit{pPlanet};       // Create a new Orbit

  if (pTail)                               // Check list is not empty
    pTail->pNext = pOrbit;              // Add the  new  object to the tail
  else                                     // List is empty
    pHead = pOrbit;                      // so new object is the head

  pTail = pOrbit;                        // Store its address as tail
}

// Find the Orbit containing pPlanet and delete it from the list
bool Solar::removePlanet(SharedPlanet PlanetToRemove)
{
  Orbit* previous {nullptr};      // no previous yet
  Orbit* current {pHead};         // initialize current to the head of the list
  while (current)
  {
    if (current->pPlanet == PlanetToRemove)          // We found the Planet!
    {
      if (previous)                            // If there is a previous Orbit...
      {
        previous->pNext = current->pNext;     // ...make it point to the next Orbit 
      }
      else
      {                                        // If there is no previous, we are removing the 
        pHead = current->pNext;                // first Orbit in the list, so update pHead
      }
      
      current->pNext = nullptr;               // Disconnect the current Orbit from the list
      delete current;                          // and delete it
      
      return true;                             // Return true: we found and removed the Planet
    }
                                               // Move both pointers along (mind the order!)
    previous = current;                        //  - first current becomes the new previous 
    current = current->pNext;                  //  - then move current along to the next Orbit
  }

  return false;                                // Return false: PlanetToRemove was not found
}

/*Adds a star to the list of stars from the Catalog.
*/
void Solar::addStar(std::string name, char letter,int number, int size)
{
  star_name = name;
  spectral_class_number = number;
  spectral_class_letter = letter;
  stellar_size = size;
  
 }
 


/*
    Uses the star's size and spectra to generate a surface temperature (star_lumin).
    Then generates the zone from the star_lumin.
*/
void Solar::generateZones()
{
  //find luminosity using array table in Solar.h
 
  switch (spectral_class_letter)
  {
    case 'F':
      star_lumin = F[stellar_size][spectral_class_number];
      break;
    case 'G':
      star_lumin = G[stellar_size][spectral_class_number];
      break;
    case 'K':
      star_lumin = K[stellar_size][spectral_class_number];
      break;
    case 'M':
      star_lumin = F[stellar_size][spectral_class_number];
      break; 
  }
  //find habitable zone using luminosity
  inner_habitable = inner_multiplier * (sqrt(star_lumin));
  outer_habitable = outer_multiplier * (sqrt(star_lumin));
  extended_habitable = extended_habitable * (sqrt(star_lumin));
  
}

//randomly generates the first orbit in the solar system
void Solar::getFirstOrbit()
{
  double orbit_radius = (0.1)*(rand() % 10 + 1);//generate radius between 0.1 and 1.0 AUs
  this->orbits.push_back(orbit_radius);
  if(orbit_radius < inner_habitable)
  {
    zone.push_back(1);//it is in the inner zone
  }
  else
  {
    if(orbit_radius > outer_habitable)
    {
      zone.push_back(3);//it is in the outer zone
    }
    else if(orbit_radius >= extended_habitable)
    {
      zone.push_back(4);//it is in the extended habitable zone
    }
    else
    {
      zone.push_back(2);//it is in the habitable zone
    }
    
  }
  
}

//Randomly generates following orbits using the prior orbit as a seed for the next one.
void Solar::getNextOrbit()
{
  double last_orbit {1};
  double subsequent_orbit {1};
  double new_orbit {1};
  last_orbit = orbits.back();
  subsequent_orbit = ((rand() % 10 + 1)*(0.1))+1.2;//multiply last orbit by rand 1.2 to 2.1
  new_orbit = last_orbit*subsequent_orbit;
  orbits.push_back(new_orbit);
  if(new_orbit < inner_habitable)
  {
    zone.push_back(1);//it is in the inner zone
  }
  else
  {
    if(new_orbit > outer_habitable)
    {
      zone.push_back(3);//it is in the habitable zone
    }
    else if(new_orbit >= extended_habitable)
    {
      zone.push_back(4);//it is in the extended habitable zone
    }
    else
    {
      zone.push_back(2);//it is in the outer zone
    }
  }

}

void Solar::listOrbits()
{
  //for testing only
  for (int i=0;i<orbits.size();i++){
    //std::cout<<"orbit "<<i+1<<" = "<<orbits.at(i)<<" zone = "<<zone.at(i)<<std::endl;
  }
}
double Solar::getLuminosity()
{
  //std::cout<<"luminosity = "<<star_lumin<<std::endl;
  return star_lumin;
}

