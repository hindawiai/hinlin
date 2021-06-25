<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Intel PXA25x and IXP4xx on-chip full speed USB device controllers
 *
 * Copyright (C) 2002 Intrinsyc, Inc. (Frank Becker)
 * Copyright (C) 2003 Robert Schwebel, Pengutronix
 * Copyright (C) 2003 Benedikt Spranger, Pengutronix
 * Copyright (C) 2003 David Brownell
 * Copyright (C) 2003 Joshua Wise
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_data/pxa2xx_udc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/prefetch.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>

#अगर_घोषित CONFIG_ARCH_LUBBOCK
#समावेश <mach/lubbock.h>
#पूर्ण_अगर

#घोषणा UDCCR	 0x0000 /* UDC Control Register */
#घोषणा UDC_RES1 0x0004 /* UDC Unकरोcumented - Reserved1 */
#घोषणा UDC_RES2 0x0008 /* UDC Unकरोcumented - Reserved2 */
#घोषणा UDC_RES3 0x000C /* UDC Unकरोcumented - Reserved3 */
#घोषणा UDCCS0	 0x0010 /* UDC Endpoपूर्णांक 0 Control/Status Register */
#घोषणा UDCCS1	 0x0014 /* UDC Endpoपूर्णांक 1 (IN) Control/Status Register */
#घोषणा UDCCS2	 0x0018 /* UDC Endpoपूर्णांक 2 (OUT) Control/Status Register */
#घोषणा UDCCS3	 0x001C /* UDC Endpoपूर्णांक 3 (IN) Control/Status Register */
#घोषणा UDCCS4	 0x0020 /* UDC Endpoपूर्णांक 4 (OUT) Control/Status Register */
#घोषणा UDCCS5	 0x0024 /* UDC Endpoपूर्णांक 5 (Interrupt) Control/Status Register */
#घोषणा UDCCS6	 0x0028 /* UDC Endpoपूर्णांक 6 (IN) Control/Status Register */
#घोषणा UDCCS7	 0x002C /* UDC Endpoपूर्णांक 7 (OUT) Control/Status Register */
#घोषणा UDCCS8	 0x0030 /* UDC Endpoपूर्णांक 8 (IN) Control/Status Register */
#घोषणा UDCCS9	 0x0034 /* UDC Endpoपूर्णांक 9 (OUT) Control/Status Register */
#घोषणा UDCCS10	 0x0038 /* UDC Endpoपूर्णांक 10 (Interrupt) Control/Status Register */
#घोषणा UDCCS11	 0x003C /* UDC Endpoपूर्णांक 11 (IN) Control/Status Register */
#घोषणा UDCCS12	 0x0040 /* UDC Endpoपूर्णांक 12 (OUT) Control/Status Register */
#घोषणा UDCCS13	 0x0044 /* UDC Endpoपूर्णांक 13 (IN) Control/Status Register */
#घोषणा UDCCS14	 0x0048 /* UDC Endpoपूर्णांक 14 (OUT) Control/Status Register */
#घोषणा UDCCS15	 0x004C /* UDC Endpoपूर्णांक 15 (Interrupt) Control/Status Register */
#घोषणा UFNRH	 0x0060 /* UDC Frame Number Register High */
#घोषणा UFNRL	 0x0064 /* UDC Frame Number Register Low */
#घोषणा UBCR2	 0x0068 /* UDC Byte Count Reg 2 */
#घोषणा UBCR4	 0x006c /* UDC Byte Count Reg 4 */
#घोषणा UBCR7	 0x0070 /* UDC Byte Count Reg 7 */
#घोषणा UBCR9	 0x0074 /* UDC Byte Count Reg 9 */
#घोषणा UBCR12	 0x0078 /* UDC Byte Count Reg 12 */
#घोषणा UBCR14	 0x007c /* UDC Byte Count Reg 14 */
#घोषणा UDDR0	 0x0080 /* UDC Endpoपूर्णांक 0 Data Register */
#घोषणा UDDR1	 0x0100 /* UDC Endpoपूर्णांक 1 Data Register */
#घोषणा UDDR2	 0x0180 /* UDC Endpoपूर्णांक 2 Data Register */
#घोषणा UDDR3	 0x0200 /* UDC Endpoपूर्णांक 3 Data Register */
#घोषणा UDDR4	 0x0400 /* UDC Endpoपूर्णांक 4 Data Register */
#घोषणा UDDR5	 0x00A0 /* UDC Endpoपूर्णांक 5 Data Register */
#घोषणा UDDR6	 0x0600 /* UDC Endpoपूर्णांक 6 Data Register */
#घोषणा UDDR7	 0x0680 /* UDC Endpoपूर्णांक 7 Data Register */
#घोषणा UDDR8	 0x0700 /* UDC Endpoपूर्णांक 8 Data Register */
#घोषणा UDDR9	 0x0900 /* UDC Endpoपूर्णांक 9 Data Register */
#घोषणा UDDR10	 0x00C0 /* UDC Endpoपूर्णांक 10 Data Register */
#घोषणा UDDR11	 0x0B00 /* UDC Endpoपूर्णांक 11 Data Register */
#घोषणा UDDR12	 0x0B80 /* UDC Endpoपूर्णांक 12 Data Register */
#घोषणा UDDR13	 0x0C00 /* UDC Endpoपूर्णांक 13 Data Register */
#घोषणा UDDR14	 0x0E00 /* UDC Endpoपूर्णांक 14 Data Register */
#घोषणा UDDR15	 0x00E0 /* UDC Endpoपूर्णांक 15 Data Register */

#घोषणा UICR0	 0x0050 /* UDC Interrupt Control Register 0 */
#घोषणा UICR1	 0x0054 /* UDC Interrupt Control Register 1 */

#घोषणा USIR0	 0x0058 /* UDC Status Interrupt Register 0 */
#घोषणा USIR1	 0x005C /* UDC Status Interrupt Register 1 */

#घोषणा UDCCR_UDE	(1 << 0)	/* UDC enable */
#घोषणा UDCCR_UDA	(1 << 1)	/* UDC active */
#घोषणा UDCCR_RSM	(1 << 2)	/* Device resume */
#घोषणा UDCCR_RESIR	(1 << 3)	/* Resume पूर्णांकerrupt request */
#घोषणा UDCCR_SUSIR	(1 << 4)	/* Suspend पूर्णांकerrupt request */
#घोषणा UDCCR_SRM	(1 << 5)	/* Suspend/resume पूर्णांकerrupt mask */
#घोषणा UDCCR_RSTIR	(1 << 6)	/* Reset पूर्णांकerrupt request */
#घोषणा UDCCR_REM	(1 << 7)	/* Reset पूर्णांकerrupt mask */

#घोषणा UDCCS0_OPR	(1 << 0)	/* OUT packet पढ़ोy */
#घोषणा UDCCS0_IPR	(1 << 1)	/* IN packet पढ़ोy */
#घोषणा UDCCS0_FTF	(1 << 2)	/* Flush Tx FIFO */
#घोषणा UDCCS0_DRWF	(1 << 3)	/* Device remote wakeup feature */
#घोषणा UDCCS0_SST	(1 << 4)	/* Sent stall */
#घोषणा UDCCS0_FST	(1 << 5)	/* Force stall */
#घोषणा UDCCS0_RNE	(1 << 6)	/* Receive FIFO no empty */
#घोषणा UDCCS0_SA	(1 << 7)	/* Setup active */

#घोषणा UDCCS_BI_TFS	(1 << 0)	/* Transmit FIFO service */
#घोषणा UDCCS_BI_TPC	(1 << 1)	/* Transmit packet complete */
#घोषणा UDCCS_BI_FTF	(1 << 2)	/* Flush Tx FIFO */
#घोषणा UDCCS_BI_TUR	(1 << 3)	/* Transmit FIFO underrun */
#घोषणा UDCCS_BI_SST	(1 << 4)	/* Sent stall */
#घोषणा UDCCS_BI_FST	(1 << 5)	/* Force stall */
#घोषणा UDCCS_BI_TSP	(1 << 7)	/* Transmit लघु packet */

#घोषणा UDCCS_BO_RFS	(1 << 0)	/* Receive FIFO service */
#घोषणा UDCCS_BO_RPC	(1 << 1)	/* Receive packet complete */
#घोषणा UDCCS_BO_DME	(1 << 3)	/* DMA enable */
#घोषणा UDCCS_BO_SST	(1 << 4)	/* Sent stall */
#घोषणा UDCCS_BO_FST	(1 << 5)	/* Force stall */
#घोषणा UDCCS_BO_RNE	(1 << 6)	/* Receive FIFO not empty */
#घोषणा UDCCS_BO_RSP	(1 << 7)	/* Receive लघु packet */

#घोषणा UDCCS_II_TFS	(1 << 0)	/* Transmit FIFO service */
#घोषणा UDCCS_II_TPC	(1 << 1)	/* Transmit packet complete */
#घोषणा UDCCS_II_FTF	(1 << 2)	/* Flush Tx FIFO */
#घोषणा UDCCS_II_TUR	(1 << 3)	/* Transmit FIFO underrun */
#घोषणा UDCCS_II_TSP	(1 << 7)	/* Transmit लघु packet */

#घोषणा UDCCS_IO_RFS	(1 << 0)	/* Receive FIFO service */
#घोषणा UDCCS_IO_RPC	(1 << 1)	/* Receive packet complete */
#अगर_घोषित CONFIG_ARCH_IXP4XX /* FIXME: is this right?, datasheed says '2' */
#घोषणा UDCCS_IO_ROF	(1 << 3)	/* Receive overflow */
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_PXA
#घोषणा UDCCS_IO_ROF	(1 << 2)	/* Receive overflow */
#पूर्ण_अगर
#घोषणा UDCCS_IO_DME	(1 << 3)	/* DMA enable */
#घोषणा UDCCS_IO_RNE	(1 << 6)	/* Receive FIFO not empty */
#घोषणा UDCCS_IO_RSP	(1 << 7)	/* Receive लघु packet */

#घोषणा UDCCS_INT_TFS	(1 << 0)	/* Transmit FIFO service */
#घोषणा UDCCS_INT_TPC	(1 << 1)	/* Transmit packet complete */
#घोषणा UDCCS_INT_FTF	(1 << 2)	/* Flush Tx FIFO */
#घोषणा UDCCS_INT_TUR	(1 << 3)	/* Transmit FIFO underrun */
#घोषणा UDCCS_INT_SST	(1 << 4)	/* Sent stall */
#घोषणा UDCCS_INT_FST	(1 << 5)	/* Force stall */
#घोषणा UDCCS_INT_TSP	(1 << 7)	/* Transmit लघु packet */

#घोषणा UICR0_IM0	(1 << 0)	/* Interrupt mask ep 0 */
#घोषणा UICR0_IM1	(1 << 1)	/* Interrupt mask ep 1 */
#घोषणा UICR0_IM2	(1 << 2)	/* Interrupt mask ep 2 */
#घोषणा UICR0_IM3	(1 << 3)	/* Interrupt mask ep 3 */
#घोषणा UICR0_IM4	(1 << 4)	/* Interrupt mask ep 4 */
#घोषणा UICR0_IM5	(1 << 5)	/* Interrupt mask ep 5 */
#घोषणा UICR0_IM6	(1 << 6)	/* Interrupt mask ep 6 */
#घोषणा UICR0_IM7	(1 << 7)	/* Interrupt mask ep 7 */

#घोषणा UICR1_IM8	(1 << 0)	/* Interrupt mask ep 8 */
#घोषणा UICR1_IM9	(1 << 1)	/* Interrupt mask ep 9 */
#घोषणा UICR1_IM10	(1 << 2)	/* Interrupt mask ep 10 */
#घोषणा UICR1_IM11	(1 << 3)	/* Interrupt mask ep 11 */
#घोषणा UICR1_IM12	(1 << 4)	/* Interrupt mask ep 12 */
#घोषणा UICR1_IM13	(1 << 5)	/* Interrupt mask ep 13 */
#घोषणा UICR1_IM14	(1 << 6)	/* Interrupt mask ep 14 */
#घोषणा UICR1_IM15	(1 << 7)	/* Interrupt mask ep 15 */

