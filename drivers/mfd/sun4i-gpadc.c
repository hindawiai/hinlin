<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ADC MFD core driver क्रम sunxi platक्रमms
 *
 * Copyright (c) 2016 Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/sun4i-gpadc.h>

#घोषणा ARCH_SUN4I_A10 0
#घोषणा ARCH_SUN5I_A13 1
#घोषणा ARCH_SUN6I_A31 2

अटल स्थिर काष्ठा resource adc_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(SUN4I_GPADC_IRQ_FIFO_DATA, "FIFO_DATA_PENDING"),
	DEFINE_RES_IRQ_NAMED(SUN4I_GPADC_IRQ_TEMP_DATA, "TEMP_DATA_PENDING"),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq sun4i_gpadc_regmap_irq[] = अणु
	REGMAP_IRQ_REG(SUN4I_GPADC_IRQ_FIFO_DATA, 0,
		       SUN4I_GPADC_INT_FIFOC_TP_DATA_IRQ_EN),
	REGMAP_IRQ_REG(SUN4I_GPADC_IRQ_TEMP_DATA, 0,
		       SUN4I_GPADC_INT_FIFOC_TEMP_IRQ_EN),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip sun4i_gpadc_regmap_irq_chip = अणु
	.name = "sun4i_gpadc_irq_chip",
	.status_base = SUN4I_GPADC_INT_FIFOS,
	.ack_base = SUN4I_GPADC_INT_FIFOS,
	.mask_base = SUN4I_GPADC_INT_FIFOC,
	.init_ack_masked = true,
	.mask_invert = true,
	.irqs = sun4i_gpadc_regmap_irq,
	.num_irqs = ARRAY_SIZE(sun4i_gpadc_regmap_irq),
	.num_regs = 1,
पूर्ण;

अटल काष्ठा mfd_cell sun4i_gpadc_cells[] = अणु
	अणु
		.name	= "sun4i-a10-gpadc-iio",
		.resources = adc_resources,
		.num_resources = ARRAY_SIZE(adc_resources),
	पूर्ण,
	अणु .name = "iio_hwmon" पूर्ण
पूर्ण;

अटल काष्ठा mfd_cell sun5i_gpadc_cells[] = अणु
	अणु
		.name	= "sun5i-a13-gpadc-iio",
		.resources = adc_resources,
		.num_resources = ARRAY_SIZE(adc_resources),
	पूर्ण,
	अणु .name = "iio_hwmon" पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell sun6i_gpadc_cells[] = अणु
	अणु
		.name	= "sun6i-a31-gpadc-iio",
		.resources = adc_resources,
		.num_resources = ARRAY_SIZE(adc_resources),
	पूर्ण,
	अणु .name = "iio_hwmon" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun4i_gpadc_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun4i_gpadc_of_match[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-ts",
		.data = (व्योम *)ARCH_SUN4I_A10,
	पूर्ण, अणु
		.compatible = "allwinner,sun5i-a13-ts",
		.data = (व्योम *)ARCH_SUN5I_A13,
	पूर्ण, अणु
		.compatible = "allwinner,sun6i-a31-ts",
		.data = (व्योम *)ARCH_SUN6I_A31,
	पूर्ण, अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, sun4i_gpadc_of_match);

अटल पूर्णांक sun4i_gpadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_gpadc_dev *dev;
	काष्ठा resource *mem;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा mfd_cell *cells;
	अचिन्हित पूर्णांक irq, size;
	पूर्णांक ret;

	of_id = of_match_node(sun4i_gpadc_of_match, pdev->dev.of_node);
	अगर (!of_id)
		वापस -EINVAL;

	चयन ((दीर्घ)of_id->data) अणु
	हाल ARCH_SUN4I_A10:
		cells = sun4i_gpadc_cells;
		size = ARRAY_SIZE(sun4i_gpadc_cells);
		अवरोध;
	हाल ARCH_SUN5I_A13:
		cells = sun5i_gpadc_cells;
		size = ARRAY_SIZE(sun5i_gpadc_cells);
		अवरोध;
	हाल ARCH_SUN6I_A31:
		cells = sun6i_gpadc_cells;
		size = ARRAY_SIZE(sun6i_gpadc_cells);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(dev->base))
		वापस PTR_ERR(dev->base);

	dev->dev = &pdev->dev;
	dev_set_drvdata(dev->dev, dev);

	dev->regmap = devm_regmap_init_mmio(dev->dev, dev->base,
					    &sun4i_gpadc_regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		dev_err(&pdev->dev, "failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Disable all पूर्णांकerrupts */
	regmap_ग_लिखो(dev->regmap, SUN4I_GPADC_INT_FIFOC, 0);

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_regmap_add_irq_chip(&pdev->dev, dev->regmap, irq,
				       IRQF_ONESHOT, 0,
				       &sun4i_gpadc_regmap_irq_chip,
				       &dev->regmap_irqc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add irq chip: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(dev->dev, 0, cells, size, शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add MFD devices: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sun4i_gpadc_driver = अणु
	.driver = अणु
		.name = "sun4i-gpadc",
		.of_match_table = sun4i_gpadc_of_match,
	पूर्ण,
	.probe = sun4i_gpadc_probe,
पूर्ण;

module_platक्रमm_driver(sun4i_gpadc_driver);

MODULE_DESCRIPTION("Allwinner sunxi platforms' GPADC MFD core driver");
MODULE_AUTHOR("Quentin Schulz <quentin.schulz@free-electrons.com>");
MODULE_LICENSE("GPL v2");
