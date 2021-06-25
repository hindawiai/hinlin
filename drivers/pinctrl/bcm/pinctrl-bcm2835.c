<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Broadcom BCM2835 GPIO unit (pinctrl + GPIO)
 *
 * Copyright (C) 2012 Chris Boot, Simon Arlott, Stephen Warren
 *
 * This driver is inspired by:
 * pinctrl-nomadik.c, please see original file क्रम copyright inक्रमmation
 * pinctrl-tegra.c, please see original file क्रम copyright inक्रमmation
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bug.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <dt-bindings/pinctrl/bcm2835.h>

#घोषणा MODULE_NAME "pinctrl-bcm2835"
#घोषणा BCM2835_NUM_GPIOS 54
#घोषणा BCM2711_NUM_GPIOS 58
#घोषणा BCM2835_NUM_BANKS 2
#घोषणा BCM2835_NUM_IRQS  3

/* GPIO रेजिस्टर offsets */
#घोषणा GPFSEL0		0x0	/* Function Select */
#घोषणा GPSET0		0x1c	/* Pin Output Set */
#घोषणा GPCLR0		0x28	/* Pin Output Clear */
#घोषणा GPLEV0		0x34	/* Pin Level */
#घोषणा GPEDS0		0x40	/* Pin Event Detect Status */
#घोषणा GPREN0		0x4c	/* Pin Rising Edge Detect Enable */
#घोषणा GPFEN0		0x58	/* Pin Falling Edge Detect Enable */
#घोषणा GPHEN0		0x64	/* Pin High Detect Enable */
#घोषणा GPLEN0		0x70	/* Pin Low Detect Enable */
#घोषणा GPAREN0		0x7c	/* Pin Async Rising Edge Detect */
#घोषणा GPAFEN0		0x88	/* Pin Async Falling Edge Detect */
#घोषणा GPPUD		0x94	/* Pin Pull-up/करोwn Enable */
#घोषणा GPPUDCLK0	0x98	/* Pin Pull-up/करोwn Enable Clock */
#घोषणा GP_GPIO_PUP_PDN_CNTRL_REG0 0xe4 /* 2711 Pin Pull-up/करोwn select */

#घोषणा FSEL_REG(p)		(GPFSEL0 + (((p) / 10) * 4))
#घोषणा FSEL_SHIFT(p)		(((p) % 10) * 3)
#घोषणा GPIO_REG_OFFSET(p)	((p) / 32)
#घोषणा GPIO_REG_SHIFT(p)	((p) % 32)

#घोषणा PUD_2711_MASK		0x3
#घोषणा PUD_2711_REG_OFFSET(p)	((p) / 16)
#घोषणा PUD_2711_REG_SHIFT(p)	(((p) % 16) * 2)

/* argument: bcm2835_pinconf_pull */
#घोषणा BCM2835_PINCONF_PARAM_PULL	(PIN_CONFIG_END + 1)

#घोषणा BCM2711_PULL_NONE	0x0
#घोषणा BCM2711_PULL_UP		0x1
#घोषणा BCM2711_PULL_DOWN	0x2

काष्ठा bcm2835_pinctrl अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	पूर्णांक *wake_irq;

	/* note: locking assumes each bank will have its own अचिन्हित दीर्घ */
	अचिन्हित दीर्घ enabled_irq_map[BCM2835_NUM_BANKS];
	अचिन्हित पूर्णांक irq_type[BCM2711_NUM_GPIOS];

	काष्ठा pinctrl_dev *pctl_dev;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा pinctrl_desc pctl_desc;
	काष्ठा pinctrl_gpio_range gpio_range;

	raw_spinlock_t irq_lock[BCM2835_NUM_BANKS];
पूर्ण;

/* pins are just named GPIO0..GPIO53 */
#घोषणा BCM2835_GPIO_PIN(a) PINCTRL_PIN(a, "gpio" #a)
अटल काष्ठा pinctrl_pin_desc bcm2835_gpio_pins[] = अणु
	BCM2835_GPIO_PIN(0),
	BCM2835_GPIO_PIN(1),
	BCM2835_GPIO_PIN(2),
	BCM2835_GPIO_PIN(3),
	BCM2835_GPIO_PIN(4),
	BCM2835_GPIO_PIN(5),
	BCM2835_GPIO_PIN(6),
	BCM2835_GPIO_PIN(7),
	BCM2835_GPIO_PIN(8),
	BCM2835_GPIO_PIN(9),
	BCM2835_GPIO_PIN(10),
	BCM2835_GPIO_PIN(11),
	BCM2835_GPIO_PIN(12),
	BCM2835_GPIO_PIN(13),
	BCM2835_GPIO_PIN(14),
	BCM2835_GPIO_PIN(15),
	BCM2835_GPIO_PIN(16),
	BCM2835_GPIO_PIN(17),
	BCM2835_GPIO_PIN(18),
	BCM2835_GPIO_PIN(19),
	BCM2835_GPIO_PIN(20),
	BCM2835_GPIO_PIN(21),
	BCM2835_GPIO_PIN(22),
	BCM2835_GPIO_PIN(23),
	BCM2835_GPIO_PIN(24),
	BCM2835_GPIO_PIN(25),
	BCM2835_GPIO_PIN(26),
	BCM2835_GPIO_PIN(27),
	BCM2835_GPIO_PIN(28),
	BCM2835_GPIO_PIN(29),
	BCM2835_GPIO_PIN(30),
	BCM2835_GPIO_PIN(31),
	BCM2835_GPIO_PIN(32),
	BCM2835_GPIO_PIN(33),
	BCM2835_GPIO_PIN(34),
	BCM2835_GPIO_PIN(35),
	BCM2835_GPIO_PIN(36),
	BCM2835_GPIO_PIN(37),
	BCM2835_GPIO_PIN(38),
	BCM2835_GPIO_PIN(39),
	BCM2835_GPIO_PIN(40),
	BCM2835_GPIO_PIN(41),
	BCM2835_GPIO_PIN(42),
	BCM2835_GPIO_PIN(43),
	BCM2835_GPIO_PIN(44),
	BCM2835_GPIO_PIN(45),
	BCM2835_GPIO_PIN(46),
	BCM2835_GPIO_PIN(47),
	BCM2835_GPIO_PIN(48),
	BCM2835_GPIO_PIN(49),
	BCM2835_GPIO_PIN(50),
	BCM2835_GPIO_PIN(51),
	BCM2835_GPIO_PIN(52),
	BCM2835_GPIO_PIN(53),
	BCM2835_GPIO_PIN(54),
	BCM2835_GPIO_PIN(55),
	BCM2835_GPIO_PIN(56),
	BCM2835_GPIO_PIN(57),
