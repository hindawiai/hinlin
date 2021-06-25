<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Core driver क्रम the imx pin controller in imx1/21/27
//
// Copyright (C) 2013 Pengutronix
// Author: Markus Pargmann <mpa@pengutronix.de>
//
// Based on pinctrl-imx.c:
//	Author: Dong Aisheng <करोng.aisheng@linaro.org>
//	Copyright (C) 2012 Freescale Semiconductor, Inc.
//	Copyright (C) 2012 Linaro Ltd.

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "pinctrl-imx1.h"

काष्ठा imx1_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	व्योम __iomem *base;
	स्थिर काष्ठा imx1_pinctrl_soc_info *info;
पूर्ण;

/*
 * MX1 रेजिस्टर offsets
 */

#घोषणा MX1_Dसूची 0x00
#घोषणा MX1_OCR 0x04
#घोषणा MX1_ICONFA 0x0c
#घोषणा MX1_ICONFB 0x14
#घोषणा MX1_GIUS 0x20
#घोषणा MX1_GPR 0x38
#घोषणा MX1_PUEN 0x40

#घोषणा MX1_PORT_STRIDE 0x100


/*
 * MUX_ID क्रमmat defines
 */
#घोषणा MX1_MUX_FUNCTION(val) (BIT(0) & val)
#घोषणा MX1_MUX_GPIO(val) ((BIT(1) & val) >> 1)
#घोषणा MX1_MUX_सूची(val) ((BIT(2) & val) >> 2)
#घोषणा MX1_MUX_OCONF(val) (((BIT(4) | BIT(5)) & val) >> 4)
#घोषणा MX1_MUX_ICONFA(val) (((BIT(8) | BIT(9)) & val) >> 8)
#घोषणा MX1_MUX_ICONFB(val) (((BIT(10) | BIT(11)) & val) >> 10)


/*
 * IMX1 IOMUXC manages the pins based on ports. Each port has 32 pins. IOMUX
 * control रेजिस्टरs are separated पूर्णांकo function, output configuration, input
 * configuration A, input configuration B, GPIO in use and data direction.
 *
 * Those controls that are represented by 1 bit have a direct mapping between
 * bit position and pin id. If they are represented by 2 bit, the lower 16 pins
 * are in the first रेजिस्टर and the upper 16 pins in the second (next)
 * रेजिस्टर. pin_id is stored in bit (pin_id%16)*2 and the bit above.
 */

/*
 * Calculates the रेजिस्टर offset from a pin_id
 */
अटल व्योम __iomem *imx1_mem(काष्ठा imx1_pinctrl *ipctl, अचिन्हित पूर्णांक pin_id)
अणु
	अचिन्हित पूर्णांक port = pin_id / 32;
	वापस ipctl->base + port * MX1_PORT_STRIDE;
पूर्ण

/*
 * Write to a रेजिस्टर with 2 bits per pin. The function will स्वतःmatically
 * use the next रेजिस्टर अगर the pin is managed in the second रेजिस्टर.
 */
अटल व्योम imx1_ग_लिखो_2bit(काष्ठा imx1_pinctrl *ipctl, अचिन्हित पूर्णांक pin_id,
		u32 value, u32 reg_offset)
अणु
	व्योम __iomem *reg = imx1_mem(ipctl, pin_id) + reg_offset;
	पूर्णांक offset = (pin_id % 16) * 2; /* offset, regardless of रेजिस्टर used */
	पूर्णांक mask = ~(0x3 << offset); /* Mask क्रम 2 bits at offset */
	u32 old_val;
	u32 new_val;

	/* Use the next रेजिस्टर अगर the pin's port pin number is >=16 */
	अगर (pin_id % 32 >= 16)
		reg += 0x04;

	dev_dbg(ipctl->dev, "write: register 0x%p offset %d value 0x%x\n",
			reg, offset, value);

	/* Get current state of pins */
	old_val = पढ़ोl(reg);
	old_val &= mask;

	new_val = value & 0x3; /* Make sure value is really 2 bit */
	new_val <<= offset;
	new_val |= old_val;/* Set new state क्रम pin_id */

	ग_लिखोl(new_val, reg);
पूर्ण

