<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// wm831x-lकरो.c  --  LDO driver क्रम the WM831x series
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

#घोषणा WM831X_LDO_MAX_NAME 9

#घोषणा WM831X_LDO_CONTROL       0
#घोषणा WM831X_LDO_ON_CONTROL    1
#घोषणा WM831X_LDO_SLEEP_CONTROL 2

#घोषणा WM831X_ALIVE_LDO_ON_CONTROL    0
#घोषणा WM831X_ALIVE_LDO_SLEEP_CONTROL 1

काष्ठा wm831x_lकरो अणु
	अक्षर name[WM831X_LDO_MAX_NAME];
	अक्षर supply_name[WM831X_LDO_MAX_NAME];
	काष्ठा regulator_desc desc;
	पूर्णांक base;
	काष्ठा wm831x *wm831x;
	काष्ठा regulator_dev *regulator;
पूर्ण;

/*
 * Shared
 */

अटल irqवापस_t wm831x_lकरो_uv_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_lकरो *lकरो = data;

	regulator_notअगरier_call_chain(lकरो->regulator,
				      REGULATOR_EVENT_UNDER_VOLTAGE,
				      शून्य);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * General purpose LDOs
 */

अटल स्थिर काष्ठा linear_range wm831x_gp_lकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0, 14, 50000),
	REGULATOR_LINEAR_RANGE(1700000, 15, 31, 100000),
पूर्ण;

अटल पूर्णांक wm831x_gp_lकरो_set_suspend_voltage(काष्ठा regulator_dev *rdev,
					     पूर्णांक uV)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक sel, reg = lकरो->base + WM831X_LDO_SLEEP_CONTROL;

	sel = regulator_map_voltage_linear_range(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	वापस wm831x_set_bits(wm831x, reg, WM831X_LDO1_ON_VSEL_MASK, sel);
पूर्ण

अटल अचिन्हित पूर्णांक wm831x_gp_lकरो_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक ctrl_reg = lकरो->base + WM831X_LDO_CONTROL;
	पूर्णांक on_reg = lकरो->base + WM831X_LDO_ON_CONTROL;
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, on_reg);
	अगर (ret < 0)
		वापस ret;

	अगर (!(ret & WM831X_LDO1_ON_MODE))
		वापस REGULATOR_MODE_NORMAL;

	ret = wm831x_reg_पढ़ो(wm831x, ctrl_reg);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & WM831X_LDO1_LP_MODE)
		वापस REGULATOR_MODE_STANDBY;
	अन्यथा
		वापस REGULATOR_MODE_IDLE;
पूर्ण

अटल पूर्णांक wm831x_gp_lकरो_set_mode(काष्ठा regulator_dev *rdev,
				  अचिन्हित पूर्णांक mode)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक ctrl_reg = lकरो->base + WM831X_LDO_CONTROL;
	पूर्णांक on_reg = lकरो->base + WM831X_LDO_ON_CONTROL;
	पूर्णांक ret;


	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		ret = wm831x_set_bits(wm831x, on_reg,
				      WM831X_LDO1_ON_MODE, 0);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	हाल REGULATOR_MODE_IDLE:
		ret = wm831x_set_bits(wm831x, ctrl_reg,
				      WM831X_LDO1_LP_MODE, 0);
		अगर (ret < 0)
			वापस ret;

		ret = wm831x_set_bits(wm831x, on_reg,
				      WM831X_LDO1_ON_MODE,
				      WM831X_LDO1_ON_MODE);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	हाल REGULATOR_MODE_STANDBY:
		ret = wm831x_set_bits(wm831x, ctrl_reg,
				      WM831X_LDO1_LP_MODE,
				      WM831X_LDO1_LP_MODE);
		अगर (ret < 0)
			वापस ret;

		ret = wm831x_set_bits(wm831x, on_reg,
				      WM831X_LDO1_ON_MODE,
				      WM831X_LDO1_ON_MODE);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_gp_lकरो_get_status(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक mask = 1 << rdev_get_id(rdev);
	पूर्णांक ret;

	/* Is the regulator on? */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_LDO_STATUS);
	अगर (ret < 0)
		वापस ret;
	अगर (!(ret & mask))
		वापस REGULATOR_STATUS_OFF;

	/* Is it reporting under voltage? */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_LDO_UV_STATUS);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & mask)
		वापस REGULATOR_STATUS_ERROR;

	ret = wm831x_gp_lकरो_get_mode(rdev);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस regulator_mode_to_status(ret);
