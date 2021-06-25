<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * First generation of pinmux driver क्रम Amlogic Meson SoCs
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 * Copyright (C) 2017 Jerome Brunet  <jbrunet@baylibre.com>
 */

/* For this first generation of pinctrl driver every pinmux group can be
 * enabled by a specअगरic bit in the first रेजिस्टर range. When all groups क्रम
 * a given pin are disabled the pin acts as a GPIO.
 */
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>

#समावेश "pinctrl-meson.h"
#समावेश "pinctrl-meson8-pmx.h"

/**
 * meson8_pmx_disable_other_groups() - disable other groups using a given pin
 *
 * @pc:		meson pin controller device
 * @pin:	number of the pin
 * @sel_group:	index of the selected group, or -1 अगर none
 *
 * The function disables all pinmux groups using a pin except the
 * selected one. If @sel_group is -1 all groups are disabled, leaving
 * the pin in GPIO mode.
 */
अटल व्योम meson8_pmx_disable_other_groups(काष्ठा meson_pinctrl *pc,
					    अचिन्हित पूर्णांक pin, पूर्णांक sel_group)
अणु
	काष्ठा meson_pmx_group *group;
	काष्ठा meson8_pmx_data *pmx_data;
	पूर्णांक i, j;

	क्रम (i = 0; i < pc->data->num_groups; i++) अणु
		group = &pc->data->groups[i];
		pmx_data = (काष्ठा meson8_pmx_data *)group->data;
		अगर (pmx_data->is_gpio || i == sel_group)
			जारी;

		क्रम (j = 0; j < group->num_pins; j++) अणु
			अगर (group->pins[j] == pin) अणु
				/* We have found a group using the pin */
				regmap_update_bits(pc->reg_mux,
						   pmx_data->reg * 4,
						   BIT(pmx_data->bit), 0);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक meson8_pmx_set_mux(काष्ठा pinctrl_dev *pcdev, अचिन्हित func_num,
			      अचिन्हित group_num)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	काष्ठा meson_pmx_func *func = &pc->data->funcs[func_num];
	काष्ठा meson_pmx_group *group = &pc->data->groups[group_num];
	काष्ठा meson8_pmx_data *pmx_data =
		(काष्ठा meson8_pmx_data *)group->data;
	पूर्णांक i, ret = 0;

	dev_dbg(pc->dev, "enable function %s, group %s\n", func->name,
		group->name);

	/*
	 * Disable groups using the same pin.
	 * The selected group is not disabled to aव्योम glitches.
	 */
	क्रम (i = 0; i < group->num_pins; i++)
		meson8_pmx_disable_other_groups(pc, group->pins[i], group_num);

	/* Function 0 (GPIO) करोesn't need any additional setting */
	अगर (func_num)
		ret = regmap_update_bits(pc->reg_mux, pmx_data->reg * 4,
					 BIT(pmx_data->bit),
					 BIT(pmx_data->bit));

	वापस ret;
पूर्ण

अटल पूर्णांक meson8_pmx_request_gpio(काष्ठा pinctrl_dev *pcdev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित offset)
अणु
	काष्ठा meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);

	meson8_pmx_disable_other_groups(pc, offset, -1);

	वापस 0;
पूर्ण

स्थिर काष्ठा pinmux_ops meson8_pmx_ops = अणु
	.set_mux = meson8_pmx_set_mux,
	.get_functions_count = meson_pmx_get_funcs_count,
	.get_function_name = meson_pmx_get_func_name,
	.get_function_groups = meson_pmx_get_groups,
	.gpio_request_enable = meson8_pmx_request_gpio,
पूर्ण;
EXPORT_SYMBOL_GPL(meson8_pmx_ops);
MODULE_LICENSE("GPL v2");
