<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम the pin muxing portions of the pin control subप्रणाली
 *
 * Copyright (C) 2011-2012 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * Based on bits of regulator core, gpio core and clk core
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * Copyright (C) 2012 NVIDIA CORPORATION. All rights reserved.
 */
#घोषणा pr_fmt(fmt) "pinmux core: " fmt

#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश "core.h"
#समावेश "pinmux.h"

पूर्णांक pinmux_check_ops(काष्ठा pinctrl_dev *pctldev)
अणु
	स्थिर काष्ठा pinmux_ops *ops = pctldev->desc->pmxops;
	अचिन्हित nfuncs;
	अचिन्हित selector = 0;

	/* Check that we implement required operations */
	अगर (!ops ||
	    !ops->get_functions_count ||
	    !ops->get_function_name ||
	    !ops->get_function_groups ||
	    !ops->set_mux) अणु
		dev_err(pctldev->dev, "pinmux ops lacks necessary functions\n");
		वापस -EINVAL;
	पूर्ण
	/* Check that all functions रेजिस्टरed have names */
	nfuncs = ops->get_functions_count(pctldev);
	जबतक (selector < nfuncs) अणु
		स्थिर अक्षर *fname = ops->get_function_name(pctldev,
							   selector);
		अगर (!fname) अणु
			dev_err(pctldev->dev, "pinmux ops has no name for function%u\n",
				selector);
			वापस -EINVAL;
		पूर्ण
		selector++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pinmux_validate_map(स्थिर काष्ठा pinctrl_map *map, पूर्णांक i)
अणु
	अगर (!map->data.mux.function) अणु
		pr_err("failed to register map %s (%d): no function given\n",
		       map->name, i);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pinmux_can_be_used_क्रम_gpio() - check अगर a specअगरic pin
 *	is either muxed to a dअगरferent function or used as gpio.
 *
 * @pctldev: the associated pin controller device
 * @pin: the pin number in the global pin space
 *
 * Controllers not defined as strict will always वापस true,
 * menaning that the gpio can be used.
 */
bool pinmux_can_be_used_क्रम_gpio(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin)
अणु
	काष्ठा pin_desc *desc = pin_desc_get(pctldev, pin);
	स्थिर काष्ठा pinmux_ops *ops = pctldev->desc->pmxops;

	/* Can't inspect pin, assume it can be used */
	अगर (!desc || !ops)
		वापस true;

	अगर (ops->strict && desc->mux_usecount)
		वापस false;

	वापस !(ops->strict && !!desc->gpio_owner);
पूर्ण

/**
 * pin_request() - request a single pin to be muxed in, typically क्रम GPIO
 * @pctldev: the associated pin controller device
 * @pin: the pin number in the global pin space
 * @owner: a representation of the owner of this pin; typically the device
 *	name that controls its mux function, or the requested GPIO name
 * @gpio_range: the range matching the GPIO pin अगर this is a request क्रम a
 *	single GPIO pin
 */
अटल पूर्णांक pin_request(काष्ठा pinctrl_dev *pctldev,
		       पूर्णांक pin, स्थिर अक्षर *owner,
		       काष्ठा pinctrl_gpio_range *gpio_range)
