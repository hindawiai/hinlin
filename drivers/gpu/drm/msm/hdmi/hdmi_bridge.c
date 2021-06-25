<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/delay.h>

#समावेश "hdmi.h"

काष्ठा hdmi_bridge अणु
	काष्ठा drm_bridge base;
	काष्ठा hdmi *hdmi;
पूर्ण;
#घोषणा to_hdmi_bridge(x) container_of(x, काष्ठा hdmi_bridge, base)

व्योम msm_hdmi_bridge_destroy(काष्ठा drm_bridge *bridge)
अणु
पूर्ण

अटल व्योम msm_hdmi_घातer_on(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_device *dev = bridge->dev;
	काष्ठा hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	काष्ठा hdmi *hdmi = hdmi_bridge->hdmi;
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	पूर्णांक i, ret;

	pm_runसमय_get_sync(&hdmi->pdev->dev);

	क्रम (i = 0; i < config->pwr_reg_cnt; i++) अणु
		ret = regulator_enable(hdmi->pwr_regs[i]);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to enable pwr regulator: %s (%d)\n",
					config->pwr_reg_names[i], ret);
		पूर्ण
	पूर्ण

	अगर (config->pwr_clk_cnt > 0) अणु
		DBG("pixclock: %lu", hdmi->pixघड़ी);
		ret = clk_set_rate(hdmi->pwr_clks[0], hdmi->pixघड़ी);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to set pixel clk: %s (%d)\n",
					config->pwr_clk_names[0], ret);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < config->pwr_clk_cnt; i++) अणु
		ret = clk_prepare_enable(hdmi->pwr_clks[i]);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to enable pwr clk: %s (%d)\n",
					config->pwr_clk_names[i], ret);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम घातer_off(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_device *dev = bridge->dev;
	काष्ठा hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	काष्ठा hdmi *hdmi = hdmi_bridge->hdmi;
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	पूर्णांक i, ret;

	/* TODO करो we need to रुको क्रम final vblank somewhere beक्रमe
	 * cutting the घड़ीs?
	 */
	mdelay(16 + 4);

	क्रम (i = 0; i < config->pwr_clk_cnt; i++)
		clk_disable_unprepare(hdmi->pwr_clks[i]);

	क्रम (i = 0; i < config->pwr_reg_cnt; i++) अणु
		ret = regulator_disable(hdmi->pwr_regs[i]);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to disable pwr regulator: %s (%d)\n",
					config->pwr_reg_names[i], ret);
		पूर्ण
	पूर्ण

	pm_runसमय_put_स्वतःsuspend(&hdmi->pdev->dev);
पूर्ण

#घोषणा AVI_IFRAME_LINE_NUMBER 1

अटल व्योम msm_hdmi_config_avi_infoframe(काष्ठा hdmi *hdmi)
अणु
	काष्ठा drm_crtc *crtc = hdmi->encoder->crtc;
	स्थिर काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	जोड़ hdmi_infoframe frame;
	u8 buffer[HDMI_INFOFRAME_SIZE(AVI)];
	u32 val;
	पूर्णांक len;

	drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						 hdmi->connector, mode);

	len = hdmi_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (len < 0) अणु
		DRM_DEV_ERROR(&hdmi->pdev->dev,
			"failed to configure avi infoframe\n");
		वापस;
	पूर्ण

	/*
	 * the AVI_INFOx रेजिस्टरs करोn't map exactly to how the AVI infoframes
	 * are packed according to the spec. The checksum from the header is
	 * written to the LSB byte of AVI_INFO0 and the version is written to
	 * the third byte from the LSB of AVI_INFO3
	 */
	hdmi_ग_लिखो(hdmi, REG_HDMI_AVI_INFO(0),
		   buffer[3] |
		   buffer[4] << 8 |
		   buffer[5] << 16 |
		   buffer[6] << 24);

	hdmi_ग_लिखो(hdmi, REG_HDMI_AVI_INFO(1),
		   buffer[7] |
		   buffer[8] << 8 |
		   buffer[9] << 16 |
		   buffer[10] << 24);

	hdmi_ग_लिखो(hdmi, REG_HDMI_AVI_INFO(2),
		   buffer[11] |
		   buffer[12] << 8 |
		   buffer[13] << 16 |
		   buffer[14] << 24);

	hdmi_ग_लिखो(hdmi, REG_HDMI_AVI_INFO(3),
		   buffer[15] |
		   buffer[16] << 8 |
		   buffer[1] << 24);

	hdmi_ग_लिखो(hdmi, REG_HDMI_INFOFRAME_CTRL0,
		   HDMI_INFOFRAME_CTRL0_AVI_SEND |
		   HDMI_INFOFRAME_CTRL0_AVI_CONT);

	val = hdmi_पढ़ो(hdmi, REG_HDMI_INFOFRAME_CTRL1);
	val &= ~HDMI_INFOFRAME_CTRL1_AVI_INFO_LINE__MASK;
	val |= HDMI_INFOFRAME_CTRL1_AVI_INFO_LINE(AVI_IFRAME_LINE_NUMBER);
	hdmi_ग_लिखो(hdmi, REG_HDMI_INFOFRAME_CTRL1, val);
पूर्ण

अटल व्योम msm_hdmi_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	काष्ठा hdmi *hdmi = hdmi_bridge->hdmi;
	काष्ठा hdmi_phy *phy = hdmi->phy;

	DBG("power up");

	अगर (!hdmi->घातer_on) अणु
		msm_hdmi_phy_resource_enable(phy);
		msm_hdmi_घातer_on(bridge);
		hdmi->घातer_on = true;
		अगर (hdmi->hdmi_mode) अणु
			msm_hdmi_config_avi_infoframe(hdmi);
			msm_hdmi_audio_update(hdmi);
		पूर्ण
	पूर्ण

	msm_hdmi_phy_घातerup(phy, hdmi->pixघड़ी);

	msm_hdmi_set_mode(hdmi, true);

	अगर (hdmi->hdcp_ctrl)
		msm_hdmi_hdcp_on(hdmi->hdcp_ctrl);
