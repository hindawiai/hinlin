<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MUSB OTG driver core code
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

/*
 * Inventra (Multipoपूर्णांक) Dual-Role Controller Driver क्रम Linux.
 *
 * This consists of a Host Controller Driver (HCD) and a peripheral
 * controller driver implementing the "Gadget" API; OTG support is
 * in the works.  These are normal Linux-USB controller drivers which
 * use IRQs and have no dedicated thपढ़ो.
 *
 * This version of the driver has only been used with products from
 * Texas Instruments.  Those products पूर्णांकegrate the Inventra logic
 * with other DMA, IRQ, and bus modules, as well as other logic that
 * needs to be reflected in this driver.
 *
 *
 * NOTE:  the original Mentor code here was pretty much a collection
 * of mechanisms that करोn't seem to have been fully पूर्णांकegrated/working
 * क्रम *any* Linux kernel version.  This version aims at Linux 2.6.now,
 * Key खोलो issues include:
 *
 *  - Lack of host-side transaction scheduling, क्रम all transfer types.
 *    The hardware करोesn't करो it; instead, software must.
 *
 *    This is not an issue क्रम OTG devices that करोn't support बाह्यal
 *    hubs, but क्रम more "normal" USB hosts it's a user issue that the
 *    "multipoint" support करोesn't scale in the expected ways.  That
 *    includes DaVinci EVM in a common non-OTG mode.
 *
 *      * Control and bulk use dedicated endpoपूर्णांकs, and there's as
 *        yet no mechanism to either (a) reclaim the hardware when
 *        peripherals are NAKing, which माला_लो complicated with bulk
 *        endpoपूर्णांकs, or (b) use more than a single bulk endpoपूर्णांक in
 *        each direction.
 *
 *        RESULT:  one device may be perceived as blocking another one.
 *
 *      * Interrupt and isochronous will dynamically allocate endpoपूर्णांक
 *        hardware, but (a) there's no record keeping क्रम bandwidth;
 *        (b) in the common हाल that few endpoपूर्णांकs are available, there
 *        is no mechanism to reuse endpoपूर्णांकs to talk to multiple devices.
 *
 *        RESULT:  At one extreme, bandwidth can be overcommitted in
 *        some hardware configurations, no faults will be reported.
 *        At the other extreme, the bandwidth capabilities which करो
 *        exist tend to be severely undercommitted.  You can't yet hook
 *        up both a keyboard and a mouse to an बाह्यal USB hub.
 */

/*
 * This माला_लो many kinds of configuration inक्रमmation:
 *	- Kconfig क्रम everything user-configurable
 *	- platक्रमm_device क्रम addressing, irq, and platक्रमm_data
 *	- platक्रमm_data is mostly क्रम board-specअगरic inक्रमmation
 *	  (plus recentrly, SOC or family details)
 *
 * Most of the conditional compilation will (someday) vanish.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/kobject.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/of.h>

#समावेश "musb_core.h"
#समावेश "musb_trace.h"

#घोषणा TA_WAIT_BCON(m) max_t(पूर्णांक, (m)->a_रुको_bcon, OTG_TIME_A_WAIT_BCON)


#घोषणा DRIVER_AUTHOR "Mentor Graphics, Texas Instruments, Nokia"
#घोषणा DRIVER_DESC "Inventra Dual-Role USB Controller Driver"

#घोषणा MUSB_VERSION "6.0"

#घोषणा DRIVER_INFO DRIVER_DESC ", v" MUSB_VERSION

#घोषणा MUSB_DRIVER_NAME "musb-hdrc"
स्थिर अक्षर musb_driver_name[] = MUSB_DRIVER_NAME;

MODULE_DESCRIPTION(DRIVER_INFO);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" MUSB_DRIVER_NAME);


/*-------------------------------------------------------------------------*/

अटल अंतरभूत काष्ठा musb *dev_to_musb(काष्ठा device *dev)
अणु
	वापस dev_get_drvdata(dev);
पूर्ण

क्रमागत musb_mode musb_get_mode(काष्ठा device *dev)
अणु
	क्रमागत usb_dr_mode mode;

	mode = usb_get_dr_mode(dev);
	चयन (mode) अणु
	हाल USB_DR_MODE_HOST:
		वापस MUSB_HOST;
	हाल USB_DR_MODE_PERIPHERAL:
		वापस MUSB_PERIPHERAL;
	हाल USB_DR_MODE_OTG:
	हाल USB_DR_MODE_UNKNOWN:
	शेष:
		वापस MUSB_OTG;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(musb_get_mode);

/*-------------------------------------------------------------------------*/

अटल पूर्णांक musb_ulpi_पढ़ो(काष्ठा usb_phy *phy, u32 reg)
अणु
	व्योम __iomem *addr = phy->io_priv;
	पूर्णांक	i = 0;
	u8	r;
	u8	घातer;
	पूर्णांक	ret;

	pm_runसमय_get_sync(phy->io_dev);

	/* Make sure the transceiver is not in low घातer mode */
	घातer = musb_पढ़ोb(addr, MUSB_POWER);
	घातer &= ~MUSB_POWER_SUSPENDM;
	musb_ग_लिखोb(addr, MUSB_POWER, घातer);

	/* REVISIT: musbhdrc_ulpi_an.pdf recommends setting the
	 * ULPICarKitControlDisableUTMI after clearing POWER_SUSPENDM.
	 */

	musb_ग_लिखोb(addr, MUSB_ULPI_REG_ADDR, (u8)reg);
	musb_ग_लिखोb(addr, MUSB_ULPI_REG_CONTROL,
			MUSB_ULPI_REG_REQ | MUSB_ULPI_RDN_WR);

	जबतक (!(musb_पढ़ोb(addr, MUSB_ULPI_REG_CONTROL)
				& MUSB_ULPI_REG_CMPLT)) अणु
		i++;
		अगर (i == 10000) अणु
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण

	पूर्ण
	r = musb_पढ़ोb(addr, MUSB_ULPI_REG_CONTROL);
	r &= ~MUSB_ULPI_REG_CMPLT;
	musb_ग_लिखोb(addr, MUSB_ULPI_REG_CONTROL, r);

	ret = musb_पढ़ोb(addr, MUSB_ULPI_REG_DATA);

out:
	pm_runसमय_put(phy->io_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक musb_ulpi_ग_लिखो(काष्ठा usb_phy *phy, u32 val, u32 reg)
अणु
	व्योम __iomem *addr = phy->io_priv;
	पूर्णांक	i = 0;
	u8	r = 0;
	u8	घातer;
	पूर्णांक	ret = 0;

	pm_runसमय_get_sync(phy->io_dev);

	/* Make sure the transceiver is not in low घातer mode */
	घातer = musb_पढ़ोb(addr, MUSB_POWER);
	घातer &= ~MUSB_POWER_SUSPENDM;
	musb_ग_लिखोb(addr, MUSB_POWER, घातer);

	musb_ग_लिखोb(addr, MUSB_ULPI_REG_ADDR, (u8)reg);
	musb_ग_लिखोb(addr, MUSB_ULPI_REG_DATA, (u8)val);
	musb_ग_लिखोb(addr, MUSB_ULPI_REG_CONTROL, MUSB_ULPI_REG_REQ);

	जबतक (!(musb_पढ़ोb(addr, MUSB_ULPI_REG_CONTROL)
				& MUSB_ULPI_REG_CMPLT)) अणु
		i++;
		अगर (i == 10000) अणु
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण
	पूर्ण

	r = musb_पढ़ोb(addr, MUSB_ULPI_REG_CONTROL);
	r &= ~MUSB_ULPI_REG_CMPLT;
	musb_ग_लिखोb(addr, MUSB_ULPI_REG_CONTROL, r);

out:
	pm_runसमय_put(phy->io_dev);

	वापस ret;
पूर्ण

अटल काष्ठा usb_phy_io_ops musb_ulpi_access = अणु
	.पढ़ो = musb_ulpi_पढ़ो,
	.ग_लिखो = musb_ulpi_ग_लिखो,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल u32 musb_शेष_fअगरo_offset(u8 epnum)
अणु
	वापस 0x20 + (epnum * 4);
पूर्ण

/* "flat" mapping: each endpoपूर्णांक has its own i/o address */
अटल व्योम musb_flat_ep_select(व्योम __iomem *mbase, u8 epnum)
अणु
पूर्ण

अटल u32 musb_flat_ep_offset(u8 epnum, u16 offset)
अणु
	वापस 0x100 + (0x10 * epnum) + offset;
पूर्ण

/* "indexed" mapping: INDEX रेजिस्टर controls रेजिस्टर bank select */
अटल व्योम musb_indexed_ep_select(व्योम __iomem *mbase, u8 epnum)
अणु
	musb_ग_लिखोb(mbase, MUSB_INDEX, epnum);
पूर्ण

अटल u32 musb_indexed_ep_offset(u8 epnum, u16 offset)
अणु
	वापस 0x10 + offset;
पूर्ण

अटल u32 musb_शेष_busctl_offset(u8 epnum, u16 offset)
अणु
	वापस 0x80 + (0x08 * epnum) + offset;
पूर्ण

अटल u8 musb_शेष_पढ़ोb(व्योम __iomem *addr, u32 offset)
अणु
	u8 data =  __raw_पढ़ोb(addr + offset);

	trace_musb_पढ़ोb(__builtin_वापस_address(0), addr, offset, data);
	वापस data;
पूर्ण

अटल व्योम musb_शेष_ग_लिखोb(व्योम __iomem *addr, u32 offset, u8 data)
अणु
	trace_musb_ग_लिखोb(__builtin_वापस_address(0), addr, offset, data);
	__raw_ग_लिखोb(data, addr + offset);
पूर्ण

अटल u16 musb_शेष_पढ़ोw(व्योम __iomem *addr, u32 offset)
अणु
	u16 data = __raw_पढ़ोw(addr + offset);

	trace_musb_पढ़ोw(__builtin_वापस_address(0), addr, offset, data);
	वापस data;
पूर्ण

अटल व्योम musb_शेष_ग_लिखोw(व्योम __iomem *addr, u32 offset, u16 data)
अणु
	trace_musb_ग_लिखोw(__builtin_वापस_address(0), addr, offset, data);
	__raw_ग_लिखोw(data, addr + offset);
पूर्ण

अटल u16 musb_शेष_get_toggle(काष्ठा musb_qh *qh, पूर्णांक is_out)
अणु
	व्योम __iomem *epio = qh->hw_ep->regs;
	u16 csr;

	अगर (is_out)
		csr = musb_पढ़ोw(epio, MUSB_TXCSR) & MUSB_TXCSR_H_DATATOGGLE;
	अन्यथा
		csr = musb_पढ़ोw(epio, MUSB_RXCSR) & MUSB_RXCSR_H_DATATOGGLE;

	वापस csr;
पूर्ण

अटल u16 musb_शेष_set_toggle(काष्ठा musb_qh *qh, पूर्णांक is_out,
				   काष्ठा urb *urb)
अणु
	u16 csr;
	u16 toggle;

	toggle = usb_gettoggle(urb->dev, qh->epnum, is_out);

	अगर (is_out)
		csr = toggle ? (MUSB_TXCSR_H_WR_DATATOGGLE
				| MUSB_TXCSR_H_DATATOGGLE)
				: MUSB_TXCSR_CLRDATATOG;
	अन्यथा
		csr = toggle ? (MUSB_RXCSR_H_WR_DATATOGGLE
				| MUSB_RXCSR_H_DATATOGGLE) : 0;

	वापस csr;
पूर्ण

/*
 * Load an endpoपूर्णांक's FIFO
 */
अटल व्योम musb_शेष_ग_लिखो_fअगरo(काष्ठा musb_hw_ep *hw_ep, u16 len,
				    स्थिर u8 *src)
अणु
	काष्ठा musb *musb = hw_ep->musb;
	व्योम __iomem *fअगरo = hw_ep->fअगरo;

	अगर (unlikely(len == 0))
		वापस;

	prefetch((u8 *)src);

	dev_dbg(musb->controller, "%cX ep%d fifo %p count %d buf %p\n",
			'T', hw_ep->epnum, fअगरo, len, src);

	/* we can't assume unaligned पढ़ोs work */
	अगर (likely((0x01 & (अचिन्हित दीर्घ) src) == 0)) अणु
		u16	index = 0;

		/* best हाल is 32bit-aligned source address */
		अगर ((0x02 & (अचिन्हित दीर्घ) src) == 0) अणु
			अगर (len >= 4) अणु
				ioग_लिखो32_rep(fअगरo, src + index, len >> 2);
				index += len & ~0x03;
			पूर्ण
			अगर (len & 0x02) अणु
				__raw_ग_लिखोw(*(u16 *)&src[index], fअगरo);
				index += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (len >= 2) अणु
				ioग_लिखो16_rep(fअगरo, src + index, len >> 1);
				index += len & ~0x01;
			पूर्ण
		पूर्ण
		अगर (len & 0x01)
			__raw_ग_लिखोb(src[index], fअगरo);
	पूर्ण अन्यथा  अणु
		/* byte aligned */
		ioग_लिखो8_rep(fअगरo, src, len);
	पूर्ण
पूर्ण

/*
 * Unload an endpoपूर्णांक's FIFO
 */
अटल व्योम musb_शेष_पढ़ो_fअगरo(काष्ठा musb_hw_ep *hw_ep, u16 len, u8 *dst)
अणु
	काष्ठा musb *musb = hw_ep->musb;
	व्योम __iomem *fअगरo = hw_ep->fअगरo;

	अगर (unlikely(len == 0))
		वापस;

	dev_dbg(musb->controller, "%cX ep%d fifo %p count %d buf %p\n",
			'R', hw_ep->epnum, fअगरo, len, dst);

	/* we can't assume unaligned ग_लिखोs work */
	अगर (likely((0x01 & (अचिन्हित दीर्घ) dst) == 0)) अणु
		u16	index = 0;

		/* best हाल is 32bit-aligned destination address */
		अगर ((0x02 & (अचिन्हित दीर्घ) dst) == 0) अणु
			अगर (len >= 4) अणु
				ioपढ़ो32_rep(fअगरo, dst, len >> 2);
				index = len & ~0x03;
			पूर्ण
			अगर (len & 0x02) अणु
				*(u16 *)&dst[index] = __raw_पढ़ोw(fअगरo);
				index += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (len >= 2) अणु
				ioपढ़ो16_rep(fअगरo, dst, len >> 1);
				index = len & ~0x01;
			पूर्ण
		पूर्ण
		अगर (len & 0x01)
			dst[index] = __raw_पढ़ोb(fअगरo);
	पूर्ण अन्यथा  अणु
		/* byte aligned */
		ioपढ़ो8_rep(fअगरo, dst, len);
	पूर्ण
पूर्ण

/*
 * Old style IO functions
 */
u8 (*musb_पढ़ोb)(व्योम __iomem *addr, u32 offset);
EXPORT_SYMBOL_GPL(musb_पढ़ोb);

व्योम (*musb_ग_लिखोb)(व्योम __iomem *addr, u32 offset, u8 data);
EXPORT_SYMBOL_GPL(musb_ग_लिखोb);

u8 (*musb_clearb)(व्योम __iomem *addr, u32 offset);
EXPORT_SYMBOL_GPL(musb_clearb);

u16 (*musb_पढ़ोw)(व्योम __iomem *addr, u32 offset);
EXPORT_SYMBOL_GPL(musb_पढ़ोw);

व्योम (*musb_ग_लिखोw)(व्योम __iomem *addr, u32 offset, u16 data);
EXPORT_SYMBOL_GPL(musb_ग_लिखोw);

u16 (*musb_clearw)(व्योम __iomem *addr, u32 offset);
EXPORT_SYMBOL_GPL(musb_clearw);

u32 musb_पढ़ोl(व्योम __iomem *addr, u32 offset)
अणु
	u32 data = __raw_पढ़ोl(addr + offset);

	trace_musb_पढ़ोl(__builtin_वापस_address(0), addr, offset, data);
	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(musb_पढ़ोl);

व्योम musb_ग_लिखोl(व्योम __iomem *addr, u32 offset, u32 data)
अणु
	trace_musb_ग_लिखोl(__builtin_वापस_address(0), addr, offset, data);
	__raw_ग_लिखोl(data, addr + offset);
पूर्ण
EXPORT_SYMBOL_GPL(musb_ग_लिखोl);

#अगर_अघोषित CONFIG_MUSB_PIO_ONLY
काष्ठा dma_controller *
(*musb_dma_controller_create)(काष्ठा musb *musb, व्योम __iomem *base);
EXPORT_SYMBOL(musb_dma_controller_create);

व्योम (*musb_dma_controller_destroy)(काष्ठा dma_controller *c);
EXPORT_SYMBOL(musb_dma_controller_destroy);
#पूर्ण_अगर

/*
 * New style IO functions
 */
व्योम musb_पढ़ो_fअगरo(काष्ठा musb_hw_ep *hw_ep, u16 len, u8 *dst)
अणु
	वापस hw_ep->musb->io.पढ़ो_fअगरo(hw_ep, len, dst);
पूर्ण

व्योम musb_ग_लिखो_fअगरo(काष्ठा musb_hw_ep *hw_ep, u16 len, स्थिर u8 *src)
अणु
	वापस hw_ep->musb->io.ग_लिखो_fअगरo(hw_ep, len, src);
पूर्ण

अटल u8 musb_पढ़ो_devctl(काष्ठा musb *musb)
अणु
	वापस musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
पूर्ण

/**
 * musb_set_host - set and initialize host mode
 * @musb: musb controller driver data
 *
 * At least some musb revisions need to enable devctl session bit in
 * peripheral mode to चयन to host mode. Initializes things to host
 * mode and sets A_IDLE. SoC glue needs to advance state further
 * based on phy provided VBUS state.
 *
 * Note that the SoC glue code may need to रुको क्रम musb to settle
 * on enable beक्रमe calling this to aव्योम babble.
 */
पूर्णांक musb_set_host(काष्ठा musb *musb)
अणु
	पूर्णांक error = 0;
	u8 devctl;

	अगर (!musb)
		वापस -EINVAL;

	devctl = musb_पढ़ो_devctl(musb);
	अगर (!(devctl & MUSB_DEVCTL_BDEVICE)) अणु
		dev_info(musb->controller,
			 "%s: already in host mode: %02x\n",
			 __func__, devctl);
		जाओ init_data;
	पूर्ण

	devctl |= MUSB_DEVCTL_SESSION;
	musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);

	error = पढ़ोx_poll_समयout(musb_पढ़ो_devctl, musb, devctl,
				   !(devctl & MUSB_DEVCTL_BDEVICE), 5000,
				   1000000);
	अगर (error) अणु
		dev_err(musb->controller, "%s: could not set host: %02x\n",
			__func__, devctl);

		वापस error;
	पूर्ण

