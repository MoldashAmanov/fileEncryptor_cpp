#include "FileEncryptor.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Реализация конструктора
FileEncryptor::FileEncryptor(const string& key) : key(key)
{
    if (key.empty())
        throw invalid_argument("Ключ не может быть пустым!");
}
// XOR-шифрование одного байта
uint8_t FileEncryptor::xorByte(uint8_t byte, char keyChar) const
{
    return byte ^ static_cast<uint8_t>(keyChar);
}
// Обработка файла
bool FileEncryptor::processFile(
    const string& inputPath,
    const string& outputPath
) const
{
    // Открываем входной файл в бинарном режиме
    ifstream inFile(inputPath, ios::binary);
    if (!inFile)
    {
        cerr << "Не удалось открыть файл: " << inputPath << "\n";
        return false;
    }
    // Создаем выходной файл в бинарном режиме
    ofstream outFile(outputPath, ios::binary);
    if (!outFile)
    {
        cerr << "Не удалось создать файл: " << outputPath << "\n";
        return false;
    }
    // Читаем весь файл в буфер
    vector<uint8_t> buffer(istreambuf_iterator<char>(inFile), {});
    // Применяем XOR с ключом 
    for (size_t i = 0; i < buffer.size(); i++)
    {
        buffer[i] = xorByte(buffer[i], key[i % key.length()]);
    }
    // Записываем результат
    outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());

    cout << "Успешно обработано " << buffer.size() << " байт.\n";
    return true;
}