#घोषणा USIR0_IR0	(1 << 0)	/* Interrupt request ep 0 */
#घोषणा USIR0_IR1	(1 << 1)	/* Interrupt request ep 1 */
#घोषणा USIR0_IR2	(1 << 2)	/* Interrupt request ep 2 */
#घोषणा USIR0_IR3	(1 << 3)	/* Interrupt request ep 3 */
#घोषणा USIR0_IR4	(1 << 4)	/* Interrupt request ep 4 */
#घोषणा USIR0_IR5	(1 << 5)	/* Interrupt request ep 5 */
#घोषणा USIR0_IR6	(1 << 6)	/* Interrupt request ep 6 */
#घोषणा USIR0_IR7	(1 << 7)	/* Interrupt request ep 7 */

#घोषणा USIR1_IR8	(1 << 0)	/* Interrupt request ep 8 */
#घोषणा USIR1_IR9	(1 << 1)	/* Interrupt request ep 9 */
#घोषणा USIR1_IR10	(1 << 2)	/* Interrupt request ep 10 */
#घोषणा USIR1_IR11	(1 << 3)	/* Interrupt request ep 11 */
#घोषणा USIR1_IR12	(1 << 4)	/* Interrupt request ep 12 */
#घोषणा USIR1_IR13	(1 << 5)	/* Interrupt request ep 13 */
#घोषणा USIR1_IR14	(1 << 6)	/* Interrupt request ep 14 */
#घोषणा USIR1_IR15	(1 << 7)	/* Interrupt request ep 15 */

/*
 * This driver handles the USB Device Controller (UDC) in Intel's PXA 25x
 * series processors.  The UDC क्रम the IXP 4xx series is very similar.
 * There are fअगरteen endpoपूर्णांकs, in addition to ep0.
 *
 * Such controller drivers work with a gadget driver.  The gadget driver
 * वापसs descriptors, implements configuration and data protocols used
 * by the host to पूर्णांकeract with this device, and allocates endpoपूर्णांकs to
 * the dअगरferent protocol पूर्णांकerfaces.  The controller driver भवizes
 * usb hardware so that the gadget drivers will be more portable.
 *
 * This UDC hardware wants to implement a bit too much USB protocol, so
 * it स्थिरrains the sorts of USB configuration change events that work.
 * The errata क्रम these chips are misleading; some "fixed" bugs from
 * pxa250 a0/a1 b0/b1/b2 sure act like they're still there.
 *
 * Note that the UDC hardware supports DMA (except on IXP) but that's
 * not used here.  IN-DMA (to host) is simple enough, when the data is
 * suitably aligned (16 bytes) ... the network stack करोesn't करो that,
 * other software can.  OUT-DMA is buggy in most chip versions, as well
 * as poorly deचिन्हित (data toggle not स्वतःmatic).  So this driver won't
 * bother using DMA.  (Mostly-working IN-DMA support was available in
 * kernels beक्रमe 2.6.23, but was never enabled or well tested.)
 */

#घोषणा	DRIVER_VERSION	"30-June-2007"
#घोषणा	DRIVER_DESC	"PXA 25x USB Device Controller driver"


अटल स्थिर अक्षर driver_name [] = "pxa25x_udc";

अटल स्थिर अक्षर ep0name [] = "ep0";


#अगर_घोषित CONFIG_ARCH_IXP4XX

/* cpu-specअगरic रेजिस्टर addresses are compiled in to this code */
#अगर_घोषित CONFIG_ARCH_PXA
#त्रुटि "Can't configure both IXP and PXA"
#पूर्ण_अगर

/* IXP करोesn't yet support <linux/clk.h> */
#घोषणा clk_get(dev,name)	शून्य
#घोषणा clk_enable(clk)		करो अणु पूर्ण जबतक (0)
#घोषणा clk_disable(clk)	करो अणु पूर्ण जबतक (0)
#घोषणा clk_put(clk)		करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

#समावेश "pxa25x_udc.h"


#अगर_घोषित	CONFIG_USB_PXA25X_SMALL
#घोषणा SIZE_STR	" (small)"
#अन्यथा
#घोषणा SIZE_STR	""
#पूर्ण_अगर

/* ---------------------------------------------------------------------------
 *	endpoपूर्णांक related parts of the api to the usb controller hardware,
 *	used by gadget driver; and the inner talker-to-hardware core.
 * ---------------------------------------------------------------------------
 */

अटल व्योम pxa25x_ep_fअगरo_flush (काष्ठा usb_ep *ep);
अटल व्योम nuke (काष्ठा pxa25x_ep *, पूर्णांक status);

/* one GPIO should control a D+ pullup, so host sees this device (or not) */
अटल व्योम pullup_off(व्योम)
अणु
	काष्ठा pxa2xx_udc_mach_info		*mach = the_controller->mach;
	पूर्णांक off_level = mach->gpio_pullup_inverted;

	अगर (gpio_is_valid(mach->gpio_pullup))
		gpio_set_value(mach->gpio_pullup, off_level);
	अन्यथा अगर (mach->udc_command)
		mach->udc_command(PXA2XX_UDC_CMD_DISCONNECT);
पूर्ण

अटल व्योम pullup_on(व्योम)
अणु
	काष्ठा pxa2xx_udc_mach_info		*mach = the_controller->mach;
	पूर्णांक on_level = !mach->gpio_pullup_inverted;

	अगर (gpio_is_valid(mach->gpio_pullup))
		gpio_set_value(mach->gpio_pullup, on_level);
	अन्यथा अगर (mach->udc_command)
		mach->udc_command(PXA2XX_UDC_CMD_CONNECT);
पूर्ण

#अगर defined(CONFIG_CPU_BIG_ENDIAN)
/*
 * IXP4xx has its buses wired up in a way that relies on never करोing any
 * byte swaps, independent of whether it runs in big-endian or little-endian
 * mode, as explained by Krzysztof Haधasa.
 *
 * We only support pxa25x in little-endian mode, but it is very likely
 * that it works the same way.
 */
अटल अंतरभूत व्योम udc_set_reg(काष्ठा pxa25x_udc *dev, u32 reg, u32 val)
अणु
	ioग_लिखो32be(val, dev->regs + reg);
पूर्ण

अटल अंतरभूत u32 udc_get_reg(काष्ठा pxa25x_udc *dev, u32 reg)
अणु
	वापस ioपढ़ो32be(dev->regs + reg);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम udc_set_reg(काष्ठा pxa25x_udc *dev, u32 reg, u32 val)
अणु
	ग_लिखोl(val, dev->regs + reg);
पूर्ण

अटल अंतरभूत u32 udc_get_reg(काष्ठा pxa25x_udc *dev, u32 reg)
अणु
	वापस पढ़ोl(dev->regs + reg);
पूर्ण
#पूर्ण_अगर

अटल व्योम pio_irq_enable(काष्ठा pxa25x_ep *ep)
अणु
	u32 bEndpoपूर्णांकAddress = ep->bEndpoपूर्णांकAddress & 0xf;

        अगर (bEndpoपूर्णांकAddress < 8)
		udc_set_reg(ep->dev, UICR0, udc_get_reg(ep->dev, UICR0) &
						~(1 << bEndpoपूर्णांकAddress));
        अन्यथा अणु
                bEndpoपूर्णांकAddress -= 8;
		udc_set_reg(ep->dev, UICR1, udc_get_reg(ep->dev, UICR1) &
						~(1 << bEndpoपूर्णांकAddress));
	पूर्ण
पूर्ण

अटल व्योम pio_irq_disable(काष्ठा pxa25x_ep *ep)
अणु
	u32 bEndpoपूर्णांकAddress = ep->bEndpoपूर्णांकAddress & 0xf;

        अगर (bEndpoपूर्णांकAddress < 8)
                udc_set_reg(ep->dev, UICR0, udc_get_reg(ep->dev, UICR0) |
						(1 << bEndpoपूर्णांकAddress));
        अन्यथा अणु
                bEndpoपूर्णांकAddress -= 8;
                udc_set_reg(ep->dev, UICR1, udc_get_reg(ep->dev, UICR1) |
						(1 << bEndpoपूर्णांकAddress));
        पूर्ण
पूर्ण

/* The UDCCR reg contains mask and पूर्णांकerrupt status bits,
 * so using '|=' isn't safe as it may ack an पूर्णांकerrupt.
 */
#घोषणा UDCCR_MASK_BITS         (UDCCR_REM | UDCCR_SRM | UDCCR_UDE)

अटल अंतरभूत व्योम udc_set_mask_UDCCR(काष्ठा pxa25x_udc *dev, पूर्णांक mask)
अणु
	u32 udccr = udc_get_reg(dev, UDCCR);

	udc_set_reg(dev, (udccr & UDCCR_MASK_BITS) | (mask & UDCCR_MASK_BITS), UDCCR);
पूर्ण

अटल अंतरभूत व्योम udc_clear_mask_UDCCR(काष्ठा pxa25x_udc *dev, पूर्णांक mask)
अणु
	u32 udccr = udc_get_reg(dev, UDCCR);

	udc_set_reg(dev, (udccr & UDCCR_MASK_BITS) & ~(mask & UDCCR_MASK_BITS), UDCCR);
पूर्ण

अटल अंतरभूत व्योम udc_ack_पूर्णांक_UDCCR(काष्ठा pxa25x_udc *dev, पूर्णांक mask)
अणु
	/* udccr contains the bits we करोnt want to change */
	u32 udccr = udc_get_reg(dev, UDCCR) & UDCCR_MASK_BITS;

	udc_set_reg(dev, udccr | (mask & ~UDCCR_MASK_BITS), UDCCR);
पूर्ण

अटल अंतरभूत u32 udc_ep_get_UDCCS(काष्ठा pxa25x_ep *ep)
अणु
	वापस udc_get_reg(ep->dev, ep->regoff_udccs);
पूर्ण

अटल अंतरभूत व्योम udc_ep_set_UDCCS(काष्ठा pxa25x_ep *ep, u32 data)
अणु
	udc_set_reg(ep->dev, data, ep->regoff_udccs);
पूर्ण

अटल अंतरभूत u32 udc_ep0_get_UDCCS(काष्ठा pxa25x_udc *dev)
अणु
	वापस udc_get_reg(dev, UDCCS0);
पूर्ण

अटल अंतरभूत व्योम udc_ep0_set_UDCCS(काष्ठा pxa25x_udc *dev, u32 data)
अणु
	udc_set_reg(dev, data, UDCCS0);
पूर्ण

अटल अंतरभूत u32 udc_ep_get_UDDR(काष्ठा pxa25x_ep *ep)
अणु
	वापस udc_get_reg(ep->dev, ep->regoff_uddr);
पूर्ण

अटल अंतरभूत व्योम udc_ep_set_UDDR(काष्ठा pxa25x_ep *ep, u32 data)
अणु
	udc_set_reg(ep->dev, data, ep->regoff_uddr);
पूर्ण

अटल अंतरभूत u32 udc_ep_get_UBCR(काष्ठा pxa25x_ep *ep)
अणु
	वापस udc_get_reg(ep->dev, ep->regoff_ubcr);
पूर्ण

/*
 * endpoपूर्णांक enable/disable
 *
 * we need to verअगरy the descriptors used to enable endpoपूर्णांकs.  since pxa25x
 * endpoपूर्णांक configurations are fixed, and are pretty much always enabled,
 * there's not a lot to manage here.
 *
 * because pxa25x can't selectively initialize bulk (or पूर्णांकerrupt) endpoपूर्णांकs,
 * (resetting endpoपूर्णांक halt and toggle), SET_INTERFACE is unusable except
 * क्रम a single पूर्णांकerface (with only the शेष altsetting) and क्रम gadget
 * drivers that करोn't halt endpoपूर्णांकs (not reset by set_पूर्णांकerface).  that also
 * means that अगर you use ISO, you must violate the USB spec rule that all
 * iso endpoपूर्णांकs must be in non-शेष altsettings.
 */
