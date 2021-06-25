<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/*
 * SyncLink Multiprotocol Serial Adapter Driver
 *
 * $Id: synclink.h,v 3.14 2006/07/17 20:15:43 paulkf Exp $
 *
 * Copyright (C) 1998-2000 by Microgate Corporation
 *
 * Redistribution of this file is permitted under
 * the terms of the GNU Public License (GPL)
 */

#अगर_अघोषित _UAPI_SYNCLINK_H_
#घोषणा _UAPI_SYNCLINK_H_
#घोषणा SYNCLINK_H_VERSION 3.6

#समावेश <linux/types.h>

#घोषणा BIT0	0x0001
#घोषणा BIT1	0x0002
#घोषणा BIT2	0x0004
#घोषणा BIT3	0x0008
#घोषणा BIT4	0x0010
#घोषणा BIT5	0x0020
#घोषणा BIT6	0x0040
#घोषणा BIT7	0x0080
#घोषणा BIT8	0x0100
#घोषणा BIT9	0x0200
#घोषणा BIT10	0x0400
#घोषणा BIT11	0x0800
#घोषणा BIT12	0x1000
#घोषणा BIT13	0x2000
#घोषणा BIT14	0x4000
#घोषणा BIT15	0x8000
#घोषणा BIT16	0x00010000
#घोषणा BIT17	0x00020000
#घोषणा BIT18	0x00040000
#घोषणा BIT19	0x00080000
#घोषणा BIT20	0x00100000
#घोषणा BIT21	0x00200000
#घोषणा BIT22	0x00400000
#घोषणा BIT23	0x00800000
#घोषणा BIT24	0x01000000
#घोषणा BIT25	0x02000000
#घोषणा BIT26	0x04000000
#घोषणा BIT27	0x08000000
#घोषणा BIT28	0x10000000
#घोषणा BIT29	0x20000000
#घोषणा BIT30	0x40000000
#घोषणा BIT31	0x80000000


#घोषणा HDLC_MAX_FRAME_SIZE	65535
#घोषणा MAX_ASYNC_TRANSMIT	4096
#घोषणा MAX_ASYNC_BUFFER_SIZE	4096

#घोषणा ASYNC_PARITY_NONE		0
#घोषणा ASYNC_PARITY_EVEN		1
#घोषणा ASYNC_PARITY_ODD		2
#घोषणा ASYNC_PARITY_SPACE		3

#घोषणा HDLC_FLAG_UNDERRUN_ABORT7	0x0000
#घोषणा HDLC_FLAG_UNDERRUN_ABORT15	0x0001
#घोषणा HDLC_FLAG_UNDERRUN_FLAG		0x0002
#घोषणा HDLC_FLAG_UNDERRUN_CRC		0x0004
#घोषणा HDLC_FLAG_SHARE_ZERO		0x0010
#घोषणा HDLC_FLAG_AUTO_CTS		0x0020
#घोषणा HDLC_FLAG_AUTO_DCD		0x0040
#घोषणा HDLC_FLAG_AUTO_RTS		0x0080
#घोषणा HDLC_FLAG_RXC_DPLL		0x0100
#घोषणा HDLC_FLAG_RXC_BRG		0x0200
#घोषणा HDLC_FLAG_RXC_TXCPIN		0x8000
#घोषणा HDLC_FLAG_RXC_RXCPIN		0x0000
#घोषणा HDLC_FLAG_TXC_DPLL		0x0400
#घोषणा HDLC_FLAG_TXC_BRG		0x0800
#घोषणा HDLC_FLAG_TXC_TXCPIN		0x0000
#घोषणा HDLC_FLAG_TXC_RXCPIN		0x0008
#घोषणा HDLC_FLAG_DPLL_DIV8		0x1000
#घोषणा HDLC_FLAG_DPLL_DIV16		0x2000
#घोषणा HDLC_FLAG_DPLL_DIV32		0x0000
#घोषणा HDLC_FLAG_HDLC_LOOPMODE		0x4000

#घोषणा HDLC_CRC_NONE			0
#घोषणा HDLC_CRC_16_CCITT		1
#घोषणा HDLC_CRC_32_CCITT		2
#घोषणा HDLC_CRC_MASK			0x00ff
#घोषणा HDLC_CRC_RETURN_EX		0x8000

