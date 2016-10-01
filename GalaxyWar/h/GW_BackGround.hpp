#ifndef GW_BACKGROUND_H
#define GW_BACKGROUND_H

#include "GW_Constantes.hpp"
#include "GW_GraphicsDeclarer.hpp"

class GW_BackGround
{
    public:
                        GW_BackGround       (void);
                        ~GW_BackGround      (void);

        static  void    Close               (void);
        static  void    Init                (void);
        static  bool    Load                (void);

                void    Display             (RenderWindow* App);
                void    Generate            (void);
                void    PlaneteGenerate     (void);
        static  float   RandomSizeEtoile    (void);
                void    SetDisplay          (cbool truc);

    private:
        float xTab[GW_BGHAUTEUR];
        float yTab[GW_BGHAUTEUR];
        float Size[GW_BGHAUTEUR];
        short x, y;
        float s, a;
        short LastID;
        bool isAffiched;
        char cste;
};
#endif
