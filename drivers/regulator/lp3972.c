<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम National Semiconductors LP3972 PMIC chip
 *
 * Based on lp3971.c
 */

#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/lp3972.h>
#समावेश <linux/slab.h>

काष्ठा lp3972 अणु
	काष्ठा device *dev;
	काष्ठा mutex io_lock;
	काष्ठा i2c_client *i2c;
पूर्ण;

/* LP3972 Control Registers */
#घोषणा LP3972_SCR_REG		0x07
#घोषणा LP3972_OVER1_REG	0x10
#घोषणा LP3972_OVSR1_REG	0x11
#घोषणा LP3972_OVER2_REG	0x12
#घोषणा LP3972_OVSR2_REG	0x13
#घोषणा LP3972_VCC1_REG		0x20
#घोषणा LP3972_ADTV1_REG	0x23
#घोषणा LP3972_ADTV2_REG	0x24
#घोषणा LP3972_AVRC_REG		0x25
#घोषणा LP3972_CDTC1_REG	0x26
#घोषणा LP3972_CDTC2_REG	0x27
#घोषणा LP3972_SDTV1_REG	0x29
#घोषणा LP3972_SDTV2_REG	0x2A
#घोषणा LP3972_MDTV1_REG	0x32
#घोषणा LP3972_MDTV2_REG	0x33
#घोषणा LP3972_L2VCR_REG	0x39
#घोषणा LP3972_L34VCR_REG	0x3A
#घोषणा LP3972_SCR1_REG		0x80
#घोषणा LP3972_SCR2_REG		0x81
#घोषणा LP3972_OEN3_REG		0x82
#घोषणा LP3972_OSR3_REG		0x83
#घोषणा LP3972_LOER4_REG	0x84
#घोषणा LP3972_B2TV_REG		0x85
#घोषणा LP3972_B3TV_REG		0x86
#घोषणा LP3972_B32RC_REG	0x87
#घोषणा LP3972_ISRA_REG		0x88
#घोषणा LP3972_BCCR_REG		0x89
#घोषणा LP3972_II1RR_REG	0x8E
#घोषणा LP3972_II2RR_REG	0x8F

#घोषणा LP3972_SYS_CONTROL1_REG		LP3972_SCR1_REG
/* System control रेजिस्टर 1 initial value,
 * bits 5, 6 and 7 are EPROM programmable */
#घोषणा SYS_CONTROL1_INIT_VAL		0x02
#घोषणा SYS_CONTROL1_INIT_MASK		0x1F

#घोषणा LP3972_VOL_CHANGE_REG		LP3972_VCC1_REG
#घोषणा LP3972_VOL_CHANGE_FLAG_GO	0x01
#घोषणा LP3972_VOL_CHANGE_FLAG_MASK	0x03

/* LDO output enable mask */
#घोषणा LP3972_OEN3_L1EN	BIT(0)
#घोषणा LP3972_OVER2_LDO2_EN	BIT(2)
#घोषणा LP3972_OVER2_LDO3_EN	BIT(3)
#घोषणा LP3972_OVER2_LDO4_EN	BIT(4)
#घोषणा LP3972_OVER1_S_EN	BIT(2)

अटल स्थिर अचिन्हित पूर्णांक lकरो1_voltage_map[] = अणु
	1700000, 1725000, 1750000, 1775000, 1800000, 1825000, 1850000, 1875000,
	1900000, 1925000, 1950000, 1975000, 2000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो23_voltage_map[] = अणु
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000, 3000000, 3100000, 3200000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो4_voltage_map[] = अणु
	1000000, 1050000, 1100000, 1150000, 1200000, 1250000, 1300000, 1350000,
	1400000, 1500000, 1800000, 1900000, 2500000, 2800000, 3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो5_voltage_map[] = अणु
	      0,       0,       0,       0,       0,  850000,  875000,  900000,
	 925000,  950000,  975000, 1000000, 1025000, 1050000, 1075000, 1100000,
	1125000, 1150000, 1175000, 1200000, 1225000, 1250000, 1275000, 1300000,
	1325000, 1350000, 1375000, 1400000, 1425000, 1450000, 1475000, 1500000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक buck1_voltage_map[] = अणु
	 725000,  750000,  775000,  800000,  825000,  850000,  875000,  900000,
	 925000,  950000,  975000, 1000000, 1025000, 1050000, 1075000, 1100000,
	1125000, 1150000, 1175000, 1200000, 1225000, 1250000, 1275000, 1300000,
	1325000, 1350000, 1375000, 1400000, 1425000, 1450000, 1475000, 1500000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक buck23_voltage_map[] = अणु
	      0,  800000,  850000,  900000,  950000, 1000000, 1050000, 1100000,
	1150000, 1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000,
	1550000, 1600000, 1650000, 1700000, 1800000, 1900000, 2500000, 2800000,
	3000000, 3300000,
