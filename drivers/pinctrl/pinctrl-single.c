<शैली गुरु>
/*
 * Generic device tree based pinctrl driver क्रम one रेजिस्टर per pin
 * type pinmux controllers
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/irqchip/chained_irq.h>

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश <linux/platक्रमm_data/pinctrl-single.h>

#समावेश "core.h"
#समावेश "devicetree.h"
#समावेश "pinconf.h"
#समावेश "pinmux.h"

#घोषणा DRIVER_NAME			"pinctrl-single"
#घोषणा PCS_OFF_DISABLED		~0U

/**
 * काष्ठा pcs_func_vals - mux function रेजिस्टर offset and value pair
 * @reg:	रेजिस्टर भव address
 * @val:	रेजिस्टर value
 * @mask:	mask
 */
काष्ठा pcs_func_vals अणु
	व्योम __iomem *reg;
	अचिन्हित val;
	अचिन्हित mask;
पूर्ण;

/**
 * काष्ठा pcs_conf_vals - pinconf parameter, pinconf रेजिस्टर offset
 * and value, enable, disable, mask
 * @param:	config parameter
 * @val:	user input bits in the pinconf रेजिस्टर
 * @enable:	enable bits in the pinconf रेजिस्टर
 * @disable:	disable bits in the pinconf रेजिस्टर
 * @mask:	mask bits in the रेजिस्टर value
 */
काष्ठा pcs_conf_vals अणु
	क्रमागत pin_config_param param;
	अचिन्हित val;
	अचिन्हित enable;
	अचिन्हित disable;
	अचिन्हित mask;
पूर्ण;

/**
 * काष्ठा pcs_conf_type - pinconf property name, pinconf param pair
 * @name:	property name in DTS file
 * @param:	config parameter
 */
काष्ठा pcs_conf_type अणु
	स्थिर अक्षर *name;
	क्रमागत pin_config_param param;
पूर्ण;

/**
 * काष्ठा pcs_function - pinctrl function
 * @name:	pinctrl function name
 * @vals:	रेजिस्टर and vals array
 * @nvals:	number of entries in vals array
 * @pgnames:	array of pingroup names the function uses
 * @npgnames:	number of pingroup names the function uses
 * @conf:	array of pin configurations
 * @nconfs:	number of pin configurations available
 * @node:	list node
 */
काष्ठा pcs_function अणु
	स्थिर अक्षर *name;
	काष्ठा pcs_func_vals *vals;
	अचिन्हित nvals;
	स्थिर अक्षर **pgnames;
	पूर्णांक npgnames;
	काष्ठा pcs_conf_vals *conf;
	पूर्णांक nconfs;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा pcs_gpiofunc_range - pin ranges with same mux value of gpio function
 * @offset:	offset base of pins
 * @npins:	number pins with the same mux value of gpio function
 * @gpiofunc:	mux value of gpio function
 * @node:	list node
 */
काष्ठा pcs_gpiofunc_range अणु
	अचिन्हित offset;
	अचिन्हित npins;
	अचिन्हित gpiofunc;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा pcs_data - wrapper क्रम data needed by pinctrl framework
 * @pa:		pindesc array
 * @cur:	index to current element
 *
 * REVISIT: We should be able to drop this eventually by adding
 * support क्रम रेजिस्टरing pins inभागidually in the pinctrl
 * framework क्रम those drivers that करोn't need a अटल array.
 */
काष्ठा pcs_data अणु
	काष्ठा pinctrl_pin_desc *pa;
	पूर्णांक cur;
पूर्ण;

/**
 * काष्ठा pcs_soc_data - SoC specअगरic settings
 * @flags:	initial SoC specअगरic PCS_FEAT_xxx values
 * @irq:	optional पूर्णांकerrupt क्रम the controller
 * @irq_enable_mask:	optional SoC specअगरic पूर्णांकerrupt enable mask
 * @irq_status_mask:	optional SoC specअगरic पूर्णांकerrupt status mask
 * @rearm:	optional SoC specअगरic wake-up rearm function
 */
काष्ठा pcs_soc_data अणु
	अचिन्हित flags;
	पूर्णांक irq;
	अचिन्हित irq_enable_mask;
	अचिन्हित irq_status_mask;
	व्योम (*rearm)(व्योम);
पूर्ण;

/**
 * काष्ठा pcs_device - pinctrl device instance
 * @res:	resources
 * @base:	भव address of the controller
 * @saved_vals: saved values क्रम the controller
 * @size:	size of the ioremapped area
 * @dev:	device entry
 * @np:		device tree node
 * @pctl:	pin controller device
 * @flags:	mask of PCS_FEAT_xxx values
 * @missing_nr_pinctrl_cells: क्रम legacy binding, may go away
 * @socdata:	soc specअगरic data
 * @lock:	spinlock क्रम रेजिस्टर access
 * @mutex:	mutex protecting the lists
 * @width:	bits per mux रेजिस्टर
 * @fmask:	function रेजिस्टर mask
 * @fshअगरt:	function रेजिस्टर shअगरt
 * @foff:	value to turn mux off
 * @fmax:	max number of functions in fmask
 * @bits_per_mux: number of bits per mux
 * @bits_per_pin: number of bits per pin
 * @pins:	physical pins on the SoC
 * @gpiofuncs:	list of gpio functions
 * @irqs:	list of पूर्णांकerrupt रेजिस्टरs
 * @chip:	chip container क्रम this instance
 * @करोमुख्य:	IRQ करोमुख्य क्रम this instance
 * @desc:	pin controller descriptor
 * @पढ़ो:	रेजिस्टर पढ़ो function to use
 * @ग_लिखो:	रेजिस्टर ग_लिखो function to use
 */
काष्ठा pcs_device अणु
	काष्ठा resource *res;
	व्योम __iomem *base;
	व्योम *saved_vals;
	अचिन्हित size;
	काष्ठा device *dev;
	काष्ठा device_node *np;
	काष्ठा pinctrl_dev *pctl;
	अचिन्हित flags;
#घोषणा PCS_CONTEXT_LOSS_OFF	(1 << 3)
#घोषणा PCS_QUIRK_SHARED_IRQ	(1 << 2)
#घोषणा PCS_FEAT_IRQ		(1 << 1)
#घोषणा PCS_FEAT_PINCONF	(1 << 0)
	काष्ठा property *missing_nr_pinctrl_cells;
	काष्ठा pcs_soc_data socdata;
	raw_spinlock_t lock;
	काष्ठा mutex mutex;
	अचिन्हित width;
	अचिन्हित fmask;
	अचिन्हित fshअगरt;
	अचिन्हित foff;
	अचिन्हित fmax;
	bool bits_per_mux;
	अचिन्हित bits_per_pin;
	काष्ठा pcs_data pins;
	काष्ठा list_head gpiofuncs;
	काष्ठा list_head irqs;
	काष्ठा irq_chip chip;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा pinctrl_desc desc;
	अचिन्हित (*पढ़ो)(व्योम __iomem *reg);
	व्योम (*ग_लिखो)(अचिन्हित val, व्योम __iomem *reg);
पूर्ण;

#घोषणा PCS_QUIRK_HAS_SHARED_IRQ	(pcs->flags & PCS_QUIRK_SHARED_IRQ)
#घोषणा PCS_HAS_IRQ		(pcs->flags & PCS_FEAT_IRQ)
#घोषणा PCS_HAS_PINCONF		(pcs->flags & PCS_FEAT_PINCONF)

अटल पूर्णांक pcs_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			   अचिन्हित दीर्घ *config);
अटल पूर्णांक pcs_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			   अचिन्हित दीर्घ *configs, अचिन्हित num_configs);

अटल क्रमागत pin_config_param pcs_bias[] = अणु
	PIN_CONFIG_BIAS_PULL_DOWN,
	PIN_CONFIG_BIAS_PULL_UP,
पूर्ण;

/*
 * This lock class tells lockdep that irqchip core that this single
 * pinctrl can be in a dअगरferent category than its parents, so it won't
 * report false recursion.
 */
अटल काष्ठा lock_class_key pcs_lock_class;

/* Class क्रम the IRQ request mutex */
अटल काष्ठा lock_class_key pcs_request_class;

/*
 * REVISIT: Reads and ग_लिखोs could eventually use regmap or something
 * generic. But at least on omaps, some mux रेजिस्टरs are perक्रमmance
 * critical as they may need to be remuxed every समय beक्रमe and after
 * idle. Adding tests क्रम रेजिस्टर access width क्रम every पढ़ो and
 * ग_लिखो like regmap is करोing is not desired, and caching the रेजिस्टरs
 * करोes not help in this हाल.
 */

अटल अचिन्हित __maybe_unused pcs_पढ़ोb(व्योम __iomem *reg)
अणु
	वापस पढ़ोb(reg);
