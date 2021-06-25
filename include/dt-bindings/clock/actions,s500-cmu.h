<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Device Tree binding स्थिरants क्रम Actions Semi S500 Clock Management Unit
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Copyright (c) 2018 LSI-TEC - Caninos Loucos
 */

#अगर_अघोषित __DT_BINDINGS_CLOCK_S500_CMU_H
#घोषणा __DT_BINDINGS_CLOCK_S500_CMU_H

#घोषणा CLK_NONE		0

/* fixed rate घड़ीs */
#घोषणा CLK_LOSC		1
#घोषणा CLK_HOSC		2

/* pll घड़ीs */
#घोषणा CLK_CORE_PLL		3
#घोषणा CLK_DEV_PLL		4
#घोषणा CLK_DDR_PLL		5
#घोषणा CLK_न_अंकD_PLL		6
#घोषणा CLK_DISPLAY_PLL		7
#घोषणा CLK_ETHERNET_PLL	8
#घोषणा CLK_AUDIO_PLL		9

/* प्रणाली घड़ी */
#घोषणा CLK_DEV			10
#घोषणा CLK_H			11
#घोषणा CLK_AHBPREDIV		12
#घोषणा CLK_AHB			13
#घोषणा CLK_DE			14
#घोषणा CLK_BISP		15
#घोषणा CLK_VCE			16
#घोषणा CLK_VDE			17

/* peripheral device घड़ी */
#घोषणा CLK_TIMER		18
#घोषणा CLK_I2C0		19
#घोषणा CLK_I2C1		20
#घोषणा CLK_I2C2		21
#घोषणा CLK_I2C3		22
#घोषणा CLK_PWM0		23
#घोषणा CLK_PWM1		24
#घोषणा CLK_PWM2		25
#घोषणा CLK_PWM3		26
#घोषणा CLK_PWM4		27
#घोषणा CLK_PWM5		28
#घोषणा CLK_SD0			29
#घोषणा CLK_SD1			30
#घोषणा CLK_SD2			31
#घोषणा CLK_SENSOR0		32
#घोषणा CLK_SENSOR1		33
#घोषणा CLK_SPI0		34
#घोषणा CLK_SPI1		35
#घोषणा CLK_SPI2		36
#घोषणा CLK_SPI3		37
#घोषणा CLK_UART0		38
#घोषणा CLK_UART1		39
#घोषणा CLK_UART2		40
#घोषणा CLK_UART3		41
#घोषणा CLK_UART4		42
#घोषणा CLK_UART5		43
#घोषणा CLK_UART6		44
#घोषणा CLK_DE1			45
#घोषणा CLK_DE2			46
#घोषणा CLK_I2SRX		47
#घोषणा CLK_I2STX		48
#घोषणा CLK_HDMI_AUDIO		49
#घोषणा CLK_HDMI		50
#घोषणा CLK_SPDIF		51
#घोषणा CLK_न_अंकD		52
#घोषणा CLK_ECC			53
#घोषणा CLK_RMII_REF		54
#घोषणा CLK_GPIO		55

/* प्रणाली घड़ी (part 2) */
#घोषणा CLK_APB			56
#घोषणा CLK_DMAC		57

#घोषणा CLK_NR_CLKS		(CLK_DMAC + 1)

#पूर्ण_अगर /* __DT_BINDINGS_CLOCK_S500_CMU_H */