पूर्ण;

/* one pin per group */
अटल स्थिर अक्षर * स्थिर bcm2835_gpio_groups[] = अणु
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
	"gpio16",
	"gpio17",
	"gpio18",
	"gpio19",
	"gpio20",
	"gpio21",
	"gpio22",
	"gpio23",
	"gpio24",
	"gpio25",
	"gpio26",
	"gpio27",
	"gpio28",
	"gpio29",
	"gpio30",
	"gpio31",
	"gpio32",
	"gpio33",
	"gpio34",
	"gpio35",
	"gpio36",
	"gpio37",
	"gpio38",
	"gpio39",
	"gpio40",
	"gpio41",
	"gpio42",
	"gpio43",
	"gpio44",
	"gpio45",
	"gpio46",
	"gpio47",
	"gpio48",
	"gpio49",
	"gpio50",
	"gpio51",
	"gpio52",
	"gpio53",
	"gpio54",
	"gpio55",
	"gpio56",
	"gpio57",
पूर्ण;

क्रमागत bcm2835_fsel अणु
	BCM2835_FSEL_COUNT = 8,
	BCM2835_FSEL_MASK = 0x7,
पूर्ण;

अटल स्थिर अक्षर * स्थिर bcm2835_functions[BCM2835_FSEL_COUNT] = अणु
	[BCM2835_FSEL_GPIO_IN] = "gpio_in",
	[BCM2835_FSEL_GPIO_OUT] = "gpio_out",
	[BCM2835_FSEL_ALT0] = "alt0",
	[BCM2835_FSEL_ALT1] = "alt1",
	[BCM2835_FSEL_ALT2] = "alt2",
	[BCM2835_FSEL_ALT3] = "alt3",
	[BCM2835_FSEL_ALT4] = "alt4",
	[BCM2835_FSEL_ALT5] = "alt5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर irq_type_names[] = अणु
	[IRQ_TYPE_NONE] = "none",
	[IRQ_TYPE_EDGE_RISING] = "edge-rising",
	[IRQ_TYPE_EDGE_FALLING] = "edge-falling",
	[IRQ_TYPE_EDGE_BOTH] = "edge-both",
	[IRQ_TYPE_LEVEL_HIGH] = "level-high",
	[IRQ_TYPE_LEVEL_LOW] = "level-low",
पूर्ण;

अटल अंतरभूत u32 bcm2835_gpio_rd(काष्ठा bcm2835_pinctrl *pc, अचिन्हित reg)
अणु
	वापस पढ़ोl(pc->base + reg);
पूर्ण

अटल अंतरभूत व्योम bcm2835_gpio_wr(काष्ठा bcm2835_pinctrl *pc, अचिन्हित reg,
		u32 val)
अणु
	ग_लिखोl(val, pc->base + reg);
पूर्ण

अटल अंतरभूत पूर्णांक bcm2835_gpio_get_bit(काष्ठा bcm2835_pinctrl *pc, अचिन्हित reg,
		अचिन्हित bit)
अणु
	reg += GPIO_REG_OFFSET(bit) * 4;
	वापस (bcm2835_gpio_rd(pc, reg) >> GPIO_REG_SHIFT(bit)) & 1;
पूर्ण

/* note NOT a पढ़ो/modअगरy/ग_लिखो cycle */
अटल अंतरभूत व्योम bcm2835_gpio_set_bit(काष्ठा bcm2835_pinctrl *pc,
		अचिन्हित reg, अचिन्हित bit)
अणु
	reg += GPIO_REG_OFFSET(bit) * 4;
	bcm2835_gpio_wr(pc, reg, BIT(GPIO_REG_SHIFT(bit)));
पूर्ण

अटल अंतरभूत क्रमागत bcm2835_fsel bcm2835_pinctrl_fsel_get(
		काष्ठा bcm2835_pinctrl *pc, अचिन्हित pin)
अणु
	u32 val = bcm2835_gpio_rd(pc, FSEL_REG(pin));
	क्रमागत bcm2835_fsel status = (val >> FSEL_SHIFT(pin)) & BCM2835_FSEL_MASK;

	dev_dbg(pc->dev, "get %08x (%u => %s)\n", val, pin,
			bcm2835_functions[status]);

	वापस status;
पूर्ण

अटल अंतरभूत व्योम bcm2835_pinctrl_fsel_set(
		काष्ठा bcm2835_pinctrl *pc, अचिन्हित pin,
		क्रमागत bcm2835_fsel fsel)
