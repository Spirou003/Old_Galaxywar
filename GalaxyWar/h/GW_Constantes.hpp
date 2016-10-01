#ifndef GW_CONSTANTES_H
#define GW_CONSTANTES_H

#include <cstdlib>
#include <cstdio>
#include "Typedefs.hpp"

#define noconst
#define TEMPLATE(PARAM) template <typename PARAM >

#define WIN

#ifdef WIN
#define SEPARATOR "\\"
#endif
#ifdef LIN
#define SEPARATOR "/"
#endif

#define FILENAME(PARAM) "img" SEPARATOR PARAM ".png"

#define GW_ERROR         0
#define GW_SUCCESS       -1

#define GW_NBEVTKEEP     5

#define GW_HAUTEUR       300
#define GW_LARGEUR       250

//#define GW_NPLANET       20

#define GW_ETOILEHEIGHT  20
#define GW_PLANETHEIGHT  150
#define GW_BGVITESSE     3
#define GW_BGHAUTEUR     ((GW_HAUTEUR+(GW_ETOILEHEIGHT*2))/GW_BGVITESSE)


#define GW_FONTSIZE      30
#define GW_NBBUTTON      5

#define GW_NBARME        GW_Collisionnable::NBTIR
#define GW_ARRAYMULT     2

#endif