अटल पूर्णांक pxa25x_ep_enable (काष्ठा usb_ep *_ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा pxa25x_ep        *ep;
	काष्ठा pxa25x_udc       *dev;

	ep = container_of (_ep, काष्ठा pxa25x_ep, ep);
	अगर (!_ep || !desc || _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT
			|| ep->bEndpoपूर्णांकAddress != desc->bEndpoपूर्णांकAddress
			|| ep->fअगरo_size < usb_endpoपूर्णांक_maxp (desc)) अणु
		DMSG("%s, bad ep or descriptor\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* xfer types must match, except that पूर्णांकerrupt ~= bulk */
	अगर (ep->bmAttributes != desc->bmAttributes
			&& ep->bmAttributes != USB_ENDPOINT_XFER_BULK
			&& desc->bmAttributes != USB_ENDPOINT_XFER_INT) अणु
		DMSG("%s, %s type mismatch\n", __func__, _ep->name);
		वापस -EINVAL;
	पूर्ण

	/* hardware _could_ करो smaller, but driver करोesn't */
	अगर ((desc->bmAttributes == USB_ENDPOINT_XFER_BULK
				&& usb_endpoपूर्णांक_maxp (desc)
						!= BULK_FIFO_SIZE)
			|| !desc->wMaxPacketSize) अणु
		DMSG("%s, bad %s maxpacket\n", __func__, _ep->name);
		वापस -दुस्फल;
	पूर्ण

	dev = ep->dev;
	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN) अणु
		DMSG("%s, bogus device state\n", __func__);
		वापस -ESHUTDOWN;
	पूर्ण

	ep->ep.desc = desc;
	ep->stopped = 0;
	ep->pio_irqs = 0;
	ep->ep.maxpacket = usb_endpoपूर्णांक_maxp (desc);

	/* flush fअगरo (mostly क्रम OUT buffers) */
	pxa25x_ep_fअगरo_flush (_ep);

	/* ... reset halt state too, अगर we could ... */

	DBG(DBG_VERBOSE, "enabled %s\n", _ep->name);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa25x_ep_disable (काष्ठा usb_ep *_ep)
अणु
	काष्ठा pxa25x_ep	*ep;
	अचिन्हित दीर्घ		flags;

	ep = container_of (_ep, काष्ठा pxa25x_ep, ep);
	अगर (!_ep || !ep->ep.desc) अणु
		DMSG("%s, %s not enabled\n", __func__,
			_ep ? ep->ep.name : शून्य);
		वापस -EINVAL;
	पूर्ण
	local_irq_save(flags);

	nuke (ep, -ESHUTDOWN);

	/* flush fअगरo (mostly क्रम IN buffers) */
	pxa25x_ep_fअगरo_flush (_ep);

	ep->ep.desc = शून्य;
	ep->stopped = 1;

	local_irq_restore(flags);
	DBG(DBG_VERBOSE, "%s disabled\n", _ep->name);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/* क्रम the pxa25x, these can just wrap kदो_स्मृति/kमुक्त.  gadget drivers
 * must still pass correctly initialized endpoपूर्णांकs, since other controller
 * drivers may care about how it's currently set up (dma issues etc).
 */

/*
 *	pxa25x_ep_alloc_request - allocate a request data काष्ठाure
 */
अटल काष्ठा usb_request *
pxa25x_ep_alloc_request (काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा pxa25x_request *req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD (&req->queue);
	वापस &req->req;
पूर्ण


/*
 *	pxa25x_ep_मुक्त_request - deallocate a request data काष्ठाure
 */
अटल व्योम
pxa25x_ep_मुक्त_request (काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा pxa25x_request	*req;

	req = container_of (_req, काष्ठा pxa25x_request, req);
	WARN_ON(!list_empty (&req->queue));
	kमुक्त(req);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 *	करोne - retire a request; caller blocked irqs
 */
अटल व्योम करोne(काष्ठा pxa25x_ep *ep, काष्ठा pxa25x_request *req, पूर्णांक status)
अणु
	अचिन्हित		stopped = ep->stopped;

	list_del_init(&req->queue);

	अगर (likely (req->req.status == -EINPROGRESS))
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	अगर (status && status != -ESHUTDOWN)
		DBG(DBG_VERBOSE, "complete %s req %p stat %d len %u/%u\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	/* करोn't modअगरy queue heads during completion callback */
	ep->stopped = 1;
	usb_gadget_giveback_request(&ep->ep, &req->req);
	ep->stopped = stopped;
पूर्ण


अटल अंतरभूत व्योम ep0_idle (काष्ठा pxa25x_udc *dev)
अणु
	dev->ep0state = EP0_IDLE;
पूर्ण

अटल पूर्णांक
ग_लिखो_packet(काष्ठा pxa25x_ep *ep, काष्ठा pxa25x_request *req, अचिन्हित max)
अणु
	u8		*buf;
	अचिन्हित	length, count;

	buf = req->req.buf + req->req.actual;
	prefetch(buf);

	/* how big will this packet be? */
	length = min(req->req.length - req->req.actual, max);
	req->req.actual += length;

	count = length;
	जबतक (likely(count--))
		udc_ep_set_UDDR(ep, *buf++);

	वापस length;
पूर्ण

/*
 * ग_लिखो to an IN endpoपूर्णांक fअगरo, as many packets as possible.
 * irqs will use this to ग_लिखो the rest later.
 * caller guarantees at least one packet buffer is पढ़ोy (or a zlp).
 */
अटल पूर्णांक
ग_लिखो_fअगरo (काष्ठा pxa25x_ep *ep, काष्ठा pxa25x_request *req)
अणु
	अचिन्हित		max;

	max = usb_endpoपूर्णांक_maxp(ep->ep.desc);
	करो अणु
		अचिन्हित	count;
		पूर्णांक		is_last, is_लघु;

		count = ग_लिखो_packet(ep, req, max);

		/* last packet is usually लघु (or a zlp) */
		अगर (unlikely (count != max))
			is_last = is_लघु = 1;
		अन्यथा अणु
			अगर (likely(req->req.length != req->req.actual)
					|| req->req.zero)
				is_last = 0;
			अन्यथा
				is_last = 1;
			/* पूर्णांकerrupt/iso maxpacket may not fill the fअगरo */
			is_लघु = unlikely (max < ep->fअगरo_size);
		पूर्ण

		DBG(DBG_VERY_NOISY, "wrote %s %d bytes%s%s %d left %p\n",
			ep->ep.name, count,
			is_last ? "/L" : "", is_लघु ? "/S" : "",
			req->req.length - req->req.actual, req);

		/* let loose that packet. maybe try writing another one,
		 * द्विगुन buffering might work.  TSP, TPC, and TFS
		 * bit values are the same क्रम all normal IN endpoपूर्णांकs.
		 */
		udc_ep_set_UDCCS(ep, UDCCS_BI_TPC);
		अगर (is_लघु)
			udc_ep_set_UDCCS(ep, UDCCS_BI_TSP);

		/* requests complete when all IN data is in the FIFO */
		अगर (is_last) अणु
			करोne (ep, req, 0);
			अगर (list_empty(&ep->queue))
				pio_irq_disable(ep);
			वापस 1;
		पूर्ण

		// TODO experiment: how robust can fअगरo mode tweaking be?
		// द्विगुन buffering is off in the शेष fअगरo mode, which
		// prevents TFS from being set here.

	पूर्ण जबतक (udc_ep_get_UDCCS(ep) & UDCCS_BI_TFS);
	वापस 0;
पूर्ण

/* caller निश्चितs req->pending (ep0 irq status nyet cleared); starts
 * ep0 data stage.  these chips want very simple state transitions.
 */
अटल अंतरभूत
व्योम ep0start(काष्ठा pxa25x_udc *dev, u32 flags, स्थिर अक्षर *tag)
अणु
	udc_ep0_set_UDCCS(dev, flags|UDCCS0_SA|UDCCS0_OPR);
	udc_set_reg(dev, USIR0, USIR0_IR0);
	dev->req_pending = 0;
	DBG(DBG_VERY_NOISY, "%s %s, %02x/%02x\n",
		__func__, tag, udc_ep0_get_UDCCS(dev), flags);
पूर्ण

अटल पूर्णांक
ग_लिखो_ep0_fअगरo (काष्ठा pxa25x_ep *ep, काष्ठा pxa25x_request *req)
अणु
	काष्ठा pxa25x_udc *dev = ep->dev;
	अचिन्हित	count;
	पूर्णांक		is_लघु;

	count = ग_लिखो_packet(&dev->ep[0], req, EP0_FIFO_SIZE);
	ep->dev->stats.ग_लिखो.bytes += count;

	/* last packet "must be" लघु (or a zlp) */
	is_लघु = (count != EP0_FIFO_SIZE);

	DBG(DBG_VERY_NOISY, "ep0in %d bytes %d left %p\n", count,
		req->req.length - req->req.actual, req);

	अगर (unlikely (is_लघु)) अणु
		अगर (ep->dev->req_pending)
			ep0start(ep->dev, UDCCS0_IPR, "short IN");
		अन्यथा
			udc_ep0_set_UDCCS(dev, UDCCS0_IPR);

		count = req->req.length;
		करोne (ep, req, 0);
		ep0_idle(ep->dev);
#अगर_अघोषित CONFIG_ARCH_IXP4XX
#अगर 1
		/* This seems to get rid of lost status irqs in some हालs:
		 * host responds quickly, or next request involves config
		 * change स्वतःmagic, or should have been hidden, or ...
		 *
		 * FIXME get rid of all udelays possible...
		 */
		अगर (count >= EP0_FIFO_SIZE) अणु
			count = 100;
			करो अणु
				अगर ((udc_ep0_get_UDCCS(dev) & UDCCS0_OPR) != 0) अणु
					/* clear OPR, generate ack */
					udc_ep0_set_UDCCS(dev, UDCCS0_OPR);
					अवरोध;
				पूर्ण
				count--;
				udelay(1);
			पूर्ण जबतक (count);
		पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (ep->dev->req_pending)
		ep0start(ep->dev, 0, "IN");
	वापस is_लघु;
पूर्ण


/*
 * पढ़ो_fअगरo -  unload packet(s) from the fअगरo we use क्रम usb OUT
 * transfers and put them पूर्णांकo the request.  caller should have made
 * sure there's at least one packet पढ़ोy.
 *
 * वापसs true अगर the request completed because of लघु packet or the
 * request buffer having filled (and maybe overran till end-of-packet).
 */
अटल पूर्णांक
पढ़ो_fअगरo (काष्ठा pxa25x_ep *ep, काष्ठा pxa25x_request *req)
अणु
	क्रम (;;) अणु
		u32		udccs;
		u8		*buf;
		अचिन्हित	bufferspace, count, is_लघु;

		/* make sure there's a packet in the FIFO.
		 * UDCCS_अणुBO,IOपूर्ण_RPC are all the same bit value.
		 * UDCCS_अणुBO,IOपूर्ण_RNE are all the same bit value.
		 */
		udccs = udc_ep_get_UDCCS(ep);
		अगर (unlikely ((udccs & UDCCS_BO_RPC) == 0))
			अवरोध;
		buf = req->req.buf + req->req.actual;
		prefetchw(buf);
		bufferspace = req->req.length - req->req.actual;

		/* पढ़ो all bytes from this packet */
		अगर (likely (udccs & UDCCS_BO_RNE)) अणु
			count = 1 + (0x0ff & udc_ep_get_UBCR(ep));
			req->req.actual += min (count, bufferspace);
		पूर्ण अन्यथा /* zlp */
			count = 0;
		is_लघु = (count < ep->ep.maxpacket);
		DBG(DBG_VERY_NOISY, "read %s %02x, %d bytes%s req %p %d/%d\n",
			ep->ep.name, udccs, count,
			is_लघु ? "/S" : "",
			req, req->req.actual, req->req.length);
		जबतक (likely (count-- != 0)) अणु
			u8	byte = (u8) udc_ep_get_UDDR(ep);

			अगर (unlikely (bufferspace == 0)) अणु
				/* this happens when the driver's buffer
				 * is smaller than what the host sent.
				 * discard the extra data.
				 */
				अगर (req->req.status != -EOVERFLOW)
					DMSG("%s overflow %d\n",
						ep->ep.name, count);
				req->req.status = -EOVERFLOW;
			पूर्ण अन्यथा अणु
				*buf++ = byte;
				bufferspace--;
			पूर्ण
		पूर्ण
		udc_ep_set_UDCCS(ep, UDCCS_BO_RPC);
		/* RPC/RSP/RNE could now reflect the other packet buffer */

		/* iso is one request per packet */
		अगर (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC) अणु
			अगर (udccs & UDCCS_IO_ROF)
				req->req.status = -EHOSTUNREACH;
			/* more like "is_done" */
			is_लघु = 1;
		पूर्ण

		/* completion */
		अगर (is_लघु || req->req.actual == req->req.length) अणु
			करोne (ep, req, 0);
			अगर (list_empty(&ep->queue))
				pio_irq_disable(ep);
			वापस 1;
		पूर्ण

		/* finished that packet.  the next one may be रुकोing... */
	पूर्ण
	वापस 0;
पूर्ण

/*
 * special ep0 version of the above.  no UBCR0 or द्विगुन buffering; status
 * handshaking is magic.  most device protocols करोn't need control-OUT.
 * CDC venकरोr commands (and RNDIS), mass storage CB/CBI, and some other
 * protocols करो use them.
 */
अटल पूर्णांक
पढ़ो_ep0_fअगरo (काष्ठा pxa25x_ep *ep, काष्ठा pxa25x_request *req)
अणु
	u8		*buf, byte;
	अचिन्हित	bufferspace;

	buf = req->req.buf + req->req.actual;
	bufferspace = req->req.length - req->req.actual;

	जबतक (udc_ep_get_UDCCS(ep) & UDCCS0_RNE) अणु
		byte = (u8) UDDR0;

		अगर (unlikely (bufferspace == 0)) अणु
			/* this happens when the driver's buffer
			 * is smaller than what the host sent.
			 * discard the extra data.
			 */
			अगर (req->req.status != -EOVERFLOW)
				DMSG("%s overflow\n", ep->ep.name);
			req->req.status = -EOVERFLOW;
		पूर्ण अन्यथा अणु
			*buf++ = byte;
			req->req.actual++;
			bufferspace--;
		पूर्ण
	पूर्ण

	udc_ep_set_UDCCS(ep, UDCCS0_OPR | UDCCS0_IPR);

	/* completion */
	अगर (req->req.actual >= req->req.length)
		वापस 1;

	/* finished that packet.  the next one may be रुकोing... */
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
pxa25x_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा pxa25x_request	*req;
	काष्ठा pxa25x_ep	*ep;
	काष्ठा pxa25x_udc	*dev;
	अचिन्हित दीर्घ		flags;

	req = container_of(_req, काष्ठा pxa25x_request, req);
	अगर (unlikely (!_req || !_req->complete || !_req->buf
			|| !list_empty(&req->queue))) अणु
		DMSG("%s, bad params\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ep = container_of(_ep, काष्ठा pxa25x_ep, ep);
	अगर (unlikely(!_ep || (!ep->ep.desc && ep->ep.name != ep0name))) अणु
		DMSG("%s, bad ep\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dev = ep->dev;
	अगर (unlikely (!dev->driver
			|| dev->gadget.speed == USB_SPEED_UNKNOWN)) अणु
		DMSG("%s, bogus device state\n", __func__);
		वापस -ESHUTDOWN;
	पूर्ण

	/* iso is always one packet per request, that's the only way
	 * we can report per-packet status.  that also helps with dma.
	 */
	अगर (unlikely (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC
			&& req->req.length > usb_endpoपूर्णांक_maxp(ep->ep.desc)))
		वापस -EMSGSIZE;

	DBG(DBG_NOISY, "%s queue req %p, len %d buf %p\n",
		_ep->name, _req, _req->length, _req->buf);

	local_irq_save(flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	/* kickstart this i/o queue? */
	अगर (list_empty(&ep->queue) && !ep->stopped) अणु
		अगर (ep->ep.desc == शून्य/* ep0 */) अणु
			अचिन्हित	length = _req->length;

			चयन (dev->ep0state) अणु
			हाल EP0_IN_DATA_PHASE:
				dev->stats.ग_लिखो.ops++;
				अगर (ग_लिखो_ep0_fअगरo(ep, req))
					req = शून्य;
				अवरोध;

			हाल EP0_OUT_DATA_PHASE:
				dev->stats.पढ़ो.ops++;
				/* messy ... */
				अगर (dev->req_config) अणु
					DBG(DBG_VERBOSE, "ep0 config ack%s\n",
						dev->has_cfr ?  "" : " raced");
					अगर (dev->has_cfr)
						udc_set_reg(dev, UDCCFR, UDCCFR_AREN |
							    UDCCFR_ACM | UDCCFR_MB1);
					करोne(ep, req, 0);
					dev->ep0state = EP0_END_XFER;
					local_irq_restore (flags);
					वापस 0;
				पूर्ण
				अगर (dev->req_pending)
					ep0start(dev, UDCCS0_IPR, "OUT");
				अगर (length == 0 || ((udc_ep0_get_UDCCS(dev) & UDCCS0_RNE) != 0
						&& पढ़ो_ep0_fअगरo(ep, req))) अणु
					ep0_idle(dev);
					करोne(ep, req, 0);
					req = शून्य;
				पूर्ण
				अवरोध;

			शेष:
				DMSG("ep0 i/o, odd state %d\n", dev->ep0state);
				local_irq_restore (flags);
				वापस -EL2HLT;
			पूर्ण
		/* can the FIFO can satisfy the request immediately? */
		पूर्ण अन्यथा अगर ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN) != 0) अणु
			अगर ((udc_ep_get_UDCCS(ep) & UDCCS_BI_TFS) != 0
					&& ग_लिखो_fअगरo(ep, req))
				req = शून्य;
		पूर्ण अन्यथा अगर ((udc_ep_get_UDCCS(ep) & UDCCS_BO_RFS) != 0
				&& पढ़ो_fअगरo(ep, req)) अणु
			req = शून्य;
		पूर्ण

		अगर (likely(req && ep->ep.desc))
			pio_irq_enable(ep);
	पूर्ण

	/* pio or dma irq handler advances the queue. */
	अगर (likely(req != शून्य))
		list_add_tail(&req->queue, &ep->queue);
	local_irq_restore(flags);

	वापस 0;
पूर्ण


/*
 *	nuke - dequeue ALL requests
 */
अटल व्योम nuke(काष्ठा pxa25x_ep *ep, पूर्णांक status)
अणु
	काष्ठा pxa25x_request *req;

	/* called with irqs blocked */
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next,
				काष्ठा pxa25x_request,
				queue);
		करोne(ep, req, status);
	पूर्ण
	अगर (ep->ep.desc)
		pio_irq_disable(ep);
पूर्ण


/* dequeue JUST ONE request */
अटल पूर्णांक pxa25x_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा pxa25x_ep	*ep;
	काष्ठा pxa25x_request	*req;
	अचिन्हित दीर्घ		flags;

	ep = container_of(_ep, काष्ठा pxa25x_ep, ep);
	अगर (!_ep || ep->ep.name == ep0name)
		वापस -EINVAL;

	local_irq_save(flags);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry (req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		local_irq_restore(flags);
		वापस -EINVAL;
	पूर्ण

	करोne(ep, req, -ECONNRESET);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक pxa25x_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा pxa25x_ep	*ep;
	अचिन्हित दीर्घ		flags;

	ep = container_of(_ep, काष्ठा pxa25x_ep, ep);
	अगर (unlikely (!_ep
			|| (!ep->ep.desc && ep->ep.name != ep0name))
			|| ep->bmAttributes == USB_ENDPOINT_XFER_ISOC) अणु
		DMSG("%s, bad ep\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (value == 0) अणु
		/* this path (reset toggle+halt) is needed to implement
		 * SET_INTERFACE on normal hardware.  but it can't be
		 * करोne from software on the PXA UDC, and the hardware
		 * क्रममाला_लो to करो it as part of SET_INTERFACE स्वतःmagic.
		 */
		DMSG("only host can clear %s halt\n", _ep->name);
		वापस -EROFS;
	पूर्ण

	local_irq_save(flags);

	अगर ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN) != 0
			&& ((udc_ep_get_UDCCS(ep) & UDCCS_BI_TFS) == 0
			   || !list_empty(&ep->queue))) अणु
		local_irq_restore(flags);
		वापस -EAGAIN;
	पूर्ण

	/* FST bit is the same क्रम control, bulk in, bulk out, पूर्णांकerrupt in */
	udc_ep_set_UDCCS(ep, UDCCS_BI_FST|UDCCS_BI_FTF);

	/* ep0 needs special care */
	अगर (!ep->ep.desc) अणु
		start_watchकरोg(ep->dev);
		ep->dev->req_pending = 0;
		ep->dev->ep0state = EP0_STALL;

	/* and bulk/पूर्णांकr endpoपूर्णांकs like dropping stalls too */
	पूर्ण अन्यथा अणु
		अचिन्हित i;
		क्रम (i = 0; i < 1000; i += 20) अणु
			अगर (udc_ep_get_UDCCS(ep) & UDCCS_BI_SST)
				अवरोध;
			udelay(20);
		पूर्ण
	पूर्ण
	local_irq_restore(flags);

	DBG(DBG_VERBOSE, "%s halt\n", _ep->name);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa25x_ep_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	काष्ठा pxa25x_ep        *ep;

	ep = container_of(_ep, काष्ठा pxa25x_ep, ep);
	अगर (!_ep) अणु
		DMSG("%s, bad ep\n", __func__);
		वापस -ENODEV;
	पूर्ण
	/* pxa can't report unclaimed bytes from IN fअगरos */
	अगर ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN) != 0)
		वापस -EOPNOTSUPP;
	अगर (ep->dev->gadget.speed == USB_SPEED_UNKNOWN
			|| (udc_ep_get_UDCCS(ep) & UDCCS_BO_RFS) == 0)
		वापस 0;
	अन्यथा
		वापस (udc_ep_get_UBCR(ep) & 0xfff) + 1;
पूर्ण

अटल व्योम pxa25x_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा pxa25x_ep        *ep;

	ep = container_of(_ep, काष्ठा pxa25x_ep, ep);
	अगर (!_ep || ep->ep.name == ep0name || !list_empty(&ep->queue)) अणु
		DMSG("%s, bad ep\n", __func__);
		वापस;
	पूर्ण

	/* toggle and halt bits stay unchanged */

	/* क्रम OUT, just पढ़ो and discard the FIFO contents. */
	अगर ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN) == 0) अणु
		जबतक (((udc_ep_get_UDCCS(ep)) & UDCCS_BO_RNE) != 0)
			(व्योम)udc_ep_get_UDDR(ep);
		वापस;
	पूर्ण

	/* most IN status is the same, but ISO can't stall */
	udc_ep_set_UDCCS(ep, UDCCS_BI_TPC|UDCCS_BI_FTF|UDCCS_BI_TUR
		| (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC
			? 0 : UDCCS_BI_SST));
