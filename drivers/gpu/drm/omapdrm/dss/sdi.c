<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#घोषणा DSS_SUBSYS_NAME "SDI"

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/माला.स>

#समावेश <drm/drm_bridge.h>

#समावेश "dss.h"
#समावेश "omapdss.h"

काष्ठा sdi_device अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा dss_device *dss;

	bool update_enabled;
	काष्ठा regulator *vdds_sdi_reg;

	काष्ठा dss_lcd_mgr_config mgr_config;
	अचिन्हित दीर्घ pixelघड़ी;
	पूर्णांक datapairs;

	काष्ठा omap_dss_device output;
	काष्ठा drm_bridge bridge;
पूर्ण;

#घोषणा drm_bridge_to_sdi(bridge) \
	container_of(bridge, काष्ठा sdi_device, bridge)

काष्ठा sdi_clk_calc_ctx अणु
	काष्ठा sdi_device *sdi;
	अचिन्हित दीर्घ pck_min, pck_max;

	अचिन्हित दीर्घ fck;
	काष्ठा dispc_घड़ी_info dispc_cinfo;
पूर्ण;

अटल bool dpi_calc_dispc_cb(पूर्णांक lckd, पूर्णांक pckd, अचिन्हित दीर्घ lck,
		अचिन्हित दीर्घ pck, व्योम *data)
अणु
	काष्ठा sdi_clk_calc_ctx *ctx = data;

	ctx->dispc_cinfo.lck_भाग = lckd;
	ctx->dispc_cinfo.pck_भाग = pckd;
	ctx->dispc_cinfo.lck = lck;
	ctx->dispc_cinfo.pck = pck;

	वापस true;
पूर्ण

अटल bool dpi_calc_dss_cb(अचिन्हित दीर्घ fck, व्योम *data)
अणु
	काष्ठा sdi_clk_calc_ctx *ctx = data;

	ctx->fck = fck;

	वापस dispc_भाग_calc(ctx->sdi->dss->dispc, fck,
			      ctx->pck_min, ctx->pck_max,
			      dpi_calc_dispc_cb, ctx);
पूर्ण

अटल पूर्णांक sdi_calc_घड़ी_भाग(काष्ठा sdi_device *sdi, अचिन्हित दीर्घ pclk,
			      अचिन्हित दीर्घ *fck,
			      काष्ठा dispc_घड़ी_info *dispc_cinfo)
अणु
	पूर्णांक i;
	काष्ठा sdi_clk_calc_ctx ctx;

	/*
	 * DSS fclk gives us very few possibilities, so finding a good pixel
	 * घड़ी may not be possible. We try multiple बार to find the घड़ी,
	 * each समय widening the pixel घड़ी range we look क्रम, up to
	 * +/- 1MHz.
	 */

	क्रम (i = 0; i < 10; ++i) अणु
		bool ok;

		स_रखो(&ctx, 0, माप(ctx));

		ctx.sdi = sdi;

		अगर (pclk > 1000 * i * i * i)
			ctx.pck_min = max(pclk - 1000 * i * i * i, 0lu);
		अन्यथा
			ctx.pck_min = 0;
		ctx.pck_max = pclk + 1000 * i * i * i;

		ok = dss_भाग_calc(sdi->dss, pclk, ctx.pck_min,
				  dpi_calc_dss_cb, &ctx);
		अगर (ok) अणु
			*fck = ctx.fck;
			*dispc_cinfo = ctx.dispc_cinfo;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम sdi_config_lcd_manager(काष्ठा sdi_device *sdi)
अणु
	sdi->mgr_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;

	sdi->mgr_config.stallmode = false;
	sdi->mgr_config.fअगरohandcheck = false;

	sdi->mgr_config.video_port_width = 24;
	sdi->mgr_config.lcden_sig_polarity = 1;

	dss_mgr_set_lcd_config(&sdi->output, &sdi->mgr_config);
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Bridge Operations
 */

अटल पूर्णांक sdi_bridge_attach(काष्ठा drm_bridge *bridge,
			     क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा sdi_device *sdi = drm_bridge_to_sdi(bridge);

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR))
		वापस -EINVAL;

	वापस drm_bridge_attach(bridge->encoder, sdi->output.next_bridge,
				 bridge, flags);
पूर्ण

