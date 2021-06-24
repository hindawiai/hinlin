<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// helpers.c  --  Voltage/Current Regulator framework helper functions.
//
// Copyright 2007, 2008 Wolfson Microelectronics PLC.
// Copyright 2008 SlimLogic Ltd.

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/module.h>

#समावेश "internal.h"

/**
 * regulator_is_enabled_regmap - standard is_enabled() क्रम regmap users
 *
 * @rdev: regulator to operate on
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O can set the
 * enable_reg and enable_mask fields in their descriptor and then use
 * this as their is_enabled operation, saving some code.
 */
पूर्णांक regulator_is_enabled_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg, &val);
	अगर (ret != 0)
		वापस ret;

	val &= rdev->desc->enable_mask;

	अगर (rdev->desc->enable_is_inverted) अणु
		अगर (rdev->desc->enable_val)
			वापस val != rdev->desc->enable_val;
		वापस val == 0;
	पूर्ण अन्यथा अणु
		अगर (rdev->desc->enable_val)
			वापस val == rdev->desc->enable_val;
		वापस val != 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(regulator_is_enabled_regmap);

/**
 * regulator_enable_regmap - standard enable() क्रम regmap users
 *
 * @rdev: regulator to operate on
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O can set the
 * enable_reg and enable_mask fields in their descriptor and then use
 * this as their enable() operation, saving some code.
 */
पूर्णांक regulator_enable_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;

	अगर (rdev->desc->enable_is_inverted) अणु
		val = rdev->desc->disable_val;
	पूर्ण अन्यथा अणु
		val = rdev->desc->enable_val;
		अगर (!val)
			val = rdev->desc->enable_mask;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_enable_regmap);

/**
 * regulator_disable_regmap - standard disable() क्रम regmap users
 *
 * @rdev: regulator to operate on
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O can set the
 * enable_reg and enable_mask fields in their descriptor and then use
 * this as their disable() operation, saving some code.
 */
पूर्णांक regulator_disable_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;

	अगर (rdev->desc->enable_is_inverted) अणु
		val = rdev->desc->enable_val;
		अगर (!val)
			val = rdev->desc->enable_mask;
	पूर्ण अन्यथा अणु
		val = rdev->desc->disable_val;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_disable_regmap);

अटल पूर्णांक regulator_range_selector_to_index(काष्ठा regulator_dev *rdev,
					     अचिन्हित पूर्णांक rval)
अणु
	पूर्णांक i;

	अगर (!rdev->desc->linear_range_selectors)
		वापस -EINVAL;

	rval &= rdev->desc->vsel_range_mask;

	क्रम (i = 0; i < rdev->desc->n_linear_ranges; i++) अणु
		अगर (rdev->desc->linear_range_selectors[i] == rval)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * regulator_get_voltage_sel_pickable_regmap - pickable range get_voltage_sel
 *
 * @rdev: regulator to operate on
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O and use pickable
 * ranges can set the vsel_reg, vsel_mask, vsel_range_reg and vsel_range_mask
 * fields in their descriptor and then use this as their get_voltage_vsel
 * operation, saving some code.
 */
पूर्णांक regulator_get_voltage_sel_pickable_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक r_val;
	पूर्णांक range;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक voltages = 0;
	स्थिर काष्ठा linear_range *r = rdev->desc->linear_ranges;

	अगर (!r)
		वापस -EINVAL;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->vsel_reg, &val);
	अगर (ret != 0)
		वापस ret;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->vsel_range_reg, &r_val);
	अगर (ret != 0)
		वापस ret;

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	range = regulator_range_selector_to_index(rdev, r_val);
	अगर (range < 0)
		वापस -EINVAL;

	voltages = linear_range_values_in_range_array(r, range);

	वापस val + voltages;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_voltage_sel_pickable_regmap);

/**
 * regulator_set_voltage_sel_pickable_regmap - pickable range set_voltage_sel
 *
 * @rdev: regulator to operate on
 * @sel: Selector to set
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O and use pickable
 * ranges can set the vsel_reg, vsel_mask, vsel_range_reg and vsel_range_mask
 * fields in their descriptor and then use this as their set_voltage_vsel
 * operation, saving some code.
 */
