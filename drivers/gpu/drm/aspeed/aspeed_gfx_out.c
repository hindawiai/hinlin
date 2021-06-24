<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2018 IBM Corporation

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "aspeed_gfx.h"

अटल पूर्णांक aspeed_gfx_get_modes(काष्ठा drm_connector *connector)
अणु
	वापस drm_add_modes_noedid(connector, 800, 600);
पूर्ण

अटल स्थिर काष्ठा
drm_connector_helper_funcs aspeed_gfx_connector_helper_funcs = अणु
	.get_modes = aspeed_gfx_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs aspeed_gfx_connector_funcs = अणु
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= drm_connector_cleanup,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

पूर्णांक aspeed_gfx_create_output(काष्ठा drm_device *drm)
अणु
	काष्ठा aspeed_gfx *priv = to_aspeed_gfx(drm);
	पूर्णांक ret;

	priv->connector.dpms = DRM_MODE_DPMS_OFF;
	priv->connector.polled = 0;
	drm_connector_helper_add(&priv->connector,
				 &aspeed_gfx_connector_helper_funcs);
	ret = drm_connector_init(drm, &priv->connector,
				 &aspeed_gfx_connector_funcs,
				 DRM_MODE_CONNECTOR_Unknown);
	वापस ret;
पूर्ण
