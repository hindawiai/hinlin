<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Toshiba TC86C001 ("Goku-S") USB Device Controller driver
 *
 * Copyright (C) 2000-2002 Lineo
 *      by Stuart Lynne, Tom Rushworth, and Bruce Balden
 * Copyright (C) 2002 Toshiba Corporation
 * Copyright (C) 2003 MontaVista Software (source@mvista.com)
 */

/*
 * PCI BAR 0 poपूर्णांकs to these रेजिस्टरs.
 */
काष्ठा goku_udc_regs अणु
	/* irq management */
	u32	पूर्णांक_status;		/* 0x000 */
	u32	पूर्णांक_enable;
#घोषणा INT_SUSPEND		0x00001		/* or resume */
#घोषणा INT_USBRESET		0x00002
#घोषणा INT_ENDPOINT0		0x00004
#घोषणा INT_SETUP		0x00008
#घोषणा INT_STATUS		0x00010
#घोषणा INT_STATUSNAK		0x00020
#घोषणा INT_EPxDATASET(n)	(0x00020 << (n))	/* 0 < n < 4 */
#	define INT_EP1DATASET		0x00040
#	define INT_EP2DATASET		0x00080
#	define INT_EP3DATASET		0x00100
#घोषणा INT_EPnNAK(n)		(0x00100 << (n))	/* 0 < n < 4 */
#	define INT_EP1NAK		0x00200
#	define INT_EP2NAK		0x00400
#	define INT_EP3NAK		0x00800
#घोषणा INT_SOF			0x01000
#घोषणा INT_ERR			0x02000
#घोषणा INT_MSTWRSET		0x04000
#घोषणा INT_MSTWREND		0x08000
#घोषणा INT_MSTWRTMOUT		0x10000
#घोषणा INT_MSTRDEND		0x20000
#घोषणा INT_SYSERROR		0x40000
#घोषणा INT_PWRDETECT		0x80000

#घोषणा	INT_DEVWIDE \
	(INT_PWRDETECT|INT_SYSERROR/*|INT_ERR*/|INT_USBRESET|INT_SUSPEND)
#घोषणा	INT_EP0 \
	(INT_SETUP|INT_ENDPOINT0/*|INT_STATUS*/|INT_STATUSNAK)

	u32	dma_master;
#घोषणा MST_EOPB_DIS		0x0800
#घोषणा MST_EOPB_ENA		0x0400
#घोषणा MST_TIMEOUT_DIS		0x0200
#घोषणा MST_TIMEOUT_ENA		0x0100
#घोषणा MST_RD_EOPB		0x0080		/* ग_लिखो-only */
#घोषणा MST_RD_RESET		0x0040
#घोषणा MST_WR_RESET		0x0020
#घोषणा MST_RD_ENA		0x0004		/* 1:start, 0:ignore */
#घोषणा MST_WR_ENA		0x0002		/* 1:start, 0:ignore */
#घोषणा MST_CONNECTION		0x0001		/* 0 क्रम ep1out/ep2in */

#घोषणा MST_R_BITS		(MST_EOPB_DIS|MST_EOPB_ENA \
					|MST_RD_ENA|MST_RD_RESET)
#घोषणा MST_W_BITS		(MST_TIMEOUT_DIS|MST_TIMEOUT_ENA \
					|MST_WR_ENA|MST_WR_RESET)
#घोषणा MST_RW_BITS		(MST_R_BITS|MST_W_BITS \
					|MST_CONNECTION)

/* these values assume (dma_master & MST_CONNECTION) == 0 */
#घोषणा UDC_MSTWR_ENDPOINT        1
#घोषणा UDC_MSTRD_ENDPOINT        2

	/* dma master ग_लिखो */
	u32	out_dma_start;
	u32	out_dma_end;
	u32	out_dma_current;

	/* dma master पढ़ो */
	u32	in_dma_start;
	u32	in_dma_end;
	u32	in_dma_current;

	u32	घातer_detect;
