/**********************************************************************
 *                                                                    *
 *  Copyright 20018-present Facebook, Inc. All Rights Reserved.       *
 *                                                                    *
 **********************************************************************/

/** @file
 *  @brief
 * this program handle configuration of vectorNav VN300 and BinaryAsyncMessage
 * read from VN300
 *
 *  @author Yuan Li
 *  @email yuali@fb.com, yuan.li@esenciatech.com
 *
 */

#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <errno.h>
#include <netlink/errno.h>
#include <net/if.h>
#include <netlink/cli/utils.h>

#define BWT_OUI 0x681f40
#define BH2_SET_LOCATION_INFORMATION 0x28
#define BH2_GET_LOCATION_INFORMATION 0x29

#define NL80211_CMD_VENDOR 103

#define NL80211_ATTR_IFINDEX 3

// Generic netlink protocol versions
#define GNL_FAMILY_VERSION 1
#define NL80211_VERSION 0

// Generic Netlink attribute IDs for NL80211 commands

#define NL80211_ATTR_VENDOR_ID 195
#define NL80211_ATTR_VENDOR_SUBCMD 196
#define NL80211_ATTR_VENDOR_DATA 197

struct
{ //memory for netlink request and response messages - headers are included
    struct nlmsghdr n;
    struct genlmsghdr g;
    char data_buf[256];
} nl_request_msg, nl_response_msg;

struct sockaddr_nl nl_address; //netlink socket address
int nl_rxtx_length;            //Number of bytes sent or received via send() or recv()
struct nlattr *nl_na;          //pointer to netlink attributes structure within the payload

unsigned int FloatToUint(float n);
float UintToFloat(unsigned int n);

unsigned int DoubleToUint(double n);
double UintToDouble(unsigned int n);

unsigned int longlongToUint(long long int n);
long long int UintTolonglong(unsigned int n);

extern int genl_ctrl_resolve(struct nl_sock *sk, const char *name);

int setLoc();
int getLoc();

static int parse_cb(struct nl_msg *msg, void *arg);


static int parse_cb(struct nl_msg *msg, void *arg)
{
    printf("nl callback \n");
    unsigned int *latitude;
    unsigned int *longitude;
    unsigned int *altitude;
    unsigned int *roll;
    unsigned int *pitch;
    unsigned int *yaw;
    unsigned int *timestamp;

    struct genlmsghdr *ghdr;

    struct nlmsghdr *nlh = nlmsg_hdr(msg);
    struct genl_ops *ops;

    ghdr = genlmsg_hdr(nlh);

    printf("gnl len %d\n", genlmsg_len(ghdr));

    char *hdr = (char *)genlmsg_user_hdr(ghdr);
    char *data = (char *)genlmsg_user_data(ghdr, 0);

    /* hdlr len will 12 bytes
    * each attritbute will take 4 bytes
    * we have  3 attribute = 3*4 = 12 bytes
    * then we have following data len of 28 bytes
    */
    //    latitude = data[15];
    //    latitude <<= 8;
    //    latitude |= data[14];
    //    latitude <<= 8;
    //    latitude |= data[13];
    //    latitude <<= 8;
    //    latitude |= data[12];

    //    longitude = data[19];
    //    longitude <<= 8;
    //    longitude |= data[18];
    //    longitude <<= 8;
    //    longitude |= data[17];
    //    longitude <<= 8;
    //    longitude |= data[16];

    latitude = &data[12];
    longitude = &data[16];
    altitude = &data[20];
    roll = &data[24];
    pitch = &data[28];
    yaw = &data[32];
    timestamp = &data[36];

    printf("lat %f lon %f alt %f, rol %f, pitch %f, yaw %f, timestamp %lu \n", UintToFloat(*latitude), UintToFloat(*longitude), UintToFloat(*altitude), UintToFloat(*roll), UintToFloat(*pitch), UintToFloat(*yaw), UintTolonglong(*timestamp));

    //nlmsg_free(msg);

    return 0;
}

