<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AppliedMicro X-Gene Multi-purpose PHY driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Loc Ho <lho@apm.com>
 *         Tuan Phan <tphan@apm.com>
 *         Suman Tripathi <stripathi@apm.com>
 *
 * The APM X-Gene PHY consists of two PLL घड़ी macro's (CMU) and lanes.
 * The first PLL घड़ी macro is used क्रम पूर्णांकernal reference घड़ी. The second
 * PLL घड़ी macro is used to generate the घड़ी क्रम the PHY. This driver
 * configures the first PLL CMU, the second PLL CMU, and programs the PHY to
 * operate according to the mode of operation. The first PLL CMU is only
 * required अगर पूर्णांकernal घड़ी is enabled.
 *
 * Logical Layer Out Of HW module units:
 *
 * -----------------
 * | Internal      |    |------|
 * | Ref PLL CMU   |----|      |     -------------    ---------
 * ------------ ----    | MUX  |-----|PHY PLL CMU|----| Serdes|
 *                      |      |     |           |    ---------
 * External Clock ------|      |     -------------
 *                      |------|
 *
 * The Ref PLL CMU CSR (Configuration System Registers) is accessed
 * indirectly from the SDS offset at 0x2000. It is only required क्रम
 * पूर्णांकernal reference घड़ी.
 * The PHY PLL CMU CSR is accessed indirectly from the SDS offset at 0x0000.
 * The Serdes CSR is accessed indirectly from the SDS offset at 0x0400.
 *
 * The Ref PLL CMU can be located within the same PHY IP or outside the PHY IP
 * due to shared Ref PLL CMU. For PHY with Ref PLL CMU shared with another IP,
 * it is located outside the PHY IP. This is the हाल क्रम the PHY located
 * at 0x1f23a000 (SATA Port 4/5). For such PHY, another resource is required
 * to located the SDS/Ref PLL CMU module and its घड़ी क्रम that IP enabled.
 *
 * Currently, this driver only supports Gen3 SATA mode with बाह्यal घड़ी.
 */
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/clk.h>

/* Max 2 lanes per a PHY unit */
#घोषणा MAX_LANE			2

/* Register offset inside the PHY */
#घोषणा SERDES_PLL_INसूचीECT_OFFSET	0x0000
#घोषणा SERDES_PLL_REF_INसूचीECT_OFFSET	0x2000
#घोषणा SERDES_INसूचीECT_OFFSET		0x0400
#घोषणा SERDES_LANE_STRIDE		0x0200

/* Some शेष Serdes parameters */
#घोषणा DEFAULT_SATA_TXBOOST_GAIN	अणु 0x1e, 0x1e, 0x1e पूर्ण
#घोषणा DEFAULT_SATA_TXEYEसूचीECTION	अणु 0x0, 0x0, 0x0 पूर्ण
#घोषणा DEFAULT_SATA_TXEYETUNING	अणु 0xa, 0xa, 0xa पूर्ण
#घोषणा DEFAULT_SATA_SPD_SEL		अणु 0x1, 0x3, 0x7 पूर्ण
#घोषणा DEFAULT_SATA_TXAMP		अणु 0x8, 0x8, 0x8 पूर्ण
#घोषणा DEFAULT_SATA_TXCN1		अणु 0x2, 0x2, 0x2 पूर्ण
#घोषणा DEFAULT_SATA_TXCN2		अणु 0x0, 0x0, 0x0 पूर्ण
#घोषणा DEFAULT_SATA_TXCP1		अणु 0xa, 0xa, 0xa पूर्ण

#घोषणा SATA_SPD_SEL_GEN3		0x7
#घोषणा SATA_SPD_SEL_GEN2		0x3
#घोषणा SATA_SPD_SEL_GEN1		0x1

#घोषणा SSC_DISABLE			0
#घोषणा SSC_ENABLE			1

#घोषणा FBDIV_VAL_50M			0x77
#घोषणा REFDIV_VAL_50M			0x1
#घोषणा FBDIV_VAL_100M			0x3B
#घोषणा REFDIV_VAL_100M			0x0

/* SATA Clock/Reset CSR */
#घोषणा SATACLKENREG			0x00000000
#घोषणा  SATA0_CORE_CLKEN		0x00000002
#घोषणा  SATA1_CORE_CLKEN		0x00000004
#घोषणा SATASRESETREG			0x00000004
#घोषणा  SATA_MEM_RESET_MASK		0x00000020
#घोषणा  SATA_MEM_RESET_RD(src)		(((src) & 0x00000020) >> 5)
#घोषणा  SATA_SDS_RESET_MASK		0x00000004
#घोषणा  SATA_CSR_RESET_MASK		0x00000001
#घोषणा  SATA_CORE_RESET_MASK		0x00000002
#घोषणा  SATA_PMCLK_RESET_MASK		0x00000010
#घोषणा  SATA_PCLK_RESET_MASK		0x00000008

/* SDS CSR used क्रम PHY Indirect access */
#घोषणा SATA_ENET_SDS_PCS_CTL0		0x00000000
#घोषणा  REGSPEC_CFG_I_TX_WORDMODE0_SET(dst, src) \
		(((dst) & ~0x00070000) | (((u32) (src) << 16) & 0x00070000))
#घोषणा  REGSPEC_CFG_I_RX_WORDMODE0_SET(dst, src) \
		(((dst) & ~0x00e00000) | (((u32) (src) << 21) & 0x00e00000))
#घोषणा SATA_ENET_SDS_CTL0		0x0000000c
#घोषणा  REGSPEC_CFG_I_CUSTOMER_PIN_MODE0_SET(dst, src) \
		(((dst) & ~0x00007fff) | (((u32) (src)) & 0x00007fff))
#घोषणा SATA_ENET_SDS_CTL1		0x00000010
#घोषणा  CFG_I_SPD_SEL_CDR_OVR1_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src)) & 0x0000000f))
#घोषणा SATA_ENET_SDS_RST_CTL		0x00000024
#घोषणा SATA_ENET_SDS_IND_CMD_REG	0x0000003c
#घोषणा  CFG_IND_WR_CMD_MASK		0x00000001
#घोषणा  CFG_IND_RD_CMD_MASK		0x00000002
#घोषणा  CFG_IND_CMD_DONE_MASK		0x00000004
#घोषणा  CFG_IND_ADDR_SET(dst, src) \
		(((dst) & ~0x003ffff0) | (((u32) (src) << 4) & 0x003ffff0))
#घोषणा SATA_ENET_SDS_IND_RDATA_REG	0x00000040
#घोषणा SATA_ENET_SDS_IND_WDATA_REG	0x00000044
#घोषणा SATA_ENET_CLK_MACRO_REG		0x0000004c
#घोषणा  I_RESET_B_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src)) & 0x00000001))
#घोषणा  I_PLL_FBDIV_SET(dst, src) \
		(((dst) & ~0x001ff000) | (((u32) (src) << 12) & 0x001ff000))
#घोषणा  I_CUSTOMEROV_SET(dst, src) \
		(((dst) & ~0x00000f80) | (((u32) (src) << 7) & 0x00000f80))
#घोषणा  O_PLL_LOCK_RD(src)		(((src) & 0x40000000) >> 30)
#घोषणा  O_PLL_READY_RD(src)		(((src) & 0x80000000) >> 31)

/* PLL Clock Macro Unit (CMU) CSR accessing from SDS indirectly */
#घोषणा CMU_REG0			0x00000
#घोषणा  CMU_REG0_PLL_REF_SEL_MASK	0x00002000
#घोषणा  CMU_REG0_PLL_REF_SEL_SET(dst, src)	\
		(((dst) & ~0x00002000) | (((u32) (src) << 13) & 0x00002000))
#घोषणा  CMU_REG0_PDOWN_MASK		0x00004000
#घोषणा  CMU_REG0_CAL_COUNT_RESOL_SET(dst, src) \
		(((dst) & ~0x000000e0) | (((u32) (src) << 5) & 0x000000e0))
#घोषणा CMU_REG1			0x00002
#घोषणा  CMU_REG1_PLL_CP_SET(dst, src) \
		(((dst) & ~0x00003c00) | (((u32) (src) << 10) & 0x00003c00))
#घोषणा  CMU_REG1_PLL_MANUALCAL_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#घोषणा  CMU_REG1_PLL_CP_SEL_SET(dst, src) \
		(((dst) & ~0x000003e0) | (((u32) (src) << 5) & 0x000003e0))
#घोषणा  CMU_REG1_REFCLK_CMOS_SEL_MASK	0x00000001
#घोषणा  CMU_REG1_REFCLK_CMOS_SEL_SET(dst, src)	\
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#घोषणा CMU_REG2			0x00004
#घोषणा  CMU_REG2_PLL_REFDIV_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#घोषणा  CMU_REG2_PLL_LFRES_SET(dst, src) \
		(((dst) & ~0x0000001e) | (((u32) (src) << 1) & 0x0000001e))
#घोषणा  CMU_REG2_PLL_FBDIV_SET(dst, src) \
		(((dst) & ~0x00003fe0) | (((u32) (src) << 5) & 0x00003fe0))
#घोषणा CMU_REG3			0x00006
#घोषणा  CMU_REG3_VCOVARSEL_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src) << 0) & 0x0000000f))
#घोषणा  CMU_REG3_VCO_MOMSEL_INIT_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#घोषणा  CMU_REG3_VCO_MANMOMSEL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#घोषणा CMU_REG4			0x00008
#घोषणा CMU_REG5			0x0000a
#घोषणा  CMU_REG5_PLL_LFSMCAP_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#घोषणा  CMU_REG5_PLL_LOCK_RESOLUTION_SET(dst, src) \
		(((dst) & ~0x0000000e) | (((u32) (src) << 1) & 0x0000000e))
#घोषणा  CMU_REG5_PLL_LFCAP_SET(dst, src) \
		(((dst) & ~0x00003000) | (((u32) (src) << 12) & 0x00003000))
#घोषणा  CMU_REG5_PLL_RESETB_MASK	0x00000001
#घोषणा CMU_REG6			0x0000c
#घोषणा  CMU_REG6_PLL_VREGTRIM_SET(dst, src) \
		(((dst) & ~0x00000600) | (((u32) (src) << 9) & 0x00000600))
#घोषणा  CMU_REG6_MAN_PVT_CAL_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#घोषणा CMU_REG7			0x0000e
#घोषणा  CMU_REG7_PLL_CALIB_DONE_RD(src) ((0x00004000 & (u32) (src)) >> 14)
#घोषणा  CMU_REG7_VCO_CAL_FAIL_RD(src)	((0x00000c00 & (u32) (src)) >> 10)
#घोषणा CMU_REG8			0x00010
#घोषणा CMU_REG9			0x00012
#घोषणा  CMU_REG9_WORD_LEN_8BIT		0x000
#घोषणा  CMU_REG9_WORD_LEN_10BIT	0x001
#घोषणा  CMU_REG9_WORD_LEN_16BIT	0x002
#घोषणा  CMU_REG9_WORD_LEN_20BIT	0x003
#घोषणा  CMU_REG9_WORD_LEN_32BIT	0x004
#घोषणा  CMU_REG9_WORD_LEN_40BIT	0x005
#घोषणा  CMU_REG9_WORD_LEN_64BIT	0x006
#घोषणा  CMU_REG9_WORD_LEN_66BIT	0x007
#घोषणा  CMU_REG9_TX_WORD_MODE_CH1_SET(dst, src) \
		(((dst) & ~0x00000380) | (((u32) (src) << 7) & 0x00000380))
