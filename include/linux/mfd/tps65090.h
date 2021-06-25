<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Core driver पूर्णांकerface क्रम TI TPS65090 PMIC family
 *
 * Copyright (C) 2012 NVIDIA Corporation
 */

#अगर_अघोषित __LINUX_MFD_TPS65090_H
#घोषणा __LINUX_MFD_TPS65090_H

#समावेश <linux/irq.h>
#समावेश <linux/regmap.h>

/* TPS65090 IRQs */
क्रमागत अणु
	TPS65090_IRQ_INTERRUPT,
	TPS65090_IRQ_VAC_STATUS_CHANGE,
	TPS65090_IRQ_VSYS_STATUS_CHANGE,
	TPS65090_IRQ_BAT_STATUS_CHANGE,
	TPS65090_IRQ_CHARGING_STATUS_CHANGE,
	TPS65090_IRQ_CHARGING_COMPLETE,
	TPS65090_IRQ_OVERLOAD_DCDC1,
	TPS65090_IRQ_OVERLOAD_DCDC2,
	TPS65090_IRQ_OVERLOAD_DCDC3,
	TPS65090_IRQ_OVERLOAD_FET1,
	TPS65090_IRQ_OVERLOAD_FET2,
	TPS65090_IRQ_OVERLOAD_FET3,
	TPS65090_IRQ_OVERLOAD_FET4,
	TPS65090_IRQ_OVERLOAD_FET5,
	TPS65090_IRQ_OVERLOAD_FET6,
	TPS65090_IRQ_OVERLOAD_FET7,
पूर्ण;

/* TPS65090 Regulator ID */
क्रमागत अणु
	TPS65090_REGULATOR_DCDC1,
	TPS65090_REGULATOR_DCDC2,
	TPS65090_REGULATOR_DCDC3,
	TPS65090_REGULATOR_FET1,
	TPS65090_REGULATOR_FET2,
	TPS65090_REGULATOR_FET3,
	TPS65090_REGULATOR_FET4,
	TPS65090_REGULATOR_FET5,
	TPS65090_REGULATOR_FET6,
	TPS65090_REGULATOR_FET7,
	TPS65090_REGULATOR_LDO1,
	TPS65090_REGULATOR_LDO2,

	/* Last entry क्रम maximum ID */
	TPS65090_REGULATOR_MAX,
पूर्ण;

/* Register addresses */
#घोषणा TPS65090_REG_INTR_STS	0x00
#घोषणा TPS65090_REG_INTR_STS2	0x01
#घोषणा TPS65090_REG_INTR_MASK	0x02
#घोषणा TPS65090_REG_INTR_MASK2	0x03
#घोषणा TPS65090_REG_CG_CTRL0	0x04
#घोषणा TPS65090_REG_CG_CTRL1	0x05
#घोषणा TPS65090_REG_CG_CTRL2	0x06
#घोषणा TPS65090_REG_CG_CTRL3	0x07
#घोषणा TPS65090_REG_CG_CTRL4	0x08
#घोषणा TPS65090_REG_CG_CTRL5	0x09
#घोषणा TPS65090_REG_CG_STATUS1	0x0a
#घोषणा TPS65090_REG_CG_STATUS2	0x0b
#घोषणा TPS65090_REG_AD_OUT1	0x17
#घोषणा TPS65090_REG_AD_OUT2	0x18

#घोषणा TPS65090_MAX_REG	TPS65090_REG_AD_OUT2
#घोषणा TPS65090_NUM_REGS	(TPS65090_MAX_REG + 1)

काष्ठा gpio_desc;

काष्ठा tps65090 अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*rmap;
	काष्ठा regmap_irq_chip_data *irq_data;
पूर्ण;

/*
 * काष्ठा tps65090_regulator_plat_data
 *
 * @reg_init_data: The regulator init data.
 * @enable_ext_control: Enable extrenal control or not. Only available क्रम
 *     DCDC1, DCDC2 and DCDC3.
 * @gpiod: Gpio descriptor अगर बाह्यal control is enabled and controlled through
 *     gpio
 * @overcurrent_रुको_valid: True अगर the overcurrent_रुको should be applied.
 * @overcurrent_रुको: Value to set as the overcurrent रुको समय.  This is the
 *     actual bitfield value, not a समय in ms (valid value are 0 - 3).
 */
काष्ठा tps65090_regulator_plat_data अणु
	काष्ठा regulator_init_data *reg_init_data;
	bool enable_ext_control;
	काष्ठा gpio_desc *gpiod;
	bool overcurrent_रुको_valid;
	पूर्णांक overcurrent_रुको;
पूर्ण;

काष्ठा tps65090_platक्रमm_data अणु
	पूर्णांक irq_base;

	अक्षर **supplied_to;
	माप_प्रकार num_supplicants;
	पूर्णांक enable_low_current_chrg;

	काष्ठा tps65090_regulator_plat_data *reg_pdata[TPS65090_REGULATOR_MAX];
पूर्ण;

/*
 * NOTE: the functions below are not पूर्णांकended क्रम use outside
 * of the TPS65090 sub-device drivers
 */
अटल अंतरभूत पूर्णांक tps65090_ग_लिखो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val)
अणु
	काष्ठा tps65090 *tps = dev_get_drvdata(dev);

	वापस regmap_ग_लिखो(tps->rmap, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक tps65090_पढ़ो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	काष्ठा tps65090 *tps = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक temp_val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tps->rmap, reg, &temp_val);
	अगर (!ret)
		*val = temp_val;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक tps65090_set_bits(काष्ठा device *dev, पूर्णांक reg,
		uपूर्णांक8_t bit_num)
अणु
	काष्ठा tps65090 *tps = dev_get_drvdata(dev);

	वापस regmap_update_bits(tps->rmap, reg, BIT(bit_num), ~0u);
पूर्ण

अटल अंतरभूत पूर्णांक tps65090_clr_bits(काष्ठा device *dev, पूर्णांक reg,
		uपूर्णांक8_t bit_num)
अणु
	काष्ठा tps65090 *tps = dev_get_drvdata(dev);

	वापस regmap_update_bits(tps->rmap, reg, BIT(bit_num), 0u);
पूर्ण

#पूर्ण_अगर /*__LINUX_MFD_TPS65090_H */
