#ifndef GW_FUNCTIONS_C
#define GW_FUNCTIONS_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_Functions.hpp"
#include <cstdio>

void GW_SetNoSmooth(Image* img, Sprite* ptr)
{
    img->SetSmooth(false);
    ptr->SetImage(*img);
}

Color RandomColor(void)
{
    UInt8 C[3] = {0}, i = rand()%3, v;
    if ((rand()&7) != 0)
    {
        v = 0;
    }
    else
    {
        v = (rand()%3)*127;
    }
    C[i] = 255;
    i = (i+(rand()&1)+1)%3;
    C[i] = rand()&255;
    i = 0;
    while (i < 3)
    {
        C[i] = (C[i]*(255-v) + v*255)/255;
        i++;
    }
    return Color(C[0], C[1], C[2], 255);
}

float GW_RandomEcart(cfloat v, cfloat precis)
{
    return (v + Random(-precis, precis));
}

float GW_FloatModulo(cfloat n, cfloat module)
{
    return (n >= 0) ? n-module*(int)(n/module) : n-module*((int)(-1 + n/module));
}

int GW_Poly2nd(CSInt32 n)
{
    return (n%2 == 1) ? (n*n+2*n+1)/4 : (n*n+2*n)/4;
}

int Random(CSInt32 a, CSInt32 b)
{
    return Randomizer::Random(a, b);
}

float Random(cfloat a, cfloat b)
{
    return Randomizer::Random(a, b);
}

void GW_To_Center(Sprite* sprite)
{
    sprite->SetCenter(sprite->GetSize().x/2, sprite->GetSize().y/2);
}

void GW_AddOctogon(Shape* polygon, const Color &in, const Color &out)
{
    polygon->AddPoint(1, 0, in, out);
    polygon->AddPoint(0.707, 0.707, in, out);
    polygon->AddPoint(0, 1, in, out);
    polygon->AddPoint(-0.707, 0.707, in, out);
    polygon->AddPoint(-1, 0, in, out);
    polygon->AddPoint(-0.707, -0.707, in, out);
    polygon->AddPoint(0, -1, in, out);
    polygon->AddPoint(0.707, -0.707, in, out);
}

float GW_Angle(cfloat x, cfloat cx, cfloat y, cfloat cy)
{
    if (cx-x <= 0.0000001 && -0.0000001 <= cx-x)
    {
        if(cy > y)
        {
            return M_PI/2;
        }
        else
        {
            return 3*M_PI/2;
        }
    }
    else
    {
        float a;
        a = GW_Atan((cy-y)/(cx-x));
        if (cx < x)
        {
            a += M_PI;
        }
        return a;
    }
}

Image* GW_CreateFromFile(const char* str)
{
    Image* ptr = new Image();
    if (ptr == NULL)
    {
        return NULL;
    }
    if(ptr->LoadFromFile(str))
    {
        return ptr;
    }
    delete(ptr);
    return NULL;
}

float GW_Sin(cfloat angle)
{
    float a = angle;
    int c = 1;
    if (a > M_PI)
    {
        a -= M_PI;
        c = -1;
    }
    if (a > M_PI/2)
    {
        a = M_PI-a;
    }
    return (c * (-a*(a - M_PI/2)/3 +a*2/M_PI));
}

float GW_Cos(cfloat a)
{
    if (a <= 3*M_PI/2)
    {
        return GW_Sin(a+M_PI/2);
    }
    else
    {
        return GW_Sin(a-3*M_PI/2);
    }
}

float GW_Atan(cfloat a)
{
    int signe = 1;
    float x = a;
    if (x < 0)
    {
        x = -x;
        signe = -1;
    }
    if (x < 1.97692)
    {
        return (-x*(x - 4.34) / 4.27)*signe;
    }
    else
    {
        cfloat X = x+1000;
        return ((1 - 0.6 / x - 0.1 / (X*X)) *(M_PI / 2))*signe;
    }
}

char GW_NaturalLog(int nb)
{
    int i = 0;
    while (nb != 0)
    {
        i++;
        nb /= 10;
    }
    if (i == 0)
    {
        i++;
    }
    return i;
}

void GW_Copy(const Image* source, Image* cible, CUInt32 X, CUInt32 Y)
{
    UInt32 i = X, j = Y;
    while (i < X+source->GetWidth())
    {
        j = Y;
        while (j < Y+source->GetHeight())
        {
            cible->SetPixel(i, j, source->GetPixel(i-X, j-Y));
            j++;
        }
        i++;
    }
}

bool GW_MassLoadImages(Image** img, CSInt32 nb, CSInt32 d, CUInt32 nbchar, const char* prech, const char* postch)
{
    int i = 0;
    bool j = true;
    char* str = (char*)malloc(sizeof(char)*(nbchar+1));
    if (str == NULL)
    {
        return false;
    }
    while (i < nb && j)
    {
        sprintf(str, "%s%d%s", prech, i+d, postch);
        img[i] = GW_CreateFromFile(str);
        if (img[i] == NULL)
        {
            j = false;
        }
        i++;
    }
    free(str);
    if (!j)
    {
        while (i > 0)
        {
            i--;
            delete(img[i]);
        }
        return false;
    }
    else
    {
        return true;
    }
}

bool GW_MassDuplicate(Image** source, Image** cible, CSInt32 nb)
{
    int i = 0, j = -1;
    while (i < nb && j == -1)
    {
        cible[i] = new Image(*source[i]);
        if (cible[i] == NULL)
        {
            j = i;
        }
        i++;
    }
    if (j > -1)
    {
        i = 0;
        while (i < j)
        {
            delete(cible[i]);
            i++;
        }
        return false;
    }
    else
    {
        return true;
    }
}

#endif
