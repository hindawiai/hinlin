<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  EMXX FCD (Function Controller Driver) क्रम USB.
 *
 *  Copyright (C) 2010 Renesas Electronics Corporation
 */

#अगर_अघोषित _LINUX_EMXX_H
#घोषणा _LINUX_EMXX_H

/*---------------------------------------------------------------------------*/

/*----------------- Default define */
#घोषणा	USE_DMA	1
#घोषणा USE_SUSPEND_WAIT	1

/*------------ Board dependence(Resource) */
#घोषणा	VBUS_VALUE		GPIO_VBUS

/* below hacked up क्रम staging पूर्णांकegration */
#घोषणा GPIO_VBUS 0 /* GPIO_P153 on KZM9D */
#घोषणा INT_VBUS 0 /* IRQ क्रम GPIO_P153 */

/*------------ Board dependence(Wait) */

/* CHATTERING रुको समय ms */
#घोषणा VBUS_CHATTERING_MDELAY		1
/* DMA Abort रुको समय ms */
#घोषणा DMA_DISABLE_TIME		10

/*------------ Controller dependence */
#घोषणा NUM_ENDPOINTS		14		/* Endpoपूर्णांक */
#घोषणा REG_EP_NUM		15		/* Endpoपूर्णांक Register */
#घोषणा DMA_MAX_COUNT		256		/* DMA Block */

#घोषणा EPC_RST_DISABLE_TIME		1	/* 1 usec */
#घोषणा EPC_सूचीPD_DISABLE_TIME		1	/* 1 msec */
#घोषणा EPC_PLL_LOCK_COUNT		1000	/* 1000 */
#घोषणा IN_DATA_EMPTY_COUNT		1000	/* 1000 */

#घोषणा CHATGER_TIME			700	/* 700msec */
#घोषणा USB_SUSPEND_TIME		2000	/* 2 sec */

/* U2F FLAG */
#घोषणा U2F_ENABLE		1
#घोषणा U2F_DISABLE		0

#घोषणा TEST_FORCE_ENABLE		(BIT(18) | BIT(16))

#घोषणा INT_SEL				BIT(10)
#घोषणा CONSTFS				BIT(9)
#घोषणा SOF_RCV				BIT(8)
#घोषणा RSUM_IN				BIT(7)
#घोषणा SUSPEND				BIT(6)
#घोषणा CONF				BIT(5)
#घोषणा DEFAULT				BIT(4)
#घोषणा CONNECTB			BIT(3)
#घोषणा PUE2				BIT(2)

#घोषणा MAX_TEST_MODE_NUM		0x05
#घोषणा TEST_MODE_SHIFT			16

/*------- (0x0004) USB Status Register */
#घोषणा SPEED_MODE			BIT(6)
#घोषणा HIGH_SPEED			BIT(6)

#घोषणा CONF				BIT(5)
#घोषणा DEFAULT				BIT(4)
#घोषणा USB_RST				BIT(3)
#घोषणा SPND_OUT			BIT(2)
#घोषणा RSUM_OUT			BIT(1)

/*------- (0x0008) USB Address Register */
#घोषणा USB_ADDR			0x007F0000
#घोषणा SOF_STATUS			BIT(15)
#घोषणा UFRAME				(BIT(14) | BIT(13) | BIT(12))
#घोषणा FRAME				0x000007FF

#घोषणा USB_ADRS_SHIFT			16

/*------- (0x000C) UTMI Characteristic 1 Register */
#घोषणा SQUSET				(BIT(7) | BIT(6) | BIT(5) | BIT(4))

#घोषणा USB_SQUSET			(BIT(6) | BIT(5) | BIT(4))

/*------- (0x0010) TEST Control Register */
#घोषणा FORCEHS				BIT(2)
#घोषणा CS_TESTMODEEN			BIT(1)
#घोषणा LOOPBACK			BIT(0)

/*------- (0x0018) Setup Data 0 Register */
/*------- (0x001C) Setup Data 1 Register */

