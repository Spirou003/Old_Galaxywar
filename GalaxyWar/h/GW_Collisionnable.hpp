#ifndef GW_COLLISIONNABLE_H
#define GW_COLLISIONNABLE_H

#include "GW_Constantes.hpp"
struct GW_JeuData;
#include <cmath>
#include "GW_Functions.hpp"
#include "../t/GW_ArrayList.hpp"
#include "GW_CollisionnableAdmin.hpp"

class GW_Collisionnable
{
    public:
        GW_Collisionnable(void);
        virtual ~GW_Collisionnable(void);
        virtual const Shape* GetPolygon(void) const = 0;
        static bool Collision(const GW_Collisionnable* obj1, const GW_Collisionnable* obj2);
        static int Type(GW_Collisionnable* obj);
        virtual void Draw(RenderWindow* App) = 0;
        virtual     bool    IsDead      (void) const = 0;
        virtual     bool    IsCollisionnable      (void) const;
        virtual     bool    IsOut       (void) const;
        bool IsDeletable(void);
        //virtual float Effet(GW_Collisionnable* obj, float self, float other) = 0;
        //virtual float Prepare(const GW_Collisionnable* obj) const = 0;
        //virtual void Paralyze(cfloat dt) = 0;
        //virtual void Carbonyze(cfloat dt) = 0;
        virtual     float   GetX        (void) const;
        virtual     float   GetY        (void) const;
        virtual     float   GetAngle    (void) const;
        virtual     void    Action      (GW_JeuData* truc, cfloat dt, bool lim = true) = 0;
        virtual     bool    Dead        (GW_JeuData* truc, RenderWindow* App) = 0;
        static void EffetCollision(GW_Collisionnable* obj1, GW_Collisionnable* obj2);
        static void ClassicDraw(RenderWindow* App, Drawable* spr, cfloat x, cfloat y, cfloat angle);

        static Shape Octogon, Carre;

        enum Type
        {
            TA, TB, TC, TKU, TW, TX, TY, TZ, NBTIR, EA, EB, EC, ED, EE, EF, EG, EH, EI, EJ, EK, EL, EM, EN, EO, EP, EQ, ER, ES, ET, EU, EV, EW, EX, EY, EZ, EJO, NBOBJ
        };

        static CUInt32 NBENN = NBOBJ-NBTIR-1;

    protected:
        static void ClassicDraw(RenderWindow* App, Drawable* spr, GW_Collisionnable* obj);
        static void PolygonProjectionToDroiteCentered(const Shape* polygon, CSInt32 nb, cfloat a, cfloat b, float* min, float* max, const GW_Collisionnable* obj);

        float x, y, angle, scaleX, scaleY, dmax;
        int type;

    private:
        bool isdelete;
};
#endif
