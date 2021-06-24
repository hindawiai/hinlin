<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell MVEBU pinctrl core driver
 *
 * Authors: Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *          Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pinctrl-mvebu.h"

#घोषणा MPPS_PER_REG	8
#घोषणा MPP_BITS	4
#घोषणा MPP_MASK	0xf

काष्ठा mvebu_pinctrl_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर **groups;
	अचिन्हित num_groups;
पूर्ण;

काष्ठा mvebu_pinctrl_group अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा mvebu_mpp_ctrl *ctrl;
	काष्ठा mvebu_mpp_ctrl_data *data;
	काष्ठा mvebu_mpp_ctrl_setting *settings;
	अचिन्हित num_settings;
	अचिन्हित gid;
	अचिन्हित *pins;
	अचिन्हित npins;
पूर्ण;

काष्ठा mvebu_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_desc desc;
	काष्ठा mvebu_pinctrl_group *groups;
	अचिन्हित num_groups;
	काष्ठा mvebu_pinctrl_function *functions;
	अचिन्हित num_functions;
	u8 variant;
पूर्ण;

पूर्णांक mvebu_mmio_mpp_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data,
			     अचिन्हित पूर्णांक pid, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित off = (pid / MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित shअगरt = (pid % MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;

	*config = (पढ़ोl(data->base + off) >> shअगरt) & MVEBU_MPP_MASK;

	वापस 0;
पूर्ण

पूर्णांक mvebu_mmio_mpp_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data,
			     अचिन्हित पूर्णांक pid, अचिन्हित दीर्घ config)
अणु
	अचिन्हित off = (pid / MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित shअगरt = (pid % MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(data->base + off) & ~(MVEBU_MPP_MASK << shअगरt);
	ग_लिखोl(reg | (config << shअगरt), data->base + off);

	वापस 0;
पूर्ण

अटल काष्ठा mvebu_pinctrl_group *mvebu_pinctrl_find_group_by_pid(
	काष्ठा mvebu_pinctrl *pctl, अचिन्हित pid)
अणु
	अचिन्हित n;
	क्रम (n = 0; n < pctl->num_groups; n++) अणु
		अगर (pid >= pctl->groups[n].pins[0] &&
		    pid < pctl->groups[n].pins[0] +
			pctl->groups[n].npins)
			वापस &pctl->groups[n];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mvebu_pinctrl_group *mvebu_pinctrl_find_group_by_name(
	काष्ठा mvebu_pinctrl *pctl, स्थिर अक्षर *name)
अणु
	अचिन्हित n;
	क्रम (n = 0; n < pctl->num_groups; n++) अणु
		अगर (म_भेद(name, pctl->groups[n].name) == 0)
			वापस &pctl->groups[n];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mvebu_mpp_ctrl_setting *mvebu_pinctrl_find_setting_by_val(
	काष्ठा mvebu_pinctrl *pctl, काष्ठा mvebu_pinctrl_group *grp,
	अचिन्हित दीर्घ config)
अणु
	अचिन्हित n;
	क्रम (n = 0; n < grp->num_settings; n++) अणु
		अगर (config == grp->settings[n].val) अणु
			अगर (!pctl->variant || (pctl->variant &
					       grp->settings[n].variant))
				वापस &grp->settings[n];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mvebu_mpp_ctrl_setting *mvebu_pinctrl_find_setting_by_name(
	काष्ठा mvebu_pinctrl *pctl, काष्ठा mvebu_pinctrl_group *grp,
	स्थिर अक्षर *name)
अणु
	अचिन्हित n;
	क्रम (n = 0; n < grp->num_settings; n++) अणु
		अगर (म_भेद(name, grp->settings[n].name) == 0) अणु
			अगर (!pctl->variant || (pctl->variant &
					       grp->settings[n].variant))
				वापस &grp->settings[n];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mvebu_mpp_ctrl_setting *mvebu_pinctrl_find_gpio_setting(
	काष्ठा mvebu_pinctrl *pctl, काष्ठा mvebu_pinctrl_group *grp)
अणु
	अचिन्हित n;
	क्रम (n = 0; n < grp->num_settings; n++) अणु
		अगर (grp->settings[n].flags &
			(MVEBU_SETTING_GPO | MVEBU_SETTING_GPI)) अणु
			अगर (!pctl->variant || (pctl->variant &
						grp->settings[n].variant))
				वापस &grp->settings[n];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mvebu_pinctrl_function *mvebu_pinctrl_find_function_by_name(
	काष्ठा mvebu_pinctrl *pctl, स्थिर अक्षर *name)
अणु
	अचिन्हित n;
	क्रम (n = 0; n < pctl->num_functions; n++) अणु
		अगर (म_भेद(name, pctl->functions[n].name) == 0)
			वापस &pctl->functions[n];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक mvebu_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित gid, अचिन्हित दीर्घ *config)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mvebu_pinctrl_group *grp = &pctl->groups[gid];

	अगर (!grp->ctrl)
		वापस -EINVAL;

	वापस grp->ctrl->mpp_get(grp->data, grp->pins[0], config);
पूर्ण

अटल पूर्णांक mvebu_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित gid, अचिन्हित दीर्घ *configs,
				अचिन्हित num_configs)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mvebu_pinctrl_group *grp = &pctl->groups[gid];
	पूर्णांक i, ret;

	अगर (!grp->ctrl)
		वापस -EINVAL;

	क्रम (i = 0; i < num_configs; i++) अणु
		ret = grp->ctrl->mpp_set(grp->data, grp->pins[0], configs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल व्योम mvebu_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
					काष्ठा seq_file *s, अचिन्हित gid)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mvebu_pinctrl_group *grp = &pctl->groups[gid];
	काष्ठा mvebu_mpp_ctrl_setting *curr;
	अचिन्हित दीर्घ config;
	अचिन्हित n;

	अगर (mvebu_pinconf_group_get(pctldev, gid, &config))
		वापस;

	curr = mvebu_pinctrl_find_setting_by_val(pctl, grp, config);

	अगर (curr) अणु
		seq_म_लिखो(s, "current: %s", curr->name);
		अगर (curr->subname)
			seq_म_लिखो(s, "(%s)", curr->subname);
		अगर (curr->flags & (MVEBU_SETTING_GPO | MVEBU_SETTING_GPI)) अणु
			seq_अ_दो(s, '(');
			अगर (curr->flags & MVEBU_SETTING_GPI)
				seq_अ_दो(s, 'i');
			अगर (curr->flags & MVEBU_SETTING_GPO)
				seq_अ_दो(s, 'o');
			seq_अ_दो(s, ')');
		पूर्ण
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "current: UNKNOWN");
	पूर्ण

	अगर (grp->num_settings > 1) अणु
		seq_माला_दो(s, ", available = [");
		क्रम (n = 0; n < grp->num_settings; n++) अणु
			अगर (curr == &grp->settings[n])
				जारी;

			/* skip unsupported settings क्रम this variant */
			अगर (pctl->variant &&
			    !(pctl->variant & grp->settings[n].variant))
				जारी;

			seq_म_लिखो(s, " %s", grp->settings[n].name);
			अगर (grp->settings[n].subname)
				seq_म_लिखो(s, "(%s)", grp->settings[n].subname);
			अगर (grp->settings[n].flags &
				(MVEBU_SETTING_GPO | MVEBU_SETTING_GPI)) अणु
				seq_अ_दो(s, '(');
				अगर (grp->settings[n].flags & MVEBU_SETTING_GPI)
					seq_अ_दो(s, 'i');
				अगर (grp->settings[n].flags & MVEBU_SETTING_GPO)
					seq_अ_दो(s, 'o');
				seq_अ_दो(s, ')');
			पूर्ण
		पूर्ण
		seq_माला_दो(s, " ]");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops mvebu_pinconf_ops = अणु
	.pin_config_group_get = mvebu_pinconf_group_get,
	.pin_config_group_set = mvebu_pinconf_group_set,
	.pin_config_group_dbg_show = mvebu_pinconf_group_dbg_show,