पूर्णांक regulator_set_voltage_sel_pickable_regmap(काष्ठा regulator_dev *rdev,
					      अचिन्हित पूर्णांक sel)
अणु
	अचिन्हित पूर्णांक range;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक voltages_in_range = 0;

	क्रम (i = 0; i < rdev->desc->n_linear_ranges; i++) अणु
		स्थिर काष्ठा linear_range *r;

		r = &rdev->desc->linear_ranges[i];
		voltages_in_range = linear_range_values_in_range(r);

		अगर (sel < voltages_in_range)
			अवरोध;
		sel -= voltages_in_range;
	पूर्ण

	अगर (i == rdev->desc->n_linear_ranges)
		वापस -EINVAL;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;
	sel += rdev->desc->linear_ranges[i].min_sel;

	range = rdev->desc->linear_range_selectors[i];

	अगर (rdev->desc->vsel_reg == rdev->desc->vsel_range_reg) अणु
		ret = regmap_update_bits(rdev->regmap,
					 rdev->desc->vsel_reg,
					 rdev->desc->vsel_range_mask |
					 rdev->desc->vsel_mask, sel | range);
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(rdev->regmap,
					 rdev->desc->vsel_range_reg,
					 rdev->desc->vsel_range_mask, range);
		अगर (ret)
			वापस ret;

		ret = regmap_update_bits(rdev->regmap, rdev->desc->vsel_reg,
				  rdev->desc->vsel_mask, sel);
	पूर्ण

	अगर (ret)
		वापस ret;

	अगर (rdev->desc->apply_bit)
		ret = regmap_update_bits(rdev->regmap, rdev->desc->apply_reg,
					 rdev->desc->apply_bit,
					 rdev->desc->apply_bit);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_voltage_sel_pickable_regmap);

/**
 * regulator_get_voltage_sel_regmap - standard get_voltage_sel क्रम regmap users
 *
 * @rdev: regulator to operate on
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O can set the
 * vsel_reg and vsel_mask fields in their descriptor and then use this
 * as their get_voltage_vsel operation, saving some code.
 */
पूर्णांक regulator_get_voltage_sel_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->vsel_reg, &val);
	अगर (ret != 0)
		वापस ret;

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_voltage_sel_regmap);

/**
 * regulator_set_voltage_sel_regmap - standard set_voltage_sel क्रम regmap users
 *
 * @rdev: regulator to operate on
 * @sel: Selector to set
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O can set the
 * vsel_reg and vsel_mask fields in their descriptor and then use this
 * as their set_voltage_vsel operation, saving some code.
 */
पूर्णांक regulator_set_voltage_sel_regmap(काष्ठा regulator_dev *rdev, अचिन्हित sel)
अणु
	पूर्णांक ret;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;

	ret = regmap_update_bits(rdev->regmap, rdev->desc->vsel_reg,
				  rdev->desc->vsel_mask, sel);
	अगर (ret)
		वापस ret;

	अगर (rdev->desc->apply_bit)
		ret = regmap_update_bits(rdev->regmap, rdev->desc->apply_reg,
					 rdev->desc->apply_bit,
					 rdev->desc->apply_bit);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_voltage_sel_regmap);

/**
 * regulator_map_voltage_iterate - map_voltage() based on list_voltage()
 *
 * @rdev: Regulator to operate on
 * @min_uV: Lower bound क्रम voltage
 * @max_uV: Upper bound क्रम voltage
 *
 * Drivers implementing set_voltage_sel() and list_voltage() can use
 * this as their map_voltage() operation.  It will find a suitable
 * voltage by calling list_voltage() until it माला_लो something in bounds
 * क्रम the requested voltages.
 */
