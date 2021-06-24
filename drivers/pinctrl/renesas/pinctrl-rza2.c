<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Combined GPIO and pin controller support क्रम Renesas RZ/A2 (R7S9210) SoC
 *
 * Copyright (C) 2018 Chris Bअक्रमt
 */

/*
 * This pin controller/gpio combined driver supports Renesas devices of RZ/A2
 * family.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinmux.h>

#समावेश "../core.h"
#समावेश "../pinmux.h"

#घोषणा DRIVER_NAME		"pinctrl-rza2"

#घोषणा RZA2_PINS_PER_PORT	8
#घोषणा RZA2_PIN_ID_TO_PORT(id)	((id) / RZA2_PINS_PER_PORT)
#घोषणा RZA2_PIN_ID_TO_PIN(id)	((id) % RZA2_PINS_PER_PORT)

/*
 * Use 16 lower bits [15:0] क्रम pin identअगरier
 * Use 16 higher bits [31:16] क्रम pin mux function
 */
#घोषणा MUX_PIN_ID_MASK		GENMASK(15, 0)
#घोषणा MUX_FUNC_MASK		GENMASK(31, 16)
#घोषणा MUX_FUNC_OFFS		16
#घोषणा MUX_FUNC(pinconf)	((pinconf & MUX_FUNC_MASK) >> MUX_FUNC_OFFS)

अटल स्थिर अक्षर port_names[] = "0123456789ABCDEFGHJKLM";

काष्ठा rza2_pinctrl_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *base;

	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा pinctrl_desc desc;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा pinctrl_gpio_range gpio_range;
	पूर्णांक npins;
पूर्ण;

#घोषणा RZA2_PDR(port)		(0x0000 + (port) * 2)	/* Direction 16-bit */
#घोषणा RZA2_PODR(port)		(0x0040 + (port))	/* Output Data 8-bit */
#घोषणा RZA2_PIDR(port)		(0x0060 + (port))	/* Input Data 8-bit */
#घोषणा RZA2_PMR(port)		(0x0080 + (port))	/* Mode 8-bit */
#घोषणा RZA2_DSCR(port)		(0x0140 + (port) * 2)	/* Drive 16-bit */
#घोषणा RZA2_PFS(port, pin)	(0x0200 + ((port) * 8) + (pin))	/* Fnct 8-bit */

#घोषणा RZA2_PWPR		0x02ff	/* Write Protect 8-bit */
#घोषणा RZA2_PFENET		0x0820	/* Ethernet Pins 8-bit */
#घोषणा RZA2_PPOC		0x0900	/* Dedicated Pins 32-bit */
#घोषणा RZA2_PHMOMO		0x0980	/* Peripheral Pins 32-bit */
#घोषणा RZA2_PCKIO		0x09d0	/* CKIO Drive 8-bit */

#घोषणा RZA2_PDR_INPUT		0x02
#घोषणा RZA2_PDR_OUTPUT		0x03
#घोषणा RZA2_PDR_MASK		0x03

#घोषणा PWPR_B0WI		BIT(7)	/* Bit Write Disable */
#घोषणा PWPR_PFSWE		BIT(6)	/* PFS Register Write Enable */
#घोषणा PFS_ISEL		BIT(6)	/* Interrupt Select */

अटल व्योम rza2_set_pin_function(व्योम __iomem *pfc_base, u8 port, u8 pin,
				  u8 func)