अणु
	u32 val = bcm2835_gpio_rd(pc, FSEL_REG(pin));
	क्रमागत bcm2835_fsel cur = (val >> FSEL_SHIFT(pin)) & BCM2835_FSEL_MASK;

	dev_dbg(pc->dev, "read %08x (%u => %s)\n", val, pin,
			bcm2835_functions[cur]);

	अगर (cur == fsel)
		वापस;

	अगर (cur != BCM2835_FSEL_GPIO_IN && fsel != BCM2835_FSEL_GPIO_IN) अणु
		/* always transition through GPIO_IN */
		val &= ~(BCM2835_FSEL_MASK << FSEL_SHIFT(pin));
		val |= BCM2835_FSEL_GPIO_IN << FSEL_SHIFT(pin);

		dev_dbg(pc->dev, "trans %08x (%u <= %s)\n", val, pin,
				bcm2835_functions[BCM2835_FSEL_GPIO_IN]);
		bcm2835_gpio_wr(pc, FSEL_REG(pin), val);
	पूर्ण

	val &= ~(BCM2835_FSEL_MASK << FSEL_SHIFT(pin));
	val |= fsel << FSEL_SHIFT(pin);

	dev_dbg(pc->dev, "write %08x (%u <= %s)\n", val, pin,
			bcm2835_functions[fsel]);
	bcm2835_gpio_wr(pc, FSEL_REG(pin), val);
पूर्ण

अटल पूर्णांक bcm2835_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक bcm2835_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);

	वापस bcm2835_gpio_get_bit(pc, GPLEV0, offset);
पूर्ण

अटल पूर्णांक bcm2835_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	क्रमागत bcm2835_fsel fsel = bcm2835_pinctrl_fsel_get(pc, offset);

	/* Alternative function करोesn't clearly provide a direction */
	अगर (fsel > BCM2835_FSEL_GPIO_OUT)
		वापस -EINVAL;

	अगर (fsel == BCM2835_FSEL_GPIO_IN)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल व्योम bcm2835_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);

	bcm2835_gpio_set_bit(pc, value ? GPSET0 : GPCLR0, offset);
पूर्ण

अटल पूर्णांक bcm2835_gpio_direction_output(काष्ठा gpio_chip *chip,
		अचिन्हित offset, पूर्णांक value)
अणु
	bcm2835_gpio_set(chip, offset, value);
	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip bcm2835_gpio_chip = अणु
	.label = MODULE_NAME,
	.owner = THIS_MODULE,
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.direction_input = bcm2835_gpio_direction_input,
	.direction_output = bcm2835_gpio_direction_output,
	.get_direction = bcm2835_gpio_get_direction,
	.get = bcm2835_gpio_get,
	.set = bcm2835_gpio_set,
	.set_config = gpiochip_generic_config,
	.base = -1,
	.ngpio = BCM2835_NUM_GPIOS,
	.can_sleep = false,
पूर्ण;

अटल स्थिर काष्ठा gpio_chip bcm2711_gpio_chip = अणु
	.label = "pinctrl-bcm2711",
	.owner = THIS_MODULE,
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.direction_input = bcm2835_gpio_direction_input,
	.direction_output = bcm2835_gpio_direction_output,
	.get_direction = bcm2835_gpio_get_direction,
	.get = bcm2835_gpio_get,
	.set = bcm2835_gpio_set,
	.set_config = gpiochip_generic_config,
	.base = -1,
	.ngpio = BCM2711_NUM_GPIOS,
	.can_sleep = false,
पूर्ण;

अटल व्योम bcm2835_gpio_irq_handle_bank(काष्ठा bcm2835_pinctrl *pc,
					 अचिन्हित पूर्णांक bank, u32 mask)
अणु
	अचिन्हित दीर्घ events;
	अचिन्हित offset;
	अचिन्हित gpio;

	events = bcm2835_gpio_rd(pc, GPEDS0 + bank * 4);
	events &= mask;
	events &= pc->enabled_irq_map[bank];
	क्रम_each_set_bit(offset, &events, 32) अणु
		gpio = (32 * bank) + offset;
		generic_handle_irq(irq_linear_revmap(pc->gpio_chip.irq.करोमुख्य,
						     gpio));
	पूर्ण
पूर्ण

अटल व्योम bcm2835_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	काष्ठा irq_chip *host_chip = irq_desc_get_chip(desc);
	पूर्णांक irq = irq_desc_get_irq(desc);
	पूर्णांक group;
	पूर्णांक i;

	क्रम (i = 0; i < BCM2835_NUM_IRQS; i++) अणु
		अगर (chip->irq.parents[i] == irq) अणु
			group = i;
			अवरोध;
		पूर्ण
	पूर्ण
	/* This should not happen, every IRQ has a bank */
	अगर (i == BCM2835_NUM_IRQS)
		BUG();

	chained_irq_enter(host_chip, desc);

	चयन (group) अणु
	हाल 0: /* IRQ0 covers GPIOs 0-27 */
		bcm2835_gpio_irq_handle_bank(pc, 0, 0x0fffffff);
		अवरोध;
	हाल 1: /* IRQ1 covers GPIOs 28-45 */
		bcm2835_gpio_irq_handle_bank(pc, 0, 0xf0000000);
		bcm2835_gpio_irq_handle_bank(pc, 1, 0x00003fff);
		अवरोध;
	हाल 2: /* IRQ2 covers GPIOs 46-57 */
		bcm2835_gpio_irq_handle_bank(pc, 1, 0x003fc000);
		अवरोध;
	पूर्ण

	chained_irq_निकास(host_chip, desc);
पूर्ण

अटल irqवापस_t bcm2835_gpio_wake_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम __bcm2835_gpio_irq_config(काष्ठा bcm2835_pinctrl *pc,
	अचिन्हित reg, अचिन्हित offset, bool enable)
