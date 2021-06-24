<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Spपढ़ोtrum Communications Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/sc27xx-pmic.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <uapi/linux/usb/अक्षरger.h>

#घोषणा SPRD_PMIC_INT_MASK_STATUS	0x0
#घोषणा SPRD_PMIC_INT_RAW_STATUS	0x4
#घोषणा SPRD_PMIC_INT_EN		0x8

#घोषणा SPRD_SC2731_IRQ_BASE		0x140
#घोषणा SPRD_SC2731_IRQ_NUMS		16
#घोषणा SPRD_SC2731_CHG_DET		0xedc

/* PMIC अक्षरger detection definition */
#घोषणा SPRD_PMIC_CHG_DET_DELAY_US	200000
#घोषणा SPRD_PMIC_CHG_DET_TIMEOUT	2000000
#घोषणा SPRD_PMIC_CHG_DET_DONE		BIT(11)
#घोषणा SPRD_PMIC_SDP_TYPE		BIT(7)
#घोषणा SPRD_PMIC_DCP_TYPE		BIT(6)
#घोषणा SPRD_PMIC_CDP_TYPE		BIT(5)
#घोषणा SPRD_PMIC_CHG_TYPE_MASK		GENMASK(7, 5)

काष्ठा sprd_pmic अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा regmap_irq *irqs;
	काष्ठा regmap_irq_chip irq_chip;
	काष्ठा regmap_irq_chip_data *irq_data;
	स्थिर काष्ठा sprd_pmic_data *pdata;
	पूर्णांक irq;
पूर्ण;

काष्ठा sprd_pmic_data अणु
	u32 irq_base;
	u32 num_irqs;
	u32 अक्षरger_det;
पूर्ण;

/*
 * Since dअगरferent PMICs of SC27xx series can have dअगरferent पूर्णांकerrupt
 * base address and irq number, we should save irq number and irq base
 * in the device data काष्ठाure.
 */
अटल स्थिर काष्ठा sprd_pmic_data sc2731_data = अणु
	.irq_base = SPRD_SC2731_IRQ_BASE,
	.num_irqs = SPRD_SC2731_IRQ_NUMS,
	.अक्षरger_det = SPRD_SC2731_CHG_DET,
पूर्ण;

क्रमागत usb_अक्षरger_type sprd_pmic_detect_अक्षरger_type(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा sprd_pmic *ddata = spi_get_drvdata(spi);
	स्थिर काष्ठा sprd_pmic_data *pdata = ddata->pdata;
	क्रमागत usb_अक्षरger_type type;
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(ddata->regmap, pdata->अक्षरger_det, val,
				       (val & SPRD_PMIC_CHG_DET_DONE),
				       SPRD_PMIC_CHG_DET_DELAY_US,
				       SPRD_PMIC_CHG_DET_TIMEOUT);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to detect charger type\n");
		वापस UNKNOWN_TYPE;
	पूर्ण

	चयन (val & SPRD_PMIC_CHG_TYPE_MASK) अणु
	हाल SPRD_PMIC_CDP_TYPE:
		type = CDP_TYPE;
		अवरोध;
	हाल SPRD_PMIC_DCP_TYPE:
		type = DCP_TYPE;
		अवरोध;
	हाल SPRD_PMIC_SDP_TYPE:
		type = SDP_TYPE;
		अवरोध;
	शेष:
		type = UNKNOWN_TYPE;
		अवरोध;
	पूर्ण

	वापस type;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_pmic_detect_अक्षरger_type);

अटल पूर्णांक sprd_pmic_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);

	वापस spi_ग_लिखो(spi, data, count);
पूर्ण

अटल पूर्णांक sprd_pmic_spi_पढ़ो(व्योम *context,
			      स्थिर व्योम *reg, माप_प्रकार reg_size,
			      व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);
	u32 rx_buf[2] = अणु 0 पूर्ण;
	पूर्णांक ret;

	/* Now we only support one PMIC रेजिस्टर to पढ़ो every समय. */
	अगर (reg_size != माप(u32) || val_size != माप(u32))
		वापस -EINVAL;

	/* Copy address to पढ़ो from पूर्णांकo first element of SPI buffer. */
	स_नकल(rx_buf, reg, माप(u32));
	ret = spi_पढ़ो(spi, rx_buf, 1);
	अगर (ret < 0)
		वापस ret;

	स_नकल(val, rx_buf, val_size);
	वापस 0;
