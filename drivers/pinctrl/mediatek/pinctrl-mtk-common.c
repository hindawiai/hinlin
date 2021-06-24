<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mt65xx pinctrl driver based on Allwinner A1X pinctrl driver.
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <dt-bindings/pinctrl/mt65xx.h>

#समावेश "../core.h"
#समावेश "../pinconf.h"
#समावेश "../pinctrl-utils.h"
#समावेश "mtk-eint.h"
#समावेश "pinctrl-mtk-common.h"

#घोषणा MAX_GPIO_MODE_PER_REG 5
#घोषणा GPIO_MODE_BITS        3
#घोषणा GPIO_MODE_PREFIX "GPIO"

अटल स्थिर अक्षर * स्थिर mtk_gpio_functions[] = अणु
	"func0", "func1", "func2", "func3",
	"func4", "func5", "func6", "func7",
	"func8", "func9", "func10", "func11",
	"func12", "func13", "func14", "func15",
पूर्ण;

/*
 * There are two base address क्रम pull related configuration
 * in mt8135, and dअगरferent GPIO pins use dअगरferent base address.
 * When pin number greater than type1_start and less than type1_end,
 * should use the second base address.
 */
अटल काष्ठा regmap *mtk_get_regmap(काष्ठा mtk_pinctrl *pctl,
		अचिन्हित दीर्घ pin)
अणु
	अगर (pin >= pctl->devdata->type1_start && pin < pctl->devdata->type1_end)
		वापस pctl->regmap2;
	वापस pctl->regmap1;
पूर्ण

अटल अचिन्हित पूर्णांक mtk_get_port(काष्ठा mtk_pinctrl *pctl, अचिन्हित दीर्घ pin)
अणु
	/* Dअगरferent SoC has dअगरferent mask and port shअगरt. */
	वापस ((pin >> 4) & pctl->devdata->port_mask)
			<< pctl->devdata->port_shf;
पूर्ण

अटल पूर्णांक mtk_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_gpio_range *range, अचिन्हित offset,
			bool input)
अणु
	अचिन्हित पूर्णांक reg_addr;
	अचिन्हित पूर्णांक bit;
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	reg_addr = mtk_get_port(pctl, offset) + pctl->devdata->dir_offset;
	bit = BIT(offset & 0xf);

	अगर (pctl->devdata->spec_dir_set)
		pctl->devdata->spec_dir_set(&reg_addr, offset);

	अगर (input)
		/* Dअगरferent SoC has dअगरferent alignment offset. */
		reg_addr = CLR_ADDR(reg_addr, pctl);
	अन्यथा
		reg_addr = SET_ADDR(reg_addr, pctl);

	regmap_ग_लिखो(mtk_get_regmap(pctl, offset), reg_addr, bit);
	वापस 0;
पूर्ण

अटल व्योम mtk_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक reg_addr;
	अचिन्हित पूर्णांक bit;
	काष्ठा mtk_pinctrl *pctl = gpiochip_get_data(chip);

	reg_addr = mtk_get_port(pctl, offset) + pctl->devdata->करोut_offset;
	bit = BIT(offset & 0xf);

	अगर (value)
		reg_addr = SET_ADDR(reg_addr, pctl);
	अन्यथा
		reg_addr = CLR_ADDR(reg_addr, pctl);

	regmap_ग_लिखो(mtk_get_regmap(pctl, offset), reg_addr, bit);
पूर्ण

अटल पूर्णांक mtk_pconf_set_ies_smt(काष्ठा mtk_pinctrl *pctl, अचिन्हित pin,
		पूर्णांक value, क्रमागत pin_config_param arg)
अणु
	अचिन्हित पूर्णांक reg_addr, offset;
	अचिन्हित पूर्णांक bit;

	/**
	 * Due to some soc are not support ies/smt config, add this special
	 * control to handle it.
	 */
	अगर (!pctl->devdata->spec_ies_smt_set &&
		pctl->devdata->ies_offset == MTK_PINCTRL_NOT_SUPPORT &&
			arg == PIN_CONFIG_INPUT_ENABLE)
		वापस -EINVAL;

	अगर (!pctl->devdata->spec_ies_smt_set &&
		pctl->devdata->smt_offset == MTK_PINCTRL_NOT_SUPPORT &&
			arg == PIN_CONFIG_INPUT_SCHMITT_ENABLE)
		वापस -EINVAL;

	/*
	 * Due to some pins are irregular, their input enable and smt
	 * control रेजिस्टर are discontinuous, so we need this special handle.
	 */
	अगर (pctl->devdata->spec_ies_smt_set) अणु
		वापस pctl->devdata->spec_ies_smt_set(mtk_get_regmap(pctl, pin),
			pin, pctl->devdata->port_align, value, arg);
	पूर्ण

	bit = BIT(pin & 0xf);

	अगर (arg == PIN_CONFIG_INPUT_ENABLE)
		offset = pctl->devdata->ies_offset;
	अन्यथा
		offset = pctl->devdata->smt_offset;

	अगर (value)
		reg_addr = SET_ADDR(mtk_get_port(pctl, pin) + offset, pctl);
	अन्यथा
		reg_addr = CLR_ADDR(mtk_get_port(pctl, pin) + offset, pctl);

	regmap_ग_लिखो(mtk_get_regmap(pctl, pin), reg_addr, bit);
	वापस 0;
