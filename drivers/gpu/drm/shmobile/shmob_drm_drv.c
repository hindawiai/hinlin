<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * shmob_drm_drv.c  --  SH Mobile DRM driver
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "shmob_drm_drv.h"
#समावेश "shmob_drm_kms.h"
#समावेश "shmob_drm_plane.h"
#समावेश "shmob_drm_regs.h"

/* -----------------------------------------------------------------------------
 * Hardware initialization
 */

अटल पूर्णांक shmob_drm_init_पूर्णांकerface(काष्ठा shmob_drm_device *sdev)
अणु
	अटल स्थिर u32 ldmt1r[] = अणु
		[SHMOB_DRM_IFACE_RGB8] = LDMT1R_MIFTYP_RGB8,
		[SHMOB_DRM_IFACE_RGB9] = LDMT1R_MIFTYP_RGB9,
		[SHMOB_DRM_IFACE_RGB12A] = LDMT1R_MIFTYP_RGB12A,
		[SHMOB_DRM_IFACE_RGB12B] = LDMT1R_MIFTYP_RGB12B,
		[SHMOB_DRM_IFACE_RGB16] = LDMT1R_MIFTYP_RGB16,
		[SHMOB_DRM_IFACE_RGB18] = LDMT1R_MIFTYP_RGB18,
		[SHMOB_DRM_IFACE_RGB24] = LDMT1R_MIFTYP_RGB24,
		[SHMOB_DRM_IFACE_YUV422] = LDMT1R_MIFTYP_YCBCR,
		[SHMOB_DRM_IFACE_SYS8A] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS8A,
		[SHMOB_DRM_IFACE_SYS8B] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS8B,
		[SHMOB_DRM_IFACE_SYS8C] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS8C,
		[SHMOB_DRM_IFACE_SYS8D] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS8D,
		[SHMOB_DRM_IFACE_SYS9] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS9,
		[SHMOB_DRM_IFACE_SYS12] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS12,
		[SHMOB_DRM_IFACE_SYS16A] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS16A,
		[SHMOB_DRM_IFACE_SYS16B] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS16B,
		[SHMOB_DRM_IFACE_SYS16C] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS16C,
		[SHMOB_DRM_IFACE_SYS18] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS18,
		[SHMOB_DRM_IFACE_SYS24] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS24,
	पूर्ण;

	अगर (sdev->pdata->अगरace.पूर्णांकerface >= ARRAY_SIZE(ldmt1r)) अणु
		dev_err(sdev->dev, "invalid interface type %u\n",
			sdev->pdata->अगरace.पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	sdev->ldmt1r = ldmt1r[sdev->pdata->अगरace.पूर्णांकerface];
	वापस 0;
पूर्ण

अटल पूर्णांक shmob_drm_setup_घड़ीs(काष्ठा shmob_drm_device *sdev,
					    क्रमागत shmob_drm_clk_source clksrc)
अणु
	काष्ठा clk *clk;
	अक्षर *clkname;

	चयन (clksrc) अणु
	हाल SHMOB_DRM_CLK_BUS:
		clkname = "bus_clk";
		sdev->lddckr = LDDCKR_ICKSEL_BUS;
		अवरोध;
	हाल SHMOB_DRM_CLK_PERIPHERAL:
		clkname = "peripheral_clk";
		sdev->lddckr = LDDCKR_ICKSEL_MIPI;
		अवरोध;
	हाल SHMOB_DRM_CLK_EXTERNAL:
		clkname = शून्य;
		sdev->lddckr = LDDCKR_ICKSEL_HDMI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	clk = devm_clk_get(sdev->dev, clkname);
	अगर (IS_ERR(clk)) अणु
		dev_err(sdev->dev, "cannot get dot clock %s\n", clkname);
		वापस PTR_ERR(clk);
	पूर्ण

	sdev->घड़ी = clk;
	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM operations
 */

अटल irqवापस_t shmob_drm_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = arg;
	काष्ठा shmob_drm_device *sdev = dev->dev_निजी;
	अचिन्हित दीर्घ flags;
	u32 status;

	/* Acknowledge पूर्णांकerrupts. Putting पूर्णांकerrupt enable and पूर्णांकerrupt flag
	 * bits in the same रेजिस्टर is really brain-dead design and requires
	 * taking a spinlock.
	 */
	spin_lock_irqsave(&sdev->irq_lock, flags);
	status = lcdc_पढ़ो(sdev, LDINTR);
	lcdc_ग_लिखो(sdev, LDINTR, status ^ LDINTR_STATUS_MASK);
	spin_unlock_irqrestore(&sdev->irq_lock, flags);

	अगर (status & LDINTR_VES) अणु
		drm_handle_vblank(dev, 0);
		shmob_drm_crtc_finish_page_flip(&sdev->crtc);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(shmob_drm_fops);

अटल स्थिर काष्ठा drm_driver shmob_drm_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET,
	.irq_handler		= shmob_drm_irq,
	DRM_GEM_CMA_DRIVER_OPS,
	.fops			= &shmob_drm_fops,
	.name			= "shmob-drm",
	.desc			= "Renesas SH Mobile DRM",
	.date			= "20120424",
	.major			= 1,
	.minor			= 0,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Power management
 */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक shmob_drm_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा shmob_drm_device *sdev = dev_get_drvdata(dev);

	drm_kms_helper_poll_disable(sdev->ddev);
	shmob_drm_crtc_suspend(&sdev->crtc);

	वापस 0;
पूर्ण

अटल पूर्णांक shmob_drm_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा shmob_drm_device *sdev = dev_get_drvdata(dev);

	drm_modeset_lock_all(sdev->ddev);
	shmob_drm_crtc_resume(&sdev->crtc);
	drm_modeset_unlock_all(sdev->ddev);

	drm_kms_helper_poll_enable(sdev->ddev);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops shmob_drm_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(shmob_drm_pm_suspend, shmob_drm_pm_resume)
पूर्ण;

/* -----------------------------------------------------------------------------
 * Platक्रमm driver
 */

अटल पूर्णांक shmob_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा shmob_drm_device *sdev = platक्रमm_get_drvdata(pdev);
	काष्ठा drm_device *ddev = sdev->ddev;

	drm_dev_unरेजिस्टर(ddev);
	drm_kms_helper_poll_fini(ddev);
	drm_irq_uninstall(ddev);
	drm_dev_put(ddev);

	वापस 0;
पूर्ण

अटल पूर्णांक shmob_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा shmob_drm_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा shmob_drm_device *sdev;
	काष्ठा drm_device *ddev;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Allocate and initialize the driver निजी data, I/O resources and
	 * घड़ीs.
	 */
	sdev = devm_kzalloc(&pdev->dev, माप(*sdev), GFP_KERNEL);
	अगर (sdev == शून्य)
		वापस -ENOMEM;

	sdev->dev = &pdev->dev;
	sdev->pdata = pdata;
	spin_lock_init(&sdev->irq_lock);

	platक्रमm_set_drvdata(pdev, sdev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sdev->mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(sdev->mmio))
		वापस PTR_ERR(sdev->mmio);

	ret = shmob_drm_setup_घड़ीs(sdev, pdata->clk_source);
	अगर (ret < 0)
		वापस ret;

	ret = shmob_drm_init_पूर्णांकerface(sdev);
	अगर (ret < 0)
		वापस ret;

	/* Allocate and initialize the DRM device. */
	ddev = drm_dev_alloc(&shmob_drm_driver, &pdev->dev);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	sdev->ddev = ddev;
	ddev->dev_निजी = sdev;

	ret = shmob_drm_modeset_init(sdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to initialize mode setting\n");
		जाओ err_मुक्त_drm_dev;
	पूर्ण

	क्रम (i = 0; i < 4; ++i) अणु
		ret = shmob_drm_plane_create(sdev, i);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to create plane %u\n", i);
			जाओ err_modeset_cleanup;
		पूर्ण
	पूर्ण

	ret = drm_vblank_init(ddev, 1);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to initialize vblank\n");
		जाओ err_modeset_cleanup;
	पूर्ण

	ret = drm_irq_install(ddev, platक्रमm_get_irq(pdev, 0));
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to install IRQ handler\n");
		जाओ err_modeset_cleanup;
	पूर्ण

	/*
	 * Register the DRM device with the core and the connectors with
	 * sysfs.
	 */
	ret = drm_dev_रेजिस्टर(ddev, 0);
	अगर (ret < 0)
		जाओ err_irq_uninstall;

	वापस 0;

err_irq_uninstall:
	drm_irq_uninstall(ddev);
err_modeset_cleanup:
	drm_kms_helper_poll_fini(ddev);
err_मुक्त_drm_dev:
	drm_dev_put(ddev);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver shmob_drm_platक्रमm_driver = अणु
	.probe		= shmob_drm_probe,
	.हटाओ		= shmob_drm_हटाओ,
	.driver		= अणु
		.name	= "shmob-drm",
		.pm	= &shmob_drm_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(shmob_drm_platक्रमm_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Renesas SH Mobile DRM Driver");
MODULE_LICENSE("GPL");
