<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_crtc.h>

#समावेश "msm_drv.h"
#समावेश "msm_kms.h"
#समावेश "dp_drm.h"

काष्ठा dp_connector अणु
	काष्ठा drm_connector base;
	काष्ठा msm_dp *dp_display;
पूर्ण;
#घोषणा to_dp_connector(x) container_of(x, काष्ठा dp_connector, base)

/**
 * dp_connector_detect - callback to determine अगर connector is connected
 * @conn: Poपूर्णांकer to drm connector काष्ठाure
 * @क्रमce: Force detect setting from drm framework
 * Returns: Connector 'is connected' status
 */
अटल क्रमागत drm_connector_status dp_connector_detect(काष्ठा drm_connector *conn,
		bool क्रमce)
अणु
	काष्ठा msm_dp *dp;

	dp = to_dp_connector(conn)->dp_display;

	DRM_DEBUG_DP("is_connected = %s\n",
		(dp->is_connected) ? "true" : "false");

	वापस (dp->is_connected) ? connector_status_connected :
					connector_status_disconnected;
पूर्ण

/**
 * dp_connector_get_modes - callback to add drm modes via drm_mode_probed_add()
 * @connector: Poपूर्णांकer to drm connector काष्ठाure
 * Returns: Number of modes added
 */
अटल पूर्णांक dp_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक rc = 0;
	काष्ठा msm_dp *dp;
	काष्ठा dp_display_mode *dp_mode = शून्य;
	काष्ठा drm_display_mode *m, drm_mode;

	अगर (!connector)
		वापस 0;

	dp = to_dp_connector(connector)->dp_display;

	dp_mode = kzalloc(माप(*dp_mode),  GFP_KERNEL);
	अगर (!dp_mode)
		वापस 0;

	/* pluggable हाल assumes EDID is पढ़ो when HPD */
	अगर (dp->is_connected) अणु
		/*
		 *The get_modes() function might वापस one mode that is stored
		 * in dp_mode when compliance test is in progress. If not, the
		 * वापस value is equal to the total number of modes supported
		 * by the sink
		 */
		rc = dp_display_get_modes(dp, dp_mode);
		अगर (rc <= 0) अणु
			DRM_ERROR("failed to get DP sink modes, rc=%d\n", rc);
			kमुक्त(dp_mode);
			वापस rc;
		पूर्ण
		अगर (dp_mode->drm_mode.घड़ी) अणु /* valid DP mode */
			स_रखो(&drm_mode, 0x0, माप(drm_mode));
			drm_mode_copy(&drm_mode, &dp_mode->drm_mode);
			m = drm_mode_duplicate(connector->dev, &drm_mode);
			अगर (!m) अणु
				DRM_ERROR("failed to add mode %ux%u\n",
				       drm_mode.hdisplay,
				       drm_mode.vdisplay);
				kमुक्त(dp_mode);
				वापस 0;
			पूर्ण
			drm_mode_probed_add(connector, m);
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_DEBUG_DP("No sink connected\n");
	पूर्ण
	kमुक्त(dp_mode);
	वापस rc;
पूर्ण

/**
 * dp_connector_mode_valid - callback to determine अगर specअगरied mode is valid
 * @connector: Poपूर्णांकer to drm connector काष्ठाure
 * @mode: Poपूर्णांकer to drm mode काष्ठाure
 * Returns: Validity status क्रम specअगरied mode
 */
अटल क्रमागत drm_mode_status dp_connector_mode_valid(
		काष्ठा drm_connector *connector,
		काष्ठा drm_display_mode *mode)
अणु
	काष्ठा msm_dp *dp_disp;

	dp_disp = to_dp_connector(connector)->dp_display;

	अगर ((dp_disp->max_pclk_khz <= 0) ||
			(dp_disp->max_pclk_khz > DP_MAX_PIXEL_CLK_KHZ) ||
			(mode->घड़ी > dp_disp->max_pclk_khz))
		वापस MODE_BAD;

	वापस dp_display_validate_mode(dp_disp, mode->घड़ी);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs dp_connector_funcs = अणु
	.detect = dp_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs dp_connector_helper_funcs = अणु
	.get_modes = dp_connector_get_modes,
	.mode_valid = dp_connector_mode_valid,
पूर्ण;

/* connector initialization */
काष्ठा drm_connector *dp_drm_connector_init(काष्ठा msm_dp *dp_display)
अणु
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा dp_connector *dp_connector;
	पूर्णांक ret;

	dp_connector = devm_kzalloc(dp_display->drm_dev->dev,
					माप(*dp_connector),
					GFP_KERNEL);
	अगर (!dp_connector)
		वापस ERR_PTR(-ENOMEM);

	dp_connector->dp_display = dp_display;

	connector = &dp_connector->base;

	ret = drm_connector_init(dp_display->drm_dev, connector,
			&dp_connector_funcs,
			DRM_MODE_CONNECTOR_DisplayPort);
	अगर (ret)
		वापस ERR_PTR(ret);

	drm_connector_helper_add(connector, &dp_connector_helper_funcs);

	/*
	 * Enable HPD to let hpd event is handled when cable is connected.
	 */
	connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_attach_encoder(connector, dp_display->encoder);

	वापस connector;
पूर्ण
