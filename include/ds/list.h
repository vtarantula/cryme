#ifndef LIST_H__
#define LIST_H__

// C++ headers
#include <memory>
#include <iostream>

template <typename T>
class ListIterator;

template <class T>
class List
{
private:
    /* data */
    struct node
    {
        T val;
        std::shared_ptr<node> next;
        node() : val(0), next(nullptr)
        {
        }

        node(const int& i) : val(i), next(nullptr)
        {
        }

        node(const int& i, node* n) : val(i), next(n)
        {
        }
    };

    size_t size;
    std::shared_ptr<node> head;
    std::shared_ptr<node> tail;

public:
    List();
    ~List();
    size_t Size() const;
    void Insert(const T&);
    void Delete(const T&);

    friend class ListIterator<T>;
};

template <typename T>
class ListIterator
{
    std::shared_ptr<typename List<T>::node> currptr;
public:
    ListIterator();
    ~ListIterator();
    ListIterator(const List<T>&);
    bool HasNext();
    T& Next();
};

template <class T>
List<T>::List() : size(0)
{
    head = std::shared_ptr<node>(new node);
    tail = head;
}

template <class T>
List<T>::~List()
{
}

template <class T>
void List<T>::Insert(const T& i)
{
    auto newNode = std::shared_ptr<node>(new node{i});
    tail->next = newNode;
    tail = newNode;
    ++size;
    // printf("%p %p\n", head.get(), tail.get());
}

template <class T>
size_t List<T>::Size() const
{
    return size;
}

template <class T>
void List<T>::Delete(const T& i)
{
    if (size == 0)
    {
        throw std::runtime_error("Delete on empty list");
    }
    auto runner = &head;
    while (*runner)
    {
        if ((*runner)->val == i)
        {
            *runner = (*runner)->next;
            --size;
        }
        else
        {
            runner = &((*runner)->next);
        }
    }
    // printf("%p %p => %d %d\n", head.get(), tail.get(), head->val, tail->val);
    // printf("=> %d\n", size);
}

template <class T>
ListIterator<T>::ListIterator()
{
}

template <class T>
ListIterator<T>::ListIterator(const List<T>& l)
{
    currptr = l.head;
}

template <class T>
ListIterator<T>::~ListIterator()
{
}

template <class T>
bool ListIterator<T>::HasNext()
{
    return currptr->next != nullptr;
}

template <class T>
T& ListIterator<T>::Next()
{
    currptr = currptr->next;
    return currptr->val;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l)
{
    os << "[ ";

    ListIterator<T> iter(l);
    while (iter.HasNext())
    {
        os << iter.Next() << " ";
    }

    os << "]";
    return os;
}

#endif  // LIST_H__
