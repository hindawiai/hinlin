<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OF helpers क्रम regulator framework
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

#समावेश "internal.h"

अटल स्थिर अक्षर *स्थिर regulator_states[PM_SUSPEND_MAX + 1] = अणु
	[PM_SUSPEND_STANDBY]	= "regulator-state-standby",
	[PM_SUSPEND_MEM]	= "regulator-state-mem",
	[PM_SUSPEND_MAX]	= "regulator-state-disk",
पूर्ण;

अटल पूर्णांक of_get_regulation_स्थिरraपूर्णांकs(काष्ठा device *dev,
					काष्ठा device_node *np,
					काष्ठा regulator_init_data **init_data,
					स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा regulation_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs = &(*init_data)->स्थिरraपूर्णांकs;
	काष्ठा regulator_state *suspend_state;
	काष्ठा device_node *suspend_np;
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret, i, len;
	पूर्णांक n_phandles;
	u32 pval;

	n_phandles = of_count_phandle_with_args(np, "regulator-coupled-with",
						शून्य);
	n_phandles = max(n_phandles, 0);

	स्थिरraपूर्णांकs->name = of_get_property(np, "regulator-name", शून्य);

	अगर (!of_property_पढ़ो_u32(np, "regulator-min-microvolt", &pval))
		स्थिरraपूर्णांकs->min_uV = pval;

	अगर (!of_property_पढ़ो_u32(np, "regulator-max-microvolt", &pval))
		स्थिरraपूर्णांकs->max_uV = pval;

	/* Voltage change possible? */
	अगर (स्थिरraपूर्णांकs->min_uV != स्थिरraपूर्णांकs->max_uV)
		स्थिरraपूर्णांकs->valid_ops_mask |= REGULATOR_CHANGE_VOLTAGE;

	/* Do we have a voltage range, अगर so try to apply it? */
	अगर (स्थिरraपूर्णांकs->min_uV && स्थिरraपूर्णांकs->max_uV)
		स्थिरraपूर्णांकs->apply_uV = true;

	अगर (!of_property_पढ़ो_u32(np, "regulator-microvolt-offset", &pval))
		स्थिरraपूर्णांकs->uV_offset = pval;
	अगर (!of_property_पढ़ो_u32(np, "regulator-min-microamp", &pval))
		स्थिरraपूर्णांकs->min_uA = pval;
	अगर (!of_property_पढ़ो_u32(np, "regulator-max-microamp", &pval))
		स्थिरraपूर्णांकs->max_uA = pval;

	अगर (!of_property_पढ़ो_u32(np, "regulator-input-current-limit-microamp",
				  &pval))
		स्थिरraपूर्णांकs->ilim_uA = pval;

	/* Current change possible? */
	अगर (स्थिरraपूर्णांकs->min_uA != स्थिरraपूर्णांकs->max_uA)
		स्थिरraपूर्णांकs->valid_ops_mask |= REGULATOR_CHANGE_CURRENT;

	स्थिरraपूर्णांकs->boot_on = of_property_पढ़ो_bool(np, "regulator-boot-on");
	स्थिरraपूर्णांकs->always_on = of_property_पढ़ो_bool(np, "regulator-always-on");
	अगर (!स्थिरraपूर्णांकs->always_on) /* status change should be possible. */
		स्थिरraपूर्णांकs->valid_ops_mask |= REGULATOR_CHANGE_STATUS;

	स्थिरraपूर्णांकs->pull_करोwn = of_property_पढ़ो_bool(np, "regulator-pull-down");

	अगर (of_property_पढ़ो_bool(np, "regulator-allow-bypass"))
		स्थिरraपूर्णांकs->valid_ops_mask |= REGULATOR_CHANGE_BYPASS;

	अगर (of_property_पढ़ो_bool(np, "regulator-allow-set-load"))
		स्थिरraपूर्णांकs->valid_ops_mask |= REGULATOR_CHANGE_DRMS;

	ret = of_property_पढ़ो_u32(np, "regulator-ramp-delay", &pval);
	अगर (!ret) अणु
		अगर (pval)
			स्थिरraपूर्णांकs->ramp_delay = pval;
		अन्यथा
			स्थिरraपूर्णांकs->ramp_disable = true;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "regulator-settling-time-us", &pval);
	अगर (!ret)
		स्थिरraपूर्णांकs->settling_समय = pval;

	ret = of_property_पढ़ो_u32(np, "regulator-settling-time-up-us", &pval);
	अगर (!ret)
		स्थिरraपूर्णांकs->settling_समय_up = pval;
	अगर (स्थिरraपूर्णांकs->settling_समय_up && स्थिरraपूर्णांकs->settling_समय) अणु
		pr_warn("%pOFn: ambiguous configuration for settling time, ignoring 'regulator-settling-time-up-us'\n",
			np);
		स्थिरraपूर्णांकs->settling_समय_up = 0;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "regulator-settling-time-down-us",
				   &pval);
	अगर (!ret)
		स्थिरraपूर्णांकs->settling_समय_करोwn = pval;
	अगर (स्थिरraपूर्णांकs->settling_समय_करोwn && स्थिरraपूर्णांकs->settling_समय) अणु
		pr_warn("%pOFn: ambiguous configuration for settling time, ignoring 'regulator-settling-time-down-us'\n",
			np);
		स्थिरraपूर्णांकs->settling_समय_करोwn = 0;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "regulator-enable-ramp-delay", &pval);
	अगर (!ret)
		स्थिरraपूर्णांकs->enable_समय = pval;

	स्थिरraपूर्णांकs->soft_start = of_property_पढ़ो_bool(np,
					"regulator-soft-start");
	ret = of_property_पढ़ो_u32(np, "regulator-active-discharge", &pval);
	अगर (!ret) अणु
		स्थिरraपूर्णांकs->active_disअक्षरge =
				(pval) ? REGULATOR_ACTIVE_DISCHARGE_ENABLE :
					REGULATOR_ACTIVE_DISCHARGE_DISABLE;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "regulator-initial-mode", &pval)) अणु
		अगर (desc && desc->of_map_mode) अणु
			mode = desc->of_map_mode(pval);
			अगर (mode == REGULATOR_MODE_INVALID)
				pr_err("%pOFn: invalid mode %u\n", np, pval);
			अन्यथा
				स्थिरraपूर्णांकs->initial_mode = mode;
		पूर्ण अन्यथा अणु
			pr_warn("%pOFn: mapping for mode %d not defined\n",
				np, pval);
		पूर्ण
	पूर्ण

	len = of_property_count_elems_of_size(np, "regulator-allowed-modes",
						माप(u32));
	अगर (len > 0) अणु
		अगर (desc && desc->of_map_mode) अणु
			क्रम (i = 0; i < len; i++) अणु
				ret = of_property_पढ़ो_u32_index(np,
					"regulator-allowed-modes", i, &pval);
				अगर (ret) अणु
					pr_err("%pOFn: couldn't read allowed modes index %d, ret=%d\n",
						np, i, ret);
					अवरोध;
				पूर्ण
				mode = desc->of_map_mode(pval);
				अगर (mode == REGULATOR_MODE_INVALID)
					pr_err("%pOFn: invalid regulator-allowed-modes element %u\n",
						np, pval);
				अन्यथा
					स्थिरraपूर्णांकs->valid_modes_mask |= mode;
			पूर्ण
			अगर (स्थिरraपूर्णांकs->valid_modes_mask)
				स्थिरraपूर्णांकs->valid_ops_mask
					|= REGULATOR_CHANGE_MODE;
		पूर्ण अन्यथा अणु
			pr_warn("%pOFn: mode mapping not defined\n", np);
		पूर्ण
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "regulator-system-load", &pval))
		स्थिरraपूर्णांकs->प्रणाली_load = pval;

	अगर (n_phandles) अणु
		स्थिरraपूर्णांकs->max_spपढ़ो = devm_kzalloc(dev,
				माप(*स्थिरraपूर्णांकs->max_spपढ़ो) * n_phandles,
				GFP_KERNEL);

		अगर (!स्थिरraपूर्णांकs->max_spपढ़ो)
			वापस -ENOMEM;

		of_property_पढ़ो_u32_array(np, "regulator-coupled-max-spread",
					   स्थिरraपूर्णांकs->max_spपढ़ो, n_phandles);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "regulator-max-step-microvolt",
				  &pval))
		स्थिरraपूर्णांकs->max_uV_step = pval;

	स्थिरraपूर्णांकs->over_current_protection = of_property_पढ़ो_bool(np,
					"regulator-over-current-protection");

	क्रम (i = 0; i < ARRAY_SIZE(regulator_states); i++) अणु
		चयन (i) अणु
		हाल PM_SUSPEND_MEM:
			suspend_state = &स्थिरraपूर्णांकs->state_mem;
			अवरोध;
		हाल PM_SUSPEND_MAX:
			suspend_state = &स्थिरraपूर्णांकs->state_disk;
			अवरोध;
		हाल PM_SUSPEND_STANDBY:
			suspend_state = &स्थिरraपूर्णांकs->state_standby;
			अवरोध;
		हाल PM_SUSPEND_ON:
		हाल PM_SUSPEND_TO_IDLE:
		शेष:
			जारी;
		पूर्ण

		suspend_np = of_get_child_by_name(np, regulator_states[i]);
		अगर (!suspend_np || !suspend_state)
			जारी;

		अगर (!of_property_पढ़ो_u32(suspend_np, "regulator-mode",
					  &pval)) अणु
			अगर (desc && desc->of_map_mode) अणु
				mode = desc->of_map_mode(pval);
				अगर (mode == REGULATOR_MODE_INVALID)
					pr_err("%pOFn: invalid mode %u\n",
					       np, pval);
				अन्यथा
					suspend_state->mode = mode;
			पूर्ण अन्यथा अणु
				pr_warn("%pOFn: mapping for mode %d not defined\n",
					np, pval);
			पूर्ण
		पूर्ण

		अगर (of_property_पढ़ो_bool(suspend_np,
					"regulator-on-in-suspend"))
			suspend_state->enabled = ENABLE_IN_SUSPEND;
		अन्यथा अगर (of_property_पढ़ो_bool(suspend_np,
					"regulator-off-in-suspend"))
			suspend_state->enabled = DISABLE_IN_SUSPEND;

		अगर (!of_property_पढ़ो_u32(suspend_np,
				"regulator-suspend-min-microvolt", &pval))
			suspend_state->min_uV = pval;

		अगर (!of_property_पढ़ो_u32(suspend_np,
				"regulator-suspend-max-microvolt", &pval))
			suspend_state->max_uV = pval;

		अगर (!of_property_पढ़ो_u32(suspend_np,
					"regulator-suspend-microvolt", &pval))
			suspend_state->uV = pval;
		अन्यथा /* otherwise use min_uV as शेष suspend voltage */
			suspend_state->uV = suspend_state->min_uV;

		अगर (of_property_पढ़ो_bool(suspend_np,
					"regulator-changeable-in-suspend"))
			suspend_state->changeable = true;

		अगर (i == PM_SUSPEND_MEM)
			स्थिरraपूर्णांकs->initial_state = PM_SUSPEND_MEM;

		of_node_put(suspend_np);
		suspend_state = शून्य;
		suspend_np = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * of_get_regulator_init_data - extract regulator_init_data काष्ठाure info
 * @dev: device requesting क्रम regulator_init_data
 * @node: regulator device node
 * @desc: regulator description
 *
 * Populates regulator_init_data काष्ठाure by extracting data from device
 * tree node, वापसs a poपूर्णांकer to the populated काष्ठाure or शून्य अगर memory
 * alloc fails.
 */
