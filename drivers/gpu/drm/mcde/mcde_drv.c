<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Linus Walleij <linus.walleij@linaro.org>
 * Parts of this file were based on the MCDE driver by Marcus Lorentzon
 * (C) ST-Ericsson SA 2013
 */

/**
 * DOC: ST-Ericsson MCDE Driver
 *
 * The MCDE (लघु क्रम multi-channel display engine) is a graphics
 * controller found in the Ux500 chipsets, such as NovaThor U8500.
 * It was initially conceptualized by ST Microelectronics क्रम the
 * successor of the Nomadik line, STn8500 but productअगरied in the
 * ST-Ericsson U8500 where is was used क्रम mass-market deployments
 * in Android phones from Samsung and Sony Ericsson.
 *
 * It can करो 1080p30 on SDTV CCIR656, DPI-2, DBI-2 or DSI क्रम
 * panels with or without frame buffering and can convert most
 * input क्रमmats including most variants of RGB and YUV.
 *
 * The hardware has four display pipes, and the layout is a little
 * bit like this::
 *
 *   Memory     -> Overlay -> Channel -> FIFO -> 8 क्रमmatters -> DSI/DPI
 *   External      0..5       0..3       A,B,    6 x DSI         bridge
 *   source 0..9                         C0,C1   2 x DPI
 *
 * FIFOs A and B are क्रम LCD and HDMI जबतक FIFO CO/C1 are क्रम
 * panels with embedded buffer.
 * 6 of the क्रमmatters are क्रम DSI, 3 pairs क्रम VID/CMD respectively.
 * 2 of the क्रमmatters are क्रम DPI.
 *
 * Behind the क्रमmatters are the DSI or DPI ports that route to
 * the बाह्यal pins of the chip. As there are 3 DSI ports and one
 * DPI port, it is possible to configure up to 4 display pipelines
 * (effectively using channels 0..3) क्रम concurrent use.
 *
 * In the current DRM/KMS setup, we use one बाह्यal source, one overlay,
 * one FIFO and one क्रमmatter which we connect to the simple CMA framebuffer
 * helpers. We then provide a bridge to the DSI port, and on the DSI port
 * bridge we connect hang a panel bridge or other bridge. This may be subject
 * to change as we exploit more of the hardware capabilities.
 *
 * TODO:
 *
 * - Enabled damaged rectangles using drm_plane_enable_fb_damage_clips()
 *   so we can selectively just transmit the damaged area to a
 *   command-only display.
 * - Enable mixing of more planes, possibly at the cost of moving away
 *   from using the simple framebuffer pipeline.
 * - Enable output to bridges such as the AV8100 HDMI encoder from
 *   the DSI bridge.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_vblank.h>

#समावेश "mcde_drm.h"

#घोषणा DRIVER_DESC	"DRM module for MCDE"

#घोषणा MCDE_PID 0x000001FC
#घोषणा MCDE_PID_METALFIX_VERSION_SHIFT 0
#घोषणा MCDE_PID_METALFIX_VERSION_MASK 0x000000FF
#घोषणा MCDE_PID_DEVELOPMENT_VERSION_SHIFT 8
#घोषणा MCDE_PID_DEVELOPMENT_VERSION_MASK 0x0000FF00
#घोषणा MCDE_PID_MINOR_VERSION_SHIFT 16
#घोषणा MCDE_PID_MINOR_VERSION_MASK 0x00FF0000
#घोषणा MCDE_PID_MAJOR_VERSION_SHIFT 24
#घोषणा MCDE_PID_MAJOR_VERSION_MASK 0xFF000000

अटल स्थिर काष्ठा drm_mode_config_funcs mcde_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create_with_dirty,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_helper_funcs mcde_mode_config_helpers = अणु
	/*
	 * Using this function is necessary to commit atomic updates
	 * that need the CRTC to be enabled beक्रमe a commit, as is
	 * the हाल with e.g. DSI displays.
	 */
	.atomic_commit_tail = drm_atomic_helper_commit_tail_rpm,
पूर्ण;

