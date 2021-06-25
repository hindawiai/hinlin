<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// mp5416.c  - regulator driver क्रम mps mp5416
//
// Copyright 2020 Monolithic Power Systems, Inc
//
// Author: Saravanan Sekar <sravanhome@gmail.com>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/i2c.h>

#घोषणा MP5416_REG_CTL0			0x00
#घोषणा MP5416_REG_CTL1			0x01
#घोषणा MP5416_REG_CTL2			0x02
#घोषणा MP5416_REG_ILIM			0x03
#घोषणा MP5416_REG_BUCK1		0x04
#घोषणा MP5416_REG_BUCK2		0x05
#घोषणा MP5416_REG_BUCK3		0x06
#घोषणा MP5416_REG_BUCK4		0x07
#घोषणा MP5416_REG_LDO1			0x08
#घोषणा MP5416_REG_LDO2			0x09
#घोषणा MP5416_REG_LDO3			0x0a
#घोषणा MP5416_REG_LDO4			0x0b

#घोषणा MP5416_REGULATOR_EN		BIT(7)
#घोषणा MP5416_MASK_VSET		0x7f
#घोषणा MP5416_MASK_BUCK1_ILIM		0xc0
#घोषणा MP5416_MASK_BUCK2_ILIM		0x0c
#घोषणा MP5416_MASK_BUCK3_ILIM		0x30
#घोषणा MP5416_MASK_BUCK4_ILIM		0x03
#घोषणा MP5416_MASK_DVS_SLEWRATE	0xc0

/* values in uV */
#घोषणा MP5416_VOLT1_MIN		600000
#घोषणा MP5416_VOLT1_MAX		2187500
#घोषणा MP5416_VOLT1_STEP		12500
#घोषणा MP5416_VOLT2_MIN		800000
#घोषणा MP5416_VOLT2_MAX		3975000
#घोषणा MP5416_VOLT2_STEP		25000

#घोषणा MP5416_VOLT1_RANGE \
	((MP5416_VOLT1_MAX - MP5416_VOLT1_MIN)/MP5416_VOLT1_STEP + 1)
#घोषणा MP5416_VOLT2_RANGE \
	((MP5416_VOLT2_MAX - MP5416_VOLT2_MIN)/MP5416_VOLT2_STEP + 1)

