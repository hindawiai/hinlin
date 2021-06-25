<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/************************************************************************
 *
 *	IONSP.H		Definitions क्रम I/O Networks Serial Protocol
 *
 *	Copyright (C) 1997-1998 Inside Out Networks, Inc.
 *
 *	These definitions are used by both kernel-mode driver and the
 *	peripheral firmware and MUST be kept in sync.
 *
 ************************************************************************/

/************************************************************************

The data to and from all ports on the peripheral is multiplexed
through a single endpoपूर्णांक pair (EP1 since it supports 64-byte
MaxPacketSize). Thereक्रमe, the data, commands, and status क्रम
each port must be preceded by a लघु header identअगरying the
destination port. The header also identअगरies the bytes that follow
as data or as command/status info.

Header क्रमmat, first byte:

    CLLLLPPP
    --------
    | |	 |------ Port Number:	0-7
    | |--------- Length:	MSB bits of length
    |----------- Data/Command:	0 = Data header
				1 = Cmd / Status (Cmd अगर OUT, Status अगर IN)

This gives 2 possible क्रमmats:


    Data header:		0LLLLPPP	LLLLLLLL
    ============

    Where (LLLL,LLLLLLL) is 12-bit length of data that follows क्रम
    port number (PPP). The length is 0-based (0-FFF means 0-4095
    bytes). The ~4K limit allows the host driver (which deals in
    transfer requests instead of inभागidual packets) to ग_लिखो a
    large chunk of data in a single request. Note, however, that
    the length must always be <= the current TxCredits क्रम a given
    port due to buffering limitations on the peripheral.


    Cmd/Status header:		1ccccPPP	[ CCCCCCCC,	 Params ]...
    ==================

    Where (cccc) or (cccc,CCCCCCCC) is the cmd or status identअगरier.
    Frequently-used values are encoded as (cccc), दीर्घer ones using
    (cccc,CCCCCCCC). Subsequent bytes are optional parameters and are
    specअगरic to the cmd or status code. This may include a length
    क्रम command and status codes that need variable-length parameters.


In addition, we use another पूर्णांकerrupt pipe (endpoपूर्णांक) which the host polls
periodically क्रम flow control inक्रमmation. The peripheral, when there has
been a change, sends the following 10-byte packet:

	RRRRRRRRRRRRRRRR
	T0T0T0T0T0T0T0T0
	T1T1T1T1T1T1T1T1
	T2T2T2T2T2T2T2T2
	T3T3T3T3T3T3T3T3

The first field is the 16-bit RxBytesAvail field, which indicates the
number of bytes which may be पढ़ो by the host from EP1. This is necessary:
(a) because OSR2.1 has a bug which causes data loss अगर the peripheral वापसs
fewer bytes than the host expects to पढ़ो, and (b) because, on Microsoft
platक्रमms at least, an outstanding पढ़ो posted on EP1 consumes about 35% of
the CPU just polling the device क्रम data.

The next 4 fields are the 16-bit TxCredits क्रम each port, which indicate how
many bytes the host is allowed to send on EP1 क्रम transmit to a given port.
After an OPEN_PORT command, the Edgeport sends the initial TxCredits क्रम that
port.

All 16-bit fields are sent in little-endian (Intel) क्रमmat.

************************************************************************/

//
// Define क्रमmat of InterruptStatus packet वापसed from the
// Interrupt pipe
//

काष्ठा पूर्णांक_status_pkt अणु
	__u16 RxBytesAvail;			// Additional bytes available to
						// be पढ़ो from Bulk IN pipe
	__u16 TxCredits[MAX_RS232_PORTS];	// Additional space available in
						// given port's TxBuffer
पूर्ण;


#घोषणा GET_INT_STATUS_SIZE(NumPorts) (माप(__u16) + (माप(__u16) * (NumPorts)))



//
// Define cmd/status header values and macros to extract them.
//
//	Data:		0LLLLPPP LLLLLLLL
//	Cmd/Stat:	1ccccPPP CCCCCCCC

#घोषणा	IOSP_DATA_HDR_SIZE		2
#घोषणा	IOSP_CMD_HDR_SIZE		2

#घोषणा	IOSP_MAX_DATA_LENGTH		0x0FFF		// 12 bits -> 4K

#घोषणा	IOSP_PORT_MASK			0x07		// Mask to isolate port number
#घोषणा	IOSP_CMD_STAT_BIT		0x80		// If set, this is command/status header

#घोषणा IS_CMD_STAT_HDR(Byte1)		((Byte1) & IOSP_CMD_STAT_BIT)
#घोषणा IS_DATA_HDR(Byte1)		(!IS_CMD_STAT_HDR(Byte1))

