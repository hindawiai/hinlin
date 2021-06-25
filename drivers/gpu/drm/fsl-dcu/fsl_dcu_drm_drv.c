<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * Freescale DCU drm device driver
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/console.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_modeset_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "fsl_dcu_drm_crtc.h"
#समावेश "fsl_dcu_drm_drv.h"
#समावेश "fsl_tcon.h"

अटल पूर्णांक legacyfb_depth = 24;
module_param(legacyfb_depth, पूर्णांक, 0444);

अटल bool fsl_dcu_drm_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg == DCU_INT_STATUS || reg == DCU_UPDATE_MODE)
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config fsl_dcu_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.अस्थिर_reg = fsl_dcu_drm_is_अस्थिर_reg,
पूर्ण;

अटल व्योम fsl_dcu_irq_uninstall(काष्ठा drm_device *dev)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;

	regmap_ग_लिखो(fsl_dev->regmap, DCU_INT_STATUS, ~0);
	regmap_ग_लिखो(fsl_dev->regmap, DCU_INT_MASK, ~0);
पूर्ण

अटल पूर्णांक fsl_dcu_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;
	पूर्णांक ret;

	ret = fsl_dcu_drm_modeset_init(fsl_dev);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "failed to initialize mode setting\n");
		वापस ret;
	पूर्ण

	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "failed to initialize vblank\n");
		जाओ करोne;
	पूर्ण

	ret = drm_irq_install(dev, fsl_dev->irq);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "failed to install IRQ handler\n");
		जाओ करोne;
	पूर्ण

	अगर (legacyfb_depth != 16 && legacyfb_depth != 24 &&
	    legacyfb_depth != 32) अणु
		dev_warn(dev->dev,
			"Invalid legacyfb_depth.  Defaulting to 24bpp\n");
		legacyfb_depth = 24;
	पूर्ण

	वापस 0;
करोne:
	drm_kms_helper_poll_fini(dev);

	drm_mode_config_cleanup(dev);
	drm_irq_uninstall(dev);
	dev->dev_निजी = शून्य;

	वापस ret;
पूर्ण

अटल व्योम fsl_dcu_unload(काष्ठा drm_device *dev)
अणु
	drm_atomic_helper_shutकरोwn(dev);
	drm_kms_helper_poll_fini(dev);

	drm_mode_config_cleanup(dev);
	drm_irq_uninstall(dev);

	dev->dev_निजी = शून्य;
पूर्ण

अटल irqवापस_t fsl_dcu_drm_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = arg;
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;
	अचिन्हित पूर्णांक पूर्णांक_status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(fsl_dev->regmap, DCU_INT_STATUS, &पूर्णांक_status);
	अगर (ret) अणु
		dev_err(dev->dev, "read DCU_INT_STATUS failed\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर (पूर्णांक_status & DCU_INT_STATUS_VBLANK)
		drm_handle_vblank(dev, 0);

	regmap_ग_लिखो(fsl_dev->regmap, DCU_INT_STATUS, पूर्णांक_status);

	वापस IRQ_HANDLED;
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(fsl_dcu_drm_fops);

अटल स्थिर काष्ठा drm_driver fsl_dcu_drm_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.load			= fsl_dcu_load,
	.unload			= fsl_dcu_unload,
	.irq_handler		= fsl_dcu_drm_irq,
	.irq_preinstall		= fsl_dcu_irq_uninstall,
	.irq_uninstall		= fsl_dcu_irq_uninstall,
	DRM_GEM_CMA_DRIVER_OPS,
	.fops			= &fsl_dcu_drm_fops,
	.name			= "fsl-dcu-drm",
	.desc			= "Freescale DCU DRM",
	.date			= "20160425",
	.major			= 1,
	.minor			= 1,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fsl_dcu_drm_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!fsl_dev)
		वापस 0;

	disable_irq(fsl_dev->irq);

	ret = drm_mode_config_helper_suspend(fsl_dev->drm);
	अगर (ret) अणु
		enable_irq(fsl_dev->irq);
		वापस ret;
	पूर्ण

	clk_disable_unprepare(fsl_dev->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_dcu_drm_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!fsl_dev)
		वापस 0;

	ret = clk_prepare_enable(fsl_dev->clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable dcu clk\n");
		वापस ret;
	पूर्ण

	अगर (fsl_dev->tcon)
		fsl_tcon_bypass_enable(fsl_dev->tcon);
	fsl_dcu_drm_init_planes(fsl_dev->drm);
	enable_irq(fsl_dev->irq);

	drm_mode_config_helper_resume(fsl_dev->drm);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops fsl_dcu_drm_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fsl_dcu_drm_pm_suspend, fsl_dcu_drm_pm_resume)
पूर्ण;

अटल स्थिर काष्ठा fsl_dcu_soc_data fsl_dcu_ls1021a_data = अणु
	.name = "ls1021a",
	.total_layer = 16,
	.max_layer = 4,
	.layer_regs = LS1021A_LAYER_REG_NUM,
पूर्ण;

