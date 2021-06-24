<शैली गुरु>
/*
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Author: Andrew F. Davis <afd@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 *
 * Based on the TPS65912 driver
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>

#समावेश <linux/mfd/tps65086.h>

क्रमागत tps65086_regulators अणु BUCK1, BUCK2, BUCK3, BUCK4, BUCK5, BUCK6, LDOA1,
	LDOA2, LDOA3, SWA1, SWB1, SWB2, VTT पूर्ण;

#घोषणा TPS65086_REGULATOR(_name, _of, _id, _nv, _vr, _vm, _er, _em, _lr, _dr, _dm)	\
	[_id] = अणु							\
		.desc = अणु						\
			.name			= _name,		\
			.of_match		= of_match_ptr(_of),	\
			.regulators_node	= "regulators",		\
			.of_parse_cb		= tps65086_of_parse_cb,	\
			.id			= _id,			\
			.ops			= &reg_ops,		\
			.n_voltages		= _nv,			\
			.type			= REGULATOR_VOLTAGE,	\
			.owner			= THIS_MODULE,		\
			.vsel_reg		= _vr,			\
			.vsel_mask		= _vm,			\
			.enable_reg		= _er,			\
			.enable_mask		= _em,			\
			.volt_table		= शून्य,			\
			.linear_ranges		= _lr,			\
			.n_linear_ranges	= ARRAY_SIZE(_lr),	\
		पूर्ण,							\
		.decay_reg = _dr,					\
		.decay_mask = _dm,					\
	पूर्ण

#घोषणा TPS65086_SWITCH(_name, _of, _id, _er, _em)			\
	[_id] = अणु							\
		.desc = अणु						\
			.name			= _name,		\
			.of_match		= of_match_ptr(_of),	\
			.regulators_node	= "regulators",		\
			.of_parse_cb		= tps65086_of_parse_cb,	\
			.id			= _id,			\
			.ops			= &चयन_ops,		\
			.type			= REGULATOR_VOLTAGE,	\
			.owner			= THIS_MODULE,		\
			.enable_reg		= _er,			\
			.enable_mask		= _em,			\
		पूर्ण,							\
	पूर्ण

काष्ठा tps65086_regulator अणु
	काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक decay_reg;
	अचिन्हित पूर्णांक decay_mask;
पूर्ण;

अटल स्थिर काष्ठा linear_range tps65086_10mv_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0x0, 0x0, 0),
	REGULATOR_LINEAR_RANGE(410000, 0x1, 0x7F, 10000),
पूर्ण;

अटल स्थिर काष्ठा linear_range tps65086_buck126_25mv_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0x0, 0x0, 0),
	REGULATOR_LINEAR_RANGE(1000000, 0x1, 0x18, 0),
	REGULATOR_LINEAR_RANGE(1025000, 0x19, 0x7F, 25000),
पूर्ण;

अटल स्थिर काष्ठा linear_range tps65086_buck345_25mv_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0x0, 0x0, 0),
	REGULATOR_LINEAR_RANGE(425000, 0x1, 0x7F, 25000),
पूर्ण;

अटल स्थिर काष्ठा linear_range tps65086_lकरोa1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1350000, 0x0, 0x0, 0),
	REGULATOR_LINEAR_RANGE(1500000, 0x1, 0x7, 100000),
	REGULATOR_LINEAR_RANGE(2300000, 0x8, 0xB, 100000),
	REGULATOR_LINEAR_RANGE(2850000, 0xC, 0xD, 150000),
	REGULATOR_LINEAR_RANGE(3300000, 0xE, 0xE, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range tps65086_lकरोa23_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(700000, 0x0, 0xD, 50000),
	REGULATOR_LINEAR_RANGE(1400000, 0xE, 0xF, 100000),
पूर्ण;

/* Operations permitted on regulators */
अटल स्थिर काष्ठा regulator_ops reg_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
पूर्ण;

/* Operations permitted on load चयनes */
अटल स्थिर काष्ठा regulator_ops चयन_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
पूर्ण;

अटल पूर्णांक tps65086_of_parse_cb(काष्ठा device_node *dev,
				स्थिर काष्ठा regulator_desc *desc,
				काष्ठा regulator_config *config);

