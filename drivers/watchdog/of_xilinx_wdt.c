<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg Device Driver क्रम Xilinx axi/xps_समयbase_wdt
 *
 * (C) Copyright 2013 - 2014 Xilinx, Inc.
 * (C) Copyright 2011 (Alejandro Cabrera <aldaya@gmail.com>)
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>

/* Register offsets क्रम the Wdt device */
#घोषणा XWT_TWCSR0_OFFSET   0x0 /* Control/Status Register0 */
#घोषणा XWT_TWCSR1_OFFSET   0x4 /* Control/Status Register1 */
#घोषणा XWT_TBR_OFFSET      0x8 /* Timebase Register Offset */

/* Control/Status Register Masks  */
#घोषणा XWT_CSR0_WRS_MASK   0x00000008 /* Reset status */
#घोषणा XWT_CSR0_WDS_MASK   0x00000004 /* Timer state  */
#घोषणा XWT_CSR0_EWDT1_MASK 0x00000002 /* Enable bit 1 */

/* Control/Status Register 0/1 bits  */
#घोषणा XWT_CSRX_EWDT2_MASK 0x00000001 /* Enable bit 2 */

/* SelfTest स्थिरants */
#घोषणा XWT_MAX_SELFTEST_LOOP_COUNT 0x00010000
#घोषणा XWT_TIMER_FAILED            0xFFFFFFFF

#घोषणा WATCHDOG_NAME     "Xilinx Watchdog"

काष्ठा xwdt_device अणु
	व्योम __iomem *base;
	u32 wdt_पूर्णांकerval;
	spinlock_t spinlock;
	काष्ठा watchकरोg_device xilinx_wdt_wdd;
	काष्ठा clk		*clk;
पूर्ण;