/*------- (0x0020) USB Interrupt Status Register */
#घोषणा EPN_INT				0x00FFFF00
#घोषणा EP15_INT			BIT(23)
#घोषणा EP14_INT			BIT(22)
#घोषणा EP13_INT			BIT(21)
#घोषणा EP12_INT			BIT(20)
#घोषणा EP11_INT			BIT(19)
#घोषणा EP10_INT			BIT(18)
#घोषणा EP9_INT				BIT(17)
#घोषणा EP8_INT				BIT(16)
#घोषणा EP7_INT				BIT(15)
#घोषणा EP6_INT				BIT(14)
#घोषणा EP5_INT				BIT(13)
#घोषणा EP4_INT				BIT(12)
#घोषणा EP3_INT				BIT(11)
#घोषणा EP2_INT				BIT(10)
#घोषणा EP1_INT				BIT(9)
#घोषणा EP0_INT				BIT(8)
#घोषणा SPEED_MODE_INT			BIT(6)
#घोषणा SOF_ERROR_INT			BIT(5)
#घोषणा SOF_INT				BIT(4)
#घोषणा USB_RST_INT			BIT(3)
#घोषणा SPND_INT			BIT(2)
#घोषणा RSUM_INT			BIT(1)

#घोषणा USB_INT_STA_RW			0x7E

/*------- (0x0024) USB Interrupt Enable Register */
#घोषणा EP15_0_EN			0x00FFFF00
#घोषणा EP15_EN				BIT(23)
#घोषणा EP14_EN				BIT(22)
#घोषणा EP13_EN				BIT(21)
#घोषणा EP12_EN				BIT(20)
#घोषणा EP11_EN				BIT(19)
#घोषणा EP10_EN				BIT(18)
#घोषणा EP9_EN				BIT(17)
#घोषणा EP8_EN				BIT(16)
#घोषणा EP7_EN				BIT(15)
#घोषणा EP6_EN				BIT(14)
#घोषणा EP5_EN				BIT(13)
#घोषणा EP4_EN				BIT(12)
#घोषणा EP3_EN				BIT(11)
#घोषणा EP2_EN				BIT(10)
#घोषणा EP1_EN				BIT(9)
#घोषणा EP0_EN				BIT(8)
#घोषणा SPEED_MODE_EN			BIT(6)
#घोषणा SOF_ERROR_EN			BIT(5)
#घोषणा SOF_EN				BIT(4)
#घोषणा USB_RST_EN			BIT(3)
#घोषणा SPND_EN				BIT(2)
#घोषणा RSUM_EN				BIT(1)

#घोषणा USB_INT_EN_BIT	\
	(EP0_EN | SPEED_MODE_EN | USB_RST_EN | SPND_EN | RSUM_EN)

/*------- (0x0028) EP0 Control Register */
#घोषणा EP0_STGSEL			BIT(18)
#घोषणा EP0_OVERSEL			BIT(17)
#घोषणा EP0_AUTO			BIT(16)
#घोषणा EP0_PIDCLR			BIT(9)
#घोषणा EP0_BCLR			BIT(8)
#घोषणा EP0_DEND			BIT(7)
#घोषणा EP0_DW				(BIT(6) | BIT(5))
#घोषणा EP0_DW4				0
#घोषणा EP0_DW3				(BIT(6) | BIT(5))
#घोषणा EP0_DW2				BIT(6)
#घोषणा EP0_DW1				BIT(5)

#घोषणा EP0_INAK_EN			BIT(4)
#घोषणा EP0_PERR_NAK_CLR		BIT(3)
#घोषणा EP0_STL				BIT(2)
#घोषणा EP0_INAK			BIT(1)
#घोषणा EP0_ONAK			BIT(0)

/*------- (0x002C) EP0 Status Register */
#घोषणा EP0_PID				BIT(18)
#घोषणा EP0_PERR_NAK			BIT(17)
#घोषणा EP0_PERR_NAK_INT		BIT(16)
#घोषणा EP0_OUT_NAK_INT			BIT(15)
#घोषणा EP0_OUT_शून्य			BIT(14)
#घोषणा EP0_OUT_FULL			BIT(13)
#घोषणा EP0_OUT_EMPTY			BIT(12)
#घोषणा EP0_IN_NAK_INT			BIT(11)
#घोषणा EP0_IN_DATA			BIT(10)
#घोषणा EP0_IN_FULL			BIT(9)
#घोषणा EP0_IN_EMPTY			BIT(8)
#घोषणा EP0_OUT_शून्य_INT		BIT(7)
#घोषणा EP0_OUT_OR_INT			BIT(6)
#घोषणा EP0_OUT_INT			BIT(5)
#घोषणा EP0_IN_INT			BIT(4)
#घोषणा EP0_STALL_INT			BIT(3)
#घोषणा STG_END_INT			BIT(2)
#घोषणा STG_START_INT			BIT(1)
#घोषणा SETUP_INT			BIT(0)