अटल काष्ठा tps65086_regulator regulators[] = अणु
	TPS65086_REGULATOR("BUCK1", "buck1", BUCK1, 0x80, TPS65086_BUCK1CTRL,
			   BUCK_VID_MASK, TPS65086_BUCK123CTRL, BIT(0),
			   tps65086_10mv_ranges, TPS65086_BUCK1CTRL,
			   BIT(0)),
	TPS65086_REGULATOR("BUCK2", "buck2", BUCK2, 0x80, TPS65086_BUCK2CTRL,
			   BUCK_VID_MASK, TPS65086_BUCK123CTRL, BIT(1),
			   tps65086_10mv_ranges, TPS65086_BUCK2CTRL,
			   BIT(0)),
	TPS65086_REGULATOR("BUCK3", "buck3", BUCK3, 0x80, TPS65086_BUCK3VID,
			   BUCK_VID_MASK, TPS65086_BUCK123CTRL, BIT(2),
			   tps65086_10mv_ranges, TPS65086_BUCK3DECAY,
			   BIT(0)),
	TPS65086_REGULATOR("BUCK4", "buck4", BUCK4, 0x80, TPS65086_BUCK4VID,
			   BUCK_VID_MASK, TPS65086_BUCK4CTRL, BIT(0),
			   tps65086_10mv_ranges, TPS65086_BUCK4VID,
			   BIT(0)),
	TPS65086_REGULATOR("BUCK5", "buck5", BUCK5, 0x80, TPS65086_BUCK5VID,
			   BUCK_VID_MASK, TPS65086_BUCK5CTRL, BIT(0),
			   tps65086_10mv_ranges, TPS65086_BUCK5CTRL,
			   BIT(0)),
	TPS65086_REGULATOR("BUCK6", "buck6", BUCK6, 0x80, TPS65086_BUCK6VID,
			   BUCK_VID_MASK, TPS65086_BUCK6CTRL, BIT(0),
			   tps65086_10mv_ranges, TPS65086_BUCK6CTRL,
			   BIT(0)),
	TPS65086_REGULATOR("LDOA1", "ldoa1", LDOA1, 0xF, TPS65086_LDOA1CTRL,
			   VDOA1_VID_MASK, TPS65086_LDOA1CTRL, BIT(0),
			   tps65086_lकरोa1_ranges, 0, 0),
	TPS65086_REGULATOR("LDOA2", "ldoa2", LDOA2, 0x10, TPS65086_LDOA2VID,
			   VDOA23_VID_MASK, TPS65086_LDOA2CTRL, BIT(0),
			   tps65086_lकरोa23_ranges, 0, 0),
	TPS65086_REGULATOR("LDOA3", "ldoa3", LDOA3, 0x10, TPS65086_LDOA3VID,
			   VDOA23_VID_MASK, TPS65086_LDOA3CTRL, BIT(0),
			   tps65086_lकरोa23_ranges, 0, 0),
	TPS65086_SWITCH("SWA1", "swa1", SWA1, TPS65086_SWVTT_EN, BIT(5)),
	TPS65086_SWITCH("SWB1", "swb1", SWB1, TPS65086_SWVTT_EN, BIT(6)),
	TPS65086_SWITCH("SWB2", "swb2", SWB2, TPS65086_SWVTT_EN, BIT(7)),
	TPS65086_SWITCH("VTT", "vtt", VTT, TPS65086_SWVTT_EN, BIT(4)),
पूर्ण;

अटल पूर्णांक tps65086_of_parse_cb(काष्ठा device_node *node,
				स्थिर काष्ठा regulator_desc *desc,
				काष्ठा regulator_config *config)
अणु
	पूर्णांक ret;

	/* Check क्रम 25mV step mode */
	अगर (of_property_पढ़ो_bool(node, "ti,regulator-step-size-25mv")) अणु
		चयन (desc->id) अणु
		हाल BUCK1:
		हाल BUCK2:
		हाल BUCK6:
			regulators[desc->id].desc.linear_ranges =
				tps65086_buck126_25mv_ranges;
			regulators[desc->id].desc.n_linear_ranges =
				ARRAY_SIZE(tps65086_buck126_25mv_ranges);
			अवरोध;
		हाल BUCK3:
		हाल BUCK4:
		हाल BUCK5:
			regulators[desc->id].desc.linear_ranges =
				tps65086_buck345_25mv_ranges;
			regulators[desc->id].desc.n_linear_ranges =
				ARRAY_SIZE(tps65086_buck345_25mv_ranges);
			अवरोध;
		शेष:
			dev_warn(config->dev, "25mV step mode only valid for BUCK regulators\n");
		पूर्ण
	पूर्ण

	/* Check क्रम decay mode */
	अगर (desc->id <= BUCK6 && of_property_पढ़ो_bool(node, "ti,regulator-decay")) अणु
		ret = regmap_ग_लिखो_bits(config->regmap,
					regulators[desc->id].decay_reg,
					regulators[desc->id].decay_mask,
					regulators[desc->id].decay_mask);
		अगर (ret) अणु
			dev_err(config->dev, "Error setting decay\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65086_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65086 *tps = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	platक्रमm_set_drvdata(pdev, tps);

	config.dev = &pdev->dev;
	config.dev->of_node = tps->dev->of_node;
	config.driver_data = tps;
	config.regmap = tps->regmap;

	क्रम (i = 0; i < ARRAY_SIZE(regulators); i++) अणु
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[i].desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(tps->dev, "failed to register %s regulator\n",
				pdev->name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id tps65086_regulator_id_table[] = अणु
	अणु "tps65086-regulator", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, tps65086_regulator_id_table);

अटल काष्ठा platक्रमm_driver tps65086_regulator_driver = अणु
	.driver = अणु
		.name = "tps65086-regulator",
	पूर्ण,
	.probe = tps65086_regulator_probe,
	.id_table = tps65086_regulator_id_table,
पूर्ण;
module_platक्रमm_driver(tps65086_regulator_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TPS65086 Regulator driver");
MODULE_LICENSE("GPL v2");
