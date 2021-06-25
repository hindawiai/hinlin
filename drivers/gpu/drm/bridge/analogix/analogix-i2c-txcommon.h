<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2016, Analogix Semiconductor. All rights reserved.
 */
#अगर_अघोषित _ANALOGIX_I2C_TXCOMMON_H_
#घोषणा _ANALOGIX_I2C_TXCOMMON_H_

/***************************************************************/
/* Register definitions क्रम TX_P2                              */
/***************************************************************/

/*
 * Core Register Definitions
 */

/* Device ID Low Byte Register */
#घोषणा SP_DEVICE_IDL_REG		0x02

/* Device ID High Byte Register */
#घोषणा SP_DEVICE_IDH_REG		0x03

/* Device version रेजिस्टर */
#घोषणा SP_DEVICE_VERSION_REG		0x04

/* Power Down Control Register */
#घोषणा SP_POWERDOWN_CTRL_REG		0x05
#घोषणा SP_REGISTER_PD			BIT(7)
#घोषणा SP_HDCP_PD			BIT(5)
#घोषणा SP_AUDIO_PD			BIT(4)
#घोषणा SP_VIDEO_PD			BIT(3)
#घोषणा SP_LINK_PD			BIT(2)
#घोषणा SP_TOTAL_PD			BIT(1)

/* Reset Control Register 1 */
#घोषणा SP_RESET_CTRL1_REG		0x06
#घोषणा SP_MISC_RST			BIT(7)
#घोषणा SP_VIDCAP_RST			BIT(6)
#घोषणा SP_VIDFIF_RST			BIT(5)
#घोषणा SP_AUDFIF_RST			BIT(4)
#घोषणा SP_AUDCAP_RST			BIT(3)
#घोषणा SP_HDCP_RST			BIT(2)
#घोषणा SP_SW_RST			BIT(1)
#घोषणा SP_HW_RST			BIT(0)

/* Reset Control Register 2 */
#घोषणा SP_RESET_CTRL2_REG		0x07
#घोषणा SP_AUX_RST			BIT(2)
#घोषणा SP_SERDES_FIFO_RST		BIT(1)
#घोषणा SP_I2C_REG_RST			BIT(0)

/* Video Control Register 1 */
#घोषणा SP_VID_CTRL1_REG		0x08
#घोषणा SP_VIDEO_EN			BIT(7)
#घोषणा SP_VIDEO_MUTE			BIT(2)
#घोषणा SP_DE_GEN			BIT(1)
#घोषणा SP_DEMUX			BIT(0)

/* Video Control Register 2 */
#घोषणा SP_VID_CTRL2_REG		0x09
#घोषणा SP_IN_COLOR_F_MASK		0x03
#घोषणा SP_IN_YC_BIT_SEL		BIT(2)
#घोषणा SP_IN_BPC_MASK			0x70
#घोषणा SP_IN_BPC_SHIFT			4
#  define SP_IN_BPC_12BIT		0x03
#  define SP_IN_BPC_10BIT		0x02
#  define SP_IN_BPC_8BIT		0x01
#  define SP_IN_BPC_6BIT		0x00
#घोषणा SP_IN_D_RANGE			BIT(7)

/* Video Control Register 3 */
#घोषणा SP_VID_CTRL3_REG		0x0a
#घोषणा SP_HPD_OUT			BIT(6)

/* Video Control Register 5 */
#घोषणा SP_VID_CTRL5_REG		0x0c
#घोषणा SP_CSC_STD_SEL			BIT(7)
#घोषणा SP_XVYCC_RNG_LMT		BIT(6)
#घोषणा SP_RANGE_Y2R			BIT(5)
#घोषणा SP_CSPACE_Y2R			BIT(4)
#घोषणा SP_RGB_RNG_LMT			BIT(3)
#घोषणा SP_Y_RNG_LMT			BIT(2)
#घोषणा SP_RANGE_R2Y			BIT(1)
#घोषणा SP_CSPACE_R2Y			BIT(0)

/* Video Control Register 6 */
#घोषणा SP_VID_CTRL6_REG		0x0d
#घोषणा SP_TEST_PATTERN_EN		BIT(7)
#घोषणा SP_VIDEO_PROCESS_EN		BIT(6)
#घोषणा SP_VID_US_MODE			BIT(3)
#घोषणा SP_VID_DS_MODE			BIT(2)
#घोषणा SP_UP_SAMPLE			BIT(1)
#घोषणा SP_DOWN_SAMPLE			BIT(0)

/* Video Control Register 8 */
#घोषणा SP_VID_CTRL8_REG		0x0f
#घोषणा SP_VID_VRES_TH			BIT(0)

/* Total Line Status Low Byte Register */
#घोषणा SP_TOTAL_LINE_STAL_REG		0x24

/* Total Line Status High Byte Register */
#घोषणा SP_TOTAL_LINE_STAH_REG		0x25

/* Active Line Status Low Byte Register */
#घोषणा SP_ACT_LINE_STAL_REG		0x26

/* Active Line Status High Byte Register */
#घोषणा SP_ACT_LINE_STAH_REG		0x27

/* Vertical Front Porch Status Register */
#घोषणा SP_V_F_PORCH_STA_REG		0x28

/* Vertical SYNC Width Status Register */
#घोषणा SP_V_SYNC_STA_REG		0x29

/* Vertical Back Porch Status Register */
#घोषणा SP_V_B_PORCH_STA_REG		0x2a

/* Total Pixel Status Low Byte Register */
#घोषणा SP_TOTAL_PIXEL_STAL_REG		0x2b

