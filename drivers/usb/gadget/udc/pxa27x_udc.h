<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/drivers/usb/gadget/pxa27x_udc.h
 * Intel PXA27x on-chip full speed USB device controller
 *
 * Inspired by original driver by Frank Becker, David Brownell, and others.
 * Copyright (C) 2008 Robert Jarzmik
 */

#अगर_अघोषित __LINUX_USB_GADGET_PXA27X_H
#घोषणा __LINUX_USB_GADGET_PXA27X_H

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/usb/otg.h>

/*
 * Register definitions
 */
/* Offsets */
#घोषणा UDCCR		0x0000		/* UDC Control Register */
#घोषणा UDCICR0		0x0004		/* UDC Interrupt Control Register0 */
#घोषणा UDCICR1		0x0008		/* UDC Interrupt Control Register1 */
#घोषणा UDCISR0		0x000C		/* UDC Interrupt Status Register 0 */
#घोषणा UDCISR1		0x0010		/* UDC Interrupt Status Register 1 */
#घोषणा UDCFNR		0x0014		/* UDC Frame Number Register */
#घोषणा UDCOTGICR	0x0018		/* UDC On-The-Go पूर्णांकerrupt control */
#घोषणा UP2OCR		0x0020		/* USB Port 2 Output Control रेजिस्टर */
#घोषणा UP3OCR		0x0024		/* USB Port 3 Output Control रेजिस्टर */
#घोषणा UDCCSRn(x)	(0x0100 + ((x)<<2)) /* UDC Control/Status रेजिस्टर */
#घोषणा UDCBCRn(x)	(0x0200 + ((x)<<2)) /* UDC Byte Count Register */
#घोषणा UDCDRn(x)	(0x0300 + ((x)<<2)) /* UDC Data Register  */
#घोषणा UDCCRn(x)	(0x0400 + ((x)<<2)) /* UDC Control Register */

#घोषणा UDCCR_OEN	(1 << 31)	/* On-the-Go Enable */
#घोषणा UDCCR_AALTHNP	(1 << 30)	/* A-device Alternate Host Negotiation
					   Protocol Port Support */
#घोषणा UDCCR_AHNP	(1 << 29)	/* A-device Host Negotiation Protocol
					   Support */
#घोषणा UDCCR_BHNP	(1 << 28)	/* B-device Host Negotiation Protocol
					   Enable */
#घोषणा UDCCR_DWRE	(1 << 16)	/* Device Remote Wake-up Enable */
#घोषणा UDCCR_ACN	(0x03 << 11)	/* Active UDC configuration Number */
#घोषणा UDCCR_ACN_S	11
#घोषणा UDCCR_AIN	(0x07 << 8)	/* Active UDC पूर्णांकerface Number */
#घोषणा UDCCR_AIN_S	8
#घोषणा UDCCR_AAISN	(0x07 << 5)	/* Active UDC Alternate Interface
					   Setting Number */
#घोषणा UDCCR_AAISN_S	5
#घोषणा UDCCR_SMAC	(1 << 4)	/* Switch Endpoपूर्णांक Memory to Active
					   Configuration */
#घोषणा UDCCR_EMCE	(1 << 3)	/* Endpoपूर्णांक Memory Configuration
					   Error */
#घोषणा UDCCR_UDR	(1 << 2)	/* UDC Resume */
#घोषणा UDCCR_UDA	(1 << 1)	/* UDC Active */
#घोषणा UDCCR_UDE	(1 << 0)	/* UDC Enable */