#घोषणा RX_OK				0
#घोषणा RX_CRC_ERROR			1

#घोषणा HDLC_TXIDLE_FLAGS		0
#घोषणा HDLC_TXIDLE_ALT_ZEROS_ONES	1
#घोषणा HDLC_TXIDLE_ZEROS		2
#घोषणा HDLC_TXIDLE_ONES		3
#घोषणा HDLC_TXIDLE_ALT_MARK_SPACE	4
#घोषणा HDLC_TXIDLE_SPACE		5
#घोषणा HDLC_TXIDLE_MARK		6
#घोषणा HDLC_TXIDLE_CUSTOM_8            0x10000000
#घोषणा HDLC_TXIDLE_CUSTOM_16           0x20000000

#घोषणा HDLC_ENCODING_NRZ			0
#घोषणा HDLC_ENCODING_NRZB			1
#घोषणा HDLC_ENCODING_NRZI_MARK			2
#घोषणा HDLC_ENCODING_NRZI_SPACE		3
#घोषणा HDLC_ENCODING_NRZI			HDLC_ENCODING_NRZI_SPACE
#घोषणा HDLC_ENCODING_BIPHASE_MARK		4
#घोषणा HDLC_ENCODING_BIPHASE_SPACE		5
#घोषणा HDLC_ENCODING_BIPHASE_LEVEL		6
#घोषणा HDLC_ENCODING_DIFF_BIPHASE_LEVEL	7

#घोषणा HDLC_PREAMBLE_LENGTH_8BITS	0
#घोषणा HDLC_PREAMBLE_LENGTH_16BITS	1
#घोषणा HDLC_PREAMBLE_LENGTH_32BITS	2
#घोषणा HDLC_PREAMBLE_LENGTH_64BITS	3

#घोषणा HDLC_PREAMBLE_PATTERN_NONE	0
#घोषणा HDLC_PREAMBLE_PATTERN_ZEROS	1
#घोषणा HDLC_PREAMBLE_PATTERN_FLAGS	2
#घोषणा HDLC_PREAMBLE_PATTERN_10	3
#घोषणा HDLC_PREAMBLE_PATTERN_01	4
#घोषणा HDLC_PREAMBLE_PATTERN_ONES	5

#घोषणा MGSL_MODE_ASYNC		1
#घोषणा MGSL_MODE_HDLC		2
#घोषणा MGSL_MODE_MONOSYNC	3
#घोषणा MGSL_MODE_BISYNC	4
#घोषणा MGSL_MODE_RAW		6
#घोषणा MGSL_MODE_BASE_CLOCK    7
#घोषणा MGSL_MODE_XSYNC         8

#घोषणा MGSL_BUS_TYPE_ISA	1
#घोषणा MGSL_BUS_TYPE_EISA	2
#घोषणा MGSL_BUS_TYPE_PCI	5

#घोषणा MGSL_INTERFACE_MASK     0xf
#घोषणा MGSL_INTERFACE_DISABLE  0
#घोषणा MGSL_INTERFACE_RS232    1
#घोषणा MGSL_INTERFACE_V35      2
#घोषणा MGSL_INTERFACE_RS422    3
#घोषणा MGSL_INTERFACE_RTS_EN   0x10
#घोषणा MGSL_INTERFACE_LL       0x20
#घोषणा MGSL_INTERFACE_RL       0x40
#घोषणा MGSL_INTERFACE_MSB_FIRST 0x80

प्रकार काष्ठा _MGSL_PARAMS
अणु
	/* Common */

	अचिन्हित दीर्घ	mode;		/* Asynchronous or HDLC */
	अचिन्हित अक्षर	loopback;	/* पूर्णांकernal loopback mode */

	/* HDLC Only */

	अचिन्हित लघु	flags;
	अचिन्हित अक्षर	encoding;	/* NRZ, NRZI, etc. */
	अचिन्हित दीर्घ	घड़ी_speed;	/* बाह्यal घड़ी speed in bits per second */
	अचिन्हित अक्षर	addr_filter;	/* receive HDLC address filter, 0xFF = disable */
	अचिन्हित लघु	crc_type;	/* None, CRC16-CCITT, or CRC32-CCITT */
	अचिन्हित अक्षर	preamble_length;
	अचिन्हित अक्षर	preamble;

	/* Async Only */

	अचिन्हित दीर्घ	data_rate;	/* bits per second */
	अचिन्हित अक्षर	data_bits;	/* 7 or 8 data bits */
	अचिन्हित अक्षर	stop_bits;	/* 1 or 2 stop bits */
	अचिन्हित अक्षर	parity;		/* none, even, or odd */

