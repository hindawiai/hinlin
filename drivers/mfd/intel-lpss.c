<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Sunrisepoपूर्णांक LPSS core support.
 *
 * Copyright (C) 2015, Intel Corporation
 *
 * Authors: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *          Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 *          Jarkko Nikula <jarkko.nikula@linux.पूर्णांकel.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/idr.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>

#समावेश <linux/dma/idma64.h>

#समावेश "intel-lpss.h"

#घोषणा LPSS_DEV_OFFSET		0x000
#घोषणा LPSS_DEV_SIZE		0x200
#घोषणा LPSS_PRIV_OFFSET	0x200
#घोषणा LPSS_PRIV_SIZE		0x100
#घोषणा LPSS_PRIV_REG_COUNT	(LPSS_PRIV_SIZE / 4)
#घोषणा LPSS_IDMA64_OFFSET	0x800
#घोषणा LPSS_IDMA64_SIZE	0x800

/* Offsets from lpss->priv */
#घोषणा LPSS_PRIV_RESETS		0x04
#घोषणा LPSS_PRIV_RESETS_IDMA		BIT(2)
#घोषणा LPSS_PRIV_RESETS_FUNC		0x3

#घोषणा LPSS_PRIV_ACTIVELTR		0x10
#घोषणा LPSS_PRIV_IDLELTR		0x14

#घोषणा LPSS_PRIV_LTR_REQ		BIT(15)
#घोषणा LPSS_PRIV_LTR_SCALE_MASK	GENMASK(11, 10)
#घोषणा LPSS_PRIV_LTR_SCALE_1US		(2 << 10)
#घोषणा LPSS_PRIV_LTR_SCALE_32US	(3 << 10)
#घोषणा LPSS_PRIV_LTR_VALUE_MASK	GENMASK(9, 0)

#घोषणा LPSS_PRIV_SSP_REG		0x20
#घोषणा LPSS_PRIV_SSP_REG_DIS_DMA_FIN	BIT(0)

#घोषणा LPSS_PRIV_REMAP_ADDR		0x40

#घोषणा LPSS_PRIV_CAPS			0xfc
#घोषणा LPSS_PRIV_CAPS_NO_IDMA		BIT(8)
#घोषणा LPSS_PRIV_CAPS_TYPE_MASK	GENMASK(7, 4)
#घोषणा LPSS_PRIV_CAPS_TYPE_SHIFT	4

/* This matches the type field in CAPS रेजिस्टर */
क्रमागत पूर्णांकel_lpss_dev_type अणु
	LPSS_DEV_I2C = 0,
	LPSS_DEV_UART,
	LPSS_DEV_SPI,
पूर्ण;

काष्ठा पूर्णांकel_lpss अणु
	स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info *info;
	क्रमागत पूर्णांकel_lpss_dev_type type;
	काष्ठा clk *clk;
	काष्ठा clk_lookup *घड़ी;
	काष्ठा mfd_cell *cell;
	काष्ठा device *dev;
	व्योम __iomem *priv;
	u32 priv_ctx[LPSS_PRIV_REG_COUNT];
	पूर्णांक devid;
	u32 caps;
	u32 active_ltr;
	u32 idle_ltr;
	काष्ठा dentry *debugfs;
पूर्ण;

अटल स्थिर काष्ठा resource पूर्णांकel_lpss_dev_resources[] = अणु
	DEFINE_RES_MEM_NAMED(LPSS_DEV_OFFSET, LPSS_DEV_SIZE, "lpss_dev"),
	DEFINE_RES_MEM_NAMED(LPSS_PRIV_OFFSET, LPSS_PRIV_SIZE, "lpss_priv"),
	DEFINE_RES_IRQ(0),
पूर्ण;

अटल स्थिर काष्ठा resource पूर्णांकel_lpss_idma64_resources[] = अणु
	DEFINE_RES_MEM(LPSS_IDMA64_OFFSET, LPSS_IDMA64_SIZE),
	DEFINE_RES_IRQ(0),
पूर्ण;

/*
 * Cells needs to be ordered so that the iDMA is created first. This is
 * because we need to be sure the DMA is available when the host controller
 * driver is probed.
 */
