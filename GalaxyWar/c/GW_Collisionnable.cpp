#ifndef GW_COLLISIONNABLE_C
#define GW_COLLISIONNABLE_C

#include <SFML/Graphics/Shape.hpp>
#include "../h/GW_Collisionnable.hpp"
#include "../h/GW_JeuData.hpp"

GW_Collisionnable::GW_Collisionnable(void){scaleX = 0;scaleY = 0;isdelete = false;}
GW_Collisionnable::~GW_Collisionnable(void){}
float   GW_Collisionnable::GetX    (void) const{return x;}
float   GW_Collisionnable::GetY    (void) const{return y;}
float   GW_Collisionnable::GetAngle(void) const{return angle;}
int     GW_Collisionnable::Type    (GW_Collisionnable* obj){return obj->type;}

bool GW_Collisionnable::IsDeletable(void)
{
    if (isdelete)
    {
        return true;
    }
    else
    {
        if (this->IsOut() || this->IsDead())
        {
            isdelete = true;
        }
        return false;
    }
}

bool GW_Collisionnable::IsOut(void) const
{
    return ((y + dmax < 0) || (y - dmax > GW_HAUTEUR) || (x + dmax < 0) || (x - dmax > GW_HAUTEUR));
}

bool GW_Collisionnable::IsCollisionnable(void) const
{
    return true;
}

void GW_Collisionnable::EffetCollision(GW_Collisionnable* obj1, GW_Collisionnable* obj2)
{
    //float d1 = obj1->Prepare(obj2), d2 = obj2->Prepare(obj1);
    //obj1->Effet(obj2, d2, d1);
    //obj2->Effet(obj1, d1, d2);
}

bool GW_Collisionnable::Collision(const GW_Collisionnable* obj1, const GW_Collisionnable* obj2)
{
    if (!obj1->IsCollisionnable() || !obj2->IsCollisionnable())
    {
        return false;
    }
    float dx = obj1->x - obj2->x, dy = obj1->y - obj2->y, r = obj1->dmax + obj2->dmax;
    if (dx*dx + dy*dy > r*r)
    {
        return false;
    }
    Shape sh1(*obj1->GetPolygon());
    Shape sh2(*obj2->GetPolygon());
    sh1.SetPosition(obj1->x, obj1->y);
    sh1.SetRotation(-obj1->angle*180/M_PI);
    sh1.SetScale(obj1->scaleX, obj1->scaleY);
    sh2.SetPosition(obj2->x, obj2->y);
    sh2.SetRotation(-obj2->angle*180/M_PI);
    sh2.SetScale(obj2->scaleX, obj2->scaleY);
    int i = 0, nb1 = sh1.GetNbPoints(), nb2 = sh2.GetNbPoints();
    if (nb1 < 3 || nb2 < 3)
    {
        return false;
    }
    while (i < nb1)
    {
        sh1.SetPointPosition(i, sh1.TransformToGlobal(sh1.GetPointPosition(i)));
        i++;
    }
    i = 0;
    while (i < nb2)
    {
        sh2.SetPointPosition(i, sh2.TransformToGlobal(sh2.GetPointPosition(i)));
        i++;
    }
    i = 0;
    Vector2<float> p1, p2;
    float min1, max1, min2, max2, a, b;
    bool istrue = true;
    while (i < nb1 && istrue)
    {
        p1 = sh1.GetPointPosition(i);
        p2 = sh1.GetPointPosition((i+1)%nb1);
        //printf("%d %d\n", int(p1.x), int(p1.y));
        a = (p1.x - p2.x);
        b = (p2.y - p1.y);
        GW_Collisionnable::PolygonProjectionToDroiteCentered(&sh1, nb1, a, b, &min1, &max1, obj1);
        GW_Collisionnable::PolygonProjectionToDroiteCentered(&sh2, nb2, a, b, &min2, &max2, obj2);
        i++;
        istrue = ((min1 < max2 && min2 < max1));
    }
    i = 0;
    //printf("\n");
    while (i < nb2 && istrue)
    {
        p1 = sh2.GetPointPosition(i);
        p2 = sh2.GetPointPosition((i+1)%nb2);
        //printf("%d %d\n", int(p1.x), int(p1.y));
        a = (p1.x - p2.x);
        b = (p2.y - p1.y);
        GW_Collisionnable::PolygonProjectionToDroiteCentered(&sh1, nb1, a, b, &min1, &max1, obj1);
        GW_Collisionnable::PolygonProjectionToDroiteCentered(&sh2, nb2, a, b, &min2, &max2, obj2);
        i++;
        istrue = ((min1 < max2 && min2 < max1));
    }
    //printf("-----\n");
    return istrue;
}

void GW_Collisionnable::PolygonProjectionToDroiteCentered(const Shape* polygon, CSInt32 nb, cfloat a, cfloat b, float* min, float* max, const GW_Collisionnable* obj)
{
    int i = 1;
    Vector2<float> p = polygon->GetPointPosition(0);
    *min = b * (p.x) - a * (p.y);
    *max = *min;
    float c;
    while (i < nb)
    {
        p = polygon->GetPointPosition(i);
        c = b * (p.x) - a * (p.y);
        if (c < *min)
        {
            *min = c;
        }
        else if (c > *max)
        {
            *max = c;
        }
        i++;
    }
}

#endif
