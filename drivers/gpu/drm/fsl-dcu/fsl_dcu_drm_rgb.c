<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * Freescale DCU drm device driver
 */

#समावेश <linux/backlight.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "fsl_dcu_drm_drv.h"
#समावेश "fsl_tcon.h"

पूर्णांक fsl_dcu_drm_encoder_create(काष्ठा fsl_dcu_drm_device *fsl_dev,
			       काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder = &fsl_dev->encoder;
	पूर्णांक ret;

	encoder->possible_crtcs = 1;

	/* Use bypass mode क्रम parallel RGB/LVDS encoder */
	अगर (fsl_dev->tcon)
		fsl_tcon_bypass_enable(fsl_dev->tcon);

	ret = drm_simple_encoder_init(fsl_dev->drm, encoder,
				      DRM_MODE_ENCODER_LVDS);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम fsl_dcu_drm_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs fsl_dcu_drm_connector_funcs = अणु
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.destroy = fsl_dcu_drm_connector_destroy,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.reset = drm_atomic_helper_connector_reset,
पूर्ण;

अटल पूर्णांक fsl_dcu_drm_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा fsl_dcu_drm_connector *fsl_connector;

	fsl_connector = to_fsl_dcu_connector(connector);
	वापस drm_panel_get_modes(fsl_connector->panel, connector);
पूर्ण

अटल पूर्णांक fsl_dcu_drm_connector_mode_valid(काष्ठा drm_connector *connector,
					    काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->hdisplay & 0xf)
		वापस MODE_ERROR;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs connector_helper_funcs = अणु
	.get_modes = fsl_dcu_drm_connector_get_modes,
	.mode_valid = fsl_dcu_drm_connector_mode_valid,
पूर्ण;

अटल पूर्णांक fsl_dcu_attach_panel(काष्ठा fsl_dcu_drm_device *fsl_dev,
				 काष्ठा drm_panel *panel)
अणु
	काष्ठा drm_encoder *encoder = &fsl_dev->encoder;
	काष्ठा drm_connector *connector = &fsl_dev->connector.base;
	पूर्णांक ret;

	fsl_dev->connector.encoder = encoder;

	ret = drm_connector_init(fsl_dev->drm, connector,
				 &fsl_dcu_drm_connector_funcs,
				 DRM_MODE_CONNECTOR_LVDS);
	अगर (ret < 0)
		वापस ret;

	drm_connector_helper_add(connector, &connector_helper_funcs);
	ret = drm_connector_रेजिस्टर(connector);
	अगर (ret < 0)
		जाओ err_cleanup;

	ret = drm_connector_attach_encoder(connector, encoder);
	अगर (ret < 0)
		जाओ err_sysfs;

	वापस 0;

err_sysfs:
	drm_connector_unरेजिस्टर(connector);
err_cleanup:
	drm_connector_cleanup(connector);
	वापस ret;
पूर्ण

पूर्णांक fsl_dcu_create_outमाला_दो(काष्ठा fsl_dcu_drm_device *fsl_dev)
अणु
	काष्ठा device_node *panel_node;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret;

	/* This is क्रम backward compatibility */
	panel_node = of_parse_phandle(fsl_dev->np, "fsl,panel", 0);
	अगर (panel_node) अणु
		fsl_dev->connector.panel = of_drm_find_panel(panel_node);
		of_node_put(panel_node);
		अगर (IS_ERR(fsl_dev->connector.panel))
			वापस PTR_ERR(fsl_dev->connector.panel);

		वापस fsl_dcu_attach_panel(fsl_dev, fsl_dev->connector.panel);
	पूर्ण

	ret = drm_of_find_panel_or_bridge(fsl_dev->np, 0, 0, &panel, &bridge);
	अगर (ret)
		वापस ret;

	अगर (panel) अणु
		fsl_dev->connector.panel = panel;
		वापस fsl_dcu_attach_panel(fsl_dev, panel);
	पूर्ण

	वापस drm_bridge_attach(&fsl_dev->encoder, bridge, शून्य, 0);
पूर्ण
