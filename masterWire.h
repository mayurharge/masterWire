
#include <Arduino.h>
#include <Wire.h>

#include".\commands.h"
#include".\constants.h"

class masterWire{
    private:
    void sendData_request(uint8_t devID,uint8_t command, int regtype, int regAddr);
    void sendData(uint8_t devID, uint8_t command, uint8_t regtype, int regAddr, unsigned long value, uint8_t numbytes);
    void sendi2cCommand(uint8_t devID, int command[],int datalen);
    void requestData(uint8_t devID);

    public:
    void begin();
    void begin(int sda, int scl);
    void reset();// resets slave
    void ScanDevices(uint8_t addrToScan);
    bool isDeviceAlive(uint8_t devID);
    void setRelayStatus(uint8_t devID, uint8_t relayID, bool status );
    bool getRelayStatus(uint8_t devID, uint8_t relayID);
    void setRelayON_AutoTurnOffTimer(uint8_t devID, uint8_t relayID, unsigned int minutes);
    void setRelayON_AutoTurnOffEnergy(uint8_t devID, uint8_t relayID, unsigned int KWh);
    float getRelayVoltage(uint8_t devID, uint8_t relayID);
    float getRelayCurrent(uint8_t devID, uint8_t relayID);
    float getRelayPower(uint8_t devID, uint8_t relayID, uint8_t powerType);
    float getRelayPowerFactor(uint8_t devID, uint8_t relayID);
    float getRelayHarmonics(uint8_t devID, uint8_t relayID, int harmonicType);
    unsigned long getRelayEnergy(uint8_t devID, uint8_t relayID);
    float getTotalPower(uint8_t devID, uint8_t powerType);
    float getTotalPowerfactor(uint8_t devID);
    unsigned long getTotalEnergy(uint8_t devID);
    bool   checkNuteralFaliure(uint8_t devID);

}