पूर्ण MGSL_PARAMS, *PMGSL_PARAMS;

#घोषणा MICROGATE_VENDOR_ID 0x13c0
#घोषणा SYNCLINK_DEVICE_ID 0x0010
#घोषणा MGSCC_DEVICE_ID 0x0020
#घोषणा SYNCLINK_SCA_DEVICE_ID 0x0030
#घोषणा SYNCLINK_GT_DEVICE_ID 0x0070
#घोषणा SYNCLINK_GT4_DEVICE_ID 0x0080
#घोषणा SYNCLINK_AC_DEVICE_ID  0x0090
#घोषणा SYNCLINK_GT2_DEVICE_ID 0x00A0
#घोषणा MGSL_MAX_SERIAL_NUMBER 30

/*
** device diagnostics status
*/

#घोषणा DiagStatus_OK				0
#घोषणा DiagStatus_AddressFailure		1
#घोषणा DiagStatus_AddressConflict		2
#घोषणा DiagStatus_IrqFailure			3
#घोषणा DiagStatus_IrqConflict			4
#घोषणा DiagStatus_DmaFailure			5
#घोषणा DiagStatus_DmaConflict			6
#घोषणा DiagStatus_PciAdapterNotFound		7
#घोषणा DiagStatus_CantAssignPciResources	8
#घोषणा DiagStatus_CantAssignPciMemAddr		9
#घोषणा DiagStatus_CantAssignPciIoAddr		10
#घोषणा DiagStatus_CantAssignPciIrq		11
#घोषणा DiagStatus_MemoryError			12

#घोषणा SerialSignal_DCD            0x01     /* Data Carrier Detect */
#घोषणा SerialSignal_TXD            0x02     /* Transmit Data */
#घोषणा SerialSignal_RI             0x04     /* Ring Indicator */
#घोषणा SerialSignal_RXD            0x08     /* Receive Data */
#घोषणा SerialSignal_CTS            0x10     /* Clear to Send */
#घोषणा SerialSignal_RTS            0x20     /* Request to Send */
#घोषणा SerialSignal_DSR            0x40     /* Data Set Ready */
#घोषणा SerialSignal_DTR            0x80     /* Data Terminal Ready */


/*
 * Counters of the input lines (CTS, DSR, RI, CD) पूर्णांकerrupts
 */
काष्ठा mgsl_icount अणु
	__u32	cts, dsr, rng, dcd, tx, rx;
	__u32	frame, parity, overrun, brk;
	__u32	buf_overrun;
	__u32	txok;
	__u32	txunder;
	__u32	txपात;
	__u32	txसमयout;
	__u32	rxलघु;
	__u32	rxदीर्घ;
	__u32	rxपात;
	__u32	rxover;
	__u32	rxcrc;
	__u32	rxok;
	__u32	निकासhunt;
	__u32	rxidle;
पूर्ण;

काष्ठा gpio_desc अणु
	__u32 state;
	__u32 smask;
	__u32 dir;
	__u32 dmask;
पूर्ण;

#घोषणा DEBUG_LEVEL_DATA	1
#घोषणा DEBUG_LEVEL_ERROR 	2
#घोषणा DEBUG_LEVEL_INFO  	3
#घोषणा DEBUG_LEVEL_BH    	4
#घोषणा DEBUG_LEVEL_ISR		5

/*
** Event bit flags क्रम use with MgslWaitEvent
*/

