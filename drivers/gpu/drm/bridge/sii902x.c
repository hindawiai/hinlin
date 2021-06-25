<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2018 Renesas Electronics
 *
 * Copyright (C) 2016 Aपंचांगel
 *		      Bo Shen <voice.shen@aपंचांगel.com>
 *
 * Authors:	      Bo Shen <voice.shen@aपंचांगel.com>
 *		      Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 *		      Wu, Songjun <Songjun.Wu@aपंचांगel.com>
 *
 * Copyright (C) 2010-2011 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/clk.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश <sound/hdmi-codec.h>

#घोषणा SII902X_TPI_VIDEO_DATA			0x0

#घोषणा SII902X_TPI_PIXEL_REPETITION		0x8
#घोषणा SII902X_TPI_AVI_PIXEL_REP_BUS_24BIT     BIT(5)
#घोषणा SII902X_TPI_AVI_PIXEL_REP_RISING_EDGE   BIT(4)
#घोषणा SII902X_TPI_AVI_PIXEL_REP_4X		3
#घोषणा SII902X_TPI_AVI_PIXEL_REP_2X		1
#घोषणा SII902X_TPI_AVI_PIXEL_REP_NONE		0
#घोषणा SII902X_TPI_CLK_RATIO_HALF		(0 << 6)
#घोषणा SII902X_TPI_CLK_RATIO_1X		(1 << 6)
#घोषणा SII902X_TPI_CLK_RATIO_2X		(2 << 6)
#घोषणा SII902X_TPI_CLK_RATIO_4X		(3 << 6)

#घोषणा SII902X_TPI_AVI_IN_FORMAT		0x9
#घोषणा SII902X_TPI_AVI_INPUT_BITMODE_12BIT	BIT(7)
#घोषणा SII902X_TPI_AVI_INPUT_DITHER		BIT(6)
#घोषणा SII902X_TPI_AVI_INPUT_RANGE_LIMITED	(2 << 2)
#घोषणा SII902X_TPI_AVI_INPUT_RANGE_FULL	(1 << 2)
#घोषणा SII902X_TPI_AVI_INPUT_RANGE_AUTO	(0 << 2)
#घोषणा SII902X_TPI_AVI_INPUT_COLORSPACE_BLACK	(3 << 0)
#घोषणा SII902X_TPI_AVI_INPUT_COLORSPACE_YUV422	(2 << 0)
#घोषणा SII902X_TPI_AVI_INPUT_COLORSPACE_YUV444	(1 << 0)
#घोषणा SII902X_TPI_AVI_INPUT_COLORSPACE_RGB	(0 << 0)

#घोषणा SII902X_TPI_AVI_INFOFRAME		0x0c

#घोषणा SII902X_SYS_CTRL_DATA			0x1a
#घोषणा SII902X_SYS_CTRL_PWR_DWN		BIT(4)
#घोषणा SII902X_SYS_CTRL_AV_MUTE		BIT(3)
#घोषणा SII902X_SYS_CTRL_DDC_BUS_REQ		BIT(2)
#घोषणा SII902X_SYS_CTRL_DDC_BUS_GRTD		BIT(1)
#घोषणा SII902X_SYS_CTRL_OUTPUT_MODE		BIT(0)
#घोषणा SII902X_SYS_CTRL_OUTPUT_HDMI		1
#घोषणा SII902X_SYS_CTRL_OUTPUT_DVI		0

#घोषणा SII902X_REG_CHIPID(n)			(0x1b + (n))

#घोषणा SII902X_PWR_STATE_CTRL			0x1e
#घोषणा SII902X_AVI_POWER_STATE_MSK		GENMASK(1, 0)
#घोषणा SII902X_AVI_POWER_STATE_D(l)		((l) & SII902X_AVI_POWER_STATE_MSK)

/* Audio  */
#घोषणा SII902X_TPI_I2S_ENABLE_MAPPING_REG	0x1f
#घोषणा SII902X_TPI_I2S_CONFIG_FIFO0			(0 << 0)
#घोषणा SII902X_TPI_I2S_CONFIG_FIFO1			(1 << 0)
#घोषणा SII902X_TPI_I2S_CONFIG_FIFO2			(2 << 0)
#घोषणा SII902X_TPI_I2S_CONFIG_FIFO3			(3 << 0)
#घोषणा SII902X_TPI_I2S_LEFT_RIGHT_SWAP			(1 << 2)
#घोषणा SII902X_TPI_I2S_AUTO_DOWNSAMPLE			(1 << 3)
#घोषणा SII902X_TPI_I2S_SELECT_SD0			(0 << 4)
#घोषणा SII902X_TPI_I2S_SELECT_SD1			(1 << 4)
#घोषणा SII902X_TPI_I2S_SELECT_SD2			(2 << 4)
#घोषणा SII902X_TPI_I2S_SELECT_SD3			(3 << 4)
#घोषणा SII902X_TPI_I2S_FIFO_ENABLE			(1 << 7)

