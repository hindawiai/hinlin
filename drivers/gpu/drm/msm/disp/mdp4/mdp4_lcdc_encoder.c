<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 * Author: Vinay Simha <vinaysimha@inक्रमcecomputing.com>
 */

#समावेश <linux/delay.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "mdp4_kms.h"

काष्ठा mdp4_lcdc_encoder अणु
	काष्ठा drm_encoder base;
	काष्ठा device_node *panel_node;
	काष्ठा drm_panel *panel;
	काष्ठा clk *lcdc_clk;
	अचिन्हित दीर्घ पूर्णांक pixघड़ी;
	काष्ठा regulator *regs[3];
	bool enabled;
	uपूर्णांक32_t bsc;
पूर्ण;
#घोषणा to_mdp4_lcdc_encoder(x) container_of(x, काष्ठा mdp4_lcdc_encoder, base)

अटल काष्ठा mdp4_kms *get_kms(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा msm_drm_निजी *priv = encoder->dev->dev_निजी;
	वापस to_mdp4_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल व्योम mdp4_lcdc_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp4_lcdc_encoder *mdp4_lcdc_encoder =
			to_mdp4_lcdc_encoder(encoder);
	drm_encoder_cleanup(encoder);
	kमुक्त(mdp4_lcdc_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs mdp4_lcdc_encoder_funcs = अणु
	.destroy = mdp4_lcdc_encoder_destroy,
पूर्ण;

/* this should probably be a helper: */
अटल काष्ठा drm_connector *get_connector(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_connector *connector;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head)
		अगर (connector->encoder == encoder)
			वापस connector;

	वापस शून्य;
पूर्ण

अटल व्योम setup_phy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_connector *connector = get_connector(encoder);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(encoder);
	uपूर्णांक32_t lvds_पूर्णांकf = 0, lvds_phy_cfg0 = 0;
	पूर्णांक bpp, nchan, swap;

	अगर (!connector)
		वापस;

	bpp = 3 * connector->display_info.bpc;

	अगर (!bpp)
		bpp = 18;

	/* TODO, these should come from panel somehow: */
	nchan = 1;
	swap = 0;

	चयन (bpp) अणु
	हाल 24:
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(0),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x08) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x05) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x04) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x03));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(0),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x02) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x01) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x00));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(1),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x11) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x10) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x0d) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x0c));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(1),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x0b) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x0a) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x09));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(2),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x1a) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x19) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x18) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x15));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(2),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x14) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x13) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x12));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(3),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x1b) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x17) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x16) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x0f));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(3),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x0e) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x07) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x06));
		अगर (nchan == 2) अणु
			lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE3_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE0_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE3_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN;
		पूर्ण अन्यथा अणु
			lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE3_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN;
		पूर्ण
		अवरोध;

	हाल 18:
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(0),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x0a) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x07) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x06) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x05));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(0),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x04) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x03) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x02));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(1),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x13) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x12) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x0f) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x0e));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(1),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x0d) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x0c) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x0b));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(2),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x1a) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x19) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x18) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x17));
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(2),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x16) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x15) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x14));
		अगर (nchan == 2) अणु
			lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE0_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN;
		पूर्ण अन्यथा अणु
			lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN;
		पूर्ण
		lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_RGB_OUT;
		अवरोध;

	शेष:
		DRM_DEV_ERROR(dev->dev, "unknown bpp: %d\n", bpp);
		वापस;
	पूर्ण

	चयन (nchan) अणु
	हाल 1:
		lvds_phy_cfg0 = MDP4_LVDS_PHY_CFG0_CHANNEL0;
		lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_CH1_CLK_LANE_EN |
				MDP4_LCDC_LVDS_INTF_CTL_MODE_SEL;
		अवरोध;
	हाल 2:
		lvds_phy_cfg0 = MDP4_LVDS_PHY_CFG0_CHANNEL0 |
				MDP4_LVDS_PHY_CFG0_CHANNEL1;
		lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_CH2_CLK_LANE_EN |
				MDP4_LCDC_LVDS_INTF_CTL_CH1_CLK_LANE_EN;
		अवरोध;
	शेष:
		DRM_DEV_ERROR(dev->dev, "unknown # of channels: %d\n", nchan);
		वापस;
	पूर्ण

	अगर (swap)
		lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_CH_SWAP;

	lvds_पूर्णांकf |= MDP4_LCDC_LVDS_INTF_CTL_ENABLE;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LVDS_PHY_CFG0, lvds_phy_cfg0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_LVDS_INTF_CTL, lvds_पूर्णांकf);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LVDS_PHY_CFG2, 0x30);

	mb();
	udelay(1);
	lvds_phy_cfg0 |= MDP4_LVDS_PHY_CFG0_SERIALIZATION_ENBLE;
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LVDS_PHY_CFG0, lvds_phy_cfg0);
पूर्ण

