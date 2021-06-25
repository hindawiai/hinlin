<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2014 Endless Mobile
 *
 * Written by:
 *     Jasper St. Pierre <jstpierre@mecheye.net>
 */

#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/amlogic/meson-canvas.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "meson_crtc.h"
#समावेश "meson_drv.h"
#समावेश "meson_overlay.h"
#समावेश "meson_plane.h"
#समावेश "meson_osd_afbcd.h"
#समावेश "meson_registers.h"
#समावेश "meson_venc_cvbs.h"
#समावेश "meson_viu.h"
#समावेश "meson_vpp.h"
#समावेश "meson_rdma.h"

#घोषणा DRIVER_NAME "meson"
#घोषणा DRIVER_DESC "Amlogic Meson DRM driver"

/**
 * DOC: Video Processing Unit
 *
 * VPU Handles the Global Video Processing, it includes management of the
 * घड़ीs gates, blocks reset lines and घातer करोमुख्यs.
 *
 * What is missing :
 *
 * - Full reset of entire video processing HW blocks
 * - Scaling and setup of the VPU घड़ी
 * - Bus घड़ी gates
 * - Powering up video processing HW blocks
 * - Powering Up HDMI controller and PHY
 */

अटल स्थिर काष्ठा drm_mode_config_funcs meson_mode_config_funcs = अणु
	.atomic_check        = drm_atomic_helper_check,
	.atomic_commit       = drm_atomic_helper_commit,
	.fb_create           = drm_gem_fb_create,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_helper_funcs meson_mode_config_helpers = अणु
	.atomic_commit_tail = drm_atomic_helper_commit_tail_rpm,
पूर्ण;

अटल irqवापस_t meson_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = arg;
	काष्ठा meson_drm *priv = dev->dev_निजी;

	(व्योम)पढ़ोl_relaxed(priv->io_base + _REG(VENC_INTFLAG));

	meson_crtc_irq(priv);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक meson_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			     काष्ठा drm_mode_create_dumb *args)
अणु
	/*
	 * We need 64bytes aligned stride, and PAGE aligned size
	 */
	args->pitch = ALIGN(DIV_ROUND_UP(args->width * args->bpp, 8), SZ_64);
	args->size = PAGE_ALIGN(args->pitch * args->height);

	वापस drm_gem_cma_dumb_create_पूर्णांकernal(file, dev, args);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(fops);

अटल स्थिर काष्ठा drm_driver meson_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,

	/* IRQ */
	.irq_handler		= meson_irq,

	/* CMA Ops */
	DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(meson_dumb_create),

	/* Misc */
	.fops			= &fops,
	.name			= DRIVER_NAME,
	.desc			= DRIVER_DESC,
	.date			= "20161109",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल bool meson_vpu_has_available_connectors(काष्ठा device *dev)
अणु
	काष्ठा device_node *ep, *remote;

	/* Parses each endpoपूर्णांक and check अगर remote exists */
	क्रम_each_endpoपूर्णांक_of_node(dev->of_node, ep) अणु
		/* If the endpoपूर्णांक node exists, consider it enabled */
		remote = of_graph_get_remote_port(ep);
		अगर (remote)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा regmap_config meson_regmap_config = अणु
	.reg_bits       = 32,
	.val_bits       = 32,
	.reg_stride     = 4,
	.max_रेजिस्टर   = 0x1000,
पूर्ण;

अटल व्योम meson_vpu_init(काष्ठा meson_drm *priv)
अणु
	u32 value;

	/*
	 * Slave dc0 and dc5 connected to master port 1.
	 * By शेष other slaves are connected to master port 0.
	 */
	value = VPU_RDARB_SLAVE_TO_MASTER_PORT(0, 1) |
		VPU_RDARB_SLAVE_TO_MASTER_PORT(5, 1);
	ग_लिखोl_relaxed(value, priv->io_base + _REG(VPU_RDARB_MODE_L1C1));

	/* Slave dc0 connected to master port 1 */
	value = VPU_RDARB_SLAVE_TO_MASTER_PORT(0, 1);
	ग_लिखोl_relaxed(value, priv->io_base + _REG(VPU_RDARB_MODE_L1C2));

	/* Slave dc4 and dc7 connected to master port 1 */
	value = VPU_RDARB_SLAVE_TO_MASTER_PORT(4, 1) |
		VPU_RDARB_SLAVE_TO_MASTER_PORT(7, 1);
	ग_लिखोl_relaxed(value, priv->io_base + _REG(VPU_RDARB_MODE_L2C1));

	/* Slave dc1 connected to master port 1 */
	value = VPU_RDARB_SLAVE_TO_MASTER_PORT(1, 1);
	ग_लिखोl_relaxed(value, priv->io_base + _REG(VPU_WRARB_MODE_L2C1));
