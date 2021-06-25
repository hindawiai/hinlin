<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Gateworks Corporation, Inc. All Rights Reserved.
 */
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा DRIVER_NAME		"ltc3676"

/* LTC3676 Registers */
#घोषणा LTC3676_BUCK1     0x01
#घोषणा LTC3676_BUCK2     0x02
#घोषणा LTC3676_BUCK3     0x03
#घोषणा LTC3676_BUCK4     0x04
#घोषणा LTC3676_LDOA      0x05
#घोषणा LTC3676_LDOB      0x06
#घोषणा LTC3676_SQD1      0x07
#घोषणा LTC3676_SQD2      0x08
#घोषणा LTC3676_CNTRL     0x09
#घोषणा LTC3676_DVB1A     0x0A
#घोषणा LTC3676_DVB1B     0x0B
#घोषणा LTC3676_DVB2A     0x0C
#घोषणा LTC3676_DVB2B     0x0D
#घोषणा LTC3676_DVB3A     0x0E
#घोषणा LTC3676_DVB3B     0x0F
#घोषणा LTC3676_DVB4A     0x10
#घोषणा LTC3676_DVB4B     0x11
#घोषणा LTC3676_MSKIRQ    0x12
#घोषणा LTC3676_MSKPG     0x13
#घोषणा LTC3676_USER      0x14
#घोषणा LTC3676_IRQSTAT   0x15
#घोषणा LTC3676_PGSTATL   0x16
#घोषणा LTC3676_PGSTATRT  0x17
#घोषणा LTC3676_HRST      0x1E
#घोषणा LTC3676_CLIRQ     0x1F

#घोषणा LTC3676_DVBxA_REF_SELECT	BIT(5)
#घोषणा LTC3676_DVBxB_PGOOD_MASK	BIT(5)

#घोषणा LTC3676_IRQSTAT_PGOOD_TIMEOUT	BIT(3)
#घोषणा LTC3676_IRQSTAT_UNDERVOLT_WARN	BIT(4)
#घोषणा LTC3676_IRQSTAT_UNDERVOLT_FAULT	BIT(5)
#घोषणा LTC3676_IRQSTAT_THERMAL_WARN	BIT(6)
#घोषणा LTC3676_IRQSTAT_THERMAL_FAULT	BIT(7)

क्रमागत ltc3676_reg अणु
	LTC3676_SW1,
	LTC3676_SW2,
	LTC3676_SW3,
	LTC3676_SW4,
	LTC3676_LDO1,
	LTC3676_LDO2,
	LTC3676_LDO3,
	LTC3676_LDO4,
	LTC3676_NUM_REGULATORS,
पूर्ण;

काष्ठा ltc3676 अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा regulator_desc regulator_descs[LTC3676_NUM_REGULATORS];
	काष्ठा regulator_dev *regulators[LTC3676_NUM_REGULATORS];
पूर्ण;

