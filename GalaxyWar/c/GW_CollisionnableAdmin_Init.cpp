#ifndef GW_COLLISIONNABLEADMIN_DRAW_C
#define GW_COLLISIONNABLEADMIN_DRAW_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_CollisionnableIncluser.hpp"

#include "../h/GW_TSL.hpp"

float GW_Ennemi_A::width = 1;       float GW_Ennemi_A::height = 1;
float GW_Ennemi_B::width = 1;       float GW_Ennemi_B::height = 1;
float GW_Ennemi_C::size = 1;
float GW_Ennemi_D::width = 1;       float GW_Ennemi_D::height = 1;
float GW_Ennemi_E::size[3] = {1,1,1};
float GW_Ennemi_F::width = 1;       float GW_Ennemi_F::height = 1;
float GW_Ennemi_G::size = 1;
float GW_Ennemi_H::width = 1;       float GW_Ennemi_H::height = 1;
float GW_Ennemi_I::width = 1;       float GW_Ennemi_I::height = 1;
float GW_Ennemi_L::size = 30;
float GW_Joueur::width = 1;         float GW_Joueur::height = 1;

float GW_Tir_A::size = 1;
float GW_Tir_B::size = 1;
float GW_Tir_C::width = 1, GW_Tir_C::height = 1;
int GW_Tir_Kube::SizeKube = GW_Ennemi_K::SizeKube;

float GW_Ennemi_J::SizeNoyau = 1;

Shape GW_Ennemi_A::polygon;
Shape GW_Ennemi_B::polygon;
Shape GW_Ennemi_F::polygon;
Shape GW_Ennemi_H::polygon[2];
Shape GW_Ennemi_I::polygon;
Shape GW_Joueur::polygon;

Sprite GW_Ennemi_A::SPRITEA[2];
Sprite GW_Ennemi_B::SPRITEB[2];
Sprite GW_Ennemi_C::SPRITEC[2];
Sprite GW_Ennemi_D::SPRITED[2][2];
Sprite GW_Ennemi_E::SPRITEE[2][3];
Sprite GW_Ennemi_F::SPRITEF[2];
Sprite GW_Ennemi_G::SPRITEG[2];
Sprite GW_Ennemi_H::SPRITEH[2][2];
Sprite GW_Ennemi_I::SPRITEI[2][4];
Sprite GW_Ennemi_J::SPRITEJ[2][6];
Sprite GW_Ennemi_J::NOYAU;
Sprite GW_Joueur::SPRITEJOUEUR[4];
Sprite GW_Joueur::LifeBar;
Sprite GW_Ennemi_K::SPRITIKUBE;

Sprite GW_Tir_A::SPRITIR;
Sprite GW_Tir_B::SPRITIR[6];
Sprite GW_Tir_C::SPRITIR[5];
Sprite GW_Tir_Kube::SPRITIRKUBE;
Sprite GW_Tir_Y::SPRITIR[3];
Image* GW_Tir_Y::img;
Shape GW_Tir_X::SPRITIR;
Shape GW_Tir_Z::SPRITIR;
Shape GW_Tir_Z::OMBRE[2];

extern Color GW_BGCOLOR;

bool GW_Ennemi_A::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab[2];
    if (GW_MassLoadImages(tab, 2, 1, 14, "img"SEPARATOR"1.", ".png"))
    {
        GW_SetNoSmooth(tab[0], &SPRITEA[0]);
        GW_SetNoSmooth(tab[1], &SPRITEA[1]);
        GW_ToCenter(SPRITEA[0]);
        GW_ToCenter(SPRITEA[1]);
        //*/
        polygon.AddPoint(18, 0);
        polygon.AddPoint(-15, 14.5);
        polygon.AddPoint(-15, -14.5);
        /*/
        polygon.AddPoint(18, 0);
        polygon.AddPoint(20.86264605, 2.37314202);
        polygon.AddPoint(20.86264605, 3.910043287);
        //*/
        exists = true;
        width = SPRITEA[0].GetSize().x;
        height = SPRITEA[0].GetSize().y;
        return true;
    }
    else
    {
        return false;
    }
}

