<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// wm831x-isink.c  --  Current sink driver क्रम the WM831x series
//
// Copyright 2009 Wolfson Microelectronics PLC.
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/regulator.h>
#समावेश <linux/mfd/wm831x/pdata.h>

#घोषणा WM831X_ISINK_MAX_NAME 7

काष्ठा wm831x_isink अणु
	अक्षर name[WM831X_ISINK_MAX_NAME];
	काष्ठा regulator_desc desc;
	पूर्णांक reg;
	काष्ठा wm831x *wm831x;
	काष्ठा regulator_dev *regulator;
पूर्ण;

अटल पूर्णांक wm831x_isink_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_isink *isink = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = isink->wm831x;
	पूर्णांक ret;

	/* We have a two stage enable: first start the ISINK... */
	ret = wm831x_set_bits(wm831x, isink->reg, WM831X_CS1_ENA,
			      WM831X_CS1_ENA);
	अगर (ret != 0)
		वापस ret;

	/* ...then enable drive */
	ret = wm831x_set_bits(wm831x, isink->reg, WM831X_CS1_DRIVE,
			      WM831X_CS1_DRIVE);
	अगर (ret != 0)
		wm831x_set_bits(wm831x, isink->reg, WM831X_CS1_ENA, 0);

	वापस ret;

पूर्ण

अटल पूर्णांक wm831x_isink_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_isink *isink = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = isink->wm831x;
	पूर्णांक ret;

	ret = wm831x_set_bits(wm831x, isink->reg, WM831X_CS1_DRIVE, 0);
	अगर (ret < 0)
		वापस ret;

	ret = wm831x_set_bits(wm831x, isink->reg, WM831X_CS1_ENA, 0);
	अगर (ret < 0)
		वापस ret;

	वापस ret;

पूर्ण

अटल पूर्णांक wm831x_isink_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_isink *isink = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = isink->wm831x;
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, isink->reg);
	अगर (ret < 0)
		वापस ret;

	अगर ((ret & (WM831X_CS1_ENA | WM831X_CS1_DRIVE)) ==
	    (WM831X_CS1_ENA | WM831X_CS1_DRIVE))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops wm831x_isink_ops = अणु
	.is_enabled = wm831x_isink_is_enabled,
	.enable = wm831x_isink_enable,
	.disable = wm831x_isink_disable,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
पूर्ण;

अटल irqवापस_t wm831x_isink_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_isink *isink = data;

	regulator_notअगरier_call_chain(isink->regulator,
				      REGULATOR_EVENT_OVER_CURRENT,
				      शून्य);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक wm831x_isink_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	काष्ठा wm831x_isink *isink;
	पूर्णांक id = pdev->id % ARRAY_SIZE(pdata->isink);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	dev_dbg(&pdev->dev, "Probing ISINK%d\n", id + 1);

	अगर (pdata == शून्य || pdata->isink[id] == शून्य)
		वापस -ENODEV;

	isink = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_isink),
			     GFP_KERNEL);
	अगर (!isink)
		वापस -ENOMEM;

	isink->wm831x = wm831x;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "No REG resource\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	isink->reg = res->start;

	/* For current parts this is correct; probably need to revisit
	 * in future.
	 */
	snम_लिखो(isink->name, माप(isink->name), "ISINK%d", id + 1);
	isink->desc.name = isink->name;
	isink->desc.id = id;
	isink->desc.ops = &wm831x_isink_ops;
	isink->desc.type = REGULATOR_CURRENT;
	isink->desc.owner = THIS_MODULE;
	isink->desc.curr_table = wm831x_isinkv_values,
	isink->desc.n_current_limits = ARRAY_SIZE(wm831x_isinkv_values),
	isink->desc.csel_reg = isink->reg,
	isink->desc.csel_mask = WM831X_CS1_ISEL_MASK,

	config.dev = pdev->dev.parent;
	config.init_data = pdata->isink[id];
	config.driver_data = isink;
	config.regmap = wm831x->regmap;

	isink->regulator = devm_regulator_रेजिस्टर(&pdev->dev, &isink->desc,
						   &config);
	अगर (IS_ERR(isink->regulator)) अणु
		ret = PTR_ERR(isink->regulator);
		dev_err(wm831x->dev, "Failed to register ISINK%d: %d\n",
			id + 1, ret);
		जाओ err;
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq(pdev, 0));
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					wm831x_isink_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					isink->name,
					isink);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request ISINK IRQ %d: %d\n",
			irq, ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, isink);

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_isink_driver = अणु
	.probe = wm831x_isink_probe,
	.driver		= अणु
		.name	= "wm831x-isink",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init wm831x_isink_init(व्योम)
अणु
	पूर्णांक ret;
	ret = platक्रमm_driver_रेजिस्टर(&wm831x_isink_driver);
	अगर (ret != 0)
		pr_err("Failed to register WM831x ISINK driver: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(wm831x_isink_init);

अटल व्योम __निकास wm831x_isink_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wm831x_isink_driver);
पूर्ण
module_निकास(wm831x_isink_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown");
MODULE_DESCRIPTION("WM831x current sink driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-isink");
