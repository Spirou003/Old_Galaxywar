#ifndef GW_VOLATILE_C
#define GW_VOLATILE_C

#include "../h/GW_Volatile.hpp"

GW_Volatile::GW_Volatile(){}
GW_Volatile::~GW_Volatile(){}
void GW_Volatile::SetX(cfloat X){x = X;}
void GW_Volatile::SetY(cfloat Y){y = Y;}
float GW_Volatile::GetX(void) const{return x;}
float GW_Volatile::GetY(void) const{return y;}
char GW_Volatile::Type(void) const{return type;}

#endif