अटल स्थिर काष्ठा mfd_cell पूर्णांकel_lpss_idma64_cell = अणु
	.name = LPSS_IDMA64_DRIVER_NAME,
	.num_resources = ARRAY_SIZE(पूर्णांकel_lpss_idma64_resources),
	.resources = पूर्णांकel_lpss_idma64_resources,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell पूर्णांकel_lpss_i2c_cell = अणु
	.name = "i2c_designware",
	.num_resources = ARRAY_SIZE(पूर्णांकel_lpss_dev_resources),
	.resources = पूर्णांकel_lpss_dev_resources,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell पूर्णांकel_lpss_uart_cell = अणु
	.name = "dw-apb-uart",
	.num_resources = ARRAY_SIZE(पूर्णांकel_lpss_dev_resources),
	.resources = पूर्णांकel_lpss_dev_resources,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell पूर्णांकel_lpss_spi_cell = अणु
	.name = "pxa2xx-spi",
	.num_resources = ARRAY_SIZE(पूर्णांकel_lpss_dev_resources),
	.resources = पूर्णांकel_lpss_dev_resources,
पूर्ण;

अटल DEFINE_IDA(पूर्णांकel_lpss_devid_ida);
अटल काष्ठा dentry *पूर्णांकel_lpss_debugfs;

अटल व्योम पूर्णांकel_lpss_cache_ltr(काष्ठा पूर्णांकel_lpss *lpss)
अणु
	lpss->active_ltr = पढ़ोl(lpss->priv + LPSS_PRIV_ACTIVELTR);
	lpss->idle_ltr = पढ़ोl(lpss->priv + LPSS_PRIV_IDLELTR);
पूर्ण

अटल पूर्णांक पूर्णांकel_lpss_debugfs_add(काष्ठा पूर्णांकel_lpss *lpss)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir(dev_name(lpss->dev), पूर्णांकel_lpss_debugfs);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	/* Cache the values पूर्णांकo lpss काष्ठाure */
	पूर्णांकel_lpss_cache_ltr(lpss);

	debugfs_create_x32("capabilities", S_IRUGO, dir, &lpss->caps);
	debugfs_create_x32("active_ltr", S_IRUGO, dir, &lpss->active_ltr);
	debugfs_create_x32("idle_ltr", S_IRUGO, dir, &lpss->idle_ltr);

	lpss->debugfs = dir;
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_lpss_debugfs_हटाओ(काष्ठा पूर्णांकel_lpss *lpss)
अणु
	debugfs_हटाओ_recursive(lpss->debugfs);
पूर्ण

अटल व्योम पूर्णांकel_lpss_ltr_set(काष्ठा device *dev, s32 val)
अणु
	काष्ठा पूर्णांकel_lpss *lpss = dev_get_drvdata(dev);
	u32 ltr;

	/*
	 * Program latency tolerance (LTR) accordingly what has been asked
	 * by the PM QoS layer or disable it in हाल we were passed
	 * negative value or PM_QOS_LATENCY_ANY.
	 */
	ltr = पढ़ोl(lpss->priv + LPSS_PRIV_ACTIVELTR);

	अगर (val == PM_QOS_LATENCY_ANY || val < 0) अणु
		ltr &= ~LPSS_PRIV_LTR_REQ;
	पूर्ण अन्यथा अणु
		ltr |= LPSS_PRIV_LTR_REQ;
		ltr &= ~LPSS_PRIV_LTR_SCALE_MASK;
		ltr &= ~LPSS_PRIV_LTR_VALUE_MASK;

		अगर (val > LPSS_PRIV_LTR_VALUE_MASK)
			ltr |= LPSS_PRIV_LTR_SCALE_32US | val >> 5;
		अन्यथा
			ltr |= LPSS_PRIV_LTR_SCALE_1US | val;
	पूर्ण

	अगर (ltr == lpss->active_ltr)
		वापस;

	ग_लिखोl(ltr, lpss->priv + LPSS_PRIV_ACTIVELTR);
	ग_लिखोl(ltr, lpss->priv + LPSS_PRIV_IDLELTR);

	/* Cache the values पूर्णांकo lpss काष्ठाure */
	पूर्णांकel_lpss_cache_ltr(lpss);
पूर्ण

अटल व्योम पूर्णांकel_lpss_ltr_expose(काष्ठा पूर्णांकel_lpss *lpss)
अणु
	lpss->dev->घातer.set_latency_tolerance = पूर्णांकel_lpss_ltr_set;
	dev_pm_qos_expose_latency_tolerance(lpss->dev);
