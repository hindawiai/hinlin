<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARC PGU DRM driver.
 *
 * Copyright (C) 2016 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/clk.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>

#घोषणा ARCPGU_REG_CTRL		0x00
#घोषणा ARCPGU_REG_STAT		0x04
#घोषणा ARCPGU_REG_FMT		0x10
#घोषणा ARCPGU_REG_HSYNC	0x14
#घोषणा ARCPGU_REG_VSYNC	0x18
#घोषणा ARCPGU_REG_ACTIVE	0x1c
#घोषणा ARCPGU_REG_BUF0_ADDR	0x40
#घोषणा ARCPGU_REG_STRIDE	0x50
#घोषणा ARCPGU_REG_START_SET	0x84

#घोषणा ARCPGU_REG_ID		0x3FC

#घोषणा ARCPGU_CTRL_ENABLE_MASK	0x02
#घोषणा ARCPGU_CTRL_VS_POL_MASK	0x1
#घोषणा ARCPGU_CTRL_VS_POL_OFST	0x3
#घोषणा ARCPGU_CTRL_HS_POL_MASK	0x1
#घोषणा ARCPGU_CTRL_HS_POL_OFST	0x4
#घोषणा ARCPGU_MODE_XRGB8888	BIT(2)
#घोषणा ARCPGU_STAT_BUSY_MASK	0x02

काष्ठा arcpgu_drm_निजी अणु
	काष्ठा drm_device	drm;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	काष्ठा drm_simple_display_pipe pipe;
	काष्ठा drm_connector	sim_conn;
पूर्ण;

#घोषणा dev_to_arcpgu(x) container_of(x, काष्ठा arcpgu_drm_निजी, drm)

#घोषणा pipe_to_arcpgu_priv(x) container_of(x, काष्ठा arcpgu_drm_निजी, pipe)

अटल अंतरभूत व्योम arc_pgu_ग_लिखो(काष्ठा arcpgu_drm_निजी *arcpgu,
				 अचिन्हित पूर्णांक reg, u32 value)
अणु
	ioग_लिखो32(value, arcpgu->regs + reg);
पूर्ण

अटल अंतरभूत u32 arc_pgu_पढ़ो(काष्ठा arcpgu_drm_निजी *arcpgu,
			       अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32(arcpgu->regs + reg);
पूर्ण

#घोषणा XRES_DEF	640
#घोषणा YRES_DEF	480

#घोषणा XRES_MAX	8192
#घोषणा YRES_MAX	8192

अटल पूर्णांक arcpgu_drm_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक count;

	count = drm_add_modes_noedid(connector, XRES_MAX, YRES_MAX);
	drm_set_preferred_mode(connector, XRES_DEF, YRES_DEF);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs
arcpgu_drm_connector_helper_funcs = अणु
	.get_modes = arcpgu_drm_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs arcpgu_drm_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक arcpgu_drm_sim_init(काष्ठा drm_device *drm, काष्ठा drm_connector *connector)
अणु
	drm_connector_helper_add(connector, &arcpgu_drm_connector_helper_funcs);
	वापस drm_connector_init(drm, connector, &arcpgu_drm_connector_funcs,
				  DRM_MODE_CONNECTOR_VIRTUAL);
पूर्ण

#घोषणा ENCODE_PGU_XY(x, y)	((((x) - 1) << 16) | ((y) - 1))

अटल स्थिर u32 arc_pgu_supported_क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल व्योम arc_pgu_set_pxl_fmt(काष्ठा arcpgu_drm_निजी *arcpgu)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = arcpgu->pipe.plane.state->fb;
	uपूर्णांक32_t pixel_क्रमmat = fb->क्रमmat->क्रमmat;
	u32 क्रमmat = DRM_FORMAT_INVALID;
	पूर्णांक i;
	u32 reg_ctrl;

	क्रम (i = 0; i < ARRAY_SIZE(arc_pgu_supported_क्रमmats); i++) अणु
		अगर (arc_pgu_supported_क्रमmats[i] == pixel_क्रमmat)
			क्रमmat = arc_pgu_supported_क्रमmats[i];
	पूर्ण

	अगर (WARN_ON(क्रमmat == DRM_FORMAT_INVALID))
		वापस;

	reg_ctrl = arc_pgu_पढ़ो(arcpgu, ARCPGU_REG_CTRL);
	अगर (क्रमmat == DRM_FORMAT_RGB565)
		reg_ctrl &= ~ARCPGU_MODE_XRGB8888;
	अन्यथा
		reg_ctrl |= ARCPGU_MODE_XRGB8888;
	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_CTRL, reg_ctrl);
पूर्ण

