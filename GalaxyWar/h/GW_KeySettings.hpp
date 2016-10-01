#ifndef GW_KEYSETTINGS_H
#define GW_KEYSETTINGS_H

#include "Typedefs.hpp"

class GW_KeySettings
{
    public:
        GW_KeySettings(void);
        ~GW_KeySettings(void);
        bool SetKey(CSInt32 tab[5]);
        bool SetIDKey(CSInt32 value, CSInt32 id);
        const int* GetKey(void) const;
        int GetIDKey(int id) const;

        enum IDKey
        {
            Up, Down, Left, Right, Fire
        };

    private:
        int Key[5];
};
#endif
