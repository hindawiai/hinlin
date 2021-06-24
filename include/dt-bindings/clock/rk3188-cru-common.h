<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 */

#अगर_अघोषित _DT_BINDINGS_CLK_ROCKCHIP_RK3188_COMMON_H
#घोषणा _DT_BINDINGS_CLK_ROCKCHIP_RK3188_COMMON_H

/* core घड़ीs from */
#घोषणा PLL_APLL		1
#घोषणा PLL_DPLL		2
#घोषणा PLL_CPLL		3
#घोषणा PLL_GPLL		4
#घोषणा CORE_PERI		5
#घोषणा CORE_L2C		6
#घोषणा ARMCLK			7

/* sclk gates (special घड़ीs) */
#घोषणा SCLK_UART0		64
#घोषणा SCLK_UART1		65
#घोषणा SCLK_UART2		66
#घोषणा SCLK_UART3		67
#घोषणा SCLK_MAC		68
#घोषणा SCLK_SPI0		69
#घोषणा SCLK_SPI1		70
#घोषणा SCLK_SARADC		71
#घोषणा SCLK_SDMMC		72
#घोषणा SCLK_SDIO		73
#घोषणा SCLK_EMMC		74
#घोषणा SCLK_I2S0		75
#घोषणा SCLK_I2S1		76
#घोषणा SCLK_I2S2		77
#घोषणा SCLK_SPDIF		78
#घोषणा SCLK_CIF0		79
#घोषणा SCLK_CIF1		80
#घोषणा SCLK_OTGPHY0		81
#घोषणा SCLK_OTGPHY1		82
#घोषणा SCLK_HSADC		83
#घोषणा SCLK_TIMER0		84
#घोषणा SCLK_TIMER1		85
#घोषणा SCLK_TIMER2		86
#घोषणा SCLK_TIMER3		87
#घोषणा SCLK_TIMER4		88
#घोषणा SCLK_TIMER5		89
#घोषणा SCLK_TIMER6		90
#घोषणा SCLK_JTAG		91
#घोषणा SCLK_SMC		92
#घोषणा SCLK_TSADC		93

#घोषणा DCLK_LCDC0		190
#घोषणा DCLK_LCDC1		191

/* aclk gates */
#घोषणा ACLK_DMA1		192
#घोषणा ACLK_DMA2		193
#घोषणा ACLK_GPS		194
#घोषणा ACLK_LCDC0		195
#घोषणा ACLK_LCDC1		196
#घोषणा ACLK_GPU		197
#घोषणा ACLK_SMC		198
#घोषणा ACLK_CIF1		199
#घोषणा ACLK_IPP		200
#घोषणा ACLK_RGA		201
#घोषणा ACLK_CIF0		202
#घोषणा ACLK_CPU		203
#घोषणा ACLK_PERI		204
#घोषणा ACLK_VEPU		205
#घोषणा ACLK_VDPU		206

/* pclk gates */
#घोषणा PCLK_GRF		320
#घोषणा PCLK_PMU		321
#घोषणा PCLK_TIMER0		322
#घोषणा PCLK_TIMER1		323
#घोषणा PCLK_TIMER2		324
#घोषणा PCLK_TIMER3		325
#घोषणा PCLK_PWM01		326
#घोषणा PCLK_PWM23		327
#घोषणा PCLK_SPI0		328
#घोषणा PCLK_SPI1		329
#घोषणा PCLK_SARADC		330
#घोषणा PCLK_WDT		331
#घोषणा PCLK_UART0		332
#घोषणा PCLK_UART1		333
#घोषणा PCLK_UART2		334
#घोषणा PCLK_UART3		335
#घोषणा PCLK_I2C0		336
#घोषणा PCLK_I2C1		337
#घोषणा PCLK_I2C2		338
#घोषणा PCLK_I2C3		339
#घोषणा PCLK_I2C4		340
#घोषणा PCLK_GPIO0		341
#घोषणा PCLK_GPIO1		342
#घोषणा PCLK_GPIO2		343
#घोषणा PCLK_GPIO3		344
#घोषणा PCLK_GPIO4		345
#घोषणा PCLK_GPIO6		346
#घोषणा PCLK_EFUSE		347
#घोषणा PCLK_TZPC		348
#घोषणा PCLK_TSADC		349
#घोषणा PCLK_CPU		350
#घोषणा PCLK_PERI		351
#घोषणा PCLK_DDRUPCTL		352
#घोषणा PCLK_PUBL		353

/* hclk gates */
#घोषणा HCLK_SDMMC		448
#घोषणा HCLK_SDIO		449
#घोषणा HCLK_EMMC		450
#घोषणा HCLK_OTG0		451
#घोषणा HCLK_EMAC		452
#घोषणा HCLK_SPDIF		453
#घोषणा HCLK_I2S0		454
#घोषणा HCLK_I2S1		455
#घोषणा HCLK_I2S2		456
#घोषणा HCLK_OTG1		457
#घोषणा HCLK_HSIC		458
#घोषणा HCLK_HSADC		459
#घोषणा HCLK_PIDF		460
#घोषणा HCLK_LCDC0		461
#घोषणा HCLK_LCDC1		462
#घोषणा HCLK_ROM		463
#घोषणा HCLK_CIF0		464
#घोषणा HCLK_IPP		465
#घोषणा HCLK_RGA		466
#घोषणा HCLK_न_अंकDC0		467
#घोषणा HCLK_CPU		468
#घोषणा HCLK_PERI		469
#घोषणा HCLK_CIF1		470
#घोषणा HCLK_VEPU		471
#घोषणा HCLK_VDPU		472
#घोषणा HCLK_HDMI		473