पूर्ण

अटल अचिन्हित पूर्णांक wm831x_gp_lकरो_get_optimum_mode(काष्ठा regulator_dev *rdev,
						   पूर्णांक input_uV,
						   पूर्णांक output_uV, पूर्णांक load_uA)
अणु
	अगर (load_uA < 20000)
		वापस REGULATOR_MODE_STANDBY;
	अगर (load_uA < 50000)
		वापस REGULATOR_MODE_IDLE;
	वापस REGULATOR_MODE_NORMAL;
पूर्ण


अटल स्थिर काष्ठा regulator_ops wm831x_gp_lकरो_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.set_suspend_voltage = wm831x_gp_lकरो_set_suspend_voltage,
	.get_mode = wm831x_gp_lकरो_get_mode,
	.set_mode = wm831x_gp_lकरो_set_mode,
	.get_status = wm831x_gp_lकरो_get_status,
	.get_optimum_mode = wm831x_gp_lकरो_get_optimum_mode,
	.get_bypass = regulator_get_bypass_regmap,
	.set_bypass = regulator_set_bypass_regmap,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल पूर्णांक wm831x_gp_lकरो_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक id;
	काष्ठा wm831x_lकरो *lकरो;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	अगर (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	अन्यथा
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Probing LDO%d\n", id + 1);

	lकरो = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_lकरो), GFP_KERNEL);
	अगर (!lकरो)
		वापस -ENOMEM;

	lकरो->wm831x = wm831x;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "No REG resource\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	lकरो->base = res->start;

	snम_लिखो(lकरो->name, माप(lकरो->name), "LDO%d", id + 1);
	lकरो->desc.name = lकरो->name;

	snम_लिखो(lकरो->supply_name, माप(lकरो->supply_name),
		 "LDO%dVDD", id + 1);
	lकरो->desc.supply_name = lकरो->supply_name;

	lकरो->desc.id = id;
	lकरो->desc.type = REGULATOR_VOLTAGE;
	lकरो->desc.n_voltages = 32;
	lकरो->desc.ops = &wm831x_gp_lकरो_ops;
	lकरो->desc.owner = THIS_MODULE;
	lकरो->desc.vsel_reg = lकरो->base + WM831X_LDO_ON_CONTROL;
	lकरो->desc.vsel_mask = WM831X_LDO1_ON_VSEL_MASK;
	lकरो->desc.enable_reg = WM831X_LDO_ENABLE;
	lकरो->desc.enable_mask = 1 << id;
	lकरो->desc.bypass_reg = lकरो->base;
	lकरो->desc.bypass_mask = WM831X_LDO1_SWI;
	lकरो->desc.linear_ranges = wm831x_gp_lकरो_ranges;
	lकरो->desc.n_linear_ranges = ARRAY_SIZE(wm831x_gp_lकरो_ranges);

	config.dev = pdev->dev.parent;
	अगर (pdata)
		config.init_data = pdata->lकरो[id];
	config.driver_data = lकरो;
	config.regmap = wm831x->regmap;

	lकरो->regulator = devm_regulator_रेजिस्टर(&pdev->dev, &lकरो->desc,
						 &config);
	अगर (IS_ERR(lकरो->regulator)) अणु
		ret = PTR_ERR(lकरो->regulator);
		dev_err(wm831x->dev, "Failed to register LDO%d: %d\n",
			id + 1, ret);
		जाओ err;
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "UV"));
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					wm831x_lकरो_uv_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					lकरो->name,
					lकरो);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request UV IRQ %d: %d\n",
			irq, ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lकरो);

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_gp_lकरो_driver = अणु
	.probe = wm831x_gp_lकरो_probe,
	.driver		= अणु
		.name	= "wm831x-ldo",
	पूर्ण,
पूर्ण;

/*
 * Analogue LDOs
 */

अटल स्थिर काष्ठा linear_range wm831x_alकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1000000, 0, 12, 50000),
	REGULATOR_LINEAR_RANGE(1700000, 13, 31, 100000),
पूर्ण;

