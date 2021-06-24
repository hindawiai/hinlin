<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Aपंचांगel PIO4 controller
 *
 * Copyright (C) 2015 Aपंचांगel,
 *               2015 Luकरोvic Desroches <luकरोvic.desroches@aपंचांगel.com>
 */

#समावेश <dt-bindings/pinctrl/at91.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/slab.h>
#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

/*
 * Warning:
 * In order to not पूर्णांकroduce confusion between Aपंचांगel PIO groups and pinctrl
 * framework groups, Aपंचांगel PIO groups will be called banks, line is kept to
 * deचिन्हित the pin id पूर्णांकo this bank.
 */

#घोषणा ATMEL_PIO_MSKR		0x0000
#घोषणा ATMEL_PIO_CFGR		0x0004
#घोषणा		ATMEL_PIO_CFGR_FUNC_MASK	GENMASK(2, 0)
#घोषणा		ATMEL_PIO_सूची_MASK		BIT(8)
#घोषणा		ATMEL_PIO_PUEN_MASK		BIT(9)
#घोषणा		ATMEL_PIO_PDEN_MASK		BIT(10)
#घोषणा		ATMEL_PIO_SR_MASK		BIT(11)
#घोषणा		ATMEL_PIO_IFEN_MASK		BIT(12)
#घोषणा		ATMEL_PIO_IFSCEN_MASK		BIT(13)
#घोषणा		ATMEL_PIO_OPD_MASK		BIT(14)
#घोषणा		ATMEL_PIO_SCHMITT_MASK		BIT(15)
#घोषणा		ATMEL_PIO_DRVSTR_MASK		GENMASK(17, 16)
#घोषणा		ATMEL_PIO_DRVSTR_OFFSET		16
#घोषणा		ATMEL_PIO_CFGR_EVTSEL_MASK	GENMASK(26, 24)
#घोषणा		ATMEL_PIO_CFGR_EVTSEL_FALLING	(0 << 24)
#घोषणा		ATMEL_PIO_CFGR_EVTSEL_RISING	(1 << 24)
#घोषणा		ATMEL_PIO_CFGR_EVTSEL_BOTH	(2 << 24)
#घोषणा		ATMEL_PIO_CFGR_EVTSEL_LOW	(3 << 24)
#घोषणा		ATMEL_PIO_CFGR_EVTSEL_HIGH	(4 << 24)
#घोषणा ATMEL_PIO_PDSR		0x0008
#घोषणा ATMEL_PIO_LOCKSR	0x000C
#घोषणा ATMEL_PIO_SODR		0x0010
#घोषणा ATMEL_PIO_CODR		0x0014
#घोषणा ATMEL_PIO_ODSR		0x0018
#घोषणा ATMEL_PIO_IER		0x0020
#घोषणा ATMEL_PIO_IDR		0x0024
#घोषणा ATMEL_PIO_IMR		0x0028
#घोषणा ATMEL_PIO_ISR		0x002C
#घोषणा ATMEL_PIO_IOFR		0x003C

#घोषणा ATMEL_PIO_NPINS_PER_BANK	32
#घोषणा ATMEL_PIO_BANK(pin_id)		(pin_id / ATMEL_PIO_NPINS_PER_BANK)
#घोषणा ATMEL_PIO_LINE(pin_id)		(pin_id % ATMEL_PIO_NPINS_PER_BANK)
#घोषणा ATMEL_PIO_BANK_OFFSET		0x40

#घोषणा ATMEL_GET_PIN_NO(pinfunc)	((pinfunc) & 0xff)
#घोषणा ATMEL_GET_PIN_FUNC(pinfunc)	((pinfunc >> 16) & 0xf)
#घोषणा ATMEL_GET_PIN_IOSET(pinfunc)	((pinfunc >> 20) & 0xf)

/* Custom pinconf parameters */
#घोषणा ATMEL_PIN_CONFIG_DRIVE_STRENGTH	(PIN_CONFIG_END + 1)

/**
 * काष्ठा aपंचांगel_pioctrl_data - Aपंचांगel PIO controller (pinmux + gpio) data काष्ठा
 * @nbanks: number of PIO banks
 * @last_bank_count: number of lines in the last bank (can be less than
 *	the rest of the banks).
 * @slew_rate_support: slew rate support
 */
काष्ठा aपंचांगel_pioctrl_data अणु
	अचिन्हित पूर्णांक nbanks;
	अचिन्हित पूर्णांक last_bank_count;
	अचिन्हित पूर्णांक slew_rate_support;
पूर्ण;

काष्ठा aपंचांगel_group अणु
	स्थिर अक्षर *name;
	u32 pin;
पूर्ण;

काष्ठा aपंचांगel_pin अणु
	अचिन्हित पूर्णांक pin_id;
	अचिन्हित पूर्णांक mux;
	अचिन्हित पूर्णांक ioset;
	अचिन्हित पूर्णांक bank;
	अचिन्हित पूर्णांक line;
	स्थिर अक्षर *device;
पूर्ण;

/**
 * काष्ठा aपंचांगel_pioctrl - Aपंचांगel PIO controller (pinmux + gpio)
 * @reg_base: base address of the controller.
 * @clk: घड़ी of the controller.
 * @nbanks: number of PIO groups, it can vary depending on the SoC.
 * @pinctrl_dev: pinctrl device रेजिस्टरed.
 * @groups: groups table to provide group name and pin in the group to pinctrl.
 * @group_names: group names table to provide all the group/pin names to
 *     pinctrl or gpio.
 * @pins: pins table used क्रम both pinctrl and gpio. pin_id, bank and line
 *     fields are set at probe समय. Other ones are set when parsing dt
 *     pinctrl.
 * @npins: number of pins.
 * @gpio_chip: gpio chip रेजिस्टरed.
 * @irq_करोमुख्य: irq करोमुख्य क्रम the gpio controller.
 * @irqs: table containing the hw irq number of the bank. The index of the
 *     table is the bank id.
 * @pm_wakeup_sources: biपंचांगap of wakeup sources (lines)
 * @pm_suspend_backup: backup/restore रेजिस्टर values on suspend/resume
 * @dev: device entry क्रम the Aपंचांगel PIO controller.
 * @node: node of the Aपंचांगel PIO controller.
 * @slew_rate_support: slew rate support
 */
