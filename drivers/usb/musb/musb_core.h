<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MUSB OTG driver defines
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

#अगर_अघोषित __MUSB_CORE_H__
#घोषणा __MUSB_CORE_H__

#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/musb.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/workqueue.h>

काष्ठा musb;
काष्ठा musb_hw_ep;
काष्ठा musb_ep;
काष्ठा musb_qh;

/* Helper defines क्रम काष्ठा musb->hwvers */
#घोषणा MUSB_HWVERS_MAJOR(x)	((x >> 10) & 0x1f)
#घोषणा MUSB_HWVERS_MINOR(x)	(x & 0x3ff)
#घोषणा MUSB_HWVERS_RC		0x8000
#घोषणा MUSB_HWVERS_1300	0x52C
#घोषणा MUSB_HWVERS_1400	0x590
#घोषणा MUSB_HWVERS_1800	0x720
#घोषणा MUSB_HWVERS_1900	0x784
#घोषणा MUSB_HWVERS_2000	0x800

#समावेश "musb_debug.h"
#समावेश "musb_dma.h"

#समावेश "musb_io.h"

#समावेश "musb_gadget.h"
#समावेश <linux/usb/hcd.h>
#समावेश "musb_host.h"

/* NOTE:  otg and peripheral-only state machines start at B_IDLE.
 * OTG or host-only go to A_IDLE when ID is sensed.
 */
#घोषणा is_peripheral_active(m)		(!(m)->is_host)
#घोषणा is_host_active(m)		((m)->is_host)

/****************************** CONSTANTS ********************************/

#अगर_अघोषित MUSB_C_NUM_EPS
#घोषणा MUSB_C_NUM_EPS ((u8)16)
#पूर्ण_अगर

#अगर_अघोषित MUSB_MAX_END0_PACKET
#घोषणा MUSB_MAX_END0_PACKET ((u16)MUSB_EP0_FIFOSIZE)
#पूर्ण_अगर

/* host side ep0 states */
क्रमागत musb_h_ep0_state अणु
	MUSB_EP0_IDLE,
	MUSB_EP0_START,			/* expect ack of setup */
	MUSB_EP0_IN,			/* expect IN DATA */
	MUSB_EP0_OUT,			/* expect ack of OUT DATA */
	MUSB_EP0_STATUS,		/* expect ack of STATUS */
पूर्ण __attribute__ ((packed));

/* peripheral side ep0 states */
क्रमागत musb_g_ep0_state अणु
	MUSB_EP0_STAGE_IDLE,		/* idle, रुकोing क्रम SETUP */
	MUSB_EP0_STAGE_SETUP,		/* received SETUP */
	MUSB_EP0_STAGE_TX,		/* IN data */
	MUSB_EP0_STAGE_RX,		/* OUT data */
	MUSB_EP0_STAGE_STATUSIN,	/* (after OUT data) */
	MUSB_EP0_STAGE_STATUSOUT,	/* (after IN data) */
	MUSB_EP0_STAGE_ACKWAIT,		/* after zlp, beक्रमe statusin */
पूर्ण __attribute__ ((packed));

/*
 * OTG protocol स्थिरants.  See USB OTG 1.3 spec,
 * sections 5.5 "Device Timings" and 6.6.5 "Timers".
 */
#घोषणा OTG_TIME_A_WAIT_VRISE	100		/* msec (max) */
#घोषणा OTG_TIME_A_WAIT_BCON	1100		/* min 1 second */
#घोषणा OTG_TIME_A_AIDL_BDIS	200		/* min 200 msec */
#घोषणा OTG_TIME_B_ASE0_BRST	100		/* min 3.125 ms */

/****************************** FUNCTIONS ********************************/

#घोषणा MUSB_HST_MODE(_musb)\
	अणु (_musb)->is_host = true; पूर्ण
#घोषणा MUSB_DEV_MODE(_musb) \
	अणु (_musb)->is_host = false; पूर्ण

#घोषणा test_devctl_hst_mode(_x) \
	(musb_पढ़ोb((_x)->mregs, MUSB_DEVCTL)&MUSB_DEVCTL_HM)

#घोषणा MUSB_MODE(musb) ((musb)->is_host ? "Host" : "Peripheral")

