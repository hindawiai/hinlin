<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - buck regulator driver
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/mfd/lp8788.h>
#समावेश <linux/gpपन.स>

/* रेजिस्टर address */
#घोषणा LP8788_EN_BUCK			0x0C
#घोषणा LP8788_BUCK_DVS_SEL		0x1D
#घोषणा LP8788_BUCK1_VOUT0		0x1E
#घोषणा LP8788_BUCK1_VOUT1		0x1F
#घोषणा LP8788_BUCK1_VOUT2		0x20
#घोषणा LP8788_BUCK1_VOUT3		0x21
#घोषणा LP8788_BUCK2_VOUT0		0x22
#घोषणा LP8788_BUCK2_VOUT1		0x23
#घोषणा LP8788_BUCK2_VOUT2		0x24
#घोषणा LP8788_BUCK2_VOUT3		0x25
#घोषणा LP8788_BUCK3_VOUT		0x26
#घोषणा LP8788_BUCK4_VOUT		0x27
#घोषणा LP8788_BUCK1_TIMESTEP		0x28
#घोषणा LP8788_BUCK_PWM			0x2D

/* mask/shअगरt bits */
#घोषणा LP8788_EN_BUCK1_M		BIT(0)	/* Addr 0Ch */
#घोषणा LP8788_EN_BUCK2_M		BIT(1)
#घोषणा LP8788_EN_BUCK3_M		BIT(2)
#घोषणा LP8788_EN_BUCK4_M		BIT(3)
#घोषणा LP8788_BUCK1_DVS_SEL_M		0x04	/* Addr 1Dh */
#घोषणा LP8788_BUCK1_DVS_M		0x03
#घोषणा LP8788_BUCK1_DVS_S		0
#घोषणा LP8788_BUCK2_DVS_SEL_M		0x40
#घोषणा LP8788_BUCK2_DVS_M		0x30
#घोषणा LP8788_BUCK2_DVS_S		4
#घोषणा LP8788_BUCK1_DVS_I2C		BIT(2)
#घोषणा LP8788_BUCK2_DVS_I2C		BIT(6)
#घोषणा LP8788_BUCK1_DVS_PIN		(0 << 2)
#घोषणा LP8788_BUCK2_DVS_PIN		(0 << 6)
#घोषणा LP8788_VOUT_M			0x1F	/* Addr 1Eh ~ 27h */
#घोषणा LP8788_STARTUP_TIME_M		0xF8	/* Addr 28h ~ 2Bh */
#घोषणा LP8788_STARTUP_TIME_S		3
#घोषणा LP8788_FPWM_BUCK1_M		BIT(0)	/* Addr 2Dh */
#घोषणा LP8788_FPWM_BUCK1_S		0
#घोषणा LP8788_FPWM_BUCK2_M		BIT(1)
#घोषणा LP8788_FPWM_BUCK2_S		1
#घोषणा LP8788_FPWM_BUCK3_M		BIT(2)
#घोषणा LP8788_FPWM_BUCK3_S		2
#घोषणा LP8788_FPWM_BUCK4_M		BIT(3)
#घोषणा LP8788_FPWM_BUCK4_S		3

#घोषणा INVALID_ADDR			0xFF
#घोषणा LP8788_FORCE_PWM		1
#घोषणा LP8788_AUTO_PWM			0
#घोषणा PIN_LOW				0
#घोषणा PIN_HIGH			1
#घोषणा ENABLE_TIME_USEC		32

#घोषणा BUCK_FPWM_MASK(x)		(1 << (x))
#घोषणा BUCK_FPWM_SHIFT(x)		(x)

क्रमागत lp8788_dvs_state अणु
	DVS_LOW  = GPIOF_OUT_INIT_LOW,
	DVS_HIGH = GPIOF_OUT_INIT_HIGH,
पूर्ण;

क्रमागत lp8788_dvs_mode अणु
	REGISTER,
	EXTPIN,
पूर्ण;

क्रमागत lp8788_buck_id अणु
	BUCK1,
	BUCK2,
	BUCK3,
	BUCK4,