अणु
	u32 value;
	reg += GPIO_REG_OFFSET(offset) * 4;
	value = bcm2835_gpio_rd(pc, reg);
	अगर (enable)
		value |= BIT(GPIO_REG_SHIFT(offset));
	अन्यथा
		value &= ~(BIT(GPIO_REG_SHIFT(offset)));
	bcm2835_gpio_wr(pc, reg, value);
पूर्ण

/* fast path क्रम IRQ handler */
अटल व्योम bcm2835_gpio_irq_config(काष्ठा bcm2835_pinctrl *pc,
	अचिन्हित offset, bool enable)
अणु
	चयन (pc->irq_type[offset]) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		__bcm2835_gpio_irq_config(pc, GPREN0, offset, enable);
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		__bcm2835_gpio_irq_config(pc, GPFEN0, offset, enable);
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		__bcm2835_gpio_irq_config(pc, GPREN0, offset, enable);
		__bcm2835_gpio_irq_config(pc, GPFEN0, offset, enable);
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		__bcm2835_gpio_irq_config(pc, GPHEN0, offset, enable);
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		__bcm2835_gpio_irq_config(pc, GPLEN0, offset, enable);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bcm2835_gpio_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	अचिन्हित gpio = irqd_to_hwirq(data);
	अचिन्हित offset = GPIO_REG_SHIFT(gpio);
	अचिन्हित bank = GPIO_REG_OFFSET(gpio);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pc->irq_lock[bank], flags);
	set_bit(offset, &pc->enabled_irq_map[bank]);
	bcm2835_gpio_irq_config(pc, gpio, true);
	raw_spin_unlock_irqrestore(&pc->irq_lock[bank], flags);
पूर्ण

अटल व्योम bcm2835_gpio_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	अचिन्हित gpio = irqd_to_hwirq(data);
	अचिन्हित offset = GPIO_REG_SHIFT(gpio);
	अचिन्हित bank = GPIO_REG_OFFSET(gpio);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pc->irq_lock[bank], flags);
	bcm2835_gpio_irq_config(pc, gpio, false);
	/* Clear events that were latched prior to clearing event sources */
	bcm2835_gpio_set_bit(pc, GPEDS0, gpio);
	clear_bit(offset, &pc->enabled_irq_map[bank]);
	raw_spin_unlock_irqrestore(&pc->irq_lock[bank], flags);
पूर्ण

अटल पूर्णांक __bcm2835_gpio_irq_set_type_disabled(काष्ठा bcm2835_pinctrl *pc,
	अचिन्हित offset, अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल IRQ_TYPE_NONE:
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
	हाल IRQ_TYPE_LEVEL_HIGH:
	हाल IRQ_TYPE_LEVEL_LOW:
		pc->irq_type[offset] = type;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* slower path क्रम reconfiguring IRQ type */
अटल पूर्णांक __bcm2835_gpio_irq_set_type_enabled(काष्ठा bcm2835_pinctrl *pc,
	अचिन्हित offset, अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल IRQ_TYPE_NONE:
		अगर (pc->irq_type[offset] != type) अणु
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
		पूर्ण
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING:
		अगर (pc->irq_type[offset] == IRQ_TYPE_EDGE_BOTH) अणु
			/* RISING alपढ़ोy enabled, disable FALLING */
			pc->irq_type[offset] = IRQ_TYPE_EDGE_FALLING;
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
		पूर्ण अन्यथा अगर (pc->irq_type[offset] != type) अणु
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
			bcm2835_gpio_irq_config(pc, offset, true);
		पूर्ण
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		अगर (pc->irq_type[offset] == IRQ_TYPE_EDGE_BOTH) अणु
			/* FALLING alपढ़ोy enabled, disable RISING */
			pc->irq_type[offset] = IRQ_TYPE_EDGE_RISING;
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
		पूर्ण अन्यथा अगर (pc->irq_type[offset] != type) अणु
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
			bcm2835_gpio_irq_config(pc, offset, true);
		पूर्ण
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		अगर (pc->irq_type[offset] == IRQ_TYPE_EDGE_RISING) अणु
			/* RISING alपढ़ोy enabled, enable FALLING too */
			pc->irq_type[offset] = IRQ_TYPE_EDGE_FALLING;
			bcm2835_gpio_irq_config(pc, offset, true);
			pc->irq_type[offset] = type;
		पूर्ण अन्यथा अगर (pc->irq_type[offset] == IRQ_TYPE_EDGE_FALLING) अणु
			/* FALLING alपढ़ोy enabled, enable RISING too */
			pc->irq_type[offset] = IRQ_TYPE_EDGE_RISING;
			bcm2835_gpio_irq_config(pc, offset, true);
			pc->irq_type[offset] = type;
		पूर्ण अन्यथा अगर (pc->irq_type[offset] != type) अणु
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
			bcm2835_gpio_irq_config(pc, offset, true);
		पूर्ण
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
	हाल IRQ_TYPE_LEVEL_LOW:
		अगर (pc->irq_type[offset] != type) अणु
			bcm2835_gpio_irq_config(pc, offset, false);
			pc->irq_type[offset] = type;
			bcm2835_gpio_irq_config(pc, offset, true);
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	अचिन्हित gpio = irqd_to_hwirq(data);
	अचिन्हित offset = GPIO_REG_SHIFT(gpio);
	अचिन्हित bank = GPIO_REG_OFFSET(gpio);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&pc->irq_lock[bank], flags);

	अगर (test_bit(offset, &pc->enabled_irq_map[bank]))
		ret = __bcm2835_gpio_irq_set_type_enabled(pc, gpio, type);
	अन्यथा
		ret = __bcm2835_gpio_irq_set_type_disabled(pc, gpio, type);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(data, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(data, handle_level_irq);

	raw_spin_unlock_irqrestore(&pc->irq_lock[bank], flags);

	वापस ret;
पूर्ण

अटल व्योम bcm2835_gpio_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	अचिन्हित gpio = irqd_to_hwirq(data);

	bcm2835_gpio_set_bit(pc, GPEDS0, gpio);
पूर्ण

अटल पूर्णांक bcm2835_gpio_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	अचिन्हित gpio = irqd_to_hwirq(data);
	अचिन्हित पूर्णांक irqgroup;
	पूर्णांक ret = -EINVAL;

	अगर (!pc->wake_irq)
		वापस ret;

	अगर (gpio <= 27)
		irqgroup = 0;
	अन्यथा अगर (gpio >= 28 && gpio <= 45)
		irqgroup = 1;
	अन्यथा अगर (gpio >= 46 && gpio <= 57)
		irqgroup = 2;
	अन्यथा
		वापस ret;

	अगर (on)
		ret = enable_irq_wake(pc->wake_irq[irqgroup]);
	अन्यथा
		ret = disable_irq_wake(pc->wake_irq[irqgroup]);

	वापस ret;
पूर्ण

अटल काष्ठा irq_chip bcm2835_gpio_irq_chip = अणु
	.name = MODULE_NAME,
	.irq_enable = bcm2835_gpio_irq_enable,
	.irq_disable = bcm2835_gpio_irq_disable,
	.irq_set_type = bcm2835_gpio_irq_set_type,
	.irq_ack = bcm2835_gpio_irq_ack,
	.irq_mask = bcm2835_gpio_irq_disable,
	.irq_unmask = bcm2835_gpio_irq_enable,
	.irq_set_wake = bcm2835_gpio_irq_set_wake,
	.flags = IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल पूर्णांक bcm2835_pctl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस BCM2835_NUM_GPIOS;
पूर्ण

अटल स्थिर अक्षर *bcm2835_pctl_get_group_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित selector)
अणु
	वापस bcm2835_gpio_groups[selector];
पूर्ण

अटल पूर्णांक bcm2835_pctl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित selector,
		स्थिर अचिन्हित **pins,
		अचिन्हित *num_pins)
