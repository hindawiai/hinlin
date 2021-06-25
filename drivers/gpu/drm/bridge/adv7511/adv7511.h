<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Analog Devices ADV7511 HDMI transmitter driver
 *
 * Copyright 2012 Analog Devices Inc.
 */

#अगर_अघोषित __DRM_I2C_ADV7511_H__
#घोषणा __DRM_I2C_ADV7511_H__

#समावेश <linux/hdmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>

#घोषणा ADV7511_REG_CHIP_REVISION		0x00
#घोषणा ADV7511_REG_N0				0x01
#घोषणा ADV7511_REG_N1				0x02
#घोषणा ADV7511_REG_N2				0x03
#घोषणा ADV7511_REG_SPDIF_FREQ			0x04
#घोषणा ADV7511_REG_CTS_AUTOMATIC1		0x05
#घोषणा ADV7511_REG_CTS_AUTOMATIC2		0x06
#घोषणा ADV7511_REG_CTS_MANUAL0			0x07
#घोषणा ADV7511_REG_CTS_MANUAL1			0x08
#घोषणा ADV7511_REG_CTS_MANUAL2			0x09
#घोषणा ADV7511_REG_AUDIO_SOURCE		0x0a
#घोषणा ADV7511_REG_AUDIO_CONFIG		0x0b
#घोषणा ADV7511_REG_I2S_CONFIG			0x0c
#घोषणा ADV7511_REG_I2S_WIDTH			0x0d
#घोषणा ADV7511_REG_AUDIO_SUB_SRC0		0x0e
#घोषणा ADV7511_REG_AUDIO_SUB_SRC1		0x0f
#घोषणा ADV7511_REG_AUDIO_SUB_SRC2		0x10
#घोषणा ADV7511_REG_AUDIO_SUB_SRC3		0x11
#घोषणा ADV7511_REG_AUDIO_CFG1			0x12
#घोषणा ADV7511_REG_AUDIO_CFG2			0x13
#घोषणा ADV7511_REG_AUDIO_CFG3			0x14
#घोषणा ADV7511_REG_I2C_FREQ_ID_CFG		0x15
#घोषणा ADV7511_REG_VIDEO_INPUT_CFG1		0x16
#घोषणा ADV7511_REG_CSC_UPPER(x)		(0x18 + (x) * 2)
#घोषणा ADV7511_REG_CSC_LOWER(x)		(0x19 + (x) * 2)
#घोषणा ADV7511_REG_SYNC_DECODER(x)		(0x30 + (x))
#घोषणा ADV7511_REG_DE_GENERATOR		(0x35 + (x))
#घोषणा ADV7511_REG_PIXEL_REPETITION		0x3b
#घोषणा ADV7511_REG_VIC_MANUAL			0x3c
#घोषणा ADV7511_REG_VIC_SEND			0x3d
#घोषणा ADV7511_REG_VIC_DETECTED		0x3e
#घोषणा ADV7511_REG_AUX_VIC_DETECTED		0x3f
#घोषणा ADV7511_REG_PACKET_ENABLE0		0x40
#घोषणा ADV7511_REG_POWER			0x41
#घोषणा ADV7511_REG_STATUS			0x42
#घोषणा ADV7511_REG_EDID_I2C_ADDR		0x43
#घोषणा ADV7511_REG_PACKET_ENABLE1		0x44
#घोषणा ADV7511_REG_PACKET_I2C_ADDR		0x45
#घोषणा ADV7511_REG_DSD_ENABLE			0x46
#घोषणा ADV7511_REG_VIDEO_INPUT_CFG2		0x48
#घोषणा ADV7511_REG_INFOFRAME_UPDATE		0x4a
#घोषणा ADV7511_REG_GC(x)			(0x4b + (x)) /* 0x4b - 0x51 */
#घोषणा ADV7511_REG_AVI_INFOFRAME_VERSION	0x52
#घोषणा ADV7511_REG_AVI_INFOFRAME_LENGTH	0x53
#घोषणा ADV7511_REG_AVI_INFOFRAME_CHECKSUM	0x54
#घोषणा ADV7511_REG_AVI_INFOFRAME(x)		(0x55 + (x)) /* 0x55 - 0x6f */
#घोषणा ADV7511_REG_AUDIO_INFOFRAME_VERSION	0x70
#घोषणा ADV7511_REG_AUDIO_INFOFRAME_LENGTH	0x71
#घोषणा ADV7511_REG_AUDIO_INFOFRAME_CHECKSUM	0x72
#घोषणा ADV7511_REG_AUDIO_INFOFRAME(x)		(0x73 + (x)) /* 0x73 - 0x7c */
#घोषणा ADV7511_REG_INT_ENABLE(x)		(0x94 + (x))
#घोषणा ADV7511_REG_INT(x)			(0x96 + (x))
#घोषणा ADV7511_REG_INPUT_CLK_DIV		0x9d
#घोषणा ADV7511_REG_PLL_STATUS			0x9e
#घोषणा ADV7511_REG_HDMI_POWER			0xa1
#घोषणा ADV7511_REG_HDCP_HDMI_CFG		0xaf
#घोषणा ADV7511_REG_AN(x)			(0xb0 + (x)) /* 0xb0 - 0xb7 */
#घोषणा ADV7511_REG_HDCP_STATUS			0xb8
#घोषणा ADV7511_REG_BCAPS			0xbe
#घोषणा ADV7511_REG_BKSV(x)			(0xc0 + (x)) /* 0xc0 - 0xc3 */
#घोषणा ADV7511_REG_EDID_SEGMENT		0xc4
#घोषणा ADV7511_REG_DDC_STATUS			0xc8
#घोषणा ADV7511_REG_EDID_READ_CTRL		0xc9
#घोषणा ADV7511_REG_BSTATUS(x)			(0xca + (x)) /* 0xca - 0xcb */
#घोषणा ADV7511_REG_TIMING_GEN_SEQ		0xd0
#घोषणा ADV7511_REG_POWER2			0xd6
#घोषणा ADV7511_REG_HSYNC_PLACEMENT_MSB		0xfa