पूर्ण;

काष्ठा lp8788_buck अणु
	काष्ठा lp8788 *lp;
	काष्ठा regulator_dev *regulator;
	व्योम *dvs;
पूर्ण;

/* BUCK 1 ~ 4 voltage ranges */
अटल स्थिर काष्ठा linear_range buck_volt_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(500000, 0, 0, 0),
	REGULATOR_LINEAR_RANGE(800000, 1, 25, 50000),
पूर्ण;

अटल व्योम lp8788_buck1_set_dvs(काष्ठा lp8788_buck *buck)
अणु
	काष्ठा lp8788_buck1_dvs *dvs = (काष्ठा lp8788_buck1_dvs *)buck->dvs;
	क्रमागत lp8788_dvs_state pinstate;

	अगर (!dvs)
		वापस;

	pinstate = dvs->vsel == DVS_SEL_V0 ? DVS_LOW : DVS_HIGH;
	अगर (gpio_is_valid(dvs->gpio))
		gpio_set_value(dvs->gpio, pinstate);
पूर्ण

अटल व्योम lp8788_buck2_set_dvs(काष्ठा lp8788_buck *buck)
अणु
	काष्ठा lp8788_buck2_dvs *dvs = (काष्ठा lp8788_buck2_dvs *)buck->dvs;
	क्रमागत lp8788_dvs_state pin1, pin2;

	अगर (!dvs)
		वापस;

	चयन (dvs->vsel) अणु
	हाल DVS_SEL_V0:
		pin1 = DVS_LOW;
		pin2 = DVS_LOW;
		अवरोध;
	हाल DVS_SEL_V1:
		pin1 = DVS_HIGH;
		pin2 = DVS_LOW;
		अवरोध;
	हाल DVS_SEL_V2:
		pin1 = DVS_LOW;
		pin2 = DVS_HIGH;
		अवरोध;
	हाल DVS_SEL_V3:
		pin1 = DVS_HIGH;
		pin2 = DVS_HIGH;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (gpio_is_valid(dvs->gpio[0]))
		gpio_set_value(dvs->gpio[0], pin1);

	अगर (gpio_is_valid(dvs->gpio[1]))
		gpio_set_value(dvs->gpio[1], pin2);
पूर्ण

अटल व्योम lp8788_set_dvs(काष्ठा lp8788_buck *buck, क्रमागत lp8788_buck_id id)
अणु
	चयन (id) अणु
	हाल BUCK1:
		lp8788_buck1_set_dvs(buck);
		अवरोध;
	हाल BUCK2:
		lp8788_buck2_set_dvs(buck);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत lp8788_dvs_mode
lp8788_get_buck_dvs_ctrl_mode(काष्ठा lp8788_buck *buck, क्रमागत lp8788_buck_id id)
अणु
	u8 val, mask;

	चयन (id) अणु
	हाल BUCK1:
		mask = LP8788_BUCK1_DVS_SEL_M;
		अवरोध;
	हाल BUCK2:
		mask = LP8788_BUCK2_DVS_SEL_M;
		अवरोध;
	शेष:
		वापस REGISTER;
	पूर्ण

	lp8788_पढ़ो_byte(buck->lp, LP8788_BUCK_DVS_SEL, &val);

	वापस val & mask ? REGISTER : EXTPIN;
पूर्ण

अटल bool lp8788_is_valid_buck_addr(u8 addr)
अणु
	चयन (addr) अणु
	हाल LP8788_BUCK1_VOUT0:
	हाल LP8788_BUCK1_VOUT1:
	हाल LP8788_BUCK1_VOUT2:
	हाल LP8788_BUCK1_VOUT3:
	हाल LP8788_BUCK2_VOUT0:
	हाल LP8788_BUCK2_VOUT1:
	हाल LP8788_BUCK2_VOUT2:
	हाल LP8788_BUCK2_VOUT3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u8 lp8788_select_buck_vout_addr(काष्ठा lp8788_buck *buck,
					क्रमागत lp8788_buck_id id)
