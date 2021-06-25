<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा FLAG_BCM4708		BIT(1)
#घोषणा FLAG_BCM4709		BIT(2)
#घोषणा FLAG_BCM53012		BIT(3)

काष्ठा ns_pinctrl अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक chipset_flag;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा regmap *regmap;
	u32 offset;

	काष्ठा pinctrl_desc pctldesc;
	काष्ठा ns_pinctrl_group *groups;
	अचिन्हित पूर्णांक num_groups;
	काष्ठा ns_pinctrl_function *functions;
	अचिन्हित पूर्णांक num_functions;
पूर्ण;

/*
 * Pins
 */

अटल स्थिर काष्ठा pinctrl_pin_desc ns_pinctrl_pins[] = अणु
	अणु 0, "spi_clk", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 1, "spi_ss", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 2, "spi_mosi", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 3, "spi_miso", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 4, "i2c_scl", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 5, "i2c_sda", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 6, "mdc", (व्योम *)(FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 7, "mdio", (व्योम *)(FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 8, "pwm0", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 9, "pwm1", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 10, "pwm2", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 11, "pwm3", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 12, "uart1_rx", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 13, "uart1_tx", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 14, "uart1_cts", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 15, "uart1_rts", (व्योम *)(FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 16, "uart2_rx", (व्योम *)(FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 17, "uart2_tx", (व्योम *)(FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
/* TODO अणु ??, "xtal_out", (व्योम *)(FLAG_BCM4709) पूर्ण, */
	अणु 22, "sdio_pwr", (व्योम *)(FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
	अणु 23, "sdio_en_1p8v", (व्योम *)(FLAG_BCM4709 | FLAG_BCM53012) पूर्ण,
पूर्ण;

/*
 * Groups
 */

काष्ठा ns_pinctrl_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक num_pins;
	अचिन्हित पूर्णांक chipsets;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक spi_pins[] = अणु 0, 1, 2, 3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_pins[] = अणु 4, 5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mdio_pins[] = अणु 6, 7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm0_pins[] = अणु 8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm1_pins[] = अणु 9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm2_pins[] = अणु 10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm3_pins[] = अणु 11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_pins[] = अणु 12, 13, 14, 15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart2_pins[] = अणु 16, 17 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_pwr_pins[] = अणु 22 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_1p8v_pins[] = अणु 23 पूर्ण;

#घोषणा NS_GROUP(_name, _pins, _chipsets)		\
अणु							\
	.name = _name,					\
	.pins = _pins,					\
	.num_pins = ARRAY_SIZE(_pins),			\
	.chipsets = _chipsets,				\
पूर्ण

अटल स्थिर काष्ठा ns_pinctrl_group ns_pinctrl_groups[] = अणु
	NS_GROUP("spi_grp", spi_pins, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("i2c_grp", i2c_pins, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("mdio_grp", mdio_pins, FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("pwm0_grp", pwm0_pins, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("pwm1_grp", pwm1_pins, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("pwm2_grp", pwm2_pins, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("pwm3_grp", pwm3_pins, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("uart1_grp", uart1_pins, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("uart2_grp", uart2_pins, FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("sdio_pwr_grp", sdio_pwr_pins, FLAG_BCM4709 | FLAG_BCM53012),
	NS_GROUP("sdio_1p8v_grp", sdio_1p8v_pins, FLAG_BCM4709 | FLAG_BCM53012),
पूर्ण;

/*
 * Functions
 */

काष्ठा ns_pinctrl_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित पूर्णांक num_groups;
	अचिन्हित पूर्णांक chipsets;
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_groups[] = अणु "spi_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c_groups[] = अणु "i2c_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mdio_groups[] = अणु "mdio_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm_groups[] = अणु "pwm0_grp", "pwm1_grp", "pwm2_grp",
					   "pwm3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart1_groups[] = अणु "uart1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart2_groups[] = अणु "uart2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio_groups[] = अणु "sdio_pwr_grp", "sdio_1p8v_grp" पूर्ण;

#घोषणा NS_FUNCTION(_name, _groups, _chipsets)		\
अणु							\
	.name = _name,					\
	.groups = _groups,				\
	.num_groups = ARRAY_SIZE(_groups),		\
	.chipsets = _chipsets,				\
पूर्ण

अटल स्थिर काष्ठा ns_pinctrl_function ns_pinctrl_functions[] = अणु
	NS_FUNCTION("spi", spi_groups, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_FUNCTION("i2c", i2c_groups, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_FUNCTION("mdio", mdio_groups, FLAG_BCM4709 | FLAG_BCM53012),
	NS_FUNCTION("pwm", pwm_groups, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_FUNCTION("uart1", uart1_groups, FLAG_BCM4708 | FLAG_BCM4709 | FLAG_BCM53012),
	NS_FUNCTION("uart2", uart2_groups, FLAG_BCM4709 | FLAG_BCM53012),
	NS_FUNCTION("sdio", sdio_groups, FLAG_BCM4709 | FLAG_BCM53012),
पूर्ण;

/*
 * Groups code
 */

अटल पूर्णांक ns_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस ns_pinctrl->num_groups;
पूर्ण

अटल स्थिर अक्षर *ns_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctrl_dev,
					     अचिन्हित पूर्णांक selector)
अणु
	काष्ठा ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस ns_pinctrl->groups[selector].name;
पूर्ण

अटल पूर्णांक ns_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctrl_dev,
				     अचिन्हित पूर्णांक selector,
				     स्थिर अचिन्हित पूर्णांक **pins,
				     अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*pins = ns_pinctrl->groups[selector].pins;
	*num_pins = ns_pinctrl->groups[selector].num_pins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops ns_pinctrl_ops = अणु
	.get_groups_count = ns_pinctrl_get_groups_count,
	.get_group_name = ns_pinctrl_get_group_name,
	.get_group_pins = ns_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

/*
 * Functions code
 */

अटल पूर्णांक ns_pinctrl_get_functions_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस ns_pinctrl->num_functions;
पूर्ण

अटल स्थिर अक्षर *ns_pinctrl_get_function_name(काष्ठा pinctrl_dev *pctrl_dev,
						अचिन्हित पूर्णांक selector)
अणु
	काष्ठा ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस ns_pinctrl->functions[selector].name;
पूर्ण

अटल पूर्णांक ns_pinctrl_get_function_groups(काष्ठा pinctrl_dev *pctrl_dev,
					  अचिन्हित पूर्णांक selector,
					  स्थिर अक्षर * स्थिर **groups,
					  अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*groups = ns_pinctrl->functions[selector].groups;
	*num_groups = ns_pinctrl->functions[selector].num_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक ns_pinctrl_set_mux(काष्ठा pinctrl_dev *pctrl_dev,
			      अचिन्हित पूर्णांक func_select,
			      अचिन्हित पूर्णांक grp_select)
अणु
	काष्ठा ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	u32 unset = 0;
	u32 पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < ns_pinctrl->groups[grp_select].num_pins; i++) अणु
		पूर्णांक pin_number = ns_pinctrl->groups[grp_select].pins[i];

		unset |= BIT(pin_number);
	पूर्ण

	regmap_पढ़ो(ns_pinctrl->regmap, ns_pinctrl->offset, &पंचांगp);
	पंचांगp &= ~unset;
	regmap_ग_लिखो(ns_pinctrl->regmap, ns_pinctrl->offset, पंचांगp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops ns_pinctrl_pmxops = अणु
	.get_functions_count = ns_pinctrl_get_functions_count,
	.get_function_name = ns_pinctrl_get_function_name,
	.get_function_groups = ns_pinctrl_get_function_groups,
	.set_mux = ns_pinctrl_set_mux,
पूर्ण;

/*
 * Controller code
 */

अटल काष्ठा pinctrl_desc ns_pinctrl_desc = अणु
	.name = "pinctrl-ns",
	.pctlops = &ns_pinctrl_ops,
	.pmxops = &ns_pinctrl_pmxops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ns_pinctrl_of_match_table[] = अणु
	अणु .compatible = "brcm,bcm4708-pinmux", .data = (व्योम *)FLAG_BCM4708, पूर्ण,
	अणु .compatible = "brcm,bcm4709-pinmux", .data = (व्योम *)FLAG_BCM4709, पूर्ण,
	अणु .compatible = "brcm,bcm53012-pinmux", .data = (व्योम *)FLAG_BCM53012, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक ns_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा ns_pinctrl *ns_pinctrl;
	काष्ठा pinctrl_desc *pctldesc;
	काष्ठा pinctrl_pin_desc *pin;
	काष्ठा ns_pinctrl_group *group;
	काष्ठा ns_pinctrl_function *function;
	पूर्णांक i;

	ns_pinctrl = devm_kzalloc(dev, माप(*ns_pinctrl), GFP_KERNEL);
	अगर (!ns_pinctrl)
		वापस -ENOMEM;
	pctldesc = &ns_pinctrl->pctldesc;
	platक्रमm_set_drvdata(pdev, ns_pinctrl);

	/* Set basic properties */

	ns_pinctrl->dev = dev;

	of_id = of_match_device(ns_pinctrl_of_match_table, dev);
	अगर (!of_id)
		वापस -EINVAL;
	ns_pinctrl->chipset_flag = (uपूर्णांकptr_t)of_id->data;

	ns_pinctrl->regmap = syscon_node_to_regmap(of_get_parent(np));
	अगर (IS_ERR(ns_pinctrl->regmap)) अणु
		पूर्णांक err = PTR_ERR(ns_pinctrl->regmap);

		dev_err(dev, "Failed to map pinctrl regs: %d\n", err);

		वापस err;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "offset", &ns_pinctrl->offset)) अणु
		dev_err(dev, "Failed to get register offset\n");
		वापस -ENOENT;
	पूर्ण

	स_नकल(pctldesc, &ns_pinctrl_desc, माप(*pctldesc));

	/* Set pinctrl properties */

	pctldesc->pins = devm_kसुस्मृति(dev, ARRAY_SIZE(ns_pinctrl_pins),
				      माप(काष्ठा pinctrl_pin_desc),
				      GFP_KERNEL);
	अगर (!pctldesc->pins)
		वापस -ENOMEM;
	क्रम (i = 0, pin = (काष्ठा pinctrl_pin_desc *)&pctldesc->pins[0];
	     i < ARRAY_SIZE(ns_pinctrl_pins); i++) अणु
		स्थिर काष्ठा pinctrl_pin_desc *src = &ns_pinctrl_pins[i];
		अचिन्हित पूर्णांक chipsets = (uपूर्णांकptr_t)src->drv_data;

		अगर (chipsets & ns_pinctrl->chipset_flag) अणु
			स_नकल(pin++, src, माप(*src));
			pctldesc->npins++;
		पूर्ण
	पूर्ण

	ns_pinctrl->groups = devm_kसुस्मृति(dev, ARRAY_SIZE(ns_pinctrl_groups),
					  माप(काष्ठा ns_pinctrl_group),
					  GFP_KERNEL);
	अगर (!ns_pinctrl->groups)
		वापस -ENOMEM;
	क्रम (i = 0, group = &ns_pinctrl->groups[0];
	     i < ARRAY_SIZE(ns_pinctrl_groups); i++) अणु
		स्थिर काष्ठा ns_pinctrl_group *src = &ns_pinctrl_groups[i];

		अगर (src->chipsets & ns_pinctrl->chipset_flag) अणु
			स_नकल(group++, src, माप(*src));
			ns_pinctrl->num_groups++;
		पूर्ण
	पूर्ण

	ns_pinctrl->functions = devm_kसुस्मृति(dev,
					     ARRAY_SIZE(ns_pinctrl_functions),
					     माप(काष्ठा ns_pinctrl_function),
					     GFP_KERNEL);
	अगर (!ns_pinctrl->functions)
		वापस -ENOMEM;
	क्रम (i = 0, function = &ns_pinctrl->functions[0];
	     i < ARRAY_SIZE(ns_pinctrl_functions); i++) अणु
		स्थिर काष्ठा ns_pinctrl_function *src = &ns_pinctrl_functions[i];

		अगर (src->chipsets & ns_pinctrl->chipset_flag) अणु
			स_नकल(function++, src, माप(*src));
			ns_pinctrl->num_functions++;
		पूर्ण
	पूर्ण

	/* Register */

	ns_pinctrl->pctldev = devm_pinctrl_रेजिस्टर(dev, pctldesc, ns_pinctrl);
	अगर (IS_ERR(ns_pinctrl->pctldev)) अणु
		dev_err(dev, "Failed to register pinctrl\n");
		वापस PTR_ERR(ns_pinctrl->pctldev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ns_pinctrl_driver = अणु
	.probe = ns_pinctrl_probe,
	.driver = अणु
		.name = "ns-pinmux",
		.of_match_table = ns_pinctrl_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ns_pinctrl_driver);

MODULE_AUTHOR("Rafaध Miधecki");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, ns_pinctrl_of_match_table);