#घोषणा ADV7511_REG_SYNC_ADJUSTMENT(x)		(0xd7 + (x)) /* 0xd7 - 0xdc */
#घोषणा ADV7511_REG_TMDS_CLOCK_INV		0xde
#घोषणा ADV7511_REG_ARC_CTRL			0xdf
#घोषणा ADV7511_REG_CEC_I2C_ADDR		0xe1
#घोषणा ADV7511_REG_CEC_CTRL			0xe2
#घोषणा ADV7511_REG_CHIP_ID_HIGH		0xf5
#घोषणा ADV7511_REG_CHIP_ID_LOW			0xf6

/* Hardware defined शेष addresses क्रम I2C रेजिस्टर maps */
#घोषणा ADV7511_CEC_I2C_ADDR_DEFAULT		0x3c
#घोषणा ADV7511_EDID_I2C_ADDR_DEFAULT		0x3f
#घोषणा ADV7511_PACKET_I2C_ADDR_DEFAULT		0x38

#घोषणा ADV7511_CSC_ENABLE			BIT(7)
#घोषणा ADV7511_CSC_UPDATE_MODE			BIT(5)

#घोषणा ADV7511_INT0_HPD			BIT(7)
#घोषणा ADV7511_INT0_VSYNC			BIT(5)
#घोषणा ADV7511_INT0_AUDIO_FIFO_FULL		BIT(4)
#घोषणा ADV7511_INT0_EDID_READY			BIT(2)
#घोषणा ADV7511_INT0_HDCP_AUTHENTICATED		BIT(1)

#घोषणा ADV7511_INT1_DDC_ERROR			BIT(7)
#घोषणा ADV7511_INT1_BKSV			BIT(6)
#घोषणा ADV7511_INT1_CEC_TX_READY		BIT(5)
#घोषणा ADV7511_INT1_CEC_TX_ARBIT_LOST		BIT(4)
#घोषणा ADV7511_INT1_CEC_TX_RETRY_TIMEOUT	BIT(3)
#घोषणा ADV7511_INT1_CEC_RX_READY3		BIT(2)
#घोषणा ADV7511_INT1_CEC_RX_READY2		BIT(1)
#घोषणा ADV7511_INT1_CEC_RX_READY1		BIT(0)

