<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2015 Heiko Stuebner <heiko@sntech.de>
 */

#अगर_अघोषित _DT_BINDINGS_CLK_ROCKCHIP_RK3368_H
#घोषणा _DT_BINDINGS_CLK_ROCKCHIP_RK3368_H

/* core घड़ीs */
#घोषणा PLL_APLLB		1
#घोषणा PLL_APLLL		2
#घोषणा PLL_DPLL		3
#घोषणा PLL_CPLL		4
#घोषणा PLL_GPLL		5
#घोषणा PLL_NPLL		6
#घोषणा ARMCLKB			7
#घोषणा ARMCLKL			8

/* sclk gates (special घड़ीs) */
#घोषणा SCLK_GPU_CORE		64
#घोषणा SCLK_SPI0		65
#घोषणा SCLK_SPI1		66
#घोषणा SCLK_SPI2		67
#घोषणा SCLK_SDMMC		68
#घोषणा SCLK_SDIO0		69
#घोषणा SCLK_EMMC		71
#घोषणा SCLK_TSADC		72
#घोषणा SCLK_SARADC		73
#घोषणा SCLK_न_अंकDC0		75
#घोषणा SCLK_UART0		77
#घोषणा SCLK_UART1		78
#घोषणा SCLK_UART2		79
#घोषणा SCLK_UART3		80
#घोषणा SCLK_UART4		81
#घोषणा SCLK_I2S_8CH		82
#घोषणा SCLK_SPDIF_8CH		83
#घोषणा SCLK_I2S_2CH		84
#घोषणा SCLK_TIMER00		85
#घोषणा SCLK_TIMER01		86
#घोषणा SCLK_TIMER02		87
#घोषणा SCLK_TIMER03		88
#घोषणा SCLK_TIMER04		89
#घोषणा SCLK_TIMER05		90
#घोषणा SCLK_OTGPHY0		93
#घोषणा SCLK_OTG_ADP		96
#घोषणा SCLK_HSICPHY480M	97
#घोषणा SCLK_HSICPHY12M		98
#घोषणा SCLK_MACREF		99
#घोषणा SCLK_VOP0_PWM		100
#घोषणा SCLK_MAC_RX		102
#घोषणा SCLK_MAC_TX		103
#घोषणा SCLK_EDP_24M		104
#घोषणा SCLK_EDP		105
#घोषणा SCLK_RGA		106
#घोषणा SCLK_ISP		107
#घोषणा SCLK_HDCP		108
#घोषणा SCLK_HDMI_HDCP		109
#घोषणा SCLK_HDMI_CEC		110
#घोषणा SCLK_HEVC_CABAC		111
#घोषणा SCLK_HEVC_CORE		112
#घोषणा SCLK_I2S_8CH_OUT	113
#घोषणा SCLK_SDMMC_DRV		114
#घोषणा SCLK_SDIO0_DRV		115
#घोषणा SCLK_EMMC_DRV		117
#घोषणा SCLK_SDMMC_SAMPLE	118
#घोषणा SCLK_SDIO0_SAMPLE	119
#घोषणा SCLK_EMMC_SAMPLE	121
#घोषणा SCLK_USBPHY480M		122
#घोषणा SCLK_PVTM_CORE		123
#घोषणा SCLK_PVTM_GPU		124
#घोषणा SCLK_PVTM_PMU		125
#घोषणा SCLK_SFC		126
#घोषणा SCLK_MAC		127
#घोषणा SCLK_MACREF_OUT		128
#घोषणा SCLK_TIMER10		133
#घोषणा SCLK_TIMER11		134
#घोषणा SCLK_TIMER12		135
#घोषणा SCLK_TIMER13		136
#घोषणा SCLK_TIMER14		137
#घोषणा SCLK_TIMER15		138
#घोषणा SCLK_VIP_OUT		139

#घोषणा DCLK_VOP		190
#घोषणा MCLK_CRYPTO		191

/* aclk gates */
#घोषणा ACLK_GPU_MEM		192
#घोषणा ACLK_GPU_CFG		193
#घोषणा ACLK_DMAC_BUS		194
#घोषणा ACLK_DMAC_PERI		195
#घोषणा ACLK_PERI_MMU		196
#घोषणा ACLK_GMAC		197
#घोषणा ACLK_VOP		198
#घोषणा ACLK_VOP_IEP		199
#घोषणा ACLK_RGA		200
#घोषणा ACLK_HDCP		201
#घोषणा ACLK_IEP		202
#घोषणा ACLK_VIO0_NOC		203
#घोषणा ACLK_VIP		204
#घोषणा ACLK_ISP		205
#घोषणा ACLK_VIO1_NOC		206
#घोषणा ACLK_VIDEO		208
#घोषणा ACLK_BUS		209
#घोषणा ACLK_PERI		210

