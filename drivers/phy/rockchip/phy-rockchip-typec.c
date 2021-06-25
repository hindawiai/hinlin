<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Chris Zhong <zyw@rock-chips.com>
 *         Kever Yang <kever.yang@rock-chips.com>
 *
 * The ROCKCHIP Type-C PHY has two PLL घड़ीs. The first PLL घड़ी
 * is used क्रम USB3, the second PLL घड़ी is used क्रम DP. This Type-C PHY has
 * 3 working modes: USB3 only mode, DP only mode, and USB3+DP mode.
 * At USB3 only mode, both PLL घड़ीs need to be initialized, this allows the
 * PHY to चयन mode between USB3 and USB3+DP, without disconnecting the USB
 * device.
 * In The DP only mode, only the DP PLL needs to be घातered on, and the 4 lanes
 * are all used क्रम DP.
 *
 * This driver माला_लो extcon cable state and property, then decides which mode to
 * select:
 *
 * 1. USB3 only mode:
 *    EXTCON_USB or EXTCON_USB_HOST state is true, and
 *    EXTCON_PROP_USB_SS property is true.
 *    EXTCON_DISP_DP state is false.
 *
 * 2. DP only mode:
 *    EXTCON_DISP_DP state is true, and
 *    EXTCON_PROP_USB_SS property is false.
 *    If EXTCON_USB_HOST state is true, it is DP + USB2 mode, since the USB2 phy
 *    is a separate phy, so this हाल is still DP only mode.
 *
 * 3. USB3+DP mode:
 *    EXTCON_USB_HOST and EXTCON_DISP_DP are both true, and
 *    EXTCON_PROP_USB_SS property is true.
 *
 * This Type-C PHY driver supports normal and flip orientation. The orientation
 * is reported by the EXTCON_PROP_USB_TYPEC_POLARITY property: true is flip
 * orientation, false is normal orientation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/extcon.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/phy/phy.h>

#घोषणा CMN_SSM_BANDGAP			(0x21 << 2)
#घोषणा CMN_SSM_BIAS			(0x22 << 2)
#घोषणा CMN_PLLSM0_PLLEN		(0x29 << 2)
#घोषणा CMN_PLLSM0_PLLPRE		(0x2a << 2)
#घोषणा CMN_PLLSM0_PLLVREF		(0x2b << 2)
#घोषणा CMN_PLLSM0_PLLLOCK		(0x2c << 2)
#घोषणा CMN_PLLSM1_PLLEN		(0x31 << 2)
#घोषणा CMN_PLLSM1_PLLPRE		(0x32 << 2)
#घोषणा CMN_PLLSM1_PLLVREF		(0x33 << 2)
#घोषणा CMN_PLLSM1_PLLLOCK		(0x34 << 2)
#घोषणा CMN_PLLSM1_USER_DEF_CTRL	(0x37 << 2)
#घोषणा CMN_ICAL_OVRD			(0xc1 << 2)
#घोषणा CMN_PLL0_VCOCAL_OVRD		(0x83 << 2)
#घोषणा CMN_PLL0_VCOCAL_INIT		(0x84 << 2)
#घोषणा CMN_PLL0_VCOCAL_ITER		(0x85 << 2)
#घोषणा CMN_PLL0_LOCK_REFCNT_START	(0x90 << 2)
#घोषणा CMN_PLL0_LOCK_PLLCNT_START	(0x92 << 2)
#घोषणा CMN_PLL0_LOCK_PLLCNT_THR	(0x93 << 2)
#घोषणा CMN_PLL0_INTDIV			(0x94 << 2)
#घोषणा CMN_PLL0_FRACDIV		(0x95 << 2)
#घोषणा CMN_PLL0_HIGH_THR		(0x96 << 2)
#घोषणा CMN_PLL0_DSM_DIAG		(0x97 << 2)
#घोषणा CMN_PLL0_SS_CTRL1		(0x98 << 2)
#घोषणा CMN_PLL0_SS_CTRL2		(0x99 << 2)
#घोषणा CMN_PLL1_VCOCAL_START		(0xa1 << 2)
#घोषणा CMN_PLL1_VCOCAL_OVRD		(0xa3 << 2)
#घोषणा CMN_PLL1_VCOCAL_INIT		(0xa4 << 2)
#घोषणा CMN_PLL1_VCOCAL_ITER		(0xa5 << 2)
#घोषणा CMN_PLL1_LOCK_REFCNT_START	(0xb0 << 2)
#घोषणा CMN_PLL1_LOCK_PLLCNT_START	(0xb2 << 2)
#घोषणा CMN_PLL1_LOCK_PLLCNT_THR	(0xb3 << 2)
#घोषणा CMN_PLL1_INTDIV			(0xb4 << 2)
#घोषणा CMN_PLL1_FRACDIV		(0xb5 << 2)
#घोषणा CMN_PLL1_HIGH_THR		(0xb6 << 2)
#घोषणा CMN_PLL1_DSM_DIAG		(0xb7 << 2)
#घोषणा CMN_PLL1_SS_CTRL1		(0xb8 << 2)
#घोषणा CMN_PLL1_SS_CTRL2		(0xb9 << 2)
#घोषणा CMN_RXCAL_OVRD			(0xd1 << 2)

#घोषणा CMN_TXPUCAL_CTRL		(0xe0 << 2)
#घोषणा CMN_TXPUCAL_OVRD		(0xe1 << 2)
#घोषणा CMN_TXPDCAL_CTRL		(0xf0 << 2)
#घोषणा CMN_TXPDCAL_OVRD		(0xf1 << 2)

/* For CMN_TXPUCAL_CTRL, CMN_TXPDCAL_CTRL */
#घोषणा CMN_TXPXCAL_START		BIT(15)
#घोषणा CMN_TXPXCAL_DONE		BIT(14)
#घोषणा CMN_TXPXCAL_NO_RESPONSE		BIT(13)
#घोषणा CMN_TXPXCAL_CURRENT_RESPONSE	BIT(12)

#घोषणा CMN_TXPU_ADJ_CTRL		(0x108 << 2)
#घोषणा CMN_TXPD_ADJ_CTRL		(0x10c << 2)

/*
 * For CMN_TXPUCAL_CTRL, CMN_TXPDCAL_CTRL,
 *     CMN_TXPU_ADJ_CTRL, CMN_TXPDCAL_CTRL
 *
 * NOTE: some of these रेजिस्टरs are करोcumented to be 2's complement
 * चिन्हित numbers, but then करोcumented to be always positive.  Weird.
 * In such a हाल, using CMN_CALIB_CODE_POS() aव्योमs the unnecessary
 * sign extension.
 */
#घोषणा CMN_CALIB_CODE_WIDTH	7
#घोषणा CMN_CALIB_CODE_OFFSET	0
#घोषणा CMN_CALIB_CODE_MASK	GENMASK(CMN_CALIB_CODE_WIDTH, 0)
#घोषणा CMN_CALIB_CODE(x)	\
	sign_extend32((x) >> CMN_CALIB_CODE_OFFSET, CMN_CALIB_CODE_WIDTH)

#घोषणा CMN_CALIB_CODE_POS_MASK	GENMASK(CMN_CALIB_CODE_WIDTH - 1, 0)
#घोषणा CMN_CALIB_CODE_POS(x)	\
	(((x) >> CMN_CALIB_CODE_OFFSET) & CMN_CALIB_CODE_POS_MASK)

