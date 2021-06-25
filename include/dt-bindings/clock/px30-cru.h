<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _DT_BINDINGS_CLK_ROCKCHIP_PX30_H
#घोषणा _DT_BINDINGS_CLK_ROCKCHIP_PX30_H

/* core घड़ीs */
#घोषणा PLL_APLL		1
#घोषणा PLL_DPLL		2
#घोषणा PLL_CPLL		3
#घोषणा PLL_NPLL		4
#घोषणा APLL_BOOST_H		5
#घोषणा APLL_BOOST_L		6
#घोषणा ARMCLK			7

/* sclk gates (special घड़ीs) */
#घोषणा USB480M			14
#घोषणा SCLK_PDM		15
#घोषणा SCLK_I2S0_TX		16
#घोषणा SCLK_I2S0_TX_OUT	17
#घोषणा SCLK_I2S0_RX		18
#घोषणा SCLK_I2S0_RX_OUT	19
#घोषणा SCLK_I2S1		20
#घोषणा SCLK_I2S1_OUT		21
#घोषणा SCLK_I2S2		22
#घोषणा SCLK_I2S2_OUT		23
#घोषणा SCLK_UART1		24
#घोषणा SCLK_UART2		25
#घोषणा SCLK_UART3		26
#घोषणा SCLK_UART4		27
#घोषणा SCLK_UART5		28
#घोषणा SCLK_I2C0		29
#घोषणा SCLK_I2C1		30
#घोषणा SCLK_I2C2		31
#घोषणा SCLK_I2C3		32
#घोषणा SCLK_I2C4		33
#घोषणा SCLK_PWM0		34
#घोषणा SCLK_PWM1		35
#घोषणा SCLK_SPI0		36
#घोषणा SCLK_SPI1		37
#घोषणा SCLK_TIMER0		38
#घोषणा SCLK_TIMER1		39
#घोषणा SCLK_TIMER2		40
#घोषणा SCLK_TIMER3		41
#घोषणा SCLK_TIMER4		42
#घोषणा SCLK_TIMER5		43
#घोषणा SCLK_TSADC		44
#घोषणा SCLK_SARADC		45
#घोषणा SCLK_OTP		46
#घोषणा SCLK_OTP_USR		47
#घोषणा SCLK_CRYPTO		48
#घोषणा SCLK_CRYPTO_APK		49
#घोषणा SCLK_DDRC		50
#घोषणा SCLK_ISP		51
#घोषणा SCLK_CIF_OUT		52
#घोषणा SCLK_RGA_CORE		53
#घोषणा SCLK_VOPB_PWM		54
#घोषणा SCLK_न_अंकDC		55
#घोषणा SCLK_SDIO		56
#घोषणा SCLK_EMMC		57
#घोषणा SCLK_SFC		58
#घोषणा SCLK_SDMMC		59
#घोषणा SCLK_OTG_ADP		60
#घोषणा SCLK_GMAC_SRC		61
#घोषणा SCLK_GMAC		62
#घोषणा SCLK_GMAC_RX_TX		63
#घोषणा SCLK_MAC_REF		64
#घोषणा SCLK_MAC_REFOUT		65
#घोषणा SCLK_MAC_OUT		66
#घोषणा SCLK_SDMMC_DRV		67
#घोषणा SCLK_SDMMC_SAMPLE	68
#घोषणा SCLK_SDIO_DRV		69
#घोषणा SCLK_SDIO_SAMPLE	70
#घोषणा SCLK_EMMC_DRV		71
#घोषणा SCLK_EMMC_SAMPLE	72
#घोषणा SCLK_GPU		73
#घोषणा SCLK_PVTM		74
#घोषणा SCLK_CORE_VPU		75
#घोषणा SCLK_GMAC_RMII		76
#घोषणा SCLK_UART2_SRC		77
#घोषणा SCLK_न_अंकDC_DIV		78
#घोषणा SCLK_न_अंकDC_DIV50	79
#घोषणा SCLK_SDIO_DIV		80
#घोषणा SCLK_SDIO_DIV50		81
#घोषणा SCLK_EMMC_DIV		82
#घोषणा SCLK_EMMC_DIV50		83
#घोषणा SCLK_DDRCLK		84
#घोषणा SCLK_UART1_SRC		85
#घोषणा SCLK_SDMMC_DIV		86
#घोषणा SCLK_SDMMC_DIV50	87

