<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Regulators driver क्रम Dialog Semiconductor DA903x
//
// Copyright (C) 2006-2008 Marvell International Ltd.
// Copyright (C) 2008 Compulab Ltd.

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/da903x.h>

/* DA9030 Registers */
#घोषणा DA9030_INVAL		(-1)
#घोषणा DA9030_LDO1011		(0x10)
#घोषणा DA9030_LDO15		(0x11)
#घोषणा DA9030_LDO1416		(0x12)
#घोषणा DA9030_LDO1819		(0x13)
#घोषणा DA9030_LDO17		(0x14)
#घोषणा DA9030_BUCK2DVM1	(0x15)
#घोषणा DA9030_BUCK2DVM2	(0x16)
#घोषणा DA9030_RCTL11		(0x17)
#घोषणा DA9030_RCTL21		(0x18)
#घोषणा DA9030_LDO1		(0x90)
#घोषणा DA9030_LDO23		(0x91)
#घोषणा DA9030_LDO45		(0x92)
#घोषणा DA9030_LDO6		(0x93)
#घोषणा DA9030_LDO78		(0x94)
#घोषणा DA9030_LDO912		(0x95)
#घोषणा DA9030_BUCK		(0x96)
#घोषणा DA9030_RCTL12		(0x97)
#घोषणा DA9030_RCTL22		(0x98)
#घोषणा DA9030_LDO_UNLOCK	(0xa0)
#घोषणा DA9030_LDO_UNLOCK_MASK	(0xe0)
#घोषणा DA9034_OVER1		(0x10)

/* DA9034 Registers */
#घोषणा DA9034_INVAL		(-1)
#घोषणा DA9034_OVER2		(0x11)
#घोषणा DA9034_OVER3		(0x12)
#घोषणा DA9034_LDO643		(0x13)
#घोषणा DA9034_LDO987		(0x14)
#घोषणा DA9034_LDO1110		(0x15)
#घोषणा DA9034_LDO1312		(0x16)
#घोषणा DA9034_LDO1514		(0x17)
#घोषणा DA9034_VCC1		(0x20)
#घोषणा DA9034_ADTV1		(0x23)
#घोषणा DA9034_ADTV2		(0x24)
#घोषणा DA9034_AVRC		(0x25)
#घोषणा DA9034_CDTV1		(0x26)
#घोषणा DA9034_CDTV2		(0x27)
#घोषणा DA9034_CVRC		(0x28)
#घोषणा DA9034_SDTV1		(0x29)
#घोषणा DA9034_SDTV2		(0x2a)
#घोषणा DA9034_SVRC		(0x2b)
#घोषणा DA9034_MDTV1		(0x32)
#घोषणा DA9034_MDTV2		(0x33)
#घोषणा DA9034_MVRC		(0x34)

/* DA9035 Registers. DA9034 Registers are comptabile to DA9035. */
#घोषणा DA9035_OVER3		(0x12)
#घोषणा DA9035_VCC2		(0x1f)
#घोषणा DA9035_3DTV1		(0x2c)
#घोषणा DA9035_3DTV2		(0x2d)
#घोषणा DA9035_3VRC		(0x2e)
#घोषणा DA9035_AUTOSKIP		(0x2f)

काष्ठा da903x_regulator_info अणु
	काष्ठा regulator_desc desc;

	पूर्णांक	max_uV;
	पूर्णांक	vol_reg;
	पूर्णांक	vol_shअगरt;
	पूर्णांक	vol_nbits;
	पूर्णांक	update_reg;
	पूर्णांक	update_bit;
	पूर्णांक	enable_reg;
	पूर्णांक	enable_bit;
पूर्ण;

अटल अंतरभूत काष्ठा device *to_da903x_dev(काष्ठा regulator_dev *rdev)
अणु
	वापस rdev_get_dev(rdev)->parent->parent;
पूर्ण

अटल अंतरभूत पूर्णांक check_range(काष्ठा da903x_regulator_info *info,
				पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	अगर (min_uV < info->desc.min_uV || min_uV > info->max_uV)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* DA9030/DA9034 common operations */
अटल पूर्णांक da903x_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित selector)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	काष्ठा device *da9034_dev = to_da903x_dev(rdev);
	uपूर्णांक8_t val, mask;

	अगर (rdev->desc->n_voltages == 1)
		वापस -EINVAL;

	val = selector << info->vol_shअगरt;
	mask = ((1 << info->vol_nbits) - 1)  << info->vol_shअगरt;

	वापस da903x_update(da9034_dev, info->vol_reg, val, mask);
