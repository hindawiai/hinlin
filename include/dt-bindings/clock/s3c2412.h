<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 *
 * Device Tree binding स्थिरants घड़ी controllers of Samsung S3C2412.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_SAMSUNG_S3C2412_CLOCK_H
#घोषणा _DT_BINDINGS_CLOCK_SAMSUNG_S3C2412_CLOCK_H

/*
 * Let each exported घड़ी get a unique index, which is used on DT-enabled
 * platक्रमms to lookup the घड़ी from a घड़ी specअगरier. These indices are
 * thereक्रमe considered an ABI and so must not be changed. This implies
 * that new घड़ीs should be added either in मुक्त spaces between घड़ी groups
 * or at the end.
 */

/* Core घड़ीs. */

/* id 1 is reserved */
#घोषणा MPLL			2
#घोषणा UPLL			3
#घोषणा MDIVCLK			4
#घोषणा MSYSCLK			5
#घोषणा USYSCLK			6
#घोषणा HCLK			7
#घोषणा PCLK			8
#घोषणा ARMDIV			9
#घोषणा ARMCLK			10


/* Special घड़ीs */
#घोषणा SCLK_CAM		16
#घोषणा SCLK_UART		17
#घोषणा SCLK_I2S		18
#घोषणा SCLK_USBD		19
#घोषणा SCLK_USBH		20

/* pclk-gates */
#घोषणा PCLK_WDT		32
#घोषणा PCLK_SPI		33
#घोषणा PCLK_I2S		34
#घोषणा PCLK_I2C		35
#घोषणा PCLK_ADC		36
#घोषणा PCLK_RTC		37
#घोषणा PCLK_GPIO		38
#घोषणा PCLK_UART2		39
#घोषणा PCLK_UART1		40
#घोषणा PCLK_UART0		41
#घोषणा PCLK_SDI		42
#घोषणा PCLK_PWM		43
#घोषणा PCLK_USBD		44

/* hclk-gates */
#घोषणा HCLK_HALF		48
#घोषणा HCLK_X2			49
#घोषणा HCLK_SDRAM		50
#घोषणा HCLK_USBH		51
#घोषणा HCLK_LCD		52
#घोषणा HCLK_न_अंकD		53
#घोषणा HCLK_DMA3		54
#घोषणा HCLK_DMA2		55
#घोषणा HCLK_DMA1		56
#घोषणा HCLK_DMA0		57

/* Total number of घड़ीs. */
#घोषणा NR_CLKS			(HCLK_DMA0 + 1)

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_SAMSUNG_S3C2412_CLOCK_H */
