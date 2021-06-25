<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम National Semiconductors LP3971 PMIC chip
 *
 *  Copyright (C) 2009 Samsung Electronics
 *  Author: Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Based on wm8350.c
 */

#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/lp3971.h>
#समावेश <linux/slab.h>

काष्ठा lp3971 अणु
	काष्ठा device *dev;
	काष्ठा mutex io_lock;
	काष्ठा i2c_client *i2c;
पूर्ण;

अटल u8 lp3971_reg_पढ़ो(काष्ठा lp3971 *lp3971, u8 reg);
अटल पूर्णांक lp3971_set_bits(काष्ठा lp3971 *lp3971, u8 reg, u16 mask, u16 val);

#घोषणा LP3971_SYS_CONTROL1_REG 0x07

/* System control रेजिस्टर 1 initial value,
   bits 4 and 5 are EPROM programmable */
#घोषणा SYS_CONTROL1_INIT_VAL 0x40
#घोषणा SYS_CONTROL1_INIT_MASK 0xCF

#घोषणा LP3971_BUCK_VOL_ENABLE_REG 0x10
#घोषणा LP3971_BUCK_VOL_CHANGE_REG 0x20

/*	Voltage control रेजिस्टरs shअगरt:
	LP3971_BUCK1 -> 0
	LP3971_BUCK2 -> 4
	LP3971_BUCK3 -> 6
*/
#घोषणा BUCK_VOL_CHANGE_SHIFT(x) (((!!x) << 2) | (x & ~0x01))
#घोषणा BUCK_VOL_CHANGE_FLAG_GO 0x01
#घोषणा BUCK_VOL_CHANGE_FLAG_TARGET 0x02
#घोषणा BUCK_VOL_CHANGE_FLAG_MASK 0x03

#घोषणा LP3971_BUCK1_BASE 0x23
#घोषणा LP3971_BUCK2_BASE 0x29
#घोषणा LP3971_BUCK3_BASE 0x32

अटल स्थिर पूर्णांक buck_base_addr[] = अणु
	LP3971_BUCK1_BASE,
	LP3971_BUCK2_BASE,
	LP3971_BUCK3_BASE,
पूर्ण;

#घोषणा LP3971_BUCK_TARGET_VOL1_REG(x) (buck_base_addr[x])
#घोषणा LP3971_BUCK_TARGET_VOL2_REG(x) (buck_base_addr[x]+1)

अटल स्थिर अचिन्हित पूर्णांक buck_voltage_map[] = अणु
	      0,  800000,  850000,  900000,  950000, 1000000, 1050000, 1100000,
	1150000, 1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000,
	1550000, 1600000, 1650000, 1700000, 1800000, 1900000, 2500000, 2800000,
	3000000, 3300000,
पूर्ण;

#घोषणा BUCK_TARGET_VOL_MASK 0x3f

#घोषणा LP3971_BUCK_RAMP_REG(x)	(buck_base_addr[x]+2)

#घोषणा LP3971_LDO_ENABLE_REG 0x12
#घोषणा LP3971_LDO_VOL_CONTR_BASE 0x39

/*	Voltage control रेजिस्टरs:
	LP3971_LDO1 -> LP3971_LDO_VOL_CONTR_BASE + 0
	LP3971_LDO2 -> LP3971_LDO_VOL_CONTR_BASE + 0
	LP3971_LDO3 -> LP3971_LDO_VOL_CONTR_BASE + 1
	LP3971_LDO4 -> LP3971_LDO_VOL_CONTR_BASE + 1
	LP3971_LDO5 -> LP3971_LDO_VOL_CONTR_BASE + 2
*/
#घोषणा LP3971_LDO_VOL_CONTR_REG(x)	(LP3971_LDO_VOL_CONTR_BASE + (x >> 1))