पूर्णांक regulator_map_voltage_iterate(काष्ठा regulator_dev *rdev,
				  पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	पूर्णांक best_val = पूर्णांक_उच्च;
	पूर्णांक selector = 0;
	पूर्णांक i, ret;

	/* Find the smallest voltage that falls within the specअगरied
	 * range.
	 */
	क्रम (i = 0; i < rdev->desc->n_voltages; i++) अणु
		ret = rdev->desc->ops->list_voltage(rdev, i);
		अगर (ret < 0)
			जारी;

		अगर (ret < best_val && ret >= min_uV && ret <= max_uV) अणु
			best_val = ret;
			selector = i;
		पूर्ण
	पूर्ण

	अगर (best_val != पूर्णांक_उच्च)
		वापस selector;
	अन्यथा
		वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_map_voltage_iterate);

/**
 * regulator_map_voltage_ascend - map_voltage() क्रम ascendant voltage list
 *
 * @rdev: Regulator to operate on
 * @min_uV: Lower bound क्रम voltage
 * @max_uV: Upper bound क्रम voltage
 *
 * Drivers that have ascendant voltage list can use this as their
 * map_voltage() operation.
 */
पूर्णांक regulator_map_voltage_ascend(काष्ठा regulator_dev *rdev,
				 पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < rdev->desc->n_voltages; i++) अणु
		ret = rdev->desc->ops->list_voltage(rdev, i);
		अगर (ret < 0)
			जारी;

		अगर (ret > max_uV)
			अवरोध;

		अगर (ret >= min_uV && ret <= max_uV)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_map_voltage_ascend);

/**
 * regulator_map_voltage_linear - map_voltage() क्रम simple linear mappings
 *
 * @rdev: Regulator to operate on
 * @min_uV: Lower bound क्रम voltage
 * @max_uV: Upper bound क्रम voltage
 *
 * Drivers providing min_uV and uV_step in their regulator_desc can
 * use this as their map_voltage() operation.
 */
पूर्णांक regulator_map_voltage_linear(काष्ठा regulator_dev *rdev,
				 पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	पूर्णांक ret, voltage;

	/* Allow uV_step to be 0 क्रम fixed voltage */
	अगर (rdev->desc->n_voltages == 1 && rdev->desc->uV_step == 0) अणु
		अगर (min_uV <= rdev->desc->min_uV && rdev->desc->min_uV <= max_uV)
			वापस 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (!rdev->desc->uV_step) अणु
		BUG_ON(!rdev->desc->uV_step);
		वापस -EINVAL;
	पूर्ण

	अगर (min_uV < rdev->desc->min_uV)
		min_uV = rdev->desc->min_uV;

	ret = DIV_ROUND_UP(min_uV - rdev->desc->min_uV, rdev->desc->uV_step);
	अगर (ret < 0)
		वापस ret;

	ret += rdev->desc->linear_min_sel;

	/* Map back पूर्णांकo a voltage to verअगरy we're still in bounds */
	voltage = rdev->desc->ops->list_voltage(rdev, ret);
	अगर (voltage < min_uV || voltage > max_uV)
		वापस -EINVAL;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_map_voltage_linear);

/**
 * regulator_map_voltage_linear_range - map_voltage() क्रम multiple linear ranges
 *
 * @rdev: Regulator to operate on
 * @min_uV: Lower bound क्रम voltage
 * @max_uV: Upper bound क्रम voltage
 *
 * Drivers providing linear_ranges in their descriptor can use this as
 * their map_voltage() callback.
 */
पूर्णांक regulator_map_voltage_linear_range(काष्ठा regulator_dev *rdev,
				       पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	स्थिर काष्ठा linear_range *range;
	पूर्णांक ret = -EINVAL;
	अचिन्हित पूर्णांक sel;
	bool found;
	पूर्णांक voltage, i;

	अगर (!rdev->desc->n_linear_ranges) अणु
		BUG_ON(!rdev->desc->n_linear_ranges);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < rdev->desc->n_linear_ranges; i++) अणु
		range = &rdev->desc->linear_ranges[i];

		ret = linear_range_get_selector_high(range, min_uV, &sel,
						     &found);
		अगर (ret)
			जारी;
		ret = sel;

		/*
		 * Map back पूर्णांकo a voltage to verअगरy we're still in bounds.
		 * If we are not, then जारी checking rest of the ranges.
		 */
		voltage = rdev->desc->ops->list_voltage(rdev, sel);
		अगर (voltage >= min_uV && voltage <= max_uV)
			अवरोध;
	पूर्ण

	अगर (i == rdev->desc->n_linear_ranges)
		वापस -EINVAL;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_map_voltage_linear_range);