अटल irqवापस_t mcde_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mcde *mcde = data;
	u32 val;

	val = पढ़ोl(mcde->regs + MCDE_MISERR);

	mcde_display_irq(mcde);

	अगर (val)
		dev_info(mcde->dev, "some error IRQ\n");
	ग_लिखोl(val, mcde->regs + MCDE_RISERR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mcde_modeset_init(काष्ठा drm_device *drm)
अणु
	काष्ठा drm_mode_config *mode_config;
	काष्ठा mcde *mcde = to_mcde(drm);
	पूर्णांक ret;

	/*
	 * If no other bridge was found, check अगर we have a DPI panel or
	 * any other bridge connected directly to the MCDE DPI output.
	 * If a DSI bridge is found, DSI will take precedence.
	 *
	 * TODO: more elaborate bridge selection अगर we have more than one
	 * thing attached to the प्रणाली.
	 */
	अगर (!mcde->bridge) अणु
		काष्ठा drm_panel *panel;
		काष्ठा drm_bridge *bridge;

		ret = drm_of_find_panel_or_bridge(drm->dev->of_node,
						  0, 0, &panel, &bridge);
		अगर (ret) अणु
			dev_err(drm->dev,
				"Could not locate any output bridge or panel\n");
			वापस ret;
		पूर्ण
		अगर (panel) अणु
			bridge = drm_panel_bridge_add_typed(panel,
					DRM_MODE_CONNECTOR_DPI);
			अगर (IS_ERR(bridge)) अणु
				dev_err(drm->dev,
					"Could not connect panel bridge\n");
				वापस PTR_ERR(bridge);
			पूर्ण
		पूर्ण
		mcde->dpi_output = true;
		mcde->bridge = bridge;
		mcde->flow_mode = MCDE_DPI_FORMATTER_FLOW;
	पूर्ण

	mode_config = &drm->mode_config;
	mode_config->funcs = &mcde_mode_config_funcs;
	mode_config->helper_निजी = &mcde_mode_config_helpers;
	/* This hardware can करो 1080p */
	mode_config->min_width = 1;
	mode_config->max_width = 1920;
	mode_config->min_height = 1;
	mode_config->max_height = 1080;

	ret = drm_vblank_init(drm, 1);
	अगर (ret) अणु
		dev_err(drm->dev, "failed to init vblank\n");
		वापस ret;
	पूर्ण

	ret = mcde_display_init(drm);
	अगर (ret) अणु
		dev_err(drm->dev, "failed to init display\n");
		वापस ret;
	पूर्ण

	/* Attach the bridge. */
	ret = drm_simple_display_pipe_attach_bridge(&mcde->pipe,
						    mcde->bridge);
	अगर (ret) अणु
		dev_err(drm->dev, "failed to attach display output bridge\n");
		वापस ret;
	पूर्ण

	drm_mode_config_reset(drm);
	drm_kms_helper_poll_init(drm);

	वापस 0;
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(drm_fops);

अटल स्थिर काष्ठा drm_driver mcde_drm_driver = अणु
	.driver_features =
		DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.lastबंद = drm_fb_helper_lastबंद,
	.ioctls = शून्य,
	.fops = &drm_fops,
	.name = "mcde",
	.desc = DRIVER_DESC,
	.date = "20180529",
	.major = 1,
	.minor = 0,
	.patchlevel = 0,
	DRM_GEM_CMA_DRIVER_OPS,
पूर्ण;

अटल पूर्णांक mcde_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;

	ret = component_bind_all(drm->dev, drm);
	अगर (ret) अणु
		dev_err(dev, "can't bind component devices\n");
		वापस ret;
	पूर्ण

	ret = mcde_modeset_init(drm);
	अगर (ret)
		जाओ unbind;

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0)
		जाओ unbind;

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

unbind:
	component_unbind_all(drm->dev, drm);
	वापस ret;
पूर्ण

अटल व्योम mcde_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(drm);
	drm_atomic_helper_shutकरोwn(drm);
	component_unbind_all(drm->dev, drm);
पूर्ण

अटल स्थिर काष्ठा component_master_ops mcde_drm_comp_ops = अणु
	.bind = mcde_drm_bind,
	.unbind = mcde_drm_unbind,
पूर्ण;

अटल काष्ठा platक्रमm_driver *स्थिर mcde_component_drivers[] = अणु
	&mcde_dsi_driver,
पूर्ण;