#घोषणा SII902X_TPI_I2S_INPUT_CONFIG_REG	0x20
#घोषणा SII902X_TPI_I2S_FIRST_BIT_SHIFT_YES		(0 << 0)
#घोषणा SII902X_TPI_I2S_FIRST_BIT_SHIFT_NO		(1 << 0)
#घोषणा SII902X_TPI_I2S_SD_सूचीECTION_MSB_FIRST		(0 << 1)
#घोषणा SII902X_TPI_I2S_SD_सूचीECTION_LSB_FIRST		(1 << 1)
#घोषणा SII902X_TPI_I2S_SD_JUSTIFY_LEFT			(0 << 2)
#घोषणा SII902X_TPI_I2S_SD_JUSTIFY_RIGHT		(1 << 2)
#घोषणा SII902X_TPI_I2S_WS_POLARITY_LOW			(0 << 3)
#घोषणा SII902X_TPI_I2S_WS_POLARITY_HIGH		(1 << 3)
#घोषणा SII902X_TPI_I2S_MCLK_MULTIPLIER_128		(0 << 4)
#घोषणा SII902X_TPI_I2S_MCLK_MULTIPLIER_256		(1 << 4)
#घोषणा SII902X_TPI_I2S_MCLK_MULTIPLIER_384		(2 << 4)
#घोषणा SII902X_TPI_I2S_MCLK_MULTIPLIER_512		(3 << 4)
#घोषणा SII902X_TPI_I2S_MCLK_MULTIPLIER_768		(4 << 4)
#घोषणा SII902X_TPI_I2S_MCLK_MULTIPLIER_1024		(5 << 4)
#घोषणा SII902X_TPI_I2S_MCLK_MULTIPLIER_1152		(6 << 4)
#घोषणा SII902X_TPI_I2S_MCLK_MULTIPLIER_192		(7 << 4)
#घोषणा SII902X_TPI_I2S_SCK_EDGE_FALLING		(0 << 7)
#घोषणा SII902X_TPI_I2S_SCK_EDGE_RISING			(1 << 7)

#घोषणा SII902X_TPI_I2S_STRM_HDR_BASE	0x21
#घोषणा SII902X_TPI_I2S_STRM_HDR_SIZE	5

#घोषणा SII902X_TPI_AUDIO_CONFIG_BYTE2_REG	0x26
#घोषणा SII902X_TPI_AUDIO_CODING_STREAM_HEADER		(0 << 0)
#घोषणा SII902X_TPI_AUDIO_CODING_PCM			(1 << 0)
#घोषणा SII902X_TPI_AUDIO_CODING_AC3			(2 << 0)
#घोषणा SII902X_TPI_AUDIO_CODING_MPEG1			(3 << 0)
#घोषणा SII902X_TPI_AUDIO_CODING_MP3			(4 << 0)
#घोषणा SII902X_TPI_AUDIO_CODING_MPEG2			(5 << 0)
#घोषणा SII902X_TPI_AUDIO_CODING_AAC			(6 << 0)
#घोषणा SII902X_TPI_AUDIO_CODING_DTS			(7 << 0)
#घोषणा SII902X_TPI_AUDIO_CODING_ATRAC			(8 << 0)
#घोषणा SII902X_TPI_AUDIO_MUTE_DISABLE			(0 << 4)
#घोषणा SII902X_TPI_AUDIO_MUTE_ENABLE			(1 << 4)
#घोषणा SII902X_TPI_AUDIO_LAYOUT_2_CHANNELS		(0 << 5)
#घोषणा SII902X_TPI_AUDIO_LAYOUT_8_CHANNELS		(1 << 5)
#घोषणा SII902X_TPI_AUDIO_INTERFACE_DISABLE		(0 << 6)
#घोषणा SII902X_TPI_AUDIO_INTERFACE_SPDIF		(1 << 6)
#घोषणा SII902X_TPI_AUDIO_INTERFACE_I2S			(2 << 6)

#घोषणा SII902X_TPI_AUDIO_CONFIG_BYTE3_REG	0x27
#घोषणा SII902X_TPI_AUDIO_FREQ_STREAM			(0 << 3)
#घोषणा SII902X_TPI_AUDIO_FREQ_32KHZ			(1 << 3)
#घोषणा SII902X_TPI_AUDIO_FREQ_44KHZ			(2 << 3)
#घोषणा SII902X_TPI_AUDIO_FREQ_48KHZ			(3 << 3)
#घोषणा SII902X_TPI_AUDIO_FREQ_88KHZ			(4 << 3)
#घोषणा SII902X_TPI_AUDIO_FREQ_96KHZ			(5 << 3)
#घोषणा SII902X_TPI_AUDIO_FREQ_176KHZ			(6 << 3)
#घोषणा SII902X_TPI_AUDIO_FREQ_192KHZ			(7 << 3)
#घोषणा SII902X_TPI_AUDIO_SAMPLE_SIZE_STREAM		(0 << 6)
#घोषणा SII902X_TPI_AUDIO_SAMPLE_SIZE_16		(1 << 6)
#घोषणा SII902X_TPI_AUDIO_SAMPLE_SIZE_20		(2 << 6)
#घोषणा SII902X_TPI_AUDIO_SAMPLE_SIZE_24		(3 << 6)

#घोषणा SII902X_TPI_AUDIO_CONFIG_BYTE4_REG	0x28

#घोषणा SII902X_INT_ENABLE			0x3c
#घोषणा SII902X_INT_STATUS			0x3d
#घोषणा SII902X_HOTPLUG_EVENT			BIT(0)
#घोषणा SII902X_PLUGGED_STATUS			BIT(2)

#घोषणा SII902X_REG_TPI_RQB			0xc7

/* Indirect पूर्णांकernal रेजिस्टर access */
#घोषणा SII902X_IND_SET_PAGE			0xbc
#घोषणा SII902X_IND_OFFSET			0xbd
#घोषणा SII902X_IND_VALUE			0xbe

#घोषणा SII902X_TPI_MISC_INFOFRAME_BASE		0xbf
#घोषणा SII902X_TPI_MISC_INFOFRAME_END		0xde
#घोषणा SII902X_TPI_MISC_INFOFRAME_SIZE	\
	(SII902X_TPI_MISC_INFOFRAME_END - SII902X_TPI_MISC_INFOFRAME_BASE)

#घोषणा SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS	500

#घोषणा SII902X_AUDIO_PORT_INDEX		3

