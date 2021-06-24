<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 * Copyright (C) 2012 Kevin Cernekee <cernekee@gmail.com>
 * Copyright (C) 2012 Broadcom Corporation
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_dev_usb_usbd.h>

#घोषणा NUM_MMIO		2
#घोषणा NUM_IRQ			7

अटल काष्ठा resource usbd_resources[NUM_MMIO + NUM_IRQ];

अटल u64 usbd_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device bcm63xx_usbd_device = अणु
	.name		= "bcm63xx_udc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(usbd_resources),
	.resource	= usbd_resources,
	.dev		= अणु
		.dma_mask		= &usbd_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

पूर्णांक __init bcm63xx_usbd_रेजिस्टर(स्थिर काष्ठा bcm63xx_usbd_platक्रमm_data *pd)
अणु
	स्थिर पूर्णांक irq_list[NUM_IRQ] = अणु IRQ_USBD,
		IRQ_USBD_RXDMA0, IRQ_USBD_TXDMA0,
		IRQ_USBD_RXDMA1, IRQ_USBD_TXDMA1,
		IRQ_USBD_RXDMA2, IRQ_USBD_TXDMA2 पूर्ण;
	पूर्णांक i;

	अगर (!BCMCPU_IS_6328() && !BCMCPU_IS_6368())
		वापस 0;

	usbd_resources[0].start = bcm63xx_regset_address(RSET_USBD);
	usbd_resources[0].end = usbd_resources[0].start + RSET_USBD_SIZE - 1;
	usbd_resources[0].flags = IORESOURCE_MEM;

	usbd_resources[1].start = bcm63xx_regset_address(RSET_USBDMA);
	usbd_resources[1].end = usbd_resources[1].start + RSET_USBDMA_SIZE - 1;
	usbd_resources[1].flags = IORESOURCE_MEM;

	क्रम (i = 0; i < NUM_IRQ; i++) अणु
		काष्ठा resource *r = &usbd_resources[NUM_MMIO + i];

		r->start = r->end = bcm63xx_get_irq_number(irq_list[i]);
		r->flags = IORESOURCE_IRQ;
	पूर्ण

	platक्रमm_device_add_data(&bcm63xx_usbd_device, pd, माप(*pd));

	वापस platक्रमm_device_रेजिस्टर(&bcm63xx_usbd_device);
पूर्ण