/* dclk gates */
#घोषणा DCLK_VOPB		150
#घोषणा DCLK_VOPL		151

/* aclk gates */
#घोषणा ACLK_GPU		170
#घोषणा ACLK_BUS_PRE		171
#घोषणा ACLK_CRYPTO		172
#घोषणा ACLK_VI_PRE		173
#घोषणा ACLK_VO_PRE		174
#घोषणा ACLK_VPU		175
#घोषणा ACLK_PERI_PRE		176
#घोषणा ACLK_GMAC		178
#घोषणा ACLK_CIF		179
#घोषणा ACLK_ISP		180
#घोषणा ACLK_VOPB		181
#घोषणा ACLK_VOPL		182
#घोषणा ACLK_RGA		183
#घोषणा ACLK_GIC		184
#घोषणा ACLK_DCF		186
#घोषणा ACLK_DMAC		187
#घोषणा ACLK_BUS_SRC		188
#घोषणा ACLK_PERI_SRC		189

/* hclk gates */
#घोषणा HCLK_BUS_PRE		240
#घोषणा HCLK_CRYPTO		241
#घोषणा HCLK_VI_PRE		242
#घोषणा HCLK_VO_PRE		243
#घोषणा HCLK_VPU		244
#घोषणा HCLK_PERI_PRE		245
#घोषणा HCLK_MMC_न_अंकD		246
#घोषणा HCLK_SDMMC		247
#घोषणा HCLK_USB		248
#घोषणा HCLK_CIF		249
#घोषणा HCLK_ISP		250
#घोषणा HCLK_VOPB		251
#घोषणा HCLK_VOPL		252
#घोषणा HCLK_RGA		253
#घोषणा HCLK_न_अंकDC		254
#घोषणा HCLK_SDIO		255
#घोषणा HCLK_EMMC		256
#घोषणा HCLK_SFC		257
#घोषणा HCLK_OTG		258
#घोषणा HCLK_HOST		259
#घोषणा HCLK_HOST_ARB		260
#घोषणा HCLK_PDM		261
#घोषणा HCLK_I2S0		262
#घोषणा HCLK_I2S1		263
#घोषणा HCLK_I2S2		264

/* pclk gates */
#घोषणा PCLK_BUS_PRE		320
#घोषणा PCLK_DDR		321
#घोषणा PCLK_VO_PRE		322
#घोषणा PCLK_GMAC		323
#घोषणा PCLK_MIPI_DSI		324
#घोषणा PCLK_MIPIDSIPHY		325
#घोषणा PCLK_MIPICSIPHY		326
#घोषणा PCLK_USB_GRF		327
#घोषणा PCLK_DCF		328
#घोषणा PCLK_UART1		329
#घोषणा PCLK_UART2		330
#घोषणा PCLK_UART3		331
#घोषणा PCLK_UART4		332
#घोषणा PCLK_UART5		333
#घोषणा PCLK_I2C0		334
#घोषणा PCLK_I2C1		335
#घोषणा PCLK_I2C2		336
#घोषणा PCLK_I2C3		337
#घोषणा PCLK_I2C4		338
#घोषणा PCLK_PWM0		339
#घोषणा PCLK_PWM1		340
#घोषणा PCLK_SPI0		341
#घोषणा PCLK_SPI1		342
#घोषणा PCLK_SARADC		343
#घोषणा PCLK_TSADC		344
#घोषणा PCLK_TIMER		345
#घोषणा PCLK_OTP_NS		346
#घोषणा PCLK_WDT_NS		347
#घोषणा PCLK_GPIO1		348
#घोषणा PCLK_GPIO2		349
#घोषणा PCLK_GPIO3		350
#घोषणा PCLK_ISP		351
#घोषणा PCLK_CIF		352
#घोषणा PCLK_OTP_PHY		353

#घोषणा CLK_NR_CLKS		(PCLK_OTP_PHY + 1)

/* pmu-घड़ीs indices */

#घोषणा PLL_GPLL		1

#घोषणा SCLK_RTC32K_PMU		4
#घोषणा SCLK_WIFI_PMU		5
#घोषणा SCLK_UART0_PMU		6
#घोषणा SCLK_PVTM_PMU		7
#घोषणा PCLK_PMU_PRE		8
#घोषणा SCLK_REF24M_PMU		9
#घोषणा SCLK_USBPHY_REF		10
#घोषणा SCLK_MIPIDSIPHY_REF	11

