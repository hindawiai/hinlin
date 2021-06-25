<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014-2018 Renesas Electronics Europe Limited
 *
 * Phil Edworthy <phil.edworthy@renesas.com>
 * Based on a driver originally written by Michel Pollet at Renesas.
 */

#समावेश <dt-bindings/pinctrl/rzn1-pinctrl.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश "../core.h"
#समावेश "../pinconf.h"
#समावेश "../pinctrl-utils.h"

/* Field positions and masks in the pinmux रेजिस्टरs */
#घोषणा RZN1_L1_PIN_DRIVE_STRENGTH	10
#घोषणा RZN1_L1_PIN_DRIVE_STRENGTH_4MA	0
#घोषणा RZN1_L1_PIN_DRIVE_STRENGTH_6MA	1
#घोषणा RZN1_L1_PIN_DRIVE_STRENGTH_8MA	2
#घोषणा RZN1_L1_PIN_DRIVE_STRENGTH_12MA	3
#घोषणा RZN1_L1_PIN_PULL		8
#घोषणा RZN1_L1_PIN_PULL_NONE		0
#घोषणा RZN1_L1_PIN_PULL_UP		1
#घोषणा RZN1_L1_PIN_PULL_DOWN		3
#घोषणा RZN1_L1_FUNCTION		0
#घोषणा RZN1_L1_FUNC_MASK		0xf
#घोषणा RZN1_L1_FUNCTION_L2		0xf

/*
 * The hardware manual describes two levels of multiplexing, but it's more
 * logical to think of the hardware as three levels, with level 3 consisting of
 * the multiplexing क्रम Ethernet MDIO संकेतs.
 *
 * Level 1 functions go from 0 to 9, with level 1 function '15' (0xf) specअगरying
 * that level 2 functions are used instead. Level 2 has a lot more options,
 * going from 0 to 61. Level 3 allows selection of MDIO functions which can be
 * भग्नing, or one of seven पूर्णांकernal peripherals. Unक्रमtunately, there are two
 * level 2 functions that can select MDIO, and two MDIO channels so we have four
 * sets of level 3 functions.
 *
 * For this driver, we've compounded the numbers together, so:
 *    0 to   9 is level 1
 *   10 to  71 is 10 + level 2 number
 *   72 to  79 is 72 + MDIO0 source क्रम level 2 MDIO function.
 *   80 to  87 is 80 + MDIO0 source क्रम level 2 MDIO_E1 function.
 *   88 to  95 is 88 + MDIO1 source क्रम level 2 MDIO function.
 *   96 to 103 is 96 + MDIO1 source क्रम level 2 MDIO_E1 function.
 * Examples:
 *  Function 28 corresponds UART0
 *  Function 73 corresponds to MDIO0 to GMAC0
 *
 * There are 170 configurable pins (called PL_GPIO in the datasheet).
 */

/*
 * Structure detailing the HW रेजिस्टरs on the RZ/N1 devices.
 * Both the Level 1 mux रेजिस्टरs and Level 2 mux रेजिस्टरs have the same
 * काष्ठाure. The only dअगरference is that Level 2 has additional MDIO रेजिस्टरs
 * at the end.
 */
काष्ठा rzn1_pinctrl_regs अणु
	u32	conf[170];
	u32	pad0[86];
	u32	status_protect;	/* 0x400 */
	/* MDIO mux रेजिस्टरs, level2 only */
	u32	l2_mdio[2];
पूर्ण;

/**
 * काष्ठा rzn1_pmx_func - describes rzn1 pinmux functions
 * @name: the name of this specअगरic function
 * @groups: corresponding pin groups
 * @num_groups: the number of groups
 */
काष्ठा rzn1_pmx_func अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर **groups;
	अचिन्हित पूर्णांक num_groups;
पूर्ण;

/**
 * काष्ठा rzn1_pin_group - describes an rzn1 pin group
 * @name: the name of this specअगरic pin group
 * @func: the name of the function selected by this group
 * @npins: the number of pins in this group array, i.e. the number of
 *	elements in .pins so we can iterate over that array
 * @pins: array of pins. Needed due to pinctrl_ops.get_group_pins()
 * @pin_ids: array of pin_ids, i.e. the value used to select the mux
 */
काष्ठा rzn1_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *func;
	अचिन्हित पूर्णांक npins;
	अचिन्हित पूर्णांक *pins;
	u8 *pin_ids;