#घोषणा EP0_STATUS_RW_BIT	(BIT(16) | BIT(15) | BIT(11) | 0xFF)

/*------- (0x0030) EP0 Interrupt Enable Register */
#घोषणा EP0_PERR_NAK_EN			BIT(16)
#घोषणा EP0_OUT_NAK_EN			BIT(15)

#घोषणा EP0_IN_NAK_EN			BIT(11)

#घोषणा EP0_OUT_शून्य_EN			BIT(7)
#घोषणा EP0_OUT_OR_EN			BIT(6)
#घोषणा EP0_OUT_EN			BIT(5)
#घोषणा EP0_IN_EN			BIT(4)
#घोषणा EP0_STALL_EN			BIT(3)
#घोषणा STG_END_EN			BIT(2)
#घोषणा STG_START_EN			BIT(1)
#घोषणा SETUP_EN			BIT(0)

#घोषणा EP0_INT_EN_BIT	\
	(EP0_OUT_OR_EN | EP0_OUT_EN | EP0_IN_EN | STG_END_EN | SETUP_EN)

/*------- (0x0034) EP0 Length Register */
#घोषणा EP0_LDATA			0x0000007F

/*------- (0x0038) EP0 Read Register */
/*------- (0x003C) EP0 Write Register */

/*------- (0x0040:) EPN Control Register */
#घोषणा EPN_EN				BIT(31)
#घोषणा EPN_BUF_TYPE			BIT(30)
#घोषणा EPN_BUF_SINGLE			BIT(30)

#घोषणा EPN_सूची0			BIT(26)
#घोषणा EPN_MODE			(BIT(25) | BIT(24))
#घोषणा EPN_BULK			0
#घोषणा EPN_INTERRUPT			BIT(24)
#घोषणा EPN_ISO				BIT(25)

#घोषणा EPN_OVERSEL			BIT(17)
#घोषणा EPN_AUTO			BIT(16)

#घोषणा EPN_IPIDCLR			BIT(11)
#घोषणा EPN_OPIDCLR			BIT(10)
#घोषणा EPN_BCLR			BIT(9)
#घोषणा EPN_CBCLR			BIT(8)
#घोषणा EPN_DEND			BIT(7)
#घोषणा EPN_DW				(BIT(6) | BIT(5))
#घोषणा EPN_DW4				0
#घोषणा EPN_DW3				(BIT(6) | BIT(5))
#घोषणा EPN_DW2				BIT(6)
#घोषणा EPN_DW1				BIT(5)

#घोषणा EPN_OSTL_EN			BIT(4)
#घोषणा EPN_ISTL			BIT(3)
#घोषणा EPN_OSTL			BIT(2)

#घोषणा EPN_ONAK			BIT(0)

/*------- (0x0044:) EPN Status Register	*/
#घोषणा EPN_ISO_PIDERR			BIT(29)		/* R */
#घोषणा EPN_OPID			BIT(28)		/* R */
#घोषणा EPN_OUT_NOTKN			BIT(27)		/* R */
#घोषणा EPN_ISO_OR			BIT(26)		/* R */

#घोषणा EPN_ISO_CRC			BIT(24)		/* R */
#घोषणा EPN_OUT_END_INT			BIT(23)		/* RW */
#घोषणा EPN_OUT_OR_INT			BIT(22)		/* RW */
#घोषणा EPN_OUT_NAK_ERR_INT		BIT(21)		/* RW */
#घोषणा EPN_OUT_STALL_INT		BIT(20)		/* RW */
#घोषणा EPN_OUT_INT			BIT(19)		/* RW */
#घोषणा EPN_OUT_शून्य_INT		BIT(18)		/* RW */
#घोषणा EPN_OUT_FULL			BIT(17)		/* R */
#घोषणा EPN_OUT_EMPTY			BIT(16)		/* R */

#घोषणा EPN_IPID			BIT(10)		/* R */
#घोषणा EPN_IN_NOTKN			BIT(9)		/* R */
#घोषणा EPN_ISO_UR			BIT(8)		/* R */
#घोषणा EPN_IN_END_INT			BIT(7)		/* RW */

