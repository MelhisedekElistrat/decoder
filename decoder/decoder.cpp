#include <iostream>
#include <string>
#include "decoder.h"

int main()
{
    //������� ����
    setlocale(LC_ALL, "rus");

    //������� ������ ������
    std::cout << "������� ����� �����: ";
    int numbOfStrings;
    std::cin >> numbOfStrings;

    //�������� ������� �����
    std::cin.ignore(32767, '\n');

    //����������� ������ �����
    std::vector<std::string> arrayStrings(numbOfStrings);

    //������� ������ ������
    std::cout << "������� ������: " << std::endl;

    //���������������� ���� �����
    for (int i = 0; i < numbOfStrings; i++)
    {
        std::getline(std::cin, arrayStrings[i]);
    }

    //���������� �������, ������������ ������
    for (int i = 0; i < numbOfStrings; i++)
        decodingStrings(arrayStrings[i]);

    //��������� ���������� ���������
    std::cout << std::endl;
    for (int i = 0; i < numbOfStrings; i++)
    {
        std::cout << arrayStrings[i] << std::endl;
    }

}

void decodingStrings(std::string& arrayStrings)
{
    //���������� ����� �������� � ������
    int numbSymbolsInGroup = numbSymbolsGroups(arrayStrings);

    //������� ��������� ������ �� ������
    arrayStrings.erase(arrayStrings.size() - 1, 1);

    // ���������� ����� �����
    int numbGroups = arrayStrings.size() / numbSymbolsInGroup;
    // ���� ���� ������� �� �������, ������ �������� ����� ����� ��������� � ������� ������� 
    if (arrayStrings.size() % numbSymbolsInGroup != 0)
        numbGroups += 1;

    //�������, ����������� ������ � ����������� � ������ ����� �� ������� � ������������ � ������� ��������� ������ �����
    std::vector<std::string> groupsOfStrings = writeGroupsToArrayStrings(arrayStrings, numbSymbolsInGroup, numbGroups);

    std::string endString = writeReverseGroups(groupsOfStrings, numbGroups);

    //������� �������� ������ �� ������� �����
    arrayStrings.clear();
    //arrayStrings = arrayStrings.replace(0, arrayStrings.size() - 1, endString);
    arrayStrings = endString;
}

int numbSymbolsGroups(std::string& stringForDetermNumbGroups)
{
    //���������� ������ ������
    int lenOfString = stringForDetermNumbGroups.size();

    //���������� ������, ������������ ����� �������� � ����� ������
    char lastSymb = stringForDetermNumbGroups[lenOfString - 1];
    //���������, ���� ��������� ������ - ���������, �� ������� �� �������� 
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

//��������� ��� ������� � for
std::vector<std::string> writeGroupsToArrayStrings(std::string& stringForReverseGroups, int numbSymbolsInGroup, int numbGroups)
{
    // �������� ������ �����
    std::vector<std::string> arrayOfStringsForReverse(numbGroups);

    //��������� ������ ����� �������� �������� ������
    for (int i = 0, j = 0; i < stringForReverseGroups.size(); i += numbSymbolsInGroup, j++)
    {
        arrayOfStringsForReverse.at(j) = stringForReverseGroups.substr(i, numbSymbolsInGroup);
    }

    return arrayOfStringsForReverse;
}

std::string writeReverseGroups(std::vector<std::string>& groupsOfStrings, int numbGroups)
{
    //��������� ������, � ������� ������� �������� ������
    std::vector<std::string> reversedStrings(numbGroups);

    //���������� ������ ������ ������ ������� ������ ������� ������� � �����.
    // (����� numbGroups - 1, ����� ���������� ��������� �� ������� � �������� ����� i
    for (int i = 0; i < numbGroups; i++)
        reversedStrings[i] = groupsOfStrings[numbGroups - 1 - i];

    //��������� ������, ������� ����� ����� �������� ��� ������
    std::string endString;

    // ������ ������ ������������� � ������
    for (int i = 0; i < numbGroups; i++)
    {
        if (i == 0)
        {
            endString = reversedStrings[i];
            continue;
        }

        endString += reversedStrings[i];
    }

    //������ ������
    return endString;
}