पूर्ण;

काष्ठा rzn1_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा rzn1_pinctrl_regs __iomem *lev1;
	काष्ठा rzn1_pinctrl_regs __iomem *lev2;
	u32 lev1_protect_phys;
	u32 lev2_protect_phys;
	पूर्णांक mdio_func[2];

	काष्ठा rzn1_pin_group *groups;
	अचिन्हित पूर्णांक ngroups;

	काष्ठा rzn1_pmx_func *functions;
	अचिन्हित पूर्णांक nfunctions;
पूर्ण;

#घोषणा RZN1_PINS_PROP "pinmux"

#घोषणा RZN1_PIN(pin) PINCTRL_PIN(pin, "pl_gpio"#pin)

अटल स्थिर काष्ठा pinctrl_pin_desc rzn1_pins[] = अणु
	RZN1_PIN(0), RZN1_PIN(1), RZN1_PIN(2), RZN1_PIN(3), RZN1_PIN(4),
	RZN1_PIN(5), RZN1_PIN(6), RZN1_PIN(7), RZN1_PIN(8), RZN1_PIN(9),
	RZN1_PIN(10), RZN1_PIN(11), RZN1_PIN(12), RZN1_PIN(13), RZN1_PIN(14),
	RZN1_PIN(15), RZN1_PIN(16), RZN1_PIN(17), RZN1_PIN(18), RZN1_PIN(19),
	RZN1_PIN(20), RZN1_PIN(21), RZN1_PIN(22), RZN1_PIN(23), RZN1_PIN(24),
	RZN1_PIN(25), RZN1_PIN(26), RZN1_PIN(27), RZN1_PIN(28), RZN1_PIN(29),
	RZN1_PIN(30), RZN1_PIN(31), RZN1_PIN(32), RZN1_PIN(33), RZN1_PIN(34),
	RZN1_PIN(35), RZN1_PIN(36), RZN1_PIN(37), RZN1_PIN(38), RZN1_PIN(39),
	RZN1_PIN(40), RZN1_PIN(41), RZN1_PIN(42), RZN1_PIN(43), RZN1_PIN(44),
	RZN1_PIN(45), RZN1_PIN(46), RZN1_PIN(47), RZN1_PIN(48), RZN1_PIN(49),
	RZN1_PIN(50), RZN1_PIN(51), RZN1_PIN(52), RZN1_PIN(53), RZN1_PIN(54),
	RZN1_PIN(55), RZN1_PIN(56), RZN1_PIN(57), RZN1_PIN(58), RZN1_PIN(59),
	RZN1_PIN(60), RZN1_PIN(61), RZN1_PIN(62), RZN1_PIN(63), RZN1_PIN(64),
	RZN1_PIN(65), RZN1_PIN(66), RZN1_PIN(67), RZN1_PIN(68), RZN1_PIN(69),
	RZN1_PIN(70), RZN1_PIN(71), RZN1_PIN(72), RZN1_PIN(73), RZN1_PIN(74),
	RZN1_PIN(75), RZN1_PIN(76), RZN1_PIN(77), RZN1_PIN(78), RZN1_PIN(79),
	RZN1_PIN(80), RZN1_PIN(81), RZN1_PIN(82), RZN1_PIN(83), RZN1_PIN(84),
	RZN1_PIN(85), RZN1_PIN(86), RZN1_PIN(87), RZN1_PIN(88), RZN1_PIN(89),
	RZN1_PIN(90), RZN1_PIN(91), RZN1_PIN(92), RZN1_PIN(93), RZN1_PIN(94),
	RZN1_PIN(95), RZN1_PIN(96), RZN1_PIN(97), RZN1_PIN(98), RZN1_PIN(99),
	RZN1_PIN(100), RZN1_PIN(101), RZN1_PIN(102), RZN1_PIN(103),
	RZN1_PIN(104), RZN1_PIN(105), RZN1_PIN(106), RZN1_PIN(107),
	RZN1_PIN(108), RZN1_PIN(109), RZN1_PIN(110), RZN1_PIN(111),
	RZN1_PIN(112), RZN1_PIN(113), RZN1_PIN(114), RZN1_PIN(115),
	RZN1_PIN(116), RZN1_PIN(117), RZN1_PIN(118), RZN1_PIN(119),
	RZN1_PIN(120), RZN1_PIN(121), RZN1_PIN(122), RZN1_PIN(123),
	RZN1_PIN(124), RZN1_PIN(125), RZN1_PIN(126), RZN1_PIN(127),
	RZN1_PIN(128), RZN1_PIN(129), RZN1_PIN(130), RZN1_PIN(131),
	RZN1_PIN(132), RZN1_PIN(133), RZN1_PIN(134), RZN1_PIN(135),
	RZN1_PIN(136), RZN1_PIN(137), RZN1_PIN(138), RZN1_PIN(139),
	RZN1_PIN(140), RZN1_PIN(141), RZN1_PIN(142), RZN1_PIN(143),
	RZN1_PIN(144), RZN1_PIN(145), RZN1_PIN(146), RZN1_PIN(147),
	RZN1_PIN(148), RZN1_PIN(149), RZN1_PIN(150), RZN1_PIN(151),
	RZN1_PIN(152), RZN1_PIN(153), RZN1_PIN(154), RZN1_PIN(155),
	RZN1_PIN(156), RZN1_PIN(157), RZN1_PIN(158), RZN1_PIN(159),
	RZN1_PIN(160), RZN1_PIN(161), RZN1_PIN(162), RZN1_PIN(163),
	RZN1_PIN(164), RZN1_PIN(165), RZN1_PIN(166), RZN1_PIN(167),
	RZN1_PIN(168), RZN1_PIN(169),
