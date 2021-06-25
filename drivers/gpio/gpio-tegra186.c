<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016-2017 NVIDIA Corporation
 *
 * Author: Thierry Reding <treding@nvidia.com>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/gpio/tegra186-gpपन.स>
#समावेश <dt-bindings/gpio/tegra194-gpपन.स>

/* security रेजिस्टरs */
#घोषणा TEGRA186_GPIO_CTL_SCR 0x0c
#घोषणा  TEGRA186_GPIO_CTL_SCR_SEC_WEN BIT(28)
#घोषणा  TEGRA186_GPIO_CTL_SCR_SEC_REN BIT(27)

#घोषणा TEGRA186_GPIO_INT_ROUTE_MAPPING(p, x) (0x14 + (p) * 0x20 + (x) * 4)

/* control रेजिस्टरs */
#घोषणा TEGRA186_GPIO_ENABLE_CONFIG 0x00
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_ENABLE BIT(0)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_OUT BIT(1)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_NONE (0x0 << 2)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_LEVEL (0x1 << 2)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_SINGLE_EDGE (0x2 << 2)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_DOUBLE_EDGE (0x3 << 2)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_MASK (0x3 << 2)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_LEVEL BIT(4)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_DEBOUNCE BIT(5)
#घोषणा  TEGRA186_GPIO_ENABLE_CONFIG_INTERRUPT BIT(6)

#घोषणा TEGRA186_GPIO_DEBOUNCE_CONTROL 0x04
#घोषणा  TEGRA186_GPIO_DEBOUNCE_CONTROL_THRESHOLD(x) ((x) & 0xff)

#घोषणा TEGRA186_GPIO_INPUT 0x08
#घोषणा  TEGRA186_GPIO_INPUT_HIGH BIT(0)

#घोषणा TEGRA186_GPIO_OUTPUT_CONTROL 0x0c
#घोषणा  TEGRA186_GPIO_OUTPUT_CONTROL_FLOATED BIT(0)

#घोषणा TEGRA186_GPIO_OUTPUT_VALUE 0x10
#घोषणा  TEGRA186_GPIO_OUTPUT_VALUE_HIGH BIT(0)

#घोषणा TEGRA186_GPIO_INTERRUPT_CLEAR 0x14

#घोषणा TEGRA186_GPIO_INTERRUPT_STATUS(x) (0x100 + (x) * 4)

काष्ठा tegra_gpio_port अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक bank;
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक pins;
पूर्ण;

काष्ठा tegra186_pin_range अणु
	अचिन्हित पूर्णांक offset;
	स्थिर अक्षर *group;
पूर्ण;

काष्ठा tegra_gpio_soc अणु
	स्थिर काष्ठा tegra_gpio_port *ports;
	अचिन्हित पूर्णांक num_ports;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक instance;

	स्थिर काष्ठा tegra186_pin_range *pin_ranges;
	अचिन्हित पूर्णांक num_pin_ranges;
	स्थिर अक्षर *pinmux;
पूर्ण;

काष्ठा tegra_gpio अणु
	काष्ठा gpio_chip gpio;
	काष्ठा irq_chip पूर्णांकc;
	अचिन्हित पूर्णांक num_irq;
	अचिन्हित पूर्णांक *irq;

	स्थिर काष्ठा tegra_gpio_soc *soc;

	व्योम __iomem *secure;
	व्योम __iomem *base;
पूर्ण;

