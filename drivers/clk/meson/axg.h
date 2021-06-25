<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2016 AmLogic, Inc.
 * Author: Michael Turquette <mturquette@baylibre.com>
 *
 * Copyright (c) 2017 Amlogic, inc.
 * Author: Qiufang Dai <qiufang.dai@amlogic.com>
 *
 */
#अगर_अघोषित __AXG_H
#घोषणा __AXG_H

/*
 * Clock controller रेजिस्टर offsets
 *
 * Register offsets from the data sheet must be multiplied by 4 beक्रमe
 * adding them to the base address to get the right value.
 */
#घोषणा HHI_GP0_PLL_CNTL		0x40
#घोषणा HHI_GP0_PLL_CNTL2		0x44
#घोषणा HHI_GP0_PLL_CNTL3		0x48
#घोषणा HHI_GP0_PLL_CNTL4		0x4c
#घोषणा HHI_GP0_PLL_CNTL5		0x50
#घोषणा HHI_GP0_PLL_STS			0x54
#घोषणा HHI_GP0_PLL_CNTL1		0x58
#घोषणा HHI_HIFI_PLL_CNTL		0x80
#घोषणा HHI_HIFI_PLL_CNTL2		0x84
#घोषणा HHI_HIFI_PLL_CNTL3		0x88
#घोषणा HHI_HIFI_PLL_CNTL4		0x8C
#घोषणा HHI_HIFI_PLL_CNTL5		0x90
#घोषणा HHI_HIFI_PLL_STS		0x94
#घोषणा HHI_HIFI_PLL_CNTL1		0x98

#घोषणा HHI_XTAL_DIVN_CNTL		0xbc
#घोषणा HHI_GCLK2_MPEG0			0xc0
#घोषणा HHI_GCLK2_MPEG1			0xc4
#घोषणा HHI_GCLK2_MPEG2			0xc8
#घोषणा HHI_GCLK2_OTHER			0xd0
#घोषणा HHI_GCLK2_AO			0xd4
#घोषणा HHI_PCIE_PLL_CNTL		0xd8
#घोषणा HHI_PCIE_PLL_CNTL1		0xdC
#घोषणा HHI_PCIE_PLL_CNTL2		0xe0
#घोषणा HHI_PCIE_PLL_CNTL3		0xe4
#घोषणा HHI_PCIE_PLL_CNTL4		0xe8
#घोषणा HHI_PCIE_PLL_CNTL5		0xec
#घोषणा HHI_PCIE_PLL_CNTL6		0xf0
#घोषणा HHI_PCIE_PLL_STS		0xf4

#घोषणा HHI_MEM_PD_REG0			0x100
#घोषणा HHI_VPU_MEM_PD_REG0		0x104
#घोषणा HHI_VIID_CLK_DIV		0x128
#घोषणा HHI_VIID_CLK_CNTL		0x12c

#घोषणा HHI_GCLK_MPEG0			0x140
#घोषणा HHI_GCLK_MPEG1			0x144
#घोषणा HHI_GCLK_MPEG2			0x148
#घोषणा HHI_GCLK_OTHER			0x150
#घोषणा HHI_GCLK_AO			0x154
#घोषणा HHI_SYS_CPU_CLK_CNTL1		0x15c
#घोषणा HHI_SYS_CPU_RESET_CNTL		0x160
#घोषणा HHI_VID_CLK_DIV			0x164
#घोषणा HHI_SPICC_HCLK_CNTL		0x168

#घोषणा HHI_MPEG_CLK_CNTL		0x174
#घोषणा HHI_VID_CLK_CNTL		0x17c
#घोषणा HHI_TS_CLK_CNTL			0x190
#घोषणा HHI_VID_CLK_CNTL2		0x194
#घोषणा HHI_SYS_CPU_CLK_CNTL0		0x19c
#घोषणा HHI_VID_PLL_CLK_DIV		0x1a0
#घोषणा HHI_VPU_CLK_CNTL		0x1bC

#घोषणा HHI_VAPBCLK_CNTL		0x1F4

#घोषणा HHI_GEN_CLK_CNTL		0x228

#घोषणा HHI_VDIN_MEAS_CLK_CNTL		0x250
#घोषणा HHI_न_अंकD_CLK_CNTL		0x25C
#घोषणा HHI_SD_EMMC_CLK_CNTL		0x264

#घोषणा HHI_MPLL_CNTL			0x280
#घोषणा HHI_MPLL_CNTL2			0x284
#घोषणा HHI_MPLL_CNTL3			0x288
#घोषणा HHI_MPLL_CNTL4			0x28C
#घोषणा HHI_MPLL_CNTL5			0x290
#घोषणा HHI_MPLL_CNTL6			0x294
#घोषणा HHI_MPLL_CNTL7			0x298
#घोषणा HHI_MPLL_CNTL8			0x29C
#घोषणा HHI_MPLL_CNTL9			0x2A0
#घोषणा HHI_MPLL_CNTL10			0x2A4

