<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register definition file क्रम Analogix DP core driver
 *
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#अगर_अघोषित _ANALOGIX_DP_REG_H
#घोषणा _ANALOGIX_DP_REG_H

#घोषणा ANALOGIX_DP_TX_SW_RESET			0x14
#घोषणा ANALOGIX_DP_FUNC_EN_1			0x18
#घोषणा ANALOGIX_DP_FUNC_EN_2			0x1C
#घोषणा ANALOGIX_DP_VIDEO_CTL_1			0x20
#घोषणा ANALOGIX_DP_VIDEO_CTL_2			0x24
#घोषणा ANALOGIX_DP_VIDEO_CTL_3			0x28

#घोषणा ANALOGIX_DP_VIDEO_CTL_8			0x3C
#घोषणा ANALOGIX_DP_VIDEO_CTL_10		0x44

#घोषणा ANALOGIX_DP_SPDIF_AUDIO_CTL_0		0xD8

#घोषणा ANALOGIX_DP_PLL_REG_1			0xfc
#घोषणा ANALOGIX_DP_PLL_REG_2			0x9e4
#घोषणा ANALOGIX_DP_PLL_REG_3			0x9e8
#घोषणा ANALOGIX_DP_PLL_REG_4			0x9ec
#घोषणा ANALOGIX_DP_PLL_REG_5			0xa00

#घोषणा ANALOGIX_DP_PD				0x12c

#घोषणा ANALOGIX_DP_IF_TYPE			0x244
#घोषणा ANALOGIX_DP_IF_PKT_DB1			0x254
#घोषणा ANALOGIX_DP_IF_PKT_DB2			0x258
#घोषणा ANALOGIX_DP_SPD_HB0			0x2F8
#घोषणा ANALOGIX_DP_SPD_HB1			0x2FC
#घोषणा ANALOGIX_DP_SPD_HB2			0x300
#घोषणा ANALOGIX_DP_SPD_HB3			0x304
#घोषणा ANALOGIX_DP_SPD_PB0			0x308
#घोषणा ANALOGIX_DP_SPD_PB1			0x30C
#घोषणा ANALOGIX_DP_SPD_PB2			0x310
#घोषणा ANALOGIX_DP_SPD_PB3			0x314
#घोषणा ANALOGIX_DP_PSR_FRAME_UPDATE_CTRL	0x318
#घोषणा ANALOGIX_DP_VSC_SHADOW_DB0		0x31C
#घोषणा ANALOGIX_DP_VSC_SHADOW_DB1		0x320

#घोषणा ANALOGIX_DP_LANE_MAP			0x35C

#घोषणा ANALOGIX_DP_ANALOG_CTL_1		0x370
#घोषणा ANALOGIX_DP_ANALOG_CTL_2		0x374
#घोषणा ANALOGIX_DP_ANALOG_CTL_3		0x378
#घोषणा ANALOGIX_DP_PLL_FILTER_CTL_1		0x37C
#घोषणा ANALOGIX_DP_TX_AMP_TUNING_CTL		0x380

#घोषणा ANALOGIX_DP_AUX_HW_RETRY_CTL		0x390

#घोषणा ANALOGIX_DP_COMMON_INT_STA_1		0x3C4
#घोषणा ANALOGIX_DP_COMMON_INT_STA_2		0x3C8
#घोषणा ANALOGIX_DP_COMMON_INT_STA_3		0x3CC
#घोषणा ANALOGIX_DP_COMMON_INT_STA_4		0x3D0
#घोषणा ANALOGIX_DP_INT_STA			0x3DC
#घोषणा ANALOGIX_DP_COMMON_INT_MASK_1		0x3E0
#घोषणा ANALOGIX_DP_COMMON_INT_MASK_2		0x3E4
#घोषणा ANALOGIX_DP_COMMON_INT_MASK_3		0x3E8
#घोषणा ANALOGIX_DP_COMMON_INT_MASK_4		0x3EC
#घोषणा ANALOGIX_DP_INT_STA_MASK		0x3F8
#घोषणा ANALOGIX_DP_INT_CTL			0x3FC

#घोषणा ANALOGIX_DP_SYS_CTL_1			0x600
#घोषणा ANALOGIX_DP_SYS_CTL_2			0x604
#घोषणा ANALOGIX_DP_SYS_CTL_3			0x608
#घोषणा ANALOGIX_DP_SYS_CTL_4			0x60C