पूर्ण;

क्रमागत अणु
	LOCK_LEVEL1 = 0x1,
	LOCK_LEVEL2 = 0x2,
	LOCK_ALL = LOCK_LEVEL1 | LOCK_LEVEL2,
पूर्ण;

अटल व्योम rzn1_hw_set_lock(काष्ठा rzn1_pinctrl *ipctl, u8 lock, u8 value)
अणु
	/*
	 * The pinmux configuration is locked by writing the physical address of
	 * the status_protect रेजिस्टर to itself. It is unlocked by writing the
	 * address | 1.
	 */
	अगर (lock & LOCK_LEVEL1) अणु
		u32 val = ipctl->lev1_protect_phys | !(value & LOCK_LEVEL1);

		ग_लिखोl(val, &ipctl->lev1->status_protect);
	पूर्ण

	अगर (lock & LOCK_LEVEL2) अणु
		u32 val = ipctl->lev2_protect_phys | !(value & LOCK_LEVEL2);

		ग_लिखोl(val, &ipctl->lev2->status_protect);
	पूर्ण
पूर्ण

अटल व्योम rzn1_pinctrl_mdio_select(काष्ठा rzn1_pinctrl *ipctl, पूर्णांक mdio,
				     u32 func)
अणु
	अगर (ipctl->mdio_func[mdio] >= 0 && ipctl->mdio_func[mdio] != func)
		dev_warn(ipctl->dev, "conflicting setting for mdio%d!\n", mdio);
	ipctl->mdio_func[mdio] = func;

	dev_dbg(ipctl->dev, "setting mdio%d to %u\n", mdio, func);

	ग_लिखोl(func, &ipctl->lev2->l2_mdio[mdio]);
पूर्ण

/*
 * Using a composite pin description, set the hardware pinmux रेजिस्टरs
 * with the corresponding values.
 * Make sure to unlock ग_लिखो protection and reset it afterward.
 *
 * NOTE: There is no protection क्रम potential concurrency, it is assumed these
 * calls are serialized alपढ़ोy.
 */
अटल पूर्णांक rzn1_set_hw_pin_func(काष्ठा rzn1_pinctrl *ipctl, अचिन्हित पूर्णांक pin,
				u32 pin_config, u8 use_locks)