#घोषणा	IOSP_GET_HDR_PORT(Byte1)		((__u8) ((Byte1) & IOSP_PORT_MASK))
#घोषणा	IOSP_GET_HDR_DATA_LEN(Byte1, Byte2)	((__u16) (((__u16)((Byte1) & 0x78)) << 5) | (Byte2))
#घोषणा	IOSP_GET_STATUS_CODE(Byte1)		((__u8) (((Byte1) &  0x78) >> 3))


//
// These macros build the 1st and 2nd bytes क्रम a data header
//
#घोषणा	IOSP_BUILD_DATA_HDR1(Port, Len)		((__u8) (((Port) | ((__u8) (((__u16) (Len)) >> 5) & 0x78))))
#घोषणा	IOSP_BUILD_DATA_HDR2(Port, Len)		((__u8) (Len))


//
// These macros build the 1st and 2nd bytes क्रम a command header
//
#घोषणा	IOSP_BUILD_CMD_HDR1(Port, Cmd)		((__u8) (IOSP_CMD_STAT_BIT | (Port) | ((__u8) ((Cmd) << 3))))


//--------------------------------------------------------------
//
//	Define values क्रम commands and command parameters
//	(sent from Host to Edgeport)
//
//	1ccccPPP P1P1P1P1 [ P2P2P2P2P2 ]...
//
//	cccc:	00-07	2-byte commands. Write UART रेजिस्टर 0-7 with
//					value in P1. See 16650.H क्रम definitions of
//					UART रेजिस्टर numbers and contents.
//
//		08-0B	3-byte commands:					==== P1 ====	==== P2 ====
//					08	available क्रम expansion
//					09	1-param commands		Command Code	Param
//					0A	available क्रम expansion
//					0B	available क्रम expansion
//
//		0C-0D	4-byte commands.	P1 = extended cmd and P2,P3 = params
//						Currently unimplemented.
//
//		0E-0F	N-byte commands:	P1 = num bytes after P1 (ie, TotalLen - 2)
//						P2 = extended cmd, P3..Pn = parameters.
//						Currently unimplemented.
//

#घोषणा	IOSP_WRITE_UART_REG(n)	((n) & 0x07)	// UartReg[ n ] := P1

// Register numbers and contents
// defined in 16554.H.

//					0x08		// Available क्रम expansion.
#घोषणा	IOSP_EXT_CMD			0x09		// P1 = Command code (defined below)

// P2 = Parameter

//
// Extended Command values, used with IOSP_EXT_CMD, may
// or may not use parameter P2.
//

#घोषणा	IOSP_CMD_OPEN_PORT		0x00		// Enable पूर्णांकs, init UART. (NO PARAM)
#घोषणा	IOSP_CMD_CLOSE_PORT		0x01		// Disable पूर्णांकs, flush buffers. (NO PARAM)
#घोषणा	IOSP_CMD_CHASE_PORT		0x02		// Wait क्रम Edgeport TX buffers to empty. (NO PARAM)
#घोषणा IOSP_CMD_SET_RX_FLOW		0x03		// Set Rx Flow Control in Edgeport
#घोषणा IOSP_CMD_SET_TX_FLOW		0x04		// Set Tx Flow Control in Edgeport
#घोषणा IOSP_CMD_SET_XON_CHAR		0x05		// Set XON Character in Edgeport
#घोषणा IOSP_CMD_SET_XOFF_CHAR		0x06		// Set XOFF Character in Edgeport
#घोषणा IOSP_CMD_RX_CHECK_REQ		0x07		// Request Edgeport to insert a Checkpoपूर्णांक पूर्णांकo

// the receive data stream (Parameter = 1 byte sequence number)

#घोषणा IOSP_CMD_SET_BREAK		0x08		// Turn on the BREAK (LCR bit 6)
#घोषणा IOSP_CMD_CLEAR_BREAK		0x09		// Turn off the BREAK (LCR bit 6)


//
// Define macros to simplअगरy building of IOSP cmds
//

#घोषणा MAKE_CMD_WRITE_REG(ppBuf, pLen, Port, Reg, Val)			\
करो अणु									\
	(*(ppBuf))[0] = IOSP_BUILD_CMD_HDR1((Port),			\
					    IOSP_WRITE_UART_REG(Reg));	\
	(*(ppBuf))[1] = (Val);						\
									\
	*ppBuf += 2;							\
	*pLen  += 2;							\
पूर्ण जबतक (0)

#घोषणा MAKE_CMD_EXT_CMD(ppBuf, pLen, Port, ExtCmd, Param)		\
करो अणु									\
	(*(ppBuf))[0] = IOSP_BUILD_CMD_HDR1((Port), IOSP_EXT_CMD);	\
	(*(ppBuf))[1] = (ExtCmd);					\
	(*(ppBuf))[2] = (Param);					\
									\
	*ppBuf += 3;							\
	*pLen  += 3;							\
