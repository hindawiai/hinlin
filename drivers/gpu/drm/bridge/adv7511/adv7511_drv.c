<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog Devices ADV7511 HDMI transmitter driver
 *
 * Copyright 2012 Analog Devices Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>

#समावेश <media/cec.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "adv7511.h"

/* ADI recommended values क्रम proper operation. */
अटल स्थिर काष्ठा reg_sequence adv7511_fixed_रेजिस्टरs[] = अणु
	अणु 0x98, 0x03 पूर्ण,
	अणु 0x9a, 0xe0 पूर्ण,
	अणु 0x9c, 0x30 पूर्ण,
	अणु 0x9d, 0x61 पूर्ण,
	अणु 0xa2, 0xa4 पूर्ण,
	अणु 0xa3, 0xa4 पूर्ण,
	अणु 0xe0, 0xd0 पूर्ण,
	अणु 0xf9, 0x00 पूर्ण,
	अणु 0x55, 0x02 पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Register access
 */

अटल स्थिर uपूर्णांक8_t adv7511_रेजिस्टर_शेषs[] = अणु
	0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 00 */
	0x00, 0x00, 0x01, 0x0e, 0xbc, 0x18, 0x01, 0x13,
	0x25, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 10 */
	0x46, 0x62, 0x04, 0xa8, 0x00, 0x00, 0x1c, 0x84,
	0x1c, 0xbf, 0x04, 0xa8, 0x1e, 0x70, 0x02, 0x1e, /* 20 */
	0x00, 0x00, 0x04, 0xa8, 0x08, 0x12, 0x1b, 0xac,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 30 */
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xb0,
	0x00, 0x50, 0x90, 0x7e, 0x79, 0x70, 0x00, 0x00, /* 40 */
	0x00, 0xa8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x02, 0x0d, 0x00, 0x00, 0x00, 0x00, /* 50 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 60 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 70 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 80 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, /* 90 */
	0x0b, 0x02, 0x00, 0x18, 0x5a, 0x60, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x80, 0x08, 0x04, 0x00, 0x00, /* a0 */
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x14,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* b0 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* c0 */
	0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x01, 0x04,
	0x30, 0xff, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, /* d0 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01,
	0x80, 0x75, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, /* e0 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x11, 0x00, /* f0 */
	0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
पूर्ण;

अटल bool adv7511_रेजिस्टर_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADV7511_REG_CHIP_REVISION:
	हाल ADV7511_REG_SPDIF_FREQ:
	हाल ADV7511_REG_CTS_AUTOMATIC1:
	हाल ADV7511_REG_CTS_AUTOMATIC2:
	हाल ADV7511_REG_VIC_DETECTED:
	हाल ADV7511_REG_VIC_SEND:
	हाल ADV7511_REG_AUX_VIC_DETECTED:
	हाल ADV7511_REG_STATUS:
	हाल ADV7511_REG_GC(1):
	हाल ADV7511_REG_INT(0):
	हाल ADV7511_REG_INT(1):
	हाल ADV7511_REG_PLL_STATUS:
	हाल ADV7511_REG_AN(0):
	हाल ADV7511_REG_AN(1):
	हाल ADV7511_REG_AN(2):
	हाल ADV7511_REG_AN(3):
	हाल ADV7511_REG_AN(4):
	हाल ADV7511_REG_AN(5):
	हाल ADV7511_REG_AN(6):
	हाल ADV7511_REG_AN(7):
	हाल ADV7511_REG_HDCP_STATUS:
	हाल ADV7511_REG_BCAPS:
	हाल ADV7511_REG_BKSV(0):
	हाल ADV7511_REG_BKSV(1):
	हाल ADV7511_REG_BKSV(2):
	हाल ADV7511_REG_BKSV(3):
	हाल ADV7511_REG_BKSV(4):
	हाल ADV7511_REG_DDC_STATUS:
	हाल ADV7511_REG_EDID_READ_CTRL:
	हाल ADV7511_REG_BSTATUS(0):
	हाल ADV7511_REG_BSTATUS(1):
	हाल ADV7511_REG_CHIP_ID_HIGH:
	हाल ADV7511_REG_CHIP_ID_LOW:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config adv7511_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = 0xff,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs_raw = adv7511_रेजिस्टर_शेषs,
	.num_reg_शेषs_raw = ARRAY_SIZE(adv7511_रेजिस्टर_शेषs),

	.अस्थिर_reg = adv7511_रेजिस्टर_अस्थिर,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Hardware configuration
 */

अटल व्योम adv7511_set_colormap(काष्ठा adv7511 *adv7511, bool enable,
				 स्थिर uपूर्णांक16_t *coeff,
				 अचिन्हित पूर्णांक scaling_factor)
अणु
	अचिन्हित पूर्णांक i;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_CSC_UPPER(1),
			   ADV7511_CSC_UPDATE_MODE, ADV7511_CSC_UPDATE_MODE);

	अगर (enable) अणु
		क्रम (i = 0; i < 12; ++i) अणु
			regmap_update_bits(adv7511->regmap,
					   ADV7511_REG_CSC_UPPER(i),
					   0x1f, coeff[i] >> 8);
			regmap_ग_लिखो(adv7511->regmap,
				     ADV7511_REG_CSC_LOWER(i),
				     coeff[i] & 0xff);
		पूर्ण
	पूर्ण

	अगर (enable)
		regmap_update_bits(adv7511->regmap, ADV7511_REG_CSC_UPPER(0),
				   0xe0, 0x80 | (scaling_factor << 5));
	अन्यथा
		regmap_update_bits(adv7511->regmap, ADV7511_REG_CSC_UPPER(0),
				   0x80, 0x00);

	regmap_update_bits(adv7511->regmap, ADV7511_REG_CSC_UPPER(1),
			   ADV7511_CSC_UPDATE_MODE, 0);
पूर्ण

अटल पूर्णांक adv7511_packet_enable(काष्ठा adv7511 *adv7511, अचिन्हित पूर्णांक packet)
अणु
	अगर (packet & 0xff)
		regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE0,
				   packet, 0xff);

	अगर (packet & 0xff00) अणु
		packet >>= 8;
		regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				   packet, 0xff);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_packet_disable(काष्ठा adv7511 *adv7511, अचिन्हित पूर्णांक packet)