#घोषणा CMN_DIAG_PLL0_FBH_OVRD		(0x1c0 << 2)
#घोषणा CMN_DIAG_PLL0_FBL_OVRD		(0x1c1 << 2)
#घोषणा CMN_DIAG_PLL0_OVRD		(0x1c2 << 2)
#घोषणा CMN_DIAG_PLL0_V2I_TUNE		(0x1c5 << 2)
#घोषणा CMN_DIAG_PLL0_CP_TUNE		(0x1c6 << 2)
#घोषणा CMN_DIAG_PLL0_LF_PROG		(0x1c7 << 2)
#घोषणा CMN_DIAG_PLL1_FBH_OVRD		(0x1d0 << 2)
#घोषणा CMN_DIAG_PLL1_FBL_OVRD		(0x1d1 << 2)
#घोषणा CMN_DIAG_PLL1_OVRD		(0x1d2 << 2)
#घोषणा CMN_DIAG_PLL1_V2I_TUNE		(0x1d5 << 2)
#घोषणा CMN_DIAG_PLL1_CP_TUNE		(0x1d6 << 2)
#घोषणा CMN_DIAG_PLL1_LF_PROG		(0x1d7 << 2)
#घोषणा CMN_DIAG_PLL1_PTATIS_TUNE1	(0x1d8 << 2)
#घोषणा CMN_DIAG_PLL1_PTATIS_TUNE2	(0x1d9 << 2)
#घोषणा CMN_DIAG_PLL1_INCLK_CTRL	(0x1da << 2)
#घोषणा CMN_DIAG_HSCLK_SEL		(0x1e0 << 2)

#घोषणा XCVR_PSM_RCTRL(n)		((0x4001 | ((n) << 9)) << 2)
#घोषणा XCVR_PSM_CAL_TMR(n)		((0x4002 | ((n) << 9)) << 2)
#घोषणा XCVR_PSM_A0IN_TMR(n)		((0x4003 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_CAL_SCLR_MULT(n)	((0x4047 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_CPOST_MULT_00(n)	((0x404c | ((n) << 9)) << 2)
#घोषणा TX_TXCC_CPOST_MULT_01(n)	((0x404d | ((n) << 9)) << 2)
#घोषणा TX_TXCC_CPOST_MULT_10(n)	((0x404e | ((n) << 9)) << 2)
#घोषणा TX_TXCC_CPOST_MULT_11(n)	((0x404f | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNFS_MULT_000(n)	((0x4050 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNFS_MULT_001(n)	((0x4051 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNFS_MULT_010(n)	((0x4052 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNFS_MULT_011(n)	((0x4053 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNFS_MULT_100(n)	((0x4054 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNFS_MULT_101(n)	((0x4055 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNFS_MULT_110(n)	((0x4056 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNFS_MULT_111(n)	((0x4057 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNLS_MULT_000(n)	((0x4058 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNLS_MULT_001(n)	((0x4059 | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNLS_MULT_010(n)	((0x405a | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNLS_MULT_011(n)	((0x405b | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNLS_MULT_100(n)	((0x405c | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNLS_MULT_101(n)	((0x405d | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNLS_MULT_110(n)	((0x405e | ((n) << 9)) << 2)
#घोषणा TX_TXCC_MGNLS_MULT_111(n)	((0x405f | ((n) << 9)) << 2)

#घोषणा XCVR_DIAG_PLLDRC_CTRL(n)	((0x40e0 | ((n) << 9)) << 2)
#घोषणा XCVR_DIAG_BIDI_CTRL(n)		((0x40e8 | ((n) << 9)) << 2)
#घोषणा XCVR_DIAG_LANE_FCM_EN_MGN(n)	((0x40f2 | ((n) << 9)) << 2)
#घोषणा TX_PSC_A0(n)			((0x4100 | ((n) << 9)) << 2)
#घोषणा TX_PSC_A1(n)			((0x4101 | ((n) << 9)) << 2)
#घोषणा TX_PSC_A2(n)			((0x4102 | ((n) << 9)) << 2)
#घोषणा TX_PSC_A3(n)			((0x4103 | ((n) << 9)) << 2)
#घोषणा TX_RCVDET_CTRL(n)		((0x4120 | ((n) << 9)) << 2)
#घोषणा TX_RCVDET_EN_TMR(n)		((0x4122 | ((n) << 9)) << 2)
#घोषणा TX_RCVDET_ST_TMR(n)		((0x4123 | ((n) << 9)) << 2)
#घोषणा TX_DIAG_TX_DRV(n)		((0x41e1 | ((n) << 9)) << 2)
#घोषणा TX_DIAG_BGREF_PREDRV_DELAY	(0x41e7 << 2)

/* Use this क्रम "n" in macros like "_MULT_XXX" to target the aux channel */
#घोषणा AUX_CH_LANE			8

#घोषणा TX_ANA_CTRL_REG_1		(0x5020 << 2)

#घोषणा TXDA_DP_AUX_EN			BIT(15)
#घोषणा AUXDA_SE_EN			BIT(14)
#घोषणा TXDA_CAL_LATCH_EN		BIT(13)
#घोषणा AUXDA_POLARITY			BIT(12)
#घोषणा TXDA_DRV_POWER_ISOLATION_EN	BIT(11)
#घोषणा TXDA_DRV_POWER_EN_PH_2_N	BIT(10)
#घोषणा TXDA_DRV_POWER_EN_PH_1_N	BIT(9)
#घोषणा TXDA_BGREF_EN			BIT(8)
#घोषणा TXDA_DRV_LDO_EN			BIT(7)
#घोषणा TXDA_DECAP_EN_DEL		BIT(6)
#घोषणा TXDA_DECAP_EN			BIT(5)
#घोषणा TXDA_UPHY_SUPPLY_EN_DEL		BIT(4)
#घोषणा TXDA_UPHY_SUPPLY_EN		BIT(3)
#घोषणा TXDA_LOW_LEAKAGE_EN		BIT(2)
#घोषणा TXDA_DRV_IDLE_LOWI_EN		BIT(1)
#घोषणा TXDA_DRV_CMN_MODE_EN		BIT(0)

#घोषणा TX_ANA_CTRL_REG_2		(0x5021 << 2)

#घोषणा AUXDA_DEBOUNCING_CLK		BIT(15)
#घोषणा TXDA_LPBK_RECOVERED_CLK_EN	BIT(14)
#घोषणा TXDA_LPBK_ISI_GEN_EN		BIT(13)
#घोषणा TXDA_LPBK_SERIAL_EN		BIT(12)
#घोषणा TXDA_LPBK_LINE_EN		BIT(11)
#घोषणा TXDA_DRV_LDO_REDC_SINKIQ	BIT(10)
#घोषणा XCVR_DECAP_EN_DEL		BIT(9)
#घोषणा XCVR_DECAP_EN			BIT(8)
#घोषणा TXDA_MPHY_ENABLE_HS_NT		BIT(7)
#घोषणा TXDA_MPHY_SA_MODE		BIT(6)
#घोषणा TXDA_DRV_LDO_RBYR_FB_EN		BIT(5)
#घोषणा TXDA_DRV_RST_PULL_DOWN		BIT(4)
#घोषणा TXDA_DRV_LDO_BG_FB_EN		BIT(3)
#घोषणा TXDA_DRV_LDO_BG_REF_EN		BIT(2)
#घोषणा TXDA_DRV_PREDRV_EN_DEL		BIT(1)
#घोषणा TXDA_DRV_PREDRV_EN		BIT(0)

#घोषणा TXDA_COEFF_CALC_CTRL		(0x5022 << 2)

#घोषणा TX_HIGH_Z			BIT(6)
#घोषणा TX_VMARGIN_OFFSET		3
#घोषणा TX_VMARGIN_MASK			0x7
#घोषणा LOW_POWER_SWING_EN		BIT(2)
#घोषणा TX_FCM_DRV_MAIN_EN		BIT(1)
#घोषणा TX_FCM_FULL_MARGIN		BIT(0)