पूर्ण जबतक (0)



//--------------------------------------------------------------
//
//	Define क्रमmat of flow control commands
//	(sent from Host to Edgeport)
//
//	11001PPP FlowCmd FlowTypes
//
//	Note that the 'FlowTypes' parameter is a bit mask; that is,
//	more than one flow control type can be active at the same समय.
//	FlowTypes = 0 means 'no flow control'.
//

//
//	IOSP_CMD_SET_RX_FLOW
//
//	Tells Edgeport how it can stop incoming UART data
//
//  Example क्रम Port 0
//	P0 = 11001000
//  P1 = IOSP_CMD_SET_RX_FLOW
//  P2 = Bit mask as follows:

#घोषणा IOSP_RX_FLOW_RTS		0x01	// Edgeport drops RTS to stop incoming data
#घोषणा IOSP_RX_FLOW_DTR		0x02	// Edgeport drops DTR to stop incoming data
#घोषणा IOSP_RX_FLOW_DSR_SENSITIVITY	0x04	// Ignores Rx data unless DSR high

// Not currently implemented by firmware.
#घोषणा IOSP_RX_FLOW_XON_XOFF		0x08	// Edgeport sends XOFF अक्षर to stop incoming data.

// Host must have previously programmed the
// XON/XOFF values with SET_XON/SET_XOFF
// beक्रमe enabling this bit.

//
//	IOSP_CMD_SET_TX_FLOW
//
//	Tells Edgeport what संकेत(s) will stop it from transmitting UART data
//
//  Example क्रम Port 0
//	P0 = 11001000
//  P1 = IOSP_CMD_SET_TX_FLOW
//  P2 = Bit mask as follows:

#घोषणा IOSP_TX_FLOW_CTS		0x01	// Edgeport stops Tx अगर CTS low
#घोषणा IOSP_TX_FLOW_DSR		0x02	// Edgeport stops Tx अगर DSR low
#घोषणा IOSP_TX_FLOW_DCD		0x04	// Edgeport stops Tx अगर DCD low
#घोषणा IOSP_TX_FLOW_XON_XOFF		0x08	// Edgeport stops Tx upon receiving XOFF अक्षर.

// Host must have previously programmed the
// XON/XOFF values with SET_XON/SET_XOFF
// beक्रमe enabling this bit.
#घोषणा IOSP_TX_FLOW_XOFF_CONTINUE	0x10	// If not set, Edgeport stops Tx when

// sending XOFF in order to fix broken
// प्रणालीs that पूर्णांकerpret the next
// received अक्षर as XON.
// If set, Edgeport जारीs Tx
// normally after transmitting XOFF.
// Not currently implemented by firmware.
#घोषणा IOSP_TX_TOGGLE_RTS		0x20	// Edgeport drives RTS as a true half-duplex

// Request-to-Send संकेत: it is उठाओd beक्रमe
// beginning transmission and lowered after
// the last Tx अक्षर leaves the UART.
// Not currently implemented by firmware.

//
//	IOSP_CMD_SET_XON_CHAR
//
//	Sets the अक्षरacter which Edgeport transmits/पूर्णांकerprets as XON.
//	Note: This command MUST be sent beक्रमe sending a SET_RX_FLOW or
//	SET_TX_FLOW with the XON_XOFF bit set.
//
//  Example क्रम Port 0
//	P0 = 11001000
//  P1 = IOSP_CMD_SET_XON_CHAR
//  P2 = 0x11


//
//	IOSP_CMD_SET_XOFF_CHAR
//
//	Sets the अक्षरacter which Edgeport transmits/पूर्णांकerprets as XOFF.
//	Note: This command must be sent beक्रमe sending a SET_RX_FLOW or
//	SET_TX_FLOW with the XON_XOFF bit set.
//
//  Example क्रम Port 0
//	P0 = 11001000
//  P1 = IOSP_CMD_SET_XOFF_CHAR
//  P2 = 0x13


//
//	IOSP_CMD_RX_CHECK_REQ
//
//  This command is used to assist in the implementation of the
//  IOCTL_SERIAL_PURGE Winकरोws IOCTL.
//  This IOSP command tries to place a marker at the end of the RX
//  queue in the Edgeport. If the Edgeport RX queue is full then
//  the Check will be discarded.
//  It is up to the device driver to समयout रुकोing क्रम the
//  RX_CHECK_RSP.  If a RX_CHECK_RSP is received, the driver is
//	sure that all data has been received from the edgeport and
//	may now purge any पूर्णांकernal RX buffers.
//  Note tat the sequence numbers may be used to detect lost
//  CHECK_REQs.