अटल क्रमागत drm_mode_status arc_pgu_mode_valid(काष्ठा drm_simple_display_pipe *pipe,
					       स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा arcpgu_drm_निजी *arcpgu = pipe_to_arcpgu_priv(pipe);
	दीर्घ rate, clk_rate = mode->घड़ी * 1000;
	दीर्घ dअगरf = clk_rate / 200; /* +-0.5% allowed by HDMI spec */

	rate = clk_round_rate(arcpgu->clk, clk_rate);
	अगर ((max(rate, clk_rate) - min(rate, clk_rate) < dअगरf) && (rate > 0))
		वापस MODE_OK;

	वापस MODE_NOCLOCK;
पूर्ण

अटल व्योम arc_pgu_mode_set(काष्ठा arcpgu_drm_निजी *arcpgu)
अणु
	काष्ठा drm_display_mode *m = &arcpgu->pipe.crtc.state->adjusted_mode;
	u32 val;

	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_FMT,
		      ENCODE_PGU_XY(m->crtc_htotal, m->crtc_vtotal));

	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_HSYNC,
		      ENCODE_PGU_XY(m->crtc_hsync_start - m->crtc_hdisplay,
				    m->crtc_hsync_end - m->crtc_hdisplay));

	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_VSYNC,
		      ENCODE_PGU_XY(m->crtc_vsync_start - m->crtc_vdisplay,
				    m->crtc_vsync_end - m->crtc_vdisplay));

	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_ACTIVE,
		      ENCODE_PGU_XY(m->crtc_hblank_end - m->crtc_hblank_start,
				    m->crtc_vblank_end - m->crtc_vblank_start));

	val = arc_pgu_पढ़ो(arcpgu, ARCPGU_REG_CTRL);

	अगर (m->flags & DRM_MODE_FLAG_PVSYNC)
		val |= ARCPGU_CTRL_VS_POL_MASK << ARCPGU_CTRL_VS_POL_OFST;
	अन्यथा
		val &= ~(ARCPGU_CTRL_VS_POL_MASK << ARCPGU_CTRL_VS_POL_OFST);

	अगर (m->flags & DRM_MODE_FLAG_PHSYNC)
		val |= ARCPGU_CTRL_HS_POL_MASK << ARCPGU_CTRL_HS_POL_OFST;
	अन्यथा
		val &= ~(ARCPGU_CTRL_HS_POL_MASK << ARCPGU_CTRL_HS_POL_OFST);

	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_CTRL, val);
	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_STRIDE, 0);
	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_START_SET, 1);

	arc_pgu_set_pxl_fmt(arcpgu);

	clk_set_rate(arcpgu->clk, m->crtc_घड़ी * 1000);
पूर्ण

अटल व्योम arc_pgu_enable(काष्ठा drm_simple_display_pipe *pipe,
			   काष्ठा drm_crtc_state *crtc_state,
			   काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा arcpgu_drm_निजी *arcpgu = pipe_to_arcpgu_priv(pipe);

	arc_pgu_mode_set(arcpgu);

	clk_prepare_enable(arcpgu->clk);
	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_CTRL,
		      arc_pgu_पढ़ो(arcpgu, ARCPGU_REG_CTRL) |
		      ARCPGU_CTRL_ENABLE_MASK);
पूर्ण

अटल व्योम arc_pgu_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा arcpgu_drm_निजी *arcpgu = pipe_to_arcpgu_priv(pipe);

	clk_disable_unprepare(arcpgu->clk);
	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_CTRL,
			      arc_pgu_पढ़ो(arcpgu, ARCPGU_REG_CTRL) &
			      ~ARCPGU_CTRL_ENABLE_MASK);
पूर्ण

अटल व्योम arc_pgu_update(काष्ठा drm_simple_display_pipe *pipe,
			   काष्ठा drm_plane_state *state)
अणु
	काष्ठा arcpgu_drm_निजी *arcpgu;
	काष्ठा drm_gem_cma_object *gem;

	अगर (!pipe->plane.state->fb)
		वापस;

	arcpgu = pipe_to_arcpgu_priv(pipe);
	gem = drm_fb_cma_get_gem_obj(pipe->plane.state->fb, 0);
	arc_pgu_ग_लिखो(arcpgu, ARCPGU_REG_BUF0_ADDR, gem->paddr);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs arc_pgu_pipe_funcs = अणु
	.update = arc_pgu_update,
	.mode_valid = arc_pgu_mode_valid,
	.enable	= arc_pgu_enable,
	.disable = arc_pgu_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs arcpgu_drm_modecfg_funcs = अणु
	.fb_create  = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(arcpgu_drm_ops);

