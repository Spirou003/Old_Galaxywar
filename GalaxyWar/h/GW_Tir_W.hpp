#ifndef GW_TIR_W_H
#define GW_TIR_W_H

#include "GW_Tir.hpp"

#define GW_NAMECLASS GW_Tir_W

class GW_NAMECLASS: public GW_Tir
{
    public:
        static bool Init(cbool previnit);
        static void Close(void);
        GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle);
        virtual float Power(CSInt32 malus = 0) const;
        virtual ~GW_NAMECLASS(void);
        virtual float GetRadius(void) const;
        void Stop(void);

        static CSInt32 VITESSE = 330;
        static Sprite SPRITIR[2];
        //static Shape Polygon;
        static float size;

        //herited (GW_Collisionnable):
            //virtual void Paralyze(cfloat dt);
            //virtual void Carbonyze(cfloat dt);
            virtual     bool    Dead        (GW_JeuData* truc, RenderWindow* App);
            virtual     bool    IsDead      (void) const;
            //virtual     bool    IsCollisionnable      (void) const;
            //virtual     bool    IsOut       (void) const;
            virtual     void    Action      (GW_JeuData* truc, cfloat dt, bool lim = true);
            virtual     void    Draw        (RenderWindow* App);
            //virtual     int     Type        (void) const;
            virtual const Shape* GetPolygon (void) const;
            //virtual float Effet(GW_NAMECLASS* obj, float self, float other);
            //virtual float Prepare(const GW_NAMECLASS* obj) const;

    private:
        static bool exists;

        bool stop;
        float p;
};
#undef GW_NAMECLASS
#endif
