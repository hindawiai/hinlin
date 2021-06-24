<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Microsemi/Microchip SoCs serial gpio driver
 *
 * Author: Lars Povlsen <lars.povlsen@microchip.com>
 *
 * Copyright (c) 2020 Microchip Technology Inc. and its subsidiaries.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#समावेश "core.h"
#समावेश "pinconf.h"

#घोषणा SGPIO_BITS_PER_WORD	32
#घोषणा SGPIO_MAX_BITS		4
#घोषणा SGPIO_SRC_BITS		3 /* 3 bit wide field per pin */

क्रमागत अणु
	REG_INPUT_DATA,
	REG_PORT_CONFIG,
	REG_PORT_ENABLE,
	REG_SIO_CONFIG,
	REG_SIO_CLOCK,
	REG_INT_POLARITY,
	REG_INT_TRIGGER,
	REG_INT_ACK,
	REG_INT_ENABLE,
	REG_INT_IDENT,
	MAXREG
पूर्ण;

क्रमागत अणु
	SGPIO_ARCH_LUTON,
	SGPIO_ARCH_OCELOT,
	SGPIO_ARCH_SPARX5,
पूर्ण;

क्रमागत अणु
	SGPIO_FLAGS_HAS_IRQ	= BIT(0),
पूर्ण;

काष्ठा sgpio_properties अणु
	पूर्णांक arch;
	पूर्णांक flags;
	u8 regoff[MAXREG];
पूर्ण;

#घोषणा SGPIO_LUTON_AUTO_REPEAT  BIT(5)
#घोषणा SGPIO_LUTON_PORT_WIDTH   GENMASK(3, 2)
#घोषणा SGPIO_LUTON_CLK_FREQ     GENMASK(11, 0)
#घोषणा SGPIO_LUTON_BIT_SOURCE   GENMASK(11, 0)

#घोषणा SGPIO_OCELOT_AUTO_REPEAT BIT(10)
#घोषणा SGPIO_OCELOT_PORT_WIDTH  GENMASK(8, 7)
#घोषणा SGPIO_OCELOT_CLK_FREQ    GENMASK(19, 8)
#घोषणा SGPIO_OCELOT_BIT_SOURCE  GENMASK(23, 12)

#घोषणा SGPIO_SPARX5_AUTO_REPEAT BIT(6)
#घोषणा SGPIO_SPARX5_PORT_WIDTH  GENMASK(4, 3)
#घोषणा SGPIO_SPARX5_CLK_FREQ    GENMASK(19, 8)
#घोषणा SGPIO_SPARX5_BIT_SOURCE  GENMASK(23, 12)

#घोषणा SGPIO_MASTER_INTR_ENA    BIT(0)

#घोषणा SGPIO_INT_TRG_LEVEL	0
#घोषणा SGPIO_INT_TRG_EDGE	1
#घोषणा SGPIO_INT_TRG_EDGE_FALL	2
#घोषणा SGPIO_INT_TRG_EDGE_RISE	3

#घोषणा SGPIO_TRG_LEVEL_HIGH	0
#घोषणा SGPIO_TRG_LEVEL_LOW	1

अटल स्थिर काष्ठा sgpio_properties properties_luton = अणु
	.arch   = SGPIO_ARCH_LUTON,
	.regoff = अणु 0x00, 0x09, 0x29, 0x2a, 0x2b पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sgpio_properties properties_ocelot = अणु
	.arch   = SGPIO_ARCH_OCELOT,
	.regoff = अणु 0x00, 0x06, 0x26, 0x04, 0x05 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sgpio_properties properties_sparx5 = अणु
	.arch   = SGPIO_ARCH_SPARX5,
	.flags  = SGPIO_FLAGS_HAS_IRQ,
	.regoff = अणु 0x00, 0x06, 0x26, 0x04, 0x05, 0x2a, 0x32, 0x3a, 0x3e, 0x42 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर functions[] = अणु "gpio" पूर्ण;

