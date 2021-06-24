<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/************************************************************************
 * Copyright 2003 Digi International (www.digi.com)
 *
 * Copyright (C) 2004 IBM Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 * Scott H Kilau <Scott_Kilau@digi.com>
 * Wendy Xiong   <wendyx@us.ibm.com>
 *
 ***********************************************************************/

#अगर_अघोषित __JSM_DRIVER_H
#घोषणा __JSM_DRIVER_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>	/* To pick up the varions Linux types */
#समावेश <linux/tty.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/device.h>

/*
 * Debugging levels can be set using debug insmod variable
 * They can also be compiled out completely.
 */
क्रमागत अणु
	DBG_INIT	= 0x01,
	DBG_BASIC	= 0x02,
	DBG_CORE	= 0x04,
	DBG_OPEN	= 0x08,
	DBG_CLOSE	= 0x10,
	DBG_READ	= 0x20,
	DBG_WRITE	= 0x40,
	DBG_IOCTL	= 0x80,
	DBG_PROC	= 0x100,
	DBG_PARAM	= 0x200,
	DBG_PSCAN	= 0x400,
	DBG_EVENT	= 0x800,
	DBG_DRAIN	= 0x1000,
	DBG_MSIGS	= 0x2000,
	DBG_MGMT	= 0x4000,
	DBG_INTR	= 0x8000,
	DBG_CARR	= 0x10000,
पूर्ण;

