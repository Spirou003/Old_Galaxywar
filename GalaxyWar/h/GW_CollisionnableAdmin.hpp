#ifndef GW_COLLISIONNABLEADMIN_H
#define GW_COLLISIONNABLEADMIN_H

#include "GW_GraphicsDeclarer.hpp"
#include "GW_Constantes.hpp"
#include "GW_JeuData.hpp"

class GW_CollisionnableAdmin
{
    public:
        static bool Init(cbool previnit);
        static void Close(void);
        static bool GW_Ennemi_GenericDead(GW_Ennemi* unite, GW_JeuData* truc, RenderWindow* App);
        static bool GW_Tir_GenericDead(GW_Tir* unite, GW_JeuData* truc, RenderWindow* App);
        static bool AddEnnemies(GW_JeuData* Data);

    private:
        virtual void truc(void) = 0;
};
#endif
