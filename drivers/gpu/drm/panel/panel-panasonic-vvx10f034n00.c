<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Red Hat
 * Copyright (C) 2015 Sony Mobile Communications Inc.
 * Author: Werner Johansson <werner.johansson@sonymobile.com>
 *
 * Based on AUO panel driver by Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

/*
 * When घातer is turned off to this panel a minimum off समय of 500ms has to be
 * observed beक्रमe घातering back on as there's no बाह्यal reset pin. Keep
 * track of earliest wakeup समय and delay subsequent prepare call accordingly
 */
#घोषणा MIN_POFF_MS (500)

काष्ठा wuxga_nt_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *dsi;

	काष्ठा regulator *supply;

	bool prepared;
	bool enabled;

	kसमय_प्रकार earliest_wake;

	स्थिर काष्ठा drm_display_mode *mode;
पूर्ण;

अटल अंतरभूत काष्ठा wuxga_nt_panel *to_wuxga_nt_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा wuxga_nt_panel, base);
पूर्ण

अटल पूर्णांक wuxga_nt_panel_on(काष्ठा wuxga_nt_panel *wuxga_nt)
अणु
	वापस mipi_dsi_turn_on_peripheral(wuxga_nt->dsi);
पूर्ण

अटल पूर्णांक wuxga_nt_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा wuxga_nt_panel *wuxga_nt = to_wuxga_nt_panel(panel);
	पूर्णांक mipi_ret, bl_ret = 0;

	अगर (!wuxga_nt->enabled)
		वापस 0;

	mipi_ret = mipi_dsi_shutकरोwn_peripheral(wuxga_nt->dsi);

	wuxga_nt->enabled = false;

	वापस mipi_ret ? mipi_ret : bl_ret;
पूर्ण

अटल पूर्णांक wuxga_nt_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा wuxga_nt_panel *wuxga_nt = to_wuxga_nt_panel(panel);

	अगर (!wuxga_nt->prepared)
		वापस 0;

	regulator_disable(wuxga_nt->supply);
	wuxga_nt->earliest_wake = kसमय_add_ms(kसमय_get_real(), MIN_POFF_MS);
	wuxga_nt->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक wuxga_nt_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा wuxga_nt_panel *wuxga_nt = to_wuxga_nt_panel(panel);
	पूर्णांक ret;
	s64 enableरुको;

	अगर (wuxga_nt->prepared)
		वापस 0;

	/*
	 * If the user re-enabled the panel beक्रमe the required off-समय then
	 * we need to रुको the reमुख्यing period beक्रमe re-enabling regulator
	 */
	enableरुको = kसमय_ms_delta(wuxga_nt->earliest_wake, kसमय_get_real());

	/* Sanity check, this should never happen */
	अगर (enableरुको > MIN_POFF_MS)
		enableरुको = MIN_POFF_MS;

	अगर (enableरुको > 0)
		msleep(enableरुको);

	ret = regulator_enable(wuxga_nt->supply);
	अगर (ret < 0)
		वापस ret;

	/*
	 * A minimum delay of 250ms is required after घातer-up until commands
	 * can be sent
	 */
	msleep(250);

	ret = wuxga_nt_panel_on(wuxga_nt);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to set panel on: %d\n", ret);
		जाओ घातeroff;
	पूर्ण

	wuxga_nt->prepared = true;

	वापस 0;

घातeroff:
	regulator_disable(wuxga_nt->supply);

	वापस ret;
पूर्ण

अटल पूर्णांक wuxga_nt_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा wuxga_nt_panel *wuxga_nt = to_wuxga_nt_panel(panel);

	अगर (wuxga_nt->enabled)
		वापस 0;

	wuxga_nt->enabled = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 164402,
	.hdisplay = 1920,
	.hsync_start = 1920 + 152,
	.hsync_end = 1920 + 152 + 52,
	.htotal = 1920 + 152 + 52 + 20,
	.vdisplay = 1200,
	.vsync_start = 1200 + 24,
	.vsync_end = 1200 + 24 + 6,
	.vtotal = 1200 + 24 + 6 + 48,
पूर्ण;

अटल पूर्णांक wuxga_nt_panel_get_modes(काष्ठा drm_panel *panel,
				    काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 217;
	connector->display_info.height_mm = 136;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs wuxga_nt_panel_funcs = अणु
	.disable = wuxga_nt_panel_disable,
	.unprepare = wuxga_nt_panel_unprepare,
	.prepare = wuxga_nt_panel_prepare,
	.enable = wuxga_nt_panel_enable,
	.get_modes = wuxga_nt_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wuxga_nt_of_match[] = अणु
	अणु .compatible = "panasonic,vvx10f034n00", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wuxga_nt_of_match);

अटल पूर्णांक wuxga_nt_panel_add(काष्ठा wuxga_nt_panel *wuxga_nt)
अणु
	काष्ठा device *dev = &wuxga_nt->dsi->dev;
	पूर्णांक ret;

	wuxga_nt->mode = &शेष_mode;

	wuxga_nt->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(wuxga_nt->supply))
		वापस PTR_ERR(wuxga_nt->supply);

	drm_panel_init(&wuxga_nt->base, &wuxga_nt->dsi->dev,
		       &wuxga_nt_panel_funcs, DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&wuxga_nt->base);
	अगर (ret)
		वापस ret;

	drm_panel_add(&wuxga_nt->base);

	वापस 0;
पूर्ण

अटल व्योम wuxga_nt_panel_del(काष्ठा wuxga_nt_panel *wuxga_nt)
अणु
	अगर (wuxga_nt->base.dev)
		drm_panel_हटाओ(&wuxga_nt->base);
पूर्ण

अटल पूर्णांक wuxga_nt_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा wuxga_nt_panel *wuxga_nt;
	पूर्णांक ret;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
			MIPI_DSI_MODE_VIDEO_HSE |
			MIPI_DSI_CLOCK_NON_CONTINUOUS |
			MIPI_DSI_MODE_LPM;

	wuxga_nt = devm_kzalloc(&dsi->dev, माप(*wuxga_nt), GFP_KERNEL);
	अगर (!wuxga_nt)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, wuxga_nt);

	wuxga_nt->dsi = dsi;

	ret = wuxga_nt_panel_add(wuxga_nt);
	अगर (ret < 0)
		वापस ret;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक wuxga_nt_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा wuxga_nt_panel *wuxga_nt = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = drm_panel_disable(&wuxga_nt->base);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", ret);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", ret);

	wuxga_nt_panel_del(wuxga_nt);

	वापस 0;
पूर्ण

अटल व्योम wuxga_nt_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा wuxga_nt_panel *wuxga_nt = mipi_dsi_get_drvdata(dsi);

	drm_panel_disable(&wuxga_nt->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver wuxga_nt_panel_driver = अणु
	.driver = अणु
		.name = "panel-panasonic-vvx10f034n00",
		.of_match_table = wuxga_nt_of_match,
	पूर्ण,
	.probe = wuxga_nt_panel_probe,
	.हटाओ = wuxga_nt_panel_हटाओ,
	.shutकरोwn = wuxga_nt_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(wuxga_nt_panel_driver);

MODULE_AUTHOR("Werner Johansson <werner.johansson@sonymobile.com>");
MODULE_DESCRIPTION("Panasonic VVX10F034N00 Novatek NT1397-based WUXGA (1920x1200) video mode panel driver");
MODULE_LICENSE("GPL v2");
