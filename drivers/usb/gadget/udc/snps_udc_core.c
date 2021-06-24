<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * amd5536.c -- AMD 5536 UDC high/full speed USB device controller
 *
 * Copyright (C) 2005-2007 AMD (https://www.amd.com)
 * Author: Thomas Dahlmann
 */

/*
 * This file करोes the core driver implementation क्रम the UDC that is based
 * on Synopsys device controller IP (dअगरferent than HS OTG IP) that is either
 * connected through PCI bus or पूर्णांकegrated to SoC platक्रमms.
 */

/* Driver strings */
#घोषणा UDC_MOD_DESCRIPTION		"Synopsys USB Device Controller"
#घोषणा UDC_DRIVER_VERSION_STRING	"01.00.0206"

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/fs.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/moduleparam.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "amd5536udc.h"

अटल व्योम udc_setup_endpoपूर्णांकs(काष्ठा udc *dev);
अटल व्योम udc_soft_reset(काष्ठा udc *dev);
अटल काष्ठा udc_request *udc_alloc_bna_dummy(काष्ठा udc_ep *ep);
अटल व्योम udc_मुक्त_request(काष्ठा usb_ep *usbep, काष्ठा usb_request *usbreq);

/* description */
अटल स्थिर अक्षर mod_desc[] = UDC_MOD_DESCRIPTION;
अटल स्थिर अक्षर name[] = "udc";

/* काष्ठाure to hold endpoपूर्णांक function poपूर्णांकers */
अटल स्थिर काष्ठा usb_ep_ops udc_ep_ops;

/* received setup data */
अटल जोड़ udc_setup_data setup_data;

/* poपूर्णांकer to device object */
अटल काष्ठा udc *udc;

/* irq spin lock क्रम soft reset */
अटल DEFINE_SPINLOCK(udc_irq_spinlock);
/* stall spin lock */
अटल DEFINE_SPINLOCK(udc_stall_spinlock);

/*
* slave mode: pending bytes in rx fअगरo after nyet,
* used अगर EPIN irq came but no req was available
*/
अटल अचिन्हित पूर्णांक udc_rxfअगरo_pending;

/* count soft resets after suspend to aव्योम loop */
अटल पूर्णांक soft_reset_occured;
अटल पूर्णांक soft_reset_after_usbreset_occured;

/* समयr */
अटल काष्ठा समयr_list udc_समयr;
अटल पूर्णांक stop_समयr;

/* set_rde -- Is used to control enabling of RX DMA. Problem is
 * that UDC has only one bit (RDE) to enable/disable RX DMA क्रम
 * all OUT endpoपूर्णांकs. So we have to handle race conditions like
 * when OUT data reaches the fअगरo but no request was queued yet.
 * This cannot be solved by letting the RX DMA disabled until a
 * request माला_लो queued because there may be other OUT packets
 * in the FIFO (important क्रम not blocking control traffic).
 * The value of set_rde controls the correspondig समयr.
 *
 * set_rde -1 == not used, means it is alloed to be set to 0 or 1
 * set_rde  0 == करो not touch RDE, करो no start the RDE समयr
 * set_rde  1 == समयr function will look whether FIFO has data
 * set_rde  2 == set by समयr function to enable RX DMA on next call
 */
अटल पूर्णांक set_rde = -1;

अटल DECLARE_COMPLETION(on_निकास);
अटल काष्ठा समयr_list udc_pollstall_समयr;
अटल पूर्णांक stop_pollstall_समयr;
अटल DECLARE_COMPLETION(on_pollstall_निकास);

/* endpoपूर्णांक names used क्रम prपूर्णांक */
अटल स्थिर अक्षर ep0_string[] = "ep0in";
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा usb_ep_caps caps;
पूर्ण ep_info[] = अणु
#घोषणा EP_INFO(_name, _caps) \
	अणु \
		.name = _name, \
		.caps = _caps, \
	पूर्ण

	EP_INFO(ep0_string,
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep1in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep2in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep3in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep4in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep5in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep6in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep7in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep8in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep9in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep10in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep11in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep12in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep13in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep14in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep15in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep0out",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep1out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep2out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep3out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep4out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep5out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep6out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep7out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep8out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep9out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep10out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep11out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep12out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep13out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep14out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep15out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),

#अघोषित EP_INFO
पूर्ण;

/* buffer fill mode */
अटल पूर्णांक use_dma_bufferfill_mode;
/* tx buffer size क्रम high speed */
अटल अचिन्हित दीर्घ hs_tx_buf = UDC_EPIN_BUFF_SIZE;

/*---------------------------------------------------------------------------*/
/* Prपूर्णांकs UDC device रेजिस्टरs and endpoपूर्णांक irq रेजिस्टरs */
अटल व्योम prपूर्णांक_regs(काष्ठा udc *dev)
अणु
	DBG(dev, "------- Device registers -------\n");
	DBG(dev, "dev config     = %08x\n", पढ़ोl(&dev->regs->cfg));
	DBG(dev, "dev control    = %08x\n", पढ़ोl(&dev->regs->ctl));
	DBG(dev, "dev status     = %08x\n", पढ़ोl(&dev->regs->sts));
	DBG(dev, "\n");
	DBG(dev, "dev int's      = %08x\n", पढ़ोl(&dev->regs->irqsts));
	DBG(dev, "dev intmask    = %08x\n", पढ़ोl(&dev->regs->irqmsk));
	DBG(dev, "\n");
	DBG(dev, "dev ep int's   = %08x\n", पढ़ोl(&dev->regs->ep_irqsts));
	DBG(dev, "dev ep intmask = %08x\n", पढ़ोl(&dev->regs->ep_irqmsk));
	DBG(dev, "\n");
	DBG(dev, "USE DMA        = %d\n", use_dma);
	अगर (use_dma && use_dma_ppb && !use_dma_ppb_du) अणु
		DBG(dev, "DMA mode       = PPBNDU (packet per buffer "
			"WITHOUT desc. update)\n");
		dev_info(dev->dev, "DMA mode (%s)\n", "PPBNDU");
	पूर्ण अन्यथा अगर (use_dma && use_dma_ppb && use_dma_ppb_du) अणु
		DBG(dev, "DMA mode       = PPBDU (packet per buffer "
			"WITH desc. update)\n");
		dev_info(dev->dev, "DMA mode (%s)\n", "PPBDU");
	पूर्ण
	अगर (use_dma && use_dma_bufferfill_mode) अणु
		DBG(dev, "DMA mode       = BF (buffer fill mode)\n");
		dev_info(dev->dev, "DMA mode (%s)\n", "BF");
	पूर्ण
	अगर (!use_dma)
		dev_info(dev->dev, "FIFO mode\n");
	DBG(dev, "-------------------------------------------------------\n");
पूर्ण

/* Masks unused पूर्णांकerrupts */
पूर्णांक udc_mask_unused_पूर्णांकerrupts(काष्ठा udc *dev)
अणु
	u32 पंचांगp;

	/* mask all dev पूर्णांकerrupts */
	पंचांगp =	AMD_BIT(UDC_DEVINT_SVC) |
		AMD_BIT(UDC_DEVINT_ENUM) |
		AMD_BIT(UDC_DEVINT_US) |
		AMD_BIT(UDC_DEVINT_UR) |
		AMD_BIT(UDC_DEVINT_ES) |
		AMD_BIT(UDC_DEVINT_SI) |
		AMD_BIT(UDC_DEVINT_SOF)|
		AMD_BIT(UDC_DEVINT_SC);
	ग_लिखोl(पंचांगp, &dev->regs->irqmsk);

	/* mask all ep पूर्णांकerrupts */
	ग_लिखोl(UDC_EPINT_MSK_DISABLE_ALL, &dev->regs->ep_irqmsk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(udc_mask_unused_पूर्णांकerrupts);

/* Enables endpoपूर्णांक 0 पूर्णांकerrupts */
अटल पूर्णांक udc_enable_ep0_पूर्णांकerrupts(काष्ठा udc *dev)
अणु
	u32 पंचांगp;

	DBG(dev, "udc_enable_ep0_interrupts()\n");

	/* पढ़ो irq mask */
	पंचांगp = पढ़ोl(&dev->regs->ep_irqmsk);
	/* enable ep0 irq's */
	पंचांगp &= AMD_UNMASK_BIT(UDC_EPINT_IN_EP0)
		& AMD_UNMASK_BIT(UDC_EPINT_OUT_EP0);
	ग_लिखोl(पंचांगp, &dev->regs->ep_irqmsk);

	वापस 0;
पूर्ण

/* Enables device पूर्णांकerrupts क्रम SET_INTF and SET_CONFIG */
पूर्णांक udc_enable_dev_setup_पूर्णांकerrupts(काष्ठा udc *dev)
अणु
	u32 पंचांगp;

	DBG(dev, "enable device interrupts for setup data\n");

	/* पढ़ो irq mask */
	पंचांगp = पढ़ोl(&dev->regs->irqmsk);

	/* enable SET_INTERFACE, SET_CONFIG and other needed irq's */
	पंचांगp &= AMD_UNMASK_BIT(UDC_DEVINT_SI)
		& AMD_UNMASK_BIT(UDC_DEVINT_SC)
		& AMD_UNMASK_BIT(UDC_DEVINT_UR)
		& AMD_UNMASK_BIT(UDC_DEVINT_SVC)
		& AMD_UNMASK_BIT(UDC_DEVINT_ENUM);
	ग_लिखोl(पंचांगp, &dev->regs->irqmsk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(udc_enable_dev_setup_पूर्णांकerrupts);

/* Calculates fअगरo start of endpoपूर्णांक based on preceding endpoपूर्णांकs */
अटल पूर्णांक udc_set_txfअगरo_addr(काष्ठा udc_ep *ep)
अणु
	काष्ठा udc	*dev;
	u32 पंचांगp;
	पूर्णांक i;

	अगर (!ep || !(ep->in))
		वापस -EINVAL;

	dev = ep->dev;
	ep->txfअगरo = dev->txfअगरo;

	/* traverse ep's */
	क्रम (i = 0; i < ep->num; i++) अणु
		अगर (dev->ep[i].regs) अणु
			/* पढ़ो fअगरo size */
			पंचांगp = पढ़ोl(&dev->ep[i].regs->bufin_framक्रमागत);
			पंचांगp = AMD_GETBITS(पंचांगp, UDC_EPIN_BUFF_SIZE);
			ep->txfअगरo += पंचांगp;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* CNAK pending field: bit0 = ep0in, bit16 = ep0out */
अटल u32 cnak_pending;

अटल व्योम UDC_QUEUE_CNAK(काष्ठा udc_ep *ep, अचिन्हित num)
अणु
	अगर (पढ़ोl(&ep->regs->ctl) & AMD_BIT(UDC_EPCTL_NAK)) अणु
		DBG(ep->dev, "NAK could not be cleared for ep%d\n", num);
		cnak_pending |= 1 << (num);
		ep->naking = 1;
	पूर्ण अन्यथा
		cnak_pending = cnak_pending & (~(1 << (num)));
पूर्ण


/* Enables endpoपूर्णांक, is called by gadget driver */
अटल पूर्णांक
udc_ep_enable(काष्ठा usb_ep *usbep, स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा udc_ep		*ep;
	काष्ठा udc		*dev;
	u32			पंचांगp;
	अचिन्हित दीर्घ		अगरlags;
	u8 udc_csr_epix;
	अचिन्हित		maxpacket;

	अगर (!usbep
			|| usbep->name == ep0_string
			|| !desc
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;

	ep = container_of(usbep, काष्ठा udc_ep, ep);
	dev = ep->dev;

	DBG(dev, "udc_ep_enable() ep %d\n", ep->num);

	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&dev->lock, अगरlags);
	ep->ep.desc = desc;

	ep->halted = 0;

	/* set traffic type */
	पंचांगp = पढ़ोl(&dev->ep[ep->num].regs->ctl);
	पंचांगp = AMD_ADDBITS(पंचांगp, desc->bmAttributes, UDC_EPCTL_ET);
	ग_लिखोl(पंचांगp, &dev->ep[ep->num].regs->ctl);

	/* set max packet size */
	maxpacket = usb_endpoपूर्णांक_maxp(desc);
	पंचांगp = पढ़ोl(&dev->ep[ep->num].regs->bufout_maxpkt);
	पंचांगp = AMD_ADDBITS(पंचांगp, maxpacket, UDC_EP_MAX_PKT_SIZE);
	ep->ep.maxpacket = maxpacket;
	ग_लिखोl(पंचांगp, &dev->ep[ep->num].regs->bufout_maxpkt);

	/* IN ep */
	अगर (ep->in) अणु

		/* ep ix in UDC CSR रेजिस्टर space */
		udc_csr_epix = ep->num;

		/* set buffer size (tx fअगरo entries) */
		पंचांगp = पढ़ोl(&dev->ep[ep->num].regs->bufin_framक्रमागत);
		/* द्विगुन buffering: fअगरo size = 2 x max packet size */
		पंचांगp = AMD_ADDBITS(
				पंचांगp,
				maxpacket * UDC_EPIN_BUFF_SIZE_MULT
					  / UDC_DWORD_BYTES,
				UDC_EPIN_BUFF_SIZE);
		ग_लिखोl(पंचांगp, &dev->ep[ep->num].regs->bufin_framक्रमागत);

		/* calc. tx fअगरo base addr */
		udc_set_txfअगरo_addr(ep);

		/* flush fअगरo */
		पंचांगp = पढ़ोl(&ep->regs->ctl);
		पंचांगp |= AMD_BIT(UDC_EPCTL_F);
		ग_लिखोl(पंचांगp, &ep->regs->ctl);

	/* OUT ep */
	पूर्ण अन्यथा अणु
		/* ep ix in UDC CSR रेजिस्टर space */
		udc_csr_epix = ep->num - UDC_CSR_EP_OUT_IX_OFS;

		/* set max packet size UDC CSR	*/
		पंचांगp = पढ़ोl(&dev->csr->ne[ep->num - UDC_CSR_EP_OUT_IX_OFS]);
		पंचांगp = AMD_ADDBITS(पंचांगp, maxpacket,
					UDC_CSR_NE_MAX_PKT);
		ग_लिखोl(पंचांगp, &dev->csr->ne[ep->num - UDC_CSR_EP_OUT_IX_OFS]);

		अगर (use_dma && !ep->in) अणु
			/* alloc and init BNA dummy request */
			ep->bna_dummy_req = udc_alloc_bna_dummy(ep);
			ep->bna_occurred = 0;
		पूर्ण

		अगर (ep->num != UDC_EP0OUT_IX)
			dev->data_ep_enabled = 1;
	पूर्ण

	/* set ep values */
	पंचांगp = पढ़ोl(&dev->csr->ne[udc_csr_epix]);
	/* max packet */
	पंचांगp = AMD_ADDBITS(पंचांगp, maxpacket, UDC_CSR_NE_MAX_PKT);
	/* ep number */
	पंचांगp = AMD_ADDBITS(पंचांगp, desc->bEndpoपूर्णांकAddress, UDC_CSR_NE_NUM);
	/* ep direction */
	पंचांगp = AMD_ADDBITS(पंचांगp, ep->in, UDC_CSR_NE_सूची);
	/* ep type */
	पंचांगp = AMD_ADDBITS(पंचांगp, desc->bmAttributes, UDC_CSR_NE_TYPE);
	/* ep config */
	पंचांगp = AMD_ADDBITS(पंचांगp, ep->dev->cur_config, UDC_CSR_NE_CFG);
	/* ep पूर्णांकerface */
	पंचांगp = AMD_ADDBITS(पंचांगp, ep->dev->cur_पूर्णांकf, UDC_CSR_NE_INTF);
	/* ep alt */
	पंचांगp = AMD_ADDBITS(पंचांगp, ep->dev->cur_alt, UDC_CSR_NE_ALT);
	/* ग_लिखो reg */
	ग_लिखोl(पंचांगp, &dev->csr->ne[udc_csr_epix]);

	/* enable ep irq */
	पंचांगp = पढ़ोl(&dev->regs->ep_irqmsk);
	पंचांगp &= AMD_UNMASK_BIT(ep->num);
	ग_लिखोl(पंचांगp, &dev->regs->ep_irqmsk);

	/*
	 * clear NAK by writing CNAK
	 * aव्योम BNA क्रम OUT DMA, करोn't clear NAK until DMA desc. written
	 */
	अगर (!use_dma || ep->in) अणु
		पंचांगp = पढ़ोl(&ep->regs->ctl);
		पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
		ग_लिखोl(पंचांगp, &ep->regs->ctl);
		ep->naking = 0;
		UDC_QUEUE_CNAK(ep, ep->num);
	पूर्ण
	पंचांगp = desc->bEndpoपूर्णांकAddress;
	DBG(dev, "%s enabled\n", usbep->name);

	spin_unlock_irqrestore(&dev->lock, अगरlags);
	वापस 0;
पूर्ण

/* Resets endpoपूर्णांक */
अटल व्योम ep_init(काष्ठा udc_regs __iomem *regs, काष्ठा udc_ep *ep)
अणु
	u32		पंचांगp;

	VDBG(ep->dev, "ep-%d reset\n", ep->num);
	ep->ep.desc = शून्य;
	ep->ep.ops = &udc_ep_ops;
	INIT_LIST_HEAD(&ep->queue);

	usb_ep_set_maxpacket_limit(&ep->ep,(u16) ~0);
	/* set NAK */
	पंचांगp = पढ़ोl(&ep->regs->ctl);
	पंचांगp |= AMD_BIT(UDC_EPCTL_SNAK);
	ग_लिखोl(पंचांगp, &ep->regs->ctl);
	ep->naking = 1;

	/* disable पूर्णांकerrupt */
	पंचांगp = पढ़ोl(&regs->ep_irqmsk);
	पंचांगp |= AMD_BIT(ep->num);
	ग_लिखोl(पंचांगp, &regs->ep_irqmsk);

	अगर (ep->in) अणु
		/* unset P and IN bit of potential क्रमmer DMA */
		पंचांगp = पढ़ोl(&ep->regs->ctl);
		पंचांगp &= AMD_UNMASK_BIT(UDC_EPCTL_P);
		ग_लिखोl(पंचांगp, &ep->regs->ctl);

		पंचांगp = पढ़ोl(&ep->regs->sts);
		पंचांगp |= AMD_BIT(UDC_EPSTS_IN);
		ग_लिखोl(पंचांगp, &ep->regs->sts);

		/* flush the fअगरo */
		पंचांगp = पढ़ोl(&ep->regs->ctl);
		पंचांगp |= AMD_BIT(UDC_EPCTL_F);
		ग_लिखोl(पंचांगp, &ep->regs->ctl);

	पूर्ण
	/* reset desc poपूर्णांकer */
	ग_लिखोl(0, &ep->regs->desptr);
पूर्ण

/* Disables endpoपूर्णांक, is called by gadget driver */
अटल पूर्णांक udc_ep_disable(काष्ठा usb_ep *usbep)
अणु
	काष्ठा udc_ep	*ep = शून्य;
	अचिन्हित दीर्घ	अगरlags;

	अगर (!usbep)
		वापस -EINVAL;

	ep = container_of(usbep, काष्ठा udc_ep, ep);
	अगर (usbep->name == ep0_string || !ep->ep.desc)
		वापस -EINVAL;

	DBG(ep->dev, "Disable ep-%d\n", ep->num);

	spin_lock_irqsave(&ep->dev->lock, अगरlags);
	udc_मुक्त_request(&ep->ep, &ep->bna_dummy_req->req);
	empty_req_queue(ep);
	ep_init(ep->dev->regs, ep);
	spin_unlock_irqrestore(&ep->dev->lock, अगरlags);

	वापस 0;
पूर्ण

/* Allocates request packet, called by gadget driver */
अटल काष्ठा usb_request *
udc_alloc_request(काष्ठा usb_ep *usbep, gfp_t gfp)
अणु
	काष्ठा udc_request	*req;
	काष्ठा udc_data_dma	*dma_desc;
	काष्ठा udc_ep	*ep;

	अगर (!usbep)
		वापस शून्य;

	ep = container_of(usbep, काष्ठा udc_ep, ep);

	VDBG(ep->dev, "udc_alloc_req(): ep%d\n", ep->num);
	req = kzalloc(माप(काष्ठा udc_request), gfp);
	अगर (!req)
		वापस शून्य;

	req->req.dma = DMA_DONT_USE;
	INIT_LIST_HEAD(&req->queue);

	अगर (ep->dma) अणु
		/* ep0 in requests are allocated from data pool here */
		dma_desc = dma_pool_alloc(ep->dev->data_requests, gfp,
						&req->td_phys);
		अगर (!dma_desc) अणु
			kमुक्त(req);
			वापस शून्य;
		पूर्ण

		VDBG(ep->dev, "udc_alloc_req: req = %p dma_desc = %p, "
				"td_phys = %lx\n",
				req, dma_desc,
				(अचिन्हित दीर्घ)req->td_phys);
		/* prevent from using desc. - set HOST BUSY */
		dma_desc->status = AMD_ADDBITS(dma_desc->status,
						UDC_DMA_STP_STS_BS_HOST_BUSY,
						UDC_DMA_STP_STS_BS);
		dma_desc->bufptr = cpu_to_le32(DMA_DONT_USE);
		req->td_data = dma_desc;
		req->td_data_last = शून्य;
		req->chain_len = 1;
	पूर्ण

	वापस &req->req;
पूर्ण

/* मुक्तs pci pool descriptors of a DMA chain */
अटल व्योम udc_मुक्त_dma_chain(काष्ठा udc *dev, काष्ठा udc_request *req)
अणु
	काष्ठा udc_data_dma *td = req->td_data;
	अचिन्हित पूर्णांक i;

	dma_addr_t addr_next = 0x00;
	dma_addr_t addr = (dma_addr_t)td->next;

	DBG(dev, "free chain req = %p\n", req);

	/* करो not मुक्त first desc., will be करोne by मुक्त क्रम request */
	क्रम (i = 1; i < req->chain_len; i++) अणु
		td = phys_to_virt(addr);
		addr_next = (dma_addr_t)td->next;
		dma_pool_मुक्त(dev->data_requests, td, addr);
		addr = addr_next;
	पूर्ण
पूर्ण

/* Frees request packet, called by gadget driver */
अटल व्योम
udc_मुक्त_request(काष्ठा usb_ep *usbep, काष्ठा usb_request *usbreq)
अणु
	काष्ठा udc_ep	*ep;
	काष्ठा udc_request	*req;

	अगर (!usbep || !usbreq)
		वापस;

	ep = container_of(usbep, काष्ठा udc_ep, ep);
	req = container_of(usbreq, काष्ठा udc_request, req);
	VDBG(ep->dev, "free_req req=%p\n", req);
	BUG_ON(!list_empty(&req->queue));
	अगर (req->td_data) अणु
		VDBG(ep->dev, "req->td_data=%p\n", req->td_data);

		/* मुक्त dma chain अगर created */
		अगर (req->chain_len > 1)
			udc_मुक्त_dma_chain(ep->dev, req);

		dma_pool_मुक्त(ep->dev->data_requests, req->td_data,
							req->td_phys);
	पूर्ण
	kमुक्त(req);
पूर्ण

/* Init BNA dummy descriptor क्रम HOST BUSY and poपूर्णांकing to itself */
अटल व्योम udc_init_bna_dummy(काष्ठा udc_request *req)
अणु
	अगर (req) अणु
		/* set last bit */
		req->td_data->status |= AMD_BIT(UDC_DMA_IN_STS_L);
		/* set next poपूर्णांकer to itself */
		req->td_data->next = req->td_phys;
		/* set HOST BUSY */
		req->td_data->status
			= AMD_ADDBITS(req->td_data->status,
					UDC_DMA_STP_STS_BS_DMA_DONE,
					UDC_DMA_STP_STS_BS);
#अगर_घोषित UDC_VERBOSE
		pr_debug("bna desc = %p, sts = %08x\n",
			req->td_data, req->td_data->status);
#पूर्ण_अगर
	पूर्ण
पूर्ण

/* Allocate BNA dummy descriptor */
अटल काष्ठा udc_request *udc_alloc_bna_dummy(काष्ठा udc_ep *ep)
अणु
	काष्ठा udc_request *req = शून्य;
	काष्ठा usb_request *_req = शून्य;

	/* alloc the dummy request */
	_req = udc_alloc_request(&ep->ep, GFP_ATOMIC);
	अगर (_req) अणु
		req = container_of(_req, काष्ठा udc_request, req);
		ep->bna_dummy_req = req;
		udc_init_bna_dummy(req);
	पूर्ण
	वापस req;
पूर्ण

/* Write data to TX fअगरo क्रम IN packets */
अटल व्योम
udc_txfअगरo_ग_लिखो(काष्ठा udc_ep *ep, काष्ठा usb_request *req)
अणु
	u8			*req_buf;
	u32			*buf;
	पूर्णांक			i, j;
	अचिन्हित		bytes = 0;
	अचिन्हित		reमुख्यing = 0;

	अगर (!req || !ep)
		वापस;

	req_buf = req->buf + req->actual;
	prefetch(req_buf);
	reमुख्यing = req->length - req->actual;

	buf = (u32 *) req_buf;

	bytes = ep->ep.maxpacket;
	अगर (bytes > reमुख्यing)
		bytes = reमुख्यing;

	/* dwords first */
	क्रम (i = 0; i < bytes / UDC_DWORD_BYTES; i++)
		ग_लिखोl(*(buf + i), ep->txfअगरo);

	/* reमुख्यing bytes must be written by byte access */
	क्रम (j = 0; j < bytes % UDC_DWORD_BYTES; j++) अणु
		ग_लिखोb((u8)(*(buf + i) >> (j << UDC_BITS_PER_BYTE_SHIFT)),
							ep->txfअगरo);
	पूर्ण

	/* dummy ग_लिखो confirm */
	ग_लिखोl(0, &ep->regs->confirm);
पूर्ण

/* Read dwords from RX fअगरo क्रम OUT transfers */
अटल पूर्णांक udc_rxfअगरo_पढ़ो_dwords(काष्ठा udc *dev, u32 *buf, पूर्णांक dwords)
अणु
	पूर्णांक i;

	VDBG(dev, "udc_read_dwords(): %d dwords\n", dwords);

	क्रम (i = 0; i < dwords; i++)
		*(buf + i) = पढ़ोl(dev->rxfअगरo);
	वापस 0;
पूर्ण

/* Read bytes from RX fअगरo क्रम OUT transfers */
अटल पूर्णांक udc_rxfअगरo_पढ़ो_bytes(काष्ठा udc *dev, u8 *buf, पूर्णांक bytes)
अणु
	पूर्णांक i, j;
	u32 पंचांगp;

	VDBG(dev, "udc_read_bytes(): %d bytes\n", bytes);

	/* dwords first */
	क्रम (i = 0; i < bytes / UDC_DWORD_BYTES; i++)
		*((u32 *)(buf + (i<<2))) = पढ़ोl(dev->rxfअगरo);

	/* reमुख्यing bytes must be पढ़ो by byte access */
	अगर (bytes % UDC_DWORD_BYTES) अणु
		पंचांगp = पढ़ोl(dev->rxfअगरo);
		क्रम (j = 0; j < bytes % UDC_DWORD_BYTES; j++) अणु
			*(buf + (i<<2) + j) = (u8)(पंचांगp & UDC_BYTE_MASK);
			पंचांगp = पंचांगp >> UDC_BITS_PER_BYTE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Read data from RX fअगरo क्रम OUT transfers */
अटल पूर्णांक
udc_rxfअगरo_पढ़ो(काष्ठा udc_ep *ep, काष्ठा udc_request *req)
अणु
	u8 *buf;
	अचिन्हित buf_space;
	अचिन्हित bytes = 0;
	अचिन्हित finished = 0;

	/* received number bytes */
	bytes = पढ़ोl(&ep->regs->sts);
	bytes = AMD_GETBITS(bytes, UDC_EPSTS_RX_PKT_SIZE);

	buf_space = req->req.length - req->req.actual;
	buf = req->req.buf + req->req.actual;
	अगर (bytes > buf_space) अणु
		अगर ((buf_space % ep->ep.maxpacket) != 0) अणु
			DBG(ep->dev,
				"%s: rx %d bytes, rx-buf space = %d bytesn\n",
				ep->ep.name, bytes, buf_space);
			req->req.status = -EOVERFLOW;
		पूर्ण
		bytes = buf_space;
	पूर्ण
	req->req.actual += bytes;

	/* last packet ? */
	अगर (((bytes % ep->ep.maxpacket) != 0) || (!bytes)
		|| ((req->req.actual == req->req.length) && !req->req.zero))
		finished = 1;

	/* पढ़ो rx fअगरo bytes */
	VDBG(ep->dev, "ep %s: rxfifo read %d bytes\n", ep->ep.name, bytes);
	udc_rxfअगरo_पढ़ो_bytes(ep->dev, buf, bytes);

	वापस finished;
पूर्ण

/* Creates or re-inits a DMA chain */
अटल पूर्णांक udc_create_dma_chain(
	काष्ठा udc_ep *ep,
	काष्ठा udc_request *req,
	अचिन्हित दीर्घ buf_len, gfp_t gfp_flags
)
अणु
	अचिन्हित दीर्घ bytes = req->req.length;
	अचिन्हित पूर्णांक i;
	dma_addr_t dma_addr;
	काष्ठा udc_data_dma	*td = शून्य;
	काष्ठा udc_data_dma	*last = शून्य;
	अचिन्हित दीर्घ txbytes;
	अचिन्हित create_new_chain = 0;
	अचिन्हित len;

	VDBG(ep->dev, "udc_create_dma_chain: bytes=%ld buf_len=%ld\n",
	     bytes, buf_len);
	dma_addr = DMA_DONT_USE;

	/* unset L bit in first desc क्रम OUT */
	अगर (!ep->in)
		req->td_data->status &= AMD_CLEAR_BIT(UDC_DMA_IN_STS_L);

	/* alloc only new desc's अगर not alपढ़ोy available */
	len = req->req.length / ep->ep.maxpacket;
	अगर (req->req.length % ep->ep.maxpacket)
		len++;

	अगर (len > req->chain_len) अणु
		/* लघुer chain alपढ़ोy allocated beक्रमe */
		अगर (req->chain_len > 1)
			udc_मुक्त_dma_chain(ep->dev, req);
		req->chain_len = len;
		create_new_chain = 1;
	पूर्ण

	td = req->td_data;
	/* gen. required number of descriptors and buffers */
	क्रम (i = buf_len; i < bytes; i += buf_len) अणु
		/* create or determine next desc. */
		अगर (create_new_chain) अणु
			td = dma_pool_alloc(ep->dev->data_requests,
					    gfp_flags, &dma_addr);
			अगर (!td)
				वापस -ENOMEM;

			td->status = 0;
		पूर्ण अन्यथा अगर (i == buf_len) अणु
			/* first td */
			td = (काष्ठा udc_data_dma *)phys_to_virt(
						req->td_data->next);
			td->status = 0;
		पूर्ण अन्यथा अणु
			td = (काष्ठा udc_data_dma *)phys_to_virt(last->next);
			td->status = 0;
		पूर्ण

		अगर (td)
			td->bufptr = req->req.dma + i; /* assign buffer */
		अन्यथा
			अवरोध;

		/* लघु packet ? */
		अगर ((bytes - i) >= buf_len) अणु
			txbytes = buf_len;
		पूर्ण अन्यथा अणु
			/* लघु packet */
			txbytes = bytes - i;
		पूर्ण

		/* link td and assign tx bytes */
		अगर (i == buf_len) अणु
			अगर (create_new_chain)
				req->td_data->next = dma_addr;
			/*
			 * अन्यथा
			 *	req->td_data->next = virt_to_phys(td);
			 */
			/* ग_लिखो tx bytes */
			अगर (ep->in) अणु
				/* first desc */
				req->td_data->status =
					AMD_ADDBITS(req->td_data->status,
						    ep->ep.maxpacket,
						    UDC_DMA_IN_STS_TXBYTES);
				/* second desc */
				td->status = AMD_ADDBITS(td->status,
							txbytes,
							UDC_DMA_IN_STS_TXBYTES);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (create_new_chain)
				last->next = dma_addr;
			/*
			 * अन्यथा
			 *	last->next = virt_to_phys(td);
			 */
			अगर (ep->in) अणु
				/* ग_लिखो tx bytes */
				td->status = AMD_ADDBITS(td->status,
							txbytes,
							UDC_DMA_IN_STS_TXBYTES);
			पूर्ण
		पूर्ण
		last = td;
	पूर्ण
	/* set last bit */
	अगर (td) अणु
		td->status |= AMD_BIT(UDC_DMA_IN_STS_L);
		/* last desc. poपूर्णांकs to itself */
		req->td_data_last = td;
	पूर्ण

	वापस 0;
पूर्ण

/* create/re-init a DMA descriptor or a DMA descriptor chain */
अटल पूर्णांक prep_dma(काष्ठा udc_ep *ep, काष्ठा udc_request *req, gfp_t gfp)
अणु
	पूर्णांक	retval = 0;
	u32	पंचांगp;

	VDBG(ep->dev, "prep_dma\n");
	VDBG(ep->dev, "prep_dma ep%d req->td_data=%p\n",
			ep->num, req->td_data);

	/* set buffer poपूर्णांकer */
	req->td_data->bufptr = req->req.dma;

	/* set last bit */
	req->td_data->status |= AMD_BIT(UDC_DMA_IN_STS_L);

	/* build/re-init dma chain अगर maxpkt scatter mode, not क्रम EP0 */
	अगर (use_dma_ppb) अणु

		retval = udc_create_dma_chain(ep, req, ep->ep.maxpacket, gfp);
		अगर (retval != 0) अणु
			अगर (retval == -ENOMEM)
				DBG(ep->dev, "Out of DMA memory\n");
			वापस retval;
		पूर्ण
		अगर (ep->in) अणु
			अगर (req->req.length == ep->ep.maxpacket) अणु
				/* ग_लिखो tx bytes */
				req->td_data->status =
					AMD_ADDBITS(req->td_data->status,
						ep->ep.maxpacket,
						UDC_DMA_IN_STS_TXBYTES);

			पूर्ण
		पूर्ण

	पूर्ण

	अगर (ep->in) अणु
		VDBG(ep->dev, "IN: use_dma_ppb=%d req->req.len=%d "
				"maxpacket=%d ep%d\n",
				use_dma_ppb, req->req.length,
				ep->ep.maxpacket, ep->num);
		/*
		 * अगर bytes < max packet then tx bytes must
		 * be written in packet per buffer mode
		 */
		अगर (!use_dma_ppb || req->req.length < ep->ep.maxpacket
				|| ep->num == UDC_EP0OUT_IX
				|| ep->num == UDC_EP0IN_IX) अणु
			/* ग_लिखो tx bytes */
			req->td_data->status =
				AMD_ADDBITS(req->td_data->status,
						req->req.length,
						UDC_DMA_IN_STS_TXBYTES);
			/* reset frame num */
			req->td_data->status =
				AMD_ADDBITS(req->td_data->status,
						0,
						UDC_DMA_IN_STS_FRAMENUM);
		पूर्ण
		/* set HOST BUSY */
		req->td_data->status =
			AMD_ADDBITS(req->td_data->status,
				UDC_DMA_STP_STS_BS_HOST_BUSY,
				UDC_DMA_STP_STS_BS);
	पूर्ण अन्यथा अणु
		VDBG(ep->dev, "OUT set host ready\n");
		/* set HOST READY */
		req->td_data->status =
			AMD_ADDBITS(req->td_data->status,
				UDC_DMA_STP_STS_BS_HOST_READY,
				UDC_DMA_STP_STS_BS);

		/* clear NAK by writing CNAK */
		अगर (ep->naking) अणु
			पंचांगp = पढ़ोl(&ep->regs->ctl);
			पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
			ग_लिखोl(पंचांगp, &ep->regs->ctl);
			ep->naking = 0;
			UDC_QUEUE_CNAK(ep, ep->num);
		पूर्ण

	पूर्ण

	वापस retval;
पूर्ण

/* Completes request packet ... caller MUST hold lock */
अटल व्योम
complete_req(काष्ठा udc_ep *ep, काष्ठा udc_request *req, पूर्णांक sts)
__releases(ep->dev->lock)
__acquires(ep->dev->lock)
अणु
	काष्ठा udc		*dev;
	अचिन्हित		halted;

	VDBG(ep->dev, "complete_req(): ep%d\n", ep->num);

	dev = ep->dev;
	/* unmap DMA */
	अगर (ep->dma)
		usb_gadget_unmap_request(&dev->gadget, &req->req, ep->in);

	halted = ep->halted;
	ep->halted = 1;

	/* set new status अगर pending */
	अगर (req->req.status == -EINPROGRESS)
		req->req.status = sts;

	/* हटाओ from ep queue */
	list_del_init(&req->queue);

	VDBG(ep->dev, "req %p => complete %d bytes at %s with sts %d\n",
		&req->req, req->req.length, ep->ep.name, sts);

	spin_unlock(&dev->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&dev->lock);
	ep->halted = halted;
पूर्ण

/* Iterates to the end of a DMA chain and वापसs last descriptor */
अटल काष्ठा udc_data_dma *udc_get_last_dma_desc(काष्ठा udc_request *req)
अणु
	काष्ठा udc_data_dma	*td;

	td = req->td_data;
	जबतक (td && !(td->status & AMD_BIT(UDC_DMA_IN_STS_L)))
		td = phys_to_virt(td->next);

	वापस td;

पूर्ण

/* Iterates to the end of a DMA chain and counts bytes received */
अटल u32 udc_get_ppbdu_rxbytes(काष्ठा udc_request *req)
अणु
	काष्ठा udc_data_dma	*td;
	u32 count;

	td = req->td_data;
	/* received number bytes */
	count = AMD_GETBITS(td->status, UDC_DMA_OUT_STS_RXBYTES);

	जबतक (td && !(td->status & AMD_BIT(UDC_DMA_IN_STS_L))) अणु
		td = phys_to_virt(td->next);
		/* received number bytes */
		अगर (td) अणु
			count += AMD_GETBITS(td->status,
				UDC_DMA_OUT_STS_RXBYTES);
		पूर्ण
	पूर्ण

	वापस count;

पूर्ण

/* Enabling RX DMA */
अटल व्योम udc_set_rde(काष्ठा udc *dev)
अणु
	u32 पंचांगp;

	VDBG(dev, "udc_set_rde()\n");
	/* stop RDE समयr */
	अगर (समयr_pending(&udc_समयr)) अणु
		set_rde = 0;
		mod_समयr(&udc_समयr, jअगरfies - 1);
	पूर्ण
	/* set RDE */
	पंचांगp = पढ़ोl(&dev->regs->ctl);
	पंचांगp |= AMD_BIT(UDC_DEVCTL_RDE);
	ग_लिखोl(पंचांगp, &dev->regs->ctl);
पूर्ण

/* Queues a request packet, called by gadget driver */
अटल पूर्णांक
udc_queue(काष्ठा usb_ep *usbep, काष्ठा usb_request *usbreq, gfp_t gfp)
अणु
	पूर्णांक			retval = 0;
	u8			खोलो_rxfअगरo = 0;
	अचिन्हित दीर्घ		अगरlags;
	काष्ठा udc_ep		*ep;
	काष्ठा udc_request	*req;
	काष्ठा udc		*dev;
	u32			पंचांगp;

	/* check the inमाला_दो */
	req = container_of(usbreq, काष्ठा udc_request, req);

	अगर (!usbep || !usbreq || !usbreq->complete || !usbreq->buf
			|| !list_empty(&req->queue))
		वापस -EINVAL;

	ep = container_of(usbep, काष्ठा udc_ep, ep);
	अगर (!ep->ep.desc && (ep->num != 0 && ep->num != UDC_EP0OUT_IX))
		वापस -EINVAL;

	VDBG(ep->dev, "udc_queue(): ep%d-in=%d\n", ep->num, ep->in);
	dev = ep->dev;

	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	/* map dma (usually करोne beक्रमe) */
	अगर (ep->dma) अणु
		VDBG(dev, "DMA map req %p\n", req);
		retval = usb_gadget_map_request(&udc->gadget, usbreq, ep->in);
		अगर (retval)
			वापस retval;
	पूर्ण

	VDBG(dev, "%s queue req %p, len %d req->td_data=%p buf %p\n",
			usbep->name, usbreq, usbreq->length,
			req->td_data, usbreq->buf);

	spin_lock_irqsave(&dev->lock, अगरlags);
	usbreq->actual = 0;
	usbreq->status = -EINPROGRESS;
	req->dma_करोne = 0;

	/* on empty queue just करो first transfer */
	अगर (list_empty(&ep->queue)) अणु
		/* zlp */
		अगर (usbreq->length == 0) अणु
			/* IN zlp's are handled by hardware */
			complete_req(ep, req, 0);
			VDBG(dev, "%s: zlp\n", ep->ep.name);
			/*
			 * अगर set_config or set_पूर्णांकf is रुकोing क्रम ack by zlp
			 * then set CSR_DONE
			 */
			अगर (dev->set_cfg_not_acked) अणु
				पंचांगp = पढ़ोl(&dev->regs->ctl);
				पंचांगp |= AMD_BIT(UDC_DEVCTL_CSR_DONE);
				ग_लिखोl(पंचांगp, &dev->regs->ctl);
				dev->set_cfg_not_acked = 0;
			पूर्ण
			/* setup command is ACK'ed now by zlp */
			अगर (dev->रुकोing_zlp_ack_ep0in) अणु
				/* clear NAK by writing CNAK in EP0_IN */
				पंचांगp = पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->ctl);
				पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
				ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0IN_IX].regs->ctl);
				dev->ep[UDC_EP0IN_IX].naking = 0;
				UDC_QUEUE_CNAK(&dev->ep[UDC_EP0IN_IX],
							UDC_EP0IN_IX);
				dev->रुकोing_zlp_ack_ep0in = 0;
			पूर्ण
			जाओ finished;
		पूर्ण
		अगर (ep->dma) अणु
			retval = prep_dma(ep, req, GFP_ATOMIC);
			अगर (retval != 0)
				जाओ finished;
			/* ग_लिखो desc poपूर्णांकer to enable DMA */
			अगर (ep->in) अणु
				/* set HOST READY */
				req->td_data->status =
					AMD_ADDBITS(req->td_data->status,
						UDC_DMA_IN_STS_BS_HOST_READY,
						UDC_DMA_IN_STS_BS);
			पूर्ण

			/* disabled rx dma जबतक descriptor update */
			अगर (!ep->in) अणु
				/* stop RDE समयr */
				अगर (समयr_pending(&udc_समयr)) अणु
					set_rde = 0;
					mod_समयr(&udc_समयr, jअगरfies - 1);
				पूर्ण
				/* clear RDE */
				पंचांगp = पढ़ोl(&dev->regs->ctl);
				पंचांगp &= AMD_UNMASK_BIT(UDC_DEVCTL_RDE);
				ग_लिखोl(पंचांगp, &dev->regs->ctl);
				खोलो_rxfअगरo = 1;

				/*
				 * अगर BNA occurred then let BNA dummy desc.
				 * poपूर्णांक to current desc.
				 */
				अगर (ep->bna_occurred) अणु
					VDBG(dev, "copy to BNA dummy desc.\n");
					स_नकल(ep->bna_dummy_req->td_data,
						req->td_data,
						माप(काष्ठा udc_data_dma));
				पूर्ण
			पूर्ण
			/* ग_लिखो desc poपूर्णांकer */
			ग_लिखोl(req->td_phys, &ep->regs->desptr);

			/* clear NAK by writing CNAK */
			अगर (ep->naking) अणु
				पंचांगp = पढ़ोl(&ep->regs->ctl);
				पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
				ग_लिखोl(पंचांगp, &ep->regs->ctl);
				ep->naking = 0;
				UDC_QUEUE_CNAK(ep, ep->num);
			पूर्ण

			अगर (ep->in) अणु
				/* enable ep irq */
				पंचांगp = पढ़ोl(&dev->regs->ep_irqmsk);
				पंचांगp &= AMD_UNMASK_BIT(ep->num);
				ग_लिखोl(पंचांगp, &dev->regs->ep_irqmsk);
			पूर्ण
		पूर्ण अन्यथा अगर (ep->in) अणु
				/* enable ep irq */
				पंचांगp = पढ़ोl(&dev->regs->ep_irqmsk);
				पंचांगp &= AMD_UNMASK_BIT(ep->num);
				ग_लिखोl(पंचांगp, &dev->regs->ep_irqmsk);
			पूर्ण

	पूर्ण अन्यथा अगर (ep->dma) अणु

		/*
		 * prep_dma not used क्रम OUT ep's, this is not possible
		 * क्रम PPB modes, because of chain creation reasons
		 */
		अगर (ep->in) अणु
			retval = prep_dma(ep, req, GFP_ATOMIC);
			अगर (retval != 0)
				जाओ finished;
		पूर्ण
	पूर्ण
	VDBG(dev, "list_add\n");
	/* add request to ep queue */
	अगर (req) अणु

		list_add_tail(&req->queue, &ep->queue);

		/* खोलो rxfअगरo अगर out data queued */
		अगर (खोलो_rxfअगरo) अणु
			/* enable DMA */
			req->dma_going = 1;
			udc_set_rde(dev);
			अगर (ep->num != UDC_EP0OUT_IX)
				dev->data_ep_queued = 1;
		पूर्ण
		/* stop OUT naking */
		अगर (!ep->in) अणु
			अगर (!use_dma && udc_rxfअगरo_pending) अणु
				DBG(dev, "udc_queue(): pending bytes in "
					"rxfifo after nyet\n");
				/*
				 * पढ़ो pending bytes afer nyet:
				 * referring to isr
				 */
				अगर (udc_rxfअगरo_पढ़ो(ep, req)) अणु
					/* finish */
					complete_req(ep, req, 0);
				पूर्ण
				udc_rxfअगरo_pending = 0;

			पूर्ण
		पूर्ण
	पूर्ण

finished:
	spin_unlock_irqrestore(&dev->lock, अगरlags);
	वापस retval;
पूर्ण

/* Empty request queue of an endpoपूर्णांक; caller holds spinlock */
व्योम empty_req_queue(काष्ठा udc_ep *ep)
अणु
	काष्ठा udc_request	*req;

	ep->halted = 1;
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next,
			काष्ठा udc_request,
			queue);
		complete_req(ep, req, -ESHUTDOWN);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(empty_req_queue);

/* Dequeues a request packet, called by gadget driver */
अटल पूर्णांक udc_dequeue(काष्ठा usb_ep *usbep, काष्ठा usb_request *usbreq)
अणु
	काष्ठा udc_ep		*ep;
	काष्ठा udc_request	*req;
	अचिन्हित		halted;
	अचिन्हित दीर्घ		अगरlags;

	ep = container_of(usbep, काष्ठा udc_ep, ep);
	अगर (!usbep || !usbreq || (!ep->ep.desc && (ep->num != 0
				&& ep->num != UDC_EP0OUT_IX)))
		वापस -EINVAL;

	req = container_of(usbreq, काष्ठा udc_request, req);

	spin_lock_irqsave(&ep->dev->lock, अगरlags);
	halted = ep->halted;
	ep->halted = 1;
	/* request in processing or next one */
	अगर (ep->queue.next == &req->queue) अणु
		अगर (ep->dma && req->dma_going) अणु
			अगर (ep->in)
				ep->cancel_transfer = 1;
			अन्यथा अणु
				u32 पंचांगp;
				u32 dma_sts;
				/* stop potential receive DMA */
				पंचांगp = पढ़ोl(&udc->regs->ctl);
				ग_लिखोl(पंचांगp & AMD_UNMASK_BIT(UDC_DEVCTL_RDE),
							&udc->regs->ctl);
				/*
				 * Cancel transfer later in ISR
				 * अगर descriptor was touched.
				 */
				dma_sts = AMD_GETBITS(req->td_data->status,
							UDC_DMA_OUT_STS_BS);
				अगर (dma_sts != UDC_DMA_OUT_STS_BS_HOST_READY)
					ep->cancel_transfer = 1;
				अन्यथा अणु
					udc_init_bna_dummy(ep->req);
					ग_लिखोl(ep->bna_dummy_req->td_phys,
						&ep->regs->desptr);
				पूर्ण
				ग_लिखोl(पंचांगp, &udc->regs->ctl);
			पूर्ण
		पूर्ण
	पूर्ण
	complete_req(ep, req, -ECONNRESET);
	ep->halted = halted;

	spin_unlock_irqrestore(&ep->dev->lock, अगरlags);
	वापस 0;
पूर्ण

/* Halt or clear halt of endpoपूर्णांक */
अटल पूर्णांक
udc_set_halt(काष्ठा usb_ep *usbep, पूर्णांक halt)
अणु
	काष्ठा udc_ep	*ep;
	u32 पंचांगp;
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक retval = 0;

	अगर (!usbep)
		वापस -EINVAL;

	pr_debug("set_halt %s: halt=%d\n", usbep->name, halt);

	ep = container_of(usbep, काष्ठा udc_ep, ep);
	अगर (!ep->ep.desc && (ep->num != 0 && ep->num != UDC_EP0OUT_IX))
		वापस -EINVAL;
	अगर (!ep->dev->driver || ep->dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&udc_stall_spinlock, अगरlags);
	/* halt or clear halt */
	अगर (halt) अणु
		अगर (ep->num == 0)
			ep->dev->stall_ep0in = 1;
		अन्यथा अणु
			/*
			 * set STALL
			 * rxfअगरo empty not taken पूर्णांकo acount
			 */
			पंचांगp = पढ़ोl(&ep->regs->ctl);
			पंचांगp |= AMD_BIT(UDC_EPCTL_S);
			ग_लिखोl(पंचांगp, &ep->regs->ctl);
			ep->halted = 1;

			/* setup poll समयr */
			अगर (!समयr_pending(&udc_pollstall_समयr)) अणु
				udc_pollstall_समयr.expires = jअगरfies +
					HZ * UDC_POLLSTALL_TIMER_USECONDS
					/ (1000 * 1000);
				अगर (!stop_pollstall_समयr) अणु
					DBG(ep->dev, "start polltimer\n");
					add_समयr(&udc_pollstall_समयr);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* ep is halted by set_halt() beक्रमe */
		अगर (ep->halted) अणु
			पंचांगp = पढ़ोl(&ep->regs->ctl);
			/* clear stall bit */
			पंचांगp = पंचांगp & AMD_CLEAR_BIT(UDC_EPCTL_S);
			/* clear NAK by writing CNAK */
			पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
			ग_लिखोl(पंचांगp, &ep->regs->ctl);
			ep->halted = 0;
			UDC_QUEUE_CNAK(ep, ep->num);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&udc_stall_spinlock, अगरlags);
	वापस retval;