#घोषणा  CMU_REG9_TX_WORD_MODE_CH0_SET(dst, src) \
		(((dst) & ~0x00000070) | (((u32) (src) << 4) & 0x00000070))
#घोषणा  CMU_REG9_PLL_POST_DIVBY2_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#घोषणा  CMU_REG9_VBG_BYPASSB_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#घोषणा  CMU_REG9_IGEN_BYPASS_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#घोषणा CMU_REG10			0x00014
#घोषणा  CMU_REG10_VREG_REFSEL_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#घोषणा CMU_REG11			0x00016
#घोषणा CMU_REG12			0x00018
#घोषणा  CMU_REG12_STATE_DELAY9_SET(dst, src) \
		(((dst) & ~0x000000f0) | (((u32) (src) << 4) & 0x000000f0))
#घोषणा CMU_REG13			0x0001a
#घोषणा CMU_REG14			0x0001c
#घोषणा CMU_REG15			0x0001e
#घोषणा CMU_REG16			0x00020
#घोषणा  CMU_REG16_PVT_DN_MAN_ENA_MASK	0x00000001
#घोषणा  CMU_REG16_PVT_UP_MAN_ENA_MASK	0x00000002
#घोषणा  CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(dst, src) \
		(((dst) & ~0x0000001c) | (((u32) (src) << 2) & 0x0000001c))
