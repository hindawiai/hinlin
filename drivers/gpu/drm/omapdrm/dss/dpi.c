<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "DPI"

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/माला.स>
#समावेश <linux/sys_soc.h>

#समावेश <drm/drm_bridge.h>

#समावेश "dss.h"
#समावेश "omapdss.h"

काष्ठा dpi_data अणु
	काष्ठा platक्रमm_device *pdev;
	क्रमागत dss_model dss_model;
	काष्ठा dss_device *dss;
	अचिन्हित पूर्णांक id;

	काष्ठा regulator *vdds_dsi_reg;
	क्रमागत dss_clk_source clk_src;
	काष्ठा dss_pll *pll;

	काष्ठा dss_lcd_mgr_config mgr_config;
	अचिन्हित दीर्घ pixelघड़ी;
	पूर्णांक data_lines;

	काष्ठा omap_dss_device output;
	काष्ठा drm_bridge bridge;
पूर्ण;

#घोषणा drm_bridge_to_dpi(bridge) container_of(bridge, काष्ठा dpi_data, bridge)

/* -----------------------------------------------------------------------------
 * Clock Handling and PLL
 */

अटल क्रमागत dss_clk_source dpi_get_clk_src_dra7xx(काष्ठा dpi_data *dpi,
						  क्रमागत omap_channel channel)
अणु
	/*
	 * Possible घड़ी sources:
	 * LCD1: FCK/PLL1_1/HDMI_PLL
	 * LCD2: FCK/PLL1_3/HDMI_PLL (DRA74x: PLL2_3)
	 * LCD3: FCK/PLL1_3/HDMI_PLL (DRA74x: PLL2_1)
	 */

	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
	अणु
		अगर (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL1_1))
			वापस DSS_CLK_SRC_PLL1_1;
		अवरोध;
	पूर्ण
	हाल OMAP_DSS_CHANNEL_LCD2:
	अणु
		अगर (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL1_3))
			वापस DSS_CLK_SRC_PLL1_3;
		अगर (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL2_3))
			वापस DSS_CLK_SRC_PLL2_3;
		अवरोध;
	पूर्ण
	हाल OMAP_DSS_CHANNEL_LCD3:
	अणु
		अगर (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL2_1))
			वापस DSS_CLK_SRC_PLL2_1;
		अगर (dss_pll_find_by_src(dpi->dss, DSS_CLK_SRC_PLL1_3))
			वापस DSS_CLK_SRC_PLL1_3;
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस DSS_CLK_SRC_FCK;
पूर्ण

अटल क्रमागत dss_clk_source dpi_get_clk_src(काष्ठा dpi_data *dpi)
अणु
	क्रमागत omap_channel channel = dpi->output.dispc_channel;

	/*
	 * XXX we can't currently use DSI PLL क्रम DPI with OMAP3, as the DSI PLL
	 * would also be used क्रम DISPC fclk. Meaning, when the DPI output is
	 * disabled, DISPC घड़ी will be disabled, and TV out will stop.
	 */
	चयन (dpi->dss_model) अणु
	हाल DSS_MODEL_OMAP2:
	हाल DSS_MODEL_OMAP3:
		वापस DSS_CLK_SRC_FCK;

	हाल DSS_MODEL_OMAP4:
		चयन (channel) अणु
		हाल OMAP_DSS_CHANNEL_LCD:
			वापस DSS_CLK_SRC_PLL1_1;
		हाल OMAP_DSS_CHANNEL_LCD2:
			वापस DSS_CLK_SRC_PLL2_1;
		शेष:
			वापस DSS_CLK_SRC_FCK;
		पूर्ण

	हाल DSS_MODEL_OMAP5:
		चयन (channel) अणु
		हाल OMAP_DSS_CHANNEL_LCD:
			वापस DSS_CLK_SRC_PLL1_1;
		हाल OMAP_DSS_CHANNEL_LCD3:
			वापस DSS_CLK_SRC_PLL2_1;
		हाल OMAP_DSS_CHANNEL_LCD2:
		शेष:
			वापस DSS_CLK_SRC_FCK;
		पूर्ण

	हाल DSS_MODEL_DRA7:
		वापस dpi_get_clk_src_dra7xx(dpi, channel);

	शेष:
		वापस DSS_CLK_SRC_FCK;
	पूर्ण
