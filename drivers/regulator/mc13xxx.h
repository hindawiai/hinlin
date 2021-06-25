<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * mc13xxx.h - regulators क्रम the Freescale mc13xxx PMIC
 *
 *  Copyright (C) 2010 Yong Shen <yong.shen@linaro.org>
 */

#अगर_अघोषित __LINUX_REGULATOR_MC13XXX_H
#घोषणा __LINUX_REGULATOR_MC13XXX_H

#समावेश <linux/regulator/driver.h>

काष्ठा mc13xxx_regulator अणु
	काष्ठा regulator_desc desc;
	पूर्णांक reg;
	पूर्णांक enable_bit;
	पूर्णांक vsel_reg;
	पूर्णांक vsel_shअगरt;
	पूर्णांक vsel_mask;
पूर्ण;

काष्ठा mc13xxx_regulator_priv अणु
	काष्ठा mc13xxx *mc13xxx;
	u32 घातermisc_pwgt_state;
	काष्ठा mc13xxx_regulator *mc13xxx_regulators;
	पूर्णांक num_regulators;
	काष्ठा regulator_dev *regulators[];
पूर्ण;

बाह्य पूर्णांक mc13xxx_fixed_regulator_set_voltage(काष्ठा regulator_dev *rdev,
		पूर्णांक min_uV, पूर्णांक max_uV, अचिन्हित *selector);

#अगर_घोषित CONFIG_OF
बाह्य पूर्णांक mc13xxx_get_num_regulators_dt(काष्ठा platक्रमm_device *pdev);
बाह्य काष्ठा mc13xxx_regulator_init_data *mc13xxx_parse_regulators_dt(
	काष्ठा platक्रमm_device *pdev, काष्ठा mc13xxx_regulator *regulators,
	पूर्णांक num_regulators);
#अन्यथा
अटल अंतरभूत पूर्णांक mc13xxx_get_num_regulators_dt(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा mc13xxx_regulator_init_data *mc13xxx_parse_regulators_dt(
	काष्ठा platक्रमm_device *pdev, काष्ठा mc13xxx_regulator *regulators,
	पूर्णांक num_regulators)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

बाह्य स्थिर काष्ठा regulator_ops mc13xxx_regulator_ops;
बाह्य स्थिर काष्ठा regulator_ops mc13xxx_fixed_regulator_ops;

#घोषणा MC13xxx_DEFINE(prefix, _name, _node, _reg, _vsel_reg, _voltages, _ops)	\
	[prefix ## _name] = अणु				\
		.desc = अणु						\
			.name = #_node,					\
			.n_voltages = ARRAY_SIZE(_voltages),		\
			.volt_table =  _voltages,			\
			.ops = &_ops,			\
			.type = REGULATOR_VOLTAGE,			\
			.id = prefix ## _name,		\
			.owner = THIS_MODULE,				\
		पूर्ण,							\
		.reg = prefix ## _reg,				\
		.enable_bit = prefix ## _reg ## _ ## _name ## EN,	\
		.vsel_reg = prefix ## _vsel_reg,			\
		.vsel_shअगरt = prefix ## _vsel_reg ## _ ## _name ## VSEL,\
		.vsel_mask = prefix ## _vsel_reg ## _ ## _name ## VSEL_M,\
	पूर्ण

#घोषणा MC13xxx_FIXED_DEFINE(prefix, _name, _node, _reg, _voltages, _ops)	\
	[prefix ## _name] = अणु				\
		.desc = अणु						\
			.name = #_node,					\
			.n_voltages = ARRAY_SIZE(_voltages),		\
			.volt_table =  _voltages,			\
			.ops = &_ops,		\
			.type = REGULATOR_VOLTAGE,			\
			.id = prefix ## _name,		\
			.owner = THIS_MODULE,				\
		पूर्ण,							\
		.reg = prefix ## _reg,				\
		.enable_bit = prefix ## _reg ## _ ## _name ## EN,	\
	पूर्ण

#घोषणा MC13xxx_GPO_DEFINE(prefix, _name, _node, _reg,  _voltages, _ops)	\
	[prefix ## _name] = अणु				\
		.desc = अणु						\
			.name = #_node,					\
			.n_voltages = ARRAY_SIZE(_voltages),		\
			.volt_table =  _voltages,			\
			.ops = &_ops,		\
			.type = REGULATOR_VOLTAGE,			\
			.id = prefix ## _name,		\
			.owner = THIS_MODULE,				\
		पूर्ण,							\
		.reg = prefix ## _reg,				\
		.enable_bit = prefix ## _reg ## _ ## _name ## EN,	\
	पूर्ण

#घोषणा MC13xxx_DEFINE_SW(_name, _node, _reg, _vsel_reg, _voltages, ops) \
	MC13xxx_DEFINE(SW, _name, _node, _reg, _vsel_reg, _voltages, ops)
#घोषणा MC13xxx_DEFINE_REGU(_name, _node, _reg, _vsel_reg, _voltages, ops) \
	MC13xxx_DEFINE(REGU, _name, _node, _reg, _vsel_reg, _voltages, ops)

#पूर्ण_अगर
