<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Core driver क्रम the imx pin controller
//
// Copyright (C) 2012 Freescale Semiconductor, Inc.
// Copyright (C) 2012 Linaro Ltd.
//
// Author: Dong Aisheng <करोng.aisheng@linaro.org>

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#समावेश "../core.h"
#समावेश "../pinconf.h"
#समावेश "../pinmux.h"
#समावेश "pinctrl-imx.h"

/* The bits in CONFIG cell defined in binding करोc*/
#घोषणा IMX_NO_PAD_CTL	0x80000000	/* no pin config need */
#घोषणा IMX_PAD_SION 0x40000000		/* set SION */

अटल अंतरभूत स्थिर काष्ठा group_desc *imx_pinctrl_find_group_by_name(
				काष्ठा pinctrl_dev *pctldev,
				स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा group_desc *grp = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < pctldev->num_groups; i++) अणु
		grp = pinctrl_generic_get_group(pctldev, i);
		अगर (grp && !म_भेद(grp->name, name))
			अवरोध;
	पूर्ण

	वापस grp;
पूर्ण

अटल व्योम imx_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
		   अचिन्हित offset)
अणु
	seq_म_लिखो(s, "%s", dev_name(pctldev->dev));
पूर्ण

अटल पूर्णांक imx_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
			काष्ठा device_node *np,
			काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	स्थिर काष्ठा group_desc *grp;
	काष्ठा pinctrl_map *new_map;
	काष्ठा device_node *parent;
	काष्ठा imx_pin *pin;
	पूर्णांक map_num = 1;
	पूर्णांक i, j;

	/*
	 * first find the group of this node and check अगर we need create
	 * config maps क्रम pins
	 */
	grp = imx_pinctrl_find_group_by_name(pctldev, np->name);
	अगर (!grp) अणु
		dev_err(ipctl->dev, "unable to find group for node %pOFn\n", np);
		वापस -EINVAL;
	पूर्ण

	अगर (info->flags & IMX_USE_SCU) अणु
		map_num += grp->num_pins;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < grp->num_pins; i++) अणु
			pin = &((काष्ठा imx_pin *)(grp->data))[i];
			अगर (!(pin->conf.mmio.config & IMX_NO_PAD_CTL))
				map_num++;
		पूर्ण
	पूर्ण

	new_map = kदो_स्मृति_array(map_num, माप(काष्ठा pinctrl_map),
				GFP_KERNEL);
	अगर (!new_map)
		वापस -ENOMEM;

	*map = new_map;
	*num_maps = map_num;

	/* create mux map */
	parent = of_get_parent(np);
	अगर (!parent) अणु
		kमुक्त(new_map);
		वापस -EINVAL;
	पूर्ण
	new_map[0].type = PIN_MAP_TYPE_MUX_GROUP;
	new_map[0].data.mux.function = parent->name;
	new_map[0].data.mux.group = np->name;
	of_node_put(parent);

	/* create config map */
	new_map++;
	क्रम (i = j = 0; i < grp->num_pins; i++) अणु
		pin = &((काष्ठा imx_pin *)(grp->data))[i];

		/*
		 * We only create config maps क्रम SCU pads or MMIO pads that
		 * are not using the शेष config(a.k.a IMX_NO_PAD_CTL)
		 */
		अगर (!(info->flags & IMX_USE_SCU) &&
		    (pin->conf.mmio.config & IMX_NO_PAD_CTL))
			जारी;

		new_map[j].type = PIN_MAP_TYPE_CONFIGS_PIN;
		new_map[j].data.configs.group_or_pin =
					pin_get_name(pctldev, pin->pin);

		अगर (info->flags & IMX_USE_SCU) अणु
			/*
			 * For SCU हाल, we set mux and conf together
			 * in one IPC call
			 */
			new_map[j].data.configs.configs =
					(अचिन्हित दीर्घ *)&pin->conf.scu;
			new_map[j].data.configs.num_configs = 2;
		पूर्ण अन्यथा अणु
			new_map[j].data.configs.configs =
					&pin->conf.mmio.config;
			new_map[j].data.configs.num_configs = 1;
		पूर्ण

		j++;
	पूर्ण

	dev_dbg(pctldev->dev, "maps: function %s group %s num %d\n",
		(*map)->data.mux.function, (*map)->data.mux.group, map_num);

	वापस 0;
