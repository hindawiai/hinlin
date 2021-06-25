<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Free Electrons
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
#समावेश "sun4i_lvds.h"

काष्ठा sun4i_lvds अणु
	काष्ठा drm_connector	connector;
	काष्ठा drm_encoder	encoder;

	काष्ठा drm_panel	*panel;
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_lvds *
drm_connector_to_sun4i_lvds(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा sun4i_lvds,
			    connector);
पूर्ण

अटल अंतरभूत काष्ठा sun4i_lvds *
drm_encoder_to_sun4i_lvds(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा sun4i_lvds,
			    encoder);
पूर्ण

अटल पूर्णांक sun4i_lvds_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा sun4i_lvds *lvds =
		drm_connector_to_sun4i_lvds(connector);

	वापस drm_panel_get_modes(lvds->panel, connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs sun4i_lvds_con_helper_funcs = अणु
	.get_modes	= sun4i_lvds_get_modes,
पूर्ण;

अटल व्योम
sun4i_lvds_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sun4i_lvds_con_funcs = अणु
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= sun4i_lvds_connector_destroy,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल व्योम sun4i_lvds_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_lvds *lvds = drm_encoder_to_sun4i_lvds(encoder);

	DRM_DEBUG_DRIVER("Enabling LVDS output\n");

	अगर (lvds->panel) अणु
		drm_panel_prepare(lvds->panel);
		drm_panel_enable(lvds->panel);
	पूर्ण
पूर्ण

अटल व्योम sun4i_lvds_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_lvds *lvds = drm_encoder_to_sun4i_lvds(encoder);

	DRM_DEBUG_DRIVER("Disabling LVDS output\n");

	अगर (lvds->panel) अणु
		drm_panel_disable(lvds->panel);
		drm_panel_unprepare(lvds->panel);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs sun4i_lvds_enc_helper_funcs = अणु
	.disable	= sun4i_lvds_encoder_disable,
	.enable		= sun4i_lvds_encoder_enable,
पूर्ण;

पूर्णांक sun4i_lvds_init(काष्ठा drm_device *drm, काष्ठा sun4i_tcon *tcon)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *bridge;
	काष्ठा sun4i_lvds *lvds;
	पूर्णांक ret;

	lvds = devm_kzalloc(drm->dev, माप(*lvds), GFP_KERNEL);
	अगर (!lvds)
		वापस -ENOMEM;
	encoder = &lvds->encoder;

	ret = drm_of_find_panel_or_bridge(tcon->dev->of_node, 1, 0,
					  &lvds->panel, &bridge);
	अगर (ret) अणु
		dev_info(drm->dev, "No panel or bridge found... LVDS output disabled\n");
		वापस 0;
	पूर्ण

	drm_encoder_helper_add(&lvds->encoder,
			       &sun4i_lvds_enc_helper_funcs);
	ret = drm_simple_encoder_init(drm, &lvds->encoder,
				      DRM_MODE_ENCODER_LVDS);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't initialise the lvds encoder\n");
		जाओ err_out;
	पूर्ण

	/* The LVDS encoder can only work with the TCON channel 0 */
	lvds->encoder.possible_crtcs = drm_crtc_mask(&tcon->crtc->crtc);

	अगर (lvds->panel) अणु
		drm_connector_helper_add(&lvds->connector,
					 &sun4i_lvds_con_helper_funcs);
		ret = drm_connector_init(drm, &lvds->connector,
					 &sun4i_lvds_con_funcs,
					 DRM_MODE_CONNECTOR_LVDS);
		अगर (ret) अणु
			dev_err(drm->dev, "Couldn't initialise the lvds connector\n");
			जाओ err_cleanup_connector;
		पूर्ण

		drm_connector_attach_encoder(&lvds->connector,
						  &lvds->encoder);
	पूर्ण

	अगर (bridge) अणु
		ret = drm_bridge_attach(encoder, bridge, शून्य, 0);
		अगर (ret) अणु
			dev_err(drm->dev, "Couldn't attach our bridge\n");
			जाओ err_cleanup_connector;
		पूर्ण
	पूर्ण

	वापस 0;

err_cleanup_connector:
	drm_encoder_cleanup(&lvds->encoder);
err_out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sun4i_lvds_init);
