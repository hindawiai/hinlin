<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Author: Gabriel Fernandez <gabriel.fernandez@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _DT_BINDINGS_STM32MP1_CLKS_H_
#घोषणा _DT_BINDINGS_STM32MP1_CLKS_H_

/* OSCILLATOR घड़ीs */
#घोषणा CK_HSE		0
#घोषणा CK_CSI		1
#घोषणा CK_LSI		2
#घोषणा CK_LSE		3
#घोषणा CK_HSI		4
#घोषणा CK_HSE_DIV2	5

/* Bus घड़ीs */
#घोषणा TIM2		6
#घोषणा TIM3		7
#घोषणा TIM4		8
#घोषणा TIM5		9
#घोषणा TIM6		10
#घोषणा TIM7		11
#घोषणा TIM12		12
#घोषणा TIM13		13
#घोषणा TIM14		14
#घोषणा LPTIM1		15
#घोषणा SPI2		16
#घोषणा SPI3		17
#घोषणा USART2		18
#घोषणा USART3		19
#घोषणा UART4		20
#घोषणा UART5		21
#घोषणा UART7		22
#घोषणा UART8		23
#घोषणा I2C1		24
#घोषणा I2C2		25
#घोषणा I2C3		26
#घोषणा I2C5		27
#घोषणा SPDIF		28
#घोषणा CEC		29
#घोषणा DAC12		30
#घोषणा MDIO		31
#घोषणा TIM1		32
#घोषणा TIM8		33
#घोषणा TIM15		34
#घोषणा TIM16		35
#घोषणा TIM17		36
#घोषणा SPI1		37
#घोषणा SPI4		38
#घोषणा SPI5		39
#घोषणा USART6		40
#घोषणा SAI1		41
#घोषणा SAI2		42
#घोषणा SAI3		43
#घोषणा DFSDM		44
#घोषणा FDCAN		45
#घोषणा LPTIM2		46
#घोषणा LPTIM3		47
#घोषणा LPTIM4		48
#घोषणा LPTIM5		49
#घोषणा SAI4		50
#घोषणा SYSCFG		51
#घोषणा VREF		52
#घोषणा TMPSENS		53
#घोषणा PMBCTRL		54
#घोषणा HDP		55
#घोषणा LTDC		56
#घोषणा DSI		57
#घोषणा IWDG2		58
#घोषणा USBPHY		59
#घोषणा STGENRO		60
#घोषणा SPI6		61
#घोषणा I2C4		62
#घोषणा I2C6		63
#घोषणा USART1		64
#घोषणा RTCAPB		65
#घोषणा TZC1		66
#घोषणा TZPC		67
#घोषणा IWDG1		68
#घोषणा BSEC		69
#घोषणा STGEN		70
#घोषणा DMA1		71
#घोषणा DMA2		72
#घोषणा DMAMUX		73
#घोषणा ADC12		74
#घोषणा USBO		75
#घोषणा SDMMC3		76
#घोषणा DCMI		77
#घोषणा CRYP2		78
#घोषणा HASH2		79
#घोषणा RNG2		80
#घोषणा CRC2		81
#घोषणा HSEM		82
#घोषणा IPCC		83
#घोषणा GPIOA		84
#घोषणा GPIOB		85
#घोषणा GPIOC		86
#घोषणा GPIOD		87
#घोषणा GPIOE		88
#घोषणा GPIOF		89
#घोषणा GPIOG		90
#घोषणा GPIOH		91
#घोषणा GPIOI		92
#घोषणा GPIOJ		93
#घोषणा GPIOK		94
#घोषणा GPIOZ		95
#घोषणा CRYP1		96
#घोषणा HASH1		97
#घोषणा RNG1		98
#घोषणा BKPSRAM		99
#घोषणा MDMA		100
#घोषणा GPU		101
#घोषणा ETHCK		102
#घोषणा ETHTX		103
#घोषणा ETHRX		104
#घोषणा ETHMAC		105
#घोषणा FMC		106
#घोषणा QSPI		107
#घोषणा SDMMC1		108
#घोषणा SDMMC2		109
#घोषणा CRC1		110
#घोषणा USBH		111
#घोषणा ETHSTP		112
#घोषणा TZC2		113