पूर्ण

काष्ठा dpi_clk_calc_ctx अणु
	काष्ठा dpi_data *dpi;
	अचिन्हित पूर्णांक clkout_idx;

	/* inमाला_दो */

	अचिन्हित दीर्घ pck_min, pck_max;

	/* outमाला_दो */

	काष्ठा dss_pll_घड़ी_info pll_cinfo;
	अचिन्हित दीर्घ fck;
	काष्ठा dispc_घड़ी_info dispc_cinfo;
पूर्ण;

अटल bool dpi_calc_dispc_cb(पूर्णांक lckd, पूर्णांक pckd, अचिन्हित दीर्घ lck,
		अचिन्हित दीर्घ pck, व्योम *data)
अणु
	काष्ठा dpi_clk_calc_ctx *ctx = data;

	/*
	 * Odd भागiders give us uneven duty cycle, causing problem when level
	 * shअगरted. So skip all odd भागiders when the pixel घड़ी is on the
	 * higher side.
	 */
	अगर (ctx->pck_min >= 100000000) अणु
		अगर (lckd > 1 && lckd % 2 != 0)
			वापस false;

		अगर (pckd > 1 && pckd % 2 != 0)
			वापस false;
	पूर्ण

	ctx->dispc_cinfo.lck_भाग = lckd;
	ctx->dispc_cinfo.pck_भाग = pckd;
	ctx->dispc_cinfo.lck = lck;
	ctx->dispc_cinfo.pck = pck;

	वापस true;
पूर्ण


अटल bool dpi_calc_hsभाग_cb(पूर्णांक m_dispc, अचिन्हित दीर्घ dispc,
		व्योम *data)
अणु
	काष्ठा dpi_clk_calc_ctx *ctx = data;

	ctx->pll_cinfo.mX[ctx->clkout_idx] = m_dispc;
	ctx->pll_cinfo.clkout[ctx->clkout_idx] = dispc;

	वापस dispc_भाग_calc(ctx->dpi->dss->dispc, dispc,
			      ctx->pck_min, ctx->pck_max,
			      dpi_calc_dispc_cb, ctx);
पूर्ण


अटल bool dpi_calc_pll_cb(पूर्णांक n, पूर्णांक m, अचिन्हित दीर्घ fपूर्णांक,
		अचिन्हित दीर्घ clkdco,
		व्योम *data)
अणु
	काष्ठा dpi_clk_calc_ctx *ctx = data;

	ctx->pll_cinfo.n = n;
	ctx->pll_cinfo.m = m;
	ctx->pll_cinfo.fपूर्णांक = fपूर्णांक;
	ctx->pll_cinfo.clkdco = clkdco;

	वापस dss_pll_hsभाग_calc_a(ctx->dpi->pll, clkdco,
		ctx->pck_min, dss_get_max_fck_rate(ctx->dpi->dss),
		dpi_calc_hsभाग_cb, ctx);
पूर्ण

अटल bool dpi_calc_dss_cb(अचिन्हित दीर्घ fck, व्योम *data)
अणु
	काष्ठा dpi_clk_calc_ctx *ctx = data;

	ctx->fck = fck;

	वापस dispc_भाग_calc(ctx->dpi->dss->dispc, fck,
			      ctx->pck_min, ctx->pck_max,
			      dpi_calc_dispc_cb, ctx);
पूर्ण

अटल bool dpi_pll_clk_calc(काष्ठा dpi_data *dpi, अचिन्हित दीर्घ pck,
		काष्ठा dpi_clk_calc_ctx *ctx)