पूर्ण

पूर्णांक mtk_pconf_spec_set_ies_smt_range(काष्ठा regmap *regmap,
		स्थिर काष्ठा mtk_pin_ies_smt_set *ies_smt_infos, अचिन्हित पूर्णांक info_num,
		अचिन्हित पूर्णांक pin, अचिन्हित अक्षर align, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक i, reg_addr, bit;

	क्रम (i = 0; i < info_num; i++) अणु
		अगर (pin >= ies_smt_infos[i].start &&
				pin <= ies_smt_infos[i].end) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == info_num)
		वापस -EINVAL;

	अगर (value)
		reg_addr = ies_smt_infos[i].offset + align;
	अन्यथा
		reg_addr = ies_smt_infos[i].offset + (align << 1);

	bit = BIT(ies_smt_infos[i].bit);
	regmap_ग_लिखो(regmap, reg_addr, bit);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_pin_drv_grp *mtk_find_pin_drv_grp_by_pin(
		काष्ठा mtk_pinctrl *pctl,  अचिन्हित दीर्घ pin) अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->devdata->n_pin_drv_grps; i++) अणु
		स्थिर काष्ठा mtk_pin_drv_grp *pin_drv =
				pctl->devdata->pin_drv_grp + i;
		अगर (pin == pin_drv->pin)
			वापस pin_drv;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mtk_pconf_set_driving(काष्ठा mtk_pinctrl *pctl,
		अचिन्हित पूर्णांक pin, अचिन्हित अक्षर driving)