bool GW_Ennemi_B::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab[2];
    if (GW_MassLoadImages(tab, 2, 1, 14, "img"SEPARATOR"2.", ".png"))
    {
        GW_SetNoSmooth(tab[0], &SPRITEB[0]);
        GW_SetNoSmooth(tab[1], &SPRITEB[1]);
        GW_ToCenter(SPRITEB[0]);
        GW_ToCenter(SPRITEB[1]);
        //*/
        polygon.AddPoint(11.5, 0);
        polygon.AddPoint(-11.5, 12.5);
        polygon.AddPoint(-11.5, -12.5);
        /*/
        polygon.AddPoint(11.5, 0);
        polygon.AddPoint(16.98528775, 2.314551911);
        polygon.AddPoint(16.98528775, 3.968633396);
        //*/
        exists = true;
        width = SPRITEB[0].GetSize().x;
        height = SPRITEB[0].GetSize().y;
        return true;
    }
    else
    {
        return false;
    }
}

bool GW_Ennemi_C::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab[2];
    if (GW_MassLoadImages(tab, 2, 1, 14, "img"SEPARATOR"3.", ".png"))
    {
        GW_SetNoSmooth(tab[0], &SPRITEC[0]);
        GW_SetNoSmooth(tab[1], &SPRITEC[1]);
        GW_ToCenter(SPRITEC[0]);
        GW_ToCenter(SPRITEC[1]);
        exists = true;
        size = SPRITEC[0].GetSize().x;
        return true;
    }
    else
    {
        return false;
    }
}

bool GW_Ennemi_D::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab1[2] = {NULL};
    Image* tab2[2] = {NULL};
    if (GW_MassLoadImages(tab1, 2, 1, 14, "img"SEPARATOR"4.", ".png"))
    {
        if (GW_MassDuplicate(tab1, tab2, 2))
        {
            int i = 0;
            while (i < 2)
            {
                GW_Saturation(tab2[i], 255);
                GW_SetNoSmooth(tab1[i], &SPRITED[0][i]);
                GW_SetNoSmooth(tab2[i], &SPRITED[1][i]);
                SPRITED[0][i].SetCenter(15, 14);
                SPRITED[1][i].SetCenter(15, 14);
                i++;
            }
            width = SPRITED[0][0].GetSize().x;
            height = SPRITED[0][0].GetSize().y;
            exists = true;
            return true;
        }
        delete(tab1[1]);
        delete(tab1[0]);
    }
    return false;
}

bool GW_Ennemi_E::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab[2][3] = {{NULL}};
    if (GW_MassLoadImages(tab[0], 3, 1, 14, "img"SEPARATOR"5.1", ".png"))
    {
        if (GW_MassLoadImages(tab[1], 3, 1, 14, "img"SEPARATOR"5.2", ".png"))
        {
            int i = 0, j = 0;
            while (j < 3)
            {
                i = 0;
                while (i < 2)
                {
                    GW_SetNoSmooth(tab[i][j], &SPRITEE[i][j]);
                    GW_ToCenter(SPRITEE[i][j]);
                    i++;
                }
                size[j] = SPRITEE[0][j].GetSize().x;
                j++;
            }
            exists = true;
            return true;
        }
        delete(tab[0][0]);
        delete(tab[0][1]);
        delete(tab[0][2]);
    }
    return false;
}

