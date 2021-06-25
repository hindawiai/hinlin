<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  CLPS711X GPIO driver
 *
 *  Copyright (C) 2012,2013 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>

अटल पूर्णांक clps711x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	व्योम __iomem *dat, *dir;
	काष्ठा gpio_chip *gc;
	पूर्णांक err, id;

	अगर (!np)
		वापस -ENODEV;

	id = of_alias_get_id(np, "gpio");
	अगर ((id < 0) || (id > 4))
		वापस -ENODEV;

	gc = devm_kzalloc(&pdev->dev, माप(*gc), GFP_KERNEL);
	अगर (!gc)
		वापस -ENOMEM;

	dat = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dat))
		वापस PTR_ERR(dat);

	dir = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	चयन (id) अणु
	हाल 3:
		/* PORTD is inverted logic क्रम direction रेजिस्टर */
		err = bgpio_init(gc, &pdev->dev, 1, dat, शून्य, शून्य,
				 शून्य, dir, 0);
		अवरोध;
	शेष:
		err = bgpio_init(gc, &pdev->dev, 1, dat, शून्य, शून्य,
				 dir, शून्य, 0);
		अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	चयन (id) अणु
	हाल 4:
		/* PORTE is 3 lines only */
		gc->ngpio = 3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	gc->base = -1;
	gc->owner = THIS_MODULE;
	platक्रमm_set_drvdata(pdev, gc);

	वापस devm_gpiochip_add_data(&pdev->dev, gc, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused clps711x_gpio_ids[] = अणु
	अणु .compatible = "cirrus,ep7209-gpio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clps711x_gpio_ids);

अटल काष्ठा platक्रमm_driver clps711x_gpio_driver = अणु
	.driver	= अणु
		.name		= "clps711x-gpio",
		.of_match_table	= of_match_ptr(clps711x_gpio_ids),
	पूर्ण,
	.probe	= clps711x_gpio_probe,
पूर्ण;
module_platक्रमm_driver(clps711x_gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("CLPS711X GPIO driver");
MODULE_ALIAS("platform:clps711x-gpio");
