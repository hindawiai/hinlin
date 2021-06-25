<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Google, Inc.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_PISTACHIO_H
#घोषणा _DT_BINDINGS_CLOCK_PISTACHIO_H

/* PLLs */
#घोषणा CLK_MIPS_PLL			0
#घोषणा CLK_AUDIO_PLL			1
#घोषणा CLK_RPU_V_PLL			2
#घोषणा CLK_RPU_L_PLL			3
#घोषणा CLK_SYS_PLL			4
#घोषणा CLK_WIFI_PLL			5
#घोषणा CLK_BT_PLL			6

/* Fixed-factor घड़ीs */
#घोषणा CLK_WIFI_DIV4			16
#घोषणा CLK_WIFI_DIV8			17

/* Gate घड़ीs */
#घोषणा CLK_MIPS			32
#घोषणा CLK_AUDIO_IN			33
#घोषणा CLK_AUDIO			34
#घोषणा CLK_I2S				35
#घोषणा CLK_SPDIF			36
#घोषणा CLK_AUDIO_DAC			37
#घोषणा CLK_RPU_V			38
#घोषणा CLK_RPU_L			39
#घोषणा CLK_RPU_SLEEP			40
#घोषणा CLK_WIFI_PLL_GATE		41
#घोषणा CLK_RPU_CORE			42
#घोषणा CLK_WIFI_ADC			43
#घोषणा CLK_WIFI_DAC			44
#घोषणा CLK_USB_PHY			45
#घोषणा CLK_ENET_IN			46
#घोषणा CLK_ENET			47
#घोषणा CLK_UART0			48
#घोषणा CLK_UART1			49
#घोषणा CLK_PERIPH_SYS			50
#घोषणा CLK_SPI0			51
#घोषणा CLK_SPI1			52
#घोषणा CLK_EVENT_TIMER			53
#घोषणा CLK_AUX_ADC_INTERNAL		54
#घोषणा CLK_AUX_ADC			55
#घोषणा CLK_SD_HOST			56
#घोषणा CLK_BT				57
#घोषणा CLK_BT_DIV4			58
#घोषणा CLK_BT_DIV8			59
#घोषणा CLK_BT_1MHZ			60

/* Divider घड़ीs */
#घोषणा CLK_MIPS_INTERNAL_DIV		64
#घोषणा CLK_MIPS_DIV			65
#घोषणा CLK_AUDIO_DIV			66
#घोषणा CLK_I2S_DIV			67
#घोषणा CLK_SPDIF_DIV			68
#घोषणा CLK_AUDIO_DAC_DIV		69
#घोषणा CLK_RPU_V_DIV			70
#घोषणा CLK_RPU_L_DIV			71
#घोषणा CLK_RPU_SLEEP_DIV		72
#घोषणा CLK_RPU_CORE_DIV		73
#घोषणा CLK_USB_PHY_DIV			74
#घोषणा CLK_ENET_DIV			75
#घोषणा CLK_UART0_INTERNAL_DIV		76
#घोषणा CLK_UART0_DIV			77
#घोषणा CLK_UART1_INTERNAL_DIV		78
#घोषणा CLK_UART1_DIV			79
#घोषणा CLK_SYS_INTERNAL_DIV		80
#घोषणा CLK_SPI0_INTERNAL_DIV		81
#घोषणा CLK_SPI0_DIV			82
#घोषणा CLK_SPI1_INTERNAL_DIV		83
#घोषणा CLK_SPI1_DIV			84
#घोषणा CLK_EVENT_TIMER_INTERNAL_DIV	85
#घोषणा CLK_EVENT_TIMER_DIV		86
#घोषणा CLK_AUX_ADC_INTERNAL_DIV	87
#घोषणा CLK_AUX_ADC_DIV			88
#घोषणा CLK_SD_HOST_DIV			89
#घोषणा CLK_BT_DIV			90
#घोषणा CLK_BT_DIV4_DIV			91
#घोषणा CLK_BT_DIV8_DIV			92
#घोषणा CLK_BT_1MHZ_INTERNAL_DIV	93
#घोषणा CLK_BT_1MHZ_DIV			94

/* Mux घड़ीs */
#घोषणा CLK_AUDIO_REF_MUX		96
#घोषणा CLK_MIPS_PLL_MUX		97
#घोषणा CLK_AUDIO_PLL_MUX		98
#घोषणा CLK_AUDIO_MUX			99
#घोषणा CLK_RPU_V_PLL_MUX		100
#घोषणा CLK_RPU_L_PLL_MUX		101
#घोषणा CLK_RPU_L_MUX			102
#घोषणा CLK_WIFI_PLL_MUX		103
#घोषणा CLK_WIFI_DIV4_MUX		104
#घोषणा CLK_WIFI_DIV8_MUX		105
#घोषणा CLK_RPU_CORE_MUX		106
#घोषणा CLK_SYS_PLL_MUX			107
#घोषणा CLK_ENET_MUX			108
#घोषणा CLK_EVENT_TIMER_MUX		109
#घोषणा CLK_SD_HOST_MUX			110
#घोषणा CLK_BT_PLL_MUX			111
#घोषणा CLK_DEBUG_MUX			112