#घोषणा UDCICR_INT(n, पूर्णांकr) (((पूर्णांकr) & 0x03) << (((n) & 0x0F) * 2))
#घोषणा UDCICR1_IECC	(1 << 31)	/* IntEn - Configuration Change */
#घोषणा UDCICR1_IESOF	(1 << 30)	/* IntEn - Start of Frame */
#घोषणा UDCICR1_IERU	(1 << 29)	/* IntEn - Resume */
#घोषणा UDCICR1_IESU	(1 << 28)	/* IntEn - Suspend */
#घोषणा UDCICR1_IERS	(1 << 27)	/* IntEn - Reset */
#घोषणा UDCICR_FIFOERR	(1 << 1)	/* FIFO Error पूर्णांकerrupt क्रम EP */
#घोषणा UDCICR_PKTCOMPL	(1 << 0)	/* Packet Complete पूर्णांकerrupt क्रम EP */
#घोषणा UDCICR_INT_MASK	(UDCICR_FIFOERR | UDCICR_PKTCOMPL)

#घोषणा UDCISR_INT(n, पूर्णांकr) (((पूर्णांकr) & 0x03) << (((n) & 0x0F) * 2))
#घोषणा UDCISR1_IRCC	(1 << 31)	/* IntReq - Configuration Change */
#घोषणा UDCISR1_IRSOF	(1 << 30)	/* IntReq - Start of Frame */
#घोषणा UDCISR1_IRRU	(1 << 29)	/* IntReq - Resume */
#घोषणा UDCISR1_IRSU	(1 << 28)	/* IntReq - Suspend */
#घोषणा UDCISR1_IRRS	(1 << 27)	/* IntReq - Reset */
#घोषणा UDCISR_INT_MASK	(UDCICR_FIFOERR | UDCICR_PKTCOMPL)

#घोषणा UDCOTGICR_IESF	(1 << 24)	/* OTG SET_FEATURE command recvd */
#घोषणा UDCOTGICR_IEXR	(1 << 17)	/* Extra Transceiver Interrupt
					   Rising Edge Interrupt Enable */
#घोषणा UDCOTGICR_IEXF	(1 << 16)	/* Extra Transceiver Interrupt
					   Falling Edge Interrupt Enable */
#घोषणा UDCOTGICR_IEVV40R (1 << 9)	/* OTG Vbus Valid 4.0V Rising Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IEVV40F (1 << 8)	/* OTG Vbus Valid 4.0V Falling Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IEVV44R (1 << 7)	/* OTG Vbus Valid 4.4V Rising Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IEVV44F (1 << 6)	/* OTG Vbus Valid 4.4V Falling Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IESVR	(1 << 5)	/* OTG Session Valid Rising Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IESVF	(1 << 4)	/* OTG Session Valid Falling Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IESDR	(1 << 3)	/* OTG A-Device SRP Detect Rising
					   Edge Interrupt Enable */
#घोषणा UDCOTGICR_IESDF	(1 << 2)	/* OTG A-Device SRP Detect Falling
					   Edge Interrupt Enable */
#घोषणा UDCOTGICR_IEIDR	(1 << 1)	/* OTG ID Change Rising Edge
					   Interrupt Enable */
#घोषणा UDCOTGICR_IEIDF	(1 << 0)	/* OTG ID Change Falling Edge
					   Interrupt Enable */

/* Host Port 2 field bits */
#घोषणा UP2OCR_CPVEN	(1 << 0)	/* Charge Pump Vbus Enable */
#घोषणा UP2OCR_CPVPE	(1 << 1)	/* Charge Pump Vbus Pulse Enable */
					/* Transceiver enablers */
#घोषणा UP2OCR_DPPDE	(1 << 2)	/*   D+ Pull Down Enable */
#घोषणा UP2OCR_DMPDE	(1 << 3)	/*   D- Pull Down Enable */
#घोषणा UP2OCR_DPPUE	(1 << 4)	/*   D+ Pull Up Enable */
#घोषणा UP2OCR_DMPUE	(1 << 5)	/*   D- Pull Up Enable */
#घोषणा UP2OCR_DPPUBE	(1 << 6)	/*   D+ Pull Up Bypass Enable */
#घोषणा UP2OCR_DMPUBE	(1 << 7)	/*   D- Pull Up Bypass Enable */
#घोषणा UP2OCR_EXSP	(1 << 8)	/* External Transceiver Speed Control */
#घोषणा UP2OCR_EXSUS	(1 << 9)	/* External Transceiver Speed Enable */
#घोषणा UP2OCR_IDON	(1 << 10)	/* OTG ID Read Enable */
#घोषणा UP2OCR_HXS	(1 << 16)	/* Transceiver Output Select */
#घोषणा UP2OCR_HXOE	(1 << 17)	/* Transceiver Output Enable */
#घोषणा UP2OCR_SEOS	(1 << 24)	/* Single-Ended Output Select */