/******************************** TYPES *************************************/

काष्ठा musb_io;

/**
 * काष्ठा musb_platक्रमm_ops - Operations passed to musb_core by HW glue layer
 * @quirks:	flags क्रम platक्रमm specअगरic quirks
 * @enable:	enable device
 * @disable:	disable device
 * @ep_offset:	वापसs the end poपूर्णांक offset
 * @ep_select:	selects the specअगरied end poपूर्णांक
 * @fअगरo_mode:	sets the fअगरo mode
 * @fअगरo_offset: वापसs the fअगरo offset
 * @पढ़ोb:	पढ़ो 8 bits
 * @ग_लिखोb:	ग_लिखो 8 bits
 * @clearb:	could be clear-on-पढ़ोb or W1C
 * @पढ़ोw:	पढ़ो 16 bits
 * @ग_लिखोw:	ग_लिखो 16 bits
 * @clearw:	could be clear-on-पढ़ोw or W1C
 * @पढ़ो_fअगरo:	पढ़ोs the fअगरo
 * @ग_लिखो_fअगरo:	ग_लिखोs to fअगरo
 * @get_toggle:	platक्रमm specअगरic get toggle function
 * @set_toggle:	platक्रमm specअगरic set toggle function
 * @dma_init:	platक्रमm specअगरic dma init function
 * @dma_निकास:	platक्रमm specअगरic dma निकास function
 * @init:	turns on घड़ीs, sets up platक्रमm-specअगरic रेजिस्टरs, etc
 * @निकास:	unकरोes @init
 * @set_mode:	क्रमcefully changes operating mode
 * @try_idle:	tries to idle the IP
 * @recover:	platक्रमm-specअगरic babble recovery
 * @vbus_status: वापसs vbus status अगर possible
 * @set_vbus:	क्रमces vbus status
 * @pre_root_reset_end: called beक्रमe the root usb port reset flag माला_लो cleared
 * @post_root_reset_end: called after the root usb port reset flag माला_लो cleared
 * @phy_callback: optional callback function क्रम the phy to call
 */
काष्ठा musb_platक्रमm_ops अणु

#घोषणा MUSB_G_NO_SKB_RESERVE	BIT(9)
#घोषणा MUSB_DA8XX		BIT(8)
#घोषणा MUSB_PRESERVE_SESSION	BIT(7)
#घोषणा MUSB_DMA_UX500		BIT(6)
#घोषणा MUSB_DMA_CPPI41		BIT(5)
#घोषणा MUSB_DMA_CPPI		BIT(4)
#घोषणा MUSB_DMA_TUSB_OMAP	BIT(3)
#घोषणा MUSB_DMA_INVENTRA	BIT(2)
#घोषणा MUSB_IN_TUSB		BIT(1)
#घोषणा MUSB_INDEXED_EP		BIT(0)
	u32	quirks;

	पूर्णांक	(*init)(काष्ठा musb *musb);
	पूर्णांक	(*निकास)(काष्ठा musb *musb);

	व्योम	(*enable)(काष्ठा musb *musb);
	व्योम	(*disable)(काष्ठा musb *musb);

	u32	(*ep_offset)(u8 epnum, u16 offset);
	व्योम	(*ep_select)(व्योम __iomem *mbase, u8 epnum);
	u16	fअगरo_mode;
	u32	(*fअगरo_offset)(u8 epnum);
	u32	(*busctl_offset)(u8 epnum, u16 offset);
	u8	(*पढ़ोb)(व्योम __iomem *addr, u32 offset);
	व्योम	(*ग_लिखोb)(व्योम __iomem *addr, u32 offset, u8 data);
	u8	(*clearb)(व्योम __iomem *addr, u32 offset);
	u16	(*पढ़ोw)(व्योम __iomem *addr, u32 offset);
	व्योम	(*ग_लिखोw)(व्योम __iomem *addr, u32 offset, u16 data);
	u16	(*clearw)(व्योम __iomem *addr, u32 offset);
	व्योम	(*पढ़ो_fअगरo)(काष्ठा musb_hw_ep *hw_ep, u16 len, u8 *buf);
	व्योम	(*ग_लिखो_fअगरo)(काष्ठा musb_hw_ep *hw_ep, u16 len, स्थिर u8 *buf);
	u16	(*get_toggle)(काष्ठा musb_qh *qh, पूर्णांक is_out);
	u16	(*set_toggle)(काष्ठा musb_qh *qh, पूर्णांक is_out, काष्ठा urb *urb);
	काष्ठा dma_controller *
		(*dma_init) (काष्ठा musb *musb, व्योम __iomem *base);
	व्योम	(*dma_निकास)(काष्ठा dma_controller *c);
	पूर्णांक	(*set_mode)(काष्ठा musb *musb, u8 mode);
	व्योम	(*try_idle)(काष्ठा musb *musb, अचिन्हित दीर्घ समयout);
	पूर्णांक	(*recover)(काष्ठा musb *musb);

	पूर्णांक	(*vbus_status)(काष्ठा musb *musb);
	व्योम	(*set_vbus)(काष्ठा musb *musb, पूर्णांक on);

	व्योम	(*pre_root_reset_end)(काष्ठा musb *musb);
	व्योम	(*post_root_reset_end)(काष्ठा musb *musb);
	पूर्णांक	(*phy_callback)(क्रमागत musb_vbus_id_status status);
	व्योम	(*clear_ep_rxपूर्णांकr)(काष्ठा musb *musb, पूर्णांक epnum);