#घोषणा ANALOGIX_DP_PKT_SEND_CTL		0x640
#घोषणा ANALOGIX_DP_HDCP_CTL			0x648

#घोषणा ANALOGIX_DP_LINK_BW_SET			0x680
#घोषणा ANALOGIX_DP_LANE_COUNT_SET		0x684
#घोषणा ANALOGIX_DP_TRAINING_PTN_SET		0x688
#घोषणा ANALOGIX_DP_LN0_LINK_TRAINING_CTL	0x68C
#घोषणा ANALOGIX_DP_LN1_LINK_TRAINING_CTL	0x690
#घोषणा ANALOGIX_DP_LN2_LINK_TRAINING_CTL	0x694
#घोषणा ANALOGIX_DP_LN3_LINK_TRAINING_CTL	0x698

#घोषणा ANALOGIX_DP_DEBUG_CTL			0x6C0
#घोषणा ANALOGIX_DP_HPD_DEGLITCH_L		0x6C4
#घोषणा ANALOGIX_DP_HPD_DEGLITCH_H		0x6C8
#घोषणा ANALOGIX_DP_LINK_DEBUG_CTL		0x6E0

#घोषणा ANALOGIX_DP_M_VID_0			0x700
#घोषणा ANALOGIX_DP_M_VID_1			0x704
#घोषणा ANALOGIX_DP_M_VID_2			0x708
#घोषणा ANALOGIX_DP_N_VID_0			0x70C
#घोषणा ANALOGIX_DP_N_VID_1			0x710
#घोषणा ANALOGIX_DP_N_VID_2			0x714

#घोषणा ANALOGIX_DP_PLL_CTL			0x71C
#घोषणा ANALOGIX_DP_PHY_PD			0x720
#घोषणा ANALOGIX_DP_PHY_TEST			0x724

#घोषणा ANALOGIX_DP_VIDEO_FIFO_THRD		0x730
#घोषणा ANALOGIX_DP_AUDIO_MARGIN		0x73C

#घोषणा ANALOGIX_DP_M_VID_GEN_FILTER_TH		0x764
#घोषणा ANALOGIX_DP_M_AUD_GEN_FILTER_TH		0x778
#घोषणा ANALOGIX_DP_AUX_CH_STA			0x780
#घोषणा ANALOGIX_DP_AUX_CH_DEFER_CTL		0x788
#घोषणा ANALOGIX_DP_AUX_RX_COMM			0x78C
#घोषणा ANALOGIX_DP_BUFFER_DATA_CTL		0x790
#घोषणा ANALOGIX_DP_AUX_CH_CTL_1		0x794
#घोषणा ANALOGIX_DP_AUX_ADDR_7_0		0x798
#घोषणा ANALOGIX_DP_AUX_ADDR_15_8		0x79C
#घोषणा ANALOGIX_DP_AUX_ADDR_19_16		0x7A0
#घोषणा ANALOGIX_DP_AUX_CH_CTL_2		0x7A4

#घोषणा ANALOGIX_DP_BUF_DATA_0			0x7C0

#घोषणा ANALOGIX_DP_SOC_GENERAL_CTL		0x800

#घोषणा ANALOGIX_DP_CRC_CON			0x890

/* ANALOGIX_DP_TX_SW_RESET */
#घोषणा RESET_DP_TX				(0x1 << 0)

/* ANALOGIX_DP_FUNC_EN_1 */
#घोषणा MASTER_VID_FUNC_EN_N			(0x1 << 7)
#घोषणा RK_VID_CAP_FUNC_EN_N			(0x1 << 6)
#घोषणा SLAVE_VID_FUNC_EN_N			(0x1 << 5)
#घोषणा RK_VID_FIFO_FUNC_EN_N			(0x1 << 5)
#घोषणा AUD_FIFO_FUNC_EN_N			(0x1 << 4)
#घोषणा AUD_FUNC_EN_N				(0x1 << 3)
#घोषणा HDCP_FUNC_EN_N				(0x1 << 2)
#घोषणा CRC_FUNC_EN_N				(0x1 << 1)
#घोषणा SW_FUNC_EN_N				(0x1 << 0)

/* ANALOGIX_DP_FUNC_EN_2 */
#घोषणा SSC_FUNC_EN_N				(0x1 << 7)
#घोषणा AUX_FUNC_EN_N				(0x1 << 2)
#घोषणा SERDES_FIFO_FUNC_EN_N			(0x1 << 1)
#घोषणा LS_CLK_DOMAIN_FUNC_EN_N			(0x1 << 0)