अणु
	स्थिर काष्ठा mtk_pin_drv_grp *pin_drv;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक bits, mask, shअगरt;
	स्थिर काष्ठा mtk_drv_group_desc *drv_grp;

	अगर (pin >= pctl->devdata->npins)
		वापस -EINVAL;

	pin_drv = mtk_find_pin_drv_grp_by_pin(pctl, pin);
	अगर (!pin_drv || pin_drv->grp > pctl->devdata->n_grp_cls)
		वापस -EINVAL;

	drv_grp = pctl->devdata->grp_desc + pin_drv->grp;
	अगर (driving >= drv_grp->min_drv && driving <= drv_grp->max_drv
		&& !(driving % drv_grp->step)) अणु
		val = driving / drv_grp->step - 1;
		bits = drv_grp->high_bit - drv_grp->low_bit + 1;
		mask = BIT(bits) - 1;
		shअगरt = pin_drv->bit + drv_grp->low_bit;
		mask <<= shअगरt;
		val <<= shअगरt;
		वापस regmap_update_bits(mtk_get_regmap(pctl, pin),
				pin_drv->offset, mask, val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक mtk_pctrl_spec_pull_set_samereg(काष्ठा regmap *regmap,
		स्थिर काष्ठा mtk_pin_spec_pupd_set_samereg *pupd_infos,
		अचिन्हित पूर्णांक info_num, अचिन्हित पूर्णांक pin,
		अचिन्हित अक्षर align, bool isup, अचिन्हित पूर्णांक r1r0)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक reg_pupd, reg_set, reg_rst;
	अचिन्हित पूर्णांक bit_pupd, bit_r0, bit_r1;
	स्थिर काष्ठा mtk_pin_spec_pupd_set_samereg *spec_pupd_pin;
	bool find = false;

	क्रम (i = 0; i < info_num; i++) अणु
		अगर (pin == pupd_infos[i].pin) अणु
			find = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!find)
		वापस -EINVAL;

	spec_pupd_pin = pupd_infos + i;
	reg_set = spec_pupd_pin->offset + align;
	reg_rst = spec_pupd_pin->offset + (align << 1);

	अगर (isup)
		reg_pupd = reg_rst;
	अन्यथा
		reg_pupd = reg_set;

	bit_pupd = BIT(spec_pupd_pin->pupd_bit);
	regmap_ग_लिखो(regmap, reg_pupd, bit_pupd);

	bit_r0 = BIT(spec_pupd_pin->r0_bit);
	bit_r1 = BIT(spec_pupd_pin->r1_bit);

	चयन (r1r0) अणु
	हाल MTK_PUPD_SET_R1R0_00:
		regmap_ग_लिखो(regmap, reg_rst, bit_r0);
		regmap_ग_लिखो(regmap, reg_rst, bit_r1);
		अवरोध;
	हाल MTK_PUPD_SET_R1R0_01:
		regmap_ग_लिखो(regmap, reg_set, bit_r0);
		regmap_ग_लिखो(regmap, reg_rst, bit_r1);
		अवरोध;
	हाल MTK_PUPD_SET_R1R0_10:
		regmap_ग_लिखो(regmap, reg_rst, bit_r0);
		regmap_ग_लिखो(regmap, reg_set, bit_r1);
		अवरोध;
	हाल MTK_PUPD_SET_R1R0_11:
		regmap_ग_लिखो(regmap, reg_set, bit_r0);
		regmap_ग_लिखो(regmap, reg_set, bit_r1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pconf_set_pull_select(काष्ठा mtk_pinctrl *pctl,
		अचिन्हित पूर्णांक pin, bool enable, bool isup, अचिन्हित पूर्णांक arg)
अणु
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक reg_pullen, reg_pullsel, r1r0;
	पूर्णांक ret;

	/* Some pins' pull setting are very dअगरferent,
	 * they have separate pull up/करोwn bit, R0 and R1
	 * resistor bit, so we need this special handle.
	 */
	अगर (pctl->devdata->spec_pull_set) अणु
		/* For special pins, bias-disable is set by R1R0,
		 * the parameter should be "MTK_PUPD_SET_R1R0_00".
		 */
		r1r0 = enable ? arg : MTK_PUPD_SET_R1R0_00;
		ret = pctl->devdata->spec_pull_set(mtk_get_regmap(pctl, pin),
			pin, pctl->devdata->port_align, isup, r1r0);
		अगर (!ret)
			वापस 0;
	पूर्ण

	/* For generic pull config, शेष arg value should be 0 or 1. */
	अगर (arg != 0 && arg != 1) अणु
		dev_err(pctl->dev, "invalid pull-up argument %d on pin %d .\n",
			arg, pin);
		वापस -EINVAL;
	पूर्ण

	bit = BIT(pin & 0xf);
	अगर (enable)
		reg_pullen = SET_ADDR(mtk_get_port(pctl, pin) +
			pctl->devdata->pullen_offset, pctl);
	अन्यथा
		reg_pullen = CLR_ADDR(mtk_get_port(pctl, pin) +
			pctl->devdata->pullen_offset, pctl);

	अगर (isup)
		reg_pullsel = SET_ADDR(mtk_get_port(pctl, pin) +
			pctl->devdata->pullsel_offset, pctl);
	अन्यथा
		reg_pullsel = CLR_ADDR(mtk_get_port(pctl, pin) +
			pctl->devdata->pullsel_offset, pctl);

	regmap_ग_लिखो(mtk_get_regmap(pctl, pin), reg_pullen, bit);
	regmap_ग_लिखो(mtk_get_regmap(pctl, pin), reg_pullsel, bit);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pconf_parse_conf(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक pin, क्रमागत pin_config_param param,
		क्रमागत pin_config_param arg)
अणु
	पूर्णांक ret = 0;
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		ret = mtk_pconf_set_pull_select(pctl, pin, false, false, arg);
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		ret = mtk_pconf_set_pull_select(pctl, pin, true, true, arg);
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ret = mtk_pconf_set_pull_select(pctl, pin, true, false, arg);
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		mtk_pmx_gpio_set_direction(pctldev, शून्य, pin, true);
		ret = mtk_pconf_set_ies_smt(pctl, pin, arg, param);
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		mtk_gpio_set(pctl->chip, pin, arg);
		ret = mtk_pmx_gpio_set_direction(pctldev, शून्य, pin, false);
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		mtk_pmx_gpio_set_direction(pctldev, शून्य, pin, true);
		ret = mtk_pconf_set_ies_smt(pctl, pin, arg, param);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		ret = mtk_pconf_set_driving(pctl, pin, arg);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_pconf_group_get(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित group,
				 अचिन्हित दीर्घ *config)
अणु
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*config = pctl->groups[group].config;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pconf_group_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित group,
				 अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mtk_pinctrl_group *g = &pctl->groups[group];
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		ret = mtk_pconf_parse_conf(pctldev, g->pin,
			pinconf_to_config_param(configs[i]),
			pinconf_to_config_argument(configs[i]));
		अगर (ret < 0)
			वापस ret;

		g->config = configs[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops mtk_pconf_ops = अणु
	.pin_config_group_get	= mtk_pconf_group_get,
	.pin_config_group_set	= mtk_pconf_group_set,
पूर्ण;

अटल काष्ठा mtk_pinctrl_group *
mtk_pctrl_find_group_by_pin(काष्ठा mtk_pinctrl *pctl, u32 pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->ngroups; i++) अणु
		काष्ठा mtk_pinctrl_group *grp = pctl->groups + i;

		अगर (grp->pin == pin)
			वापस grp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा mtk_desc_function *mtk_pctrl_find_function_by_pin(
		काष्ठा mtk_pinctrl *pctl, u32 pin_num, u32 fnum)
अणु
	स्थिर काष्ठा mtk_desc_pin *pin = pctl->devdata->pins + pin_num;
	स्थिर काष्ठा mtk_desc_function *func = pin->functions;

	जबतक (func && func->name) अणु
		अगर (func->muxval == fnum)
			वापस func;
		func++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool mtk_pctrl_is_function_valid(काष्ठा mtk_pinctrl *pctl,
		u32 pin_num, u32 fnum)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->devdata->npins; i++) अणु
		स्थिर काष्ठा mtk_desc_pin *pin = pctl->devdata->pins + i;

		अगर (pin->pin.number == pin_num) अणु
			स्थिर काष्ठा mtk_desc_function *func =
					pin->functions;

			जबतक (func && func->name) अणु
				अगर (func->muxval == fnum)
					वापस true;
				func++;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक mtk_pctrl_dt_node_to_map_func(काष्ठा mtk_pinctrl *pctl,
		u32 pin, u32 fnum, काष्ठा mtk_pinctrl_group *grp,
		काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps)
अणु
	bool ret;

	अगर (*num_maps == *reserved_maps)
		वापस -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)[*num_maps].data.mux.group = grp->name;

	ret = mtk_pctrl_is_function_valid(pctl, pin, fnum);
	अगर (!ret) अणु
		dev_err(pctl->dev, "invalid function %d on pin %d .\n",
				fnum, pin);
		वापस -EINVAL;
	पूर्ण

	(*map)[*num_maps].data.mux.function = mtk_gpio_functions[fnum];
	(*num_maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pctrl_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा device_node *node,
				      काष्ठा pinctrl_map **map,
				      अचिन्हित *reserved_maps,
				      अचिन्हित *num_maps)