पूर्ण

अटल व्योम meson_हटाओ_framebuffers(व्योम)
अणु
	काष्ठा apertures_काष्ठा *ap;

	ap = alloc_apertures(1);
	अगर (!ap)
		वापस;

	/* The framebuffer can be located anywhere in RAM */
	ap->ranges[0].base = 0;
	ap->ranges[0].size = ~0;

	drm_fb_helper_हटाओ_conflicting_framebuffers(ap, "meson-drm-fb",
						      false);
	kमुक्त(ap);
पूर्ण

काष्ठा meson_drm_soc_attr अणु
	काष्ठा meson_drm_soc_limits limits;
	स्थिर काष्ठा soc_device_attribute *attrs;
पूर्ण;

अटल स्थिर काष्ठा meson_drm_soc_attr meson_drm_soc_attrs[] = अणु
	/* S805X/S805Y HDMI PLL won't lock क्रम HDMI PHY freq > 1,65GHz */
	अणु
		.limits = अणु
			.max_hdmi_phy_freq = 1650000,
		पूर्ण,
		.attrs = (स्थिर काष्ठा soc_device_attribute []) अणु
			अणु .soc_id = "GXL (S805*)", पूर्ण,
			अणु /* sentinel */ पूर्ण,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक meson_drv_bind_master(काष्ठा device *dev, bool has_components)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा meson_drm_match_data *match;
	काष्ठा meson_drm *priv;
	काष्ठा drm_device *drm;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret, i;

	/* Checks अगर an output connector is available */
	अगर (!meson_vpu_has_available_connectors(dev)) अणु
		dev_err(dev, "No output connector available\n");
		वापस -ENODEV;
	पूर्ण

	match = of_device_get_match_data(dev);
	अगर (!match)
		वापस -ENODEV;

	drm = drm_dev_alloc(&meson_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ मुक्त_drm;
	पूर्ण
	drm->dev_निजी = priv;
	priv->drm = drm;
	priv->dev = dev;
	priv->compat = match->compat;
	priv->afbcd.ops = match->afbcd_ops;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "vpu");
	regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regs)) अणु
		ret = PTR_ERR(regs);
		जाओ मुक्त_drm;
	पूर्ण

	priv->io_base = regs;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "hhi");
	अगर (!res) अणु
		ret = -EINVAL;
		जाओ मुक्त_drm;
	पूर्ण
	/* Simply ioremap since it may be a shared रेजिस्टर zone */
	regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!regs) अणु
		ret = -EADDRNOTAVAIL;
		जाओ मुक्त_drm;
	पूर्ण

	priv->hhi = devm_regmap_init_mmio(dev, regs,
					  &meson_regmap_config);
	अगर (IS_ERR(priv->hhi)) अणु
		dev_err(&pdev->dev, "Couldn't create the HHI regmap\n");
		ret = PTR_ERR(priv->hhi);
		जाओ मुक्त_drm;
	पूर्ण

	priv->canvas = meson_canvas_get(dev);
	अगर (IS_ERR(priv->canvas)) अणु
		ret = PTR_ERR(priv->canvas);
		जाओ मुक्त_drm;
	पूर्ण

	ret = meson_canvas_alloc(priv->canvas, &priv->canvas_id_osd1);
	अगर (ret)
		जाओ मुक्त_drm;
	ret = meson_canvas_alloc(priv->canvas, &priv->canvas_id_vd1_0);
	अगर (ret) अणु
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_osd1);
		जाओ मुक्त_drm;
	पूर्ण
	ret = meson_canvas_alloc(priv->canvas, &priv->canvas_id_vd1_1);
	अगर (ret) अणु
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_osd1);
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_vd1_0);
		जाओ मुक्त_drm;
	पूर्ण
	ret = meson_canvas_alloc(priv->canvas, &priv->canvas_id_vd1_2);
	अगर (ret) अणु
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_osd1);
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_vd1_0);
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_vd1_1);
		जाओ मुक्त_drm;
	पूर्ण

	priv->vsync_irq = platक्रमm_get_irq(pdev, 0);

	ret = drm_vblank_init(drm, 1);
	अगर (ret)
		जाओ मुक्त_drm;

	/* Assign limits per soc revision/package */
	क्रम (i = 0 ; i < ARRAY_SIZE(meson_drm_soc_attrs) ; ++i) अणु
		अगर (soc_device_match(meson_drm_soc_attrs[i].attrs)) अणु
			priv->limits = &meson_drm_soc_attrs[i].limits;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Remove early framebuffers (ie. simplefb) */
	meson_हटाओ_framebuffers();

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		जाओ मुक्त_drm;
	drm->mode_config.max_width = 3840;
	drm->mode_config.max_height = 2160;
	drm->mode_config.funcs = &meson_mode_config_funcs;
	drm->mode_config.helper_निजी	= &meson_mode_config_helpers;

	/* Hardware Initialization */

	meson_vpu_init(priv);
	meson_venc_init(priv);
	meson_vpp_init(priv);
	meson_viu_init(priv);
	अगर (priv->afbcd.ops) अणु
		ret = priv->afbcd.ops->init(priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Encoder Initialization */

	ret = meson_venc_cvbs_create(priv);
	अगर (ret)
		जाओ मुक्त_drm;

	अगर (has_components) अणु
		ret = component_bind_all(drm->dev, drm);
		अगर (ret) अणु
			dev_err(drm->dev, "Couldn't bind all components\n");
			जाओ मुक्त_drm;
		पूर्ण
	पूर्ण

	ret = meson_plane_create(priv);
	अगर (ret)
		जाओ मुक्त_drm;

	ret = meson_overlay_create(priv);
	अगर (ret)
		जाओ मुक्त_drm;

	ret = meson_crtc_create(priv);
	अगर (ret)
		जाओ मुक्त_drm;

	ret = drm_irq_install(drm, priv->vsync_irq);
	अगर (ret)
		जाओ मुक्त_drm;

	drm_mode_config_reset(drm);

	drm_kms_helper_poll_init(drm);

	platक्रमm_set_drvdata(pdev, priv);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ uninstall_irq;

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

uninstall_irq:
	drm_irq_uninstall(drm);
मुक्त_drm:
	drm_dev_put(drm);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_drv_bind(काष्ठा device *dev)
अणु
	वापस meson_drv_bind_master(dev, true);
पूर्ण

अटल व्योम meson_drv_unbind(काष्ठा device *dev)
अणु
	काष्ठा meson_drm *priv = dev_get_drvdata(dev);
	काष्ठा drm_device *drm = priv->drm;

	अगर (priv->canvas) अणु
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_osd1);
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_vd1_0);
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_vd1_1);
		meson_canvas_मुक्त(priv->canvas, priv->canvas_id_vd1_2);
	पूर्ण

	drm_dev_unरेजिस्टर(drm);
	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutकरोwn(drm);
	component_unbind_all(dev, drm);
	drm_irq_uninstall(drm);
	drm_dev_put(drm);

	अगर (priv->afbcd.ops) अणु
		priv->afbcd.ops->reset(priv);
		meson_rdma_मुक्त(priv);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा component_master_ops meson_drv_master_ops = अणु
	.bind	= meson_drv_bind,
	.unbind	= meson_drv_unbind,