अटल व्योम imx1_ग_लिखो_bit(काष्ठा imx1_pinctrl *ipctl, अचिन्हित पूर्णांक pin_id,
		u32 value, u32 reg_offset)
अणु
	व्योम __iomem *reg = imx1_mem(ipctl, pin_id) + reg_offset;
	पूर्णांक offset = pin_id % 32;
	पूर्णांक mask = ~BIT_MASK(offset);
	u32 old_val;
	u32 new_val;

	/* Get current state of pins */
	old_val = पढ़ोl(reg);
	old_val &= mask;

	new_val = value & 0x1; /* Make sure value is really 1 bit */
	new_val <<= offset;
	new_val |= old_val;/* Set new state क्रम pin_id */

	ग_लिखोl(new_val, reg);
पूर्ण

अटल पूर्णांक imx1_पढ़ो_2bit(काष्ठा imx1_pinctrl *ipctl, अचिन्हित पूर्णांक pin_id,
		u32 reg_offset)
अणु
	व्योम __iomem *reg = imx1_mem(ipctl, pin_id) + reg_offset;
	पूर्णांक offset = (pin_id % 16) * 2;

	/* Use the next रेजिस्टर अगर the pin's port pin number is >=16 */
	अगर (pin_id % 32 >= 16)
		reg += 0x04;

	वापस (पढ़ोl(reg) & (BIT(offset) | BIT(offset+1))) >> offset;
पूर्ण

अटल पूर्णांक imx1_पढ़ो_bit(काष्ठा imx1_pinctrl *ipctl, अचिन्हित पूर्णांक pin_id,
		u32 reg_offset)
अणु
	व्योम __iomem *reg = imx1_mem(ipctl, pin_id) + reg_offset;
	पूर्णांक offset = pin_id % 32;

	वापस !!(पढ़ोl(reg) & BIT(offset));
पूर्ण

अटल अंतरभूत स्थिर काष्ठा imx1_pin_group *imx1_pinctrl_find_group_by_name(
				स्थिर काष्ठा imx1_pinctrl_soc_info *info,
				स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा imx1_pin_group *grp = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < info->ngroups; i++) अणु
		अगर (!म_भेद(info->groups[i].name, name)) अणु
			grp = &info->groups[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस grp;
पूर्ण

अटल पूर्णांक imx1_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;

	वापस info->ngroups;
पूर्ण

अटल स्थिर अक्षर *imx1_get_group_name(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित selector)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;

	वापस info->groups[selector].name;
पूर्ण

अटल पूर्णांक imx1_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			       स्थिर अचिन्हित पूर्णांक **pins,
			       अचिन्हित *npins)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;

	अगर (selector >= info->ngroups)
		वापस -EINVAL;

	*pins = info->groups[selector].pin_ids;
	*npins = info->groups[selector].npins;

	वापस 0;
पूर्ण

अटल व्योम imx1_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
		   अचिन्हित offset)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);

	seq_म_लिखो(s, "GPIO %d, function %d, direction %d, oconf %d, iconfa %d, iconfb %d",
			imx1_पढ़ो_bit(ipctl, offset, MX1_GIUS),
			imx1_पढ़ो_bit(ipctl, offset, MX1_GPR),
			imx1_पढ़ो_bit(ipctl, offset, MX1_Dसूची),
			imx1_पढ़ो_2bit(ipctl, offset, MX1_OCR),
			imx1_पढ़ो_2bit(ipctl, offset, MX1_ICONFA),
			imx1_पढ़ो_2bit(ipctl, offset, MX1_ICONFB));
पूर्ण

