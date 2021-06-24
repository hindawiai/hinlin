<शैली गुरु>
/*
 * Texas Instruments' TPS65217 and TPS65218 Power Button Input Driver
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 * Author: Felipe Balbi <balbi@ti.com>
 * Author: Marcin Niestroj <m.niestroj@grinn-global.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/tps65217.h>
#समावेश <linux/mfd/tps65218.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

काष्ठा tps6521x_data अणु
	अचिन्हित पूर्णांक reg_status;
	अचिन्हित पूर्णांक pb_mask;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा tps6521x_data tps65217_data = अणु
	.reg_status = TPS65217_REG_STATUS,
	.pb_mask = TPS65217_STATUS_PB,
	.name = "tps65217_pwrbutton",
पूर्ण;

अटल स्थिर काष्ठा tps6521x_data tps65218_data = अणु
	.reg_status = TPS65218_REG_STATUS,
	.pb_mask = TPS65218_STATUS_PB_STATE,
	.name = "tps65218_pwrbutton",
पूर्ण;

काष्ठा tps6521x_pwrbutton अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा input_dev *idev;
	स्थिर काष्ठा tps6521x_data *data;
	अक्षर phys[32];
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_tps6521x_pb_match[] = अणु
	अणु .compatible = "ti,tps65217-pwrbutton", .data = &tps65217_data पूर्ण,
	अणु .compatible = "ti,tps65218-pwrbutton", .data = &tps65218_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_tps6521x_pb_match);

अटल irqवापस_t tps6521x_pb_irq(पूर्णांक irq, व्योम *_pwr)
अणु
	काष्ठा tps6521x_pwrbutton *pwr = _pwr;
	स्थिर काष्ठा tps6521x_data *tps_data = pwr->data;
	अचिन्हित पूर्णांक reg;
	पूर्णांक error;

	error = regmap_पढ़ो(pwr->regmap, tps_data->reg_status, &reg);
	अगर (error) अणु
		dev_err(pwr->dev, "can't read register: %d\n", error);
		जाओ out;
	पूर्ण

	अगर (reg & tps_data->pb_mask) अणु
		input_report_key(pwr->idev, KEY_POWER, 1);
		pm_wakeup_event(pwr->dev, 0);
	पूर्ण अन्यथा अणु
		input_report_key(pwr->idev, KEY_POWER, 0);
	पूर्ण

	input_sync(pwr->idev);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tps6521x_pb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tps6521x_pwrbutton *pwr;
	काष्ठा input_dev *idev;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक error;
	पूर्णांक irq;

	match = of_match_node(of_tps6521x_pb_match, dev->of_node);
	अगर (!match)
		वापस -ENXIO;

	pwr = devm_kzalloc(dev, माप(*pwr), GFP_KERNEL);
	अगर (!pwr)
		वापस -ENOMEM;

	pwr->data = match->data;

	idev = devm_input_allocate_device(dev);
	अगर (!idev)
		वापस -ENOMEM;

	idev->name = pwr->data->name;
	snम_लिखो(pwr->phys, माप(pwr->phys), "%s/input0",
		pwr->data->name);
	idev->phys = pwr->phys;
	idev->dev.parent = dev;
	idev->id.bustype = BUS_I2C;

	input_set_capability(idev, EV_KEY, KEY_POWER);

	pwr->regmap = dev_get_regmap(dev->parent, शून्य);
	pwr->dev = dev;
	pwr->idev = idev;
	device_init_wakeup(dev, true);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	error = devm_request_thपढ़ोed_irq(dev, irq, शून्य, tps6521x_pb_irq,
					  IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
					  pwr->data->name, pwr);
	अगर (error) अणु
		dev_err(dev, "failed to request IRQ #%d: %d\n", irq, error);
		वापस error;
	पूर्ण

	error= input_रेजिस्टर_device(idev);
	अगर (error) अणु
		dev_err(dev, "Can't register power button: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id tps6521x_pwrbtn_id_table[] = अणु
	अणु "tps65218-pwrbutton", पूर्ण,
	अणु "tps65217-pwrbutton", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, tps6521x_pwrbtn_id_table);

अटल काष्ठा platक्रमm_driver tps6521x_pb_driver = अणु
	.probe	= tps6521x_pb_probe,
	.driver	= अणु
		.name	= "tps6521x_pwrbutton",
		.of_match_table = of_tps6521x_pb_match,
	पूर्ण,
	.id_table = tps6521x_pwrbtn_id_table,
पूर्ण;
module_platक्रमm_driver(tps6521x_pb_driver);

MODULE_DESCRIPTION("TPS6521X Power Button");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
