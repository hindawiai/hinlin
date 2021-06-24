<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i.MX drm driver - LVDS display bridge
 *
 * Copyright (C) 2012 Sascha Hauer, Pengutronix
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regmap.h>
#समावेश <linux/videodev2.h>

#समावेश <video/of_display_timing.h>
#समावेश <video/of_videomode.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "imx-drm.h"

#घोषणा DRIVER_NAME "imx-ldb"

#घोषणा LDB_CH0_MODE_EN_TO_DI0		(1 << 0)
#घोषणा LDB_CH0_MODE_EN_TO_DI1		(3 << 0)
#घोषणा LDB_CH0_MODE_EN_MASK		(3 << 0)
#घोषणा LDB_CH1_MODE_EN_TO_DI0		(1 << 2)
#घोषणा LDB_CH1_MODE_EN_TO_DI1		(3 << 2)
#घोषणा LDB_CH1_MODE_EN_MASK		(3 << 2)
#घोषणा LDB_SPLIT_MODE_EN		(1 << 4)
#घोषणा LDB_DATA_WIDTH_CH0_24		(1 << 5)
#घोषणा LDB_BIT_MAP_CH0_JEIDA		(1 << 6)
#घोषणा LDB_DATA_WIDTH_CH1_24		(1 << 7)
#घोषणा LDB_BIT_MAP_CH1_JEIDA		(1 << 8)
#घोषणा LDB_DI0_VS_POL_ACT_LOW		(1 << 9)
#घोषणा LDB_DI1_VS_POL_ACT_LOW		(1 << 10)
#घोषणा LDB_BGREF_RMODE_INT		(1 << 15)

काष्ठा imx_ldb_channel;

काष्ठा imx_ldb_encoder अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा imx_ldb_channel *channel;
पूर्ण;

काष्ठा imx_ldb;

काष्ठा imx_ldb_channel अणु
	काष्ठा imx_ldb *ldb;

	/* Defines what is connected to the ldb, only one at a समय */
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;

	काष्ठा device_node *child;
	काष्ठा i2c_adapter *ddc;
	पूर्णांक chno;
	व्योम *edid;
	काष्ठा drm_display_mode mode;
	पूर्णांक mode_valid;
	u32 bus_क्रमmat;
	u32 bus_flags;
पूर्ण;

अटल अंतरभूत काष्ठा imx_ldb_channel *con_to_imx_ldb_ch(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा imx_ldb_encoder, connector)->channel;
पूर्ण

अटल अंतरभूत काष्ठा imx_ldb_channel *enc_to_imx_ldb_ch(काष्ठा drm_encoder *e)
अणु
	वापस container_of(e, काष्ठा imx_ldb_encoder, encoder)->channel;
पूर्ण

काष्ठा bus_mux अणु
	पूर्णांक reg;
	पूर्णांक shअगरt;
	पूर्णांक mask;
पूर्ण;

काष्ठा imx_ldb अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा imx_ldb_channel channel[2];
	काष्ठा clk *clk[2]; /* our own घड़ी */
	काष्ठा clk *clk_sel[4]; /* parent of display घड़ी */
	काष्ठा clk *clk_parent[4]; /* original parent of clk_sel */
	काष्ठा clk *clk_pll[2]; /* upstream घड़ी we can adjust */
	u32 ldb_ctrl;
	स्थिर काष्ठा bus_mux *lvds_mux;
पूर्ण;

अटल व्योम imx_ldb_ch_set_bus_क्रमmat(काष्ठा imx_ldb_channel *imx_ldb_ch,
				      u32 bus_क्रमmat)