#घोषणा MgslEvent_DsrActive	0x0001
#घोषणा MgslEvent_DsrInactive	0x0002
#घोषणा MgslEvent_Dsr		0x0003
#घोषणा MgslEvent_CtsActive	0x0004
#घोषणा MgslEvent_CtsInactive	0x0008
#घोषणा MgslEvent_Cts		0x000c
#घोषणा MgslEvent_DcdActive	0x0010
#घोषणा MgslEvent_DcdInactive	0x0020
#घोषणा MgslEvent_Dcd		0x0030
#घोषणा MgslEvent_RiActive	0x0040
#घोषणा MgslEvent_RiInactive	0x0080
#घोषणा MgslEvent_Ri		0x00c0
#घोषणा MgslEvent_ExitHuntMode	0x0100
#घोषणा MgslEvent_IdleReceived	0x0200

/* Private IOCTL codes:
 *
 * MGSL_IOCSPARAMS	set MGSL_PARAMS काष्ठाure values
 * MGSL_IOCGPARAMS	get current MGSL_PARAMS काष्ठाure values
 * MGSL_IOCSTXIDLE	set current transmit idle mode
 * MGSL_IOCGTXIDLE	get current transmit idle mode
 * MGSL_IOCTXENABLE	enable or disable transmitter
 * MGSL_IOCRXENABLE	enable or disable receiver
 * MGSL_IOCTXABORT	पात transmitting frame (HDLC)
 * MGSL_IOCGSTATS	वापस current statistics
 * MGSL_IOCWAITEVENT	रुको क्रम specअगरied event to occur
 * MGSL_LOOPTXDONE	transmit in HDLC LoopMode करोne
 * MGSL_IOCSIF          set the serial पूर्णांकerface type
 * MGSL_IOCGIF          get the serial पूर्णांकerface type
 */
#घोषणा MGSL_MAGIC_IOC	'm'
#घोषणा MGSL_IOCSPARAMS		_IOW(MGSL_MAGIC_IOC,0,काष्ठा _MGSL_PARAMS)
#घोषणा MGSL_IOCGPARAMS		_IOR(MGSL_MAGIC_IOC,1,काष्ठा _MGSL_PARAMS)
#घोषणा MGSL_IOCSTXIDLE		_IO(MGSL_MAGIC_IOC,2)
#घोषणा MGSL_IOCGTXIDLE		_IO(MGSL_MAGIC_IOC,3)
#घोषणा MGSL_IOCTXENABLE	_IO(MGSL_MAGIC_IOC,4)
#घोषणा MGSL_IOCRXENABLE	_IO(MGSL_MAGIC_IOC,5)
#घोषणा MGSL_IOCTXABORT		_IO(MGSL_MAGIC_IOC,6)
#घोषणा MGSL_IOCGSTATS		_IO(MGSL_MAGIC_IOC,7)
#घोषणा MGSL_IOCWAITEVENT	_IOWR(MGSL_MAGIC_IOC,8,पूर्णांक)
#घोषणा MGSL_IOCCLRMODCOUNT	_IO(MGSL_MAGIC_IOC,15)
#घोषणा MGSL_IOCLOOPTXDONE	_IO(MGSL_MAGIC_IOC,9)
#घोषणा MGSL_IOCSIF		_IO(MGSL_MAGIC_IOC,10)
#घोषणा MGSL_IOCGIF		_IO(MGSL_MAGIC_IOC,11)
#घोषणा MGSL_IOCSGPIO		_IOW(MGSL_MAGIC_IOC,16,काष्ठा gpio_desc)
#घोषणा MGSL_IOCGGPIO		_IOR(MGSL_MAGIC_IOC,17,काष्ठा gpio_desc)
#घोषणा MGSL_IOCWAITGPIO	_IOWR(MGSL_MAGIC_IOC,18,काष्ठा gpio_desc)
#घोषणा MGSL_IOCSXSYNC		_IO(MGSL_MAGIC_IOC, 19)
#घोषणा MGSL_IOCGXSYNC		_IO(MGSL_MAGIC_IOC, 20)
#घोषणा MGSL_IOCSXCTRL		_IO(MGSL_MAGIC_IOC, 21)
#घोषणा MGSL_IOCGXCTRL		_IO(MGSL_MAGIC_IOC, 22)


#पूर्ण_अगर /* _UAPI_SYNCLINK_H_ */