अटल पूर्णांक wm831x_alकरो_set_suspend_voltage(काष्ठा regulator_dev *rdev,
					     पूर्णांक uV)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक sel, reg = lकरो->base + WM831X_LDO_SLEEP_CONTROL;

	sel = regulator_map_voltage_linear_range(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	वापस wm831x_set_bits(wm831x, reg, WM831X_LDO7_ON_VSEL_MASK, sel);
पूर्ण

अटल अचिन्हित पूर्णांक wm831x_alकरो_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक on_reg = lकरो->base + WM831X_LDO_ON_CONTROL;
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, on_reg);
	अगर (ret < 0)
		वापस 0;

	अगर (ret & WM831X_LDO7_ON_MODE)
		वापस REGULATOR_MODE_IDLE;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक wm831x_alकरो_set_mode(काष्ठा regulator_dev *rdev,
				  अचिन्हित पूर्णांक mode)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक on_reg = lकरो->base + WM831X_LDO_ON_CONTROL;
	पूर्णांक ret;


	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		ret = wm831x_set_bits(wm831x, on_reg, WM831X_LDO7_ON_MODE, 0);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	हाल REGULATOR_MODE_IDLE:
		ret = wm831x_set_bits(wm831x, on_reg, WM831X_LDO7_ON_MODE,
				      WM831X_LDO7_ON_MODE);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_alकरो_get_status(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक mask = 1 << rdev_get_id(rdev);
	पूर्णांक ret;

	/* Is the regulator on? */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_LDO_STATUS);
	अगर (ret < 0)
		वापस ret;
	अगर (!(ret & mask))
		वापस REGULATOR_STATUS_OFF;

	/* Is it reporting under voltage? */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_LDO_UV_STATUS);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & mask)
		वापस REGULATOR_STATUS_ERROR;

	ret = wm831x_alकरो_get_mode(rdev);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस regulator_mode_to_status(ret);
पूर्ण

अटल स्थिर काष्ठा regulator_ops wm831x_alकरो_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.set_suspend_voltage = wm831x_alकरो_set_suspend_voltage,
	.get_mode = wm831x_alकरो_get_mode,
	.set_mode = wm831x_alकरो_set_mode,
	.get_status = wm831x_alकरो_get_status,
	.set_bypass = regulator_set_bypass_regmap,
	.get_bypass = regulator_get_bypass_regmap,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल पूर्णांक wm831x_alकरो_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक id;
	काष्ठा wm831x_lकरो *lकरो;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	अगर (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	अन्यथा
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Probing LDO%d\n", id + 1);

	lकरो = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_lकरो), GFP_KERNEL);
	अगर (!lकरो)
		वापस -ENOMEM;

	lकरो->wm831x = wm831x;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "No REG resource\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	lकरो->base = res->start;

	snम_लिखो(lकरो->name, माप(lकरो->name), "LDO%d", id + 1);
	lकरो->desc.name = lकरो->name;

	snम_लिखो(lकरो->supply_name, माप(lकरो->supply_name),
		 "LDO%dVDD", id + 1);
	lकरो->desc.supply_name = lकरो->supply_name;

	lकरो->desc.id = id;
	lकरो->desc.type = REGULATOR_VOLTAGE;
	lकरो->desc.n_voltages = 32;
	lकरो->desc.linear_ranges = wm831x_alकरो_ranges;
	lकरो->desc.n_linear_ranges = ARRAY_SIZE(wm831x_alकरो_ranges);
	lकरो->desc.ops = &wm831x_alकरो_ops;
	lकरो->desc.owner = THIS_MODULE;
	lकरो->desc.vsel_reg = lकरो->base + WM831X_LDO_ON_CONTROL;
	lकरो->desc.vsel_mask = WM831X_LDO7_ON_VSEL_MASK;
	lकरो->desc.enable_reg = WM831X_LDO_ENABLE;
	lकरो->desc.enable_mask = 1 << id;
	lकरो->desc.bypass_reg = lकरो->base;
	lकरो->desc.bypass_mask = WM831X_LDO7_SWI;

	config.dev = pdev->dev.parent;
	अगर (pdata)
		config.init_data = pdata->lकरो[id];
	config.driver_data = lकरो;
	config.regmap = wm831x->regmap;

	lकरो->regulator = devm_regulator_रेजिस्टर(&pdev->dev, &lकरो->desc,
						 &config);
	अगर (IS_ERR(lकरो->regulator)) अणु
		ret = PTR_ERR(lकरो->regulator);
		dev_err(wm831x->dev, "Failed to register LDO%d: %d\n",
			id + 1, ret);
		जाओ err;
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "UV"));
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					wm831x_lकरो_uv_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					lकरो->name, lकरो);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request UV IRQ %d: %d\n",
			irq, ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lकरो);

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_alकरो_driver = अणु
	.probe = wm831x_alकरो_probe,
	.driver		= अणु
		.name	= "wm831x-aldo",
	पूर्ण,