पूर्ण;

अटल स्थिर पूर्णांक lकरो_output_enable_mask[] = अणु
	LP3972_OEN3_L1EN,
	LP3972_OVER2_LDO2_EN,
	LP3972_OVER2_LDO3_EN,
	LP3972_OVER2_LDO4_EN,
	LP3972_OVER1_S_EN,
पूर्ण;

अटल स्थिर पूर्णांक lकरो_output_enable_addr[] = अणु
	LP3972_OEN3_REG,
	LP3972_OVER2_REG,
	LP3972_OVER2_REG,
	LP3972_OVER2_REG,
	LP3972_OVER1_REG,
पूर्ण;

अटल स्थिर पूर्णांक lकरो_vol_ctl_addr[] = अणु
	LP3972_MDTV1_REG,
	LP3972_L2VCR_REG,
	LP3972_L34VCR_REG,
	LP3972_L34VCR_REG,
	LP3972_SDTV1_REG,
पूर्ण;

अटल स्थिर पूर्णांक buck_vol_enable_addr[] = अणु
	LP3972_OVER1_REG,
	LP3972_OEN3_REG,
	LP3972_OEN3_REG,
पूर्ण;

अटल स्थिर पूर्णांक buck_base_addr[] = अणु
	LP3972_ADTV1_REG,
	LP3972_B2TV_REG,
	LP3972_B3TV_REG,
पूर्ण;

#घोषणा LP3972_LDO_OUTPUT_ENABLE_MASK(x) (lकरो_output_enable_mask[x])
#घोषणा LP3972_LDO_OUTPUT_ENABLE_REG(x) (lकरो_output_enable_addr[x])

/*	LDO voltage control रेजिस्टरs shअगरt:
	LP3972_LDO1 -> 0, LP3972_LDO2 -> 4
	LP3972_LDO3 -> 0, LP3972_LDO4 -> 4
	LP3972_LDO5 -> 0
*/
#घोषणा LP3972_LDO_VOL_CONTR_SHIFT(x) (((x) & 1) << 2)
#घोषणा LP3972_LDO_VOL_CONTR_REG(x) (lकरो_vol_ctl_addr[x])
#घोषणा LP3972_LDO_VOL_CHANGE_SHIFT(x) ((x) ? 4 : 6)

#घोषणा LP3972_LDO_VOL_MASK(x) (((x) % 4) ? 0x0f : 0x1f)
#घोषणा LP3972_LDO_VOL_MIN_IDX(x) (((x) == 4) ? 0x05 : 0x00)
#घोषणा LP3972_LDO_VOL_MAX_IDX(x) ((x) ? (((x) == 4) ? 0x1f : 0x0f) : 0x0c)

#घोषणा LP3972_BUCK_VOL_ENABLE_REG(x) (buck_vol_enable_addr[x])
#घोषणा LP3972_BUCK_VOL1_REG(x) (buck_base_addr[x])
#घोषणा LP3972_BUCK_VOL_MASK 0x1f

