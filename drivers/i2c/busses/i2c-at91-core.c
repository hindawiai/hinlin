<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  i2c Support क्रम Aपंचांगel's AT91 Two-Wire Interface (TWI)
 *
 *  Copyright (C) 2011 Weinmann Medical GmbH
 *  Author: Nikolaus Voss <n.voss@weinmann.de>
 *
 *  Evolved from original work by:
 *  Copyright (C) 2004 Rick Bronson
 *  Converted to 2.6 by Andrew Victor <andrew@sanpeople.com>
 *
 *  Borrowed heavily from original work by:
 *  Copyright (C) 2000 Philip Edelbrock <phil@stimpy.netroedge.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pinctrl/consumer.h>

#समावेश "i2c-at91.h"

अचिन्हित at91_twi_पढ़ो(काष्ठा at91_twi_dev *dev, अचिन्हित reg)
अणु
	वापस पढ़ोl_relaxed(dev->base + reg);
पूर्ण

व्योम at91_twi_ग_लिखो(काष्ठा at91_twi_dev *dev, अचिन्हित reg, अचिन्हित val)
अणु
	ग_लिखोl_relaxed(val, dev->base + reg);
पूर्ण

व्योम at91_disable_twi_पूर्णांकerrupts(काष्ठा at91_twi_dev *dev)
अणु
	at91_twi_ग_लिखो(dev, AT91_TWI_IDR, AT91_TWI_INT_MASK);
पूर्ण

व्योम at91_twi_irq_save(काष्ठा at91_twi_dev *dev)
अणु
	dev->imr = at91_twi_पढ़ो(dev, AT91_TWI_IMR) & AT91_TWI_INT_MASK;
	at91_disable_twi_पूर्णांकerrupts(dev);
पूर्ण

व्योम at91_twi_irq_restore(काष्ठा at91_twi_dev *dev)
अणु
	at91_twi_ग_लिखो(dev, AT91_TWI_IER, dev->imr);
पूर्ण

व्योम at91_init_twi_bus(काष्ठा at91_twi_dev *dev)
अणु
	at91_disable_twi_पूर्णांकerrupts(dev);
	at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_SWRST);
	अगर (dev->slave_detected)
		at91_init_twi_bus_slave(dev);
	अन्यथा
		at91_init_twi_bus_master(dev);
पूर्ण

अटल काष्ठा at91_twi_pdata at91rm9200_config = अणु
	.clk_max_भाग = 5,
	.clk_offset = 3,
	.has_unre_flag = true,
पूर्ण;

अटल काष्ठा at91_twi_pdata at91sam9261_config = अणु
	.clk_max_भाग = 5,
	.clk_offset = 4,
पूर्ण;

अटल काष्ठा at91_twi_pdata at91sam9260_config = अणु
	.clk_max_भाग = 7,
	.clk_offset = 4,
पूर्ण;

अटल काष्ठा at91_twi_pdata at91sam9g20_config = अणु
	.clk_max_भाग = 7,
	.clk_offset = 4,
पूर्ण;

अटल काष्ठा at91_twi_pdata at91sam9g10_config = अणु
	.clk_max_भाग = 7,
	.clk_offset = 4,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id at91_twi_devtypes[] = अणु
	अणु
		.name = "i2c-at91rm9200",
		.driver_data = (अचिन्हित दीर्घ) &at91rm9200_config,
	पूर्ण, अणु
		.name = "i2c-at91sam9261",
		.driver_data = (अचिन्हित दीर्घ) &at91sam9261_config,
	पूर्ण, अणु
		.name = "i2c-at91sam9260",
		.driver_data = (अचिन्हित दीर्घ) &at91sam9260_config,
	पूर्ण, अणु
		.name = "i2c-at91sam9g20",
		.driver_data = (अचिन्हित दीर्घ) &at91sam9g20_config,
	पूर्ण, अणु
		.name = "i2c-at91sam9g10",
		.driver_data = (अचिन्हित दीर्घ) &at91sam9g10_config,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

#अगर defined(CONFIG_OF)
अटल काष्ठा at91_twi_pdata at91sam9x5_config = अणु
	.clk_max_भाग = 7,
	.clk_offset = 4,
पूर्ण;

अटल काष्ठा at91_twi_pdata sama5d4_config = अणु
	.clk_max_भाग = 7,
	.clk_offset = 4,
	.has_hold_field = true,
	.has_dig_filtr = true,
पूर्ण;

अटल काष्ठा at91_twi_pdata sama5d2_config = अणु
	.clk_max_भाग = 7,
	.clk_offset = 3,
	.has_unre_flag = true,
	.has_alt_cmd = true,
	.has_hold_field = true,
	.has_dig_filtr = true,
	.has_adv_dig_filtr = true,
	.has_ana_filtr = true,
	.has_clear_cmd = false,	/* due to errata, CLEAR cmd is not working */
पूर्ण;

अटल काष्ठा at91_twi_pdata sam9x60_config = अणु
	.clk_max_भाग = 7,
	.clk_offset = 3,
	.has_unre_flag = true,
	.has_alt_cmd = true,
	.has_hold_field = true,
	.has_dig_filtr = true,
	.has_adv_dig_filtr = true,
	.has_ana_filtr = true,
	.has_clear_cmd = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_twi_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91rm9200-i2c",
		.data = &at91rm9200_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9260-i2c",
		.data = &at91sam9260_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9261-i2c",
		.data = &at91sam9261_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9g20-i2c",
		.data = &at91sam9g20_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9g10-i2c",
		.data = &at91sam9g10_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9x5-i2c",
		.data = &at91sam9x5_config,
	पूर्ण, अणु
		.compatible = "atmel,sama5d4-i2c",
		.data = &sama5d4_config,
	पूर्ण, अणु
		.compatible = "atmel,sama5d2-i2c",
		.data = &sama5d2_config,
	पूर्ण, अणु
		.compatible = "microchip,sam9x60-i2c",
		.data = &sam9x60_config,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_twi_dt_ids);