#घोषणा  CMU_REG16_CALIBRATION_DONE_OVERRIDE_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#घोषणा  CMU_REG16_BYPASS_PLL_LOCK_SET(dst, src) \
		(((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#घोषणा CMU_REG17			0x00022
#घोषणा  CMU_REG17_PVT_CODE_R2A_SET(dst, src) \
		(((dst) & ~0x00007f00) | (((u32) (src) << 8) & 0x00007f00))
#घोषणा  CMU_REG17_RESERVED_7_SET(dst, src) \
		(((dst) & ~0x000000e0) | (((u32) (src) << 5) & 0x000000e0))
#घोषणा  CMU_REG17_PVT_TERM_MAN_ENA_MASK	0x00008000
#घोषणा CMU_REG18			0x00024
#घोषणा CMU_REG19			0x00026
#घोषणा CMU_REG20			0x00028
#घोषणा CMU_REG21			0x0002a
#घोषणा CMU_REG22			0x0002c
#घोषणा CMU_REG23			0x0002e
#घोषणा CMU_REG24			0x00030
#घोषणा CMU_REG25			0x00032
#घोषणा CMU_REG26			0x00034
#घोषणा  CMU_REG26_FORCE_PLL_LOCK_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#घोषणा CMU_REG27			0x00036
#घोषणा CMU_REG28			0x00038
#घोषणा CMU_REG29			0x0003a
#घोषणा CMU_REG30			0x0003c
#घोषणा  CMU_REG30_LOCK_COUNT_SET(dst, src) \
		(((dst) & ~0x00000006) | (((u32) (src) << 1) & 0x00000006))
#घोषणा  CMU_REG30_PCIE_MODE_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#घोषणा CMU_REG31			0x0003e
#घोषणा CMU_REG32			0x00040
#घोषणा  CMU_REG32_FORCE_VCOCAL_START_MASK	0x00004000
#घोषणा  CMU_REG32_PVT_CAL_WAIT_SEL_SET(dst, src) \
		(((dst) & ~0x00000006) | (((u32) (src) << 1) & 0x00000006))
#घोषणा  CMU_REG32_IREF_ADJ_SET(dst, src) \
		(((dst) & ~0x00000180) | (((u32) (src) << 7) & 0x00000180))
#घोषणा CMU_REG33			0x00042
#घोषणा CMU_REG34			0x00044
#घोषणा  CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(dst, src) \
		(((dst) & ~0x0000000f) | (((u32) (src) << 0) & 0x0000000f))
#घोषणा  CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(dst, src) \
		(((dst) & ~0x00000f00) | (((u32) (src) << 8) & 0x00000f00))
#घोषणा  CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(dst, src) \
		(((dst) & ~0x000000f0) | (((u32) (src) << 4) & 0x000000f0))
#घोषणा  CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(dst, src) \
		(((dst) & ~0x0000f000) | (((u32) (src) << 12) & 0x0000f000))
#घोषणा CMU_REG35			0x00046
#घोषणा  CMU_REG35_PLL_SSC_MOD_SET(dst, src) \
		(((dst) & ~0x0000fe00) | (((u32) (src) << 9) & 0x0000fe00))
#घोषणा CMU_REG36				0x00048
#घोषणा  CMU_REG36_PLL_SSC_EN_SET(dst, src) \
		(((dst) & ~0x00000010) | (((u32) (src) << 4) & 0x00000010))
#घोषणा  CMU_REG36_PLL_SSC_VSTEP_SET(dst, src) \
		(((dst) & ~0x0000ffc0) | (((u32) (src) << 6) & 0x0000ffc0))
#घोषणा  CMU_REG36_PLL_SSC_DSMSEL_SET(dst, src) \
		(((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#घोषणा CMU_REG37			0x0004a
#घोषणा CMU_REG38			0x0004c
#घोषणा CMU_REG39			0x0004e

/* PHY lane CSR accessing from SDS indirectly */
#घोषणा RXTX_REG0			0x000
#घोषणा  RXTX_REG0_CTLE_EQ_HR_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#घोषणा  RXTX_REG0_CTLE_EQ_QR_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#घोषणा  RXTX_REG0_CTLE_EQ_FR_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((u32) (src) << 1) & 0x0000003e))
#घोषणा RXTX_REG1			0x002
#घोषणा  RXTX_REG1_RXACVCM_SET(dst, src) \
		(((dst) & ~0x0000f000) | (((u32) (src) << 12) & 0x0000f000))
#घोषणा  RXTX_REG1_CTLE_EQ_SET(dst, src) \
		(((dst) & ~0x00000f80) | (((u32) (src) << 7) & 0x00000f80))
#घोषणा  RXTX_REG1_RXVREG1_SET(dst, src) \
		(((dst) & ~0x00000060) | (((u32) (src) << 5) & 0x00000060))
#घोषणा  RXTX_REG1_RXIREF_ADJ_SET(dst, src) \
		(((dst) & ~0x00000006) | (((u32) (src) << 1) &  0x00000006))
#घोषणा RXTX_REG2			0x004
#घोषणा  RXTX_REG2_VTT_ENA_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32) (src) << 8) & 0x00000100))
#घोषणा  RXTX_REG2_TX_FIFO_ENA_SET(dst, src) \
		(((dst) & ~0x00000020) | (((u32) (src) << 5) & 0x00000020))
#घोषणा  RXTX_REG2_VTT_SEL_SET(dst, src) \
		(((dst) & ~0x000000c0) | (((u32) (src) << 6) & 0x000000c0))
#घोषणा RXTX_REG4			0x008
#घोषणा  RXTX_REG4_TX_LOOPBACK_BUF_EN_MASK	0x00000040
#घोषणा  RXTX_REG4_TX_DATA_RATE_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#घोषणा  RXTX_REG4_TX_WORD_MODE_SET(dst, src) \
		(((dst) & ~0x00003800) | (((u32) (src) << 11) & 0x00003800))
#घोषणा RXTX_REG5			0x00a
#घोषणा  RXTX_REG5_TX_CN1_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#घोषणा  RXTX_REG5_TX_CP1_SET(dst, src) \
		(((dst) & ~0x000007e0) | (((u32) (src) << 5) & 0x000007e0))
#घोषणा  RXTX_REG5_TX_CN2_SET(dst, src) \
		(((dst) & ~0x0000001f) | (((u32) (src) << 0) & 0x0000001f))
#घोषणा RXTX_REG6			0x00c
#घोषणा  RXTX_REG6_TXAMP_CNTL_SET(dst, src) \
		(((dst) & ~0x00000780) | (((u32) (src) << 7) & 0x00000780))
#घोषणा  RXTX_REG6_TXAMP_ENA_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#घोषणा  RXTX_REG6_RX_BIST_ERRCNT_RD_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#घोषणा  RXTX_REG6_TX_IDLE_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#घोषणा  RXTX_REG6_RX_BIST_RESYNC_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#घोषणा RXTX_REG7			0x00e
#घोषणा  RXTX_REG7_RESETB_RXD_MASK	0x00000100
#घोषणा  RXTX_REG7_RESETB_RXA_MASK	0x00000080
#घोषणा  RXTX_REG7_BIST_ENA_RX_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#घोषणा  RXTX_REG7_RX_WORD_MODE_SET(dst, src) \
		(((dst) & ~0x00003800) | (((u32) (src) << 11) & 0x00003800))
#घोषणा RXTX_REG8			0x010
#घोषणा  RXTX_REG8_CDR_LOOP_ENA_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 14) & 0x00004000))
#घोषणा  RXTX_REG8_CDR_BYPASS_RXLOS_SET(dst, src) \
		(((dst) & ~0x00000800) | (((u32) (src) << 11) & 0x00000800))
#घोषणा  RXTX_REG8_SSC_ENABLE_SET(dst, src) \
		(((dst) & ~0x00000200) | (((u32) (src) << 9) & 0x00000200))
#घोषणा  RXTX_REG8_SD_VREF_SET(dst, src) \
		(((dst) & ~0x000000f0) | (((u32) (src) << 4) & 0x000000f0))
#घोषणा  RXTX_REG8_SD_DISABLE_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32) (src) << 8) & 0x00000100))
#घोषणा RXTX_REG7			0x00e
#घोषणा  RXTX_REG7_RESETB_RXD_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32) (src) << 8) & 0x00000100))
#घोषणा  RXTX_REG7_RESETB_RXA_SET(dst, src) \
		(((dst) & ~0x00000080) | (((u32) (src) << 7) & 0x00000080))
#घोषणा  RXTX_REG7_LOOP_BACK_ENA_CTLE_MASK	0x00004000
#घोषणा  RXTX_REG7_LOOP_BACK_ENA_CTLE_SET(dst, src) \
		(((dst) & ~0x00004000) | (((u32) (src) << 14) & 0x00004000))
#घोषणा RXTX_REG11			0x016
#घोषणा  RXTX_REG11_PHASE_ADJUST_LIMIT_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#घोषणा RXTX_REG12			0x018
#घोषणा  RXTX_REG12_LATCH_OFF_ENA_SET(dst, src) \
		(((dst) & ~0x00002000) | (((u32) (src) << 13) & 0x00002000))
#घोषणा  RXTX_REG12_SUMOS_ENABLE_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#घोषणा  RXTX_REG12_RX_DET_TERM_ENABLE_MASK	0x00000002
#घोषणा  RXTX_REG12_RX_DET_TERM_ENABLE_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#घोषणा RXTX_REG13			0x01a
#घोषणा RXTX_REG14			0x01c
#घोषणा  RXTX_REG14_CLTE_LATCAL_MAN_PROG_SET(dst, src) \
		(((dst) & ~0x0000003f) | (((u32) (src) << 0) & 0x0000003f))
#घोषणा  RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32) (src) << 6) & 0x00000040))
#घोषणा RXTX_REG26			0x034
#घोषणा  RXTX_REG26_PERIOD_ERROR_LATCH_SET(dst, src) \
		(((dst) & ~0x00003800) | (((u32) (src) << 11) & 0x00003800))
#घोषणा  RXTX_REG26_BLWC_ENA_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#घोषणा RXTX_REG21			0x02a
#घोषणा  RXTX_REG21_DO_LATCH_CALOUT_RD(src) ((0x0000fc00 & (u32) (src)) >> 10)
#घोषणा  RXTX_REG21_XO_LATCH_CALOUT_RD(src) ((0x000003f0 & (u32) (src)) >> 4)
#घोषणा  RXTX_REG21_LATCH_CAL_FAIL_ODD_RD(src)	((0x0000000f & (u32)(src)))
#घोषणा RXTX_REG22			0x02c
#घोषणा  RXTX_REG22_SO_LATCH_CALOUT_RD(src) ((0x000003f0 & (u32) (src)) >> 4)
#घोषणा  RXTX_REG22_EO_LATCH_CALOUT_RD(src) ((0x0000fc00 & (u32) (src)) >> 10)
#घोषणा  RXTX_REG22_LATCH_CAL_FAIL_EVEN_RD(src)	((0x0000000f & (u32)(src)))
#घोषणा RXTX_REG23			0x02e
#घोषणा  RXTX_REG23_DE_LATCH_CALOUT_RD(src) ((0x0000fc00 & (u32) (src)) >> 10)
#घोषणा  RXTX_REG23_XE_LATCH_CALOUT_RD(src) ((0x000003f0 & (u32) (src)) >> 4)
#घोषणा RXTX_REG24			0x030
#घोषणा  RXTX_REG24_EE_LATCH_CALOUT_RD(src) ((0x0000fc00 & (u32) (src)) >> 10)
#घोषणा  RXTX_REG24_SE_LATCH_CALOUT_RD(src) ((0x000003f0 & (u32) (src)) >> 4)
#घोषणा RXTX_REG27			0x036
#घोषणा RXTX_REG28			0x038
#घोषणा RXTX_REG31			0x03e
#घोषणा RXTX_REG38			0x04c
#घोषणा  RXTX_REG38_CUSTOMER_PINMODE_INV_SET(dst, src) \
		(((dst) & 0x0000fffe) | (((u32) (src) << 1) & 0x0000fffe))
#घोषणा RXTX_REG39			0x04e
#घोषणा RXTX_REG40			0x050
#घोषणा RXTX_REG41			0x052
#घोषणा RXTX_REG42			0x054
#घोषणा RXTX_REG43			0x056
#घोषणा RXTX_REG44			0x058
#घोषणा RXTX_REG45			0x05a
#घोषणा RXTX_REG46			0x05c
#घोषणा RXTX_REG47			0x05e
#घोषणा RXTX_REG48			0x060
#घोषणा RXTX_REG49			0x062
#घोषणा RXTX_REG50			0x064
#घोषणा RXTX_REG51			0x066
#घोषणा RXTX_REG52			0x068
#घोषणा RXTX_REG53			0x06a
#घोषणा RXTX_REG54			0x06c
#घोषणा RXTX_REG55			0x06e
#घोषणा RXTX_REG61			0x07a
#घोषणा  RXTX_REG61_ISCAN_INBERT_SET(dst, src) \
		(((dst) & ~0x00000010) | (((u32) (src) << 4) & 0x00000010))
#घोषणा  RXTX_REG61_LOADFREQ_SHIFT_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#घोषणा  RXTX_REG61_EYE_COUNT_WIDTH_SEL_SET(dst, src) \
		(((dst) & ~0x000000c0) | (((u32) (src) << 6) & 0x000000c0))
#घोषणा  RXTX_REG61_SPD_SEL_CDR_SET(dst, src) \
		(((dst) & ~0x00003c00) | (((u32) (src) << 10) & 0x00003c00))
#घोषणा RXTX_REG62			0x07c
#घोषणा  RXTX_REG62_PERIOD_H1_QLATCH_SET(dst, src) \
		(((dst) & ~0x00003800) | (((u32) (src) << 11) & 0x00003800))
#घोषणा RXTX_REG81			0x0a2
#घोषणा  RXTX_REG89_MU_TH7_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#घोषणा  RXTX_REG89_MU_TH8_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#घोषणा  RXTX_REG89_MU_TH9_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((u32) (src) << 1) & 0x0000003e))
#घोषणा RXTX_REG96			0x0c0
#घोषणा  RXTX_REG96_MU_FREQ1_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#घोषणा  RXTX_REG96_MU_FREQ2_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#घोषणा  RXTX_REG96_MU_FREQ3_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((u32) (src) << 1) & 0x0000003e))
#घोषणा RXTX_REG99			0x0c6
#घोषणा  RXTX_REG99_MU_PHASE1_SET(dst, src) \
		(((dst) & ~0x0000f800) | (((u32) (src) << 11) & 0x0000f800))
#घोषणा  RXTX_REG99_MU_PHASE2_SET(dst, src) \
		(((dst) & ~0x000007c0) | (((u32) (src) << 6) & 0x000007c0))
#घोषणा  RXTX_REG99_MU_PHASE3_SET(dst, src) \
		(((dst) & ~0x0000003e) | (((u32) (src) << 1) & 0x0000003e))
#घोषणा RXTX_REG102			0x0cc
#घोषणा  RXTX_REG102_FREQLOOP_LIMIT_SET(dst, src) \
		(((dst) & ~0x00000060) | (((u32) (src) << 5) & 0x00000060))
#घोषणा RXTX_REG114			0x0e4
#घोषणा RXTX_REG121			0x0f2
#घोषणा  RXTX_REG121_SUMOS_CAL_CODE_RD(src) ((0x0000003e & (u32)(src)) >> 0x1)
#घोषणा RXTX_REG125			0x0fa
#घोषणा  RXTX_REG125_PQ_REG_SET(dst, src) \
		(((dst) & ~0x0000fe00) | (((u32) (src) << 9) & 0x0000fe00))
#घोषणा  RXTX_REG125_SIGN_PQ_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32) (src) << 8) & 0x00000100))
#घोषणा  RXTX_REG125_SIGN_PQ_2C_SET(dst, src) \
		(((dst) & ~0x00000080) | (((u32) (src) << 7) & 0x00000080))
#घोषणा  RXTX_REG125_PHZ_MANUALCODE_SET(dst, src) \
		(((dst) & ~0x0000007c) | (((u32) (src) << 2) & 0x0000007c))
#घोषणा  RXTX_REG125_PHZ_MANUAL_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#घोषणा RXTX_REG127			0x0fe
#घोषणा  RXTX_REG127_FORCE_SUM_CAL_START_MASK	0x00000002
#घोषणा  RXTX_REG127_FORCE_LAT_CAL_START_MASK	0x00000004
#घोषणा  RXTX_REG127_FORCE_SUM_CAL_START_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#घोषणा  RXTX_REG127_FORCE_LAT_CAL_START_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#घोषणा  RXTX_REG127_LATCH_MAN_CAL_ENA_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32) (src) << 3) & 0x00000008))
#घोषणा  RXTX_REG127_DO_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#घोषणा  RXTX_REG127_XO_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#घोषणा RXTX_REG128			0x100
#घोषणा  RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(dst, src) \
		(((dst) & ~0x0000000c) | (((u32) (src) << 2) & 0x0000000c))
#घोषणा  RXTX_REG128_EO_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#घोषणा  RXTX_REG128_SO_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#घोषणा RXTX_REG129			0x102
#घोषणा  RXTX_REG129_DE_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#घोषणा  RXTX_REG129_XE_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#घोषणा RXTX_REG130			0x104
#घोषणा  RXTX_REG130_EE_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x0000fc00) | (((u32) (src) << 10) & 0x0000fc00))
#घोषणा  RXTX_REG130_SE_LATCH_MANCAL_SET(dst, src) \
		(((dst) & ~0x000003f0) | (((u32) (src) << 4) & 0x000003f0))
#घोषणा RXTX_REG145			0x122
#घोषणा  RXTX_REG145_TX_IDLE_SATA_SET(dst, src) \
		(((dst) & ~0x00000001) | (((u32) (src) << 0) & 0x00000001))
#घोषणा  RXTX_REG145_RXES_ENA_SET(dst, src) \
		(((dst) & ~0x00000002) | (((u32) (src) << 1) & 0x00000002))
#घोषणा  RXTX_REG145_RXDFE_CONFIG_SET(dst, src) \
		(((dst) & ~0x0000c000) | (((u32) (src) << 14) & 0x0000c000))
#घोषणा  RXTX_REG145_RXVWES_LATENA_SET(dst, src) \
		(((dst) & ~0x00000004) | (((u32) (src) << 2) & 0x00000004))
#घोषणा RXTX_REG147			0x126
#घोषणा RXTX_REG148			0x128

/* Clock macro type */
क्रमागत cmu_type_t अणु
	REF_CMU = 0,	/* Clock macro is the पूर्णांकernal reference घड़ी */
	PHY_CMU = 1,	/* Clock macro is the PLL क्रम the Serdes */
पूर्ण;

क्रमागत mux_type_t अणु
	MUX_SELECT_ATA = 0,	/* Switch the MUX to ATA */
	MUX_SELECT_SGMMII = 0,	/* Switch the MUX to SGMII */
पूर्ण;

क्रमागत clk_type_t अणु
	CLK_EXT_DIFF = 0,	/* External dअगरferential */
	CLK_INT_DIFF = 1,	/* Internal dअगरferential */
	CLK_INT_SING = 2,	/* Internal single ended */
पूर्ण;

क्रमागत xgene_phy_mode अणु
	MODE_SATA	= 0,	/* List them क्रम simple reference */
	MODE_SGMII	= 1,
	MODE_PCIE	= 2,
	MODE_USB	= 3,
	MODE_XFI	= 4,
	MODE_MAX
पूर्ण;

काष्ठा xgene_sata_override_param अणु
	u32 speed[MAX_LANE]; /* Index क्रम override parameter per lane */
	u32 txspeed[3];			/* Tx speed */
	u32 txboostgain[MAX_LANE*3];	/* Tx freq boost and gain control */
	u32 txeyetuning[MAX_LANE*3];	/* Tx eye tuning */
	u32 txeyedirection[MAX_LANE*3]; /* Tx eye tuning direction */
	u32 txamplitude[MAX_LANE*3];	/* Tx amplitude control */
	u32 txprecursor_cn1[MAX_LANE*3]; /* Tx emphasis taps 1st pre-cursor */
	u32 txprecursor_cn2[MAX_LANE*3]; /* Tx emphasis taps 2nd pre-cursor */
	u32 txpostcursor_cp1[MAX_LANE*3]; /* Tx emphasis taps post-cursor */
पूर्ण;

काष्ठा xgene_phy_ctx अणु
	काष्ठा device *dev;
	काष्ठा phy *phy;
	क्रमागत xgene_phy_mode mode;		/* Mode of operation */
	क्रमागत clk_type_t clk_type;	/* Input घड़ी selection */
	व्योम __iomem *sds_base;		/* PHY CSR base addr */
	काष्ठा clk *clk;		/* Optional घड़ी */

	/* Override Serdes parameters */
	काष्ठा xgene_sata_override_param sata_param;
पूर्ण;

/*
 * For chip earlier than A3 version, enable this flag.
 * To enable, pass boot argument phy_xgene.preA3Chip=1
 */
अटल पूर्णांक preA3Chip;
MODULE_PARM_DESC(preA3Chip, "Enable pre-A3 chip support (1=enable 0=disable)");
module_param_named(preA3Chip, preA3Chip, पूर्णांक, 0444);

अटल व्योम sds_wr(व्योम __iomem *csr_base, u32 indirect_cmd_reg,
		   u32 indirect_data_reg, u32 addr, u32 data)
अणु
	अचिन्हित दीर्घ deadline = jअगरfies + HZ;
	u32 val;
	u32 cmd;

	cmd = CFG_IND_WR_CMD_MASK | CFG_IND_CMD_DONE_MASK;
	cmd = CFG_IND_ADDR_SET(cmd, addr);
	ग_लिखोl(data, csr_base + indirect_data_reg);
	पढ़ोl(csr_base + indirect_data_reg); /* Force a barrier */
	ग_लिखोl(cmd, csr_base + indirect_cmd_reg);
	पढ़ोl(csr_base + indirect_cmd_reg); /* Force a barrier */
	करो अणु
		val = पढ़ोl(csr_base + indirect_cmd_reg);
	पूर्ण जबतक (!(val & CFG_IND_CMD_DONE_MASK) &&
		 समय_beक्रमe(jअगरfies, deadline));
	अगर (!(val & CFG_IND_CMD_DONE_MASK))
		pr_err("SDS WR timeout at 0x%p offset 0x%08X value 0x%08X\n",
		       csr_base + indirect_cmd_reg, addr, data);
पूर्ण

अटल व्योम sds_rd(व्योम __iomem *csr_base, u32 indirect_cmd_reg,
		   u32 indirect_data_reg, u32 addr, u32 *data)
अणु
	अचिन्हित दीर्घ deadline = jअगरfies + HZ;
	u32 val;
	u32 cmd;

	cmd = CFG_IND_RD_CMD_MASK | CFG_IND_CMD_DONE_MASK;
	cmd = CFG_IND_ADDR_SET(cmd, addr);
	ग_लिखोl(cmd, csr_base + indirect_cmd_reg);
	पढ़ोl(csr_base + indirect_cmd_reg); /* Force a barrier */
	करो अणु
		val = पढ़ोl(csr_base + indirect_cmd_reg);
	पूर्ण जबतक (!(val & CFG_IND_CMD_DONE_MASK) &&
		 समय_beक्रमe(jअगरfies, deadline));
	*data = पढ़ोl(csr_base + indirect_data_reg);
	अगर (!(val & CFG_IND_CMD_DONE_MASK))
		pr_err("SDS WR timeout at 0x%p offset 0x%08X value 0x%08X\n",
		       csr_base + indirect_cmd_reg, addr, *data);
पूर्ण

अटल व्योम cmu_wr(काष्ठा xgene_phy_ctx *ctx, क्रमागत cmu_type_t cmu_type,
		   u32 reg, u32 data)
अणु
	व्योम __iomem *sds_base = ctx->sds_base;
	u32 val;

	अगर (cmu_type == REF_CMU)
		reg += SERDES_PLL_REF_INसूचीECT_OFFSET;
	अन्यथा
		reg += SERDES_PLL_INसूचीECT_OFFSET;
	sds_wr(sds_base, SATA_ENET_SDS_IND_CMD_REG,
		SATA_ENET_SDS_IND_WDATA_REG, reg, data);
	sds_rd(sds_base, SATA_ENET_SDS_IND_CMD_REG,
		SATA_ENET_SDS_IND_RDATA_REG, reg, &val);
	pr_debug("CMU WR addr 0x%X value 0x%08X <-> 0x%08X\n", reg, data, val);
पूर्ण

अटल व्योम cmu_rd(काष्ठा xgene_phy_ctx *ctx, क्रमागत cmu_type_t cmu_type,
		   u32 reg, u32 *data)
अणु
	व्योम __iomem *sds_base = ctx->sds_base;

	अगर (cmu_type == REF_CMU)
		reg += SERDES_PLL_REF_INसूचीECT_OFFSET;
	अन्यथा
		reg += SERDES_PLL_INसूचीECT_OFFSET;
	sds_rd(sds_base, SATA_ENET_SDS_IND_CMD_REG,
		SATA_ENET_SDS_IND_RDATA_REG, reg, data);
	pr_debug("CMU RD addr 0x%X value 0x%08X\n", reg, *data);
पूर्ण

अटल व्योम cmu_toggle1to0(काष्ठा xgene_phy_ctx *ctx, क्रमागत cmu_type_t cmu_type,
			   u32 reg, u32 bits)
अणु
	u32 val;

	cmu_rd(ctx, cmu_type, reg, &val);
	val |= bits;
	cmu_wr(ctx, cmu_type, reg, val);
	cmu_rd(ctx, cmu_type, reg, &val);
	val &= ~bits;
	cmu_wr(ctx, cmu_type, reg, val);
पूर्ण

अटल व्योम cmu_clrbits(काष्ठा xgene_phy_ctx *ctx, क्रमागत cmu_type_t cmu_type,
			u32 reg, u32 bits)
अणु
	u32 val;

	cmu_rd(ctx, cmu_type, reg, &val);
	val &= ~bits;
	cmu_wr(ctx, cmu_type, reg, val);
पूर्ण

अटल व्योम cmu_setbits(काष्ठा xgene_phy_ctx *ctx, क्रमागत cmu_type_t cmu_type,
			u32 reg, u32 bits)
अणु
	u32 val;

	cmu_rd(ctx, cmu_type, reg, &val);
	val |= bits;
	cmu_wr(ctx, cmu_type, reg, val);
पूर्ण

अटल व्योम serdes_wr(काष्ठा xgene_phy_ctx *ctx, पूर्णांक lane, u32 reg, u32 data)
अणु
	व्योम __iomem *sds_base = ctx->sds_base;
	u32 val;

	reg += SERDES_INसूचीECT_OFFSET;
	reg += lane * SERDES_LANE_STRIDE;
	sds_wr(sds_base, SATA_ENET_SDS_IND_CMD_REG,
	       SATA_ENET_SDS_IND_WDATA_REG, reg, data);
	sds_rd(sds_base, SATA_ENET_SDS_IND_CMD_REG,
	       SATA_ENET_SDS_IND_RDATA_REG, reg, &val);
	pr_debug("SERDES WR addr 0x%X value 0x%08X <-> 0x%08X\n", reg, data,
		 val);
पूर्ण

अटल व्योम serdes_rd(काष्ठा xgene_phy_ctx *ctx, पूर्णांक lane, u32 reg, u32 *data)
अणु
	व्योम __iomem *sds_base = ctx->sds_base;

	reg += SERDES_INसूचीECT_OFFSET;
	reg += lane * SERDES_LANE_STRIDE;
	sds_rd(sds_base, SATA_ENET_SDS_IND_CMD_REG,
	       SATA_ENET_SDS_IND_RDATA_REG, reg, data);
	pr_debug("SERDES RD addr 0x%X value 0x%08X\n", reg, *data);
पूर्ण

अटल व्योम serdes_clrbits(काष्ठा xgene_phy_ctx *ctx, पूर्णांक lane, u32 reg,
			   u32 bits)
अणु
	u32 val;

	serdes_rd(ctx, lane, reg, &val);
	val &= ~bits;
	serdes_wr(ctx, lane, reg, val);
पूर्ण

अटल व्योम serdes_setbits(काष्ठा xgene_phy_ctx *ctx, पूर्णांक lane, u32 reg,
			   u32 bits)
अणु
	u32 val;

	serdes_rd(ctx, lane, reg, &val);
	val |= bits;
	serdes_wr(ctx, lane, reg, val);
पूर्ण

अटल व्योम xgene_phy_cfg_cmu_clk_type(काष्ठा xgene_phy_ctx *ctx,
				       क्रमागत cmu_type_t cmu_type,
				       क्रमागत clk_type_t clk_type)
अणु
	u32 val;

	/* Set the reset sequence delay क्रम TX पढ़ोy निश्चितion */
	cmu_rd(ctx, cmu_type, CMU_REG12, &val);
	val = CMU_REG12_STATE_DELAY9_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG12, val);
	/* Set the programmable stage delays between various enable stages */
	cmu_wr(ctx, cmu_type, CMU_REG13, 0x0222);
	cmu_wr(ctx, cmu_type, CMU_REG14, 0x2225);

	/* Configure घड़ी type */
	अगर (clk_type == CLK_EXT_DIFF) अणु
		/* Select बाह्यal घड़ी mux */
		cmu_rd(ctx, cmu_type, CMU_REG0, &val);
		val = CMU_REG0_PLL_REF_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG0, val);
		/* Select CMOS as reference घड़ी  */
		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev, "Set external reference clock\n");
	पूर्ण अन्यथा अगर (clk_type == CLK_INT_DIFF) अणु
		/* Select पूर्णांकernal घड़ी mux */
		cmu_rd(ctx, cmu_type, CMU_REG0, &val);
		val = CMU_REG0_PLL_REF_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG0, val);
		/* Select CMOS as reference घड़ी  */
		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev, "Set internal reference clock\n");
	पूर्ण अन्यथा अगर (clk_type == CLK_INT_SING) अणु
		/*
		 * NOTE: This घड़ी type is NOT support क्रम controller
		 *	 whose पूर्णांकernal घड़ी shared in the PCIe controller
		 *
		 * Select पूर्णांकernal घड़ी mux
		 */
		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x1);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		/* Select CML as reference घड़ी */
		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_REFCLK_CMOS_SEL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		dev_dbg(ctx->dev,
			"Set internal single ended reference clock\n");
	पूर्ण
