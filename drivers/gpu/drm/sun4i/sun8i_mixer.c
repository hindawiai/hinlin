<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on sun4i_backend.c, which is:
 *   Copyright (C) 2015 Free Electrons
 *   Copyright (C) 2015 NextThing Co
 */

#समावेश <linux/component.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "sun4i_drv.h"
#समावेश "sun8i_mixer.h"
#समावेश "sun8i_ui_layer.h"
#समावेश "sun8i_vi_layer.h"
#समावेश "sunxi_engine.h"

काष्ठा de2_fmt_info अणु
	u32	drm_fmt;
	u32	de2_fmt;
पूर्ण;

अटल स्थिर काष्ठा de2_fmt_info de2_क्रमmats[] = अणु
	अणु
		.drm_fmt = DRM_FORMAT_ARGB8888,
		.de2_fmt = SUN8I_MIXER_FBFMT_ARGB8888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_ABGR8888,
		.de2_fmt = SUN8I_MIXER_FBFMT_ABGR8888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_RGBA8888,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGBA8888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_BGRA8888,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGRA8888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_XRGB8888,
		.de2_fmt = SUN8I_MIXER_FBFMT_XRGB8888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_XBGR8888,
		.de2_fmt = SUN8I_MIXER_FBFMT_XBGR8888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_RGBX8888,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGBX8888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_BGRX8888,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGRX8888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_RGB888,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGB888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_BGR888,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGR888,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_RGB565,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGB565,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_BGR565,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGR565,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_ARGB4444,
		.de2_fmt = SUN8I_MIXER_FBFMT_ARGB4444,
	पूर्ण,
	अणु
		/* क्रम DE2 VI layer which ignores alpha */
		.drm_fmt = DRM_FORMAT_XRGB4444,
		.de2_fmt = SUN8I_MIXER_FBFMT_ARGB4444,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_ABGR4444,
		.de2_fmt = SUN8I_MIXER_FBFMT_ABGR4444,
	पूर्ण,
	अणु
		/* क्रम DE2 VI layer which ignores alpha */
		.drm_fmt = DRM_FORMAT_XBGR4444,
		.de2_fmt = SUN8I_MIXER_FBFMT_ABGR4444,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_RGBA4444,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGBA4444,
	पूर्ण,
	अणु
		/* क्रम DE2 VI layer which ignores alpha */
		.drm_fmt = DRM_FORMAT_RGBX4444,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGBA4444,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_BGRA4444,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGRA4444,
	पूर्ण,
	अणु
		/* क्रम DE2 VI layer which ignores alpha */
		.drm_fmt = DRM_FORMAT_BGRX4444,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGRA4444,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_ARGB1555,
		.de2_fmt = SUN8I_MIXER_FBFMT_ARGB1555,
	पूर्ण,
	अणु
		/* क्रम DE2 VI layer which ignores alpha */
		.drm_fmt = DRM_FORMAT_XRGB1555,
		.de2_fmt = SUN8I_MIXER_FBFMT_ARGB1555,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_ABGR1555,
		.de2_fmt = SUN8I_MIXER_FBFMT_ABGR1555,
	पूर्ण,
	अणु
		/* क्रम DE2 VI layer which ignores alpha */
		.drm_fmt = DRM_FORMAT_XBGR1555,
		.de2_fmt = SUN8I_MIXER_FBFMT_ABGR1555,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_RGBA5551,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGBA5551,
	पूर्ण,
	अणु
		/* क्रम DE2 VI layer which ignores alpha */
		.drm_fmt = DRM_FORMAT_RGBX5551,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGBA5551,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_BGRA5551,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGRA5551,
	पूर्ण,
	अणु
		/* क्रम DE2 VI layer which ignores alpha */
		.drm_fmt = DRM_FORMAT_BGRX5551,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGRA5551,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_ARGB2101010,
		.de2_fmt = SUN8I_MIXER_FBFMT_ARGB2101010,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_ABGR2101010,
		.de2_fmt = SUN8I_MIXER_FBFMT_ABGR2101010,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_RGBA1010102,
		.de2_fmt = SUN8I_MIXER_FBFMT_RGBA1010102,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_BGRA1010102,
		.de2_fmt = SUN8I_MIXER_FBFMT_BGRA1010102,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_UYVY,
		.de2_fmt = SUN8I_MIXER_FBFMT_UYVY,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_VYUY,
		.de2_fmt = SUN8I_MIXER_FBFMT_VYUY,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_YUYV,
		.de2_fmt = SUN8I_MIXER_FBFMT_YUYV,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_YVYU,
		.de2_fmt = SUN8I_MIXER_FBFMT_YVYU,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_NV16,
		.de2_fmt = SUN8I_MIXER_FBFMT_NV16,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_NV61,
		.de2_fmt = SUN8I_MIXER_FBFMT_NV61,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_NV12,
		.de2_fmt = SUN8I_MIXER_FBFMT_NV12,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_NV21,
		.de2_fmt = SUN8I_MIXER_FBFMT_NV21,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_YUV422,
		.de2_fmt = SUN8I_MIXER_FBFMT_YUV422,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_YUV420,
		.de2_fmt = SUN8I_MIXER_FBFMT_YUV420,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_YUV411,
		.de2_fmt = SUN8I_MIXER_FBFMT_YUV411,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_YVU422,
		.de2_fmt = SUN8I_MIXER_FBFMT_YUV422,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_YVU420,
		.de2_fmt = SUN8I_MIXER_FBFMT_YUV420,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_YVU411,
		.de2_fmt = SUN8I_MIXER_FBFMT_YUV411,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_P010,
		.de2_fmt = SUN8I_MIXER_FBFMT_P010_YUV,
	पूर्ण,
	अणु
		.drm_fmt = DRM_FORMAT_P210,
		.de2_fmt = SUN8I_MIXER_FBFMT_P210_YUV,
	पूर्ण,
