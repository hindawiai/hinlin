<शैली गुरु>
/*
 * Copyright (C) 2013-2015 ARM Limited
 * Author: Liviu Dudau <Liviu.Dudau@arm.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 *  ARM HDLCD Driver
 */

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/console.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/list.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_modeset_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "hdlcd_drv.h"
#समावेश "hdlcd_regs.h"

अटल पूर्णांक hdlcd_load(काष्ठा drm_device *drm, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(drm->dev);
	काष्ठा resource *res;
	u32 version;
	पूर्णांक ret;

	hdlcd->clk = devm_clk_get(drm->dev, "pxlclk");
	अगर (IS_ERR(hdlcd->clk))
		वापस PTR_ERR(hdlcd->clk);

#अगर_घोषित CONFIG_DEBUG_FS
	atomic_set(&hdlcd->buffer_underrun_count, 0);
	atomic_set(&hdlcd->bus_error_count, 0);
	atomic_set(&hdlcd->vsync_count, 0);
	atomic_set(&hdlcd->dma_end_count, 0);
#पूर्ण_अगर

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdlcd->mmio = devm_ioremap_resource(drm->dev, res);
	अगर (IS_ERR(hdlcd->mmio)) अणु
		DRM_ERROR("failed to map control registers area\n");
		ret = PTR_ERR(hdlcd->mmio);
		hdlcd->mmio = शून्य;
		वापस ret;
	पूर्ण

	version = hdlcd_पढ़ो(hdlcd, HDLCD_REG_VERSION);
	अगर ((version & HDLCD_PRODUCT_MASK) != HDLCD_PRODUCT_ID) अणु
		DRM_ERROR("unknown product id: 0x%x\n", version);
		वापस -EINVAL;
	पूर्ण
	DRM_INFO("found ARM HDLCD version r%dp%d\n",
		(version & HDLCD_VERSION_MAJOR_MASK) >> 8,
		version & HDLCD_VERSION_MINOR_MASK);

	/* Get the optional framebuffer memory resource */
	ret = of_reserved_mem_device_init(drm->dev);
	अगर (ret && ret != -ENODEV)
		वापस ret;

	ret = dma_set_mask_and_coherent(drm->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ setup_fail;

	ret = hdlcd_setup_crtc(drm);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to create crtc\n");
		जाओ setup_fail;
	पूर्ण

	ret = drm_irq_install(drm, platक्रमm_get_irq(pdev, 0));
	अगर (ret < 0) अणु
		DRM_ERROR("failed to install IRQ handler\n");
		जाओ irq_fail;
	पूर्ण

	वापस 0;

irq_fail:
	drm_crtc_cleanup(&hdlcd->crtc);
setup_fail:
	of_reserved_mem_device_release(drm->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs hdlcd_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल व्योम hdlcd_setup_mode_config(काष्ठा drm_device *drm)
अणु
	drm_mode_config_init(drm);
	drm->mode_config.min_width = 0;
	drm->mode_config.min_height = 0;
	drm->mode_config.max_width = HDLCD_MAX_XRES;
	drm->mode_config.max_height = HDLCD_MAX_YRES;
	drm->mode_config.funcs = &hdlcd_mode_config_funcs;
पूर्ण

अटल irqवापस_t hdlcd_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *drm = arg;
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;
	अचिन्हित दीर्घ irq_status;

	irq_status = hdlcd_पढ़ो(hdlcd, HDLCD_REG_INT_STATUS);

#अगर_घोषित CONFIG_DEBUG_FS
	अगर (irq_status & HDLCD_INTERRUPT_UNDERRUN)
		atomic_inc(&hdlcd->buffer_underrun_count);

	अगर (irq_status & HDLCD_INTERRUPT_DMA_END)
		atomic_inc(&hdlcd->dma_end_count);

	अगर (irq_status & HDLCD_INTERRUPT_BUS_ERROR)
		atomic_inc(&hdlcd->bus_error_count);

	अगर (irq_status & HDLCD_INTERRUPT_VSYNC)
		atomic_inc(&hdlcd->vsync_count);

#पूर्ण_अगर
	अगर (irq_status & HDLCD_INTERRUPT_VSYNC)
		drm_crtc_handle_vblank(&hdlcd->crtc);

	/* acknowledge पूर्णांकerrupt(s) */
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_INT_CLEAR, irq_status);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hdlcd_irq_preinstall(काष्ठा drm_device *drm)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;
	/* Ensure पूर्णांकerrupts are disabled */
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_INT_MASK, 0);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_INT_CLEAR, ~0);
पूर्ण

