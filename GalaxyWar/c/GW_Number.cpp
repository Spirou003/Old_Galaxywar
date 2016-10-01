#ifndef GW_NUMBER_C
#define GW_NUMBER_C

#include "../h/GW_GraphicsIncluser.hpp"
#include "../h/GW_Number.hpp"

bool GW_Number::exists = false;
Image GW_Number::Numbers[11];

GW_Number::GW_Number(void)
{
    type = NUMBER;
    y = 0;
    x = 0;
    size = 0;
    Time = 0;
    t = 0;
    s = 0;
    l = 0;
    value = 0;
    this->NewSprite();
    if (image == NULL)
    {
        return;
    }
}

GW_Number::GW_Number(cfloat X, cfloat Y, CSInt32 Value, UInt16 tei, UInt8 sat, char lum)
{
    type = NUMBER;
    t = tei;
    s = sat;
    l = lum;
    size = 0;
    Time = 0;
    this->NewSprite();
    if (image == NULL)
    {
        return;
    }
    this->SetValue(Value);
    this->SetX(X);
    this->SetY(Y);
}

void GW_Number::NewSprite(void)
{
    image = new Sprite();
}

GW_Number* GW_Number::RandomCreate(cfloat X, cfloat Y, CSInt32 Value)
{
    return GW_Number::Create
    (X, Y, Value,
     Random(0, 1535),
     Random(0, 255),
     Random(0, 96)-32);
}

GW_Number* GW_Number::Create(cfloat X, cfloat Y, CSInt32 Value, UInt16 tei, UInt8 sat, char lum)
{
    return new GW_Number(X, Y, Value, tei, sat, lum);
}

GW_Number* GW_Number::Create(void)
{
    return GW_Number::Create(0.f, 0.f, 0, 0, 0, 0);
}

float GW_Number::GetSize(CSInt32 Value)
{
    if (Value > 9999)
    {
        return 2/3.;
    }
    else
    {
        return GW_NaturalLog(Value)*0.5/6+0.25;
    }
}

GW_Number::~GW_Number(void)
{
    if (size != 0)
    {
        delete(image->GetImage());
        delete(image);
    }
}

void GW_Number::SetX(cfloat X)
{
    x = X;
    image->SetX(x);
}

void GW_Number::SetY(cfloat Y)
{
    y = Y;
    image->SetY(y);
}

bool GW_Number::SetValue(CSInt32 Value)
{
    value = Value;
    Image* img = GW_Number::IntegerToImage(Value, t, s, l);
    if (img == NULL)
    {
        return false;
    }
    delete(image->GetImage());
    image->SetImage(*img);
    size = GW_Number::GetSize(Value);
    GW_ToCenter(*image);
    return true;
}

int GW_Number::GetValue(void) const
{
    return value;
}

bool GW_Number::Draw(RenderWindow* App, cfloat dt)
{
    Time += dt;
    if (Time > 1.f)
    {
        return true;
    }
    else if (Time > 0.5f)
    {
        image->SetAlpha((1-Time)*510);
    }
    else if (Time > 0.1f)
    {
        image->SetScale(size, size);
    }
    else
    {
        float much = Time*4*size;
        image->SetScale(much, much);
    }
    App->Draw(*image);
    return false;
}

Image* GW_Number::IntegerToImage(int value, UInt16 teinte, UInt8 saturation, char luminosite)
{
    int taille = GW_NaturalLog(value), tf = taille + (taille-1)/3, width = 0, v;
    char* str = (char*)malloc(sizeof(char)*tf);
    if (str == NULL)
    {
        return NULL;
    }
    int i = 0;
    while (i < tf)
    {
        if (i%4 == 3)
        {
            str[tf-1-i] = 10;
            width += Numbers[10].GetWidth();
        }
        else
        {
            v = value%10;
            str[tf-1-i] = v;
            width += Numbers[v].GetWidth();
            value/= 10;
        }
        i++;
    }
    i = 0;
    Image* img = new Image(width, Numbers[0].GetHeight(), Color(255,0,0,255));
    if (img == NULL)
    {
        free(str);
        return NULL;
    }
    width = 0;
    while (i < tf)
    {
        GW_Copy(&Numbers[(int)str[i]], img, width, 0);
        width += Numbers[(int)str[i]].GetWidth();
        i++;
    }
    free(str);
    GW_TSL(img, teinte, saturation, luminosite);
    img->SetSmooth(false);
    return img;
}

bool GW_Number::Init(cbool previnit)
{
    if (exists || !previnit)
    {
        return false;
    }
    char prech[] = "img"SEPARATOR"n";
    char postch[] = ".png";
    int nbchar = 11;
    int i = 0;
    char* str = (char*)malloc(sizeof(char)*(nbchar+1));
    if (str == NULL)
    {
        return false;
    }
    while (i < 10)
    {
        sprintf(str, "%s%d%s", prech, i, postch);
        if (!Numbers[i].LoadFromFile(str))
        {
            free(str);
            return false;
        }
        i++;
    }
    sprintf(str, "%sn%s", prech, postch);
    if (Numbers[10].LoadFromFile(str))
    {
        exists = true;
        free(str);
        return true;
    }
    free(str);
    return false;
}

void GW_Number::Close(void)
{
    exists = false;
}

#endif