काष्ठा sgpio_bank अणु
	काष्ठा sgpio_priv *priv;
	bool is_input;
	काष्ठा gpio_chip gpio;
	काष्ठा pinctrl_desc pctl_desc;
पूर्ण;

काष्ठा sgpio_priv अणु
	काष्ठा device *dev;
	काष्ठा sgpio_bank in;
	काष्ठा sgpio_bank out;
	u32 bitcount;
	u32 ports;
	u32 घड़ी;
	u32 __iomem *regs;
	स्थिर काष्ठा sgpio_properties *properties;
पूर्ण;

काष्ठा sgpio_port_addr अणु
	u8 port;
	u8 bit;
पूर्ण;

अटल अंतरभूत व्योम sgpio_pin_to_addr(काष्ठा sgpio_priv *priv, पूर्णांक pin,
				     काष्ठा sgpio_port_addr *addr)
अणु
	addr->port = pin / priv->bitcount;
	addr->bit = pin % priv->bitcount;
पूर्ण

अटल अंतरभूत पूर्णांक sgpio_addr_to_pin(काष्ठा sgpio_priv *priv, पूर्णांक port, पूर्णांक bit)
अणु
	वापस bit + port * priv->bitcount;
पूर्ण

अटल अंतरभूत u32 sgpio_पढ़ोl(काष्ठा sgpio_priv *priv, u32 rno, u32 off)
अणु
	u32 __iomem *reg = &priv->regs[priv->properties->regoff[rno] + off];

	वापस पढ़ोl(reg);
पूर्ण

अटल अंतरभूत व्योम sgpio_ग_लिखोl(काष्ठा sgpio_priv *priv,
				u32 val, u32 rno, u32 off)
अणु
	u32 __iomem *reg = &priv->regs[priv->properties->regoff[rno] + off];

	ग_लिखोl(val, reg);
पूर्ण

अटल अंतरभूत व्योम sgpio_clrsetbits(काष्ठा sgpio_priv *priv,
				    u32 rno, u32 off, u32 clear, u32 set)
अणु
	u32 __iomem *reg = &priv->regs[priv->properties->regoff[rno] + off];
	u32 val = पढ़ोl(reg);

	val &= ~clear;
	val |= set;

	ग_लिखोl(val, reg);
पूर्ण

अटल अंतरभूत व्योम sgpio_configure_bitstream(काष्ठा sgpio_priv *priv)
अणु
	पूर्णांक width = priv->bitcount - 1;
	u32 clr, set;

	चयन (priv->properties->arch) अणु
	हाल SGPIO_ARCH_LUTON:
		clr = SGPIO_LUTON_PORT_WIDTH;
		set = SGPIO_LUTON_AUTO_REPEAT |
			FIELD_PREP(SGPIO_LUTON_PORT_WIDTH, width);
		अवरोध;
	हाल SGPIO_ARCH_OCELOT:
		clr = SGPIO_OCELOT_PORT_WIDTH;
		set = SGPIO_OCELOT_AUTO_REPEAT |
			FIELD_PREP(SGPIO_OCELOT_PORT_WIDTH, width);
		अवरोध;
	हाल SGPIO_ARCH_SPARX5:
		clr = SGPIO_SPARX5_PORT_WIDTH;
		set = SGPIO_SPARX5_AUTO_REPEAT |
			FIELD_PREP(SGPIO_SPARX5_PORT_WIDTH, width);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	sgpio_clrsetbits(priv, REG_SIO_CONFIG, 0, clr, set);
पूर्ण