अणु
	काष्ठा pin_desc *desc;
	स्थिर काष्ठा pinmux_ops *ops = pctldev->desc->pmxops;
	पूर्णांक status = -EINVAL;

	desc = pin_desc_get(pctldev, pin);
	अगर (desc == शून्य) अणु
		dev_err(pctldev->dev,
			"pin %d is not registered so it cannot be requested\n",
			pin);
		जाओ out;
	पूर्ण

	dev_dbg(pctldev->dev, "request pin %d (%s) for %s\n",
		pin, desc->name, owner);

	अगर ((!gpio_range || ops->strict) &&
	    desc->mux_usecount && म_भेद(desc->mux_owner, owner)) अणु
		dev_err(pctldev->dev,
			"pin %s already requested by %s; cannot claim for %s\n",
			desc->name, desc->mux_owner, owner);
		जाओ out;
	पूर्ण

	अगर ((gpio_range || ops->strict) && desc->gpio_owner) अणु
		dev_err(pctldev->dev,
			"pin %s already requested by %s; cannot claim for %s\n",
			desc->name, desc->gpio_owner, owner);
		जाओ out;
	पूर्ण

	अगर (gpio_range) अणु
		desc->gpio_owner = owner;
	पूर्ण अन्यथा अणु
		desc->mux_usecount++;
		अगर (desc->mux_usecount > 1)
			वापस 0;

		desc->mux_owner = owner;
	पूर्ण

	/* Let each pin increase references to this module */
	अगर (!try_module_get(pctldev->owner)) अणु
		dev_err(pctldev->dev,
			"could not increase module refcount for pin %d\n",
			pin);
		status = -EINVAL;
		जाओ out_मुक्त_pin;
	पूर्ण

	/*
	 * If there is no kind of request function क्रम the pin we just assume
	 * we got it by शेष and proceed.
	 */
	अगर (gpio_range && ops->gpio_request_enable)
		/* This requests and enables a single GPIO pin */
		status = ops->gpio_request_enable(pctldev, gpio_range, pin);
	अन्यथा अगर (ops->request)
		status = ops->request(pctldev, pin);
	अन्यथा
		status = 0;

	अगर (status) अणु
		dev_err(pctldev->dev, "request() failed for pin %d\n", pin);
		module_put(pctldev->owner);
	पूर्ण

out_मुक्त_pin:
	अगर (status) अणु
		अगर (gpio_range) अणु
			desc->gpio_owner = शून्य;
		पूर्ण अन्यथा अणु
			desc->mux_usecount--;
			अगर (!desc->mux_usecount)
				desc->mux_owner = शून्य;
		पूर्ण
	पूर्ण
out:
	अगर (status)
		dev_err(pctldev->dev, "pin-%d (%s) status %d\n",
			pin, owner, status);

	वापस status;
पूर्ण

/**
 * pin_मुक्त() - release a single muxed in pin so something अन्यथा can be muxed
 * @pctldev: pin controller device handling this pin
 * @pin: the pin to मुक्त
 * @gpio_range: the range matching the GPIO pin अगर this is a request क्रम a
 *	single GPIO pin
 *
 * This function वापसs a poपूर्णांकer to the previous owner. This is used
 * क्रम callers that dynamically allocate an owner name so it can be मुक्तd
 * once the pin is मुक्त. This is करोne क्रम GPIO request functions.
 */
अटल स्थिर अक्षर *pin_मुक्त(काष्ठा pinctrl_dev *pctldev, पूर्णांक pin,
			    काष्ठा pinctrl_gpio_range *gpio_range)
अणु
	स्थिर काष्ठा pinmux_ops *ops = pctldev->desc->pmxops;
	काष्ठा pin_desc *desc;
	स्थिर अक्षर *owner;

	desc = pin_desc_get(pctldev, pin);
	अगर (desc == शून्य) अणु
		dev_err(pctldev->dev,
			"pin is not registered so it cannot be freed\n");
		वापस शून्य;
	पूर्ण

	अगर (!gpio_range) अणु
		/*
		 * A pin should not be मुक्तd more बार than allocated.
		 */
		अगर (WARN_ON(!desc->mux_usecount))
			वापस शून्य;
		desc->mux_usecount--;
		अगर (desc->mux_usecount)
			वापस शून्य;
	पूर्ण

	/*
	 * If there is no kind of request function क्रम the pin we just assume
	 * we got it by शेष and proceed.
	 */
	अगर (gpio_range && ops->gpio_disable_मुक्त)
		ops->gpio_disable_मुक्त(pctldev, gpio_range, pin);
	अन्यथा अगर (ops->मुक्त)
		ops->मुक्त(pctldev, pin);

	अगर (gpio_range) अणु
		owner = desc->gpio_owner;
		desc->gpio_owner = शून्य;
	पूर्ण अन्यथा अणु
		owner = desc->mux_owner;
		desc->mux_owner = शून्य;
		desc->mux_setting = शून्य;
	पूर्ण

	module_put(pctldev->owner);

	वापस owner;
