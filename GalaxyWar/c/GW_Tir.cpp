#ifndef GW_TIR_C
#define GW_TIR_C

#include "../h/GW_Tir.hpp"

        GW_Tir::~GW_Tir (void)      {}
int     GW_Tir::GetLevel(void) const{return Level;}
bool    GW_Tir::GetEnd  (void) const{return end;}
void    GW_Tir::End     (void)      {end = true;}
float   GW_Tir::GetVX   (void) const{return vx;}
float   GW_Tir::GetVY   (void) const{return vy;}
#endif