अटल अंतरभूत व्योम sgpio_configure_घड़ी(काष्ठा sgpio_priv *priv, u32 clkfrq)
अणु
	u32 clr, set;

	चयन (priv->properties->arch) अणु
	हाल SGPIO_ARCH_LUTON:
		clr = SGPIO_LUTON_CLK_FREQ;
		set = FIELD_PREP(SGPIO_LUTON_CLK_FREQ, clkfrq);
		अवरोध;
	हाल SGPIO_ARCH_OCELOT:
		clr = SGPIO_OCELOT_CLK_FREQ;
		set = FIELD_PREP(SGPIO_OCELOT_CLK_FREQ, clkfrq);
		अवरोध;
	हाल SGPIO_ARCH_SPARX5:
		clr = SGPIO_SPARX5_CLK_FREQ;
		set = FIELD_PREP(SGPIO_SPARX5_CLK_FREQ, clkfrq);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	sgpio_clrsetbits(priv, REG_SIO_CLOCK, 0, clr, set);
पूर्ण

अटल व्योम sgpio_output_set(काष्ठा sgpio_priv *priv,
			     काष्ठा sgpio_port_addr *addr,
			     पूर्णांक value)
अणु
	अचिन्हित पूर्णांक bit = SGPIO_SRC_BITS * addr->bit;
	u32 clr, set;

	चयन (priv->properties->arch) अणु
	हाल SGPIO_ARCH_LUTON:
		clr = FIELD_PREP(SGPIO_LUTON_BIT_SOURCE, BIT(bit));
		set = FIELD_PREP(SGPIO_LUTON_BIT_SOURCE, value << bit);
		अवरोध;
	हाल SGPIO_ARCH_OCELOT:
		clr = FIELD_PREP(SGPIO_OCELOT_BIT_SOURCE, BIT(bit));
		set = FIELD_PREP(SGPIO_OCELOT_BIT_SOURCE, value << bit);
		अवरोध;
	हाल SGPIO_ARCH_SPARX5:
		clr = FIELD_PREP(SGPIO_SPARX5_BIT_SOURCE, BIT(bit));
		set = FIELD_PREP(SGPIO_SPARX5_BIT_SOURCE, value << bit);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	sgpio_clrsetbits(priv, REG_PORT_CONFIG, addr->port, clr, set);
पूर्ण

अटल पूर्णांक sgpio_output_get(काष्ठा sgpio_priv *priv,
			    काष्ठा sgpio_port_addr *addr)
अणु
	u32 val, portval = sgpio_पढ़ोl(priv, REG_PORT_CONFIG, addr->port);
	अचिन्हित पूर्णांक bit = SGPIO_SRC_BITS * addr->bit;

	चयन (priv->properties->arch) अणु
	हाल SGPIO_ARCH_LUTON:
		val = FIELD_GET(SGPIO_LUTON_BIT_SOURCE, portval);
		अवरोध;
	हाल SGPIO_ARCH_OCELOT:
		val = FIELD_GET(SGPIO_OCELOT_BIT_SOURCE, portval);
		अवरोध;
	हाल SGPIO_ARCH_SPARX5:
		val = FIELD_GET(SGPIO_SPARX5_BIT_SOURCE, portval);
		अवरोध;
	शेष:
		val = 0;
		अवरोध;
	पूर्ण
	वापस !!(val & BIT(bit));
पूर्ण

अटल पूर्णांक sgpio_input_get(काष्ठा sgpio_priv *priv,
			   काष्ठा sgpio_port_addr *addr)
अणु
	वापस !!(sgpio_पढ़ोl(priv, REG_INPUT_DATA, addr->bit) & BIT(addr->port));
पूर्ण

