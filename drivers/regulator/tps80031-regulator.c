<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// tps80031-regulator.c -- TI TPS80031 regulator driver.
//
// Regulator driver क्रम TI TPS80031/TPS80032 Fully Integrated Power
// Management with Power Path and Battery Charger.
//
// Copyright (c) 2012, NVIDIA Corporation.
//
// Author: Laxman Dewangan <ldewangan@nvidia.com>

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/tps80031.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/slab.h>

/* Flags क्रम DCDC Voltage पढ़ोing */
#घोषणा DCDC_OFFSET_EN		BIT(0)
#घोषणा DCDC_EXTENDED_EN	BIT(1)
#घोषणा TRACK_MODE_ENABLE	BIT(2)

#घोषणा SMPS_MULTOFFSET_VIO	BIT(1)
#घोषणा SMPS_MULTOFFSET_SMPS1	BIT(3)
#घोषणा SMPS_MULTOFFSET_SMPS2	BIT(4)
#घोषणा SMPS_MULTOFFSET_SMPS3	BIT(6)
#घोषणा SMPS_MULTOFFSET_SMPS4	BIT(0)

#घोषणा SMPS_CMD_MASK		0xC0
#घोषणा SMPS_VSEL_MASK		0x3F
#घोषणा LDO_VSEL_MASK		0x1F
#घोषणा LDO_TRACK_VSEL_MASK	0x3F

#घोषणा MISC2_LDOUSB_IN_VSYS	BIT(4)
#घोषणा MISC2_LDOUSB_IN_PMID	BIT(3)
#घोषणा MISC2_LDOUSB_IN_MASK	0x18

#घोषणा MISC2_LDO3_SEL_VIB_VAL	BIT(0)
#घोषणा MISC2_LDO3_SEL_VIB_MASK	0x1

#घोषणा BOOST_HW_PWR_EN		BIT(5)
#घोषणा BOOST_HW_PWR_EN_MASK	BIT(5)

#घोषणा OPA_MODE_EN		BIT(6)
#घोषणा OPA_MODE_EN_MASK	BIT(6)

#घोषणा USB_VBUS_CTRL_SET	0x04
#घोषणा USB_VBUS_CTRL_CLR	0x05
#घोषणा VBUS_DISCHRG		0x20

काष्ठा tps80031_regulator_info अणु
	/* Regulator रेजिस्टर address.*/
	u8		trans_reg;
	u8		state_reg;
	u8		क्रमce_reg;
	u8		volt_reg;
	u8		volt_id;

	/*Power request bits */
	पूर्णांक		preq_bit;

	/* used by regulator core */
	काष्ठा regulator_desc	desc;

पूर्ण;

काष्ठा tps80031_regulator अणु
	काष्ठा device			*dev;
	काष्ठा tps80031_regulator_info	*rinfo;

	u8				device_flags;
	अचिन्हित पूर्णांक			config_flags;
	अचिन्हित पूर्णांक			ext_ctrl_flag;
पूर्ण;

अटल अंतरभूत काष्ठा device *to_tps80031_dev(काष्ठा regulator_dev *rdev)
अणु
	वापस rdev_get_dev(rdev)->parent->parent;
पूर्ण

अटल पूर्णांक tps80031_reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);
	u8 reg_val;
	पूर्णांक ret;

	अगर (ri->ext_ctrl_flag & TPS80031_EXT_PWR_REQ)
		वापस true;

	ret = tps80031_पढ़ो(parent, TPS80031_SLAVE_ID1, ri->rinfo->state_reg,
				&reg_val);
	अगर (ret < 0) अणु
		dev_err(&rdev->dev, "Reg 0x%02x read failed, err = %d\n",
			ri->rinfo->state_reg, ret);
		वापस ret;
	पूर्ण
	वापस (reg_val & TPS80031_STATE_MASK) == TPS80031_STATE_ON;
पूर्ण

