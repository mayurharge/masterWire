#include"masterWire.h"
int deviceAddressArray[MAX_SLAVES];
byte readBuf[32]; // max data
masterWire::masterWire(){

}
void masterWire::begin(){
    
}
void masterWire::begin(int sda, int scl){
    
}
void masterWire::reset(){
    
}
void masterWire::ScanDevices(uint8_t addrToScan){
    uint8_t arrayPtr=0;
    if(addrToScan>127){ 
        addrToScan=127;
    }
    for(int i=1 ; i<=addrToScan ; i++){ //address 0 for master
        Wire.beginTransmission(i);
        Wrie.write(ALIVE_BEAT_REQUEST_CMD);
        Wire.endTransmission();
        Wire.requestFrom(i, 1 , true);
        uint8_t Bit = Wire.read();
        if(Bit==ALIVE_BEAT_RECEIVE_CMD){
            if(arrayPtr>(MAX_SLAVES-1)){
                break;
            }
            deviceAddressArray[arrayPtr]=i;
            arrayPtr++;     
        }
    }
}
bool masterWire::isDeviceAlive(uint8_t devID){ // devID is deviceAddressArray's pointer rainging from 1 t0 MAX_SLAVES
        bool status = false;
        if((devID>MAX_SLAVES)||(devID==0))return status;
        Wire.beginTransmission(deviceAddressArray[devID-1]);
        Wrie.write(ALIVE_BEAT_REQUEST_CMD);
        Wire.endTransmission();
        Wire.requestFrom(deviceAddressArray[devID-1], 1 , true);
        uint8_t Bit = Wire.read();
        if(Bit==ALIVE_BEAT_RECEIVE_CMD){
            status=true;
        }
    return status;
}

//=================================================
// relay status commands
// ================================================
void masterWire::setRelayStatus(uint8_t devID, uint8_t relayID, bool status ){

}
void masterWire::getRelayStatus(uint8_t devID, uint8_t relayID){

}
void masterWire::setRelayON_AutoTurnOffTimer(uint8_t devID, uint8_t relayID, unsigned int minutes){

}
void masterWire::setRelayON_AutoTurnOffEnergy(uint8_t devID, uint8_t relayID, unsigned int KWh){

}
//=================================================
// relay energy commands specially designed for implementing in for loops
// ================================================
float masterWire::getRelayVoltage(uint8_t devID, uint8_t relayID){
    uint8_t readAddress = VOLTAGE_POINTER+relayID-1;
    sendData_request(devID,READ,POWER,readAddress);

}
float masterWire::getRelayCurrent(uint8_t devID, uint8_t relayID){
    uint8_t readAddress = CURRENT_POINTER+relayID-1;

}
float masterWire::getRelayPower(uint8_t devID, uint8_t relayID, uint8_t powerType){
    uint8_t readAddress = POWER_POINTER+powerType+(relayID-1)*3;

}
float masterWire::getRelayPowerFactor(uint8_t devID, uint8_t relayID){
    uint8_t readAddress = POWER_FACTOR_POINTER+relayID-1;

}
float masterWire::getRelayHarmonics(uint8_t devID, uint8_t relayID, int harmonicType){
    uint8_t readAddress = HARMONICS_POINTER+harmonicType+(relayID-1)*2;
    
}
unsigned long masterWire::getRelayEnergy(uint8_t devID, uint8_t relayID){
    uint8_t readAddress = relayID;

}
float masterWire::getTotalPower(uint8_t devID, uint8_t powerType){
    uint8_t readAddress = TOTAL_POWER_POINTER + powerType;
}
float masterWire::getTotalPowerfactor(uint8_t devID){
    uint8_t readAddress = TOTAL_POWER_FACTOR;

}


unsigned long masterWire::getTotalEnergy(uint8_t devID){
    uint8_t readAddress = TOTAL_ENERGY;

}
bool   masterWire::checkNuteralFaliure(uint8_t devID){
    // uint8_t readAddress = xyz;

}

void masterWire::sendData(uint8_t devID, uint8_t command, uint8_t regtype, int regAddr, unsigned long value, uint8_t numbytes){
    byte _sendBytes[13];
    _sendBytes[0]= 0x4B;
    _sendBytes[1]= 0X55;
    _sendBytes[2]= command;
    _sendBytes[3]= regtype;
    _sendBytes[4]= regAddr;
    _sendBytes[5]= numbytes;
    _sendBytes[6]= 0x00;
    if(numbytes>2){    
        byte A= (value&0x000000FF);           
        byte B= (value&0x0000FF00)>>8;
        byte C= (value&0x00FF0000)>>16;           
        byte D= (value&0xFF000000)>>24;
        _sendBytes[7]= D;
        _sendBytes[8]= C;
        _sendBytes[9]= B;
        _sendBytes[10]=A;

    }else if(numbytes>1){     
        byte A= (value&0x00FF);           
        byte B= (value&0xFF00)>>8;
        _sendBytes[7]=0x00;
        _sendBytes[8]=0x00;
        _sendBytes[9]= B;
        _sendBytes[10]=A;
    }else {
        _sendBytes[7]=0x00;
        _sendBytes[8]=0x00;
        _sendBytes[9]=0x00;
        _sendBytes[10]=value;
        
    }
    int checksum= 0x15; // will write checkum calculator @ end
    _sendBytes[11]=checksum;
    sendi2cCommand(devID,command,12);

}
void masterWire::sendData_request(uint8_t devID,uint8_t command, int regtype, int regAddr){
    sendData( devID, command,  regtype,  regAddr , 0, 0);
    delay(50); //safety
    requestData(devID);
}
//=================================================
//  sendData_request(devID,READ,POWER,readAddress,2);
// above are globlal functions below local functions
// ================================================
void masterWire::sendi2cCommand(uint8_t devID, int command[],int datalen){
        Wire.beginTransmission(deviceAddressArray[devID-1]);
        for(int i=0;i<datalen;i++){
        Wrie.write(command[i]);
        }
        Wire.endTransmission();
}
void masterWire::requestData(uint8_t devID){
    Wire.requestFrom(deviceAddressArray[devID-1], true);
    while(Wire.available()>0){
        readBuf[i] = Wire.read();
    }     
}