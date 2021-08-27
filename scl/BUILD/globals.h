/*+
 * File:	globals.h
 *
 * Purpose:	All global declarations go here.
 *
 * Revision History:
 *
 * 1.0	- Thomas R. Dean - June 2004
 *	- Initial Version
 * 1.1  - Thomas Dean April 2015
 *	- clean up of includes
-*/
#ifndef _GLOBALS_H_
#define  _GLOBALS_H_

#include <stdint.h>
#include <stdio.h>

#define true 1
#define false 0
typedef int bool;

extern FILE * traceFile;
extern char * progname;
extern FILE * traceFileCons;
extern int learnmode;
extern unsigned long long count;
extern unsigned long long failed;

struct HeaderInfo {
	uint32_t srcIP;
	uint32_t dstIP;
	uint16_t srcPort;
	uint16_t dstPort;
	long time;
	unsigned long pktCount;
};

union Data
{
	unsigned int value1;
	char* value2;
	int value3;
	int type;
};



#endif /* _GLOBALS_H_ */