अटल स्थिर काष्ठा tegra_gpio_port *
tegra186_gpio_get_port(काष्ठा tegra_gpio *gpio, अचिन्हित पूर्णांक *pin)
अणु
	अचिन्हित पूर्णांक start = 0, i;

	क्रम (i = 0; i < gpio->soc->num_ports; i++) अणु
		स्थिर काष्ठा tegra_gpio_port *port = &gpio->soc->ports[i];

		अगर (*pin >= start && *pin < start + port->pins) अणु
			*pin -= start;
			वापस port;
		पूर्ण

		start += port->pins;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __iomem *tegra186_gpio_get_base(काष्ठा tegra_gpio *gpio,
					    अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा tegra_gpio_port *port;
	अचिन्हित पूर्णांक offset;

	port = tegra186_gpio_get_port(gpio, &pin);
	अगर (!port)
		वापस शून्य;

	offset = port->bank * 0x1000 + port->port * 0x200;

	वापस gpio->base + offset + pin * 0x20;
पूर्ण

अटल पूर्णांक tegra186_gpio_get_direction(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	व्योम __iomem *base;
	u32 value;

	base = tegra186_gpio_get_base(gpio, offset);
	अगर (WARN_ON(base == शून्य))
		वापस -ENODEV;

	value = पढ़ोl(base + TEGRA186_GPIO_ENABLE_CONFIG);
	अगर (value & TEGRA186_GPIO_ENABLE_CONFIG_OUT)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक tegra186_gpio_direction_input(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	व्योम __iomem *base;
	u32 value;

	base = tegra186_gpio_get_base(gpio, offset);
	अगर (WARN_ON(base == शून्य))
		वापस -ENODEV;

	value = पढ़ोl(base + TEGRA186_GPIO_OUTPUT_CONTROL);
	value |= TEGRA186_GPIO_OUTPUT_CONTROL_FLOATED;
	ग_लिखोl(value, base + TEGRA186_GPIO_OUTPUT_CONTROL);

	value = पढ़ोl(base + TEGRA186_GPIO_ENABLE_CONFIG);
	value |= TEGRA186_GPIO_ENABLE_CONFIG_ENABLE;
	value &= ~TEGRA186_GPIO_ENABLE_CONFIG_OUT;
	ग_लिखोl(value, base + TEGRA186_GPIO_ENABLE_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_gpio_direction_output(काष्ठा gpio_chip *chip,
					  अचिन्हित पूर्णांक offset, पूर्णांक level)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	व्योम __iomem *base;
	u32 value;

	/* configure output level first */
	chip->set(chip, offset, level);

	base = tegra186_gpio_get_base(gpio, offset);
	अगर (WARN_ON(base == शून्य))
		वापस -EINVAL;

	/* set the direction */
	value = पढ़ोl(base + TEGRA186_GPIO_OUTPUT_CONTROL);
	value &= ~TEGRA186_GPIO_OUTPUT_CONTROL_FLOATED;
	ग_लिखोl(value, base + TEGRA186_GPIO_OUTPUT_CONTROL);

	value = पढ़ोl(base + TEGRA186_GPIO_ENABLE_CONFIG);
	value |= TEGRA186_GPIO_ENABLE_CONFIG_ENABLE;
	value |= TEGRA186_GPIO_ENABLE_CONFIG_OUT;
	ग_लिखोl(value, base + TEGRA186_GPIO_ENABLE_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	व्योम __iomem *base;
	u32 value;

	base = tegra186_gpio_get_base(gpio, offset);
	अगर (WARN_ON(base == शून्य))
		वापस -ENODEV;

	value = पढ़ोl(base + TEGRA186_GPIO_ENABLE_CONFIG);
	अगर (value & TEGRA186_GPIO_ENABLE_CONFIG_OUT)
		value = पढ़ोl(base + TEGRA186_GPIO_OUTPUT_VALUE);
	अन्यथा
		value = पढ़ोl(base + TEGRA186_GPIO_INPUT);

	वापस value & BIT(0);
पूर्ण

अटल व्योम tegra186_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			      पूर्णांक level)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	व्योम __iomem *base;
	u32 value;

	base = tegra186_gpio_get_base(gpio, offset);
	अगर (WARN_ON(base == शून्य))
		वापस;

	value = पढ़ोl(base + TEGRA186_GPIO_OUTPUT_VALUE);
	अगर (level == 0)
		value &= ~TEGRA186_GPIO_OUTPUT_VALUE_HIGH;
	अन्यथा
		value |= TEGRA186_GPIO_OUTPUT_VALUE_HIGH;

	ग_लिखोl(value, base + TEGRA186_GPIO_OUTPUT_VALUE);
पूर्ण

अटल पूर्णांक tegra186_gpio_set_config(काष्ठा gpio_chip *chip,
				    अचिन्हित पूर्णांक offset,
				    अचिन्हित दीर्घ config)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	u32 debounce, value;
	व्योम __iomem *base;

	base = tegra186_gpio_get_base(gpio, offset);
	अगर (base == शून्य)
		वापस -ENXIO;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);

	/*
	 * The Tegra186 GPIO controller supports a maximum of 255 ms debounce
	 * समय.
	 */
	अगर (debounce > 255000)
		वापस -EINVAL;

	debounce = DIV_ROUND_UP(debounce, USEC_PER_MSEC);

	value = TEGRA186_GPIO_DEBOUNCE_CONTROL_THRESHOLD(debounce);
	ग_लिखोl(value, base + TEGRA186_GPIO_DEBOUNCE_CONTROL);

	value = पढ़ोl(base + TEGRA186_GPIO_ENABLE_CONFIG);
	value |= TEGRA186_GPIO_ENABLE_CONFIG_DEBOUNCE;
	ग_लिखोl(value, base + TEGRA186_GPIO_ENABLE_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_gpio_add_pin_ranges(काष्ठा gpio_chip *chip)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक err;

	अगर (!gpio->soc->pinmux || gpio->soc->num_pin_ranges == 0)
		वापस 0;

	np = of_find_compatible_node(शून्य, शून्य, gpio->soc->pinmux);
	अगर (!np)
		वापस -ENODEV;

	pctldev = of_pinctrl_get(np);
	of_node_put(np);
	अगर (!pctldev)
		वापस -EPROBE_DEFER;

	क्रम (i = 0; i < gpio->soc->num_pin_ranges; i++) अणु
		अचिन्हित पूर्णांक pin = gpio->soc->pin_ranges[i].offset, port;
		स्थिर अक्षर *group = gpio->soc->pin_ranges[i].group;

		port = pin / 8;
		pin = pin % 8;

		अगर (port >= gpio->soc->num_ports) अणु
			dev_warn(chip->parent, "invalid port %u for %s\n",
				 port, group);
			जारी;
		पूर्ण

		क्रम (j = 0; j < port; j++)
			pin += gpio->soc->ports[j].pins;

		err = gpiochip_add_pingroup_range(chip, pctldev, pin, group);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_gpio_of_xlate(काष्ठा gpio_chip *chip,
				  स्थिर काष्ठा of_phandle_args *spec,
				  u32 *flags)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक port, pin, i, offset = 0;

	अगर (WARN_ON(chip->of_gpio_n_cells < 2))
		वापस -EINVAL;

	अगर (WARN_ON(spec->args_count < chip->of_gpio_n_cells))
		वापस -EINVAL;

	port = spec->args[0] / 8;
	pin = spec->args[0] % 8;

	अगर (port >= gpio->soc->num_ports) अणु
		dev_err(chip->parent, "invalid port number: %u\n", port);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < port; i++)
		offset += gpio->soc->ports[i].pins;

	अगर (flags)
		*flags = spec->args[1];

	वापस offset + pin;
पूर्ण

अटल व्योम tegra186_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा tegra_gpio *gpio = irq_data_get_irq_chip_data(data);
	व्योम __iomem *base;

	base = tegra186_gpio_get_base(gpio, data->hwirq);
	अगर (WARN_ON(base == शून्य))
		वापस;

	ग_लिखोl(1, base + TEGRA186_GPIO_INTERRUPT_CLEAR);
पूर्ण

अटल व्योम tegra186_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा tegra_gpio *gpio = irq_data_get_irq_chip_data(data);
	व्योम __iomem *base;
	u32 value;

	base = tegra186_gpio_get_base(gpio, data->hwirq);
	अगर (WARN_ON(base == शून्य))
		वापस;

	value = पढ़ोl(base + TEGRA186_GPIO_ENABLE_CONFIG);
	value &= ~TEGRA186_GPIO_ENABLE_CONFIG_INTERRUPT;
	ग_लिखोl(value, base + TEGRA186_GPIO_ENABLE_CONFIG);
पूर्ण

अटल व्योम tegra186_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा tegra_gpio *gpio = irq_data_get_irq_chip_data(data);
	व्योम __iomem *base;
	u32 value;

	base = tegra186_gpio_get_base(gpio, data->hwirq);
	अगर (WARN_ON(base == शून्य))
		वापस;

	value = पढ़ोl(base + TEGRA186_GPIO_ENABLE_CONFIG);
	value |= TEGRA186_GPIO_ENABLE_CONFIG_INTERRUPT;
	ग_लिखोl(value, base + TEGRA186_GPIO_ENABLE_CONFIG);
पूर्ण

अटल पूर्णांक tegra186_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा tegra_gpio *gpio = irq_data_get_irq_chip_data(data);
	व्योम __iomem *base;
	u32 value;

	base = tegra186_gpio_get_base(gpio, data->hwirq);
	अगर (WARN_ON(base == शून्य))
		वापस -ENODEV;

	value = पढ़ोl(base + TEGRA186_GPIO_ENABLE_CONFIG);
	value &= ~TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_MASK;
	value &= ~TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_LEVEL;

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_NONE:
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING:
		value |= TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_SINGLE_EDGE;
		value |= TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_LEVEL;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		value |= TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_SINGLE_EDGE;
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		value |= TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_DOUBLE_EDGE;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		value |= TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_LEVEL;
		value |= TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_LEVEL;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		value |= TEGRA186_GPIO_ENABLE_CONFIG_TRIGGER_TYPE_LEVEL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(value, base + TEGRA186_GPIO_ENABLE_CONFIG);

	अगर ((type & IRQ_TYPE_EDGE_BOTH) == 0)
		irq_set_handler_locked(data, handle_level_irq);
	अन्यथा
		irq_set_handler_locked(data, handle_edge_irq);

	अगर (data->parent_data)
		वापस irq_chip_set_type_parent(data, type);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	अगर (data->parent_data)
		वापस irq_chip_set_wake_parent(data, on);

	वापस 0;
पूर्ण

अटल व्योम tegra186_gpio_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा tegra_gpio *gpio = irq_desc_get_handler_data(desc);
	काष्ठा irq_करोमुख्य *करोमुख्य = gpio->gpio.irq.करोमुख्य;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक parent = irq_desc_get_irq(desc);
	अचिन्हित पूर्णांक i, offset = 0;

	chained_irq_enter(chip, desc);

	क्रम (i = 0; i < gpio->soc->num_ports; i++) अणु
		स्थिर काष्ठा tegra_gpio_port *port = &gpio->soc->ports[i];
		अचिन्हित पूर्णांक pin, irq;
		अचिन्हित दीर्घ value;
		व्योम __iomem *base;

		base = gpio->base + port->bank * 0x1000 + port->port * 0x200;

		/* skip ports that are not associated with this bank */
		अगर (parent != gpio->irq[port->bank])
			जाओ skip;

		value = पढ़ोl(base + TEGRA186_GPIO_INTERRUPT_STATUS(1));

		क्रम_each_set_bit(pin, &value, port->pins) अणु
			irq = irq_find_mapping(करोमुख्य, offset + pin);
			अगर (WARN_ON(irq == 0))
				जारी;

			generic_handle_irq(irq);
		पूर्ण

skip:
		offset += port->pins;
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक tegra186_gpio_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
					      काष्ठा irq_fwspec *fwspec,
					      अचिन्हित दीर्घ *hwirq,
					      अचिन्हित पूर्णांक *type)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(करोमुख्य->host_data);
	अचिन्हित पूर्णांक port, pin, i, offset = 0;

	अगर (WARN_ON(gpio->gpio.of_gpio_n_cells < 2))
		वापस -EINVAL;

	अगर (WARN_ON(fwspec->param_count < gpio->gpio.of_gpio_n_cells))
		वापस -EINVAL;

	port = fwspec->param[0] / 8;
	pin = fwspec->param[0] % 8;

	अगर (port >= gpio->soc->num_ports)
		वापस -EINVAL;

	क्रम (i = 0; i < port; i++)
		offset += gpio->soc->ports[i].pins;

	*type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;
	*hwirq = offset + pin;

	वापस 0;
पूर्ण

अटल व्योम *tegra186_gpio_populate_parent_fwspec(काष्ठा gpio_chip *chip,
						 अचिन्हित पूर्णांक parent_hwirq,
						 अचिन्हित पूर्णांक parent_type)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा irq_fwspec *fwspec;

	fwspec = kदो_स्मृति(माप(*fwspec), GFP_KERNEL);
	अगर (!fwspec)
		वापस शून्य;

	fwspec->fwnode = chip->irq.parent_करोमुख्य->fwnode;
	fwspec->param_count = 3;
	fwspec->param[0] = gpio->soc->instance;
	fwspec->param[1] = parent_hwirq;
	fwspec->param[2] = parent_type;

	वापस fwspec;
पूर्ण

अटल पूर्णांक tegra186_gpio_child_to_parent_hwirq(काष्ठा gpio_chip *chip,
					       अचिन्हित पूर्णांक hwirq,
					       अचिन्हित पूर्णांक type,
					       अचिन्हित पूर्णांक *parent_hwirq,
					       अचिन्हित पूर्णांक *parent_type)
अणु
	*parent_hwirq = chip->irq.child_offset_to_irq(chip, hwirq);
	*parent_type = type;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक tegra186_gpio_child_offset_to_irq(काष्ठा gpio_chip *chip,
						      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_gpio *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < gpio->soc->num_ports; i++) अणु
		अगर (offset < gpio->soc->ports[i].pins)
			अवरोध;

		offset -= gpio->soc->ports[i].pins;
	पूर्ण

	वापस offset + i * 8;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra186_pmc_of_match[] = अणु
	अणु .compatible = "nvidia,tegra186-pmc" पूर्ण,
	अणु .compatible = "nvidia,tegra194-pmc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम tegra186_gpio_init_route_mapping(काष्ठा tegra_gpio *gpio)
अणु
	अचिन्हित पूर्णांक i, j;
	u32 value;

	क्रम (i = 0; i < gpio->soc->num_ports; i++) अणु
		स्थिर काष्ठा tegra_gpio_port *port = &gpio->soc->ports[i];
		अचिन्हित पूर्णांक offset, p = port->port;
		व्योम __iomem *base;

		base = gpio->secure + port->bank * 0x1000 + 0x800;

		value = पढ़ोl(base + TEGRA186_GPIO_CTL_SCR);

		/*
		 * For controllers that haven't been locked करोwn yet, make
		 * sure to program the शेष पूर्णांकerrupt route mapping.
		 */
		अगर ((value & TEGRA186_GPIO_CTL_SCR_SEC_REN) == 0 &&
		    (value & TEGRA186_GPIO_CTL_SCR_SEC_WEN) == 0) अणु
			क्रम (j = 0; j < 8; j++) अणु
				offset = TEGRA186_GPIO_INT_ROUTE_MAPPING(p, j);

				value = पढ़ोl(base + offset);
				value = BIT(port->pins) - 1;
				ग_लिखोl(value, base + offset);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tegra186_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक i, j, offset;
	काष्ठा gpio_irq_chip *irq;
	काष्ठा tegra_gpio *gpio;
	काष्ठा device_node *np;
	अक्षर **names;
	पूर्णांक err;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->soc = of_device_get_match_data(&pdev->dev);

	gpio->secure = devm_platक्रमm_ioremap_resource_byname(pdev, "security");
	अगर (IS_ERR(gpio->secure))
		वापस PTR_ERR(gpio->secure);

	gpio->base = devm_platक्रमm_ioremap_resource_byname(pdev, "gpio");
	अगर (IS_ERR(gpio->base))
		वापस PTR_ERR(gpio->base);

	err = platक्रमm_irq_count(pdev);
	अगर (err < 0)
		वापस err;

	gpio->num_irq = err;

	gpio->irq = devm_kसुस्मृति(&pdev->dev, gpio->num_irq, माप(*gpio->irq),
				 GFP_KERNEL);
	अगर (!gpio->irq)
		वापस -ENOMEM;

	क्रम (i = 0; i < gpio->num_irq; i++) अणु
		err = platक्रमm_get_irq(pdev, i);
		अगर (err < 0)
			वापस err;

		gpio->irq[i] = err;
	पूर्ण

	gpio->gpio.label = gpio->soc->name;
	gpio->gpio.parent = &pdev->dev;

	gpio->gpio.request = gpiochip_generic_request;
	gpio->gpio.मुक्त = gpiochip_generic_मुक्त;
	gpio->gpio.get_direction = tegra186_gpio_get_direction;
	gpio->gpio.direction_input = tegra186_gpio_direction_input;
	gpio->gpio.direction_output = tegra186_gpio_direction_output;
	gpio->gpio.get = tegra186_gpio_get;
	gpio->gpio.set = tegra186_gpio_set;
	gpio->gpio.set_config = tegra186_gpio_set_config;
	gpio->gpio.add_pin_ranges = tegra186_gpio_add_pin_ranges;

	gpio->gpio.base = -1;

	क्रम (i = 0; i < gpio->soc->num_ports; i++)
		gpio->gpio.ngpio += gpio->soc->ports[i].pins;

	names = devm_kसुस्मृति(gpio->gpio.parent, gpio->gpio.ngpio,
			     माप(*names), GFP_KERNEL);
	अगर (!names)
		वापस -ENOMEM;

	क्रम (i = 0, offset = 0; i < gpio->soc->num_ports; i++) अणु
		स्थिर काष्ठा tegra_gpio_port *port = &gpio->soc->ports[i];
		अक्षर *name;

		क्रम (j = 0; j < port->pins; j++) अणु
			name = devm_kaप्र_लिखो(gpio->gpio.parent, GFP_KERNEL,
					      "P%s.%02x", port->name, j);
			अगर (!name)
				वापस -ENOMEM;

			names[offset + j] = name;
		पूर्ण

		offset += port->pins;
	पूर्ण

	gpio->gpio.names = (स्थिर अक्षर * स्थिर *)names;

	gpio->gpio.of_node = pdev->dev.of_node;
	gpio->gpio.of_gpio_n_cells = 2;
	gpio->gpio.of_xlate = tegra186_gpio_of_xlate;

	gpio->पूर्णांकc.name = pdev->dev.of_node->name;
	gpio->पूर्णांकc.irq_ack = tegra186_irq_ack;
	gpio->पूर्णांकc.irq_mask = tegra186_irq_mask;
	gpio->पूर्णांकc.irq_unmask = tegra186_irq_unmask;
	gpio->पूर्णांकc.irq_set_type = tegra186_irq_set_type;
	gpio->पूर्णांकc.irq_set_wake = tegra186_irq_set_wake;

	irq = &gpio->gpio.irq;
	irq->chip = &gpio->पूर्णांकc;
	irq->fwnode = of_node_to_fwnode(pdev->dev.of_node);
	irq->child_to_parent_hwirq = tegra186_gpio_child_to_parent_hwirq;
	irq->populate_parent_alloc_arg = tegra186_gpio_populate_parent_fwspec;
	irq->child_offset_to_irq = tegra186_gpio_child_offset_to_irq;
	irq->child_irq_करोमुख्य_ops.translate = tegra186_gpio_irq_करोमुख्य_translate;
	irq->handler = handle_simple_irq;
	irq->शेष_type = IRQ_TYPE_NONE;
	irq->parent_handler = tegra186_gpio_irq;
	irq->parent_handler_data = gpio;
	irq->num_parents = gpio->num_irq;
	irq->parents = gpio->irq;

	np = of_find_matching_node(शून्य, tegra186_pmc_of_match);
	अगर (np) अणु
		irq->parent_करोमुख्य = irq_find_host(np);
		of_node_put(np);

		अगर (!irq->parent_करोमुख्य)
			वापस -EPROBE_DEFER;
	पूर्ण

	tegra186_gpio_init_route_mapping(gpio);

	irq->map = devm_kसुस्मृति(&pdev->dev, gpio->gpio.ngpio,
				माप(*irq->map), GFP_KERNEL);
	अगर (!irq->map)
		वापस -ENOMEM;

	क्रम (i = 0, offset = 0; i < gpio->soc->num_ports; i++) अणु
		स्थिर काष्ठा tegra_gpio_port *port = &gpio->soc->ports[i];

		क्रम (j = 0; j < port->pins; j++)
			irq->map[offset + j] = irq->parents[port->bank];

		offset += port->pins;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gpio);

	err = devm_gpiochip_add_data(&pdev->dev, &gpio->gpio, gpio);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

#घोषणा TEGRA186_MAIN_GPIO_PORT(_name, _bank, _port, _pins)	\
	[TEGRA186_MAIN_GPIO_PORT_##_name] = अणु			\
		.name = #_name,					\
		.bank = _bank,					\
		.port = _port,					\
		.pins = _pins,					\
	पूर्ण

अटल स्थिर काष्ठा tegra_gpio_port tegra186_मुख्य_ports[] = अणु
	TEGRA186_MAIN_GPIO_PORT( A, 2, 0, 7),
	TEGRA186_MAIN_GPIO_PORT( B, 3, 0, 7),
	TEGRA186_MAIN_GPIO_PORT( C, 3, 1, 7),
	TEGRA186_MAIN_GPIO_PORT( D, 3, 2, 6),
	TEGRA186_MAIN_GPIO_PORT( E, 2, 1, 8),
	TEGRA186_MAIN_GPIO_PORT( F, 2, 2, 6),
	TEGRA186_MAIN_GPIO_PORT( G, 4, 1, 6),
	TEGRA186_MAIN_GPIO_PORT( H, 1, 0, 7),
	TEGRA186_MAIN_GPIO_PORT( I, 0, 4, 8),
	TEGRA186_MAIN_GPIO_PORT( J, 5, 0, 8),
	TEGRA186_MAIN_GPIO_PORT( K, 5, 1, 1),
	TEGRA186_MAIN_GPIO_PORT( L, 1, 1, 8),
	TEGRA186_MAIN_GPIO_PORT( M, 5, 3, 6),
	TEGRA186_MAIN_GPIO_PORT( N, 0, 0, 7),
	TEGRA186_MAIN_GPIO_PORT( O, 0, 1, 4),
	TEGRA186_MAIN_GPIO_PORT( P, 4, 0, 7),
	TEGRA186_MAIN_GPIO_PORT( Q, 0, 2, 6),
	TEGRA186_MAIN_GPIO_PORT( R, 0, 5, 6),
	TEGRA186_MAIN_GPIO_PORT( T, 0, 3, 4),
	TEGRA186_MAIN_GPIO_PORT( X, 1, 2, 8),
	TEGRA186_MAIN_GPIO_PORT( Y, 1, 3, 7),
	TEGRA186_MAIN_GPIO_PORT(BB, 2, 3, 2),
	TEGRA186_MAIN_GPIO_PORT(CC, 5, 2, 4),
पूर्ण;

अटल स्थिर काष्ठा tegra_gpio_soc tegra186_मुख्य_soc = अणु
	.num_ports = ARRAY_SIZE(tegra186_मुख्य_ports),
	.ports = tegra186_मुख्य_ports,
	.name = "tegra186-gpio",
	.instance = 0,
पूर्ण;

#घोषणा TEGRA186_AON_GPIO_PORT(_name, _bank, _port, _pins)	\
	[TEGRA186_AON_GPIO_PORT_##_name] = अणु			\
		.name = #_name,					\
		.bank = _bank,					\
		.port = _port,					\
		.pins = _pins,					\
	पूर्ण

अटल स्थिर काष्ठा tegra_gpio_port tegra186_aon_ports[] = अणु
	TEGRA186_AON_GPIO_PORT( S, 0, 1, 5),
	TEGRA186_AON_GPIO_PORT( U, 0, 2, 6),
	TEGRA186_AON_GPIO_PORT( V, 0, 4, 8),
	TEGRA186_AON_GPIO_PORT( W, 0, 5, 8),
	TEGRA186_AON_GPIO_PORT( Z, 0, 7, 4),
	TEGRA186_AON_GPIO_PORT(AA, 0, 6, 8),
	TEGRA186_AON_GPIO_PORT(EE, 0, 3, 3),
	TEGRA186_AON_GPIO_PORT(FF, 0, 0, 5),
पूर्ण;

अटल स्थिर काष्ठा tegra_gpio_soc tegra186_aon_soc = अणु
	.num_ports = ARRAY_SIZE(tegra186_aon_ports),
	.ports = tegra186_aon_ports,
	.name = "tegra186-gpio-aon",
	.instance = 1,
पूर्ण;

#घोषणा TEGRA194_MAIN_GPIO_PORT(_name, _bank, _port, _pins)	\
	[TEGRA194_MAIN_GPIO_PORT_##_name] = अणु			\
		.name = #_name,					\
		.bank = _bank,					\
		.port = _port,					\
		.pins = _pins,					\
	पूर्ण

अटल स्थिर काष्ठा tegra_gpio_port tegra194_मुख्य_ports[] = अणु
	TEGRA194_MAIN_GPIO_PORT( A, 1, 2, 8),
	TEGRA194_MAIN_GPIO_PORT( B, 4, 7, 2),
	TEGRA194_MAIN_GPIO_PORT( C, 4, 3, 8),
	TEGRA194_MAIN_GPIO_PORT( D, 4, 4, 4),
	TEGRA194_MAIN_GPIO_PORT( E, 4, 5, 8),
	TEGRA194_MAIN_GPIO_PORT( F, 4, 6, 6),
	TEGRA194_MAIN_GPIO_PORT( G, 4, 0, 8),
	TEGRA194_MAIN_GPIO_PORT( H, 4, 1, 8),
	TEGRA194_MAIN_GPIO_PORT( I, 4, 2, 5),
	TEGRA194_MAIN_GPIO_PORT( J, 5, 1, 6),
	TEGRA194_MAIN_GPIO_PORT( K, 3, 0, 8),
	TEGRA194_MAIN_GPIO_PORT( L, 3, 1, 4),
	TEGRA194_MAIN_GPIO_PORT( M, 2, 3, 8),
	TEGRA194_MAIN_GPIO_PORT( N, 2, 4, 3),
	TEGRA194_MAIN_GPIO_PORT( O, 5, 0, 6),
	TEGRA194_MAIN_GPIO_PORT( P, 2, 5, 8),
	TEGRA194_MAIN_GPIO_PORT( Q, 2, 6, 8),
	TEGRA194_MAIN_GPIO_PORT( R, 2, 7, 6),
	TEGRA194_MAIN_GPIO_PORT( S, 3, 3, 8),
	TEGRA194_MAIN_GPIO_PORT( T, 3, 4, 8),
	TEGRA194_MAIN_GPIO_PORT( U, 3, 5, 1),
	TEGRA194_MAIN_GPIO_PORT( V, 1, 0, 8),
	TEGRA194_MAIN_GPIO_PORT( W, 1, 1, 2),
	TEGRA194_MAIN_GPIO_PORT( X, 2, 0, 8),
	TEGRA194_MAIN_GPIO_PORT( Y, 2, 1, 8),
	TEGRA194_MAIN_GPIO_PORT( Z, 2, 2, 8),
	TEGRA194_MAIN_GPIO_PORT(FF, 3, 2, 2),
	TEGRA194_MAIN_GPIO_PORT(GG, 0, 0, 2)
पूर्ण;

अटल स्थिर काष्ठा tegra186_pin_range tegra194_मुख्य_pin_ranges[] = अणु
	अणु TEGRA194_MAIN_GPIO(GG, 0), "pex_l5_clkreq_n_pgg0" पूर्ण,
	अणु TEGRA194_MAIN_GPIO(GG, 1), "pex_l5_rst_n_pgg1" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_gpio_soc tegra194_मुख्य_soc = अणु
	.num_ports = ARRAY_SIZE(tegra194_मुख्य_ports),
	.ports = tegra194_मुख्य_ports,
	.name = "tegra194-gpio",
	.instance = 0,
	.num_pin_ranges = ARRAY_SIZE(tegra194_मुख्य_pin_ranges),
	.pin_ranges = tegra194_मुख्य_pin_ranges,
	.pinmux = "nvidia,tegra194-pinmux",
पूर्ण;

#घोषणा TEGRA194_AON_GPIO_PORT(_name, _bank, _port, _pins)	\
	[TEGRA194_AON_GPIO_PORT_##_name] = अणु			\
		.name = #_name,					\
		.bank = _bank,					\
		.port = _port,					\
		.pins = _pins,					\
	पूर्ण

अटल स्थिर काष्ठा tegra_gpio_port tegra194_aon_ports[] = अणु
	TEGRA194_AON_GPIO_PORT(AA, 0, 3, 8),
	TEGRA194_AON_GPIO_PORT(BB, 0, 4, 4),
	TEGRA194_AON_GPIO_PORT(CC, 0, 1, 8),
	TEGRA194_AON_GPIO_PORT(DD, 0, 2, 3),
	TEGRA194_AON_GPIO_PORT(EE, 0, 0, 7)
पूर्ण;

अटल स्थिर काष्ठा tegra_gpio_soc tegra194_aon_soc = अणु
	.num_ports = ARRAY_SIZE(tegra194_aon_ports),
	.ports = tegra194_aon_ports,
	.name = "tegra194-gpio-aon",
	.instance = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra186_gpio_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra186-gpio",
		.data = &tegra186_मुख्य_soc
	पूर्ण, अणु
		.compatible = "nvidia,tegra186-gpio-aon",
		.data = &tegra186_aon_soc
	पूर्ण, अणु
		.compatible = "nvidia,tegra194-gpio",
		.data = &tegra194_मुख्य_soc
	पूर्ण, अणु
		.compatible = "nvidia,tegra194-gpio-aon",
		.data = &tegra194_aon_soc
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra186_gpio_of_match);

अटल काष्ठा platक्रमm_driver tegra186_gpio_driver = अणु
	.driver = अणु
		.name = "tegra186-gpio",
		.of_match_table = tegra186_gpio_of_match,
	पूर्ण,
	.probe = tegra186_gpio_probe,
	.हटाओ = tegra186_gpio_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra186_gpio_driver);

MODULE_DESCRIPTION("NVIDIA Tegra186 GPIO controller driver");
MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_LICENSE("GPL v2");