#घोषणा EPN_IN_NAK_ERR_INT		BIT(5)		/* RW */
#घोषणा EPN_IN_STALL_INT		BIT(4)		/* RW */
#घोषणा EPN_IN_INT			BIT(3)		/* RW */
#घोषणा EPN_IN_DATA			BIT(2)		/* R */
#घोषणा EPN_IN_FULL			BIT(1)		/* R */
#घोषणा EPN_IN_EMPTY			BIT(0)		/* R */

#घोषणा EPN_INT_EN	\
	(EPN_OUT_END_INT | EPN_OUT_INT | EPN_IN_END_INT | EPN_IN_INT)

/*------- (0x0048:) EPN Interrupt Enable Register */
#घोषणा EPN_OUT_END_EN			BIT(23)		/* RW */
#घोषणा EPN_OUT_OR_EN			BIT(22)		/* RW */
#घोषणा EPN_OUT_NAK_ERR_EN		BIT(21)		/* RW */
#घोषणा EPN_OUT_STALL_EN		BIT(20)		/* RW */
#घोषणा EPN_OUT_EN			BIT(19)		/* RW */
#घोषणा EPN_OUT_शून्य_EN			BIT(18)		/* RW */

#घोषणा EPN_IN_END_EN			BIT(7)		/* RW */

#घोषणा EPN_IN_NAK_ERR_EN		BIT(5)		/* RW */
#घोषणा EPN_IN_STALL_EN			BIT(4)		/* RW */
#घोषणा EPN_IN_EN			BIT(3)		/* RW */

/*------- (0x004C:) EPN Interrupt Enable Register */
#घोषणा EPN_STOP_MODE			BIT(11)
#घोषणा EPN_DEND_SET			BIT(10)
#घोषणा EPN_BURST_SET			BIT(9)
#घोषणा EPN_STOP_SET			BIT(8)

#घोषणा EPN_DMA_EN			BIT(4)

#घोषणा EPN_DMAMODE0			BIT(0)

/*------- (0x0050:) EPN MaxPacket & BaseAddress Register */
#घोषणा EPN_BASEAD			0x1FFF0000
#घोषणा EPN_MPKT			0x000007FF

/*------- (0x0054:) EPN Length & DMA Count Register */
#घोषणा EPN_DMACNT			0x01FF0000
#घोषणा EPN_LDATA			0x000007FF

/*------- (0x0058:) EPN Read Register */
/*------- (0x005C:) EPN Write Register */

/*------- (0x1000) AHBSCTR Register */
#घोषणा WAIT_MODE			BIT(0)

/*------- (0x1004) AHBMCTR Register */
#घोषणा ARBITER_CTR			BIT(31)		/* RW */
#घोषणा MCYCLE_RST			BIT(12)		/* RW */

#घोषणा ENDIAN_CTR			(BIT(9) | BIT(8))	/* RW */
#घोषणा ENDIAN_BYTE_SWAP		BIT(9)
#घोषणा ENDIAN_HALF_WORD_SWAP		ENDIAN_CTR

#घोषणा HBUSREQ_MODE			BIT(5)		/* RW */
#घोषणा HTRANS_MODE			BIT(4)		/* RW */

#घोषणा WBURST_TYPE			BIT(2)		/* RW */
#घोषणा BURST_TYPE			(BIT(1) | BIT(0))	/* RW */
#घोषणा BURST_MAX_16			0
#घोषणा BURST_MAX_8			BIT(0)
#घोषणा BURST_MAX_4			BIT(1)
#घोषणा BURST_SINGLE			BURST_TYPE

/*------- (0x1008) AHBBINT Register */
#घोषणा DMA_ENDINT			0xFFFE0000	/* RW */

#घोषणा AHB_VBUS_INT			BIT(13)		/* RW */

#घोषणा MBUS_ERRINT			BIT(6)		/* RW */

#घोषणा SBUS_ERRINT0			BIT(4)		/* RW */
#घोषणा ERR_MASTER			0x0000000F	/* R */

/*------- (0x100C) AHBBINTEN Register */
#घोषणा DMA_ENDINTEN			0xFFFE0000	/* RW */

#घोषणा VBUS_INTEN			BIT(13)		/* RW */

