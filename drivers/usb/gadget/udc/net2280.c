<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम the PLX NET2280 USB device controller.
 * Specs and errata are available from <http://www.plxtech.com>.
 *
 * PLX Technology Inc. (क्रमmerly NetChip Technology) supported the
 * development of this driver.
 *
 *
 * CODE STATUS HIGHLIGHTS
 *
 * This driver should work well with most "gadget" drivers, including
 * the Mass Storage, Serial, and Ethernet/RNDIS gadget drivers
 * as well as Gadget Zero and Gadgetfs.
 *
 * DMA is enabled by शेष.
 *
 * MSI is enabled by शेष.  The legacy IRQ is used अगर MSI couldn't
 * be enabled.
 *
 * Note that almost all the errata workarounds here are only needed क्रम
 * rev1 chips.  Rev1a silicon (0110) fixes almost all of them.
 */

/*
 * Copyright (C) 2003 David Brownell
 * Copyright (C) 2003-2005 PLX Technology, Inc.
 * Copyright (C) 2014 Ricarकरो Ribalda - Qtechnology/AS
 *
 * Modअगरied Seth Levy 2005 PLX Technology, Inc. to provide compatibility
 *	with 2282 chip
 *
 * Modअगरied Ricarकरो Ribalda Qtechnology AS  to provide compatibility
 *	with usb 338x chip. Based on PLX driver
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा	DRIVER_DESC		"PLX NET228x/USB338x USB Peripheral Controller"
#घोषणा	DRIVER_VERSION		"2005 Sept 27/v3.0"

#घोषणा	EP_DONTUSE		13	/* nonzero */

#घोषणा USE_RDK_LEDS		/* GPIO pins control three LEDs */


अटल स्थिर अक्षर driver_name[] = "net2280";
अटल स्थिर अक्षर driver_desc[] = DRIVER_DESC;

अटल स्थिर u32 ep_bit[9] = अणु 0, 17, 2, 19, 4, 1, 18, 3, 20 पूर्ण;
अटल स्थिर अक्षर ep0name[] = "ep0";

#घोषणा EP_INFO(_name, _caps) \
	अणु \
		.name = _name, \
		.caps = _caps, \
	पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा usb_ep_caps caps;
पूर्ण ep_info_dft[] = अणु /* Default endpoपूर्णांक configuration */
	EP_INFO(ep0name,
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep-a",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep-b",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep-c",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep-d",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep-e",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep-f",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep-g",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep-h",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
पूर्ण, ep_info_adv[] = अणु /* Endpoपूर्णांकs क्रम usb3380 advance mode */
	EP_INFO(ep0name,
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep1in",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep2out",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep3in",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep4out",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep1out",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep2in",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep3out",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep4in",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_IN)),
पूर्ण;

#अघोषित EP_INFO

/* mode 0 == ep-अणुa,b,c,dपूर्ण 1K fअगरo each
 * mode 1 == ep-अणुa,bपूर्ण 2K fअगरo each, ep-अणुc,dपूर्ण unavailable
 * mode 2 == ep-a 2K fअगरo, ep-अणुb,cपूर्ण 1K each, ep-d unavailable
 */
अटल uलघु fअगरo_mode;

/* "modprobe net2280 fifo_mode=1" etc */
module_param(fअगरo_mode, uलघु, 0644);

/* enable_suspend -- When enabled, the driver will respond to
 * USB suspend requests by घातering करोwn the NET2280.  Otherwise,
 * USB suspend requests will be ignored.  This is acceptable क्रम
 * self-घातered devices
 */
अटल bool enable_suspend;

/* "modprobe net2280 enable_suspend=1" etc */
module_param(enable_suspend, bool, 0444);

#घोषणा	सूची_STRING(bAddress) (((bAddress) & USB_सूची_IN) ? "in" : "out")

अटल अक्षर *type_string(u8 bmAttributes)
अणु
	चयन ((bmAttributes) & USB_ENDPOINT_XFERTYPE_MASK) अणु
	हाल USB_ENDPOINT_XFER_BULK:	वापस "bulk";
	हाल USB_ENDPOINT_XFER_ISOC:	वापस "iso";
	हाल USB_ENDPOINT_XFER_INT:	वापस "intr";
	पूर्ण
	वापस "control";
पूर्ण

#समावेश "net2280.h"

#घोषणा valid_bit	cpu_to_le32(BIT(VALID_BIT))
#घोषणा dma_करोne_ie	cpu_to_le32(BIT(DMA_DONE_INTERRUPT_ENABLE))

अटल व्योम ep_clear_seqnum(काष्ठा net2280_ep *ep);
अटल व्योम stop_activity(काष्ठा net2280 *dev,
					काष्ठा usb_gadget_driver *driver);
अटल व्योम ep0_start(काष्ठा net2280 *dev);

/*-------------------------------------------------------------------------*/
अटल अंतरभूत व्योम enable_pciirqenb(काष्ठा net2280_ep *ep)
अणु
	u32 पंचांगp = पढ़ोl(&ep->dev->regs->pciirqenb0);

	अगर (ep->dev->quirks & PLX_LEGACY)
		पंचांगp |= BIT(ep->num);
	अन्यथा
		पंचांगp |= BIT(ep_bit[ep->num]);
	ग_लिखोl(पंचांगp, &ep->dev->regs->pciirqenb0);

	वापस;
पूर्ण

