#ifndef PUTILITIES_H
#define PUTILITIES_H

#include "globals.h"
#include "pglobals.h"

bool lengthRemaining(PDU * thePDU, unsigned long length, char * name);
bool checkSlack(PDU * thePDU, unsigned long len);
uint8_t get8_e(PDU * thePDU, uint8_t endianness);
uint16_t get16_e(PDU * thePDU, uint8_t endianness);
uint32_t get24_e(PDU * thePDU, uint8_t endianness);
uint32_t get32_e(PDU * thePDU, uint8_t endianness);
uint64_t get48_e(PDU * thePDU, uint8_t endianness);
uint64_t get64_e(PDU * thePDU, uint8_t endianness);
float getReal4_e(PDU * thePDU, uint8_t endianness);
double getReal8_e(PDU * thePDU, uint8_t endianness);
uint8_t get8(PDU * thePDU);
uint16_t get16(PDU * thePDU);
uint32_t get24(PDU * thePDU);
uint32_t get32(PDU * thePDU);
uint64_t get64(PDU * thePDU);
float getReal4(PDU * thePDU);
double getReal8(PDU * thePDU);
#endif /* PUTILITIES_H */