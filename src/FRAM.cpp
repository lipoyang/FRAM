#include <string.h>
#include "FRAM.h"

// FRAM OP-CODE
#define OP_WREN     0x06    // Set Write Enable Latch
#define OP_WRDI     0x04    // Reset Write Enable Latch
#define OP_RDSR     0x05    // Read Status Register
#define OP_WRSR     0x01    // Write Status Register
#define OP_READ     0x03    // Read Memory Code
#define OP_WRITE    0x02    // Write Memory Code
#define OP_RDID     0x9F    // Read Device ID
#define OP_FSTRD    0x0B    // Fast Read Memory Code
#define OP_SLEEP    0xB9    // Fast Read Memory Code

// constructor
// size: size of the FRAM device [kB]
FRAM::FRAM(int size) : _size(size*1024)
{
    ;
}

// destructor
FRAM::~FRAM()
{
    this->end();
}

// begin the FRAM device
// ssPin: pin number of SS (Slave Select)
// spi: SPI bus
// frequency: SPI clock frequency [Hz]
void FRAM::begin(uint8_t  ssPin, SPIClass &spi, uint32_t frequency)
{
    _ssPin     = ssPin;
    _spi       = &spi;
    _frequency = frequency;
    
    _spi->begin();
    
    pinMode(_ssPin, OUTPUT);
    digitalWrite(_ssPin, HIGH);
}

// end the FRAM drive
void FRAM::end()
{
//  _spi->begin();
}

// read bytes
uint8_t* FRAM::readBytes (int address, uint8_t* value, int len)
{
    if (!value || !len) return value;
    if (address < 0 || address + len > _size) return value;
    
    _spi->beginTransaction(SPISettings(_frequency, MSBFIRST, SPI_MODE0));
    
    digitalWrite(_ssPin, LOW);
    uint8_t cmd_buff[4];
    cmd_buff[0] = OP_READ;
    cmd_buff[1] = (uint8_t)((address >> 16) & 0xFF);
    cmd_buff[2] = (uint8_t)((address >>  8) & 0xFF);
    cmd_buff[3] = (uint8_t)( address        & 0xFF);
    
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
    _spi->writeBytes(cmd_buff, 4);
    _spi->transferBytes(NULL, value, len);
#else
    _spi->transfer(cmd_buff, 4);
    uint8_t* ptr = value;
    for(int i = 0; i < len; i++){
        *ptr++ = _spi->transfer(0xFF);
    }
#endif
    digitalWrite(_ssPin, HIGH);
    
    _spi->endTransaction();
    
    return value;
}

// write bytes
void FRAM::writeBytes (int address, const uint8_t* value, int len)
{
    if (!value || !len) return;
    if (address < 0 || address + len > _size) return;
    
    _spi->beginTransaction(SPISettings(_frequency, MSBFIRST, SPI_MODE0));
    
    digitalWrite(_ssPin, LOW);
    _spi->transfer(OP_WREN);
    digitalWrite(_ssPin, HIGH);
    
    digitalWrite(_ssPin, LOW);
    uint8_t cmd_buff[4];
    cmd_buff[0] = OP_WRITE;
    cmd_buff[1] = (uint8_t)((address >> 16) & 0xFF);
    cmd_buff[2] = (uint8_t)((address >>  8) & 0xFF);
    cmd_buff[3] = (uint8_t)( address        & 0xFF);
    
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
    _spi->writeBytes(cmd_buff, 4);
    _spi->writeBytes(value, len);
#else
    _spi->transfer(cmd_buff, 4);
    const uint8_t* ptr = value;
    for(int i = 0; i < len; i++){
        _spi->transfer(*ptr++);
    }
#endif
    digitalWrite(_ssPin, HIGH);
    
    digitalWrite(_ssPin, LOW);
    _spi->transfer(OP_WRDI);
    digitalWrite(_ssPin, HIGH);
    
    _spi->endTransaction();
}

// read a byte
uint8_t FRAM::read(int address)
{
    uint8_t value = 0;
    this->readBytes(address, &value, sizeof(value));
    return value;
}

// write a byte
void FRAM::write(int address, uint8_t value)
{
    this->writeBytes(address, &value, sizeof(value));
}

// read various type data
int8_t FRAM::readChar (int address) {
    return this->readAny<int8_t>(address);
}

uint8_t FRAM::readByte (int address) {
    return this->readAny<uint8_t>(address);
}

int16_t FRAM::readShort (int address) {
    return this->readAny<int16_t>(address);
}

uint16_t FRAM::readUShort (int address) {
    return this->readAny<uint16_t>(address);
}

int32_t FRAM::readLong (int address) {
    return this->readAny<int32_t>(address);
}

uint32_t FRAM::readULong (int address) {
    return this->readAny<uint32_t>(address);
}

float FRAM::readFloat (int address) {
    return this->readAny<float>(address);
}

double FRAM::readDouble (int address) {
    return this->readAny<double>(address);
}

bool FRAM::readBool (int address)
{
    uint8_t value = this->readAny<uint8_t>(address);
    return (value == 0) ? false : true;
}

int FRAM::readString (int address, char* value, int maxLen)
{
    this->readBytes (address, (uint8_t*)value, maxLen);
    int len = strnlen(value, maxLen);
    return len;
}

String FRAM::readString (int address, int maxLen)
{
    char value[maxLen+1] = {0,};
    this->readBytes (address, (uint8_t*)value, maxLen);
    
    int len  = strnlen(value, maxLen);
    if(len == 0) return String();
    
    return String(value);
}

// write various type data
void FRAM::writeChar (int address, int8_t value) {
    this->writeBytes(address, (uint8_t*)(&value), sizeof(value));
}

void FRAM::writeByte (int address, uint8_t value) {
    this->writeBytes(address, (uint8_t*)(&value), sizeof(value));
}

void FRAM::writeShort (int address, int16_t value) {
    this->writeBytes(address, (uint8_t*)(&value), sizeof(value));
}

void FRAM::writeUShort (int address, uint16_t value) {
    this->writeBytes(address, (uint8_t*)(&value), sizeof(value));
}

void FRAM::writeLong (int address, int32_t value) {
    this->writeBytes(address, (uint8_t*)(&value), sizeof(value));
}

void FRAM::writeULong (int address, uint32_t value) {
    this->writeBytes(address, (uint8_t*)(&value), sizeof(value));
}

void FRAM::writeFloat (int address, float value) {
    this->writeBytes(address, (uint8_t*)(&value), sizeof(value));
}

void FRAM::writeDouble (int address, double value) {
    this->writeBytes(address, (uint8_t*)(&value), sizeof(value));
}

void FRAM::writeBool (int address, bool value)
{
    uint8_t bValue = (value) ? 1 : 0;
    this->writeBytes(address, &bValue, sizeof(bValue));
}

void FRAM::writeString (int address, const char* value)
{
    int len = strlen(value);
    this->writeBytes(address, (uint8_t*)value, len+1);
}

void FRAM::writeString (int address, String value)
{
    return this->writeString (address, value.c_str());
}
