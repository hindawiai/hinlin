<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2017 Rockchip Electronics Co. Ltd.
 * Author: Elaine <zhangqing@rock-chips.com>
 */

#अगर_अघोषित _DT_BINDINGS_CLK_ROCKCHIP_RK3128_H
#घोषणा _DT_BINDINGS_CLK_ROCKCHIP_RK3128_H

/* core घड़ीs */
#घोषणा PLL_APLL		1
#घोषणा PLL_DPLL		2
#घोषणा PLL_CPLL		3
#घोषणा PLL_GPLL		4
#घोषणा ARMCLK			5
#घोषणा PLL_GPLL_DIV2		6
#घोषणा PLL_GPLL_DIV3		7

/* sclk gates (special घड़ीs) */
#घोषणा SCLK_SPI0		65
#घोषणा SCLK_न_अंकDC		67
#घोषणा SCLK_SDMMC		68
#घोषणा SCLK_SDIO		69
#घोषणा SCLK_EMMC		71
#घोषणा SCLK_UART0		77
#घोषणा SCLK_UART1		78
#घोषणा SCLK_UART2		79
#घोषणा SCLK_I2S0		80
#घोषणा SCLK_I2S1		81
#घोषणा SCLK_SPDIF		83
#घोषणा SCLK_TIMER0		85
#घोषणा SCLK_TIMER1		86
#घोषणा SCLK_TIMER2		87
#घोषणा SCLK_TIMER3		88
#घोषणा SCLK_TIMER4		89
#घोषणा SCLK_TIMER5		90
#घोषणा SCLK_SARADC		91
#घोषणा SCLK_I2S_OUT		113
#घोषणा SCLK_SDMMC_DRV		114
#घोषणा SCLK_SDIO_DRV		115
#घोषणा SCLK_EMMC_DRV		117
#घोषणा SCLK_SDMMC_SAMPLE	118
#घोषणा SCLK_SDIO_SAMPLE	119
#घोषणा SCLK_EMMC_SAMPLE	121
#घोषणा SCLK_VOP		122
#घोषणा SCLK_MAC_SRC		124
#घोषणा SCLK_MAC		126
#घोषणा SCLK_MAC_REFOUT		127
#घोषणा SCLK_MAC_REF		128
#घोषणा SCLK_MAC_RX		129
#घोषणा SCLK_MAC_TX		130
#घोषणा SCLK_HEVC_CORE		134
#घोषणा SCLK_RGA		135
#घोषणा SCLK_CRYPTO		138
#घोषणा SCLK_TSP		139
#घोषणा SCLK_OTGPHY0		142
#घोषणा SCLK_OTGPHY1		143
#घोषणा SCLK_DDRC		144
#घोषणा SCLK_PVTM_FUNC		145
#घोषणा SCLK_PVTM_CORE		146
#घोषणा SCLK_PVTM_GPU		147
#घोषणा SCLK_MIPI_24M		148
#घोषणा SCLK_PVTM		149
#घोषणा SCLK_CIF_SRC		150
#घोषणा SCLK_CIF_OUT_SRC	151
#घोषणा SCLK_CIF_OUT		152
#घोषणा SCLK_SFC		153
#घोषणा SCLK_USB480M		154

/* dclk gates */
#घोषणा DCLK_VOP		190
#घोषणा DCLK_EBC		191

/* aclk gates */
#घोषणा ACLK_VIO0		192
#घोषणा ACLK_VIO1		193
#घोषणा ACLK_DMAC		194
#घोषणा ACLK_CPU		195
#घोषणा ACLK_VEPU		196
#घोषणा ACLK_VDPU		197
#घोषणा ACLK_CIF		198
#घोषणा ACLK_IEP		199
#घोषणा ACLK_LCDC0		204
#घोषणा ACLK_RGA		205
#घोषणा ACLK_PERI		210
#घोषणा ACLK_VOP		211
#घोषणा ACLK_GMAC		212
#घोषणा ACLK_GPU		213

/* pclk gates */
#घोषणा PCLK_SARADC		318
#घोषणा PCLK_WDT		319
#घोषणा PCLK_GPIO0		320
#घोषणा PCLK_GPIO1		321
#घोषणा PCLK_GPIO2		322
#घोषणा PCLK_GPIO3		323
#घोषणा PCLK_VIO_H2P		324
#घोषणा PCLK_MIPI		325
#घोषणा PCLK_EFUSE		326
#घोषणा PCLK_HDMI		327
#घोषणा PCLK_ACODEC		328
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
#घोषणा PCLK_GMAC		367
#घोषणा PCLK_PMU_PRE		368
#घोषणा PCLK_SIM_CARD		369

/* hclk gates */
#घोषणा HCLK_SPDIF		440
#घोषणा HCLK_GPS		441
#घोषणा HCLK_USBHOST		442
#घोषणा HCLK_I2S_8CH		443
#घोषणा HCLK_I2S_2CH		444
#घोषणा HCLK_VOP		452
#घोषणा HCLK_न_अंकDC		453
#घोषणा HCLK_SDMMC		456
#घोषणा HCLK_SDIO		457
#घोषणा HCLK_EMMC		459
#घोषणा HCLK_CPU		460
#घोषणा HCLK_VEPU		461
#घोषणा HCLK_VDPU		462
#घोषणा HCLK_LCDC0		463
#घोषणा HCLK_EBC		465
#घोषणा HCLK_VIO		466
#घोषणा HCLK_RGA		467
#घोषणा HCLK_IEP		468
#घोषणा HCLK_VIO_H2P		469
#घोषणा HCLK_CIF		470
#घोषणा HCLK_HOST2		473
#घोषणा HCLK_OTG		474
#घोषणा HCLK_TSP		475
#घोषणा HCLK_CRYPTO		476
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
#घोषणा SRST_STRC_SYS_A		14
#घोषणा SRST_L2C		15

