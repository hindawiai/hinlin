<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 NVIDIA Corporation
 */

#अगर_अघोषित DRM_TEGRA_SOR_H
#घोषणा DRM_TEGRA_SOR_H

#घोषणा SOR_CTXSW 0x00

#घोषणा SOR_SUPER_STATE0 0x01

#घोषणा SOR_SUPER_STATE1 0x02
#घोषणा  SOR_SUPER_STATE_ATTACHED		(1 << 3)
#घोषणा  SOR_SUPER_STATE_MODE_NORMAL		(1 << 2)
#घोषणा  SOR_SUPER_STATE_HEAD_MODE_MASK		(3 << 0)
#घोषणा  SOR_SUPER_STATE_HEAD_MODE_AWAKE	(2 << 0)
#घोषणा  SOR_SUPER_STATE_HEAD_MODE_SNOOZE	(1 << 0)
#घोषणा  SOR_SUPER_STATE_HEAD_MODE_SLEEP	(0 << 0)

#घोषणा SOR_STATE0 0x03

#घोषणा SOR_STATE1 0x04
#घोषणा  SOR_STATE_ASY_PIXELDEPTH_MASK		(0xf << 17)
#घोषणा  SOR_STATE_ASY_PIXELDEPTH_BPP_18_444	(0x2 << 17)
#घोषणा  SOR_STATE_ASY_PIXELDEPTH_BPP_24_444	(0x5 << 17)
#घोषणा  SOR_STATE_ASY_PIXELDEPTH_BPP_30_444	(0x6 << 17)
#घोषणा  SOR_STATE_ASY_PIXELDEPTH_BPP_36_444	(0x8 << 17)
#घोषणा  SOR_STATE_ASY_PIXELDEPTH_BPP_48_444	(0x9 << 17)
#घोषणा  SOR_STATE_ASY_VSYNCPOL			(1 << 13)
#घोषणा  SOR_STATE_ASY_HSYNCPOL			(1 << 12)
#घोषणा  SOR_STATE_ASY_PROTOCOL_MASK		(0xf << 8)
#घोषणा  SOR_STATE_ASY_PROTOCOL_CUSTOM		(0xf << 8)
#घोषणा  SOR_STATE_ASY_PROTOCOL_DP_A		(0x8 << 8)
#घोषणा  SOR_STATE_ASY_PROTOCOL_DP_B		(0x9 << 8)
#घोषणा  SOR_STATE_ASY_PROTOCOL_SINGLE_TMDS_A	(0x1 << 8)
#घोषणा  SOR_STATE_ASY_PROTOCOL_LVDS		(0x0 << 8)
#घोषणा  SOR_STATE_ASY_CRC_MODE_MASK		(0x3 << 6)
#घोषणा  SOR_STATE_ASY_CRC_MODE_NON_ACTIVE	(0x2 << 6)
#घोषणा  SOR_STATE_ASY_CRC_MODE_COMPLETE	(0x1 << 6)
#घोषणा  SOR_STATE_ASY_CRC_MODE_ACTIVE		(0x0 << 6)
#घोषणा  SOR_STATE_ASY_SUBOWNER_MASK		(0x3 << 4)
#घोषणा  SOR_STATE_ASY_OWNER_MASK		0xf
#घोषणा  SOR_STATE_ASY_OWNER(x)			(((x) & 0xf) << 0)

#घोषणा SOR_HEAD_STATE0(x) (0x05 + (x))
#घोषणा  SOR_HEAD_STATE_RANGECOMPRESS_MASK (0x1 << 3)
#घोषणा  SOR_HEAD_STATE_DYNRANGE_MASK (0x1 << 2)
#घोषणा  SOR_HEAD_STATE_DYNRANGE_VESA (0 << 2)
#घोषणा  SOR_HEAD_STATE_DYNRANGE_CEA (1 << 2)
#घोषणा  SOR_HEAD_STATE_COLORSPACE_MASK (0x3 << 0)
#घोषणा  SOR_HEAD_STATE_COLORSPACE_RGB (0 << 0)
#घोषणा SOR_HEAD_STATE1(x) (0x07 + (x))
#घोषणा SOR_HEAD_STATE2(x) (0x09 + (x))
#घोषणा SOR_HEAD_STATE3(x) (0x0b + (x))
#घोषणा SOR_HEAD_STATE4(x) (0x0d + (x))
#घोषणा SOR_HEAD_STATE5(x) (0x0f + (x))
#घोषणा SOR_CRC_CNTRL 0x11
#घोषणा  SOR_CRC_CNTRL_ENABLE			(1 << 0)
#घोषणा SOR_DP_DEBUG_MVID 0x12