अणु
	काष्ठा property *pins;
	u32 pinfunc, pin, func;
	पूर्णांक num_pins, num_funcs, maps_per_pin;
	अचिन्हित दीर्घ *configs;
	अचिन्हित पूर्णांक num_configs;
	bool has_config = false;
	पूर्णांक i, err;
	अचिन्हित reserve = 0;
	काष्ठा mtk_pinctrl_group *grp;
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	pins = of_find_property(node, "pinmux", शून्य);
	अगर (!pins) अणु
		dev_err(pctl->dev, "missing pins property in node %pOFn .\n",
				node);
		वापस -EINVAL;
	पूर्ण

	err = pinconf_generic_parse_dt_config(node, pctldev, &configs,
		&num_configs);
	अगर (err)
		वापस err;

	अगर (num_configs)
		has_config = true;

	num_pins = pins->length / माप(u32);
	num_funcs = num_pins;
	maps_per_pin = 0;
	अगर (num_funcs)
		maps_per_pin++;
	अगर (has_config && num_pins >= 1)
		maps_per_pin++;

	अगर (!num_pins || !maps_per_pin) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	reserve = num_pins * maps_per_pin;

	err = pinctrl_utils_reserve_map(pctldev, map,
			reserved_maps, num_maps, reserve);
	अगर (err < 0)
		जाओ निकास;

	क्रम (i = 0; i < num_pins; i++) अणु
		err = of_property_पढ़ो_u32_index(node, "pinmux",
				i, &pinfunc);
		अगर (err)
			जाओ निकास;

		pin = MTK_GET_PIN_NO(pinfunc);
		func = MTK_GET_PIN_FUNC(pinfunc);

		अगर (pin >= pctl->devdata->npins ||
				func >= ARRAY_SIZE(mtk_gpio_functions)) अणु
			dev_err(pctl->dev, "invalid pins value.\n");
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		grp = mtk_pctrl_find_group_by_pin(pctl, pin);
		अगर (!grp) अणु
			dev_err(pctl->dev, "unable to match pin %d to group\n",
					pin);
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		err = mtk_pctrl_dt_node_to_map_func(pctl, pin, func, grp, map,
				reserved_maps, num_maps);
		अगर (err < 0)
			जाओ निकास;

		अगर (has_config) अणु
			err = pinctrl_utils_add_map_configs(pctldev, map,
					reserved_maps, num_maps, grp->name,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GROUP);
			अगर (err < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

	err = 0;

निकास:
	kमुक्त(configs);
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा device_node *np_config,
				 काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा device_node *np;
	अचिन्हित reserved_maps;
	पूर्णांक ret;

	*map = शून्य;
	*num_maps = 0;
	reserved_maps = 0;

	क्रम_each_child_of_node(np_config, np) अणु
		ret = mtk_pctrl_dt_subnode_to_map(pctldev, np, map,
				&reserved_maps, num_maps);
		अगर (ret < 0) अणु
			pinctrl_utils_मुक्त_map(pctldev, *map, *num_maps);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->ngroups;
पूर्ण

अटल स्थिर अक्षर *mtk_pctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित group)
अणु
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->groups[group].name;
पूर्ण

