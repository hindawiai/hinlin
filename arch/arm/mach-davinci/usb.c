<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>
#समावेश <linux/usb/musb.h>

#समावेश <mach/common.h>
#समावेश <mach/cputype.h>

#समावेश "irqs.h"

#घोषणा DAVINCI_USB_OTG_BASE	0x01c64000

#अगर IS_ENABLED(CONFIG_USB_MUSB_HDRC)
अटल काष्ठा musb_hdrc_config musb_config = अणु
	.multipoपूर्णांक	= true,

	.num_eps	= 5,
	.ram_bits	= 10,
पूर्ण;

अटल काष्ठा musb_hdrc_platक्रमm_data usb_data = अणु
	/* OTG requires a Mini-AB connector */
	.mode           = MUSB_OTG,
	.घड़ी		= "usb",
	.config		= &musb_config,
पूर्ण;

अटल काष्ठा resource usb_resources[] = अणु
	अणु
		/* physical address */
		.start          = DAVINCI_USB_OTG_BASE,
		.end            = DAVINCI_USB_OTG_BASE + 0x5ff,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start          = DAVINCI_INTC_IRQ(IRQ_USBINT),
		.flags          = IORESOURCE_IRQ,
		.name		= "mc"
	पूर्ण,
	अणु
		/* placeholder क्रम the dedicated CPPI IRQ */
		.flags          = IORESOURCE_IRQ,
		.name		= "dma"
	पूर्ण,
पूर्ण;

अटल u64 usb_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device usb_dev = अणु
	.name           = "musb-davinci",
	.id             = -1,
	.dev = अणु
		.platक्रमm_data		= &usb_data,
		.dma_mask		= &usb_dmamask,
		.coherent_dma_mask      = DMA_BIT_MASK(32),
	पूर्ण,
	.resource       = usb_resources,
	.num_resources  = ARRAY_SIZE(usb_resources),
पूर्ण;

व्योम __init davinci_setup_usb(अचिन्हित mA, अचिन्हित potpgt_ms)
अणु
	usb_data.घातer = mA > 510 ? 255 : mA / 2;
	usb_data.potpgt = (potpgt_ms + 1) / 2;

	अगर (cpu_is_davinci_dm646x()) अणु
		/* Override the शेषs as DM6467 uses dअगरferent IRQs. */
		usb_dev.resource[1].start = DAVINCI_INTC_IRQ(IRQ_DM646X_USBINT);
		usb_dev.resource[2].start = DAVINCI_INTC_IRQ(
							IRQ_DM646X_USBDMAINT);
	पूर्ण अन्यथा	/* other devices करोn't have dedicated CPPI IRQ */
		usb_dev.num_resources = 2;

	platक्रमm_device_रेजिस्टर(&usb_dev);
पूर्ण

#अन्यथा

व्योम __init davinci_setup_usb(अचिन्हित mA, अचिन्हित potpgt_ms)
अणु
पूर्ण

#पूर्ण_अगर  /* CONFIG_USB_MUSB_HDRC */
