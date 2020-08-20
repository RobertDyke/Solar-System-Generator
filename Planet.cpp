#include "Planet.h"
#include <iomanip>
/*
  Planet randomly generates planets.

*/

Planet::Planet(double orb, int oz, double cr, double dm, double dy, double lm)
{
    orbital_radius = orb;
    orbital_zone = oz;
    core = cr;
    diameter = dm;
    density = dy;

    double radius = diameter/2.0;
    double gravity_metric {0.0};//gravity in meters per second squared
    volume_sphere = (4/3)*pi*(pow(radius,3));
    mass = volume_sphere*density/volume_of_earth;
    gravity_metric = G*mass*mass_of_earth/pow((radius*1000),2);//radius must be in meters and not kilometers
    gravity = gravity_metric/earth_g;

    // temperature calculation is T=((L)(0.65)/16pi * boltzmann's constant * orbital distance squares)e+0.25
    //reduced below. 36 is plus 36 degrees Kelvin to account for the greenhouse effect
    
    double temp1 = lm * 3.95e+9;
    double temp2 = pow(orbital_radius,2);
    double temp3 = pow((temp1/temp2),0.25);
    double temp4 = temp3 + 36.0;//Kelvin
    temperature = ((temp4 - 273.15)*(9/5)) + 32.0;//Kelvin to Farenheit
    //mmwr = (pow(1.86,19))*temp3*orbital_radius*(pow(1.0, 3))/(mass*pow(5.98,24));//wrong formula
    mmwr = (pow(3.11,-3))*temp3*orbital_radius/mass;
    atmos_type ={"Vacuum"};
    if(mmwr<=119)
    {
      atmos_type ={"Very Thin"};
      if(orbital_zone==3)
      {
        world_type ={"Ice Ball"};
      }
    }
    if(mmwr<=79)
    {
      atmos_type ={"Thin"};
      if(orbital_zone==3)
      {
        world_type ={"Failed Core"};
      }
    }
    if(mmwr<=39)
    {
      atmos_type ={"Standard"};
      if(orbital_zone==1)
      {
        world_type ={"Hot House"};
      }
      if(orbital_zone==2)
      {
        world_type ={"Desert"};
        if(orbital_zone==3)
      {
        world_type ={"Failed Core"};
      }
      }
    }
    if(mmwr<=19)
    {
      atmos_type ={"Dense"};
      if(orbital_zone==1)
      {
        world_type ={"Hot House"};
      }
      if(orbital_zone==2)
      {
        world_type ={"Garden"};
      }
      if(orbital_zone==3)
      {
        world_type ={"Failed Core"};
      }
    }
    if(mmwr<=4)
    {
      atmos_type ={"Massive"};
      world_type ={"Gas Giant"};
      if(orbital_zone==2)
      {

      }
      
    }
      
        //std::cout<<"temp1 = "<<temp1<<" temp2 = "<<temp2<<" temp3 = "<<temp3<<std::endl;
    //temperature = (pow((lm * (3.95e+9))/pow(orbital_radius,2)),0.25) + 36.0;
    

}

double Planet::volume() const// Volume of a Planet 
  //const here means that the values are not changed by the function
  {
    return core*diameter*density;
  }


void Planet::listTitle() const{
  std::cout<<std::setw(zone_width)<<"Zone"
  <<sep<<std::setw(orbit_width)<<"Orbit "
  <<sep<<std::setw(diameter_width)<<"Diameter"
  <<sep<<std::setw(mass_width)<<"Mass"
  <<sep<<std::setw(gravity_width)<<"Gravity"
  <<sep<<std::setw(temperature_width)<<"Temperature"
  <<sep<<std::setw(type_width)<<"Type"<<std::endl;
  std::cout<<std::setw(zone_width)<<" "
  <<sep<<std::setw(orbit_width)<<"(Earth=1.0)"
  <<sep<<std::setw(diameter_width)<<"Kilometers"
  <<sep<<std::setw(mass_width)<<"(Earth=1.0)"
  <<sep<<std::setw(gravity_width)<<"(Earth=1.0)"
  <<sep<<std::setw(temperature_width)<<"Celsius "
  <<sep<<std::setw(type_width)<<" "<<std::endl;
  std::cout<<"------------------------------------------------------------------------------------------------------"<<std::endl;
}
void Planet::listPlanets() const{
   /*
    std::cout<<"orbit = "<<orbital_radius<<" zone = "<<orbital_zone<<" diameter = "<<diameter;
    std::cout<<" mass = "<<mass<<" gravity = "<<gravity<<" temperature = "<<temperature<<" "<<world_type<<std::endl;
  */
 
  std::cout<<std::setw(zone_width)<<orbital_zone
  <<sep<<std::setw(orbit_width)<<std::setprecision(2)<<orbital_radius
  <<sep<<std::setw(diameter_width)<<std::setprecision(5)<<diameter
  <<sep<<std::setw(mass_width)<<std::setfill(' ')<<std::setprecision(6)<<mass
  <<sep<<std::setw(gravity_width)<<std::setfill(' ')<<std::setprecision(6)<<gravity
  <<sep<<std::setw(temperature_width)<<std::setfill(' ')<<std::setprecision(6)<<temperature
  <<sep<<std::setw(type_width)<<std::setfill(' ')<<std::setprecision(6)<<world_type<<std::endl;

}