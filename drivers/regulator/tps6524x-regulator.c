<शैली गुरु>
/*
 * Regulator driver क्रम TPS6524x PMIC
 *
 * Copyright (C) 2010 Texas Instruments
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

#घोषणा REG_LDO_SET		0x0
#घोषणा LDO_ILIM_MASK		1	/* 0 = 400-800, 1 = 900-1500 */
#घोषणा LDO_VSEL_MASK		0x0f
#घोषणा LDO2_ILIM_SHIFT		12
#घोषणा LDO2_VSEL_SHIFT		4
#घोषणा LDO1_ILIM_SHIFT		8
#घोषणा LDO1_VSEL_SHIFT		0

#घोषणा REG_BLOCK_EN		0x1
#घोषणा BLOCK_MASK		1
#घोषणा BLOCK_LDO1_SHIFT	0
#घोषणा BLOCK_LDO2_SHIFT	1
#घोषणा BLOCK_LCD_SHIFT		2
#घोषणा BLOCK_USB_SHIFT		3

#घोषणा REG_DCDC_SET		0x2
#घोषणा DCDC_VDCDC_MASK		0x1f
#घोषणा DCDC_VDCDC1_SHIFT	0
#घोषणा DCDC_VDCDC2_SHIFT	5
#घोषणा DCDC_VDCDC3_SHIFT	10

#घोषणा REG_DCDC_EN		0x3
#घोषणा DCDCDCDC_EN_MASK	0x1
#घोषणा DCDCDCDC1_EN_SHIFT	0
#घोषणा DCDCDCDC1_PG_MSK	BIT(1)
#घोषणा DCDCDCDC2_EN_SHIFT	2
#घोषणा DCDCDCDC2_PG_MSK	BIT(3)
#घोषणा DCDCDCDC3_EN_SHIFT	4
#घोषणा DCDCDCDC3_PG_MSK	BIT(5)

#घोषणा REG_USB			0x4
#घोषणा USB_ILIM_SHIFT		0
#घोषणा USB_ILIM_MASK		0x3
#घोषणा USB_TSD_SHIFT		2
#घोषणा USB_TSD_MASK		0x3
#घोषणा USB_TWARN_SHIFT		4
#घोषणा USB_TWARN_MASK		0x3
#घोषणा USB_IWARN_SD		BIT(6)
#घोषणा USB_FAST_LOOP		BIT(7)

#घोषणा REG_ALARM		0x5
#घोषणा ALARM_LDO1		BIT(0)
#घोषणा ALARM_DCDC1		BIT(1)
#घोषणा ALARM_DCDC2		BIT(2)
#घोषणा ALARM_DCDC3		BIT(3)
#घोषणा ALARM_LDO2		BIT(4)
#घोषणा ALARM_USB_WARN		BIT(5)
#घोषणा ALARM_USB_ALARM		BIT(6)
#घोषणा ALARM_LCD		BIT(9)
#घोषणा ALARM_TEMP_WARM		BIT(10)
#घोषणा ALARM_TEMP_HOT		BIT(11)
#घोषणा ALARM_NRST		BIT(14)
#घोषणा ALARM_POWERUP		BIT(15)

#घोषणा REG_INT_ENABLE		0x6
#घोषणा INT_LDO1		BIT(0)
#घोषणा INT_DCDC1		BIT(1)
#घोषणा INT_DCDC2		BIT(2)
#घोषणा INT_DCDC3		BIT(3)
#घोषणा INT_LDO2		BIT(4)
#घोषणा INT_USB_WARN		BIT(5)
#घोषणा INT_USB_ALARM		BIT(6)
#घोषणा INT_LCD			BIT(9)
#घोषणा INT_TEMP_WARM		BIT(10)
#घोषणा INT_TEMP_HOT		BIT(11)
#घोषणा INT_GLOBAL_EN		BIT(15)

#घोषणा REG_INT_STATUS		0x7
#घोषणा STATUS_LDO1		BIT(0)
#घोषणा STATUS_DCDC1		BIT(1)
#घोषणा STATUS_DCDC2		BIT(2)
#घोषणा STATUS_DCDC3		BIT(3)
#घोषणा STATUS_LDO2		BIT(4)
#घोषणा STATUS_USB_WARN		BIT(5)
#घोषणा STATUS_USB_ALARM	BIT(6)
#घोषणा STATUS_LCD		BIT(9)
#घोषणा STATUS_TEMP_WARM	BIT(10)
#घोषणा STATUS_TEMP_HOT		BIT(11)