#घोषणा SOR_CLK_CNTRL 0x13
#घोषणा  SOR_CLK_CNTRL_DP_LINK_SPEED_MASK	(0x1f << 2)
#घोषणा  SOR_CLK_CNTRL_DP_LINK_SPEED(x)		(((x) & 0x1f) << 2)
#घोषणा  SOR_CLK_CNTRL_DP_LINK_SPEED_G1_62	(0x06 << 2)
#घोषणा  SOR_CLK_CNTRL_DP_LINK_SPEED_G2_70	(0x0a << 2)
#घोषणा  SOR_CLK_CNTRL_DP_LINK_SPEED_G5_40	(0x14 << 2)
#घोषणा  SOR_CLK_CNTRL_DP_CLK_SEL_MASK		(3 << 0)
#घोषणा  SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK	(0 << 0)
#घोषणा  SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_PCLK	(1 << 0)
#घोषणा  SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK	(2 << 0)
#घोषणा  SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_DPCLK	(3 << 0)

#घोषणा SOR_CAP 0x14

#घोषणा SOR_PWR 0x15
#घोषणा  SOR_PWR_TRIGGER			(1 << 31)
#घोषणा  SOR_PWR_MODE_SAFE			(1 << 28)
#घोषणा  SOR_PWR_NORMAL_STATE_PU		(1 << 0)

#घोषणा SOR_TEST 0x16
#घोषणा  SOR_TEST_CRC_POST_SERIALIZE		(1 << 23)
#घोषणा  SOR_TEST_ATTACHED			(1 << 10)
#घोषणा  SOR_TEST_HEAD_MODE_MASK		(3 << 8)
#घोषणा  SOR_TEST_HEAD_MODE_AWAKE		(2 << 8)

#घोषणा SOR_PLL0 0x17
#घोषणा  SOR_PLL0_ICHPMP_MASK			(0xf << 24)
#घोषणा  SOR_PLL0_ICHPMP(x)			(((x) & 0xf) << 24)
#घोषणा  SOR_PLL0_FILTER_MASK			(0xf << 16)
#घोषणा  SOR_PLL0_FILTER(x)			(((x) & 0xf) << 16)
#घोषणा  SOR_PLL0_VCOCAP_MASK			(0xf << 8)
#घोषणा  SOR_PLL0_VCOCAP(x)			(((x) & 0xf) << 8)
#घोषणा  SOR_PLL0_VCOCAP_RST			SOR_PLL0_VCOCAP(3)
#घोषणा  SOR_PLL0_PLLREG_MASK			(0x3 << 6)
#घोषणा  SOR_PLL0_PLLREG_LEVEL(x)		(((x) & 0x3) << 6)
#घोषणा  SOR_PLL0_PLLREG_LEVEL_V25		SOR_PLL0_PLLREG_LEVEL(0)
#घोषणा  SOR_PLL0_PLLREG_LEVEL_V15		SOR_PLL0_PLLREG_LEVEL(1)
#घोषणा  SOR_PLL0_PLLREG_LEVEL_V35		SOR_PLL0_PLLREG_LEVEL(2)
#घोषणा  SOR_PLL0_PLLREG_LEVEL_V45		SOR_PLL0_PLLREG_LEVEL(3)
#घोषणा  SOR_PLL0_PULLDOWN			(1 << 5)
#घोषणा  SOR_PLL0_RESISTOR_EXT			(1 << 4)
#घोषणा  SOR_PLL0_VCOPD				(1 << 2)
#घोषणा  SOR_PLL0_PWR				(1 << 0)

#घोषणा SOR_PLL1 0x18
/* XXX: पढ़ो-only bit? */
#घोषणा  SOR_PLL1_LOADADJ_MASK			(0xf << 20)
#घोषणा  SOR_PLL1_LOADADJ(x)			(((x) & 0xf) << 20)
#घोषणा  SOR_PLL1_TERM_COMPOUT			(1 << 15)
#घोषणा  SOR_PLL1_TMDS_TERMADJ_MASK		(0xf << 9)
#घोषणा  SOR_PLL1_TMDS_TERMADJ(x)		(((x) & 0xf) << 9)
#घोषणा  SOR_PLL1_TMDS_TERM			(1 << 8)

