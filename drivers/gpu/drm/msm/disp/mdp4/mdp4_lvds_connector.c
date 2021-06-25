<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 * Author: Vinay Simha <vinaysimha@inक्रमcecomputing.com>
 */

#समावेश "mdp4_kms.h"

काष्ठा mdp4_lvds_connector अणु
	काष्ठा drm_connector base;
	काष्ठा drm_encoder *encoder;
	काष्ठा device_node *panel_node;
	काष्ठा drm_panel *panel;
पूर्ण;
#घोषणा to_mdp4_lvds_connector(x) container_of(x, काष्ठा mdp4_lvds_connector, base)

अटल क्रमागत drm_connector_status mdp4_lvds_connector_detect(
		काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा mdp4_lvds_connector *mdp4_lvds_connector =
			to_mdp4_lvds_connector(connector);

	अगर (!mdp4_lvds_connector->panel) अणु
		mdp4_lvds_connector->panel =
			of_drm_find_panel(mdp4_lvds_connector->panel_node);
		अगर (IS_ERR(mdp4_lvds_connector->panel))
			mdp4_lvds_connector->panel = शून्य;
	पूर्ण

	वापस mdp4_lvds_connector->panel ?
			connector_status_connected :
			connector_status_disconnected;
पूर्ण

अटल व्योम mdp4_lvds_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा mdp4_lvds_connector *mdp4_lvds_connector =
			to_mdp4_lvds_connector(connector);

	drm_connector_cleanup(connector);

	kमुक्त(mdp4_lvds_connector);
पूर्ण

अटल पूर्णांक mdp4_lvds_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा mdp4_lvds_connector *mdp4_lvds_connector =
			to_mdp4_lvds_connector(connector);
	काष्ठा drm_panel *panel = mdp4_lvds_connector->panel;
	पूर्णांक ret = 0;

	अगर (panel)
		ret = drm_panel_get_modes(panel, connector);

	वापस ret;
पूर्ण

अटल पूर्णांक mdp4_lvds_connector_mode_valid(काष्ठा drm_connector *connector,
				 काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mdp4_lvds_connector *mdp4_lvds_connector =
			to_mdp4_lvds_connector(connector);
	काष्ठा drm_encoder *encoder = mdp4_lvds_connector->encoder;
	दीर्घ actual, requested;

	requested = 1000 * mode->घड़ी;
	actual = mdp4_lcdc_round_pixclk(encoder, requested);

	DBG("requested=%ld, actual=%ld", requested, actual);

	अगर (actual != requested)
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs mdp4_lvds_connector_funcs = अणु
	.detect = mdp4_lvds_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = mdp4_lvds_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs mdp4_lvds_connector_helper_funcs = अणु
	.get_modes = mdp4_lvds_connector_get_modes,
	.mode_valid = mdp4_lvds_connector_mode_valid,
पूर्ण;

/* initialize connector */
काष्ठा drm_connector *mdp4_lvds_connector_init(काष्ठा drm_device *dev,
		काष्ठा device_node *panel_node, काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा mdp4_lvds_connector *mdp4_lvds_connector;

	mdp4_lvds_connector = kzalloc(माप(*mdp4_lvds_connector), GFP_KERNEL);
	अगर (!mdp4_lvds_connector)
		वापस ERR_PTR(-ENOMEM);

	mdp4_lvds_connector->encoder = encoder;
	mdp4_lvds_connector->panel_node = panel_node;

	connector = &mdp4_lvds_connector->base;

	drm_connector_init(dev, connector, &mdp4_lvds_connector_funcs,
			DRM_MODE_CONNECTOR_LVDS);
	drm_connector_helper_add(connector, &mdp4_lvds_connector_helper_funcs);

	connector->polled = 0;

	connector->पूर्णांकerlace_allowed = 0;
	connector->द्विगुनscan_allowed = 0;

	drm_connector_attach_encoder(connector, encoder);

	वापस connector;
पूर्ण
