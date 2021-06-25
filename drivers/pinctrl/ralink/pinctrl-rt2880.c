<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2013 John Crispin <blogic@खोलोwrt.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>

#समावेश <यंत्र/mach-ralink/ralink_regs.h>
#समावेश <यंत्र/mach-ralink/pinmux.h>
#समावेश <यंत्र/mach-ralink/mt7620.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

#घोषणा SYSC_REG_GPIO_MODE	0x60
#घोषणा SYSC_REG_GPIO_MODE2	0x64

काष्ठा rt2880_priv अणु
	काष्ठा device *dev;

	काष्ठा pinctrl_pin_desc *pads;
	काष्ठा pinctrl_desc *desc;

	काष्ठा rt2880_pmx_func **func;
	पूर्णांक func_count;

	काष्ठा rt2880_pmx_group *groups;
	स्थिर अक्षर **group_names;
	पूर्णांक group_count;

	u8 *gpio;
	पूर्णांक max_pins;
पूर्ण;

अटल पूर्णांक rt2880_get_group_count(काष्ठा pinctrl_dev *pctrldev)
अणु
	काष्ठा rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	वापस p->group_count;
पूर्ण

अटल स्थिर अक्षर *rt2880_get_group_name(काष्ठा pinctrl_dev *pctrldev,
					 अचिन्हित पूर्णांक group)
अणु
	काष्ठा rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	वापस (group >= p->group_count) ? शून्य : p->group_names[group];
पूर्ण

