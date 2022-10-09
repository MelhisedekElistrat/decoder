/*!\mainpage decoder
* ѕрограмма УDecodingФ предназначена дл€ расшифровки текста,\n
* который был зашифрован разбитием каждой строки на N символов\n 
* N в каждой строке разное) перестановкой групп местами.\n
* 
*/

#pragma once
#include <vector>


/*! √лавна€ функци€, декодирующа€ строку
*	\param[in\out] arrayStrings - строки, которые надо декодировать
*	\exeption error ошибка, если хот€ бы одна строка не заканчиваетс€ нужным символом
*/
void decodingAllStrings(std::vector<std::string>& arrayStrings);

/*! ‘ункци€ декодировани€ каждой строки
*	\param[in\out] arrayStrings - строки, которые надо декодировать 
*	\return true, если декодинг прошел успешно; false, если строка не заканчиваетс€ нужным символом
*/
bool decodingString(std::string& arrayStrings);

/*! ‘ункци€, определ€юща€ число символов в группе
*	\param[in\out] stringForDetermNumb - строка, в которой надо определить число символов в группе
*	\param[out] numbSymbInGroups - число символов в группе
*	\return число символов в группе
*/
int numbSymbolsGroups(std::string& stringForDetermNumbSymbols);


/*! ‘ункци€, раздел€юща€ строку на массив строк по группам
*	\param[in\out] stringForReverseGroups - строка дл€ переворачивани€
*	\param[in] numbSymbolsInGroup - число символов в группе
*	\param[in] numbGroups - число групп в строке
*	\return вектор строк, в каждой строке которого хран€тс€ группы, на которые разбилась строка
*/
std::vector<std::string> writeGroupsToArrayStrings(std::string& stringForReverseGroups, int numbSymbolsInGroup, int numbGroups);

/*! ‘ункци€, записывающа€ вектор строк наоборот в одну строку
*	\param[in] groupsOfStrings - вектор строк, которые надо записать в обратном пор€дке
*	\param[out] endString - перевернута€ строка
*	\return декодированна€ итогова€ строка
*/
std::string writeReverseGroups(std::vector<std::string>& groupsOfStrings);