पूर्ण

अटल अचिन्हित __maybe_unused pcs_पढ़ोw(व्योम __iomem *reg)
अणु
	वापस पढ़ोw(reg);
पूर्ण

अटल अचिन्हित __maybe_unused pcs_पढ़ोl(व्योम __iomem *reg)
अणु
	वापस पढ़ोl(reg);
पूर्ण

अटल व्योम __maybe_unused pcs_ग_लिखोb(अचिन्हित val, व्योम __iomem *reg)
अणु
	ग_लिखोb(val, reg);
पूर्ण

अटल व्योम __maybe_unused pcs_ग_लिखोw(अचिन्हित val, व्योम __iomem *reg)
अणु
	ग_लिखोw(val, reg);
पूर्ण

अटल व्योम __maybe_unused pcs_ग_लिखोl(अचिन्हित val, व्योम __iomem *reg)
अणु
	ग_लिखोl(val, reg);
पूर्ण

अटल अचिन्हित पूर्णांक pcs_pin_reg_offset_get(काष्ठा pcs_device *pcs,
					   अचिन्हित पूर्णांक pin)
अणु
	अचिन्हित पूर्णांक mux_bytes = pcs->width / BITS_PER_BYTE;

	अगर (pcs->bits_per_mux) अणु
		अचिन्हित पूर्णांक pin_offset_bytes;

		pin_offset_bytes = (pcs->bits_per_pin * pin) / BITS_PER_BYTE;
		वापस (pin_offset_bytes / mux_bytes) * mux_bytes;
	पूर्ण

	वापस pin * mux_bytes;
पूर्ण

अटल अचिन्हित पूर्णांक pcs_pin_shअगरt_reg_get(काष्ठा pcs_device *pcs,
					  अचिन्हित पूर्णांक pin)
अणु
	वापस (pin % (pcs->width / pcs->bits_per_pin)) * pcs->bits_per_pin;
पूर्ण

अटल व्योम pcs_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
					काष्ठा seq_file *s,
					अचिन्हित pin)
अणु
	काष्ठा pcs_device *pcs;
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ offset;
	माप_प्रकार pa;

	pcs = pinctrl_dev_get_drvdata(pctldev);

	offset = pcs_pin_reg_offset_get(pcs, pin);
	val = pcs->पढ़ो(pcs->base + offset);

	अगर (pcs->bits_per_mux)
		val &= pcs->fmask << pcs_pin_shअगरt_reg_get(pcs, pin);

	pa = pcs->res->start + offset;

	seq_म_लिखो(s, "%zx %08x %s ", pa, val, DRIVER_NAME);
पूर्ण

अटल व्योम pcs_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	काष्ठा pcs_device *pcs;

	pcs = pinctrl_dev_get_drvdata(pctldev);
	devm_kमुक्त(pcs->dev, map);
पूर्ण

अटल पूर्णांक pcs_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा device_node *np_config,
				काष्ठा pinctrl_map **map, अचिन्हित *num_maps);

अटल स्थिर काष्ठा pinctrl_ops pcs_pinctrl_ops = अणु
	.get_groups_count = pinctrl_generic_get_group_count,
	.get_group_name = pinctrl_generic_get_group_name,
	.get_group_pins = pinctrl_generic_get_group_pins,
	.pin_dbg_show = pcs_pin_dbg_show,
	.dt_node_to_map = pcs_dt_node_to_map,
	.dt_मुक्त_map = pcs_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक pcs_get_function(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			    काष्ठा pcs_function **func)
अणु
	काष्ठा pcs_device *pcs = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pin_desc *pdesc = pin_desc_get(pctldev, pin);
	स्थिर काष्ठा pinctrl_setting_mux *setting;
	काष्ठा function_desc *function;
	अचिन्हित fselector;

	/* If pin is not described in DTS & enabled, mux_setting is शून्य. */
	setting = pdesc->mux_setting;
	अगर (!setting)
		वापस -ENOTSUPP;
	fselector = setting->func;
	function = pinmux_generic_get_function(pctldev, fselector);
	*func = function->data;
	अगर (!(*func)) अणु
		dev_err(pcs->dev, "%s could not find function%i\n",
			__func__, fselector);
		वापस -ENOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcs_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित fselector,
	अचिन्हित group)
अणु
	काष्ठा pcs_device *pcs;
	काष्ठा function_desc *function;
	काष्ठा pcs_function *func;
	पूर्णांक i;

	pcs = pinctrl_dev_get_drvdata(pctldev);
	/* If function mask is null, needn't enable it. */
	अगर (!pcs->fmask)
		वापस 0;
	function = pinmux_generic_get_function(pctldev, fselector);
	func = function->data;
	अगर (!func)
		वापस -EINVAL;

	dev_dbg(pcs->dev, "enabling %s function%i\n",
		func->name, fselector);

	क्रम (i = 0; i < func->nvals; i++) अणु
		काष्ठा pcs_func_vals *vals;
		अचिन्हित दीर्घ flags;
		अचिन्हित val, mask;

		vals = &func->vals[i];
		raw_spin_lock_irqsave(&pcs->lock, flags);
		val = pcs->पढ़ो(vals->reg);

		अगर (pcs->bits_per_mux)
			mask = vals->mask;
		अन्यथा
			mask = pcs->fmask;

		val &= ~mask;
		val |= (vals->val & mask);
		pcs->ग_लिखो(val, vals->reg);
		raw_spin_unlock_irqrestore(&pcs->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcs_request_gpio(काष्ठा pinctrl_dev *pctldev,
			    काष्ठा pinctrl_gpio_range *range, अचिन्हित pin)
अणु
	काष्ठा pcs_device *pcs = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pcs_gpiofunc_range *frange = शून्य;
	काष्ठा list_head *pos, *पंचांगp;
	अचिन्हित data;

	/* If function mask is null, वापस directly. */
	अगर (!pcs->fmask)
		वापस -ENOTSUPP;

	list_क्रम_each_safe(pos, पंचांगp, &pcs->gpiofuncs) अणु
		u32 offset;

		frange = list_entry(pos, काष्ठा pcs_gpiofunc_range, node);
		अगर (pin >= frange->offset + frange->npins
			|| pin < frange->offset)
			जारी;

		offset = pcs_pin_reg_offset_get(pcs, pin);

		अगर (pcs->bits_per_mux) अणु
			पूर्णांक pin_shअगरt = pcs_pin_shअगरt_reg_get(pcs, pin);

			data = pcs->पढ़ो(pcs->base + offset);
			data &= ~(pcs->fmask << pin_shअगरt);
			data |= frange->gpiofunc << pin_shअगरt;
			pcs->ग_लिखो(data, pcs->base + offset);
		पूर्ण अन्यथा अणु
			data = pcs->पढ़ो(pcs->base + offset);
			data &= ~pcs->fmask;
			data |= frange->gpiofunc;
			pcs->ग_लिखो(data, pcs->base + offset);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops pcs_pinmux_ops = अणु
	.get_functions_count = pinmux_generic_get_function_count,
	.get_function_name = pinmux_generic_get_function_name,
	.get_function_groups = pinmux_generic_get_function_groups,
	.set_mux = pcs_set_mux,
	.gpio_request_enable = pcs_request_gpio,
पूर्ण;

/* Clear BIAS value */
अटल व्योम pcs_pinconf_clear_bias(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin)
अणु
	अचिन्हित दीर्घ config;
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(pcs_bias); i++) अणु
		config = pinconf_to_config_packed(pcs_bias[i], 0);
		pcs_pinconf_set(pctldev, pin, &config, 1);
	पूर्ण
पूर्ण

/*
 * Check whether PIN_CONFIG_BIAS_DISABLE is valid.
 * It's depend on that PULL_DOWN & PULL_UP configs are all invalid.
 */
अटल bool pcs_pinconf_bias_disable(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin)
अणु
	अचिन्हित दीर्घ config;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcs_bias); i++) अणु
		config = pinconf_to_config_packed(pcs_bias[i], 0);
		अगर (!pcs_pinconf_get(pctldev, pin, &config))
			जाओ out;
	पूर्ण
	वापस true;
out:
	वापस false;
पूर्ण