/**
 * regulator_map_voltage_pickable_linear_range - map_voltage, pickable ranges
 *
 * @rdev: Regulator to operate on
 * @min_uV: Lower bound क्रम voltage
 * @max_uV: Upper bound क्रम voltage
 *
 * Drivers providing pickable linear_ranges in their descriptor can use
 * this as their map_voltage() callback.
 */
पूर्णांक regulator_map_voltage_pickable_linear_range(काष्ठा regulator_dev *rdev,
						पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	स्थिर काष्ठा linear_range *range;
	पूर्णांक ret = -EINVAL;
	पूर्णांक voltage, i;
	अचिन्हित पूर्णांक selector = 0;

	अगर (!rdev->desc->n_linear_ranges) अणु
		BUG_ON(!rdev->desc->n_linear_ranges);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < rdev->desc->n_linear_ranges; i++) अणु
		पूर्णांक linear_max_uV;
		bool found;
		अचिन्हित पूर्णांक sel;

		range = &rdev->desc->linear_ranges[i];
		linear_max_uV = linear_range_get_max_value(range);

		अगर (!(min_uV <= linear_max_uV && max_uV >= range->min)) अणु
			selector += linear_range_values_in_range(range);
			जारी;
		पूर्ण

		ret = linear_range_get_selector_high(range, min_uV, &sel,
						     &found);
		अगर (ret) अणु
			selector += linear_range_values_in_range(range);
			जारी;
		पूर्ण

		ret = selector + sel - range->min_sel;

		voltage = rdev->desc->ops->list_voltage(rdev, ret);

		/*
		 * Map back पूर्णांकo a voltage to verअगरy we're still in bounds.
		 * We may have overlapping voltage ranges. Hence we करोn't
		 * निकास but retry until we have checked all ranges.
		 */
		अगर (voltage < min_uV || voltage > max_uV)
			selector += linear_range_values_in_range(range);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (i == rdev->desc->n_linear_ranges)
		वापस -EINVAL;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_map_voltage_pickable_linear_range);

/**
 * regulator_desc_list_voltage_linear - List voltages with simple calculation
 *
 * @desc: Regulator desc क्रम regulator which volatges are to be listed
 * @selector: Selector to convert पूर्णांकo a voltage
 *
 * Regulators with a simple linear mapping between voltages and
 * selectors can set min_uV and uV_step in the regulator descriptor
 * and then use this function prior regulator registration to list
 * the voltages. This is useful when voltages need to be listed during
 * device-tree parsing.
 */
पूर्णांक regulator_desc_list_voltage_linear(स्थिर काष्ठा regulator_desc *desc,
				       अचिन्हित पूर्णांक selector)
अणु
	अगर (selector >= desc->n_voltages)
		वापस -EINVAL;

	अगर (selector < desc->linear_min_sel)
		वापस 0;

	selector -= desc->linear_min_sel;

	वापस desc->min_uV + (desc->uV_step * selector);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_desc_list_voltage_linear);

/**
 * regulator_list_voltage_linear - List voltages with simple calculation
 *
 * @rdev: Regulator device
 * @selector: Selector to convert पूर्णांकo a voltage
 *
 * Regulators with a simple linear mapping between voltages and
 * selectors can set min_uV and uV_step in the regulator descriptor
 * and then use this function as their list_voltage() operation,
 */
पूर्णांक regulator_list_voltage_linear(काष्ठा regulator_dev *rdev,
				  अचिन्हित पूर्णांक selector)
अणु
	वापस regulator_desc_list_voltage_linear(rdev->desc, selector);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_list_voltage_linear);

/**
 * regulator_list_voltage_pickable_linear_range - pickable range list voltages
 *
 * @rdev: Regulator device
 * @selector: Selector to convert पूर्णांकo a voltage
 *
 * list_voltage() operation, पूर्णांकended to be used by drivers utilizing pickable
 * ranges helpers.
 */