काष्ठा aपंचांगel_pioctrl अणु
	व्योम __iomem		*reg_base;
	काष्ठा clk		*clk;
	अचिन्हित पूर्णांक		nbanks;
	काष्ठा pinctrl_dev	*pinctrl_dev;
	काष्ठा aपंचांगel_group	*groups;
	स्थिर अक्षर * स्थिर	*group_names;
	काष्ठा aपंचांगel_pin	**pins;
	अचिन्हित पूर्णांक		npins;
	काष्ठा gpio_chip	*gpio_chip;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
	पूर्णांक			*irqs;
	अचिन्हित पूर्णांक		*pm_wakeup_sources;
	काष्ठा अणु
		u32		imr;
		u32		odsr;
		u32		cfgr[ATMEL_PIO_NPINS_PER_BANK];
	पूर्ण *pm_suspend_backup;
	काष्ठा device		*dev;
	काष्ठा device_node	*node;
	अचिन्हित पूर्णांक		slew_rate_support;
पूर्ण;

अटल स्थिर अक्षर * स्थिर aपंचांगel_functions[] = अणु
	"GPIO", "A", "B", "C", "D", "E", "F", "G"
पूर्ण;

अटल स्थिर काष्ठा pinconf_generic_params aपंचांगel_custom_bindings[] = अणु
	अणु"atmel,drive-strength", ATMEL_PIN_CONFIG_DRIVE_STRENGTH, 0पूर्ण,
पूर्ण;

/* --- GPIO --- */
अटल अचिन्हित पूर्णांक aपंचांगel_gpio_पढ़ो(काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl,
				    अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(aपंचांगel_pioctrl->reg_base
			     + ATMEL_PIO_BANK_OFFSET * bank + reg);
पूर्ण

अटल व्योम aपंचांगel_gpio_ग_लिखो(काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl,
			     अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl_relaxed(val, aपंचांगel_pioctrl->reg_base
		       + ATMEL_PIO_BANK_OFFSET * bank + reg);
पूर्ण

अटल व्योम aपंचांगel_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	/*
	 * Nothing to करो, पूर्णांकerrupt is cleared when पढ़ोing the status
	 * रेजिस्टर.
	 */
पूर्ण

अटल पूर्णांक aपंचांगel_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = irq_data_get_irq_chip_data(d);
	काष्ठा aपंचांगel_pin *pin = aपंचांगel_pioctrl->pins[d->hwirq];
	अचिन्हित पूर्णांक reg;

	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_MSKR,
			 BIT(pin->line));
	reg = aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_CFGR);
	reg &= (~ATMEL_PIO_CFGR_EVTSEL_MASK);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		irq_set_handler_locked(d, handle_edge_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_set_handler_locked(d, handle_edge_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		irq_set_handler_locked(d, handle_edge_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_BOTH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_set_handler_locked(d, handle_level_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_LOW;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_set_handler_locked(d, handle_level_irq);
		reg |= ATMEL_PIO_CFGR_EVTSEL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_NONE:
	शेष:
		वापस -EINVAL;
	पूर्ण

	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_CFGR, reg);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = irq_data_get_irq_chip_data(d);
	काष्ठा aपंचांगel_pin *pin = aपंचांगel_pioctrl->pins[d->hwirq];

	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_IDR,
			 BIT(pin->line));
पूर्ण

अटल व्योम aपंचांगel_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = irq_data_get_irq_chip_data(d);
	काष्ठा aपंचांगel_pin *pin = aपंचांगel_pioctrl->pins[d->hwirq];

	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_IER,
			 BIT(pin->line));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक aपंचांगel_gpio_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = irq_data_get_irq_chip_data(d);
	पूर्णांक bank = ATMEL_PIO_BANK(d->hwirq);
	पूर्णांक line = ATMEL_PIO_LINE(d->hwirq);

	/* The gpio controller has one पूर्णांकerrupt line per bank. */
	irq_set_irq_wake(aपंचांगel_pioctrl->irqs[bank], on);

	अगर (on)
		aपंचांगel_pioctrl->pm_wakeup_sources[bank] |= BIT(line);
	अन्यथा
		aपंचांगel_pioctrl->pm_wakeup_sources[bank] &= ~(BIT(line));

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा aपंचांगel_gpio_irq_set_wake शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा irq_chip aपंचांगel_gpio_irq_chip = अणु
	.name		= "GPIO",
	.irq_ack	= aपंचांगel_gpio_irq_ack,
	.irq_mask	= aपंचांगel_gpio_irq_mask,
	.irq_unmask	= aपंचांगel_gpio_irq_unmask,
	.irq_set_type	= aपंचांगel_gpio_irq_set_type,
	.irq_set_wake	= aपंचांगel_gpio_irq_set_wake,
पूर्ण;

अटल पूर्णांक aपंचांगel_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = gpiochip_get_data(chip);

	वापस irq_find_mapping(aपंचांगel_pioctrl->irq_करोमुख्य, offset);
पूर्ण

अटल व्योम aपंचांगel_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ isr;
	पूर्णांक n, bank = -1;

	/* Find from which bank is the irq received. */
	क्रम (n = 0; n < aपंचांगel_pioctrl->nbanks; n++) अणु
		अगर (aपंचांगel_pioctrl->irqs[n] == irq) अणु
			bank = n;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bank < 0) अणु
		dev_err(aपंचांगel_pioctrl->dev,
			"no bank associated to irq %u\n", irq);
		वापस;
	पूर्ण

	chained_irq_enter(chip, desc);

	क्रम (;;) अणु
		isr = (अचिन्हित दीर्घ)aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, bank,
						     ATMEL_PIO_ISR);
		isr &= (अचिन्हित दीर्घ)aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, bank,
						      ATMEL_PIO_IMR);
		अगर (!isr)
			अवरोध;

		क्रम_each_set_bit(n, &isr, BITS_PER_LONG)
			generic_handle_irq(aपंचांगel_gpio_to_irq(
					aपंचांगel_pioctrl->gpio_chip,
					bank * ATMEL_PIO_NPINS_PER_BANK + n));
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक aपंचांगel_gpio_direction_input(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = gpiochip_get_data(chip);
	काष्ठा aपंचांगel_pin *pin = aपंचांगel_pioctrl->pins[offset];
	अचिन्हित पूर्णांक reg;

	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_MSKR,
			 BIT(pin->line));
	reg = aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_CFGR);
	reg &= ~ATMEL_PIO_सूची_MASK;
	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_CFGR, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = gpiochip_get_data(chip);
	काष्ठा aपंचांगel_pin *pin = aपंचांगel_pioctrl->pins[offset];
	अचिन्हित पूर्णांक reg;

	reg = aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_PDSR);

	वापस !!(reg & BIT(pin->line));