पूर्ण

अटल व्योम msm_hdmi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
पूर्ण

अटल व्योम msm_hdmi_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
पूर्ण

अटल व्योम msm_hdmi_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	काष्ठा hdmi *hdmi = hdmi_bridge->hdmi;
	काष्ठा hdmi_phy *phy = hdmi->phy;

	अगर (hdmi->hdcp_ctrl)
		msm_hdmi_hdcp_off(hdmi->hdcp_ctrl);

	DBG("power down");
	msm_hdmi_set_mode(hdmi, false);

	msm_hdmi_phy_घातerकरोwn(phy);

	अगर (hdmi->घातer_on) अणु
		घातer_off(bridge);
		hdmi->घातer_on = false;
		अगर (hdmi->hdmi_mode)
			msm_hdmi_audio_update(hdmi);
		msm_hdmi_phy_resource_disable(phy);
	पूर्ण
पूर्ण

अटल व्योम msm_hdmi_bridge_mode_set(काष्ठा drm_bridge *bridge,
		 स्थिर काष्ठा drm_display_mode *mode,
		 स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	काष्ठा hdmi *hdmi = hdmi_bridge->hdmi;
	पूर्णांक hstart, hend, vstart, vend;
	uपूर्णांक32_t frame_ctrl;

	mode = adjusted_mode;

	hdmi->pixघड़ी = mode->घड़ी * 1000;

	hstart = mode->htotal - mode->hsync_start;
	hend   = mode->htotal - mode->hsync_start + mode->hdisplay;

	vstart = mode->vtotal - mode->vsync_start - 1;
	vend   = mode->vtotal - mode->vsync_start + mode->vdisplay - 1;

	DBG("htotal=%d, vtotal=%d, hstart=%d, hend=%d, vstart=%d, vend=%d",
			mode->htotal, mode->vtotal, hstart, hend, vstart, vend);

	hdmi_ग_लिखो(hdmi, REG_HDMI_TOTAL,
			HDMI_TOTAL_H_TOTAL(mode->htotal - 1) |
			HDMI_TOTAL_V_TOTAL(mode->vtotal - 1));

	hdmi_ग_लिखो(hdmi, REG_HDMI_ACTIVE_HSYNC,
			HDMI_ACTIVE_HSYNC_START(hstart) |
			HDMI_ACTIVE_HSYNC_END(hend));
	hdmi_ग_लिखो(hdmi, REG_HDMI_ACTIVE_VSYNC,
			HDMI_ACTIVE_VSYNC_START(vstart) |
			HDMI_ACTIVE_VSYNC_END(vend));

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		hdmi_ग_लिखो(hdmi, REG_HDMI_VSYNC_TOTAL_F2,
				HDMI_VSYNC_TOTAL_F2_V_TOTAL(mode->vtotal));
		hdmi_ग_लिखो(hdmi, REG_HDMI_VSYNC_ACTIVE_F2,
				HDMI_VSYNC_ACTIVE_F2_START(vstart + 1) |
				HDMI_VSYNC_ACTIVE_F2_END(vend + 1));
	पूर्ण अन्यथा अणु
		hdmi_ग_लिखो(hdmi, REG_HDMI_VSYNC_TOTAL_F2,
				HDMI_VSYNC_TOTAL_F2_V_TOTAL(0));
		hdmi_ग_लिखो(hdmi, REG_HDMI_VSYNC_ACTIVE_F2,
				HDMI_VSYNC_ACTIVE_F2_START(0) |
				HDMI_VSYNC_ACTIVE_F2_END(0));
	पूर्ण

	frame_ctrl = 0;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		frame_ctrl |= HDMI_FRAME_CTRL_HSYNC_LOW;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		frame_ctrl |= HDMI_FRAME_CTRL_VSYNC_LOW;
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		frame_ctrl |= HDMI_FRAME_CTRL_INTERLACED_EN;
	DBG("frame_ctrl=%08x", frame_ctrl);
	hdmi_ग_लिखो(hdmi, REG_HDMI_FRAME_CTRL, frame_ctrl);

	अगर (hdmi->hdmi_mode)
		msm_hdmi_audio_update(hdmi);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs msm_hdmi_bridge_funcs = अणु
		.pre_enable = msm_hdmi_bridge_pre_enable,
		.enable = msm_hdmi_bridge_enable,
		.disable = msm_hdmi_bridge_disable,
		.post_disable = msm_hdmi_bridge_post_disable,
		.mode_set = msm_hdmi_bridge_mode_set,
पूर्ण;


/* initialize bridge */
काष्ठा drm_bridge *msm_hdmi_bridge_init(काष्ठा hdmi *hdmi)
अणु
	काष्ठा drm_bridge *bridge = शून्य;
	काष्ठा hdmi_bridge *hdmi_bridge;
	पूर्णांक ret;

	hdmi_bridge = devm_kzalloc(hdmi->dev->dev,
			माप(*hdmi_bridge), GFP_KERNEL);
	अगर (!hdmi_bridge) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	hdmi_bridge->hdmi = hdmi;

	bridge = &hdmi_bridge->base;
	bridge->funcs = &msm_hdmi_bridge_funcs;

	ret = drm_bridge_attach(hdmi->encoder, bridge, शून्य, 0);
	अगर (ret)
		जाओ fail;

	वापस bridge;

fail:
	अगर (bridge)
		msm_hdmi_bridge_destroy(bridge);

	वापस ERR_PTR(ret);
पूर्ण