int test = 0;
int setLoc()
{

  struct nl_msg *msg;

    float latitude;
    float longitude;
    float altitude;
    float roll;
    float pitch;
    float yaw;
    long long unsigned int timestamp;

    unsigned int u32buf[7] = {};

    char u8buf[28] = {};

    latitude = 37.77+test;
    longitude = 122.3478+test;
    altitude = -29.48;
    roll = 0.123;
    pitch = 0.3678;
    yaw = 0.04231;
    timestamp = 1+test;

    test++;

    u32buf[0] = FloatToUint(latitude);
    u32buf[1] = FloatToUint(longitude);
    u32buf[2] = FloatToUint(altitude);
    u32buf[3] = FloatToUint(roll);
    u32buf[4] = FloatToUint(pitch);
    u32buf[5] = FloatToUint(yaw);
    u32buf[6] = longlongToUint(timestamp);

    // latitude = 34;
    // longitude = 1222;
    // altitude = 21;
    // roll = 23;
    // pitch = 3;
    // yaw = 1;
    // timestamp = 492132132;

    // latitude = 0;
    // longitude = 0;
    // altitude = 0;
    // roll = 0;
    // pitch = 0;
    // yaw = 0;
    // timestamp = 0;

    u8buf[0] = (unsigned char)(u32buf[0] >> 24) & 0x000000ff;
    u8buf[1] = (unsigned char)(u32buf[0] >> 16) & 0x000000ff;
    u8buf[2] = (unsigned char)(u32buf[0] >> 8) & 0x000000ff;
    u8buf[3] = (unsigned char)(u32buf[0]) & 0x000000ff;

    u8buf[4] = (unsigned char)(u32buf[1] >> 24) & 0x000000ff;
    u8buf[5] = (unsigned char)(u32buf[1] >> 16) & 0x000000ff;
    u8buf[6] = (unsigned char)(u32buf[1] >> 8) & 0x000000ff;
    u8buf[7] = (unsigned char)(u32buf[1]) & 0x000000ff;

    u8buf[8] = (unsigned char)(u32buf[2] >> 24) & 0x000000ff;
    u8buf[9] = (unsigned char)(u32buf[2] >> 16) & 0x000000ff;
    u8buf[10] = (unsigned char)(u32buf[2] >> 8) & 0x000000ff;
    u8buf[11] = (unsigned char)(u32buf[2]) & 0x000000ff;

    u8buf[12] = (unsigned char)(u32buf[3] >> 24) & 0x000000ff;
    u8buf[13] = (unsigned char)(u32buf[3] >> 16) & 0x000000ff;
    u8buf[14] = (unsigned char)(u32buf[3] >> 8) & 0x000000ff;
    u8buf[15] = (unsigned char)(u32buf[3]) & 0x000000ff;

    u8buf[16] = (unsigned char)(u32buf[4] >> 24) & 0x000000ff;
    u8buf[17] = (unsigned char)(u32buf[4] >> 16) & 0x000000ff;
    u8buf[18] = (unsigned char)(u32buf[4] >> 8) & 0x000000ff;
    u8buf[19] = (unsigned char)(u32buf[4]) & 0x000000ff;

    u8buf[20] = (unsigned char)(u32buf[5] >> 24) & 0x000000ff;
    u8buf[21] = (unsigned char)(u32buf[5] >> 16) & 0x000000ff;
    u8buf[22] = (unsigned char)(u32buf[5] >> 8) & 0x000000ff;
    u8buf[23] = (unsigned char)(u32buf[5]) & 0x000000ff;

    u8buf[24] = (unsigned char)(u32buf[6] >> 24) & 0x000000ff;
    u8buf[25] = (unsigned char)(u32buf[6] >> 16) & 0x000000ff;
    u8buf[26] = (unsigned char)(u32buf[6] >> 8) & 0x000000ff;
    u8buf[27] = (unsigned char)(u32buf[6]) & 0x000000ff;

    //for (int i =0; i< 28; i++){
    //   printf("%d. %d\n", i, u8buf[i]);
    //}

    printf("lat %lf lon %lf alt %lf, rol %f, pitch %f, yaw %f, timestamp %lu \n", latitude, longitude, altitude, roll, pitch, yaw, timestamp);
    struct nl_sock *nlsock = nl_socket_alloc();

    printf("size of u8buf is %d \n", sizeof(u8buf));

    if (!nlsock)
    {

        fprintf(stderr, "Unable to alloc nl socket! \n");
        exit(-1);
    }

    // Allocate the messages and callback handler.
    msg = nlmsg_alloc();
    if (!msg)
    {
        fprintf(stderr, "ERROR: Failed to allocate netlink message for msg.\n");
        return -ENOMEM;
    }

    int if_index = if_nametoindex("wlan1"); // Use BLue wireless interface
    int family_id;

    /* disable seq checks on multicast sockets */
    nl_socket_disable_msg_peek(nlsock);
    nl_socket_disable_auto_ack(nlsock);

    /* connect to genetlink */

    if (genl_connect(nlsock))
    {

        fprintf(stderr, "Unable to connect to genetlink! \n");
        exit(-1);
    }

    family_id = genl_ctrl_resolve(nlsock, "nl80211");

    printf("family id is %d \n", family_id);

    if (!genlmsg_put(msg, NL_AUTO_PID, NL_AUTO_SEQ, family_id, 0,
                     0, NL80211_CMD_VENDOR, NL80211_VERSION))
    {
        fprintf(stderr, "failed to put nl hdr! msg \n");
        return -ENOMEM;
    }

    NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, if_index);
    NLA_PUT_U32(msg, NL80211_ATTR_VENDOR_ID, BWT_OUI);
    NLA_PUT_U32(msg, NL80211_ATTR_VENDOR_SUBCMD, BH2_SET_LOCATION_INFORMATION);

    NLA_PUT(msg, NL80211_ATTR_VENDOR_DATA, sizeof(unsigned int) * 7, u8buf);

    int err = nl_send_auto(nlsock, msg);
    if (err < 0)
    {
        fprintf(stderr, "failed to send nl message msg!\n");
    }

    nlmsg_free(msg);
    nl_close(nlsock);
	nl_socket_free(nlsock);

  nla_put_failure:

    //return -NLE_MSGSIZE;
    return 0;

}