#घोषणा UDCCSR0_ACM	(1 << 9)	/* Ack Control Mode */
#घोषणा UDCCSR0_AREN	(1 << 8)	/* Ack Response Enable */
#घोषणा UDCCSR0_SA	(1 << 7)	/* Setup Active */
#घोषणा UDCCSR0_RNE	(1 << 6)	/* Receive FIFO Not Empty */
#घोषणा UDCCSR0_FST	(1 << 5)	/* Force Stall */
#घोषणा UDCCSR0_SST	(1 << 4)	/* Sent Stall */
#घोषणा UDCCSR0_DME	(1 << 3)	/* DMA Enable */
#घोषणा UDCCSR0_FTF	(1 << 2)	/* Flush Transmit FIFO */
#घोषणा UDCCSR0_IPR	(1 << 1)	/* IN Packet Ready */
#घोषणा UDCCSR0_OPC	(1 << 0)	/* OUT Packet Complete */

#घोषणा UDCCSR_DPE	(1 << 9)	/* Data Packet Error */
#घोषणा UDCCSR_FEF	(1 << 8)	/* Flush Endpoपूर्णांक FIFO */
#घोषणा UDCCSR_SP	(1 << 7)	/* Short Packet Control/Status */
#घोषणा UDCCSR_BNE	(1 << 6)	/* Buffer Not Empty (IN endpoपूर्णांकs) */
#घोषणा UDCCSR_BNF	(1 << 6)	/* Buffer Not Full (OUT endpoपूर्णांकs) */
#घोषणा UDCCSR_FST	(1 << 5)	/* Force STALL */
#घोषणा UDCCSR_SST	(1 << 4)	/* Sent STALL */
#घोषणा UDCCSR_DME	(1 << 3)	/* DMA Enable */
#घोषणा UDCCSR_TRN	(1 << 2)	/* Tx/Rx NAK */
#घोषणा UDCCSR_PC	(1 << 1)	/* Packet Complete */
#घोषणा UDCCSR_FS	(1 << 0)	/* FIFO needs service */

#घोषणा UDCCONR_CN	(0x03 << 25)	/* Configuration Number */
#घोषणा UDCCONR_CN_S	25
#घोषणा UDCCONR_IN	(0x07 << 22)	/* Interface Number */
#घोषणा UDCCONR_IN_S	22
#घोषणा UDCCONR_AISN	(0x07 << 19)	/* Alternate Interface Number */
#घोषणा UDCCONR_AISN_S	19
#घोषणा UDCCONR_EN	(0x0f << 15)	/* Endpoपूर्णांक Number */
#घोषणा UDCCONR_EN_S	15
#घोषणा UDCCONR_ET	(0x03 << 13)	/* Endpoपूर्णांक Type: */
#घोषणा UDCCONR_ET_S	13
#घोषणा UDCCONR_ET_INT	(0x03 << 13)	/*   Interrupt */
#घोषणा UDCCONR_ET_BULK	(0x02 << 13)	/*   Bulk */
#घोषणा UDCCONR_ET_ISO	(0x01 << 13)	/*   Isochronous */
#घोषणा UDCCONR_ET_NU	(0x00 << 13)	/*   Not used */
#घोषणा UDCCONR_ED	(1 << 12)	/* Endpoपूर्णांक Direction */
#घोषणा UDCCONR_MPS	(0x3ff << 2)	/* Maximum Packet Size */
#घोषणा UDCCONR_MPS_S	2
#घोषणा UDCCONR_DE	(1 << 1)	/* Double Buffering Enable */
#घोषणा UDCCONR_EE	(1 << 0)	/* Endpoपूर्णांक Enable */

