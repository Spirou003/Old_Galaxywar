#ifndef GW_LINKEDLIST_H
#define GW_LINKEDLIST_H

template <typename T>
class GW_LinkedList
{
    public:
        GW_LinkedList(void);
        ~GW_LinkedList(void);
        int GetCursor(void) const;
        void SetCursor(const int i);
        int Size(void) const;
        bool Add(T* obj);
        T* GetValue(const int i);
        void SetValue(T* obj, const int i);
        bool IsVisit(const int i);
        void Visit(const int i);
        void GetNode(GW_LinkedList<T>* list, const int i);
        void GetNodeFromCursor(GW_LinkedList<T>* list);

    protected:
        class GW_Node
        {
            public:
                GW_Node(void);
                GW_Node(GW_Node* next);
                GW_Node(T* object, GW_Node* next);
                GW_Node(GW_Node* next, T* object);
                GW_Node(T* object);
                ~GW_Node(void);
                bool IsVisit(void) const;
                void Visit(void);
                T* GetValue(void) const;
                void SetValue(T* object);
                GW_Node* GetNext(void) const;
                void SetNext(GW_Node* next);

            private:
                GW_Node* Next;
                bool isVisited;
                T* Object;
        };

    private:
        GW_Node* head;
        GW_Node* curs;
        int size, pos;
};

template <typename T>
GW_LinkedList<T>::GW_Node::GW_Node(void)
{
    Next = NULL;
    Object = NULL;
    isVisited = false;
}

template <typename T>
GW_LinkedList<T>::GW_Node::GW_Node(GW_Node* next)
{
    this->SetNext(next);
    Object = NULL;
    isVisited = false;
}

template <typename T>
GW_LinkedList<T>::GW_Node::GW_Node(GW_Node* next, T* object)
{
    this->SetNext(next);
    this->SetValue(object);
    isVisited = false;
}

template <typename T>
GW_LinkedList<T>::GW_Node::GW_Node(T* object)
{
    Next = NULL;
    this->SetValue(object);
    isVisited = false;
}

template <typename T>
GW_LinkedList<T>::GW_Node::GW_Node(T* object, GW_Node* next)
{
    this->SetNext(next);
    this->SetValue(object);
    isVisited = false;
}

template <typename T>
typename GW_LinkedList<T>::GW_Node* GW_LinkedList<T>::GW_Node::GetNext(void) const
{
    return Next;
}

template <typename T>
void GW_LinkedList<T>::GW_Node::SetNext(GW_Node* next)
{
    Next = next;
}

template <typename T>
GW_LinkedList<T>::GW_Node::~GW_Node(void)
{
    ;
}

template <typename T>
bool GW_LinkedList<T>::GW_Node::IsVisit(void) const
{
    return isVisited;
}

template <typename T>
void GW_LinkedList<T>::GW_Node::Visit(void)
{
    isVisited = !isVisited;
}

template <typename T>
T* GW_LinkedList<T>::GW_Node::GetValue(void) const
{
    return Object;
}

template <typename T>
void GW_LinkedList<T>::GW_Node::SetValue(T* object)
{
    Object = object;
}

//------------------------------------------------------------------------------

template <typename T>
GW_LinkedList<T>::GW_LinkedList(void)
{
    size = 0;
    pos = 0;
    curs = NULL;
    head = NULL;
}

template <typename T>
GW_LinkedList<T>::~GW_LinkedList(void)
{
    GW_Node* node;
    while (size > 0)
    {
        node = head;
        head = node->GetNext();
        delete(node);
        size--;
    }
}

template <typename T>
int GW_LinkedList<T>::GetCursor(void) const
{
    return pos;
}

template <typename T>
void GW_LinkedList<T>::SetCursor(const int i)
{
    if (pos > i)
    {
        pos = 0;
        curs = head;
    }
    while (pos < i)
    {
        pos++;
        curs = curs->GetNext();
    }
}

template <typename T>
int GW_LinkedList<T>::Size(void) const
{
    return size;
}

template <typename T>
bool GW_LinkedList<T>::Add(T* obj)
{
    GW_Node* node = new GW_Node(obj, head);
    if (node == NULL)
    {
        return false;
    }
    head = node;
    size++;
    pos++;
    return true;
}

template <typename T>
T* GW_LinkedList<T>::GetValue(const int i)
{
    this->SetCursor(i);
    return curs->GetValue();
}

template <typename T>
void GW_LinkedList<T>::SetValue(T* obj, const int i)
{
    this->SetCursor(i);
    curs->SetValue(obj);
}

template <typename T>
bool GW_LinkedList<T>::IsVisit(const int i)
{
    this->SetCursor(i);
    return curs->IsVisit();
}

template <typename T>
void GW_LinkedList<T>::Visit(const int i)
{
    this->SetCursor(i);
    curs->Visit();
}

template <typename T>
void GW_LinkedList<T>::GetNode(GW_LinkedList<T>* list, const int i)
{
    list->SetCursor(i-1);
    GW_Node* node;
    if (i == 0 || list->size == 1)
    {
        node = list->head;
        list->curs = node->GetNext();
        list->head = node->GetNext();
        list->pos = 0;
    }
    else
    {
        node = list->curs->GetNext();
        list->curs->SetNext(node->GetNext());
    }
    node->SetNext(head);
    head = node;
    list->size--;
    size++;
    pos++;
}
#endif
