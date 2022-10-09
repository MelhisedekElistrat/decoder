#include <iostream>
#include <string>
#include <fstream>
#include "decoder.h"

int main()
{
    //русский язык
    setlocale(LC_ALL, "rus");

    //Создаем fin для потоковых данных
    std::ifstream fin;

    //Установить маску исключений, чтобы выводилась ошибка открытия файла
    fin.exceptions(std::istream::badbit | std::ifstream::failbit);

    //Тут будут храниться строки
    std::vector<std::string> arrayStrings;

    //Название файла с входными данными
    std::string nameFileInput = "input.txt";

    try
    {
        //Открываем файел
        fin.open(nameFileInput);
    }
    catch (const std::exception& ex)
    {
        //Выводится тип ошибки
        std::cout << ex.what() << std::endl;

        //Если неверное расширение файла
        if (nameFileInput.find(".txt") == std::string::npos)
        {
            std::cout << "Неверно указано расширение файла. Файл должен иметь расширение .txt" << std::endl;
            exit(1);
        }

        //Если ошибка в названии файла
        std::cout << "Неверно указан файл с входными данными. Возможно, файл не существует" << std::endl;
        exit(1);
    }

    //Отключаем генерацию всех исключений
    fin.exceptions(std::ifstream::goodbit);

    //Размер вектора 
    int sizeOfVect = 1;

    //Число строк равно нулю, потом в цикле получится явное число
    int numbOfStrings = 0;

    //Если не равна нулю, то можно будет переходить на другую строку
    int moveToNextString = 0;

    //Если точка равна 0,  то можно будет переходить на другую строку
    int activePointForCycle = 0;

    //Если строки в файле еще есть
    while (!fin.eof())
    {
        //
        if (moveToNextString != 0 && activePointForCycle == 0)
        {
            //Увеличивается число строк
            numbOfStrings++;

            //Отдельно увеличивается размер вектора
            sizeOfVect++;
        }

        //Изменяется размер вектора до 1
        arrayStrings.resize(sizeOfVect);

        //Извлекается строка из файла
        //Возникает исключение при считывании пустой строки
        std::getline(fin, arrayStrings[numbOfStrings]);

        //Проверка на корректность строк (не пустая строка)
        if (arrayStrings[numbOfStrings] == "")
        {
            //Делаем данный флаг 1, чтобы при заходе на следующую итерацию
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

        //Если все соответствует условиям, переходим на другую строку
        moveToNextString++;

        //Если строка извлеклась корректно, то обнуляем переменную, чтобы перейти на следующую строку
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
    if (sizeOfVect == 1 && arrayStrings[0] == "")
    {

        std::cout << "Файл пуст!" << std::endl;
        exit(3);
    }

    //Удалить вме пустые строки
    if (arrayStrings[numbOfStrings] == "")
    {
        arrayStrings.resize(sizeOfVect - 1);
        sizeOfVect--;
        numbOfStrings--;
    }

    //Функция для декодирования строк
    decodingAllStrings(arrayStrings);

    //Вызывается объект ofstream для записи данных в файл 
    std::ofstream fout;

    //Названиев файла вывода
    std::string nameFileOutput = "output.txt";
    try
    {
        //Открываем файел
        fout.open(nameFileOutput);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        if (nameFileOutput.find(".txt") == std::string::npos)
        {
            std::cout << "Неверно указано расширение файла. Файл должен иметь расширение .txt" << std::endl;
            exit(1);
        }
        std::cout << "Ошибка открытия файла!" << std::endl;
        exit(1);
    }

    fout.clear();

    //Отправляем полученные результаты в файл.
    for (int i = 0; i < sizeOfVect; i++)
    {
        fout << arrayStrings[i] << "\n";
    }

    fin.close();
    fout.close();
}
/*
    \arrayStrings - строка, которую надо изменить
*/
void decodingAllStrings(std::vector<std::string>& arrayStrings)
{
    bool pointError;

    //Вызывается функция, декодирующая строки
    for (int i = 0; i < arrayStrings.size(); i++)
    {
        pointError = decodingString(arrayStrings[i]);

        if (!pointError)
            //Завершить выполнение программы, если последний символ строки неверен 
        {
            std::cout << "Ошибка, строка " << i + 1 << " не заканчивается нужным символом!" << std::endl;
            exit(15);
        }
    }
}

bool decodingString(std::string& arrayStrings)
{
    //Определить число символов в группе
    int numbSymbolsInGroup = numbSymbolsGroups(arrayStrings);

    //Если строка не заканчивается прописной или строчной буквой латинского алфавита, то ошибка
    if (numbSymbolsInGroup == 3456)
    {
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

int numbSymbolsGroups(std::string& stringForDetermNumbSymbols)
{
    int numbSymbInGroups;
    //Определяет размер строки
    int lenOfString = stringForDetermNumbSymbols.size();
    if (lenOfString == 0)
    {
        numbSymbInGroups = 3456;
        return numbSymbInGroups;
    }

    //Определяет символ, определяющий число символов в одной группе
    char lastSymb = stringForDetermNumbSymbols[lenOfString - 1];

    //Проверяет, если последний символ - прописной, то сделать ее строчной 
    if (lastSymb >= 65 && lastSymb <= 90) {
        lastSymb += 32;
    }

    //Находит нужное число символов в группе (3456, если символ не нашелся)
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