/* pclk gates */
#घोषणा PCLK_GPIO0		320
#घोषणा PCLK_GPIO1		321
#घोषणा PCLK_GPIO2		322
#घोषणा PCLK_GPIO3		323
#घोषणा PCLK_PMUGRF		324
#घोषणा PCLK_MAILBOX		325
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
#घोषणा PCLK_PWM0		350
#घोषणा PCLK_PWM1		351
#घोषणा PCLK_TIMER0		353
#घोषणा PCLK_TIMER1		354
#घोषणा PCLK_EDP_CTRL		355
#घोषणा PCLK_MIPI_DSI0		356
#घोषणा PCLK_MIPI_CSI		358
#घोषणा PCLK_HDCP		359
#घोषणा PCLK_HDMI_CTRL		360
#घोषणा PCLK_VIO_H2P		361
#घोषणा PCLK_BUS		362
#घोषणा PCLK_PERI		363
#घोषणा PCLK_DDRUPCTL		364
#घोषणा PCLK_DDRPHY		365
#घोषणा PCLK_ISP		366
#घोषणा PCLK_VIP		367
#घोषणा PCLK_WDT		368
#घोषणा PCLK_EFUSE256		369
#घोषणा PCLK_DPHYRX		370
#घोषणा PCLK_DPHYTX0		371

/* hclk gates */
#घोषणा HCLK_SFC		448
#घोषणा HCLK_OTG0		449
#घोषणा HCLK_HOST0		450
#घोषणा HCLK_HOST1		451
#घोषणा HCLK_HSIC		452
#घोषणा HCLK_न_अंकDC0		453
#घोषणा HCLK_TSP		455
#घोषणा HCLK_SDMMC		456
#घोषणा HCLK_SDIO0		457
#घोषणा HCLK_EMMC		459
#घोषणा HCLK_HSADC		460
#घोषणा HCLK_CRYPTO		461
#घोषणा HCLK_I2S_2CH		462
#घोषणा HCLK_I2S_8CH		463
#घोषणा HCLK_SPDIF		464
#घोषणा HCLK_VOP		465
#घोषणा HCLK_ROM		467
#घोषणा HCLK_IEP		468
#घोषणा HCLK_ISP		469
#घोषणा HCLK_RGA		470
#घोषणा HCLK_VIO_AHB_ARBI	471
#घोषणा HCLK_VIO_NOC		472
#घोषणा HCLK_VIP		473
#घोषणा HCLK_VIO_H2P		474
#घोषणा HCLK_VIO_HDCPMMU	475
#घोषणा HCLK_VIDEO		476
#घोषणा HCLK_BUS		477
#घोषणा HCLK_PERI		478

#घोषणा CLK_NR_CLKS		(HCLK_PERI + 1)

/* soft-reset indices */
#घोषणा SRST_CORE_B0		0
#घोषणा SRST_CORE_B1		1
#घोषणा SRST_CORE_B2		2
#घोषणा SRST_CORE_B3		3
#घोषणा SRST_CORE_B0_PO		4
#घोषणा SRST_CORE_B1_PO		5
#घोषणा SRST_CORE_B2_PO		6
#घोषणा SRST_CORE_B3_PO		7
#घोषणा SRST_L2_B		8
#घोषणा SRST_ADB_B		9
#घोषणा SRST_PD_CORE_B_NIU	10
#घोषणा SRST_PDBUS_STRSYS	11
#घोषणा SRST_SOCDBG_B		14
#घोषणा SRST_CORE_B_DBG		15

#घोषणा SRST_DMAC1		18
#घोषणा SRST_INTMEM		19
#घोषणा SRST_ROM		20
#घोषणा SRST_SPDIF8CH		21
#घोषणा SRST_I2S8CH		23
#घोषणा SRST_MAILBOX		24
#घोषणा SRST_I2S2CH		25
#घोषणा SRST_EFUSE_256		26
#घोषणा SRST_MCU_SYS		28
#घोषणा SRST_MCU_PO		29
#घोषणा SRST_MCU_NOC		30
#घोषणा SRST_EFUSE		31

#घोषणा SRST_GPIO0		32
#घोषणा SRST_GPIO1		33
#घोषणा SRST_GPIO2		34
#घोषणा SRST_GPIO3		35
#घोषणा SRST_GPIO4		36
#घोषणा SRST_PMUGRF		41
#घोषणा SRST_I2C0		42
#घोषणा SRST_I2C1		43
#घोषणा SRST_I2C2		44
#घोषणा SRST_I2C3		45
#घोषणा SRST_I2C4		46
#घोषणा SRST_I2C5		47

#घोषणा SRST_DWPWM		48
#घोषणा SRST_MMC_PERI		49
#घोषणा SRST_PERIPH_MMU		50
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
#घोषणा SRST_USBHOST0		72
#घोषणा SRST_HSIC		73
#घोषणा SRST_HSIC_AUX		74
#घोषणा SRST_HSIC_PHY		75
#घोषणा SRST_HSADC		76
#घोषणा SRST_न_अंकDC0		77
#घोषणा SRST_SFC		79

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
#घोषणा SRST_VIP		104
#घोषणा SRST_RGA_CORE		105
#घोषणा SRST_IEP_AXI		106
#घोषणा SRST_IEP_AHB		107
#घोषणा SRST_RGA_AXI		108
#घोषणा SRST_RGA_AHB		109
#घोषणा SRST_ISP		110
#घोषणा SRST_EDP_24M		111