#घोषणा ADV7511_ARC_CTRL_POWER_DOWN		BIT(0)

#घोषणा ADV7511_CEC_CTRL_POWER_DOWN		BIT(0)

#घोषणा ADV7511_POWER_POWER_DOWN		BIT(6)

#घोषणा ADV7511_HDMI_CFG_MODE_MASK		0x2
#घोषणा ADV7511_HDMI_CFG_MODE_DVI		0x0
#घोषणा ADV7511_HDMI_CFG_MODE_HDMI		0x2

#घोषणा ADV7511_AUDIO_SELECT_I2C		0x0
#घोषणा ADV7511_AUDIO_SELECT_SPDIF		0x1
#घोषणा ADV7511_AUDIO_SELECT_DSD		0x2
#घोषणा ADV7511_AUDIO_SELECT_HBR		0x3
#घोषणा ADV7511_AUDIO_SELECT_DST		0x4

#घोषणा ADV7511_I2S_SAMPLE_LEN_16		0x2
#घोषणा ADV7511_I2S_SAMPLE_LEN_20		0x3
#घोषणा ADV7511_I2S_SAMPLE_LEN_18		0x4
#घोषणा ADV7511_I2S_SAMPLE_LEN_22		0x5
#घोषणा ADV7511_I2S_SAMPLE_LEN_19		0x8
#घोषणा ADV7511_I2S_SAMPLE_LEN_23		0x9
#घोषणा ADV7511_I2S_SAMPLE_LEN_24		0xb
#घोषणा ADV7511_I2S_SAMPLE_LEN_17		0xc
#घोषणा ADV7511_I2S_SAMPLE_LEN_21		0xd

#घोषणा ADV7511_SAMPLE_FREQ_44100		0x0
#घोषणा ADV7511_SAMPLE_FREQ_48000		0x2
#घोषणा ADV7511_SAMPLE_FREQ_32000		0x3
#घोषणा ADV7511_SAMPLE_FREQ_88200		0x8
#घोषणा ADV7511_SAMPLE_FREQ_96000		0xa
#घोषणा ADV7511_SAMPLE_FREQ_176400		0xc
#घोषणा ADV7511_SAMPLE_FREQ_192000		0xe

#घोषणा ADV7511_STATUS_POWER_DOWN_POLARITY	BIT(7)
#घोषणा ADV7511_STATUS_HPD			BIT(6)
#घोषणा ADV7511_STATUS_MONITOR_SENSE		BIT(5)
#घोषणा ADV7511_STATUS_I2S_32BIT_MODE		BIT(3)

#घोषणा ADV7511_PACKET_ENABLE_N_CTS		BIT(8+6)
#घोषणा ADV7511_PACKET_ENABLE_AUDIO_SAMPLE	BIT(8+5)
#घोषणा ADV7511_PACKET_ENABLE_AVI_INFOFRAME	BIT(8+4)
#घोषणा ADV7511_PACKET_ENABLE_AUDIO_INFOFRAME	BIT(8+3)
#घोषणा ADV7511_PACKET_ENABLE_GC		BIT(7)
#घोषणा ADV7511_PACKET_ENABLE_SPD		BIT(6)
#घोषणा ADV7511_PACKET_ENABLE_MPEG		BIT(5)
#घोषणा ADV7511_PACKET_ENABLE_ACP		BIT(4)
#घोषणा ADV7511_PACKET_ENABLE_ISRC		BIT(3)
#घोषणा ADV7511_PACKET_ENABLE_GM		BIT(2)
#घोषणा ADV7511_PACKET_ENABLE_SPARE2		BIT(1)
#घोषणा ADV7511_PACKET_ENABLE_SPARE1		BIT(0)

#घोषणा ADV7511_REG_POWER2_HPD_SRC_MASK		0xc0
#घोषणा ADV7511_REG_POWER2_HPD_SRC_BOTH		0x00
#घोषणा ADV7511_REG_POWER2_HPD_SRC_HPD		0x40
#घोषणा ADV7511_REG_POWER2_HPD_SRC_CEC		0x80
#घोषणा ADV7511_REG_POWER2_HPD_SRC_NONE		0xc0
#घोषणा ADV7511_REG_POWER2_TDMS_ENABLE		BIT(4)
#घोषणा ADV7511_REG_POWER2_GATE_INPUT_CLK	BIT(0)