init_data:
	musb->is_active = 1;
	musb->xceiv->otg->state = OTG_STATE_A_IDLE;
	MUSB_HST_MODE(musb);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(musb_set_host);

/**
 * musb_set_peripheral - set and initialize peripheral mode
 * @musb: musb controller driver data
 *
 * Clears devctl session bit and initializes things क्रम peripheral
 * mode and sets B_IDLE. SoC glue needs to advance state further
 * based on phy provided VBUS state.
 */
पूर्णांक musb_set_peripheral(काष्ठा musb *musb)
अणु
	पूर्णांक error = 0;
	u8 devctl;

	अगर (!musb)
		वापस -EINVAL;

	devctl = musb_पढ़ो_devctl(musb);
	अगर (devctl & MUSB_DEVCTL_BDEVICE) अणु
		dev_info(musb->controller,
			 "%s: already in peripheral mode: %02x\n",
			 __func__, devctl);

		जाओ init_data;
	पूर्ण

	devctl &= ~MUSB_DEVCTL_SESSION;
	musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);

	error = पढ़ोx_poll_समयout(musb_पढ़ो_devctl, musb, devctl,
				   devctl & MUSB_DEVCTL_BDEVICE, 5000,
				   1000000);
	अगर (error) अणु
		dev_err(musb->controller, "%s: could not set peripheral: %02x\n",
			__func__, devctl);

		वापस error;
	पूर्ण

init_data:
	musb->is_active = 0;
	musb->xceiv->otg->state = OTG_STATE_B_IDLE;
	MUSB_DEV_MODE(musb);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(musb_set_peripheral);

/*-------------------------------------------------------------------------*/

/* क्रम high speed test mode; see USB 2.0 spec 7.1.20 */
अटल स्थिर u8 musb_test_packet[53] = अणु
	/* implicit SYNC then DATA0 to start */

	/* JKJKJKJK x9 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* JJKKJJKK x8 */
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	/* JJJJKKKK x8 */
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	/* JJJJJJJKKKKKKK x8 */
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	/* JJJJJJJK x8 */
	0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd,
	/* JKKKKKKK x10, JK */
	0xfc, 0x7e, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0x7e

	/* implicit CRC16 then EOP to end */
पूर्ण;

व्योम musb_load_testpacket(काष्ठा musb *musb)
अणु
	व्योम __iomem	*regs = musb->endpoपूर्णांकs[0].regs;

	musb_ep_select(musb->mregs, 0);
	musb_ग_लिखो_fअगरo(musb->control_ep,
			माप(musb_test_packet), musb_test_packet);
	musb_ग_लिखोw(regs, MUSB_CSR0, MUSB_CSR0_TXPKTRDY);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Handles OTG hnp समयouts, such as b_ase0_brst
 */
अटल व्योम musb_otg_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा musb	*musb = from_समयr(musb, t, otg_समयr);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&musb->lock, flags);
	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_B_WAIT_ACON:
		musb_dbg(musb,
			"HNP: b_wait_acon timeout; back to b_peripheral");
		musb_g_disconnect(musb);
		musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		musb->is_active = 0;
		अवरोध;
	हाल OTG_STATE_A_SUSPEND:
	हाल OTG_STATE_A_WAIT_BCON:
		musb_dbg(musb, "HNP: %s timeout",
			usb_otg_state_string(musb->xceiv->otg->state));
		musb_platक्रमm_set_vbus(musb, 0);
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VFALL;
		अवरोध;
	शेष:
		musb_dbg(musb, "HNP: Unhandled mode %s",
			usb_otg_state_string(musb->xceiv->otg->state));
	पूर्ण
	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

/*
 * Stops the HNP transition. Caller must take care of locking.
 */
व्योम musb_hnp_stop(काष्ठा musb *musb)
अणु
	काष्ठा usb_hcd	*hcd = musb->hcd;
	व्योम __iomem	*mbase = musb->mregs;
	u8	reg;

	musb_dbg(musb, "HNP: stop from %s",
			usb_otg_state_string(musb->xceiv->otg->state));

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_PERIPHERAL:
		musb_g_disconnect(musb);
		musb_dbg(musb, "HNP: back to %s",
			usb_otg_state_string(musb->xceiv->otg->state));
		अवरोध;
	हाल OTG_STATE_B_HOST:
		musb_dbg(musb, "HNP: Disabling HR");
		अगर (hcd)
			hcd->self.is_b_host = 0;
		musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		MUSB_DEV_MODE(musb);
		reg = musb_पढ़ोb(mbase, MUSB_POWER);
		reg |= MUSB_POWER_SUSPENDM;
		musb_ग_लिखोb(mbase, MUSB_POWER, reg);
		/* REVISIT: Start SESSION_REQUEST here? */
		अवरोध;
	शेष:
		musb_dbg(musb, "HNP: Stopping in unknown state %s",
			usb_otg_state_string(musb->xceiv->otg->state));
	पूर्ण

	/*
	 * When वापसing to A state after HNP, aव्योम hub_port_rebounce(),
	 * which cause occasional OPT A "Did not receive reset after connect"
	 * errors.
	 */
	musb->port1_status &= ~(USB_PORT_STAT_C_CONNECTION << 16);
पूर्ण

अटल व्योम musb_recover_from_babble(काष्ठा musb *musb);

अटल व्योम musb_handle_पूर्णांकr_resume(काष्ठा musb *musb, u8 devctl)
अणु
	musb_dbg(musb, "RESUME (%s)",
			usb_otg_state_string(musb->xceiv->otg->state));

	अगर (devctl & MUSB_DEVCTL_HM) अणु
		चयन (musb->xceiv->otg->state) अणु
		हाल OTG_STATE_A_SUSPEND:
			/* remote wakeup? */
			musb->port1_status |=
					(USB_PORT_STAT_C_SUSPEND << 16)
					| MUSB_PORT_STAT_RESUME;
			musb->rh_समयr = jअगरfies
				+ msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
			musb->xceiv->otg->state = OTG_STATE_A_HOST;
			musb->is_active = 1;
			musb_host_resume_root_hub(musb);
			schedule_delayed_work(&musb->finish_resume_work,
				msecs_to_jअगरfies(USB_RESUME_TIMEOUT));
			अवरोध;
		हाल OTG_STATE_B_WAIT_ACON:
			musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
			musb->is_active = 1;
			MUSB_DEV_MODE(musb);
			अवरोध;
		शेष:
			WARNING("bogus %s RESUME (%s)\n",
				"host",
				usb_otg_state_string(musb->xceiv->otg->state));
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (musb->xceiv->otg->state) अणु
		हाल OTG_STATE_A_SUSPEND:
			/* possibly DISCONNECT is upcoming */
			musb->xceiv->otg->state = OTG_STATE_A_HOST;
			musb_host_resume_root_hub(musb);
			अवरोध;
		हाल OTG_STATE_B_WAIT_ACON:
		हाल OTG_STATE_B_PERIPHERAL:
			/* disconnect जबतक suspended?  we may
			 * not get a disconnect irq...
			 */
			अगर ((devctl & MUSB_DEVCTL_VBUS)
					!= (3 << MUSB_DEVCTL_VBUS_SHIFT)
					) अणु
				musb->पूर्णांक_usb |= MUSB_INTR_DISCONNECT;
				musb->पूर्णांक_usb &= ~MUSB_INTR_SUSPEND;
				अवरोध;
			पूर्ण
			musb_g_resume(musb);
			अवरोध;
		हाल OTG_STATE_B_IDLE:
			musb->पूर्णांक_usb &= ~MUSB_INTR_SUSPEND;
			अवरोध;
		शेष:
			WARNING("bogus %s RESUME (%s)\n",
				"peripheral",
				usb_otg_state_string(musb->xceiv->otg->state));
		पूर्ण
	पूर्ण
पूर्ण

/* वापस IRQ_HANDLED to tell the caller to वापस immediately */
अटल irqवापस_t musb_handle_पूर्णांकr_sessreq(काष्ठा musb *musb, u8 devctl)
अणु
	व्योम __iomem *mbase = musb->mregs;

	अगर ((devctl & MUSB_DEVCTL_VBUS) == MUSB_DEVCTL_VBUS
			&& (devctl & MUSB_DEVCTL_BDEVICE)) अणु
		musb_dbg(musb, "SessReq while on B state");
		वापस IRQ_HANDLED;
	पूर्ण

	musb_dbg(musb, "SESSION_REQUEST (%s)",
		usb_otg_state_string(musb->xceiv->otg->state));

	/* IRQ arrives from ID pin sense or (later, अगर VBUS घातer
	 * is हटाओd) SRP.  responses are समय critical:
	 *  - turn on VBUS (with silicon-specअगरic mechanism)
	 *  - go through A_WAIT_VRISE
	 *  - ... to A_WAIT_BCON.
	 * a_रुको_vrise_पंचांगout triggers VBUS_ERROR transitions
	 */
	musb_ग_लिखोb(mbase, MUSB_DEVCTL, MUSB_DEVCTL_SESSION);
	musb->ep0_stage = MUSB_EP0_START;
	musb->xceiv->otg->state = OTG_STATE_A_IDLE;
	MUSB_HST_MODE(musb);
	musb_platक्रमm_set_vbus(musb, 1);

	वापस IRQ_NONE;
पूर्ण

