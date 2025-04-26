#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED
#include <vector>

using namespace std;

const size_t MaxSize = 100;

// Родительский класс "Итератор"

template<typename T>
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual T GetCurrent() const = 0;
};

// Класс с виртуальной функцией GetIterator

template<typename T>
class ContainerClass
{
public:
    virtual class Iterator<T> *GetIterator() = 0;
};

// Итератор для обхода массива

template<typename T>
class ArrayIterator : public Iterator<T>
{
private:
    const T *ArrayContainer;
    size_t Pos;
    size_t Size;

public:
    ArrayIterator(T *container, size_t _size)
    : ArrayContainer(container), Pos(0), Size(_size) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= Size); }
    T GetCurrent() const override { return ArrayContainer[Pos]; }
};

// Шаблонный класс, содержащий динамический массив

template <typename T>
class ArrayClass : public ContainerClass<T>
{
private:
    T *Items;
    size_t ArraySize;

public:
    void Add(T newObject) { Items[ArraySize++] = newObject; }
    size_t Size() const { return ArraySize; }

    T operator[](size_t index) const { return Items[index]; }
    T GetElement(size_t index) const { return Items[index]; }

    ArrayClass() : ArraySize(0) { Items = new T[MaxSize]; }
    virtual ~ArrayClass() { delete Items; }

    class Iterator<T> *GetIterator()
    {
        return new ArrayIterator<T>(Items, ArraySize);
    };
};

// Итератор для обхода вектора

template<typename T>
class VectorIterator : public Iterator<T>
{
private:
    const vector<T> *VectorContainer;
    size_t Pos;
    size_t Size;

public:
    VectorIterator(const vector<T> *container, size_t _size)
    : VectorContainer(container), Pos(0), Size(_size) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= Size); }
    T GetCurrent() const override { return (*VectorContainer)[Pos]; }
};

// Шаблонный класс, содержаший вектор

template <typename T>
class VectorClass : public ContainerClass<T>
{
private:
    vector<T> Items;

public:
    bool Empty() const { return Items.empty(); }
    void Push(T newObject) { Items.push_back(newObject); }
    size_t Size() const { return Items.size(); }

    T operator[](size_t index) const { return Items[index]; }
    T GetVectorElement(size_t index) const { return Items[index]; }

    VectorClass() {};

    class Iterator<T> *GetIterator()
    {
        size_t _size = Items.size();
        return new VectorIterator<T>(&Items, _size);
    };
};

// Декоратор для итератора (пустой)

template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *It;

public:
    IteratorDecorator(Iterator<T> *it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual T GetCurrent() const { return It->GetCurrent(); }
};

// Адаптер для итератора

template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    ContainerType *Container;
    typename ContainerType::const_iterator It;

public:
    ConstIteratorAdapter(ContainerType *container)
    : Container(container)
    {
        It = Container->begin();
    }

    virtual ~ConstIteratorAdapter() {}
    virtual void First() { It = Container->begin(); }
    virtual void Next() { It++; }
    virtual bool IsDone() const { return (It == Container->end()); }
    virtual ItemType GetCurrent() const { return *It; }
};

#endif // CONTAINERS_H_INCLUDED