#घोषणा ADV7511_LOW_REFRESH_RATE_NONE		0x0
#घोषणा ADV7511_LOW_REFRESH_RATE_24HZ		0x1
#घोषणा ADV7511_LOW_REFRESH_RATE_25HZ		0x2
#घोषणा ADV7511_LOW_REFRESH_RATE_30HZ		0x3

#घोषणा ADV7511_AUDIO_CFG3_LEN_MASK		0x0f
#घोषणा ADV7511_I2C_FREQ_ID_CFG_RATE_MASK	0xf0

#घोषणा ADV7511_AUDIO_SOURCE_I2S		0
#घोषणा ADV7511_AUDIO_SOURCE_SPDIF		1

#घोषणा ADV7511_I2S_FORMAT_I2S			0
#घोषणा ADV7511_I2S_FORMAT_RIGHT_J		1
#घोषणा ADV7511_I2S_FORMAT_LEFT_J		2

#घोषणा ADV7511_PACKET(p, x)	    ((p) * 0x20 + (x))
#घोषणा ADV7511_PACKET_SDP(x)	    ADV7511_PACKET(0, x)
#घोषणा ADV7511_PACKET_MPEG(x)	    ADV7511_PACKET(1, x)
#घोषणा ADV7511_PACKET_ACP(x)	    ADV7511_PACKET(2, x)
#घोषणा ADV7511_PACKET_ISRC1(x)	    ADV7511_PACKET(3, x)
#घोषणा ADV7511_PACKET_ISRC2(x)	    ADV7511_PACKET(4, x)
#घोषणा ADV7511_PACKET_GM(x)	    ADV7511_PACKET(5, x)
#घोषणा ADV7511_PACKET_SPARE(x)	    ADV7511_PACKET(6, x)

#घोषणा ADV7511_REG_CEC_TX_FRAME_HDR	0x00
#घोषणा ADV7511_REG_CEC_TX_FRAME_DATA0	0x01
#घोषणा ADV7511_REG_CEC_TX_FRAME_LEN	0x10
#घोषणा ADV7511_REG_CEC_TX_ENABLE	0x11
#घोषणा ADV7511_REG_CEC_TX_RETRY	0x12
#घोषणा ADV7511_REG_CEC_TX_LOW_DRV_CNT	0x14
#घोषणा ADV7511_REG_CEC_RX_FRAME_HDR	0x15
#घोषणा ADV7511_REG_CEC_RX_FRAME_DATA0	0x16
#घोषणा ADV7511_REG_CEC_RX_FRAME_LEN	0x25
#घोषणा ADV7511_REG_CEC_RX_ENABLE	0x26
#घोषणा ADV7511_REG_CEC_RX_BUFFERS	0x4a
#घोषणा ADV7511_REG_CEC_LOG_ADDR_MASK	0x4b
#घोषणा ADV7511_REG_CEC_LOG_ADDR_0_1	0x4c
#घोषणा ADV7511_REG_CEC_LOG_ADDR_2	0x4d
#घोषणा ADV7511_REG_CEC_CLK_DIV		0x4e
#घोषणा ADV7511_REG_CEC_SOFT_RESET	0x50

#घोषणा ADV7533_REG_CEC_OFFSET		0x70

क्रमागत adv7511_input_घड़ी अणु
	ADV7511_INPUT_CLOCK_1X,
	ADV7511_INPUT_CLOCK_2X,
	ADV7511_INPUT_CLOCK_DDR,
पूर्ण;

क्रमागत adv7511_input_justअगरication अणु
	ADV7511_INPUT_JUSTIFICATION_EVENLY = 0,
	ADV7511_INPUT_JUSTIFICATION_RIGHT = 1,
	ADV7511_INPUT_JUSTIFICATION_LEFT = 2,
पूर्ण;

क्रमागत adv7511_input_sync_pulse अणु
	ADV7511_INPUT_SYNC_PULSE_DE = 0,
	ADV7511_INPUT_SYNC_PULSE_HSYNC = 1,
	ADV7511_INPUT_SYNC_PULSE_VSYNC = 2,
	ADV7511_INPUT_SYNC_PULSE_NONE = 3,
