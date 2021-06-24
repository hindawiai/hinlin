<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Jamie Iles
 *
 * All enquiries to support@picochip.com
 */
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_data/gpio-dwapb.h>
#समावेश <linux/slab.h>

#समावेश "gpiolib.h"
#समावेश "gpiolib-acpi.h"

#घोषणा GPIO_SWPORTA_DR		0x00
#घोषणा GPIO_SWPORTA_DDR	0x04
#घोषणा GPIO_SWPORTB_DR		0x0c
#घोषणा GPIO_SWPORTB_DDR	0x10
#घोषणा GPIO_SWPORTC_DR		0x18
#घोषणा GPIO_SWPORTC_DDR	0x1c
#घोषणा GPIO_SWPORTD_DR		0x24
#घोषणा GPIO_SWPORTD_DDR	0x28
#घोषणा GPIO_INTEN		0x30
#घोषणा GPIO_INTMASK		0x34
#घोषणा GPIO_INTTYPE_LEVEL	0x38
#घोषणा GPIO_INT_POLARITY	0x3c
#घोषणा GPIO_INTSTATUS		0x40
#घोषणा GPIO_PORTA_DEBOUNCE	0x48
#घोषणा GPIO_PORTA_EOI		0x4c
#घोषणा GPIO_EXT_PORTA		0x50
#घोषणा GPIO_EXT_PORTB		0x54
#घोषणा GPIO_EXT_PORTC		0x58
#घोषणा GPIO_EXT_PORTD		0x5c

#घोषणा DWAPB_DRIVER_NAME	"gpio-dwapb"
#घोषणा DWAPB_MAX_PORTS		4

#घोषणा GPIO_EXT_PORT_STRIDE	0x04 /* रेजिस्टर stride 32 bits */
#घोषणा GPIO_SWPORT_DR_STRIDE	0x0c /* रेजिस्टर stride 3*32 bits */
#घोषणा GPIO_SWPORT_DDR_STRIDE	0x0c /* रेजिस्टर stride 3*32 bits */

#घोषणा GPIO_REG_OFFSET_V2	1

#घोषणा GPIO_INTMASK_V2		0x44
#घोषणा GPIO_INTTYPE_LEVEL_V2	0x34
#घोषणा GPIO_INT_POLARITY_V2	0x38
#घोषणा GPIO_INTSTATUS_V2	0x3c
#घोषणा GPIO_PORTA_EOI_V2	0x40

#घोषणा DWAPB_NR_CLOCKS		2

काष्ठा dwapb_gpio;

#अगर_घोषित CONFIG_PM_SLEEP
/* Store GPIO context across प्रणाली-wide suspend/resume transitions */
काष्ठा dwapb_context अणु
	u32 data;
	u32 dir;
	u32 ext;
	u32 पूर्णांक_en;
	u32 पूर्णांक_mask;
	u32 पूर्णांक_type;
	u32 पूर्णांक_pol;
	u32 पूर्णांक_deb;
	u32 wake_en;
पूर्ण;
#पूर्ण_अगर

काष्ठा dwapb_gpio_port_irqchip अणु
	काष्ठा irq_chip		irqchip;
	अचिन्हित पूर्णांक		nr_irqs;
	अचिन्हित पूर्णांक		irq[DWAPB_MAX_GPIOS];
पूर्ण;

काष्ठा dwapb_gpio_port अणु
	काष्ठा gpio_chip	gc;
	काष्ठा dwapb_gpio_port_irqchip *pirq;
	काष्ठा dwapb_gpio	*gpio;
#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा dwapb_context	*ctx;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		idx;
पूर्ण;
#घोषणा to_dwapb_gpio(_gc) \
	(container_of(_gc, काष्ठा dwapb_gpio_port, gc)->gpio)

काष्ठा dwapb_gpio अणु
	काष्ठा	device		*dev;
	व्योम __iomem		*regs;
	काष्ठा dwapb_gpio_port	*ports;
	अचिन्हित पूर्णांक		nr_ports;
	अचिन्हित पूर्णांक		flags;
	काष्ठा reset_control	*rst;
	काष्ठा clk_bulk_data	clks[DWAPB_NR_CLOCKS];