काष्ठा regulator_init_data *of_get_regulator_init_data(काष्ठा device *dev,
					  काष्ठा device_node *node,
					  स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा regulator_init_data *init_data;

	अगर (!node)
		वापस शून्य;

	init_data = devm_kzalloc(dev, माप(*init_data), GFP_KERNEL);
	अगर (!init_data)
		वापस शून्य; /* Out of memory? */

	अगर (of_get_regulation_स्थिरraपूर्णांकs(dev, node, &init_data, desc))
		वापस शून्य;

	वापस init_data;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_regulator_init_data);

काष्ठा devm_of_regulator_matches अणु
	काष्ठा of_regulator_match *matches;
	अचिन्हित पूर्णांक num_matches;
पूर्ण;

अटल व्योम devm_of_regulator_put_matches(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा devm_of_regulator_matches *devm_matches = res;
	पूर्णांक i;

	क्रम (i = 0; i < devm_matches->num_matches; i++)
		of_node_put(devm_matches->matches[i].of_node);
पूर्ण

/**
 * of_regulator_match - extract multiple regulator init data from device tree.
 * @dev: device requesting the data
 * @node: parent device node of the regulators
 * @matches: match table क्रम the regulators
 * @num_matches: number of entries in match table
 *
 * This function uses a match table specअगरied by the regulator driver to
 * parse regulator init data from the device tree. @node is expected to
 * contain a set of child nodes, each providing the init data क्रम one
 * regulator. The data parsed from a child node will be matched to a regulator
 * based on either the deprecated property regulator-compatible अगर present,
 * or otherwise the child node's name. Note that the match table is modअगरied
 * in place and an additional of_node reference is taken क्रम each matched
 * regulator.
 *
 * Returns the number of matches found or a negative error code on failure.
 */
पूर्णांक of_regulator_match(काष्ठा device *dev, काष्ठा device_node *node,
		       काष्ठा of_regulator_match *matches,
		       अचिन्हित पूर्णांक num_matches)
अणु
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर *name;
	काष्ठा device_node *child;
	काष्ठा devm_of_regulator_matches *devm_matches;

	अगर (!dev || !node)
		वापस -EINVAL;

	devm_matches = devres_alloc(devm_of_regulator_put_matches,
				    माप(काष्ठा devm_of_regulator_matches),
				    GFP_KERNEL);
	अगर (!devm_matches)
		वापस -ENOMEM;

	devm_matches->matches = matches;
	devm_matches->num_matches = num_matches;

	devres_add(dev, devm_matches);

	क्रम (i = 0; i < num_matches; i++) अणु
		काष्ठा of_regulator_match *match = &matches[i];
		match->init_data = शून्य;
		match->of_node = शून्य;
	पूर्ण

	क्रम_each_child_of_node(node, child) अणु
		name = of_get_property(child,
					"regulator-compatible", शून्य);
		अगर (!name)
			name = child->name;
		क्रम (i = 0; i < num_matches; i++) अणु
			काष्ठा of_regulator_match *match = &matches[i];
			अगर (match->of_node)
				जारी;

			अगर (म_भेद(match->name, name))
				जारी;

			match->init_data =
				of_get_regulator_init_data(dev, child,
							   match->desc);
			अगर (!match->init_data) अणु
				dev_err(dev,
					"failed to parse DT for regulator %pOFn\n",
					child);
				of_node_put(child);
				वापस -EINVAL;
			पूर्ण
			match->of_node = of_node_get(child);
			count++;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(of_regulator_match);

अटल काष्ठा
device_node *regulator_of_get_init_node(काष्ठा device *dev,
					स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा device_node *search, *child;
	स्थिर अक्षर *name;

	अगर (!dev->of_node || !desc->of_match)
		वापस शून्य;

	अगर (desc->regulators_node) अणु
		search = of_get_child_by_name(dev->of_node,
					      desc->regulators_node);
	पूर्ण अन्यथा अणु
		search = of_node_get(dev->of_node);

		अगर (!म_भेद(desc->of_match, search->name))
			वापस search;
	पूर्ण

	अगर (!search) अणु
		dev_dbg(dev, "Failed to find regulator container node '%s'\n",
			desc->regulators_node);
		वापस शून्य;
	पूर्ण

	क्रम_each_available_child_of_node(search, child) अणु
		name = of_get_property(child, "regulator-compatible", शून्य);
		अगर (!name) अणु
			अगर (!desc->of_match_full_name)
				name = child->name;
			अन्यथा
				name = child->full_name;
		पूर्ण

		अगर (!म_भेद(desc->of_match, name)) अणु
			of_node_put(search);
			/*
			 * 'of_node_get(child)' is alपढ़ोy perक्रमmed by the
			 * क्रम_each loop.
			 */
			वापस child;
		पूर्ण
	पूर्ण

	of_node_put(search);

	वापस शून्य;
पूर्ण

काष्ठा regulator_init_data *regulator_of_get_init_data(काष्ठा device *dev,
					    स्थिर काष्ठा regulator_desc *desc,
					    काष्ठा regulator_config *config,
					    काष्ठा device_node **node)
अणु
	काष्ठा device_node *child;
	काष्ठा regulator_init_data *init_data = शून्य;

	child = regulator_of_get_init_node(dev, desc);
	अगर (!child)
		वापस शून्य;

	init_data = of_get_regulator_init_data(dev, child, desc);
	अगर (!init_data) अणु
		dev_err(dev, "failed to parse DT for regulator %pOFn\n", child);
		जाओ error;
	पूर्ण

	अगर (desc->of_parse_cb) अणु
		पूर्णांक ret;

		ret = desc->of_parse_cb(child, desc, config);
		अगर (ret) अणु
			अगर (ret == -EPROBE_DEFER) अणु
				of_node_put(child);
				वापस ERR_PTR(-EPROBE_DEFER);
			पूर्ण
			dev_err(dev,
				"driver callback failed to parse DT for regulator %pOFn\n",
				child);
			जाओ error;
		पूर्ण
	पूर्ण

	*node = child;

	वापस init_data;

error:
	of_node_put(child);

	वापस शून्य;
पूर्ण

काष्ठा regulator_dev *of_find_regulator_by_node(काष्ठा device_node *np)
अणु
	काष्ठा device *dev;

	dev = class_find_device_by_of_node(&regulator_class, np);

	वापस dev ? dev_to_rdev(dev) : शून्य;
पूर्ण

/*
 * Returns number of regulators coupled with rdev.
 */
पूर्णांक of_get_n_coupled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा device_node *node = rdev->dev.of_node;
	पूर्णांक n_phandles;

	n_phandles = of_count_phandle_with_args(node,
						"regulator-coupled-with",
						शून्य);

	वापस (n_phandles > 0) ? n_phandles : 0;
पूर्ण

/* Looks क्रम "to_find" device_node in src's "regulator-coupled-with" property */
अटल bool of_coupling_find_node(काष्ठा device_node *src,
				  काष्ठा device_node *to_find,
				  पूर्णांक *index)
अणु
	पूर्णांक n_phandles, i;
	bool found = false;

	n_phandles = of_count_phandle_with_args(src,
						"regulator-coupled-with",
						शून्य);

	क्रम (i = 0; i < n_phandles; i++) अणु
		काष्ठा device_node *पंचांगp = of_parse_phandle(src,
					   "regulator-coupled-with", i);

		अगर (!पंचांगp)
			अवरोध;

		/* found */
		अगर (पंचांगp == to_find)
			found = true;

		of_node_put(पंचांगp);

		अगर (found) अणु
			*index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

/**
 * of_check_coupling_data - Parse rdev's coupling properties and check data
 *			    consistency
 * @rdev: poपूर्णांकer to regulator_dev whose data is checked
 *
 * Function checks अगर all the following conditions are met:
 * - rdev's max_spपढ़ो is greater than 0
 * - all coupled regulators have the same max_spपढ़ो
 * - all coupled regulators have the same number of regulator_dev phandles
 * - all regulators are linked to each other
 *
 * Returns true अगर all conditions are met.
 */
bool of_check_coupling_data(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा device_node *node = rdev->dev.of_node;
	पूर्णांक n_phandles = of_get_n_coupled(rdev);
	काष्ठा device_node *c_node;
	पूर्णांक index;
	पूर्णांक i;
	bool ret = true;

	/* iterate over rdev's phandles */
	क्रम (i = 0; i < n_phandles; i++) अणु
		पूर्णांक max_spपढ़ो = rdev->स्थिरraपूर्णांकs->max_spपढ़ो[i];
		पूर्णांक c_max_spपढ़ो, c_n_phandles;

		अगर (max_spपढ़ो <= 0) अणु
			dev_err(&rdev->dev, "max_spread value invalid\n");
			वापस false;
		पूर्ण

		c_node = of_parse_phandle(node,
					  "regulator-coupled-with", i);

		अगर (!c_node)
			ret = false;

		c_n_phandles = of_count_phandle_with_args(c_node,
							  "regulator-coupled-with",
							  शून्य);

		अगर (c_n_phandles != n_phandles) अणु
			dev_err(&rdev->dev, "number of coupled reg phandles mismatch\n");
			ret = false;
			जाओ clean;
		पूर्ण

		अगर (!of_coupling_find_node(c_node, node, &index)) अणु
			dev_err(&rdev->dev, "missing 2-way linking for coupled regulators\n");
			ret = false;
			जाओ clean;
		पूर्ण

		अगर (of_property_पढ़ो_u32_index(c_node, "regulator-coupled-max-spread",
					       index, &c_max_spपढ़ो)) अणु
			ret = false;
			जाओ clean;
		पूर्ण

		अगर (c_max_spपढ़ो != max_spपढ़ो) अणु
			dev_err(&rdev->dev,
				"coupled regulators max_spread mismatch\n");
			ret = false;
			जाओ clean;
		पूर्ण

clean:
		of_node_put(c_node);
		अगर (!ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * of_parse_coupled regulator - Get regulator_dev poपूर्णांकer from rdev's property
 * @rdev: Poपूर्णांकer to regulator_dev, whose DTS is used as a source to parse
 *	  "regulator-coupled-with" property
 * @index: Index in phandles array
 *
 * Returns the regulator_dev poपूर्णांकer parsed from DTS. If it has not been yet
 * रेजिस्टरed, वापसs शून्य
 */
काष्ठा regulator_dev *of_parse_coupled_regulator(काष्ठा regulator_dev *rdev,
						 पूर्णांक index)
अणु
	काष्ठा device_node *node = rdev->dev.of_node;
	काष्ठा device_node *c_node;
	काष्ठा regulator_dev *c_rdev;

	c_node = of_parse_phandle(node, "regulator-coupled-with", index);
	अगर (!c_node)
		वापस शून्य;

	c_rdev = of_find_regulator_by_node(c_node);

	of_node_put(c_node);

	वापस c_rdev;
पूर्ण