पूर्ण

अटल पूर्णांक aपंचांगel_gpio_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				   अचिन्हित दीर्घ *bits)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank;

	biपंचांगap_zero(bits, aपंचांगel_pioctrl->npins);

	क्रम (bank = 0; bank < aपंचांगel_pioctrl->nbanks; bank++) अणु
		अचिन्हित पूर्णांक word = bank;
		अचिन्हित पूर्णांक offset = 0;
		अचिन्हित पूर्णांक reg;

#अगर ATMEL_PIO_NPINS_PER_BANK != BITS_PER_LONG
		word = BIT_WORD(bank * ATMEL_PIO_NPINS_PER_BANK);
		offset = bank * ATMEL_PIO_NPINS_PER_BANK % BITS_PER_LONG;
#पूर्ण_अगर
		अगर (!mask[word])
			जारी;

		reg = aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, bank, ATMEL_PIO_PDSR);
		bits[word] |= mask[word] & (reg << offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_gpio_direction_output(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset,
				       पूर्णांक value)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = gpiochip_get_data(chip);
	काष्ठा aपंचांगel_pin *pin = aपंचांगel_pioctrl->pins[offset];
	अचिन्हित पूर्णांक reg;

	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank,
			 value ? ATMEL_PIO_SODR : ATMEL_PIO_CODR,
			 BIT(pin->line));

	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_MSKR,
			 BIT(pin->line));
	reg = aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_CFGR);
	reg |= ATMEL_PIO_सूची_MASK;
	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank, ATMEL_PIO_CFGR, reg);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = gpiochip_get_data(chip);
	काष्ठा aपंचांगel_pin *pin = aपंचांगel_pioctrl->pins[offset];

	aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, pin->bank,
			 val ? ATMEL_PIO_SODR : ATMEL_PIO_CODR,
			 BIT(pin->line));
पूर्ण

अटल व्योम aपंचांगel_gpio_set_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				    अचिन्हित दीर्घ *bits)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank;

	क्रम (bank = 0; bank < aपंचांगel_pioctrl->nbanks; bank++) अणु
		अचिन्हित पूर्णांक biपंचांगask;
		अचिन्हित पूर्णांक word = bank;

/*
 * On a 64-bit platक्रमm, BITS_PER_LONG is 64 so it is necessary to iterate over
 * two 32bit words to handle the whole  biपंचांगask
 */
#अगर ATMEL_PIO_NPINS_PER_BANK != BITS_PER_LONG
		word = BIT_WORD(bank * ATMEL_PIO_NPINS_PER_BANK);
#पूर्ण_अगर
		अगर (!mask[word])
			जारी;

		biपंचांगask = mask[word] & bits[word];
		aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, bank, ATMEL_PIO_SODR, biपंचांगask);

		biपंचांगask = mask[word] & ~bits[word];
		aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, bank, ATMEL_PIO_CODR, biपंचांगask);

#अगर ATMEL_PIO_NPINS_PER_BANK != BITS_PER_LONG
		mask[word] >>= ATMEL_PIO_NPINS_PER_BANK;
		bits[word] >>= ATMEL_PIO_NPINS_PER_BANK;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल काष्ठा gpio_chip aपंचांगel_gpio_chip = अणु
	.direction_input        = aपंचांगel_gpio_direction_input,
	.get                    = aपंचांगel_gpio_get,
	.get_multiple           = aपंचांगel_gpio_get_multiple,
	.direction_output       = aपंचांगel_gpio_direction_output,
	.set                    = aपंचांगel_gpio_set,
	.set_multiple           = aपंचांगel_gpio_set_multiple,
	.to_irq                 = aपंचांगel_gpio_to_irq,
	.base                   = 0,
पूर्ण;

/* --- PINCTRL --- */
अटल अचिन्हित पूर्णांक aपंचांगel_pin_config_पढ़ो(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित पूर्णांक pin_id)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक bank = aपंचांगel_pioctrl->pins[pin_id]->bank;
	अचिन्हित पूर्णांक line = aपंचांगel_pioctrl->pins[pin_id]->line;
	व्योम __iomem *addr = aपंचांगel_pioctrl->reg_base
			     + bank * ATMEL_PIO_BANK_OFFSET;

	ग_लिखोl_relaxed(BIT(line), addr + ATMEL_PIO_MSKR);
	/* Have to set MSKR first, to access the right pin CFGR. */
	wmb();

	वापस पढ़ोl_relaxed(addr + ATMEL_PIO_CFGR);
पूर्ण

अटल व्योम aपंचांगel_pin_config_ग_लिखो(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक pin_id, u32 conf)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक bank = aपंचांगel_pioctrl->pins[pin_id]->bank;
	अचिन्हित पूर्णांक line = aपंचांगel_pioctrl->pins[pin_id]->line;
	व्योम __iomem *addr = aपंचांगel_pioctrl->reg_base
			     + bank * ATMEL_PIO_BANK_OFFSET;

	ग_लिखोl_relaxed(BIT(line), addr + ATMEL_PIO_MSKR);
	/* Have to set MSKR first, to access the right pin CFGR. */
	wmb();
	ग_लिखोl_relaxed(conf, addr + ATMEL_PIO_CFGR);