अणु
	अगर (packet & 0xff)
		regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE0,
				   packet, 0x00);

	अगर (packet & 0xff00) अणु
		packet >>= 8;
		regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				   packet, 0x00);
	पूर्ण

	वापस 0;
पूर्ण

/* Coefficients क्रम adv7511 color space conversion */
अटल स्थिर uपूर्णांक16_t adv7511_csc_ycbcr_to_rgb[] = अणु
	0x0734, 0x04ad, 0x0000, 0x1c1b,
	0x1ddc, 0x04ad, 0x1f24, 0x0135,
	0x0000, 0x04ad, 0x087c, 0x1b77,
पूर्ण;

अटल व्योम adv7511_set_config_csc(काष्ठा adv7511 *adv7511,
				   काष्ठा drm_connector *connector,
				   bool rgb, bool hdmi_mode)
अणु
	काष्ठा adv7511_video_config config;
	bool output_क्रमmat_422, output_क्रमmat_ycbcr;
	अचिन्हित पूर्णांक mode;
	uपूर्णांक8_t infoframe[17];

	config.hdmi_mode = hdmi_mode;

	hdmi_avi_infoframe_init(&config.avi_infoframe);

	config.avi_infoframe.scan_mode = HDMI_SCAN_MODE_UNDERSCAN;

	अगर (rgb) अणु
		config.csc_enable = false;
		config.avi_infoframe.colorspace = HDMI_COLORSPACE_RGB;
	पूर्ण अन्यथा अणु
		config.csc_scaling_factor = ADV7511_CSC_SCALING_4;
		config.csc_coefficents = adv7511_csc_ycbcr_to_rgb;

		अगर ((connector->display_info.color_क्रमmats &
		     DRM_COLOR_FORMAT_YCRCB422) &&
		    config.hdmi_mode) अणु
			config.csc_enable = false;
			config.avi_infoframe.colorspace =
				HDMI_COLORSPACE_YUV422;
		पूर्ण अन्यथा अणु
			config.csc_enable = true;
			config.avi_infoframe.colorspace = HDMI_COLORSPACE_RGB;
		पूर्ण
	पूर्ण

	अगर (config.hdmi_mode) अणु
		mode = ADV7511_HDMI_CFG_MODE_HDMI;

		चयन (config.avi_infoframe.colorspace) अणु
		हाल HDMI_COLORSPACE_YUV444:
			output_क्रमmat_422 = false;
			output_क्रमmat_ycbcr = true;
			अवरोध;
		हाल HDMI_COLORSPACE_YUV422:
			output_क्रमmat_422 = true;
			output_क्रमmat_ycbcr = true;
			अवरोध;
		शेष:
			output_क्रमmat_422 = false;
			output_क्रमmat_ycbcr = false;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		mode = ADV7511_HDMI_CFG_MODE_DVI;
		output_क्रमmat_422 = false;
		output_क्रमmat_ycbcr = false;
	पूर्ण

	adv7511_packet_disable(adv7511, ADV7511_PACKET_ENABLE_AVI_INFOFRAME);

	adv7511_set_colormap(adv7511, config.csc_enable,
			     config.csc_coefficents,
			     config.csc_scaling_factor);

	regmap_update_bits(adv7511->regmap, ADV7511_REG_VIDEO_INPUT_CFG1, 0x81,
			   (output_क्रमmat_422 << 7) | output_क्रमmat_ycbcr);

	regmap_update_bits(adv7511->regmap, ADV7511_REG_HDCP_HDMI_CFG,
			   ADV7511_HDMI_CFG_MODE_MASK, mode);

	hdmi_avi_infoframe_pack(&config.avi_infoframe, infoframe,
				माप(infoframe));

	/* The AVI infoframe id is not configurable */
	regmap_bulk_ग_लिखो(adv7511->regmap, ADV7511_REG_AVI_INFOFRAME_VERSION,
			  infoframe + 1, माप(infoframe) - 1);

	adv7511_packet_enable(adv7511, ADV7511_PACKET_ENABLE_AVI_INFOFRAME);
पूर्ण

अटल व्योम adv7511_set_link_config(काष्ठा adv7511 *adv7511,
				    स्थिर काष्ठा adv7511_link_config *config)
अणु
	/*
	 * The input style values करोcumented in the datasheet करोn't match the
	 * hardware रेजिस्टर field values :-(
	 */
	अटल स्थिर अचिन्हित पूर्णांक input_styles[4] = अणु 0, 2, 1, 3 पूर्ण;

	अचिन्हित पूर्णांक घड़ी_delay;
	अचिन्हित पूर्णांक color_depth;
	अचिन्हित पूर्णांक input_id;

	घड़ी_delay = (config->घड़ी_delay + 1200) / 400;
	color_depth = config->input_color_depth == 8 ? 3
		    : (config->input_color_depth == 10 ? 1 : 2);

	/* TODO Support input ID 6 */
	अगर (config->input_colorspace != HDMI_COLORSPACE_YUV422)
		input_id = config->input_घड़ी == ADV7511_INPUT_CLOCK_DDR
			 ? 5 : 0;
	अन्यथा अगर (config->input_घड़ी == ADV7511_INPUT_CLOCK_DDR)
		input_id = config->embedded_sync ? 8 : 7;
	अन्यथा अगर (config->input_घड़ी == ADV7511_INPUT_CLOCK_2X)
		input_id = config->embedded_sync ? 4 : 3;
	अन्यथा
		input_id = config->embedded_sync ? 2 : 1;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_I2C_FREQ_ID_CFG, 0xf,
			   input_id);
	regmap_update_bits(adv7511->regmap, ADV7511_REG_VIDEO_INPUT_CFG1, 0x7e,
			   (color_depth << 4) |
			   (input_styles[config->input_style] << 2));
	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_VIDEO_INPUT_CFG2,
		     config->input_justअगरication << 3);
	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_TIMING_GEN_SEQ,
		     config->sync_pulse << 2);

	regmap_ग_लिखो(adv7511->regmap, 0xba, घड़ी_delay << 5);

	adv7511->embedded_sync = config->embedded_sync;
	adv7511->hsync_polarity = config->hsync_polarity;
	adv7511->vsync_polarity = config->vsync_polarity;
	adv7511->rgb = config->input_colorspace == HDMI_COLORSPACE_RGB;