अणु
	u32 l1_cache;
	u32 l2_cache;
	u32 l1;
	u32 l2;

	/* Level 3 MDIO multiplexing */
	अगर (pin_config >= RZN1_FUNC_MDIO0_HIGHZ &&
	    pin_config <= RZN1_FUNC_MDIO1_E1_SWITCH) अणु
		पूर्णांक mdio_channel;
		u32 mdio_func;

		अगर (pin_config <= RZN1_FUNC_MDIO1_HIGHZ)
			mdio_channel = 0;
		अन्यथा
			mdio_channel = 1;

		/* Get MDIO func, and convert the func to the level 2 number */
		अगर (pin_config <= RZN1_FUNC_MDIO0_SWITCH) अणु
			mdio_func = pin_config - RZN1_FUNC_MDIO0_HIGHZ;
			pin_config = RZN1_FUNC_ETH_MDIO;
		पूर्ण अन्यथा अगर (pin_config <= RZN1_FUNC_MDIO0_E1_SWITCH) अणु
			mdio_func = pin_config - RZN1_FUNC_MDIO0_E1_HIGHZ;
			pin_config = RZN1_FUNC_ETH_MDIO_E1;
		पूर्ण अन्यथा अगर (pin_config <= RZN1_FUNC_MDIO1_SWITCH) अणु
			mdio_func = pin_config - RZN1_FUNC_MDIO1_HIGHZ;
			pin_config = RZN1_FUNC_ETH_MDIO;
		पूर्ण अन्यथा अणु
			mdio_func = pin_config - RZN1_FUNC_MDIO1_E1_HIGHZ;
			pin_config = RZN1_FUNC_ETH_MDIO_E1;
		पूर्ण
		rzn1_pinctrl_mdio_select(ipctl, mdio_channel, mdio_func);
	पूर्ण

	/* Note here, we करो not allow anything past the MDIO Mux values */
	अगर (pin >= ARRAY_SIZE(ipctl->lev1->conf) ||
	    pin_config >= RZN1_FUNC_MDIO0_HIGHZ)
		वापस -EINVAL;

	l1 = पढ़ोl(&ipctl->lev1->conf[pin]);
	l1_cache = l1;
	l2 = पढ़ोl(&ipctl->lev2->conf[pin]);
	l2_cache = l2;

	dev_dbg(ipctl->dev, "setting func for pin %u to %u\n", pin, pin_config);

	l1 &= ~(RZN1_L1_FUNC_MASK << RZN1_L1_FUNCTION);

	अगर (pin_config < RZN1_FUNC_L2_OFFSET) अणु
		l1 |= (pin_config << RZN1_L1_FUNCTION);
	पूर्ण अन्यथा अणु
		l1 |= (RZN1_L1_FUNCTION_L2 << RZN1_L1_FUNCTION);

		l2 = pin_config - RZN1_FUNC_L2_OFFSET;
	पूर्ण

	/* If either configuration changes, we update both anyway */
	अगर (l1 != l1_cache || l2 != l2_cache) अणु
		ग_लिखोl(l1, &ipctl->lev1->conf[pin]);
		ग_लिखोl(l2, &ipctl->lev2->conf[pin]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rzn1_pin_group *rzn1_pinctrl_find_group_by_name(
	स्थिर काष्ठा rzn1_pinctrl *ipctl, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ipctl->ngroups; i++) अणु
		अगर (!म_भेद(ipctl->groups[i].name, name))
			वापस &ipctl->groups[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक rzn1_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);

	वापस ipctl->ngroups;
पूर्ण

अटल स्थिर अक्षर *rzn1_get_group_name(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक selector)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);

	वापस ipctl->groups[selector].name;
पूर्ण

अटल पूर्णांक rzn1_get_group_pins(काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित पूर्णांक selector, स्थिर अचिन्हित पूर्णांक **pins,
			       अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);

	अगर (selector >= ipctl->ngroups)
		वापस -EINVAL;

	*pins = ipctl->groups[selector].pins;
	*npins = ipctl->groups[selector].npins;

	वापस 0;
पूर्ण

/*
 * This function is called क्रम each pinctl 'Function' node.
 * Sub-nodes can be used to describe multiple 'Groups' for the 'Function'
 * If there aren't any sub-nodes, the 'Group' is essentially the 'Function'.
 * Each 'Group' uses pinmux = <...> to detail the pins and data used to select
 * the functionality. Each 'Group' has optional pin configurations that apply
 * to all pins in the 'Group'.
 */