अणु
	u16 mask16;
	u16 reg16;
	u8 reg8;

	/* Set pin to 'Non-use (Hi-z input protection)'  */
	reg16 = पढ़ोw(pfc_base + RZA2_PDR(port));
	mask16 = RZA2_PDR_MASK << (pin * 2);
	reg16 &= ~mask16;
	ग_लिखोw(reg16, pfc_base + RZA2_PDR(port));

	/* Temporarily चयन to GPIO */
	reg8 = पढ़ोb(pfc_base + RZA2_PMR(port));
	reg8 &= ~BIT(pin);
	ग_लिखोb(reg8, pfc_base + RZA2_PMR(port));

	/* PFS Register Write Protect : OFF */
	ग_लिखोb(0x00, pfc_base + RZA2_PWPR);		/* B0WI=0, PFSWE=0 */
	ग_लिखोb(PWPR_PFSWE, pfc_base + RZA2_PWPR);	/* B0WI=0, PFSWE=1 */

	/* Set Pin function (पूर्णांकerrupt disabled, ISEL=0) */
	ग_लिखोb(func, pfc_base + RZA2_PFS(port, pin));

	/* PFS Register Write Protect : ON */
	ग_लिखोb(0x00, pfc_base + RZA2_PWPR);	/* B0WI=0, PFSWE=0 */
	ग_लिखोb(0x80, pfc_base + RZA2_PWPR);	/* B0WI=1, PFSWE=0 */

	/* Port Mode  : Peripheral module pin functions */
	reg8 = पढ़ोb(pfc_base + RZA2_PMR(port));
	reg8 |= BIT(pin);
	ग_लिखोb(reg8, pfc_base + RZA2_PMR(port));
पूर्ण

अटल व्योम rza2_pin_to_gpio(व्योम __iomem *pfc_base, अचिन्हित पूर्णांक offset,
			     u8 dir)
अणु
	u8 port = RZA2_PIN_ID_TO_PORT(offset);
	u8 pin = RZA2_PIN_ID_TO_PIN(offset);
	u16 mask16;
	u16 reg16;

	reg16 = पढ़ोw(pfc_base + RZA2_PDR(port));
	mask16 = RZA2_PDR_MASK << (pin * 2);
	reg16 &= ~mask16;

	अगर (dir)
		reg16 |= RZA2_PDR_INPUT << (pin * 2);	/* pin as input */
	अन्यथा
		reg16 |= RZA2_PDR_OUTPUT << (pin * 2);	/* pin as output */

	ग_लिखोw(reg16, pfc_base + RZA2_PDR(port));
पूर्ण

