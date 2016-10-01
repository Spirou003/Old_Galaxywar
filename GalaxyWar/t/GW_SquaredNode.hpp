#ifndef GW_SQUAREDNODE_H
#define GW_SQUAREDNODE_H

TEMPLATE(T) class GW_SquaredNode
{
    public:
        GW_SquaredNode(void);
        GW_SquaredNode(GW_SquaredNode* obj, const int dir);
        GW_SquaredNode(GW_SquaredNode* obj[4]);
        GW_SquaredNode* GetNext(const int dir) const;
        void SetNext(GW_SquaredNode* obj, const int dir);
        void SetNext(GW_SquaredNode* obj[4]);
        T* GetValue(void) const;
        void SetValue(T* obj);

        enum GWSN_Dir
        {
            Up, Down, Left, Right
        };

    private:
        T* Object;
        GW_SquaredNode* next[4];
};

TEMPLATE(T) GW_SquaredNode<T>::GW_SquaredNode(void)
{
    int i = 0;
    while (i < 4)
    {
        next[i] = NULL;
        i++;
    }
}

TEMPLATE(T) GW_SquaredNode<T>::GW_SquaredNode(GW_SquaredNode* obj, const int dir)
{
    int i = 0;
    while (i < 4)
    {
        next[i] = NULL;
        i++;
    }
    next[dir] = obj;
}

TEMPLATE(T) GW_SquaredNode<T>::GW_SquaredNode(GW_SquaredNode* obj[4])
{
    int i = 0;
    while (i < 4)
    {
        next[i] = obj[i];
        i++;
    }
}

TEMPLATE(T) void GW_SquaredNode<T>::SetNext(GW_SquaredNode* obj, const int dir)
{
    switch (dir)
    {
        case Up:
            obj->next[Down] = this;
            break;
        case Down:
            obj->next[Up] = this;
            break;
        case Left:
            obj->next[Right] = this;
            break;
        case Right:
            obj->next[Left] = this;
            break;
        default:
            return;
            break;
    }
    next[dir] = obj;
}

TEMPLATE(T) void GW_SquaredNode<T>::SetNext(GW_SquaredNode* obj[4])
{
    int i = 0;
    while (i < 4)
    {
        this->SetNext(obj[i], i);
        i++;
    }
}

TEMPLATE(T) GW_SquaredNode<T>* GW_SquaredNode<T>::GetNext(const int id) const
{
    return next[id];
}

TEMPLATE(T) T* GW_SquaredNode<T>::GetValue(void) const
{
    return Object;
}

TEMPLATE(T) void GW_SquaredNode<T>::SetValue(T* obj)
{
    Object = obj;
}
#endif
