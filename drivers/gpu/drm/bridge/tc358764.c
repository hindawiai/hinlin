<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Samsung Electronics Co., Ltd
 *
 * Authors:
 *	Andrzej Hajda <a.hajda@samsung.com>
 *	Maciej Purski <m.purski@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#घोषणा FLD_MASK(start, end)    (((1 << ((start) - (end) + 1)) - 1) << (end))
#घोषणा FLD_VAL(val, start, end) (((val) << (end)) & FLD_MASK(start, end))

/* PPI layer रेजिस्टरs */
#घोषणा PPI_STARTPPI		0x0104 /* START control bit */
#घोषणा PPI_LPTXTIMECNT		0x0114 /* LPTX timing संकेत */
#घोषणा PPI_LANEENABLE		0x0134 /* Enables each lane */
#घोषणा PPI_TX_RX_TA		0x013C /* BTA timing parameters */
#घोषणा PPI_D0S_CLRSIPOCOUNT	0x0164 /* Assertion समयr क्रम Lane 0 */
#घोषणा PPI_D1S_CLRSIPOCOUNT	0x0168 /* Assertion समयr क्रम Lane 1 */
#घोषणा PPI_D2S_CLRSIPOCOUNT	0x016C /* Assertion समयr क्रम Lane 2 */
#घोषणा PPI_D3S_CLRSIPOCOUNT	0x0170 /* Assertion समयr क्रम Lane 3 */
#घोषणा PPI_START_FUNCTION	1

/* DSI layer रेजिस्टरs */
#घोषणा DSI_STARTDSI		0x0204 /* START control bit of DSI-TX */
#घोषणा DSI_LANEENABLE		0x0210 /* Enables each lane */
#घोषणा DSI_RX_START		1

/* Video path रेजिस्टरs */
#घोषणा VP_CTRL			0x0450 /* Video Path Control */
#घोषणा VP_CTRL_MSF(v)		FLD_VAL(v, 0, 0) /* Magic square in RGB666 */
#घोषणा VP_CTRL_VTGEN(v)	FLD_VAL(v, 4, 4) /* Use chip घड़ी क्रम timing */
#घोषणा VP_CTRL_EVTMODE(v)	FLD_VAL(v, 5, 5) /* Event mode */
#घोषणा VP_CTRL_RGB888(v)	FLD_VAL(v, 8, 8) /* RGB888 mode */
#घोषणा VP_CTRL_VSDELAY(v)	FLD_VAL(v, 31, 20) /* VSYNC delay */
#घोषणा VP_CTRL_HSPOL		BIT(17) /* Polarity of HSYNC संकेत */
#घोषणा VP_CTRL_DEPOL		BIT(18) /* Polarity of DE संकेत */
#घोषणा VP_CTRL_VSPOL		BIT(19) /* Polarity of VSYNC संकेत */
#घोषणा VP_HTIM1		0x0454 /* Horizontal Timing Control 1 */
#घोषणा VP_HTIM1_HBP(v)		FLD_VAL(v, 24, 16)
#घोषणा VP_HTIM1_HSYNC(v)	FLD_VAL(v, 8, 0)
#घोषणा VP_HTIM2		0x0458 /* Horizontal Timing Control 2 */
#घोषणा VP_HTIM2_HFP(v)		FLD_VAL(v, 24, 16)
#घोषणा VP_HTIM2_HACT(v)	FLD_VAL(v, 10, 0)
#घोषणा VP_VTIM1		0x045C /* Vertical Timing Control 1 */
#घोषणा VP_VTIM1_VBP(v)		FLD_VAL(v, 23, 16)
#घोषणा VP_VTIM1_VSYNC(v)	FLD_VAL(v, 7, 0)
#घोषणा VP_VTIM2		0x0460 /* Vertical Timing Control 2 */
#घोषणा VP_VTIM2_VFP(v)		FLD_VAL(v, 23, 16)
#घोषणा VP_VTIM2_VACT(v)	FLD_VAL(v, 10, 0)
#घोषणा VP_VFUEN		0x0464 /* Video Frame Timing Update Enable */