पूर्णांक regulator_list_voltage_pickable_linear_range(काष्ठा regulator_dev *rdev,
						 अचिन्हित पूर्णांक selector)
अणु
	स्थिर काष्ठा linear_range *range;
	पूर्णांक i;
	अचिन्हित पूर्णांक all_sels = 0;

	अगर (!rdev->desc->n_linear_ranges) अणु
		BUG_ON(!rdev->desc->n_linear_ranges);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < rdev->desc->n_linear_ranges; i++) अणु
		अचिन्हित पूर्णांक sel_indexes;

		range = &rdev->desc->linear_ranges[i];

		sel_indexes = linear_range_values_in_range(range) - 1;

		अगर (all_sels + sel_indexes >= selector) अणु
			selector -= all_sels;
			/*
			 * As we see here, pickable ranges work only as
			 * दीर्घ as the first selector क्रम each pickable
			 * range is 0, and the each subsequent range क्रम
			 * this 'pick' follow immediately at next unused
			 * selector (Eg. there is no gaps between ranges).
			 * I think this is fine but it probably should be
			 * करोcumented. OTOH, whole pickable range stuff
			 * might benefit from some करोcumentation
			 */
			वापस range->min + (range->step * selector);
		पूर्ण

		all_sels += (sel_indexes + 1);
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_list_voltage_pickable_linear_range);

/**
 * regulator_desc_list_voltage_linear_range - List voltages क्रम linear ranges
 *
 * @desc: Regulator desc क्रम regulator which volatges are to be listed
 * @selector: Selector to convert पूर्णांकo a voltage
 *
 * Regulators with a series of simple linear mappings between voltages
 * and selectors who have set linear_ranges in the regulator descriptor
 * can use this function prior regulator registration to list voltages.
 * This is useful when voltages need to be listed during device-tree
 * parsing.
 */
पूर्णांक regulator_desc_list_voltage_linear_range(स्थिर काष्ठा regulator_desc *desc,
					     अचिन्हित पूर्णांक selector)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	BUG_ON(!desc->n_linear_ranges);

	ret = linear_range_get_value_array(desc->linear_ranges,
					   desc->n_linear_ranges, selector,
					   &val);
	अगर (ret)
		वापस ret;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_desc_list_voltage_linear_range);

/**
 * regulator_list_voltage_linear_range - List voltages क्रम linear ranges
 *
 * @rdev: Regulator device
 * @selector: Selector to convert पूर्णांकo a voltage
 *
 * Regulators with a series of simple linear mappings between voltages
 * and selectors can set linear_ranges in the regulator descriptor and
 * then use this function as their list_voltage() operation,
 */
पूर्णांक regulator_list_voltage_linear_range(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक selector)
अणु
	वापस regulator_desc_list_voltage_linear_range(rdev->desc, selector);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_list_voltage_linear_range);

/**
 * regulator_list_voltage_table - List voltages with table based mapping
 *
 * @rdev: Regulator device
 * @selector: Selector to convert पूर्णांकo a voltage
 *
 * Regulators with table based mapping between voltages and
 * selectors can set volt_table in the regulator descriptor
 * and then use this function as their list_voltage() operation.
 */
पूर्णांक regulator_list_voltage_table(काष्ठा regulator_dev *rdev,
				 अचिन्हित पूर्णांक selector)
अणु
	अगर (!rdev->desc->volt_table) अणु
		BUG_ON(!rdev->desc->volt_table);
		वापस -EINVAL;
	पूर्ण

	अगर (selector >= rdev->desc->n_voltages)
		वापस -EINVAL;
	अगर (selector < rdev->desc->linear_min_sel)
		वापस 0;

	वापस rdev->desc->volt_table[selector];
पूर्ण
EXPORT_SYMBOL_GPL(regulator_list_voltage_table);

/**
 * regulator_set_bypass_regmap - Default set_bypass() using regmap
 *
 * @rdev: device to operate on.
 * @enable: state to set.
 */
