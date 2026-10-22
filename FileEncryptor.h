#pragma once
#include <string>
#include <cstdint>

using namespace std;

class FileEncryptor
{
    private:
        string key; // Ключ шифрования
        
        // XOR-шифрование одного байта
        uint8_t xorByte(uint8_t byte, char keyChar) const;
    public:
        // Конструктор принимает ключ
        explicit FileEncryptor(const string& key);
        // Обработка файла (шифрование/дешифрование)
        bool processFile(
            const string& inputPath,
            const string& outputPath
        ) const;
};