पूर्ण

अटल व्योम xgene_phy_sata_cfg_cmu_core(काष्ठा xgene_phy_ctx *ctx,
					क्रमागत cmu_type_t cmu_type,
					क्रमागत clk_type_t clk_type)
अणु
	u32 val;
	पूर्णांक ref_100MHz;

	अगर (cmu_type == REF_CMU) अणु
		/* Set VCO calibration voltage threshold */
		cmu_rd(ctx, cmu_type, CMU_REG34, &val);
		val = CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(val, 0x7);
		val = CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(val, 0xc);
		val = CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(val, 0x3);
		val = CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(val, 0x8);
		cmu_wr(ctx, cmu_type, CMU_REG34, val);
	पूर्ण

	/* Set the VCO calibration counter */
	cmu_rd(ctx, cmu_type, CMU_REG0, &val);
	अगर (cmu_type == REF_CMU || preA3Chip)
		val = CMU_REG0_CAL_COUNT_RESOL_SET(val, 0x4);
	अन्यथा
		val = CMU_REG0_CAL_COUNT_RESOL_SET(val, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG0, val);

	/* Configure PLL क्रम calibration */
	cmu_rd(ctx, cmu_type, CMU_REG1, &val);
	val = CMU_REG1_PLL_CP_SET(val, 0x1);
	अगर (cmu_type == REF_CMU || preA3Chip)
		val = CMU_REG1_PLL_CP_SEL_SET(val, 0x5);
	अन्यथा
		val = CMU_REG1_PLL_CP_SEL_SET(val, 0x3);
	अगर (cmu_type == REF_CMU)
		val = CMU_REG1_PLL_MANUALCAL_SET(val, 0x0);
	अन्यथा
		val = CMU_REG1_PLL_MANUALCAL_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG1, val);

	अगर (cmu_type != REF_CMU)
		cmu_clrbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);

	/* Configure the PLL क्रम either 100MHz or 50MHz */
	cmu_rd(ctx, cmu_type, CMU_REG2, &val);
	अगर (cmu_type == REF_CMU) अणु
		val = CMU_REG2_PLL_LFRES_SET(val, 0xa);
		ref_100MHz = 1;
	पूर्ण अन्यथा अणु
		val = CMU_REG2_PLL_LFRES_SET(val, 0x3);
		अगर (clk_type == CLK_EXT_DIFF)
			ref_100MHz = 0;
		अन्यथा
			ref_100MHz = 1;
	पूर्ण
	अगर (ref_100MHz) अणु
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_100M);
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_100M);
	पूर्ण अन्यथा अणु
		val = CMU_REG2_PLL_FBDIV_SET(val, FBDIV_VAL_50M);
		val = CMU_REG2_PLL_REFDIV_SET(val, REFDIV_VAL_50M);
	पूर्ण
	cmu_wr(ctx, cmu_type, CMU_REG2, val);

	/* Configure the VCO */
	cmu_rd(ctx, cmu_type, CMU_REG3, &val);
	अगर (cmu_type == REF_CMU) अणु
		val = CMU_REG3_VCOVARSEL_SET(val, 0x3);
		val = CMU_REG3_VCO_MOMSEL_INIT_SET(val, 0x10);
	पूर्ण अन्यथा अणु
		val = CMU_REG3_VCOVARSEL_SET(val, 0xF);
		अगर (preA3Chip)
			val = CMU_REG3_VCO_MOMSEL_INIT_SET(val, 0x15);
		अन्यथा
			val = CMU_REG3_VCO_MOMSEL_INIT_SET(val, 0x1a);
		val = CMU_REG3_VCO_MANMOMSEL_SET(val, 0x15);
	पूर्ण
	cmu_wr(ctx, cmu_type, CMU_REG3, val);

	/* Disable क्रमce PLL lock */
	cmu_rd(ctx, cmu_type, CMU_REG26, &val);
	val = CMU_REG26_FORCE_PLL_LOCK_SET(val, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG26, val);

	/* Setup PLL loop filter */
	cmu_rd(ctx, cmu_type, CMU_REG5, &val);
	val = CMU_REG5_PLL_LFSMCAP_SET(val, 0x3);
	val = CMU_REG5_PLL_LFCAP_SET(val, 0x3);
	अगर (cmu_type == REF_CMU || !preA3Chip)
		val = CMU_REG5_PLL_LOCK_RESOLUTION_SET(val, 0x7);
	अन्यथा
		val = CMU_REG5_PLL_LOCK_RESOLUTION_SET(val, 0x4);
	cmu_wr(ctx, cmu_type, CMU_REG5, val);

	/* Enable or disable manual calibration */
	cmu_rd(ctx, cmu_type, CMU_REG6, &val);
	val = CMU_REG6_PLL_VREGTRIM_SET(val, preA3Chip ? 0x0 : 0x2);
	val = CMU_REG6_MAN_PVT_CAL_SET(val, preA3Chip ? 0x1 : 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG6, val);

	/* Configure lane क्रम 20-bits */
	अगर (cmu_type == PHY_CMU) अणु
		cmu_rd(ctx, cmu_type, CMU_REG9, &val);
		val = CMU_REG9_TX_WORD_MODE_CH1_SET(val,
						    CMU_REG9_WORD_LEN_20BIT);
		val = CMU_REG9_TX_WORD_MODE_CH0_SET(val,
						    CMU_REG9_WORD_LEN_20BIT);
		val = CMU_REG9_PLL_POST_DIVBY2_SET(val, 0x1);
		अगर (!preA3Chip) अणु
			val = CMU_REG9_VBG_BYPASSB_SET(val, 0x0);
			val = CMU_REG9_IGEN_BYPASS_SET(val , 0x0);
		पूर्ण
		cmu_wr(ctx, cmu_type, CMU_REG9, val);

		अगर (!preA3Chip) अणु
			cmu_rd(ctx, cmu_type, CMU_REG10, &val);
			val = CMU_REG10_VREG_REFSEL_SET(val, 0x1);
			cmu_wr(ctx, cmu_type, CMU_REG10, val);
		पूर्ण
	पूर्ण

	cmu_rd(ctx, cmu_type, CMU_REG16, &val);
	val = CMU_REG16_CALIBRATION_DONE_OVERRIDE_SET(val, 0x1);
	val = CMU_REG16_BYPASS_PLL_LOCK_SET(val, 0x1);
	अगर (cmu_type == REF_CMU || preA3Chip)
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x4);
	अन्यथा
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x7);
	cmu_wr(ctx, cmu_type, CMU_REG16, val);

	/* Configure क्रम SATA */
	cmu_rd(ctx, cmu_type, CMU_REG30, &val);
	val = CMU_REG30_PCIE_MODE_SET(val, 0x0);
	val = CMU_REG30_LOCK_COUNT_SET(val, 0x3);
	cmu_wr(ctx, cmu_type, CMU_REG30, val);

	/* Disable state machine bypass */
	cmu_wr(ctx, cmu_type, CMU_REG31, 0xF);

	cmu_rd(ctx, cmu_type, CMU_REG32, &val);
	val = CMU_REG32_PVT_CAL_WAIT_SEL_SET(val, 0x3);
	अगर (cmu_type == REF_CMU || preA3Chip)
		val = CMU_REG32_IREF_ADJ_SET(val, 0x3);
	अन्यथा
		val = CMU_REG32_IREF_ADJ_SET(val, 0x1);
	cmu_wr(ctx, cmu_type, CMU_REG32, val);

	/* Set VCO calibration threshold */
	अगर (cmu_type != REF_CMU && preA3Chip)
		cmu_wr(ctx, cmu_type, CMU_REG34, 0x8d27);
	अन्यथा
		cmu_wr(ctx, cmu_type, CMU_REG34, 0x873c);

	/* Set CTLE Override and override रुकोing from state machine */
	cmu_wr(ctx, cmu_type, CMU_REG37, 0xF00F);
