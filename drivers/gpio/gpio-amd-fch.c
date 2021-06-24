<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * GPIO driver क्रम the AMD G series FCH (eg. GX-412TC)
 *
 * Copyright (C) 2018 metux IT consult
 * Author: Enrico Weigelt, metux IT consult <info@metux.net>
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_data/gpio/gpio-amd-fch.h>
#समावेश <linux/spinlock.h>

#घोषणा AMD_FCH_MMIO_BASE		0xFED80000
#घोषणा AMD_FCH_GPIO_BANK0_BASE		0x1500
#घोषणा AMD_FCH_GPIO_SIZE		0x0300

#घोषणा AMD_FCH_GPIO_FLAG_सूचीECTION	BIT(23)
#घोषणा AMD_FCH_GPIO_FLAG_WRITE		BIT(22)
#घोषणा AMD_FCH_GPIO_FLAG_READ		BIT(16)

अटल स्थिर काष्ठा resource amd_fch_gpio_iores =
	DEFINE_RES_MEM_NAMED(
		AMD_FCH_MMIO_BASE + AMD_FCH_GPIO_BANK0_BASE,
		AMD_FCH_GPIO_SIZE,
		"amd-fch-gpio-iomem");

काष्ठा amd_fch_gpio_priv अणु
	काष्ठा gpio_chip		gc;
	व्योम __iomem			*base;
	काष्ठा amd_fch_gpio_pdata	*pdata;
	spinlock_t			lock;
पूर्ण;

अटल व्योम __iomem *amd_fch_gpio_addr(काष्ठा amd_fch_gpio_priv *priv,
				       अचिन्हित पूर्णांक gpio)
अणु
	वापस priv->base + priv->pdata->gpio_reg[gpio]*माप(u32);
पूर्ण

अटल पूर्णांक amd_fch_gpio_direction_input(काष्ठा gpio_chip *gc,
					अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा amd_fch_gpio_priv *priv = gpiochip_get_data(gc);
	व्योम __iomem *ptr = amd_fch_gpio_addr(priv, offset);

	spin_lock_irqsave(&priv->lock, flags);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(ptr) & ~AMD_FCH_GPIO_FLAG_सूचीECTION, ptr);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_fch_gpio_direction_output(काष्ठा gpio_chip *gc,
					 अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा amd_fch_gpio_priv *priv = gpiochip_get_data(gc);
	व्योम __iomem *ptr = amd_fch_gpio_addr(priv, gpio);
	u32 val;

	spin_lock_irqsave(&priv->lock, flags);

	val = पढ़ोl_relaxed(ptr);
	अगर (value)
		val |= AMD_FCH_GPIO_FLAG_WRITE;
	अन्यथा
		val &= ~AMD_FCH_GPIO_FLAG_WRITE;

	ग_लिखोl_relaxed(val | AMD_FCH_GPIO_FLAG_सूचीECTION, ptr);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_fch_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_fch_gpio_priv *priv = gpiochip_get_data(gc);
	व्योम __iomem *ptr = amd_fch_gpio_addr(priv, gpio);

	spin_lock_irqsave(&priv->lock, flags);
	ret = (पढ़ोl_relaxed(ptr) & AMD_FCH_GPIO_FLAG_सूचीECTION);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ret ? GPIO_LINE_सूचीECTION_OUT : GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल व्योम amd_fch_gpio_set(काष्ठा gpio_chip *gc,
			     अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा amd_fch_gpio_priv *priv = gpiochip_get_data(gc);
	व्योम __iomem *ptr = amd_fch_gpio_addr(priv, gpio);
	u32 mask;

	spin_lock_irqsave(&priv->lock, flags);

	mask = पढ़ोl_relaxed(ptr);
	अगर (value)
		mask |= AMD_FCH_GPIO_FLAG_WRITE;
	अन्यथा
		mask &= ~AMD_FCH_GPIO_FLAG_WRITE;
	ग_लिखोl_relaxed(mask, ptr);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक amd_fch_gpio_get(काष्ठा gpio_chip *gc,
			    अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	काष्ठा amd_fch_gpio_priv *priv = gpiochip_get_data(gc);
	व्योम __iomem *ptr = amd_fch_gpio_addr(priv, offset);

	spin_lock_irqsave(&priv->lock, flags);
	ret = (पढ़ोl_relaxed(ptr) & AMD_FCH_GPIO_FLAG_READ);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक amd_fch_gpio_request(काष्ठा gpio_chip *chip,
				अचिन्हित पूर्णांक gpio_pin)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक amd_fch_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा amd_fch_gpio_priv *priv;
	काष्ठा amd_fch_gpio_pdata *pdata;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform_data\n");
		वापस -ENOENT;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pdata	= pdata;

	priv->gc.owner			= THIS_MODULE;
	priv->gc.parent			= &pdev->dev;
	priv->gc.label			= dev_name(&pdev->dev);
	priv->gc.ngpio			= priv->pdata->gpio_num;
	priv->gc.names			= priv->pdata->gpio_names;
	priv->gc.base			= -1;
	priv->gc.request		= amd_fch_gpio_request;
	priv->gc.direction_input	= amd_fch_gpio_direction_input;
	priv->gc.direction_output	= amd_fch_gpio_direction_output;
	priv->gc.get_direction		= amd_fch_gpio_get_direction;
	priv->gc.get			= amd_fch_gpio_get;
	priv->gc.set			= amd_fch_gpio_set;

	spin_lock_init(&priv->lock);

	priv->base = devm_ioremap_resource(&pdev->dev, &amd_fch_gpio_iores);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	platक्रमm_set_drvdata(pdev, priv);

	वापस devm_gpiochip_add_data(&pdev->dev, &priv->gc, priv);
पूर्ण

अटल काष्ठा platक्रमm_driver amd_fch_gpio_driver = अणु
	.driver = अणु
		.name = AMD_FCH_GPIO_DRIVER_NAME,
	पूर्ण,
	.probe = amd_fch_gpio_probe,
पूर्ण;

module_platक्रमm_driver(amd_fch_gpio_driver);

MODULE_AUTHOR("Enrico Weigelt, metux IT consult <info@metux.net>");
MODULE_DESCRIPTION("AMD G-series FCH GPIO driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" AMD_FCH_GPIO_DRIVER_NAME);