पूर्ण;

अटल अंतरभूत u32 gpio_reg_v2_convert(अचिन्हित पूर्णांक offset)
अणु
	चयन (offset) अणु
	हाल GPIO_INTMASK:
		वापस GPIO_INTMASK_V2;
	हाल GPIO_INTTYPE_LEVEL:
		वापस GPIO_INTTYPE_LEVEL_V2;
	हाल GPIO_INT_POLARITY:
		वापस GPIO_INT_POLARITY_V2;
	हाल GPIO_INTSTATUS:
		वापस GPIO_INTSTATUS_V2;
	हाल GPIO_PORTA_EOI:
		वापस GPIO_PORTA_EOI_V2;
	पूर्ण

	वापस offset;
पूर्ण

अटल अंतरभूत u32 gpio_reg_convert(काष्ठा dwapb_gpio *gpio, अचिन्हित पूर्णांक offset)
अणु
	अगर (gpio->flags & GPIO_REG_OFFSET_V2)
		वापस gpio_reg_v2_convert(offset);

	वापस offset;
पूर्ण

अटल अंतरभूत u32 dwapb_पढ़ो(काष्ठा dwapb_gpio *gpio, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_chip *gc	= &gpio->ports[0].gc;
	व्योम __iomem *reg_base	= gpio->regs;

	वापस gc->पढ़ो_reg(reg_base + gpio_reg_convert(gpio, offset));
पूर्ण

अटल अंतरभूत व्योम dwapb_ग_लिखो(काष्ठा dwapb_gpio *gpio, अचिन्हित पूर्णांक offset,
			       u32 val)
अणु
	काष्ठा gpio_chip *gc	= &gpio->ports[0].gc;
	व्योम __iomem *reg_base	= gpio->regs;

	gc->ग_लिखो_reg(reg_base + gpio_reg_convert(gpio, offset), val);
पूर्ण

अटल काष्ठा dwapb_gpio_port *dwapb_offs_to_port(काष्ठा dwapb_gpio *gpio, अचिन्हित पूर्णांक offs)
अणु
	काष्ठा dwapb_gpio_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < gpio->nr_ports; i++) अणु
		port = &gpio->ports[i];
		अगर (port->idx == offs / DWAPB_MAX_GPIOS)
			वापस port;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम dwapb_toggle_trigger(काष्ठा dwapb_gpio *gpio, अचिन्हित पूर्णांक offs)
अणु
	काष्ठा dwapb_gpio_port *port = dwapb_offs_to_port(gpio, offs);
	काष्ठा gpio_chip *gc;
	u32 pol;
	पूर्णांक val;

	अगर (!port)
		वापस;
	gc = &port->gc;

	pol = dwapb_पढ़ो(gpio, GPIO_INT_POLARITY);
	/* Just पढ़ो the current value right out of the data रेजिस्टर */
	val = gc->get(gc, offs % DWAPB_MAX_GPIOS);
	अगर (val)
		pol &= ~BIT(offs);
	अन्यथा
		pol |= BIT(offs);

	dwapb_ग_लिखो(gpio, GPIO_INT_POLARITY, pol);
पूर्ण