पूर्ण;

/*
 * काष्ठा musb_hw_ep - endpoपूर्णांक hardware (bidirectional)
 *
 * Ordered slightly क्रम better cacheline locality.
 */
काष्ठा musb_hw_ep अणु
	काष्ठा musb		*musb;
	व्योम __iomem		*fअगरo;
	व्योम __iomem		*regs;

#अगर IS_ENABLED(CONFIG_USB_MUSB_TUSB6010)
	व्योम __iomem		*conf;
#पूर्ण_अगर

	/* index in musb->endpoपूर्णांकs[]  */
	u8			epnum;

	/* hardware configuration, possibly dynamic */
	bool			is_shared_fअगरo;
	bool			tx_द्विगुन_buffered;
	bool			rx_द्विगुन_buffered;
	u16			max_packet_sz_tx;
	u16			max_packet_sz_rx;

	काष्ठा dma_channel	*tx_channel;
	काष्ठा dma_channel	*rx_channel;

#अगर IS_ENABLED(CONFIG_USB_MUSB_TUSB6010)
	/* TUSB has "asynchronous" and "synchronous" dma modes */
	dma_addr_t		fअगरo_async;
	dma_addr_t		fअगरo_sync;
	व्योम __iomem		*fअगरo_sync_va;
#पूर्ण_अगर

	/* currently scheduled peripheral endpoपूर्णांक */
	काष्ठा musb_qh		*in_qh;
	काष्ठा musb_qh		*out_qh;

	u8			rx_reinit;
	u8			tx_reinit;

	/* peripheral side */
	काष्ठा musb_ep		ep_in;			/* TX */
	काष्ठा musb_ep		ep_out;			/* RX */
पूर्ण;

अटल अंतरभूत काष्ठा musb_request *next_in_request(काष्ठा musb_hw_ep *hw_ep)
अणु
	वापस next_request(&hw_ep->ep_in);
पूर्ण

अटल अंतरभूत काष्ठा musb_request *next_out_request(काष्ठा musb_hw_ep *hw_ep)
अणु
	वापस next_request(&hw_ep->ep_out);
पूर्ण

काष्ठा musb_csr_regs अणु
	/* FIFO रेजिस्टरs */
	u16 txmaxp, txcsr, rxmaxp, rxcsr;
	u16 rxfअगरoadd, txfअगरoadd;
	u8 txtype, txपूर्णांकerval, rxtype, rxपूर्णांकerval;
	u8 rxfअगरosz, txfअगरosz;
	u8 txfunaddr, txhubaddr, txhubport;
	u8 rxfunaddr, rxhubaddr, rxhubport;
पूर्ण;

काष्ठा musb_context_रेजिस्टरs अणु

	u8 घातer;
	u8 पूर्णांकrusbe;
	u16 frame;
	u8 index, tesपंचांगode;

	u8 devctl, busctl, misc;
	u32 otg_पूर्णांकerfsel;

	काष्ठा musb_csr_regs index_regs[MUSB_C_NUM_EPS];