पूर्ण;

पूर्णांक sun8i_mixer_drm_क्रमmat_to_hw(u32 क्रमmat, u32 *hw_क्रमmat)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(de2_क्रमmats); ++i)
		अगर (de2_क्रमmats[i].drm_fmt == क्रमmat) अणु
			*hw_क्रमmat = de2_क्रमmats[i].de2_fmt;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम sun8i_mixer_commit(काष्ठा sunxi_engine *engine)
अणु
	DRM_DEBUG_DRIVER("Committing changes\n");

	regmap_ग_लिखो(engine->regs, SUN8I_MIXER_GLOBAL_DBUFF,
		     SUN8I_MIXER_GLOBAL_DBUFF_ENABLE);
पूर्ण

अटल काष्ठा drm_plane **sun8i_layers_init(काष्ठा drm_device *drm,
					    काष्ठा sunxi_engine *engine)
अणु
	काष्ठा drm_plane **planes;
	काष्ठा sun8i_mixer *mixer = engine_to_sun8i_mixer(engine);
	पूर्णांक i;

	planes = devm_kसुस्मृति(drm->dev,
			      mixer->cfg->vi_num + mixer->cfg->ui_num + 1,
			      माप(*planes), GFP_KERNEL);
	अगर (!planes)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < mixer->cfg->vi_num; i++) अणु
		काष्ठा sun8i_vi_layer *layer;

		layer = sun8i_vi_layer_init_one(drm, mixer, i);
		अगर (IS_ERR(layer)) अणु
			dev_err(drm->dev,
				"Couldn't initialize overlay plane\n");
			वापस ERR_CAST(layer);
		पूर्ण

		planes[i] = &layer->plane;
	पूर्ण

	क्रम (i = 0; i < mixer->cfg->ui_num; i++) अणु
		काष्ठा sun8i_ui_layer *layer;

		layer = sun8i_ui_layer_init_one(drm, mixer, i);
		अगर (IS_ERR(layer)) अणु
			dev_err(drm->dev, "Couldn't initialize %s plane\n",
				i ? "overlay" : "primary");
			वापस ERR_CAST(layer);
		पूर्ण

		planes[mixer->cfg->vi_num + i] = &layer->plane;
	पूर्ण

	वापस planes;