अटल पूर्णांक lp3972_i2c_पढ़ो(काष्ठा i2c_client *i2c, अक्षर reg, पूर्णांक count,
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

अटल पूर्णांक lp3972_i2c_ग_लिखो(काष्ठा i2c_client *i2c, अक्षर reg, पूर्णांक count,
	स्थिर u16 *src)
अणु
	अगर (count != 1)
		वापस -EIO;
	वापस i2c_smbus_ग_लिखो_byte_data(i2c, reg, *src);
पूर्ण

अटल u8 lp3972_reg_पढ़ो(काष्ठा lp3972 *lp3972, u8 reg)
अणु
	u16 val = 0;

	mutex_lock(&lp3972->io_lock);

	lp3972_i2c_पढ़ो(lp3972->i2c, reg, 1, &val);

	dev_dbg(lp3972->dev, "reg read 0x%02x -> 0x%02x\n", (पूर्णांक)reg,
		(अचिन्हित)val & 0xff);

	mutex_unlock(&lp3972->io_lock);

	वापस val & 0xff;
पूर्ण

अटल पूर्णांक lp3972_set_bits(काष्ठा lp3972 *lp3972, u8 reg, u16 mask, u16 val)
अणु
	u16 पंचांगp;
	पूर्णांक ret;

	mutex_lock(&lp3972->io_lock);

	ret = lp3972_i2c_पढ़ो(lp3972->i2c, reg, 1, &पंचांगp);
	अगर (ret == 0) अणु
		पंचांगp = (पंचांगp & ~mask) | val;
		ret = lp3972_i2c_ग_लिखो(lp3972->i2c, reg, 1, &पंचांगp);
		dev_dbg(lp3972->dev, "reg write 0x%02x -> 0x%02x\n", (पूर्णांक)reg,
			(अचिन्हित)val & 0xff);
	पूर्ण
	mutex_unlock(&lp3972->io_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक lp3972_lकरो_is_enabled(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3972_LDO1;
	u16 mask = LP3972_LDO_OUTPUT_ENABLE_MASK(lकरो);
	u16 val;

	val = lp3972_reg_पढ़ो(lp3972, LP3972_LDO_OUTPUT_ENABLE_REG(lकरो));
	वापस !!(val & mask);
पूर्ण

अटल पूर्णांक lp3972_lकरो_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3972_LDO1;
	u16 mask = LP3972_LDO_OUTPUT_ENABLE_MASK(lकरो);

	वापस lp3972_set_bits(lp3972, LP3972_LDO_OUTPUT_ENABLE_REG(lकरो),
				mask, mask);
पूर्ण

अटल पूर्णांक lp3972_lकरो_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3972_LDO1;
	u16 mask = LP3972_LDO_OUTPUT_ENABLE_MASK(lकरो);

	वापस lp3972_set_bits(lp3972, LP3972_LDO_OUTPUT_ENABLE_REG(lकरो),
				mask, 0);
पूर्ण

अटल पूर्णांक lp3972_lकरो_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3972_LDO1;
	u16 mask = LP3972_LDO_VOL_MASK(lकरो);
	u16 val, reg;

	reg = lp3972_reg_पढ़ो(lp3972, LP3972_LDO_VOL_CONTR_REG(lकरो));
	val = (reg >> LP3972_LDO_VOL_CONTR_SHIFT(lकरो)) & mask;

	वापस val;
पूर्ण

अटल पूर्णांक lp3972_lकरो_set_voltage_sel(काष्ठा regulator_dev *dev,
				      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक lकरो = rdev_get_id(dev) - LP3972_LDO1;
	पूर्णांक shअगरt, ret;

	shअगरt = LP3972_LDO_VOL_CONTR_SHIFT(lकरो);
	ret = lp3972_set_bits(lp3972, LP3972_LDO_VOL_CONTR_REG(lकरो),
		LP3972_LDO_VOL_MASK(lकरो) << shअगरt, selector << shअगरt);

	अगर (ret)
		वापस ret;

	/*
	 * LDO1 and LDO5 support voltage control by either target voltage1
	 * or target voltage2 रेजिस्टर.
	 * We use target voltage1 रेजिस्टर क्रम LDO1 and LDO5 in this driver.
	 * We need to update voltage change control रेजिस्टर(0x20) to enable
	 * LDO1 and LDO5 to change to their programmed target values.
	 */
	चयन (lकरो) अणु
	हाल LP3972_LDO1:
	हाल LP3972_LDO5:
		shअगरt = LP3972_LDO_VOL_CHANGE_SHIFT(lकरो);
		ret = lp3972_set_bits(lp3972, LP3972_VOL_CHANGE_REG,
			LP3972_VOL_CHANGE_FLAG_MASK << shअगरt,
			LP3972_VOL_CHANGE_FLAG_GO << shअगरt);
		अगर (ret)
			वापस ret;

		ret = lp3972_set_bits(lp3972, LP3972_VOL_CHANGE_REG,
			LP3972_VOL_CHANGE_FLAG_MASK << shअगरt, 0);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops lp3972_lकरो_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.is_enabled = lp3972_lकरो_is_enabled,
	.enable = lp3972_lकरो_enable,
	.disable = lp3972_lकरो_disable,
	.get_voltage_sel = lp3972_lकरो_get_voltage_sel,
	.set_voltage_sel = lp3972_lकरो_set_voltage_sel,
पूर्ण;

अटल पूर्णांक lp3972_dcdc_is_enabled(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3972_DCDC1;
	u16 mask = 1 << (buck * 2);
	u16 val;

	val = lp3972_reg_पढ़ो(lp3972, LP3972_BUCK_VOL_ENABLE_REG(buck));
	वापस !!(val & mask);
पूर्ण

अटल पूर्णांक lp3972_dcdc_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3972_DCDC1;
	u16 mask = 1 << (buck * 2);
	u16 val;

	val = lp3972_set_bits(lp3972, LP3972_BUCK_VOL_ENABLE_REG(buck),
				mask, mask);
	वापस val;
पूर्ण

अटल पूर्णांक lp3972_dcdc_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3972_DCDC1;
	u16 mask = 1 << (buck * 2);
	u16 val;

	val = lp3972_set_bits(lp3972, LP3972_BUCK_VOL_ENABLE_REG(buck),
				mask, 0);
	वापस val;
पूर्ण

अटल पूर्णांक lp3972_dcdc_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3972_DCDC1;
	u16 reg;

	reg = lp3972_reg_पढ़ो(lp3972, LP3972_BUCK_VOL1_REG(buck));
	reg &= LP3972_BUCK_VOL_MASK;

	वापस reg;
पूर्ण

अटल पूर्णांक lp3972_dcdc_set_voltage_sel(काष्ठा regulator_dev *dev,
				       अचिन्हित पूर्णांक selector)
अणु
	काष्ठा lp3972 *lp3972 = rdev_get_drvdata(dev);
	पूर्णांक buck = rdev_get_id(dev) - LP3972_DCDC1;
	पूर्णांक ret;

	ret = lp3972_set_bits(lp3972, LP3972_BUCK_VOL1_REG(buck),
				LP3972_BUCK_VOL_MASK, selector);
	अगर (ret)
		वापस ret;

	अगर (buck != 0)
		वापस ret;

	ret = lp3972_set_bits(lp3972, LP3972_VOL_CHANGE_REG,
		LP3972_VOL_CHANGE_FLAG_MASK, LP3972_VOL_CHANGE_FLAG_GO);
	अगर (ret)
		वापस ret;

	वापस lp3972_set_bits(lp3972, LP3972_VOL_CHANGE_REG,
				LP3972_VOL_CHANGE_FLAG_MASK, 0);
पूर्ण

अटल स्थिर काष्ठा regulator_ops lp3972_dcdc_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.is_enabled = lp3972_dcdc_is_enabled,
	.enable = lp3972_dcdc_enable,
	.disable = lp3972_dcdc_disable,
	.get_voltage_sel = lp3972_dcdc_get_voltage_sel,
	.set_voltage_sel = lp3972_dcdc_set_voltage_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	अणु
		.name = "LDO1",
		.id = LP3972_LDO1,
		.ops = &lp3972_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो1_voltage_map),
		.volt_table = lकरो1_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO2",
		.id = LP3972_LDO2,
		.ops = &lp3972_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो23_voltage_map),
		.volt_table = lकरो23_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO3",
		.id = LP3972_LDO3,
		.ops = &lp3972_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो23_voltage_map),
		.volt_table = lकरो23_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO4",
		.id = LP3972_LDO4,
		.ops = &lp3972_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो4_voltage_map),
		.volt_table = lकरो4_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO5",
		.id = LP3972_LDO5,
		.ops = &lp3972_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lकरो5_voltage_map),
		.volt_table = lकरो5_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC1",
		.id = LP3972_DCDC1,
		.ops = &lp3972_dcdc_ops,
		.n_voltages = ARRAY_SIZE(buck1_voltage_map),
		.volt_table = buck1_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC2",
		.id = LP3972_DCDC2,
		.ops = &lp3972_dcdc_ops,
		.n_voltages = ARRAY_SIZE(buck23_voltage_map),
		.volt_table = buck23_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC3",
		.id = LP3972_DCDC3,
		.ops = &lp3972_dcdc_ops,
		.n_voltages = ARRAY_SIZE(buck23_voltage_map),
		.volt_table = buck23_voltage_map,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक setup_regulators(काष्ठा lp3972 *lp3972,
	काष्ठा lp3972_platक्रमm_data *pdata)