पूर्ण

अटल व्योम imx_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops imx_pctrl_ops = अणु
	.get_groups_count = pinctrl_generic_get_group_count,
	.get_group_name = pinctrl_generic_get_group_name,
	.get_group_pins = pinctrl_generic_get_group_pins,
	.pin_dbg_show = imx_pin_dbg_show,
	.dt_node_to_map = imx_dt_node_to_map,
	.dt_मुक्त_map = imx_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक imx_pmx_set_one_pin_mmio(काष्ठा imx_pinctrl *ipctl,
				    काष्ठा imx_pin *pin)
अणु
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	काष्ठा imx_pin_mmio *pin_mmio = &pin->conf.mmio;
	स्थिर काष्ठा imx_pin_reg *pin_reg;
	अचिन्हित पूर्णांक pin_id;

	pin_id = pin->pin;
	pin_reg = &ipctl->pin_regs[pin_id];

	अगर (pin_reg->mux_reg == -1) अणु
		dev_dbg(ipctl->dev, "Pin(%s) does not support mux function\n",
			info->pins[pin_id].name);
		वापस 0;
	पूर्ण

	अगर (info->flags & SHARE_MUX_CONF_REG) अणु
		u32 reg;

		reg = पढ़ोl(ipctl->base + pin_reg->mux_reg);
		reg &= ~info->mux_mask;
		reg |= (pin_mmio->mux_mode << info->mux_shअगरt);
		ग_लिखोl(reg, ipctl->base + pin_reg->mux_reg);
		dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%x\n",
			pin_reg->mux_reg, reg);
	पूर्ण अन्यथा अणु
		ग_लिखोl(pin_mmio->mux_mode, ipctl->base + pin_reg->mux_reg);
		dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%x\n",
			pin_reg->mux_reg, pin_mmio->mux_mode);
	पूर्ण

	/*
	 * If the select input value begins with 0xff, it's a quirky
	 * select input and the value should be पूर्णांकerpreted as below.
	 *     31     23      15      7        0
	 *     | 0xff | shअगरt | width | select |
	 * It's used to work around the problem that the select
	 * input क्रम some pin is not implemented in the select
	 * input रेजिस्टर but in some general purpose रेजिस्टर.
	 * We encode the select input value, width and shअगरt of
	 * the bit field पूर्णांकo input_val cell of pin function ID
	 * in device tree, and then decode them here क्रम setting
	 * up the select input bits in general purpose रेजिस्टर.
	 */
	अगर (pin_mmio->input_val >> 24 == 0xff) अणु
		u32 val = pin_mmio->input_val;
		u8 select = val & 0xff;
		u8 width = (val >> 8) & 0xff;
		u8 shअगरt = (val >> 16) & 0xff;
		u32 mask = ((1 << width) - 1) << shअगरt;
		/*
		 * The input_reg[i] here is actually some IOMUXC general
		 * purpose रेजिस्टर, not regular select input रेजिस्टर.
		 */
		val = पढ़ोl(ipctl->base + pin_mmio->input_reg);
		val &= ~mask;
		val |= select << shअगरt;
		ग_लिखोl(val, ipctl->base + pin_mmio->input_reg);
	पूर्ण अन्यथा अगर (pin_mmio->input_reg) अणु
		/*
		 * Regular select input रेजिस्टर can never be at offset
		 * 0, and we only prपूर्णांक रेजिस्टर value क्रम regular हाल.
		 */
		अगर (ipctl->input_sel_base)
			ग_लिखोl(pin_mmio->input_val, ipctl->input_sel_base +
					pin_mmio->input_reg);
		अन्यथा
			ग_लिखोl(pin_mmio->input_val, ipctl->base +
					pin_mmio->input_reg);
		dev_dbg(ipctl->dev,
			"==>select_input: offset 0x%x val 0x%x\n",
			pin_mmio->input_reg, pin_mmio->input_val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_pmx_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
		       अचिन्हित group)
