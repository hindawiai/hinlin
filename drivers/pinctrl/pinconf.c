<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम the pin config portions of the pin control subप्रणाली
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#घोषणा pr_fmt(fmt) "pinconfig core: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश "core.h"
#समावेश "pinconf.h"

पूर्णांक pinconf_check_ops(काष्ठा pinctrl_dev *pctldev)
अणु
	स्थिर काष्ठा pinconf_ops *ops = pctldev->desc->confops;

	/* We have to be able to config the pins in SOME way */
	अगर (!ops->pin_config_set && !ops->pin_config_group_set) अणु
		dev_err(pctldev->dev,
			"pinconf has to be able to set a pins config\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक pinconf_validate_map(स्थिर काष्ठा pinctrl_map *map, पूर्णांक i)
अणु
	अगर (!map->data.configs.group_or_pin) अणु
		pr_err("failed to register map %s (%d): no group/pin given\n",
		       map->name, i);
		वापस -EINVAL;
	पूर्ण

	अगर (!map->data.configs.num_configs ||
			!map->data.configs.configs) अणु
		pr_err("failed to register map %s (%d): no configs given\n",
		       map->name, i);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pin_config_get_क्रम_pin(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			   अचिन्हित दीर्घ *config)
अणु
	स्थिर काष्ठा pinconf_ops *ops = pctldev->desc->confops;

	अगर (!ops || !ops->pin_config_get) अणु
		dev_dbg(pctldev->dev,
			"cannot get pin configuration, .pin_config_get missing in driver\n");
		वापस -ENOTSUPP;
	पूर्ण

	वापस ops->pin_config_get(pctldev, pin, config);
पूर्ण

पूर्णांक pin_config_group_get(स्थिर अक्षर *dev_name, स्थिर अक्षर *pin_group,
			 अचिन्हित दीर्घ *config)
अणु
	काष्ठा pinctrl_dev *pctldev;
	स्थिर काष्ठा pinconf_ops *ops;
	पूर्णांक selector, ret;

	pctldev = get_pinctrl_dev_from_devname(dev_name);
	अगर (!pctldev) अणु
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	mutex_lock(&pctldev->mutex);

	ops = pctldev->desc->confops;

	अगर (!ops || !ops->pin_config_group_get) अणु
		dev_dbg(pctldev->dev,
			"cannot get configuration for pin group, missing group config get function in driver\n");
		ret = -ENOTSUPP;
		जाओ unlock;
	पूर्ण

	selector = pinctrl_get_group_selector(pctldev, pin_group);
	अगर (selector < 0) अणु
		ret = selector;
		जाओ unlock;
	पूर्ण

	ret = ops->pin_config_group_get(pctldev, selector, config);

unlock:
	mutex_unlock(&pctldev->mutex);
	वापस ret;
पूर्ण

पूर्णांक pinconf_map_to_setting(स्थिर काष्ठा pinctrl_map *map,
			  काष्ठा pinctrl_setting *setting)
अणु
	काष्ठा pinctrl_dev *pctldev = setting->pctldev;
	पूर्णांक pin;

	चयन (setting->type) अणु
	हाल PIN_MAP_TYPE_CONFIGS_PIN:
		pin = pin_get_from_name(pctldev,
					map->data.configs.group_or_pin);
		अगर (pin < 0) अणु
			dev_err(pctldev->dev, "could not map pin config for \"%s\"",
				map->data.configs.group_or_pin);
			वापस pin;
		पूर्ण
		setting->data.configs.group_or_pin = pin;
		अवरोध;
	हाल PIN_MAP_TYPE_CONFIGS_GROUP:
		pin = pinctrl_get_group_selector(pctldev,
					 map->data.configs.group_or_pin);
		अगर (pin < 0) अणु
			dev_err(pctldev->dev, "could not map group config for \"%s\"",
				map->data.configs.group_or_pin);
			वापस pin;
		पूर्ण
		setting->data.configs.group_or_pin = pin;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	setting->data.configs.num_configs = map->data.configs.num_configs;
	setting->data.configs.configs = map->data.configs.configs;

	वापस 0;
पूर्ण

व्योम pinconf_मुक्त_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
पूर्ण

पूर्णांक pinconf_apply_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
	काष्ठा pinctrl_dev *pctldev = setting->pctldev;
	स्थिर काष्ठा pinconf_ops *ops = pctldev->desc->confops;
	पूर्णांक ret;

	अगर (!ops) अणु
		dev_err(pctldev->dev, "missing confops\n");
		वापस -EINVAL;
	पूर्ण

	चयन (setting->type) अणु
	हाल PIN_MAP_TYPE_CONFIGS_PIN:
		अगर (!ops->pin_config_set) अणु
			dev_err(pctldev->dev, "missing pin_config_set op\n");
			वापस -EINVAL;
		पूर्ण
		ret = ops->pin_config_set(pctldev,
				setting->data.configs.group_or_pin,
				setting->data.configs.configs,
				setting->data.configs.num_configs);
		अगर (ret < 0) अणु
			dev_err(pctldev->dev,
				"pin_config_set op failed for pin %d\n",
				setting->data.configs.group_or_pin);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल PIN_MAP_TYPE_CONFIGS_GROUP:
		अगर (!ops->pin_config_group_set) अणु
			dev_err(pctldev->dev,
				"missing pin_config_group_set op\n");
			वापस -EINVAL;
		पूर्ण
		ret = ops->pin_config_group_set(pctldev,
				setting->data.configs.group_or_pin,
				setting->data.configs.configs,
				setting->data.configs.num_configs);
		अगर (ret < 0) अणु
			dev_err(pctldev->dev,
				"pin_config_group_set op failed for group %d\n",
				setting->data.configs.group_or_pin);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pinconf_set_config(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
		       अचिन्हित दीर्घ *configs, माप_प्रकार nconfigs)
अणु
	स्थिर काष्ठा pinconf_ops *ops;

	ops = pctldev->desc->confops;
	अगर (!ops || !ops->pin_config_set)
		वापस -ENOTSUPP;

	वापस ops->pin_config_set(pctldev, pin, configs, nconfigs);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल व्योम pinconf_show_config(काष्ठा seq_file *s, काष्ठा pinctrl_dev *pctldev,
		      अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	स्थिर काष्ठा pinconf_ops *confops;
	पूर्णांक i;

	अगर (pctldev)
		confops = pctldev->desc->confops;
	अन्यथा
		confops = शून्य;

	क्रम (i = 0; i < num_configs; i++) अणु
		seq_माला_दो(s, "config ");
		अगर (confops && confops->pin_config_config_dbg_show)
			confops->pin_config_config_dbg_show(pctldev, s,
							    configs[i]);
		अन्यथा
			seq_म_लिखो(s, "%08lx", configs[i]);
		seq_अ_दो(s, '\n');
	पूर्ण
पूर्ण

व्योम pinconf_show_map(काष्ठा seq_file *s, स्थिर काष्ठा pinctrl_map *map)
अणु
	काष्ठा pinctrl_dev *pctldev;

	pctldev = get_pinctrl_dev_from_devname(map->ctrl_dev_name);

	चयन (map->type) अणु
	हाल PIN_MAP_TYPE_CONFIGS_PIN:
		seq_माला_दो(s, "pin ");
		अवरोध;
	हाल PIN_MAP_TYPE_CONFIGS_GROUP:
		seq_माला_दो(s, "group ");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	seq_म_लिखो(s, "%s\n", map->data.configs.group_or_pin);

	pinconf_show_config(s, pctldev, map->data.configs.configs,
			    map->data.configs.num_configs);
पूर्ण

व्योम pinconf_show_setting(काष्ठा seq_file *s,
			  स्थिर काष्ठा pinctrl_setting *setting)
अणु
	काष्ठा pinctrl_dev *pctldev = setting->pctldev;
	स्थिर काष्ठा pinctrl_ops *pctlops = pctldev->desc->pctlops;
	काष्ठा pin_desc *desc;

	चयन (setting->type) अणु
	हाल PIN_MAP_TYPE_CONFIGS_PIN:
		desc = pin_desc_get(setting->pctldev,
				    setting->data.configs.group_or_pin);
		seq_म_लिखो(s, "pin %s (%d)", desc->name,
			   setting->data.configs.group_or_pin);
		अवरोध;
	हाल PIN_MAP_TYPE_CONFIGS_GROUP:
		seq_म_लिखो(s, "group %s (%d)",
			   pctlops->get_group_name(pctldev,
					setting->data.configs.group_or_pin),
			   setting->data.configs.group_or_pin);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * FIXME: We should really get the pin controller to dump the config
	 * values, so they can be decoded to something meaningful.
	 */
	pinconf_show_config(s, pctldev, setting->data.configs.configs,
			    setting->data.configs.num_configs);
पूर्ण

अटल व्योम pinconf_dump_pin(काष्ठा pinctrl_dev *pctldev,
			     काष्ठा seq_file *s, पूर्णांक pin)
अणु
	स्थिर काष्ठा pinconf_ops *ops = pctldev->desc->confops;

	/* no-op when not using generic pin config */
	pinconf_generic_dump_pins(pctldev, s, शून्य, pin);
	अगर (ops && ops->pin_config_dbg_show)
		ops->pin_config_dbg_show(pctldev, s, pin);
पूर्ण

अटल पूर्णांक pinconf_pins_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_dev *pctldev = s->निजी;
	अचिन्हित i, pin;

	seq_माला_दो(s, "Pin config settings per pin\n");
	seq_माला_दो(s, "Format: pin (name): configs\n");

	mutex_lock(&pctldev->mutex);

	/* The pin number can be retrived from the pin controller descriptor */
	क्रम (i = 0; i < pctldev->desc->npins; i++) अणु
		काष्ठा pin_desc *desc;

		pin = pctldev->desc->pins[i].number;
		desc = pin_desc_get(pctldev, pin);
		/* Skip अगर we cannot search the pin */
		अगर (!desc)
			जारी;

		seq_म_लिखो(s, "pin %d (%s): ", pin, desc->name);

		pinconf_dump_pin(pctldev, s, pin);
		seq_अ_दो(s, '\n');
	पूर्ण

	mutex_unlock(&pctldev->mutex);

	वापस 0;
पूर्ण

अटल व्योम pinconf_dump_group(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा seq_file *s, अचिन्हित selector,
			       स्थिर अक्षर *gname)
अणु
	स्थिर काष्ठा pinconf_ops *ops = pctldev->desc->confops;

	/* no-op when not using generic pin config */
	pinconf_generic_dump_pins(pctldev, s, gname, 0);
	अगर (ops && ops->pin_config_group_dbg_show)
		ops->pin_config_group_dbg_show(pctldev, s, selector);
पूर्ण

अटल पूर्णांक pinconf_groups_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_dev *pctldev = s->निजी;
	स्थिर काष्ठा pinctrl_ops *pctlops = pctldev->desc->pctlops;
	अचिन्हित ngroups = pctlops->get_groups_count(pctldev);
	अचिन्हित selector = 0;

	seq_माला_दो(s, "Pin config settings per pin group\n");
	seq_माला_दो(s, "Format: group (name): configs\n");

	जबतक (selector < ngroups) अणु
		स्थिर अक्षर *gname = pctlops->get_group_name(pctldev, selector);

		seq_म_लिखो(s, "%u (%s): ", selector, gname);
		pinconf_dump_group(pctldev, s, selector, gname);
		seq_अ_दो(s, '\n');
		selector++;
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(pinconf_pins);
DEFINE_SHOW_ATTRIBUTE(pinconf_groups);

व्योम pinconf_init_device_debugfs(काष्ठा dentry *devroot,
			 काष्ठा pinctrl_dev *pctldev)
अणु
	debugfs_create_file("pinconf-pins", 0444,
			    devroot, pctldev, &pinconf_pins_fops);
	debugfs_create_file("pinconf-groups", 0444,
			    devroot, pctldev, &pinconf_groups_fops);
पूर्ण

#पूर्ण_अगर
