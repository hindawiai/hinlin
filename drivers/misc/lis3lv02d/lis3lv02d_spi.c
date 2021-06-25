<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lis3lv02d_spi - SPI glue layer क्रम lis3lv02d
 *
 * Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>

#समावेश "lis3lv02d.h"

#घोषणा DRV_NAME 	"lis3lv02d_spi"
#घोषणा LIS3_SPI_READ	0x80

अटल पूर्णांक lis3_spi_पढ़ो(काष्ठा lis3lv02d *lis3, पूर्णांक reg, u8 *v)
अणु
	काष्ठा spi_device *spi = lis3->bus_priv;
	पूर्णांक ret = spi_w8r8(spi, reg | LIS3_SPI_READ);
	अगर (ret < 0)
		वापस -EINVAL;

	*v = (u8) ret;
	वापस 0;
पूर्ण

अटल पूर्णांक lis3_spi_ग_लिखो(काष्ठा lis3lv02d *lis3, पूर्णांक reg, u8 val)
अणु
	u8 पंचांगp[2] = अणु reg, val पूर्ण;
	काष्ठा spi_device *spi = lis3->bus_priv;
	वापस spi_ग_लिखो(spi, पंचांगp, माप(पंचांगp));
पूर्ण

अटल पूर्णांक lis3_spi_init(काष्ठा lis3lv02d *lis3)
अणु
	u8 reg;
	पूर्णांक ret;

	/* घातer up the device */
	ret = lis3->पढ़ो(lis3, CTRL_REG1, &reg);
	अगर (ret < 0)
		वापस ret;

	reg |= CTRL1_PD0 | CTRL1_Xen | CTRL1_Yen | CTRL1_Zen;
	वापस lis3->ग_लिखो(lis3, CTRL_REG1, reg);
पूर्ण

अटल जोड़ axis_conversion lis3lv02d_axis_normal =
	अणु .as_array = अणु 1, 2, 3 पूर्ण पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lis302dl_spi_dt_ids[] = अणु
	अणु .compatible = "st,lis302dl-spi" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lis302dl_spi_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक lis302dl_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	lis3_dev.bus_priv	= spi;
	lis3_dev.init		= lis3_spi_init;
	lis3_dev.पढ़ो		= lis3_spi_पढ़ो;
	lis3_dev.ग_लिखो		= lis3_spi_ग_लिखो;
	lis3_dev.irq		= spi->irq;
	lis3_dev.ac		= lis3lv02d_axis_normal;
	lis3_dev.pdata		= spi->dev.platक्रमm_data;

#अगर_घोषित CONFIG_OF
	अगर (of_match_device(lis302dl_spi_dt_ids, &spi->dev)) अणु
		lis3_dev.of_node = spi->dev.of_node;
		ret = lis3lv02d_init_dt(&lis3_dev);
		अगर (ret)
			वापस ret;
	पूर्ण
#पूर्ण_अगर
	spi_set_drvdata(spi, &lis3_dev);

	वापस lis3lv02d_init_device(&lis3_dev);
पूर्ण

अटल पूर्णांक lis302dl_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा lis3lv02d *lis3 = spi_get_drvdata(spi);
	lis3lv02d_joystick_disable(lis3);
	lis3lv02d_घातeroff(lis3);

	वापस lis3lv02d_हटाओ_fs(&lis3_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक lis3lv02d_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा lis3lv02d *lis3 = spi_get_drvdata(spi);

	अगर (!lis3->pdata || !lis3->pdata->wakeup_flags)
		lis3lv02d_घातeroff(&lis3_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक lis3lv02d_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा lis3lv02d *lis3 = spi_get_drvdata(spi);

	अगर (!lis3->pdata || !lis3->pdata->wakeup_flags)
		lis3lv02d_घातeron(lis3);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(lis3lv02d_spi_pm, lis3lv02d_spi_suspend,
			 lis3lv02d_spi_resume);

अटल काष्ठा spi_driver lis302dl_spi_driver = अणु
	.driver	 = अणु
		.name   = DRV_NAME,
		.pm	= &lis3lv02d_spi_pm,
		.of_match_table = of_match_ptr(lis302dl_spi_dt_ids),
	पूर्ण,
	.probe	= lis302dl_spi_probe,
	.हटाओ	= lis302dl_spi_हटाओ,
पूर्ण;

module_spi_driver(lis302dl_spi_driver);

MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>");
MODULE_DESCRIPTION("lis3lv02d SPI glue layer");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:" DRV_NAME);