पूर्ण;

अटल पूर्णांक mvebu_pinmux_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->num_functions;
पूर्ण

अटल स्थिर अक्षर *mvebu_pinmux_get_func_name(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित fid)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->functions[fid].name;
पूर्ण

अटल पूर्णांक mvebu_pinmux_get_groups(काष्ठा pinctrl_dev *pctldev, अचिन्हित fid,
				स्थिर अक्षर * स्थिर **groups,
				अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctl->functions[fid].groups;
	*num_groups = pctl->functions[fid].num_groups;
	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pinmux_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित fid,
			    अचिन्हित gid)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mvebu_pinctrl_function *func = &pctl->functions[fid];
	काष्ठा mvebu_pinctrl_group *grp = &pctl->groups[gid];
	काष्ठा mvebu_mpp_ctrl_setting *setting;
	पूर्णांक ret;
	अचिन्हित दीर्घ config;

	setting = mvebu_pinctrl_find_setting_by_name(pctl, grp,
						     func->name);
	अगर (!setting) अणु
		dev_err(pctl->dev,
			"unable to find setting %s in group %s\n",
			func->name, func->groups[gid]);
		वापस -EINVAL;
	पूर्ण

	config = setting->val;
	ret = mvebu_pinconf_group_set(pctldev, grp->gid, &config, 1);
	अगर (ret) अणु
		dev_err(pctl->dev, "cannot set group %s to %s\n",
			func->groups[gid], func->name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pinmux_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_gpio_range *range, अचिन्हित offset)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mvebu_pinctrl_group *grp;
	काष्ठा mvebu_mpp_ctrl_setting *setting;
	अचिन्हित दीर्घ config;

	grp = mvebu_pinctrl_find_group_by_pid(pctl, offset);
	अगर (!grp)
		वापस -EINVAL;

	अगर (grp->ctrl->mpp_gpio_req)
		वापस grp->ctrl->mpp_gpio_req(grp->data, offset);

	setting = mvebu_pinctrl_find_gpio_setting(pctl, grp);
	अगर (!setting)
		वापस -ENOTSUPP;

	config = setting->val;

	वापस mvebu_pinconf_group_set(pctldev, grp->gid, &config, 1);
