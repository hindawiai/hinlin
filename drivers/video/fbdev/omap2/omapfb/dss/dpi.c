<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/dpi.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "DPI"

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

#घोषणा HSDIV_DISPC	0

काष्ठा dpi_data अणु
	काष्ठा platक्रमm_device *pdev;

	काष्ठा regulator *vdds_dsi_reg;
	काष्ठा dss_pll *pll;

	काष्ठा mutex lock;

	काष्ठा omap_video_timings timings;
	काष्ठा dss_lcd_mgr_config mgr_config;
	पूर्णांक data_lines;

	काष्ठा omap_dss_device output;

	bool port_initialized;
पूर्ण;

अटल काष्ठा dpi_data *dpi_get_data_from_dssdev(काष्ठा omap_dss_device *dssdev)
अणु
	वापस container_of(dssdev, काष्ठा dpi_data, output);
पूर्ण

/* only used in non-DT mode */
अटल काष्ठा dpi_data *dpi_get_data_from_pdev(काष्ठा platक्रमm_device *pdev)
अणु
	वापस platक्रमm_get_drvdata(pdev);
पूर्ण

अटल काष्ठा dss_pll *dpi_get_pll(क्रमागत omap_channel channel)
अणु
	/*
	 * XXX we can't currently use DSI PLL क्रम DPI with OMAP3, as the DSI PLL
	 * would also be used क्रम DISPC fclk. Meaning, when the DPI output is
	 * disabled, DISPC घड़ी will be disabled, and TV out will stop.
	 */
	चयन (omapdss_get_version()) अणु
	हाल OMAPDSS_VER_OMAP24xx:
	हाल OMAPDSS_VER_OMAP34xx_ES1:
	हाल OMAPDSS_VER_OMAP34xx_ES3:
	हाल OMAPDSS_VER_OMAP3630:
	हाल OMAPDSS_VER_AM35xx:
	हाल OMAPDSS_VER_AM43xx:
		वापस शून्य;

	हाल OMAPDSS_VER_OMAP4430_ES1:
	हाल OMAPDSS_VER_OMAP4430_ES2:
	हाल OMAPDSS_VER_OMAP4:
		चयन (channel) अणु
		हाल OMAP_DSS_CHANNEL_LCD:
			वापस dss_pll_find("dsi0");
		हाल OMAP_DSS_CHANNEL_LCD2:
			वापस dss_pll_find("dsi1");
		शेष:
			वापस शून्य;
		पूर्ण

	हाल OMAPDSS_VER_OMAP5:
		चयन (channel) अणु
		हाल OMAP_DSS_CHANNEL_LCD:
			वापस dss_pll_find("dsi0");
		हाल OMAP_DSS_CHANNEL_LCD3:
			वापस dss_pll_find("dsi1");
		शेष:
			वापस शून्य;
		पूर्ण

	हाल OMAPDSS_VER_DRA7xx:
		चयन (channel) अणु
		हाल OMAP_DSS_CHANNEL_LCD:
		हाल OMAP_DSS_CHANNEL_LCD2:
			वापस dss_pll_find("video0");
		हाल OMAP_DSS_CHANNEL_LCD3:
			वापस dss_pll_find("video1");
		शेष:
			वापस शून्य;
		पूर्ण

	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल क्रमागत omap_dss_clk_source dpi_get_alt_clk_src(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC;
	शेष:
		/* this shouldn't happen */
		WARN_ON(1);
		वापस OMAP_DSS_CLK_SRC_FCK;
	पूर्ण
पूर्ण

काष्ठा dpi_clk_calc_ctx अणु
	काष्ठा dss_pll *pll;

	/* inमाला_दो */

	अचिन्हित दीर्घ pck_min, pck_max;

	/* outमाला_दो */

	काष्ठा dss_pll_घड़ी_info dsi_cinfo;
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

	/*
	 * Odd भागiders give us uneven duty cycle, causing problem when level
	 * shअगरted. So skip all odd भागiders when the pixel घड़ी is on the
	 * higher side.
	 */
	अगर (m_dispc > 1 && m_dispc % 2 != 0 && ctx->pck_min >= 100000000)
		वापस false;

	ctx->dsi_cinfo.mX[HSDIV_DISPC] = m_dispc;
	ctx->dsi_cinfo.clkout[HSDIV_DISPC] = dispc;

	वापस dispc_भाग_calc(dispc, ctx->pck_min, ctx->pck_max,
			dpi_calc_dispc_cb, ctx);
पूर्ण


अटल bool dpi_calc_pll_cb(पूर्णांक n, पूर्णांक m, अचिन्हित दीर्घ fपूर्णांक,
		अचिन्हित दीर्घ clkdco,
		व्योम *data)
अणु
	काष्ठा dpi_clk_calc_ctx *ctx = data;

	ctx->dsi_cinfo.n = n;
	ctx->dsi_cinfo.m = m;
	ctx->dsi_cinfo.fपूर्णांक = fपूर्णांक;
	ctx->dsi_cinfo.clkdco = clkdco;

	वापस dss_pll_hsभाग_calc(ctx->pll, clkdco,
		ctx->pck_min, dss_feat_get_param_max(FEAT_PARAM_DSS_FCK),
		dpi_calc_hsभाग_cb, ctx);
पूर्ण

अटल bool dpi_calc_dss_cb(अचिन्हित दीर्घ fck, व्योम *data)
अणु
	काष्ठा dpi_clk_calc_ctx *ctx = data;

	ctx->fck = fck;

	वापस dispc_भाग_calc(fck, ctx->pck_min, ctx->pck_max,
			dpi_calc_dispc_cb, ctx);
पूर्ण

अटल bool dpi_dsi_clk_calc(काष्ठा dpi_data *dpi, अचिन्हित दीर्घ pck,
		काष्ठा dpi_clk_calc_ctx *ctx)
अणु
	अचिन्हित दीर्घ clkin;
	अचिन्हित दीर्घ pll_min, pll_max;

	स_रखो(ctx, 0, माप(*ctx));
	ctx->pll = dpi->pll;
	ctx->pck_min = pck - 1000;
	ctx->pck_max = pck + 1000;

	pll_min = 0;
	pll_max = 0;

	clkin = clk_get_rate(ctx->pll->clkin);

	वापस dss_pll_calc(ctx->pll, clkin,
			pll_min, pll_max,
			dpi_calc_pll_cb, ctx);
पूर्ण

अटल bool dpi_dss_clk_calc(अचिन्हित दीर्घ pck, काष्ठा dpi_clk_calc_ctx *ctx)
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
		अगर (pck > 1000 * i * i * i)
			ctx->pck_min = max(pck - 1000 * i * i * i, 0lu);
		अन्यथा
			ctx->pck_min = 0;
		ctx->pck_max = pck + 1000 * i * i * i;

		ok = dss_भाग_calc(pck, ctx->pck_min, dpi_calc_dss_cb, ctx);
		अगर (ok)
			वापस ok;
	पूर्ण

	वापस false;
पूर्ण



अटल पूर्णांक dpi_set_dsi_clk(काष्ठा dpi_data *dpi, क्रमागत omap_channel channel,
		अचिन्हित दीर्घ pck_req, अचिन्हित दीर्घ *fck, पूर्णांक *lck_भाग,
		पूर्णांक *pck_भाग)
अणु
	काष्ठा dpi_clk_calc_ctx ctx;
	पूर्णांक r;
	bool ok;

	ok = dpi_dsi_clk_calc(dpi, pck_req, &ctx);
	अगर (!ok)
		वापस -EINVAL;

	r = dss_pll_set_config(dpi->pll, &ctx.dsi_cinfo);
	अगर (r)
		वापस r;

	dss_select_lcd_clk_source(channel,
			dpi_get_alt_clk_src(channel));

	dpi->mgr_config.घड़ी_info = ctx.dispc_cinfo;

	*fck = ctx.dsi_cinfo.clkout[HSDIV_DISPC];
	*lck_भाग = ctx.dispc_cinfo.lck_भाग;
	*pck_भाग = ctx.dispc_cinfo.pck_भाग;

	वापस 0;
पूर्ण

अटल पूर्णांक dpi_set_dispc_clk(काष्ठा dpi_data *dpi, अचिन्हित दीर्घ pck_req,
		अचिन्हित दीर्घ *fck, पूर्णांक *lck_भाग, पूर्णांक *pck_भाग)
अणु
	काष्ठा dpi_clk_calc_ctx ctx;
	पूर्णांक r;
	bool ok;

	ok = dpi_dss_clk_calc(pck_req, &ctx);
	अगर (!ok)
		वापस -EINVAL;

	r = dss_set_fck_rate(ctx.fck);
	अगर (r)
		वापस r;

	dpi->mgr_config.घड़ी_info = ctx.dispc_cinfo;

	*fck = ctx.fck;
	*lck_भाग = ctx.dispc_cinfo.lck_भाग;
	*pck_भाग = ctx.dispc_cinfo.pck_भाग;

	वापस 0;
पूर्ण

अटल पूर्णांक dpi_set_mode(काष्ठा dpi_data *dpi)
अणु
	काष्ठा omap_dss_device *out = &dpi->output;
	काष्ठा omap_overlay_manager *mgr = out->manager;
	काष्ठा omap_video_timings *t = &dpi->timings;
	पूर्णांक lck_भाग = 0, pck_भाग = 0;
	अचिन्हित दीर्घ fck = 0;
	अचिन्हित दीर्घ pck;
	पूर्णांक r = 0;

	अगर (dpi->pll)
		r = dpi_set_dsi_clk(dpi, mgr->id, t->pixelघड़ी, &fck,
				&lck_भाग, &pck_भाग);
	अन्यथा
		r = dpi_set_dispc_clk(dpi, t->pixelघड़ी, &fck,
				&lck_भाग, &pck_भाग);
	अगर (r)
		वापस r;

	pck = fck / lck_भाग / pck_भाग;

	अगर (pck != t->pixelघड़ी) अणु
		DSSWARN("Could not find exact pixel clock. Requested %d Hz, got %lu Hz\n",
			t->pixelघड़ी, pck);

		t->pixelघड़ी = pck;
	पूर्ण

	dss_mgr_set_timings(mgr, t);

	वापस 0;
पूर्ण

अटल व्योम dpi_config_lcd_manager(काष्ठा dpi_data *dpi)
अणु
	काष्ठा omap_dss_device *out = &dpi->output;
	काष्ठा omap_overlay_manager *mgr = out->manager;

	dpi->mgr_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;

	dpi->mgr_config.stallmode = false;
	dpi->mgr_config.fअगरohandcheck = false;

	dpi->mgr_config.video_port_width = dpi->data_lines;

	dpi->mgr_config.lcden_sig_polarity = 0;

	dss_mgr_set_lcd_config(mgr, &dpi->mgr_config);
पूर्ण

अटल पूर्णांक dpi_display_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	काष्ठा omap_dss_device *out = &dpi->output;
	पूर्णांक r;

	mutex_lock(&dpi->lock);

	अगर (dss_has_feature(FEAT_DPI_USES_VDDS_DSI) && !dpi->vdds_dsi_reg) अणु
		DSSERR("no VDSS_DSI regulator\n");
		r = -ENODEV;
		जाओ err_no_reg;
	पूर्ण

	अगर (out->manager == शून्य) अणु
		DSSERR("failed to enable display: no output/manager\n");
		r = -ENODEV;
		जाओ err_no_out_mgr;
	पूर्ण

	अगर (dss_has_feature(FEAT_DPI_USES_VDDS_DSI)) अणु
		r = regulator_enable(dpi->vdds_dsi_reg);
		अगर (r)
			जाओ err_reg_enable;
	पूर्ण

	r = dispc_runसमय_get();
	अगर (r)
		जाओ err_get_dispc;

	r = dss_dpi_select_source(out->port_num, out->manager->id);
	अगर (r)
		जाओ err_src_sel;

	अगर (dpi->pll) अणु
		r = dss_pll_enable(dpi->pll);
		अगर (r)
			जाओ err_dsi_pll_init;
	पूर्ण

	r = dpi_set_mode(dpi);
	अगर (r)
		जाओ err_set_mode;

	dpi_config_lcd_manager(dpi);

	mdelay(2);

	r = dss_mgr_enable(out->manager);
	अगर (r)
		जाओ err_mgr_enable;

	mutex_unlock(&dpi->lock);

	वापस 0;

err_mgr_enable:
err_set_mode:
	अगर (dpi->pll)
		dss_pll_disable(dpi->pll);
err_dsi_pll_init:
err_src_sel:
	dispc_runसमय_put();
err_get_dispc:
	अगर (dss_has_feature(FEAT_DPI_USES_VDDS_DSI))
		regulator_disable(dpi->vdds_dsi_reg);
err_reg_enable:
err_no_out_mgr:
err_no_reg:
	mutex_unlock(&dpi->lock);
	वापस r;
पूर्ण

अटल व्योम dpi_display_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	काष्ठा omap_overlay_manager *mgr = dpi->output.manager;

	mutex_lock(&dpi->lock);

	dss_mgr_disable(mgr);

	अगर (dpi->pll) अणु
		dss_select_lcd_clk_source(mgr->id, OMAP_DSS_CLK_SRC_FCK);
		dss_pll_disable(dpi->pll);
	पूर्ण

	dispc_runसमय_put();

	अगर (dss_has_feature(FEAT_DPI_USES_VDDS_DSI))
		regulator_disable(dpi->vdds_dsi_reg);

	mutex_unlock(&dpi->lock);
पूर्ण

अटल व्योम dpi_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);

	DSSDBG("dpi_set_timings\n");

	mutex_lock(&dpi->lock);

	dpi->timings = *timings;

	mutex_unlock(&dpi->lock);