अणु
	काष्ठा imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	काष्ठा function_desc *func;
	काष्ठा group_desc *grp;
	काष्ठा imx_pin *pin;
	अचिन्हित पूर्णांक npins;
	पूर्णांक i, err;

	/*
	 * Configure the mux mode क्रम each pin in the group क्रम a specअगरic
	 * function.
	 */
	grp = pinctrl_generic_get_group(pctldev, group);
	अगर (!grp)
		वापस -EINVAL;

	func = pinmux_generic_get_function(pctldev, selector);
	अगर (!func)
		वापस -EINVAL;

	npins = grp->num_pins;

	dev_dbg(ipctl->dev, "enable function %s group %s\n",
		func->name, grp->name);

	क्रम (i = 0; i < npins; i++) अणु
		/*
		 * For IMX_USE_SCU हाल, we postpone the mux setting
		 * until config is set as we can set them together
		 * in one IPC call
		 */
		pin = &((काष्ठा imx_pin *)(grp->data))[i];
		अगर (!(info->flags & IMX_USE_SCU)) अणु
			err = imx_pmx_set_one_pin_mmio(ipctl, pin);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा pinmux_ops imx_pmx_ops = अणु
	.get_functions_count = pinmux_generic_get_function_count,
	.get_function_name = pinmux_generic_get_function_name,
	.get_function_groups = pinmux_generic_get_function_groups,
	.set_mux = imx_pmx_set,
पूर्ण;

/* decode generic config पूर्णांकo raw रेजिस्टर values */
अटल u32 imx_pinconf_decode_generic_config(काष्ठा imx_pinctrl *ipctl,
					      अचिन्हित दीर्घ *configs,
					      अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	स्थिर काष्ठा imx_cfg_params_decode *decode;
	क्रमागत pin_config_param param;
	u32 raw_config = 0;
	u32 param_val;
	पूर्णांक i, j;

	WARN_ON(num_configs > info->num_decodes);

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		param_val = pinconf_to_config_argument(configs[i]);
		decode = info->decodes;
		क्रम (j = 0; j < info->num_decodes; j++) अणु
			अगर (param == decode->param) अणु
				अगर (decode->invert)
					param_val = !param_val;
				raw_config |= (param_val << decode->shअगरt)
					      & decode->mask;
				अवरोध;
			पूर्ण
			decode++;
		पूर्ण
	पूर्ण

	अगर (info->fixup)
		info->fixup(configs, num_configs, &raw_config);

	वापस raw_config;
पूर्ण

अटल u32 imx_pinconf_parse_generic_config(काष्ठा device_node *np,
					    काष्ठा imx_pinctrl *ipctl)
अणु
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	काष्ठा pinctrl_dev *pctl = ipctl->pctl;
	अचिन्हित पूर्णांक num_configs;
	अचिन्हित दीर्घ *configs;
	पूर्णांक ret;

	अगर (!info->generic_pinconf)
		वापस 0;

	ret = pinconf_generic_parse_dt_config(np, pctl, &configs,
					      &num_configs);
	अगर (ret)
		वापस 0;

	वापस imx_pinconf_decode_generic_config(ipctl, configs, num_configs);
पूर्ण

अटल पूर्णांक imx_pinconf_get_mmio(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin_id,
				अचिन्हित दीर्घ *config)
अणु
	काष्ठा imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	स्थिर काष्ठा imx_pin_reg *pin_reg = &ipctl->pin_regs[pin_id];

	अगर (pin_reg->conf_reg == -1) अणु
		dev_err(ipctl->dev, "Pin(%s) does not support config function\n",
			info->pins[pin_id].name);
		वापस -EINVAL;
	पूर्ण

	*config = पढ़ोl(ipctl->base + pin_reg->conf_reg);

	अगर (info->flags & SHARE_MUX_CONF_REG)
		*config &= ~info->mux_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित pin_id, अचिन्हित दीर्घ *config)