अणु
	*pins = &bcm2835_gpio_pins[selector].number;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल व्योम bcm2835_pctl_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
		काष्ठा seq_file *s,
		अचिन्हित offset)
अणु
	काष्ठा bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा gpio_chip *chip = &pc->gpio_chip;
	क्रमागत bcm2835_fsel fsel = bcm2835_pinctrl_fsel_get(pc, offset);
	स्थिर अक्षर *fname = bcm2835_functions[fsel];
	पूर्णांक value = bcm2835_gpio_get_bit(pc, GPLEV0, offset);
	पूर्णांक irq = irq_find_mapping(chip->irq.करोमुख्य, offset);

	seq_म_लिखो(s, "function %s in %s; irq %d (%s)",
		fname, value ? "hi" : "lo",
		irq, irq_type_names[pc->irq_type[offset]]);
पूर्ण

अटल व्योम bcm2835_pctl_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map *maps, अचिन्हित num_maps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_maps; i++)
		अगर (maps[i].type == PIN_MAP_TYPE_CONFIGS_PIN)
			kमुक्त(maps[i].data.configs.configs);

	kमुक्त(maps);
पूर्ण

अटल पूर्णांक bcm2835_pctl_dt_node_to_map_func(काष्ठा bcm2835_pinctrl *pc,
		काष्ठा device_node *np, u32 pin, u32 fnum,
		काष्ठा pinctrl_map **maps)