#घोषणा SOR_PLL2 0x19
#घोषणा  SOR_PLL2_LVDS_ENABLE			(1 << 25)
#घोषणा  SOR_PLL2_SEQ_PLLCAPPD_ENFORCE		(1 << 24)
#घोषणा  SOR_PLL2_PORT_POWERDOWN		(1 << 23)
#घोषणा  SOR_PLL2_BANDGAP_POWERDOWN		(1 << 22)
#घोषणा  SOR_PLL2_POWERDOWN_OVERRIDE		(1 << 18)
#घोषणा  SOR_PLL2_SEQ_PLLCAPPD			(1 << 17)
#घोषणा  SOR_PLL2_SEQ_PLL_PULLDOWN		(1 << 16)

#घोषणा SOR_PLL3 0x1a
#घोषणा  SOR_PLL3_BG_TEMP_COEF_MASK		(0xf << 28)
#घोषणा  SOR_PLL3_BG_TEMP_COEF(x)		(((x) & 0xf) << 28)
#घोषणा  SOR_PLL3_BG_VREF_LEVEL_MASK		(0xf << 24)
#घोषणा  SOR_PLL3_BG_VREF_LEVEL(x)		(((x) & 0xf) << 24)
#घोषणा  SOR_PLL3_PLL_VDD_MODE_1V8		(0 << 13)
#घोषणा  SOR_PLL3_PLL_VDD_MODE_3V3		(1 << 13)
#घोषणा  SOR_PLL3_AVDD10_LEVEL_MASK		(0xf << 8)
#घोषणा  SOR_PLL3_AVDD10_LEVEL(x)		(((x) & 0xf) << 8)
#घोषणा  SOR_PLL3_AVDD14_LEVEL_MASK		(0xf << 4)
#घोषणा  SOR_PLL3_AVDD14_LEVEL(x)		(((x) & 0xf) << 4)

#घोषणा SOR_CSTM 0x1b
#घोषणा  SOR_CSTM_ROTCLK_MASK			(0xf << 24)
#घोषणा  SOR_CSTM_ROTCLK(x)			(((x) & 0xf) << 24)
#घोषणा  SOR_CSTM_LVDS				(1 << 16)
#घोषणा  SOR_CSTM_LINK_ACT_B			(1 << 15)
#घोषणा  SOR_CSTM_LINK_ACT_A			(1 << 14)
#घोषणा  SOR_CSTM_UPPER				(1 << 11)

#घोषणा SOR_LVDS 0x1c
#घोषणा SOR_CRCA 0x1d
#घोषणा  SOR_CRCA_VALID			(1 << 0)
#घोषणा  SOR_CRCA_RESET			(1 << 0)
#घोषणा SOR_CRCB 0x1e
#घोषणा SOR_BLANK 0x1f
#घोषणा SOR_SEQ_CTL 0x20
#घोषणा  SOR_SEQ_CTL_PD_PC_ALT(x)	(((x) & 0xf) << 12)
#घोषणा  SOR_SEQ_CTL_PD_PC(x)		(((x) & 0xf) <<  8)
#घोषणा  SOR_SEQ_CTL_PU_PC_ALT(x)	(((x) & 0xf) <<  4)
#घोषणा  SOR_SEQ_CTL_PU_PC(x)		(((x) & 0xf) <<  0)

#घोषणा SOR_LANE_SEQ_CTL 0x21
#घोषणा  SOR_LANE_SEQ_CTL_TRIGGER		(1 << 31)
#घोषणा  SOR_LANE_SEQ_CTL_STATE_BUSY		(1 << 28)
#घोषणा  SOR_LANE_SEQ_CTL_SEQUENCE_UP		(0 << 20)
#घोषणा  SOR_LANE_SEQ_CTL_SEQUENCE_DOWN		(1 << 20)
#घोषणा  SOR_LANE_SEQ_CTL_POWER_STATE_UP	(0 << 16)
#घोषणा  SOR_LANE_SEQ_CTL_POWER_STATE_DOWN	(1 << 16)
#घोषणा  SOR_LANE_SEQ_CTL_DELAY(x)		(((x) & 0xf) << 12)