अटल पूर्णांक pcs_pinconf_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा pcs_device *pcs = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pcs_function *func;
	क्रमागत pin_config_param param;
	अचिन्हित offset = 0, data = 0, i, j, ret;

	ret = pcs_get_function(pctldev, pin, &func);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < func->nconfs; i++) अणु
		param = pinconf_to_config_param(*config);
		अगर (param == PIN_CONFIG_BIAS_DISABLE) अणु
			अगर (pcs_pinconf_bias_disable(pctldev, pin)) अणु
				*config = 0;
				वापस 0;
			पूर्ण अन्यथा अणु
				वापस -ENOTSUPP;
			पूर्ण
		पूर्ण अन्यथा अगर (param != func->conf[i].param) अणु
			जारी;
		पूर्ण

		offset = pin * (pcs->width / BITS_PER_BYTE);
		data = pcs->पढ़ो(pcs->base + offset) & func->conf[i].mask;
		चयन (func->conf[i].param) अणु
		/* 4 parameters */
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			अगर ((data != func->conf[i].enable) ||
			    (data == func->conf[i].disable))
				वापस -ENOTSUPP;
			*config = 0;
			अवरोध;
		/* 2 parameters */
		हाल PIN_CONFIG_INPUT_SCHMITT:
			क्रम (j = 0; j < func->nconfs; j++) अणु
				चयन (func->conf[j].param) अणु
				हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
					अगर (data != func->conf[j].enable)
						वापस -ENOTSUPP;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
			*config = data;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
		हाल PIN_CONFIG_SLEW_RATE:
		हाल PIN_CONFIG_MODE_LOW_POWER:
		शेष:
			*config = data;
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक pcs_pinconf_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित pin, अचिन्हित दीर्घ *configs,
				अचिन्हित num_configs)
अणु
	काष्ठा pcs_device *pcs = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pcs_function *func;
	अचिन्हित offset = 0, shअगरt = 0, i, data, ret;
	u32 arg;
	पूर्णांक j;

	ret = pcs_get_function(pctldev, pin, &func);
	अगर (ret)
		वापस ret;

	क्रम (j = 0; j < num_configs; j++) अणु
		क्रम (i = 0; i < func->nconfs; i++) अणु
			अगर (pinconf_to_config_param(configs[j])
				!= func->conf[i].param)
				जारी;

			offset = pin * (pcs->width / BITS_PER_BYTE);
			data = pcs->पढ़ो(pcs->base + offset);
			arg = pinconf_to_config_argument(configs[j]);
			चयन (func->conf[i].param) अणु
			/* 2 parameters */
			हाल PIN_CONFIG_INPUT_SCHMITT:
			हाल PIN_CONFIG_DRIVE_STRENGTH:
			हाल PIN_CONFIG_SLEW_RATE:
			हाल PIN_CONFIG_MODE_LOW_POWER:
				shअगरt = ffs(func->conf[i].mask) - 1;
				data &= ~func->conf[i].mask;
				data |= (arg << shअगरt) & func->conf[i].mask;
				अवरोध;
			/* 4 parameters */
			हाल PIN_CONFIG_BIAS_DISABLE:
				pcs_pinconf_clear_bias(pctldev, pin);
				अवरोध;
			हाल PIN_CONFIG_BIAS_PULL_DOWN:
			हाल PIN_CONFIG_BIAS_PULL_UP:
				अगर (arg)
					pcs_pinconf_clear_bias(pctldev, pin);
				fallthrough;
			हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
				data &= ~func->conf[i].mask;
				अगर (arg)
					data |= func->conf[i].enable;
				अन्यथा
					data |= func->conf[i].disable;
				अवरोध;
			शेष:
				वापस -ENOTSUPP;
			पूर्ण
			pcs->ग_लिखो(data, pcs->base + offset);

			अवरोध;
		पूर्ण
		अगर (i >= func->nconfs)
			वापस -ENOTSUPP;
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल पूर्णांक pcs_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित group, अचिन्हित दीर्घ *config)
अणु
	स्थिर अचिन्हित *pins;
	अचिन्हित npins, old = 0;
	पूर्णांक i, ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < npins; i++) अणु
		अगर (pcs_pinconf_get(pctldev, pins[i], config))
			वापस -ENOTSUPP;
		/* configs करो not match between two pins */
		अगर (i && (old != *config))
			वापस -ENOTSUPP;
		old = *config;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcs_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित group, अचिन्हित दीर्घ *configs,
				अचिन्हित num_configs)
अणु
	स्थिर अचिन्हित *pins;
	अचिन्हित npins;
	पूर्णांक i, ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < npins; i++) अणु
		अगर (pcs_pinconf_set(pctldev, pins[i], configs, num_configs))
			वापस -ENOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pcs_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				काष्ठा seq_file *s, अचिन्हित pin)
अणु
पूर्ण

अटल व्योम pcs_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
				काष्ठा seq_file *s, अचिन्हित selector)
अणु
पूर्ण

अटल व्योम pcs_pinconf_config_dbg_show(काष्ठा pinctrl_dev *pctldev,
					काष्ठा seq_file *s,
					अचिन्हित दीर्घ config)
अणु
	pinconf_generic_dump_config(pctldev, s, config);
पूर्ण

अटल स्थिर काष्ठा pinconf_ops pcs_pinconf_ops = अणु
	.pin_config_get = pcs_pinconf_get,
	.pin_config_set = pcs_pinconf_set,
	.pin_config_group_get = pcs_pinconf_group_get,
	.pin_config_group_set = pcs_pinconf_group_set,
	.pin_config_dbg_show = pcs_pinconf_dbg_show,
	.pin_config_group_dbg_show = pcs_pinconf_group_dbg_show,
	.pin_config_config_dbg_show = pcs_pinconf_config_dbg_show,
	.is_generic = true,
पूर्ण;

/**
 * pcs_add_pin() - add a pin to the अटल per controller pin array
 * @pcs: pcs driver instance
 * @offset: रेजिस्टर offset from base
 */