अणु
	क्रमागत lp8788_dvs_mode mode = lp8788_get_buck_dvs_ctrl_mode(buck, id);
	काष्ठा lp8788_buck1_dvs *b1_dvs;
	काष्ठा lp8788_buck2_dvs *b2_dvs;
	u8 val, idx, addr;
	पूर्णांक pin1, pin2;

	चयन (id) अणु
	हाल BUCK1:
		अगर (mode == EXTPIN) अणु
			b1_dvs = (काष्ठा lp8788_buck1_dvs *)buck->dvs;
			अगर (!b1_dvs)
				जाओ err;

			idx = gpio_get_value(b1_dvs->gpio) ? 1 : 0;
		पूर्ण अन्यथा अणु
			lp8788_पढ़ो_byte(buck->lp, LP8788_BUCK_DVS_SEL, &val);
			idx = (val & LP8788_BUCK1_DVS_M) >> LP8788_BUCK1_DVS_S;
		पूर्ण
		addr = LP8788_BUCK1_VOUT0 + idx;
		अवरोध;
	हाल BUCK2:
		अगर (mode == EXTPIN) अणु
			b2_dvs = (काष्ठा lp8788_buck2_dvs *)buck->dvs;
			अगर (!b2_dvs)
				जाओ err;

			pin1 = gpio_get_value(b2_dvs->gpio[0]);
			pin2 = gpio_get_value(b2_dvs->gpio[1]);

			अगर (pin1 == PIN_LOW && pin2 == PIN_LOW)
				idx = 0;
			अन्यथा अगर (pin1 == PIN_LOW && pin2 == PIN_HIGH)
				idx = 2;
			अन्यथा अगर (pin1 == PIN_HIGH && pin2 == PIN_LOW)
				idx = 1;
			अन्यथा
				idx = 3;
		पूर्ण अन्यथा अणु
			lp8788_पढ़ो_byte(buck->lp, LP8788_BUCK_DVS_SEL, &val);
			idx = (val & LP8788_BUCK2_DVS_M) >> LP8788_BUCK2_DVS_S;
		पूर्ण
		addr = LP8788_BUCK2_VOUT0 + idx;
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	वापस addr;
err:
	वापस INVALID_ADDR;
पूर्ण

अटल पूर्णांक lp8788_buck12_set_voltage_sel(काष्ठा regulator_dev *rdev,
					अचिन्हित selector)
अणु
	काष्ठा lp8788_buck *buck = rdev_get_drvdata(rdev);
	क्रमागत lp8788_buck_id id = rdev_get_id(rdev);
	u8 addr;

	अगर (buck->dvs)
		lp8788_set_dvs(buck, id);

	addr = lp8788_select_buck_vout_addr(buck, id);
	अगर (!lp8788_is_valid_buck_addr(addr))
		वापस -EINVAL;

	वापस lp8788_update_bits(buck->lp, addr, LP8788_VOUT_M, selector);
पूर्ण

अटल पूर्णांक lp8788_buck12_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lp8788_buck *buck = rdev_get_drvdata(rdev);
	क्रमागत lp8788_buck_id id = rdev_get_id(rdev);
	पूर्णांक ret;
	u8 val, addr;

	addr = lp8788_select_buck_vout_addr(buck, id);
	अगर (!lp8788_is_valid_buck_addr(addr))
		वापस -EINVAL;

	ret = lp8788_पढ़ो_byte(buck->lp, addr, &val);
	अगर (ret)
		वापस ret;

	वापस val & LP8788_VOUT_M;
पूर्ण

अटल पूर्णांक lp8788_buck_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lp8788_buck *buck = rdev_get_drvdata(rdev);
	क्रमागत lp8788_buck_id id = rdev_get_id(rdev);
	u8 val, addr = LP8788_BUCK1_TIMESTEP + id;

	अगर (lp8788_पढ़ो_byte(buck->lp, addr, &val))
		वापस -EINVAL;

	val = (val & LP8788_STARTUP_TIME_M) >> LP8788_STARTUP_TIME_S;

	वापस ENABLE_TIME_USEC * val;
