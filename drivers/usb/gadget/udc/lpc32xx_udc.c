<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB Gadget driver क्रम LPC32xx
 *
 * Authors:
 *    Kevin Wells <kevin.wells@nxp.com>
 *    Mike James
 *    Roland Stigge <stigge@antcom.de>
 *
 * Copyright (C) 2006 Philips Semiconductors
 * Copyright (C) 2009 NXP Semiconductors
 * Copyright (C) 2012 Roland Stigge
 *
 * Note: This driver is based on original work करोne by Mike James क्रम
 *       the LPC3180.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/isp1301.h>

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#पूर्ण_अगर

/*
 * USB device configuration काष्ठाure
 */
प्रकार व्योम (*usc_chg_event)(पूर्णांक);
काष्ठा lpc32xx_usbd_cfg अणु
	पूर्णांक vbus_drv_pol;   /* 0=active low drive क्रम VBUS via ISP1301 */
	usc_chg_event conn_chgb; /* Connection change event (optional) */
	usc_chg_event susp_chgb; /* Suspend/resume event (optional) */
	usc_chg_event rmwk_chgb; /* Enable/disable remote wakeup */
पूर्ण;

/*
 * controller driver data काष्ठाures
 */

/* 16 endpoपूर्णांकs (not to be confused with 32 hardware endpoपूर्णांकs) */
#घोषणा	NUM_ENDPOINTS	16

/*
 * IRQ indices make पढ़ोing the code a little easier
 */
#घोषणा IRQ_USB_LP	0
#घोषणा IRQ_USB_HP	1
#घोषणा IRQ_USB_DEVDMA	2
#घोषणा IRQ_USB_ATX	3

#घोषणा EP_OUT 0 /* RX (from host) */
#घोषणा EP_IN 1 /* TX (to host) */

/* Returns the पूर्णांकerrupt mask क्रम the selected hardware endpoपूर्णांक */
#घोषणा EP_MASK_SEL(ep, dir) (1 << (((ep) * 2) + dir))

#घोषणा EP_INT_TYPE 0
#घोषणा EP_ISO_TYPE 1
#घोषणा EP_BLK_TYPE 2
#घोषणा EP_CTL_TYPE 3

/* EP0 states */
#घोषणा WAIT_FOR_SETUP 0 /* Wait क्रम setup packet */
#घोषणा DATA_IN        1 /* Expect dev->host transfer */
#घोषणा DATA_OUT       2 /* Expect host->dev transfer */

/* DD (DMA Descriptor) काष्ठाure, requires word alignment, this is alपढ़ोy
 * defined in the LPC32XX USB device header file, but this version is slightly
 * modअगरied to tag some work data with each DMA descriptor. */
काष्ठा lpc32xx_usbd_dd_gad अणु
	u32 dd_next_phy;
	u32 dd_setup;
	u32 dd_buffer_addr;
	u32 dd_status;
	u32 dd_iso_ps_mem_addr;
	u32 this_dma;
	u32 iso_status[6]; /* 5 spare */
	u32 dd_next_v;
पूर्ण;

/*
 * Logical endpoपूर्णांक काष्ठाure
 */
काष्ठा lpc32xx_ep अणु
	काष्ठा usb_ep		ep;
	काष्ठा list_head	queue;
	काष्ठा lpc32xx_udc	*udc;

	u32			hwep_num_base; /* Physical hardware EP */
	u32			hwep_num; /* Maps to hardware endpoपूर्णांक */
	u32			maxpacket;
	u32			lep;

	bool			is_in;
	bool			req_pending;
	u32			eptype;

	u32                     totalपूर्णांकs;

	bool			wedge;
पूर्ण;

क्रमागत atx_type अणु
	ISP1301,
	STOTG04,
पूर्ण;

/*
 * Common UDC काष्ठाure
 */
काष्ठा lpc32xx_udc अणु
	काष्ठा usb_gadget	gadget;
	काष्ठा usb_gadget_driver *driver;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा device		*dev;
	काष्ठा dentry		*pde;
	spinlock_t		lock;
	काष्ठा i2c_client	*isp1301_i2c_client;

	/* Board and device specअगरic */
	काष्ठा lpc32xx_usbd_cfg	*board;
	व्योम __iomem		*udp_baseaddr;
	पूर्णांक			udp_irq[4];
	काष्ठा clk		*usb_slv_clk;

	/* DMA support */
	u32			*udca_v_base;
	u32			udca_p_base;
	काष्ठा dma_pool		*dd_cache;

	/* Common EP and control data */
	u32			enabled_devपूर्णांकs;
	u32			enabled_hwepपूर्णांकs;
	u32			dev_status;
	u32			realized_eps;

	/* VBUS detection, pullup, and घातer flags */
	u8			vbus;
	u8			last_vbus;
	पूर्णांक			pullup;
	पूर्णांक			घातeron;
	क्रमागत atx_type		atx;

	/* Work queues related to I2C support */
	काष्ठा work_काष्ठा	pullup_job;
	काष्ठा work_काष्ठा	घातer_job;

	/* USB device peripheral - various */
	काष्ठा lpc32xx_ep	ep[NUM_ENDPOINTS];
	bool			enabled;
	bool			घड़ीed;
	bool			suspended;
	पूर्णांक                     ep0state;
	atomic_t                enabled_ep_cnt;
	रुको_queue_head_t       ep_disable_रुको_queue;
पूर्ण;

/*
 * Endpoपूर्णांक request
 */
काष्ठा lpc32xx_request अणु
	काष्ठा usb_request	req;
	काष्ठा list_head	queue;
	काष्ठा lpc32xx_usbd_dd_gad *dd_desc_ptr;
	bool			mapped;
	bool			send_zlp;
पूर्ण;

अटल अंतरभूत काष्ठा lpc32xx_udc *to_udc(काष्ठा usb_gadget *g)
अणु
	वापस container_of(g, काष्ठा lpc32xx_udc, gadget);
पूर्ण

