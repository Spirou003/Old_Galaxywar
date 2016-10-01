#ifndef GW_CRYPTOGRAPH_H
#define GW_CRYPTOGRAPH_H

#include "Typedefs.hpp"

class GW_Cryptograph
{
    public:
        GW_Cryptograph();
        GW_Cryptograph(CSInt16 p);
        ~GW_Cryptograph();
        void GenerateKey(CSInt16 p);
        void SetKey(CUInt8 tab[]);
        void Encrypt(CSInt32 nb, CUInt8 source[], UInt8 cible[]) const;
        void Decrypt(CSInt32 nb, CUInt8 source[], UInt8 cible[]) const;
        CUInt8* GetKey(void) const;

    private:
        UInt8 tabencrypt[256];
        UInt8 tabdecrypt[256];
};
#endif