अटल पूर्णांक pcs_add_pin(काष्ठा pcs_device *pcs, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pcs_soc_data *pcs_soc = &pcs->socdata;
	काष्ठा pinctrl_pin_desc *pin;
	पूर्णांक i;

	i = pcs->pins.cur;
	अगर (i >= pcs->desc.npins) अणु
		dev_err(pcs->dev, "too many pins, max %i\n",
			pcs->desc.npins);
		वापस -ENOMEM;
	पूर्ण

	अगर (pcs_soc->irq_enable_mask) अणु
		अचिन्हित val;

		val = pcs->पढ़ो(pcs->base + offset);
		अगर (val & pcs_soc->irq_enable_mask) अणु
			dev_dbg(pcs->dev, "irq enabled at boot for pin at %lx (%x), clearing\n",
				(अचिन्हित दीर्घ)pcs->res->start + offset, val);
			val &= ~pcs_soc->irq_enable_mask;
			pcs->ग_लिखो(val, pcs->base + offset);
		पूर्ण
	पूर्ण

	pin = &pcs->pins.pa[i];
	pin->number = i;
	pcs->pins.cur++;

	वापस i;
पूर्ण

/**
 * pcs_allocate_pin_table() - adds all the pins क्रम the pinctrl driver
 * @pcs: pcs driver instance
 *
 * In हाल of errors, resources are मुक्तd in pcs_मुक्त_resources.
 *
 * If your hardware needs holes in the address space, then just set
 * up multiple driver instances.
 */
अटल पूर्णांक pcs_allocate_pin_table(काष्ठा pcs_device *pcs)
अणु
	पूर्णांक mux_bytes, nr_pins, i;

	mux_bytes = pcs->width / BITS_PER_BYTE;

	अगर (pcs->bits_per_mux) अणु
		pcs->bits_per_pin = fls(pcs->fmask);
		nr_pins = (pcs->size * BITS_PER_BYTE) / pcs->bits_per_pin;
	पूर्ण अन्यथा अणु
		nr_pins = pcs->size / mux_bytes;
	पूर्ण

	dev_dbg(pcs->dev, "allocating %i pins\n", nr_pins);
	pcs->pins.pa = devm_kसुस्मृति(pcs->dev,
				nr_pins, माप(*pcs->pins.pa),
				GFP_KERNEL);
	अगर (!pcs->pins.pa)
		वापस -ENOMEM;

	pcs->desc.pins = pcs->pins.pa;
	pcs->desc.npins = nr_pins;

	क्रम (i = 0; i < pcs->desc.npins; i++) अणु
		अचिन्हित offset;
		पूर्णांक res;

		offset = pcs_pin_reg_offset_get(pcs, i);
		res = pcs_add_pin(pcs, offset);
		अगर (res < 0) अणु
			dev_err(pcs->dev, "error adding pins: %i\n", res);
			वापस res;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pcs_add_function() - adds a new function to the function list
 * @pcs: pcs driver instance
 * @fcn: new function allocated
 * @name: name of the function
 * @vals: array of mux रेजिस्टर value pairs used by the function
 * @nvals: number of mux रेजिस्टर value pairs
 * @pgnames: array of pingroup names क्रम the function
 * @npgnames: number of pingroup names
 *
 * Caller must take care of locking.
 */
अटल पूर्णांक pcs_add_function(काष्ठा pcs_device *pcs,
			    काष्ठा pcs_function **fcn,
			    स्थिर अक्षर *name,
			    काष्ठा pcs_func_vals *vals,
			    अचिन्हित पूर्णांक nvals,
			    स्थिर अक्षर **pgnames,
			    अचिन्हित पूर्णांक npgnames)
अणु
	काष्ठा pcs_function *function;
	पूर्णांक selector;

	function = devm_kzalloc(pcs->dev, माप(*function), GFP_KERNEL);
	अगर (!function)
		वापस -ENOMEM;

	function->vals = vals;
	function->nvals = nvals;
	function->name = name;

	selector = pinmux_generic_add_function(pcs->pctl, name,
					       pgnames, npgnames,
					       function);
	अगर (selector < 0) अणु
		devm_kमुक्त(pcs->dev, function);
		*fcn = शून्य;
	पूर्ण अन्यथा अणु
		*fcn = function;
	पूर्ण

	वापस selector;
पूर्ण

/**
 * pcs_get_pin_by_offset() - get a pin index based on the रेजिस्टर offset
 * @pcs: pcs driver instance
 * @offset: रेजिस्टर offset from the base
 *
 * Note that this is OK as दीर्घ as the pins are in a अटल array.
 */
अटल पूर्णांक pcs_get_pin_by_offset(काष्ठा pcs_device *pcs, अचिन्हित offset)
अणु
	अचिन्हित index;

	अगर (offset >= pcs->size) अणु
		dev_err(pcs->dev, "mux offset out of range: 0x%x (0x%x)\n",
			offset, pcs->size);
		वापस -EINVAL;
	पूर्ण

	अगर (pcs->bits_per_mux)
		index = (offset * BITS_PER_BYTE) / pcs->bits_per_pin;
	अन्यथा
		index = offset / (pcs->width / BITS_PER_BYTE);

	वापस index;
पूर्ण

/*
 * check whether data matches enable bits or disable bits
 * Return value: 1 क्रम matching enable bits, 0 क्रम matching disable bits,
 *               and negative value क्रम matching failure.
 */
अटल पूर्णांक pcs_config_match(अचिन्हित data, अचिन्हित enable, अचिन्हित disable)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (data == enable)
		ret = 1;
	अन्यथा अगर (data == disable)
		ret = 0;
	वापस ret;
पूर्ण

अटल व्योम add_config(काष्ठा pcs_conf_vals **conf, क्रमागत pin_config_param param,
		       अचिन्हित value, अचिन्हित enable, अचिन्हित disable,
		       अचिन्हित mask)
अणु
	(*conf)->param = param;
	(*conf)->val = value;
	(*conf)->enable = enable;
	(*conf)->disable = disable;
	(*conf)->mask = mask;
	(*conf)++;
पूर्ण

अटल व्योम add_setting(अचिन्हित दीर्घ **setting, क्रमागत pin_config_param param,
			अचिन्हित arg)
अणु
	**setting = pinconf_to_config_packed(param, arg);
	(*setting)++;
पूर्ण

/* add pinconf setting with 2 parameters */
अटल व्योम pcs_add_conf2(काष्ठा pcs_device *pcs, काष्ठा device_node *np,
			  स्थिर अक्षर *name, क्रमागत pin_config_param param,
			  काष्ठा pcs_conf_vals **conf, अचिन्हित दीर्घ **settings)
अणु
	अचिन्हित value[2], shअगरt;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32_array(np, name, value, 2);
	अगर (ret)
		वापस;
	/* set value & mask */
	value[0] &= value[1];
	shअगरt = ffs(value[1]) - 1;
	/* skip enable & disable */
	add_config(conf, param, value[0], 0, 0, value[1]);
	add_setting(settings, param, value[0] >> shअगरt);
पूर्ण

/* add pinconf setting with 4 parameters */
अटल व्योम pcs_add_conf4(काष्ठा pcs_device *pcs, काष्ठा device_node *np,
			  स्थिर अक्षर *name, क्रमागत pin_config_param param,
			  काष्ठा pcs_conf_vals **conf, अचिन्हित दीर्घ **settings)
अणु
	अचिन्हित value[4];
	पूर्णांक ret;

	/* value to set, enable, disable, mask */
	ret = of_property_पढ़ो_u32_array(np, name, value, 4);
	अगर (ret)
		वापस;
	अगर (!value[3]) अणु
		dev_err(pcs->dev, "mask field of the property can't be 0\n");
		वापस;
	पूर्ण
	value[0] &= value[3];
	value[1] &= value[3];
	value[2] &= value[3];
	ret = pcs_config_match(value[0], value[1], value[2]);
	अगर (ret < 0)
		dev_dbg(pcs->dev, "failed to match enable or disable bits\n");
	add_config(conf, param, value[0], value[1], value[2], value[3]);
	add_setting(settings, param, ret);
पूर्ण

अटल पूर्णांक pcs_parse_pinconf(काष्ठा pcs_device *pcs, काष्ठा device_node *np,
			     काष्ठा pcs_function *func,
			     काष्ठा pinctrl_map **map)

अणु
	काष्ठा pinctrl_map *m = *map;
	पूर्णांक i = 0, nconfs = 0;
	अचिन्हित दीर्घ *settings = शून्य, *s = शून्य;
	काष्ठा pcs_conf_vals *conf = शून्य;
	अटल स्थिर काष्ठा pcs_conf_type prop2[] = अणु
		अणु "pinctrl-single,drive-strength", PIN_CONFIG_DRIVE_STRENGTH, पूर्ण,
		अणु "pinctrl-single,slew-rate", PIN_CONFIG_SLEW_RATE, पूर्ण,
		अणु "pinctrl-single,input-schmitt", PIN_CONFIG_INPUT_SCHMITT, पूर्ण,
		अणु "pinctrl-single,low-power-mode", PIN_CONFIG_MODE_LOW_POWER, पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा pcs_conf_type prop4[] = अणु
		अणु "pinctrl-single,bias-pullup", PIN_CONFIG_BIAS_PULL_UP, पूर्ण,
		अणु "pinctrl-single,bias-pulldown", PIN_CONFIG_BIAS_PULL_DOWN, पूर्ण,
		अणु "pinctrl-single,input-schmitt-enable",
			PIN_CONFIG_INPUT_SCHMITT_ENABLE, पूर्ण,
	पूर्ण;

	/* If pinconf isn't supported, don't parse properties in below. */
	अगर (!PCS_HAS_PINCONF)
		वापस -ENOTSUPP;

	/* cacluate how much properties are supported in current node */
	क्रम (i = 0; i < ARRAY_SIZE(prop2); i++) अणु
		अगर (of_find_property(np, prop2[i].name, शून्य))
			nconfs++;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(prop4); i++) अणु
		अगर (of_find_property(np, prop4[i].name, शून्य))
			nconfs++;
	पूर्ण
	अगर (!nconfs)
		वापस -ENOTSUPP;

	func->conf = devm_kसुस्मृति(pcs->dev,
				  nconfs, माप(काष्ठा pcs_conf_vals),
				  GFP_KERNEL);
	अगर (!func->conf)
		वापस -ENOMEM;
	func->nconfs = nconfs;
	conf = &(func->conf[0]);
	m++;
	settings = devm_kसुस्मृति(pcs->dev, nconfs, माप(अचिन्हित दीर्घ),
				GFP_KERNEL);
	अगर (!settings)
		वापस -ENOMEM;
	s = &settings[0];

	क्रम (i = 0; i < ARRAY_SIZE(prop2); i++)
		pcs_add_conf2(pcs, np, prop2[i].name, prop2[i].param,
			      &conf, &s);
	क्रम (i = 0; i < ARRAY_SIZE(prop4); i++)
		pcs_add_conf4(pcs, np, prop4[i].name, prop4[i].param,
			      &conf, &s);
	m->type = PIN_MAP_TYPE_CONFIGS_GROUP;
	m->data.configs.group_or_pin = np->name;
	m->data.configs.configs = settings;
	m->data.configs.num_configs = nconfs;
	वापस 0;
पूर्ण

/**
 * pcs_parse_one_pinctrl_entry() - parses a device tree mux entry
 * @pcs: pinctrl driver instance
 * @np: device node of the mux entry
 * @map: map entry
 * @num_maps: number of map
 * @pgnames: pingroup names
 *
 * Note that this binding currently supports only sets of one रेजिस्टर + value.
 *
 * Also note that this driver tries to aव्योम understanding pin and function
 * names because of the extra bloat they would cause especially in the हाल of
 * a large number of pins. This driver just sets what is specअगरied क्रम the board
 * in the .dts file. Further user space debugging tools can be developed to
 * decipher the pin and function names using debugfs.
 *
 * If you are concerned about the boot समय, set up the अटल pins in
 * the bootloader, and only set up selected pins as device tree entries.
 */