#घोषणा PW_DETECT		0x04
#घोषणा PW_RESETB		0x02
#घोषणा PW_PULLUP		0x01

	u8	_reserved0 [0x1d8];

	/* endpoपूर्णांक रेजिस्टरs */
	u32	ep_fअगरo [4];		/* 0x200 */
	u8	_reserved1 [0x10];
	u32	ep_mode [4];		/* only 1-3 valid */
	u8	_reserved2 [0x10];

	u32	ep_status [4];
#घोषणा EPxSTATUS_TOGGLE	0x40
#घोषणा EPxSTATUS_SUSPEND	0x20
#घोषणा EPxSTATUS_EP_MASK	(0x07<<2)
#	define EPxSTATUS_EP_READY	(0<<2)
#	define EPxSTATUS_EP_DATAIN	(1<<2)
#	define EPxSTATUS_EP_FULL	(2<<2)
#	define EPxSTATUS_EP_TX_ERR	(3<<2)
#	define EPxSTATUS_EP_RX_ERR	(4<<2)
#	define EPxSTATUS_EP_BUSY	(5<<2)
#	define EPxSTATUS_EP_STALL	(6<<2)
#	define EPxSTATUS_EP_INVALID	(7<<2)
#घोषणा EPxSTATUS_FIFO_DISABLE	0x02
#घोषणा EPxSTATUS_STAGE_ERROR	0x01

	u8	_reserved3 [0x10];
	u32	EPxSizeLA[4];
#घोषणा PACKET_ACTIVE		(1<<7)
#घोषणा DATASIZE		0x7f
	u8	_reserved3a [0x10];
	u32	EPxSizeLB[4];		/* only 1,2 valid */
	u8	_reserved3b [0x10];
	u32	EPxSizeHA[4];		/* only 1-3 valid */
	u8	_reserved3c [0x10];
	u32	EPxSizeHB[4];		/* only 1,2 valid */
	u8	_reserved4[0x30];

	/* SETUP packet contents */
	u32	bRequestType;		/* 0x300 */
	u32	bRequest;
	u32	wValueL;
	u32	wValueH;
	u32	wIndexL;
	u32	wIndexH;
	u32	wLengthL;
	u32	wLengthH;

	/* command पूर्णांकeraction/handshaking */
	u32	SetupRecv;		/* 0x320 */
	u32	CurrConfig;
	u32	StdRequest;
	u32	Request;
	u32	DataSet;
#घोषणा DATASET_A(epnum)	(1<<(2*(epnum)))
#घोषणा DATASET_B(epnum)	(2<<(2*(epnum)))
#घोषणा DATASET_AB(epnum)	(3<<(2*(epnum)))
	u8	_reserved5[4];

	u32	UsbState;
#घोषणा USBSTATE_CONFIGURED	0x04
#घोषणा USBSTATE_ADDRESSED	0x02
#घोषणा USBSTATE_DEFAULT	0x01

	u32	EOP;

	u32	Command;		/* 0x340 */
#घोषणा COMMAND_SETDATA0	2
#घोषणा COMMAND_RESET		3
#घोषणा COMMAND_STALL		4
#घोषणा COMMAND_INVALID		5
#घोषणा COMMAND_FIFO_DISABLE	7
#घोषणा COMMAND_FIFO_ENABLE	8
#घोषणा COMMAND_INIT_DESCRIPTOR	9
#घोषणा COMMAND_FIFO_CLEAR	10	/* also stall */
#घोषणा COMMAND_STALL_CLEAR	11
#घोषणा COMMAND_EP(n)		((n) << 4)

	u32	EPxSingle;
	u8	_reserved6[4];
	u32	EPxBCS;
	u8	_reserved7[8];
	u32	IntControl;
#घोषणा ICONTROL_STATUSNAK	1
	u8	_reserved8[4];

	u32	reqmode;	// 0x360 standard request mode, low 8 bits