अटल पूर्णांक imx1_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
			काष्ठा device_node *np,
			काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;
	स्थिर काष्ठा imx1_pin_group *grp;
	काष्ठा pinctrl_map *new_map;
	काष्ठा device_node *parent;
	पूर्णांक map_num = 1;
	पूर्णांक i, j;

	/*
	 * first find the group of this node and check अगर we need create
	 * config maps क्रम pins
	 */
	grp = imx1_pinctrl_find_group_by_name(info, np->name);
	अगर (!grp) अणु
		dev_err(info->dev, "unable to find group for node %pOFn\n",
			np);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < grp->npins; i++)
		map_num++;

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
	क्रम (i = j = 0; i < grp->npins; i++) अणु
		new_map[j].type = PIN_MAP_TYPE_CONFIGS_PIN;
		new_map[j].data.configs.group_or_pin =
				pin_get_name(pctldev, grp->pins[i].pin_id);
		new_map[j].data.configs.configs = &grp->pins[i].config;
		new_map[j].data.configs.num_configs = 1;
		j++;
	पूर्ण

	dev_dbg(pctldev->dev, "maps: function %s group %s num %d\n",
		(*map)->data.mux.function, (*map)->data.mux.group, map_num);

	वापस 0;
पूर्ण

अटल व्योम imx1_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops imx1_pctrl_ops = अणु
	.get_groups_count = imx1_get_groups_count,
	.get_group_name = imx1_get_group_name,
	.get_group_pins = imx1_get_group_pins,
	.pin_dbg_show = imx1_pin_dbg_show,
	.dt_node_to_map = imx1_dt_node_to_map,
	.dt_मुक्त_map = imx1_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक imx1_pmx_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			अचिन्हित group)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;
	स्थिर काष्ठा imx1_pin *pins;
	अचिन्हित पूर्णांक npins;
	पूर्णांक i;

	/*
	 * Configure the mux mode क्रम each pin in the group क्रम a specअगरic
	 * function.
	 */
	pins = info->groups[group].pins;
	npins = info->groups[group].npins;

	WARN_ON(!pins || !npins);

	dev_dbg(ipctl->dev, "enable function %s group %s\n",
		info->functions[selector].name, info->groups[group].name);

	क्रम (i = 0; i < npins; i++) अणु
		अचिन्हित पूर्णांक mux = pins[i].mux_id;
		अचिन्हित पूर्णांक pin_id = pins[i].pin_id;
		अचिन्हित पूर्णांक afunction = MX1_MUX_FUNCTION(mux);
		अचिन्हित पूर्णांक gpio_in_use = MX1_MUX_GPIO(mux);
		अचिन्हित पूर्णांक direction = MX1_MUX_सूची(mux);
		अचिन्हित पूर्णांक gpio_oconf = MX1_MUX_OCONF(mux);
		अचिन्हित पूर्णांक gpio_iconfa = MX1_MUX_ICONFA(mux);
		अचिन्हित पूर्णांक gpio_iconfb = MX1_MUX_ICONFB(mux);

		dev_dbg(pctldev->dev, "%s, pin 0x%x, function %d, gpio %d, direction %d, oconf %d, iconfa %d, iconfb %d\n",
				__func__, pin_id, afunction, gpio_in_use,
				direction, gpio_oconf, gpio_iconfa,
				gpio_iconfb);

		imx1_ग_लिखो_bit(ipctl, pin_id, gpio_in_use, MX1_GIUS);
		imx1_ग_लिखो_bit(ipctl, pin_id, direction, MX1_Dसूची);

		अगर (gpio_in_use) अणु
			imx1_ग_लिखो_2bit(ipctl, pin_id, gpio_oconf, MX1_OCR);
			imx1_ग_लिखो_2bit(ipctl, pin_id, gpio_iconfa,
					MX1_ICONFA);
			imx1_ग_लिखो_2bit(ipctl, pin_id, gpio_iconfb,
					MX1_ICONFB);
		पूर्ण अन्यथा अणु
			imx1_ग_लिखो_bit(ipctl, pin_id, afunction, MX1_GPR);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx1_pmx_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;

	वापस info->nfunctions;
पूर्ण

अटल स्थिर अक्षर *imx1_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित selector)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;

	वापस info->functions[selector].name;
पूर्ण

अटल पूर्णांक imx1_pmx_get_groups(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			       स्थिर अक्षर * स्थिर **groups,
			       अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;

	*groups = info->functions[selector].groups;
	*num_groups = info->functions[selector].num_groups;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops imx1_pmx_ops = अणु
	.get_functions_count = imx1_pmx_get_funcs_count,
	.get_function_name = imx1_pmx_get_func_name,
	.get_function_groups = imx1_pmx_get_groups,
	.set_mux = imx1_pmx_set,
पूर्ण;

अटल पूर्णांक imx1_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित pin_id, अचिन्हित दीर्घ *config)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);

	*config = imx1_पढ़ो_bit(ipctl, pin_id, MX1_PUEN);

	वापस 0;
