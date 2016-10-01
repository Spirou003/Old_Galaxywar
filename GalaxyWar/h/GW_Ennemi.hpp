#ifndef GW_ENNEMI_H
#define GW_ENNEMI_H

#include "GW_Collisionnable.hpp"
class GW_VolatileAdmin;
class GW_Tir;

class GW_Ennemi: public GW_Collisionnable
{
    public:
                            GW_Ennemi   (void);
        virtual             ~GW_Ennemi  (void);

        static      void    Close       (void);
        virtual     int     Degats      (GW_JeuData* truc, GW_Tir* tir) = 0;
        //static      bool    GenericDead (GW_Ennemi* unite, GW_JeuData* truc, RenderWindow* App);
        static      bool    Init        (cbool previnit);
        virtual     int     Points      (void) const = 0;
        static void AddResistances(GW_Ennemi* obj, CSInt32 Niv);

        //herited(GW_Collisionnable):
            virtual     bool    Dead        (GW_JeuData* truc, RenderWindow* App) = 0;
            virtual     bool    IsDead      (void) const = 0;
            //virtual     bool    IsCollisionnable      (void) const;
            //virtual     bool    IsOut       (void) const;
            virtual     void    Action      (GW_JeuData* truc, cfloat dt, bool lim = true) = 0;
            virtual const Shape* GetPolygon (void) const = 0;
            virtual     void    Draw        (RenderWindow* App) = 0;
            //virtual void Paralyze(cfloat dt) = 0;
            //virtual void Carbonyze(cfloat dt) = 0;
            //virtual float Effet(GW_NAMECLASS* obj, float self, float other) = 0;
            //virtual float Prepare(const GW_NAMECLASS* obj) const = 0;

    protected:
        int Resistances[GW_NBARME];
};
#endif