/* LVDS रेजिस्टरs */
#घोषणा LV_MX0003		0x0480 /* Mux input bit 0 to 3 */
#घोषणा LV_MX0407		0x0484 /* Mux input bit 4 to 7 */
#घोषणा LV_MX0811		0x0488 /* Mux input bit 8 to 11 */
#घोषणा LV_MX1215		0x048C /* Mux input bit 12 to 15 */
#घोषणा LV_MX1619		0x0490 /* Mux input bit 16 to 19 */
#घोषणा LV_MX2023		0x0494 /* Mux input bit 20 to 23 */
#घोषणा LV_MX2427		0x0498 /* Mux input bit 24 to 27 */
#घोषणा LV_MX(b0, b1, b2, b3)	(FLD_VAL(b0, 4, 0) | FLD_VAL(b1, 12, 8) | \
				FLD_VAL(b2, 20, 16) | FLD_VAL(b3, 28, 24))

/* Input bit numbers used in mux रेजिस्टरs */
क्रमागत अणु
	LVI_R0,
	LVI_R1,
	LVI_R2,
	LVI_R3,
	LVI_R4,
	LVI_R5,
	LVI_R6,
	LVI_R7,
	LVI_G0,
	LVI_G1,
	LVI_G2,
	LVI_G3,
	LVI_G4,
	LVI_G5,
	LVI_G6,
	LVI_G7,
	LVI_B0,
	LVI_B1,
	LVI_B2,
	LVI_B3,
	LVI_B4,
	LVI_B5,
	LVI_B6,
	LVI_B7,
	LVI_HS,
	LVI_VS,
	LVI_DE,
	LVI_L0
पूर्ण;

#घोषणा LV_CFG			0x049C /* LVDS Configuration */
#घोषणा LV_PHY0			0x04A0 /* LVDS PHY 0 */
#घोषणा LV_PHY0_RST(v)		FLD_VAL(v, 22, 22) /* PHY reset */
#घोषणा LV_PHY0_IS(v)		FLD_VAL(v, 15, 14)
#घोषणा LV_PHY0_ND(v)		FLD_VAL(v, 4, 0) /* Frequency range select */
#घोषणा LV_PHY0_PRBS_ON(v)	FLD_VAL(v, 20, 16) /* Clock/Data Flag pins */

/* System रेजिस्टरs */
#घोषणा SYS_RST			0x0504 /* System Reset */
#घोषणा SYS_ID			0x0580 /* System ID */

#घोषणा SYS_RST_I2CS		BIT(0) /* Reset I2C-Slave controller */
#घोषणा SYS_RST_I2CM		BIT(1) /* Reset I2C-Master controller */
#घोषणा SYS_RST_LCD		BIT(2) /* Reset LCD controller */
#घोषणा SYS_RST_BM		BIT(3) /* Reset Bus Management controller */
#घोषणा SYS_RST_DSIRX		BIT(4) /* Reset DSI-RX and App controller */
#घोषणा SYS_RST_REG		BIT(5) /* Reset Register module */

#घोषणा LPX_PERIOD		2
#घोषणा TTA_SURE		3
#घोषणा TTA_GET			0x20000

/* Lane enable PPI and DSI रेजिस्टर bits */
#घोषणा LANEENABLE_CLEN		BIT(0)
#घोषणा LANEENABLE_L0EN		BIT(1)
#घोषणा LANEENABLE_L1EN		BIT(2)
#घोषणा LANEENABLE_L2EN		BIT(3)
#घोषणा LANEENABLE_L3EN		BIT(4)

/* LVCFG fields */
#घोषणा LV_CFG_LVEN		BIT(0)
#घोषणा LV_CFG_LVDLINK		BIT(1)
#घोषणा LV_CFG_CLKPOL1		BIT(2)
#घोषणा LV_CFG_CLKPOL2		BIT(3)