अटल व्योम mdp4_lcdc_encoder_mode_set(काष्ठा drm_encoder *encoder,
		काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा mdp4_lcdc_encoder *mdp4_lcdc_encoder =
			to_mdp4_lcdc_encoder(encoder);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(encoder);
	uपूर्णांक32_t lcdc_hsync_skew, vsync_period, vsync_len, ctrl_pol;
	uपूर्णांक32_t display_v_start, display_v_end;
	uपूर्णांक32_t hsync_start_x, hsync_end_x;

	mode = adjusted_mode;

	DBG("set mode: " DRM_MODE_FMT, DRM_MODE_ARG(mode));

	mdp4_lcdc_encoder->pixघड़ी = mode->घड़ी * 1000;

	DBG("pixclock=%lu", mdp4_lcdc_encoder->pixघड़ी);

	ctrl_pol = 0;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		ctrl_pol |= MDP4_LCDC_CTRL_POLARITY_HSYNC_LOW;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		ctrl_pol |= MDP4_LCDC_CTRL_POLARITY_VSYNC_LOW;
	/* probably need to get DATA_EN polarity from panel.. */

	lcdc_hsync_skew = 0;  /* get this from panel? */

	hsync_start_x = (mode->htotal - mode->hsync_start);
	hsync_end_x = mode->htotal - (mode->hsync_start - mode->hdisplay) - 1;

	vsync_period = mode->vtotal * mode->htotal;
	vsync_len = (mode->vsync_end - mode->vsync_start) * mode->htotal;
	display_v_start = (mode->vtotal - mode->vsync_start) * mode->htotal + lcdc_hsync_skew;
	display_v_end = vsync_period - ((mode->vsync_start - mode->vdisplay) * mode->htotal) + lcdc_hsync_skew - 1;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_HSYNC_CTRL,
			MDP4_LCDC_HSYNC_CTRL_PULSEW(mode->hsync_end - mode->hsync_start) |
			MDP4_LCDC_HSYNC_CTRL_PERIOD(mode->htotal));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_VSYNC_PERIOD, vsync_period);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_VSYNC_LEN, vsync_len);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_DISPLAY_HCTRL,
			MDP4_LCDC_DISPLAY_HCTRL_START(hsync_start_x) |
			MDP4_LCDC_DISPLAY_HCTRL_END(hsync_end_x));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_DISPLAY_VSTART, display_v_start);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_DISPLAY_VEND, display_v_end);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_BORDER_CLR, 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_UNDERFLOW_CLR,
			MDP4_LCDC_UNDERFLOW_CLR_ENABLE_RECOVERY |
			MDP4_LCDC_UNDERFLOW_CLR_COLOR(0xff));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_HSYNC_SKEW, lcdc_hsync_skew);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_CTRL_POLARITY, ctrl_pol);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_ACTIVE_HCTL,
			MDP4_LCDC_ACTIVE_HCTL_START(0) |
			MDP4_LCDC_ACTIVE_HCTL_END(0));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_ACTIVE_VSTART, 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_ACTIVE_VEND, 0);
