# FRAM library for Arduino

* Enables reading and writing data from/to FRAM devices with single SPI I/O.
* FRAM class has methods similar to EEPROM class, and no need for update().

## Methods

### FRAM(size)
constructor.
* size: size of FRAM device [kB]

### begin(ssPin, spi, frequency)
initializes the FRAM library.
* ssPin: pin number of SS (Slave Select), default = SS (4)
* spi: SPI bus, default = SPI
* frequency: SPI clock frequency [Hz], default = 4000000

### end()
terminates the FRAM library.

### read(address)
reads a byte from the FRAM.
* address: the location to read from, starting from 0 (int)
* return: the value stored in that location (byte)

### write(address, value)
writes a byte to the FRAM.
* address: the location to write to, starting from 0 (int)
* value: the value to write, from 0 to 255 (byte)

### get(address, data)
reads any data type or object from the FRAM.
* address: the location to write to, starting from 0 (int)
* data: the data to read, can be a primitive type (eg. float) or a custom struct
* return: a reference to the data passed in

### put(address, data)
writes any data type or object to the FRAM.
* address: the location to write to, starting from 0 (int)
* data: the data to write, can be a primitive type (eg. float) or a custom struct
* return: a reference to the data passed in

### read methods for various types
* readChar  (address)
* readByte  (address)
* readShort (address)
* readUShort(address)
* readLong  (address)
* readULong (address)
* readFloat (address)
* readDouble(address)
* readBool  (address)
* readString(address, buffer, maxLen) ... for char array
* readString(address, maxLen) ... for String object
* readBytes (address, buffer, len)
    
### write methods for various types
* writeChar  (address, value)
* writeByte  (address, value)
* writeShort (address, value)
* writeUShort(address, value)
* writeLong  (address, value)
* writeULong (address, value)
* writeFloat (address, value)
* writeDouble(address, value)
* writeBool  (address, value)
* writeString(address, buffer) ... for char array
* writeString(address, value) ... for String object
* writeBytes (address, buffer, len)