अणु
	काष्ठा pinctrl_map *map = *maps;

	अगर (fnum >= ARRAY_SIZE(bcm2835_functions)) अणु
		dev_err(pc->dev, "%pOF: invalid brcm,function %d\n", np, fnum);
		वापस -EINVAL;
	पूर्ण

	map->type = PIN_MAP_TYPE_MUX_GROUP;
	map->data.mux.group = bcm2835_gpio_groups[pin];
	map->data.mux.function = bcm2835_functions[fnum];
	(*maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_pctl_dt_node_to_map_pull(काष्ठा bcm2835_pinctrl *pc,
		काष्ठा device_node *np, u32 pin, u32 pull,
		काष्ठा pinctrl_map **maps)
अणु
	काष्ठा pinctrl_map *map = *maps;
	अचिन्हित दीर्घ *configs;

	अगर (pull > 2) अणु
		dev_err(pc->dev, "%pOF: invalid brcm,pull %d\n", np, pull);
		वापस -EINVAL;
	पूर्ण

	configs = kzalloc(माप(*configs), GFP_KERNEL);
	अगर (!configs)
		वापस -ENOMEM;
	configs[0] = pinconf_to_config_packed(BCM2835_PINCONF_PARAM_PULL, pull);

	map->type = PIN_MAP_TYPE_CONFIGS_PIN;
	map->data.configs.group_or_pin = bcm2835_gpio_pins[pin].name;
	map->data.configs.configs = configs;
	map->data.configs.num_configs = 1;
	(*maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_pctl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा device_node *np,
		काष्ठा pinctrl_map **map, अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा property *pins, *funcs, *pulls;
	पूर्णांक num_pins, num_funcs, num_pulls, maps_per_pin;
	काष्ठा pinctrl_map *maps, *cur_map;
	पूर्णांक i, err;
	u32 pin, func, pull;

	/* Check क्रम generic binding in this node */
	err = pinconf_generic_dt_node_to_map_all(pctldev, np, map, num_maps);
	अगर (err || *num_maps)
		वापस err;

	/* Generic binding did not find anything जारी with legacy parse */
	pins = of_find_property(np, "brcm,pins", शून्य);
	अगर (!pins) अणु
		dev_err(pc->dev, "%pOF: missing brcm,pins property\n", np);
		वापस -EINVAL;
	पूर्ण

	funcs = of_find_property(np, "brcm,function", शून्य);
	pulls = of_find_property(np, "brcm,pull", शून्य);

	अगर (!funcs && !pulls) अणु
		dev_err(pc->dev,
			"%pOF: neither brcm,function nor brcm,pull specified\n",
			np);
		वापस -EINVAL;
	पूर्ण

	num_pins = pins->length / 4;
	num_funcs = funcs ? (funcs->length / 4) : 0;
	num_pulls = pulls ? (pulls->length / 4) : 0;

	अगर (num_funcs > 1 && num_funcs != num_pins) अणु
		dev_err(pc->dev,
			"%pOF: brcm,function must have 1 or %d entries\n",
			np, num_pins);
		वापस -EINVAL;
	पूर्ण

	अगर (num_pulls > 1 && num_pulls != num_pins) अणु
		dev_err(pc->dev,
			"%pOF: brcm,pull must have 1 or %d entries\n",
			np, num_pins);
		वापस -EINVAL;
	पूर्ण

	maps_per_pin = 0;
	अगर (num_funcs)
		maps_per_pin++;
	अगर (num_pulls)
		maps_per_pin++;
	cur_map = maps = kसुस्मृति(num_pins * maps_per_pin, माप(*maps),
				 GFP_KERNEL);
	अगर (!maps)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_pins; i++) अणु
		err = of_property_पढ़ो_u32_index(np, "brcm,pins", i, &pin);
		अगर (err)
			जाओ out;
		अगर (pin >= pc->pctl_desc.npins) अणु
			dev_err(pc->dev, "%pOF: invalid brcm,pins value %d\n",
				np, pin);
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (num_funcs) अणु
			err = of_property_पढ़ो_u32_index(np, "brcm,function",
					(num_funcs > 1) ? i : 0, &func);
			अगर (err)
				जाओ out;
			err = bcm2835_pctl_dt_node_to_map_func(pc, np, pin,
							func, &cur_map);
			अगर (err)
				जाओ out;
		पूर्ण
		अगर (num_pulls) अणु
			err = of_property_पढ़ो_u32_index(np, "brcm,pull",
					(num_pulls > 1) ? i : 0, &pull);
			अगर (err)
				जाओ out;
			err = bcm2835_pctl_dt_node_to_map_pull(pc, np, pin,
							pull, &cur_map);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

	*map = maps;
	*num_maps = num_pins * maps_per_pin;

	वापस 0;

out:
	bcm2835_pctl_dt_मुक्त_map(pctldev, maps, num_pins * maps_per_pin);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops bcm2835_pctl_ops = अणु
	.get_groups_count = bcm2835_pctl_get_groups_count,
	.get_group_name = bcm2835_pctl_get_group_name,
	.get_group_pins = bcm2835_pctl_get_group_pins,
	.pin_dbg_show = bcm2835_pctl_pin_dbg_show,
	.dt_node_to_map = bcm2835_pctl_dt_node_to_map,
	.dt_मुक्त_map = bcm2835_pctl_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक bcm2835_pmx_मुक्त(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित offset)
अणु
	काष्ठा bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);

	/* disable by setting to GPIO_IN */
	bcm2835_pinctrl_fsel_set(pc, offset, BCM2835_FSEL_GPIO_IN);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_pmx_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस BCM2835_FSEL_COUNT;
पूर्ण

अटल स्थिर अक्षर *bcm2835_pmx_get_function_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित selector)
अणु
	वापस bcm2835_functions[selector];
पूर्ण

अटल पूर्णांक bcm2835_pmx_get_function_groups(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित selector,
		स्थिर अक्षर * स्थिर **groups,
		अचिन्हित * स्थिर num_groups)
अणु
	/* every pin can करो every function */
	*groups = bcm2835_gpio_groups;
	*num_groups = BCM2835_NUM_GPIOS;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_pmx_set(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित func_selector,
		अचिन्हित group_selector)
अणु
	काष्ठा bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);

	bcm2835_pinctrl_fsel_set(pc, group_selector, func_selector);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_pmx_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range,
		अचिन्हित offset)
अणु
	काष्ठा bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);

	/* disable by setting to GPIO_IN */
	bcm2835_pinctrl_fsel_set(pc, offset, BCM2835_FSEL_GPIO_IN);
पूर्ण

अटल पूर्णांक bcm2835_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range,
		अचिन्हित offset,
		bool input)
अणु
	काष्ठा bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत bcm2835_fsel fsel = input ?
		BCM2835_FSEL_GPIO_IN : BCM2835_FSEL_GPIO_OUT;

	bcm2835_pinctrl_fsel_set(pc, offset, fsel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops bcm2835_pmx_ops = अणु
	.मुक्त = bcm2835_pmx_मुक्त,
	.get_functions_count = bcm2835_pmx_get_functions_count,
	.get_function_name = bcm2835_pmx_get_function_name,
	.get_function_groups = bcm2835_pmx_get_function_groups,
	.set_mux = bcm2835_pmx_set,
	.gpio_disable_मुक्त = bcm2835_pmx_gpio_disable_मुक्त,
	.gpio_set_direction = bcm2835_pmx_gpio_set_direction,
पूर्ण;

अटल पूर्णांक bcm2835_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित pin, अचिन्हित दीर्घ *config)
अणु
	/* No way to पढ़ो back config in HW */
	वापस -ENOTSUPP;
पूर्ण

अटल व्योम bcm2835_pull_config_set(काष्ठा bcm2835_pinctrl *pc,
		अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक arg)
