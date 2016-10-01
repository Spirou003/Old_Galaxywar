#ifndef GW_KEYSETTINGS_C
#define GW_KEYSETTINGS_C

#include "../h/GW_KeySettings.hpp"

GW_KeySettings::GW_KeySettings(void)
{
    /*/
    Key[0] = Key::Up;
    Key[1] = Key::Down;
    Key[2] = Key::Left;
    Key[3] = Key::Right;
    Key[4] = Key::M;
    /*/
    Key[0] = 293;
    Key[1] = 294;
    Key[2] = 291;
    Key[3] = 292;
    Key[4] = 'm';//277:space
}

GW_KeySettings::~GW_KeySettings(void)
{
    ;
}

bool GW_KeySettings::SetIDKey(int value, int id)
{
    int i = 0;
    while (i < 5)
    {
        if (Key[i] == value)
        {
            return false;
        }
        i++;
    }
    Key[id] = value;
    return true;
}

bool GW_KeySettings::SetKey(CSInt32 tab[5])
{
    GW_KeySettings nouveau;
    int i = 0;
    while (i < 5)
    {
        if (!nouveau.SetIDKey(tab[i], i))
        {
            return false;
        }
        i++;
    }
    i = 0;
    while (i < 5)
    {
        Key[i] = tab[i];
        i++;
    }
    return true;
}

const int* GW_KeySettings::GetKey(void) const
{
    return Key;
}

int GW_KeySettings::GetIDKey(int id) const
{
    return Key[id];
}

#endif