अटल पूर्णांक mcde_compare_dev(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev == data;
पूर्ण

अटल पूर्णांक mcde_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा drm_device *drm;
	काष्ठा mcde *mcde;
	काष्ठा component_match *match = शून्य;
	काष्ठा resource *res;
	u32 pid;
	पूर्णांक irq;
	पूर्णांक ret;
	पूर्णांक i;

	mcde = devm_drm_dev_alloc(dev, &mcde_drm_driver, काष्ठा mcde, drm);
	अगर (IS_ERR(mcde))
		वापस PTR_ERR(mcde);
	drm = &mcde->drm;
	mcde->dev = dev;
	platक्रमm_set_drvdata(pdev, drm);

	/* First obtain and turn on the मुख्य घातer */
	mcde->epod = devm_regulator_get(dev, "epod");
	अगर (IS_ERR(mcde->epod)) अणु
		ret = PTR_ERR(mcde->epod);
		dev_err(dev, "can't get EPOD regulator\n");
		वापस ret;
	पूर्ण
	ret = regulator_enable(mcde->epod);
	अगर (ret) अणु
		dev_err(dev, "can't enable EPOD regulator\n");
		वापस ret;
	पूर्ण
	mcde->vana = devm_regulator_get(dev, "vana");
	अगर (IS_ERR(mcde->vana)) अणु
		ret = PTR_ERR(mcde->vana);
		dev_err(dev, "can't get VANA regulator\n");
		जाओ regulator_epod_off;
	पूर्ण
	ret = regulator_enable(mcde->vana);
	अगर (ret) अणु
		dev_err(dev, "can't enable VANA regulator\n");
		जाओ regulator_epod_off;
	पूर्ण
	/*
	 * The venकरोr code uses ESRAM (onchip RAM) and need to activate
	 * the v-esram34 regulator, but we करोn't use that yet
	 */

	/* Clock the silicon so we can access the रेजिस्टरs */
	mcde->mcde_clk = devm_clk_get(dev, "mcde");
	अगर (IS_ERR(mcde->mcde_clk)) अणु
		dev_err(dev, "unable to get MCDE main clock\n");
		ret = PTR_ERR(mcde->mcde_clk);
		जाओ regulator_off;
	पूर्ण
	ret = clk_prepare_enable(mcde->mcde_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable MCDE main clock\n");
		जाओ regulator_off;
	पूर्ण
	dev_info(dev, "MCDE clk rate %lu Hz\n", clk_get_rate(mcde->mcde_clk));

	mcde->lcd_clk = devm_clk_get(dev, "lcd");
	अगर (IS_ERR(mcde->lcd_clk)) अणु
		dev_err(dev, "unable to get LCD clock\n");
		ret = PTR_ERR(mcde->lcd_clk);
		जाओ clk_disable;
	पूर्ण
	mcde->hdmi_clk = devm_clk_get(dev, "hdmi");
	अगर (IS_ERR(mcde->hdmi_clk)) अणु
		dev_err(dev, "unable to get HDMI clock\n");
		ret = PTR_ERR(mcde->hdmi_clk);
		जाओ clk_disable;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mcde->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mcde->regs)) अणु
		dev_err(dev, "no MCDE regs\n");
		ret = -EINVAL;
		जाओ clk_disable;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ clk_disable;
	पूर्ण

	ret = devm_request_irq(dev, irq, mcde_irq, 0, "mcde", mcde);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq %d\n", ret);
		जाओ clk_disable;
	पूर्ण

	/*
	 * Check hardware revision, we only support U8500v2 version
	 * as this was the only version used क्रम mass market deployment,
	 * but surely you can add more versions अगर you have them and
	 * need them.
	 */
	pid = पढ़ोl(mcde->regs + MCDE_PID);
	dev_info(dev, "found MCDE HW revision %d.%d (dev %d, metal fix %d)\n",
		 (pid & MCDE_PID_MAJOR_VERSION_MASK)
		 >> MCDE_PID_MAJOR_VERSION_SHIFT,
		 (pid & MCDE_PID_MINOR_VERSION_MASK)
		 >> MCDE_PID_MINOR_VERSION_SHIFT,
		 (pid & MCDE_PID_DEVELOPMENT_VERSION_MASK)
		 >> MCDE_PID_DEVELOPMENT_VERSION_SHIFT,
		 (pid & MCDE_PID_METALFIX_VERSION_MASK)
		 >> MCDE_PID_METALFIX_VERSION_SHIFT);
	अगर (pid != 0x03000800) अणु
		dev_err(dev, "unsupported hardware revision\n");
		ret = -ENODEV;
		जाओ clk_disable;
	पूर्ण

	/* Disable and clear any pending पूर्णांकerrupts */
	mcde_display_disable_irqs(mcde);
	ग_लिखोl(0, mcde->regs + MCDE_IMSCERR);
	ग_लिखोl(0xFFFFFFFF, mcde->regs + MCDE_RISERR);

	/* Spawn child devices क्रम the DSI ports */
	devm_of_platक्रमm_populate(dev);

	/* Create something that will match the subdrivers when we bind */
	क्रम (i = 0; i < ARRAY_SIZE(mcde_component_drivers); i++) अणु
		काष्ठा device_driver *drv = &mcde_component_drivers[i]->driver;
		काष्ठा device *p = शून्य, *d;

		जबतक ((d = platक्रमm_find_device_by_driver(p, drv))) अणु
			put_device(p);
			component_match_add(dev, &match, mcde_compare_dev, d);
			p = d;
		पूर्ण
		put_device(p);
	पूर्ण
	अगर (!match) अणु
		dev_err(dev, "no matching components\n");
		ret = -ENODEV;
		जाओ clk_disable;
	पूर्ण
	अगर (IS_ERR(match)) अणु
		dev_err(dev, "could not create component match\n");
		ret = PTR_ERR(match);
		जाओ clk_disable;
	पूर्ण

	/*
	 * Perक्रमm an invasive reset of the MCDE and all blocks by
	 * cutting the घातer to the subप्रणाली, then bring it back up
	 * later when we enable the display as a result of
	 * component_master_add_with_match().
	 */
	ret = regulator_disable(mcde->epod);
	अगर (ret) अणु
		dev_err(dev, "can't disable EPOD regulator\n");
		वापस ret;
	पूर्ण
	/* Wait 50 ms so we are sure we cut the घातer */
	usleep_range(50000, 70000);

	ret = component_master_add_with_match(&pdev->dev, &mcde_drm_comp_ops,
					      match);
	अगर (ret) अणु
		dev_err(dev, "failed to add component master\n");
		/*
		 * The EPOD regulator is alपढ़ोy disabled at this poपूर्णांक so some
		 * special errorpath code is needed
		 */
		clk_disable_unprepare(mcde->mcde_clk);
		regulator_disable(mcde->vana);
		वापस ret;
	पूर्ण

	वापस 0;