पूर्ण


अटल काष्ठा usb_ep_ops pxa25x_ep_ops = अणु
	.enable		= pxa25x_ep_enable,
	.disable	= pxa25x_ep_disable,

	.alloc_request	= pxa25x_ep_alloc_request,
	.मुक्त_request	= pxa25x_ep_मुक्त_request,

	.queue		= pxa25x_ep_queue,
	.dequeue	= pxa25x_ep_dequeue,

	.set_halt	= pxa25x_ep_set_halt,
	.fअगरo_status	= pxa25x_ep_fअगरo_status,
	.fअगरo_flush	= pxa25x_ep_fअगरo_flush,
पूर्ण;


/* ---------------------------------------------------------------------------
 *	device-scoped parts of the api to the usb controller hardware
 * ---------------------------------------------------------------------------
 */

अटल पूर्णांक pxa25x_udc_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा pxa25x_udc	*dev;

	dev = container_of(_gadget, काष्ठा pxa25x_udc, gadget);
	वापस ((udc_get_reg(dev, UFNRH) & 0x07) << 8) |
		(udc_get_reg(dev, UFNRL) & 0xff);
पूर्ण

अटल पूर्णांक pxa25x_udc_wakeup(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा pxa25x_udc	*udc;

	udc = container_of(_gadget, काष्ठा pxa25x_udc, gadget);

	/* host may not have enabled remote wakeup */
	अगर ((udc_ep0_get_UDCCS(udc) & UDCCS0_DRWF) == 0)
		वापस -EHOSTUNREACH;
	udc_set_mask_UDCCR(udc, UDCCR_RSM);
	वापस 0;
पूर्ण

अटल व्योम stop_activity(काष्ठा pxa25x_udc *, काष्ठा usb_gadget_driver *);
अटल व्योम udc_enable (काष्ठा pxa25x_udc *);
अटल व्योम udc_disable(काष्ठा pxa25x_udc *);

/* We disable the UDC -- and its 48 MHz घड़ी -- whenever it's not
 * in active use.
 */
अटल पूर्णांक pullup(काष्ठा pxa25x_udc *udc)
अणु
	पूर्णांक is_active = udc->vbus && udc->pullup && !udc->suspended;
	DMSG("%s\n", is_active ? "active" : "inactive");
	अगर (is_active) अणु
		अगर (!udc->active) अणु
			udc->active = 1;
			/* Enable घड़ी क्रम USB device */
			clk_enable(udc->clk);
			udc_enable(udc);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (udc->active) अणु
			अगर (udc->gadget.speed != USB_SPEED_UNKNOWN) अणु
				DMSG("disconnect %s\n", udc->driver
					? udc->driver->driver.name
					: "(no driver)");
				stop_activity(udc, udc->driver);
			पूर्ण
			udc_disable(udc);
			/* Disable घड़ी क्रम USB device */
			clk_disable(udc->clk);
			udc->active = 0;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

/* VBUS reporting logically comes from a transceiver */
अटल पूर्णांक pxa25x_udc_vbus_session(काष्ठा usb_gadget *_gadget, पूर्णांक is_active)
अणु
	काष्ठा pxa25x_udc	*udc;

	udc = container_of(_gadget, काष्ठा pxa25x_udc, gadget);
	udc->vbus = is_active;
	DMSG("vbus %s\n", is_active ? "supplied" : "inactive");
	pullup(udc);
	वापस 0;
पूर्ण

/* drivers may have software control over D+ pullup */
अटल पूर्णांक pxa25x_udc_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक is_active)
अणु
	काष्ठा pxa25x_udc	*udc;

	udc = container_of(_gadget, काष्ठा pxa25x_udc, gadget);

	/* not all boards support pullup control */
	अगर (!gpio_is_valid(udc->mach->gpio_pullup) && !udc->mach->udc_command)
		वापस -EOPNOTSUPP;

	udc->pullup = (is_active != 0);
	pullup(udc);
	वापस 0;
