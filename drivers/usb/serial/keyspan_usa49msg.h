<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
	usa49msg.h

	Copyright (C) 1998-2000 InnoSys Incorporated.  All Rights Reserved
	This file is available under a BSD-style copyright

	Keyspan USB Async Message Formats क्रम the USA49W

	Redistribution and use in source and binary क्रमms, with or without
	modअगरication, are permitted provided that the following conditions are
	met:

	1. Redistributions of source code must retain this licence text
   	without modअगरication, this list of conditions, and the following
   	disclaimer.  The following copyright notice must appear immediately at
   	the beginning of all source files:

        	Copyright (C) 1998-2000 InnoSys Incorporated.  All Rights Reserved

        	This file is available under a BSD-style copyright

	2. The name of InnoSys Incorporated may not be used to enकरोrse or promote
   	products derived from this software without specअगरic prior written
   	permission.

	THIS SOFTWARE IS PROVIDED BY INNOSYS CORP. ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
	NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
	INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.    

	4th revision: USA49W version

	Buffer क्रमmats क्रम RX/TX data messages are not defined by
	a काष्ठाure, but are described here:

	USB OUT (host -> USAxx, transmit) messages contain a 
	REQUEST_ACK indicator (set to 0xff to request an ACK at the 
	completion of transmit; 0x00 otherwise), followed by data:

		RQSTACK DAT DAT DAT ...

	with a total data length of 63.

	USB IN (USAxx -> host, receive) messages begin with a status
	byte in which the 0x80 bit is either:
				   	
		(a)	0x80 bit clear
			indicates that the bytes following it are all data
			bytes:

				STAT DATA DATA DATA DATA DATA ...

			क्रम a total of up to 63 DATA bytes,

	or:

		(b)	0x80 bit set
			indiates that the bytes following alternate data and
			status bytes:

				STAT DATA STAT DATA STAT DATA STAT DATA ...

			क्रम a total of up to 32 DATA bytes.

	The valid bits in the STAT bytes are:

		OVERRUN	0x02
		PARITY	0x04
		FRAMING	0x08
		BREAK	0x10

	Notes:
	
	(1) The OVERRUN bit can appear in either (a) or (b) क्रमmat
		messages, but the but the PARITY/FRAMING/BREAK bits
		only appear in (b) क्रमmat messages.
	(2) For the host to determine the exact poपूर्णांक at which the
		overrun occurred (to identअगरy the poपूर्णांक in the data
		stream at which the data was lost), it needs to count
		128 अक्षरacters, starting at the first अक्षरacter of the
		message in which OVERRUN was reported; the lost अक्षरacter(s)
		would have been received between the 128th and 129th
		अक्षरacters.
	(3)	An RX data message in which the first byte has 0x80 clear
		serves as a "break off" indicator.
	(4)	a control message specअगरying disablePort will be answered
		with a status message, but no further status will be sent
		until a control messages with enablePort is sent

	revision history:

	1999feb10	add reportHskiaChanges to allow us to ignore them
	1999feb10	add txAckThreshold क्रम fast+loose throughput enhancement
	1999mar30	beef up support क्रम RX error reporting
	1999apr14	add resetDataToggle to control message
	2000jan04	merge with usa17msg.h
	2000mar08	clone from usa26msg.h -> usa49msg.h
	2000mar09	change to support 4 ports
	2000may03	change बाह्यal घड़ीing to match USA-49W hardware
	2000jun01	add extended BSD-style copyright text
	2001jul05	change message क्रमmat to improve OVERRUN हाल
*/

#अगर_अघोषित	__USA49MSG__
#घोषणा	__USA49MSG__


/*
	Host->device messages sent on the global control endpoपूर्णांक:

	portNumber	message
	----------	--------------------
	0,1,2,3		portControlMessage
	0x80		globalControlMessage
*/