पूर्ण

अटल व्योम dpi_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);

	mutex_lock(&dpi->lock);

	*timings = dpi->timings;

	mutex_unlock(&dpi->lock);
पूर्ण

अटल पूर्णांक dpi_check_timings(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	काष्ठा omap_overlay_manager *mgr = dpi->output.manager;
	पूर्णांक lck_भाग, pck_भाग;
	अचिन्हित दीर्घ fck;
	अचिन्हित दीर्घ pck;
	काष्ठा dpi_clk_calc_ctx ctx;
	bool ok;

	अगर (mgr && !dispc_mgr_timings_ok(mgr->id, timings))
		वापस -EINVAL;

	अगर (timings->pixelघड़ी == 0)
		वापस -EINVAL;

	अगर (dpi->pll) अणु
		ok = dpi_dsi_clk_calc(dpi, timings->pixelघड़ी, &ctx);
		अगर (!ok)
			वापस -EINVAL;

		fck = ctx.dsi_cinfo.clkout[HSDIV_DISPC];
	पूर्ण अन्यथा अणु
		ok = dpi_dss_clk_calc(timings->pixelघड़ी, &ctx);
		अगर (!ok)
			वापस -EINVAL;

		fck = ctx.fck;
	पूर्ण

	lck_भाग = ctx.dispc_cinfo.lck_भाग;
	pck_भाग = ctx.dispc_cinfo.pck_भाग;

	pck = fck / lck_भाग / pck_भाग;

	timings->pixelघड़ी = pck;

	वापस 0;
पूर्ण

अटल व्योम dpi_set_data_lines(काष्ठा omap_dss_device *dssdev, पूर्णांक data_lines)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);

	mutex_lock(&dpi->lock);

	dpi->data_lines = data_lines;

	mutex_unlock(&dpi->lock);