अटल स्थिर काष्ठा fsl_dcu_soc_data fsl_dcu_vf610_data = अणु
	.name = "vf610",
	.total_layer = 64,
	.max_layer = 6,
	.layer_regs = VF610_LAYER_REG_NUM,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_dcu_of_match[] = अणु
	अणु
		.compatible = "fsl,ls1021a-dcu",
		.data = &fsl_dcu_ls1021a_data,
	पूर्ण, अणु
		.compatible = "fsl,vf610-dcu",
		.data = &fsl_dcu_vf610_data,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_dcu_of_match);

अटल पूर्णांक fsl_dcu_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev;
	काष्ठा drm_device *drm;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	व्योम __iomem *base;
	काष्ठा clk *pix_clk_in;
	अक्षर pix_clk_name[32];
	स्थिर अक्षर *pix_clk_in_name;
	स्थिर काष्ठा of_device_id *id;
	पूर्णांक ret;
	u8 भाग_ratio_shअगरt = 0;

	fsl_dev = devm_kzalloc(dev, माप(*fsl_dev), GFP_KERNEL);
	अगर (!fsl_dev)
		वापस -ENOMEM;

	id = of_match_node(fsl_dcu_of_match, pdev->dev.of_node);
	अगर (!id)
		वापस -ENODEV;
	fsl_dev->soc = id->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		वापस ret;
	पूर्ण

	fsl_dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (fsl_dev->irq < 0) अणु
		dev_err(dev, "failed to get irq\n");
		वापस fsl_dev->irq;
	पूर्ण

	fsl_dev->regmap = devm_regmap_init_mmio(dev, base,
			&fsl_dcu_regmap_config);
	अगर (IS_ERR(fsl_dev->regmap)) अणु
		dev_err(dev, "regmap init failed\n");
		वापस PTR_ERR(fsl_dev->regmap);
	पूर्ण

	fsl_dev->clk = devm_clk_get(dev, "dcu");
	अगर (IS_ERR(fsl_dev->clk)) अणु
		dev_err(dev, "failed to get dcu clock\n");
		वापस PTR_ERR(fsl_dev->clk);
	पूर्ण
	ret = clk_prepare_enable(fsl_dev->clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable dcu clk\n");
		वापस ret;
	पूर्ण

	pix_clk_in = devm_clk_get(dev, "pix");
	अगर (IS_ERR(pix_clk_in)) अणु
		/* legancy binding, use dcu घड़ी as pixel घड़ी input */
		pix_clk_in = fsl_dev->clk;
	पूर्ण

	अगर (of_property_पढ़ो_bool(dev->of_node, "big-endian"))
		भाग_ratio_shअगरt = 24;

	pix_clk_in_name = __clk_get_name(pix_clk_in);
	snम_लिखो(pix_clk_name, माप(pix_clk_name), "%s_pix", pix_clk_in_name);
	fsl_dev->pix_clk = clk_रेजिस्टर_भागider(dev, pix_clk_name,
			pix_clk_in_name, 0, base + DCU_DIV_RATIO,
			भाग_ratio_shअगरt, 8, CLK_DIVIDER_ROUND_CLOSEST, शून्य);
	अगर (IS_ERR(fsl_dev->pix_clk)) अणु
		dev_err(dev, "failed to register pix clk\n");
		ret = PTR_ERR(fsl_dev->pix_clk);
		जाओ disable_clk;
	पूर्ण

	fsl_dev->tcon = fsl_tcon_init(dev);

	drm = drm_dev_alloc(&fsl_dcu_drm_driver, dev);
	अगर (IS_ERR(drm)) अणु
		ret = PTR_ERR(drm);
		जाओ unरेजिस्टर_pix_clk;
	पूर्ण

	fsl_dev->dev = dev;
	fsl_dev->drm = drm;
	fsl_dev->np = dev->of_node;
	drm->dev_निजी = fsl_dev;
	dev_set_drvdata(dev, fsl_dev);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0)
		जाओ put;

	drm_fbdev_generic_setup(drm, legacyfb_depth);

	वापस 0;

put:
	drm_dev_put(drm);
unरेजिस्टर_pix_clk:
	clk_unरेजिस्टर(fsl_dev->pix_clk);
disable_clk:
	clk_disable_unprepare(fsl_dev->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_dcu_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = platक्रमm_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(fsl_dev->drm);
	drm_dev_put(fsl_dev->drm);
	clk_disable_unprepare(fsl_dev->clk);
	clk_unरेजिस्टर(fsl_dev->pix_clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver fsl_dcu_drm_platक्रमm_driver = अणु
	.probe		= fsl_dcu_drm_probe,
	.हटाओ		= fsl_dcu_drm_हटाओ,
	.driver		= अणु
		.name	= "fsl-dcu",
		.pm	= &fsl_dcu_drm_pm_ops,
		.of_match_table = fsl_dcu_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(fsl_dcu_drm_platक्रमm_driver);

MODULE_DESCRIPTION("Freescale DCU DRM Driver");
MODULE_LICENSE("GPL");
