/*
 * UDP implementation (as per http://tools.ietf.org/html/rfc768)
 *
 * Author:
 * Thomas Watteyne <watteyne@eecs.berkeley.edu>, August 2010
 * Ankur Mehta <mehtank@eecs.berkeley.edu>, September 2010
 */

#include "openwsn.h"
#include "udp.h"
#include "openserial.h"
#include "packetfunctions.h"
#include "forwarding.h"
#include "openqueue.h"
//UDP applications
#include "appudpchannel.h"
#include "appudpecho.h"
#include "appudpgina.h"
#include "appudpheli.h"
#include "appudpinject.h"
#include "appudpleds.h"
#include "appudpprint.h"
#include "appudpsensor.h"

//===================================== variables =============================

//===================================== prototypes ============================

//===================================== public ================================

void udp_init() {
}

error_t udp_send(OpenQueueEntry_t* msg) {
   msg->owner       = COMPONENT_UDP;
   msg->l4_protocol = IANA_UDP;
   msg->l4_payload  = msg->payload;
   msg->l4_length   = msg->length;
   packetfunctions_reserveHeaderSize(msg,sizeof(udp_ht));
   packetfunctions_htons(msg->l4_sourcePortORicmpv6Type,&(msg->payload[0]));
   packetfunctions_htons(msg->l4_destination_port,&(msg->payload[2]));
   packetfunctions_htons(msg->length,&(msg->payload[4]));
   packetfunctions_calculateChecksum(msg,(uint8_t*)&(((udp_ht*)msg->payload)->checksum));
   return forwarding_send(msg);
}

void udp_sendDone(OpenQueueEntry_t* msg, error_t error) {
   msg->owner = COMPONENT_UDP;
   switch(msg->l4_sourcePortORicmpv6Type) {
      case WKP_UDP_CHANNEL:
         appudpchannel_sendDone(msg,error);
         break;
      case WKP_UDP_ECHO:
         appudpecho_sendDone(msg,error);
         break;
      case WKP_UDP_GINA:
         appudpgina_sendDone(msg,error);
         break;
      /* remove heli application for now since we need TimerA for IEEE802.15.4e
      case WKP_UDP_HELI:
         appudpheli_sendDone(msg,error);
         break;
      */
      case WKP_UDP_LEDS:
         appudpleds_sendDone(msg,error);
         break;
      case WKP_UDP_INJECT:
         appudpinject_sendDone(msg,error);
         break;
      case WKP_UDP_DISCARD:
         appudpprint_sendDone(msg,error);
         break;
      case WKP_UDP_SENSOR:
         appudpsensor_sendDone(msg,error);
         break;
      default:
         openserial_printError(COMPONENT_UDP,ERR_UNSUPPORTED_PORT_NUMBER,msg->l4_sourcePortORicmpv6Type,0);
         openqueue_freePacketBuffer(msg);         
   }
}

void udp_receive(OpenQueueEntry_t* msg) {
   msg->owner                      = COMPONENT_UDP;
   msg->l4_sourcePortORicmpv6Type  = msg->payload[0]*256+msg->payload[1];
   msg->l4_destination_port        = msg->payload[2]*256+msg->payload[3];
   packetfunctions_tossHeader(msg,sizeof(udp_ht));
   switch(msg->l4_destination_port) {
      case WKP_UDP_CHANNEL:
         appudpchannel_receive(msg);
         break;
      case WKP_UDP_ECHO:
         appudpecho_receive(msg);
         break;
      case WKP_UDP_GINA:
         appudpgina_receive(msg);
         break;
      /* remove heli application for now since we need TimerA for IEEE802.15.4e
      case WKP_UDP_HELI:
         appudpheli_receive(msg);
         break;
      */
      case WKP_UDP_LEDS:
         appudpleds_receive(msg);
         break;
      case WKP_UDP_INJECT:
         appudpinject_receive(msg);
         break;
      case WKP_UDP_DISCARD:
         appudpprint_receive(msg);
         break;
      case WKP_UDP_SENSOR:
         appudpsensor_receive(msg);
         break;
      default:
         openserial_printError(COMPONENT_UDP,ERR_UNSUPPORTED_PORT_NUMBER,msg->l4_destination_port,1);
         openqueue_freePacketBuffer(msg);         
   }
}

bool udp_debugPrint() {
   return FALSE;
}