अटल पूर्णांक tps80031_reg_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);
	पूर्णांक ret;

	अगर (ri->ext_ctrl_flag & TPS80031_EXT_PWR_REQ)
		वापस 0;

	ret = tps80031_update(parent, TPS80031_SLAVE_ID1, ri->rinfo->state_reg,
			TPS80031_STATE_ON, TPS80031_STATE_MASK);
	अगर (ret < 0) अणु
		dev_err(&rdev->dev, "Reg 0x%02x update failed, err = %d\n",
			ri->rinfo->state_reg, ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tps80031_reg_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);
	पूर्णांक ret;

	अगर (ri->ext_ctrl_flag & TPS80031_EXT_PWR_REQ)
		वापस 0;

	ret = tps80031_update(parent, TPS80031_SLAVE_ID1, ri->rinfo->state_reg,
			TPS80031_STATE_OFF, TPS80031_STATE_MASK);
	अगर (ret < 0)
		dev_err(&rdev->dev, "Reg 0x%02x update failed, err = %d\n",
			ri->rinfo->state_reg, ret);
	वापस ret;
पूर्ण

/* DCDC voltages क्रम the selector of 58 to 63 */
अटल स्थिर पूर्णांक tps80031_dcdc_voltages[4][5] = अणु
	अणु 1350, 1500, 1800, 1900, 2100पूर्ण,
	अणु 1350, 1500, 1800, 1900, 2100पूर्ण,
	अणु 2084, 2315, 2778, 2932, 3241पूर्ण,
	अणु 4167, 2315, 2778, 2932, 3241पूर्ण,
पूर्ण;

अटल पूर्णांक tps80031_dcdc_list_voltage(काष्ठा regulator_dev *rdev, अचिन्हित sel)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	पूर्णांक volt_index = ri->device_flags & 0x3;

	अगर (sel == 0)
		वापस 0;
	अन्यथा अगर (sel < 58)
		वापस regulator_list_voltage_linear(rdev, sel - 1);
	अन्यथा
		वापस tps80031_dcdc_voltages[volt_index][sel - 58] * 1000;
पूर्ण

अटल पूर्णांक tps80031_dcdc_set_voltage_sel(काष्ठा regulator_dev *rdev,
		अचिन्हित vsel)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);
	पूर्णांक ret;
	u8 reg_val;

	अगर (ri->rinfo->क्रमce_reg) अणु
		ret = tps80031_पढ़ो(parent, ri->rinfo->volt_id,
						ri->rinfo->क्रमce_reg, &reg_val);
		अगर (ret < 0) अणु
			dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
				ri->rinfo->क्रमce_reg, ret);
			वापस ret;
		पूर्ण
		अगर (!(reg_val & SMPS_CMD_MASK)) अणु
			ret = tps80031_update(parent, ri->rinfo->volt_id,
				ri->rinfo->क्रमce_reg, vsel, SMPS_VSEL_MASK);
			अगर (ret < 0)
				dev_err(ri->dev,
					"reg 0x%02x update failed, e = %d\n",
					ri->rinfo->क्रमce_reg, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	ret = tps80031_update(parent, ri->rinfo->volt_id,
			ri->rinfo->volt_reg, vsel, SMPS_VSEL_MASK);
	अगर (ret < 0)
		dev_err(ri->dev, "reg 0x%02x update failed, e = %d\n",
			ri->rinfo->volt_reg, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tps80031_dcdc_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);
	uपूर्णांक8_t vsel = 0;
	पूर्णांक ret;

	अगर (ri->rinfo->क्रमce_reg) अणु
		ret = tps80031_पढ़ो(parent, ri->rinfo->volt_id,
						ri->rinfo->क्रमce_reg, &vsel);
		अगर (ret < 0) अणु
			dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
					ri->rinfo->क्रमce_reg, ret);
			वापस ret;
		पूर्ण

		अगर (!(vsel & SMPS_CMD_MASK))
			वापस vsel & SMPS_VSEL_MASK;
	पूर्ण
	ret = tps80031_पढ़ो(parent, ri->rinfo->volt_id,
				ri->rinfo->volt_reg, &vsel);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
			ri->rinfo->volt_reg, ret);
		वापस ret;
	पूर्ण
	वापस vsel & SMPS_VSEL_MASK;
पूर्ण