अटल स्थिर अक्षर * स्थिर tc358764_supplies[] = अणु
	"vddc", "vddio", "vddlvds"
पूर्ण;

काष्ठा tc358764 अणु
	काष्ठा device *dev;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(tc358764_supplies)];
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा drm_panel *panel;
	पूर्णांक error;
पूर्ण;

अटल पूर्णांक tc358764_clear_error(काष्ठा tc358764 *ctx)
अणु
	पूर्णांक ret = ctx->error;

	ctx->error = 0;
	वापस ret;
पूर्ण

अटल व्योम tc358764_पढ़ो(काष्ठा tc358764 *ctx, u16 addr, u32 *val)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	sमाप_प्रकार ret;

	अगर (ctx->error)
		वापस;

	cpu_to_le16s(&addr);
	ret = mipi_dsi_generic_पढ़ो(dsi, &addr, माप(addr), val, माप(*val));
	अगर (ret >= 0)
		le32_to_cpus(val);

	dev_dbg(ctx->dev, "read: %d, addr: %d\n", addr, *val);
पूर्ण

अटल व्योम tc358764_ग_लिखो(काष्ठा tc358764 *ctx, u16 addr, u32 val)
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

अटल अंतरभूत काष्ठा tc358764 *bridge_to_tc358764(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा tc358764, bridge);
पूर्ण

अटल अंतरभूत
काष्ठा tc358764 *connector_to_tc358764(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा tc358764, connector);
पूर्ण

अटल पूर्णांक tc358764_init(काष्ठा tc358764 *ctx)
अणु
	u32 v = 0;

	tc358764_पढ़ो(ctx, SYS_ID, &v);
	अगर (ctx->error)
		वापस tc358764_clear_error(ctx);
	dev_info(ctx->dev, "ID: %#x\n", v);

	/* configure PPI counters */
	tc358764_ग_लिखो(ctx, PPI_TX_RX_TA, TTA_GET | TTA_SURE);
	tc358764_ग_लिखो(ctx, PPI_LPTXTIMECNT, LPX_PERIOD);
	tc358764_ग_लिखो(ctx, PPI_D0S_CLRSIPOCOUNT, 5);
	tc358764_ग_लिखो(ctx, PPI_D1S_CLRSIPOCOUNT, 5);
	tc358764_ग_लिखो(ctx, PPI_D2S_CLRSIPOCOUNT, 5);
	tc358764_ग_लिखो(ctx, PPI_D3S_CLRSIPOCOUNT, 5);

	/* enable four data lanes and घड़ी lane */
	tc358764_ग_लिखो(ctx, PPI_LANEENABLE, LANEENABLE_L3EN | LANEENABLE_L2EN |
		       LANEENABLE_L1EN | LANEENABLE_L0EN | LANEENABLE_CLEN);
	tc358764_ग_लिखो(ctx, DSI_LANEENABLE, LANEENABLE_L3EN | LANEENABLE_L2EN |
		       LANEENABLE_L1EN | LANEENABLE_L0EN | LANEENABLE_CLEN);

	/* start */
	tc358764_ग_लिखो(ctx, PPI_STARTPPI, PPI_START_FUNCTION);
	tc358764_ग_लिखो(ctx, DSI_STARTDSI, DSI_RX_START);

	/* configure video path */
	tc358764_ग_लिखो(ctx, VP_CTRL, VP_CTRL_VSDELAY(15) | VP_CTRL_RGB888(1) |
		       VP_CTRL_EVTMODE(1) | VP_CTRL_HSPOL | VP_CTRL_VSPOL);

	/* reset PHY */
	tc358764_ग_लिखो(ctx, LV_PHY0, LV_PHY0_RST(1) |
		       LV_PHY0_PRBS_ON(4) | LV_PHY0_IS(2) | LV_PHY0_ND(6));
	tc358764_ग_लिखो(ctx, LV_PHY0, LV_PHY0_PRBS_ON(4) | LV_PHY0_IS(2) |
		       LV_PHY0_ND(6));

	/* reset bridge */
	tc358764_ग_लिखो(ctx, SYS_RST, SYS_RST_LCD);

	/* set bit order */
	tc358764_ग_लिखो(ctx, LV_MX0003, LV_MX(LVI_R0, LVI_R1, LVI_R2, LVI_R3));
	tc358764_ग_लिखो(ctx, LV_MX0407, LV_MX(LVI_R4, LVI_R7, LVI_R5, LVI_G0));
	tc358764_ग_लिखो(ctx, LV_MX0811, LV_MX(LVI_G1, LVI_G2, LVI_G6, LVI_G7));
	tc358764_ग_लिखो(ctx, LV_MX1215, LV_MX(LVI_G3, LVI_G4, LVI_G5, LVI_B0));
	tc358764_ग_लिखो(ctx, LV_MX1619, LV_MX(LVI_B6, LVI_B7, LVI_B1, LVI_B2));
	tc358764_ग_लिखो(ctx, LV_MX2023, LV_MX(LVI_B3, LVI_B4, LVI_B5, LVI_L0));
	tc358764_ग_लिखो(ctx, LV_MX2427, LV_MX(LVI_HS, LVI_VS, LVI_DE, LVI_R6));
	tc358764_ग_लिखो(ctx, LV_CFG, LV_CFG_CLKPOL2 | LV_CFG_CLKPOL1 |
		       LV_CFG_LVEN);

	वापस tc358764_clear_error(ctx);
