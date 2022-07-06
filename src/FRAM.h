#pragma once

#include <Arduino.h>
#include <SPI.h>

class FRAM {
public:
    FRAM(int size);
    ~FRAM(void);
    
    // begin / end
    void begin(
            uint8_t  ssPin=SS,
            SPIClass &spi=SPI, 
            uint32_t frequency=4000000);
    void end();
    
    // read / write bytes
    uint8_t* readBytes  (int address,       uint8_t* value, int len);
    void     writeBytes (int address, const uint8_t* value, int len);
    
    // read / write a byte
    uint8_t read (int address);
    void    write(int address, uint8_t val);
    
    // read various type data
    int8_t   readChar  (int address);
    uint8_t  readByte  (int address);
    int16_t  readShort (int address);
    uint16_t readUShort(int address);
    int32_t  readLong  (int address);
    uint32_t readULong (int address);
    float    readFloat (int address);
    double   readDouble(int address);
    bool     readBool  (int address);
    int      readString(int address, char* value, int maxLen);
    String   readString(int address, int maxLen);
    
    // write various type data
    void writeChar  (int address, int8_t   value);
    void writeByte  (int address, uint8_t  value);
    void writeShort (int address, int16_t  value);
    void writeUShort(int address, uint16_t value);
    void writeLong  (int address, int32_t  value);
    void writeULong (int address, uint32_t value);
    void writeFloat (int address, float    value);
    void writeDouble(int address, double   value);
    void writeBool  (int address, bool     value);
    void writeString(int address, const char* value);
    void writeString(int address, String value);
    
    // get(read) any type data
    template<class T>
    T & get(int address, T &t)
    {
        this->readBytes(address, (uint8_t*)(&t), sizeof(T));
        return t;
    }
    
    // put(write) any type data
    template<class T>
    const T & put(int address, const T &t)
    {
        this->writeBytes(address, (uint8_t*)(&t), sizeof(T));
        return t;
    }
    
private:
    int       _size;
    uint8_t   _ssPin;
    SPIClass* _spi;
    uint32_t  _frequency;
    
    // read any type data (private function)
    template<class T>
    T readAny(int address)
    {
        T t = 0;
        this->readBytes(address, (uint8_t*)(&t), sizeof(T));
        return t;
    }
};