पूर्ण

अटल पूर्णांक da903x_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	काष्ठा device *da9034_dev = to_da903x_dev(rdev);
	uपूर्णांक8_t val, mask;
	पूर्णांक ret;

	अगर (rdev->desc->n_voltages == 1)
		वापस 0;

	ret = da903x_पढ़ो(da9034_dev, info->vol_reg, &val);
	अगर (ret)
		वापस ret;

	mask = ((1 << info->vol_nbits) - 1)  << info->vol_shअगरt;
	val = (val & mask) >> info->vol_shअगरt;

	वापस val;
पूर्ण

अटल पूर्णांक da903x_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	काष्ठा device *da9034_dev = to_da903x_dev(rdev);

	वापस da903x_set_bits(da9034_dev, info->enable_reg,
					1 << info->enable_bit);
पूर्ण

अटल पूर्णांक da903x_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	काष्ठा device *da9034_dev = to_da903x_dev(rdev);

	वापस da903x_clr_bits(da9034_dev, info->enable_reg,
					1 << info->enable_bit);
पूर्ण

अटल पूर्णांक da903x_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	काष्ठा device *da9034_dev = to_da903x_dev(rdev);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	ret = da903x_पढ़ो(da9034_dev, info->enable_reg, &reg_val);
	अगर (ret)
		वापस ret;

	वापस !!(reg_val & (1 << info->enable_bit));
पूर्ण

/* DA9030 specअगरic operations */
अटल पूर्णांक da9030_set_lकरो1_15_voltage_sel(काष्ठा regulator_dev *rdev,
					  अचिन्हित selector)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	काष्ठा device *da903x_dev = to_da903x_dev(rdev);
	uपूर्णांक8_t val, mask;
	पूर्णांक ret;

	val = selector << info->vol_shअगरt;
	mask = ((1 << info->vol_nbits) - 1)  << info->vol_shअगरt;
	val |= DA9030_LDO_UNLOCK; /* have to set UNLOCK bits */
	mask |= DA9030_LDO_UNLOCK_MASK;

	/* ग_लिखो twice */
	ret = da903x_update(da903x_dev, info->vol_reg, val, mask);
	अगर (ret)
		वापस ret;

	वापस da903x_update(da903x_dev, info->vol_reg, val, mask);
पूर्ण

अटल पूर्णांक da9030_map_lकरो14_voltage(काष्ठा regulator_dev *rdev,
				    पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक thresh, sel;

	अगर (check_range(info, min_uV, max_uV)) अणु
		pr_err("invalid voltage range (%d, %d) uV\n", min_uV, max_uV);
		वापस -EINVAL;
	पूर्ण

	thresh = (info->max_uV + info->desc.min_uV) / 2;
	अगर (min_uV < thresh) अणु
		sel = DIV_ROUND_UP(thresh - min_uV, info->desc.uV_step);
		sel |= 0x4;
	पूर्ण अन्यथा अणु
		sel = DIV_ROUND_UP(min_uV - thresh, info->desc.uV_step);
	पूर्ण

	वापस sel;
पूर्ण

अटल पूर्णांक da9030_list_lकरो14_voltage(काष्ठा regulator_dev *rdev,
				     अचिन्हित selector)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक volt;

	अगर (selector & 0x4)
		volt = rdev->desc->min_uV +
		       rdev->desc->uV_step * (3 - (selector & ~0x4));
	अन्यथा
		volt = (info->max_uV + rdev->desc->min_uV) / 2 +
		       rdev->desc->uV_step * (selector & ~0x4);

	अगर (volt > info->max_uV)
		वापस -EINVAL;

	वापस volt;
पूर्ण

/* DA9034 specअगरic operations */
अटल पूर्णांक da9034_set_dvc_voltage_sel(काष्ठा regulator_dev *rdev,
				      अचिन्हित selector)
अणु
	काष्ठा da903x_regulator_info *info = rdev_get_drvdata(rdev);
	काष्ठा device *da9034_dev = to_da903x_dev(rdev);
	uपूर्णांक8_t val, mask;
	पूर्णांक ret;

	val = selector << info->vol_shअगरt;
	mask = ((1 << info->vol_nbits) - 1)  << info->vol_shअगरt;

	ret = da903x_update(da9034_dev, info->vol_reg, val, mask);
	अगर (ret)
		वापस ret;

	ret = da903x_set_bits(da9034_dev, info->update_reg,
					1 << info->update_bit);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा linear_range da9034_lकरो12_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1700000, 0, 7, 50000),
	REGULATOR_LINEAR_RANGE(2700000, 8, 15, 50000),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops da903x_regulator_lकरो_ops = अणु
	.set_voltage_sel = da903x_set_voltage_sel,
	.get_voltage_sel = da903x_get_voltage_sel,
	.list_voltage	= regulator_list_voltage_linear,
	.map_voltage	= regulator_map_voltage_linear,
	.enable		= da903x_enable,
	.disable	= da903x_disable,
	.is_enabled	= da903x_is_enabled,
