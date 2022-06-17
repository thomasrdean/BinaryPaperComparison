grammar ARP;

@header {
#include <fstream>
typedef char macArray[8];
typedef unsigned int ipArray[4];
}

arp: hwType protocolType hwSize protocolSize opcode senderMAC senderIP targetMAC targetIP
{ std::cout << "Successufly parsed ARP Packet" << std::endl;};

hwType: word16;
protocolType: word16;
hwSize: BYTE;
protocolSize: BYTE;
opcode: word16;
senderMAC: mac;
senderIP: ip {std::cout << "SenderIP: " << ($ip.i[0]) << ":" << ($ip.i[1]) << ":";
              std::cout << ($ip.i[2]) << ":" << ($ip.i[3]) << std::endl;};
targetMAC: mac;
targetIP: ip {std::cout << "TargetIP: " << ($ip.i[0]) << ":" << ($ip.i[1]) << ":";
              std::cout << ($ip.i[2]) << ":" << ($ip.i[3]) << std::endl;};

mac returns [macArray m]:
    b0=BYTE b1=BYTE b2=BYTE b3=BYTE b4=BYTE b5=BYTE
    {$m[0]=$b0->getText()[0]; $m[1]=$b1->getText()[0]; $m[2]=$b2->getText()[0]; $m[3]=$b3->getText()[0];$m[4]=$b4->getText()[0]; $m[5]=$b5->getText()[0];};

word16 returns [unsigned int v]:
    b1=BYTE b2=BYTE {$v = $b1->getText()[0] << 8 || $b2->getText()[0];};

ip returns [ipArray i]:
    b0=BYTE b1=BYTE b2=BYTE b3=BYTE
    { $i[0] = ($b0->getText()[0]); $i[1]=($b1->getText()[0]); $i[2]=($b2->getText()[0]);$i[3]=($b3->getText()[0]); };

BYTE: '\u0000'..'\u00FF';