पूर्ण

/* boards may consume current from VBUS, up to 100-500mA based on config.
 * the 500uA suspend उच्चमानing means that exclusively vbus-घातered PXA designs
 * violate USB specs.
 */
अटल पूर्णांक pxa25x_udc_vbus_draw(काष्ठा usb_gadget *_gadget, अचिन्हित mA)
अणु
	काष्ठा pxa25x_udc	*udc;

	udc = container_of(_gadget, काष्ठा pxa25x_udc, gadget);

	अगर (!IS_ERR_OR_शून्य(udc->transceiver))
		वापस usb_phy_set_घातer(udc->transceiver, mA);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक pxa25x_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक pxa25x_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops pxa25x_udc_ops = अणु
	.get_frame	= pxa25x_udc_get_frame,
	.wakeup		= pxa25x_udc_wakeup,
	.vbus_session	= pxa25x_udc_vbus_session,
	.pullup		= pxa25x_udc_pullup,
	.vbus_draw	= pxa25x_udc_vbus_draw,
	.udc_start	= pxa25x_udc_start,
	.udc_stop	= pxa25x_udc_stop,
पूर्ण;

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS

अटल पूर्णांक udc_debug_show(काष्ठा seq_file *m, व्योम *_d)
अणु
	काष्ठा pxa25x_udc	*dev = m->निजी;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			i;
	u32			पंचांगp;

	local_irq_save(flags);

	/* basic device status */
	seq_म_लिखो(m, DRIVER_DESC "\n"
		"%s version: %s\nGadget driver: %s\nHost %s\n\n",
		driver_name, DRIVER_VERSION SIZE_STR "(pio)",
		dev->driver ? dev->driver->driver.name : "(none)",
		dev->gadget.speed == USB_SPEED_FULL ? "full speed" : "disconnected");

	/* रेजिस्टरs क्रम device and ep0 */
	seq_म_लिखो(m,
		"uicr %02X.%02X, usir %02X.%02x, ufnr %02X.%02X\n",
		udc_get_reg(dev, UICR1), udc_get_reg(dev, UICR0),
		udc_get_reg(dev, USIR1), udc_get_reg(dev, USIR0),
		udc_get_reg(dev, UFNRH), udc_get_reg(dev, UFNRL));

	पंचांगp = udc_get_reg(dev, UDCCR);
	seq_म_लिखो(m,
		"udccr %02X =%s%s%s%s%s%s%s%s\n", पंचांगp,
		(पंचांगp & UDCCR_REM) ? " rem" : "",
		(पंचांगp & UDCCR_RSTIR) ? " rstir" : "",
		(पंचांगp & UDCCR_SRM) ? " srm" : "",
		(पंचांगp & UDCCR_SUSIR) ? " susir" : "",
		(पंचांगp & UDCCR_RESIR) ? " resir" : "",
		(पंचांगp & UDCCR_RSM) ? " rsm" : "",
		(पंचांगp & UDCCR_UDA) ? " uda" : "",
		(पंचांगp & UDCCR_UDE) ? " ude" : "");

	पंचांगp = udc_ep0_get_UDCCS(dev);
	seq_म_लिखो(m,
		"udccs0 %02X =%s%s%s%s%s%s%s%s\n", पंचांगp,
		(पंचांगp & UDCCS0_SA) ? " sa" : "",
		(पंचांगp & UDCCS0_RNE) ? " rne" : "",
		(पंचांगp & UDCCS0_FST) ? " fst" : "",
		(पंचांगp & UDCCS0_SST) ? " sst" : "",
		(पंचांगp & UDCCS0_DRWF) ? " dwrf" : "",
		(पंचांगp & UDCCS0_FTF) ? " ftf" : "",
		(पंचांगp & UDCCS0_IPR) ? " ipr" : "",
		(पंचांगp & UDCCS0_OPR) ? " opr" : "");

	अगर (dev->has_cfr) अणु
		पंचांगp = udc_get_reg(dev, UDCCFR);
		seq_म_लिखो(m,
			"udccfr %02X =%s%s\n", पंचांगp,
			(पंचांगp & UDCCFR_AREN) ? " aren" : "",
			(पंचांगp & UDCCFR_ACM) ? " acm" : "");
	पूर्ण

	अगर (dev->gadget.speed != USB_SPEED_FULL || !dev->driver)
		जाओ करोne;

	seq_म_लिखो(m, "ep0 IN %lu/%lu, OUT %lu/%lu\nirqs %lu\n\n",
		dev->stats.ग_लिखो.bytes, dev->stats.ग_लिखो.ops,
		dev->stats.पढ़ो.bytes, dev->stats.पढ़ो.ops,
		dev->stats.irqs);

	/* dump endpoपूर्णांक queues */
	क्रम (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) अणु
		काष्ठा pxa25x_ep	*ep = &dev->ep [i];
		काष्ठा pxa25x_request	*req;

		अगर (i != 0) अणु
			स्थिर काष्ठा usb_endpoपूर्णांक_descriptor	*desc;

			desc = ep->ep.desc;
			अगर (!desc)
				जारी;
			पंचांगp = udc_ep_get_UDCCS(&dev->ep[i]);
			seq_म_लिखो(m,
				"%s max %d %s udccs %02x irqs %lu\n",
				ep->ep.name, usb_endpoपूर्णांक_maxp(desc),
				"pio", पंचांगp, ep->pio_irqs);
			/* TODO translate all five groups of udccs bits! */

		पूर्ण अन्यथा /* ep0 should only have one transfer queued */
			seq_म_लिखो(m, "ep0 max 16 pio irqs %lu\n",
				ep->pio_irqs);

		अगर (list_empty(&ep->queue)) अणु
			seq_म_लिखो(m, "\t(nothing queued)\n");
			जारी;
		पूर्ण
		list_क्रम_each_entry(req, &ep->queue, queue) अणु
			seq_म_लिखो(m,
					"\treq %p len %d/%d buf %p\n",
					&req->req, req->req.actual,
					req->req.length, req->req.buf);
		पूर्ण
	पूर्ण

करोne:
	local_irq_restore(flags);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(udc_debug);

#घोषणा create_debug_files(dev) \
	करो अणु \
		dev->debugfs_udc = debugfs_create_file(dev->gadget.name, \
			S_IRUGO, शून्य, dev, &udc_debug_fops); \
	पूर्ण जबतक (0)
#घोषणा हटाओ_debug_files(dev) debugfs_हटाओ(dev->debugfs_udc)

#अन्यथा	/* !CONFIG_USB_GADGET_DEBUG_खाताS */

#घोषणा create_debug_files(dev) करो अणुपूर्ण जबतक (0)
#घोषणा हटाओ_debug_files(dev) करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर	/* CONFIG_USB_GADGET_DEBUG_खाताS */

/*-------------------------------------------------------------------------*/

/*
 *	udc_disable - disable USB device controller
 */
अटल व्योम udc_disable(काष्ठा pxa25x_udc *dev)
अणु
	/* block all irqs */
	udc_set_mask_UDCCR(dev, UDCCR_SRM|UDCCR_REM);
	udc_set_reg(dev, UICR0, 0xff);
	udc_set_reg(dev, UICR1, 0xff);
	udc_set_reg(dev, UFNRH, UFNRH_SIM);

	/* अगर hardware supports it, disconnect from usb */
	pullup_off();

	udc_clear_mask_UDCCR(dev, UDCCR_UDE);

	ep0_idle (dev);
	dev->gadget.speed = USB_SPEED_UNKNOWN;
पूर्ण


/*
 *	udc_reinit - initialize software state
 */
अटल व्योम udc_reinit(काष्ठा pxa25x_udc *dev)
अणु
	u32	i;

	/* device/ep0 records init */
	INIT_LIST_HEAD (&dev->gadget.ep_list);
	INIT_LIST_HEAD (&dev->gadget.ep0->ep_list);
	dev->ep0state = EP0_IDLE;
	dev->gadget.quirk_altset_not_supp = 1;

	/* basic endpoपूर्णांक records init */
	क्रम (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) अणु
		काष्ठा pxa25x_ep *ep = &dev->ep[i];

		अगर (i != 0)
			list_add_tail (&ep->ep.ep_list, &dev->gadget.ep_list);

		ep->ep.desc = शून्य;
		ep->stopped = 0;
		INIT_LIST_HEAD (&ep->queue);
		ep->pio_irqs = 0;
		usb_ep_set_maxpacket_limit(&ep->ep, ep->ep.maxpacket);
	पूर्ण

	/* the rest was अटलally initialized, and is पढ़ो-only */
पूर्ण

/* until it's enabled, this UDC should be completely invisible
 * to any USB host.
 */