काष्ठा sii902x अणु
	काष्ठा i2c_client *i2c;
	काष्ठा regmap *regmap;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा i2c_mux_core *i2cmux;
	काष्ठा regulator_bulk_data supplies[2];
	/*
	 * Mutex protects audio and video functions from पूर्णांकerfering
	 * each other, by keeping their i2c command sequences atomic.
	 */
	काष्ठा mutex mutex;
	काष्ठा sii902x_audio अणु
		काष्ठा platक्रमm_device *pdev;
		काष्ठा clk *mclk;
		u32 i2s_fअगरo_sequence[4];
	पूर्ण audio;
पूर्ण;

अटल पूर्णांक sii902x_पढ़ो_unlocked(काष्ठा i2c_client *i2c, u8 reg, u8 *val)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक ret;

	ret = __i2c_smbus_xfer(i2c->adapter, i2c->addr, i2c->flags,
			       I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data);

	अगर (ret < 0)
		वापस ret;

	*val = data.byte;
	वापस 0;
पूर्ण

अटल पूर्णांक sii902x_ग_लिखो_unlocked(काष्ठा i2c_client *i2c, u8 reg, u8 val)
अणु
	जोड़ i2c_smbus_data data;

	data.byte = val;

	वापस __i2c_smbus_xfer(i2c->adapter, i2c->addr, i2c->flags,
				I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA,
				&data);
पूर्ण

अटल पूर्णांक sii902x_update_bits_unlocked(काष्ठा i2c_client *i2c, u8 reg, u8 mask,
					u8 val)
अणु
	पूर्णांक ret;
	u8 status;

	ret = sii902x_पढ़ो_unlocked(i2c, reg, &status);
	अगर (ret)
		वापस ret;
	status &= ~mask;
	status |= val & mask;
	वापस sii902x_ग_लिखो_unlocked(i2c, reg, status);
पूर्ण

अटल अंतरभूत काष्ठा sii902x *bridge_to_sii902x(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा sii902x, bridge);
पूर्ण

अटल अंतरभूत काष्ठा sii902x *connector_to_sii902x(काष्ठा drm_connector *con)
अणु
	वापस container_of(con, काष्ठा sii902x, connector);
पूर्ण

अटल व्योम sii902x_reset(काष्ठा sii902x *sii902x)
अणु
	अगर (!sii902x->reset_gpio)
		वापस;

	gpiod_set_value(sii902x->reset_gpio, 1);

	/* The datasheet says treset-min = 100us. Make it 150us to be sure. */
	usleep_range(150, 200);

	gpiod_set_value(sii902x->reset_gpio, 0);
पूर्ण

अटल क्रमागत drm_connector_status
sii902x_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा sii902x *sii902x = connector_to_sii902x(connector);
	अचिन्हित पूर्णांक status;

	mutex_lock(&sii902x->mutex);

	regmap_पढ़ो(sii902x->regmap, SII902X_INT_STATUS, &status);

	mutex_unlock(&sii902x->mutex);

	वापस (status & SII902X_PLUGGED_STATUS) ?
	       connector_status_connected : connector_status_disconnected;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sii902x_connector_funcs = अणु
	.detect = sii902x_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक sii902x_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा sii902x *sii902x = connector_to_sii902x(connector);
	u32 bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;
	u8 output_mode = SII902X_SYS_CTRL_OUTPUT_DVI;
	काष्ठा edid *edid;
	पूर्णांक num = 0, ret;

	mutex_lock(&sii902x->mutex);

	edid = drm_get_edid(connector, sii902x->i2cmux->adapter[0]);
	drm_connector_update_edid_property(connector, edid);
	अगर (edid) अणु
		अगर (drm_detect_hdmi_monitor(edid))
			output_mode = SII902X_SYS_CTRL_OUTPUT_HDMI;

		num = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण

	ret = drm_display_info_set_bus_क्रमmats(&connector->display_info,
					       &bus_क्रमmat, 1);
	अगर (ret)
		जाओ error_out;

	ret = regmap_update_bits(sii902x->regmap, SII902X_SYS_CTRL_DATA,
				 SII902X_SYS_CTRL_OUTPUT_MODE, output_mode);
	अगर (ret)
		जाओ error_out;

	ret = num;

error_out:
	mutex_unlock(&sii902x->mutex);

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status sii902x_mode_valid(काष्ठा drm_connector *connector,
					       काष्ठा drm_display_mode *mode)
अणु
	/* TODO: check mode */

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs sii902x_connector_helper_funcs = अणु
	.get_modes = sii902x_get_modes,
	.mode_valid = sii902x_mode_valid,
पूर्ण;

अटल व्योम sii902x_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sii902x *sii902x = bridge_to_sii902x(bridge);

	mutex_lock(&sii902x->mutex);

	regmap_update_bits(sii902x->regmap, SII902X_SYS_CTRL_DATA,
			   SII902X_SYS_CTRL_PWR_DWN,
			   SII902X_SYS_CTRL_PWR_DWN);

	mutex_unlock(&sii902x->mutex);
पूर्ण

अटल व्योम sii902x_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sii902x *sii902x = bridge_to_sii902x(bridge);

	mutex_lock(&sii902x->mutex);

	regmap_update_bits(sii902x->regmap, SII902X_PWR_STATE_CTRL,
			   SII902X_AVI_POWER_STATE_MSK,
			   SII902X_AVI_POWER_STATE_D(0));
	regmap_update_bits(sii902x->regmap, SII902X_SYS_CTRL_DATA,
			   SII902X_SYS_CTRL_PWR_DWN, 0);

	mutex_unlock(&sii902x->mutex);
पूर्ण

अटल व्योम sii902x_bridge_mode_set(काष्ठा drm_bridge *bridge,
				    स्थिर काष्ठा drm_display_mode *mode,
				    स्थिर काष्ठा drm_display_mode *adj)