#घोषणा jsm_dbg(nlevel, pdev, fmt, ...)				\
करो अणु								\
	अगर (DBG_##nlevel & jsm_debug)				\
		dev_dbg(pdev->dev, fmt, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा	MAXLINES	256
#घोषणा MAXPORTS	8
#घोषणा MAX_STOPS_SENT	5

/* Board ids */
#घोषणा PCI_DEVICE_ID_CLASSIC_4		0x0028
#घोषणा PCI_DEVICE_ID_CLASSIC_8		0x0029
#घोषणा PCI_DEVICE_ID_CLASSIC_4_422	0x00D0
#घोषणा PCI_DEVICE_ID_CLASSIC_8_422	0x00D1
#घोषणा PCI_DEVICE_ID_NEO_4             0x00B0
#घोषणा PCI_DEVICE_ID_NEO_1_422         0x00CC
#घोषणा PCI_DEVICE_ID_NEO_1_422_485     0x00CD
#घोषणा PCI_DEVICE_ID_NEO_2_422_485     0x00CE
#घोषणा PCIE_DEVICE_ID_NEO_8            0x00F0
#घोषणा PCIE_DEVICE_ID_NEO_4            0x00F1
#घोषणा PCIE_DEVICE_ID_NEO_4RJ45        0x00F2
#घोषणा PCIE_DEVICE_ID_NEO_8RJ45        0x00F3

/* Board type definitions */

#घोषणा T_NEO		0000
#घोषणा T_CLASSIC	0001
#घोषणा T_PCIBUS	0400

/* Board State Definitions */

#घोषणा BD_RUNNING	0x0
#घोषणा BD_REASON	0x7f
#घोषणा BD_NOTFOUND	0x1
#घोषणा BD_NOIOPORT	0x2
#घोषणा BD_NOMEM	0x3
#घोषणा BD_NOBIOS	0x4
#घोषणा BD_NOFEP	0x5
#घोषणा BD_FAILED	0x6
#घोषणा BD_ALLOCATED	0x7
#घोषणा BD_TRIBOOT	0x8
#घोषणा BD_BADKME	0x80


/* 4 extra क्रम alignment play space */
#घोषणा WRITEBUFLEN	((4096) + 4)

#घोषणा JSM_VERSION	"jsm: 1.2-1-INKERNEL"
#घोषणा JSM_PARTNUM	"40002438_A-INKERNEL"

काष्ठा jsm_board;
काष्ठा jsm_channel;

/************************************************************************
 * Per board operations काष्ठाure					*
 ************************************************************************/
काष्ठा board_ops अणु
	irq_handler_t पूर्णांकr;
	व्योम (*uart_init)(काष्ठा jsm_channel *ch);
	व्योम (*uart_off)(काष्ठा jsm_channel *ch);
	व्योम (*param)(काष्ठा jsm_channel *ch);
	व्योम (*निश्चित_modem_संकेतs)(काष्ठा jsm_channel *ch);
	व्योम (*flush_uart_ग_लिखो)(काष्ठा jsm_channel *ch);
	व्योम (*flush_uart_पढ़ो)(काष्ठा jsm_channel *ch);
	व्योम (*disable_receiver)(काष्ठा jsm_channel *ch);
	व्योम (*enable_receiver)(काष्ठा jsm_channel *ch);
	व्योम (*send_अवरोध)(काष्ठा jsm_channel *ch);
	व्योम (*clear_अवरोध)(काष्ठा jsm_channel *ch);
	व्योम (*send_start_अक्षरacter)(काष्ठा jsm_channel *ch);
	व्योम (*send_stop_अक्षरacter)(काष्ठा jsm_channel *ch);
	व्योम (*copy_data_from_queue_to_uart)(काष्ठा jsm_channel *ch);
	u32 (*get_uart_bytes_left)(काष्ठा jsm_channel *ch);
	व्योम (*send_immediate_अक्षर)(काष्ठा jsm_channel *ch, अचिन्हित अक्षर);
पूर्ण;


/*
 *	Per-board inक्रमmation
 */
काष्ठा jsm_board
अणु
	पूर्णांक		boardnum;	/* Board number: 0-32 */

	पूर्णांक		type;		/* Type of board */
	u8		rev;		/* PCI revision ID */
	काष्ठा pci_dev	*pci_dev;
	u32		maxports;	/* MAX ports this board can handle */

	spinlock_t	bd_पूर्णांकr_lock;	/* Used to protect the poller tasklet and
					 * the पूर्णांकerrupt routine from each other.
					 */

	u32		nasync;		/* Number of ports on card */

	u32		irq;		/* Interrupt request number */

	u64		membase;	/* Start of base memory of the card */
	u64		membase_end;	/* End of base memory of the card */

	u8	__iomem *re_map_membase;/* Remapped memory of the card */

	u64		iobase;		/* Start of io base of the card */
	u64		iobase_end;	/* End of io base of the card */

	u32		bd_uart_offset;	/* Space between each UART */

	काष्ठा jsm_channel *channels[MAXPORTS]; /* array of poपूर्णांकers to our channels. */

	u32		bd_भागidend;	/* Board/UARTs specअगरic भागidend */

	काष्ठा board_ops *bd_ops;

	काष्ठा list_head jsm_board_entry;
पूर्ण;

/************************************************************************
 * Device flag definitions क्रम ch_flags.
 ************************************************************************/
#घोषणा CH_PRON		0x0001		/* Prपूर्णांकer on string		*/
#घोषणा CH_STOP		0x0002		/* Output is stopped		*/
#घोषणा CH_STOPI	0x0004		/* Input is stopped		*/
#घोषणा CH_CD		0x0008		/* Carrier is present		*/
#घोषणा CH_FCAR		0x0010		/* Carrier क्रमced on		*/
#घोषणा CH_HANGUP	0x0020		/* Hangup received		*/

#घोषणा CH_RECEIVER_OFF	0x0040		/* Receiver is off		*/
#घोषणा CH_OPENING	0x0080		/* Port in fragile खोलो state	*/
#घोषणा CH_CLOSING	0x0100		/* Port in fragile बंद state	*/
#घोषणा CH_FIFO_ENABLED 0x0200		/* Port has FIFOs enabled	*/
#घोषणा CH_TX_FIFO_EMPTY 0x0400		/* TX Fअगरo is completely empty	*/
#घोषणा CH_TX_FIFO_LWM	0x0800		/* TX Fअगरo is below Low Water	*/
#घोषणा CH_BREAK_SENDING 0x1000		/* Break is being sent		*/
#घोषणा CH_LOOPBACK 0x2000		/* Channel is in lookback mode	*/
#घोषणा CH_BAUD0	0x08000		/* Used क्रम checking B0 transitions */

/* Our Read/Error queue sizes */
#घोषणा RQUEUEMASK	0x1FFF		/* 8 K - 1 */
#घोषणा EQUEUEMASK	0x1FFF		/* 8 K - 1 */
#घोषणा RQUEUESIZE	(RQUEUEMASK + 1)
#घोषणा EQUEUESIZE	RQUEUESIZE


/************************************************************************
 * Channel inक्रमmation काष्ठाure.
 ************************************************************************/
काष्ठा jsm_channel अणु
	काष्ठा uart_port uart_port;
	काष्ठा jsm_board	*ch_bd;		/* Board काष्ठाure poपूर्णांकer	*/

	spinlock_t	ch_lock;	/* provide क्रम serialization */
	रुको_queue_head_t ch_flags_रुको;

	u32		ch_portnum;	/* Port number, 0 offset.	*/
	u32		ch_खोलो_count;	/* खोलो count			*/
	u32		ch_flags;	/* Channel flags		*/

	u64		ch_बंद_delay;	/* How दीर्घ we should drop RTS/DTR क्रम */

	tcflag_t	ch_c_अगरlag;	/* channel अगरlags		*/
	tcflag_t	ch_c_cflag;	/* channel cflags		*/
	tcflag_t	ch_c_oflag;	/* channel oflags		*/
	tcflag_t	ch_c_lflag;	/* channel lflags		*/
	u8		ch_stopc;	/* Stop अक्षरacter		*/
	u8		ch_startc;	/* Start अक्षरacter		*/

	u8		ch_mostat;	/* FEP output modem status	*/
	u8		ch_mistat;	/* FEP input modem status	*/

	/* Poपूर्णांकers to the "mapped" UART काष्ठाs */
	काष्ठा neo_uart_काष्ठा __iomem *ch_neo_uart; /* NEO card */
	काष्ठा cls_uart_काष्ठा __iomem *ch_cls_uart; /* Classic card */

	u8		ch_cached_lsr;	/* Cached value of the LSR रेजिस्टर */

	u8		*ch_rqueue;	/* Our पढ़ो queue buffer - दो_स्मृति'ed */
	u16		ch_r_head;	/* Head location of the पढ़ो queue */
	u16		ch_r_tail;	/* Tail location of the पढ़ो queue */

	u8		*ch_equeue;	/* Our error queue buffer - दो_स्मृति'ed */
	u16		ch_e_head;	/* Head location of the error queue */
	u16		ch_e_tail;	/* Tail location of the error queue */

	u64		ch_rxcount;	/* total of data received so far */
	u64		ch_txcount;	/* total of data transmitted so far */

	u8		ch_r_tlevel;	/* Receive Trigger level */
	u8		ch_t_tlevel;	/* Transmit Trigger level */

	u8		ch_r_watermark;	/* Receive Watermark */


	u32		ch_stops_sent;	/* How many बार I have sent a stop अक्षरacter
					 * to try to stop the other guy sending.
					 */
	u64		ch_err_parity;	/* Count of parity errors on channel */
	u64		ch_err_frame;	/* Count of framing errors on channel */
	u64		ch_err_अवरोध;	/* Count of अवरोधs on channel */
	u64		ch_err_overrun; /* Count of overruns on channel */

	u64		ch_xon_sends;	/* Count of xons transmitted */
	u64		ch_xoff_sends;	/* Count of xoffs transmitted */
पूर्ण;

/************************************************************************
 * Per channel/port Classic UART काष्ठाures				*
 ************************************************************************
 *		Base Structure Entries Usage Meanings to Host		*
 *									*
 *	W = पढ़ो ग_लिखो		R = पढ़ो only				*
 *			U = Unused.					*
 ************************************************************************/

काष्ठा cls_uart_काष्ठा अणु
	u8 txrx;	/* WR  RHR/THR - Holding Reg */
	u8 ier;		/* WR  IER - Interrupt Enable Reg */
	u8 isr_fcr;	/* WR  ISR/FCR - Interrupt Status Reg/Fअगरo Control Reg*/
	u8 lcr;		/* WR  LCR - Line Control Reg */
	u8 mcr;		/* WR  MCR - Modem Control Reg */
	u8 lsr;		/* WR  LSR - Line Status Reg */
	u8 msr;		/* WR  MSR - Modem Status Reg */
	u8 spr;		/* WR  SPR - Scratch Pad Reg */
पूर्ण;

/* Where to पढ़ो the पूर्णांकerrupt रेजिस्टर (8bits) */
#घोषणा UART_CLASSIC_POLL_ADDR_OFFSET	0x40

#घोषणा UART_EXAR654_ENHANCED_REGISTER_SET 0xBF

#घोषणा UART_16654_FCR_TXTRIGGER_8	0x0
#घोषणा UART_16654_FCR_TXTRIGGER_16	0x10
#घोषणा UART_16654_FCR_TXTRIGGER_32	0x20
#घोषणा UART_16654_FCR_TXTRIGGER_56	0x30

#घोषणा UART_16654_FCR_RXTRIGGER_8	0x0
#घोषणा UART_16654_FCR_RXTRIGGER_16	0x40
#घोषणा UART_16654_FCR_RXTRIGGER_56	0x80
#घोषणा UART_16654_FCR_RXTRIGGER_60	0xC0

#घोषणा UART_IIR_CTSRTS			0x20	/* Received CTS/RTS change of state */
#घोषणा UART_IIR_RDI_TIMEOUT		0x0C    /* Receiver data TIMEOUT */

/*
 * These are the EXTENDED definitions क्रम the Exar 654's Interrupt
 * Enable Register.
 */
#घोषणा UART_EXAR654_EFR_ECB      0x10    /* Enhanced control bit */
#घोषणा UART_EXAR654_EFR_IXON     0x2     /* Receiver compares Xon1/Xoff1 */
#घोषणा UART_EXAR654_EFR_IXOFF    0x8     /* Transmit Xon1/Xoff1 */
#घोषणा UART_EXAR654_EFR_RTSDTR   0x40    /* Auto RTS/DTR Flow Control Enable */
#घोषणा UART_EXAR654_EFR_CTSDSR   0x80    /* Auto CTS/DSR Flow COntrol Enable */

#घोषणा UART_EXAR654_XOFF_DETECT  0x1     /* Indicates whether chip saw an incoming XOFF अक्षर  */
#घोषणा UART_EXAR654_XON_DETECT   0x2     /* Indicates whether chip saw an incoming XON अक्षर */

#घोषणा UART_EXAR654_IER_XOFF     0x20    /* Xoff Interrupt Enable */
#घोषणा UART_EXAR654_IER_RTSDTR   0x40    /* Output Interrupt Enable */
#घोषणा UART_EXAR654_IER_CTSDSR   0x80    /* Input Interrupt Enable */

/************************************************************************
 * Per channel/port NEO UART काष्ठाure					*
 ************************************************************************
 *		Base Structure Entries Usage Meanings to Host		*
 *									*
 *	W = पढ़ो ग_लिखो		R = पढ़ो only				*
 *			U = Unused.					*
 ************************************************************************/

काष्ठा neo_uart_काष्ठा अणु
	 u8 txrx;		/* WR	RHR/THR - Holding Reg */
	 u8 ier;		/* WR	IER - Interrupt Enable Reg */
	 u8 isr_fcr;		/* WR	ISR/FCR - Interrupt Status Reg/Fअगरo Control Reg */
	 u8 lcr;		/* WR	LCR - Line Control Reg */
	 u8 mcr;		/* WR	MCR - Modem Control Reg */
	 u8 lsr;		/* WR	LSR - Line Status Reg */
	 u8 msr;		/* WR	MSR - Modem Status Reg */
	 u8 spr;		/* WR	SPR - Scratch Pad Reg */
	 u8 fctr;		/* WR	FCTR - Feature Control Reg */
	 u8 efr;		/* WR	EFR - Enhanced Function Reg */
	 u8 tfअगरo;		/* WR	TXCNT/TXTRG - Transmit FIFO Reg */
	 u8 rfअगरo;		/* WR	RXCNT/RXTRG - Receive FIFO Reg */
	 u8 xoffअक्षर1;	/* WR	XOFF 1 - XOff Character 1 Reg */
	 u8 xoffअक्षर2;	/* WR	XOFF 2 - XOff Character 2 Reg */
	 u8 xonअक्षर1;	/* WR	XON 1 - Xon Character 1 Reg */
	 u8 xonअक्षर2;	/* WR	XON 2 - XOn Character 2 Reg */

	 u8 reserved1[0x2ff - 0x200]; /* U	Reserved by Exar */
	 u8 txrxburst[64];	/* RW	64 bytes of RX/TX FIFO Data */
	 u8 reserved2[0x37f - 0x340]; /* U	Reserved by Exar */
	 u8 rxburst_with_errors[64];	/* R	64 bytes of RX FIFO Data + LSR */
पूर्ण;

/* Where to पढ़ो the extended पूर्णांकerrupt रेजिस्टर (32bits instead of 8bits) */
#घोषणा	UART_17158_POLL_ADDR_OFFSET	0x80

/*
 * These are the redefinitions क्रम the FCTR on the XR17C158, since
 * Exar made them dअगरferent than their earlier design. (XR16C854)
 */

/* These are only applicable when table D is selected */
#घोषणा UART_17158_FCTR_RTS_NODELAY	0x00
#घोषणा UART_17158_FCTR_RTS_4DELAY	0x01
#घोषणा UART_17158_FCTR_RTS_6DELAY	0x02
#घोषणा UART_17158_FCTR_RTS_8DELAY	0x03
#घोषणा UART_17158_FCTR_RTS_12DELAY	0x12
#घोषणा UART_17158_FCTR_RTS_16DELAY	0x05
#घोषणा UART_17158_FCTR_RTS_20DELAY	0x13
#घोषणा UART_17158_FCTR_RTS_24DELAY	0x06
#घोषणा UART_17158_FCTR_RTS_28DELAY	0x14
#घोषणा UART_17158_FCTR_RTS_32DELAY	0x07
#घोषणा UART_17158_FCTR_RTS_36DELAY	0x16
#घोषणा UART_17158_FCTR_RTS_40DELAY	0x08
#घोषणा UART_17158_FCTR_RTS_44DELAY	0x09
#घोषणा UART_17158_FCTR_RTS_48DELAY	0x10
#घोषणा UART_17158_FCTR_RTS_52DELAY	0x11

#घोषणा UART_17158_FCTR_RTS_IRDA	0x10
#घोषणा UART_17158_FCTR_RS485		0x20
#घोषणा UART_17158_FCTR_TRGA		0x00
#घोषणा UART_17158_FCTR_TRGB		0x40
#घोषणा UART_17158_FCTR_TRGC		0x80
#घोषणा UART_17158_FCTR_TRGD		0xC0

/* 17158 trigger table selects.. */
#घोषणा UART_17158_FCTR_BIT6		0x40
#घोषणा UART_17158_FCTR_BIT7		0x80

/* 17158 TX/RX memmapped buffer offsets */
#घोषणा UART_17158_RX_FIFOSIZE		64
#घोषणा UART_17158_TX_FIFOSIZE		64

/* 17158 Extended IIR's */
#घोषणा UART_17158_IIR_RDI_TIMEOUT	0x0C	/* Receiver data TIMEOUT */
#घोषणा UART_17158_IIR_XONXOFF		0x10	/* Received an XON/XOFF अक्षर */
#घोषणा UART_17158_IIR_HWFLOW_STATE_CHANGE 0x20	/* CTS/DSR or RTS/DTR state change */
#घोषणा UART_17158_IIR_FIFO_ENABLED	0xC0	/* 16550 FIFOs are Enabled */

/*
 * These are the extended पूर्णांकerrupts that get sent
 * back to us from the UART's 32bit पूर्णांकerrupt रेजिस्टर
 */
#घोषणा UART_17158_RX_LINE_STATUS	0x1	/* RX Ready */
#घोषणा UART_17158_RXRDY_TIMEOUT	0x2	/* RX Ready Timeout */
#घोषणा UART_17158_TXRDY		0x3	/* TX Ready */
#घोषणा UART_17158_MSR			0x4	/* Modem State Change */
#घोषणा UART_17158_TX_AND_FIFO_CLR	0x40	/* Transmitter Holding Reg Empty */
#घोषणा UART_17158_RX_FIFO_DATA_ERROR	0x80	/* UART detected an RX FIFO Data error */

/*
 * These are the EXTENDED definitions क्रम the 17C158's Interrupt
 * Enable Register.
 */
#घोषणा UART_17158_EFR_ECB	0x10	/* Enhanced control bit */
#घोषणा UART_17158_EFR_IXON	0x2	/* Receiver compares Xon1/Xoff1 */
#घोषणा UART_17158_EFR_IXOFF	0x8	/* Transmit Xon1/Xoff1 */
#घोषणा UART_17158_EFR_RTSDTR	0x40	/* Auto RTS/DTR Flow Control Enable */
#घोषणा UART_17158_EFR_CTSDSR	0x80	/* Auto CTS/DSR Flow COntrol Enable */

#घोषणा UART_17158_XOFF_DETECT	0x1	/* Indicates whether chip saw an incoming XOFF अक्षर */
#घोषणा UART_17158_XON_DETECT	0x2	/* Indicates whether chip saw an incoming XON अक्षर */

#घोषणा UART_17158_IER_RSVD1	0x10	/* Reserved by Exar */
#घोषणा UART_17158_IER_XOFF	0x20	/* Xoff Interrupt Enable */
#घोषणा UART_17158_IER_RTSDTR	0x40	/* Output Interrupt Enable */
#घोषणा UART_17158_IER_CTSDSR	0x80	/* Input Interrupt Enable */

#घोषणा PCI_DEVICE_NEO_2DB9_PCI_NAME		"Neo 2 - DB9 Universal PCI"
#घोषणा PCI_DEVICE_NEO_2DB9PRI_PCI_NAME		"Neo 2 - DB9 Universal PCI - Powered Ring Indicator"
#घोषणा PCI_DEVICE_NEO_2RJ45_PCI_NAME		"Neo 2 - RJ45 Universal PCI"
#घोषणा PCI_DEVICE_NEO_2RJ45PRI_PCI_NAME	"Neo 2 - RJ45 Universal PCI - Powered Ring Indicator"
#घोषणा PCIE_DEVICE_NEO_IBM_PCI_NAME		"Neo 4 - PCI Express - IBM"

/*
 * Our Global Variables.
 */
बाह्य काष्ठा	uart_driver jsm_uart_driver;
बाह्य काष्ठा	board_ops jsm_neo_ops;
बाह्य काष्ठा	board_ops jsm_cls_ops;
बाह्य पूर्णांक	jsm_debug;

/*************************************************************************
 *
 * Prototypes क्रम non-अटल functions used in more than one module
 *
 *************************************************************************/
पूर्णांक jsm_tty_init(काष्ठा jsm_board *);
पूर्णांक jsm_uart_port_init(काष्ठा jsm_board *);
पूर्णांक jsm_हटाओ_uart_port(काष्ठा jsm_board *);
व्योम jsm_input(काष्ठा jsm_channel *ch);
व्योम jsm_check_queue_flow_control(काष्ठा jsm_channel *ch);

#पूर्ण_अगर