अटल पूर्णांक rzn1_dt_node_to_map_one(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा device_node *np,
				   काष्ठा pinctrl_map **map,
				   अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा rzn1_pin_group *grp;
	अचिन्हित दीर्घ *configs = शून्य;
	अचिन्हित पूर्णांक reserved_maps = *num_maps;
	अचिन्हित पूर्णांक num_configs = 0;
	अचिन्हित पूर्णांक reserve = 1;
	पूर्णांक ret;

	dev_dbg(ipctl->dev, "processing node %pOF\n", np);

	grp = rzn1_pinctrl_find_group_by_name(ipctl, np->name);
	अगर (!grp) अणु
		dev_err(ipctl->dev, "unable to find group for node %pOF\n", np);

		वापस -EINVAL;
	पूर्ण

	/* Get the group's pin configuration */
	ret = pinconf_generic_parse_dt_config(np, pctldev, &configs,
					      &num_configs);
	अगर (ret < 0) अणु
		dev_err(ipctl->dev, "%pOF: could not parse property\n", np);

		वापस ret;
	पूर्ण

	अगर (num_configs)
		reserve++;

	/* Increase the number of maps to cover this group */
	ret = pinctrl_utils_reserve_map(pctldev, map, &reserved_maps, num_maps,
					reserve);
	अगर (ret < 0)
		जाओ out;

	/* Associate the group with the function */
	ret = pinctrl_utils_add_map_mux(pctldev, map, &reserved_maps, num_maps,
					grp->name, grp->func);
	अगर (ret < 0)
		जाओ out;

	अगर (num_configs) अणु
		/* Associate the group's pin configuration with the group */
		ret = pinctrl_utils_add_map_configs(pctldev, map,
				&reserved_maps, num_maps, grp->name,
				configs, num_configs,
				PIN_MAP_TYPE_CONFIGS_GROUP);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	dev_dbg(pctldev->dev, "maps: function %s group %s (%d pins)\n",
		grp->func, grp->name, grp->npins);

out:
	kमुक्त(configs);

	वापस ret;
पूर्ण

अटल पूर्णांक rzn1_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा device_node *np,
			       काष्ठा pinctrl_map **map,
			       अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा device_node *child;
	पूर्णांक ret;

	*map = शून्य;
	*num_maps = 0;

	ret = rzn1_dt_node_to_map_one(pctldev, np, map, num_maps);
	अगर (ret < 0)
		वापस ret;

	क्रम_each_child_of_node(np, child) अणु
		ret = rzn1_dt_node_to_map_one(pctldev, child, map, num_maps);
		अगर (ret < 0) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops rzn1_pctrl_ops = अणु
	.get_groups_count = rzn1_get_groups_count,
	.get_group_name = rzn1_get_group_name,
	.get_group_pins = rzn1_get_group_pins,
	.dt_node_to_map = rzn1_dt_node_to_map,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक rzn1_pmx_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);

	वापस ipctl->nfunctions;
पूर्ण

अटल स्थिर अक्षर *rzn1_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित पूर्णांक selector)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);

	वापस ipctl->functions[selector].name;
पूर्ण