पूर्ण;

अटल पूर्णांक __maybe_unused meson_drv_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा meson_drm *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस 0;

	वापस drm_mode_config_helper_suspend(priv->drm);
पूर्ण

अटल पूर्णांक __maybe_unused meson_drv_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा meson_drm *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस 0;

	meson_vpu_init(priv);
	meson_venc_init(priv);
	meson_vpp_init(priv);
	meson_viu_init(priv);
	अगर (priv->afbcd.ops)
		priv->afbcd.ops->init(priv);

	वापस drm_mode_config_helper_resume(priv->drm);
पूर्ण

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	DRM_DEBUG_DRIVER("Comparing of node %pOF with %pOF\n",
			 dev->of_node, data);

	वापस dev->of_node == data;
पूर्ण

/* Possible connectors nodes to ignore */
अटल स्थिर काष्ठा of_device_id connectors_match[] = अणु
	अणु .compatible = "composite-video-connector" पूर्ण,
	अणु .compatible = "svideo-connector" पूर्ण,
	अणु .compatible = "hdmi-connector" पूर्ण,
	अणु .compatible = "dvi-connector" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक meson_probe_remote(काष्ठा platक्रमm_device *pdev,
			      काष्ठा component_match **match,
			      काष्ठा device_node *parent,
			      काष्ठा device_node *remote)
