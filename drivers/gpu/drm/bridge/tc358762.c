<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Marek Vasut <marex@denx.de>
 *
 * Based on tc358764.c by
 *  Andrzej Hajda <a.hajda@samsung.com>
 *  Maciej Purski <m.purski@samsung.com>
 *
 * Based on rpi_touchscreen.c by
 *  Eric Anholt <eric@anholt.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

/* PPI layer रेजिस्टरs */
#घोषणा PPI_STARTPPI		0x0104 /* START control bit */
#घोषणा PPI_LPTXTIMECNT		0x0114 /* LPTX timing संकेत */
#घोषणा PPI_D0S_ATMR		0x0144
#घोषणा PPI_D1S_ATMR		0x0148
#घोषणा PPI_D0S_CLRSIPOCOUNT	0x0164 /* Assertion समयr क्रम Lane 0 */
#घोषणा PPI_D1S_CLRSIPOCOUNT	0x0168 /* Assertion समयr क्रम Lane 1 */
#घोषणा PPI_START_FUNCTION	1

/* DSI layer रेजिस्टरs */
#घोषणा DSI_STARTDSI		0x0204 /* START control bit of DSI-TX */
#घोषणा DSI_LANEENABLE		0x0210 /* Enables each lane */
#घोषणा DSI_RX_START		1

/* LCDC/DPI Host Registers */
#घोषणा LCDCTRL			0x0420

/* SPI Master Registers */
#घोषणा SPICMR			0x0450
#घोषणा SPITCR			0x0454

/* System Controller Registers */
#घोषणा SYSCTRL			0x0464

/* System रेजिस्टरs */
#घोषणा LPX_PERIOD		3

/* Lane enable PPI and DSI रेजिस्टर bits */
#घोषणा LANEENABLE_CLEN		BIT(0)
#घोषणा LANEENABLE_L0EN		BIT(1)
#घोषणा LANEENABLE_L1EN		BIT(2)

काष्ठा tc358762 अणु
	काष्ठा device *dev;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;
	काष्ठा regulator *regulator;
	काष्ठा drm_bridge *panel_bridge;
	bool pre_enabled;
	पूर्णांक error;
पूर्ण;

अटल पूर्णांक tc358762_clear_error(काष्ठा tc358762 *ctx)
अणु
	पूर्णांक ret = ctx->error;

	ctx->error = 0;
	वापस ret;
पूर्ण

अटल व्योम tc358762_ग_लिखो(काष्ठा tc358762 *ctx, u16 addr, u32 val)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	sमाप_प्रकार ret;
	u8 data[6];

	अगर (ctx->error)
		वापस;

	data[0] = addr;
	data[1] = addr >> 8;
	data[2] = val;
	data[3] = val >> 8;
	data[4] = val >> 16;
	data[5] = val >> 24;

	ret = mipi_dsi_generic_ग_लिखो(dsi, data, माप(data));
	अगर (ret < 0)
		ctx->error = ret;
पूर्ण

अटल अंतरभूत काष्ठा tc358762 *bridge_to_tc358762(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा tc358762, bridge);
पूर्ण

अटल पूर्णांक tc358762_init(काष्ठा tc358762 *ctx)
अणु
	tc358762_ग_लिखो(ctx, DSI_LANEENABLE,
		       LANEENABLE_L0EN | LANEENABLE_CLEN);
	tc358762_ग_लिखो(ctx, PPI_D0S_CLRSIPOCOUNT, 5);
	tc358762_ग_लिखो(ctx, PPI_D1S_CLRSIPOCOUNT, 5);
	tc358762_ग_लिखो(ctx, PPI_D0S_ATMR, 0);
	tc358762_ग_लिखो(ctx, PPI_D1S_ATMR, 0);
	tc358762_ग_लिखो(ctx, PPI_LPTXTIMECNT, LPX_PERIOD);

	tc358762_ग_लिखो(ctx, SPICMR, 0x00);
	tc358762_ग_लिखो(ctx, LCDCTRL, 0x00100150);
	tc358762_ग_लिखो(ctx, SYSCTRL, 0x040f);
	msleep(100);

	tc358762_ग_लिखो(ctx, PPI_STARTPPI, PPI_START_FUNCTION);
	tc358762_ग_लिखो(ctx, DSI_STARTDSI, DSI_RX_START);

	msleep(100);

	वापस tc358762_clear_error(ctx);