पूर्ण

/* gadget पूर्णांकerface */
अटल स्थिर काष्ठा usb_ep_ops udc_ep_ops = अणु
	.enable		= udc_ep_enable,
	.disable	= udc_ep_disable,

	.alloc_request	= udc_alloc_request,
	.मुक्त_request	= udc_मुक्त_request,

	.queue		= udc_queue,
	.dequeue	= udc_dequeue,

	.set_halt	= udc_set_halt,
	/* fअगरo ops not implemented */
पूर्ण;

/*-------------------------------------------------------------------------*/

/* Get frame counter (not implemented) */
अटल पूर्णांक udc_get_frame(काष्ठा usb_gadget *gadget)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/* Initiates a remote wakeup */
अटल पूर्णांक udc_remote_wakeup(काष्ठा udc *dev)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	DBG(dev, "UDC initiates remote wakeup\n");

	spin_lock_irqsave(&dev->lock, flags);

	पंचांगp = पढ़ोl(&dev->regs->ctl);
	पंचांगp |= AMD_BIT(UDC_DEVCTL_RES);
	ग_लिखोl(पंचांगp, &dev->regs->ctl);
	पंचांगp &= AMD_CLEAR_BIT(UDC_DEVCTL_RES);
	ग_लिखोl(पंचांगp, &dev->regs->ctl);

	spin_unlock_irqrestore(&dev->lock, flags);
	वापस 0;