#घोषणा SOR_SEQ_INST(x) (0x22 + (x))
#घोषणा  SOR_SEQ_INST_PLL_PULLDOWN (1 << 31)
#घोषणा  SOR_SEQ_INST_POWERDOWN_MACRO (1 << 30)
#घोषणा  SOR_SEQ_INST_ASSERT_PLL_RESET (1 << 29)
#घोषणा  SOR_SEQ_INST_BLANK_V (1 << 28)
#घोषणा  SOR_SEQ_INST_BLANK_H (1 << 27)
#घोषणा  SOR_SEQ_INST_BLANK_DE (1 << 26)
#घोषणा  SOR_SEQ_INST_BLACK_DATA (1 << 25)
#घोषणा  SOR_SEQ_INST_TRISTATE_IOS (1 << 24)
#घोषणा  SOR_SEQ_INST_DRIVE_PWM_OUT_LO (1 << 23)
#घोषणा  SOR_SEQ_INST_PIN_B_LOW (0 << 22)
#घोषणा  SOR_SEQ_INST_PIN_B_HIGH (1 << 22)
#घोषणा  SOR_SEQ_INST_PIN_A_LOW (0 << 21)
#घोषणा  SOR_SEQ_INST_PIN_A_HIGH (1 << 21)
#घोषणा  SOR_SEQ_INST_SEQUENCE_UP (0 << 19)
#घोषणा  SOR_SEQ_INST_SEQUENCE_DOWN (1 << 19)
#घोषणा  SOR_SEQ_INST_LANE_SEQ_STOP (0 << 18)
#घोषणा  SOR_SEQ_INST_LANE_SEQ_RUN (1 << 18)
#घोषणा  SOR_SEQ_INST_PORT_POWERDOWN (1 << 17)
#घोषणा  SOR_SEQ_INST_PLL_POWERDOWN (1 << 16)
#घोषणा  SOR_SEQ_INST_HALT (1 << 15)
#घोषणा  SOR_SEQ_INST_WAIT_US (0 << 12)
#घोषणा  SOR_SEQ_INST_WAIT_MS (1 << 12)
#घोषणा  SOR_SEQ_INST_WAIT_VSYNC (2 << 12)
#घोषणा  SOR_SEQ_INST_WAIT(x) (((x) & 0x3ff) << 0)

#घोषणा SOR_PWM_DIV 0x32
#घोषणा  SOR_PWM_DIV_MASK			0xffffff

#घोषणा SOR_PWM_CTL 0x33
#घोषणा  SOR_PWM_CTL_TRIGGER			(1 << 31)
#घोषणा  SOR_PWM_CTL_CLK_SEL			(1 << 30)
#घोषणा  SOR_PWM_CTL_DUTY_CYCLE_MASK		0xffffff

#घोषणा SOR_VCRC_A0 0x34
#घोषणा SOR_VCRC_A1 0x35
#घोषणा SOR_VCRC_B0 0x36
#घोषणा SOR_VCRC_B1 0x37
#घोषणा SOR_CCRC_A0 0x38
#घोषणा SOR_CCRC_A1 0x39
#घोषणा SOR_CCRC_B0 0x3a
#घोषणा SOR_CCRC_B1 0x3b
#घोषणा SOR_EDATA_A0 0x3c
#घोषणा SOR_EDATA_A1 0x3d
#घोषणा SOR_EDATA_B0 0x3e
#घोषणा SOR_EDATA_B1 0x3f
#घोषणा SOR_COUNT_A0 0x40
#घोषणा SOR_COUNT_A1 0x41
#घोषणा SOR_COUNT_B0 0x42
#घोषणा SOR_COUNT_B1 0x43
#घोषणा SOR_DEBUG_A0 0x44
#घोषणा SOR_DEBUG_A1 0x45
#घोषणा SOR_DEBUG_B0 0x46
#घोषणा SOR_DEBUG_B1 0x47
#घोषणा SOR_TRIG 0x48
#घोषणा SOR_MSCHECK 0x49
#घोषणा SOR_XBAR_CTRL 0x4a
#घोषणा  SOR_XBAR_CTRL_LINK1_XSEL(channel, value) ((((value) & 0x7) << ((channel) * 3)) << 17)
#घोषणा  SOR_XBAR_CTRL_LINK0_XSEL(channel, value) ((((value) & 0x7) << ((channel) * 3)) <<  2)
#घोषणा  SOR_XBAR_CTRL_LINK_SWAP (1 << 1)
#घोषणा  SOR_XBAR_CTRL_BYPASS (1 << 0)
#घोषणा SOR_XBAR_POL 0x4b

