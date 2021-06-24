<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2016 Rockchip Electronics Co. Ltd.
 * Author: Shawn Lin <shawn.lin@rock-chips.com>
 */

#अगर_अघोषित _DT_BINDINGS_CLK_ROCKCHIP_RV1108_H
#घोषणा _DT_BINDINGS_CLK_ROCKCHIP_RV1108_H

/* pll id */
#घोषणा PLL_APLL			0
#घोषणा PLL_DPLL			1
#घोषणा PLL_GPLL			2
#घोषणा ARMCLK				3

/* sclk gates (special घड़ीs) */
#घोषणा SCLK_SPI0			65
#घोषणा SCLK_न_अंकDC			67
#घोषणा SCLK_SDMMC			68
#घोषणा SCLK_SDIO			69
#घोषणा SCLK_EMMC			71
#घोषणा SCLK_UART0			72
#घोषणा SCLK_UART1			73
#घोषणा SCLK_UART2			74
#घोषणा SCLK_I2S0			75
#घोषणा SCLK_I2S1			76
#घोषणा SCLK_I2S2			77
#घोषणा SCLK_TIMER0			78
#घोषणा SCLK_TIMER1			79
#घोषणा SCLK_SFC			80
#घोषणा SCLK_SDMMC_DRV			81
#घोषणा SCLK_SDIO_DRV			82
#घोषणा SCLK_EMMC_DRV			83
#घोषणा SCLK_SDMMC_SAMPLE		84
#घोषणा SCLK_SDIO_SAMPLE		85
#घोषणा SCLK_EMMC_SAMPLE		86
#घोषणा SCLK_VENC_CORE			87
#घोषणा SCLK_HEVC_CORE			88
#घोषणा SCLK_HEVC_CABAC			89
#घोषणा SCLK_PWM0_PMU			90
#घोषणा SCLK_I2C0_PMU			91
#घोषणा SCLK_WIFI			92
#घोषणा SCLK_CIFOUT			93
#घोषणा SCLK_MIPI_CSI_OUT		94
#घोषणा SCLK_CIF0			95
#घोषणा SCLK_CIF1			96
#घोषणा SCLK_CIF2			97
#घोषणा SCLK_CIF3			98
#घोषणा SCLK_DSP			99
#घोषणा SCLK_DSP_IOP			100
#घोषणा SCLK_DSP_EPP			101
#घोषणा SCLK_DSP_EDP			102
#घोषणा SCLK_DSP_EDAP			103
#घोषणा SCLK_CVBS_HOST			104
#घोषणा SCLK_HDMI_SFR			105
#घोषणा SCLK_HDMI_CEC			106
#घोषणा SCLK_CRYPTO			107
#घोषणा SCLK_SPI			108
#घोषणा SCLK_SARADC			109
#घोषणा SCLK_TSADC			110
#घोषणा SCLK_MAC_PRE			111
#घोषणा SCLK_MAC			112
#घोषणा SCLK_MAC_RX			113
#घोषणा SCLK_MAC_REF			114
#घोषणा SCLK_MAC_REFOUT			115
#घोषणा SCLK_DSP_PFM			116
#घोषणा SCLK_RGA			117
#घोषणा SCLK_I2C1			118
#घोषणा SCLK_I2C2			119
#घोषणा SCLK_I2C3			120
#घोषणा SCLK_PWM			121
#घोषणा SCLK_ISP			122
#घोषणा SCLK_USBPHY			123
#घोषणा SCLK_I2S0_SRC			124
#घोषणा SCLK_I2S1_SRC			125
#घोषणा SCLK_I2S2_SRC			126
#घोषणा SCLK_UART0_SRC			127
#घोषणा SCLK_UART1_SRC			128
#घोषणा SCLK_UART2_SRC			129

#घोषणा DCLK_VOP_SRC			185
#घोषणा DCLK_HDMIPHY			186
#घोषणा DCLK_VOP			187