/* Kernel घड़ीs */
#घोषणा SDMMC1_K	118
#घोषणा SDMMC2_K	119
#घोषणा SDMMC3_K	120
#घोषणा FMC_K		121
#घोषणा QSPI_K		122
#घोषणा ETHCK_K		123
#घोषणा RNG1_K		124
#घोषणा RNG2_K		125
#घोषणा GPU_K		126
#घोषणा USBPHY_K	127
#घोषणा STGEN_K		128
#घोषणा SPDIF_K		129
#घोषणा SPI1_K		130
#घोषणा SPI2_K		131
#घोषणा SPI3_K		132
#घोषणा SPI4_K		133
#घोषणा SPI5_K		134
#घोषणा SPI6_K		135
#घोषणा CEC_K		136
#घोषणा I2C1_K		137
#घोषणा I2C2_K		138
#घोषणा I2C3_K		139
#घोषणा I2C4_K		140
#घोषणा I2C5_K		141
#घोषणा I2C6_K		142
#घोषणा LPTIM1_K	143
#घोषणा LPTIM2_K	144
#घोषणा LPTIM3_K	145
#घोषणा LPTIM4_K	146
#घोषणा LPTIM5_K	147
#घोषणा USART1_K	148
#घोषणा USART2_K	149
#घोषणा USART3_K	150
#घोषणा UART4_K		151
#घोषणा UART5_K		152
#घोषणा USART6_K	153
#घोषणा UART7_K		154
#घोषणा UART8_K		155
#घोषणा DFSDM_K		156
#घोषणा FDCAN_K		157
#घोषणा SAI1_K		158
#घोषणा SAI2_K		159
#घोषणा SAI3_K		160
#घोषणा SAI4_K		161
#घोषणा ADC12_K		162
#घोषणा DSI_K		163
#घोषणा DSI_PX		164
#घोषणा ADFSDM_K	165
#घोषणा USBO_K		166
#घोषणा LTDC_PX		167
#घोषणा DAC12_K		168
#घोषणा ETHPTP_K	169

/* PLL */
#घोषणा PLL1		176
#घोषणा PLL2		177
#घोषणा PLL3		178
#घोषणा PLL4		179

/* ODF */
#घोषणा PLL1_P		180
#घोषणा PLL1_Q		181
#घोषणा PLL1_R		182
#घोषणा PLL2_P		183
#घोषणा PLL2_Q		184
#घोषणा PLL2_R		185
#घोषणा PLL3_P		186
#घोषणा PLL3_Q		187
#घोषणा PLL3_R		188
#घोषणा PLL4_P		189
#घोषणा PLL4_Q		190
#घोषणा PLL4_R		191

/* AUX */
#घोषणा RTC		192

/* MCLK */
#घोषणा CK_PER		193
#घोषणा CK_MPU		194
#घोषणा CK_AXI		195
#घोषणा CK_MCU		196

/* Time base */
#घोषणा TIM2_K		197
#घोषणा TIM3_K		198
#घोषणा TIM4_K		199
#घोषणा TIM5_K		200
#घोषणा TIM6_K		201
#घोषणा TIM7_K		202
#घोषणा TIM12_K		203
#घोषणा TIM13_K		204
#घोषणा TIM14_K		205
#घोषणा TIM1_K		206
#घोषणा TIM8_K		207
#घोषणा TIM15_K		208
#घोषणा TIM16_K		209
#घोषणा TIM17_K		210

/* MCO घड़ीs */
#घोषणा CK_MCO1		211
#घोषणा CK_MCO2		212

/* TRACE & DEBUG घड़ीs */
#घोषणा CK_DBG		214
#घोषणा CK_TRACE	215

/* DDR */
#घोषणा DDRC1		220
#घोषणा DDRC1LP		221
#घोषणा DDRC2		222
#घोषणा DDRC2LP		223
#घोषणा DDRPHYC		224
#घोषणा DDRPHYCLP	225
#घोषणा DDRCAPB		226
#घोषणा DDRCAPBLP	227
#घोषणा AXIDCG		228
#घोषणा DDRPHYCAPB	229
#घोषणा DDRPHYCAPBLP	230
#घोषणा DDRPERFM	231

#घोषणा STM32MP1_LAST_CLK 232

#पूर्ण_अगर /* _DT_BINDINGS_STM32MP1_CLKS_H_ */