अटल पूर्णांक
net2280_enable(काष्ठा usb_ep *_ep, स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा net2280		*dev;
	काष्ठा net2280_ep	*ep;
	u32			max;
	u32 पंचांगp = 0;
	u32 type;
	अचिन्हित दीर्घ		flags;
	अटल स्थिर u32 ep_key[9] = अणु 1, 0, 1, 0, 1, 1, 0, 1, 0 पूर्ण;
	पूर्णांक ret = 0;

	ep = container_of(_ep, काष्ठा net2280_ep, ep);
	अगर (!_ep || !desc || ep->desc || _ep->name == ep0name ||
			desc->bDescriptorType != USB_DT_ENDPOINT) अणु
		pr_err("%s: failed at line=%d\n", __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण
	dev = ep->dev;
	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN) अणु
		ret = -ESHUTDOWN;
		जाओ prपूर्णांक_err;
	पूर्ण

	/* erratum 0119 workaround ties up an endpoपूर्णांक number */
	अगर ((desc->bEndpoपूर्णांकAddress & 0x0f) == EP_DONTUSE) अणु
		ret = -गलत_तर्क;
		जाओ prपूर्णांक_err;
	पूर्ण

	अगर (dev->quirks & PLX_PCIE) अणु
		अगर ((desc->bEndpoपूर्णांकAddress & 0x0f) >= 0x0c) अणु
			ret = -गलत_तर्क;
			जाओ prपूर्णांक_err;
		पूर्ण
		ep->is_in = !!usb_endpoपूर्णांक_dir_in(desc);
		अगर (dev->enhanced_mode && ep->is_in && ep_key[ep->num]) अणु
			ret = -EINVAL;
			जाओ prपूर्णांक_err;
		पूर्ण
	पूर्ण

	/* sanity check ep-e/ep-f since their fअगरos are small */
	max = usb_endpoपूर्णांक_maxp(desc);
	अगर (ep->num > 4 && max > 64 && (dev->quirks & PLX_LEGACY)) अणु
		ret = -दुस्फल;
		जाओ prपूर्णांक_err;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	_ep->maxpacket = max;
	ep->desc = desc;

	/* ep_reset() has alपढ़ोy been called */
	ep->stopped = 0;
	ep->wedged = 0;
	ep->out_overflow = 0;

	/* set speed-dependent max packet; may kick in high bandwidth */
	set_max_speed(ep, max);

	/* set type, direction, address; reset fअगरo counters */
	ग_लिखोl(BIT(FIFO_FLUSH), &ep->regs->ep_stat);

	अगर ((dev->quirks & PLX_PCIE) && dev->enhanced_mode) अणु
		पंचांगp = पढ़ोl(&ep->cfg->ep_cfg);
		/* If USB ep number करोesn't match hardware ep number */
		अगर ((पंचांगp & 0xf) != usb_endpoपूर्णांक_num(desc)) अणु
			ret = -EINVAL;
			spin_unlock_irqrestore(&dev->lock, flags);
			जाओ prपूर्णांक_err;
		पूर्ण
		अगर (ep->is_in)
			पंचांगp &= ~USB3380_EP_CFG_MASK_IN;
		अन्यथा
			पंचांगp &= ~USB3380_EP_CFG_MASK_OUT;
	पूर्ण
	type = (desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK);
	अगर (type == USB_ENDPOINT_XFER_INT) अणु
		/* erratum 0105 workaround prevents hs NYET */
		अगर (dev->chiprev == 0100 &&
				dev->gadget.speed == USB_SPEED_HIGH &&
				!(desc->bEndpoपूर्णांकAddress & USB_सूची_IN))
			ग_लिखोl(BIT(CLEAR_NAK_OUT_PACKETS_MODE),
				&ep->regs->ep_rsp);
	पूर्ण अन्यथा अगर (type == USB_ENDPOINT_XFER_BULK) अणु
		/* catch some particularly blatant driver bugs */
		अगर ((dev->gadget.speed == USB_SPEED_SUPER && max != 1024) ||
		    (dev->gadget.speed == USB_SPEED_HIGH && max != 512) ||
		    (dev->gadget.speed == USB_SPEED_FULL && max > 64)) अणु
			spin_unlock_irqrestore(&dev->lock, flags);
			ret = -दुस्फल;
			जाओ prपूर्णांक_err;
		पूर्ण
	पूर्ण
	ep->is_iso = (type == USB_ENDPOINT_XFER_ISOC);
	/* Enable this endpoपूर्णांक */
	अगर (dev->quirks & PLX_LEGACY) अणु
		पंचांगp |= type << ENDPOINT_TYPE;
		पंचांगp |= desc->bEndpoपूर्णांकAddress;
		/* शेष full fअगरo lines */
		पंचांगp |= (4 << ENDPOINT_BYTE_COUNT);
		पंचांगp |= BIT(ENDPOINT_ENABLE);
		ep->is_in = (पंचांगp & USB_सूची_IN) != 0;
	पूर्ण अन्यथा अणु
		/* In Legacy mode, only OUT endpoपूर्णांकs are used */
		अगर (dev->enhanced_mode && ep->is_in) अणु
			पंचांगp |= type << IN_ENDPOINT_TYPE;
			पंचांगp |= BIT(IN_ENDPOINT_ENABLE);
		पूर्ण अन्यथा अणु
			पंचांगp |= type << OUT_ENDPOINT_TYPE;
			पंचांगp |= BIT(OUT_ENDPOINT_ENABLE);
			पंचांगp |= (ep->is_in << ENDPOINT_सूचीECTION);
		पूर्ण

		पंचांगp |= (4 << ENDPOINT_BYTE_COUNT);
		अगर (!dev->enhanced_mode)
			पंचांगp |= usb_endpoपूर्णांक_num(desc);
		पंचांगp |= (ep->ep.maxburst << MAX_BURST_SIZE);
	पूर्ण

	/* Make sure all the रेजिस्टरs are written beक्रमe ep_rsp*/
	wmb();

	/* क्रम OUT transfers, block the rx fअगरo until a पढ़ो is posted */
	अगर (!ep->is_in)
		ग_लिखोl(BIT(SET_NAK_OUT_PACKETS), &ep->regs->ep_rsp);
	अन्यथा अगर (!(dev->quirks & PLX_2280)) अणु
		/* Added क्रम 2282, Don't use nak packets on an in endpoपूर्णांक,
		 * this was ignored on 2280
		 */
		ग_लिखोl(BIT(CLEAR_NAK_OUT_PACKETS) |
			BIT(CLEAR_NAK_OUT_PACKETS_MODE), &ep->regs->ep_rsp);
	पूर्ण

	अगर (dev->quirks & PLX_PCIE)
		ep_clear_seqnum(ep);
	ग_लिखोl(पंचांगp, &ep->cfg->ep_cfg);

	/* enable irqs */
	अगर (!ep->dma) अणु				/* pio, per-packet */
		enable_pciirqenb(ep);

		पंचांगp = BIT(DATA_PACKET_RECEIVED_INTERRUPT_ENABLE) |
			BIT(DATA_PACKET_TRANSMITTED_INTERRUPT_ENABLE);
		अगर (dev->quirks & PLX_2280)
			पंचांगp |= पढ़ोl(&ep->regs->ep_irqenb);
		ग_लिखोl(पंचांगp, &ep->regs->ep_irqenb);
	पूर्ण अन्यथा अणु				/* dma, per-request */
		पंचांगp = BIT((8 + ep->num));	/* completion */
		पंचांगp |= पढ़ोl(&dev->regs->pciirqenb1);
		ग_लिखोl(पंचांगp, &dev->regs->pciirqenb1);

		/* क्रम लघु OUT transfers, dma completions can't
		 * advance the queue; करो it pio-style, by hand.
		 * NOTE erratum 0112 workaround #2
		 */
		अगर ((desc->bEndpoपूर्णांकAddress & USB_सूची_IN) == 0) अणु
			पंचांगp = BIT(SHORT_PACKET_TRANSFERRED_INTERRUPT_ENABLE);
			ग_लिखोl(पंचांगp, &ep->regs->ep_irqenb);

			enable_pciirqenb(ep);
		पूर्ण
	पूर्ण

	पंचांगp = desc->bEndpoपूर्णांकAddress;
	ep_dbg(dev, "enabled %s (ep%d%s-%s) %s max %04x\n",
		_ep->name, पंचांगp & 0x0f, सूची_STRING(पंचांगp),
		type_string(desc->bmAttributes),
		ep->dma ? "dma" : "pio", max);

	/* pci ग_लिखोs may still be posted */
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;

prपूर्णांक_err:
	dev_err(&ep->dev->pdev->dev, "%s: error=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक handshake(u32 __iomem *ptr, u32 mask, u32 करोne, पूर्णांक usec)
अणु
	u32	result;
	पूर्णांक	ret;

	ret = पढ़ोl_poll_समयout_atomic(ptr, result,
					((result & mask) == करोne ||
					 result == U32_MAX),
					1, usec);
	अगर (result == U32_MAX)		/* device unplugged */
		वापस -ENODEV;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops net2280_ep_ops;

अटल व्योम ep_reset_228x(काष्ठा net2280_regs __iomem *regs,
			  काष्ठा net2280_ep *ep)
अणु
	u32		पंचांगp;

	ep->desc = शून्य;
	INIT_LIST_HEAD(&ep->queue);

	usb_ep_set_maxpacket_limit(&ep->ep, ~0);
	ep->ep.ops = &net2280_ep_ops;

	/* disable the dma, irqs, endpoपूर्णांक... */
	अगर (ep->dma) अणु
		ग_लिखोl(0, &ep->dma->dmactl);
		ग_लिखोl(BIT(DMA_SCATTER_GATHER_DONE_INTERRUPT) |
			BIT(DMA_TRANSACTION_DONE_INTERRUPT) |
			BIT(DMA_ABORT),
			&ep->dma->dmastat);

		पंचांगp = पढ़ोl(&regs->pciirqenb0);
		पंचांगp &= ~BIT(ep->num);
		ग_लिखोl(पंचांगp, &regs->pciirqenb0);
	पूर्ण अन्यथा अणु
		पंचांगp = पढ़ोl(&regs->pciirqenb1);
		पंचांगp &= ~BIT((8 + ep->num));	/* completion */
		ग_लिखोl(पंचांगp, &regs->pciirqenb1);
	पूर्ण
	ग_लिखोl(0, &ep->regs->ep_irqenb);

	/* init to our chosen शेषs, notably so that we NAK OUT
	 * packets until the driver queues a पढ़ो (+note erratum 0112)
	 */
	अगर (!ep->is_in || (ep->dev->quirks & PLX_2280)) अणु
		पंचांगp = BIT(SET_NAK_OUT_PACKETS_MODE) |
		BIT(SET_NAK_OUT_PACKETS) |
		BIT(CLEAR_EP_HIDE_STATUS_PHASE) |
		BIT(CLEAR_INTERRUPT_MODE);
	पूर्ण अन्यथा अणु
		/* added क्रम 2282 */
		पंचांगp = BIT(CLEAR_NAK_OUT_PACKETS_MODE) |
		BIT(CLEAR_NAK_OUT_PACKETS) |
		BIT(CLEAR_EP_HIDE_STATUS_PHASE) |
		BIT(CLEAR_INTERRUPT_MODE);
	पूर्ण

	अगर (ep->num != 0) अणु
		पंचांगp |= BIT(CLEAR_ENDPOINT_TOGGLE) |
			BIT(CLEAR_ENDPOINT_HALT);
	पूर्ण
	ग_लिखोl(पंचांगp, &ep->regs->ep_rsp);

	/* scrub most status bits, and flush any fअगरo state */
	अगर (ep->dev->quirks & PLX_2280)
		पंचांगp = BIT(FIFO_OVERFLOW) |
			BIT(FIFO_UNDERFLOW);
	अन्यथा
		पंचांगp = 0;

	ग_लिखोl(पंचांगp | BIT(TIMEOUT) |
		BIT(USB_STALL_SENT) |
		BIT(USB_IN_NAK_SENT) |
		BIT(USB_IN_ACK_RCVD) |
		BIT(USB_OUT_PING_NAK_SENT) |
		BIT(USB_OUT_ACK_SENT) |
		BIT(FIFO_FLUSH) |
		BIT(SHORT_PACKET_OUT_DONE_INTERRUPT) |
		BIT(SHORT_PACKET_TRANSFERRED_INTERRUPT) |
		BIT(DATA_PACKET_RECEIVED_INTERRUPT) |
		BIT(DATA_PACKET_TRANSMITTED_INTERRUPT) |
		BIT(DATA_OUT_PING_TOKEN_INTERRUPT) |
		BIT(DATA_IN_TOKEN_INTERRUPT),
		&ep->regs->ep_stat);

	/* fअगरo size is handled separately */
पूर्ण

अटल व्योम ep_reset_338x(काष्ठा net2280_regs __iomem *regs,
					काष्ठा net2280_ep *ep)
अणु
	u32 पंचांगp, dmastat;

	ep->desc = शून्य;
	INIT_LIST_HEAD(&ep->queue);

	usb_ep_set_maxpacket_limit(&ep->ep, ~0);
	ep->ep.ops = &net2280_ep_ops;

	/* disable the dma, irqs, endpoपूर्णांक... */
	अगर (ep->dma) अणु
		ग_लिखोl(0, &ep->dma->dmactl);
		ग_लिखोl(BIT(DMA_ABORT_DONE_INTERRUPT) |
		       BIT(DMA_PAUSE_DONE_INTERRUPT) |
		       BIT(DMA_SCATTER_GATHER_DONE_INTERRUPT) |
		       BIT(DMA_TRANSACTION_DONE_INTERRUPT),
		       /* | BIT(DMA_ABORT), */
		       &ep->dma->dmastat);

		dmastat = पढ़ोl(&ep->dma->dmastat);
		अगर (dmastat == 0x5002) अणु
			ep_warn(ep->dev, "The dmastat return = %x!!\n",
			       dmastat);
			ग_लिखोl(0x5a, &ep->dma->dmastat);
		पूर्ण

		पंचांगp = पढ़ोl(&regs->pciirqenb0);
		पंचांगp &= ~BIT(ep_bit[ep->num]);
		ग_लिखोl(पंचांगp, &regs->pciirqenb0);
	पूर्ण अन्यथा अणु
		अगर (ep->num < 5) अणु
			पंचांगp = पढ़ोl(&regs->pciirqenb1);
			पंचांगp &= ~BIT((8 + ep->num));	/* completion */
			ग_लिखोl(पंचांगp, &regs->pciirqenb1);
		पूर्ण
	पूर्ण
	ग_लिखोl(0, &ep->regs->ep_irqenb);

	ग_लिखोl(BIT(SHORT_PACKET_OUT_DONE_INTERRUPT) |
	       BIT(SHORT_PACKET_TRANSFERRED_INTERRUPT) |
	       BIT(FIFO_OVERFLOW) |
	       BIT(DATA_PACKET_RECEIVED_INTERRUPT) |
	       BIT(DATA_PACKET_TRANSMITTED_INTERRUPT) |
	       BIT(DATA_OUT_PING_TOKEN_INTERRUPT) |
	       BIT(DATA_IN_TOKEN_INTERRUPT), &ep->regs->ep_stat);

	पंचांगp = पढ़ोl(&ep->cfg->ep_cfg);
	अगर (ep->is_in)
		पंचांगp &= ~USB3380_EP_CFG_MASK_IN;
	अन्यथा
		पंचांगp &= ~USB3380_EP_CFG_MASK_OUT;
	ग_लिखोl(पंचांगp, &ep->cfg->ep_cfg);
पूर्ण

अटल व्योम nuke(काष्ठा net2280_ep *);

अटल पूर्णांक net2280_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा net2280_ep	*ep;
	अचिन्हित दीर्घ		flags;

	ep = container_of(_ep, काष्ठा net2280_ep, ep);
	अगर (!_ep || _ep->name == ep0name) अणु
		pr_err("%s: Invalid ep=%p\n", __func__, _ep);
		वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(&ep->dev->lock, flags);
	nuke(ep);

	अगर (ep->dev->quirks & PLX_PCIE)
		ep_reset_338x(ep->dev->regs, ep);
	अन्यथा
		ep_reset_228x(ep->dev->regs, ep);

	ep_vdbg(ep->dev, "disabled %s %s\n",
			ep->dma ? "dma" : "pio", _ep->name);

	/* synch memory views with the device */
	(व्योम)पढ़ोl(&ep->cfg->ep_cfg);

	अगर (!ep->dma && ep->num >= 1 && ep->num <= 4)
		ep->dma = &ep->dev->dma[ep->num - 1];

	spin_unlock_irqrestore(&ep->dev->lock, flags);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_request
*net2280_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा net2280_ep	*ep;
	काष्ठा net2280_request	*req;

	अगर (!_ep) अणु
		pr_err("%s: Invalid ep\n", __func__);
		वापस शून्य;
	पूर्ण
	ep = container_of(_ep, काष्ठा net2280_ep, ep);

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	/* this dma descriptor may be swapped with the previous dummy */
	अगर (ep->dma) अणु
		काष्ठा net2280_dma	*td;

		td = dma_pool_alloc(ep->dev->requests, gfp_flags,
				&req->td_dma);
		अगर (!td) अणु
			kमुक्त(req);
			वापस शून्य;
		पूर्ण
		td->dmacount = 0;	/* not VALID */
		td->dmadesc = td->dmaaddr;
		req->td = td;
	पूर्ण
	वापस &req->req;
पूर्ण

अटल व्योम net2280_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा net2280_ep	*ep;
	काष्ठा net2280_request	*req;

	ep = container_of(_ep, काष्ठा net2280_ep, ep);
	अगर (!_ep || !_req) अणु
		dev_err(&ep->dev->pdev->dev, "%s: Invalid ep=%p or req=%p\n",
							__func__, _ep, _req);
		वापस;
	पूर्ण

	req = container_of(_req, काष्ठा net2280_request, req);
	WARN_ON(!list_empty(&req->queue));
	अगर (req->td)
		dma_pool_मुक्त(ep->dev->requests, req->td, req->td_dma);
	kमुक्त(req);
पूर्ण

/*-------------------------------------------------------------------------*/

/* load a packet पूर्णांकo the fअगरo we use क्रम usb IN transfers.
 * works क्रम all endpoपूर्णांकs.
 *
 * NOTE: pio with ep-a..ep-d could stuff multiple packets पूर्णांकo the fअगरo
 * at a समय, but this code is simpler because it knows it only ग_लिखोs
 * one packet.  ep-a..ep-d should use dma instead.
 */
अटल व्योम ग_लिखो_fअगरo(काष्ठा net2280_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा net2280_ep_regs	__iomem *regs = ep->regs;
	u8			*buf;
	u32			पंचांगp;
	अचिन्हित		count, total;

	/* INVARIANT:  fअगरo is currently empty. (testable) */

	अगर (req) अणु
		buf = req->buf + req->actual;
		prefetch(buf);
		total = req->length - req->actual;
	पूर्ण अन्यथा अणु
		total = 0;
		buf = शून्य;
	पूर्ण

	/* ग_लिखो just one packet at a समय */
	count = ep->ep.maxpacket;
	अगर (count > total)	/* min() cannot be used on a bitfield */
		count = total;

	ep_vdbg(ep->dev, "write %s fifo (IN) %d bytes%s req %p\n",
			ep->ep.name, count,
			(count != ep->ep.maxpacket) ? " (short)" : "",
			req);
	जबतक (count >= 4) अणु
		/* NOTE be careful अगर you try to align these. fअगरo lines
		 * should normally be full (4 bytes) and successive partial
		 * lines are ok only in certain हालs.
		 */
		पंचांगp = get_unaligned((u32 *)buf);
		cpu_to_le32s(&पंचांगp);
		ग_लिखोl(पंचांगp, &regs->ep_data);
		buf += 4;
		count -= 4;
	पूर्ण

	/* last fअगरo entry is "short" unless we wrote a full packet.
	 * also explicitly validate last word in (periodic) transfers
	 * when maxpacket is not a multiple of 4 bytes.
	 */
	अगर (count || total < ep->ep.maxpacket) अणु
		पंचांगp = count ? get_unaligned((u32 *)buf) : count;
		cpu_to_le32s(&पंचांगp);
		set_fअगरo_bytecount(ep, count & 0x03);
		ग_लिखोl(पंचांगp, &regs->ep_data);
	पूर्ण

	/* pci ग_लिखोs may still be posted */
पूर्ण

/* work around erratum 0106: PCI and USB race over the OUT fअगरo.
 * caller guarantees chiprev 0100, out endpoपूर्णांक is NAKing, and
 * there's no real data in the fअगरo.
 *
 * NOTE:  also used in हालs where that erratum करोesn't apply:
 * where the host wrote "too much" data to us.
 */
अटल व्योम out_flush(काष्ठा net2280_ep *ep)
अणु
	u32	__iomem *statp;
	u32	पंचांगp;

	statp = &ep->regs->ep_stat;

	पंचांगp = पढ़ोl(statp);
	अगर (पंचांगp & BIT(NAK_OUT_PACKETS)) अणु
		ep_dbg(ep->dev, "%s %s %08x !NAK\n",
			ep->ep.name, __func__, पंचांगp);
		ग_लिखोl(BIT(SET_NAK_OUT_PACKETS), &ep->regs->ep_rsp);
	पूर्ण

	ग_लिखोl(BIT(DATA_OUT_PING_TOKEN_INTERRUPT) |
		BIT(DATA_PACKET_RECEIVED_INTERRUPT),
		statp);
	ग_लिखोl(BIT(FIFO_FLUSH), statp);
	/* Make sure that stap is written */
	mb();
	पंचांगp = पढ़ोl(statp);
	अगर (पंचांगp & BIT(DATA_OUT_PING_TOKEN_INTERRUPT) &&
			/* high speed did bulk NYET; fअगरo isn't filling */
			ep->dev->gadget.speed == USB_SPEED_FULL) अणु
		अचिन्हित	usec;

		usec = 50;		/* 64 byte bulk/पूर्णांकerrupt */
		handshake(statp, BIT(USB_OUT_PING_NAK_SENT),
				BIT(USB_OUT_PING_NAK_SENT), usec);
		/* NAK करोne; now CLEAR_NAK_OUT_PACKETS is safe */
	पूर्ण
पूर्ण

/* unload packet(s) from the fअगरo we use क्रम usb OUT transfers.
 * वापसs true अगरf the request completed, because of लघु packet
 * or the request buffer having filled with full packets.
 *
 * क्रम ep-a..ep-d this will पढ़ो multiple packets out when they
 * have been accepted.
 */
अटल पूर्णांक पढ़ो_fअगरo(काष्ठा net2280_ep *ep, काष्ठा net2280_request *req)
अणु
	काष्ठा net2280_ep_regs	__iomem *regs = ep->regs;
	u8			*buf = req->req.buf + req->req.actual;
	अचिन्हित		count, पंचांगp, is_लघु;
	अचिन्हित		cleanup = 0, prevent = 0;

	/* erratum 0106 ... packets coming in during fअगरo पढ़ोs might
	 * be incompletely rejected.  not all हालs have workarounds.
	 */
	अगर (ep->dev->chiprev == 0x0100 &&
			ep->dev->gadget.speed == USB_SPEED_FULL) अणु
		udelay(1);
		पंचांगp = पढ़ोl(&ep->regs->ep_stat);
		अगर ((पंचांगp & BIT(NAK_OUT_PACKETS)))
			cleanup = 1;
		अन्यथा अगर ((पंचांगp & BIT(FIFO_FULL))) अणु
			start_out_naking(ep);
			prevent = 1;
		पूर्ण
		/* अन्यथा: hope we करोn't see the problem */
	पूर्ण

	/* never overflow the rx buffer. the fअगरo पढ़ोs packets until
	 * it sees a लघु one; we might not be पढ़ोy क्रम them all.
	 */
	prefetchw(buf);
	count = पढ़ोl(&regs->ep_avail);
	अगर (unlikely(count == 0)) अणु
		udelay(1);
		पंचांगp = पढ़ोl(&ep->regs->ep_stat);
		count = पढ़ोl(&regs->ep_avail);
		/* handled that data alपढ़ोy? */
		अगर (count == 0 && (पंचांगp & BIT(NAK_OUT_PACKETS)) == 0)
			वापस 0;
	पूर्ण

	पंचांगp = req->req.length - req->req.actual;
	अगर (count > पंचांगp) अणु
		/* as with DMA, data overflow माला_लो flushed */
		अगर ((पंचांगp % ep->ep.maxpacket) != 0) अणु
			ep_err(ep->dev,
				"%s out fifo %d bytes, expected %d\n",
				ep->ep.name, count, पंचांगp);
			req->req.status = -EOVERFLOW;
			cleanup = 1;
			/* NAK_OUT_PACKETS will be set, so flushing is safe;
			 * the next पढ़ो will start with the next packet
			 */
		पूर्ण /* अन्यथा it's a ZLP, no worries */
		count = पंचांगp;
	पूर्ण
	req->req.actual += count;

	is_लघु = (count == 0) || ((count % ep->ep.maxpacket) != 0);

	ep_vdbg(ep->dev, "read %s fifo (OUT) %d bytes%s%s%s req %p %d/%d\n",
			ep->ep.name, count, is_लघु ? " (short)" : "",
			cleanup ? " flush" : "", prevent ? " nak" : "",
			req, req->req.actual, req->req.length);

	जबतक (count >= 4) अणु
		पंचांगp = पढ़ोl(&regs->ep_data);
		cpu_to_le32s(&पंचांगp);
		put_unaligned(पंचांगp, (u32 *)buf);
		buf += 4;
		count -= 4;
	पूर्ण
	अगर (count) अणु
		पंचांगp = पढ़ोl(&regs->ep_data);
		/* LE conversion is implicit here: */
		करो अणु
			*buf++ = (u8) पंचांगp;
			पंचांगp >>= 8;
		पूर्ण जबतक (--count);
	पूर्ण
	अगर (cleanup)
		out_flush(ep);
	अगर (prevent) अणु
		ग_लिखोl(BIT(CLEAR_NAK_OUT_PACKETS), &ep->regs->ep_rsp);
		(व्योम) पढ़ोl(&ep->regs->ep_rsp);
	पूर्ण

	वापस is_लघु || req->req.actual == req->req.length;
पूर्ण

/* fill out dma descriptor to match a given request */
अटल व्योम fill_dma_desc(काष्ठा net2280_ep *ep,
					काष्ठा net2280_request *req, पूर्णांक valid)
अणु
	काष्ठा net2280_dma	*td = req->td;
	u32			dmacount = req->req.length;

	/* करोn't let DMA जारी after a लघु OUT packet,
	 * so overruns can't affect the next transfer.
	 * in हाल of overruns on max-size packets, we can't
	 * stop the fअगरo from filling but we can flush it.
	 */
	अगर (ep->is_in)
		dmacount |= BIT(DMA_सूचीECTION);
	अगर ((!ep->is_in && (dmacount % ep->ep.maxpacket) != 0) ||
					!(ep->dev->quirks & PLX_2280))
		dmacount |= BIT(END_OF_CHAIN);

	req->valid = valid;
	अगर (valid)
		dmacount |= BIT(VALID_BIT);
	dmacount |= BIT(DMA_DONE_INTERRUPT_ENABLE);

	/* td->dmadesc = previously set by caller */
	td->dmaaddr = cpu_to_le32 (req->req.dma);

	/* 2280 may be polling VALID_BIT through ep->dma->dmadesc */
	wmb();
	td->dmacount = cpu_to_le32(dmacount);
पूर्ण

अटल स्थिर u32 dmactl_शेष =
		BIT(DMA_SCATTER_GATHER_DONE_INTERRUPT) |
		BIT(DMA_CLEAR_COUNT_ENABLE) |
		/* erratum 0116 workaround part 1 (use POLLING) */
		(POLL_100_USEC << DESCRIPTOR_POLLING_RATE) |
		BIT(DMA_VALID_BIT_POLLING_ENABLE) |
		BIT(DMA_VALID_BIT_ENABLE) |
		BIT(DMA_SCATTER_GATHER_ENABLE) |
		/* erratum 0116 workaround part 2 (no AUTOSTART) */
		BIT(DMA_ENABLE);

अटल अंतरभूत व्योम spin_stop_dma(काष्ठा net2280_dma_regs __iomem *dma)
अणु
	handshake(&dma->dmactl, BIT(DMA_ENABLE), 0, 50);
पूर्ण

अटल अंतरभूत व्योम stop_dma(काष्ठा net2280_dma_regs __iomem *dma)
अणु
	ग_लिखोl(पढ़ोl(&dma->dmactl) & ~BIT(DMA_ENABLE), &dma->dmactl);
	spin_stop_dma(dma);
पूर्ण

अटल व्योम start_queue(काष्ठा net2280_ep *ep, u32 dmactl, u32 td_dma)
अणु
	काष्ठा net2280_dma_regs	__iomem *dma = ep->dma;
	अचिन्हित पूर्णांक पंचांगp = BIT(VALID_BIT) | (ep->is_in << DMA_सूचीECTION);

	अगर (!(ep->dev->quirks & PLX_2280))
		पंचांगp |= BIT(END_OF_CHAIN);

	ग_लिखोl(पंचांगp, &dma->dmacount);
	ग_लिखोl(पढ़ोl(&dma->dmastat), &dma->dmastat);

	ग_लिखोl(td_dma, &dma->dmadesc);
	अगर (ep->dev->quirks & PLX_PCIE)
		dmactl |= BIT(DMA_REQUEST_OUTSTANDING);
	ग_लिखोl(dmactl, &dma->dmactl);

	/* erratum 0116 workaround part 3:  pci arbiter away from net2280 */
	(व्योम) पढ़ोl(&ep->dev->pci->pcimstctl);

	ग_लिखोl(BIT(DMA_START), &dma->dmastat);
पूर्ण

अटल व्योम start_dma(काष्ठा net2280_ep *ep, काष्ठा net2280_request *req)
अणु
	u32			पंचांगp;
	काष्ठा net2280_dma_regs	__iomem *dma = ep->dma;

	/* FIXME can't use DMA क्रम ZLPs */

	/* on this path we "know" there's no dma active (yet) */
	WARN_ON(पढ़ोl(&dma->dmactl) & BIT(DMA_ENABLE));
	ग_लिखोl(0, &ep->dma->dmactl);

	/* previous OUT packet might have been लघु */
	अगर (!ep->is_in && (पढ़ोl(&ep->regs->ep_stat) &
				BIT(NAK_OUT_PACKETS))) अणु
		ग_लिखोl(BIT(SHORT_PACKET_TRANSFERRED_INTERRUPT),
			&ep->regs->ep_stat);

		पंचांगp = पढ़ोl(&ep->regs->ep_avail);
		अगर (पंचांगp) अणु
			ग_लिखोl(पढ़ोl(&dma->dmastat), &dma->dmastat);

			/* transfer all/some fअगरo data */
			ग_लिखोl(req->req.dma, &dma->dmaaddr);
			पंचांगp = min(पंचांगp, req->req.length);

			/* dma irq, faking scatterlist status */
			req->td->dmacount = cpu_to_le32(req->req.length - पंचांगp);
			ग_लिखोl(BIT(DMA_DONE_INTERRUPT_ENABLE) | पंचांगp,
					&dma->dmacount);
			req->td->dmadesc = 0;
			req->valid = 1;

			ग_लिखोl(BIT(DMA_ENABLE), &dma->dmactl);
			ग_लिखोl(BIT(DMA_START), &dma->dmastat);
			वापस;
		पूर्ण
		stop_out_naking(ep);
	पूर्ण

	पंचांगp = dmactl_शेष;

	/* क्रमce packet boundaries between dma requests, but prevent the
	 * controller from स्वतःmagically writing a last "short" packet
	 * (zero length) unless the driver explicitly said to करो that.
	 */
	अगर (ep->is_in) अणु
		अगर (likely((req->req.length % ep->ep.maxpacket) ||
							req->req.zero))अणु
			पंचांगp |= BIT(DMA_FIFO_VALIDATE);
			ep->in_fअगरo_validate = 1;
		पूर्ण अन्यथा
			ep->in_fअगरo_validate = 0;
	पूर्ण

	/* init req->td, poपूर्णांकing to the current dummy */
	req->td->dmadesc = cpu_to_le32 (ep->td_dma);
	fill_dma_desc(ep, req, 1);

	req->td->dmacount |= cpu_to_le32(BIT(END_OF_CHAIN));

	start_queue(ep, पंचांगp, req->td_dma);
पूर्ण

अटल अंतरभूत व्योम
queue_dma(काष्ठा net2280_ep *ep, काष्ठा net2280_request *req, पूर्णांक valid)
अणु
	काष्ठा net2280_dma	*end;
	dma_addr_t		पंचांगp;

	/* swap new dummy क्रम old, link; fill and maybe activate */
	end = ep->dummy;
	ep->dummy = req->td;
	req->td = end;

	पंचांगp = ep->td_dma;
	ep->td_dma = req->td_dma;
	req->td_dma = पंचांगp;

	end->dmadesc = cpu_to_le32 (ep->td_dma);

	fill_dma_desc(ep, req, valid);
पूर्ण

अटल व्योम
करोne(काष्ठा net2280_ep *ep, काष्ठा net2280_request *req, पूर्णांक status)
अणु
	काष्ठा net2280		*dev;
	अचिन्हित		stopped = ep->stopped;

	list_del_init(&req->queue);

	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	dev = ep->dev;
	अगर (ep->dma)
		usb_gadget_unmap_request(&dev->gadget, &req->req, ep->is_in);

	अगर (status && status != -ESHUTDOWN)
		ep_vdbg(dev, "complete %s req %p stat %d len %u/%u\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	/* करोn't modअगरy queue heads during completion callback */
	ep->stopped = 1;
	spin_unlock(&dev->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&dev->lock);
	ep->stopped = stopped;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
net2280_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा net2280_request	*req;
	काष्ठा net2280_ep	*ep;
	काष्ठा net2280		*dev;
	अचिन्हित दीर्घ		flags;
	पूर्णांक ret = 0;

	/* we always require a cpu-view buffer, so that we can
	 * always use pio (as fallback or whatever).
	 */
	ep = container_of(_ep, काष्ठा net2280_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0)) अणु
		pr_err("%s: Invalid ep=%p or ep->desc\n", __func__, _ep);
		वापस -EINVAL;
	पूर्ण
	req = container_of(_req, काष्ठा net2280_request, req);
	अगर (!_req || !_req->complete || !_req->buf ||
				!list_empty(&req->queue)) अणु
		ret = -EINVAL;
		जाओ prपूर्णांक_err;
	पूर्ण
	अगर (_req->length > (~0 & DMA_BYTE_COUNT_MASK)) अणु
		ret = -गलत_तर्क;
		जाओ prपूर्णांक_err;
	पूर्ण
	dev = ep->dev;
	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN) अणु
		ret = -ESHUTDOWN;
		जाओ prपूर्णांक_err;
	पूर्ण

	/* FIXME implement PIO fallback क्रम ZLPs with DMA */
	अगर (ep->dma && _req->length == 0) अणु
		ret = -EOPNOTSUPP;
		जाओ prपूर्णांक_err;
	पूर्ण

	/* set up dma mapping in हाल the caller didn't */
	अगर (ep->dma) अणु
		ret = usb_gadget_map_request(&dev->gadget, _req,
				ep->is_in);
		अगर (ret)
			जाओ prपूर्णांक_err;
	पूर्ण

	ep_vdbg(dev, "%s queue req %p, len %d buf %p\n",
			_ep->name, _req, _req->length, _req->buf);

	spin_lock_irqsave(&dev->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	/* kickstart this i/o queue? */
	अगर  (list_empty(&ep->queue) && !ep->stopped &&
		!((dev->quirks & PLX_PCIE) && ep->dma &&
		  (पढ़ोl(&ep->regs->ep_rsp) & BIT(CLEAR_ENDPOINT_HALT)))) अणु

		/* use DMA अगर the endpoपूर्णांक supports it, अन्यथा pio */
		अगर (ep->dma)
			start_dma(ep, req);
		अन्यथा अणु
			/* maybe there's no control data, just status ack */
			अगर (ep->num == 0 && _req->length == 0) अणु
				allow_status(ep);
				करोne(ep, req, 0);
				ep_vdbg(dev, "%s status ack\n", ep->ep.name);
				जाओ करोne;
			पूर्ण

			/* PIO ... stuff the fअगरo, or unblock it.  */
			अगर (ep->is_in)
				ग_लिखो_fअगरo(ep, _req);
			अन्यथा अणु
				u32	s;

				/* OUT FIFO might have packet(s) buffered */
				s = पढ़ोl(&ep->regs->ep_stat);
				अगर ((s & BIT(FIFO_EMPTY)) == 0) अणु
					/* note:  _req->लघु_not_ok is
					 * ignored here since PIO _always_
					 * stops queue advance here, and
					 * _req->status करोesn't change क्रम
					 * लघु पढ़ोs (only _req->actual)
					 */
					अगर (पढ़ो_fअगरo(ep, req) &&
							ep->num == 0) अणु
						करोne(ep, req, 0);
						allow_status(ep);
						/* करोn't queue it */
						req = शून्य;
					पूर्ण अन्यथा अगर (पढ़ो_fअगरo(ep, req) &&
							ep->num != 0) अणु
						करोne(ep, req, 0);
						req = शून्य;
					पूर्ण अन्यथा
						s = पढ़ोl(&ep->regs->ep_stat);
				पूर्ण

				/* करोn't NAK, let the fअगरo fill */
				अगर (req && (s & BIT(NAK_OUT_PACKETS)))
					ग_लिखोl(BIT(CLEAR_NAK_OUT_PACKETS),
							&ep->regs->ep_rsp);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (ep->dma) अणु
		पूर्णांक	valid = 1;

		अगर (ep->is_in) अणु
			पूर्णांक	expect;

			/* preventing magic zlps is per-engine state, not
			 * per-transfer; irq logic must recover hiccups.
			 */
			expect = likely(req->req.zero ||
				(req->req.length % ep->ep.maxpacket));
			अगर (expect != ep->in_fअगरo_validate)
				valid = 0;
		पूर्ण
		queue_dma(ep, req, valid);

	पूर्ण /* अन्यथा the irq handler advances the queue. */

	ep->responded = 1;
	अगर (req)
		list_add_tail(&req->queue, &ep->queue);
करोne:
	spin_unlock_irqrestore(&dev->lock, flags);

	/* pci ग_लिखोs may still be posted */
	वापस ret;

prपूर्णांक_err:
	dev_err(&ep->dev->pdev->dev, "%s: error=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
dma_करोne(काष्ठा net2280_ep *ep,	काष्ठा net2280_request *req, u32 dmacount,
		पूर्णांक status)
अणु
	req->req.actual = req->req.length - (DMA_BYTE_COUNT_MASK & dmacount);
	करोne(ep, req, status);
पूर्ण

अटल पूर्णांक scan_dma_completions(काष्ठा net2280_ep *ep)
अणु
	पूर्णांक num_completed = 0;

	/* only look at descriptors that were "naturally" retired,
	 * so fअगरo and list head state won't matter
	 */
	जबतक (!list_empty(&ep->queue)) अणु
		काष्ठा net2280_request	*req;
		u32 req_dma_count;

		req = list_entry(ep->queue.next,
				काष्ठा net2280_request, queue);
		अगर (!req->valid)
			अवरोध;
		rmb();
		req_dma_count = le32_to_cpup(&req->td->dmacount);
		अगर ((req_dma_count & BIT(VALID_BIT)) != 0)
			अवरोध;

		/* SHORT_PACKET_TRANSFERRED_INTERRUPT handles "usb-short"
		 * हालs where DMA must be पातed; this code handles
		 * all non-पात DMA completions.
		 */
		अगर (unlikely(req->td->dmadesc == 0)) अणु
			/* paranoia */
			u32 स्थिर ep_dmacount = पढ़ोl(&ep->dma->dmacount);

			अगर (ep_dmacount & DMA_BYTE_COUNT_MASK)
				अवरोध;
			/* single transfer mode */
			dma_करोne(ep, req, req_dma_count, 0);
			num_completed++;
			अवरोध;
		पूर्ण अन्यथा अगर (!ep->is_in &&
			   (req->req.length % ep->ep.maxpacket) &&
			   !(ep->dev->quirks & PLX_PCIE)) अणु

			u32 स्थिर ep_stat = पढ़ोl(&ep->regs->ep_stat);
			/* AVOID TROUBLE HERE by not issuing लघु पढ़ोs from
			 * your gadget driver.  That helps aव्योमs errata 0121,
			 * 0122, and 0124; not all हालs trigger the warning.
			 */
			अगर ((ep_stat & BIT(NAK_OUT_PACKETS)) == 0) अणु
				ep_warn(ep->dev, "%s lost packet sync!\n",
						ep->ep.name);
				req->req.status = -EOVERFLOW;
			पूर्ण अन्यथा अणु
				u32 स्थिर ep_avail = पढ़ोl(&ep->regs->ep_avail);
				अगर (ep_avail) अणु
					/* fअगरo माला_लो flushed later */
					ep->out_overflow = 1;
					ep_dbg(ep->dev,
						"%s dma, discard %d len %d\n",
						ep->ep.name, ep_avail,
						req->req.length);
					req->req.status = -EOVERFLOW;
				पूर्ण
			पूर्ण
		पूर्ण
		dma_करोne(ep, req, req_dma_count, 0);
		num_completed++;
	पूर्ण

	वापस num_completed;
पूर्ण

अटल व्योम restart_dma(काष्ठा net2280_ep *ep)
अणु
	काष्ठा net2280_request	*req;

	अगर (ep->stopped)
		वापस;
	req = list_entry(ep->queue.next, काष्ठा net2280_request, queue);

	start_dma(ep, req);
पूर्ण

अटल व्योम पात_dma(काष्ठा net2280_ep *ep)
अणु
	/* पात the current transfer */
	अगर (likely(!list_empty(&ep->queue))) अणु
		/* FIXME work around errata 0121, 0122, 0124 */
		ग_लिखोl(BIT(DMA_ABORT), &ep->dma->dmastat);
		spin_stop_dma(ep->dma);
	पूर्ण अन्यथा
		stop_dma(ep->dma);
	scan_dma_completions(ep);
पूर्ण

/* dequeue ALL requests */
अटल व्योम nuke(काष्ठा net2280_ep *ep)
अणु
	काष्ठा net2280_request	*req;

	/* called with spinlock held */
	ep->stopped = 1;
	अगर (ep->dma)
		पात_dma(ep);
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next,
				काष्ठा net2280_request,
				queue);
		करोne(ep, req, -ESHUTDOWN);
	पूर्ण
पूर्ण

/* dequeue JUST ONE request */
अटल पूर्णांक net2280_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा net2280_ep	*ep;
	काष्ठा net2280_request	*req;
	अचिन्हित दीर्घ		flags;
	u32			dmactl;
	पूर्णांक			stopped;

	ep = container_of(_ep, काष्ठा net2280_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0) || !_req) अणु
		pr_err("%s: Invalid ep=%p or ep->desc or req=%p\n",
						__func__, _ep, _req);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&ep->dev->lock, flags);
	stopped = ep->stopped;

	/* quiesce dma जबतक we patch the queue */
	dmactl = 0;
	ep->stopped = 1;
	अगर (ep->dma) अणु
		dmactl = पढ़ोl(&ep->dma->dmactl);
		/* WARNING erratum 0127 may kick in ... */
		stop_dma(ep->dma);
		scan_dma_completions(ep);
	पूर्ण

	/* make sure it's still queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		ep->stopped = stopped;
		spin_unlock_irqrestore(&ep->dev->lock, flags);
		ep_dbg(ep->dev, "%s: Request mismatch\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* queue head may be partially complete. */
	अगर (ep->queue.next == &req->queue) अणु
		अगर (ep->dma) अणु
			ep_dbg(ep->dev, "unlink (%s) dma\n", _ep->name);
			_req->status = -ECONNRESET;
			पात_dma(ep);
			अगर (likely(ep->queue.next == &req->queue)) अणु
				/* NOTE: misreports single-transfer mode*/
				req->td->dmacount = 0;	/* invalidate */
				dma_करोne(ep, req,
					पढ़ोl(&ep->dma->dmacount),
					-ECONNRESET);
			पूर्ण
		पूर्ण अन्यथा अणु
			ep_dbg(ep->dev, "unlink (%s) pio\n", _ep->name);
			करोne(ep, req, -ECONNRESET);
		पूर्ण
		req = शून्य;
	पूर्ण

	अगर (req)
		करोne(ep, req, -ECONNRESET);
	ep->stopped = stopped;

	अगर (ep->dma) अणु
		/* turn off dma on inactive queues */
		अगर (list_empty(&ep->queue))
			stop_dma(ep->dma);
		अन्यथा अगर (!ep->stopped) अणु
			/* resume current request, or start new one */
			अगर (req)
				ग_लिखोl(dmactl, &ep->dma->dmactl);
			अन्यथा
				start_dma(ep, list_entry(ep->queue.next,
					काष्ठा net2280_request, queue));
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&ep->dev->lock, flags);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक net2280_fअगरo_status(काष्ठा usb_ep *_ep);