/* aclk gates */
#घोषणा ACLK_DMAC			192
#घोषणा ACLK_PRE			193
#घोषणा ACLK_CORE			194
#घोषणा ACLK_ENMCORE			195
#घोषणा ACLK_RKVENC			196
#घोषणा ACLK_RKVDEC			197
#घोषणा ACLK_VPU			198
#घोषणा ACLK_CIF0			199
#घोषणा ACLK_VIO0			200
#घोषणा ACLK_VIO1			201
#घोषणा ACLK_VOP			202
#घोषणा ACLK_IEP			203
#घोषणा ACLK_RGA			204
#घोषणा ACLK_ISP			205
#घोषणा ACLK_CIF1			206
#घोषणा ACLK_CIF2			207
#घोषणा ACLK_CIF3			208
#घोषणा ACLK_PERI			209
#घोषणा ACLK_GMAC			210

/* pclk gates */
#घोषणा PCLK_GPIO1			256
#घोषणा PCLK_GPIO2			257
#घोषणा PCLK_GPIO3			258
#घोषणा PCLK_GRF			259
#घोषणा PCLK_I2C1			260
#घोषणा PCLK_I2C2			261
#घोषणा PCLK_I2C3			262
#घोषणा PCLK_SPI			263
#घोषणा PCLK_SFC			264
#घोषणा PCLK_UART0			265
#घोषणा PCLK_UART1			266
#घोषणा PCLK_UART2			267
#घोषणा PCLK_TSADC			268
#घोषणा PCLK_PWM			269
#घोषणा PCLK_TIMER			270
#घोषणा PCLK_PERI			271
#घोषणा PCLK_GPIO0_PMU			272
#घोषणा PCLK_I2C0_PMU			273
#घोषणा PCLK_PWM0_PMU			274
#घोषणा PCLK_ISP			275
#घोषणा PCLK_VIO			276
#घोषणा PCLK_MIPI_DSI			277
#घोषणा PCLK_HDMI_CTRL			278
#घोषणा PCLK_SARADC			279
#घोषणा PCLK_DSP_CFG			280
#घोषणा PCLK_BUS			281
#घोषणा PCLK_EFUSE0			282
#घोषणा PCLK_EFUSE1			283
#घोषणा PCLK_WDT			284
#घोषणा PCLK_GMAC			285

/* hclk gates */
#घोषणा HCLK_I2S0_8CH			320
#घोषणा HCLK_I2S1_2CH			321
#घोषणा HCLK_I2S2_2CH			322
#घोषणा HCLK_न_अंकDC			323
#घोषणा HCLK_SDMMC			324
#घोषणा HCLK_SDIO			325
#घोषणा HCLK_EMMC			326
#घोषणा HCLK_PERI			327
#घोषणा HCLK_SFC			328
#घोषणा HCLK_RKVENC			329
#घोषणा HCLK_RKVDEC			330
#घोषणा HCLK_CIF0			331
#घोषणा HCLK_VIO			332
#घोषणा HCLK_VOP			333
#घोषणा HCLK_IEP			334
#घोषणा HCLK_RGA			335
#घोषणा HCLK_ISP			336
#घोषणा HCLK_CRYPTO_MST			337
#घोषणा HCLK_CRYPTO_SLV			338
#घोषणा HCLK_HOST0			339
#घोषणा HCLK_OTG			340
#घोषणा HCLK_CIF1			341
#घोषणा HCLK_CIF2			342
#घोषणा HCLK_CIF3			343
#घोषणा HCLK_BUS			344
#घोषणा HCLK_VPU			345

#घोषणा CLK_NR_CLKS			(HCLK_VPU + 1)

/* reset id */
#घोषणा SRST_CORE_PO_AD			0
#घोषणा SRST_CORE_AD			1
#घोषणा SRST_L2_AD			2
#घोषणा SRST_CPU_NIU_AD			3
#घोषणा SRST_CORE_PO			4
#घोषणा SRST_CORE			5
#घोषणा SRST_L2				6
#घोषणा SRST_CORE_DBG			8
#घोषणा PRST_DBG			9
#घोषणा RST_DAP				10
#घोषणा PRST_DBG_NIU			11
#घोषणा ARST_STRC_SYS_AD		15

