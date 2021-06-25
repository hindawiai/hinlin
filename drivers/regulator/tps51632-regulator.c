<शैली गुरु>
/*
 * tps51632-regulator.c -- TI TPS51632
 *
 * Regulator driver क्रम TPS51632 3-2-1 Phase D-Cap Step Down Driverless
 * Controller with serial VID control and DVFS.
 *
 * Copyright (c) 2012, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/tps51632-regulator.h>
#समावेश <linux/slab.h>

/* Register definitions */
#घोषणा TPS51632_VOLTAGE_SELECT_REG		0x0
#घोषणा TPS51632_VOLTAGE_BASE_REG		0x1
#घोषणा TPS51632_OFFSET_REG			0x2
#घोषणा TPS51632_IMON_REG			0x3
#घोषणा TPS51632_VMAX_REG			0x4
#घोषणा TPS51632_DVFS_CONTROL_REG		0x5
#घोषणा TPS51632_POWER_STATE_REG		0x6
#घोषणा TPS51632_SLEW_REGS			0x7
#घोषणा TPS51632_FAULT_REG			0x14

#घोषणा TPS51632_MAX_REG			0x15

#घोषणा TPS51632_VOUT_MASK			0x7F
#घोषणा TPS51632_VOUT_OFFSET_MASK		0x1F
#घोषणा TPS51632_VMAX_MASK			0x7F
#घोषणा TPS51632_VMAX_LOCK			0x80

/* TPS51632_DVFS_CONTROL_REG */
#घोषणा TPS51632_DVFS_PWMEN			0x1
#घोषणा TPS51632_DVFS_STEP_20			0x2
#घोषणा TPS51632_DVFS_VMAX_PG			0x4
#घोषणा TPS51632_DVFS_PWMRST			0x8
#घोषणा TPS51632_DVFS_OCA_EN			0x10
#घोषणा TPS51632_DVFS_FCCM			0x20

/* TPS51632_POWER_STATE_REG */
#घोषणा TPS51632_POWER_STATE_MASK		0x03
#घोषणा TPS51632_POWER_STATE_MULTI_PHASE_CCM	0x0
#घोषणा TPS51632_POWER_STATE_SINGLE_PHASE_CCM	0x1
#घोषणा TPS51632_POWER_STATE_SINGLE_PHASE_DCM	0x2

#घोषणा TPS51632_MIN_VOLTAGE			500000
#घोषणा TPS51632_MAX_VOLTAGE			1520000
#घोषणा TPS51632_VOLTAGE_STEP_10mV		10000
#घोषणा TPS51632_VOLTAGE_STEP_20mV		20000
#घोषणा TPS51632_MAX_VSEL			0x7F
#घोषणा TPS51632_MIN_VSEL			0x19
#घोषणा TPS51632_DEFAULT_RAMP_DELAY		6000
#घोषणा TPS51632_VOLT_VSEL(uV)					\
		(DIV_ROUND_UP(uV - TPS51632_MIN_VOLTAGE,	\
			TPS51632_VOLTAGE_STEP_10mV) +		\
			TPS51632_MIN_VSEL)

/* TPS51632 chip inक्रमmation */
काष्ठा tps51632_chip अणु
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल पूर्णांक tps51632_dcdc_set_ramp_delay(काष्ठा regulator_dev *rdev,
		पूर्णांक ramp_delay)
