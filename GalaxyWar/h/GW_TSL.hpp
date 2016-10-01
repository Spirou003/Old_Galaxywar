#ifndef GW_TSL_H
#define GW_TSL_H

#include "Typedefs.hpp"
#include "GW_GraphicsDeclarer.hpp"

void GW_Teinte(sf::Image* img, UInt16 effet);
void GW_Saturation(sf::Image* img, UInt8 effet);
void GW_Luminosite(sf::Image* img, char effet);
void GW_TSL(sf::Image* img, UInt16 teinte, UInt8 saturation, char luminosite);

#endif