#घोषणा ep_dbg(epp, fmt, arg...) \
	dev_dbg(epp->udc->dev, "%s: " fmt, __func__, ## arg)
#घोषणा ep_err(epp, fmt, arg...) \
	dev_err(epp->udc->dev, "%s: " fmt, __func__, ## arg)
#घोषणा ep_info(epp, fmt, arg...) \
	dev_info(epp->udc->dev, "%s: " fmt, __func__, ## arg)
#घोषणा ep_warn(epp, fmt, arg...) \
	dev_warn(epp->udc->dev, "%s:" fmt, __func__, ## arg)

#घोषणा UDCA_BUFF_SIZE (128)

/**********************************************************************
 * USB device controller रेजिस्टर offsets
 **********************************************************************/

#घोषणा USBD_DEVINTST(x)	((x) + 0x200)
#घोषणा USBD_DEVINTEN(x)	((x) + 0x204)
#घोषणा USBD_DEVINTCLR(x)	((x) + 0x208)
#घोषणा USBD_DEVINTSET(x)	((x) + 0x20C)
#घोषणा USBD_CMDCODE(x)		((x) + 0x210)
#घोषणा USBD_CMDDATA(x)		((x) + 0x214)
#घोषणा USBD_RXDATA(x)		((x) + 0x218)
#घोषणा USBD_TXDATA(x)		((x) + 0x21C)
#घोषणा USBD_RXPLEN(x)		((x) + 0x220)
#घोषणा USBD_TXPLEN(x)		((x) + 0x224)
#घोषणा USBD_CTRL(x)		((x) + 0x228)
#घोषणा USBD_DEVINTPRI(x)	((x) + 0x22C)
#घोषणा USBD_EPINTST(x)		((x) + 0x230)
#घोषणा USBD_EPINTEN(x)		((x) + 0x234)
#घोषणा USBD_EPINTCLR(x)	((x) + 0x238)
#घोषणा USBD_EPINTSET(x)	((x) + 0x23C)
#घोषणा USBD_EPINTPRI(x)	((x) + 0x240)
#घोषणा USBD_REEP(x)		((x) + 0x244)
#घोषणा USBD_EPIND(x)		((x) + 0x248)
#घोषणा USBD_EPMAXPSIZE(x)	((x) + 0x24C)
/* DMA support रेजिस्टरs only below */
/* Set, clear, or get enabled state of the DMA request status. If
 * enabled, an IN or OUT token will start a DMA transfer क्रम the EP */
#घोषणा USBD_DMARST(x)		((x) + 0x250)
#घोषणा USBD_DMARCLR(x)		((x) + 0x254)
#घोषणा USBD_DMARSET(x)		((x) + 0x258)
/* DMA UDCA head poपूर्णांकer */
#घोषणा USBD_UDCAH(x)		((x) + 0x280)
/* EP DMA status, enable, and disable. This is used to specअगरically
 * enabled or disable DMA क्रम a specअगरic EP */
#घोषणा USBD_EPDMAST(x)		((x) + 0x284)
#घोषणा USBD_EPDMAEN(x)		((x) + 0x288)
#घोषणा USBD_EPDMADIS(x)	((x) + 0x28C)
/* DMA master पूर्णांकerrupts enable and pending पूर्णांकerrupts */
#घोषणा USBD_DMAINTST(x)	((x) + 0x290)
#घोषणा USBD_DMAINTEN(x)	((x) + 0x294)
/* DMA end of transfer पूर्णांकerrupt enable, disable, status */
#घोषणा USBD_EOTINTST(x)	((x) + 0x2A0)
#घोषणा USBD_EOTINTCLR(x)	((x) + 0x2A4)
#घोषणा USBD_EOTINTSET(x)	((x) + 0x2A8)
/* New DD request पूर्णांकerrupt enable, disable, status */
#घोषणा USBD_NDDRTINTST(x)	((x) + 0x2AC)
#घोषणा USBD_NDDRTINTCLR(x)	((x) + 0x2B0)
#घोषणा USBD_NDDRTINTSET(x)	((x) + 0x2B4)
/* DMA error पूर्णांकerrupt enable, disable, status */
#घोषणा USBD_SYSERRTINTST(x)	((x) + 0x2B8)
#घोषणा USBD_SYSERRTINTCLR(x)	((x) + 0x2BC)
#घोषणा USBD_SYSERRTINTSET(x)	((x) + 0x2C0)

/**********************************************************************
 * USBD_DEVINTST/USBD_DEVINTEN/USBD_DEVINTCLR/USBD_DEVINTSET/
 * USBD_DEVINTPRI रेजिस्टर definitions
 **********************************************************************/
#घोषणा USBD_ERR_INT		(1 << 9)
#घोषणा USBD_EP_RLZED		(1 << 8)
#घोषणा USBD_TXENDPKT		(1 << 7)
#घोषणा USBD_RXENDPKT		(1 << 6)
#घोषणा USBD_CDFULL		(1 << 5)
#घोषणा USBD_CCEMPTY		(1 << 4)
#घोषणा USBD_DEV_STAT		(1 << 3)
#घोषणा USBD_EP_SLOW		(1 << 2)
#घोषणा USBD_EP_FAST		(1 << 1)
#घोषणा USBD_FRAME		(1 << 0)

/**********************************************************************
 * USBD_EPINTST/USBD_EPINTEN/USBD_EPINTCLR/USBD_EPINTSET/
 * USBD_EPINTPRI रेजिस्टर definitions
 **********************************************************************/
/* End poपूर्णांक selection macro (RX) */
#घोषणा USBD_RX_EP_SEL(e)	(1 << ((e) << 1))

/* End poपूर्णांक selection macro (TX) */
#घोषणा USBD_TX_EP_SEL(e)	(1 << (((e) << 1) + 1))

/**********************************************************************
 * USBD_REEP/USBD_DMARST/USBD_DMARCLR/USBD_DMARSET/USBD_EPDMAST/
 * USBD_EPDMAEN/USBD_EPDMADIS/
 * USBD_NDDRTINTST/USBD_NDDRTINTCLR/USBD_NDDRTINTSET/
 * USBD_EOTINTST/USBD_EOTINTCLR/USBD_EOTINTSET/
 * USBD_SYSERRTINTST/USBD_SYSERRTINTCLR/USBD_SYSERRTINTSET
 * रेजिस्टर definitions
 **********************************************************************/
/* Endpoपूर्णांक selection macro */
#घोषणा USBD_EP_SEL(e)		(1 << (e))

/**********************************************************************
 * SBD_DMAINTST/USBD_DMAINTEN
 **********************************************************************/
#घोषणा USBD_SYS_ERR_INT	(1 << 2)
#घोषणा USBD_NEW_DD_INT		(1 << 1)
#घोषणा USBD_EOT_INT		(1 << 0)

/**********************************************************************
 * USBD_RXPLEN रेजिस्टर definitions
 **********************************************************************/
#घोषणा USBD_PKT_RDY		(1 << 11)
#घोषणा USBD_DV			(1 << 10)
#घोषणा USBD_PK_LEN_MASK	0x3FF

/**********************************************************************
 * USBD_CTRL रेजिस्टर definitions
 **********************************************************************/
#घोषणा USBD_LOG_ENDPOINT(e)	((e) << 2)
#घोषणा USBD_WR_EN		(1 << 1)
#घोषणा USBD_RD_EN		(1 << 0)

/**********************************************************************
 * USBD_CMDCODE रेजिस्टर definitions
 **********************************************************************/
#घोषणा USBD_CMD_CODE(c)	((c) << 16)
#घोषणा USBD_CMD_PHASE(p)	((p) << 8)

/**********************************************************************
 * USBD_DMARST/USBD_DMARCLR/USBD_DMARSET रेजिस्टर definitions
 **********************************************************************/
#घोषणा USBD_DMAEP(e)		(1 << (e))

/* DD (DMA Descriptor) काष्ठाure, requires word alignment */
काष्ठा lpc32xx_usbd_dd अणु
	u32 *dd_next;
	u32 dd_setup;
	u32 dd_buffer_addr;
	u32 dd_status;
	u32 dd_iso_ps_mem_addr;
पूर्ण;

/* dd_setup bit defines */
#घोषणा DD_SETUP_ATLE_DMA_MODE	0x01
#घोषणा DD_SETUP_NEXT_DD_VALID	0x04
#घोषणा DD_SETUP_ISO_EP		0x10
#घोषणा DD_SETUP_PACKETLEN(n)	(((n) & 0x7FF) << 5)
#घोषणा DD_SETUP_DMALENBYTES(n)	(((n) & 0xFFFF) << 16)

/* dd_status bit defines */
#घोषणा DD_STATUS_DD_RETIRED	0x01
#घोषणा DD_STATUS_STS_MASK	0x1E
#घोषणा DD_STATUS_STS_NS	0x00 /* Not serviced */
#घोषणा DD_STATUS_STS_BS	0x02 /* Being serviced */
#घोषणा DD_STATUS_STS_NC	0x04 /* Normal completion */
#घोषणा DD_STATUS_STS_DUR	0x06 /* Data underrun (लघु packet) */
#घोषणा DD_STATUS_STS_DOR	0x08 /* Data overrun */
#घोषणा DD_STATUS_STS_SE	0x12 /* System error */
#घोषणा DD_STATUS_PKT_VAL	0x20 /* Packet valid */
#घोषणा DD_STATUS_LSB_EX	0x40 /* LS byte extracted (ATLE) */
#घोषणा DD_STATUS_MSB_EX	0x80 /* MS byte extracted (ATLE) */
#घोषणा DD_STATUS_MLEN(n)	(((n) >> 8) & 0x3F)
#घोषणा DD_STATUS_CURDMACNT(n)	(((n) >> 16) & 0xFFFF)

/*
 *
 * Protocol engine bits below
 *
 */
/* Device Interrupt Bit Definitions */
#घोषणा FRAME_INT		0x00000001
#घोषणा EP_FAST_INT		0x00000002
#घोषणा EP_SLOW_INT		0x00000004
#घोषणा DEV_STAT_INT		0x00000008
#घोषणा CCEMTY_INT		0x00000010
#घोषणा CDFULL_INT		0x00000020
#घोषणा RxENDPKT_INT		0x00000040
#घोषणा TxENDPKT_INT		0x00000080
#घोषणा EP_RLZED_INT		0x00000100
#घोषणा ERR_INT			0x00000200

/* Rx & Tx Packet Length Definitions */
#घोषणा PKT_LNGTH_MASK		0x000003FF
#घोषणा PKT_DV			0x00000400
#घोषणा PKT_RDY			0x00000800

/* USB Control Definitions */
#घोषणा CTRL_RD_EN		0x00000001
#घोषणा CTRL_WR_EN		0x00000002

/* Command Codes */
#घोषणा CMD_SET_ADDR		0x00D00500
#घोषणा CMD_CFG_DEV		0x00D80500
#घोषणा CMD_SET_MODE		0x00F30500
#घोषणा CMD_RD_FRAME		0x00F50500
#घोषणा DAT_RD_FRAME		0x00F50200
#घोषणा CMD_RD_TEST		0x00FD0500
#घोषणा DAT_RD_TEST		0x00FD0200
#घोषणा CMD_SET_DEV_STAT	0x00FE0500
#घोषणा CMD_GET_DEV_STAT	0x00FE0500
#घोषणा DAT_GET_DEV_STAT	0x00FE0200
#घोषणा CMD_GET_ERR_CODE	0x00FF0500
#घोषणा DAT_GET_ERR_CODE	0x00FF0200
#घोषणा CMD_RD_ERR_STAT		0x00FB0500
#घोषणा DAT_RD_ERR_STAT		0x00FB0200
#घोषणा DAT_WR_BYTE(x)		(0x00000100 | ((x) << 16))
#घोषणा CMD_SEL_EP(x)		(0x00000500 | ((x) << 16))
#घोषणा DAT_SEL_EP(x)		(0x00000200 | ((x) << 16))
#घोषणा CMD_SEL_EP_CLRI(x)	(0x00400500 | ((x) << 16))
#घोषणा DAT_SEL_EP_CLRI(x)	(0x00400200 | ((x) << 16))
#घोषणा CMD_SET_EP_STAT(x)	(0x00400500 | ((x) << 16))
#घोषणा CMD_CLR_BUF		0x00F20500
#घोषणा DAT_CLR_BUF		0x00F20200
#घोषणा CMD_VALID_BUF		0x00FA0500

/* Device Address Register Definitions */
#घोषणा DEV_ADDR_MASK		0x7F
#घोषणा DEV_EN			0x80

/* Device Configure Register Definitions */
#घोषणा CONF_DVICE		0x01

/* Device Mode Register Definitions */
#घोषणा AP_CLK			0x01
#घोषणा INAK_CI			0x02
#घोषणा INAK_CO			0x04
#घोषणा INAK_II			0x08
#घोषणा INAK_IO			0x10
#घोषणा INAK_BI			0x20
#घोषणा INAK_BO			0x40

/* Device Status Register Definitions */
#घोषणा DEV_CON			0x01
#घोषणा DEV_CON_CH		0x02
#घोषणा DEV_SUS			0x04
#घोषणा DEV_SUS_CH		0x08
#घोषणा DEV_RST			0x10

/* Error Code Register Definitions */
#घोषणा ERR_EC_MASK		0x0F
#घोषणा ERR_EA			0x10

/* Error Status Register Definitions */
#घोषणा ERR_PID			0x01
#घोषणा ERR_UEPKT		0x02
#घोषणा ERR_DCRC		0x04
#घोषणा ERR_TIMOUT		0x08
#घोषणा ERR_EOP			0x10
#घोषणा ERR_B_OVRN		0x20
#घोषणा ERR_BTSTF		0x40
#घोषणा ERR_TGL			0x80

/* Endpoपूर्णांक Select Register Definitions */
#घोषणा EP_SEL_F		0x01
#घोषणा EP_SEL_ST		0x02
#घोषणा EP_SEL_STP		0x04
#घोषणा EP_SEL_PO		0x08
#घोषणा EP_SEL_EPN		0x10
#घोषणा EP_SEL_B_1_FULL		0x20
#घोषणा EP_SEL_B_2_FULL		0x40

/* Endpoपूर्णांक Status Register Definitions */
#घोषणा EP_STAT_ST		0x01
#घोषणा EP_STAT_DA		0x20
#घोषणा EP_STAT_RF_MO		0x40
#घोषणा EP_STAT_CND_ST		0x80

/* Clear Buffer Register Definitions */
#घोषणा CLR_BUF_PO		0x01

/* DMA Interrupt Bit Definitions */
#घोषणा EOT_INT			0x01
#घोषणा NDD_REQ_INT		0x02
#घोषणा SYS_ERR_INT		0x04

#घोषणा	DRIVER_VERSION	"1.03"
अटल स्थिर अक्षर driver_name[] = "lpc32xx_udc";

/*
 *
 * proc पूर्णांकerface support
 *
 */
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
अटल अक्षर *epnames[] = अणु"INT", "ISO", "BULK", "CTRL"पूर्ण;
अटल स्थिर अक्षर debug_filename[] = "driver/udc";

अटल व्योम proc_ep_show(काष्ठा seq_file *s, काष्ठा lpc32xx_ep *ep)
अणु
	काष्ठा lpc32xx_request *req;

	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "%12s, maxpacket %4d %3s",
			ep->ep.name, ep->ep.maxpacket,
			ep->is_in ? "in" : "out");
	seq_म_लिखो(s, " type %4s", epnames[ep->eptype]);
	seq_म_लिखो(s, " ints: %12d", ep->totalपूर्णांकs);

	अगर (list_empty(&ep->queue))
		seq_म_लिखो(s, "\t(queue empty)\n");
	अन्यथा अणु
		list_क्रम_each_entry(req, &ep->queue, queue) अणु
			u32 length = req->req.actual;

			seq_म_लिखो(s, "\treq %p len %d/%d buf %p\n",
				   &req->req, length,
				   req->req.length, req->req.buf);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक udc_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा lpc32xx_udc *udc = s->निजी;
	काष्ठा lpc32xx_ep *ep;
	अचिन्हित दीर्घ flags;

	seq_म_लिखो(s, "%s: version %s\n", driver_name, DRIVER_VERSION);

	spin_lock_irqsave(&udc->lock, flags);

	seq_म_लिखो(s, "vbus %s, pullup %s, %s powered%s, gadget %s\n\n",
		   udc->vbus ? "present" : "off",
		   udc->enabled ? (udc->vbus ? "active" : "enabled") :
		   "disabled",
		   udc->gadget.is_selfघातered ? "self" : "VBUS",
		   udc->suspended ? ", suspended" : "",
		   udc->driver ? udc->driver->driver.name : "(none)");

	अगर (udc->enabled && udc->vbus) अणु
		proc_ep_show(s, &udc->ep[0]);
		list_क्रम_each_entry(ep, &udc->gadget.ep_list, ep.ep_list)
			proc_ep_show(s, ep);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(udc);

अटल व्योम create_debug_file(काष्ठा lpc32xx_udc *udc)
अणु
	udc->pde = debugfs_create_file(debug_filename, 0, शून्य, udc, &udc_fops);
पूर्ण

अटल व्योम हटाओ_debug_file(काष्ठा lpc32xx_udc *udc)
अणु
	debugfs_हटाओ(udc->pde);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम create_debug_file(काष्ठा lpc32xx_udc *udc) अणुपूर्ण
अटल अंतरभूत व्योम हटाओ_debug_file(काष्ठा lpc32xx_udc *udc) अणुपूर्ण
#पूर्ण_अगर

/* Primary initialization sequence क्रम the ISP1301 transceiver */
अटल व्योम isp1301_udc_configure(काष्ठा lpc32xx_udc *udc)
अणु
	u8 value;
	s32 venकरोr, product;

	venकरोr = i2c_smbus_पढ़ो_word_data(udc->isp1301_i2c_client, 0x00);
	product = i2c_smbus_पढ़ो_word_data(udc->isp1301_i2c_client, 0x02);

	अगर (venकरोr == 0x0483 && product == 0xa0c4)
		udc->atx = STOTG04;

	/* LPC32XX only supports DAT_SE0 USB mode */
	/* This sequence is important */

	/* Disable transparent UART mode first */
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_MODE_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR),
		MC1_UART_EN);

	/* Set full speed and SE0 mode */
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_MODE_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR), ~0);
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_MODE_CONTROL_1, (MC1_SPEED_REG | MC1_DAT_SE0));

	/*
	 * The PSW_OE enable bit state is reversed in the ISP1301 User's Guide
	 */
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_MODE_CONTROL_2 | ISP1301_I2C_REG_CLEAR_ADDR), ~0);

	value = MC2_BI_DI;
	अगर (udc->atx != STOTG04)
		value |= MC2_SPD_SUSP_CTRL;
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_MODE_CONTROL_2, value);

	/* Driver VBUS_DRV high or low depending on board setup */
	अगर (udc->board->vbus_drv_pol != 0)
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DRV);
	अन्यथा
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR,
			OTG1_VBUS_DRV);

	/* Bi-directional mode with suspend control
	 * Enable both pullकरोwns क्रम now - the pullup will be enable when VBUS
	 * is detected */
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR), ~0);
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_OTG_CONTROL_1,
		(0 | OTG1_DM_PULLDOWN | OTG1_DP_PULLDOWN));

	/* Disअक्षरge VBUS (just in हाल) */
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DISCHRG);
	msleep(1);
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR),
		OTG1_VBUS_DISCHRG);

	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_LATCH | ISP1301_I2C_REG_CLEAR_ADDR, ~0);

	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_FALLING | ISP1301_I2C_REG_CLEAR_ADDR, ~0);
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_RISING | ISP1301_I2C_REG_CLEAR_ADDR, ~0);

	dev_info(udc->dev, "ISP1301 Vendor ID  : 0x%04x\n", venकरोr);
	dev_info(udc->dev, "ISP1301 Product ID : 0x%04x\n", product);
	dev_info(udc->dev, "ISP1301 Version ID : 0x%04x\n",
		 i2c_smbus_पढ़ो_word_data(udc->isp1301_i2c_client, 0x14));

पूर्ण

/* Enables or disables the USB device pullup via the ISP1301 transceiver */
अटल व्योम isp1301_pullup_set(काष्ठा lpc32xx_udc *udc)
अणु
	अगर (udc->pullup)
		/* Enable pullup क्रम bus संकेतling */
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_OTG_CONTROL_1, OTG1_DP_PULLUP);
	अन्यथा
		/* Enable pullup क्रम bus संकेतling */
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR,
			OTG1_DP_PULLUP);
पूर्ण

अटल व्योम pullup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lpc32xx_udc *udc =
		container_of(work, काष्ठा lpc32xx_udc, pullup_job);

	isp1301_pullup_set(udc);
पूर्ण

अटल व्योम isp1301_pullup_enable(काष्ठा lpc32xx_udc *udc, पूर्णांक en_pullup,
				  पूर्णांक block)
अणु
	अगर (en_pullup == udc->pullup)
		वापस;

	udc->pullup = en_pullup;
	अगर (block)
		isp1301_pullup_set(udc);
	अन्यथा
		/* defer slow i2c pull up setting */
		schedule_work(&udc->pullup_job);
पूर्ण

#अगर_घोषित CONFIG_PM
/* Powers up or करोwn the ISP1301 transceiver */
अटल व्योम isp1301_set_घातerstate(काष्ठा lpc32xx_udc *udc, पूर्णांक enable)
अणु
	/* There is no "global power down" रेजिस्टर क्रम stotg04 */
	अगर (udc->atx == STOTG04)
		वापस;

	अगर (enable != 0)
		/* Power up ISP1301 - this ISP1301 will स्वतःmatically wakeup
		   when VBUS is detected */
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_MODE_CONTROL_2 | ISP1301_I2C_REG_CLEAR_ADDR,
			MC2_GLOBAL_PWR_DN);
	अन्यथा
		/* Power करोwn ISP1301 */
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_MODE_CONTROL_2, MC2_GLOBAL_PWR_DN);
पूर्ण

अटल व्योम घातer_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lpc32xx_udc *udc =
		container_of(work, काष्ठा lpc32xx_udc, घातer_job);

	isp1301_set_घातerstate(udc, udc->घातeron);
पूर्ण
#पूर्ण_अगर

/*
 *
 * USB protocol engine command/data पढ़ो/ग_लिखो helper functions
 *
 */
/* Issues a single command to the USB device state machine */
अटल व्योम udc_protocol_cmd_w(काष्ठा lpc32xx_udc *udc, u32 cmd)
अणु
	u32 pass = 0;
	पूर्णांक to;

	/* EP may lock on CLRI अगर this पढ़ो isn't करोne */
	u32 पंचांगp = पढ़ोl(USBD_DEVINTST(udc->udp_baseaddr));
	(व्योम) पंचांगp;

	जबतक (pass == 0) अणु
		ग_लिखोl(USBD_CCEMPTY, USBD_DEVINTCLR(udc->udp_baseaddr));

		/* Write command code */
		ग_लिखोl(cmd, USBD_CMDCODE(udc->udp_baseaddr));
		to = 10000;
		जबतक (((पढ़ोl(USBD_DEVINTST(udc->udp_baseaddr)) &
			 USBD_CCEMPTY) == 0) && (to > 0)) अणु
			to--;
		पूर्ण

		अगर (to > 0)
			pass = 1;

		cpu_relax();
	पूर्ण
पूर्ण

/* Issues 2 commands (or command and data) to the USB device state machine */
अटल अंतरभूत व्योम udc_protocol_cmd_data_w(काष्ठा lpc32xx_udc *udc, u32 cmd,
					   u32 data)
अणु
	udc_protocol_cmd_w(udc, cmd);
	udc_protocol_cmd_w(udc, data);
पूर्ण

/* Issues a single command to the USB device state machine and पढ़ोs
 * response data */
