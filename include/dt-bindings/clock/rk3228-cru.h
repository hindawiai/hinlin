<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2015 Rockchip Electronics Co. Ltd.
 * Author: Jeffy Chen <jeffy.chen@rock-chips.com>
 */

#अगर_अघोषित _DT_BINDINGS_CLK_ROCKCHIP_RK3228_H
#घोषणा _DT_BINDINGS_CLK_ROCKCHIP_RK3228_H

/* core घड़ीs */
#घोषणा PLL_APLL		1
#घोषणा PLL_DPLL		2
#घोषणा PLL_CPLL		3
#घोषणा PLL_GPLL		4
#घोषणा ARMCLK			5

/* sclk gates (special घड़ीs) */
#घोषणा SCLK_SPI0		65
#घोषणा SCLK_न_अंकDC		67
#घोषणा SCLK_SDMMC		68
#घोषणा SCLK_SDIO		69
#घोषणा SCLK_EMMC		71
#घोषणा SCLK_TSADC		72
#घोषणा SCLK_UART0		77
#घोषणा SCLK_UART1		78
#घोषणा SCLK_UART2		79
#घोषणा SCLK_I2S0		80
#घोषणा SCLK_I2S1		81
#घोषणा SCLK_I2S2		82
#घोषणा SCLK_SPDIF		83
#घोषणा SCLK_TIMER0		85
#घोषणा SCLK_TIMER1		86
#घोषणा SCLK_TIMER2		87
#घोषणा SCLK_TIMER3		88
#घोषणा SCLK_TIMER4		89
#घोषणा SCLK_TIMER5		90
#घोषणा SCLK_I2S_OUT		113
#घोषणा SCLK_SDMMC_DRV		114
#घोषणा SCLK_SDIO_DRV		115
#घोषणा SCLK_EMMC_DRV		117
#घोषणा SCLK_SDMMC_SAMPLE	118
#घोषणा SCLK_SDIO_SAMPLE	119
#घोषणा SCLK_SDIO_SRC		120
#घोषणा SCLK_EMMC_SAMPLE	121
#घोषणा SCLK_VOP		122
#घोषणा SCLK_HDMI_HDCP		123
#घोषणा SCLK_MAC_SRC		124
#घोषणा SCLK_MAC_EXTCLK		125
#घोषणा SCLK_MAC		126
#घोषणा SCLK_MAC_REFOUT		127
#घोषणा SCLK_MAC_REF		128
#घोषणा SCLK_MAC_RX		129
#घोषणा SCLK_MAC_TX		130
#घोषणा SCLK_MAC_PHY		131
#घोषणा SCLK_MAC_OUT		132
#घोषणा SCLK_VDEC_CABAC		133
#घोषणा SCLK_VDEC_CORE		134
#घोषणा SCLK_RGA		135
#घोषणा SCLK_HDCP		136
#घोषणा SCLK_HDMI_CEC		137
#घोषणा SCLK_CRYPTO		138
#घोषणा SCLK_TSP		139
#घोषणा SCLK_HSADC		140
#घोषणा SCLK_WIFI		141
#घोषणा SCLK_OTGPHY0		142
#घोषणा SCLK_OTGPHY1		143
#घोषणा SCLK_HDMI_PHY		144

/* dclk gates */
#घोषणा DCLK_VOP		190
#घोषणा DCLK_HDMI_PHY		191

/* aclk gates */
#घोषणा ACLK_DMAC		194
#घोषणा ACLK_CPU		195
#घोषणा ACLK_VPU_PRE		196
#घोषणा ACLK_RKVDEC_PRE		197
#घोषणा ACLK_RGA_PRE		198
#घोषणा ACLK_IEP_PRE		199
#घोषणा ACLK_HDCP_PRE		200
#घोषणा ACLK_VOP_PRE		201
#घोषणा ACLK_VPU		202
#घोषणा ACLK_RKVDEC		203
#घोषणा ACLK_IEP		204
#घोषणा ACLK_RGA		205
#घोषणा ACLK_HDCP		206
#घोषणा ACLK_PERI		210
#घोषणा ACLK_VOP		211
#घोषणा ACLK_GMAC		212
#घोषणा ACLK_GPU		213