#पूर्ण_अगर

अटल काष्ठा at91_twi_pdata *at91_twi_get_driver_data(
					काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;
		match = of_match_node(aपंचांगel_twi_dt_ids, pdev->dev.of_node);
		अगर (!match)
			वापस शून्य;
		वापस (काष्ठा at91_twi_pdata *)match->data;
	पूर्ण
	वापस (काष्ठा at91_twi_pdata *) platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

अटल पूर्णांक at91_twi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_twi_dev *dev;
	काष्ठा resource *mem;
	पूर्णांक rc;
	u32 phy_addr;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->dev = &pdev->dev;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem)
		वापस -ENODEV;
	phy_addr = mem->start;

	dev->pdata = at91_twi_get_driver_data(pdev);
	अगर (!dev->pdata)
		वापस -ENODEV;

	dev->base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(dev->base))
		वापस PTR_ERR(dev->base);

	dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dev->irq < 0)
		वापस dev->irq;

	platक्रमm_set_drvdata(pdev, dev);

	dev->clk = devm_clk_get(dev->dev, शून्य);
	अगर (IS_ERR(dev->clk)) अणु
		dev_err(dev->dev, "no clock defined\n");
		वापस -ENODEV;
	पूर्ण
	clk_prepare_enable(dev->clk);

	snम_लिखो(dev->adapter.name, माप(dev->adapter.name), "AT91");
	i2c_set_adapdata(&dev->adapter, dev);
	dev->adapter.owner = THIS_MODULE;
	dev->adapter.class = I2C_CLASS_DEPRECATED;
	dev->adapter.dev.parent = dev->dev;
	dev->adapter.nr = pdev->id;
	dev->adapter.समयout = AT91_I2C_TIMEOUT;
	dev->adapter.dev.of_node = pdev->dev.of_node;

	dev->slave_detected = i2c_detect_slave_mode(&pdev->dev);

	अगर (dev->slave_detected)
		rc = at91_twi_probe_slave(pdev, phy_addr, dev);
	अन्यथा
		rc = at91_twi_probe_master(pdev, phy_addr, dev);
	अगर (rc)
		वापस rc;

	at91_init_twi_bus(dev);

	pm_runसमय_set_स्वतःsuspend_delay(dev->dev, AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(dev->dev);
	pm_runसमय_set_active(dev->dev);
	pm_runसमय_enable(dev->dev);

	rc = i2c_add_numbered_adapter(&dev->adapter);
	अगर (rc) अणु
		clk_disable_unprepare(dev->clk);

		pm_runसमय_disable(dev->dev);
		pm_runसमय_set_suspended(dev->dev);

		वापस rc;
	पूर्ण

	dev_info(dev->dev, "AT91 i2c bus driver (hw version: %#x).\n",
		 at91_twi_पढ़ो(dev, AT91_TWI_VER));
	वापस 0;
पूर्ण

अटल पूर्णांक at91_twi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_twi_dev *dev = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&dev->adapter);
	clk_disable_unprepare(dev->clk);

	pm_runसमय_disable(dev->dev);
	pm_runसमय_set_suspended(dev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक at91_twi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा at91_twi_dev *twi_dev = dev_get_drvdata(dev);

	clk_disable_unprepare(twi_dev->clk);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_twi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा at91_twi_dev *twi_dev = dev_get_drvdata(dev);

	pinctrl_pm_select_शेष_state(dev);

	वापस clk_prepare_enable(twi_dev->clk);
पूर्ण

अटल पूर्णांक at91_twi_suspend_noirq(काष्ठा device *dev)
अणु
	अगर (!pm_runसमय_status_suspended(dev))
		at91_twi_runसमय_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_twi_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा at91_twi_dev *twi_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!pm_runसमय_status_suspended(dev)) अणु
		ret = at91_twi_runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
	pm_request_स्वतःsuspend(dev);

	at91_init_twi_bus(twi_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops at91_twi_pm = अणु
	.suspend_noirq	= at91_twi_suspend_noirq,
	.resume_noirq	= at91_twi_resume_noirq,
	.runसमय_suspend	= at91_twi_runसमय_suspend,
	.runसमय_resume		= at91_twi_runसमय_resume,
पूर्ण;

#घोषणा at91_twi_pm_ops (&at91_twi_pm)
#अन्यथा
#घोषणा at91_twi_pm_ops शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver at91_twi_driver = अणु
	.probe		= at91_twi_probe,
	.हटाओ		= at91_twi_हटाओ,
	.id_table	= at91_twi_devtypes,
	.driver		= अणु
		.name	= "at91_i2c",
		.of_match_table = of_match_ptr(aपंचांगel_twi_dt_ids),
		.pm	= at91_twi_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init at91_twi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&at91_twi_driver);
पूर्ण

अटल व्योम __निकास at91_twi_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&at91_twi_driver);
पूर्ण

subsys_initcall(at91_twi_init);
module_निकास(at91_twi_निकास);

MODULE_AUTHOR("Nikolaus Voss <n.voss@weinmann.de>");
MODULE_DESCRIPTION("I2C (TWI) driver for Atmel AT91");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:at91_i2c");