काष्ठा keyspan_usa49_portControlMessage
अणु
	/*
		0.	0/1/2/3 	port control message follows
			0x80 set	non-port control message follows
	*/
	u8	portNumber,

	/*
		there are three types of "commands" sent in the control message:

		1.	configuration changes which must be requested by setting
			the corresponding "set" flag (and should only be requested
			when necessary, to reduce overhead on the USA26):
	*/
		setClocking,	// host requests baud rate be set
		baudLo,			// host करोes baud भागisor calculation
		baudHi,			// baudHi is only used क्रम first port (gives lower rates)
		prescaler,		// specअगरied as N/8; values 8-ff are valid
						// must be set any समय पूर्णांकernal baud rate is set;
		txClocking,		// 0=पूर्णांकernal, 1=बाह्यal/DSR
		rxClocking,		// 0=पूर्णांकernal, 1=बाह्यal/DSR

		setLcr,			// host requests lcr be set
		lcr,			// use PARITY, STOPBITS, DATABITS below

		setFlowControl,	// host requests flow control be set
		ctsFlowControl,	// 1=use CTS flow control, 0=करोn't
		xonFlowControl,	// 1=use XON/XOFF flow control, 0=करोn't
		xonChar,		// specअगरied in current अक्षरacter क्रमmat
		xoffChar,		// specअगरied in current अक्षरacter क्रमmat

		setRts,			// host requests RTS output be set
		rts,			// 1=active, 0=inactive

		setDtr,			// host requests DTR output be set
		dtr;			// 1=on, 0=off


	/*
		3.	configuration data which is simply used as is (no overhead,
			but must be specअगरied correctly in every host message).
	*/
	u8	क्रमwardingLength,  // क्रमward when this number of अक्षरs available
		dsrFlowControl,	// 1=use DSR flow control, 0=करोn't
		txAckThreshold,	// 0=not allowed, 1=normal, 2-255 deliver ACK faster
		loopbackMode;	// 0=no loopback, 1=loopback enabled

	/*
		4.	commands which are flags only; these are processed in order
			(so that, e.g., अगर both _txOn and _txOff flags are set, the
			port ends in a TX_OFF state); any non-zero value is respected
	*/
	u8	_txOn,			// enable transmitting (and जारी अगर there's data)
		_txOff,			// stop transmitting
		txFlush,		// toss outbound data
		txBreak,		// turn on अवरोध (cleared by _txOn)
		rxOn,			// turn on receiver
		rxOff,			// turn off receiver
		rxFlush,		// toss inbound data
		rxForward,		// क्रमward all inbound data, NOW (as अगर fwdLen==1)
		वापसStatus,	// वापस current status (even अगर it hasn't changed)
		resetDataToggle,// reset data toggle state to DATA0
		enablePort,		// start servicing port (move data, check status)
		disablePort;	// stop servicing port (करोes implicit tx/rx flush/off)
	
पूर्ण;

// defines क्रम bits in lcr
#घोषणा	USA_DATABITS_5		0x00
#घोषणा	USA_DATABITS_6		0x01
#घोषणा	USA_DATABITS_7		0x02
#घोषणा	USA_DATABITS_8		0x03
#घोषणा	STOPBITS_5678_1		0x00	// 1 stop bit क्रम all byte sizes
#घोषणा	STOPBITS_5_1p5		0x04	// 1.5 stop bits क्रम 5-bit byte
#घोषणा	STOPBITS_678_2		0x04	// 2 stop bits क्रम 6/7/8-bit byte
#घोषणा	USA_PARITY_NONE		0x00
#घोषणा	USA_PARITY_ODD		0x08
#घोषणा	USA_PARITY_EVEN		0x18
#घोषणा	PARITY_1			0x28
#घोषणा	PARITY_0			0x38

/*
	during normal operation, status messages are वापसed 
	to the host whenever the board detects changes.  In some
	circumstances (e.g. Winकरोws), status messages from the
	device cause problems; to shut them off, the host issues
	a control message with the disableStatusMessages flags
	set (to any non-zero value).  The device will respond to
	this message, and then suppress further status messages;
	it will resume sending status messages any समय the host
	sends any control message (either global or port-specअगरic).
*/

काष्ठा keyspan_usa49_globalControlMessage
अणु
	u8	portNumber,			// 0x80
		sendGlobalStatus,	// 1/2=number of status responses requested
		resetStatusToggle,	// 1=reset global status toggle
		resetStatusCount,	// a cycling value
		remoteWakeupEnable,		// 0x10=P1, 0x20=P2, 0x40=P3, 0x80=P4
		disableStatusMessages;	// 1=send no status until host talks
पूर्ण;

/*
	Device->host messages send on the global status endpoपूर्णांक

	portNumber			message
	----------			--------------------
	0x00,0x01,0x02,0x03	portStatusMessage
	0x80				globalStatusMessage
	0x81				globalDebugMessage
*/

काष्ठा keyspan_usa49_portStatusMessage	// one क्रम each port
अणु
	u8	portNumber,		// 0,1,2,3
		cts,			// reports CTS pin
		dcd,			// reports DCD pin
		dsr,			// reports DSR pin
		ri,				// reports RI pin
		_txOff,			// transmit has been disabled (by host)
		_txXoff,		// transmit is in XOFF state (either host or RX XOFF)
		rxEnabled,		// as configured by rxOn/rxOff 1=on, 0=off
		controlResponse,// 1=a control message has been processed
		txAck,			// ACK (data TX complete)
		rs232valid;		// RS-232 संकेत valid
पूर्ण;

// bits in RX data message when STAT byte is included
#घोषणा	RXERROR_OVERRUN	0x02
#घोषणा	RXERROR_PARITY	0x04
#घोषणा	RXERROR_FRAMING	0x08
#घोषणा	RXERROR_BREAK	0x10

काष्ठा keyspan_usa49_globalStatusMessage
अणु
	u8	portNumber,			// 0x80=globalStatusMessage
		sendGlobalStatus,	// from request, decremented
		resetStatusCount;	// as in request
पूर्ण;

काष्ठा keyspan_usa49_globalDebugMessage
अणु
	u8	portNumber,			// 0x81=globalDebugMessage
		n,					// typically a count/status byte
		b;					// typically a data byte
पूर्ण;

// ie: the maximum length of an EZUSB endpoपूर्णांक buffer
#घोषणा	MAX_DATA_LEN			64

// update status approx. 60 बार a second (16.6666 ms)
#घोषणा	STATUS_UPDATE_INTERVAL	16

// status rationing tuning value (each port माला_लो checked each n ms)
#घोषणा	STATUS_RATION	10

#पूर्ण_अगर