/* pclk gates */
#घोषणा PCLK_GPIO0		320
#घोषणा PCLK_GPIO1		321
#घोषणा PCLK_GPIO2		322
#घोषणा PCLK_GPIO3		323
#घोषणा PCLK_VIO_H2P		324
#घोषणा PCLK_HDCP		325
#घोषणा PCLK_EFUSE_1024		326
#घोषणा PCLK_EFUSE_256		327
#घोषणा PCLK_GRF		329
#घोषणा PCLK_I2C0		332
#घोषणा PCLK_I2C1		333
#घोषणा PCLK_I2C2		334
#घोषणा PCLK_I2C3		335
#घोषणा PCLK_SPI0		338
#घोषणा PCLK_UART0		341
#घोषणा PCLK_UART1		342
#घोषणा PCLK_UART2		343
#घोषणा PCLK_TSADC		344
#घोषणा PCLK_PWM		350
#घोषणा PCLK_TIMER		353
#घोषणा PCLK_CPU		354
#घोषणा PCLK_PERI		363
#घोषणा PCLK_HDMI_CTRL		364
#घोषणा PCLK_HDMI_PHY		365
#घोषणा PCLK_GMAC		367

/* hclk gates */
#घोषणा HCLK_I2S0_8CH		442
#घोषणा HCLK_I2S1_8CH		443
#घोषणा HCLK_I2S2_2CH		444
#घोषणा HCLK_SPDIF_8CH		445
#घोषणा HCLK_VOP		452
#घोषणा HCLK_न_अंकDC		453
#घोषणा HCLK_SDMMC		456
#घोषणा HCLK_SDIO		457
#घोषणा HCLK_EMMC		459
#घोषणा HCLK_CPU		460
#घोषणा HCLK_VPU_PRE		461
#घोषणा HCLK_RKVDEC_PRE		462
#घोषणा HCLK_VIO_PRE		463
#घोषणा HCLK_VPU		464
#घोषणा HCLK_RKVDEC		465
#घोषणा HCLK_VIO		466
#घोषणा HCLK_RGA		467
#घोषणा HCLK_IEP		468
#घोषणा HCLK_VIO_H2P		469
#घोषणा HCLK_HDCP_MMU		470
#घोषणा HCLK_HOST0		471
#घोषणा HCLK_HOST1		472
#घोषणा HCLK_HOST2		473
#घोषणा HCLK_OTG		474
#घोषणा HCLK_TSP		475
#घोषणा HCLK_M_CRYPTO		476
#घोषणा HCLK_S_CRYPTO		477
#घोषणा HCLK_PERI		478

#घोषणा CLK_NR_CLKS		(HCLK_PERI + 1)

/* soft-reset indices */
#घोषणा SRST_CORE0_PO		0
#घोषणा SRST_CORE1_PO		1
#घोषणा SRST_CORE2_PO		2
#घोषणा SRST_CORE3_PO		3
#घोषणा SRST_CORE0		4
#घोषणा SRST_CORE1		5
#घोषणा SRST_CORE2		6
#घोषणा SRST_CORE3		7
#घोषणा SRST_CORE0_DBG		8
#घोषणा SRST_CORE1_DBG		9
#घोषणा SRST_CORE2_DBG		10
#घोषणा SRST_CORE3_DBG		11
#घोषणा SRST_TOPDBG		12
#घोषणा SRST_ACLK_CORE		13
#घोषणा SRST_NOC		14
#घोषणा SRST_L2C		15

#घोषणा SRST_CPUSYS_H		18
#घोषणा SRST_BUSSYS_H		19
#घोषणा SRST_SPDIF		20
#घोषणा SRST_INTMEM		21
#घोषणा SRST_ROM		22
#घोषणा SRST_OTG_ADP		23
#घोषणा SRST_I2S0		24
#घोषणा SRST_I2S1		25
#घोषणा SRST_I2S2		26
#घोषणा SRST_ACODEC_P		27
#घोषणा SRST_DFIMON		28
#घोषणा SRST_MSCH		29
#घोषणा SRST_EFUSE1024		30
#घोषणा SRST_EFUSE256		31

#घोषणा SRST_GPIO0		32
#घोषणा SRST_GPIO1		33
#घोषणा SRST_GPIO2		34
#घोषणा SRST_GPIO3		35
#घोषणा SRST_PERIPH_NOC_A	36
#घोषणा SRST_PERIPH_NOC_BUS_H	37
#घोषणा SRST_PERIPH_NOC_P	38
#घोषणा SRST_UART0		39
#घोषणा SRST_UART1		40
#घोषणा SRST_UART2		41
#घोषणा SRST_PHYNOC		42
#घोषणा SRST_I2C0		43
#घोषणा SRST_I2C1		44
#घोषणा SRST_I2C2		45
#घोषणा SRST_I2C3		46