पूर्ण

/**
 * pinmux_request_gpio() - request pinmuxing क्रम a GPIO pin
 * @pctldev: pin controller device affected
 * @pin: the pin to mux in क्रम GPIO
 * @range: the applicable GPIO range
 * @gpio: number of requested GPIO
 */
पूर्णांक pinmux_request_gpio(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_gpio_range *range,
			अचिन्हित pin, अचिन्हित gpio)
अणु
	स्थिर अक्षर *owner;
	पूर्णांक ret;

	/* Conjure some name stating what chip and pin this is taken by */
	owner = kaप्र_लिखो(GFP_KERNEL, "%s:%d", range->name, gpio);
	अगर (!owner)
		वापस -ENOMEM;

	ret = pin_request(pctldev, pin, owner, range);
	अगर (ret < 0)
		kमुक्त(owner);

	वापस ret;
पूर्ण

/**
 * pinmux_मुक्त_gpio() - release a pin from GPIO muxing
 * @pctldev: the pin controller device क्रम the pin
 * @pin: the affected currently GPIO-muxed in pin
 * @range: applicable GPIO range
 */
व्योम pinmux_मुक्त_gpio(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
		      काष्ठा pinctrl_gpio_range *range)
अणु
	स्थिर अक्षर *owner;

	owner = pin_मुक्त(pctldev, pin, range);
	kमुक्त(owner);
पूर्ण

/**
 * pinmux_gpio_direction() - set the direction of a single muxed-in GPIO pin
 * @pctldev: the pin controller handling this pin
 * @range: applicable GPIO range
 * @pin: the affected GPIO pin in this controller
 * @input: true अगर we set the pin as input, false क्रम output
 */
पूर्णांक pinmux_gpio_direction(काष्ठा pinctrl_dev *pctldev,
			  काष्ठा pinctrl_gpio_range *range,
			  अचिन्हित pin, bool input)
अणु
	स्थिर काष्ठा pinmux_ops *ops;
	पूर्णांक ret;

	ops = pctldev->desc->pmxops;

	अगर (ops->gpio_set_direction)
		ret = ops->gpio_set_direction(pctldev, range, pin, input);
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक pinmux_func_name_to_selector(काष्ठा pinctrl_dev *pctldev,
					स्थिर अक्षर *function)
अणु
	स्थिर काष्ठा pinmux_ops *ops = pctldev->desc->pmxops;
	अचिन्हित nfuncs = ops->get_functions_count(pctldev);
	अचिन्हित selector = 0;

	/* See अगर this pctldev has this function */
	जबतक (selector < nfuncs) अणु
		स्थिर अक्षर *fname = ops->get_function_name(pctldev, selector);

		अगर (!म_भेद(function, fname))
			वापस selector;

		selector++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक pinmux_map_to_setting(स्थिर काष्ठा pinctrl_map *map,
			  काष्ठा pinctrl_setting *setting)