पूर्ण

अटल व्योम __adv7511_घातer_on(काष्ठा adv7511 *adv7511)
अणु
	adv7511->current_edid_segment = -1;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER,
			   ADV7511_POWER_POWER_DOWN, 0);
	अगर (adv7511->i2c_मुख्य->irq) अणु
		/*
		 * Documentation says the INT_ENABLE रेजिस्टरs are reset in
		 * POWER_DOWN mode. My 7511w preserved the bits, however.
		 * Still, let's be safe and stick to the करोcumentation.
		 */
		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_INT_ENABLE(0),
			     ADV7511_INT0_EDID_READY | ADV7511_INT0_HPD);
		regmap_update_bits(adv7511->regmap,
				   ADV7511_REG_INT_ENABLE(1),
				   ADV7511_INT1_DDC_ERROR,
				   ADV7511_INT1_DDC_ERROR);
	पूर्ण

	/*
	 * Per spec it is allowed to pulse the HPD संकेत to indicate that the
	 * EDID inक्रमmation has changed. Some monitors करो this when they wakeup
	 * from standby or are enabled. When the HPD goes low the adv7511 is
	 * reset and the outमाला_दो are disabled which might cause the monitor to
	 * go to standby again. To aव्योम this we ignore the HPD pin क्रम the
	 * first few seconds after enabling the output.
	 */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER2,
			   ADV7511_REG_POWER2_HPD_SRC_MASK,
			   ADV7511_REG_POWER2_HPD_SRC_NONE);
पूर्ण

अटल व्योम adv7511_घातer_on(काष्ठा adv7511 *adv7511)
अणु
	__adv7511_घातer_on(adv7511);

	/*
	 * Most of the रेजिस्टरs are reset during घातer करोwn or when HPD is low.
	 */
	regcache_sync(adv7511->regmap);

	अगर (adv7511->type == ADV7533 || adv7511->type == ADV7535)
		adv7533_dsi_घातer_on(adv7511);
	adv7511->घातered = true;
पूर्ण

अटल व्योम __adv7511_घातer_off(काष्ठा adv7511 *adv7511)
अणु
	/* TODO: setup additional घातer करोwn modes */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER,
			   ADV7511_POWER_POWER_DOWN,
			   ADV7511_POWER_POWER_DOWN);
	regmap_update_bits(adv7511->regmap,
			   ADV7511_REG_INT_ENABLE(1),
			   ADV7511_INT1_DDC_ERROR, 0);
	regcache_mark_dirty(adv7511->regmap);
पूर्ण

अटल व्योम adv7511_घातer_off(काष्ठा adv7511 *adv7511)
अणु
	__adv7511_घातer_off(adv7511);
	अगर (adv7511->type == ADV7533 || adv7511->type == ADV7535)
		adv7533_dsi_घातer_off(adv7511);
	adv7511->घातered = false;
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt and hotplug detection
 */

अटल bool adv7511_hpd(काष्ठा adv7511 *adv7511)
अणु
	अचिन्हित पूर्णांक irq0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(adv7511->regmap, ADV7511_REG_INT(0), &irq0);
	अगर (ret < 0)
		वापस false;

	अगर (irq0 & ADV7511_INT0_HPD) अणु
		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_INT(0),
			     ADV7511_INT0_HPD);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम adv7511_hpd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adv7511 *adv7511 = container_of(work, काष्ठा adv7511, hpd_work);
	क्रमागत drm_connector_status status;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(adv7511->regmap, ADV7511_REG_STATUS, &val);
	अगर (ret < 0)
		status = connector_status_disconnected;
	अन्यथा अगर (val & ADV7511_STATUS_HPD)
		status = connector_status_connected;
	अन्यथा
		status = connector_status_disconnected;

	/*
	 * The bridge resets its रेजिस्टरs on unplug. So when we get a plug
	 * event and we're alपढ़ोy supposed to be घातered, cycle the bridge to
	 * restore its state.
	 */
	अगर (status == connector_status_connected &&
	    adv7511->connector.status == connector_status_disconnected &&
	    adv7511->घातered) अणु
		regcache_mark_dirty(adv7511->regmap);
		adv7511_घातer_on(adv7511);
	पूर्ण

	अगर (adv7511->connector.status != status) अणु
		adv7511->connector.status = status;

		अगर (adv7511->connector.dev) अणु
			अगर (status == connector_status_disconnected)
				cec_phys_addr_invalidate(adv7511->cec_adap);
			drm_kms_helper_hotplug_event(adv7511->connector.dev);
		पूर्ण अन्यथा अणु
			drm_bridge_hpd_notअगरy(&adv7511->bridge, status);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक adv7511_irq_process(काष्ठा adv7511 *adv7511, bool process_hpd)
अणु
	अचिन्हित पूर्णांक irq0, irq1;
	पूर्णांक ret;

	ret = regmap_पढ़ो(adv7511->regmap, ADV7511_REG_INT(0), &irq0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(adv7511->regmap, ADV7511_REG_INT(1), &irq1);
	अगर (ret < 0)
		वापस ret;

	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_INT(0), irq0);
	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_INT(1), irq1);

	अगर (process_hpd && irq0 & ADV7511_INT0_HPD && adv7511->bridge.encoder)
		schedule_work(&adv7511->hpd_work);

	अगर (irq0 & ADV7511_INT0_EDID_READY || irq1 & ADV7511_INT1_DDC_ERROR) अणु
		adv7511->edid_पढ़ो = true;

		अगर (adv7511->i2c_मुख्य->irq)
			wake_up_all(&adv7511->wq);
	पूर्ण

#अगर_घोषित CONFIG_DRM_I2C_ADV7511_CEC
	adv7511_cec_irq_process(adv7511, irq1);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल irqवापस_t adv7511_irq_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा adv7511 *adv7511 = devid;
	पूर्णांक ret;

	ret = adv7511_irq_process(adv7511, true);
	वापस ret < 0 ? IRQ_NONE : IRQ_HANDLED;
पूर्ण

/* -----------------------------------------------------------------------------
 * EDID retrieval
 */

