<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#समावेश "drm/drm_edid.h"
#समावेश "msm_kms.h"
#समावेश "edp.h"

काष्ठा edp_connector अणु
	काष्ठा drm_connector base;
	काष्ठा msm_edp *edp;
पूर्ण;
#घोषणा to_edp_connector(x) container_of(x, काष्ठा edp_connector, base)

अटल क्रमागत drm_connector_status edp_connector_detect(
		काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा edp_connector *edp_connector = to_edp_connector(connector);
	काष्ठा msm_edp *edp = edp_connector->edp;

	DBG("");
	वापस msm_edp_ctrl_panel_connected(edp->ctrl) ?
		connector_status_connected : connector_status_disconnected;
पूर्ण

अटल व्योम edp_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा edp_connector *edp_connector = to_edp_connector(connector);

	DBG("");

	drm_connector_cleanup(connector);

	kमुक्त(edp_connector);
पूर्ण

अटल पूर्णांक edp_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा edp_connector *edp_connector = to_edp_connector(connector);
	काष्ठा msm_edp *edp = edp_connector->edp;

	काष्ठा edid *drm_edid = शून्य;
	पूर्णांक ret = 0;

	DBG("");
	ret = msm_edp_ctrl_get_panel_info(edp->ctrl, connector, &drm_edid);
	अगर (ret)
		वापस ret;

	drm_connector_update_edid_property(connector, drm_edid);
	अगर (drm_edid)
		ret = drm_add_edid_modes(connector, drm_edid);

	वापस ret;
पूर्ण

अटल पूर्णांक edp_connector_mode_valid(काष्ठा drm_connector *connector,
				 काष्ठा drm_display_mode *mode)
अणु
	काष्ठा edp_connector *edp_connector = to_edp_connector(connector);
	काष्ठा msm_edp *edp = edp_connector->edp;
	काष्ठा msm_drm_निजी *priv = connector->dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	दीर्घ actual, requested;

	requested = 1000 * mode->घड़ी;
	actual = kms->funcs->round_pixclk(kms,
			requested, edp_connector->edp->encoder);

	DBG("requested=%ld, actual=%ld", requested, actual);
	अगर (actual != requested)
		वापस MODE_CLOCK_RANGE;

	अगर (!msm_edp_ctrl_pixel_घड़ी_valid(
		edp->ctrl, mode->घड़ी, शून्य, शून्य))
		वापस MODE_CLOCK_RANGE;

	/* Invalidate all modes अगर color क्रमmat is not supported */
	अगर (connector->display_info.bpc > 8)
		वापस MODE_BAD;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs edp_connector_funcs = अणु
	.detect = edp_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = edp_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs edp_connector_helper_funcs = अणु
	.get_modes = edp_connector_get_modes,
	.mode_valid = edp_connector_mode_valid,
पूर्ण;

/* initialize connector */
काष्ठा drm_connector *msm_edp_connector_init(काष्ठा msm_edp *edp)
अणु
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा edp_connector *edp_connector;
	पूर्णांक ret;

	edp_connector = kzalloc(माप(*edp_connector), GFP_KERNEL);
	अगर (!edp_connector)
		वापस ERR_PTR(-ENOMEM);

	edp_connector->edp = edp;

	connector = &edp_connector->base;

	ret = drm_connector_init(edp->dev, connector, &edp_connector_funcs,
			DRM_MODE_CONNECTOR_eDP);
	अगर (ret)
		वापस ERR_PTR(ret);

	drm_connector_helper_add(connector, &edp_connector_helper_funcs);

	/* We करोn't support HPD, so only poll status until connected. */
	connector->polled = DRM_CONNECTOR_POLL_CONNECT;

	/* Display driver करोesn't support पूर्णांकerlace now. */
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	drm_connector_attach_encoder(connector, edp->encoder);

	वापस connector;
पूर्ण