#घोषणा TX_DIG_CTRL_REG_2		(0x5024 << 2)

#घोषणा TX_HIGH_Z_TM_EN			BIT(15)
#घोषणा TX_RESCAL_CODE_OFFSET		0
#घोषणा TX_RESCAL_CODE_MASK		0x3f

#घोषणा TXDA_CYA_AUXDA_CYA		(0x5025 << 2)
#घोषणा TX_ANA_CTRL_REG_3		(0x5026 << 2)
#घोषणा TX_ANA_CTRL_REG_4		(0x5027 << 2)
#घोषणा TX_ANA_CTRL_REG_5		(0x5029 << 2)

#घोषणा RX_PSC_A0(n)			((0x8000 | ((n) << 9)) << 2)
#घोषणा RX_PSC_A1(n)			((0x8001 | ((n) << 9)) << 2)
#घोषणा RX_PSC_A2(n)			((0x8002 | ((n) << 9)) << 2)
#घोषणा RX_PSC_A3(n)			((0x8003 | ((n) << 9)) << 2)
#घोषणा RX_PSC_CAL(n)			((0x8006 | ((n) << 9)) << 2)
#घोषणा RX_PSC_RDY(n)			((0x8007 | ((n) << 9)) << 2)
#घोषणा RX_IQPI_ILL_CAL_OVRD		(0x8023 << 2)
#घोषणा RX_EPI_ILL_CAL_OVRD		(0x8033 << 2)
#घोषणा RX_SDCAL0_OVRD			(0x8041 << 2)
#घोषणा RX_SDCAL1_OVRD			(0x8049 << 2)
#घोषणा RX_SLC_INIT			(0x806d << 2)
#घोषणा RX_SLC_RUN			(0x806e << 2)
#घोषणा RX_CDRLF_CNFG2			(0x8081 << 2)
#घोषणा RX_SIGDET_HL_FILT_TMR(n)	((0x8090 | ((n) << 9)) << 2)
#घोषणा RX_SLC_IOP0_OVRD		(0x8101 << 2)
#घोषणा RX_SLC_IOP1_OVRD		(0x8105 << 2)
#घोषणा RX_SLC_QOP0_OVRD		(0x8109 << 2)
#घोषणा RX_SLC_QOP1_OVRD		(0x810d << 2)
#घोषणा RX_SLC_EOP0_OVRD		(0x8111 << 2)
#घोषणा RX_SLC_EOP1_OVRD		(0x8115 << 2)
#घोषणा RX_SLC_ION0_OVRD		(0x8119 << 2)
#घोषणा RX_SLC_ION1_OVRD		(0x811d << 2)
#घोषणा RX_SLC_QON0_OVRD		(0x8121 << 2)
#घोषणा RX_SLC_QON1_OVRD		(0x8125 << 2)
#घोषणा RX_SLC_EON0_OVRD		(0x8129 << 2)
#घोषणा RX_SLC_EON1_OVRD		(0x812d << 2)
#घोषणा RX_SLC_IEP0_OVRD		(0x8131 << 2)
#घोषणा RX_SLC_IEP1_OVRD		(0x8135 << 2)
#घोषणा RX_SLC_QEP0_OVRD		(0x8139 << 2)
#घोषणा RX_SLC_QEP1_OVRD		(0x813d << 2)
#घोषणा RX_SLC_EEP0_OVRD		(0x8141 << 2)
#घोषणा RX_SLC_EEP1_OVRD		(0x8145 << 2)
#घोषणा RX_SLC_IEN0_OVRD		(0x8149 << 2)
#घोषणा RX_SLC_IEN1_OVRD		(0x814d << 2)
#घोषणा RX_SLC_QEN0_OVRD		(0x8151 << 2)
#घोषणा RX_SLC_QEN1_OVRD		(0x8155 << 2)
#घोषणा RX_SLC_EEN0_OVRD		(0x8159 << 2)
#घोषणा RX_SLC_EEN1_OVRD		(0x815d << 2)
#घोषणा RX_REE_CTRL_DATA_MASK(n)	((0x81bb | ((n) << 9)) << 2)
#घोषणा RX_DIAG_SIGDET_TUNE(n)		((0x81dc | ((n) << 9)) << 2)
#घोषणा RX_DIAG_SC2C_DELAY		(0x81e1 << 2)

#घोषणा PMA_LANE_CFG			(0xc000 << 2)
#घोषणा PIPE_CMN_CTRL1			(0xc001 << 2)
#घोषणा PIPE_CMN_CTRL2			(0xc002 << 2)
#घोषणा PIPE_COM_LOCK_CFG1		(0xc003 << 2)
#घोषणा PIPE_COM_LOCK_CFG2		(0xc004 << 2)
#घोषणा PIPE_RCV_DET_INH		(0xc005 << 2)
#घोषणा DP_MODE_CTL			(0xc008 << 2)
#घोषणा DP_CLK_CTL			(0xc009 << 2)
#घोषणा STS				(0xc00F << 2)
#घोषणा PHY_ISO_CMN_CTRL		(0xc010 << 2)
#घोषणा PHY_DP_TX_CTL			(0xc408 << 2)
#घोषणा PMA_CMN_CTRL1			(0xc800 << 2)
#घोषणा PHY_PMA_ISO_CMN_CTRL		(0xc810 << 2)
#घोषणा PHY_ISOLATION_CTRL		(0xc81f << 2)
#घोषणा PHY_PMA_ISO_XCVR_CTRL(n)	((0xcc11 | ((n) << 6)) << 2)
#घोषणा PHY_PMA_ISO_LINK_MODE(n)	((0xcc12 | ((n) << 6)) << 2)
#घोषणा PHY_PMA_ISO_PWRST_CTRL(n)	((0xcc13 | ((n) << 6)) << 2)
#घोषणा PHY_PMA_ISO_TX_DATA_LO(n)	((0xcc14 | ((n) << 6)) << 2)
#घोषणा PHY_PMA_ISO_TX_DATA_HI(n)	((0xcc15 | ((n) << 6)) << 2)
#घोषणा PHY_PMA_ISO_RX_DATA_LO(n)	((0xcc16 | ((n) << 6)) << 2)
#घोषणा PHY_PMA_ISO_RX_DATA_HI(n)	((0xcc17 | ((n) << 6)) << 2)
#घोषणा TX_BIST_CTRL(n)			((0x4140 | ((n) << 9)) << 2)
#घोषणा TX_BIST_UDDWR(n)		((0x4141 | ((n) << 9)) << 2)

/*
 * Selects which PLL घड़ी will be driven on the analog high speed
 * घड़ी 0: PLL 0 भाग 1
 * घड़ी 1: PLL 1 भाग 2
 */
#घोषणा CLK_PLL_CONFIG			0X30
#घोषणा CLK_PLL_MASK			0x33

#घोषणा CMN_READY			BIT(0)

#घोषणा DP_PLL_CLOCK_ENABLE		BIT(2)
#घोषणा DP_PLL_ENABLE			BIT(0)
#घोषणा DP_PLL_DATA_RATE_RBR		((2 << 12) | (4 << 8))
#घोषणा DP_PLL_DATA_RATE_HBR		((2 << 12) | (4 << 8))
#घोषणा DP_PLL_DATA_RATE_HBR2		((1 << 12) | (2 << 8))

#घोषणा DP_MODE_A0			BIT(4)
#घोषणा DP_MODE_A2			BIT(6)
#घोषणा DP_MODE_ENTER_A0		0xc101
#घोषणा DP_MODE_ENTER_A2		0xc104

