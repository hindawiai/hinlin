<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Linear Technology LTC3589,LTC3589-1 regulator support
//
// Copyright (c) 2014 Philipp Zabel <p.zabel@pengutronix.de>, Pengutronix

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा DRIVER_NAME		"ltc3589"

#घोषणा LTC3589_IRQSTAT		0x02
#घोषणा LTC3589_SCR1		0x07
#घोषणा LTC3589_OVEN		0x10
#घोषणा LTC3589_SCR2		0x12
#घोषणा LTC3589_PGSTAT		0x13
#घोषणा LTC3589_VCCR		0x20
#घोषणा LTC3589_CLIRQ		0x21
#घोषणा LTC3589_B1DTV1		0x23
#घोषणा LTC3589_B1DTV2		0x24
#घोषणा LTC3589_VRRCR		0x25
#घोषणा LTC3589_B2DTV1		0x26
#घोषणा LTC3589_B2DTV2		0x27
#घोषणा LTC3589_B3DTV1		0x29
#घोषणा LTC3589_B3DTV2		0x2a
#घोषणा LTC3589_L2DTV1		0x32
#घोषणा LTC3589_L2DTV2		0x33

#घोषणा LTC3589_IRQSTAT_PGOOD_TIMEOUT	BIT(3)
#घोषणा LTC3589_IRQSTAT_UNDERVOLT_WARN	BIT(4)
#घोषणा LTC3589_IRQSTAT_UNDERVOLT_FAULT	BIT(5)
#घोषणा LTC3589_IRQSTAT_THERMAL_WARN	BIT(6)
#घोषणा LTC3589_IRQSTAT_THERMAL_FAULT	BIT(7)

#घोषणा LTC3589_OVEN_SW1		BIT(0)
#घोषणा LTC3589_OVEN_SW2		BIT(1)
#घोषणा LTC3589_OVEN_SW3		BIT(2)
#घोषणा LTC3589_OVEN_BB_OUT		BIT(3)
#घोषणा LTC3589_OVEN_LDO2		BIT(4)
#घोषणा LTC3589_OVEN_LDO3		BIT(5)
#घोषणा LTC3589_OVEN_LDO4		BIT(6)
#घोषणा LTC3589_OVEN_SW_CTRL		BIT(7)

#घोषणा LTC3589_VCCR_SW1_GO		BIT(0)
#घोषणा LTC3589_VCCR_SW2_GO		BIT(2)
#घोषणा LTC3589_VCCR_SW3_GO		BIT(4)
#घोषणा LTC3589_VCCR_LDO2_GO		BIT(6)

क्रमागत ltc3589_variant अणु
	LTC3589,
	LTC3589_1,
	LTC3589_2,
पूर्ण;

क्रमागत ltc3589_reg अणु
	LTC3589_SW1,
	LTC3589_SW2,
	LTC3589_SW3,
	LTC3589_BB_OUT,
	LTC3589_LDO1,
	LTC3589_LDO2,
	LTC3589_LDO3,
	LTC3589_LDO4,
	LTC3589_NUM_REGULATORS,
पूर्ण;

काष्ठा ltc3589 अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	क्रमागत ltc3589_variant variant;
	काष्ठा regulator_desc regulator_descs[LTC3589_NUM_REGULATORS];
	काष्ठा regulator_dev *regulators[LTC3589_NUM_REGULATORS];
पूर्ण;

अटल स्थिर पूर्णांक ltc3589_lकरो4[] = अणु
	2800000, 2500000, 1800000, 3300000,
पूर्ण;

अटल स्थिर पूर्णांक ltc3589_12_lकरो4[] = अणु
	1200000, 1800000, 2500000, 3200000,
पूर्ण;

अटल पूर्णांक ltc3589_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	काष्ठा ltc3589 *ltc3589 = rdev_get_drvdata(rdev);
	पूर्णांक sel, shअगरt;

	अगर (unlikely(ramp_delay <= 0))
		वापस -EINVAL;

	/* VRRCR slew rate offsets are the same as VCCR go bit offsets */
	shअगरt = ffs(rdev->desc->apply_bit) - 1;

	/* The slew rate can be set to 0.88, 1.75, 3.5, or 7 mV/uS */
	क्रम (sel = 0; sel < 4; sel++) अणु
		अगर ((880 << sel) >= ramp_delay) अणु
			वापस regmap_update_bits(ltc3589->regmap,
						  LTC3589_VRRCR,
						  0x3 << shअगरt, sel << shअगरt);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltc3589_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा ltc3589 *ltc3589 = rdev_get_drvdata(rdev);
	पूर्णांक sel;

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	/* DTV2 रेजिस्टर follows right after the corresponding DTV1 रेजिस्टर */
	वापस regmap_update_bits(ltc3589->regmap, rdev->desc->vsel_reg + 1,
				  rdev->desc->vsel_mask, sel);
