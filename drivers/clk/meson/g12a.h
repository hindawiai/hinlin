<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2016 Amlogic, Inc.
 * Author: Michael Turquette <mturquette@baylibre.com>
 *
 * Copyright (c) 2018 Amlogic, inc.
 * Author: Qiufang Dai <qiufang.dai@amlogic.com>
 * Author: Jian Hu <jian.hu@amlogic.com>
 *
 */
#अगर_अघोषित __G12A_H
#घोषणा __G12A_H

/*
 * Clock controller रेजिस्टर offsets
 *
 * Register offsets from the data sheet must be multiplied by 4 beक्रमe
 * adding them to the base address to get the right value.
 */
#घोषणा HHI_MIPI_CNTL0			0x000
#घोषणा HHI_MIPI_CNTL1			0x004
#घोषणा HHI_MIPI_CNTL2			0x008
#घोषणा HHI_MIPI_STS			0x00C
#घोषणा HHI_GP0_PLL_CNTL0		0x040
#घोषणा HHI_GP0_PLL_CNTL1		0x044
#घोषणा HHI_GP0_PLL_CNTL2		0x048
#घोषणा HHI_GP0_PLL_CNTL3		0x04C
#घोषणा HHI_GP0_PLL_CNTL4		0x050
#घोषणा HHI_GP0_PLL_CNTL5		0x054
#घोषणा HHI_GP0_PLL_CNTL6		0x058
#घोषणा HHI_GP0_PLL_STS			0x05C
#घोषणा HHI_GP1_PLL_CNTL0		0x060
#घोषणा HHI_GP1_PLL_CNTL1		0x064
#घोषणा HHI_GP1_PLL_CNTL2		0x068
#घोषणा HHI_GP1_PLL_CNTL3		0x06C
#घोषणा HHI_GP1_PLL_CNTL4		0x070
#घोषणा HHI_GP1_PLL_CNTL5		0x074
#घोषणा HHI_GP1_PLL_CNTL6		0x078
#घोषणा HHI_GP1_PLL_STS			0x07C
#घोषणा HHI_PCIE_PLL_CNTL0		0x098
#घोषणा HHI_PCIE_PLL_CNTL1		0x09C
#घोषणा HHI_PCIE_PLL_CNTL2		0x0A0
#घोषणा HHI_PCIE_PLL_CNTL3		0x0A4
#घोषणा HHI_PCIE_PLL_CNTL4		0x0A8
#घोषणा HHI_PCIE_PLL_CNTL5		0x0AC
#घोषणा HHI_PCIE_PLL_STS		0x0B8
#घोषणा HHI_HIFI_PLL_CNTL0		0x0D8
#घोषणा HHI_HIFI_PLL_CNTL1		0x0DC
#घोषणा HHI_HIFI_PLL_CNTL2		0x0E0
#घोषणा HHI_HIFI_PLL_CNTL3		0x0E4
#घोषणा HHI_HIFI_PLL_CNTL4		0x0E8
#घोषणा HHI_HIFI_PLL_CNTL5		0x0EC
#घोषणा HHI_HIFI_PLL_CNTL6		0x0F0
#घोषणा HHI_VIID_CLK_DIV		0x128
#घोषणा HHI_VIID_CLK_CNTL		0x12C
#घोषणा HHI_GCLK_MPEG0			0x140
#घोषणा HHI_GCLK_MPEG1			0x144
#घोषणा HHI_GCLK_MPEG2			0x148
#घोषणा HHI_GCLK_OTHER			0x150
#घोषणा HHI_GCLK_OTHER2			0x154
#घोषणा HHI_SYS_CPU_CLK_CNTL1		0x15c
#घोषणा HHI_VID_CLK_DIV			0x164
#घोषणा HHI_MPEG_CLK_CNTL		0x174
#घोषणा HHI_AUD_CLK_CNTL		0x178
#घोषणा HHI_VID_CLK_CNTL		0x17c
#घोषणा HHI_TS_CLK_CNTL			0x190
#घोषणा HHI_VID_CLK_CNTL2		0x194
#घोषणा HHI_SYS_CPU_CLK_CNTL0		0x19c
#घोषणा HHI_VID_PLL_CLK_DIV		0x1A0
#घोषणा HHI_MALI_CLK_CNTL		0x1b0
#घोषणा HHI_VPU_CLKC_CNTL		0x1b4
#घोषणा HHI_VPU_CLK_CNTL		0x1bC
#घोषणा HHI_NNA_CLK_CNTL		0x1C8
#घोषणा HHI_HDMI_CLK_CNTL		0x1CC
#घोषणा HHI_VDEC_CLK_CNTL		0x1E0
#घोषणा HHI_VDEC2_CLK_CNTL		0x1E4
#घोषणा HHI_VDEC3_CLK_CNTL		0x1E8
#घोषणा HHI_VDEC4_CLK_CNTL		0x1EC
#घोषणा HHI_HDCP22_CLK_CNTL		0x1F0
#घोषणा HHI_VAPBCLK_CNTL		0x1F4
#घोषणा HHI_SYS_CPUB_CLK_CNTL1		0x200
#घोषणा HHI_SYS_CPUB_CLK_CNTL		0x208
#घोषणा HHI_VPU_CLKB_CNTL		0x20C
#घोषणा HHI_SYS_CPU_CLK_CNTL2		0x210
#घोषणा HHI_SYS_CPU_CLK_CNTL3		0x214
#घोषणा HHI_SYS_CPU_CLK_CNTL4		0x218
#घोषणा HHI_SYS_CPU_CLK_CNTL5		0x21c
#घोषणा HHI_SYS_CPU_CLK_CNTL6		0x220
#घोषणा HHI_GEN_CLK_CNTL		0x228
#घोषणा HHI_VDIN_MEAS_CLK_CNTL		0x250
#घोषणा HHI_MIPIDSI_PHY_CLK_CNTL	0x254
#घोषणा HHI_न_अंकD_CLK_CNTL		0x25C
#घोषणा HHI_SD_EMMC_CLK_CNTL		0x264
#घोषणा HHI_MPLL_CNTL0			0x278
#घोषणा HHI_MPLL_CNTL1			0x27C
#घोषणा HHI_MPLL_CNTL2			0x280
#घोषणा HHI_MPLL_CNTL3			0x284
#घोषणा HHI_MPLL_CNTL4			0x288
#घोषणा HHI_MPLL_CNTL5			0x28c
#घोषणा HHI_MPLL_CNTL6			0x290
#घोषणा HHI_MPLL_CNTL7			0x294
#घोषणा HHI_MPLL_CNTL8			0x298
#घोषणा HHI_FIX_PLL_CNTL0		0x2A0
#घोषणा HHI_FIX_PLL_CNTL1		0x2A4
#घोषणा HHI_FIX_PLL_CNTL3		0x2AC
#घोषणा HHI_SYS_PLL_CNTL0		0x2f4
#घोषणा HHI_SYS_PLL_CNTL1		0x2f8
#घोषणा HHI_SYS_PLL_CNTL2		0x2fc
#घोषणा HHI_SYS_PLL_CNTL3		0x300
#घोषणा HHI_SYS_PLL_CNTL4		0x304
#घोषणा HHI_SYS_PLL_CNTL5		0x308
#घोषणा HHI_SYS_PLL_CNTL6		0x30c
#घोषणा HHI_HDMI_PLL_CNTL0		0x320
#घोषणा HHI_HDMI_PLL_CNTL1		0x324
#घोषणा HHI_HDMI_PLL_CNTL2		0x328
#घोषणा HHI_HDMI_PLL_CNTL3		0x32c
#घोषणा HHI_HDMI_PLL_CNTL4		0x330
#घोषणा HHI_HDMI_PLL_CNTL5		0x334
#घोषणा HHI_HDMI_PLL_CNTL6		0x338
#घोषणा HHI_SPICC_CLK_CNTL		0x3dc
#घोषणा HHI_SYS1_PLL_CNTL0		0x380
#घोषणा HHI_SYS1_PLL_CNTL1		0x384
#घोषणा HHI_SYS1_PLL_CNTL2		0x388
#घोषणा HHI_SYS1_PLL_CNTL3		0x38c
#घोषणा HHI_SYS1_PLL_CNTL4		0x390
#घोषणा HHI_SYS1_PLL_CNTL5		0x394
#घोषणा HHI_SYS1_PLL_CNTL6		0x398