#घोषणा PHY_MODE_SET_TIMEOUT		100000

#घोषणा PIN_ASSIGN_C_E			0x51d9
#घोषणा PIN_ASSIGN_D_F			0x5100

#घोषणा MODE_DISCONNECT			0
#घोषणा MODE_UFP_USB			BIT(0)
#घोषणा MODE_DFP_USB			BIT(1)
#घोषणा MODE_DFP_DP			BIT(2)

काष्ठा usb3phy_reg अणु
	u32 offset;
	u32 enable_bit;
	u32 ग_लिखो_enable;
पूर्ण;

/**
 * काष्ठा rockchip_usb3phy_port_cfg - usb3-phy port configuration.
 * @reg: the base address क्रम usb3-phy config.
 * @typec_conn_dir: the रेजिस्टर of type-c connector direction.
 * @usb3tousb2_en: the रेजिस्टर of type-c क्रमce usb2 to usb2 enable.
 * @बाह्यal_psm: the रेजिस्टर of type-c phy बाह्यal psm घड़ी.
 * @pipe_status: the रेजिस्टर of type-c phy pipe status.
 * @usb3_host_disable: the रेजिस्टर of type-c usb3 host disable.
 * @usb3_host_port: the रेजिस्टर of type-c usb3 host port.
 * @uphy_dp_sel: the रेजिस्टर of type-c phy DP select control.
 */
काष्ठा rockchip_usb3phy_port_cfg अणु
	अचिन्हित पूर्णांक reg;
	काष्ठा usb3phy_reg typec_conn_dir;
	काष्ठा usb3phy_reg usb3tousb2_en;
	काष्ठा usb3phy_reg बाह्यal_psm;
	काष्ठा usb3phy_reg pipe_status;
	काष्ठा usb3phy_reg usb3_host_disable;
	काष्ठा usb3phy_reg usb3_host_port;
	काष्ठा usb3phy_reg uphy_dp_sel;
पूर्ण;

काष्ठा rockchip_typec_phy अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा extcon_dev *extcon;
	काष्ठा regmap *grf_regs;
	काष्ठा clk *clk_core;
	काष्ठा clk *clk_ref;
	काष्ठा reset_control *uphy_rst;
	काष्ठा reset_control *pipe_rst;
	काष्ठा reset_control *tcphy_rst;
	स्थिर काष्ठा rockchip_usb3phy_port_cfg *port_cfgs;
	/* mutex to protect access to inभागidual PHYs */
	काष्ठा mutex lock;

	bool flip;
	u8 mode;
पूर्ण;

काष्ठा phy_reg अणु
	u16 value;
	u32 addr;
पूर्ण;

अटल काष्ठा phy_reg usb3_pll_cfg[] = अणु
	अणु 0xf0,		CMN_PLL0_VCOCAL_INIT पूर्ण,
	अणु 0x18,		CMN_PLL0_VCOCAL_ITER पूर्ण,
	अणु 0xd0,		CMN_PLL0_INTDIV पूर्ण,
	अणु 0x4a4a,	CMN_PLL0_FRACDIV पूर्ण,
	अणु 0x34,		CMN_PLL0_HIGH_THR पूर्ण,
	अणु 0x1ee,	CMN_PLL0_SS_CTRL1 पूर्ण,
	अणु 0x7f03,	CMN_PLL0_SS_CTRL2 पूर्ण,
	अणु 0x20,		CMN_PLL0_DSM_DIAG पूर्ण,
	अणु 0,		CMN_DIAG_PLL0_OVRD पूर्ण,
	अणु 0,		CMN_DIAG_PLL0_FBH_OVRD पूर्ण,
	अणु 0,		CMN_DIAG_PLL0_FBL_OVRD पूर्ण,
	अणु 0x7,		CMN_DIAG_PLL0_V2I_TUNE पूर्ण,
	अणु 0x45,		CMN_DIAG_PLL0_CP_TUNE पूर्ण,
	अणु 0x8,		CMN_DIAG_PLL0_LF_PROG पूर्ण,
पूर्ण;

अटल काष्ठा phy_reg dp_pll_cfg[] = अणु
	अणु 0xf0,		CMN_PLL1_VCOCAL_INIT पूर्ण,
	अणु 0x18,		CMN_PLL1_VCOCAL_ITER पूर्ण,
	अणु 0x30b9,	CMN_PLL1_VCOCAL_START पूर्ण,
	अणु 0x21c,	CMN_PLL1_INTDIV पूर्ण,
	अणु 0,		CMN_PLL1_FRACDIV पूर्ण,
	अणु 0x5,		CMN_PLL1_HIGH_THR पूर्ण,
	अणु 0x35,		CMN_PLL1_SS_CTRL1 पूर्ण,
	अणु 0x7f1e,	CMN_PLL1_SS_CTRL2 पूर्ण,
	अणु 0x20,		CMN_PLL1_DSM_DIAG पूर्ण,
	अणु 0,		CMN_PLLSM1_USER_DEF_CTRL पूर्ण,
	अणु 0,		CMN_DIAG_PLL1_OVRD पूर्ण,
	अणु 0,		CMN_DIAG_PLL1_FBH_OVRD पूर्ण,
	अणु 0,		CMN_DIAG_PLL1_FBL_OVRD पूर्ण,
	अणु 0x6,		CMN_DIAG_PLL1_V2I_TUNE पूर्ण,
	अणु 0x45,		CMN_DIAG_PLL1_CP_TUNE पूर्ण,
	अणु 0x8,		CMN_DIAG_PLL1_LF_PROG पूर्ण,
	अणु 0x100,	CMN_DIAG_PLL1_PTATIS_TUNE1 पूर्ण,
	अणु 0x7,		CMN_DIAG_PLL1_PTATIS_TUNE2 पूर्ण,
	अणु 0x4,		CMN_DIAG_PLL1_INCLK_CTRL पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_usb3phy_port_cfg rk3399_usb3phy_port_cfgs[] = अणु
	अणु
		.reg = 0xff7c0000,
		.typec_conn_dir	= अणु 0xe580, 0, 16 पूर्ण,
		.usb3tousb2_en	= अणु 0xe580, 3, 19 पूर्ण,
		.बाह्यal_psm	= अणु 0xe588, 14, 30 पूर्ण,
		.pipe_status	= अणु 0xe5c0, 0, 0 पूर्ण,
		.usb3_host_disable = अणु 0x2434, 0, 16 पूर्ण,
		.usb3_host_port = अणु 0x2434, 12, 28 पूर्ण,
		.uphy_dp_sel	= अणु 0x6268, 19, 19 पूर्ण,
	पूर्ण,
	अणु
		.reg = 0xff800000,
		.typec_conn_dir	= अणु 0xe58c, 0, 16 पूर्ण,
		.usb3tousb2_en	= अणु 0xe58c, 3, 19 पूर्ण,
		.बाह्यal_psm	= अणु 0xe594, 14, 30 पूर्ण,
		.pipe_status	= अणु 0xe5c0, 16, 16 पूर्ण,
		.usb3_host_disable = अणु 0x2444, 0, 16 पूर्ण,
		.usb3_host_port = अणु 0x2444, 12, 28 पूर्ण,
		.uphy_dp_sel	= अणु 0x6268, 3, 19 पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम tcphy_cfg_24m(काष्ठा rockchip_typec_phy *tcphy)