पूर्ण

अटल पूर्णांक lp8788_buck_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा lp8788_buck *buck = rdev_get_drvdata(rdev);
	क्रमागत lp8788_buck_id id = rdev_get_id(rdev);
	u8 mask, val;

	mask = BUCK_FPWM_MASK(id);
	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = LP8788_FORCE_PWM << BUCK_FPWM_SHIFT(id);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = LP8788_AUTO_PWM << BUCK_FPWM_SHIFT(id);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस lp8788_update_bits(buck->lp, LP8788_BUCK_PWM, mask, val);
पूर्ण

अटल अचिन्हित पूर्णांक lp8788_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lp8788_buck *buck = rdev_get_drvdata(rdev);
	क्रमागत lp8788_buck_id id = rdev_get_id(rdev);
	u8 val;
	पूर्णांक ret;

	ret = lp8788_पढ़ो_byte(buck->lp, LP8788_BUCK_PWM, &val);
	अगर (ret)
		वापस ret;

	वापस val & BUCK_FPWM_MASK(id) ?
				REGULATOR_MODE_FAST : REGULATOR_MODE_NORMAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops lp8788_buck12_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = lp8788_buck12_set_voltage_sel,
	.get_voltage_sel = lp8788_buck12_get_voltage_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.enable_समय = lp8788_buck_enable_समय,
	.set_mode = lp8788_buck_set_mode,
	.get_mode = lp8788_buck_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops lp8788_buck34_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.enable_समय = lp8788_buck_enable_समय,
	.set_mode = lp8788_buck_set_mode,
	.get_mode = lp8788_buck_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc lp8788_buck_desc[] = अणु
	अणु
		.name = "buck1",
		.id = BUCK1,
		.ops = &lp8788_buck12_ops,
		.n_voltages = 26,
		.linear_ranges = buck_volt_ranges,
		.n_linear_ranges = ARRAY_SIZE(buck_volt_ranges),
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_BUCK,
		.enable_mask = LP8788_EN_BUCK1_M,
	पूर्ण,
	अणु
		.name = "buck2",
		.id = BUCK2,
		.ops = &lp8788_buck12_ops,
		.n_voltages = 26,
		.linear_ranges = buck_volt_ranges,
		.n_linear_ranges = ARRAY_SIZE(buck_volt_ranges),
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_BUCK,
		.enable_mask = LP8788_EN_BUCK2_M,
	पूर्ण,
	अणु
		.name = "buck3",
		.id = BUCK3,
		.ops = &lp8788_buck34_ops,
		.n_voltages = 26,
		.linear_ranges = buck_volt_ranges,
		.n_linear_ranges = ARRAY_SIZE(buck_volt_ranges),
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_BUCK3_VOUT,
		.vsel_mask = LP8788_VOUT_M,
		.enable_reg = LP8788_EN_BUCK,
		.enable_mask = LP8788_EN_BUCK3_M,
	पूर्ण,
	अणु
		.name = "buck4",
		.id = BUCK4,
		.ops = &lp8788_buck34_ops,
		.n_voltages = 26,
		.linear_ranges = buck_volt_ranges,
		.n_linear_ranges = ARRAY_SIZE(buck_volt_ranges),
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_BUCK4_VOUT,
		.vsel_mask = LP8788_VOUT_M,
		.enable_reg = LP8788_EN_BUCK,
		.enable_mask = LP8788_EN_BUCK4_M,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lp8788_dvs_gpio_request(काष्ठा platक्रमm_device *pdev,
				काष्ठा lp8788_buck *buck,
				क्रमागत lp8788_buck_id id)