/* ANALOGIX_DP_VIDEO_CTL_1 */
#घोषणा VIDEO_EN				(0x1 << 7)
#घोषणा HDCP_VIDEO_MUTE				(0x1 << 6)

/* ANALOGIX_DP_VIDEO_CTL_1 */
#घोषणा IN_D_RANGE_MASK				(0x1 << 7)
#घोषणा IN_D_RANGE_SHIFT			(7)
#घोषणा IN_D_RANGE_CEA				(0x1 << 7)
#घोषणा IN_D_RANGE_VESA				(0x0 << 7)
#घोषणा IN_BPC_MASK				(0x7 << 4)
#घोषणा IN_BPC_SHIFT				(4)
#घोषणा IN_BPC_12_BITS				(0x3 << 4)
#घोषणा IN_BPC_10_BITS				(0x2 << 4)
#घोषणा IN_BPC_8_BITS				(0x1 << 4)
#घोषणा IN_BPC_6_BITS				(0x0 << 4)
#घोषणा IN_COLOR_F_MASK				(0x3 << 0)
#घोषणा IN_COLOR_F_SHIFT			(0)
#घोषणा IN_COLOR_F_YCBCR444			(0x2 << 0)
#घोषणा IN_COLOR_F_YCBCR422			(0x1 << 0)
#घोषणा IN_COLOR_F_RGB				(0x0 << 0)

/* ANALOGIX_DP_VIDEO_CTL_3 */
#घोषणा IN_YC_COEFFI_MASK			(0x1 << 7)
#घोषणा IN_YC_COEFFI_SHIFT			(7)
#घोषणा IN_YC_COEFFI_ITU709			(0x1 << 7)
#घोषणा IN_YC_COEFFI_ITU601			(0x0 << 7)
#घोषणा VID_CHK_UPDATE_TYPE_MASK		(0x1 << 4)
#घोषणा VID_CHK_UPDATE_TYPE_SHIFT		(4)
#घोषणा VID_CHK_UPDATE_TYPE_1			(0x1 << 4)
#घोषणा VID_CHK_UPDATE_TYPE_0			(0x0 << 4)
#घोषणा REUSE_SPD_EN				(0x1 << 3)

/* ANALOGIX_DP_VIDEO_CTL_8 */
#घोषणा VID_HRES_TH(x)				(((x) & 0xf) << 4)
#घोषणा VID_VRES_TH(x)				(((x) & 0xf) << 0)

/* ANALOGIX_DP_VIDEO_CTL_10 */
#घोषणा FORMAT_SEL				(0x1 << 4)
#घोषणा INTERACE_SCAN_CFG			(0x1 << 2)
#घोषणा VSYNC_POLARITY_CFG			(0x1 << 1)
#घोषणा HSYNC_POLARITY_CFG			(0x1 << 0)

/* ANALOGIX_DP_PLL_REG_1 */
#घोषणा REF_CLK_24M				(0x1 << 0)
#घोषणा REF_CLK_27M				(0x0 << 0)
#घोषणा REF_CLK_MASK				(0x1 << 0)

/* ANALOGIX_DP_PSR_FRAME_UPDATE_CTRL */
#घोषणा PSR_FRAME_UP_TYPE_BURST			(0x1 << 0)
#घोषणा PSR_FRAME_UP_TYPE_SINGLE		(0x0 << 0)
#घोषणा PSR_CRC_SEL_HARDWARE			(0x1 << 1)
#घोषणा PSR_CRC_SEL_MANUALLY			(0x0 << 1)

/* ANALOGIX_DP_LANE_MAP */
#घोषणा LANE3_MAP_LOGIC_LANE_0			(0x0 << 6)
#घोषणा LANE3_MAP_LOGIC_LANE_1			(0x1 << 6)
#घोषणा LANE3_MAP_LOGIC_LANE_2			(0x2 << 6)
#घोषणा LANE3_MAP_LOGIC_LANE_3			(0x3 << 6)
#घोषणा LANE2_MAP_LOGIC_LANE_0			(0x0 << 4)
#घोषणा LANE2_MAP_LOGIC_LANE_1			(0x1 << 4)
#घोषणा LANE2_MAP_LOGIC_LANE_2			(0x2 << 4)
#घोषणा LANE2_MAP_LOGIC_LANE_3			(0x3 << 4)
#घोषणा LANE1_MAP_LOGIC_LANE_0			(0x0 << 2)
#घोषणा LANE1_MAP_LOGIC_LANE_1			(0x1 << 2)
#घोषणा LANE1_MAP_LOGIC_LANE_2			(0x2 << 2)
#घोषणा LANE1_MAP_LOGIC_LANE_3			(0x3 << 2)
#घोषणा LANE0_MAP_LOGIC_LANE_0			(0x0 << 0)
#घोषणा LANE0_MAP_LOGIC_LANE_1			(0x1 << 0)
#घोषणा LANE0_MAP_LOGIC_LANE_2			(0x2 << 0)
#घोषणा LANE0_MAP_LOGIC_LANE_3			(0x3 << 0)