#घोषणा REG_SOFTWARE_RESET	0xb
#घोषणा REG_WRITE_ENABLE	0xd
#घोषणा REG_REV_ID		0xf

#घोषणा N_DCDC			3
#घोषणा N_LDO			2
#घोषणा N_SWITCH		2
#घोषणा N_REGULATORS		(N_DCDC + N_LDO + N_SWITCH)

#घोषणा CMD_READ(reg)		((reg) << 6)
#घोषणा CMD_WRITE(reg)		(BIT(5) | (reg) << 6)
#घोषणा STAT_CLK		BIT(3)
#घोषणा STAT_WRITE		BIT(2)
#घोषणा STAT_INVALID		BIT(1)
#घोषणा STAT_WP			BIT(0)

काष्ठा field अणु
	पूर्णांक		reg;
	पूर्णांक		shअगरt;
	पूर्णांक		mask;
पूर्ण;

काष्ठा supply_info अणु
	स्थिर अक्षर	*name;
	पूर्णांक		n_voltages;
	स्थिर अचिन्हित पूर्णांक *voltages;
	पूर्णांक		n_ilimsels;
	स्थिर अचिन्हित पूर्णांक *ilimsels;
	काष्ठा field	enable, voltage, ilimsel;
पूर्ण;

काष्ठा tps6524x अणु
	काष्ठा device		*dev;
	काष्ठा spi_device	*spi;
	काष्ठा mutex		lock;
	काष्ठा regulator_desc	desc[N_REGULATORS];
पूर्ण;

अटल पूर्णांक __पढ़ो_reg(काष्ठा tps6524x *hw, पूर्णांक reg)
अणु
	पूर्णांक error = 0;
	u16 cmd = CMD_READ(reg), in;
	u8 status;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[3];

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	t[0].tx_buf = &cmd;
	t[0].len = 2;
	t[0].bits_per_word = 12;
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = &in;
	t[1].len = 2;
	t[1].bits_per_word = 16;
	spi_message_add_tail(&t[1], &m);

	t[2].rx_buf = &status;
	t[2].len = 1;
	t[2].bits_per_word = 4;
	spi_message_add_tail(&t[2], &m);

	error = spi_sync(hw->spi, &m);
	अगर (error < 0)
		वापस error;

	dev_dbg(hw->dev, "read reg %d, data %x, status %x\n",
		reg, in, status);

	अगर (!(status & STAT_CLK) || (status & STAT_WRITE))
		वापस -EIO;

	अगर (status & STAT_INVALID)
		वापस -EINVAL;

	वापस in;
पूर्ण

