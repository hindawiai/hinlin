<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// SLG51000 High PSRR, Multi-Output Regulators
// Copyright (C) 2019  Dialog Semiconductor
//
// Author: Eric Jeong <eric.jeong.खोलोsource@diasemi.com>

#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश "slg51000-regulator.h"

#घोषणा SLG51000_SCTL_EVT               7
#घोषणा SLG51000_MAX_EVT_REGISTER       8
#घोषणा SLG51000_LDOHP_LV_MIN           1200000
#घोषणा SLG51000_LDOHP_HV_MIN           2400000

क्रमागत slg51000_regulators अणु
	SLG51000_REGULATOR_LDO1 = 0,
	SLG51000_REGULATOR_LDO2,
	SLG51000_REGULATOR_LDO3,
	SLG51000_REGULATOR_LDO4,
	SLG51000_REGULATOR_LDO5,
	SLG51000_REGULATOR_LDO6,
	SLG51000_REGULATOR_LDO7,
	SLG51000_MAX_REGULATORS,
पूर्ण;

काष्ठा slg51000 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_desc *rdesc[SLG51000_MAX_REGULATORS];
	काष्ठा regulator_dev *rdev[SLG51000_MAX_REGULATORS];
	काष्ठा gpio_desc *cs_gpiod;
	पूर्णांक chip_irq;
पूर्ण;

काष्ठा slg51000_evt_sta अणु
	अचिन्हित पूर्णांक ereg;
	अचिन्हित पूर्णांक sreg;
पूर्ण;

अटल स्थिर काष्ठा slg51000_evt_sta es_reg[SLG51000_MAX_EVT_REGISTER] = अणु
	अणुSLG51000_LDO1_EVENT, SLG51000_LDO1_STATUSपूर्ण,
	अणुSLG51000_LDO2_EVENT, SLG51000_LDO2_STATUSपूर्ण,
	अणुSLG51000_LDO3_EVENT, SLG51000_LDO3_STATUSपूर्ण,
	अणुSLG51000_LDO4_EVENT, SLG51000_LDO4_STATUSपूर्ण,
	अणुSLG51000_LDO5_EVENT, SLG51000_LDO5_STATUSपूर्ण,
	अणुSLG51000_LDO6_EVENT, SLG51000_LDO6_STATUSपूर्ण,
	अणुSLG51000_LDO7_EVENT, SLG51000_LDO7_STATUSपूर्ण,
	अणुSLG51000_SYSCTL_EVENT, SLG51000_SYSCTL_STATUSपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range slg51000_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(SLG51000_SYSCTL_MATRIX_CONF_A,
			 SLG51000_SYSCTL_MATRIX_CONF_A),
	regmap_reg_range(SLG51000_LDO1_VSEL, SLG51000_LDO1_VSEL),
	regmap_reg_range(SLG51000_LDO1_MINV, SLG51000_LDO1_MAXV),
	regmap_reg_range(SLG51000_LDO1_IRQ_MASK, SLG51000_LDO1_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO2_VSEL, SLG51000_LDO2_VSEL),
	regmap_reg_range(SLG51000_LDO2_MINV, SLG51000_LDO2_MAXV),
	regmap_reg_range(SLG51000_LDO2_IRQ_MASK, SLG51000_LDO2_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO3_VSEL, SLG51000_LDO3_VSEL),
	regmap_reg_range(SLG51000_LDO3_MINV, SLG51000_LDO3_MAXV),
	regmap_reg_range(SLG51000_LDO3_IRQ_MASK, SLG51000_LDO3_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO4_VSEL, SLG51000_LDO4_VSEL),
	regmap_reg_range(SLG51000_LDO4_MINV, SLG51000_LDO4_MAXV),
	regmap_reg_range(SLG51000_LDO4_IRQ_MASK, SLG51000_LDO4_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO5_VSEL, SLG51000_LDO5_VSEL),
	regmap_reg_range(SLG51000_LDO5_MINV, SLG51000_LDO5_MAXV),
	regmap_reg_range(SLG51000_LDO5_IRQ_MASK, SLG51000_LDO5_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO6_VSEL, SLG51000_LDO6_VSEL),
	regmap_reg_range(SLG51000_LDO6_MINV, SLG51000_LDO6_MAXV),
	regmap_reg_range(SLG51000_LDO6_IRQ_MASK, SLG51000_LDO6_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO7_VSEL, SLG51000_LDO7_VSEL),
	regmap_reg_range(SLG51000_LDO7_MINV, SLG51000_LDO7_MAXV),
	regmap_reg_range(SLG51000_LDO7_IRQ_MASK, SLG51000_LDO7_IRQ_MASK),
	regmap_reg_range(SLG51000_OTP_IRQ_MASK, SLG51000_OTP_IRQ_MASK),