अटल पूर्णांक mtk_pctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित group,
				      स्थिर अचिन्हित **pins,
				      अचिन्हित *num_pins)
अणु
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*pins = (अचिन्हित *)&pctl->groups[group].pin;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops mtk_pctrl_ops = अणु
	.dt_node_to_map		= mtk_pctrl_dt_node_to_map,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
	.get_groups_count	= mtk_pctrl_get_groups_count,
	.get_group_name		= mtk_pctrl_get_group_name,
	.get_group_pins		= mtk_pctrl_get_group_pins,
पूर्ण;

अटल पूर्णांक mtk_pmx_get_funcs_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(mtk_gpio_functions);
पूर्ण

अटल स्थिर अक्षर *mtk_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित selector)
अणु
	वापस mtk_gpio_functions[selector];
पूर्ण

अटल पूर्णांक mtk_pmx_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित function,
				     स्थिर अक्षर * स्थिर **groups,
				     अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctl->grp_names;
	*num_groups = pctl->ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pmx_set_mode(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित दीर्घ pin, अचिन्हित दीर्घ mode)
अणु
	अचिन्हित पूर्णांक reg_addr;
	अचिन्हित अक्षर bit;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक mask = (1L << GPIO_MODE_BITS) - 1;
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	अगर (pctl->devdata->spec_pinmux_set)
		pctl->devdata->spec_pinmux_set(mtk_get_regmap(pctl, pin),
					pin, mode);

	reg_addr = ((pin / MAX_GPIO_MODE_PER_REG) << pctl->devdata->port_shf)
			+ pctl->devdata->pinmux_offset;

	mode &= mask;
	bit = pin % MAX_GPIO_MODE_PER_REG;
	mask <<= (GPIO_MODE_BITS * bit);
	val = (mode << (GPIO_MODE_BITS * bit));
	वापस regmap_update_bits(mtk_get_regmap(pctl, pin),
			reg_addr, mask, val);
पूर्ण

अटल स्थिर काष्ठा mtk_desc_pin *
mtk_find_pin_by_eपूर्णांक_num(काष्ठा mtk_pinctrl *pctl, अचिन्हित पूर्णांक eपूर्णांक_num)
अणु
	पूर्णांक i;
	स्थिर काष्ठा mtk_desc_pin *pin;

	क्रम (i = 0; i < pctl->devdata->npins; i++) अणु
		pin = pctl->devdata->pins + i;
		अगर (pin->eपूर्णांक.eपूर्णांकnum == eपूर्णांक_num)
			वापस pin;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mtk_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
			    अचिन्हित function,
			    अचिन्हित group)
अणु
	bool ret;
	स्थिर काष्ठा mtk_desc_function *desc;
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mtk_pinctrl_group *g = pctl->groups + group;

	ret = mtk_pctrl_is_function_valid(pctl, g->pin, function);
	अगर (!ret) अणु
		dev_err(pctl->dev, "invalid function %d on group %d .\n",
				function, group);
		वापस -EINVAL;
	पूर्ण

	desc = mtk_pctrl_find_function_by_pin(pctl, g->pin, function);
	अगर (!desc)
		वापस -EINVAL;
	mtk_pmx_set_mode(pctldev, g->pin, desc->muxval);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pmx_find_gpio_mode(काष्ठा mtk_pinctrl *pctl,
				अचिन्हित offset)
अणु
	स्थिर काष्ठा mtk_desc_pin *pin = pctl->devdata->pins + offset;
	स्थिर काष्ठा mtk_desc_function *func = pin->functions;

	जबतक (func && func->name) अणु
		अगर (!म_भेदन(func->name, GPIO_MODE_PREFIX,
			माप(GPIO_MODE_PREFIX)-1))
			वापस func->muxval;
		func++;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mtk_pmx_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_gpio_range *range,
				    अचिन्हित offset)