#घोषणा CLK_NR_CLKS		(HCLK_HDMI + 1)

/* soft-reset indices */
#घोषणा SRST_MCORE		2
#घोषणा SRST_CORE0		3
#घोषणा SRST_CORE1		4
#घोषणा SRST_MCORE_DBG		7
#घोषणा SRST_CORE0_DBG		8
#घोषणा SRST_CORE1_DBG		9
#घोषणा SRST_CORE0_WDT		12
#घोषणा SRST_CORE1_WDT		13
#घोषणा SRST_STRC_SYS		14
#घोषणा SRST_L2C		15

#घोषणा SRST_CPU_AHB		17
#घोषणा SRST_AHB2APB		19
#घोषणा SRST_DMA1		20
#घोषणा SRST_INTMEM		21
#घोषणा SRST_ROM		22
#घोषणा SRST_SPDIF		26
#घोषणा SRST_TIMER0		27
#घोषणा SRST_TIMER1		28
#घोषणा SRST_EFUSE		30

#घोषणा SRST_GPIO0		32
#घोषणा SRST_GPIO1		33
#घोषणा SRST_GPIO2		34
#घोषणा SRST_GPIO3		35

#घोषणा SRST_UART0		39
#घोषणा SRST_UART1		40
#घोषणा SRST_UART2		41
#घोषणा SRST_UART3		42
#घोषणा SRST_I2C0		43
#घोषणा SRST_I2C1		44
#घोषणा SRST_I2C2		45
#घोषणा SRST_I2C3		46
#घोषणा SRST_I2C4		47

#घोषणा SRST_PWM0		48
#घोषणा SRST_PWM1		49
#घोषणा SRST_DAP_PO		50
#घोषणा SRST_DAP		51
#घोषणा SRST_DAP_SYS		52
#घोषणा SRST_TPIU_ATB		53
#घोषणा SRST_PMU_APB		54
#घोषणा SRST_GRF		55
#घोषणा SRST_PMU		56
#घोषणा SRST_PERI_AXI		57
#घोषणा SRST_PERI_AHB		58
#घोषणा SRST_PERI_APB		59
#घोषणा SRST_PERI_NIU		60
#घोषणा SRST_CPU_PERI		61
#घोषणा SRST_EMEM_PERI		62
#घोषणा SRST_USB_PERI		63

#घोषणा SRST_DMA2		64
#घोषणा SRST_SMC		65
#घोषणा SRST_MAC		66
#घोषणा SRST_न_अंकC0		68
#घोषणा SRST_USBOTG0		69
#घोषणा SRST_USBPHY0		70
#घोषणा SRST_OTGC0		71
#घोषणा SRST_USBOTG1		72
#घोषणा SRST_USBPHY1		73
#घोषणा SRST_OTGC1		74
#घोषणा SRST_HSADC		76
#घोषणा SRST_PIDFILTER		77
#घोषणा SRST_DDR_MSCH		79

#घोषणा SRST_TZPC		80
#घोषणा SRST_SDMMC		81
#घोषणा SRST_SDIO		82
#घोषणा SRST_EMMC		83
#घोषणा SRST_SPI0		84
#घोषणा SRST_SPI1		85
#घोषणा SRST_WDT		86
#घोषणा SRST_SARADC		87
#घोषणा SRST_DDRPHY		88
#घोषणा SRST_DDRPHY_APB		89
#घोषणा SRST_DDRCTL		90
#घोषणा SRST_DDRCTL_APB		91
#घोषणा SRST_DDRPUB		93

#घोषणा SRST_VIO0_AXI		98
#घोषणा SRST_VIO0_AHB		99
#घोषणा SRST_LCDC0_AXI		100
#घोषणा SRST_LCDC0_AHB		101
#घोषणा SRST_LCDC0_DCLK		102
#घोषणा SRST_LCDC1_AXI		103
#घोषणा SRST_LCDC1_AHB		104
#घोषणा SRST_LCDC1_DCLK		105
#घोषणा SRST_IPP_AXI		106
#घोषणा SRST_IPP_AHB		107
#घोषणा SRST_RGA_AXI		108
#घोषणा SRST_RGA_AHB		109
#घोषणा SRST_CIF0		110

#घोषणा SRST_VCODEC_AXI		112
#घोषणा SRST_VCODEC_AHB		113
#घोषणा SRST_VIO1_AXI		114
#घोषणा SRST_VCODEC_CPU		115
#घोषणा SRST_VCODEC_NIU		116
#घोषणा SRST_GPU		120
#घोषणा SRST_GPU_NIU		122
#घोषणा SRST_TFUN_ATB		125
#घोषणा SRST_TFUN_APB		126
#घोषणा SRST_CTI4_APB		127

#घोषणा SRST_TPIU_APB		128
#घोषणा SRST_TRACE		129
#घोषणा SRST_CORE_DBG		130
#घोषणा SRST_DBG_APB		131
#घोषणा SRST_CTI0		132
#घोषणा SRST_CTI0_APB		133
#घोषणा SRST_CTI1		134
#घोषणा SRST_CTI1_APB		135
#घोषणा SRST_PTM_CORE0		136
#घोषणा SRST_PTM_CORE1		137
#घोषणा SRST_PTM0		138
#घोषणा SRST_PTM0_ATB		139
#घोषणा SRST_PTM1		140
#घोषणा SRST_PTM1_ATB		141
#घोषणा SRST_CTM		142
#घोषणा SRST_TS			143

#पूर्ण_अगर
