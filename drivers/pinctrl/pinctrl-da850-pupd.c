<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinconf driver क्रम TI DA850/OMAP-L138/AM18XX pullup/pullकरोwn groups
 *
 * Copyright (C) 2016  David Lechner
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DA850_PUPD_ENA		0x00
#घोषणा DA850_PUPD_SEL		0x04

काष्ठा da850_pupd_data अणु
	व्योम __iomem *base;
	काष्ठा pinctrl_desc desc;
	काष्ठा pinctrl_dev *pinctrl;
पूर्ण;

अटल स्थिर अक्षर * स्थिर da850_pupd_group_names[] = अणु
	"cp0", "cp1", "cp2", "cp3", "cp4", "cp5", "cp6", "cp7",
	"cp8", "cp9", "cp10", "cp11", "cp12", "cp13", "cp14", "cp15",
	"cp16", "cp17", "cp18", "cp19", "cp20", "cp21", "cp22", "cp23",
	"cp24", "cp25", "cp26", "cp27", "cp28", "cp29", "cp30", "cp31",
पूर्ण;

अटल पूर्णांक da850_pupd_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(da850_pupd_group_names);
पूर्ण

अटल स्थिर अक्षर *da850_pupd_get_group_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित पूर्णांक selector)
अणु
	वापस da850_pupd_group_names[selector];
पूर्ण

अटल पूर्णांक da850_pupd_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक selector,
				     स्थिर अचिन्हित पूर्णांक **pins,
				     अचिन्हित पूर्णांक *num_pins)
अणु
	*num_pins = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops da850_pupd_pctlops = अणु
	.get_groups_count	= da850_pupd_get_groups_count,
	.get_group_name		= da850_pupd_get_group_name,
	.get_group_pins		= da850_pupd_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक da850_pupd_pin_config_group_get(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक selector,
					   अचिन्हित दीर्घ *config)
अणु
	काष्ठा da850_pupd_data *data = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	u32 val;
	u16 arg;

	val = पढ़ोl(data->base + DA850_PUPD_ENA);
	arg = !!(~val & BIT(selector));

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (arg) अणु
			/* bias is disabled */
			arg = 0;
			अवरोध;
		पूर्ण
		val = पढ़ोl(data->base + DA850_PUPD_SEL);
		अगर (param == PIN_CONFIG_BIAS_PULL_DOWN)
			val = ~val;
		arg = !!(val & BIT(selector));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक da850_pupd_pin_config_group_set(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक selector,
					   अचिन्हित दीर्घ *configs,
					   अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा da850_pupd_data *data = pinctrl_dev_get_drvdata(pctldev);
	u32 ena, sel;
	क्रमागत pin_config_param param;
	पूर्णांक i;

	ena = पढ़ोl(data->base + DA850_PUPD_ENA);
	sel = पढ़ोl(data->base + DA850_PUPD_SEL);

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			ena &= ~BIT(selector);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			ena |= BIT(selector);
			sel |= BIT(selector);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ena |= BIT(selector);
			sel &= ~BIT(selector);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ग_लिखोl(sel, data->base + DA850_PUPD_SEL);
	ग_लिखोl(ena, data->base + DA850_PUPD_ENA);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops da850_pupd_confops = अणु
	.is_generic		= true,
	.pin_config_group_get	= da850_pupd_pin_config_group_get,
	.pin_config_group_set	= da850_pupd_pin_config_group_set,
पूर्ण;

अटल पूर्णांक da850_pupd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da850_pupd_data *data;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->base)) अणु
		dev_err(dev, "Could not map resource\n");
		वापस PTR_ERR(data->base);
	पूर्ण

	data->desc.name = dev_name(dev);
	data->desc.pctlops = &da850_pupd_pctlops;
	data->desc.confops = &da850_pupd_confops;
	data->desc.owner = THIS_MODULE;

	data->pinctrl = devm_pinctrl_रेजिस्टर(dev, &data->desc, data);
	अगर (IS_ERR(data->pinctrl)) अणु
		dev_err(dev, "Failed to register pinctrl\n");
		वापस PTR_ERR(data->pinctrl);
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल पूर्णांक da850_pupd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id da850_pupd_of_match[] = अणु
	अणु .compatible = "ti,da850-pupd" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da850_pupd_of_match);

अटल काष्ठा platक्रमm_driver da850_pupd_driver = अणु
	.driver	= अणु
		.name		= "ti-da850-pupd",
		.of_match_table	= da850_pupd_of_match,
	पूर्ण,
	.probe	= da850_pupd_probe,
	.हटाओ	= da850_pupd_हटाओ,
पूर्ण;
module_platक्रमm_driver(da850_pupd_driver);

MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_DESCRIPTION("TI DA850/OMAP-L138/AM18XX pullup/pulldown configuration");
MODULE_LICENSE("GPL");