अणु
	काष्ठा imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;

	अगर (info->flags & IMX_USE_SCU)
		वापस info->imx_pinconf_get(pctldev, pin_id, config);
	अन्यथा
		वापस imx_pinconf_get_mmio(pctldev, pin_id, config);
पूर्ण

अटल पूर्णांक imx_pinconf_set_mmio(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित pin_id, अचिन्हित दीर्घ *configs,
				अचिन्हित num_configs)
अणु
	काष्ठा imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	स्थिर काष्ठा imx_pin_reg *pin_reg = &ipctl->pin_regs[pin_id];
	पूर्णांक i;

	अगर (pin_reg->conf_reg == -1) अणु
		dev_err(ipctl->dev, "Pin(%s) does not support config function\n",
			info->pins[pin_id].name);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(ipctl->dev, "pinconf set pin %s\n",
		info->pins[pin_id].name);

	क्रम (i = 0; i < num_configs; i++) अणु
		अगर (info->flags & SHARE_MUX_CONF_REG) अणु
			u32 reg;
			reg = पढ़ोl(ipctl->base + pin_reg->conf_reg);
			reg &= info->mux_mask;
			reg |= configs[i];
			ग_लिखोl(reg, ipctl->base + pin_reg->conf_reg);
			dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%x\n",
				pin_reg->conf_reg, reg);
		पूर्ण अन्यथा अणु
			ग_लिखोl(configs[i], ipctl->base + pin_reg->conf_reg);
			dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%lx\n",
				pin_reg->conf_reg, configs[i]);
		पूर्ण
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल पूर्णांक imx_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित pin_id, अचिन्हित दीर्घ *configs,
			   अचिन्हित num_configs)
अणु
	काष्ठा imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;

	अगर (info->flags & IMX_USE_SCU)
		वापस info->imx_pinconf_set(pctldev, pin_id,
					   configs, num_configs);
	अन्यथा
		वापस imx_pinconf_set_mmio(pctldev, pin_id,
					    configs, num_configs);
पूर्ण

अटल व्योम imx_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा seq_file *s, अचिन्हित pin_id)
अणु
	काष्ठा imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	स्थिर काष्ठा imx_pin_reg *pin_reg;
	अचिन्हित दीर्घ config;
	पूर्णांक ret;

	अगर (info->flags & IMX_USE_SCU) अणु
		ret = info->imx_pinconf_get(pctldev, pin_id, &config);
		अगर (ret) अणु
			dev_err(ipctl->dev, "failed to get %s pinconf\n",
				pin_get_name(pctldev, pin_id));
			seq_माला_दो(s, "N/A");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		pin_reg = &ipctl->pin_regs[pin_id];
		अगर (pin_reg->conf_reg == -1) अणु
			seq_माला_दो(s, "N/A");
			वापस;
		पूर्ण

		config = पढ़ोl(ipctl->base + pin_reg->conf_reg);
	पूर्ण

	seq_म_लिखो(s, "0x%lx", config);
पूर्ण

अटल व्योम imx_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
					 काष्ठा seq_file *s, अचिन्हित group)