अणु
	काष्ठा imx_ldb *ldb = imx_ldb_ch->ldb;
	पूर्णांक dual = ldb->ldb_ctrl & LDB_SPLIT_MODE_EN;

	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
		अगर (imx_ldb_ch->chno == 0 || dual)
			ldb->ldb_ctrl |= LDB_DATA_WIDTH_CH0_24;
		अगर (imx_ldb_ch->chno == 1 || dual)
			ldb->ldb_ctrl |= LDB_DATA_WIDTH_CH1_24;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
		अगर (imx_ldb_ch->chno == 0 || dual)
			ldb->ldb_ctrl |= LDB_DATA_WIDTH_CH0_24 |
					 LDB_BIT_MAP_CH0_JEIDA;
		अगर (imx_ldb_ch->chno == 1 || dual)
			ldb->ldb_ctrl |= LDB_DATA_WIDTH_CH1_24 |
					 LDB_BIT_MAP_CH1_JEIDA;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक imx_ldb_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा imx_ldb_channel *imx_ldb_ch = con_to_imx_ldb_ch(connector);
	पूर्णांक num_modes;

	num_modes = drm_panel_get_modes(imx_ldb_ch->panel, connector);
	अगर (num_modes > 0)
		वापस num_modes;

	अगर (!imx_ldb_ch->edid && imx_ldb_ch->ddc)
		imx_ldb_ch->edid = drm_get_edid(connector, imx_ldb_ch->ddc);

	अगर (imx_ldb_ch->edid) अणु
		drm_connector_update_edid_property(connector,
							imx_ldb_ch->edid);
		num_modes = drm_add_edid_modes(connector, imx_ldb_ch->edid);
	पूर्ण

	अगर (imx_ldb_ch->mode_valid) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_create(connector->dev);
		अगर (!mode)
			वापस -EINVAL;
		drm_mode_copy(mode, &imx_ldb_ch->mode);
		mode->type |= DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, mode);
		num_modes++;
	पूर्ण

	वापस num_modes;
पूर्ण

अटल व्योम imx_ldb_set_घड़ी(काष्ठा imx_ldb *ldb, पूर्णांक mux, पूर्णांक chno,
		अचिन्हित दीर्घ serial_clk, अचिन्हित दीर्घ di_clk)
अणु
	पूर्णांक ret;

	dev_dbg(ldb->dev, "%s: now: %ld want: %ld\n", __func__,
			clk_get_rate(ldb->clk_pll[chno]), serial_clk);
	clk_set_rate(ldb->clk_pll[chno], serial_clk);

	dev_dbg(ldb->dev, "%s after: %ld\n", __func__,
			clk_get_rate(ldb->clk_pll[chno]));

	dev_dbg(ldb->dev, "%s: now: %ld want: %ld\n", __func__,
			clk_get_rate(ldb->clk[chno]),
			(दीर्घ पूर्णांक)di_clk);
	clk_set_rate(ldb->clk[chno], di_clk);

	dev_dbg(ldb->dev, "%s after: %ld\n", __func__,
			clk_get_rate(ldb->clk[chno]));

	/* set display घड़ी mux to LDB input घड़ी */
	ret = clk_set_parent(ldb->clk_sel[mux], ldb->clk[chno]);
	अगर (ret)
		dev_err(ldb->dev,
			"unable to set di%d parent clock to ldb_di%d\n", mux,
			chno);
पूर्ण