#घोषणा MBUS_ERRINTEN			BIT(6)		/* RW */

#घोषणा SBUS_ERRINT0EN			BIT(4)		/* RW */

/*------- (0x1010) EPCTR Register */
#घोषणा सूचीPD				BIT(12)		/* RW */

#घोषणा VBUS_LEVEL			BIT(8)		/* R */

#घोषणा PLL_RESUME			BIT(5)		/* RW */
#घोषणा PLL_LOCK			BIT(4)		/* R */

#घोषणा EPC_RST				BIT(0)		/* RW */

/*------- (0x1014) USBF_EPTEST Register */
#घोषणा LINESTATE			(BIT(9) | BIT(8))	/* R */
#घोषणा DM_LEVEL			BIT(9)		/* R */
#घोषणा DP_LEVEL			BIT(8)		/* R */

#घोषणा PHY_TST				BIT(1)		/* RW */
#घोषणा PHY_TSTCLK			BIT(0)		/* RW */

/*------- (0x1020) USBSSVER Register */
#घोषणा AHBB_VER			0x00FF0000	/* R */
#घोषणा EPC_VER				0x0000FF00	/* R */
#घोषणा SS_VER				0x000000FF	/* R */

/*------- (0x1024) USBSSCONF Register */
#घोषणा EP_AVAILABLE			0xFFFF0000	/* R */
#घोषणा DMA_AVAILABLE			0x0000FFFF	/* R */

/*------- (0x1110:) EPNDCR1 Register */
#घोषणा DCR1_EPN_DMACNT			0x00FF0000	/* RW */

#घोषणा DCR1_EPN_सूची0			BIT(1)		/* RW */
#घोषणा DCR1_EPN_REQEN			BIT(0)		/* RW */

/*------- (0x1114:) EPNDCR2 Register */
#घोषणा DCR2_EPN_LMPKT			0x07FF0000	/* RW */

#घोषणा DCR2_EPN_MPKT			0x000007FF	/* RW */

/*------- (0x1118:) EPNTADR Register */
#घोषणा EPN_TADR			0xFFFFFFFF	/* RW */

/*===========================================================================*/
/* Struct */
/*------- ep_regs */
काष्ठा ep_regs अणु
	u32 EP_CONTROL;			/* EP Control */
	u32 EP_STATUS;			/* EP Status */
	u32 EP_INT_ENA;			/* EP Interrupt Enable */
	u32 EP_DMA_CTRL;		/* EP DMA Control */
	u32 EP_PCKT_ADRS;		/* EP Maxpacket & BaseAddress */
	u32 EP_LEN_DCNT;		/* EP Length & DMA count */
	u32 EP_READ;			/* EP Read */
	u32 EP_WRITE;			/* EP Write */
पूर्ण;

/*------- ep_dcr */
काष्ठा ep_dcr अणु
	u32 EP_DCR1;			/* EP_DCR1 */
	u32 EP_DCR2;			/* EP_DCR2 */
	u32 EP_TADR;			/* EP_TADR */
	u32 Reserved;			/* Reserved */
पूर्ण;

/*------- Function Registers */
काष्ठा fc_regs अणु
	u32 USB_CONTROL;		/* (0x0000) USB Control */
	u32 USB_STATUS;			/* (0x0004) USB Status */
	u32 USB_ADDRESS;		/* (0x0008) USB Address */
	u32 UTMI_CHARACTER_1;		/* (0x000C) UTMI Setting */
	u32 TEST_CONTROL;		/* (0x0010) TEST Control */
	u32 reserved_14;		/* (0x0014) Reserved */
	u32 SETUP_DATA0;		/* (0x0018) Setup Data0 */
	u32 SETUP_DATA1;		/* (0x001C) Setup Data1 */
	u32 USB_INT_STA;		/* (0x0020) USB Interrupt Status */
	u32 USB_INT_ENA;		/* (0x0024) USB Interrupt Enable */
	u32 EP0_CONTROL;		/* (0x0028) EP0 Control */
	u32 EP0_STATUS;			/* (0x002C) EP0 Status */
	u32 EP0_INT_ENA;		/* (0x0030) EP0 Interrupt Enable */
	u32 EP0_LENGTH;			/* (0x0034) EP0 Length */
	u32 EP0_READ;			/* (0x0038) EP0 Read */
	u32 EP0_WRITE;			/* (0x003C) EP0 Write */

	काष्ठा ep_regs EP_REGS[REG_EP_NUM];	/* Endpoपूर्णांक Register */

	u8 reserved_220[0x1000 - 0x220];	/* (0x0220:0x0FFF) Reserved */

	u32 AHBSCTR;			/* (0x1000) AHBSCTR */
	u32 AHBMCTR;			/* (0x1004) AHBMCTR */
	u32 AHBBINT;			/* (0x1008) AHBBINT */
	u32 AHBBINTEN;			/* (0x100C) AHBBINTEN */
	u32 EPCTR;			/* (0x1010) EPCTR */
	u32 USBF_EPTEST;		/* (0x1014) USBF_EPTEST */

	u8 reserved_1018[0x20 - 0x18];	/* (0x1018:0x101F) Reserved */

	u32 USBSSVER;			/* (0x1020) USBSSVER */
	u32 USBSSCONF;			/* (0x1024) USBSSCONF */

	u8 reserved_1028[0x110 - 0x28];	/* (0x1028:0x110F) Reserved */

	काष्ठा ep_dcr EP_DCR[REG_EP_NUM];	/* */

	u8 reserved_1200[0x1000 - 0x200];	/* Reserved */
