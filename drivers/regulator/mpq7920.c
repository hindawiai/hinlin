<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// mpq7920.c  - regulator driver क्रम mps mpq7920
//
// Copyright 2019 Monolithic Power Systems, Inc
//
// Author: Saravanan Sekar <sravanhome@gmail.com>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश "mpq7920.h"

#घोषणा MPQ7920_BUCK_VOLT_RANGE \
	((MPQ7920_VOLT_MAX - MPQ7920_BUCK_VOLT_MIN)/MPQ7920_VOLT_STEP + 1)
#घोषणा MPQ7920_LDO_VOLT_RANGE \
	((MPQ7920_VOLT_MAX - MPQ7920_LDO_VOLT_MIN)/MPQ7920_VOLT_STEP + 1)

#घोषणा MPQ7920BUCK(_name, _id, _ilim)					\
	[MPQ7920_BUCK ## _id] = अणु					\
		.id = MPQ7920_BUCK ## _id,				\
		.name = _name,						\
		.of_match = _name,					\
		.regulators_node = "regulators",			\
		.of_parse_cb = mpq7920_parse_cb,			\
		.ops = &mpq7920_buck_ops,				\
		.min_uV = MPQ7920_BUCK_VOLT_MIN,			\
		.uV_step = MPQ7920_VOLT_STEP,				\
		.n_voltages = MPQ7920_BUCK_VOLT_RANGE,			\
		.curr_table = _ilim,					\
		.n_current_limits = ARRAY_SIZE(_ilim),			\
		.csel_reg = MPQ7920_BUCK ##_id## _REG_C,		\
		.csel_mask = MPQ7920_MASK_BUCK_ILIM,			\
		.enable_reg = MPQ7920_REG_REGULATOR_EN,			\
		.enable_mask = BIT(MPQ7920_REGULATOR_EN_OFFSET -	\
					 MPQ7920_BUCK ## _id),		\
		.vsel_reg = MPQ7920_BUCK ##_id## _REG_A,		\
		.vsel_mask = MPQ7920_MASK_VREF,				\
		.active_disअक्षरge_on	= MPQ7920_DISCHARGE_ON,		\
		.active_disअक्षरge_reg	= MPQ7920_BUCK ##_id## _REG_B,	\
		.active_disअक्षरge_mask	= MPQ7920_MASK_DISCHARGE,	\
		.soft_start_reg		= MPQ7920_BUCK ##_id## _REG_C,	\
		.soft_start_mask	= MPQ7920_MASK_SOFTSTART,	\
		.owner			= THIS_MODULE,			\
	पूर्ण

#घोषणा MPQ7920LDO(_name, _id, _ops, _ilim, _ilim_sz, _creg, _cmask)	\
	[MPQ7920_LDO ## _id] = अणु					\
		.id = MPQ7920_LDO ## _id,				\
		.name = _name,						\
		.of_match = _name,					\
		.regulators_node = "regulators",			\
		.ops = _ops,						\
		.min_uV = MPQ7920_LDO_VOLT_MIN,				\
		.uV_step = MPQ7920_VOLT_STEP,				\
		.n_voltages = MPQ7920_LDO_VOLT_RANGE,			\
		.vsel_reg = MPQ7920_LDO ##_id## _REG_A,			\
		.vsel_mask = MPQ7920_MASK_VREF,				\
		.curr_table = _ilim,					\
		.n_current_limits = _ilim_sz,				\
		.csel_reg = _creg,					\
		.csel_mask = _cmask,					\
		.enable_reg = (_id == 1) ? 0 : MPQ7920_REG_REGULATOR_EN,\
		.enable_mask = BIT(MPQ7920_REGULATOR_EN_OFFSET -	\
					MPQ7920_LDO ##_id + 1),		\
		.active_disअक्षरge_on	= MPQ7920_DISCHARGE_ON,		\
		.active_disअक्षरge_mask	= MPQ7920_MASK_DISCHARGE,	\
		.active_disअक्षरge_reg	= MPQ7920_LDO ##_id## _REG_B,	\
		.type			= REGULATOR_VOLTAGE,		\
		.owner			= THIS_MODULE,			\
	पूर्ण

क्रमागत mpq7920_regulators अणु
	MPQ7920_BUCK1,
	MPQ7920_BUCK2,
	MPQ7920_BUCK3,
	MPQ7920_BUCK4,
	MPQ7920_LDO1, /* LDORTC */
	MPQ7920_LDO2,
	MPQ7920_LDO3,
	MPQ7920_LDO4,
	MPQ7920_LDO5,
	MPQ7920_MAX_REGULATORS,
पूर्ण;

काष्ठा mpq7920_regulator_info अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_desc *rdesc;
पूर्ण;

अटल स्थिर काष्ठा regmap_config mpq7920_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x25,
पूर्ण;

/* Current limits array (in uA)
 * ILIM1 & ILIM3
 */
अटल स्थिर अचिन्हित पूर्णांक mpq7920_I_limits1[] = अणु
	4600000, 6600000, 7600000, 9300000
पूर्ण;

/* ILIM2 & ILIM4 */
अटल स्थिर अचिन्हित पूर्णांक mpq7920_I_limits2[] = अणु
	2700000, 3900000, 5100000, 6100000
पूर्ण;

/* LDO4 & LDO5 */
अटल स्थिर अचिन्हित पूर्णांक mpq7920_I_limits3[] = अणु
	300000, 700000
पूर्ण;

अटल पूर्णांक mpq7920_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay);
अटल पूर्णांक mpq7920_parse_cb(काष्ठा device_node *np,
				स्थिर काष्ठा regulator_desc *rdesc,
				काष्ठा regulator_config *config);

/* RTCLDO not controllable, always ON */
अटल स्थिर काष्ठा regulator_ops mpq7920_lकरोrtc_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mpq7920_lकरो_wo_current_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_active_disअक्षरge	= regulator_set_active_disअक्षरge_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mpq7920_lकरो_ops = अणु
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
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mpq7920_buck_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_active_disअक्षरge	= regulator_set_active_disअक्षरge_regmap,
	.set_soft_start		= regulator_set_soft_start_regmap,
	.set_ramp_delay		= mpq7920_set_ramp_delay,
पूर्ण;

अटल काष्ठा regulator_desc mpq7920_regulators_desc[MPQ7920_MAX_REGULATORS] = अणु
	MPQ7920BUCK("buck1", 1, mpq7920_I_limits1),
	MPQ7920BUCK("buck2", 2, mpq7920_I_limits2),
	MPQ7920BUCK("buck3", 3, mpq7920_I_limits1),
	MPQ7920BUCK("buck4", 4, mpq7920_I_limits2),
	MPQ7920LDO("ldortc", 1, &mpq7920_lकरोrtc_ops, शून्य, 0, 0, 0),
	MPQ7920LDO("ldo2", 2, &mpq7920_lकरो_wo_current_ops, शून्य, 0, 0, 0),
	MPQ7920LDO("ldo3", 3, &mpq7920_lकरो_wo_current_ops, शून्य, 0, 0, 0),
	MPQ7920LDO("ldo4", 4, &mpq7920_lकरो_ops, mpq7920_I_limits3,
			ARRAY_SIZE(mpq7920_I_limits3), MPQ7920_LDO4_REG_B,
			MPQ7920_MASK_LDO_ILIM),
	MPQ7920LDO("ldo5", 5, &mpq7920_lकरो_ops, mpq7920_I_limits3,
			ARRAY_SIZE(mpq7920_I_limits3), MPQ7920_LDO5_REG_B,
			MPQ7920_MASK_LDO_ILIM),
पूर्ण;

/*
 * DVS ramp rate BUCK1 to BUCK4
 * 00-01: Reserved
 * 10: 8mV/us
 * 11: 4mV/us
 */
अटल पूर्णांक mpq7920_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	अचिन्हित पूर्णांक ramp_val;

	अगर (ramp_delay > 8000 || ramp_delay < 0)
		वापस -EINVAL;

	अगर (ramp_delay <= 4000)
		ramp_val = 3;
	अन्यथा
		ramp_val = 2;

	वापस regmap_update_bits(rdev->regmap, MPQ7920_REG_CTL0,
				  MPQ7920_MASK_DVS_SLEWRATE, ramp_val << 6);
पूर्ण

अटल पूर्णांक mpq7920_parse_cb(काष्ठा device_node *np,
				स्थिर काष्ठा regulator_desc *desc,
				काष्ठा regulator_config *config)
अणु
	uपूर्णांक8_t val;
	पूर्णांक ret;
	काष्ठा mpq7920_regulator_info *info = config->driver_data;
	काष्ठा regulator_desc *rdesc = &info->rdesc[desc->id];

	अगर (of_property_पढ़ो_bool(np, "mps,buck-ovp-disable")) अणु
		regmap_update_bits(config->regmap,
				MPQ7920_BUCK1_REG_B + (rdesc->id * 4),
				MPQ7920_MASK_OVP, MPQ7920_OVP_DISABLE);
	पूर्ण

	ret = of_property_पढ़ो_u8(np, "mps,buck-phase-delay", &val);
	अगर (!ret) अणु
		regmap_update_bits(config->regmap,
				MPQ7920_BUCK1_REG_C + (rdesc->id * 4),
				MPQ7920_MASK_BUCK_PHASE_DEALY,
				(val & 3) << 4);
	पूर्ण

	ret = of_property_पढ़ो_u8(np, "mps,buck-softstart", &val);
	अगर (!ret)
		rdesc->soft_start_val_on = (val & 3) << 2;

	वापस 0;
पूर्ण

अटल व्योम mpq7920_parse_dt(काष्ठा device *dev,
		 काष्ठा mpq7920_regulator_info *info)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np = dev->of_node;
	uपूर्णांक8_t freq;

	np = of_get_child_by_name(np, "regulators");
	अगर (!np) अणु
		dev_err(dev, "missing 'regulators' subnode in DT\n");
		वापस;
	पूर्ण

	ret = of_property_पढ़ो_u8(np, "mps,switch-freq", &freq);
	अगर (!ret) अणु
		regmap_update_bits(info->regmap, MPQ7920_REG_CTL0,
					MPQ7920_MASK_SWITCH_FREQ,
					(freq & 3) << 4);
	पूर्ण

	of_node_put(np);
पूर्ण

अटल पूर्णांक mpq7920_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा mpq7920_regulator_info *info;
	काष्ठा regulator_config config = अणु शून्य, पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	पूर्णांक i;

	info = devm_kzalloc(dev, माप(काष्ठा mpq7920_regulator_info),
				GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->rdesc = mpq7920_regulators_desc;
	regmap = devm_regmap_init_i2c(client, &mpq7920_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to allocate regmap!\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	i2c_set_clientdata(client, info);
	info->regmap = regmap;
	अगर (client->dev.of_node)
		mpq7920_parse_dt(&client->dev, info);

	config.dev = dev;
	config.regmap = regmap;
	config.driver_data = info;

	क्रम (i = 0; i < MPQ7920_MAX_REGULATORS; i++) अणु
		rdev = devm_regulator_रेजिस्टर(dev,
					       &mpq7920_regulators_desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev, "Failed to register regulator!\n");
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpq7920_of_match[] = अणु
	अणु .compatible = "mps,mpq7920"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpq7920_of_match);

अटल स्थिर काष्ठा i2c_device_id mpq7920_id[] = अणु
	अणु "mpq7920", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mpq7920_id);

अटल काष्ठा i2c_driver mpq7920_regulator_driver = अणु
	.driver = अणु
		.name = "mpq7920",
		.of_match_table = of_match_ptr(mpq7920_of_match),
	पूर्ण,
	.probe_new = mpq7920_i2c_probe,
	.id_table = mpq7920_id,
पूर्ण;
module_i2c_driver(mpq7920_regulator_driver);

MODULE_AUTHOR("Saravanan Sekar <sravanhome@gmail.com>");
MODULE_DESCRIPTION("MPQ7920 PMIC regulator driver");
MODULE_LICENSE("GPL");