अटल व्योम imx_ldb_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा imx_ldb_channel *imx_ldb_ch = enc_to_imx_ldb_ch(encoder);
	काष्ठा imx_ldb *ldb = imx_ldb_ch->ldb;
	पूर्णांक dual = ldb->ldb_ctrl & LDB_SPLIT_MODE_EN;
	पूर्णांक mux = drm_of_encoder_active_port_id(imx_ldb_ch->child, encoder);

	अगर (mux < 0 || mux >= ARRAY_SIZE(ldb->clk_sel)) अणु
		dev_warn(ldb->dev, "%s: invalid mux %d\n", __func__, mux);
		वापस;
	पूर्ण

	drm_panel_prepare(imx_ldb_ch->panel);

	अगर (dual) अणु
		clk_set_parent(ldb->clk_sel[mux], ldb->clk[0]);
		clk_set_parent(ldb->clk_sel[mux], ldb->clk[1]);

		clk_prepare_enable(ldb->clk[0]);
		clk_prepare_enable(ldb->clk[1]);
	पूर्ण अन्यथा अणु
		clk_set_parent(ldb->clk_sel[mux], ldb->clk[imx_ldb_ch->chno]);
	पूर्ण

	अगर (imx_ldb_ch == &ldb->channel[0] || dual) अणु
		ldb->ldb_ctrl &= ~LDB_CH0_MODE_EN_MASK;
		अगर (mux == 0 || ldb->lvds_mux)
			ldb->ldb_ctrl |= LDB_CH0_MODE_EN_TO_DI0;
		अन्यथा अगर (mux == 1)
			ldb->ldb_ctrl |= LDB_CH0_MODE_EN_TO_DI1;
	पूर्ण
	अगर (imx_ldb_ch == &ldb->channel[1] || dual) अणु
		ldb->ldb_ctrl &= ~LDB_CH1_MODE_EN_MASK;
		अगर (mux == 1 || ldb->lvds_mux)
			ldb->ldb_ctrl |= LDB_CH1_MODE_EN_TO_DI1;
		अन्यथा अगर (mux == 0)
			ldb->ldb_ctrl |= LDB_CH1_MODE_EN_TO_DI0;
	पूर्ण

	अगर (ldb->lvds_mux) अणु
		स्थिर काष्ठा bus_mux *lvds_mux = शून्य;

		अगर (imx_ldb_ch == &ldb->channel[0])
			lvds_mux = &ldb->lvds_mux[0];
		अन्यथा अगर (imx_ldb_ch == &ldb->channel[1])
			lvds_mux = &ldb->lvds_mux[1];

		regmap_update_bits(ldb->regmap, lvds_mux->reg, lvds_mux->mask,
				   mux << lvds_mux->shअगरt);
	पूर्ण

	regmap_ग_लिखो(ldb->regmap, IOMUXC_GPR2, ldb->ldb_ctrl);

	drm_panel_enable(imx_ldb_ch->panel);
पूर्ण

अटल व्योम
imx_ldb_encoder_atomic_mode_set(काष्ठा drm_encoder *encoder,
				काष्ठा drm_crtc_state *crtc_state,
				काष्ठा drm_connector_state *connector_state)
अणु
	काष्ठा imx_ldb_channel *imx_ldb_ch = enc_to_imx_ldb_ch(encoder);
	काष्ठा drm_display_mode *mode = &crtc_state->adjusted_mode;
	काष्ठा imx_ldb *ldb = imx_ldb_ch->ldb;
	पूर्णांक dual = ldb->ldb_ctrl & LDB_SPLIT_MODE_EN;
	अचिन्हित दीर्घ serial_clk;
	अचिन्हित दीर्घ di_clk = mode->घड़ी * 1000;
	पूर्णांक mux = drm_of_encoder_active_port_id(imx_ldb_ch->child, encoder);
	u32 bus_क्रमmat = imx_ldb_ch->bus_क्रमmat;

	अगर (mux < 0 || mux >= ARRAY_SIZE(ldb->clk_sel)) अणु
		dev_warn(ldb->dev, "%s: invalid mux %d\n", __func__, mux);
		वापस;
	पूर्ण

	अगर (mode->घड़ी > 170000) अणु
		dev_warn(ldb->dev,
			 "%s: mode exceeds 170 MHz pixel clock\n", __func__);
	पूर्ण
	अगर (mode->घड़ी > 85000 && !dual) अणु
		dev_warn(ldb->dev,
			 "%s: mode exceeds 85 MHz pixel clock\n", __func__);
	पूर्ण

	अगर (dual) अणु
		serial_clk = 3500UL * mode->घड़ी;
		imx_ldb_set_घड़ी(ldb, mux, 0, serial_clk, di_clk);
		imx_ldb_set_घड़ी(ldb, mux, 1, serial_clk, di_clk);
	पूर्ण अन्यथा अणु
		serial_clk = 7000UL * mode->घड़ी;
		imx_ldb_set_घड़ी(ldb, mux, imx_ldb_ch->chno, serial_clk,
				  di_clk);
	पूर्ण

	/* FIXME - assumes straight connections DI0 --> CH0, DI1 --> CH1 */
	अगर (imx_ldb_ch == &ldb->channel[0] || dual) अणु
		अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
			ldb->ldb_ctrl |= LDB_DI0_VS_POL_ACT_LOW;
		अन्यथा अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
			ldb->ldb_ctrl &= ~LDB_DI0_VS_POL_ACT_LOW;
	पूर्ण
	अगर (imx_ldb_ch == &ldb->channel[1] || dual) अणु
		अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
			ldb->ldb_ctrl |= LDB_DI1_VS_POL_ACT_LOW;
		अन्यथा अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
			ldb->ldb_ctrl &= ~LDB_DI1_VS_POL_ACT_LOW;
	पूर्ण

	अगर (!bus_क्रमmat) अणु
		काष्ठा drm_connector *connector = connector_state->connector;
		काष्ठा drm_display_info *di = &connector->display_info;

		अगर (di->num_bus_क्रमmats)
			bus_क्रमmat = di->bus_क्रमmats[0];
	पूर्ण
	imx_ldb_ch_set_bus_क्रमmat(imx_ldb_ch, bus_क्रमmat);
