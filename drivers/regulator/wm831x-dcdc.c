<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// wm831x-dcdc.c  --  DC-DC buck converter driver क्रम the WM831x series
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
#समावेश <linux/regulator/machine.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/regulator.h>
#समावेश <linux/mfd/wm831x/pdata.h>

#घोषणा WM831X_BUCKV_MAX_SELECTOR 0x68
#घोषणा WM831X_BUCKP_MAX_SELECTOR 0x66

#घोषणा WM831X_DCDC_MODE_FAST    0
#घोषणा WM831X_DCDC_MODE_NORMAL  1
#घोषणा WM831X_DCDC_MODE_IDLE    2
#घोषणा WM831X_DCDC_MODE_STANDBY 3

#घोषणा WM831X_DCDC_MAX_NAME 9

/* Register offsets in control block */
#घोषणा WM831X_DCDC_CONTROL_1     0
#घोषणा WM831X_DCDC_CONTROL_2     1
#घोषणा WM831X_DCDC_ON_CONFIG     2
#घोषणा WM831X_DCDC_SLEEP_CONTROL 3
#घोषणा WM831X_DCDC_DVS_CONTROL   4

/*
 * Shared
 */

काष्ठा wm831x_dcdc अणु
	अक्षर name[WM831X_DCDC_MAX_NAME];
	अक्षर supply_name[WM831X_DCDC_MAX_NAME];
	काष्ठा regulator_desc desc;
	पूर्णांक base;
	काष्ठा wm831x *wm831x;
	काष्ठा regulator_dev *regulator;
	काष्ठा gpio_desc *dvs_gpiod;
	पूर्णांक dvs_gpio_state;
	पूर्णांक on_vsel;
	पूर्णांक dvs_vsel;
पूर्ण;

अटल अचिन्हित पूर्णांक wm831x_dcdc_get_mode(काष्ठा regulator_dev *rdev)

अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	u16 reg = dcdc->base + WM831X_DCDC_ON_CONFIG;
	पूर्णांक val;

	val = wm831x_reg_पढ़ो(wm831x, reg);
	अगर (val < 0)
		वापस val;

	val = (val & WM831X_DC1_ON_MODE_MASK) >> WM831X_DC1_ON_MODE_SHIFT;

	चयन (val) अणु
	हाल WM831X_DCDC_MODE_FAST:
		वापस REGULATOR_MODE_FAST;
	हाल WM831X_DCDC_MODE_NORMAL:
		वापस REGULATOR_MODE_NORMAL;
	हाल WM831X_DCDC_MODE_STANDBY:
		वापस REGULATOR_MODE_STANDBY;
	हाल WM831X_DCDC_MODE_IDLE:
		वापस REGULATOR_MODE_IDLE;
	शेष:
		BUG();
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक wm831x_dcdc_set_mode_पूर्णांक(काष्ठा wm831x *wm831x, पूर्णांक reg,
				    अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = WM831X_DCDC_MODE_FAST;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = WM831X_DCDC_MODE_NORMAL;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = WM831X_DCDC_MODE_STANDBY;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		val = WM831X_DCDC_MODE_IDLE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस wm831x_set_bits(wm831x, reg, WM831X_DC1_ON_MODE_MASK,
			       val << WM831X_DC1_ON_MODE_SHIFT);
पूर्ण

अटल पूर्णांक wm831x_dcdc_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	u16 reg = dcdc->base + WM831X_DCDC_ON_CONFIG;

	वापस wm831x_dcdc_set_mode_पूर्णांक(wm831x, reg, mode);
पूर्ण

अटल पूर्णांक wm831x_dcdc_set_suspend_mode(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक mode)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	u16 reg = dcdc->base + WM831X_DCDC_SLEEP_CONTROL;

	वापस wm831x_dcdc_set_mode_पूर्णांक(wm831x, reg, mode);
पूर्ण

अटल पूर्णांक wm831x_dcdc_get_status(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	पूर्णांक ret;

	/* First, check क्रम errors */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_DCDC_UV_STATUS);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & (1 << rdev_get_id(rdev))) अणु
		dev_dbg(wm831x->dev, "DCDC%d under voltage\n",
			rdev_get_id(rdev) + 1);
		वापस REGULATOR_STATUS_ERROR;
	पूर्ण

	/* DCDC1 and DCDC2 can additionally detect high voltage/current */
	अगर (rdev_get_id(rdev) < 2) अणु
		अगर (ret & (WM831X_DC1_OV_STS << rdev_get_id(rdev))) अणु
			dev_dbg(wm831x->dev, "DCDC%d over voltage\n",
				rdev_get_id(rdev) + 1);
			वापस REGULATOR_STATUS_ERROR;
		पूर्ण

		अगर (ret & (WM831X_DC1_HC_STS << rdev_get_id(rdev))) अणु
			dev_dbg(wm831x->dev, "DCDC%d over current\n",
				rdev_get_id(rdev) + 1);
			वापस REGULATOR_STATUS_ERROR;
		पूर्ण
	पूर्ण

	/* Is the regulator on? */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_DCDC_STATUS);
	अगर (ret < 0)
		वापस ret;
	अगर (!(ret & (1 << rdev_get_id(rdev))))
		वापस REGULATOR_STATUS_OFF;

	/* TODO: When we handle hardware control modes so we can report the
	 * current mode. */
	वापस REGULATOR_STATUS_ON;