पूर्ण

अटल पूर्णांक ltc3589_set_suspend_mode(काष्ठा regulator_dev *rdev,
				    अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ltc3589 *ltc3589 = rdev_get_drvdata(rdev);
	पूर्णांक mask, bit = 0;

	/* VCCR reference selects are right next to the VCCR go bits */
	mask = rdev->desc->apply_bit << 1;

	अगर (mode == REGULATOR_MODE_STANDBY)
		bit = mask;	/* Select DTV2 */

	mask |= rdev->desc->apply_bit;
	bit |= rdev->desc->apply_bit;
	वापस regmap_update_bits(ltc3589->regmap, LTC3589_VCCR, mask, bit);
पूर्ण

/* SW1, SW2, SW3, LDO2 */
अटल स्थिर काष्ठा regulator_ops ltc3589_linear_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_ramp_delay = ltc3589_set_ramp_delay,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_suspend_voltage = ltc3589_set_suspend_voltage,
	.set_suspend_mode = ltc3589_set_suspend_mode,
पूर्ण;

/* BB_OUT, LDO3 */
अटल स्थिर काष्ठा regulator_ops ltc3589_fixed_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

/* LDO1 */
अटल स्थिर काष्ठा regulator_ops ltc3589_fixed_standby_regulator_ops = अणु
पूर्ण;

/* LDO4 */
अटल स्थिर काष्ठा regulator_ops ltc3589_table_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_table,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक ltc3589_scale(अचिन्हित पूर्णांक uV, u32 r1, u32 r2)
अणु
	uपूर्णांक64_t पंचांगp;

	अगर (uV == 0)
		वापस 0;

	पंचांगp = (uपूर्णांक64_t)uV * r1;
	करो_भाग(पंचांगp, r2);
	वापस uV + (अचिन्हित पूर्णांक)पंचांगp;
पूर्ण

अटल पूर्णांक ltc3589_of_parse_cb(काष्ठा device_node *np,
			       स्थिर काष्ठा regulator_desc *desc,
			       काष्ठा regulator_config *config)
अणु
	काष्ठा ltc3589 *ltc3589 = config->driver_data;
	काष्ठा regulator_desc *rdesc = &ltc3589->regulator_descs[desc->id];
	u32 r[2];
	पूर्णांक ret;

	/* Parse feedback voltage भागiders. LDO3 and LDO4 करोn't have them */
	अगर (desc->id >= LTC3589_LDO3)
		वापस 0;

	ret = of_property_पढ़ो_u32_array(np, "lltc,fb-voltage-divider", r, 2);
	अगर (ret) अणु
		dev_err(ltc3589->dev, "Failed to parse voltage divider: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (!r[0] || !r[1])
		वापस 0;

	rdesc->min_uV = ltc3589_scale(desc->min_uV, r[0], r[1]);
	rdesc->uV_step = ltc3589_scale(desc->uV_step, r[0], r[1]);
	rdesc->fixed_uV = ltc3589_scale(desc->fixed_uV, r[0], r[1]);

	वापस 0;
पूर्ण

#घोषणा LTC3589_REG(_name, _of_name, _ops, en_bit, dtv1_reg, dtv_mask, go_bit)\
	[LTC3589_ ## _name] = अणु						\
		.name = #_name,						\
		.of_match = of_match_ptr(#_of_name),			\
		.regulators_node = of_match_ptr("regulators"),		\
		.of_parse_cb = ltc3589_of_parse_cb,			\
		.n_voltages = (dtv_mask) + 1,				\
		.min_uV = (go_bit) ? 362500 : 0,			\
		.uV_step = (go_bit) ? 12500 : 0,			\
		.ramp_delay = (go_bit) ? 1750 : 0,			\
		.fixed_uV = (dtv_mask) ? 0 : 800000,			\
		.ops = &ltc3589_ ## _ops ## _regulator_ops,		\
		.type = REGULATOR_VOLTAGE,				\
		.id = LTC3589_ ## _name,				\
		.owner = THIS_MODULE,					\
		.vsel_reg = (dtv1_reg),					\
		.vsel_mask = (dtv_mask),				\
		.apply_reg = (go_bit) ? LTC3589_VCCR : 0,		\
		.apply_bit = (go_bit),					\
		.enable_reg = (en_bit) ? LTC3589_OVEN : 0,		\
		.enable_mask = (en_bit),				\
	पूर्ण

#घोषणा LTC3589_LINEAR_REG(_name, _of_name, _dtv1)			\
	LTC3589_REG(_name, _of_name, linear, LTC3589_OVEN_ ## _name,	\
		    LTC3589_ ## _dtv1, 0x1f,				\
		    LTC3589_VCCR_ ## _name ## _GO)

#घोषणा LTC3589_FIXED_REG(_name, _of_name)				\
	LTC3589_REG(_name, _of_name, fixed, LTC3589_OVEN_ ## _name, 0, 0, 0)

अटल स्थिर काष्ठा regulator_desc ltc3589_regulators[] = अणु
	LTC3589_LINEAR_REG(SW1, sw1, B1DTV1),
	LTC3589_LINEAR_REG(SW2, sw2, B2DTV1),
	LTC3589_LINEAR_REG(SW3, sw3, B3DTV1),
	LTC3589_FIXED_REG(BB_OUT, bb-out),
	LTC3589_REG(LDO1, lकरो1, fixed_standby, 0, 0, 0, 0),
	LTC3589_LINEAR_REG(LDO2, lकरो2, L2DTV1),
	LTC3589_FIXED_REG(LDO3, lकरो3),
	LTC3589_REG(LDO4, lकरो4, table, LTC3589_OVEN_LDO4, LTC3589_L2DTV2,
		    0x60, 0),
पूर्ण;

अटल bool ltc3589_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LTC3589_IRQSTAT:
	हाल LTC3589_SCR1:
	हाल LTC3589_OVEN:
	हाल LTC3589_SCR2:
	हाल LTC3589_VCCR:
	हाल LTC3589_CLIRQ:
	हाल LTC3589_B1DTV1:
	हाल LTC3589_B1DTV2:
	हाल LTC3589_VRRCR:
	हाल LTC3589_B2DTV1:
	हाल LTC3589_B2DTV2:
	हाल LTC3589_B3DTV1:
	हाल LTC3589_B3DTV2:
	हाल LTC3589_L2DTV1:
	हाल LTC3589_L2DTV2:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool ltc3589_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LTC3589_IRQSTAT:
	हाल LTC3589_SCR1:
	हाल LTC3589_OVEN:
	हाल LTC3589_SCR2:
	हाल LTC3589_PGSTAT:
	हाल LTC3589_VCCR:
	हाल LTC3589_B1DTV1:
	हाल LTC3589_B1DTV2:
	हाल LTC3589_VRRCR:
	हाल LTC3589_B2DTV1:
	हाल LTC3589_B2DTV2:
	हाल LTC3589_B3DTV1:
	हाल LTC3589_B3DTV2:
	हाल LTC3589_L2DTV1:
	हाल LTC3589_L2DTV2:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool ltc3589_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LTC3589_IRQSTAT:
	हाल LTC3589_PGSTAT:
	हाल LTC3589_VCCR:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा reg_शेष ltc3589_reg_शेषs[] = अणु
	अणु LTC3589_SCR1,   0x00 पूर्ण,
	अणु LTC3589_OVEN,   0x00 पूर्ण,
	अणु LTC3589_SCR2,   0x00 पूर्ण,
	अणु LTC3589_VCCR,   0x00 पूर्ण,
	अणु LTC3589_B1DTV1, 0x19 पूर्ण,
	अणु LTC3589_B1DTV2, 0x19 पूर्ण,
	अणु LTC3589_VRRCR,  0xff पूर्ण,
	अणु LTC3589_B2DTV1, 0x19 पूर्ण,
	अणु LTC3589_B2DTV2, 0x19 पूर्ण,
	अणु LTC3589_B3DTV1, 0x19 पूर्ण,
	अणु LTC3589_B3DTV2, 0x19 पूर्ण,
	अणु LTC3589_L2DTV1, 0x19 पूर्ण,
	अणु LTC3589_L2DTV2, 0x19 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ltc3589_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखोable_reg = ltc3589_ग_लिखोable_reg,
	.पढ़ोable_reg = ltc3589_पढ़ोable_reg,
	.अस्थिर_reg = ltc3589_अस्थिर_reg,
	.max_रेजिस्टर = LTC3589_L2DTV2,
	.reg_शेषs = ltc3589_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ltc3589_reg_शेषs),
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल irqवापस_t ltc3589_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ltc3589 *ltc3589 = dev_id;
	अचिन्हित पूर्णांक i, irqstat, event;

	regmap_पढ़ो(ltc3589->regmap, LTC3589_IRQSTAT, &irqstat);

	अगर (irqstat & LTC3589_IRQSTAT_THERMAL_WARN) अणु
		event = REGULATOR_EVENT_OVER_TEMP;
		क्रम (i = 0; i < LTC3589_NUM_REGULATORS; i++)
			regulator_notअगरier_call_chain(ltc3589->regulators[i],
						      event, शून्य);
	पूर्ण

	अगर (irqstat & LTC3589_IRQSTAT_UNDERVOLT_WARN) अणु
		event = REGULATOR_EVENT_UNDER_VOLTAGE;
		क्रम (i = 0; i < LTC3589_NUM_REGULATORS; i++)
			regulator_notअगरier_call_chain(ltc3589->regulators[i],
						      event, शून्य);
	पूर्ण

	/* Clear warning condition */
	regmap_ग_लिखो(ltc3589->regmap, LTC3589_CLIRQ, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ltc3589_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा regulator_desc *descs;
	काष्ठा ltc3589 *ltc3589;
	पूर्णांक i, ret;

	ltc3589 = devm_kzalloc(dev, माप(*ltc3589), GFP_KERNEL);
	अगर (!ltc3589)
		वापस -ENOMEM;

	i2c_set_clientdata(client, ltc3589);
	अगर (client->dev.of_node)
		ltc3589->variant = (क्रमागत ltc3589_variant)
			of_device_get_match_data(&client->dev);
	अन्यथा
		ltc3589->variant = id->driver_data;
	ltc3589->dev = dev;

	descs = ltc3589->regulator_descs;
	स_नकल(descs, ltc3589_regulators, माप(ltc3589_regulators));
	अगर (ltc3589->variant == LTC3589) अणु
		descs[LTC3589_LDO3].fixed_uV = 1800000;
		descs[LTC3589_LDO4].volt_table = ltc3589_lकरो4;
	पूर्ण अन्यथा अणु
		descs[LTC3589_LDO3].fixed_uV = 2800000;
		descs[LTC3589_LDO4].volt_table = ltc3589_12_lकरो4;
	पूर्ण

	ltc3589->regmap = devm_regmap_init_i2c(client, &ltc3589_regmap_config);
	अगर (IS_ERR(ltc3589->regmap)) अणु
		ret = PTR_ERR(ltc3589->regmap);
		dev_err(dev, "failed to initialize regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < LTC3589_NUM_REGULATORS; i++) अणु
		काष्ठा regulator_desc *desc = &ltc3589->regulator_descs[i];
		काष्ठा regulator_config config = अणु पूर्ण;

		config.dev = dev;
		config.driver_data = ltc3589;

		ltc3589->regulators[i] = devm_regulator_रेजिस्टर(dev, desc,
								 &config);
		अगर (IS_ERR(ltc3589->regulators[i])) अणु
			ret = PTR_ERR(ltc3589->regulators[i]);
			dev_err(dev, "failed to register regulator %s: %d\n",
				desc->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						ltc3589_isr,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						client->name, ltc3589);
		अगर (ret) अणु
			dev_err(dev, "Failed to request IRQ: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc3589_i2c_id[] = अणु
	अणु "ltc3589",   LTC3589   पूर्ण,
	अणु "ltc3589-1", LTC3589_1 पूर्ण,
	अणु "ltc3589-2", LTC3589_2 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc3589_i2c_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ltc3589_of_match[] = अणु
	अणु
		.compatible = "lltc,ltc3589",
		.data = (व्योम *)LTC3589,
	पूर्ण,
	अणु
		.compatible = "lltc,ltc3589-1",
		.data = (व्योम *)LTC3589_1,
	पूर्ण,
	अणु
		.compatible = "lltc,ltc3589-2",
		.data = (व्योम *)LTC3589_2,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc3589_of_match);

अटल काष्ठा i2c_driver ltc3589_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = of_match_ptr(ltc3589_of_match),
	पूर्ण,
	.probe = ltc3589_probe,
	.id_table = ltc3589_i2c_id,
पूर्ण;
module_i2c_driver(ltc3589_driver);

MODULE_AUTHOR("Philipp Zabel <p.zabel@pengutronix.de>");
MODULE_DESCRIPTION("Regulator driver for Linear Technology LTC3589(-1,2)");
MODULE_LICENSE("GPL v2");
