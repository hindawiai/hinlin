<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-ac97.c  --  ALSA SoC Audio Layer AC97 support
//
// Copyright 2005 Wolfson Microelectronics PLC.
// Copyright 2005 Openedhand Ltd.
// Copyright (C) 2010 Slimlogic Ltd.
// Copyright (C) 2010 Texas Instruments Inc.
//
// Author: Liam Girdwood <lrg@slimlogic.co.uk>
//         with code, comments and ideas from :-
//         Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>

#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/soc.h>

काष्ठा snd_ac97_reset_cfg अणु
	काष्ठा pinctrl *pctl;
	काष्ठा pinctrl_state *pstate_reset;
	काष्ठा pinctrl_state *pstate_warm_reset;
	काष्ठा pinctrl_state *pstate_run;
	पूर्णांक gpio_sdata;
	पूर्णांक gpio_sync;
	पूर्णांक gpio_reset;
पूर्ण;

काष्ठा snd_ac97_gpio_priv अणु
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio_chip;
#पूर्ण_अगर
	अचिन्हित पूर्णांक gpios_set;
	काष्ठा snd_soc_component *component;
पूर्ण;

अटल काष्ठा snd_ac97_bus soc_ac97_bus = अणु
	.ops = शून्य, /* Gets initialized in snd_soc_set_ac97_ops() */
पूर्ण;

अटल व्योम soc_ac97_device_release(काष्ठा device *dev)
अणु
	kमुक्त(to_ac97_t(dev));
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल अंतरभूत काष्ठा snd_soc_component *gpio_to_component(काष्ठा gpio_chip *chip)
अणु
	काष्ठा snd_ac97_gpio_priv *gpio_priv = gpiochip_get_data(chip);

	वापस gpio_priv->component;
पूर्ण

अटल पूर्णांक snd_soc_ac97_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अगर (offset >= AC97_NUM_GPIOS)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_soc_ac97_gpio_direction_in(काष्ठा gpio_chip *chip,
					  अचिन्हित offset)
अणु
	काष्ठा snd_soc_component *component = gpio_to_component(chip);

	dev_dbg(component->dev, "set gpio %d to output\n", offset);
	वापस snd_soc_component_update_bits(component, AC97_GPIO_CFG,
				   1 << offset, 1 << offset);
पूर्ण

अटल पूर्णांक snd_soc_ac97_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा snd_soc_component *component = gpio_to_component(chip);
	पूर्णांक ret;

	ret = snd_soc_component_पढ़ो(component, AC97_GPIO_STATUS);

	dev_dbg(component->dev, "get gpio %d : %d\n", offset,
		ret & (1 << offset));

	वापस !!(ret & (1 << offset));
पूर्ण

अटल व्योम snd_soc_ac97_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset,
				  पूर्णांक value)
अणु
	काष्ठा snd_ac97_gpio_priv *gpio_priv = gpiochip_get_data(chip);
	काष्ठा snd_soc_component *component = gpio_to_component(chip);

	gpio_priv->gpios_set &= ~(1 << offset);
	gpio_priv->gpios_set |= (!!value) << offset;
	snd_soc_component_ग_लिखो(component, AC97_GPIO_STATUS,
				gpio_priv->gpios_set);
	dev_dbg(component->dev, "set gpio %d to %d\n", offset, !!value);
पूर्ण

अटल पूर्णांक snd_soc_ac97_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा snd_soc_component *component = gpio_to_component(chip);

	dev_dbg(component->dev, "set gpio %d to output\n", offset);
	snd_soc_ac97_gpio_set(chip, offset, value);
	वापस snd_soc_component_update_bits(component, AC97_GPIO_CFG,
					     1 << offset, 0);
पूर्ण

अटल स्थिर काष्ठा gpio_chip snd_soc_ac97_gpio_chip = अणु
	.label			= "snd_soc_ac97",
	.owner			= THIS_MODULE,
	.request		= snd_soc_ac97_gpio_request,
	.direction_input	= snd_soc_ac97_gpio_direction_in,
	.get			= snd_soc_ac97_gpio_get,
	.direction_output	= snd_soc_ac97_gpio_direction_out,
	.set			= snd_soc_ac97_gpio_set,
	.can_sleep		= 1,
पूर्ण;