अटल व्योम musb_handle_पूर्णांकr_vbuserr(काष्ठा musb *musb, u8 devctl)
अणु
	पूर्णांक	ignore = 0;

	/* During connection as an A-Device, we may see a लघु
	 * current spikes causing voltage drop, because of cable
	 * and peripheral capacitance combined with vbus draw.
	 * (So: less common with truly self-घातered devices, where
	 * vbus करोesn't act like a घातer supply.)
	 *
	 * Such spikes are लघु; usually less than ~500 usec, max
	 * of ~2 msec.  That is, they're not sustained overcurrent
	 * errors, though they're reported using VBUSERROR irqs.
	 *
	 * Workarounds:  (a) hardware: use self घातered devices.
	 * (b) software:  ignore non-repeated VBUS errors.
	 *
	 * REVISIT:  करो delays from lots of DEBUG_KERNEL checks
	 * make trouble here, keeping VBUS < 4.4V ?
	 */
	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_HOST:
		/* recovery is dicey once we've gotten past the
		 * initial stages of क्रमागतeration, but अगर VBUS
		 * stayed ok at the other end of the link, and
		 * another reset is due (at least क्रम high speed,
		 * to reकरो the chirp etc), it might work OK...
		 */
	हाल OTG_STATE_A_WAIT_BCON:
	हाल OTG_STATE_A_WAIT_VRISE:
		अगर (musb->vbuserr_retry) अणु
			व्योम __iomem *mbase = musb->mregs;

			musb->vbuserr_retry--;
			ignore = 1;
			devctl |= MUSB_DEVCTL_SESSION;
			musb_ग_लिखोb(mbase, MUSB_DEVCTL, devctl);
		पूर्ण अन्यथा अणु
			musb->port1_status |=
				  USB_PORT_STAT_OVERCURRENT
				| (USB_PORT_STAT_C_OVERCURRENT << 16);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_prपूर्णांकk(ignore ? KERN_DEBUG : KERN_ERR, musb->controller,
			"VBUS_ERROR in %s (%02x, %s), retry #%d, port1 %08x\n",
			usb_otg_state_string(musb->xceiv->otg->state),
			devctl,
			(अणु अक्षर *s;
			चयन (devctl & MUSB_DEVCTL_VBUS) अणु
			हाल 0 << MUSB_DEVCTL_VBUS_SHIFT:
				s = "<SessEnd"; अवरोध;
			हाल 1 << MUSB_DEVCTL_VBUS_SHIFT:
				s = "<AValid"; अवरोध;
			हाल 2 << MUSB_DEVCTL_VBUS_SHIFT:
				s = "<VBusValid"; अवरोध;
			/* हाल 3 << MUSB_DEVCTL_VBUS_SHIFT: */
			शेष:
				s = "VALID"; अवरोध;
			पूर्ण s; पूर्ण),
			VBUSERR_RETRY_COUNT - musb->vbuserr_retry,
			musb->port1_status);

	/* go through A_WAIT_VFALL then start a new session */
	अगर (!ignore)
		musb_platक्रमm_set_vbus(musb, 0);
पूर्ण

अटल व्योम musb_handle_पूर्णांकr_suspend(काष्ठा musb *musb, u8 devctl)
अणु
	musb_dbg(musb, "SUSPEND (%s) devctl %02x",
		usb_otg_state_string(musb->xceiv->otg->state), devctl);

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_PERIPHERAL:
		/* We also come here अगर the cable is हटाओd, since
		 * this silicon करोesn't report ID-no-दीर्घer-grounded.
		 *
		 * We depend on T(a_रुको_bcon) to shut us करोwn, and
		 * hope users करोn't करो anything dicey during this
		 * undesired detour through A_WAIT_BCON.
		 */
		musb_hnp_stop(musb);
		musb_host_resume_root_hub(musb);
		musb_root_disconnect(musb);
		musb_platक्रमm_try_idle(musb, jअगरfies
				+ msecs_to_jअगरfies(musb->a_रुको_bcon
					? : OTG_TIME_A_WAIT_BCON));

		अवरोध;
	हाल OTG_STATE_B_IDLE:
		अगर (!musb->is_active)
			अवरोध;
		fallthrough;
	हाल OTG_STATE_B_PERIPHERAL:
		musb_g_suspend(musb);
		musb->is_active = musb->g.b_hnp_enable;
		अगर (musb->is_active) अणु
			musb->xceiv->otg->state = OTG_STATE_B_WAIT_ACON;
			musb_dbg(musb, "HNP: Setting timer for b_ase0_brst");
			mod_समयr(&musb->otg_समयr, jअगरfies
				+ msecs_to_jअगरfies(
						OTG_TIME_B_ASE0_BRST));
		पूर्ण
		अवरोध;
	हाल OTG_STATE_A_WAIT_BCON:
		अगर (musb->a_रुको_bcon != 0)
			musb_platक्रमm_try_idle(musb, jअगरfies
				+ msecs_to_jअगरfies(musb->a_रुको_bcon));
		अवरोध;
	हाल OTG_STATE_A_HOST:
		musb->xceiv->otg->state = OTG_STATE_A_SUSPEND;
		musb->is_active = musb->hcd->self.b_hnp_enable;
		अवरोध;
	हाल OTG_STATE_B_HOST:
		/* Transition to B_PERIPHERAL, see 6.8.2.6 p 44 */
		musb_dbg(musb, "REVISIT: SUSPEND as B_HOST");
		अवरोध;
	शेष:
		/* "should not happen" */
		musb->is_active = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम musb_handle_पूर्णांकr_connect(काष्ठा musb *musb, u8 devctl, u8 पूर्णांक_usb)
अणु
	काष्ठा usb_hcd *hcd = musb->hcd;

	musb->is_active = 1;
	musb->ep0_stage = MUSB_EP0_START;

	musb->पूर्णांकrtxe = musb->epmask;
	musb_ग_लिखोw(musb->mregs, MUSB_INTRTXE, musb->पूर्णांकrtxe);
	musb->पूर्णांकrrxe = musb->epmask & 0xfffe;
	musb_ग_लिखोw(musb->mregs, MUSB_INTRRXE, musb->पूर्णांकrrxe);
	musb_ग_लिखोb(musb->mregs, MUSB_INTRUSBE, 0xf7);
	musb->port1_status &= ~(USB_PORT_STAT_LOW_SPEED
				|USB_PORT_STAT_HIGH_SPEED
				|USB_PORT_STAT_ENABLE
				);
	musb->port1_status |= USB_PORT_STAT_CONNECTION
				|(USB_PORT_STAT_C_CONNECTION << 16);

	/* high vs full speed is just a guess until after reset */
	अगर (devctl & MUSB_DEVCTL_LSDEV)
		musb->port1_status |= USB_PORT_STAT_LOW_SPEED;

	/* indicate new connection to OTG machine */
	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_B_PERIPHERAL:
		अगर (पूर्णांक_usb & MUSB_INTR_SUSPEND) अणु
			musb_dbg(musb, "HNP: SUSPEND+CONNECT, now b_host");
			पूर्णांक_usb &= ~MUSB_INTR_SUSPEND;
			जाओ b_host;
		पूर्ण अन्यथा
			musb_dbg(musb, "CONNECT as b_peripheral???");
		अवरोध;
	हाल OTG_STATE_B_WAIT_ACON:
		musb_dbg(musb, "HNP: CONNECT, now b_host");
b_host:
		musb->xceiv->otg->state = OTG_STATE_B_HOST;
		अगर (musb->hcd)
			musb->hcd->self.is_b_host = 1;
		del_समयr(&musb->otg_समयr);
		अवरोध;
	शेष:
		अगर ((devctl & MUSB_DEVCTL_VBUS)
				== (3 << MUSB_DEVCTL_VBUS_SHIFT)) अणु
			musb->xceiv->otg->state = OTG_STATE_A_HOST;
			अगर (hcd)
				hcd->self.is_b_host = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	musb_host_poke_root_hub(musb);

	musb_dbg(musb, "CONNECT (%s) devctl %02x",
			usb_otg_state_string(musb->xceiv->otg->state), devctl);
पूर्ण

अटल व्योम musb_handle_पूर्णांकr_disconnect(काष्ठा musb *musb, u8 devctl)
अणु
	musb_dbg(musb, "DISCONNECT (%s) as %s, devctl %02x",
			usb_otg_state_string(musb->xceiv->otg->state),
			MUSB_MODE(musb), devctl);

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_HOST:
	हाल OTG_STATE_A_SUSPEND:
		musb_host_resume_root_hub(musb);
		musb_root_disconnect(musb);
		अगर (musb->a_रुको_bcon != 0)
			musb_platक्रमm_try_idle(musb, jअगरfies
				+ msecs_to_jअगरfies(musb->a_रुको_bcon));
		अवरोध;
	हाल OTG_STATE_B_HOST:
		/* REVISIT this behaves क्रम "real disconnect"
		 * हालs; make sure the other transitions from
		 * from B_HOST act right too.  The B_HOST code
		 * in hnp_stop() is currently not used...
		 */
		musb_root_disconnect(musb);
		अगर (musb->hcd)
			musb->hcd->self.is_b_host = 0;
		musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		MUSB_DEV_MODE(musb);
		musb_g_disconnect(musb);
		अवरोध;
	हाल OTG_STATE_A_PERIPHERAL:
		musb_hnp_stop(musb);
		musb_root_disconnect(musb);
		fallthrough;
	हाल OTG_STATE_B_WAIT_ACON:
	हाल OTG_STATE_B_PERIPHERAL:
	हाल OTG_STATE_B_IDLE:
		musb_g_disconnect(musb);
		अवरोध;
	शेष:
		WARNING("unhandled DISCONNECT transition (%s)\n",
			usb_otg_state_string(musb->xceiv->otg->state));
		अवरोध;
	पूर्ण
पूर्ण

/*
 * mentor saves a bit: bus reset and babble share the same irq.
 * only host sees babble; only peripheral sees bus reset.
 */
अटल व्योम musb_handle_पूर्णांकr_reset(काष्ठा musb *musb)
अणु
	अगर (is_host_active(musb)) अणु
		/*
		 * When BABBLE happens what we can depends on which
		 * platक्रमm MUSB is running, because some platक्रमms
		 * implemented proprietary means क्रम 'recovering' from
		 * Babble conditions. One such platक्रमm is AM335x. In
		 * most हालs, however, the only thing we can करो is
		 * drop the session.
		 */
		dev_err(musb->controller, "Babble\n");
		musb_recover_from_babble(musb);
	पूर्ण अन्यथा अणु
		musb_dbg(musb, "BUS RESET as %s",
			usb_otg_state_string(musb->xceiv->otg->state));
		चयन (musb->xceiv->otg->state) अणु
		हाल OTG_STATE_A_SUSPEND:
			musb_g_reset(musb);
			fallthrough;
		हाल OTG_STATE_A_WAIT_BCON:	/* OPT TD.4.7-900ms */
			/* never use invalid T(a_रुको_bcon) */
			musb_dbg(musb, "HNP: in %s, %d msec timeout",
				usb_otg_state_string(musb->xceiv->otg->state),
				TA_WAIT_BCON(musb));
			mod_समयr(&musb->otg_समयr, jअगरfies
				+ msecs_to_jअगरfies(TA_WAIT_BCON(musb)));
			अवरोध;
		हाल OTG_STATE_A_PERIPHERAL:
			del_समयr(&musb->otg_समयr);
			musb_g_reset(musb);
			अवरोध;
		हाल OTG_STATE_B_WAIT_ACON:
			musb_dbg(musb, "HNP: RESET (%s), to b_peripheral",
				usb_otg_state_string(musb->xceiv->otg->state));
			musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
			musb_g_reset(musb);
			अवरोध;
		हाल OTG_STATE_B_IDLE:
			musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
			fallthrough;
		हाल OTG_STATE_B_PERIPHERAL:
			musb_g_reset(musb);
			अवरोध;
		शेष:
			musb_dbg(musb, "Unhandled BUS RESET as %s",
				usb_otg_state_string(musb->xceiv->otg->state));
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Interrupt Service Routine to record USB "global" पूर्णांकerrupts.
 * Since these करो not happen often and signअगरy things of
 * paramount importance, it seems OK to check them inभागidually;
 * the order of the tests is specअगरied in the manual
 *
 * @param musb instance poपूर्णांकer
 * @param पूर्णांक_usb रेजिस्टर contents
 * @param devctl
 */

अटल irqवापस_t musb_stage0_irq(काष्ठा musb *musb, u8 पूर्णांक_usb,
				u8 devctl)
अणु
	irqवापस_t handled = IRQ_NONE;

	musb_dbg(musb, "<== DevCtl=%02x, int_usb=0x%x", devctl, पूर्णांक_usb);

	/* in host mode, the peripheral may issue remote wakeup.
	 * in peripheral mode, the host may resume the link.
	 * spurious RESUME irqs happen too, paired with SUSPEND.
	 */
	अगर (पूर्णांक_usb & MUSB_INTR_RESUME) अणु
		musb_handle_पूर्णांकr_resume(musb, devctl);
		handled = IRQ_HANDLED;
	पूर्ण

	/* see manual क्रम the order of the tests */
	अगर (पूर्णांक_usb & MUSB_INTR_SESSREQ) अणु
		अगर (musb_handle_पूर्णांकr_sessreq(musb, devctl))
			वापस IRQ_HANDLED;
		handled = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांक_usb & MUSB_INTR_VBUSERROR) अणु
		musb_handle_पूर्णांकr_vbuserr(musb, devctl);
		handled = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांक_usb & MUSB_INTR_SUSPEND) अणु
		musb_handle_पूर्णांकr_suspend(musb, devctl);
		handled = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांक_usb & MUSB_INTR_CONNECT) अणु
		musb_handle_पूर्णांकr_connect(musb, devctl, पूर्णांक_usb);
		handled = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांक_usb & MUSB_INTR_DISCONNECT) अणु
		musb_handle_पूर्णांकr_disconnect(musb, devctl);
		handled = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांक_usb & MUSB_INTR_RESET) अणु
		musb_handle_पूर्णांकr_reset(musb);
		handled = IRQ_HANDLED;
	पूर्ण

