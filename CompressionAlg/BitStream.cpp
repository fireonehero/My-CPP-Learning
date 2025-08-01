#include "BitStream.hpp"
#include <fstream>

BitWriter::BitWriter(std::ofstream* outputStreamPtr){
    this->outputStream = outputStreamPtr;
    this->buffer = 0;
    this->bitCount = 0;
}

void BitWriter::writeBit(char bit){
    if(bit == '1'){
        this->buffer |= (1 << (7 - this->bitCount));
    }

    this->bitCount += 1;

    if(this->bitCount == 8){
        this->outputStream->put(this->buffer);
        this->buffer = 0;
        this->bitCount = 0;
    }
}

void BitWriter::flush(){
    if(this->bitCount > 0){
        this->outputStream->put(this->buffer);
    }
}

BitReader::BitReader(std::ifstream* inputStreamPtr){
    this->inputStream = inputStreamPtr;
    this->buffer = 0;
    this->bitCount = 8;
}

int BitReader::readBit(){
    int bit;
    
    if(this->bitCount == 8){
        this->inputStream->get(reinterpret_cast<char&>(this->buffer));        

        if (!this->inputStream->good()) {
            return EOF;
        }

        this->bitCount = 0;
    }

    bit = (this->buffer >> (7 - this->bitCount)) & 1;

    this->bitCount += 1;

    return bit;

}