पूर्ण

अटल पूर्णांक mvebu_pinmux_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
	   काष्ठा pinctrl_gpio_range *range, अचिन्हित offset, bool input)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mvebu_pinctrl_group *grp;
	काष्ठा mvebu_mpp_ctrl_setting *setting;

	grp = mvebu_pinctrl_find_group_by_pid(pctl, offset);
	अगर (!grp)
		वापस -EINVAL;

	अगर (grp->ctrl->mpp_gpio_dir)
		वापस grp->ctrl->mpp_gpio_dir(grp->data, offset, input);

	setting = mvebu_pinctrl_find_gpio_setting(pctl, grp);
	अगर (!setting)
		वापस -ENOTSUPP;

	अगर ((input && (setting->flags & MVEBU_SETTING_GPI)) ||
	    (!input && (setting->flags & MVEBU_SETTING_GPO)))
		वापस 0;

	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops mvebu_pinmux_ops = अणु
	.get_functions_count = mvebu_pinmux_get_funcs_count,
	.get_function_name = mvebu_pinmux_get_func_name,
	.get_function_groups = mvebu_pinmux_get_groups,
	.gpio_request_enable = mvebu_pinmux_gpio_request_enable,
	.gpio_set_direction = mvebu_pinmux_gpio_set_direction,
	.set_mux = mvebu_pinmux_set,
पूर्ण;