अटल पूर्णांक pcs_parse_one_pinctrl_entry(काष्ठा pcs_device *pcs,
						काष्ठा device_node *np,
						काष्ठा pinctrl_map **map,
						अचिन्हित *num_maps,
						स्थिर अक्षर **pgnames)
अणु
	स्थिर अक्षर *name = "pinctrl-single,pins";
	काष्ठा pcs_func_vals *vals;
	पूर्णांक rows, *pins, found = 0, res = -ENOMEM, i, fsel, gsel;
	काष्ठा pcs_function *function = शून्य;

	rows = pinctrl_count_index_with_args(np, name);
	अगर (rows <= 0) अणु
		dev_err(pcs->dev, "Invalid number of rows: %d\n", rows);
		वापस -EINVAL;
	पूर्ण

	vals = devm_kसुस्मृति(pcs->dev, rows, माप(*vals), GFP_KERNEL);
	अगर (!vals)
		वापस -ENOMEM;

	pins = devm_kसुस्मृति(pcs->dev, rows, माप(*pins), GFP_KERNEL);
	अगर (!pins)
		जाओ मुक्त_vals;

	क्रम (i = 0; i < rows; i++) अणु
		काष्ठा of_phandle_args pinctrl_spec;
		अचिन्हित पूर्णांक offset;
		पूर्णांक pin;

		res = pinctrl_parse_index_with_args(np, name, i, &pinctrl_spec);
		अगर (res)
			वापस res;

		अगर (pinctrl_spec.args_count < 2 || pinctrl_spec.args_count > 3) अणु
			dev_err(pcs->dev, "invalid args_count for spec: %i\n",
				pinctrl_spec.args_count);
			अवरोध;
		पूर्ण

		offset = pinctrl_spec.args[0];
		vals[found].reg = pcs->base + offset;

		चयन (pinctrl_spec.args_count) अणु
		हाल 2:
			vals[found].val = pinctrl_spec.args[1];
			अवरोध;
		हाल 3:
			vals[found].val = (pinctrl_spec.args[1] | pinctrl_spec.args[2]);
			अवरोध;
		पूर्ण

		dev_dbg(pcs->dev, "%pOFn index: 0x%x value: 0x%x\n",
			pinctrl_spec.np, offset, vals[found].val);

		pin = pcs_get_pin_by_offset(pcs, offset);
		अगर (pin < 0) अणु
			dev_err(pcs->dev,
				"could not add functions for %pOFn %ux\n",
				np, offset);
			अवरोध;
		पूर्ण
		pins[found++] = pin;
	पूर्ण

	pgnames[0] = np->name;
	mutex_lock(&pcs->mutex);
	fsel = pcs_add_function(pcs, &function, np->name, vals, found,
				pgnames, 1);
	अगर (fsel < 0) अणु
		res = fsel;
		जाओ मुक्त_pins;
	पूर्ण

	gsel = pinctrl_generic_add_group(pcs->pctl, np->name, pins, found, pcs);
	अगर (gsel < 0) अणु
		res = gsel;
		जाओ मुक्त_function;
	पूर्ण

	(*map)->type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)->data.mux.group = np->name;
	(*map)->data.mux.function = np->name;

	अगर (PCS_HAS_PINCONF && function) अणु
		res = pcs_parse_pinconf(pcs, np, function, map);
		अगर (res == 0)
			*num_maps = 2;
		अन्यथा अगर (res == -ENOTSUPP)
			*num_maps = 1;
		अन्यथा
			जाओ मुक्त_pingroups;
	पूर्ण अन्यथा अणु
		*num_maps = 1;
	पूर्ण
	mutex_unlock(&pcs->mutex);

	वापस 0;

मुक्त_pingroups:
	pinctrl_generic_हटाओ_group(pcs->pctl, gsel);
	*num_maps = 1;
मुक्त_function:
	pinmux_generic_हटाओ_function(pcs->pctl, fsel);
मुक्त_pins:
	mutex_unlock(&pcs->mutex);
	devm_kमुक्त(pcs->dev, pins);

मुक्त_vals:
	devm_kमुक्त(pcs->dev, vals);

	वापस res;
पूर्ण

अटल पूर्णांक pcs_parse_bits_in_pinctrl_entry(काष्ठा pcs_device *pcs,
						काष्ठा device_node *np,
						काष्ठा pinctrl_map **map,
						अचिन्हित *num_maps,
						स्थिर अक्षर **pgnames)
अणु
	स्थिर अक्षर *name = "pinctrl-single,bits";
	काष्ठा pcs_func_vals *vals;
	पूर्णांक rows, *pins, found = 0, res = -ENOMEM, i, fsel, gsel;
	पूर्णांक npins_in_row;
	काष्ठा pcs_function *function = शून्य;

	rows = pinctrl_count_index_with_args(np, name);
	अगर (rows <= 0) अणु
		dev_err(pcs->dev, "Invalid number of rows: %d\n", rows);
		वापस -EINVAL;
	पूर्ण

	npins_in_row = pcs->width / pcs->bits_per_pin;

	vals = devm_kzalloc(pcs->dev,
			    array3_size(rows, npins_in_row, माप(*vals)),
			    GFP_KERNEL);
	अगर (!vals)
		वापस -ENOMEM;

	pins = devm_kzalloc(pcs->dev,
			    array3_size(rows, npins_in_row, माप(*pins)),
			    GFP_KERNEL);
	अगर (!pins)
		जाओ मुक्त_vals;

	क्रम (i = 0; i < rows; i++) अणु
		काष्ठा of_phandle_args pinctrl_spec;
		अचिन्हित offset, val;
		अचिन्हित mask, bit_pos, val_pos, mask_pos, submask;
		अचिन्हित pin_num_from_lsb;
		पूर्णांक pin;

		res = pinctrl_parse_index_with_args(np, name, i, &pinctrl_spec);
		अगर (res)
			वापस res;

		अगर (pinctrl_spec.args_count < 3) अणु
			dev_err(pcs->dev, "invalid args_count for spec: %i\n",
				pinctrl_spec.args_count);
			अवरोध;
		पूर्ण

		/* Index plus two value cells */
		offset = pinctrl_spec.args[0];
		val = pinctrl_spec.args[1];
		mask = pinctrl_spec.args[2];

		dev_dbg(pcs->dev, "%pOFn index: 0x%x value: 0x%x mask: 0x%x\n",
			pinctrl_spec.np, offset, val, mask);

		/* Parse pins in each row from LSB */
		जबतक (mask) अणु
			bit_pos = __ffs(mask);
			pin_num_from_lsb = bit_pos / pcs->bits_per_pin;
			mask_pos = ((pcs->fmask) << bit_pos);
			val_pos = val & mask_pos;
			submask = mask & mask_pos;

			अगर ((mask & mask_pos) == 0) अणु
				dev_err(pcs->dev,
					"Invalid mask for %pOFn at 0x%x\n",
					np, offset);
				अवरोध;
			पूर्ण

			mask &= ~mask_pos;

			अगर (submask != mask_pos) अणु
				dev_warn(pcs->dev,
						"Invalid submask 0x%x for %pOFn at 0x%x\n",
						submask, np, offset);
				जारी;
			पूर्ण

			vals[found].mask = submask;
			vals[found].reg = pcs->base + offset;
			vals[found].val = val_pos;

			pin = pcs_get_pin_by_offset(pcs, offset);
			अगर (pin < 0) अणु
				dev_err(pcs->dev,
					"could not add functions for %pOFn %ux\n",
					np, offset);
				अवरोध;
			पूर्ण
			pins[found++] = pin + pin_num_from_lsb;
		पूर्ण
	पूर्ण

	pgnames[0] = np->name;
	mutex_lock(&pcs->mutex);
	fsel = pcs_add_function(pcs, &function, np->name, vals, found,
				pgnames, 1);
	अगर (fsel < 0) अणु
		res = fsel;
		जाओ मुक्त_pins;
	पूर्ण

	gsel = pinctrl_generic_add_group(pcs->pctl, np->name, pins, found, pcs);
	अगर (gsel < 0) अणु
		res = gsel;
		जाओ मुक्त_function;
	पूर्ण

	(*map)->type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)->data.mux.group = np->name;
	(*map)->data.mux.function = np->name;

	अगर (PCS_HAS_PINCONF) अणु
		dev_err(pcs->dev, "pinconf not supported\n");
		जाओ मुक्त_pingroups;
	पूर्ण

	*num_maps = 1;
	mutex_unlock(&pcs->mutex);

	वापस 0;

मुक्त_pingroups:
	pinctrl_generic_हटाओ_group(pcs->pctl, gsel);
	*num_maps = 1;