पूर्ण

अटल व्योम mdp4_lcdc_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा mdp4_lcdc_encoder *mdp4_lcdc_encoder =
			to_mdp4_lcdc_encoder(encoder);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(encoder);
	काष्ठा drm_panel *panel;
	पूर्णांक i, ret;

	अगर (WARN_ON(!mdp4_lcdc_encoder->enabled))
		वापस;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_ENABLE, 0);

	panel = of_drm_find_panel(mdp4_lcdc_encoder->panel_node);
	अगर (!IS_ERR(panel)) अणु
		drm_panel_disable(panel);
		drm_panel_unprepare(panel);
	पूर्ण

	/*
	 * Wait क्रम a vsync so we know the ENABLE=0 latched beक्रमe
	 * the (connector) source of the vsync's माला_लो disabled,
	 * otherwise we end up in a funny state अगर we re-enable
	 * beक्रमe the disable latches, which results that some of
	 * the settings changes क्रम the new modeset (like new
	 * scanout buffer) करोn't latch properly..
	 */
	mdp_irq_रुको(&mdp4_kms->base, MDP4_IRQ_PRIMARY_VSYNC);

	clk_disable_unprepare(mdp4_lcdc_encoder->lcdc_clk);

	क्रम (i = 0; i < ARRAY_SIZE(mdp4_lcdc_encoder->regs); i++) अणु
		ret = regulator_disable(mdp4_lcdc_encoder->regs[i]);
		अगर (ret)
			DRM_DEV_ERROR(dev->dev, "failed to disable regulator: %d\n", ret);
	पूर्ण

	mdp4_lcdc_encoder->enabled = false;
पूर्ण

अटल व्योम mdp4_lcdc_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा mdp4_lcdc_encoder *mdp4_lcdc_encoder =
			to_mdp4_lcdc_encoder(encoder);
	अचिन्हित दीर्घ pc = mdp4_lcdc_encoder->pixघड़ी;
	काष्ठा mdp4_kms *mdp4_kms = get_kms(encoder);
	काष्ठा drm_panel *panel;
	uपूर्णांक32_t config;
	पूर्णांक i, ret;

	अगर (WARN_ON(mdp4_lcdc_encoder->enabled))
		वापस;

	/* TODO: hard-coded क्रम 18bpp: */
	config =
		MDP4_DMA_CONFIG_R_BPC(BPC6) |
		MDP4_DMA_CONFIG_G_BPC(BPC6) |
		MDP4_DMA_CONFIG_B_BPC(BPC6) |
		MDP4_DMA_CONFIG_PACK(0x21) |
		MDP4_DMA_CONFIG_DEFLKR_EN |
		MDP4_DMA_CONFIG_DITHER_EN;

	अगर (!of_property_पढ़ो_bool(dev->dev->of_node, "qcom,lcdc-align-lsb"))
		config |= MDP4_DMA_CONFIG_PACK_ALIGN_MSB;

	mdp4_crtc_set_config(encoder->crtc, config);
	mdp4_crtc_set_पूर्णांकf(encoder->crtc, INTF_LCDC_DTV, 0);

	क्रम (i = 0; i < ARRAY_SIZE(mdp4_lcdc_encoder->regs); i++) अणु
		ret = regulator_enable(mdp4_lcdc_encoder->regs[i]);
		अगर (ret)
			DRM_DEV_ERROR(dev->dev, "failed to enable regulator: %d\n", ret);
	पूर्ण

	DBG("setting lcdc_clk=%lu", pc);
	ret = clk_set_rate(mdp4_lcdc_encoder->lcdc_clk, pc);
	अगर (ret)
		DRM_DEV_ERROR(dev->dev, "failed to configure lcdc_clk: %d\n", ret);
	ret = clk_prepare_enable(mdp4_lcdc_encoder->lcdc_clk);
	अगर (ret)
		DRM_DEV_ERROR(dev->dev, "failed to enable lcdc_clk: %d\n", ret);

	panel = of_drm_find_panel(mdp4_lcdc_encoder->panel_node);
	अगर (!IS_ERR(panel)) अणु
		drm_panel_prepare(panel);
		drm_panel_enable(panel);
	पूर्ण

	setup_phy(encoder);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_ENABLE, 1);

	mdp4_lcdc_encoder->enabled = true;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs mdp4_lcdc_encoder_helper_funcs = अणु
	.mode_set = mdp4_lcdc_encoder_mode_set,
	.disable = mdp4_lcdc_encoder_disable,
	.enable = mdp4_lcdc_encoder_enable,