अणु
	काष्ठा pinctrl_dev *pctldev = setting->pctldev;
	स्थिर काष्ठा pinmux_ops *pmxops = pctldev->desc->pmxops;
	अक्षर स्थिर * स्थिर *groups;
	अचिन्हित num_groups;
	पूर्णांक ret;
	स्थिर अक्षर *group;

	अगर (!pmxops) अणु
		dev_err(pctldev->dev, "does not support mux function\n");
		वापस -EINVAL;
	पूर्ण

	ret = pinmux_func_name_to_selector(pctldev, map->data.mux.function);
	अगर (ret < 0) अणु
		dev_err(pctldev->dev, "invalid function %s in map table\n",
			map->data.mux.function);
		वापस ret;
	पूर्ण
	setting->data.mux.func = ret;

	ret = pmxops->get_function_groups(pctldev, setting->data.mux.func,
					  &groups, &num_groups);
	अगर (ret < 0) अणु
		dev_err(pctldev->dev, "can't query groups for function %s\n",
			map->data.mux.function);
		वापस ret;
	पूर्ण
	अगर (!num_groups) अणु
		dev_err(pctldev->dev,
			"function %s can't be selected on any group\n",
			map->data.mux.function);
		वापस -EINVAL;
	पूर्ण
	अगर (map->data.mux.group) अणु
		group = map->data.mux.group;
		ret = match_string(groups, num_groups, group);
		अगर (ret < 0) अणु
			dev_err(pctldev->dev,
				"invalid group \"%s\" for function \"%s\"\n",
				group, map->data.mux.function);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		group = groups[0];
	पूर्ण

	ret = pinctrl_get_group_selector(pctldev, group);
	अगर (ret < 0) अणु
		dev_err(pctldev->dev, "invalid group %s in map table\n",
			map->data.mux.group);
		वापस ret;
	पूर्ण
	setting->data.mux.group = ret;

	वापस 0;
पूर्ण

व्योम pinmux_मुक्त_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
	/* This function is currently unused */
पूर्ण

पूर्णांक pinmux_enable_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
	काष्ठा pinctrl_dev *pctldev = setting->pctldev;
	स्थिर काष्ठा pinctrl_ops *pctlops = pctldev->desc->pctlops;
	स्थिर काष्ठा pinmux_ops *ops = pctldev->desc->pmxops;
	पूर्णांक ret = 0;
	स्थिर अचिन्हित *pins = शून्य;
	अचिन्हित num_pins = 0;
	पूर्णांक i;
	काष्ठा pin_desc *desc;

	अगर (pctlops->get_group_pins)
		ret = pctlops->get_group_pins(pctldev, setting->data.mux.group,
					      &pins, &num_pins);

	अगर (ret) अणु
		स्थिर अक्षर *gname;

		/* errors only affect debug data, so just warn */
		gname = pctlops->get_group_name(pctldev,
						setting->data.mux.group);
		dev_warn(pctldev->dev,
			 "could not get pins for group %s\n",
			 gname);
		num_pins = 0;
	पूर्ण

	/* Try to allocate all pins in this group, one by one */
	क्रम (i = 0; i < num_pins; i++) अणु
		ret = pin_request(pctldev, pins[i], setting->dev_name, शून्य);
		अगर (ret) अणु
			स्थिर अक्षर *gname;
			स्थिर अक्षर *pname;

			desc = pin_desc_get(pctldev, pins[i]);
			pname = desc ? desc->name : "non-existing";
			gname = pctlops->get_group_name(pctldev,
						setting->data.mux.group);
			dev_err(pctldev->dev,
				"could not request pin %d (%s) from group %s "
				" on device %s\n",
				pins[i], pname, gname,
				pinctrl_dev_get_name(pctldev));
			जाओ err_pin_request;
		पूर्ण
	पूर्ण

	/* Now that we have acquired the pins, encode the mux setting */
	क्रम (i = 0; i < num_pins; i++) अणु
		desc = pin_desc_get(pctldev, pins[i]);
		अगर (desc == शून्य) अणु
			dev_warn(pctldev->dev,
				 "could not get pin desc for pin %d\n",
				 pins[i]);
			जारी;
		पूर्ण
		desc->mux_setting = &(setting->data.mux);
	पूर्ण

	ret = ops->set_mux(pctldev, setting->data.mux.func,
			   setting->data.mux.group);

	अगर (ret)
		जाओ err_set_mux;

	वापस 0;

err_set_mux:
	क्रम (i = 0; i < num_pins; i++) अणु
		desc = pin_desc_get(pctldev, pins[i]);
		अगर (desc)
			desc->mux_setting = शून्य;
	पूर्ण