अणु
	पूर्णांक i, err;

	/* Instantiate the regulators */
	क्रम (i = 0; i < pdata->num_regulators; i++) अणु
		काष्ठा lp3972_regulator_subdev *reg = &pdata->regulators[i];
		काष्ठा regulator_config config = अणु पूर्ण;
		काष्ठा regulator_dev *rdev;

		config.dev = lp3972->dev;
		config.init_data = reg->initdata;
		config.driver_data = lp3972;

		rdev = devm_regulator_रेजिस्टर(lp3972->dev,
					       &regulators[reg->id], &config);
		अगर (IS_ERR(rdev)) अणु
			err = PTR_ERR(rdev);
			dev_err(lp3972->dev, "regulator init failed: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp3972_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lp3972 *lp3972;
	काष्ठा lp3972_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	पूर्णांक ret;
	u16 val;

	अगर (!pdata) अणु
		dev_dbg(&i2c->dev, "No platform init data supplied\n");
		वापस -ENODEV;
	पूर्ण

	lp3972 = devm_kzalloc(&i2c->dev, माप(काष्ठा lp3972), GFP_KERNEL);
	अगर (!lp3972)
		वापस -ENOMEM;

	lp3972->i2c = i2c;
	lp3972->dev = &i2c->dev;

	mutex_init(&lp3972->io_lock);

	/* Detect LP3972 */
	ret = lp3972_i2c_पढ़ो(i2c, LP3972_SYS_CONTROL1_REG, 1, &val);
	अगर (ret == 0 &&
		(val & SYS_CONTROL1_INIT_MASK) != SYS_CONTROL1_INIT_VAL) अणु
		ret = -ENODEV;
		dev_err(&i2c->dev, "chip reported: val = 0x%x\n", val);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "failed to detect device. ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = setup_regulators(lp3972, pdata);
	अगर (ret < 0)
		वापस ret;

	i2c_set_clientdata(i2c, lp3972);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp3972_i2c_id[] = अणु
	अणु "lp3972", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp3972_i2c_id);

अटल काष्ठा i2c_driver lp3972_i2c_driver = अणु
	.driver = अणु
		.name = "lp3972",
	पूर्ण,
	.probe    = lp3972_i2c_probe,
	.id_table = lp3972_i2c_id,
पूर्ण;

अटल पूर्णांक __init lp3972_module_init(व्योम)
अणु
	वापस i2c_add_driver(&lp3972_i2c_driver);
पूर्ण
subsys_initcall(lp3972_module_init);

अटल व्योम __निकास lp3972_module_निकास(व्योम)
अणु
	i2c_del_driver(&lp3972_i2c_driver);
पूर्ण
module_निकास(lp3972_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Axel Lin <axel.lin@gmail.com>");
MODULE_DESCRIPTION("LP3972 PMIC driver");
