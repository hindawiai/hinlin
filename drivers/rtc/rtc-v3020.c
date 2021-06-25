<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/rtc/rtc-v3020.c
 *
 * Copyright (C) 2006 8D Technologies inc.
 * Copyright (C) 2004 Compulab Ltd.
 *
 * Driver क्रम the V3020 RTC
 *
 * Changelog:
 *
 *  10-May-2006: Raphael Assenat <raph@8d.com>
 *				- Converted to platक्रमm driver
 *				- Use the generic rtc class
 *
 *  ??-???-2004: Someone at Compulab
 *			- Initial driver creation.
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/types.h>
#समावेश <linux/bcd.h>
#समावेश <linux/platक्रमm_data/rtc-v3020.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>

#समावेश <linux/पन.स>

#अघोषित DEBUG

काष्ठा v3020;

काष्ठा v3020_chip_ops अणु
	पूर्णांक (*map_io)(काष्ठा v3020 *chip, काष्ठा platक्रमm_device *pdev,
		      काष्ठा v3020_platक्रमm_data *pdata);
	व्योम (*unmap_io)(काष्ठा v3020 *chip);
	अचिन्हित अक्षर (*पढ़ो_bit)(काष्ठा v3020 *chip);
	व्योम (*ग_लिखो_bit)(काष्ठा v3020 *chip, अचिन्हित अक्षर bit);
पूर्ण;

#घोषणा V3020_CS	0
#घोषणा V3020_WR	1
#घोषणा V3020_RD	2
#घोषणा V3020_IO	3

काष्ठा v3020 अणु
	/* MMIO access */
	व्योम __iomem *ioaddress;
	पूर्णांक leftshअगरt;

	/* GPIO access */
	काष्ठा gpio *gpio;

	स्थिर काष्ठा v3020_chip_ops *ops;

	काष्ठा rtc_device *rtc;
पूर्ण;


अटल पूर्णांक v3020_mmio_map(काष्ठा v3020 *chip, काष्ठा platक्रमm_device *pdev,
			  काष्ठा v3020_platक्रमm_data *pdata)
अणु
	अगर (pdev->num_resources != 1)
		वापस -EBUSY;

	अगर (pdev->resource[0].flags != IORESOURCE_MEM)
		वापस -EBUSY;

	chip->leftshअगरt = pdata->leftshअगरt;
	chip->ioaddress = ioremap(pdev->resource[0].start, 1);
	अगर (chip->ioaddress == शून्य)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम v3020_mmio_unmap(काष्ठा v3020 *chip)
अणु
	iounmap(chip->ioaddress);
पूर्ण

अटल व्योम v3020_mmio_ग_लिखो_bit(काष्ठा v3020 *chip, अचिन्हित अक्षर bit)
अणु
	ग_लिखोl(bit << chip->leftshअगरt, chip->ioaddress);
पूर्ण

अटल अचिन्हित अक्षर v3020_mmio_पढ़ो_bit(काष्ठा v3020 *chip)
अणु
	वापस !!(पढ़ोl(chip->ioaddress) & (1 << chip->leftshअगरt));
पूर्ण

अटल स्थिर काष्ठा v3020_chip_ops v3020_mmio_ops = अणु
	.map_io		= v3020_mmio_map,
	.unmap_io	= v3020_mmio_unmap,
	.पढ़ो_bit	= v3020_mmio_पढ़ो_bit,
	.ग_लिखो_bit	= v3020_mmio_ग_लिखो_bit,
पूर्ण;

अटल काष्ठा gpio v3020_gpio[] = अणु
	अणु 0, GPIOF_OUT_INIT_HIGH, "RTC CS"पूर्ण,
	अणु 0, GPIOF_OUT_INIT_HIGH, "RTC WR"पूर्ण,
	अणु 0, GPIOF_OUT_INIT_HIGH, "RTC RD"पूर्ण,
	अणु 0, GPIOF_OUT_INIT_HIGH, "RTC IO"पूर्ण,
पूर्ण;

अटल पूर्णांक v3020_gpio_map(काष्ठा v3020 *chip, काष्ठा platक्रमm_device *pdev,
			  काष्ठा v3020_platक्रमm_data *pdata)
अणु
	पूर्णांक err;

	v3020_gpio[V3020_CS].gpio = pdata->gpio_cs;
	v3020_gpio[V3020_WR].gpio = pdata->gpio_wr;
	v3020_gpio[V3020_RD].gpio = pdata->gpio_rd;
	v3020_gpio[V3020_IO].gpio = pdata->gpio_io;

	err = gpio_request_array(v3020_gpio, ARRAY_SIZE(v3020_gpio));

	अगर (!err)
		chip->gpio = v3020_gpio;

	वापस err;
पूर्ण