अणु
	पूर्णांक muxval;
	काष्ठा mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	muxval = mtk_pmx_find_gpio_mode(pctl, offset);

	अगर (muxval < 0) अणु
		dev_err(pctl->dev, "invalid gpio pin %d.\n", offset);
		वापस -EINVAL;
	पूर्ण

	mtk_pmx_set_mode(pctldev, offset, muxval);
	mtk_pconf_set_ies_smt(pctl, offset, 1, PIN_CONFIG_INPUT_ENABLE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops mtk_pmx_ops = अणु
	.get_functions_count	= mtk_pmx_get_funcs_cnt,
	.get_function_name	= mtk_pmx_get_func_name,
	.get_function_groups	= mtk_pmx_get_func_groups,
	.set_mux		= mtk_pmx_set_mux,
	.gpio_set_direction	= mtk_pmx_gpio_set_direction,
	.gpio_request_enable	= mtk_pmx_gpio_request_enable,
पूर्ण;

अटल पूर्णांक mtk_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक mtk_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	mtk_gpio_set(chip, offset, value);
	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल पूर्णांक mtk_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अचिन्हित पूर्णांक reg_addr;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक पढ़ो_val = 0;

	काष्ठा mtk_pinctrl *pctl = gpiochip_get_data(chip);

	reg_addr =  mtk_get_port(pctl, offset) + pctl->devdata->dir_offset;
	bit = BIT(offset & 0xf);

	अगर (pctl->devdata->spec_dir_set)
		pctl->devdata->spec_dir_set(&reg_addr, offset);

	regmap_पढ़ो(pctl->regmap1, reg_addr, &पढ़ो_val);
	अगर (पढ़ो_val & bit)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक mtk_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अचिन्हित पूर्णांक reg_addr;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक पढ़ो_val = 0;
	काष्ठा mtk_pinctrl *pctl = gpiochip_get_data(chip);

	reg_addr = mtk_get_port(pctl, offset) +
		pctl->devdata->din_offset;

	bit = BIT(offset & 0xf);
	regmap_पढ़ो(pctl->regmap1, reg_addr, &पढ़ो_val);
	वापस !!(पढ़ो_val & bit);
पूर्ण

अटल पूर्णांक mtk_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा mtk_pinctrl *pctl = gpiochip_get_data(chip);
	स्थिर काष्ठा mtk_desc_pin *pin;
	अचिन्हित दीर्घ eपूर्णांक_n;

	pin = pctl->devdata->pins + offset;
	अगर (pin->eपूर्णांक.eपूर्णांकnum == NO_EINT_SUPPORT)
		वापस -EINVAL;

	eपूर्णांक_n = pin->eपूर्णांक.eपूर्णांकnum;

	वापस mtk_eपूर्णांक_find_irq(pctl->eपूर्णांक, eपूर्णांक_n);
पूर्ण

अटल पूर्णांक mtk_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित offset,
			       अचिन्हित दीर्घ config)
अणु
	काष्ठा mtk_pinctrl *pctl = gpiochip_get_data(chip);
	स्थिर काष्ठा mtk_desc_pin *pin;
	अचिन्हित दीर्घ eपूर्णांक_n;
	u32 debounce;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	pin = pctl->devdata->pins + offset;
	अगर (pin->eपूर्णांक.eपूर्णांकnum == NO_EINT_SUPPORT)
		वापस -EINVAL;

	debounce = pinconf_to_config_argument(config);
	eपूर्णांक_n = pin->eपूर्णांक.eपूर्णांकnum;

	वापस mtk_eपूर्णांक_set_debounce(pctl->eपूर्णांक, eपूर्णांक_n, debounce);
पूर्ण

अटल स्थिर काष्ठा gpio_chip mtk_gpio_chip = अणु
	.owner			= THIS_MODULE,
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.get_direction		= mtk_gpio_get_direction,
	.direction_input	= mtk_gpio_direction_input,
	.direction_output	= mtk_gpio_direction_output,
	.get			= mtk_gpio_get,
	.set			= mtk_gpio_set,
	.to_irq			= mtk_gpio_to_irq,
	.set_config		= mtk_gpio_set_config,
	.of_gpio_n_cells	= 2,
पूर्ण;

अटल पूर्णांक mtk_eपूर्णांक_suspend(काष्ठा device *device)
अणु
	काष्ठा mtk_pinctrl *pctl = dev_get_drvdata(device);

	वापस mtk_eपूर्णांक_करो_suspend(pctl->eपूर्णांक);