#अगर 0
/* REVISIT ... this would be क्रम multiplexing periodic endpoपूर्णांकs, or
 * supporting transfer phasing to prevent exceeding ISO bandwidth
 * limits of a given frame or microframe.
 *
 * It's not needed क्रम peripheral side, which dedicates endpoपूर्णांकs;
 * though it _might_ use SOF irqs क्रम other purposes.
 *
 * And it's not currently needed क्रम host side, which also dedicates
 * endpoपूर्णांकs, relies on TX/RX पूर्णांकerval रेजिस्टरs, and isn't claimed
 * to support ISO transfers yet.
 */
	अगर (पूर्णांक_usb & MUSB_INTR_SOF) अणु
		व्योम __iomem *mbase = musb->mregs;
		काष्ठा musb_hw_ep	*ep;
		u8 epnum;
		u16 frame;

		dev_dbg(musb->controller, "START_OF_FRAME\n");
		handled = IRQ_HANDLED;

		/* start any periodic Tx transfers रुकोing क्रम current frame */
		frame = musb_पढ़ोw(mbase, MUSB_FRAME);
		ep = musb->endpoपूर्णांकs;
		क्रम (epnum = 1; (epnum < musb->nr_endpoपूर्णांकs)
					&& (musb->epmask >= (1 << epnum));
				epnum++, ep++) अणु
			/*
			 * FIXME handle framecounter wraps (12 bits)
			 * eliminate duplicated StartUrb logic
			 */
			अगर (ep->dwWaitFrame >= frame) अणु
				ep->dwWaitFrame = 0;
				pr_debug("SOF --> periodic TX%s on %d\n",
					ep->tx_channel ? " DMA" : "",
					epnum);
				अगर (!ep->tx_channel)
					musb_h_tx_start(musb, epnum);
				अन्यथा
					cppi_hostdma_start(musb, epnum);
			पूर्ण
		पूर्ण		/* end of क्रम loop */
	पूर्ण
#पूर्ण_अगर

	schedule_delayed_work(&musb->irq_work, 0);

	वापस handled;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम musb_disable_पूर्णांकerrupts(काष्ठा musb *musb)
अणु
	व्योम __iomem	*mbase = musb->mregs;

	/* disable पूर्णांकerrupts */
	musb_ग_लिखोb(mbase, MUSB_INTRUSBE, 0);
	musb->पूर्णांकrtxe = 0;
	musb_ग_लिखोw(mbase, MUSB_INTRTXE, 0);
	musb->पूर्णांकrrxe = 0;
	musb_ग_लिखोw(mbase, MUSB_INTRRXE, 0);

	/*  flush pending पूर्णांकerrupts */
	musb_clearb(mbase, MUSB_INTRUSB);
	musb_clearw(mbase, MUSB_INTRTX);
	musb_clearw(mbase, MUSB_INTRRX);
पूर्ण

अटल व्योम musb_enable_पूर्णांकerrupts(काष्ठा musb *musb)
अणु
	व्योम __iomem    *regs = musb->mregs;

	/*  Set INT enable रेजिस्टरs, enable पूर्णांकerrupts */
	musb->पूर्णांकrtxe = musb->epmask;
	musb_ग_लिखोw(regs, MUSB_INTRTXE, musb->पूर्णांकrtxe);
	musb->पूर्णांकrrxe = musb->epmask & 0xfffe;
	musb_ग_लिखोw(regs, MUSB_INTRRXE, musb->पूर्णांकrrxe);
	musb_ग_लिखोb(regs, MUSB_INTRUSBE, 0xf7);

पूर्ण

/*
 * Program the HDRC to start (enable पूर्णांकerrupts, dma, etc.).
 */
व्योम musb_start(काष्ठा musb *musb)
अणु
	व्योम __iomem    *regs = musb->mregs;
	u8              devctl = musb_पढ़ोb(regs, MUSB_DEVCTL);
	u8		घातer;

	musb_dbg(musb, "<== devctl %02x", devctl);

	musb_enable_पूर्णांकerrupts(musb);
	musb_ग_लिखोb(regs, MUSB_TESTMODE, 0);

	घातer = MUSB_POWER_ISOUPDATE;
	/*
	 * treating UNKNOWN as unspecअगरied maximum speed, in which हाल
	 * we will शेष to high-speed.
	 */
	अगर (musb->config->maximum_speed == USB_SPEED_HIGH ||
			musb->config->maximum_speed == USB_SPEED_UNKNOWN)
		घातer |= MUSB_POWER_HSENAB;
	musb_ग_लिखोb(regs, MUSB_POWER, घातer);

	musb->is_active = 0;
	devctl = musb_पढ़ोb(regs, MUSB_DEVCTL);
	devctl &= ~MUSB_DEVCTL_SESSION;

	/* session started after:
	 * (a) ID-grounded irq, host mode;
	 * (b) vbus present/connect IRQ, peripheral mode;
	 * (c) peripheral initiates, using SRP
	 */
	अगर (musb->port_mode != MUSB_HOST &&
			musb->xceiv->otg->state != OTG_STATE_A_WAIT_BCON &&
			(devctl & MUSB_DEVCTL_VBUS) == MUSB_DEVCTL_VBUS) अणु
		musb->is_active = 1;
	पूर्ण अन्यथा अणु
		devctl |= MUSB_DEVCTL_SESSION;
	पूर्ण

	musb_platक्रमm_enable(musb);
	musb_ग_लिखोb(regs, MUSB_DEVCTL, devctl);
पूर्ण

/*
 * Make the HDRC stop (disable पूर्णांकerrupts, etc.);
 * reversible by musb_start
 * called on gadget driver unरेजिस्टर
 * with controller locked, irqs blocked
 * acts as a NOP unless some role activated the hardware
 */
व्योम musb_stop(काष्ठा musb *musb)
अणु
	/* stop IRQs, समयrs, ... */
	musb_platक्रमm_disable(musb);
	musb_disable_पूर्णांकerrupts(musb);
	musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, 0);

	/* FIXME
	 *  - mark host and/or peripheral drivers unusable/inactive
	 *  - disable DMA (and enable it in HdrcStart)
	 *  - make sure we can musb_start() after musb_stop(); with
	 *    OTG mode, gadget driver module rmmod/modprobe cycles that
	 *  - ...
	 */
	musb_platक्रमm_try_idle(musb, 0);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * The silicon either has hard-wired endpoपूर्णांक configurations, or अन्यथा
 * "dynamic fifo" sizing.  The driver has support क्रम both, though at this
 * writing only the dynamic sizing is very well tested.   Since we चयनed
 * away from compile-समय hardware parameters, we can no दीर्घer rely on
 * dead code elimination to leave only the relevant one in the object file.
 *
 * We करोn't currently use dynamic fअगरo setup capability to करो anything
 * more than selecting one of a bunch of predefined configurations.
 */
अटल uलघु fअगरo_mode;

/* "modprobe ... fifo_mode=1" etc */
module_param(fअगरo_mode, uलघु, 0);
MODULE_PARM_DESC(fअगरo_mode, "initial endpoint configuration");

/*
 * tables defining fअगरo_mode values.  define more अगर you like.
 * क्रम host side, make sure both halves of ep1 are set up.
 */

/* mode 0 - fits in 2KB */
अटल काष्ठा musb_fअगरo_cfg mode_0_cfg[] = अणु
अणु .hw_ep_num = 1, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 1, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 2, .style = FIFO_RXTX, .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 3, .style = FIFO_RXTX, .maxpacket = 256, पूर्ण,
अणु .hw_ep_num = 4, .style = FIFO_RXTX, .maxpacket = 256, पूर्ण,
पूर्ण;

/* mode 1 - fits in 4KB */
अटल काष्ठा musb_fअगरo_cfg mode_1_cfg[] = अणु
अणु .hw_ep_num = 1, .style = FIFO_TX,   .maxpacket = 512, .mode = BUF_DOUBLE, पूर्ण,
अणु .hw_ep_num = 1, .style = FIFO_RX,   .maxpacket = 512, .mode = BUF_DOUBLE, पूर्ण,
अणु .hw_ep_num = 2, .style = FIFO_RXTX, .maxpacket = 512, .mode = BUF_DOUBLE, पूर्ण,
अणु .hw_ep_num = 3, .style = FIFO_RXTX, .maxpacket = 256, पूर्ण,
अणु .hw_ep_num = 4, .style = FIFO_RXTX, .maxpacket = 256, पूर्ण,
पूर्ण;

/* mode 2 - fits in 4KB */
अटल काष्ठा musb_fअगरo_cfg mode_2_cfg[] = अणु
अणु .hw_ep_num = 1, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 1, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 2, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 2, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 3, .style = FIFO_RXTX, .maxpacket = 960, पूर्ण,
अणु .hw_ep_num = 4, .style = FIFO_RXTX, .maxpacket = 1024, पूर्ण,
पूर्ण;

/* mode 3 - fits in 4KB */
अटल काष्ठा musb_fअगरo_cfg mode_3_cfg[] = अणु
अणु .hw_ep_num = 1, .style = FIFO_TX,   .maxpacket = 512, .mode = BUF_DOUBLE, पूर्ण,
अणु .hw_ep_num = 1, .style = FIFO_RX,   .maxpacket = 512, .mode = BUF_DOUBLE, पूर्ण,
अणु .hw_ep_num = 2, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 2, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 3, .style = FIFO_RXTX, .maxpacket = 256, पूर्ण,
अणु .hw_ep_num = 4, .style = FIFO_RXTX, .maxpacket = 256, पूर्ण,
पूर्ण;

/* mode 4 - fits in 16KB */
अटल काष्ठा musb_fअगरo_cfg mode_4_cfg[] = अणु
अणु .hw_ep_num =  1, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  1, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  2, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  2, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  3, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  3, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  4, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  4, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  5, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  5, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  6, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  6, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  7, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  7, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  8, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  8, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  9, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  9, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 10, .style = FIFO_TX,   .maxpacket = 256, पूर्ण,
अणु .hw_ep_num = 10, .style = FIFO_RX,   .maxpacket = 64, पूर्ण,
अणु .hw_ep_num = 11, .style = FIFO_TX,   .maxpacket = 256, पूर्ण,
अणु .hw_ep_num = 11, .style = FIFO_RX,   .maxpacket = 64, पूर्ण,
अणु .hw_ep_num = 12, .style = FIFO_TX,   .maxpacket = 256, पूर्ण,
अणु .hw_ep_num = 12, .style = FIFO_RX,   .maxpacket = 64, पूर्ण,
अणु .hw_ep_num = 13, .style = FIFO_RXTX, .maxpacket = 4096, पूर्ण,
अणु .hw_ep_num = 14, .style = FIFO_RXTX, .maxpacket = 1024, पूर्ण,
अणु .hw_ep_num = 15, .style = FIFO_RXTX, .maxpacket = 1024, पूर्ण,
पूर्ण;

/* mode 5 - fits in 8KB */
अटल काष्ठा musb_fअगरo_cfg mode_5_cfg[] = अणु
अणु .hw_ep_num =  1, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  1, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  2, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  2, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  3, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  3, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  4, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  4, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  5, .style = FIFO_TX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  5, .style = FIFO_RX,   .maxpacket = 512, पूर्ण,
अणु .hw_ep_num =  6, .style = FIFO_TX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num =  6, .style = FIFO_RX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num =  7, .style = FIFO_TX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num =  7, .style = FIFO_RX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num =  8, .style = FIFO_TX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num =  8, .style = FIFO_RX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num =  9, .style = FIFO_TX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num =  9, .style = FIFO_RX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num = 10, .style = FIFO_TX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num = 10, .style = FIFO_RX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num = 11, .style = FIFO_TX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num = 11, .style = FIFO_RX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num = 12, .style = FIFO_TX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num = 12, .style = FIFO_RX,   .maxpacket = 32, पूर्ण,
अणु .hw_ep_num = 13, .style = FIFO_RXTX, .maxpacket = 512, पूर्ण,
अणु .hw_ep_num = 14, .style = FIFO_RXTX, .maxpacket = 1024, पूर्ण,
अणु .hw_ep_num = 15, .style = FIFO_RXTX, .maxpacket = 1024, पूर्ण,
पूर्ण;

/*
 * configure a fअगरo; क्रम non-shared endpoपूर्णांकs, this may be called
 * once क्रम a tx fअगरo and once क्रम an rx fअगरo.
 *
 * वापसs negative त्रुटि_सं or offset क्रम next fअगरo.
 */
अटल पूर्णांक
fअगरo_setup(काष्ठा musb *musb, काष्ठा musb_hw_ep  *hw_ep,
		स्थिर काष्ठा musb_fअगरo_cfg *cfg, u16 offset)
अणु
	व्योम __iomem	*mbase = musb->mregs;
	पूर्णांक	size = 0;
	u16	maxpacket = cfg->maxpacket;
	u16	c_off = offset >> 3;
	u8	c_size;

	/* expect hw_ep has alपढ़ोy been zero-initialized */

	size = ffs(max(maxpacket, (u16) 8)) - 1;
	maxpacket = 1 << size;

	c_size = size - 3;
	अगर (cfg->mode == BUF_DOUBLE) अणु
		अगर ((offset + (maxpacket << 1)) >
				(1 << (musb->config->ram_bits + 2)))
			वापस -EMSGSIZE;
		c_size |= MUSB_FIFOSZ_DPB;
	पूर्ण अन्यथा अणु
		अगर ((offset + maxpacket) > (1 << (musb->config->ram_bits + 2)))
			वापस -EMSGSIZE;
	पूर्ण

	/* configure the FIFO */
	musb_ग_लिखोb(mbase, MUSB_INDEX, hw_ep->epnum);

	/* EP0 reserved endpoपूर्णांक क्रम control, bidirectional;
	 * EP1 reserved क्रम bulk, two unidirectional halves.
	 */
	अगर (hw_ep->epnum == 1)
		musb->bulk_ep = hw_ep;
	/* REVISIT error check:  be sure ep0 can both rx and tx ... */
	चयन (cfg->style) अणु
	हाल FIFO_TX:
		musb_ग_लिखोb(mbase, MUSB_TXFIFOSZ, c_size);
		musb_ग_लिखोw(mbase, MUSB_TXFIFOADD, c_off);
		hw_ep->tx_द्विगुन_buffered = !!(c_size & MUSB_FIFOSZ_DPB);
		hw_ep->max_packet_sz_tx = maxpacket;
		अवरोध;
	हाल FIFO_RX:
		musb_ग_लिखोb(mbase, MUSB_RXFIFOSZ, c_size);
		musb_ग_लिखोw(mbase, MUSB_RXFIFOADD, c_off);
		hw_ep->rx_द्विगुन_buffered = !!(c_size & MUSB_FIFOSZ_DPB);
		hw_ep->max_packet_sz_rx = maxpacket;
		अवरोध;
	हाल FIFO_RXTX:
		musb_ग_लिखोb(mbase, MUSB_TXFIFOSZ, c_size);
		musb_ग_लिखोw(mbase, MUSB_TXFIFOADD, c_off);
		hw_ep->rx_द्विगुन_buffered = !!(c_size & MUSB_FIFOSZ_DPB);
		hw_ep->max_packet_sz_rx = maxpacket;

		musb_ग_लिखोb(mbase, MUSB_RXFIFOSZ, c_size);
		musb_ग_लिखोw(mbase, MUSB_RXFIFOADD, c_off);
		hw_ep->tx_द्विगुन_buffered = hw_ep->rx_द्विगुन_buffered;
		hw_ep->max_packet_sz_tx = maxpacket;

		hw_ep->is_shared_fअगरo = true;
		अवरोध;
	पूर्ण

	/* NOTE rx and tx endpoपूर्णांक irqs aren't managed separately,
	 * which happens to be ok
	 */
	musb->epmask |= (1 << hw_ep->epnum);

	वापस offset + (maxpacket << ((c_size & MUSB_FIFOSZ_DPB) ? 1 : 0));