पूर्ण

अटल पूर्णांक aपंचांगel_pctl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस aपंचांगel_pioctrl->npins;
पूर्ण

अटल स्थिर अक्षर *aपंचांगel_pctl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित पूर्णांक selector)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस aपंचांगel_pioctrl->groups[selector].name;
पूर्ण

अटल पूर्णांक aपंचांगel_pctl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक selector,
				     स्थिर अचिन्हित पूर्णांक **pins,
				     अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = (अचिन्हित पूर्णांक *)&aपंचांगel_pioctrl->groups[selector].pin;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल काष्ठा aपंचांगel_group *
aपंचांगel_pctl_find_group_by_pin(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक i;

	क्रम (i = 0; i < aपंचांगel_pioctrl->npins; i++) अणु
		काष्ठा aपंचांगel_group *grp = aपंचांगel_pioctrl->groups + i;

		अगर (grp->pin == pin)
			वापस grp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक aपंचांगel_pctl_xlate_pinfunc(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा device_node *np,
				    u32 pinfunc, स्थिर अक्षर **grp_name,
				    स्थिर अक्षर **func_name)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक pin_id, func_id;
	काष्ठा aपंचांगel_group *grp;

	pin_id = ATMEL_GET_PIN_NO(pinfunc);
	func_id = ATMEL_GET_PIN_FUNC(pinfunc);

	अगर (func_id >= ARRAY_SIZE(aपंचांगel_functions))
		वापस -EINVAL;

	*func_name = aपंचांगel_functions[func_id];

	grp = aपंचांगel_pctl_find_group_by_pin(pctldev, pin_id);
	अगर (!grp)
		वापस -EINVAL;
	*grp_name = grp->name;

	aपंचांगel_pioctrl->pins[pin_id]->mux = func_id;
	aपंचांगel_pioctrl->pins[pin_id]->ioset = ATMEL_GET_PIN_IOSET(pinfunc);
	/* Want the device name not the group one. */
	अगर (np->parent == aपंचांगel_pioctrl->node)
		aपंचांगel_pioctrl->pins[pin_id]->device = np->name;
	अन्यथा
		aपंचांगel_pioctrl->pins[pin_id]->device = np->parent->name;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_pctl_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
					काष्ठा device_node *np,
					काष्ठा pinctrl_map **map,
					अचिन्हित पूर्णांक *reserved_maps,
					अचिन्हित पूर्णांक *num_maps)
अणु
	अचिन्हित पूर्णांक num_pins, num_configs, reserve;
	अचिन्हित दीर्घ *configs;
	काष्ठा property	*pins;
	u32 pinfunc;
	पूर्णांक ret, i;

	pins = of_find_property(np, "pinmux", शून्य);
	अगर (!pins)
		वापस -EINVAL;

	ret = pinconf_generic_parse_dt_config(np, pctldev, &configs,
					      &num_configs);
	अगर (ret < 0) अणु
		dev_err(pctldev->dev, "%pOF: could not parse node property\n",
			np);
		वापस ret;
	पूर्ण

	num_pins = pins->length / माप(u32);
	अगर (!num_pins) अणु
		dev_err(pctldev->dev, "no pins found in node %pOF\n", np);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	/*
	 * Reserve maps, at least there is a mux map and an optional conf
	 * map क्रम each pin.
	 */
	reserve = 1;
	अगर (num_configs)
		reserve++;
	reserve *= num_pins;
	ret = pinctrl_utils_reserve_map(pctldev, map, reserved_maps, num_maps,
					reserve);
	अगर (ret < 0)
		जाओ निकास;

	क्रम (i = 0; i < num_pins; i++) अणु
		स्थिर अक्षर *group, *func;

		ret = of_property_पढ़ो_u32_index(np, "pinmux", i, &pinfunc);
		अगर (ret)
			जाओ निकास;

		ret = aपंचांगel_pctl_xlate_pinfunc(pctldev, np, pinfunc, &group,
					       &func);
		अगर (ret)
			जाओ निकास;

		pinctrl_utils_add_map_mux(pctldev, map, reserved_maps, num_maps,
					  group, func);

		अगर (num_configs) अणु
			ret = pinctrl_utils_add_map_configs(pctldev, map,
					reserved_maps, num_maps, group,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GROUP);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	kमुक्त(configs);
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_pctl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा device_node *np_config,
				     काष्ठा pinctrl_map **map,
				     अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक reserved_maps;
	पूर्णांक ret;

	*map = शून्य;
	*num_maps = 0;
	reserved_maps = 0;

	/*
	 * If all the pins of a device have the same configuration (or no one),
	 * it is useless to add a subnode, so directly parse node referenced by
	 * phandle.
	 */
	ret = aपंचांगel_pctl_dt_subnode_to_map(pctldev, np_config, map,
					   &reserved_maps, num_maps);
	अगर (ret) अणु
		क्रम_each_child_of_node(np_config, np) अणु
			ret = aपंचांगel_pctl_dt_subnode_to_map(pctldev, np, map,
						    &reserved_maps, num_maps);
			अगर (ret < 0) अणु
				of_node_put(np);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ret < 0) अणु
		pinctrl_utils_मुक्त_map(pctldev, *map, *num_maps);
		dev_err(pctldev->dev, "can't create maps for node %pOF\n",
			np_config);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops aपंचांगel_pctlops = अणु
	.get_groups_count	= aपंचांगel_pctl_get_groups_count,
	.get_group_name		= aपंचांगel_pctl_get_group_name,
	.get_group_pins		= aपंचांगel_pctl_get_group_pins,
	.dt_node_to_map		= aपंचांगel_pctl_dt_node_to_map,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक aपंचांगel_pmx_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(aपंचांगel_functions);
पूर्ण

