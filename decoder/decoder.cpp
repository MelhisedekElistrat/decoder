﻿#include <iostream>
#include <string>
#include <fstream>
#include "decoder.h"

int main()
{
    //русский язык
    setlocale(LC_ALL, "rus");

    //Создаем штуку для потоковых данных
    std::ifstream fin;

    //Тут будут храниться строки
    std::vector<std::string> arrayStrings;

    try
    {
        //Открываем файел
        fin.open("decoderInputData.txt");
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        std::cout << "Ошибка открытия файла!" << std::endl;
        exit(1);
    }

    //Размер вектора 
    int sizeOfVect = 1;

    //Число строк равно нулю, потом в цикле получится явное число
    int numbOfStrings = 0;

    int i = 0; //хз надо ли оно

    int activePointForCycle = 0;
    //Если строки в файле еще есть
    while (!fin.eof())
    {
        if (i != 0 && activePointForCycle == 0)
        {
            //Увеличивается число строк
            numbOfStrings++;

            //Отдельно увеличивается размер вектора
            sizeOfVect++;
        }

        //Изменяется размер вектора до 1
        arrayStrings.resize(sizeOfVect);

        //Извлекается строка из файла
        std::getline(fin, arrayStrings[numbOfStrings]);

        //Проверка на корректность строк (не пустая строка)
        if (arrayStrings[numbOfStrings] == "")
        {
            //Убираем строку

            /*sizeOfVect--;

            numbOfStrings--;*/
            activePointForCycle++;
            //Идем на новую итерацию
            continue;
        }

        //Если символов меньше трех (2 символа должны остаться, третий потом удалится)
        if (arrayStrings[numbOfStrings].size() < 3)
        {
            std::cout << "Количество символов меньше минимального!" << std::endl;
            exit(4);
        }

        //Размер строк не меньше 100
        if (arrayStrings[numbOfStrings].size() > 100)
        {
            std::cout << "Слишком много символов в строке! \nМаксимальное число символов в строке - 100! " << std::endl;
            exit(5);
        }

        i++;

        if (activePointForCycle != 0)
            activePointForCycle = 0;

    }

    //Максимальное число строк - 100
    if (sizeOfVect > 100)
    {
        std::cout << "Слишком много строк! \nМаксимальное число строк - 100! " << std::endl;
        exit(6);
    }

    //Если файл пустой, то программа вылетает с ошибкой
    if (sizeOfVect == 0)
    {
        std::cout << "Файл пуст!" << std::endl;
        exit(3);
    }

    //bool pointError;

    ////Вызывается функция, декодирующая строки
    //for (int i = 0; i < numbOfStrings; i++)
    //{
    //    pointError = decodingStrings(arrayStrings[i]);

    //    if (!pointError)
    //    //Завершить выполнение программы, если последний символ строки неверен 
    //        exit(15);
    //}

    if (arrayStrings[numbOfStrings] == "")
    {
        arrayStrings.resize(sizeOfVect - 1);
        sizeOfVect--;
        numbOfStrings--;
    }

    decodingAllStrings(arrayStrings);

    //Вызывается объект ofstream для перезаписи данных в файл 
    std::ofstream fout;

    try
    {
        //Открываем файел
        fout.open("decoderInputData.txt");
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        std::cout << "Ошибка открытия файла!" << std::endl;
        exit(1);
    }

    //Хз как работает пока что 20:49
    //Теперь понял 20:53
    fout.clear();

    //Отправляем полученные результаты в файл.
    for (int i = 0; i < sizeOfVect; i++)
    {
        fout << arrayStrings[i] << "\n";
    }

    fin.close();
    fout.close();
}

void decodingAllStrings(std::vector<std::string>& arrayStrings)
{
    bool pointError;

    //Вызывается функция, декодирующая строки
    for (int i = 0; i < arrayStrings.size(); i++)
    {
        pointError = decodingStrings(arrayStrings[i]);

        if (!pointError)
            //Завершить выполнение программы, если последний символ строки неверен 
            exit(15);
    }
}


bool decodingStrings(std::string& arrayStrings)
{
    //Определить число символов в группе
    int numbSymbolsInGroup = numbSymbolsGroups(arrayStrings);

    //Если строка не заканчивается прописной или строчной буквой латинского алфавита, то ошибка
    if (numbSymbolsInGroup == 3456)
    {
        std::cout << "Ошибка, строка(-и) не заканчивается(-ются) нужным символом!" << std::endl;
        return false;
    }

    //Удалить последний символ из строки
    arrayStrings.erase(arrayStrings.size() - 1, 1);

    // Определяет число групп
    int numbGroups = arrayStrings.size() / numbSymbolsInGroup;
    // Если есть остаток от деления, значит конечное число нужно округлить в большую сторону 
    if (arrayStrings.size() % numbSymbolsInGroup != 0)
        numbGroups += 1;

    //Функция, принимающая строку и разбивающая в массив строк по группам и вовзаращющая в текущий двумерный массив строк
    std::vector<std::string> groupsOfStrings = writeGroupsToArrayStrings(arrayStrings, numbSymbolsInGroup, numbGroups);

    std::string endString = writeReverseGroups(groupsOfStrings);

    //сначала очистить массив от лишнего говна
    arrayStrings.clear();
    //arrayStrings = arrayStrings.replace(0, arrayStrings.size() - 1, endString);
    arrayStrings = endString;

    return true;
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

std::string writeReverseGroups(std::vector<std::string>& groupsOfStrings)
{
    int numbGroups = groupsOfStrings.size();
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