पूर्ण

अटल irqवापस_t wm831x_dcdc_uv_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_dcdc *dcdc = data;

	regulator_notअगरier_call_chain(dcdc->regulator,
				      REGULATOR_EVENT_UNDER_VOLTAGE,
				      शून्य);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm831x_dcdc_oc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_dcdc *dcdc = data;

	regulator_notअगरier_call_chain(dcdc->regulator,
				      REGULATOR_EVENT_OVER_CURRENT,
				      शून्य);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * BUCKV specअगरics
 */

अटल स्थिर काष्ठा linear_range wm831x_buckv_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 0x7, 0),
	REGULATOR_LINEAR_RANGE(600000, 0x8, 0x68, 12500),
पूर्ण;

अटल पूर्णांक wm831x_buckv_set_dvs(काष्ठा regulator_dev *rdev, पूर्णांक state)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);

	अगर (state == dcdc->dvs_gpio_state)
		वापस 0;

	dcdc->dvs_gpio_state = state;
	gpiod_set_value(dcdc->dvs_gpiod, state);

	/* Should रुको क्रम DVS state change to be निश्चितed अगर we have
	 * a GPIO क्रम it, क्रम now assume the device is configured
	 * क्रम the fastest possible transition.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_buckv_set_voltage_sel(काष्ठा regulator_dev *rdev,
					अचिन्हित vsel)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	पूर्णांक on_reg = dcdc->base + WM831X_DCDC_ON_CONFIG;
	पूर्णांक dvs_reg = dcdc->base + WM831X_DCDC_DVS_CONTROL;
	पूर्णांक ret;

	/* If this value is alपढ़ोy set then करो a GPIO update अगर we can */
	अगर (dcdc->dvs_gpiod && dcdc->on_vsel == vsel)
		वापस wm831x_buckv_set_dvs(rdev, 0);

	अगर (dcdc->dvs_gpiod && dcdc->dvs_vsel == vsel)
		वापस wm831x_buckv_set_dvs(rdev, 1);

	/* Always set the ON status to the minimum voltage */
	ret = wm831x_set_bits(wm831x, on_reg, WM831X_DC1_ON_VSEL_MASK, vsel);
	अगर (ret < 0)
		वापस ret;
	dcdc->on_vsel = vsel;

	अगर (!dcdc->dvs_gpiod)
		वापस ret;

	/* Kick the voltage transition now */
	ret = wm831x_buckv_set_dvs(rdev, 0);
	अगर (ret < 0)
		वापस ret;

	/*
	 * If this VSEL is higher than the last one we've seen then
	 * remember it as the DVS VSEL.  This is optimised क्रम CPUfreq
	 * usage where we want to get to the highest voltage very
	 * quickly.
	 */
	अगर (vsel > dcdc->dvs_vsel) अणु
		ret = wm831x_set_bits(wm831x, dvs_reg,
				      WM831X_DC1_DVS_VSEL_MASK,
				      vsel);
		अगर (ret == 0)
			dcdc->dvs_vsel = vsel;
		अन्यथा
			dev_warn(wm831x->dev,
				 "Failed to set DCDC DVS VSEL: %d\n", ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_buckv_set_suspend_voltage(काष्ठा regulator_dev *rdev,
					    पूर्णांक uV)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	u16 reg = dcdc->base + WM831X_DCDC_SLEEP_CONTROL;
	पूर्णांक vsel;

	vsel = regulator_map_voltage_linear_range(rdev, uV, uV);
	अगर (vsel < 0)
		वापस vsel;

	वापस wm831x_set_bits(wm831x, reg, WM831X_DC1_SLP_VSEL_MASK, vsel);
पूर्ण

अटल पूर्णांक wm831x_buckv_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);

	अगर (dcdc->dvs_gpiod && dcdc->dvs_gpio_state)
		वापस dcdc->dvs_vsel;
	अन्यथा
		वापस dcdc->on_vsel;
