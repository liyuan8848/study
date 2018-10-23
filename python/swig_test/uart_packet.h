#ifndef UART_PACKET_H_
#define UART_PACKET_H_

#include <stdlib.h>
#include <stdint.h>

#define TIMESTAMP_SIZE_B 8
#define GPS_DATA_LENGTH_B 28
#define DATA_RATE_LENGTH_B 2
#define NBR_PAA_TEMPERATURES 64
#define VER_INFO_SIZE_B 64

#define TYPEDEF_PACKET(NAME)     \
    typedef struct {             \
        UartPacketHeader header; \
        NAME##Data data;         \
    } __attribute__((__packed__)) NAME

typedef enum {
    UART_PACKET_TYPE_START_VALUE,
    POWER_AND_ENERGY = UART_PACKET_TYPE_START_VALUE,
    TEMPERATURE,
    GPS,
    DATARATE,
    PAA_TEMPERATURE,

    IDL_REQUEST = 5,
    STD_REQUEST = 6,
    ATX_REQUEST = 7,
    ARX_REQUEST = 8,
    VER_REQUEST = 9,
    FLT_REQUEST = 10,
    OFF_REQUEST = 11,

    PACKET_ERROR_RATE,
    PACKETS_PER_SECOND,

    IDL_ACK,
    STD_ACK,
    ATX_ACK,
    ARX_ACK,
    VER_ACK,
    FLT_ACK,
    OFF_ACK,

    IDL_STE,
    STD_STE,
    ACT_STE,

    INVALID,
    UART_PACKET_TYPE_END_VALUE = INVALID
} UartPacketType;

// PAA power supply temperature
typedef struct {
    uint8_t t0;
    uint8_t t1;
} __attribute__((__packed__)) PAAPsT;

typedef struct {
    UartPacketType type;
    uint8_t timestamp[TIMESTAMP_SIZE_B];
} __attribute__((__packed__)) UartPacketHeader;

typedef struct {
    uint8_t returnCode;
} __attribute__((__packed__)) IDLAckPacketData;

typedef struct {
    uint8_t returnCode;
} __attribute__((__packed__)) STDAckPacketData;

typedef struct {
    uint8_t returnCode;
} __attribute__((__packed__)) ATXAckPacketData;

typedef struct {
    uint8_t returnCode;
} __attribute__((__packed__)) ARXAckPacketData;

typedef struct {
    uint8_t returnCode;
    uint8_t type;
    uint8_t verInfo[VER_INFO_SIZE_B];
} __attribute__((__packed__)) VERAckPacketData;

typedef struct {
    uint8_t returnCode;
} __attribute__((__packed__)) FLTAckPacketData;

typedef struct {
    uint8_t returnCode;
} __attribute__((__packed__)) OFFAckPacketData;


typedef struct {
    uint8_t device  : 4,
            channel : 4;
} __attribute__((__packed__)) STDStePacketData;

typedef struct {
    uint8_t mode    : 4,
            channel : 4;
} __attribute__((__packed__)) ACTStePacketData;

typedef struct {
    uint8_t device  : 4,
            channel : 4;
} __attribute__((__packed__)) STDRequestPacketData;

typedef struct {
    uint8_t mcs     : 4,
            channel : 4;
    uint8_t tx_eirp;
} __attribute__((__packed__)) ATXRequestPacketData;

typedef struct {
    uint8_t mcs         : 4,
            channel     : 4;
    uint8_t manual_auto : 1,
            rx_gain     : 7;
} __attribute__((__packed__)) ARXRequestPacketData;

typedef struct {
    uint8_t   type;
} __attribute__((__packed__)) VERRequestPacketData;

typedef struct {
    uint8_t   fault;
} __attribute__((__packed__)) FLTRequestPacketData;

typedef struct {
    uint8_t drf26;
    uint8_t drf38;
    uint8_t fem26;
    uint8_t fem38;
    PAAPsT paa26Ps;
    PAAPsT paa38Ps;
    uint8_t bpu;
} __attribute__((__packed__)) TemperaturePacketData;