#घोषणा CLK_NR_CLKS			113

/* Peripheral gate घड़ीs */
#घोषणा PERIPH_CLK_SYS			0
#घोषणा PERIPH_CLK_SYS_BUS		1
#घोषणा PERIPH_CLK_DDR			2
#घोषणा PERIPH_CLK_ROM			3
#घोषणा PERIPH_CLK_COUNTER_FAST		4
#घोषणा PERIPH_CLK_COUNTER_SLOW		5
#घोषणा PERIPH_CLK_IR			6
#घोषणा PERIPH_CLK_WD			7
#घोषणा PERIPH_CLK_PDM			8
#घोषणा PERIPH_CLK_PWM			9
#घोषणा PERIPH_CLK_I2C0			10
#घोषणा PERIPH_CLK_I2C1			11
#घोषणा PERIPH_CLK_I2C2			12
#घोषणा PERIPH_CLK_I2C3			13

/* Peripheral भागider घड़ीs */
#घोषणा PERIPH_CLK_ROM_DIV		32
#घोषणा PERIPH_CLK_COUNTER_FAST_DIV	33
#घोषणा PERIPH_CLK_COUNTER_SLOW_PRE_DIV	34
#घोषणा PERIPH_CLK_COUNTER_SLOW_DIV	35
#घोषणा PERIPH_CLK_IR_PRE_DIV		36
#घोषणा PERIPH_CLK_IR_DIV		37
#घोषणा PERIPH_CLK_WD_PRE_DIV		38
#घोषणा PERIPH_CLK_WD_DIV		39
#घोषणा PERIPH_CLK_PDM_PRE_DIV		40
#घोषणा PERIPH_CLK_PDM_DIV		41
#घोषणा PERIPH_CLK_PWM_PRE_DIV		42
#घोषणा PERIPH_CLK_PWM_DIV		43
#घोषणा PERIPH_CLK_I2C0_PRE_DIV		44
#घोषणा PERIPH_CLK_I2C0_DIV		45
#घोषणा PERIPH_CLK_I2C1_PRE_DIV		46
#घोषणा PERIPH_CLK_I2C1_DIV		47
#घोषणा PERIPH_CLK_I2C2_PRE_DIV		48
#घोषणा PERIPH_CLK_I2C2_DIV		49
#घोषणा PERIPH_CLK_I2C3_PRE_DIV		50
#घोषणा PERIPH_CLK_I2C3_DIV		51

#घोषणा PERIPH_CLK_NR_CLKS		52

/* System gate घड़ीs */
#घोषणा SYS_CLK_I2C0			0
#घोषणा SYS_CLK_I2C1			1
#घोषणा SYS_CLK_I2C2			2
#घोषणा SYS_CLK_I2C3			3
#घोषणा SYS_CLK_I2S_IN			4
#घोषणा SYS_CLK_PAUD_OUT		5
#घोषणा SYS_CLK_SPDIF_OUT		6
#घोषणा SYS_CLK_SPI0_MASTER		7
#घोषणा SYS_CLK_SPI0_SLAVE		8
#घोषणा SYS_CLK_PWM			9
#घोषणा SYS_CLK_UART0			10
#घोषणा SYS_CLK_UART1			11
#घोषणा SYS_CLK_SPI1			12
#घोषणा SYS_CLK_MDC			13
#घोषणा SYS_CLK_SD_HOST			14
#घोषणा SYS_CLK_ENET			15
#घोषणा SYS_CLK_IR			16
#घोषणा SYS_CLK_WD			17
#घोषणा SYS_CLK_TIMER			18
#घोषणा SYS_CLK_I2S_OUT			24
#घोषणा SYS_CLK_SPDIF_IN		25
#घोषणा SYS_CLK_EVENT_TIMER		26
#घोषणा SYS_CLK_HASH			27

#घोषणा SYS_CLK_NR_CLKS			28

/* Gates क्रम बाह्यal input घड़ीs */
#घोषणा EXT_CLK_AUDIO_IN		0
#घोषणा EXT_CLK_ENET_IN			1

#घोषणा EXT_CLK_NR_CLKS			2

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_PISTACHIO_H */