अटल पूर्णांक adv7511_रुको_क्रम_edid(काष्ठा adv7511 *adv7511, पूर्णांक समयout)
अणु
	पूर्णांक ret;

	अगर (adv7511->i2c_मुख्य->irq) अणु
		ret = रुको_event_पूर्णांकerruptible_समयout(adv7511->wq,
				adv7511->edid_पढ़ो, msecs_to_jअगरfies(समयout));
	पूर्ण अन्यथा अणु
		क्रम (; समयout > 0; समयout -= 25) अणु
			ret = adv7511_irq_process(adv7511, false);
			अगर (ret < 0)
				अवरोध;

			अगर (adv7511->edid_पढ़ो)
				अवरोध;

			msleep(25);
		पूर्ण
	पूर्ण

	वापस adv7511->edid_पढ़ो ? 0 : -EIO;
पूर्ण

अटल पूर्णांक adv7511_get_edid_block(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block,
				  माप_प्रकार len)
अणु
	काष्ठा adv7511 *adv7511 = data;
	काष्ठा i2c_msg xfer[2];
	uपूर्णांक8_t offset;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (len > 128)
		वापस -EINVAL;

	अगर (adv7511->current_edid_segment != block / 2) अणु
		अचिन्हित पूर्णांक status;

		ret = regmap_पढ़ो(adv7511->regmap, ADV7511_REG_DDC_STATUS,
				  &status);
		अगर (ret < 0)
			वापस ret;

		अगर (status != 2) अणु
			adv7511->edid_पढ़ो = false;
			regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_EDID_SEGMENT,
				     block);
			ret = adv7511_रुको_क्रम_edid(adv7511, 200);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		/* Break this apart, hopefully more I2C controllers will
		 * support 64 byte transfers than 256 byte transfers
		 */

		xfer[0].addr = adv7511->i2c_edid->addr;
		xfer[0].flags = 0;
		xfer[0].len = 1;
		xfer[0].buf = &offset;
		xfer[1].addr = adv7511->i2c_edid->addr;
		xfer[1].flags = I2C_M_RD;
		xfer[1].len = 64;
		xfer[1].buf = adv7511->edid_buf;

		offset = 0;

		क्रम (i = 0; i < 4; ++i) अणु
			ret = i2c_transfer(adv7511->i2c_edid->adapter, xfer,
					   ARRAY_SIZE(xfer));
			अगर (ret < 0)
				वापस ret;
			अन्यथा अगर (ret != 2)
				वापस -EIO;

			xfer[1].buf += 64;
			offset += 64;
		पूर्ण

		adv7511->current_edid_segment = block / 2;
	पूर्ण

	अगर (block % 2 == 0)
		स_नकल(buf, adv7511->edid_buf, len);
	अन्यथा
		स_नकल(buf, adv7511->edid_buf + 128, len);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * ADV75xx helpers
 */

अटल काष्ठा edid *adv7511_get_edid(काष्ठा adv7511 *adv7511,
				     काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *edid;

	/* Reading the EDID only works अगर the device is घातered */
	अगर (!adv7511->घातered) अणु
		अचिन्हित पूर्णांक edid_i2c_addr =
					(adv7511->i2c_edid->addr << 1);

		__adv7511_घातer_on(adv7511);

		/* Reset the EDID_I2C_ADDR रेजिस्टर as it might be cleared */
		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_EDID_I2C_ADDR,
			     edid_i2c_addr);
	पूर्ण

	edid = drm_करो_get_edid(connector, adv7511_get_edid_block, adv7511);

	अगर (!adv7511->घातered)
		__adv7511_घातer_off(adv7511);

	adv7511_set_config_csc(adv7511, connector, adv7511->rgb,
			       drm_detect_hdmi_monitor(edid));

	cec_s_phys_addr_from_edid(adv7511->cec_adap, edid);

	वापस edid;
पूर्ण

अटल पूर्णांक adv7511_get_modes(काष्ठा adv7511 *adv7511,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *edid;
	अचिन्हित पूर्णांक count;

	edid = adv7511_get_edid(adv7511, connector);

	drm_connector_update_edid_property(connector, edid);
	count = drm_add_edid_modes(connector, edid);

	kमुक्त(edid);

	वापस count;
पूर्ण

अटल क्रमागत drm_connector_status
adv7511_detect(काष्ठा adv7511 *adv7511, काष्ठा drm_connector *connector)
अणु
	क्रमागत drm_connector_status status;
	अचिन्हित पूर्णांक val;
	bool hpd;
	पूर्णांक ret;

	ret = regmap_पढ़ो(adv7511->regmap, ADV7511_REG_STATUS, &val);
	अगर (ret < 0)
		वापस connector_status_disconnected;

	अगर (val & ADV7511_STATUS_HPD)
		status = connector_status_connected;
	अन्यथा
		status = connector_status_disconnected;

	hpd = adv7511_hpd(adv7511);

	/* The chip resets itself when the cable is disconnected, so in हाल
	 * there is a pending HPD पूर्णांकerrupt and the cable is connected there was
	 * at least one transition from disconnected to connected and the chip
	 * has to be reinitialized. */
	अगर (status == connector_status_connected && hpd && adv7511->घातered) अणु
		regcache_mark_dirty(adv7511->regmap);
		adv7511_घातer_on(adv7511);
		अगर (connector)
			adv7511_get_modes(adv7511, connector);
		अगर (adv7511->status == connector_status_connected)
			status = connector_status_disconnected;
	पूर्ण अन्यथा अणु
		/* Renable HPD sensing */
		regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER2,
				   ADV7511_REG_POWER2_HPD_SRC_MASK,
				   ADV7511_REG_POWER2_HPD_SRC_BOTH);
	पूर्ण

	adv7511->status = status;
	वापस status;
पूर्ण