#घोषणा G_REQMODE_SET_INTF	(1<<7)
#घोषणा G_REQMODE_GET_INTF	(1<<6)
#घोषणा G_REQMODE_SET_CONF	(1<<5)
#घोषणा G_REQMODE_GET_CONF	(1<<4)
#घोषणा G_REQMODE_GET_DESC	(1<<3)
#घोषणा G_REQMODE_SET_FEAT	(1<<2)
#घोषणा G_REQMODE_CLEAR_FEAT	(1<<1)
#घोषणा G_REQMODE_GET_STATUS	(1<<0)

	u32	ReqMode;
	u8	_reserved9[0x18];
	u32	PortStatus;		/* 0x380 */
	u8	_reserved10[8];
	u32	address;
	u32	buff_test;
	u8	_reserved11[4];
	u32	UsbReady;
	u8	_reserved12[4];
	u32	SetDescStall;		/* 0x3a0 */
	u8	_reserved13[0x45c];

	/* hardware could handle limited GET_DESCRIPTOR duties */
#घोषणा	DESC_LEN	0x80
	u32	descriptors[DESC_LEN];	/* 0x800 */
	u8	_reserved14[0x600];

पूर्ण __attribute__ ((packed));

#घोषणा	MAX_FIFO_SIZE	64
#घोषणा	MAX_EP0_SIZE	8		/* ep0 fअगरo is bigger, though */


/*-------------------------------------------------------------------------*/

/* DRIVER DATA STRUCTURES and UTILITIES */

काष्ठा goku_ep अणु
	काष्ठा usb_ep				ep;
	काष्ठा goku_udc				*dev;
	अचिन्हित दीर्घ				irqs;

	अचिन्हित				num:8,
						dma:1,
						is_in:1,
						stopped:1;

	/* analogous to a host-side qh */
	काष्ठा list_head			queue;

	u32 __iomem				*reg_fअगरo;
	u32 __iomem				*reg_mode;
	u32 __iomem				*reg_status;
पूर्ण;

काष्ठा goku_request अणु
	काष्ठा usb_request		req;
	काष्ठा list_head		queue;

	अचिन्हित			mapped:1;
पूर्ण;

क्रमागत ep0state अणु
	EP0_DISCONNECT,		/* no host */
	EP0_IDLE,		/* between STATUS ack and SETUP report */
	EP0_IN, EP0_OUT,	/* data stage */
	EP0_STATUS,		/* status stage */
	EP0_STALL,		/* data or status stages */
	EP0_SUSPEND,		/* usb suspend */
पूर्ण;

काष्ठा goku_udc अणु
	/* each pci device provides one gadget, several endpoपूर्णांकs */
	काष्ठा usb_gadget		gadget;
	spinlock_t			lock;
	काष्ठा goku_ep			ep[4];
	काष्ठा usb_gadget_driver	*driver;

	क्रमागत ep0state			ep0state;
	अचिन्हित			got_irq:1,
					got_region:1,
					req_config:1,
					configured:1,
					enabled:1;

	/* pci state used to access those endpoपूर्णांकs */
	काष्ठा pci_dev			*pdev;
	काष्ठा goku_udc_regs __iomem	*regs;
	u32				पूर्णांक_enable;

	/* statistics... */
	अचिन्हित दीर्घ			irqs;
पूर्ण;
#घोषणा to_goku_udc(g)		(container_of((g), काष्ठा goku_udc, gadget))

/*-------------------------------------------------------------------------*/

#घोषणा xprपूर्णांकk(dev,level,fmt,args...) \
	prपूर्णांकk(level "%s %s: " fmt , driver_name , \
			pci_name(dev->pdev) , ## args)

#अगर_घोषित DEBUG
#घोषणा DBG(dev,fmt,args...) \
	xprपूर्णांकk(dev , KERN_DEBUG , fmt , ## args)
#अन्यथा
#घोषणा DBG(dev,fmt,args...) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

#अगर_घोषित VERBOSE
#घोषणा VDBG DBG
#अन्यथा
#घोषणा VDBG(dev,fmt,args...) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर	/* VERBOSE */

#घोषणा ERROR(dev,fmt,args...) \
	xprपूर्णांकk(dev , KERN_ERR , fmt , ## args)
#घोषणा WARNING(dev,fmt,args...) \
	xprपूर्णांकk(dev , KERN_WARNING , fmt , ## args)
#घोषणा INFO(dev,fmt,args...) \
	xprपूर्णांकk(dev , KERN_INFO , fmt , ## args)

