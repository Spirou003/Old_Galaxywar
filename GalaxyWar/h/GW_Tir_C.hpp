#ifndef GW_TIR_C_H
#define GW_TIR_C_H

#include "GW_Tir.hpp"

#define GW_NAMECLASS GW_Tir_C

class GW_NAMECLASS: public GW_Tir
{
    public:
        static bool Init(cbool previnit);
        static void Close(void);
        GW_NAMECLASS(CSInt32 level, cfloat X, cfloat Y, cfloat Angle, cbool isdecalled = false, CSInt32 Ndiv = 12);
        virtual float Power(CSInt32 malus = 0) const;
        virtual ~GW_NAMECLASS(void);
        virtual float GetRadius(void) const;
        virtual bool IsCollisionnable(void) const;

        static void Tirs_Generate(CSInt32 level, cfloat x, cfloat y, float* t, GW_ArrayList<GW_Tir> *list);

        static CSInt32 VITESSE = 400;
        static Sprite SPRITIR[5];
        static float width, height;

        virtual void End(void);

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

        float t, s;
        int id, nbdiv;
        bool state;
        cbool ID;
};
#undef GW_NAMECLASS
#endif