पूर्ण

/* Remote wakeup gadget पूर्णांकerface */
अटल पूर्णांक udc_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा udc		*dev;

	अगर (!gadget)
		वापस -EINVAL;
	dev = container_of(gadget, काष्ठा udc, gadget);
	udc_remote_wakeup(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक amd5536_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक amd5536_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops udc_ops = अणु
	.wakeup		= udc_wakeup,
	.get_frame	= udc_get_frame,
	.udc_start	= amd5536_udc_start,
	.udc_stop	= amd5536_udc_stop,
पूर्ण;

/* Setups endpoपूर्णांक parameters, adds endpoपूर्णांकs to linked list */
अटल व्योम make_ep_lists(काष्ठा udc *dev)
अणु
	/* make gadget ep lists */
	INIT_LIST_HEAD(&dev->gadget.ep_list);
	list_add_tail(&dev->ep[UDC_EPIN_STATUS_IX].ep.ep_list,
						&dev->gadget.ep_list);
	list_add_tail(&dev->ep[UDC_EPIN_IX].ep.ep_list,
						&dev->gadget.ep_list);
	list_add_tail(&dev->ep[UDC_EPOUT_IX].ep.ep_list,
						&dev->gadget.ep_list);

	/* fअगरo config */
	dev->ep[UDC_EPIN_STATUS_IX].fअगरo_depth = UDC_EPIN_SMALLINT_BUFF_SIZE;
	अगर (dev->gadget.speed == USB_SPEED_FULL)
		dev->ep[UDC_EPIN_IX].fअगरo_depth = UDC_FS_EPIN_BUFF_SIZE;
	अन्यथा अगर (dev->gadget.speed == USB_SPEED_HIGH)
		dev->ep[UDC_EPIN_IX].fअगरo_depth = hs_tx_buf;
	dev->ep[UDC_EPOUT_IX].fअगरo_depth = UDC_RXFIFO_SIZE;
पूर्ण

/* Inits UDC context */
व्योम udc_basic_init(काष्ठा udc *dev)
अणु
	u32	पंचांगp;

	DBG(dev, "udc_basic_init()\n");

	dev->gadget.speed = USB_SPEED_UNKNOWN;

	/* stop RDE समयr */
	अगर (समयr_pending(&udc_समयr)) अणु
		set_rde = 0;
		mod_समयr(&udc_समयr, jअगरfies - 1);
	पूर्ण
	/* stop poll stall समयr */
	अगर (समयr_pending(&udc_pollstall_समयr))
		mod_समयr(&udc_pollstall_समयr, jअगरfies - 1);
	/* disable DMA */
	पंचांगp = पढ़ोl(&dev->regs->ctl);
	पंचांगp &= AMD_UNMASK_BIT(UDC_DEVCTL_RDE);
	पंचांगp &= AMD_UNMASK_BIT(UDC_DEVCTL_TDE);
	ग_लिखोl(पंचांगp, &dev->regs->ctl);

	/* enable dynamic CSR programming */
	पंचांगp = पढ़ोl(&dev->regs->cfg);
	पंचांगp |= AMD_BIT(UDC_DEVCFG_CSR_PRG);
	/* set self घातered */
	पंचांगp |= AMD_BIT(UDC_DEVCFG_SP);
	/* set remote wakeupable */
	पंचांगp |= AMD_BIT(UDC_DEVCFG_RWKP);
	ग_लिखोl(पंचांगp, &dev->regs->cfg);

	make_ep_lists(dev);

	dev->data_ep_enabled = 0;
	dev->data_ep_queued = 0;
पूर्ण
EXPORT_SYMBOL_GPL(udc_basic_init);

/* init रेजिस्टरs at driver load समय */
अटल पूर्णांक startup_रेजिस्टरs(काष्ठा udc *dev)
अणु
	u32 पंचांगp;

	/* init controller by soft reset */
	udc_soft_reset(dev);

	/* mask not needed पूर्णांकerrupts */
	udc_mask_unused_पूर्णांकerrupts(dev);

	/* put पूर्णांकo initial config */
	udc_basic_init(dev);
	/* link up all endpoपूर्णांकs */
	udc_setup_endpoपूर्णांकs(dev);

	/* program speed */
	पंचांगp = पढ़ोl(&dev->regs->cfg);
	अगर (use_fullspeed)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_DEVCFG_SPD_FS, UDC_DEVCFG_SPD);
	अन्यथा
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_DEVCFG_SPD_HS, UDC_DEVCFG_SPD);
	ग_लिखोl(पंचांगp, &dev->regs->cfg);

	वापस 0;
