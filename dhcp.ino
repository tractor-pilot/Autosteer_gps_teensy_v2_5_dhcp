#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
#include "dhcp_defs.h"

IPAddress broadcastIP(255,255,255,255);
//uint8_t Eth_myip[4] = {192,168,0,2}; 
uint8_t Eth_subnetMask[4] = {255,255,255,0}; 
uint8_t ipLeaseTime[4] = {255,255,255,255};
uint8_t ipRouter[4] = {0,0,0,1};
uint8_t ipBroadCast[4] = {0,0,0,255};
uint8_t ipDNS[8] = {8,8,8,8,8,8,4,4};
byte ip4client[4] = {0,0,0,112};
char domainNameStr[] = "tractorpilot.local";
String dot = ".";

EthernetUDP dhcpUDP;
uint8_t packetBuffer[DHCP_MESSAGE_SIZE]; 
uint8_t servRespMsg[DHCP_MESSAGE_SIZE];
int srvRespLastElement = 240;
 
void initDHCP() {
  Serial.println("Join TractorPilot community - https://tractorpilot.com Telegram:https://t.me/tractor_pilot");
    for (int i=0; i<3; i++) {
      ipRouter[i] = Eth_myip[i];
      ipBroadCast[i] = Eth_myip[i];
      ip4client[i] = Eth_myip[i];
  }
  dhcpUDP.beginMulticast (broadcastIP,DHCP_SERVER_PORT); 
}

void addServerOptsToMsg(uint8_t optID, uint8_t optSize, uint8_t option[])
{
    servRespMsg[srvRespLastElement] = optID;
    srvRespLastElement++;
    servRespMsg[srvRespLastElement] = optSize;
    srvRespLastElement++;
    for (int i=0; i<optSize; i++)
    {
      servRespMsg[srvRespLastElement] = option[i];
      srvRespLastElement++;  
    }
}

void buildServResponse (uint8_t udpMsg[], int length, uint8_t msgType)
{
    if (length>=240) {
    memset(servRespMsg, 0, DHCP_MESSAGE_SIZE);
    srvRespLastElement = 240;
    memcpy(servRespMsg,udpMsg,240);
   
    int len = strlen(domainNameStr);
    uint8_t domainName[len + 1];
    for (int i = 0; i < len; ++i) {
          domainName[i] = (uint8_t)domainNameStr[i];
    }
    domainName[len] = '\0';

    uint8_t opt [1] = {msgType}; 
    addServerOptsToMsg(dhcpMessageType,sizeof(opt),opt);
    addServerOptsToMsg(dhcpServerIdentifier,sizeof(Eth_myip),Eth_myip);
    addServerOptsToMsg(dhcpIPaddrLeaseTime,sizeof(ipLeaseTime),ipLeaseTime);
    addServerOptsToMsg(dhcpSubnetMask,sizeof(Eth_subnetMask),Eth_subnetMask);
    addServerOptsToMsg(dhcpRoutersOnSubnet,sizeof(ipRouter),ipRouter);
    addServerOptsToMsg(dhcpDns,sizeof(ipDNS),ipDNS);
    addServerOptsToMsg(dhcpDomainName, sizeof(domainName), domainName);
    addServerOptsToMsg(dhcpBroadcastAddr,sizeof(ipBroadCast),ipBroadCast);
    }
}

void dhcpLoop() {

  int packetSize = dhcpUDP.parsePacket();
  if (packetSize) {
    Serial.print("Client DHCP Request Received! Size: ");
    Serial.println(packetSize);
    dhcpUDP.read(packetBuffer, packetSize);
    DHCP_MSG* dhcpMSG = (DHCP_MSG*)packetBuffer;
    Serial.println(dhcpMSG->OPT[0]+dot+dhcpMSG->OPT[1]+dot+dhcpMSG->OPT[2]);

    if (dhcpMSG->OPT[0]==53)
    {
      dhcpMSG->op = DHCP_BOOTREPLY; 
      memcpy(dhcpMSG->yiaddr,ip4client,4);
      memcpy(dhcpMSG->siaddr, Eth_myip,4);

      if (dhcpMSG->OPT[2]==1)
      {
        Serial.println("DHCP DISCOVER FROM CLIEMT");
        buildServResponse((char*)dhcpMSG, packetSize, DHCP_OFFER);
      }
      else if (dhcpMSG->OPT[2]==3)
      {
        Serial.println("DHCP REQUEST FROM CLIENT");
        buildServResponse((char*)dhcpMSG, packetSize,DHCP_ACK);
        Serial.print("ASSIGN IP TO CLIENT");
        Serial.println(ip4client[0]+dot+ip4client[1]+dot+ip4client[2]+dot+ip4client[3]);
      }

      char udpMsg[srvRespLastElement+1];
      for (int i = 0; i < srvRespLastElement+1; ++i) {
        udpMsg[i] = (char)servRespMsg[i];
      }

      dhcpUDP.beginPacket(broadcastIP, DHCP_CLIENT_PORT);
      dhcpUDP.write(udpMsg,srvRespLastElement+1);
      dhcpUDP.endPacket();
    }

  }
  //delay(10);
}

void arrayVarDump(uint8_t arr[], int elementsNum)
{    
    String dot = ".";
    for (int i=0; i<elementsNum; i++)
    {
      Serial.print("\n(");
      Serial.print(i);
      Serial.print(") ");
      Serial.print(arr[i],HEX);
      Serial.print(dot);
    } 
}
