<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "sun4i_backend.h"
#समावेश "sun4i_crtc.h"
#समावेश "sun4i_drv.h"
#समावेश "sun4i_hdmi.h"

अटल अंतरभूत काष्ठा sun4i_hdmi *
drm_encoder_to_sun4i_hdmi(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा sun4i_hdmi,
			    encoder);
पूर्ण

अटल अंतरभूत काष्ठा sun4i_hdmi *
drm_connector_to_sun4i_hdmi(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा sun4i_hdmi,
			    connector);
पूर्ण

अटल पूर्णांक sun4i_hdmi_setup_avi_infoframes(काष्ठा sun4i_hdmi *hdmi,
					   काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdmi_avi_infoframe frame;
	u8 buffer[17];
	पूर्णांक i, ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &hdmi->connector, mode);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to get infoframes from mode\n");
		वापस ret;
	पूर्ण

	ret = hdmi_avi_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to pack infoframes\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < माप(buffer); i++)
		ग_लिखोb(buffer[i], hdmi->base + SUN4I_HDMI_AVI_INFOFRAME_REG(i));

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_hdmi_atomic_check(काष्ठा drm_encoder *encoder,
				   काष्ठा drm_crtc_state *crtc_state,
				   काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_display_mode *mode = &crtc_state->mode;

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम sun4i_hdmi_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_hdmi *hdmi = drm_encoder_to_sun4i_hdmi(encoder);
	u32 val;

	DRM_DEBUG_DRIVER("Disabling the HDMI Output\n");

	val = पढ़ोl(hdmi->base + SUN4I_HDMI_VID_CTRL_REG);
	val &= ~SUN4I_HDMI_VID_CTRL_ENABLE;
	ग_लिखोl(val, hdmi->base + SUN4I_HDMI_VID_CTRL_REG);

	clk_disable_unprepare(hdmi->पंचांगds_clk);
पूर्ण

अटल व्योम sun4i_hdmi_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	काष्ठा sun4i_hdmi *hdmi = drm_encoder_to_sun4i_hdmi(encoder);
	u32 val = 0;

	DRM_DEBUG_DRIVER("Enabling the HDMI Output\n");

	clk_prepare_enable(hdmi->पंचांगds_clk);

	sun4i_hdmi_setup_avi_infoframes(hdmi, mode);
	val |= SUN4I_HDMI_PKT_CTRL_TYPE(0, SUN4I_HDMI_PKT_AVI);
	val |= SUN4I_HDMI_PKT_CTRL_TYPE(1, SUN4I_HDMI_PKT_END);
	ग_लिखोl(val, hdmi->base + SUN4I_HDMI_PKT_CTRL_REG(0));

	val = SUN4I_HDMI_VID_CTRL_ENABLE;
	अगर (hdmi->hdmi_monitor)
		val |= SUN4I_HDMI_VID_CTRL_HDMI_MODE;

	ग_लिखोl(val, hdmi->base + SUN4I_HDMI_VID_CTRL_REG);
पूर्ण

अटल व्योम sun4i_hdmi_mode_set(काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sun4i_hdmi *hdmi = drm_encoder_to_sun4i_hdmi(encoder);
	अचिन्हित पूर्णांक x, y;
	u32 val;

	clk_set_rate(hdmi->mod_clk, mode->crtc_घड़ी * 1000);
	clk_set_rate(hdmi->पंचांगds_clk, mode->crtc_घड़ी * 1000);

	/* Set input sync enable */
	ग_लिखोl(SUN4I_HDMI_UNKNOWN_INPUT_SYNC,
	       hdmi->base + SUN4I_HDMI_UNKNOWN_REG);

	/*
	 * Setup output pad (?) controls
	 *
	 * This is करोne here instead of at probe/bind समय because
	 * the controller seems to toggle some of the bits on its own.
	 *
	 * We can't just initialize the रेजिस्टर there, we need to
	 * protect the घड़ी bits that have alपढ़ोy been पढ़ो out and
	 * cached by the घड़ी framework.
	 */
	val = पढ़ोl(hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);
	val &= SUN4I_HDMI_PAD_CTRL1_HALVE_CLK;
	val |= hdmi->variant->pad_ctrl1_init_val;
	ग_लिखोl(val, hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);
	val = पढ़ोl(hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);

	/* Setup timing रेजिस्टरs */
	ग_लिखोl(SUN4I_HDMI_VID_TIMING_X(mode->hdisplay) |
	       SUN4I_HDMI_VID_TIMING_Y(mode->vdisplay),
	       hdmi->base + SUN4I_HDMI_VID_TIMING_ACT_REG);

	x = mode->htotal - mode->hsync_start;
	y = mode->vtotal - mode->vsync_start;
	ग_लिखोl(SUN4I_HDMI_VID_TIMING_X(x) | SUN4I_HDMI_VID_TIMING_Y(y),
	       hdmi->base + SUN4I_HDMI_VID_TIMING_BP_REG);

	x = mode->hsync_start - mode->hdisplay;
	y = mode->vsync_start - mode->vdisplay;
	ग_लिखोl(SUN4I_HDMI_VID_TIMING_X(x) | SUN4I_HDMI_VID_TIMING_Y(y),
	       hdmi->base + SUN4I_HDMI_VID_TIMING_FP_REG);

	x = mode->hsync_end - mode->hsync_start;
	y = mode->vsync_end - mode->vsync_start;
	ग_लिखोl(SUN4I_HDMI_VID_TIMING_X(x) | SUN4I_HDMI_VID_TIMING_Y(y),
	       hdmi->base + SUN4I_HDMI_VID_TIMING_SPW_REG);

	val = SUN4I_HDMI_VID_TIMING_POL_TX_CLK;
	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		val |= SUN4I_HDMI_VID_TIMING_POL_HSYNC;

	अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
		val |= SUN4I_HDMI_VID_TIMING_POL_VSYNC;

	ग_लिखोl(val, hdmi->base + SUN4I_HDMI_VID_TIMING_POL_REG);
पूर्ण

अटल क्रमागत drm_mode_status sun4i_hdmi_mode_valid(काष्ठा drm_encoder *encoder,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा sun4i_hdmi *hdmi = drm_encoder_to_sun4i_hdmi(encoder);
	अचिन्हित दीर्घ rate = mode->घड़ी * 1000;
	अचिन्हित दीर्घ dअगरf = rate / 200; /* +-0.5% allowed by HDMI spec */
	दीर्घ rounded_rate;

	/* 165 MHz is the typical max pixelघड़ी frequency क्रम HDMI <= 1.2 */
	अगर (rate > 165000000)
		वापस MODE_CLOCK_HIGH;
	rounded_rate = clk_round_rate(hdmi->पंचांगds_clk, rate);
	अगर (rounded_rate > 0 &&
	    max_t(अचिन्हित दीर्घ, rounded_rate, rate) -
	    min_t(अचिन्हित दीर्घ, rounded_rate, rate) < dअगरf)
		वापस MODE_OK;
	वापस MODE_NOCLOCK;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs sun4i_hdmi_helper_funcs = अणु
	.atomic_check	= sun4i_hdmi_atomic_check,
	.disable	= sun4i_hdmi_disable,
	.enable		= sun4i_hdmi_enable,
	.mode_set	= sun4i_hdmi_mode_set,
	.mode_valid	= sun4i_hdmi_mode_valid,
पूर्ण;

अटल पूर्णांक sun4i_hdmi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा sun4i_hdmi *hdmi = drm_connector_to_sun4i_hdmi(connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	edid = drm_get_edid(connector, hdmi->ddc_i2c ?: hdmi->i2c);
	अगर (!edid)
		वापस 0;

	hdmi->hdmi_monitor = drm_detect_hdmi_monitor(edid);
	DRM_DEBUG_DRIVER("Monitor is %s monitor\n",
			 hdmi->hdmi_monitor ? "an HDMI" : "a DVI");

	drm_connector_update_edid_property(connector, edid);
	cec_s_phys_addr_from_edid(hdmi->cec_adap, edid);
	ret = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल काष्ठा i2c_adapter *sun4i_hdmi_get_ddc(काष्ठा device *dev)
अणु
	काष्ठा device_node *phandle, *remote;
	काष्ठा i2c_adapter *ddc;

	remote = of_graph_get_remote_node(dev->of_node, 1, -1);
	अगर (!remote)
		वापस ERR_PTR(-EINVAL);

	phandle = of_parse_phandle(remote, "ddc-i2c-bus", 0);
	of_node_put(remote);
	अगर (!phandle)
		वापस ERR_PTR(-ENODEV);

	ddc = of_get_i2c_adapter_by_node(phandle);
	of_node_put(phandle);
	अगर (!ddc)
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस ddc;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs sun4i_hdmi_connector_helper_funcs = अणु
	.get_modes	= sun4i_hdmi_get_modes,
पूर्ण;

अटल क्रमागत drm_connector_status
sun4i_hdmi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा sun4i_hdmi *hdmi = drm_connector_to_sun4i_hdmi(connector);
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(hdmi->base + SUN4I_HDMI_HPD_REG);
	अगर (!(reg & SUN4I_HDMI_HPD_HIGH)) अणु
		cec_phys_addr_invalidate(hdmi->cec_adap);
		वापस connector_status_disconnected;
	पूर्ण

	वापस connector_status_connected;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sun4i_hdmi_connector_funcs = अणु
	.detect			= sun4i_hdmi_connector_detect,
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= drm_connector_cleanup,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

#अगर_घोषित CONFIG_DRM_SUN4I_HDMI_CEC
अटल पूर्णांक sun4i_hdmi_cec_pin_पढ़ो(काष्ठा cec_adapter *adap)
अणु
	काष्ठा sun4i_hdmi *hdmi = cec_get_drvdata(adap);

	वापस पढ़ोl(hdmi->base + SUN4I_HDMI_CEC) & SUN4I_HDMI_CEC_RX;
पूर्ण

अटल व्योम sun4i_hdmi_cec_pin_low(काष्ठा cec_adapter *adap)
अणु
	काष्ठा sun4i_hdmi *hdmi = cec_get_drvdata(adap);

	/* Start driving the CEC pin low */
	ग_लिखोl(SUN4I_HDMI_CEC_ENABLE, hdmi->base + SUN4I_HDMI_CEC);
पूर्ण

अटल व्योम sun4i_hdmi_cec_pin_high(काष्ठा cec_adapter *adap)
अणु
	काष्ठा sun4i_hdmi *hdmi = cec_get_drvdata(adap);

	/*
	 * Stop driving the CEC pin, the pull up will take over
	 * unless another CEC device is driving the pin low.
	 */
	ग_लिखोl(0, hdmi->base + SUN4I_HDMI_CEC);
पूर्ण

अटल स्थिर काष्ठा cec_pin_ops sun4i_hdmi_cec_pin_ops = अणु
	.पढ़ो = sun4i_hdmi_cec_pin_पढ़ो,
	.low = sun4i_hdmi_cec_pin_low,
	.high = sun4i_hdmi_cec_pin_high,
पूर्ण;
#पूर्ण_अगर

#घोषणा SUN4I_HDMI_PAD_CTRL1_MASK	(GENMASK(24, 7) | GENMASK(5, 0))
#घोषणा SUN4I_HDMI_PLL_CTRL_MASK	(GENMASK(31, 8) | GENMASK(3, 0))

/* Only dअगरference from sun5i is AMP is 4 instead of 6 */
अटल स्थिर काष्ठा sun4i_hdmi_variant sun4i_variant = अणु
	.pad_ctrl0_init_val	= SUN4I_HDMI_PAD_CTRL0_TXEN |
				  SUN4I_HDMI_PAD_CTRL0_CKEN |
				  SUN4I_HDMI_PAD_CTRL0_PWENG |
				  SUN4I_HDMI_PAD_CTRL0_PWEND |
				  SUN4I_HDMI_PAD_CTRL0_PWENC |
				  SUN4I_HDMI_PAD_CTRL0_LDODEN |
				  SUN4I_HDMI_PAD_CTRL0_LDOCEN |
				  SUN4I_HDMI_PAD_CTRL0_BIASEN,
	.pad_ctrl1_init_val	= SUN4I_HDMI_PAD_CTRL1_REG_AMP(4) |
				  SUN4I_HDMI_PAD_CTRL1_REG_EMP(2) |
				  SUN4I_HDMI_PAD_CTRL1_REG_DENCK |
				  SUN4I_HDMI_PAD_CTRL1_REG_DEN |
				  SUN4I_HDMI_PAD_CTRL1_EMPCK_OPT |
				  SUN4I_HDMI_PAD_CTRL1_EMP_OPT |
				  SUN4I_HDMI_PAD_CTRL1_AMPCK_OPT |
				  SUN4I_HDMI_PAD_CTRL1_AMP_OPT,
	.pll_ctrl_init_val	= SUN4I_HDMI_PLL_CTRL_VCO_S(8) |
				  SUN4I_HDMI_PLL_CTRL_CS(7) |
				  SUN4I_HDMI_PLL_CTRL_CP_S(15) |
				  SUN4I_HDMI_PLL_CTRL_S(7) |
				  SUN4I_HDMI_PLL_CTRL_VCO_GAIN(4) |
				  SUN4I_HDMI_PLL_CTRL_SDIV2 |
				  SUN4I_HDMI_PLL_CTRL_LDO2_EN |
				  SUN4I_HDMI_PLL_CTRL_LDO1_EN |
				  SUN4I_HDMI_PLL_CTRL_HV_IS_33 |
				  SUN4I_HDMI_PLL_CTRL_BWS |
				  SUN4I_HDMI_PLL_CTRL_PLL_EN,

	.ddc_clk_reg		= REG_FIELD(SUN4I_HDMI_DDC_CLK_REG, 0, 6),
	.ddc_clk_pre_भागider	= 2,
	.ddc_clk_m_offset	= 1,

	.field_ddc_en		= REG_FIELD(SUN4I_HDMI_DDC_CTRL_REG, 31, 31),
	.field_ddc_start	= REG_FIELD(SUN4I_HDMI_DDC_CTRL_REG, 30, 30),
	.field_ddc_reset	= REG_FIELD(SUN4I_HDMI_DDC_CTRL_REG, 0, 0),
	.field_ddc_addr_reg	= REG_FIELD(SUN4I_HDMI_DDC_ADDR_REG, 0, 31),
	.field_ddc_slave_addr	= REG_FIELD(SUN4I_HDMI_DDC_ADDR_REG, 0, 6),
	.field_ddc_पूर्णांक_status	= REG_FIELD(SUN4I_HDMI_DDC_INT_STATUS_REG, 0, 8),
	.field_ddc_fअगरo_clear	= REG_FIELD(SUN4I_HDMI_DDC_FIFO_CTRL_REG, 31, 31),
	.field_ddc_fअगरo_rx_thres = REG_FIELD(SUN4I_HDMI_DDC_FIFO_CTRL_REG, 4, 7),
	.field_ddc_fअगरo_tx_thres = REG_FIELD(SUN4I_HDMI_DDC_FIFO_CTRL_REG, 0, 3),
	.field_ddc_byte_count	= REG_FIELD(SUN4I_HDMI_DDC_BYTE_COUNT_REG, 0, 9),
	.field_ddc_cmd		= REG_FIELD(SUN4I_HDMI_DDC_CMD_REG, 0, 2),
	.field_ddc_sda_en	= REG_FIELD(SUN4I_HDMI_DDC_LINE_CTRL_REG, 9, 9),
	.field_ddc_sck_en	= REG_FIELD(SUN4I_HDMI_DDC_LINE_CTRL_REG, 8, 8),

	.ddc_fअगरo_reg		= SUN4I_HDMI_DDC_FIFO_DATA_REG,
	.ddc_fअगरo_has_dir	= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_hdmi_variant sun5i_variant = अणु
	.pad_ctrl0_init_val	= SUN4I_HDMI_PAD_CTRL0_TXEN |
				  SUN4I_HDMI_PAD_CTRL0_CKEN |
				  SUN4I_HDMI_PAD_CTRL0_PWENG |
				  SUN4I_HDMI_PAD_CTRL0_PWEND |
				  SUN4I_HDMI_PAD_CTRL0_PWENC |
				  SUN4I_HDMI_PAD_CTRL0_LDODEN |
				  SUN4I_HDMI_PAD_CTRL0_LDOCEN |
				  SUN4I_HDMI_PAD_CTRL0_BIASEN,
	.pad_ctrl1_init_val	= SUN4I_HDMI_PAD_CTRL1_REG_AMP(6) |
				  SUN4I_HDMI_PAD_CTRL1_REG_EMP(2) |
				  SUN4I_HDMI_PAD_CTRL1_REG_DENCK |
				  SUN4I_HDMI_PAD_CTRL1_REG_DEN |
				  SUN4I_HDMI_PAD_CTRL1_EMPCK_OPT |
				  SUN4I_HDMI_PAD_CTRL1_EMP_OPT |
				  SUN4I_HDMI_PAD_CTRL1_AMPCK_OPT |
				  SUN4I_HDMI_PAD_CTRL1_AMP_OPT,
	.pll_ctrl_init_val	= SUN4I_HDMI_PLL_CTRL_VCO_S(8) |
				  SUN4I_HDMI_PLL_CTRL_CS(7) |
				  SUN4I_HDMI_PLL_CTRL_CP_S(15) |
				  SUN4I_HDMI_PLL_CTRL_S(7) |
				  SUN4I_HDMI_PLL_CTRL_VCO_GAIN(4) |
				  SUN4I_HDMI_PLL_CTRL_SDIV2 |
				  SUN4I_HDMI_PLL_CTRL_LDO2_EN |
				  SUN4I_HDMI_PLL_CTRL_LDO1_EN |
				  SUN4I_HDMI_PLL_CTRL_HV_IS_33 |
				  SUN4I_HDMI_PLL_CTRL_BWS |
				  SUN4I_HDMI_PLL_CTRL_PLL_EN,

	.ddc_clk_reg		= REG_FIELD(SUN4I_HDMI_DDC_CLK_REG, 0, 6),
	.ddc_clk_pre_भागider	= 2,
	.ddc_clk_m_offset	= 1,

	.field_ddc_en		= REG_FIELD(SUN4I_HDMI_DDC_CTRL_REG, 31, 31),
	.field_ddc_start	= REG_FIELD(SUN4I_HDMI_DDC_CTRL_REG, 30, 30),
	.field_ddc_reset	= REG_FIELD(SUN4I_HDMI_DDC_CTRL_REG, 0, 0),
	.field_ddc_addr_reg	= REG_FIELD(SUN4I_HDMI_DDC_ADDR_REG, 0, 31),
	.field_ddc_slave_addr	= REG_FIELD(SUN4I_HDMI_DDC_ADDR_REG, 0, 6),
	.field_ddc_पूर्णांक_status	= REG_FIELD(SUN4I_HDMI_DDC_INT_STATUS_REG, 0, 8),
	.field_ddc_fअगरo_clear	= REG_FIELD(SUN4I_HDMI_DDC_FIFO_CTRL_REG, 31, 31),
	.field_ddc_fअगरo_rx_thres = REG_FIELD(SUN4I_HDMI_DDC_FIFO_CTRL_REG, 4, 7),
	.field_ddc_fअगरo_tx_thres = REG_FIELD(SUN4I_HDMI_DDC_FIFO_CTRL_REG, 0, 3),
	.field_ddc_byte_count	= REG_FIELD(SUN4I_HDMI_DDC_BYTE_COUNT_REG, 0, 9),
	.field_ddc_cmd		= REG_FIELD(SUN4I_HDMI_DDC_CMD_REG, 0, 2),
	.field_ddc_sda_en	= REG_FIELD(SUN4I_HDMI_DDC_LINE_CTRL_REG, 9, 9),
	.field_ddc_sck_en	= REG_FIELD(SUN4I_HDMI_DDC_LINE_CTRL_REG, 8, 8),

	.ddc_fअगरo_reg		= SUN4I_HDMI_DDC_FIFO_DATA_REG,
	.ddc_fअगरo_has_dir	= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_hdmi_variant sun6i_variant = अणु
	.has_ddc_parent_clk	= true,
	.has_reset_control	= true,
	.pad_ctrl0_init_val	= 0xff |
				  SUN4I_HDMI_PAD_CTRL0_TXEN |
				  SUN4I_HDMI_PAD_CTRL0_CKEN |
				  SUN4I_HDMI_PAD_CTRL0_PWENG |
				  SUN4I_HDMI_PAD_CTRL0_PWEND |
				  SUN4I_HDMI_PAD_CTRL0_PWENC |
				  SUN4I_HDMI_PAD_CTRL0_LDODEN |
				  SUN4I_HDMI_PAD_CTRL0_LDOCEN,
	.pad_ctrl1_init_val	= SUN4I_HDMI_PAD_CTRL1_REG_AMP(6) |
				  SUN4I_HDMI_PAD_CTRL1_REG_EMP(4) |
				  SUN4I_HDMI_PAD_CTRL1_REG_DENCK |
				  SUN4I_HDMI_PAD_CTRL1_REG_DEN |
				  SUN4I_HDMI_PAD_CTRL1_EMPCK_OPT |
				  SUN4I_HDMI_PAD_CTRL1_EMP_OPT |
				  SUN4I_HDMI_PAD_CTRL1_PWSDT |
				  SUN4I_HDMI_PAD_CTRL1_PWSCK |
				  SUN4I_HDMI_PAD_CTRL1_AMPCK_OPT |
				  SUN4I_HDMI_PAD_CTRL1_AMP_OPT |
				  SUN4I_HDMI_PAD_CTRL1_UNKNOWN,
	.pll_ctrl_init_val	= SUN4I_HDMI_PLL_CTRL_VCO_S(8) |
				  SUN4I_HDMI_PLL_CTRL_CS(3) |
				  SUN4I_HDMI_PLL_CTRL_CP_S(10) |
				  SUN4I_HDMI_PLL_CTRL_S(4) |
				  SUN4I_HDMI_PLL_CTRL_VCO_GAIN(4) |
				  SUN4I_HDMI_PLL_CTRL_SDIV2 |
				  SUN4I_HDMI_PLL_CTRL_LDO2_EN |
				  SUN4I_HDMI_PLL_CTRL_LDO1_EN |
				  SUN4I_HDMI_PLL_CTRL_HV_IS_33 |
				  SUN4I_HDMI_PLL_CTRL_PLL_EN,

	.ddc_clk_reg		= REG_FIELD(SUN6I_HDMI_DDC_CLK_REG, 0, 6),
	.ddc_clk_pre_भागider	= 1,
	.ddc_clk_m_offset	= 2,

	.पंचांगds_clk_भाग_offset	= 1,

	.field_ddc_en		= REG_FIELD(SUN6I_HDMI_DDC_CTRL_REG, 0, 0),
	.field_ddc_start	= REG_FIELD(SUN6I_HDMI_DDC_CTRL_REG, 27, 27),
	.field_ddc_reset	= REG_FIELD(SUN6I_HDMI_DDC_CTRL_REG, 31, 31),
	.field_ddc_addr_reg	= REG_FIELD(SUN6I_HDMI_DDC_ADDR_REG, 1, 31),
	.field_ddc_slave_addr	= REG_FIELD(SUN6I_HDMI_DDC_ADDR_REG, 1, 7),
	.field_ddc_पूर्णांक_status	= REG_FIELD(SUN6I_HDMI_DDC_INT_STATUS_REG, 0, 8),
	.field_ddc_fअगरo_clear	= REG_FIELD(SUN6I_HDMI_DDC_FIFO_CTRL_REG, 18, 18),
	.field_ddc_fअगरo_rx_thres = REG_FIELD(SUN6I_HDMI_DDC_FIFO_CTRL_REG, 4, 7),
	.field_ddc_fअगरo_tx_thres = REG_FIELD(SUN6I_HDMI_DDC_FIFO_CTRL_REG, 0, 3),
	.field_ddc_byte_count	= REG_FIELD(SUN6I_HDMI_DDC_CMD_REG, 16, 25),
	.field_ddc_cmd		= REG_FIELD(SUN6I_HDMI_DDC_CMD_REG, 0, 2),
	.field_ddc_sda_en	= REG_FIELD(SUN6I_HDMI_DDC_CTRL_REG, 6, 6),
	.field_ddc_sck_en	= REG_FIELD(SUN6I_HDMI_DDC_CTRL_REG, 4, 4),

	.ddc_fअगरo_reg		= SUN6I_HDMI_DDC_FIFO_DATA_REG,
	.ddc_fअगरo_thres_incl	= true,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun4i_hdmi_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= 0x580,
पूर्ण;

अटल पूर्णांक sun4i_hdmi_bind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा cec_connector_info conn_info;
	काष्ठा sun4i_drv *drv = drm->dev_निजी;
	काष्ठा sun4i_hdmi *hdmi;
	काष्ठा resource *res;
	u32 reg;
	पूर्णांक ret;

	hdmi = devm_kzalloc(dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;
	dev_set_drvdata(dev, hdmi);
	hdmi->dev = dev;
	hdmi->drv = drv;

	hdmi->variant = of_device_get_match_data(dev);
	अगर (!hdmi->variant)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hdmi->base)) अणु
		dev_err(dev, "Couldn't map the HDMI encoder registers\n");
		वापस PTR_ERR(hdmi->base);
	पूर्ण

	अगर (hdmi->variant->has_reset_control) अणु
		hdmi->reset = devm_reset_control_get(dev, शून्य);
		अगर (IS_ERR(hdmi->reset)) अणु
			dev_err(dev, "Couldn't get the HDMI reset control\n");
			वापस PTR_ERR(hdmi->reset);
		पूर्ण

		ret = reset_control_deनिश्चित(hdmi->reset);
		अगर (ret) अणु
			dev_err(dev, "Couldn't deassert HDMI reset\n");
			वापस ret;
		पूर्ण
	पूर्ण

	hdmi->bus_clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(hdmi->bus_clk)) अणु
		dev_err(dev, "Couldn't get the HDMI bus clock\n");
		ret = PTR_ERR(hdmi->bus_clk);
		जाओ err_निश्चित_reset;
	पूर्ण
	clk_prepare_enable(hdmi->bus_clk);

	hdmi->mod_clk = devm_clk_get(dev, "mod");
	अगर (IS_ERR(hdmi->mod_clk)) अणु
		dev_err(dev, "Couldn't get the HDMI mod clock\n");
		ret = PTR_ERR(hdmi->mod_clk);
		जाओ err_disable_bus_clk;
	पूर्ण
	clk_prepare_enable(hdmi->mod_clk);

	hdmi->pll0_clk = devm_clk_get(dev, "pll-0");
	अगर (IS_ERR(hdmi->pll0_clk)) अणु
		dev_err(dev, "Couldn't get the HDMI PLL 0 clock\n");
		ret = PTR_ERR(hdmi->pll0_clk);
		जाओ err_disable_mod_clk;
	पूर्ण

	hdmi->pll1_clk = devm_clk_get(dev, "pll-1");
	अगर (IS_ERR(hdmi->pll1_clk)) अणु
		dev_err(dev, "Couldn't get the HDMI PLL 1 clock\n");
		ret = PTR_ERR(hdmi->pll1_clk);
		जाओ err_disable_mod_clk;
	पूर्ण

	hdmi->regmap = devm_regmap_init_mmio(dev, hdmi->base,
					     &sun4i_hdmi_regmap_config);
	अगर (IS_ERR(hdmi->regmap)) अणु
		dev_err(dev, "Couldn't create HDMI encoder regmap\n");
		ret = PTR_ERR(hdmi->regmap);
		जाओ err_disable_mod_clk;
	पूर्ण

	ret = sun4i_पंचांगds_create(hdmi);
	अगर (ret) अणु
		dev_err(dev, "Couldn't create the TMDS clock\n");
		जाओ err_disable_mod_clk;
	पूर्ण

	अगर (hdmi->variant->has_ddc_parent_clk) अणु
		hdmi->ddc_parent_clk = devm_clk_get(dev, "ddc");
		अगर (IS_ERR(hdmi->ddc_parent_clk)) अणु
			dev_err(dev, "Couldn't get the HDMI DDC clock\n");
			ret = PTR_ERR(hdmi->ddc_parent_clk);
			जाओ err_disable_mod_clk;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdmi->ddc_parent_clk = hdmi->पंचांगds_clk;
	पूर्ण

	ग_लिखोl(SUN4I_HDMI_CTRL_ENABLE, hdmi->base + SUN4I_HDMI_CTRL_REG);

	ग_लिखोl(hdmi->variant->pad_ctrl0_init_val,
	       hdmi->base + SUN4I_HDMI_PAD_CTRL0_REG);

	reg = पढ़ोl(hdmi->base + SUN4I_HDMI_PLL_CTRL_REG);
	reg &= SUN4I_HDMI_PLL_CTRL_DIV_MASK;
	reg |= hdmi->variant->pll_ctrl_init_val;
	ग_लिखोl(reg, hdmi->base + SUN4I_HDMI_PLL_CTRL_REG);

	ret = sun4i_hdmi_i2c_create(dev, hdmi);
	अगर (ret) अणु
		dev_err(dev, "Couldn't create the HDMI I2C adapter\n");
		जाओ err_disable_mod_clk;
	पूर्ण

	hdmi->ddc_i2c = sun4i_hdmi_get_ddc(dev);
	अगर (IS_ERR(hdmi->ddc_i2c)) अणु
		ret = PTR_ERR(hdmi->ddc_i2c);
		अगर (ret == -ENODEV)
			hdmi->ddc_i2c = शून्य;
		अन्यथा
			जाओ err_del_i2c_adapter;
	पूर्ण

	drm_encoder_helper_add(&hdmi->encoder,
			       &sun4i_hdmi_helper_funcs);
	ret = drm_simple_encoder_init(drm, &hdmi->encoder,
				      DRM_MODE_ENCODER_TMDS);
	अगर (ret) अणु
		dev_err(dev, "Couldn't initialise the HDMI encoder\n");
		जाओ err_put_ddc_i2c;
	पूर्ण

	hdmi->encoder.possible_crtcs = drm_of_find_possible_crtcs(drm,
								  dev->of_node);
	अगर (!hdmi->encoder.possible_crtcs) अणु
		ret = -EPROBE_DEFER;
		जाओ err_put_ddc_i2c;
	पूर्ण

#अगर_घोषित CONFIG_DRM_SUN4I_HDMI_CEC
	hdmi->cec_adap = cec_pin_allocate_adapter(&sun4i_hdmi_cec_pin_ops,
		hdmi, "sun4i", CEC_CAP_DEFAULTS | CEC_CAP_CONNECTOR_INFO);
	ret = PTR_ERR_OR_ZERO(hdmi->cec_adap);
	अगर (ret < 0)
		जाओ err_cleanup_connector;
	ग_लिखोl(पढ़ोl(hdmi->base + SUN4I_HDMI_CEC) & ~SUN4I_HDMI_CEC_TX,
	       hdmi->base + SUN4I_HDMI_CEC);
#पूर्ण_अगर

	drm_connector_helper_add(&hdmi->connector,
				 &sun4i_hdmi_connector_helper_funcs);
	ret = drm_connector_init_with_ddc(drm, &hdmi->connector,
					  &sun4i_hdmi_connector_funcs,
					  DRM_MODE_CONNECTOR_HDMIA,
					  hdmi->ddc_i2c);
	अगर (ret) अणु
		dev_err(dev,
			"Couldn't initialise the HDMI connector\n");
		जाओ err_cleanup_connector;
	पूर्ण
	cec_fill_conn_info_from_drm(&conn_info, &hdmi->connector);
	cec_s_conn_info(hdmi->cec_adap, &conn_info);

	/* There is no HPD पूर्णांकerrupt, so we need to poll the controller */
	hdmi->connector.polled = DRM_CONNECTOR_POLL_CONNECT |
		DRM_CONNECTOR_POLL_DISCONNECT;

	ret = cec_रेजिस्टर_adapter(hdmi->cec_adap, dev);
	अगर (ret < 0)
		जाओ err_cleanup_connector;
	drm_connector_attach_encoder(&hdmi->connector, &hdmi->encoder);

	वापस 0;

err_cleanup_connector:
	cec_delete_adapter(hdmi->cec_adap);
	drm_encoder_cleanup(&hdmi->encoder);
err_put_ddc_i2c:
	i2c_put_adapter(hdmi->ddc_i2c);
err_del_i2c_adapter:
	i2c_del_adapter(hdmi->i2c);
err_disable_mod_clk:
	clk_disable_unprepare(hdmi->mod_clk);
err_disable_bus_clk:
	clk_disable_unprepare(hdmi->bus_clk);
err_निश्चित_reset:
	reset_control_निश्चित(hdmi->reset);
	वापस ret;
पूर्ण

अटल व्योम sun4i_hdmi_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा sun4i_hdmi *hdmi = dev_get_drvdata(dev);

	cec_unरेजिस्टर_adapter(hdmi->cec_adap);
	i2c_del_adapter(hdmi->i2c);
	i2c_put_adapter(hdmi->ddc_i2c);
	clk_disable_unprepare(hdmi->mod_clk);
	clk_disable_unprepare(hdmi->bus_clk);
पूर्ण

अटल स्थिर काष्ठा component_ops sun4i_hdmi_ops = अणु
	.bind	= sun4i_hdmi_bind,
	.unbind	= sun4i_hdmi_unbind,
पूर्ण;

अटल पूर्णांक sun4i_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sun4i_hdmi_ops);
पूर्ण

अटल पूर्णांक sun4i_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun4i_hdmi_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_hdmi_of_table[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-hdmi", .data = &sun4i_variant, पूर्ण,
	अणु .compatible = "allwinner,sun5i-a10s-hdmi", .data = &sun5i_variant, पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-hdmi", .data = &sun6i_variant, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_hdmi_of_table);

अटल काष्ठा platक्रमm_driver sun4i_hdmi_driver = अणु
	.probe		= sun4i_hdmi_probe,
	.हटाओ		= sun4i_hdmi_हटाओ,
	.driver		= अणु
		.name		= "sun4i-hdmi",
		.of_match_table	= sun4i_hdmi_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_hdmi_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A10 HDMI Driver");
MODULE_LICENSE("GPL");
