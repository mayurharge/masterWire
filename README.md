# KIOT_i2c_Master

List of functions:-
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30

Function parameter properties
1. "devID" is uint8_t and deviceAddressArray's pointer rainging from 1 t0 MAX_SLAVES
2. "relayID" range 1-3 slave will not accept more than 3
3. setRelayON_AutoTurnOffTimer & setRelayON_ AutoTurnOffEnergy slave will turn on relay no matter previous state

1. relayGet[3];
2. powerGet[MAX_PARAMS];
3. relayAutoTimer[3]; same for read
4. calibSet[6]; same for read;
5. energyGet[3]; unsigned long;




command flow
reg - relay reg

send command 



1       2       3       4       5       6           7       8       9       10      11      12             
0x04B   0x55    0x01    0x01    addr    numbytes    buf     MSB                     LSB     checksum
                0x02    0x04    addr    numbytes    buf     byte1   byte2   byte3   byte4
    heade       r/w     regType regAddr

byte 6 to byte 11 == 0x00 for read command



