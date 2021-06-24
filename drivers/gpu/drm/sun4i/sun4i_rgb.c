<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "sun4i_crtc.h"
#समावेश "sun4i_tcon.h"
#समावेश "sun4i_rgb.h"

काष्ठा sun4i_rgb अणु
	काष्ठा drm_connector	connector;
	काष्ठा drm_encoder	encoder;

	काष्ठा sun4i_tcon	*tcon;
	काष्ठा drm_panel	*panel;
	काष्ठा drm_bridge	*bridge;
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_rgb *
drm_connector_to_sun4i_rgb(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा sun4i_rgb,
			    connector);
पूर्ण

अटल अंतरभूत काष्ठा sun4i_rgb *
drm_encoder_to_sun4i_rgb(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा sun4i_rgb,
			    encoder);
पूर्ण

अटल पूर्णांक sun4i_rgb_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा sun4i_rgb *rgb =
		drm_connector_to_sun4i_rgb(connector);

	वापस drm_panel_get_modes(rgb->panel, connector);
पूर्ण

/*
 * VESA DMT defines a tolerance of 0.5% on the pixel घड़ी, जबतक the
 * CVT spec reuses that tolerance in its examples, so it looks to be a
 * good शेष tolerance क्रम the EDID-based modes. Define it to 5 per
 * mille to aव्योम भग्नing poपूर्णांक operations.
 */
#घोषणा SUN4I_RGB_DOTCLOCK_TOLERANCE_PER_MILLE	5

