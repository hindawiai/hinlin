<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 *    Zheng Yang <zhengyang@rock-chips.com>
 *    Yakir Yang <ykk@rock-chips.com>
 */

#अगर_अघोषित __INNO_HDMI_H__
#घोषणा __INNO_HDMI_H__

#घोषणा DDC_SEGMENT_ADDR		0x30

क्रमागत PWR_MODE अणु
	NORMAL,
	LOWER_PWR,
पूर्ण;

#घोषणा HDMI_SCL_RATE			(100*1000)
#घोषणा DDC_BUS_FREQ_L			0x4b
#घोषणा DDC_BUS_FREQ_H			0x4c

#घोषणा HDMI_SYS_CTRL			0x00
#घोषणा m_RST_ANALOG			(1 << 6)
#घोषणा v_RST_ANALOG			(0 << 6)
#घोषणा v_NOT_RST_ANALOG		(1 << 6)
#घोषणा m_RST_DIGITAL			(1 << 5)
#घोषणा v_RST_DIGITAL			(0 << 5)
#घोषणा v_NOT_RST_DIGITAL		(1 << 5)
#घोषणा m_REG_CLK_INV			(1 << 4)
#घोषणा v_REG_CLK_NOT_INV		(0 << 4)
#घोषणा v_REG_CLK_INV			(1 << 4)
#घोषणा m_VCLK_INV			(1 << 3)
#घोषणा v_VCLK_NOT_INV			(0 << 3)
#घोषणा v_VCLK_INV			(1 << 3)
#घोषणा m_REG_CLK_SOURCE		(1 << 2)
#घोषणा v_REG_CLK_SOURCE_TMDS		(0 << 2)
#घोषणा v_REG_CLK_SOURCE_SYS		(1 << 2)
#घोषणा m_POWER				(1 << 1)
#घोषणा v_PWR_ON			(0 << 1)
#घोषणा v_PWR_OFF			(1 << 1)
#घोषणा m_INT_POL			(1 << 0)
#घोषणा v_INT_POL_HIGH			1
#घोषणा v_INT_POL_LOW			0

#घोषणा HDMI_VIDEO_CONTRL1		0x01
#घोषणा m_VIDEO_INPUT_FORMAT		(7 << 1)
#घोषणा m_DE_SOURCE			(1 << 0)
#घोषणा v_VIDEO_INPUT_FORMAT(n)		(n << 1)
#घोषणा v_DE_EXTERNAL			1
#घोषणा v_DE_INTERNAL			0
क्रमागत अणु
	VIDEO_INPUT_SDR_RGB444 = 0,
	VIDEO_INPUT_DDR_RGB444 = 5,
	VIDEO_INPUT_DDR_YCBCR422 = 6
पूर्ण;

#घोषणा HDMI_VIDEO_CONTRL2		0x02
#घोषणा m_VIDEO_OUTPUT_COLOR		(3 << 6)
#घोषणा m_VIDEO_INPUT_BITS		(3 << 4)
#घोषणा m_VIDEO_INPUT_CSP		(1 << 0)
#घोषणा v_VIDEO_OUTPUT_COLOR(n)		(((n) & 0x3) << 6)
#घोषणा v_VIDEO_INPUT_BITS(n)		(n << 4)
#घोषणा v_VIDEO_INPUT_CSP(n)		(n << 0)
क्रमागत अणु
	VIDEO_INPUT_12BITS = 0,
	VIDEO_INPUT_10BITS = 1,
	VIDEO_INPUT_REVERT = 2,
	VIDEO_INPUT_8BITS = 3,
पूर्ण;

#घोषणा HDMI_VIDEO_CONTRL		0x03
#घोषणा m_VIDEO_AUTO_CSC		(1 << 7)
#घोषणा v_VIDEO_AUTO_CSC(n)		(n << 7)
#घोषणा m_VIDEO_C0_C2_SWAP		(1 << 0)
#घोषणा v_VIDEO_C0_C2_SWAP(n)		(n << 0)
क्रमागत अणु
	C0_C2_CHANGE_ENABLE = 0,
	C0_C2_CHANGE_DISABLE = 1,
	AUTO_CSC_DISABLE = 0,
	AUTO_CSC_ENABLE = 1,