पूर्ण

अटल स्थिर काष्ठा sunxi_engine_ops sun8i_engine_ops = अणु
	.commit		= sun8i_mixer_commit,
	.layers_init	= sun8i_layers_init,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun8i_mixer_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= 0xffffc, /* guessed */
पूर्ण;

अटल पूर्णांक sun8i_mixer_of_get_id(काष्ठा device_node *node)
अणु
	काष्ठा device_node *ep, *remote;
	काष्ठा of_endpoपूर्णांक of_ep;

	/* Output port is 1, and we want the first endpoपूर्णांक. */
	ep = of_graph_get_endpoपूर्णांक_by_regs(node, 1, -1);
	अगर (!ep)
		वापस -EINVAL;

	remote = of_graph_get_remote_endpoपूर्णांक(ep);
	of_node_put(ep);
	अगर (!remote)
		वापस -EINVAL;

	of_graph_parse_endpoपूर्णांक(remote, &of_ep);
	of_node_put(remote);
	वापस of_ep.id;
पूर्ण

अटल पूर्णांक sun8i_mixer_bind(काष्ठा device *dev, काष्ठा device *master,
			      व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा sun4i_drv *drv = drm->dev_निजी;
	काष्ठा sun8i_mixer *mixer;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक base;
	पूर्णांक plane_cnt;
	पूर्णांक i, ret;

	/*
	 * The mixer uses single 32-bit रेजिस्टर to store memory
	 * addresses, so that it cannot deal with 64-bit memory
	 * addresses.
	 * Restrict the DMA mask so that the mixer won't be
	 * allocated some memory that is too high.
	 */
	ret = dma_set_mask(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "Cannot do 32-bit DMA.\n");
		वापस ret;
	पूर्ण

	mixer = devm_kzalloc(dev, माप(*mixer), GFP_KERNEL);
	अगर (!mixer)
		वापस -ENOMEM;
	dev_set_drvdata(dev, mixer);
	mixer->engine.ops = &sun8i_engine_ops;
	mixer->engine.node = dev->of_node;

	अगर (of_find_property(dev->of_node, "iommus", शून्य)) अणु
		/*
		 * This assume we have the same DMA स्थिरraपूर्णांकs क्रम
		 * all our the mixers in our pipeline. This sounds
		 * bad, but it has always been the हाल क्रम us, and
		 * DRM करोesn't करो per-device allocation either, so we
		 * would need to fix DRM first...
		 */
		ret = of_dma_configure(drm->dev, dev->of_node, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * While this function can fail, we shouldn't करो anything
	 * अगर this happens. Some early DE2 DT entries करोn't provide
	 * mixer id but work nevertheless because matching between
	 * TCON and mixer is करोne by comparing node poपूर्णांकers (old
	 * way) instead comparing ids. If this function fails and
	 * id is needed, it will fail during id matching anyway.
	 */
	mixer->engine.id = sun8i_mixer_of_get_id(dev->of_node);

	mixer->cfg = of_device_get_match_data(dev);
	अगर (!mixer->cfg)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	mixer->engine.regs = devm_regmap_init_mmio(dev, regs,
						   &sun8i_mixer_regmap_config);
	अगर (IS_ERR(mixer->engine.regs)) अणु
		dev_err(dev, "Couldn't create the mixer regmap\n");
		वापस PTR_ERR(mixer->engine.regs);
	पूर्ण

	mixer->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(mixer->reset)) अणु
		dev_err(dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(mixer->reset);
	पूर्ण

	ret = reset_control_deनिश्चित(mixer->reset);
	अगर (ret) अणु
		dev_err(dev, "Couldn't deassert our reset line\n");
		वापस ret;
	पूर्ण

	mixer->bus_clk = devm_clk_get(dev, "bus");
	अगर (IS_ERR(mixer->bus_clk)) अणु
		dev_err(dev, "Couldn't get the mixer bus clock\n");
		ret = PTR_ERR(mixer->bus_clk);
		जाओ err_निश्चित_reset;
	पूर्ण
	clk_prepare_enable(mixer->bus_clk);

	mixer->mod_clk = devm_clk_get(dev, "mod");
	अगर (IS_ERR(mixer->mod_clk)) अणु
		dev_err(dev, "Couldn't get the mixer module clock\n");
		ret = PTR_ERR(mixer->mod_clk);
		जाओ err_disable_bus_clk;
	पूर्ण

	/*
	 * It seems that we need to enक्रमce that rate क्रम whatever
	 * reason क्रम the mixer to be functional. Make sure it's the
	 * हाल.
	 */
	अगर (mixer->cfg->mod_rate)
		clk_set_rate(mixer->mod_clk, mixer->cfg->mod_rate);

	clk_prepare_enable(mixer->mod_clk);

	list_add_tail(&mixer->engine.list, &drv->engine_list);

	base = sun8i_blender_base(mixer);

	/* Reset रेजिस्टरs and disable unused sub-engines */
	अगर (mixer->cfg->is_de3) अणु
		क्रम (i = 0; i < DE3_MIXER_UNIT_SIZE; i += 4)
			regmap_ग_लिखो(mixer->engine.regs, i, 0);

		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_FCE_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_PEAK_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_LCTI_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_BLS_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_FCC_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_DNS_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_DRC_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_FMT_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_CDC0_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN50I_MIXER_CDC1_EN, 0);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < DE2_MIXER_UNIT_SIZE; i += 4)
			regmap_ग_लिखो(mixer->engine.regs, i, 0);

		regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_FCE_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_BWS_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_LTI_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_PEAK_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_ASE_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_FCC_EN, 0);
		regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_DCSC_EN, 0);
	पूर्ण

	/* Enable the mixer */
	regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_GLOBAL_CTL,
		     SUN8I_MIXER_GLOBAL_CTL_RT_EN);

	/* Set background color to black */
	regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_BLEND_BKCOLOR(base),
		     SUN8I_MIXER_BLEND_COLOR_BLACK);

	/*
	 * Set fill color of bottom plane to black. Generally not needed
	 * except when VI plane is at bottom (zpos = 0) and enabled.
	 */
	regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_BLEND_PIPE_CTL(base),
		     SUN8I_MIXER_BLEND_PIPE_CTL_FC_EN(0));
	regmap_ग_लिखो(mixer->engine.regs, SUN8I_MIXER_BLEND_ATTR_FCOLOR(base, 0),
		     SUN8I_MIXER_BLEND_COLOR_BLACK);

	plane_cnt = mixer->cfg->vi_num + mixer->cfg->ui_num;
	क्रम (i = 0; i < plane_cnt; i++)
		regmap_ग_लिखो(mixer->engine.regs,
			     SUN8I_MIXER_BLEND_MODE(base, i),
			     SUN8I_MIXER_BLEND_MODE_DEF);

	regmap_update_bits(mixer->engine.regs, SUN8I_MIXER_BLEND_PIPE_CTL(base),
			   SUN8I_MIXER_BLEND_PIPE_CTL_EN_MSK, 0);

	वापस 0;

