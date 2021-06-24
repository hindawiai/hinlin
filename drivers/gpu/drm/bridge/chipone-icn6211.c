<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2020 Amarula Solutions(India)
 * Author: Jagan Teki <jagan@amarulasolutions.com>
 */

#समावेश <drm/drm_of.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_mipi_dsi.h>

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#घोषणा HACTIVE_LI		0x20
#घोषणा VACTIVE_LI		0x21
#घोषणा VACTIVE_HACTIVE_HI	0x22
#घोषणा HFP_LI			0x23
#घोषणा HSYNC_LI		0x24
#घोषणा HBP_LI			0x25
#घोषणा HFP_HSW_HBP_HI		0x26
#घोषणा VFP			0x27
#घोषणा VSYNC			0x28
#घोषणा VBP			0x29

काष्ठा chipone अणु
	काष्ठा device *dev;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator *vdd1;
	काष्ठा regulator *vdd2;
	काष्ठा regulator *vdd3;
पूर्ण;

अटल अंतरभूत काष्ठा chipone *bridge_to_chipone(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा chipone, bridge);
पूर्ण

अटल काष्ठा drm_display_mode *bridge_to_mode(काष्ठा drm_bridge *bridge)
अणु
	वापस &bridge->encoder->crtc->state->adjusted_mode;
पूर्ण

अटल अंतरभूत पूर्णांक chipone_dsi_ग_लिखो(काष्ठा chipone *icn,  स्थिर व्योम *seq,
				    माप_प्रकार len)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(icn->dev);

	वापस mipi_dsi_generic_ग_लिखो(dsi, seq, len);
पूर्ण

#घोषणा ICN6211_DSI(icn, seq...)				\
	अणु							\
		स्थिर u8 d[] = अणु seq पूर्ण;				\
		chipone_dsi_ग_लिखो(icn, d, ARRAY_SIZE(d));	\
	पूर्ण

अटल व्योम chipone_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा chipone *icn = bridge_to_chipone(bridge);
	काष्ठा drm_display_mode *mode = bridge_to_mode(bridge);

	ICN6211_DSI(icn, 0x7a, 0xc1);

	ICN6211_DSI(icn, HACTIVE_LI, mode->hdisplay & 0xff);

	ICN6211_DSI(icn, VACTIVE_LI, mode->vdisplay & 0xff);

	/**
	 * lsb nibble: 2nd nibble of hdisplay
	 * msb nibble: 2nd nibble of vdisplay
	 */
	ICN6211_DSI(icn, VACTIVE_HACTIVE_HI,
		    ((mode->hdisplay >> 8) & 0xf) |
		    (((mode->vdisplay >> 8) & 0xf) << 4));

	ICN6211_DSI(icn, HFP_LI, mode->hsync_start - mode->hdisplay);

	ICN6211_DSI(icn, HSYNC_LI, mode->hsync_end - mode->hsync_start);

	ICN6211_DSI(icn, HBP_LI, mode->htotal - mode->hsync_end);

	ICN6211_DSI(icn, HFP_HSW_HBP_HI, 0x00);

	ICN6211_DSI(icn, VFP, mode->vsync_start - mode->vdisplay);

	ICN6211_DSI(icn, VSYNC, mode->vsync_end - mode->vsync_start);

	ICN6211_DSI(icn, VBP, mode->vtotal - mode->vsync_end);

	/* dsi specअगरic sequence */
	ICN6211_DSI(icn, MIPI_DCS_SET_TEAR_OFF, 0x80);
	ICN6211_DSI(icn, MIPI_DCS_SET_ADDRESS_MODE, 0x28);
	ICN6211_DSI(icn, 0xb5, 0xa0);
	ICN6211_DSI(icn, 0x5c, 0xff);
	ICN6211_DSI(icn, MIPI_DCS_SET_COLUMN_ADDRESS, 0x01);
	ICN6211_DSI(icn, MIPI_DCS_GET_POWER_SAVE, 0x92);
	ICN6211_DSI(icn, 0x6b, 0x71);
	ICN6211_DSI(icn, 0x69, 0x2b);
	ICN6211_DSI(icn, MIPI_DCS_ENTER_SLEEP_MODE, 0x40);
	ICN6211_DSI(icn, MIPI_DCS_EXIT_SLEEP_MODE, 0x98);

	/* icn6211 specअगरic sequence */
	ICN6211_DSI(icn, 0xb6, 0x20);
	ICN6211_DSI(icn, 0x51, 0x20);
	ICN6211_DSI(icn, 0x09, 0x10);

	usleep_range(10000, 11000);
पूर्ण