पूर्ण

अटल व्योम पूर्णांकel_lpss_ltr_hide(काष्ठा पूर्णांकel_lpss *lpss)
अणु
	dev_pm_qos_hide_latency_tolerance(lpss->dev);
	lpss->dev->घातer.set_latency_tolerance = शून्य;
पूर्ण

अटल पूर्णांक पूर्णांकel_lpss_assign_devs(काष्ठा पूर्णांकel_lpss *lpss)
अणु
	स्थिर काष्ठा mfd_cell *cell;
	अचिन्हित पूर्णांक type;

	type = lpss->caps & LPSS_PRIV_CAPS_TYPE_MASK;
	type >>= LPSS_PRIV_CAPS_TYPE_SHIFT;

	चयन (type) अणु
	हाल LPSS_DEV_I2C:
		cell = &पूर्णांकel_lpss_i2c_cell;
		अवरोध;
	हाल LPSS_DEV_UART:
		cell = &पूर्णांकel_lpss_uart_cell;
		अवरोध;
	हाल LPSS_DEV_SPI:
		cell = &पूर्णांकel_lpss_spi_cell;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	lpss->cell = devm_kmemdup(lpss->dev, cell, माप(*cell), GFP_KERNEL);
	अगर (!lpss->cell)
		वापस -ENOMEM;

	lpss->type = type;

	वापस 0;
पूर्ण

अटल bool पूर्णांकel_lpss_has_idma(स्थिर काष्ठा पूर्णांकel_lpss *lpss)
अणु
	वापस (lpss->caps & LPSS_PRIV_CAPS_NO_IDMA) == 0;
पूर्ण

अटल व्योम पूर्णांकel_lpss_set_remap_addr(स्थिर काष्ठा पूर्णांकel_lpss *lpss)
अणु
	resource_माप_प्रकार addr = lpss->info->mem->start;

	lo_hi_ग_लिखोq(addr, lpss->priv + LPSS_PRIV_REMAP_ADDR);
पूर्ण

अटल व्योम पूर्णांकel_lpss_deनिश्चित_reset(स्थिर काष्ठा पूर्णांकel_lpss *lpss)
अणु
	u32 value = LPSS_PRIV_RESETS_FUNC | LPSS_PRIV_RESETS_IDMA;

	/* Bring out the device from reset */
	ग_लिखोl(value, lpss->priv + LPSS_PRIV_RESETS);
पूर्ण

अटल व्योम पूर्णांकel_lpss_init_dev(स्थिर काष्ठा पूर्णांकel_lpss *lpss)
अणु
	u32 value = LPSS_PRIV_SSP_REG_DIS_DMA_FIN;

	/* Set the device in reset state */
	ग_लिखोl(0, lpss->priv + LPSS_PRIV_RESETS);

	पूर्णांकel_lpss_deनिश्चित_reset(lpss);

	पूर्णांकel_lpss_set_remap_addr(lpss);

	अगर (!पूर्णांकel_lpss_has_idma(lpss))
		वापस;

	/* Make sure that SPI multiblock DMA transfers are re-enabled */
	अगर (lpss->type == LPSS_DEV_SPI)
		ग_लिखोl(value, lpss->priv + LPSS_PRIV_SSP_REG);
पूर्ण

अटल व्योम पूर्णांकel_lpss_unरेजिस्टर_घड़ी_प्रकारree(काष्ठा clk *clk)
अणु
	काष्ठा clk *parent;

	जबतक (clk) अणु
		parent = clk_get_parent(clk);
		clk_unरेजिस्टर(clk);
		clk = parent;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_lpss_रेजिस्टर_घड़ी_भागider(काष्ठा पूर्णांकel_lpss *lpss,
					     स्थिर अक्षर *devname,
					     काष्ठा clk **clk)