अटल पूर्णांक mvebu_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	वापस pctl->num_groups;
पूर्ण

अटल स्थिर अक्षर *mvebu_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित gid)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	वापस pctl->groups[gid].name;
पूर्ण

अटल पूर्णांक mvebu_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित gid, स्थिर अचिन्हित **pins,
					अचिन्हित *num_pins)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	*pins = pctl->groups[gid].pins;
	*num_pins = pctl->groups[gid].npins;
	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pinctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
					काष्ठा device_node *np,
					काष्ठा pinctrl_map **map,
					अचिन्हित *num_maps)
अणु
	काष्ठा mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा property *prop;
	स्थिर अक्षर *function;
	स्थिर अक्षर *group;
	पूर्णांक ret, nmaps, n;

	*map = शून्य;
	*num_maps = 0;

	ret = of_property_पढ़ो_string(np, "marvell,function", &function);
	अगर (ret) अणु
		dev_err(pctl->dev,
			"missing marvell,function in node %pOFn\n", np);
		वापस 0;
	पूर्ण

	nmaps = of_property_count_strings(np, "marvell,pins");
	अगर (nmaps < 0) अणु
		dev_err(pctl->dev,
			"missing marvell,pins in node %pOFn\n", np);
		वापस 0;
	पूर्ण

	*map = kदो_स्मृति_array(nmaps, माप(**map), GFP_KERNEL);
	अगर (!*map)
		वापस -ENOMEM;

	n = 0;
	of_property_क्रम_each_string(np, "marvell,pins", prop, group) अणु
		काष्ठा mvebu_pinctrl_group *grp =
			mvebu_pinctrl_find_group_by_name(pctl, group);

		अगर (!grp) अणु
			dev_err(pctl->dev, "unknown pin %s", group);
			जारी;
		पूर्ण

		अगर (!mvebu_pinctrl_find_setting_by_name(pctl, grp, function)) अणु
			dev_err(pctl->dev, "unsupported function %s on pin %s",
				function, group);
			जारी;
		पूर्ण

		(*map)[n].type = PIN_MAP_TYPE_MUX_GROUP;
		(*map)[n].data.mux.group = group;
		(*map)[n].data.mux.function = function;
		n++;
	पूर्ण

	*num_maps = nmaps;

	वापस 0;
पूर्ण

अटल व्योम mvebu_pinctrl_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops mvebu_pinctrl_ops = अणु
	.get_groups_count = mvebu_pinctrl_get_groups_count,
	.get_group_name = mvebu_pinctrl_get_group_name,
	.get_group_pins = mvebu_pinctrl_get_group_pins,
	.dt_node_to_map = mvebu_pinctrl_dt_node_to_map,
	.dt_मुक्त_map = mvebu_pinctrl_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक _add_function(काष्ठा mvebu_pinctrl_function *funcs, पूर्णांक *funcsize,
			स्थिर अक्षर *name)
अणु
	अगर (*funcsize <= 0)
		वापस -EOVERFLOW;

	जबतक (funcs->num_groups) अणु
		/* function alपढ़ोy there */
		अगर (म_भेद(funcs->name, name) == 0) अणु
			funcs->num_groups++;
			वापस -EEXIST;
		पूर्ण
		funcs++;
	पूर्ण

	/* append new unique function */
	funcs->name = name;
	funcs->num_groups = 1;
	(*funcsize)--;

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pinctrl_build_functions(काष्ठा platक्रमm_device *pdev,
					 काष्ठा mvebu_pinctrl *pctl)
