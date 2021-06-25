<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Unisoc SC9863A platक्रमm घड़ीs
 *
 * Copyright (C) 2019, Unisoc Communications Inc.
 */

#अगर_अघोषित _DT_BINDINGS_CLK_SC9863A_H_
#घोषणा _DT_BINDINGS_CLK_SC9863A_H_

#घोषणा CLK_MPLL0_GATE		0
#घोषणा CLK_DPLL0_GATE		1
#घोषणा CLK_LPLL_GATE		2
#घोषणा CLK_GPLL_GATE		3
#घोषणा CLK_DPLL1_GATE		4
#घोषणा CLK_MPLL1_GATE		5
#घोषणा CLK_MPLL2_GATE		6
#घोषणा CLK_ISPPLL_GATE		7
#घोषणा CLK_PMU_APB_NUM		(CLK_ISPPLL_GATE + 1)

#घोषणा CLK_AUDIO_GATE		0
#घोषणा CLK_RPLL		1
#घोषणा CLK_RPLL_390M		2
#घोषणा CLK_RPLL_260M		3
#घोषणा CLK_RPLL_195M		4
#घोषणा CLK_RPLL_26M		5
#घोषणा CLK_ANLG_PHY_G5_NUM	(CLK_RPLL_26M + 1)

#घोषणा CLK_TWPLL		0
#घोषणा CLK_TWPLL_768M		1
#घोषणा CLK_TWPLL_384M		2
#घोषणा CLK_TWPLL_192M		3
#घोषणा CLK_TWPLL_96M		4
#घोषणा CLK_TWPLL_48M		5
#घोषणा CLK_TWPLL_24M		6
#घोषणा CLK_TWPLL_12M		7
#घोषणा CLK_TWPLL_512M		8
#घोषणा CLK_TWPLL_256M		9
#घोषणा CLK_TWPLL_128M		10
#घोषणा CLK_TWPLL_64M		11
#घोषणा CLK_TWPLL_307M2		12
#घोषणा CLK_TWPLL_219M4		13
#घोषणा CLK_TWPLL_170M6		14
#घोषणा CLK_TWPLL_153M6		15
#घोषणा CLK_TWPLL_76M8		16
#घोषणा CLK_TWPLL_51M2		17
#घोषणा CLK_TWPLL_38M4		18
#घोषणा CLK_TWPLL_19M2		19
#घोषणा CLK_LPLL		20
#घोषणा CLK_LPLL_409M6		21
#घोषणा CLK_LPLL_245M76		22
#घोषणा CLK_GPLL		23
#घोषणा CLK_ISPPLL		24
#घोषणा CLK_ISPPLL_468M		25
#घोषणा CLK_ANLG_PHY_G1_NUM	(CLK_ISPPLL_468M + 1)

#घोषणा CLK_DPLL0		0
#घोषणा CLK_DPLL1		1
#घोषणा CLK_DPLL0_933M		2
#घोषणा CLK_DPLL0_622M3		3
#घोषणा CLK_DPLL0_400M		4
#घोषणा CLK_DPLL0_266M7		5
#घोषणा CLK_DPLL0_123M1		6
#घोषणा CLK_DPLL0_50M		7
#घोषणा CLK_ANLG_PHY_G7_NUM	(CLK_DPLL0_50M + 1)

#घोषणा CLK_MPLL0		0
#घोषणा CLK_MPLL1		1
#घोषणा CLK_MPLL2		2
#घोषणा CLK_MPLL2_675M		3
#घोषणा CLK_ANLG_PHY_G4_NUM	(CLK_MPLL2_675M + 1)