पूर्ण;

/*
 * काष्ठा musb - Driver instance data.
 */
काष्ठा musb अणु
	/* device lock */
	spinlock_t		lock;
	spinlock_t		list_lock;	/* resume work list lock */

	काष्ठा musb_io		io;
	स्थिर काष्ठा musb_platक्रमm_ops *ops;
	काष्ठा musb_context_रेजिस्टरs context;

	irqवापस_t		(*isr)(पूर्णांक, व्योम *);
	काष्ठा delayed_work	irq_work;
	काष्ठा delayed_work	deनिश्चित_reset_work;
	काष्ठा delayed_work	finish_resume_work;
	काष्ठा delayed_work	gadget_work;
	u16			hwvers;

	u16			पूर्णांकrrxe;
	u16			पूर्णांकrtxe;
/* this hub status bit is reserved by USB 2.0 and not seen by usbcore */
#घोषणा MUSB_PORT_STAT_RESUME	(1 << 31)

	u32			port1_status;

	अचिन्हित दीर्घ		rh_समयr;

	क्रमागत musb_h_ep0_state	ep0_stage;

	/* bulk traffic normally dedicates endpoपूर्णांक hardware, and each
	 * direction has its own ring of host side endpoपूर्णांकs.
	 * we try to progress the transfer at the head of each endpoपूर्णांक's
	 * queue until it completes or NAKs too much; then we try the next
	 * endpoपूर्णांक.
	 */
	काष्ठा musb_hw_ep	*bulk_ep;

	काष्ठा list_head	control;	/* of musb_qh */
	काष्ठा list_head	in_bulk;	/* of musb_qh */
	काष्ठा list_head	out_bulk;	/* of musb_qh */
	काष्ठा list_head	pending_list;	/* pending work list */

	काष्ठा समयr_list	otg_समयr;
	काष्ठा समयr_list	dev_समयr;
	काष्ठा notअगरier_block	nb;

	काष्ठा dma_controller	*dma_controller;

	काष्ठा device		*controller;
	व्योम __iomem		*ctrl_base;
	व्योम __iomem		*mregs;

#अगर IS_ENABLED(CONFIG_USB_MUSB_TUSB6010)
	dma_addr_t		async;
	dma_addr_t		sync;
	व्योम __iomem		*sync_va;
	u8			tusb_revision;
#पूर्ण_अगर

	/* passed करोwn from chip/board specअगरic irq handlers */
	u8			पूर्णांक_usb;
	u16			पूर्णांक_rx;
	u16			पूर्णांक_tx;

	काष्ठा usb_phy		*xceiv;
	काष्ठा phy		*phy;

	पूर्णांक nIrq;
	अचिन्हित		irq_wake:1;

	काष्ठा musb_hw_ep	 endpoपूर्णांकs[MUSB_C_NUM_EPS];
#घोषणा control_ep		endpoपूर्णांकs

#घोषणा VBUSERR_RETRY_COUNT	3
	u16			vbuserr_retry;
	u16 epmask;
	u8 nr_endpoपूर्णांकs;

	पूर्णांक			(*board_set_घातer)(पूर्णांक state);

	u8			min_घातer;	/* vbus क्रम periph, in mA/2 */

	क्रमागत musb_mode		port_mode;
	bool			session;
	अचिन्हित दीर्घ		quirk_retries;
	bool			is_host;

	पूर्णांक			a_रुको_bcon;	/* VBUS समयout in msecs */
	अचिन्हित दीर्घ		idle_समयout;	/* Next समयout in jअगरfies */

	अचिन्हित		is_initialized:1;
	अचिन्हित		is_runसमय_suspended:1;

	/* active means connected and not suspended */
	अचिन्हित		is_active:1;

	अचिन्हित is_multipoपूर्णांक:1;

	अचिन्हित		hb_iso_rx:1;	/* high bandwidth iso rx? */
	अचिन्हित		hb_iso_tx:1;	/* high bandwidth iso tx? */
	अचिन्हित		dyn_fअगरo:1;	/* dynamic FIFO supported? */

	अचिन्हित		bulk_split:1;