अटल u32 udc_protocol_cmd_r(काष्ठा lpc32xx_udc *udc, u32 cmd)
अणु
	पूर्णांक to = 1000;

	/* Write a command and पढ़ो data from the protocol engine */
	ग_लिखोl((USBD_CDFULL | USBD_CCEMPTY),
		     USBD_DEVINTCLR(udc->udp_baseaddr));

	/* Write command code */
	udc_protocol_cmd_w(udc, cmd);

	जबतक ((!(पढ़ोl(USBD_DEVINTST(udc->udp_baseaddr)) & USBD_CDFULL))
	       && (to > 0))
		to--;
	अगर (!to)
		dev_dbg(udc->dev,
			"Protocol engine didn't receive response (CDFULL)\n");

	वापस पढ़ोl(USBD_CMDDATA(udc->udp_baseaddr));
पूर्ण

/*
 *
 * USB device पूर्णांकerrupt mask support functions
 *
 */
/* Enable one or more USB device पूर्णांकerrupts */
अटल अंतरभूत व्योम uda_enable_devपूर्णांक(काष्ठा lpc32xx_udc *udc, u32 devmask)
अणु
	udc->enabled_devपूर्णांकs |= devmask;
	ग_लिखोl(udc->enabled_devपूर्णांकs, USBD_DEVINTEN(udc->udp_baseaddr));
पूर्ण

/* Disable one or more USB device पूर्णांकerrupts */
अटल अंतरभूत व्योम uda_disable_devपूर्णांक(काष्ठा lpc32xx_udc *udc, u32 mask)
अणु
	udc->enabled_devपूर्णांकs &= ~mask;
	ग_लिखोl(udc->enabled_devपूर्णांकs, USBD_DEVINTEN(udc->udp_baseaddr));
पूर्ण

/* Clear one or more USB device पूर्णांकerrupts */
अटल अंतरभूत व्योम uda_clear_devपूर्णांक(काष्ठा lpc32xx_udc *udc, u32 mask)
अणु
	ग_लिखोl(mask, USBD_DEVINTCLR(udc->udp_baseaddr));
पूर्ण

/*
 *
 * Endpoपूर्णांक पूर्णांकerrupt disable/enable functions
 *
 */