#घोषणा SRST_PWM		48
#घोषणा SRST_A53_GIC		49
#घोषणा SRST_DAP		51
#घोषणा SRST_DAP_NOC		52
#घोषणा SRST_CRYPTO		53
#घोषणा SRST_SGRF		54
#घोषणा SRST_GRF		55
#घोषणा SRST_GMAC		56
#घोषणा SRST_PERIPH_NOC_H	58
#घोषणा SRST_MACPHY		63

#घोषणा SRST_DMA		64
#घोषणा SRST_न_अंकDC		68
#घोषणा SRST_USBOTG		69
#घोषणा SRST_OTGC		70
#घोषणा SRST_USBHOST0		71
#घोषणा SRST_HOST_CTRL0		72
#घोषणा SRST_USBHOST1		73
#घोषणा SRST_HOST_CTRL1		74
#घोषणा SRST_USBHOST2		75
#घोषणा SRST_HOST_CTRL2		76
#घोषणा SRST_USBPOR0		77
#घोषणा SRST_USBPOR1		78
#घोषणा SRST_DDRMSCH		79

#घोषणा SRST_SMART_CARD		80
#घोषणा SRST_SDMMC		81
#घोषणा SRST_SDIO		82
#घोषणा SRST_EMMC		83
#घोषणा SRST_SPI		84
#घोषणा SRST_TSP_H		85
#घोषणा SRST_TSP		86
#घोषणा SRST_TSADC		87
#घोषणा SRST_DDRPHY		88
#घोषणा SRST_DDRPHY_P		89
#घोषणा SRST_DDRCTRL		90
#घोषणा SRST_DDRCTRL_P		91
#घोषणा SRST_HOST0_ECHI		92
#घोषणा SRST_HOST1_ECHI		93
#घोषणा SRST_HOST2_ECHI		94
#घोषणा SRST_VOP_NOC_A		95

#घोषणा SRST_HDMI_P		96
#घोषणा SRST_VIO_ARBI_H		97
#घोषणा SRST_IEP_NOC_A		98
#घोषणा SRST_VIO_NOC_H		99
#घोषणा SRST_VOP_A		100
#घोषणा SRST_VOP_H		101
#घोषणा SRST_VOP_D		102
#घोषणा SRST_UTMI0		103
#घोषणा SRST_UTMI1		104
#घोषणा SRST_UTMI2		105
#घोषणा SRST_UTMI3		106
#घोषणा SRST_RGA		107
#घोषणा SRST_RGA_NOC_A		108
#घोषणा SRST_RGA_A		109
#घोषणा SRST_RGA_H		110
#घोषणा SRST_HDCP_A		111

#घोषणा SRST_VPU_A		112
#घोषणा SRST_VPU_H		113
#घोषणा SRST_VPU_NOC_A		116
#घोषणा SRST_VPU_NOC_H		117
#घोषणा SRST_RKVDEC_A		118
#घोषणा SRST_RKVDEC_NOC_A	119
#घोषणा SRST_RKVDEC_H		120
#घोषणा SRST_RKVDEC_NOC_H	121
#घोषणा SRST_RKVDEC_CORE	122
#घोषणा SRST_RKVDEC_CABAC	123
#घोषणा SRST_IEP_A		124
#घोषणा SRST_IEP_H		125
#घोषणा SRST_GPU_A		126
#घोषणा SRST_GPU_NOC_A		127

#घोषणा SRST_CORE_DBG		128
#घोषणा SRST_DBG_P		129
#घोषणा SRST_TIMER0		130
#घोषणा SRST_TIMER1		131
#घोषणा SRST_TIMER2		132
#घोषणा SRST_TIMER3		133
#घोषणा SRST_TIMER4		134
#घोषणा SRST_TIMER5		135
#घोषणा SRST_VIO_H2P		136
#घोषणा SRST_HDMIPHY		139
#घोषणा SRST_VDAC		140
#घोषणा SRST_TIMER_6CH_P	141

#पूर्ण_अगर