अटल पूर्णांक tps80031_lकरो_list_voltage(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक sel)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);

	/* Check क्रम valid setting क्रम TPS80031 or TPS80032-ES1.0 */
	अगर ((ri->rinfo->desc.id == TPS80031_REGULATOR_LDO2) &&
			(ri->device_flags & TRACK_MODE_ENABLE)) अणु
		अचिन्हित nvsel = (sel) & 0x1F;
		अगर (((tps80031_get_chip_info(parent) == TPS80031) ||
			((tps80031_get_chip_info(parent) == TPS80032) &&
			(tps80031_get_pmu_version(parent) == 0x0))) &&
			((nvsel == 0x0) || (nvsel >= 0x19 && nvsel <= 0x1F))) अणु
				dev_err(ri->dev,
					"Invalid sel %d in track mode LDO2\n",
					nvsel);
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस regulator_list_voltage_linear(rdev, sel);
पूर्ण

अटल पूर्णांक tps80031_lकरो_map_voltage(काष्ठा regulator_dev *rdev,
				    पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);

	/* Check क्रम valid setting क्रम TPS80031 or TPS80032-ES1.0 */
	अगर ((ri->rinfo->desc.id == TPS80031_REGULATOR_LDO2) &&
			(ri->device_flags & TRACK_MODE_ENABLE)) अणु
		अगर (((tps80031_get_chip_info(parent) == TPS80031) ||
			((tps80031_get_chip_info(parent) == TPS80032) &&
			(tps80031_get_pmu_version(parent) == 0x0)))) अणु
			वापस regulator_map_voltage_iterate(rdev, min_uV,
							     max_uV);
		पूर्ण
	पूर्ण

	वापस regulator_map_voltage_linear(rdev, min_uV, max_uV);
पूर्ण

अटल पूर्णांक tps80031_vbus_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);
	पूर्णांक ret;
	uपूर्णांक8_t ctrl1 = 0;
	uपूर्णांक8_t ctrl3 = 0;

	ret = tps80031_पढ़ो(parent, TPS80031_SLAVE_ID2,
			TPS80031_CHARGERUSB_CTRL1, &ctrl1);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
			TPS80031_CHARGERUSB_CTRL1, ret);
		वापस ret;
	पूर्ण
	ret = tps80031_पढ़ो(parent, TPS80031_SLAVE_ID2,
				TPS80031_CHARGERUSB_CTRL3, &ctrl3);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
			TPS80031_CHARGERUSB_CTRL3, ret);
		वापस ret;
	पूर्ण
	अगर ((ctrl1 & OPA_MODE_EN) && (ctrl3 & BOOST_HW_PWR_EN))
		वापस 1;
	वापस ret;
पूर्ण