#घोषणा UDCCR_MASK_BITS (UDCCR_OEN | UDCCR_SMAC | UDCCR_UDR | UDCCR_UDE)
#घोषणा UDCCSR_WR_MASK	(UDCCSR_DME | UDCCSR_FST)
#घोषणा UDC_FNR_MASK	(0x7ff)
#घोषणा UDC_BCR_MASK	(0x3ff)

/*
 * UDCCR = UDC Endpoपूर्णांक Configuration Registers
 * UDCCSR = UDC Control/Status Register क्रम this EP
 * UDCBCR = UDC Byte Count Reमुख्यing (contents of OUT fअगरo)
 * UDCDR = UDC Endpoपूर्णांक Data Register (the fअगरo)
 */
#घोषणा ofs_UDCCR(ep)	(UDCCRn(ep->idx))
#घोषणा ofs_UDCCSR(ep)	(UDCCSRn(ep->idx))
#घोषणा ofs_UDCBCR(ep)	(UDCBCRn(ep->idx))
#घोषणा ofs_UDCDR(ep)	(UDCDRn(ep->idx))

/* Register access macros */
#घोषणा udc_ep_पढ़ोl(ep, reg)	\
	__raw_पढ़ोl((ep)->dev->regs + ofs_##reg(ep))
#घोषणा udc_ep_ग_लिखोl(ep, reg, value)	\
	__raw_ग_लिखोl((value), ep->dev->regs + ofs_##reg(ep))
#घोषणा udc_ep_पढ़ोb(ep, reg)	\
	__raw_पढ़ोb((ep)->dev->regs + ofs_##reg(ep))
#घोषणा udc_ep_ग_लिखोb(ep, reg, value)	\
	__raw_ग_लिखोb((value), ep->dev->regs + ofs_##reg(ep))
#घोषणा udc_पढ़ोl(dev, reg)	\
	__raw_पढ़ोl((dev)->regs + (reg))
#घोषणा udc_ग_लिखोl(udc, reg, value)	\
	__raw_ग_लिखोl((value), (udc)->regs + (reg))

#घोषणा UDCCSR_MASK		(UDCCSR_FST | UDCCSR_DME)
#घोषणा UDCCISR0_EP_MASK	~0
#घोषणा UDCCISR1_EP_MASK	0xffff
#घोषणा UDCCSR0_CTRL_REQ_MASK	(UDCCSR0_OPC | UDCCSR0_SA | UDCCSR0_RNE)

#घोषणा EPIDX(ep)	(ep->idx)
#घोषणा EPADDR(ep)	(ep->addr)
#घोषणा EPXFERTYPE(ep)	(ep->type)
#घोषणा EPNAME(ep)	(ep->name)
#घोषणा is_ep0(ep)	(!ep->idx)
#घोषणा EPXFERTYPE_is_ISO(ep) (EPXFERTYPE(ep) == USB_ENDPOINT_XFER_ISOC)

/*
 * Endpoपूर्णांक definitions
 *
 * Once enabled, pxa endpoपूर्णांक configuration is मुक्तzed, and cannot change
 * unless a reset happens or the udc is disabled.
 * Thereक्रमe, we must define all pxa potential endpoपूर्णांक definitions needed क्रम
 * all gadget and set them up beक्रमe the udc is enabled.
 *
 * As the architecture chosen is fully अटल, meaning the pxa endpoपूर्णांक
 * configurations are set up once and क्रम all, we must provide a way to match
 * one usb endpoपूर्णांक (usb_ep) to several pxa endpoपूर्णांकs. The reason is that gadget
 * layer स्वतःconf करोesn't choose the usb_ep endpoपूर्णांक on (config, पूर्णांकerface, alt)
 * criteria, जबतक the pxa architecture requires that.
 *
 * The solution is to define several pxa endpoपूर्णांकs matching one usb_ep. Ex:
 *   - "ep1-in" matches pxa endpoपूर्णांक EPA (which is an IN ep at addr 1, when
 *     the udc talks on (config=3, पूर्णांकerface=0, alt=0)
 *   - "ep1-in" matches pxa endpoपूर्णांक EPB (which is an IN ep at addr 1, when
 *     the udc talks on (config=3, पूर्णांकerface=0, alt=1)
 *   - "ep1-in" matches pxa endpoपूर्णांक EPC (which is an IN ep at addr 1, when
 *     the udc talks on (config=2, पूर्णांकerface=0, alt=0)
 *
 * We'll define the pxa endpoपूर्णांक by its index (EPA => idx=1, EPB => idx=2, ...)
 */

/*
 * Endpoपूर्णांक definition helpers
 */
#घोषणा USB_EP_DEF(addr, bname, dir, type, maxpkt, ctype, cdir) \
अणु .usb_ep = अणु	.name = bname, .ops = &pxa_ep_ops, .maxpacket = maxpkt, \
		.caps = USB_EP_CAPS(ctype, cdir), पूर्ण, \
  .desc = अणु	.bEndpoपूर्णांकAddress = addr | (dir ? USB_सूची_IN : 0), \
		.bmAttributes = USB_ENDPOINT_XFER_ ## type, \
		.wMaxPacketSize = maxpkt, पूर्ण, \
  .dev = &memory \
पूर्ण
#घोषणा USB_EP_BULK(addr, bname, dir, cdir) \
	USB_EP_DEF(addr, bname, dir, BULK, BULK_FIFO_SIZE, \
		USB_EP_CAPS_TYPE_BULK, cdir)
#घोषणा USB_EP_ISO(addr, bname, dir, cdir) \
	USB_EP_DEF(addr, bname, dir, ISOC, ISO_FIFO_SIZE, \
		USB_EP_CAPS_TYPE_ISO, cdir)
#घोषणा USB_EP_INT(addr, bname, dir, cdir) \
	USB_EP_DEF(addr, bname, dir, INT, INT_FIFO_SIZE, \
		USB_EP_CAPS_TYPE_INT, cdir)
#घोषणा USB_EP_IN_BULK(n)	USB_EP_BULK(n, "ep" #n "in-bulk", 1, \
					USB_EP_CAPS_सूची_IN)
#घोषणा USB_EP_OUT_BULK(n)	USB_EP_BULK(n, "ep" #n "out-bulk", 0, \
					USB_EP_CAPS_सूची_OUT)
#घोषणा USB_EP_IN_ISO(n)	USB_EP_ISO(n,  "ep" #n "in-iso", 1, \
					USB_EP_CAPS_सूची_IN)
#घोषणा USB_EP_OUT_ISO(n)	USB_EP_ISO(n,  "ep" #n "out-iso", 0, \
					USB_EP_CAPS_सूची_OUT)