अणु
	u32 i, rdata;

	/*
	 * cmn_ref_clk_sel = 3, select the 24Mhz क्रम clk parent
	 * cmn_psm_clk_dig_भाग = 2, set the clk भागision to 2
	 */
	ग_लिखोl(0x830, tcphy->base + PMA_CMN_CTRL1);
	क्रम (i = 0; i < 4; i++) अणु
		/*
		 * The following PHY configuration assumes a 24 MHz reference
		 * घड़ी.
		 */
		ग_लिखोl(0x90, tcphy->base + XCVR_DIAG_LANE_FCM_EN_MGN(i));
		ग_लिखोl(0x960, tcphy->base + TX_RCVDET_EN_TMR(i));
		ग_लिखोl(0x30, tcphy->base + TX_RCVDET_ST_TMR(i));
	पूर्ण

	rdata = पढ़ोl(tcphy->base + CMN_DIAG_HSCLK_SEL);
	rdata &= ~CLK_PLL_MASK;
	rdata |= CLK_PLL_CONFIG;
	ग_लिखोl(rdata, tcphy->base + CMN_DIAG_HSCLK_SEL);
पूर्ण

अटल व्योम tcphy_cfg_usb3_pll(काष्ठा rockchip_typec_phy *tcphy)
अणु
	u32 i;

	/* load the configuration of PLL0 */
	क्रम (i = 0; i < ARRAY_SIZE(usb3_pll_cfg); i++)
		ग_लिखोl(usb3_pll_cfg[i].value,
		       tcphy->base + usb3_pll_cfg[i].addr);
पूर्ण

अटल व्योम tcphy_cfg_dp_pll(काष्ठा rockchip_typec_phy *tcphy)
अणु
	u32 i;

	/* set the शेष mode to RBR */
	ग_लिखोl(DP_PLL_CLOCK_ENABLE | DP_PLL_ENABLE | DP_PLL_DATA_RATE_RBR,
	       tcphy->base + DP_CLK_CTL);

	/* load the configuration of PLL1 */
	क्रम (i = 0; i < ARRAY_SIZE(dp_pll_cfg); i++)
		ग_लिखोl(dp_pll_cfg[i].value, tcphy->base + dp_pll_cfg[i].addr);
पूर्ण

