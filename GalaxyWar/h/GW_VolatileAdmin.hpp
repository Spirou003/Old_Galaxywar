#ifndef GW_VOLATILEADMIN_H
#define GW_VOLATILEADMIN_H

#include "../h/GW_Volatile.hpp"
#include "../t/GW_ArrayList.hpp"

class GW_VolatileAdmin
{
    public:
        GW_VolatileAdmin();
        ~GW_VolatileAdmin();
        void DrawAll(RenderWindow* App, cfloat dt);
        void RemoveAll(void);
        bool Add(GW_Volatile* obj);
        static bool Init(cbool previnit);
        static void Close(void);

    protected:
        GW_ArrayList<GW_Volatile> list[GW_Volatile::NBTYPES];
};
#endif
