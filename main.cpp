#include <iostream>
#include <map>
#include <string>
using namespace std;
bool CommandAdd (string str);
bool haveLetters (string str);
bool findSurname (string str);
bool findNumber (string str);
int main() {

    map<string, string> phonebook;
    string command;

    while (phonebook.size()< 5) {
        //ввод команды
        cout << ": " << endl;
        getline (cin, command);

        //добавление номера
        if (CommandAdd(command)) { // команда добавления
            string first; // первая часть
            string second; // вторая часть
            bool space = false; // наличие пробела
            bool plus = false; // наличие +
            bool error = false; // если была ошибка
            for (int i = 0; i < command.length() && !error; i++) {
                // Если + не на 0ом месте - ошибка. Так же исключается наличие больше одного +
                if (command[i] == '+' && i > 0) {
                    error = true;
                    cout << "incorrect number";
                    break;
                }
                if (command[0] == '+') { plus = true; } // наличие +
                if (command[i] == ' ') { space = true; } // наличие пробела
                // если цифры, + или - и не пробел
                if ((isdigit(command[i]) || command[i] == '-' || plus) && !space) {
                    // добавляем символы в первую часть
                    first += command[i];
                }// если не пробел и был пробел
                else if (command[i] != ' ' && space) {
                    // если не буквы - ошибка
                    if (isdigit(command[i]) ||
                        (command[i] < 65 || (command[i] > 90 && command[i] < 97) || command[i] > 122)) {
                        error = true;
                        cout << "Incorrect surname";
                        break;
                    }
                    // добавляем ко второй части
                    second += command[i];
                }
            }
            // если ошибка - выводим информацию
            if (error) cout << "Invalid request. Enter again";
            else { // иначе добавляем информацию к слолварю
                phonebook.insert(make_pair(first, second));
                cout << "Insert in phonebook complete";
            }
        } else if (findSurname(command)) { // ищем по номеру фамилию

            map<string, string>::iterator it = phonebook.find(command);
            if (it != phonebook.end()) {
                cout << it->first << " " << it->second << endl;
            } else { cout << "Number not found!\n"; }
        } else if (findNumber(command)) { // ищем по фамилии номер
            for (map<string, string>::iterator i = phonebook.begin(); i != phonebook.end(); i++) {
                if (i->second == command) { cout << i->first << " " << i->second; }
            }
        } else {cout << "Error";}
    }
}

bool haveLetters (string str){
    bool haveLetters = false;
    for (int i = 0; i < str.length (); i++){
        if (str[i] >= 65 && str [i] <= 90 || str [i] >=97 && str [i] <= 122) {haveLetters = true;}
    }
    return haveLetters;
}
bool CommandAdd (string str) { //проверка, является ли команда добавлением

    if ((isdigit(str [0]) || str[0] == '+') && isdigit (str[1]) && haveLetters(str)) {
        return true;
    } else {return false;}
}
bool findSurname (string str){
    if ((isdigit(str [0]) || str[0] == '+') && isdigit (str[1]) && !haveLetters (str) ){
        return true;
    }
    return false;
}
bool findNumber (string str){
    bool Surname = true;
    for (int i = 0; i < str.length (); i++){
        if (isdigit (str[i])|| (str [i] < 65 ||(str [i] > 90 && str [i] < 97 )|| str [i] >122 ) ) {return false;}
    }
    return true;
}