#घोषणा	can_bulk_split(musb, type) \
	(((type) == USB_ENDPOINT_XFER_BULK) && (musb)->bulk_split)

	अचिन्हित		bulk_combine:1;
#घोषणा	can_bulk_combine(musb, type) \
	(((type) == USB_ENDPOINT_XFER_BULK) && (musb)->bulk_combine)

	/* is_suspended means USB B_PERIPHERAL suspend */
	अचिन्हित		is_suspended:1;

	/* may_wakeup means remote wakeup is enabled */
	अचिन्हित		may_wakeup:1;

	/* is_self_घातered is reported in device status and the
	 * config descriptor.  is_bus_घातered means B_PERIPHERAL
	 * draws some VBUS current; both can be true.
	 */
	अचिन्हित		is_self_घातered:1;
	अचिन्हित		is_bus_घातered:1;

	अचिन्हित		set_address:1;
	अचिन्हित		test_mode:1;
	अचिन्हित		softconnect:1;

	अचिन्हित		flush_irq_work:1;

	u8			address;
	u8			test_mode_nr;
	u16			ackpend;		/* ep0 */
	क्रमागत musb_g_ep0_state	ep0_state;
	काष्ठा usb_gadget	g;			/* the gadget */
	काष्ठा usb_gadget_driver *gadget_driver;	/* its driver */
	काष्ठा usb_hcd		*hcd;			/* the usb hcd */

	स्थिर काष्ठा musb_hdrc_config *config;

	पूर्णांक			xceiv_old_state;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry		*debugfs_root;
#पूर्ण_अगर
पूर्ण;

/* This must be included after काष्ठा musb is defined */
#समावेश "musb_regs.h"

अटल अंतरभूत काष्ठा musb *gadget_to_musb(काष्ठा usb_gadget *g)
अणु
	वापस container_of(g, काष्ठा musb, g);
पूर्ण