err_pin_request:
	/* On error release all taken pins */
	जबतक (--i >= 0)
		pin_मुक्त(pctldev, pins[i], शून्य);

	वापस ret;
पूर्ण

व्योम pinmux_disable_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
	काष्ठा pinctrl_dev *pctldev = setting->pctldev;
	स्थिर काष्ठा pinctrl_ops *pctlops = pctldev->desc->pctlops;
	पूर्णांक ret = 0;
	स्थिर अचिन्हित *pins = शून्य;
	अचिन्हित num_pins = 0;
	पूर्णांक i;
	काष्ठा pin_desc *desc;

	अगर (pctlops->get_group_pins)
		ret = pctlops->get_group_pins(pctldev, setting->data.mux.group,
					      &pins, &num_pins);
	अगर (ret) अणु
		स्थिर अक्षर *gname;

		/* errors only affect debug data, so just warn */
		gname = pctlops->get_group_name(pctldev,
						setting->data.mux.group);
		dev_warn(pctldev->dev,
			 "could not get pins for group %s\n",
			 gname);
		num_pins = 0;
	पूर्ण

	/* Flag the descs that no setting is active */
	क्रम (i = 0; i < num_pins; i++) अणु
		desc = pin_desc_get(pctldev, pins[i]);
		अगर (desc == शून्य) अणु
			dev_warn(pctldev->dev,
				 "could not get pin desc for pin %d\n",
				 pins[i]);
			जारी;
		पूर्ण
		अगर (desc->mux_setting == &(setting->data.mux)) अणु
			pin_मुक्त(pctldev, pins[i], शून्य);
		पूर्ण अन्यथा अणु
			स्थिर अक्षर *gname;

			gname = pctlops->get_group_name(pctldev,
						setting->data.mux.group);
			dev_warn(pctldev->dev,
				 "not freeing pin %d (%s) as part of "
				 "deactivating group %s - it is already "
				 "used for some other setting",
				 pins[i], desc->name, gname);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