अणु
	काष्ठा group_desc *grp;
	अचिन्हित दीर्घ config;
	स्थिर अक्षर *name;
	पूर्णांक i, ret;

	अगर (group >= pctldev->num_groups)
		वापस;

	seq_माला_दो(s, "\n");
	grp = pinctrl_generic_get_group(pctldev, group);
	अगर (!grp)
		वापस;

	क्रम (i = 0; i < grp->num_pins; i++) अणु
		काष्ठा imx_pin *pin = &((काष्ठा imx_pin *)(grp->data))[i];

		name = pin_get_name(pctldev, pin->pin);
		ret = imx_pinconf_get(pctldev, pin->pin, &config);
		अगर (ret)
			वापस;
		seq_म_लिखो(s, "  %s: 0x%lx\n", name, config);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops imx_pinconf_ops = अणु
	.pin_config_get = imx_pinconf_get,
	.pin_config_set = imx_pinconf_set,
	.pin_config_dbg_show = imx_pinconf_dbg_show,
	.pin_config_group_dbg_show = imx_pinconf_group_dbg_show,
पूर्ण;

/*
 * Each pin represented in fsl,pins consists of a number of u32 PIN_FUNC_ID
 * and 1 u32 CONFIG, the total size is PIN_FUNC_ID + CONFIG क्रम each pin.
 * For generic_pinconf हाल, there's no extra u32 CONFIG.
 *
 * PIN_FUNC_ID क्रमmat:
 * Default:
 *     <mux_reg conf_reg input_reg mux_mode input_val>
 * SHARE_MUX_CONF_REG:
 *     <mux_conf_reg input_reg mux_mode input_val>
 * IMX_USE_SCU:
 *	<pin_id mux_mode>
 */
#घोषणा FSL_PIN_SIZE 24
#घोषणा FSL_PIN_SHARE_SIZE 20
#घोषणा FSL_SCU_PIN_SIZE 12

अटल व्योम imx_pinctrl_parse_pin_mmio(काष्ठा imx_pinctrl *ipctl,
				       अचिन्हित पूर्णांक *pin_id, काष्ठा imx_pin *pin,
				       स्थिर __be32 **list_p,
				       काष्ठा device_node *np)
अणु
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	काष्ठा imx_pin_mmio *pin_mmio = &pin->conf.mmio;
	काष्ठा imx_pin_reg *pin_reg;
	स्थिर __be32 *list = *list_p;
	u32 mux_reg, conf_reg;
	u32 config;

	mux_reg = be32_to_cpu(*list++);

	अगर (!(info->flags & ZERO_OFFSET_VALID) && !mux_reg)
		mux_reg = -1;

	अगर (info->flags & SHARE_MUX_CONF_REG) अणु
		conf_reg = mux_reg;
	पूर्ण अन्यथा अणु
		conf_reg = be32_to_cpu(*list++);
		अगर (!conf_reg)
			conf_reg = -1;
	पूर्ण

	*pin_id = (mux_reg != -1) ? mux_reg / 4 : conf_reg / 4;
	pin_reg = &ipctl->pin_regs[*pin_id];
	pin->pin = *pin_id;
	pin_reg->mux_reg = mux_reg;
	pin_reg->conf_reg = conf_reg;
	pin_mmio->input_reg = be32_to_cpu(*list++);
	pin_mmio->mux_mode = be32_to_cpu(*list++);
	pin_mmio->input_val = be32_to_cpu(*list++);

	अगर (info->generic_pinconf) अणु
		/* generic pin config decoded */
		pin_mmio->config = imx_pinconf_parse_generic_config(np, ipctl);
	पूर्ण अन्यथा अणु
		/* legacy pin config पढ़ो from devicetree */
		config = be32_to_cpu(*list++);

		/* SION bit is in mux रेजिस्टर */
		अगर (config & IMX_PAD_SION)
			pin_mmio->mux_mode |= IOMUXC_CONFIG_SION;
		pin_mmio->config = config & ~IMX_PAD_SION;
	पूर्ण

	*list_p = list;

	dev_dbg(ipctl->dev, "%s: 0x%x 0x%08lx", info->pins[*pin_id].name,
			     pin_mmio->mux_mode, pin_mmio->config);
पूर्ण

अटल पूर्णांक imx_pinctrl_parse_groups(काष्ठा device_node *np,
				    काष्ठा group_desc *grp,
				    काष्ठा imx_pinctrl *ipctl,
				    u32 index)