पूर्ण;

#घोषणा HDMI_VIDEO_CONTRL3		0x04
#घोषणा m_COLOR_DEPTH_NOT_INDICATED	(1 << 4)
#घोषणा m_SOF				(1 << 3)
#घोषणा m_COLOR_RANGE			(1 << 2)
#घोषणा m_CSC				(1 << 0)
#घोषणा v_COLOR_DEPTH_NOT_INDICATED(n)	((n) << 4)
#घोषणा v_SOF_ENABLE			(0 << 3)
#घोषणा v_SOF_DISABLE			(1 << 3)
#घोषणा v_COLOR_RANGE_FULL		(1 << 2)
#घोषणा v_COLOR_RANGE_LIMITED		(0 << 2)
#घोषणा v_CSC_ENABLE			1
#घोषणा v_CSC_DISABLE			0

#घोषणा HDMI_AV_MUTE			0x05
#घोषणा m_AVMUTE_CLEAR			(1 << 7)
#घोषणा m_AVMUTE_ENABLE			(1 << 6)
#घोषणा m_AUDIO_MUTE			(1 << 1)
#घोषणा m_VIDEO_BLACK			(1 << 0)
#घोषणा v_AVMUTE_CLEAR(n)		(n << 7)
#घोषणा v_AVMUTE_ENABLE(n)		(n << 6)
#घोषणा v_AUDIO_MUTE(n)			(n << 1)
#घोषणा v_VIDEO_MUTE(n)			(n << 0)

#घोषणा HDMI_VIDEO_TIMING_CTL		0x08
#घोषणा v_HSYNC_POLARITY(n)		(n << 3)
#घोषणा v_VSYNC_POLARITY(n)		(n << 2)
#घोषणा v_INETLACE(n)			(n << 1)
#घोषणा v_EXTERANL_VIDEO(n)		(n << 0)

#घोषणा HDMI_VIDEO_EXT_HTOTAL_L		0x09
#घोषणा HDMI_VIDEO_EXT_HTOTAL_H		0x0a
#घोषणा HDMI_VIDEO_EXT_HBLANK_L		0x0b
#घोषणा HDMI_VIDEO_EXT_HBLANK_H		0x0c
#घोषणा HDMI_VIDEO_EXT_HDELAY_L		0x0d
#घोषणा HDMI_VIDEO_EXT_HDELAY_H		0x0e
#घोषणा HDMI_VIDEO_EXT_HDURATION_L	0x0f
#घोषणा HDMI_VIDEO_EXT_HDURATION_H	0x10
#घोषणा HDMI_VIDEO_EXT_VTOTAL_L		0x11
#घोषणा HDMI_VIDEO_EXT_VTOTAL_H		0x12
#घोषणा HDMI_VIDEO_EXT_VBLANK		0x13
#घोषणा HDMI_VIDEO_EXT_VDELAY		0x14
#घोषणा HDMI_VIDEO_EXT_VDURATION	0x15

#घोषणा HDMI_VIDEO_CSC_COEF		0x18

#घोषणा HDMI_AUDIO_CTRL1		0x35
क्रमागत अणु
	CTS_SOURCE_INTERNAL = 0,
	CTS_SOURCE_EXTERNAL = 1,
पूर्ण;
#घोषणा v_CTS_SOURCE(n)			(n << 7)

क्रमागत अणु
	DOWNSAMPLE_DISABLE = 0,
	DOWNSAMPLE_1_2 = 1,
	DOWNSAMPLE_1_4 = 2,
पूर्ण;
#घोषणा v_DOWN_SAMPLE(n)		(n << 5)