पूर्ण

अटल व्योम tc358762_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358762 *ctx = bridge_to_tc358762(bridge);
	पूर्णांक ret;

	/*
	 * The post_disable hook might be called multiple बार.
	 * We want to aव्योम regulator imbalance below.
	 */
	अगर (!ctx->pre_enabled)
		वापस;

	ctx->pre_enabled = false;

	ret = regulator_disable(ctx->regulator);
	अगर (ret < 0)
		dev_err(ctx->dev, "error disabling regulators (%d)\n", ret);
पूर्ण

अटल व्योम tc358762_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358762 *ctx = bridge_to_tc358762(bridge);
	पूर्णांक ret;

	ret = regulator_enable(ctx->regulator);
	अगर (ret < 0)
		dev_err(ctx->dev, "error enabling regulators (%d)\n", ret);

	ret = tc358762_init(ctx);
	अगर (ret < 0)
		dev_err(ctx->dev, "error initializing bridge (%d)\n", ret);

	ctx->pre_enabled = true;
पूर्ण

अटल पूर्णांक tc358762_attach(काष्ठा drm_bridge *bridge,
			   क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा tc358762 *ctx = bridge_to_tc358762(bridge);

	वापस drm_bridge_attach(bridge->encoder, ctx->panel_bridge,
				 bridge, flags);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs tc358762_bridge_funcs = अणु
	.post_disable = tc358762_post_disable,
	.pre_enable = tc358762_pre_enable,
	.attach = tc358762_attach,
पूर्ण;

अटल पूर्णांक tc358762_parse_dt(काष्ठा tc358762 *ctx)
अणु
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा device *dev = ctx->dev;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	ret = drm_of_find_panel_or_bridge(dev->of_node, 1, 0, &panel, शून्य);
	अगर (ret)
		वापस ret;

	panel_bridge = devm_drm_panel_bridge_add(dev, panel);

	अगर (IS_ERR(panel_bridge))
		वापस PTR_ERR(panel_bridge);

	ctx->panel_bridge = panel_bridge;

	वापस 0;
पूर्ण

अटल पूर्णांक tc358762_configure_regulators(काष्ठा tc358762 *ctx)
अणु
	ctx->regulator = devm_regulator_get(ctx->dev, "vddc");
	अगर (IS_ERR(ctx->regulator))
		वापस PTR_ERR(ctx->regulator);

	वापस 0;
पूर्ण

अटल पूर्णांक tc358762_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा tc358762 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(काष्ठा tc358762), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;
	ctx->pre_enabled = false;

	/* TODO: Find out how to get dual-lane mode working */
	dsi->lanes = 1;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			  MIPI_DSI_MODE_LPM;

	ret = tc358762_parse_dt(ctx);
	अगर (ret < 0)
		वापस ret;

	ret = tc358762_configure_regulators(ctx);
	अगर (ret < 0)
		वापस ret;

	ctx->bridge.funcs = &tc358762_bridge_funcs;
	ctx->bridge.type = DRM_MODE_CONNECTOR_DPI;
	ctx->bridge.of_node = dev->of_node;

	drm_bridge_add(&ctx->bridge);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		drm_bridge_हटाओ(&ctx->bridge);
		dev_err(dev, "failed to attach dsi\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tc358762_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा tc358762 *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_bridge_हटाओ(&ctx->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tc358762_of_match[] = अणु
	अणु .compatible = "toshiba,tc358762" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tc358762_of_match);

अटल काष्ठा mipi_dsi_driver tc358762_driver = अणु
	.probe = tc358762_probe,
	.हटाओ = tc358762_हटाओ,
	.driver = अणु
		.name = "tc358762",
		.of_match_table = tc358762_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(tc358762_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("MIPI-DSI based Driver for TC358762 DSI/DPI Bridge");
MODULE_LICENSE("GPL v2");
