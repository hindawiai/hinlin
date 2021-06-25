<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम HTC PASIC3 LED/DS1WM chip.
 *
 * Copyright (C) 2006 Philipp Zabel <philipp.zabel@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/ds1wm.h>
#समावेश <linux/mfd/htc-pasic3.h>
#समावेश <linux/slab.h>

काष्ठा pasic3_data अणु
	व्योम __iomem *mapping;
	अचिन्हित पूर्णांक bus_shअगरt;
पूर्ण;

#घोषणा REG_ADDR  5
#घोषणा REG_DATA  6

#घोषणा READ_MODE 0x80

/*
 * ग_लिखो to a secondary रेजिस्टर on the PASIC3
 */
व्योम pasic3_ग_लिखो_रेजिस्टर(काष्ठा device *dev, u32 reg, u8 val)
अणु
	काष्ठा pasic3_data *asic = dev_get_drvdata(dev);
	पूर्णांक bus_shअगरt = asic->bus_shअगरt;
	व्योम __iomem *addr = asic->mapping + (REG_ADDR << bus_shअगरt);
	व्योम __iomem *data = asic->mapping + (REG_DATA << bus_shअगरt);

	__raw_ग_लिखोb(~READ_MODE & reg, addr);
	__raw_ग_लिखोb(val, data);
पूर्ण
EXPORT_SYMBOL(pasic3_ग_लिखो_रेजिस्टर); /* क्रम leds-pasic3 */

/*
 * पढ़ो from a secondary रेजिस्टर on the PASIC3
 */
u8 pasic3_पढ़ो_रेजिस्टर(काष्ठा device *dev, u32 reg)
अणु
	काष्ठा pasic3_data *asic = dev_get_drvdata(dev);
	पूर्णांक bus_shअगरt = asic->bus_shअगरt;
	व्योम __iomem *addr = asic->mapping + (REG_ADDR << bus_shअगरt);
	व्योम __iomem *data = asic->mapping + (REG_DATA << bus_shअगरt);

	__raw_ग_लिखोb(READ_MODE | reg, addr);
	वापस __raw_पढ़ोb(data);
पूर्ण
EXPORT_SYMBOL(pasic3_पढ़ो_रेजिस्टर); /* क्रम leds-pasic3 */

/*
 * LEDs
 */

अटल काष्ठा mfd_cell led_cell __initdata = अणु
	.name = "leds-pasic3",
पूर्ण;

/*
 * DS1WM
 */

अटल पूर्णांक ds1wm_enable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = pdev->dev.parent;
	पूर्णांक c;

	c = pasic3_पढ़ो_रेजिस्टर(dev, 0x28);
	pasic3_ग_लिखो_रेजिस्टर(dev, 0x28, c & 0x7f);

	dev_dbg(dev, "DS1WM OWM_EN low (active) %02x\n", c & 0x7f);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1wm_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = pdev->dev.parent;
	पूर्णांक c;

	c = pasic3_पढ़ो_रेजिस्टर(dev, 0x28);
	pasic3_ग_लिखो_रेजिस्टर(dev, 0x28, c | 0x80);

	dev_dbg(dev, "DS1WM OWM_EN high (inactive) %02x\n", c | 0x80);
	वापस 0;
पूर्ण

अटल काष्ठा ds1wm_driver_data ds1wm_pdata = अणु
	.active_high = 0,
	.reset_recover_delay = 1,
पूर्ण;

अटल काष्ठा resource ds1wm_resources[] __initdata = अणु
	[0] = अणु
		.start  = 0,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = 0,
		.end    = 0,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ds1wm_cell __initस्थिर = अणु
	.name          = "ds1wm",
	.enable        = ds1wm_enable,
	.disable       = ds1wm_disable,
	.platक्रमm_data = &ds1wm_pdata,
	.pdata_size    = माप(ds1wm_pdata),
	.num_resources = 2,
	.resources     = ds1wm_resources,
पूर्ण;

अटल पूर्णांक __init pasic3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pasic3_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pasic3_data *asic;
	काष्ठा resource *r;
	पूर्णांक ret;
	पूर्णांक irq = 0;

	r = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (r) अणु
		ds1wm_resources[1].flags = IORESOURCE_IRQ | (r->flags &
			(IORESOURCE_IRQ_HIGHEDGE | IORESOURCE_IRQ_LOWEDGE));
		irq = r->start;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r)
		वापस -ENXIO;

	अगर (!request_mem_region(r->start, resource_size(r), "pasic3"))
		वापस -EBUSY;

	asic = devm_kzalloc(dev, माप(काष्ठा pasic3_data), GFP_KERNEL);
	अगर (!asic)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, asic);

	asic->mapping = ioremap(r->start, resource_size(r));
	अगर (!asic->mapping) अणु
		dev_err(dev, "couldn't ioremap PASIC3\n");
		वापस -ENOMEM;
	पूर्ण

	/* calculate bus shअगरt from mem resource */
	asic->bus_shअगरt = (resource_size(r) - 5) >> 3;

	अगर (pdata && pdata->घड़ी_rate) अणु
		ds1wm_pdata.घड़ी_rate = pdata->घड़ी_rate;
		/* the first 5 PASIC3 रेजिस्टरs control the DS1WM */
		ds1wm_resources[0].end = (5 << asic->bus_shअगरt) - 1;
		ret = mfd_add_devices(&pdev->dev, pdev->id,
				      &ds1wm_cell, 1, r, irq, शून्य);
		अगर (ret < 0)
			dev_warn(dev, "failed to register DS1WM\n");
	पूर्ण

	अगर (pdata && pdata->led_pdata) अणु
		led_cell.platक्रमm_data = pdata->led_pdata;
		led_cell.pdata_size = माप(काष्ठा pasic3_leds_machinfo);
		ret = mfd_add_devices(&pdev->dev, pdev->id, &led_cell, 1, r,
				      0, शून्य);
		अगर (ret < 0)
			dev_warn(dev, "failed to register LED device\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pasic3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pasic3_data *asic = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *r;

	mfd_हटाओ_devices(&pdev->dev);

	iounmap(asic->mapping);
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(r->start, resource_size(r));
	वापस 0;
पूर्ण

MODULE_ALIAS("platform:pasic3");

अटल काष्ठा platक्रमm_driver pasic3_driver = अणु
	.driver		= अणु
		.name	= "pasic3",
	पूर्ण,
	.हटाओ		= pasic3_हटाओ,
पूर्ण;

module_platक्रमm_driver_probe(pasic3_driver, pasic3_probe);

MODULE_AUTHOR("Philipp Zabel <philipp.zabel@gmail.com>");
MODULE_DESCRIPTION("Core driver for HTC PASIC3");
MODULE_LICENSE("GPL");