क्रमागत अणु
	AUDIO_SOURCE_IIS = 0,
	AUDIO_SOURCE_SPDIF = 1,
पूर्ण;
#घोषणा v_AUDIO_SOURCE(n)		(n << 3)

#घोषणा v_MCLK_ENABLE(n)		(n << 2)
क्रमागत अणु
	MCLK_128FS = 0,
	MCLK_256FS = 1,
	MCLK_384FS = 2,
	MCLK_512FS = 3,
पूर्ण;
#घोषणा v_MCLK_RATIO(n)			(n)

#घोषणा AUDIO_SAMPLE_RATE		0x37
क्रमागत अणु
	AUDIO_32K = 0x3,
	AUDIO_441K = 0x0,
	AUDIO_48K = 0x2,
	AUDIO_882K = 0x8,
	AUDIO_96K = 0xa,
	AUDIO_1764K = 0xc,
	AUDIO_192K = 0xe,
पूर्ण;

#घोषणा AUDIO_I2S_MODE			0x38
क्रमागत अणु
	I2S_CHANNEL_1_2 = 1,
	I2S_CHANNEL_3_4 = 3,
	I2S_CHANNEL_5_6 = 7,
	I2S_CHANNEL_7_8 = 0xf
पूर्ण;
#घोषणा v_I2S_CHANNEL(n)		((n) << 2)
क्रमागत अणु
	I2S_STANDARD = 0,
	I2S_LEFT_JUSTIFIED = 1,
	I2S_RIGHT_JUSTIFIED = 2,
पूर्ण;
#घोषणा v_I2S_MODE(n)			(n)

#घोषणा AUDIO_I2S_MAP			0x39
#घोषणा AUDIO_I2S_SWAPS_SPDIF		0x3a
#घोषणा v_SPIDF_FREQ(n)			(n)

#घोषणा N_32K				0x1000
#घोषणा N_441K				0x1880
#घोषणा N_882K				0x3100
#घोषणा N_1764K				0x6200
#घोषणा N_48K				0x1800
#घोषणा N_96K				0x3000
#घोषणा N_192K				0x6000

#घोषणा HDMI_AUDIO_CHANNEL_STATUS	0x3e
#घोषणा m_AUDIO_STATUS_NLPCM		(1 << 7)
#घोषणा m_AUDIO_STATUS_USE		(1 << 6)
#घोषणा m_AUDIO_STATUS_COPYRIGHT	(1 << 5)
#घोषणा m_AUDIO_STATUS_ADDITION		(3 << 2)
#घोषणा m_AUDIO_STATUS_CLK_ACCURACY	(2 << 0)
#घोषणा v_AUDIO_STATUS_NLPCM(n)		((n & 1) << 7)
#घोषणा AUDIO_N_H			0x3f
#घोषणा AUDIO_N_M			0x40
#घोषणा AUDIO_N_L			0x41

#घोषणा HDMI_AUDIO_CTS_H		0x45
#घोषणा HDMI_AUDIO_CTS_M		0x46
#घोषणा HDMI_AUDIO_CTS_L		0x47

#घोषणा HDMI_DDC_CLK_L			0x4b
#घोषणा HDMI_DDC_CLK_H			0x4c

#घोषणा HDMI_EDID_SEGMENT_POINTER	0x4d
#घोषणा HDMI_EDID_WORD_ADDR		0x4e
#घोषणा HDMI_EDID_FIFO_OFFSET		0x4f
#घोषणा HDMI_EDID_FIFO_ADDR		0x50

#घोषणा HDMI_PACKET_SEND_MANUAL		0x9c
#घोषणा HDMI_PACKET_SEND_AUTO		0x9d
#घोषणा m_PACKET_GCP_EN			(1 << 7)
#घोषणा m_PACKET_MSI_EN			(1 << 6)
#घोषणा m_PACKET_SDI_EN			(1 << 5)
#घोषणा m_PACKET_VSI_EN			(1 << 4)
#घोषणा v_PACKET_GCP_EN(n)		((n & 1) << 7)
#घोषणा v_PACKET_MSI_EN(n)		((n & 1) << 6)
#घोषणा v_PACKET_SDI_EN(n)		((n & 1) << 5)
#घोषणा v_PACKET_VSI_EN(n)		((n & 1) << 4)

