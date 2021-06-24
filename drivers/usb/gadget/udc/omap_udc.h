<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * omap_udc.h -- क्रम omap 3.2 udc, with OTG support
 *
 * 2004 (C) Texas Instruments, Inc.
 * 2004 (C) David Brownell
 */

/*
 * USB device/endpoपूर्णांक management रेजिस्टरs
 */

#घोषणा	UDC_REV				(UDC_BASE + 0x0)	/* Revision */
#घोषणा	UDC_EP_NUM			(UDC_BASE + 0x4)	/* Which endpoपूर्णांक */
#	define	UDC_SETUP_SEL		(1 << 6)
#	define	UDC_EP_SEL		(1 << 5)
#	define	UDC_EP_सूची		(1 << 4)
	/* low 4 bits क्रम endpoपूर्णांक number */
#घोषणा	UDC_DATA			(UDC_BASE + 0x08)	/* Endpoपूर्णांक FIFO */
#घोषणा	UDC_CTRL			(UDC_BASE + 0x0C)	/* Endpoपूर्णांक control */
#	define	UDC_CLR_HALT		(1 << 7)
#	define	UDC_SET_HALT		(1 << 6)
#	define	UDC_CLRDATA_TOGGLE	(1 << 3)
#	define	UDC_SET_FIFO_EN		(1 << 2)
#	define	UDC_CLR_EP		(1 << 1)
#	define	UDC_RESET_EP		(1 << 0)
#घोषणा	UDC_STAT_FLG			(UDC_BASE + 0x10)	/* Endpoपूर्णांक status */
#	define	UDC_NO_RXPACKET		(1 << 15)
#	define	UDC_MISS_IN		(1 << 14)
#	define	UDC_DATA_FLUSH		(1 << 13)
#	define	UDC_ISO_ERR		(1 << 12)
#	define	UDC_ISO_FIFO_EMPTY	(1 << 9)
#	define	UDC_ISO_FIFO_FULL	(1 << 8)
#	define	UDC_EP_HALTED		(1 << 6)
#	define	UDC_STALL		(1 << 5)
#	define	UDC_NAK			(1 << 4)
#	define	UDC_ACK			(1 << 3)
#	define	UDC_FIFO_EN		(1 << 2)
#	define	UDC_NON_ISO_FIFO_EMPTY	(1 << 1)
#	define	UDC_NON_ISO_FIFO_FULL	(1 << 0)
#घोषणा	UDC_RXFSTAT			(UDC_BASE + 0x14)	/* OUT bytecount */
#घोषणा	UDC_SYSCON1			(UDC_BASE + 0x18)	/* System config 1 */
#	define	UDC_CFG_LOCK		(1 << 8)
#	define	UDC_DATA_ENDIAN		(1 << 7)
#	define	UDC_DMA_ENDIAN		(1 << 6)
#	define	UDC_NAK_EN		(1 << 4)
#	define	UDC_AUTODECODE_DIS	(1 << 3)
#	define	UDC_SELF_PWR		(1 << 2)
#	define	UDC_SOFF_DIS		(1 << 1)
#	define	UDC_PULLUP_EN		(1 << 0)
#घोषणा	UDC_SYSCON2			(UDC_BASE + 0x1C)	/* System config 2 */
#	define	UDC_RMT_WKP		(1 << 6)
#	define	UDC_STALL_CMD		(1 << 5)
#	define	UDC_DEV_CFG		(1 << 3)
#	define	UDC_CLR_CFG		(1 << 2)
#घोषणा	UDC_DEVSTAT			(UDC_BASE + 0x20)	/* Device status */
#	define	UDC_B_HNP_ENABLE	(1 << 9)
#	define	UDC_A_HNP_SUPPORT	(1 << 8)
#	define	UDC_A_ALT_HNP_SUPPORT	(1 << 7)
#	define	UDC_R_WK_OK		(1 << 6)
#	define	UDC_USB_RESET		(1 << 5)
#	define	UDC_SUS			(1 << 4)
#	define	UDC_CFG			(1 << 3)
#	define	UDC_ADD			(1 << 2)
#	define	UDC_DEF			(1 << 1)
#	define	UDC_ATT			(1 << 0)
#घोषणा	UDC_SOF				(UDC_BASE + 0x24)	/* Start of frame */
#	define	UDC_FT_LOCK		(1 << 12)
#	define	UDC_TS_OK		(1 << 11)
#	define	UDC_TS			0x03ff
#घोषणा	UDC_IRQ_EN			(UDC_BASE + 0x28)	/* Interrupt enable */
#	define	UDC_SOF_IE		(1 << 7)
#	define	UDC_EPN_RX_IE		(1 << 5)
#	define	UDC_EPN_TX_IE		(1 << 4)
#	define	UDC_DS_CHG_IE		(1 << 3)
#	define	UDC_EP0_IE		(1 << 0)
#घोषणा	UDC_DMA_IRQ_EN			(UDC_BASE + 0x2C)	/* DMA irq enable */
	/* rx/tx dma channels numbered 1-3 not 0-2 */
