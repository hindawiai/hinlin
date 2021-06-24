<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Motorola CPCAP PMIC core driver
 *
 * Copyright (C) 2016 Tony Lindgren <tony@atomide.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/motorola-cpcap.h>
#समावेश <linux/spi/spi.h>

#घोषणा CPCAP_NR_IRQ_REG_BANKS	6
#घोषणा CPCAP_NR_IRQ_CHIPS	3
#घोषणा CPCAP_REGISTER_SIZE	4
#घोषणा CPCAP_REGISTER_BITS	16

काष्ठा cpcap_ddata अणु
	काष्ठा spi_device *spi;
	काष्ठा regmap_irq *irqs;
	काष्ठा regmap_irq_chip_data *irqdata[CPCAP_NR_IRQ_CHIPS];
	स्थिर काष्ठा regmap_config *regmap_conf;
	काष्ठा regmap *regmap;
पूर्ण;

अटल पूर्णांक cpcap_sense_irq(काष्ठा regmap *regmap, पूर्णांक irq)
अणु
	पूर्णांक regnum = irq / CPCAP_REGISTER_BITS;
	पूर्णांक mask = BIT(irq % CPCAP_REGISTER_BITS);
	पूर्णांक reg = CPCAP_REG_INTS1 + (regnum * CPCAP_REGISTER_SIZE);
	पूर्णांक err, val;

	अगर (reg < CPCAP_REG_INTS1 || reg > CPCAP_REG_INTS4)
		वापस -EINVAL;

	err = regmap_पढ़ो(regmap, reg, &val);
	अगर (err)
		वापस err;

	वापस !!(val & mask);
पूर्ण

पूर्णांक cpcap_sense_virq(काष्ठा regmap *regmap, पूर्णांक virq)
अणु
	काष्ठा regmap_irq_chip_data *d = irq_get_chip_data(virq);
	पूर्णांक irq_base = regmap_irq_chip_get_base(d);

	वापस cpcap_sense_irq(regmap, virq - irq_base);
पूर्ण
EXPORT_SYMBOL_GPL(cpcap_sense_virq);

