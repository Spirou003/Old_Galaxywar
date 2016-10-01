#ifndef GW_CRYPTOGRAPH_C
#define GW_CRYPTOGRAPH_C

#include <cstdlib>
#include "../h/GW_Cryptograph.hpp"

GW_Cryptograph::GW_Cryptograph()
{
    int i = 0;
    while (i < 256)
    {
        tabencrypt[i] = i;
        tabdecrypt[i] = i;
        i++;
    }
}

GW_Cryptograph::GW_Cryptograph(CSInt16 p)
{
    int i = 0;
    while (i < 256)
    {
        tabencrypt[i] = i;
        i++;
    }
    this->GenerateKey(p);
}

GW_Cryptograph::~GW_Cryptograph()
{
    ;
}

void GW_Cryptograph::GenerateKey(CSInt16 p)
{
    int i = 0;
    UInt8 p1, p2, val;
    while (i < p)
    {
        p1 = rand()%256;
        p2 = (rand()+p1)%256;
        val = tabencrypt[int(p1)];
        tabencrypt[int(p1)] = tabencrypt[int(p2)];
        tabencrypt[int(p2)] = val;
        i++;
    }
    i = 0;
    while (i < 256)
    {
        tabdecrypt[int(tabencrypt[i])] = i;
        i++;
    }
}

void GW_Cryptograph::SetKey(CUInt8 tab[])
{
    int i = 0;
    while (i < 256)
    {
        tabencrypt[i] = tab[i];
        tabdecrypt[int(tabencrypt[i])] = i;
        i++;
    }
}

void GW_Cryptograph::Encrypt(CSInt32 nb, CUInt8 source[], UInt8 cible[]) const
{
    int i = 0;
    while (i < nb)
    {
        cible[i] = tabencrypt[int(source[i])];
        i++;
    }
}

void GW_Cryptograph::Decrypt(CSInt32 nb, CUInt8 source[], UInt8 cible[]) const
{
    int i = 0;
    while (i < nb)
    {
        cible[i] = tabdecrypt[int(source[i])];
        i++;
    }
}

CUInt8* GW_Cryptograph::GetKey(void) const
{
    return tabencrypt;
}

#endif
