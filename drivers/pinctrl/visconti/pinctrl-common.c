<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 TOSHIBA CORPORATION
 * Copyright (c) 2020 Toshiba Electronic Devices & Storage Corporation
 * Copyright (c) 2020 Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp>
 */

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश "pinctrl-common.h"
#समावेश "../core.h"
#समावेश "../pinconf.h"
#समावेश "../pinctrl-utils.h"

#घोषणा DSEL_MASK GENMASK(3, 0)

/* निजी data */
काष्ठा visconti_pinctrl अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा pinctrl_desc pctl_desc;

	स्थिर काष्ठा visconti_pinctrl_devdata  *devdata;

	spinlock_t lock; /* protect pinctrl रेजिस्टर */
पूर्ण;

/* pinconf */
अटल पूर्णांक visconti_pin_config_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक _pin,
				  अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा visconti_desc_pin *pin = &priv->devdata->pins[_pin];
	क्रमागत pin_config_param param;
	अचिन्हित पूर्णांक arg;
	पूर्णांक i, ret = 0;
	अचिन्हित पूर्णांक val, set_val, pude_val;
	अचिन्हित दीर्घ flags;

	dev_dbg(priv->dev, "%s: pin = %d (%s)\n", __func__, _pin, pin->pin.name);

	spin_lock_irqsave(&priv->lock, flags);

	क्रम (i = 0; i < num_configs; i++) अणु
		set_val = 0;
		pude_val = 0;

		param = pinconf_to_config_param(configs[i]);
		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			set_val = 1;
			fallthrough;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			/* update pudsel setting */
			val = पढ़ोl(priv->base + pin->pudsel_offset);
			val &= ~BIT(pin->pud_shअगरt);
			val |= set_val << pin->pud_shअगरt;
			ग_लिखोl(val, priv->base + pin->pudsel_offset);
			pude_val = 1;
			fallthrough;
		हाल PIN_CONFIG_BIAS_DISABLE:
			/* update pude setting */
			val = पढ़ोl(priv->base + pin->pude_offset);
			val &= ~BIT(pin->pud_shअगरt);
			val |= pude_val << pin->pud_shअगरt;
			ग_लिखोl(val, priv->base + pin->pude_offset);
			dev_dbg(priv->dev, "BIAS(%d): off = 0x%x val = 0x%x\n",
				param, pin->pude_offset, val);
			अवरोध;

		हाल PIN_CONFIG_DRIVE_STRENGTH:
			arg = pinconf_to_config_argument(configs[i]);
			dev_dbg(priv->dev, "DRV_STR arg = %d\n", arg);
			चयन (arg) अणु
			हाल 2:
			हाल 4:
			हाल 8:
			हाल 16:
			हाल 24:
			हाल 32:
				/*
				 * I/O drive capacity setting:
				 * 2mA: 0
				 * 4mA: 1
				 * 8mA: 3
				 * 16mA: 7
				 * 24mA: 11
				 * 32mA: 15
				 */
				set_val = DIV_ROUND_CLOSEST(arg, 2) - 1;
				अवरोध;
			शेष:
				ret = -EINVAL;
				जाओ err;
			पूर्ण
			/* update drive setting */
			val = पढ़ोl(priv->base + pin->dsel_offset);
			val &= ~(DSEL_MASK << pin->dsel_shअगरt);
			val |= set_val << pin->dsel_shअगरt;
			ग_लिखोl(val, priv->base + pin->dsel_offset);
			अवरोध;

		शेष:
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण
	पूर्ण
