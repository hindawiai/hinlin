<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 */

#अगर_अघोषित _DT_BINDINGS_CLK_ROCKCHIP_RK3288_H
#घोषणा _DT_BINDINGS_CLK_ROCKCHIP_RK3288_H

/* core घड़ीs */
#घोषणा PLL_APLL		1
#घोषणा PLL_DPLL		2
#घोषणा PLL_CPLL		3
#घोषणा PLL_GPLL		4
#घोषणा PLL_NPLL		5
#घोषणा ARMCLK			6

/* sclk gates (special घड़ीs) */
#घोषणा SCLK_GPU		64
#घोषणा SCLK_SPI0		65
#घोषणा SCLK_SPI1		66
#घोषणा SCLK_SPI2		67
#घोषणा SCLK_SDMMC		68
#घोषणा SCLK_SDIO0		69
#घोषणा SCLK_SDIO1		70
#घोषणा SCLK_EMMC		71
#घोषणा SCLK_TSADC		72
#घोषणा SCLK_SARADC		73
#घोषणा SCLK_PS2C		74
#घोषणा SCLK_न_अंकDC0		75
#घोषणा SCLK_न_अंकDC1		76
#घोषणा SCLK_UART0		77
#घोषणा SCLK_UART1		78
#घोषणा SCLK_UART2		79
#घोषणा SCLK_UART3		80
#घोषणा SCLK_UART4		81
#घोषणा SCLK_I2S0		82
#घोषणा SCLK_SPDIF		83
#घोषणा SCLK_SPDIF8CH		84
#घोषणा SCLK_TIMER0		85
#घोषणा SCLK_TIMER1		86
#घोषणा SCLK_TIMER2		87
#घोषणा SCLK_TIMER3		88
#घोषणा SCLK_TIMER4		89
#घोषणा SCLK_TIMER5		90
#घोषणा SCLK_TIMER6		91
#घोषणा SCLK_HSADC		92
#घोषणा SCLK_OTGPHY0		93
#घोषणा SCLK_OTGPHY1		94
#घोषणा SCLK_OTGPHY2		95
#घोषणा SCLK_OTG_ADP		96
#घोषणा SCLK_HSICPHY480M	97
#घोषणा SCLK_HSICPHY12M		98
#घोषणा SCLK_MACREF		99
#घोषणा SCLK_LCDC_PWM0		100
#घोषणा SCLK_LCDC_PWM1		101
#घोषणा SCLK_MAC_RX		102
#घोषणा SCLK_MAC_TX		103
#घोषणा SCLK_EDP_24M		104
#घोषणा SCLK_EDP		105
#घोषणा SCLK_RGA		106
#घोषणा SCLK_ISP		107
#घोषणा SCLK_ISP_JPE		108
#घोषणा SCLK_HDMI_HDCP		109
#घोषणा SCLK_HDMI_CEC		110
#घोषणा SCLK_HEVC_CABAC		111
#घोषणा SCLK_HEVC_CORE		112
#घोषणा SCLK_I2S0_OUT		113
#घोषणा SCLK_SDMMC_DRV		114
#घोषणा SCLK_SDIO0_DRV		115
#घोषणा SCLK_SDIO1_DRV		116
#घोषणा SCLK_EMMC_DRV		117
#घोषणा SCLK_SDMMC_SAMPLE	118
#घोषणा SCLK_SDIO0_SAMPLE	119
#घोषणा SCLK_SDIO1_SAMPLE	120
#घोषणा SCLK_EMMC_SAMPLE	121
#घोषणा SCLK_USBPHY480M_SRC	122
#घोषणा SCLK_PVTM_CORE		123
#घोषणा SCLK_PVTM_GPU		124
#घोषणा SCLK_CRYPTO		125
#घोषणा SCLK_MIPIDSI_24M	126
#घोषणा SCLK_VIP_OUT		127

#घोषणा SCLK_MAC		151
#घोषणा SCLK_MACREF_OUT		152

#घोषणा DCLK_VOP0		190
#घोषणा DCLK_VOP1		191