अणु
	काष्ठा mvebu_pinctrl_function *funcs;
	पूर्णांक num = 0, funcsize = pctl->desc.npins;
	पूर्णांक n, s;

	/* we allocate functions क्रम number of pins and hope
	 * there are fewer unique functions than pins available */
	funcs = devm_kसुस्मृति(&pdev->dev,
			     funcsize, माप(काष्ठा mvebu_pinctrl_function),
			     GFP_KERNEL);
	अगर (!funcs)
		वापस -ENOMEM;

	क्रम (n = 0; n < pctl->num_groups; n++) अणु
		काष्ठा mvebu_pinctrl_group *grp = &pctl->groups[n];
		क्रम (s = 0; s < grp->num_settings; s++) अणु
			पूर्णांक ret;

			/* skip unsupported settings on this variant */
			अगर (pctl->variant &&
			    !(pctl->variant & grp->settings[s].variant))
				जारी;

			/* check क्रम unique functions and count groups */
			ret = _add_function(funcs, &funcsize,
					    grp->settings[s].name);
			अगर (ret == -EOVERFLOW)
				dev_err(&pdev->dev,
					"More functions than pins(%d)\n",
					pctl->desc.npins);
			अगर (ret < 0)
				जारी;

			num++;
		पूर्ण
	पूर्ण

	pctl->num_functions = num;
	pctl->functions = funcs;

	क्रम (n = 0; n < pctl->num_groups; n++) अणु
		काष्ठा mvebu_pinctrl_group *grp = &pctl->groups[n];
		क्रम (s = 0; s < grp->num_settings; s++) अणु
			काष्ठा mvebu_pinctrl_function *f;
			स्थिर अक्षर **groups;

			/* skip unsupported settings on this variant */
			अगर (pctl->variant &&
			    !(pctl->variant & grp->settings[s].variant))
				जारी;

			f = mvebu_pinctrl_find_function_by_name(pctl,
							grp->settings[s].name);

			/* allocate group name array अगर not करोne alपढ़ोy */
			अगर (!f->groups) अणु
				f->groups = devm_kसुस्मृति(&pdev->dev,
						 f->num_groups,
						 माप(अक्षर *),
						 GFP_KERNEL);
				अगर (!f->groups)
					वापस -ENOMEM;
			पूर्ण

			/* find next मुक्त group name and assign current name */
			groups = f->groups;
			जबतक (*groups)
				groups++;
			*groups = grp->name;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mvebu_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_pinctrl_soc_info *soc = dev_get_platdata(&pdev->dev);
	काष्ठा mvebu_pinctrl *pctl;
	काष्ठा pinctrl_pin_desc *pdesc;
	अचिन्हित gid, n, k;
	अचिन्हित size, noname = 0;
	अक्षर *noname_buf;
	व्योम *p;
	पूर्णांक ret;

	अगर (!soc || !soc->controls || !soc->modes) अणु
		dev_err(&pdev->dev, "wrong pinctrl soc info\n");
		वापस -EINVAL;
	पूर्ण

	pctl = devm_kzalloc(&pdev->dev, माप(काष्ठा mvebu_pinctrl),
			GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;

	pctl->desc.name = dev_name(&pdev->dev);
	pctl->desc.owner = THIS_MODULE;
	pctl->desc.pctlops = &mvebu_pinctrl_ops;
	pctl->desc.pmxops = &mvebu_pinmux_ops;
	pctl->desc.confops = &mvebu_pinconf_ops;
	pctl->variant = soc->variant;
	pctl->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, pctl);

	/* count controls and create names क्रम mvebu generic
	   रेजिस्टर controls; also करोes sanity checks */
	pctl->num_groups = 0;
	pctl->desc.npins = 0;
	क्रम (n = 0; n < soc->ncontrols; n++) अणु
		स्थिर काष्ठा mvebu_mpp_ctrl *ctrl = &soc->controls[n];

		pctl->desc.npins += ctrl->npins;
		/* initialize control's pins[] array */
		क्रम (k = 0; k < ctrl->npins; k++)
			ctrl->pins[k] = ctrl->pid + k;

		/*
		 * We allow to pass controls with शून्य name that we treat
		 * as a range of one-pin groups with generic mvebu रेजिस्टर
		 * controls.
		 */
		अगर (!ctrl->name) अणु
			pctl->num_groups += ctrl->npins;
			noname += ctrl->npins;
		पूर्ण अन्यथा अणु
			pctl->num_groups += 1;
		पूर्ण
	पूर्ण

	pdesc = devm_kसुस्मृति(&pdev->dev,
			     pctl->desc.npins,
			     माप(काष्ठा pinctrl_pin_desc),
			     GFP_KERNEL);
	अगर (!pdesc)
		वापस -ENOMEM;

	क्रम (n = 0; n < pctl->desc.npins; n++)
		pdesc[n].number = n;
	pctl->desc.pins = pdesc;

	/*
	 * allocate groups and name buffers क्रम unnamed groups.
	 */
	size = pctl->num_groups * माप(*pctl->groups) + noname * 8;
	p = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pctl->groups = p;
	noname_buf = p + pctl->num_groups * माप(*pctl->groups);

	/* assign mpp controls to groups */
	gid = 0;
	क्रम (n = 0; n < soc->ncontrols; n++) अणु
		स्थिर काष्ठा mvebu_mpp_ctrl *ctrl = &soc->controls[n];
		काष्ठा mvebu_mpp_ctrl_data *data = soc->control_data ?
						   &soc->control_data[n] : शून्य;

		pctl->groups[gid].gid = gid;
		pctl->groups[gid].ctrl = ctrl;
		pctl->groups[gid].data = data;
		pctl->groups[gid].name = ctrl->name;
		pctl->groups[gid].pins = ctrl->pins;
		pctl->groups[gid].npins = ctrl->npins;

		/*
		 * We treat unnamed controls as a range of one-pin groups
		 * with generic mvebu रेजिस्टर controls. Use one group क्रम
		 * each in this range and assign a शेष group name.
		 */
		अगर (!ctrl->name) अणु
			pctl->groups[gid].name = noname_buf;
			pctl->groups[gid].npins = 1;
			प्र_लिखो(noname_buf, "mpp%d", ctrl->pid+0);
			noname_buf += 8;

			क्रम (k = 1; k < ctrl->npins; k++) अणु
				gid++;
				pctl->groups[gid].gid = gid;
				pctl->groups[gid].ctrl = ctrl;
				pctl->groups[gid].data = data;
				pctl->groups[gid].name = noname_buf;
				pctl->groups[gid].pins = &ctrl->pins[k];
				pctl->groups[gid].npins = 1;
				प्र_लिखो(noname_buf, "mpp%d", ctrl->pid+k);
				noname_buf += 8;
			पूर्ण
		पूर्ण
		gid++;
	पूर्ण

	/* assign mpp modes to groups */
	क्रम (n = 0; n < soc->nmodes; n++) अणु
		काष्ठा mvebu_mpp_mode *mode = &soc->modes[n];
		काष्ठा mvebu_mpp_ctrl_setting *set = &mode->settings[0];
		काष्ठा mvebu_pinctrl_group *grp;
		अचिन्हित num_settings;
		अचिन्हित supp_settings;

		क्रम (num_settings = 0, supp_settings = 0; ; set++) अणु
			अगर (!set->name)
				अवरोध;

			num_settings++;

			/* skip unsupported settings क्रम this variant */
			अगर (pctl->variant && !(pctl->variant & set->variant))
				जारी;

			supp_settings++;

			/* find gpio/gpo/gpi settings */
			अगर (म_भेद(set->name, "gpio") == 0)
				set->flags = MVEBU_SETTING_GPI |
					MVEBU_SETTING_GPO;
			अन्यथा अगर (म_भेद(set->name, "gpo") == 0)
				set->flags = MVEBU_SETTING_GPO;
			अन्यथा अगर (म_भेद(set->name, "gpi") == 0)
				set->flags = MVEBU_SETTING_GPI;
		पूर्ण

		/* skip modes with no settings क्रम this variant */
		अगर (!supp_settings)
			जारी;

		grp = mvebu_pinctrl_find_group_by_pid(pctl, mode->pid);
		अगर (!grp) अणु
			dev_warn(&pdev->dev, "unknown pinctrl group %d\n",
				mode->pid);
			जारी;
		पूर्ण

		grp->settings = mode->settings;
		grp->num_settings = num_settings;
	पूर्ण

	ret = mvebu_pinctrl_build_functions(pdev, pctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to build functions\n");
		वापस ret;
	पूर्ण

	pctl->pctldev = devm_pinctrl_रेजिस्टर(&pdev->dev, &pctl->desc, pctl);
	अगर (IS_ERR(pctl->pctldev)) अणु
		dev_err(&pdev->dev, "unable to register pinctrl driver\n");
		वापस PTR_ERR(pctl->pctldev);
	पूर्ण

	dev_info(&pdev->dev, "registered pinctrl driver\n");

	/* रेजिस्टर gpio ranges */
	क्रम (n = 0; n < soc->ngpioranges; n++)
		pinctrl_add_gpio_range(pctl->pctldev, &soc->gpioranges[n]);

	वापस 0;
पूर्ण

/*
 * mvebu_pinctrl_simple_mmio_probe - probe a simple mmio pinctrl
 * @pdev: platक्रमm device (with platक्रमm data alपढ़ोy attached)
 *
 * Initialise a simple (single base address) mmio pinctrl driver,
 * assigning the MMIO base address to all mvebu mpp ctrl instances.
 */
पूर्णांक mvebu_pinctrl_simple_mmio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_pinctrl_soc_info *soc = dev_get_platdata(&pdev->dev);
	काष्ठा mvebu_mpp_ctrl_data *mpp_data;
	व्योम __iomem *base;
	पूर्णांक i;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	mpp_data = devm_kसुस्मृति(&pdev->dev, soc->ncontrols, माप(*mpp_data),
				GFP_KERNEL);
	अगर (!mpp_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < soc->ncontrols; i++)
		mpp_data[i].base = base;

	soc->control_data = mpp_data;

	वापस mvebu_pinctrl_probe(pdev);
पूर्ण

पूर्णांक mvebu_regmap_mpp_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data,
			      अचिन्हित पूर्णांक pid, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित off = (pid / MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित shअगरt = (pid % MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap.map, data->regmap.offset + off, &val);
	अगर (err)
		वापस err;

	*config = (val >> shअगरt) & MVEBU_MPP_MASK;

	वापस 0;
पूर्ण

पूर्णांक mvebu_regmap_mpp_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data,
			      अचिन्हित पूर्णांक pid, अचिन्हित दीर्घ config)
अणु
	अचिन्हित off = (pid / MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;
	अचिन्हित shअगरt = (pid % MVEBU_MPPS_PER_REG) * MVEBU_MPP_BITS;

	वापस regmap_update_bits(data->regmap.map, data->regmap.offset + off,
				  MVEBU_MPP_MASK << shअगरt, config << shअगरt);
पूर्ण

पूर्णांक mvebu_pinctrl_simple_regmap_probe(काष्ठा platक्रमm_device *pdev,
				      काष्ठा device *syscon_dev, u32 offset)
अणु
	काष्ठा mvebu_pinctrl_soc_info *soc = dev_get_platdata(&pdev->dev);
	काष्ठा mvebu_mpp_ctrl_data *mpp_data;
	काष्ठा regmap *regmap;
	पूर्णांक i;

	regmap = syscon_node_to_regmap(syscon_dev->of_node);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	mpp_data = devm_kसुस्मृति(&pdev->dev, soc->ncontrols, माप(*mpp_data),
				GFP_KERNEL);
	अगर (!mpp_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < soc->ncontrols; i++) अणु
		mpp_data[i].regmap.map = regmap;
		mpp_data[i].regmap.offset = offset;
	पूर्ण

	soc->control_data = mpp_data;

	वापस mvebu_pinctrl_probe(pdev);
पूर्ण