अटल पूर्णांक arcpgu_load(काष्ठा arcpgu_drm_निजी *arcpgu)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(arcpgu->drm.dev);
	काष्ठा device_node *encoder_node = शून्य, *endpoपूर्णांक_node = शून्य;
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा drm_device *drm = &arcpgu->drm;
	काष्ठा resource *res;
	पूर्णांक ret;

	arcpgu->clk = devm_clk_get(drm->dev, "pxlclk");
	अगर (IS_ERR(arcpgu->clk))
		वापस PTR_ERR(arcpgu->clk);

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;

	drm->mode_config.min_width = 0;
	drm->mode_config.min_height = 0;
	drm->mode_config.max_width = 1920;
	drm->mode_config.max_height = 1080;
	drm->mode_config.funcs = &arcpgu_drm_modecfg_funcs;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	arcpgu->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(arcpgu->regs))
		वापस PTR_ERR(arcpgu->regs);

	dev_info(drm->dev, "arc_pgu ID: 0x%x\n",
		 arc_pgu_पढ़ो(arcpgu, ARCPGU_REG_ID));

	/* Get the optional framebuffer memory resource */
	ret = of_reserved_mem_device_init(drm->dev);
	अगर (ret && ret != -ENODEV)
		वापस ret;

	अगर (dma_set_mask_and_coherent(drm->dev, DMA_BIT_MASK(32)))
		वापस -ENODEV;

	/*
	 * There is only one output port inside each device. It is linked with
	 * encoder endpoपूर्णांक.
	 */
	endpoपूर्णांक_node = of_graph_get_next_endpoपूर्णांक(pdev->dev.of_node, शून्य);
	अगर (endpoपूर्णांक_node) अणु
		encoder_node = of_graph_get_remote_port_parent(endpoपूर्णांक_node);
		of_node_put(endpoपूर्णांक_node);
	पूर्ण अन्यथा अणु
		connector = &arcpgu->sim_conn;
		dev_info(drm->dev, "no encoder found. Assumed virtual LCD on simulation platform\n");
		ret = arcpgu_drm_sim_init(drm, connector);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = drm_simple_display_pipe_init(drm, &arcpgu->pipe, &arc_pgu_pipe_funcs,
					   arc_pgu_supported_क्रमmats,
					   ARRAY_SIZE(arc_pgu_supported_क्रमmats),
					   शून्य, connector);
	अगर (ret)
		वापस ret;

	अगर (encoder_node) अणु
		काष्ठा drm_bridge *bridge;

		/* Locate drm bridge from the hdmi encoder DT node */
		bridge = of_drm_find_bridge(encoder_node);
		अगर (!bridge)
			वापस -EPROBE_DEFER;

		ret = drm_simple_display_pipe_attach_bridge(&arcpgu->pipe, bridge);
		अगर (ret)
			वापस ret;
	पूर्ण

	drm_mode_config_reset(drm);
	drm_kms_helper_poll_init(drm);

	platक्रमm_set_drvdata(pdev, drm);
	वापस 0;
पूर्ण

अटल पूर्णांक arcpgu_unload(काष्ठा drm_device *drm)
अणु
	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutकरोwn(drm);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक arcpgu_show_pxlघड़ी(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *drm = node->minor->dev;
	काष्ठा arcpgu_drm_निजी *arcpgu = dev_to_arcpgu(drm);
	अचिन्हित दीर्घ clkrate = clk_get_rate(arcpgu->clk);
	अचिन्हित दीर्घ mode_घड़ी = arcpgu->pipe.crtc.mode.crtc_घड़ी * 1000;

	seq_म_लिखो(m, "hw  : %lu\n", clkrate);
	seq_म_लिखो(m, "mode: %lu\n", mode_घड़ी);
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list arcpgu_debugfs_list[] = अणु
	अणु "clocks", arcpgu_show_pxlघड़ी, 0 पूर्ण,
पूर्ण;

अटल व्योम arcpgu_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(arcpgu_debugfs_list,
				 ARRAY_SIZE(arcpgu_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा drm_driver arcpgu_drm_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.name = "arcpgu",
	.desc = "ARC PGU Controller",
	.date = "20160219",
	.major = 1,
	.minor = 0,
	.patchlevel = 0,
	.fops = &arcpgu_drm_ops,
	DRM_GEM_CMA_DRIVER_OPS,
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init = arcpgu_debugfs_init,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक arcpgu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arcpgu_drm_निजी *arcpgu;
	पूर्णांक ret;

	arcpgu = devm_drm_dev_alloc(&pdev->dev, &arcpgu_drm_driver,
				    काष्ठा arcpgu_drm_निजी, drm);
	अगर (IS_ERR(arcpgu))
		वापस PTR_ERR(arcpgu);

	ret = arcpgu_load(arcpgu);
	अगर (ret)
		वापस ret;

	ret = drm_dev_रेजिस्टर(&arcpgu->drm, 0);
	अगर (ret)
		जाओ err_unload;

	drm_fbdev_generic_setup(&arcpgu->drm, 16);

	वापस 0;

err_unload:
	arcpgu_unload(&arcpgu->drm);

	वापस ret;
पूर्ण

अटल पूर्णांक arcpgu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(drm);
	arcpgu_unload(drm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id arcpgu_of_table[] = अणु
	अणु.compatible = "snps,arcpgu"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, arcpgu_of_table);

अटल काष्ठा platक्रमm_driver arcpgu_platक्रमm_driver = अणु
	.probe = arcpgu_probe,
	.हटाओ = arcpgu_हटाओ,
	.driver = अणु
		   .name = "arcpgu",
		   .of_match_table = arcpgu_of_table,
		   पूर्ण,
पूर्ण;

module_platक्रमm_driver(arcpgu_platक्रमm_driver);

MODULE_AUTHOR("Carlos Palminha <palminha@synopsys.com>");
MODULE_DESCRIPTION("ARC PGU DRM driver");
MODULE_LICENSE("GPL");