अटल पूर्णांक rt2880_get_group_pins(काष्ठा pinctrl_dev *pctrldev,
				 अचिन्हित पूर्णांक group,
				 स्थिर अचिन्हित पूर्णांक **pins,
				 अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	अगर (group >= p->group_count)
		वापस -EINVAL;

	*pins = p->groups[group].func[0].pins;
	*num_pins = p->groups[group].func[0].pin_count;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops rt2880_pctrl_ops = अणु
	.get_groups_count	= rt2880_get_group_count,
	.get_group_name		= rt2880_get_group_name,
	.get_group_pins		= rt2880_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map		= pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक rt2880_pmx_func_count(काष्ठा pinctrl_dev *pctrldev)
अणु
	काष्ठा rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	वापस p->func_count;
पूर्ण

अटल स्थिर अक्षर *rt2880_pmx_func_name(काष्ठा pinctrl_dev *pctrldev,
					अचिन्हित पूर्णांक func)
अणु
	काष्ठा rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	वापस p->func[func]->name;
पूर्ण

अटल पूर्णांक rt2880_pmx_group_get_groups(काष्ठा pinctrl_dev *pctrldev,
				       अचिन्हित पूर्णांक func,
				       स्थिर अक्षर * स्थिर **groups,
				       अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	अगर (p->func[func]->group_count == 1)
		*groups = &p->group_names[p->func[func]->groups[0]];
	अन्यथा
		*groups = p->group_names;

	*num_groups = p->func[func]->group_count;

	वापस 0;
पूर्ण

अटल पूर्णांक rt2880_pmx_group_enable(काष्ठा pinctrl_dev *pctrldev,
				   अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक group)
अणु
	काष्ठा rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);
	u32 mode = 0;
	u32 reg = SYSC_REG_GPIO_MODE;
	पूर्णांक i;
	पूर्णांक shअगरt;

	/* करोnt allow द्विगुन use */
	अगर (p->groups[group].enabled) अणु
		dev_err(p->dev, "%s is already enabled\n",
			p->groups[group].name);
		वापस 0;
	पूर्ण

	p->groups[group].enabled = 1;
	p->func[func]->enabled = 1;

	shअगरt = p->groups[group].shअगरt;
	अगर (shअगरt >= 32) अणु
		shअगरt -= 32;
		reg = SYSC_REG_GPIO_MODE2;
	पूर्ण
	mode = rt_sysc_r32(reg);
	mode &= ~(p->groups[group].mask << shअगरt);

	/* mark the pins as gpio */
	क्रम (i = 0; i < p->groups[group].func[0].pin_count; i++)
		p->gpio[p->groups[group].func[0].pins[i]] = 1;

	/* function 0 is gpio and needs special handling */
	अगर (func == 0) अणु
		mode |= p->groups[group].gpio << shअगरt;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < p->func[func]->pin_count; i++)
			p->gpio[p->func[func]->pins[i]] = 0;
		mode |= p->func[func]->value << shअगरt;
	पूर्ण
	rt_sysc_w32(mode, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2880_pmx_group_gpio_request_enable(काष्ठा pinctrl_dev *pctrldev,
						काष्ठा pinctrl_gpio_range *range,
						अचिन्हित पूर्णांक pin)
अणु
	काष्ठा rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	अगर (!p->gpio[pin]) अणु
		dev_err(p->dev, "pin %d is not set to gpio mux\n", pin);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops rt2880_pmx_group_ops = अणु
	.get_functions_count	= rt2880_pmx_func_count,
	.get_function_name	= rt2880_pmx_func_name,
	.get_function_groups	= rt2880_pmx_group_get_groups,
	.set_mux		= rt2880_pmx_group_enable,
	.gpio_request_enable	= rt2880_pmx_group_gpio_request_enable,
पूर्ण;

अटल काष्ठा pinctrl_desc rt2880_pctrl_desc = अणु
	.owner		= THIS_MODULE,
	.name		= "rt2880-pinmux",
	.pctlops	= &rt2880_pctrl_ops,
	.pmxops		= &rt2880_pmx_group_ops,
पूर्ण;

अटल काष्ठा rt2880_pmx_func gpio_func = अणु
	.name = "gpio",
पूर्ण;

अटल पूर्णांक rt2880_pinmux_index(काष्ठा rt2880_priv *p)
अणु
	काष्ठा rt2880_pmx_group *mux = p->groups;
	पूर्णांक i, j, c = 0;

	/* count the mux functions */
	जबतक (mux->name) अणु
		p->group_count++;
		mux++;
	पूर्ण

	/* allocate the group names array needed by the gpio function */
	p->group_names = devm_kसुस्मृति(p->dev, p->group_count,
				      माप(अक्षर *), GFP_KERNEL);
	अगर (!p->group_names)
		वापस -ENOMEM;

	क्रम (i = 0; i < p->group_count; i++) अणु
		p->group_names[i] = p->groups[i].name;
		p->func_count += p->groups[i].func_count;
	पूर्ण

	/* we have a dummy function[0] क्रम gpio */
	p->func_count++;

	/* allocate our function and group mapping index buffers */
	p->func = devm_kसुस्मृति(p->dev, p->func_count,
			       माप(*p->func), GFP_KERNEL);
	gpio_func.groups = devm_kसुस्मृति(p->dev, p->group_count, माप(पूर्णांक),
					GFP_KERNEL);
	अगर (!p->func || !gpio_func.groups)
		वापस -ENOMEM;

	/* add a backpoपूर्णांकer to the function so it knows its group */
	gpio_func.group_count = p->group_count;
	क्रम (i = 0; i < gpio_func.group_count; i++)
		gpio_func.groups[i] = i;

	p->func[c] = &gpio_func;
	c++;

	/* add reमुख्यing functions */
	क्रम (i = 0; i < p->group_count; i++) अणु
		क्रम (j = 0; j < p->groups[i].func_count; j++) अणु
			p->func[c] = &p->groups[i].func[j];
			p->func[c]->groups = devm_kzalloc(p->dev, माप(पूर्णांक),
						    GFP_KERNEL);
			अगर (!p->func[c]->groups)
				वापस -ENOMEM;
			p->func[c]->groups[0] = i;
			p->func[c]->group_count = 1;
			c++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt2880_pinmux_pins(काष्ठा rt2880_priv *p)
अणु
	पूर्णांक i, j;

	/*
	 * loop over the functions and initialize the pins array.
	 * also work out the highest pin used.
	 */
	क्रम (i = 0; i < p->func_count; i++) अणु
		पूर्णांक pin;

		अगर (!p->func[i]->pin_count)
			जारी;

		p->func[i]->pins = devm_kसुस्मृति(p->dev,
						p->func[i]->pin_count,
						माप(पूर्णांक),
						GFP_KERNEL);
		क्रम (j = 0; j < p->func[i]->pin_count; j++)
			p->func[i]->pins[j] = p->func[i]->pin_first + j;

		pin = p->func[i]->pin_first + p->func[i]->pin_count;
		अगर (pin > p->max_pins)
			p->max_pins = pin;
	पूर्ण

	/* the buffer that tells us which pins are gpio */
	p->gpio = devm_kसुस्मृति(p->dev, p->max_pins, माप(u8), GFP_KERNEL);
	/* the pads needed to tell pinctrl about our pins */
	p->pads = devm_kसुस्मृति(p->dev, p->max_pins,
			       माप(काष्ठा pinctrl_pin_desc), GFP_KERNEL);
	अगर (!p->pads || !p->gpio)
		वापस -ENOMEM;

	स_रखो(p->gpio, 1, माप(u8) * p->max_pins);
	क्रम (i = 0; i < p->func_count; i++) अणु
		अगर (!p->func[i]->pin_count)
			जारी;

		क्रम (j = 0; j < p->func[i]->pin_count; j++)
			p->gpio[p->func[i]->pins[j]] = 0;
	पूर्ण

	/* pin 0 is always a gpio */
	p->gpio[0] = 1;

	/* set the pads */
	क्रम (i = 0; i < p->max_pins; i++) अणु
		/* म_माप("ioXY") + 1 = 5 */
		अक्षर *name = devm_kzalloc(p->dev, 5, GFP_KERNEL);

		अगर (!name)
			वापस -ENOMEM;
		snम_लिखो(name, 5, "io%d", i);
		p->pads[i].number = i;
		p->pads[i].name = name;
	पूर्ण
	p->desc->pins = p->pads;
	p->desc->npins = p->max_pins;

	वापस 0;
पूर्ण

अटल पूर्णांक rt2880_pinmux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rt2880_priv *p;
	काष्ठा pinctrl_dev *dev;
	पूर्णांक err;

	अगर (!rt2880_pinmux_data)
		वापस -ENOTSUPP;

	/* setup the निजी data */
	p = devm_kzalloc(&pdev->dev, माप(काष्ठा rt2880_priv), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->dev = &pdev->dev;
	p->desc = &rt2880_pctrl_desc;
	p->groups = rt2880_pinmux_data;
	platक्रमm_set_drvdata(pdev, p);

	/* init the device */
	err = rt2880_pinmux_index(p);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to load index\n");
		वापस err;
	पूर्ण

	err = rt2880_pinmux_pins(p);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to load pins\n");
		वापस err;
	पूर्ण
	dev = pinctrl_रेजिस्टर(p->desc, &pdev->dev, p);

	वापस PTR_ERR_OR_ZERO(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id rt2880_pinmux_match[] = अणु
	अणु .compatible = "ralink,rt2880-pinmux" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt2880_pinmux_match);

अटल काष्ठा platक्रमm_driver rt2880_pinmux_driver = अणु
	.probe = rt2880_pinmux_probe,
	.driver = अणु
		.name = "rt2880-pinmux",
		.of_match_table = rt2880_pinmux_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rt2880_pinmux_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rt2880_pinmux_driver);
पूर्ण

core_initcall_sync(rt2880_pinmux_init);