अटल पूर्णांक
net2280_set_halt_and_wedge(काष्ठा usb_ep *_ep, पूर्णांक value, पूर्णांक wedged)
अणु
	काष्ठा net2280_ep	*ep;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			retval = 0;

	ep = container_of(_ep, काष्ठा net2280_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0)) अणु
		pr_err("%s: Invalid ep=%p or ep->desc\n", __func__, _ep);
		वापस -EINVAL;
	पूर्ण
	अगर (!ep->dev->driver || ep->dev->gadget.speed == USB_SPEED_UNKNOWN) अणु
		retval = -ESHUTDOWN;
		जाओ prपूर्णांक_err;
	पूर्ण
	अगर (ep->desc /* not ep0 */ && (ep->desc->bmAttributes & 0x03)
						== USB_ENDPOINT_XFER_ISOC) अणु
		retval = -EINVAL;
		जाओ prपूर्णांक_err;
	पूर्ण

	spin_lock_irqsave(&ep->dev->lock, flags);
	अगर (!list_empty(&ep->queue)) अणु
		retval = -EAGAIN;
		जाओ prपूर्णांक_unlock;
	पूर्ण अन्यथा अगर (ep->is_in && value && net2280_fअगरo_status(_ep) != 0) अणु
		retval = -EAGAIN;
		जाओ prपूर्णांक_unlock;
	पूर्ण अन्यथा अणु
		ep_vdbg(ep->dev, "%s %s %s\n", _ep->name,
				value ? "set" : "clear",
				wedged ? "wedge" : "halt");
		/* set/clear, then synch memory views with the device */
		अगर (value) अणु
			अगर (ep->num == 0)
				ep->dev->protocol_stall = 1;
			अन्यथा
				set_halt(ep);
			अगर (wedged)
				ep->wedged = 1;
		पूर्ण अन्यथा अणु
			clear_halt(ep);
			अगर (ep->dev->quirks & PLX_PCIE &&
				!list_empty(&ep->queue) && ep->td_dma)
					restart_dma(ep);
			ep->wedged = 0;
		पूर्ण
		(व्योम) पढ़ोl(&ep->regs->ep_rsp);
	पूर्ण
	spin_unlock_irqrestore(&ep->dev->lock, flags);

	वापस retval;

prपूर्णांक_unlock:
	spin_unlock_irqrestore(&ep->dev->lock, flags);
prपूर्णांक_err:
	dev_err(&ep->dev->pdev->dev, "%s: error=%d\n", __func__, retval);
	वापस retval;
पूर्ण

अटल पूर्णांक net2280_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	वापस net2280_set_halt_and_wedge(_ep, value, 0);
पूर्ण

अटल पूर्णांक net2280_set_wedge(काष्ठा usb_ep *_ep)
अणु
	अगर (!_ep || _ep->name == ep0name) अणु
		pr_err("%s: Invalid ep=%p or ep0\n", __func__, _ep);
		वापस -EINVAL;
	पूर्ण
	वापस net2280_set_halt_and_wedge(_ep, 1, 1);
पूर्ण

अटल पूर्णांक net2280_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	काष्ठा net2280_ep	*ep;
	u32			avail;

	ep = container_of(_ep, काष्ठा net2280_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0)) अणु
		pr_err("%s: Invalid ep=%p or ep->desc\n", __func__, _ep);
		वापस -ENODEV;
	पूर्ण
	अगर (!ep->dev->driver || ep->dev->gadget.speed == USB_SPEED_UNKNOWN) अणु
		dev_err(&ep->dev->pdev->dev,
			"%s: Invalid driver=%p or speed=%d\n",
			__func__, ep->dev->driver, ep->dev->gadget.speed);
		वापस -ESHUTDOWN;
	पूर्ण

	avail = पढ़ोl(&ep->regs->ep_avail) & (BIT(12) - 1);
	अगर (avail > ep->fअगरo_size) अणु
		dev_err(&ep->dev->pdev->dev, "%s: Fifo overflow\n", __func__);
		वापस -EOVERFLOW;
	पूर्ण
	अगर (ep->is_in)
		avail = ep->fअगरo_size - avail;
	वापस avail;
पूर्ण