पूर्ण

अटल काष्ठा musb_fअगरo_cfg ep0_cfg = अणु
	.style = FIFO_RXTX, .maxpacket = 64,
पूर्ण;

अटल पूर्णांक ep_config_from_table(काष्ठा musb *musb)
अणु
	स्थिर काष्ठा musb_fअगरo_cfg	*cfg;
	अचिन्हित		i, n;
	पूर्णांक			offset;
	काष्ठा musb_hw_ep	*hw_ep = musb->endpoपूर्णांकs;

	अगर (musb->config->fअगरo_cfg) अणु
		cfg = musb->config->fअगरo_cfg;
		n = musb->config->fअगरo_cfg_size;
		जाओ करोne;
	पूर्ण

	चयन (fअगरo_mode) अणु
	शेष:
		fअगरo_mode = 0;
		fallthrough;
	हाल 0:
		cfg = mode_0_cfg;
		n = ARRAY_SIZE(mode_0_cfg);
		अवरोध;
	हाल 1:
		cfg = mode_1_cfg;
		n = ARRAY_SIZE(mode_1_cfg);
		अवरोध;
	हाल 2:
		cfg = mode_2_cfg;
		n = ARRAY_SIZE(mode_2_cfg);
		अवरोध;
	हाल 3:
		cfg = mode_3_cfg;
		n = ARRAY_SIZE(mode_3_cfg);
		अवरोध;
	हाल 4:
		cfg = mode_4_cfg;
		n = ARRAY_SIZE(mode_4_cfg);
		अवरोध;
	हाल 5:
		cfg = mode_5_cfg;
		n = ARRAY_SIZE(mode_5_cfg);
		अवरोध;
	पूर्ण

	pr_debug("%s: setup fifo_mode %d\n", musb_driver_name, fअगरo_mode);


करोne:
	offset = fअगरo_setup(musb, hw_ep, &ep0_cfg, 0);
	/* निश्चित(offset > 0) */

	/* NOTE:  क्रम RTL versions >= 1.400 EPINFO and RAMINFO would
	 * be better than अटल musb->config->num_eps and DYN_FIFO_SIZE...
	 */

	क्रम (i = 0; i < n; i++) अणु
		u8	epn = cfg->hw_ep_num;

		अगर (epn >= musb->config->num_eps) अणु
			pr_debug("%s: invalid ep %d\n",
					musb_driver_name, epn);
			वापस -EINVAL;
		पूर्ण
		offset = fअगरo_setup(musb, hw_ep + epn, cfg++, offset);
		अगर (offset < 0) अणु
			pr_debug("%s: mem overrun, ep %d\n",
					musb_driver_name, epn);
			वापस offset;
		पूर्ण
		epn++;
		musb->nr_endpoपूर्णांकs = max(epn, musb->nr_endpoपूर्णांकs);
	पूर्ण

	pr_debug("%s: %d/%d max ep, %d/%d memory\n",
			musb_driver_name,
			n + 1, musb->config->num_eps * 2 - 1,
			offset, (1 << (musb->config->ram_bits + 2)));

	अगर (!musb->bulk_ep) अणु
		pr_debug("%s: missing bulk\n", musb_driver_name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * ep_config_from_hw - when MUSB_C_DYNFIFO_DEF is false
 * @param musb the controller
 */
अटल पूर्णांक ep_config_from_hw(काष्ठा musb *musb)
अणु
	u8 epnum = 0;
	काष्ठा musb_hw_ep *hw_ep;
	व्योम __iomem *mbase = musb->mregs;
	पूर्णांक ret = 0;

	musb_dbg(musb, "<== static silicon ep config");

	/* FIXME pick up ep0 maxpacket size */

	क्रम (epnum = 1; epnum < musb->config->num_eps; epnum++) अणु
		musb_ep_select(mbase, epnum);
		hw_ep = musb->endpoपूर्णांकs + epnum;

		ret = musb_पढ़ो_fअगरosize(musb, hw_ep, epnum);
		अगर (ret < 0)
			अवरोध;

		/* FIXME set up hw_ep->अणुrx,txपूर्ण_द्विगुन_buffered */

		/* pick an RX/TX endpoपूर्णांक क्रम bulk */
		अगर (hw_ep->max_packet_sz_tx < 512
				|| hw_ep->max_packet_sz_rx < 512)
			जारी;

		/* REVISIT:  this algorithm is lazy, we should at least
		 * try to pick a द्विगुन buffered endpoपूर्णांक.
		 */
		अगर (musb->bulk_ep)
			जारी;
		musb->bulk_ep = hw_ep;
	पूर्ण

	अगर (!musb->bulk_ep) अणु
		pr_debug("%s: missing bulk\n", musb_driver_name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत अणु MUSB_CONTROLLER_MHDRC, MUSB_CONTROLLER_HDRC, पूर्ण;

/* Initialize MUSB (M)HDRC part of the USB hardware subप्रणाली;
 * configure endpoपूर्णांकs, or take their config from silicon
 */
अटल पूर्णांक musb_core_init(u16 musb_type, काष्ठा musb *musb)
अणु
	u8 reg;
	अक्षर *type;
	अक्षर aInfo[90];
	व्योम __iomem	*mbase = musb->mregs;
	पूर्णांक		status = 0;
	पूर्णांक		i;

	/* log core options (पढ़ो using indexed model) */
	reg = musb_पढ़ो_configdata(mbase);

	म_नकल(aInfo, (reg & MUSB_CONFIGDATA_UTMIDW) ? "UTMI-16" : "UTMI-8");
	अगर (reg & MUSB_CONFIGDATA_DYNFIFO) अणु
		म_जोड़ो(aInfo, ", dyn FIFOs");
		musb->dyn_fअगरo = true;
	पूर्ण
	अगर (reg & MUSB_CONFIGDATA_MPRXE) अणु
		म_जोड़ो(aInfo, ", bulk combine");
		musb->bulk_combine = true;
	पूर्ण
	अगर (reg & MUSB_CONFIGDATA_MPTXE) अणु
		म_जोड़ो(aInfo, ", bulk split");
		musb->bulk_split = true;
	पूर्ण
	अगर (reg & MUSB_CONFIGDATA_HBRXE) अणु
		म_जोड़ो(aInfo, ", HB-ISO Rx");
		musb->hb_iso_rx = true;
	पूर्ण
	अगर (reg & MUSB_CONFIGDATA_HBTXE) अणु
		म_जोड़ो(aInfo, ", HB-ISO Tx");
		musb->hb_iso_tx = true;
	पूर्ण
	अगर (reg & MUSB_CONFIGDATA_SOFTCONE)
		म_जोड़ो(aInfo, ", SoftConn");

	pr_debug("%s: ConfigData=0x%02x (%s)\n", musb_driver_name, reg, aInfo);

	अगर (MUSB_CONTROLLER_MHDRC == musb_type) अणु
		musb->is_multipoपूर्णांक = 1;
		type = "M";
	पूर्ण अन्यथा अणु
		musb->is_multipoपूर्णांक = 0;
		type = "";
		अगर (IS_ENABLED(CONFIG_USB) &&
		    !IS_ENABLED(CONFIG_USB_OTG_DISABLE_EXTERNAL_HUB)) अणु
			pr_err("%s: kernel must disable external hubs, please fix the configuration\n",
			       musb_driver_name);
		पूर्ण
	पूर्ण

	/* log release info */
	musb->hwvers = musb_पढ़ोw(mbase, MUSB_HWVERS);
	pr_debug("%s: %sHDRC RTL version %d.%d%s\n",
		 musb_driver_name, type, MUSB_HWVERS_MAJOR(musb->hwvers),
		 MUSB_HWVERS_MINOR(musb->hwvers),
		 (musb->hwvers & MUSB_HWVERS_RC) ? "RC" : "");

	/* configure ep0 */
	musb_configure_ep0(musb);

	/* discover endpoपूर्णांक configuration */
	musb->nr_endpoपूर्णांकs = 1;
	musb->epmask = 1;

	अगर (musb->dyn_fअगरo)
		status = ep_config_from_table(musb);
	अन्यथा
		status = ep_config_from_hw(musb);

	अगर (status < 0)
		वापस status;

	/* finish init, and prपूर्णांक endpoपूर्णांक config */
	क्रम (i = 0; i < musb->nr_endpoपूर्णांकs; i++) अणु
		काष्ठा musb_hw_ep	*hw_ep = musb->endpoपूर्णांकs + i;

		hw_ep->fअगरo = musb->io.fअगरo_offset(i) + mbase;
#अगर IS_ENABLED(CONFIG_USB_MUSB_TUSB6010)
		अगर (musb->ops->quirks & MUSB_IN_TUSB) अणु
			hw_ep->fअगरo_async = musb->async + 0x400 +
				musb->io.fअगरo_offset(i);
			hw_ep->fअगरo_sync = musb->sync + 0x400 +
				musb->io.fअगरo_offset(i);
			hw_ep->fअगरo_sync_va =
				musb->sync_va + 0x400 + musb->io.fअगरo_offset(i);

			अगर (i == 0)
				hw_ep->conf = mbase - 0x400 + TUSB_EP0_CONF;
			अन्यथा
				hw_ep->conf = mbase + 0x400 +
					(((i - 1) & 0xf) << 2);
		पूर्ण
#पूर्ण_अगर

		hw_ep->regs = musb->io.ep_offset(i, 0) + mbase;
		hw_ep->rx_reinit = 1;
		hw_ep->tx_reinit = 1;

		अगर (hw_ep->max_packet_sz_tx) अणु
			musb_dbg(musb, "%s: hw_ep %d%s, %smax %d",
				musb_driver_name, i,
				hw_ep->is_shared_fअगरo ? "shared" : "tx",
				hw_ep->tx_द्विगुन_buffered
					? "doublebuffer, " : "",
				hw_ep->max_packet_sz_tx);
		पूर्ण
		अगर (hw_ep->max_packet_sz_rx && !hw_ep->is_shared_fअगरo) अणु
			musb_dbg(musb, "%s: hw_ep %d%s, %smax %d",
				musb_driver_name, i,
				"rx",
				hw_ep->rx_द्विगुन_buffered
					? "doublebuffer, " : "",
				hw_ep->max_packet_sz_rx);
		पूर्ण
		अगर (!(hw_ep->max_packet_sz_tx || hw_ep->max_packet_sz_rx))
			musb_dbg(musb, "hw_ep %d not configured", i);
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * handle all the irqs defined by the HDRC core. क्रम now we expect:  other
 * irq sources (phy, dma, etc) will be handled first, musb->पूर्णांक_* values
 * will be asचिन्हित, and the irq will alपढ़ोy have been acked.
 *
 * called in irq context with spinlock held, irqs blocked
 */
irqवापस_t musb_पूर्णांकerrupt(काष्ठा musb *musb)
अणु
	irqवापस_t	retval = IRQ_NONE;
	अचिन्हित दीर्घ	status;
	अचिन्हित दीर्घ	epnum;
	u8		devctl;

	अगर (!musb->पूर्णांक_usb && !musb->पूर्णांक_tx && !musb->पूर्णांक_rx)
		वापस IRQ_NONE;

	devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);

	trace_musb_isr(musb);

	/**
	 * According to Mentor Graphics' करोcumentation, flowअक्षरt on page 98,
	 * IRQ should be handled as follows:
	 *
	 * . Resume IRQ
	 * . Session Request IRQ
	 * . VBUS Error IRQ
	 * . Suspend IRQ
	 * . Connect IRQ
	 * . Disconnect IRQ
	 * . Reset/Babble IRQ
	 * . SOF IRQ (we're not using this one)
	 * . Endpoपूर्णांक 0 IRQ
	 * . TX Endpoपूर्णांकs
	 * . RX Endpoपूर्णांकs
	 *
	 * We will be following that flowअक्षरt in order to aव्योम any problems
	 * that might arise with पूर्णांकernal Finite State Machine.
	 */

	अगर (musb->पूर्णांक_usb)
		retval |= musb_stage0_irq(musb, musb->पूर्णांक_usb, devctl);

	अगर (musb->पूर्णांक_tx & 1) अणु
		अगर (is_host_active(musb))
			retval |= musb_h_ep0_irq(musb);
		अन्यथा
			retval |= musb_g_ep0_irq(musb);

		/* we have just handled endpoपूर्णांक 0 IRQ, clear it */
		musb->पूर्णांक_tx &= ~BIT(0);
	पूर्ण

	status = musb->पूर्णांक_tx;

	क्रम_each_set_bit(epnum, &status, 16) अणु
		retval = IRQ_HANDLED;
		अगर (is_host_active(musb))
			musb_host_tx(musb, epnum);
		अन्यथा
			musb_g_tx(musb, epnum);
	पूर्ण

	status = musb->पूर्णांक_rx;

	क्रम_each_set_bit(epnum, &status, 16) अणु
		retval = IRQ_HANDLED;
		अगर (is_host_active(musb))
			musb_host_rx(musb, epnum);
		अन्यथा
			musb_g_rx(musb, epnum);
	पूर्ण

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(musb_पूर्णांकerrupt);

#अगर_अघोषित CONFIG_MUSB_PIO_ONLY
अटल bool use_dma = true;

/* "modprobe ... use_dma=0" etc */
module_param(use_dma, bool, 0644);
MODULE_PARM_DESC(use_dma, "enable/disable use of DMA");

व्योम musb_dma_completion(काष्ठा musb *musb, u8 epnum, u8 transmit)
अणु
	/* called with controller lock alपढ़ोy held */

	अगर (!epnum) अणु
		अगर (!is_cppi_enabled(musb)) अणु
			/* endpoपूर्णांक 0 */
			अगर (is_host_active(musb))
				musb_h_ep0_irq(musb);
			अन्यथा
				musb_g_ep0_irq(musb);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* endpoपूर्णांकs 1..15 */
		अगर (transmit) अणु
			अगर (is_host_active(musb))
				musb_host_tx(musb, epnum);
			अन्यथा
				musb_g_tx(musb, epnum);
		पूर्ण अन्यथा अणु
			/* receive */
			अगर (is_host_active(musb))
				musb_host_rx(musb, epnum);
			अन्यथा
				musb_g_rx(musb, epnum);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(musb_dma_completion);

#अन्यथा
#घोषणा use_dma			0
#पूर्ण_अगर

अटल पूर्णांक (*musb_phy_callback)(क्रमागत musb_vbus_id_status status);

/*
 * musb_mailbox - optional phy notअगरier function
 * @status phy state change
 *
 * Optionally माला_लो called from the USB PHY. Note that the USB PHY must be
 * disabled at the poपूर्णांक the phy_callback is रेजिस्टरed or unरेजिस्टरed.
 */
पूर्णांक musb_mailbox(क्रमागत musb_vbus_id_status status)
अणु
	अगर (musb_phy_callback)
		वापस musb_phy_callback(status);

	वापस -ENODEV;
पूर्ण;
EXPORT_SYMBOL_GPL(musb_mailbox);

/*-------------------------------------------------------------------------*/

अटल sमाप_प्रकार
mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा musb *musb = dev_to_musb(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&musb->lock, flags);
	ret = प्र_लिखो(buf, "%s\n", usb_otg_state_string(musb->xceiv->otg->state));
	spin_unlock_irqrestore(&musb->lock, flags);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा musb	*musb = dev_to_musb(dev);
	अचिन्हित दीर्घ	flags;
	पूर्णांक		status;

	spin_lock_irqsave(&musb->lock, flags);
	अगर (sysfs_streq(buf, "host"))
		status = musb_platक्रमm_set_mode(musb, MUSB_HOST);
	अन्यथा अगर (sysfs_streq(buf, "peripheral"))
		status = musb_platक्रमm_set_mode(musb, MUSB_PERIPHERAL);
	अन्यथा अगर (sysfs_streq(buf, "otg"))
		status = musb_platक्रमm_set_mode(musb, MUSB_OTG);
	अन्यथा
		status = -EINVAL;
	spin_unlock_irqrestore(&musb->lock, flags);

	वापस (status == 0) ? n : status;
पूर्ण
अटल DEVICE_ATTR_RW(mode);

अटल sमाप_प्रकार
vbus_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा musb	*musb = dev_to_musb(dev);
	अचिन्हित दीर्घ	flags;
	अचिन्हित दीर्घ	val;

	अगर (माला_पूछो(buf, "%lu", &val) < 1) अणु
		dev_err(dev, "Invalid VBUS timeout ms value\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&musb->lock, flags);
	/* क्रमce T(a_रुको_bcon) to be zero/unlimited *OR* valid */
	musb->a_रुको_bcon = val ? max_t(पूर्णांक, val, OTG_TIME_A_WAIT_BCON) : 0 ;
	अगर (musb->xceiv->otg->state == OTG_STATE_A_WAIT_BCON)
		musb->is_active = 0;
	musb_platक्रमm_try_idle(musb, jअगरfies + msecs_to_jअगरfies(val));
	spin_unlock_irqrestore(&musb->lock, flags);

	वापस n;
पूर्ण

अटल sमाप_प्रकार
vbus_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा musb	*musb = dev_to_musb(dev);
	अचिन्हित दीर्घ	flags;
	अचिन्हित दीर्घ	val;
	पूर्णांक		vbus;
	u8		devctl;

	pm_runसमय_get_sync(dev);
	spin_lock_irqsave(&musb->lock, flags);
	val = musb->a_रुको_bcon;
	vbus = musb_platक्रमm_get_vbus_status(musb);
	अगर (vbus < 0) अणु
		/* Use शेष MUSB method by means of DEVCTL रेजिस्टर */
		devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
		अगर ((devctl & MUSB_DEVCTL_VBUS)
				== (3 << MUSB_DEVCTL_VBUS_SHIFT))
			vbus = 1;
		अन्यथा
			vbus = 0;
	पूर्ण
	spin_unlock_irqrestore(&musb->lock, flags);
	pm_runसमय_put_sync(dev);

	वापस प्र_लिखो(buf, "Vbus %s, timeout %lu msec\n",
			vbus ? "on" : "off", val);
पूर्ण
अटल DEVICE_ATTR_RW(vbus);

/* Gadget drivers can't know that a host is connected so they might want
 * to start SRP, but users can.  This allows userspace to trigger SRP.
 */
अटल sमाप_प्रकार srp_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा musb	*musb = dev_to_musb(dev);
	अचिन्हित लघु	srp;

	अगर (माला_पूछो(buf, "%hu", &srp) != 1
			|| (srp != 1)) अणु
		dev_err(dev, "SRP: Value must be 1\n");
		वापस -EINVAL;
	पूर्ण

	अगर (srp == 1)
		musb_g_wakeup(musb);

	वापस n;
पूर्ण
अटल DEVICE_ATTR_WO(srp);

अटल काष्ठा attribute *musb_attrs[] = अणु
	&dev_attr_mode.attr,
	&dev_attr_vbus.attr,
	&dev_attr_srp.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(musb);

#घोषणा MUSB_QUIRK_B_INVALID_VBUS_91	(MUSB_DEVCTL_BDEVICE | \
					 (2 << MUSB_DEVCTL_VBUS_SHIFT) | \
					 MUSB_DEVCTL_SESSION)
#घोषणा MUSB_QUIRK_B_DISCONNECT_99	(MUSB_DEVCTL_BDEVICE | \
					 (3 << MUSB_DEVCTL_VBUS_SHIFT) | \
					 MUSB_DEVCTL_SESSION)