अटल पूर्णांक rza2_chip_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा rza2_pinctrl_priv *priv = gpiochip_get_data(chip);
	u8 port = RZA2_PIN_ID_TO_PORT(offset);
	u8 pin = RZA2_PIN_ID_TO_PIN(offset);
	u16 reg16;

	reg16 = पढ़ोw(priv->base + RZA2_PDR(port));
	reg16 = (reg16 >> (pin * 2)) & RZA2_PDR_MASK;

	अगर (reg16 == RZA2_PDR_OUTPUT)
		वापस GPIO_LINE_सूचीECTION_OUT;

	अगर (reg16 == RZA2_PDR_INPUT)
		वापस GPIO_LINE_सूचीECTION_IN;

	/*
	 * This GPIO controller has a शेष Hi-Z state that is not input or
	 * output, so क्रमce the pin to input now.
	 */
	rza2_pin_to_gpio(priv->base, offset, 1);

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक rza2_chip_direction_input(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा rza2_pinctrl_priv *priv = gpiochip_get_data(chip);

	rza2_pin_to_gpio(priv->base, offset, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक rza2_chip_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा rza2_pinctrl_priv *priv = gpiochip_get_data(chip);
	u8 port = RZA2_PIN_ID_TO_PORT(offset);
	u8 pin = RZA2_PIN_ID_TO_PIN(offset);

	वापस !!(पढ़ोb(priv->base + RZA2_PIDR(port)) & BIT(pin));
पूर्ण

अटल व्योम rza2_chip_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			  पूर्णांक value)
अणु
	काष्ठा rza2_pinctrl_priv *priv = gpiochip_get_data(chip);
	u8 port = RZA2_PIN_ID_TO_PORT(offset);
	u8 pin = RZA2_PIN_ID_TO_PIN(offset);
	u8 new_value;

	new_value = पढ़ोb(priv->base + RZA2_PODR(port));

	अगर (value)
		new_value |= BIT(pin);
	अन्यथा
		new_value &= ~BIT(pin);

	ग_लिखोb(new_value, priv->base + RZA2_PODR(port));
पूर्ण

अटल पूर्णांक rza2_chip_direction_output(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा rza2_pinctrl_priv *priv = gpiochip_get_data(chip);

	rza2_chip_set(chip, offset, val);
	rza2_pin_to_gpio(priv->base, offset, 0);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर rza2_gpio_names[] = अणु
	"P0_0", "P0_1", "P0_2", "P0_3", "P0_4", "P0_5", "P0_6", "P0_7",
	"P1_0", "P1_1", "P1_2", "P1_3", "P1_4", "P1_5", "P1_6", "P1_7",
	"P2_0", "P2_1", "P2_2", "P2_3", "P2_4", "P2_5", "P2_6", "P2_7",
	"P3_0", "P3_1", "P3_2", "P3_3", "P3_4", "P3_5", "P3_6", "P3_7",
	"P4_0", "P4_1", "P4_2", "P4_3", "P4_4", "P4_5", "P4_6", "P4_7",
	"P5_0", "P5_1", "P5_2", "P5_3", "P5_4", "P5_5", "P5_6", "P5_7",
	"P6_0", "P6_1", "P6_2", "P6_3", "P6_4", "P6_5", "P6_6", "P6_7",
	"P7_0", "P7_1", "P7_2", "P7_3", "P7_4", "P7_5", "P7_6", "P7_7",
	"P8_0", "P8_1", "P8_2", "P8_3", "P8_4", "P8_5", "P8_6", "P8_7",
	"P9_0", "P9_1", "P9_2", "P9_3", "P9_4", "P9_5", "P9_6", "P9_7",
	"PA_0", "PA_1", "PA_2", "PA_3", "PA_4", "PA_5", "PA_6", "PA_7",
	"PB_0", "PB_1", "PB_2", "PB_3", "PB_4", "PB_5", "PB_6", "PB_7",
	"PC_0", "PC_1", "PC_2", "PC_3", "PC_4", "PC_5", "PC_6", "PC_7",
	"PD_0", "PD_1", "PD_2", "PD_3", "PD_4", "PD_5", "PD_6", "PD_7",
	"PE_0", "PE_1", "PE_2", "PE_3", "PE_4", "PE_5", "PE_6", "PE_7",
	"PF_0", "PF_1", "PF_2", "PF_3", "PF_4", "PF_5", "PF_6", "PF_7",
	"PG_0", "PG_1", "PG_2", "PG_3", "PG_4", "PG_5", "PG_6", "PG_7",
	"PH_0", "PH_1", "PH_2", "PH_3", "PH_4", "PH_5", "PH_6", "PH_7",
	/* port I करोes not exist */
	"PJ_0", "PJ_1", "PJ_2", "PJ_3", "PJ_4", "PJ_5", "PJ_6", "PJ_7",
	"PK_0", "PK_1", "PK_2", "PK_3", "PK_4", "PK_5", "PK_6", "PK_7",
	"PL_0", "PL_1", "PL_2", "PL_3", "PL_4", "PL_5", "PL_6", "PL_7",
	"PM_0", "PM_1", "PM_2", "PM_3", "PM_4", "PM_5", "PM_6", "PM_7",
पूर्ण;

अटल काष्ठा gpio_chip chip = अणु
	.names = rza2_gpio_names,
	.base = -1,
	.get_direction = rza2_chip_get_direction,
	.direction_input = rza2_chip_direction_input,
	.direction_output = rza2_chip_direction_output,
	.get = rza2_chip_get,
	.set = rza2_chip_set,
पूर्ण;

अटल पूर्णांक rza2_gpio_रेजिस्टर(काष्ठा rza2_pinctrl_priv *priv)
अणु
	काष्ठा device_node *np = priv->dev->of_node;
	काष्ठा of_phandle_args of_args;
	पूर्णांक ret;

	chip.label = devm_kaप्र_लिखो(priv->dev, GFP_KERNEL, "%pOFn", np);
	chip.of_node = np;
	chip.parent = priv->dev;
	chip.ngpio = priv->npins;

	ret = of_parse_phandle_with_fixed_args(np, "gpio-ranges", 3, 0,
					       &of_args);
	अगर (ret) अणु
		dev_err(priv->dev, "Unable to parse gpio-ranges\n");
		वापस ret;
	पूर्ण

	अगर ((of_args.args[0] != 0) ||
	    (of_args.args[1] != 0) ||
	    (of_args.args[2] != priv->npins)) अणु
		dev_err(priv->dev, "gpio-ranges does not match selected SOC\n");
		वापस -EINVAL;
	पूर्ण
	priv->gpio_range.id = 0;
	priv->gpio_range.pin_base = priv->gpio_range.base = 0;
	priv->gpio_range.npins = priv->npins;
	priv->gpio_range.name = chip.label;
	priv->gpio_range.gc = &chip;

	/* Register our gpio chip with gpiolib */
	ret = devm_gpiochip_add_data(priv->dev, &chip, priv);
	अगर (ret)
		वापस ret;

	/* Register pin range with pinctrl core */
	pinctrl_add_gpio_range(priv->pctl, &priv->gpio_range);

	dev_dbg(priv->dev, "Registered gpio controller\n");

	वापस 0;
पूर्ण

अटल पूर्णांक rza2_pinctrl_रेजिस्टर(काष्ठा rza2_pinctrl_priv *priv)
अणु
	काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	pins = devm_kसुस्मृति(priv->dev, priv->npins, माप(*pins), GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	priv->pins = pins;
	priv->desc.pins = pins;
	priv->desc.npins = priv->npins;

	क्रम (i = 0; i < priv->npins; i++) अणु
		pins[i].number = i;
		pins[i].name = rza2_gpio_names[i];
	पूर्ण

	ret = devm_pinctrl_रेजिस्टर_and_init(priv->dev, &priv->desc, priv,
					     &priv->pctl);
	अगर (ret) अणु
		dev_err(priv->dev, "pinctrl registration failed\n");
		वापस ret;
	पूर्ण

	ret = pinctrl_enable(priv->pctl);
	अगर (ret) अणु
		dev_err(priv->dev, "pinctrl enable failed\n");
		वापस ret;
	पूर्ण

	ret = rza2_gpio_रेजिस्टर(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "GPIO registration failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * For each DT node, create a single pin mapping. That pin mapping will only
 * contain a single group of pins, and that group of pins will only have a
 * single function that can be selected.
 */
अटल पूर्णांक rza2_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा device_node *np,
			       काष्ठा pinctrl_map **map,
			       अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा rza2_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक *pins, *psel_val;
	पूर्णांक i, ret, npins, gsel, fsel;
	काष्ठा property *of_pins;
	स्थिर अक्षर **pin_fn;

	/* Find out how many pins to map */
	of_pins = of_find_property(np, "pinmux", शून्य);
	अगर (!of_pins) अणु
		dev_info(priv->dev, "Missing pinmux property\n");
		वापस -ENOENT;
	पूर्ण
	npins = of_pins->length / माप(u32);

	pins = devm_kसुस्मृति(priv->dev, npins, माप(*pins), GFP_KERNEL);
	psel_val = devm_kसुस्मृति(priv->dev, npins, माप(*psel_val),
				GFP_KERNEL);
	pin_fn = devm_kzalloc(priv->dev, माप(*pin_fn), GFP_KERNEL);
	अगर (!pins || !psel_val || !pin_fn)
		वापस -ENOMEM;

	/* Collect pin locations and mux settings from DT properties */
	क्रम (i = 0; i < npins; ++i) अणु
		u32 value;

		ret = of_property_पढ़ो_u32_index(np, "pinmux", i, &value);
		अगर (ret)
			वापस ret;
		pins[i] = value & MUX_PIN_ID_MASK;
		psel_val[i] = MUX_FUNC(value);
	पूर्ण

	/* Register a single pin group listing all the pins we पढ़ो from DT */
	gsel = pinctrl_generic_add_group(pctldev, np->name, pins, npins, शून्य);
	अगर (gsel < 0)
		वापस gsel;

	/*
	 * Register a single group function where the 'data' is an array PSEL
	 * रेजिस्टर values पढ़ो from DT.
	 */
	pin_fn[0] = np->name;
	fsel = pinmux_generic_add_function(pctldev, np->name, pin_fn, 1,
					   psel_val);
	अगर (fsel < 0) अणु
		ret = fsel;
		जाओ हटाओ_group;
	पूर्ण

	dev_dbg(priv->dev, "Parsed %pOF with %d pins\n", np, npins);

	/* Create map where to retrieve function and mux settings from */
	*num_maps = 0;
	*map = kzalloc(माप(**map), GFP_KERNEL);
	अगर (!*map) अणु
		ret = -ENOMEM;
		जाओ हटाओ_function;
	पूर्ण

	(*map)->type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)->data.mux.group = np->name;
	(*map)->data.mux.function = np->name;
	*num_maps = 1;

	वापस 0;

हटाओ_function:
	pinmux_generic_हटाओ_function(pctldev, fsel);

हटाओ_group:
	pinctrl_generic_हटाओ_group(pctldev, gsel);

	dev_err(priv->dev, "Unable to parse DT node %s\n", np->name);

	वापस ret;
पूर्ण

अटल व्योम rza2_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
			     काष्ठा pinctrl_map *map, अचिन्हित पूर्णांक num_maps)
अणु
	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops rza2_pinctrl_ops = अणु
	.get_groups_count	= pinctrl_generic_get_group_count,
	.get_group_name		= pinctrl_generic_get_group_name,
	.get_group_pins		= pinctrl_generic_get_group_pins,
	.dt_node_to_map		= rza2_dt_node_to_map,
	.dt_मुक्त_map		= rza2_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक rza2_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक selector,
			अचिन्हित पूर्णांक group)
अणु
	काष्ठा rza2_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा function_desc *func;
	अचिन्हित पूर्णांक i, *psel_val;
	काष्ठा group_desc *grp;

	grp = pinctrl_generic_get_group(pctldev, group);
	अगर (!grp)
		वापस -EINVAL;

	func = pinmux_generic_get_function(pctldev, selector);
	अगर (!func)
		वापस -EINVAL;

	psel_val = func->data;

	क्रम (i = 0; i < grp->num_pins; ++i) अणु
		dev_dbg(priv->dev, "Setting P%c_%d to PSEL=%d\n",
			port_names[RZA2_PIN_ID_TO_PORT(grp->pins[i])],
			RZA2_PIN_ID_TO_PIN(grp->pins[i]),
			psel_val[i]);
		rza2_set_pin_function(
			priv->base,
			RZA2_PIN_ID_TO_PORT(grp->pins[i]),
			RZA2_PIN_ID_TO_PIN(grp->pins[i]),
			psel_val[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops rza2_pinmux_ops = अणु
	.get_functions_count	= pinmux_generic_get_function_count,
	.get_function_name	= pinmux_generic_get_function_name,
	.get_function_groups	= pinmux_generic_get_function_groups,
	.set_mux		= rza2_set_mux,
	.strict			= true,
पूर्ण;

अटल पूर्णांक rza2_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rza2_pinctrl_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	platक्रमm_set_drvdata(pdev, priv);

	priv->npins = (पूर्णांक)(uपूर्णांकptr_t)of_device_get_match_data(&pdev->dev) *
		      RZA2_PINS_PER_PORT;

	priv->desc.name		= DRIVER_NAME;
	priv->desc.pctlops	= &rza2_pinctrl_ops;
	priv->desc.pmxops	= &rza2_pinmux_ops;
	priv->desc.owner	= THIS_MODULE;

	ret = rza2_pinctrl_रेजिस्टर(priv);
	अगर (ret)
		वापस ret;

	dev_info(&pdev->dev, "Registered ports P0 - P%c\n",
		 port_names[priv->desc.npins / RZA2_PINS_PER_PORT - 1]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rza2_pinctrl_of_match[] = अणु
	अणु .compatible = "renesas,r7s9210-pinctrl", .data = (व्योम *)22, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver rza2_pinctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = rza2_pinctrl_of_match,
	पूर्ण,
	.probe = rza2_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init rza2_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rza2_pinctrl_driver);
पूर्ण
core_initcall(rza2_pinctrl_init);

MODULE_AUTHOR("Chris Brandt <chris.brandt@renesas.com>");
MODULE_DESCRIPTION("Pin and gpio controller driver for RZ/A2 SoC");
MODULE_LICENSE("GPL v2");