अणु
	स्थिर काष्ठा imx_pinctrl_soc_info *info = ipctl->info;
	काष्ठा imx_pin *pin;
	पूर्णांक size, pin_size;
	स्थिर __be32 *list;
	पूर्णांक i;

	dev_dbg(ipctl->dev, "group(%d): %pOFn\n", index, np);

	अगर (info->flags & IMX_USE_SCU)
		pin_size = FSL_SCU_PIN_SIZE;
	अन्यथा अगर (info->flags & SHARE_MUX_CONF_REG)
		pin_size = FSL_PIN_SHARE_SIZE;
	अन्यथा
		pin_size = FSL_PIN_SIZE;

	अगर (info->generic_pinconf)
		pin_size -= 4;

	/* Initialise group */
	grp->name = np->name;

	/*
	 * the binding क्रमmat is fsl,pins = <PIN_FUNC_ID CONFIG ...>,
	 * करो sanity check and calculate pins number
	 *
	 * First try legacy 'fsl,pins' property, then fall back to the
	 * generic 'pinmux'.
	 *
	 * Note: क्रम generic 'pinmux' case, there's no CONFIG part in
	 * the binding क्रमmat.
	 */
	list = of_get_property(np, "fsl,pins", &size);
	अगर (!list) अणु
		list = of_get_property(np, "pinmux", &size);
		अगर (!list) अणु
			dev_err(ipctl->dev,
				"no fsl,pins and pins property in node %pOF\n", np);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* we करो not check वापस since it's safe node passed करोwn */
	अगर (!size || size % pin_size) अणु
		dev_err(ipctl->dev, "Invalid fsl,pins or pins property in node %pOF\n", np);
		वापस -EINVAL;
	पूर्ण

	grp->num_pins = size / pin_size;
	grp->data = devm_kसुस्मृति(ipctl->dev,
				 grp->num_pins, माप(काष्ठा imx_pin),
				 GFP_KERNEL);
	grp->pins = devm_kसुस्मृति(ipctl->dev,
				 grp->num_pins, माप(अचिन्हित पूर्णांक),
				 GFP_KERNEL);
	अगर (!grp->pins || !grp->data)
		वापस -ENOMEM;

	क्रम (i = 0; i < grp->num_pins; i++) अणु
		pin = &((काष्ठा imx_pin *)(grp->data))[i];
		अगर (info->flags & IMX_USE_SCU)
			info->imx_pinctrl_parse_pin(ipctl, &grp->pins[i],
						  pin, &list);
		अन्यथा
			imx_pinctrl_parse_pin_mmio(ipctl, &grp->pins[i],
						   pin, &list, np);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_pinctrl_parse_functions(काष्ठा device_node *np,
				       काष्ठा imx_pinctrl *ipctl,
				       u32 index)
अणु
	काष्ठा pinctrl_dev *pctl = ipctl->pctl;
	काष्ठा device_node *child;
	काष्ठा function_desc *func;
	काष्ठा group_desc *grp;
	u32 i = 0;

	dev_dbg(pctl->dev, "parse function(%d): %pOFn\n", index, np);

	func = pinmux_generic_get_function(pctl, index);
	अगर (!func)
		वापस -EINVAL;

	/* Initialise function */
	func->name = np->name;
	func->num_group_names = of_get_child_count(np);
	अगर (func->num_group_names == 0) अणु
		dev_err(ipctl->dev, "no groups defined in %pOF\n", np);
		वापस -EINVAL;
	पूर्ण
	func->group_names = devm_kसुस्मृति(ipctl->dev, func->num_group_names,
					 माप(अक्षर *), GFP_KERNEL);
	अगर (!func->group_names)
		वापस -ENOMEM;

	क्रम_each_child_of_node(np, child) अणु
		func->group_names[i] = child->name;

		grp = devm_kzalloc(ipctl->dev, माप(काष्ठा group_desc),
				   GFP_KERNEL);
		अगर (!grp) अणु
			of_node_put(child);
			वापस -ENOMEM;
		पूर्ण

		mutex_lock(&ipctl->mutex);
		radix_tree_insert(&pctl->pin_group_tree,
				  ipctl->group_index++, grp);
		mutex_unlock(&ipctl->mutex);

		imx_pinctrl_parse_groups(child, grp, ipctl, i++);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Check अगर the DT contains pins in the direct child nodes. This indicates the
 * newer DT क्रमmat to store pins. This function वापसs true अगर the first found
 * fsl,pins property is in a child of np. Otherwise false is वापसed.
 */