पूर्ण

अटल व्योम xgene_phy_ssc_enable(काष्ठा xgene_phy_ctx *ctx,
				 क्रमागत cmu_type_t cmu_type)
अणु
	u32 val;

	/* Set SSC modulation value */
	cmu_rd(ctx, cmu_type, CMU_REG35, &val);
	val = CMU_REG35_PLL_SSC_MOD_SET(val, 98);
	cmu_wr(ctx, cmu_type, CMU_REG35, val);

	/* Enable SSC, set vertical step and DSM value */
	cmu_rd(ctx, cmu_type, CMU_REG36, &val);
	val = CMU_REG36_PLL_SSC_VSTEP_SET(val, 30);
	val = CMU_REG36_PLL_SSC_EN_SET(val, 1);
	val = CMU_REG36_PLL_SSC_DSMSEL_SET(val, 1);
	cmu_wr(ctx, cmu_type, CMU_REG36, val);

	/* Reset the PLL */
	cmu_clrbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);
	cmu_setbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);

	/* Force VCO calibration to restart */
	cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
		       CMU_REG32_FORCE_VCOCAL_START_MASK);
पूर्ण

अटल व्योम xgene_phy_sata_cfg_lanes(काष्ठा xgene_phy_ctx *ctx)
अणु
	u32 val;
	u32 reg;
	पूर्णांक i;
	पूर्णांक lane;

	क्रम (lane = 0; lane < MAX_LANE; lane++) अणु
		serdes_wr(ctx, lane, RXTX_REG147, 0x6);

		/* Set boost control क्रम quarter, half, and full rate */
		serdes_rd(ctx, lane, RXTX_REG0, &val);
		val = RXTX_REG0_CTLE_EQ_HR_SET(val, 0x10);
		val = RXTX_REG0_CTLE_EQ_QR_SET(val, 0x10);
		val = RXTX_REG0_CTLE_EQ_FR_SET(val, 0x10);
		serdes_wr(ctx, lane, RXTX_REG0, val);

		/* Set boost control value */
		serdes_rd(ctx, lane, RXTX_REG1, &val);
		val = RXTX_REG1_RXACVCM_SET(val, 0x7);
		val = RXTX_REG1_CTLE_EQ_SET(val,
			ctx->sata_param.txboostgain[lane * 3 +
			ctx->sata_param.speed[lane]]);
		serdes_wr(ctx, lane, RXTX_REG1, val);

		/* Latch VTT value based on the termination to ground and
		   enable TX FIFO */
		serdes_rd(ctx, lane, RXTX_REG2, &val);
		val = RXTX_REG2_VTT_ENA_SET(val, 0x1);
		val = RXTX_REG2_VTT_SEL_SET(val, 0x1);
		val = RXTX_REG2_TX_FIFO_ENA_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG2, val);

		/* Configure Tx क्रम 20-bits */
		serdes_rd(ctx, lane, RXTX_REG4, &val);
		val = RXTX_REG4_TX_WORD_MODE_SET(val, CMU_REG9_WORD_LEN_20BIT);
		serdes_wr(ctx, lane, RXTX_REG4, val);

		अगर (!preA3Chip) अणु
			serdes_rd(ctx, lane, RXTX_REG1, &val);
			val = RXTX_REG1_RXVREG1_SET(val, 0x2);
			val = RXTX_REG1_RXIREF_ADJ_SET(val, 0x2);
			serdes_wr(ctx, lane, RXTX_REG1, val);
		पूर्ण

		/* Set pre-emphasis first 1 and 2, and post-emphasis values */
		serdes_rd(ctx, lane, RXTX_REG5, &val);
		val = RXTX_REG5_TX_CN1_SET(val,
			ctx->sata_param.txprecursor_cn1[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG5_TX_CP1_SET(val,
			ctx->sata_param.txpostcursor_cp1[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG5_TX_CN2_SET(val,
			ctx->sata_param.txprecursor_cn2[lane * 3 +
			ctx->sata_param.speed[lane]]);
		serdes_wr(ctx, lane, RXTX_REG5, val);

		/* Set TX amplitude value */
		serdes_rd(ctx, lane, RXTX_REG6, &val);
		val = RXTX_REG6_TXAMP_CNTL_SET(val,
			ctx->sata_param.txamplitude[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG6_TXAMP_ENA_SET(val, 0x1);
		val = RXTX_REG6_TX_IDLE_SET(val, 0x0);
		val = RXTX_REG6_RX_BIST_RESYNC_SET(val, 0x0);
		val = RXTX_REG6_RX_BIST_ERRCNT_RD_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG6, val);

		/* Configure Rx क्रम 20-bits */
		serdes_rd(ctx, lane, RXTX_REG7, &val);
		val = RXTX_REG7_BIST_ENA_RX_SET(val, 0x0);
		val = RXTX_REG7_RX_WORD_MODE_SET(val, CMU_REG9_WORD_LEN_20BIT);
		serdes_wr(ctx, lane, RXTX_REG7, val);

		/* Set CDR and LOS values and enable Rx SSC */
		serdes_rd(ctx, lane, RXTX_REG8, &val);
		val = RXTX_REG8_CDR_LOOP_ENA_SET(val, 0x1);
		val = RXTX_REG8_CDR_BYPASS_RXLOS_SET(val, 0x0);
		val = RXTX_REG8_SSC_ENABLE_SET(val, 0x1);
		val = RXTX_REG8_SD_DISABLE_SET(val, 0x0);
		val = RXTX_REG8_SD_VREF_SET(val, 0x4);
		serdes_wr(ctx, lane, RXTX_REG8, val);

		/* Set phase adjust upper/lower limits */
		serdes_rd(ctx, lane, RXTX_REG11, &val);
		val = RXTX_REG11_PHASE_ADJUST_LIMIT_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG11, val);

		/* Enable Latch Off; disable SUMOS and Tx termination */
		serdes_rd(ctx, lane, RXTX_REG12, &val);
		val = RXTX_REG12_LATCH_OFF_ENA_SET(val, 0x1);
		val = RXTX_REG12_SUMOS_ENABLE_SET(val, 0x0);
		val = RXTX_REG12_RX_DET_TERM_ENABLE_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG12, val);

		/* Set period error latch to 512T and enable BWL */
		serdes_rd(ctx, lane, RXTX_REG26, &val);
		val = RXTX_REG26_PERIOD_ERROR_LATCH_SET(val, 0x0);
		val = RXTX_REG26_BLWC_ENA_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG26, val);

		serdes_wr(ctx, lane, RXTX_REG28, 0x0);

		/* Set DFE loop preset value */
		serdes_wr(ctx, lane, RXTX_REG31, 0x0);

		/* Set Eye Monitor counter width to 12-bit */
		serdes_rd(ctx, lane, RXTX_REG61, &val);
		val = RXTX_REG61_ISCAN_INBERT_SET(val, 0x1);
		val = RXTX_REG61_LOADFREQ_SHIFT_SET(val, 0x0);
		val = RXTX_REG61_EYE_COUNT_WIDTH_SEL_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG61, val);

		serdes_rd(ctx, lane, RXTX_REG62, &val);
		val = RXTX_REG62_PERIOD_H1_QLATCH_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG62, val);

		/* Set BW select tap X क्रम DFE loop */
		क्रम (i = 0; i < 9; i++) अणु
			reg = RXTX_REG81 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG89_MU_TH7_SET(val, 0xe);
			val = RXTX_REG89_MU_TH8_SET(val, 0xe);
			val = RXTX_REG89_MU_TH9_SET(val, 0xe);
			serdes_wr(ctx, lane, reg, val);
		पूर्ण

		/* Set BW select tap X क्रम frequency adjust loop */
		क्रम (i = 0; i < 3; i++) अणु
			reg = RXTX_REG96 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG96_MU_FREQ1_SET(val, 0x10);
			val = RXTX_REG96_MU_FREQ2_SET(val, 0x10);
			val = RXTX_REG96_MU_FREQ3_SET(val, 0x10);
			serdes_wr(ctx, lane, reg, val);
		पूर्ण

		/* Set BW select tap X क्रम phase adjust loop */
		क्रम (i = 0; i < 3; i++) अणु
			reg = RXTX_REG99 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG99_MU_PHASE1_SET(val, 0x7);
			val = RXTX_REG99_MU_PHASE2_SET(val, 0x7);
			val = RXTX_REG99_MU_PHASE3_SET(val, 0x7);
			serdes_wr(ctx, lane, reg, val);
		पूर्ण

		serdes_rd(ctx, lane, RXTX_REG102, &val);
		val = RXTX_REG102_FREQLOOP_LIMIT_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG102, val);

		serdes_wr(ctx, lane, RXTX_REG114, 0xffe0);

		serdes_rd(ctx, lane, RXTX_REG125, &val);
		val = RXTX_REG125_SIGN_PQ_SET(val,
			ctx->sata_param.txeyedirection[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG125_PQ_REG_SET(val,
			ctx->sata_param.txeyetuning[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG125_PHZ_MANUAL_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG125, val);

		serdes_rd(ctx, lane, RXTX_REG127, &val);
		val = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG127, val);

		serdes_rd(ctx, lane, RXTX_REG128, &val);
		val = RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(val, 0x3);
		serdes_wr(ctx, lane, RXTX_REG128, val);

		serdes_rd(ctx, lane, RXTX_REG145, &val);
		val = RXTX_REG145_RXDFE_CONFIG_SET(val, 0x3);
		val = RXTX_REG145_TX_IDLE_SATA_SET(val, 0x0);
		अगर (preA3Chip) अणु
			val = RXTX_REG145_RXES_ENA_SET(val, 0x1);
			val = RXTX_REG145_RXVWES_LATENA_SET(val, 0x1);
		पूर्ण अन्यथा अणु
			val = RXTX_REG145_RXES_ENA_SET(val, 0x0);
			val = RXTX_REG145_RXVWES_LATENA_SET(val, 0x0);
		पूर्ण
		serdes_wr(ctx, lane, RXTX_REG145, val);

		/*
		 * Set Rx LOS filter घड़ी rate, sample rate, and threshold
		 * winकरोws
		 */
		क्रम (i = 0; i < 4; i++) अणु
			reg = RXTX_REG148 + i * 2;
			serdes_wr(ctx, lane, reg, 0xFFFF);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_phy_cal_rdy_chk(काष्ठा xgene_phy_ctx *ctx,
				 क्रमागत cmu_type_t cmu_type,
				 क्रमागत clk_type_t clk_type)
अणु
	व्योम __iomem *csr_serdes = ctx->sds_base;
	पूर्णांक loop;
	u32 val;

	/* Release PHY मुख्य reset */
	ग_लिखोl(0xdf, csr_serdes + SATA_ENET_SDS_RST_CTL);
	पढ़ोl(csr_serdes + SATA_ENET_SDS_RST_CTL); /* Force a barrier */

	अगर (cmu_type != REF_CMU) अणु
		cmu_setbits(ctx, cmu_type, CMU_REG5, CMU_REG5_PLL_RESETB_MASK);
		/*
		 * As per PHY design spec, the PLL reset requires a minimum
		 * of 800us.
		 */
		usleep_range(800, 1000);

		cmu_rd(ctx, cmu_type, CMU_REG1, &val);
		val = CMU_REG1_PLL_MANUALCAL_SET(val, 0x0);
		cmu_wr(ctx, cmu_type, CMU_REG1, val);
		/*
		 * As per PHY design spec, the PLL स्वतः calibration requires
		 * a minimum of 800us.
		 */
		usleep_range(800, 1000);

		cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
			       CMU_REG32_FORCE_VCOCAL_START_MASK);
		/*
		 * As per PHY design spec, the PLL requires a minimum of
		 * 800us to settle.
		 */
		usleep_range(800, 1000);
	पूर्ण

	अगर (!preA3Chip)
		जाओ skip_manual_cal;

	/*
	 * Configure the termination resister calibration
	 * The serial receive pins, RXP/RXN, have TERMination resistor
	 * that is required to be calibrated.
	 */
	cmu_rd(ctx, cmu_type, CMU_REG17, &val);
	val = CMU_REG17_PVT_CODE_R2A_SET(val, 0x12);
	val = CMU_REG17_RESERVED_7_SET(val, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG17, val);
	cmu_toggle1to0(ctx, cmu_type, CMU_REG17,
		       CMU_REG17_PVT_TERM_MAN_ENA_MASK);
	/*
	 * The serial transmit pins, TXP/TXN, have Pull-UP and Pull-DOWN
	 * resistors that are required to the calibrated.
	 * Configure the pull DOWN calibration
	 */
	cmu_rd(ctx, cmu_type, CMU_REG17, &val);
	val = CMU_REG17_PVT_CODE_R2A_SET(val, 0x29);
	val = CMU_REG17_RESERVED_7_SET(val, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG17, val);
	cmu_toggle1to0(ctx, cmu_type, CMU_REG16,
		       CMU_REG16_PVT_DN_MAN_ENA_MASK);
	/* Configure the pull UP calibration */
	cmu_rd(ctx, cmu_type, CMU_REG17, &val);
	val = CMU_REG17_PVT_CODE_R2A_SET(val, 0x28);
	val = CMU_REG17_RESERVED_7_SET(val, 0x0);
	cmu_wr(ctx, cmu_type, CMU_REG17, val);
	cmu_toggle1to0(ctx, cmu_type, CMU_REG16,
		       CMU_REG16_PVT_UP_MAN_ENA_MASK);

skip_manual_cal:
	/* Poll the PLL calibration completion status क्रम at least 1 ms */
	loop = 100;
	करो अणु
		cmu_rd(ctx, cmu_type, CMU_REG7, &val);
		अगर (CMU_REG7_PLL_CALIB_DONE_RD(val))
			अवरोध;
		/*
		 * As per PHY design spec, PLL calibration status requires
		 * a minimum of 10us to be updated.
		 */
		usleep_range(10, 100);
	पूर्ण जबतक (--loop > 0);

	cmu_rd(ctx, cmu_type, CMU_REG7, &val);
	dev_dbg(ctx->dev, "PLL calibration %s\n",
		CMU_REG7_PLL_CALIB_DONE_RD(val) ? "done" : "failed");
	अगर (CMU_REG7_VCO_CAL_FAIL_RD(val)) अणु
		dev_err(ctx->dev,
			"PLL calibration failed due to VCO failure\n");
		वापस -1;
	पूर्ण
	dev_dbg(ctx->dev, "PLL calibration successful\n");

	cmu_rd(ctx, cmu_type, CMU_REG15, &val);
	dev_dbg(ctx->dev, "PHY Tx is %sready\n", val & 0x300 ? "" : "not ");
	वापस 0;
पूर्ण

अटल व्योम xgene_phy_pdwn_क्रमce_vco(काष्ठा xgene_phy_ctx *ctx,
				     क्रमागत cmu_type_t cmu_type,
				     क्रमागत clk_type_t clk_type)
अणु
	u32 val;

	dev_dbg(ctx->dev, "Reset VCO and re-start again\n");
	अगर (cmu_type == PHY_CMU) अणु
		cmu_rd(ctx, cmu_type, CMU_REG16, &val);
		val = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(val, 0x7);
		cmu_wr(ctx, cmu_type, CMU_REG16, val);
	पूर्ण

	cmu_toggle1to0(ctx, cmu_type, CMU_REG0, CMU_REG0_PDOWN_MASK);
	cmu_toggle1to0(ctx, cmu_type, CMU_REG32,
		       CMU_REG32_FORCE_VCOCAL_START_MASK);
पूर्ण

अटल पूर्णांक xgene_phy_hw_init_sata(काष्ठा xgene_phy_ctx *ctx,
				  क्रमागत clk_type_t clk_type, पूर्णांक ssc_enable)
अणु
	व्योम __iomem *sds_base = ctx->sds_base;
	u32 val;
	पूर्णांक i;

	/* Configure the PHY क्रम operation */
	dev_dbg(ctx->dev, "Reset PHY\n");
	/* Place PHY पूर्णांकo reset */
	ग_लिखोl(0x0, sds_base + SATA_ENET_SDS_RST_CTL);
	val = पढ़ोl(sds_base + SATA_ENET_SDS_RST_CTL);	/* Force a barrier */
	/* Release PHY lane from reset (active high) */
	ग_लिखोl(0x20, sds_base + SATA_ENET_SDS_RST_CTL);
	पढ़ोl(sds_base + SATA_ENET_SDS_RST_CTL);	/* Force a barrier */
	/* Release all PHY module out of reset except PHY मुख्य reset */
	ग_लिखोl(0xde, sds_base + SATA_ENET_SDS_RST_CTL);
	पढ़ोl(sds_base + SATA_ENET_SDS_RST_CTL);	/* Force a barrier */

	/* Set the operation speed */
	val = पढ़ोl(sds_base + SATA_ENET_SDS_CTL1);
	val = CFG_I_SPD_SEL_CDR_OVR1_SET(val,
		ctx->sata_param.txspeed[ctx->sata_param.speed[0]]);
	ग_लिखोl(val, sds_base + SATA_ENET_SDS_CTL1);

	dev_dbg(ctx->dev, "Set the customer pin mode to SATA\n");
	val = पढ़ोl(sds_base + SATA_ENET_SDS_CTL0);
	val = REGSPEC_CFG_I_CUSTOMER_PIN_MODE0_SET(val, 0x4421);
	ग_लिखोl(val, sds_base + SATA_ENET_SDS_CTL0);

	/* Configure the घड़ी macro unit (CMU) घड़ी type */
	xgene_phy_cfg_cmu_clk_type(ctx, PHY_CMU, clk_type);

	/* Configure the घड़ी macro */
	xgene_phy_sata_cfg_cmu_core(ctx, PHY_CMU, clk_type);

	/* Enable SSC अगर enabled */
	अगर (ssc_enable)
		xgene_phy_ssc_enable(ctx, PHY_CMU);

	/* Configure PHY lanes */
	xgene_phy_sata_cfg_lanes(ctx);

	/* Set Rx/Tx 20-bit */
	val = पढ़ोl(sds_base + SATA_ENET_SDS_PCS_CTL0);
	val = REGSPEC_CFG_I_RX_WORDMODE0_SET(val, 0x3);
	val = REGSPEC_CFG_I_TX_WORDMODE0_SET(val, 0x3);
	ग_लिखोl(val, sds_base + SATA_ENET_SDS_PCS_CTL0);

	/* Start PLL calibration and try क्रम three बार */
	i = 10;
	करो अणु
		अगर (!xgene_phy_cal_rdy_chk(ctx, PHY_CMU, clk_type))
			अवरोध;
		/* If failed, toggle the VCO घातer संकेत and start again */
		xgene_phy_pdwn_क्रमce_vco(ctx, PHY_CMU, clk_type);
	पूर्ण जबतक (--i > 0);
	/* Even on failure, allow to जारी any way */
	अगर (i <= 0)
		dev_err(ctx->dev, "PLL calibration failed\n");

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_phy_hw_initialize(काष्ठा xgene_phy_ctx *ctx,
				   क्रमागत clk_type_t clk_type,
				   पूर्णांक ssc_enable)
अणु
	पूर्णांक rc;

	dev_dbg(ctx->dev, "PHY init clk type %d\n", clk_type);

	अगर (ctx->mode == MODE_SATA) अणु
		rc = xgene_phy_hw_init_sata(ctx, clk_type, ssc_enable);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		dev_err(ctx->dev, "Un-supported customer pin mode %d\n",
			ctx->mode);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Receiver Offset Calibration:
 *
 * Calibrate the receiver संकेत path offset in two steps - summar and
 * latch calibrations
 */
अटल व्योम xgene_phy_क्रमce_lat_summer_cal(काष्ठा xgene_phy_ctx *ctx, पूर्णांक lane)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा अणु
		u32 reg;
		u32 val;
	पूर्ण serdes_reg[] = अणु
		अणुRXTX_REG38, 0x0पूर्ण,
		अणुRXTX_REG39, 0xff00पूर्ण,
		अणुRXTX_REG40, 0xffffपूर्ण,
		अणुRXTX_REG41, 0xffffपूर्ण,
		अणुRXTX_REG42, 0xffffपूर्ण,
		अणुRXTX_REG43, 0xffffपूर्ण,
		अणुRXTX_REG44, 0xffffपूर्ण,
		अणुRXTX_REG45, 0xffffपूर्ण,
		अणुRXTX_REG46, 0xffffपूर्ण,
		अणुRXTX_REG47, 0xfffcपूर्ण,
		अणुRXTX_REG48, 0x0पूर्ण,
		अणुRXTX_REG49, 0x0पूर्ण,
		अणुRXTX_REG50, 0x0पूर्ण,
		अणुRXTX_REG51, 0x0पूर्ण,
		अणुRXTX_REG52, 0x0पूर्ण,
		अणुRXTX_REG53, 0x0पूर्ण,
		अणुRXTX_REG54, 0x0पूर्ण,
		अणुRXTX_REG55, 0x0पूर्ण,
	पूर्ण;

	/* Start SUMMER calibration */
	serdes_setbits(ctx, lane, RXTX_REG127,
		       RXTX_REG127_FORCE_SUM_CAL_START_MASK);
	/*
	 * As per PHY design spec, the Summer calibration requires a minimum
	 * of 100us to complete.
	 */
	usleep_range(100, 500);
	serdes_clrbits(ctx, lane, RXTX_REG127,
			RXTX_REG127_FORCE_SUM_CAL_START_MASK);
	/*
	 * As per PHY design spec, the स्वतः calibration requires a minimum
	 * of 100us to complete.
	 */
	usleep_range(100, 500);

	/* Start latch calibration */
	serdes_setbits(ctx, lane, RXTX_REG127,
		       RXTX_REG127_FORCE_LAT_CAL_START_MASK);
	/*
	 * As per PHY design spec, the latch calibration requires a minimum
	 * of 100us to complete.
	 */
	usleep_range(100, 500);
	serdes_clrbits(ctx, lane, RXTX_REG127,
		       RXTX_REG127_FORCE_LAT_CAL_START_MASK);

	/* Configure the PHY lane क्रम calibration */
	serdes_wr(ctx, lane, RXTX_REG28, 0x7);
	serdes_wr(ctx, lane, RXTX_REG31, 0x7e00);
	serdes_clrbits(ctx, lane, RXTX_REG4,
		       RXTX_REG4_TX_LOOPBACK_BUF_EN_MASK);
	serdes_clrbits(ctx, lane, RXTX_REG7,
		       RXTX_REG7_LOOP_BACK_ENA_CTLE_MASK);
	क्रम (i = 0; i < ARRAY_SIZE(serdes_reg); i++)
		serdes_wr(ctx, lane, serdes_reg[i].reg,
			  serdes_reg[i].val);
पूर्ण

अटल व्योम xgene_phy_reset_rxd(काष्ठा xgene_phy_ctx *ctx, पूर्णांक lane)
अणु
	/* Reset digital Rx */
	serdes_clrbits(ctx, lane, RXTX_REG7, RXTX_REG7_RESETB_RXD_MASK);
	/* As per PHY design spec, the reset requires a minimum of 100us. */
	usleep_range(100, 150);
	serdes_setbits(ctx, lane, RXTX_REG7, RXTX_REG7_RESETB_RXD_MASK);
पूर्ण

अटल पूर्णांक xgene_phy_get_avg(पूर्णांक accum, पूर्णांक samples)
अणु
	वापस (accum + (samples / 2)) / samples;
पूर्ण

अटल व्योम xgene_phy_gen_avg_val(काष्ठा xgene_phy_ctx *ctx, पूर्णांक lane)
अणु
	पूर्णांक max_loop = 10;
	पूर्णांक avg_loop = 0;
	पूर्णांक lat_करो = 0, lat_xo = 0, lat_eo = 0, lat_so = 0;
	पूर्णांक lat_de = 0, lat_xe = 0, lat_ee = 0, lat_se = 0;
	पूर्णांक sum_cal = 0;
	पूर्णांक lat_करो_itr, lat_xo_itr, lat_eo_itr, lat_so_itr;
	पूर्णांक lat_de_itr, lat_xe_itr, lat_ee_itr, lat_se_itr;
	पूर्णांक sum_cal_itr;
	पूर्णांक fail_even;
	पूर्णांक fail_odd;
	u32 val;

	dev_dbg(ctx->dev, "Generating avg calibration value for lane %d\n",
		lane);

	/* Enable RX Hi-Z termination */
	serdes_setbits(ctx, lane, RXTX_REG12,
			RXTX_REG12_RX_DET_TERM_ENABLE_MASK);
	/* Turn off DFE */
	serdes_wr(ctx, lane, RXTX_REG28, 0x0000);
	/* DFE Presets to zero */
	serdes_wr(ctx, lane, RXTX_REG31, 0x0000);

	/*
	 * Receiver Offset Calibration:
	 * Calibrate the receiver संकेत path offset in two steps - summar
	 * and latch calibration.
	 * Runs the "Receiver Offset Calibration multiple बार to determine
	 * the average value to use.
	 */
	जबतक (avg_loop < max_loop) अणु
		/* Start the calibration */
		xgene_phy_क्रमce_lat_summer_cal(ctx, lane);

		serdes_rd(ctx, lane, RXTX_REG21, &val);
		lat_करो_itr = RXTX_REG21_DO_LATCH_CALOUT_RD(val);
		lat_xo_itr = RXTX_REG21_XO_LATCH_CALOUT_RD(val);
		fail_odd = RXTX_REG21_LATCH_CAL_FAIL_ODD_RD(val);

		serdes_rd(ctx, lane, RXTX_REG22, &val);
		lat_eo_itr = RXTX_REG22_EO_LATCH_CALOUT_RD(val);
		lat_so_itr = RXTX_REG22_SO_LATCH_CALOUT_RD(val);
		fail_even = RXTX_REG22_LATCH_CAL_FAIL_EVEN_RD(val);

		serdes_rd(ctx, lane, RXTX_REG23, &val);
		lat_de_itr = RXTX_REG23_DE_LATCH_CALOUT_RD(val);
		lat_xe_itr = RXTX_REG23_XE_LATCH_CALOUT_RD(val);

		serdes_rd(ctx, lane, RXTX_REG24, &val);
		lat_ee_itr = RXTX_REG24_EE_LATCH_CALOUT_RD(val);
		lat_se_itr = RXTX_REG24_SE_LATCH_CALOUT_RD(val);

		serdes_rd(ctx, lane, RXTX_REG121, &val);
		sum_cal_itr = RXTX_REG121_SUMOS_CAL_CODE_RD(val);

		/* Check क्रम failure. If passed, sum them क्रम averaging */
		अगर ((fail_even == 0 || fail_even == 1) &&
		    (fail_odd == 0 || fail_odd == 1)) अणु
			lat_करो += lat_करो_itr;
			lat_xo += lat_xo_itr;
			lat_eo += lat_eo_itr;
			lat_so += lat_so_itr;
			lat_de += lat_de_itr;
			lat_xe += lat_xe_itr;
			lat_ee += lat_ee_itr;
			lat_se += lat_se_itr;
			sum_cal += sum_cal_itr;

			dev_dbg(ctx->dev, "Iteration %d:\n", avg_loop);
			dev_dbg(ctx->dev, "DO 0x%x XO 0x%x EO 0x%x SO 0x%x\n",
				lat_करो_itr, lat_xo_itr, lat_eo_itr,
				lat_so_itr);
			dev_dbg(ctx->dev, "DE 0x%x XE 0x%x EE 0x%x SE 0x%x\n",
				lat_de_itr, lat_xe_itr, lat_ee_itr,
				lat_se_itr);
			dev_dbg(ctx->dev, "SUM 0x%x\n", sum_cal_itr);
			++avg_loop;
		पूर्ण अन्यथा अणु
			dev_err(ctx->dev,
				"Receiver calibration failed at %d loop\n",
				avg_loop);
		पूर्ण
		xgene_phy_reset_rxd(ctx, lane);
	पूर्ण

	/* Update latch manual calibration with average value */
	serdes_rd(ctx, lane, RXTX_REG127, &val);
	val = RXTX_REG127_DO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_करो, max_loop));
	val = RXTX_REG127_XO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_xo, max_loop));
	serdes_wr(ctx, lane, RXTX_REG127, val);

	serdes_rd(ctx, lane, RXTX_REG128, &val);
	val = RXTX_REG128_EO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_eo, max_loop));
	val = RXTX_REG128_SO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_so, max_loop));
	serdes_wr(ctx, lane, RXTX_REG128, val);

	serdes_rd(ctx, lane, RXTX_REG129, &val);
	val = RXTX_REG129_DE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_de, max_loop));
	val = RXTX_REG129_XE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_xe, max_loop));
	serdes_wr(ctx, lane, RXTX_REG129, val);

	serdes_rd(ctx, lane, RXTX_REG130, &val);
	val = RXTX_REG130_EE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_ee, max_loop));
	val = RXTX_REG130_SE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_se, max_loop));
	serdes_wr(ctx, lane, RXTX_REG130, val);

	/* Update SUMMER calibration with average value */
	serdes_rd(ctx, lane, RXTX_REG14, &val);
	val = RXTX_REG14_CLTE_LATCAL_MAN_PROG_SET(val,
		xgene_phy_get_avg(sum_cal, max_loop));
	serdes_wr(ctx, lane, RXTX_REG14, val);

	dev_dbg(ctx->dev, "Average Value:\n");
	dev_dbg(ctx->dev, "DO 0x%x XO 0x%x EO 0x%x SO 0x%x\n",
		 xgene_phy_get_avg(lat_करो, max_loop),
		 xgene_phy_get_avg(lat_xo, max_loop),
		 xgene_phy_get_avg(lat_eo, max_loop),
		 xgene_phy_get_avg(lat_so, max_loop));
	dev_dbg(ctx->dev, "DE 0x%x XE 0x%x EE 0x%x SE 0x%x\n",
		 xgene_phy_get_avg(lat_de, max_loop),
		 xgene_phy_get_avg(lat_xe, max_loop),
		 xgene_phy_get_avg(lat_ee, max_loop),
		 xgene_phy_get_avg(lat_se, max_loop));
	dev_dbg(ctx->dev, "SUM 0x%x\n",
		xgene_phy_get_avg(sum_cal, max_loop));

	serdes_rd(ctx, lane, RXTX_REG14, &val);
	val = RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(val, 0x1);
	serdes_wr(ctx, lane, RXTX_REG14, val);
	dev_dbg(ctx->dev, "Enable Manual Summer calibration\n");

	serdes_rd(ctx, lane, RXTX_REG127, &val);
	val = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(val, 0x1);
	dev_dbg(ctx->dev, "Enable Manual Latch calibration\n");
	serdes_wr(ctx, lane, RXTX_REG127, val);

	/* Disable RX Hi-Z termination */
	serdes_rd(ctx, lane, RXTX_REG12, &val);
	val = RXTX_REG12_RX_DET_TERM_ENABLE_SET(val, 0);
	serdes_wr(ctx, lane, RXTX_REG12, val);
	/* Turn on DFE */
	serdes_wr(ctx, lane, RXTX_REG28, 0x0007);
	/* Set DFE preset */
	serdes_wr(ctx, lane, RXTX_REG31, 0x7e00);
