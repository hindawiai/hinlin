<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Intel PXA25x on-chip full speed USB device controller
 *
 * Copyright (C) 2003 Robert Schwebel <r.schwebel@pengutronix.de>, Pengutronix
 * Copyright (C) 2003 David Brownell
 */

#अगर_अघोषित __LINUX_USB_GADGET_PXA25X_H
#घोषणा __LINUX_USB_GADGET_PXA25X_H

#समावेश <linux/types.h>

/*-------------------------------------------------------------------------*/

/* pxa25x has this (move to include/यंत्र-arm/arch-pxa/pxa-regs.h) */
#घोषणा UFNRH_SIR	(1 << 7)	/* SOF पूर्णांकerrupt request */
#घोषणा UFNRH_SIM	(1 << 6)	/* SOF पूर्णांकerrupt mask */
#घोषणा UFNRH_IPE14	(1 << 5)	/* ISO packet error, ep14 */
#घोषणा UFNRH_IPE9	(1 << 4)	/* ISO packet error, ep9 */
#घोषणा UFNRH_IPE4	(1 << 3)	/* ISO packet error, ep4 */

/* pxa255 has this (move to include/यंत्र-arm/arch-pxa/pxa-regs.h) */
#घोषणा	UDCCFR		UDC_RES2	/* UDC Control Function Register */
#घोषणा UDCCFR_AREN	(1 << 7)	/* ACK response enable (now) */
#घोषणा UDCCFR_ACM	(1 << 2)	/* ACK control mode (रुको क्रम AREN) */

/* latest pxa255 errata define new "must be one" bits in UDCCFR */
#घोषणा	UDCCFR_MB1	(0xff & ~(UDCCFR_AREN|UDCCFR_ACM))

/*-------------------------------------------------------------------------*/

काष्ठा pxa25x_udc;

काष्ठा pxa25x_ep अणु
	काष्ठा usb_ep				ep;
	काष्ठा pxa25x_udc			*dev;

	काष्ठा list_head			queue;
	अचिन्हित दीर्घ				pio_irqs;

	अचिन्हित लघु				fअगरo_size;
	u8					bEndpoपूर्णांकAddress;
	u8					bmAttributes;

	अचिन्हित				stopped : 1;
	अचिन्हित				dma_fixup : 1;

	/* UDCCS = UDC Control/Status क्रम this EP
	 * UBCR = UDC Byte Count Reमुख्यing (contents of OUT fअगरo)
	 * UDDR = UDC Endpoपूर्णांक Data Register (the fअगरo)
	 * DRCM = DMA Request Channel Map
	 */
	u32					regoff_udccs;
	u32					regoff_ubcr;
	u32					regoff_uddr;
पूर्ण;

काष्ठा pxa25x_request अणु
	काष्ठा usb_request			req;
	काष्ठा list_head			queue;
पूर्ण;

क्रमागत ep0_state अणु
	EP0_IDLE,
	EP0_IN_DATA_PHASE,
	EP0_OUT_DATA_PHASE,
	EP0_END_XFER,
	EP0_STALL,
पूर्ण;

#घोषणा EP0_FIFO_SIZE	((अचिन्हित)16)
#घोषणा BULK_FIFO_SIZE	((अचिन्हित)64)
#घोषणा ISO_FIFO_SIZE	((अचिन्हित)256)
#घोषणा INT_FIFO_SIZE	((अचिन्हित)8)

काष्ठा udc_stats अणु
	काष्ठा ep0stats अणु
		अचिन्हित दीर्घ		ops;
		अचिन्हित दीर्घ		bytes;
	पूर्ण पढ़ो, ग_लिखो;
	अचिन्हित दीर्घ			irqs;
पूर्ण;

#अगर_घोषित CONFIG_USB_PXA25X_SMALL
/* when memory's tight, SMALL config saves code+data.  */
#घोषणा	PXA_UDC_NUM_ENDPOINTS	3
#पूर्ण_अगर

#अगर_अघोषित	PXA_UDC_NUM_ENDPOINTS
#घोषणा	PXA_UDC_NUM_ENDPOINTS	16
#पूर्ण_अगर

काष्ठा pxa25x_udc अणु
	काष्ठा usb_gadget			gadget;
	काष्ठा usb_gadget_driver		*driver;

	क्रमागत ep0_state				ep0state;
	काष्ठा udc_stats			stats;
	अचिन्हित				got_irq : 1,
						vbus : 1,
						pullup : 1,
						has_cfr : 1,
						req_pending : 1,
						req_std : 1,
						req_config : 1,
						suspended : 1,
						active : 1;

#घोषणा start_watchकरोg(dev) mod_समयr(&dev->समयr, jअगरfies + (HZ/200))
	काष्ठा समयr_list			समयr;

	काष्ठा device				*dev;
	काष्ठा clk				*clk;
	काष्ठा pxa2xx_udc_mach_info		*mach;
	काष्ठा usb_phy				*transceiver;
	u64					dma_mask;
	काष्ठा pxa25x_ep			ep [PXA_UDC_NUM_ENDPOINTS];

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS
	काष्ठा dentry				*debugfs_udc;
#पूर्ण_अगर
	व्योम __iomem				*regs;
पूर्ण;
#घोषणा to_pxa25x(g)	(container_of((g), काष्ठा pxa25x_udc, gadget))

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_ARCH_LUBBOCK
#समावेश <mach/lubbock.h>
/* lubbock can also report usb connect/disconnect irqs */
#पूर्ण_अगर

