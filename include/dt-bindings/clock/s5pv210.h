<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Author: Mateusz Krawczuk <m.krawczuk@partner.samsung.com>
 *
 * Device Tree binding स्थिरants क्रम Samsung S5PV210 घड़ी controller.
 */

#अगर_अघोषित _DT_BINDINGS_CLOCK_S5PV210_H
#घोषणा _DT_BINDINGS_CLOCK_S5PV210_H

/* Core घड़ीs. */
#घोषणा FIN_PLL			1
#घोषणा FOUT_APLL		2
#घोषणा FOUT_MPLL		3
#घोषणा FOUT_EPLL		4
#घोषणा FOUT_VPLL		5

/* Muxes. */
#घोषणा MOUT_FLASH		6
#घोषणा MOUT_PSYS		7
#घोषणा MOUT_DSYS		8
#घोषणा MOUT_MSYS		9
#घोषणा MOUT_VPLL		10
#घोषणा MOUT_EPLL		11
#घोषणा MOUT_MPLL		12
#घोषणा MOUT_APLL		13
#घोषणा MOUT_VPLLSRC		14
#घोषणा MOUT_CSIS		15
#घोषणा MOUT_FIMD		16
#घोषणा MOUT_CAM1		17
#घोषणा MOUT_CAM0		18
#घोषणा MOUT_DAC		19
#घोषणा MOUT_MIXER		20
#घोषणा MOUT_HDMI		21
#घोषणा MOUT_G2D		22
#घोषणा MOUT_MFC		23
#घोषणा MOUT_G3D		24
#घोषणा MOUT_FIMC2		25
#घोषणा MOUT_FIMC1		26
#घोषणा MOUT_FIMC0		27
#घोषणा MOUT_UART3		28
#घोषणा MOUT_UART2		29
#घोषणा MOUT_UART1		30
#घोषणा MOUT_UART0		31
#घोषणा MOUT_MMC3		32
#घोषणा MOUT_MMC2		33
#घोषणा MOUT_MMC1		34
#घोषणा MOUT_MMC0		35
#घोषणा MOUT_PWM		36
#घोषणा MOUT_SPI0		37
#घोषणा MOUT_SPI1		38
#घोषणा MOUT_DMC0		39
#घोषणा MOUT_PWI		40
#घोषणा MOUT_HPM		41
#घोषणा MOUT_SPDIF		42
#घोषणा MOUT_AUDIO2		43
#घोषणा MOUT_AUDIO1		44
#घोषणा MOUT_AUDIO0		45

/* Dividers. */
#घोषणा DOUT_PCLKP		46
#घोषणा DOUT_HCLKP		47
#घोषणा DOUT_PCLKD		48
#घोषणा DOUT_HCLKD		49
#घोषणा DOUT_PCLKM		50
#घोषणा DOUT_HCLKM		51
#घोषणा DOUT_A2M		52
#घोषणा DOUT_APLL		53
#घोषणा DOUT_CSIS		54
#घोषणा DOUT_FIMD		55
#घोषणा DOUT_CAM1		56
#घोषणा DOUT_CAM0		57
#घोषणा DOUT_TBLK		58
#घोषणा DOUT_G2D		59
#घोषणा DOUT_MFC		60
#घोषणा DOUT_G3D		61
#घोषणा DOUT_FIMC2		62
#घोषणा DOUT_FIMC1		63
#घोषणा DOUT_FIMC0		64
#घोषणा DOUT_UART3		65
#घोषणा DOUT_UART2		66
#घोषणा DOUT_UART1		67
#घोषणा DOUT_UART0		68
#घोषणा DOUT_MMC3		69
#घोषणा DOUT_MMC2		70
#घोषणा DOUT_MMC1		71
#घोषणा DOUT_MMC0		72
#घोषणा DOUT_PWM		73
#घोषणा DOUT_SPI1		74
#घोषणा DOUT_SPI0		75
#घोषणा DOUT_DMC0		76
#घोषणा DOUT_PWI		77
#घोषणा DOUT_HPM		78
#घोषणा DOUT_COPY		79
#घोषणा DOUT_FLASH		80
#घोषणा DOUT_AUDIO2		81
#घोषणा DOUT_AUDIO1		82
#घोषणा DOUT_AUDIO0		83
#घोषणा DOUT_DPM		84
#घोषणा DOUT_DVSEM		85