पूर्ण

/* Current limit options */
अटल स्थिर अचिन्हित पूर्णांक wm831x_dcdc_ilim[] = अणु
	125000, 250000, 375000, 500000, 625000, 750000, 875000, 1000000
पूर्ण;

अटल स्थिर काष्ठा regulator_ops wm831x_buckv_ops = अणु
	.set_voltage_sel = wm831x_buckv_set_voltage_sel,
	.get_voltage_sel = wm831x_buckv_get_voltage_sel,
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_suspend_voltage = wm831x_buckv_set_suspend_voltage,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.get_status = wm831x_dcdc_get_status,
	.get_mode = wm831x_dcdc_get_mode,
	.set_mode = wm831x_dcdc_set_mode,
	.set_suspend_mode = wm831x_dcdc_set_suspend_mode,
पूर्ण;

/*
 * Set up DVS control.  We just log errors since we can still run
 * (with reduced perक्रमmance) अगर we fail.
 */
अटल व्योम wm831x_buckv_dvs_init(काष्ठा platक्रमm_device *pdev,
				  काष्ठा wm831x_dcdc *dcdc,
				  काष्ठा wm831x_buckv_pdata *pdata)
अणु
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	पूर्णांक ret;
	u16 ctrl;

	अगर (!pdata)
		वापस;

	/* gpiolib won't let us पढ़ो the GPIO status so pick the higher
	 * of the two existing voltages so we take it as platक्रमm data.
	 */
	dcdc->dvs_gpio_state = pdata->dvs_init_state;

	dcdc->dvs_gpiod = devm_gpiod_get(&pdev->dev, "dvs",
			dcdc->dvs_gpio_state ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW);
	अगर (IS_ERR(dcdc->dvs_gpiod)) अणु
		dev_err(wm831x->dev, "Failed to get %s DVS GPIO: %ld\n",
			dcdc->name, PTR_ERR(dcdc->dvs_gpiod));
		वापस;
	पूर्ण

	चयन (pdata->dvs_control_src) अणु
	हाल 1:
		ctrl = 2 << WM831X_DC1_DVS_SRC_SHIFT;
		अवरोध;
	हाल 2:
		ctrl = 3 << WM831X_DC1_DVS_SRC_SHIFT;
		अवरोध;
	शेष:
		dev_err(wm831x->dev, "Invalid DVS control source %d for %s\n",
			pdata->dvs_control_src, dcdc->name);
		वापस;
	पूर्ण

	/* If DVS_VSEL is set to the minimum value then उठाओ it to ON_VSEL
	 * to make bootstrapping a bit smoother.
	 */
	अगर (!dcdc->dvs_vsel) अणु
		ret = wm831x_set_bits(wm831x,
				      dcdc->base + WM831X_DCDC_DVS_CONTROL,
				      WM831X_DC1_DVS_VSEL_MASK, dcdc->on_vsel);
		अगर (ret == 0)
			dcdc->dvs_vsel = dcdc->on_vsel;
		अन्यथा
			dev_warn(wm831x->dev, "Failed to set DVS_VSEL: %d\n",
				 ret);
	पूर्ण

	ret = wm831x_set_bits(wm831x, dcdc->base + WM831X_DCDC_DVS_CONTROL,
			      WM831X_DC1_DVS_SRC_MASK, ctrl);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to set %s DVS source: %d\n",
			dcdc->name, ret);
	पूर्ण
पूर्ण