अटल व्योम udc_enable (काष्ठा pxa25x_udc *dev)
अणु
	udc_clear_mask_UDCCR(dev, UDCCR_UDE);

	/* try to clear these bits beक्रमe we enable the udc */
	udc_ack_पूर्णांक_UDCCR(dev, UDCCR_SUSIR|/*UDCCR_RSTIR|*/UDCCR_RESIR);

	ep0_idle(dev);
	dev->gadget.speed = USB_SPEED_UNKNOWN;
	dev->stats.irqs = 0;

	/*
	 * sequence taken from chapter 12.5.10, PXA250 AppProcDevManual:
	 * - enable UDC
	 * - अगर RESET is alपढ़ोy in progress, ack पूर्णांकerrupt
	 * - unmask reset पूर्णांकerrupt
	 */
	udc_set_mask_UDCCR(dev, UDCCR_UDE);
	अगर (!(udc_get_reg(dev, UDCCR) & UDCCR_UDA))
		udc_ack_पूर्णांक_UDCCR(dev, UDCCR_RSTIR);

	अगर (dev->has_cfr /* UDC_RES2 is defined */) अणु
		/* pxa255 (a0+) can aव्योम a set_config race that could
		 * prevent gadget drivers from configuring correctly
		 */
		udc_set_reg(dev, UDCCFR, UDCCFR_ACM | UDCCFR_MB1);
	पूर्ण अन्यथा अणु
		/* "USB test mode" क्रम pxa250 errata 40-42 (stepping a0, a1)
		 * which could result in missing packets and पूर्णांकerrupts.
		 * supposedly one bit per endpoपूर्णांक, controlling whether it
		 * द्विगुन buffers or not; ACM/AREN bits fit पूर्णांकo the holes.
		 * zero bits (like USIR0_IRx) disable द्विगुन buffering.
		 */
		udc_set_reg(dev, UDC_RES1, 0x00);
		udc_set_reg(dev, UDC_RES2, 0x00);
	पूर्ण

	/* enable suspend/resume and reset irqs */
	udc_clear_mask_UDCCR(dev, UDCCR_SRM | UDCCR_REM);

	/* enable ep0 irqs */
	udc_set_reg(dev, UICR0, udc_get_reg(dev, UICR0) & ~UICR0_IM0);

	/* अगर hardware supports it, pullup D+ and रुको क्रम reset */
	pullup_on();
पूर्ण


/* when a driver is successfully रेजिस्टरed, it will receive
 * control requests including set_configuration(), which enables
 * non-control requests.  then usb traffic follows until a
 * disconnect is reported.  then a host may connect again, or
 * the driver might get unbound.
 */
अटल पूर्णांक pxa25x_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा pxa25x_udc	*dev = to_pxa25x(g);
	पूर्णांक			retval;

	/* first hook up the driver ... */
	dev->driver = driver;
	dev->pullup = 1;

	/* ... then enable host detection and ep0; and we're पढ़ोy
	 * क्रम set_configuration as well as eventual disconnect.
	 */
	/* connect to bus through transceiver */
	अगर (!IS_ERR_OR_शून्य(dev->transceiver)) अणु
		retval = otg_set_peripheral(dev->transceiver->otg,
						&dev->gadget);
		अगर (retval)
			जाओ bind_fail;
	पूर्ण

	dump_state(dev);
	वापस 0;
bind_fail:
	वापस retval;
पूर्ण