पूर्ण

अटल पूर्णांक xgene_phy_hw_init(काष्ठा phy *phy)
अणु
	काष्ठा xgene_phy_ctx *ctx = phy_get_drvdata(phy);
	पूर्णांक rc;
	पूर्णांक i;

	rc = xgene_phy_hw_initialize(ctx, CLK_EXT_DIFF, SSC_DISABLE);
	अगर (rc) अणु
		dev_err(ctx->dev, "PHY initialize failed %d\n", rc);
		वापस rc;
	पूर्ण

	/* Setup घड़ी properly after PHY configuration */
	अगर (!IS_ERR(ctx->clk)) अणु
		/* HW requires an toggle of the घड़ी */
		clk_prepare_enable(ctx->clk);
		clk_disable_unprepare(ctx->clk);
		clk_prepare_enable(ctx->clk);
	पूर्ण

	/* Compute average value */
	क्रम (i = 0; i < MAX_LANE; i++)
		xgene_phy_gen_avg_val(ctx, i);

	dev_dbg(ctx->dev, "PHY initialized\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops xgene_phy_ops = अणु
	.init		= xgene_phy_hw_init,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *xgene_phy_xlate(काष्ठा device *dev,
				   काष्ठा of_phandle_args *args)
अणु
	काष्ठा xgene_phy_ctx *ctx = dev_get_drvdata(dev);

	अगर (args->args_count <= 0)
		वापस ERR_PTR(-EINVAL);
	अगर (args->args[0] >= MODE_MAX)
		वापस ERR_PTR(-EINVAL);

	ctx->mode = args->args[0];
	वापस ctx->phy;
पूर्ण

अटल व्योम xgene_phy_get_param(काष्ठा platक्रमm_device *pdev,
				स्थिर अक्षर *name, u32 *buffer,
				पूर्णांक count, u32 *शेष_val,
				u32 conv_factor)
अणु
	पूर्णांक i;

	अगर (!of_property_पढ़ो_u32_array(pdev->dev.of_node, name, buffer,
					count)) अणु
		क्रम (i = 0; i < count; i++)
			buffer[i] /= conv_factor;
		वापस;
	पूर्ण
	/* Does not exist, load शेष */
	क्रम (i = 0; i < count; i++)
		buffer[i] = शेष_val[i % 3];
पूर्ण

अटल पूर्णांक xgene_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा xgene_phy_ctx *ctx;
	u32 शेष_spd[] = DEFAULT_SATA_SPD_SEL;
	u32 शेष_txboost_gain[] = DEFAULT_SATA_TXBOOST_GAIN;
	u32 शेष_txeye_direction[] = DEFAULT_SATA_TXEYEसूचीECTION;
	u32 शेष_txeye_tuning[] = DEFAULT_SATA_TXEYETUNING;
	u32 शेष_txamp[] = DEFAULT_SATA_TXAMP;
	u32 शेष_txcn1[] = DEFAULT_SATA_TXCN1;
	u32 शेष_txcn2[] = DEFAULT_SATA_TXCN2;
	u32 शेष_txcp1[] = DEFAULT_SATA_TXCP1;
	पूर्णांक i;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = &pdev->dev;

	ctx->sds_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctx->sds_base))
		वापस PTR_ERR(ctx->sds_base);

	/* Retrieve optional घड़ी */
	ctx->clk = clk_get(&pdev->dev, शून्य);

	/* Load override paramaters */
	xgene_phy_get_param(pdev, "apm,tx-eye-tuning",
		ctx->sata_param.txeyetuning, 6, शेष_txeye_tuning, 1);
	xgene_phy_get_param(pdev, "apm,tx-eye-direction",
		ctx->sata_param.txeyedirection, 6, शेष_txeye_direction, 1);
	xgene_phy_get_param(pdev, "apm,tx-boost-gain",
		ctx->sata_param.txboostgain, 6, शेष_txboost_gain, 1);
	xgene_phy_get_param(pdev, "apm,tx-amplitude",
		ctx->sata_param.txamplitude, 6, शेष_txamp, 13300);
	xgene_phy_get_param(pdev, "apm,tx-pre-cursor1",
		ctx->sata_param.txprecursor_cn1, 6, शेष_txcn1, 18200);
	xgene_phy_get_param(pdev, "apm,tx-pre-cursor2",
		ctx->sata_param.txprecursor_cn2, 6, शेष_txcn2, 18200);
	xgene_phy_get_param(pdev, "apm,tx-post-cursor",
		ctx->sata_param.txpostcursor_cp1, 6, शेष_txcp1, 18200);
	xgene_phy_get_param(pdev, "apm,tx-speed",
		ctx->sata_param.txspeed, 3, शेष_spd, 1);
	क्रम (i = 0; i < MAX_LANE; i++)
		ctx->sata_param.speed[i] = 2; /* Default to Gen3 */

	platक्रमm_set_drvdata(pdev, ctx);

	ctx->phy = devm_phy_create(ctx->dev, शून्य, &xgene_phy_ops);
	अगर (IS_ERR(ctx->phy)) अणु
		dev_dbg(&pdev->dev, "Failed to create PHY\n");
		वापस PTR_ERR(ctx->phy);
	पूर्ण
	phy_set_drvdata(ctx->phy, ctx);

	phy_provider = devm_of_phy_provider_रेजिस्टर(ctx->dev, xgene_phy_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_phy_of_match[] = अणु
	अणु.compatible = "apm,xgene-phy",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_phy_of_match);

अटल काष्ठा platक्रमm_driver xgene_phy_driver = अणु
	.probe = xgene_phy_probe,
	.driver = अणु
		   .name = "xgene-phy",
		   .of_match_table = xgene_phy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(xgene_phy_driver);

MODULE_DESCRIPTION("APM X-Gene Multi-Purpose PHY driver");
MODULE_AUTHOR("Loc Ho <lho@apm.com>");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("0.1");