#घोषणा XIN24M_DIV		12

#घोषणा PCLK_GPIO0_PMU		20
#घोषणा PCLK_UART0_PMU		21

#घोषणा CLKPMU_NR_CLKS		(PCLK_UART0_PMU + 1)

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
#घोषणा SRST_CORE_NOC		13
#घोषणा SRST_STRC_A		14
#घोषणा SRST_L2C		15

#घोषणा SRST_DAP		16
#घोषणा SRST_CORE_PVTM		17
#घोषणा SRST_GPU		18
#घोषणा SRST_GPU_NIU		19
#घोषणा SRST_UPCTL2		20
#घोषणा SRST_UPCTL2_A		21
#घोषणा SRST_UPCTL2_P		22
#घोषणा SRST_MSCH		23
#घोषणा SRST_MSCH_P		24
#घोषणा SRST_DDRMON_P		25
#घोषणा SRST_DDRSTDBY_P		26
#घोषणा SRST_DDRSTDBY		27
#घोषणा SRST_DDRGRF_p		28
#घोषणा SRST_AXI_SPLIT_A	29
#घोषणा SRST_AXI_CMD_A		30
#घोषणा SRST_AXI_CMD_P		31

#घोषणा SRST_DDRPHY		32
#घोषणा SRST_DDRPHYDIV		33
#घोषणा SRST_DDRPHY_P		34
#घोषणा SRST_VPU_A		36
#घोषणा SRST_VPU_NIU_A		37
#घोषणा SRST_VPU_H		38
#घोषणा SRST_VPU_NIU_H		39
#घोषणा SRST_VI_NIU_A		40
#घोषणा SRST_VI_NIU_H		41
#घोषणा SRST_ISP_H		42
#घोषणा SRST_ISP		43
#घोषणा SRST_CIF_A		44
#घोषणा SRST_CIF_H		45
#घोषणा SRST_CIF_PCLKIN		46
#घोषणा SRST_MIPICSIPHY_P	47

#घोषणा SRST_VO_NIU_A		48
#घोषणा SRST_VO_NIU_H		49
#घोषणा SRST_VO_NIU_P		50
#घोषणा SRST_VOPB_A		51
#घोषणा SRST_VOPB_H		52
#घोषणा SRST_VOPB		53
#घोषणा SRST_PWM_VOPB		54
#घोषणा SRST_VOPL_A		55
#घोषणा SRST_VOPL_H		56
#घोषणा SRST_VOPL		57
#घोषणा SRST_RGA_A		58
#घोषणा SRST_RGA_H		59
#घोषणा SRST_RGA		60
#घोषणा SRST_MIPIDSI_HOST_P	61
#घोषणा SRST_MIPIDSIPHY_P	62
#घोषणा SRST_VPU_CORE		63

#घोषणा SRST_PERI_NIU_A		64
#घोषणा SRST_USB_NIU_H		65
#घोषणा SRST_USB2OTG_H		66
#घोषणा SRST_USB2OTG		67
#घोषणा SRST_USB2OTG_ADP	68
#घोषणा SRST_USB2HOST_H		69
#घोषणा SRST_USB2HOST_ARB_H	70
#घोषणा SRST_USB2HOST_AUX_H	71
#घोषणा SRST_USB2HOST_EHCI	72
#घोषणा SRST_USB2HOST		73
#घोषणा SRST_USBPHYPOR		74
#घोषणा SRST_USBPHY_OTG_PORT	75
#घोषणा SRST_USBPHY_HOST_PORT	76
#घोषणा SRST_USBPHY_GRF		77
#घोषणा SRST_CPU_BOOST_P	78
#घोषणा SRST_CPU_BOOST		79

#घोषणा SRST_MMC_न_अंकD_NIU_H	80
#घोषणा SRST_SDIO_H		81
#घोषणा SRST_EMMC_H		82
#घोषणा SRST_SFC_H		83
#घोषणा SRST_SFC		84
#घोषणा SRST_SDCARD_NIU_H	85
#घोषणा SRST_SDMMC_H		86
#घोषणा SRST_न_अंकDC_H		89
#घोषणा SRST_न_अंकDC		90
#घोषणा SRST_GMAC_NIU_A		92
#घोषणा SRST_GMAC_NIU_P		93
#घोषणा SRST_GMAC_A		94