अटल व्योम
reset_gadget(काष्ठा pxa25x_udc *dev, काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक i;

	/* करोn't disconnect drivers more than once */
	अगर (dev->gadget.speed == USB_SPEED_UNKNOWN)
		driver = शून्य;
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	/* prevent new request submissions, समाप्त any outstanding requests  */
	क्रम (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) अणु
		काष्ठा pxa25x_ep *ep = &dev->ep[i];

		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	पूर्ण
	del_समयr_sync(&dev->समयr);

	/* report reset; the driver is alपढ़ोy quiesced */
	अगर (driver)
		usb_gadget_udc_reset(&dev->gadget, driver);

	/* re-init driver-visible data काष्ठाures */
	udc_reinit(dev);
पूर्ण

अटल व्योम
stop_activity(काष्ठा pxa25x_udc *dev, काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक i;

	/* करोn't disconnect drivers more than once */
	अगर (dev->gadget.speed == USB_SPEED_UNKNOWN)
		driver = शून्य;
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	/* prevent new request submissions, समाप्त any outstanding requests  */
	क्रम (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) अणु
		काष्ठा pxa25x_ep *ep = &dev->ep[i];

		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	पूर्ण
	del_समयr_sync(&dev->समयr);

	/* report disconnect; the driver is alपढ़ोy quiesced */
	अगर (driver)
		driver->disconnect(&dev->gadget);

	/* re-init driver-visible data काष्ठाures */
	udc_reinit(dev);
पूर्ण

अटल पूर्णांक pxa25x_udc_stop(काष्ठा usb_gadget*g)
अणु
	काष्ठा pxa25x_udc	*dev = to_pxa25x(g);

	local_irq_disable();
	dev->pullup = 0;
	stop_activity(dev, शून्य);
	local_irq_enable();

	अगर (!IS_ERR_OR_शून्य(dev->transceiver))
		(व्योम) otg_set_peripheral(dev->transceiver->otg, शून्य);

	dev->driver = शून्य;

	dump_state(dev);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_ARCH_LUBBOCK

/* Lubbock has separate connect and disconnect irqs.  More typical designs
 * use one GPIO as the VBUS IRQ, and another to control the D+ pullup.
 */

अटल irqवापस_t
lubbock_vbus_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा pxa25x_udc	*dev = _dev;
	पूर्णांक			vbus;

	dev->stats.irqs++;
	चयन (irq) अणु
	हाल LUBBOCK_USB_IRQ:
		vbus = 1;
		disable_irq(LUBBOCK_USB_IRQ);
		enable_irq(LUBBOCK_USB_DISC_IRQ);
		अवरोध;
	हाल LUBBOCK_USB_DISC_IRQ:
		vbus = 0;
		disable_irq(LUBBOCK_USB_DISC_IRQ);
		enable_irq(LUBBOCK_USB_IRQ);
		अवरोध;
	शेष:
		वापस IRQ_NONE;
	पूर्ण

	pxa25x_udc_vbus_session(&dev->gadget, vbus);
	वापस IRQ_HANDLED;
पूर्ण

#पूर्ण_अगर


/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम clear_ep_state (काष्ठा pxa25x_udc *dev)
अणु
	अचिन्हित i;

	/* hardware SET_अणुCONFIGURATION,INTERFACEपूर्ण स्वतःmagic resets endpoपूर्णांक
	 * fअगरos, and pending transactions mustn't be जारीd in any हाल.
	 */
	क्रम (i = 1; i < PXA_UDC_NUM_ENDPOINTS; i++)
		nuke(&dev->ep[i], -ECONNABORTED);
पूर्ण

अटल व्योम udc_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा pxa25x_udc	*dev = from_समयr(dev, t, समयr);

	local_irq_disable();
	अगर (dev->ep0state == EP0_STALL
			&& (udc_ep0_get_UDCCS(dev) & UDCCS0_FST) == 0
			&& (udc_ep0_get_UDCCS(dev) & UDCCS0_SST) == 0) अणु
		udc_ep0_set_UDCCS(dev, UDCCS0_FST|UDCCS0_FTF);
		DBG(DBG_VERBOSE, "ep0 re-stall\n");
		start_watchकरोg(dev);
	पूर्ण
	local_irq_enable();
पूर्ण

अटल व्योम handle_ep0 (काष्ठा pxa25x_udc *dev)
अणु
	u32			udccs0 = udc_ep0_get_UDCCS(dev);
	काष्ठा pxa25x_ep	*ep = &dev->ep [0];
	काष्ठा pxa25x_request	*req;
	जोड़ अणु
		काष्ठा usb_ctrlrequest	r;
		u8			raw [8];
		u32			word [2];
	पूर्ण u;

	अगर (list_empty(&ep->queue))
		req = शून्य;
	अन्यथा
		req = list_entry(ep->queue.next, काष्ठा pxa25x_request, queue);

	/* clear stall status */
	अगर (udccs0 & UDCCS0_SST) अणु
		nuke(ep, -EPIPE);
		udc_ep0_set_UDCCS(dev, UDCCS0_SST);
		del_समयr(&dev->समयr);
		ep0_idle(dev);
	पूर्ण

	/* previous request unfinished?  non-error अगरf back-to-back ... */
	अगर ((udccs0 & UDCCS0_SA) != 0 && dev->ep0state != EP0_IDLE) अणु
		nuke(ep, 0);
		del_समयr(&dev->समयr);
		ep0_idle(dev);
	पूर्ण

	चयन (dev->ep0state) अणु
	हाल EP0_IDLE:
		/* late-अवरोधing status? */
		udccs0 = udc_ep0_get_UDCCS(dev);

		/* start control request? */
		अगर (likely((udccs0 & (UDCCS0_OPR|UDCCS0_SA|UDCCS0_RNE))
				== (UDCCS0_OPR|UDCCS0_SA|UDCCS0_RNE))) अणु
			पूर्णांक i;

			nuke (ep, -EPROTO);

			/* पढ़ो SETUP packet */
			क्रम (i = 0; i < 8; i++) अणु
				अगर (unlikely(!(udc_ep0_get_UDCCS(dev) & UDCCS0_RNE))) अणु
bad_setup:
					DMSG("SETUP %d!\n", i);
					जाओ stall;
				पूर्ण
				u.raw [i] = (u8) UDDR0;
			पूर्ण
			अगर (unlikely((udc_ep0_get_UDCCS(dev) & UDCCS0_RNE) != 0))
				जाओ bad_setup;

got_setup:
			DBG(DBG_VERBOSE, "SETUP %02x.%02x v%04x i%04x l%04x\n",
				u.r.bRequestType, u.r.bRequest,
				le16_to_cpu(u.r.wValue),
				le16_to_cpu(u.r.wIndex),
				le16_to_cpu(u.r.wLength));

			/* cope with स्वतःmagic क्रम some standard requests. */
			dev->req_std = (u.r.bRequestType & USB_TYPE_MASK)
						== USB_TYPE_STANDARD;
			dev->req_config = 0;
			dev->req_pending = 1;
			चयन (u.r.bRequest) अणु
			/* hardware restricts gadget drivers here! */
			हाल USB_REQ_SET_CONFIGURATION:
				अगर (u.r.bRequestType == USB_RECIP_DEVICE) अणु
					/* reflect hardware's स्वतःmagic
					 * up to the gadget driver.
					 */
config_change:
					dev->req_config = 1;
					clear_ep_state(dev);
					/* अगर !has_cfr, there's no synch
					 * अन्यथा use AREN (later) not SA|OPR
					 * USIR0_IR0 acts edge sensitive
					 */
				पूर्ण
				अवरोध;
			/* ... and here, even more ... */
			हाल USB_REQ_SET_INTERFACE:
				अगर (u.r.bRequestType == USB_RECIP_INTERFACE) अणु
					/* udc hardware is broken by design:
					 *  - altsetting may only be zero;
					 *  - hw resets all पूर्णांकerfaces' eps;
					 *  - ep reset करोesn't include halt(?).
					 */
					DMSG("broken set_interface (%d/%d)\n",
						le16_to_cpu(u.r.wIndex),
						le16_to_cpu(u.r.wValue));
					जाओ config_change;
				पूर्ण
				अवरोध;
			/* hardware was supposed to hide this */
			हाल USB_REQ_SET_ADDRESS:
				अगर (u.r.bRequestType == USB_RECIP_DEVICE) अणु
					ep0start(dev, 0, "address");
					वापस;
				पूर्ण
				अवरोध;
			पूर्ण

			अगर (u.r.bRequestType & USB_सूची_IN)
				dev->ep0state = EP0_IN_DATA_PHASE;
			अन्यथा
				dev->ep0state = EP0_OUT_DATA_PHASE;

			i = dev->driver->setup(&dev->gadget, &u.r);
			अगर (i < 0) अणु
				/* hardware स्वतःmagic preventing STALL... */
				अगर (dev->req_config) अणु
					/* hardware someबार neglects to tell
					 * tell us about config change events,
					 * so later ones may fail...
					 */
					WARNING("config change %02x fail %d?\n",
						u.r.bRequest, i);
					वापस;
					/* TODO experiment:  अगर has_cfr,
					 * hardware didn't ACK; maybe we
					 * could actually STALL!
					 */
				पूर्ण
				DBG(DBG_VERBOSE, "protocol STALL, "
					"%02x err %d\n", udc_ep0_get_UDCCS(dev), i);
stall:
				/* the watchकरोg समयr helps deal with हालs
				 * where udc seems to clear FST wrongly, and
				 * then NAKs instead of STALLing.
				 */
				ep0start(dev, UDCCS0_FST|UDCCS0_FTF, "stall");
				start_watchकरोg(dev);
				dev->ep0state = EP0_STALL;

			/* deferred i/o == no response yet */
			पूर्ण अन्यथा अगर (dev->req_pending) अणु
				अगर (likely(dev->ep0state == EP0_IN_DATA_PHASE
						|| dev->req_std || u.r.wLength))
					ep0start(dev, 0, "defer");
				अन्यथा
					ep0start(dev, UDCCS0_IPR, "defer/IPR");
			पूर्ण

			/* expect at least one data or status stage irq */
			वापस;

		पूर्ण अन्यथा अगर (likely((udccs0 & (UDCCS0_OPR|UDCCS0_SA))
				== (UDCCS0_OPR|UDCCS0_SA))) अणु
			अचिन्हित i;

			/* pxa210/250 erratum 131 क्रम B0/B1 says RNE lies.
			 * still observed on a pxa255 a0.
			 */
			DBG(DBG_VERBOSE, "e131\n");
			nuke(ep, -EPROTO);

			/* पढ़ो SETUP data, but करोn't trust it too much */
			क्रम (i = 0; i < 8; i++)
				u.raw [i] = (u8) UDDR0;
			अगर ((u.r.bRequestType & USB_RECIP_MASK)
					> USB_RECIP_OTHER)
				जाओ stall;
			अगर (u.word [0] == 0 && u.word [1] == 0)
				जाओ stall;
			जाओ got_setup;
		पूर्ण अन्यथा अणु
			/* some अक्रमom early IRQ:
			 * - we acked FST
			 * - IPR cleared
			 * - OPR got set, without SA (likely status stage)
			 */
			udc_ep0_set_UDCCS(dev, udccs0 & (UDCCS0_SA|UDCCS0_OPR));
		पूर्ण
		अवरोध;
	हाल EP0_IN_DATA_PHASE:			/* GET_DESCRIPTOR etc */
		अगर (udccs0 & UDCCS0_OPR) अणु
			udc_ep0_set_UDCCS(dev, UDCCS0_OPR|UDCCS0_FTF);
			DBG(DBG_VERBOSE, "ep0in premature status\n");
			अगर (req)
				करोne(ep, req, 0);
			ep0_idle(dev);
		पूर्ण अन्यथा /* irq was IPR clearing */ अणु
			अगर (req) अणु
				/* this IN packet might finish the request */
				(व्योम) ग_लिखो_ep0_fअगरo(ep, req);
			पूर्ण /* अन्यथा IN token beक्रमe response was written */
		पूर्ण
		अवरोध;
	हाल EP0_OUT_DATA_PHASE:		/* SET_DESCRIPTOR etc */
		अगर (udccs0 & UDCCS0_OPR) अणु
			अगर (req) अणु
				/* this OUT packet might finish the request */
				अगर (पढ़ो_ep0_fअगरo(ep, req))
					करोne(ep, req, 0);
				/* अन्यथा more OUT packets expected */
			पूर्ण /* अन्यथा OUT token beक्रमe पढ़ो was issued */
		पूर्ण अन्यथा /* irq was IPR clearing */ अणु
			DBG(DBG_VERBOSE, "ep0out premature status\n");
			अगर (req)
				करोne(ep, req, 0);
			ep0_idle(dev);
		पूर्ण
		अवरोध;
	हाल EP0_END_XFER:
		अगर (req)
			करोne(ep, req, 0);
		/* ack control-IN status (maybe in-zlp was skipped)
		 * also appears after some config change events.
		 */
		अगर (udccs0 & UDCCS0_OPR)
			udc_ep0_set_UDCCS(dev, UDCCS0_OPR);
		ep0_idle(dev);
		अवरोध;
	हाल EP0_STALL:
		udc_ep0_set_UDCCS(dev, UDCCS0_FST);
		अवरोध;
	पूर्ण
	udc_set_reg(dev, USIR0, USIR0_IR0);
पूर्ण

अटल व्योम handle_ep(काष्ठा pxa25x_ep *ep)
अणु
	काष्ठा pxa25x_request	*req;
	पूर्णांक			is_in = ep->bEndpoपूर्णांकAddress & USB_सूची_IN;
	पूर्णांक			completed;
	u32			udccs, पंचांगp;

	करो अणु
		completed = 0;
		अगर (likely (!list_empty(&ep->queue)))
			req = list_entry(ep->queue.next,
					काष्ठा pxa25x_request, queue);
		अन्यथा
			req = शून्य;

		// TODO check FST handling

		udccs = udc_ep_get_UDCCS(ep);
		अगर (unlikely(is_in)) अणु	/* irq from TPC, SST, or (ISO) TUR */
			पंचांगp = UDCCS_BI_TUR;
			अगर (likely(ep->bmAttributes == USB_ENDPOINT_XFER_BULK))
				पंचांगp |= UDCCS_BI_SST;
			पंचांगp &= udccs;
			अगर (likely (पंचांगp))
				udc_ep_set_UDCCS(ep, पंचांगp);
			अगर (req && likely ((udccs & UDCCS_BI_TFS) != 0))
				completed = ग_लिखो_fअगरo(ep, req);

		पूर्ण अन्यथा अणु	/* irq from RPC (or क्रम ISO, ROF) */
			अगर (likely(ep->bmAttributes == USB_ENDPOINT_XFER_BULK))
				पंचांगp = UDCCS_BO_SST | UDCCS_BO_DME;
			अन्यथा
				पंचांगp = UDCCS_IO_ROF | UDCCS_IO_DME;
			पंचांगp &= udccs;
			अगर (likely(पंचांगp))
				udc_ep_set_UDCCS(ep, पंचांगp);

			/* fअगरos can hold packets, पढ़ोy क्रम पढ़ोing... */
			अगर (likely(req)) अणु
				completed = पढ़ो_fअगरo(ep, req);
			पूर्ण अन्यथा
				pio_irq_disable(ep);
		पूर्ण
		ep->pio_irqs++;
	पूर्ण जबतक (completed);
पूर्ण

/*
 *	pxa25x_udc_irq - पूर्णांकerrupt handler
 *
 * aव्योम delays in ep0 processing. the control handshaking isn't always
 * under software control (pxa250c0 and the pxa255 are better), and delays
 * could cause usb protocol errors.
 */
अटल irqवापस_t
pxa25x_udc_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा pxa25x_udc	*dev = _dev;
	पूर्णांक			handled;

	dev->stats.irqs++;
	करो अणु
		u32		udccr = udc_get_reg(dev, UDCCR);

		handled = 0;

		/* SUSpend Interrupt Request */
		अगर (unlikely(udccr & UDCCR_SUSIR)) अणु
			udc_ack_पूर्णांक_UDCCR(dev, UDCCR_SUSIR);
			handled = 1;
			DBG(DBG_VERBOSE, "USB suspend\n");

			अगर (dev->gadget.speed != USB_SPEED_UNKNOWN
					&& dev->driver
					&& dev->driver->suspend)
				dev->driver->suspend(&dev->gadget);
			ep0_idle (dev);
		पूर्ण

		/* RESume Interrupt Request */
		अगर (unlikely(udccr & UDCCR_RESIR)) अणु
			udc_ack_पूर्णांक_UDCCR(dev, UDCCR_RESIR);
			handled = 1;
			DBG(DBG_VERBOSE, "USB resume\n");

			अगर (dev->gadget.speed != USB_SPEED_UNKNOWN
					&& dev->driver
					&& dev->driver->resume)
				dev->driver->resume(&dev->gadget);
		पूर्ण

		/* ReSeT Interrupt Request - USB reset */
		अगर (unlikely(udccr & UDCCR_RSTIR)) अणु
			udc_ack_पूर्णांक_UDCCR(dev, UDCCR_RSTIR);
			handled = 1;

			अगर ((udc_get_reg(dev, UDCCR) & UDCCR_UDA) == 0) अणु
				DBG(DBG_VERBOSE, "USB reset start\n");

				/* reset driver and endpoपूर्णांकs,
				 * in हाल that's not yet करोne
				 */
				reset_gadget(dev, dev->driver);

			पूर्ण अन्यथा अणु
				DBG(DBG_VERBOSE, "USB reset end\n");
				dev->gadget.speed = USB_SPEED_FULL;
				स_रखो(&dev->stats, 0, माप dev->stats);
				/* driver and endpoपूर्णांकs are still reset */
			पूर्ण

		पूर्ण अन्यथा अणु
			u32	usir0 = udc_get_reg(dev, USIR0) &
					~udc_get_reg(dev, UICR0);
			u32	usir1 = udc_get_reg(dev, USIR1) &
					~udc_get_reg(dev, UICR1);
			पूर्णांक	i;

			अगर (unlikely (!usir0 && !usir1))
				जारी;

			DBG(DBG_VERY_NOISY, "irq %02x.%02x\n", usir1, usir0);

			/* control traffic */
			अगर (usir0 & USIR0_IR0) अणु
				dev->ep[0].pio_irqs++;
				handle_ep0(dev);
				handled = 1;
			पूर्ण

			/* endpoपूर्णांक data transfers */
			क्रम (i = 0; i < 8; i++) अणु
				u32	पंचांगp = 1 << i;

				अगर (i && (usir0 & पंचांगp)) अणु
					handle_ep(&dev->ep[i]);
					udc_set_reg(dev, USIR0,
						udc_get_reg(dev, USIR0) | पंचांगp);
					handled = 1;
				पूर्ण
#अगर_अघोषित	CONFIG_USB_PXA25X_SMALL
				अगर (usir1 & पंचांगp) अणु
					handle_ep(&dev->ep[i+8]);
					udc_set_reg(dev, USIR1,
						udc_get_reg(dev, USIR1) | पंचांगp);
					handled = 1;
				पूर्ण
#पूर्ण_अगर
			पूर्ण
		पूर्ण

		/* we could also ask क्रम 1 msec SOF (SIR) पूर्णांकerrupts */

	पूर्ण जबतक (handled);
	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम nop_release (काष्ठा device *dev)
अणु
	DMSG("%s %s\n", __func__, dev_name(dev));
पूर्ण

/* this uses load-समय allocation and initialization (instead of
 * करोing it at run-समय) to save code, eliminate fault paths, and
 * be more obviously correct.
 */
अटल काष्ठा pxa25x_udc memory = अणु
	.gadget = अणु
		.ops		= &pxa25x_udc_ops,
		.ep0		= &memory.ep[0].ep,
		.name		= driver_name,
		.dev = अणु
			.init_name	= "gadget",
			.release	= nop_release,
		पूर्ण,
	पूर्ण,

	/* control endpoपूर्णांक */
	.ep[0] = अणु
		.ep = अणु
			.name		= ep0name,
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= EP0_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL,
						USB_EP_CAPS_सूची_ALL),
		पूर्ण,
		.dev		= &memory,
		.regoff_udccs	= UDCCS0,
		.regoff_uddr	= UDDR0,
	पूर्ण,

	/* first group of endpoपूर्णांकs */
	.ep[1] = अणु
		.ep = अणु
			.name		= "ep1in-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_IN),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= BULK_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 1,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.regoff_udccs	= UDCCS1,
		.regoff_uddr	= UDDR1,
	पूर्ण,
	.ep[2] = अणु
		.ep = अणु
			.name		= "ep2out-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_OUT),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= BULK_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 2,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.regoff_udccs	= UDCCS2,
		.regoff_ubcr	= UBCR2,
		.regoff_uddr	= UDDR2,
	पूर्ण,
#अगर_अघोषित CONFIG_USB_PXA25X_SMALL
	.ep[3] = अणु
		.ep = अणु
			.name		= "ep3in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_सूची_IN),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= ISO_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 3,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.regoff_udccs	= UDCCS3,
		.regoff_uddr	= UDDR3,
	पूर्ण,
	.ep[4] = अणु
		.ep = अणु
			.name		= "ep4out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_सूची_OUT),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= ISO_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 4,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.regoff_udccs	= UDCCS4,
		.regoff_ubcr	= UBCR4,
		.regoff_uddr	= UDDR4,
	पूर्ण,
	.ep[5] = अणु
		.ep = अणु
			.name		= "ep5in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
			.caps		= USB_EP_CAPS(0, 0),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= INT_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 5,
		.bmAttributes	= USB_ENDPOINT_XFER_INT,
		.regoff_udccs	= UDCCS5,
		.regoff_uddr	= UDDR5,
	पूर्ण,

	/* second group of endpoपूर्णांकs */
	.ep[6] = अणु
		.ep = अणु
			.name		= "ep6in-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_IN),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= BULK_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 6,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.regoff_udccs	= UDCCS6,
		.regoff_uddr	= UDDR6,
	पूर्ण,
	.ep[7] = अणु
		.ep = अणु
			.name		= "ep7out-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_OUT),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= BULK_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 7,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.regoff_udccs	= UDCCS7,
		.regoff_ubcr	= UBCR7,
		.regoff_uddr	= UDDR7,
	पूर्ण,
	.ep[8] = अणु
		.ep = अणु
			.name		= "ep8in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_सूची_IN),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= ISO_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 8,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.regoff_udccs	= UDCCS8,
		.regoff_uddr	= UDDR8,
	पूर्ण,
	.ep[9] = अणु
		.ep = अणु
			.name		= "ep9out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_सूची_OUT),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= ISO_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 9,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.regoff_udccs	= UDCCS9,
		.regoff_ubcr	= UBCR9,
		.regoff_uddr	= UDDR9,
	पूर्ण,
	.ep[10] = अणु
		.ep = अणु
			.name		= "ep10in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
			.caps		= USB_EP_CAPS(0, 0),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= INT_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 10,
		.bmAttributes	= USB_ENDPOINT_XFER_INT,
		.regoff_udccs	= UDCCS10,
		.regoff_uddr	= UDDR10,
	पूर्ण,

	/* third group of endpoपूर्णांकs */
	.ep[11] = अणु
		.ep = अणु
			.name		= "ep11in-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_IN),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= BULK_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 11,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.regoff_udccs	= UDCCS11,
		.regoff_uddr	= UDDR11,
	पूर्ण,
	.ep[12] = अणु
		.ep = अणु
			.name		= "ep12out-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK,
						USB_EP_CAPS_सूची_OUT),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= BULK_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 12,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.regoff_udccs	= UDCCS12,
		.regoff_ubcr	= UBCR12,
		.regoff_uddr	= UDDR12,
	पूर्ण,
	.ep[13] = अणु
		.ep = अणु
			.name		= "ep13in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_सूची_IN),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= ISO_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 13,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.regoff_udccs	= UDCCS13,
		.regoff_uddr	= UDDR13,
	पूर्ण,
	.ep[14] = अणु
		.ep = अणु
			.name		= "ep14out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_सूची_OUT),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= ISO_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = 14,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.regoff_udccs	= UDCCS14,
		.regoff_ubcr	= UBCR14,
		.regoff_uddr	= UDDR14,
	पूर्ण,
	.ep[15] = अणु
		.ep = अणु
			.name		= "ep15in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
			.caps		= USB_EP_CAPS(0, 0),
		पूर्ण,
		.dev		= &memory,
		.fअगरo_size	= INT_FIFO_SIZE,
		.bEndpoपूर्णांकAddress = USB_सूची_IN | 15,
		.bmAttributes	= USB_ENDPOINT_XFER_INT,
		.regoff_udccs	= UDCCS15,
		.regoff_uddr	= UDDR15,
	पूर्ण,
