<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2019 five technologies GmbH
// Author: Markus Reichl <m.reichl@fivetechno.de>

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regmap.h>


#घोषणा VOL_MIN_IDX			0x00
#घोषणा VOL_MAX_IDX			0x7ff

/* Register definitions */
#घोषणा MP8859_VOUT_L_REG		0    //3 lo Bits
#घोषणा MP8859_VOUT_H_REG		1    //8 hi Bits
#घोषणा MP8859_VOUT_GO_REG		2
#घोषणा MP8859_IOUT_LIM_REG		3
#घोषणा MP8859_CTL1_REG			4
#घोषणा MP8859_CTL2_REG			5
#घोषणा MP8859_RESERVED1_REG		6
#घोषणा MP8859_RESERVED2_REG		7
#घोषणा MP8859_RESERVED3_REG		8
#घोषणा MP8859_STATUS_REG		9
#घोषणा MP8859_INTERRUPT_REG		0x0A
#घोषणा MP8859_MASK_REG			0x0B
#घोषणा MP8859_ID1_REG			0x0C
#घोषणा MP8859_MFR_ID_REG		0x27
#घोषणा MP8859_DEV_ID_REG		0x28
#घोषणा MP8859_IC_REV_REG		0x29

#घोषणा MP8859_MAX_REG			0x29

#घोषणा MP8859_GO_BIT			0x01


अटल पूर्णांक mp8859_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक sel)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(rdev->regmap, MP8859_VOUT_L_REG, sel & 0x7);

	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(rdev->regmap, MP8859_VOUT_H_REG, sel >> 3);

	अगर (ret)
		वापस ret;
	ret = regmap_update_bits(rdev->regmap, MP8859_VOUT_GO_REG,
					MP8859_GO_BIT, 1);
	वापस ret;
पूर्ण

अटल पूर्णांक mp8859_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val_पंचांगp;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, MP8859_VOUT_H_REG, &val_पंचांगp);

	अगर (ret)
		वापस ret;
	val = val_पंचांगp << 3;

	ret = regmap_पढ़ो(rdev->regmap, MP8859_VOUT_L_REG, &val_पंचांगp);

	अगर (ret)
		वापस ret;
	val |= val_पंचांगp & 0x07;
	वापस val;
पूर्ण

अटल स्थिर काष्ठा linear_range mp8859_dcdc_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, VOL_MIN_IDX, VOL_MAX_IDX, 10000),
पूर्ण;

अटल स्थिर काष्ठा regmap_config mp8859_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MP8859_MAX_REG,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mp8859_ops = अणु
	.set_voltage_sel = mp8859_set_voltage_sel,
	.get_voltage_sel = mp8859_get_voltage_sel,
	.list_voltage = regulator_list_voltage_linear_range,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc mp8859_regulators[] = अणु
	अणु
		.id = 0,
		.type = REGULATOR_VOLTAGE,
		.name = "mp8859_dcdc",
		.supply_name = "vin",
		.of_match = of_match_ptr("mp8859_dcdc"),
		.n_voltages = VOL_MAX_IDX + 1,
		.linear_ranges = mp8859_dcdc_ranges,
		.n_linear_ranges = 1,
		.ops = &mp8859_ops,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mp8859_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	पूर्णांक ret;
	काष्ठा regulator_config config = अणु.dev = &i2c->devपूर्ण;
	काष्ठा regmap *regmap = devm_regmap_init_i2c(i2c, &mp8859_regmap);
	काष्ठा regulator_dev *rdev;

	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण
	rdev = devm_regulator_रेजिस्टर(&i2c->dev, &mp8859_regulators[0],
					&config);

	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(&i2c->dev, "failed to register %s: %d\n",
			mp8859_regulators[0].name, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mp8859_dt_id[] = अणु
	अणु.compatible =  "mps,mp8859"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mp8859_dt_id);

अटल स्थिर काष्ठा i2c_device_id mp8859_i2c_id[] = अणु
	अणु "mp8859", पूर्ण,
	अणु  पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mp8859_i2c_id);

अटल काष्ठा i2c_driver mp8859_regulator_driver = अणु
	.driver = अणु
		.name = "mp8859",
		.of_match_table = of_match_ptr(mp8859_dt_id),
	पूर्ण,
	.probe_new = mp8859_i2c_probe,
	.id_table = mp8859_i2c_id,
पूर्ण;

module_i2c_driver(mp8859_regulator_driver);

MODULE_DESCRIPTION("Monolithic Power Systems MP8859 voltage regulator driver");
MODULE_AUTHOR("Markus Reichl <m.reichl@fivetechno.de>");
MODULE_LICENSE("GPL v2");
