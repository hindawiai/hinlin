<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Touchscreen driver क्रम Marvell 88PM860x
 *
 * Copyright (C) 2009 Marvell International Ltd.
 * 	Haojian Zhuang <haojian.zhuang@marvell.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#घोषणा MEAS_LEN		(8)
#घोषणा ACCURATE_BIT		(12)

/* touch रेजिस्टर */
#घोषणा MEAS_EN3		(0x52)

#घोषणा MEAS_TSIX_1		(0x8D)
#घोषणा MEAS_TSIX_2		(0x8E)
#घोषणा MEAS_TSIY_1		(0x8F)
#घोषणा MEAS_TSIY_2		(0x90)
#घोषणा MEAS_TSIZ1_1		(0x91)
#घोषणा MEAS_TSIZ1_2		(0x92)
#घोषणा MEAS_TSIZ2_1		(0x93)
#घोषणा MEAS_TSIZ2_2		(0x94)

/* bit definitions of touch */
#घोषणा MEAS_PD_EN		(1 << 3)
#घोषणा MEAS_TSIX_EN		(1 << 4)
#घोषणा MEAS_TSIY_EN		(1 << 5)
#घोषणा MEAS_TSIZ1_EN		(1 << 6)
#घोषणा MEAS_TSIZ2_EN		(1 << 7)

काष्ठा pm860x_touch अणु
	काष्ठा input_dev *idev;
	काष्ठा i2c_client *i2c;
	काष्ठा pm860x_chip *chip;
	पूर्णांक irq;
	पूर्णांक res_x;		/* resistor of Xplate */
पूर्ण;

अटल irqवापस_t pm860x_touch_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_touch *touch = data;
	काष्ठा pm860x_chip *chip = touch->chip;
	अचिन्हित अक्षर buf[MEAS_LEN];
	पूर्णांक x, y, pen_करोwn;
	पूर्णांक z1, z2, rt = 0;
	पूर्णांक ret;

	ret = pm860x_bulk_पढ़ो(touch->i2c, MEAS_TSIX_1, MEAS_LEN, buf);
	अगर (ret < 0)
		जाओ out;

	pen_करोwn = buf[1] & (1 << 6);
	x = ((buf[0] & 0xFF) << 4) | (buf[1] & 0x0F);
	y = ((buf[2] & 0xFF) << 4) | (buf[3] & 0x0F);
	z1 = ((buf[4] & 0xFF) << 4) | (buf[5] & 0x0F);
	z2 = ((buf[6] & 0xFF) << 4) | (buf[7] & 0x0F);

	अगर (pen_करोwn) अणु
		अगर ((x != 0) && (z1 != 0) && (touch->res_x != 0)) अणु
			rt = z2 / z1 - 1;
			rt = (rt * touch->res_x * x) >> ACCURATE_BIT;
			dev_dbg(chip->dev, "z1:%d, z2:%d, rt:%d\n",
				z1, z2, rt);
		पूर्ण
		input_report_असल(touch->idev, ABS_X, x);
		input_report_असल(touch->idev, ABS_Y, y);
		input_report_असल(touch->idev, ABS_PRESSURE, rt);
		input_report_key(touch->idev, BTN_TOUCH, 1);
		dev_dbg(chip->dev, "pen down at [%d, %d].\n", x, y);
	पूर्ण अन्यथा अणु
		input_report_असल(touch->idev, ABS_PRESSURE, 0);
		input_report_key(touch->idev, BTN_TOUCH, 0);
		dev_dbg(chip->dev, "pen release\n");
	पूर्ण
	input_sync(touch->idev);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pm860x_touch_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा pm860x_touch *touch = input_get_drvdata(dev);
	पूर्णांक data, ret;

	data = MEAS_PD_EN | MEAS_TSIX_EN | MEAS_TSIY_EN
		| MEAS_TSIZ1_EN | MEAS_TSIZ2_EN;
	ret = pm860x_set_bits(touch->i2c, MEAS_EN3, data, data);
	अगर (ret < 0)
		जाओ out;
	वापस 0;
out:
	वापस ret;
पूर्ण