अटल पूर्णांक snd_soc_ac97_init_gpio(काष्ठा snd_ac97 *ac97,
				  काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97_gpio_priv *gpio_priv;
	पूर्णांक ret;

	gpio_priv = devm_kzalloc(component->dev, माप(*gpio_priv), GFP_KERNEL);
	अगर (!gpio_priv)
		वापस -ENOMEM;
	ac97->gpio_priv = gpio_priv;
	gpio_priv->component = component;
	gpio_priv->gpio_chip = snd_soc_ac97_gpio_chip;
	gpio_priv->gpio_chip.ngpio = AC97_NUM_GPIOS;
	gpio_priv->gpio_chip.parent = component->dev;
	gpio_priv->gpio_chip.base = -1;

	ret = gpiochip_add_data(&gpio_priv->gpio_chip, gpio_priv);
	अगर (ret != 0)
		dev_err(component->dev, "Failed to add GPIOs: %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम snd_soc_ac97_मुक्त_gpio(काष्ठा snd_ac97 *ac97)
अणु
	gpiochip_हटाओ(&ac97->gpio_priv->gpio_chip);
पूर्ण
#अन्यथा
अटल पूर्णांक snd_soc_ac97_init_gpio(काष्ठा snd_ac97 *ac97,
				  काष्ठा snd_soc_component *component)
अणु
	वापस 0;
पूर्ण

अटल व्योम snd_soc_ac97_मुक्त_gpio(काष्ठा snd_ac97 *ac97)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * snd_soc_alloc_ac97_component() - Allocate new a AC'97 device
 * @component: The COMPONENT क्रम which to create the AC'97 device
 *
 * Allocated a new snd_ac97 device and पूर्णांकializes it, but करोes not yet रेजिस्टर
 * it. The caller is responsible to either call device_add(&ac97->dev) to
 * रेजिस्टर the device, or to call put_device(&ac97->dev) to मुक्त the device.
 *
 * Returns: A snd_ac97 device or a PTR_ERR in हाल of an error.
 */
काष्ठा snd_ac97 *snd_soc_alloc_ac97_component(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97 *ac97;

	ac97 = kzalloc(माप(काष्ठा snd_ac97), GFP_KERNEL);
	अगर (ac97 == शून्य)
		वापस ERR_PTR(-ENOMEM);

	ac97->bus = &soc_ac97_bus;
	ac97->num = 0;

	ac97->dev.bus = &ac97_bus_type;
	ac97->dev.parent = component->card->dev;
	ac97->dev.release = soc_ac97_device_release;

	dev_set_name(&ac97->dev, "%d-%d:%s",
		     component->card->snd_card->number, 0,
		     component->name);

	device_initialize(&ac97->dev);

	वापस ac97;
पूर्ण
EXPORT_SYMBOL(snd_soc_alloc_ac97_component);

/**
 * snd_soc_new_ac97_component - initailise AC97 device
 * @component: audio component
 * @id: The expected device ID
 * @id_mask: Mask that is applied to the device ID beक्रमe comparing with @id
 *
 * Initialises AC97 component resources क्रम use by ad-hoc devices only.
 *
 * If @id is not 0 this function will reset the device, then पढ़ो the ID from
 * the device and check अगर it matches the expected ID. If it करोesn't match an
 * error will be वापसed and device will not be रेजिस्टरed.
 *
 * Returns: A PTR_ERR() on failure or a valid snd_ac97 काष्ठा on success.
 */
काष्ठा snd_ac97 *snd_soc_new_ac97_component(काष्ठा snd_soc_component *component,
	अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक id_mask)
अणु
	काष्ठा snd_ac97 *ac97;
	पूर्णांक ret;

	ac97 = snd_soc_alloc_ac97_component(component);
	अगर (IS_ERR(ac97))
		वापस ac97;

	अगर (id) अणु
		ret = snd_ac97_reset(ac97, false, id, id_mask);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to reset AC97 device: %d\n",
				ret);
			जाओ err_put_device;
		पूर्ण
	पूर्ण

	ret = device_add(&ac97->dev);
	अगर (ret)
		जाओ err_put_device;

	ret = snd_soc_ac97_init_gpio(ac97, component);
	अगर (ret)
		जाओ err_put_device;

	वापस ac97;

err_put_device:
	put_device(&ac97->dev);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_new_ac97_component);

/**
 * snd_soc_मुक्त_ac97_component - मुक्त AC97 component device
 * @ac97: snd_ac97 device to be मुक्तd
 *
 * Frees AC97 component device resources.
 */
व्योम snd_soc_मुक्त_ac97_component(काष्ठा snd_ac97 *ac97)
अणु
	snd_soc_ac97_मुक्त_gpio(ac97);
	device_del(&ac97->dev);
	ac97->bus = शून्य;
	put_device(&ac97->dev);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_मुक्त_ac97_component);

अटल काष्ठा snd_ac97_reset_cfg snd_ac97_rst_cfg;

अटल व्योम snd_soc_ac97_warm_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा pinctrl *pctl = snd_ac97_rst_cfg.pctl;

	pinctrl_select_state(pctl, snd_ac97_rst_cfg.pstate_warm_reset);

	gpio_direction_output(snd_ac97_rst_cfg.gpio_sync, 1);

	udelay(10);

	gpio_direction_output(snd_ac97_rst_cfg.gpio_sync, 0);

	pinctrl_select_state(pctl, snd_ac97_rst_cfg.pstate_run);
	msleep(2);
पूर्ण