पूर्ण

/* Sets initial endpoपूर्णांक parameters */
अटल व्योम udc_setup_endpoपूर्णांकs(काष्ठा udc *dev)
अणु
	काष्ठा udc_ep	*ep;
	u32	पंचांगp;
	u32	reg;

	DBG(dev, "udc_setup_endpoints()\n");

	/* पढ़ो क्रमागत speed */
	पंचांगp = पढ़ोl(&dev->regs->sts);
	पंचांगp = AMD_GETBITS(पंचांगp, UDC_DEVSTS_ENUM_SPEED);
	अगर (पंचांगp == UDC_DEVSTS_ENUM_SPEED_HIGH)
		dev->gadget.speed = USB_SPEED_HIGH;
	अन्यथा अगर (पंचांगp == UDC_DEVSTS_ENUM_SPEED_FULL)
		dev->gadget.speed = USB_SPEED_FULL;

	/* set basic ep parameters */
	क्रम (पंचांगp = 0; पंचांगp < UDC_EP_NUM; पंचांगp++) अणु
		ep = &dev->ep[पंचांगp];
		ep->dev = dev;
		ep->ep.name = ep_info[पंचांगp].name;
		ep->ep.caps = ep_info[पंचांगp].caps;
		ep->num = पंचांगp;
		/* txfअगरo size is calculated at enable समय */
		ep->txfअगरo = dev->txfअगरo;

		/* fअगरo size */
		अगर (पंचांगp < UDC_EPIN_NUM) अणु
			ep->fअगरo_depth = UDC_TXFIFO_SIZE;
			ep->in = 1;
		पूर्ण अन्यथा अणु
			ep->fअगरo_depth = UDC_RXFIFO_SIZE;
			ep->in = 0;

		पूर्ण
		ep->regs = &dev->ep_regs[पंचांगp];
		/*
		 * ep will be reset only अगर ep was not enabled beक्रमe to aव्योम
		 * disabling ep पूर्णांकerrupts when ENUM पूर्णांकerrupt occurs but ep is
		 * not enabled by gadget driver
		 */
		अगर (!ep->ep.desc)
			ep_init(dev->regs, ep);

		अगर (use_dma) अणु
			/*
			 * ep->dma is not really used, just to indicate that
			 * DMA is active: हटाओ this
			 * dma regs = dev control regs
			 */
			ep->dma = &dev->regs->ctl;

			/* nak OUT endpoपूर्णांकs until enable - not क्रम ep0 */
			अगर (पंचांगp != UDC_EP0IN_IX && पंचांगp != UDC_EP0OUT_IX
						&& पंचांगp > UDC_EPIN_NUM) अणु
				/* set NAK */
				reg = पढ़ोl(&dev->ep[पंचांगp].regs->ctl);
				reg |= AMD_BIT(UDC_EPCTL_SNAK);
				ग_लिखोl(reg, &dev->ep[पंचांगp].regs->ctl);
				dev->ep[पंचांगp].naking = 1;

			पूर्ण
		पूर्ण
	पूर्ण
	/* EP0 max packet */
	अगर (dev->gadget.speed == USB_SPEED_FULL) अणु
		usb_ep_set_maxpacket_limit(&dev->ep[UDC_EP0IN_IX].ep,
					   UDC_FS_EP0IN_MAX_PKT_SIZE);
		usb_ep_set_maxpacket_limit(&dev->ep[UDC_EP0OUT_IX].ep,
					   UDC_FS_EP0OUT_MAX_PKT_SIZE);
	पूर्ण अन्यथा अगर (dev->gadget.speed == USB_SPEED_HIGH) अणु
		usb_ep_set_maxpacket_limit(&dev->ep[UDC_EP0IN_IX].ep,
					   UDC_EP0IN_MAX_PKT_SIZE);
		usb_ep_set_maxpacket_limit(&dev->ep[UDC_EP0OUT_IX].ep,
					   UDC_EP0OUT_MAX_PKT_SIZE);
	पूर्ण

	/*
	 * with suspend bug workaround, ep0 params क्रम gadget driver
	 * are set at gadget driver bind() call
	 */
	dev->gadget.ep0 = &dev->ep[UDC_EP0IN_IX].ep;
	dev->ep[UDC_EP0IN_IX].halted = 0;
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);

	/* init cfg/alt/पूर्णांक */
	dev->cur_config = 0;
	dev->cur_पूर्णांकf = 0;
	dev->cur_alt = 0;
पूर्ण

/* Bringup after Connect event, initial bringup to be पढ़ोy क्रम ep0 events */
अटल व्योम usb_connect(काष्ठा udc *dev)
अणु
	/* Return अगर alपढ़ोy connected */
	अगर (dev->connected)
		वापस;

	dev_info(dev->dev, "USB Connect\n");

	dev->connected = 1;

	/* put पूर्णांकo initial config */
	udc_basic_init(dev);

	/* enable device setup पूर्णांकerrupts */
	udc_enable_dev_setup_पूर्णांकerrupts(dev);
पूर्ण

/*
 * Calls gadget with disconnect event and resets the UDC and makes
 * initial bringup to be पढ़ोy क्रम ep0 events
 */