/* Enable one or more USB endpoपूर्णांक पूर्णांकerrupts */
अटल व्योम uda_enable_hwepपूर्णांक(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc->enabled_hwepपूर्णांकs |= (1 << hwep);
	ग_लिखोl(udc->enabled_hwepपूर्णांकs, USBD_EPINTEN(udc->udp_baseaddr));
पूर्ण

/* Disable one or more USB endpoपूर्णांक पूर्णांकerrupts */
अटल व्योम uda_disable_hwepपूर्णांक(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc->enabled_hwepपूर्णांकs &= ~(1 << hwep);
	ग_लिखोl(udc->enabled_hwepपूर्णांकs, USBD_EPINTEN(udc->udp_baseaddr));
पूर्ण

/* Clear one or more USB endpoपूर्णांक पूर्णांकerrupts */
अटल अंतरभूत व्योम uda_clear_hwepपूर्णांक(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	ग_लिखोl((1 << hwep), USBD_EPINTCLR(udc->udp_baseaddr));
पूर्ण

/* Enable DMA क्रम the HW channel */
अटल अंतरभूत व्योम udc_ep_dma_enable(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	ग_लिखोl((1 << hwep), USBD_EPDMAEN(udc->udp_baseaddr));
पूर्ण

/* Disable DMA क्रम the HW channel */
अटल अंतरभूत व्योम udc_ep_dma_disable(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	ग_लिखोl((1 << hwep), USBD_EPDMADIS(udc->udp_baseaddr));
पूर्ण

/*
 *
 * Endpoपूर्णांक realize/unrealize functions
 *
 */
/* Beक्रमe an endpoपूर्णांक can be used, it needs to be realized
 * in the USB protocol engine - this realizes the endpoपूर्णांक.
 * The पूर्णांकerrupt (FIFO or DMA) is not enabled with this function */
अटल व्योम udc_realize_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep,
			     u32 maxpacket)
अणु
	पूर्णांक to = 1000;

	ग_लिखोl(USBD_EP_RLZED, USBD_DEVINTCLR(udc->udp_baseaddr));
	ग_लिखोl(hwep, USBD_EPIND(udc->udp_baseaddr));
	udc->realized_eps |= (1 << hwep);
	ग_लिखोl(udc->realized_eps, USBD_REEP(udc->udp_baseaddr));
	ग_लिखोl(maxpacket, USBD_EPMAXPSIZE(udc->udp_baseaddr));

	/* Wait until endpoपूर्णांक is realized in hardware */
	जबतक ((!(पढ़ोl(USBD_DEVINTST(udc->udp_baseaddr)) &
		  USBD_EP_RLZED)) && (to > 0))
		to--;
	अगर (!to)
		dev_dbg(udc->dev, "EP not correctly realized in hardware\n");

	ग_लिखोl(USBD_EP_RLZED, USBD_DEVINTCLR(udc->udp_baseaddr));
पूर्ण

/* Unrealize an EP */
अटल व्योम udc_unrealize_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc->realized_eps &= ~(1 << hwep);
	ग_लिखोl(udc->realized_eps, USBD_REEP(udc->udp_baseaddr));
पूर्ण

/*
 *
 * Endpoपूर्णांक support functions
 *
 */
/* Select and clear endpoपूर्णांक पूर्णांकerrupt */
अटल u32 udc_selep_clrपूर्णांक(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc_protocol_cmd_w(udc, CMD_SEL_EP_CLRI(hwep));
	वापस udc_protocol_cmd_r(udc, DAT_SEL_EP_CLRI(hwep));
पूर्ण

/* Disables the endpoपूर्णांक in the USB protocol engine */
अटल व्योम udc_disable_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc_protocol_cmd_data_w(udc, CMD_SET_EP_STAT(hwep),
				DAT_WR_BYTE(EP_STAT_DA));
पूर्ण

/* Stalls the endpoपूर्णांक - endpoपूर्णांक will वापस STALL */
अटल व्योम udc_stall_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc_protocol_cmd_data_w(udc, CMD_SET_EP_STAT(hwep),
				DAT_WR_BYTE(EP_STAT_ST));
पूर्ण

/* Clear stall or reset endpoपूर्णांक */
अटल व्योम udc_clrstall_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc_protocol_cmd_data_w(udc, CMD_SET_EP_STAT(hwep),
				DAT_WR_BYTE(0));
पूर्ण

/* Select an endpoपूर्णांक क्रम endpoपूर्णांक status, clear, validate */
अटल व्योम udc_select_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc_protocol_cmd_w(udc, CMD_SEL_EP(hwep));
पूर्ण

/*
 *
 * Endpoपूर्णांक buffer management functions
 *
 */
/* Clear the current endpoपूर्णांक's buffer */
अटल व्योम udc_clr_buffer_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc_select_hwep(udc, hwep);
	udc_protocol_cmd_w(udc, CMD_CLR_BUF);
पूर्ण

/* Validate the current endpoपूर्णांक's buffer */
अटल व्योम udc_val_buffer_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	udc_select_hwep(udc, hwep);
	udc_protocol_cmd_w(udc, CMD_VALID_BUF);
पूर्ण

अटल अंतरभूत u32 udc_clearep_माला_लोts(काष्ठा lpc32xx_udc *udc, u32 hwep)
अणु
	/* Clear EP पूर्णांकerrupt */
	uda_clear_hwepपूर्णांक(udc, hwep);
	वापस udc_selep_clrपूर्णांक(udc, hwep);
पूर्ण

/*
 *
 * USB EP DMA support
 *
 */
/* Allocate a DMA Descriptor */
अटल काष्ठा lpc32xx_usbd_dd_gad *udc_dd_alloc(काष्ठा lpc32xx_udc *udc)
अणु
	dma_addr_t			dma;
	काष्ठा lpc32xx_usbd_dd_gad	*dd;

	dd = dma_pool_alloc(udc->dd_cache, GFP_ATOMIC | GFP_DMA, &dma);
	अगर (dd)
		dd->this_dma = dma;

	वापस dd;
पूर्ण

/* Free a DMA Descriptor */
अटल व्योम udc_dd_मुक्त(काष्ठा lpc32xx_udc *udc, काष्ठा lpc32xx_usbd_dd_gad *dd)
अणु
	dma_pool_मुक्त(udc->dd_cache, dd, dd->this_dma);
पूर्ण

/*
 *
 * USB setup and shutकरोwn functions
 *
 */
/* Enables or disables most of the USB प्रणाली घड़ीs when low घातer mode is
 * needed. Clocks are typically started on a connection event, and disabled
 * when a cable is disconnected */
अटल व्योम udc_clk_set(काष्ठा lpc32xx_udc *udc, पूर्णांक enable)
अणु
	अगर (enable != 0) अणु
		अगर (udc->घड़ीed)
			वापस;

		udc->घड़ीed = 1;
		clk_prepare_enable(udc->usb_slv_clk);
	पूर्ण अन्यथा अणु
		अगर (!udc->घड़ीed)
			वापस;

		udc->घड़ीed = 0;
		clk_disable_unprepare(udc->usb_slv_clk);
	पूर्ण
पूर्ण

/* Set/reset USB device address */
अटल व्योम udc_set_address(काष्ठा lpc32xx_udc *udc, u32 addr)
अणु
	/* Address will be latched at the end of the status phase, or
	   latched immediately अगर function is called twice */
	udc_protocol_cmd_data_w(udc, CMD_SET_ADDR,
				DAT_WR_BYTE(DEV_EN | addr));
पूर्ण

/* Setup up a IN request क्रम DMA transfer - this consists of determining the
 * list of DMA addresses क्रम the transfer, allocating DMA Descriptors,
 * installing the DD पूर्णांकo the UDCA, and then enabling the DMA क्रम that EP */
अटल पूर्णांक udc_ep_in_req_dma(काष्ठा lpc32xx_udc *udc, काष्ठा lpc32xx_ep *ep)
अणु
	काष्ठा lpc32xx_request *req;
	u32 hwep = ep->hwep_num;

	ep->req_pending = 1;

	/* There will always be a request रुकोing here */
	req = list_entry(ep->queue.next, काष्ठा lpc32xx_request, queue);

	/* Place the DD Descriptor पूर्णांकo the UDCA */
	udc->udca_v_base[hwep] = req->dd_desc_ptr->this_dma;

	/* Enable DMA and पूर्णांकerrupt क्रम the HW EP */
	udc_ep_dma_enable(udc, hwep);

	/* Clear ZLP अगर last packet is not of MAXP size */
	अगर (req->req.length % ep->ep.maxpacket)
		req->send_zlp = 0;

	वापस 0;
पूर्ण

/* Setup up a OUT request क्रम DMA transfer - this consists of determining the
 * list of DMA addresses क्रम the transfer, allocating DMA Descriptors,
 * installing the DD पूर्णांकo the UDCA, and then enabling the DMA क्रम that EP */
अटल पूर्णांक udc_ep_out_req_dma(काष्ठा lpc32xx_udc *udc, काष्ठा lpc32xx_ep *ep)
अणु
	काष्ठा lpc32xx_request *req;
	u32 hwep = ep->hwep_num;

	ep->req_pending = 1;

	/* There will always be a request रुकोing here */
	req = list_entry(ep->queue.next, काष्ठा lpc32xx_request, queue);

	/* Place the DD Descriptor पूर्णांकo the UDCA */
	udc->udca_v_base[hwep] = req->dd_desc_ptr->this_dma;

	/* Enable DMA and पूर्णांकerrupt क्रम the HW EP */
	udc_ep_dma_enable(udc, hwep);
	वापस 0;
पूर्ण

अटल व्योम udc_disable(काष्ठा lpc32xx_udc *udc)
अणु
	u32 i;

	/* Disable device */
	udc_protocol_cmd_data_w(udc, CMD_CFG_DEV, DAT_WR_BYTE(0));
	udc_protocol_cmd_data_w(udc, CMD_SET_DEV_STAT, DAT_WR_BYTE(0));

	/* Disable all device पूर्णांकerrupts (including EP0) */
	uda_disable_devपूर्णांक(udc, 0x3FF);

	/* Disable and reset all endpoपूर्णांक पूर्णांकerrupts */
	क्रम (i = 0; i < 32; i++) अणु
		uda_disable_hwepपूर्णांक(udc, i);
		uda_clear_hwepपूर्णांक(udc, i);
		udc_disable_hwep(udc, i);
		udc_unrealize_hwep(udc, i);
		udc->udca_v_base[i] = 0;

		/* Disable and clear all पूर्णांकerrupts and DMA */
		udc_ep_dma_disable(udc, i);
		ग_लिखोl((1 << i), USBD_EOTINTCLR(udc->udp_baseaddr));
		ग_लिखोl((1 << i), USBD_NDDRTINTCLR(udc->udp_baseaddr));
		ग_लिखोl((1 << i), USBD_SYSERRTINTCLR(udc->udp_baseaddr));
		ग_लिखोl((1 << i), USBD_DMARCLR(udc->udp_baseaddr));
	पूर्ण

	/* Disable DMA पूर्णांकerrupts */
	ग_लिखोl(0, USBD_DMAINTEN(udc->udp_baseaddr));

	ग_लिखोl(0, USBD_UDCAH(udc->udp_baseaddr));
पूर्ण

अटल व्योम udc_enable(काष्ठा lpc32xx_udc *udc)
अणु
	u32 i;
	काष्ठा lpc32xx_ep *ep = &udc->ep[0];

	/* Start with known state */
	udc_disable(udc);

	/* Enable device */
	udc_protocol_cmd_data_w(udc, CMD_SET_DEV_STAT, DAT_WR_BYTE(DEV_CON));

	/* EP पूर्णांकerrupts on high priority, FRAME पूर्णांकerrupt on low priority */
	ग_लिखोl(USBD_EP_FAST, USBD_DEVINTPRI(udc->udp_baseaddr));
	ग_लिखोl(0xFFFF, USBD_EPINTPRI(udc->udp_baseaddr));

	/* Clear any pending device पूर्णांकerrupts */
	ग_लिखोl(0x3FF, USBD_DEVINTCLR(udc->udp_baseaddr));

	/* Setup UDCA - not yet used (DMA) */
	ग_लिखोl(udc->udca_p_base, USBD_UDCAH(udc->udp_baseaddr));

	/* Only enable EP0 in and out क्रम now, EP0 only works in FIFO mode */
	क्रम (i = 0; i <= 1; i++) अणु
		udc_realize_hwep(udc, i, ep->ep.maxpacket);
		uda_enable_hwepपूर्णांक(udc, i);
		udc_select_hwep(udc, i);
		udc_clrstall_hwep(udc, i);
		udc_clr_buffer_hwep(udc, i);
	पूर्ण

	/* Device पूर्णांकerrupt setup */
	uda_clear_devपूर्णांक(udc, (USBD_ERR_INT | USBD_DEV_STAT | USBD_EP_SLOW |
			       USBD_EP_FAST));
	uda_enable_devपूर्णांक(udc, (USBD_ERR_INT | USBD_DEV_STAT | USBD_EP_SLOW |
				USBD_EP_FAST));

	/* Set device address to 0 - called twice to क्रमce a latch in the USB
	   engine without the need of a setup packet status closure */
	udc_set_address(udc, 0);
	udc_set_address(udc, 0);

	/* Enable master DMA पूर्णांकerrupts */
	ग_लिखोl((USBD_SYS_ERR_INT | USBD_EOT_INT),
		     USBD_DMAINTEN(udc->udp_baseaddr));

	udc->dev_status = 0;
पूर्ण

/*
 *
 * USB device board specअगरic events handled via callbacks
 *
 */
/* Connection change event - notअगरy board function of change */
अटल व्योम uda_घातer_event(काष्ठा lpc32xx_udc *udc, u32 conn)
अणु
	/* Just notअगरy of a connection change event (optional) */
	अगर (udc->board->conn_chgb != शून्य)
		udc->board->conn_chgb(conn);
पूर्ण

/* Suspend/resume event - notअगरy board function of change */
अटल व्योम uda_resm_susp_event(काष्ठा lpc32xx_udc *udc, u32 conn)
अणु
	/* Just notअगरy of a Suspend/resume change event (optional) */
	अगर (udc->board->susp_chgb != शून्य)
		udc->board->susp_chgb(conn);

	अगर (conn)
		udc->suspended = 0;
	अन्यथा
		udc->suspended = 1;
पूर्ण

/* Remote wakeup enable/disable - notअगरy board function of change */
अटल व्योम uda_remwkp_cgh(काष्ठा lpc32xx_udc *udc)
अणु
	अगर (udc->board->rmwk_chgb != शून्य)
		udc->board->rmwk_chgb(udc->dev_status &
				      (1 << USB_DEVICE_REMOTE_WAKEUP));
पूर्ण

/* Reads data from FIFO, adjusts क्रम alignment and data size */
अटल व्योम udc_pop_fअगरo(काष्ठा lpc32xx_udc *udc, u8 *data, u32 bytes)
अणु
	पूर्णांक n, i, bl;
	u16 *p16;
	u32 *p32, पंचांगp, cbytes;

	/* Use optimal data transfer method based on source address and size */
	चयन (((uपूर्णांकptr_t) data) & 0x3) अणु
	हाल 0: /* 32-bit aligned */
		p32 = (u32 *) data;
		cbytes = (bytes & ~0x3);

		/* Copy 32-bit aligned data first */
		क्रम (n = 0; n < cbytes; n += 4)
			*p32++ = पढ़ोl(USBD_RXDATA(udc->udp_baseaddr));

		/* Handle any reमुख्यing bytes */
		bl = bytes - cbytes;
		अगर (bl) अणु
			पंचांगp = पढ़ोl(USBD_RXDATA(udc->udp_baseaddr));
			क्रम (n = 0; n < bl; n++)
				data[cbytes + n] = ((पंचांगp >> (n * 8)) & 0xFF);

		पूर्ण
		अवरोध;

	हाल 1: /* 8-bit aligned */
	हाल 3:
		/* Each byte has to be handled independently */
		क्रम (n = 0; n < bytes; n += 4) अणु
			पंचांगp = पढ़ोl(USBD_RXDATA(udc->udp_baseaddr));

			bl = bytes - n;
			अगर (bl > 4)
				bl = 4;

			क्रम (i = 0; i < bl; i++)
				data[n + i] = (u8) ((पंचांगp >> (i * 8)) & 0xFF);
		पूर्ण
		अवरोध;

	हाल 2: /* 16-bit aligned */
		p16 = (u16 *) data;
		cbytes = (bytes & ~0x3);

		/* Copy 32-bit sized objects first with 16-bit alignment */
		क्रम (n = 0; n < cbytes; n += 4) अणु
			पंचांगp = पढ़ोl(USBD_RXDATA(udc->udp_baseaddr));
			*p16++ = (u16)(पंचांगp & 0xFFFF);
			*p16++ = (u16)((पंचांगp >> 16) & 0xFFFF);
		पूर्ण

		/* Handle any reमुख्यing bytes */
		bl = bytes - cbytes;
		अगर (bl) अणु
			पंचांगp = पढ़ोl(USBD_RXDATA(udc->udp_baseaddr));
			क्रम (n = 0; n < bl; n++)
				data[cbytes + n] = ((पंचांगp >> (n * 8)) & 0xFF);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/* Read data from the FIFO क्रम an endpoपूर्णांक. This function is क्रम endpoपूर्णांकs (such
 * as EP0) that करोn't use DMA. This function should only be called अगर a packet
 * is known to be पढ़ोy to पढ़ो क्रम the endpoपूर्णांक. Note that the endpoपूर्णांक must
 * be selected in the protocol engine prior to this call. */
अटल u32 udc_पढ़ो_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep, u32 *data,
			 u32 bytes)
अणु
	u32 पंचांगpv;
	पूर्णांक to = 1000;
	u32 पंचांगp, hwrep = ((hwep & 0x1E) << 1) | CTRL_RD_EN;

	/* Setup पढ़ो of endpoपूर्णांक */
	ग_लिखोl(hwrep, USBD_CTRL(udc->udp_baseaddr));

	/* Wait until packet is पढ़ोy */
	जबतक ((((पंचांगpv = पढ़ोl(USBD_RXPLEN(udc->udp_baseaddr))) &
		 PKT_RDY) == 0)	&& (to > 0))
		to--;
	अगर (!to)
		dev_dbg(udc->dev, "No packet ready on FIFO EP read\n");

	/* Mask out count */
	पंचांगp = पंचांगpv & PKT_LNGTH_MASK;
	अगर (bytes < पंचांगp)
		पंचांगp = bytes;

	अगर ((पंचांगp > 0) && (data != शून्य))
		udc_pop_fअगरo(udc, (u8 *) data, पंचांगp);

	ग_लिखोl(((hwep & 0x1E) << 1), USBD_CTRL(udc->udp_baseaddr));

	/* Clear the buffer */
	udc_clr_buffer_hwep(udc, hwep);

	वापस पंचांगp;
पूर्ण

/* Stuffs data पूर्णांकo the FIFO, adjusts क्रम alignment and data size */
अटल व्योम udc_stuff_fअगरo(काष्ठा lpc32xx_udc *udc, u8 *data, u32 bytes)
अणु
	पूर्णांक n, i, bl;
	u16 *p16;
	u32 *p32, पंचांगp, cbytes;

	/* Use optimal data transfer method based on source address and size */
	चयन (((uपूर्णांकptr_t) data) & 0x3) अणु
	हाल 0: /* 32-bit aligned */
		p32 = (u32 *) data;
		cbytes = (bytes & ~0x3);

		/* Copy 32-bit aligned data first */
		क्रम (n = 0; n < cbytes; n += 4)
			ग_लिखोl(*p32++, USBD_TXDATA(udc->udp_baseaddr));

		/* Handle any reमुख्यing bytes */
		bl = bytes - cbytes;
		अगर (bl) अणु
			पंचांगp = 0;
			क्रम (n = 0; n < bl; n++)
				पंचांगp |= data[cbytes + n] << (n * 8);

			ग_लिखोl(पंचांगp, USBD_TXDATA(udc->udp_baseaddr));
		पूर्ण
		अवरोध;

	हाल 1: /* 8-bit aligned */
	हाल 3:
		/* Each byte has to be handled independently */
		क्रम (n = 0; n < bytes; n += 4) अणु
			bl = bytes - n;
			अगर (bl > 4)
				bl = 4;

			पंचांगp = 0;
			क्रम (i = 0; i < bl; i++)
				पंचांगp |= data[n + i] << (i * 8);

			ग_लिखोl(पंचांगp, USBD_TXDATA(udc->udp_baseaddr));
		पूर्ण
		अवरोध;

	हाल 2: /* 16-bit aligned */
		p16 = (u16 *) data;
		cbytes = (bytes & ~0x3);

		/* Copy 32-bit aligned data first */
		क्रम (n = 0; n < cbytes; n += 4) अणु
			पंचांगp = *p16++ & 0xFFFF;
			पंचांगp |= (*p16++ & 0xFFFF) << 16;
			ग_लिखोl(पंचांगp, USBD_TXDATA(udc->udp_baseaddr));
		पूर्ण

		/* Handle any reमुख्यing bytes */
		bl = bytes - cbytes;
		अगर (bl) अणु
			पंचांगp = 0;
			क्रम (n = 0; n < bl; n++)
				पंचांगp |= data[cbytes + n] << (n * 8);

			ग_लिखोl(पंचांगp, USBD_TXDATA(udc->udp_baseaddr));
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/* Write data to the FIFO क्रम an endpoपूर्णांक. This function is क्रम endpoपूर्णांकs (such
 * as EP0) that करोn't use DMA. Note that the endpoपूर्णांक must be selected in the
 * protocol engine prior to this call. */
अटल व्योम udc_ग_लिखो_hwep(काष्ठा lpc32xx_udc *udc, u32 hwep, u32 *data,
			   u32 bytes)
अणु
	u32 hwwep = ((hwep & 0x1E) << 1) | CTRL_WR_EN;

	अगर ((bytes > 0) && (data == शून्य))
		वापस;

	/* Setup ग_लिखो of endpoपूर्णांक */
	ग_लिखोl(hwwep, USBD_CTRL(udc->udp_baseaddr));

	ग_लिखोl(bytes, USBD_TXPLEN(udc->udp_baseaddr));

	/* Need at least 1 byte to trigger TX */
	अगर (bytes == 0)
		ग_लिखोl(0, USBD_TXDATA(udc->udp_baseaddr));
	अन्यथा
		udc_stuff_fअगरo(udc, (u8 *) data, bytes);

	ग_लिखोl(((hwep & 0x1E) << 1), USBD_CTRL(udc->udp_baseaddr));

	udc_val_buffer_hwep(udc, hwep);
पूर्ण

/* USB device reset - resets USB to a शेष state with just EP0
   enabled */
अटल व्योम uda_usb_reset(काष्ठा lpc32xx_udc *udc)
अणु
	u32 i = 0;
	/* Re-init device controller and EP0 */
	udc_enable(udc);
	udc->gadget.speed = USB_SPEED_FULL;

	क्रम (i = 1; i < NUM_ENDPOINTS; i++) अणु
		काष्ठा lpc32xx_ep *ep = &udc->ep[i];
		ep->req_pending = 0;
	पूर्ण
पूर्ण

/* Send a ZLP on EP0 */
अटल व्योम udc_ep0_send_zlp(काष्ठा lpc32xx_udc *udc)
अणु
	udc_ग_लिखो_hwep(udc, EP_IN, शून्य, 0);
पूर्ण

/* Get current frame number */
अटल u16 udc_get_current_frame(काष्ठा lpc32xx_udc *udc)
अणु
	u16 flo, fhi;

	udc_protocol_cmd_w(udc, CMD_RD_FRAME);
	flo = (u16) udc_protocol_cmd_r(udc, DAT_RD_FRAME);
	fhi = (u16) udc_protocol_cmd_r(udc, DAT_RD_FRAME);

	वापस (fhi << 8) | flo;
पूर्ण

/* Set the device as configured - enables all endpoपूर्णांकs */
अटल अंतरभूत व्योम udc_set_device_configured(काष्ठा lpc32xx_udc *udc)
अणु
	udc_protocol_cmd_data_w(udc, CMD_CFG_DEV, DAT_WR_BYTE(CONF_DVICE));
पूर्ण

/* Set the device as unconfigured - disables all endpoपूर्णांकs */
अटल अंतरभूत व्योम udc_set_device_unconfigured(काष्ठा lpc32xx_udc *udc)
अणु
	udc_protocol_cmd_data_w(udc, CMD_CFG_DEV, DAT_WR_BYTE(0));
पूर्ण

/* reinit == restore initial software state */
अटल व्योम udc_reinit(काष्ठा lpc32xx_udc *udc)
अणु
	u32 i;

	INIT_LIST_HEAD(&udc->gadget.ep_list);
	INIT_LIST_HEAD(&udc->gadget.ep0->ep_list);

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		काष्ठा lpc32xx_ep *ep = &udc->ep[i];

		अगर (i != 0)
			list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
		usb_ep_set_maxpacket_limit(&ep->ep, ep->maxpacket);
		INIT_LIST_HEAD(&ep->queue);
		ep->req_pending = 0;
	पूर्ण

	udc->ep0state = WAIT_FOR_SETUP;
पूर्ण

/* Must be called with lock */
अटल व्योम करोne(काष्ठा lpc32xx_ep *ep, काष्ठा lpc32xx_request *req, पूर्णांक status)
अणु
	काष्ठा lpc32xx_udc *udc = ep->udc;

	list_del_init(&req->queue);
	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	अगर (ep->lep) अणु
		usb_gadget_unmap_request(&udc->gadget, &req->req, ep->is_in);

		/* Free DDs */
		udc_dd_मुक्त(udc, req->dd_desc_ptr);
	पूर्ण

	अगर (status && status != -ESHUTDOWN)
		ep_dbg(ep, "%s done %p, status %d\n", ep->ep.name, req, status);

	ep->req_pending = 0;
	spin_unlock(&udc->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&udc->lock);
पूर्ण

/* Must be called with lock */
अटल व्योम nuke(काष्ठा lpc32xx_ep *ep, पूर्णांक status)
अणु
	काष्ठा lpc32xx_request *req;

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा lpc32xx_request, queue);
		करोne(ep, req, status);
	पूर्ण

	अगर (status == -ESHUTDOWN) अणु
		uda_disable_hwepपूर्णांक(ep->udc, ep->hwep_num);
		udc_disable_hwep(ep->udc, ep->hwep_num);
	पूर्ण
पूर्ण

/* IN endpoपूर्णांक 0 transfer */
अटल पूर्णांक udc_ep0_in_req(काष्ठा lpc32xx_udc *udc)
अणु
	काष्ठा lpc32xx_request *req;
	काष्ठा lpc32xx_ep *ep0 = &udc->ep[0];
	u32 tsend, ts = 0;

	अगर (list_empty(&ep0->queue))
		/* Nothing to send */
		वापस 0;
	अन्यथा
		req = list_entry(ep0->queue.next, काष्ठा lpc32xx_request,
				 queue);

	tsend = ts = req->req.length - req->req.actual;
	अगर (ts == 0) अणु
		/* Send a ZLP */
		udc_ep0_send_zlp(udc);
		करोne(ep0, req, 0);
		वापस 1;
	पूर्ण अन्यथा अगर (ts > ep0->ep.maxpacket)
		ts = ep0->ep.maxpacket; /* Just send what we can */

	/* Write data to the EP0 FIFO and start transfer */
	udc_ग_लिखो_hwep(udc, EP_IN, (req->req.buf + req->req.actual), ts);

	/* Increment data poपूर्णांकer */
	req->req.actual += ts;

	अगर (tsend >= ep0->ep.maxpacket)
		वापस 0; /* Stay in data transfer state */

	/* Transfer request is complete */
	udc->ep0state = WAIT_FOR_SETUP;
	करोne(ep0, req, 0);
	वापस 1;
पूर्ण

/* OUT endpoपूर्णांक 0 transfer */
अटल पूर्णांक udc_ep0_out_req(काष्ठा lpc32xx_udc *udc)
अणु
	काष्ठा lpc32xx_request *req;
	काष्ठा lpc32xx_ep *ep0 = &udc->ep[0];
	u32 tr, bufferspace;

	अगर (list_empty(&ep0->queue))
		वापस 0;
	अन्यथा
		req = list_entry(ep0->queue.next, काष्ठा lpc32xx_request,
				 queue);

	अगर (req) अणु
		अगर (req->req.length == 0) अणु
			/* Just dequeue request */
			करोne(ep0, req, 0);
			udc->ep0state = WAIT_FOR_SETUP;
			वापस 1;
		पूर्ण

		/* Get data from FIFO */
		bufferspace = req->req.length - req->req.actual;
		अगर (bufferspace > ep0->ep.maxpacket)
			bufferspace = ep0->ep.maxpacket;

		/* Copy data to buffer */
		prefetchw(req->req.buf + req->req.actual);
		tr = udc_पढ़ो_hwep(udc, EP_OUT, req->req.buf + req->req.actual,
				   bufferspace);
		req->req.actual += bufferspace;

		अगर (tr < ep0->ep.maxpacket) अणु
			/* This is the last packet */
			करोne(ep0, req, 0);
			udc->ep0state = WAIT_FOR_SETUP;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Must be called with lock */
अटल व्योम stop_activity(काष्ठा lpc32xx_udc *udc)
अणु
	काष्ठा usb_gadget_driver *driver = udc->driver;
	पूर्णांक i;

	अगर (udc->gadget.speed == USB_SPEED_UNKNOWN)
		driver = शून्य;

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->suspended = 0;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		काष्ठा lpc32xx_ep *ep = &udc->ep[i];
		nuke(ep, -ESHUTDOWN);
	पूर्ण
	अगर (driver) अणु
		spin_unlock(&udc->lock);
		driver->disconnect(&udc->gadget);
		spin_lock(&udc->lock);
	पूर्ण

	isp1301_pullup_enable(udc, 0, 0);
	udc_disable(udc);
	udc_reinit(udc);
पूर्ण

/*
 * Activate or समाप्त host pullup
 * Can be called with or without lock
 */
अटल व्योम pullup(काष्ठा lpc32xx_udc *udc, पूर्णांक is_on)
अणु
	अगर (!udc->घड़ीed)
		वापस;

	अगर (!udc->enabled || !udc->vbus)
		is_on = 0;

	अगर (is_on != udc->pullup)
		isp1301_pullup_enable(udc, is_on, 0);
पूर्ण

/* Must be called without lock */
अटल पूर्णांक lpc32xx_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा lpc32xx_ep *ep = container_of(_ep, काष्ठा lpc32xx_ep, ep);
	काष्ठा lpc32xx_udc *udc = ep->udc;
	अचिन्हित दीर्घ	flags;

	अगर ((ep->hwep_num_base == 0) || (ep->hwep_num == 0))
		वापस -EINVAL;
	spin_lock_irqsave(&udc->lock, flags);

	nuke(ep, -ESHUTDOWN);

	/* Clear all DMA statuses क्रम this EP */
	udc_ep_dma_disable(udc, ep->hwep_num);
	ग_लिखोl(1 << ep->hwep_num, USBD_EOTINTCLR(udc->udp_baseaddr));
	ग_लिखोl(1 << ep->hwep_num, USBD_NDDRTINTCLR(udc->udp_baseaddr));
	ग_लिखोl(1 << ep->hwep_num, USBD_SYSERRTINTCLR(udc->udp_baseaddr));
	ग_लिखोl(1 << ep->hwep_num, USBD_DMARCLR(udc->udp_baseaddr));

	/* Remove the DD poपूर्णांकer in the UDCA */
	udc->udca_v_base[ep->hwep_num] = 0;

	/* Disable and reset endpoपूर्णांक and पूर्णांकerrupt */
	uda_clear_hwepपूर्णांक(udc, ep->hwep_num);
	udc_unrealize_hwep(udc, ep->hwep_num);

	ep->hwep_num = 0;

	spin_unlock_irqrestore(&udc->lock, flags);

	atomic_dec(&udc->enabled_ep_cnt);
	wake_up(&udc->ep_disable_रुको_queue);

	वापस 0;
पूर्ण

/* Must be called without lock */
अटल पूर्णांक lpc32xx_ep_enable(काष्ठा usb_ep *_ep,
			     स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा lpc32xx_ep *ep = container_of(_ep, काष्ठा lpc32xx_ep, ep);
	काष्ठा lpc32xx_udc *udc;
	u16 maxpacket;
	u32 पंचांगp;
	अचिन्हित दीर्घ flags;

	/* Verअगरy EP data */
	अगर ((!_ep) || (!ep) || (!desc) ||
	    (desc->bDescriptorType != USB_DT_ENDPOINT))
		वापस -EINVAL;

	udc = ep->udc;
	maxpacket = usb_endpoपूर्णांक_maxp(desc);
	अगर ((maxpacket == 0) || (maxpacket > ep->maxpacket)) अणु
		dev_dbg(udc->dev, "bad ep descriptor's packet size\n");
		वापस -EINVAL;
	पूर्ण

	/* Don't touch EP0 */
	अगर (ep->hwep_num_base == 0) अणु
		dev_dbg(udc->dev, "Can't re-enable EP0!!!\n");
		वापस -EINVAL;
	पूर्ण

	/* Is driver पढ़ोy? */
	अगर ((!udc->driver) || (udc->gadget.speed == USB_SPEED_UNKNOWN)) अणु
		dev_dbg(udc->dev, "bogus device state\n");
		वापस -ESHUTDOWN;
	पूर्ण

	पंचांगp = desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
	चयन (पंचांगp) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		वापस -EINVAL;

	हाल USB_ENDPOINT_XFER_INT:
		अगर (maxpacket > ep->maxpacket) अणु
			dev_dbg(udc->dev,
				"Bad INT endpoint maxpacket %d\n", maxpacket);
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल USB_ENDPOINT_XFER_BULK:
		चयन (maxpacket) अणु
		हाल 8:
		हाल 16:
		हाल 32:
		हाल 64:
			अवरोध;

		शेष:
			dev_dbg(udc->dev,
				"Bad BULK endpoint maxpacket %d\n", maxpacket);
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल USB_ENDPOINT_XFER_ISOC:
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&udc->lock, flags);

	/* Initialize endpoपूर्णांक to match the selected descriptor */
	ep->is_in = (desc->bEndpoपूर्णांकAddress & USB_सूची_IN) != 0;
	ep->ep.maxpacket = maxpacket;

	/* Map hardware endpoपूर्णांक from base and direction */
	अगर (ep->is_in)
		/* IN endpoपूर्णांकs are offset 1 from the OUT endpoपूर्णांक */
		ep->hwep_num = ep->hwep_num_base + EP_IN;
	अन्यथा
		ep->hwep_num = ep->hwep_num_base;

	ep_dbg(ep, "EP enabled: %s, HW:%d, MP:%d IN:%d\n", ep->ep.name,
	       ep->hwep_num, maxpacket, (ep->is_in == 1));

	/* Realize the endpoपूर्णांक, पूर्णांकerrupt is enabled later when
	 * buffers are queued, IN EPs will NAK until buffers are पढ़ोy */
	udc_realize_hwep(udc, ep->hwep_num, ep->ep.maxpacket);
	udc_clr_buffer_hwep(udc, ep->hwep_num);
	uda_disable_hwepपूर्णांक(udc, ep->hwep_num);
	udc_clrstall_hwep(udc, ep->hwep_num);

	/* Clear all DMA statuses क्रम this EP */
	udc_ep_dma_disable(udc, ep->hwep_num);
	ग_लिखोl(1 << ep->hwep_num, USBD_EOTINTCLR(udc->udp_baseaddr));
	ग_लिखोl(1 << ep->hwep_num, USBD_NDDRTINTCLR(udc->udp_baseaddr));
	ग_लिखोl(1 << ep->hwep_num, USBD_SYSERRTINTCLR(udc->udp_baseaddr));
	ग_लिखोl(1 << ep->hwep_num, USBD_DMARCLR(udc->udp_baseaddr));

	spin_unlock_irqrestore(&udc->lock, flags);

	atomic_inc(&udc->enabled_ep_cnt);
	वापस 0;
पूर्ण

/*
 * Allocate a USB request list
 * Can be called with or without lock
 */
अटल काष्ठा usb_request *lpc32xx_ep_alloc_request(काष्ठा usb_ep *_ep,
						    gfp_t gfp_flags)
अणु
	काष्ठा lpc32xx_request *req;

	req = kzalloc(माप(काष्ठा lpc32xx_request), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);
	वापस &req->req;
पूर्ण

/*
 * De-allocate a USB request list
 * Can be called with or without lock
 */
अटल व्योम lpc32xx_ep_मुक्त_request(काष्ठा usb_ep *_ep,
				    काष्ठा usb_request *_req)
अणु
	काष्ठा lpc32xx_request *req;

	req = container_of(_req, काष्ठा lpc32xx_request, req);
	BUG_ON(!list_empty(&req->queue));
	kमुक्त(req);
पूर्ण

/* Must be called without lock */
अटल पूर्णांक lpc32xx_ep_queue(काष्ठा usb_ep *_ep,
			    काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा lpc32xx_request *req;
	काष्ठा lpc32xx_ep *ep;
	काष्ठा lpc32xx_udc *udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = 0;

	req = container_of(_req, काष्ठा lpc32xx_request, req);
	ep = container_of(_ep, काष्ठा lpc32xx_ep, ep);

	अगर (!_ep || !_req || !_req->complete || !_req->buf ||
	    !list_empty(&req->queue))
		वापस -EINVAL;

	udc = ep->udc;

	अगर (udc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -EPIPE;

	अगर (ep->lep) अणु
		काष्ठा lpc32xx_usbd_dd_gad *dd;

		status = usb_gadget_map_request(&udc->gadget, _req, ep->is_in);
		अगर (status)
			वापस status;

		/* For the request, build a list of DDs */
		dd = udc_dd_alloc(udc);
		अगर (!dd) अणु
			/* Error allocating DD */
			वापस -ENOMEM;
		पूर्ण
		req->dd_desc_ptr = dd;

		/* Setup the DMA descriptor */
		dd->dd_next_phy = dd->dd_next_v = 0;
		dd->dd_buffer_addr = req->req.dma;
		dd->dd_status = 0;

		/* Special handling क्रम ISO EPs */
		अगर (ep->eptype == EP_ISO_TYPE) अणु
			dd->dd_setup = DD_SETUP_ISO_EP |
				DD_SETUP_PACKETLEN(0) |
				DD_SETUP_DMALENBYTES(1);
			dd->dd_iso_ps_mem_addr = dd->this_dma + 24;
			अगर (ep->is_in)
				dd->iso_status[0] = req->req.length;
			अन्यथा
				dd->iso_status[0] = 0;
		पूर्ण अन्यथा
			dd->dd_setup = DD_SETUP_PACKETLEN(ep->ep.maxpacket) |
				DD_SETUP_DMALENBYTES(req->req.length);
	पूर्ण

	ep_dbg(ep, "%s queue req %p len %d buf %p (in=%d) z=%d\n", _ep->name,
	       _req, _req->length, _req->buf, ep->is_in, _req->zero);

	spin_lock_irqsave(&udc->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;
	req->send_zlp = _req->zero;

	/* Kickstart empty queues */
	अगर (list_empty(&ep->queue)) अणु
		list_add_tail(&req->queue, &ep->queue);

		अगर (ep->hwep_num_base == 0) अणु
			/* Handle expected data direction */
			अगर (ep->is_in) अणु
				/* IN packet to host */
				udc->ep0state = DATA_IN;
				status = udc_ep0_in_req(udc);
			पूर्ण अन्यथा अणु
				/* OUT packet from host */
				udc->ep0state = DATA_OUT;
				status = udc_ep0_out_req(udc);
			पूर्ण
		पूर्ण अन्यथा अगर (ep->is_in) अणु
			/* IN packet to host and kick off transfer */
			अगर (!ep->req_pending)
				udc_ep_in_req_dma(udc, ep);
		पूर्ण अन्यथा
			/* OUT packet from host and kick off list */
			अगर (!ep->req_pending)
				udc_ep_out_req_dma(udc, ep);
	पूर्ण अन्यथा
		list_add_tail(&req->queue, &ep->queue);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस (status < 0) ? status : 0;
पूर्ण

/* Must be called without lock */
अटल पूर्णांक lpc32xx_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा lpc32xx_ep *ep;
	काष्ठा lpc32xx_request *req;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा lpc32xx_ep, ep);
	अगर (!_ep || ep->hwep_num_base == 0)
		वापस -EINVAL;

	spin_lock_irqsave(&ep->udc->lock, flags);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		spin_unlock_irqrestore(&ep->udc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	करोne(ep, req, -ECONNRESET);

	spin_unlock_irqrestore(&ep->udc->lock, flags);

	वापस 0;
पूर्ण

/* Must be called without lock */
अटल पूर्णांक lpc32xx_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा lpc32xx_ep *ep = container_of(_ep, काष्ठा lpc32xx_ep, ep);
	काष्ठा lpc32xx_udc *udc;
	अचिन्हित दीर्घ flags;

	अगर ((!ep) || (ep->hwep_num <= 1))
		वापस -EINVAL;

	/* Don't halt an IN EP */
	अगर (ep->is_in)
		वापस -EAGAIN;

	udc = ep->udc;
	spin_lock_irqsave(&udc->lock, flags);

	अगर (value == 1) अणु
		/* stall */
		udc_protocol_cmd_data_w(udc, CMD_SET_EP_STAT(ep->hwep_num),
					DAT_WR_BYTE(EP_STAT_ST));
	पूर्ण अन्यथा अणु
		/* End stall */
		ep->wedge = 0;
		udc_protocol_cmd_data_w(udc, CMD_SET_EP_STAT(ep->hwep_num),
					DAT_WR_BYTE(0));
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/* set the halt feature and ignores clear requests */
अटल पूर्णांक lpc32xx_ep_set_wedge(काष्ठा usb_ep *_ep)
अणु
	काष्ठा lpc32xx_ep *ep = container_of(_ep, काष्ठा lpc32xx_ep, ep);

	अगर (!_ep || !ep->udc)
		वापस -EINVAL;

	ep->wedge = 1;

	वापस usb_ep_set_halt(_ep);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops lpc32xx_ep_ops = अणु
	.enable		= lpc32xx_ep_enable,
	.disable	= lpc32xx_ep_disable,
	.alloc_request	= lpc32xx_ep_alloc_request,
	.मुक्त_request	= lpc32xx_ep_मुक्त_request,
	.queue		= lpc32xx_ep_queue,
	.dequeue	= lpc32xx_ep_dequeue,
	.set_halt	= lpc32xx_ep_set_halt,
	.set_wedge	= lpc32xx_ep_set_wedge,
पूर्ण;

/* Send a ZLP on a non-0 IN EP */
अटल व्योम udc_send_in_zlp(काष्ठा lpc32xx_udc *udc, काष्ठा lpc32xx_ep *ep)
अणु
	/* Clear EP status */
	udc_clearep_माला_लोts(udc, ep->hwep_num);

	/* Send ZLP via FIFO mechanism */
	udc_ग_लिखो_hwep(udc, ep->hwep_num, शून्य, 0);
पूर्ण

/*
 * Handle EP completion क्रम ZLP
 * This function will only be called when a delayed ZLP needs to be sent out
 * after a DMA transfer has filled both buffers.
 */
अटल व्योम udc_handle_eps(काष्ठा lpc32xx_udc *udc, काष्ठा lpc32xx_ep *ep)
अणु
	u32 epstatus;
	काष्ठा lpc32xx_request *req;

	अगर (ep->hwep_num <= 0)
		वापस;

	uda_clear_hwepपूर्णांक(udc, ep->hwep_num);

	/* If this पूर्णांकerrupt isn't enabled, वापस now */
	अगर (!(udc->enabled_hwepपूर्णांकs & (1 << ep->hwep_num)))
		वापस;

	/* Get endpoपूर्णांक status */
	epstatus = udc_clearep_माला_लोts(udc, ep->hwep_num);

	/*
	 * This should never happen, but protect against writing to the
	 * buffer when full.
	 */
	अगर (epstatus & EP_SEL_F)
		वापस;

	अगर (ep->is_in) अणु
		udc_send_in_zlp(udc, ep);
		uda_disable_hwepपूर्णांक(udc, ep->hwep_num);
	पूर्ण अन्यथा
		वापस;

	/* If there isn't a request रुकोing, something went wrong */
	req = list_entry(ep->queue.next, काष्ठा lpc32xx_request, queue);
	अगर (req) अणु
		करोne(ep, req, 0);

		/* Start another request अगर पढ़ोy */
		अगर (!list_empty(&ep->queue)) अणु
			अगर (ep->is_in)
				udc_ep_in_req_dma(udc, ep);
			अन्यथा
				udc_ep_out_req_dma(udc, ep);
		पूर्ण अन्यथा
			ep->req_pending = 0;
	पूर्ण
पूर्ण


/* DMA end of transfer completion */
अटल व्योम udc_handle_dma_ep(काष्ठा lpc32xx_udc *udc, काष्ठा lpc32xx_ep *ep)
अणु
	u32 status;
	काष्ठा lpc32xx_request *req;
	काष्ठा lpc32xx_usbd_dd_gad *dd;

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
	ep->totalपूर्णांकs++;
#पूर्ण_अगर

	req = list_entry(ep->queue.next, काष्ठा lpc32xx_request, queue);
	अगर (!req) अणु
		ep_err(ep, "DMA interrupt on no req!\n");
		वापस;
	पूर्ण
	dd = req->dd_desc_ptr;

	/* DMA descriptor should always be retired क्रम this call */
	अगर (!(dd->dd_status & DD_STATUS_DD_RETIRED))
		ep_warn(ep, "DMA descriptor did not retire\n");

	/* Disable DMA */
	udc_ep_dma_disable(udc, ep->hwep_num);
	ग_लिखोl((1 << ep->hwep_num), USBD_EOTINTCLR(udc->udp_baseaddr));
	ग_लिखोl((1 << ep->hwep_num), USBD_NDDRTINTCLR(udc->udp_baseaddr));

	/* System error? */
	अगर (पढ़ोl(USBD_SYSERRTINTST(udc->udp_baseaddr)) &
	    (1 << ep->hwep_num)) अणु
		ग_लिखोl((1 << ep->hwep_num),
			     USBD_SYSERRTINTCLR(udc->udp_baseaddr));
		ep_err(ep, "AHB critical error!\n");
		ep->req_pending = 0;

		/* The error could have occurred on a packet of a multipacket
		 * transfer, so recovering the transfer is not possible. Close
		 * the request with an error */
		करोne(ep, req, -ECONNABORTED);
		वापस;
	पूर्ण

	/* Handle the current DD's status */
	status = dd->dd_status;
	चयन (status & DD_STATUS_STS_MASK) अणु
	हाल DD_STATUS_STS_NS:
		/* DD not serviced? This shouldn't happen! */
		ep->req_pending = 0;
		ep_err(ep, "DMA critical EP error: DD not serviced (0x%x)!\n",
		       status);

		करोne(ep, req, -ECONNABORTED);
		वापस;

	हाल DD_STATUS_STS_BS:
		/* Interrupt only fires on EOT - This shouldn't happen! */
		ep->req_pending = 0;
		ep_err(ep, "DMA critical EP error: EOT prior to service completion (0x%x)!\n",
		       status);
		करोne(ep, req, -ECONNABORTED);
		वापस;

	हाल DD_STATUS_STS_NC:
	हाल DD_STATUS_STS_DUR:
		/* Really just a लघु packet, not an underrun */
		/* This is a good status and what we expect */
		अवरोध;

	शेष:
		/* Data overrun, प्रणाली error, or unknown */
		ep->req_pending = 0;
		ep_err(ep, "DMA critical EP error: System error (0x%x)!\n",
		       status);
		करोne(ep, req, -ECONNABORTED);
		वापस;
	पूर्ण

	/* ISO endpoपूर्णांकs are handled dअगरferently */
	अगर (ep->eptype == EP_ISO_TYPE) अणु
		अगर (ep->is_in)
			req->req.actual = req->req.length;
		अन्यथा
			req->req.actual = dd->iso_status[0] & 0xFFFF;
	पूर्ण अन्यथा
		req->req.actual += DD_STATUS_CURDMACNT(status);

	/* Send a ZLP अगर necessary. This will be करोne क्रम non-पूर्णांक
	 * packets which have a size that is a भागisor of MAXP */
	अगर (req->send_zlp) अणु
		/*
		 * If at least 1 buffer is available, send the ZLP now.
		 * Otherwise, the ZLP send needs to be deferred until a
		 * buffer is available.
		 */
		अगर (udc_clearep_माला_लोts(udc, ep->hwep_num) & EP_SEL_F) अणु
			udc_clearep_माला_लोts(udc, ep->hwep_num);
			uda_enable_hwepपूर्णांक(udc, ep->hwep_num);
			udc_clearep_माला_लोts(udc, ep->hwep_num);

			/* Let the EP पूर्णांकerrupt handle the ZLP */
			वापस;
		पूर्ण अन्यथा
			udc_send_in_zlp(udc, ep);
	पूर्ण

	/* Transfer request is complete */
	करोne(ep, req, 0);

	/* Start another request अगर पढ़ोy */
	udc_clearep_माला_लोts(udc, ep->hwep_num);
	अगर (!list_empty((&ep->queue))) अणु
		अगर (ep->is_in)
			udc_ep_in_req_dma(udc, ep);
		अन्यथा
			udc_ep_out_req_dma(udc, ep);
	पूर्ण अन्यथा
		ep->req_pending = 0;

पूर्ण

/*
 *
 * Endpoपूर्णांक 0 functions
 *
 */
अटल व्योम udc_handle_dev(काष्ठा lpc32xx_udc *udc)
अणु
	u32 पंचांगp;

	udc_protocol_cmd_w(udc, CMD_GET_DEV_STAT);
	पंचांगp = udc_protocol_cmd_r(udc, DAT_GET_DEV_STAT);

	अगर (पंचांगp & DEV_RST)
		uda_usb_reset(udc);
	अन्यथा अगर (पंचांगp & DEV_CON_CH)
		uda_घातer_event(udc, (पंचांगp & DEV_CON));
	अन्यथा अगर (पंचांगp & DEV_SUS_CH) अणु
		अगर (पंचांगp & DEV_SUS) अणु
			अगर (udc->vbus == 0)
				stop_activity(udc);
			अन्यथा अगर ((udc->gadget.speed != USB_SPEED_UNKNOWN) &&
				 udc->driver) अणु
				/* Power करोwn transceiver */
				udc->घातeron = 0;
				schedule_work(&udc->pullup_job);
				uda_resm_susp_event(udc, 1);
			पूर्ण
		पूर्ण अन्यथा अगर ((udc->gadget.speed != USB_SPEED_UNKNOWN) &&
			   udc->driver && udc->vbus) अणु
			uda_resm_susp_event(udc, 0);
			/* Power up transceiver */
			udc->घातeron = 1;
			schedule_work(&udc->pullup_job);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक udc_get_status(काष्ठा lpc32xx_udc *udc, u16 reqtype, u16 wIndex)
अणु
	काष्ठा lpc32xx_ep *ep;
	u32 ep0buff = 0, पंचांगp;

	चयन (reqtype & USB_RECIP_MASK) अणु
	हाल USB_RECIP_INTERFACE:
		अवरोध; /* Not supported */

	हाल USB_RECIP_DEVICE:
		ep0buff = udc->gadget.is_selfघातered;
		अगर (udc->dev_status & (1 << USB_DEVICE_REMOTE_WAKEUP))
			ep0buff |= (1 << USB_DEVICE_REMOTE_WAKEUP);
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		पंचांगp = wIndex & USB_ENDPOINT_NUMBER_MASK;
		ep = &udc->ep[पंचांगp];
		अगर ((पंचांगp == 0) || (पंचांगp >= NUM_ENDPOINTS))
			वापस -EOPNOTSUPP;

		अगर (wIndex & USB_सूची_IN) अणु
			अगर (!ep->is_in)
				वापस -EOPNOTSUPP; /* Something's wrong */
		पूर्ण अन्यथा अगर (ep->is_in)
			वापस -EOPNOTSUPP; /* Not an IN endpoपूर्णांक */

		/* Get status of the endpoपूर्णांक */
		udc_protocol_cmd_w(udc, CMD_SEL_EP(ep->hwep_num));
		पंचांगp = udc_protocol_cmd_r(udc, DAT_SEL_EP(ep->hwep_num));

		अगर (पंचांगp & EP_SEL_ST)
			ep0buff = (1 << USB_ENDPOINT_HALT);
		अन्यथा
			ep0buff = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Return data */
	udc_ग_लिखो_hwep(udc, EP_IN, &ep0buff, 2);

	वापस 0;
पूर्ण

अटल व्योम udc_handle_ep0_setup(काष्ठा lpc32xx_udc *udc)
अणु
	काष्ठा lpc32xx_ep *ep, *ep0 = &udc->ep[0];
	काष्ठा usb_ctrlrequest ctrlpkt;
	पूर्णांक i, bytes;
	u16 wIndex, wValue, reqtype, req, पंचांगp;

	/* Nuke previous transfers */
	nuke(ep0, -EPROTO);

	/* Get setup packet */
	bytes = udc_पढ़ो_hwep(udc, EP_OUT, (u32 *) &ctrlpkt, 8);
	अगर (bytes != 8) अणु
		ep_warn(ep0, "Incorrectly sized setup packet (s/b 8, is %d)!\n",
			bytes);
		वापस;
	पूर्ण

	/* Native endianness */
	wIndex = le16_to_cpu(ctrlpkt.wIndex);
	wValue = le16_to_cpu(ctrlpkt.wValue);
	reqtype = le16_to_cpu(ctrlpkt.bRequestType);

	/* Set direction of EP0 */
	अगर (likely(reqtype & USB_सूची_IN))
		ep0->is_in = 1;
	अन्यथा
		ep0->is_in = 0;

	/* Handle SETUP packet */
	req = le16_to_cpu(ctrlpkt.bRequest);
	चयन (req) अणु
	हाल USB_REQ_CLEAR_FEATURE:
	हाल USB_REQ_SET_FEATURE:
		चयन (reqtype) अणु
		हाल (USB_TYPE_STANDARD | USB_RECIP_DEVICE):
			अगर (wValue != USB_DEVICE_REMOTE_WAKEUP)
				जाओ stall; /* Nothing अन्यथा handled */

			/* Tell board about event */
			अगर (req == USB_REQ_CLEAR_FEATURE)
				udc->dev_status &=
					~(1 << USB_DEVICE_REMOTE_WAKEUP);
			अन्यथा
				udc->dev_status |=
					(1 << USB_DEVICE_REMOTE_WAKEUP);
			uda_remwkp_cgh(udc);
			जाओ zlp_send;

		हाल (USB_TYPE_STANDARD | USB_RECIP_ENDPOINT):
			पंचांगp = wIndex & USB_ENDPOINT_NUMBER_MASK;
			अगर ((wValue != USB_ENDPOINT_HALT) ||
			    (पंचांगp >= NUM_ENDPOINTS))
				अवरोध;

			/* Find hardware endpoपूर्णांक from logical endpoपूर्णांक */
			ep = &udc->ep[पंचांगp];
			पंचांगp = ep->hwep_num;
			अगर (पंचांगp == 0)
				अवरोध;

			अगर (req == USB_REQ_SET_FEATURE)
				udc_stall_hwep(udc, पंचांगp);
			अन्यथा अगर (!ep->wedge)
				udc_clrstall_hwep(udc, पंचांगp);

			जाओ zlp_send;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल USB_REQ_SET_ADDRESS:
		अगर (reqtype == (USB_TYPE_STANDARD | USB_RECIP_DEVICE)) अणु
			udc_set_address(udc, wValue);
			जाओ zlp_send;
		पूर्ण
		अवरोध;

	हाल USB_REQ_GET_STATUS:
		udc_get_status(udc, reqtype, wIndex);
		वापस;

	शेष:
		अवरोध; /* Let GadgetFS handle the descriptor instead */
	पूर्ण

	अगर (likely(udc->driver)) अणु
		/* device-2-host (IN) or no data setup command, process
		 * immediately */
		spin_unlock(&udc->lock);
		i = udc->driver->setup(&udc->gadget, &ctrlpkt);

		spin_lock(&udc->lock);
		अगर (req == USB_REQ_SET_CONFIGURATION) अणु
			/* Configuration is set after endpoपूर्णांकs are realized */
			अगर (wValue) अणु
				/* Set configuration */
				udc_set_device_configured(udc);

				udc_protocol_cmd_data_w(udc, CMD_SET_MODE,
							DAT_WR_BYTE(AP_CLK |
							INAK_BI | INAK_II));
			पूर्ण अन्यथा अणु
				/* Clear configuration */
				udc_set_device_unconfigured(udc);

				/* Disable NAK पूर्णांकerrupts */
				udc_protocol_cmd_data_w(udc, CMD_SET_MODE,
							DAT_WR_BYTE(AP_CLK));
			पूर्ण
		पूर्ण

		अगर (i < 0) अणु
			/* setup processing failed, क्रमce stall */
			dev_dbg(udc->dev,
				"req %02x.%02x protocol STALL; stat %d\n",
				reqtype, req, i);
			udc->ep0state = WAIT_FOR_SETUP;
			जाओ stall;
		पूर्ण
	पूर्ण

	अगर (!ep0->is_in)
		udc_ep0_send_zlp(udc); /* ZLP IN packet on data phase */

	वापस;

stall:
	udc_stall_hwep(udc, EP_IN);
	वापस;

zlp_send:
	udc_ep0_send_zlp(udc);
	वापस;
पूर्ण

/* IN endpoपूर्णांक 0 transfer */
अटल व्योम udc_handle_ep0_in(काष्ठा lpc32xx_udc *udc)
अणु
	काष्ठा lpc32xx_ep *ep0 = &udc->ep[0];
	u32 epstatus;

	/* Clear EP पूर्णांकerrupt */
	epstatus = udc_clearep_माला_लोts(udc, EP_IN);

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
	ep0->totalपूर्णांकs++;
#पूर्ण_अगर

	/* Stalled? Clear stall and reset buffers */
	अगर (epstatus & EP_SEL_ST) अणु
		udc_clrstall_hwep(udc, EP_IN);
		nuke(ep0, -ECONNABORTED);
		udc->ep0state = WAIT_FOR_SETUP;
		वापस;
	पूर्ण

	/* Is a buffer available? */
	अगर (!(epstatus & EP_SEL_F)) अणु
		/* Handle based on current state */
		अगर (udc->ep0state == DATA_IN)
			udc_ep0_in_req(udc);
		अन्यथा अणु
			/* Unknown state क्रम EP0 oe end of DATA IN phase */
			nuke(ep0, -ECONNABORTED);
			udc->ep0state = WAIT_FOR_SETUP;
		पूर्ण
	पूर्ण
पूर्ण

/* OUT endpoपूर्णांक 0 transfer */
अटल व्योम udc_handle_ep0_out(काष्ठा lpc32xx_udc *udc)
अणु
	काष्ठा lpc32xx_ep *ep0 = &udc->ep[0];
	u32 epstatus;

	/* Clear EP पूर्णांकerrupt */
	epstatus = udc_clearep_माला_लोts(udc, EP_OUT);


#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
	ep0->totalपूर्णांकs++;
#पूर्ण_अगर

	/* Stalled? */
	अगर (epstatus & EP_SEL_ST) अणु
		udc_clrstall_hwep(udc, EP_OUT);
		nuke(ep0, -ECONNABORTED);
		udc->ep0state = WAIT_FOR_SETUP;
		वापस;
	पूर्ण

	/* A NAK may occur अगर a packet couldn't be received yet */
	अगर (epstatus & EP_SEL_EPN)
		वापस;
	/* Setup packet incoming? */
	अगर (epstatus & EP_SEL_STP) अणु
		nuke(ep0, 0);
		udc->ep0state = WAIT_FOR_SETUP;
	पूर्ण

	/* Data available? */
	अगर (epstatus & EP_SEL_F)
		/* Handle based on current state */
		चयन (udc->ep0state) अणु
		हाल WAIT_FOR_SETUP:
			udc_handle_ep0_setup(udc);
			अवरोध;

		हाल DATA_OUT:
			udc_ep0_out_req(udc);
			अवरोध;

		शेष:
			/* Unknown state क्रम EP0 */
			nuke(ep0, -ECONNABORTED);
			udc->ep0state = WAIT_FOR_SETUP;
		पूर्ण
पूर्ण

/* Must be called without lock */
अटल पूर्णांक lpc32xx_get_frame(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक frame;
	अचिन्हित दीर्घ flags;
	काष्ठा lpc32xx_udc *udc = to_udc(gadget);

	अगर (!udc->घड़ीed)
		वापस -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);

	frame = (पूर्णांक) udc_get_current_frame(udc);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस frame;
पूर्ण

अटल पूर्णांक lpc32xx_wakeup(काष्ठा usb_gadget *gadget)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक lpc32xx_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	gadget->is_selfघातered = (is_on != 0);

	वापस 0;
पूर्ण

/*
 * vbus is here!  turn everything on that's पढ़ोy
 * Must be called without lock
 */
अटल पूर्णांक lpc32xx_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lpc32xx_udc *udc = to_udc(gadget);

	spin_lock_irqsave(&udc->lock, flags);

	/* Doesn't need lock */
	अगर (udc->driver) अणु
		udc_clk_set(udc, 1);
		udc_enable(udc);
		pullup(udc, is_active);
	पूर्ण अन्यथा अणु
		stop_activity(udc);
		pullup(udc, 0);

		spin_unlock_irqrestore(&udc->lock, flags);
		/*
		 *  Wait क्रम all the endpoपूर्णांकs to disable,
		 *  beक्रमe disabling घड़ीs. Don't रुको अगर
		 *  endpoपूर्णांकs are not enabled.
		 */
		अगर (atomic_पढ़ो(&udc->enabled_ep_cnt))
			रुको_event_पूर्णांकerruptible(udc->ep_disable_रुको_queue,
				 (atomic_पढ़ो(&udc->enabled_ep_cnt) == 0));

		spin_lock_irqsave(&udc->lock, flags);

		udc_clk_set(udc, 0);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

/* Can be called with or without lock */
अटल पूर्णांक lpc32xx_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा lpc32xx_udc *udc = to_udc(gadget);

	/* Doesn't need lock */
	pullup(udc, is_on);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_start(काष्ठा usb_gadget *, काष्ठा usb_gadget_driver *);
अटल पूर्णांक lpc32xx_stop(काष्ठा usb_gadget *);

अटल स्थिर काष्ठा usb_gadget_ops lpc32xx_udc_ops = अणु
	.get_frame		= lpc32xx_get_frame,
	.wakeup			= lpc32xx_wakeup,
	.set_selfघातered	= lpc32xx_set_selfघातered,
	.vbus_session		= lpc32xx_vbus_session,
	.pullup			= lpc32xx_pullup,
	.udc_start		= lpc32xx_start,
	.udc_stop		= lpc32xx_stop,
पूर्ण;

अटल व्योम nop_release(काष्ठा device *dev)
अणु
	/* nothing to मुक्त */
पूर्ण

अटल स्थिर काष्ठा lpc32xx_udc controller_ढाँचा = अणु
	.gadget = अणु
		.ops	= &lpc32xx_udc_ops,
		.name	= driver_name,
		.dev	= अणु
			.init_name = "gadget",
			.release = nop_release,
		पूर्ण
	पूर्ण,
	.ep[0] = अणु
		.ep = अणु
			.name	= "ep0",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 0,
		.hwep_num	= 0, /* Can be 0 or 1, has special handling */
		.lep		= 0,
		.eptype		= EP_CTL_TYPE,
	पूर्ण,
	.ep[1] = अणु
		.ep = अणु
			.name	= "ep1-int",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_INT,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 2,
		.hwep_num	= 0, /* 2 or 3, will be set later */
		.lep		= 1,
		.eptype		= EP_INT_TYPE,
	पूर्ण,
	.ep[2] = अणु
		.ep = अणु
			.name	= "ep2-bulk",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 4,
		.hwep_num	= 0, /* 4 or 5, will be set later */
		.lep		= 2,
		.eptype		= EP_BLK_TYPE,
	पूर्ण,
	.ep[3] = अणु
		.ep = अणु
			.name	= "ep3-iso",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 1023,
		.hwep_num_base	= 6,
		.hwep_num	= 0, /* 6 or 7, will be set later */
		.lep		= 3,
		.eptype		= EP_ISO_TYPE,
	पूर्ण,
	.ep[4] = अणु
		.ep = अणु
			.name	= "ep4-int",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_INT,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 8,
		.hwep_num	= 0, /* 8 or 9, will be set later */
		.lep		= 4,
		.eptype		= EP_INT_TYPE,
	पूर्ण,
	.ep[5] = अणु
		.ep = अणु
			.name	= "ep5-bulk",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 10,
		.hwep_num	= 0, /* 10 or 11, will be set later */
		.lep		= 5,
		.eptype		= EP_BLK_TYPE,
	पूर्ण,
	.ep[6] = अणु
		.ep = अणु
			.name	= "ep6-iso",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 1023,
		.hwep_num_base	= 12,
		.hwep_num	= 0, /* 12 or 13, will be set later */
		.lep		= 6,
		.eptype		= EP_ISO_TYPE,
	पूर्ण,
	.ep[7] = अणु
		.ep = अणु
			.name	= "ep7-int",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_INT,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 14,
		.hwep_num	= 0,
		.lep		= 7,
		.eptype		= EP_INT_TYPE,
	पूर्ण,
	.ep[8] = अणु
		.ep = अणु
			.name	= "ep8-bulk",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 16,
		.hwep_num	= 0,
		.lep		= 8,
		.eptype		= EP_BLK_TYPE,
	पूर्ण,
	.ep[9] = अणु
		.ep = अणु
			.name	= "ep9-iso",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 1023,
		.hwep_num_base	= 18,
		.hwep_num	= 0,
		.lep		= 9,
		.eptype		= EP_ISO_TYPE,
	पूर्ण,
	.ep[10] = अणु
		.ep = अणु
			.name	= "ep10-int",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_INT,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 20,
		.hwep_num	= 0,
		.lep		= 10,
		.eptype		= EP_INT_TYPE,
	पूर्ण,
	.ep[11] = अणु
		.ep = अणु
			.name	= "ep11-bulk",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 22,
		.hwep_num	= 0,
		.lep		= 11,
		.eptype		= EP_BLK_TYPE,
	पूर्ण,
	.ep[12] = अणु
		.ep = अणु
			.name	= "ep12-iso",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 1023,
		.hwep_num_base	= 24,
		.hwep_num	= 0,
		.lep		= 12,
		.eptype		= EP_ISO_TYPE,
	पूर्ण,
	.ep[13] = अणु
		.ep = अणु
			.name	= "ep13-int",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_INT,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 26,
		.hwep_num	= 0,
		.lep		= 13,
		.eptype		= EP_INT_TYPE,
	पूर्ण,
	.ep[14] = अणु
		.ep = अणु
			.name	= "ep14-bulk",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 64,
		.hwep_num_base	= 28,
		.hwep_num	= 0,
		.lep		= 14,
		.eptype		= EP_BLK_TYPE,
	पूर्ण,
	.ep[15] = अणु
		.ep = अणु
			.name	= "ep15-bulk",
			.ops	= &lpc32xx_ep_ops,
			.caps	= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
					USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.maxpacket	= 1023,
		.hwep_num_base	= 30,
		.hwep_num	= 0,
		.lep		= 15,
		.eptype		= EP_BLK_TYPE,
	पूर्ण,
पूर्ण;

/* ISO and status पूर्णांकerrupts */
अटल irqवापस_t lpc32xx_usb_lp_irq(पूर्णांक irq, व्योम *_udc)
अणु
	u32 पंचांगp, devstat;
	काष्ठा lpc32xx_udc *udc = _udc;

	spin_lock(&udc->lock);

	/* Read the device status रेजिस्टर */
	devstat = पढ़ोl(USBD_DEVINTST(udc->udp_baseaddr));

	devstat &= ~USBD_EP_FAST;
	ग_लिखोl(devstat, USBD_DEVINTCLR(udc->udp_baseaddr));
	devstat = devstat & udc->enabled_devपूर्णांकs;

	/* Device specअगरic handling needed? */
	अगर (devstat & USBD_DEV_STAT)
		udc_handle_dev(udc);

	/* Start of frame? (devstat & FRAME_INT):
	 * The frame पूर्णांकerrupt isn't really needed क्रम ISO support,
	 * as the driver will queue the necessary packets */

	/* Error? */
	अगर (devstat & ERR_INT) अणु
		/* All types of errors, from cable removal during transfer to
		 * misc protocol and bit errors. These are mostly क्रम just info,
		 * as the USB hardware will work around these. If these errors
		 * happen alot, something is wrong. */
		udc_protocol_cmd_w(udc, CMD_RD_ERR_STAT);
		पंचांगp = udc_protocol_cmd_r(udc, DAT_RD_ERR_STAT);
		dev_dbg(udc->dev, "Device error (0x%x)!\n", पंचांगp);
	पूर्ण

	spin_unlock(&udc->lock);

	वापस IRQ_HANDLED;
पूर्ण

/* EP पूर्णांकerrupts */
अटल irqवापस_t lpc32xx_usb_hp_irq(पूर्णांक irq, व्योम *_udc)
अणु
	u32 पंचांगp;
	काष्ठा lpc32xx_udc *udc = _udc;

	spin_lock(&udc->lock);

	/* Read the device status रेजिस्टर */
	ग_लिखोl(USBD_EP_FAST, USBD_DEVINTCLR(udc->udp_baseaddr));

	/* Endpoपूर्णांकs */
	पंचांगp = पढ़ोl(USBD_EPINTST(udc->udp_baseaddr));

	/* Special handling क्रम EP0 */
	अगर (पंचांगp & (EP_MASK_SEL(0, EP_OUT) | EP_MASK_SEL(0, EP_IN))) अणु
		/* Handle EP0 IN */
		अगर (पंचांगp & (EP_MASK_SEL(0, EP_IN)))
			udc_handle_ep0_in(udc);

		/* Handle EP0 OUT */
		अगर (पंचांगp & (EP_MASK_SEL(0, EP_OUT)))
			udc_handle_ep0_out(udc);
	पूर्ण

	/* All other EPs */
	अगर (पंचांगp & ~(EP_MASK_SEL(0, EP_OUT) | EP_MASK_SEL(0, EP_IN))) अणु
		पूर्णांक i;

		/* Handle other EP पूर्णांकerrupts */
		क्रम (i = 1; i < NUM_ENDPOINTS; i++) अणु
			अगर (पंचांगp & (1 << udc->ep[i].hwep_num))
				udc_handle_eps(udc, &udc->ep[i]);
		पूर्ण
	पूर्ण

	spin_unlock(&udc->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lpc32xx_usb_devdma_irq(पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा lpc32xx_udc *udc = _udc;

	पूर्णांक i;
	u32 पंचांगp;

	spin_lock(&udc->lock);

	/* Handle EP DMA EOT पूर्णांकerrupts */
	पंचांगp = पढ़ोl(USBD_EOTINTST(udc->udp_baseaddr)) |
		(पढ़ोl(USBD_EPDMAST(udc->udp_baseaddr)) &
		 पढ़ोl(USBD_NDDRTINTST(udc->udp_baseaddr))) |
		पढ़ोl(USBD_SYSERRTINTST(udc->udp_baseaddr));
	क्रम (i = 1; i < NUM_ENDPOINTS; i++) अणु
		अगर (पंचांगp & (1 << udc->ep[i].hwep_num))
			udc_handle_dma_ep(udc, &udc->ep[i]);
	पूर्ण

	spin_unlock(&udc->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 *
 * VBUS detection, pullup handler, and Gadget cable state notअगरication
 *
 */
अटल व्योम vbus_work(काष्ठा lpc32xx_udc *udc)
अणु
	u8 value;

	अगर (udc->enabled != 0) अणु
		/* Disअक्षरge VBUS real quick */
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DISCHRG);

		/* Give VBUS some समय (100mS) to disअक्षरge */
		msleep(100);

		/* Disable VBUS disअक्षरge resistor */
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR,
			OTG1_VBUS_DISCHRG);

		/* Clear पूर्णांकerrupt */
		i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_INTERRUPT_LATCH |
			ISP1301_I2C_REG_CLEAR_ADDR, ~0);

		/* Get the VBUS status from the transceiver */
		value = i2c_smbus_पढ़ो_byte_data(udc->isp1301_i2c_client,
						 ISP1301_I2C_INTERRUPT_SOURCE);

		/* VBUS on or off? */
		अगर (value & INT_SESS_VLD)
			udc->vbus = 1;
		अन्यथा
			udc->vbus = 0;

		/* VBUS changed? */
		अगर (udc->last_vbus != udc->vbus) अणु
			udc->last_vbus = udc->vbus;
			lpc32xx_vbus_session(&udc->gadget, udc->vbus);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t lpc32xx_usb_vbus_irq(पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा lpc32xx_udc *udc = _udc;

	vbus_work(udc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lpc32xx_start(काष्ठा usb_gadget *gadget,
			 काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा lpc32xx_udc *udc = to_udc(gadget);

	अगर (!driver || driver->max_speed < USB_SPEED_FULL || !driver->setup) अणु
		dev_err(udc->dev, "bad parameter.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (udc->driver) अणु
		dev_err(udc->dev, "UDC already has a gadget driver\n");
		वापस -EBUSY;
	पूर्ण

	udc->driver = driver;
	udc->gadget.dev.of_node = udc->dev->of_node;
	udc->enabled = 1;
	udc->gadget.is_selfघातered = 1;
	udc->vbus = 0;

	/* Force VBUS process once to check क्रम cable insertion */
	udc->last_vbus = udc->vbus = 0;
	vbus_work(udc);

	/* enable पूर्णांकerrupts */
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_FALLING, INT_SESS_VLD | INT_VBUS_VLD);
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_RISING, INT_SESS_VLD | INT_VBUS_VLD);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा lpc32xx_udc *udc = to_udc(gadget);

	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_FALLING | ISP1301_I2C_REG_CLEAR_ADDR, ~0);
	i2c_smbus_ग_लिखो_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_RISING | ISP1301_I2C_REG_CLEAR_ADDR, ~0);

	अगर (udc->घड़ीed) अणु
		spin_lock(&udc->lock);
		stop_activity(udc);
		spin_unlock(&udc->lock);

		/*
		 *  Wait क्रम all the endpoपूर्णांकs to disable,
		 *  beक्रमe disabling घड़ीs. Don't रुको अगर
		 *  endpoपूर्णांकs are not enabled.
		 */
		अगर (atomic_पढ़ो(&udc->enabled_ep_cnt))
			रुको_event_पूर्णांकerruptible(udc->ep_disable_रुको_queue,
				(atomic_पढ़ो(&udc->enabled_ep_cnt) == 0));

		spin_lock(&udc->lock);
		udc_clk_set(udc, 0);
		spin_unlock(&udc->lock);
	पूर्ण

	udc->enabled = 0;
	udc->driver = शून्य;

	वापस 0;
पूर्ण

अटल व्योम lpc32xx_udc_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	/* Force disconnect on reboot */
	काष्ठा lpc32xx_udc *udc = platक्रमm_get_drvdata(dev);

	pullup(udc, 0);
पूर्ण

/*
 * Callbacks to be overridden by options passed via OF (TODO)
 */

अटल व्योम lpc32xx_usbd_conn_chg(पूर्णांक conn)
अणु
	/* Do nothing, it might be nice to enable an LED
	 * based on conn state being !0 */
पूर्ण

अटल व्योम lpc32xx_usbd_susp_chg(पूर्णांक susp)
अणु
	/* Device suspend अगर susp != 0 */
पूर्ण

अटल व्योम lpc32xx_rmwkup_chg(पूर्णांक remote_wakup_enable)
अणु
	/* Enable or disable USB remote wakeup */
पूर्ण

अटल काष्ठा lpc32xx_usbd_cfg lpc32xx_usbddata = अणु
	.vbus_drv_pol = 0,
	.conn_chgb = &lpc32xx_usbd_conn_chg,
	.susp_chgb = &lpc32xx_usbd_susp_chg,
	.rmwk_chgb = &lpc32xx_rmwkup_chg,
पूर्ण;


अटल u64 lpc32xx_usbd_dmamask = ~(u32) 0x7F;

अटल पूर्णांक lpc32xx_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा lpc32xx_udc *udc;
	पूर्णांक retval, i;
	dma_addr_t dma_handle;
	काष्ठा device_node *isp1301_node;

	udc = devm_kmemdup(dev, &controller_ढाँचा, माप(*udc), GFP_KERNEL);
	अगर (!udc)
		वापस -ENOMEM;

	क्रम (i = 0; i <= 15; i++)
		udc->ep[i].udc = udc;
	udc->gadget.ep0 = &udc->ep[0].ep;

	/* init software state */
	udc->gadget.dev.parent = dev;
	udc->pdev = pdev;
	udc->dev = &pdev->dev;
	udc->enabled = 0;

	अगर (pdev->dev.of_node) अणु
		isp1301_node = of_parse_phandle(pdev->dev.of_node,
						"transceiver", 0);
	पूर्ण अन्यथा अणु
		isp1301_node = शून्य;
	पूर्ण

	udc->isp1301_i2c_client = isp1301_get_client(isp1301_node);
	अगर (!udc->isp1301_i2c_client) अणु
		वापस -EPROBE_DEFER;
	पूर्ण

	dev_info(udc->dev, "ISP1301 I2C device at address 0x%x\n",
		 udc->isp1301_i2c_client->addr);

	pdev->dev.dma_mask = &lpc32xx_usbd_dmamask;
	retval = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (retval)
		वापस retval;

	udc->board = &lpc32xx_usbddata;

	/*
	 * Resources are mapped as follows:
	 *  IORESOURCE_MEM, base address and size of USB space
	 *  IORESOURCE_IRQ, USB device low priority पूर्णांकerrupt number
	 *  IORESOURCE_IRQ, USB device high priority पूर्णांकerrupt number
	 *  IORESOURCE_IRQ, USB device पूर्णांकerrupt number
	 *  IORESOURCE_IRQ, USB transceiver पूर्णांकerrupt number
	 */

	spin_lock_init(&udc->lock);

	/* Get IRQs */
	क्रम (i = 0; i < 4; i++) अणु
		udc->udp_irq[i] = platक्रमm_get_irq(pdev, i);
		अगर (udc->udp_irq[i] < 0)
			वापस udc->udp_irq[i];
	पूर्ण

	udc->udp_baseaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(udc->udp_baseaddr)) अणु
		dev_err(udc->dev, "IO map failure\n");
		वापस PTR_ERR(udc->udp_baseaddr);
	पूर्ण

	/* Get USB device घड़ी */
	udc->usb_slv_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(udc->usb_slv_clk)) अणु
		dev_err(udc->dev, "failed to acquire USB device clock\n");
		वापस PTR_ERR(udc->usb_slv_clk);
	पूर्ण

	/* Enable USB device घड़ी */
	retval = clk_prepare_enable(udc->usb_slv_clk);
	अगर (retval < 0) अणु
		dev_err(udc->dev, "failed to start USB device clock\n");
		वापस retval;
	पूर्ण

	/* Setup deferred workqueue data */
	udc->घातeron = udc->pullup = 0;
	INIT_WORK(&udc->pullup_job, pullup_work);
#अगर_घोषित CONFIG_PM
	INIT_WORK(&udc->घातer_job, घातer_work);
#पूर्ण_अगर

	/* All घड़ीs are now on */
	udc->घड़ीed = 1;

	isp1301_udc_configure(udc);
	/* Allocate memory क्रम the UDCA */
	udc->udca_v_base = dma_alloc_coherent(&pdev->dev, UDCA_BUFF_SIZE,
					      &dma_handle,
					      (GFP_KERNEL | GFP_DMA));
	अगर (!udc->udca_v_base) अणु
		dev_err(udc->dev, "error getting UDCA region\n");
		retval = -ENOMEM;
		जाओ i2c_fail;
	पूर्ण
	udc->udca_p_base = dma_handle;
	dev_dbg(udc->dev, "DMA buffer(0x%x bytes), P:0x%08x, V:0x%p\n",
		UDCA_BUFF_SIZE, udc->udca_p_base, udc->udca_v_base);

	/* Setup the DD DMA memory pool */
	udc->dd_cache = dma_pool_create("udc_dd", udc->dev,
					माप(काष्ठा lpc32xx_usbd_dd_gad),
					माप(u32), 0);
	अगर (!udc->dd_cache) अणु
		dev_err(udc->dev, "error getting DD DMA region\n");
		retval = -ENOMEM;
		जाओ dma_alloc_fail;
	पूर्ण

	/* Clear USB peripheral and initialize gadget endpoपूर्णांकs */
	udc_disable(udc);
	udc_reinit(udc);

	/* Request IRQs - low and high priority USB device IRQs are routed to
	 * the same handler, जबतक the DMA पूर्णांकerrupt is routed अन्यथाwhere */
	retval = devm_request_irq(dev, udc->udp_irq[IRQ_USB_LP],
				  lpc32xx_usb_lp_irq, 0, "udc_lp", udc);
	अगर (retval < 0) अणु
		dev_err(udc->dev, "LP request irq %d failed\n",
			udc->udp_irq[IRQ_USB_LP]);
		जाओ irq_req_fail;
	पूर्ण
	retval = devm_request_irq(dev, udc->udp_irq[IRQ_USB_HP],
				  lpc32xx_usb_hp_irq, 0, "udc_hp", udc);
	अगर (retval < 0) अणु
		dev_err(udc->dev, "HP request irq %d failed\n",
			udc->udp_irq[IRQ_USB_HP]);
		जाओ irq_req_fail;
	पूर्ण

	retval = devm_request_irq(dev, udc->udp_irq[IRQ_USB_DEVDMA],
				  lpc32xx_usb_devdma_irq, 0, "udc_dma", udc);
	अगर (retval < 0) अणु
		dev_err(udc->dev, "DEV request irq %d failed\n",
			udc->udp_irq[IRQ_USB_DEVDMA]);
		जाओ irq_req_fail;
	पूर्ण

	/* The transceiver पूर्णांकerrupt is used क्रम VBUS detection and will
	   kick off the VBUS handler function */
	retval = devm_request_thपढ़ोed_irq(dev, udc->udp_irq[IRQ_USB_ATX], शून्य,
					   lpc32xx_usb_vbus_irq, IRQF_ONESHOT,
					   "udc_otg", udc);
	अगर (retval < 0) अणु
		dev_err(udc->dev, "VBUS request irq %d failed\n",
			udc->udp_irq[IRQ_USB_ATX]);
		जाओ irq_req_fail;
	पूर्ण

	/* Initialize रुको queue */
	init_रुकोqueue_head(&udc->ep_disable_रुको_queue);
	atomic_set(&udc->enabled_ep_cnt, 0);

	retval = usb_add_gadget_udc(dev, &udc->gadget);
	अगर (retval < 0)
		जाओ add_gadget_fail;

	dev_set_drvdata(dev, udc);
	device_init_wakeup(dev, 1);
	create_debug_file(udc);

	/* Disable घड़ीs क्रम now */
	udc_clk_set(udc, 0);

	dev_info(udc->dev, "%s version %s\n", driver_name, DRIVER_VERSION);
	वापस 0;

add_gadget_fail:
irq_req_fail:
	dma_pool_destroy(udc->dd_cache);
dma_alloc_fail:
	dma_मुक्त_coherent(&pdev->dev, UDCA_BUFF_SIZE,
			  udc->udca_v_base, udc->udca_p_base);
i2c_fail:
	clk_disable_unprepare(udc->usb_slv_clk);
	dev_err(udc->dev, "%s probe failed, %d\n", driver_name, retval);

	वापस retval;
पूर्ण

अटल पूर्णांक lpc32xx_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_udc *udc = platक्रमm_get_drvdata(pdev);

	usb_del_gadget_udc(&udc->gadget);
	अगर (udc->driver)
		वापस -EBUSY;

	udc_clk_set(udc, 1);
	udc_disable(udc);
	pullup(udc, 0);

	device_init_wakeup(&pdev->dev, 0);
	हटाओ_debug_file(udc);

	dma_pool_destroy(udc->dd_cache);
	dma_मुक्त_coherent(&pdev->dev, UDCA_BUFF_SIZE,
			  udc->udca_v_base, udc->udca_p_base);

	clk_disable_unprepare(udc->usb_slv_clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक lpc32xx_udc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t mesg)
अणु
	काष्ठा lpc32xx_udc *udc = platक्रमm_get_drvdata(pdev);

	अगर (udc->घड़ीed) अणु
		/* Power करोwn ISP */
		udc->घातeron = 0;
		isp1301_set_घातerstate(udc, 0);

		/* Disable घड़ीing */
		udc_clk_set(udc, 0);

		/* Keep घड़ी flag on, so we know to re-enable घड़ीs
		   on resume */
		udc->घड़ीed = 1;

		/* Kill global USB घड़ी */
		clk_disable_unprepare(udc->usb_slv_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_udc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_udc *udc = platक्रमm_get_drvdata(pdev);

	अगर (udc->घड़ीed) अणु
		/* Enable global USB घड़ी */
		clk_prepare_enable(udc->usb_slv_clk);

		/* Enable घड़ीing */
		udc_clk_set(udc, 1);

		/* ISP back to normal घातer mode */
		udc->घातeron = 1;
		isp1301_set_घातerstate(udc, 1);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा	lpc32xx_udc_suspend	शून्य
#घोषणा	lpc32xx_udc_resume	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lpc32xx_udc_of_match[] = अणु
	अणु .compatible = "nxp,lpc3220-udc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc32xx_udc_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver lpc32xx_udc_driver = अणु
	.हटाओ		= lpc32xx_udc_हटाओ,
	.shutकरोwn	= lpc32xx_udc_shutकरोwn,
	.suspend	= lpc32xx_udc_suspend,
	.resume		= lpc32xx_udc_resume,
	.driver		= अणु
		.name	= driver_name,
		.of_match_table = of_match_ptr(lpc32xx_udc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(lpc32xx_udc_driver, lpc32xx_udc_probe);

MODULE_DESCRIPTION("LPC32XX udc driver");
MODULE_AUTHOR("Kevin Wells <kevin.wells@nxp.com>");
MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lpc32xx_udc");