अटल क्रमागत drm_mode_status sun4i_rgb_mode_valid(काष्ठा drm_encoder *crtc,
						 स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा sun4i_rgb *rgb = drm_encoder_to_sun4i_rgb(crtc);
	काष्ठा sun4i_tcon *tcon = rgb->tcon;
	u32 hsync = mode->hsync_end - mode->hsync_start;
	u32 vsync = mode->vsync_end - mode->vsync_start;
	अचिन्हित दीर्घ दीर्घ rate = mode->घड़ी * 1000;
	अचिन्हित दीर्घ दीर्घ lowest, highest;
	अचिन्हित दीर्घ दीर्घ rounded_rate;

	DRM_DEBUG_DRIVER("Validating modes...\n");

	अगर (hsync < 1)
		वापस MODE_HSYNC_NARROW;

	अगर (hsync > 0x3ff)
		वापस MODE_HSYNC_WIDE;

	अगर ((mode->hdisplay < 1) || (mode->htotal < 1))
		वापस MODE_H_ILLEGAL;

	अगर ((mode->hdisplay > 0x7ff) || (mode->htotal > 0xfff))
		वापस MODE_BAD_HVALUE;

	DRM_DEBUG_DRIVER("Horizontal parameters OK\n");

	अगर (vsync < 1)
		वापस MODE_VSYNC_NARROW;

	अगर (vsync > 0x3ff)
		वापस MODE_VSYNC_WIDE;

	अगर ((mode->vdisplay < 1) || (mode->vtotal < 1))
		वापस MODE_V_ILLEGAL;

	अगर ((mode->vdisplay > 0x7ff) || (mode->vtotal > 0xfff))
		वापस MODE_BAD_VVALUE;

	DRM_DEBUG_DRIVER("Vertical parameters OK\n");

	/*
	 * TODO: We should use the काष्ठा display_timing अगर available
	 * and / or trying to stretch the timings within that
	 * tolerancy to take care of panels that we wouldn't be able
	 * to have a exact match क्रम.
	 */
	अगर (rgb->panel) अणु
		DRM_DEBUG_DRIVER("RGB panel used, skipping clock rate checks");
		जाओ out;
	पूर्ण

	/*
	 * That shouldn't ever happen unless something is really wrong, but it
	 * करोesn't harm to check.
	 */
	अगर (!rgb->bridge)
		जाओ out;

	tcon->dclk_min_भाग = 6;
	tcon->dclk_max_भाग = 127;
	rounded_rate = clk_round_rate(tcon->dclk, rate);

	lowest = rate * (1000 - SUN4I_RGB_DOTCLOCK_TOLERANCE_PER_MILLE);
	करो_भाग(lowest, 1000);
	अगर (rounded_rate < lowest)
		वापस MODE_CLOCK_LOW;

	highest = rate * (1000 + SUN4I_RGB_DOTCLOCK_TOLERANCE_PER_MILLE);
	करो_भाग(highest, 1000);
	अगर (rounded_rate > highest)
		वापस MODE_CLOCK_HIGH;

out:
	DRM_DEBUG_DRIVER("Clock rate OK\n");

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs sun4i_rgb_con_helper_funcs = अणु
	.get_modes	= sun4i_rgb_get_modes,
पूर्ण;

अटल व्योम
sun4i_rgb_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sun4i_rgb_con_funcs = अणु
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= sun4i_rgb_connector_destroy,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल व्योम sun4i_rgb_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_rgb *rgb = drm_encoder_to_sun4i_rgb(encoder);

	DRM_DEBUG_DRIVER("Enabling RGB output\n");

	अगर (rgb->panel) अणु
		drm_panel_prepare(rgb->panel);
		drm_panel_enable(rgb->panel);
	पूर्ण
पूर्ण

अटल व्योम sun4i_rgb_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_rgb *rgb = drm_encoder_to_sun4i_rgb(encoder);

	DRM_DEBUG_DRIVER("Disabling RGB output\n");

	अगर (rgb->panel) अणु
		drm_panel_disable(rgb->panel);
		drm_panel_unprepare(rgb->panel);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs sun4i_rgb_enc_helper_funcs = अणु
	.disable	= sun4i_rgb_encoder_disable,
	.enable		= sun4i_rgb_encoder_enable,
	.mode_valid	= sun4i_rgb_mode_valid,
पूर्ण;

पूर्णांक sun4i_rgb_init(काष्ठा drm_device *drm, काष्ठा sun4i_tcon *tcon)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा sun4i_rgb *rgb;
	पूर्णांक ret;

	rgb = devm_kzalloc(drm->dev, माप(*rgb), GFP_KERNEL);
	अगर (!rgb)
		वापस -ENOMEM;
	rgb->tcon = tcon;
	encoder = &rgb->encoder;

	ret = drm_of_find_panel_or_bridge(tcon->dev->of_node, 1, 0,
					  &rgb->panel, &rgb->bridge);
	अगर (ret) अणु
		dev_info(drm->dev, "No panel or bridge found... RGB output disabled\n");
		वापस 0;
	पूर्ण

	drm_encoder_helper_add(&rgb->encoder,
			       &sun4i_rgb_enc_helper_funcs);
	ret = drm_simple_encoder_init(drm, &rgb->encoder,
				      DRM_MODE_ENCODER_NONE);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't initialise the rgb encoder\n");
		जाओ err_out;
	पूर्ण

	/* The RGB encoder can only work with the TCON channel 0 */
	rgb->encoder.possible_crtcs = drm_crtc_mask(&tcon->crtc->crtc);

	अगर (rgb->panel) अणु
		drm_connector_helper_add(&rgb->connector,
					 &sun4i_rgb_con_helper_funcs);
		ret = drm_connector_init(drm, &rgb->connector,
					 &sun4i_rgb_con_funcs,
					 DRM_MODE_CONNECTOR_Unknown);
		अगर (ret) अणु
			dev_err(drm->dev, "Couldn't initialise the rgb connector\n");
			जाओ err_cleanup_connector;
		पूर्ण

		drm_connector_attach_encoder(&rgb->connector,
						  &rgb->encoder);
	पूर्ण

	अगर (rgb->bridge) अणु
		ret = drm_bridge_attach(encoder, rgb->bridge, शून्य, 0);
		अगर (ret) अणु
			dev_err(drm->dev, "Couldn't attach our bridge\n");
			जाओ err_cleanup_connector;
		पूर्ण
	पूर्ण

	वापस 0;

err_cleanup_connector:
	drm_encoder_cleanup(&rgb->encoder);
err_out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sun4i_rgb_init);