#घोषणा SRST_PMU_NIU_P		96
#घोषणा SRST_PMU_SGRF_P		97
#घोषणा SRST_PMU_GRF_P		98
#घोषणा SRST_PMU		99
#घोषणा SRST_PMU_MEM_P		100
#घोषणा SRST_PMU_GPIO0_P	101
#घोषणा SRST_PMU_UART0_P	102
#घोषणा SRST_PMU_CRU_P		103
#घोषणा SRST_PMU_PVTM		104
#घोषणा SRST_PMU_UART		105
#घोषणा SRST_PMU_NIU_H		106
#घोषणा SRST_PMU_DDR_FAIL_SAVE	107
#घोषणा SRST_PMU_CORE_PERF_A	108
#घोषणा SRST_PMU_CORE_GRF_P	109
#घोषणा SRST_PMU_GPU_PERF_A	110
#घोषणा SRST_PMU_GPU_GRF_P	111

#घोषणा SRST_CRYPTO_NIU_A	112
#घोषणा SRST_CRYPTO_NIU_H	113
#घोषणा SRST_CRYPTO_A		114
#घोषणा SRST_CRYPTO_H		115
#घोषणा SRST_CRYPTO		116
#घोषणा SRST_CRYPTO_APK		117
#घोषणा SRST_BUS_NIU_H		120
#घोषणा SRST_USB_NIU_P		121
#घोषणा SRST_BUS_TOP_NIU_P	122
#घोषणा SRST_INTMEM_A		123
#घोषणा SRST_GIC_A		124
#घोषणा SRST_ROM_H		126
#घोषणा SRST_DCF_A		127

#घोषणा SRST_DCF_P		128
#घोषणा SRST_PDM_H		129
#घोषणा SRST_PDM		130
#घोषणा SRST_I2S0_H		131
#घोषणा SRST_I2S0_TX		132
#घोषणा SRST_I2S1_H		133
#घोषणा SRST_I2S1		134
#घोषणा SRST_I2S2_H		135
#घोषणा SRST_I2S2		136
#घोषणा SRST_UART1_P		137
#घोषणा SRST_UART1		138
#घोषणा SRST_UART2_P		139
#घोषणा SRST_UART2		140
#घोषणा SRST_UART3_P		141
#घोषणा SRST_UART3		142
#घोषणा SRST_UART4_P		143

#घोषणा SRST_UART4		144
#घोषणा SRST_UART5_P		145
#घोषणा SRST_UART5		146
#घोषणा SRST_I2C0_P		147
#घोषणा SRST_I2C0		148
#घोषणा SRST_I2C1_P		149
#घोषणा SRST_I2C1		150
#घोषणा SRST_I2C2_P		151
#घोषणा SRST_I2C2		152
#घोषणा SRST_I2C3_P		153
#घोषणा SRST_I2C3		154
#घोषणा SRST_PWM0_P		157
#घोषणा SRST_PWM0		158
#घोषणा SRST_PWM1_P		159

#घोषणा SRST_PWM1		160
#घोषणा SRST_SPI0_P		161
#घोषणा SRST_SPI0		162
#घोषणा SRST_SPI1_P		163
#घोषणा SRST_SPI1		164
#घोषणा SRST_SARADC_P		165
#घोषणा SRST_SARADC		166
#घोषणा SRST_TSADC_P		167
#घोषणा SRST_TSADC		168
#घोषणा SRST_TIMER_P		169
#घोषणा SRST_TIMER0		170
#घोषणा SRST_TIMER1		171
#घोषणा SRST_TIMER2		172
#घोषणा SRST_TIMER3		173
#घोषणा SRST_TIMER4		174
#घोषणा SRST_TIMER5		175

#घोषणा SRST_OTP_NS_P		176
#घोषणा SRST_OTP_NS_SBPI	177
#घोषणा SRST_OTP_NS_USR		178
#घोषणा SRST_OTP_PHY_P		179
#घोषणा SRST_OTP_PHY		180
#घोषणा SRST_WDT_NS_P		181
#घोषणा SRST_GPIO1_P		182
#घोषणा SRST_GPIO2_P		183
#घोषणा SRST_GPIO3_P		184
#घोषणा SRST_SGRF_P		185
#घोषणा SRST_GRF_P		186
#घोषणा SRST_I2S0_RX		191

#पूर्ण_अगर