/* ANALOGIX_DP_ANALOG_CTL_1 */
#घोषणा TX_TERMINAL_CTRL_50_OHM			(0x1 << 4)

/* ANALOGIX_DP_ANALOG_CTL_2 */
#घोषणा SEL_24M					(0x1 << 3)
#घोषणा TX_DVDD_BIT_1_0625V			(0x4 << 0)

/* ANALOGIX_DP_ANALOG_CTL_3 */
#घोषणा DRIVE_DVDD_BIT_1_0625V			(0x4 << 5)
#घोषणा VCO_BIT_600_MICRO			(0x5 << 0)

/* ANALOGIX_DP_PLL_FILTER_CTL_1 */
#घोषणा PD_RING_OSC				(0x1 << 6)
#घोषणा AUX_TERMINAL_CTRL_50_OHM		(0x2 << 4)
#घोषणा TX_CUR1_2X				(0x1 << 2)
#घोषणा TX_CUR_16_MA				(0x3 << 0)

/* ANALOGIX_DP_TX_AMP_TUNING_CTL */
#घोषणा CH3_AMP_400_MV				(0x0 << 24)
#घोषणा CH2_AMP_400_MV				(0x0 << 16)
#घोषणा CH1_AMP_400_MV				(0x0 << 8)
#घोषणा CH0_AMP_400_MV				(0x0 << 0)

/* ANALOGIX_DP_AUX_HW_RETRY_CTL */
#घोषणा AUX_BIT_PERIOD_EXPECTED_DELAY(x)	(((x) & 0x7) << 8)
#घोषणा AUX_HW_RETRY_INTERVAL_MASK		(0x3 << 3)
#घोषणा AUX_HW_RETRY_INTERVAL_600_MICROSECONDS	(0x0 << 3)
#घोषणा AUX_HW_RETRY_INTERVAL_800_MICROSECONDS	(0x1 << 3)
#घोषणा AUX_HW_RETRY_INTERVAL_1000_MICROSECONDS	(0x2 << 3)
#घोषणा AUX_HW_RETRY_INTERVAL_1800_MICROSECONDS	(0x3 << 3)
#घोषणा AUX_HW_RETRY_COUNT_SEL(x)		(((x) & 0x7) << 0)

/* ANALOGIX_DP_COMMON_INT_STA_1 */
#घोषणा VSYNC_DET				(0x1 << 7)
#घोषणा PLL_LOCK_CHG				(0x1 << 6)
#घोषणा SPDIF_ERR				(0x1 << 5)
#घोषणा SPDIF_UNSTBL				(0x1 << 4)
#घोषणा VID_FORMAT_CHG				(0x1 << 3)
#घोषणा AUD_CLK_CHG				(0x1 << 2)
#घोषणा VID_CLK_CHG				(0x1 << 1)
#घोषणा SW_INT					(0x1 << 0)

/* ANALOGIX_DP_COMMON_INT_STA_2 */
#घोषणा ENC_EN_CHG				(0x1 << 6)
#घोषणा HW_BKSV_RDY				(0x1 << 3)
#घोषणा HW_SHA_DONE				(0x1 << 2)
#घोषणा HW_AUTH_STATE_CHG			(0x1 << 1)
#घोषणा HW_AUTH_DONE				(0x1 << 0)

/* ANALOGIX_DP_COMMON_INT_STA_3 */
#घोषणा AFIFO_UNDER				(0x1 << 7)
#घोषणा AFIFO_OVER				(0x1 << 6)
#घोषणा R0_CHK_FLAG				(0x1 << 5)

