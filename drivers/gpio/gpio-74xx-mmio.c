<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 74xx MMIO GPIO driver
 *
 *  Copyright (C) 2014 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MMIO_74XX_सूची_IN	(0 << 8)
#घोषणा MMIO_74XX_सूची_OUT	(1 << 8)
#घोषणा MMIO_74XX_BIT_CNT(x)	((x) & 0xff)

काष्ठा mmio_74xx_gpio_priv अणु
	काष्ठा gpio_chip	gc;
	अचिन्हित		flags;
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmio_74xx_gpio_ids[] = अणु
	अणु
		.compatible	= "ti,741g125",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_IN | 1),
	पूर्ण,
	अणु
		.compatible	= "ti,742g125",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_IN | 2),
	पूर्ण,
	अणु
		.compatible	= "ti,74125",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_IN | 4),
	पूर्ण,
	अणु
		.compatible	= "ti,74365",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_IN | 6),
	पूर्ण,
	अणु
		.compatible	= "ti,74244",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_IN | 8),
	पूर्ण,
	अणु
		.compatible	= "ti,741624",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_IN | 16),
	पूर्ण,
	अणु
		.compatible	= "ti,741g74",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_OUT | 1),
	पूर्ण,
	अणु
		.compatible	= "ti,7474",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_OUT | 2),
	पूर्ण,
	अणु
		.compatible	= "ti,74175",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_OUT | 4),
	पूर्ण,
	अणु
		.compatible	= "ti,74174",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_OUT | 6),
	पूर्ण,
	अणु
		.compatible	= "ti,74273",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_OUT | 8),
	पूर्ण,
	अणु
		.compatible	= "ti,7416374",
		.data		= (स्थिर व्योम *)(MMIO_74XX_सूची_OUT | 16),
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mmio_74xx_gpio_ids);

अटल पूर्णांक mmio_74xx_get_direction(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा mmio_74xx_gpio_priv *priv = gpiochip_get_data(gc);

	अगर (priv->flags & MMIO_74XX_सूची_OUT)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस  GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक mmio_74xx_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा mmio_74xx_gpio_priv *priv = gpiochip_get_data(gc);

	वापस (priv->flags & MMIO_74XX_सूची_OUT) ? -ENOTSUPP : 0;
पूर्ण

अटल पूर्णांक mmio_74xx_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा mmio_74xx_gpio_priv *priv = gpiochip_get_data(gc);

	अगर (priv->flags & MMIO_74XX_सूची_OUT) अणु
		gc->set(gc, gpio, val);
		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक mmio_74xx_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmio_74xx_gpio_priv *priv;
	व्योम __iomem *dat;
	पूर्णांक err;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->flags = (uपूर्णांकptr_t)of_device_get_match_data(&pdev->dev);

	dat = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dat))
		वापस PTR_ERR(dat);

	err = bgpio_init(&priv->gc, &pdev->dev,
			 DIV_ROUND_UP(MMIO_74XX_BIT_CNT(priv->flags), 8),
			 dat, शून्य, शून्य, शून्य, शून्य, 0);
	अगर (err)
		वापस err;

	priv->gc.direction_input = mmio_74xx_dir_in;
	priv->gc.direction_output = mmio_74xx_dir_out;
	priv->gc.get_direction = mmio_74xx_get_direction;
	priv->gc.ngpio = MMIO_74XX_BIT_CNT(priv->flags);
	priv->gc.owner = THIS_MODULE;

	platक्रमm_set_drvdata(pdev, priv);

	वापस devm_gpiochip_add_data(&pdev->dev, &priv->gc, priv);
पूर्ण

अटल काष्ठा platक्रमm_driver mmio_74xx_gpio_driver = अणु
	.driver	= अणु
		.name		= "74xx-mmio-gpio",
		.of_match_table	= mmio_74xx_gpio_ids,
	पूर्ण,
	.probe	= mmio_74xx_gpio_probe,
पूर्ण;
module_platक्रमm_driver(mmio_74xx_gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("74xx MMIO GPIO driver");
