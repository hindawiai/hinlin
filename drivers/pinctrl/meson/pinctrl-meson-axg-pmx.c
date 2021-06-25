<शैली गुरु>
/*
 * Second generation of pinmux driver क्रम Amlogic Meson-AXG SoC.
 *
 * Copyright (c) 2017 Baylibre SAS.
 * Author:  Jerome Brunet  <jbrunet@baylibre.com>
 *
 * Copyright (c) 2017 Amlogic, Inc. All rights reserved.
 * Author: Xingyu Chen <xingyu.chen@amlogic.com>
 *
 * SPDX-License-Identअगरier: (GPL-2.0+ or MIT)
 */

/*
 * This new generation of pinctrl IP is मुख्यly aकरोpted by the
 * Meson-AXG SoC and later series, which use 4-width continuous
 * रेजिस्टर bit to select the function क्रम each pin.
 *
 * The value 0 is always selecting the GPIO mode, जबतक other
 * values (start from 1) क्रम selecting the function mode.
 */
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>

#समावेश "pinctrl-meson.h"
#समावेश "pinctrl-meson-axg-pmx.h"

अटल पूर्णांक meson_axg_pmx_get_bank(काष्ठा meson_pinctrl *pc,
			अचिन्हित पूर्णांक pin,
			काष्ठा meson_pmx_bank **bank)
अणु
	पूर्णांक i;
	काष्ठा meson_axg_pmx_data *pmx = pc->data->pmx_data;

	क्रम (i = 0; i < pmx->num_pmx_banks; i++)
		अगर (pin >= pmx->pmx_banks[i].first &&
				pin <= pmx->pmx_banks[i].last) अणु
			*bank = &pmx->pmx_banks[i];
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक meson_pmx_calc_reg_and_offset(काष्ठा meson_pmx_bank *bank,
			अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक *reg,
			अचिन्हित पूर्णांक *offset)
अणु
	पूर्णांक shअगरt;

	shअगरt = pin - bank->first;

	*reg = bank->reg + (bank->offset + (shअगरt << 2)) / 32;
	*offset = (bank->offset + (shअगरt << 2)) % 32;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_axg_pmx_update_function(काष्ठा meson_pinctrl *pc,
			अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक func)
अणु
	पूर्णांक ret;
	पूर्णांक reg;
	पूर्णांक offset;
	काष्ठा meson_pmx_bank *bank;

	ret = meson_axg_pmx_get_bank(pc, pin, &bank);
	अगर (ret)
		वापस ret;

	meson_pmx_calc_reg_and_offset(bank, pin, &reg, &offset);

	ret = regmap_update_bits(pc->reg_mux, reg << 2,
		0xf << offset, (func & 0xf) << offset);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_axg_pmx_set_mux(काष्ठा pinctrl_dev *pcdev,
			अचिन्हित पूर्णांक func_num, अचिन्हित पूर्णांक group_num)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	काष्ठा meson_pmx_func *func = &pc->data->funcs[func_num];
	काष्ठा meson_pmx_group *group = &pc->data->groups[group_num];
	काष्ठा meson_pmx_axg_data *pmx_data =
		(काष्ठा meson_pmx_axg_data *)group->data;

	dev_dbg(pc->dev, "enable function %s, group %s\n", func->name,
		group->name);

	क्रम (i = 0; i < group->num_pins; i++) अणु
		ret = meson_axg_pmx_update_function(pc, group->pins[i],
			pmx_data->func);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_axg_pmx_request_gpio(काष्ठा pinctrl_dev *pcdev,
			काष्ठा pinctrl_gpio_range *range, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	वापस meson_axg_pmx_update_function(pc, offset, 0);
पूर्ण

स्थिर काष्ठा pinmux_ops meson_axg_pmx_ops = अणु
	.set_mux = meson_axg_pmx_set_mux,
	.get_functions_count = meson_pmx_get_funcs_count,
	.get_function_name = meson_pmx_get_func_name,
	.get_function_groups = meson_pmx_get_groups,
	.gpio_request_enable = meson_axg_pmx_request_gpio,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_axg_pmx_ops);

MODULE_LICENSE("Dual BSD/GPL");