अणु
	अचिन्हित दीर्घ clkin;

	स_रखो(ctx, 0, माप(*ctx));
	ctx->dpi = dpi;
	ctx->clkout_idx = dss_pll_get_clkout_idx_क्रम_src(dpi->clk_src);

	clkin = clk_get_rate(dpi->pll->clkin);

	अगर (dpi->pll->hw->type == DSS_PLL_TYPE_A) अणु
		अचिन्हित दीर्घ pll_min, pll_max;

		ctx->pck_min = pck - 1000;
		ctx->pck_max = pck + 1000;

		pll_min = 0;
		pll_max = 0;

		वापस dss_pll_calc_a(ctx->dpi->pll, clkin,
				pll_min, pll_max,
				dpi_calc_pll_cb, ctx);
	पूर्ण अन्यथा अणु /* DSS_PLL_TYPE_B */
		dss_pll_calc_b(dpi->pll, clkin, pck, &ctx->pll_cinfo);

		ctx->dispc_cinfo.lck_भाग = 1;
		ctx->dispc_cinfo.pck_भाग = 1;
		ctx->dispc_cinfo.lck = ctx->pll_cinfo.clkout[0];
		ctx->dispc_cinfo.pck = ctx->dispc_cinfo.lck;

		वापस true;
	पूर्ण
पूर्ण

अटल bool dpi_dss_clk_calc(काष्ठा dpi_data *dpi, अचिन्हित दीर्घ pck,
			     काष्ठा dpi_clk_calc_ctx *ctx)
अणु
	पूर्णांक i;

	/*
	 * DSS fck gives us very few possibilities, so finding a good pixel
	 * घड़ी may not be possible. We try multiple बार to find the घड़ी,
	 * each समय widening the pixel घड़ी range we look क्रम, up to
	 * +/- ~15MHz.
	 */

	क्रम (i = 0; i < 25; ++i) अणु
		bool ok;

		स_रखो(ctx, 0, माप(*ctx));
		ctx->dpi = dpi;
		अगर (pck > 1000 * i * i * i)
			ctx->pck_min = max(pck - 1000 * i * i * i, 0lu);
		अन्यथा
			ctx->pck_min = 0;
		ctx->pck_max = pck + 1000 * i * i * i;

		ok = dss_भाग_calc(dpi->dss, pck, ctx->pck_min,
				  dpi_calc_dss_cb, ctx);
		अगर (ok)
			वापस ok;
	पूर्ण

	वापस false;
पूर्ण



अटल पूर्णांक dpi_set_pll_clk(काष्ठा dpi_data *dpi, अचिन्हित दीर्घ pck_req)
अणु
	काष्ठा dpi_clk_calc_ctx ctx;
	पूर्णांक r;
	bool ok;

	ok = dpi_pll_clk_calc(dpi, pck_req, &ctx);
	अगर (!ok)
		वापस -EINVAL;

	r = dss_pll_set_config(dpi->pll, &ctx.pll_cinfo);
	अगर (r)
		वापस r;

	dss_select_lcd_clk_source(dpi->dss, dpi->output.dispc_channel,
				  dpi->clk_src);

	dpi->mgr_config.घड़ी_info = ctx.dispc_cinfo;

	वापस 0;
पूर्ण

अटल पूर्णांक dpi_set_dispc_clk(काष्ठा dpi_data *dpi, अचिन्हित दीर्घ pck_req)
अणु
	काष्ठा dpi_clk_calc_ctx ctx;
	पूर्णांक r;
	bool ok;

	ok = dpi_dss_clk_calc(dpi, pck_req, &ctx);
	अगर (!ok)
		वापस -EINVAL;

	r = dss_set_fck_rate(dpi->dss, ctx.fck);
	अगर (r)
		वापस r;

	dpi->mgr_config.घड़ी_info = ctx.dispc_cinfo;

	वापस 0;
पूर्ण

अटल पूर्णांक dpi_set_mode(काष्ठा dpi_data *dpi)
अणु
	पूर्णांक r;

	अगर (dpi->pll)
		r = dpi_set_pll_clk(dpi, dpi->pixelघड़ी);
	अन्यथा
		r = dpi_set_dispc_clk(dpi, dpi->pixelघड़ी);

	वापस r;
पूर्ण

अटल व्योम dpi_config_lcd_manager(काष्ठा dpi_data *dpi)
अणु
	dpi->mgr_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;

	dpi->mgr_config.stallmode = false;
	dpi->mgr_config.fअगरohandcheck = false;

	dpi->mgr_config.video_port_width = dpi->data_lines;

	dpi->mgr_config.lcden_sig_polarity = 0;

	dss_mgr_set_lcd_config(&dpi->output, &dpi->mgr_config);