पूर्ण

अटल पूर्णांक imx1_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित pin_id, अचिन्हित दीर्घ *configs,
			     अचिन्हित num_configs)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक i;

	क्रम (i = 0; i != num_configs; ++i) अणु
		imx1_ग_लिखो_bit(ipctl, pin_id, configs[i] & 0x01, MX1_PUEN);

		dev_dbg(ipctl->dev, "pinconf set pullup pin %s\n",
			pin_desc_get(pctldev, pin_id)->name);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx1_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा seq_file *s, अचिन्हित pin_id)
अणु
	अचिन्हित दीर्घ config;

	imx1_pinconf_get(pctldev, pin_id, &config);
	seq_म_लिखो(s, "0x%lx", config);
पूर्ण

अटल व्योम imx1_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
					 काष्ठा seq_file *s, अचिन्हित group)
अणु
	काष्ठा imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा imx1_pinctrl_soc_info *info = ipctl->info;
	काष्ठा imx1_pin_group *grp;
	अचिन्हित दीर्घ config;
	स्थिर अक्षर *name;
	पूर्णांक i, ret;

	अगर (group >= info->ngroups)
		वापस;

	seq_माला_दो(s, "\n");
	grp = &info->groups[group];
	क्रम (i = 0; i < grp->npins; i++) अणु
		name = pin_get_name(pctldev, grp->pins[i].pin_id);
		ret = imx1_pinconf_get(pctldev, grp->pins[i].pin_id, &config);
		अगर (ret)
			वापस;
		seq_म_लिखो(s, "%s: 0x%lx", name, config);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops imx1_pinconf_ops = अणु
	.pin_config_get = imx1_pinconf_get,
	.pin_config_set = imx1_pinconf_set,
	.pin_config_dbg_show = imx1_pinconf_dbg_show,
	.pin_config_group_dbg_show = imx1_pinconf_group_dbg_show,
पूर्ण;

अटल काष्ठा pinctrl_desc imx1_pinctrl_desc = अणु
	.pctlops = &imx1_pctrl_ops,
	.pmxops = &imx1_pmx_ops,
	.confops = &imx1_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक imx1_pinctrl_parse_groups(काष्ठा device_node *np,
				    काष्ठा imx1_pin_group *grp,
				    काष्ठा imx1_pinctrl_soc_info *info,
				    u32 index)
अणु
	पूर्णांक size;
	स्थिर __be32 *list;
	पूर्णांक i;

	dev_dbg(info->dev, "group(%d): %pOFn\n", index, np);

	/* Initialise group */
	grp->name = np->name;

	/*
	 * the binding क्रमmat is fsl,pins = <PIN MUX_ID CONFIG>
	 */
	list = of_get_property(np, "fsl,pins", &size);
	/* we करो not check वापस since it's safe node passed करोwn */
	अगर (!size || size % 12) अणु
		dev_notice(info->dev, "Not a valid fsl,pins property (%pOFn)\n",
				np);
		वापस -EINVAL;
	पूर्ण

	grp->npins = size / 12;
	grp->pins = devm_kसुस्मृति(info->dev,
			grp->npins, माप(काष्ठा imx1_pin), GFP_KERNEL);
	grp->pin_ids = devm_kसुस्मृति(info->dev,
			grp->npins, माप(अचिन्हित पूर्णांक), GFP_KERNEL);

	अगर (!grp->pins || !grp->pin_ids)
		वापस -ENOMEM;

	क्रम (i = 0; i < grp->npins; i++) अणु
		grp->pins[i].pin_id = be32_to_cpu(*list++);
		grp->pins[i].mux_id = be32_to_cpu(*list++);
		grp->pins[i].config = be32_to_cpu(*list++);

		grp->pin_ids[i] = grp->pins[i].pin_id;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx1_pinctrl_parse_functions(काष्ठा device_node *np,
				       काष्ठा imx1_pinctrl_soc_info *info,
				       u32 index)