पूर्ण;

अटल स्थिर काष्ठा regmap_range slg51000_पढ़ोable_ranges[] = अणु
	regmap_reg_range(SLG51000_SYSCTL_PATN_ID_B0,
			 SLG51000_SYSCTL_PATN_ID_B2),
	regmap_reg_range(SLG51000_SYSCTL_SYS_CONF_A,
			 SLG51000_SYSCTL_SYS_CONF_A),
	regmap_reg_range(SLG51000_SYSCTL_SYS_CONF_D,
			 SLG51000_SYSCTL_MATRIX_CONF_B),
	regmap_reg_range(SLG51000_SYSCTL_REFGEN_CONF_C,
			 SLG51000_SYSCTL_UVLO_CONF_A),
	regmap_reg_range(SLG51000_SYSCTL_FAULT_LOG1, SLG51000_SYSCTL_IRQ_MASK),
	regmap_reg_range(SLG51000_IO_GPIO1_CONF, SLG51000_IO_GPIO_STATUS),
	regmap_reg_range(SLG51000_LUTARRAY_LUT_VAL_0,
			 SLG51000_LUTARRAY_LUT_VAL_11),
	regmap_reg_range(SLG51000_MUXARRAY_INPUT_SEL_0,
			 SLG51000_MUXARRAY_INPUT_SEL_63),
	regmap_reg_range(SLG51000_PWRSEQ_RESOURCE_EN_0,
			 SLG51000_PWRSEQ_INPUT_SENSE_CONF_B),
	regmap_reg_range(SLG51000_LDO1_VSEL, SLG51000_LDO1_VSEL),
	regmap_reg_range(SLG51000_LDO1_MINV, SLG51000_LDO1_MAXV),
	regmap_reg_range(SLG51000_LDO1_MISC1, SLG51000_LDO1_VSEL_ACTUAL),
	regmap_reg_range(SLG51000_LDO1_EVENT, SLG51000_LDO1_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO2_VSEL, SLG51000_LDO2_VSEL),
	regmap_reg_range(SLG51000_LDO2_MINV, SLG51000_LDO2_MAXV),
	regmap_reg_range(SLG51000_LDO2_MISC1, SLG51000_LDO2_VSEL_ACTUAL),
	regmap_reg_range(SLG51000_LDO2_EVENT, SLG51000_LDO2_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO3_VSEL, SLG51000_LDO3_VSEL),
	regmap_reg_range(SLG51000_LDO3_MINV, SLG51000_LDO3_MAXV),
	regmap_reg_range(SLG51000_LDO3_CONF1, SLG51000_LDO3_VSEL_ACTUAL),
	regmap_reg_range(SLG51000_LDO3_EVENT, SLG51000_LDO3_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO4_VSEL, SLG51000_LDO4_VSEL),
	regmap_reg_range(SLG51000_LDO4_MINV, SLG51000_LDO4_MAXV),
	regmap_reg_range(SLG51000_LDO4_CONF1, SLG51000_LDO4_VSEL_ACTUAL),
	regmap_reg_range(SLG51000_LDO4_EVENT, SLG51000_LDO4_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO5_VSEL, SLG51000_LDO5_VSEL),
	regmap_reg_range(SLG51000_LDO5_MINV, SLG51000_LDO5_MAXV),
	regmap_reg_range(SLG51000_LDO5_TRIM2, SLG51000_LDO5_TRIM2),
	regmap_reg_range(SLG51000_LDO5_CONF1, SLG51000_LDO5_VSEL_ACTUAL),
	regmap_reg_range(SLG51000_LDO5_EVENT, SLG51000_LDO5_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO6_VSEL, SLG51000_LDO6_VSEL),
	regmap_reg_range(SLG51000_LDO6_MINV, SLG51000_LDO6_MAXV),
	regmap_reg_range(SLG51000_LDO6_TRIM2, SLG51000_LDO6_TRIM2),
	regmap_reg_range(SLG51000_LDO6_CONF1, SLG51000_LDO6_VSEL_ACTUAL),
	regmap_reg_range(SLG51000_LDO6_EVENT, SLG51000_LDO6_IRQ_MASK),
	regmap_reg_range(SLG51000_LDO7_VSEL, SLG51000_LDO7_VSEL),
	regmap_reg_range(SLG51000_LDO7_MINV, SLG51000_LDO7_MAXV),
	regmap_reg_range(SLG51000_LDO7_CONF1, SLG51000_LDO7_VSEL_ACTUAL),
	regmap_reg_range(SLG51000_LDO7_EVENT, SLG51000_LDO7_IRQ_MASK),
	regmap_reg_range(SLG51000_OTP_EVENT, SLG51000_OTP_EVENT),
	regmap_reg_range(SLG51000_OTP_IRQ_MASK, SLG51000_OTP_IRQ_MASK),
	regmap_reg_range(SLG51000_OTP_LOCK_OTP_PROG, SLG51000_OTP_LOCK_CTRL),
	regmap_reg_range(SLG51000_LOCK_GLOBAL_LOCK_CTRL1,
			 SLG51000_LOCK_GLOBAL_LOCK_CTRL1),