#घोषणा USB_EP_IN_INT(n)	USB_EP_INT(n,  "ep" #n "in-int", 1, \
					USB_EP_CAPS_सूची_IN)
#घोषणा USB_EP_CTRL	USB_EP_DEF(0,  "ep0", 0, CONTROL, EP0_FIFO_SIZE, \
				USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_ALL)

#घोषणा PXA_EP_DEF(_idx, _addr, dir, _type, maxpkt, _config, अगरace, altset) \
अणु \
	.dev = &memory, \
	.name = "ep" #_idx, \
	.idx = _idx, .enabled = 0, \
	.dir_in = dir, .addr = _addr, \
	.config = _config, .पूर्णांकerface = अगरace, .alternate = altset, \
	.type = _type, .fअगरo_size = maxpkt, \
पूर्ण
#घोषणा PXA_EP_BULK(_idx, addr, dir, config, अगरace, alt) \
  PXA_EP_DEF(_idx, addr, dir, USB_ENDPOINT_XFER_BULK, BULK_FIFO_SIZE, \
		config, अगरace, alt)
#घोषणा PXA_EP_ISO(_idx, addr, dir, config, अगरace, alt) \
  PXA_EP_DEF(_idx, addr, dir, USB_ENDPOINT_XFER_ISOC, ISO_FIFO_SIZE, \
		config, अगरace, alt)