अटल क्रमागत drm_mode_status
sdi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
		      स्थिर काष्ठा drm_display_info *info,
		      स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा sdi_device *sdi = drm_bridge_to_sdi(bridge);
	अचिन्हित दीर्घ pixelघड़ी = mode->घड़ी * 1000;
	काष्ठा dispc_घड़ी_info dispc_cinfo;
	अचिन्हित दीर्घ fck;
	पूर्णांक ret;

	अगर (pixelघड़ी == 0)
		वापस MODE_NOCLOCK;

	ret = sdi_calc_घड़ी_भाग(sdi, pixelघड़ी, &fck, &dispc_cinfo);
	अगर (ret < 0)
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल bool sdi_bridge_mode_fixup(काष्ठा drm_bridge *bridge,
				  स्थिर काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sdi_device *sdi = drm_bridge_to_sdi(bridge);
	अचिन्हित दीर्घ pixelघड़ी = mode->घड़ी * 1000;
	काष्ठा dispc_घड़ी_info dispc_cinfo;
	अचिन्हित दीर्घ fck;
	अचिन्हित दीर्घ pck;
	पूर्णांक ret;

	ret = sdi_calc_घड़ी_भाग(sdi, pixelघड़ी, &fck, &dispc_cinfo);
	अगर (ret < 0)
		वापस false;

	pck = fck / dispc_cinfo.lck_भाग / dispc_cinfo.pck_भाग;

	अगर (pck != pixelघड़ी)
		dev_dbg(&sdi->pdev->dev,
			"pixel clock adjusted from %lu Hz to %lu Hz\n",
			pixelघड़ी, pck);

	adjusted_mode->घड़ी = pck / 1000;

	वापस true;
पूर्ण

अटल व्योम sdi_bridge_mode_set(काष्ठा drm_bridge *bridge,
				स्थिर काष्ठा drm_display_mode *mode,
				स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sdi_device *sdi = drm_bridge_to_sdi(bridge);

	sdi->pixelघड़ी = adjusted_mode->घड़ी * 1000;
पूर्ण

अटल व्योम sdi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sdi_device *sdi = drm_bridge_to_sdi(bridge);
	काष्ठा dispc_घड़ी_info dispc_cinfo;
	अचिन्हित दीर्घ fck;
	पूर्णांक r;

	r = regulator_enable(sdi->vdds_sdi_reg);
	अगर (r)
		वापस;

	r = dispc_runसमय_get(sdi->dss->dispc);
	अगर (r)
		जाओ err_get_dispc;

	r = sdi_calc_घड़ी_भाग(sdi, sdi->pixelघड़ी, &fck, &dispc_cinfo);
	अगर (r)
		जाओ err_calc_घड़ी_भाग;

	sdi->mgr_config.घड़ी_info = dispc_cinfo;

	r = dss_set_fck_rate(sdi->dss, fck);
	अगर (r)
		जाओ err_set_dss_घड़ी_भाग;

	sdi_config_lcd_manager(sdi);

	/*
	 * LCLK and PCLK भागisors are located in shaकरोw रेजिस्टरs, and we
	 * normally ग_लिखो them to DISPC रेजिस्टरs when enabling the output.
	 * However, SDI uses pck-मुक्त as source घड़ी क्रम its PLL, and pck-मुक्त
	 * is affected by the भागisors. And as we need the PLL beक्रमe enabling
	 * the output, we need to ग_लिखो the भागisors early.
	 *
	 * It seems just writing to the DISPC रेजिस्टर is enough, and we करोn't
	 * need to care about the shaकरोw रेजिस्टर mechanism क्रम pck-मुक्त. The
	 * exact reason क्रम this is unknown.
	 */
	dispc_mgr_set_घड़ी_भाग(sdi->dss->dispc, sdi->output.dispc_channel,
				&sdi->mgr_config.घड़ी_info);

	dss_sdi_init(sdi->dss, sdi->datapairs);
	r = dss_sdi_enable(sdi->dss);
	अगर (r)
		जाओ err_sdi_enable;
	mdelay(2);

	r = dss_mgr_enable(&sdi->output);
	अगर (r)
		जाओ err_mgr_enable;

	वापस;

err_mgr_enable:
	dss_sdi_disable(sdi->dss);
err_sdi_enable:
err_set_dss_घड़ी_भाग:
err_calc_घड़ी_भाग:
	dispc_runसमय_put(sdi->dss->dispc);
err_get_dispc:
	regulator_disable(sdi->vdds_sdi_reg);
पूर्ण

अटल व्योम sdi_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sdi_device *sdi = drm_bridge_to_sdi(bridge);

	dss_mgr_disable(&sdi->output);

	dss_sdi_disable(sdi->dss);

	dispc_runसमय_put(sdi->dss->dispc);

	regulator_disable(sdi->vdds_sdi_reg);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs sdi_bridge_funcs = अणु
	.attach = sdi_bridge_attach,
	.mode_valid = sdi_bridge_mode_valid,
	.mode_fixup = sdi_bridge_mode_fixup,
	.mode_set = sdi_bridge_mode_set,
	.enable = sdi_bridge_enable,
	.disable = sdi_bridge_disable,
पूर्ण;

अटल व्योम sdi_bridge_init(काष्ठा sdi_device *sdi)
अणु
	sdi->bridge.funcs = &sdi_bridge_funcs;
	sdi->bridge.of_node = sdi->pdev->dev.of_node;
	sdi->bridge.type = DRM_MODE_CONNECTOR_LVDS;

	drm_bridge_add(&sdi->bridge);
पूर्ण

अटल व्योम sdi_bridge_cleanup(काष्ठा sdi_device *sdi)
अणु
	drm_bridge_हटाओ(&sdi->bridge);
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialisation and Cleanup
 */

अटल पूर्णांक sdi_init_output(काष्ठा sdi_device *sdi)
अणु
	काष्ठा omap_dss_device *out = &sdi->output;
	पूर्णांक r;

	sdi_bridge_init(sdi);

	out->dev = &sdi->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_SDI;
	out->type = OMAP_DISPLAY_TYPE_SDI;
	out->name = "sdi.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_LCD;
	/* We have SDI only on OMAP3, where it's on port 1 */
	out->of_port = 1;
	out->bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE	/* 15.5.9.1.2 */
		       | DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE;

	r = omapdss_device_init_output(out, &sdi->bridge);
	अगर (r < 0) अणु
		sdi_bridge_cleanup(sdi);
		वापस r;
	पूर्ण

	omapdss_device_रेजिस्टर(out);

	वापस 0;
पूर्ण

अटल व्योम sdi_uninit_output(काष्ठा sdi_device *sdi)
अणु
	omapdss_device_unरेजिस्टर(&sdi->output);
	omapdss_device_cleanup_output(&sdi->output);

	sdi_bridge_cleanup(sdi);
पूर्ण

पूर्णांक sdi_init_port(काष्ठा dss_device *dss, काष्ठा platक्रमm_device *pdev,
		  काष्ठा device_node *port)
अणु
	काष्ठा sdi_device *sdi;
	काष्ठा device_node *ep;
	u32 datapairs;
	पूर्णांक r;

	sdi = kzalloc(माप(*sdi), GFP_KERNEL);
	अगर (!sdi)
		वापस -ENOMEM;

	ep = of_get_next_child(port, शून्य);
	अगर (!ep) अणु
		r = 0;
		जाओ err_मुक्त;
	पूर्ण

	r = of_property_पढ़ो_u32(ep, "datapairs", &datapairs);
	of_node_put(ep);
	अगर (r) अणु
		DSSERR("failed to parse datapairs\n");
		जाओ err_मुक्त;
	पूर्ण

	sdi->datapairs = datapairs;
	sdi->dss = dss;

	sdi->pdev = pdev;
	port->data = sdi;

	sdi->vdds_sdi_reg = devm_regulator_get(&pdev->dev, "vdds_sdi");
	अगर (IS_ERR(sdi->vdds_sdi_reg)) अणु
		r = PTR_ERR(sdi->vdds_sdi_reg);
		अगर (r != -EPROBE_DEFER)
			DSSERR("can't get VDDS_SDI regulator\n");
		जाओ err_मुक्त;
	पूर्ण

	r = sdi_init_output(sdi);
	अगर (r)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	kमुक्त(sdi);

	वापस r;
पूर्ण

व्योम sdi_uninit_port(काष्ठा device_node *port)
अणु
	काष्ठा sdi_device *sdi = port->data;

	अगर (!sdi)
		वापस;

	sdi_uninit_output(sdi);
	kमुक्त(sdi);
पूर्ण
