<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 MediaTek Inc.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#अगर_अघोषित __PINCTRL_MTK_COMMON_V2_H
#घोषणा __PINCTRL_MTK_COMMON_V2_H

#समावेश <linux/gpio/driver.h>

#घोषणा MTK_INPUT      0
#घोषणा MTK_OUTPUT     1
#घोषणा MTK_DISABLE    0
#घोषणा MTK_ENABLE     1
#घोषणा MTK_PULLDOWN   0
#घोषणा MTK_PULLUP     1

#घोषणा EINT_NA	U16_MAX
#घोषणा NO_EINT_SUPPORT	EINT_NA

#घोषणा PIN_FIELD_CALC(_s_pin, _e_pin, _i_base, _s_addr, _x_addrs,      \
		       _s_bit, _x_bits, _sz_reg, _fixed) अणु		\
		.s_pin = _s_pin,					\
		.e_pin = _e_pin,					\
		.i_base = _i_base,					\
		.s_addr = _s_addr,					\
		.x_addrs = _x_addrs,					\
		.s_bit = _s_bit,					\
		.x_bits = _x_bits,					\
		.sz_reg = _sz_reg,					\
		.fixed = _fixed,					\
	पूर्ण

#घोषणा PIN_FIELD(_s_pin, _e_pin, _s_addr, _x_addrs, _s_bit, _x_bits)	\
	PIN_FIELD_CALC(_s_pin, _e_pin, 0, _s_addr, _x_addrs, _s_bit,	\
		       _x_bits, 32, 0)

#घोषणा PINS_FIELD(_s_pin, _e_pin, _s_addr, _x_addrs, _s_bit, _x_bits)	\
	PIN_FIELD_CALC(_s_pin, _e_pin, 0, _s_addr, _x_addrs, _s_bit,	\
		       _x_bits, 32, 1)

/* List these attributes which could be modअगरied क्रम the pin */
क्रमागत अणु
	PINCTRL_PIN_REG_MODE,
	PINCTRL_PIN_REG_सूची,
	PINCTRL_PIN_REG_DI,
	PINCTRL_PIN_REG_DO,
	PINCTRL_PIN_REG_SR,
	PINCTRL_PIN_REG_SMT,
	PINCTRL_PIN_REG_PD,
	PINCTRL_PIN_REG_PU,
	PINCTRL_PIN_REG_E4,
	PINCTRL_PIN_REG_E8,
	PINCTRL_PIN_REG_TDSEL,
	PINCTRL_PIN_REG_RDSEL,
	PINCTRL_PIN_REG_DRV,
	PINCTRL_PIN_REG_PUPD,
	PINCTRL_PIN_REG_R0,
	PINCTRL_PIN_REG_R1,
	PINCTRL_PIN_REG_IES,
	PINCTRL_PIN_REG_PULLEN,
	PINCTRL_PIN_REG_PULLSEL,
	PINCTRL_PIN_REG_DRV_EN,
	PINCTRL_PIN_REG_DRV_E0,
	PINCTRL_PIN_REG_DRV_E1,
	PINCTRL_PIN_REG_DRV_ADV,
	PINCTRL_PIN_REG_MAX,
पूर्ण;

/* Group the pins by the driving current */
क्रमागत अणु
	DRV_FIXED,
	DRV_GRP0,
	DRV_GRP1,
	DRV_GRP2,
	DRV_GRP3,
	DRV_GRP4,
	DRV_GRP_MAX,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mtk_शेष_रेजिस्टर_base_names[] __maybe_unused = अणु
	"base",
पूर्ण;

/* काष्ठा mtk_pin_field - the काष्ठाure that holds the inक्रमmation of the field
 *			  used to describe the attribute क्रम the pin
 * @base:		the index poपूर्णांकing to the entry in base address list
 * @offset:		the रेजिस्टर offset relative to the base address
 * @mask:		the mask used to filter out the field from the रेजिस्टर
 * @bitpos:		the start bit relative to the रेजिस्टर
 * @next:		the indication that the field would be extended to the
			next रेजिस्टर
 */
काष्ठा mtk_pin_field अणु
	u8  index;
	u32 offset;
	u32 mask;
	u8  bitpos;
	u8  next;
पूर्ण;

/* काष्ठा mtk_pin_field_calc - the काष्ठाure that holds the range providing
 *			       the guide used to look up the relevant field
 * @s_pin:		the start pin within the range
 * @e_pin:		the end pin within the range
 * @i_base:		the index poपूर्णांकing to the entry in base address list
 * @s_addr:		the start address क्रम the range
 * @x_addrs:		the address distance between two consecutive रेजिस्टरs
 *			within the range
 * @s_bit:		the start bit क्रम the first रेजिस्टर within the range
 * @x_bits:		the bit distance between two consecutive pins within
 *			the range
 * @sz_reg:		the size of bits in a रेजिस्टर
 * @fixed:		the consecutive pins share the same bits with the 1st
 *			pin
 */
काष्ठा mtk_pin_field_calc अणु
	u16 s_pin;
	u16 e_pin;
	u8  i_base;
	u32 s_addr;
	u8  x_addrs;
	u8  s_bit;
	u8  x_bits;
	u8  sz_reg;
	u8  fixed;