अटल u32 dwapb_करो_irq(काष्ठा dwapb_gpio *gpio)
अणु
	काष्ठा gpio_chip *gc = &gpio->ports[0].gc;
	अचिन्हित दीर्घ irq_status;
	irq_hw_number_t hwirq;

	irq_status = dwapb_पढ़ो(gpio, GPIO_INTSTATUS);
	क्रम_each_set_bit(hwirq, &irq_status, DWAPB_MAX_GPIOS) अणु
		पूर्णांक gpio_irq = irq_find_mapping(gc->irq.करोमुख्य, hwirq);
		u32 irq_type = irq_get_trigger_type(gpio_irq);

		generic_handle_irq(gpio_irq);

		अगर ((irq_type & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_BOTH)
			dwapb_toggle_trigger(gpio, hwirq);
	पूर्ण

	वापस irq_status;
पूर्ण

अटल व्योम dwapb_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा dwapb_gpio *gpio = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	chained_irq_enter(chip, desc);
	dwapb_करो_irq(gpio);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल irqवापस_t dwapb_irq_handler_mfd(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_RETVAL(dwapb_करो_irq(dev_id));
पूर्ण

अटल व्योम dwapb_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा dwapb_gpio *gpio = to_dwapb_gpio(gc);
	u32 val = BIT(irqd_to_hwirq(d));
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	dwapb_ग_लिखो(gpio, GPIO_PORTA_EOI, val);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम dwapb_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा dwapb_gpio *gpio = to_dwapb_gpio(gc);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	val = dwapb_पढ़ो(gpio, GPIO_INTMASK) | BIT(irqd_to_hwirq(d));
	dwapb_ग_लिखो(gpio, GPIO_INTMASK, val);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम dwapb_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा dwapb_gpio *gpio = to_dwapb_gpio(gc);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	val = dwapb_पढ़ो(gpio, GPIO_INTMASK) & ~BIT(irqd_to_hwirq(d));
	dwapb_ग_लिखो(gpio, GPIO_INTMASK, val);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम dwapb_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा dwapb_gpio *gpio = to_dwapb_gpio(gc);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	val = dwapb_पढ़ो(gpio, GPIO_INTEN);
	val |= BIT(irqd_to_hwirq(d));
	dwapb_ग_लिखो(gpio, GPIO_INTEN, val);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम dwapb_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा dwapb_gpio *gpio = to_dwapb_gpio(gc);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	val = dwapb_पढ़ो(gpio, GPIO_INTEN);
	val &= ~BIT(irqd_to_hwirq(d));
	dwapb_ग_लिखो(gpio, GPIO_INTEN, val);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल पूर्णांक dwapb_irq_set_type(काष्ठा irq_data *d, u32 type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा dwapb_gpio *gpio = to_dwapb_gpio(gc);
	irq_hw_number_t bit = irqd_to_hwirq(d);
	अचिन्हित दीर्घ level, polarity, flags;

	अगर (type & ~IRQ_TYPE_SENSE_MASK)
		वापस -EINVAL;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	level = dwapb_पढ़ो(gpio, GPIO_INTTYPE_LEVEL);
	polarity = dwapb_पढ़ो(gpio, GPIO_INT_POLARITY);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		level |= BIT(bit);
		dwapb_toggle_trigger(gpio, bit);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		level |= BIT(bit);
		polarity |= BIT(bit);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		level |= BIT(bit);
		polarity &= ~BIT(bit);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		level &= ~BIT(bit);
		polarity |= BIT(bit);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		level &= ~BIT(bit);
		polarity &= ~BIT(bit);
		अवरोध;
	पूर्ण

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);

	dwapb_ग_लिखो(gpio, GPIO_INTTYPE_LEVEL, level);
	अगर (type != IRQ_TYPE_EDGE_BOTH)
		dwapb_ग_लिखो(gpio, GPIO_INT_POLARITY, polarity);
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dwapb_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा dwapb_gpio *gpio = to_dwapb_gpio(gc);
	काष्ठा dwapb_context *ctx = gpio->ports[0].ctx;
	irq_hw_number_t bit = irqd_to_hwirq(d);

	अगर (enable)
		ctx->wake_en |= BIT(bit);
	अन्यथा
		ctx->wake_en &= ~BIT(bit);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dwapb_gpio_set_debounce(काष्ठा gpio_chip *gc,
				   अचिन्हित offset, अचिन्हित debounce)
अणु
	काष्ठा dwapb_gpio_port *port = gpiochip_get_data(gc);
	काष्ठा dwapb_gpio *gpio = port->gpio;
	अचिन्हित दीर्घ flags, val_deb;
	अचिन्हित दीर्घ mask = BIT(offset);

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	val_deb = dwapb_पढ़ो(gpio, GPIO_PORTA_DEBOUNCE);
	अगर (debounce)
		val_deb |= mask;
	अन्यथा
		val_deb &= ~mask;
	dwapb_ग_लिखो(gpio, GPIO_PORTA_DEBOUNCE, val_deb);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwapb_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित offset,
				 अचिन्हित दीर्घ config)
अणु
	u32 debounce;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	वापस dwapb_gpio_set_debounce(gc, offset, debounce);
पूर्ण

अटल पूर्णांक dwapb_convert_irqs(काष्ठा dwapb_gpio_port_irqchip *pirq,
			      काष्ठा dwapb_port_property *pp)
अणु
	पूर्णांक i;

	/* Group all available IRQs पूर्णांकo an array of parental IRQs. */
	क्रम (i = 0; i < pp->ngpio; ++i) अणु
		अगर (!pp->irq[i])
			जारी;

		pirq->irq[pirq->nr_irqs++] = pp->irq[i];
	पूर्ण

	वापस pirq->nr_irqs ? 0 : -ENOENT;
पूर्ण

अटल व्योम dwapb_configure_irqs(काष्ठा dwapb_gpio *gpio,
				 काष्ठा dwapb_gpio_port *port,
				 काष्ठा dwapb_port_property *pp)
अणु
	काष्ठा dwapb_gpio_port_irqchip *pirq;
	काष्ठा gpio_chip *gc = &port->gc;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक err;

	pirq = devm_kzalloc(gpio->dev, माप(*pirq), GFP_KERNEL);
	अगर (!pirq)
		वापस;

	अगर (dwapb_convert_irqs(pirq, pp)) अणु
		dev_warn(gpio->dev, "no IRQ for port%d\n", pp->idx);
		जाओ err_kमुक्त_pirq;
	पूर्ण

	girq = &gc->irq;
	girq->handler = handle_bad_irq;
	girq->शेष_type = IRQ_TYPE_NONE;

	port->pirq = pirq;
	pirq->irqchip.name = DWAPB_DRIVER_NAME;
	pirq->irqchip.irq_ack = dwapb_irq_ack;
	pirq->irqchip.irq_mask = dwapb_irq_mask;
	pirq->irqchip.irq_unmask = dwapb_irq_unmask;
	pirq->irqchip.irq_set_type = dwapb_irq_set_type;
	pirq->irqchip.irq_enable = dwapb_irq_enable;
	pirq->irqchip.irq_disable = dwapb_irq_disable;
#अगर_घोषित CONFIG_PM_SLEEP
	pirq->irqchip.irq_set_wake = dwapb_irq_set_wake;
#पूर्ण_अगर

	अगर (!pp->irq_shared) अणु
		girq->num_parents = pirq->nr_irqs;
		girq->parents = pirq->irq;
		girq->parent_handler_data = gpio;
		girq->parent_handler = dwapb_irq_handler;
	पूर्ण अन्यथा अणु
		/* This will let us handle the parent IRQ in the driver */
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->parent_handler = शून्य;

		/*
		 * Request a shared IRQ since where MFD would have devices
		 * using the same irq pin
		 */
		err = devm_request_irq(gpio->dev, pp->irq[0],
				       dwapb_irq_handler_mfd,
				       IRQF_SHARED, DWAPB_DRIVER_NAME, gpio);
		अगर (err) अणु
			dev_err(gpio->dev, "error requesting IRQ\n");
			जाओ err_kमुक्त_pirq;
		पूर्ण
	पूर्ण

	girq->chip = &pirq->irqchip;

	वापस;

err_kमुक्त_pirq:
	devm_kमुक्त(gpio->dev, pirq);
पूर्ण

अटल पूर्णांक dwapb_gpio_add_port(काष्ठा dwapb_gpio *gpio,
			       काष्ठा dwapb_port_property *pp,
			       अचिन्हित पूर्णांक offs)
अणु
	काष्ठा dwapb_gpio_port *port;
	व्योम __iomem *dat, *set, *dirout;
	पूर्णांक err;

	port = &gpio->ports[offs];
	port->gpio = gpio;
	port->idx = pp->idx;

#अगर_घोषित CONFIG_PM_SLEEP
	port->ctx = devm_kzalloc(gpio->dev, माप(*port->ctx), GFP_KERNEL);
	अगर (!port->ctx)
		वापस -ENOMEM;
#पूर्ण_अगर

	dat = gpio->regs + GPIO_EXT_PORTA + pp->idx * GPIO_EXT_PORT_STRIDE;
	set = gpio->regs + GPIO_SWPORTA_DR + pp->idx * GPIO_SWPORT_DR_STRIDE;
	dirout = gpio->regs + GPIO_SWPORTA_DDR + pp->idx * GPIO_SWPORT_DDR_STRIDE;

	/* This रेजिस्टरs 32 GPIO lines per port */
	err = bgpio_init(&port->gc, gpio->dev, 4, dat, set, शून्य, dirout,
			 शून्य, 0);
	अगर (err) अणु
		dev_err(gpio->dev, "failed to init gpio chip for port%d\n",
			port->idx);
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_OF_GPIO
	port->gc.of_node = to_of_node(pp->fwnode);
#पूर्ण_अगर
	port->gc.ngpio = pp->ngpio;
	port->gc.base = pp->gpio_base;

	/* Only port A support debounce */
	अगर (pp->idx == 0)
		port->gc.set_config = dwapb_gpio_set_config;

	/* Only port A can provide पूर्णांकerrupts in all configurations of the IP */
	अगर (pp->idx == 0)
		dwapb_configure_irqs(gpio, port, pp);

	err = devm_gpiochip_add_data(gpio->dev, &port->gc, port);
	अगर (err) अणु
		dev_err(gpio->dev, "failed to register gpiochip for port%d\n",
			port->idx);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dwapb_get_irq(काष्ठा device *dev, काष्ठा fwnode_handle *fwnode,
			  काष्ठा dwapb_port_property *pp)
अणु
	काष्ठा device_node *np = शून्य;
	पूर्णांक irq = -ENXIO, j;

	अगर (fwnode_property_पढ़ो_bool(fwnode, "interrupt-controller"))
		np = to_of_node(fwnode);

	क्रम (j = 0; j < pp->ngpio; j++) अणु
		अगर (np)
			irq = of_irq_get(np, j);
		अन्यथा अगर (has_acpi_companion(dev))
			irq = platक्रमm_get_irq_optional(to_platक्रमm_device(dev), j);
		अगर (irq > 0)
			pp->irq[j] = irq;
	पूर्ण
पूर्ण

अटल काष्ठा dwapb_platक्रमm_data *dwapb_gpio_get_pdata(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा dwapb_platक्रमm_data *pdata;
	काष्ठा dwapb_port_property *pp;
	पूर्णांक nports;
	पूर्णांक i;

	nports = device_get_child_node_count(dev);
	अगर (nports == 0)
		वापस ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->properties = devm_kसुस्मृति(dev, nports, माप(*pp), GFP_KERNEL);
	अगर (!pdata->properties)
		वापस ERR_PTR(-ENOMEM);

	pdata->nports = nports;

	i = 0;
	device_क्रम_each_child_node(dev, fwnode)  अणु
		pp = &pdata->properties[i++];
		pp->fwnode = fwnode;

		अगर (fwnode_property_पढ़ो_u32(fwnode, "reg", &pp->idx) ||
		    pp->idx >= DWAPB_MAX_PORTS) अणु
			dev_err(dev,
				"missing/invalid port index for port%d\n", i);
			fwnode_handle_put(fwnode);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		अगर (fwnode_property_पढ़ो_u32(fwnode, "ngpios", &pp->ngpio) &&
		    fwnode_property_पढ़ो_u32(fwnode, "snps,nr-gpios", &pp->ngpio)) अणु
			dev_info(dev,
				 "failed to get number of gpios for port%d\n",
				 i);
			pp->ngpio = DWAPB_MAX_GPIOS;
		पूर्ण

		pp->irq_shared	= false;
		pp->gpio_base	= -1;

		/*
		 * Only port A can provide पूर्णांकerrupts in all configurations of
		 * the IP.
		 */
		अगर (pp->idx == 0)
			dwapb_get_irq(dev, fwnode, pp);
	पूर्ण

	वापस pdata;
पूर्ण

अटल व्योम dwapb_निश्चित_reset(व्योम *data)
अणु
	काष्ठा dwapb_gpio *gpio = data;

	reset_control_निश्चित(gpio->rst);
पूर्ण

अटल पूर्णांक dwapb_get_reset(काष्ठा dwapb_gpio *gpio)
अणु
	पूर्णांक err;

	gpio->rst = devm_reset_control_get_optional_shared(gpio->dev, शून्य);
	अगर (IS_ERR(gpio->rst))
		वापस dev_err_probe(gpio->dev, PTR_ERR(gpio->rst),
				     "Cannot get reset descriptor\n");

	err = reset_control_deनिश्चित(gpio->rst);
	अगर (err) अणु
		dev_err(gpio->dev, "Cannot deassert reset lane\n");
		वापस err;
	पूर्ण

	वापस devm_add_action_or_reset(gpio->dev, dwapb_निश्चित_reset, gpio);
पूर्ण

अटल व्योम dwapb_disable_clks(व्योम *data)
अणु
	काष्ठा dwapb_gpio *gpio = data;

	clk_bulk_disable_unprepare(DWAPB_NR_CLOCKS, gpio->clks);
पूर्ण

अटल पूर्णांक dwapb_get_clks(काष्ठा dwapb_gpio *gpio)
अणु
	पूर्णांक err;

	/* Optional bus and debounce घड़ीs */
	gpio->clks[0].id = "bus";
	gpio->clks[1].id = "db";
	err = devm_clk_bulk_get_optional(gpio->dev, DWAPB_NR_CLOCKS,
					 gpio->clks);
	अगर (err) अणु
		dev_err(gpio->dev, "Cannot get APB/Debounce clocks\n");
		वापस err;
	पूर्ण

	err = clk_bulk_prepare_enable(DWAPB_NR_CLOCKS, gpio->clks);
	अगर (err) अणु
		dev_err(gpio->dev, "Cannot enable APB/Debounce clocks\n");
		वापस err;
	पूर्ण

	वापस devm_add_action_or_reset(gpio->dev, dwapb_disable_clks, gpio);
पूर्ण

अटल स्थिर काष्ठा of_device_id dwapb_of_match[] = अणु
	अणु .compatible = "snps,dw-apb-gpio", .data = (व्योम *)0पूर्ण,
	अणु .compatible = "apm,xgene-gpio-v2", .data = (व्योम *)GPIO_REG_OFFSET_V2पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dwapb_of_match);

अटल स्थिर काष्ठा acpi_device_id dwapb_acpi_match[] = अणु
	अणु"HISI0181", 0पूर्ण,
	अणु"APMC0D07", 0पूर्ण,
	अणु"APMC0D81", GPIO_REG_OFFSET_V2पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dwapb_acpi_match);