अणु
	काष्ठा tps51632_chip *tps = rdev_get_drvdata(rdev);
	पूर्णांक bit;
	पूर्णांक ret;

	अगर (ramp_delay == 0)
		bit = 0;
	अन्यथा
		bit = DIV_ROUND_UP(ramp_delay, 6000) - 1;

	ret = regmap_ग_लिखो(tps->regmap, TPS51632_SLEW_REGS, BIT(bit));
	अगर (ret < 0)
		dev_err(tps->dev, "SLEW reg write failed, err %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops tps51632_dcdc_ops = अणु
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= tps51632_dcdc_set_ramp_delay,
पूर्ण;

अटल पूर्णांक tps51632_init_dcdc(काष्ठा tps51632_chip *tps,
		काष्ठा tps51632_regulator_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;
	uपूर्णांक8_t	control = 0;
	पूर्णांक vsel;

	अगर (!pdata->enable_pwm_dvfs)
		जाओ skip_pwm_config;

	control |= TPS51632_DVFS_PWMEN;
	vsel = TPS51632_VOLT_VSEL(pdata->base_voltage_uV);
	ret = regmap_ग_लिखो(tps->regmap, TPS51632_VOLTAGE_BASE_REG, vsel);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "BASE reg write failed, err %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pdata->dvfs_step_20mV)
		control |= TPS51632_DVFS_STEP_20;

	अगर (pdata->max_voltage_uV) अणु
		अचिन्हित पूर्णांक vmax;
		/**
		 * TPS51632 hw behavior: VMAX रेजिस्टर can be ग_लिखो only
		 * once as it get locked after first ग_लिखो. The lock get
		 * reset only when device is घातer-reset.
		 * Write रेजिस्टर only when lock bit is not enabled.
		 */
		ret = regmap_पढ़ो(tps->regmap, TPS51632_VMAX_REG, &vmax);
		अगर (ret < 0) अणु
			dev_err(tps->dev, "VMAX read failed, err %d\n", ret);
			वापस ret;
		पूर्ण
		अगर (!(vmax & TPS51632_VMAX_LOCK)) अणु
			vsel = TPS51632_VOLT_VSEL(pdata->max_voltage_uV);
			ret = regmap_ग_लिखो(tps->regmap, TPS51632_VMAX_REG,
					vsel);
			अगर (ret < 0) अणु
				dev_err(tps->dev,
					"VMAX write failed, err %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

skip_pwm_config:
	ret = regmap_ग_लिखो(tps->regmap, TPS51632_DVFS_CONTROL_REG, control);
	अगर (ret < 0)
		dev_err(tps->dev, "DVFS reg write failed, err %d\n", ret);
	वापस ret;
पूर्ण

अटल bool is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TPS51632_OFFSET_REG:
	हाल TPS51632_FAULT_REG:
	हाल TPS51632_IMON_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_पढ़ो_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x08 ... 0x0F:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool is_ग_लिखो_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TPS51632_VOLTAGE_SELECT_REG:
	हाल TPS51632_VOLTAGE_BASE_REG:
	हाल TPS51632_VMAX_REG:
	हाल TPS51632_DVFS_CONTROL_REG:
	हाल TPS51632_POWER_STATE_REG:
	हाल TPS51632_SLEW_REGS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tps51632_regmap_config = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.ग_लिखोable_reg		= is_ग_लिखो_reg,
	.पढ़ोable_reg		= is_पढ़ो_reg,
	.अस्थिर_reg		= is_अस्थिर_reg,
	.max_रेजिस्टर		= TPS51632_MAX_REG - 1,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tps51632_of_match[] = अणु
	अणु .compatible = "ti,tps51632",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tps51632_of_match);

अटल काष्ठा tps51632_regulator_platक्रमm_data *
	of_get_tps51632_platक्रमm_data(काष्ठा device *dev,
				      स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा tps51632_regulator_platक्रमm_data *pdata;
	काष्ठा device_node *np = dev->of_node;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->reg_init_data = of_get_regulator_init_data(dev, dev->of_node,
							  desc);
	अगर (!pdata->reg_init_data) अणु
		dev_err(dev, "Not able to get OF regulator init data\n");
		वापस शून्य;
	पूर्ण

	pdata->enable_pwm_dvfs =
			of_property_पढ़ो_bool(np, "ti,enable-pwm-dvfs");
	pdata->dvfs_step_20mV = of_property_पढ़ो_bool(np, "ti,dvfs-step-20mV");

	pdata->base_voltage_uV = pdata->reg_init_data->स्थिरraपूर्णांकs.min_uV ? :
					TPS51632_MIN_VOLTAGE;
	pdata->max_voltage_uV = pdata->reg_init_data->स्थिरraपूर्णांकs.max_uV ? :
					TPS51632_MAX_VOLTAGE;
	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा tps51632_regulator_platक्रमm_data *
	of_get_tps51632_platक्रमm_data(काष्ठा device *dev,
				      स्थिर काष्ठा regulator_desc *desc)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tps51632_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tps51632_regulator_platक्रमm_data *pdata;
	काष्ठा regulator_dev *rdev;
	काष्ठा tps51632_chip *tps;
	पूर्णांक ret;
	काष्ठा regulator_config config = अणु पूर्ण;

	अगर (client->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;
		match = of_match_device(of_match_ptr(tps51632_of_match),
				&client->dev);
		अगर (!match) अणु
			dev_err(&client->dev, "Error: No device match found\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	tps->dev = &client->dev;
	tps->desc.name = client->name;
	tps->desc.id = 0;
	tps->desc.ramp_delay = TPS51632_DEFAULT_RAMP_DELAY;
	tps->desc.min_uV = TPS51632_MIN_VOLTAGE;
	tps->desc.uV_step = TPS51632_VOLTAGE_STEP_10mV;
	tps->desc.linear_min_sel = TPS51632_MIN_VSEL;
	tps->desc.n_voltages = TPS51632_MAX_VSEL + 1;
	tps->desc.ops = &tps51632_dcdc_ops;
	tps->desc.type = REGULATOR_VOLTAGE;
	tps->desc.owner = THIS_MODULE;

	pdata = dev_get_platdata(&client->dev);
	अगर (!pdata && client->dev.of_node)
		pdata = of_get_tps51632_platक्रमm_data(&client->dev, &tps->desc);
	अगर (!pdata) अणु
		dev_err(&client->dev, "No Platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->enable_pwm_dvfs) अणु
		अगर ((pdata->base_voltage_uV < TPS51632_MIN_VOLTAGE) ||
		    (pdata->base_voltage_uV > TPS51632_MAX_VOLTAGE)) अणु
			dev_err(&client->dev, "Invalid base_voltage_uV setting\n");
			वापस -EINVAL;
		पूर्ण

		अगर ((pdata->max_voltage_uV) &&
		    ((pdata->max_voltage_uV < TPS51632_MIN_VOLTAGE) ||
		     (pdata->max_voltage_uV > TPS51632_MAX_VOLTAGE))) अणु
			dev_err(&client->dev, "Invalid max_voltage_uV setting\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (pdata->enable_pwm_dvfs)
		tps->desc.vsel_reg = TPS51632_VOLTAGE_BASE_REG;
	अन्यथा
		tps->desc.vsel_reg = TPS51632_VOLTAGE_SELECT_REG;
	tps->desc.vsel_mask = TPS51632_VOUT_MASK;

	tps->regmap = devm_regmap_init_i2c(client, &tps51632_regmap_config);
	अगर (IS_ERR(tps->regmap)) अणु
		ret = PTR_ERR(tps->regmap);
		dev_err(&client->dev, "regmap init failed, err %d\n", ret);
		वापस ret;
	पूर्ण
	i2c_set_clientdata(client, tps);

	ret = tps51632_init_dcdc(tps, pdata);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "Init failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	/* Register the regulators */
	config.dev = &client->dev;
	config.init_data = pdata->reg_init_data;
	config.driver_data = tps;
	config.regmap = tps->regmap;
	config.of_node = client->dev.of_node;

	rdev = devm_regulator_रेजिस्टर(&client->dev, &tps->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(tps->dev, "regulator register failed\n");
		वापस PTR_ERR(rdev);
	पूर्ण

	tps->rdev = rdev;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps51632_id[] = अणु
	अणु.name = "tps51632",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tps51632_id);

अटल काष्ठा i2c_driver tps51632_i2c_driver = अणु
	.driver = अणु
		.name = "tps51632",
		.of_match_table = of_match_ptr(tps51632_of_match),
	पूर्ण,
	.probe = tps51632_probe,
	.id_table = tps51632_id,
पूर्ण;

अटल पूर्णांक __init tps51632_init(व्योम)
अणु
	वापस i2c_add_driver(&tps51632_i2c_driver);
पूर्ण
subsys_initcall(tps51632_init);

अटल व्योम __निकास tps51632_cleanup(व्योम)
अणु
	i2c_del_driver(&tps51632_i2c_driver);
पूर्ण
module_निकास(tps51632_cleanup);

MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_DESCRIPTION("TPS51632 voltage regulator driver");
MODULE_LICENSE("GPL v2");