अटल पूर्णांक पढ़ो_reg(काष्ठा tps6524x *hw, पूर्णांक reg)
अणु
	पूर्णांक ret;

	mutex_lock(&hw->lock);
	ret = __पढ़ो_reg(hw, reg);
	mutex_unlock(&hw->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक __ग_लिखो_reg(काष्ठा tps6524x *hw, पूर्णांक reg, पूर्णांक val)
अणु
	पूर्णांक error = 0;
	u16 cmd = CMD_WRITE(reg), out = val;
	u8 status;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[3];

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	t[0].tx_buf = &cmd;
	t[0].len = 2;
	t[0].bits_per_word = 12;
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = &out;
	t[1].len = 2;
	t[1].bits_per_word = 16;
	spi_message_add_tail(&t[1], &m);

	t[2].rx_buf = &status;
	t[2].len = 1;
	t[2].bits_per_word = 4;
	spi_message_add_tail(&t[2], &m);

	error = spi_sync(hw->spi, &m);
	अगर (error < 0)
		वापस error;

	dev_dbg(hw->dev, "wrote reg %d, data %x, status %x\n",
		reg, out, status);

	अगर (!(status & STAT_CLK) || !(status & STAT_WRITE))
		वापस -EIO;

	अगर (status & (STAT_INVALID | STAT_WP))
		वापस -EINVAL;

	वापस error;
पूर्ण

अटल पूर्णांक __rmw_reg(काष्ठा tps6524x *hw, पूर्णांक reg, पूर्णांक mask, पूर्णांक val)
अणु
	पूर्णांक ret;

	ret = __पढ़ो_reg(hw, reg);
	अगर (ret < 0)
		वापस ret;

	ret &= ~mask;
	ret |= val;

	ret = __ग_लिखो_reg(hw, reg, ret);

	वापस (ret < 0) ? ret : 0;
पूर्ण

अटल पूर्णांक rmw_protect(काष्ठा tps6524x *hw, पूर्णांक reg, पूर्णांक mask, पूर्णांक val)
अणु
	पूर्णांक ret;

	mutex_lock(&hw->lock);

	ret = __ग_लिखो_reg(hw, REG_WRITE_ENABLE, 1);
	अगर (ret) अणु
		dev_err(hw->dev, "failed to set write enable\n");
		जाओ error;
	पूर्ण

	ret = __rmw_reg(hw, reg, mask, val);
	अगर (ret)
		dev_err(hw->dev, "failed to rmw register %d\n", reg);

	ret = __ग_लिखो_reg(hw, REG_WRITE_ENABLE, 0);
	अगर (ret) अणु
		dev_err(hw->dev, "failed to clear write enable\n");
		जाओ error;
	पूर्ण

error:
	mutex_unlock(&hw->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_field(काष्ठा tps6524x *hw, स्थिर काष्ठा field *field)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = पढ़ो_reg(hw, field->reg);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	वापस (पंचांगp >> field->shअगरt) & field->mask;
पूर्ण

अटल पूर्णांक ग_लिखो_field(काष्ठा tps6524x *hw, स्थिर काष्ठा field *field,
		       पूर्णांक val)
अणु
	अगर (val & ~field->mask)
		वापस -EOVERFLOW;

	वापस rmw_protect(hw, field->reg,
				    field->mask << field->shअगरt,
				    val << field->shअगरt);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक dcdc1_voltages[] = अणु
	 800000,  825000,  850000,  875000,
	 900000,  925000,  950000,  975000,
	1000000, 1025000, 1050000, 1075000,
	1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000,
	1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000,
	1500000, 1525000, 1550000, 1575000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक dcdc2_voltages[] = अणु
	1400000, 1450000, 1500000, 1550000,
	1600000, 1650000, 1700000, 1750000,
	1800000, 1850000, 1900000, 1950000,
	2000000, 2050000, 2100000, 2150000,
	2200000, 2250000, 2300000, 2350000,
	2400000, 2450000, 2500000, 2550000,
	2600000, 2650000, 2700000, 2750000,
	2800000, 2850000, 2900000, 2950000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक dcdc3_voltages[] = अणु
	2400000, 2450000, 2500000, 2550000, 2600000,
	2650000, 2700000, 2750000, 2800000, 2850000,
	2900000, 2950000, 3000000, 3050000, 3100000,
	3150000, 3200000, 3250000, 3300000, 3350000,
	3400000, 3450000, 3500000, 3550000, 3600000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो1_voltages[] = अणु
	4300000, 4350000, 4400000, 4450000,
	4500000, 4550000, 4600000, 4650000,
	4700000, 4750000, 4800000, 4850000,
	4900000, 4950000, 5000000, 5050000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो2_voltages[] = अणु
	1100000, 1150000, 1200000, 1250000,
	1300000, 1700000, 1750000, 1800000,
	1850000, 1900000, 3150000, 3200000,
	3250000, 3300000, 3350000, 3400000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fixed_5000000_voltage[] = अणु
	5000000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_ilimsel[] = अणु
	400000, 1500000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक usb_ilimsel[] = अणु
	200000, 400000, 800000, 1000000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fixed_2400000_ilimsel[] = अणु
	2400000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fixed_1200000_ilimsel[] = अणु
	1200000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fixed_400000_ilimsel[] = अणु
	400000
पूर्ण;

#घोषणा __MK_FIELD(_reg, _mask, _shअगरt) \
	अणु .reg = (_reg), .mask = (_mask), .shअगरt = (_shअगरt), पूर्ण

अटल स्थिर काष्ठा supply_info supply_info[N_REGULATORS] = अणु
	अणु
		.name		= "DCDC1",
		.n_voltages	= ARRAY_SIZE(dcdc1_voltages),
		.voltages	= dcdc1_voltages,
		.n_ilimsels	= ARRAY_SIZE(fixed_2400000_ilimsel),
		.ilimsels	= fixed_2400000_ilimsel,
		.enable		= __MK_FIELD(REG_DCDC_EN, DCDCDCDC_EN_MASK,
					     DCDCDCDC1_EN_SHIFT),
		.voltage	= __MK_FIELD(REG_DCDC_SET, DCDC_VDCDC_MASK,
					     DCDC_VDCDC1_SHIFT),
	पूर्ण,
	अणु
		.name		= "DCDC2",
		.n_voltages	= ARRAY_SIZE(dcdc2_voltages),
		.voltages	= dcdc2_voltages,
		.n_ilimsels	= ARRAY_SIZE(fixed_1200000_ilimsel),
		.ilimsels	= fixed_1200000_ilimsel,
		.enable		= __MK_FIELD(REG_DCDC_EN, DCDCDCDC_EN_MASK,
					     DCDCDCDC2_EN_SHIFT),
		.voltage	= __MK_FIELD(REG_DCDC_SET, DCDC_VDCDC_MASK,
					     DCDC_VDCDC2_SHIFT),
	पूर्ण,
	अणु
		.name		= "DCDC3",
		.n_voltages	= ARRAY_SIZE(dcdc3_voltages),
		.voltages	= dcdc3_voltages,
		.n_ilimsels	= ARRAY_SIZE(fixed_1200000_ilimsel),
		.ilimsels	= fixed_1200000_ilimsel,
		.enable		= __MK_FIELD(REG_DCDC_EN, DCDCDCDC_EN_MASK,
					DCDCDCDC3_EN_SHIFT),
		.voltage	= __MK_FIELD(REG_DCDC_SET, DCDC_VDCDC_MASK,
					     DCDC_VDCDC3_SHIFT),
	पूर्ण,
	अणु
		.name		= "LDO1",
		.n_voltages	= ARRAY_SIZE(lकरो1_voltages),
		.voltages	= lकरो1_voltages,
		.n_ilimsels	= ARRAY_SIZE(lकरो_ilimsel),
		.ilimsels	= lकरो_ilimsel,
		.enable		= __MK_FIELD(REG_BLOCK_EN, BLOCK_MASK,
					     BLOCK_LDO1_SHIFT),
		.voltage	= __MK_FIELD(REG_LDO_SET, LDO_VSEL_MASK,
					     LDO1_VSEL_SHIFT),
		.ilimsel	= __MK_FIELD(REG_LDO_SET, LDO_ILIM_MASK,
					     LDO1_ILIM_SHIFT),
	पूर्ण,
	अणु
		.name		= "LDO2",
		.n_voltages	= ARRAY_SIZE(lकरो2_voltages),
		.voltages	= lकरो2_voltages,
		.n_ilimsels	= ARRAY_SIZE(lकरो_ilimsel),
		.ilimsels	= lकरो_ilimsel,
		.enable		= __MK_FIELD(REG_BLOCK_EN, BLOCK_MASK,
					     BLOCK_LDO2_SHIFT),
		.voltage	= __MK_FIELD(REG_LDO_SET, LDO_VSEL_MASK,
					     LDO2_VSEL_SHIFT),
		.ilimsel	= __MK_FIELD(REG_LDO_SET, LDO_ILIM_MASK,
					     LDO2_ILIM_SHIFT),
	पूर्ण,
	अणु
		.name		= "USB",
		.n_voltages	= ARRAY_SIZE(fixed_5000000_voltage),
		.voltages	= fixed_5000000_voltage,
		.n_ilimsels	= ARRAY_SIZE(usb_ilimsel),
		.ilimsels	= usb_ilimsel,
		.enable		= __MK_FIELD(REG_BLOCK_EN, BLOCK_MASK,
					     BLOCK_USB_SHIFT),
		.ilimsel	= __MK_FIELD(REG_USB, USB_ILIM_MASK,
					     USB_ILIM_SHIFT),
	पूर्ण,
	अणु
		.name		= "LCD",
		.n_voltages	= ARRAY_SIZE(fixed_5000000_voltage),
		.voltages	= fixed_5000000_voltage,
		.n_ilimsels	= ARRAY_SIZE(fixed_400000_ilimsel),
		.ilimsels	= fixed_400000_ilimsel,
		.enable		= __MK_FIELD(REG_BLOCK_EN, BLOCK_MASK,
					     BLOCK_LCD_SHIFT),
	पूर्ण,
पूर्ण;

अटल पूर्णांक set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित selector)
अणु
	स्थिर काष्ठा supply_info *info;
	काष्ठा tps6524x *hw;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	अगर (rdev->desc->n_voltages == 1)
		वापस -EINVAL;

	वापस ग_लिखो_field(hw, &info->voltage, selector);
पूर्ण

अटल पूर्णांक get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा supply_info *info;
	काष्ठा tps6524x *hw;
	पूर्णांक ret;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	अगर (rdev->desc->n_voltages == 1)
		वापस 0;

	ret = पढ़ो_field(hw, &info->voltage);
	अगर (ret < 0)
		वापस ret;
	अगर (WARN_ON(ret >= info->n_voltages))
		वापस -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक set_current_limit(काष्ठा regulator_dev *rdev, पूर्णांक min_uA,
			     पूर्णांक max_uA)
अणु
	स्थिर काष्ठा supply_info *info;
	काष्ठा tps6524x *hw;
	पूर्णांक i;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	अगर (info->n_ilimsels == 1)
		वापस -EINVAL;

	क्रम (i = info->n_ilimsels - 1; i >= 0; i--) अणु
		अगर (min_uA <= info->ilimsels[i] &&
		    max_uA >= info->ilimsels[i])
			वापस ग_लिखो_field(hw, &info->ilimsel, i);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा supply_info *info;
	काष्ठा tps6524x *hw;
	पूर्णांक ret;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	अगर (info->n_ilimsels == 1)
		वापस info->ilimsels[0];

	ret = पढ़ो_field(hw, &info->ilimsel);
	अगर (ret < 0)
		वापस ret;
	अगर (WARN_ON(ret >= info->n_ilimsels))
		वापस -EIO;

	वापस info->ilimsels[ret];
पूर्ण

अटल पूर्णांक enable_supply(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा supply_info *info;
	काष्ठा tps6524x *hw;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	वापस ग_लिखो_field(hw, &info->enable, 1);
पूर्ण

अटल पूर्णांक disable_supply(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा supply_info *info;
	काष्ठा tps6524x *hw;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	वापस ग_लिखो_field(hw, &info->enable, 0);
पूर्ण

अटल पूर्णांक is_supply_enabled(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा supply_info *info;
	काष्ठा tps6524x *hw;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	वापस पढ़ो_field(hw, &info->enable);
पूर्ण

अटल स्थिर काष्ठा regulator_ops regulator_ops = अणु
	.is_enabled		= is_supply_enabled,
	.enable			= enable_supply,
	.disable		= disable_supply,
	.get_voltage_sel	= get_voltage_sel,
	.set_voltage_sel	= set_voltage_sel,
	.list_voltage		= regulator_list_voltage_table,
	.map_voltage		= regulator_map_voltage_ascend,
	.set_current_limit	= set_current_limit,
	.get_current_limit	= get_current_limit,
पूर्ण;

अटल पूर्णांक pmic_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा tps6524x *hw;
	काष्ठा device *dev = &spi->dev;
	स्थिर काष्ठा supply_info *info = supply_info;
	काष्ठा regulator_init_data *init_data;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	init_data = dev_get_platdata(dev);
	अगर (!init_data) अणु
		dev_err(dev, "could not find regulator platform data\n");
		वापस -EINVAL;
	पूर्ण

	hw = devm_kzalloc(&spi->dev, माप(काष्ठा tps6524x), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;

	spi_set_drvdata(spi, hw);

	स_रखो(hw, 0, माप(काष्ठा tps6524x));
	hw->dev = dev;
	hw->spi = spi;
	mutex_init(&hw->lock);

	क्रम (i = 0; i < N_REGULATORS; i++, info++, init_data++) अणु
		hw->desc[i].name	= info->name;
		hw->desc[i].id		= i;
		hw->desc[i].n_voltages	= info->n_voltages;
		hw->desc[i].volt_table	= info->voltages;
		hw->desc[i].ops		= &regulator_ops;
		hw->desc[i].type	= REGULATOR_VOLTAGE;
		hw->desc[i].owner	= THIS_MODULE;

		config.dev = dev;
		config.init_data = init_data;
		config.driver_data = hw;

		rdev = devm_regulator_रेजिस्टर(dev, &hw->desc[i], &config);
		अगर (IS_ERR(rdev))
			वापस PTR_ERR(rdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver pmic_driver = अणु
	.probe		= pmic_probe,
	.driver		= अणु
		.name	= "tps6524x",
	पूर्ण,
पूर्ण;

module_spi_driver(pmic_driver);

MODULE_DESCRIPTION("TPS6524X PMIC Driver");
MODULE_AUTHOR("Cyril Chemparathy");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:tps6524x");