अटल पूर्णांक hdlcd_irq_postinstall(काष्ठा drm_device *drm)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;
	अचिन्हित दीर्घ irq_mask = hdlcd_पढ़ो(hdlcd, HDLCD_REG_INT_MASK);

	/* enable debug पूर्णांकerrupts */
	irq_mask |= HDLCD_DEBUG_INT_MASK;

	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_INT_MASK, irq_mask);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम hdlcd_irq_uninstall(काष्ठा drm_device *drm)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;
	/* disable all the पूर्णांकerrupts that we might have enabled */
	अचिन्हित दीर्घ irq_mask = hdlcd_पढ़ो(hdlcd, HDLCD_REG_INT_MASK);

#अगर_घोषित CONFIG_DEBUG_FS
	/* disable debug पूर्णांकerrupts */
	irq_mask &= ~HDLCD_DEBUG_INT_MASK;
#पूर्ण_अगर

	/* disable vsync पूर्णांकerrupts */
	irq_mask &= ~HDLCD_INTERRUPT_VSYNC;

	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_INT_MASK, irq_mask);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक hdlcd_show_underrun_count(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *drm = node->minor->dev;
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;

	seq_म_लिखो(m, "underrun : %d\n", atomic_पढ़ो(&hdlcd->buffer_underrun_count));
	seq_म_लिखो(m, "dma_end  : %d\n", atomic_पढ़ो(&hdlcd->dma_end_count));
	seq_म_लिखो(m, "bus_error: %d\n", atomic_पढ़ो(&hdlcd->bus_error_count));
	seq_म_लिखो(m, "vsync    : %d\n", atomic_पढ़ो(&hdlcd->vsync_count));
	वापस 0;
पूर्ण

अटल पूर्णांक hdlcd_show_pxlघड़ी(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *drm = node->minor->dev;
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;
	अचिन्हित दीर्घ clkrate = clk_get_rate(hdlcd->clk);
	अचिन्हित दीर्घ mode_घड़ी = hdlcd->crtc.mode.crtc_घड़ी * 1000;

	seq_म_लिखो(m, "hw  : %lu\n", clkrate);
	seq_म_लिखो(m, "mode: %lu\n", mode_घड़ी);
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list hdlcd_debugfs_list[] = अणु
	अणु "interrupt_count", hdlcd_show_underrun_count, 0 पूर्ण,
	अणु "clocks", hdlcd_show_pxlघड़ी, 0 पूर्ण,
पूर्ण;

अटल व्योम hdlcd_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(hdlcd_debugfs_list,
				 ARRAY_SIZE(hdlcd_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
#पूर्ण_अगर

DEFINE_DRM_GEM_CMA_FOPS(fops);

अटल स्थिर काष्ठा drm_driver hdlcd_driver = अणु
	.driver_features = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.irq_handler = hdlcd_irq,
	.irq_preinstall = hdlcd_irq_preinstall,
	.irq_postinstall = hdlcd_irq_postinstall,
	.irq_uninstall = hdlcd_irq_uninstall,
	DRM_GEM_CMA_DRIVER_OPS,
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init = hdlcd_debugfs_init,
#पूर्ण_अगर
	.fops = &fops,
	.name = "hdlcd",
	.desc = "ARM HDLCD Controller DRM",
	.date = "20151021",
	.major = 1,
	.minor = 0,
पूर्ण;

अटल पूर्णांक hdlcd_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm;
	काष्ठा hdlcd_drm_निजी *hdlcd;
	पूर्णांक ret;

	hdlcd = devm_kzalloc(dev, माप(*hdlcd), GFP_KERNEL);
	अगर (!hdlcd)
		वापस -ENOMEM;

	drm = drm_dev_alloc(&hdlcd_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	drm->dev_निजी = hdlcd;
	dev_set_drvdata(dev, drm);

	hdlcd_setup_mode_config(drm);
	ret = hdlcd_load(drm, 0);
	अगर (ret)
		जाओ err_मुक्त;

	/* Set the CRTC's port so that the encoder component can find it */
	hdlcd->crtc.port = of_graph_get_port_by_id(dev->of_node, 0);

	ret = component_bind_all(dev, drm);
	अगर (ret) अणु
		DRM_ERROR("Failed to bind all components\n");
		जाओ err_unload;
	पूर्ण

	ret = pm_runसमय_set_active(dev);
	अगर (ret)
		जाओ err_pm_active;

	pm_runसमय_enable(dev);

	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to initialise vblank\n");
		जाओ err_vblank;
	पूर्ण

	drm_mode_config_reset(drm);
	drm_kms_helper_poll_init(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ err_रेजिस्टर;

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

err_रेजिस्टर:
	drm_kms_helper_poll_fini(drm);
err_vblank:
	pm_runसमय_disable(drm->dev);
err_pm_active:
	drm_atomic_helper_shutकरोwn(drm);
	component_unbind_all(dev, drm);
err_unload:
	of_node_put(hdlcd->crtc.port);
	hdlcd->crtc.port = शून्य;
	drm_irq_uninstall(drm);
	of_reserved_mem_device_release(drm->dev);
err_मुक्त:
	drm_mode_config_cleanup(drm);
	dev_set_drvdata(dev, शून्य);
	drm_dev_put(drm);

	वापस ret;
पूर्ण

अटल व्योम hdlcd_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;

	drm_dev_unरेजिस्टर(drm);
	drm_kms_helper_poll_fini(drm);
	component_unbind_all(dev, drm);
	of_node_put(hdlcd->crtc.port);
	hdlcd->crtc.port = शून्य;
	pm_runसमय_get_sync(dev);
	drm_atomic_helper_shutकरोwn(drm);
	drm_irq_uninstall(drm);
	pm_runसमय_put(dev);
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	of_reserved_mem_device_release(dev);
	drm_mode_config_cleanup(drm);
	drm->dev_निजी = शून्य;
	dev_set_drvdata(dev, शून्य);
	drm_dev_put(drm);
पूर्ण

अटल स्थिर काष्ठा component_master_ops hdlcd_master_ops = अणु
	.bind		= hdlcd_drm_bind,
	.unbind		= hdlcd_drm_unbind,
पूर्ण;

अटल पूर्णांक compare_dev(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल पूर्णांक hdlcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *port;
	काष्ठा component_match *match = शून्य;

	/* there is only one output port inside each device, find it */
	port = of_graph_get_remote_node(pdev->dev.of_node, 0, 0);
	अगर (!port)
		वापस -ENODEV;

	drm_of_component_match_add(&pdev->dev, &match, compare_dev, port);
	of_node_put(port);

	वापस component_master_add_with_match(&pdev->dev, &hdlcd_master_ops,
					       match);
पूर्ण

अटल पूर्णांक hdlcd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &hdlcd_master_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id  hdlcd_of_match[] = अणु
	अणु .compatible	= "arm,hdlcd" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hdlcd_of_match);

अटल पूर्णांक __maybe_unused hdlcd_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm);
पूर्ण

अटल पूर्णांक __maybe_unused hdlcd_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	drm_mode_config_helper_resume(drm);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(hdlcd_pm_ops, hdlcd_pm_suspend, hdlcd_pm_resume);

अटल काष्ठा platक्रमm_driver hdlcd_platक्रमm_driver = अणु
	.probe		= hdlcd_probe,
	.हटाओ		= hdlcd_हटाओ,
	.driver	= अणु
		.name = "hdlcd",
		.pm = &hdlcd_pm_ops,
		.of_match_table	= hdlcd_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hdlcd_platक्रमm_driver);

MODULE_AUTHOR("Liviu Dudau");
MODULE_DESCRIPTION("ARM HDLCD DRM driver");
MODULE_LICENSE("GPL v2");
