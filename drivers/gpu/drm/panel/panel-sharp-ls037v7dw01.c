<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sharp LS037V7DW01 LCD Panel Driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated
 *
 * Based on the omapdrm-specअगरic panel-sharp-ls037v7dw01 driver
 *
 * Copyright (C) 2013 Texas Instruments Incorporated
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा ls037v7dw01_panel अणु
	काष्ठा drm_panel panel;
	काष्ठा platक्रमm_device *pdev;

	काष्ठा regulator *vdd;
	काष्ठा gpio_desc *resb_gpio;	/* low = reset active min 20 us */
	काष्ठा gpio_desc *ini_gpio;	/* high = घातer on */
	काष्ठा gpio_desc *mo_gpio;	/* low = 480x640, high = 240x320 */
	काष्ठा gpio_desc *lr_gpio;	/* high = conventional horizontal scanning */
	काष्ठा gpio_desc *ud_gpio;	/* high = conventional vertical scanning */
पूर्ण;

#घोषणा to_ls037v7dw01_device(p) \
	container_of(p, काष्ठा ls037v7dw01_panel, panel)

अटल पूर्णांक ls037v7dw01_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा ls037v7dw01_panel *lcd = to_ls037v7dw01_device(panel);

	gpiod_set_value_cansleep(lcd->ini_gpio, 0);
	gpiod_set_value_cansleep(lcd->resb_gpio, 0);

	/* Wait at least 5 vsyncs after disabling the LCD. */
	msleep(100);

	वापस 0;
पूर्ण

अटल पूर्णांक ls037v7dw01_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ls037v7dw01_panel *lcd = to_ls037v7dw01_device(panel);

	regulator_disable(lcd->vdd);
	वापस 0;
पूर्ण

अटल पूर्णांक ls037v7dw01_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ls037v7dw01_panel *lcd = to_ls037v7dw01_device(panel);
	पूर्णांक ret;

	ret = regulator_enable(lcd->vdd);
	अगर (ret < 0)
		dev_err(&lcd->pdev->dev, "%s: failed to enable regulator\n",
			__func__);

	वापस ret;
पूर्ण

अटल पूर्णांक ls037v7dw01_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा ls037v7dw01_panel *lcd = to_ls037v7dw01_device(panel);

	/* Wait couple of vsyncs beक्रमe enabling the LCD. */
	msleep(50);

	gpiod_set_value_cansleep(lcd->resb_gpio, 1);
	gpiod_set_value_cansleep(lcd->ini_gpio, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode ls037v7dw01_mode = अणु
	.घड़ी = 19200,
	.hdisplay = 480,
	.hsync_start = 480 + 1,
	.hsync_end = 480 + 1 + 2,
	.htotal = 480 + 1 + 2 + 28,
	.vdisplay = 640,
	.vsync_start = 640 + 1,
	.vsync_end = 640 + 1 + 1,
	.vtotal = 640 + 1 + 1 + 1,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm = 56,
	.height_mm = 75,
पूर्ण;

अटल पूर्णांक ls037v7dw01_get_modes(काष्ठा drm_panel *panel,
				 काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &ls037v7dw01_mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = ls037v7dw01_mode.width_mm;
	connector->display_info.height_mm = ls037v7dw01_mode.height_mm;
	/*
	 * FIXME: According to the datasheet pixel data is sampled on the
	 * rising edge of the घड़ी, but the code running on the SDP3430
	 * indicates sampling on the negative edge. This should be tested on a
	 * real device.
	 */
	connector->display_info.bus_flags = DRM_BUS_FLAG_DE_HIGH
					  | DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE
					  | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs ls037v7dw01_funcs = अणु
	.disable = ls037v7dw01_disable,
	.unprepare = ls037v7dw01_unprepare,
	.prepare = ls037v7dw01_prepare,
	.enable = ls037v7dw01_enable,
	.get_modes = ls037v7dw01_get_modes,
पूर्ण;

अटल पूर्णांक ls037v7dw01_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ls037v7dw01_panel *lcd;

	lcd = devm_kzalloc(&pdev->dev, माप(*lcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, lcd);
	lcd->pdev = pdev;

	lcd->vdd = devm_regulator_get(&pdev->dev, "envdd");
	अगर (IS_ERR(lcd->vdd)) अणु
		dev_err(&pdev->dev, "failed to get regulator\n");
		वापस PTR_ERR(lcd->vdd);
	पूर्ण

	lcd->ini_gpio = devm_gpiod_get(&pdev->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->ini_gpio)) अणु
		dev_err(&pdev->dev, "failed to get enable gpio\n");
		वापस PTR_ERR(lcd->ini_gpio);
	पूर्ण

	lcd->resb_gpio = devm_gpiod_get(&pdev->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->resb_gpio)) अणु
		dev_err(&pdev->dev, "failed to get reset gpio\n");
		वापस PTR_ERR(lcd->resb_gpio);
	पूर्ण

	lcd->mo_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 0,
					    GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->mo_gpio)) अणु
		dev_err(&pdev->dev, "failed to get mode[0] gpio\n");
		वापस PTR_ERR(lcd->mo_gpio);
	पूर्ण

	lcd->lr_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 1,
					    GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->lr_gpio)) अणु
		dev_err(&pdev->dev, "failed to get mode[1] gpio\n");
		वापस PTR_ERR(lcd->lr_gpio);
	पूर्ण

	lcd->ud_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 2,
					    GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->ud_gpio)) अणु
		dev_err(&pdev->dev, "failed to get mode[2] gpio\n");
		वापस PTR_ERR(lcd->ud_gpio);
	पूर्ण

	drm_panel_init(&lcd->panel, &pdev->dev, &ls037v7dw01_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&lcd->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक ls037v7dw01_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ls037v7dw01_panel *lcd = platक्रमm_get_drvdata(pdev);

	drm_panel_हटाओ(&lcd->panel);
	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ls037v7dw01_of_match[] = अणु
	अणु .compatible = "sharp,ls037v7dw01", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, ls037v7dw01_of_match);

अटल काष्ठा platक्रमm_driver ls037v7dw01_driver = अणु
	.probe		= ls037v7dw01_probe,
	.हटाओ		= ls037v7dw01_हटाओ,
	.driver		= अणु
		.name = "panel-sharp-ls037v7dw01",
		.of_match_table = ls037v7dw01_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ls037v7dw01_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("Sharp LS037V7DW01 Panel Driver");
MODULE_LICENSE("GPL");