#घोषणा SRST_DDRPHY_CLKDIV		16
#घोषणा SRST_DDRPHY			17
#घोषणा PRST_DDRPHY			18
#घोषणा PRST_HDMIPHY			19
#घोषणा PRST_VDACPHY			20
#घोषणा PRST_VADCPHY			21
#घोषणा PRST_MIPI_CSI_PHY		22
#घोषणा PRST_MIPI_DSI_PHY		23
#घोषणा PRST_ACODEC			24
#घोषणा ARST_BUS_NIU			25
#घोषणा PRST_TOP_NIU			26
#घोषणा ARST_INTMEM			27
#घोषणा HRST_ROM			28
#घोषणा ARST_DMAC			29
#घोषणा SRST_MSCH_NIU			30
#घोषणा PRST_MSCH_NIU			31

#घोषणा PRST_DDRUPCTL			32
#घोषणा NRST_DDRUPCTL			33
#घोषणा PRST_DDRMON			34
#घोषणा HRST_I2S0_8CH			35
#घोषणा MRST_I2S0_8CH			36
#घोषणा HRST_I2S1_2CH			37
#घोषणा MRST_IS21_2CH			38
#घोषणा HRST_I2S2_2CH			39
#घोषणा MRST_I2S2_2CH			40
#घोषणा HRST_CRYPTO			41
#घोषणा SRST_CRYPTO			42
#घोषणा PRST_SPI			43
#घोषणा SRST_SPI			44
#घोषणा PRST_UART0			45
#घोषणा PRST_UART1			46
#घोषणा PRST_UART2			47

#घोषणा SRST_UART0			48
#घोषणा SRST_UART1			49
#घोषणा SRST_UART2			50
#घोषणा PRST_I2C1			51
#घोषणा PRST_I2C2			52
#घोषणा PRST_I2C3			53
#घोषणा SRST_I2C1			54
#घोषणा SRST_I2C2			55
#घोषणा SRST_I2C3			56
#घोषणा PRST_PWM1			58
#घोषणा SRST_PWM1			60
#घोषणा PRST_WDT			61
#घोषणा PRST_GPIO1			62
#घोषणा PRST_GPIO2			63

#घोषणा PRST_GPIO3			64
#घोषणा PRST_GRF			65
#घोषणा PRST_EFUSE			66
#घोषणा PRST_EFUSE512			67
#घोषणा PRST_TIMER0			68
#घोषणा SRST_TIMER0			69
#घोषणा SRST_TIMER1			70
#घोषणा PRST_TSADC			71
#घोषणा SRST_TSADC			72
#घोषणा PRST_SARADC			73
#घोषणा SRST_SARADC			74
#घोषणा HRST_SYSBUS			75
#घोषणा PRST_USBGRF			76

#घोषणा ARST_PERIPH_NIU			80
#घोषणा HRST_PERIPH_NIU			81
#घोषणा PRST_PERIPH_NIU			82
#घोषणा HRST_PERIPH			83
#घोषणा HRST_SDMMC			84
#घोषणा HRST_SDIO			85
#घोषणा HRST_EMMC			86
#घोषणा HRST_न_अंकDC			87
#घोषणा NRST_न_अंकDC			88
#घोषणा HRST_SFC			89
#घोषणा SRST_SFC			90
#घोषणा ARST_GMAC			91
#घोषणा HRST_OTG			92
#घोषणा SRST_OTG			93
#घोषणा SRST_OTG_ADP			94
#घोषणा HRST_HOST0			95

#घोषणा HRST_HOST0_AUX			96
#घोषणा HRST_HOST0_ARB			97
#घोषणा SRST_HOST0_EHCIPHY		98
#घोषणा SRST_HOST0_UTMI			99
#घोषणा SRST_USBPOR			100
#घोषणा SRST_UTMI0			101
#घोषणा SRST_UTMI1			102

