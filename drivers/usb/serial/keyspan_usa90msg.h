<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
	usa90msg.h

	Copyright (c) 1998-2003 InnoSys Incorporated.  All Rights Reserved
	This file is available under a BSD-style copyright

	Keyspan USB Async Message Formats क्रम the USA19HS

	Redistribution and use in source and binary क्रमms, with or without
	modअगरication, are permitted provided that the following conditions are
	met:

	1. Redistributions of source code must retain this licence text
   	without modअगरication, this list of conditions, and the following
   	disclaimer.  The following copyright notice must appear immediately at
   	the beginning of all source files:

        	Copyright (c) 1998-2003 InnoSys Incorporated.  All Rights Reserved

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

	Revisions:

	2003feb14		add setTxMode/txMode  and cancelRxXoff to portControl
	2003mar21		change name of PARITY_0/1 to add MARK/SPACE
*/

#अगर_अघोषित	__USA90MSG__
#घोषणा	__USA90MSG__

काष्ठा keyspan_usa90_portControlMessage
अणु
	/*
		there are three types of "commands" sent in the control message:

		1.	configuration changes which must be requested by setting
			the corresponding "set" flag (and should only be requested
			when necessary, to reduce overhead on the device):
	*/

	u8	setClocking,	// host requests baud rate be set
		baudLo,			// host करोes baud भागisor calculation
		baudHi,			// host करोes baud भागisor calculation 
		
		setLcr,			// host requests lcr be set
		lcr,			// use PARITY, STOPBITS, DATABITS below
		
		setRxMode,		// set receive mode
		rxMode,			// RXMODE_DMA or RXMODE_BYHAND

		setTxMode,		// set transmit mode
		txMode,			// TXMODE_DMA or TXMODE_BYHAND

		setTxFlowControl,	// host requests tx flow control be set
		txFlowControl	,	// use TX_FLOW... bits below
		setRxFlowControl,	// host requests rx flow control be set
		rxFlowControl,	// use RX_FLOW... bits below
		sendXoff,		// host requests XOFF transmitted immediately
		sendXon,		// host requests XON अक्षर transmitted
		xonChar,		// specअगरied in current अक्षरacter क्रमmat
		xoffChar,		// specअगरied in current अक्षरacter क्रमmat

		sendChar,		// host requests अक्षर transmitted immediately
		txChar,			// अक्षरacter to send

		setRts,			// host requests RTS output be set
		rts,			// 1=on, 0=off
		setDtr, 		// host requests DTR output be set
		dtr;			// 1=on, 0=off

	
	/*
		2.	configuration data which is simply used as is 
			and must be specअगरied correctly in every host message.
	*/

	u8	rxForwardingLength,  // क्रमward when this number of अक्षरs available
		rxForwardingTimeout, // (1-31 in ms)
		txAckSetting;	   // 0=करोn't ack, 1=normal, 2-255 TBD...
	/*
		3.	Firmware states which cause actions अगर they change					
		and must be specअगरied correctly in every host message.
	*/

	u8	portEnabled,	// 0=disabled, 1=enabled
		txFlush,		// 0=normal, 1=toss outbound data
		txBreak,		// 0=अवरोध off, 1=अवरोध on
		loopbackMode;	// 0=no loopback, 1=loopback enabled

	/*
		4.	commands which are flags only; these are processed in order
			(so that, e.g., अगर rxFlush and rxForward flags are set, the
			port will have no data to क्रमward); any non-zero value 
			is respected
	*/

	u8	rxFlush,		// toss inbound data
		rxForward,		// क्रमward all inbound data, NOW (as अगर fwdLen==1)
		cancelRxXoff,	// cancel any receive XOFF state (_txXoff)
		वापसStatus;	// वापस current status NOW
पूर्ण;

// defines क्रम bits in lcr
#घोषणा		USA_DATABITS_5		0x00
#घोषणा		USA_DATABITS_6		0x01
#घोषणा		USA_DATABITS_7		0x02
#घोषणा		USA_DATABITS_8		0x03
#घोषणा		STOPBITS_5678_1		0x00	// 1 stop bit क्रम all byte sizes
#घोषणा		STOPBITS_5_1p5		0x04	// 1.5 stop bits क्रम 5-bit byte
#घोषणा		STOPBITS_678_2		0x04	// 2 stop bits क्रम 6-8 bit byte
#घोषणा		USA_PARITY_NONE		0x00
#घोषणा		USA_PARITY_ODD		0x08
#घोषणा		USA_PARITY_EVEN		0x18
#घोषणा		PARITY_MARK_1  		0x28   	// क्रमce parity MARK
#घोषणा		PARITY_SPACE_0 		0x38	// क्रमce parity SPACE

#घोषणा		TXFLOW_CTS			0x04	
#घोषणा		TXFLOW_DSR			0x08
#घोषणा		TXFLOW_XOFF			0x01	
#घोषणा		TXFLOW_XOFF_ANY		0x02	
#घोषणा		TXFLOW_XOFF_BITS	(TXFLOW_XOFF | TXFLOW_XOFF_ANY)

#घोषणा		RXFLOW_XOFF			0x10	
#घोषणा		RXFLOW_RTS			0x20	
#घोषणा		RXFLOW_DTR			0x40
#घोषणा		RXFLOW_DSR_SENSITIVITY	0x80

#घोषणा		RXMODE_BYHAND		0x00	
#घोषणा		RXMODE_DMA			0x02	

#घोषणा		TXMODE_BYHAND		0x00	
#घोषणा		TXMODE_DMA			0x02	


// all things called "StatusMessage" are sent on the status endpoपूर्णांक

काष्ठा keyspan_usa90_portStatusMessage	
अणु
	u8	msr,			// reports the actual MSR रेजिस्टर
		cts,			// reports CTS pin
		dcd,			// reports DCD pin
		dsr,			// reports DSR pin
		ri,				// reports RI pin
		_txXoff,		// port is in XOFF state (we received XOFF)
		rxBreak,		// reports अवरोध state
		rxOverrun,		// count of overrun errors (since last reported)
		rxParity,		// count of parity errors (since last reported)
		rxFrame,		// count of frame errors (since last reported)
		portState,		// PORTSTATE_xxx bits (useful क्रम debugging)
		messageAck,		// message acknowledgement
		अक्षरAck,		// अक्षरacter acknowledgement
		controlResponse;	// (value = वापसStatus) a control message has been processed 
पूर्ण;

// bits in RX data message when STAT byte is included

#घोषणा	RXERROR_OVERRUN		0x02
#घोषणा	RXERROR_PARITY		0x04
#घोषणा	RXERROR_FRAMING		0x08
#घोषणा	RXERROR_BREAK		0x10

#घोषणा	PORTSTATE_ENABLED	0x80
#घोषणा	PORTSTATE_TXFLUSH	0x01
#घोषणा	PORTSTATE_TXBREAK	0x02
#घोषणा	PORTSTATE_LOOPBACK 	0x04

// MSR bits

#घोषणा USA_MSR_dCTS	  		0x01		// CTS has changed since last report	
#घोषणा USA_MSR_dDSR	  		0x02
#घोषणा USA_MSR_dRI			0x04
#घोषणा USA_MSR_dDCD	  		0x08

#घोषणा USA_MSR_CTS			0x10	  	// current state of CTS
#घोषणा USA_MSR_DSR			0x20
#घोषणा USA_USA_MSR_RI			0x40
#घोषणा MSR_DCD				0x80

// ie: the maximum length of an endpoपूर्णांक buffer
#घोषणा		MAX_DATA_LEN			64

#पूर्ण_अगर
