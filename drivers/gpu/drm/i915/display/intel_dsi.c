<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <drm/drm_mipi_dsi.h>
#समावेश "intel_dsi.h"

पूर्णांक पूर्णांकel_dsi_bitrate(स्थिर काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);

	अगर (WARN_ON(bpp < 0))
		bpp = 16;

	वापस पूर्णांकel_dsi->pclk * bpp / पूर्णांकel_dsi->lane_count;
पूर्ण

पूर्णांक पूर्णांकel_dsi_tlpx_ns(स्थिर काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	चयन (पूर्णांकel_dsi->escape_clk_भाग) अणु
	शेष:
	हाल 0:
		वापस 50;
	हाल 1:
		वापस 100;
	हाल 2:
		वापस 200;
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_dsi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा drm_display_mode *mode;

	drm_dbg_kms(&i915->drm, "\n");

	अगर (!पूर्णांकel_connector->panel.fixed_mode) अणु
		drm_dbg_kms(&i915->drm, "no fixed mode\n");
		वापस 0;
	पूर्ण

	mode = drm_mode_duplicate(connector->dev,
				  पूर्णांकel_connector->panel.fixed_mode);
	अगर (!mode) अणु
		drm_dbg_kms(&i915->drm, "drm_mode_duplicate failed\n");
		वापस 0;
	पूर्ण

	drm_mode_probed_add(connector, mode);
	वापस 1;
पूर्ण

क्रमागत drm_mode_status पूर्णांकel_dsi_mode_valid(काष्ठा drm_connector *connector,
					  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	स्थिर काष्ठा drm_display_mode *fixed_mode = पूर्णांकel_connector->panel.fixed_mode;
	पूर्णांक max_करोtclk = to_i915(connector->dev)->max_करोtclk_freq;

	drm_dbg_kms(&dev_priv->drm, "\n");

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	अगर (fixed_mode) अणु
		अगर (mode->hdisplay > fixed_mode->hdisplay)
			वापस MODE_PANEL;
		अगर (mode->vdisplay > fixed_mode->vdisplay)
			वापस MODE_PANEL;
		अगर (fixed_mode->घड़ी > max_करोtclk)
			वापस MODE_CLOCK_HIGH;
	पूर्ण

	वापस पूर्णांकel_mode_valid_max_plane_size(dev_priv, mode, false);
पूर्ण

काष्ठा पूर्णांकel_dsi_host *पूर्णांकel_dsi_host_init(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
					   स्थिर काष्ठा mipi_dsi_host_ops *funcs,
					   क्रमागत port port)
अणु
	काष्ठा पूर्णांकel_dsi_host *host;
	काष्ठा mipi_dsi_device *device;

	host = kzalloc(माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस शून्य;

	host->base.ops = funcs;
	host->पूर्णांकel_dsi = पूर्णांकel_dsi;
	host->port = port;

	/*
	 * We should call mipi_dsi_host_रेजिस्टर(&host->base) here, but we करोn't
	 * have a host->dev, and we करोn't have OF stuff either. So just use the
	 * dsi framework as a library and hope क्रम the best. Create the dsi
	 * devices by ourselves here too. Need to be careful though, because we
	 * करोn't initialize any of the driver model devices here.
	 */
	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (!device) अणु
		kमुक्त(host);
		वापस शून्य;
	पूर्ण

	device->host = &host->base;
	host->device = device;

	वापस host;
पूर्ण

क्रमागत drm_panel_orientation
पूर्णांकel_dsi_get_panel_orientation(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	क्रमागत drm_panel_orientation orientation;

	orientation = dev_priv->vbt.dsi.orientation;
	अगर (orientation != DRM_MODE_PANEL_ORIENTATION_UNKNOWN)
		वापस orientation;

	orientation = dev_priv->vbt.orientation;
	अगर (orientation != DRM_MODE_PANEL_ORIENTATION_UNKNOWN)
		वापस orientation;

	वापस DRM_MODE_PANEL_ORIENTATION_NORMAL;
पूर्ण