पूर्ण

अटल पूर्णांक dpi_verअगरy_dsi_pll(काष्ठा dss_pll *pll)
अणु
	पूर्णांक r;

	/* करो initial setup with the PLL to see अगर it is operational */

	r = dss_pll_enable(pll);
	अगर (r)
		वापस r;

	dss_pll_disable(pll);

	वापस 0;
पूर्ण

अटल पूर्णांक dpi_init_regulator(काष्ठा dpi_data *dpi)
अणु
	काष्ठा regulator *vdds_dsi;

	अगर (!dss_has_feature(FEAT_DPI_USES_VDDS_DSI))
		वापस 0;

	अगर (dpi->vdds_dsi_reg)
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

अटल व्योम dpi_init_pll(काष्ठा dpi_data *dpi)
अणु
	काष्ठा dss_pll *pll;

	अगर (dpi->pll)
		वापस;

	pll = dpi_get_pll(dpi->output.dispc_channel);
	अगर (!pll)
		वापस;

	/* On DRA7 we need to set a mux to use the PLL */
	अगर (omapdss_get_version() == OMAPDSS_VER_DRA7xx)
		dss_ctrl_pll_set_control_mux(pll->id, dpi->output.dispc_channel);

	अगर (dpi_verअगरy_dsi_pll(pll)) अणु
		DSSWARN("DSI PLL not operational\n");
		वापस;
	पूर्ण

	dpi->pll = pll;