अटल स्थिर अक्षर *aपंचांगel_pmx_get_function_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित पूर्णांक selector)
अणु
	वापस aपंचांगel_functions[selector];
पूर्ण

अटल पूर्णांक aपंचांगel_pmx_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित पूर्णांक selector,
					 स्थिर अक्षर * स्थिर **groups,
					 अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = aपंचांगel_pioctrl->group_names;
	*num_groups = aपंचांगel_pioctrl->npins;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित पूर्णांक function,
			     अचिन्हित पूर्णांक group)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक pin;
	u32 conf;

	dev_dbg(pctldev->dev, "enable function %s group %s\n",
		aपंचांगel_functions[function], aपंचांगel_pioctrl->groups[group].name);

	pin = aपंचांगel_pioctrl->groups[group].pin;
	conf = aपंचांगel_pin_config_पढ़ो(pctldev, pin);
	conf &= (~ATMEL_PIO_CFGR_FUNC_MASK);
	conf |= (function & ATMEL_PIO_CFGR_FUNC_MASK);
	dev_dbg(pctldev->dev, "pin: %u, conf: 0x%08x\n", pin, conf);
	aपंचांगel_pin_config_ग_लिखो(pctldev, pin, conf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops aपंचांगel_pmxops = अणु
	.get_functions_count	= aपंचांगel_pmx_get_functions_count,
	.get_function_name	= aपंचांगel_pmx_get_function_name,
	.get_function_groups	= aपंचांगel_pmx_get_function_groups,
	.set_mux		= aपंचांगel_pmx_set_mux,
पूर्ण;

अटल पूर्णांक aपंचांगel_conf_pin_config_group_get(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक group,
					   अचिन्हित दीर्घ *config)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config), arg = 0;
	काष्ठा aपंचांगel_group *grp = aपंचांगel_pioctrl->groups + group;
	अचिन्हित पूर्णांक pin_id = grp->pin;
	u32 res;

	res = aपंचांगel_pin_config_पढ़ो(pctldev, pin_id);

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (!(res & ATMEL_PIO_PUEN_MASK))
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर ((res & ATMEL_PIO_PUEN_MASK) ||
		    (!(res & ATMEL_PIO_PDEN_MASK)))
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर ((res & ATMEL_PIO_PUEN_MASK) ||
		    ((res & ATMEL_PIO_PDEN_MASK)))
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (!(res & ATMEL_PIO_OPD_MASK))
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (!(res & ATMEL_PIO_SCHMITT_MASK))
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		अगर (!aपंचांगel_pioctrl->slew_rate_support)
			वापस -EOPNOTSUPP;
		अगर (!(res & ATMEL_PIO_SR_MASK))
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल ATMEL_PIN_CONFIG_DRIVE_STRENGTH:
		अगर (!(res & ATMEL_PIO_DRVSTR_MASK))
			वापस -EINVAL;
		arg = (res & ATMEL_PIO_DRVSTR_MASK) >> ATMEL_PIO_DRVSTR_OFFSET;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_conf_pin_config_group_set(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक group,
					   अचिन्हित दीर्घ *configs,
					   अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा aपंचांगel_group *grp = aपंचांगel_pioctrl->groups + group;
	अचिन्हित पूर्णांक bank, pin, pin_id = grp->pin;
	u32 mask, conf = 0;
	पूर्णांक i;

	conf = aपंचांगel_pin_config_पढ़ो(pctldev, pin_id);

	/* Keep slew rate enabled by शेष. */
	अगर (aपंचांगel_pioctrl->slew_rate_support)
		conf |= ATMEL_PIO_SR_MASK;

	क्रम (i = 0; i < num_configs; i++) अणु
		अचिन्हित पूर्णांक param = pinconf_to_config_param(configs[i]);
		अचिन्हित पूर्णांक arg = pinconf_to_config_argument(configs[i]);

		dev_dbg(pctldev->dev, "%s: pin=%u, config=0x%lx\n",
			__func__, pin_id, configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			conf &= (~ATMEL_PIO_PUEN_MASK);
			conf &= (~ATMEL_PIO_PDEN_MASK);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			conf |= ATMEL_PIO_PUEN_MASK;
			conf &= (~ATMEL_PIO_PDEN_MASK);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			conf |= ATMEL_PIO_PDEN_MASK;
			conf &= (~ATMEL_PIO_PUEN_MASK);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			अगर (arg == 0)
				conf &= (~ATMEL_PIO_OPD_MASK);
			अन्यथा
				conf |= ATMEL_PIO_OPD_MASK;
			अवरोध;
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			अगर (arg == 0)
				conf |= ATMEL_PIO_SCHMITT_MASK;
			अन्यथा
				conf &= (~ATMEL_PIO_SCHMITT_MASK);
			अवरोध;
		हाल PIN_CONFIG_INPUT_DEBOUNCE:
			अगर (arg == 0) अणु
				conf &= (~ATMEL_PIO_IFEN_MASK);
				conf &= (~ATMEL_PIO_IFSCEN_MASK);
			पूर्ण अन्यथा अणु
				/*
				 * We करोn't care about the debounce value क्रम several reasons:
				 * - can't have dअगरferent debounce periods inside a same group,
				 * - the रेजिस्टर to configure this period is a secure रेजिस्टर.
				 * The debouncing filter can filter a pulse with a duration of less
				 * than 1/2 slow घड़ी period.
				 */
				conf |= ATMEL_PIO_IFEN_MASK;
				conf |= ATMEL_PIO_IFSCEN_MASK;
			पूर्ण
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			conf |= ATMEL_PIO_सूची_MASK;
			bank = ATMEL_PIO_BANK(pin_id);
			pin = ATMEL_PIO_LINE(pin_id);
			mask = 1 << pin;

			अगर (arg == 0) अणु
				ग_लिखोl_relaxed(mask, aपंचांगel_pioctrl->reg_base +
					bank * ATMEL_PIO_BANK_OFFSET +
					ATMEL_PIO_CODR);
			पूर्ण अन्यथा अणु
				ग_लिखोl_relaxed(mask, aपंचांगel_pioctrl->reg_base +
					bank * ATMEL_PIO_BANK_OFFSET +
					ATMEL_PIO_SODR);
			पूर्ण
			अवरोध;
		हाल PIN_CONFIG_SLEW_RATE:
			अगर (!aपंचांगel_pioctrl->slew_rate_support)
				अवरोध;
			/* And हटाओ it अगर explicitly requested. */
			अगर (arg == 0)
				conf &= ~ATMEL_PIO_SR_MASK;
			अवरोध;
		हाल ATMEL_PIN_CONFIG_DRIVE_STRENGTH:
			चयन (arg) अणु
			हाल ATMEL_PIO_DRVSTR_LO:
			हाल ATMEL_PIO_DRVSTR_ME:
			हाल ATMEL_PIO_DRVSTR_HI:
				conf &= (~ATMEL_PIO_DRVSTR_MASK);
				conf |= arg << ATMEL_PIO_DRVSTR_OFFSET;
				अवरोध;
			शेष:
				dev_warn(pctldev->dev, "drive strength not updated (incorrect value)\n");
			पूर्ण
			अवरोध;
		शेष:
			dev_warn(pctldev->dev,
				 "unsupported configuration parameter: %u\n",
				 param);
			जारी;
		पूर्ण
	पूर्ण

	dev_dbg(pctldev->dev, "%s: reg=0x%08x\n", __func__, conf);
	aपंचांगel_pin_config_ग_लिखो(pctldev, pin_id, conf);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_conf_pin_config_dbg_show(काष्ठा pinctrl_dev *pctldev,
					   काष्ठा seq_file *s,
					   अचिन्हित पूर्णांक pin_id)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	u32 conf;

	अगर (!aपंचांगel_pioctrl->pins[pin_id]->device)
		वापस;

	अगर (aपंचांगel_pioctrl->pins[pin_id])
		seq_म_लिखो(s, " (%s, ioset %u) ",
			   aपंचांगel_pioctrl->pins[pin_id]->device,
			   aपंचांगel_pioctrl->pins[pin_id]->ioset);

	conf = aपंचांगel_pin_config_पढ़ो(pctldev, pin_id);
	अगर (conf & ATMEL_PIO_PUEN_MASK)
		seq_म_लिखो(s, "%s ", "pull-up");
	अगर (conf & ATMEL_PIO_PDEN_MASK)
		seq_म_लिखो(s, "%s ", "pull-down");
	अगर (conf & ATMEL_PIO_IFEN_MASK)
		seq_म_लिखो(s, "%s ", "debounce");
	अगर (conf & ATMEL_PIO_OPD_MASK)
		seq_म_लिखो(s, "%s ", "open-drain");
	अगर (conf & ATMEL_PIO_SCHMITT_MASK)
		seq_म_लिखो(s, "%s ", "schmitt");
	अगर (aपंचांगel_pioctrl->slew_rate_support && (conf & ATMEL_PIO_SR_MASK))
		seq_म_लिखो(s, "%s ", "slew-rate");
	अगर (conf & ATMEL_PIO_DRVSTR_MASK) अणु
		चयन ((conf & ATMEL_PIO_DRVSTR_MASK) >> ATMEL_PIO_DRVSTR_OFFSET) अणु
		हाल ATMEL_PIO_DRVSTR_ME:
			seq_म_लिखो(s, "%s ", "medium-drive");
			अवरोध;
		हाल ATMEL_PIO_DRVSTR_HI:
			seq_म_लिखो(s, "%s ", "high-drive");
			अवरोध;
		/* ATMEL_PIO_DRVSTR_LO and 0 which is the शेष value at reset */
		शेष:
			seq_म_लिखो(s, "%s ", "low-drive");
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops aपंचांगel_confops = अणु
	.pin_config_group_get	= aपंचांगel_conf_pin_config_group_get,
	.pin_config_group_set	= aपंचांगel_conf_pin_config_group_set,
	.pin_config_dbg_show	= aपंचांगel_conf_pin_config_dbg_show,
पूर्ण;

अटल काष्ठा pinctrl_desc aपंचांगel_pinctrl_desc = अणु
	.name		= "atmel_pinctrl",
	.confops	= &aपंचांगel_confops,
	.pctlops	= &aपंचांगel_pctlops,
	.pmxops		= &aपंचांगel_pmxops,
पूर्ण;

अटल पूर्णांक __maybe_unused aपंचांगel_pctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = dev_get_drvdata(dev);
	पूर्णांक i, j;

	/*
	 * For each bank, save IMR to restore it later and disable all GPIO
	 * पूर्णांकerrupts excepting the ones marked as wakeup sources.
	 */
	क्रम (i = 0; i < aपंचांगel_pioctrl->nbanks; i++) अणु
		aपंचांगel_pioctrl->pm_suspend_backup[i].imr =
			aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, i, ATMEL_PIO_IMR);
		aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, i, ATMEL_PIO_IDR,
				 ~aपंचांगel_pioctrl->pm_wakeup_sources[i]);
		aपंचांगel_pioctrl->pm_suspend_backup[i].odsr =
			aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, i, ATMEL_PIO_ODSR);
		क्रम (j = 0; j < ATMEL_PIO_NPINS_PER_BANK; j++) अणु
			aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, i,
					 ATMEL_PIO_MSKR, BIT(j));
			aपंचांगel_pioctrl->pm_suspend_backup[i].cfgr[j] =
				aपंचांगel_gpio_पढ़ो(aपंचांगel_pioctrl, i,
						ATMEL_PIO_CFGR);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused aपंचांगel_pctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl = dev_get_drvdata(dev);
	पूर्णांक i, j;

	क्रम (i = 0; i < aपंचांगel_pioctrl->nbanks; i++) अणु
		aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, i, ATMEL_PIO_IER,
				 aपंचांगel_pioctrl->pm_suspend_backup[i].imr);
		aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, i, ATMEL_PIO_SODR,
				 aपंचांगel_pioctrl->pm_suspend_backup[i].odsr);
		क्रम (j = 0; j < ATMEL_PIO_NPINS_PER_BANK; j++) अणु
			aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, i,
					 ATMEL_PIO_MSKR, BIT(j));
			aपंचांगel_gpio_ग_लिखो(aपंचांगel_pioctrl, i, ATMEL_PIO_CFGR,
					 aपंचांगel_pioctrl->pm_suspend_backup[i].cfgr[j]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops aपंचांगel_pctrl_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(aपंचांगel_pctrl_suspend, aपंचांगel_pctrl_resume)
पूर्ण;

/*
 * The number of banks can be dअगरferent from a SoC to another one.
 * We can have up to 16 banks.
 */
अटल स्थिर काष्ठा aपंचांगel_pioctrl_data aपंचांगel_sama5d2_pioctrl_data = अणु
	.nbanks			= 4,
	.last_bank_count	= ATMEL_PIO_NPINS_PER_BANK,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_pioctrl_data microchip_sama7g5_pioctrl_data = अणु
	.nbanks			= 5,
	.last_bank_count	= 8, /* sama7g5 has only PE0 to PE7 */
	.slew_rate_support	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_pctrl_of_match[] = अणु
	अणु
		.compatible = "atmel,sama5d2-pinctrl",
		.data = &aपंचांगel_sama5d2_pioctrl_data,
	पूर्ण, अणु
		.compatible = "microchip,sama7g5-pinctrl",
		.data = &microchip_sama7g5_pioctrl_data,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक aपंचांगel_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pinctrl_pin_desc	*pin_desc;
	स्थिर अक्षर **group_names;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक i, ret;
	काष्ठा resource	*res;
	काष्ठा aपंचांगel_pioctrl *aपंचांगel_pioctrl;
	स्थिर काष्ठा aपंचांगel_pioctrl_data *aपंचांगel_pioctrl_data;

	aपंचांगel_pioctrl = devm_kzalloc(dev, माप(*aपंचांगel_pioctrl), GFP_KERNEL);
	अगर (!aपंचांगel_pioctrl)
		वापस -ENOMEM;
	aपंचांगel_pioctrl->dev = dev;
	aपंचांगel_pioctrl->node = dev->of_node;
	platक्रमm_set_drvdata(pdev, aपंचांगel_pioctrl);

	match = of_match_node(aपंचांगel_pctrl_of_match, dev->of_node);
	अगर (!match) अणु
		dev_err(dev, "unknown compatible string\n");
		वापस -ENODEV;
	पूर्ण
	aपंचांगel_pioctrl_data = match->data;
	aपंचांगel_pioctrl->nbanks = aपंचांगel_pioctrl_data->nbanks;
	aपंचांगel_pioctrl->npins = aपंचांगel_pioctrl->nbanks * ATMEL_PIO_NPINS_PER_BANK;
	/* अगर last bank has limited number of pins, adjust accordingly */
	अगर (aपंचांगel_pioctrl_data->last_bank_count != ATMEL_PIO_NPINS_PER_BANK) अणु
		aपंचांगel_pioctrl->npins -= ATMEL_PIO_NPINS_PER_BANK;
		aपंचांगel_pioctrl->npins += aपंचांगel_pioctrl_data->last_bank_count;
	पूर्ण
	aपंचांगel_pioctrl->slew_rate_support = aपंचांगel_pioctrl_data->slew_rate_support;

	aपंचांगel_pioctrl->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(aपंचांगel_pioctrl->reg_base))
		वापस PTR_ERR(aपंचांगel_pioctrl->reg_base);

	aपंचांगel_pioctrl->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(aपंचांगel_pioctrl->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(aपंचांगel_pioctrl->clk);
	पूर्ण

	aपंचांगel_pioctrl->pins = devm_kसुस्मृति(dev,
					   aपंचांगel_pioctrl->npins,
					   माप(*aपंचांगel_pioctrl->pins),
					   GFP_KERNEL);
	अगर (!aपंचांगel_pioctrl->pins)
		वापस -ENOMEM;

	pin_desc = devm_kसुस्मृति(dev, aपंचांगel_pioctrl->npins, माप(*pin_desc),
				GFP_KERNEL);
	अगर (!pin_desc)
		वापस -ENOMEM;
	aपंचांगel_pinctrl_desc.pins = pin_desc;
	aपंचांगel_pinctrl_desc.npins = aपंचांगel_pioctrl->npins;
	aपंचांगel_pinctrl_desc.num_custom_params = ARRAY_SIZE(aपंचांगel_custom_bindings);
	aपंचांगel_pinctrl_desc.custom_params = aपंचांगel_custom_bindings;

	/* One pin is one group since a pin can achieve all functions. */
	group_names = devm_kसुस्मृति(dev,
				   aपंचांगel_pioctrl->npins, माप(*group_names),
				   GFP_KERNEL);
	अगर (!group_names)
		वापस -ENOMEM;
	aपंचांगel_pioctrl->group_names = group_names;

	aपंचांगel_pioctrl->groups = devm_kसुस्मृति(&pdev->dev,
			aपंचांगel_pioctrl->npins, माप(*aपंचांगel_pioctrl->groups),
			GFP_KERNEL);
	अगर (!aपंचांगel_pioctrl->groups)
		वापस -ENOMEM;
	क्रम (i = 0 ; i < aपंचांगel_pioctrl->npins; i++) अणु
		काष्ठा aपंचांगel_group *group = aपंचांगel_pioctrl->groups + i;
		अचिन्हित पूर्णांक bank = ATMEL_PIO_BANK(i);
		अचिन्हित पूर्णांक line = ATMEL_PIO_LINE(i);

		aपंचांगel_pioctrl->pins[i] = devm_kzalloc(dev,
				माप(**aपंचांगel_pioctrl->pins), GFP_KERNEL);
		अगर (!aपंचांगel_pioctrl->pins[i])
			वापस -ENOMEM;

		aपंचांगel_pioctrl->pins[i]->pin_id = i;
		aपंचांगel_pioctrl->pins[i]->bank = bank;
		aपंचांगel_pioctrl->pins[i]->line = line;

		pin_desc[i].number = i;
		/* Pin naming convention: P(bank_name)(bank_pin_number). */
		pin_desc[i].name = kaप्र_लिखो(GFP_KERNEL, "P%c%d",
					     bank + 'A', line);

		group->name = group_names[i] = pin_desc[i].name;
		group->pin = pin_desc[i].number;

		dev_dbg(dev, "pin_id=%u, bank=%u, line=%u", i, bank, line);
	पूर्ण

	aपंचांगel_pioctrl->gpio_chip = &aपंचांगel_gpio_chip;
	aपंचांगel_pioctrl->gpio_chip->of_node = dev->of_node;
	aपंचांगel_pioctrl->gpio_chip->ngpio = aपंचांगel_pioctrl->npins;
	aपंचांगel_pioctrl->gpio_chip->label = dev_name(dev);
	aपंचांगel_pioctrl->gpio_chip->parent = dev;
	aपंचांगel_pioctrl->gpio_chip->names = aपंचांगel_pioctrl->group_names;

	aपंचांगel_pioctrl->pm_wakeup_sources = devm_kसुस्मृति(dev,
			aपंचांगel_pioctrl->nbanks,
			माप(*aपंचांगel_pioctrl->pm_wakeup_sources),
			GFP_KERNEL);
	अगर (!aपंचांगel_pioctrl->pm_wakeup_sources)
		वापस -ENOMEM;

	aपंचांगel_pioctrl->pm_suspend_backup = devm_kसुस्मृति(dev,
			aपंचांगel_pioctrl->nbanks,
			माप(*aपंचांगel_pioctrl->pm_suspend_backup),
			GFP_KERNEL);
	अगर (!aपंचांगel_pioctrl->pm_suspend_backup)
		वापस -ENOMEM;

	aपंचांगel_pioctrl->irqs = devm_kसुस्मृति(dev,
					   aपंचांगel_pioctrl->nbanks,
					   माप(*aपंचांगel_pioctrl->irqs),
					   GFP_KERNEL);
	अगर (!aपंचांगel_pioctrl->irqs)
		वापस -ENOMEM;

	/* There is one controller but each bank has its own irq line. */
	क्रम (i = 0; i < aपंचांगel_pioctrl->nbanks; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, i);
		अगर (!res) अणु
			dev_err(dev, "missing irq resource for group %c\n",
				'A' + i);
			वापस -EINVAL;
		पूर्ण
		aपंचांगel_pioctrl->irqs[i] = res->start;
		irq_set_chained_handler_and_data(res->start,
			aपंचांगel_gpio_irq_handler, aपंचांगel_pioctrl);
		dev_dbg(dev, "bank %i: irq=%pr\n", i, res);
	पूर्ण

	aपंचांगel_pioctrl->irq_करोमुख्य = irq_करोमुख्य_add_linear(dev->of_node,
			aपंचांगel_pioctrl->gpio_chip->ngpio,
			&irq_करोमुख्य_simple_ops, शून्य);
	अगर (!aपंचांगel_pioctrl->irq_करोमुख्य) अणु
		dev_err(dev, "can't add the irq domain\n");
		वापस -ENODEV;
	पूर्ण
	aपंचांगel_pioctrl->irq_करोमुख्य->name = "atmel gpio";

	क्रम (i = 0; i < aपंचांगel_pioctrl->npins; i++) अणु
		पूर्णांक irq = irq_create_mapping(aपंचांगel_pioctrl->irq_करोमुख्य, i);

		irq_set_chip_and_handler(irq, &aपंचांगel_gpio_irq_chip,
					 handle_simple_irq);
		irq_set_chip_data(irq, aपंचांगel_pioctrl);
		dev_dbg(dev,
			"atmel gpio irq domain: hwirq: %d, linux irq: %d\n",
			i, irq);
	पूर्ण

	ret = clk_prepare_enable(aपंचांगel_pioctrl->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to prepare and enable clock\n");
		जाओ clk_prepare_enable_error;
	पूर्ण

	aपंचांगel_pioctrl->pinctrl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev,
							   &aपंचांगel_pinctrl_desc,
							   aपंचांगel_pioctrl);
	अगर (IS_ERR(aपंचांगel_pioctrl->pinctrl_dev)) अणु
		ret = PTR_ERR(aपंचांगel_pioctrl->pinctrl_dev);
		dev_err(dev, "pinctrl registration failed\n");
		जाओ clk_unprep;
	पूर्ण

	ret = gpiochip_add_data(aपंचांगel_pioctrl->gpio_chip, aपंचांगel_pioctrl);
	अगर (ret) अणु
		dev_err(dev, "failed to add gpiochip\n");
		जाओ clk_unprep;
	पूर्ण

	ret = gpiochip_add_pin_range(aपंचांगel_pioctrl->gpio_chip, dev_name(dev),
				     0, 0, aपंचांगel_pioctrl->gpio_chip->ngpio);
	अगर (ret) अणु
		dev_err(dev, "failed to add gpio pin range\n");
		जाओ gpiochip_add_pin_range_error;
	पूर्ण

	dev_info(&pdev->dev, "atmel pinctrl initialized\n");

	वापस 0;

gpiochip_add_pin_range_error:
	gpiochip_हटाओ(aपंचांगel_pioctrl->gpio_chip);

clk_unprep:
	clk_disable_unprepare(aपंचांगel_pioctrl->clk);

clk_prepare_enable_error:
	irq_करोमुख्य_हटाओ(aपंचांगel_pioctrl->irq_करोमुख्य);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_pinctrl_driver = अणु
	.driver = अणु
		.name = "pinctrl-at91-pio4",
		.of_match_table = aपंचांगel_pctrl_of_match,
		.pm = &aपंचांगel_pctrl_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = aपंचांगel_pinctrl_probe,
पूर्ण;
builtin_platक्रमm_driver(aपंचांगel_pinctrl_driver);