#घोषणा HHI_MPLL3_CNTL0			0x2E0
#घोषणा HHI_MPLL3_CNTL1			0x2E4
#घोषणा HHI_PLL_TOP_MISC		0x2E8

#घोषणा HHI_SYS_PLL_CNTL1		0x2FC
#घोषणा HHI_SYS_PLL_CNTL		0x300
#घोषणा HHI_SYS_PLL_CNTL2		0x304
#घोषणा HHI_SYS_PLL_CNTL3		0x308
#घोषणा HHI_SYS_PLL_CNTL4		0x30c
#घोषणा HHI_SYS_PLL_CNTL5		0x310
#घोषणा HHI_SYS_PLL_STS			0x314
#घोषणा HHI_DPLL_TOP_I			0x318
#घोषणा HHI_DPLL_TOP2_I			0x31C

/*
 * CLKID index values
 *
 * These indices are entirely contrived and करो not map onto the hardware.
 * It has now been decided to expose everything by शेष in the DT header:
 * include/dt-bindings/घड़ी/axg-clkc.h. Only the घड़ीs ids we करोn't want
 * to expose, such as the पूर्णांकernal muxes and भागiders of composite घड़ीs,
 * will reमुख्य defined here.
 */
#घोषणा CLKID_MPEG_SEL				8
#घोषणा CLKID_MPEG_DIV				9
#घोषणा CLKID_SD_EMMC_B_CLK0_SEL		61
#घोषणा CLKID_SD_EMMC_B_CLK0_DIV		62
#घोषणा CLKID_SD_EMMC_C_CLK0_SEL		63
#घोषणा CLKID_SD_EMMC_C_CLK0_DIV		64
#घोषणा CLKID_MPLL0_DIV				65
#घोषणा CLKID_MPLL1_DIV				66
#घोषणा CLKID_MPLL2_DIV				67
#घोषणा CLKID_MPLL3_DIV				68
#घोषणा CLKID_MPLL_PREDIV			70
#घोषणा CLKID_FCLK_DIV2_DIV			71
#घोषणा CLKID_FCLK_DIV3_DIV			72
#घोषणा CLKID_FCLK_DIV4_DIV			73
#घोषणा CLKID_FCLK_DIV5_DIV			74
#घोषणा CLKID_FCLK_DIV7_DIV			75
#घोषणा CLKID_PCIE_PLL				76
#घोषणा CLKID_PCIE_MUX				77
#घोषणा CLKID_PCIE_REF				78
#घोषणा CLKID_GEN_CLK_SEL			82
#घोषणा CLKID_GEN_CLK_DIV			83
#घोषणा CLKID_SYS_PLL_DCO			85
#घोषणा CLKID_FIXED_PLL_DCO			86
#घोषणा CLKID_GP0_PLL_DCO			87
#घोषणा CLKID_HIFI_PLL_DCO			88
#घोषणा CLKID_PCIE_PLL_DCO			89
#घोषणा CLKID_PCIE_PLL_OD			90
#घोषणा CLKID_VPU_0_DIV				91
#घोषणा CLKID_VPU_1_DIV				94
#घोषणा CLKID_VAPB_0_DIV			98
#घोषणा CLKID_VAPB_1_DIV			101
#घोषणा CLKID_VCLK_SEL				108
#घोषणा CLKID_VCLK2_SEL				109
#घोषणा CLKID_VCLK_INPUT			110
#घोषणा CLKID_VCLK2_INPUT			111
#घोषणा CLKID_VCLK_DIV				112
#घोषणा CLKID_VCLK2_DIV				113
#घोषणा CLKID_VCLK_DIV2_EN			114
#घोषणा CLKID_VCLK_DIV4_EN			115
#घोषणा CLKID_VCLK_DIV6_EN			116
#घोषणा CLKID_VCLK_DIV12_EN			117
#घोषणा CLKID_VCLK2_DIV2_EN			118
#घोषणा CLKID_VCLK2_DIV4_EN			119
#घोषणा CLKID_VCLK2_DIV6_EN			120
#घोषणा CLKID_VCLK2_DIV12_EN			121
#घोषणा CLKID_CTS_ENCL_SEL			132
#घोषणा CLKID_VDIN_MEAS_SEL			134
#घोषणा CLKID_VDIN_MEAS_DIV			135

#घोषणा NR_CLKS					137

/* include the CLKIDs that have been made part of the DT binding */
#समावेश <dt-bindings/घड़ी/axg-clkc.h>

#पूर्ण_अगर /* __AXG_H */