पूर्ण

अटल पूर्णांक mtk_eपूर्णांक_resume(काष्ठा device *device)
अणु
	काष्ठा mtk_pinctrl *pctl = dev_get_drvdata(device);

	वापस mtk_eपूर्णांक_करो_resume(pctl->eपूर्णांक);
पूर्ण

स्थिर काष्ठा dev_pm_ops mtk_eपूर्णांक_pm_ops = अणु
	.suspend_noirq = mtk_eपूर्णांक_suspend,
	.resume_noirq = mtk_eपूर्णांक_resume,
पूर्ण;

अटल पूर्णांक mtk_pctrl_build_state(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_pinctrl *pctl = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	pctl->ngroups = pctl->devdata->npins;

	/* Allocate groups */
	pctl->groups = devm_kसुस्मृति(&pdev->dev, pctl->ngroups,
				    माप(*pctl->groups), GFP_KERNEL);
	अगर (!pctl->groups)
		वापस -ENOMEM;

	/* We assume that one pin is one group, use pin name as group name. */
	pctl->grp_names = devm_kसुस्मृति(&pdev->dev, pctl->ngroups,
				       माप(*pctl->grp_names), GFP_KERNEL);
	अगर (!pctl->grp_names)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctl->devdata->npins; i++) अणु
		स्थिर काष्ठा mtk_desc_pin *pin = pctl->devdata->pins + i;
		काष्ठा mtk_pinctrl_group *group = pctl->groups + i;

		group->name = pin->pin.name;
		group->pin = pin->pin.number;

		pctl->grp_names[i] = pin->pin.name;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mtk_xt_get_gpio_n(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n, अचिन्हित पूर्णांक *gpio_n,
		  काष्ठा gpio_chip **gpio_chip)
अणु
	काष्ठा mtk_pinctrl *pctl = (काष्ठा mtk_pinctrl *)data;
	स्थिर काष्ठा mtk_desc_pin *pin;

	pin = mtk_find_pin_by_eपूर्णांक_num(pctl, eपूर्णांक_n);
	अगर (!pin)
		वापस -EINVAL;

	*gpio_chip = pctl->chip;
	*gpio_n = pin->pin.number;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_xt_get_gpio_state(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n)
अणु
	काष्ठा mtk_pinctrl *pctl = (काष्ठा mtk_pinctrl *)data;
	स्थिर काष्ठा mtk_desc_pin *pin;

	pin = mtk_find_pin_by_eपूर्णांक_num(pctl, eपूर्णांक_n);
	अगर (!pin)
		वापस -EINVAL;

	वापस mtk_gpio_get(pctl->chip, pin->pin.number);
पूर्ण

अटल पूर्णांक mtk_xt_set_gpio_as_eपूर्णांक(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n)
अणु
	काष्ठा mtk_pinctrl *pctl = (काष्ठा mtk_pinctrl *)data;
	स्थिर काष्ठा mtk_desc_pin *pin;

	pin = mtk_find_pin_by_eपूर्णांक_num(pctl, eपूर्णांक_n);
	अगर (!pin)
		वापस -EINVAL;

	/* set mux to INT mode */
	mtk_pmx_set_mode(pctl->pctl_dev, pin->pin.number, pin->eपूर्णांक.eपूर्णांकmux);
	/* set gpio direction to input */
	mtk_pmx_gpio_set_direction(pctl->pctl_dev, शून्य, pin->pin.number,
				   true);
	/* set input-enable */
	mtk_pconf_set_ies_smt(pctl, pin->pin.number, 1,
			      PIN_CONFIG_INPUT_ENABLE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_eपूर्णांक_xt mtk_eपूर्णांक_xt = अणु
	.get_gpio_n = mtk_xt_get_gpio_n,
	.get_gpio_state = mtk_xt_get_gpio_state,
	.set_gpio_as_eपूर्णांक = mtk_xt_set_gpio_as_eपूर्णांक,
पूर्ण;

अटल पूर्णांक mtk_eपूर्णांक_init(काष्ठा mtk_pinctrl *pctl, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;

	अगर (!of_property_पढ़ो_bool(np, "interrupt-controller"))
		वापस -ENODEV;

	pctl->eपूर्णांक = devm_kzalloc(pctl->dev, माप(*pctl->eपूर्णांक), GFP_KERNEL);
	अगर (!pctl->eपूर्णांक)
		वापस -ENOMEM;

	pctl->eपूर्णांक->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pctl->eपूर्णांक->base))
		वापस PTR_ERR(pctl->eपूर्णांक->base);

	pctl->eपूर्णांक->irq = irq_of_parse_and_map(np, 0);
	अगर (!pctl->eपूर्णांक->irq)
		वापस -EINVAL;

	pctl->eपूर्णांक->dev = &pdev->dev;
	/*
	 * If pctl->eपूर्णांक->regs == शून्य, it would fall back पूर्णांकo using a generic
	 * रेजिस्टर map in mtk_eपूर्णांक_करो_init calls.
	 */
	pctl->eपूर्णांक->regs = pctl->devdata->eपूर्णांक_regs;
	pctl->eपूर्णांक->hw = &pctl->devdata->eपूर्णांक_hw;
	pctl->eपूर्णांक->pctl = pctl;
	pctl->eपूर्णांक->gpio_xlate = &mtk_eपूर्णांक_xt;

	वापस mtk_eपूर्णांक_करो_init(pctl->eपूर्णांक);