पूर्णांक regulator_set_bypass_regmap(काष्ठा regulator_dev *rdev, bool enable)
अणु
	अचिन्हित पूर्णांक val;

	अगर (enable) अणु
		val = rdev->desc->bypass_val_on;
		अगर (!val)
			val = rdev->desc->bypass_mask;
	पूर्ण अन्यथा अणु
		val = rdev->desc->bypass_val_off;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, rdev->desc->bypass_reg,
				  rdev->desc->bypass_mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_bypass_regmap);

/**
 * regulator_set_soft_start_regmap - Default set_soft_start() using regmap
 *
 * @rdev: device to operate on.
 */
पूर्णांक regulator_set_soft_start_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;

	val = rdev->desc->soft_start_val_on;
	अगर (!val)
		val = rdev->desc->soft_start_mask;

	वापस regmap_update_bits(rdev->regmap, rdev->desc->soft_start_reg,
				  rdev->desc->soft_start_mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_soft_start_regmap);

/**
 * regulator_set_pull_करोwn_regmap - Default set_pull_करोwn() using regmap
 *
 * @rdev: device to operate on.
 */
पूर्णांक regulator_set_pull_करोwn_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;

	val = rdev->desc->pull_करोwn_val_on;
	अगर (!val)
		val = rdev->desc->pull_करोwn_mask;

	वापस regmap_update_bits(rdev->regmap, rdev->desc->pull_करोwn_reg,
				  rdev->desc->pull_करोwn_mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_pull_करोwn_regmap);

/**
 * regulator_get_bypass_regmap - Default get_bypass() using regmap
 *
 * @rdev: device to operate on.
 * @enable: current state.
 */
पूर्णांक regulator_get_bypass_regmap(काष्ठा regulator_dev *rdev, bool *enable)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक val_on = rdev->desc->bypass_val_on;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->bypass_reg, &val);
	अगर (ret != 0)
		वापस ret;

	अगर (!val_on)
		val_on = rdev->desc->bypass_mask;

	*enable = (val & rdev->desc->bypass_mask) == val_on;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_bypass_regmap);

/**
 * regulator_set_active_disअक्षरge_regmap - Default set_active_disअक्षरge()
 *					   using regmap
 *
 * @rdev: device to operate on.
 * @enable: state to set, 0 to disable and 1 to enable.
 */
पूर्णांक regulator_set_active_disअक्षरge_regmap(काष्ठा regulator_dev *rdev,
					  bool enable)
अणु
	अचिन्हित पूर्णांक val;

	अगर (enable)
		val = rdev->desc->active_disअक्षरge_on;
	अन्यथा
		val = rdev->desc->active_disअक्षरge_off;

	वापस regmap_update_bits(rdev->regmap,
				  rdev->desc->active_disअक्षरge_reg,
				  rdev->desc->active_disअक्षरge_mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_active_disअक्षरge_regmap);

/**
 * regulator_set_current_limit_regmap - set_current_limit क्रम regmap users
 *
 * @rdev: regulator to operate on
 * @min_uA: Lower bound क्रम current limit
 * @max_uA: Upper bound क्रम current limit
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O can set curr_table,
 * csel_reg and csel_mask fields in their descriptor and then use this
 * as their set_current_limit operation, saving some code.
 */
पूर्णांक regulator_set_current_limit_regmap(काष्ठा regulator_dev *rdev,
				       पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	अचिन्हित पूर्णांक n_currents = rdev->desc->n_current_limits;
	पूर्णांक i, sel = -1;

	अगर (n_currents == 0)
		वापस -EINVAL;

	अगर (rdev->desc->curr_table) अणु
		स्थिर अचिन्हित पूर्णांक *curr_table = rdev->desc->curr_table;
		bool ascend = curr_table[n_currents - 1] > curr_table[0];

		/* search क्रम बंदst to maximum */
		अगर (ascend) अणु
			क्रम (i = n_currents - 1; i >= 0; i--) अणु
				अगर (min_uA <= curr_table[i] &&
				    curr_table[i] <= max_uA) अणु
					sel = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < n_currents; i++) अणु
				अगर (min_uA <= curr_table[i] &&
				    curr_table[i] <= max_uA) अणु
					sel = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (sel < 0)
		वापस -EINVAL;

	sel <<= ffs(rdev->desc->csel_mask) - 1;

	वापस regmap_update_bits(rdev->regmap, rdev->desc->csel_reg,
				  rdev->desc->csel_mask, sel);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_current_limit_regmap);

