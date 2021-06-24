<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/sdi.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 */

#घोषणा DSS_SUBSYS_NAME "SDI"

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>
#समावेश <linux/component.h>

#समावेश <video/omapfb_dss.h>
#समावेश "dss.h"

अटल काष्ठा अणु
	काष्ठा platक्रमm_device *pdev;

	bool update_enabled;
	काष्ठा regulator *vdds_sdi_reg;

	काष्ठा dss_lcd_mgr_config mgr_config;
	काष्ठा omap_video_timings timings;
	पूर्णांक datapairs;

	काष्ठा omap_dss_device output;

	bool port_initialized;
पूर्ण sdi;

काष्ठा sdi_clk_calc_ctx अणु
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

	वापस dispc_भाग_calc(fck, ctx->pck_min, ctx->pck_max,
			dpi_calc_dispc_cb, ctx);
पूर्ण

अटल पूर्णांक sdi_calc_घड़ी_भाग(अचिन्हित दीर्घ pclk,
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
		अगर (pclk > 1000 * i * i * i)
			ctx.pck_min = max(pclk - 1000 * i * i * i, 0lu);
		अन्यथा
			ctx.pck_min = 0;
		ctx.pck_max = pclk + 1000 * i * i * i;

		ok = dss_भाग_calc(pclk, ctx.pck_min, dpi_calc_dss_cb, &ctx);
		अगर (ok) अणु
			*fck = ctx.fck;
			*dispc_cinfo = ctx.dispc_cinfo;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम sdi_config_lcd_manager(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_overlay_manager *mgr = sdi.output.manager;

	sdi.mgr_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;

	sdi.mgr_config.stallmode = false;
	sdi.mgr_config.fअगरohandcheck = false;

	sdi.mgr_config.video_port_width = 24;
	sdi.mgr_config.lcden_sig_polarity = 1;

	dss_mgr_set_lcd_config(mgr, &sdi.mgr_config);
पूर्ण

अटल पूर्णांक sdi_display_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_dss_device *out = &sdi.output;
	काष्ठा omap_video_timings *t = &sdi.timings;
	अचिन्हित दीर्घ fck;
	काष्ठा dispc_घड़ी_info dispc_cinfo;
	अचिन्हित दीर्घ pck;
	पूर्णांक r;

	अगर (out->manager == शून्य) अणु
		DSSERR("failed to enable display: no output/manager\n");
		वापस -ENODEV;
	पूर्ण

	r = regulator_enable(sdi.vdds_sdi_reg);
	अगर (r)
		जाओ err_reg_enable;

	r = dispc_runसमय_get();
	अगर (r)
		जाओ err_get_dispc;

	/* 15.5.9.1.2 */
	t->data_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
	t->sync_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;

	r = sdi_calc_घड़ी_भाग(t->pixelघड़ी, &fck, &dispc_cinfo);
	अगर (r)
		जाओ err_calc_घड़ी_भाग;

	sdi.mgr_config.घड़ी_info = dispc_cinfo;

	pck = fck / dispc_cinfo.lck_भाग / dispc_cinfo.pck_भाग;

	अगर (pck != t->pixelघड़ी) अणु
		DSSWARN("Could not find exact pixel clock. Requested %d Hz, got %lu Hz\n",
			t->pixelघड़ी, pck);

		t->pixelघड़ी = pck;
	पूर्ण


	dss_mgr_set_timings(out->manager, t);

	r = dss_set_fck_rate(fck);
	अगर (r)
		जाओ err_set_dss_घड़ी_भाग;

	sdi_config_lcd_manager(dssdev);

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
	dispc_mgr_set_घड़ी_भाग(out->manager->id, &sdi.mgr_config.घड़ी_info);

	dss_sdi_init(sdi.datapairs);
	r = dss_sdi_enable();
	अगर (r)
		जाओ err_sdi_enable;
	mdelay(2);

	r = dss_mgr_enable(out->manager);
	अगर (r)
		जाओ err_mgr_enable;

	वापस 0;

err_mgr_enable:
	dss_sdi_disable();
err_sdi_enable:
err_set_dss_घड़ी_भाग:
err_calc_घड़ी_भाग:
	dispc_runसमय_put();
err_get_dispc:
	regulator_disable(sdi.vdds_sdi_reg);
err_reg_enable:
	वापस r;
पूर्ण

अटल व्योम sdi_display_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_overlay_manager *mgr = sdi.output.manager;

	dss_mgr_disable(mgr);

	dss_sdi_disable();

	dispc_runसमय_put();

	regulator_disable(sdi.vdds_sdi_reg);
पूर्ण

अटल व्योम sdi_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	sdi.timings = *timings;
पूर्ण

अटल व्योम sdi_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	*timings = sdi.timings;
पूर्ण

अटल पूर्णांक sdi_check_timings(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings)
अणु
	काष्ठा omap_overlay_manager *mgr = sdi.output.manager;

	अगर (mgr && !dispc_mgr_timings_ok(mgr->id, timings))
		वापस -EINVAL;

	अगर (timings->pixelघड़ी == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम sdi_set_datapairs(काष्ठा omap_dss_device *dssdev, पूर्णांक datapairs)
अणु
	sdi.datapairs = datapairs;
पूर्ण

अटल पूर्णांक sdi_init_regulator(व्योम)
अणु
	काष्ठा regulator *vdds_sdi;

	अगर (sdi.vdds_sdi_reg)
		वापस 0;

	vdds_sdi = devm_regulator_get(&sdi.pdev->dev, "vdds_sdi");
	अगर (IS_ERR(vdds_sdi)) अणु
		अगर (PTR_ERR(vdds_sdi) != -EPROBE_DEFER)
			DSSERR("can't get VDDS_SDI regulator\n");
		वापस PTR_ERR(vdds_sdi);
	पूर्ण

	sdi.vdds_sdi_reg = vdds_sdi;

	वापस 0;
पूर्ण

अटल पूर्णांक sdi_connect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा omap_overlay_manager *mgr;
	पूर्णांक r;

	r = sdi_init_regulator();
	अगर (r)
		वापस r;

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

अटल व्योम sdi_disconnect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	WARN_ON(dst != dssdev->dst);

	अगर (dst != dssdev->dst)
		वापस;

	omapdss_output_unset_device(dssdev);

	अगर (dssdev->manager)
		dss_mgr_disconnect(dssdev->manager, dssdev);
पूर्ण

अटल स्थिर काष्ठा omapdss_sdi_ops sdi_ops = अणु
	.connect = sdi_connect,
	.disconnect = sdi_disconnect,

	.enable = sdi_display_enable,
	.disable = sdi_display_disable,

	.check_timings = sdi_check_timings,
	.set_timings = sdi_set_timings,
	.get_timings = sdi_get_timings,

	.set_datapairs = sdi_set_datapairs,
पूर्ण;

अटल व्योम sdi_init_output(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *out = &sdi.output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_SDI;
	out->output_type = OMAP_DISPLAY_TYPE_SDI;
	out->name = "sdi.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_LCD;
	/* We have SDI only on OMAP3, where it's on port 1 */
	out->port_num = 1;
	out->ops.sdi = &sdi_ops;
	out->owner = THIS_MODULE;

	omapdss_रेजिस्टर_output(out);
पूर्ण

अटल व्योम sdi_uninit_output(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *out = &sdi.output;

	omapdss_unरेजिस्टर_output(out);
पूर्ण

अटल पूर्णांक sdi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	sdi.pdev = pdev;

	sdi_init_output(pdev);

	वापस 0;
पूर्ण

अटल व्योम sdi_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	sdi_uninit_output(pdev);
पूर्ण

अटल स्थिर काष्ठा component_ops sdi_component_ops = अणु
	.bind	= sdi_bind,
	.unbind	= sdi_unbind,
पूर्ण;

अटल पूर्णांक sdi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sdi_component_ops);
पूर्ण

अटल पूर्णांक sdi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sdi_component_ops);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_sdi_driver = अणु
	.probe		= sdi_probe,
	.हटाओ         = sdi_हटाओ,
	.driver         = अणु
		.name   = "omapdss_sdi",
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

पूर्णांक __init sdi_init_platक्रमm_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_sdi_driver);
पूर्ण

व्योम sdi_uninit_platक्रमm_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_sdi_driver);
पूर्ण

पूर्णांक sdi_init_port(काष्ठा platक्रमm_device *pdev, काष्ठा device_node *port)
अणु
	काष्ठा device_node *ep;
	u32 datapairs;
	पूर्णांक r;

	ep = omapdss_of_get_next_endpoपूर्णांक(port, शून्य);
	अगर (!ep)
		वापस 0;

	r = of_property_पढ़ो_u32(ep, "datapairs", &datapairs);
	अगर (r) अणु
		DSSERR("failed to parse datapairs\n");
		जाओ err_datapairs;
	पूर्ण

	sdi.datapairs = datapairs;

	of_node_put(ep);

	sdi.pdev = pdev;

	sdi_init_output(pdev);

	sdi.port_initialized = true;

	वापस 0;

err_datapairs:
	of_node_put(ep);

	वापस r;
पूर्ण

व्योम sdi_uninit_port(काष्ठा device_node *port)
अणु
	अगर (!sdi.port_initialized)
		वापस;

	sdi_uninit_output(sdi.pdev);
पूर्ण