clk_disable:
	clk_disable_unprepare(mcde->mcde_clk);
regulator_off:
	regulator_disable(mcde->vana);
regulator_epod_off:
	regulator_disable(mcde->epod);
	वापस ret;

पूर्ण

अटल पूर्णांक mcde_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);
	काष्ठा mcde *mcde = to_mcde(drm);

	component_master_del(&pdev->dev, &mcde_drm_comp_ops);
	clk_disable_unprepare(mcde->mcde_clk);
	regulator_disable(mcde->vana);
	regulator_disable(mcde->epod);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mcde_of_match[] = अणु
	अणु
		.compatible = "ste,mcde",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mcde_driver = अणु
	.driver = अणु
		.name           = "mcde",
		.of_match_table = of_match_ptr(mcde_of_match),
	पूर्ण,
	.probe = mcde_probe,
	.हटाओ = mcde_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_driver *स्थिर component_drivers[] = अणु
	&mcde_dsi_driver,
पूर्ण;

अटल पूर्णांक __init mcde_drm_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_रेजिस्टर_drivers(component_drivers,
					ARRAY_SIZE(component_drivers));
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&mcde_driver);
पूर्ण

अटल व्योम __निकास mcde_drm_unरेजिस्टर(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(component_drivers,
				    ARRAY_SIZE(component_drivers));
	platक्रमm_driver_unरेजिस्टर(&mcde_driver);
पूर्ण

module_init(mcde_drm_रेजिस्टर);
module_निकास(mcde_drm_unरेजिस्टर);

MODULE_ALIAS("platform:mcde-drm");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_LICENSE("GPL");