अणु
	काष्ठा device_node *ep, *remote_node;
	पूर्णांक count = 1;

	/* If node is a connector, वापस and करो not add to match table */
	अगर (of_match_node(connectors_match, remote))
		वापस 1;

	component_match_add(&pdev->dev, match, compare_of, remote);

	क्रम_each_endpoपूर्णांक_of_node(remote, ep) अणु
		remote_node = of_graph_get_remote_port_parent(ep);
		अगर (!remote_node ||
		    remote_node == parent || /* Ignore parent endpoपूर्णांक */
		    !of_device_is_available(remote_node)) अणु
			of_node_put(remote_node);
			जारी;
		पूर्ण

		count += meson_probe_remote(pdev, match, remote, remote_node);

		of_node_put(remote_node);
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम meson_drv_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_drm *priv = dev_get_drvdata(&pdev->dev);

	अगर (!priv)
		वापस;

	drm_kms_helper_poll_fini(priv->drm);
	drm_atomic_helper_shutकरोwn(priv->drm);
पूर्ण

अटल पूर्णांक meson_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा component_match *match = शून्य;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *ep, *remote;
	पूर्णांक count = 0;

	क्रम_each_endpoपूर्णांक_of_node(np, ep) अणु
		remote = of_graph_get_remote_port_parent(ep);
		अगर (!remote || !of_device_is_available(remote)) अणु
			of_node_put(remote);
			जारी;
		पूर्ण

		count += meson_probe_remote(pdev, &match, np, remote);
		of_node_put(remote);
	पूर्ण

	अगर (count && !match)
		वापस meson_drv_bind_master(&pdev->dev, false);

	/* If some endpoपूर्णांकs were found, initialize the nodes */
	अगर (count) अणु
		dev_info(&pdev->dev, "Queued %d outputs on vpu\n", count);

		वापस component_master_add_with_match(&pdev->dev,
						       &meson_drv_master_ops,
						       match);
	पूर्ण

	/* If no output endpoपूर्णांकs were available, simply bail out */
	वापस 0;
पूर्ण;

अटल काष्ठा meson_drm_match_data meson_drm_gxbb_data = अणु
	.compat = VPU_COMPATIBLE_GXBB,
पूर्ण;

अटल काष्ठा meson_drm_match_data meson_drm_gxl_data = अणु
	.compat = VPU_COMPATIBLE_GXL,
पूर्ण;

अटल काष्ठा meson_drm_match_data meson_drm_gxm_data = अणु
	.compat = VPU_COMPATIBLE_GXM,
	.afbcd_ops = &meson_afbcd_gxm_ops,
पूर्ण;

अटल काष्ठा meson_drm_match_data meson_drm_g12a_data = अणु
	.compat = VPU_COMPATIBLE_G12A,
	.afbcd_ops = &meson_afbcd_g12a_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dt_match[] = अणु
	अणु .compatible = "amlogic,meson-gxbb-vpu",
	  .data       = (व्योम *)&meson_drm_gxbb_data पूर्ण,
	अणु .compatible = "amlogic,meson-gxl-vpu",
	  .data       = (व्योम *)&meson_drm_gxl_data पूर्ण,
	अणु .compatible = "amlogic,meson-gxm-vpu",
	  .data       = (व्योम *)&meson_drm_gxm_data पूर्ण,
	अणु .compatible = "amlogic,meson-g12a-vpu",
	  .data       = (व्योम *)&meson_drm_g12a_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dt_match);

अटल स्थिर काष्ठा dev_pm_ops meson_drv_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(meson_drv_pm_suspend, meson_drv_pm_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver meson_drm_platक्रमm_driver = अणु
	.probe      = meson_drv_probe,
	.shutकरोwn   = meson_drv_shutकरोwn,
	.driver     = अणु
		.name	= "meson-drm",
		.of_match_table = dt_match,
		.pm = &meson_drv_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_drm_platक्रमm_driver);

MODULE_AUTHOR("Jasper St. Pierre <jstpierre@mecheye.net>");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