पूर्ण

पूर्णांक mtk_pctrl_init(काष्ठा platक्रमm_device *pdev,
		स्थिर काष्ठा mtk_pinctrl_devdata *data,
		काष्ठा regmap *regmap)
अणु
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा mtk_pinctrl *pctl;
	काष्ठा device_node *np = pdev->dev.of_node, *node;
	काष्ठा property *prop;
	पूर्णांक ret, i;

	pctl = devm_kzalloc(&pdev->dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pctl);

	prop = of_find_property(np, "pins-are-numbered", शून्य);
	अगर (!prop) अणु
		dev_err(&pdev->dev, "only support pins-are-numbered format\n");
		वापस -EINVAL;
	पूर्ण

	node = of_parse_phandle(np, "mediatek,pctl-regmap", 0);
	अगर (node) अणु
		pctl->regmap1 = syscon_node_to_regmap(node);
		अगर (IS_ERR(pctl->regmap1))
			वापस PTR_ERR(pctl->regmap1);
	पूर्ण अन्यथा अगर (regmap) अणु
		pctl->regmap1  = regmap;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Pinctrl node has not register regmap.\n");
		वापस -EINVAL;
	पूर्ण

	/* Only 8135 has two base addr, other SoCs have only one. */
	node = of_parse_phandle(np, "mediatek,pctl-regmap", 1);
	अगर (node) अणु
		pctl->regmap2 = syscon_node_to_regmap(node);
		अगर (IS_ERR(pctl->regmap2))
			वापस PTR_ERR(pctl->regmap2);
	पूर्ण

	pctl->devdata = data;
	ret = mtk_pctrl_build_state(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "build state failed: %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	pins = devm_kसुस्मृति(&pdev->dev, pctl->devdata->npins, माप(*pins),
			    GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctl->devdata->npins; i++)
		pins[i] = pctl->devdata->pins[i].pin;

	pctl->pctl_desc.name = dev_name(&pdev->dev);
	pctl->pctl_desc.owner = THIS_MODULE;
	pctl->pctl_desc.pins = pins;
	pctl->pctl_desc.npins = pctl->devdata->npins;
	pctl->pctl_desc.confops = &mtk_pconf_ops;
	pctl->pctl_desc.pctlops = &mtk_pctrl_ops;
	pctl->pctl_desc.pmxops = &mtk_pmx_ops;
	pctl->dev = &pdev->dev;

	pctl->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, &pctl->pctl_desc,
					       pctl);
	अगर (IS_ERR(pctl->pctl_dev)) अणु
		dev_err(&pdev->dev, "couldn't register pinctrl driver\n");
		वापस PTR_ERR(pctl->pctl_dev);
	पूर्ण

	pctl->chip = devm_kzalloc(&pdev->dev, माप(*pctl->chip), GFP_KERNEL);
	अगर (!pctl->chip)
		वापस -ENOMEM;

	*pctl->chip = mtk_gpio_chip;
	pctl->chip->ngpio = pctl->devdata->npins;
	pctl->chip->label = dev_name(&pdev->dev);
	pctl->chip->parent = &pdev->dev;
	pctl->chip->base = -1;

	ret = gpiochip_add_data(pctl->chip, pctl);
	अगर (ret)
		वापस -EINVAL;

	/* Register the GPIO to pin mappings. */
	ret = gpiochip_add_pin_range(pctl->chip, dev_name(&pdev->dev),
			0, 0, pctl->devdata->npins);
	अगर (ret) अणु
		ret = -EINVAL;
		जाओ chip_error;
	पूर्ण

	ret = mtk_eपूर्णांक_init(pctl, pdev);
	अगर (ret)
		जाओ chip_error;

	वापस 0;

chip_error:
	gpiochip_हटाओ(pctl->chip);
	वापस ret;
पूर्ण
