#include "FileEncryptor.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void showHelp()
{
    cout << "\n----- FileEncryptor -----\n"
        << "Использование: \n"
        << " encrypt <input> <output> <key> - зашифровать файл\n"
        << " decrypt <input> <output> <key> - дешифровать файл\n"
        << " (XOR симметричен, поэтому команды идентичны по логике)\n\n";
}

int main(int argc, char* argv[])
{
    // Проверяем количество аргументов
    if (argc != 5)
    {
        showHelp();
        return 1;
    }

    // Извлекаем аргументы командной строки
    string mode = argv[1];
    string inputPath = argv[2];
    string outputPath = argv[3];
    string key = argv[4];

    try
    {
        FileEncryptor enc(key);

        if (mode == "encrypt" || mode == "decrypt")
        {
            if (enc.processFile(inputPath, outputPath))
            {
                cout << (mode == "encrypt" ? "Файл зашифрован" : "Файл расшифрован") << " в: " << outputPath << "\n";              
            }
        }
        else
        {
            cerr << "Неизвестная команда: " << mode << "\n";
            showHelp();
            return 1;
        }
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}