अटल पूर्णांक cpcap_check_revision(काष्ठा cpcap_ddata *cpcap)
अणु
	u16 venकरोr, rev;
	पूर्णांक ret;

	ret = cpcap_get_venकरोr(&cpcap->spi->dev, cpcap->regmap, &venकरोr);
	अगर (ret)
		वापस ret;

	ret = cpcap_get_revision(&cpcap->spi->dev, cpcap->regmap, &rev);
	अगर (ret)
		वापस ret;

	dev_info(&cpcap->spi->dev, "CPCAP vendor: %s rev: %i.%i (%x)\n",
		 venकरोr == CPCAP_VENDOR_ST ? "ST" : "TI",
		 CPCAP_REVISION_MAJOR(rev), CPCAP_REVISION_MINOR(rev),
		 rev);

	अगर (rev < CPCAP_REVISION_2_1) अणु
		dev_info(&cpcap->spi->dev,
			 "Please add old CPCAP revision support as needed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * First two irq chips are the two निजी macro पूर्णांकerrupt chips, the third
 * irq chip is क्रम रेजिस्टर banks 1 - 4 and is available क्रम drivers to use.
 */
अटल काष्ठा regmap_irq_chip cpcap_irq_chip[CPCAP_NR_IRQ_CHIPS] = अणु
	अणु
		.name = "cpcap-m2",
		.num_regs = 1,
		.status_base = CPCAP_REG_MI1,
		.ack_base = CPCAP_REG_MI1,
		.mask_base = CPCAP_REG_MIM1,
		.use_ack = true,
		.clear_ack = true,
	पूर्ण,
	अणु
		.name = "cpcap-m2",
		.num_regs = 1,
		.status_base = CPCAP_REG_MI2,
		.ack_base = CPCAP_REG_MI2,
		.mask_base = CPCAP_REG_MIM2,
		.use_ack = true,
		.clear_ack = true,
	पूर्ण,
	अणु
		.name = "cpcap1-4",
		.num_regs = 4,
		.status_base = CPCAP_REG_INT1,
		.ack_base = CPCAP_REG_INT1,
		.mask_base = CPCAP_REG_INTM1,
		.use_ack = true,
		.clear_ack = true,
	पूर्ण,
पूर्ण;

अटल व्योम cpcap_init_one_regmap_irq(काष्ठा cpcap_ddata *cpcap,
				      काष्ठा regmap_irq *rirq,
				      पूर्णांक irq_base, पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित पूर्णांक bit, mask;

	reg_offset = irq - irq_base;
	reg_offset /= cpcap->regmap_conf->val_bits;
	reg_offset *= cpcap->regmap_conf->reg_stride;

	bit = irq % cpcap->regmap_conf->val_bits;
	mask = (1 << bit);

	rirq->reg_offset = reg_offset;
	rirq->mask = mask;
पूर्ण

अटल पूर्णांक cpcap_init_irq_chip(काष्ठा cpcap_ddata *cpcap, पूर्णांक irq_chip,
			       पूर्णांक irq_start, पूर्णांक nr_irqs)
अणु
	काष्ठा regmap_irq_chip *chip = &cpcap_irq_chip[irq_chip];
	पूर्णांक i, ret;

	क्रम (i = irq_start; i < irq_start + nr_irqs; i++) अणु
		काष्ठा regmap_irq *rirq = &cpcap->irqs[i];

		cpcap_init_one_regmap_irq(cpcap, rirq, irq_start, i);
	पूर्ण
	chip->irqs = &cpcap->irqs[irq_start];
	chip->num_irqs = nr_irqs;
	chip->irq_drv_data = cpcap;

	ret = devm_regmap_add_irq_chip(&cpcap->spi->dev, cpcap->regmap,
				       cpcap->spi->irq,
				       irq_get_trigger_type(cpcap->spi->irq) |
				       IRQF_SHARED, -1,
				       chip, &cpcap->irqdata[irq_chip]);
	अगर (ret) अणु
		dev_err(&cpcap->spi->dev, "could not add irq chip %i: %i\n",
			irq_chip, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_init_irq(काष्ठा cpcap_ddata *cpcap)
अणु
	पूर्णांक ret;

	cpcap->irqs = devm_kzalloc(&cpcap->spi->dev,
				   array3_size(माप(*cpcap->irqs),
					       CPCAP_NR_IRQ_REG_BANKS,
					       cpcap->regmap_conf->val_bits),
				   GFP_KERNEL);
	अगर (!cpcap->irqs)
		वापस -ENOMEM;

	ret = cpcap_init_irq_chip(cpcap, 0, 0, 16);
	अगर (ret)
		वापस ret;

	ret = cpcap_init_irq_chip(cpcap, 1, 16, 16);
	अगर (ret)
		वापस ret;

	ret = cpcap_init_irq_chip(cpcap, 2, 32, 64);
	अगर (ret)
		वापस ret;

	enable_irq_wake(cpcap->spi->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cpcap_of_match[] = अणु
	अणु .compatible = "motorola,cpcap", पूर्ण,
	अणु .compatible = "st,6556002", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_of_match);

अटल स्थिर काष्ठा regmap_config cpcap_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 4,
	.pad_bits = 0,
	.val_bits = 16,
	.ग_लिखो_flag_mask = 0x8000,
	.max_रेजिस्टर = CPCAP_REG_ST_TEST2,
	.cache_type = REGCACHE_NONE,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cpcap_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	disable_irq(spi->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	enable_irq(spi->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cpcap_pm, cpcap_suspend, cpcap_resume);

अटल स्थिर काष्ठा mfd_cell cpcap_mfd_devices[] = अणु
	अणु
		.name          = "cpcap_adc",
		.of_compatible = "motorola,mapphone-cpcap-adc",
	पूर्ण, अणु
		.name          = "cpcap_battery",
		.of_compatible = "motorola,cpcap-battery",
	पूर्ण, अणु
		.name          = "cpcap-charger",
		.of_compatible = "motorola,mapphone-cpcap-charger",
	पूर्ण, अणु
		.name          = "cpcap-regulator",
		.of_compatible = "motorola,mapphone-cpcap-regulator",
	पूर्ण, अणु
		.name          = "cpcap-rtc",
		.of_compatible = "motorola,cpcap-rtc",
	पूर्ण, अणु
		.name          = "cpcap-pwrbutton",
		.of_compatible = "motorola,cpcap-pwrbutton",
	पूर्ण, अणु
		.name          = "cpcap-usb-phy",
		.of_compatible = "motorola,mapphone-cpcap-usb-phy",
	पूर्ण, अणु
		.name          = "cpcap-led",
		.id            = 0,
		.of_compatible = "motorola,cpcap-led-red",
	पूर्ण, अणु
		.name          = "cpcap-led",
		.id            = 1,
		.of_compatible = "motorola,cpcap-led-green",
	पूर्ण, अणु
		.name          = "cpcap-led",
		.id            = 2,
		.of_compatible = "motorola,cpcap-led-blue",
	पूर्ण, अणु
		.name          = "cpcap-led",
		.id            = 3,
		.of_compatible = "motorola,cpcap-led-adl",
	पूर्ण, अणु
		.name          = "cpcap-led",
		.id            = 4,
		.of_compatible = "motorola,cpcap-led-cp",
	पूर्ण, अणु
		.name          = "cpcap-codec",
	पूर्ण
पूर्ण;

अटल पूर्णांक cpcap_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा cpcap_ddata *cpcap;
	पूर्णांक ret;

	match = of_match_device(of_match_ptr(cpcap_of_match), &spi->dev);
	अगर (!match)
		वापस -ENODEV;

	cpcap = devm_kzalloc(&spi->dev, माप(*cpcap), GFP_KERNEL);
	अगर (!cpcap)
		वापस -ENOMEM;

	cpcap->spi = spi;
	spi_set_drvdata(spi, cpcap);

	spi->bits_per_word = 16;
	spi->mode = SPI_MODE_0 | SPI_CS_HIGH;

	ret = spi_setup(spi);
	अगर (ret)
		वापस ret;

	cpcap->regmap_conf = &cpcap_regmap_config;
	cpcap->regmap = devm_regmap_init_spi(spi, &cpcap_regmap_config);
	अगर (IS_ERR(cpcap->regmap)) अणु
		ret = PTR_ERR(cpcap->regmap);
		dev_err(&cpcap->spi->dev, "Failed to initialize regmap: %d\n",
			ret);

		वापस ret;
	पूर्ण

	ret = cpcap_check_revision(cpcap);
	अगर (ret) अणु
		dev_err(&cpcap->spi->dev, "Failed to detect CPCAP: %i\n", ret);
		वापस ret;
	पूर्ण

	ret = cpcap_init_irq(cpcap);
	अगर (ret)
		वापस ret;

	वापस devm_mfd_add_devices(&spi->dev, 0, cpcap_mfd_devices,
				    ARRAY_SIZE(cpcap_mfd_devices), शून्य, 0, शून्य);
पूर्ण

अटल काष्ठा spi_driver cpcap_driver = अणु
	.driver = अणु
		.name = "cpcap-core",
		.of_match_table = cpcap_of_match,
		.pm = &cpcap_pm,
	पूर्ण,
	.probe = cpcap_probe,
पूर्ण;
module_spi_driver(cpcap_driver);

MODULE_ALIAS("platform:cpcap");
MODULE_DESCRIPTION("CPCAP driver");
MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_LICENSE("GPL v2");
