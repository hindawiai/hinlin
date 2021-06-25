<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Description of Z8530 Z85C30 and Z85230 communications chips
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1998 Alan Cox <alan@lxorguk.ukuu.org.uk>
 */

#अगर_अघोषित _Z8530_H
#घोषणा _Z8530_H

#समावेश <linux/tty.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* Conversion routines to/from brg समय स्थिरants from/to bits
 * per second.
 */
#घोषणा BRG_TO_BPS(brg, freq) ((freq) / 2 / ((brg) + 2))
#घोषणा BPS_TO_BRG(bps, freq) ((((freq) + (bps)) / (2 * (bps))) - 2)

/* The Zilog रेजिस्टर set */

#घोषणा	FLAG	0x7e

/* Write Register 0 */
#घोषणा	R0	0		/* Register selects */
#घोषणा	R1	1
#घोषणा	R2	2
#घोषणा	R3	3
#घोषणा	R4	4
#घोषणा	R5	5
#घोषणा	R6	6
#घोषणा	R7	7
#घोषणा	R8	8
#घोषणा	R9	9
#घोषणा	R10	10
#घोषणा	R11	11
#घोषणा	R12	12
#घोषणा	R13	13
#घोषणा	R14	14
#घोषणा	R15	15

#घोषणा RPRIME	16		/* Indicate a prime रेजिस्टर access on 230 */

#घोषणा	शून्यCODE	0	/* Null Code */
#घोषणा	POINT_HIGH	0x8	/* Select upper half of रेजिस्टरs */
#घोषणा	RES_EXT_INT	0x10	/* Reset Ext. Status Interrupts */
#घोषणा	SEND_ABORT	0x18	/* HDLC Abort */
#घोषणा	RES_RxINT_FC	0x20	/* Reset RxINT on First Character */
#घोषणा	RES_Tx_P	0x28	/* Reset TxINT Pending */
#घोषणा	ERR_RES		0x30	/* Error Reset */
#घोषणा	RES_H_IUS	0x38	/* Reset highest IUS */

#घोषणा	RES_Rx_CRC	0x40	/* Reset Rx CRC Checker */
#घोषणा	RES_Tx_CRC	0x80	/* Reset Tx CRC Checker */
#घोषणा	RES_EOM_L	0xC0	/* Reset EOM latch */

/* Write Register 1 */

#घोषणा	EXT_INT_ENAB	0x1	/* Ext Int Enable */
#घोषणा	TxINT_ENAB	0x2	/* Tx Int Enable */
#घोषणा	PAR_SPEC	0x4	/* Parity is special condition */

#घोषणा	RxINT_DISAB	0	/* Rx Int Disable */
#घोषणा	RxINT_FCERR	0x8	/* Rx Int on First Character Only or Error */
#घोषणा	INT_ALL_Rx	0x10	/* Int on all Rx Characters or error */
#घोषणा	INT_ERR_Rx	0x18	/* Int on error only */

#घोषणा	WT_RDY_RT	0x20	/* Wait/Ready on R/T */
#घोषणा	WT_FN_RDYFN	0x40	/* Wait/FN/Ready FN */
#घोषणा	WT_RDY_ENAB	0x80	/* Wait/Ready Enable */

/* Write Register #2 (Interrupt Vector) */

/* Write Register 3 */

#घोषणा	RxENABLE	0x1	/* Rx Enable */
#घोषणा	SYNC_L_INH	0x2	/* Sync Character Load Inhibit */
#घोषणा	ADD_SM		0x4	/* Address Search Mode (SDLC) */
#घोषणा	RxCRC_ENAB	0x8	/* Rx CRC Enable */
#घोषणा	ENT_HM		0x10	/* Enter Hunt Mode */
#घोषणा	AUTO_ENAB	0x20	/* Auto Enables */
#घोषणा	Rx5		0x0	/* Rx 5 Bits/Character */
#घोषणा	Rx7		0x40	/* Rx 7 Bits/Character */
#घोषणा	Rx6		0x80	/* Rx 6 Bits/Character */
#घोषणा	Rx8		0xc0	/* Rx 8 Bits/Character */

/* Write Register 4 */

