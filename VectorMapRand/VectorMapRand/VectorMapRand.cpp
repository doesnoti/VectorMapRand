/*
Личный комментарий
*-"нет C++11 и выше" - в первоначальной версии использовались: шаблонная функция, цикл foreach и ключевое слово auto,
*что, как я понял, относится к C++11. Если имелось ввиду именно использование rand() - поправил этот момент.
*
*-"создаются лишние элементы в map" - не до конца понятный мне комментарий. Как я понял, мне необходимо было
*заполнять случайными числами ключи контейнера map. Изначально меня смутило "ограничение удаляемых элементов - не более 15".
*Ведь если их больше или равно 9, то map уже останется пустым. Если требовалось, всё таки, заполнять значения,
*то мне не понятен комментарий про лишние элементы map. Я попытался уточнить этот вопрос, но не получил ответа.
*
*-Был комментарий про линейную сложность и использование алгоритмов STL. Если мы заполняем значения map и подразумевалось
*использование функции find/find_if, то задача и так будет иметь квадратичную сложность, только придётся с её помощью
*прогонять два контейнера. А сортировку для vector не использовал, потому что в этом не было необходимости (значения
map шли вразнобой).
*
*В общем, много моментов, которые мне не до конца ясны, и если бы была возможность их уточнить - всё сделал бы, как необходимо.
*Сама по себе формулировка задания может иметь несколько интерпритаций. Надеюсь отклонение моей реализации от того,что
*было вами задумано, не будет показателем моих навыков.
*/

/*
*1.Случайными числами от 1 до 9 заполняются значения контейнеров vector[i] и map[i];
*2.Удалиются случайное число элементов (не более 15) в каждом контейнере;
*3.Проводится синхронизация, чтобы в vector и map остались только имеющиеся в обоих контейнерах элементы.
*/

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>

using namespace std;

/*Функции печатают содержимое контейнеров*/

template <typename T>
void PrintVector(vector<T> &contVect)
{
    cout << "Vector: ";

    for (const auto& element : contVect)
    {
        cout << element << " ";
    }

    cout << endl;
}

template <typename T>
void PrintMap(map<T, T> &contMap)
{
    cout << "Map: ";

    for (const auto& element : contMap)
    {
        cout << element.first << " ";
    }

    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "ru");

    int i;

    cout << "Введи кол-во элементов (больше 15): ";
    cin >> i;

    if (i <= 15)
    {
        cout << "Ошибка: число меньше или равно 15" << endl;
        return 0;
    }

    map <int, int> randMap;
    vector <int> randVector;
    randVector.reserve(i);

    mt19937_64 rand{ random_device{}() };
    uniform_int_distribution<int> range(1, 9);

    for (int j = 0; j < i; j++)
    {
        randMap.emplace(range(rand), i);
        randVector.push_back(range(rand));
    }

    PrintMap(randMap);
    PrintVector(randVector);

    uniform_int_distribution<int> rangeDel(0, 15);

    int numItemToDel = rangeDel(rand);

    cout << endl << "Кол-во удаляемых элементов: " << numItemToDel << endl;

    if (numItemToDel >= randMap.size())       //Если кол-во удаляемых элементов больше или равно размеру map
    {
        for (int j = 0; j < numItemToDel; j++)
        {
            randVector.pop_back();
        }

        randMap.clear();

        cout << endl << "После удаления:" << endl;

        PrintMap(randMap);
        PrintVector(randVector);

        randVector.clear();

        cout << endl << "После синхронизации:" << endl;

        PrintMap(randMap);
        PrintVector(randVector);

        return 0;
    }

    for (int j = 0; j < numItemToDel; j++)
    {
        randVector.pop_back();
        randMap.erase(--end(randMap));
    }

    sort(begin(randVector), end(randVector));

    cout << endl << "После удаления:" << endl;

    PrintMap(randMap);
    PrintVector(randVector);

    auto mapsElement = begin(randMap);
    vector <bool> fMap(randMap.size(), false), fVector(randVector.size(), false);   //Отслеживают какие элементы удалить
    int jVector = 0, jMap = 0;
    vector <int> keyMapToDel;
    
    for (const auto& vectorsElement : randVector)
    {
        if (vectorsElement >= mapsElement->first)
        {
            if (vectorsElement == mapsElement->first)
            {
                fMap[jMap] = true;
                fVector[jVector] = true;
            }
            else if (mapsElement != --end(randMap))
            {
                if (!fMap[jMap])
                {
                    keyMapToDel.push_back(mapsElement->first);
                }
                ++mapsElement;
                ++jMap;

                if (vectorsElement > mapsElement->first)
                {
                    while ((vectorsElement > mapsElement->first) && (mapsElement != --end(randMap)) )
                    {
                        if (!fMap[jMap])
                        {
                            keyMapToDel.push_back(mapsElement->first);
                        }
                        ++mapsElement;
                        ++jMap;
                    }
                }

                if (vectorsElement == mapsElement->first)
                {
                    fMap[jMap] = true;
                    fVector[jVector] = true;
                }
            }
        }

        ++jVector;
    }

    while (mapsElement != end(randMap))
    {
        if (!fMap[jMap])
        {
            keyMapToDel.push_back(mapsElement->first);
        }
        ++mapsElement;
        ++jMap;
    }

    const int VECTORSIZE = randVector.size();

    for (const auto& toDel : keyMapToDel)
    {
        randMap.erase(toDel);
    }

    int count = 0;

    for (int j = 0; j < VECTORSIZE; j++)
    {
        if (!fVector[j])
        {
            randVector.erase(randVector.begin() + (j - count));     //Должны учитывать, что следующие элементы смещаются при удалении
            ++count;
        }
    }

    cout << endl << "После синхронизации:" << endl;

    PrintMap(randMap);
    PrintVector(randVector);

    return 0;
}