#घोषणा PXA_EP_INT(_idx, addr, dir, config, अगरace, alt) \
  PXA_EP_DEF(_idx, addr, dir, USB_ENDPOINT_XFER_INT, INT_FIFO_SIZE, \
		config, अगरace, alt)
#घोषणा PXA_EP_IN_BULK(i, adr, c, f, a)		PXA_EP_BULK(i, adr, 1, c, f, a)
#घोषणा PXA_EP_OUT_BULK(i, adr, c, f, a)	PXA_EP_BULK(i, adr, 0, c, f, a)
#घोषणा PXA_EP_IN_ISO(i, adr, c, f, a)		PXA_EP_ISO(i, adr, 1, c, f, a)
#घोषणा PXA_EP_OUT_ISO(i, adr, c, f, a)		PXA_EP_ISO(i, adr, 0, c, f, a)
#घोषणा PXA_EP_IN_INT(i, adr, c, f, a)		PXA_EP_INT(i, adr, 1, c, f, a)
#घोषणा PXA_EP_CTRL	PXA_EP_DEF(0, 0, 0, 0, EP0_FIFO_SIZE, 0, 0, 0)

काष्ठा pxa27x_udc;

काष्ठा stats अणु
	अचिन्हित दीर्घ in_ops;
	अचिन्हित दीर्घ out_ops;
	अचिन्हित दीर्घ in_bytes;
	अचिन्हित दीर्घ out_bytes;
	अचिन्हित दीर्घ irqs;
पूर्ण;

/**
 * काष्ठा udc_usb_ep - container of each usb_ep काष्ठाure
 * @usb_ep: usb endpoपूर्णांक
 * @desc: usb descriptor, especially type and address
 * @dev: udc managing this endpoपूर्णांक
 * @pxa_ep: matching pxa_ep (cache of find_pxa_ep() call)
 */
काष्ठा udc_usb_ep अणु
	काष्ठा usb_ep usb_ep;
	काष्ठा usb_endpoपूर्णांक_descriptor desc;
	काष्ठा pxa_udc *dev;
	काष्ठा pxa_ep *pxa_ep;
पूर्ण;

/**
 * काष्ठा pxa_ep - pxa endpoपूर्णांक
 * @dev: udc device
 * @queue: requests queue
 * @lock: lock to pxa_ep data (queues and stats)
 * @enabled: true when endpoपूर्णांक enabled (not stopped by gadget layer)
 * @in_handle_ep: number of recursions of handle_ep() function
 * 	Prevents deadlocks or infinite recursions of types :
 *	  irq->handle_ep()->req_करोne()->req.complete()->pxa_ep_queue()->handle_ep()
 *      or
 *        pxa_ep_queue()->handle_ep()->req_करोne()->req.complete()->pxa_ep_queue()
 * @idx: endpoपूर्णांक index (1 => epA, 2 => epB, ..., 24 => epX)
 * @name: endpoपूर्णांक name (क्रम trace/debug purpose)
 * @dir_in: 1 अगर IN endpoपूर्णांक, 0 अगर OUT endpoपूर्णांक
 * @addr: usb endpoपूर्णांक number
 * @config: configuration in which this endpoपूर्णांक is active
 * @पूर्णांकerface: पूर्णांकerface in which this endpoपूर्णांक is active
 * @alternate: altsetting in which this endpoitn is active
 * @fअगरo_size: max packet size in the endpoपूर्णांक fअगरo
 * @type: endpoपूर्णांक type (bulk, iso, पूर्णांक, ...)
 * @udccsr_value: save रेजिस्टर of UDCCSR0 क्रम suspend/resume
 * @udccr_value: save रेजिस्टर of UDCCR क्रम suspend/resume
 * @stats: endpoपूर्णांक statistics
 *
 * The *PROBLEM* is that pxa's endpoपूर्णांक configuration scheme is both misdeचिन्हित
 * (cares about config/पूर्णांकerface/altsetting, thus placing needless limits on
 * device capability) and full of implementation bugs क्रमcing it to be set up
 * क्रम use more or less like a pxa255.
 *
 * As we define the pxa_ep अटलally, we must guess all needed pxa_ep क्रम all
 * gadget which may work with this udc driver.
 */