#घोषणा SOR_DP_LINKCTL0 0x4c
#घोषणा  SOR_DP_LINKCTL_LANE_COUNT_MASK		(0x1f << 16)
#घोषणा  SOR_DP_LINKCTL_LANE_COUNT(x)		(((1 << (x)) - 1) << 16)
#घोषणा  SOR_DP_LINKCTL_ENHANCED_FRAME		(1 << 14)
#घोषणा  SOR_DP_LINKCTL_TU_SIZE_MASK		(0x7f << 2)
#घोषणा  SOR_DP_LINKCTL_TU_SIZE(x)		(((x) & 0x7f) << 2)
#घोषणा  SOR_DP_LINKCTL_ENABLE			(1 << 0)

#घोषणा SOR_DP_LINKCTL1 0x4d

#घोषणा SOR_LANE_DRIVE_CURRENT0 0x4e
#घोषणा SOR_LANE_DRIVE_CURRENT1 0x4f
#घोषणा SOR_LANE4_DRIVE_CURRENT0 0x50
#घोषणा SOR_LANE4_DRIVE_CURRENT1 0x51
#घोषणा  SOR_LANE_DRIVE_CURRENT_LANE3(x) (((x) & 0xff) << 24)
#घोषणा  SOR_LANE_DRIVE_CURRENT_LANE2(x) (((x) & 0xff) << 16)
#घोषणा  SOR_LANE_DRIVE_CURRENT_LANE1(x) (((x) & 0xff) << 8)
#घोषणा  SOR_LANE_DRIVE_CURRENT_LANE0(x) (((x) & 0xff) << 0)

#घोषणा SOR_LANE_PREEMPHASIS0 0x52
#घोषणा SOR_LANE_PREEMPHASIS1 0x53
#घोषणा SOR_LANE4_PREEMPHASIS0 0x54
#घोषणा SOR_LANE4_PREEMPHASIS1 0x55
#घोषणा  SOR_LANE_PREEMPHASIS_LANE3(x) (((x) & 0xff) << 24)
#घोषणा  SOR_LANE_PREEMPHASIS_LANE2(x) (((x) & 0xff) << 16)
#घोषणा  SOR_LANE_PREEMPHASIS_LANE1(x) (((x) & 0xff) << 8)
#घोषणा  SOR_LANE_PREEMPHASIS_LANE0(x) (((x) & 0xff) << 0)

#घोषणा SOR_LANE_POSTCURSOR0 0x56
#घोषणा SOR_LANE_POSTCURSOR1 0x57
#घोषणा  SOR_LANE_POSTCURSOR_LANE3(x) (((x) & 0xff) << 24)
#घोषणा  SOR_LANE_POSTCURSOR_LANE2(x) (((x) & 0xff) << 16)
#घोषणा  SOR_LANE_POSTCURSOR_LANE1(x) (((x) & 0xff) << 8)
#घोषणा  SOR_LANE_POSTCURSOR_LANE0(x) (((x) & 0xff) << 0)

#घोषणा SOR_DP_CONFIG0 0x58
#घोषणा SOR_DP_CONFIG_DISPARITY_NEGATIVE	(1 << 31)
#घोषणा SOR_DP_CONFIG_ACTIVE_SYM_ENABLE		(1 << 26)
#घोषणा SOR_DP_CONFIG_ACTIVE_SYM_POLARITY	(1 << 24)
#घोषणा SOR_DP_CONFIG_ACTIVE_SYM_FRAC_MASK	(0xf << 16)
#घोषणा SOR_DP_CONFIG_ACTIVE_SYM_FRAC(x)	(((x) & 0xf) << 16)
#घोषणा SOR_DP_CONFIG_ACTIVE_SYM_COUNT_MASK	(0x7f << 8)
#घोषणा SOR_DP_CONFIG_ACTIVE_SYM_COUNT(x)	(((x) & 0x7f) << 8)
#घोषणा SOR_DP_CONFIG_WATERMARK_MASK	(0x3f << 0)
#घोषणा SOR_DP_CONFIG_WATERMARK(x)	(((x) & 0x3f) << 0)

#घोषणा SOR_DP_CONFIG1 0x59
#घोषणा SOR_DP_MN0 0x5a
#घोषणा SOR_DP_MN1 0x5b