typedef struct {
    uint8_t per;
} __attribute__((__packed__)) PerPacketData;

typedef struct {
    uint16_t pps;
} __attribute__((__packed__)) PpsPacketData;


typedef struct {
    /* union power { */
    /*     uint16_t value; */
    /*     struct { */
    /*         uint8_t mantissa; */
    /*         uint8_t exponent; */
    /*     } __attribute__((__packed__)) s; */
    /* }__attribute__((__packed__)) power; */
    /*  */
    /* union energy { */
    /*     uint16_t value; */
    /*     struct { */
    /*         uint8_t mantissa_msb; */
    /*         uint8_t mantissa_lsb; */
    /*         uint8_t exponent; */
    /*     } __attribute__((__packed__)) s; */
    /* } __attribute__((__packed__)) energy; */
    float power;
    float energy;

} __attribute__((__packed__)) PowerAndEnergyPacketData;

typedef struct {
    uint8_t gps[GPS_DATA_LENGTH_B];
} __attribute__((__packed__)) GpsPacketData;

typedef struct {
    uint8_t uplink[DATA_RATE_LENGTH_B];
    uint8_t downlink[DATA_RATE_LENGTH_B];
} __attribute__((__packed__)) DataRatePacketData;

typedef struct {
    uint8_t paa26[NBR_PAA_TEMPERATURES];
    uint8_t paa38[NBR_PAA_TEMPERATURES];
} __attribute__((__packed__)) PAATemperaturePacketData;


TYPEDEF_PACKET(PowerAndEnergyPacket);
TYPEDEF_PACKET(TemperaturePacket);
TYPEDEF_PACKET(GpsPacket);
TYPEDEF_PACKET(DataRatePacket);
TYPEDEF_PACKET(PAATemperaturePacket);
TYPEDEF_PACKET(PerPacket);
TYPEDEF_PACKET(PpsPacket);

typedef struct {
    UartPacketHeader header;
} __attribute__((__packed__)) IDLRequestPacket;

typedef struct {
    UartPacketHeader header;
} __attribute__((__packed__)) OFFRequestPacket;

TYPEDEF_PACKET(STDRequestPacket);
TYPEDEF_PACKET(ATXRequestPacket);
TYPEDEF_PACKET(ARXRequestPacket);
TYPEDEF_PACKET(VERRequestPacket);
TYPEDEF_PACKET(FLTRequestPacket);
TYPEDEF_PACKET(IDLAckPacket);
TYPEDEF_PACKET(STDAckPacket);
TYPEDEF_PACKET(ATXAckPacket);
TYPEDEF_PACKET(ARXAckPacket);
TYPEDEF_PACKET(VERAckPacket);
TYPEDEF_PACKET(FLTAckPacket);
TYPEDEF_PACKET(OFFAckPacket);

typedef struct {
    UartPacketHeader header;
} __attribute__((__packed__)) IDLStePacket;

TYPEDEF_PACKET(STDStePacket);
TYPEDEF_PACKET(ACTStePacket);

size_t UartPacket_getSize(UartPacketType t);
size_t UartPacket_getMaxPacketSize(void);
void UartPacket_initPowerAndEnergyPacket(PowerAndEnergyPacket *const p);
void UartPacket_initTemperaturePacket(TemperaturePacket *const p);
void UartPacket_initGpsPacket(GpsPacket *const p);
void UartPacket_initDataRatePacket(DataRatePacket *const p);
void UartPacket_initPAATemperaturePacket(PAATemperaturePacket *const p);

void UartPacket_initSTDRequestPacket(STDRequestPacket *const p);
void UartPacket_initATXRequestPacket(ATXRequestPacket *const p);
void UartPacket_initARXRequestPacket(ARXRequestPacket *const p);
void UartPacket_initVERRequestPacket(VERRequestPacket *const p);
void UartPacket_initIDLRequestPacket(IDLRequestPacket *const p);
void UartPacket_initFLTRequestPacket(FLTRequestPacket *const p);
void UartPacket_initOFFRequestPacket(OFFRequestPacket *const p);

#endif