#पूर्ण_अगर /* !CONFIG_USB_PXA25X_SMALL */
पूर्ण;

#घोषणा CP15R0_VENDOR_MASK	0xffffe000

#अगर	defined(CONFIG_ARCH_PXA)
#घोषणा CP15R0_XSCALE_VALUE	0x69052000	/* पूर्णांकel/arm/xscale */

#या_अगर	defined(CONFIG_ARCH_IXP4XX)
#घोषणा CP15R0_XSCALE_VALUE	0x69054000	/* पूर्णांकel/arm/ixp4xx */

#पूर्ण_अगर

#घोषणा CP15R0_PROD_MASK	0x000003f0
#घोषणा PXA25x			0x00000100	/* and PXA26x */
#घोषणा PXA210			0x00000120

#घोषणा CP15R0_REV_MASK		0x0000000f

#घोषणा CP15R0_PRODREV_MASK	(CP15R0_PROD_MASK | CP15R0_REV_MASK)

#घोषणा PXA255_A0		0x00000106	/* or PXA260_B1 */
#घोषणा PXA250_C0		0x00000105	/* or PXA26x_B0 */
#घोषणा PXA250_B2		0x00000104
#घोषणा PXA250_B1		0x00000103	/* or PXA260_A0 */
#घोषणा PXA250_B0		0x00000102
#घोषणा PXA250_A1		0x00000101
#घोषणा PXA250_A0		0x00000100

#घोषणा PXA210_C0		0x00000125
#घोषणा PXA210_B2		0x00000124
#घोषणा PXA210_B1		0x00000123
#घोषणा PXA210_B0		0x00000122
#घोषणा IXP425_A0		0x000001c1
#घोषणा IXP425_B0		0x000001f1
#घोषणा IXP465_AD		0x00000200

/*
 *	probe - binds to the platक्रमm device
 */
अटल पूर्णांक pxa25x_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa25x_udc *dev = &memory;
	पूर्णांक retval, irq;
	u32 chiprev;

	pr_info("%s: version %s\n", driver_name, DRIVER_VERSION);

	/* insist on Intel/ARM/XScale */
	यंत्र("mrc%? p15, 0, %0, c0, c0" : "=r" (chiprev));
	अगर ((chiprev & CP15R0_VENDOR_MASK) != CP15R0_XSCALE_VALUE) अणु
		pr_err("%s: not XScale!\n", driver_name);
		वापस -ENODEV;
	पूर्ण

	/* trigger chiprev-specअगरic logic */
	चयन (chiprev & CP15R0_PRODREV_MASK) अणु
#अगर	defined(CONFIG_ARCH_PXA)
	हाल PXA255_A0:
		dev->has_cfr = 1;
		अवरोध;
	हाल PXA250_A0:
	हाल PXA250_A1:
		/* A0/A1 "not released"; ep 13, 15 unusable */
		fallthrough;
	हाल PXA250_B2: हाल PXA210_B2:
	हाल PXA250_B1: हाल PXA210_B1:
	हाल PXA250_B0: हाल PXA210_B0:
		/* OUT-DMA is broken ... */
		fallthrough;
	हाल PXA250_C0: हाल PXA210_C0:
		अवरोध;
#या_अगर	defined(CONFIG_ARCH_IXP4XX)
	हाल IXP425_A0:
	हाल IXP425_B0:
	हाल IXP465_AD:
		dev->has_cfr = 1;
		अवरोध;
#पूर्ण_अगर
	शेष:
		pr_err("%s: unrecognized processor: %08x\n",
			driver_name, chiprev);
		/* iop3xx, ixp4xx, ... */
		वापस -ENODEV;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENODEV;

	dev->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dev->regs))
		वापस PTR_ERR(dev->regs);

	dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk))
		वापस PTR_ERR(dev->clk);

	pr_debug("%s: IRQ %d%s%s\n", driver_name, irq,
		dev->has_cfr ? "" : " (!cfr)",
		SIZE_STR "(pio)"
		);

	/* other non-अटल parts of init */
	dev->dev = &pdev->dev;
	dev->mach = dev_get_platdata(&pdev->dev);

	dev->transceiver = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);

	अगर (gpio_is_valid(dev->mach->gpio_pullup)) अणु
		retval = devm_gpio_request(&pdev->dev, dev->mach->gpio_pullup,
					   "pca25x_udc GPIO PULLUP");
		अगर (retval) अणु
			dev_dbg(&pdev->dev,
				"can't get pullup gpio %d, err: %d\n",
				dev->mach->gpio_pullup, retval);
			जाओ err;
		पूर्ण
		gpio_direction_output(dev->mach->gpio_pullup, 0);
	पूर्ण

	समयr_setup(&dev->समयr, udc_watchकरोg, 0);

	the_controller = dev;
	platक्रमm_set_drvdata(pdev, dev);

	udc_disable(dev);
	udc_reinit(dev);

	dev->vbus = 0;

	/* irq setup after old hardware state is cleaned up */
	retval = devm_request_irq(&pdev->dev, irq, pxa25x_udc_irq, 0,
				  driver_name, dev);
	अगर (retval != 0) अणु
		pr_err("%s: can't get irq %d, err %d\n",
			driver_name, irq, retval);
		जाओ err;
	पूर्ण
	dev->got_irq = 1;

#अगर_घोषित CONFIG_ARCH_LUBBOCK
	अगर (machine_is_lubbock()) अणु
		retval = devm_request_irq(&pdev->dev, LUBBOCK_USB_DISC_IRQ,
					  lubbock_vbus_irq, 0, driver_name,
					  dev);
		अगर (retval != 0) अणु
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_DISC_IRQ, retval);
			जाओ err;
		पूर्ण
		retval = devm_request_irq(&pdev->dev, LUBBOCK_USB_IRQ,
					  lubbock_vbus_irq, 0, driver_name,
					  dev);
		अगर (retval != 0) अणु
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_IRQ, retval);
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	create_debug_files(dev);

	retval = usb_add_gadget_udc(&pdev->dev, &dev->gadget);
	अगर (!retval)
		वापस retval;

	हटाओ_debug_files(dev);
 err:
	अगर (!IS_ERR_OR_शून्य(dev->transceiver))
		dev->transceiver = शून्य;
	वापस retval;
पूर्ण

अटल व्योम pxa25x_udc_shutकरोwn(काष्ठा platक्रमm_device *_dev)
अणु
	pullup_off();
पूर्ण

अटल पूर्णांक pxa25x_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa25x_udc *dev = platक्रमm_get_drvdata(pdev);

	अगर (dev->driver)
		वापस -EBUSY;

	usb_del_gadget_udc(&dev->gadget);
	dev->pullup = 0;
	pullup(dev);

	हटाओ_debug_files(dev);

	अगर (!IS_ERR_OR_शून्य(dev->transceiver))
		dev->transceiver = शून्य;

	the_controller = शून्य;
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_PM

/* USB suspend (controlled by the host) and प्रणाली suspend (controlled
 * by the PXA) करोn't necessarily work well together.  If USB is active,
 * the 48 MHz घड़ी is required; so the प्रणाली can't enter 33 MHz idle
 * mode, or any deeper PM saving state.
 *
 * For now, we punt and क्रमcibly disconnect from the USB host when PXA
 * enters any suspend state.  While we're disconnected, we always disable
 * the 48MHz USB घड़ी ... allowing PXA sleep and/or 33 MHz idle states.
 * Boards without software pullup control shouldn't use those states.
 * VBUS IRQs should probably be ignored so that the PXA device just acts
 * "dead" to USB hosts until प्रणाली resume.
 */
अटल पूर्णांक pxa25x_udc_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा pxa25x_udc	*udc = platक्रमm_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	अगर (!gpio_is_valid(udc->mach->gpio_pullup) && !udc->mach->udc_command)
		WARNING("USB host won't detect disconnect!\n");
	udc->suspended = 1;

	local_irq_save(flags);
	pullup(udc);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa25x_udc_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pxa25x_udc	*udc = platक्रमm_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	udc->suspended = 0;
	local_irq_save(flags);
	pullup(udc);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा	pxa25x_udc_suspend	शून्य
#घोषणा	pxa25x_udc_resume	शून्य
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल काष्ठा platक्रमm_driver udc_driver = अणु
	.shutकरोwn	= pxa25x_udc_shutकरोwn,
	.probe		= pxa25x_udc_probe,
	.हटाओ		= pxa25x_udc_हटाओ,
	.suspend	= pxa25x_udc_suspend,
	.resume		= pxa25x_udc_resume,
	.driver		= अणु
		.name	= "pxa25x-udc",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(udc_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Frank Becker, Robert Schwebel, David Brownell");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa25x-udc");