अणु
	अक्षर name[32];
	काष्ठा clk *पंचांगp = *clk;

	snम_लिखो(name, माप(name), "%s-enable", devname);
	पंचांगp = clk_रेजिस्टर_gate(शून्य, name, __clk_get_name(पंचांगp), 0,
				lpss->priv, 0, 0, शून्य);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);

	snम_लिखो(name, माप(name), "%s-div", devname);
	पंचांगp = clk_रेजिस्टर_fractional_भागider(शून्य, name, __clk_get_name(पंचांगp),
					      0, lpss->priv, 1, 15, 16, 15, 0,
					      शून्य);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);
	*clk = पंचांगp;

	snम_लिखो(name, माप(name), "%s-update", devname);
	पंचांगp = clk_रेजिस्टर_gate(शून्य, name, __clk_get_name(पंचांगp),
				CLK_SET_RATE_PARENT, lpss->priv, 31, 0, शून्य);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);
	*clk = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_lpss_रेजिस्टर_घड़ी(काष्ठा पूर्णांकel_lpss *lpss)
अणु
	स्थिर काष्ठा mfd_cell *cell = lpss->cell;
	काष्ठा clk *clk;
	अक्षर devname[24];
	पूर्णांक ret;

	अगर (!lpss->info->clk_rate)
		वापस 0;

	/* Root घड़ी */
	clk = clk_रेजिस्टर_fixed_rate(शून्य, dev_name(lpss->dev), शून्य, 0,
				      lpss->info->clk_rate);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	snम_लिखो(devname, माप(devname), "%s.%d", cell->name, lpss->devid);

	/*
	 * Support क्रम घड़ी भागider only अगर it has some preset value.
	 * Otherwise we assume that the भागider is not used.
	 */
	अगर (lpss->type != LPSS_DEV_I2C) अणु
		ret = पूर्णांकel_lpss_रेजिस्टर_घड़ी_भागider(lpss, devname, &clk);
		अगर (ret)
			जाओ err_clk_रेजिस्टर;
	पूर्ण

	ret = -ENOMEM;

	/* Clock क्रम the host controller */
	lpss->घड़ी = clkdev_create(clk, lpss->info->clk_con_id, "%s", devname);
	अगर (!lpss->घड़ी)
		जाओ err_clk_रेजिस्टर;

	lpss->clk = clk;

	वापस 0;

err_clk_रेजिस्टर:
	पूर्णांकel_lpss_unरेजिस्टर_घड़ी_प्रकारree(clk);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_lpss_unरेजिस्टर_घड़ी(काष्ठा पूर्णांकel_lpss *lpss)
अणु
	अगर (IS_ERR_OR_शून्य(lpss->clk))
		वापस;

	clkdev_drop(lpss->घड़ी);
	पूर्णांकel_lpss_unरेजिस्टर_घड़ी_प्रकारree(lpss->clk);
पूर्ण

पूर्णांक पूर्णांकel_lpss_probe(काष्ठा device *dev,
		     स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info *info)
अणु
	काष्ठा पूर्णांकel_lpss *lpss;
	पूर्णांक ret;

	अगर (!info || !info->mem || info->irq <= 0)
		वापस -EINVAL;

	lpss = devm_kzalloc(dev, माप(*lpss), GFP_KERNEL);
	अगर (!lpss)
		वापस -ENOMEM;

	lpss->priv = devm_ioremap_uc(dev, info->mem->start + LPSS_PRIV_OFFSET,
				  LPSS_PRIV_SIZE);
	अगर (!lpss->priv)
		वापस -ENOMEM;

	lpss->info = info;
	lpss->dev = dev;
	lpss->caps = पढ़ोl(lpss->priv + LPSS_PRIV_CAPS);

	dev_set_drvdata(dev, lpss);

	ret = पूर्णांकel_lpss_assign_devs(lpss);
	अगर (ret)
		वापस ret;

	lpss->cell->swnode = info->swnode;

	पूर्णांकel_lpss_init_dev(lpss);

	lpss->devid = ida_simple_get(&पूर्णांकel_lpss_devid_ida, 0, 0, GFP_KERNEL);
	अगर (lpss->devid < 0)
		वापस lpss->devid;

	ret = पूर्णांकel_lpss_रेजिस्टर_घड़ी(lpss);
	अगर (ret)
		जाओ err_clk_रेजिस्टर;

	पूर्णांकel_lpss_ltr_expose(lpss);

	ret = पूर्णांकel_lpss_debugfs_add(lpss);
	अगर (ret)
		dev_warn(dev, "Failed to create debugfs entries\n");

	अगर (पूर्णांकel_lpss_has_idma(lpss)) अणु
		ret = mfd_add_devices(dev, lpss->devid, &पूर्णांकel_lpss_idma64_cell,
				      1, info->mem, info->irq, शून्य);
		अगर (ret)
			dev_warn(dev, "Failed to add %s, fallback to PIO\n",
				 LPSS_IDMA64_DRIVER_NAME);
	पूर्ण

	ret = mfd_add_devices(dev, lpss->devid, lpss->cell,
			      1, info->mem, info->irq, शून्य);
	अगर (ret)
		जाओ err_हटाओ_ltr;

	dev_pm_set_driver_flags(dev, DPM_FLAG_SMART_SUSPEND);

	वापस 0;

