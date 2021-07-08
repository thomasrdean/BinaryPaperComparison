CFLAGS = -g 
LDFLAGS = -g
BASEOBJS= ARP_Generated.o UDP_Generated.o IGMP_Generated.o RTPS_Generated.o NTP_Generated.o putilities.o packet.o StringHash.o DNS_Generated.o

OBJS= $(BASEOBJS) callback.o
LEARNOBJS= $(BASEOBJS) callbackLearn.o

# no constraint engine, so no learn mode, but leave in the makefile for integration for now
all: bin/pcapparse bin/pcapdebug #pcapparseLearn pcapdebugLearn

bin/pcapparse:  pmain.o $(OBJS)
	gcc -o bin/pcapparse $(LDFLAGS) pmain.o $(OBJS) -lpcap 

bin/pcapdebug: pmain.o $(OBJS)
	gcc -O0 -o bin/pcapdebug $(LDFLAGS) pmain.o $(OBJS) -lpcap

bin/pcapparseLearn:  pmain.o $(LEARNOBJS)
	gcc -o bin/pcapparseLearn $(LDFLAGS) pmain.o $(OBJS) -lpcap 

bin/pcapdebugLearn: pmain.o $(LEARNOBJS)
	gcc -O0 -o bin/pcapdebugLearn $(LDFLAGS) pmain.o $(OBJS) -lpcap

clean:
	rm -f *.o bin/pcapparse bin/pcapdebug bin/pcapparseLearn bin/pcapdebugLearn

# MAIN
pmain.o: globals.h pglobals.h 

# PARSER  - assumes the network protocols for DND research
# need to generalize this

UDP_Generated.o: globals.h pglobals.h UDP_Generated.h
IGMP_Generated.o: globals.h pglobals.h IGMP_Generated.h
RTPS_Generated.o: globals.h pglobals.h RTPS_Generated.h
ARP_Generated.o: globals.h pglobals.h ARP_Generated.h
DNS_Generated.o: globals.h pglobals.h DNS_Generated.h

putilities.o: putilities.h

packet.o: globals.h packet.h
pglobals.h: packet.h
	touch pglobals.h

StringHash.o: StringHash.h

callback.o: globals.h StringHash.h IGMP_Generated.h RTPS_Generated.h

callbackLearn.o: callback.c globals.h StringHash.h IGMP_Generated.h RTPS_Generated.h
	gcc -DLEARN $(CFLAGS) -c -o callbackLearn.o