#घोषणा SRST_CPUSYS_H		18
#घोषणा SRST_AHB2APBSYS_H	19
#घोषणा SRST_SPDIF		20
#घोषणा SRST_INTMEM		21
#घोषणा SRST_ROM		22
#घोषणा SRST_PERI_NIU		23
#घोषणा SRST_I2S_2CH		24
#घोषणा SRST_I2S_8CH		25
#घोषणा SRST_GPU_PVTM		26
#घोषणा SRST_FUNC_PVTM		27
#घोषणा SRST_CORE_PVTM		29
#घोषणा SRST_EFUSE_P		30
#घोषणा SRST_ACODEC_P		31

#घोषणा SRST_GPIO0		32
#घोषणा SRST_GPIO1		33
#घोषणा SRST_GPIO2		34
#घोषणा SRST_GPIO3		35
#घोषणा SRST_MIPIPHY_P		36
#घोषणा SRST_UART0		39
#घोषणा SRST_UART1		40
#घोषणा SRST_UART2		41
#घोषणा SRST_I2C0		43
#घोषणा SRST_I2C1		44
#घोषणा SRST_I2C2		45
#घोषणा SRST_I2C3		46
#घोषणा SRST_SFC		47

#घोषणा SRST_PWM		48
#घोषणा SRST_DAP_PO		50
#घोषणा SRST_DAP		51
#घोषणा SRST_DAP_SYS		52
#घोषणा SRST_CRYPTO		53
#घोषणा SRST_GRF		55
#घोषणा SRST_GMAC		56
#घोषणा SRST_PERIPH_SYS_A	57
#घोषणा SRST_PERIPH_SYS_H	58
#घोषणा SRST_PERIPH_SYS_P       59
#घोषणा SRST_SMART_CARD		60
#घोषणा SRST_CPU_PERI		61
#घोषणा SRST_EMEM_PERI		62
#घोषणा SRST_USB_PERI		63

#घोषणा SRST_DMA		64
#घोषणा SRST_GPS		67
#घोषणा SRST_न_अंकDC		68
#घोषणा SRST_USBOTG0		69
#घोषणा SRST_OTGC0		71
#घोषणा SRST_USBOTG1		72
#घोषणा SRST_OTGC1		74
#घोषणा SRST_DDRMSCH		79

#घोषणा SRST_SDMMC		81
#घोषणा SRST_SDIO		82
#घोषणा SRST_EMMC		83
#घोषणा SRST_SPI		84
#घोषणा SRST_WDT		86
#घोषणा SRST_SARADC		87
#घोषणा SRST_DDRPHY		88
#घोषणा SRST_DDRPHY_P		89
#घोषणा SRST_DDRCTRL		90
#घोषणा SRST_DDRCTRL_P		91
#घोषणा SRST_TSP		92
#घोषणा SRST_TSP_CLKIN		93
#घोषणा SRST_HOST0_ECHI		94

#घोषणा SRST_HDMI_P		96
#घोषणा SRST_VIO_ARBI_H		97
#घोषणा SRST_VIO0_A		98
#घोषणा SRST_VIO_BUS_H		99
#घोषणा SRST_VOP_A		100
#घोषणा SRST_VOP_H		101
#घोषणा SRST_VOP_D		102
#घोषणा SRST_UTMI0		103
#घोषणा SRST_UTMI1		104
#घोषणा SRST_USBPOR		105
#घोषणा SRST_IEP_A		106
#घोषणा SRST_IEP_H		107
#घोषणा SRST_RGA_A		108
#घोषणा SRST_RGA_H		109
#घोषणा SRST_CIF0		110
#घोषणा SRST_PMU		111

#घोषणा SRST_VCODEC_A		112
#घोषणा SRST_VCODEC_H		113
#घोषणा SRST_VIO1_A		114
#घोषणा SRST_HEVC_CORE		115
#घोषणा SRST_VCODEC_NIU_A	116
#घोषणा SRST_PMU_NIU_P		117
#घोषणा SRST_LCDC0_S		119
#घोषणा SRST_GPU		120
#घोषणा SRST_GPU_NIU_A		122
#घोषणा SRST_EBC_A		123
#घोषणा SRST_EBC_H		124

#घोषणा SRST_CORE_DBG		128
#घोषणा SRST_DBG_P		129
#घोषणा SRST_TIMER0		130
#घोषणा SRST_TIMER1		131
#घोषणा SRST_TIMER2		132
#घोषणा SRST_TIMER3		133
#घोषणा SRST_TIMER4		134
#घोषणा SRST_TIMER5		135
#घोषणा SRST_VIO_H2P		136
#घोषणा SRST_VIO_MIPI_DSI	137

#पूर्ण_अगर
