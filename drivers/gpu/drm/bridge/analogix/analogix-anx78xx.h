<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2016, Analogix Semiconductor. All rights reserved.
 */

#अगर_अघोषित __ANX78xx_H
#घोषणा __ANX78xx_H

#समावेश "analogix-i2c-dptx.h"
#समावेश "analogix-i2c-txcommon.h"

/***************************************************************/
/* Register definitions क्रम RX_PO                              */
/***************************************************************/

/*
 * System Control and Status
 */

/* Software Reset Register 1 */
#घोषणा SP_SOFTWARE_RESET1_REG		0x11
#घोषणा SP_VIDEO_RST			BIT(4)
#घोषणा SP_HDCP_MAN_RST			BIT(2)
#घोषणा SP_TMDS_RST			BIT(1)
#घोषणा SP_SW_MAN_RST			BIT(0)

/* System Status Register */
#घोषणा SP_SYSTEM_STATUS_REG		0x14
#घोषणा SP_TMDS_CLOCK_DET		BIT(1)
#घोषणा SP_TMDS_DE_DET			BIT(0)

/* HDMI Status Register */
#घोषणा SP_HDMI_STATUS_REG		0x15
#घोषणा SP_HDMI_AUD_LAYOUT		BIT(3)
#घोषणा SP_HDMI_DET			BIT(0)
#  define SP_DVI_MODE			0
#  define SP_HDMI_MODE			1

/* HDMI Mute Control Register */
#घोषणा SP_HDMI_MUTE_CTRL_REG		0x16
#घोषणा SP_AUD_MUTE			BIT(1)
#घोषणा SP_VID_MUTE			BIT(0)

/* System Power Down Register 1 */
#घोषणा SP_SYSTEM_POWER_DOWN1_REG	0x18
#घोषणा SP_PWDN_CTRL			BIT(0)

/*
 * Audio and Video Auto Control
 */

/* Auto Audio and Video Control रेजिस्टर */
#घोषणा SP_AUDVID_CTRL_REG		0x20
#घोषणा SP_AVC_OE			BIT(7)
#घोषणा SP_AAC_OE			BIT(6)
#घोषणा SP_AVC_EN			BIT(1)
#घोषणा SP_AAC_EN			BIT(0)

/* Audio Exception Enable Registers */
#घोषणा SP_AUD_EXCEPTION_ENABLE_BASE	(0x24 - 1)
/* Bits क्रम Audio Exception Enable Register 3 */
#घोषणा SP_AEC_EN21			BIT(5)

/*
 * Interrupt
 */

/* Interrupt Status Register 1 */
#घोषणा SP_INT_STATUS1_REG		0x31
/* Bits क्रम Interrupt Status Register 1 */
#घोषणा SP_HDMI_DVI			BIT(7)
#घोषणा SP_CKDT_CHG			BIT(6)
#घोषणा SP_SCDT_CHG			BIT(5)
#घोषणा SP_PCLK_CHG			BIT(4)
#घोषणा SP_PLL_UNLOCK			BIT(3)
#घोषणा SP_CABLE_PLUG_CHG		BIT(2)
#घोषणा SP_SET_MUTE			BIT(1)
#घोषणा SP_SW_INTR			BIT(0)
/* Bits क्रम Interrupt Status Register 2 */
#घोषणा SP_HDCP_ERR			BIT(5)
#घोषणा SP_AUDIO_SAMPLE_CHG		BIT(0)	/* unकरोcumented */
/* Bits क्रम Interrupt Status Register 3 */
#घोषणा SP_AUD_MODE_CHG			BIT(0)
/* Bits क्रम Interrupt Status Register 5 */
#घोषणा SP_AUDIO_RCV			BIT(0)
/* Bits क्रम Interrupt Status Register 6 */
#घोषणा SP_INT_STATUS6_REG		0x36
#घोषणा SP_CTS_RCV			BIT(7)
#घोषणा SP_NEW_AUD_PKT			BIT(4)
#घोषणा SP_NEW_AVI_PKT			BIT(1)
#घोषणा SP_NEW_CP_PKT			BIT(0)
/* Bits क्रम Interrupt Status Register 7 */
#घोषणा SP_NO_VSI			BIT(7)
#घोषणा SP_NEW_VS			BIT(4)

/* Interrupt Mask 1 Status Registers */
#घोषणा SP_INT_MASK1_REG		0x41

/* HDMI US TIMER Control Register */
#घोषणा SP_HDMI_US_TIMER_CTRL_REG	0x49
#घोषणा SP_MS_TIMER_MARGIN_10_8_MASK	0x07

/*
 * TMDS Control
 */

/* TMDS Control Registers */
#घोषणा SP_TMDS_CTRL_BASE		(0x50 - 1)
/* Bits क्रम TMDS Control Register 7 */
#घोषणा SP_PD_RT			BIT(0)

/*
 * Video Control
 */

/* Video Status Register */
#घोषणा SP_VIDEO_STATUS_REG		0x70
#घोषणा SP_COLOR_DEPTH_MASK		0xf0
#घोषणा SP_COLOR_DEPTH_SHIFT		4
#  define SP_COLOR_DEPTH_MODE_LEGACY	0x00
#  define SP_COLOR_DEPTH_MODE_24BIT	0x04
#  define SP_COLOR_DEPTH_MODE_30BIT	0x05
#  define SP_COLOR_DEPTH_MODE_36BIT	0x06
#  define SP_COLOR_DEPTH_MODE_48BIT	0x07