पूर्ण;

अटल स्थिर काष्ठा regmap_range slg51000_अस्थिर_ranges[] = अणु
	regmap_reg_range(SLG51000_SYSCTL_FAULT_LOG1, SLG51000_SYSCTL_STATUS),
	regmap_reg_range(SLG51000_IO_GPIO_STATUS, SLG51000_IO_GPIO_STATUS),
	regmap_reg_range(SLG51000_LDO1_EVENT, SLG51000_LDO1_STATUS),
	regmap_reg_range(SLG51000_LDO2_EVENT, SLG51000_LDO2_STATUS),
	regmap_reg_range(SLG51000_LDO3_EVENT, SLG51000_LDO3_STATUS),
	regmap_reg_range(SLG51000_LDO4_EVENT, SLG51000_LDO4_STATUS),
	regmap_reg_range(SLG51000_LDO5_EVENT, SLG51000_LDO5_STATUS),
	regmap_reg_range(SLG51000_LDO6_EVENT, SLG51000_LDO6_STATUS),
	regmap_reg_range(SLG51000_LDO7_EVENT, SLG51000_LDO7_STATUS),
	regmap_reg_range(SLG51000_OTP_EVENT, SLG51000_OTP_EVENT),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table slg51000_ग_लिखोable_table = अणु
	.yes_ranges	= slg51000_ग_लिखोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(slg51000_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table slg51000_पढ़ोable_table = अणु
	.yes_ranges	= slg51000_पढ़ोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(slg51000_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table slg51000_अस्थिर_table = अणु
	.yes_ranges	= slg51000_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(slg51000_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config slg51000_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.max_रेजिस्टर = 0x8000,
	.wr_table = &slg51000_ग_लिखोable_table,
	.rd_table = &slg51000_पढ़ोable_table,
	.अस्थिर_table = &slg51000_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops slg51000_regl_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops slg51000_चयन_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल पूर्णांक slg51000_of_parse_cb(काष्ठा device_node *np,
				स्थिर काष्ठा regulator_desc *desc,
				काष्ठा regulator_config *config)
अणु
	काष्ठा gpio_desc *ena_gpiod;

	ena_gpiod = fwnode_gpiod_get_index(of_fwnode_handle(np), "enable", 0,
					   GPIOD_OUT_LOW |
						GPIOD_FLAGS_BIT_NONEXCLUSIVE,
					   "gpio-en-ldo");
	अगर (!IS_ERR(ena_gpiod))
		config->ena_gpiod = ena_gpiod;

	वापस 0;
पूर्ण

#घोषणा SLG51000_REGL_DESC(_id, _name, _s_name, _min, _step) \
	[SLG51000_REGULATOR_##_id] = अणु                             \
		.name = #_name,                                    \
		.supply_name = _s_name,				   \
		.id = SLG51000_REGULATOR_##_id,                    \
		.of_match = of_match_ptr(#_name),                  \
		.of_parse_cb = slg51000_of_parse_cb,               \
		.ops = &slg51000_regl_ops,                         \
		.regulators_node = of_match_ptr("regulators"),     \
		.n_voltages = 256,                                 \
		.min_uV = _min,                                    \
		.uV_step = _step,                                  \
		.linear_min_sel = 0,                               \
		.vsel_mask = SLG51000_VSEL_MASK,                   \
		.vsel_reg = SLG51000_##_id##_VSEL,                 \
		.enable_reg = SLG51000_SYSCTL_MATRIX_CONF_A,       \
		.enable_mask = BIT(SLG51000_REGULATOR_##_id),      \
		.type = REGULATOR_VOLTAGE,                         \
		.owner = THIS_MODULE,                              \
	पूर्ण

अटल काष्ठा regulator_desc regls_desc[SLG51000_MAX_REGULATORS] = अणु
	SLG51000_REGL_DESC(LDO1, lकरो1, शून्य,   2400000,  5000),
	SLG51000_REGL_DESC(LDO2, lकरो2, शून्य,   2400000,  5000),
	SLG51000_REGL_DESC(LDO3, lकरो3, "vin3", 1200000, 10000),
	SLG51000_REGL_DESC(LDO4, lकरो4, "vin4", 1200000, 10000),
	SLG51000_REGL_DESC(LDO5, lकरो5, "vin5",  400000,  5000),
	SLG51000_REGL_DESC(LDO6, lकरो6, "vin6",  400000,  5000),
	SLG51000_REGL_DESC(LDO7, lकरो7, "vin7", 1200000, 10000),
पूर्ण;

अटल पूर्णांक slg51000_regulator_init(काष्ठा slg51000 *chip)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_desc *rdesc;
	अचिन्हित पूर्णांक reg, val;
	u8 vsel_range[2];
	पूर्णांक id, ret = 0;
	स्थिर अचिन्हित पूर्णांक min_regs[SLG51000_MAX_REGULATORS] = अणु
		SLG51000_LDO1_MINV, SLG51000_LDO2_MINV, SLG51000_LDO3_MINV,
		SLG51000_LDO4_MINV, SLG51000_LDO5_MINV, SLG51000_LDO6_MINV,
		SLG51000_LDO7_MINV,
	पूर्ण;

	क्रम (id = 0; id < SLG51000_MAX_REGULATORS; id++) अणु
		chip->rdesc[id] = &regls_desc[id];
		rdesc = chip->rdesc[id];
		config.regmap = chip->regmap;
		config.dev = chip->dev;
		config.driver_data = chip;

		ret = regmap_bulk_पढ़ो(chip->regmap, min_regs[id],
				       vsel_range, 2);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to read the MIN register\n");
			वापस ret;
		पूर्ण

		चयन (id) अणु
		हाल SLG51000_REGULATOR_LDO1:
		हाल SLG51000_REGULATOR_LDO2:
			अगर (id == SLG51000_REGULATOR_LDO1)
				reg = SLG51000_LDO1_MISC1;
			अन्यथा
				reg = SLG51000_LDO2_MISC1;

			ret = regmap_पढ़ो(chip->regmap, reg, &val);
			अगर (ret < 0) अणु
				dev_err(chip->dev,
					"Failed to read voltage range of ldo%d\n",
					id + 1);
				वापस ret;
			पूर्ण

			rdesc->linear_min_sel = vsel_range[0];
			rdesc->n_voltages = vsel_range[1] + 1;
			अगर (val & SLG51000_SEL_VRANGE_MASK)
				rdesc->min_uV = SLG51000_LDOHP_HV_MIN
						+ (vsel_range[0]
						   * rdesc->uV_step);
			अन्यथा
				rdesc->min_uV = SLG51000_LDOHP_LV_MIN
						+ (vsel_range[0]
						   * rdesc->uV_step);
			अवरोध;

		हाल SLG51000_REGULATOR_LDO5:
		हाल SLG51000_REGULATOR_LDO6:
			अगर (id == SLG51000_REGULATOR_LDO5)
				reg = SLG51000_LDO5_TRIM2;
			अन्यथा
				reg = SLG51000_LDO6_TRIM2;

			ret = regmap_पढ़ो(chip->regmap, reg, &val);
			अगर (ret < 0) अणु
				dev_err(chip->dev,
					"Failed to read LDO mode register\n");
				वापस ret;
			पूर्ण

			अगर (val & SLG51000_SEL_BYP_MODE_MASK) अणु
				rdesc->ops = &slg51000_चयन_ops;
				rdesc->n_voltages = 0;
				rdesc->min_uV = 0;
				rdesc->uV_step = 0;
				rdesc->linear_min_sel = 0;
				अवरोध;
			पूर्ण
			fallthrough;	/* to the check below */

		शेष:
			rdesc->linear_min_sel = vsel_range[0];
			rdesc->n_voltages = vsel_range[1] + 1;
			rdesc->min_uV = rdesc->min_uV
					+ (vsel_range[0] * rdesc->uV_step);
			अवरोध;
		पूर्ण

		chip->rdev[id] = devm_regulator_रेजिस्टर(chip->dev, rdesc,
							 &config);
		अगर (IS_ERR(chip->rdev[id])) अणु
			ret = PTR_ERR(chip->rdev[id]);
			dev_err(chip->dev,
				"Failed to register regulator(%s):%d\n",
				chip->rdesc[id]->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t slg51000_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा slg51000 *chip = data;
	काष्ठा regmap *regmap = chip->regmap;
	क्रमागत अणु R0 = 0, R1, R2, REG_MAX पूर्ण;
	u8 evt[SLG51000_MAX_EVT_REGISTER][REG_MAX];
	पूर्णांक ret, i, handled = IRQ_NONE;
	अचिन्हित पूर्णांक evt_otp, mask_otp;

	/* Read event[R0], status[R1] and mask[R2] रेजिस्टर */
	क्रम (i = 0; i < SLG51000_MAX_EVT_REGISTER; i++) अणु
		ret = regmap_bulk_पढ़ो(regmap, es_reg[i].ereg, evt[i], REG_MAX);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to read event registers(%d)\n", ret);
			वापस IRQ_NONE;
		पूर्ण
	पूर्ण

	ret = regmap_पढ़ो(regmap, SLG51000_OTP_EVENT, &evt_otp);
	अगर (ret < 0) अणु
		dev_err(chip->dev,
			"Failed to read otp event registers(%d)\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(regmap, SLG51000_OTP_IRQ_MASK, &mask_otp);
	अगर (ret < 0) अणु
		dev_err(chip->dev,
			"Failed to read otp mask register(%d)\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	अगर ((evt_otp & SLG51000_EVT_CRC_MASK) &&
	    !(mask_otp & SLG51000_IRQ_CRC_MASK)) अणु
		dev_info(chip->dev,
			 "OTP has been read or OTP crc is not zero\n");
		handled = IRQ_HANDLED;
	पूर्ण

	क्रम (i = 0; i < SLG51000_MAX_REGULATORS; i++) अणु
		अगर (!(evt[i][R2] & SLG51000_IRQ_ILIM_FLAG_MASK) &&
		    (evt[i][R0] & SLG51000_EVT_ILIM_FLAG_MASK)) अणु
			regulator_notअगरier_call_chain(chip->rdev[i],
					    REGULATOR_EVENT_OVER_CURRENT, शून्य);

			अगर (evt[i][R1] & SLG51000_STA_ILIM_FLAG_MASK)
				dev_warn(chip->dev,
					 "Over-current limit(ldo%d)\n", i + 1);
			handled = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	अगर (!(evt[SLG51000_SCTL_EVT][R2] & SLG51000_IRQ_HIGH_TEMP_WARN_MASK) &&
	    (evt[SLG51000_SCTL_EVT][R0] & SLG51000_EVT_HIGH_TEMP_WARN_MASK)) अणु
		क्रम (i = 0; i < SLG51000_MAX_REGULATORS; i++) अणु
			अगर (!(evt[i][R1] & SLG51000_STA_ILIM_FLAG_MASK) &&
			    (evt[i][R1] & SLG51000_STA_VOUT_OK_FLAG_MASK)) अणु
				regulator_notअगरier_call_chain(chip->rdev[i],
					       REGULATOR_EVENT_OVER_TEMP, शून्य);
			पूर्ण
		पूर्ण
		handled = IRQ_HANDLED;
		अगर (evt[SLG51000_SCTL_EVT][R1] &
		    SLG51000_STA_HIGH_TEMP_WARN_MASK)
			dev_warn(chip->dev, "High temperature warning!\n");
	पूर्ण

	वापस handled;
पूर्ण

अटल व्योम slg51000_clear_fault_log(काष्ठा slg51000 *chip)
अणु
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret = 0;

	ret = regmap_पढ़ो(chip->regmap, SLG51000_SYSCTL_FAULT_LOG1, &val);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read Fault log register\n");
		वापस;
	पूर्ण

	अगर (val & SLG51000_FLT_OVER_TEMP_MASK)
		dev_dbg(chip->dev, "Fault log: FLT_OVER_TEMP\n");
	अगर (val & SLG51000_FLT_POWER_SEQ_CRASH_REQ_MASK)
		dev_dbg(chip->dev, "Fault log: FLT_POWER_SEQ_CRASH_REQ\n");
	अगर (val & SLG51000_FLT_RST_MASK)
		dev_dbg(chip->dev, "Fault log: FLT_RST\n");
	अगर (val & SLG51000_FLT_POR_MASK)
		dev_dbg(chip->dev, "Fault log: FLT_POR\n");
पूर्ण

अटल पूर्णांक slg51000_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा slg51000 *chip;
	काष्ठा gpio_desc *cs_gpiod;
	पूर्णांक error, ret;

	chip = devm_kzalloc(dev, माप(काष्ठा slg51000), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	cs_gpiod = devm_gpiod_get_optional(dev, "dlg,cs",
					   GPIOD_OUT_HIGH |
						GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	अगर (IS_ERR(cs_gpiod))
		वापस PTR_ERR(cs_gpiod);

	अगर (cs_gpiod) अणु
		dev_info(dev, "Found chip selector property\n");
		chip->cs_gpiod = cs_gpiod;
	पूर्ण

	i2c_set_clientdata(client, chip);
	chip->chip_irq = client->irq;
	chip->dev = dev;
	chip->regmap = devm_regmap_init_i2c(client, &slg51000_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		error = PTR_ERR(chip->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	ret = slg51000_regulator_init(chip);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to init regulator(%d)\n", ret);
		वापस ret;
	पूर्ण

	slg51000_clear_fault_log(chip);

	अगर (chip->chip_irq) अणु
		ret = devm_request_thपढ़ोed_irq(dev, chip->chip_irq, शून्य,
						slg51000_irq_handler,
						(IRQF_TRIGGER_HIGH |
						IRQF_ONESHOT),
						"slg51000-irq", chip);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to request IRQ: %d\n",
				chip->chip_irq);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(dev, "No IRQ configured\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id slg51000_i2c_id[] = अणु
	अणु"slg51000", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, slg51000_i2c_id);

अटल काष्ठा i2c_driver slg51000_regulator_driver = अणु
	.driver = अणु
		.name = "slg51000-regulator",
	पूर्ण,
	.probe_new = slg51000_i2c_probe,
	.id_table = slg51000_i2c_id,
पूर्ण;

module_i2c_driver(slg51000_regulator_driver);

MODULE_AUTHOR("Eric Jeong <eric.jeong.opensource@diasemi.com>");
MODULE_DESCRIPTION("SLG51000 regulator driver");
MODULE_LICENSE("GPL");