err:
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक visconti_pin_config_group_set(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक selector,
					अचिन्हित दीर्घ *configs,
					अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक num_pins;
	पूर्णांक i, ret;

	pins = priv->devdata->groups[selector].pins;
	num_pins = priv->devdata->groups[selector].nr_pins;

	dev_dbg(priv->dev, "%s: select = %d, n_pin = %d, n_config = %d\n",
		__func__, selector, num_pins, num_configs);

	क्रम (i = 0; i < num_pins; i++) अणु
		ret = visconti_pin_config_set(pctldev, pins[i],
					     configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा pinconf_ops visconti_pinconf_ops = अणु
	.is_generic			= true,
	.pin_config_set			= visconti_pin_config_set,
	.pin_config_group_set		= visconti_pin_config_group_set,
	.pin_config_config_dbg_show	= pinconf_generic_dump_config,
पूर्ण;

/* pinctrl */
अटल पूर्णांक visconti_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->devdata->nr_groups;
पूर्ण

अटल स्थिर अक्षर *visconti_get_group_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->devdata->groups[selector].name;
पूर्ण

अटल पूर्णांक visconti_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक selector,
				      स्थिर अचिन्हित पूर्णांक **pins,
				      अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);

	*pins = priv->devdata->groups[selector].pins;
	*num_pins = priv->devdata->groups[selector].nr_pins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops visconti_pinctrl_ops = अणु
	.get_groups_count	= visconti_get_groups_count,
	.get_group_name		= visconti_get_group_name,
	.get_group_pins		= visconti_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

/* pinmux */
अटल पूर्णांक visconti_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->devdata->nr_functions;
पूर्ण

अटल स्थिर अक्षर *visconti_get_function_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित पूर्णांक selector)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->devdata->functions[selector].name;
पूर्ण

अटल पूर्णांक visconti_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक selector,
				       स्थिर अक्षर * स्थिर **groups,
				       अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);

	*groups = priv->devdata->functions[selector].groups;
	*num_groups = priv->devdata->functions[selector].nr_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक visconti_set_mux(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक group)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा visconti_pin_function *func = &priv->devdata->functions[function];
	स्थिर काष्ठा visconti_pin_group *grp = &priv->devdata->groups[group];
	स्थिर काष्ठा visconti_mux *mux = &grp->mux;
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ flags;

	dev_dbg(priv->dev, "%s: function = %d(%s) group = %d(%s)\n", __func__,
		function, func->name, group, grp->name);

	spin_lock_irqsave(&priv->lock, flags);

	/* update mux */
	val = पढ़ोl(priv->base + mux->offset);
	val &= ~mux->mask;
	val |= mux->val;
	ग_लिखोl(val, priv->base + mux->offset);

	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(priv->dev, "[%x]: 0x%x\n", mux->offset, val);

	वापस 0;
पूर्ण

अटल पूर्णांक visconti_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_gpio_range *range,
				      अचिन्हित पूर्णांक pin)
अणु
	काष्ठा visconti_pinctrl *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा visconti_mux *gpio_mux = &priv->devdata->gpio_mux[pin];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	dev_dbg(priv->dev, "%s: pin = %d\n", __func__, pin);

	/* update mux */
	spin_lock_irqsave(&priv->lock, flags);
	val = पढ़ोl(priv->base + gpio_mux->offset);
	val &= ~gpio_mux->mask;
	val |= gpio_mux->val;
	ग_लिखोl(val, priv->base + gpio_mux->offset);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops visconti_pinmux_ops = अणु
	.get_functions_count	= visconti_get_functions_count,
	.get_function_name	= visconti_get_function_name,
	.get_function_groups	= visconti_get_function_groups,
	.set_mux		= visconti_set_mux,
	.gpio_request_enable	= visconti_gpio_request_enable,
	.strict			= true,
पूर्ण;

पूर्णांक visconti_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			  स्थिर काष्ठा visconti_pinctrl_devdata *devdata)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा visconti_pinctrl *priv;
	काष्ठा pinctrl_pin_desc *pins;
	पूर्णांक i, ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->devdata = devdata;
	spin_lock_init(&priv->lock);

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		dev_err(dev, "unable to map I/O space\n");
		वापस PTR_ERR(priv->base);
	पूर्ण

	pins = devm_kसुस्मृति(dev, devdata->nr_pins,
			    माप(*pins), GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < devdata->nr_pins; i++)
		pins[i] = devdata->pins[i].pin;

	priv->pctl_desc.name = dev_name(dev);
	priv->pctl_desc.owner = THIS_MODULE;
	priv->pctl_desc.pins = pins;
	priv->pctl_desc.npins = devdata->nr_pins;
	priv->pctl_desc.confops = &visconti_pinconf_ops;
	priv->pctl_desc.pctlops = &visconti_pinctrl_ops;
	priv->pctl_desc.pmxops = &visconti_pinmux_ops;

	ret = devm_pinctrl_रेजिस्टर_and_init(dev, &priv->pctl_desc,
					     priv, &priv->pctl);
	अगर (ret) अणु
		dev_err(dev, "couldn't register pinctrl: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (devdata->unlock)
		devdata->unlock(priv->base);

	वापस pinctrl_enable(priv->pctl);
पूर्ण