/**
 * regulator_get_current_limit_regmap - get_current_limit क्रम regmap users
 *
 * @rdev: regulator to operate on
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O can set the
 * csel_reg and csel_mask fields in their descriptor and then use this
 * as their get_current_limit operation, saving some code.
 */
पूर्णांक regulator_get_current_limit_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->csel_reg, &val);
	अगर (ret != 0)
		वापस ret;

	val &= rdev->desc->csel_mask;
	val >>= ffs(rdev->desc->csel_mask) - 1;

	अगर (rdev->desc->curr_table) अणु
		अगर (val >= rdev->desc->n_current_limits)
			वापस -EINVAL;

		वापस rdev->desc->curr_table[val];
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_get_current_limit_regmap);

/**
 * regulator_bulk_set_supply_names - initialize the 'supply' fields in an array
 *                                   of regulator_bulk_data काष्ठाs
 *
 * @consumers: array of regulator_bulk_data entries to initialize
 * @supply_names: array of supply name strings
 * @num_supplies: number of supply names to initialize
 *
 * Note: the 'consumers' array must be the size of 'num_supplies'.
 */
व्योम regulator_bulk_set_supply_names(काष्ठा regulator_bulk_data *consumers,
				     स्थिर अक्षर *स्थिर *supply_names,
				     अचिन्हित पूर्णांक num_supplies)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_supplies; i++)
		consumers[i].supply = supply_names[i];
पूर्ण
EXPORT_SYMBOL_GPL(regulator_bulk_set_supply_names);

/**
 * regulator_is_equal - test whether two regulators are the same
 *
 * @reg1: first regulator to operate on
 * @reg2: second regulator to operate on
 */
bool regulator_is_equal(काष्ठा regulator *reg1, काष्ठा regulator *reg2)
अणु
	वापस reg1->rdev == reg2->rdev;
पूर्ण
EXPORT_SYMBOL_GPL(regulator_is_equal);

अटल पूर्णांक find_बंदst_bigger(अचिन्हित पूर्णांक target, स्थिर अचिन्हित पूर्णांक *table,
			       अचिन्हित पूर्णांक num_sel, अचिन्हित पूर्णांक *sel)
अणु
	अचिन्हित पूर्णांक s, पंचांगp, max, maxsel = 0;
	bool found = false;

	max = table[0];

	क्रम (s = 0; s < num_sel; s++) अणु
		अगर (table[s] > max) अणु
			max = table[s];
			maxsel = s;
		पूर्ण
		अगर (table[s] >= target) अणु
			अगर (!found || table[s] - target < पंचांगp - target) अणु
				पंचांगp = table[s];
				*sel = s;
				found = true;
				अगर (पंचांगp == target)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		*sel = maxsel;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * regulator_set_ramp_delay_regmap - set_ramp_delay() helper
 *
 * @rdev: regulator to operate on
 *
 * Regulators that use regmap क्रम their रेजिस्टर I/O can set the ramp_reg
 * and ramp_mask fields in their descriptor and then use this as their
 * set_ramp_delay operation, saving some code.
 */
पूर्णांक regulator_set_ramp_delay_regmap(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक sel;

	अगर (WARN_ON(!rdev->desc->n_ramp_values || !rdev->desc->ramp_delay_table))
		वापस -EINVAL;

	ret = find_बंदst_bigger(ramp_delay, rdev->desc->ramp_delay_table,
				  rdev->desc->n_ramp_values, &sel);

	अगर (ret) अणु
		dev_warn(rdev_get_dev(rdev),
			 "Can't set ramp-delay %u, setting %u\n", ramp_delay,
			 rdev->desc->ramp_delay_table[sel]);
	पूर्ण

	sel <<= ffs(rdev->desc->ramp_mask) - 1;

	वापस regmap_update_bits(rdev->regmap, rdev->desc->ramp_reg,
				  rdev->desc->ramp_mask, sel);
पूर्ण
EXPORT_SYMBOL_GPL(regulator_set_ramp_delay_regmap);
