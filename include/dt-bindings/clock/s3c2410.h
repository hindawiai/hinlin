<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
 *
 * Device Tree binding स्थिरants घड़ी controllers of Samsung S3C2410 and later.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_SAMSUNG_S3C2410_CLOCK_H
#घोषणा _DT_BINDINGS_CLOCK_SAMSUNG_S3C2410_CLOCK_H

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
#घोषणा FCLK			4
#घोषणा HCLK			5
#घोषणा PCLK			6
#घोषणा UCLK			7
#घोषणा ARMCLK			8

/* pclk-gates */
#घोषणा PCLK_UART0		16
#घोषणा PCLK_UART1		17
#घोषणा PCLK_UART2		18
#घोषणा PCLK_I2C		19
#घोषणा PCLK_SDI		20
#घोषणा PCLK_SPI		21
#घोषणा PCLK_ADC		22
#घोषणा PCLK_AC97		23
#घोषणा PCLK_I2S		24
#घोषणा PCLK_PWM		25
#घोषणा PCLK_RTC		26
#घोषणा PCLK_GPIO		27


/* hclk-gates */
#घोषणा HCLK_LCD		32
#घोषणा HCLK_USBH		33
#घोषणा HCLK_USBD		34
#घोषणा HCLK_न_अंकD		35
#घोषणा HCLK_CAM		36


#घोषणा CAMIF			40


/* Total number of घड़ीs. */
#घोषणा NR_CLKS			(CAMIF + 1)

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_SAMSUNG_S3C2443_CLOCK_H */