#घोषणा	PAR_ENA		0x1	/* Parity Enable */
#घोषणा	PAR_EVEN	0x2	/* Parity Even/Odd* */

#घोषणा	SYNC_ENAB	0	/* Sync Modes Enable */
#घोषणा	SB1		0x4	/* 1 stop bit/अक्षर */
#घोषणा	SB15		0x8	/* 1.5 stop bits/अक्षर */
#घोषणा	SB2		0xc	/* 2 stop bits/अक्षर */

#घोषणा	MONSYNC		0	/* 8 Bit Sync अक्षरacter */
#घोषणा	BISYNC		0x10	/* 16 bit sync अक्षरacter */
#घोषणा	SDLC		0x20	/* SDLC Mode (01111110 Sync Flag) */
#घोषणा	EXTSYNC		0x30	/* External Sync Mode */

#घोषणा	X1CLK		0x0	/* x1 घड़ी mode */
#घोषणा	X16CLK		0x40	/* x16 घड़ी mode */
#घोषणा	X32CLK		0x80	/* x32 घड़ी mode */
#घोषणा	X64CLK		0xC0	/* x64 घड़ी mode */

/* Write Register 5 */

#घोषणा	TxCRC_ENAB	0x1	/* Tx CRC Enable */
#घोषणा	RTS		0x2	/* RTS */
#घोषणा	SDLC_CRC	0x4	/* SDLC/CRC-16 */
#घोषणा	TxENAB		0x8	/* Tx Enable */
#घोषणा	SND_BRK		0x10	/* Send Break */
#घोषणा	Tx5		0x0	/* Tx 5 bits (or less)/अक्षरacter */
#घोषणा	Tx7		0x20	/* Tx 7 bits/अक्षरacter */
#घोषणा	Tx6		0x40	/* Tx 6 bits/अक्षरacter */
#घोषणा	Tx8		0x60	/* Tx 8 bits/अक्षरacter */
#घोषणा	DTR		0x80	/* DTR */

/* Write Register 6 (Sync bits 0-7/SDLC Address Field) */

/* Write Register 7 (Sync bits 8-15/SDLC 01111110) */

/* Write Register 8 (transmit buffer) */

/* Write Register 9 (Master पूर्णांकerrupt control) */
#घोषणा	VIS	1	/* Vector Includes Status */
#घोषणा	NV	2	/* No Vector */
#घोषणा	DLC	4	/* Disable Lower Chain */
#घोषणा	MIE	8	/* Master Interrupt Enable */
#घोषणा	STATHI	0x10	/* Status high */
#घोषणा	NORESET	0	/* No reset on ग_लिखो to R9 */
#घोषणा	CHRB	0x40	/* Reset channel B */
#घोषणा	CHRA	0x80	/* Reset channel A */
#घोषणा	FHWRES	0xc0	/* Force hardware reset */

/* Write Register 10 (misc control bits) */
#घोषणा	BIT6	1	/* 6 bit/8bit sync */
#घोषणा	LOOPMODE 2	/* SDLC Loop mode */
#घोषणा	ABUNDER	4	/* Abort/flag on SDLC xmit underrun */
#घोषणा	MARKIDLE 8	/* Mark/flag on idle */
#घोषणा	GAOP	0x10	/* Go active on poll */
#घोषणा	NRZ	0	/* NRZ mode */
#घोषणा	NRZI	0x20	/* NRZI mode */
#घोषणा	FM1	0x40	/* FM1 (transition = 1) */
#घोषणा	FM0	0x60	/* FM0 (transition = 0) */
#घोषणा	CRCPS	0x80	/* CRC Preset I/O */