/*	Voltage control रेजिस्टरs shअगरt:
	LP3971_LDO1 -> 0, LP3971_LDO2 -> 4
	LP3971_LDO3 -> 0, LP3971_LDO4 -> 4
	LP3971_LDO5 -> 0
*/
#घोषणा LDO_VOL_CONTR_SHIFT(x) ((x & 1) << 2)
#घोषणा LDO_VOL_CONTR_MASK 0x0f

अटल स्थिर अचिन्हित पूर्णांक lकरो45_voltage_map[] = अणु
	1000000, 1050000, 1100000, 1150000, 1200000, 1250000, 1300000, 1350000,
	1400000, 1500000, 1800000, 1900000, 2500000, 2800000, 3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो123_voltage_map[] = अणु
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000, 3000000, 3100000, 3200000, 3300000,
पूर्ण;

#घोषणा LDO_VOL_MIN_IDX 0x00
#घोषणा LDO_VOL_MAX_IDX 0x0f

अटल पूर्णांक lp3971_lकरो_is_enabled(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3971_LDO1;
	u16 mask = 1 << (1 + lकरो);
	u16 val;

	val = lp3971_reg_पढ़ो(lp3971, LP3971_LDO_ENABLE_REG);
	वापस (val & mask) != 0;
पूर्ण

अटल पूर्णांक lp3971_lकरो_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3971_LDO1;
	u16 mask = 1 << (1 + lकरो);

	वापस lp3971_set_bits(lp3971, LP3971_LDO_ENABLE_REG, mask, mask);
पूर्ण

अटल पूर्णांक lp3971_lकरो_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3971_LDO1;
	u16 mask = 1 << (1 + lकरो);

	वापस lp3971_set_bits(lp3971, LP3971_LDO_ENABLE_REG, mask, 0);
पूर्ण

अटल पूर्णांक lp3971_lकरो_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3971_LDO1;
	u16 val, reg;

	reg = lp3971_reg_पढ़ो(lp3971, LP3971_LDO_VOL_CONTR_REG(lकरो));
	val = (reg >> LDO_VOL_CONTR_SHIFT(lकरो)) & LDO_VOL_CONTR_MASK;

	वापस val;
पूर्ण

अटल पूर्णांक lp3971_lकरो_set_voltage_sel(काष्ठा regulator_dev *dev,
				      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3971_LDO1;

	वापस lp3971_set_bits(lp3971, LP3971_LDO_VOL_CONTR_REG(lकरो),
			LDO_VOL_CONTR_MASK << LDO_VOL_CONTR_SHIFT(lकरो),
			selector << LDO_VOL_CONTR_SHIFT(lकरो));
पूर्ण

अटल स्थिर काष्ठा regulator_ops lp3971_lकरो_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.is_enabled = lp3971_lकरो_is_enabled,
	.enable = lp3971_lकरो_enable,
	.disable = lp3971_lकरो_disable,
	.get_voltage_sel = lp3971_lकरो_get_voltage_sel,
	.set_voltage_sel = lp3971_lकरो_set_voltage_sel,
पूर्ण;

अटल पूर्णांक lp3971_dcdc_is_enabled(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3971_DCDC1;
	u16 mask = 1 << (buck * 2);
	u16 val;

	val = lp3971_reg_पढ़ो(lp3971, LP3971_BUCK_VOL_ENABLE_REG);
	वापस (val & mask) != 0;
पूर्ण

अटल पूर्णांक lp3971_dcdc_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3971_DCDC1;
	u16 mask = 1 << (buck * 2);

	वापस lp3971_set_bits(lp3971, LP3971_BUCK_VOL_ENABLE_REG, mask, mask);
पूर्ण

अटल पूर्णांक lp3971_dcdc_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3971_DCDC1;
	u16 mask = 1 << (buck * 2);

	वापस lp3971_set_bits(lp3971, LP3971_BUCK_VOL_ENABLE_REG, mask, 0);
पूर्ण

अटल पूर्णांक lp3971_dcdc_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3971_DCDC1;
	u16 reg;

	reg = lp3971_reg_पढ़ो(lp3971, LP3971_BUCK_TARGET_VOL1_REG(buck));
	reg &= BUCK_TARGET_VOL_MASK;

	वापस reg;
पूर्ण

अटल पूर्णांक lp3971_dcdc_set_voltage_sel(काष्ठा regulator_dev *dev,
				       अचिन्हित पूर्णांक selector)
अणु
	काष्ठा lp3971 *lp3971 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3971_DCDC1;
	पूर्णांक ret;

	ret = lp3971_set_bits(lp3971, LP3971_BUCK_TARGET_VOL1_REG(buck),
	       BUCK_TARGET_VOL_MASK, selector);
	अगर (ret)
		वापस ret;

	ret = lp3971_set_bits(lp3971, LP3971_BUCK_VOL_CHANGE_REG,
	       BUCK_VOL_CHANGE_FLAG_MASK << BUCK_VOL_CHANGE_SHIFT(buck),
	       BUCK_VOL_CHANGE_FLAG_GO << BUCK_VOL_CHANGE_SHIFT(buck));
	अगर (ret)
		वापस ret;

	वापस lp3971_set_bits(lp3971, LP3971_BUCK_VOL_CHANGE_REG,
	       BUCK_VOL_CHANGE_FLAG_MASK << BUCK_VOL_CHANGE_SHIFT(buck),
	       0 << BUCK_VOL_CHANGE_SHIFT(buck));
पूर्ण

अटल स्थिर काष्ठा regulator_ops lp3971_dcdc_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.is_enabled = lp3971_dcdc_is_enabled,
	.enable = lp3971_dcdc_enable,
	.disable = lp3971_dcdc_disable,
	.get_voltage_sel = lp3971_dcdc_get_voltage_sel,
	.set_voltage_sel = lp3971_dcdc_set_voltage_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	अणु
		.name = "LDO1",
		.id = LP3971_LDO1,
		.ops = &lp3971_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो123_voltage_map),
		.volt_table = lकरो123_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO2",
		.id = LP3971_LDO2,
		.ops = &lp3971_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो123_voltage_map),
		.volt_table = lकरो123_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO3",
		.id = LP3971_LDO3,
		.ops = &lp3971_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो123_voltage_map),
		.volt_table = lकरो123_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO4",
		.id = LP3971_LDO4,
		.ops = &lp3971_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो45_voltage_map),
		.volt_table = lकरो45_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO5",
		.id = LP3971_LDO5,
		.ops = &lp3971_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो45_voltage_map),
		.volt_table = lकरो45_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC1",
		.id = LP3971_DCDC1,
		.ops = &lp3971_dcdc_ops,
		.n_voltages = ARRAY_SIZE(buck_voltage_map),
		.volt_table = buck_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC2",
		.id = LP3971_DCDC2,
		.ops = &lp3971_dcdc_ops,
		.n_voltages = ARRAY_SIZE(buck_voltage_map),
		.volt_table = buck_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC3",
		.id = LP3971_DCDC3,
		.ops = &lp3971_dcdc_ops,
		.n_voltages = ARRAY_SIZE(buck_voltage_map),
		.volt_table = buck_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lp3971_i2c_पढ़ो(काष्ठा i2c_client *i2c, अक्षर reg, पूर्णांक count,
	u16 *dest)
