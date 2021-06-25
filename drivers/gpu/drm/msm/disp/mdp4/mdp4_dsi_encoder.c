<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 * Copyright (c) 2014, Inक्रमce Computing. All rights reserved.
 *
 * Author: Vinay Simha <vinaysimha@inक्रमcecomputing.com>
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "mdp4_kms.h"

काष्ठा mdp4_dsi_encoder अणु
	काष्ठा drm_encoder base;
	काष्ठा drm_panel *panel;
	bool enabled;
पूर्ण;
#घोषणा to_mdp4_dsi_encoder(x) container_of(x, काष्ठा mdp4_dsi_encoder, base)

अटल काष्ठा mdp4_kms *get_kms(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा msm_drm_निजी *priv = encoder->dev->dev_निजी;
	वापस to_mdp4_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल व्योम mdp4_dsi_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp4_dsi_encoder *mdp4_dsi_encoder = to_mdp4_dsi_encoder(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(mdp4_dsi_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs mdp4_dsi_encoder_funcs = अणु
	.destroy = mdp4_dsi_encoder_destroy,
पूर्ण;

अटल व्योम mdp4_dsi_encoder_mode_set(काष्ठा drm_encoder *encoder,
				      काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा mdp4_kms *mdp4_kms = get_kms(encoder);
	uपूर्णांक32_t dsi_hsync_skew, vsync_period, vsync_len, ctrl_pol;
	uपूर्णांक32_t display_v_start, display_v_end;
	uपूर्णांक32_t hsync_start_x, hsync_end_x;

	mode = adjusted_mode;

	DBG("set mode: " DRM_MODE_FMT, DRM_MODE_ARG(mode));

	ctrl_pol = 0;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		ctrl_pol |= MDP4_DSI_CTRL_POLARITY_HSYNC_LOW;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		ctrl_pol |= MDP4_DSI_CTRL_POLARITY_VSYNC_LOW;
	/* probably need to get DATA_EN polarity from panel.. */

	dsi_hsync_skew = 0;  /* get this from panel? */

	hsync_start_x = (mode->htotal - mode->hsync_start);
	hsync_end_x = mode->htotal - (mode->hsync_start - mode->hdisplay) - 1;

	vsync_period = mode->vtotal * mode->htotal;
	vsync_len = (mode->vsync_end - mode->vsync_start) * mode->htotal;
	display_v_start = (mode->vtotal - mode->vsync_start) * mode->htotal + dsi_hsync_skew;
	display_v_end = vsync_period - ((mode->vsync_start - mode->vdisplay) * mode->htotal) + dsi_hsync_skew - 1;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_HSYNC_CTRL,
			MDP4_DSI_HSYNC_CTRL_PULSEW(mode->hsync_end - mode->hsync_start) |
			MDP4_DSI_HSYNC_CTRL_PERIOD(mode->htotal));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_VSYNC_PERIOD, vsync_period);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_VSYNC_LEN, vsync_len);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_DISPLAY_HCTRL,
			MDP4_DSI_DISPLAY_HCTRL_START(hsync_start_x) |
			MDP4_DSI_DISPLAY_HCTRL_END(hsync_end_x));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_DISPLAY_VSTART, display_v_start);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_DISPLAY_VEND, display_v_end);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_CTRL_POLARITY, ctrl_pol);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_UNDERFLOW_CLR,
			MDP4_DSI_UNDERFLOW_CLR_ENABLE_RECOVERY |
			MDP4_DSI_UNDERFLOW_CLR_COLOR(0xff));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_ACTIVE_HCTL,
			MDP4_DSI_ACTIVE_HCTL_START(0) |
			MDP4_DSI_ACTIVE_HCTL_END(0));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_HSYNC_SKEW, dsi_hsync_skew);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_BORDER_CLR, 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_ACTIVE_VSTART, 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_ACTIVE_VEND, 0);
पूर्ण

अटल व्योम mdp4_dsi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp4_dsi_encoder *mdp4_dsi_encoder = to_mdp4_dsi_encoder(encoder);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(encoder);

	अगर (!mdp4_dsi_encoder->enabled)
		वापस;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_ENABLE, 0);

	/*
	 * Wait क्रम a vsync so we know the ENABLE=0 latched beक्रमe
	 * the (connector) source of the vsync's माला_लो disabled,
	 * otherwise we end up in a funny state अगर we re-enable
	 * beक्रमe the disable latches, which results that some of
	 * the settings changes क्रम the new modeset (like new
	 * scanout buffer) करोn't latch properly..
	 */
	mdp_irq_रुको(&mdp4_kms->base, MDP4_IRQ_PRIMARY_VSYNC);

	mdp4_dsi_encoder->enabled = false;
पूर्ण

अटल व्योम mdp4_dsi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp4_dsi_encoder *mdp4_dsi_encoder = to_mdp4_dsi_encoder(encoder);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(encoder);

	अगर (mdp4_dsi_encoder->enabled)
		वापस;

	mdp4_crtc_set_config(encoder->crtc,
			MDP4_DMA_CONFIG_PACK_ALIGN_MSB |
			MDP4_DMA_CONFIG_DEFLKR_EN |
			MDP4_DMA_CONFIG_DITHER_EN |
			MDP4_DMA_CONFIG_R_BPC(BPC8) |
			MDP4_DMA_CONFIG_G_BPC(BPC8) |
			MDP4_DMA_CONFIG_B_BPC(BPC8) |
			MDP4_DMA_CONFIG_PACK(0x21));

	mdp4_crtc_set_पूर्णांकf(encoder->crtc, INTF_DSI_VIDEO, 0);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_ENABLE, 1);

	mdp4_dsi_encoder->enabled = true;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs mdp4_dsi_encoder_helper_funcs = अणु
	.mode_set = mdp4_dsi_encoder_mode_set,
	.disable = mdp4_dsi_encoder_disable,
	.enable = mdp4_dsi_encoder_enable,
पूर्ण;

/* initialize encoder */
काष्ठा drm_encoder *mdp4_dsi_encoder_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder = शून्य;
	काष्ठा mdp4_dsi_encoder *mdp4_dsi_encoder;
	पूर्णांक ret;

	mdp4_dsi_encoder = kzalloc(माप(*mdp4_dsi_encoder), GFP_KERNEL);
	अगर (!mdp4_dsi_encoder) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	encoder = &mdp4_dsi_encoder->base;

	drm_encoder_init(dev, encoder, &mdp4_dsi_encoder_funcs,
			 DRM_MODE_ENCODER_DSI, शून्य);
	drm_encoder_helper_add(encoder, &mdp4_dsi_encoder_helper_funcs);

	वापस encoder;

fail:
	अगर (encoder)
		mdp4_dsi_encoder_destroy(encoder);

	वापस ERR_PTR(ret);
पूर्ण
