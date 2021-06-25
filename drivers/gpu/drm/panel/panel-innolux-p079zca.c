<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2017, Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा panel_init_cmd अणु
	माप_प्रकार len;
	स्थिर अक्षर *data;
पूर्ण;

#घोषणा _INIT_CMD(...) अणु \
	.len = माप((अक्षर[])अणु__VA_ARGS__पूर्ण), \
	.data = (अक्षर[])अणु__VA_ARGS__पूर्ण पूर्ण

काष्ठा panel_desc अणु
	स्थिर काष्ठा drm_display_mode *mode;
	अचिन्हित पूर्णांक bpc;
	काष्ठा अणु
		अचिन्हित पूर्णांक width;
		अचिन्हित पूर्णांक height;
	पूर्ण size;

	अचिन्हित दीर्घ flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	स्थिर काष्ठा panel_init_cmd *init_cmds;
	अचिन्हित पूर्णांक lanes;
	स्थिर अक्षर * स्थिर *supply_names;
	अचिन्हित पूर्णांक num_supplies;
	अचिन्हित पूर्णांक sleep_mode_delay;
	अचिन्हित पूर्णांक घातer_करोwn_delay;
पूर्ण;

काष्ठा innolux_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *link;
	स्थिर काष्ठा panel_desc *desc;

	काष्ठा regulator_bulk_data *supplies;
	काष्ठा gpio_desc *enable_gpio;

	bool prepared;
	bool enabled;
पूर्ण;

अटल अंतरभूत काष्ठा innolux_panel *to_innolux_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा innolux_panel, base);
पूर्ण