अटल पूर्णांक tps80031_vbus_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);
	पूर्णांक ret;

	ret = tps80031_set_bits(parent, TPS80031_SLAVE_ID2,
				TPS80031_CHARGERUSB_CTRL1, OPA_MODE_EN);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
					TPS80031_CHARGERUSB_CTRL1, ret);
		वापस ret;
	पूर्ण

	ret = tps80031_set_bits(parent, TPS80031_SLAVE_ID2,
				TPS80031_CHARGERUSB_CTRL3, BOOST_HW_PWR_EN);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
			TPS80031_CHARGERUSB_CTRL3, ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tps80031_vbus_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps80031_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा device *parent = to_tps80031_dev(rdev);
	पूर्णांक ret;

	अगर (ri->config_flags & TPS80031_VBUS_DISCHRG_EN_PDN) अणु
		ret = tps80031_ग_लिखो(parent, TPS80031_SLAVE_ID2,
			USB_VBUS_CTRL_SET, VBUS_DISCHRG);
		अगर (ret < 0) अणु
			dev_err(ri->dev, "reg 0x%02x write failed, e = %d\n",
				USB_VBUS_CTRL_SET, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = tps80031_clr_bits(parent, TPS80031_SLAVE_ID2,
			TPS80031_CHARGERUSB_CTRL1,  OPA_MODE_EN);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "reg 0x%02x clearbit failed, e = %d\n",
				TPS80031_CHARGERUSB_CTRL1, ret);
		वापस ret;
	पूर्ण

	ret = tps80031_clr_bits(parent, TPS80031_SLAVE_ID2,
				TPS80031_CHARGERUSB_CTRL3, BOOST_HW_PWR_EN);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "reg 0x%02x clearbit failed, e = %d\n",
				TPS80031_CHARGERUSB_CTRL3, ret);
		वापस ret;
	पूर्ण

	mdelay(DIV_ROUND_UP(ri->rinfo->desc.enable_समय, 1000));
	अगर (ri->config_flags & TPS80031_VBUS_DISCHRG_EN_PDN) अणु
		ret = tps80031_ग_लिखो(parent, TPS80031_SLAVE_ID2,
			USB_VBUS_CTRL_CLR, VBUS_DISCHRG);
		अगर (ret < 0) अणु
			dev_err(ri->dev, "reg 0x%02x write failed, e = %d\n",
					USB_VBUS_CTRL_CLR, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops tps80031_dcdc_ops = अणु
	.list_voltage		= tps80031_dcdc_list_voltage,
	.set_voltage_sel	= tps80031_dcdc_set_voltage_sel,
	.get_voltage_sel	= tps80031_dcdc_get_voltage_sel,
	.enable		= tps80031_reg_enable,
	.disable	= tps80031_reg_disable,
	.is_enabled	= tps80031_reg_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps80031_lकरो_ops = अणु
	.list_voltage		= tps80031_lकरो_list_voltage,
	.map_voltage		= tps80031_lकरो_map_voltage,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.enable			= tps80031_reg_enable,
	.disable		= tps80031_reg_disable,
	.is_enabled		= tps80031_reg_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps80031_vbus_sw_ops = अणु
	.list_voltage	= regulator_list_voltage_linear,
	.enable		= tps80031_vbus_enable,
	.disable	= tps80031_vbus_disable,
	.is_enabled	= tps80031_vbus_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps80031_vbus_hw_ops = अणु
	.list_voltage	= regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps80031_ext_reg_ops = अणु
	.list_voltage	= regulator_list_voltage_linear,
	.enable		= tps80031_reg_enable,
	.disable	= tps80031_reg_disable,
	.is_enabled	= tps80031_reg_is_enabled,
पूर्ण;

/* Non-निकासing शेष definition क्रम some रेजिस्टर */
#घोषणा TPS80031_SMPS3_CFG_FORCE	0
#घोषणा TPS80031_SMPS4_CFG_FORCE	0

#घोषणा TPS80031_VBUS_CFG_TRANS		0
#घोषणा TPS80031_VBUS_CFG_STATE		0

#घोषणा TPS80031_REG_SMPS(_id, _volt_id, _pbit)	\
अणु								\
	.trans_reg = TPS80031_##_id##_CFG_TRANS,		\
	.state_reg = TPS80031_##_id##_CFG_STATE,		\
	.क्रमce_reg = TPS80031_##_id##_CFG_FORCE,		\
	.volt_reg = TPS80031_##_id##_CFG_VOLTAGE,		\
	.volt_id = TPS80031_SLAVE_##_volt_id,			\
	.preq_bit = _pbit,					\
	.desc = अणु						\
		.name = "tps80031_"#_id,			\
		.id = TPS80031_REGULATOR_##_id,			\
		.n_voltages = 63,				\
		.ops = &tps80031_dcdc_ops,			\
		.type = REGULATOR_VOLTAGE,			\
		.owner = THIS_MODULE,				\
		.enable_समय = 500,				\
	पूर्ण,							\
पूर्ण

#घोषणा TPS80031_REG_LDO(_id, _preq_bit)			\
अणु								\
	.trans_reg = TPS80031_##_id##_CFG_TRANS,		\
	.state_reg = TPS80031_##_id##_CFG_STATE,		\
	.volt_reg = TPS80031_##_id##_CFG_VOLTAGE,		\
	.volt_id = TPS80031_SLAVE_ID1,				\
	.preq_bit = _preq_bit,					\
	.desc = अणु						\
		.owner = THIS_MODULE,				\
		.name = "tps80031_"#_id,			\
		.id = TPS80031_REGULATOR_##_id,			\
		.ops = &tps80031_lकरो_ops,			\
		.type = REGULATOR_VOLTAGE,			\
		.min_uV = 1000000,				\
		.uV_step = 100000,				\
		.linear_min_sel = 1,				\
		.n_voltages = 25,				\
		.vsel_reg = TPS80031_##_id##_CFG_VOLTAGE,	\
		.vsel_mask = LDO_VSEL_MASK,			\
		.enable_समय = 500,				\
	पूर्ण,							\
पूर्ण

#घोषणा TPS80031_REG_FIXED(_id, max_mV, _ops, _delay, _pbit)	\
अणु								\
	.trans_reg = TPS80031_##_id##_CFG_TRANS,		\
	.state_reg = TPS80031_##_id##_CFG_STATE,		\
	.volt_id = TPS80031_SLAVE_ID1,				\
	.preq_bit = _pbit,					\
	.desc = अणु						\
		.name = "tps80031_"#_id,			\
		.id = TPS80031_REGULATOR_##_id,			\
		.min_uV = max_mV * 1000,			\
		.n_voltages = 1,				\
		.ops = &_ops,					\
		.type = REGULATOR_VOLTAGE,			\
		.owner = THIS_MODULE,				\
		.enable_समय = _delay,				\
	पूर्ण,							\
पूर्ण

अटल काष्ठा tps80031_regulator_info tps80031_rinfo[TPS80031_REGULATOR_MAX] = अणु
	TPS80031_REG_SMPS(VIO,   ID0, 4),
	TPS80031_REG_SMPS(SMPS1, ID0, 0),
	TPS80031_REG_SMPS(SMPS2, ID0, 1),
	TPS80031_REG_SMPS(SMPS3, ID1, 2),
	TPS80031_REG_SMPS(SMPS4, ID1, 3),
	TPS80031_REG_LDO(VANA,   -1),
	TPS80031_REG_LDO(LDO1,   8),
	TPS80031_REG_LDO(LDO2,   9),
	TPS80031_REG_LDO(LDO3,   10),
	TPS80031_REG_LDO(LDO4,   11),
	TPS80031_REG_LDO(LDO5,   12),
	TPS80031_REG_LDO(LDO6,   13),
	TPS80031_REG_LDO(LDO7,   14),
	TPS80031_REG_LDO(LDOLN,  15),
	TPS80031_REG_LDO(LDOUSB, 5),
	TPS80031_REG_FIXED(VBUS,   5000, tps80031_vbus_hw_ops, 100000, -1),
	TPS80031_REG_FIXED(REGEN1, 3300, tps80031_ext_reg_ops, 0, 16),
	TPS80031_REG_FIXED(REGEN2, 3300, tps80031_ext_reg_ops, 0, 17),
	TPS80031_REG_FIXED(SYSEN,  3300, tps80031_ext_reg_ops, 0, 18),
पूर्ण;

अटल पूर्णांक tps80031_घातer_req_config(काष्ठा device *parent,
		काष्ठा tps80031_regulator *ri,
		काष्ठा tps80031_regulator_platक्रमm_data *tps80031_pdata)
अणु
	पूर्णांक ret = 0;

	अगर (ri->rinfo->preq_bit < 0)
		जाओ skip_pwr_req_config;

	ret = tps80031_ext_घातer_req_config(parent, ri->ext_ctrl_flag,
			ri->rinfo->preq_bit, ri->rinfo->state_reg,
			ri->rinfo->trans_reg);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "ext powerreq config failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

skip_pwr_req_config:
	अगर (tps80031_pdata->ext_ctrl_flag & TPS80031_PWR_ON_ON_SLEEP) अणु
		ret = tps80031_update(parent, TPS80031_SLAVE_ID1,
				ri->rinfo->trans_reg, TPS80031_TRANS_SLEEP_ON,
				TPS80031_TRANS_SLEEP_MASK);
		अगर (ret < 0) अणु
			dev_err(ri->dev, "Reg 0x%02x update failed, e %d\n",
					ri->rinfo->trans_reg, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tps80031_regulator_config(काष्ठा device *parent,
		काष्ठा tps80031_regulator *ri,
		काष्ठा tps80031_regulator_platक्रमm_data *tps80031_pdata)
अणु
	पूर्णांक ret = 0;

	चयन (ri->rinfo->desc.id) अणु
	हाल TPS80031_REGULATOR_LDOUSB:
		अगर (ri->config_flags & (TPS80031_USBLDO_INPUT_VSYS |
			TPS80031_USBLDO_INPUT_PMID)) अणु
			अचिन्हित val;

			अगर (ri->config_flags & TPS80031_USBLDO_INPUT_VSYS)
				val = MISC2_LDOUSB_IN_VSYS;
			अन्यथा
				val = MISC2_LDOUSB_IN_PMID;

			ret = tps80031_update(parent, TPS80031_SLAVE_ID1,
				TPS80031_MISC2, val,
				MISC2_LDOUSB_IN_MASK);
			अगर (ret < 0) अणु
				dev_err(ri->dev,
					"LDOUSB config failed, e= %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल TPS80031_REGULATOR_LDO3:
		अगर (ri->config_flags & TPS80031_LDO3_OUTPUT_VIB) अणु
			ret = tps80031_update(parent, TPS80031_SLAVE_ID1,
				TPS80031_MISC2, MISC2_LDO3_SEL_VIB_VAL,
				MISC2_LDO3_SEL_VIB_MASK);
			अगर (ret < 0) अणु
				dev_err(ri->dev,
					"LDO3 config failed, e = %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल TPS80031_REGULATOR_VBUS:
		/* Provide SW control Ops अगर VBUS is SW control */
		अगर (!(ri->config_flags & TPS80031_VBUS_SW_ONLY))
			ri->rinfo->desc.ops = &tps80031_vbus_sw_ops;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Configure Active state to ON, SLEEP to OFF and OFF_state to OFF */
	ret = tps80031_update(parent, TPS80031_SLAVE_ID1, ri->rinfo->trans_reg,
		TPS80031_TRANS_ACTIVE_ON | TPS80031_TRANS_SLEEP_OFF |
		TPS80031_TRANS_OFF_OFF, TPS80031_TRANS_ACTIVE_MASK |
		TPS80031_TRANS_SLEEP_MASK | TPS80031_TRANS_OFF_MASK);
	अगर (ret < 0) अणु
		dev_err(ri->dev, "trans reg update failed, e %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक check_smps_mode_mult(काष्ठा device *parent,
	काष्ठा tps80031_regulator *ri)
अणु
	पूर्णांक mult_offset;
	पूर्णांक ret;
	u8 smps_offset;
	u8 smps_mult;

	ret = tps80031_पढ़ो(parent, TPS80031_SLAVE_ID1,
			TPS80031_SMPS_OFFSET, &smps_offset);
	अगर (ret < 0) अणु
		dev_err(parent, "Error in reading smps offset register\n");
		वापस ret;
	पूर्ण

	ret = tps80031_पढ़ो(parent, TPS80031_SLAVE_ID1,
			TPS80031_SMPS_MULT, &smps_mult);
	अगर (ret < 0) अणु
		dev_err(parent, "Error in reading smps mult register\n");
		वापस ret;
	पूर्ण

	चयन (ri->rinfo->desc.id) अणु
	हाल TPS80031_REGULATOR_VIO:
		mult_offset = SMPS_MULTOFFSET_VIO;
		अवरोध;
	हाल TPS80031_REGULATOR_SMPS1:
		mult_offset = SMPS_MULTOFFSET_SMPS1;
		अवरोध;
	हाल TPS80031_REGULATOR_SMPS2:
		mult_offset = SMPS_MULTOFFSET_SMPS2;
		अवरोध;
	हाल TPS80031_REGULATOR_SMPS3:
		mult_offset = SMPS_MULTOFFSET_SMPS3;
		अवरोध;
	हाल TPS80031_REGULATOR_SMPS4:
		mult_offset = SMPS_MULTOFFSET_SMPS4;
		अवरोध;
	हाल TPS80031_REGULATOR_LDO2:
		ri->device_flags = smps_mult & BIT(5) ? TRACK_MODE_ENABLE : 0;
		/* TRACK mode the lकरो2 varies from 600mV to 1300mV */
		अगर (ri->device_flags & TRACK_MODE_ENABLE) अणु
			ri->rinfo->desc.min_uV = 600000;
			ri->rinfo->desc.uV_step = 12500;
			ri->rinfo->desc.n_voltages = 57;
			ri->rinfo->desc.vsel_mask = LDO_TRACK_VSEL_MASK;
		पूर्ण
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण

	ri->device_flags = (smps_offset & mult_offset) ? DCDC_OFFSET_EN : 0;
	ri->device_flags |= (smps_mult & mult_offset) ? DCDC_EXTENDED_EN : 0;
	चयन (ri->device_flags) अणु
	हाल 0:
		ri->rinfo->desc.min_uV = 607700;
		ri->rinfo->desc.uV_step = 12660;
		अवरोध;
	हाल DCDC_OFFSET_EN:
		ri->rinfo->desc.min_uV = 700000;
		ri->rinfo->desc.uV_step = 12500;
		अवरोध;
	हाल DCDC_EXTENDED_EN:
		ri->rinfo->desc.min_uV = 1852000;
		ri->rinfo->desc.uV_step = 38600;
		अवरोध;
	हाल DCDC_OFFSET_EN | DCDC_EXTENDED_EN:
		ri->rinfo->desc.min_uV = 2161000;
		ri->rinfo->desc.uV_step = 38600;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps80031_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps80031_platक्रमm_data *pdata;
	काष्ठा tps80031_regulator_platक्रमm_data *tps_pdata;
	काष्ठा tps80031_regulator *ri;
	काष्ठा tps80031_regulator *pmic;
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा tps80031 *tps80031_mfd = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक ret;
	पूर्णांक num;

	pdata = dev_get_platdata(pdev->dev.parent);

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	pmic = devm_kसुस्मृति(&pdev->dev,
			TPS80031_REGULATOR_MAX, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	क्रम (num = 0; num < TPS80031_REGULATOR_MAX; ++num) अणु
		tps_pdata = pdata->regulator_pdata[num];
		ri = &pmic[num];
		ri->rinfo = &tps80031_rinfo[num];
		ri->dev = &pdev->dev;

		check_smps_mode_mult(pdev->dev.parent, ri);
		config.dev = &pdev->dev;
		config.init_data = शून्य;
		config.driver_data = ri;
		config.regmap = tps80031_mfd->regmap[ri->rinfo->volt_id];

		अगर (tps_pdata) अणु
			config.init_data = tps_pdata->reg_init_data;
			ri->config_flags = tps_pdata->config_flags;
			ri->ext_ctrl_flag = tps_pdata->ext_ctrl_flag;
			ret = tps80031_regulator_config(pdev->dev.parent,
					ri, tps_pdata);
			अगर (ret < 0) अणु
				dev_err(&pdev->dev,
					"regulator config failed, e %d\n", ret);
				वापस ret;
			पूर्ण

			ret = tps80031_घातer_req_config(pdev->dev.parent,
					ri, tps_pdata);
			अगर (ret < 0) अणु
				dev_err(&pdev->dev,
					"pwr_req config failed, err %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &ri->rinfo->desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev,
				"register regulator failed %s\n",
					ri->rinfo->desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, pmic);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tps80031_regulator_driver = अणु
	.driver	= अणु
		.name	= "tps80031-pmic",
	पूर्ण,
	.probe		= tps80031_regulator_probe,
पूर्ण;

अटल पूर्णांक __init tps80031_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps80031_regulator_driver);
पूर्ण
subsys_initcall(tps80031_regulator_init);

अटल व्योम __निकास tps80031_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tps80031_regulator_driver);
पूर्ण
module_निकास(tps80031_regulator_निकास);

MODULE_ALIAS("platform:tps80031-regulator");
MODULE_DESCRIPTION("Regulator Driver for TI TPS80031/TPS80032 PMIC");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