#घोषणा SRST_VIDEO_AXI		112
#घोषणा SRST_VIDEO_AHB		113
#घोषणा SRST_MIPIDPHYTX		114
#घोषणा SRST_MIPIDSI0		115
#घोषणा SRST_MIPIDPHYRX		116
#घोषणा SRST_MIPICSI		117
#घोषणा SRST_GPU		120
#घोषणा SRST_HDMI		121
#घोषणा SRST_EDP		122
#घोषणा SRST_PMU_PVTM		123
#घोषणा SRST_CORE_PVTM		124
#घोषणा SRST_GPU_PVTM		125
#घोषणा SRST_GPU_SYS		126
#घोषणा SRST_GPU_MEM_NIU	127

#घोषणा SRST_MMC0		128
#घोषणा SRST_SDIO0		129
#घोषणा SRST_EMMC		131
#घोषणा SRST_USBOTG_AHB		132
#घोषणा SRST_USBOTG_PHY		133
#घोषणा SRST_USBOTG_CON		134
#घोषणा SRST_USBHOST0_AHB	135
#घोषणा SRST_USBHOST0_PHY	136
#घोषणा SRST_USBHOST0_CON	137
#घोषणा SRST_USBOTG_UTMI	138
#घोषणा SRST_USBHOST1_UTMI	139
#घोषणा SRST_USB_ADP		141

#घोषणा SRST_CORESIGHT		144
#घोषणा SRST_PD_CORE_AHB_NOC	145
#घोषणा SRST_PD_CORE_APB_NOC	146
#घोषणा SRST_GIC		148
#घोषणा SRST_LCDC_PWM0		149
#घोषणा SRST_RGA_H2P_BRG	153
#घोषणा SRST_VIDEO		154
#घोषणा SRST_GPU_CFG_NIU	157
#घोषणा SRST_TSADC		159

#घोषणा SRST_DDRPHY0		160
#घोषणा SRST_DDRPHY0_APB	161
#घोषणा SRST_DDRCTRL0		162
#घोषणा SRST_DDRCTRL0_APB	163
#घोषणा SRST_VIDEO_NIU		165
#घोषणा SRST_VIDEO_NIU_AHB	167
#घोषणा SRST_DDRMSCH0		170
#घोषणा SRST_PDBUS_AHB		173
#घोषणा SRST_CRYPTO		174

#घोषणा SRST_UART0		179
#घोषणा SRST_UART1		180
#घोषणा SRST_UART2		181
#घोषणा SRST_UART3		182
#घोषणा SRST_UART4		183
#घोषणा SRST_SIMC		186
#घोषणा SRST_TSP		188
#घोषणा SRST_TSP_CLKIN0		189

#घोषणा SRST_CORE_L0		192
#घोषणा SRST_CORE_L1		193
#घोषणा SRST_CORE_L2		194
#घोषणा SRST_CORE_L3		195
#घोषणा SRST_CORE_L0_PO		195
#घोषणा SRST_CORE_L1_PO		197
#घोषणा SRST_CORE_L2_PO		198
#घोषणा SRST_CORE_L3_PO		199
#घोषणा SRST_L2_L		200
#घोषणा SRST_ADB_L		201
#घोषणा SRST_PD_CORE_L_NIU	202
#घोषणा SRST_CCI_SYS		203
#घोषणा SRST_CCI_DDR		204
#घोषणा SRST_CCI		205
#घोषणा SRST_SOCDBG_L		206
#घोषणा SRST_CORE_L_DBG		207

#घोषणा SRST_CORE_B0_NC		208
#घोषणा SRST_CORE_B0_PO_NC	209
#घोषणा SRST_L2_B_NC		210
#घोषणा SRST_ADB_B_NC		211
#घोषणा SRST_PD_CORE_B_NIU_NC	212
#घोषणा SRST_PDBUS_STRSYS_NC	213
#घोषणा SRST_CORE_L0_NC		214
#घोषणा SRST_CORE_L0_PO_NC	215
#घोषणा SRST_L2_L_NC		216
#घोषणा SRST_ADB_L_NC		217
#घोषणा SRST_PD_CORE_L_NIU_NC	218
#घोषणा SRST_CCI_SYS_NC		219
#घोषणा SRST_CCI_DDR_NC		220
#घोषणा SRST_CCI_NC		221
#घोषणा SRST_TRACE_NC		222

#घोषणा SRST_TIMER00		224
#घोषणा SRST_TIMER01		225
#घोषणा SRST_TIMER02		226
#घोषणा SRST_TIMER03		227
#घोषणा SRST_TIMER04		228
#घोषणा SRST_TIMER05		229
#घोषणा SRST_TIMER10		230
#घोषणा SRST_TIMER11		231
#घोषणा SRST_TIMER12		232
#घोषणा SRST_TIMER13		233
#घोषणा SRST_TIMER14		234
#घोषणा SRST_TIMER15		235
#घोषणा SRST_TIMER0_APB		236
#घोषणा SRST_TIMER1_APB		237

#पूर्ण_अगर