int getLoc()
{
    
    struct nl_msg *msg2;

    struct nl_sock *nlsock = nl_socket_alloc();

    int err;

    if (!nlsock)
    {

        fprintf(stderr, "Unable to alloc nl socket! \n");
        exit(-1);
    }
    
    int if_index = if_nametoindex("wlan1"); // Use BLue wireless interface
    int family_id;

    /* disable seq checks on multicast sockets */
    nl_socket_disable_msg_peek(nlsock);
    nl_socket_disable_auto_ack(nlsock);

    /* connect to genetlink */

    if (genl_connect(nlsock))
    {

        fprintf(stderr, "Unable to connect to genetlink! \n");
        exit(-1);
    }

    family_id = genl_ctrl_resolve(nlsock, "nl80211");

    printf("family id is %d \n", family_id);
    /****************************************************************************/
    // Allocate the messages and callback handler.
    msg2 = nlmsg_alloc();
    if (!msg2)
    {
        fprintf(stderr, "ERROR: Failed to allocate netlink message for msg2.\n");
        return -ENOMEM;
    }

    if (!genlmsg_put(msg2, NL_AUTO_PID, NL_AUTO_SEQ, family_id, 0,
                     0, NL80211_CMD_VENDOR, NL80211_VERSION))
    {
        fprintf(stderr, "msg2 failed to put nl hdr!\n");
        return -ENOMEM;
    }

    NLA_PUT_U32(msg2, NL80211_ATTR_IFINDEX, if_index);
    NLA_PUT_U32(msg2, NL80211_ATTR_VENDOR_ID, BWT_OUI);
    NLA_PUT_U32(msg2, NL80211_ATTR_VENDOR_SUBCMD, BH2_GET_LOCATION_INFORMATION);
    NLA_PUT_U8(msg2, NL80211_ATTR_VENDOR_DATA, 0x01); // binary or text


    if ((err = nl_send_auto_complete(nlsock, msg2)) < 0)
        fprintf(stderr, "Unable to send message: %s", nl_geterror(err));

    // printf("wait for ack\n");
    // //nl_wait_for_ack(nlsock);
    // printf("ack recv\n");

    if ((err = nl_socket_modify_cb(nlsock, NL_CB_VALID, NL_CB_CUSTOM,
                                   parse_cb, NULL)) < 0)
        fprintf(stderr, "Unable to modify valid message callback");

    if ((err = nl_recvmsgs_default(nlsock)) < 0)
        fprintf(stderr, "Unable to receive message: %s", nl_geterror(err));

    printf("END -----------\n");
    nlmsg_free(msg2);
    nl_close(nlsock);
	nl_socket_free(nlsock);


nla_put_failure:

    //return -NLE_MSGSIZE;
    return 0;
}

int main(int argc, char **argv)
{
    while(1){

    
   setLoc();
   getLoc();
   
    }
  return 0;

}

unsigned int FloatToUint(float n)
{
    return (unsigned int)(*(unsigned int *)&n);
}

float UintToFloat(unsigned int n)
{
    return (float)(*(float *)&n);
}

unsigned int DoubleToUint(double n)
{
    return (unsigned int)(*(unsigned int *)&n);
}

double UintToDouble(unsigned int n)
{
    return (double)(*(double *)&n);
}

unsigned int longlongToUint(long long int n)
{
    return (unsigned int)(*(unsigned int *)&n);
}

long long int UintTolonglong(unsigned int n)
{
    return (long long int)(*(long long int *)&n);
}