अटल पूर्णांक innolux_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा innolux_panel *innolux = to_innolux_panel(panel);

	अगर (!innolux->enabled)
		वापस 0;

	innolux->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक innolux_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा innolux_panel *innolux = to_innolux_panel(panel);
	पूर्णांक err;

	अगर (!innolux->prepared)
		वापस 0;

	err = mipi_dsi_dcs_set_display_off(innolux->link);
	अगर (err < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", err);

	err = mipi_dsi_dcs_enter_sleep_mode(innolux->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", err);
		वापस err;
	पूर्ण

	अगर (innolux->desc->sleep_mode_delay)
		msleep(innolux->desc->sleep_mode_delay);

	gpiod_set_value_cansleep(innolux->enable_gpio, 0);

	अगर (innolux->desc->घातer_करोwn_delay)
		msleep(innolux->desc->घातer_करोwn_delay);

	err = regulator_bulk_disable(innolux->desc->num_supplies,
				     innolux->supplies);
	अगर (err < 0)
		वापस err;

	innolux->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक innolux_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा innolux_panel *innolux = to_innolux_panel(panel);
	पूर्णांक err;

	अगर (innolux->prepared)
		वापस 0;

	gpiod_set_value_cansleep(innolux->enable_gpio, 0);

	err = regulator_bulk_enable(innolux->desc->num_supplies,
				    innolux->supplies);
	अगर (err < 0)
		वापस err;

	/* p079zca: t2 (20ms), p097pfg: t4 (15ms) */
	usleep_range(20000, 21000);

	gpiod_set_value_cansleep(innolux->enable_gpio, 1);

	/* p079zca: t4, p097pfg: t5 */
	usleep_range(20000, 21000);

	अगर (innolux->desc->init_cmds) अणु
		स्थिर काष्ठा panel_init_cmd *cmds =
					innolux->desc->init_cmds;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; cmds[i].len != 0; i++) अणु
			स्थिर काष्ठा panel_init_cmd *cmd = &cmds[i];

			err = mipi_dsi_generic_ग_लिखो(innolux->link, cmd->data,
						     cmd->len);
			अगर (err < 0) अणु
				dev_err(panel->dev, "failed to write command %u\n", i);
				जाओ घातeroff;
			पूर्ण

			/*
			 * Included by अक्रमom guessing, because without this
			 * (or at least, some delay), the panel someबार
			 * didn't appear to pick up the command sequence.
			 */
			err = mipi_dsi_dcs_nop(innolux->link);
			अगर (err < 0) अणु
				dev_err(panel->dev, "failed to send DCS nop: %d\n", err);
				जाओ घातeroff;
			पूर्ण
		पूर्ण
	पूर्ण

	err = mipi_dsi_dcs_निकास_sleep_mode(innolux->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* T6: 120ms - 1000ms*/
	msleep(120);

	err = mipi_dsi_dcs_set_display_on(innolux->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set display on: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* T7: 5ms */
	usleep_range(5000, 6000);

	innolux->prepared = true;

	वापस 0;

घातeroff:
	gpiod_set_value_cansleep(innolux->enable_gpio, 0);
	regulator_bulk_disable(innolux->desc->num_supplies, innolux->supplies);

	वापस err;
पूर्ण

अटल पूर्णांक innolux_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा innolux_panel *innolux = to_innolux_panel(panel);

	अगर (innolux->enabled)
		वापस 0;

	innolux->enabled = true;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर innolux_p079zca_supply_names[] = अणु
	"power",
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_p079zca_mode = अणु
	.घड़ी = 56900,
	.hdisplay = 768,
	.hsync_start = 768 + 40,
	.hsync_end = 768 + 40 + 40,
	.htotal = 768 + 40 + 40 + 40,
	.vdisplay = 1024,
	.vsync_start = 1024 + 20,
	.vsync_end = 1024 + 20 + 4,
	.vtotal = 1024 + 20 + 4 + 20,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_p079zca_panel_desc = अणु
	.mode = &innolux_p079zca_mode,
	.bpc = 8,
	.size = अणु
		.width = 120,
		.height = 160,
	पूर्ण,
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		 MIPI_DSI_MODE_LPM,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
	.supply_names = innolux_p079zca_supply_names,
	.num_supplies = ARRAY_SIZE(innolux_p079zca_supply_names),
	.घातer_करोwn_delay = 80, /* T8: 80ms - 1000ms */
पूर्ण;

अटल स्थिर अक्षर * स्थिर innolux_p097pfg_supply_names[] = अणु
	"avdd",
	"avee",
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_p097pfg_mode = अणु
	.घड़ी = 229000,
	.hdisplay = 1536,
	.hsync_start = 1536 + 100,
	.hsync_end = 1536 + 100 + 24,
	.htotal = 1536 + 100 + 24 + 100,
	.vdisplay = 2048,
	.vsync_start = 2048 + 100,
	.vsync_end = 2048 + 100 + 2,
	.vtotal = 2048 + 100 + 2 + 18,
पूर्ण;

/*
 * Display manufacturer failed to provide init sequencing according to
 * https://chromium-review.googlesource.com/c/chromiumos/third_party/coreboot/+/892065/
 * so the init sequence stems from a रेजिस्टर dump of a working panel.
 */
अटल स्थिर काष्ठा panel_init_cmd innolux_p097pfg_init_cmds[] = अणु
	/* page 0 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x00),
	_INIT_CMD(0xB1, 0xE8, 0x11),
	_INIT_CMD(0xB2, 0x25, 0x02),
	_INIT_CMD(0xB5, 0x08, 0x00),
	_INIT_CMD(0xBC, 0x0F, 0x00),
	_INIT_CMD(0xB8, 0x03, 0x06, 0x00, 0x00),
	_INIT_CMD(0xBD, 0x01, 0x90, 0x14, 0x14),
	_INIT_CMD(0x6F, 0x01),
	_INIT_CMD(0xC0, 0x03),
	_INIT_CMD(0x6F, 0x02),
	_INIT_CMD(0xC1, 0x0D),
	_INIT_CMD(0xD9, 0x01, 0x09, 0x70),
	_INIT_CMD(0xC5, 0x12, 0x21, 0x00),
	_INIT_CMD(0xBB, 0x93, 0x93),

	/* page 1 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01),
	_INIT_CMD(0xB3, 0x3C, 0x3C),
	_INIT_CMD(0xB4, 0x0F, 0x0F),
	_INIT_CMD(0xB9, 0x45, 0x45),
	_INIT_CMD(0xBA, 0x14, 0x14),
	_INIT_CMD(0xCA, 0x02),
	_INIT_CMD(0xCE, 0x04),
	_INIT_CMD(0xC3, 0x9B, 0x9B),
	_INIT_CMD(0xD8, 0xC0, 0x03),
	_INIT_CMD(0xBC, 0x82, 0x01),
	_INIT_CMD(0xBD, 0x9E, 0x01),

	/* page 2 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x02),
	_INIT_CMD(0xB0, 0x82),
	_INIT_CMD(0xD1, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x82, 0x00, 0xA5,
		  0x00, 0xC1, 0x00, 0xEA, 0x01, 0x0D, 0x01, 0x40),
	_INIT_CMD(0xD2, 0x01, 0x6A, 0x01, 0xA8, 0x01, 0xDC, 0x02, 0x29,
		  0x02, 0x67, 0x02, 0x68, 0x02, 0xA8, 0x02, 0xF0),
	_INIT_CMD(0xD3, 0x03, 0x19, 0x03, 0x49, 0x03, 0x67, 0x03, 0x8C,
		  0x03, 0xA6, 0x03, 0xC7, 0x03, 0xDE, 0x03, 0xEC),
	_INIT_CMD(0xD4, 0x03, 0xFF, 0x03, 0xFF),
	_INIT_CMD(0xE0, 0x00, 0x00, 0x00, 0x86, 0x00, 0xC5, 0x00, 0xE5,
		  0x00, 0xFF, 0x01, 0x26, 0x01, 0x45, 0x01, 0x75),
	_INIT_CMD(0xE1, 0x01, 0x9C, 0x01, 0xD5, 0x02, 0x05, 0x02, 0x4D,
		  0x02, 0x86, 0x02, 0x87, 0x02, 0xC3, 0x03, 0x03),
	_INIT_CMD(0xE2, 0x03, 0x2A, 0x03, 0x56, 0x03, 0x72, 0x03, 0x94,
		  0x03, 0xAC, 0x03, 0xCB, 0x03, 0xE0, 0x03, 0xED),
	_INIT_CMD(0xE3, 0x03, 0xFF, 0x03, 0xFF),

	/* page 3 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x03),
	_INIT_CMD(0xB0, 0x00, 0x00, 0x00, 0x00),
	_INIT_CMD(0xB1, 0x00, 0x00, 0x00, 0x00),
	_INIT_CMD(0xB2, 0x00, 0x00, 0x06, 0x04, 0x01, 0x40, 0x85),
	_INIT_CMD(0xB3, 0x10, 0x07, 0xFC, 0x04, 0x01, 0x40, 0x80),
	_INIT_CMD(0xB6, 0xF0, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01,
		  0x40, 0x80),
	_INIT_CMD(0xBA, 0xC5, 0x07, 0x00, 0x04, 0x11, 0x25, 0x8C),
	_INIT_CMD(0xBB, 0xC5, 0x07, 0x00, 0x03, 0x11, 0x25, 0x8C),
	_INIT_CMD(0xC0, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x80, 0x80),
	_INIT_CMD(0xC1, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x80, 0x80),
	_INIT_CMD(0xC4, 0x00, 0x00),
	_INIT_CMD(0xEF, 0x41),

	/* page 4 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x04),
	_INIT_CMD(0xEC, 0x4C),

	/* page 5 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x05),
	_INIT_CMD(0xB0, 0x13, 0x03, 0x03, 0x01),
	_INIT_CMD(0xB1, 0x30, 0x00),
	_INIT_CMD(0xB2, 0x02, 0x02, 0x00),
	_INIT_CMD(0xB3, 0x82, 0x23, 0x82, 0x9D),
	_INIT_CMD(0xB4, 0xC5, 0x75, 0x24, 0x57),
	_INIT_CMD(0xB5, 0x00, 0xD4, 0x72, 0x11, 0x11, 0xAB, 0x0A),
	_INIT_CMD(0xB6, 0x00, 0x00, 0xD5, 0x72, 0x24, 0x56),
	_INIT_CMD(0xB7, 0x5C, 0xDC, 0x5C, 0x5C),
	_INIT_CMD(0xB9, 0x0C, 0x00, 0x00, 0x01, 0x00),
	_INIT_CMD(0xC0, 0x75, 0x11, 0x11, 0x54, 0x05),
	_INIT_CMD(0xC6, 0x00, 0x00, 0x00, 0x00),
	_INIT_CMD(0xD0, 0x00, 0x48, 0x08, 0x00, 0x00),
	_INIT_CMD(0xD1, 0x00, 0x48, 0x09, 0x00, 0x00),

	/* page 6 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x06),
	_INIT_CMD(0xB0, 0x02, 0x32, 0x32, 0x08, 0x2F),
	_INIT_CMD(0xB1, 0x2E, 0x15, 0x14, 0x13, 0x12),
	_INIT_CMD(0xB2, 0x11, 0x10, 0x00, 0x3D, 0x3D),
	_INIT_CMD(0xB3, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D),
	_INIT_CMD(0xB4, 0x3D, 0x32),
	_INIT_CMD(0xB5, 0x03, 0x32, 0x32, 0x09, 0x2F),
	_INIT_CMD(0xB6, 0x2E, 0x1B, 0x1A, 0x19, 0x18),
	_INIT_CMD(0xB7, 0x17, 0x16, 0x01, 0x3D, 0x3D),
	_INIT_CMD(0xB8, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D),
	_INIT_CMD(0xB9, 0x3D, 0x32),
	_INIT_CMD(0xC0, 0x01, 0x32, 0x32, 0x09, 0x2F),
	_INIT_CMD(0xC1, 0x2E, 0x1A, 0x1B, 0x16, 0x17),
	_INIT_CMD(0xC2, 0x18, 0x19, 0x03, 0x3D, 0x3D),
	_INIT_CMD(0xC3, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D),
	_INIT_CMD(0xC4, 0x3D, 0x32),
	_INIT_CMD(0xC5, 0x00, 0x32, 0x32, 0x08, 0x2F),
	_INIT_CMD(0xC6, 0x2E, 0x14, 0x15, 0x10, 0x11),
	_INIT_CMD(0xC7, 0x12, 0x13, 0x02, 0x3D, 0x3D),
	_INIT_CMD(0xC8, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D),
	_INIT_CMD(0xC9, 0x3D, 0x32),

	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_p097pfg_panel_desc = अणु
	.mode = &innolux_p097pfg_mode,
	.bpc = 8,
	.size = अणु
		.width = 147,
		.height = 196,
	पूर्ण,
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		 MIPI_DSI_MODE_LPM,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.init_cmds = innolux_p097pfg_init_cmds,
	.lanes = 4,
	.supply_names = innolux_p097pfg_supply_names,
	.num_supplies = ARRAY_SIZE(innolux_p097pfg_supply_names),
	.sleep_mode_delay = 100, /* T15 */
पूर्ण;

अटल पूर्णांक innolux_panel_get_modes(काष्ठा drm_panel *panel,
				   काष्ठा drm_connector *connector)
अणु
	काष्ठा innolux_panel *innolux = to_innolux_panel(panel);
	स्थिर काष्ठा drm_display_mode *m = innolux->desc->mode;
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, m);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
			m->hdisplay, m->vdisplay, drm_mode_vrefresh(m));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = innolux->desc->size.width;
	connector->display_info.height_mm = innolux->desc->size.height;
	connector->display_info.bpc = innolux->desc->bpc;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs innolux_panel_funcs = अणु
	.disable = innolux_panel_disable,
	.unprepare = innolux_panel_unprepare,
	.prepare = innolux_panel_prepare,
	.enable = innolux_panel_enable,
	.get_modes = innolux_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id innolux_of_match[] = अणु
	अणु .compatible = "innolux,p079zca",
	  .data = &innolux_p079zca_panel_desc
	पूर्ण,
	अणु .compatible = "innolux,p097pfg",
	  .data = &innolux_p097pfg_panel_desc
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, innolux_of_match);