अणु
	पूर्णांक ret;

	अगर (count != 1)
		वापस -EIO;
	ret = i2c_smbus_पढ़ो_byte_data(i2c, reg);
	अगर (ret < 0)
		वापस ret;

	*dest = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक lp3971_i2c_ग_लिखो(काष्ठा i2c_client *i2c, अक्षर reg, पूर्णांक count,
	स्थिर u16 *src)
अणु
	अगर (count != 1)
		वापस -EIO;
	वापस i2c_smbus_ग_लिखो_byte_data(i2c, reg, *src);
पूर्ण

अटल u8 lp3971_reg_पढ़ो(काष्ठा lp3971 *lp3971, u8 reg)
अणु
	u16 val = 0;

	mutex_lock(&lp3971->io_lock);

	lp3971_i2c_पढ़ो(lp3971->i2c, reg, 1, &val);

	dev_dbg(lp3971->dev, "reg read 0x%02x -> 0x%02x\n", (पूर्णांक)reg,
		(अचिन्हित)val&0xff);

	mutex_unlock(&lp3971->io_lock);

	वापस val & 0xff;
पूर्ण

अटल पूर्णांक lp3971_set_bits(काष्ठा lp3971 *lp3971, u8 reg, u16 mask, u16 val)
अणु
	u16 पंचांगp;
	पूर्णांक ret;

	mutex_lock(&lp3971->io_lock);

	ret = lp3971_i2c_पढ़ो(lp3971->i2c, reg, 1, &पंचांगp);
	अगर (ret == 0) अणु
		पंचांगp = (पंचांगp & ~mask) | val;
		ret = lp3971_i2c_ग_लिखो(lp3971->i2c, reg, 1, &पंचांगp);
		dev_dbg(lp3971->dev, "reg write 0x%02x -> 0x%02x\n", (पूर्णांक)reg,
			(अचिन्हित)val&0xff);
	पूर्ण
	mutex_unlock(&lp3971->io_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक setup_regulators(काष्ठा lp3971 *lp3971,
				      काष्ठा lp3971_platक्रमm_data *pdata)
अणु
	पूर्णांक i, err;

	/* Instantiate the regulators */
	क्रम (i = 0; i < pdata->num_regulators; i++) अणु
		काष्ठा regulator_config config = अणु पूर्ण;
		काष्ठा lp3971_regulator_subdev *reg = &pdata->regulators[i];
		काष्ठा regulator_dev *rdev;

		config.dev = lp3971->dev;
		config.init_data = reg->initdata;
		config.driver_data = lp3971;

		rdev = devm_regulator_रेजिस्टर(lp3971->dev,
					       &regulators[reg->id], &config);
		अगर (IS_ERR(rdev)) अणु
			err = PTR_ERR(rdev);
			dev_err(lp3971->dev, "regulator init failed: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp3971_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा lp3971 *lp3971;
	काष्ठा lp3971_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	पूर्णांक ret;
	u16 val;

	अगर (!pdata) अणु
		dev_dbg(&i2c->dev, "No platform init data supplied\n");
		वापस -ENODEV;
	पूर्ण

	lp3971 = devm_kzalloc(&i2c->dev, माप(काष्ठा lp3971), GFP_KERNEL);
	अगर (lp3971 == शून्य)
		वापस -ENOMEM;

	lp3971->i2c = i2c;
	lp3971->dev = &i2c->dev;

	mutex_init(&lp3971->io_lock);

	/* Detect LP3971 */
	ret = lp3971_i2c_पढ़ो(i2c, LP3971_SYS_CONTROL1_REG, 1, &val);
	अगर (ret == 0 && (val & SYS_CONTROL1_INIT_MASK) != SYS_CONTROL1_INIT_VAL)
		ret = -ENODEV;
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "failed to detect device\n");
		वापस ret;
	पूर्ण

	ret = setup_regulators(lp3971, pdata);
	अगर (ret < 0)
		वापस ret;

	i2c_set_clientdata(i2c, lp3971);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp3971_i2c_id[] = अणु
	अणु "lp3971", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp3971_i2c_id);

अटल काष्ठा i2c_driver lp3971_i2c_driver = अणु
	.driver = अणु
		.name = "LP3971",
	पूर्ण,
	.probe_new = lp3971_i2c_probe,
	.id_table = lp3971_i2c_id,
पूर्ण;

module_i2c_driver(lp3971_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marek Szyprowski <m.szyprowski@samsung.com>");
MODULE_DESCRIPTION("LP3971 PMIC driver");