अटल पूर्णांक wm831x_buckv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक id;
	काष्ठा wm831x_dcdc *dcdc;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	अगर (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	अन्यथा
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Probing DCDC%d\n", id + 1);

	dcdc = devm_kzalloc(&pdev->dev,  माप(काष्ठा wm831x_dcdc),
			    GFP_KERNEL);
	अगर (!dcdc)
		वापस -ENOMEM;

	dcdc->wm831x = wm831x;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "No REG resource\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	dcdc->base = res->start;

	snम_लिखो(dcdc->name, माप(dcdc->name), "DCDC%d", id + 1);
	dcdc->desc.name = dcdc->name;

	snम_लिखो(dcdc->supply_name, माप(dcdc->supply_name),
		 "DC%dVDD", id + 1);
	dcdc->desc.supply_name = dcdc->supply_name;

	dcdc->desc.id = id;
	dcdc->desc.type = REGULATOR_VOLTAGE;
	dcdc->desc.n_voltages = WM831X_BUCKV_MAX_SELECTOR + 1;
	dcdc->desc.linear_ranges = wm831x_buckv_ranges;
	dcdc->desc.n_linear_ranges = ARRAY_SIZE(wm831x_buckv_ranges);
	dcdc->desc.ops = &wm831x_buckv_ops;
	dcdc->desc.owner = THIS_MODULE;
	dcdc->desc.enable_reg = WM831X_DCDC_ENABLE;
	dcdc->desc.enable_mask = 1 << id;
	dcdc->desc.csel_reg = dcdc->base + WM831X_DCDC_CONTROL_2;
	dcdc->desc.csel_mask = WM831X_DC1_HC_THR_MASK;
	dcdc->desc.n_current_limits = ARRAY_SIZE(wm831x_dcdc_ilim);
	dcdc->desc.curr_table = wm831x_dcdc_ilim;

	ret = wm831x_reg_पढ़ो(wm831x, dcdc->base + WM831X_DCDC_ON_CONFIG);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to read ON VSEL: %d\n", ret);
		जाओ err;
	पूर्ण
	dcdc->on_vsel = ret & WM831X_DC1_ON_VSEL_MASK;

	ret = wm831x_reg_पढ़ो(wm831x, dcdc->base + WM831X_DCDC_DVS_CONTROL);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to read DVS VSEL: %d\n", ret);
		जाओ err;
	पूर्ण
	dcdc->dvs_vsel = ret & WM831X_DC1_DVS_VSEL_MASK;

	अगर (pdata && pdata->dcdc[id])
		wm831x_buckv_dvs_init(pdev, dcdc,
				      pdata->dcdc[id]->driver_data);

	config.dev = pdev->dev.parent;
	अगर (pdata)
		config.init_data = pdata->dcdc[id];
	config.driver_data = dcdc;
	config.regmap = wm831x->regmap;

	dcdc->regulator = devm_regulator_रेजिस्टर(&pdev->dev, &dcdc->desc,
						  &config);
	अगर (IS_ERR(dcdc->regulator)) अणु
		ret = PTR_ERR(dcdc->regulator);
		dev_err(wm831x->dev, "Failed to register DCDC%d: %d\n",
			id + 1, ret);
		जाओ err;
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "UV"));
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					wm831x_dcdc_uv_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dcdc->name, dcdc);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request UV IRQ %d: %d\n",
			irq, ret);
		जाओ err;
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "HC"));
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					wm831x_dcdc_oc_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dcdc->name, dcdc);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request HC IRQ %d: %d\n",
			irq, ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dcdc);

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_buckv_driver = अणु
	.probe = wm831x_buckv_probe,
	.driver		= अणु
		.name	= "wm831x-buckv",
	पूर्ण,
पूर्ण;

/*
 * BUCKP specअगरics
 */

अटल पूर्णांक wm831x_buckp_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	u16 reg = dcdc->base + WM831X_DCDC_SLEEP_CONTROL;
	पूर्णांक sel;

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	वापस wm831x_set_bits(wm831x, reg, WM831X_DC3_ON_VSEL_MASK, sel);
पूर्ण

अटल स्थिर काष्ठा regulator_ops wm831x_buckp_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.set_suspend_voltage = wm831x_buckp_set_suspend_voltage,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.get_status = wm831x_dcdc_get_status,
	.get_mode = wm831x_dcdc_get_mode,
	.set_mode = wm831x_dcdc_set_mode,
	.set_suspend_mode = wm831x_dcdc_set_suspend_mode,