/* Write Register 11 (Clock Mode control) */
#घोषणा	TRxCXT	0	/* TRxC = Xtal output */
#घोषणा	TRxCTC	1	/* TRxC = Transmit घड़ी */
#घोषणा	TRxCBR	2	/* TRxC = BR Generator Output */
#घोषणा	TRxCDP	3	/* TRxC = DPLL output */
#घोषणा	TRxCOI	4	/* TRxC O/I */
#घोषणा	TCRTxCP	0	/* Transmit घड़ी = RTxC pin */
#घोषणा	TCTRxCP	8	/* Transmit घड़ी = TRxC pin */
#घोषणा	TCBR	0x10	/* Transmit घड़ी = BR Generator output */
#घोषणा	TCDPLL	0x18	/* Transmit घड़ी = DPLL output */
#घोषणा	RCRTxCP	0	/* Receive घड़ी = RTxC pin */
#घोषणा	RCTRxCP	0x20	/* Receive घड़ी = TRxC pin */
#घोषणा	RCBR	0x40	/* Receive घड़ी = BR Generator output */
#घोषणा	RCDPLL	0x60	/* Receive घड़ी = DPLL output */
#घोषणा	RTxCX	0x80	/* RTxC Xtal/No Xtal */

/* Write Register 12 (lower byte of baud rate generator समय स्थिरant) */

/* Write Register 13 (upper byte of baud rate generator समय स्थिरant) */

/* Write Register 14 (Misc control bits) */
#घोषणा	BRENABL	1	/* Baud rate generator enable */
#घोषणा	BRSRC	2	/* Baud rate generator source */
#घोषणा	DTRREQ	4	/* DTR/Request function */
#घोषणा	AUTOECHO 8	/* Auto Echo */
#घोषणा	LOOPBAK	0x10	/* Local loopback */
#घोषणा	SEARCH	0x20	/* Enter search mode */
#घोषणा	RMC	0x40	/* Reset missing घड़ी */
#घोषणा	DISDPLL	0x60	/* Disable DPLL */
#घोषणा	SSBR	0x80	/* Set DPLL source = BR generator */
#घोषणा	SSRTxC	0xa0	/* Set DPLL source = RTxC */
#घोषणा	SFMM	0xc0	/* Set FM mode */
#घोषणा	SNRZI	0xe0	/* Set NRZI mode */

/* Write Register 15 (बाह्यal/status पूर्णांकerrupt control) */
#घोषणा PRIME	1	/* R5' etc रेजिस्टर access (Z85C30/230 only) */
#घोषणा	ZCIE	2	/* Zero count IE */
#घोषणा FIFOE	4	/* Z85230 only */
#घोषणा	DCDIE	8	/* DCD IE */
#घोषणा	SYNCIE	0x10	/* Sync/hunt IE */
#घोषणा	CTSIE	0x20	/* CTS IE */
#घोषणा	TxUIE	0x40	/* Tx Underrun/EOM IE */
#घोषणा	BRKIE	0x80	/* Break/Abort IE */


/* Read Register 0 */
#घोषणा	Rx_CH_AV	0x1	/* Rx Character Available */
#घोषणा	ZCOUNT		0x2	/* Zero count */
#घोषणा	Tx_BUF_EMP	0x4	/* Tx Buffer empty */
#घोषणा	DCD		0x8	/* DCD */
#घोषणा	SYNC_HUNT	0x10	/* Sync/hunt */
#घोषणा	CTS		0x20	/* CTS */
#घोषणा	TxEOM		0x40	/* Tx underrun */
#घोषणा	BRK_ABRT	0x80	/* Break/Abort */

/* Read Register 1 */
#घोषणा	ALL_SNT		0x1	/* All sent */
/* Residue Data क्रम 8 Rx bits/अक्षर programmed */
#घोषणा	RES3		0x8	/* 0/3 */
#घोषणा	RES4		0x4	/* 0/4 */
#घोषणा	RES5		0xc	/* 0/5 */
#घोषणा	RES6		0x2	/* 0/6 */
#घोषणा	RES7		0xa	/* 0/7 */
#घोषणा	RES8		0x6	/* 0/8 */
#घोषणा	RES18		0xe	/* 1/8 */
#घोषणा	RES28		0x0	/* 2/8 */
/* Special Rx Condition Interrupts */
#घोषणा	PAR_ERR		0x10	/* Parity error */
#घोषणा	Rx_OVR		0x20	/* Rx Overrun Error */
#घोषणा	CRC_ERR		0x40	/* CRC/Framing Error */
#घोषणा	END_FR		0x80	/* End of Frame (SDLC) */

/* Read Register 2 (channel b only) - Interrupt vector */

