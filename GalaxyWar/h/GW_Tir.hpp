#ifndef GW_TIR_H
#define GW_TIR_H

#include "GW_Collisionnable.hpp"
class GW_VolatileAdmin;

class GW_Tir: public GW_Collisionnable
{
    public:
        virtual             ~GW_Tir     (void);

        virtual     float   Power       (CSInt32 malus = 0) const = 0;
        virtual     float   GetVX       (void) const;
        virtual     float   GetVY       (void) const;
        virtual     bool    GetEnd      (void) const;
        virtual     float   GetRadius   (void) const = 0;

        static      bool    Init        (cbool previnit);
        static      void    Close       (void);

        //static      bool    GenericDead (GW_Tir* tir, GW_JeuData* truc, RenderWindow* App);
                    int     GetLevel    (void) const;

        virtual void End(void);

        //herited (GW_Collisionnable):
            //virtual void Paralyze(cfloat dt) = 0;
            //virtual void Carbonyze(cfloat dt) = 0;
            virtual     bool    Dead        (GW_JeuData* truc, RenderWindow* App) = 0;
            virtual     bool    IsDead      (void) const = 0;
            //virtual     bool    IsCollisionnable      (void) const;
            //virtual     bool    IsOut       (void) const;
            virtual     void    Action      (GW_JeuData* truc, cfloat dt, bool lim = true) = 0;
            virtual     void    Draw        (RenderWindow* App) = 0;
            //virtual     int     Type        (void) const = 0;
            virtual const Shape* GetPolygon (void) const = 0;
            //virtual float Effet(GW_NAMECLASS* obj, float self, float other) = 0;
            //virtual float Prepare(const GW_NAMECLASS* obj) const = 0;

    protected:
        bool end;
        float vx, vy;
        int Level;//, type;
};
#endif