अटल व्योम v3020_gpio_unmap(काष्ठा v3020 *chip)
अणु
	gpio_मुक्त_array(v3020_gpio, ARRAY_SIZE(v3020_gpio));
पूर्ण

अटल व्योम v3020_gpio_ग_लिखो_bit(काष्ठा v3020 *chip, अचिन्हित अक्षर bit)
अणु
	gpio_direction_output(chip->gpio[V3020_IO].gpio, bit);
	gpio_set_value(chip->gpio[V3020_CS].gpio, 0);
	gpio_set_value(chip->gpio[V3020_WR].gpio, 0);
	udelay(1);
	gpio_set_value(chip->gpio[V3020_WR].gpio, 1);
	gpio_set_value(chip->gpio[V3020_CS].gpio, 1);
पूर्ण

अटल अचिन्हित अक्षर v3020_gpio_पढ़ो_bit(काष्ठा v3020 *chip)
अणु
	पूर्णांक bit;

	gpio_direction_input(chip->gpio[V3020_IO].gpio);
	gpio_set_value(chip->gpio[V3020_CS].gpio, 0);
	gpio_set_value(chip->gpio[V3020_RD].gpio, 0);
	udelay(1);
	bit = !!gpio_get_value(chip->gpio[V3020_IO].gpio);
	udelay(1);
	gpio_set_value(chip->gpio[V3020_RD].gpio, 1);
	gpio_set_value(chip->gpio[V3020_CS].gpio, 1);

	वापस bit;
पूर्ण

अटल स्थिर काष्ठा v3020_chip_ops v3020_gpio_ops = अणु
	.map_io		= v3020_gpio_map,
	.unmap_io	= v3020_gpio_unmap,
	.पढ़ो_bit	= v3020_gpio_पढ़ो_bit,
	.ग_लिखो_bit	= v3020_gpio_ग_लिखो_bit,
पूर्ण;