काष्ठा pxa_ep अणु
	काष्ठा pxa_udc		*dev;

	काष्ठा list_head	queue;
	spinlock_t		lock;		/* Protects this काष्ठाure */
						/* (queues, stats) */
	अचिन्हित		enabled:1;
	अचिन्हित		in_handle_ep:1;

	अचिन्हित		idx:5;
	अक्षर			*name;

	/*
	 * Specअगरic pxa endpoपूर्णांक data, needed क्रम hardware initialization
	 */
	अचिन्हित		dir_in:1;
	अचिन्हित		addr:4;
	अचिन्हित		config:2;
	अचिन्हित		पूर्णांकerface:3;
	अचिन्हित		alternate:3;
	अचिन्हित		fअगरo_size;
	अचिन्हित		type;

#अगर_घोषित CONFIG_PM
	u32			udccsr_value;
	u32			udccr_value;
#पूर्ण_अगर
	काष्ठा stats		stats;
पूर्ण;

/**
 * काष्ठा pxa27x_request - container of each usb_request काष्ठाure
 * @req: usb request
 * @udc_usb_ep: usb endpoपूर्णांक the request was submitted on
 * @in_use: sanity check अगर request alपढ़ोy queued on an pxa_ep
 * @queue: linked list of requests, linked on pxa_ep->queue
 */
काष्ठा pxa27x_request अणु
	काष्ठा usb_request			req;
	काष्ठा udc_usb_ep			*udc_usb_ep;
	अचिन्हित				in_use:1;
	काष्ठा list_head			queue;
पूर्ण;

क्रमागत ep0_state अणु
	WAIT_FOR_SETUP,
	SETUP_STAGE,
	IN_DATA_STAGE,
	OUT_DATA_STAGE,
	IN_STATUS_STAGE,
	OUT_STATUS_STAGE,
	STALL,
	WAIT_ACK_SET_CONF_INTERF
पूर्ण;

अटल अक्षर *ep0_state_name[] = अणु
	"WAIT_FOR_SETUP", "SETUP_STAGE", "IN_DATA_STAGE", "OUT_DATA_STAGE",
	"IN_STATUS_STAGE", "OUT_STATUS_STAGE", "STALL",
	"WAIT_ACK_SET_CONF_INTERF"
पूर्ण;
#घोषणा EP0_STNAME(udc) ep0_state_name[(udc)->ep0state]

#घोषणा EP0_FIFO_SIZE	16U
#घोषणा BULK_FIFO_SIZE	64U
#घोषणा ISO_FIFO_SIZE	256U
#घोषणा INT_FIFO_SIZE	16U

काष्ठा udc_stats अणु
	अचिन्हित दीर्घ	irqs_reset;
	अचिन्हित दीर्घ	irqs_suspend;
	अचिन्हित दीर्घ	irqs_resume;
	अचिन्हित दीर्घ	irqs_reconfig;
पूर्ण;

#घोषणा NR_USB_ENDPOINTS (1 + 5)	/* ep0 + ep1in-bulk + .. + ep3in-iso */
#घोषणा NR_PXA_ENDPOINTS (1 + 14)	/* ep0 + epA + epB + .. + epX */