err_disable_bus_clk:
	clk_disable_unprepare(mixer->bus_clk);
err_निश्चित_reset:
	reset_control_निश्चित(mixer->reset);
	वापस ret;
पूर्ण

अटल व्योम sun8i_mixer_unbind(काष्ठा device *dev, काष्ठा device *master,
				 व्योम *data)
अणु
	काष्ठा sun8i_mixer *mixer = dev_get_drvdata(dev);

	list_del(&mixer->engine.list);

	clk_disable_unprepare(mixer->mod_clk);
	clk_disable_unprepare(mixer->bus_clk);
	reset_control_निश्चित(mixer->reset);
पूर्ण

अटल स्थिर काष्ठा component_ops sun8i_mixer_ops = अणु
	.bind	= sun8i_mixer_bind,
	.unbind	= sun8i_mixer_unbind,
पूर्ण;

अटल पूर्णांक sun8i_mixer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sun8i_mixer_ops);
पूर्ण

अटल पूर्णांक sun8i_mixer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun8i_mixer_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun8i_mixer_cfg sun8i_a83t_mixer0_cfg = अणु
	.ccsc		= 0,
	.scaler_mask	= 0xf,
	.scanline_yuv	= 2048,
	.ui_num		= 3,
	.vi_num		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun8i_mixer_cfg sun8i_a83t_mixer1_cfg = अणु
	.ccsc		= 1,
	.scaler_mask	= 0x3,
	.scanline_yuv	= 2048,
	.ui_num		= 1,
	.vi_num		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun8i_mixer_cfg sun8i_h3_mixer0_cfg = अणु
	.ccsc		= 0,
	.mod_rate	= 432000000,
	.scaler_mask	= 0xf,
	.scanline_yuv	= 2048,
	.ui_num		= 3,
	.vi_num		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun8i_mixer_cfg sun8i_r40_mixer0_cfg = अणु
	.ccsc		= 0,
	.mod_rate	= 297000000,
	.scaler_mask	= 0xf,
	.scanline_yuv	= 2048,
	.ui_num		= 3,
	.vi_num		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun8i_mixer_cfg sun8i_r40_mixer1_cfg = अणु
	.ccsc		= 1,
	.mod_rate	= 297000000,
	.scaler_mask	= 0x3,
	.scanline_yuv	= 2048,
	.ui_num		= 1,
	.vi_num		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun8i_mixer_cfg sun8i_v3s_mixer_cfg = अणु
	.vi_num = 2,
	.ui_num = 1,
	.scaler_mask = 0x3,
	.scanline_yuv = 2048,
	.ccsc = 0,
	.mod_rate = 150000000,