मुक्त_function:
	pinmux_generic_हटाओ_function(pcs->pctl, fsel);
मुक्त_pins:
	mutex_unlock(&pcs->mutex);
	devm_kमुक्त(pcs->dev, pins);

मुक्त_vals:
	devm_kमुक्त(pcs->dev, vals);

	वापस res;
पूर्ण
/**
 * pcs_dt_node_to_map() - allocates and parses pinctrl maps
 * @pctldev: pinctrl instance
 * @np_config: device tree pinmux entry
 * @map: array of map entries
 * @num_maps: number of maps
 */
अटल पूर्णांक pcs_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा device_node *np_config,
				काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा pcs_device *pcs;
	स्थिर अक्षर **pgnames;
	पूर्णांक ret;

	pcs = pinctrl_dev_get_drvdata(pctldev);

	/* create 2 maps. One is क्रम pinmux, and the other is क्रम pinconf. */
	*map = devm_kसुस्मृति(pcs->dev, 2, माप(**map), GFP_KERNEL);
	अगर (!*map)
		वापस -ENOMEM;

	*num_maps = 0;

	pgnames = devm_kzalloc(pcs->dev, माप(*pgnames), GFP_KERNEL);
	अगर (!pgnames) अणु
		ret = -ENOMEM;
		जाओ मुक्त_map;
	पूर्ण

	अगर (pcs->bits_per_mux) अणु
		ret = pcs_parse_bits_in_pinctrl_entry(pcs, np_config, map,
				num_maps, pgnames);
		अगर (ret < 0) अणु
			dev_err(pcs->dev, "no pins entries for %pOFn\n",
				np_config);
			जाओ मुक्त_pgnames;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = pcs_parse_one_pinctrl_entry(pcs, np_config, map,
				num_maps, pgnames);
		अगर (ret < 0) अणु
			dev_err(pcs->dev, "no pins entries for %pOFn\n",
				np_config);
			जाओ मुक्त_pgnames;
		पूर्ण
	पूर्ण

	वापस 0;

मुक्त_pgnames:
	devm_kमुक्त(pcs->dev, pgnames);
मुक्त_map:
	devm_kमुक्त(pcs->dev, *map);

	वापस ret;
पूर्ण

/**
 * pcs_irq_मुक्त() - मुक्त पूर्णांकerrupt
 * @pcs: pcs driver instance
 */
अटल व्योम pcs_irq_मुक्त(काष्ठा pcs_device *pcs)
अणु
	काष्ठा pcs_soc_data *pcs_soc = &pcs->socdata;

	अगर (pcs_soc->irq < 0)
		वापस;

	अगर (pcs->करोमुख्य)
		irq_करोमुख्य_हटाओ(pcs->करोमुख्य);

	अगर (PCS_QUIRK_HAS_SHARED_IRQ)
		मुक्त_irq(pcs_soc->irq, pcs_soc);
	अन्यथा
		irq_set_chained_handler(pcs_soc->irq, शून्य);
पूर्ण

/**
 * pcs_मुक्त_resources() - मुक्त memory used by this driver
 * @pcs: pcs driver instance
 */
अटल व्योम pcs_मुक्त_resources(काष्ठा pcs_device *pcs)
अणु
	pcs_irq_मुक्त(pcs);
	pinctrl_unरेजिस्टर(pcs->pctl);

#अगर IS_BUILTIN(CONFIG_PINCTRL_SINGLE)
	अगर (pcs->missing_nr_pinctrl_cells)
		of_हटाओ_property(pcs->np, pcs->missing_nr_pinctrl_cells);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक pcs_add_gpio_func(काष्ठा device_node *node, काष्ठा pcs_device *pcs)
अणु
	स्थिर अक्षर *propname = "pinctrl-single,gpio-range";
	स्थिर अक्षर *cellname = "#pinctrl-single,gpio-range-cells";
	काष्ठा of_phandle_args gpiospec;
	काष्ठा pcs_gpiofunc_range *range;
	पूर्णांक ret, i;

	क्रम (i = 0; ; i++) अणु
		ret = of_parse_phandle_with_args(node, propname, cellname,
						 i, &gpiospec);
		/* Do not treat it as error. Only treat it as end condition. */
		अगर (ret) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		range = devm_kzalloc(pcs->dev, माप(*range), GFP_KERNEL);
		अगर (!range) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		range->offset = gpiospec.args[0];
		range->npins = gpiospec.args[1];
		range->gpiofunc = gpiospec.args[2];
		mutex_lock(&pcs->mutex);
		list_add_tail(&range->node, &pcs->gpiofuncs);
		mutex_unlock(&pcs->mutex);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * काष्ठा pcs_पूर्णांकerrupt
 * @reg:	भव address of पूर्णांकerrupt रेजिस्टर
 * @hwirq:	hardware irq number
 * @irq:	भव irq number
 * @node:	list node
 */
काष्ठा pcs_पूर्णांकerrupt अणु
	व्योम __iomem *reg;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक irq;
	काष्ठा list_head node;
पूर्ण;

/**
 * pcs_irq_set() - enables or disables an पूर्णांकerrupt
 * @pcs_soc: SoC specअगरic settings
 * @irq: पूर्णांकerrupt
 * @enable: enable or disable the पूर्णांकerrupt
 *
 * Note that this currently assumes one पूर्णांकerrupt per pinctrl
 * रेजिस्टर that is typically used क्रम wake-up events.
 */
अटल अंतरभूत व्योम pcs_irq_set(काष्ठा pcs_soc_data *pcs_soc,
			       पूर्णांक irq, स्थिर bool enable)
अणु
	काष्ठा pcs_device *pcs;
	काष्ठा list_head *pos;
	अचिन्हित mask;

	pcs = container_of(pcs_soc, काष्ठा pcs_device, socdata);
	list_क्रम_each(pos, &pcs->irqs) अणु
		काष्ठा pcs_पूर्णांकerrupt *pcswi;
		अचिन्हित soc_mask;

		pcswi = list_entry(pos, काष्ठा pcs_पूर्णांकerrupt, node);
		अगर (irq != pcswi->irq)
			जारी;

		soc_mask = pcs_soc->irq_enable_mask;
		raw_spin_lock(&pcs->lock);
		mask = pcs->पढ़ो(pcswi->reg);
		अगर (enable)
			mask |= soc_mask;
		अन्यथा
			mask &= ~soc_mask;
		pcs->ग_लिखो(mask, pcswi->reg);

		/* flush posted ग_लिखो */
		mask = pcs->पढ़ो(pcswi->reg);
		raw_spin_unlock(&pcs->lock);
	पूर्ण

	अगर (pcs_soc->rearm)
		pcs_soc->rearm();
पूर्ण

/**
 * pcs_irq_mask() - mask pinctrl पूर्णांकerrupt
 * @d: पूर्णांकerrupt data
 */
अटल व्योम pcs_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा pcs_soc_data *pcs_soc = irq_data_get_irq_chip_data(d);

	pcs_irq_set(pcs_soc, d->irq, false);
पूर्ण

/**
 * pcs_irq_unmask() - unmask pinctrl पूर्णांकerrupt
 * @d: पूर्णांकerrupt data
 */
अटल व्योम pcs_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा pcs_soc_data *pcs_soc = irq_data_get_irq_chip_data(d);

	pcs_irq_set(pcs_soc, d->irq, true);
पूर्ण

/**
 * pcs_irq_set_wake() - toggle the suspend and resume wake up
 * @d: पूर्णांकerrupt data
 * @state: wake-up state
 *
 * Note that this should be called only क्रम suspend and resume.
 * For runसमय PM, the wake-up events should be enabled by शेष.
 */
अटल पूर्णांक pcs_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक state)
अणु
	अगर (state)
		pcs_irq_unmask(d);
	अन्यथा
		pcs_irq_mask(d);

	वापस 0;
पूर्ण

/**
 * pcs_irq_handle() - common पूर्णांकerrupt handler
 * @pcs_soc: SoC specअगरic settings
 *
 * Note that this currently assumes we have one पूर्णांकerrupt bit per
 * mux रेजिस्टर. This पूर्णांकerrupt is typically used क्रम wake-up events.
 * For more complex पूर्णांकerrupts dअगरferent handlers can be specअगरied.
 */
