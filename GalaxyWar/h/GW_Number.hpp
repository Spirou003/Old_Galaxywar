#ifndef GW_NUMBER_H
#define GW_NUMBER_H

#include "GW_Volatile.hpp"
#include "GW_TSL.hpp"

class GW_Number: public GW_Volatile
{
    public:
        GW_Number(void);
        static GW_Number* Create(cfloat X, cfloat Y, CSInt32 Value, UInt16 tei, UInt8 sat, char lum);
        static GW_Number* RandomCreate(cfloat X, cfloat Y, CSInt32 Value);
        static GW_Number* Create();
        bool SetValue(CSInt32 Value);
        int GetValue(void) const;
        static Image* IntegerToImage(int value, UInt16 teinte, UInt8 saturation, char luminosite);
        static float GetSize(CSInt32 Value);

        static bool Init(cbool previnit);
        static void Close(void);

        static Image Numbers[11];

        //herited:
            virtual void SetX(cfloat X);
            virtual void SetY(cfloat Y);
            /*virtual float GetX(void) const;
            virtual float GetY(void) const;*/
            virtual bool Draw(RenderWindow* App, cfloat dt);

    private:
        GW_Number(cfloat X, cfloat Y, CSInt32 Value, UInt16 tei, UInt8 sat, char lum);
        ~GW_Number(void);
        void NewSprite(void);

        static bool exists;

        float size, Time;
        UInt16 t;
        UInt8 s;
        char l;
        int value;
        Sprite* image;
};
#endif