#घोषणा SOR_DP_PADCTL0 0x5c
#घोषणा  SOR_DP_PADCTL_PAD_CAL_PD	(1 << 23)
#घोषणा  SOR_DP_PADCTL_TX_PU_ENABLE	(1 << 22)
#घोषणा  SOR_DP_PADCTL_TX_PU_MASK	(0xff << 8)
#घोषणा  SOR_DP_PADCTL_TX_PU(x)		(((x) & 0xff) << 8)
#घोषणा  SOR_DP_PADCTL_CM_TXD_3		(1 << 7)
#घोषणा  SOR_DP_PADCTL_CM_TXD_2		(1 << 6)
#घोषणा  SOR_DP_PADCTL_CM_TXD_1		(1 << 5)
#घोषणा  SOR_DP_PADCTL_CM_TXD_0		(1 << 4)
#घोषणा  SOR_DP_PADCTL_CM_TXD(x)	(1 << (4 + (x)))
#घोषणा  SOR_DP_PADCTL_PD_TXD_3		(1 << 3)
#घोषणा  SOR_DP_PADCTL_PD_TXD_0		(1 << 2)
#घोषणा  SOR_DP_PADCTL_PD_TXD_1		(1 << 1)
#घोषणा  SOR_DP_PADCTL_PD_TXD_2		(1 << 0)
#घोषणा  SOR_DP_PADCTL_PD_TXD(x)	(1 << (0 + (x)))

#घोषणा SOR_DP_PADCTL1 0x5d

#घोषणा SOR_DP_DEBUG0 0x5e
#घोषणा SOR_DP_DEBUG1 0x5f

#घोषणा SOR_DP_SPARE0 0x60
#घोषणा  SOR_DP_SPARE_DISP_VIDEO_PREAMBLE	(1 << 3)
#घोषणा  SOR_DP_SPARE_MACRO_SOR_CLK		(1 << 2)
#घोषणा  SOR_DP_SPARE_PANEL_INTERNAL		(1 << 1)
#घोषणा  SOR_DP_SPARE_SEQ_ENABLE		(1 << 0)

#घोषणा SOR_DP_SPARE1 0x61
#घोषणा SOR_DP_AUDIO_CTRL 0x62

#घोषणा SOR_DP_AUDIO_HBLANK_SYMBOLS 0x63
#घोषणा SOR_DP_AUDIO_HBLANK_SYMBOLS_MASK (0x01ffff << 0)

#घोषणा SOR_DP_AUDIO_VBLANK_SYMBOLS 0x64
#घोषणा SOR_DP_AUDIO_VBLANK_SYMBOLS_MASK (0x1fffff << 0)

#घोषणा SOR_DP_GENERIC_INFOFRAME_HEADER 0x65
#घोषणा SOR_DP_GENERIC_INFOFRAME_SUBPACK0 0x66
#घोषणा SOR_DP_GENERIC_INFOFRAME_SUBPACK1 0x67
#घोषणा SOR_DP_GENERIC_INFOFRAME_SUBPACK2 0x68
#घोषणा SOR_DP_GENERIC_INFOFRAME_SUBPACK3 0x69
#घोषणा SOR_DP_GENERIC_INFOFRAME_SUBPACK4 0x6a
#घोषणा SOR_DP_GENERIC_INFOFRAME_SUBPACK5 0x6b
#घोषणा SOR_DP_GENERIC_INFOFRAME_SUBPACK6 0x6c

#घोषणा SOR_DP_TPG 0x6d
#घोषणा  SOR_DP_TPG_CHANNEL_CODING	(1 << 6)
#घोषणा  SOR_DP_TPG_SCRAMBLER_MASK	(3 << 4)
#घोषणा  SOR_DP_TPG_SCRAMBLER_FIBONACCI	(2 << 4)
#घोषणा  SOR_DP_TPG_SCRAMBLER_GALIOS	(1 << 4)
#घोषणा  SOR_DP_TPG_SCRAMBLER_NONE	(0 << 4)
#घोषणा  SOR_DP_TPG_PATTERN_MASK	(0xf << 0)
#घोषणा  SOR_DP_TPG_PATTERN_HBR2	(0x8 << 0)
#घोषणा  SOR_DP_TPG_PATTERN_CSTM	(0x7 << 0)
#घोषणा  SOR_DP_TPG_PATTERN_PRBS7	(0x6 << 0)
#घोषणा  SOR_DP_TPG_PATTERN_SBLERRRATE	(0x5 << 0)
#घोषणा  SOR_DP_TPG_PATTERN_D102	(0x4 << 0)
#घोषणा  SOR_DP_TPG_PATTERN_TRAIN3	(0x3 << 0)
#घोषणा  SOR_DP_TPG_PATTERN_TRAIN2	(0x2 << 0)
#घोषणा  SOR_DP_TPG_PATTERN_TRAIN1	(0x1 << 0)
#घोषणा  SOR_DP_TPG_PATTERN_NONE	(0x0 << 0)