अटल काष्ठा pxa25x_udc *the_controller;

/*-------------------------------------------------------------------------*/

/*
 * Debugging support vanishes in non-debug builds.  DBG_NORMAL should be
 * mostly silent during normal use/testing, with no timing side-effects.
 */
#घोषणा DBG_NORMAL	1	/* error paths, device state transitions */
#घोषणा DBG_VERBOSE	2	/* add some success path trace info */
#घोषणा DBG_NOISY	3	/* ... even more: request level */
#घोषणा DBG_VERY_NOISY	4	/* ... even more: packet level */

#घोषणा DMSG(stuff...)	pr_debug("udc: " stuff)

#अगर_घोषित DEBUG

अटल स्थिर अक्षर *state_name[] = अणु
	"EP0_IDLE",
	"EP0_IN_DATA_PHASE", "EP0_OUT_DATA_PHASE",
	"EP0_END_XFER", "EP0_STALL"
पूर्ण;

#अगर_घोषित VERBOSE_DEBUG
#    define UDC_DEBUG DBG_VERBOSE
#अन्यथा
#    define UDC_DEBUG DBG_NORMAL
#पूर्ण_अगर

अटल व्योम __maybe_unused
dump_udccr(स्थिर अक्षर *label)
अणु
	u32	udccr = UDCCR;
	DMSG("%s %02X =%s%s%s%s%s%s%s%s\n",
		label, udccr,
		(udccr & UDCCR_REM) ? " rem" : "",
		(udccr & UDCCR_RSTIR) ? " rstir" : "",
		(udccr & UDCCR_SRM) ? " srm" : "",
		(udccr & UDCCR_SUSIR) ? " susir" : "",
		(udccr & UDCCR_RESIR) ? " resir" : "",
		(udccr & UDCCR_RSM) ? " rsm" : "",
		(udccr & UDCCR_UDA) ? " uda" : "",
		(udccr & UDCCR_UDE) ? " ude" : "");
पूर्ण

अटल व्योम __maybe_unused
dump_udccs0(स्थिर अक्षर *label)
अणु
	u32		udccs0 = UDCCS0;

	DMSG("%s %s %02X =%s%s%s%s%s%s%s%s\n",
		label, state_name[the_controller->ep0state], udccs0,
		(udccs0 & UDCCS0_SA) ? " sa" : "",
		(udccs0 & UDCCS0_RNE) ? " rne" : "",
		(udccs0 & UDCCS0_FST) ? " fst" : "",
		(udccs0 & UDCCS0_SST) ? " sst" : "",
		(udccs0 & UDCCS0_DRWF) ? " dwrf" : "",
		(udccs0 & UDCCS0_FTF) ? " ftf" : "",
		(udccs0 & UDCCS0_IPR) ? " ipr" : "",
		(udccs0 & UDCCS0_OPR) ? " opr" : "");
पूर्ण

अटल अंतरभूत u32 udc_ep_get_UDCCS(काष्ठा pxa25x_ep *);

अटल व्योम __maybe_unused
dump_state(काष्ठा pxa25x_udc *dev)
अणु
	u32		पंचांगp;
	अचिन्हित	i;

	DMSG("%s, uicr %02X.%02X, usir %02X.%02x, ufnr %02X.%02X\n",
		state_name[dev->ep0state],
		UICR1, UICR0, USIR1, USIR0, UFNRH, UFNRL);
	dump_udccr("udccr");
	अगर (dev->has_cfr) अणु
		पंचांगp = UDCCFR;
		DMSG("udccfr %02X =%s%s\n", पंचांगp,
			(पंचांगp & UDCCFR_AREN) ? " aren" : "",
			(पंचांगp & UDCCFR_ACM) ? " acm" : "");
	पूर्ण

	अगर (!dev->driver) अणु
		DMSG("no gadget driver bound\n");
		वापस;
	पूर्ण अन्यथा
		DMSG("ep0 driver '%s'\n", dev->driver->driver.name);

	dump_udccs0 ("udccs0");
	DMSG("ep0 IN %lu/%lu, OUT %lu/%lu\n",
		dev->stats.ग_लिखो.bytes, dev->stats.ग_लिखो.ops,
		dev->stats.पढ़ो.bytes, dev->stats.पढ़ो.ops);

	क्रम (i = 1; i < PXA_UDC_NUM_ENDPOINTS; i++) अणु
		अगर (dev->ep[i].ep.desc == शून्य)
			जारी;
		DMSG ("udccs%d = %02x\n", i, udc_ep_get_UDCCS(&dev->ep[i]));
	पूर्ण
पूर्ण

#अन्यथा

#घोषणा	dump_udccr(x)	करोअणुपूर्णजबतक(0)
#घोषणा	dump_udccs0(x)	करोअणुपूर्णजबतक(0)
#घोषणा	dump_state(x)	करोअणुपूर्णजबतक(0)

#घोषणा UDC_DEBUG ((अचिन्हित)0)

#पूर्ण_अगर

#घोषणा DBG(lvl, stuff...) करोअणुअगर ((lvl) <= UDC_DEBUG) DMSG(stuff);पूर्णजबतक(0)

#घोषणा ERR(stuff...)		pr_err("udc: " stuff)
#घोषणा WARNING(stuff...)	pr_warn("udc: " stuff)
#घोषणा INFO(stuff...)		pr_info("udc: " stuff)


#पूर्ण_अगर /* __LINUX_USB_GADGET_PXA25X_H */