पूर्ण

अटल व्योम tc358764_reset(काष्ठा tc358764 *ctx)
अणु
	gpiod_set_value(ctx->gpio_reset, 1);
	usleep_range(1000, 2000);
	gpiod_set_value(ctx->gpio_reset, 0);
	usleep_range(1000, 2000);
पूर्ण

अटल पूर्णांक tc358764_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा tc358764 *ctx = connector_to_tc358764(connector);

	वापस drm_panel_get_modes(ctx->panel, connector);
पूर्ण

अटल स्थिर
काष्ठा drm_connector_helper_funcs tc358764_connector_helper_funcs = अणु
	.get_modes = tc358764_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs tc358764_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल व्योम tc358764_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358764 *ctx = bridge_to_tc358764(bridge);
	पूर्णांक ret = drm_panel_disable(bridge_to_tc358764(bridge)->panel);

	अगर (ret < 0)
		dev_err(ctx->dev, "error disabling panel (%d)\n", ret);
पूर्ण

अटल व्योम tc358764_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358764 *ctx = bridge_to_tc358764(bridge);
	पूर्णांक ret;

	ret = drm_panel_unprepare(ctx->panel);
	अगर (ret < 0)
		dev_err(ctx->dev, "error unpreparing panel (%d)\n", ret);
	tc358764_reset(ctx);
	usleep_range(10000, 15000);
	ret = regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0)
		dev_err(ctx->dev, "error disabling regulators (%d)\n", ret);
पूर्ण

अटल व्योम tc358764_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358764 *ctx = bridge_to_tc358764(bridge);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0)
		dev_err(ctx->dev, "error enabling regulators (%d)\n", ret);
	usleep_range(10000, 15000);
	tc358764_reset(ctx);
	ret = tc358764_init(ctx);
	अगर (ret < 0)
		dev_err(ctx->dev, "error initializing bridge (%d)\n", ret);
	ret = drm_panel_prepare(ctx->panel);
	अगर (ret < 0)
		dev_err(ctx->dev, "error preparing panel (%d)\n", ret);
पूर्ण

अटल व्योम tc358764_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358764 *ctx = bridge_to_tc358764(bridge);
	पूर्णांक ret = drm_panel_enable(ctx->panel);

	अगर (ret < 0)
		dev_err(ctx->dev, "error enabling panel (%d)\n", ret);
पूर्ण