/* Total Pixel Status High Byte Register */
#घोषणा SP_TOTAL_PIXEL_STAH_REG		0x2c

/* Active Pixel Status Low Byte Register */
#घोषणा SP_ACT_PIXEL_STAL_REG		0x2d

/* Active Pixel Status High Byte Register */
#घोषणा SP_ACT_PIXEL_STAH_REG		0x2e

/* Horizontal Front Porch Status Low Byte Register */
#घोषणा SP_H_F_PORCH_STAL_REG		0x2f

/* Horizontal Front Porch Statys High Byte Register */
#घोषणा SP_H_F_PORCH_STAH_REG		0x30

/* Horizontal SYNC Width Status Low Byte Register */
#घोषणा SP_H_SYNC_STAL_REG		0x31

/* Horizontal SYNC Width Status High Byte Register */
#घोषणा SP_H_SYNC_STAH_REG		0x32

/* Horizontal Back Porch Status Low Byte Register */
#घोषणा SP_H_B_PORCH_STAL_REG		0x33

/* Horizontal Back Porch Status High Byte Register */
#घोषणा SP_H_B_PORCH_STAH_REG		0x34

/* InfoFrame AVI Packet DB1 Register */
#घोषणा SP_INFOFRAME_AVI_DB1_REG	0x70

/* Bit Control Specअगरic Register */
#घोषणा SP_BIT_CTRL_SPECIFIC_REG	0x80
#घोषणा SP_BIT_CTRL_SELECT_SHIFT	1
#घोषणा SP_ENABLE_BIT_CTRL		BIT(0)

/* InfoFrame Audio Packet DB1 Register */
#घोषणा SP_INFOFRAME_AUD_DB1_REG	0x83

/* InfoFrame MPEG Packet DB1 Register */
#घोषणा SP_INFOFRAME_MPEG_DB1_REG	0xb0

/* Audio Channel Status Registers */
#घोषणा SP_AUD_CH_STATUS_BASE		0xd0

/* Audio Channel Num Register 5 */
#घोषणा SP_I2S_CHANNEL_NUM_MASK		0xe0
#  define SP_I2S_CH_NUM_1		(0x00 << 5)
#  define SP_I2S_CH_NUM_2		(0x01 << 5)
#  define SP_I2S_CH_NUM_3		(0x02 << 5)
#  define SP_I2S_CH_NUM_4		(0x03 << 5)
#  define SP_I2S_CH_NUM_5		(0x04 << 5)
#  define SP_I2S_CH_NUM_6		(0x05 << 5)
#  define SP_I2S_CH_NUM_7		(0x06 << 5)
#  define SP_I2S_CH_NUM_8		(0x07 << 5)
#घोषणा SP_EXT_VUCP			BIT(2)
#घोषणा SP_VBIT				BIT(1)
#घोषणा SP_AUDIO_LAYOUT			BIT(0)

/* Analog Debug Register 1 */
#घोषणा SP_ANALOG_DEBUG1_REG		0xdc

/* Analog Debug Register 2 */
#घोषणा SP_ANALOG_DEBUG2_REG		0xdd
#घोषणा SP_FORCE_SW_OFF_BYPASS		0x20
#घोषणा SP_XTAL_FRQ			0x1c
#  define SP_XTAL_FRQ_19M2		(0x00 << 2)
#  define SP_XTAL_FRQ_24M		(0x01 << 2)
#  define SP_XTAL_FRQ_25M		(0x02 << 2)
#  define SP_XTAL_FRQ_26M		(0x03 << 2)
#  define SP_XTAL_FRQ_27M		(0x04 << 2)
#  define SP_XTAL_FRQ_38M4		(0x05 << 2)
#  define SP_XTAL_FRQ_52M		(0x06 << 2)
#घोषणा SP_POWERON_TIME_1P5MS		0x03

/* Analog Control 0 Register */
#घोषणा SP_ANALOG_CTRL0_REG		0xe1

/* Common Interrupt Status Register 1 */
#घोषणा SP_COMMON_INT_STATUS_BASE	(0xf1 - 1)
#घोषणा SP_PLL_LOCK_CHG			0x40

/* Common Interrupt Status Register 2 */
#घोषणा SP_COMMON_INT_STATUS2		0xf2
#घोषणा SP_HDCP_AUTH_CHG		BIT(1)
#घोषणा SP_HDCP_AUTH_DONE		BIT(0)

#घोषणा SP_HDCP_LINK_CHECK_FAIL		BIT(0)

/* Common Interrupt Status Register 4 */
#घोषणा SP_COMMON_INT_STATUS4_REG	0xf4
#घोषणा SP_HPD_IRQ			BIT(6)
#घोषणा SP_HPD_ESYNC_ERR		BIT(4)
#घोषणा SP_HPD_CHG			BIT(2)
#घोषणा SP_HPD_LOST			BIT(1)
#घोषणा SP_HPD_PLUG			BIT(0)

/* DP Interrupt Status Register */
#घोषणा SP_DP_INT_STATUS1_REG		0xf7
#घोषणा SP_TRAINING_FINISH		BIT(5)
#घोषणा SP_POLLING_ERR			BIT(4)

/* Common Interrupt Mask Register */
#घोषणा SP_COMMON_INT_MASK_BASE		(0xf8 - 1)

#घोषणा SP_COMMON_INT_MASK4_REG		0xfb

/* DP Interrupts Mask Register */
#घोषणा SP_DP_INT_MASK1_REG		0xfe

/* Interrupt Control Register */
#घोषणा SP_INT_CTRL_REG			0xff

#पूर्ण_अगर /* _ANALOGIX_I2C_TXCOMMON_H_ */