अटल पूर्णांक sgpio_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा sgpio_bank *bank = pinctrl_dev_get_drvdata(pctldev);
	u32 param = pinconf_to_config_param(*config);
	काष्ठा sgpio_priv *priv = bank->priv;
	काष्ठा sgpio_port_addr addr;
	पूर्णांक val;

	sgpio_pin_to_addr(priv, pin, &addr);

	चयन (param) अणु
	हाल PIN_CONFIG_INPUT_ENABLE:
		val = bank->is_input;
		अवरोध;

	हाल PIN_CONFIG_OUTPUT_ENABLE:
		val = !bank->is_input;
		अवरोध;

	हाल PIN_CONFIG_OUTPUT:
		अगर (bank->is_input)
			वापस -EINVAL;
		val = sgpio_output_get(priv, &addr);
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sgpio_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			     अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा sgpio_bank *bank = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sgpio_priv *priv = bank->priv;
	काष्ठा sgpio_port_addr addr;
	पूर्णांक cfg, err = 0;
	u32 param, arg;

	sgpio_pin_to_addr(priv, pin, &addr);

	क्रम (cfg = 0; cfg < num_configs; cfg++) अणु
		param = pinconf_to_config_param(configs[cfg]);
		arg = pinconf_to_config_argument(configs[cfg]);

		चयन (param) अणु
		हाल PIN_CONFIG_OUTPUT:
			अगर (bank->is_input)
				वापस -EINVAL;
			sgpio_output_set(priv, &addr, arg);
			अवरोध;

		शेष:
			err = -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops sgpio_confops = अणु
	.is_generic = true,
	.pin_config_get = sgpio_pinconf_get,
	.pin_config_set = sgpio_pinconf_set,
	.pin_config_config_dbg_show = pinconf_generic_dump_config,
पूर्ण;

अटल पूर्णांक sgpio_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 1;
पूर्ण

अटल स्थिर अक्षर *sgpio_get_function_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक function)
अणु
	वापस functions[0];
पूर्ण

अटल पूर्णांक sgpio_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक function,
				     स्थिर अक्षर *स्थिर **groups,
				     अचिन्हित *स्थिर num_groups)
अणु
	*groups  = functions;
	*num_groups = ARRAY_SIZE(functions);

	वापस 0;
पूर्ण

अटल पूर्णांक sgpio_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक selector, अचिन्हित पूर्णांक group)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sgpio_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_gpio_range *range,
				    अचिन्हित पूर्णांक pin, bool input)
अणु
	काष्ठा sgpio_bank *bank = pinctrl_dev_get_drvdata(pctldev);

	वापस (input == bank->is_input) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक sgpio_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sgpio_bank *bank = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sgpio_priv *priv = bank->priv;
	काष्ठा sgpio_port_addr addr;

	sgpio_pin_to_addr(priv, offset, &addr);

	अगर ((priv->ports & BIT(addr.port)) == 0) अणु
		dev_warn(priv->dev, "Request port %d.%d: Port is not enabled\n",
			 addr.port, addr.bit);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops sgpio_pmx_ops = अणु
	.get_functions_count = sgpio_get_functions_count,
	.get_function_name = sgpio_get_function_name,
	.get_function_groups = sgpio_get_function_groups,
	.set_mux = sgpio_pinmux_set_mux,
	.gpio_set_direction = sgpio_gpio_set_direction,
	.gpio_request_enable = sgpio_gpio_request_enable,
पूर्ण;

अटल पूर्णांक sgpio_pctl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा sgpio_bank *bank = pinctrl_dev_get_drvdata(pctldev);

	वापस bank->pctl_desc.npins;
पूर्ण

अटल स्थिर अक्षर *sgpio_pctl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित पूर्णांक group)
अणु
	काष्ठा sgpio_bank *bank = pinctrl_dev_get_drvdata(pctldev);

	वापस bank->pctl_desc.pins[group].name;
पूर्ण