अटल पूर्णांक xilinx_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक ret;
	u32 control_status_reg;
	काष्ठा xwdt_device *xdev = watchकरोg_get_drvdata(wdd);

	ret = clk_enable(xdev->clk);
	अगर (ret) अणु
		dev_err(wdd->parent, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	spin_lock(&xdev->spinlock);

	/* Clean previous status and enable the watchकरोg समयr */
	control_status_reg = ioपढ़ो32(xdev->base + XWT_TWCSR0_OFFSET);
	control_status_reg |= (XWT_CSR0_WRS_MASK | XWT_CSR0_WDS_MASK);

	ioग_लिखो32((control_status_reg | XWT_CSR0_EWDT1_MASK),
		  xdev->base + XWT_TWCSR0_OFFSET);

	ioग_लिखो32(XWT_CSRX_EWDT2_MASK, xdev->base + XWT_TWCSR1_OFFSET);

	spin_unlock(&xdev->spinlock);

	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	u32 control_status_reg;
	काष्ठा xwdt_device *xdev = watchकरोg_get_drvdata(wdd);

	spin_lock(&xdev->spinlock);

	control_status_reg = ioपढ़ो32(xdev->base + XWT_TWCSR0_OFFSET);

	ioग_लिखो32((control_status_reg & ~XWT_CSR0_EWDT1_MASK),
		  xdev->base + XWT_TWCSR0_OFFSET);

	ioग_लिखो32(0, xdev->base + XWT_TWCSR1_OFFSET);

	spin_unlock(&xdev->spinlock);

	clk_disable(xdev->clk);

	pr_info("Stopped!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_wdt_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	u32 control_status_reg;
	काष्ठा xwdt_device *xdev = watchकरोg_get_drvdata(wdd);

	spin_lock(&xdev->spinlock);

	control_status_reg = ioपढ़ो32(xdev->base + XWT_TWCSR0_OFFSET);
	control_status_reg |= (XWT_CSR0_WRS_MASK | XWT_CSR0_WDS_MASK);
	ioग_लिखो32(control_status_reg, xdev->base + XWT_TWCSR0_OFFSET);

	spin_unlock(&xdev->spinlock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info xilinx_wdt_ident = अणु
	.options =  WDIOF_MAGICCLOSE |
		    WDIOF_KEEPALIVEPING,
	.firmware_version =	1,
	.identity =	WATCHDOG_NAME,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops xilinx_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = xilinx_wdt_start,
	.stop = xilinx_wdt_stop,
	.ping = xilinx_wdt_keepalive,
पूर्ण;

अटल u32 xwdt_selftest(काष्ठा xwdt_device *xdev)
अणु
	पूर्णांक i;
	u32 समयr_value1;
	u32 समयr_value2;

	spin_lock(&xdev->spinlock);

	समयr_value1 = ioपढ़ो32(xdev->base + XWT_TBR_OFFSET);
	समयr_value2 = ioपढ़ो32(xdev->base + XWT_TBR_OFFSET);

	क्रम (i = 0;
		((i <= XWT_MAX_SELFTEST_LOOP_COUNT) &&
			(समयr_value2 == समयr_value1)); i++) अणु
		समयr_value2 = ioपढ़ो32(xdev->base + XWT_TBR_OFFSET);
	पूर्ण

	spin_unlock(&xdev->spinlock);

	अगर (समयr_value2 != समयr_value1)
		वापस ~XWT_TIMER_FAILED;
	अन्यथा
		वापस XWT_TIMER_FAILED;
पूर्ण

अटल व्योम xwdt_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक xwdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक rc;
	u32 pfreq = 0, enable_once = 0;
	काष्ठा xwdt_device *xdev;
	काष्ठा watchकरोg_device *xilinx_wdt_wdd;

	xdev = devm_kzalloc(dev, माप(*xdev), GFP_KERNEL);
	अगर (!xdev)
		वापस -ENOMEM;

	xilinx_wdt_wdd = &xdev->xilinx_wdt_wdd;
	xilinx_wdt_wdd->info = &xilinx_wdt_ident;
	xilinx_wdt_wdd->ops = &xilinx_wdt_ops;
	xilinx_wdt_wdd->parent = dev;

	xdev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xdev->base))
		वापस PTR_ERR(xdev->base);

	rc = of_property_पढ़ो_u32(dev->of_node, "xlnx,wdt-interval",
				  &xdev->wdt_पूर्णांकerval);
	अगर (rc)
		dev_warn(dev, "Parameter \"xlnx,wdt-interval\" not found\n");

	rc = of_property_पढ़ो_u32(dev->of_node, "xlnx,wdt-enable-once",
				  &enable_once);
	अगर (rc)
		dev_warn(dev,
			 "Parameter \"xlnx,wdt-enable-once\" not found\n");

	watchकरोg_set_nowayout(xilinx_wdt_wdd, enable_once);

	xdev->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(xdev->clk)) अणु
		अगर (PTR_ERR(xdev->clk) != -ENOENT)
			वापस PTR_ERR(xdev->clk);

		/*
		 * Clock framework support is optional, जारी on
		 * anyways अगर we करोn't find a matching घड़ी.
		 */
		xdev->clk = शून्य;

		rc = of_property_पढ़ो_u32(dev->of_node, "clock-frequency",
					  &pfreq);
		अगर (rc)
			dev_warn(dev,
				 "The watchdog clock freq cannot be obtained\n");
	पूर्ण अन्यथा अणु
		pfreq = clk_get_rate(xdev->clk);
	पूर्ण

	/*
	 * Twice of the 2^wdt_पूर्णांकerval / freq  because the first wdt overflow is
	 * ignored (पूर्णांकerrupt), reset is only generated at second wdt overflow
	 */
	अगर (pfreq && xdev->wdt_पूर्णांकerval)
		xilinx_wdt_wdd->समयout = 2 * ((1 << xdev->wdt_पूर्णांकerval) /
					  pfreq);

	spin_lock_init(&xdev->spinlock);
	watchकरोg_set_drvdata(xilinx_wdt_wdd, xdev);

	rc = clk_prepare_enable(xdev->clk);
	अगर (rc) अणु
		dev_err(dev, "unable to enable clock\n");
		वापस rc;
	पूर्ण
	rc = devm_add_action_or_reset(dev, xwdt_clk_disable_unprepare,
				      xdev->clk);
	अगर (rc)
		वापस rc;

	rc = xwdt_selftest(xdev);
	अगर (rc == XWT_TIMER_FAILED) अणु
		dev_err(dev, "SelfTest routine error\n");
		वापस rc;
	पूर्ण

	rc = devm_watchकरोg_रेजिस्टर_device(dev, xilinx_wdt_wdd);
	अगर (rc)
		वापस rc;

	clk_disable(xdev->clk);

	dev_info(dev, "Xilinx Watchdog Timer at %p with timeout %ds\n",
		 xdev->base, xilinx_wdt_wdd->समयout);

	platक्रमm_set_drvdata(pdev, xdev);

	वापस 0;
पूर्ण

/**
 * xwdt_suspend - Suspend the device.
 *
 * @dev: handle to the device काष्ठाure.
 * Return: 0 always.
 */
अटल पूर्णांक __maybe_unused xwdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा xwdt_device *xdev = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&xdev->xilinx_wdt_wdd))
		xilinx_wdt_stop(&xdev->xilinx_wdt_wdd);

	वापस 0;
पूर्ण

/**
 * xwdt_resume - Resume the device.
 *
 * @dev: handle to the device काष्ठाure.
 * Return: 0 on success, त्रुटि_सं otherwise.
 */
अटल पूर्णांक __maybe_unused xwdt_resume(काष्ठा device *dev)
अणु
	काष्ठा xwdt_device *xdev = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (watchकरोg_active(&xdev->xilinx_wdt_wdd))
		ret = xilinx_wdt_start(&xdev->xilinx_wdt_wdd);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(xwdt_pm_ops, xwdt_suspend, xwdt_resume);

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id xwdt_of_match[] = अणु
	अणु .compatible = "xlnx,xps-timebase-wdt-1.00.a", पूर्ण,
	अणु .compatible = "xlnx,xps-timebase-wdt-1.01.a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xwdt_of_match);

अटल काष्ठा platक्रमm_driver xwdt_driver = अणु
	.probe       = xwdt_probe,
	.driver = अणु
		.name  = WATCHDOG_NAME,
		.of_match_table = xwdt_of_match,
		.pm = &xwdt_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xwdt_driver);

MODULE_AUTHOR("Alejandro Cabrera <aldaya@gmail.com>");
MODULE_DESCRIPTION("Xilinx Watchdog driver");
MODULE_LICENSE("GPL");