err_हटाओ_ltr:
	पूर्णांकel_lpss_debugfs_हटाओ(lpss);
	पूर्णांकel_lpss_ltr_hide(lpss);
	पूर्णांकel_lpss_unरेजिस्टर_घड़ी(lpss);

err_clk_रेजिस्टर:
	ida_simple_हटाओ(&पूर्णांकel_lpss_devid_ida, lpss->devid);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_lpss_probe);

व्योम पूर्णांकel_lpss_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_lpss *lpss = dev_get_drvdata(dev);

	mfd_हटाओ_devices(dev);
	पूर्णांकel_lpss_debugfs_हटाओ(lpss);
	पूर्णांकel_lpss_ltr_hide(lpss);
	पूर्णांकel_lpss_unरेजिस्टर_घड़ी(lpss);
	ida_simple_हटाओ(&पूर्णांकel_lpss_devid_ida, lpss->devid);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_lpss_हटाओ);

अटल पूर्णांक resume_lpss_device(काष्ठा device *dev, व्योम *data)
अणु
	अगर (!dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND))
		pm_runसमय_resume(dev);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_lpss_prepare(काष्ठा device *dev)
अणु
	/*
	 * Resume both child devices beक्रमe entering प्रणाली sleep. This
	 * ensures that they are in proper state beक्रमe they get suspended.
	 */
	device_क्रम_each_child_reverse(dev, शून्य, resume_lpss_device);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_lpss_prepare);

पूर्णांक पूर्णांकel_lpss_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_lpss *lpss = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	/* Save device context */
	क्रम (i = 0; i < LPSS_PRIV_REG_COUNT; i++)
		lpss->priv_ctx[i] = पढ़ोl(lpss->priv + i * 4);

	/*
	 * If the device type is not UART, then put the controller पूर्णांकo
	 * reset. UART cannot be put पूर्णांकo reset since S3/S0ix fail when
	 * no_console_suspend flag is enabled.
	 */
	अगर (lpss->type != LPSS_DEV_UART)
		ग_लिखोl(0, lpss->priv + LPSS_PRIV_RESETS);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_lpss_suspend);

पूर्णांक पूर्णांकel_lpss_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_lpss *lpss = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	पूर्णांकel_lpss_deनिश्चित_reset(lpss);

	/* Restore device context */
	क्रम (i = 0; i < LPSS_PRIV_REG_COUNT; i++)
		ग_लिखोl(lpss->priv_ctx[i], lpss->priv + i * 4);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_lpss_resume);

अटल पूर्णांक __init पूर्णांकel_lpss_init(व्योम)
अणु
	पूर्णांकel_lpss_debugfs = debugfs_create_dir("intel_lpss", शून्य);
	वापस 0;
पूर्ण
module_init(पूर्णांकel_lpss_init);

अटल व्योम __निकास पूर्णांकel_lpss_निकास(व्योम)
अणु
	ida_destroy(&पूर्णांकel_lpss_devid_ida);
	debugfs_हटाओ(पूर्णांकel_lpss_debugfs);
पूर्ण
module_निकास(पूर्णांकel_lpss_निकास);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_AUTHOR("Heikki Krogerus <heikki.krogerus@linux.intel.com>");
MODULE_AUTHOR("Jarkko Nikula <jarkko.nikula@linux.intel.com>");
MODULE_DESCRIPTION("Intel LPSS core driver");
MODULE_LICENSE("GPL v2");
/*
 * Ensure the DMA driver is loaded beक्रमe the host controller device appears,
 * so that the host controller driver can request its DMA channels as early
 * as possible.
 *
 * If the DMA module is not there that's OK as well.
 */
MODULE_SOFTDEP("pre: platform:" LPSS_IDMA64_DRIVER_NAME);