/* Read Register 3 (पूर्णांकerrupt pending रेजिस्टर) ch a only */
#घोषणा	CHBEXT	0x1		/* Channel B Ext/Stat IP */
#घोषणा	CHBTxIP	0x2		/* Channel B Tx IP */
#घोषणा	CHBRxIP	0x4		/* Channel B Rx IP */
#घोषणा	CHAEXT	0x8		/* Channel A Ext/Stat IP */
#घोषणा	CHATxIP	0x10		/* Channel A Tx IP */
#घोषणा	CHARxIP	0x20		/* Channel A Rx IP */

/* Read Register 8 (receive data रेजिस्टर) */

/* Read Register 10  (misc status bits) */
#घोषणा	ONLOOP	2		/* On loop */
#घोषणा	LOOPSEND 0x10		/* Loop sending */
#घोषणा	CLK2MIS	0x40		/* Two घड़ीs missing */
#घोषणा	CLK1MIS	0x80		/* One घड़ी missing */

/* Read Register 12 (lower byte of baud rate generator स्थिरant) */

/* Read Register 13 (upper byte of baud rate generator स्थिरant) */

/* Read Register 15 (value of WR 15) */


/*
 *	Interrupt handling functions क्रम this SCC
 */

काष्ठा z8530_channel;
 
काष्ठा z8530_irqhandler
अणु
	व्योम (*rx)(काष्ठा z8530_channel *);
	व्योम (*tx)(काष्ठा z8530_channel *);
	व्योम (*status)(काष्ठा z8530_channel *);
पूर्ण;

/*
 *	A channel of the Z8530
 */

काष्ठा z8530_channel
अणु
	काष्ठा		z8530_irqhandler *irqs;		/* IRQ handlers */
	/*
	 *	Synchronous
	 */
	u16		count;		/* Buyes received */
	u16		max;		/* Most we can receive this frame */
	u16		mtu;		/* MTU of the device */
	u8		*dptr;		/* Poपूर्णांकer पूर्णांकo rx buffer */
	काष्ठा sk_buff	*skb;		/* Buffer dptr poपूर्णांकs पूर्णांकo */
	काष्ठा sk_buff	*skb2;		/* Pending buffer */
	u8		status;		/* Current DCD */
	u8		dcdcheck;	/* which bit to check क्रम line */
	u8		sync;		/* Set अगर in sync mode */

	u8		regs[32];	/* Register map क्रम the chip */
	u8		pendregs[32];	/* Pending रेजिस्टर values */
	
	काष्ठा sk_buff 	*tx_skb;	/* Buffer being transmitted */
	काष्ठा sk_buff  *tx_next_skb;	/* Next transmit buffer */
	u8		*tx_ptr;	/* Byte poपूर्णांकer पूर्णांकo the buffer */
	u8		*tx_next_ptr;	/* Next poपूर्णांकer to use */
	u8		*tx_dma_buf[2];	/* TX flip buffers क्रम DMA */
	u8		tx_dma_used;	/* Flip buffer usage toggler */
	u16		txcount;	/* Count of bytes to transmit */
	
	व्योम		(*rx_function)(काष्ठा z8530_channel *, काष्ठा sk_buff *);
	
	/*
	 *	Sync DMA
	 */
	
	u8		rxdma;		/* DMA channels */
	u8		txdma;		
	u8		rxdma_on;	/* DMA active अगर flag set */
	u8		txdma_on;
	u8		dma_num;	/* Buffer we are DMAing पूर्णांकo */
	u8		dma_पढ़ोy;	/* Is the other buffer मुक्त */
	u8		dma_tx;		/* TX is to use DMA */
	u8		*rx_buf[2];	/* The flip buffers */
	
	/*
	 *	System
	 */
	 
	काष्ठा z8530_dev *dev;		/* Z85230 chip instance we are from */
	अचिन्हित दीर्घ	ctrlio;		/* I/O ports */
	अचिन्हित दीर्घ	dataio;

	/*
	 *	For PC we encode this way.
	 */	