पूर्ण

अटल काष्ठा regmap_bus sprd_pmic_regmap = अणु
	.ग_लिखो = sprd_pmic_spi_ग_लिखो,
	.पढ़ो = sprd_pmic_spi_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sprd_pmic_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 0xffff,
पूर्ण;

अटल पूर्णांक sprd_pmic_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा sprd_pmic *ddata;
	स्थिर काष्ठा sprd_pmic_data *pdata;
	पूर्णांक ret, i;

	pdata = of_device_get_match_data(&spi->dev);
	अगर (!pdata) अणु
		dev_err(&spi->dev, "No matching driver data found\n");
		वापस -EINVAL;
	पूर्ण

	ddata = devm_kzalloc(&spi->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->regmap = devm_regmap_init(&spi->dev, &sprd_pmic_regmap,
					 &spi->dev, &sprd_pmic_config);
	अगर (IS_ERR(ddata->regmap)) अणु
		ret = PTR_ERR(ddata->regmap);
		dev_err(&spi->dev, "Failed to allocate register map %d\n", ret);
		वापस ret;
	पूर्ण

	spi_set_drvdata(spi, ddata);
	ddata->dev = &spi->dev;
	ddata->irq = spi->irq;
	ddata->pdata = pdata;

	ddata->irq_chip.name = dev_name(&spi->dev);
	ddata->irq_chip.status_base =
		pdata->irq_base + SPRD_PMIC_INT_MASK_STATUS;
	ddata->irq_chip.mask_base = pdata->irq_base + SPRD_PMIC_INT_EN;
	ddata->irq_chip.ack_base = 0;
	ddata->irq_chip.num_regs = 1;
	ddata->irq_chip.num_irqs = pdata->num_irqs;
	ddata->irq_chip.mask_invert = true;

	ddata->irqs = devm_kसुस्मृति(&spi->dev,
				   pdata->num_irqs, माप(काष्ठा regmap_irq),
				   GFP_KERNEL);
	अगर (!ddata->irqs)
		वापस -ENOMEM;

	ddata->irq_chip.irqs = ddata->irqs;
	क्रम (i = 0; i < pdata->num_irqs; i++)
		ddata->irqs[i].mask = BIT(i);

	ret = devm_regmap_add_irq_chip(&spi->dev, ddata->regmap, ddata->irq,
				       IRQF_ONESHOT, 0,
				       &ddata->irq_chip, &ddata->irq_data);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to add PMIC irq chip %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_of_platक्रमm_populate(&spi->dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to populate sub-devices %d\n", ret);
		वापस ret;
	पूर्ण

	device_init_wakeup(&spi->dev, true);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sprd_pmic_suspend(काष्ठा device *dev)
अणु
	काष्ठा sprd_pmic *ddata = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(ddata->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pmic_resume(काष्ठा device *dev)
अणु
	काष्ठा sprd_pmic *ddata = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(ddata->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sprd_pmic_pm_ops, sprd_pmic_suspend, sprd_pmic_resume);

अटल स्थिर काष्ठा of_device_id sprd_pmic_match[] = अणु
	अणु .compatible = "sprd,sc2731", .data = &sc2731_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_pmic_match);

अटल काष्ठा spi_driver sprd_pmic_driver = अणु
	.driver = अणु
		.name = "sc27xx-pmic",
		.of_match_table = sprd_pmic_match,
		.pm = &sprd_pmic_pm_ops,
	पूर्ण,
	.probe = sprd_pmic_probe,
पूर्ण;

अटल पूर्णांक __init sprd_pmic_init(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&sprd_pmic_driver);
पूर्ण
subsys_initcall(sprd_pmic_init);

अटल व्योम __निकास sprd_pmic_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&sprd_pmic_driver);
पूर्ण
module_निकास(sprd_pmic_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Spreadtrum SC27xx PMICs driver");
MODULE_AUTHOR("Baolin Wang <baolin.wang@spreadtrum.com>");