पूर्ण;

/* NOTE: this is dedicated क्रम the insane DA9030 LDO14 */
अटल स्थिर काष्ठा regulator_ops da9030_regulator_lकरो14_ops = अणु
	.set_voltage_sel = da903x_set_voltage_sel,
	.get_voltage_sel = da903x_get_voltage_sel,
	.list_voltage	= da9030_list_lकरो14_voltage,
	.map_voltage	= da9030_map_lकरो14_voltage,
	.enable		= da903x_enable,
	.disable	= da903x_disable,
	.is_enabled	= da903x_is_enabled,
पूर्ण;

/* NOTE: this is dedicated क्रम the DA9030 LDO1 and LDO15 that have locks  */
अटल स्थिर काष्ठा regulator_ops da9030_regulator_lकरो1_15_ops = अणु
	.set_voltage_sel = da9030_set_lकरो1_15_voltage_sel,
	.get_voltage_sel = da903x_get_voltage_sel,
	.list_voltage	= regulator_list_voltage_linear,
	.map_voltage	= regulator_map_voltage_linear,
	.enable		= da903x_enable,
	.disable	= da903x_disable,
	.is_enabled	= da903x_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops da9034_regulator_dvc_ops = अणु
	.set_voltage_sel = da9034_set_dvc_voltage_sel,
	.get_voltage_sel = da903x_get_voltage_sel,
	.list_voltage	= regulator_list_voltage_linear,
	.map_voltage	= regulator_map_voltage_linear,
	.enable		= da903x_enable,
	.disable	= da903x_disable,
	.is_enabled	= da903x_is_enabled,
पूर्ण;

/* NOTE: this is dedicated क्रम the insane LDO12 */
अटल स्थिर काष्ठा regulator_ops da9034_regulator_lकरो12_ops = अणु
	.set_voltage_sel = da903x_set_voltage_sel,
	.get_voltage_sel = da903x_get_voltage_sel,
	.list_voltage	= regulator_list_voltage_linear_range,
	.map_voltage	= regulator_map_voltage_linear_range,
	.enable		= da903x_enable,
	.disable	= da903x_disable,
	.is_enabled	= da903x_is_enabled,
पूर्ण;

#घोषणा DA903x_LDO(_pmic, _id, min, max, step, vreg, shअगरt, nbits, ereg, ebit)	\
अणु									\
	.desc	= अणु							\
		.name	= "LDO" #_id,					\
		.ops	= &da903x_regulator_lकरो_ops,			\
		.type	= REGULATOR_VOLTAGE,				\
		.id	= _pmic##_ID_LDO##_id,				\
		.n_voltages = (step) ? ((max - min) / step + 1) : 1,	\
		.owner	= THIS_MODULE,					\
		.min_uV	 = (min) * 1000,				\
		.uV_step = (step) * 1000,				\
	पूर्ण,								\
	.max_uV		= (max) * 1000,					\
	.vol_reg	= _pmic##_##vreg,				\
	.vol_shअगरt	= (shअगरt),					\
	.vol_nbits	= (nbits),					\
	.enable_reg	= _pmic##_##ereg,				\
	.enable_bit	= (ebit),					\
पूर्ण

