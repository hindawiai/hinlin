<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MEN 16Z127 GPIO driver
 *
 * Copyright (C) 2016 MEN Mikroelektronik GmbH (www.men.de)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/mcb.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>

#घोषणा MEN_Z127_CTRL	0x00
#घोषणा MEN_Z127_PSR	0x04
#घोषणा MEN_Z127_IRQR	0x08
#घोषणा MEN_Z127_GPIODR	0x0c
#घोषणा MEN_Z127_IER1	0x10
#घोषणा MEN_Z127_IER2	0x14
#घोषणा MEN_Z127_DBER	0x18
#घोषणा MEN_Z127_ODER	0x1C
#घोषणा GPIO_TO_DBCNT_REG(gpio)	((gpio * 4) + 0x80)

#घोषणा MEN_Z127_DB_MIN_US	50
/* 16 bit compare रेजिस्टर. Each bit represents 50us */
#घोषणा MEN_Z127_DB_MAX_US	(0xffff * MEN_Z127_DB_MIN_US)
#घोषणा MEN_Z127_DB_IN_RANGE(db)	((db >= MEN_Z127_DB_MIN_US) && \
					 (db <= MEN_Z127_DB_MAX_US))

काष्ठा men_z127_gpio अणु
	काष्ठा gpio_chip gc;
	व्योम __iomem *reg_base;
	काष्ठा resource *mem;
पूर्ण;

अटल पूर्णांक men_z127_debounce(काष्ठा gpio_chip *gc, अचिन्हित gpio,
			     अचिन्हित debounce)
अणु
	काष्ठा men_z127_gpio *priv = gpiochip_get_data(gc);
	काष्ठा device *dev = gc->parent;
	अचिन्हित पूर्णांक rnd;
	u32 db_en, db_cnt;

	अगर (!MEN_Z127_DB_IN_RANGE(debounce)) अणु
		dev_err(dev, "debounce value %u out of range", debounce);
		वापस -EINVAL;
	पूर्ण

	अगर (debounce > 0) अणु
		/* round up or करोwn depending on MSB-1 */
		rnd = fls(debounce) - 1;

		अगर (rnd && (debounce & BIT(rnd - 1)))
			debounce = roundup(debounce, MEN_Z127_DB_MIN_US);
		अन्यथा
			debounce = roundकरोwn(debounce, MEN_Z127_DB_MIN_US);

		अगर (debounce > MEN_Z127_DB_MAX_US)
			debounce = MEN_Z127_DB_MAX_US;

		/* 50us per रेजिस्टर unit */
		debounce /= 50;
	पूर्ण

	spin_lock(&gc->bgpio_lock);

	db_en = पढ़ोl(priv->reg_base + MEN_Z127_DBER);

	अगर (debounce == 0) अणु
		db_en &= ~BIT(gpio);
		db_cnt = 0;
	पूर्ण अन्यथा अणु
		db_en |= BIT(gpio);
		db_cnt = debounce;
	पूर्ण

	ग_लिखोl(db_en, priv->reg_base + MEN_Z127_DBER);
	ग_लिखोl(db_cnt, priv->reg_base + GPIO_TO_DBCNT_REG(gpio));

	spin_unlock(&gc->bgpio_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक men_z127_set_single_ended(काष्ठा gpio_chip *gc,
				     अचिन्हित offset,
				     क्रमागत pin_config_param param)
अणु
	काष्ठा men_z127_gpio *priv = gpiochip_get_data(gc);
	u32 od_en;

	spin_lock(&gc->bgpio_lock);
	od_en = पढ़ोl(priv->reg_base + MEN_Z127_ODER);

	अगर (param == PIN_CONFIG_DRIVE_OPEN_DRAIN)
		od_en |= BIT(offset);
	अन्यथा
		/* Implicitly PIN_CONFIG_DRIVE_PUSH_PULL */
		od_en &= ~BIT(offset);

	ग_लिखोl(od_en, priv->reg_base + MEN_Z127_ODER);
	spin_unlock(&gc->bgpio_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक men_z127_set_config(काष्ठा gpio_chip *gc, अचिन्हित offset,
			       अचिन्हित दीर्घ config)
अणु
	क्रमागत pin_config_param param = pinconf_to_config_param(config);

	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस men_z127_set_single_ended(gc, offset, param);

	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		वापस men_z127_debounce(gc, offset,
			pinconf_to_config_argument(config));

	शेष:
		अवरोध;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक men_z127_probe(काष्ठा mcb_device *mdev,
			  स्थिर काष्ठा mcb_device_id *id)
अणु
	काष्ठा men_z127_gpio *men_z127_gpio;
	काष्ठा device *dev = &mdev->dev;
	पूर्णांक ret;

	men_z127_gpio = devm_kzalloc(dev, माप(काष्ठा men_z127_gpio),
				     GFP_KERNEL);
	अगर (!men_z127_gpio)
		वापस -ENOMEM;

	men_z127_gpio->mem = mcb_request_mem(mdev, dev_name(dev));
	अगर (IS_ERR(men_z127_gpio->mem)) अणु
		dev_err(dev, "failed to request device memory");
		वापस PTR_ERR(men_z127_gpio->mem);
	पूर्ण

	men_z127_gpio->reg_base = ioremap(men_z127_gpio->mem->start,
					  resource_size(men_z127_gpio->mem));
	अगर (men_z127_gpio->reg_base == शून्य) अणु
		ret = -ENXIO;
		जाओ err_release;
	पूर्ण

	mcb_set_drvdata(mdev, men_z127_gpio);

	ret = bgpio_init(&men_z127_gpio->gc, &mdev->dev, 4,
			 men_z127_gpio->reg_base + MEN_Z127_PSR,
			 men_z127_gpio->reg_base + MEN_Z127_CTRL,
			 शून्य,
			 men_z127_gpio->reg_base + MEN_Z127_GPIODR,
			 शून्य, 0);
	अगर (ret)
		जाओ err_unmap;

	men_z127_gpio->gc.set_config = men_z127_set_config;

	ret = gpiochip_add_data(&men_z127_gpio->gc, men_z127_gpio);
	अगर (ret) अणु
		dev_err(dev, "failed to register MEN 16Z127 GPIO controller");
		जाओ err_unmap;
	पूर्ण

	dev_info(dev, "MEN 16Z127 GPIO driver registered");

	वापस 0;

err_unmap:
	iounmap(men_z127_gpio->reg_base);
err_release:
	mcb_release_mem(men_z127_gpio->mem);
	वापस ret;
पूर्ण

अटल व्योम men_z127_हटाओ(काष्ठा mcb_device *mdev)
अणु
	काष्ठा men_z127_gpio *men_z127_gpio = mcb_get_drvdata(mdev);

	gpiochip_हटाओ(&men_z127_gpio->gc);
	iounmap(men_z127_gpio->reg_base);
	mcb_release_mem(men_z127_gpio->mem);
पूर्ण

अटल स्थिर काष्ठा mcb_device_id men_z127_ids[] = अणु
	अणु .device = 0x7f पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mcb, men_z127_ids);

अटल काष्ठा mcb_driver men_z127_driver = अणु
	.driver = अणु
		.name = "z127-gpio",
	पूर्ण,
	.probe = men_z127_probe,
	.हटाओ = men_z127_हटाओ,
	.id_table = men_z127_ids,
पूर्ण;
module_mcb_driver(men_z127_driver);

MODULE_AUTHOR("Andreas Werner <andreas.werner@men.de>");
MODULE_DESCRIPTION("MEN 16z127 GPIO Controller");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("mcb:16z127");
MODULE_IMPORT_NS(MCB);