पूर्ण

/*
 * Return a hardcoded channel क्रम the DPI output. This should work क्रम
 * current use हालs, but this can be later expanded to either resolve
 * the channel in some more dynamic manner, or get the channel as a user
 * parameter.
 */
अटल क्रमागत omap_channel dpi_get_channel(पूर्णांक port_num)
अणु
	चयन (omapdss_get_version()) अणु
	हाल OMAPDSS_VER_OMAP24xx:
	हाल OMAPDSS_VER_OMAP34xx_ES1:
	हाल OMAPDSS_VER_OMAP34xx_ES3:
	हाल OMAPDSS_VER_OMAP3630:
	हाल OMAPDSS_VER_AM35xx:
	हाल OMAPDSS_VER_AM43xx:
		वापस OMAP_DSS_CHANNEL_LCD;

	हाल OMAPDSS_VER_DRA7xx:
		चयन (port_num) अणु
		हाल 2:
			वापस OMAP_DSS_CHANNEL_LCD3;
		हाल 1:
			वापस OMAP_DSS_CHANNEL_LCD2;
		हाल 0:
		शेष:
			वापस OMAP_DSS_CHANNEL_LCD;
		पूर्ण

	हाल OMAPDSS_VER_OMAP4430_ES1:
	हाल OMAPDSS_VER_OMAP4430_ES2:
	हाल OMAPDSS_VER_OMAP4:
		वापस OMAP_DSS_CHANNEL_LCD2;

	हाल OMAPDSS_VER_OMAP5:
		वापस OMAP_DSS_CHANNEL_LCD3;

	शेष:
		DSSWARN("unsupported DSS version\n");
		वापस OMAP_DSS_CHANNEL_LCD;
	पूर्ण