पूर्ण;

दीर्घ mdp4_lcdc_round_pixclk(काष्ठा drm_encoder *encoder, अचिन्हित दीर्घ rate)
अणु
	काष्ठा mdp4_lcdc_encoder *mdp4_lcdc_encoder =
			to_mdp4_lcdc_encoder(encoder);
	वापस clk_round_rate(mdp4_lcdc_encoder->lcdc_clk, rate);
पूर्ण

/* initialize encoder */
काष्ठा drm_encoder *mdp4_lcdc_encoder_init(काष्ठा drm_device *dev,
		काष्ठा device_node *panel_node)
अणु
	काष्ठा drm_encoder *encoder = शून्य;
	काष्ठा mdp4_lcdc_encoder *mdp4_lcdc_encoder;
	काष्ठा regulator *reg;
	पूर्णांक ret;

	mdp4_lcdc_encoder = kzalloc(माप(*mdp4_lcdc_encoder), GFP_KERNEL);
	अगर (!mdp4_lcdc_encoder) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	mdp4_lcdc_encoder->panel_node = panel_node;

	encoder = &mdp4_lcdc_encoder->base;

	drm_encoder_init(dev, encoder, &mdp4_lcdc_encoder_funcs,
			 DRM_MODE_ENCODER_LVDS, शून्य);
	drm_encoder_helper_add(encoder, &mdp4_lcdc_encoder_helper_funcs);

	/* TODO: करो we need dअगरferent pll in other हालs? */
	mdp4_lcdc_encoder->lcdc_clk = mpd4_lvds_pll_init(dev);
	अगर (IS_ERR(mdp4_lcdc_encoder->lcdc_clk)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to get lvds_clk\n");
		ret = PTR_ERR(mdp4_lcdc_encoder->lcdc_clk);
		जाओ fail;
	पूर्ण

	/* TODO: dअगरferent regulators in other हालs? */
	reg = devm_regulator_get(dev->dev, "lvds-vccs-3p3v");
	अगर (IS_ERR(reg)) अणु
		ret = PTR_ERR(reg);
		DRM_DEV_ERROR(dev->dev, "failed to get lvds-vccs-3p3v: %d\n", ret);
		जाओ fail;
	पूर्ण
	mdp4_lcdc_encoder->regs[0] = reg;

	reg = devm_regulator_get(dev->dev, "lvds-pll-vdda");
	अगर (IS_ERR(reg)) अणु
		ret = PTR_ERR(reg);
		DRM_DEV_ERROR(dev->dev, "failed to get lvds-pll-vdda: %d\n", ret);
		जाओ fail;
	पूर्ण
	mdp4_lcdc_encoder->regs[1] = reg;

	reg = devm_regulator_get(dev->dev, "lvds-vdda");
	अगर (IS_ERR(reg)) अणु
		ret = PTR_ERR(reg);
		DRM_DEV_ERROR(dev->dev, "failed to get lvds-vdda: %d\n", ret);
		जाओ fail;
	पूर्ण
	mdp4_lcdc_encoder->regs[2] = reg;

	वापस encoder;

fail:
	अगर (encoder)
		mdp4_lcdc_encoder_destroy(encoder);

	वापस ERR_PTR(ret);
पूर्ण
