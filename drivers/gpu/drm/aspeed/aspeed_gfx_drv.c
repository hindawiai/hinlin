<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2018 IBM Corporation

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_drv.h>

#समावेश "aspeed_gfx.h"

/**
 * DOC: ASPEED GFX Driver
 *
 * This driver is क्रम the ASPEED BMC SoC's 'GFX' display hardware, also called
 * the 'SOC Display Controller' in the datasheet. This driver runs on the ARM
 * based BMC प्रणालीs, unlike the ast driver which runs on a host CPU and is क्रम
 * a PCIe graphics device.
 *
 * The AST2500 supports a total of 3 output paths:
 *
 *   1. VGA output, the output target can choose either or both to the DAC
 *   or DVO पूर्णांकerface.
 *
 *   2. Graphics CRT output, the output target can choose either or both to
 *   the DAC or DVO पूर्णांकerface.
 *
 *   3. Video input from DVO, the video input can be used क्रम video engine
 *   capture or DAC display output.
 *
 * Output options are selected in SCU2C.
 *
 * The "VGA mode" device is the PCI attached controller. The "Graphics CRT"
 * is the ARM's पूर्णांकernal display controller.
 *
 * The driver only supports a simple configuration consisting of a 40MHz
 * pixel घड़ी, fixed by hardware limitations, and the VGA output path.
 *
 * The driver was written with the 'AST2500 Software Programming Guide' v17,
 * which is available under NDA from ASPEED.
 */

काष्ठा aspeed_gfx_config अणु
	u32 dac_reg;		/* DAC रेजिस्टर in SCU */
	u32 vga_scratch_reg;	/* VGA scratch रेजिस्टर in SCU */
	u32 throd_val;		/* Default Threshold Seting */
	u32 scan_line_max;	/* Max memory size of one scan line */
पूर्ण;

अटल स्थिर काष्ठा aspeed_gfx_config ast2400_config = अणु
	.dac_reg = 0x2c,
	.vga_scratch_reg = 0x50,
	.throd_val = CRT_THROD_LOW(0x1e) | CRT_THROD_HIGH(0x12),
	.scan_line_max = 64,
पूर्ण;

अटल स्थिर काष्ठा aspeed_gfx_config ast2500_config = अणु
	.dac_reg = 0x2c,
	.vga_scratch_reg = 0x50,
	.throd_val = CRT_THROD_LOW(0x24) | CRT_THROD_HIGH(0x3c),
	.scan_line_max = 128,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_gfx_match[] = अणु
	अणु .compatible = "aspeed,ast2400-gfx", .data = &ast2400_config पूर्ण,
	अणु .compatible = "aspeed,ast2500-gfx", .data = &ast2500_config पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aspeed_gfx_match);

अटल स्थिर काष्ठा drm_mode_config_funcs aspeed_gfx_mode_config_funcs = अणु
	.fb_create		= drm_gem_fb_create,
	.atomic_check		= drm_atomic_helper_check,
	.atomic_commit		= drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक aspeed_gfx_setup_mode_config(काष्ठा drm_device *drm)
अणु
	पूर्णांक ret;

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;

	drm->mode_config.min_width = 0;
	drm->mode_config.min_height = 0;
	drm->mode_config.max_width = 800;
	drm->mode_config.max_height = 600;
	drm->mode_config.funcs = &aspeed_gfx_mode_config_funcs;

	वापस ret;
पूर्ण

