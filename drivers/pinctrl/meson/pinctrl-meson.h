<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Pin controller and GPIO driver क्रम Amlogic Meson SoCs
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>

काष्ठा meson_pinctrl;

/**
 * काष्ठा meson_pmx_group - a pinmux group
 *
 * @name:	group name
 * @pins:	pins in the group
 * @num_pins:	number of pins in the group
 * @is_gpio:	whether the group is a single GPIO group
 * @reg:	रेजिस्टर offset क्रम the group in the करोमुख्य mux रेजिस्टरs
 * @bit		bit index enabling the group
 * @करोमुख्य:	index of the करोमुख्य this group beदीर्घs to
 */
काष्ठा meson_pmx_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक num_pins;
	स्थिर व्योम *data;
पूर्ण;

/**
 * काष्ठा meson_pmx_func - a pinmux function
 *
 * @name:	function name
 * @groups:	groups in the function
 * @num_groups:	number of groups in the function
 */
काष्ठा meson_pmx_func अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक num_groups;
पूर्ण;

/**
 * काष्ठा meson_reg_desc - a रेजिस्टर descriptor
 *
 * @reg:	रेजिस्टर offset in the regmap
 * @bit:	bit index in रेजिस्टर
 *
 * The काष्ठाure describes the inक्रमmation needed to control pull,
 * pull-enable, direction, etc. क्रम a single pin
 */
काष्ठा meson_reg_desc अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक bit;
पूर्ण;

/**
 * क्रमागत meson_reg_type - type of रेजिस्टरs encoded in @meson_reg_desc
 */
क्रमागत meson_reg_type अणु
	REG_PULLEN,
	REG_PULL,
	REG_सूची,
	REG_OUT,
	REG_IN,
	REG_DS,
	NUM_REG,
पूर्ण;

/**
 * क्रमागत meson_pinconf_drv - value of drive-strength supported
 */
क्रमागत meson_pinconf_drv अणु
	MESON_PINCONF_DRV_500UA,
	MESON_PINCONF_DRV_2500UA,
	MESON_PINCONF_DRV_3000UA,
	MESON_PINCONF_DRV_4000UA,
पूर्ण;

/**
 * काष्ठा meson bank
 *
 * @name:	bank name
 * @first:	first pin of the bank
 * @last:	last pin of the bank
 * @irq:	hwirq base number of the bank
 * @regs:	array of रेजिस्टर descriptors
 *
 * A bank represents a set of pins controlled by a contiguous set of
 * bits in the करोमुख्य रेजिस्टरs. The काष्ठाure specअगरies which bits in
 * the regmap control the dअगरferent functionalities. Each member of
 * the @regs array refers to the first pin of the bank.
 */
काष्ठा meson_bank अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक last;
	पूर्णांक irq_first;
	पूर्णांक irq_last;
	काष्ठा meson_reg_desc regs[NUM_REG];
पूर्ण;

काष्ठा meson_pinctrl_data अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	काष्ठा meson_pmx_group *groups;
	काष्ठा meson_pmx_func *funcs;
	अचिन्हित पूर्णांक num_pins;
	अचिन्हित पूर्णांक num_groups;
	अचिन्हित पूर्णांक num_funcs;
	काष्ठा meson_bank *banks;
	अचिन्हित पूर्णांक num_banks;
	स्थिर काष्ठा pinmux_ops *pmx_ops;
	व्योम *pmx_data;
	पूर्णांक (*parse_dt)(काष्ठा meson_pinctrl *pc);
पूर्ण;

काष्ठा meson_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pcdev;
	काष्ठा pinctrl_desc desc;
	काष्ठा meson_pinctrl_data *data;
	काष्ठा regmap *reg_mux;
	काष्ठा regmap *reg_pullen;
	काष्ठा regmap *reg_pull;
	काष्ठा regmap *reg_gpio;
	काष्ठा regmap *reg_ds;
	काष्ठा gpio_chip chip;
	काष्ठा device_node *of_node;
पूर्ण;

#घोषणा FUNCTION(fn)							\
	अणु								\
		.name = #fn,						\
		.groups = fn ## _groups,				\
		.num_groups = ARRAY_SIZE(fn ## _groups),		\
	पूर्ण

#घोषणा BANK_DS(n, f, l, fi, li, per, peb, pr, pb, dr, db, or, ob, ir, ib,     \
		dsr, dsb)                                                      \
	अणु								\
		.name		= n,					\
		.first		= f,					\
		.last		= l,					\
		.irq_first	= fi,					\
		.irq_last	= li,					\
		.regs = अणु						\
			[REG_PULLEN]	= अणु per, peb पूर्ण,			\
			[REG_PULL]	= अणु pr, pb पूर्ण,			\
			[REG_सूची]	= अणु dr, db पूर्ण,			\
			[REG_OUT]	= अणु or, ob पूर्ण,			\
			[REG_IN]	= अणु ir, ib पूर्ण,			\
			[REG_DS]	= अणु dsr, dsb पूर्ण,			\
		पूर्ण,							\
	 पूर्ण

#घोषणा BANK(n, f, l, fi, li, per, peb, pr, pb, dr, db, or, ob, ir, ib) \
	BANK_DS(n, f, l, fi, li, per, peb, pr, pb, dr, db, or, ob, ir, ib, 0, 0)

#घोषणा MESON_PIN(x) PINCTRL_PIN(x, #x)

/* Common pmx functions */
पूर्णांक meson_pmx_get_funcs_count(काष्ठा pinctrl_dev *pcdev);
स्थिर अक्षर *meson_pmx_get_func_name(काष्ठा pinctrl_dev *pcdev,
				    अचिन्हित selector);
पूर्णांक meson_pmx_get_groups(काष्ठा pinctrl_dev *pcdev,
			 अचिन्हित selector,
			 स्थिर अक्षर * स्थिर **groups,
			 अचिन्हित * स्थिर num_groups);

/* Common probe function */
पूर्णांक meson_pinctrl_probe(काष्ठा platक्रमm_device *pdev);
/* Common ao groups extra dt parse function क्रम SoCs beक्रमe g12a  */
पूर्णांक meson8_aobus_parse_dt_extra(काष्ठा meson_pinctrl *pc);
/* Common extra dt parse function क्रम SoCs like A1  */
पूर्णांक meson_a1_parse_dt_extra(काष्ठा meson_pinctrl *pc);
