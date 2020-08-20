# ReadMe for Capstone Project: Solar System Generator

This project takes a known real star and randomly generates a system of planets for it.
It generates a text list of the planets, their orbits, characteristics, and type.

All needed files are included in the project submission.

Main.cpp contains a few functions for general use such as random number generators. 
Solar.h and Solar.cpp contain the Solar class for deriving the luminosity of the star(i.e. surface temperature or how hot the star is) and the zones. The zones are inner, habitable, and outer (i.e. too hot, just right, too cold). The Orbit class determines the distance each planet is from the star. The first orbit is generated randomly. Each subsequent orbit takes the prior orbit as a seed to generate the next orbit. This insures that each orbit is larger than the prior one.
Planet.h and Planet.cpp generate the details of each planet. Diameter and density are determined randomly based on the zone the planet is it. Atmosphere and other stats are derived from diameter, density, and zone. 
  
 
  

## Build and run instructions
It uses cmake and make to compile. CMakeLists.txt is included. Run cmake in the build directory followed by make.
     Then run ./Solar to execute the project.
  

## Rubic Points
* Rubic_1: Loops, Functions, I/O: A variety of control structures are used. Main.cpp line 111
* Rubic_2: OOP: Code is organized into classes with class attributes and methods. Planet.h line 7
* Rubic_3: OOP: All data members are specified as public, protected, or private. Planet.h line 8
* Rubic_4: OOP: All class member functions document their effects. Solar.cpp line 6
* Rubic_5: OOP: Classes encapsuates behavior. Solar.cpp line 7
* 
## Other notes
Originally I planned to include a large list of stars that could be used to generate planets. That has been moved to a later version. Currently, it generates from the G2 star in the Alpha Centuari system. A few other near Earth stars are included in main.cpp between lines 79 and 91. Any of these can be used by commenting out Alpha Centauri and un-commenting the desired star. 