#घोषणा DA903x_DVC(_pmic, _id, min, max, step, vreg, nbits, ureg, ubit, ereg, ebit) \
अणु									\
	.desc	= अणु							\
		.name	= #_id,						\
		.ops	= &da9034_regulator_dvc_ops,			\
		.type	= REGULATOR_VOLTAGE,				\
		.id	= _pmic##_ID_##_id,				\
		.n_voltages = (step) ? ((max - min) / step + 1) : 1,	\
		.owner	= THIS_MODULE,					\
		.min_uV = (min) * 1000,					\
		.uV_step = (step) * 1000,				\
	पूर्ण,								\
	.max_uV		= (max) * 1000,					\
	.vol_reg	= _pmic##_##vreg,				\
	.vol_shअगरt	= (0),						\
	.vol_nbits	= (nbits),					\
	.update_reg	= _pmic##_##ureg,				\
	.update_bit	= (ubit),					\
	.enable_reg	= _pmic##_##ereg,				\
	.enable_bit	= (ebit),					\
पूर्ण

#घोषणा DA9034_LDO(_id, min, max, step, vreg, shअगरt, nbits, ereg, ebit)	\
	DA903x_LDO(DA9034, _id, min, max, step, vreg, shअगरt, nbits, ereg, ebit)

#घोषणा DA9030_LDO(_id, min, max, step, vreg, shअगरt, nbits, ereg, ebit)	\
	DA903x_LDO(DA9030, _id, min, max, step, vreg, shअगरt, nbits, ereg, ebit)

#घोषणा DA9030_DVC(_id, min, max, step, vreg, nbits, ureg, ubit, ereg, ebit) \
	DA903x_DVC(DA9030, _id, min, max, step, vreg, nbits, ureg, ubit, \
		   ereg, ebit)

#घोषणा DA9034_DVC(_id, min, max, step, vreg, nbits, ureg, ubit, ereg, ebit) \
	DA903x_DVC(DA9034, _id, min, max, step, vreg, nbits, ureg, ubit, \
		   ereg, ebit)

#घोषणा DA9035_DVC(_id, min, max, step, vreg, nbits, ureg, ubit, ereg, ebit) \
	DA903x_DVC(DA9035, _id, min, max, step, vreg, nbits, ureg, ubit, \
		   ereg, ebit)

अटल काष्ठा da903x_regulator_info da903x_regulator_info[] = अणु
	/* DA9030 */
	DA9030_DVC(BUCK2, 850, 1625, 25, BUCK2DVM1, 5, BUCK2DVM1, 7, RCTL11, 0),

	DA9030_LDO( 1, 1200, 3200, 100,    LDO1, 0, 5, RCTL12, 1),
	DA9030_LDO( 2, 1800, 3200, 100,   LDO23, 0, 4, RCTL12, 2),
	DA9030_LDO( 3, 1800, 3200, 100,   LDO23, 4, 4, RCTL12, 3),
	DA9030_LDO( 4, 1800, 3200, 100,   LDO45, 0, 4, RCTL12, 4),
	DA9030_LDO( 5, 1800, 3200, 100,   LDO45, 4, 4, RCTL12, 5),
	DA9030_LDO( 6, 1800, 3200, 100,    LDO6, 0, 4, RCTL12, 6),
	DA9030_LDO( 7, 1800, 3200, 100,   LDO78, 0, 4, RCTL12, 7),
	DA9030_LDO( 8, 1800, 3200, 100,   LDO78, 4, 4, RCTL22, 0),
	DA9030_LDO( 9, 1800, 3200, 100,  LDO912, 0, 4, RCTL22, 1),
	DA9030_LDO(10, 1800, 3200, 100, LDO1011, 0, 4, RCTL22, 2),
	DA9030_LDO(11, 1800, 3200, 100, LDO1011, 4, 4, RCTL22, 3),
	DA9030_LDO(12, 1800, 3200, 100,  LDO912, 4, 4, RCTL22, 4),
	DA9030_LDO(14, 2760, 2940,  30, LDO1416, 0, 3, RCTL11, 4),
	DA9030_LDO(15, 1100, 2650,  50,	  LDO15, 0, 5, RCTL11, 5),
	DA9030_LDO(16, 1100, 2650,  50, LDO1416, 3, 5, RCTL11, 6),
	DA9030_LDO(17, 1800, 3200, 100,   LDO17, 0, 4, RCTL11, 7),
	DA9030_LDO(18, 1800, 3200, 100, LDO1819, 0, 4, RCTL21, 2),
	DA9030_LDO(19, 1800, 3200, 100, LDO1819, 4, 4, RCTL21, 1),
	DA9030_LDO(13, 2100, 2100, 0, INVAL, 0, 0, RCTL11, 3), /* fixed @2.1V */

	/* DA9034 */
	DA9034_DVC(BUCK1, 725, 1500, 25, ADTV2, 5, VCC1, 0, OVER1, 0),
	DA9034_DVC(BUCK2, 725, 1500, 25, CDTV2, 5, VCC1, 2, OVER1, 1),
	DA9034_DVC(LDO2,  725, 1500, 25, SDTV2, 5, VCC1, 4, OVER1, 2),
	DA9034_DVC(LDO1, 1700, 2075, 25, MDTV1, 4, VCC1, 6, OVER3, 4),

	DA9034_LDO( 3, 1800, 3300, 100,  LDO643, 0, 4, OVER3, 5),
	DA9034_LDO( 4, 1800, 2900,1100,  LDO643, 4, 1, OVER3, 6),
	DA9034_LDO( 6, 2500, 2850,  50,  LDO643, 5, 3, OVER2, 0),
	DA9034_LDO( 7, 2700, 3050,  50,  LDO987, 0, 3, OVER2, 1),
	DA9034_LDO( 8, 2700, 2850,  50,  LDO987, 3, 2, OVER2, 2),
	DA9034_LDO( 9, 2700, 3050,  50,  LDO987, 5, 3, OVER2, 3),
	DA9034_LDO(10, 2700, 3050,  50, LDO1110, 0, 3, OVER2, 4),
	DA9034_LDO(11, 1800, 3300, 100, LDO1110, 4, 4, OVER2, 5),
	DA9034_LDO(12, 1700, 3050,  50, LDO1312, 0, 4, OVER3, 6),
	DA9034_LDO(13, 1800, 3300, 100, LDO1312, 4, 4, OVER2, 7),
	DA9034_LDO(14, 1800, 3300, 100, LDO1514, 0, 4, OVER3, 0),
	DA9034_LDO(15, 1800, 3300, 100, LDO1514, 4, 4, OVER3, 1),
	DA9034_LDO(5, 3100, 3100, 0, INVAL, 0, 0, OVER3, 7), /* fixed @3.1V */

	/* DA9035 */
	DA9035_DVC(BUCK3, 1800, 2200, 100, 3DTV1, 3, VCC2, 0, OVER3, 3),