#घोषणा MUSB_QUIRK_A_DISCONNECT_19	((3 << MUSB_DEVCTL_VBUS_SHIFT) | \
					 MUSB_DEVCTL_SESSION)

/*
 * Check the musb devctl session bit to determine अगर we want to
 * allow PM runसमय क्रम the device. In general, we want to keep things
 * active when the session bit is set except after host disconnect.
 *
 * Only called from musb_irq_work. If this ever needs to get called
 * अन्यथाwhere, proper locking must be implemented क्रम musb->session.
 */
अटल व्योम musb_pm_runसमय_check_session(काष्ठा musb *musb)
अणु
	u8 devctl, s;
	पूर्णांक error;

	devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);

	/* Handle session status quirks first */
	s = MUSB_DEVCTL_FSDEV | MUSB_DEVCTL_LSDEV |
		MUSB_DEVCTL_HR;
	चयन (devctl & ~s) अणु
	हाल MUSB_QUIRK_B_DISCONNECT_99:
		अगर (musb->quirk_retries && !musb->flush_irq_work) अणु
			musb_dbg(musb, "Poll devctl in case of suspend after disconnect\n");
			schedule_delayed_work(&musb->irq_work,
					      msecs_to_jअगरfies(1000));
			musb->quirk_retries--;
		पूर्ण
		अवरोध;
	हाल MUSB_QUIRK_B_INVALID_VBUS_91:
		अगर (musb->quirk_retries && !musb->flush_irq_work) अणु
			musb_dbg(musb,
				 "Poll devctl on invalid vbus, assume no session");
			schedule_delayed_work(&musb->irq_work,
					      msecs_to_jअगरfies(1000));
			musb->quirk_retries--;
			वापस;
		पूर्ण
		fallthrough;
	हाल MUSB_QUIRK_A_DISCONNECT_19:
		अगर (musb->quirk_retries && !musb->flush_irq_work) अणु
			musb_dbg(musb,
				 "Poll devctl on possible host mode disconnect");
			schedule_delayed_work(&musb->irq_work,
					      msecs_to_jअगरfies(1000));
			musb->quirk_retries--;
			वापस;
		पूर्ण
		अगर (!musb->session)
			अवरोध;
		musb_dbg(musb, "Allow PM on possible host mode disconnect");
		pm_runसमय_mark_last_busy(musb->controller);
		pm_runसमय_put_स्वतःsuspend(musb->controller);
		musb->session = false;
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	/* No need to करो anything अगर session has not changed */
	s = devctl & MUSB_DEVCTL_SESSION;
	अगर (s == musb->session)
		वापस;

	/* Block PM or allow PM? */
	अगर (s) अणु
		musb_dbg(musb, "Block PM on active session: %02x", devctl);
		error = pm_runसमय_get_sync(musb->controller);
		अगर (error < 0)
			dev_err(musb->controller, "Could not enable: %i\n",
				error);
		musb->quirk_retries = 3;
	पूर्ण अन्यथा अणु
		musb_dbg(musb, "Allow PM with no session: %02x", devctl);
		pm_runसमय_mark_last_busy(musb->controller);
		pm_runसमय_put_स्वतःsuspend(musb->controller);
	पूर्ण

	musb->session = s;
पूर्ण

/* Only used to provide driver mode change events */
अटल व्योम musb_irq_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा musb *musb = container_of(data, काष्ठा musb, irq_work.work);
	पूर्णांक error;

	error = pm_runसमय_resume_and_get(musb->controller);
	अगर (error < 0) अणु
		dev_err(musb->controller, "Could not enable: %i\n", error);

		वापस;
	पूर्ण

	musb_pm_runसमय_check_session(musb);

	अगर (musb->xceiv->otg->state != musb->xceiv_old_state) अणु
		musb->xceiv_old_state = musb->xceiv->otg->state;
		sysfs_notअगरy(&musb->controller->kobj, शून्य, "mode");
	पूर्ण

	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);
पूर्ण

अटल व्योम musb_recover_from_babble(काष्ठा musb *musb)
अणु
	पूर्णांक ret;
	u8 devctl;

	musb_disable_पूर्णांकerrupts(musb);

	/*
	 * रुको at least 320 cycles of 60MHz घड़ी. That's 5.3us, we will give
	 * it some slack and रुको क्रम 10us.
	 */
	udelay(10);

	ret  = musb_platक्रमm_recover(musb);
	अगर (ret) अणु
		musb_enable_पूर्णांकerrupts(musb);
		वापस;
	पूर्ण

	/* drop session bit */
	devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
	devctl &= ~MUSB_DEVCTL_SESSION;
	musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);

	/* tell usbcore about it */
	musb_root_disconnect(musb);

	/*
	 * When a babble condition occurs, the musb controller
	 * हटाओs the session bit and the endpoपूर्णांक config is lost.
	 */
	अगर (musb->dyn_fअगरo)
		ret = ep_config_from_table(musb);
	अन्यथा
		ret = ep_config_from_hw(musb);

	/* restart session */
	अगर (ret == 0)
		musb_start(musb);
पूर्ण

/* --------------------------------------------------------------------------
 * Init support
 */

अटल काष्ठा musb *allocate_instance(काष्ठा device *dev,
		स्थिर काष्ठा musb_hdrc_config *config, व्योम __iomem *mbase)
अणु
	काष्ठा musb		*musb;
	काष्ठा musb_hw_ep	*ep;
	पूर्णांक			epnum;
	पूर्णांक			ret;

	musb = devm_kzalloc(dev, माप(*musb), GFP_KERNEL);
	अगर (!musb)
		वापस शून्य;

	INIT_LIST_HEAD(&musb->control);
	INIT_LIST_HEAD(&musb->in_bulk);
	INIT_LIST_HEAD(&musb->out_bulk);
	INIT_LIST_HEAD(&musb->pending_list);

	musb->vbuserr_retry = VBUSERR_RETRY_COUNT;
	musb->a_रुको_bcon = OTG_TIME_A_WAIT_BCON;
	musb->mregs = mbase;
	musb->ctrl_base = mbase;
	musb->nIrq = -ENODEV;
	musb->config = config;
	BUG_ON(musb->config->num_eps > MUSB_C_NUM_EPS);
	क्रम (epnum = 0, ep = musb->endpoपूर्णांकs;
			epnum < musb->config->num_eps;
			epnum++, ep++) अणु
		ep->musb = musb;
		ep->epnum = epnum;
	पूर्ण

	musb->controller = dev;

	ret = musb_host_alloc(musb);
	अगर (ret < 0)
		जाओ err_मुक्त;

	dev_set_drvdata(dev, musb);

	वापस musb;

err_मुक्त:
	वापस शून्य;
पूर्ण

अटल व्योम musb_मुक्त(काष्ठा musb *musb)
अणु
	/* this has multiple entry modes. it handles fault cleanup after
	 * probe(), where things may be partially set up, as well as rmmod
	 * cleanup after everything's been de-activated.
	 */

	अगर (musb->nIrq >= 0) अणु
		अगर (musb->irq_wake)
			disable_irq_wake(musb->nIrq);
		मुक्त_irq(musb->nIrq, musb);
	पूर्ण

	musb_host_मुक्त(musb);
पूर्ण

काष्ठा musb_pending_work अणु
	पूर्णांक (*callback)(काष्ठा musb *musb, व्योम *data);
	व्योम *data;
	काष्ठा list_head node;
पूर्ण;

#अगर_घोषित CONFIG_PM
/*
 * Called from musb_runसमय_resume(), musb_resume(), and
 * musb_queue_resume_work(). Callers must take musb->lock.
 */
