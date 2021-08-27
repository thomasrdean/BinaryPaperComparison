#include "putilities.h"

bool lengthRemaining(PDU * thePDU, unsigned long length, char * name) {
	if(thePDU->remaining >= length) {
		thePDU->remaining -= length;
		return true;
	} else {
		//fprintf(stderr,"%s: PDU Length Error file: %s line: %d\n",name, __FILE__ , __LINE__);
		return false;
	}   
}

bool checkSlack(PDU * thePDU, unsigned long len) {
	while(len > 0) {
		if(thePDU->data[thePDU->curPos++] != '\0')
			return false;
		len--;
	};
	return true;
}

uint8_t get8_e(PDU * thePDU, uint8_t endianness) {
	return thePDU->data[thePDU->curPos++];;
}

uint16_t get16_e(PDU * thePDU, uint8_t endianness) {
	uint16_t result;
	if((endianness & 0x1) == LITTLEENDIAN) //Little Endian
		result = thePDU->data[thePDU->curPos++] |
					thePDU->data[thePDU->curPos++] << 8;
	else //Big Endian
		result = thePDU->data[thePDU->curPos++] << 8 | 
					  thePDU->data[thePDU->curPos++];

	return result;
}

uint32_t get24_e(PDU * thePDU, uint8_t endianness) {
	uint32_t result = 0;
	if((endianness & 0x1) == LITTLEENDIAN) //Little Endian
		result = thePDU->data[thePDU->curPos++] |
					thePDU->data[thePDU->curPos++] << 8 |
					thePDU->data[thePDU->curPos++] << 16;
	else //Big Endian
		result = thePDU->data[thePDU->curPos++] << 16 |
					thePDU->data[thePDU->curPos++] << 8 | 
					  thePDU->data[thePDU->curPos++];

	return result;
}

uint32_t get32_e(PDU * thePDU, uint8_t endianness) {
	uint32_t result;
	if((endianness & 0x1) == LITTLEENDIAN) //Little Endian
		result = thePDU->data[thePDU->curPos++] |
					thePDU->data[thePDU->curPos++] << 8 |
					thePDU->data[thePDU->curPos++] << 16 |
					thePDU->data[thePDU->curPos++] << 24;
	else //Big Endian
		result = thePDU->data[thePDU->curPos++] << 24 | 
					thePDU->data[thePDU->curPos++] << 16 | 
					thePDU->data[thePDU->curPos++] << 8 | 
					thePDU->data[thePDU->curPos++];
	return result;
}

uint64_t get48_e(PDU * thePDU, uint8_t endianness) {
	uint64_t result;
	//NOTE: ASSUMING ONLY BIGENDIAN (USED FOR ARP)
	result = (uint64_t)0x0000 << 46 |
					(uint64_t)thePDU->data[thePDU->curPos++] << 40 | 
					(uint64_t)thePDU->data[thePDU->curPos++] << 32 | 
					thePDU->data[thePDU->curPos++] << 24 | 
					thePDU->data[thePDU->curPos++] << 16 | 
					thePDU->data[thePDU->curPos++] << 8 | 
					thePDU->data[thePDU->curPos++];
	return result;
}

uint64_t get64_e(PDU * thePDU, uint8_t endianness) {
	uint64_t result;
	if((endianness & 0x1) == LITTLEENDIAN) 
		result = ((uint64_t)get32_e(thePDU, endianness)) | ((uint64_t)get32_e(thePDU, endianness) << 32);
	else{
	    //uint64_t top  = ((uint64_t)get32_e(thePDU, endianness) << 32);
	    //fprintf(stderr,"top = %llx\n",top);
	    //uint64_t bottom = ((uint64_t)get32_e(thePDU, endianness));
	    //fprintf(stderr,"bottom = %llx\n",bottom);
	    //result = top | bottom;
	    result = ((uint64_t)get32_e(thePDU, endianness) << 32) | ((uint64_t)get32_e(thePDU, endianness));
	}
	return result;
}

float getReal4_e(PDU * thePDU, uint8_t endianness) {
	uint32_t i = get32_e(thePDU, endianness);
 	return *((float *)&i);
}

double getReal8_e(PDU * thePDU, uint8_t endianness) {
	uint64_t i = get64_e(thePDU, endianness);
 	return *((double *)&i);
}

uint8_t get8(PDU * thePDU) {
	return thePDU->data[thePDU->curPos++];;
}

uint16_t get16(PDU * thePDU) {
	return get16_e(thePDU, BIGENDIAN);
}

uint32_t get24(PDU * thePDU) {
	return get24_e(thePDU, BIGENDIAN);
}

uint32_t get32(PDU * thePDU) {
	return get32_e(thePDU, BIGENDIAN);
}

uint64_t get64(PDU * thePDU) {
	return get64_e(thePDU, BIGENDIAN);
}

float getReal4(PDU * thePDU) {
	uint32_t i = get32_e(thePDU, BIGENDIAN);
	return *((float *)&i);
}

double getReal8(PDU * thePDU) {
	uint64_t i = get64_e(thePDU, BIGENDIAN);
	return *((double *)&i);
}

void align4(PDU * thePDU){
   uint32_t slack = thePDU->curPos % 4;
   if (slack){
      // not divisible by 4
      // remove the remaining bytes to be divisible by 4
      checkSlack(thePDU,4-slack);
   }
   // otherwise nothing to be done
}
void align8(PDU * thePDU){
   uint32_t slack = thePDU->curPos % 8;
   if (slack){
      // not divisible by 8
      // remove the remaining bytes to be divisible by 8
      checkSlack(thePDU,8-slack);
   }
   // otherwise nothing to be done
}

//added code here
void slackmod4(PDU * thePDU){
   printf("slackmod4");
   uint32_t slack = thePDU->curPos % 4;
   if(slack > 0)
        {
         checkSlack(thePDU,4-slack);
        }
}