पूर्ण;

/*
 * Alive LDO
 */

#घोषणा WM831X_ALIVE_LDO_MAX_SELECTOR 0xf

अटल पूर्णांक wm831x_alive_lकरो_set_suspend_voltage(काष्ठा regulator_dev *rdev,
					     पूर्णांक uV)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक sel, reg = lकरो->base + WM831X_ALIVE_LDO_SLEEP_CONTROL;

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	वापस wm831x_set_bits(wm831x, reg, WM831X_LDO11_ON_VSEL_MASK, sel);
पूर्ण

अटल पूर्णांक wm831x_alive_lकरो_get_status(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_lकरो *lकरो = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = lकरो->wm831x;
	पूर्णांक mask = 1 << rdev_get_id(rdev);
	पूर्णांक ret;

	/* Is the regulator on? */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_LDO_STATUS);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & mask)
		वापस REGULATOR_STATUS_ON;
	अन्यथा
		वापस REGULATOR_STATUS_OFF;
पूर्ण

अटल स्थिर काष्ठा regulator_ops wm831x_alive_lकरो_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.set_suspend_voltage = wm831x_alive_lकरो_set_suspend_voltage,
	.get_status = wm831x_alive_lकरो_get_status,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल पूर्णांक wm831x_alive_lकरो_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक id;
	काष्ठा wm831x_lकरो *lकरो;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	अन्यथा
		id = 0;
	id = pdev->id - id;


	dev_dbg(&pdev->dev, "Probing LDO%d\n", id + 1);

	lकरो = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_lकरो), GFP_KERNEL);
	अगर (!lकरो)
		वापस -ENOMEM;

	lकरो->wm831x = wm831x;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "No REG resource\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	lकरो->base = res->start;

	snम_लिखो(lकरो->name, माप(lकरो->name), "LDO%d", id + 1);
	lकरो->desc.name = lकरो->name;

	snम_लिखो(lकरो->supply_name, माप(lकरो->supply_name),
		 "LDO%dVDD", id + 1);
	lकरो->desc.supply_name = lकरो->supply_name;

	lकरो->desc.id = id;
	lकरो->desc.type = REGULATOR_VOLTAGE;
	lकरो->desc.n_voltages = WM831X_ALIVE_LDO_MAX_SELECTOR + 1;
	lकरो->desc.ops = &wm831x_alive_lकरो_ops;
	lकरो->desc.owner = THIS_MODULE;
	lकरो->desc.vsel_reg = lकरो->base + WM831X_ALIVE_LDO_ON_CONTROL;
	lकरो->desc.vsel_mask = WM831X_LDO11_ON_VSEL_MASK;
	lकरो->desc.enable_reg = WM831X_LDO_ENABLE;
	lकरो->desc.enable_mask = 1 << id;
	lकरो->desc.min_uV = 800000;
	lकरो->desc.uV_step = 50000;
	lकरो->desc.enable_समय = 1000;

	config.dev = pdev->dev.parent;
	अगर (pdata)
		config.init_data = pdata->lकरो[id];
	config.driver_data = lकरो;
	config.regmap = wm831x->regmap;

	lकरो->regulator = devm_regulator_रेजिस्टर(&pdev->dev, &lकरो->desc,
						 &config);
	अगर (IS_ERR(lकरो->regulator)) अणु
		ret = PTR_ERR(lकरो->regulator);
		dev_err(wm831x->dev, "Failed to register LDO%d: %d\n",
			id + 1, ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lकरो);

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_alive_lकरो_driver = अणु
	.probe = wm831x_alive_lकरो_probe,
	.driver		= अणु
		.name	= "wm831x-alive-ldo",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&wm831x_gp_lकरो_driver,
	&wm831x_alकरो_driver,
	&wm831x_alive_lकरो_driver,
पूर्ण;

अटल पूर्णांक __init wm831x_lकरो_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
subsys_initcall(wm831x_lकरो_init);

अटल व्योम __निकास wm831x_lकरो_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(wm831x_lकरो_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM831x LDO driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-ldo");
MODULE_ALIAS("platform:wm831x-aldo");
MODULE_ALIAS("platform:wm831x-aliveldo");
