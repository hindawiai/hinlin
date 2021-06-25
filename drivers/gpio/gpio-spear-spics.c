<शैली गुरु>
/*
 * SPEAr platक्रमm SPI chipselect असलtraction over gpiolib
 *
 * Copyright (C) 2012 ST Microelectronics
 * Shiraz Hashim <shiraz.linux.kernel@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

/* maximum chipselects */
#घोषणा NUM_OF_GPIO	4

/*
 * Provision is available on some SPEAr SoCs to control ARM PL022 spi cs
 * through प्रणाली रेजिस्टरs. This रेजिस्टर lies outside spi (pl022)
 * address space पूर्णांकo प्रणाली रेजिस्टरs.
 *
 * It provides control क्रम spi chip select lines so that any chipselect
 * (out of 4 possible chipselects in pl022) can be made low to select
 * the particular slave.
 */

/**
 * काष्ठा spear_spics - represents spi chip select control
 * @base: base address
 * @perip_cfg: configuration रेजिस्टर
 * @sw_enable_bit: bit to enable s/w control over chipselects
 * @cs_value_bit: bit to program high or low chipselect
 * @cs_enable_mask: mask to select bits required to select chipselect
 * @cs_enable_shअगरt: bit pos of cs_enable_mask
 * @use_count: use count of a spi controller cs lines
 * @last_off: stores last offset caller of set_value()
 * @chip: gpio_chip असलtraction
 */
काष्ठा spear_spics अणु
	व्योम __iomem		*base;
	u32			perip_cfg;
	u32			sw_enable_bit;
	u32			cs_value_bit;
	u32			cs_enable_mask;
	u32			cs_enable_shअगरt;
	अचिन्हित दीर्घ		use_count;
	पूर्णांक			last_off;
	काष्ठा gpio_chip	chip;
पूर्ण;

/* gpio framework specअगरic routines */
अटल पूर्णांक spics_get_value(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस -ENXIO;
पूर्ण

अटल व्योम spics_set_value(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा spear_spics *spics = gpiochip_get_data(chip);
	u32 पंचांगp;

	/* select chip select from रेजिस्टर */
	पंचांगp = पढ़ोl_relaxed(spics->base + spics->perip_cfg);
	अगर (spics->last_off != offset) अणु
		spics->last_off = offset;
		पंचांगp &= ~(spics->cs_enable_mask << spics->cs_enable_shअगरt);
		पंचांगp |= offset << spics->cs_enable_shअगरt;
	पूर्ण

	/* toggle chip select line */
	पंचांगp &= ~(0x1 << spics->cs_value_bit);
	पंचांगp |= value << spics->cs_value_bit;
	ग_लिखोl_relaxed(पंचांगp, spics->base + spics->perip_cfg);
पूर्ण

अटल पूर्णांक spics_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक spics_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
		पूर्णांक value)
अणु
	spics_set_value(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक spics_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा spear_spics *spics = gpiochip_get_data(chip);
	u32 पंचांगp;

	अगर (!spics->use_count++) अणु
		पंचांगp = पढ़ोl_relaxed(spics->base + spics->perip_cfg);
		पंचांगp |= 0x1 << spics->sw_enable_bit;
		पंचांगp |= 0x1 << spics->cs_value_bit;
		ग_लिखोl_relaxed(पंचांगp, spics->base + spics->perip_cfg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम spics_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा spear_spics *spics = gpiochip_get_data(chip);
	u32 पंचांगp;

	अगर (!--spics->use_count) अणु
		पंचांगp = पढ़ोl_relaxed(spics->base + spics->perip_cfg);
		पंचांगp &= ~(0x1 << spics->sw_enable_bit);
		ग_लिखोl_relaxed(पंचांगp, spics->base + spics->perip_cfg);
	पूर्ण
पूर्ण

अटल पूर्णांक spics_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spear_spics *spics;
	पूर्णांक ret;

	spics = devm_kzalloc(&pdev->dev, माप(*spics), GFP_KERNEL);
	अगर (!spics)
		वापस -ENOMEM;

	spics->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spics->base))
		वापस PTR_ERR(spics->base);

	अगर (of_property_पढ़ो_u32(np, "st-spics,peripcfg-reg",
				&spics->perip_cfg))
		जाओ err_dt_data;
	अगर (of_property_पढ़ो_u32(np, "st-spics,sw-enable-bit",
				&spics->sw_enable_bit))
		जाओ err_dt_data;
	अगर (of_property_पढ़ो_u32(np, "st-spics,cs-value-bit",
				&spics->cs_value_bit))
		जाओ err_dt_data;
	अगर (of_property_पढ़ो_u32(np, "st-spics,cs-enable-mask",
				&spics->cs_enable_mask))
		जाओ err_dt_data;
	अगर (of_property_पढ़ो_u32(np, "st-spics,cs-enable-shift",
				&spics->cs_enable_shअगरt))
		जाओ err_dt_data;

	platक्रमm_set_drvdata(pdev, spics);

	spics->chip.ngpio = NUM_OF_GPIO;
	spics->chip.base = -1;
	spics->chip.request = spics_request;
	spics->chip.मुक्त = spics_मुक्त;
	spics->chip.direction_input = spics_direction_input;
	spics->chip.direction_output = spics_direction_output;
	spics->chip.get = spics_get_value;
	spics->chip.set = spics_set_value;
	spics->chip.label = dev_name(&pdev->dev);
	spics->chip.parent = &pdev->dev;
	spics->chip.owner = THIS_MODULE;
	spics->last_off = -1;

	ret = devm_gpiochip_add_data(&pdev->dev, &spics->chip, spics);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to add gpio chip\n");
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "spear spics registered\n");
	वापस 0;

err_dt_data:
	dev_err(&pdev->dev, "DT probe failed\n");
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा of_device_id spics_gpio_of_match[] = अणु
	अणु .compatible = "st,spear-spics-gpio" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver spics_gpio_driver = अणु
	.probe = spics_gpio_probe,
	.driver = अणु
		.name = "spear-spics-gpio",
		.of_match_table = spics_gpio_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init spics_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&spics_gpio_driver);
पूर्ण
subsys_initcall(spics_gpio_init);