अटल irqवापस_t aspeed_gfx_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा aspeed_gfx *priv = to_aspeed_gfx(drm);
	u32 reg;

	reg = पढ़ोl(priv->base + CRT_CTRL1);

	अगर (reg & CRT_CTRL_VERTICAL_INTR_STS) अणु
		drm_crtc_handle_vblank(&priv->pipe.crtc);
		ग_लिखोl(reg, priv->base + CRT_CTRL1);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक aspeed_gfx_load(काष्ठा drm_device *drm)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(drm->dev);
	काष्ठा aspeed_gfx *priv = to_aspeed_gfx(drm);
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा aspeed_gfx_config *config;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(drm->dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	match = of_match_device(aspeed_gfx_match, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;
	config = match->data;

	priv->dac_reg = config->dac_reg;
	priv->vga_scratch_reg = config->vga_scratch_reg;
	priv->throd_val = config->throd_val;
	priv->scan_line_max = config->scan_line_max;

	priv->scu = syscon_regmap_lookup_by_phandle(np, "syscon");
	अगर (IS_ERR(priv->scu)) अणु
		priv->scu = syscon_regmap_lookup_by_compatible("aspeed,ast2500-scu");
		अगर (IS_ERR(priv->scu)) अणु
			dev_err(&pdev->dev, "failed to find SCU regmap\n");
			वापस PTR_ERR(priv->scu);
		पूर्ण
	पूर्ण

	ret = of_reserved_mem_device_init(drm->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to initialize reserved mem: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = dma_set_mask_and_coherent(drm->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to set DMA mask: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->rst = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->rst)) अणु
		dev_err(&pdev->dev,
			"missing or invalid reset controller device tree entry");
		वापस PTR_ERR(priv->rst);
	पूर्ण
	reset_control_deनिश्चित(priv->rst);

	priv->clk = devm_clk_get(drm->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev,
			"missing or invalid clk device tree entry");
		वापस PTR_ERR(priv->clk);
	पूर्ण
	clk_prepare_enable(priv->clk);

	/* Sanitize control रेजिस्टरs */
	ग_लिखोl(0, priv->base + CRT_CTRL1);
	ग_लिखोl(0, priv->base + CRT_CTRL2);

	ret = aspeed_gfx_setup_mode_config(drm);
	अगर (ret < 0)
		वापस ret;

	ret = drm_vblank_init(drm, 1);
	अगर (ret < 0) अणु
		dev_err(drm->dev, "Failed to initialise vblank\n");
		वापस ret;
	पूर्ण

	ret = aspeed_gfx_create_output(drm);
	अगर (ret < 0) अणु
		dev_err(drm->dev, "Failed to create outputs\n");
		वापस ret;
	पूर्ण

	ret = aspeed_gfx_create_pipe(drm);
	अगर (ret < 0) अणु
		dev_err(drm->dev, "Cannot setup simple display pipe\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(drm->dev, platक्रमm_get_irq(pdev, 0),
			       aspeed_gfx_irq_handler, 0, "aspeed gfx", drm);
	अगर (ret < 0) अणु
		dev_err(drm->dev, "Failed to install IRQ handler\n");
		वापस ret;
	पूर्ण

	drm_mode_config_reset(drm);

	वापस 0;
पूर्ण

अटल व्योम aspeed_gfx_unload(काष्ठा drm_device *drm)
अणु
	drm_kms_helper_poll_fini(drm);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(fops);

अटल स्थिर काष्ठा drm_driver aspeed_gfx_driver = अणु
	.driver_features        = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	DRM_GEM_CMA_DRIVER_OPS,
	.fops = &fops,
	.name = "aspeed-gfx-drm",
	.desc = "ASPEED GFX DRM",
	.date = "20180319",
	.major = 1,
	.minor = 0,
पूर्ण;

अटल sमाप_प्रकार dac_mux_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा aspeed_gfx *priv = dev_get_drvdata(dev);
	u32 val;
	पूर्णांक rc;

	rc = kstrtou32(buf, 0, &val);
	अगर (rc)
		वापस rc;

	अगर (val > 3)
		वापस -EINVAL;

	rc = regmap_update_bits(priv->scu, priv->dac_reg, 0x30000, val << 16);
	अगर (rc < 0)
		वापस 0;

	वापस count;
पूर्ण

अटल sमाप_प्रकार dac_mux_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aspeed_gfx *priv = dev_get_drvdata(dev);
	u32 reg;
	पूर्णांक rc;

	rc = regmap_पढ़ो(priv->scu, priv->dac_reg, &reg);
	अगर (rc)
		वापस rc;

	वापस प्र_लिखो(buf, "%u\n", (reg >> 16) & 0x3);
पूर्ण
अटल DEVICE_ATTR_RW(dac_mux);

अटल sमाप_प्रकार
vga_pw_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा aspeed_gfx *priv = dev_get_drvdata(dev);
	u32 reg;
	पूर्णांक rc;

	rc = regmap_पढ़ो(priv->scu, priv->vga_scratch_reg, &reg);
	अगर (rc)
		वापस rc;

	वापस प्र_लिखो(buf, "%u\n", reg & 1);
पूर्ण
अटल DEVICE_ATTR_RO(vga_pw);

अटल काष्ठा attribute *aspeed_sysfs_entries[] = अणु
	&dev_attr_vga_pw.attr,
	&dev_attr_dac_mux.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group aspeed_sysfs_attr_group = अणु
	.attrs = aspeed_sysfs_entries,
पूर्ण;

अटल पूर्णांक aspeed_gfx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_gfx *priv;
	पूर्णांक ret;

	priv = devm_drm_dev_alloc(&pdev->dev, &aspeed_gfx_driver,
				  काष्ठा aspeed_gfx, drm);
	अगर (IS_ERR(priv))
		वापस PTR_ERR(priv);

	ret = aspeed_gfx_load(&priv->drm);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	ret = sysfs_create_group(&pdev->dev.kobj, &aspeed_sysfs_attr_group);
	अगर (ret)
		वापस ret;

	ret = drm_dev_रेजिस्टर(&priv->drm, 0);
	अगर (ret)
		जाओ err_unload;

	drm_fbdev_generic_setup(&priv->drm, 32);
	वापस 0;

err_unload:
	sysfs_हटाओ_group(&pdev->dev.kobj, &aspeed_sysfs_attr_group);
	aspeed_gfx_unload(&priv->drm);

	वापस ret;
पूर्ण

अटल पूर्णांक aspeed_gfx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);

	sysfs_हटाओ_group(&pdev->dev.kobj, &aspeed_sysfs_attr_group);
	drm_dev_unरेजिस्टर(drm);
	aspeed_gfx_unload(drm);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aspeed_gfx_platक्रमm_driver = अणु
	.probe		= aspeed_gfx_probe,
	.हटाओ		= aspeed_gfx_हटाओ,
	.driver = अणु
		.name = "aspeed_gfx",
		.of_match_table = aspeed_gfx_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aspeed_gfx_platक्रमm_driver);

MODULE_AUTHOR("Joel Stanley <joel@jms.id.au>");
MODULE_DESCRIPTION("ASPEED BMC DRM/KMS driver");
MODULE_LICENSE("GPL");
