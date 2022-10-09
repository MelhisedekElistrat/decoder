#include <iostream>
#include <string>
#include "decoder.h"

int main()
{
    //русский язык
    setlocale(LC_ALL, "rus");

    //Просьба ввести строки
    std::cout << "Введите число строк: ";
    int numbOfStrings;
    std::cin >> numbOfStrings;

    //Удаление символа ввода
    std::cin.ignore(32767, '\n');

    //Объявляется вектор строк
    std::vector<std::string> arrayStrings(numbOfStrings);

    //Просьба ввести строки
    std::cout << "Введите строки: " << std::endl;

    //Непосредственный ввод строк
    for (int i = 0; i < numbOfStrings; i++)
    {
        std::getline(std::cin, arrayStrings[i]);
    }

    //вызывается функция, декодирующая строки
    for (int i = 0; i < numbOfStrings; i++)
        decodingStrings(arrayStrings[i]);

    //выводится полученный результат
    std::cout << std::endl;
    for (int i = 0; i < numbOfStrings; i++)
    {
        std::cout << arrayStrings[i] << std::endl;
    }

}

void decodingStrings(std::string& arrayStrings)
{
    //Определить число символов в группе
    int numbSymbolsInGroup = numbSymbolsGroups(arrayStrings);

    //Удалить последний символ из строки
    arrayStrings.erase(arrayStrings.size() - 1, 1);

    // Определяет число групп
    int numbGroups = arrayStrings.size() / numbSymbolsInGroup;
    // Если есть остаток от деления, значит конечное число нужно округлить в большую сторону 
    if (arrayStrings.size() % numbSymbolsInGroup != 0)
        numbGroups += 1;

    //Функция, принимающая строку и разбивающая в массив строк по группам и вовзаращющая в текущий двумерный массив строк
    std::vector<std::string> groupsOfStrings = writeGroupsToArrayStrings(arrayStrings, numbSymbolsInGroup, numbGroups);

    std::string endString = writeReverseGroups(groupsOfStrings, numbGroups);

    //сначала очистить массив от лишнего говна
    arrayStrings.clear();
    //arrayStrings = arrayStrings.replace(0, arrayStrings.size() - 1, endString);
    arrayStrings = endString;
}

int numbSymbolsGroups(std::string& stringForDetermNumbGroups)
{
    //Определяет размер строки
    int lenOfString = stringForDetermNumbGroups.size();

    //Определяет символ, определяющий число символов в одной группе
    char lastSymb = stringForDetermNumbGroups[lenOfString - 1];
    //Проверяет, если последний символ - прописной, то сделать ее строчной 
    if (lastSymb >= 65 && lastSymb <= 90) {
        lastSymb += 32;
    }

    int numbSymbInGroups;
    switch (lastSymb)
    {
    case 'a':
        numbSymbInGroups = 2;
        break;
    case 'b':
        numbSymbInGroups = 3;
        break;
    case 'c':
        numbSymbInGroups = 4;
        break;
    case 'd':
        numbSymbInGroups = 5;
        break;
    case 'e':
        numbSymbInGroups = 6;
        break;
    case 'f':
        numbSymbInGroups = 7;
        break;
    case 'g':
        numbSymbInGroups = 8;
        break;
    case 'h':
        numbSymbInGroups = 9;
        break;
    case 'i':
        numbSymbInGroups = 10;
        break;
    case 'j':
        numbSymbInGroups = 11;
        break;
    case 'k':
        numbSymbInGroups = 12;
        break;
    case 'l':
        numbSymbInGroups = 13;
        break;
    case 'm':
        numbSymbInGroups = 14;
        break;
    case 'n':
        numbSymbInGroups = 15;
        break;
    case 'o':
        numbSymbInGroups = 16;
        break;
    case 'p':
        numbSymbInGroups = 17;
        break;
    case 'q':
        numbSymbInGroups = 18;
        break;
    case 'r':
        numbSymbInGroups = 19;
        break;
    case 's':
        numbSymbInGroups = 20;
        break;
    case 't':
        numbSymbInGroups = 21;
        break;
    case 'u':
        numbSymbInGroups = 22;
        break;
    case 'v':
        numbSymbInGroups = 23;
        break;
    case 'w':
        numbSymbInGroups = 24;
        break;
    case 'x':
        numbSymbInGroups = 25;
        break;
    case 'y':
        numbSymbInGroups = 26;
        break;
    case 'z':
        numbSymbInGroups = 27;
        break;

    default:
        numbSymbInGroups = 3456;
        break;
    }

    return numbSymbInGroups;
}

//ПРОВЕРИТЬ ЭТУ ФУНКЦИЮ В for
std::vector<std::string> writeGroupsToArrayStrings(std::string& stringForReverseGroups, int numbSymbolsInGroup, int numbGroups)
{
    // Объявить массив строк
    std::vector<std::string> arrayOfStringsForReverse(numbGroups);

    //Заполнить массив строк группами исходной строки
    for (int i = 0, j = 0; i < stringForReverseGroups.size(); i += numbSymbolsInGroup, j++)
    {
        arrayOfStringsForReverse.at(j) = stringForReverseGroups.substr(i, numbSymbolsInGroup);
    }

    return arrayOfStringsForReverse;
}

std::string writeReverseGroups(std::vector<std::string>& groupsOfStrings, int numbGroups)
{
    //Объявляем вектор, в который запишем обратные строки
    std::vector<std::string> reversedStrings(numbGroups);

    //Присводить каждой строке нового вектора строку старого вектора с конца.
    // (Берем numbGroups - 1, чтобы обратиться правильно по индексу и вычитаем число i
    for (int i = 0; i < numbGroups; i++)
        reversedStrings[i] = groupsOfStrings[numbGroups - 1 - i];

    //Объявляем строку, которая будет иметь конечный вид строки
    std::string endString;

    // Каждую группу конкатанируем к строке
    for (int i = 0; i < numbGroups; i++)
    {
        if (i == 0)
        {
            endString = reversedStrings[i];
            continue;
        }

        endString += reversedStrings[i];
    }

    //Вернем строку
    return endString;
}