/* aclk gates */
#घोषणा ACLK_GPU		192
#घोषणा ACLK_DMAC1		193
#घोषणा ACLK_DMAC2		194
#घोषणा ACLK_MMU		195
#घोषणा ACLK_GMAC		196
#घोषणा ACLK_VOP0		197
#घोषणा ACLK_VOP1		198
#घोषणा ACLK_CRYPTO		199
#घोषणा ACLK_RGA		200
#घोषणा ACLK_RGA_NIU		201
#घोषणा ACLK_IEP		202
#घोषणा ACLK_VIO0_NIU		203
#घोषणा ACLK_VIP		204
#घोषणा ACLK_ISP		205
#घोषणा ACLK_VIO1_NIU		206
#घोषणा ACLK_HEVC		207
#घोषणा ACLK_VCODEC		208
#घोषणा ACLK_CPU		209
#घोषणा ACLK_PERI		210

/* pclk gates */
#घोषणा PCLK_GPIO0		320
#घोषणा PCLK_GPIO1		321
#घोषणा PCLK_GPIO2		322
#घोषणा PCLK_GPIO3		323
#घोषणा PCLK_GPIO4		324
#घोषणा PCLK_GPIO5		325
#घोषणा PCLK_GPIO6		326
#घोषणा PCLK_GPIO7		327
#घोषणा PCLK_GPIO8		328
#घोषणा PCLK_GRF		329
#घोषणा PCLK_SGRF		330
#घोषणा PCLK_PMU		331
#घोषणा PCLK_I2C0		332
#घोषणा PCLK_I2C1		333
#घोषणा PCLK_I2C2		334
#घोषणा PCLK_I2C3		335
#घोषणा PCLK_I2C4		336
#घोषणा PCLK_I2C5		337
#घोषणा PCLK_SPI0		338
#घोषणा PCLK_SPI1		339
#घोषणा PCLK_SPI2		340
#घोषणा PCLK_UART0		341
#घोषणा PCLK_UART1		342
#घोषणा PCLK_UART2		343
#घोषणा PCLK_UART3		344
#घोषणा PCLK_UART4		345
#घोषणा PCLK_TSADC		346
#घोषणा PCLK_SARADC		347
#घोषणा PCLK_SIM		348
#घोषणा PCLK_GMAC		349
#घोषणा PCLK_PWM		350
#घोषणा PCLK_RKPWM		351
#घोषणा PCLK_PS2C		352
#घोषणा PCLK_TIMER		353
#घोषणा PCLK_TZPC		354
#घोषणा PCLK_EDP_CTRL		355
#घोषणा PCLK_MIPI_DSI0		356
#घोषणा PCLK_MIPI_DSI1		357
#घोषणा PCLK_MIPI_CSI		358
#घोषणा PCLK_LVDS_PHY		359
#घोषणा PCLK_HDMI_CTRL		360
#घोषणा PCLK_VIO2_H2P		361
#घोषणा PCLK_CPU		362
#घोषणा PCLK_PERI		363
#घोषणा PCLK_DDRUPCTL0		364
#घोषणा PCLK_PUBL0		365
#घोषणा PCLK_DDRUPCTL1		366
#घोषणा PCLK_PUBL1		367
#घोषणा PCLK_WDT		368
#घोषणा PCLK_EFUSE256		369
#घोषणा PCLK_EFUSE1024		370
#घोषणा PCLK_ISP_IN		371

/* hclk gates */
#घोषणा HCLK_GPS		448
#घोषणा HCLK_OTG0		449
#घोषणा HCLK_USBHOST0		450
#घोषणा HCLK_USBHOST1		451
#घोषणा HCLK_HSIC		452
#घोषणा HCLK_न_अंकDC0		453
#घोषणा HCLK_न_अंकDC1		454
#घोषणा HCLK_TSP		455
#घोषणा HCLK_SDMMC		456
#घोषणा HCLK_SDIO0		457
#घोषणा HCLK_SDIO1		458
#घोषणा HCLK_EMMC		459
#घोषणा HCLK_HSADC		460
#घोषणा HCLK_CRYPTO		461
#घोषणा HCLK_I2S0		462
#घोषणा HCLK_SPDIF		463
#घोषणा HCLK_SPDIF8CH		464
#घोषणा HCLK_VOP0		465
#घोषणा HCLK_VOP1		466
#घोषणा HCLK_ROM		467
#घोषणा HCLK_IEP		468
#घोषणा HCLK_ISP		469
#घोषणा HCLK_RGA		470
#घोषणा HCLK_VIO_AHB_ARBI	471
#घोषणा HCLK_VIO_NIU		472
#घोषणा HCLK_VIP		473
#घोषणा HCLK_VIO2_H2P		474
#घोषणा HCLK_HEVC		475
#घोषणा HCLK_VCODEC		476
#घोषणा HCLK_CPU		477
#घोषणा HCLK_PERI		478