पूर्ण;

अटल अंतरभूत काष्ठा da903x_regulator_info *find_regulator_info(पूर्णांक id)
अणु
	काष्ठा da903x_regulator_info *ri;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(da903x_regulator_info); i++) अणु
		ri = &da903x_regulator_info[i];
		अगर (ri->desc.id == id)
			वापस ri;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक da903x_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da903x_regulator_info *ri = शून्य;
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;

	ri = find_regulator_info(pdev->id);
	अगर (ri == शून्य) अणु
		dev_err(&pdev->dev, "invalid regulator ID specified\n");
		वापस -EINVAL;
	पूर्ण

	/* Workaround क्रम the weird LDO12 voltage setting */
	अगर (ri->desc.id == DA9034_ID_LDO12) अणु
		ri->desc.ops = &da9034_regulator_lकरो12_ops;
		ri->desc.n_voltages = 16;
		ri->desc.linear_ranges = da9034_lकरो12_ranges;
		ri->desc.n_linear_ranges = ARRAY_SIZE(da9034_lकरो12_ranges);
	पूर्ण

	अगर (ri->desc.id == DA9030_ID_LDO14)
		ri->desc.ops = &da9030_regulator_lकरो14_ops;

	अगर (ri->desc.id == DA9030_ID_LDO1 || ri->desc.id == DA9030_ID_LDO15)
		ri->desc.ops = &da9030_regulator_lकरो1_15_ops;

	config.dev = &pdev->dev;
	config.init_data = dev_get_platdata(&pdev->dev);
	config.driver_data = ri;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &ri->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "failed to register regulator %s\n",
				ri->desc.name);
		वापस PTR_ERR(rdev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, rdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da903x_regulator_driver = अणु
	.driver	= अणु
		.name	= "da903x-regulator",
	पूर्ण,
	.probe		= da903x_regulator_probe,
पूर्ण;

अटल पूर्णांक __init da903x_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&da903x_regulator_driver);
पूर्ण
subsys_initcall(da903x_regulator_init);

अटल व्योम __निकास da903x_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&da903x_regulator_driver);
पूर्ण
module_निकास(da903x_regulator_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>"
	      "Mike Rapoport <mike@compulab.co.il>");
MODULE_DESCRIPTION("Regulator Driver for Dialog Semiconductor DA903X PMIC");
MODULE_ALIAS("platform:da903x-regulator");