/* Gates */
#घोषणा SCLK_FIMC		86
#घोषणा CLK_CSIS		87
#घोषणा CLK_ROTATOR		88
#घोषणा CLK_FIMC2		89
#घोषणा CLK_FIMC1		90
#घोषणा CLK_FIMC0		91
#घोषणा CLK_MFC			92
#घोषणा CLK_G2D			93
#घोषणा CLK_G3D			94
#घोषणा CLK_IMEM		95
#घोषणा CLK_PDMA1		96
#घोषणा CLK_PDMA0		97
#घोषणा CLK_MDMA		98
#घोषणा CLK_DMC1		99
#घोषणा CLK_DMC0		100
#घोषणा CLK_NFCON		101
#घोषणा CLK_SROMC		102
#घोषणा CLK_CFCON		103
#घोषणा CLK_न_अंकDXL		104
#घोषणा CLK_USB_HOST		105
#घोषणा CLK_USB_OTG		106
#घोषणा CLK_HDMI		107
#घोषणा CLK_TVENC		108
#घोषणा CLK_MIXER		109
#घोषणा CLK_VP			110
#घोषणा CLK_DSIM		111
#घोषणा CLK_FIMD		112
#घोषणा CLK_TZIC3		113
#घोषणा CLK_TZIC2		114
#घोषणा CLK_TZIC1		115
#घोषणा CLK_TZIC0		116
#घोषणा CLK_VIC3		117
#घोषणा CLK_VIC2		118
#घोषणा CLK_VIC1		119
#घोषणा CLK_VIC0		120
#घोषणा CLK_TSI			121
#घोषणा CLK_HSMMC3		122
#घोषणा CLK_HSMMC2		123
#घोषणा CLK_HSMMC1		124
#घोषणा CLK_HSMMC0		125
#घोषणा CLK_JTAG		126
#घोषणा CLK_MODEMIF		127
#घोषणा CLK_CORESIGHT		128
#घोषणा CLK_SDM			129
#घोषणा CLK_SECSS		130
#घोषणा CLK_PCM2		131
#घोषणा CLK_PCM1		132
#घोषणा CLK_PCM0		133
#घोषणा CLK_SYSCON		134
#घोषणा CLK_GPIO		135
#घोषणा CLK_TSADC		136
#घोषणा CLK_PWM			137
#घोषणा CLK_WDT			138
#घोषणा CLK_KEYIF		139
#घोषणा CLK_UART3		140
#घोषणा CLK_UART2		141
#घोषणा CLK_UART1		142
#घोषणा CLK_UART0		143
#घोषणा CLK_SYSTIMER		144
#घोषणा CLK_RTC			145
#घोषणा CLK_SPI1		146
#घोषणा CLK_SPI0		147
#घोषणा CLK_I2C_HDMI_PHY	148
#घोषणा CLK_I2C1		149
#घोषणा CLK_I2C2		150
#घोषणा CLK_I2C0		151
#घोषणा CLK_I2S1		152
#घोषणा CLK_I2S2		153
#घोषणा CLK_I2S0		154
#घोषणा CLK_AC97		155
#घोषणा CLK_SPDIF		156
#घोषणा CLK_TZPC3		157
#घोषणा CLK_TZPC2		158
#घोषणा CLK_TZPC1		159
#घोषणा CLK_TZPC0		160
#घोषणा CLK_SECKEY		161
#घोषणा CLK_IEM_APC		162
#घोषणा CLK_IEM_IEC		163
#घोषणा CLK_CHIPID		164
#घोषणा CLK_JPEG		163

/* Special घड़ीs*/
#घोषणा SCLK_PWI		164
#घोषणा SCLK_SPDIF		165
#घोषणा SCLK_AUDIO2		166
#घोषणा SCLK_AUDIO1		167
#घोषणा SCLK_AUDIO0		168
#घोषणा SCLK_PWM		169
#घोषणा SCLK_SPI1		170
#घोषणा SCLK_SPI0		171
#घोषणा SCLK_UART3		172
#घोषणा SCLK_UART2		173
#घोषणा SCLK_UART1		174
#घोषणा SCLK_UART0		175
#घोषणा SCLK_MMC3		176
#घोषणा SCLK_MMC2		177
#घोषणा SCLK_MMC1		178
#घोषणा SCLK_MMC0		179
#घोषणा SCLK_FINVPLL		180
#घोषणा SCLK_CSIS		181
#घोषणा SCLK_FIMD		182
#घोषणा SCLK_CAM1		183
#घोषणा SCLK_CAM0		184
#घोषणा SCLK_DAC		185
#घोषणा SCLK_MIXER		186
#घोषणा SCLK_HDMI		187
#घोषणा SCLK_FIMC2		188
#घोषणा SCLK_FIMC1		189
#घोषणा SCLK_FIMC0		190
#घोषणा SCLK_HDMI27M		191
#घोषणा SCLK_HDMIPHY		192
#घोषणा SCLK_USBPHY0		193
#घोषणा SCLK_USBPHY1		194

/* S5P6442-specअगरic घड़ीs */
#घोषणा MOUT_D0SYNC		195
#घोषणा MOUT_D1SYNC		196
#घोषणा DOUT_MIXER		197
#घोषणा CLK_ETB			198
#घोषणा CLK_ETM			199

/* CLKOUT */
#घोषणा FOUT_APLL_CLKOUT	200
#घोषणा FOUT_MPLL_CLKOUT	201
#घोषणा DOUT_APLL_CLKOUT	202
#घोषणा MOUT_CLKSEL		203
#घोषणा DOUT_CLKOUT		204
#घोषणा MOUT_CLKOUT		205

/* Total number of घड़ीs. */
#घोषणा NR_CLKS			206

#पूर्ण_अगर /* _DT_BINDINGS_CLOCK_S5PV210_H */