पूर्ण;

अटल पूर्णांक wm831x_buckp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक id;
	काष्ठा wm831x_dcdc *dcdc;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	अगर (pdata && pdata->wm831x_num)
		id = (pdata->wm831x_num * 10) + 1;
	अन्यथा
		id = 0;
	id = pdev->id - id;

	dev_dbg(&pdev->dev, "Probing DCDC%d\n", id + 1);

	dcdc = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_dcdc),
			    GFP_KERNEL);
	अगर (!dcdc)
		वापस -ENOMEM;

	dcdc->wm831x = wm831x;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "No REG resource\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	dcdc->base = res->start;

	snम_लिखो(dcdc->name, माप(dcdc->name), "DCDC%d", id + 1);
	dcdc->desc.name = dcdc->name;

	snम_लिखो(dcdc->supply_name, माप(dcdc->supply_name),
		 "DC%dVDD", id + 1);
	dcdc->desc.supply_name = dcdc->supply_name;

	dcdc->desc.id = id;
	dcdc->desc.type = REGULATOR_VOLTAGE;
	dcdc->desc.n_voltages = WM831X_BUCKP_MAX_SELECTOR + 1;
	dcdc->desc.ops = &wm831x_buckp_ops;
	dcdc->desc.owner = THIS_MODULE;
	dcdc->desc.vsel_reg = dcdc->base + WM831X_DCDC_ON_CONFIG;
	dcdc->desc.vsel_mask = WM831X_DC3_ON_VSEL_MASK;
	dcdc->desc.enable_reg = WM831X_DCDC_ENABLE;
	dcdc->desc.enable_mask = 1 << id;
	dcdc->desc.min_uV = 850000;
	dcdc->desc.uV_step = 25000;

	config.dev = pdev->dev.parent;
	अगर (pdata)
		config.init_data = pdata->dcdc[id];
	config.driver_data = dcdc;
	config.regmap = wm831x->regmap;

	dcdc->regulator = devm_regulator_रेजिस्टर(&pdev->dev, &dcdc->desc,
						  &config);
	अगर (IS_ERR(dcdc->regulator)) अणु
		ret = PTR_ERR(dcdc->regulator);
		dev_err(wm831x->dev, "Failed to register DCDC%d: %d\n",
			id + 1, ret);
		जाओ err;
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "UV"));
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					wm831x_dcdc_uv_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dcdc->name, dcdc);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request UV IRQ %d: %d\n",
			irq, ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dcdc);

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_buckp_driver = अणु
	.probe = wm831x_buckp_probe,
	.driver		= अणु
		.name	= "wm831x-buckp",
	पूर्ण,
पूर्ण;

/*
 * DCDC boost convertors
 */

अटल पूर्णांक wm831x_boostp_get_status(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm831x_dcdc *dcdc = rdev_get_drvdata(rdev);
	काष्ठा wm831x *wm831x = dcdc->wm831x;
	पूर्णांक ret;

	/* First, check क्रम errors */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_DCDC_UV_STATUS);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & (1 << rdev_get_id(rdev))) अणु
		dev_dbg(wm831x->dev, "DCDC%d under voltage\n",
			rdev_get_id(rdev) + 1);
		वापस REGULATOR_STATUS_ERROR;
	पूर्ण

	/* Is the regulator on? */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_DCDC_STATUS);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & (1 << rdev_get_id(rdev)))
		वापस REGULATOR_STATUS_ON;
	अन्यथा
		वापस REGULATOR_STATUS_OFF;
पूर्ण

