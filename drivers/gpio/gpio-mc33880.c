<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MC33880 high-side/low-side चयन GPIO driver
 * Copyright (c) 2009 Intel Corporation
 */

/* Supports:
 * Freescale MC33880 high-side/low-side चयन
 */

#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/mc33880.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_NAME "mc33880"

/*
 * Pin configurations, see MAX7301 datasheet page 6
 */
#घोषणा PIN_CONFIG_MASK 0x03
#घोषणा PIN_CONFIG_IN_PULLUP 0x03
#घोषणा PIN_CONFIG_IN_WO_PULLUP 0x02
#घोषणा PIN_CONFIG_OUT 0x01

#घोषणा PIN_NUMBER 8


/*
 * Some रेजिस्टरs must be पढ़ो back to modअगरy.
 * To save समय we cache them here in memory
 */
काष्ठा mc33880 अणु
	काष्ठा mutex	lock;	/* protect from simultaneous accesses */
	u8		port_config;
	काष्ठा gpio_chip chip;
	काष्ठा spi_device *spi;
पूर्ण;

अटल पूर्णांक mc33880_ग_लिखो_config(काष्ठा mc33880 *mc)
अणु
	वापस spi_ग_लिखो(mc->spi, &mc->port_config, माप(mc->port_config));
पूर्ण


अटल पूर्णांक __mc33880_set(काष्ठा mc33880 *mc, अचिन्हित offset, पूर्णांक value)
अणु
	अगर (value)
		mc->port_config |= 1 << offset;
	अन्यथा
		mc->port_config &= ~(1 << offset);

	वापस mc33880_ग_लिखो_config(mc);
पूर्ण


अटल व्योम mc33880_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा mc33880 *mc = gpiochip_get_data(chip);

	mutex_lock(&mc->lock);

	__mc33880_set(mc, offset, value);

	mutex_unlock(&mc->lock);
पूर्ण

अटल पूर्णांक mc33880_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा mc33880 *mc;
	काष्ठा mc33880_platक्रमm_data *pdata;
	पूर्णांक ret;

	pdata = dev_get_platdata(&spi->dev);
	अगर (!pdata || !pdata->base) अणु
		dev_dbg(&spi->dev, "incorrect or missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * bits_per_word cannot be configured in platक्रमm data
	 */
	spi->bits_per_word = 8;

	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	mc = devm_kzalloc(&spi->dev, माप(काष्ठा mc33880), GFP_KERNEL);
	अगर (!mc)
		वापस -ENOMEM;

	mutex_init(&mc->lock);

	spi_set_drvdata(spi, mc);

	mc->spi = spi;

	mc->chip.label = DRIVER_NAME,
	mc->chip.set = mc33880_set;
	mc->chip.base = pdata->base;
	mc->chip.ngpio = PIN_NUMBER;
	mc->chip.can_sleep = true;
	mc->chip.parent = &spi->dev;
	mc->chip.owner = THIS_MODULE;

	mc->port_config = 0x00;
	/* ग_लिखो twice, because during initialisation the first setting
	 * is just क्रम testing SPI communication, and the second is the
	 * "real" configuration
	 */
	ret = mc33880_ग_लिखो_config(mc);
	mc->port_config = 0x00;
	अगर (!ret)
		ret = mc33880_ग_लिखो_config(mc);

	अगर (ret) अणु
		dev_err(&spi->dev, "Failed writing to " DRIVER_NAME ": %d\n",
			ret);
		जाओ निकास_destroy;
	पूर्ण

	ret = gpiochip_add_data(&mc->chip, mc);
	अगर (ret)
		जाओ निकास_destroy;

	वापस ret;

निकास_destroy:
	mutex_destroy(&mc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mc33880_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा mc33880 *mc;

	mc = spi_get_drvdata(spi);
	अगर (!mc)
		वापस -ENODEV;

	gpiochip_हटाओ(&mc->chip);
	mutex_destroy(&mc->lock);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver mc33880_driver = अणु
	.driver = अणु
		.name		= DRIVER_NAME,
	पूर्ण,
	.probe		= mc33880_probe,
	.हटाओ		= mc33880_हटाओ,
पूर्ण;

अटल पूर्णांक __init mc33880_init(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&mc33880_driver);
पूर्ण
/* रेजिस्टर after spi postcore initcall and beक्रमe
 * subsys initcalls that may rely on these GPIOs
 */
subsys_initcall(mc33880_init);

अटल व्योम __निकास mc33880_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&mc33880_driver);
पूर्ण
module_निकास(mc33880_निकास);

MODULE_AUTHOR("Mocean Laboratories <info@mocean-labs.com>");
MODULE_LICENSE("GPL v2");