अटल पूर्णांक rzn1_pmx_get_groups(काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित पूर्णांक selector,
			       स्थिर अक्षर * स्थिर **groups,
			       अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = ipctl->functions[selector].groups;
	*num_groups = ipctl->functions[selector].num_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक rzn1_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक selector,
			अचिन्हित पूर्णांक group)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा rzn1_pin_group *grp = &ipctl->groups[group];
	अचिन्हित पूर्णांक i, grp_pins = grp->npins;

	dev_dbg(ipctl->dev, "set mux %s(%d) group %s(%d)\n",
		ipctl->functions[selector].name, selector, grp->name, group);

	rzn1_hw_set_lock(ipctl, LOCK_ALL, LOCK_ALL);
	क्रम (i = 0; i < grp_pins; i++)
		rzn1_set_hw_pin_func(ipctl, grp->pins[i], grp->pin_ids[i], 0);
	rzn1_hw_set_lock(ipctl, LOCK_ALL, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops rzn1_pmx_ops = अणु
	.get_functions_count = rzn1_pmx_get_funcs_count,
	.get_function_name = rzn1_pmx_get_func_name,
	.get_function_groups = rzn1_pmx_get_groups,
	.set_mux = rzn1_set_mux,
पूर्ण;

अटल पूर्णांक rzn1_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			    अचिन्हित दीर्घ *config)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अटल स्थिर u32 reg_drive[4] = अणु 4, 6, 8, 12 पूर्ण;
	u32 pull, drive, l1mux;
	u32 l1, l2, arg = 0;

	अगर (pin >= ARRAY_SIZE(ipctl->lev1->conf))
		वापस -EINVAL;

	l1 = पढ़ोl(&ipctl->lev1->conf[pin]);

	l1mux = l1 & RZN1_L1_FUNC_MASK;
	pull = (l1 >> RZN1_L1_PIN_PULL) & 0x3;
	drive = (l1 >> RZN1_L1_PIN_DRIVE_STRENGTH) & 0x3;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (pull != RZN1_L1_PIN_PULL_UP)
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (pull != RZN1_L1_PIN_PULL_DOWN)
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pull != RZN1_L1_PIN_PULL_NONE)
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		arg = reg_drive[drive];
		अवरोध;
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		l2 = पढ़ोl(&ipctl->lev2->conf[pin]);
		अगर (l1mux == RZN1_L1_FUNCTION_L2) अणु
			अगर (l2 != 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (l1mux != RZN1_FUNC_HIGHZ) अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक rzn1_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			    अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	अचिन्हित पूर्णांक i;
	u32 l1, l1_cache;
	u32 drv;
	u32 arg;

	अगर (pin >= ARRAY_SIZE(ipctl->lev1->conf))
		वापस -EINVAL;

	l1 = पढ़ोl(&ipctl->lev1->conf[pin]);
	l1_cache = l1;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			dev_dbg(ipctl->dev, "set pin %d pull up\n", pin);
			l1 &= ~(0x3 << RZN1_L1_PIN_PULL);
			l1 |= (RZN1_L1_PIN_PULL_UP << RZN1_L1_PIN_PULL);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			dev_dbg(ipctl->dev, "set pin %d pull down\n", pin);
			l1 &= ~(0x3 << RZN1_L1_PIN_PULL);
			l1 |= (RZN1_L1_PIN_PULL_DOWN << RZN1_L1_PIN_PULL);
			अवरोध;
		हाल PIN_CONFIG_BIAS_DISABLE:
			dev_dbg(ipctl->dev, "set pin %d bias off\n", pin);
			l1 &= ~(0x3 << RZN1_L1_PIN_PULL);
			l1 |= (RZN1_L1_PIN_PULL_NONE << RZN1_L1_PIN_PULL);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			dev_dbg(ipctl->dev, "set pin %d drv %umA\n", pin, arg);
			चयन (arg) अणु
			हाल 4:
				drv = RZN1_L1_PIN_DRIVE_STRENGTH_4MA;
				अवरोध;
			हाल 6:
				drv = RZN1_L1_PIN_DRIVE_STRENGTH_6MA;
				अवरोध;
			हाल 8:
				drv = RZN1_L1_PIN_DRIVE_STRENGTH_8MA;
				अवरोध;
			हाल 12:
				drv = RZN1_L1_PIN_DRIVE_STRENGTH_12MA;
				अवरोध;
			शेष:
				dev_err(ipctl->dev,
					"Drive strength %umA not supported\n",
					arg);

				वापस -EINVAL;
			पूर्ण

			l1 &= ~(0x3 << RZN1_L1_PIN_DRIVE_STRENGTH);
			l1 |= (drv << RZN1_L1_PIN_DRIVE_STRENGTH);
			अवरोध;

		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			dev_dbg(ipctl->dev, "set pin %d High-Z\n", pin);
			l1 &= ~RZN1_L1_FUNC_MASK;
			l1 |= RZN1_FUNC_HIGHZ;
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	अगर (l1 != l1_cache) अणु
		rzn1_hw_set_lock(ipctl, LOCK_LEVEL1, LOCK_LEVEL1);
		ग_लिखोl(l1, &ipctl->lev1->conf[pin]);
		rzn1_hw_set_lock(ipctl, LOCK_LEVEL1, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rzn1_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector,
				  अचिन्हित दीर्घ *config)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा rzn1_pin_group *grp = &ipctl->groups[selector];
	अचिन्हित दीर्घ old = 0;
	अचिन्हित पूर्णांक i;

	dev_dbg(ipctl->dev, "group get %s selector:%u\n", grp->name, selector);

	क्रम (i = 0; i < grp->npins; i++) अणु
		अगर (rzn1_pinconf_get(pctldev, grp->pins[i], config))
			वापस -ENOTSUPP;

		/* configs करो not match between two pins */
		अगर (i && (old != *config))
			वापस -ENOTSUPP;

		old = *config;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rzn1_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector,
				  अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा rzn1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा rzn1_pin_group *grp = &ipctl->groups[selector];
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	dev_dbg(ipctl->dev, "group set %s selector:%u configs:%p/%d\n",
		grp->name, selector, configs, num_configs);

	क्रम (i = 0; i < grp->npins; i++) अणु
		अचिन्हित पूर्णांक pin = grp->pins[i];

		ret = rzn1_pinconf_set(pctldev, pin, configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops rzn1_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = rzn1_pinconf_get,
	.pin_config_set = rzn1_pinconf_set,
	.pin_config_group_get = rzn1_pinconf_group_get,
	.pin_config_group_set = rzn1_pinconf_group_set,
	.pin_config_config_dbg_show = pinconf_generic_dump_config,
पूर्ण;

अटल काष्ठा pinctrl_desc rzn1_pinctrl_desc = अणु
	.pctlops = &rzn1_pctrl_ops,
	.pmxops = &rzn1_pmx_ops,
	.confops = &rzn1_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक rzn1_pinctrl_parse_groups(काष्ठा device_node *np,
				     काष्ठा rzn1_pin_group *grp,
				     काष्ठा rzn1_pinctrl *ipctl)
अणु
	स्थिर __be32 *list;
	अचिन्हित पूर्णांक i;
	पूर्णांक size;

	dev_dbg(ipctl->dev, "%s: %s\n", __func__, np->name);

	/* Initialise group */
	grp->name = np->name;

	/*
	 * The binding क्रमmat is
	 *	pinmux = <PIN_FUNC_ID CONFIG ...>,
	 * करो sanity check and calculate pins number
	 */
	list = of_get_property(np, RZN1_PINS_PROP, &size);
	अगर (!list) अणु
		dev_err(ipctl->dev,
			"no " RZN1_PINS_PROP " property in node %pOF\n", np);

		वापस -EINVAL;
	पूर्ण

	अगर (!size) अणु
		dev_err(ipctl->dev, "Invalid " RZN1_PINS_PROP " in node %pOF\n",
			np);

		वापस -EINVAL;
	पूर्ण

	grp->npins = size / माप(list[0]);
	grp->pin_ids = devm_kदो_स्मृति_array(ipctl->dev,
					  grp->npins, माप(grp->pin_ids[0]),
					  GFP_KERNEL);
	grp->pins = devm_kदो_स्मृति_array(ipctl->dev,
				       grp->npins, माप(grp->pins[0]),
				       GFP_KERNEL);
	अगर (!grp->pin_ids || !grp->pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < grp->npins; i++) अणु
		u32 pin_id = be32_to_cpu(*list++);

		grp->pins[i] = pin_id & 0xff;
		grp->pin_ids[i] = (pin_id >> 8) & 0x7f;
	पूर्ण

	वापस grp->npins;
पूर्ण

अटल पूर्णांक rzn1_pinctrl_count_function_groups(काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	पूर्णांक count = 0;

	अगर (of_property_count_u32_elems(np, RZN1_PINS_PROP) > 0)
		count++;

	क्रम_each_child_of_node(np, child) अणु
		अगर (of_property_count_u32_elems(child, RZN1_PINS_PROP) > 0)
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक rzn1_pinctrl_parse_functions(काष्ठा device_node *np,
					काष्ठा rzn1_pinctrl *ipctl,
					अचिन्हित पूर्णांक index)
अणु
	काष्ठा rzn1_pmx_func *func;
	काष्ठा rzn1_pin_group *grp;
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक ret;

	func = &ipctl->functions[index];

	/* Initialise function */
	func->name = np->name;
	func->num_groups = rzn1_pinctrl_count_function_groups(np);
	अगर (func->num_groups == 0) अणु
		dev_err(ipctl->dev, "no groups defined in %pOF\n", np);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(ipctl->dev, "function %s has %d groups\n",
		np->name, func->num_groups);

	func->groups = devm_kदो_स्मृति_array(ipctl->dev,
					  func->num_groups, माप(अक्षर *),
					  GFP_KERNEL);
	अगर (!func->groups)
		वापस -ENOMEM;

	अगर (of_property_count_u32_elems(np, RZN1_PINS_PROP) > 0) अणु
		func->groups[i] = np->name;
		grp = &ipctl->groups[ipctl->ngroups];
		grp->func = func->name;
		ret = rzn1_pinctrl_parse_groups(np, grp, ipctl);
		अगर (ret < 0)
			वापस ret;
		i++;
		ipctl->ngroups++;
	पूर्ण

	क्रम_each_child_of_node(np, child) अणु
		func->groups[i] = child->name;
		grp = &ipctl->groups[ipctl->ngroups];
		grp->func = func->name;
		ret = rzn1_pinctrl_parse_groups(child, grp, ipctl);
		अगर (ret < 0) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
		i++;
		ipctl->ngroups++;
	पूर्ण

	dev_dbg(ipctl->dev, "function %s parsed %u/%u groups\n",
		np->name, i, func->num_groups);

	वापस 0;
पूर्ण

अटल पूर्णांक rzn1_pinctrl_probe_dt(काष्ठा platक्रमm_device *pdev,
				 काष्ठा rzn1_pinctrl *ipctl)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक maxgroups = 0;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक nfuncs = 0;
	पूर्णांक ret;

	nfuncs = of_get_child_count(np);
	अगर (nfuncs <= 0)
		वापस 0;

	ipctl->nfunctions = nfuncs;
	ipctl->functions = devm_kदो_स्मृति_array(&pdev->dev, nfuncs,
					      माप(*ipctl->functions),
					      GFP_KERNEL);
	अगर (!ipctl->functions)
		वापस -ENOMEM;

	ipctl->ngroups = 0;
	क्रम_each_child_of_node(np, child)
		maxgroups += rzn1_pinctrl_count_function_groups(child);

	ipctl->groups = devm_kदो_स्मृति_array(&pdev->dev,
					   maxgroups,
					   माप(*ipctl->groups),
					   GFP_KERNEL);
	अगर (!ipctl->groups)
		वापस -ENOMEM;

	क्रम_each_child_of_node(np, child) अणु
		ret = rzn1_pinctrl_parse_functions(child, ipctl, i++);
		अगर (ret < 0) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rzn1_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rzn1_pinctrl *ipctl;
	काष्ठा resource *res;
	पूर्णांक ret;

	/* Create state holders etc क्रम this driver */
	ipctl = devm_kzalloc(&pdev->dev, माप(*ipctl), GFP_KERNEL);
	अगर (!ipctl)
		वापस -ENOMEM;

	ipctl->mdio_func[0] = -1;
	ipctl->mdio_func[1] = -1;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ipctl->lev1_protect_phys = (u32)res->start + 0x400;
	ipctl->lev1 = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ipctl->lev1))
		वापस PTR_ERR(ipctl->lev1);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	ipctl->lev2_protect_phys = (u32)res->start + 0x400;
	ipctl->lev2 = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ipctl->lev2))
		वापस PTR_ERR(ipctl->lev2);

	ipctl->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ipctl->clk))
		वापस PTR_ERR(ipctl->clk);
	ret = clk_prepare_enable(ipctl->clk);
	अगर (ret)
		वापस ret;

	ipctl->dev = &pdev->dev;
	rzn1_pinctrl_desc.name = dev_name(&pdev->dev);
	rzn1_pinctrl_desc.pins = rzn1_pins;
	rzn1_pinctrl_desc.npins = ARRAY_SIZE(rzn1_pins);

	ret = rzn1_pinctrl_probe_dt(pdev, ipctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "fail to probe dt properties\n");
		जाओ err_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ipctl);

	ret = devm_pinctrl_रेजिस्टर_and_init(&pdev->dev, &rzn1_pinctrl_desc,
					     ipctl, &ipctl->pctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register rzn1 pinctrl driver\n");
		जाओ err_clk;
	पूर्ण

	ret = pinctrl_enable(ipctl->pctl);
	अगर (ret)
		जाओ err_clk;

	dev_info(&pdev->dev, "probed\n");

	वापस 0;

err_clk:
	clk_disable_unprepare(ipctl->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक rzn1_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rzn1_pinctrl *ipctl = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(ipctl->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rzn1_pinctrl_match[] = अणु
	अणु .compatible = "renesas,rzn1-pinctrl", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rzn1_pinctrl_match);

अटल काष्ठा platक्रमm_driver rzn1_pinctrl_driver = अणु
	.probe	= rzn1_pinctrl_probe,
	.हटाओ = rzn1_pinctrl_हटाओ,
	.driver	= अणु
		.name		= "rzn1-pinctrl",
		.of_match_table	= rzn1_pinctrl_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init _pinctrl_drv_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rzn1_pinctrl_driver);
पूर्ण
subsys_initcall(_pinctrl_drv_रेजिस्टर);

MODULE_AUTHOR("Phil Edworthy <phil.edworthy@renesas.com>");
MODULE_DESCRIPTION("Renesas RZ/N1 pinctrl driver");
MODULE_LICENSE("GPL v2");
