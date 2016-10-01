#ifndef GW_TSL_C
#define GW_TSL_C

#include "../h/GW_TSL.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
using namespace sf;

void GW_Teinte(Image* img, UInt16 effet)
{
    if (effet%1536 == 0)
    {
        return;
    }
    UInt32 i = 0, j = 0, x = img->GetWidth(), y = img->GetHeight(), rr = 0, gg = 0, bb = 0;
    short min = 0, max = 0, rgba[4] = {0};
    double n;
    UInt8 c,d, c1, c2;
    Color pix;
    effet = effet % 1536;
    if (effet < 512)
    {
        rr = 0;gg = 1;bb = 2;
    }
    else if (effet < 1024)
    {
        rr = 1;gg = 2;bb = 0;
    }
    else
    {
        rr = 2;gg = 0;bb = 1;
    }
    effet %= 512;
    CUInt32 R = rr, G = gg, B = bb;
    if (effet < 256)
    {
        while (i < x)
        {
            j = 0;
            while (j < y)
            {
                pix = img->GetPixel(i, j);
                rgba[R] = pix.r;
                rgba[G] = pix.g;
                rgba[B] = pix.b;
                rgba[3] = pix.a;
                if (!(rgba[0] == rgba[1] && rgba[1] == rgba[2]))
                {
                    min = rgba[0];
                    max = rgba[1];
                    c = 0;
                    d = 1;
                    if (rgba[1] < min)
                    {
                        max = rgba[0];
                        min = rgba[1];
                        d = 0;
                        c = 1;
                    }
                    if (rgba[2] < min)
                    {
                        min = rgba[2];
                        c = 2;
                    }
                    else if (rgba[2] > max)
                    {
                        max = rgba[2];
                        d = 2;
                    }
                    c1 = (c+1)%3;
                    c2 = (c+2)%3;
                    if (c1 == d)
                    {
                        n = rgba[c2] + effet*(double)(max-min)/255;
                        if (n > max)
                        {
                            rgba[d] = 2*max - n;
                            rgba[c2] = max;
                        }
                        else
                        {
                            rgba[c2] = n;
                        }
                    }
                    else
                    {
                        n = rgba[c1] - effet*(double)(max-min)/255;
                        if (n < min)
                        {
                            rgba[c] = 2*min - n;
                            rgba[c1] = min;
                        }
                        else
                        {
                            rgba[c1] = n;
                        }
                    }
                    img->SetPixel(i, j, Color(rgba[0],rgba[1],rgba[2],rgba[3]));
                }
                j++;
            }
            i++;
        }
    }
    else if (effet < 512)
    {
        effet = effet % 256;
        while (i < x)
        {
            j = 0;
            while (j < y)
            {
                pix = img->GetPixel(i, j);
                rgba[R] = pix.r;
                rgba[G] = pix.g;
                rgba[B] = pix.b;
                rgba[3] = pix.a;
                if (!(rgba[0] == rgba[1] && rgba[1] == rgba[2]))
                {
                    min = rgba[0];
                    max = rgba[1];
                    c = 0;
                    d = 1;
                    if (rgba[1] < min)
                    {
                        max = rgba[0];
                        min = rgba[1];
                        d = 0;
                        c = 1;
                    }
                    if (rgba[2] < min)
                    {
                        min = rgba[2];
                        c = 2;
                    }
                    else if (rgba[2] > max)
                    {
                        max = rgba[2];
                        d = 2;
                    }
                    c1 = (c+1)%3;
                    c2 = (c+2)%3;
                    if (c1 == d)
                    {
                        rgba[d] = min+max - rgba[(c+2)%3];
                        rgba[c2] = max;
                        //d = (d+1)%3;
                        n = rgba[c1] - effet*(double)(max-min)/255;
                        if (n < min)
                        {
                            rgba[c] = 2*min - n;
                            rgba[c1] = min;
                        }
                        else
                        {
                            rgba[c1] = n;
                        }
                    }
                    else
                    {
                        rgba[c] = max+min - rgba[(c+1)%3];
                        rgba[c1] = min;
                        c2 = c;
                        c = c1;
                        n = rgba[c2] + effet*(double)(max-min)/255;
                        if (n > max)
                        {
                            rgba[d] = 2*max - n;
                            rgba[c2] = max;
                        }
                        else
                        {
                            rgba[c2] = n;
                        }
                    }
                    img->SetPixel(i, j, Color(rgba[0],rgba[1],rgba[2],rgba[3]));
                }
                j++;
            }
            i++;
        }
    }
}

void GW_Saturation(Image* img, UInt8 effet)
{
    if (effet == 0)
    {
        return;
    }
    UInt32 i = 0, j = 0, x = img->GetWidth(), y = img->GetHeight();
    SInt16 rgba[4] = {0};
    double moy = 0, mod = effet/256.f, mod1 = 1-mod;
    Color pix;
    while (i < x)
    {
        j = 0;
        while (j < y)
        {
            pix = img->GetPixel(i, j);
            rgba[0] = pix.r;
            rgba[1] = pix.g;
            rgba[2] = pix.b;
            rgba[3] = pix.a;
            if (!(rgba[0] == rgba[1] && rgba[1] == rgba[2]))
            {
                moy = mod*((rgba[0]+rgba[1]+rgba[2])/3);
                pix.r = rgba[0]*mod1 + moy;
                pix.g = rgba[1]*mod1 + moy;
                pix.b = rgba[2]*mod1 + moy;
                img->SetPixel(i, j, pix);
            }
            j++;
        }
        i++;
    }
}

void GW_Luminosite(Image* img, char effet)
{
    if (effet == 0)
    {
        return;
    }
    UInt32 i = 0, j = 0, x = img->GetWidth(), y = img->GetHeight();
    SInt16 c = 255;
    double mod = effet/128.f, mod1;
    Color pix;
    if (effet < 0)
    {
        mod = -mod;
        c = 0;
    }
    mod1 = 1-mod;
    mod *= c;
    while (i < x)
    {
        j = 0;
        while (j < y)
        {
            pix = img->GetPixel(i, j);
            img->SetPixel(i, j, Color(pix.r*mod1 + mod, pix.g*mod1 + mod, pix.b*mod1 + mod, pix.a));
            j++;
        }
        i++;
    }
}

void GW_TSL(sf::Image* img, UInt16 teinte, UInt8 saturation, char luminosite)
{
    GW_Luminosite(img, luminosite);
    if (luminosite == 127 || luminosite == -128)
    {
        return;
    }
    GW_Saturation(img, saturation);
    if (saturation != 0)
    {
        GW_Teinte(img, teinte);
    }
}

#endif