अटल व्योम v3020_set_reg(काष्ठा v3020 *chip, अचिन्हित अक्षर address,
			अचिन्हित अक्षर data)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर पंचांगp;

	पंचांगp = address;
	क्रम (i = 0; i < 4; i++) अणु
		chip->ops->ग_लिखो_bit(chip, (पंचांगp & 1));
		पंचांगp >>= 1;
		udelay(1);
	पूर्ण

	/* Commands करोnt have data */
	अगर (!V3020_IS_COMMAND(address)) अणु
		क्रम (i = 0; i < 8; i++) अणु
			chip->ops->ग_लिखो_bit(chip, (data & 1));
			data >>= 1;
			udelay(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित अक्षर v3020_get_reg(काष्ठा v3020 *chip, अचिन्हित अक्षर address)
अणु
	अचिन्हित पूर्णांक data = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		chip->ops->ग_लिखो_bit(chip, (address & 1));
		address >>= 1;
		udelay(1);
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		data >>= 1;
		अगर (chip->ops->पढ़ो_bit(chip))
			data |= 0x80;
		udelay(1);
	पूर्ण

	वापस data;
पूर्ण

अटल पूर्णांक v3020_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा v3020 *chip = dev_get_drvdata(dev);
	पूर्णांक पंचांगp;

	/* Copy the current समय to ram... */
	v3020_set_reg(chip, V3020_CMD_CLOCK2RAM, 0);

	/* ...and then पढ़ो स्थिरant values. */
	पंचांगp = v3020_get_reg(chip, V3020_SECONDS);
	dt->पंचांग_sec	= bcd2bin(पंचांगp);
	पंचांगp = v3020_get_reg(chip, V3020_MINUTES);
	dt->पंचांग_min	= bcd2bin(पंचांगp);
	पंचांगp = v3020_get_reg(chip, V3020_HOURS);
	dt->पंचांग_hour	= bcd2bin(पंचांगp);
	पंचांगp = v3020_get_reg(chip, V3020_MONTH_DAY);
	dt->पंचांग_mday	= bcd2bin(पंचांगp);
	पंचांगp = v3020_get_reg(chip, V3020_MONTH);
	dt->पंचांग_mon    = bcd2bin(पंचांगp) - 1;
	पंचांगp = v3020_get_reg(chip, V3020_WEEK_DAY);
	dt->पंचांग_wday	= bcd2bin(पंचांगp);
	पंचांगp = v3020_get_reg(chip, V3020_YEAR);
	dt->पंचांग_year = bcd2bin(पंचांगp)+100;

	dev_dbg(dev, "\n%s : Read RTC values\n", __func__);
	dev_dbg(dev, "tm_hour: %i\n", dt->पंचांग_hour);
	dev_dbg(dev, "tm_min : %i\n", dt->पंचांग_min);
	dev_dbg(dev, "tm_sec : %i\n", dt->पंचांग_sec);
	dev_dbg(dev, "tm_year: %i\n", dt->पंचांग_year);
	dev_dbg(dev, "tm_mon : %i\n", dt->पंचांग_mon);
	dev_dbg(dev, "tm_mday: %i\n", dt->पंचांग_mday);
	dev_dbg(dev, "tm_wday: %i\n", dt->पंचांग_wday);

	वापस 0;
पूर्ण


अटल पूर्णांक v3020_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा v3020 *chip = dev_get_drvdata(dev);

	dev_dbg(dev, "\n%s : Setting RTC values\n", __func__);
	dev_dbg(dev, "tm_sec : %i\n", dt->पंचांग_sec);
	dev_dbg(dev, "tm_min : %i\n", dt->पंचांग_min);
	dev_dbg(dev, "tm_hour: %i\n", dt->पंचांग_hour);
	dev_dbg(dev, "tm_mday: %i\n", dt->पंचांग_mday);
	dev_dbg(dev, "tm_wday: %i\n", dt->पंचांग_wday);
	dev_dbg(dev, "tm_year: %i\n", dt->पंचांग_year);

	/* Write all the values to ram... */
	v3020_set_reg(chip, V3020_SECONDS,	bin2bcd(dt->पंचांग_sec));
	v3020_set_reg(chip, V3020_MINUTES,	bin2bcd(dt->पंचांग_min));
	v3020_set_reg(chip, V3020_HOURS,	bin2bcd(dt->पंचांग_hour));
	v3020_set_reg(chip, V3020_MONTH_DAY,	bin2bcd(dt->पंचांग_mday));
	v3020_set_reg(chip, V3020_MONTH,	bin2bcd(dt->पंचांग_mon + 1));
	v3020_set_reg(chip, V3020_WEEK_DAY,	bin2bcd(dt->पंचांग_wday));
	v3020_set_reg(chip, V3020_YEAR,		bin2bcd(dt->पंचांग_year % 100));

	/* ...and set the घड़ी. */
	v3020_set_reg(chip, V3020_CMD_RAM2CLOCK, 0);

	/* Compulab used this delay here. I करोnt know why,
	 * the datasheet करोes not specअगरy a delay. */
	/*mdelay(5);*/

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops v3020_rtc_ops = अणु
	.पढ़ो_समय	= v3020_पढ़ो_समय,
	.set_समय	= v3020_set_समय,
पूर्ण;

अटल पूर्णांक rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v3020_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा v3020 *chip;
	पूर्णांक retval = -EBUSY;
	पूर्णांक i;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	अगर (pdata->use_gpio)
		chip->ops = &v3020_gpio_ops;
	अन्यथा
		chip->ops = &v3020_mmio_ops;

	retval = chip->ops->map_io(chip, pdev, pdata);
	अगर (retval)
		वापस retval;

	/* Make sure the v3020 expects a communication cycle
	 * by पढ़ोing 8 बार */
	क्रम (i = 0; i < 8; i++)
		chip->ops->पढ़ो_bit(chip);

	/* Test chip by करोing a ग_लिखो/पढ़ो sequence
	 * to the chip ram */
	v3020_set_reg(chip, V3020_SECONDS, 0x33);
	अगर (v3020_get_reg(chip, V3020_SECONDS) != 0x33) अणु
		retval = -ENODEV;
		जाओ err_io;
	पूर्ण

	/* Make sure frequency measurement mode, test modes, and lock
	 * are all disabled */
	v3020_set_reg(chip, V3020_STATUS_0, 0x0);

	अगर (pdata->use_gpio)
		dev_info(&pdev->dev, "Chip available at GPIOs "
			 "%d, %d, %d, %d\n",
			 chip->gpio[V3020_CS].gpio, chip->gpio[V3020_WR].gpio,
			 chip->gpio[V3020_RD].gpio, chip->gpio[V3020_IO].gpio);
	अन्यथा
		dev_info(&pdev->dev, "Chip available at "
			 "physical address 0x%llx,"
			 "data connected to D%d\n",
			 (अचिन्हित दीर्घ दीर्घ)pdev->resource[0].start,
			 chip->leftshअगरt);

	platक्रमm_set_drvdata(pdev, chip);

	chip->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "v3020",
					&v3020_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(chip->rtc)) अणु
		retval = PTR_ERR(chip->rtc);
		जाओ err_io;
	पूर्ण

	वापस 0;

err_io:
	chip->ops->unmap_io(chip);

	वापस retval;
पूर्ण

अटल पूर्णांक rtc_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा v3020 *chip = platक्रमm_get_drvdata(dev);

	chip->ops->unmap_io(chip);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rtc_device_driver = अणु
	.probe	= rtc_probe,
	.हटाओ = rtc_हटाओ,
	.driver = अणु
		.name	= "v3020",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rtc_device_driver);

MODULE_DESCRIPTION("V3020 RTC");
MODULE_AUTHOR("Raphael Assenat");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:v3020");