पूर्ण;

/**
 * क्रमागत adv7511_sync_polarity - Polarity क्रम the input sync संकेतs
 * @ADV7511_SYNC_POLARITY_PASSTHROUGH:  Sync polarity matches that of
 *				       the currently configured mode.
 * @ADV7511_SYNC_POLARITY_LOW:	    Sync polarity is low
 * @ADV7511_SYNC_POLARITY_HIGH:	    Sync polarity is high
 *
 * If the polarity is set to either LOW or HIGH the driver will configure the
 * ADV7511 to पूर्णांकernally invert the sync संकेत अगर required to match the sync
 * polarity setting क्रम the currently selected output mode.
 *
 * If the polarity is set to PASSTHROUGH, the ADV7511 will route the संकेत
 * unchanged. This is used when the upstream graphics core alपढ़ोy generates
 * the sync संकेतs with the correct polarity.
 */
क्रमागत adv7511_sync_polarity अणु
	ADV7511_SYNC_POLARITY_PASSTHROUGH,
	ADV7511_SYNC_POLARITY_LOW,
	ADV7511_SYNC_POLARITY_HIGH,
पूर्ण;

/**
 * काष्ठा adv7511_link_config - Describes adv7511 hardware configuration
 * @input_color_depth:		Number of bits per color component (8, 10 or 12)
 * @input_colorspace:		The input colorspace (RGB, YUV444, YUV422)
 * @input_घड़ी:		The input video घड़ी style (1x, 2x, DDR)
 * @input_style:		The input component arrangement variant
 * @input_justअगरication:	Video input क्रमmat bit justअगरication
 * @घड़ी_delay:		Clock delay क्रम the input घड़ी (in ps)
 * @embedded_sync:		Video input uses BT.656-style embedded sync
 * @sync_pulse:			Select the sync pulse
 * @vsync_polarity:		vsync input संकेत configuration
 * @hsync_polarity:		hsync input संकेत configuration
 */
काष्ठा adv7511_link_config अणु
	अचिन्हित पूर्णांक input_color_depth;
	क्रमागत hdmi_colorspace input_colorspace;
	क्रमागत adv7511_input_घड़ी input_घड़ी;
	अचिन्हित पूर्णांक input_style;
	क्रमागत adv7511_input_justअगरication input_justअगरication;

	पूर्णांक घड़ी_delay;

	bool embedded_sync;
	क्रमागत adv7511_input_sync_pulse sync_pulse;
	क्रमागत adv7511_sync_polarity vsync_polarity;
	क्रमागत adv7511_sync_polarity hsync_polarity;
पूर्ण;

/**
 * क्रमागत adv7511_csc_scaling - Scaling factor क्रम the ADV7511 CSC
 * @ADV7511_CSC_SCALING_1: CSC results are not scaled
 * @ADV7511_CSC_SCALING_2: CSC results are scaled by a factor of two
 * @ADV7511_CSC_SCALING_4: CSC results are scalled by a factor of four
 */
क्रमागत adv7511_csc_scaling अणु
	ADV7511_CSC_SCALING_1 = 0,
	ADV7511_CSC_SCALING_2 = 1,
	ADV7511_CSC_SCALING_4 = 2,
पूर्ण;

/**
 * काष्ठा adv7511_video_config - Describes adv7511 hardware configuration
 * @csc_enable:			Whether to enable color space conversion
 * @csc_scaling_factor:		Color space conversion scaling factor
 * @csc_coefficents:		Color space conversion coefficents
 * @hdmi_mode:			Whether to use HDMI or DVI output mode
 * @avi_infoframe:		HDMI infoframe
 */
काष्ठा adv7511_video_config अणु
	bool csc_enable;
	क्रमागत adv7511_csc_scaling csc_scaling_factor;
	स्थिर uपूर्णांक16_t *csc_coefficents;

	bool hdmi_mode;
	काष्ठा hdmi_avi_infoframe avi_infoframe;
पूर्ण;

क्रमागत adv7511_type अणु
	ADV7511,
	ADV7533,
	ADV7535,
पूर्ण;

