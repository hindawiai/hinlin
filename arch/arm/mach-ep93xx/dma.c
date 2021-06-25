<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/dma.c
 *
 * Platक्रमm support code क्रम the EP93xx dmaengine driver.
 *
 * Copyright (C) 2011 Mika Westerberg
 *
 * This work is based on the original dma-m2p implementation with
 * following copyrights:
 *
 *   Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 *   Copyright (C) 2006 Applied Data Systems
 *   Copyright (C) 2009 Ryan Mallon <rmallon@gmail.com>
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/platक्रमm_data/dma-ep93xx.h>
#समावेश "hardware.h"

#समावेश "soc.h"

#घोषणा DMA_CHANNEL(_name, _base, _irq) \
	अणु .name = (_name), .base = (_base), .irq = (_irq) पूर्ण

/*
 * DMA M2P channels.
 *
 * On the EP93xx chip the following peripherals my be allocated to the 10
 * Memory to Internal Peripheral (M2P) channels (5 transmit + 5 receive).
 *
 *	I2S	contains 3 Tx and 3 Rx DMA Channels
 *	AAC	contains 3 Tx and 3 Rx DMA Channels
 *	UART1	contains 1 Tx and 1 Rx DMA Channels
 *	UART2	contains 1 Tx and 1 Rx DMA Channels
 *	UART3	contains 1 Tx and 1 Rx DMA Channels
 *	IrDA	contains 1 Tx and 1 Rx DMA Channels
 *
 * Registers are mapped अटलally in ep93xx_map_io().
 */
अटल काष्ठा ep93xx_dma_chan_data ep93xx_dma_m2p_channels[] = अणु
	DMA_CHANNEL("m2p0", EP93XX_DMA_BASE + 0x0000, IRQ_EP93XX_DMAM2P0),
	DMA_CHANNEL("m2p1", EP93XX_DMA_BASE + 0x0040, IRQ_EP93XX_DMAM2P1),
	DMA_CHANNEL("m2p2", EP93XX_DMA_BASE + 0x0080, IRQ_EP93XX_DMAM2P2),
	DMA_CHANNEL("m2p3", EP93XX_DMA_BASE + 0x00c0, IRQ_EP93XX_DMAM2P3),
	DMA_CHANNEL("m2p4", EP93XX_DMA_BASE + 0x0240, IRQ_EP93XX_DMAM2P4),
	DMA_CHANNEL("m2p5", EP93XX_DMA_BASE + 0x0200, IRQ_EP93XX_DMAM2P5),
	DMA_CHANNEL("m2p6", EP93XX_DMA_BASE + 0x02c0, IRQ_EP93XX_DMAM2P6),
	DMA_CHANNEL("m2p7", EP93XX_DMA_BASE + 0x0280, IRQ_EP93XX_DMAM2P7),
	DMA_CHANNEL("m2p8", EP93XX_DMA_BASE + 0x0340, IRQ_EP93XX_DMAM2P8),
	DMA_CHANNEL("m2p9", EP93XX_DMA_BASE + 0x0300, IRQ_EP93XX_DMAM2P9),
पूर्ण;

अटल काष्ठा ep93xx_dma_platक्रमm_data ep93xx_dma_m2p_data = अणु
	.channels		= ep93xx_dma_m2p_channels,
	.num_channels		= ARRAY_SIZE(ep93xx_dma_m2p_channels),
पूर्ण;

अटल u64 ep93xx_dma_m2p_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device ep93xx_dma_m2p_device = अणु
	.name			= "ep93xx-dma-m2p",
	.id			= -1,
	.dev			= अणु
		.platक्रमm_data		= &ep93xx_dma_m2p_data,
		.dma_mask		= &ep93xx_dma_m2p_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

/*
 * DMA M2M channels.
 *
 * There are 2 M2M channels which support स_नकल/स_रखो and in addition simple
 * hardware requests from/to SSP and IDE. We करो not implement an बाह्यal
 * hardware requests.
 *
 * Registers are mapped अटलally in ep93xx_map_io().
 */
अटल काष्ठा ep93xx_dma_chan_data ep93xx_dma_m2m_channels[] = अणु
	DMA_CHANNEL("m2m0", EP93XX_DMA_BASE + 0x0100, IRQ_EP93XX_DMAM2M0),
	DMA_CHANNEL("m2m1", EP93XX_DMA_BASE + 0x0140, IRQ_EP93XX_DMAM2M1),
पूर्ण;

अटल काष्ठा ep93xx_dma_platक्रमm_data ep93xx_dma_m2m_data = अणु
	.channels		= ep93xx_dma_m2m_channels,
	.num_channels		= ARRAY_SIZE(ep93xx_dma_m2m_channels),
पूर्ण;

अटल u64 ep93xx_dma_m2m_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device ep93xx_dma_m2m_device = अणु
	.name			= "ep93xx-dma-m2m",
	.id			= -1,
	.dev			= अणु
		.platक्रमm_data		= &ep93xx_dma_m2m_data,
		.dma_mask		= &ep93xx_dma_m2m_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ep93xx_dma_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&ep93xx_dma_m2p_device);
	platक्रमm_device_रेजिस्टर(&ep93xx_dma_m2m_device);
	वापस 0;
पूर्ण
arch_initcall(ep93xx_dma_init);
