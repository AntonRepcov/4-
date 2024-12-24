#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

string cleanString(const string& input) {
    string result;
    bool lastWasSpace = false;
    bool lastWasPunctuation = false;

    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];

        if (ch == ' ') {
            if (!lastWasSpace) {
                result += ch;
                lastWasSpace = true;
            }
        }
        else if (ch == '.' || ch == ',' || ch == ';' || ch == ':') {
            if (!lastWasPunctuation) {
                result += ch;
                lastWasPunctuation = true;
            }
        }
        else {
            result += ch;
            lastWasSpace = false;
            lastWasPunctuation = false;
        }
    }
    if (result.back() == '.') {
        result.pop_back();
    }

    return result;
}

string fixCapitalization(const string& input) {
    string result = input;
    bool newWord = true;

    for (size_t i = 0; i < result.size(); ++i) {
        if (isalpha(result[i])) {
            if (newWord) {
                result[i] = toupper(result[i]);
                newWord = false;
            }
            else {
                result[i] = tolower(result[i]);
            }
        }
        else {
            newWord = true;
        }
    }

    return result;
}

bool containsDigit(const string& word) {
    for (char c : word) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}

vector<size_t> findSubstring(const string& text, const string& substring) {
    vector<size_t> positions;
    size_t pos = text.find(substring, 0);

    while (pos != string::npos) {
        positions.push_back(pos);
        pos = text.find(substring, pos + 1);
    }

    return positions;
}

int main() {
    setlocale(LC_ALL, "ru-RU");
    cout << "Введите слова: ";
    string input;
    getline(cin, input);

    // Очищаем строку от лишних пробелов и знаков препинания
    input = cleanString(input);

    // 3. Выводим слова без цифр
    istringstream ss(input);
    string word;

    cout << "Слова без цифр: ";
    while (ss >> word) {
        if (!containsDigit(word)) {
            cout << word << " ";
        }
    }
    cout << endl;

    // 4. Преобразуем каждое слово в строке, делая первую букву заглавной
    ss.clear();
    ss.str(input);

    cout << "Слова с 1 заглавной: ";
    while (ss >> word) {
        cout << fixCapitalization(word) << " ";
    }
    cout << std::endl;

    // 5. Линейный поиск подстроки
    string substring;
    cout << "Подстрока для поиска: ";
    cin >> substring;

    vector<size_t> positions = findSubstring(input, substring);

    if (positions.empty()) {
        cout << "Не найдено." << std::endl;
    }
    else {
        std::cout << "Подстрока найдена на позиции: ";
        for (size_t pos : positions) {
            cout << pos << " ";
        }
        cout << endl;
    }

    return 0;
}