अणु
	काष्ठा sii902x *sii902x = bridge_to_sii902x(bridge);
	काष्ठा regmap *regmap = sii902x->regmap;
	u8 buf[HDMI_INFOFRAME_SIZE(AVI)];
	काष्ठा hdmi_avi_infoframe frame;
	u16 pixel_घड़ी_10kHz = adj->घड़ी / 10;
	पूर्णांक ret;

	buf[0] = pixel_घड़ी_10kHz & 0xff;
	buf[1] = pixel_घड़ी_10kHz >> 8;
	buf[2] = drm_mode_vrefresh(adj);
	buf[3] = 0x00;
	buf[4] = adj->hdisplay;
	buf[5] = adj->hdisplay >> 8;
	buf[6] = adj->vdisplay;
	buf[7] = adj->vdisplay >> 8;
	buf[8] = SII902X_TPI_CLK_RATIO_1X | SII902X_TPI_AVI_PIXEL_REP_NONE |
		 SII902X_TPI_AVI_PIXEL_REP_BUS_24BIT;
	buf[9] = SII902X_TPI_AVI_INPUT_RANGE_AUTO |
		 SII902X_TPI_AVI_INPUT_COLORSPACE_RGB;

	mutex_lock(&sii902x->mutex);

	ret = regmap_bulk_ग_लिखो(regmap, SII902X_TPI_VIDEO_DATA, buf, 10);
	अगर (ret)
		जाओ out;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &sii902x->connector, adj);
	अगर (ret < 0) अणु
		DRM_ERROR("couldn't fill AVI infoframe\n");
		जाओ out;
	पूर्ण

	ret = hdmi_avi_infoframe_pack(&frame, buf, माप(buf));
	अगर (ret < 0) अणु
		DRM_ERROR("failed to pack AVI infoframe: %d\n", ret);
		जाओ out;
	पूर्ण

	/* Do not send the infoframe header, but keep the CRC field. */
	regmap_bulk_ग_लिखो(regmap, SII902X_TPI_AVI_INFOFRAME,
			  buf + HDMI_INFOFRAME_HEADER_SIZE - 1,
			  HDMI_AVI_INFOFRAME_SIZE + 1);

out:
	mutex_unlock(&sii902x->mutex);
पूर्ण

अटल पूर्णांक sii902x_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा sii902x *sii902x = bridge_to_sii902x(bridge);
	काष्ठा drm_device *drm = bridge->dev;
	पूर्णांक ret;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR) अणु
		DRM_ERROR("Fix bridge driver to make connector optional!");
		वापस -EINVAL;
	पूर्ण

	drm_connector_helper_add(&sii902x->connector,
				 &sii902x_connector_helper_funcs);

	अगर (!drm_core_check_feature(drm, DRIVER_ATOMIC)) अणु
		dev_err(&sii902x->i2c->dev,
			"sii902x driver is only compatible with DRM devices supporting atomic updates\n");
		वापस -ENOTSUPP;
	पूर्ण

	ret = drm_connector_init(drm, &sii902x->connector,
				 &sii902x_connector_funcs,
				 DRM_MODE_CONNECTOR_HDMIA);
	अगर (ret)
		वापस ret;

	अगर (sii902x->i2c->irq > 0)
		sii902x->connector.polled = DRM_CONNECTOR_POLL_HPD;
	अन्यथा
		sii902x->connector.polled = DRM_CONNECTOR_POLL_CONNECT;

	drm_connector_attach_encoder(&sii902x->connector, bridge->encoder);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs sii902x_bridge_funcs = अणु
	.attach = sii902x_bridge_attach,
	.mode_set = sii902x_bridge_mode_set,
	.disable = sii902x_bridge_disable,
	.enable = sii902x_bridge_enable,
पूर्ण;

अटल पूर्णांक sii902x_mute(काष्ठा sii902x *sii902x, bool mute)
अणु
	काष्ठा device *dev = &sii902x->i2c->dev;
	अचिन्हित पूर्णांक val = mute ? SII902X_TPI_AUDIO_MUTE_ENABLE :
		SII902X_TPI_AUDIO_MUTE_DISABLE;

	dev_dbg(dev, "%s: %s\n", __func__, mute ? "Muted" : "Unmuted");

	वापस regmap_update_bits(sii902x->regmap,
				  SII902X_TPI_AUDIO_CONFIG_BYTE2_REG,
				  SII902X_TPI_AUDIO_MUTE_ENABLE, val);
पूर्ण

अटल स्थिर पूर्णांक sii902x_mclk_भाग_प्रकारable[] = अणु
	128, 256, 384, 512, 768, 1024, 1152, 192 पूर्ण;

अटल पूर्णांक sii902x_select_mclk_भाग(u8 *i2s_config_reg, अचिन्हित पूर्णांक rate,
				   अचिन्हित पूर्णांक mclk)
अणु
	पूर्णांक भाग = mclk / rate;
	पूर्णांक distance = 100000;
	u8 i, nearest = 0;

	क्रम (i = 0; i < ARRAY_SIZE(sii902x_mclk_भाग_प्रकारable); i++) अणु
		अचिन्हित पूर्णांक d = असल(भाग - sii902x_mclk_भाग_प्रकारable[i]);

		अगर (d >= distance)
			जारी;

		nearest = i;
		distance = d;
		अगर (d == 0)
			अवरोध;
	पूर्ण

	*i2s_config_reg |= nearest << 4;

	वापस sii902x_mclk_भाग_प्रकारable[nearest];
पूर्ण

अटल स्थिर काष्ठा sii902x_sample_freq अणु
	u32 freq;
	u8 val;
पूर्ण sii902x_sample_freq[] = अणु
	अणु .freq = 32000,	.val = SII902X_TPI_AUDIO_FREQ_32KHZ पूर्ण,
	अणु .freq = 44000,	.val = SII902X_TPI_AUDIO_FREQ_44KHZ पूर्ण,
	अणु .freq = 48000,	.val = SII902X_TPI_AUDIO_FREQ_48KHZ पूर्ण,
	अणु .freq = 88000,	.val = SII902X_TPI_AUDIO_FREQ_88KHZ पूर्ण,
	अणु .freq = 96000,	.val = SII902X_TPI_AUDIO_FREQ_96KHZ पूर्ण,
	अणु .freq = 176000,	.val = SII902X_TPI_AUDIO_FREQ_176KHZ पूर्ण,
	अणु .freq = 192000,	.val = SII902X_TPI_AUDIO_FREQ_192KHZ पूर्ण,