/* ANALOGIX_DP_COMMON_INT_STA_4 */
#घोषणा PSR_ACTIVE				(0x1 << 7)
#घोषणा PSR_INACTIVE				(0x1 << 6)
#घोषणा SPDIF_BI_PHASE_ERR			(0x1 << 5)
#घोषणा HOTPLUG_CHG				(0x1 << 2)
#घोषणा HPD_LOST				(0x1 << 1)
#घोषणा PLUG					(0x1 << 0)

/* ANALOGIX_DP_INT_STA */
#घोषणा INT_HPD					(0x1 << 6)
#घोषणा HW_TRAINING_FINISH			(0x1 << 5)
#घोषणा RPLY_RECEIV				(0x1 << 1)
#घोषणा AUX_ERR					(0x1 << 0)

/* ANALOGIX_DP_INT_CTL */
#घोषणा SOFT_INT_CTRL				(0x1 << 2)
#घोषणा INT_POL1				(0x1 << 1)
#घोषणा INT_POL0				(0x1 << 0)

/* ANALOGIX_DP_SYS_CTL_1 */
#घोषणा DET_STA					(0x1 << 2)
#घोषणा FORCE_DET				(0x1 << 1)
#घोषणा DET_CTRL				(0x1 << 0)

/* ANALOGIX_DP_SYS_CTL_2 */
#घोषणा CHA_CRI(x)				(((x) & 0xf) << 4)
#घोषणा CHA_STA					(0x1 << 2)
#घोषणा FORCE_CHA				(0x1 << 1)
#घोषणा CHA_CTRL				(0x1 << 0)

/* ANALOGIX_DP_SYS_CTL_3 */
#घोषणा HPD_STATUS				(0x1 << 6)
#घोषणा F_HPD					(0x1 << 5)
#घोषणा HPD_CTRL				(0x1 << 4)
#घोषणा HDCP_RDY				(0x1 << 3)
#घोषणा STRM_VALID				(0x1 << 2)
#घोषणा F_VALID					(0x1 << 1)
#घोषणा VALID_CTRL				(0x1 << 0)

/* ANALOGIX_DP_SYS_CTL_4 */
#घोषणा FIX_M_AUD				(0x1 << 4)
#घोषणा ENHANCED				(0x1 << 3)
#घोषणा FIX_M_VID				(0x1 << 2)
#घोषणा M_VID_UPDATE_CTRL			(0x3 << 0)

/* ANALOGIX_DP_TRAINING_PTN_SET */
#घोषणा SCRAMBLER_TYPE				(0x1 << 9)
#घोषणा HW_LINK_TRAINING_PATTERN		(0x1 << 8)
#घोषणा SCRAMBLING_DISABLE			(0x1 << 5)
#घोषणा SCRAMBLING_ENABLE			(0x0 << 5)
#घोषणा LINK_QUAL_PATTERN_SET_MASK		(0x3 << 2)
#घोषणा LINK_QUAL_PATTERN_SET_PRBS7		(0x3 << 2)
#घोषणा LINK_QUAL_PATTERN_SET_D10_2		(0x1 << 2)
#घोषणा LINK_QUAL_PATTERN_SET_DISABLE		(0x0 << 2)
#घोषणा SW_TRAINING_PATTERN_SET_MASK		(0x3 << 0)
#घोषणा SW_TRAINING_PATTERN_SET_PTN2		(0x2 << 0)
#घोषणा SW_TRAINING_PATTERN_SET_PTN1		(0x1 << 0)
#घोषणा SW_TRAINING_PATTERN_SET_NORMAL		(0x0 << 0)

/* ANALOGIX_DP_LN0_LINK_TRAINING_CTL */
#घोषणा PRE_EMPHASIS_SET_MASK			(0x3 << 3)
#घोषणा PRE_EMPHASIS_SET_SHIFT			(3)

/* ANALOGIX_DP_DEBUG_CTL */
#घोषणा PLL_LOCK				(0x1 << 4)
#घोषणा F_PLL_LOCK				(0x1 << 3)
#घोषणा PLL_LOCK_CTRL				(0x1 << 2)
#घोषणा PN_INV					(0x1 << 0)

/* ANALOGIX_DP_PLL_CTL */
#घोषणा DP_PLL_PD				(0x1 << 7)
#घोषणा DP_PLL_RESET				(0x1 << 6)
#घोषणा DP_PLL_LOOP_BIT_DEFAULT			(0x1 << 4)
#घोषणा DP_PLL_REF_BIT_1_1250V			(0x5 << 0)
#घोषणा DP_PLL_REF_BIT_1_2500V			(0x7 << 0)