अटल क्रमागत drm_mode_status adv7511_mode_valid(काष्ठा adv7511 *adv7511,
			      काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 165000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल व्योम adv7511_mode_set(काष्ठा adv7511 *adv7511,
			     स्थिर काष्ठा drm_display_mode *mode,
			     स्थिर काष्ठा drm_display_mode *adj_mode)
अणु
	अचिन्हित पूर्णांक low_refresh_rate;
	अचिन्हित पूर्णांक hsync_polarity = 0;
	अचिन्हित पूर्णांक vsync_polarity = 0;

	अगर (adv7511->embedded_sync) अणु
		अचिन्हित पूर्णांक hsync_offset, hsync_len;
		अचिन्हित पूर्णांक vsync_offset, vsync_len;

		hsync_offset = adj_mode->crtc_hsync_start -
			       adj_mode->crtc_hdisplay;
		vsync_offset = adj_mode->crtc_vsync_start -
			       adj_mode->crtc_vdisplay;
		hsync_len = adj_mode->crtc_hsync_end -
			    adj_mode->crtc_hsync_start;
		vsync_len = adj_mode->crtc_vsync_end -
			    adj_mode->crtc_vsync_start;

		/* The hardware vsync generator has a off-by-one bug */
		vsync_offset += 1;

		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_HSYNC_PLACEMENT_MSB,
			     ((hsync_offset >> 10) & 0x7) << 5);
		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_SYNC_DECODER(0),
			     (hsync_offset >> 2) & 0xff);
		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_SYNC_DECODER(1),
			     ((hsync_offset & 0x3) << 6) |
			     ((hsync_len >> 4) & 0x3f));
		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_SYNC_DECODER(2),
			     ((hsync_len & 0xf) << 4) |
			     ((vsync_offset >> 6) & 0xf));
		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_SYNC_DECODER(3),
			     ((vsync_offset & 0x3f) << 2) |
			     ((vsync_len >> 8) & 0x3));
		regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_SYNC_DECODER(4),
			     vsync_len & 0xff);

		hsync_polarity = !(adj_mode->flags & DRM_MODE_FLAG_PHSYNC);
		vsync_polarity = !(adj_mode->flags & DRM_MODE_FLAG_PVSYNC);
	पूर्ण अन्यथा अणु
		क्रमागत adv7511_sync_polarity mode_hsync_polarity;
		क्रमागत adv7511_sync_polarity mode_vsync_polarity;

		/**
		 * If the input संकेत is always low or always high we want to
		 * invert or let it passthrough depending on the polarity of the
		 * current mode.
		 **/
		अगर (adj_mode->flags & DRM_MODE_FLAG_NHSYNC)
			mode_hsync_polarity = ADV7511_SYNC_POLARITY_LOW;
		अन्यथा
			mode_hsync_polarity = ADV7511_SYNC_POLARITY_HIGH;

		अगर (adj_mode->flags & DRM_MODE_FLAG_NVSYNC)
			mode_vsync_polarity = ADV7511_SYNC_POLARITY_LOW;
		अन्यथा
			mode_vsync_polarity = ADV7511_SYNC_POLARITY_HIGH;

		अगर (adv7511->hsync_polarity != mode_hsync_polarity &&
		    adv7511->hsync_polarity !=
		    ADV7511_SYNC_POLARITY_PASSTHROUGH)
			hsync_polarity = 1;

		अगर (adv7511->vsync_polarity != mode_vsync_polarity &&
		    adv7511->vsync_polarity !=
		    ADV7511_SYNC_POLARITY_PASSTHROUGH)
			vsync_polarity = 1;
	पूर्ण

	अगर (drm_mode_vrefresh(mode) <= 24)
		low_refresh_rate = ADV7511_LOW_REFRESH_RATE_24HZ;
	अन्यथा अगर (drm_mode_vrefresh(mode) <= 25)
		low_refresh_rate = ADV7511_LOW_REFRESH_RATE_25HZ;
	अन्यथा अगर (drm_mode_vrefresh(mode) <= 30)
		low_refresh_rate = ADV7511_LOW_REFRESH_RATE_30HZ;
	अन्यथा
		low_refresh_rate = ADV7511_LOW_REFRESH_RATE_NONE;

	regmap_update_bits(adv7511->regmap, 0xfb,
		0x6, low_refresh_rate << 1);
	regmap_update_bits(adv7511->regmap, 0x17,
		0x60, (vsync_polarity << 6) | (hsync_polarity << 5));

	अगर (adv7511->type == ADV7533 || adv7511->type == ADV7535)
		adv7533_mode_set(adv7511, adj_mode);

	drm_mode_copy(&adv7511->curr_mode, adj_mode);

	/*
	 * TODO Test first order 4:2:2 to 4:4:4 up conversion method, which is
	 * supposed to give better results.
	 */

	adv7511->f_पंचांगds = mode->घड़ी;
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Connector Operations
 */

अटल काष्ठा adv7511 *connector_to_adv7511(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा adv7511, connector);
पूर्ण

अटल पूर्णांक adv7511_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा adv7511 *adv = connector_to_adv7511(connector);

	वापस adv7511_get_modes(adv, connector);
पूर्ण