अटल व्योम usb_disconnect(काष्ठा udc *dev)
अणु
	u32 पंचांगp;

	/* Return अगर alपढ़ोy disconnected */
	अगर (!dev->connected)
		वापस;

	dev_info(dev->dev, "USB Disconnect\n");

	dev->connected = 0;

	/* mask पूर्णांकerrupts */
	udc_mask_unused_पूर्णांकerrupts(dev);

	अगर (dev->driver) अणु
		spin_unlock(&dev->lock);
		dev->driver->disconnect(&dev->gadget);
		spin_lock(&dev->lock);

		/* empty queues */
		क्रम (पंचांगp = 0; पंचांगp < UDC_EP_NUM; पंचांगp++)
			empty_req_queue(&dev->ep[पंचांगp]);
	पूर्ण

	/* disable ep0 */
	ep_init(dev->regs, &dev->ep[UDC_EP0IN_IX]);

	अगर (!soft_reset_occured) अणु
		/* init controller by soft reset */
		udc_soft_reset(dev);
		soft_reset_occured++;
	पूर्ण

	/* re-enable dev पूर्णांकerrupts */
	udc_enable_dev_setup_पूर्णांकerrupts(dev);
	/* back to full speed ? */
	अगर (use_fullspeed) अणु
		पंचांगp = पढ़ोl(&dev->regs->cfg);
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_DEVCFG_SPD_FS, UDC_DEVCFG_SPD);
		ग_लिखोl(पंचांगp, &dev->regs->cfg);
	पूर्ण
पूर्ण

/* Reset the UDC core */
अटल व्योम udc_soft_reset(काष्ठा udc *dev)
अणु
	अचिन्हित दीर्घ	flags;

	DBG(dev, "Soft reset\n");
	/*
	 * reset possible रुकोing पूर्णांकerrupts, because पूर्णांक.
	 * status is lost after soft reset,
	 * ep पूर्णांक. status reset
	 */
	ग_लिखोl(UDC_EPINT_MSK_DISABLE_ALL, &dev->regs->ep_irqsts);
	/* device पूर्णांक. status reset */
	ग_लिखोl(UDC_DEV_MSK_DISABLE, &dev->regs->irqsts);

	/* Don't करो this क्रम Broadcom UDC since this is a reserved
	 * bit.
	 */
	अगर (dev->chiprev != UDC_BCM_REV) अणु
		spin_lock_irqsave(&udc_irq_spinlock, flags);
		ग_लिखोl(AMD_BIT(UDC_DEVCFG_SOFTRESET), &dev->regs->cfg);
		पढ़ोl(&dev->regs->cfg);
		spin_unlock_irqrestore(&udc_irq_spinlock, flags);
	पूर्ण
पूर्ण

/* RDE समयr callback to set RDE bit */
अटल व्योम udc_समयr_function(काष्ठा समयr_list *unused)
अणु
	u32 पंचांगp;

	spin_lock_irq(&udc_irq_spinlock);

	अगर (set_rde > 0) अणु
		/*
		 * खोलो the fअगरo अगर fअगरo was filled on last समयr call
		 * conditionally
		 */
		अगर (set_rde > 1) अणु
			/* set RDE to receive setup data */
			पंचांगp = पढ़ोl(&udc->regs->ctl);
			पंचांगp |= AMD_BIT(UDC_DEVCTL_RDE);
			ग_लिखोl(पंचांगp, &udc->regs->ctl);
			set_rde = -1;
		पूर्ण अन्यथा अगर (पढ़ोl(&udc->regs->sts)
				& AMD_BIT(UDC_DEVSTS_RXFIFO_EMPTY)) अणु
			/*
			 * अगर fअगरo empty setup polling, करो not just
			 * खोलो the fअगरo
			 */
			udc_समयr.expires = jअगरfies + HZ/UDC_RDE_TIMER_DIV;
			अगर (!stop_समयr)
				add_समयr(&udc_समयr);
		पूर्ण अन्यथा अणु
			/*
			 * fअगरo contains data now, setup समयr क्रम खोलोing
			 * the fअगरo when समयr expires to be able to receive
			 * setup packets, when data packets माला_लो queued by
			 * gadget layer then समयr will क्रमced to expire with
			 * set_rde=0 (RDE is set in udc_queue())
			 */
			set_rde++;
			/* debug: lhadmot_समयr_start = 221070 */
			udc_समयr.expires = jअगरfies + HZ*UDC_RDE_TIMER_SECONDS;
			अगर (!stop_समयr)
				add_समयr(&udc_समयr);
		पूर्ण

	पूर्ण अन्यथा
		set_rde = -1; /* RDE was set by udc_queue() */
	spin_unlock_irq(&udc_irq_spinlock);
	अगर (stop_समयr)
		complete(&on_निकास);

पूर्ण

/* Handle halt state, used in stall poll समयr */
अटल व्योम udc_handle_halt_state(काष्ठा udc_ep *ep)
अणु
	u32 पंचांगp;
	/* set stall as दीर्घ not halted */
	अगर (ep->halted == 1) अणु
		पंचांगp = पढ़ोl(&ep->regs->ctl);
		/* STALL cleared ? */
		अगर (!(पंचांगp & AMD_BIT(UDC_EPCTL_S))) अणु
			/*
			 * FIXME: MSC spec requires that stall reमुख्यs
			 * even on receivng of CLEAR_FEATURE HALT. So
			 * we would set STALL again here to be compliant.
			 * But with current mass storage drivers this करोes
			 * not work (would produce endless host retries).
			 * So we clear halt on CLEAR_FEATURE.
			 *
			DBG(ep->dev, "ep %d: set STALL again\n", ep->num);
			पंचांगp |= AMD_BIT(UDC_EPCTL_S);
			ग_लिखोl(पंचांगp, &ep->regs->ctl);*/

			/* clear NAK by writing CNAK */
			पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
			ग_लिखोl(पंचांगp, &ep->regs->ctl);
			ep->halted = 0;
			UDC_QUEUE_CNAK(ep, ep->num);
		पूर्ण
	पूर्ण
पूर्ण

/* Stall समयr callback to poll S bit and set it again after */
अटल व्योम udc_pollstall_समयr_function(काष्ठा समयr_list *unused)
अणु
	काष्ठा udc_ep *ep;
	पूर्णांक halted = 0;

	spin_lock_irq(&udc_stall_spinlock);
	/*
	 * only one IN and OUT endpoपूर्णांकs are handled
	 * IN poll stall
	 */
	ep = &udc->ep[UDC_EPIN_IX];
	udc_handle_halt_state(ep);
	अगर (ep->halted)
		halted = 1;
	/* OUT poll stall */
	ep = &udc->ep[UDC_EPOUT_IX];
	udc_handle_halt_state(ep);
	अगर (ep->halted)
		halted = 1;

	/* setup समयr again when still halted */
	अगर (!stop_pollstall_समयr && halted) अणु
		udc_pollstall_समयr.expires = jअगरfies +
					HZ * UDC_POLLSTALL_TIMER_USECONDS
					/ (1000 * 1000);
		add_समयr(&udc_pollstall_समयr);
	पूर्ण
	spin_unlock_irq(&udc_stall_spinlock);

	अगर (stop_pollstall_समयr)
		complete(&on_pollstall_निकास);
पूर्ण

/* Inits endpoपूर्णांक 0 so that SETUP packets are processed */
अटल व्योम activate_control_endpoपूर्णांकs(काष्ठा udc *dev)
अणु
	u32 पंचांगp;

	DBG(dev, "activate_control_endpoints\n");

	/* flush fअगरo */
	पंचांगp = पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->ctl);
	पंचांगp |= AMD_BIT(UDC_EPCTL_F);
	ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0IN_IX].regs->ctl);

	/* set ep0 directions */
	dev->ep[UDC_EP0IN_IX].in = 1;
	dev->ep[UDC_EP0OUT_IX].in = 0;

	/* set buffer size (tx fअगरo entries) of EP0_IN */
	पंचांगp = पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->bufin_framक्रमागत);
	अगर (dev->gadget.speed == USB_SPEED_FULL)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_FS_EPIN0_BUFF_SIZE,
					UDC_EPIN_BUFF_SIZE);
	अन्यथा अगर (dev->gadget.speed == USB_SPEED_HIGH)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_EPIN0_BUFF_SIZE,
					UDC_EPIN_BUFF_SIZE);
	ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0IN_IX].regs->bufin_framक्रमागत);

	/* set max packet size of EP0_IN */
	पंचांगp = पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->bufout_maxpkt);
	अगर (dev->gadget.speed == USB_SPEED_FULL)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_FS_EP0IN_MAX_PKT_SIZE,
					UDC_EP_MAX_PKT_SIZE);
	अन्यथा अगर (dev->gadget.speed == USB_SPEED_HIGH)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_EP0IN_MAX_PKT_SIZE,
				UDC_EP_MAX_PKT_SIZE);
	ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0IN_IX].regs->bufout_maxpkt);

	/* set max packet size of EP0_OUT */
	पंचांगp = पढ़ोl(&dev->ep[UDC_EP0OUT_IX].regs->bufout_maxpkt);
	अगर (dev->gadget.speed == USB_SPEED_FULL)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_FS_EP0OUT_MAX_PKT_SIZE,
					UDC_EP_MAX_PKT_SIZE);
	अन्यथा अगर (dev->gadget.speed == USB_SPEED_HIGH)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_EP0OUT_MAX_PKT_SIZE,
					UDC_EP_MAX_PKT_SIZE);
	ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0OUT_IX].regs->bufout_maxpkt);

	/* set max packet size of EP0 in UDC CSR */
	पंचांगp = पढ़ोl(&dev->csr->ne[0]);
	अगर (dev->gadget.speed == USB_SPEED_FULL)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_FS_EP0OUT_MAX_PKT_SIZE,
					UDC_CSR_NE_MAX_PKT);
	अन्यथा अगर (dev->gadget.speed == USB_SPEED_HIGH)
		पंचांगp = AMD_ADDBITS(पंचांगp, UDC_EP0OUT_MAX_PKT_SIZE,
					UDC_CSR_NE_MAX_PKT);
	ग_लिखोl(पंचांगp, &dev->csr->ne[0]);

	अगर (use_dma) अणु
		dev->ep[UDC_EP0OUT_IX].td->status |=
			AMD_BIT(UDC_DMA_OUT_STS_L);
		/* ग_लिखो dma desc address */
		ग_लिखोl(dev->ep[UDC_EP0OUT_IX].td_stp_dma,
			&dev->ep[UDC_EP0OUT_IX].regs->subptr);
		ग_लिखोl(dev->ep[UDC_EP0OUT_IX].td_phys,
			&dev->ep[UDC_EP0OUT_IX].regs->desptr);
		/* stop RDE समयr */
		अगर (समयr_pending(&udc_समयr)) अणु
			set_rde = 0;
			mod_समयr(&udc_समयr, jअगरfies - 1);
		पूर्ण
		/* stop pollstall समयr */
		अगर (समयr_pending(&udc_pollstall_समयr))
			mod_समयr(&udc_pollstall_समयr, jअगरfies - 1);
		/* enable DMA */
		पंचांगp = पढ़ोl(&dev->regs->ctl);
		पंचांगp |= AMD_BIT(UDC_DEVCTL_MODE)
				| AMD_BIT(UDC_DEVCTL_RDE)
				| AMD_BIT(UDC_DEVCTL_TDE);
		अगर (use_dma_bufferfill_mode)
			पंचांगp |= AMD_BIT(UDC_DEVCTL_BF);
		अन्यथा अगर (use_dma_ppb_du)
			पंचांगp |= AMD_BIT(UDC_DEVCTL_DU);
		ग_लिखोl(पंचांगp, &dev->regs->ctl);
	पूर्ण

	/* clear NAK by writing CNAK क्रम EP0IN */
	पंचांगp = पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->ctl);
	पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
	ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0IN_IX].regs->ctl);
	dev->ep[UDC_EP0IN_IX].naking = 0;
	UDC_QUEUE_CNAK(&dev->ep[UDC_EP0IN_IX], UDC_EP0IN_IX);

	/* clear NAK by writing CNAK क्रम EP0OUT */
	पंचांगp = पढ़ोl(&dev->ep[UDC_EP0OUT_IX].regs->ctl);
	पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
	ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0OUT_IX].regs->ctl);
	dev->ep[UDC_EP0OUT_IX].naking = 0;
	UDC_QUEUE_CNAK(&dev->ep[UDC_EP0OUT_IX], UDC_EP0OUT_IX);
पूर्ण

/* Make endpoपूर्णांक 0 पढ़ोy क्रम control traffic */
अटल पूर्णांक setup_ep0(काष्ठा udc *dev)
अणु
	activate_control_endpoपूर्णांकs(dev);
	/* enable ep0 पूर्णांकerrupts */
	udc_enable_ep0_पूर्णांकerrupts(dev);
	/* enable device setup पूर्णांकerrupts */
	udc_enable_dev_setup_पूर्णांकerrupts(dev);

	वापस 0;
पूर्ण

/* Called by gadget driver to रेजिस्टर itself */
अटल पूर्णांक amd5536_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा udc *dev = to_amd5536_udc(g);
	u32 पंचांगp;

	driver->driver.bus = शून्य;
	dev->driver = driver;

	/* Some gadget drivers use both ep0 directions.
	 * NOTE: to gadget driver, ep0 is just one endpoपूर्णांक...
	 */
	dev->ep[UDC_EP0OUT_IX].ep.driver_data =
		dev->ep[UDC_EP0IN_IX].ep.driver_data;

	/* get पढ़ोy क्रम ep0 traffic */
	setup_ep0(dev);

	/* clear SD */
	पंचांगp = पढ़ोl(&dev->regs->ctl);
	पंचांगp = पंचांगp & AMD_CLEAR_BIT(UDC_DEVCTL_SD);
	ग_लिखोl(पंचांगp, &dev->regs->ctl);

	usb_connect(dev);

	वापस 0;
पूर्ण

/* shutकरोwn requests and disconnect from gadget */
अटल व्योम
shutकरोwn(काष्ठा udc *dev, काष्ठा usb_gadget_driver *driver)
__releases(dev->lock)
__acquires(dev->lock)
अणु
	पूर्णांक पंचांगp;

	/* empty queues and init hardware */
	udc_basic_init(dev);

	क्रम (पंचांगp = 0; पंचांगp < UDC_EP_NUM; पंचांगp++)
		empty_req_queue(&dev->ep[पंचांगp]);

	udc_setup_endpoपूर्णांकs(dev);
पूर्ण

/* Called by gadget driver to unरेजिस्टर itself */
अटल पूर्णांक amd5536_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा udc *dev = to_amd5536_udc(g);
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&dev->lock, flags);
	udc_mask_unused_पूर्णांकerrupts(dev);
	shutकरोwn(dev, शून्य);
	spin_unlock_irqrestore(&dev->lock, flags);

	dev->driver = शून्य;

	/* set SD */
	पंचांगp = पढ़ोl(&dev->regs->ctl);
	पंचांगp |= AMD_BIT(UDC_DEVCTL_SD);
	ग_लिखोl(पंचांगp, &dev->regs->ctl);

	वापस 0;
पूर्ण

/* Clear pending NAK bits */
अटल व्योम udc_process_cnak_queue(काष्ठा udc *dev)
अणु
	u32 पंचांगp;
	u32 reg;

	/* check epin's */
	DBG(dev, "CNAK pending queue processing\n");
	क्रम (पंचांगp = 0; पंचांगp < UDC_EPIN_NUM_USED; पंचांगp++) अणु
		अगर (cnak_pending & (1 << पंचांगp)) अणु
			DBG(dev, "CNAK pending for ep%d\n", पंचांगp);
			/* clear NAK by writing CNAK */
			reg = पढ़ोl(&dev->ep[पंचांगp].regs->ctl);
			reg |= AMD_BIT(UDC_EPCTL_CNAK);
			ग_लिखोl(reg, &dev->ep[पंचांगp].regs->ctl);
			dev->ep[पंचांगp].naking = 0;
			UDC_QUEUE_CNAK(&dev->ep[पंचांगp], dev->ep[पंचांगp].num);
		पूर्ण
	पूर्ण
	/* ...	and ep0out */
	अगर (cnak_pending & (1 << UDC_EP0OUT_IX)) अणु
		DBG(dev, "CNAK pending for ep%d\n", UDC_EP0OUT_IX);
		/* clear NAK by writing CNAK */
		reg = पढ़ोl(&dev->ep[UDC_EP0OUT_IX].regs->ctl);
		reg |= AMD_BIT(UDC_EPCTL_CNAK);
		ग_लिखोl(reg, &dev->ep[UDC_EP0OUT_IX].regs->ctl);
		dev->ep[UDC_EP0OUT_IX].naking = 0;
		UDC_QUEUE_CNAK(&dev->ep[UDC_EP0OUT_IX],
				dev->ep[UDC_EP0OUT_IX].num);
	पूर्ण