#	define	UDC_TX_DONE_IE(n)	(1 << (4 * (n) - 2))
#	define	UDC_RX_CNT_IE(n)	(1 << (4 * (n) - 3))
#	define	UDC_RX_EOT_IE(n)	(1 << (4 * (n) - 4))
#घोषणा	UDC_IRQ_SRC			(UDC_BASE + 0x30)	/* Interrupt source */
#	define	UDC_TXN_DONE		(1 << 10)
#	define	UDC_RXN_CNT		(1 << 9)
#	define	UDC_RXN_EOT		(1 << 8)
#	define	UDC_IRQ_SOF		(1 << 7)
#	define	UDC_EPN_RX		(1 << 5)
#	define	UDC_EPN_TX		(1 << 4)
#	define	UDC_DS_CHG		(1 << 3)
#	define	UDC_SETUP		(1 << 2)
#	define	UDC_EP0_RX		(1 << 1)
#	define	UDC_EP0_TX		(1 << 0)
#	define	UDC_IRQ_SRC_MASK	0x7bf
#घोषणा	UDC_EPN_STAT			(UDC_BASE + 0x34)	/* EP irq status */
#घोषणा	UDC_DMAN_STAT			(UDC_BASE + 0x38)	/* DMA irq status */
#	define	UDC_DMA_RX_SB		(1 << 12)
#	define	UDC_DMA_RX_SRC(x)	(((x)>>8) & 0xf)
#	define	UDC_DMA_TX_SRC(x)	(((x)>>0) & 0xf)


/* DMA configuration रेजिस्टरs:  up to three channels in each direction.  */
#घोषणा	UDC_RXDMA_CFG			(UDC_BASE + 0x40)	/* 3 eps क्रम RX DMA */
#	define	UDC_DMA_REQ		(1 << 12)
#घोषणा	UDC_TXDMA_CFG			(UDC_BASE + 0x44)	/* 3 eps क्रम TX DMA */
#घोषणा	UDC_DATA_DMA			(UDC_BASE + 0x48)	/* rx/tx fअगरo addr */

/* rx/tx dma control, numbering channels 1-3 not 0-2 */
#घोषणा	UDC_TXDMA(chan)			(UDC_BASE + 0x50 - 4 + 4 * (chan))
#	define UDC_TXN_EOT		(1 << 15)	/* bytes vs packets */
#	define UDC_TXN_START		(1 << 14)	/* start transfer */
#	define UDC_TXN_TSC		0x03ff		/* units in xfer */
#घोषणा	UDC_RXDMA(chan)			(UDC_BASE + 0x60 - 4 + 4 * (chan))
#	define UDC_RXN_STOP		(1 << 15)	/* enable EOT irq */
#	define UDC_RXN_TC		0x00ff		/* packets in xfer */