bool GW_Ennemi_F::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab[2];
    if (GW_MassLoadImages(tab, 2, 1, 14, "img"SEPARATOR"6.", ".png"))
    {
        GW_SetNoSmooth(tab[0], &SPRITEF[0]);
        GW_SetNoSmooth(tab[1], &SPRITEF[1]);
        GW_ToCenter(SPRITEF[0]);
        GW_ToCenter(SPRITEF[1]);
        //*/
        polygon.AddPoint(-22, 7);
        polygon.AddPoint(21, 12);
        polygon.AddPoint(19, -18);
        polygon.AddPoint(-21, -25);
        /*/
        polygon.AddPoint(23.08679276, 2.833539873);
        polygon.AddPoint(24.18677324, 0.519146114);
        polygon.AddPoint(26.17250466, 5.524807593);
        polygon.AddPoint(32.64965543, 4.013729156);
        //*/
        exists = true;
        width = 50;
        height = 42;
        return true;
    }
    else
    {
        return false;
    }
}

bool GW_Ennemi_G::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab[2];
    if (GW_MassLoadImages(tab, 2, 1, 14, "img"SEPARATOR"7.", ".png"))
    {
        GW_SetNoSmooth(tab[0], &SPRITEG[0]);
        GW_SetNoSmooth(tab[1], &SPRITEG[1]);
        GW_ToCenter(SPRITEG[0]);
        GW_ToCenter(SPRITEG[1]);
        exists = true;
        size = SPRITEG[0].GetSize().x;
        return true;
    }
    else
    {
        return false;
    }
}

bool GW_Ennemi_H::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab1[2] = {NULL};
    Image* tab2[2] = {NULL};
    if (GW_MassLoadImages(tab1, 2, 1, 14, "img"SEPARATOR"8.", ".png"))
    {
        if (GW_MassDuplicate(tab1, tab2, 2))
        {
            int i = 0;
            while (i < 2)
            {
                GW_Saturation(tab2[i], 255);
                GW_SetNoSmooth(tab1[i], &SPRITEH[0][i]);
                GW_SetNoSmooth(tab2[i], &SPRITEH[1][i]);
                GW_ToCenter(SPRITEH[i][0]);
                SPRITEH[i][1].SetCenter(10, 15);
                i++;
            }
            width = SPRITEH[0][0].GetSize().x;
            height = SPRITEH[0][0].GetSize().y;
            //*/
            polygon[0].AddPoint(-29, -13);
            polygon[0].AddPoint(-18, -22);
            polygon[0].AddPoint(29, -4.5);
            polygon[0].AddPoint(29, 4.5);
            polygon[0].AddPoint(-18, 22);
            polygon[0].AddPoint(-29, 13);

            polygon[1].AddPoint(-23, 21);
            polygon[1].AddPoint(18, 21);
            polygon[1].AddPoint(18, -21);
            polygon[1].AddPoint(-23, -21);
            /*/
            GW_Ennemi_H::polygon[0].AddPoint(31.78049716, 3.56301186);
            GW_Ennemi_H::polygon[0].AddPoint(28.42530481, 4.026659469);
            GW_Ennemi_H::polygon[0].AddPoint(29.34706118, 6.129240643);
            GW_Ennemi_H::polygon[0].AddPoint(29.34706118, 0.153944664);
            GW_Ennemi_H::polygon[0].AddPoint(28.42530481, 2.256525838);
            GW_Ennemi_H::polygon[0].AddPoint(31.78049716, 2.720173447);

            GW_Ennemi_H::polygon[1].AddPoint(31.144823, 2.40161777);
            GW_Ennemi_H::polygon[1].AddPoint(27.65863337, 0.862170055);
            GW_Ennemi_H::polygon[1].AddPoint(27.65863337, 5.421015253);
            GW_Ennemi_H::polygon[1].AddPoint(31.144823, 3.881567538);
            //*/
            exists = true;
            return true;
        }
        delete(tab1[1]);
        delete(tab1[0]);
    }
    return false;
}