#घोषणा HDMI_CONTROL_PACKET_BUF_INDEX	0x9f
क्रमागत अणु
	INFOFRAME_VSI = 0x05,
	INFOFRAME_AVI = 0x06,
	INFOFRAME_AAI = 0x08,
पूर्ण;

#घोषणा HDMI_CONTROL_PACKET_ADDR	0xa0
#घोषणा HDMI_MAXIMUM_INFO_FRAME_SIZE	0x11
क्रमागत अणु
	AVI_COLOR_MODE_RGB = 0,
	AVI_COLOR_MODE_YCBCR422 = 1,
	AVI_COLOR_MODE_YCBCR444 = 2,
	AVI_COLORIMETRY_NO_DATA = 0,

	AVI_COLORIMETRY_SMPTE_170M = 1,
	AVI_COLORIMETRY_ITU709 = 2,
	AVI_COLORIMETRY_EXTENDED = 3,

	AVI_CODED_FRAME_ASPECT_NO_DATA = 0,
	AVI_CODED_FRAME_ASPECT_4_3 = 1,
	AVI_CODED_FRAME_ASPECT_16_9 = 2,

	ACTIVE_ASPECT_RATE_SAME_AS_CODED_FRAME = 0x08,
	ACTIVE_ASPECT_RATE_4_3 = 0x09,
	ACTIVE_ASPECT_RATE_16_9 = 0x0A,
	ACTIVE_ASPECT_RATE_14_9 = 0x0B,
पूर्ण;

#घोषणा HDMI_HDCP_CTRL			0x52
#घोषणा m_HDMI_DVI			(1 << 1)
#घोषणा v_HDMI_DVI(n)			(n << 1)

#घोषणा HDMI_INTERRUPT_MASK1		0xc0
#घोषणा HDMI_INTERRUPT_STATUS1		0xc1
#घोषणा	m_INT_ACTIVE_VSYNC		(1 << 5)
#घोषणा m_INT_EDID_READY		(1 << 2)

#घोषणा HDMI_INTERRUPT_MASK2		0xc2
#घोषणा HDMI_INTERRUPT_STATUS2		0xc3
#घोषणा m_INT_HDCP_ERR			(1 << 7)
#घोषणा m_INT_BKSV_FLAG			(1 << 6)
#घोषणा m_INT_HDCP_OK			(1 << 4)

#घोषणा HDMI_STATUS			0xc8
#घोषणा m_HOTPLUG			(1 << 7)
#घोषणा m_MASK_INT_HOTPLUG		(1 << 5)
#घोषणा m_INT_HOTPLUG			(1 << 1)
#घोषणा v_MASK_INT_HOTPLUG(n)		((n & 0x1) << 5)

#घोषणा HDMI_COLORBAR                   0xc9

#घोषणा HDMI_PHY_SYNC			0xce
#घोषणा HDMI_PHY_SYS_CTL		0xe0
#घोषणा m_TMDS_CLK_SOURCE		(1 << 5)
#घोषणा v_TMDS_FROM_PLL			(0 << 5)
#घोषणा v_TMDS_FROM_GEN			(1 << 5)
#घोषणा m_PHASE_CLK			(1 << 4)
#घोषणा v_DEFAULT_PHASE			(0 << 4)
#घोषणा v_SYNC_PHASE			(1 << 4)
#घोषणा m_TMDS_CURRENT_PWR		(1 << 3)
#घोषणा v_TURN_ON_CURRENT		(0 << 3)
#घोषणा v_CAT_OFF_CURRENT		(1 << 3)
#घोषणा m_BANDGAP_PWR			(1 << 2)
#घोषणा v_BANDGAP_PWR_UP		(0 << 2)
#घोषणा v_BANDGAP_PWR_DOWN		(1 << 2)
#घोषणा m_PLL_PWR			(1 << 1)
#घोषणा v_PLL_PWR_UP			(0 << 1)
#घोषणा v_PLL_PWR_DOWN			(1 << 1)
#घोषणा m_TMDS_CHG_PWR			(1 << 0)
#घोषणा v_TMDS_CHG_PWR_UP		(0 << 0)
#घोषणा v_TMDS_CHG_PWR_DOWN		(1 << 0)

