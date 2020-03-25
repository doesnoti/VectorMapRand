/*
Личный комментарий
*Недавно узнал, что помимо того, чтобы программа работала корректно, необходимо,
*чтобы у тебя был определённый стиль программирования/комментирования. Я изучал
*этот момент, но вариаций стилей встречал несколько. Какой именно необходим - не знаю.
*Данную программу оформлял так, как привык. Если это не соответствует вашим требованиям,
*то освоить иной стиль программирования не будет проблемой.
*Как написано у меня в резюме: "Могу не иметь каких-то навыков, но способен овладеть
*ими в кратчайшие сроки".
*/

/*
1.Случайными числами от 1 до 9 заполняются значения контейнеров vector[i] и map[i];
2.Удалиются случайное число элементов (не более 15) в каждом контейнере;
3.Проводится синхронизация, чтобы в vector и map остались только имеющиеся в обоих контейнерах элементы.
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

/*
*Функции печатают содержимое контейнеров
*/

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
        cout << element.second << " ";
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

    srand(time(NULL));

    for (int j = 0; j < i; j++)
    {
        randMap.emplace(j, rand() % 9 + 1);
        randVector.push_back(rand() % 9 + 1);
    }

    PrintMap(randMap);
    PrintVector(randVector);

    int numItemToDel = rand() % 16;

    cout << endl << "Кол-во удаляемых элементов: " << numItemToDel << endl;

    for (int j = 0; j < numItemToDel; j++)
    {
        randVector.pop_back();
        randMap.erase(randMap.size() - 1);
    }

    cout << endl << "После удаления:" << endl;

    PrintMap(randMap);
    PrintVector(randVector);

    int size = randVector.size();
    vector <bool> fMap(size, false), fVector(size, false);  //Создаю вектора флагов, которые будут говорить какие элементы не встречаются

    for (int j = 0; j < size; j++)
    {
        for (int k = 0; k < size; k++)
        {
            if (randVector[j] == randMap[k])
            {
                fVector[j] = true;
                fMap[k] = true;
            }
        }
    }

    int count = 0;

    for (int j = 0; j < size; j++)
    {
        if (!fVector[j])
        {
            randVector.erase(randVector.begin() + (j - count)); //Должны учитывать, что индекс элементов смещается при удалении
            ++count;
        }

        if (!fMap[j])
        {
            randMap.erase(j);
        }
    }

    cout << endl << "После синхронизации:" << endl;

    PrintMap(randMap);
    PrintVector(randVector);
}