अटल पूर्णांक innolux_panel_add(काष्ठा mipi_dsi_device *dsi,
			     स्थिर काष्ठा panel_desc *desc)
अणु
	काष्ठा innolux_panel *innolux;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक err, i;

	innolux = devm_kzalloc(dev, माप(*innolux), GFP_KERNEL);
	अगर (!innolux)
		वापस -ENOMEM;

	innolux->desc = desc;

	innolux->supplies = devm_kसुस्मृति(dev, desc->num_supplies,
					 माप(*innolux->supplies),
					 GFP_KERNEL);
	अगर (!innolux->supplies)
		वापस -ENOMEM;

	क्रम (i = 0; i < desc->num_supplies; i++)
		innolux->supplies[i].supply = desc->supply_names[i];

	err = devm_regulator_bulk_get(dev, desc->num_supplies,
				      innolux->supplies);
	अगर (err < 0)
		वापस err;

	innolux->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						       GPIOD_OUT_HIGH);
	अगर (IS_ERR(innolux->enable_gpio)) अणु
		err = PTR_ERR(innolux->enable_gpio);
		dev_dbg(dev, "failed to get enable gpio: %d\n", err);
		innolux->enable_gpio = शून्य;
	पूर्ण

	drm_panel_init(&innolux->base, dev, &innolux_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	err = drm_panel_of_backlight(&innolux->base);
	अगर (err)
		वापस err;

	drm_panel_add(&innolux->base);

	mipi_dsi_set_drvdata(dsi, innolux);
	innolux->link = dsi;

	वापस 0;
पूर्ण

अटल व्योम innolux_panel_del(काष्ठा innolux_panel *innolux)
अणु
	drm_panel_हटाओ(&innolux->base);
पूर्ण

अटल पूर्णांक innolux_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	स्थिर काष्ठा panel_desc *desc;
	पूर्णांक err;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_flags = desc->flags;
	dsi->क्रमmat = desc->क्रमmat;
	dsi->lanes = desc->lanes;

	err = innolux_panel_add(dsi, desc);
	अगर (err < 0)
		वापस err;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक innolux_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा innolux_panel *innolux = mipi_dsi_get_drvdata(dsi);
	पूर्णांक err;

	err = drm_panel_unprepare(&innolux->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to unprepare panel: %d\n", err);

	err = drm_panel_disable(&innolux->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", err);

	err = mipi_dsi_detach(dsi);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	innolux_panel_del(innolux);

	वापस 0;
पूर्ण

अटल व्योम innolux_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा innolux_panel *innolux = mipi_dsi_get_drvdata(dsi);

	drm_panel_unprepare(&innolux->base);
	drm_panel_disable(&innolux->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver innolux_panel_driver = अणु
	.driver = अणु
		.name = "panel-innolux-p079zca",
		.of_match_table = innolux_of_match,
	पूर्ण,
	.probe = innolux_panel_probe,
	.हटाओ = innolux_panel_हटाओ,
	.shutकरोwn = innolux_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(innolux_panel_driver);

MODULE_AUTHOR("Chris Zhong <zyw@rock-chips.com>");
MODULE_AUTHOR("Lin Huang <hl@rock-chips.com>");
MODULE_DESCRIPTION("Innolux P079ZCA panel driver");
MODULE_LICENSE("GPL v2");