#घोषणा CLK_NR_CLKS		(HCLK_PERI + 1)

/* soft-reset indices */
#घोषणा SRST_CORE0		0
#घोषणा SRST_CORE1		1
#घोषणा SRST_CORE2		2
#घोषणा SRST_CORE3		3
#घोषणा SRST_CORE0_PO		4
#घोषणा SRST_CORE1_PO		5
#घोषणा SRST_CORE2_PO		6
#घोषणा SRST_CORE3_PO		7
#घोषणा SRST_PDCORE_STRSYS	8
#घोषणा SRST_PDBUS_STRSYS	9
#घोषणा SRST_L2C		10
#घोषणा SRST_TOPDBG		11
#घोषणा SRST_CORE0_DBG		12
#घोषणा SRST_CORE1_DBG		13
#घोषणा SRST_CORE2_DBG		14
#घोषणा SRST_CORE3_DBG		15

#घोषणा SRST_PDBUG_AHB_ARBITOR	16
#घोषणा SRST_EFUSE256		17
#घोषणा SRST_DMAC1		18
#घोषणा SRST_INTMEM		19
#घोषणा SRST_ROM		20
#घोषणा SRST_SPDIF8CH		21
#घोषणा SRST_TIMER		22
#घोषणा SRST_I2S0		23
#घोषणा SRST_SPDIF		24
#घोषणा SRST_TIMER0		25
#घोषणा SRST_TIMER1		26
#घोषणा SRST_TIMER2		27
#घोषणा SRST_TIMER3		28
#घोषणा SRST_TIMER4		29
#घोषणा SRST_TIMER5		30
#घोषणा SRST_EFUSE		31

#घोषणा SRST_GPIO0		32
#घोषणा SRST_GPIO1		33
#घोषणा SRST_GPIO2		34
#घोषणा SRST_GPIO3		35
#घोषणा SRST_GPIO4		36
#घोषणा SRST_GPIO5		37
#घोषणा SRST_GPIO6		38
#घोषणा SRST_GPIO7		39
#घोषणा SRST_GPIO8		40
#घोषणा SRST_I2C0		42
#घोषणा SRST_I2C1		43
#घोषणा SRST_I2C2		44
#घोषणा SRST_I2C3		45
#घोषणा SRST_I2C4		46
#घोषणा SRST_I2C5		47

#घोषणा SRST_DWPWM		48
#घोषणा SRST_MMC_PERI		49
#घोषणा SRST_PERIPH_MMU		50
#घोषणा SRST_DAP		51
#घोषणा SRST_DAP_SYS		52
#घोषणा SRST_TPIU		53
#घोषणा SRST_PMU_APB		54
#घोषणा SRST_GRF		55
#घोषणा SRST_PMU		56
#घोषणा SRST_PERIPH_AXI		57
#घोषणा SRST_PERIPH_AHB		58
#घोषणा SRST_PERIPH_APB		59
#घोषणा SRST_PERIPH_NIU		60
#घोषणा SRST_PDPERI_AHB_ARBI	61
#घोषणा SRST_EMEM		62
#घोषणा SRST_USB_PERI		63

#घोषणा SRST_DMAC2		64
#घोषणा SRST_MAC		66
#घोषणा SRST_GPS		67
#घोषणा SRST_RKPWM		69
#घोषणा SRST_CCP		71
#घोषणा SRST_USBHOST0		72
#घोषणा SRST_HSIC		73
#घोषणा SRST_HSIC_AUX		74
#घोषणा SRST_HSIC_PHY		75
#घोषणा SRST_HSADC		76
#घोषणा SRST_न_अंकDC0		77
#घोषणा SRST_न_अंकDC1		78

#घोषणा SRST_TZPC		80
#घोषणा SRST_SPI0		83
#घोषणा SRST_SPI1		84
#घोषणा SRST_SPI2		85
#घोषणा SRST_SARADC		87
#घोषणा SRST_PDALIVE_NIU	88
#घोषणा SRST_PDPMU_INTMEM	89
#घोषणा SRST_PDPMU_NIU		90
#घोषणा SRST_SGRF		91