bool GW_Ennemi_I::Init(cbool previnit)
{
    if (exists)
    {
        return false;
    }
    int i = 0;
    Image* tab[4] = {NULL};
    Image* tab2[4] = {NULL};
    if (GW_MassLoadImages(tab, 4, 1, 14, "img"SEPARATOR"9.1", ".png"))
    {
        if (GW_MassDuplicate(tab, tab2, 4))
        {
            while (i < 4)
            {
                GW_Teinte(tab2[i], 1024);
                GW_SetNoSmooth(tab[i], &SPRITEI[0][i]);
                GW_SetNoSmooth(tab2[i], &SPRITEI[1][i]);
                GW_ToCenter(SPRITEI[0][i]);
                GW_ToCenter(SPRITEI[1][i]);
                i++;
            }
            //*/
            polygon.AddPoint(-10, 0);
            polygon.AddPoint(0, 17);
            polygon.AddPoint(10, 0);
            polygon.AddPoint(0, -17);
            /*/
            polygon.AddPoint(10, M_PI);
            polygon.AddPoint(17, M_PI/2);
            polygon.AddPoint(10, 0);
            polygon.AddPoint(17, 3*M_PI/2);
            //*/
            width = SPRITEI[0][0].GetSize().x;
            height = SPRITEI[0][0].GetSize().y;
            exists = true;
            return true;
        }
        while (i < 4)
        {
            delete(tab[i]);
            i++;
        }
    }
    return false;
}

bool GW_Ennemi_J::Init(cbool previnit)
{
    if (exists)
    {
        return false;
    }
    Image* image = GW_CreateFromFile(FILENAME("10.0"));
    if (image == NULL)
    {
        return false;
    }
    else
    {
        GW_SetNoSmooth(image, &NOYAU);
        SizeNoyau = NOYAU.GetSize().x;
        GW_ToCenter(NOYAU);
    }
    int i = 0, j = 0;
    Image* tab[2][6] = {{NULL}};
    if (GW_MassLoadImages(tab[0], 6, 1, 14, "img"SEPARATOR"10.", ".png"))
    {
        if (GW_MassDuplicate(tab[0], tab[1], 6))
        {
            while (j < 6)
            {
                i = 0;
                GW_TSL(tab[1][j], 680, 40, 35);
                while (i < 2)
                {
                    GW_SetNoSmooth(tab[i][j], &SPRITEJ[i][j]);
                    GW_ToCenter(SPRITEJ[i][j]);
                    i++;
                }
                j++;
            }
            exists = true;
            return true;
        }
        while (i < 6)
        {
            delete(tab[i]);
            i++;
        }
    }
    delete(image);
    return false;
}

bool GW_Ennemi_K::Init(cbool previnit)
{
    GW_ToCenter(SPRITIKUBE);
    return previnit;
}

bool GW_Ennemi_L::Init(cbool previnit)
{
    return previnit;
}

bool GW_Joueur::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* tab[4];
    if (GW_MassLoadImages(tab, 4, 0, 14, "img"SEPARATOR"0.", ".png"))
    {
        int i = 4;
        while (i > 0)
        {
            i--;
            GW_SetNoSmooth(tab[i], &SPRITEJOUEUR[i]);
            SPRITEJOUEUR[i].SetCenter(SPRITEJOUEUR[i].GetSize().x/2, 2-(SPRITEJOUEUR[3].GetSize().y/2));
        }
        GW_ToCenter(SPRITEJOUEUR[3]);
        //*/
        polygon.AddPoint(2, -14.5);
        polygon.AddPoint(-2, -14.5);
        polygon.AddPoint(-12.5, 8.5);
        polygon.AddPoint(12.5, 8.5);
        /*/
        GW_Joueur::polygon.AddPoint(14.63728117, 4.849455155);
        GW_Joueur::polygon.AddPoint(14.63728117, 4.575322806);
        GW_Joueur::polygon.AddPoint(15.11621646, 2.544415995);
        GW_Joueur::polygon.AddPoint(15.11621646, 0.597176658);
        //*/
        exists = true;
        width = SPRITEJOUEUR[3].GetSize().x;
        height = SPRITEJOUEUR[3].GetSize().y;
        GW_Joueur_INITJPOS = GW_HAUTEUR - height*1.5;
        LifeBar.SetScale(width, 2);
        LifeBar.SetCenter(0, -(4+(int)height/2)/2);
        return true;
    }
    else
    {
        return false;
    }
}