अटल पूर्णांक dwapb_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा dwapb_gpio *gpio;
	पूर्णांक err;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dwapb_platक्रमm_data *pdata = dev_get_platdata(dev);

	अगर (!pdata) अणु
		pdata = dwapb_gpio_get_pdata(dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	अगर (!pdata->nports)
		वापस -ENODEV;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->dev = &pdev->dev;
	gpio->nr_ports = pdata->nports;

	err = dwapb_get_reset(gpio);
	अगर (err)
		वापस err;

	gpio->ports = devm_kसुस्मृति(&pdev->dev, gpio->nr_ports,
				   माप(*gpio->ports), GFP_KERNEL);
	अगर (!gpio->ports)
		वापस -ENOMEM;

	gpio->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio->regs))
		वापस PTR_ERR(gpio->regs);

	err = dwapb_get_clks(gpio);
	अगर (err)
		वापस err;

	gpio->flags = (uपूर्णांकptr_t)device_get_match_data(dev);

	क्रम (i = 0; i < gpio->nr_ports; i++) अणु
		err = dwapb_gpio_add_port(gpio, &pdata->properties[i], i);
		अगर (err)
			वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gpio);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dwapb_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwapb_gpio *gpio = dev_get_drvdata(dev);
	काष्ठा gpio_chip *gc	= &gpio->ports[0].gc;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	क्रम (i = 0; i < gpio->nr_ports; i++) अणु
		अचिन्हित पूर्णांक offset;
		अचिन्हित पूर्णांक idx = gpio->ports[i].idx;
		काष्ठा dwapb_context *ctx = gpio->ports[i].ctx;

		offset = GPIO_SWPORTA_DDR + idx * GPIO_SWPORT_DDR_STRIDE;
		ctx->dir = dwapb_पढ़ो(gpio, offset);

		offset = GPIO_SWPORTA_DR + idx * GPIO_SWPORT_DR_STRIDE;
		ctx->data = dwapb_पढ़ो(gpio, offset);

		offset = GPIO_EXT_PORTA + idx * GPIO_EXT_PORT_STRIDE;
		ctx->ext = dwapb_पढ़ो(gpio, offset);

		/* Only port A can provide पूर्णांकerrupts */
		अगर (idx == 0) अणु
			ctx->पूर्णांक_mask	= dwapb_पढ़ो(gpio, GPIO_INTMASK);
			ctx->पूर्णांक_en	= dwapb_पढ़ो(gpio, GPIO_INTEN);
			ctx->पूर्णांक_pol	= dwapb_पढ़ो(gpio, GPIO_INT_POLARITY);
			ctx->पूर्णांक_type	= dwapb_पढ़ो(gpio, GPIO_INTTYPE_LEVEL);
			ctx->पूर्णांक_deb	= dwapb_पढ़ो(gpio, GPIO_PORTA_DEBOUNCE);

			/* Mask out पूर्णांकerrupts */
			dwapb_ग_लिखो(gpio, GPIO_INTMASK, ~ctx->wake_en);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	clk_bulk_disable_unprepare(DWAPB_NR_CLOCKS, gpio->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक dwapb_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा dwapb_gpio *gpio = dev_get_drvdata(dev);
	काष्ठा gpio_chip *gc	= &gpio->ports[0].gc;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, err;

	err = clk_bulk_prepare_enable(DWAPB_NR_CLOCKS, gpio->clks);
	अगर (err) अणु
		dev_err(gpio->dev, "Cannot reenable APB/Debounce clocks\n");
		वापस err;
	पूर्ण

	spin_lock_irqsave(&gc->bgpio_lock, flags);
	क्रम (i = 0; i < gpio->nr_ports; i++) अणु
		अचिन्हित पूर्णांक offset;
		अचिन्हित पूर्णांक idx = gpio->ports[i].idx;
		काष्ठा dwapb_context *ctx = gpio->ports[i].ctx;

		offset = GPIO_SWPORTA_DR + idx * GPIO_SWPORT_DR_STRIDE;
		dwapb_ग_लिखो(gpio, offset, ctx->data);

		offset = GPIO_SWPORTA_DDR + idx * GPIO_SWPORT_DDR_STRIDE;
		dwapb_ग_लिखो(gpio, offset, ctx->dir);

		offset = GPIO_EXT_PORTA + idx * GPIO_EXT_PORT_STRIDE;
		dwapb_ग_लिखो(gpio, offset, ctx->ext);

		/* Only port A can provide पूर्णांकerrupts */
		अगर (idx == 0) अणु
			dwapb_ग_लिखो(gpio, GPIO_INTTYPE_LEVEL, ctx->पूर्णांक_type);
			dwapb_ग_लिखो(gpio, GPIO_INT_POLARITY, ctx->पूर्णांक_pol);
			dwapb_ग_लिखो(gpio, GPIO_PORTA_DEBOUNCE, ctx->पूर्णांक_deb);
			dwapb_ग_लिखो(gpio, GPIO_INTEN, ctx->पूर्णांक_en);
			dwapb_ग_लिखो(gpio, GPIO_INTMASK, ctx->पूर्णांक_mask);

			/* Clear out spurious पूर्णांकerrupts */
			dwapb_ग_लिखो(gpio, GPIO_PORTA_EOI, 0xffffffff);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(dwapb_gpio_pm_ops, dwapb_gpio_suspend,
			 dwapb_gpio_resume);

अटल काष्ठा platक्रमm_driver dwapb_gpio_driver = अणु
	.driver		= अणु
		.name	= DWAPB_DRIVER_NAME,
		.pm	= &dwapb_gpio_pm_ops,
		.of_match_table = dwapb_of_match,
		.acpi_match_table = dwapb_acpi_match,
	पूर्ण,
	.probe		= dwapb_gpio_probe,
पूर्ण;

module_platक्रमm_driver(dwapb_gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jamie Iles");
MODULE_DESCRIPTION("Synopsys DesignWare APB GPIO driver");
MODULE_ALIAS("platform:" DWAPB_DRIVER_NAME);
