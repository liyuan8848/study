#include <stdint.h>
#include <stdlib.h>

#include "uart_packet.h"

static void initPacket(void*, UartPacketType);


size_t UartPacket_getSize(UartPacketType t) {
    size_t size;

    switch(t) {
        case POWER_AND_ENERGY:
            size = sizeof(PowerAndEnergyPacket);
            break;
        case TEMPERATURE:
            size = sizeof(TemperaturePacket);
            break;
        case GPS:
            size = sizeof(GpsPacket);
            break;
        case DATARATE:
            size = sizeof(DataRatePacket);
            break;
        case PAA_TEMPERATURE:
            size = sizeof(PAATemperaturePacket);
            break;
        case IDL_ACK:
            size = sizeof(IDLAckPacket);
            break;
        case VER_ACK:
            size = sizeof(VERAckPacket);
            break;
        case IDL_STE:
            size = sizeof(IDLStePacket);
            break;
        case STD_STE:
            size = sizeof(STDStePacket);
            break;
        case ACT_STE:
            size = sizeof(ACTStePacket);
            break;
        case IDL_REQUEST:
            size = sizeof(IDLRequestPacket);
            break;
        case STD_REQUEST:
            size = sizeof(STDRequestPacket);
            break;
        case ATX_REQUEST:
            size = sizeof(ATXRequestPacket);
            break;
        case ARX_REQUEST:
            size = sizeof(ARXRequestPacket);
            break;
        case VER_REQUEST:
            size = sizeof(VERRequestPacket);
            break;
        case FLT_REQUEST:
            size = sizeof(FLTRequestPacket);
            break;
        case OFF_REQUEST:
            size = sizeof(OFFRequestPacket);
            break;
        default:
            size = 0;
    }

    return size;
}

size_t UartPacket_getMaxPacketSize(void) {
    unsigned i;
    size_t maxSize = 0,
           packetSize;

    for (i = UART_PACKET_TYPE_START_VALUE; i < UART_PACKET_TYPE_END_VALUE; i++) {
        packetSize = UartPacket_getSize((UartPacketType)i);
        if (packetSize > maxSize)
            maxSize = packetSize;
    }

    return packetSize;

}

void UartPacket_initPowerAndEnergyPacket(PowerAndEnergyPacket *const p) {
    initPacket(p, POWER_AND_ENERGY);
}

void UartPacket_initTemperaturePacket(TemperaturePacket *const p) {
    initPacket(p, TEMPERATURE);
}

void UartPacket_initGpsPacket(GpsPacket *const p) {
    initPacket(p, GPS);
}

void UartPacket_initDataRatePacket(DataRatePacket *const p) {
    initPacket(p, DATARATE);
}

void UartPacket_initPAATemperaturePacket(PAATemperaturePacket *const p) {
    initPacket(p, PAA_TEMPERATURE);
}

void UartPacket_initSTDRequestPacket(STDRequestPacket *const p) {
    initPacket(p, STD_REQUEST);
}

void UartPacket_initATXRequestPacket(ATXRequestPacket *const p) {
    initPacket(p, ATX_REQUEST);
}

void UartPacket_initARXRequestPacket(ARXRequestPacket *const p) {
    initPacket(p, ARX_REQUEST);
}

void UartPacket_initVERRequestPacket(VERRequestPacket *const p) {
    initPacket(p, VER_REQUEST);
}

void UartPacket_initFLTRequestPacket(FLTRequestPacket *const p) {
    initPacket(p, FLT_REQUEST);
}

void UartPacket_initIDLRequestPacket(IDLRequestPacket *const p) {
    initPacket(p, IDL_REQUEST);
}

void UartPacket_initOFFRequestPacket(OFFRequestPacket *const p) {
    initPacket(p, OFF_REQUEST);
}

static void initPacket(void *p, UartPacketType type) {
    UartPacketHeader *h = (UartPacketHeader *)p;
    h->type = type;
}