#घोषणा CLK_AP_APB		0
#घोषणा CLK_AP_CE		1
#घोषणा CLK_न_अंकDC_ECC		2
#घोषणा CLK_न_अंकDC_26M		3
#घोषणा CLK_EMMC_32K		4
#घोषणा CLK_SDIO0_32K		5
#घोषणा CLK_SDIO1_32K		6
#घोषणा CLK_SDIO2_32K		7
#घोषणा CLK_OTG_UTMI		8
#घोषणा CLK_AP_UART0		9
#घोषणा CLK_AP_UART1		10
#घोषणा CLK_AP_UART2		11
#घोषणा CLK_AP_UART3		12
#घोषणा CLK_AP_UART4		13
#घोषणा CLK_AP_I2C0		14
#घोषणा CLK_AP_I2C1		15
#घोषणा CLK_AP_I2C2		16
#घोषणा CLK_AP_I2C3		17
#घोषणा CLK_AP_I2C4		18
#घोषणा CLK_AP_I2C5		19
#घोषणा CLK_AP_I2C6		20
#घोषणा CLK_AP_SPI0		21
#घोषणा CLK_AP_SPI1		22
#घोषणा CLK_AP_SPI2		23
#घोषणा CLK_AP_SPI3		24
#घोषणा CLK_AP_IIS0		25
#घोषणा CLK_AP_IIS1		26
#घोषणा CLK_AP_IIS2		27
#घोषणा CLK_SIM0		28
#घोषणा CLK_SIM0_32K		29
#घोषणा CLK_AP_CLK_NUM		(CLK_SIM0_32K + 1)

#घोषणा CLK_13M			0
#घोषणा CLK_6M5			1
#घोषणा CLK_4M3			2
#घोषणा CLK_2M			3
#घोषणा CLK_250K		4
#घोषणा CLK_RCO_25M		5
#घोषणा CLK_RCO_4M		6
#घोषणा CLK_RCO_2M		7
#घोषणा CLK_EMC			8
#घोषणा CLK_AON_APB		9
#घोषणा CLK_ADI			10
#घोषणा CLK_AUX0		11
#घोषणा CLK_AUX1		12
#घोषणा CLK_AUX2		13
#घोषणा CLK_PROBE		14
#घोषणा CLK_PWM0		15
#घोषणा CLK_PWM1		16
#घोषणा CLK_PWM2		17
#घोषणा CLK_AON_THM		18
#घोषणा CLK_AUDIF		19
#घोषणा CLK_CPU_DAP		20
#घोषणा CLK_CPU_TS		21
#घोषणा CLK_DJTAG_TCK		22
#घोषणा CLK_EMC_REF		23
#घोषणा CLK_CSSYS		24
#घोषणा CLK_AON_PMU		25
#घोषणा CLK_PMU_26M		26
#घोषणा CLK_AON_TMR		27
#घोषणा CLK_POWER_CPU		28
#घोषणा CLK_AP_AXI		29
#घोषणा CLK_SDIO0_2X		30
#घोषणा CLK_SDIO1_2X		31
#घोषणा CLK_SDIO2_2X		32
#घोषणा CLK_EMMC_2X		33
#घोषणा CLK_DPU			34
#घोषणा CLK_DPU_DPI		35
#घोषणा CLK_OTG_REF		36
#घोषणा CLK_SDPHY_APB		37
#घोषणा CLK_ALG_IO_APB		38
#घोषणा CLK_GPU_CORE		39
#घोषणा CLK_GPU_SOC		40
#घोषणा CLK_MM_EMC		41
#घोषणा CLK_MM_AHB		42
#घोषणा CLK_BPC			43
#घोषणा CLK_DCAM_IF		44
#घोषणा CLK_ISP			45
#घोषणा CLK_JPG			46
#घोषणा CLK_CPP			47
#घोषणा CLK_SENSOR0		48
#घोषणा CLK_SENSOR1		49
#घोषणा CLK_SENSOR2		50
#घोषणा CLK_MM_VEMC		51
#घोषणा CLK_MM_VAHB		52
#घोषणा CLK_VSP			53
#घोषणा CLK_CORE0		54
#घोषणा CLK_CORE1		55
#घोषणा CLK_CORE2		56
#घोषणा CLK_CORE3		57
#घोषणा CLK_CORE4		58
#घोषणा CLK_CORE5		59
#घोषणा CLK_CORE6		60
#घोषणा CLK_CORE7		61
#घोषणा CLK_SCU			62
#घोषणा CLK_ACE			63
#घोषणा CLK_AXI_PERIPH		64
#घोषणा CLK_AXI_ACP		65
#घोषणा CLK_ATB			66
#घोषणा CLK_DEBUG_APB		67
#घोषणा CLK_GIC			68
#घोषणा CLK_PERIPH		69
#घोषणा CLK_AON_CLK_NUM		(CLK_VSP + 1)