/* Video Data Range Control Register */
#घोषणा SP_VID_DATA_RANGE_CTRL_REG	0x83
#घोषणा SP_R2Y_INPUT_LIMIT		BIT(1)

/* Pixel Clock High Resolution Counter Registers */
#घोषणा SP_PCLK_HIGHRES_CNT_BASE	(0x8c - 1)

/*
 * Audio Control
 */

/* Number of Audio Channels Status Registers */
#घोषणा SP_AUD_CH_STATUS_REG_NUM	6

/* Audio IN S/PDIF Channel Status Registers */
#घोषणा SP_AUD_SPDIF_CH_STATUS_BASE	0xc7

/* Audio IN S/PDIF Channel Status Register 4 */
#घोषणा SP_FS_FREQ_MASK			0x0f
#  define SP_FS_FREQ_44100HZ		0x00
#  define SP_FS_FREQ_48000HZ		0x02
#  define SP_FS_FREQ_32000HZ		0x03
#  define SP_FS_FREQ_88200HZ		0x08
#  define SP_FS_FREQ_96000HZ		0x0a
#  define SP_FS_FREQ_176400HZ		0x0c
#  define SP_FS_FREQ_192000HZ		0x0e

/*
 * Micellaneous Control Block
 */

/* CHIP Control Register */
#घोषणा SP_CHIP_CTRL_REG		0xe3
#घोषणा SP_MAN_HDMI5V_DET		BIT(3)
#घोषणा SP_PLLLOCK_CKDT_EN		BIT(2)
#घोषणा SP_ANALOG_CKDT_EN		BIT(1)
#घोषणा SP_DIGITAL_CKDT_EN		BIT(0)

/* Packet Receiving Status Register */
#घोषणा SP_PACKET_RECEIVING_STATUS_REG	0xf3
#घोषणा SP_AVI_RCVD			BIT(5)
#घोषणा SP_VSI_RCVD			BIT(1)

/***************************************************************/
/* Register definitions क्रम RX_P1                              */
/***************************************************************/

/* HDCP BCAPS Shaकरोw Register */
#घोषणा SP_HDCP_BCAPS_SHADOW_REG	0x2a
#घोषणा SP_BCAPS_REPEATER		BIT(5)

/* HDCP Status Register */
#घोषणा SP_RX_HDCP_STATUS_REG		0x3f
#घोषणा SP_AUTH_EN			BIT(4)

/*
 * InfoFrame and Control Packet Registers
 */

/* AVI InfoFrame packet checksum */
#घोषणा SP_AVI_INFOFRAME_CHECKSUM	0xa3

/* AVI InfoFrame Registers */
#घोषणा SP_AVI_INFOFRAME_DATA_BASE	0xa4

#घोषणा SP_AVI_COLOR_F_MASK		0x60
#घोषणा SP_AVI_COLOR_F_SHIFT		5

/* Audio InfoFrame Registers */
#घोषणा SP_AUD_INFOFRAME_DATA_BASE	0xc4
#घोषणा SP_AUD_INFOFRAME_LAYOUT_MASK	0x0f

/* MPEG/HDMI Venकरोr Specअगरic InfoFrame Packet type code */
#घोषणा SP_MPEG_VS_INFOFRAME_TYPE_REG	0xe0

/* MPEG/HDMI Venकरोr Specअगरic InfoFrame Packet length */
#घोषणा SP_MPEG_VS_INFOFRAME_LEN_REG	0xe2

/* MPEG/HDMI Venकरोr Specअगरic InfoFrame Packet version number */
#घोषणा SP_MPEG_VS_INFOFRAME_VER_REG	0xe1

/* MPEG/HDMI Venकरोr Specअगरic InfoFrame Packet content */
#घोषणा SP_MPEG_VS_INFOFRAME_DATA_BASE	0xe4

/* General Control Packet Register */
#घोषणा SP_GENERAL_CTRL_PACKET_REG	0x9f
#घोषणा SP_CLEAR_AVMUTE			BIT(4)
#घोषणा SP_SET_AVMUTE			BIT(0)

/***************************************************************/
/* Register definitions क्रम TX_P1                              */
/***************************************************************/

/* DP TX Link Training Control Register */
#घोषणा SP_DP_TX_LT_CTRL0_REG		0x30

/* PD 1.2 Lपूर्णांक Training 80bit Pattern Register */
#घोषणा SP_DP_LT_80BIT_PATTERN0_REG	0x80
#घोषणा SP_DP_LT_80BIT_PATTERN_REG_NUM	10

/* Audio Interface Control Register 0 */
#घोषणा SP_AUD_INTERFACE_CTRL0_REG	0x5f
#घोषणा SP_AUD_INTERFACE_DISABLE	0x80

/* Audio Interface Control Register 2 */
#घोषणा SP_AUD_INTERFACE_CTRL2_REG	0x60
#घोषणा SP_M_AUD_ADJUST_ST		0x04

/* Audio Interface Control Register 3 */
#घोषणा SP_AUD_INTERFACE_CTRL3_REG	0x62

/* Audio Interface Control Register 4 */
#घोषणा SP_AUD_INTERFACE_CTRL4_REG	0x67

/* Audio Interface Control Register 5 */
#घोषणा SP_AUD_INTERFACE_CTRL5_REG	0x68

/* Audio Interface Control Register 6 */
#घोषणा SP_AUD_INTERFACE_CTRL6_REG	0x69

/* Firmware Version Register */
#घोषणा SP_FW_VER_REG			0xb7

#पूर्ण_अगर