#घोषणा Z8530_PORT_SLEEP	0x80000000
#घोषणा Z8530_PORT_OF(x)	((x)&0xFFFF)

	u32		rx_overrun;		/* Overruns - not करोne yet */
	u32		rx_crc_err;

	/*
	 *	Bound device poपूर्णांकers
	 */

	व्योम		*निजी;	/* For our owner */
	काष्ठा net_device	*netdevice;	/* Network layer device */

	spinlock_t		*lock;	  /* Device lock */
पूर्ण;

/*
 *	Each Z853x0 device.
 */

काष्ठा z8530_dev
अणु
	अक्षर *name;	/* Device instance name */
	काष्ठा z8530_channel chanA;	/* SCC channel A */
	काष्ठा z8530_channel chanB;	/* SCC channel B */
	पूर्णांक type;
#घोषणा Z8530	0	/* NMOS dinosaur */	
#घोषणा Z85C30	1	/* CMOS - better */
#घोषणा Z85230	2	/* CMOS with real FIFO */
	पूर्णांक irq;	/* Interrupt क्रम the device */
	पूर्णांक active;	/* Soft पूर्णांकerrupt enable - the Mac करोesn't 
			   always have a hard disable on its 8530s... */
	spinlock_t lock;
पूर्ण;


/*
 *	Functions
 */
 
बाह्य u8 z8530_dead_port[];
बाह्य u8 z8530_hdlc_kilostream_85230[];
बाह्य u8 z8530_hdlc_kilostream[];
irqवापस_t z8530_पूर्णांकerrupt(पूर्णांक, व्योम *);
व्योम z8530_describe(काष्ठा z8530_dev *, अक्षर *mapping, अचिन्हित दीर्घ io);
पूर्णांक z8530_init(काष्ठा z8530_dev *);
पूर्णांक z8530_shutकरोwn(काष्ठा z8530_dev *);
पूर्णांक z8530_sync_खोलो(काष्ठा net_device *, काष्ठा z8530_channel *);
पूर्णांक z8530_sync_बंद(काष्ठा net_device *, काष्ठा z8530_channel *);
पूर्णांक z8530_sync_dma_खोलो(काष्ठा net_device *, काष्ठा z8530_channel *);
पूर्णांक z8530_sync_dma_बंद(काष्ठा net_device *, काष्ठा z8530_channel *);
पूर्णांक z8530_sync_txdma_खोलो(काष्ठा net_device *, काष्ठा z8530_channel *);
पूर्णांक z8530_sync_txdma_बंद(काष्ठा net_device *, काष्ठा z8530_channel *);
पूर्णांक z8530_channel_load(काष्ठा z8530_channel *, u8 *);
netdev_tx_t z8530_queue_xmit(काष्ठा z8530_channel *c, काष्ठा sk_buff *skb);
व्योम z8530_null_rx(काष्ठा z8530_channel *c, काष्ठा sk_buff *skb);


/*
 *	Standard पूर्णांकerrupt vector sets
 */
 
बाह्य काष्ठा z8530_irqhandler z8530_sync, z8530_async, z8530_nop;

/*
 *	Asynchronous Interfacing
 */

/*
 * The size of the serial xmit buffer is 1 page, or 4096 bytes
 */

#घोषणा SERIAL_XMIT_SIZE 4096
#घोषणा WAKEUP_CHARS	256

/*
 * Events are used to schedule things to happen at समयr-पूर्णांकerrupt
 * समय, instead of at rs पूर्णांकerrupt समय.
 */
#घोषणा RS_EVENT_WRITE_WAKEUP	0

/* Internal flags used only by kernel/chr_drv/serial.c */
#घोषणा ZILOG_INITIALIZED	0x80000000 /* Serial port was initialized */
#घोषणा ZILOG_CALLOUT_ACTIVE	0x40000000 /* Call out device is active */
#घोषणा ZILOG_NORMAL_ACTIVE	0x20000000 /* Normal device is active */
#घोषणा ZILOG_BOOT_AUTOCONF	0x10000000 /* Autoconfigure port on bootup */
#घोषणा ZILOG_CLOSING		0x08000000 /* Serial port is closing */
#घोषणा ZILOG_CTS_FLOW		0x04000000 /* Do CTS flow control */
#घोषणा ZILOG_CHECK_CD		0x02000000 /* i.e., CLOCAL */

#पूर्ण_अगर /* !(_Z8530_H) */