/**
 * काष्ठा pxa_udc - udc काष्ठाure
 * @regs: mapped IO space
 * @irq: udc irq
 * @clk: udc घड़ी
 * @usb_gadget: udc gadget काष्ठाure
 * @driver: bound gadget (zero, g_ether, g_mass_storage, ...)
 * @dev: device
 * @udc_command: machine specअगरic function to activate D+ pullup
 * @gpiod: gpio descriptor of gpio क्रम D+ pullup (or शून्य अगर none)
 * @transceiver: बाह्यal transceiver to handle vbus sense and D+ pullup
 * @ep0state: control endpoपूर्णांक state machine state
 * @stats: statistics on udc usage
 * @udc_usb_ep: array of usb endpoपूर्णांकs offered by the gadget
 * @pxa_ep: array of pxa available endpoपूर्णांकs
 * @enabled: UDC was enabled by a previous udc_enable()
 * @pullup_on: अगर pullup resistor connected to D+ pin
 * @pullup_resume: अगर pullup resistor should be connected to D+ pin on resume
 * @config: UDC active configuration
 * @last_पूर्णांकerface: UDC पूर्णांकerface of the last SET_INTERFACE host request
 * @last_alternate: UDC altsetting of the last SET_INTERFACE host request
 * @udccsr0: save of udccsr0 in हाल of suspend
 * @debugfs_root: root entry of debug fileप्रणाली
 * @debugfs_state: debugfs entry क्रम "udcstate"
 * @debugfs_queues: debugfs entry क्रम "queues"
 * @debugfs_eps: debugfs entry क्रम "epstate"
 */
काष्ठा pxa_udc अणु
	व्योम __iomem				*regs;
	पूर्णांक					irq;
	काष्ठा clk				*clk;

	काष्ठा usb_gadget			gadget;
	काष्ठा usb_gadget_driver		*driver;
	काष्ठा device				*dev;
	व्योम					(*udc_command)(पूर्णांक);
	काष्ठा gpio_desc			*gpiod;
	काष्ठा usb_phy				*transceiver;

	क्रमागत ep0_state				ep0state;
	काष्ठा udc_stats			stats;

	काष्ठा udc_usb_ep			udc_usb_ep[NR_USB_ENDPOINTS];
	काष्ठा pxa_ep				pxa_ep[NR_PXA_ENDPOINTS];

	अचिन्हित				enabled:1;
	अचिन्हित				pullup_on:1;
	अचिन्हित				pullup_resume:1;
	अचिन्हित				vbus_sensed:1;
	अचिन्हित				config:2;
	अचिन्हित				last_पूर्णांकerface:3;
	अचिन्हित				last_alternate:3;

#अगर_घोषित CONFIG_PM
	अचिन्हित				udccsr0;
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS
	काष्ठा dentry				*debugfs_root;
#पूर्ण_अगर
पूर्ण;
#घोषणा to_pxa(g)	(container_of((g), काष्ठा pxa_udc, gadget))

अटल अंतरभूत काष्ठा pxa_udc *to_gadget_udc(काष्ठा usb_gadget *gadget)
अणु
	वापस container_of(gadget, काष्ठा pxa_udc, gadget);
पूर्ण

/*
 * Debugging/message support
 */
#घोषणा ep_dbg(ep, fmt, arg...) \
	dev_dbg(ep->dev->dev, "%s:%s: " fmt, EPNAME(ep), __func__, ## arg)
#घोषणा ep_vdbg(ep, fmt, arg...) \
	dev_vdbg(ep->dev->dev, "%s:%s: " fmt, EPNAME(ep), __func__, ## arg)
#घोषणा ep_err(ep, fmt, arg...) \
	dev_err(ep->dev->dev, "%s:%s: " fmt, EPNAME(ep), __func__, ## arg)
#घोषणा ep_info(ep, fmt, arg...) \
	dev_info(ep->dev->dev, "%s:%s: " fmt, EPNAME(ep), __func__, ## arg)
#घोषणा ep_warn(ep, fmt, arg...) \
	dev_warn(ep->dev->dev, "%s:%s:" fmt, EPNAME(ep), __func__, ## arg)

#पूर्ण_अगर /* __LINUX_USB_GADGET_PXA27X_H */