अटल क्रमागत drm_mode_status
adv7511_connector_mode_valid(काष्ठा drm_connector *connector,
			     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा adv7511 *adv = connector_to_adv7511(connector);

	वापस adv7511_mode_valid(adv, mode);
पूर्ण

अटल काष्ठा drm_connector_helper_funcs adv7511_connector_helper_funcs = अणु
	.get_modes = adv7511_connector_get_modes,
	.mode_valid = adv7511_connector_mode_valid,
पूर्ण;

अटल क्रमागत drm_connector_status
adv7511_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा adv7511 *adv = connector_to_adv7511(connector);

	वापस adv7511_detect(adv, connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs adv7511_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = adv7511_connector_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक adv7511_connector_init(काष्ठा adv7511 *adv)
अणु
	काष्ठा drm_bridge *bridge = &adv->bridge;
	पूर्णांक ret;

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	अगर (adv->i2c_मुख्य->irq)
		adv->connector.polled = DRM_CONNECTOR_POLL_HPD;
	अन्यथा
		adv->connector.polled = DRM_CONNECTOR_POLL_CONNECT |
				DRM_CONNECTOR_POLL_DISCONNECT;

	ret = drm_connector_init(bridge->dev, &adv->connector,
				 &adv7511_connector_funcs,
				 DRM_MODE_CONNECTOR_HDMIA);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण
	drm_connector_helper_add(&adv->connector,
				 &adv7511_connector_helper_funcs);
	drm_connector_attach_encoder(&adv->connector, bridge->encoder);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Bridge Operations
 */

अटल काष्ठा adv7511 *bridge_to_adv7511(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा adv7511, bridge);
पूर्ण

अटल व्योम adv7511_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा adv7511 *adv = bridge_to_adv7511(bridge);

	adv7511_घातer_on(adv);
पूर्ण

अटल व्योम adv7511_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा adv7511 *adv = bridge_to_adv7511(bridge);

	adv7511_घातer_off(adv);
पूर्ण

अटल व्योम adv7511_bridge_mode_set(काष्ठा drm_bridge *bridge,
				    स्थिर काष्ठा drm_display_mode *mode,
				    स्थिर काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा adv7511 *adv = bridge_to_adv7511(bridge);

	adv7511_mode_set(adv, mode, adj_mode);
पूर्ण

अटल पूर्णांक adv7511_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा adv7511 *adv = bridge_to_adv7511(bridge);
	पूर्णांक ret = 0;

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)) अणु
		ret = adv7511_connector_init(adv);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (adv->type == ADV7533 || adv->type == ADV7535)
		ret = adv7533_attach_dsi(adv);

	अगर (adv->i2c_मुख्य->irq)
		regmap_ग_लिखो(adv->regmap, ADV7511_REG_INT_ENABLE(0),
			     ADV7511_INT0_HPD);

	वापस ret;
पूर्ण

अटल क्रमागत drm_connector_status adv7511_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा adv7511 *adv = bridge_to_adv7511(bridge);

	वापस adv7511_detect(adv, शून्य);
पूर्ण

अटल काष्ठा edid *adv7511_bridge_get_edid(काष्ठा drm_bridge *bridge,
					    काष्ठा drm_connector *connector)
अणु
	काष्ठा adv7511 *adv = bridge_to_adv7511(bridge);

	वापस adv7511_get_edid(adv, connector);
पूर्ण

अटल व्योम adv7511_bridge_hpd_notअगरy(काष्ठा drm_bridge *bridge,
				      क्रमागत drm_connector_status status)
अणु
	काष्ठा adv7511 *adv = bridge_to_adv7511(bridge);

	अगर (status == connector_status_disconnected)
		cec_phys_addr_invalidate(adv->cec_adap);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs adv7511_bridge_funcs = अणु
	.enable = adv7511_bridge_enable,
	.disable = adv7511_bridge_disable,
	.mode_set = adv7511_bridge_mode_set,
	.attach = adv7511_bridge_attach,
	.detect = adv7511_bridge_detect,
	.get_edid = adv7511_bridge_get_edid,
	.hpd_notअगरy = adv7511_bridge_hpd_notअगरy,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe & हटाओ
 */

अटल स्थिर अक्षर * स्थिर adv7511_supply_names[] = अणु
	"avdd",
	"dvdd",
	"pvdd",
	"bgvdd",
	"dvdd-3v",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adv7533_supply_names[] = अणु
	"avdd",
	"dvdd",
	"pvdd",
	"a2vdd",
	"v3p3",
	"v1p2",
पूर्ण;

अटल पूर्णांक adv7511_init_regulators(काष्ठा adv7511 *adv)
अणु
	काष्ठा device *dev = &adv->i2c_मुख्य->dev;
	स्थिर अक्षर * स्थिर *supply_names;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (adv->type == ADV7511) अणु
		supply_names = adv7511_supply_names;
		adv->num_supplies = ARRAY_SIZE(adv7511_supply_names);
	पूर्ण अन्यथा अणु
		supply_names = adv7533_supply_names;
		adv->num_supplies = ARRAY_SIZE(adv7533_supply_names);
	पूर्ण

	adv->supplies = devm_kसुस्मृति(dev, adv->num_supplies,
				     माप(*adv->supplies), GFP_KERNEL);
	अगर (!adv->supplies)
		वापस -ENOMEM;

	क्रम (i = 0; i < adv->num_supplies; i++)
		adv->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(dev, adv->num_supplies, adv->supplies);
	अगर (ret)
		वापस ret;

	वापस regulator_bulk_enable(adv->num_supplies, adv->supplies);
पूर्ण

अटल व्योम adv7511_uninit_regulators(काष्ठा adv7511 *adv)
अणु
	regulator_bulk_disable(adv->num_supplies, adv->supplies);
पूर्ण

अटल bool adv7511_cec_रेजिस्टर_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा adv7511 *adv7511 = i2c_get_clientdata(i2c);

	अगर (adv7511->type == ADV7533 || adv7511->type == ADV7535)
		reg -= ADV7533_REG_CEC_OFFSET;

	चयन (reg) अणु
	हाल ADV7511_REG_CEC_RX_FRAME_HDR:
	हाल ADV7511_REG_CEC_RX_FRAME_DATA0...
		ADV7511_REG_CEC_RX_FRAME_DATA0 + 14:
	हाल ADV7511_REG_CEC_RX_FRAME_LEN:
	हाल ADV7511_REG_CEC_RX_BUFFERS:
	हाल ADV7511_REG_CEC_TX_LOW_DRV_CNT:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config adv7511_cec_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = 0xff,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = adv7511_cec_रेजिस्टर_अस्थिर,
पूर्ण;

अटल पूर्णांक adv7511_init_cec_regmap(काष्ठा adv7511 *adv)
अणु
	पूर्णांक ret;

	adv->i2c_cec = i2c_new_ancillary_device(adv->i2c_मुख्य, "cec",
						ADV7511_CEC_I2C_ADDR_DEFAULT);
	अगर (IS_ERR(adv->i2c_cec))
		वापस PTR_ERR(adv->i2c_cec);
	i2c_set_clientdata(adv->i2c_cec, adv);

	adv->regmap_cec = devm_regmap_init_i2c(adv->i2c_cec,
					&adv7511_cec_regmap_config);
	अगर (IS_ERR(adv->regmap_cec)) अणु
		ret = PTR_ERR(adv->regmap_cec);
		जाओ err;
	पूर्ण

	अगर (adv->type == ADV7533 || adv->type == ADV7535) अणु
		ret = adv7533_patch_cec_रेजिस्टरs(adv);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	i2c_unरेजिस्टर_device(adv->i2c_cec);
	वापस ret;
पूर्ण

अटल पूर्णांक adv7511_parse_dt(काष्ठा device_node *np,
			    काष्ठा adv7511_link_config *config)
अणु
	स्थिर अक्षर *str;
	पूर्णांक ret;

	of_property_पढ़ो_u32(np, "adi,input-depth", &config->input_color_depth);
	अगर (config->input_color_depth != 8 && config->input_color_depth != 10 &&
	    config->input_color_depth != 12)
		वापस -EINVAL;

	ret = of_property_पढ़ो_string(np, "adi,input-colorspace", &str);
	अगर (ret < 0)
		वापस ret;

	अगर (!म_भेद(str, "rgb"))
		config->input_colorspace = HDMI_COLORSPACE_RGB;
	अन्यथा अगर (!म_भेद(str, "yuv422"))
		config->input_colorspace = HDMI_COLORSPACE_YUV422;
	अन्यथा अगर (!म_भेद(str, "yuv444"))
		config->input_colorspace = HDMI_COLORSPACE_YUV444;
	अन्यथा
		वापस -EINVAL;

	ret = of_property_पढ़ो_string(np, "adi,input-clock", &str);
	अगर (ret < 0)
		वापस ret;

	अगर (!म_भेद(str, "1x"))
		config->input_घड़ी = ADV7511_INPUT_CLOCK_1X;
	अन्यथा अगर (!म_भेद(str, "2x"))
		config->input_घड़ी = ADV7511_INPUT_CLOCK_2X;
	अन्यथा अगर (!म_भेद(str, "ddr"))
		config->input_घड़ी = ADV7511_INPUT_CLOCK_DDR;
	अन्यथा
		वापस -EINVAL;

	अगर (config->input_colorspace == HDMI_COLORSPACE_YUV422 ||
	    config->input_घड़ी != ADV7511_INPUT_CLOCK_1X) अणु
		ret = of_property_पढ़ो_u32(np, "adi,input-style",
					   &config->input_style);
		अगर (ret)
			वापस ret;

		अगर (config->input_style < 1 || config->input_style > 3)
			वापस -EINVAL;

		ret = of_property_पढ़ो_string(np, "adi,input-justification",
					      &str);
		अगर (ret < 0)
			वापस ret;

		अगर (!म_भेद(str, "left"))
			config->input_justअगरication =
				ADV7511_INPUT_JUSTIFICATION_LEFT;
		अन्यथा अगर (!म_भेद(str, "evenly"))
			config->input_justअगरication =
				ADV7511_INPUT_JUSTIFICATION_EVENLY;
		अन्यथा अगर (!म_भेद(str, "right"))
			config->input_justअगरication =
				ADV7511_INPUT_JUSTIFICATION_RIGHT;
		अन्यथा
			वापस -EINVAL;

	पूर्ण अन्यथा अणु
		config->input_style = 1;
		config->input_justअगरication = ADV7511_INPUT_JUSTIFICATION_LEFT;
	पूर्ण

	of_property_पढ़ो_u32(np, "adi,clock-delay", &config->घड़ी_delay);
	अगर (config->घड़ी_delay < -1200 || config->घड़ी_delay > 1600)
		वापस -EINVAL;

	config->embedded_sync = of_property_पढ़ो_bool(np, "adi,embedded-sync");

	/* Hardcode the sync pulse configurations क्रम now. */
	config->sync_pulse = ADV7511_INPUT_SYNC_PULSE_NONE;
	config->vsync_polarity = ADV7511_SYNC_POLARITY_PASSTHROUGH;
	config->hsync_polarity = ADV7511_SYNC_POLARITY_PASSTHROUGH;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_probe(काष्ठा i2c_client *i2c, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adv7511_link_config link_config;
	काष्ठा adv7511 *adv7511;
	काष्ठा device *dev = &i2c->dev;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!dev->of_node)
		वापस -EINVAL;

	adv7511 = devm_kzalloc(dev, माप(*adv7511), GFP_KERNEL);
	अगर (!adv7511)
		वापस -ENOMEM;

	adv7511->i2c_मुख्य = i2c;
	adv7511->घातered = false;
	adv7511->status = connector_status_disconnected;

	अगर (dev->of_node)
		adv7511->type = (क्रमागत adv7511_type)of_device_get_match_data(dev);
	अन्यथा
		adv7511->type = id->driver_data;

	स_रखो(&link_config, 0, माप(link_config));

	अगर (adv7511->type == ADV7511)
		ret = adv7511_parse_dt(dev->of_node, &link_config);
	अन्यथा
		ret = adv7533_parse_dt(dev->of_node, adv7511);
	अगर (ret)
		वापस ret;

	ret = adv7511_init_regulators(adv7511);
	अगर (ret) अणु
		dev_err(dev, "failed to init regulators\n");
		वापस ret;
	पूर्ण

	/*
	 * The घातer करोwn GPIO is optional. If present, toggle it from active to
	 * inactive to wake up the encoder.
	 */
	adv7511->gpio_pd = devm_gpiod_get_optional(dev, "pd", GPIOD_OUT_HIGH);
	अगर (IS_ERR(adv7511->gpio_pd)) अणु
		ret = PTR_ERR(adv7511->gpio_pd);
		जाओ uninit_regulators;
	पूर्ण

	अगर (adv7511->gpio_pd) अणु
		usleep_range(5000, 6000);
		gpiod_set_value_cansleep(adv7511->gpio_pd, 0);
	पूर्ण

	adv7511->regmap = devm_regmap_init_i2c(i2c, &adv7511_regmap_config);
	अगर (IS_ERR(adv7511->regmap)) अणु
		ret = PTR_ERR(adv7511->regmap);
		जाओ uninit_regulators;
	पूर्ण

	ret = regmap_पढ़ो(adv7511->regmap, ADV7511_REG_CHIP_REVISION, &val);
	अगर (ret)
		जाओ uninit_regulators;
	dev_dbg(dev, "Rev. %d\n", val);

	अगर (adv7511->type == ADV7511)
		ret = regmap_रेजिस्टर_patch(adv7511->regmap,
					    adv7511_fixed_रेजिस्टरs,
					    ARRAY_SIZE(adv7511_fixed_रेजिस्टरs));
	अन्यथा
		ret = adv7533_patch_रेजिस्टरs(adv7511);
	अगर (ret)
		जाओ uninit_regulators;

	adv7511_packet_disable(adv7511, 0xffff);

	adv7511->i2c_edid = i2c_new_ancillary_device(i2c, "edid",
					ADV7511_EDID_I2C_ADDR_DEFAULT);
	अगर (IS_ERR(adv7511->i2c_edid)) अणु
		ret = PTR_ERR(adv7511->i2c_edid);
		जाओ uninit_regulators;
	पूर्ण

	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_EDID_I2C_ADDR,
		     adv7511->i2c_edid->addr << 1);

	adv7511->i2c_packet = i2c_new_ancillary_device(i2c, "packet",
					ADV7511_PACKET_I2C_ADDR_DEFAULT);
	अगर (IS_ERR(adv7511->i2c_packet)) अणु
		ret = PTR_ERR(adv7511->i2c_packet);
		जाओ err_i2c_unरेजिस्टर_edid;
	पूर्ण

	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_PACKET_I2C_ADDR,
		     adv7511->i2c_packet->addr << 1);

	ret = adv7511_init_cec_regmap(adv7511);
	अगर (ret)
		जाओ err_i2c_unरेजिस्टर_packet;

	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_CEC_I2C_ADDR,
		     adv7511->i2c_cec->addr << 1);

	INIT_WORK(&adv7511->hpd_work, adv7511_hpd_work);

	अगर (i2c->irq) अणु
		init_रुकोqueue_head(&adv7511->wq);

		ret = devm_request_thपढ़ोed_irq(dev, i2c->irq, शून्य,
						adv7511_irq_handler,
						IRQF_ONESHOT, dev_name(dev),
						adv7511);
		अगर (ret)
			जाओ err_unरेजिस्टर_cec;
	पूर्ण

	adv7511_घातer_off(adv7511);

	i2c_set_clientdata(i2c, adv7511);

	अगर (adv7511->type == ADV7511)
		adv7511_set_link_config(adv7511, &link_config);

	ret = adv7511_cec_init(dev, adv7511);
	अगर (ret)
		जाओ err_unरेजिस्टर_cec;

	adv7511->bridge.funcs = &adv7511_bridge_funcs;
	adv7511->bridge.ops = DRM_BRIDGE_OP_DETECT | DRM_BRIDGE_OP_EDID
			    | DRM_BRIDGE_OP_HPD;
	adv7511->bridge.of_node = dev->of_node;
	adv7511->bridge.type = DRM_MODE_CONNECTOR_HDMIA;

	drm_bridge_add(&adv7511->bridge);

	adv7511_audio_init(dev, adv7511);
	वापस 0;