अटल व्योम net2280_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा net2280_ep	*ep;

	ep = container_of(_ep, काष्ठा net2280_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0)) अणु
		pr_err("%s: Invalid ep=%p or ep->desc\n", __func__, _ep);
		वापस;
	पूर्ण
	अगर (!ep->dev->driver || ep->dev->gadget.speed == USB_SPEED_UNKNOWN) अणु
		dev_err(&ep->dev->pdev->dev,
			"%s: Invalid driver=%p or speed=%d\n",
			__func__, ep->dev->driver, ep->dev->gadget.speed);
		वापस;
	पूर्ण

	ग_लिखोl(BIT(FIFO_FLUSH), &ep->regs->ep_stat);
	(व्योम) पढ़ोl(&ep->regs->ep_rsp);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops net2280_ep_ops = अणु
	.enable		= net2280_enable,
	.disable	= net2280_disable,

	.alloc_request	= net2280_alloc_request,
	.मुक्त_request	= net2280_मुक्त_request,

	.queue		= net2280_queue,
	.dequeue	= net2280_dequeue,

	.set_halt	= net2280_set_halt,
	.set_wedge	= net2280_set_wedge,
	.fअगरo_status	= net2280_fअगरo_status,
	.fअगरo_flush	= net2280_fअगरo_flush,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक net2280_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा net2280		*dev;
	अचिन्हित दीर्घ		flags;
	u16			retval;

	अगर (!_gadget)
		वापस -ENODEV;
	dev = container_of(_gadget, काष्ठा net2280, gadget);
	spin_lock_irqsave(&dev->lock, flags);
	retval = get_idx_reg(dev->regs, REG_FRAME) & 0x03ff;
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक net2280_wakeup(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा net2280		*dev;
	u32			पंचांगp;
	अचिन्हित दीर्घ		flags;

	अगर (!_gadget)
		वापस 0;
	dev = container_of(_gadget, काष्ठा net2280, gadget);

	spin_lock_irqsave(&dev->lock, flags);
	पंचांगp = पढ़ोl(&dev->usb->usbctl);
	अगर (पंचांगp & BIT(DEVICE_REMOTE_WAKEUP_ENABLE))
		ग_लिखोl(BIT(GENERATE_RESUME), &dev->usb->usbstat);
	spin_unlock_irqrestore(&dev->lock, flags);

	/* pci ग_लिखोs may still be posted */
	वापस 0;
पूर्ण

अटल पूर्णांक net2280_set_selfघातered(काष्ठा usb_gadget *_gadget, पूर्णांक value)
अणु
	काष्ठा net2280		*dev;
	u32			पंचांगp;
	अचिन्हित दीर्घ		flags;

	अगर (!_gadget)
		वापस 0;
	dev = container_of(_gadget, काष्ठा net2280, gadget);

	spin_lock_irqsave(&dev->lock, flags);
	पंचांगp = पढ़ोl(&dev->usb->usbctl);
	अगर (value) अणु
		पंचांगp |= BIT(SELF_POWERED_STATUS);
		_gadget->is_selfघातered = 1;
	पूर्ण अन्यथा अणु
		पंचांगp &= ~BIT(SELF_POWERED_STATUS);
		_gadget->is_selfघातered = 0;
	पूर्ण
	ग_लिखोl(पंचांगp, &dev->usb->usbctl);
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक net2280_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक is_on)
अणु
	काष्ठा net2280  *dev;
	u32             पंचांगp;
	अचिन्हित दीर्घ   flags;

	अगर (!_gadget)
		वापस -ENODEV;
	dev = container_of(_gadget, काष्ठा net2280, gadget);

	spin_lock_irqsave(&dev->lock, flags);
	पंचांगp = पढ़ोl(&dev->usb->usbctl);
	dev->softconnect = (is_on != 0);
	अगर (is_on) अणु
		ep0_start(dev);
		ग_लिखोl(पंचांगp | BIT(USB_DETECT_ENABLE), &dev->usb->usbctl);
	पूर्ण अन्यथा अणु
		ग_लिखोl(पंचांगp & ~BIT(USB_DETECT_ENABLE), &dev->usb->usbctl);
		stop_activity(dev, शून्य);
	पूर्ण

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा usb_ep *net2280_match_ep(काष्ठा usb_gadget *_gadget,
		काष्ठा usb_endpoपूर्णांक_descriptor *desc,
		काष्ठा usb_ss_ep_comp_descriptor *ep_comp)
अणु
	अक्षर name[8];
	काष्ठा usb_ep *ep;

	अगर (usb_endpoपूर्णांक_type(desc) == USB_ENDPOINT_XFER_INT) अणु
		/* ep-e, ep-f are PIO with only 64 byte fअगरos */
		ep = gadget_find_ep_by_name(_gadget, "ep-e");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
		ep = gadget_find_ep_by_name(_gadget, "ep-f");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
	पूर्ण

	/* USB3380: Only first four endpoपूर्णांकs have DMA channels. Allocate
	 * slower पूर्णांकerrupt endpoपूर्णांकs from PIO hw endpoपूर्णांकs, to allow bulk/isoc
	 * endpoपूर्णांकs use DMA hw endpoपूर्णांकs.
	 */
	अगर (usb_endpoपूर्णांक_type(desc) == USB_ENDPOINT_XFER_INT &&
	    usb_endpoपूर्णांक_dir_in(desc)) अणु
		ep = gadget_find_ep_by_name(_gadget, "ep2in");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
		ep = gadget_find_ep_by_name(_gadget, "ep4in");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_type(desc) == USB_ENDPOINT_XFER_INT &&
		   !usb_endpoपूर्णांक_dir_in(desc)) अणु
		ep = gadget_find_ep_by_name(_gadget, "ep1out");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
		ep = gadget_find_ep_by_name(_gadget, "ep3out");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_type(desc) != USB_ENDPOINT_XFER_BULK &&
		   usb_endpoपूर्णांक_dir_in(desc)) अणु
		ep = gadget_find_ep_by_name(_gadget, "ep1in");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
		ep = gadget_find_ep_by_name(_gadget, "ep3in");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_type(desc) != USB_ENDPOINT_XFER_BULK &&
		   !usb_endpoपूर्णांक_dir_in(desc)) अणु
		ep = gadget_find_ep_by_name(_gadget, "ep2out");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
		ep = gadget_find_ep_by_name(_gadget, "ep4out");
		अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
			वापस ep;
	पूर्ण

	/* USB3380: use same address क्रम usb and hardware endpoपूर्णांकs */
	snम_लिखो(name, माप(name), "ep%d%s", usb_endpoपूर्णांक_num(desc),
			usb_endpoपूर्णांक_dir_in(desc) ? "in" : "out");
	ep = gadget_find_ep_by_name(_gadget, name);
	अगर (ep && usb_gadget_ep_match_desc(_gadget, ep, desc, ep_comp))
		वापस ep;

	वापस शून्य;
पूर्ण

