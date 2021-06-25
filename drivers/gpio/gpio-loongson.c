<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Loongson-2F/3A/3B GPIO Support
 *
 *  Copyright (c) 2008 Riअक्षरd Liu,  STMicroelectronics	 <riअक्षरd.liu@st.com>
 *  Copyright (c) 2008-2010 Arnaud Patard <apatard@mandriva.com>
 *  Copyright (c) 2013 Hongbing Hu <huhb@lemote.com>
 *  Copyright (c) 2014 Huacai Chen <chenhc@lemote.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/types.h>
#समावेश <loongson.h>

#घोषणा STLS2F_N_GPIO		4
#घोषणा STLS3A_N_GPIO		16

#अगर_घोषित CONFIG_CPU_LOONGSON64
#घोषणा LOONGSON_N_GPIO	STLS3A_N_GPIO
#अन्यथा
#घोषणा LOONGSON_N_GPIO	STLS2F_N_GPIO
#पूर्ण_अगर

/*
 * Offset पूर्णांकo the रेजिस्टर where we पढ़ो lines, we ग_लिखो them from offset 0.
 * This offset is the only thing that stand between us and using
 * GPIO_GENERIC.
 */
#घोषणा LOONGSON_GPIO_IN_OFFSET	16

अटल DEFINE_SPINLOCK(gpio_lock);

अटल पूर्णांक loongson_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	u32 val;

	spin_lock(&gpio_lock);
	val = LOONGSON_GPIODATA;
	spin_unlock(&gpio_lock);

	वापस !!(val & BIT(gpio + LOONGSON_GPIO_IN_OFFSET));
पूर्ण

अटल व्योम loongson_gpio_set_value(काष्ठा gpio_chip *chip,
		अचिन्हित gpio, पूर्णांक value)
अणु
	u32 val;

	spin_lock(&gpio_lock);
	val = LOONGSON_GPIODATA;
	अगर (value)
		val |= BIT(gpio);
	अन्यथा
		val &= ~BIT(gpio);
	LOONGSON_GPIODATA = val;
	spin_unlock(&gpio_lock);
पूर्ण

अटल पूर्णांक loongson_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	u32 temp;

	spin_lock(&gpio_lock);
	temp = LOONGSON_GPIOIE;
	temp |= BIT(gpio);
	LOONGSON_GPIOIE = temp;
	spin_unlock(&gpio_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक loongson_gpio_direction_output(काष्ठा gpio_chip *chip,
		अचिन्हित gpio, पूर्णांक level)
अणु
	u32 temp;

	loongson_gpio_set_value(chip, gpio, level);
	spin_lock(&gpio_lock);
	temp = LOONGSON_GPIOIE;
	temp &= ~BIT(gpio);
	LOONGSON_GPIOIE = temp;
	spin_unlock(&gpio_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक loongson_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_chip *gc;
	काष्ठा device *dev = &pdev->dev;

	gc = devm_kzalloc(dev, माप(*gc), GFP_KERNEL);
	अगर (!gc)
		वापस -ENOMEM;

	gc->label = "loongson-gpio-chip";
	gc->base = 0;
	gc->ngpio = LOONGSON_N_GPIO;
	gc->get = loongson_gpio_get_value;
	gc->set = loongson_gpio_set_value;
	gc->direction_input = loongson_gpio_direction_input;
	gc->direction_output = loongson_gpio_direction_output;

	वापस gpiochip_add_data(gc, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver loongson_gpio_driver = अणु
	.driver = अणु
		.name = "loongson-gpio",
	पूर्ण,
	.probe = loongson_gpio_probe,
पूर्ण;

अटल पूर्णांक __init loongson_gpio_setup(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&loongson_gpio_driver);
	अगर (ret) अणु
		pr_err("error registering loongson GPIO driver\n");
		वापस ret;
	पूर्ण

	pdev = platक्रमm_device_रेजिस्टर_simple("loongson-gpio", -1, शून्य, 0);
	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
postcore_initcall(loongson_gpio_setup);