अटल bool imx_pinctrl_dt_is_flat_functions(काष्ठा device_node *np)
अणु
	काष्ठा device_node *function_np;
	काष्ठा device_node *pinctrl_np;

	क्रम_each_child_of_node(np, function_np) अणु
		अगर (of_property_पढ़ो_bool(function_np, "fsl,pins")) अणु
			of_node_put(function_np);
			वापस true;
		पूर्ण

		क्रम_each_child_of_node(function_np, pinctrl_np) अणु
			अगर (of_property_पढ़ो_bool(pinctrl_np, "fsl,pins")) अणु
				of_node_put(pinctrl_np);
				of_node_put(function_np);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक imx_pinctrl_probe_dt(काष्ठा platक्रमm_device *pdev,
				काष्ठा imx_pinctrl *ipctl)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;
	काष्ठा pinctrl_dev *pctl = ipctl->pctl;
	u32 nfuncs = 0;
	u32 i = 0;
	bool flat_funcs;

	अगर (!np)
		वापस -ENODEV;

	flat_funcs = imx_pinctrl_dt_is_flat_functions(np);
	अगर (flat_funcs) अणु
		nfuncs = 1;
	पूर्ण अन्यथा अणु
		nfuncs = of_get_child_count(np);
		अगर (nfuncs == 0) अणु
			dev_err(&pdev->dev, "no functions defined\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nfuncs; i++) अणु
		काष्ठा function_desc *function;

		function = devm_kzalloc(&pdev->dev, माप(*function),
					GFP_KERNEL);
		अगर (!function)
			वापस -ENOMEM;

		mutex_lock(&ipctl->mutex);
		radix_tree_insert(&pctl->pin_function_tree, i, function);
		mutex_unlock(&ipctl->mutex);
	पूर्ण
	pctl->num_functions = nfuncs;

	ipctl->group_index = 0;
	अगर (flat_funcs) अणु
		pctl->num_groups = of_get_child_count(np);
	पूर्ण अन्यथा अणु
		pctl->num_groups = 0;
		क्रम_each_child_of_node(np, child)
			pctl->num_groups += of_get_child_count(child);
	पूर्ण

	अगर (flat_funcs) अणु
		imx_pinctrl_parse_functions(np, ipctl, 0);
	पूर्ण अन्यथा अणु
		i = 0;
		क्रम_each_child_of_node(np, child)
			imx_pinctrl_parse_functions(child, ipctl, i++);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक imx_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		      स्थिर काष्ठा imx_pinctrl_soc_info *info)