अटल व्योम tcphy_tx_usb3_cfg_lane(काष्ठा rockchip_typec_phy *tcphy, u32 lane)
अणु
	ग_लिखोl(0x7799, tcphy->base + TX_PSC_A0(lane));
	ग_लिखोl(0x7798, tcphy->base + TX_PSC_A1(lane));
	ग_लिखोl(0x5098, tcphy->base + TX_PSC_A2(lane));
	ग_लिखोl(0x5098, tcphy->base + TX_PSC_A3(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_000(lane));
	ग_लिखोl(0xbf, tcphy->base + XCVR_DIAG_BIDI_CTRL(lane));
पूर्ण

अटल व्योम tcphy_rx_usb3_cfg_lane(काष्ठा rockchip_typec_phy *tcphy, u32 lane)
अणु
	ग_लिखोl(0xa6fd, tcphy->base + RX_PSC_A0(lane));
	ग_लिखोl(0xa6fd, tcphy->base + RX_PSC_A1(lane));
	ग_लिखोl(0xa410, tcphy->base + RX_PSC_A2(lane));
	ग_लिखोl(0x2410, tcphy->base + RX_PSC_A3(lane));
	ग_लिखोl(0x23ff, tcphy->base + RX_PSC_CAL(lane));
	ग_लिखोl(0x13, tcphy->base + RX_SIGDET_HL_FILT_TMR(lane));
	ग_लिखोl(0x03e7, tcphy->base + RX_REE_CTRL_DATA_MASK(lane));
	ग_लिखोl(0x1004, tcphy->base + RX_DIAG_SIGDET_TUNE(lane));
	ग_लिखोl(0x2010, tcphy->base + RX_PSC_RDY(lane));
	ग_लिखोl(0xfb, tcphy->base + XCVR_DIAG_BIDI_CTRL(lane));
पूर्ण

अटल व्योम tcphy_dp_cfg_lane(काष्ठा rockchip_typec_phy *tcphy, u32 lane)
अणु
	u16 rdata;

	ग_लिखोl(0xbefc, tcphy->base + XCVR_PSM_RCTRL(lane));
	ग_लिखोl(0x6799, tcphy->base + TX_PSC_A0(lane));
	ग_लिखोl(0x6798, tcphy->base + TX_PSC_A1(lane));
	ग_लिखोl(0x98, tcphy->base + TX_PSC_A2(lane));
	ग_लिखोl(0x98, tcphy->base + TX_PSC_A3(lane));

	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_000(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_001(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_010(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_011(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_100(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_101(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_110(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_MGNFS_MULT_111(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_CPOST_MULT_10(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_CPOST_MULT_01(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_CPOST_MULT_00(lane));
	ग_लिखोl(0, tcphy->base + TX_TXCC_CPOST_MULT_11(lane));

	ग_लिखोl(0x128, tcphy->base + TX_TXCC_CAL_SCLR_MULT(lane));
	ग_लिखोl(0x400, tcphy->base + TX_DIAG_TX_DRV(lane));

	rdata = पढ़ोl(tcphy->base + XCVR_DIAG_PLLDRC_CTRL(lane));
	rdata = (rdata & 0x8fff) | 0x6000;
	ग_लिखोl(rdata, tcphy->base + XCVR_DIAG_PLLDRC_CTRL(lane));
पूर्ण

अटल अंतरभूत पूर्णांक property_enable(काष्ठा rockchip_typec_phy *tcphy,
				  स्थिर काष्ठा usb3phy_reg *reg, bool en)
अणु
	u32 mask = 1 << reg->ग_लिखो_enable;
	u32 val = en << reg->enable_bit;

	वापस regmap_ग_लिखो(tcphy->grf_regs, reg->offset, val | mask);
पूर्ण

अटल व्योम tcphy_dp_aux_set_flip(काष्ठा rockchip_typec_phy *tcphy)
अणु
	u16 tx_ana_ctrl_reg_1;

	/*
	 * Select the polarity of the xcvr:
	 * 1, Reverses the polarity (If TYPEC, Pulls ups aux_p and pull
	 * करोwn aux_m)
	 * 0, Normal polarity (अगर TYPEC, pulls up aux_m and pulls करोwn
	 * aux_p)
	 */
	tx_ana_ctrl_reg_1 = पढ़ोl(tcphy->base + TX_ANA_CTRL_REG_1);
	अगर (!tcphy->flip)
		tx_ana_ctrl_reg_1 |= AUXDA_POLARITY;
	अन्यथा
		tx_ana_ctrl_reg_1 &= ~AUXDA_POLARITY;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
पूर्ण

अटल व्योम tcphy_dp_aux_calibration(काष्ठा rockchip_typec_phy *tcphy)
अणु
	u16 val;
	u16 tx_ana_ctrl_reg_1;
	u16 tx_ana_ctrl_reg_2;
	s32 pu_calib_code, pd_calib_code;
	s32 pu_adj, pd_adj;
	u16 calib;

	/*
	 * Calculate calibration code as per करोcs: use an average of the
	 * pull करोwn and pull up.  Then add in adjusपंचांगents.
	 */
	val = पढ़ोl(tcphy->base + CMN_TXPUCAL_CTRL);
	pu_calib_code = CMN_CALIB_CODE_POS(val);
	val = पढ़ोl(tcphy->base + CMN_TXPDCAL_CTRL);
	pd_calib_code = CMN_CALIB_CODE_POS(val);
	val = पढ़ोl(tcphy->base + CMN_TXPU_ADJ_CTRL);
	pu_adj = CMN_CALIB_CODE(val);
	val = पढ़ोl(tcphy->base + CMN_TXPD_ADJ_CTRL);
	pd_adj = CMN_CALIB_CODE(val);
	calib = (pu_calib_code + pd_calib_code) / 2 + pu_adj + pd_adj;

	/* disable txda_cal_latch_en क्रम reग_लिखो the calibration values */
	tx_ana_ctrl_reg_1 = पढ़ोl(tcphy->base + TX_ANA_CTRL_REG_1);
	tx_ana_ctrl_reg_1 &= ~TXDA_CAL_LATCH_EN;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);

	/* ग_लिखो the calibration, then delay 10 ms as sample in करोcs */
	val = पढ़ोl(tcphy->base + TX_DIG_CTRL_REG_2);
	val &= ~(TX_RESCAL_CODE_MASK << TX_RESCAL_CODE_OFFSET);
	val |= calib << TX_RESCAL_CODE_OFFSET;
	ग_लिखोl(val, tcphy->base + TX_DIG_CTRL_REG_2);
	usleep_range(10000, 10050);

	/*
	 * Enable संकेत क्रम latch that sample and holds calibration values.
	 * Activate this संकेत क्रम 1 घड़ी cycle to sample new calibration
	 * values.
	 */
	tx_ana_ctrl_reg_1 |= TXDA_CAL_LATCH_EN;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
	usleep_range(150, 200);

	/* set TX Voltage Level and TX Deemphasis to 0 */
	ग_लिखोl(0, tcphy->base + PHY_DP_TX_CTL);

	/* re-enable decap */
	tx_ana_ctrl_reg_2 = XCVR_DECAP_EN;
	ग_लिखोl(tx_ana_ctrl_reg_2, tcphy->base + TX_ANA_CTRL_REG_2);
	udelay(1);
	tx_ana_ctrl_reg_2 |= XCVR_DECAP_EN_DEL;
	ग_लिखोl(tx_ana_ctrl_reg_2, tcphy->base + TX_ANA_CTRL_REG_2);

	ग_लिखोl(0, tcphy->base + TX_ANA_CTRL_REG_3);

	tx_ana_ctrl_reg_1 |= TXDA_UPHY_SUPPLY_EN;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
	udelay(1);
	tx_ana_ctrl_reg_1 |= TXDA_UPHY_SUPPLY_EN_DEL;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);

	ग_लिखोl(0, tcphy->base + TX_ANA_CTRL_REG_5);

	/*
	 * Programs txda_drv_lकरो_prog[15:0], Sets driver LDO
	 * voltage 16'h1001 क्रम DP-AUX-TX and RX
	 */
	ग_लिखोl(0x1001, tcphy->base + TX_ANA_CTRL_REG_4);

	/* re-enables Bandgap reference क्रम LDO */
	tx_ana_ctrl_reg_1 |= TXDA_DRV_LDO_EN;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
	udelay(5);
	tx_ana_ctrl_reg_1 |= TXDA_BGREF_EN;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);

	/*
	 * re-enables the transmitter pre-driver, driver data selection MUX,
	 * and receiver detect circuits.
	 */
	tx_ana_ctrl_reg_2 |= TXDA_DRV_PREDRV_EN;
	ग_लिखोl(tx_ana_ctrl_reg_2, tcphy->base + TX_ANA_CTRL_REG_2);
	udelay(1);
	tx_ana_ctrl_reg_2 |= TXDA_DRV_PREDRV_EN_DEL;
	ग_लिखोl(tx_ana_ctrl_reg_2, tcphy->base + TX_ANA_CTRL_REG_2);

	/*
	 * Do all the unकरोcumented magic:
	 * - Turn on TXDA_DP_AUX_EN, whatever that is, even though sample
	 *   never shows this going on.
	 * - Turn on TXDA_DECAP_EN (and TXDA_DECAP_EN_DEL) even though
	 *   करोcs say क्रम aux it's always 0.
	 * - Turn off the LDO and BGREF, which we just spent समय turning
	 *   on above (???).
	 *
	 * Without this magic, things seem worse.
	 */
	tx_ana_ctrl_reg_1 |= TXDA_DP_AUX_EN;
	tx_ana_ctrl_reg_1 |= TXDA_DECAP_EN;
	tx_ana_ctrl_reg_1 &= ~TXDA_DRV_LDO_EN;
	tx_ana_ctrl_reg_1 &= ~TXDA_BGREF_EN;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
	udelay(1);
	tx_ana_ctrl_reg_1 |= TXDA_DECAP_EN_DEL;
	ग_लिखोl(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);

	/*
	 * Unकरो the work we did to set the LDO voltage.
	 * This करोesn't seem to help nor hurt, but it kinda goes with the
	 * unकरोcumented magic above.
	 */
	ग_लिखोl(0, tcphy->base + TX_ANA_CTRL_REG_4);

	/* Don't set voltage swing to 400 mV peak to peak (dअगरferential) */
	ग_लिखोl(0, tcphy->base + TXDA_COEFF_CALC_CTRL);

	/* Init TXDA_CYA_AUXDA_CYA क्रम unknown magic reasons */
	ग_लिखोl(0, tcphy->base + TXDA_CYA_AUXDA_CYA);

	/*
	 * More unकरोcumented magic, presumably the goal of which is to
	 * make the "auxda_source_aux_oen" be ignored and instead to decide
	 * about "high impedance state" based on what software माला_दो in the
	 * रेजिस्टर TXDA_COEFF_CALC_CTRL (see TX_HIGH_Z).  Since we only
	 * program that रेजिस्टर once and we करोn't set the bit TX_HIGH_Z,
	 * presumably the goal here is that we should never put the analog
	 * driver in high impedance state.
	 */
	val = पढ़ोl(tcphy->base + TX_DIG_CTRL_REG_2);
	val |= TX_HIGH_Z_TM_EN;
	ग_लिखोl(val, tcphy->base + TX_DIG_CTRL_REG_2);
पूर्ण

अटल पूर्णांक tcphy_phy_init(काष्ठा rockchip_typec_phy *tcphy, u8 mode)
अणु
	स्थिर काष्ठा rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;
	पूर्णांक ret, i;
	u32 val;

	ret = clk_prepare_enable(tcphy->clk_core);
	अगर (ret) अणु
		dev_err(tcphy->dev, "Failed to prepare_enable core clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(tcphy->clk_ref);
	अगर (ret) अणु
		dev_err(tcphy->dev, "Failed to prepare_enable ref clock\n");
		जाओ err_clk_core;
	पूर्ण

	reset_control_deनिश्चित(tcphy->tcphy_rst);

	property_enable(tcphy, &cfg->typec_conn_dir, tcphy->flip);
	tcphy_dp_aux_set_flip(tcphy);

	tcphy_cfg_24m(tcphy);

	अगर (mode == MODE_DFP_DP) अणु
		tcphy_cfg_dp_pll(tcphy);
		क्रम (i = 0; i < 4; i++)
			tcphy_dp_cfg_lane(tcphy, i);

		ग_लिखोl(PIN_ASSIGN_C_E, tcphy->base + PMA_LANE_CFG);
	पूर्ण अन्यथा अणु
		tcphy_cfg_usb3_pll(tcphy);
		tcphy_cfg_dp_pll(tcphy);
		अगर (tcphy->flip) अणु
			tcphy_tx_usb3_cfg_lane(tcphy, 3);
			tcphy_rx_usb3_cfg_lane(tcphy, 2);
			tcphy_dp_cfg_lane(tcphy, 0);
			tcphy_dp_cfg_lane(tcphy, 1);
		पूर्ण अन्यथा अणु
			tcphy_tx_usb3_cfg_lane(tcphy, 0);
			tcphy_rx_usb3_cfg_lane(tcphy, 1);
			tcphy_dp_cfg_lane(tcphy, 2);
			tcphy_dp_cfg_lane(tcphy, 3);
		पूर्ण

		ग_लिखोl(PIN_ASSIGN_D_F, tcphy->base + PMA_LANE_CFG);
	पूर्ण

	ग_लिखोl(DP_MODE_ENTER_A2, tcphy->base + DP_MODE_CTL);

	reset_control_deनिश्चित(tcphy->uphy_rst);

	ret = पढ़ोx_poll_समयout(पढ़ोl, tcphy->base + PMA_CMN_CTRL1,
				 val, val & CMN_READY, 10,
				 PHY_MODE_SET_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(tcphy->dev, "wait pma ready timeout\n");
		ret = -ETIMEDOUT;
		जाओ err_रुको_pma;
	पूर्ण

	reset_control_deनिश्चित(tcphy->pipe_rst);

	वापस 0;

err_रुको_pma:
	reset_control_निश्चित(tcphy->uphy_rst);
	reset_control_निश्चित(tcphy->tcphy_rst);
	clk_disable_unprepare(tcphy->clk_ref);
err_clk_core:
	clk_disable_unprepare(tcphy->clk_core);
	वापस ret;
पूर्ण

अटल व्योम tcphy_phy_deinit(काष्ठा rockchip_typec_phy *tcphy)
अणु
	reset_control_निश्चित(tcphy->tcphy_rst);
	reset_control_निश्चित(tcphy->uphy_rst);
	reset_control_निश्चित(tcphy->pipe_rst);
	clk_disable_unprepare(tcphy->clk_core);
	clk_disable_unprepare(tcphy->clk_ref);
पूर्ण

अटल पूर्णांक tcphy_get_mode(काष्ठा rockchip_typec_phy *tcphy)
अणु
	काष्ठा extcon_dev *edev = tcphy->extcon;
	जोड़ extcon_property_value property;
	अचिन्हित पूर्णांक id;
	bool ufp, dp;
	u8 mode;
	पूर्णांक ret;

	अगर (!edev)
		वापस MODE_DFP_USB;

	ufp = extcon_get_state(edev, EXTCON_USB);
	dp = extcon_get_state(edev, EXTCON_DISP_DP);

	mode = MODE_DFP_USB;
	id = EXTCON_USB_HOST;

	अगर (ufp) अणु
		mode = MODE_UFP_USB;
		id = EXTCON_USB;
	पूर्ण अन्यथा अगर (dp) अणु
		mode = MODE_DFP_DP;
		id = EXTCON_DISP_DP;

		ret = extcon_get_property(edev, id, EXTCON_PROP_USB_SS,
					  &property);
		अगर (ret) अणु
			dev_err(tcphy->dev, "get superspeed property failed\n");
			वापस ret;
		पूर्ण

		अगर (property.पूर्णांकval)
			mode |= MODE_DFP_USB;
	पूर्ण

	ret = extcon_get_property(edev, id, EXTCON_PROP_USB_TYPEC_POLARITY,
				  &property);
	अगर (ret) अणु
		dev_err(tcphy->dev, "get polarity property failed\n");
		वापस ret;
	पूर्ण

	tcphy->flip = property.पूर्णांकval ? 1 : 0;

	वापस mode;
पूर्ण

अटल पूर्णांक tcphy_cfg_usb3_to_usb2_only(काष्ठा rockchip_typec_phy *tcphy,
				       bool value)
अणु
	स्थिर काष्ठा rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;

	property_enable(tcphy, &cfg->usb3tousb2_en, value);
	property_enable(tcphy, &cfg->usb3_host_disable, value);
	property_enable(tcphy, &cfg->usb3_host_port, !value);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_usb3_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_typec_phy *tcphy = phy_get_drvdata(phy);
	स्थिर काष्ठा rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;
	स्थिर काष्ठा usb3phy_reg *reg = &cfg->pipe_status;
	पूर्णांक समयout, new_mode, ret = 0;
	u32 val;

	mutex_lock(&tcphy->lock);

	new_mode = tcphy_get_mode(tcphy);
	अगर (new_mode < 0) अणु
		ret = new_mode;
		जाओ unlock_ret;
	पूर्ण

	/* DP-only mode; fall back to USB2 */
	अगर (!(new_mode & (MODE_DFP_USB | MODE_UFP_USB))) अणु
		tcphy_cfg_usb3_to_usb2_only(tcphy, true);
		जाओ unlock_ret;
	पूर्ण

	अगर (tcphy->mode == new_mode)
		जाओ unlock_ret;

	अगर (tcphy->mode == MODE_DISCONNECT) अणु
		ret = tcphy_phy_init(tcphy, new_mode);
		अगर (ret)
			जाओ unlock_ret;
	पूर्ण

	/* रुको TCPHY क्रम pipe पढ़ोy */
	क्रम (समयout = 0; समयout < 100; समयout++) अणु
		regmap_पढ़ो(tcphy->grf_regs, reg->offset, &val);
		अगर (!(val & BIT(reg->enable_bit))) अणु
			tcphy->mode |= new_mode & (MODE_DFP_USB | MODE_UFP_USB);

			/* enable usb3 host */
			tcphy_cfg_usb3_to_usb2_only(tcphy, false);
			जाओ unlock_ret;
		पूर्ण
		usleep_range(10, 20);
	पूर्ण

	अगर (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);

	ret = -ETIMEDOUT;

unlock_ret:
	mutex_unlock(&tcphy->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_usb3_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_typec_phy *tcphy = phy_get_drvdata(phy);

	mutex_lock(&tcphy->lock);
	tcphy_cfg_usb3_to_usb2_only(tcphy, false);

	अगर (tcphy->mode == MODE_DISCONNECT)
		जाओ unlock;

	tcphy->mode &= ~(MODE_UFP_USB | MODE_DFP_USB);
	अगर (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);

unlock:
	mutex_unlock(&tcphy->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops rockchip_usb3_phy_ops = अणु
	.घातer_on	= rockchip_usb3_phy_घातer_on,
	.घातer_off	= rockchip_usb3_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक rockchip_dp_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_typec_phy *tcphy = phy_get_drvdata(phy);
	स्थिर काष्ठा rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;
	पूर्णांक new_mode, ret = 0;
	u32 val;

	mutex_lock(&tcphy->lock);

	new_mode = tcphy_get_mode(tcphy);
	अगर (new_mode < 0) अणु
		ret = new_mode;
		जाओ unlock_ret;
	पूर्ण

	अगर (!(new_mode & MODE_DFP_DP)) अणु
		ret = -ENODEV;
		जाओ unlock_ret;
	पूर्ण

	अगर (tcphy->mode == new_mode)
		जाओ unlock_ret;

	/*
	 * If the PHY has been घातer on, but the mode is not DP only mode,
	 * re-init the PHY क्रम setting all of 4 lanes to DP.
	 */
	अगर (new_mode == MODE_DFP_DP && tcphy->mode != MODE_DISCONNECT) अणु
		tcphy_phy_deinit(tcphy);
		ret = tcphy_phy_init(tcphy, new_mode);
	पूर्ण अन्यथा अगर (tcphy->mode == MODE_DISCONNECT) अणु
		ret = tcphy_phy_init(tcphy, new_mode);
	पूर्ण
	अगर (ret)
		जाओ unlock_ret;

	property_enable(tcphy, &cfg->uphy_dp_sel, 1);

	ret = पढ़ोx_poll_समयout(पढ़ोl, tcphy->base + DP_MODE_CTL,
				 val, val & DP_MODE_A2, 1000,
				 PHY_MODE_SET_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(tcphy->dev, "failed to wait TCPHY enter A2\n");
		जाओ घातer_on_finish;
	पूर्ण

	tcphy_dp_aux_calibration(tcphy);

	ग_लिखोl(DP_MODE_ENTER_A0, tcphy->base + DP_MODE_CTL);

	ret = पढ़ोx_poll_समयout(पढ़ोl, tcphy->base + DP_MODE_CTL,
				 val, val & DP_MODE_A0, 1000,
				 PHY_MODE_SET_TIMEOUT);
	अगर (ret < 0) अणु
		ग_लिखोl(DP_MODE_ENTER_A2, tcphy->base + DP_MODE_CTL);
		dev_err(tcphy->dev, "failed to wait TCPHY enter A0\n");
		जाओ घातer_on_finish;
	पूर्ण

	tcphy->mode |= MODE_DFP_DP;

घातer_on_finish:
	अगर (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);
unlock_ret:
	mutex_unlock(&tcphy->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_dp_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_typec_phy *tcphy = phy_get_drvdata(phy);

	mutex_lock(&tcphy->lock);

	अगर (tcphy->mode == MODE_DISCONNECT)
		जाओ unlock;

	tcphy->mode &= ~MODE_DFP_DP;

	ग_लिखोl(DP_MODE_ENTER_A2, tcphy->base + DP_MODE_CTL);

	अगर (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);

unlock:
	mutex_unlock(&tcphy->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops rockchip_dp_phy_ops = अणु
	.घातer_on	= rockchip_dp_phy_घातer_on,
	.घातer_off	= rockchip_dp_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक tcphy_parse_dt(काष्ठा rockchip_typec_phy *tcphy,
			  काष्ठा device *dev)
अणु
	tcphy->grf_regs = syscon_regmap_lookup_by_phandle(dev->of_node,
							  "rockchip,grf");
	अगर (IS_ERR(tcphy->grf_regs)) अणु
		dev_err(dev, "could not find grf dt node\n");
		वापस PTR_ERR(tcphy->grf_regs);
	पूर्ण

	tcphy->clk_core = devm_clk_get(dev, "tcpdcore");
	अगर (IS_ERR(tcphy->clk_core)) अणु
		dev_err(dev, "could not get uphy core clock\n");
		वापस PTR_ERR(tcphy->clk_core);
	पूर्ण

	tcphy->clk_ref = devm_clk_get(dev, "tcpdphy-ref");
	अगर (IS_ERR(tcphy->clk_ref)) अणु
		dev_err(dev, "could not get uphy ref clock\n");
		वापस PTR_ERR(tcphy->clk_ref);
	पूर्ण

	tcphy->uphy_rst = devm_reset_control_get(dev, "uphy");
	अगर (IS_ERR(tcphy->uphy_rst)) अणु
		dev_err(dev, "no uphy_rst reset control found\n");
		वापस PTR_ERR(tcphy->uphy_rst);
	पूर्ण

	tcphy->pipe_rst = devm_reset_control_get(dev, "uphy-pipe");
	अगर (IS_ERR(tcphy->pipe_rst)) अणु
		dev_err(dev, "no pipe_rst reset control found\n");
		वापस PTR_ERR(tcphy->pipe_rst);
	पूर्ण

	tcphy->tcphy_rst = devm_reset_control_get(dev, "uphy-tcphy");
	अगर (IS_ERR(tcphy->tcphy_rst)) अणु
		dev_err(dev, "no tcphy_rst reset control found\n");
		वापस PTR_ERR(tcphy->tcphy_rst);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम typec_phy_pre_init(काष्ठा rockchip_typec_phy *tcphy)
अणु
	स्थिर काष्ठा rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;

	reset_control_निश्चित(tcphy->tcphy_rst);
	reset_control_निश्चित(tcphy->uphy_rst);
	reset_control_निश्चित(tcphy->pipe_rst);

	/* select बाह्यal psm घड़ी */
	property_enable(tcphy, &cfg->बाह्यal_psm, 1);
	property_enable(tcphy, &cfg->usb3tousb2_en, 0);

	tcphy->mode = MODE_DISCONNECT;
पूर्ण

अटल पूर्णांक rockchip_typec_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child_np;
	काष्ठा rockchip_typec_phy *tcphy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा resource *res;
	स्थिर काष्ठा rockchip_usb3phy_port_cfg *phy_cfgs;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक index, ret;

	tcphy = devm_kzalloc(dev, माप(*tcphy), GFP_KERNEL);
	अगर (!tcphy)
		वापस -ENOMEM;

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match || !match->data) अणु
		dev_err(dev, "phy configs are not assigned!\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tcphy->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(tcphy->base))
		वापस PTR_ERR(tcphy->base);

	phy_cfgs = match->data;
	/* find out a proper config which can be matched with dt. */
	index = 0;
	जबतक (phy_cfgs[index].reg) अणु
		अगर (phy_cfgs[index].reg == res->start) अणु
			tcphy->port_cfgs = &phy_cfgs[index];
			अवरोध;
		पूर्ण

		++index;
	पूर्ण

	अगर (!tcphy->port_cfgs) अणु
		dev_err(dev, "no phy-config can be matched with %pOFn node\n",
			np);
		वापस -EINVAL;
	पूर्ण

	ret = tcphy_parse_dt(tcphy, dev);
	अगर (ret)
		वापस ret;

	tcphy->dev = dev;
	platक्रमm_set_drvdata(pdev, tcphy);
	mutex_init(&tcphy->lock);

	typec_phy_pre_init(tcphy);

	tcphy->extcon = extcon_get_edev_by_phandle(dev, 0);
	अगर (IS_ERR(tcphy->extcon)) अणु
		अगर (PTR_ERR(tcphy->extcon) == -ENODEV) अणु
			tcphy->extcon = शून्य;
		पूर्ण अन्यथा अणु
			अगर (PTR_ERR(tcphy->extcon) != -EPROBE_DEFER)
				dev_err(dev, "Invalid or missing extcon\n");
			वापस PTR_ERR(tcphy->extcon);
		पूर्ण
	पूर्ण

	pm_runसमय_enable(dev);

	क्रम_each_available_child_of_node(np, child_np) अणु
		काष्ठा phy *phy;

		अगर (of_node_name_eq(child_np, "dp-port"))
			phy = devm_phy_create(dev, child_np,
					      &rockchip_dp_phy_ops);
		अन्यथा अगर (of_node_name_eq(child_np, "usb3-port"))
			phy = devm_phy_create(dev, child_np,
					      &rockchip_usb3_phy_ops);
		अन्यथा
			जारी;

		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "failed to create phy: %pOFn\n",
				child_np);
			pm_runसमय_disable(dev);
			of_node_put(child_np);
			वापस PTR_ERR(phy);
		पूर्ण

		phy_set_drvdata(phy, tcphy);
	पूर्ण

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		dev_err(dev, "Failed to register phy provider\n");
		pm_runसमय_disable(dev);
		वापस PTR_ERR(phy_provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_typec_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_typec_phy_dt_ids[] = अणु
	अणु
		.compatible = "rockchip,rk3399-typec-phy",
		.data = &rk3399_usb3phy_port_cfgs
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_typec_phy_dt_ids);

अटल काष्ठा platक्रमm_driver rockchip_typec_phy_driver = अणु
	.probe		= rockchip_typec_phy_probe,
	.हटाओ		= rockchip_typec_phy_हटाओ,
	.driver		= अणु
		.name	= "rockchip-typec-phy",
		.of_match_table = rockchip_typec_phy_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_typec_phy_driver);

MODULE_AUTHOR("Chris Zhong <zyw@rock-chips.com>");
MODULE_AUTHOR("Kever Yang <kever.yang@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip USB TYPE-C PHY driver");
MODULE_LICENSE("GPL v2");