पूर्ण;

अटल स्थिर काष्ठा sun8i_mixer_cfg sun50i_a64_mixer0_cfg = अणु
	.ccsc		= 0,
	.mod_rate	= 297000000,
	.scaler_mask	= 0xf,
	.scanline_yuv	= 4096,
	.ui_num		= 3,
	.vi_num		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun8i_mixer_cfg sun50i_a64_mixer1_cfg = अणु
	.ccsc		= 1,
	.mod_rate	= 297000000,
	.scaler_mask	= 0x3,
	.scanline_yuv	= 2048,
	.ui_num		= 1,
	.vi_num		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun8i_mixer_cfg sun50i_h6_mixer0_cfg = अणु
	.ccsc		= 0,
	.is_de3		= true,
	.mod_rate	= 600000000,
	.scaler_mask	= 0xf,
	.scanline_yuv	= 4096,
	.ui_num		= 3,
	.vi_num		= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun8i_mixer_of_table[] = अणु
	अणु
		.compatible = "allwinner,sun8i-a83t-de2-mixer-0",
		.data = &sun8i_a83t_mixer0_cfg,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a83t-de2-mixer-1",
		.data = &sun8i_a83t_mixer1_cfg,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-de2-mixer-0",
		.data = &sun8i_h3_mixer0_cfg,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-r40-de2-mixer-0",
		.data = &sun8i_r40_mixer0_cfg,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-r40-de2-mixer-1",
		.data = &sun8i_r40_mixer1_cfg,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-v3s-de2-mixer",
		.data = &sun8i_v3s_mixer_cfg,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-a64-de2-mixer-0",
		.data = &sun50i_a64_mixer0_cfg,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-a64-de2-mixer-1",
		.data = &sun50i_a64_mixer1_cfg,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h6-de3-mixer-0",
		.data = &sun50i_h6_mixer0_cfg,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun8i_mixer_of_table);

अटल काष्ठा platक्रमm_driver sun8i_mixer_platक्रमm_driver = अणु
	.probe		= sun8i_mixer_probe,
	.हटाओ		= sun8i_mixer_हटाओ,
	.driver		= अणु
		.name		= "sun8i-mixer",
		.of_match_table	= sun8i_mixer_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun8i_mixer_platक्रमm_driver);

MODULE_AUTHOR("Icenowy Zheng <icenowy@aosc.io>");
MODULE_DESCRIPTION("Allwinner DE2 Mixer driver");
MODULE_LICENSE("GPL");