अटल व्योम pm860x_touch_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pm860x_touch *touch = input_get_drvdata(dev);
	पूर्णांक data;

	data = MEAS_PD_EN | MEAS_TSIX_EN | MEAS_TSIY_EN
		| MEAS_TSIZ1_EN | MEAS_TSIZ2_EN;
	pm860x_set_bits(touch->i2c, MEAS_EN3, data, 0);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक pm860x_touch_dt_init(काष्ठा platक्रमm_device *pdev,
					  काष्ठा pm860x_chip *chip,
					  पूर्णांक *res_x)
अणु
	काष्ठा device_node *np = pdev->dev.parent->of_node;
	काष्ठा i2c_client *i2c = (chip->id == CHIP_PM8607) ? chip->client \
				 : chip->companion;
	पूर्णांक data, n, ret;
	अगर (!np)
		वापस -ENODEV;
	np = of_get_child_by_name(np, "touch");
	अगर (!np) अणु
		dev_err(&pdev->dev, "Can't find touch node\n");
		वापस -EINVAL;
	पूर्ण
	/* set GPADC MISC1 रेजिस्टर */
	data = 0;
	अगर (!of_property_पढ़ो_u32(np, "marvell,88pm860x-gpadc-prebias", &n))
		data |= (n << 1) & PM8607_GPADC_PREBIAS_MASK;
	अगर (!of_property_पढ़ो_u32(np, "marvell,88pm860x-gpadc-slot-cycle", &n))
		data |= (n << 3) & PM8607_GPADC_SLOT_CYCLE_MASK;
	अगर (!of_property_पढ़ो_u32(np, "marvell,88pm860x-gpadc-off-scale", &n))
		data |= (n << 5) & PM8607_GPADC_OFF_SCALE_MASK;
	अगर (!of_property_पढ़ो_u32(np, "marvell,88pm860x-gpadc-sw-cal", &n))
		data |= (n << 7) & PM8607_GPADC_SW_CAL_MASK;
	अगर (data) अणु
		ret = pm860x_reg_ग_लिखो(i2c, PM8607_GPADC_MISC1, data);
		अगर (ret < 0)
			जाओ err_put_node;
	पूर्ण
	/* set tsi prebias समय */
	अगर (!of_property_पढ़ो_u32(np, "marvell,88pm860x-tsi-prebias", &data)) अणु
		ret = pm860x_reg_ग_लिखो(i2c, PM8607_TSI_PREBIAS, data);
		अगर (ret < 0)
			जाओ err_put_node;
	पूर्ण
	/* set prebias & prechg समय of pen detect */
	data = 0;
	अगर (!of_property_पढ़ो_u32(np, "marvell,88pm860x-pen-prebias", &n))
		data |= n & PM8607_PD_PREBIAS_MASK;
	अगर (!of_property_पढ़ो_u32(np, "marvell,88pm860x-pen-prechg", &n))
		data |= n & PM8607_PD_PRECHG_MASK;
	अगर (data) अणु
		ret = pm860x_reg_ग_लिखो(i2c, PM8607_PD_PREBIAS, data);
		अगर (ret < 0)
			जाओ err_put_node;
	पूर्ण
	of_property_पढ़ो_u32(np, "marvell,88pm860x-resistor-X", res_x);

	of_node_put(np);

	वापस 0;

err_put_node:
	of_node_put(np);

	वापस -EINVAL;
पूर्ण
#अन्यथा
#घोषणा pm860x_touch_dt_init(x, y, z)	(-1)
#पूर्ण_अगर