#घोषणा SOR_DP_TPG_CONFIG 0x6e
#घोषणा SOR_DP_LQ_CSTM0 0x6f
#घोषणा SOR_DP_LQ_CSTM1 0x70
#घोषणा SOR_DP_LQ_CSTM2 0x71

#घोषणा SOR_DP_PADCTL2 0x73
#घोषणा  SOR_DP_PADCTL_SPAREPLL_MASK (0xff << 24)
#घोषणा  SOR_DP_PADCTL_SPAREPLL(x) (((x) & 0xff) << 24)

#घोषणा SOR_HDMI_AUDIO_INFOFRAME_CTRL 0x9a
#घोषणा SOR_HDMI_AUDIO_INFOFRAME_STATUS 0x9b
#घोषणा SOR_HDMI_AUDIO_INFOFRAME_HEADER 0x9c

#घोषणा SOR_HDMI_AVI_INFOFRAME_CTRL 0x9f
#घोषणा  INFOFRAME_CTRL_CHECKSUM_ENABLE	(1 << 9)
#घोषणा  INFOFRAME_CTRL_SINGLE		(1 << 8)
#घोषणा  INFOFRAME_CTRL_OTHER		(1 << 4)
#घोषणा  INFOFRAME_CTRL_ENABLE		(1 << 0)

#घोषणा SOR_HDMI_AVI_INFOFRAME_STATUS 0xa0
#घोषणा  INFOFRAME_STATUS_DONE		(1 << 0)

#घोषणा SOR_HDMI_AVI_INFOFRAME_HEADER 0xa1
#घोषणा  INFOFRAME_HEADER_LEN(x) (((x) & 0xff) << 16)
#घोषणा  INFOFRAME_HEADER_VERSION(x) (((x) & 0xff) << 8)
#घोषणा  INFOFRAME_HEADER_TYPE(x) (((x) & 0xff) << 0)

#घोषणा SOR_HDMI_ACR_CTRL 0xb1

#घोषणा SOR_HDMI_ACR_0320_SUBPACK_LOW 0xb2
#घोषणा  SOR_HDMI_ACR_SUBPACK_LOW_SB1(x) (((x) & 0xff) << 24)

#घोषणा SOR_HDMI_ACR_0320_SUBPACK_HIGH 0xb3
#घोषणा  SOR_HDMI_ACR_SUBPACK_HIGH_ENABLE (1 << 31)

#घोषणा SOR_HDMI_ACR_0441_SUBPACK_LOW 0xb4
#घोषणा SOR_HDMI_ACR_0441_SUBPACK_HIGH 0xb5

#घोषणा SOR_HDMI_CTRL 0xc0
#घोषणा  SOR_HDMI_CTRL_ENABLE (1 << 30)
#घोषणा  SOR_HDMI_CTRL_MAX_AC_PACKET(x) (((x) & 0x1f) << 16)
#घोषणा  SOR_HDMI_CTRL_AUDIO_LAYOUT (1 << 10)
#घोषणा  SOR_HDMI_CTRL_REKEY(x) (((x) & 0x7f) << 0)

#घोषणा SOR_HDMI_SPARE 0xcb
#घोषणा  SOR_HDMI_SPARE_ACR_PRIORITY_HIGH (1 << 31)
#घोषणा  SOR_HDMI_SPARE_CTS_RESET(x) (((x) & 0x7) << 16)
#घोषणा  SOR_HDMI_SPARE_HW_CTS_ENABLE (1 << 0)

#घोषणा SOR_REFCLK 0xe6
#घोषणा  SOR_REFCLK_DIV_INT(x) ((((x) >> 2) & 0xff) << 8)
#घोषणा  SOR_REFCLK_DIV_FRAC(x) (((x) & 0x3) << 6)

