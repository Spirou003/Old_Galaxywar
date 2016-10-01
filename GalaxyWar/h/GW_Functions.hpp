#ifndef GW_FUNCTIONS_H
#define GW_FUNCTIONS_H

#include "Typedefs.hpp"
#include "GW_GraphicsDeclarer.hpp"

//#define GW_ToCenter(PARAM) PARAM.SetCenter(PARAM.GetSize().x/2.f,PARAM.GetSize().y/2.f);
#define GW_ToCenter(PARAM) GW_To_Center(&PARAM);

void    GW_To_Center        (Sprite* sprite);
void    GW_AddOctogon       (Shape* polygon, const Color &in, const Color &out);
float   GW_Angle            (cfloat x, cfloat cx, cfloat y, cfloat cy);
Image*  GW_CreateFromFile   (const char* str);
float   GW_Sin              (cfloat a);
float   GW_Cos              (cfloat a);
float   GW_Atan             (cfloat a);
char    GW_NaturalLog       (int nb);
void GW_Copy(const Image* source, Image* cible, CUInt32 X, CUInt32 Y);
int Random(CSInt32 a, CSInt32 b);
float Random(cfloat a, cfloat b);
float GW_RandomEcart(cfloat v, cfloat precis);
int GW_Poly2nd(CSInt32 n);
float GW_FloatModulo(cfloat n, cfloat module);
void GW_SetNoSmooth(Image* img, Sprite* ptr);
bool GW_MassLoadImages(Image** img, CSInt32 nb, CSInt32 d, CUInt32 nbchar, const char* prech, const char* postch);
bool GW_MassDuplicate(Image** source, Image** cible, CSInt32 nb);
Color RandomColor(void);

#endif
