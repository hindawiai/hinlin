<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Tomasz Figa <tomasz.figa at gmail.com>
 *
 * Device Tree binding स्थिरants क्रम Samsung S3C64xx घड़ी controller.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_SAMSUNG_S3C64XX_CLOCK_H
#घोषणा _DT_BINDINGS_CLOCK_SAMSUNG_S3C64XX_CLOCK_H

/*
 * Let each exported घड़ी get a unique index, which is used on DT-enabled
 * platक्रमms to lookup the घड़ी from a घड़ी specअगरier. These indices are
 * thereक्रमe considered an ABI and so must not be changed. This implies
 * that new घड़ीs should be added either in मुक्त spaces between घड़ी groups
 * or at the end.
 */

/* Core घड़ीs. */
#घोषणा CLK27M			1
#घोषणा CLK48M			2
#घोषणा FOUT_APLL		3
#घोषणा FOUT_MPLL		4
#घोषणा FOUT_EPLL		5
#घोषणा ARMCLK			6
#घोषणा HCLKX2			7
#घोषणा HCLK			8
#घोषणा PCLK			9

/* HCLK bus घड़ीs. */
#घोषणा HCLK_3DSE		16
#घोषणा HCLK_UHOST		17
#घोषणा HCLK_SECUR		18
#घोषणा HCLK_SDMA1		19
#घोषणा HCLK_SDMA0		20
#घोषणा HCLK_IROM		21
#घोषणा HCLK_DDR1		22
#घोषणा HCLK_MEM1		23
#घोषणा HCLK_MEM0		24
#घोषणा HCLK_USB		25
#घोषणा HCLK_HSMMC2		26
#घोषणा HCLK_HSMMC1		27
#घोषणा HCLK_HSMMC0		28
#घोषणा HCLK_MDP		29
#घोषणा HCLK_DHOST		30
#घोषणा HCLK_IHOST		31
#घोषणा HCLK_DMA1		32
#घोषणा HCLK_DMA0		33
#घोषणा HCLK_JPEG		34
#घोषणा HCLK_CAMIF		35
#घोषणा HCLK_SCALER		36
#घोषणा HCLK_2D			37
#घोषणा HCLK_TV			38
#घोषणा HCLK_POST0		39
#घोषणा HCLK_ROT		40
#घोषणा HCLK_LCD		41
#घोषणा HCLK_TZIC		42
#घोषणा HCLK_INTC		43
#घोषणा HCLK_MFC		44
#घोषणा HCLK_DDR0		45

/* PCLK bus घड़ीs. */
#घोषणा PCLK_IIC1		48
#घोषणा PCLK_IIS2		49
#घोषणा PCLK_SKEY		50
#घोषणा PCLK_CHIPID		51
#घोषणा PCLK_SPI1		52
#घोषणा PCLK_SPI0		53
#घोषणा PCLK_HSIRX		54
#घोषणा PCLK_HSITX		55
#घोषणा PCLK_GPIO		56
#घोषणा PCLK_IIC0		57
#घोषणा PCLK_IIS1		58
#घोषणा PCLK_IIS0		59
#घोषणा PCLK_AC97		60
#घोषणा PCLK_TZPC		61
#घोषणा PCLK_TSADC		62
#घोषणा PCLK_KEYPAD		63
#घोषणा PCLK_IRDA		64
#घोषणा PCLK_PCM1		65
#घोषणा PCLK_PCM0		66
#घोषणा PCLK_PWM		67
#घोषणा PCLK_RTC		68
#घोषणा PCLK_WDT		69
#घोषणा PCLK_UART3		70
#घोषणा PCLK_UART2		71
#घोषणा PCLK_UART1		72
#घोषणा PCLK_UART0		73
#घोषणा PCLK_MFC		74

/* Special घड़ीs. */
#घोषणा SCLK_UHOST		80
#घोषणा SCLK_MMC2_48		81
#घोषणा SCLK_MMC1_48		82
#घोषणा SCLK_MMC0_48		83
#घोषणा SCLK_MMC2		84
#घोषणा SCLK_MMC1		85
#घोषणा SCLK_MMC0		86
#घोषणा SCLK_SPI1_48		87
#घोषणा SCLK_SPI0_48		88
#घोषणा SCLK_SPI1		89
#घोषणा SCLK_SPI0		90
#घोषणा SCLK_DAC27		91
#घोषणा SCLK_TV27		92
#घोषणा SCLK_SCALER27		93
#घोषणा SCLK_SCALER		94
#घोषणा SCLK_LCD27		95
#घोषणा SCLK_LCD		96
#घोषणा SCLK_FIMC		97
#घोषणा SCLK_POST0_27		98
#घोषणा SCLK_AUDIO2		99
#घोषणा SCLK_POST0		100
#घोषणा SCLK_AUDIO1		101
#घोषणा SCLK_AUDIO0		102
#घोषणा SCLK_SECUR		103
#घोषणा SCLK_IRDA		104
#घोषणा SCLK_UART		105
#घोषणा SCLK_MFC		106
#घोषणा SCLK_CAM		107
#घोषणा SCLK_JPEG		108
#घोषणा SCLK_ONEन_अंकD		109

/* MEM0 bus घड़ीs - S3C6410-specअगरic. */
#घोषणा MEM0_CFCON		112
#घोषणा MEM0_ONEन_अंकD1		113
#घोषणा MEM0_ONEन_अंकD0		114
#घोषणा MEM0_NFCON		115
#घोषणा MEM0_SROM		116

/* Muxes. */
#घोषणा MOUT_APLL		128
#घोषणा MOUT_MPLL		129
#घोषणा MOUT_EPLL		130
#घोषणा MOUT_MFC		131
#घोषणा MOUT_AUDIO0		132
#घोषणा MOUT_AUDIO1		133
#घोषणा MOUT_UART		134
#घोषणा MOUT_SPI0		135
#घोषणा MOUT_SPI1		136
#घोषणा MOUT_MMC0		137
#घोषणा MOUT_MMC1		138
#घोषणा MOUT_MMC2		139
#घोषणा MOUT_UHOST		140
#घोषणा MOUT_IRDA		141
#घोषणा MOUT_LCD		142
#घोषणा MOUT_SCALER		143
#घोषणा MOUT_DAC27		144
#घोषणा MOUT_TV27		145
#घोषणा MOUT_AUDIO2		146

/* Dividers. */
#घोषणा DOUT_MPLL		160
#घोषणा DOUT_SECUR		161
#घोषणा DOUT_CAM		162
#घोषणा DOUT_JPEG		163
#घोषणा DOUT_MFC		164
#घोषणा DOUT_MMC0		165
#घोषणा DOUT_MMC1		166
#घोषणा DOUT_MMC2		167
#घोषणा DOUT_LCD		168
#घोषणा DOUT_SCALER		169
#घोषणा DOUT_UHOST		170
#घोषणा DOUT_SPI0		171
#घोषणा DOUT_SPI1		172
#घोषणा DOUT_AUDIO0		173
#घोषणा DOUT_AUDIO1		174
#घोषणा DOUT_UART		175
#घोषणा DOUT_IRDA		176
#घोषणा DOUT_FIMC		177
#घोषणा DOUT_AUDIO2		178

/* Total number of घड़ीs. */
#घोषणा NR_CLKS			(DOUT_AUDIO2 + 1)

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_SAMSUNG_S3C64XX_CLOCK_H */