/*
 * Endpoपूर्णांक configuration रेजिस्टरs (used beक्रमe CFG_LOCK is set)
 * UDC_EP_TX(0) is unused
 */
#घोषणा	UDC_EP_RX(endpoपूर्णांक)		(UDC_BASE + 0x80 + (endpoपूर्णांक)*4)
#	define	UDC_EPN_RX_VALID	(1 << 15)
#	define	UDC_EPN_RX_DB		(1 << 14)
	/* buffer size in bits 13, 12 */
#	define	UDC_EPN_RX_ISO		(1 << 11)
	/* buffer poपूर्णांकer in low 11 bits */
#घोषणा	UDC_EP_TX(endpoपूर्णांक)		(UDC_BASE + 0xc0 + (endpoपूर्णांक)*4)
	/* same bitfields as in RX */

/*-------------------------------------------------------------------------*/

काष्ठा omap_req अणु
	काष्ठा usb_request		req;
	काष्ठा list_head		queue;
	अचिन्हित			dma_bytes;
	अचिन्हित			mapped:1;
पूर्ण;

काष्ठा omap_ep अणु
	काष्ठा usb_ep			ep;
	काष्ठा list_head		queue;
	अचिन्हित दीर्घ			irqs;
	काष्ठा list_head		iso;
	अक्षर				name[14];
	u16				maxpacket;
	u8				bEndpoपूर्णांकAddress;
	u8				bmAttributes;
	अचिन्हित			द्विगुन_buf:1;
	अचिन्हित			stopped:1;
	अचिन्हित			fnf:1;
	अचिन्हित			has_dma:1;
	u8				ackरुको;
	u8				dma_channel;
	u16				dma_counter;
	पूर्णांक				lch;
	काष्ठा omap_udc			*udc;
	काष्ठा समयr_list		समयr;
पूर्ण;

काष्ठा omap_udc अणु
	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;
	spinlock_t			lock;
	काष्ठा omap_ep			ep[32];
	u16				devstat;
	u16				clr_halt;
	काष्ठा usb_phy			*transceiver;
	काष्ठा list_head		iso;
	अचिन्हित			softconnect:1;
	अचिन्हित			vbus_active:1;
	अचिन्हित			ep0_pending:1;
	अचिन्हित			ep0_in:1;
	अचिन्हित			ep0_set_config:1;
	अचिन्हित			ep0_reset_config:1;
	अचिन्हित			ep0_setup:1;
	काष्ठा completion		*करोne;
	काष्ठा clk			*dc_clk;
	काष्ठा clk			*hhc_clk;
	अचिन्हित			clk_requested:1;
पूर्ण;

/*-------------------------------------------------------------------------*/

#अगर_घोषित VERBOSE
#    define VDBG		DBG
#अन्यथा
#    define VDBG(stuff...)	करोअणुपूर्णजबतक(0)
#पूर्ण_अगर

#घोषणा ERR(stuff...)		pr_err("udc: " stuff)
#घोषणा WARNING(stuff...)	pr_warn("udc: " stuff)
#घोषणा INFO(stuff...)		pr_info("udc: " stuff)
#घोषणा DBG(stuff...)		pr_debug("udc: " stuff)

/*-------------------------------------------------------------------------*/

/* MOD_CONF_CTRL_0 */
#घोषणा VBUS_W2FC_1510		(1 << 17)	/* 0 gpio0, 1 dvdd2 pin */

/* FUNC_MUX_CTRL_0 */
#घोषणा	VBUS_CTRL_1510		(1 << 19)	/* 1 connected (software) */
#घोषणा	VBUS_MODE_1510		(1 << 18)	/* 0 hardware, 1 software */

#घोषणा	HMC_1510	((omap_पढ़ोl(MOD_CONF_CTRL_0) >> 1) & 0x3f)
#घोषणा	HMC_1610	(omap_पढ़ोl(OTG_SYSCON_2) & 0x3f)
#घोषणा	HMC		(cpu_is_omap15xx() ? HMC_1510 : HMC_1610)

