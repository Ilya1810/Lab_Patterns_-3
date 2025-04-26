#include <iostream>
#include <cstdint>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Containers.h"


using namespace std;

// Родительский класс
class Firearms
{
private:
    bool FirearmsIsOK;

public:
    Firearms();
    virtual void Shoot() = 0;
    virtual void Reload() = 0;
    virtual void Clean() = 0;
    virtual ~Firearms();

protected:
    double Calibre; // Калибр в миллиметрах
    int8_t Ammunition;
    int16_t Weight; // Масса в граммах

};

Firearms::Firearms() : Calibre(1.0), Ammunition(1), Weight(1), FirearmsIsOK(true)
{

}

Firearms::~Firearms()
{
    wcout << L"Удаляется образец оружия..." << endl;
}

// Наследники

class Colt_M1911 : public Firearms
{
public:
    Colt_M1911();
    ~Colt_M1911();

    void Shoot();
    void Reload();
    void Clean();
};

Colt_M1911::Colt_M1911()
{
    Calibre = 11.43;
    Ammunition = 7;
    Weight = 1120;
    wcout << L"Создаётся образец Кольта М1911..."  << endl;
}

Colt_M1911::~Colt_M1911()
{
    wcout << L"Удаляется образец Кольта М1911..."  << endl;
}

void Colt_M1911::Shoot()
{
    wcout << L"Выстрел из Кольта М1911" << endl;
}
void Colt_M1911::Reload()
{
    wcout << L"Перезарядка Кольта М1911" << endl;
}
void Colt_M1911::Clean()
{
    wcout << L"Чистка Кольта М1911" << endl;
}

//////////////////////////////////////////////////////////

class RPK : public Firearms
{
public:
    RPK();
    ~RPK();

    void Shoot();
    void Reload();
    void Clean();
};

RPK::RPK()
{
    Calibre = 7.62;
    Ammunition = 75;
    Weight = 7100;
    wcout << L"Создаётся образец РПК..."  << endl;
}

RPK::~RPK()
{
    wcout << L"Удаляется образец РПК..."  << endl;
}

void RPK::Shoot()
{
    wcout << L"Выстрел из РПК" << endl;
}
void RPK::Reload()
{
    wcout << L"Перезарядка РПК" << endl;
}
void RPK::Clean()
{
    wcout << L"Чистка РПК" << endl;
}

////////////////////////////////////////////////////////////////////

class VSS_Vintorez : public Firearms
{
public:
    VSS_Vintorez();
    ~VSS_Vintorez();

    void Shoot();
    void Reload();
    void Clean();
};

VSS_Vintorez::VSS_Vintorez()
{
    Calibre = 9.00;
    Ammunition = 10;
    Weight = 3700;
    wcout << L"Создаётся образец ВСС Винторез..."  << endl;
}

VSS_Vintorez::~VSS_Vintorez()
{
    wcout << L"Удаляется образец ВСС Винторез..."  << endl;
}

void VSS_Vintorez::Shoot()
{
    wcout << L"Выстрел из ВСС Винторез" << endl;
}
void VSS_Vintorez::Reload()
{
    wcout << L"Перезарядка ВСС Винторез" << endl;
}
void VSS_Vintorez::Clean()
{
    wcout << L"Чистка ВСС Винторез" << endl;
}

//Реализация паттерна "Фабричный метод"

enum class FirearmsType : int
{
    Colt_M1911 = 1,
    RPK = 2,
    VSS_Vintorez = 3,
    Undefined = 0
};

Firearms *CreateFirearms(FirearmsType type)
{
    Firearms *newFirearms = nullptr;

    if (type == FirearmsType::Colt_M1911)
    {
        newFirearms = new Colt_M1911;
    }
    else if (type == FirearmsType::RPK)
    {
        newFirearms = new RPK;
    }
    else if (type == FirearmsType::VSS_Vintorez)
    {
        newFirearms = new VSS_Vintorez;
    }

    return newFirearms;
}

// Реализации трёх декораторов

class FirearmsNumberDecorator : public IteratorDecorator<Firearms*>
{
private:
    size_t Number;

public:
    FirearmsNumberDecorator(Iterator<Firearms*> *it)
    : IteratorDecorator<Firearms*>(it), Number(1) {}

