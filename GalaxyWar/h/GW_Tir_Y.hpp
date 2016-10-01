#ifndef GW_TIR_Y_H
#define GW_TIR_Y_H

#include "GW_Tir.hpp"

#define GW_NAMECLASS GW_Tir_Y

class GW_NAMECLASS: public GW_Tir
{
    public:
        static bool Init(cbool previnit);
        static void Close(void);
        GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle);
        virtual float Power(CSInt32 malus = 0) const;
        virtual ~GW_NAMECLASS(void);
        virtual float GetRadius(void) const;

        void SetX(float X);
        void SetY(float Y);
        void SetPower(float truc);

        static CSInt32 Vitesse = 80;
        static Sprite SPRITIR[3];

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
        static Image* img;

        void BDraw(RenderWindow* App, Sprite* spr, cfloat A, cfloat I, cfloat S);

        float id, a, sens;
        int ID;
};
#undef GW_NAMECLASS
#endif
