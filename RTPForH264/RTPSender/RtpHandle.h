#pragma once
#include <winsock2.h>
#include "H264Handle.h"

typedef struct 
{
    /* byte 0 */
    unsigned char csrc_len:4;        /* expect 0 */
    unsigned char extension:1;       /* expect 1, see RTP_OP below */
    unsigned char padding:1;         /* expect 0 */
    unsigned char version:2;         /* expect 2 */
    /* byte 1 */
    unsigned char payload:7;         /* RTP_PAYLOAD_RTSP */
    unsigned char marker:1;          /* expect 1 */
    /* bytes 2,3 */
    unsigned short seq_no;            
    /* bytes 4-7 */
    unsigned  long timestamp;        
    /* bytes 8-11 */
    unsigned long ssrc;              /* stream number is used here. */
} RTP_FIXED_HEADER;

typedef struct {
    //byte 0
	unsigned char TYPE:5;
    unsigned char NRI:2;
	unsigned char F:1;        
} NALU_HEADER; /* 1 BYTE */

typedef struct {
    //byte 0
    unsigned char TYPE:5;
	unsigned char NRI:2; 
	unsigned char F:1;              
} FU_INDICATOR; /* 1 BYTE */

typedef struct {
    //byte 0
    unsigned char TYPE:5;
	unsigned char R:1;
	unsigned char E:1;
	unsigned char S:1;    
} FU_HEADER;   /* 1 BYTES */

#define H264                   96

class CRtpHandle
{
public:
	CRtpHandle(void);
	~CRtpHandle(void);

	BOOL InitiateWinsock();
	BOOL Connet(char* ip, int port);
	BOOL PacketSend(NALU_t *n, float framerate);

	static unsigned short seq_num;
private:

	SOCKET    socket1;
	struct sockaddr_in server;
	char sendbuf[1500];
	
	unsigned int ts_current;
	unsigned int timestamp_increse;
	int total_bytes;
	int total_sent;
};