#घोषणा CLK_OTG_EB		0
#घोषणा CLK_DMA_EB		1
#घोषणा CLK_CE_EB		2
#घोषणा CLK_न_अंकDC_EB		3
#घोषणा CLK_SDIO0_EB		4
#घोषणा CLK_SDIO1_EB		5
#घोषणा CLK_SDIO2_EB		6
#घोषणा CLK_EMMC_EB		7
#घोषणा CLK_EMMC_32K_EB		8
#घोषणा CLK_SDIO0_32K_EB	9
#घोषणा CLK_SDIO1_32K_EB	10
#घोषणा CLK_SDIO2_32K_EB	11
#घोषणा CLK_न_अंकDC_26M_EB	12
#घोषणा CLK_DMA_EB2		13
#घोषणा CLK_CE_EB2		14
#घोषणा CLK_AP_AHB_GATE_NUM	(CLK_CE_EB2 + 1)

#घोषणा CLK_GPIO_EB		0
#घोषणा CLK_PWM0_EB		1
#घोषणा CLK_PWM1_EB		2
#घोषणा CLK_PWM2_EB		3
#घोषणा CLK_PWM3_EB		4
#घोषणा CLK_KPD_EB		5
#घोषणा CLK_AON_SYST_EB		6
#घोषणा CLK_AP_SYST_EB		7
#घोषणा CLK_AON_TMR_EB		8
#घोषणा CLK_EFUSE_EB		9
#घोषणा CLK_EIC_EB		10
#घोषणा CLK_INTC_EB		11
#घोषणा CLK_ADI_EB		12
#घोषणा CLK_AUDIF_EB		13
#घोषणा CLK_AUD_EB		14
#घोषणा CLK_VBC_EB		15
#घोषणा CLK_PIN_EB		16
#घोषणा CLK_AP_WDG_EB		17
#घोषणा CLK_MM_EB		18
#घोषणा CLK_AON_APB_CKG_EB	19
#घोषणा CLK_CA53_TS0_EB		20
#घोषणा CLK_CA53_TS1_EB		21
#घोषणा CLK_CS53_DAP_EB		22
#घोषणा CLK_PMU_EB		23
#घोषणा CLK_THM_EB		24
#घोषणा CLK_AUX0_EB		25
#घोषणा CLK_AUX1_EB		26
#घोषणा CLK_AUX2_EB		27
#घोषणा CLK_PROBE_EB		28
#घोषणा CLK_EMC_REF_EB		29
#घोषणा CLK_CA53_WDG_EB		30
#घोषणा CLK_AP_TMR1_EB		31
#घोषणा CLK_AP_TMR2_EB		32
#घोषणा CLK_DISP_EMC_EB		33
#घोषणा CLK_ZIP_EMC_EB		34
#घोषणा CLK_GSP_EMC_EB		35
#घोषणा CLK_MM_VSP_EB		36
#घोषणा CLK_MDAR_EB		37
#घोषणा CLK_RTC4M0_CAL_EB	38
#घोषणा CLK_RTC4M1_CAL_EB	39
#घोषणा CLK_DJTAG_EB		40
#घोषणा CLK_MBOX_EB		41
#घोषणा CLK_AON_DMA_EB		42
#घोषणा CLK_AON_APB_DEF_EB	43
#घोषणा CLK_CA5_TS0_EB		44
#घोषणा CLK_DBG_EB		45
#घोषणा CLK_DBG_EMC_EB		46
#घोषणा CLK_CROSS_TRIG_EB	47
#घोषणा CLK_SERDES_DPHY_EB	48
#घोषणा CLK_ARCH_RTC_EB		49
#घोषणा CLK_KPD_RTC_EB		50
#घोषणा CLK_AON_SYST_RTC_EB	51
#घोषणा CLK_AP_SYST_RTC_EB	52
#घोषणा CLK_AON_TMR_RTC_EB	53
#घोषणा CLK_AP_TMR0_RTC_EB	54
#घोषणा CLK_EIC_RTC_EB		55
#घोषणा CLK_EIC_RTCDV5_EB	56
#घोषणा CLK_AP_WDG_RTC_EB	57
#घोषणा CLK_CA53_WDG_RTC_EB	58
#घोषणा CLK_THM_RTC_EB		59
#घोषणा CLK_ATHMA_RTC_EB	60
#घोषणा CLK_GTHMA_RTC_EB	61
#घोषणा CLK_ATHMA_RTC_A_EB	62
#घोषणा CLK_GTHMA_RTC_A_EB	63
#घोषणा CLK_AP_TMR1_RTC_EB	64
#घोषणा CLK_AP_TMR2_RTC_EB	65
#घोषणा CLK_DXCO_LC_RTC_EB	66
#घोषणा CLK_BB_CAL_RTC_EB	67
#घोषणा CLK_GNU_EB		68
#घोषणा CLK_DISP_EB		69
#घोषणा CLK_MM_EMC_EB		70
#घोषणा CLK_POWER_CPU_EB	71
#घोषणा CLK_HW_I2C_EB		72
#घोषणा CLK_MM_VSP_EMC_EB	73
#घोषणा CLK_VSP_EB		74
#घोषणा CLK_CSSYS_EB		75
#घोषणा CLK_DMC_EB		76
#घोषणा CLK_ROSC_EB		77
#घोषणा CLK_S_D_CFG_EB		78
#घोषणा CLK_S_D_REF_EB		79
#घोषणा CLK_B_DMA_EB		80
#घोषणा CLK_ANLG_EB		81
#घोषणा CLK_ANLG_APB_EB		82
#घोषणा CLK_BSMTMR_EB		83
#घोषणा CLK_AP_AXI_EB		84
#घोषणा CLK_AP_INTC0_EB		85
#घोषणा CLK_AP_INTC1_EB		86
#घोषणा CLK_AP_INTC2_EB		87
#घोषणा CLK_AP_INTC3_EB		88
#घोषणा CLK_AP_INTC4_EB		89
#घोषणा CLK_AP_INTC5_EB		90
#घोषणा CLK_SCC_EB		91
#घोषणा CLK_DPHY_CFG_EB		92
#घोषणा CLK_DPHY_REF_EB		93
#घोषणा CLK_CPHY_CFG_EB		94
#घोषणा CLK_OTG_REF_EB		95
#घोषणा CLK_SERDES_EB		96
#घोषणा CLK_AON_AP_EMC_EB	97
#घोषणा CLK_AON_APB_GATE_NUM	(CLK_AON_AP_EMC_EB + 1)

