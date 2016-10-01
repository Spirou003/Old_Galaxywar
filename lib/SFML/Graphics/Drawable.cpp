#ifndef GW_SF_DRAWABLE_C
#define GW_SF_DRAWABLE_C

#include "Drawable.hpp"

void sf::Drawable::SetAlpha(const unsigned char a)
{
    myColor.a = a;
}

#endif