अटल स्थिर काष्ठा regulator_ops wm831x_boostp_ops = अणु
	.get_status = wm831x_boostp_get_status,

	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल पूर्णांक wm831x_boostp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक id = pdev->id % ARRAY_SIZE(pdata->dcdc);
	काष्ठा wm831x_dcdc *dcdc;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	dev_dbg(&pdev->dev, "Probing DCDC%d\n", id + 1);

	अगर (pdata == शून्य || pdata->dcdc[id] == शून्य)
		वापस -ENODEV;

	dcdc = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_dcdc), GFP_KERNEL);
	अगर (!dcdc)
		वापस -ENOMEM;

	dcdc->wm831x = wm831x;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "No REG resource\n");
		वापस -EINVAL;
	पूर्ण
	dcdc->base = res->start;

	snम_लिखो(dcdc->name, माप(dcdc->name), "DCDC%d", id + 1);
	dcdc->desc.name = dcdc->name;
	dcdc->desc.id = id;
	dcdc->desc.type = REGULATOR_VOLTAGE;
	dcdc->desc.ops = &wm831x_boostp_ops;
	dcdc->desc.owner = THIS_MODULE;
	dcdc->desc.enable_reg = WM831X_DCDC_ENABLE;
	dcdc->desc.enable_mask = 1 << id;

	config.dev = pdev->dev.parent;
	अगर (pdata)
		config.init_data = pdata->dcdc[id];
	config.driver_data = dcdc;
	config.regmap = wm831x->regmap;

	dcdc->regulator = devm_regulator_रेजिस्टर(&pdev->dev, &dcdc->desc,
						  &config);
	अगर (IS_ERR(dcdc->regulator)) अणु
		ret = PTR_ERR(dcdc->regulator);
		dev_err(wm831x->dev, "Failed to register DCDC%d: %d\n",
			id + 1, ret);
		वापस ret;
	पूर्ण

	irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "UV"));
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					wm831x_dcdc_uv_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dcdc->name,
					dcdc);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request UV IRQ %d: %d\n",
			irq, ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dcdc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_boostp_driver = अणु
	.probe = wm831x_boostp_probe,
	.driver		= अणु
		.name	= "wm831x-boostp",
	पूर्ण,
पूर्ण;

/*
 * External Power Enable
 *
 * These aren't actually DCDCs but look like them in hardware so share
 * code.
 */

#घोषणा WM831X_EPE_BASE 6

अटल स्थिर काष्ठा regulator_ops wm831x_epe_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.get_status = wm831x_dcdc_get_status,
पूर्ण;

अटल पूर्णांक wm831x_epe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(wm831x->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक id = pdev->id % ARRAY_SIZE(pdata->epe);
	काष्ठा wm831x_dcdc *dcdc;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "Probing EPE%d\n", id + 1);

	dcdc = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_dcdc), GFP_KERNEL);
	अगर (!dcdc)
		वापस -ENOMEM;

	dcdc->wm831x = wm831x;

	/* For current parts this is correct; probably need to revisit
	 * in future.
	 */
	snम_लिखो(dcdc->name, माप(dcdc->name), "EPE%d", id + 1);
	dcdc->desc.name = dcdc->name;
	dcdc->desc.id = id + WM831X_EPE_BASE; /* Offset in DCDC रेजिस्टरs */
	dcdc->desc.ops = &wm831x_epe_ops;
	dcdc->desc.type = REGULATOR_VOLTAGE;
	dcdc->desc.owner = THIS_MODULE;
	dcdc->desc.enable_reg = WM831X_DCDC_ENABLE;
	dcdc->desc.enable_mask = 1 << dcdc->desc.id;

	config.dev = pdev->dev.parent;
	अगर (pdata)
		config.init_data = pdata->epe[id];
	config.driver_data = dcdc;
	config.regmap = wm831x->regmap;

	dcdc->regulator = devm_regulator_रेजिस्टर(&pdev->dev, &dcdc->desc,
						  &config);
	अगर (IS_ERR(dcdc->regulator)) अणु
		ret = PTR_ERR(dcdc->regulator);
		dev_err(wm831x->dev, "Failed to register EPE%d: %d\n",
			id + 1, ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dcdc);

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_epe_driver = अणु
	.probe = wm831x_epe_probe,
	.driver		= अणु
		.name	= "wm831x-epe",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&wm831x_buckv_driver,
	&wm831x_buckp_driver,
	&wm831x_boostp_driver,
	&wm831x_epe_driver,
पूर्ण;

अटल पूर्णांक __init wm831x_dcdc_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
subsys_initcall(wm831x_dcdc_init);

अटल व्योम __निकास wm831x_dcdc_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(wm831x_dcdc_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown");
MODULE_DESCRIPTION("WM831x DC-DC convertor driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-buckv");
MODULE_ALIAS("platform:wm831x-buckp");
MODULE_ALIAS("platform:wm831x-boostp");
MODULE_ALIAS("platform:wm831x-epe");