अटल अंतरभूत अक्षर *musb_ep_xfertype_string(u8 type)
अणु
	अक्षर *s;

	चयन (type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		s = "ctrl";
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		s = "iso";
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		s = "bulk";
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		s = "int";
		अवरोध;
	शेष:
		s = "";
		अवरोध;
	पूर्ण
	वापस s;
पूर्ण

अटल अंतरभूत पूर्णांक musb_पढ़ो_fअगरosize(काष्ठा musb *musb,
		काष्ठा musb_hw_ep *hw_ep, u8 epnum)
अणु
	व्योम __iomem *mbase = musb->mregs;
	u8 reg = 0;

	/* पढ़ो from core using indexed model */
	reg = musb_पढ़ोb(mbase, musb->io.ep_offset(epnum, MUSB_FIFOSIZE));
	/* 0's वापसed when no more endpoपूर्णांकs */
	अगर (!reg)
		वापस -ENODEV;

	musb->nr_endpoपूर्णांकs++;
	musb->epmask |= (1 << epnum);

	hw_ep->max_packet_sz_tx = 1 << (reg & 0x0f);

	/* shared TX/RX FIFO? */
	अगर ((reg & 0xf0) == 0xf0) अणु
		hw_ep->max_packet_sz_rx = hw_ep->max_packet_sz_tx;
		hw_ep->is_shared_fअगरo = true;
		वापस 0;
	पूर्ण अन्यथा अणु
		hw_ep->max_packet_sz_rx = 1 << ((reg & 0xf0) >> 4);
		hw_ep->is_shared_fअगरo = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम musb_configure_ep0(काष्ठा musb *musb)
अणु
	musb->endpoपूर्णांकs[0].max_packet_sz_tx = MUSB_EP0_FIFOSIZE;
	musb->endpoपूर्णांकs[0].max_packet_sz_rx = MUSB_EP0_FIFOSIZE;
	musb->endpoपूर्णांकs[0].is_shared_fअगरo = true;
पूर्ण

/***************************** Glue it together *****************************/

बाह्य स्थिर अक्षर musb_driver_name[];

बाह्य व्योम musb_stop(काष्ठा musb *musb);
बाह्य व्योम musb_start(काष्ठा musb *musb);

बाह्य व्योम musb_ग_लिखो_fअगरo(काष्ठा musb_hw_ep *ep, u16 len, स्थिर u8 *src);
बाह्य व्योम musb_पढ़ो_fअगरo(काष्ठा musb_hw_ep *ep, u16 len, u8 *dst);

बाह्य पूर्णांक musb_set_host(काष्ठा musb *musb);
बाह्य पूर्णांक musb_set_peripheral(काष्ठा musb *musb);

बाह्य व्योम musb_load_testpacket(काष्ठा musb *);

बाह्य irqवापस_t musb_पूर्णांकerrupt(काष्ठा musb *);

बाह्य व्योम musb_hnp_stop(काष्ठा musb *musb);

पूर्णांक musb_queue_resume_work(काष्ठा musb *musb,
			   पूर्णांक (*callback)(काष्ठा musb *musb, व्योम *data),
			   व्योम *data);

अटल अंतरभूत व्योम musb_platक्रमm_set_vbus(काष्ठा musb *musb, पूर्णांक is_on)
अणु
	अगर (musb->ops->set_vbus)
		musb->ops->set_vbus(musb, is_on);
पूर्ण

अटल अंतरभूत व्योम musb_platक्रमm_enable(काष्ठा musb *musb)
अणु
	अगर (musb->ops->enable)
		musb->ops->enable(musb);
पूर्ण

अटल अंतरभूत व्योम musb_platक्रमm_disable(काष्ठा musb *musb)
अणु
	अगर (musb->ops->disable)
		musb->ops->disable(musb);
पूर्ण

अटल अंतरभूत पूर्णांक musb_platक्रमm_set_mode(काष्ठा musb *musb, u8 mode)
अणु
	अगर (!musb->ops->set_mode)
		वापस 0;

	वापस musb->ops->set_mode(musb, mode);
पूर्ण

अटल अंतरभूत व्योम musb_platक्रमm_try_idle(काष्ठा musb *musb,
		अचिन्हित दीर्घ समयout)
अणु
	अगर (musb->ops->try_idle)
		musb->ops->try_idle(musb, समयout);
पूर्ण

अटल अंतरभूत पूर्णांक  musb_platक्रमm_recover(काष्ठा musb *musb)
अणु
	अगर (!musb->ops->recover)
		वापस 0;

	वापस musb->ops->recover(musb);
पूर्ण

अटल अंतरभूत पूर्णांक musb_platक्रमm_get_vbus_status(काष्ठा musb *musb)
अणु
	अगर (!musb->ops->vbus_status)
		वापस -EINVAL;

	वापस musb->ops->vbus_status(musb);
पूर्ण

अटल अंतरभूत पूर्णांक musb_platक्रमm_init(काष्ठा musb *musb)
अणु
	अगर (!musb->ops->init)
		वापस -EINVAL;

	वापस musb->ops->init(musb);
पूर्ण

अटल अंतरभूत पूर्णांक musb_platक्रमm_निकास(काष्ठा musb *musb)
अणु
	अगर (!musb->ops->निकास)
		वापस -EINVAL;

	वापस musb->ops->निकास(musb);
पूर्ण

अटल अंतरभूत व्योम musb_platक्रमm_pre_root_reset_end(काष्ठा musb *musb)
अणु
	अगर (musb->ops->pre_root_reset_end)
		musb->ops->pre_root_reset_end(musb);
पूर्ण

अटल अंतरभूत व्योम musb_platक्रमm_post_root_reset_end(काष्ठा musb *musb)
अणु
	अगर (musb->ops->post_root_reset_end)
		musb->ops->post_root_reset_end(musb);
पूर्ण

अटल अंतरभूत व्योम musb_platक्रमm_clear_ep_rxपूर्णांकr(काष्ठा musb *musb, पूर्णांक epnum)
अणु
	अगर (musb->ops->clear_ep_rxपूर्णांकr)
		musb->ops->clear_ep_rxपूर्णांकr(musb, epnum);
पूर्ण

/*
 * माला_लो the "dr_mode" property from DT and converts it पूर्णांकo musb_mode
 * अगर the property is not found or not recognized वापसs MUSB_OTG
 */
बाह्य क्रमागत musb_mode musb_get_mode(काष्ठा device *dev);

#पूर्ण_अगर	/* __MUSB_CORE_H__ */
