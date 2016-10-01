#ifndef GW_ARRAYLIST_H
#define GW_ARRAYLIST_H

TEMPLATE(T) class GW_ArrayList
{
    public:
                        GW_ArrayList    (void);
                        ~GW_ArrayList   (void);

                bool    Init            (bool previnit);
                void    Close           (void);

                bool    Add             (T* object);
                T*      Get             (int index);
                T*      Delete          (int index);
        static  void    ToEmpty         (GW_ArrayList<T>* list);
                int     Size            (void);
                int     PhysicalSize    (void) const;
            const T**   GetTab          (void) const;

    private:
        bool Extend(void);

        int nb, size;
        T** tab;
};

TEMPLATE(T) const T** GW_ArrayList<T>::GetTab(void) const
{
    return tab;
}

TEMPLATE(T) int GW_ArrayList<T>::PhysicalSize(void) const
{
    return size;
}

TEMPLATE(T) void GW_ArrayList<T>::ToEmpty(GW_ArrayList<T>* list)
{
    while (list->Size() != 0)
    {
        delete(list->Delete(0));
    }
}

TEMPLATE(T) int GW_ArrayList<T>::Size(void)
{
    return nb;
}

TEMPLATE(T) GW_ArrayList<T>::GW_ArrayList(void)
{
    size = 0;
    nb = 0;
    tab = NULL;
}

TEMPLATE(T) GW_ArrayList<T>::~GW_ArrayList(void)
{
    this->Close();
}

TEMPLATE(T) bool GW_ArrayList<T>::Init(bool previnit)
{
    if (!previnit)
    {
        return false;
    }
    tab = new T*[1];
    if (tab == NULL)
    {
        return false;
    }
    size = 1;
    return true;
}

TEMPLATE(T) bool GW_ArrayList<T>::Extend(void)
{
    T **newtab = (T**)malloc(sizeof(T*)*size*GW_ARRAYMULT);
    if (newtab == NULL)
    {
        return false;
    }
    int i = 0;
    while (i < nb)
    {
        newtab[i] = tab[i];
        i++;
    }
    size *= GW_ARRAYMULT;
    delete(tab);
    tab = newtab;
    return true;
}

TEMPLATE(T) void GW_ArrayList<T>::Close(void)
{
    if (size != 0)
    {
        delete(tab);
        size = 0;
    }
}

TEMPLATE(T) T* GW_ArrayList<T>::Delete(int index)
{
    T* elem = tab[index];
    nb--;
    tab[index] = tab[nb];
    return elem;
}

TEMPLATE(T) T* GW_ArrayList<T>::Get(int index)
{
    return tab[index];
}

TEMPLATE(T) bool GW_ArrayList<T>::Add(T* object)
{
    if (nb == size)
    {
        if (!this->Extend())
        {
            return false;
        }
    }
    tab[nb] = object;
    nb++;
    return true;
}
#endif