#घोषणा MP5416BUCK(_name, _id, _ilim, _dreg, _dval, _vsel)		\
	[MP5416_BUCK ## _id] = अणु					\
		.id = MP5416_BUCK ## _id,				\
		.name = _name,						\
		.of_match = _name,					\
		.regulators_node = "regulators",			\
		.ops = &mp5416_buck_ops,				\
		.min_uV = MP5416_VOLT ##_vsel## _MIN,			\
		.uV_step = MP5416_VOLT ##_vsel## _STEP,			\
		.n_voltages = MP5416_VOLT ##_vsel## _RANGE,		\
		.curr_table = _ilim,					\
		.n_current_limits = ARRAY_SIZE(_ilim),			\
		.csel_reg = MP5416_REG_ILIM,				\
		.csel_mask = MP5416_MASK_BUCK ## _id ##_ILIM,		\
		.vsel_reg = MP5416_REG_BUCK ## _id,			\
		.vsel_mask = MP5416_MASK_VSET,				\
		.enable_reg = MP5416_REG_BUCK ## _id,			\
		.enable_mask = MP5416_REGULATOR_EN,			\
		.active_disअक्षरge_on	= _dval,			\
		.active_disअक्षरge_reg	= _dreg,			\
		.active_disअक्षरge_mask	= _dval,			\
		.owner			= THIS_MODULE,			\
	पूर्ण

#घोषणा MP5416LDO(_name, _id, _dval)					\
	[MP5416_LDO ## _id] = अणु						\
		.id = MP5416_LDO ## _id,				\
		.name = _name,						\
		.of_match = _name,					\
		.regulators_node = "regulators",			\
		.ops = &mp5416_lकरो_ops,					\
		.min_uV = MP5416_VOLT2_MIN,				\
		.uV_step = MP5416_VOLT2_STEP,				\
		.n_voltages = MP5416_VOLT2_RANGE,			\
		.vsel_reg = MP5416_REG_LDO ##_id,			\
		.vsel_mask = MP5416_MASK_VSET,				\
		.enable_reg = MP5416_REG_LDO ##_id,			\
		.enable_mask = MP5416_REGULATOR_EN,			\
		.active_disअक्षरge_on	= _dval,			\
		.active_disअक्षरge_reg	= MP5416_REG_CTL2,		\
		.active_disअक्षरge_mask	= _dval,			\
		.owner			= THIS_MODULE,			\
	पूर्ण

क्रमागत mp5416_regulators अणु
	MP5416_BUCK1,
	MP5416_BUCK2,
	MP5416_BUCK3,
	MP5416_BUCK4,
	MP5416_LDO1,
	MP5416_LDO2,
	MP5416_LDO3,
	MP5416_LDO4,
	MP5416_MAX_REGULATORS,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mp5416_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x0d,
पूर्ण;

/* Current limits array (in uA)
 * ILIM1 & ILIM3
 */
अटल स्थिर अचिन्हित पूर्णांक mp5416_I_limits1[] = अणु
	3800000, 4600000, 5600000, 6800000
पूर्ण;

/* ILIM2 & ILIM4 */
अटल स्थिर अचिन्हित पूर्णांक mp5416_I_limits2[] = अणु
	2200000, 3200000, 4200000, 5200000
पूर्ण;

अटल पूर्णांक mp5416_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay);

अटल स्थिर काष्ठा regulator_ops mp5416_lकरो_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_active_disअक्षरge	= regulator_set_active_disअक्षरge_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mp5416_buck_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_active_disअक्षरge	= regulator_set_active_disअक्षरge_regmap,
	.get_current_limit	= regulator_get_current_limit_regmap,
	.set_current_limit	= regulator_set_current_limit_regmap,
	.set_ramp_delay		= mp5416_set_ramp_delay,
पूर्ण;

अटल काष्ठा regulator_desc mp5416_regulators_desc[MP5416_MAX_REGULATORS] = अणु
	MP5416BUCK("buck1", 1, mp5416_I_limits1, MP5416_REG_CTL1, BIT(0), 1),
	MP5416BUCK("buck2", 2, mp5416_I_limits2, MP5416_REG_CTL1, BIT(1), 2),
	MP5416BUCK("buck3", 3, mp5416_I_limits1, MP5416_REG_CTL1, BIT(2), 1),
	MP5416BUCK("buck4", 4, mp5416_I_limits2, MP5416_REG_CTL2, BIT(5), 2),
	MP5416LDO("ldo1", 1, BIT(4)),
	MP5416LDO("ldo2", 2, BIT(3)),
	MP5416LDO("ldo3", 3, BIT(2)),
	MP5416LDO("ldo4", 4, BIT(1)),
पूर्ण;

/*
 * DVS ramp rate BUCK1 to BUCK4
 * 00: 32mV/us
 * 01: 16mV/us
 * 10: 8mV/us
 * 11: 4mV/us
 */
अटल पूर्णांक mp5416_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	अचिन्हित पूर्णांक ramp_val;

	अगर (ramp_delay > 32000 || ramp_delay < 0)
		वापस -EINVAL;

	अगर (ramp_delay <= 4000)
		ramp_val = 3;
	अन्यथा अगर (ramp_delay <= 8000)
		ramp_val = 2;
	अन्यथा अगर (ramp_delay <= 16000)
		ramp_val = 1;
	अन्यथा
		ramp_val = 0;

	वापस regmap_update_bits(rdev->regmap, MP5416_REG_CTL2,
				  MP5416_MASK_DVS_SLEWRATE, ramp_val << 6);
पूर्ण

अटल पूर्णांक mp5416_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा regulator_config config = अणु शून्य, पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	पूर्णांक i;

	regmap = devm_regmap_init_i2c(client, &mp5416_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to allocate regmap!\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	config.dev = dev;
	config.regmap = regmap;

	क्रम (i = 0; i < MP5416_MAX_REGULATORS; i++) अणु
		rdev = devm_regulator_रेजिस्टर(dev,
					       &mp5416_regulators_desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev, "Failed to register regulator!\n");
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mp5416_of_match[] = अणु
	अणु .compatible = "mps,mp5416" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mp5416_of_match);

अटल स्थिर काष्ठा i2c_device_id mp5416_id[] = अणु
	अणु "mp5416", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mp5416_id);

अटल काष्ठा i2c_driver mp5416_regulator_driver = अणु
	.driver = अणु
		.name = "mp5416",
		.of_match_table = of_match_ptr(mp5416_of_match),
	पूर्ण,
	.probe_new = mp5416_i2c_probe,
	.id_table = mp5416_id,
पूर्ण;
module_i2c_driver(mp5416_regulator_driver);

MODULE_AUTHOR("Saravanan Sekar <sravanhome@gmail.com>");
MODULE_DESCRIPTION("MP5416 PMIC regulator driver");
MODULE_LICENSE("GPL");