अटल पूर्णांक sgpio_pctl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक group,
				     स्थिर अचिन्हित पूर्णांक **pins,
				     अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा sgpio_bank *bank = pinctrl_dev_get_drvdata(pctldev);

	*pins = &bank->pctl_desc.pins[group].number;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops sgpio_pctl_ops = अणु
	.get_groups_count = sgpio_pctl_get_groups_count,
	.get_group_name = sgpio_pctl_get_group_name,
	.get_group_pins = sgpio_pctl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक microchip_sgpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा sgpio_bank *bank = gpiochip_get_data(gc);

	/* Fixed-position function */
	वापस bank->is_input ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक microchip_sgpio_direction_output(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा sgpio_bank *bank = gpiochip_get_data(gc);
	काष्ठा sgpio_priv *priv = bank->priv;
	काष्ठा sgpio_port_addr addr;

	/* Fixed-position function */
	अगर (bank->is_input)
		वापस -EINVAL;

	sgpio_pin_to_addr(priv, gpio, &addr);

	sgpio_output_set(priv, &addr, value);

	वापस 0;
पूर्ण

अटल पूर्णांक microchip_sgpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा sgpio_bank *bank = gpiochip_get_data(gc);

	वापस bank->is_input ? GPIO_LINE_सूचीECTION_IN : GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल व्योम microchip_sgpio_set_value(काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	microchip_sgpio_direction_output(gc, gpio, value);
पूर्ण

अटल पूर्णांक microchip_sgpio_get_value(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा sgpio_bank *bank = gpiochip_get_data(gc);
	काष्ठा sgpio_priv *priv = bank->priv;
	काष्ठा sgpio_port_addr addr;

	sgpio_pin_to_addr(priv, gpio, &addr);

	वापस bank->is_input ? sgpio_input_get(priv, &addr) : sgpio_output_get(priv, &addr);
पूर्ण

अटल पूर्णांक microchip_sgpio_of_xlate(काष्ठा gpio_chip *gc,
			       स्थिर काष्ठा of_phandle_args *gpiospec,
			       u32 *flags)
अणु
	काष्ठा sgpio_bank *bank = gpiochip_get_data(gc);
	काष्ठा sgpio_priv *priv = bank->priv;
	पूर्णांक pin;

	/*
	 * Note that the SGIO pin is defined by *2* numbers, a port
	 * number between 0 and 31, and a bit index, 0 to 3.
	 */
	अगर (gpiospec->args[0] > SGPIO_BITS_PER_WORD ||
	    gpiospec->args[1] > priv->bitcount)
		वापस -EINVAL;

	pin = sgpio_addr_to_pin(priv, gpiospec->args[0], gpiospec->args[1]);

	अगर (pin > gc->ngpio)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpiospec->args[2];

	वापस pin;
पूर्ण

अटल पूर्णांक microchip_sgpio_get_ports(काष्ठा sgpio_priv *priv)
अणु
	स्थिर अक्षर *range_property_name = "microchip,sgpio-port-ranges";
	काष्ठा device *dev = priv->dev;
	u32 range_params[64];
	पूर्णांक i, nranges, ret;

	/* Calculate port mask */
	nranges = device_property_count_u32(dev, range_property_name);
	अगर (nranges < 2 || nranges % 2 || nranges > ARRAY_SIZE(range_params)) अणु
		dev_err(dev, "%s port range: '%s' property\n",
			nranges == -EINVAL ? "Missing" : "Invalid",
			range_property_name);
		वापस -EINVAL;
	पूर्ण

	ret = device_property_पढ़ो_u32_array(dev, range_property_name,
					     range_params, nranges);
	अगर (ret) अणु
		dev_err(dev, "failed to parse '%s' property: %d\n",
			range_property_name, ret);
		वापस ret;
	पूर्ण
	क्रम (i = 0; i < nranges; i += 2) अणु
		पूर्णांक start, end;

		start = range_params[i];
		end = range_params[i + 1];
		अगर (start > end || end >= SGPIO_BITS_PER_WORD) अणु
			dev_err(dev, "Ill-formed port-range [%d:%d]\n",
				start, end);
		पूर्ण
		priv->ports |= GENMASK(end, start);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम microchip_sgpio_irq_settype(काष्ठा irq_data *data,
					पूर्णांक type,
					पूर्णांक polarity)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sgpio_bank *bank = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(data);
	काष्ठा sgpio_port_addr addr;
	u32 ena;

	sgpio_pin_to_addr(bank->priv, gpio, &addr);

	/* Disable पूर्णांकerrupt जबतक changing type */
	ena = sgpio_पढ़ोl(bank->priv, REG_INT_ENABLE, addr.bit);
	sgpio_ग_लिखोl(bank->priv, ena & ~BIT(addr.port), REG_INT_ENABLE, addr.bit);

	/* Type value spपढ़ो over 2 रेजिस्टरs sets: low, high bit */
	sgpio_clrsetbits(bank->priv, REG_INT_TRIGGER, addr.bit,
			 BIT(addr.port), (!!(type & 0x1)) << addr.port);
	sgpio_clrsetbits(bank->priv, REG_INT_TRIGGER, SGPIO_MAX_BITS + addr.bit,
			 BIT(addr.port), (!!(type & 0x2)) << addr.port);

	अगर (type == SGPIO_INT_TRG_LEVEL)
		sgpio_clrsetbits(bank->priv, REG_INT_POLARITY, addr.bit,
				 BIT(addr.port), polarity << addr.port);

	/* Possibly re-enable पूर्णांकerrupts */
	sgpio_ग_लिखोl(bank->priv, ena, REG_INT_ENABLE, addr.bit);
पूर्ण

अटल व्योम microchip_sgpio_irq_setreg(काष्ठा irq_data *data,
				       पूर्णांक reg,
				       bool clear)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sgpio_bank *bank = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(data);
	काष्ठा sgpio_port_addr addr;

	sgpio_pin_to_addr(bank->priv, gpio, &addr);

	अगर (clear)
		sgpio_clrsetbits(bank->priv, reg, addr.bit, BIT(addr.port), 0);
	अन्यथा
		sgpio_clrsetbits(bank->priv, reg, addr.bit, 0, BIT(addr.port));
पूर्ण

अटल व्योम microchip_sgpio_irq_mask(काष्ठा irq_data *data)
अणु
	microchip_sgpio_irq_setreg(data, REG_INT_ENABLE, true);
पूर्ण

अटल व्योम microchip_sgpio_irq_unmask(काष्ठा irq_data *data)
अणु
	microchip_sgpio_irq_setreg(data, REG_INT_ENABLE, false);
पूर्ण

अटल व्योम microchip_sgpio_irq_ack(काष्ठा irq_data *data)
अणु
	microchip_sgpio_irq_setreg(data, REG_INT_ACK, false);
पूर्ण

अटल पूर्णांक microchip_sgpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	type &= IRQ_TYPE_SENSE_MASK;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		irq_set_handler_locked(data, handle_edge_irq);
		microchip_sgpio_irq_settype(data, SGPIO_INT_TRG_EDGE, 0);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		irq_set_handler_locked(data, handle_edge_irq);
		microchip_sgpio_irq_settype(data, SGPIO_INT_TRG_EDGE_RISE, 0);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_set_handler_locked(data, handle_edge_irq);
		microchip_sgpio_irq_settype(data, SGPIO_INT_TRG_EDGE_FALL, 0);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_set_handler_locked(data, handle_level_irq);
		microchip_sgpio_irq_settype(data, SGPIO_INT_TRG_LEVEL, SGPIO_TRG_LEVEL_HIGH);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_set_handler_locked(data, handle_level_irq);
		microchip_sgpio_irq_settype(data, SGPIO_INT_TRG_LEVEL, SGPIO_TRG_LEVEL_LOW);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_chip microchip_sgpio_irqchip = अणु
	.name		= "gpio",
	.irq_mask	= microchip_sgpio_irq_mask,
	.irq_ack	= microchip_sgpio_irq_ack,
	.irq_unmask	= microchip_sgpio_irq_unmask,
	.irq_set_type	= microchip_sgpio_irq_set_type,
पूर्ण;

अटल व्योम sgpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *parent_chip = irq_desc_get_chip(desc);
	काष्ठा gpio_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा sgpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा sgpio_priv *priv = bank->priv;
	पूर्णांक bit, port, gpio;
	दीर्घ val;

	क्रम (bit = 0; bit < priv->bitcount; bit++) अणु
		val = sgpio_पढ़ोl(priv, REG_INT_IDENT, bit);
		अगर (!val)
			जारी;

		chained_irq_enter(parent_chip, desc);

		क्रम_each_set_bit(port, &val, SGPIO_BITS_PER_WORD) अणु
			gpio = sgpio_addr_to_pin(priv, port, bit);
			generic_handle_irq(irq_linear_revmap(chip->irq.करोमुख्य, gpio));
		पूर्ण

		chained_irq_निकास(parent_chip, desc);
	पूर्ण
पूर्ण

अटल पूर्णांक microchip_sgpio_रेजिस्टर_bank(काष्ठा device *dev,
					 काष्ठा sgpio_priv *priv,
					 काष्ठा fwnode_handle *fwnode,
					 पूर्णांक bankno)
अणु
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा pinctrl_desc *pctl_desc;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा sgpio_bank *bank;
	काष्ठा gpio_chip *gc;
	u32 ngpios;
	पूर्णांक i, ret;

	/* Get overall bank काष्ठा */
	bank = (bankno == 0) ? &priv->in : &priv->out;
	bank->priv = priv;

	अगर (fwnode_property_पढ़ो_u32(fwnode, "ngpios", &ngpios)) अणु
		dev_info(dev, "failed to get number of gpios for bank%d\n",
			 bankno);
		ngpios = 64;
	पूर्ण

	priv->bitcount = ngpios / SGPIO_BITS_PER_WORD;
	अगर (priv->bitcount > SGPIO_MAX_BITS) अणु
		dev_err(dev, "Bit width exceeds maximum (%d)\n",
			SGPIO_MAX_BITS);
		वापस -EINVAL;
	पूर्ण

	pctl_desc = &bank->pctl_desc;
	pctl_desc->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s-%sput",
					 dev_name(dev),
					 bank->is_input ? "in" : "out");
	pctl_desc->pctlops = &sgpio_pctl_ops;
	pctl_desc->pmxops = &sgpio_pmx_ops;
	pctl_desc->confops = &sgpio_confops;
	pctl_desc->owner = THIS_MODULE;

	pins = devm_kzalloc(dev, माप(*pins)*ngpios, GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	pctl_desc->npins = ngpios;
	pctl_desc->pins = pins;

	क्रम (i = 0; i < ngpios; i++) अणु
		काष्ठा sgpio_port_addr addr;

		sgpio_pin_to_addr(priv, i, &addr);

		pins[i].number = i;
		pins[i].name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
					      "SGPIO_%c_p%db%d",
					      bank->is_input ? 'I' : 'O',
					      addr.port, addr.bit);
		अगर (!pins[i].name)
			वापस -ENOMEM;
	पूर्ण

	pctldev = devm_pinctrl_रेजिस्टर(dev, pctl_desc, bank);
	अगर (IS_ERR(pctldev))
		वापस dev_err_probe(dev, PTR_ERR(pctldev), "Failed to register pinctrl\n");

	gc			= &bank->gpio;
	gc->label		= pctl_desc->name;
	gc->parent		= dev;
	gc->of_node		= to_of_node(fwnode);
	gc->owner		= THIS_MODULE;
	gc->get_direction	= microchip_sgpio_get_direction;
	gc->direction_input	= microchip_sgpio_direction_input;
	gc->direction_output	= microchip_sgpio_direction_output;
	gc->get			= microchip_sgpio_get_value;
	gc->set			= microchip_sgpio_set_value;
	gc->request		= gpiochip_generic_request;
	gc->मुक्त		= gpiochip_generic_मुक्त;
	gc->of_xlate		= microchip_sgpio_of_xlate;
	gc->of_gpio_n_cells     = 3;
	gc->base		= -1;
	gc->ngpio		= ngpios;

	अगर (bank->is_input && priv->properties->flags & SGPIO_FLAGS_HAS_IRQ) अणु
		पूर्णांक irq = fwnode_irq_get(fwnode, 0);

		अगर (irq) अणु
			काष्ठा gpio_irq_chip *girq = &gc->irq;

			girq->chip = devm_kmemdup(dev, &microchip_sgpio_irqchip,
						  माप(microchip_sgpio_irqchip),
						  GFP_KERNEL);
			अगर (!girq->chip)
				वापस -ENOMEM;
			girq->parent_handler = sgpio_irq_handler;
			girq->num_parents = 1;
			girq->parents = devm_kसुस्मृति(dev, 1,
						     माप(*girq->parents),
						     GFP_KERNEL);
			अगर (!girq->parents)
				वापस -ENOMEM;
			girq->parents[0] = irq;
			girq->शेष_type = IRQ_TYPE_NONE;
			girq->handler = handle_bad_irq;

			/* Disable all inभागidual pins */
			क्रम (i = 0; i < SGPIO_MAX_BITS; i++)
				sgpio_ग_लिखोl(priv, 0, REG_INT_ENABLE, i);
			/* Master enable */
			sgpio_clrsetbits(priv, REG_SIO_CONFIG, 0, 0, SGPIO_MASTER_INTR_ENA);
		पूर्ण
	पूर्ण

	ret = devm_gpiochip_add_data(dev, gc, bank);
	अगर (ret)
		dev_err(dev, "Failed to register: ret %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक microchip_sgpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक भाग_घड़ी = 0, ret, port, i, nbanks;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा sgpio_priv *priv;
	काष्ठा clk *clk;
	u32 val;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(dev, PTR_ERR(clk), "Failed to get clock\n");

	भाग_घड़ी = clk_get_rate(clk);
	अगर (device_property_पढ़ो_u32(dev, "bus-frequency", &priv->घड़ी))
		priv->घड़ी = 12500000;
	अगर (priv->घड़ी == 0 || priv->घड़ी > (भाग_घड़ी / 2)) अणु
		dev_err(dev, "Invalid frequency %d\n", priv->घड़ी);
		वापस -EINVAL;
	पूर्ण

	priv->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->regs))
		वापस PTR_ERR(priv->regs);
	priv->properties = device_get_match_data(dev);
	priv->in.is_input = true;

	/* Get rest of device properties */
	ret = microchip_sgpio_get_ports(priv);
	अगर (ret)
		वापस ret;

	nbanks = device_get_child_node_count(dev);
	अगर (nbanks != 2) अणु
		dev_err(dev, "Must have 2 banks (have %d)\n", nbanks);
		वापस -EINVAL;
	पूर्ण

	i = 0;
	device_क्रम_each_child_node(dev, fwnode) अणु
		ret = microchip_sgpio_रेजिस्टर_bank(dev, priv, fwnode, i++);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (priv->in.gpio.ngpio != priv->out.gpio.ngpio) अणु
		dev_err(dev, "Banks must have same GPIO count\n");
		वापस -दुस्फल;
	पूर्ण

	sgpio_configure_bitstream(priv);

	val = max(2U, भाग_घड़ी / priv->घड़ी);
	sgpio_configure_घड़ी(priv, val);

	क्रम (port = 0; port < SGPIO_BITS_PER_WORD; port++)
		sgpio_ग_लिखोl(priv, 0, REG_PORT_CONFIG, port);
	sgpio_ग_लिखोl(priv, priv->ports, REG_PORT_ENABLE, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id microchip_sgpio_gpio_of_match[] = अणु
	अणु
		.compatible = "microchip,sparx5-sgpio",
		.data = &properties_sparx5,
	पूर्ण, अणु
		.compatible = "mscc,luton-sgpio",
		.data = &properties_luton,
	पूर्ण, अणु
		.compatible = "mscc,ocelot-sgpio",
		.data = &properties_ocelot,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver microchip_sgpio_pinctrl_driver = अणु
	.driver = अणु
		.name = "pinctrl-microchip-sgpio",
		.of_match_table = microchip_sgpio_gpio_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = microchip_sgpio_probe,
पूर्ण;
builtin_platक्रमm_driver(microchip_sgpio_pinctrl_driver);
