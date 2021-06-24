<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Altera SPI driver
 *
 * Copyright (C) 2008 Thomas Chou <thomas@wytron.com.tw>
 *
 * Based on spi_s3c24xx.c, which is:
 * Copyright (c) 2006 Ben Dooks
 * Copyright (c) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/altera.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#घोषणा DRV_NAME "spi_altera"

क्रमागत altera_spi_type अणु
	ALTERA_SPI_TYPE_UNKNOWN,
	ALTERA_SPI_TYPE_SUBDEV,
पूर्ण;

अटल स्थिर काष्ठा regmap_config spi_altera_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,
पूर्ण;

अटल पूर्णांक altera_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *platid = platक्रमm_get_device_id(pdev);
	काष्ठा altera_spi_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	क्रमागत altera_spi_type type = ALTERA_SPI_TYPE_UNKNOWN;
	काष्ठा altera_spi *hw;
	काष्ठा spi_master *master;
	पूर्णांक err = -ENODEV;
	u16 i;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा altera_spi));
	अगर (!master)
		वापस err;

	/* setup the master state. */
	master->bus_num = pdev->id;

	अगर (pdata) अणु
		अगर (pdata->num_chipselect > ALTERA_SPI_MAX_CS) अणु
			dev_err(&pdev->dev,
				"Invalid number of chipselect: %u\n",
				pdata->num_chipselect);
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		master->num_chipselect = pdata->num_chipselect;
		master->mode_bits = pdata->mode_bits;
		master->bits_per_word_mask = pdata->bits_per_word_mask;
	पूर्ण अन्यथा अणु
		master->num_chipselect = 16;
		master->mode_bits = SPI_CS_HIGH;
		master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 16);
	पूर्ण

	master->dev.of_node = pdev->dev.of_node;

	hw = spi_master_get_devdata(master);
	hw->dev = &pdev->dev;

	अगर (platid)
		type = platid->driver_data;

	/* find and map our resources */
	अगर (type == ALTERA_SPI_TYPE_SUBDEV) अणु
		काष्ठा resource *regoff;

		hw->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
		अगर (!hw->regmap) अणु
			dev_err(&pdev->dev, "get regmap failed\n");
			जाओ निकास;
		पूर्ण

		regoff = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
		अगर (regoff)
			hw->regoff = regoff->start;
	पूर्ण अन्यथा अणु
		व्योम __iomem *res;

		res = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(res)) अणु
			err = PTR_ERR(res);
			जाओ निकास;
		पूर्ण

		hw->regmap = devm_regmap_init_mmio(&pdev->dev, res,
						   &spi_altera_config);
		अगर (IS_ERR(hw->regmap)) अणु
			dev_err(&pdev->dev, "regmap mmio init failed\n");
			err = PTR_ERR(hw->regmap);
			जाओ निकास;
		पूर्ण
	पूर्ण

	altera_spi_init_master(master);

	/* irq is optional */
	hw->irq = platक्रमm_get_irq(pdev, 0);
	अगर (hw->irq >= 0) अणु
		err = devm_request_irq(&pdev->dev, hw->irq, altera_spi_irq, 0,
				       pdev->name, master);
		अगर (err)
			जाओ निकास;
	पूर्ण

	err = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (err)
		जाओ निकास;

	अगर (pdata) अणु
		क्रम (i = 0; i < pdata->num_devices; i++) अणु
			अगर (!spi_new_device(master, pdata->devices + i))
				dev_warn(&pdev->dev,
					 "unable to create SPI device: %s\n",
					 pdata->devices[i].modalias);
		पूर्ण
	पूर्ण

	dev_info(&pdev->dev, "regoff %u, irq %d\n", hw->regoff, hw->irq);

	वापस 0;
निकास:
	spi_master_put(master);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id altera_spi_match[] = अणु
	अणु .compatible = "ALTR,spi-1.0", पूर्ण,
	अणु .compatible = "altr,spi-1.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altera_spi_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल स्थिर काष्ठा platक्रमm_device_id altera_spi_ids[] = अणु
	अणु DRV_NAME,		ALTERA_SPI_TYPE_UNKNOWN पूर्ण,
	अणु "subdev_spi_altera",	ALTERA_SPI_TYPE_SUBDEV पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, altera_spi_ids);

अटल काष्ठा platक्रमm_driver altera_spi_driver = अणु
	.probe = altera_spi_probe,
	.driver = अणु
		.name = DRV_NAME,
		.pm = शून्य,
		.of_match_table = of_match_ptr(altera_spi_match),
	पूर्ण,
	.id_table	= altera_spi_ids,
पूर्ण;
module_platक्रमm_driver(altera_spi_driver);

MODULE_DESCRIPTION("Altera SPI driver");
MODULE_AUTHOR("Thomas Chou <thomas@wytron.com.tw>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