पूर्ण;

अटल पूर्णांक sii902x_audio_hw_params(काष्ठा device *dev, व्योम *data,
				   काष्ठा hdmi_codec_daअगरmt *daअगरmt,
				   काष्ठा hdmi_codec_params *params)
अणु
	काष्ठा sii902x *sii902x = dev_get_drvdata(dev);
	u8 i2s_config_reg = SII902X_TPI_I2S_SD_सूचीECTION_MSB_FIRST;
	u8 config_byte2_reg = (SII902X_TPI_AUDIO_INTERFACE_I2S |
			       SII902X_TPI_AUDIO_MUTE_ENABLE |
			       SII902X_TPI_AUDIO_CODING_PCM);
	u8 config_byte3_reg = 0;
	u8 infoframe_buf[HDMI_INFOFRAME_SIZE(AUDIO)];
	अचिन्हित दीर्घ mclk_rate;
	पूर्णांक i, ret;

	अगर (daअगरmt->bit_clk_master || daअगरmt->frame_clk_master) अणु
		dev_dbg(dev, "%s: I2S master mode not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	चयन (daअगरmt->fmt) अणु
	हाल HDMI_I2S:
		i2s_config_reg |= SII902X_TPI_I2S_FIRST_BIT_SHIFT_YES |
			SII902X_TPI_I2S_SD_JUSTIFY_LEFT;
		अवरोध;
	हाल HDMI_RIGHT_J:
		i2s_config_reg |= SII902X_TPI_I2S_SD_JUSTIFY_RIGHT;
		अवरोध;
	हाल HDMI_LEFT_J:
		i2s_config_reg |= SII902X_TPI_I2S_SD_JUSTIFY_LEFT;
		अवरोध;
	शेष:
		dev_dbg(dev, "%s: Unsupported i2s format %u\n", __func__,
			daअगरmt->fmt);
		वापस -EINVAL;
	पूर्ण

	अगर (daअगरmt->bit_clk_inv)
		i2s_config_reg |= SII902X_TPI_I2S_SCK_EDGE_FALLING;
	अन्यथा
		i2s_config_reg |= SII902X_TPI_I2S_SCK_EDGE_RISING;

	अगर (daअगरmt->frame_clk_inv)
		i2s_config_reg |= SII902X_TPI_I2S_WS_POLARITY_LOW;
	अन्यथा
		i2s_config_reg |= SII902X_TPI_I2S_WS_POLARITY_HIGH;

	अगर (params->channels > 2)
		config_byte2_reg |= SII902X_TPI_AUDIO_LAYOUT_8_CHANNELS;
	अन्यथा
		config_byte2_reg |= SII902X_TPI_AUDIO_LAYOUT_2_CHANNELS;

	चयन (params->sample_width) अणु
	हाल 16:
		config_byte3_reg |= SII902X_TPI_AUDIO_SAMPLE_SIZE_16;
		अवरोध;
	हाल 20:
		config_byte3_reg |= SII902X_TPI_AUDIO_SAMPLE_SIZE_20;
		अवरोध;
	हाल 24:
	हाल 32:
		config_byte3_reg |= SII902X_TPI_AUDIO_SAMPLE_SIZE_24;
		अवरोध;
	शेष:
		dev_err(dev, "%s: Unsupported sample width %u\n", __func__,
			params->sample_width);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sii902x_sample_freq); i++) अणु
		अगर (params->sample_rate == sii902x_sample_freq[i].freq) अणु
			config_byte3_reg |= sii902x_sample_freq[i].val;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(sii902x->audio.mclk);
	अगर (ret) अणु
		dev_err(dev, "Enabling mclk failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (sii902x->audio.mclk) अणु
		mclk_rate = clk_get_rate(sii902x->audio.mclk);
		ret = sii902x_select_mclk_भाग(&i2s_config_reg,
					      params->sample_rate, mclk_rate);
		अगर (mclk_rate != ret * params->sample_rate)
			dev_dbg(dev, "Inaccurate reference clock (%ld/%d != %u)\n",
				mclk_rate, ret, params->sample_rate);
	पूर्ण

	mutex_lock(&sii902x->mutex);

	ret = regmap_ग_लिखो(sii902x->regmap,
			   SII902X_TPI_AUDIO_CONFIG_BYTE2_REG,
			   config_byte2_reg);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_ग_लिखो(sii902x->regmap, SII902X_TPI_I2S_INPUT_CONFIG_REG,
			   i2s_config_reg);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(sii902x->audio.i2s_fअगरo_sequence) &&
		    sii902x->audio.i2s_fअगरo_sequence[i]; i++)
		regmap_ग_लिखो(sii902x->regmap,
			     SII902X_TPI_I2S_ENABLE_MAPPING_REG,
			     sii902x->audio.i2s_fअगरo_sequence[i]);

	ret = regmap_ग_लिखो(sii902x->regmap, SII902X_TPI_AUDIO_CONFIG_BYTE3_REG,
			   config_byte3_reg);
	अगर (ret)
		जाओ out;

	ret = regmap_bulk_ग_लिखो(sii902x->regmap, SII902X_TPI_I2S_STRM_HDR_BASE,
				params->iec.status,
				min((माप_प्रकार) SII902X_TPI_I2S_STRM_HDR_SIZE,
				    माप(params->iec.status)));
	अगर (ret)
		जाओ out;

	ret = hdmi_audio_infoframe_pack(&params->cea, infoframe_buf,
					माप(infoframe_buf));
	अगर (ret < 0) अणु
		dev_err(dev, "%s: Failed to pack audio infoframe: %d\n",
			__func__, ret);
		जाओ out;
	पूर्ण

	ret = regmap_bulk_ग_लिखो(sii902x->regmap,
				SII902X_TPI_MISC_INFOFRAME_BASE,
				infoframe_buf,
				min(ret, SII902X_TPI_MISC_INFOFRAME_SIZE));
	अगर (ret)
		जाओ out;

	/* Decode Level 0 Packets */
	ret = regmap_ग_लिखो(sii902x->regmap, SII902X_IND_SET_PAGE, 0x02);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(sii902x->regmap, SII902X_IND_OFFSET, 0x24);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(sii902x->regmap, SII902X_IND_VALUE, 0x02);
	अगर (ret)
		जाओ out;

	dev_dbg(dev, "%s: hdmi audio enabled\n", __func__);