#घोषणा HDMI_PHY_CHG_PWR		0xe1
#घोषणा v_CLK_CHG_PWR(n)		((n & 1) << 3)
#घोषणा v_DATA_CHG_PWR(n)		((n & 7) << 0)

#घोषणा HDMI_PHY_DRIVER			0xe2
#घोषणा v_CLK_MAIN_DRIVER(n)		(n << 4)
#घोषणा v_DATA_MAIN_DRIVER(n)		(n << 0)

#घोषणा HDMI_PHY_PRE_EMPHASIS		0xe3
#घोषणा v_PRE_EMPHASIS(n)		((n & 7) << 4)
#घोषणा v_CLK_PRE_DRIVER(n)		((n & 3) << 2)
#घोषणा v_DATA_PRE_DRIVER(n)		((n & 3) << 0)

#घोषणा HDMI_PHY_FEEDBACK_DIV_RATIO_LOW		0xe7
#घोषणा v_FEEDBACK_DIV_LOW(n)			(n & 0xff)
#घोषणा HDMI_PHY_FEEDBACK_DIV_RATIO_HIGH	0xe8
#घोषणा v_FEEDBACK_DIV_HIGH(n)			(n & 1)

#घोषणा HDMI_PHY_PRE_DIV_RATIO		0xed
#घोषणा v_PRE_DIV_RATIO(n)		(n & 0x1f)

#घोषणा HDMI_CEC_CTRL			0xd0
#घोषणा m_ADJUST_FOR_HISENSE		(1 << 6)
#घोषणा m_REJECT_RX_BROADCAST		(1 << 5)
#घोषणा m_BUSFREETIME_ENABLE		(1 << 2)
#घोषणा m_REJECT_RX			(1 << 1)
#घोषणा m_START_TX			(1 << 0)

#घोषणा HDMI_CEC_DATA			0xd1
#घोषणा HDMI_CEC_TX_OFFSET		0xd2
#घोषणा HDMI_CEC_RX_OFFSET		0xd3
#घोषणा HDMI_CEC_CLK_H			0xd4
#घोषणा HDMI_CEC_CLK_L			0xd5
#घोषणा HDMI_CEC_TX_LENGTH		0xd6
#घोषणा HDMI_CEC_RX_LENGTH		0xd7
#घोषणा HDMI_CEC_TX_INT_MASK		0xd8
#घोषणा m_TX_DONE			(1 << 3)
#घोषणा m_TX_NOACK			(1 << 2)
#घोषणा m_TX_BROADCAST_REJ		(1 << 1)
#घोषणा m_TX_BUSNOTFREE			(1 << 0)

#घोषणा HDMI_CEC_RX_INT_MASK		0xd9
#घोषणा m_RX_LA_ERR			(1 << 4)
#घोषणा m_RX_GLITCH			(1 << 3)
#घोषणा m_RX_DONE			(1 << 0)

#घोषणा HDMI_CEC_TX_INT			0xda
#घोषणा HDMI_CEC_RX_INT			0xdb
#घोषणा HDMI_CEC_BUSFREETIME_L		0xdc
#घोषणा HDMI_CEC_BUSFREETIME_H		0xdd
#घोषणा HDMI_CEC_LOGICADDR		0xde

#पूर्ण_अगर /* __INNO_HDMI_H__ */