पूर्ण

अटल पूर्णांक dpi_घड़ी_update(काष्ठा dpi_data *dpi, अचिन्हित दीर्घ *घड़ी)
अणु
	पूर्णांक lck_भाग, pck_भाग;
	अचिन्हित दीर्घ fck;
	काष्ठा dpi_clk_calc_ctx ctx;

	अगर (dpi->pll) अणु
		अगर (!dpi_pll_clk_calc(dpi, *घड़ी, &ctx))
			वापस -EINVAL;

		fck = ctx.pll_cinfo.clkout[ctx.clkout_idx];
	पूर्ण अन्यथा अणु
		अगर (!dpi_dss_clk_calc(dpi, *घड़ी, &ctx))
			वापस -EINVAL;

		fck = ctx.fck;
	पूर्ण

	lck_भाग = ctx.dispc_cinfo.lck_भाग;
	pck_भाग = ctx.dispc_cinfo.pck_भाग;

	*घड़ी = fck / lck_भाग / pck_भाग;

	वापस 0;
पूर्ण

अटल पूर्णांक dpi_verअगरy_pll(काष्ठा dss_pll *pll)
अणु
	पूर्णांक r;

	/* करो initial setup with the PLL to see अगर it is operational */

	r = dss_pll_enable(pll);
	अगर (r)
		वापस r;

	dss_pll_disable(pll);

	वापस 0;
पूर्ण

अटल व्योम dpi_init_pll(काष्ठा dpi_data *dpi)
अणु
	काष्ठा dss_pll *pll;

	अगर (dpi->pll)
		वापस;

	dpi->clk_src = dpi_get_clk_src(dpi);

	pll = dss_pll_find_by_src(dpi->dss, dpi->clk_src);
	अगर (!pll)
		वापस;

	अगर (dpi_verअगरy_pll(pll)) अणु
		DSSWARN("PLL not operational\n");
		वापस;
	पूर्ण

	dpi->pll = pll;
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Bridge Operations
 */

अटल पूर्णांक dpi_bridge_attach(काष्ठा drm_bridge *bridge,
			     क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा dpi_data *dpi = drm_bridge_to_dpi(bridge);

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR))
		वापस -EINVAL;

	dpi_init_pll(dpi);

	वापस drm_bridge_attach(bridge->encoder, dpi->output.next_bridge,
				 bridge, flags);
पूर्ण