#घोषणा CLK_MAHB_CKG_EB		0
#घोषणा CLK_MDCAM_EB		1
#घोषणा CLK_MISP_EB		2
#घोषणा CLK_MAHBCSI_EB		3
#घोषणा CLK_MCSI_S_EB		4
#घोषणा CLK_MCSI_T_EB		5
#घोषणा CLK_DCAM_AXI_EB		6
#घोषणा CLK_ISP_AXI_EB		7
#घोषणा CLK_MCSI_EB		8
#घोषणा CLK_MCSI_S_CKG_EB	9
#घोषणा CLK_MCSI_T_CKG_EB	10
#घोषणा CLK_SENSOR0_EB		11
#घोषणा CLK_SENSOR1_EB		12
#घोषणा CLK_SENSOR2_EB		13
#घोषणा CLK_MCPHY_CFG_EB	14
#घोषणा CLK_MM_GATE_NUM		(CLK_MCPHY_CFG_EB + 1)

#घोषणा CLK_MIPI_CSI		0
#घोषणा CLK_MIPI_CSI_S		1
#घोषणा CLK_MIPI_CSI_M		2
#घोषणा CLK_MM_CLK_NUM		(CLK_MIPI_CSI_M + 1)

#घोषणा CLK_SIM0_EB		0
#घोषणा CLK_IIS0_EB		1
#घोषणा CLK_IIS1_EB		2
#घोषणा CLK_IIS2_EB		3
#घोषणा CLK_SPI0_EB		4
#घोषणा CLK_SPI1_EB		5
#घोषणा CLK_SPI2_EB		6
#घोषणा CLK_I2C0_EB		7
#घोषणा CLK_I2C1_EB		8
#घोषणा CLK_I2C2_EB		9
#घोषणा CLK_I2C3_EB		10
#घोषणा CLK_I2C4_EB		11
#घोषणा CLK_UART0_EB		12
#घोषणा CLK_UART1_EB		13
#घोषणा CLK_UART2_EB		14
#घोषणा CLK_UART3_EB		15
#घोषणा CLK_UART4_EB		16
#घोषणा CLK_SIM0_32K_EB		17
#घोषणा CLK_SPI3_EB		18
#घोषणा CLK_I2C5_EB		19
#घोषणा CLK_I2C6_EB		20
#घोषणा CLK_AP_APB_GATE_NUM	(CLK_I2C6_EB + 1)

#पूर्ण_अगर /* _DT_BINDINGS_CLK_SC9863A_H_ */