out:
	mutex_unlock(&sii902x->mutex);

	अगर (ret) अणु
		clk_disable_unprepare(sii902x->audio.mclk);
		dev_err(dev, "%s: hdmi audio enable failed: %d\n", __func__,
			ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sii902x_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा sii902x *sii902x = dev_get_drvdata(dev);

	mutex_lock(&sii902x->mutex);

	regmap_ग_लिखो(sii902x->regmap, SII902X_TPI_AUDIO_CONFIG_BYTE2_REG,
		     SII902X_TPI_AUDIO_INTERFACE_DISABLE);

	mutex_unlock(&sii902x->mutex);

	clk_disable_unprepare(sii902x->audio.mclk);
पूर्ण

अटल पूर्णांक sii902x_audio_mute(काष्ठा device *dev, व्योम *data,
			      bool enable, पूर्णांक direction)
अणु
	काष्ठा sii902x *sii902x = dev_get_drvdata(dev);

	mutex_lock(&sii902x->mutex);

	sii902x_mute(sii902x, enable);

	mutex_unlock(&sii902x->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक sii902x_audio_get_eld(काष्ठा device *dev, व्योम *data,
				 uपूर्णांक8_t *buf, माप_प्रकार len)
अणु
	काष्ठा sii902x *sii902x = dev_get_drvdata(dev);

	mutex_lock(&sii902x->mutex);

	स_नकल(buf, sii902x->connector.eld,
	       min(माप(sii902x->connector.eld), len));

	mutex_unlock(&sii902x->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक sii902x_audio_get_dai_id(काष्ठा snd_soc_component *component,
				    काष्ठा device_node *endpoपूर्णांक)
अणु
	काष्ठा of_endpoपूर्णांक of_ep;
	पूर्णांक ret;

	ret = of_graph_parse_endpoपूर्णांक(endpoपूर्णांक, &of_ep);
	अगर (ret < 0)
		वापस ret;

	/*
	 * HDMI sound should be located at reg = <3>
	 * Return expected DAI index 0.
	 */
	अगर (of_ep.port == SII902X_AUDIO_PORT_INDEX)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops sii902x_audio_codec_ops = अणु
	.hw_params = sii902x_audio_hw_params,
	.audio_shutकरोwn = sii902x_audio_shutकरोwn,
	.mute_stream = sii902x_audio_mute,
	.get_eld = sii902x_audio_get_eld,
	.get_dai_id = sii902x_audio_get_dai_id,
	.no_capture_mute = 1,
पूर्ण;

अटल पूर्णांक sii902x_audio_codec_init(काष्ठा sii902x *sii902x,
				    काष्ठा device *dev)
अणु
	अटल स्थिर u8 audio_fअगरo_id[] = अणु
		SII902X_TPI_I2S_CONFIG_FIFO0,
		SII902X_TPI_I2S_CONFIG_FIFO1,
		SII902X_TPI_I2S_CONFIG_FIFO2,
		SII902X_TPI_I2S_CONFIG_FIFO3,
	पूर्ण;
	अटल स्थिर u8 i2s_lane_id[] = अणु
		SII902X_TPI_I2S_SELECT_SD0,
		SII902X_TPI_I2S_SELECT_SD1,
		SII902X_TPI_I2S_SELECT_SD2,
		SII902X_TPI_I2S_SELECT_SD3,
	पूर्ण;
	काष्ठा hdmi_codec_pdata codec_data = अणु
		.ops = &sii902x_audio_codec_ops,
		.i2s = 1, /* Only i2s support क्रम now. */
		.spdअगर = 0,
		.max_i2s_channels = 0,
	पूर्ण;
	u8 lanes[4];
	पूर्णांक num_lanes, i;

	अगर (!of_property_पढ़ो_bool(dev->of_node, "#sound-dai-cells")) अणु
		dev_dbg(dev, "%s: No \"#sound-dai-cells\", no audio\n",
			__func__);
		वापस 0;
	पूर्ण

	num_lanes = of_property_पढ़ो_variable_u8_array(dev->of_node,
						       "sil,i2s-data-lanes",
						       lanes, 1,
						       ARRAY_SIZE(lanes));

	अगर (num_lanes == -EINVAL) अणु
		dev_dbg(dev,
			"%s: No \"sil,i2s-data-lanes\", use default <0>\n",
			__func__);
		num_lanes = 1;
		lanes[0] = 0;
	पूर्ण अन्यथा अगर (num_lanes < 0) अणु
		dev_err(dev,
			"%s: Error gettin \"sil,i2s-data-lanes\": %d\n",
			__func__, num_lanes);
		वापस num_lanes;
	पूर्ण
	codec_data.max_i2s_channels = 2 * num_lanes;

	क्रम (i = 0; i < num_lanes; i++)
		sii902x->audio.i2s_fअगरo_sequence[i] |= audio_fअगरo_id[i] |
			i2s_lane_id[lanes[i]] |	SII902X_TPI_I2S_FIFO_ENABLE;

	sii902x->audio.mclk = devm_clk_get_optional(dev, "mclk");
	अगर (IS_ERR(sii902x->audio.mclk)) अणु
		dev_err(dev, "%s: No clock (audio mclk) found: %ld\n",
			__func__, PTR_ERR(sii902x->audio.mclk));
		वापस PTR_ERR(sii902x->audio.mclk);
	पूर्ण

	sii902x->audio.pdev = platक्रमm_device_रेजिस्टर_data(
		dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
		&codec_data, माप(codec_data));

	वापस PTR_ERR_OR_ZERO(sii902x->audio.pdev);
पूर्ण

अटल स्थिर काष्ठा regmap_range sii902x_अस्थिर_ranges[] = अणु
	अणु .range_min = 0, .range_max = 0xff पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sii902x_अस्थिर_table = अणु
	.yes_ranges = sii902x_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(sii902x_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config sii902x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.disable_locking = true, /* काष्ठा sii902x mutex should be enough */
	.max_रेजिस्टर = SII902X_TPI_MISC_INFOFRAME_END,
	.अस्थिर_table = &sii902x_अस्थिर_table,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल irqवापस_t sii902x_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sii902x *sii902x = data;
	अचिन्हित पूर्णांक status = 0;

	mutex_lock(&sii902x->mutex);

	regmap_पढ़ो(sii902x->regmap, SII902X_INT_STATUS, &status);
	regmap_ग_लिखो(sii902x->regmap, SII902X_INT_STATUS, status);

	mutex_unlock(&sii902x->mutex);

	अगर ((status & SII902X_HOTPLUG_EVENT) && sii902x->bridge.dev)
		drm_helper_hpd_irq_event(sii902x->bridge.dev);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * The purpose of sii902x_i2c_bypass_select is to enable the pass through
 * mode of the HDMI transmitter. Do not use regmap from within this function,
 * only use sii902x_*_unlocked functions to पढ़ो/modअगरy/ग_लिखो रेजिस्टरs.
 * We are holding the parent adapter lock here, keep this in mind beक्रमe
 * adding more i2c transactions.
 *
 * Also, since SII902X_SYS_CTRL_DATA is used with regmap_update_bits अन्यथाwhere
 * in this driver, we need to make sure that we only touch 0x1A[2:1] from
 * within sii902x_i2c_bypass_select and sii902x_i2c_bypass_deselect, and that
 * we leave the reमुख्यing bits as we have found them.
 */
अटल पूर्णांक sii902x_i2c_bypass_select(काष्ठा i2c_mux_core *mux, u32 chan_id)
अणु
	काष्ठा sii902x *sii902x = i2c_mux_priv(mux);
	काष्ठा device *dev = &sii902x->i2c->dev;
	अचिन्हित दीर्घ समयout;
	u8 status;
	पूर्णांक ret;

	ret = sii902x_update_bits_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					   SII902X_SYS_CTRL_DDC_BUS_REQ,
					   SII902X_SYS_CTRL_DDC_BUS_REQ);
	अगर (ret)
		वापस ret;

	समयout = jअगरfies +
		  msecs_to_jअगरfies(SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS);
	करो अणु
		ret = sii902x_पढ़ो_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					    &status);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (!(status & SII902X_SYS_CTRL_DDC_BUS_GRTD) &&
		 समय_beक्रमe(jअगरfies, समयout));

	अगर (!(status & SII902X_SYS_CTRL_DDC_BUS_GRTD)) अणु
		dev_err(dev, "Failed to acquire the i2c bus\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस sii902x_ग_लिखो_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
				      status);
पूर्ण

/*
 * The purpose of sii902x_i2c_bypass_deselect is to disable the pass through
 * mode of the HDMI transmitter. Do not use regmap from within this function,
 * only use sii902x_*_unlocked functions to पढ़ो/modअगरy/ग_लिखो रेजिस्टरs.
 * We are holding the parent adapter lock here, keep this in mind beक्रमe
 * adding more i2c transactions.
 *
 * Also, since SII902X_SYS_CTRL_DATA is used with regmap_update_bits अन्यथाwhere
 * in this driver, we need to make sure that we only touch 0x1A[2:1] from
 * within sii902x_i2c_bypass_select and sii902x_i2c_bypass_deselect, and that
 * we leave the reमुख्यing bits as we have found them.
 */
अटल पूर्णांक sii902x_i2c_bypass_deselect(काष्ठा i2c_mux_core *mux, u32 chan_id)
अणु
	काष्ठा sii902x *sii902x = i2c_mux_priv(mux);
	काष्ठा device *dev = &sii902x->i2c->dev;
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक retries;
	u8 status;
	पूर्णांक ret;

	/*
	 * When the HDMI transmitter is in pass through mode, we need an
	 * (unकरोcumented) additional delay between STOP and START conditions
	 * to guarantee the bus won't get stuck.
	 */
	udelay(30);

	/*
	 * Someबार the I2C bus can stall after failure to use the
	 * EDID channel. Retry a few बार to see अगर things clear
	 * up, अन्यथा जारी anyway.
	 */
	retries = 5;
	करो अणु
		ret = sii902x_पढ़ो_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					    &status);
		retries--;
	पूर्ण जबतक (ret && retries);
	अगर (ret) अणु
		dev_err(dev, "failed to read status (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = sii902x_update_bits_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					   SII902X_SYS_CTRL_DDC_BUS_REQ |
					   SII902X_SYS_CTRL_DDC_BUS_GRTD, 0);
	अगर (ret)
		वापस ret;

	समयout = jअगरfies +
		  msecs_to_jअगरfies(SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS);
	करो अणु
		ret = sii902x_पढ़ो_unlocked(sii902x->i2c, SII902X_SYS_CTRL_DATA,
					    &status);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (status & (SII902X_SYS_CTRL_DDC_BUS_REQ |
			   SII902X_SYS_CTRL_DDC_BUS_GRTD) &&
		 समय_beक्रमe(jअगरfies, समयout));

	अगर (status & (SII902X_SYS_CTRL_DDC_BUS_REQ |
		      SII902X_SYS_CTRL_DDC_BUS_GRTD)) अणु
		dev_err(dev, "failed to release the i2c bus\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_timings शेष_sii902x_timings = अणु
	.input_bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE
		 | DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE
		 | DRM_BUS_FLAG_DE_HIGH,
पूर्ण;

अटल पूर्णांक sii902x_init(काष्ठा sii902x *sii902x)
अणु
	काष्ठा device *dev = &sii902x->i2c->dev;
	अचिन्हित पूर्णांक status = 0;
	u8 chipid[4];
	पूर्णांक ret;

	sii902x_reset(sii902x);

	ret = regmap_ग_लिखो(sii902x->regmap, SII902X_REG_TPI_RQB, 0x0);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_पढ़ो(sii902x->regmap, SII902X_REG_CHIPID(0),
			       &chipid, 4);
	अगर (ret) अणु
		dev_err(dev, "regmap_read failed %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (chipid[0] != 0xb0) अणु
		dev_err(dev, "Invalid chipid: %02x (expecting 0xb0)\n",
			chipid[0]);
		वापस -EINVAL;
	पूर्ण

	/* Clear all pending पूर्णांकerrupts */
	regmap_पढ़ो(sii902x->regmap, SII902X_INT_STATUS, &status);
	regmap_ग_लिखो(sii902x->regmap, SII902X_INT_STATUS, status);

	अगर (sii902x->i2c->irq > 0) अणु
		regmap_ग_लिखो(sii902x->regmap, SII902X_INT_ENABLE,
			     SII902X_HOTPLUG_EVENT);

		ret = devm_request_thपढ़ोed_irq(dev, sii902x->i2c->irq, शून्य,
						sii902x_पूर्णांकerrupt,
						IRQF_ONESHOT, dev_name(dev),
						sii902x);
		अगर (ret)
			वापस ret;
	पूर्ण

	sii902x->bridge.funcs = &sii902x_bridge_funcs;
	sii902x->bridge.of_node = dev->of_node;
	sii902x->bridge.timings = &शेष_sii902x_timings;
	drm_bridge_add(&sii902x->bridge);

	sii902x_audio_codec_init(sii902x, dev);

	i2c_set_clientdata(sii902x->i2c, sii902x);

	sii902x->i2cmux = i2c_mux_alloc(sii902x->i2c->adapter, dev,
					1, 0, I2C_MUX_GATE,
					sii902x_i2c_bypass_select,
					sii902x_i2c_bypass_deselect);
	अगर (!sii902x->i2cmux)
		वापस -ENOMEM;

	sii902x->i2cmux->priv = sii902x;
	वापस i2c_mux_add_adapter(sii902x->i2cmux, 0, 0, 0);
पूर्ण

अटल पूर्णांक sii902x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा sii902x *sii902x;
	पूर्णांक ret;

	ret = i2c_check_functionality(client->adapter,
				      I2C_FUNC_SMBUS_BYTE_DATA);
	अगर (!ret) अणु
		dev_err(dev, "I2C adapter not suitable\n");
		वापस -EIO;
	पूर्ण

	sii902x = devm_kzalloc(dev, माप(*sii902x), GFP_KERNEL);
	अगर (!sii902x)
		वापस -ENOMEM;

	sii902x->i2c = client;
	sii902x->regmap = devm_regmap_init_i2c(client, &sii902x_regmap_config);
	अगर (IS_ERR(sii902x->regmap))
		वापस PTR_ERR(sii902x->regmap);

	sii902x->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(sii902x->reset_gpio)) अणु
		dev_err(dev, "Failed to retrieve/request reset gpio: %ld\n",
			PTR_ERR(sii902x->reset_gpio));
		वापस PTR_ERR(sii902x->reset_gpio);
	पूर्ण

	mutex_init(&sii902x->mutex);

	sii902x->supplies[0].supply = "iovcc";
	sii902x->supplies[1].supply = "cvcc12";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(sii902x->supplies),
				      sii902x->supplies);
	अगर (ret < 0)
		वापस ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(sii902x->supplies),
				    sii902x->supplies);
	अगर (ret < 0) अणु
		dev_err_probe(dev, ret, "Failed to enable supplies");
		वापस ret;
	पूर्ण

	ret = sii902x_init(sii902x);
	अगर (ret < 0) अणु
		regulator_bulk_disable(ARRAY_SIZE(sii902x->supplies),
				       sii902x->supplies);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sii902x_हटाओ(काष्ठा i2c_client *client)

अणु
	काष्ठा sii902x *sii902x = i2c_get_clientdata(client);

	i2c_mux_del_adapters(sii902x->i2cmux);
	drm_bridge_हटाओ(&sii902x->bridge);
	regulator_bulk_disable(ARRAY_SIZE(sii902x->supplies),
			       sii902x->supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sii902x_dt_ids[] = अणु
	अणु .compatible = "sil,sii9022", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sii902x_dt_ids);

अटल स्थिर काष्ठा i2c_device_id sii902x_i2c_ids[] = अणु
	अणु "sii9022", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sii902x_i2c_ids);

अटल काष्ठा i2c_driver sii902x_driver = अणु
	.probe = sii902x_probe,
	.हटाओ = sii902x_हटाओ,
	.driver = अणु
		.name = "sii902x",
		.of_match_table = sii902x_dt_ids,
	पूर्ण,
	.id_table = sii902x_i2c_ids,
पूर्ण;
module_i2c_driver(sii902x_driver);

MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_DESCRIPTION("SII902x RGB -> HDMI bridges");
MODULE_LICENSE("GPL");