अटल पूर्णांक pcs_irq_handle(काष्ठा pcs_soc_data *pcs_soc)
अणु
	काष्ठा pcs_device *pcs;
	काष्ठा list_head *pos;
	पूर्णांक count = 0;

	pcs = container_of(pcs_soc, काष्ठा pcs_device, socdata);
	list_क्रम_each(pos, &pcs->irqs) अणु
		काष्ठा pcs_पूर्णांकerrupt *pcswi;
		अचिन्हित mask;

		pcswi = list_entry(pos, काष्ठा pcs_पूर्णांकerrupt, node);
		raw_spin_lock(&pcs->lock);
		mask = pcs->पढ़ो(pcswi->reg);
		raw_spin_unlock(&pcs->lock);
		अगर (mask & pcs_soc->irq_status_mask) अणु
			generic_handle_irq(irq_find_mapping(pcs->करोमुख्य,
							    pcswi->hwirq));
			count++;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/**
 * pcs_irq_handler() - handler क्रम the shared पूर्णांकerrupt हाल
 * @irq: पूर्णांकerrupt
 * @d: data
 *
 * Use this क्रम हालs where multiple instances of
 * pinctrl-single share a single पूर्णांकerrupt like on omaps.
 */
अटल irqवापस_t pcs_irq_handler(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा pcs_soc_data *pcs_soc = d;

	वापस pcs_irq_handle(pcs_soc) ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/**
 * pcs_irq_handle() - handler क्रम the dedicated chained पूर्णांकerrupt हाल
 * @desc: पूर्णांकerrupt descriptor
 *
 * Use this अगर you have a separate पूर्णांकerrupt क्रम each
 * pinctrl-single instance.
 */
अटल व्योम pcs_irq_chain_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा pcs_soc_data *pcs_soc = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip;

	chip = irq_desc_get_chip(desc);
	chained_irq_enter(chip, desc);
	pcs_irq_handle(pcs_soc);
	/* REVISIT: export and add handle_bad_irq(irq, desc)? */
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक pcs_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hwirq)
अणु
	काष्ठा pcs_soc_data *pcs_soc = d->host_data;
	काष्ठा pcs_device *pcs;
	काष्ठा pcs_पूर्णांकerrupt *pcswi;

	pcs = container_of(pcs_soc, काष्ठा pcs_device, socdata);
	pcswi = devm_kzalloc(pcs->dev, माप(*pcswi), GFP_KERNEL);
	अगर (!pcswi)
		वापस -ENOMEM;

	pcswi->reg = pcs->base + hwirq;
	pcswi->hwirq = hwirq;
	pcswi->irq = irq;

	mutex_lock(&pcs->mutex);
	list_add_tail(&pcswi->node, &pcs->irqs);
	mutex_unlock(&pcs->mutex);

	irq_set_chip_data(irq, pcs_soc);
	irq_set_chip_and_handler(irq, &pcs->chip,
				 handle_level_irq);
	irq_set_lockdep_class(irq, &pcs_lock_class, &pcs_request_class);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pcs_irqकरोमुख्य_ops = अणु
	.map = pcs_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

/**
 * pcs_irq_init_chained_handler() - set up a chained पूर्णांकerrupt handler
 * @pcs: pcs driver instance
 * @np: device node poपूर्णांकer
 */
अटल पूर्णांक pcs_irq_init_chained_handler(काष्ठा pcs_device *pcs,
					काष्ठा device_node *np)
अणु
	काष्ठा pcs_soc_data *pcs_soc = &pcs->socdata;
	स्थिर अक्षर *name = "pinctrl";
	पूर्णांक num_irqs;

	अगर (!pcs_soc->irq_enable_mask ||
	    !pcs_soc->irq_status_mask) अणु
		pcs_soc->irq = -1;
		वापस -EINVAL;
	पूर्ण

	INIT_LIST_HEAD(&pcs->irqs);
	pcs->chip.name = name;
	pcs->chip.irq_ack = pcs_irq_mask;
	pcs->chip.irq_mask = pcs_irq_mask;
	pcs->chip.irq_unmask = pcs_irq_unmask;
	pcs->chip.irq_set_wake = pcs_irq_set_wake;

	अगर (PCS_QUIRK_HAS_SHARED_IRQ) अणु
		पूर्णांक res;

		res = request_irq(pcs_soc->irq, pcs_irq_handler,
				  IRQF_SHARED | IRQF_NO_SUSPEND |
				  IRQF_NO_THREAD,
				  name, pcs_soc);
		अगर (res) अणु
			pcs_soc->irq = -1;
			वापस res;
		पूर्ण
	पूर्ण अन्यथा अणु
		irq_set_chained_handler_and_data(pcs_soc->irq,
						 pcs_irq_chain_handler,
						 pcs_soc);
	पूर्ण

	/*
	 * We can use the रेजिस्टर offset as the hardirq
	 * number as irq_करोमुख्य_add_simple maps them lazily.
	 * This way we can easily support more than one
	 * पूर्णांकerrupt per function अगर needed.
	 */
	num_irqs = pcs->size;

	pcs->करोमुख्य = irq_करोमुख्य_add_simple(np, num_irqs, 0,
					    &pcs_irqकरोमुख्य_ops,
					    pcs_soc);
	अगर (!pcs->करोमुख्य) अणु
		irq_set_chained_handler(pcs_soc->irq, शून्य);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pcs_save_context(काष्ठा pcs_device *pcs)
अणु
	पूर्णांक i, mux_bytes;
	u64 *regsl;
	u32 *regsw;
	u16 *regshw;

	mux_bytes = pcs->width / BITS_PER_BYTE;

	अगर (!pcs->saved_vals) अणु
		pcs->saved_vals = devm_kzalloc(pcs->dev, pcs->size, GFP_ATOMIC);
		अगर (!pcs->saved_vals)
			वापस -ENOMEM;
	पूर्ण

	चयन (pcs->width) अणु
	हाल 64:
		regsl = pcs->saved_vals;
		क्रम (i = 0; i < pcs->size; i += mux_bytes)
			*regsl++ = pcs->पढ़ो(pcs->base + i);
		अवरोध;
	हाल 32:
		regsw = pcs->saved_vals;
		क्रम (i = 0; i < pcs->size; i += mux_bytes)
			*regsw++ = pcs->पढ़ो(pcs->base + i);
		अवरोध;
	हाल 16:
		regshw = pcs->saved_vals;
		क्रम (i = 0; i < pcs->size; i += mux_bytes)
			*regshw++ = pcs->पढ़ो(pcs->base + i);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pcs_restore_context(काष्ठा pcs_device *pcs)
अणु
	पूर्णांक i, mux_bytes;
	u64 *regsl;
	u32 *regsw;
	u16 *regshw;

	mux_bytes = pcs->width / BITS_PER_BYTE;

	चयन (pcs->width) अणु
	हाल 64:
		regsl = pcs->saved_vals;
		क्रम (i = 0; i < pcs->size; i += mux_bytes)
			pcs->ग_लिखो(*regsl++, pcs->base + i);
		अवरोध;
	हाल 32:
		regsw = pcs->saved_vals;
		क्रम (i = 0; i < pcs->size; i += mux_bytes)
			pcs->ग_लिखो(*regsw++, pcs->base + i);
		अवरोध;
	हाल 16:
		regshw = pcs->saved_vals;
		क्रम (i = 0; i < pcs->size; i += mux_bytes)
			pcs->ग_लिखो(*regshw++, pcs->base + i);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pinctrl_single_suspend(काष्ठा platक्रमm_device *pdev,
					pm_message_t state)
अणु
	काष्ठा pcs_device *pcs;

	pcs = platक्रमm_get_drvdata(pdev);
	अगर (!pcs)
		वापस -EINVAL;

	अगर (pcs->flags & PCS_CONTEXT_LOSS_OFF) अणु
		पूर्णांक ret;

		ret = pcs_save_context(pcs);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस pinctrl_क्रमce_sleep(pcs->pctl);
पूर्ण

अटल पूर्णांक pinctrl_single_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcs_device *pcs;

	pcs = platक्रमm_get_drvdata(pdev);
	अगर (!pcs)
		वापस -EINVAL;

	अगर (pcs->flags & PCS_CONTEXT_LOSS_OFF)
		pcs_restore_context(pcs);

	वापस pinctrl_क्रमce_शेष(pcs->pctl);
पूर्ण
#पूर्ण_अगर

/**
 * pcs_quirk_missing_pinctrl_cells - handle legacy binding
 * @pcs: pinctrl driver instance
 * @np: device tree node
 * @cells: number of cells
 *
 * Handle legacy binding with no #pinctrl-cells. This should be
 * always two pinctrl-single,bit-per-mux and one क्रम others.
 * At some poपूर्णांक we may want to consider removing this.
 */
अटल पूर्णांक pcs_quirk_missing_pinctrl_cells(काष्ठा pcs_device *pcs,
					   काष्ठा device_node *np,
					   पूर्णांक cells)
