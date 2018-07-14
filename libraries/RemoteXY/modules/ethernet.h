#ifndef _REMOTEXY_MOD_ETHERNET_H_
#define _REMOTEXY_MOD_ETHERNET_H_

#include "classes/RemoteXY_API.h"

class CRemoteXY : public CRemoteXY_API {

  protected:
  char * macAddress;
  uint16_t port;
  EthernetServer *server;
  EthernetClient client;
  uint32_t serverTimeOut;
  
  public:
  CRemoteXY (const void * _conf, void * _var, const char * _accessPassword, const char * _macAddress, uint16_t _port) {
    macAddress = (char *) _macAddress;
    port = _port;
    serverTimeOut = 0;
    init (_conf, _var, _accessPassword);
  }
  
  uint8_t initModule () {  
    uint8_t mac[6];
    delay(100);    
    rxy_getMacAddr (macAddress, mac);  
#if defined(REMOTEXY__DEBUGLOGS)
      REMOTEXY__DEBUGLOGS.println("Ethernet connecting...");
#endif
    if (Ethernet.begin(mac) == 0) {
#if defined(REMOTEXY__DEBUGLOGS)
      REMOTEXY__DEBUGLOGS.println("Ethernet DHCP configuration failed");
#endif
      return 0;
    }
    client.stop();
    server = new EthernetServer (port);
    server->begin();    
#if defined(REMOTEXY__DEBUGLOGS)
    REMOTEXY__DEBUGLOGS.println("Ethernet DHCP connected");
    REMOTEXY__DEBUGLOGS.print("IP: ");
    REMOTEXY__DEBUGLOGS.println(Ethernet.localIP());
    REMOTEXY__DEBUGLOGS.println("Server started");
#endif
    return 1;
  }
 
  
  void handlerModule () {    
    if (!client) {
      client=server->available();
      if (client) {
        resetServerTimeOut ();  // new client
#if defined(REMOTEXY__DEBUGLOGS)
        REMOTEXY__DEBUGLOGS.println ();
        REMOTEXY__DEBUGLOGS.println ("Client connected");
        REMOTEXY__DEBUGLOGS.print ("<-");
#endif
      }
    }
    if (client) {
      if (client.connected()) {
        if (millis () - serverTimeOut > REMOTEXY_SERVER_TIMEOUT) {
          client.stop ();
#if defined(REMOTEXY__DEBUGLOGS)
          REMOTEXY__DEBUGLOGS.println ();
          REMOTEXY__DEBUGLOGS.println ("Client stoped by timeout");
          REMOTEXY__DEBUGLOGS.print ("<-");
#endif
        }
      }
      else {
        client.stop ();
#if defined(REMOTEXY__DEBUGLOGS)
        REMOTEXY__DEBUGLOGS.println ();
        REMOTEXY__DEBUGLOGS.println ("Client stoped");
        REMOTEXY__DEBUGLOGS.print ("<-");
#endif
      }
    }        
  }

  
      
  void sendByte (uint8_t b) {
    if (client) {
      if (client.connected()) {
        client.write(b);    
#if defined(REMOTEXY__DEBUGLOGS)
        REMOTEXY__DEBUGLOGS.print (b, HEX);
        REMOTEXY__DEBUGLOGS.print (' ');
#endif
        resetServerTimeOut ();
      }
    }
  }  
  uint8_t receiveByte () {
    uint8_t b;
    if (client) {
      if (client.connected()) {
        b = client.read();
#if defined(REMOTEXY__DEBUGLOGS)
        REMOTEXY__DEBUGLOGS.print (b, HEX);
        REMOTEXY__DEBUGLOGS.print (' ');
#endif
        resetServerTimeOut ();
        return b;
      }
    }
  }
  uint8_t availableByte () {
    if (client) {
      if (client.connected()) return client.available();
    }
    return 0;
  }  
  
  void resetServerTimeOut () {
    serverTimeOut = millis (); //REMOTEXY_SERVER_TIMEOUT;
  }
  
};

#define RemoteXY_Init() remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD, REMOTEXY_ETHERNET_MAC, REMOTEXY_SERVER_PORT)


#endif //_REMOTEXY_MOD_ETHERNET_H_