अटल पूर्णांक musb_run_resume_work(काष्ठा musb *musb)
अणु
	काष्ठा musb_pending_work *w, *_w;
	अचिन्हित दीर्घ flags;
	पूर्णांक error = 0;

	spin_lock_irqsave(&musb->list_lock, flags);
	list_क्रम_each_entry_safe(w, _w, &musb->pending_list, node) अणु
		अगर (w->callback) अणु
			error = w->callback(musb, w->data);
			अगर (error < 0) अणु
				dev_err(musb->controller,
					"resume callback %p failed: %i\n",
					w->callback, error);
			पूर्ण
		पूर्ण
		list_del(&w->node);
		devm_kमुक्त(musb->controller, w);
	पूर्ण
	spin_unlock_irqrestore(&musb->list_lock, flags);

	वापस error;
पूर्ण
#पूर्ण_अगर

/*
 * Called to run work अगर device is active or अन्यथा queue the work to happen
 * on resume. Caller must take musb->lock and must hold an RPM reference.
 *
 * Note that we cowardly refuse queuing work after musb PM runसमय
 * resume is करोne calling musb_run_resume_work() and वापस -EINPROGRESS
 * instead.
 */
पूर्णांक musb_queue_resume_work(काष्ठा musb *musb,
			   पूर्णांक (*callback)(काष्ठा musb *musb, व्योम *data),
			   व्योम *data)
अणु
	काष्ठा musb_pending_work *w;
	अचिन्हित दीर्घ flags;
	bool is_suspended;
	पूर्णांक error;

	अगर (WARN_ON(!callback))
		वापस -EINVAL;

	spin_lock_irqsave(&musb->list_lock, flags);
	is_suspended = musb->is_runसमय_suspended;

	अगर (is_suspended) अणु
		w = devm_kzalloc(musb->controller, माप(*w), GFP_ATOMIC);
		अगर (!w) अणु
			error = -ENOMEM;
			जाओ out_unlock;
		पूर्ण

		w->callback = callback;
		w->data = data;

		list_add_tail(&w->node, &musb->pending_list);
		error = 0;
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&musb->list_lock, flags);

	अगर (!is_suspended)
		error = callback(musb, data);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(musb_queue_resume_work);

अटल व्योम musb_deनिश्चित_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा musb *musb;
	अचिन्हित दीर्घ flags;

	musb = container_of(work, काष्ठा musb, deनिश्चित_reset_work.work);

	spin_lock_irqsave(&musb->lock, flags);

	अगर (musb->port1_status & USB_PORT_STAT_RESET)
		musb_port_reset(musb, false);

	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

/*
 * Perक्रमm generic per-controller initialization.
 *
 * @dev: the controller (alपढ़ोy घड़ीed, etc)
 * @nIrq: IRQ number
 * @ctrl: भव address of controller रेजिस्टरs,
 *	not yet corrected क्रम platक्रमm-specअगरic offsets
 */
अटल पूर्णांक
musb_init_controller(काष्ठा device *dev, पूर्णांक nIrq, व्योम __iomem *ctrl)
अणु
	पूर्णांक			status;
	काष्ठा musb		*musb;
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);

	/* The driver might handle more features than the board; OK.
	 * Fail when the board needs a feature that's not enabled.
	 */
	अगर (!plat) अणु
		dev_err(dev, "no platform_data?\n");
		status = -ENODEV;
		जाओ fail0;
	पूर्ण

	/* allocate */
	musb = allocate_instance(dev, plat->config, ctrl);
	अगर (!musb) अणु
		status = -ENOMEM;
		जाओ fail0;
	पूर्ण

	spin_lock_init(&musb->lock);
	spin_lock_init(&musb->list_lock);
	musb->board_set_घातer = plat->set_घातer;
	musb->min_घातer = plat->min_घातer;
	musb->ops = plat->platक्रमm_ops;
	musb->port_mode = plat->mode;

	/*
	 * Initialize the शेष IO functions. At least omap2430 needs
	 * these early. We initialize the platक्रमm specअगरic IO functions
	 * later on.
	 */
	musb_पढ़ोb = musb_शेष_पढ़ोb;
	musb_ग_लिखोb = musb_शेष_ग_लिखोb;
	musb_पढ़ोw = musb_शेष_पढ़ोw;
	musb_ग_लिखोw = musb_शेष_ग_लिखोw;

	/* The musb_platक्रमm_init() call:
	 *   - adjusts musb->mregs
	 *   - sets the musb->isr
	 *   - may initialize an पूर्णांकegrated transceiver
	 *   - initializes musb->xceiv, usually by otg_get_phy()
	 *   - stops घातering VBUS
	 *
	 * There are various transceiver configurations.
	 * DaVinci, TUSB60x0, and others पूर्णांकegrate them.  OMAP3 uses
	 * बाह्यal/discrete ones in various flavors (twl4030 family,
	 * isp1504, non-OTG, etc) mostly hooking up through ULPI.
	 */
	status = musb_platक्रमm_init(musb);
	अगर (status < 0)
		जाओ fail1;

	अगर (!musb->isr) अणु
		status = -ENODEV;
		जाओ fail2;
	पूर्ण


	/* Most devices use indexed offset or flat offset */
	अगर (musb->ops->quirks & MUSB_INDEXED_EP) अणु
		musb->io.ep_offset = musb_indexed_ep_offset;
		musb->io.ep_select = musb_indexed_ep_select;
	पूर्ण अन्यथा अणु
		musb->io.ep_offset = musb_flat_ep_offset;
		musb->io.ep_select = musb_flat_ep_select;
	पूर्ण

	अगर (musb->ops->quirks & MUSB_G_NO_SKB_RESERVE)
		musb->g.quirk_aव्योमs_skb_reserve = 1;

	/* At least tusb6010 has its own offsets */
	अगर (musb->ops->ep_offset)
		musb->io.ep_offset = musb->ops->ep_offset;
	अगर (musb->ops->ep_select)
		musb->io.ep_select = musb->ops->ep_select;

	अगर (musb->ops->fअगरo_mode)
		fअगरo_mode = musb->ops->fअगरo_mode;
	अन्यथा
		fअगरo_mode = 4;

	अगर (musb->ops->fअगरo_offset)
		musb->io.fअगरo_offset = musb->ops->fअगरo_offset;
	अन्यथा
		musb->io.fअगरo_offset = musb_शेष_fअगरo_offset;

	अगर (musb->ops->busctl_offset)
		musb->io.busctl_offset = musb->ops->busctl_offset;
	अन्यथा
		musb->io.busctl_offset = musb_शेष_busctl_offset;

	अगर (musb->ops->पढ़ोb)
		musb_पढ़ोb = musb->ops->पढ़ोb;
	अगर (musb->ops->ग_लिखोb)
		musb_ग_लिखोb = musb->ops->ग_लिखोb;
	अगर (musb->ops->clearb)
		musb_clearb = musb->ops->clearb;
	अन्यथा
		musb_clearb = musb_पढ़ोb;

	अगर (musb->ops->पढ़ोw)
		musb_पढ़ोw = musb->ops->पढ़ोw;
	अगर (musb->ops->ग_लिखोw)
		musb_ग_लिखोw = musb->ops->ग_लिखोw;
	अगर (musb->ops->clearw)
		musb_clearw = musb->ops->clearw;
	अन्यथा
		musb_clearw = musb_पढ़ोw;

#अगर_अघोषित CONFIG_MUSB_PIO_ONLY
	अगर (!musb->ops->dma_init || !musb->ops->dma_निकास) अणु
		dev_err(dev, "DMA controller not set\n");
		status = -ENODEV;
		जाओ fail2;
	पूर्ण
	musb_dma_controller_create = musb->ops->dma_init;
	musb_dma_controller_destroy = musb->ops->dma_निकास;
#पूर्ण_अगर

	अगर (musb->ops->पढ़ो_fअगरo)
		musb->io.पढ़ो_fअगरo = musb->ops->पढ़ो_fअगरo;
	अन्यथा
		musb->io.पढ़ो_fअगरo = musb_शेष_पढ़ो_fअगरo;

	अगर (musb->ops->ग_लिखो_fअगरo)
		musb->io.ग_लिखो_fअगरo = musb->ops->ग_लिखो_fअगरo;
	अन्यथा
		musb->io.ग_लिखो_fअगरo = musb_शेष_ग_लिखो_fअगरo;

	अगर (musb->ops->get_toggle)
		musb->io.get_toggle = musb->ops->get_toggle;
	अन्यथा
		musb->io.get_toggle = musb_शेष_get_toggle;

	अगर (musb->ops->set_toggle)
		musb->io.set_toggle = musb->ops->set_toggle;
	अन्यथा
		musb->io.set_toggle = musb_शेष_set_toggle;

	अगर (!musb->xceiv->io_ops) अणु
		musb->xceiv->io_dev = musb->controller;
		musb->xceiv->io_priv = musb->mregs;
		musb->xceiv->io_ops = &musb_ulpi_access;
	पूर्ण

	अगर (musb->ops->phy_callback)
		musb_phy_callback = musb->ops->phy_callback;

	/*
	 * We need musb_पढ़ो/ग_लिखो functions initialized क्रम PM.
	 * Note that at least 2430 glue needs स्वतःsuspend delay
	 * somewhere above 300 ms क्रम the hardware to idle properly
	 * after disconnecting the cable in host mode. Let's use
	 * 500 ms क्रम some margin.
	 */
	pm_runसमय_use_स्वतःsuspend(musb->controller);
	pm_runसमय_set_स्वतःsuspend_delay(musb->controller, 500);
	pm_runसमय_enable(musb->controller);
	pm_runसमय_get_sync(musb->controller);

	status = usb_phy_init(musb->xceiv);
	अगर (status < 0)
		जाओ err_usb_phy_init;

	अगर (use_dma && dev->dma_mask) अणु
		musb->dma_controller =
			musb_dma_controller_create(musb, musb->mregs);
		अगर (IS_ERR(musb->dma_controller)) अणु
			status = PTR_ERR(musb->dma_controller);
			जाओ fail2_5;
		पूर्ण
	पूर्ण

	/* be sure पूर्णांकerrupts are disabled beक्रमe connecting ISR */
	musb_platक्रमm_disable(musb);
	musb_disable_पूर्णांकerrupts(musb);
	musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, 0);

	/* MUSB_POWER_SOFTCONN might be alपढ़ोy set, JZ4740 करोes this. */
	musb_ग_लिखोb(musb->mregs, MUSB_POWER, 0);

	/* Init IRQ workqueue beक्रमe request_irq */
	INIT_DELAYED_WORK(&musb->irq_work, musb_irq_work);
	INIT_DELAYED_WORK(&musb->deनिश्चित_reset_work, musb_deनिश्चित_reset);
	INIT_DELAYED_WORK(&musb->finish_resume_work, musb_host_finish_resume);

	/* setup musb parts of the core (especially endpoपूर्णांकs) */
	status = musb_core_init(plat->config->multipoपूर्णांक
			? MUSB_CONTROLLER_MHDRC
			: MUSB_CONTROLLER_HDRC, musb);
	अगर (status < 0)
		जाओ fail3;

	समयr_setup(&musb->otg_समयr, musb_otg_समयr_func, 0);

	/* attach to the IRQ */
	अगर (request_irq(nIrq, musb->isr, IRQF_SHARED, dev_name(dev), musb)) अणु
		dev_err(dev, "request_irq %d failed!\n", nIrq);
		status = -ENODEV;
		जाओ fail3;
	पूर्ण
	musb->nIrq = nIrq;
	/* FIXME this handles wakeup irqs wrong */
	अगर (enable_irq_wake(nIrq) == 0) अणु
		musb->irq_wake = 1;
		device_init_wakeup(dev, 1);
	पूर्ण अन्यथा अणु
		musb->irq_wake = 0;
	पूर्ण

	/* program PHY to use बाह्यal vBus अगर required */
	अगर (plat->extvbus) अणु
		u8 busctl = musb_पढ़ोb(musb->mregs, MUSB_ULPI_BUSCONTROL);
		busctl |= MUSB_ULPI_USE_EXTVBUS;
		musb_ग_लिखोb(musb->mregs, MUSB_ULPI_BUSCONTROL, busctl);
	पूर्ण

	MUSB_DEV_MODE(musb);
	musb->xceiv->otg->state = OTG_STATE_B_IDLE;

	चयन (musb->port_mode) अणु
	हाल MUSB_HOST:
		status = musb_host_setup(musb, plat->घातer);
		अगर (status < 0)
			जाओ fail3;
		status = musb_platक्रमm_set_mode(musb, MUSB_HOST);
		अवरोध;
	हाल MUSB_PERIPHERAL:
		status = musb_gadget_setup(musb);
		अगर (status < 0)
			जाओ fail3;
		status = musb_platक्रमm_set_mode(musb, MUSB_PERIPHERAL);
		अवरोध;
	हाल MUSB_OTG:
		status = musb_host_setup(musb, plat->घातer);
		अगर (status < 0)
			जाओ fail3;
		status = musb_gadget_setup(musb);
		अगर (status) अणु
			musb_host_cleanup(musb);
			जाओ fail3;
		पूर्ण
		status = musb_platक्रमm_set_mode(musb, MUSB_OTG);
		अवरोध;
	शेष:
		dev_err(dev, "unsupported port mode %d\n", musb->port_mode);
		अवरोध;
	पूर्ण

	अगर (status < 0)
		जाओ fail3;

	musb_init_debugfs(musb);

	musb->is_initialized = 1;
	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);

	वापस 0;

fail3:
	cancel_delayed_work_sync(&musb->irq_work);
	cancel_delayed_work_sync(&musb->finish_resume_work);
	cancel_delayed_work_sync(&musb->deनिश्चित_reset_work);
	अगर (musb->dma_controller)
		musb_dma_controller_destroy(musb->dma_controller);

fail2_5:
	usb_phy_shutकरोwn(musb->xceiv);

err_usb_phy_init:
	pm_runसमय_करोnt_use_स्वतःsuspend(musb->controller);
	pm_runसमय_put_sync(musb->controller);
	pm_runसमय_disable(musb->controller);

fail2:
	अगर (musb->irq_wake)
		device_init_wakeup(dev, 0);
	musb_platक्रमm_निकास(musb);

fail1:
	अगर (status != -EPROBE_DEFER)
		dev_err(musb->controller,
			"%s failed with status %d\n", __func__, status);

	musb_मुक्त(musb);

fail0:

	वापस status;

पूर्ण

/*-------------------------------------------------------------------------*/