पूर्ण;

/* काष्ठा mtk_pin_reg_calc - the काष्ठाure that holds all ranges used to
 *			     determine which रेजिस्टर the pin would make use of
 *			     क्रम certain pin attribute.
 * @range:		     the start address क्रम the range
 * @nranges:		     the number of items in the range
 */
काष्ठा mtk_pin_reg_calc अणु
	स्थिर काष्ठा mtk_pin_field_calc *range;
	अचिन्हित पूर्णांक nranges;
पूर्ण;

/**
 * काष्ठा mtk_func_desc - the काष्ठाure that providing inक्रमmation
 *			  all the funcs क्रम this pin
 * @name:		the name of function
 * @muxval:		the mux to the function
 */
काष्ठा mtk_func_desc अणु
	स्थिर अक्षर *name;
	u8 muxval;
पूर्ण;

/**
 * काष्ठा mtk_eपूर्णांक_desc - the काष्ठाure that providing inक्रमmation
 *			       क्रम eपूर्णांक data per pin
 * @eपूर्णांक_m:		the eपूर्णांक mux क्रम this pin
 * @eitn_n:		the eपूर्णांक number क्रम this pin
 */
काष्ठा mtk_eपूर्णांक_desc अणु
	u16 eपूर्णांक_m;
	u16 eपूर्णांक_n;
पूर्ण;

/**
 * काष्ठा mtk_pin_desc - the काष्ठाure that providing inक्रमmation
 *			       क्रम each pin of chips
 * @number:		unique pin number from the global pin number space
 * @name:		name क्रम this pin
 * @eपूर्णांक:		the eपूर्णांक data क्रम this pin
 * @drv_n:		the index with the driving group
 * @funcs:		all available functions क्रम this pins (only used in
 *			those drivers compatible to pinctrl-mtk-common.c-like
 *			ones)
 */
काष्ठा mtk_pin_desc अणु
	अचिन्हित पूर्णांक number;
	स्थिर अक्षर *name;
	काष्ठा mtk_eपूर्णांक_desc eपूर्णांक;
	u8 drv_n;
	काष्ठा mtk_func_desc *funcs;
पूर्ण;

काष्ठा mtk_pinctrl_group अणु
	स्थिर अक्षर	*name;
	अचिन्हित दीर्घ	config;
	अचिन्हित	pin;
पूर्ण;

काष्ठा mtk_pinctrl;

/* काष्ठा mtk_pin_soc - the काष्ठाure that holds SoC-specअगरic data */
काष्ठा mtk_pin_soc अणु
	स्थिर काष्ठा mtk_pin_reg_calc	*reg_cal;
	स्थिर काष्ठा mtk_pin_desc	*pins;
	अचिन्हित पूर्णांक			npins;
	स्थिर काष्ठा group_desc		*grps;
	अचिन्हित पूर्णांक			ngrps;
	स्थिर काष्ठा function_desc	*funcs;
	अचिन्हित पूर्णांक			nfuncs;
	स्थिर काष्ठा mtk_eपूर्णांक_regs	*eपूर्णांक_regs;
	स्थिर काष्ठा mtk_eपूर्णांक_hw	*eपूर्णांक_hw;

	/* Specअगरic parameters per SoC */
	u8				gpio_m;
	bool				ies_present;
	स्थिर अक्षर * स्थिर		*base_names;
	अचिन्हित पूर्णांक			nbase_names;

	/* Specअगरic pinconfig operations */
	पूर्णांक (*bias_disable_set)(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc);
	पूर्णांक (*bias_disable_get)(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *res);
	पूर्णांक (*bias_set)(काष्ठा mtk_pinctrl *hw,
			स्थिर काष्ठा mtk_pin_desc *desc, bool pullup);
	पूर्णांक (*bias_get)(काष्ठा mtk_pinctrl *hw,
			स्थिर काष्ठा mtk_pin_desc *desc, bool pullup, पूर्णांक *res);

	पूर्णांक (*bias_set_combo)(काष्ठा mtk_pinctrl *hw,
			स्थिर काष्ठा mtk_pin_desc *desc, u32 pullup, u32 arg);
	पूर्णांक (*bias_get_combo)(काष्ठा mtk_pinctrl *hw,
			स्थिर काष्ठा mtk_pin_desc *desc, u32 *pullup, u32 *arg);

	पूर्णांक (*drive_set)(काष्ठा mtk_pinctrl *hw,
			 स्थिर काष्ठा mtk_pin_desc *desc, u32 arg);
	पूर्णांक (*drive_get)(काष्ठा mtk_pinctrl *hw,
			 स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *val);

	पूर्णांक (*adv_pull_set)(काष्ठा mtk_pinctrl *hw,
			    स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			    u32 arg);
	पूर्णांक (*adv_pull_get)(काष्ठा mtk_pinctrl *hw,
			    स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			    u32 *val);
	पूर्णांक (*adv_drive_set)(काष्ठा mtk_pinctrl *hw,
			     स्थिर काष्ठा mtk_pin_desc *desc, u32 arg);
	पूर्णांक (*adv_drive_get)(काष्ठा mtk_pinctrl *hw,
			     स्थिर काष्ठा mtk_pin_desc *desc, u32 *val);

	/* Specअगरic driver data */
	व्योम				*driver_data;