अटल क्रमागत drm_mode_status
dpi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
		       स्थिर काष्ठा drm_display_info *info,
		       स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा dpi_data *dpi = drm_bridge_to_dpi(bridge);
	अचिन्हित दीर्घ घड़ी = mode->घड़ी * 1000;
	पूर्णांक ret;

	अगर (mode->hdisplay % 8 != 0)
		वापस MODE_BAD_WIDTH;

	अगर (mode->घड़ी == 0)
		वापस MODE_NOCLOCK;

	ret = dpi_घड़ी_update(dpi, &घड़ी);
	अगर (ret < 0)
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल bool dpi_bridge_mode_fixup(काष्ठा drm_bridge *bridge,
				   स्थिर काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा dpi_data *dpi = drm_bridge_to_dpi(bridge);
	अचिन्हित दीर्घ घड़ी = mode->घड़ी * 1000;
	पूर्णांक ret;

	ret = dpi_घड़ी_update(dpi, &घड़ी);
	अगर (ret < 0)
		वापस false;

	adjusted_mode->घड़ी = घड़ी / 1000;

	वापस true;
पूर्ण

अटल व्योम dpi_bridge_mode_set(काष्ठा drm_bridge *bridge,
				 स्थिर काष्ठा drm_display_mode *mode,
				 स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा dpi_data *dpi = drm_bridge_to_dpi(bridge);

	dpi->pixelघड़ी = adjusted_mode->घड़ी * 1000;
पूर्ण

अटल व्योम dpi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dpi_data *dpi = drm_bridge_to_dpi(bridge);
	पूर्णांक r;

	अगर (dpi->vdds_dsi_reg) अणु
		r = regulator_enable(dpi->vdds_dsi_reg);
		अगर (r)
			वापस;
	पूर्ण

	r = dispc_runसमय_get(dpi->dss->dispc);
	अगर (r)
		जाओ err_get_dispc;

	r = dss_dpi_select_source(dpi->dss, dpi->id, dpi->output.dispc_channel);
	अगर (r)
		जाओ err_src_sel;

	अगर (dpi->pll) अणु
		r = dss_pll_enable(dpi->pll);
		अगर (r)
			जाओ err_pll_init;
	पूर्ण

	r = dpi_set_mode(dpi);
	अगर (r)
		जाओ err_set_mode;

	dpi_config_lcd_manager(dpi);

	mdelay(2);

	r = dss_mgr_enable(&dpi->output);
	अगर (r)
		जाओ err_mgr_enable;

	वापस;

err_mgr_enable:
err_set_mode:
	अगर (dpi->pll)
		dss_pll_disable(dpi->pll);
err_pll_init:
err_src_sel:
	dispc_runसमय_put(dpi->dss->dispc);
err_get_dispc:
	अगर (dpi->vdds_dsi_reg)
		regulator_disable(dpi->vdds_dsi_reg);
पूर्ण

अटल व्योम dpi_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dpi_data *dpi = drm_bridge_to_dpi(bridge);

	dss_mgr_disable(&dpi->output);

	अगर (dpi->pll) अणु
		dss_select_lcd_clk_source(dpi->dss, dpi->output.dispc_channel,
					  DSS_CLK_SRC_FCK);
		dss_pll_disable(dpi->pll);
	पूर्ण

	dispc_runसमय_put(dpi->dss->dispc);

	अगर (dpi->vdds_dsi_reg)
		regulator_disable(dpi->vdds_dsi_reg);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs dpi_bridge_funcs = अणु
	.attach = dpi_bridge_attach,
	.mode_valid = dpi_bridge_mode_valid,
	.mode_fixup = dpi_bridge_mode_fixup,
	.mode_set = dpi_bridge_mode_set,
	.enable = dpi_bridge_enable,
	.disable = dpi_bridge_disable,
पूर्ण;

अटल व्योम dpi_bridge_init(काष्ठा dpi_data *dpi)
अणु
	dpi->bridge.funcs = &dpi_bridge_funcs;
	dpi->bridge.of_node = dpi->pdev->dev.of_node;
	dpi->bridge.type = DRM_MODE_CONNECTOR_DPI;

	drm_bridge_add(&dpi->bridge);
पूर्ण

अटल व्योम dpi_bridge_cleanup(काष्ठा dpi_data *dpi)
अणु
	drm_bridge_हटाओ(&dpi->bridge);
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialisation and Cleanup
 */

/*
 * Return a hardcoded channel क्रम the DPI output. This should work क्रम
 * current use हालs, but this can be later expanded to either resolve
 * the channel in some more dynamic manner, or get the channel as a user
 * parameter.
 */
अटल क्रमागत omap_channel dpi_get_channel(काष्ठा dpi_data *dpi)
अणु
	चयन (dpi->dss_model) अणु
	हाल DSS_MODEL_OMAP2:
	हाल DSS_MODEL_OMAP3:
		वापस OMAP_DSS_CHANNEL_LCD;

	हाल DSS_MODEL_DRA7:
		चयन (dpi->id) अणु
		हाल 2:
			वापस OMAP_DSS_CHANNEL_LCD3;
		हाल 1:
			वापस OMAP_DSS_CHANNEL_LCD2;
		हाल 0:
		शेष:
			वापस OMAP_DSS_CHANNEL_LCD;
		पूर्ण

	हाल DSS_MODEL_OMAP4:
		वापस OMAP_DSS_CHANNEL_LCD2;

	हाल DSS_MODEL_OMAP5:
		वापस OMAP_DSS_CHANNEL_LCD3;

	शेष:
		DSSWARN("unsupported DSS version\n");
		वापस OMAP_DSS_CHANNEL_LCD;
	पूर्ण
पूर्ण

अटल पूर्णांक dpi_init_output_port(काष्ठा dpi_data *dpi, काष्ठा device_node *port)
अणु
	काष्ठा omap_dss_device *out = &dpi->output;
	u32 port_num = 0;
	पूर्णांक r;

	dpi_bridge_init(dpi);

	of_property_पढ़ो_u32(port, "reg", &port_num);
	dpi->id = port_num <= 2 ? port_num : 0;

	चयन (port_num) अणु
	हाल 2:
		out->name = "dpi.2";
		अवरोध;
	हाल 1:
		out->name = "dpi.1";
		अवरोध;
	हाल 0:
	शेष:
		out->name = "dpi.0";
		अवरोध;
	पूर्ण

	out->dev = &dpi->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_DPI;
	out->type = OMAP_DISPLAY_TYPE_DPI;
	out->dispc_channel = dpi_get_channel(dpi);
	out->of_port = port_num;

	r = omapdss_device_init_output(out, &dpi->bridge);
	अगर (r < 0) अणु
		dpi_bridge_cleanup(dpi);
		वापस r;
	पूर्ण

	omapdss_device_रेजिस्टर(out);

	वापस 0;
पूर्ण

अटल व्योम dpi_uninit_output_port(काष्ठा device_node *port)
अणु
	काष्ठा dpi_data *dpi = port->data;
	काष्ठा omap_dss_device *out = &dpi->output;

	omapdss_device_unरेजिस्टर(out);
	omapdss_device_cleanup_output(out);

	dpi_bridge_cleanup(dpi);
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialisation and Cleanup
 */

अटल स्थिर काष्ठा soc_device_attribute dpi_soc_devices[] = अणु
	अणु .machine = "OMAP3[456]*" पूर्ण,
	अणु .machine = "[AD]M37*" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक dpi_init_regulator(काष्ठा dpi_data *dpi)
अणु
	काष्ठा regulator *vdds_dsi;

	/*
	 * The DPI uses the DSI VDDS on OMAP34xx, OMAP35xx, OMAP36xx, AM37xx and
	 * DM37xx only.
	 */
	अगर (!soc_device_match(dpi_soc_devices))
		वापस 0;

	vdds_dsi = devm_regulator_get(&dpi->pdev->dev, "vdds_dsi");
	अगर (IS_ERR(vdds_dsi)) अणु
		अगर (PTR_ERR(vdds_dsi) != -EPROBE_DEFER)
			DSSERR("can't get VDDS_DSI regulator\n");
		वापस PTR_ERR(vdds_dsi);
	पूर्ण

	dpi->vdds_dsi_reg = vdds_dsi;

	वापस 0;
पूर्ण

पूर्णांक dpi_init_port(काष्ठा dss_device *dss, काष्ठा platक्रमm_device *pdev,
		  काष्ठा device_node *port, क्रमागत dss_model dss_model)
अणु
	काष्ठा dpi_data *dpi;
	काष्ठा device_node *ep;
	u32 datalines;
	पूर्णांक r;

	dpi = devm_kzalloc(&pdev->dev, माप(*dpi), GFP_KERNEL);
	अगर (!dpi)
		वापस -ENOMEM;

	ep = of_get_next_child(port, शून्य);
	अगर (!ep)
		वापस 0;

	r = of_property_पढ़ो_u32(ep, "data-lines", &datalines);
	of_node_put(ep);
	अगर (r) अणु
		DSSERR("failed to parse datalines\n");
		वापस r;
	पूर्ण

	dpi->data_lines = datalines;

	dpi->pdev = pdev;
	dpi->dss_model = dss_model;
	dpi->dss = dss;
	port->data = dpi;

	r = dpi_init_regulator(dpi);
	अगर (r)
		वापस r;

	वापस dpi_init_output_port(dpi, port);
पूर्ण

व्योम dpi_uninit_port(काष्ठा device_node *port)
अणु
	काष्ठा dpi_data *dpi = port->data;

	अगर (!dpi)
		वापस;

	dpi_uninit_output_port(port);
पूर्ण