//  Example क्रम Port 0
//	P0 = 11001000
//  P1 = IOSP_CMD_RX_CHECK_REQ
//  P2 = Sequence number


//  Response will be:
//  P1 = IOSP_EXT_RX_CHECK_RSP
//  P2 = Request Sequence number



//--------------------------------------------------------------
//
//	Define values क्रम status and status parameters
//	(received by Host from Edgeport)
//
//	1ssssPPP P1P1P1P1 [ P2P2P2P2P2 ]...
//
//	ssss:	00-07	2-byte status.	ssss identअगरies which UART रेजिस्टर
//					has changed value, and the new value is in P1.
//					Note that the ssss values करो not correspond to the
//					16554 रेजिस्टर numbers given in 16554.H. Instead,
//					see below क्रम definitions of the ssss numbers
//					used in this status message.
//
//		08-0B	3-byte status:					==== P1 ====	==== P2 ====
//					08	LSR_DATA:		New LSR		Errored byte
//					09	1-param responses	Response Code	Param
//					0A	OPEN_RSP:		InitialMsr	TxBufferSize
//					0B	available क्रम expansion
//
//		0C-0D	4-byte status.	P1 = extended status code and P2,P3 = params
//					Not currently implemented.
//
//		0E-0F	N-byte status:	P1 = num bytes after P1 (ie, TotalLen - 2)
//					P2 = extended status, P3..Pn = parameters.
//					Not currently implemented.
//

/****************************************************
 *	SSSS values क्रम 2-byte status messages (0-8)
 ****************************************************/

#घोषणा	IOSP_STATUS_LSR			0x00	// P1 is new value of LSR रेजिस्टर.

// Bits defined in 16554.H. Edgeport
// वापसs this in order to report
// line status errors (overrun,
// parity, framing, अवरोध). This क्रमm
// is used when a errored receive data
// अक्षरacter was NOT present in the
// UART when the LSR error occurred
// (ie, when LSR bit 0 = 0).

#घोषणा	IOSP_STATUS_MSR			0x01	// P1 is new value of MSR रेजिस्टर.

// Bits defined in 16554.H. Edgeport
// वापसs this in order to report
// changes in modem status lines
// (CTS, DSR, RI, CD)
//

//					0x02	// Available क्रम future expansion
//					0x03	//
//					0x04	//
//					0x05	//
//					0x06	//
//					0x07	//


/****************************************************
 *	SSSS values क्रम 3-byte status messages (8-A)
 ****************************************************/

#घोषणा	IOSP_STATUS_LSR_DATA		0x08	// P1 is new value of LSR रेजिस्टर (same as STATUS_LSR)

// P2 is errored अक्षरacter पढ़ो from
//    RxFIFO after LSR reported an error.

#घोषणा	IOSP_EXT_STATUS			0x09	// P1 is status/response code, param in P2.


// Response Codes (P1 values) क्रम 3-byte status messages

#घोषणा	IOSP_EXT_STATUS_CHASE_RSP	0	// Reply to CHASE_PORT cmd. P2 is outcome:
#घोषणा	IOSP_EXT_STATUS_CHASE_PASS	0	//	P2 = 0: All Tx data drained successfully
#घोषणा	IOSP_EXT_STATUS_CHASE_FAIL	1	//	P2 = 1: Timed out (stuck due to flow

//			control from remote device).

#घोषणा	IOSP_EXT_STATUS_RX_CHECK_RSP	1	// Reply to RX_CHECK cmd. P2 is sequence number


#घोषणा IOSP_STATUS_OPEN_RSP		0x0A	// Reply to OPEN_PORT cmd.

// P1 is Initial MSR value
// P2 is encoded TxBuffer Size:
//	TxBufferSize = (P2 + 1) * 64

//					0x0B	// Available क्रम future expansion

#घोषणा GET_TX_BUFFER_SIZE(P2) (((P2) + 1) * 64)




/****************************************************
 *	SSSS values क्रम 4-byte status messages
 ****************************************************/

#घोषणा IOSP_EXT4_STATUS		0x0C	// Extended status code in P1,

// Params in P2, P3
// Currently unimplemented.

//					0x0D	// Currently unused, available.



//
// Macros to parse status messages
//

#घोषणा	IOSP_GET_STATUS_LEN(code)	((code) < 8 ? 2 : ((code) < 0x0A ? 3 : 4))

#घोषणा	IOSP_STATUS_IS_2BYTE(code)	((code) < 0x08)
#घोषणा	IOSP_STATUS_IS_3BYTE(code)	(((code) >= 0x08) && ((code) <= 0x0B))
#घोषणा	IOSP_STATUS_IS_4BYTE(code)	(((code) >= 0x0C) && ((code) <= 0x0D))