#घोषणा ADV7511_MAX_ADDRS 3

काष्ठा adv7511 अणु
	काष्ठा i2c_client *i2c_मुख्य;
	काष्ठा i2c_client *i2c_edid;
	काष्ठा i2c_client *i2c_packet;
	काष्ठा i2c_client *i2c_cec;

	काष्ठा regmap *regmap;
	काष्ठा regmap *regmap_cec;
	क्रमागत drm_connector_status status;
	bool घातered;

	काष्ठा drm_display_mode curr_mode;

	अचिन्हित पूर्णांक f_पंचांगds;
	अचिन्हित पूर्णांक f_audio;
	अचिन्हित पूर्णांक audio_source;

	अचिन्हित पूर्णांक current_edid_segment;
	uपूर्णांक8_t edid_buf[256];
	bool edid_पढ़ो;

	रुको_queue_head_t wq;
	काष्ठा work_काष्ठा hpd_work;

	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;

	bool embedded_sync;
	क्रमागत adv7511_sync_polarity vsync_polarity;
	क्रमागत adv7511_sync_polarity hsync_polarity;
	bool rgb;

	काष्ठा gpio_desc *gpio_pd;

	काष्ठा regulator_bulk_data *supplies;
	अचिन्हित पूर्णांक num_supplies;

	/* ADV7533 DSI RX related params */
	काष्ठा device_node *host_node;
	काष्ठा mipi_dsi_device *dsi;
	u8 num_dsi_lanes;
	bool use_timing_gen;

	क्रमागत adv7511_type type;
	काष्ठा platक्रमm_device *audio_pdev;

	काष्ठा cec_adapter *cec_adap;
	u8   cec_addr[ADV7511_MAX_ADDRS];
	u8   cec_valid_addrs;
	bool cec_enabled_adap;
	काष्ठा clk *cec_clk;
	u32 cec_clk_freq;
पूर्ण;

#अगर_घोषित CONFIG_DRM_I2C_ADV7511_CEC
पूर्णांक adv7511_cec_init(काष्ठा device *dev, काष्ठा adv7511 *adv7511);
व्योम adv7511_cec_irq_process(काष्ठा adv7511 *adv7511, अचिन्हित पूर्णांक irq1);
#अन्यथा
अटल अंतरभूत पूर्णांक adv7511_cec_init(काष्ठा device *dev, काष्ठा adv7511 *adv7511)
अणु
	अचिन्हित पूर्णांक offset = adv7511->type == ADV7533 ?
						ADV7533_REG_CEC_OFFSET : 0;

	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_CEC_CTRL + offset,
		     ADV7511_CEC_CTRL_POWER_DOWN);
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम adv7533_dsi_घातer_on(काष्ठा adv7511 *adv);
व्योम adv7533_dsi_घातer_off(काष्ठा adv7511 *adv);
व्योम adv7533_mode_set(काष्ठा adv7511 *adv, स्थिर काष्ठा drm_display_mode *mode);
पूर्णांक adv7533_patch_रेजिस्टरs(काष्ठा adv7511 *adv);
पूर्णांक adv7533_patch_cec_रेजिस्टरs(काष्ठा adv7511 *adv);
पूर्णांक adv7533_attach_dsi(काष्ठा adv7511 *adv);
व्योम adv7533_detach_dsi(काष्ठा adv7511 *adv);
पूर्णांक adv7533_parse_dt(काष्ठा device_node *np, काष्ठा adv7511 *adv);

#अगर_घोषित CONFIG_DRM_I2C_ADV7511_AUDIO
पूर्णांक adv7511_audio_init(काष्ठा device *dev, काष्ठा adv7511 *adv7511);
व्योम adv7511_audio_निकास(काष्ठा adv7511 *adv7511);
#अन्यथा /*CONFIG_DRM_I2C_ADV7511_AUDIO */
अटल अंतरभूत पूर्णांक adv7511_audio_init(काष्ठा device *dev, काष्ठा adv7511 *adv7511)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम adv7511_audio_निकास(काष्ठा adv7511 *adv7511)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DRM_I2C_ADV7511_AUDIO */

#पूर्ण_अगर /* __DRM_I2C_ADV7511_H__ */