अणु
	काष्ठा regmap_config config = अणु .name = "gpr" पूर्ण;
	काष्ठा device_node *dev_np = pdev->dev.of_node;
	काष्ठा pinctrl_desc *imx_pinctrl_desc;
	काष्ठा device_node *np;
	काष्ठा imx_pinctrl *ipctl;
	काष्ठा regmap *gpr;
	पूर्णांक ret, i;

	अगर (!info || !info->pins || !info->npins) अणु
		dev_err(&pdev->dev, "wrong pinctrl info\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info->gpr_compatible) अणु
		gpr = syscon_regmap_lookup_by_compatible(info->gpr_compatible);
		अगर (!IS_ERR(gpr))
			regmap_attach_dev(&pdev->dev, gpr, &config);
	पूर्ण

	/* Create state holders etc क्रम this driver */
	ipctl = devm_kzalloc(&pdev->dev, माप(*ipctl), GFP_KERNEL);
	अगर (!ipctl)
		वापस -ENOMEM;

	अगर (!(info->flags & IMX_USE_SCU)) अणु
		ipctl->pin_regs = devm_kदो_स्मृति_array(&pdev->dev, info->npins,
						     माप(*ipctl->pin_regs),
						     GFP_KERNEL);
		अगर (!ipctl->pin_regs)
			वापस -ENOMEM;

		क्रम (i = 0; i < info->npins; i++) अणु
			ipctl->pin_regs[i].mux_reg = -1;
			ipctl->pin_regs[i].conf_reg = -1;
		पूर्ण

		ipctl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(ipctl->base))
			वापस PTR_ERR(ipctl->base);

		अगर (of_property_पढ़ो_bool(dev_np, "fsl,input-sel")) अणु
			np = of_parse_phandle(dev_np, "fsl,input-sel", 0);
			अगर (!np) अणु
				dev_err(&pdev->dev, "iomuxc fsl,input-sel property not found\n");
				वापस -EINVAL;
			पूर्ण

			ipctl->input_sel_base = of_iomap(np, 0);
			of_node_put(np);
			अगर (!ipctl->input_sel_base) अणु
				dev_err(&pdev->dev,
					"iomuxc input select base address not found\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	imx_pinctrl_desc = devm_kzalloc(&pdev->dev, माप(*imx_pinctrl_desc),
					GFP_KERNEL);
	अगर (!imx_pinctrl_desc)
		वापस -ENOMEM;

	imx_pinctrl_desc->name = dev_name(&pdev->dev);
	imx_pinctrl_desc->pins = info->pins;
	imx_pinctrl_desc->npins = info->npins;
	imx_pinctrl_desc->pctlops = &imx_pctrl_ops;
	imx_pinctrl_desc->pmxops = &imx_pmx_ops;
	imx_pinctrl_desc->confops = &imx_pinconf_ops;
	imx_pinctrl_desc->owner = THIS_MODULE;

	/* क्रम generic pinconf */
	imx_pinctrl_desc->custom_params = info->custom_params;
	imx_pinctrl_desc->num_custom_params = info->num_custom_params;

	/* platक्रमm specअगरic callback */
	imx_pmx_ops.gpio_set_direction = info->gpio_set_direction;

	mutex_init(&ipctl->mutex);

	ipctl->info = info;
	ipctl->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ipctl);
	ret = devm_pinctrl_रेजिस्टर_and_init(&pdev->dev,
					     imx_pinctrl_desc, ipctl,
					     &ipctl->pctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register IMX pinctrl driver\n");
		वापस ret;
	पूर्ण

	ret = imx_pinctrl_probe_dt(pdev, ipctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "fail to probe dt properties\n");
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "initialized IMX pinctrl driver\n");

	वापस pinctrl_enable(ipctl->pctl);
पूर्ण
EXPORT_SYMBOL_GPL(imx_pinctrl_probe);

अटल पूर्णांक __maybe_unused imx_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx_pinctrl *ipctl = dev_get_drvdata(dev);

	वापस pinctrl_क्रमce_sleep(ipctl->pctl);
पूर्ण

अटल पूर्णांक __maybe_unused imx_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा imx_pinctrl *ipctl = dev_get_drvdata(dev);

	वापस pinctrl_क्रमce_शेष(ipctl->pctl);
पूर्ण

स्थिर काष्ठा dev_pm_ops imx_pinctrl_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(imx_pinctrl_suspend,
					imx_pinctrl_resume)
पूर्ण;
EXPORT_SYMBOL_GPL(imx_pinctrl_pm_ops);

MODULE_AUTHOR("Dong Aisheng <aisheng.dong@nxp.com>");
MODULE_DESCRIPTION("NXP i.MX common pinctrl driver");
MODULE_LICENSE("GPL v2");
