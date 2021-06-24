<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ROHM Semiconductors

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>

अटल पूर्णांक set_dvs_level(स्थिर काष्ठा regulator_desc *desc,
			 काष्ठा device_node *np, काष्ठा regmap *regmap,
			 अक्षर *prop, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
			 अचिन्हित पूर्णांक omask, अचिन्हित पूर्णांक oreg)
अणु
	पूर्णांक ret, i;
	uपूर्णांक32_t uv;

	ret = of_property_पढ़ो_u32(np, prop, &uv);
	अगर (ret) अणु
		अगर (ret != -EINVAL)
			वापस ret;
		वापस 0;
	पूर्ण
	/* If voltage is set to 0 => disable */
	अगर (uv == 0) अणु
		अगर (omask)
			वापस regmap_update_bits(regmap, oreg, omask, 0);
	पूर्ण
	/* Some setups करोn't allow setting own voltage but करो allow enabling */
	अगर (!mask) अणु
		अगर (omask)
			वापस regmap_update_bits(regmap, oreg, omask, omask);

		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < desc->n_voltages; i++) अणु
		/* NOTE to next hacker - Does not support pickable ranges */
		अगर (desc->linear_range_selectors)
			वापस -EINVAL;
		अगर (desc->n_linear_ranges)
			ret = regulator_desc_list_voltage_linear_range(desc, i);
		अन्यथा
			ret = regulator_desc_list_voltage_linear(desc, i);
		अगर (ret < 0)
			जारी;
		अगर (ret == uv) अणु
			i <<= ffs(desc->vsel_mask) - 1;
			ret = regmap_update_bits(regmap, reg, mask, i);
			अगर (omask && !ret)
				ret = regmap_update_bits(regmap, oreg, omask,
							 omask);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक rohm_regulator_set_dvs_levels(स्थिर काष्ठा rohm_dvs_config *dvs,
			  काष्ठा device_node *np,
			  स्थिर काष्ठा regulator_desc *desc,
			  काष्ठा regmap *regmap)
अणु
	पूर्णांक i, ret = 0;
	अक्षर *prop;
	अचिन्हित पूर्णांक reg, mask, omask, oreg = desc->enable_reg;

	क्रम (i = 0; i < ROHM_DVS_LEVEL_VALID_AMOUNT && !ret; i++) अणु
		पूर्णांक bit;

		bit = BIT(i);
		अगर (dvs->level_map & bit) अणु
			चयन (bit) अणु
			हाल ROHM_DVS_LEVEL_RUN:
				prop = "rohm,dvs-run-voltage";
				reg = dvs->run_reg;
				mask = dvs->run_mask;
				omask = dvs->run_on_mask;
				अवरोध;
			हाल ROHM_DVS_LEVEL_IDLE:
				prop = "rohm,dvs-idle-voltage";
				reg = dvs->idle_reg;
				mask = dvs->idle_mask;
				omask = dvs->idle_on_mask;
				अवरोध;
			हाल ROHM_DVS_LEVEL_SUSPEND:
				prop = "rohm,dvs-suspend-voltage";
				reg = dvs->suspend_reg;
				mask = dvs->suspend_mask;
				omask = dvs->suspend_on_mask;
				अवरोध;
			हाल ROHM_DVS_LEVEL_LPSR:
				prop = "rohm,dvs-lpsr-voltage";
				reg = dvs->lpsr_reg;
				mask = dvs->lpsr_mask;
				omask = dvs->lpsr_on_mask;
				अवरोध;
			हाल ROHM_DVS_LEVEL_SNVS:
				prop = "rohm,dvs-snvs-voltage";
				reg = dvs->snvs_reg;
				mask = dvs->snvs_mask;
				omask = dvs->snvs_on_mask;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			ret = set_dvs_level(desc, np, regmap, prop, reg, mask,
					    omask, oreg);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rohm_regulator_set_dvs_levels);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("Generic helpers for ROHM PMIC regulator drivers");