err_unरेजिस्टर_cec:
	i2c_unरेजिस्टर_device(adv7511->i2c_cec);
	clk_disable_unprepare(adv7511->cec_clk);
err_i2c_unरेजिस्टर_packet:
	i2c_unरेजिस्टर_device(adv7511->i2c_packet);
err_i2c_unरेजिस्टर_edid:
	i2c_unरेजिस्टर_device(adv7511->i2c_edid);
uninit_regulators:
	adv7511_uninit_regulators(adv7511);

	वापस ret;
पूर्ण

अटल पूर्णांक adv7511_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा adv7511 *adv7511 = i2c_get_clientdata(i2c);

	अगर (adv7511->type == ADV7533 || adv7511->type == ADV7535)
		adv7533_detach_dsi(adv7511);
	i2c_unरेजिस्टर_device(adv7511->i2c_cec);
	clk_disable_unprepare(adv7511->cec_clk);

	adv7511_uninit_regulators(adv7511);

	drm_bridge_हटाओ(&adv7511->bridge);

	adv7511_audio_निकास(adv7511);

	cec_unरेजिस्टर_adapter(adv7511->cec_adap);

	i2c_unरेजिस्टर_device(adv7511->i2c_packet);
	i2c_unरेजिस्टर_device(adv7511->i2c_edid);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adv7511_i2c_ids[] = अणु
	अणु "adv7511", ADV7511 पूर्ण,
	अणु "adv7511w", ADV7511 पूर्ण,
	अणु "adv7513", ADV7511 पूर्ण,
	अणु "adv7533", ADV7533 पूर्ण,
	अणु "adv7535", ADV7535 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adv7511_i2c_ids);

