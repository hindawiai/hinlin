<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* linux/arch/arm/mach-s3c6400/include/mach/dma.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S3C6400 - DMA support
 */

#अगर_अघोषित __ASM_ARCH_DMA_H
#घोषणा __ASM_ARCH_DMA_H __खाता__

#घोषणा S3C64XX_DMA_CHAN(name)		((अचिन्हित दीर्घ)(name))

/* DMA0/SDMA0 */
#घोषणा DMACH_UART0		"uart0_tx"
#घोषणा DMACH_UART0_SRC2	"uart0_rx"
#घोषणा DMACH_UART1		"uart1_tx"
#घोषणा DMACH_UART1_SRC2	"uart1_rx"
#घोषणा DMACH_UART2		"uart2_tx"
#घोषणा DMACH_UART2_SRC2	"uart2_rx"
#घोषणा DMACH_UART3		"uart3_tx"
#घोषणा DMACH_UART3_SRC2	"uart3_rx"
#घोषणा DMACH_PCM0_TX		"pcm0_tx"
#घोषणा DMACH_PCM0_RX		"pcm0_rx"
#घोषणा DMACH_I2S0_OUT		"i2s0_tx"
#घोषणा DMACH_I2S0_IN		"i2s0_rx"
#घोषणा DMACH_SPI0_TX		S3C64XX_DMA_CHAN("spi0_tx")
#घोषणा DMACH_SPI0_RX		S3C64XX_DMA_CHAN("spi0_rx")
#घोषणा DMACH_HSI_I2SV40_TX	"i2s2_tx"
#घोषणा DMACH_HSI_I2SV40_RX	"i2s2_rx"

/* DMA1/SDMA1 */
#घोषणा DMACH_PCM1_TX		"pcm1_tx"
#घोषणा DMACH_PCM1_RX		"pcm1_rx"
#घोषणा DMACH_I2S1_OUT		"i2s1_tx"
#घोषणा DMACH_I2S1_IN		"i2s1_rx"
#घोषणा DMACH_SPI1_TX		S3C64XX_DMA_CHAN("spi1_tx")
#घोषणा DMACH_SPI1_RX		S3C64XX_DMA_CHAN("spi1_rx")
#घोषणा DMACH_AC97_PCMOUT	"ac97_out"
#घोषणा DMACH_AC97_PCMIN	"ac97_in"
#घोषणा DMACH_AC97_MICIN	"ac97_mic"
#घोषणा DMACH_PWM		"pwm"
#घोषणा DMACH_IRDA		"irda"
#घोषणा DMACH_EXTERNAL		"external"
#घोषणा DMACH_SECURITY_RX	"sec_rx"
#घोषणा DMACH_SECURITY_TX	"sec_tx"

क्रमागत dma_ch अणु
	DMACH_MAX = 32
पूर्ण;

#समावेश <linux/amba/pl08x.h>

#पूर्ण_अगर /* __ASM_ARCH_IRQ_H */