अटल पूर्णांक tc358764_attach(काष्ठा drm_bridge *bridge,
			   क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा tc358764 *ctx = bridge_to_tc358764(bridge);
	काष्ठा drm_device *drm = bridge->dev;
	पूर्णांक ret;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR) अणु
		DRM_ERROR("Fix bridge driver to make connector optional!");
		वापस -EINVAL;
	पूर्ण

	ctx->connector.polled = DRM_CONNECTOR_POLL_HPD;
	ret = drm_connector_init(drm, &ctx->connector,
				 &tc358764_connector_funcs,
				 DRM_MODE_CONNECTOR_LVDS);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector\n");
		वापस ret;
	पूर्ण

	drm_connector_helper_add(&ctx->connector,
				 &tc358764_connector_helper_funcs);
	drm_connector_attach_encoder(&ctx->connector, bridge->encoder);
	ctx->connector.funcs->reset(&ctx->connector);
	drm_connector_रेजिस्टर(&ctx->connector);

	वापस 0;
पूर्ण

अटल व्योम tc358764_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358764 *ctx = bridge_to_tc358764(bridge);

	drm_connector_unरेजिस्टर(&ctx->connector);
	ctx->panel = शून्य;
	drm_connector_put(&ctx->connector);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs tc358764_bridge_funcs = अणु
	.disable = tc358764_disable,
	.post_disable = tc358764_post_disable,
	.enable = tc358764_enable,
	.pre_enable = tc358764_pre_enable,
	.attach = tc358764_attach,
	.detach = tc358764_detach,
पूर्ण;

अटल पूर्णांक tc358764_parse_dt(काष्ठा tc358764 *ctx)
अणु
	काष्ठा device *dev = ctx->dev;
	पूर्णांक ret;

	ctx->gpio_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->gpio_reset)) अणु
		dev_err(dev, "no reset GPIO pin provided\n");
		वापस PTR_ERR(ctx->gpio_reset);
	पूर्ण

	ret = drm_of_find_panel_or_bridge(ctx->dev->of_node, 1, 0, &ctx->panel,
					  शून्य);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(dev, "cannot find panel (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tc358764_configure_regulators(काष्ठा tc358764 *ctx)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->supplies); ++i)
		ctx->supplies[i].supply = tc358764_supplies[i];

	ret = devm_regulator_bulk_get(ctx->dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	अगर (ret < 0)
		dev_err(ctx->dev, "failed to get regulators: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tc358764_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा tc358764 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(काष्ठा tc358764), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST
		| MIPI_DSI_MODE_VIDEO_AUTO_VERT | MIPI_DSI_MODE_LPM;

	ret = tc358764_parse_dt(ctx);
	अगर (ret < 0)
		वापस ret;

	ret = tc358764_configure_regulators(ctx);
	अगर (ret < 0)
		वापस ret;

	ctx->bridge.funcs = &tc358764_bridge_funcs;
	ctx->bridge.of_node = dev->of_node;

	drm_bridge_add(&ctx->bridge);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		drm_bridge_हटाओ(&ctx->bridge);
		dev_err(dev, "failed to attach dsi\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tc358764_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा tc358764 *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_bridge_हटाओ(&ctx->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tc358764_of_match[] = अणु
	अणु .compatible = "toshiba,tc358764" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tc358764_of_match);

अटल काष्ठा mipi_dsi_driver tc358764_driver = अणु
	.probe = tc358764_probe,
	.हटाओ = tc358764_हटाओ,
	.driver = अणु
		.name = "tc358764",
		.owner = THIS_MODULE,
		.of_match_table = tc358764_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(tc358764_driver);

MODULE_AUTHOR("Andrzej Hajda <a.hajda@samsung.com>");
MODULE_AUTHOR("Maciej Purski <m.purski@samsung.com>");
MODULE_DESCRIPTION("MIPI-DSI based Driver for TC358764 DSI/LVDS Bridge");
MODULE_LICENSE("GPL v2");