#घोषणा SOR_INPUT_CONTROL 0xe8
#घोषणा  SOR_INPUT_CONTROL_ARM_VIDEO_RANGE_LIMITED (1 << 1)
#घोषणा  SOR_INPUT_CONTROL_HDMI_SRC_SELECT(x) (((x) & 0x1) << 0)

#घोषणा SOR_AUDIO_CNTRL 0xfc
#घोषणा  SOR_AUDIO_CNTRL_INJECT_शून्यSMPL (1 << 29)
#घोषणा  SOR_AUDIO_CNTRL_SOURCE_SELECT(x) (((x) & 0x3) << 20)
#घोषणा   SOURCE_SELECT_MASK 0x3
#घोषणा   SOURCE_SELECT_HDA 0x2
#घोषणा   SOURCE_SELECT_SPDIF 0x1
#घोषणा   SOURCE_SELECT_AUTO 0x0
#घोषणा  SOR_AUDIO_CNTRL_AFIFO_FLUSH (1 << 12)

#घोषणा SOR_AUDIO_SPARE 0xfe
#घोषणा  SOR_AUDIO_SPARE_HBR_ENABLE (1 << 27)

#घोषणा SOR_AUDIO_NVAL_0320 0xff
#घोषणा SOR_AUDIO_NVAL_0441 0x100
#घोषणा SOR_AUDIO_NVAL_0882 0x101
#घोषणा SOR_AUDIO_NVAL_1764 0x102
#घोषणा SOR_AUDIO_NVAL_0480 0x103
#घोषणा SOR_AUDIO_NVAL_0960 0x104
#घोषणा SOR_AUDIO_NVAL_1920 0x105

#घोषणा SOR_AUDIO_HDA_CODEC_SCRATCH0 0x10a
#घोषणा  SOR_AUDIO_HDA_CODEC_SCRATCH0_VALID (1 << 30)
#घोषणा  SOR_AUDIO_HDA_CODEC_SCRATCH0_FMT_MASK 0xffff

#घोषणा SOR_AUDIO_HDA_ELD_BUFWR 0x10c
#घोषणा  SOR_AUDIO_HDA_ELD_BUFWR_INDEX(x) (((x) & 0xff) << 8)
#घोषणा  SOR_AUDIO_HDA_ELD_BUFWR_DATA(x) (((x) & 0xff) << 0)

#घोषणा SOR_AUDIO_HDA_PRESENSE 0x10d
#घोषणा  SOR_AUDIO_HDA_PRESENSE_ELDV (1 << 1)
#घोषणा  SOR_AUDIO_HDA_PRESENSE_PD (1 << 0)

#घोषणा SOR_AUDIO_AVAL_0320 0x10f
#घोषणा SOR_AUDIO_AVAL_0441 0x110
#घोषणा SOR_AUDIO_AVAL_0882 0x111
#घोषणा SOR_AUDIO_AVAL_1764 0x112
#घोषणा SOR_AUDIO_AVAL_0480 0x113
#घोषणा SOR_AUDIO_AVAL_0960 0x114
#घोषणा SOR_AUDIO_AVAL_1920 0x115

#घोषणा SOR_INT_STATUS 0x11c
#घोषणा  SOR_INT_CODEC_CP_REQUEST (1 << 2)
#घोषणा  SOR_INT_CODEC_SCRATCH1 (1 << 1)
#घोषणा  SOR_INT_CODEC_SCRATCH0 (1 << 0)

#घोषणा SOR_INT_MASK 0x11d
#घोषणा SOR_INT_ENABLE 0x11e

#घोषणा SOR_HDMI_VSI_INFOFRAME_CTRL 0x123
#घोषणा SOR_HDMI_VSI_INFOFRAME_STATUS 0x124
#घोषणा SOR_HDMI_VSI_INFOFRAME_HEADER 0x125

#घोषणा SOR_HDMI_AUDIO_N 0x13c
#घोषणा SOR_HDMI_AUDIO_N_LOOKUP (1 << 28)
#घोषणा SOR_HDMI_AUDIO_N_RESET (1 << 20)

#घोषणा SOR_HDMI2_CTRL 0x13e
#घोषणा  SOR_HDMI2_CTRL_CLOCK_MODE_DIV_BY_4 (1 << 1)
#घोषणा  SOR_HDMI2_CTRL_SCRAMBLE (1 << 0)

#पूर्ण_अगर