पूर्ण

अटल पूर्णांक dpi_connect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	काष्ठा omap_overlay_manager *mgr;
	पूर्णांक r;

	r = dpi_init_regulator(dpi);
	अगर (r)
		वापस r;

	dpi_init_pll(dpi);

	mgr = omap_dss_get_overlay_manager(dssdev->dispc_channel);
	अगर (!mgr)
		वापस -ENODEV;

	r = dss_mgr_connect(mgr, dssdev);
	अगर (r)
		वापस r;

	r = omapdss_output_set_device(dssdev, dst);
	अगर (r) अणु
		DSSERR("failed to connect output to new device: %s\n",
				dst->name);
		dss_mgr_disconnect(mgr, dssdev);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpi_disconnect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	WARN_ON(dst != dssdev->dst);

	अगर (dst != dssdev->dst)
		वापस;

	omapdss_output_unset_device(dssdev);

	अगर (dssdev->manager)
		dss_mgr_disconnect(dssdev->manager, dssdev);
पूर्ण

अटल स्थिर काष्ठा omapdss_dpi_ops dpi_ops = अणु
	.connect = dpi_connect,
	.disconnect = dpi_disconnect,

	.enable = dpi_display_enable,
	.disable = dpi_display_disable,

	.check_timings = dpi_check_timings,
	.set_timings = dpi_set_timings,
	.get_timings = dpi_get_timings,

	.set_data_lines = dpi_set_data_lines,
पूर्ण;