/*
 * CLKID index values
 *
 * These indices are entirely contrived and करो not map onto the hardware.
 * It has now been decided to expose everything by शेष in the DT header:
 * include/dt-bindings/घड़ी/g12a-clkc.h. Only the घड़ीs ids we करोn't want
 * to expose, such as the पूर्णांकernal muxes and भागiders of composite घड़ीs,
 * will reमुख्य defined here.
 */
#घोषणा CLKID_MPEG_SEL				8
#घोषणा CLKID_MPEG_DIV				9
#घोषणा CLKID_SD_EMMC_A_CLK0_SEL		63
#घोषणा CLKID_SD_EMMC_A_CLK0_DIV		64
#घोषणा CLKID_SD_EMMC_B_CLK0_SEL		65
#घोषणा CLKID_SD_EMMC_B_CLK0_DIV		66
#घोषणा CLKID_SD_EMMC_C_CLK0_SEL		67
#घोषणा CLKID_SD_EMMC_C_CLK0_DIV		68
#घोषणा CLKID_MPLL0_DIV				69
#घोषणा CLKID_MPLL1_DIV				70
#घोषणा CLKID_MPLL2_DIV				71
#घोषणा CLKID_MPLL3_DIV				72
#घोषणा CLKID_MPLL_PREDIV			73
#घोषणा CLKID_FCLK_DIV2_DIV			75
#घोषणा CLKID_FCLK_DIV3_DIV			76
#घोषणा CLKID_FCLK_DIV4_DIV			77
#घोषणा CLKID_FCLK_DIV5_DIV			78
#घोषणा CLKID_FCLK_DIV7_DIV			79
#घोषणा CLKID_FCLK_DIV2P5_DIV			100
#घोषणा CLKID_FIXED_PLL_DCO			101
#घोषणा CLKID_SYS_PLL_DCO			102
#घोषणा CLKID_GP0_PLL_DCO			103
#घोषणा CLKID_HIFI_PLL_DCO			104
#घोषणा CLKID_VPU_0_DIV				111
#घोषणा CLKID_VPU_1_DIV				114
#घोषणा CLKID_VAPB_0_DIV			118
#घोषणा CLKID_VAPB_1_DIV			121
#घोषणा CLKID_HDMI_PLL_DCO			125
#घोषणा CLKID_HDMI_PLL_OD			126
#घोषणा CLKID_HDMI_PLL_OD2			127
#घोषणा CLKID_VID_PLL_SEL			130
#घोषणा CLKID_VID_PLL_DIV			131
#घोषणा CLKID_VCLK_SEL				132
#घोषणा CLKID_VCLK2_SEL				133
#घोषणा CLKID_VCLK_INPUT			134
#घोषणा CLKID_VCLK2_INPUT			135
#घोषणा CLKID_VCLK_DIV				136
#घोषणा CLKID_VCLK2_DIV				137
#घोषणा CLKID_VCLK_DIV2_EN			140
#घोषणा CLKID_VCLK_DIV4_EN			141
#घोषणा CLKID_VCLK_DIV6_EN			142
#घोषणा CLKID_VCLK_DIV12_EN			143
#घोषणा CLKID_VCLK2_DIV2_EN			144
#घोषणा CLKID_VCLK2_DIV4_EN			145
#घोषणा CLKID_VCLK2_DIV6_EN			146
#घोषणा CLKID_VCLK2_DIV12_EN			147
#घोषणा CLKID_CTS_ENCI_SEL			158
#घोषणा CLKID_CTS_ENCP_SEL			159
#घोषणा CLKID_CTS_VDAC_SEL			160
#घोषणा CLKID_HDMI_TX_SEL			161
#घोषणा CLKID_HDMI_SEL				166
#घोषणा CLKID_HDMI_DIV				167
#घोषणा CLKID_MALI_0_DIV			170
#घोषणा CLKID_MALI_1_DIV			173
#घोषणा CLKID_MPLL_50M_DIV			176
#घोषणा CLKID_SYS_PLL_DIV16_EN			178
#घोषणा CLKID_SYS_PLL_DIV16			179
#घोषणा CLKID_CPU_CLK_DYN0_SEL			180
#घोषणा CLKID_CPU_CLK_DYN0_DIV			181
#घोषणा CLKID_CPU_CLK_DYN0			182
#घोषणा CLKID_CPU_CLK_DYN1_SEL			183
#घोषणा CLKID_CPU_CLK_DYN1_DIV			184
#घोषणा CLKID_CPU_CLK_DYN1			185
#घोषणा CLKID_CPU_CLK_DYN			186
#घोषणा CLKID_CPU_CLK_DIV16_EN			188
#घोषणा CLKID_CPU_CLK_DIV16			189
#घोषणा CLKID_CPU_CLK_APB_DIV			190
#घोषणा CLKID_CPU_CLK_APB			191
#घोषणा CLKID_CPU_CLK_ATB_DIV			192
#घोषणा CLKID_CPU_CLK_ATB			193
#घोषणा CLKID_CPU_CLK_AXI_DIV			194
#घोषणा CLKID_CPU_CLK_AXI			195
#घोषणा CLKID_CPU_CLK_TRACE_DIV			196
#घोषणा CLKID_CPU_CLK_TRACE			197
#घोषणा CLKID_PCIE_PLL_DCO			198
#घोषणा CLKID_PCIE_PLL_DCO_DIV2			199
#घोषणा CLKID_PCIE_PLL_OD			200
#घोषणा CLKID_VDEC_1_SEL			202
#घोषणा CLKID_VDEC_1_DIV			203
#घोषणा CLKID_VDEC_HEVC_SEL			205
#घोषणा CLKID_VDEC_HEVC_DIV			206
#घोषणा CLKID_VDEC_HEVCF_SEL			208
#घोषणा CLKID_VDEC_HEVCF_DIV			209
#घोषणा CLKID_TS_DIV				211
#घोषणा CLKID_SYS1_PLL_DCO			213
#घोषणा CLKID_SYS1_PLL				214
#घोषणा CLKID_SYS1_PLL_DIV16_EN			215
#घोषणा CLKID_SYS1_PLL_DIV16			216
#घोषणा CLKID_CPUB_CLK_DYN0_SEL			217
#घोषणा CLKID_CPUB_CLK_DYN0_DIV			218
#घोषणा CLKID_CPUB_CLK_DYN0			219
#घोषणा CLKID_CPUB_CLK_DYN1_SEL			220
#घोषणा CLKID_CPUB_CLK_DYN1_DIV			221
#घोषणा CLKID_CPUB_CLK_DYN1			222
#घोषणा CLKID_CPUB_CLK_DYN			223
#घोषणा CLKID_CPUB_CLK_DIV16_EN			225
#घोषणा CLKID_CPUB_CLK_DIV16			226
#घोषणा CLKID_CPUB_CLK_DIV2			227
#घोषणा CLKID_CPUB_CLK_DIV3			228
#घोषणा CLKID_CPUB_CLK_DIV4			229
#घोषणा CLKID_CPUB_CLK_DIV5			230
#घोषणा CLKID_CPUB_CLK_DIV6			231
#घोषणा CLKID_CPUB_CLK_DIV7			232
#घोषणा CLKID_CPUB_CLK_DIV8			233
#घोषणा CLKID_CPUB_CLK_APB_SEL			234
#घोषणा CLKID_CPUB_CLK_APB			235
#घोषणा CLKID_CPUB_CLK_ATB_SEL			236
#घोषणा CLKID_CPUB_CLK_ATB			237
#घोषणा CLKID_CPUB_CLK_AXI_SEL			238
#घोषणा CLKID_CPUB_CLK_AXI			239
#घोषणा CLKID_CPUB_CLK_TRACE_SEL		240
#घोषणा CLKID_CPUB_CLK_TRACE			241
#घोषणा CLKID_GP1_PLL_DCO			242
#घोषणा CLKID_DSU_CLK_DYN0_SEL			244
#घोषणा CLKID_DSU_CLK_DYN0_DIV			245
#घोषणा CLKID_DSU_CLK_DYN0			246
#घोषणा CLKID_DSU_CLK_DYN1_SEL			247
#घोषणा CLKID_DSU_CLK_DYN1_DIV			248
#घोषणा CLKID_DSU_CLK_DYN1			249
#घोषणा CLKID_DSU_CLK_DYN			250
#घोषणा CLKID_DSU_CLK_FINAL			251
#घोषणा CLKID_SPICC0_SCLK_SEL			256
#घोषणा CLKID_SPICC0_SCLK_DIV			257
#घोषणा CLKID_SPICC1_SCLK_SEL			259
#घोषणा CLKID_SPICC1_SCLK_DIV			260
#घोषणा CLKID_NNA_AXI_CLK_SEL			262
#घोषणा CLKID_NNA_AXI_CLK_DIV			263
#घोषणा CLKID_NNA_CORE_CLK_SEL			265
#घोषणा CLKID_NNA_CORE_CLK_DIV			266
#घोषणा CLKID_MIPI_DSI_PXCLK_DIV		268

#घोषणा NR_CLKS					271

/* include the CLKIDs that have been made part of the DT binding */
#समावेश <dt-bindings/घड़ी/g12a-clkc.h>

#पूर्ण_अगर /* __G12A_H */