अणु
	काष्ठा property *p;
	स्थिर अक्षर *name = "#pinctrl-cells";
	पूर्णांक error;
	u32 val;

	error = of_property_पढ़ो_u32(np, name, &val);
	अगर (!error)
		वापस 0;

	dev_warn(pcs->dev, "please update dts to use %s = <%i>\n",
		 name, cells);

	p = devm_kzalloc(pcs->dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->length = माप(__be32);
	p->value = devm_kzalloc(pcs->dev, माप(__be32), GFP_KERNEL);
	अगर (!p->value)
		वापस -ENOMEM;
	*(__be32 *)p->value = cpu_to_be32(cells);

	p->name = devm_kstrdup(pcs->dev, name, GFP_KERNEL);
	अगर (!p->name)
		वापस -ENOMEM;

	pcs->missing_nr_pinctrl_cells = p;

#अगर IS_BUILTIN(CONFIG_PINCTRL_SINGLE)
	error = of_add_property(np, pcs->missing_nr_pinctrl_cells);
#पूर्ण_अगर

	वापस error;
पूर्ण

अटल पूर्णांक pcs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा pcs_pdata *pdata;
	काष्ठा resource *res;
	काष्ठा pcs_device *pcs;
	स्थिर काष्ठा pcs_soc_data *soc;
	पूर्णांक ret;

	soc = of_device_get_match_data(&pdev->dev);
	अगर (WARN_ON(!soc))
		वापस -EINVAL;

	pcs = devm_kzalloc(&pdev->dev, माप(*pcs), GFP_KERNEL);
	अगर (!pcs)
		वापस -ENOMEM;

	pcs->dev = &pdev->dev;
	pcs->np = np;
	raw_spin_lock_init(&pcs->lock);
	mutex_init(&pcs->mutex);
	INIT_LIST_HEAD(&pcs->gpiofuncs);
	pcs->flags = soc->flags;
	स_नकल(&pcs->socdata, soc, माप(*soc));

	ret = of_property_पढ़ो_u32(np, "pinctrl-single,register-width",
				   &pcs->width);
	अगर (ret) अणु
		dev_err(pcs->dev, "register width not specified\n");

		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "pinctrl-single,function-mask",
				   &pcs->fmask);
	अगर (!ret) अणु
		pcs->fshअगरt = __ffs(pcs->fmask);
		pcs->fmax = pcs->fmask >> pcs->fshअगरt;
	पूर्ण अन्यथा अणु
		/* If mask property करोesn't exist, function mux is invalid. */
		pcs->fmask = 0;
		pcs->fshअगरt = 0;
		pcs->fmax = 0;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "pinctrl-single,function-off",
					&pcs->foff);
	अगर (ret)
		pcs->foff = PCS_OFF_DISABLED;

	pcs->bits_per_mux = of_property_पढ़ो_bool(np,
						  "pinctrl-single,bit-per-mux");
	ret = pcs_quirk_missing_pinctrl_cells(pcs, np,
					      pcs->bits_per_mux ? 2 : 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to patch #pinctrl-cells\n");

		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(pcs->dev, "could not get resource\n");
		वापस -ENODEV;
	पूर्ण

	pcs->res = devm_request_mem_region(pcs->dev, res->start,
			resource_size(res), DRIVER_NAME);
	अगर (!pcs->res) अणु
		dev_err(pcs->dev, "could not get mem_region\n");
		वापस -EBUSY;
	पूर्ण

	pcs->size = resource_size(pcs->res);
	pcs->base = devm_ioremap(pcs->dev, pcs->res->start, pcs->size);
	अगर (!pcs->base) अणु
		dev_err(pcs->dev, "could not ioremap\n");
		वापस -ENODEV;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pcs);

	चयन (pcs->width) अणु
	हाल 8:
		pcs->पढ़ो = pcs_पढ़ोb;
		pcs->ग_लिखो = pcs_ग_लिखोb;
		अवरोध;
	हाल 16:
		pcs->पढ़ो = pcs_पढ़ोw;
		pcs->ग_लिखो = pcs_ग_लिखोw;
		अवरोध;
	हाल 32:
		pcs->पढ़ो = pcs_पढ़ोl;
		pcs->ग_लिखो = pcs_ग_लिखोl;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	pcs->desc.name = DRIVER_NAME;
	pcs->desc.pctlops = &pcs_pinctrl_ops;
	pcs->desc.pmxops = &pcs_pinmux_ops;
	अगर (PCS_HAS_PINCONF)
		pcs->desc.confops = &pcs_pinconf_ops;
	pcs->desc.owner = THIS_MODULE;

	ret = pcs_allocate_pin_table(pcs);
	अगर (ret < 0)
		जाओ मुक्त;

	ret = pinctrl_रेजिस्टर_and_init(&pcs->desc, pcs->dev, pcs, &pcs->pctl);
	अगर (ret) अणु
		dev_err(pcs->dev, "could not register single pinctrl driver\n");
		जाओ मुक्त;
	पूर्ण

	ret = pcs_add_gpio_func(np, pcs);
	अगर (ret < 0)
		जाओ मुक्त;

	pcs->socdata.irq = irq_of_parse_and_map(np, 0);
	अगर (pcs->socdata.irq)
		pcs->flags |= PCS_FEAT_IRQ;

	/* We still need auxdata क्रम some omaps क्रम PRM पूर्णांकerrupts */
	pdata = dev_get_platdata(&pdev->dev);
	अगर (pdata) अणु
		अगर (pdata->rearm)
			pcs->socdata.rearm = pdata->rearm;
		अगर (pdata->irq) अणु
			pcs->socdata.irq = pdata->irq;
			pcs->flags |= PCS_FEAT_IRQ;
		पूर्ण
	पूर्ण

	अगर (PCS_HAS_IRQ) अणु
		ret = pcs_irq_init_chained_handler(pcs, np);
		अगर (ret < 0)
			dev_warn(pcs->dev, "initialized with no interrupts\n");
	पूर्ण

	dev_info(pcs->dev, "%i pins, size %u\n", pcs->desc.npins, pcs->size);

	वापस pinctrl_enable(pcs->pctl);

मुक्त:
	pcs_मुक्त_resources(pcs);

	वापस ret;
पूर्ण

अटल पूर्णांक pcs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcs_device *pcs = platक्रमm_get_drvdata(pdev);

	अगर (!pcs)
		वापस 0;

	pcs_मुक्त_resources(pcs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcs_soc_data pinctrl_single_omap_wkup = अणु
	.flags = PCS_QUIRK_SHARED_IRQ,
	.irq_enable_mask = (1 << 14),	/* OMAP_WAKEUP_EN */
	.irq_status_mask = (1 << 15),	/* OMAP_WAKEUP_EVENT */
पूर्ण;

अटल स्थिर काष्ठा pcs_soc_data pinctrl_single_dra7 = अणु
	.irq_enable_mask = (1 << 24),	/* WAKEUPENABLE */
	.irq_status_mask = (1 << 25),	/* WAKEUPEVENT */
पूर्ण;

अटल स्थिर काष्ठा pcs_soc_data pinctrl_single_am437x = अणु
	.flags = PCS_QUIRK_SHARED_IRQ | PCS_CONTEXT_LOSS_OFF,
	.irq_enable_mask = (1 << 29),   /* OMAP_WAKEUP_EN */
	.irq_status_mask = (1 << 30),   /* OMAP_WAKEUP_EVENT */
पूर्ण;

अटल स्थिर काष्ठा pcs_soc_data pinctrl_single = अणु
पूर्ण;

अटल स्थिर काष्ठा pcs_soc_data pinconf_single = अणु
	.flags = PCS_FEAT_PINCONF,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pcs_of_match[] = अणु
	अणु .compatible = "ti,omap3-padconf", .data = &pinctrl_single_omap_wkup पूर्ण,
	अणु .compatible = "ti,omap4-padconf", .data = &pinctrl_single_omap_wkup पूर्ण,
	अणु .compatible = "ti,omap5-padconf", .data = &pinctrl_single_omap_wkup पूर्ण,
	अणु .compatible = "ti,dra7-padconf", .data = &pinctrl_single_dra7 पूर्ण,
	अणु .compatible = "ti,am437-padconf", .data = &pinctrl_single_am437x पूर्ण,
	अणु .compatible = "pinctrl-single", .data = &pinctrl_single पूर्ण,
	अणु .compatible = "pinconf-single", .data = &pinconf_single पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pcs_of_match);

अटल काष्ठा platक्रमm_driver pcs_driver = अणु
	.probe		= pcs_probe,
	.हटाओ		= pcs_हटाओ,
	.driver = अणु
		.name		= DRIVER_NAME,
		.of_match_table	= pcs_of_match,
	पूर्ण,
#अगर_घोषित CONFIG_PM
	.suspend = pinctrl_single_suspend,
	.resume = pinctrl_single_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(pcs_driver);

MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("One-register-per-pin type device tree based pinctrl driver");
MODULE_LICENSE("GPL v2");