bool GW_Tir_A::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* img = new Image();
    if (img != NULL)
    {
        if (img->LoadFromFile("img\\tirvso1.png"))
        {
            GW_SetNoSmooth(img, &SPRITIR);
            SPRITIR.SetCenter(SPRITIR.GetSize().x/2, SPRITIR.GetSize().y/6);
            exists = true;
            size = SPRITIR.GetSize().y;
            SPRITIR.SetColor(RandomColor());
            //SPRITIR.SetColor(Color(255,196,128,255));
            return true;
        }
        delete(img);
    }
    return false;
}

bool GW_Tir_B::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* ptr[6];
    if (GW_MassLoadImages(ptr, 6, 0, 14, "img"SEPARATOR"b.", ".png"))
    {
        int i = 0;
        while (i < 6)
        {
            GW_SetNoSmooth(ptr[i], &SPRITIR[i]);
            GW_ToCenter(SPRITIR[i]);
            i++;
        }
        size = ptr[0]->GetWidth()/2;
        exists = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool GW_Tir_C::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    Image* ptr[5];
    if (GW_MassLoadImages(ptr, 5, 1, 14, "img"SEPARATOR"f.", ".png"))
    {
        int i = 0;
        while (i < 5)
        {
            GW_SetNoSmooth(ptr[i], &SPRITIR[i]);
            GW_ToCenter(SPRITIR[i]);
            i++;
        }
        width = ptr[0]->GetWidth();
        height = width/10;
        exists = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool GW_Tir_Kube::Init(cbool previnit)
{
    GW_ToCenter(SPRITIRKUBE);
    return previnit;
}

bool GW_Tir_X::Init(cbool previnit)
{
    SPRITIR.EnableFill(true);
    SPRITIR.AddPoint(0, 0, Color(0, 0, 0, 0), Color(0, 0, 0, 0));
    SPRITIR.AddPoint(1, 0, Color(0, 0, 0, 0), Color(0, 0, 0, 0));
    SPRITIR.AddPoint(0.9, 0.4, Color(0, 0, 0, 0), Color(0, 0, 0, 0));
    SPRITIR.AddPoint(0, 0.5, Color(0, 0, 0, 0), Color(0, 0, 0, 0));
    SPRITIR.SetScale(16, 20);
    return previnit;
}

bool GW_Tir_Y::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    img = GW_CreateFromFile(FILENAME("tir"));
    if (img != NULL)
    {
        SPRITIR[0].SetImage(*img);
        Image *ptr = new Image(*img);
        if (ptr != NULL)
        {
            GW_Teinte(ptr, 512);
            SPRITIR[1].SetImage(*ptr);
            ptr = new Image(*img);
            if (ptr != NULL)
            {
                GW_Teinte(ptr, 1024);
                SPRITIR[2].SetImage(*ptr);
                GW_ToCenter(SPRITIR[0]);
                GW_ToCenter(SPRITIR[1]);
                GW_ToCenter(SPRITIR[2]);
                exists = true;
                return true;
            }
            delete(SPRITIR[1].GetImage());
        }
        delete(SPRITIR[0].GetImage());
    }
    return true;
}

bool GW_Tir_Z::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    GW_AddOctogon(&SPRITIR, Color(96, 255, 96, 255), Color(0, 224, 0, 255));
    GW_AddOctogon(&OMBRE[0], Color(255, 96, 96, 255), Color(255, 0, 0, 255));
    GW_AddOctogon(&OMBRE[1], Color(96, 96, 255, 255), Color(0, 0, 255, 255));
    SPRITIR.SetOutlineWidth(0.3333);
    OMBRE[0].SetOutlineWidth(0.3333);
    OMBRE[1].SetOutlineWidth(0.3333);
    return true;
}

#endif
