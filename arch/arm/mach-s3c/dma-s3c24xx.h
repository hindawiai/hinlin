<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2003-2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Samsung S3C24XX DMA support
 */

#अगर_अघोषित __ASM_ARCH_DMA_H
#घोषणा __ASM_ARCH_DMA_H __खाता__

#समावेश <linux/device.h>

/* We use `भव` dma channels to hide the fact we have only a limited
 * number of DMA channels, and not of all of them (dependent on the device)
 * can be attached to any DMA source. We thereक्रमe let the DMA core handle
 * the allocation of hardware channels to clients.
*/

क्रमागत dma_ch अणु
	DMACH_XD0 = 0,
	DMACH_XD1,
	DMACH_SDI,
	DMACH_SPI0,
	DMACH_SPI1,
	DMACH_UART0,
	DMACH_UART1,
	DMACH_UART2,
	DMACH_TIMER,
	DMACH_I2S_IN,
	DMACH_I2S_OUT,
	DMACH_PCM_IN,
	DMACH_PCM_OUT,
	DMACH_MIC_IN,
	DMACH_USB_EP1,
	DMACH_USB_EP2,
	DMACH_USB_EP3,
	DMACH_USB_EP4,
	DMACH_UART0_SRC2,	/* s3c2412 second uart sources */
	DMACH_UART1_SRC2,
	DMACH_UART2_SRC2,
	DMACH_UART3,		/* s3c2443 has extra uart */
	DMACH_UART3_SRC2,
	DMACH_SPI0_TX,		/* s3c2443/2416/2450 hsspi0 */
	DMACH_SPI0_RX,		/* s3c2443/2416/2450 hsspi0 */
	DMACH_SPI1_TX,		/* s3c2443/2450 hsspi1 */
	DMACH_SPI1_RX,		/* s3c2443/2450 hsspi1 */
	DMACH_MAX,		/* the end entry */
पूर्ण;

#पूर्ण_अगर /* __ASM_ARCH_DMA_H */