अटल पूर्णांक ltc3676_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा ltc3676 *ltc3676 = rdev_get_drvdata(rdev);
	काष्ठा device *dev = ltc3676->dev;
	पूर्णांक dcdc = rdev_get_id(rdev);
	पूर्णांक sel;

	dev_dbg(dev, "%s id=%d uV=%d\n", __func__, dcdc, uV);
	sel = regulator_map_voltage_linear(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	/* DVBB रेजिस्टर follows right after the corresponding DVBA रेजिस्टर */
	वापस regmap_update_bits(ltc3676->regmap, rdev->desc->vsel_reg + 1,
				  rdev->desc->vsel_mask, sel);
पूर्ण

अटल पूर्णांक ltc3676_set_suspend_mode(काष्ठा regulator_dev *rdev,
				    अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ltc3676 *ltc3676= rdev_get_drvdata(rdev);
	काष्ठा device *dev = ltc3676->dev;
	पूर्णांक mask, val;
	पूर्णांक dcdc = rdev_get_id(rdev);

	dev_dbg(dev, "%s id=%d mode=%d\n", __func__, dcdc, mode);

	mask = LTC3676_DVBxA_REF_SELECT;
	चयन (mode) अणु
	हाल REGULATOR_MODE_STANDBY:
		val = 0; /* select DVBxA */
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = LTC3676_DVBxA_REF_SELECT; /* select DVBxB */
		अवरोध;
	शेष:
		dev_warn(&rdev->dev, "%s: regulator mode: 0x%x not supported\n",
			 rdev->desc->name, mode);
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(ltc3676->regmap, rdev->desc->vsel_reg,
				  mask, val);
पूर्ण

अटल पूर्णांक ltc3676_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित selector)
अणु
	काष्ठा ltc3676 *ltc3676 = rdev_get_drvdata(rdev);
	काष्ठा device *dev = ltc3676->dev;
	पूर्णांक ret, dcdc = rdev_get_id(rdev);

	dev_dbg(dev, "%s id=%d selector=%d\n", __func__, dcdc, selector);

	ret = regmap_update_bits(ltc3676->regmap, rdev->desc->vsel_reg + 1,
				 LTC3676_DVBxB_PGOOD_MASK,
				 LTC3676_DVBxB_PGOOD_MASK);
	अगर (ret)
		वापस ret;

	वापस regulator_set_voltage_sel_regmap(rdev, selector);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ltc3676_scale(अचिन्हित पूर्णांक uV, u32 r1, u32 r2)
अणु
	uपूर्णांक64_t पंचांगp;
	अगर (uV == 0)
		वापस 0;
	पंचांगp = (uपूर्णांक64_t)uV * r1;
	करो_भाग(पंचांगp, r2);
	वापस uV + (अचिन्हित पूर्णांक)पंचांगp;
पूर्ण

अटल पूर्णांक ltc3676_of_parse_cb(काष्ठा device_node *np,
			       स्थिर काष्ठा regulator_desc *desc,
			       काष्ठा regulator_config *config)
अणु
	काष्ठा ltc3676 *ltc3676 = config->driver_data;
	काष्ठा regulator_desc *rdesc = &ltc3676->regulator_descs[desc->id];
	u32 r[2];
	पूर्णांक ret;

	/* LDO3 has a fixed output */
	अगर (desc->id == LTC3676_LDO3)
		वापस 0;

	ret = of_property_पढ़ो_u32_array(np, "lltc,fb-voltage-divider", r, 2);
	अगर (ret) अणु
		dev_err(ltc3676->dev, "Failed to parse voltage divider: %d\n",
			ret);
		वापस ret;
	पूर्ण

	rdesc->min_uV = ltc3676_scale(desc->min_uV, r[0], r[1]);
	rdesc->uV_step = ltc3676_scale(desc->uV_step, r[0], r[1]);
	rdesc->fixed_uV = ltc3676_scale(desc->fixed_uV, r[0], r[1]);

	वापस 0;
पूर्ण

/* SW1, SW2, SW3, SW4 linear 0.8V-3.3V with scalar via R1/R2 feeback res */
अटल स्थिर काष्ठा regulator_ops ltc3676_linear_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = ltc3676_set_voltage_sel,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_suspend_voltage = ltc3676_set_suspend_voltage,
	.set_suspend_mode = ltc3676_set_suspend_mode,
पूर्ण;

/* LDO1 always on fixed 0.8V-3.3V via scalar via R1/R2 feeback res */
अटल स्थिर काष्ठा regulator_ops ltc3676_fixed_standby_regulator_ops = अणु
पूर्ण;

/* LDO2, LDO3 fixed (LDO2 has बाह्यal scalar via R1/R2 feedback res) */
अटल स्थिर काष्ठा regulator_ops ltc3676_fixed_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

#घोषणा LTC3676_REG(_id, _name, _ops, en_reg, en_bit, dvba_reg, dvb_mask)   \
	[LTC3676_ ## _id] = अणु                                        \
		.name = #_name,                                \
		.of_match = of_match_ptr(#_name),              \
		.regulators_node = of_match_ptr("regulators"), \
		.of_parse_cb = ltc3676_of_parse_cb,            \
		.n_voltages = (dvb_mask) + 1,                  \
		.min_uV = (dvba_reg) ? 412500 : 0,             \
		.uV_step = (dvba_reg) ? 12500 : 0,             \
		.ramp_delay = (dvba_reg) ? 800 : 0,            \
		.fixed_uV = (dvb_mask) ? 0 : 725000,           \
		.ops = &ltc3676_ ## _ops ## _regulator_ops,    \
		.type = REGULATOR_VOLTAGE,                     \
		.id = LTC3676_ ## _id,                         \
		.owner = THIS_MODULE,                          \
		.vsel_reg = (dvba_reg),                        \
		.vsel_mask = (dvb_mask),                       \
		.enable_reg = (en_reg),                        \
		.enable_mask = (1 << en_bit),                  \
	पूर्ण

#घोषणा LTC3676_LINEAR_REG(_id, _name, _en, _dvba)                     \
	LTC3676_REG(_id, _name, linear,                                \
		    LTC3676_ ## _en, 7,                                \
		    LTC3676_ ## _dvba, 0x1f)

#घोषणा LTC3676_FIXED_REG(_id, _name, _en_reg, _en_bit)                \
	LTC3676_REG(_id, _name, fixed, LTC3676_ ## _en_reg, _en_bit, 0, 0)

अटल स्थिर काष्ठा regulator_desc ltc3676_regulators[LTC3676_NUM_REGULATORS] = अणु
	LTC3676_LINEAR_REG(SW1, sw1, BUCK1, DVB1A),
	LTC3676_LINEAR_REG(SW2, sw2, BUCK2, DVB2A),
	LTC3676_LINEAR_REG(SW3, sw3, BUCK3, DVB3A),
	LTC3676_LINEAR_REG(SW4, sw4, BUCK4, DVB4A),
	LTC3676_REG(LDO1, lकरो1, fixed_standby, 0, 0, 0, 0),
	LTC3676_FIXED_REG(LDO2, lकरो2, LDOA, 2),
	LTC3676_FIXED_REG(LDO3, lकरो3, LDOA, 5),
	LTC3676_FIXED_REG(LDO4, lकरो4, LDOB, 2),
पूर्ण;

अटल bool ltc3676_पढ़ोable_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LTC3676_BUCK1 ... LTC3676_IRQSTAT:
	हाल LTC3676_HRST:
	हाल LTC3676_CLIRQ:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool ltc3676_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LTC3676_IRQSTAT ... LTC3676_PGSTATRT:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config ltc3676_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखोable_reg = ltc3676_पढ़ोable_ग_लिखोable_reg,
	.पढ़ोable_reg = ltc3676_पढ़ोable_ग_लिखोable_reg,
	.अस्थिर_reg = ltc3676_अस्थिर_reg,
	.max_रेजिस्टर = LTC3676_CLIRQ,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल irqवापस_t ltc3676_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ltc3676 *ltc3676 = dev_id;
	काष्ठा device *dev = ltc3676->dev;
	अचिन्हित पूर्णांक i, irqstat, event;

	regmap_पढ़ो(ltc3676->regmap, LTC3676_IRQSTAT, &irqstat);

	dev_dbg(dev, "irq%d irqstat=0x%02x\n", irq, irqstat);
	अगर (irqstat & LTC3676_IRQSTAT_THERMAL_WARN) अणु
		dev_warn(dev, "Over-temperature Warning\n");
		event = REGULATOR_EVENT_OVER_TEMP;
		क्रम (i = 0; i < LTC3676_NUM_REGULATORS; i++)
			regulator_notअगरier_call_chain(ltc3676->regulators[i],
						      event, शून्य);
	पूर्ण

	अगर (irqstat & LTC3676_IRQSTAT_UNDERVOLT_WARN) अणु
		dev_info(dev, "Undervoltage Warning\n");
		event = REGULATOR_EVENT_UNDER_VOLTAGE;
		क्रम (i = 0; i < LTC3676_NUM_REGULATORS; i++)
			regulator_notअगरier_call_chain(ltc3676->regulators[i],
						      event, शून्य);
	पूर्ण

	/* Clear warning condition */
	regmap_ग_लिखो(ltc3676->regmap, LTC3676_CLIRQ, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ltc3676_regulator_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा regulator_init_data *init_data = dev_get_platdata(dev);
	काष्ठा regulator_desc *descs;
	काष्ठा ltc3676 *ltc3676;
	पूर्णांक i, ret;

	ltc3676 = devm_kzalloc(dev, माप(*ltc3676), GFP_KERNEL);
	अगर (!ltc3676)
		वापस -ENOMEM;

	i2c_set_clientdata(client, ltc3676);
	ltc3676->dev = dev;

	descs = ltc3676->regulator_descs;
	स_नकल(descs, ltc3676_regulators, माप(ltc3676_regulators));
	descs[LTC3676_LDO3].fixed_uV = 1800000; /* LDO3 is fixed 1.8V */

	ltc3676->regmap = devm_regmap_init_i2c(client, &ltc3676_regmap_config);
	अगर (IS_ERR(ltc3676->regmap)) अणु
		ret = PTR_ERR(ltc3676->regmap);
		dev_err(dev, "failed to initialize regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < LTC3676_NUM_REGULATORS; i++) अणु
		काष्ठा regulator_desc *desc = &ltc3676->regulator_descs[i];
		काष्ठा regulator_config config = अणु पूर्ण;

		अगर (init_data)
			config.init_data = &init_data[i];

		config.dev = dev;
		config.driver_data = ltc3676;

		ltc3676->regulators[i] = devm_regulator_रेजिस्टर(dev, desc,
								 &config);
		अगर (IS_ERR(ltc3676->regulators[i])) अणु
			ret = PTR_ERR(ltc3676->regulators[i]);
			dev_err(dev, "failed to register regulator %s: %d\n",
				desc->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	regmap_ग_लिखो(ltc3676->regmap, LTC3676_CLIRQ, 0);
	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						ltc3676_isr,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						client->name, ltc3676);
		अगर (ret) अणु
			dev_err(dev, "Failed to request IRQ: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc3676_i2c_id[] = अणु
	अणु "ltc3676" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc3676_i2c_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ltc3676_of_match[] = अणु
	अणु .compatible = "lltc,ltc3676" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc3676_of_match);

अटल काष्ठा i2c_driver ltc3676_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = of_match_ptr(ltc3676_of_match),
	पूर्ण,
	.probe_new = ltc3676_regulator_probe,
	.id_table = ltc3676_i2c_id,
पूर्ण;
module_i2c_driver(ltc3676_driver);

MODULE_AUTHOR("Tim Harvey <tharvey@gateworks.com>");
MODULE_DESCRIPTION("Regulator driver for Linear Technology LTC3676");
MODULE_LICENSE("GPL v2");