अटल व्योम chipone_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा chipone *icn = bridge_to_chipone(bridge);
	पूर्णांक ret;

	अगर (icn->vdd1) अणु
		ret = regulator_enable(icn->vdd1);
		अगर (ret)
			DRM_DEV_ERROR(icn->dev,
				      "failed to enable VDD1 regulator: %d\n", ret);
	पूर्ण

	अगर (icn->vdd2) अणु
		ret = regulator_enable(icn->vdd2);
		अगर (ret)
			DRM_DEV_ERROR(icn->dev,
				      "failed to enable VDD2 regulator: %d\n", ret);
	पूर्ण

	अगर (icn->vdd3) अणु
		ret = regulator_enable(icn->vdd3);
		अगर (ret)
			DRM_DEV_ERROR(icn->dev,
				      "failed to enable VDD3 regulator: %d\n", ret);
	पूर्ण

	gpiod_set_value(icn->enable_gpio, 1);

	usleep_range(10000, 11000);
पूर्ण

अटल व्योम chipone_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा chipone *icn = bridge_to_chipone(bridge);

	अगर (icn->vdd1)
		regulator_disable(icn->vdd1);

	अगर (icn->vdd2)
		regulator_disable(icn->vdd2);

	अगर (icn->vdd3)
		regulator_disable(icn->vdd3);

	gpiod_set_value(icn->enable_gpio, 0);
पूर्ण

अटल पूर्णांक chipone_attach(काष्ठा drm_bridge *bridge, क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा chipone *icn = bridge_to_chipone(bridge);

	वापस drm_bridge_attach(bridge->encoder, icn->panel_bridge, bridge, flags);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs chipone_bridge_funcs = अणु
	.attach = chipone_attach,
	.post_disable = chipone_post_disable,
	.pre_enable = chipone_pre_enable,
	.enable = chipone_enable,
पूर्ण;

अटल पूर्णांक chipone_parse_dt(काष्ठा chipone *icn)
अणु
	काष्ठा device *dev = icn->dev;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	icn->vdd1 = devm_regulator_get_optional(dev, "vdd1");
	अगर (IS_ERR(icn->vdd1)) अणु
		ret = PTR_ERR(icn->vdd1);
		अगर (ret == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		icn->vdd1 = शून्य;
		DRM_DEV_DEBUG(dev, "failed to get VDD1 regulator: %d\n", ret);
	पूर्ण

	icn->vdd2 = devm_regulator_get_optional(dev, "vdd2");
	अगर (IS_ERR(icn->vdd2)) अणु
		ret = PTR_ERR(icn->vdd2);
		अगर (ret == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		icn->vdd2 = शून्य;
		DRM_DEV_DEBUG(dev, "failed to get VDD2 regulator: %d\n", ret);
	पूर्ण

	icn->vdd3 = devm_regulator_get_optional(dev, "vdd3");
	अगर (IS_ERR(icn->vdd3)) अणु
		ret = PTR_ERR(icn->vdd3);
		अगर (ret == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		icn->vdd3 = शून्य;
		DRM_DEV_DEBUG(dev, "failed to get VDD3 regulator: %d\n", ret);
	पूर्ण

	icn->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(icn->enable_gpio)) अणु
		DRM_DEV_ERROR(dev, "failed to get enable GPIO\n");
		वापस PTR_ERR(icn->enable_gpio);
	पूर्ण

	ret = drm_of_find_panel_or_bridge(dev->of_node, 1, 0, &panel, शून्य);
	अगर (ret)
		वापस ret;

	icn->panel_bridge = devm_drm_panel_bridge_add(dev, panel);
	अगर (IS_ERR(icn->panel_bridge))
		वापस PTR_ERR(icn->panel_bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक chipone_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा chipone *icn;
	पूर्णांक ret;

	icn = devm_kzalloc(dev, माप(काष्ठा chipone), GFP_KERNEL);
	अगर (!icn)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, icn);
	icn->dev = dev;

	ret = chipone_parse_dt(icn);
	अगर (ret)
		वापस ret;

	icn->bridge.funcs = &chipone_bridge_funcs;
	icn->bridge.type = DRM_MODE_CONNECTOR_DPI;
	icn->bridge.of_node = dev->of_node;

	drm_bridge_add(&icn->bridge);

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO_SYNC_PULSE;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		drm_bridge_हटाओ(&icn->bridge);
		dev_err(dev, "failed to attach dsi\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक chipone_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा chipone *icn = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_bridge_हटाओ(&icn->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id chipone_of_match[] = अणु
	अणु .compatible = "chipone,icn6211", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, chipone_of_match);

अटल काष्ठा mipi_dsi_driver chipone_driver = अणु
	.probe = chipone_probe,
	.हटाओ = chipone_हटाओ,
	.driver = अणु
		.name = "chipone-icn6211",
		.owner = THIS_MODULE,
		.of_match_table = chipone_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(chipone_driver);

MODULE_AUTHOR("Jagan Teki <jagan@amarulasolutions.com>");
MODULE_DESCRIPTION("Chipone ICN6211 MIPI-DSI to RGB Converter Bridge");
MODULE_LICENSE("GPL");