/* ANALOGIX_DP_PHY_PD */
#घोषणा DP_INC_BG				(0x1 << 7)
#घोषणा DP_EXP_BG				(0x1 << 6)
#घोषणा DP_PHY_PD				(0x1 << 5)
#घोषणा RK_AUX_PD				(0x1 << 5)
#घोषणा AUX_PD					(0x1 << 4)
#घोषणा RK_PLL_PD				(0x1 << 4)
#घोषणा CH3_PD					(0x1 << 3)
#घोषणा CH2_PD					(0x1 << 2)
#घोषणा CH1_PD					(0x1 << 1)
#घोषणा CH0_PD					(0x1 << 0)
#घोषणा DP_ALL_PD				(0xff)

/* ANALOGIX_DP_PHY_TEST */
#घोषणा MACRO_RST				(0x1 << 5)
#घोषणा CH1_TEST				(0x1 << 1)
#घोषणा CH0_TEST				(0x1 << 0)

/* ANALOGIX_DP_AUX_CH_STA */
#घोषणा AUX_BUSY				(0x1 << 4)
#घोषणा AUX_STATUS_MASK				(0xf << 0)

/* ANALOGIX_DP_AUX_CH_DEFER_CTL */
#घोषणा DEFER_CTRL_EN				(0x1 << 7)
#घोषणा DEFER_COUNT(x)				(((x) & 0x7f) << 0)

/* ANALOGIX_DP_AUX_RX_COMM */
#घोषणा AUX_RX_COMM_I2C_DEFER			(0x2 << 2)
#घोषणा AUX_RX_COMM_AUX_DEFER			(0x2 << 0)

/* ANALOGIX_DP_BUFFER_DATA_CTL */
#घोषणा BUF_CLR					(0x1 << 7)
#घोषणा BUF_DATA_COUNT(x)			(((x) & 0x1f) << 0)

/* ANALOGIX_DP_AUX_CH_CTL_1 */
#घोषणा AUX_LENGTH(x)				(((x - 1) & 0xf) << 4)
#घोषणा AUX_TX_COMM_MASK			(0xf << 0)
#घोषणा AUX_TX_COMM_DP_TRANSACTION		(0x1 << 3)
#घोषणा AUX_TX_COMM_I2C_TRANSACTION		(0x0 << 3)
#घोषणा AUX_TX_COMM_MOT				(0x1 << 2)
#घोषणा AUX_TX_COMM_WRITE			(0x0 << 0)
#घोषणा AUX_TX_COMM_READ			(0x1 << 0)

/* ANALOGIX_DP_AUX_ADDR_7_0 */
#घोषणा AUX_ADDR_7_0(x)				(((x) >> 0) & 0xff)

/* ANALOGIX_DP_AUX_ADDR_15_8 */
#घोषणा AUX_ADDR_15_8(x)			(((x) >> 8) & 0xff)

/* ANALOGIX_DP_AUX_ADDR_19_16 */
#घोषणा AUX_ADDR_19_16(x)			(((x) >> 16) & 0x0f)

/* ANALOGIX_DP_AUX_CH_CTL_2 */
#घोषणा ADDR_ONLY				(0x1 << 1)
#घोषणा AUX_EN					(0x1 << 0)

/* ANALOGIX_DP_SOC_GENERAL_CTL */
#घोषणा AUDIO_MODE_SPDIF_MODE			(0x1 << 8)
#घोषणा AUDIO_MODE_MASTER_MODE			(0x0 << 8)
#घोषणा MASTER_VIDEO_INTERLACE_EN		(0x1 << 4)
#घोषणा VIDEO_MASTER_CLK_SEL			(0x1 << 2)
#घोषणा VIDEO_MASTER_MODE_EN			(0x1 << 1)
#घोषणा VIDEO_MODE_MASK				(0x1 << 0)
#घोषणा VIDEO_MODE_SLAVE_MODE			(0x1 << 0)
#घोषणा VIDEO_MODE_MASTER_MODE			(0x0 << 0)

/* ANALOGIX_DP_PKT_SEND_CTL */
#घोषणा IF_UP					(0x1 << 4)
#घोषणा IF_EN					(0x1 << 0)

/* ANALOGIX_DP_CRC_CON */
#घोषणा PSR_VID_CRC_FLUSH			(0x1 << 2)
#घोषणा PSR_VID_CRC_ENABLE			(0x1 << 0)

#पूर्ण_अगर /* _ANALOGIX_DP_REG_H */