अटल पूर्णांक pm860x_touch_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm860x_touch_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा pm860x_touch *touch;
	काष्ठा i2c_client *i2c = (chip->id == CHIP_PM8607) ? chip->client \
				 : chip->companion;
	पूर्णांक irq, ret, res_x = 0, data = 0;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	अगर (pm860x_touch_dt_init(pdev, chip, &res_x)) अणु
		अगर (pdata) अणु
			/* set GPADC MISC1 रेजिस्टर */
			data = 0;
			data |= (pdata->gpadc_prebias << 1)
				& PM8607_GPADC_PREBIAS_MASK;
			data |= (pdata->slot_cycle << 3)
				& PM8607_GPADC_SLOT_CYCLE_MASK;
			data |= (pdata->off_scale << 5)
				& PM8607_GPADC_OFF_SCALE_MASK;
			data |= (pdata->sw_cal << 7)
				& PM8607_GPADC_SW_CAL_MASK;
			अगर (data) अणु
				ret = pm860x_reg_ग_लिखो(i2c,
					PM8607_GPADC_MISC1, data);
				अगर (ret < 0)
					वापस -EINVAL;
			पूर्ण
			/* set tsi prebias समय */
			अगर (pdata->tsi_prebias) अणु
				data = pdata->tsi_prebias;
				ret = pm860x_reg_ग_लिखो(i2c,
					PM8607_TSI_PREBIAS, data);
				अगर (ret < 0)
					वापस -EINVAL;
			पूर्ण
			/* set prebias & prechg समय of pen detect */
			data = 0;
			data |= pdata->pen_prebias
				& PM8607_PD_PREBIAS_MASK;
			data |= (pdata->pen_prechg << 5)
				& PM8607_PD_PRECHG_MASK;
			अगर (data) अणु
				ret = pm860x_reg_ग_लिखो(i2c,
					PM8607_PD_PREBIAS, data);
				अगर (ret < 0)
					वापस -EINVAL;
			पूर्ण
			res_x = pdata->res_x;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "failed to get platform data\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* enable GPADC */
	ret = pm860x_set_bits(i2c, PM8607_GPADC_MISC1, PM8607_GPADC_EN,
			      PM8607_GPADC_EN);
	अगर (ret)
		वापस ret;

	touch = devm_kzalloc(&pdev->dev, माप(काष्ठा pm860x_touch),
			     GFP_KERNEL);
	अगर (!touch)
		वापस -ENOMEM;

	touch->idev = devm_input_allocate_device(&pdev->dev);
	अगर (!touch->idev) अणु
		dev_err(&pdev->dev, "Failed to allocate input device!\n");
		वापस -ENOMEM;
	पूर्ण

	touch->idev->name = "88pm860x-touch";
	touch->idev->phys = "88pm860x/input0";
	touch->idev->id.bustype = BUS_I2C;
	touch->idev->dev.parent = &pdev->dev;
	touch->idev->खोलो = pm860x_touch_खोलो;
	touch->idev->बंद = pm860x_touch_बंद;
	touch->chip = chip;
	touch->i2c = i2c;
	touch->irq = irq;
	touch->res_x = res_x;
	input_set_drvdata(touch->idev, touch);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, touch->irq, शून्य,
					pm860x_touch_handler, IRQF_ONESHOT,
					"touch", touch);
	अगर (ret < 0)
		वापस ret;

	__set_bit(EV_ABS, touch->idev->evbit);
	__set_bit(ABS_X, touch->idev->असलbit);
	__set_bit(ABS_Y, touch->idev->असलbit);
	__set_bit(ABS_PRESSURE, touch->idev->असलbit);
	__set_bit(EV_SYN, touch->idev->evbit);
	__set_bit(EV_KEY, touch->idev->evbit);
	__set_bit(BTN_TOUCH, touch->idev->keybit);

	input_set_असल_params(touch->idev, ABS_X, 0, 1 << ACCURATE_BIT, 0, 0);
	input_set_असल_params(touch->idev, ABS_Y, 0, 1 << ACCURATE_BIT, 0, 0);
	input_set_असल_params(touch->idev, ABS_PRESSURE, 0, 1 << ACCURATE_BIT,
				0, 0);

	ret = input_रेजिस्टर_device(touch->idev);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to register touch!\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm860x_touch_driver = अणु
	.driver	= अणु
		.name	= "88pm860x-touch",
	पूर्ण,
	.probe	= pm860x_touch_probe,
पूर्ण;
module_platक्रमm_driver(pm860x_touch_driver);

MODULE_DESCRIPTION("Touchscreen driver for Marvell Semiconductor 88PM860x");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:88pm860x-touch");

