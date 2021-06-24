<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 *
 * Device Tree binding स्थिरants घड़ी controllers of Samsung S3C2443 and later.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_SAMSUNG_S3C2443_CLOCK_H
#घोषणा _DT_BINDINGS_CLOCK_SAMSUNG_S3C2443_CLOCK_H

/*
 * Let each exported घड़ी get a unique index, which is used on DT-enabled
 * platक्रमms to lookup the घड़ी from a घड़ी specअगरier. These indices are
 * thereक्रमe considered an ABI and so must not be changed. This implies
 * that new घड़ीs should be added either in मुक्त spaces between घड़ी groups
 * or at the end.
 */

/* Core घड़ीs. */
#घोषणा MSYSCLK			1
#घोषणा ESYSCLK			2
#घोषणा ARMDIV			3
#घोषणा ARMCLK			4
#घोषणा HCLK			5
#घोषणा PCLK			6
#घोषणा MPLL			7
#घोषणा EPLL			8

/* Special घड़ीs */
#घोषणा SCLK_HSSPI0		16
#घोषणा SCLK_FIMD		17
#घोषणा SCLK_I2S0		18
#घोषणा SCLK_I2S1		19
#घोषणा SCLK_HSMMC1		20
#घोषणा SCLK_HSMMC_EXT		21
#घोषणा SCLK_CAM		22
#घोषणा SCLK_UART		23
#घोषणा SCLK_USBH		24

/* Muxes */
#घोषणा MUX_HSSPI0		32
#घोषणा MUX_HSSPI1		33
#घोषणा MUX_HSMMC0		34
#घोषणा MUX_HSMMC1		35

/* hclk-gates */
#घोषणा HCLK_DMA0		48
#घोषणा HCLK_DMA1		49
#घोषणा HCLK_DMA2		50
#घोषणा HCLK_DMA3		51
#घोषणा HCLK_DMA4		52
#घोषणा HCLK_DMA5		53
#घोषणा HCLK_DMA6		54
#घोषणा HCLK_DMA7		55
#घोषणा HCLK_CAM		56
#घोषणा HCLK_LCD		57
#घोषणा HCLK_USBH		58
#घोषणा HCLK_USBD		59
#घोषणा HCLK_IROM		60
#घोषणा HCLK_HSMMC0		61
#घोषणा HCLK_HSMMC1		62
#घोषणा HCLK_CFC		63
#घोषणा HCLK_SSMC		64
#घोषणा HCLK_DRAM		65
#घोषणा HCLK_2D			66

/* pclk-gates */
#घोषणा PCLK_UART0		72
#घोषणा PCLK_UART1		73
#घोषणा PCLK_UART2		74
#घोषणा PCLK_UART3		75
#घोषणा PCLK_I2C0		76
#घोषणा PCLK_SDI		77
#घोषणा PCLK_SPI0		78
#घोषणा PCLK_ADC		79
#घोषणा PCLK_AC97		80
#घोषणा PCLK_I2S0		81
#घोषणा PCLK_PWM		82
#घोषणा PCLK_WDT		83
#घोषणा PCLK_RTC		84
#घोषणा PCLK_GPIO		85
#घोषणा PCLK_SPI1		86
#घोषणा PCLK_CHIPID		87
#घोषणा PCLK_I2C1		88
#घोषणा PCLK_I2S1		89
#घोषणा PCLK_PCM		90

/* Total number of घड़ीs. */
#घोषणा NR_CLKS			(PCLK_PCM + 1)

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_SAMSUNG_S3C2443_CLOCK_H */
