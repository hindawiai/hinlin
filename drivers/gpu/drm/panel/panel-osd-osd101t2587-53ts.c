<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

#समावेश <video/mipi_display.h>

काष्ठा osd101t2587_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *dsi;

	काष्ठा regulator *supply;

	bool prepared;
	bool enabled;

	स्थिर काष्ठा drm_display_mode *शेष_mode;
पूर्ण;

अटल अंतरभूत काष्ठा osd101t2587_panel *ti_osd_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा osd101t2587_panel, base);
पूर्ण

अटल पूर्णांक osd101t2587_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा osd101t2587_panel *osd101t2587 = ti_osd_panel(panel);
	पूर्णांक ret;

	अगर (!osd101t2587->enabled)
		वापस 0;

	ret = mipi_dsi_shutकरोwn_peripheral(osd101t2587->dsi);

	osd101t2587->enabled = false;

	वापस ret;
पूर्ण

अटल पूर्णांक osd101t2587_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा osd101t2587_panel *osd101t2587 = ti_osd_panel(panel);

	अगर (!osd101t2587->prepared)
		वापस 0;

	regulator_disable(osd101t2587->supply);
	osd101t2587->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक osd101t2587_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा osd101t2587_panel *osd101t2587 = ti_osd_panel(panel);
	पूर्णांक ret;

	अगर (osd101t2587->prepared)
		वापस 0;

	ret = regulator_enable(osd101t2587->supply);
	अगर (!ret)
		osd101t2587->prepared = true;

	वापस ret;
पूर्ण

अटल पूर्णांक osd101t2587_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा osd101t2587_panel *osd101t2587 = ti_osd_panel(panel);
	पूर्णांक ret;

	अगर (osd101t2587->enabled)
		वापस 0;

	ret = mipi_dsi_turn_on_peripheral(osd101t2587->dsi);
	अगर (ret)
		वापस ret;

	osd101t2587->enabled = true;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode_osd101t2587 = अणु
	.घड़ी = 164400,
	.hdisplay = 1920,
	.hsync_start = 1920 + 152,
	.hsync_end = 1920 + 152 + 52,
	.htotal = 1920 + 152 + 52 + 20,
	.vdisplay = 1200,
	.vsync_start = 1200 + 24,
	.vsync_end = 1200 + 24 + 6,
	.vtotal = 1200 + 24 + 6 + 48,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल पूर्णांक osd101t2587_panel_get_modes(काष्ठा drm_panel *panel,
				       काष्ठा drm_connector *connector)
अणु
	काष्ठा osd101t2587_panel *osd101t2587 = ti_osd_panel(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, osd101t2587->शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%ux@%u\n",
			osd101t2587->शेष_mode->hdisplay,
			osd101t2587->शेष_mode->vdisplay,
			drm_mode_vrefresh(osd101t2587->शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 217;
	connector->display_info.height_mm = 136;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs osd101t2587_panel_funcs = अणु
	.disable = osd101t2587_panel_disable,
	.unprepare = osd101t2587_panel_unprepare,
	.prepare = osd101t2587_panel_prepare,
	.enable = osd101t2587_panel_enable,
	.get_modes = osd101t2587_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id osd101t2587_of_match[] = अणु
	अणु
		.compatible = "osddisplays,osd101t2587-53ts",
		.data = &शेष_mode_osd101t2587,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, osd101t2587_of_match);

अटल पूर्णांक osd101t2587_panel_add(काष्ठा osd101t2587_panel *osd101t2587)
अणु
	काष्ठा device *dev = &osd101t2587->dsi->dev;
	पूर्णांक ret;

	osd101t2587->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(osd101t2587->supply))
		वापस PTR_ERR(osd101t2587->supply);

	drm_panel_init(&osd101t2587->base, &osd101t2587->dsi->dev,
		       &osd101t2587_panel_funcs, DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&osd101t2587->base);
	अगर (ret)
		वापस ret;

	drm_panel_add(&osd101t2587->base);

	वापस 0;
पूर्ण

अटल पूर्णांक osd101t2587_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा osd101t2587_panel *osd101t2587;
	स्थिर काष्ठा of_device_id *id;
	पूर्णांक ret;

	id = of_match_node(osd101t2587_of_match, dsi->dev.of_node);
	अगर (!id)
		वापस -ENODEV;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
			  MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			  MIPI_DSI_MODE_EOT_PACKET;

	osd101t2587 = devm_kzalloc(&dsi->dev, माप(*osd101t2587), GFP_KERNEL);
	अगर (!osd101t2587)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, osd101t2587);

	osd101t2587->dsi = dsi;
	osd101t2587->शेष_mode = id->data;

	ret = osd101t2587_panel_add(osd101t2587);
	अगर (ret < 0)
		वापस ret;

	ret = mipi_dsi_attach(dsi);
	अगर (ret)
		drm_panel_हटाओ(&osd101t2587->base);

	वापस ret;
पूर्ण

अटल पूर्णांक osd101t2587_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा osd101t2587_panel *osd101t2587 = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = drm_panel_disable(&osd101t2587->base);
	अगर (ret < 0)
		dev_warn(&dsi->dev, "failed to disable panel: %d\n", ret);

	drm_panel_unprepare(&osd101t2587->base);
	drm_panel_हटाओ(&osd101t2587->base);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम osd101t2587_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा osd101t2587_panel *osd101t2587 = mipi_dsi_get_drvdata(dsi);

	drm_panel_disable(&osd101t2587->base);
	drm_panel_unprepare(&osd101t2587->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver osd101t2587_panel_driver = अणु
	.driver = अणु
		.name = "panel-osd-osd101t2587-53ts",
		.of_match_table = osd101t2587_of_match,
	पूर्ण,
	.probe = osd101t2587_panel_probe,
	.हटाओ = osd101t2587_panel_हटाओ,
	.shutकरोwn = osd101t2587_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(osd101t2587_panel_driver);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("OSD101T2587-53TS DSI panel");
MODULE_LICENSE("GPL v2");