अणु
	u32 off, bit;

	off = GPIO_REG_OFFSET(pin);
	bit = GPIO_REG_SHIFT(pin);

	bcm2835_gpio_wr(pc, GPPUD, arg & 3);
	/*
	 * BCM2835 datasheet say to रुको 150 cycles, but not of what.
	 * But the VideoCore firmware delay क्रम this operation
	 * based nearly on the same amount of VPU cycles and this घड़ी
	 * runs at 250 MHz.
	 */
	udelay(1);
	bcm2835_gpio_wr(pc, GPPUDCLK0 + (off * 4), BIT(bit));
	udelay(1);
	bcm2835_gpio_wr(pc, GPPUDCLK0 + (off * 4), 0);
पूर्ण

अटल पूर्णांक bcm2835_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
			अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	u32 param, arg;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		/* Set legacy brcm,pull */
		हाल BCM2835_PINCONF_PARAM_PULL:
			bcm2835_pull_config_set(pc, pin, arg);
			अवरोध;

		/* Set pull generic bindings */
		हाल PIN_CONFIG_BIAS_DISABLE:
			bcm2835_pull_config_set(pc, pin, BCM2835_PUD_OFF);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			bcm2835_pull_config_set(pc, pin, BCM2835_PUD_DOWN);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			bcm2835_pull_config_set(pc, pin, BCM2835_PUD_UP);
			अवरोध;

		/* Set output-high or output-low */
		हाल PIN_CONFIG_OUTPUT:
			bcm2835_gpio_set_bit(pc, arg ? GPSET0 : GPCLR0, pin);
			अवरोध;

		शेष:
			वापस -ENOTSUPP;

		पूर्ण /* चयन param type */
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops bcm2835_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = bcm2835_pinconf_get,
	.pin_config_set = bcm2835_pinconf_set,
पूर्ण;

अटल व्योम bcm2711_pull_config_set(काष्ठा bcm2835_pinctrl *pc,
				    अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक arg)
अणु
	u32 shअगरter;
	u32 value;
	u32 off;

	off = PUD_2711_REG_OFFSET(pin);
	shअगरter = PUD_2711_REG_SHIFT(pin);

	value = bcm2835_gpio_rd(pc, GP_GPIO_PUP_PDN_CNTRL_REG0 + (off * 4));
	value &= ~(PUD_2711_MASK << shअगरter);
	value |= (arg << shअगरter);
	bcm2835_gpio_wr(pc, GP_GPIO_PUP_PDN_CNTRL_REG0 + (off * 4), value);
पूर्ण

अटल पूर्णांक bcm2711_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
			       अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	u32 param, arg;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		/* convert legacy brcm,pull */
		हाल BCM2835_PINCONF_PARAM_PULL:
			अगर (arg == BCM2835_PUD_UP)
				arg = BCM2711_PULL_UP;
			अन्यथा अगर (arg == BCM2835_PUD_DOWN)
				arg = BCM2711_PULL_DOWN;
			अन्यथा
				arg = BCM2711_PULL_NONE;

			bcm2711_pull_config_set(pc, pin, arg);
			अवरोध;

		/* Set pull generic bindings */
		हाल PIN_CONFIG_BIAS_DISABLE:
			bcm2711_pull_config_set(pc, pin, BCM2711_PULL_NONE);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			bcm2711_pull_config_set(pc, pin, BCM2711_PULL_DOWN);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			bcm2711_pull_config_set(pc, pin, BCM2711_PULL_UP);
			अवरोध;

		/* Set output-high or output-low */
		हाल PIN_CONFIG_OUTPUT:
			bcm2835_gpio_set_bit(pc, arg ? GPSET0 : GPCLR0, pin);
			अवरोध;

		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops bcm2711_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = bcm2835_pinconf_get,
	.pin_config_set = bcm2711_pinconf_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc bcm2835_pinctrl_desc = अणु
	.name = MODULE_NAME,
	.pins = bcm2835_gpio_pins,
	.npins = BCM2835_NUM_GPIOS,
	.pctlops = &bcm2835_pctl_ops,
	.pmxops = &bcm2835_pmx_ops,
	.confops = &bcm2835_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc bcm2711_pinctrl_desc = अणु
	.name = "pinctrl-bcm2711",
	.pins = bcm2835_gpio_pins,
	.npins = BCM2711_NUM_GPIOS,
	.pctlops = &bcm2835_pctl_ops,
	.pmxops = &bcm2835_pmx_ops,
	.confops = &bcm2711_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_gpio_range bcm2835_pinctrl_gpio_range = अणु
	.name = MODULE_NAME,
	.npins = BCM2835_NUM_GPIOS,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_gpio_range bcm2711_pinctrl_gpio_range = अणु
	.name = "pinctrl-bcm2711",
	.npins = BCM2711_NUM_GPIOS,
पूर्ण;

काष्ठा bcm_plat_data अणु
	स्थिर काष्ठा gpio_chip *gpio_chip;
	स्थिर काष्ठा pinctrl_desc *pctl_desc;
	स्थिर काष्ठा pinctrl_gpio_range *gpio_range;
पूर्ण;

अटल स्थिर काष्ठा bcm_plat_data bcm2835_plat_data = अणु
	.gpio_chip = &bcm2835_gpio_chip,
	.pctl_desc = &bcm2835_pinctrl_desc,
	.gpio_range = &bcm2835_pinctrl_gpio_range,
पूर्ण;