पूर्ण

अटल व्योम imx_ldb_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा imx_ldb_channel *imx_ldb_ch = enc_to_imx_ldb_ch(encoder);
	काष्ठा imx_ldb *ldb = imx_ldb_ch->ldb;
	पूर्णांक dual = ldb->ldb_ctrl & LDB_SPLIT_MODE_EN;
	पूर्णांक mux, ret;

	drm_panel_disable(imx_ldb_ch->panel);

	अगर (imx_ldb_ch == &ldb->channel[0] || dual)
		ldb->ldb_ctrl &= ~LDB_CH0_MODE_EN_MASK;
	अगर (imx_ldb_ch == &ldb->channel[1] || dual)
		ldb->ldb_ctrl &= ~LDB_CH1_MODE_EN_MASK;

	regmap_ग_लिखो(ldb->regmap, IOMUXC_GPR2, ldb->ldb_ctrl);

	अगर (dual) अणु
		clk_disable_unprepare(ldb->clk[0]);
		clk_disable_unprepare(ldb->clk[1]);
	पूर्ण

	अगर (ldb->lvds_mux) अणु
		स्थिर काष्ठा bus_mux *lvds_mux = शून्य;

		अगर (imx_ldb_ch == &ldb->channel[0])
			lvds_mux = &ldb->lvds_mux[0];
		अन्यथा अगर (imx_ldb_ch == &ldb->channel[1])
			lvds_mux = &ldb->lvds_mux[1];

		regmap_पढ़ो(ldb->regmap, lvds_mux->reg, &mux);
		mux &= lvds_mux->mask;
		mux >>= lvds_mux->shअगरt;
	पूर्ण अन्यथा अणु
		mux = (imx_ldb_ch == &ldb->channel[0]) ? 0 : 1;
	पूर्ण

	/* set display घड़ी mux back to original input घड़ी */
	ret = clk_set_parent(ldb->clk_sel[mux], ldb->clk_parent[mux]);
	अगर (ret)
		dev_err(ldb->dev,
			"unable to set di%d parent clock to original parent\n",
			mux);

	drm_panel_unprepare(imx_ldb_ch->panel);
पूर्ण