अटल पूर्णांक net2280_start(काष्ठा usb_gadget *_gadget,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक net2280_stop(काष्ठा usb_gadget *_gadget);

अटल स्थिर काष्ठा usb_gadget_ops net2280_ops = अणु
	.get_frame	= net2280_get_frame,
	.wakeup		= net2280_wakeup,
	.set_selfघातered = net2280_set_selfघातered,
	.pullup		= net2280_pullup,
	.udc_start	= net2280_start,
	.udc_stop	= net2280_stop,
	.match_ep	= net2280_match_ep,
पूर्ण;

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_USB_GADGET_DEBUG_खाताS

/* FIXME move these पूर्णांकo procfs, and use seq_file.
 * Sysfs _still_ करोesn't behave क्रम arbitrarily sized files,
 * and also करोesn't help products using this with 2.4 kernels.
 */

/* "function" sysfs attribute */
अटल sमाप_प्रकार function_show(काष्ठा device *_dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा net2280	*dev = dev_get_drvdata(_dev);

	अगर (!dev->driver || !dev->driver->function ||
			म_माप(dev->driver->function) > PAGE_SIZE)
		वापस 0;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", dev->driver->function);
पूर्ण
अटल DEVICE_ATTR_RO(function);

अटल sमाप_प्रकार रेजिस्टरs_show(काष्ठा device *_dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net2280		*dev;
	अक्षर			*next;
	अचिन्हित		size, t;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			i;
	u32			t1, t2;
	स्थिर अक्षर		*s;

	dev = dev_get_drvdata(_dev);
	next = buf;
	size = PAGE_SIZE;
	spin_lock_irqsave(&dev->lock, flags);

	अगर (dev->driver)
		s = dev->driver->driver.name;
	अन्यथा
		s = "(none)";

	/* Main Control Registers */
	t = scnम_लिखो(next, size, "%s version " DRIVER_VERSION
			", chiprev %04x\n\n"
			"devinit %03x fifoctl %08x gadget '%s'\n"
			"pci irqenb0 %02x irqenb1 %08x "
			"irqstat0 %04x irqstat1 %08x\n",
			driver_name, dev->chiprev,
			पढ़ोl(&dev->regs->devinit),
			पढ़ोl(&dev->regs->fअगरoctl),
			s,
			पढ़ोl(&dev->regs->pciirqenb0),
			पढ़ोl(&dev->regs->pciirqenb1),
			पढ़ोl(&dev->regs->irqstat0),
			पढ़ोl(&dev->regs->irqstat1));
	size -= t;
	next += t;

	/* USB Control Registers */
	t1 = पढ़ोl(&dev->usb->usbctl);
	t2 = पढ़ोl(&dev->usb->usbstat);
	अगर (t1 & BIT(VBUS_PIN)) अणु
		अगर (t2 & BIT(HIGH_SPEED))
			s = "high speed";
		अन्यथा अगर (dev->gadget.speed == USB_SPEED_UNKNOWN)
			s = "powered";
		अन्यथा
			s = "full speed";
		/* full speed bit (6) not working?? */
	पूर्ण अन्यथा
			s = "not attached";
	t = scnम_लिखो(next, size,
			"stdrsp %08x usbctl %08x usbstat %08x "
				"addr 0x%02x (%s)\n",
			पढ़ोl(&dev->usb->stdrsp), t1, t2,
			पढ़ोl(&dev->usb->ouraddr), s);
	size -= t;
	next += t;

	/* PCI Master Control Registers */

	/* DMA Control Registers */

	/* Configurable EP Control Registers */
	क्रम (i = 0; i < dev->n_ep; i++) अणु
		काष्ठा net2280_ep	*ep;

		ep = &dev->ep[i];
		अगर (i && !ep->desc)
			जारी;

		t1 = पढ़ोl(&ep->cfg->ep_cfg);
		t2 = पढ़ोl(&ep->regs->ep_rsp) & 0xff;
		t = scnम_लिखो(next, size,
				"\n%s\tcfg %05x rsp (%02x) %s%s%s%s%s%s%s%s"
					"irqenb %02x\n",
				ep->ep.name, t1, t2,
				(t2 & BIT(CLEAR_NAK_OUT_PACKETS))
					? "NAK " : "",
				(t2 & BIT(CLEAR_EP_HIDE_STATUS_PHASE))
					? "hide " : "",
				(t2 & BIT(CLEAR_EP_FORCE_CRC_ERROR))
					? "CRC " : "",
				(t2 & BIT(CLEAR_INTERRUPT_MODE))
					? "interrupt " : "",
				(t2 & BIT(CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE))
					? "status " : "",
				(t2 & BIT(CLEAR_NAK_OUT_PACKETS_MODE))
					? "NAKmode " : "",
				(t2 & BIT(CLEAR_ENDPOINT_TOGGLE))
					? "DATA1 " : "DATA0 ",
				(t2 & BIT(CLEAR_ENDPOINT_HALT))
					? "HALT " : "",
				पढ़ोl(&ep->regs->ep_irqenb));
		size -= t;
		next += t;

		t = scnम_लिखो(next, size,
				"\tstat %08x avail %04x "
				"(ep%d%s-%s)%s\n",
				पढ़ोl(&ep->regs->ep_stat),
				पढ़ोl(&ep->regs->ep_avail),
				t1 & 0x0f, सूची_STRING(t1),
				type_string(t1 >> 8),
				ep->stopped ? "*" : "");
		size -= t;
		next += t;

		अगर (!ep->dma)
			जारी;

		t = scnम_लिखो(next, size,
				"  dma\tctl %08x stat %08x count %08x\n"
				"\taddr %08x desc %08x\n",
				पढ़ोl(&ep->dma->dmactl),
				पढ़ोl(&ep->dma->dmastat),
				पढ़ोl(&ep->dma->dmacount),
				पढ़ोl(&ep->dma->dmaaddr),
				पढ़ोl(&ep->dma->dmadesc));
		size -= t;
		next += t;

	पूर्ण

	/* Indexed Registers (none yet) */

	/* Statistics */
	t = scnम_लिखो(next, size, "\nirqs:  ");
	size -= t;
	next += t;
	क्रम (i = 0; i < dev->n_ep; i++) अणु
		काष्ठा net2280_ep	*ep;

		ep = &dev->ep[i];
		अगर (i && !ep->irqs)
			जारी;
		t = scnम_लिखो(next, size, " %s/%lu", ep->ep.name, ep->irqs);
		size -= t;
		next += t;

	पूर्ण
	t = scnम_लिखो(next, size, "\n");
	size -= t;
	next += t;

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस PAGE_SIZE - size;
पूर्ण
अटल DEVICE_ATTR_RO(रेजिस्टरs);

अटल sमाप_प्रकार queues_show(काष्ठा device *_dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा net2280		*dev;
	अक्षर			*next;
	अचिन्हित		size;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			i;

	dev = dev_get_drvdata(_dev);
	next = buf;
	size = PAGE_SIZE;
	spin_lock_irqsave(&dev->lock, flags);

	क्रम (i = 0; i < dev->n_ep; i++) अणु
		काष्ठा net2280_ep		*ep = &dev->ep[i];
		काष्ठा net2280_request		*req;
		पूर्णांक				t;

		अगर (i != 0) अणु
			स्थिर काष्ठा usb_endpoपूर्णांक_descriptor	*d;

			d = ep->desc;
			अगर (!d)
				जारी;
			t = d->bEndpoपूर्णांकAddress;
			t = scnम_लिखो(next, size,
				"\n%s (ep%d%s-%s) max %04x %s fifo %d\n",
				ep->ep.name, t & USB_ENDPOINT_NUMBER_MASK,
				(t & USB_सूची_IN) ? "in" : "out",
				type_string(d->bmAttributes),
				usb_endpoपूर्णांक_maxp(d),
				ep->dma ? "dma" : "pio", ep->fअगरo_size
				);
		पूर्ण अन्यथा /* ep0 should only have one transfer queued */
			t = scnम_लिखो(next, size, "ep0 max 64 pio %s\n",
					ep->is_in ? "in" : "out");
		अगर (t <= 0 || t > size)
			जाओ करोne;
		size -= t;
		next += t;

		अगर (list_empty(&ep->queue)) अणु
			t = scnम_लिखो(next, size, "\t(nothing queued)\n");
			अगर (t <= 0 || t > size)
				जाओ करोne;
			size -= t;
			next += t;
			जारी;
		पूर्ण
		list_क्रम_each_entry(req, &ep->queue, queue) अणु
			अगर (ep->dma && req->td_dma == पढ़ोl(&ep->dma->dmadesc))
				t = scnम_लिखो(next, size,
					"\treq %p len %d/%d "
					"buf %p (dmacount %08x)\n",
					&req->req, req->req.actual,
					req->req.length, req->req.buf,
					पढ़ोl(&ep->dma->dmacount));
			अन्यथा
				t = scnम_लिखो(next, size,
					"\treq %p len %d/%d buf %p\n",
					&req->req, req->req.actual,
					req->req.length, req->req.buf);
			अगर (t <= 0 || t > size)
				जाओ करोne;
			size -= t;
			next += t;

			अगर (ep->dma) अणु
				काष्ठा net2280_dma	*td;

				td = req->td;
				t = scnम_लिखो(next, size, "\t    td %08x "
					" count %08x buf %08x desc %08x\n",
					(u32) req->td_dma,
					le32_to_cpu(td->dmacount),
					le32_to_cpu(td->dmaaddr),
					le32_to_cpu(td->dmadesc));
				अगर (t <= 0 || t > size)
					जाओ करोne;
				size -= t;
				next += t;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस PAGE_SIZE - size;
पूर्ण
अटल DEVICE_ATTR_RO(queues);


#अन्यथा

#घोषणा device_create_file(a, b)	(0)
#घोषणा device_हटाओ_file(a, b)	करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/* another driver-specअगरic mode might be a request type करोing dma
 * to/from another device fअगरo instead of to/from memory.
 */

अटल व्योम set_fअगरo_mode(काष्ठा net2280 *dev, पूर्णांक mode)
अणु
	/* keeping high bits preserves BAR2 */
	ग_लिखोl((0xffff << PCI_BASE2_RANGE) | mode, &dev->regs->fअगरoctl);

	/* always ep-अणुa,b,e,fपूर्ण ... maybe not ep-c or ep-d */
	INIT_LIST_HEAD(&dev->gadget.ep_list);
	list_add_tail(&dev->ep[1].ep.ep_list, &dev->gadget.ep_list);
	list_add_tail(&dev->ep[2].ep.ep_list, &dev->gadget.ep_list);
	चयन (mode) अणु
	हाल 0:
		list_add_tail(&dev->ep[3].ep.ep_list, &dev->gadget.ep_list);
		list_add_tail(&dev->ep[4].ep.ep_list, &dev->gadget.ep_list);
		dev->ep[1].fअगरo_size = dev->ep[2].fअगरo_size = 1024;
		अवरोध;
	हाल 1:
		dev->ep[1].fअगरo_size = dev->ep[2].fअगरo_size = 2048;
		अवरोध;
	हाल 2:
		list_add_tail(&dev->ep[3].ep.ep_list, &dev->gadget.ep_list);
		dev->ep[1].fअगरo_size = 2048;
		dev->ep[2].fअगरo_size = 1024;
		अवरोध;
	पूर्ण
	/* fअगरo sizes क्रम ep0, ep-c, ep-d, ep-e, and ep-f never change */
	list_add_tail(&dev->ep[5].ep.ep_list, &dev->gadget.ep_list);
	list_add_tail(&dev->ep[6].ep.ep_list, &dev->gadget.ep_list);
पूर्ण

अटल व्योम defect7374_disable_data_eps(काष्ठा net2280 *dev)
अणु
	/*
	 * For Defect 7374, disable data EPs (and more):
	 *  - This phase unकरोes the earlier phase of the Defect 7374 workaround,
	 *    returing ep regs back to normal.
	 */
	काष्ठा net2280_ep *ep;
	पूर्णांक i;
	अचिन्हित अक्षर ep_sel;
	u32 पंचांगp_reg;

	क्रम (i = 1; i < 5; i++) अणु
		ep = &dev->ep[i];
		ग_लिखोl(i, &ep->cfg->ep_cfg);
	पूर्ण

	/* CSROUT, CSRIN, PCIOUT, PCIIN, STATIN, RCIN */
	क्रम (i = 0; i < 6; i++)
		ग_लिखोl(0, &dev->dep[i].dep_cfg);

	क्रम (ep_sel = 0; ep_sel <= 21; ep_sel++) अणु
		/* Select an endpoपूर्णांक क्रम subsequent operations: */
		पंचांगp_reg = पढ़ोl(&dev->plregs->pl_ep_ctrl);
		ग_लिखोl(((पंचांगp_reg & ~0x1f) | ep_sel), &dev->plregs->pl_ep_ctrl);

		अगर (ep_sel < 2 || (ep_sel > 9 && ep_sel < 14) ||
					ep_sel == 18 || ep_sel == 20)
			जारी;

		/* Change settings on some selected endpoपूर्णांकs */
		पंचांगp_reg = पढ़ोl(&dev->plregs->pl_ep_cfg_4);
		पंचांगp_reg &= ~BIT(NON_CTRL_IN_TOLERATE_BAD_सूची);
		ग_लिखोl(पंचांगp_reg, &dev->plregs->pl_ep_cfg_4);
		पंचांगp_reg = पढ़ोl(&dev->plregs->pl_ep_ctrl);
		पंचांगp_reg |= BIT(EP_INITIALIZED);
		ग_लिखोl(पंचांगp_reg, &dev->plregs->pl_ep_ctrl);
	पूर्ण
पूर्ण

अटल व्योम defect7374_enable_data_eps_zero(काष्ठा net2280 *dev)
अणु
	u32 पंचांगp = 0, पंचांगp_reg;
	u32 scratch;
	पूर्णांक i;
	अचिन्हित अक्षर ep_sel;

	scratch = get_idx_reg(dev->regs, SCRATCH);

	WARN_ON((scratch & (0xf << DEFECT7374_FSM_FIELD))
		== DEFECT7374_FSM_SS_CONTROL_READ);

	scratch &= ~(0xf << DEFECT7374_FSM_FIELD);

	ep_warn(dev, "Operate Defect 7374 workaround soft this time");
	ep_warn(dev, "It will operate on cold-reboot and SS connect");

	/*GPEPs:*/
	पंचांगp = ((0 << ENDPOINT_NUMBER) | BIT(ENDPOINT_सूचीECTION) |
			(2 << OUT_ENDPOINT_TYPE) | (2 << IN_ENDPOINT_TYPE) |
			((dev->enhanced_mode) ?
			 BIT(OUT_ENDPOINT_ENABLE) | BIT(IN_ENDPOINT_ENABLE) :
			 BIT(ENDPOINT_ENABLE)));

	क्रम (i = 1; i < 5; i++)
		ग_लिखोl(पंचांगp, &dev->ep[i].cfg->ep_cfg);

	/* CSRIN, PCIIN, STATIN, RCIN*/
	पंचांगp = ((0 << ENDPOINT_NUMBER) | BIT(ENDPOINT_ENABLE));
	ग_लिखोl(पंचांगp, &dev->dep[1].dep_cfg);
	ग_लिखोl(पंचांगp, &dev->dep[3].dep_cfg);
	ग_लिखोl(पंचांगp, &dev->dep[4].dep_cfg);
	ग_लिखोl(पंचांगp, &dev->dep[5].dep_cfg);

	/*Implemented क्रम development and debug.
	 * Can be refined/tuned later.*/
	क्रम (ep_sel = 0; ep_sel <= 21; ep_sel++) अणु
		/* Select an endpoपूर्णांक क्रम subsequent operations: */
		पंचांगp_reg = पढ़ोl(&dev->plregs->pl_ep_ctrl);
		ग_लिखोl(((पंचांगp_reg & ~0x1f) | ep_sel),
				&dev->plregs->pl_ep_ctrl);

		अगर (ep_sel == 1) अणु
			पंचांगp =
				(पढ़ोl(&dev->plregs->pl_ep_ctrl) |
				 BIT(CLEAR_ACK_ERROR_CODE) | 0);
			ग_लिखोl(पंचांगp, &dev->plregs->pl_ep_ctrl);
			जारी;
		पूर्ण

		अगर (ep_sel == 0 || (ep_sel > 9 && ep_sel < 14) ||
				ep_sel == 18  || ep_sel == 20)
			जारी;

		पंचांगp = (पढ़ोl(&dev->plregs->pl_ep_cfg_4) |
				BIT(NON_CTRL_IN_TOLERATE_BAD_सूची) | 0);
		ग_लिखोl(पंचांगp, &dev->plregs->pl_ep_cfg_4);

		पंचांगp = पढ़ोl(&dev->plregs->pl_ep_ctrl) &
			~BIT(EP_INITIALIZED);
		ग_लिखोl(पंचांगp, &dev->plregs->pl_ep_ctrl);

	पूर्ण

	/* Set FSM to focus on the first Control Read:
	 * - Tip: Connection speed is known upon the first
	 * setup request.*/
	scratch |= DEFECT7374_FSM_WAITING_FOR_CONTROL_READ;
	set_idx_reg(dev->regs, SCRATCH, scratch);

पूर्ण

/* keeping it simple:
 * - one bus driver, initted first;
 * - one function driver, initted second
 *
 * most of the work to support multiple net2280 controllers would
 * be to associate this gadget driver (yes?) with all of them, or
 * perhaps to bind specअगरic drivers to specअगरic devices.
 */

अटल व्योम usb_reset_228x(काष्ठा net2280 *dev)
अणु
	u32	पंचांगp;

	dev->gadget.speed = USB_SPEED_UNKNOWN;
	(व्योम) पढ़ोl(&dev->usb->usbctl);

	net2280_led_init(dev);

	/* disable स्वतःmatic responses, and irqs */
	ग_लिखोl(0, &dev->usb->stdrsp);
	ग_लिखोl(0, &dev->regs->pciirqenb0);
	ग_लिखोl(0, &dev->regs->pciirqenb1);

	/* clear old dma and irq state */
	क्रम (पंचांगp = 0; पंचांगp < 4; पंचांगp++) अणु
		काष्ठा net2280_ep       *ep = &dev->ep[पंचांगp + 1];
		अगर (ep->dma)
			पात_dma(ep);
	पूर्ण

	ग_लिखोl(~0, &dev->regs->irqstat0),
	ग_लिखोl(~(u32)BIT(SUSPEND_REQUEST_INTERRUPT), &dev->regs->irqstat1),

	/* reset, and enable pci */
	पंचांगp = पढ़ोl(&dev->regs->devinit) |
		BIT(PCI_ENABLE) |
		BIT(FIFO_SOFT_RESET) |
		BIT(USB_SOFT_RESET) |
		BIT(M8051_RESET);
	ग_लिखोl(पंचांगp, &dev->regs->devinit);

	/* standard fअगरo and endpoपूर्णांक allocations */
	set_fअगरo_mode(dev, (fअगरo_mode <= 2) ? fअगरo_mode : 0);
पूर्ण

अटल व्योम usb_reset_338x(काष्ठा net2280 *dev)
अणु
	u32 पंचांगp;

	dev->gadget.speed = USB_SPEED_UNKNOWN;
	(व्योम)पढ़ोl(&dev->usb->usbctl);

	net2280_led_init(dev);

	अगर (dev->bug7734_patched) अणु
		/* disable स्वतःmatic responses, and irqs */
		ग_लिखोl(0, &dev->usb->stdrsp);
		ग_लिखोl(0, &dev->regs->pciirqenb0);
		ग_लिखोl(0, &dev->regs->pciirqenb1);
	पूर्ण

	/* clear old dma and irq state */
	क्रम (पंचांगp = 0; पंचांगp < 4; पंचांगp++) अणु
		काष्ठा net2280_ep *ep = &dev->ep[पंचांगp + 1];
		काष्ठा net2280_dma_regs __iomem *dma;

		अगर (ep->dma) अणु
			पात_dma(ep);
		पूर्ण अन्यथा अणु
			dma = &dev->dma[पंचांगp];
			ग_लिखोl(BIT(DMA_ABORT), &dma->dmastat);
			ग_लिखोl(0, &dma->dmactl);
		पूर्ण
	पूर्ण

	ग_लिखोl(~0, &dev->regs->irqstat0), ग_लिखोl(~0, &dev->regs->irqstat1);

	अगर (dev->bug7734_patched) अणु
		/* reset, and enable pci */
		पंचांगp = पढ़ोl(&dev->regs->devinit) |
		    BIT(PCI_ENABLE) |
		    BIT(FIFO_SOFT_RESET) |
		    BIT(USB_SOFT_RESET) |
		    BIT(M8051_RESET);

		ग_लिखोl(पंचांगp, &dev->regs->devinit);
	पूर्ण

	/* always ep-अणु1,2,3,4पूर्ण ... maybe not ep-3 or ep-4 */
	INIT_LIST_HEAD(&dev->gadget.ep_list);

	क्रम (पंचांगp = 1; पंचांगp < dev->n_ep; पंचांगp++)
		list_add_tail(&dev->ep[पंचांगp].ep.ep_list, &dev->gadget.ep_list);

पूर्ण

अटल व्योम usb_reset(काष्ठा net2280 *dev)
अणु
	अगर (dev->quirks & PLX_LEGACY)
		वापस usb_reset_228x(dev);
	वापस usb_reset_338x(dev);
पूर्ण

अटल व्योम usb_reinit_228x(काष्ठा net2280 *dev)
अणु
	u32	पंचांगp;

	/* basic endpoपूर्णांक init */
	क्रम (पंचांगp = 0; पंचांगp < 7; पंचांगp++) अणु
		काष्ठा net2280_ep	*ep = &dev->ep[पंचांगp];

		ep->ep.name = ep_info_dft[पंचांगp].name;
		ep->ep.caps = ep_info_dft[पंचांगp].caps;
		ep->dev = dev;
		ep->num = पंचांगp;

		अगर (पंचांगp > 0 && पंचांगp <= 4) अणु
			ep->fअगरo_size = 1024;
			ep->dma = &dev->dma[पंचांगp - 1];
		पूर्ण अन्यथा
			ep->fअगरo_size = 64;
		ep->regs = &dev->epregs[पंचांगp];
		ep->cfg = &dev->epregs[पंचांगp];
		ep_reset_228x(dev->regs, ep);
	पूर्ण
	usb_ep_set_maxpacket_limit(&dev->ep[0].ep, 64);
	usb_ep_set_maxpacket_limit(&dev->ep[5].ep, 64);
	usb_ep_set_maxpacket_limit(&dev->ep[6].ep, 64);

	dev->gadget.ep0 = &dev->ep[0].ep;
	dev->ep[0].stopped = 0;
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);

	/* we want to prevent lowlevel/insecure access from the USB host,
	 * but erratum 0119 means this enable bit is ignored
	 */
	क्रम (पंचांगp = 0; पंचांगp < 5; पंचांगp++)
		ग_लिखोl(EP_DONTUSE, &dev->dep[पंचांगp].dep_cfg);
पूर्ण

अटल व्योम usb_reinit_338x(काष्ठा net2280 *dev)
अणु
	पूर्णांक i;
	u32 पंचांगp, val;
	अटल स्थिर u32 ne[9] = अणु 0, 1, 2, 3, 4, 1, 2, 3, 4 पूर्ण;
	अटल स्थिर u32 ep_reg_addr[9] = अणु 0x00, 0xC0, 0x00, 0xC0, 0x00,
						0x00, 0xC0, 0x00, 0xC0 पूर्ण;

	/* basic endpoपूर्णांक init */
	क्रम (i = 0; i < dev->n_ep; i++) अणु
		काष्ठा net2280_ep *ep = &dev->ep[i];

		ep->ep.name = dev->enhanced_mode ? ep_info_adv[i].name :
						   ep_info_dft[i].name;
		ep->ep.caps = dev->enhanced_mode ? ep_info_adv[i].caps :
						   ep_info_dft[i].caps;
		ep->dev = dev;
		ep->num = i;

		अगर (i > 0 && i <= 4)
			ep->dma = &dev->dma[i - 1];

		अगर (dev->enhanced_mode) अणु
			ep->cfg = &dev->epregs[ne[i]];
			/*
			 * Set USB endpoपूर्णांक number, hardware allows same number
			 * in both directions.
			 */
			 अगर (i > 0 && i < 5)
				ग_लिखोl(ne[i], &ep->cfg->ep_cfg);
			ep->regs = (काष्ठा net2280_ep_regs __iomem *)
				(((व्योम __iomem *)&dev->epregs[ne[i]]) +
				ep_reg_addr[i]);
		पूर्ण अन्यथा अणु
			ep->cfg = &dev->epregs[i];
			ep->regs = &dev->epregs[i];
		पूर्ण

		ep->fअगरo_size = (i != 0) ? 2048 : 512;

		ep_reset_338x(dev->regs, ep);
	पूर्ण
	usb_ep_set_maxpacket_limit(&dev->ep[0].ep, 512);

	dev->gadget.ep0 = &dev->ep[0].ep;
	dev->ep[0].stopped = 0;

	/* Link layer set up */
	अगर (dev->bug7734_patched) अणु
		पंचांगp = पढ़ोl(&dev->usb_ext->usbctl2) &
		    ~(BIT(U1_ENABLE) | BIT(U2_ENABLE) | BIT(LTM_ENABLE));
		ग_लिखोl(पंचांगp, &dev->usb_ext->usbctl2);
	पूर्ण

	/* Hardware Defect and Workaround */
	val = पढ़ोl(&dev->llregs->ll_lfps_5);
	val &= ~(0xf << TIMER_LFPS_6US);
	val |= 0x5 << TIMER_LFPS_6US;
	ग_लिखोl(val, &dev->llregs->ll_lfps_5);

	val = पढ़ोl(&dev->llregs->ll_lfps_6);
	val &= ~(0xffff << TIMER_LFPS_80US);
	val |= 0x0100 << TIMER_LFPS_80US;
	ग_लिखोl(val, &dev->llregs->ll_lfps_6);

	/*
	 * AA_AB Errata. Issue 4. Workaround क्रम SuperSpeed USB
	 * Hot Reset Exit Handshake may Fail in Specअगरic Case using
	 * Default Register Settings. Workaround क्रम Enumeration test.
	 */
	val = पढ़ोl(&dev->llregs->ll_tsn_counters_2);
	val &= ~(0x1f << HOT_TX_NORESET_TS2);
	val |= 0x10 << HOT_TX_NORESET_TS2;
	ग_लिखोl(val, &dev->llregs->ll_tsn_counters_2);

	val = पढ़ोl(&dev->llregs->ll_tsn_counters_3);
	val &= ~(0x1f << HOT_RX_RESET_TS2);
	val |= 0x3 << HOT_RX_RESET_TS2;
	ग_लिखोl(val, &dev->llregs->ll_tsn_counters_3);

	/*
	 * AB errata. Errata 11. Workaround क्रम Default Duration of LFPS
	 * Handshake Signaling क्रम Device-Initiated U1 Exit is too लघु.
	 * Without this, various क्रमागतeration failures observed with
	 * modern superspeed hosts.
	 */
	val = पढ़ोl(&dev->llregs->ll_lfps_समयrs_2);
	ग_लिखोl((val & 0xffff0000) | LFPS_TIMERS_2_WORKAROUND_VALUE,
	       &dev->llregs->ll_lfps_समयrs_2);

	/*
	 * Set Recovery Idle to Recover bit:
	 * - On SS connections, setting Recovery Idle to Recover Fmw improves
	 *   link robustness with various hosts and hubs.
	 * - It is safe to set क्रम all connection speeds; all chip revisions.
	 * - R-M-W to leave other bits undisturbed.
	 * - Reference PLX TT-7372
	*/
	val = पढ़ोl(&dev->llregs->ll_tsn_chicken_bit);
	val |= BIT(RECOVERY_IDLE_TO_RECOVER_FMW);
	ग_लिखोl(val, &dev->llregs->ll_tsn_chicken_bit);

	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);

	/* disable dedicated endpoपूर्णांकs */
	ग_लिखोl(0x0D, &dev->dep[0].dep_cfg);
	ग_लिखोl(0x0D, &dev->dep[1].dep_cfg);
	ग_लिखोl(0x0E, &dev->dep[2].dep_cfg);
	ग_लिखोl(0x0E, &dev->dep[3].dep_cfg);
	ग_लिखोl(0x0F, &dev->dep[4].dep_cfg);
	ग_लिखोl(0x0C, &dev->dep[5].dep_cfg);
पूर्ण

अटल व्योम usb_reinit(काष्ठा net2280 *dev)
अणु
	अगर (dev->quirks & PLX_LEGACY)
		वापस usb_reinit_228x(dev);
	वापस usb_reinit_338x(dev);
पूर्ण

अटल व्योम ep0_start_228x(काष्ठा net2280 *dev)
अणु
	ग_लिखोl(BIT(CLEAR_EP_HIDE_STATUS_PHASE) |
		BIT(CLEAR_NAK_OUT_PACKETS) |
		BIT(CLEAR_CONTROL_STATUS_PHASE_HANDSHAKE),
		&dev->epregs[0].ep_rsp);

	/*
	 * hardware optionally handles a bunch of standard requests
	 * that the API hides from drivers anyway.  have it करो so.
	 * endpoपूर्णांक status/features are handled in software, to
	 * help pass tests क्रम some dubious behavior.
	 */
	ग_लिखोl(BIT(SET_TEST_MODE) |
		BIT(SET_ADDRESS) |
		BIT(DEVICE_SET_CLEAR_DEVICE_REMOTE_WAKEUP) |
		BIT(GET_DEVICE_STATUS) |
		BIT(GET_INTERFACE_STATUS),
		&dev->usb->stdrsp);
	ग_लिखोl(BIT(USB_ROOT_PORT_WAKEUP_ENABLE) |
		BIT(SELF_POWERED_USB_DEVICE) |
		BIT(REMOTE_WAKEUP_SUPPORT) |
		(dev->softconnect << USB_DETECT_ENABLE) |
		BIT(SELF_POWERED_STATUS),
		&dev->usb->usbctl);

	/* enable irqs so we can see ep0 and general operation  */
	ग_लिखोl(BIT(SETUP_PACKET_INTERRUPT_ENABLE) |
		BIT(ENDPOINT_0_INTERRUPT_ENABLE),
		&dev->regs->pciirqenb0);
	ग_लिखोl(BIT(PCI_INTERRUPT_ENABLE) |
		BIT(PCI_MASTER_ABORT_RECEIVED_INTERRUPT_ENABLE) |
		BIT(PCI_TARGET_ABORT_RECEIVED_INTERRUPT_ENABLE) |
		BIT(PCI_RETRY_ABORT_INTERRUPT_ENABLE) |
		BIT(VBUS_INTERRUPT_ENABLE) |
		BIT(ROOT_PORT_RESET_INTERRUPT_ENABLE) |
		BIT(SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE),
		&dev->regs->pciirqenb1);

	/* करोn't leave any ग_लिखोs posted */
	(व्योम) पढ़ोl(&dev->usb->usbctl);
पूर्ण

अटल व्योम ep0_start_338x(काष्ठा net2280 *dev)
अणु

	अगर (dev->bug7734_patched)
		ग_लिखोl(BIT(CLEAR_NAK_OUT_PACKETS_MODE) |
		       BIT(SET_EP_HIDE_STATUS_PHASE),
		       &dev->epregs[0].ep_rsp);

	/*
	 * hardware optionally handles a bunch of standard requests
	 * that the API hides from drivers anyway.  have it करो so.
	 * endpoपूर्णांक status/features are handled in software, to
	 * help pass tests क्रम some dubious behavior.
	 */
	ग_लिखोl(BIT(SET_ISOCHRONOUS_DELAY) |
	       BIT(SET_SEL) |
	       BIT(SET_TEST_MODE) |
	       BIT(SET_ADDRESS) |
	       BIT(GET_INTERFACE_STATUS) |
	       BIT(GET_DEVICE_STATUS),
		&dev->usb->stdrsp);
	dev->wakeup_enable = 1;
	ग_लिखोl(BIT(USB_ROOT_PORT_WAKEUP_ENABLE) |
	       (dev->softconnect << USB_DETECT_ENABLE) |
	       BIT(DEVICE_REMOTE_WAKEUP_ENABLE),
	       &dev->usb->usbctl);

	/* enable irqs so we can see ep0 and general operation  */
	ग_लिखोl(BIT(SETUP_PACKET_INTERRUPT_ENABLE) |
	       BIT(ENDPOINT_0_INTERRUPT_ENABLE),
	       &dev->regs->pciirqenb0);
	ग_लिखोl(BIT(PCI_INTERRUPT_ENABLE) |
	       BIT(ROOT_PORT_RESET_INTERRUPT_ENABLE) |
	       BIT(SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE) |
	       BIT(VBUS_INTERRUPT_ENABLE),
	       &dev->regs->pciirqenb1);

	/* करोn't leave any ग_लिखोs posted */
	(व्योम)पढ़ोl(&dev->usb->usbctl);
पूर्ण

अटल व्योम ep0_start(काष्ठा net2280 *dev)
अणु
	अगर (dev->quirks & PLX_LEGACY)
		वापस ep0_start_228x(dev);
	वापस ep0_start_338x(dev);
पूर्ण

/* when a driver is successfully रेजिस्टरed, it will receive
 * control requests including set_configuration(), which enables
 * non-control requests.  then usb traffic follows until a
 * disconnect is reported.  then a host may connect again, or
 * the driver might get unbound.
 */
अटल पूर्णांक net2280_start(काष्ठा usb_gadget *_gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा net2280		*dev;
	पूर्णांक			retval;
	अचिन्हित		i;

	/* insist on high speed support from the driver, since
	 * (dev->usb->xcvrdiag & FORCE_FULL_SPEED_MODE)
	 * "must not be used in normal operation"
	 */
	अगर (!driver || driver->max_speed < USB_SPEED_HIGH ||
			!driver->setup)
		वापस -EINVAL;

	dev = container_of(_gadget, काष्ठा net2280, gadget);

	क्रम (i = 0; i < dev->n_ep; i++)
		dev->ep[i].irqs = 0;

	/* hook up the driver ... */
	driver->driver.bus = शून्य;
	dev->driver = driver;

	retval = device_create_file(&dev->pdev->dev, &dev_attr_function);
	अगर (retval)
		जाओ err_unbind;
	retval = device_create_file(&dev->pdev->dev, &dev_attr_queues);
	अगर (retval)
		जाओ err_func;

	/* enable host detection and ep0; and we're पढ़ोy
	 * क्रम set_configuration as well as eventual disconnect.
	 */
	net2280_led_active(dev, 1);

	अगर ((dev->quirks & PLX_PCIE) && !dev->bug7734_patched)
		defect7374_enable_data_eps_zero(dev);

	ep0_start(dev);

	/* pci ग_लिखोs may still be posted */
	वापस 0;

err_func:
	device_हटाओ_file(&dev->pdev->dev, &dev_attr_function);
err_unbind:
	dev->driver = शून्य;
	वापस retval;
पूर्ण

अटल व्योम stop_activity(काष्ठा net2280 *dev, काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक			i;

	/* करोn't disconnect if it's not connected */
	अगर (dev->gadget.speed == USB_SPEED_UNKNOWN)
		driver = शून्य;

	/* stop hardware; prevent new request submissions;
	 * and समाप्त any outstanding requests.
	 */
	usb_reset(dev);
	क्रम (i = 0; i < dev->n_ep; i++)
		nuke(&dev->ep[i]);

	/* report disconnect; the driver is alपढ़ोy quiesced */
	अगर (driver) अणु
		spin_unlock(&dev->lock);
		driver->disconnect(&dev->gadget);
		spin_lock(&dev->lock);
	पूर्ण

	usb_reinit(dev);
पूर्ण

अटल पूर्णांक net2280_stop(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा net2280	*dev;
	अचिन्हित दीर्घ	flags;

	dev = container_of(_gadget, काष्ठा net2280, gadget);

	spin_lock_irqsave(&dev->lock, flags);
	stop_activity(dev, शून्य);
	spin_unlock_irqrestore(&dev->lock, flags);

	net2280_led_active(dev, 0);

	device_हटाओ_file(&dev->pdev->dev, &dev_attr_function);
	device_हटाओ_file(&dev->pdev->dev, &dev_attr_queues);

	dev->driver = शून्य;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/* handle ep0, ep-e, ep-f with 64 byte packets: packet per irq.
 * also works क्रम dma-capable endpoपूर्णांकs, in pio mode or just
 * to manually advance the queue after लघु OUT transfers.
 */
अटल व्योम handle_ep_small(काष्ठा net2280_ep *ep)
अणु
	काष्ठा net2280_request	*req;
	u32			t;
	/* 0 error, 1 mid-data, 2 करोne */
	पूर्णांक			mode = 1;

	अगर (!list_empty(&ep->queue))
		req = list_entry(ep->queue.next,
			काष्ठा net2280_request, queue);
	अन्यथा
		req = शून्य;

	/* ack all, and handle what we care about */
	t = पढ़ोl(&ep->regs->ep_stat);
	ep->irqs++;

	ep_vdbg(ep->dev, "%s ack ep_stat %08x, req %p\n",
			ep->ep.name, t, req ? &req->req : शून्य);

	अगर (!ep->is_in || (ep->dev->quirks & PLX_2280))
		ग_लिखोl(t & ~BIT(NAK_OUT_PACKETS), &ep->regs->ep_stat);
	अन्यथा
		/* Added क्रम 2282 */
		ग_लिखोl(t, &ep->regs->ep_stat);

	/* क्रम ep0, monitor token irqs to catch data stage length errors
	 * and to synchronize on status.
	 *
	 * also, to defer reporting of protocol stalls ... here's where
	 * data or status first appears, handling stalls here should never
	 * cause trouble on the host side..
	 *
	 * control requests could be slightly faster without token synch क्रम
	 * status, but status can jam up that way.
	 */
	अगर (unlikely(ep->num == 0)) अणु
		अगर (ep->is_in) अणु
			/* status; stop NAKing */
			अगर (t & BIT(DATA_OUT_PING_TOKEN_INTERRUPT)) अणु
				अगर (ep->dev->protocol_stall) अणु
					ep->stopped = 1;
					set_halt(ep);
				पूर्ण
				अगर (!req)
					allow_status(ep);
				mode = 2;
			/* reply to extra IN data tokens with a zlp */
			पूर्ण अन्यथा अगर (t & BIT(DATA_IN_TOKEN_INTERRUPT)) अणु
				अगर (ep->dev->protocol_stall) अणु
					ep->stopped = 1;
					set_halt(ep);
					mode = 2;
				पूर्ण अन्यथा अगर (ep->responded &&
						!req && !ep->stopped)
					ग_लिखो_fअगरo(ep, शून्य);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* status; stop NAKing */
			अगर (t & BIT(DATA_IN_TOKEN_INTERRUPT)) अणु
				अगर (ep->dev->protocol_stall) अणु
					ep->stopped = 1;
					set_halt(ep);
				पूर्ण
				mode = 2;
			/* an extra OUT token is an error */
			पूर्ण अन्यथा अगर (((t & BIT(DATA_OUT_PING_TOKEN_INTERRUPT)) &&
					req &&
					req->req.actual == req->req.length) ||
					(ep->responded && !req)) अणु
				ep->dev->protocol_stall = 1;
				set_halt(ep);
				ep->stopped = 1;
				अगर (req)
					करोne(ep, req, -EOVERFLOW);
				req = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (unlikely(!req))
		वापस;

	/* manual DMA queue advance after लघु OUT */
	अगर (likely(ep->dma)) अणु
		अगर (t & BIT(SHORT_PACKET_TRANSFERRED_INTERRUPT)) अणु
			काष्ठा net2280_request *stuck_req = शून्य;
			पूर्णांक	stopped = ep->stopped;
			पूर्णांक	num_completed;
			पूर्णांक	stuck = 0;
			u32	count;

			/* TRANSFERRED works around OUT_DONE erratum 0112.
			 * we expect (N <= maxpacket) bytes; host wrote M.
			 * अगरf (M < N) we won't ever see a DMA पूर्णांकerrupt.
			 */
			ep->stopped = 1;
			क्रम (count = 0; ; t = पढ़ोl(&ep->regs->ep_stat)) अणु

				/* any preceding dma transfers must finish.
				 * dma handles (M >= N), may empty the queue
				 */
				num_completed = scan_dma_completions(ep);
				अगर (unlikely(list_empty(&ep->queue) ||
						ep->out_overflow)) अणु
					req = शून्य;
					अवरोध;
				पूर्ण
				req = list_entry(ep->queue.next,
					काष्ठा net2280_request, queue);

				/* here either (M < N), a "real" लघु rx;
				 * or (M == N) and the queue didn't empty
				 */
				अगर (likely(t & BIT(FIFO_EMPTY))) अणु
					count = पढ़ोl(&ep->dma->dmacount);
					count &= DMA_BYTE_COUNT_MASK;
					अगर (पढ़ोl(&ep->dma->dmadesc)
							!= req->td_dma)
						req = शून्य;
					अवरोध;
				पूर्ण

				/* Escape loop अगर no dma transfers completed
				 * after few retries.
				 */
				अगर (num_completed == 0) अणु
					अगर (stuck_req == req &&
					    पढ़ोl(&ep->dma->dmadesc) !=
						  req->td_dma && stuck++ > 5) अणु
						count = पढ़ोl(
							&ep->dma->dmacount);
						count &= DMA_BYTE_COUNT_MASK;
						req = शून्य;
						ep_dbg(ep->dev, "%s escape stuck %d, count %u\n",
							ep->ep.name, stuck,
							count);
						अवरोध;
					पूर्ण अन्यथा अगर (stuck_req != req) अणु
						stuck_req = req;
						stuck = 0;
					पूर्ण
				पूर्ण अन्यथा अणु
					stuck_req = शून्य;
					stuck = 0;
				पूर्ण

				udelay(1);
			पूर्ण

			/* stop DMA, leave ep NAKing */
			ग_लिखोl(BIT(DMA_ABORT), &ep->dma->dmastat);
			spin_stop_dma(ep->dma);

			अगर (likely(req)) अणु
				req->td->dmacount = 0;
				t = पढ़ोl(&ep->regs->ep_avail);
				dma_करोne(ep, req, count,
					(ep->out_overflow || t)
						? -EOVERFLOW : 0);
			पूर्ण

			/* also flush to prevent erratum 0106 trouble */
			अगर (unlikely(ep->out_overflow ||
					(ep->dev->chiprev == 0x0100 &&
					ep->dev->gadget.speed
					== USB_SPEED_FULL))) अणु
				out_flush(ep);
				ep->out_overflow = 0;
			पूर्ण

			/* (re)start dma अगर needed, stop NAKing */
			ep->stopped = stopped;
			अगर (!list_empty(&ep->queue))
				restart_dma(ep);
		पूर्ण अन्यथा
			ep_dbg(ep->dev, "%s dma ep_stat %08x ??\n",
					ep->ep.name, t);
		वापस;

	/* data packet(s) received (in the fअगरo, OUT) */
	पूर्ण अन्यथा अगर (t & BIT(DATA_PACKET_RECEIVED_INTERRUPT)) अणु
		अगर (पढ़ो_fअगरo(ep, req) && ep->num != 0)
			mode = 2;

	/* data packet(s) transmitted (IN) */
	पूर्ण अन्यथा अगर (t & BIT(DATA_PACKET_TRANSMITTED_INTERRUPT)) अणु
		अचिन्हित	len;

		len = req->req.length - req->req.actual;
		अगर (len > ep->ep.maxpacket)
			len = ep->ep.maxpacket;
		req->req.actual += len;

		/* अगर we wrote it all, we're usually करोne */
		/* send zlps until the status stage */
		अगर ((req->req.actual == req->req.length) &&
			(!req->req.zero || len != ep->ep.maxpacket) && ep->num)
				mode = 2;

	/* there was nothing to करो ...  */
	पूर्ण अन्यथा अगर (mode == 1)
		वापस;

	/* करोne */
	अगर (mode == 2) अणु
		/* stream endpoपूर्णांकs often resubmit/unlink in completion */
		करोne(ep, req, 0);

		/* maybe advance queue to next request */
		अगर (ep->num == 0) अणु
			/* NOTE:  net2280 could let gadget driver start the
			 * status stage later. since not all controllers let
			 * them control that, the api करोesn't (yet) allow it.
			 */
			अगर (!ep->stopped)
				allow_status(ep);
			req = शून्य;
		पूर्ण अन्यथा अणु
			अगर (!list_empty(&ep->queue) && !ep->stopped)
				req = list_entry(ep->queue.next,
					काष्ठा net2280_request, queue);
			अन्यथा
				req = शून्य;
			अगर (req && !ep->is_in)
				stop_out_naking(ep);
		पूर्ण
	पूर्ण

	/* is there a buffer क्रम the next packet?
	 * क्रम best streaming perक्रमmance, make sure there is one.
	 */
	अगर (req && !ep->stopped) अणु

		/* load IN fअगरo with next packet (may be zlp) */
		अगर (t & BIT(DATA_PACKET_TRANSMITTED_INTERRUPT))
			ग_लिखो_fअगरo(ep, &req->req);
	पूर्ण
पूर्ण

अटल काष्ठा net2280_ep *get_ep_by_addr(काष्ठा net2280 *dev, u16 wIndex)
अणु
	काष्ठा net2280_ep	*ep;

	अगर ((wIndex & USB_ENDPOINT_NUMBER_MASK) == 0)
		वापस &dev->ep[0];
	list_क्रम_each_entry(ep, &dev->gadget.ep_list, ep.ep_list) अणु
		u8	bEndpoपूर्णांकAddress;

		अगर (!ep->desc)
			जारी;
		bEndpoपूर्णांकAddress = ep->desc->bEndpoपूर्णांकAddress;
		अगर ((wIndex ^ bEndpoपूर्णांकAddress) & USB_सूची_IN)
			जारी;
		अगर ((wIndex & 0x0f) == (bEndpoपूर्णांकAddress & 0x0f))
			वापस ep;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम defect7374_workaround(काष्ठा net2280 *dev, काष्ठा usb_ctrlrequest r)
अणु
	u32 scratch, fsmvalue;
	u32 ack_रुको_समयout, state;

	/* Workaround क्रम Defect 7374 (U1/U2 erroneously rejected): */
	scratch = get_idx_reg(dev->regs, SCRATCH);
	fsmvalue = scratch & (0xf << DEFECT7374_FSM_FIELD);
	scratch &= ~(0xf << DEFECT7374_FSM_FIELD);

	अगर (!((fsmvalue == DEFECT7374_FSM_WAITING_FOR_CONTROL_READ) &&
				(r.bRequestType & USB_सूची_IN)))
		वापस;

	/* This is the first Control Read क्रम this connection: */
	अगर (!(पढ़ोl(&dev->usb->usbstat) & BIT(SUPER_SPEED_MODE))) अणु
		/*
		 * Connection is NOT SS:
		 * - Connection must be FS or HS.
		 * - This FSM state should allow workaround software to
		 * run after the next USB connection.
		 */
		scratch |= DEFECT7374_FSM_NON_SS_CONTROL_READ;
		dev->bug7734_patched = 1;
		जाओ restore_data_eps;
	पूर्ण

	/* Connection is SS: */
	क्रम (ack_रुको_समयout = 0;
			ack_रुको_समयout < DEFECT_7374_NUMBEROF_MAX_WAIT_LOOPS;
			ack_रुको_समयout++) अणु

		state =	पढ़ोl(&dev->plregs->pl_ep_status_1)
			& (0xff << STATE);
		अगर ((state >= (ACK_GOOD_NORMAL << STATE)) &&
			(state <= (ACK_GOOD_MORE_ACKS_TO_COME << STATE))) अणु
			scratch |= DEFECT7374_FSM_SS_CONTROL_READ;
			dev->bug7734_patched = 1;
			अवरोध;
		पूर्ण

		/*
		 * We have not yet received host's Data Phase ACK
		 * - Wait and try again.
		 */
		udelay(DEFECT_7374_PROCESSOR_WAIT_TIME);

		जारी;
	पूर्ण


	अगर (ack_रुको_समयout >= DEFECT_7374_NUMBEROF_MAX_WAIT_LOOPS) अणु
		ep_err(dev, "FAIL: Defect 7374 workaround waited but failed "
		"to detect SS host's data phase ACK.");
		ep_err(dev, "PL_EP_STATUS_1(23:16):.Expected from 0x11 to 0x16"
		"got 0x%2.2x.\n", state >> STATE);
	पूर्ण अन्यथा अणु
		ep_warn(dev, "INFO: Defect 7374 workaround waited about\n"
		"%duSec for Control Read Data Phase ACK\n",
			DEFECT_7374_PROCESSOR_WAIT_TIME * ack_रुको_समयout);
	पूर्ण

restore_data_eps:
	/*
	 * Restore data EPs to their pre-workaround settings (disabled,
	 * initialized, and other details).
	 */
	defect7374_disable_data_eps(dev);

	set_idx_reg(dev->regs, SCRATCH, scratch);

	वापस;
पूर्ण

अटल व्योम ep_clear_seqnum(काष्ठा net2280_ep *ep)
अणु
	काष्ठा net2280 *dev = ep->dev;
	u32 val;
	अटल स्थिर u32 ep_pl[9] = अणु 0, 3, 4, 7, 8, 2, 5, 6, 9 पूर्ण;

	val = पढ़ोl(&dev->plregs->pl_ep_ctrl) & ~0x1f;
	val |= ep_pl[ep->num];
	ग_लिखोl(val, &dev->plregs->pl_ep_ctrl);
	val |= BIT(SEQUENCE_NUMBER_RESET);
	ग_लिखोl(val, &dev->plregs->pl_ep_ctrl);

	वापस;
पूर्ण

अटल व्योम handle_stat0_irqs_superspeed(काष्ठा net2280 *dev,
		काष्ठा net2280_ep *ep, काष्ठा usb_ctrlrequest r)
अणु
	काष्ठा net2280_ep *e;
	u16 status;
	पूर्णांक पंचांगp = 0;

#घोषणा	w_value		le16_to_cpu(r.wValue)
#घोषणा	w_index		le16_to_cpu(r.wIndex)
#घोषणा	w_length	le16_to_cpu(r.wLength)

	चयन (r.bRequest) अणु
	हाल USB_REQ_SET_CONFIGURATION:
		dev->addressed_state = !w_value;
		जाओ usb3_delegate;

	हाल USB_REQ_GET_STATUS:
		चयन (r.bRequestType) अणु
		हाल (USB_सूची_IN | USB_TYPE_STANDARD | USB_RECIP_DEVICE):
			status = dev->wakeup_enable ? 0x02 : 0x00;
			अगर (dev->gadget.is_selfघातered)
				status |= BIT(0);
			status |= (dev->u1_enable << 2 | dev->u2_enable << 3 |
							dev->lपंचांग_enable << 4);
			ग_लिखोl(0, &dev->epregs[0].ep_irqenb);
			set_fअगरo_bytecount(ep, माप(status));
			ग_लिखोl((__क्रमce u32) status, &dev->epregs[0].ep_data);
			allow_status_338x(ep);
			अवरोध;

		हाल (USB_सूची_IN | USB_TYPE_STANDARD | USB_RECIP_ENDPOINT):
			e = get_ep_by_addr(dev, w_index);
			अगर (!e)
				जाओ करो_stall3;
			status = पढ़ोl(&e->regs->ep_rsp) &
						BIT(CLEAR_ENDPOINT_HALT);
			ग_लिखोl(0, &dev->epregs[0].ep_irqenb);
			set_fअगरo_bytecount(ep, माप(status));
			ग_लिखोl((__क्रमce u32) status, &dev->epregs[0].ep_data);
			allow_status_338x(ep);
			अवरोध;

		शेष:
			जाओ usb3_delegate;
		पूर्ण
		अवरोध;

	हाल USB_REQ_CLEAR_FEATURE:
		चयन (r.bRequestType) अणु
		हाल (USB_सूची_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE):
			अगर (!dev->addressed_state) अणु
				चयन (w_value) अणु
				हाल USB_DEVICE_U1_ENABLE:
					dev->u1_enable = 0;
					ग_लिखोl(पढ़ोl(&dev->usb_ext->usbctl2) &
						~BIT(U1_ENABLE),
						&dev->usb_ext->usbctl2);
					allow_status_338x(ep);
					जाओ next_endpoपूर्णांकs3;

				हाल USB_DEVICE_U2_ENABLE:
					dev->u2_enable = 0;
					ग_लिखोl(पढ़ोl(&dev->usb_ext->usbctl2) &
						~BIT(U2_ENABLE),
						&dev->usb_ext->usbctl2);
					allow_status_338x(ep);
					जाओ next_endpoपूर्णांकs3;

				हाल USB_DEVICE_LTM_ENABLE:
					dev->lपंचांग_enable = 0;
					ग_लिखोl(पढ़ोl(&dev->usb_ext->usbctl2) &
						~BIT(LTM_ENABLE),
						&dev->usb_ext->usbctl2);
					allow_status_338x(ep);
					जाओ next_endpoपूर्णांकs3;

				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (w_value == USB_DEVICE_REMOTE_WAKEUP) अणु
				dev->wakeup_enable = 0;
				ग_लिखोl(पढ़ोl(&dev->usb->usbctl) &
					~BIT(DEVICE_REMOTE_WAKEUP_ENABLE),
					&dev->usb->usbctl);
				allow_status_338x(ep);
				अवरोध;
			पूर्ण
			जाओ usb3_delegate;

		हाल (USB_सूची_OUT | USB_TYPE_STANDARD | USB_RECIP_ENDPOINT):
			e = get_ep_by_addr(dev,	w_index);
			अगर (!e)
				जाओ करो_stall3;
			अगर (w_value != USB_ENDPOINT_HALT)
				जाओ करो_stall3;
			ep_vdbg(dev, "%s clear halt\n", e->ep.name);
			/*
			 * Workaround क्रम SS SeqNum not cleared via
			 * Endpoपूर्णांक Halt (Clear) bit. select endpoपूर्णांक
			 */
			ep_clear_seqnum(e);
			clear_halt(e);
			अगर (!list_empty(&e->queue) && e->td_dma)
				restart_dma(e);
			allow_status(ep);
			ep->stopped = 1;
			अवरोध;

		शेष:
			जाओ usb3_delegate;
		पूर्ण
		अवरोध;
	हाल USB_REQ_SET_FEATURE:
		चयन (r.bRequestType) अणु
		हाल (USB_सूची_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE):
			अगर (!dev->addressed_state) अणु
				चयन (w_value) अणु
				हाल USB_DEVICE_U1_ENABLE:
					dev->u1_enable = 1;
					ग_लिखोl(पढ़ोl(&dev->usb_ext->usbctl2) |
						BIT(U1_ENABLE),
						&dev->usb_ext->usbctl2);
					allow_status_338x(ep);
					जाओ next_endpoपूर्णांकs3;

				हाल USB_DEVICE_U2_ENABLE:
					dev->u2_enable = 1;
					ग_लिखोl(पढ़ोl(&dev->usb_ext->usbctl2) |
						BIT(U2_ENABLE),
						&dev->usb_ext->usbctl2);
					allow_status_338x(ep);
					जाओ next_endpoपूर्णांकs3;

				हाल USB_DEVICE_LTM_ENABLE:
					dev->lपंचांग_enable = 1;
					ग_लिखोl(पढ़ोl(&dev->usb_ext->usbctl2) |
						BIT(LTM_ENABLE),
						&dev->usb_ext->usbctl2);
					allow_status_338x(ep);
					जाओ next_endpoपूर्णांकs3;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (w_value == USB_DEVICE_REMOTE_WAKEUP) अणु
				dev->wakeup_enable = 1;
				ग_लिखोl(पढ़ोl(&dev->usb->usbctl) |
					BIT(DEVICE_REMOTE_WAKEUP_ENABLE),
					&dev->usb->usbctl);
				allow_status_338x(ep);
				अवरोध;
			पूर्ण
			जाओ usb3_delegate;

		हाल (USB_सूची_OUT | USB_TYPE_STANDARD | USB_RECIP_ENDPOINT):
			e = get_ep_by_addr(dev,	w_index);
			अगर (!e || (w_value != USB_ENDPOINT_HALT))
				जाओ करो_stall3;
			ep->stopped = 1;
			अगर (ep->num == 0)
				ep->dev->protocol_stall = 1;
			अन्यथा अणु
				अगर (ep->dma)
					पात_dma(ep);
				set_halt(ep);
			पूर्ण
			allow_status_338x(ep);
			अवरोध;

		शेष:
			जाओ usb3_delegate;
		पूर्ण

		अवरोध;
	शेष:

usb3_delegate:
		ep_vdbg(dev, "setup %02x.%02x v%04x i%04x l%04x ep_cfg %08x\n",
				r.bRequestType, r.bRequest,
				w_value, w_index, w_length,
				पढ़ोl(&ep->cfg->ep_cfg));

		ep->responded = 0;
		spin_unlock(&dev->lock);
		पंचांगp = dev->driver->setup(&dev->gadget, &r);
		spin_lock(&dev->lock);
	पूर्ण
करो_stall3:
	अगर (पंचांगp < 0) अणु
		ep_vdbg(dev, "req %02x.%02x protocol STALL; stat %d\n",
				r.bRequestType, r.bRequest, पंचांगp);
		dev->protocol_stall = 1;
		/* TD 9.9 Halt Endpoपूर्णांक test. TD 9.22 Set feature test */
		set_halt(ep);
	पूर्ण

next_endpoपूर्णांकs3:

#अघोषित	w_value
#अघोषित	w_index
#अघोषित	w_length

	वापस;
पूर्ण

अटल व्योम usb338x_handle_ep_पूर्णांकr(काष्ठा net2280 *dev, u32 stat0)
अणु
	u32 index;
	u32 bit;

	क्रम (index = 0; index < ARRAY_SIZE(ep_bit); index++) अणु
		bit = BIT(ep_bit[index]);

		अगर (!stat0)
			अवरोध;

		अगर (!(stat0 & bit))
			जारी;

		stat0 &= ~bit;

		handle_ep_small(&dev->ep[index]);
	पूर्ण
पूर्ण

अटल व्योम handle_stat0_irqs(काष्ठा net2280 *dev, u32 stat)
अणु
	काष्ठा net2280_ep	*ep;
	u32			num, scratch;

	/* most of these करोn't need inभागidual acks */
	stat &= ~BIT(INTA_ASSERTED);
	अगर (!stat)
		वापस;
	/* ep_dbg(dev, "irqstat0 %04x\n", stat); */

	/* starting a control request? */
	अगर (unlikely(stat & BIT(SETUP_PACKET_INTERRUPT))) अणु
		जोड़ अणु
			u32			raw[2];
			काष्ठा usb_ctrlrequest	r;
		पूर्ण u;
		पूर्णांक				पंचांगp;
		काष्ठा net2280_request		*req;

		अगर (dev->gadget.speed == USB_SPEED_UNKNOWN) अणु
			u32 val = पढ़ोl(&dev->usb->usbstat);
			अगर (val & BIT(SUPER_SPEED)) अणु
				dev->gadget.speed = USB_SPEED_SUPER;
				usb_ep_set_maxpacket_limit(&dev->ep[0].ep,
						EP0_SS_MAX_PACKET_SIZE);
			पूर्ण अन्यथा अगर (val & BIT(HIGH_SPEED)) अणु
				dev->gadget.speed = USB_SPEED_HIGH;
				usb_ep_set_maxpacket_limit(&dev->ep[0].ep,
						EP0_HS_MAX_PACKET_SIZE);
			पूर्ण अन्यथा अणु
				dev->gadget.speed = USB_SPEED_FULL;
				usb_ep_set_maxpacket_limit(&dev->ep[0].ep,
						EP0_HS_MAX_PACKET_SIZE);
			पूर्ण
			net2280_led_speed(dev, dev->gadget.speed);
			ep_dbg(dev, "%s\n",
					usb_speed_string(dev->gadget.speed));
		पूर्ण

		ep = &dev->ep[0];
		ep->irqs++;

		/* make sure any leftover request state is cleared */
		stat &= ~BIT(ENDPOINT_0_INTERRUPT);
		जबतक (!list_empty(&ep->queue)) अणु
			req = list_entry(ep->queue.next,
					काष्ठा net2280_request, queue);
			करोne(ep, req, (req->req.actual == req->req.length)
						? 0 : -EPROTO);
		पूर्ण
		ep->stopped = 0;
		dev->protocol_stall = 0;
		अगर (!(dev->quirks & PLX_PCIE)) अणु
			अगर (ep->dev->quirks & PLX_2280)
				पंचांगp = BIT(FIFO_OVERFLOW) |
				    BIT(FIFO_UNDERFLOW);
			अन्यथा
				पंचांगp = 0;

			ग_लिखोl(पंचांगp | BIT(TIMEOUT) |
				   BIT(USB_STALL_SENT) |
				   BIT(USB_IN_NAK_SENT) |
				   BIT(USB_IN_ACK_RCVD) |
				   BIT(USB_OUT_PING_NAK_SENT) |
				   BIT(USB_OUT_ACK_SENT) |
				   BIT(SHORT_PACKET_OUT_DONE_INTERRUPT) |
				   BIT(SHORT_PACKET_TRANSFERRED_INTERRUPT) |
				   BIT(DATA_PACKET_RECEIVED_INTERRUPT) |
				   BIT(DATA_PACKET_TRANSMITTED_INTERRUPT) |
				   BIT(DATA_OUT_PING_TOKEN_INTERRUPT) |
				   BIT(DATA_IN_TOKEN_INTERRUPT),
				   &ep->regs->ep_stat);
		पूर्ण
		u.raw[0] = पढ़ोl(&dev->usb->setup0123);
		u.raw[1] = पढ़ोl(&dev->usb->setup4567);

		cpu_to_le32s(&u.raw[0]);
		cpu_to_le32s(&u.raw[1]);

		अगर ((dev->quirks & PLX_PCIE) && !dev->bug7734_patched)
			defect7374_workaround(dev, u.r);

		पंचांगp = 0;

#घोषणा	w_value		le16_to_cpu(u.r.wValue)
#घोषणा	w_index		le16_to_cpu(u.r.wIndex)
#घोषणा	w_length	le16_to_cpu(u.r.wLength)

		/* ack the irq */
		ग_लिखोl(BIT(SETUP_PACKET_INTERRUPT), &dev->regs->irqstat0);
		stat ^= BIT(SETUP_PACKET_INTERRUPT);

		/* watch control traffic at the token level, and क्रमce
		 * synchronization beक्रमe letting the status stage happen.
		 * FIXME ignore tokens we'll NAK, until driver responds.
		 * that'll mean a lot less irqs क्रम some drivers.
		 */
		ep->is_in = (u.r.bRequestType & USB_सूची_IN) != 0;
		अगर (ep->is_in) अणु
			scratch = BIT(DATA_PACKET_TRANSMITTED_INTERRUPT) |
				BIT(DATA_OUT_PING_TOKEN_INTERRUPT) |
				BIT(DATA_IN_TOKEN_INTERRUPT);
			stop_out_naking(ep);
		पूर्ण अन्यथा
			scratch = BIT(DATA_PACKET_RECEIVED_INTERRUPT) |
				BIT(DATA_OUT_PING_TOKEN_INTERRUPT) |
				BIT(DATA_IN_TOKEN_INTERRUPT);
		ग_लिखोl(scratch, &dev->epregs[0].ep_irqenb);

		/* we made the hardware handle most lowlevel requests;
		 * everything अन्यथा goes uplevel to the gadget code.
		 */
		ep->responded = 1;

		अगर (dev->gadget.speed == USB_SPEED_SUPER) अणु
			handle_stat0_irqs_superspeed(dev, ep, u.r);
			जाओ next_endpoपूर्णांकs;
		पूर्ण

		चयन (u.r.bRequest) अणु
		हाल USB_REQ_GET_STATUS: अणु
			काष्ठा net2280_ep	*e;
			__le32			status;

			/* hw handles device and पूर्णांकerface status */
			अगर (u.r.bRequestType != (USB_सूची_IN|USB_RECIP_ENDPOINT))
				जाओ delegate;
			e = get_ep_by_addr(dev, w_index);
			अगर (!e || w_length > 2)
				जाओ करो_stall;

			अगर (पढ़ोl(&e->regs->ep_rsp) & BIT(SET_ENDPOINT_HALT))
				status = cpu_to_le32(1);
			अन्यथा
				status = cpu_to_le32(0);

			/* करोn't bother with a request object! */
			ग_लिखोl(0, &dev->epregs[0].ep_irqenb);
			set_fअगरo_bytecount(ep, w_length);
			ग_लिखोl((__क्रमce u32)status, &dev->epregs[0].ep_data);
			allow_status(ep);
			ep_vdbg(dev, "%s stat %02x\n", ep->ep.name, status);
			जाओ next_endpoपूर्णांकs;
			पूर्ण
			अवरोध;
		हाल USB_REQ_CLEAR_FEATURE: अणु
			काष्ठा net2280_ep	*e;

			/* hw handles device features */
			अगर (u.r.bRequestType != USB_RECIP_ENDPOINT)
				जाओ delegate;
			अगर (w_value != USB_ENDPOINT_HALT || w_length != 0)
				जाओ करो_stall;
			e = get_ep_by_addr(dev, w_index);
			अगर (!e)
				जाओ करो_stall;
			अगर (e->wedged) अणु
				ep_vdbg(dev, "%s wedged, halt not cleared\n",
						ep->ep.name);
			पूर्ण अन्यथा अणु
				ep_vdbg(dev, "%s clear halt\n", e->ep.name);
				clear_halt(e);
				अगर ((ep->dev->quirks & PLX_PCIE) &&
					!list_empty(&e->queue) && e->td_dma)
						restart_dma(e);
			पूर्ण
			allow_status(ep);
			जाओ next_endpoपूर्णांकs;
			पूर्ण
			अवरोध;
		हाल USB_REQ_SET_FEATURE: अणु
			काष्ठा net2280_ep	*e;

			/* hw handles device features */
			अगर (u.r.bRequestType != USB_RECIP_ENDPOINT)
				जाओ delegate;
			अगर (w_value != USB_ENDPOINT_HALT || w_length != 0)
				जाओ करो_stall;
			e = get_ep_by_addr(dev, w_index);
			अगर (!e)
				जाओ करो_stall;
			अगर (e->ep.name == ep0name)
				जाओ करो_stall;
			set_halt(e);
			अगर ((dev->quirks & PLX_PCIE) && e->dma)
				पात_dma(e);
			allow_status(ep);
			ep_vdbg(dev, "%s set halt\n", ep->ep.name);
			जाओ next_endpoपूर्णांकs;
			पूर्ण
			अवरोध;
		शेष:
delegate:
			ep_vdbg(dev, "setup %02x.%02x v%04x i%04x l%04x "
				"ep_cfg %08x\n",
				u.r.bRequestType, u.r.bRequest,
				w_value, w_index, w_length,
				पढ़ोl(&ep->cfg->ep_cfg));
			ep->responded = 0;
			spin_unlock(&dev->lock);
			पंचांगp = dev->driver->setup(&dev->gadget, &u.r);
			spin_lock(&dev->lock);
		पूर्ण

		/* stall ep0 on error */
		अगर (पंचांगp < 0) अणु
करो_stall:
			ep_vdbg(dev, "req %02x.%02x protocol STALL; stat %d\n",
					u.r.bRequestType, u.r.bRequest, पंचांगp);
			dev->protocol_stall = 1;
		पूर्ण

		/* some in/out token irq should follow; maybe stall then.
		 * driver must queue a request (even zlp) or halt ep0
		 * beक्रमe the host बार out.
		 */
	पूर्ण

#अघोषित	w_value
#अघोषित	w_index
#अघोषित	w_length

next_endpoपूर्णांकs:
	अगर ((dev->quirks & PLX_PCIE) && dev->enhanced_mode) अणु
		u32 mask = (BIT(ENDPOINT_0_INTERRUPT) |
			USB3380_IRQSTAT0_EP_INTR_MASK_IN |
			USB3380_IRQSTAT0_EP_INTR_MASK_OUT);

		अगर (stat & mask) अणु
			usb338x_handle_ep_पूर्णांकr(dev, stat & mask);
			stat &= ~mask;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* endpoपूर्णांक data irq ? */
		scratch = stat & 0x7f;
		stat &= ~0x7f;
		क्रम (num = 0; scratch; num++) अणु
			u32		t;

			/* करो this endpoपूर्णांक's FIFO and queue need tending? */
			t = BIT(num);
			अगर ((scratch & t) == 0)
				जारी;
			scratch ^= t;

			ep = &dev->ep[num];
			handle_ep_small(ep);
		पूर्ण
	पूर्ण

	अगर (stat)
		ep_dbg(dev, "unhandled irqstat0 %08x\n", stat);
पूर्ण

#घोषणा DMA_INTERRUPTS (BIT(DMA_D_INTERRUPT) | \
		BIT(DMA_C_INTERRUPT) | \
		BIT(DMA_B_INTERRUPT) | \
		BIT(DMA_A_INTERRUPT))
#घोषणा	PCI_ERROR_INTERRUPTS ( \
		BIT(PCI_MASTER_ABORT_RECEIVED_INTERRUPT) | \
		BIT(PCI_TARGET_ABORT_RECEIVED_INTERRUPT) | \
		BIT(PCI_RETRY_ABORT_INTERRUPT))

अटल व्योम handle_stat1_irqs(काष्ठा net2280 *dev, u32 stat)
__releases(dev->lock)
__acquires(dev->lock)
अणु
	काष्ठा net2280_ep	*ep;
	u32			पंचांगp, num, mask, scratch;

	/* after disconnect there's nothing अन्यथा to करो! */
	पंचांगp = BIT(VBUS_INTERRUPT) | BIT(ROOT_PORT_RESET_INTERRUPT);
	mask = BIT(SUPER_SPEED) | BIT(HIGH_SPEED) | BIT(FULL_SPEED);

	/* VBUS disconnect is indicated by VBUS_PIN and VBUS_INTERRUPT set.
	 * Root Port Reset is indicated by ROOT_PORT_RESET_INTERRUPT set and
	 * both HIGH_SPEED and FULL_SPEED clear (as ROOT_PORT_RESET_INTERRUPT
	 * only indicates a change in the reset state).
	 */
	अगर (stat & पंचांगp) अणु
		bool	reset = false;
		bool	disconnect = false;

		/*
		 * Ignore disconnects and resets अगर the speed hasn't been set.
		 * VBUS can bounce and there's always an initial reset.
		 */
		ग_लिखोl(पंचांगp, &dev->regs->irqstat1);
		अगर (dev->gadget.speed != USB_SPEED_UNKNOWN) अणु
			अगर ((stat & BIT(VBUS_INTERRUPT)) &&
					(पढ़ोl(&dev->usb->usbctl) &
						BIT(VBUS_PIN)) == 0) अणु
				disconnect = true;
				ep_dbg(dev, "disconnect %s\n",
						dev->driver->driver.name);
			पूर्ण अन्यथा अगर ((stat & BIT(ROOT_PORT_RESET_INTERRUPT)) &&
					(पढ़ोl(&dev->usb->usbstat) & mask)
						== 0) अणु
				reset = true;
				ep_dbg(dev, "reset %s\n",
						dev->driver->driver.name);
			पूर्ण

			अगर (disconnect || reset) अणु
				stop_activity(dev, dev->driver);
				ep0_start(dev);
				spin_unlock(&dev->lock);
				अगर (reset)
					usb_gadget_udc_reset
						(&dev->gadget, dev->driver);
				अन्यथा
					(dev->driver->disconnect)
						(&dev->gadget);
				spin_lock(&dev->lock);
				वापस;
			पूर्ण
		पूर्ण
		stat &= ~पंचांगp;

		/* vBUS can bounce ... one of many reasons to ignore the
		 * notion of hotplug events on bus connect/disconnect!
		 */
		अगर (!stat)
			वापस;
	पूर्ण

	/* NOTE: chip stays in PCI D0 state क्रम now, but it could
	 * enter D1 to save more घातer
	 */
	पंचांगp = BIT(SUSPEND_REQUEST_CHANGE_INTERRUPT);
	अगर (stat & पंचांगp) अणु
		ग_लिखोl(पंचांगp, &dev->regs->irqstat1);
		spin_unlock(&dev->lock);
		अगर (stat & BIT(SUSPEND_REQUEST_INTERRUPT)) अणु
			अगर (dev->driver->suspend)
				dev->driver->suspend(&dev->gadget);
			अगर (!enable_suspend)
				stat &= ~BIT(SUSPEND_REQUEST_INTERRUPT);
		पूर्ण अन्यथा अणु
			अगर (dev->driver->resume)
				dev->driver->resume(&dev->gadget);
			/* at high speed, note erratum 0133 */
		पूर्ण
		spin_lock(&dev->lock);
		stat &= ~पंचांगp;
	पूर्ण

	/* clear any other status/irqs */
	अगर (stat)
		ग_लिखोl(stat, &dev->regs->irqstat1);

	/* some status we can just ignore */
	अगर (dev->quirks & PLX_2280)
		stat &= ~(BIT(CONTROL_STATUS_INTERRUPT) |
			  BIT(SUSPEND_REQUEST_INTERRUPT) |
			  BIT(RESUME_INTERRUPT) |
			  BIT(SOF_INTERRUPT));
	अन्यथा
		stat &= ~(BIT(CONTROL_STATUS_INTERRUPT) |
			  BIT(RESUME_INTERRUPT) |
			  BIT(SOF_DOWN_INTERRUPT) |
			  BIT(SOF_INTERRUPT));

	अगर (!stat)
		वापस;
	/* ep_dbg(dev, "irqstat1 %08x\n", stat);*/

	/* DMA status, क्रम ep-अणुa,b,c,dपूर्ण */
	scratch = stat & DMA_INTERRUPTS;
	stat &= ~DMA_INTERRUPTS;
	scratch >>= 9;
	क्रम (num = 0; scratch; num++) अणु
		काष्ठा net2280_dma_regs	__iomem *dma;

		पंचांगp = BIT(num);
		अगर ((पंचांगp & scratch) == 0)
			जारी;
		scratch ^= पंचांगp;

		ep = &dev->ep[num + 1];
		dma = ep->dma;

		अगर (!dma)
			जारी;

		/* clear ep's dma status */
		पंचांगp = पढ़ोl(&dma->dmastat);
		ग_लिखोl(पंचांगp, &dma->dmastat);

		/* dma sync*/
		अगर (dev->quirks & PLX_PCIE) अणु
			u32 r_dmacount = पढ़ोl(&dma->dmacount);
			अगर (!ep->is_in &&  (r_dmacount & 0x00FFFFFF) &&
			    (पंचांगp & BIT(DMA_TRANSACTION_DONE_INTERRUPT)))
				जारी;
		पूर्ण

		अगर (!(पंचांगp & BIT(DMA_TRANSACTION_DONE_INTERRUPT))) अणु
			ep_dbg(ep->dev, "%s no xact done? %08x\n",
				ep->ep.name, पंचांगp);
			जारी;
		पूर्ण
		stop_dma(ep->dma);

		/* OUT transfers terminate when the data from the
		 * host is in our memory.  Process whatever's करोne.
		 * On this path, we know transfer's last packet wasn't
		 * less than req->length. NAK_OUT_PACKETS may be set,
		 * or the FIFO may alपढ़ोy be holding new packets.
		 *
		 * IN transfers can linger in the FIFO क्रम a very
		 * दीर्घ समय ... we ignore that क्रम now, accounting
		 * precisely (like PIO करोes) needs per-packet irqs
		 */
		scan_dma_completions(ep);

		/* disable dma on inactive queues; अन्यथा maybe restart */
		अगर (!list_empty(&ep->queue)) अणु
			पंचांगp = पढ़ोl(&dma->dmactl);
			restart_dma(ep);
		पूर्ण
		ep->irqs++;
	पूर्ण

	/* NOTE:  there are other PCI errors we might usefully notice.
	 * अगर they appear very often, here's where to try recovering.
	 */
	अगर (stat & PCI_ERROR_INTERRUPTS) अणु
		ep_err(dev, "pci dma error; stat %08x\n", stat);
		stat &= ~PCI_ERROR_INTERRUPTS;
		/* these are fatal errors, but "maybe" they won't
		 * happen again ...
		 */
		stop_activity(dev, dev->driver);
		ep0_start(dev);
		stat = 0;
	पूर्ण

	अगर (stat)
		ep_dbg(dev, "unhandled irqstat1 %08x\n", stat);
पूर्ण

अटल irqवापस_t net2280_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा net2280		*dev = _dev;

	/* shared पूर्णांकerrupt, not ours */
	अगर ((dev->quirks & PLX_LEGACY) &&
		(!(पढ़ोl(&dev->regs->irqstat0) & BIT(INTA_ASSERTED))))
		वापस IRQ_NONE;

	spin_lock(&dev->lock);

	/* handle disconnect, dma, and more */
	handle_stat1_irqs(dev, पढ़ोl(&dev->regs->irqstat1));

	/* control requests and PIO */
	handle_stat0_irqs(dev, पढ़ोl(&dev->regs->irqstat0));

	अगर (dev->quirks & PLX_PCIE) अणु
		/* re-enable पूर्णांकerrupt to trigger any possible new पूर्णांकerrupt */
		u32 pciirqenb1 = पढ़ोl(&dev->regs->pciirqenb1);
		ग_लिखोl(pciirqenb1 & 0x7FFFFFFF, &dev->regs->pciirqenb1);
		ग_लिखोl(pciirqenb1, &dev->regs->pciirqenb1);
	पूर्ण

	spin_unlock(&dev->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम gadget_release(काष्ठा device *_dev)
अणु
	काष्ठा net2280	*dev = container_of(_dev, काष्ठा net2280, gadget.dev);

	kमुक्त(dev);
पूर्ण

/* tear करोwn the binding between this driver and the pci device */

अटल व्योम net2280_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net2280		*dev = pci_get_drvdata(pdev);

	अगर (dev->added)
		usb_del_gadget(&dev->gadget);

	BUG_ON(dev->driver);

	/* then clean up the resources we allocated during probe() */
	अगर (dev->requests) अणु
		पूर्णांक		i;
		क्रम (i = 1; i < 5; i++) अणु
			अगर (!dev->ep[i].dummy)
				जारी;
			dma_pool_मुक्त(dev->requests, dev->ep[i].dummy,
					dev->ep[i].td_dma);
		पूर्ण
		dma_pool_destroy(dev->requests);
	पूर्ण
	अगर (dev->got_irq)
		मुक्त_irq(pdev->irq, dev);
	अगर (dev->quirks & PLX_PCIE)
		pci_disable_msi(pdev);
	अगर (dev->regs) अणु
		net2280_led_shutकरोwn(dev);
		iounmap(dev->regs);
	पूर्ण
	अगर (dev->region)
		release_mem_region(pci_resource_start(pdev, 0),
				pci_resource_len(pdev, 0));
	अगर (dev->enabled)
		pci_disable_device(pdev);
	device_हटाओ_file(&pdev->dev, &dev_attr_रेजिस्टरs);

	ep_info(dev, "unbind\n");
	usb_put_gadget(&dev->gadget);
पूर्ण

/* wrap this driver around the specअगरied device, but
 * करोn't respond over USB until a gadget driver binds to us.
 */

अटल पूर्णांक net2280_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net2280		*dev;
	अचिन्हित दीर्घ		resource, len;
	व्योम			__iomem *base = शून्य;
	पूर्णांक			retval, i;

	/* alloc, and start init */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		retval = -ENOMEM;
		जाओ करोne;
	पूर्ण

	pci_set_drvdata(pdev, dev);
	usb_initialize_gadget(&pdev->dev, &dev->gadget, gadget_release);
	spin_lock_init(&dev->lock);
	dev->quirks = id->driver_data;
	dev->pdev = pdev;
	dev->gadget.ops = &net2280_ops;
	dev->gadget.max_speed = (dev->quirks & PLX_SUPERSPEED) ?
				USB_SPEED_SUPER : USB_SPEED_HIGH;

	/* the "gadget" असलtracts/भवizes the controller */
	dev->gadget.name = driver_name;

	/* now all the pci goodies ... */
	अगर (pci_enable_device(pdev) < 0) अणु
		retval = -ENODEV;
		जाओ करोne;
	पूर्ण
	dev->enabled = 1;

	/* BAR 0 holds all the रेजिस्टरs
	 * BAR 1 is 8051 memory; unused here (note erratum 0103)
	 * BAR 2 is fअगरo memory; unused here
	 */
	resource = pci_resource_start(pdev, 0);
	len = pci_resource_len(pdev, 0);
	अगर (!request_mem_region(resource, len, driver_name)) अणु
		ep_dbg(dev, "controller already in use\n");
		retval = -EBUSY;
		जाओ करोne;
	पूर्ण
	dev->region = 1;

	/* FIXME provide firmware करोwnload पूर्णांकerface to put
	 * 8051 code पूर्णांकo the chip, e.g. to turn on PCI PM.
	 */

	base = ioremap(resource, len);
	अगर (base == शून्य) अणु
		ep_dbg(dev, "can't map memory\n");
		retval = -EFAULT;
		जाओ करोne;
	पूर्ण
	dev->regs = (काष्ठा net2280_regs __iomem *) base;
	dev->usb = (काष्ठा net2280_usb_regs __iomem *) (base + 0x0080);
	dev->pci = (काष्ठा net2280_pci_regs __iomem *) (base + 0x0100);
	dev->dma = (काष्ठा net2280_dma_regs __iomem *) (base + 0x0180);
	dev->dep = (काष्ठा net2280_dep_regs __iomem *) (base + 0x0200);
	dev->epregs = (काष्ठा net2280_ep_regs __iomem *) (base + 0x0300);

	अगर (dev->quirks & PLX_PCIE) अणु
		u32 fsmvalue;
		u32 usbstat;
		dev->usb_ext = (काष्ठा usb338x_usb_ext_regs __iomem *)
							(base + 0x00b4);
		dev->llregs = (काष्ठा usb338x_ll_regs __iomem *)
							(base + 0x0700);
		dev->plregs = (काष्ठा usb338x_pl_regs __iomem *)
							(base + 0x0800);
		usbstat = पढ़ोl(&dev->usb->usbstat);
		dev->enhanced_mode = !!(usbstat & BIT(11));
		dev->n_ep = (dev->enhanced_mode) ? 9 : 5;
		/* put पूर्णांकo initial config, link up all endpoपूर्णांकs */
		fsmvalue = get_idx_reg(dev->regs, SCRATCH) &
					(0xf << DEFECT7374_FSM_FIELD);
		/* See अगर firmware needs to set up क्रम workaround: */
		अगर (fsmvalue == DEFECT7374_FSM_SS_CONTROL_READ) अणु
			dev->bug7734_patched = 1;
			ग_लिखोl(0, &dev->usb->usbctl);
		पूर्ण अन्यथा
			dev->bug7734_patched = 0;
	पूर्ण अन्यथा अणु
		dev->enhanced_mode = 0;
		dev->n_ep = 7;
		/* put पूर्णांकo initial config, link up all endpoपूर्णांकs */
		ग_लिखोl(0, &dev->usb->usbctl);
	पूर्ण

	usb_reset(dev);
	usb_reinit(dev);

	/* irq setup after old hardware is cleaned up */
	अगर (!pdev->irq) अणु
		ep_err(dev, "No IRQ.  Check PCI setup!\n");
		retval = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर (dev->quirks & PLX_PCIE)
		अगर (pci_enable_msi(pdev))
			ep_err(dev, "Failed to enable MSI mode\n");

	अगर (request_irq(pdev->irq, net2280_irq, IRQF_SHARED,
							driver_name, dev)) अणु
		ep_err(dev, "request interrupt %d failed\n", pdev->irq);
		retval = -EBUSY;
		जाओ करोne;
	पूर्ण
	dev->got_irq = 1;

	/* DMA setup */
	/* NOTE:  we know only the 32 LSBs of dma addresses may be nonzero */
	dev->requests = dma_pool_create("requests", &pdev->dev,
		माप(काष्ठा net2280_dma),
		0 /* no alignment requirements */,
		0 /* or page-crossing issues */);
	अगर (!dev->requests) अणु
		ep_dbg(dev, "can't get request pool\n");
		retval = -ENOMEM;
		जाओ करोne;
	पूर्ण
	क्रम (i = 1; i < 5; i++) अणु
		काष्ठा net2280_dma	*td;

		td = dma_pool_alloc(dev->requests, GFP_KERNEL,
				&dev->ep[i].td_dma);
		अगर (!td) अणु
			ep_dbg(dev, "can't get dummy %d\n", i);
			retval = -ENOMEM;
			जाओ करोne;
		पूर्ण
		td->dmacount = 0;	/* not VALID */
		td->dmadesc = td->dmaaddr;
		dev->ep[i].dummy = td;
	पूर्ण

	/* enable lower-overhead pci memory bursts during DMA */
	अगर (dev->quirks & PLX_LEGACY)
		ग_लिखोl(BIT(DMA_MEMORY_WRITE_AND_INVALIDATE_ENABLE) |
			/*
			 * 256 ग_लिखो retries may not be enough...
			   BIT(PCI_RETRY_ABORT_ENABLE) |
			*/
			BIT(DMA_READ_MULTIPLE_ENABLE) |
			BIT(DMA_READ_LINE_ENABLE),
			&dev->pci->pcimstctl);
	/* erratum 0115 shouldn't appear: Linux inits PCI_LATENCY_TIMER */
	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	/* ... also flushes any posted pci ग_लिखोs */
	dev->chiprev = get_idx_reg(dev->regs, REG_CHIPREV) & 0xffff;

	/* करोne */
	ep_info(dev, "%s\n", driver_desc);
	ep_info(dev, "irq %d, pci mem %p, chip rev %04x\n",
			pdev->irq, base, dev->chiprev);
	ep_info(dev, "version: " DRIVER_VERSION "; %s\n",
		dev->enhanced_mode ? "enhanced mode" : "legacy mode");
	retval = device_create_file(&pdev->dev, &dev_attr_रेजिस्टरs);
	अगर (retval)
		जाओ करोne;

	retval = usb_add_gadget(&dev->gadget);
	अगर (retval)
		जाओ करोne;
	dev->added = 1;
	वापस 0;

करोne:
	अगर (dev) अणु
		net2280_हटाओ(pdev);
		kमुक्त(dev);
	पूर्ण
	वापस retval;
पूर्ण

/* make sure the board is quiescent; otherwise it will जारी
 * generating IRQs across the upcoming reboot.
 */

अटल व्योम net2280_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net2280		*dev = pci_get_drvdata(pdev);

	/* disable IRQs */
	ग_लिखोl(0, &dev->regs->pciirqenb0);
	ग_लिखोl(0, &dev->regs->pciirqenb1);

	/* disable the pullup so the host will think we're gone */
	ग_लिखोl(0, &dev->usb->usbctl);

पूर्ण


/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु अणु
	.class =	PCI_CLASS_SERIAL_USB_DEVICE,
	.class_mask =	~0,
	.venकरोr =	PCI_VENDOR_ID_PLX_LEGACY,
	.device =	0x2280,
	.subvenकरोr =	PCI_ANY_ID,
	.subdevice =	PCI_ANY_ID,
	.driver_data =	PLX_LEGACY | PLX_2280,
	पूर्ण, अणु
	.class =	PCI_CLASS_SERIAL_USB_DEVICE,
	.class_mask =	~0,
	.venकरोr =	PCI_VENDOR_ID_PLX_LEGACY,
	.device =	0x2282,
	.subvenकरोr =	PCI_ANY_ID,
	.subdevice =	PCI_ANY_ID,
	.driver_data =	PLX_LEGACY,
	पूर्ण,
	अणु
	.class =	PCI_CLASS_SERIAL_USB_DEVICE,
	.class_mask =	~0,
	.venकरोr =	PCI_VENDOR_ID_PLX,
	.device =	0x2380,
	.subvenकरोr =	PCI_ANY_ID,
	.subdevice =	PCI_ANY_ID,
	.driver_data =	PLX_PCIE,
	 पूर्ण,
	अणु
	.class =	((PCI_CLASS_SERIAL_USB << 8) | 0xfe),
	.class_mask =	~0,
	.venकरोr =	PCI_VENDOR_ID_PLX,
	.device =	0x3380,
	.subvenकरोr =	PCI_ANY_ID,
	.subdevice =	PCI_ANY_ID,
	.driver_data =	PLX_PCIE | PLX_SUPERSPEED,
	 पूर्ण,
	अणु
	.class =	PCI_CLASS_SERIAL_USB_DEVICE,
	.class_mask =	~0,
	.venकरोr =	PCI_VENDOR_ID_PLX,
	.device =	0x3382,
	.subvenकरोr =	PCI_ANY_ID,
	.subdevice =	PCI_ANY_ID,
	.driver_data =	PLX_PCIE | PLX_SUPERSPEED,
	 पूर्ण,
अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);

/* pci driver glue; this is a "new style" PCI driver module */
अटल काष्ठा pci_driver net2280_pci_driver = अणु
	.name =		driver_name,
	.id_table =	pci_ids,

	.probe =	net2280_probe,
	.हटाओ =	net2280_हटाओ,
	.shutकरोwn =	net2280_shutकरोwn,

	/* FIXME add घातer management support */
पूर्ण;

module_pci_driver(net2280_pci_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("David Brownell");
MODULE_LICENSE("GPL");