अटल स्थिर काष्ठा of_device_id adv7511_of_ids[] = अणु
	अणु .compatible = "adi,adv7511", .data = (व्योम *)ADV7511 पूर्ण,
	अणु .compatible = "adi,adv7511w", .data = (व्योम *)ADV7511 पूर्ण,
	अणु .compatible = "adi,adv7513", .data = (व्योम *)ADV7511 पूर्ण,
	अणु .compatible = "adi,adv7533", .data = (व्योम *)ADV7533 पूर्ण,
	अणु .compatible = "adi,adv7535", .data = (व्योम *)ADV7535 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adv7511_of_ids);

अटल काष्ठा mipi_dsi_driver adv7533_dsi_driver = अणु
	.driver.name = "adv7533",
पूर्ण;

अटल काष्ठा i2c_driver adv7511_driver = अणु
	.driver = अणु
		.name = "adv7511",
		.of_match_table = adv7511_of_ids,
	पूर्ण,
	.id_table = adv7511_i2c_ids,
	.probe = adv7511_probe,
	.हटाओ = adv7511_हटाओ,
पूर्ण;

अटल पूर्णांक __init adv7511_init(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_DRM_MIPI_DSI))
		mipi_dsi_driver_रेजिस्टर(&adv7533_dsi_driver);

	वापस i2c_add_driver(&adv7511_driver);
पूर्ण
module_init(adv7511_init);

अटल व्योम __निकास adv7511_निकास(व्योम)
अणु
	i2c_del_driver(&adv7511_driver);

	अगर (IS_ENABLED(CONFIG_DRM_MIPI_DSI))
		mipi_dsi_driver_unरेजिस्टर(&adv7533_dsi_driver);
पूर्ण
module_निकास(adv7511_निकास);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("ADV7511 HDMI transmitter driver");
MODULE_LICENSE("GPL");