अटल पूर्णांक imx_ldb_encoder_atomic_check(काष्ठा drm_encoder *encoder,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा imx_crtc_state *imx_crtc_state = to_imx_crtc_state(crtc_state);
	काष्ठा imx_ldb_channel *imx_ldb_ch = enc_to_imx_ldb_ch(encoder);
	काष्ठा drm_display_info *di = &conn_state->connector->display_info;
	u32 bus_क्रमmat = imx_ldb_ch->bus_क्रमmat;

	/* Bus क्रमmat description in DT overrides connector display info. */
	अगर (!bus_क्रमmat && di->num_bus_क्रमmats) अणु
		bus_क्रमmat = di->bus_क्रमmats[0];
		imx_crtc_state->bus_flags = di->bus_flags;
	पूर्ण अन्यथा अणु
		bus_क्रमmat = imx_ldb_ch->bus_क्रमmat;
		imx_crtc_state->bus_flags = imx_ldb_ch->bus_flags;
	पूर्ण
	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		imx_crtc_state->bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
		imx_crtc_state->bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	imx_crtc_state->di_hsync_pin = 2;
	imx_crtc_state->di_vsync_pin = 3;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा drm_connector_funcs imx_ldb_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = imx_drm_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs imx_ldb_connector_helper_funcs = अणु
	.get_modes = imx_ldb_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs imx_ldb_encoder_helper_funcs = अणु
	.atomic_mode_set = imx_ldb_encoder_atomic_mode_set,
	.enable = imx_ldb_encoder_enable,
	.disable = imx_ldb_encoder_disable,
	.atomic_check = imx_ldb_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक imx_ldb_get_clk(काष्ठा imx_ldb *ldb, पूर्णांक chno)
अणु
	अक्षर clkname[16];

	snम_लिखो(clkname, माप(clkname), "di%d", chno);
	ldb->clk[chno] = devm_clk_get(ldb->dev, clkname);
	अगर (IS_ERR(ldb->clk[chno]))
		वापस PTR_ERR(ldb->clk[chno]);

	snम_लिखो(clkname, माप(clkname), "di%d_pll", chno);
	ldb->clk_pll[chno] = devm_clk_get(ldb->dev, clkname);

	वापस PTR_ERR_OR_ZERO(ldb->clk_pll[chno]);
पूर्ण

अटल पूर्णांक imx_ldb_रेजिस्टर(काष्ठा drm_device *drm,
	काष्ठा imx_ldb_channel *imx_ldb_ch)
अणु
	काष्ठा imx_ldb *ldb = imx_ldb_ch->ldb;
	काष्ठा imx_ldb_encoder *ldb_encoder;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	ldb_encoder = drmm_simple_encoder_alloc(drm, काष्ठा imx_ldb_encoder,
						encoder, DRM_MODE_ENCODER_LVDS);
	अगर (IS_ERR(ldb_encoder))
		वापस PTR_ERR(ldb_encoder);

	ldb_encoder->channel = imx_ldb_ch;
	connector = &ldb_encoder->connector;
	encoder = &ldb_encoder->encoder;

	ret = imx_drm_encoder_parse_of(drm, encoder, imx_ldb_ch->child);
	अगर (ret)
		वापस ret;

	ret = imx_ldb_get_clk(ldb, imx_ldb_ch->chno);
	अगर (ret)
		वापस ret;

	अगर (ldb->ldb_ctrl & LDB_SPLIT_MODE_EN) अणु
		ret = imx_ldb_get_clk(ldb, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	drm_encoder_helper_add(encoder, &imx_ldb_encoder_helper_funcs);

	अगर (imx_ldb_ch->bridge) अणु
		ret = drm_bridge_attach(encoder, imx_ldb_ch->bridge, शून्य, 0);
		अगर (ret) अणु
			DRM_ERROR("Failed to initialize bridge with drm\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We want to add the connector whenever there is no bridge
		 * that brings its own, not only when there is a panel. For
		 * historical reasons, the ldb driver can also work without
		 * a panel.
		 */
		drm_connector_helper_add(connector,
					 &imx_ldb_connector_helper_funcs);
		drm_connector_init_with_ddc(drm, connector,
					    &imx_ldb_connector_funcs,
					    DRM_MODE_CONNECTOR_LVDS,
					    imx_ldb_ch->ddc);
		drm_connector_attach_encoder(connector, encoder);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा imx_ldb_bit_mapping अणु
	u32 bus_क्रमmat;
	u32 datawidth;
	स्थिर अक्षर * स्थिर mapping;
पूर्ण;

अटल स्थिर काष्ठा imx_ldb_bit_mapping imx_ldb_bit_mappings[] = अणु
	अणु MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,  18, "spwg" पूर्ण,
	अणु MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,  24, "spwg" पूर्ण,
	अणु MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA, 24, "jeida" पूर्ण,
पूर्ण;

अटल u32 of_get_bus_क्रमmat(काष्ठा device *dev, काष्ठा device_node *np)
अणु
	स्थिर अक्षर *bm;
	u32 datawidth = 0;
	पूर्णांक ret, i;

	ret = of_property_पढ़ो_string(np, "fsl,data-mapping", &bm);
	अगर (ret < 0)
		वापस ret;

	of_property_पढ़ो_u32(np, "fsl,data-width", &datawidth);

	क्रम (i = 0; i < ARRAY_SIZE(imx_ldb_bit_mappings); i++) अणु
		अगर (!strहालcmp(bm, imx_ldb_bit_mappings[i].mapping) &&
		    datawidth == imx_ldb_bit_mappings[i].datawidth)
			वापस imx_ldb_bit_mappings[i].bus_क्रमmat;
	पूर्ण

	dev_err(dev, "invalid data mapping: %d-bit \"%s\"\n", datawidth, bm);

	वापस -ENOENT;
पूर्ण

अटल काष्ठा bus_mux imx6q_lvds_mux[2] = अणु
	अणु
		.reg = IOMUXC_GPR3,
		.shअगरt = 6,
		.mask = IMX6Q_GPR3_LVDS0_MUX_CTL_MASK,
	पूर्ण, अणु
		.reg = IOMUXC_GPR3,
		.shअगरt = 8,
		.mask = IMX6Q_GPR3_LVDS1_MUX_CTL_MASK,
	पूर्ण
पूर्ण;

/*
 * For a device declaring compatible = "fsl,imx6q-ldb", "fsl,imx53-ldb",
 * of_match_device will walk through this list and take the first entry
 * matching any of its compatible values. Thereक्रमe, the more generic
 * entries (in this हाल fsl,imx53-ldb) need to be ordered last.
 */
अटल स्थिर काष्ठा of_device_id imx_ldb_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-ldb", .data = imx6q_lvds_mux, पूर्ण,
	अणु .compatible = "fsl,imx53-ldb", .data = शून्य, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_ldb_dt_ids);

अटल पूर्णांक imx_ldb_panel_ddc(काष्ठा device *dev,
		काष्ठा imx_ldb_channel *channel, काष्ठा device_node *child)
अणु
	काष्ठा device_node *ddc_node;
	स्थिर u8 *edidp;
	पूर्णांक ret;

	ddc_node = of_parse_phandle(child, "ddc-i2c-bus", 0);
	अगर (ddc_node) अणु
		channel->ddc = of_find_i2c_adapter_by_node(ddc_node);
		of_node_put(ddc_node);
		अगर (!channel->ddc) अणु
			dev_warn(dev, "failed to get ddc i2c adapter\n");
			वापस -EPROBE_DEFER;
		पूर्ण
	पूर्ण

	अगर (!channel->ddc) अणु
		पूर्णांक edid_len;

		/* अगर no DDC available, fallback to hardcoded EDID */
		dev_dbg(dev, "no ddc available\n");

		edidp = of_get_property(child, "edid", &edid_len);
		अगर (edidp) अणु
			channel->edid = kmemdup(edidp, edid_len, GFP_KERNEL);
		पूर्ण अन्यथा अगर (!channel->panel) अणु
			/* fallback to display-timings node */
			ret = of_get_drm_display_mode(child,
						      &channel->mode,
						      &channel->bus_flags,
						      OF_USE_NATIVE_MODE);
			अगर (!ret)
				channel->mode_valid = 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक imx_ldb_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा imx_ldb *imx_ldb = dev_get_drvdata(dev);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा imx_ldb_channel *channel = &imx_ldb->channel[i];

		अगर (!channel->ldb)
			जारी;

		ret = imx_ldb_रेजिस्टर(drm, channel);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा component_ops imx_ldb_ops = अणु
	.bind	= imx_ldb_bind,
पूर्ण;

अटल पूर्णांक imx_ldb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा of_device_id *of_id = of_match_device(imx_ldb_dt_ids, dev);
	काष्ठा device_node *child;
	काष्ठा imx_ldb *imx_ldb;
	पूर्णांक dual;
	पूर्णांक ret;
	पूर्णांक i;

	imx_ldb = devm_kzalloc(dev, माप(*imx_ldb), GFP_KERNEL);
	अगर (!imx_ldb)
		वापस -ENOMEM;

	imx_ldb->regmap = syscon_regmap_lookup_by_phandle(np, "gpr");
	अगर (IS_ERR(imx_ldb->regmap)) अणु
		dev_err(dev, "failed to get parent regmap\n");
		वापस PTR_ERR(imx_ldb->regmap);
	पूर्ण

	/* disable LDB by resetting the control रेजिस्टर to POR शेष */
	regmap_ग_लिखो(imx_ldb->regmap, IOMUXC_GPR2, 0);

	imx_ldb->dev = dev;

	अगर (of_id)
		imx_ldb->lvds_mux = of_id->data;

	dual = of_property_पढ़ो_bool(np, "fsl,dual-channel");
	अगर (dual)
		imx_ldb->ldb_ctrl |= LDB_SPLIT_MODE_EN;

	/*
	 * There are three dअगरferent possible घड़ी mux configurations:
	 * i.MX53:  ipu1_di0_sel, ipu1_di1_sel
	 * i.MX6q:  ipu1_di0_sel, ipu1_di1_sel, ipu2_di0_sel, ipu2_di1_sel
	 * i.MX6dl: ipu1_di0_sel, ipu1_di1_sel, lcdअगर_sel
	 * Map them all to di0_sel...di3_sel.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		अक्षर clkname[16];

		प्र_लिखो(clkname, "di%d_sel", i);
		imx_ldb->clk_sel[i] = devm_clk_get(imx_ldb->dev, clkname);
		अगर (IS_ERR(imx_ldb->clk_sel[i])) अणु
			ret = PTR_ERR(imx_ldb->clk_sel[i]);
			imx_ldb->clk_sel[i] = शून्य;
			अवरोध;
		पूर्ण

		imx_ldb->clk_parent[i] = clk_get_parent(imx_ldb->clk_sel[i]);
	पूर्ण
	अगर (i == 0)
		वापस ret;

	क्रम_each_child_of_node(np, child) अणु
		काष्ठा imx_ldb_channel *channel;
		पूर्णांक bus_क्रमmat;

		ret = of_property_पढ़ो_u32(child, "reg", &i);
		अगर (ret || i < 0 || i > 1) अणु
			ret = -EINVAL;
			जाओ मुक्त_child;
		पूर्ण

		अगर (!of_device_is_available(child))
			जारी;

		अगर (dual && i > 0) अणु
			dev_warn(dev, "dual-channel mode, ignoring second output\n");
			जारी;
		पूर्ण

		channel = &imx_ldb->channel[i];
		channel->ldb = imx_ldb;
		channel->chno = i;

		/*
		 * The output port is port@4 with an बाह्यal 4-port mux or
		 * port@2 with the पूर्णांकernal 2-port mux.
		 */
		ret = drm_of_find_panel_or_bridge(child,
						  imx_ldb->lvds_mux ? 4 : 2, 0,
						  &channel->panel, &channel->bridge);
		अगर (ret && ret != -ENODEV)
			जाओ मुक्त_child;

		/* panel ddc only अगर there is no bridge */
		अगर (!channel->bridge) अणु
			ret = imx_ldb_panel_ddc(dev, channel, child);
			अगर (ret)
				जाओ मुक्त_child;
		पूर्ण

		bus_क्रमmat = of_get_bus_क्रमmat(dev, child);
		अगर (bus_क्रमmat == -EINVAL) अणु
			/*
			 * If no bus क्रमmat was specअगरied in the device tree,
			 * we can still get it from the connected panel later.
			 */
			अगर (channel->panel && channel->panel->funcs &&
			    channel->panel->funcs->get_modes)
				bus_क्रमmat = 0;
		पूर्ण
		अगर (bus_क्रमmat < 0) अणु
			dev_err(dev, "could not determine data mapping: %d\n",
				bus_क्रमmat);
			ret = bus_क्रमmat;
			जाओ मुक्त_child;
		पूर्ण
		channel->bus_क्रमmat = bus_क्रमmat;
		channel->child = child;
	पूर्ण

	platक्रमm_set_drvdata(pdev, imx_ldb);

	वापस component_add(&pdev->dev, &imx_ldb_ops);

मुक्त_child:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल पूर्णांक imx_ldb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_ldb *imx_ldb = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा imx_ldb_channel *channel = &imx_ldb->channel[i];

		kमुक्त(channel->edid);
		i2c_put_adapter(channel->ddc);
	पूर्ण

	component_del(&pdev->dev, &imx_ldb_ops);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_ldb_driver = अणु
	.probe		= imx_ldb_probe,
	.हटाओ		= imx_ldb_हटाओ,
	.driver		= अणु
		.of_match_table = imx_ldb_dt_ids,
		.name	= DRIVER_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx_ldb_driver);

MODULE_DESCRIPTION("i.MX LVDS driver");
MODULE_AUTHOR("Sascha Hauer, Pengutronix");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