अटल व्योम dpi_init_output(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_pdev(pdev);
	काष्ठा omap_dss_device *out = &dpi->output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_DPI;
	out->output_type = OMAP_DISPLAY_TYPE_DPI;
	out->name = "dpi.0";
	out->dispc_channel = dpi_get_channel(0);
	out->ops.dpi = &dpi_ops;
	out->owner = THIS_MODULE;

	omapdss_रेजिस्टर_output(out);
पूर्ण

अटल व्योम dpi_uninit_output(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dpi_data *dpi = dpi_get_data_from_pdev(pdev);
	काष्ठा omap_dss_device *out = &dpi->output;

	omapdss_unरेजिस्टर_output(out);
पूर्ण

अटल व्योम dpi_init_output_port(काष्ठा platक्रमm_device *pdev,
	काष्ठा device_node *port)
अणु
	काष्ठा dpi_data *dpi = port->data;
	काष्ठा omap_dss_device *out = &dpi->output;
	पूर्णांक r;
	u32 port_num;

	r = of_property_पढ़ो_u32(port, "reg", &port_num);
	अगर (r)
		port_num = 0;

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

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_DPI;
	out->output_type = OMAP_DISPLAY_TYPE_DPI;
	out->dispc_channel = dpi_get_channel(port_num);
	out->port_num = port_num;
	out->ops.dpi = &dpi_ops;
	out->owner = THIS_MODULE;

	omapdss_रेजिस्टर_output(out);
पूर्ण

अटल व्योम dpi_uninit_output_port(काष्ठा device_node *port)
अणु
	काष्ठा dpi_data *dpi = port->data;
	काष्ठा omap_dss_device *out = &dpi->output;

	omapdss_unरेजिस्टर_output(out);
पूर्ण

अटल पूर्णांक dpi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा dpi_data *dpi;

	dpi = devm_kzalloc(&pdev->dev, माप(*dpi), GFP_KERNEL);
	अगर (!dpi)
		वापस -ENOMEM;

	dpi->pdev = pdev;

	platक्रमm_set_drvdata(pdev, dpi);

	mutex_init(&dpi->lock);

	dpi_init_output(pdev);

	वापस 0;
पूर्ण

अटल व्योम dpi_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	dpi_uninit_output(pdev);
पूर्ण

अटल स्थिर काष्ठा component_ops dpi_component_ops = अणु
	.bind	= dpi_bind,
	.unbind	= dpi_unbind,
पूर्ण;

अटल पूर्णांक dpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &dpi_component_ops);
पूर्ण

अटल पूर्णांक dpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &dpi_component_ops);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_dpi_driver = अणु
	.probe		= dpi_probe,
	.हटाओ		= dpi_हटाओ,
	.driver         = अणु
		.name   = "omapdss_dpi",
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

पूर्णांक __init dpi_init_platक्रमm_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_dpi_driver);
पूर्ण

व्योम dpi_uninit_platक्रमm_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_dpi_driver);
पूर्ण

पूर्णांक dpi_init_port(काष्ठा platक्रमm_device *pdev, काष्ठा device_node *port)
अणु
	काष्ठा dpi_data *dpi;
	काष्ठा device_node *ep;
	u32 datalines;
	पूर्णांक r;

	dpi = devm_kzalloc(&pdev->dev, माप(*dpi), GFP_KERNEL);
	अगर (!dpi)
		वापस -ENOMEM;

	ep = omapdss_of_get_next_endpoपूर्णांक(port, शून्य);
	अगर (!ep)
		वापस 0;

	r = of_property_पढ़ो_u32(ep, "data-lines", &datalines);
	अगर (r) अणु
		DSSERR("failed to parse datalines\n");
		जाओ err_datalines;
	पूर्ण

	dpi->data_lines = datalines;

	of_node_put(ep);

	dpi->pdev = pdev;
	port->data = dpi;

	mutex_init(&dpi->lock);

	dpi_init_output_port(pdev, port);

	dpi->port_initialized = true;

	वापस 0;

err_datalines:
	of_node_put(ep);

	वापस r;
पूर्ण

व्योम dpi_uninit_port(काष्ठा device_node *port)
अणु
	काष्ठा dpi_data *dpi = port->data;

	अगर (!dpi->port_initialized)
		वापस;

	dpi_uninit_output_port(port);
पूर्ण