अणु
	काष्ठा lp8788_platक्रमm_data *pdata = buck->lp->pdata;
	अक्षर *b1_name = "LP8788_B1_DVS";
	अक्षर *b2_name[] = अणु "LP8788_B2_DVS1", "LP8788_B2_DVS2" पूर्ण;
	पूर्णांक i, gpio, ret;

	चयन (id) अणु
	हाल BUCK1:
		gpio = pdata->buck1_dvs->gpio;
		ret = devm_gpio_request_one(&pdev->dev, gpio, DVS_LOW,
					    b1_name);
		अगर (ret)
			वापस ret;

		buck->dvs = pdata->buck1_dvs;
		अवरोध;
	हाल BUCK2:
		क्रम (i = 0; i < LP8788_NUM_BUCK2_DVS; i++) अणु
			gpio = pdata->buck2_dvs->gpio[i];
			ret = devm_gpio_request_one(&pdev->dev, gpio,
						    DVS_LOW, b2_name[i]);
			अगर (ret)
				वापस ret;
		पूर्ण
		buck->dvs = pdata->buck2_dvs;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_init_dvs(काष्ठा platक्रमm_device *pdev,
			काष्ठा lp8788_buck *buck, क्रमागत lp8788_buck_id id)
अणु
	काष्ठा lp8788_platक्रमm_data *pdata = buck->lp->pdata;
	u8 mask[] = अणु LP8788_BUCK1_DVS_SEL_M, LP8788_BUCK2_DVS_SEL_M पूर्ण;
	u8 val[]  = अणु LP8788_BUCK1_DVS_PIN, LP8788_BUCK2_DVS_PIN पूर्ण;
	u8 शेष_dvs_mode[] = अणु LP8788_BUCK1_DVS_I2C, LP8788_BUCK2_DVS_I2C पूर्ण;

	/* no dvs क्रम buck3, 4 */
	अगर (id > BUCK2)
		वापस 0;

	/* no dvs platक्रमm data, then dvs will be selected by I2C रेजिस्टरs */
	अगर (!pdata)
		जाओ set_शेष_dvs_mode;

	अगर ((id == BUCK1 && !pdata->buck1_dvs) ||
		(id == BUCK2 && !pdata->buck2_dvs))
		जाओ set_शेष_dvs_mode;

	अगर (lp8788_dvs_gpio_request(pdev, buck, id))
		जाओ set_शेष_dvs_mode;

	वापस lp8788_update_bits(buck->lp, LP8788_BUCK_DVS_SEL, mask[id],
				val[id]);

set_शेष_dvs_mode:
	वापस lp8788_update_bits(buck->lp, LP8788_BUCK_DVS_SEL, mask[id],
				  शेष_dvs_mode[id]);
पूर्ण

अटल पूर्णांक lp8788_buck_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक id = pdev->id;
	काष्ठा lp8788_buck *buck;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;

	अगर (id >= LP8788_NUM_BUCKS)
		वापस -EINVAL;

	buck = devm_kzalloc(&pdev->dev, माप(काष्ठा lp8788_buck), GFP_KERNEL);
	अगर (!buck)
		वापस -ENOMEM;

	buck->lp = lp;

	ret = lp8788_init_dvs(pdev, buck, id);
	अगर (ret)
		वापस ret;

	cfg.dev = pdev->dev.parent;
	cfg.init_data = lp->pdata ? lp->pdata->buck_data[id] : शून्य;
	cfg.driver_data = buck;
	cfg.regmap = lp->regmap;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &lp8788_buck_desc[id], &cfg);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(&pdev->dev, "BUCK%d regulator register err = %d\n",
				id + 1, ret);
		वापस ret;
	पूर्ण

	buck->regulator = rdev;
	platक्रमm_set_drvdata(pdev, buck);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lp8788_buck_driver = अणु
	.probe = lp8788_buck_probe,
	.driver = अणु
		.name = LP8788_DEV_BUCK,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init lp8788_buck_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&lp8788_buck_driver);
पूर्ण
subsys_initcall(lp8788_buck_init);

अटल व्योम __निकास lp8788_buck_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&lp8788_buck_driver);
पूर्ण
module_निकास(lp8788_buck_निकास);

MODULE_DESCRIPTION("TI LP8788 BUCK Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lp8788-buck");