/* Called from pincontrol core */
अटल पूर्णांक pinmux_functions_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_dev *pctldev = s->निजी;
	स्थिर काष्ठा pinmux_ops *pmxops = pctldev->desc->pmxops;
	अचिन्हित nfuncs;
	अचिन्हित func_selector = 0;

	अगर (!pmxops)
		वापस 0;

	mutex_lock(&pctldev->mutex);
	nfuncs = pmxops->get_functions_count(pctldev);
	जबतक (func_selector < nfuncs) अणु
		स्थिर अक्षर *func = pmxops->get_function_name(pctldev,
							  func_selector);
		स्थिर अक्षर * स्थिर *groups;
		अचिन्हित num_groups;
		पूर्णांक ret;
		पूर्णांक i;

		ret = pmxops->get_function_groups(pctldev, func_selector,
						  &groups, &num_groups);
		अगर (ret) अणु
			seq_म_लिखो(s, "function %s: COULD NOT GET GROUPS\n",
				   func);
			func_selector++;
			जारी;
		पूर्ण

		seq_म_लिखो(s, "function %d: %s, groups = [ ", func_selector, func);
		क्रम (i = 0; i < num_groups; i++)
			seq_म_लिखो(s, "%s ", groups[i]);
		seq_माला_दो(s, "]\n");

		func_selector++;
	पूर्ण

	mutex_unlock(&pctldev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pinmux_pins_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_dev *pctldev = s->निजी;
	स्थिर काष्ठा pinctrl_ops *pctlops = pctldev->desc->pctlops;
	स्थिर काष्ठा pinmux_ops *pmxops = pctldev->desc->pmxops;
	अचिन्हित i, pin;

	अगर (!pmxops)
		वापस 0;

	seq_माला_दो(s, "Pinmux settings per pin\n");
	अगर (pmxops->strict)
		seq_माला_दो(s,
		 "Format: pin (name): mux_owner|gpio_owner (strict) hog?\n");
	अन्यथा
		seq_माला_दो(s,
		"Format: pin (name): mux_owner gpio_owner hog?\n");

	mutex_lock(&pctldev->mutex);

	/* The pin number can be retrived from the pin controller descriptor */
	क्रम (i = 0; i < pctldev->desc->npins; i++) अणु
		काष्ठा pin_desc *desc;
		bool is_hog = false;

		pin = pctldev->desc->pins[i].number;
		desc = pin_desc_get(pctldev, pin);
		/* Skip अगर we cannot search the pin */
		अगर (desc == शून्य)
			जारी;

		अगर (desc->mux_owner &&
		    !म_भेद(desc->mux_owner, pinctrl_dev_get_name(pctldev)))
			is_hog = true;

		अगर (pmxops->strict) अणु
			अगर (desc->mux_owner)
				seq_म_लिखो(s, "pin %d (%s): device %s%s",
					   pin, desc->name, desc->mux_owner,
					   is_hog ? " (HOG)" : "");
			अन्यथा अगर (desc->gpio_owner)
				seq_म_लिखो(s, "pin %d (%s): GPIO %s",
					   pin, desc->name, desc->gpio_owner);
			अन्यथा
				seq_म_लिखो(s, "pin %d (%s): UNCLAIMED",
					   pin, desc->name);
		पूर्ण अन्यथा अणु
			/* For non-strict controllers */
			seq_म_लिखो(s, "pin %d (%s): %s %s%s", pin, desc->name,
				   desc->mux_owner ? desc->mux_owner
				   : "(MUX UNCLAIMED)",
				   desc->gpio_owner ? desc->gpio_owner
				   : "(GPIO UNCLAIMED)",
				   is_hog ? " (HOG)" : "");
		पूर्ण

		/* If mux: prपूर्णांक function+group claiming the pin */
		अगर (desc->mux_setting)
			seq_म_लिखो(s, " function %s group %s\n",
				   pmxops->get_function_name(pctldev,
					desc->mux_setting->func),
				   pctlops->get_group_name(pctldev,
					desc->mux_setting->group));
		अन्यथा
			seq_अ_दो(s, '\n');
	पूर्ण

	mutex_unlock(&pctldev->mutex);

	वापस 0;
पूर्ण

व्योम pinmux_show_map(काष्ठा seq_file *s, स्थिर काष्ठा pinctrl_map *map)
अणु
	seq_म_लिखो(s, "group %s\nfunction %s\n",
		map->data.mux.group ? map->data.mux.group : "(default)",
		map->data.mux.function);
पूर्ण

व्योम pinmux_show_setting(काष्ठा seq_file *s,
			 स्थिर काष्ठा pinctrl_setting *setting)
अणु
	काष्ठा pinctrl_dev *pctldev = setting->pctldev;
	स्थिर काष्ठा pinmux_ops *pmxops = pctldev->desc->pmxops;
	स्थिर काष्ठा pinctrl_ops *pctlops = pctldev->desc->pctlops;

	seq_म_लिखो(s, "group: %s (%u) function: %s (%u)\n",
		   pctlops->get_group_name(pctldev, setting->data.mux.group),
		   setting->data.mux.group,
		   pmxops->get_function_name(pctldev, setting->data.mux.func),
		   setting->data.mux.func);
पूर्ण

DEFINE_SHOW_ATTRIBUTE(pinmux_functions);
DEFINE_SHOW_ATTRIBUTE(pinmux_pins);

#घोषणा PINMUX_SELECT_MAX 128
अटल sमाप_प्रकार pinmux_select(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				   माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा seq_file *sfile = file->निजी_data;
	काष्ठा pinctrl_dev *pctldev = sfile->निजी;
	स्थिर काष्ठा pinmux_ops *pmxops = pctldev->desc->pmxops;
	स्थिर अक्षर *स्थिर *groups;
	अक्षर *buf, *gname, *fname;
	अचिन्हित पूर्णांक num_groups;
	पूर्णांक fsel, gsel, ret;

	अगर (len > PINMUX_SELECT_MAX)
		वापस -ENOMEM;

	buf = kzalloc(PINMUX_SELECT_MAX, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = म_नकलन_from_user(buf, user_buf, PINMUX_SELECT_MAX);
	अगर (ret < 0)
		जाओ निकास_मुक्त_buf;
	buf[len-1] = '\0';

	/* हटाओ leading and trailing spaces of input buffer */
	gname = म_मालाip(buf);
	अगर (*gname == '\0') अणु
		ret = -EINVAL;
		जाओ निकास_मुक्त_buf;
	पूर्ण

	/* find a separator which is a spacelike अक्षरacter */
	क्रम (fname = gname; !है_खाली(*fname); fname++) अणु
		अगर (*fname == '\0') अणु
			ret = -EINVAL;
			जाओ निकास_मुक्त_buf;
		पूर्ण
	पूर्ण
	*fname = '\0';

	/* drop extra spaces between function and group names */
	fname = skip_spaces(fname + 1);
	अगर (*fname == '\0') अणु
		ret = -EINVAL;
		जाओ निकास_मुक्त_buf;
	पूर्ण

	ret = pinmux_func_name_to_selector(pctldev, fname);
	अगर (ret < 0) अणु
		dev_err(pctldev->dev, "invalid function %s in map table\n", fname);
		जाओ निकास_मुक्त_buf;
	पूर्ण
	fsel = ret;

	ret = pmxops->get_function_groups(pctldev, fsel, &groups, &num_groups);
	अगर (ret) अणु
		dev_err(pctldev->dev, "no groups for function %d (%s)", fsel, fname);
		जाओ निकास_मुक्त_buf;
	पूर्ण

	ret = match_string(groups, num_groups, gname);
	अगर (ret < 0) अणु
		dev_err(pctldev->dev, "invalid group %s", gname);
		जाओ निकास_मुक्त_buf;
	पूर्ण

	ret = pinctrl_get_group_selector(pctldev, gname);
	अगर (ret < 0) अणु
		dev_err(pctldev->dev, "failed to get group selector for %s", gname);
		जाओ निकास_मुक्त_buf;
	पूर्ण
	gsel = ret;

	ret = pmxops->set_mux(pctldev, fsel, gsel);
	अगर (ret) अणु
		dev_err(pctldev->dev, "set_mux() failed: %d", ret);
		जाओ निकास_मुक्त_buf;
	पूर्ण
	ret = len;

निकास_मुक्त_buf:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक pinmux_select_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, शून्य, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations pinmux_select_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = pinmux_select_खोलो,
	.ग_लिखो = pinmux_select,
	.llseek = no_llseek,
	.release = single_release,
पूर्ण;

व्योम pinmux_init_device_debugfs(काष्ठा dentry *devroot,
			 काष्ठा pinctrl_dev *pctldev)
अणु
	debugfs_create_file("pinmux-functions", 0444,
			    devroot, pctldev, &pinmux_functions_fops);
	debugfs_create_file("pinmux-pins", 0444,
			    devroot, pctldev, &pinmux_pins_fops);
	debugfs_create_file("pinmux-select", 0200,
			    devroot, pctldev, &pinmux_select_ops);
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#अगर_घोषित CONFIG_GENERIC_PINMUX_FUNCTIONS

/**
 * pinmux_generic_get_function_count() - वापसs number of functions
 * @pctldev: pin controller device
 */
पूर्णांक pinmux_generic_get_function_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस pctldev->num_functions;
पूर्ण
EXPORT_SYMBOL_GPL(pinmux_generic_get_function_count);

/**
 * pinmux_generic_get_function_name() - वापसs the function name
 * @pctldev: pin controller device
 * @selector: function number
 */
स्थिर अक्षर *
pinmux_generic_get_function_name(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा function_desc *function;

	function = radix_tree_lookup(&pctldev->pin_function_tree,
				     selector);
	अगर (!function)
		वापस शून्य;

	वापस function->name;
पूर्ण
EXPORT_SYMBOL_GPL(pinmux_generic_get_function_name);

/**
 * pinmux_generic_get_function_groups() - माला_लो the function groups
 * @pctldev: pin controller device
 * @selector: function number
 * @groups: array of pin groups
 * @num_groups: number of pin groups
 */
पूर्णांक pinmux_generic_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक selector,
				       स्थिर अक्षर * स्थिर **groups,
				       अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा function_desc *function;

	function = radix_tree_lookup(&pctldev->pin_function_tree,
				     selector);
	अगर (!function) अणु
		dev_err(pctldev->dev, "%s could not find function%i\n",
			__func__, selector);
		वापस -EINVAL;
	पूर्ण
	*groups = function->group_names;
	*num_groups = function->num_group_names;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinmux_generic_get_function_groups);

/**
 * pinmux_generic_get_function() - वापसs a function based on the number
 * @pctldev: pin controller device
 * @selector: function number
 */
काष्ठा function_desc *pinmux_generic_get_function(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित पूर्णांक selector)
अणु
	काष्ठा function_desc *function;

	function = radix_tree_lookup(&pctldev->pin_function_tree,
				     selector);
	अगर (!function)
		वापस शून्य;

	वापस function;
पूर्ण
EXPORT_SYMBOL_GPL(pinmux_generic_get_function);

/**
 * pinmux_generic_add_function() - adds a function group
 * @pctldev: pin controller device
 * @name: name of the function
 * @groups: array of pin groups
 * @num_groups: number of pin groups
 * @data: pin controller driver specअगरic data
 */
पूर्णांक pinmux_generic_add_function(काष्ठा pinctrl_dev *pctldev,
				स्थिर अक्षर *name,
				स्थिर अक्षर **groups,
				स्थिर अचिन्हित पूर्णांक num_groups,
				व्योम *data)
अणु
	काष्ठा function_desc *function;
	पूर्णांक selector;

	अगर (!name)
		वापस -EINVAL;

	selector = pinmux_func_name_to_selector(pctldev, name);
	अगर (selector >= 0)
		वापस selector;

	selector = pctldev->num_functions;

	function = devm_kzalloc(pctldev->dev, माप(*function), GFP_KERNEL);
	अगर (!function)
		वापस -ENOMEM;

	function->name = name;
	function->group_names = groups;
	function->num_group_names = num_groups;
	function->data = data;

	radix_tree_insert(&pctldev->pin_function_tree, selector, function);

	pctldev->num_functions++;

	वापस selector;
पूर्ण
EXPORT_SYMBOL_GPL(pinmux_generic_add_function);

/**
 * pinmux_generic_हटाओ_function() - हटाओs a numbered function
 * @pctldev: pin controller device
 * @selector: function number
 *
 * Note that the caller must take care of locking.
 */
पूर्णांक pinmux_generic_हटाओ_function(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक selector)
अणु
	काष्ठा function_desc *function;

	function = radix_tree_lookup(&pctldev->pin_function_tree,
				     selector);
	अगर (!function)
		वापस -ENOENT;

	radix_tree_delete(&pctldev->pin_function_tree, selector);
	devm_kमुक्त(pctldev->dev, function);

	pctldev->num_functions--;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinmux_generic_हटाओ_function);

/**
 * pinmux_generic_मुक्त_functions() - हटाओs all functions
 * @pctldev: pin controller device
 *
 * Note that the caller must take care of locking. The pinctrl
 * functions are allocated with devm_kzalloc() so no need to मुक्त
 * them here.
 */
व्योम pinmux_generic_मुक्त_functions(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;

	radix_tree_क्रम_each_slot(slot, &pctldev->pin_function_tree, &iter, 0)
		radix_tree_delete(&pctldev->pin_function_tree, iter.index);

	pctldev->num_functions = 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_GENERIC_PINMUX_FUNCTIONS */