    void First()
    {
        It->First();
        wcout << L"Образец оружия номер 1:" << endl;
    }

    void Next()
    {
        It->Next();
        if (!It->IsDone())
        {
            Number += 1;
            wcout << L"Образец оружия номер " << Number << ":" << endl;
        }
    }
};

class FirearmsCleaningDecorator : public IteratorDecorator<Firearms*>
{
public:
    FirearmsCleaningDecorator(Iterator<Firearms*> *it)
    : IteratorDecorator<Firearms*>(it) {}

    void Next()
    {
        It->GetCurrent()->Clean();
        It->Next();
        wcout << endl; // Исключительно для красоты вывода!
    }
};

class FirearmsReloadingDecorator : public IteratorDecorator<Firearms*>
{
public:
    FirearmsReloadingDecorator(Iterator<Firearms*> *it)
    : IteratorDecorator<Firearms*>(it) {}

    void Next()
    {
        It->GetCurrent()->Reload();

        It->Next();
    }
};

// Функция, осуществляющая стрельбу из всего оружия в контейнере

void Salute(Iterator<Firearms*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Firearms *pFirearms = it->GetCurrent();
        pFirearms->Shoot();
    }
}

// Основной код
int main()
{

    setlocale (LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));

    // Создание массива и заполнение его случайными образцами оружия

    wcout << L"Создание и заполнение массива образцов оружия: " << endl << endl;
    ArrayClass<Firearms*> firearms_array;
    for (size_t i=0; i<5; i++)
    {
        int firearms_type_number = rand()%3+1;
        FirearmsType firearms_type = static_cast<FirearmsType>(firearms_type_number);
        Firearms *newFirearms = CreateFirearms(firearms_type);
        firearms_array.Add(newFirearms);
    }

    // Создание вектора и заполнение его случайными образцами оружия

    wcout << endl << L"Создание и заполнение вектора образцов оружия: " << endl << endl;
    VectorClass<Firearms*> firearms_vector;
    for (size_t i=0; i<5; i++)
    {
        int firearms_type_number = rand()%3+1;
        FirearmsType firearms_type = static_cast<FirearmsType>(firearms_type_number);
        Firearms *newFirearms = CreateFirearms(firearms_type);
        firearms_vector.Push(newFirearms);
    }

    // Создание списка и заполнение его случайными образцами оружия

    wcout << endl << L"Создание и заполнение списка образцов оружия: " << endl << endl;
    list<Firearms*> firearms_list;
    for (size_t i=0; i<5; i++)
    {
        int firearms_type_number = rand()%3+1;
        FirearmsType firearms_type = static_cast<FirearmsType>(firearms_type_number);
        Firearms *newFirearms = CreateFirearms(firearms_type);
        firearms_list.push_back(newFirearms);
    }

    // Демонстрация работы декораторов

    wcout << endl << L"Действие декораторов на массив образцов оружия: " << endl << endl;
    Iterator<Firearms*> *allDecoratorsIt = new FirearmsNumberDecorator(new FirearmsCleaningDecorator(new FirearmsReloadingDecorator(firearms_array.GetIterator())));
    Salute(allDecoratorsIt);
    delete allDecoratorsIt;

    wcout << endl << L"Действие декораторов на вектор образцов оружия: " << endl << endl;
    Iterator<Firearms*> *allDecoratorsIt1 = new FirearmsNumberDecorator(new FirearmsCleaningDecorator(new FirearmsReloadingDecorator(firearms_vector.GetIterator())));
    Salute(allDecoratorsIt1);
    delete allDecoratorsIt1;

    // Демонстрация работы адаптера

    wcout << endl << L"Работа со списком образцов оружия при помощи адаптера: " << endl << endl;
    Iterator<Firearms*> *adaptedIt = new ConstIteratorAdapter<list<Firearms*>, Firearms*>(&firearms_list);
    Iterator<Firearms*> *adaptedCleaninigIt = new FirearmsCleaningDecorator(adaptedIt);
    Salute(adaptedCleaninigIt);
    delete adaptedCleaninigIt;

    return 0;
}