पूर्ण __aligned(32);

#घोषणा EP0_PACKETSIZE			64
#घोषणा EP_PACKETSIZE			1024

/* EPN RAM SIZE */
#घोषणा D_RAM_SIZE_CTRL			64

/* EPN Bulk Endpoपूर्णांक Max Packet Size */
#घोषणा D_FS_RAM_SIZE_BULK		64
#घोषणा D_HS_RAM_SIZE_BULK		512

काष्ठा nbu2ss_udc;

क्रमागत ep0_state अणु
	EP0_IDLE,
	EP0_IN_DATA_PHASE,
	EP0_OUT_DATA_PHASE,
	EP0_IN_STATUS_PHASE,
	EP0_OUT_STATUS_PAHSE,
	EP0_END_XFER,
	EP0_SUSPEND,
	EP0_STALL,
पूर्ण;

काष्ठा nbu2ss_req अणु
	काष्ठा usb_request		req;
	काष्ठा list_head		queue;

	u32			भाग_len;
	bool		dma_flag;
	bool		zero;

	bool		unaligned;

	अचिन्हित			mapped:1;
पूर्ण;

काष्ठा nbu2ss_ep अणु
	काष्ठा usb_ep			ep;
	काष्ठा list_head		queue;

	काष्ठा nbu2ss_udc		*udc;

	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;

	u8		epnum;
	u8		direct;
	u8		ep_type;

	अचिन्हित		wedged:1;
	अचिन्हित		halted:1;
	अचिन्हित		stalled:1;

	u8		*virt_buf;
	dma_addr_t	phys_buf;
पूर्ण;

काष्ठा nbu2ss_udc अणु
	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *driver;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *dev;
	spinlock_t lock; /* Protects nbu2ss_udc काष्ठाure fields */
	काष्ठा completion		*pकरोne;

	क्रमागत ep0_state			ep0state;
	क्रमागत usb_device_state	devstate;
	काष्ठा usb_ctrlrequest	ctrl;
	काष्ठा nbu2ss_req		ep0_req;
	u8		ep0_buf[EP0_PACKETSIZE];

	काष्ठा nbu2ss_ep	ep[NUM_ENDPOINTS];

	अचिन्हित		softconnect:1;
	अचिन्हित		vbus_active:1;
	अचिन्हित		linux_suspended:1;
	अचिन्हित		linux_resume:1;
	अचिन्हित		usb_suspended:1;
	अचिन्हित		remote_wakeup:1;
	अचिन्हित		udc_enabled:1;

	अचिन्हित पूर्णांक		mA;

	u32		curr_config;	/* Current Configuration Number */

	काष्ठा fc_regs __iomem *p_regs;
पूर्ण;

/* USB रेजिस्टर access काष्ठाure */
जोड़ usb_reg_access अणु
	काष्ठा अणु
		अचिन्हित अक्षर	DATA[4];
	पूर्ण byte;
	अचिन्हित पूर्णांक		dw;
पूर्ण;

/*-------------------------------------------------------------------------*/

#पूर्ण_अगर  /* _LINUX_EMXX_H */