अणु
	काष्ठा device_node *child;
	काष्ठा imx1_pmx_func *func;
	काष्ठा imx1_pin_group *grp;
	पूर्णांक ret;
	अटल u32 grp_index;
	u32 i = 0;

	dev_dbg(info->dev, "parse function(%d): %pOFn\n", index, np);

	func = &info->functions[index];

	/* Initialise function */
	func->name = np->name;
	func->num_groups = of_get_child_count(np);
	अगर (func->num_groups == 0)
		वापस -EINVAL;

	func->groups = devm_kसुस्मृति(info->dev,
			func->num_groups, माप(अक्षर *), GFP_KERNEL);

	अगर (!func->groups)
		वापस -ENOMEM;

	क्रम_each_child_of_node(np, child) अणु
		func->groups[i] = child->name;
		grp = &info->groups[grp_index++];
		ret = imx1_pinctrl_parse_groups(child, grp, info, i++);
		अगर (ret == -ENOMEM) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx1_pinctrl_parse_dt(काष्ठा platक्रमm_device *pdev,
		काष्ठा imx1_pinctrl *pctl, काष्ठा imx1_pinctrl_soc_info *info)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;
	पूर्णांक ret;
	u32 nfuncs = 0;
	u32 ngroups = 0;
	u32 अगरunc = 0;

	अगर (!np)
		वापस -ENODEV;

	क्रम_each_child_of_node(np, child) अणु
		++nfuncs;
		ngroups += of_get_child_count(child);
	पूर्ण

	अगर (!nfuncs) अणु
		dev_err(&pdev->dev, "No pin functions defined\n");
		वापस -EINVAL;
	पूर्ण

	info->nfunctions = nfuncs;
	info->functions = devm_kसुस्मृति(&pdev->dev,
			nfuncs, माप(काष्ठा imx1_pmx_func), GFP_KERNEL);

	info->ngroups = ngroups;
	info->groups = devm_kसुस्मृति(&pdev->dev,
			ngroups, माप(काष्ठा imx1_pin_group), GFP_KERNEL);


	अगर (!info->functions || !info->groups)
		वापस -ENOMEM;

	क्रम_each_child_of_node(np, child) अणु
		ret = imx1_pinctrl_parse_functions(child, info, अगरunc++);
		अगर (ret == -ENOMEM) अणु
			of_node_put(child);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक imx1_pinctrl_core_probe(काष्ठा platक्रमm_device *pdev,
		      काष्ठा imx1_pinctrl_soc_info *info)
अणु
	काष्ठा imx1_pinctrl *ipctl;
	काष्ठा resource *res;
	काष्ठा pinctrl_desc *pctl_desc;
	पूर्णांक ret;

	अगर (!info || !info->pins || !info->npins) अणु
		dev_err(&pdev->dev, "wrong pinctrl info\n");
		वापस -EINVAL;
	पूर्ण
	info->dev = &pdev->dev;

	/* Create state holders etc क्रम this driver */
	ipctl = devm_kzalloc(&pdev->dev, माप(*ipctl), GFP_KERNEL);
	अगर (!ipctl)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOENT;

	ipctl->base = devm_ioremap(&pdev->dev, res->start,
			resource_size(res));
	अगर (!ipctl->base)
		वापस -ENOMEM;

	pctl_desc = &imx1_pinctrl_desc;
	pctl_desc->name = dev_name(&pdev->dev);
	pctl_desc->pins = info->pins;
	pctl_desc->npins = info->npins;

	ret = imx1_pinctrl_parse_dt(pdev, ipctl, info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "fail to probe dt properties\n");
		वापस ret;
	पूर्ण

	ipctl->info = info;
	ipctl->dev = info->dev;
	platक्रमm_set_drvdata(pdev, ipctl);
	ipctl->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, pctl_desc, ipctl);
	अगर (IS_ERR(ipctl->pctl)) अणु
		dev_err(&pdev->dev, "could not register IMX pinctrl driver\n");
		वापस PTR_ERR(ipctl->pctl);
	पूर्ण

	ret = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to populate subdevices\n");
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "initialized IMX pinctrl driver\n");

	वापस 0;
पूर्ण