अटल स्थिर काष्ठा bcm_plat_data bcm2711_plat_data = अणु
	.gpio_chip = &bcm2711_gpio_chip,
	.pctl_desc = &bcm2711_pinctrl_desc,
	.gpio_range = &bcm2711_pinctrl_gpio_range,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm2835_pinctrl_match[] = अणु
	अणु
		.compatible = "brcm,bcm2835-gpio",
		.data = &bcm2835_plat_data,
	पूर्ण,
	अणु
		.compatible = "brcm,bcm2711-gpio",
		.data = &bcm2711_plat_data,
	पूर्ण,
	अणु
		.compatible = "brcm,bcm7211-gpio",
		.data = &bcm2711_plat_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक bcm2835_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा bcm_plat_data *pdata;
	काष्ठा bcm2835_pinctrl *pc;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा resource iomem;
	पूर्णांक err, i;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक is_7211 = 0;

	BUILD_BUG_ON(ARRAY_SIZE(bcm2835_gpio_pins) != BCM2711_NUM_GPIOS);
	BUILD_BUG_ON(ARRAY_SIZE(bcm2835_gpio_groups) != BCM2711_NUM_GPIOS);

	pc = devm_kzalloc(dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pc);
	pc->dev = dev;

	err = of_address_to_resource(np, 0, &iomem);
	अगर (err) अणु
		dev_err(dev, "could not get IO memory\n");
		वापस err;
	पूर्ण

	pc->base = devm_ioremap_resource(dev, &iomem);
	अगर (IS_ERR(pc->base))
		वापस PTR_ERR(pc->base);

	match = of_match_node(bcm2835_pinctrl_match, pdev->dev.of_node);
	अगर (!match)
		वापस -EINVAL;

	pdata = match->data;
	is_7211 = of_device_is_compatible(np, "brcm,bcm7211-gpio");

	pc->gpio_chip = *pdata->gpio_chip;
	pc->gpio_chip.parent = dev;
	pc->gpio_chip.of_node = np;

	क्रम (i = 0; i < BCM2835_NUM_BANKS; i++) अणु
		अचिन्हित दीर्घ events;
		अचिन्हित offset;

		/* clear event detection flags */
		bcm2835_gpio_wr(pc, GPREN0 + i * 4, 0);
		bcm2835_gpio_wr(pc, GPFEN0 + i * 4, 0);
		bcm2835_gpio_wr(pc, GPHEN0 + i * 4, 0);
		bcm2835_gpio_wr(pc, GPLEN0 + i * 4, 0);
		bcm2835_gpio_wr(pc, GPAREN0 + i * 4, 0);
		bcm2835_gpio_wr(pc, GPAFEN0 + i * 4, 0);

		/* clear all the events */
		events = bcm2835_gpio_rd(pc, GPEDS0 + i * 4);
		क्रम_each_set_bit(offset, &events, 32)
			bcm2835_gpio_wr(pc, GPEDS0 + i * 4, BIT(offset));

		raw_spin_lock_init(&pc->irq_lock[i]);
	पूर्ण

	girq = &pc->gpio_chip.irq;
	girq->chip = &bcm2835_gpio_irq_chip;
	girq->parent_handler = bcm2835_gpio_irq_handler;
	girq->num_parents = BCM2835_NUM_IRQS;
	girq->parents = devm_kसुस्मृति(dev, BCM2835_NUM_IRQS,
				     माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;

	अगर (is_7211) अणु
		pc->wake_irq = devm_kसुस्मृति(dev, BCM2835_NUM_IRQS,
					    माप(*pc->wake_irq),
					    GFP_KERNEL);
		अगर (!pc->wake_irq)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * Use the same handler क्रम all groups: this is necessary
	 * since we use one gpiochip to cover all lines - the
	 * irq handler then needs to figure out which group and
	 * bank that was firing the IRQ and look up the per-group
	 * and bank data.
	 */
	क्रम (i = 0; i < BCM2835_NUM_IRQS; i++) अणु
		पूर्णांक len;
		अक्षर *name;

		girq->parents[i] = irq_of_parse_and_map(np, i);
		अगर (!is_7211)
			जारी;

		/* Skip over the all banks पूर्णांकerrupts */
		pc->wake_irq[i] = irq_of_parse_and_map(np, i +
						       BCM2835_NUM_IRQS + 1);

		len = म_माप(dev_name(pc->dev)) + 16;
		name = devm_kzalloc(pc->dev, len, GFP_KERNEL);
		अगर (!name)
			वापस -ENOMEM;

		snम_लिखो(name, len, "%s:bank%d", dev_name(pc->dev), i);

		/* These are optional पूर्णांकerrupts */
		err = devm_request_irq(dev, pc->wake_irq[i],
				       bcm2835_gpio_wake_irq_handler,
				       IRQF_SHARED, name, pc);
		अगर (err)
			dev_warn(dev, "unable to request wake IRQ %d\n",
				 pc->wake_irq[i]);
	पूर्ण

	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	err = gpiochip_add_data(&pc->gpio_chip, pc);
	अगर (err) अणु
		dev_err(dev, "could not add GPIO chip\n");
		वापस err;
	पूर्ण

	pc->pctl_desc = *pdata->pctl_desc;
	pc->pctl_dev = devm_pinctrl_रेजिस्टर(dev, &pc->pctl_desc, pc);
	अगर (IS_ERR(pc->pctl_dev)) अणु
		gpiochip_हटाओ(&pc->gpio_chip);
		वापस PTR_ERR(pc->pctl_dev);
	पूर्ण

	pc->gpio_range = *pdata->gpio_range;
	pc->gpio_range.base = pc->gpio_chip.base;
	pc->gpio_range.gc = &pc->gpio_chip;
	pinctrl_add_gpio_range(pc->pctl_dev, &pc->gpio_range);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm2835_pinctrl_driver = अणु
	.probe = bcm2835_pinctrl_probe,
	.driver = अणु
		.name = MODULE_NAME,
		.of_match_table = bcm2835_pinctrl_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(bcm2835_pinctrl_driver);