पूर्ण;

काष्ठा mtk_pinctrl अणु
	काष्ठा pinctrl_dev		*pctrl;
	व्योम __iomem			**base;
	u8				nbase;
	काष्ठा device			*dev;
	काष्ठा gpio_chip		chip;
	स्थिर काष्ठा mtk_pin_soc        *soc;
	काष्ठा mtk_eपूर्णांक			*eपूर्णांक;
	काष्ठा mtk_pinctrl_group	*groups;
	स्थिर अक्षर          **grp_names;
	/* lock pin's रेजिस्टर resource to aव्योम multiple thपढ़ोs issue*/
	spinlock_t lock;
पूर्ण;

व्योम mtk_rmw(काष्ठा mtk_pinctrl *pctl, u8 i, u32 reg, u32 mask, u32 set);

पूर्णांक mtk_hw_set_value(काष्ठा mtk_pinctrl *hw, स्थिर काष्ठा mtk_pin_desc *desc,
		     पूर्णांक field, पूर्णांक value);
पूर्णांक mtk_hw_get_value(काष्ठा mtk_pinctrl *hw, स्थिर काष्ठा mtk_pin_desc *desc,
		     पूर्णांक field, पूर्णांक *value);

पूर्णांक mtk_build_eपूर्णांक(काष्ठा mtk_pinctrl *hw, काष्ठा platक्रमm_device *pdev);

पूर्णांक mtk_pinconf_bias_disable_set(काष्ठा mtk_pinctrl *hw,
				 स्थिर काष्ठा mtk_pin_desc *desc);
पूर्णांक mtk_pinconf_bias_disable_get(काष्ठा mtk_pinctrl *hw,
				 स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *res);
पूर्णांक mtk_pinconf_bias_set(काष्ठा mtk_pinctrl *hw,
			 स्थिर काष्ठा mtk_pin_desc *desc, bool pullup);
पूर्णांक mtk_pinconf_bias_get(काष्ठा mtk_pinctrl *hw,
			 स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			 पूर्णांक *res);

पूर्णांक mtk_pinconf_bias_disable_set_rev1(काष्ठा mtk_pinctrl *hw,
				      स्थिर काष्ठा mtk_pin_desc *desc);
पूर्णांक mtk_pinconf_bias_disable_get_rev1(काष्ठा mtk_pinctrl *hw,
				      स्थिर काष्ठा mtk_pin_desc *desc,
				      पूर्णांक *res);
पूर्णांक mtk_pinconf_bias_set_rev1(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc, bool pullup);
पूर्णांक mtk_pinconf_bias_get_rev1(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			      पूर्णांक *res);
पूर्णांक mtk_pinconf_bias_set_combo(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				u32 pullup, u32 enable);
पूर्णांक mtk_pinconf_bias_get_combo(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc,
			      u32 *pullup, u32 *enable);

पूर्णांक mtk_pinconf_drive_set(काष्ठा mtk_pinctrl *hw,
			  स्थिर काष्ठा mtk_pin_desc *desc, u32 arg);
पूर्णांक mtk_pinconf_drive_get(काष्ठा mtk_pinctrl *hw,
			  स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *val);

पूर्णांक mtk_pinconf_drive_set_rev1(काष्ठा mtk_pinctrl *hw,
			       स्थिर काष्ठा mtk_pin_desc *desc, u32 arg);
पूर्णांक mtk_pinconf_drive_get_rev1(काष्ठा mtk_pinctrl *hw,
			       स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *val);

पूर्णांक mtk_pinconf_drive_set_raw(काष्ठा mtk_pinctrl *hw,
			       स्थिर काष्ठा mtk_pin_desc *desc, u32 arg);
पूर्णांक mtk_pinconf_drive_get_raw(काष्ठा mtk_pinctrl *hw,
			       स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *val);

पूर्णांक mtk_pinconf_adv_pull_set(काष्ठा mtk_pinctrl *hw,
			     स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			     u32 arg);
पूर्णांक mtk_pinconf_adv_pull_get(काष्ठा mtk_pinctrl *hw,
			     स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			     u32 *val);
पूर्णांक mtk_pinconf_adv_drive_set(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc, u32 arg);
पूर्णांक mtk_pinconf_adv_drive_get(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc, u32 *val);
पूर्णांक mtk_pinconf_adv_drive_set_raw(काष्ठा mtk_pinctrl *hw,
				  स्थिर काष्ठा mtk_pin_desc *desc, u32 arg);
पूर्णांक mtk_pinconf_adv_drive_get_raw(काष्ठा mtk_pinctrl *hw,
				  स्थिर काष्ठा mtk_pin_desc *desc, u32 *val);

bool mtk_is_virt_gpio(काष्ठा mtk_pinctrl *hw, अचिन्हित पूर्णांक gpio_n);
#पूर्ण_अगर /* __PINCTRL_MTK_COMMON_V2_H */