पूर्ण

/* Enabling RX DMA after setup packet */
अटल व्योम udc_ep0_set_rde(काष्ठा udc *dev)
अणु
	अगर (use_dma) अणु
		/*
		 * only enable RXDMA when no data endpoपूर्णांक enabled
		 * or data is queued
		 */
		अगर (!dev->data_ep_enabled || dev->data_ep_queued) अणु
			udc_set_rde(dev);
		पूर्ण अन्यथा अणु
			/*
			 * setup समयr क्रम enabling RDE (to not enable
			 * RXFIFO DMA क्रम data endpoपूर्णांकs to early)
			 */
			अगर (set_rde != 0 && !समयr_pending(&udc_समयr)) अणु
				udc_समयr.expires =
					jअगरfies + HZ/UDC_RDE_TIMER_DIV;
				set_rde = 1;
				अगर (!stop_समयr)
					add_समयr(&udc_समयr);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


/* Interrupt handler क्रम data OUT traffic */
अटल irqवापस_t udc_data_out_isr(काष्ठा udc *dev, पूर्णांक ep_ix)
अणु
	irqवापस_t		ret_val = IRQ_NONE;
	u32			पंचांगp;
	काष्ठा udc_ep		*ep;
	काष्ठा udc_request	*req;
	अचिन्हित पूर्णांक		count;
	काष्ठा udc_data_dma	*td = शून्य;
	अचिन्हित		dma_करोne;

	VDBG(dev, "ep%d irq\n", ep_ix);
	ep = &dev->ep[ep_ix];

	पंचांगp = पढ़ोl(&ep->regs->sts);
	अगर (use_dma) अणु
		/* BNA event ? */
		अगर (पंचांगp & AMD_BIT(UDC_EPSTS_BNA)) अणु
			DBG(dev, "BNA ep%dout occurred - DESPTR = %x\n",
					ep->num, पढ़ोl(&ep->regs->desptr));
			/* clear BNA */
			ग_लिखोl(पंचांगp | AMD_BIT(UDC_EPSTS_BNA), &ep->regs->sts);
			अगर (!ep->cancel_transfer)
				ep->bna_occurred = 1;
			अन्यथा
				ep->cancel_transfer = 0;
			ret_val = IRQ_HANDLED;
			जाओ finished;
		पूर्ण
	पूर्ण
	/* HE event ? */
	अगर (पंचांगp & AMD_BIT(UDC_EPSTS_HE)) अणु
		dev_err(dev->dev, "HE ep%dout occurred\n", ep->num);

		/* clear HE */
		ग_लिखोl(पंचांगp | AMD_BIT(UDC_EPSTS_HE), &ep->regs->sts);
		ret_val = IRQ_HANDLED;
		जाओ finished;
	पूर्ण

	अगर (!list_empty(&ep->queue)) अणु

		/* next request */
		req = list_entry(ep->queue.next,
			काष्ठा udc_request, queue);
	पूर्ण अन्यथा अणु
		req = शून्य;
		udc_rxfअगरo_pending = 1;
	पूर्ण
	VDBG(dev, "req = %p\n", req);
	/* fअगरo mode */
	अगर (!use_dma) अणु

		/* पढ़ो fअगरo */
		अगर (req && udc_rxfअगरo_पढ़ो(ep, req)) अणु
			ret_val = IRQ_HANDLED;

			/* finish */
			complete_req(ep, req, 0);
			/* next request */
			अगर (!list_empty(&ep->queue) && !ep->halted) अणु
				req = list_entry(ep->queue.next,
					काष्ठा udc_request, queue);
			पूर्ण अन्यथा
				req = शून्य;
		पूर्ण

	/* DMA */
	पूर्ण अन्यथा अगर (!ep->cancel_transfer && req) अणु
		ret_val = IRQ_HANDLED;

		/* check क्रम DMA करोne */
		अगर (!use_dma_ppb) अणु
			dma_करोne = AMD_GETBITS(req->td_data->status,
						UDC_DMA_OUT_STS_BS);
		/* packet per buffer mode - rx bytes */
		पूर्ण अन्यथा अणु
			/*
			 * अगर BNA occurred then recover desc. from
			 * BNA dummy desc.
			 */
			अगर (ep->bna_occurred) अणु
				VDBG(dev, "Recover desc. from BNA dummy\n");
				स_नकल(req->td_data, ep->bna_dummy_req->td_data,
						माप(काष्ठा udc_data_dma));
				ep->bna_occurred = 0;
				udc_init_bna_dummy(ep->req);
			पूर्ण
			td = udc_get_last_dma_desc(req);
			dma_करोne = AMD_GETBITS(td->status, UDC_DMA_OUT_STS_BS);
		पूर्ण
		अगर (dma_करोne == UDC_DMA_OUT_STS_BS_DMA_DONE) अणु
			/* buffer fill mode - rx bytes */
			अगर (!use_dma_ppb) अणु
				/* received number bytes */
				count = AMD_GETBITS(req->td_data->status,
						UDC_DMA_OUT_STS_RXBYTES);
				VDBG(dev, "rx bytes=%u\n", count);
			/* packet per buffer mode - rx bytes */
			पूर्ण अन्यथा अणु
				VDBG(dev, "req->td_data=%p\n", req->td_data);
				VDBG(dev, "last desc = %p\n", td);
				/* received number bytes */
				अगर (use_dma_ppb_du) अणु
					/* every desc. counts bytes */
					count = udc_get_ppbdu_rxbytes(req);
				पूर्ण अन्यथा अणु
					/* last desc. counts bytes */
					count = AMD_GETBITS(td->status,
						UDC_DMA_OUT_STS_RXBYTES);
					अगर (!count && req->req.length
						== UDC_DMA_MAXPACKET) अणु
						/*
						 * on 64k packets the RXBYTES
						 * field is zero
						 */
						count = UDC_DMA_MAXPACKET;
					पूर्ण
				पूर्ण
				VDBG(dev, "last desc rx bytes=%u\n", count);
			पूर्ण

			पंचांगp = req->req.length - req->req.actual;
			अगर (count > पंचांगp) अणु
				अगर ((पंचांगp % ep->ep.maxpacket) != 0) अणु
					DBG(dev, "%s: rx %db, space=%db\n",
						ep->ep.name, count, पंचांगp);
					req->req.status = -EOVERFLOW;
				पूर्ण
				count = पंचांगp;
			पूर्ण
			req->req.actual += count;
			req->dma_going = 0;
			/* complete request */
			complete_req(ep, req, 0);

			/* next request */
			अगर (!list_empty(&ep->queue) && !ep->halted) अणु
				req = list_entry(ep->queue.next,
					काष्ठा udc_request,
					queue);
				/*
				 * DMA may be alपढ़ोy started by udc_queue()
				 * called by gadget drivers completion
				 * routine. This happens when queue
				 * holds one request only.
				 */
				अगर (req->dma_going == 0) अणु
					/* next dma */
					अगर (prep_dma(ep, req, GFP_ATOMIC) != 0)
						जाओ finished;
					/* ग_लिखो desc poपूर्णांकer */
					ग_लिखोl(req->td_phys,
						&ep->regs->desptr);
					req->dma_going = 1;
					/* enable DMA */
					udc_set_rde(dev);
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * implant BNA dummy descriptor to allow
				 * RXFIFO खोलोing by RDE
				 */
				अगर (ep->bna_dummy_req) अणु
					/* ग_लिखो desc poपूर्णांकer */
					ग_लिखोl(ep->bna_dummy_req->td_phys,
						&ep->regs->desptr);
					ep->bna_occurred = 0;
				पूर्ण

				/*
				 * schedule समयr क्रम setting RDE अगर queue
				 * reमुख्यs empty to allow ep0 packets pass
				 * through
				 */
				अगर (set_rde != 0
						&& !समयr_pending(&udc_समयr)) अणु
					udc_समयr.expires =
						jअगरfies
						+ HZ*UDC_RDE_TIMER_SECONDS;
					set_rde = 1;
					अगर (!stop_समयr)
						add_समयr(&udc_समयr);
				पूर्ण
				अगर (ep->num != UDC_EP0OUT_IX)
					dev->data_ep_queued = 0;
			पूर्ण

		पूर्ण अन्यथा अणु
			/*
			* RX DMA must be reenabled क्रम each desc in PPBDU mode
			* and must be enabled क्रम PPBNDU mode in हाल of BNA
			*/
			udc_set_rde(dev);
		पूर्ण

	पूर्ण अन्यथा अगर (ep->cancel_transfer) अणु
		ret_val = IRQ_HANDLED;
		ep->cancel_transfer = 0;
	पूर्ण

	/* check pending CNAKS */
	अगर (cnak_pending) अणु
		/* CNAk processing when rxfअगरo empty only */
		अगर (पढ़ोl(&dev->regs->sts) & AMD_BIT(UDC_DEVSTS_RXFIFO_EMPTY))
			udc_process_cnak_queue(dev);
	पूर्ण

	/* clear OUT bits in ep status */
	ग_लिखोl(UDC_EPSTS_OUT_CLEAR, &ep->regs->sts);
finished:
	वापस ret_val;
पूर्ण

/* Interrupt handler क्रम data IN traffic */
अटल irqवापस_t udc_data_in_isr(काष्ठा udc *dev, पूर्णांक ep_ix)
अणु
	irqवापस_t ret_val = IRQ_NONE;
	u32 पंचांगp;
	u32 epsts;
	काष्ठा udc_ep *ep;
	काष्ठा udc_request *req;
	काष्ठा udc_data_dma *td;
	अचिन्हित len;

	ep = &dev->ep[ep_ix];

	epsts = पढ़ोl(&ep->regs->sts);
	अगर (use_dma) अणु
		/* BNA ? */
		अगर (epsts & AMD_BIT(UDC_EPSTS_BNA)) अणु
			dev_err(dev->dev,
				"BNA ep%din occurred - DESPTR = %08lx\n",
				ep->num,
				(अचिन्हित दीर्घ) पढ़ोl(&ep->regs->desptr));

			/* clear BNA */
			ग_लिखोl(epsts, &ep->regs->sts);
			ret_val = IRQ_HANDLED;
			जाओ finished;
		पूर्ण
	पूर्ण
	/* HE event ? */
	अगर (epsts & AMD_BIT(UDC_EPSTS_HE)) अणु
		dev_err(dev->dev,
			"HE ep%dn occurred - DESPTR = %08lx\n",
			ep->num, (अचिन्हित दीर्घ) पढ़ोl(&ep->regs->desptr));

		/* clear HE */
		ग_लिखोl(epsts | AMD_BIT(UDC_EPSTS_HE), &ep->regs->sts);
		ret_val = IRQ_HANDLED;
		जाओ finished;
	पूर्ण

	/* DMA completion */
	अगर (epsts & AMD_BIT(UDC_EPSTS_TDC)) अणु
		VDBG(dev, "TDC set- completion\n");
		ret_val = IRQ_HANDLED;
		अगर (!ep->cancel_transfer && !list_empty(&ep->queue)) अणु
			req = list_entry(ep->queue.next,
					काष्ठा udc_request, queue);
			/*
			 * length bytes transferred
			 * check dma करोne of last desc. in PPBDU mode
			 */
			अगर (use_dma_ppb_du) अणु
				td = udc_get_last_dma_desc(req);
				अगर (td)
					req->req.actual = req->req.length;
			पूर्ण अन्यथा अणु
				/* assume all bytes transferred */
				req->req.actual = req->req.length;
			पूर्ण

			अगर (req->req.actual == req->req.length) अणु
				/* complete req */
				complete_req(ep, req, 0);
				req->dma_going = 0;
				/* further request available ? */
				अगर (list_empty(&ep->queue)) अणु
					/* disable पूर्णांकerrupt */
					पंचांगp = पढ़ोl(&dev->regs->ep_irqmsk);
					पंचांगp |= AMD_BIT(ep->num);
					ग_लिखोl(पंचांगp, &dev->regs->ep_irqmsk);
				पूर्ण
			पूर्ण
		पूर्ण
		ep->cancel_transfer = 0;

	पूर्ण
	/*
	 * status reg has IN bit set and TDC not set (अगर TDC was handled,
	 * IN must not be handled (UDC defect) ?
	 */
	अगर ((epsts & AMD_BIT(UDC_EPSTS_IN))
			&& !(epsts & AMD_BIT(UDC_EPSTS_TDC))) अणु
		ret_val = IRQ_HANDLED;
		अगर (!list_empty(&ep->queue)) अणु
			/* next request */
			req = list_entry(ep->queue.next,
					काष्ठा udc_request, queue);
			/* FIFO mode */
			अगर (!use_dma) अणु
				/* ग_लिखो fअगरo */
				udc_txfअगरo_ग_लिखो(ep, &req->req);
				len = req->req.length - req->req.actual;
				अगर (len > ep->ep.maxpacket)
					len = ep->ep.maxpacket;
				req->req.actual += len;
				अगर (req->req.actual == req->req.length
					|| (len != ep->ep.maxpacket)) अणु
					/* complete req */
					complete_req(ep, req, 0);
				पूर्ण
			/* DMA */
			पूर्ण अन्यथा अगर (req && !req->dma_going) अणु
				VDBG(dev, "IN DMA : req=%p req->td_data=%p\n",
					req, req->td_data);
				अगर (req->td_data) अणु

					req->dma_going = 1;

					/*
					 * unset L bit of first desc.
					 * क्रम chain
					 */
					अगर (use_dma_ppb && req->req.length >
							ep->ep.maxpacket) अणु
						req->td_data->status &=
							AMD_CLEAR_BIT(
							UDC_DMA_IN_STS_L);
					पूर्ण

					/* ग_लिखो desc poपूर्णांकer */
					ग_लिखोl(req->td_phys, &ep->regs->desptr);

					/* set HOST READY */
					req->td_data->status =
						AMD_ADDBITS(
						req->td_data->status,
						UDC_DMA_IN_STS_BS_HOST_READY,
						UDC_DMA_IN_STS_BS);

					/* set poll demand bit */
					पंचांगp = पढ़ोl(&ep->regs->ctl);
					पंचांगp |= AMD_BIT(UDC_EPCTL_P);
					ग_लिखोl(पंचांगp, &ep->regs->ctl);
				पूर्ण
			पूर्ण

		पूर्ण अन्यथा अगर (!use_dma && ep->in) अणु
			/* disable पूर्णांकerrupt */
			पंचांगp = पढ़ोl(
				&dev->regs->ep_irqmsk);
			पंचांगp |= AMD_BIT(ep->num);
			ग_लिखोl(पंचांगp,
				&dev->regs->ep_irqmsk);
		पूर्ण
	पूर्ण
	/* clear status bits */
	ग_लिखोl(epsts, &ep->regs->sts);

finished:
	वापस ret_val;

पूर्ण