#घोषणा SRST_VIO_ARBI		96
#घोषणा SRST_RGA_NIU		97
#घोषणा SRST_VIO0_NIU_AXI	98
#घोषणा SRST_VIO_NIU_AHB	99
#घोषणा SRST_LCDC0_AXI		100
#घोषणा SRST_LCDC0_AHB		101
#घोषणा SRST_LCDC0_DCLK		102
#घोषणा SRST_VIO1_NIU_AXI	103
#घोषणा SRST_VIP		104
#घोषणा SRST_RGA_CORE		105
#घोषणा SRST_IEP_AXI		106
#घोषणा SRST_IEP_AHB		107
#घोषणा SRST_RGA_AXI		108
#घोषणा SRST_RGA_AHB		109
#घोषणा SRST_ISP		110
#घोषणा SRST_EDP		111

#घोषणा SRST_VCODEC_AXI		112
#घोषणा SRST_VCODEC_AHB		113
#घोषणा SRST_VIO_H2P		114
#घोषणा SRST_MIPIDSI0		115
#घोषणा SRST_MIPIDSI1		116
#घोषणा SRST_MIPICSI		117
#घोषणा SRST_LVDS_PHY		118
#घोषणा SRST_LVDS_CON		119
#घोषणा SRST_GPU		120
#घोषणा SRST_HDMI		121
#घोषणा SRST_CORE_PVTM		124
#घोषणा SRST_GPU_PVTM		125

#घोषणा SRST_MMC0		128
#घोषणा SRST_SDIO0		129
#घोषणा SRST_SDIO1		130
#घोषणा SRST_EMMC		131
#घोषणा SRST_USBOTG_AHB		132
#घोषणा SRST_USBOTG_PHY		133
#घोषणा SRST_USBOTG_CON		134
#घोषणा SRST_USBHOST0_AHB	135
#घोषणा SRST_USBHOST0_PHY	136
#घोषणा SRST_USBHOST0_CON	137
#घोषणा SRST_USBHOST1_AHB	138
#घोषणा SRST_USBHOST1_PHY	139
#घोषणा SRST_USBHOST1_CON	140
#घोषणा SRST_USB_ADP		141
#घोषणा SRST_ACC_EFUSE		142

#घोषणा SRST_CORESIGHT		144
#घोषणा SRST_PD_CORE_AHB_NOC	145
#घोषणा SRST_PD_CORE_APB_NOC	146
#घोषणा SRST_PD_CORE_MP_AXI	147
#घोषणा SRST_GIC		148
#घोषणा SRST_LCDC_PWM0		149
#घोषणा SRST_LCDC_PWM1		150
#घोषणा SRST_VIO0_H2P_BRG	151
#घोषणा SRST_VIO1_H2P_BRG	152
#घोषणा SRST_RGA_H2P_BRG	153
#घोषणा SRST_HEVC		154
#घोषणा SRST_TSADC		159

#घोषणा SRST_DDRPHY0		160
#घोषणा SRST_DDRPHY0_APB	161
#घोषणा SRST_DDRCTRL0		162
#घोषणा SRST_DDRCTRL0_APB	163
#घोषणा SRST_DDRPHY0_CTRL	164
#घोषणा SRST_DDRPHY1		165
#घोषणा SRST_DDRPHY1_APB	166
#घोषणा SRST_DDRCTRL1		167
#घोषणा SRST_DDRCTRL1_APB	168
#घोषणा SRST_DDRPHY1_CTRL	169
#घोषणा SRST_DDRMSCH0		170
#घोषणा SRST_DDRMSCH1		171
#घोषणा SRST_CRYPTO		174
#घोषणा SRST_C2C_HOST		175

#घोषणा SRST_LCDC1_AXI		176
#घोषणा SRST_LCDC1_AHB		177
#घोषणा SRST_LCDC1_DCLK		178
#घोषणा SRST_UART0		179
#घोषणा SRST_UART1		180
#घोषणा SRST_UART2		181
#घोषणा SRST_UART3		182
#घोषणा SRST_UART4		183
#घोषणा SRST_SIMC		186
#घोषणा SRST_PS2C		187
#घोषणा SRST_TSP		188
#घोषणा SRST_TSP_CLKIN0		189
#घोषणा SRST_TSP_CLKIN1		190
#घोषणा SRST_TSP_27M		191

#पूर्ण_अगर