/* all implementations (PCI bridge to FPGA, VLYNQ, etc) should just
 * bridge to a platक्रमm device; this driver then suffices.
 */
अटल पूर्णांक musb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device	*dev = &pdev->dev;
	पूर्णांक		irq = platक्रमm_get_irq_byname(pdev, "mc");
	व्योम __iomem	*base;

	अगर (irq <= 0)
		वापस -ENODEV;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	वापस musb_init_controller(dev, irq, base);
पूर्ण

अटल पूर्णांक musb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device	*dev = &pdev->dev;
	काष्ठा musb	*musb = dev_to_musb(dev);
	अचिन्हित दीर्घ	flags;

	/* this माला_लो called on rmmod.
	 *  - Host mode: host may still be active
	 *  - Peripheral mode: peripheral is deactivated (or never-activated)
	 *  - OTG mode: both roles are deactivated (or never-activated)
	 */
	musb_निकास_debugfs(musb);

	cancel_delayed_work_sync(&musb->irq_work);
	cancel_delayed_work_sync(&musb->finish_resume_work);
	cancel_delayed_work_sync(&musb->deनिश्चित_reset_work);
	pm_runसमय_get_sync(musb->controller);
	musb_host_cleanup(musb);
	musb_gadget_cleanup(musb);

	musb_platक्रमm_disable(musb);
	spin_lock_irqsave(&musb->lock, flags);
	musb_disable_पूर्णांकerrupts(musb);
	musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, 0);
	spin_unlock_irqrestore(&musb->lock, flags);
	musb_platक्रमm_निकास(musb);

	pm_runसमय_करोnt_use_स्वतःsuspend(musb->controller);
	pm_runसमय_put_sync(musb->controller);
	pm_runसमय_disable(musb->controller);
	musb_phy_callback = शून्य;
	अगर (musb->dma_controller)
		musb_dma_controller_destroy(musb->dma_controller);
	usb_phy_shutकरोwn(musb->xceiv);
	musb_मुक्त(musb);
	device_init_wakeup(dev, 0);
	वापस 0;
पूर्ण

#अगर_घोषित	CONFIG_PM

अटल व्योम musb_save_context(काष्ठा musb *musb)
अणु
	पूर्णांक i;
	व्योम __iomem *musb_base = musb->mregs;
	व्योम __iomem *epio;

	musb->context.frame = musb_पढ़ोw(musb_base, MUSB_FRAME);
	musb->context.tesपंचांगode = musb_पढ़ोb(musb_base, MUSB_TESTMODE);
	musb->context.busctl = musb_पढ़ोb(musb_base, MUSB_ULPI_BUSCONTROL);
	musb->context.घातer = musb_पढ़ोb(musb_base, MUSB_POWER);
	musb->context.पूर्णांकrusbe = musb_पढ़ोb(musb_base, MUSB_INTRUSBE);
	musb->context.index = musb_पढ़ोb(musb_base, MUSB_INDEX);
	musb->context.devctl = musb_पढ़ोb(musb_base, MUSB_DEVCTL);

	क्रम (i = 0; i < musb->config->num_eps; ++i) अणु
		काष्ठा musb_hw_ep	*hw_ep;

		hw_ep = &musb->endpoपूर्णांकs[i];
		अगर (!hw_ep)
			जारी;

		epio = hw_ep->regs;
		अगर (!epio)
			जारी;

		musb_ग_लिखोb(musb_base, MUSB_INDEX, i);
		musb->context.index_regs[i].txmaxp =
			musb_पढ़ोw(epio, MUSB_TXMAXP);
		musb->context.index_regs[i].txcsr =
			musb_पढ़ोw(epio, MUSB_TXCSR);
		musb->context.index_regs[i].rxmaxp =
			musb_पढ़ोw(epio, MUSB_RXMAXP);
		musb->context.index_regs[i].rxcsr =
			musb_पढ़ोw(epio, MUSB_RXCSR);

		अगर (musb->dyn_fअगरo) अणु
			musb->context.index_regs[i].txfअगरoadd =
					musb_पढ़ोw(musb_base, MUSB_TXFIFOADD);
			musb->context.index_regs[i].rxfअगरoadd =
					musb_पढ़ोw(musb_base, MUSB_RXFIFOADD);
			musb->context.index_regs[i].txfअगरosz =
					musb_पढ़ोb(musb_base, MUSB_TXFIFOSZ);
			musb->context.index_regs[i].rxfअगरosz =
					musb_पढ़ोb(musb_base, MUSB_RXFIFOSZ);
		पूर्ण

		musb->context.index_regs[i].txtype =
			musb_पढ़ोb(epio, MUSB_TXTYPE);
		musb->context.index_regs[i].txपूर्णांकerval =
			musb_पढ़ोb(epio, MUSB_TXINTERVAL);
		musb->context.index_regs[i].rxtype =
			musb_पढ़ोb(epio, MUSB_RXTYPE);
		musb->context.index_regs[i].rxपूर्णांकerval =
			musb_पढ़ोb(epio, MUSB_RXINTERVAL);

		musb->context.index_regs[i].txfunaddr =
			musb_पढ़ो_txfunaddr(musb, i);
		musb->context.index_regs[i].txhubaddr =
			musb_पढ़ो_txhubaddr(musb, i);
		musb->context.index_regs[i].txhubport =
			musb_पढ़ो_txhubport(musb, i);

		musb->context.index_regs[i].rxfunaddr =
			musb_पढ़ो_rxfunaddr(musb, i);
		musb->context.index_regs[i].rxhubaddr =
			musb_पढ़ो_rxhubaddr(musb, i);
		musb->context.index_regs[i].rxhubport =
			musb_पढ़ो_rxhubport(musb, i);
	पूर्ण
पूर्ण

अटल व्योम musb_restore_context(काष्ठा musb *musb)
अणु
	पूर्णांक i;
	व्योम __iomem *musb_base = musb->mregs;
	व्योम __iomem *epio;
	u8 घातer;

	musb_ग_लिखोw(musb_base, MUSB_FRAME, musb->context.frame);
	musb_ग_लिखोb(musb_base, MUSB_TESTMODE, musb->context.tesपंचांगode);
	musb_ग_लिखोb(musb_base, MUSB_ULPI_BUSCONTROL, musb->context.busctl);

	/* Don't affect SUSPENDM/RESUME bits in POWER reg */
	घातer = musb_पढ़ोb(musb_base, MUSB_POWER);
	घातer &= MUSB_POWER_SUSPENDM | MUSB_POWER_RESUME;
	musb->context.घातer &= ~(MUSB_POWER_SUSPENDM | MUSB_POWER_RESUME);
	घातer |= musb->context.घातer;
	musb_ग_लिखोb(musb_base, MUSB_POWER, घातer);

	musb_ग_लिखोw(musb_base, MUSB_INTRTXE, musb->पूर्णांकrtxe);
	musb_ग_लिखोw(musb_base, MUSB_INTRRXE, musb->पूर्णांकrrxe);
	musb_ग_लिखोb(musb_base, MUSB_INTRUSBE, musb->context.पूर्णांकrusbe);
	अगर (musb->context.devctl & MUSB_DEVCTL_SESSION)
		musb_ग_लिखोb(musb_base, MUSB_DEVCTL, musb->context.devctl);

	क्रम (i = 0; i < musb->config->num_eps; ++i) अणु
		काष्ठा musb_hw_ep	*hw_ep;

		hw_ep = &musb->endpoपूर्णांकs[i];
		अगर (!hw_ep)
			जारी;

		epio = hw_ep->regs;
		अगर (!epio)
			जारी;

		musb_ग_लिखोb(musb_base, MUSB_INDEX, i);
		musb_ग_लिखोw(epio, MUSB_TXMAXP,
			musb->context.index_regs[i].txmaxp);
		musb_ग_लिखोw(epio, MUSB_TXCSR,
			musb->context.index_regs[i].txcsr);
		musb_ग_लिखोw(epio, MUSB_RXMAXP,
			musb->context.index_regs[i].rxmaxp);
		musb_ग_लिखोw(epio, MUSB_RXCSR,
			musb->context.index_regs[i].rxcsr);

		अगर (musb->dyn_fअगरo) अणु
			musb_ग_लिखोb(musb_base, MUSB_TXFIFOSZ,
				musb->context.index_regs[i].txfअगरosz);
			musb_ग_लिखोb(musb_base, MUSB_RXFIFOSZ,
				musb->context.index_regs[i].rxfअगरosz);
			musb_ग_लिखोw(musb_base, MUSB_TXFIFOADD,
				musb->context.index_regs[i].txfअगरoadd);
			musb_ग_लिखोw(musb_base, MUSB_RXFIFOADD,
				musb->context.index_regs[i].rxfअगरoadd);
		पूर्ण

		musb_ग_लिखोb(epio, MUSB_TXTYPE,
				musb->context.index_regs[i].txtype);
		musb_ग_लिखोb(epio, MUSB_TXINTERVAL,
				musb->context.index_regs[i].txपूर्णांकerval);
		musb_ग_लिखोb(epio, MUSB_RXTYPE,
				musb->context.index_regs[i].rxtype);
		musb_ग_लिखोb(epio, MUSB_RXINTERVAL,

				musb->context.index_regs[i].rxपूर्णांकerval);
		musb_ग_लिखो_txfunaddr(musb, i,
				musb->context.index_regs[i].txfunaddr);
		musb_ग_लिखो_txhubaddr(musb, i,
				musb->context.index_regs[i].txhubaddr);
		musb_ग_लिखो_txhubport(musb, i,
				musb->context.index_regs[i].txhubport);

		musb_ग_लिखो_rxfunaddr(musb, i,
				musb->context.index_regs[i].rxfunaddr);
		musb_ग_लिखो_rxhubaddr(musb, i,
				musb->context.index_regs[i].rxhubaddr);
		musb_ग_लिखो_rxhubport(musb, i,
				musb->context.index_regs[i].rxhubport);
	पूर्ण
	musb_ग_लिखोb(musb_base, MUSB_INDEX, musb->context.index);
पूर्ण

अटल पूर्णांक musb_suspend(काष्ठा device *dev)
अणु
	काष्ठा musb	*musb = dev_to_musb(dev);
	अचिन्हित दीर्घ	flags;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	musb_platक्रमm_disable(musb);
	musb_disable_पूर्णांकerrupts(musb);

	musb->flush_irq_work = true;
	जबतक (flush_delayed_work(&musb->irq_work))
		;
	musb->flush_irq_work = false;

	अगर (!(musb->ops->quirks & MUSB_PRESERVE_SESSION))
		musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, 0);

	WARN_ON(!list_empty(&musb->pending_list));

	spin_lock_irqsave(&musb->lock, flags);

	अगर (is_peripheral_active(musb)) अणु
		/* FIXME क्रमce disconnect unless we know USB will wake
		 * the प्रणाली up quickly enough to respond ...
		 */
	पूर्ण अन्यथा अगर (is_host_active(musb)) अणु
		/* we know all the children are suspended; someबार
		 * they will even be wakeup-enabled.
		 */
	पूर्ण

	musb_save_context(musb);

	spin_unlock_irqrestore(&musb->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक musb_resume(काष्ठा device *dev)
अणु
	काष्ठा musb *musb = dev_to_musb(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक error;
	u8 devctl;
	u8 mask;

	/*
	 * For अटल cmos like DaVinci, रेजिस्टर values were preserved
	 * unless क्रम some reason the whole soc घातered करोwn or the USB
	 * module got reset through the PSC (vs just being disabled).
	 *
	 * For the DSPS glue layer though, a full रेजिस्टर restore has to
	 * be करोne. As it shouldn't harm other platक्रमms, we करो it
	 * unconditionally.
	 */

	musb_restore_context(musb);

	devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
	mask = MUSB_DEVCTL_BDEVICE | MUSB_DEVCTL_FSDEV | MUSB_DEVCTL_LSDEV;
	अगर ((devctl & mask) != (musb->context.devctl & mask))
		musb->port1_status = 0;

	musb_enable_पूर्णांकerrupts(musb);
	musb_platक्रमm_enable(musb);

	/* session might be disabled in suspend */
	अगर (musb->port_mode == MUSB_HOST &&
	    !(musb->ops->quirks & MUSB_PRESERVE_SESSION)) अणु
		devctl |= MUSB_DEVCTL_SESSION;
		musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);
	पूर्ण

	spin_lock_irqsave(&musb->lock, flags);
	error = musb_run_resume_work(musb);
	अगर (error)
		dev_err(musb->controller, "resume work failed with %i\n",
			error);
	spin_unlock_irqrestore(&musb->lock, flags);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक musb_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा musb	*musb = dev_to_musb(dev);

	musb_save_context(musb);
	musb->is_runसमय_suspended = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक musb_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा musb *musb = dev_to_musb(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	/*
	 * When pm_runसमय_get_sync called क्रम the first समय in driver
	 * init,  some of the काष्ठाure is still not initialized which is
	 * used in restore function. But घड़ी needs to be
	 * enabled beक्रमe any रेजिस्टर access, so
	 * pm_runसमय_get_sync has to be called.
	 * Also context restore without save करोes not make
	 * any sense
	 */
	अगर (!musb->is_initialized)
		वापस 0;

	musb_restore_context(musb);

	spin_lock_irqsave(&musb->lock, flags);
	error = musb_run_resume_work(musb);
	अगर (error)
		dev_err(musb->controller, "resume work failed with %i\n",
			error);
	musb->is_runसमय_suspended = 0;
	spin_unlock_irqrestore(&musb->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops musb_dev_pm_ops = अणु
	.suspend	= musb_suspend,
	.resume		= musb_resume,
	.runसमय_suspend = musb_runसमय_suspend,
	.runसमय_resume = musb_runसमय_resume,
पूर्ण;

#घोषणा MUSB_DEV_PM_OPS (&musb_dev_pm_ops)
#अन्यथा
#घोषणा	MUSB_DEV_PM_OPS	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver musb_driver = अणु
	.driver = अणु
		.name		= musb_driver_name,
		.bus		= &platक्रमm_bus_type,
		.pm		= MUSB_DEV_PM_OPS,
		.dev_groups	= musb_groups,
	पूर्ण,
	.probe		= musb_probe,
	.हटाओ		= musb_हटाओ,
पूर्ण;

module_platक्रमm_driver(musb_driver);