/* Interrupt handler क्रम Control OUT traffic */
अटल irqवापस_t udc_control_out_isr(काष्ठा udc *dev)
__releases(dev->lock)
__acquires(dev->lock)
अणु
	irqवापस_t ret_val = IRQ_NONE;
	u32 पंचांगp;
	पूर्णांक setup_supported;
	u32 count;
	पूर्णांक set = 0;
	काष्ठा udc_ep	*ep;
	काष्ठा udc_ep	*ep_पंचांगp;

	ep = &dev->ep[UDC_EP0OUT_IX];

	/* clear irq */
	ग_लिखोl(AMD_BIT(UDC_EPINT_OUT_EP0), &dev->regs->ep_irqsts);

	पंचांगp = पढ़ोl(&dev->ep[UDC_EP0OUT_IX].regs->sts);
	/* check BNA and clear अगर set */
	अगर (पंचांगp & AMD_BIT(UDC_EPSTS_BNA)) अणु
		VDBG(dev, "ep0: BNA set\n");
		ग_लिखोl(AMD_BIT(UDC_EPSTS_BNA),
			&dev->ep[UDC_EP0OUT_IX].regs->sts);
		ep->bna_occurred = 1;
		ret_val = IRQ_HANDLED;
		जाओ finished;
	पूर्ण

	/* type of data: SETUP or DATA 0 bytes */
	पंचांगp = AMD_GETBITS(पंचांगp, UDC_EPSTS_OUT);
	VDBG(dev, "data_typ = %x\n", पंचांगp);

	/* setup data */
	अगर (पंचांगp == UDC_EPSTS_OUT_SETUP) अणु
		ret_val = IRQ_HANDLED;

		ep->dev->stall_ep0in = 0;
		dev->रुकोing_zlp_ack_ep0in = 0;

		/* set NAK क्रम EP0_IN */
		पंचांगp = पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->ctl);
		पंचांगp |= AMD_BIT(UDC_EPCTL_SNAK);
		ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0IN_IX].regs->ctl);
		dev->ep[UDC_EP0IN_IX].naking = 1;
		/* get setup data */
		अगर (use_dma) अणु

			/* clear OUT bits in ep status */
			ग_लिखोl(UDC_EPSTS_OUT_CLEAR,
				&dev->ep[UDC_EP0OUT_IX].regs->sts);

			setup_data.data[0] =
				dev->ep[UDC_EP0OUT_IX].td_stp->data12;
			setup_data.data[1] =
				dev->ep[UDC_EP0OUT_IX].td_stp->data34;
			/* set HOST READY */
			dev->ep[UDC_EP0OUT_IX].td_stp->status =
					UDC_DMA_STP_STS_BS_HOST_READY;
		पूर्ण अन्यथा अणु
			/* पढ़ो fअगरo */
			udc_rxfअगरo_पढ़ो_dwords(dev, setup_data.data, 2);
		पूर्ण

		/* determine direction of control data */
		अगर ((setup_data.request.bRequestType & USB_सूची_IN) != 0) अणु
			dev->gadget.ep0 = &dev->ep[UDC_EP0IN_IX].ep;
			/* enable RDE */
			udc_ep0_set_rde(dev);
			set = 0;
		पूर्ण अन्यथा अणु
			dev->gadget.ep0 = &dev->ep[UDC_EP0OUT_IX].ep;
			/*
			 * implant BNA dummy descriptor to allow RXFIFO खोलोing
			 * by RDE
			 */
			अगर (ep->bna_dummy_req) अणु
				/* ग_लिखो desc poपूर्णांकer */
				ग_लिखोl(ep->bna_dummy_req->td_phys,
					&dev->ep[UDC_EP0OUT_IX].regs->desptr);
				ep->bna_occurred = 0;
			पूर्ण

			set = 1;
			dev->ep[UDC_EP0OUT_IX].naking = 1;
			/*
			 * setup समयr क्रम enabling RDE (to not enable
			 * RXFIFO DMA क्रम data to early)
			 */
			set_rde = 1;
			अगर (!समयr_pending(&udc_समयr)) अणु
				udc_समयr.expires = jअगरfies +
							HZ/UDC_RDE_TIMER_DIV;
				अगर (!stop_समयr)
					add_समयr(&udc_समयr);
			पूर्ण
		पूर्ण

		/*
		 * mass storage reset must be processed here because
		 * next packet may be a CLEAR_FEATURE HALT which would not
		 * clear the stall bit when no STALL handshake was received
		 * beक्रमe (स्वतःstall can cause this)
		 */
		अगर (setup_data.data[0] == UDC_MSCRES_DWORD0
				&& setup_data.data[1] == UDC_MSCRES_DWORD1) अणु
			DBG(dev, "MSC Reset\n");
			/*
			 * clear stall bits
			 * only one IN and OUT endpoपूर्णांकs are handled
			 */
			ep_पंचांगp = &udc->ep[UDC_EPIN_IX];
			udc_set_halt(&ep_पंचांगp->ep, 0);
			ep_पंचांगp = &udc->ep[UDC_EPOUT_IX];
			udc_set_halt(&ep_पंचांगp->ep, 0);
		पूर्ण

		/* call gadget with setup data received */
		spin_unlock(&dev->lock);
		setup_supported = dev->driver->setup(&dev->gadget,
						&setup_data.request);
		spin_lock(&dev->lock);

		पंचांगp = पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->ctl);
		/* ep0 in वापसs data (not zlp) on IN phase */
		अगर (setup_supported >= 0 && setup_supported <
				UDC_EP0IN_MAXPACKET) अणु
			/* clear NAK by writing CNAK in EP0_IN */
			पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
			ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0IN_IX].regs->ctl);
			dev->ep[UDC_EP0IN_IX].naking = 0;
			UDC_QUEUE_CNAK(&dev->ep[UDC_EP0IN_IX], UDC_EP0IN_IX);

		/* अगर unsupported request then stall */
		पूर्ण अन्यथा अगर (setup_supported < 0) अणु
			पंचांगp |= AMD_BIT(UDC_EPCTL_S);
			ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0IN_IX].regs->ctl);
		पूर्ण अन्यथा
			dev->रुकोing_zlp_ack_ep0in = 1;


		/* clear NAK by writing CNAK in EP0_OUT */
		अगर (!set) अणु
			पंचांगp = पढ़ोl(&dev->ep[UDC_EP0OUT_IX].regs->ctl);
			पंचांगp |= AMD_BIT(UDC_EPCTL_CNAK);
			ग_लिखोl(पंचांगp, &dev->ep[UDC_EP0OUT_IX].regs->ctl);
			dev->ep[UDC_EP0OUT_IX].naking = 0;
			UDC_QUEUE_CNAK(&dev->ep[UDC_EP0OUT_IX], UDC_EP0OUT_IX);
		पूर्ण

		अगर (!use_dma) अणु
			/* clear OUT bits in ep status */
			ग_लिखोl(UDC_EPSTS_OUT_CLEAR,
				&dev->ep[UDC_EP0OUT_IX].regs->sts);
		पूर्ण

	/* data packet 0 bytes */
	पूर्ण अन्यथा अगर (पंचांगp == UDC_EPSTS_OUT_DATA) अणु
		/* clear OUT bits in ep status */
		ग_लिखोl(UDC_EPSTS_OUT_CLEAR, &dev->ep[UDC_EP0OUT_IX].regs->sts);

		/* get setup data: only 0 packet */
		अगर (use_dma) अणु
			/* no req अगर 0 packet, just reactivate */
			अगर (list_empty(&dev->ep[UDC_EP0OUT_IX].queue)) अणु
				VDBG(dev, "ZLP\n");

				/* set HOST READY */
				dev->ep[UDC_EP0OUT_IX].td->status =
					AMD_ADDBITS(
					dev->ep[UDC_EP0OUT_IX].td->status,
					UDC_DMA_OUT_STS_BS_HOST_READY,
					UDC_DMA_OUT_STS_BS);
				/* enable RDE */
				udc_ep0_set_rde(dev);
				ret_val = IRQ_HANDLED;

			पूर्ण अन्यथा अणु
				/* control ग_लिखो */
				ret_val |= udc_data_out_isr(dev, UDC_EP0OUT_IX);
				/* re-program desc. poपूर्णांकer क्रम possible ZLPs */
				ग_लिखोl(dev->ep[UDC_EP0OUT_IX].td_phys,
					&dev->ep[UDC_EP0OUT_IX].regs->desptr);
				/* enable RDE */
				udc_ep0_set_rde(dev);
			पूर्ण
		पूर्ण अन्यथा अणु

			/* received number bytes */
			count = पढ़ोl(&dev->ep[UDC_EP0OUT_IX].regs->sts);
			count = AMD_GETBITS(count, UDC_EPSTS_RX_PKT_SIZE);
			/* out data क्रम fअगरo mode not working */
			count = 0;

			/* 0 packet or real data ? */
			अगर (count != 0) अणु
				ret_val |= udc_data_out_isr(dev, UDC_EP0OUT_IX);
			पूर्ण अन्यथा अणु
				/* dummy पढ़ो confirm */
				पढ़ोl(&dev->ep[UDC_EP0OUT_IX].regs->confirm);
				ret_val = IRQ_HANDLED;
			पूर्ण
		पूर्ण
	पूर्ण

	/* check pending CNAKS */
	अगर (cnak_pending) अणु
		/* CNAk processing when rxfअगरo empty only */
		अगर (पढ़ोl(&dev->regs->sts) & AMD_BIT(UDC_DEVSTS_RXFIFO_EMPTY))
			udc_process_cnak_queue(dev);
	पूर्ण

finished:
	वापस ret_val;
पूर्ण

/* Interrupt handler क्रम Control IN traffic */
अटल irqवापस_t udc_control_in_isr(काष्ठा udc *dev)
अणु
	irqवापस_t ret_val = IRQ_NONE;
	u32 पंचांगp;
	काष्ठा udc_ep *ep;
	काष्ठा udc_request *req;
	अचिन्हित len;

	ep = &dev->ep[UDC_EP0IN_IX];

	/* clear irq */
	ग_लिखोl(AMD_BIT(UDC_EPINT_IN_EP0), &dev->regs->ep_irqsts);

	पंचांगp = पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->sts);
	/* DMA completion */
	अगर (पंचांगp & AMD_BIT(UDC_EPSTS_TDC)) अणु
		VDBG(dev, "isr: TDC clear\n");
		ret_val = IRQ_HANDLED;

		/* clear TDC bit */
		ग_लिखोl(AMD_BIT(UDC_EPSTS_TDC),
				&dev->ep[UDC_EP0IN_IX].regs->sts);

	/* status reg has IN bit set ? */
	पूर्ण अन्यथा अगर (पंचांगp & AMD_BIT(UDC_EPSTS_IN)) अणु
		ret_val = IRQ_HANDLED;

		अगर (ep->dma) अणु
			/* clear IN bit */
			ग_लिखोl(AMD_BIT(UDC_EPSTS_IN),
				&dev->ep[UDC_EP0IN_IX].regs->sts);
		पूर्ण
		अगर (dev->stall_ep0in) अणु
			DBG(dev, "stall ep0in\n");
			/* halt ep0in */
			पंचांगp = पढ़ोl(&ep->regs->ctl);
			पंचांगp |= AMD_BIT(UDC_EPCTL_S);
			ग_लिखोl(पंचांगp, &ep->regs->ctl);
		पूर्ण अन्यथा अणु
			अगर (!list_empty(&ep->queue)) अणु
				/* next request */
				req = list_entry(ep->queue.next,
						काष्ठा udc_request, queue);

				अगर (ep->dma) अणु
					/* ग_लिखो desc poपूर्णांकer */
					ग_लिखोl(req->td_phys, &ep->regs->desptr);
					/* set HOST READY */
					req->td_data->status =
						AMD_ADDBITS(
						req->td_data->status,
						UDC_DMA_STP_STS_BS_HOST_READY,
						UDC_DMA_STP_STS_BS);

					/* set poll demand bit */
					पंचांगp =
					पढ़ोl(&dev->ep[UDC_EP0IN_IX].regs->ctl);
					पंचांगp |= AMD_BIT(UDC_EPCTL_P);
					ग_लिखोl(पंचांगp,
					&dev->ep[UDC_EP0IN_IX].regs->ctl);

					/* all bytes will be transferred */
					req->req.actual = req->req.length;

					/* complete req */
					complete_req(ep, req, 0);

				पूर्ण अन्यथा अणु
					/* ग_लिखो fअगरo */
					udc_txfअगरo_ग_लिखो(ep, &req->req);

					/* lengh bytes transferred */
					len = req->req.length - req->req.actual;
					अगर (len > ep->ep.maxpacket)
						len = ep->ep.maxpacket;

					req->req.actual += len;
					अगर (req->req.actual == req->req.length
						|| (len != ep->ep.maxpacket)) अणु
						/* complete req */
						complete_req(ep, req, 0);
					पूर्ण
				पूर्ण

			पूर्ण
		पूर्ण
		ep->halted = 0;
		dev->stall_ep0in = 0;
		अगर (!ep->dma) अणु
			/* clear IN bit */
			ग_लिखोl(AMD_BIT(UDC_EPSTS_IN),
				&dev->ep[UDC_EP0IN_IX].regs->sts);
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण


/* Interrupt handler क्रम global device events */
अटल irqवापस_t udc_dev_isr(काष्ठा udc *dev, u32 dev_irq)
__releases(dev->lock)
__acquires(dev->lock)
अणु
	irqवापस_t ret_val = IRQ_NONE;
	u32 पंचांगp;
	u32 cfg;
	काष्ठा udc_ep *ep;
	u16 i;
	u8 udc_csr_epix;

	/* SET_CONFIG irq ? */
	अगर (dev_irq & AMD_BIT(UDC_DEVINT_SC)) अणु
		ret_val = IRQ_HANDLED;

		/* पढ़ो config value */
		पंचांगp = पढ़ोl(&dev->regs->sts);
		cfg = AMD_GETBITS(पंचांगp, UDC_DEVSTS_CFG);
		DBG(dev, "SET_CONFIG interrupt: config=%d\n", cfg);
		dev->cur_config = cfg;
		dev->set_cfg_not_acked = 1;

		/* make usb request क्रम gadget driver */
		स_रखो(&setup_data, 0 , माप(जोड़ udc_setup_data));
		setup_data.request.bRequest = USB_REQ_SET_CONFIGURATION;
		setup_data.request.wValue = cpu_to_le16(dev->cur_config);

		/* programm the NE रेजिस्टरs */
		क्रम (i = 0; i < UDC_EP_NUM; i++) अणु
			ep = &dev->ep[i];
			अगर (ep->in) अणु

				/* ep ix in UDC CSR रेजिस्टर space */
				udc_csr_epix = ep->num;


			/* OUT ep */
			पूर्ण अन्यथा अणु
				/* ep ix in UDC CSR रेजिस्टर space */
				udc_csr_epix = ep->num - UDC_CSR_EP_OUT_IX_OFS;
			पूर्ण

			पंचांगp = पढ़ोl(&dev->csr->ne[udc_csr_epix]);
			/* ep cfg */
			पंचांगp = AMD_ADDBITS(पंचांगp, ep->dev->cur_config,
						UDC_CSR_NE_CFG);
			/* ग_लिखो reg */
			ग_लिखोl(पंचांगp, &dev->csr->ne[udc_csr_epix]);

			/* clear stall bits */
			ep->halted = 0;
			पंचांगp = पढ़ोl(&ep->regs->ctl);
			पंचांगp = पंचांगp & AMD_CLEAR_BIT(UDC_EPCTL_S);
			ग_लिखोl(पंचांगp, &ep->regs->ctl);
		पूर्ण
		/* call gadget zero with setup data received */
		spin_unlock(&dev->lock);
		पंचांगp = dev->driver->setup(&dev->gadget, &setup_data.request);
		spin_lock(&dev->lock);

	पूर्ण /* SET_INTERFACE ? */
	अगर (dev_irq & AMD_BIT(UDC_DEVINT_SI)) अणु
		ret_val = IRQ_HANDLED;

		dev->set_cfg_not_acked = 1;
		/* पढ़ो पूर्णांकerface and alt setting values */
		पंचांगp = पढ़ोl(&dev->regs->sts);
		dev->cur_alt = AMD_GETBITS(पंचांगp, UDC_DEVSTS_ALT);
		dev->cur_पूर्णांकf = AMD_GETBITS(पंचांगp, UDC_DEVSTS_INTF);

		/* make usb request क्रम gadget driver */
		स_रखो(&setup_data, 0 , माप(जोड़ udc_setup_data));
		setup_data.request.bRequest = USB_REQ_SET_INTERFACE;
		setup_data.request.bRequestType = USB_RECIP_INTERFACE;
		setup_data.request.wValue = cpu_to_le16(dev->cur_alt);
		setup_data.request.wIndex = cpu_to_le16(dev->cur_पूर्णांकf);

		DBG(dev, "SET_INTERFACE interrupt: alt=%d intf=%d\n",
				dev->cur_alt, dev->cur_पूर्णांकf);

		/* programm the NE रेजिस्टरs */
		क्रम (i = 0; i < UDC_EP_NUM; i++) अणु
			ep = &dev->ep[i];
			अगर (ep->in) अणु

				/* ep ix in UDC CSR रेजिस्टर space */
				udc_csr_epix = ep->num;


			/* OUT ep */
			पूर्ण अन्यथा अणु
				/* ep ix in UDC CSR रेजिस्टर space */
				udc_csr_epix = ep->num - UDC_CSR_EP_OUT_IX_OFS;
			पूर्ण

			/* UDC CSR reg */
			/* set ep values */
			पंचांगp = पढ़ोl(&dev->csr->ne[udc_csr_epix]);
			/* ep पूर्णांकerface */
			पंचांगp = AMD_ADDBITS(पंचांगp, ep->dev->cur_पूर्णांकf,
						UDC_CSR_NE_INTF);
			/* पंचांगp = AMD_ADDBITS(पंचांगp, 2, UDC_CSR_NE_INTF); */
			/* ep alt */
			पंचांगp = AMD_ADDBITS(पंचांगp, ep->dev->cur_alt,
						UDC_CSR_NE_ALT);
			/* ग_लिखो reg */
			ग_लिखोl(पंचांगp, &dev->csr->ne[udc_csr_epix]);

			/* clear stall bits */
			ep->halted = 0;
			पंचांगp = पढ़ोl(&ep->regs->ctl);
			पंचांगp = पंचांगp & AMD_CLEAR_BIT(UDC_EPCTL_S);
			ग_लिखोl(पंचांगp, &ep->regs->ctl);
		पूर्ण

		/* call gadget zero with setup data received */
		spin_unlock(&dev->lock);
		पंचांगp = dev->driver->setup(&dev->gadget, &setup_data.request);
		spin_lock(&dev->lock);

	पूर्ण /* USB reset */
	अगर (dev_irq & AMD_BIT(UDC_DEVINT_UR)) अणु
		DBG(dev, "USB Reset interrupt\n");
		ret_val = IRQ_HANDLED;

		/* allow soft reset when suspend occurs */
		soft_reset_occured = 0;

		dev->रुकोing_zlp_ack_ep0in = 0;
		dev->set_cfg_not_acked = 0;

		/* mask not needed पूर्णांकerrupts */
		udc_mask_unused_पूर्णांकerrupts(dev);

		/* call gadget to resume and reset configs etc. */
		spin_unlock(&dev->lock);
		अगर (dev->sys_suspended && dev->driver->resume) अणु
			dev->driver->resume(&dev->gadget);
			dev->sys_suspended = 0;
		पूर्ण
		usb_gadget_udc_reset(&dev->gadget, dev->driver);
		spin_lock(&dev->lock);

		/* disable ep0 to empty req queue */
		empty_req_queue(&dev->ep[UDC_EP0IN_IX]);
		ep_init(dev->regs, &dev->ep[UDC_EP0IN_IX]);

		/* soft reset when rxfअगरo not empty */
		पंचांगp = पढ़ोl(&dev->regs->sts);
		अगर (!(पंचांगp & AMD_BIT(UDC_DEVSTS_RXFIFO_EMPTY))
				&& !soft_reset_after_usbreset_occured) अणु
			udc_soft_reset(dev);
			soft_reset_after_usbreset_occured++;
		पूर्ण

		/*
		 * DMA reset to समाप्त potential old DMA hw hang,
		 * POLL bit is alपढ़ोy reset by ep_init() through
		 * disconnect()
		 */
		DBG(dev, "DMA machine reset\n");
		पंचांगp = पढ़ोl(&dev->regs->cfg);
		ग_लिखोl(पंचांगp | AMD_BIT(UDC_DEVCFG_DMARST), &dev->regs->cfg);
		ग_लिखोl(पंचांगp, &dev->regs->cfg);

		/* put पूर्णांकo initial config */
		udc_basic_init(dev);

		/* enable device setup पूर्णांकerrupts */
		udc_enable_dev_setup_पूर्णांकerrupts(dev);

		/* enable suspend पूर्णांकerrupt */
		पंचांगp = पढ़ोl(&dev->regs->irqmsk);
		पंचांगp &= AMD_UNMASK_BIT(UDC_DEVINT_US);
		ग_लिखोl(पंचांगp, &dev->regs->irqmsk);

	पूर्ण /* USB suspend */
	अगर (dev_irq & AMD_BIT(UDC_DEVINT_US)) अणु
		DBG(dev, "USB Suspend interrupt\n");
		ret_val = IRQ_HANDLED;
		अगर (dev->driver->suspend) अणु
			spin_unlock(&dev->lock);
			dev->sys_suspended = 1;
			dev->driver->suspend(&dev->gadget);
			spin_lock(&dev->lock);
		पूर्ण
	पूर्ण /* new speed ? */
	अगर (dev_irq & AMD_BIT(UDC_DEVINT_ENUM)) अणु
		DBG(dev, "ENUM interrupt\n");
		ret_val = IRQ_HANDLED;
		soft_reset_after_usbreset_occured = 0;

		/* disable ep0 to empty req queue */
		empty_req_queue(&dev->ep[UDC_EP0IN_IX]);
		ep_init(dev->regs, &dev->ep[UDC_EP0IN_IX]);

		/* link up all endpoपूर्णांकs */
		udc_setup_endpoपूर्णांकs(dev);
		dev_info(dev->dev, "Connect: %s\n",
			 usb_speed_string(dev->gadget.speed));

		/* init ep 0 */
		activate_control_endpoपूर्णांकs(dev);

		/* enable ep0 पूर्णांकerrupts */
		udc_enable_ep0_पूर्णांकerrupts(dev);
	पूर्ण
	/* session valid change पूर्णांकerrupt */
	अगर (dev_irq & AMD_BIT(UDC_DEVINT_SVC)) अणु
		DBG(dev, "USB SVC interrupt\n");
		ret_val = IRQ_HANDLED;

		/* check that session is not valid to detect disconnect */
		पंचांगp = पढ़ोl(&dev->regs->sts);
		अगर (!(पंचांगp & AMD_BIT(UDC_DEVSTS_SESSVLD))) अणु
			/* disable suspend पूर्णांकerrupt */
			पंचांगp = पढ़ोl(&dev->regs->irqmsk);
			पंचांगp |= AMD_BIT(UDC_DEVINT_US);
			ग_लिखोl(पंचांगp, &dev->regs->irqmsk);
			DBG(dev, "USB Disconnect (session valid low)\n");
			/* cleanup on disconnect */
			usb_disconnect(udc);
		पूर्ण

	पूर्ण

	वापस ret_val;
पूर्ण

/* Interrupt Service Routine, see Linux Kernel Doc क्रम parameters */
irqवापस_t udc_irq(पूर्णांक irq, व्योम *pdev)
अणु
	काष्ठा udc *dev = pdev;
	u32 reg;
	u16 i;
	u32 ep_irq;
	irqवापस_t ret_val = IRQ_NONE;

	spin_lock(&dev->lock);

	/* check क्रम ep irq */
	reg = पढ़ोl(&dev->regs->ep_irqsts);
	अगर (reg) अणु
		अगर (reg & AMD_BIT(UDC_EPINT_OUT_EP0))
			ret_val |= udc_control_out_isr(dev);
		अगर (reg & AMD_BIT(UDC_EPINT_IN_EP0))
			ret_val |= udc_control_in_isr(dev);

		/*
		 * data endpoपूर्णांक
		 * iterate ep's
		 */
		क्रम (i = 1; i < UDC_EP_NUM; i++) अणु
			ep_irq = 1 << i;
			अगर (!(reg & ep_irq) || i == UDC_EPINT_OUT_EP0)
				जारी;

			/* clear irq status */
			ग_लिखोl(ep_irq, &dev->regs->ep_irqsts);

			/* irq क्रम out ep ? */
			अगर (i > UDC_EPIN_NUM)
				ret_val |= udc_data_out_isr(dev, i);
			अन्यथा
				ret_val |= udc_data_in_isr(dev, i);
		पूर्ण

	पूर्ण


	/* check क्रम dev irq */
	reg = पढ़ोl(&dev->regs->irqsts);
	अगर (reg) अणु
		/* clear irq */
		ग_लिखोl(reg, &dev->regs->irqsts);
		ret_val |= udc_dev_isr(dev, reg);
	पूर्ण


	spin_unlock(&dev->lock);
	वापस ret_val;
पूर्ण
EXPORT_SYMBOL_GPL(udc_irq);

/* Tears करोwn device */
व्योम gadget_release(काष्ठा device *pdev)
अणु
	काष्ठा amd5536udc *dev = dev_get_drvdata(pdev);
	kमुक्त(dev);
पूर्ण
EXPORT_SYMBOL_GPL(gadget_release);

/* Cleanup on device हटाओ */
व्योम udc_हटाओ(काष्ठा udc *dev)
अणु
	/* हटाओ समयr */
	stop_समयr++;
	अगर (समयr_pending(&udc_समयr))
		रुको_क्रम_completion(&on_निकास);
	del_समयr_sync(&udc_समयr);
	/* हटाओ pollstall समयr */
	stop_pollstall_समयr++;
	अगर (समयr_pending(&udc_pollstall_समयr))
		रुको_क्रम_completion(&on_pollstall_निकास);
	del_समयr_sync(&udc_pollstall_समयr);
	udc = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(udc_हटाओ);

/* मुक्त all the dma pools */
व्योम मुक्त_dma_pools(काष्ठा udc *dev)
अणु
	dma_pool_मुक्त(dev->stp_requests, dev->ep[UDC_EP0OUT_IX].td,
		      dev->ep[UDC_EP0OUT_IX].td_phys);
	dma_pool_मुक्त(dev->stp_requests, dev->ep[UDC_EP0OUT_IX].td_stp,
		      dev->ep[UDC_EP0OUT_IX].td_stp_dma);
	dma_pool_destroy(dev->stp_requests);
	dma_pool_destroy(dev->data_requests);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_dma_pools);

/* create dma pools on init */
पूर्णांक init_dma_pools(काष्ठा udc *dev)
अणु
	काष्ठा udc_stp_dma	*td_stp;
	काष्ठा udc_data_dma	*td_data;
	पूर्णांक retval;

	/* consistent DMA mode setting ? */
	अगर (use_dma_ppb) अणु
		use_dma_bufferfill_mode = 0;
	पूर्ण अन्यथा अणु
		use_dma_ppb_du = 0;
		use_dma_bufferfill_mode = 1;
	पूर्ण

	/* DMA setup */
	dev->data_requests = dma_pool_create("data_requests", dev->dev,
		माप(काष्ठा udc_data_dma), 0, 0);
	अगर (!dev->data_requests) अणु
		DBG(dev, "can't get request data pool\n");
		वापस -ENOMEM;
	पूर्ण

	/* EP0 in dma regs = dev control regs */
	dev->ep[UDC_EP0IN_IX].dma = &dev->regs->ctl;

	/* dma desc क्रम setup data */
	dev->stp_requests = dma_pool_create("setup requests", dev->dev,
		माप(काष्ठा udc_stp_dma), 0, 0);
	अगर (!dev->stp_requests) अणु
		DBG(dev, "can't get stp request pool\n");
		retval = -ENOMEM;
		जाओ err_create_dma_pool;
	पूर्ण
	/* setup */
	td_stp = dma_pool_alloc(dev->stp_requests, GFP_KERNEL,
				&dev->ep[UDC_EP0OUT_IX].td_stp_dma);
	अगर (!td_stp) अणु
		retval = -ENOMEM;
		जाओ err_alloc_dma;
	पूर्ण
	dev->ep[UDC_EP0OUT_IX].td_stp = td_stp;

	/* data: 0 packets !? */
	td_data = dma_pool_alloc(dev->stp_requests, GFP_KERNEL,
				&dev->ep[UDC_EP0OUT_IX].td_phys);
	अगर (!td_data) अणु
		retval = -ENOMEM;
		जाओ err_alloc_phys;
	पूर्ण
	dev->ep[UDC_EP0OUT_IX].td = td_data;
	वापस 0;

err_alloc_phys:
	dma_pool_मुक्त(dev->stp_requests, dev->ep[UDC_EP0OUT_IX].td_stp,
		      dev->ep[UDC_EP0OUT_IX].td_stp_dma);
err_alloc_dma:
	dma_pool_destroy(dev->stp_requests);
	dev->stp_requests = शून्य;
err_create_dma_pool:
	dma_pool_destroy(dev->data_requests);
	dev->data_requests = शून्य;
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(init_dma_pools);

/* general probe */
पूर्णांक udc_probe(काष्ठा udc *dev)
अणु
	अक्षर		पंचांगp[128];
	u32		reg;
	पूर्णांक		retval;

	/* device काष्ठा setup */
	dev->gadget.ops = &udc_ops;

	dev_set_name(&dev->gadget.dev, "gadget");
	dev->gadget.name = name;
	dev->gadget.max_speed = USB_SPEED_HIGH;

	/* init रेजिस्टरs, पूर्णांकerrupts, ... */
	startup_रेजिस्टरs(dev);

	dev_info(dev->dev, "%s\n", mod_desc);

	snम_लिखो(पंचांगp, माप(पंचांगp), "%d", dev->irq);

	/* Prपूर्णांक this device info क्रम AMD chips only*/
	अगर (dev->chiprev == UDC_HSA0_REV ||
	    dev->chiprev == UDC_HSB1_REV) अणु
		dev_info(dev->dev, "irq %s, pci mem %08lx, chip rev %02x(Geode5536 %s)\n",
			 पंचांगp, dev->phys_addr, dev->chiprev,
			 (dev->chiprev == UDC_HSA0_REV) ?
			 "A0" : "B1");
		म_नकल(पंचांगp, UDC_DRIVER_VERSION_STRING);
		अगर (dev->chiprev == UDC_HSA0_REV) अणु
			dev_err(dev->dev, "chip revision is A0; too old\n");
			retval = -ENODEV;
			जाओ finished;
		पूर्ण
		dev_info(dev->dev,
			 "driver version: %s(for Geode5536 B1)\n", पंचांगp);
	पूर्ण

	udc = dev;

	retval = usb_add_gadget_udc_release(udc->dev, &dev->gadget,
					    gadget_release);
	अगर (retval)
		जाओ finished;

	/* समयr init */
	समयr_setup(&udc_समयr, udc_समयr_function, 0);
	समयr_setup(&udc_pollstall_समयr, udc_pollstall_समयr_function, 0);

	/* set SD */
	reg = पढ़ोl(&dev->regs->ctl);
	reg |= AMD_BIT(UDC_DEVCTL_SD);
	ग_लिखोl(reg, &dev->regs->ctl);

	/* prपूर्णांक dev रेजिस्टर info */
	prपूर्णांक_regs(dev);

	वापस 0;

finished:
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(udc_probe);

MODULE_DESCRIPTION(UDC_MOD_DESCRIPTION);
MODULE_AUTHOR("Thomas Dahlmann");
MODULE_LICENSE("GPL");