अटल व्योम snd_soc_ac97_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा pinctrl *pctl = snd_ac97_rst_cfg.pctl;

	pinctrl_select_state(pctl, snd_ac97_rst_cfg.pstate_reset);

	gpio_direction_output(snd_ac97_rst_cfg.gpio_sync, 0);
	gpio_direction_output(snd_ac97_rst_cfg.gpio_sdata, 0);
	gpio_direction_output(snd_ac97_rst_cfg.gpio_reset, 0);

	udelay(10);

	gpio_direction_output(snd_ac97_rst_cfg.gpio_reset, 1);

	pinctrl_select_state(pctl, snd_ac97_rst_cfg.pstate_run);
	msleep(2);
पूर्ण

अटल पूर्णांक snd_soc_ac97_parse_pinctl(काष्ठा device *dev,
		काष्ठा snd_ac97_reset_cfg *cfg)
अणु
	काष्ठा pinctrl *p;
	काष्ठा pinctrl_state *state;
	पूर्णांक gpio;
	पूर्णांक ret;

	p = devm_pinctrl_get(dev);
	अगर (IS_ERR(p)) अणु
		dev_err(dev, "Failed to get pinctrl\n");
		वापस PTR_ERR(p);
	पूर्ण
	cfg->pctl = p;

	state = pinctrl_lookup_state(p, "ac97-reset");
	अगर (IS_ERR(state)) अणु
		dev_err(dev, "Can't find pinctrl state ac97-reset\n");
		वापस PTR_ERR(state);
	पूर्ण
	cfg->pstate_reset = state;

	state = pinctrl_lookup_state(p, "ac97-warm-reset");
	अगर (IS_ERR(state)) अणु
		dev_err(dev, "Can't find pinctrl state ac97-warm-reset\n");
		वापस PTR_ERR(state);
	पूर्ण
	cfg->pstate_warm_reset = state;

	state = pinctrl_lookup_state(p, "ac97-running");
	अगर (IS_ERR(state)) अणु
		dev_err(dev, "Can't find pinctrl state ac97-running\n");
		वापस PTR_ERR(state);
	पूर्ण
	cfg->pstate_run = state;

	gpio = of_get_named_gpio(dev->of_node, "ac97-gpios", 0);
	अगर (gpio < 0) अणु
		dev_err(dev, "Can't find ac97-sync gpio\n");
		वापस gpio;
	पूर्ण
	ret = devm_gpio_request(dev, gpio, "AC97 link sync");
	अगर (ret) अणु
		dev_err(dev, "Failed requesting ac97-sync gpio\n");
		वापस ret;
	पूर्ण
	cfg->gpio_sync = gpio;

	gpio = of_get_named_gpio(dev->of_node, "ac97-gpios", 1);
	अगर (gpio < 0) अणु
		dev_err(dev, "Can't find ac97-sdata gpio %d\n", gpio);
		वापस gpio;
	पूर्ण
	ret = devm_gpio_request(dev, gpio, "AC97 link sdata");
	अगर (ret) अणु
		dev_err(dev, "Failed requesting ac97-sdata gpio\n");
		वापस ret;
	पूर्ण
	cfg->gpio_sdata = gpio;

	gpio = of_get_named_gpio(dev->of_node, "ac97-gpios", 2);
	अगर (gpio < 0) अणु
		dev_err(dev, "Can't find ac97-reset gpio\n");
		वापस gpio;
	पूर्ण
	ret = devm_gpio_request(dev, gpio, "AC97 link reset");
	अगर (ret) अणु
		dev_err(dev, "Failed requesting ac97-reset gpio\n");
		वापस ret;
	पूर्ण
	cfg->gpio_reset = gpio;

	वापस 0;
पूर्ण

काष्ठा snd_ac97_bus_ops *soc_ac97_ops;
EXPORT_SYMBOL_GPL(soc_ac97_ops);

पूर्णांक snd_soc_set_ac97_ops(काष्ठा snd_ac97_bus_ops *ops)
अणु
	अगर (ops == soc_ac97_ops)
		वापस 0;

	अगर (soc_ac97_ops && ops)
		वापस -EBUSY;

	soc_ac97_ops = ops;
	soc_ac97_bus.ops = ops;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_set_ac97_ops);

/**
 * snd_soc_set_ac97_ops_of_reset - Set ac97 ops with generic ac97 reset functions
 * @ops: bus ops
 * @pdev: platक्रमm device
 *
 * This function sets the reset and warm_reset properties of ops and parses
 * the device node of pdev to get pinctrl states and gpio numbers to use.
 */
पूर्णांक snd_soc_set_ac97_ops_of_reset(काष्ठा snd_ac97_bus_ops *ops,
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_ac97_reset_cfg cfg;
	पूर्णांक ret;

	ret = snd_soc_ac97_parse_pinctl(dev, &cfg);
	अगर (ret)
		वापस ret;

	ret = snd_soc_set_ac97_ops(ops);
	अगर (ret)
		वापस ret;

	ops->warm_reset = snd_soc_ac97_warm_reset;
	ops->reset = snd_soc_ac97_reset;

	snd_ac97_rst_cfg = cfg;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_set_ac97_ops_of_reset);
