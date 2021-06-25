<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver core पूर्णांकerface to the pinctrl subप्रणाली.
 *
 * Copyright (C) 2012 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * Based on bits of regulator core, gpio core and clk core
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/pinctrl/devinfo.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/slab.h>

/**
 * pinctrl_bind_pins() - called by the device core beक्रमe probe
 * @dev: the device that is just about to probe
 */
पूर्णांक pinctrl_bind_pins(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (dev->of_node_reused)
		वापस 0;

	dev->pins = devm_kzalloc(dev, माप(*(dev->pins)), GFP_KERNEL);
	अगर (!dev->pins)
		वापस -ENOMEM;

	dev->pins->p = devm_pinctrl_get(dev);
	अगर (IS_ERR(dev->pins->p)) अणु
		dev_dbg(dev, "no pinctrl handle\n");
		ret = PTR_ERR(dev->pins->p);
		जाओ cleanup_alloc;
	पूर्ण

	dev->pins->शेष_state = pinctrl_lookup_state(dev->pins->p,
					PINCTRL_STATE_DEFAULT);
	अगर (IS_ERR(dev->pins->शेष_state)) अणु
		dev_dbg(dev, "no default pinctrl state\n");
		ret = 0;
		जाओ cleanup_get;
	पूर्ण

	dev->pins->init_state = pinctrl_lookup_state(dev->pins->p,
					PINCTRL_STATE_INIT);
	अगर (IS_ERR(dev->pins->init_state)) अणु
		/* Not supplying this state is perfectly legal */
		dev_dbg(dev, "no init pinctrl state\n");

		ret = pinctrl_select_state(dev->pins->p,
					   dev->pins->शेष_state);
	पूर्ण अन्यथा अणु
		ret = pinctrl_select_state(dev->pins->p, dev->pins->init_state);
	पूर्ण

	अगर (ret) अणु
		dev_dbg(dev, "failed to activate initial pinctrl state\n");
		जाओ cleanup_get;
	पूर्ण

#अगर_घोषित CONFIG_PM
	/*
	 * If घातer management is enabled, we also look क्रम the optional
	 * sleep and idle pin states, with semantics as defined in
	 * <linux/pinctrl/pinctrl-state.h>
	 */
	dev->pins->sleep_state = pinctrl_lookup_state(dev->pins->p,
					PINCTRL_STATE_SLEEP);
	अगर (IS_ERR(dev->pins->sleep_state))
		/* Not supplying this state is perfectly legal */
		dev_dbg(dev, "no sleep pinctrl state\n");

	dev->pins->idle_state = pinctrl_lookup_state(dev->pins->p,
					PINCTRL_STATE_IDLE);
	अगर (IS_ERR(dev->pins->idle_state))
		/* Not supplying this state is perfectly legal */
		dev_dbg(dev, "no idle pinctrl state\n");
#पूर्ण_अगर

	वापस 0;

	/*
	 * If no pinctrl handle or शेष state was found क्रम this device,
	 * let's explicitly मुक्त the pin container in the device, there is
	 * no poपूर्णांक in keeping it around.
	 */
cleanup_get:
	devm_pinctrl_put(dev->pins->p);
cleanup_alloc:
	devm_kमुक्त(dev, dev->pins);
	dev->pins = शून्य;

	/* Return deferrals */
	अगर (ret == -EPROBE_DEFER)
		वापस ret;
	/* Return serious errors */
	अगर (ret == -EINVAL)
		वापस ret;
	/* We ignore errors like -ENOENT meaning no pinctrl state */

	वापस 0;
पूर्ण