#घोषणा ARST_VIO0_NIU			102
#घोषणा ARST_VIO1_NIU			103
#घोषणा HRST_VIO_NIU			104
#घोषणा PRST_VIO_NIU			105
#घोषणा ARST_VOP			106
#घोषणा HRST_VOP			107
#घोषणा DRST_VOP			108
#घोषणा ARST_IEP			109
#घोषणा HRST_IEP			110
#घोषणा ARST_RGA			111
#घोषणा HRST_RGA			112
#घोषणा SRST_RGA			113
#घोषणा PRST_CVBS			114
#घोषणा PRST_HDMI			115
#घोषणा SRST_HDMI			116
#घोषणा PRST_MIPI_DSI			117

#घोषणा ARST_ISP_NIU			118
#घोषणा HRST_ISP_NIU			119
#घोषणा HRST_ISP			120
#घोषणा SRST_ISP			121
#घोषणा ARST_VIP0			122
#घोषणा HRST_VIP0			123
#घोषणा PRST_VIP0			124
#घोषणा ARST_VIP1			125
#घोषणा HRST_VIP1			126
#घोषणा PRST_VIP1			127
#घोषणा ARST_VIP2			128
#घोषणा HRST_VIP2			129
#घोषणा PRST_VIP2			120
#घोषणा ARST_VIP3			121
#घोषणा HRST_VIP3			122
#घोषणा PRST_VIP4			123

#घोषणा PRST_CIF1TO4			124
#घोषणा SRST_CVBS_CLK			125
#घोषणा HRST_CVBS			126

#घोषणा ARST_VPU_NIU			140
#घोषणा HRST_VPU_NIU			141
#घोषणा ARST_VPU			142
#घोषणा HRST_VPU			143
#घोषणा ARST_RKVDEC_NIU			144
#घोषणा HRST_RKVDEC_NIU			145
#घोषणा ARST_RKVDEC			146
#घोषणा HRST_RKVDEC			147
#घोषणा SRST_RKVDEC_CABAC		148
#घोषणा SRST_RKVDEC_CORE		149
#घोषणा ARST_RKVENC_NIU			150
#घोषणा HRST_RKVENC_NIU			151
#घोषणा ARST_RKVENC			152
#घोषणा HRST_RKVENC			153
#घोषणा SRST_RKVENC_CORE		154

#घोषणा SRST_DSP_CORE			156
#घोषणा SRST_DSP_SYS			157
#घोषणा SRST_DSP_GLOBAL			158
#घोषणा SRST_DSP_OECM			159
#घोषणा PRST_DSP_IOP_NIU		160
#घोषणा ARST_DSP_EPP_NIU		161
#घोषणा ARST_DSP_EDP_NIU		162
#घोषणा PRST_DSP_DBG_NIU		163
#घोषणा PRST_DSP_CFG_NIU		164
#घोषणा PRST_DSP_GRF			165
#घोषणा PRST_DSP_MAILBOX		166
#घोषणा PRST_DSP_INTC			167
#घोषणा PRST_DSP_PFM_MON		169
#घोषणा SRST_DSP_PFM_MON		170
#घोषणा ARST_DSP_EDAP_NIU		171

#घोषणा SRST_PMU			172
#घोषणा SRST_PMU_I2C0			173
#घोषणा PRST_PMU_I2C0			174
#घोषणा PRST_PMU_GPIO0			175
#घोषणा PRST_PMU_INTMEM			176
#घोषणा PRST_PMU_PWM0			177
#घोषणा SRST_PMU_PWM0			178
#घोषणा PRST_PMU_GRF			179
#घोषणा SRST_PMU_NIU			180
#घोषणा SRST_PMU_PVTM			181
#घोषणा ARST_DSP_EDP_PERF		184
#घोषणा ARST_DSP_EPP_PERF		185

#पूर्ण_अगर /* _DT_BINDINGS_CLK_ROCKCHIP_RV1108_H */
