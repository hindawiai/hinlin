<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Maxime Coquelin 2015
 * Copyright (C) STMicroelectronics 2017
 * Author:  Maxime Coquelin <mcoquelin.sपंचांग32@gmail.com>
 *
 * Heavily based on Mediatek's pinctrl driver
 */
#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "../pinconf.h"
#समावेश "../pinctrl-utils.h"
#समावेश "pinctrl-stm32.h"

#घोषणा STM32_GPIO_MODER	0x00
#घोषणा STM32_GPIO_TYPER	0x04
#घोषणा STM32_GPIO_SPEEDR	0x08
#घोषणा STM32_GPIO_PUPDR	0x0c
#घोषणा STM32_GPIO_IDR		0x10
#घोषणा STM32_GPIO_ODR		0x14
#घोषणा STM32_GPIO_BSRR		0x18
#घोषणा STM32_GPIO_LCKR		0x1c
#घोषणा STM32_GPIO_AFRL		0x20
#घोषणा STM32_GPIO_AFRH		0x24

/* custom bitfield to backup pin status */
#घोषणा STM32_GPIO_BKP_MODE_SHIFT	0
#घोषणा STM32_GPIO_BKP_MODE_MASK	GENMASK(1, 0)
#घोषणा STM32_GPIO_BKP_ALT_SHIFT	2
#घोषणा STM32_GPIO_BKP_ALT_MASK		GENMASK(5, 2)
#घोषणा STM32_GPIO_BKP_SPEED_SHIFT	6
#घोषणा STM32_GPIO_BKP_SPEED_MASK	GENMASK(7, 6)
#घोषणा STM32_GPIO_BKP_PUPD_SHIFT	8
#घोषणा STM32_GPIO_BKP_PUPD_MASK	GENMASK(9, 8)
#घोषणा STM32_GPIO_BKP_TYPE		10
#घोषणा STM32_GPIO_BKP_VAL		11

#घोषणा STM32_GPIO_PINS_PER_BANK 16
#घोषणा STM32_GPIO_IRQ_LINE	 16

#घोषणा SYSCFG_IRQMUX_MASK GENMASK(3, 0)

#घोषणा gpio_range_to_bank(chip) \
		container_of(chip, काष्ठा sपंचांग32_gpio_bank, range)

#घोषणा HWSPNLCK_TIMEOUT	1000 /* usec */

अटल स्थिर अक्षर * स्थिर sपंचांग32_gpio_functions[] = अणु
	"gpio", "af0", "af1",
	"af2", "af3", "af4",
	"af5", "af6", "af7",
	"af8", "af9", "af10",
	"af11", "af12", "af13",
	"af14", "af15", "analog",
पूर्ण;

काष्ठा sपंचांग32_pinctrl_group अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ config;
	अचिन्हित pin;
पूर्ण;

काष्ठा sपंचांग32_gpio_bank अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा reset_control *rstc;
	spinlock_t lock;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा pinctrl_gpio_range range;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	u32 bank_nr;
	u32 bank_ioport_nr;
	u32 pin_backup[STM32_GPIO_PINS_PER_BANK];
	u8 irq_type[STM32_GPIO_PINS_PER_BANK];
पूर्ण;

काष्ठा sपंचांग32_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl_dev;
	काष्ठा pinctrl_desc pctl_desc;
	काष्ठा sपंचांग32_pinctrl_group *groups;
	अचिन्हित ngroups;
	स्थिर अक्षर **grp_names;
	काष्ठा sपंचांग32_gpio_bank *banks;
	अचिन्हित nbanks;
	स्थिर काष्ठा sपंचांग32_pinctrl_match_data *match_data;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा regmap		*regmap;
	काष्ठा regmap_field	*irqmux[STM32_GPIO_PINS_PER_BANK];
	काष्ठा hwspinlock *hwlock;
	काष्ठा sपंचांग32_desc_pin *pins;
	u32 npins;
	u32 pkg;
	u16 irqmux_map;
	spinlock_t irqmux_lock;
पूर्ण;

अटल अंतरभूत पूर्णांक sपंचांग32_gpio_pin(पूर्णांक gpio)
अणु
	वापस gpio % STM32_GPIO_PINS_PER_BANK;
पूर्ण

अटल अंतरभूत u32 sपंचांग32_gpio_get_mode(u32 function)
अणु
	चयन (function) अणु
	हाल STM32_PIN_GPIO:
		वापस 0;
	हाल STM32_PIN_AF(0) ... STM32_PIN_AF(15):
		वापस 2;
	हाल STM32_PIN_ANALOG:
		वापस 3;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32 sपंचांग32_gpio_get_alt(u32 function)
अणु
	चयन (function) अणु
	हाल STM32_PIN_GPIO:
		वापस 0;
	हाल STM32_PIN_AF(0) ... STM32_PIN_AF(15):
		वापस function - 1;
	हाल STM32_PIN_ANALOG:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_gpio_backup_value(काष्ठा sपंचांग32_gpio_bank *bank,
				    u32 offset, u32 value)
अणु
	bank->pin_backup[offset] &= ~BIT(STM32_GPIO_BKP_VAL);
	bank->pin_backup[offset] |= value << STM32_GPIO_BKP_VAL;
पूर्ण

अटल व्योम sपंचांग32_gpio_backup_mode(काष्ठा sपंचांग32_gpio_bank *bank, u32 offset,
				   u32 mode, u32 alt)
अणु
	bank->pin_backup[offset] &= ~(STM32_GPIO_BKP_MODE_MASK |
				      STM32_GPIO_BKP_ALT_MASK);
	bank->pin_backup[offset] |= mode << STM32_GPIO_BKP_MODE_SHIFT;
	bank->pin_backup[offset] |= alt << STM32_GPIO_BKP_ALT_SHIFT;
पूर्ण

अटल व्योम sपंचांग32_gpio_backup_driving(काष्ठा sपंचांग32_gpio_bank *bank, u32 offset,
				      u32 drive)
अणु
	bank->pin_backup[offset] &= ~BIT(STM32_GPIO_BKP_TYPE);
	bank->pin_backup[offset] |= drive << STM32_GPIO_BKP_TYPE;
पूर्ण

अटल व्योम sपंचांग32_gpio_backup_speed(काष्ठा sपंचांग32_gpio_bank *bank, u32 offset,
				    u32 speed)
अणु
	bank->pin_backup[offset] &= ~STM32_GPIO_BKP_SPEED_MASK;
	bank->pin_backup[offset] |= speed << STM32_GPIO_BKP_SPEED_SHIFT;
पूर्ण

अटल व्योम sपंचांग32_gpio_backup_bias(काष्ठा sपंचांग32_gpio_bank *bank, u32 offset,
				   u32 bias)
अणु
	bank->pin_backup[offset] &= ~STM32_GPIO_BKP_PUPD_MASK;
	bank->pin_backup[offset] |= bias << STM32_GPIO_BKP_PUPD_SHIFT;
पूर्ण

/* GPIO functions */

अटल अंतरभूत व्योम __sपंचांग32_gpio_set(काष्ठा sपंचांग32_gpio_bank *bank,
	अचिन्हित offset, पूर्णांक value)
अणु
	sपंचांग32_gpio_backup_value(bank, offset, value);

	अगर (!value)
		offset += STM32_GPIO_PINS_PER_BANK;

	clk_enable(bank->clk);

	ग_लिखोl_relaxed(BIT(offset), bank->base + STM32_GPIO_BSRR);

	clk_disable(bank->clk);
पूर्ण

अटल पूर्णांक sपंचांग32_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);
	काष्ठा pinctrl_gpio_range *range;
	पूर्णांक pin = offset + (bank->bank_nr * STM32_GPIO_PINS_PER_BANK);

	range = pinctrl_find_gpio_range_from_pin_nolock(pctl->pctl_dev, pin);
	अगर (!range) अणु
		dev_err(pctl->dev, "pin %d not in range.\n", pin);
		वापस -EINVAL;
	पूर्ण

	वापस pinctrl_gpio_request(chip->base + offset);
पूर्ण

अटल व्योम sपंचांग32_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	pinctrl_gpio_मुक्त(chip->base + offset);
पूर्ण

अटल पूर्णांक sपंचांग32_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = gpiochip_get_data(chip);
	पूर्णांक ret;

	clk_enable(bank->clk);

	ret = !!(पढ़ोl_relaxed(bank->base + STM32_GPIO_IDR) & BIT(offset));

	clk_disable(bank->clk);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = gpiochip_get_data(chip);

	__sपंचांग32_gpio_set(bank, offset, value);
पूर्ण

अटल पूर्णांक sपंचांग32_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक sपंचांग32_gpio_direction_output(काष्ठा gpio_chip *chip,
	अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = gpiochip_get_data(chip);

	__sपंचांग32_gpio_set(bank, offset, value);
	pinctrl_gpio_direction_output(chip->base + offset);

	वापस 0;
पूर्ण


अटल पूर्णांक sपंचांग32_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा irq_fwspec fwspec;

	fwspec.fwnode = bank->fwnode;
	fwspec.param_count = 2;
	fwspec.param[0] = offset;
	fwspec.param[1] = IRQ_TYPE_NONE;

	वापस irq_create_fwspec_mapping(&fwspec);
पूर्ण

अटल पूर्णांक sपंचांग32_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = gpiochip_get_data(chip);
	पूर्णांक pin = sपंचांग32_gpio_pin(offset);
	पूर्णांक ret;
	u32 mode, alt;

	sपंचांग32_pmx_get_mode(bank, pin, &mode, &alt);
	अगर ((alt == 0) && (mode == 0))
		ret = GPIO_LINE_सूचीECTION_IN;
	अन्यथा अगर ((alt == 0) && (mode == 1))
		ret = GPIO_LINE_सूचीECTION_OUT;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा gpio_chip sपंचांग32_gpio_ढाँचा = अणु
	.request		= sपंचांग32_gpio_request,
	.मुक्त			= sपंचांग32_gpio_मुक्त,
	.get			= sपंचांग32_gpio_get,
	.set			= sपंचांग32_gpio_set,
	.direction_input	= sपंचांग32_gpio_direction_input,
	.direction_output	= sपंचांग32_gpio_direction_output,
	.to_irq			= sपंचांग32_gpio_to_irq,
	.get_direction		= sपंचांग32_gpio_get_direction,
	.set_config		= gpiochip_generic_config,
पूर्ण;

अटल व्योम sपंचांग32_gpio_irq_trigger(काष्ठा irq_data *d)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = d->करोमुख्य->host_data;
	पूर्णांक level;

	/* If level पूर्णांकerrupt type then retrig */
	level = sपंचांग32_gpio_get(&bank->gpio_chip, d->hwirq);
	अगर ((level == 0 && bank->irq_type[d->hwirq] == IRQ_TYPE_LEVEL_LOW) ||
	    (level == 1 && bank->irq_type[d->hwirq] == IRQ_TYPE_LEVEL_HIGH))
		irq_chip_retrigger_hierarchy(d);
पूर्ण

अटल व्योम sपंचांग32_gpio_irq_eoi(काष्ठा irq_data *d)
अणु
	irq_chip_eoi_parent(d);
	sपंचांग32_gpio_irq_trigger(d);
पूर्ण;

अटल पूर्णांक sपंचांग32_gpio_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = d->करोमुख्य->host_data;
	u32 parent_type;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
		parent_type = type;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		parent_type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		parent_type = IRQ_TYPE_EDGE_FALLING;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	bank->irq_type[d->hwirq] = type;

	वापस irq_chip_set_type_parent(d, parent_type);
पूर्ण;

अटल पूर्णांक sपंचांग32_gpio_irq_request_resources(काष्ठा irq_data *irq_data)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = irq_data->करोमुख्य->host_data;
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);
	पूर्णांक ret;

	ret = sपंचांग32_gpio_direction_input(&bank->gpio_chip, irq_data->hwirq);
	अगर (ret)
		वापस ret;

	ret = gpiochip_lock_as_irq(&bank->gpio_chip, irq_data->hwirq);
	अगर (ret) अणु
		dev_err(pctl->dev, "unable to lock HW IRQ %lu for IRQ\n",
			irq_data->hwirq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_gpio_irq_release_resources(काष्ठा irq_data *irq_data)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = irq_data->करोमुख्य->host_data;

	gpiochip_unlock_as_irq(&bank->gpio_chip, irq_data->hwirq);
पूर्ण

अटल व्योम sपंचांग32_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	irq_chip_unmask_parent(d);
	sपंचांग32_gpio_irq_trigger(d);
पूर्ण

अटल काष्ठा irq_chip sपंचांग32_gpio_irq_chip = अणु
	.name		= "stm32gpio",
	.irq_eoi	= sपंचांग32_gpio_irq_eoi,
	.irq_ack	= irq_chip_ack_parent,
	.irq_mask	= irq_chip_mask_parent,
	.irq_unmask	= sपंचांग32_gpio_irq_unmask,
	.irq_set_type	= sपंचांग32_gpio_set_type,
	.irq_set_wake	= irq_chip_set_wake_parent,
	.irq_request_resources = sपंचांग32_gpio_irq_request_resources,
	.irq_release_resources = sपंचांग32_gpio_irq_release_resources,
पूर्ण;

अटल पूर्णांक sपंचांग32_gpio_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				       काष्ठा irq_fwspec *fwspec,
				       अचिन्हित दीर्घ *hwirq,
				       अचिन्हित पूर्णांक *type)
अणु
	अगर ((fwspec->param_count != 2) ||
	    (fwspec->param[0] >= STM32_GPIO_IRQ_LINE))
		वापस -EINVAL;

	*hwirq = fwspec->param[0];
	*type = fwspec->param[1];
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_gpio_करोमुख्य_activate(काष्ठा irq_करोमुख्य *d,
				      काष्ठा irq_data *irq_data, bool reserve)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = d->host_data;
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/*
	 * gpio irq mux is shared between several banks, a lock has to be करोne
	 * to aव्योम overriding.
	 */
	spin_lock_irqsave(&pctl->irqmux_lock, flags);

	अगर (pctl->hwlock) अणु
		ret = hwspin_lock_समयout_in_atomic(pctl->hwlock,
						    HWSPNLCK_TIMEOUT);
		अगर (ret) अणु
			dev_err(pctl->dev, "Can't get hwspinlock\n");
			जाओ unlock;
		पूर्ण
	पूर्ण

	अगर (pctl->irqmux_map & BIT(irq_data->hwirq)) अणु
		dev_err(pctl->dev, "irq line %ld already requested.\n",
			irq_data->hwirq);
		ret = -EBUSY;
		अगर (pctl->hwlock)
			hwspin_unlock_in_atomic(pctl->hwlock);
		जाओ unlock;
	पूर्ण अन्यथा अणु
		pctl->irqmux_map |= BIT(irq_data->hwirq);
	पूर्ण

	regmap_field_ग_लिखो(pctl->irqmux[irq_data->hwirq], bank->bank_ioport_nr);

	अगर (pctl->hwlock)
		hwspin_unlock_in_atomic(pctl->hwlock);

unlock:
	spin_unlock_irqrestore(&pctl->irqmux_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_gpio_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *d,
					 काष्ठा irq_data *irq_data)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = d->host_data;
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pctl->irqmux_lock, flags);
	pctl->irqmux_map &= ~BIT(irq_data->hwirq);
	spin_unlock_irqrestore(&pctl->irqmux_lock, flags);
पूर्ण

अटल पूर्णांक sपंचांग32_gpio_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *d,
				   अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = d->host_data;
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;

	hwirq = fwspec->param[0];
	parent_fwspec.fwnode = d->parent->fwnode;
	parent_fwspec.param_count = 2;
	parent_fwspec.param[0] = fwspec->param[0];
	parent_fwspec.param[1] = fwspec->param[1];

	irq_करोमुख्य_set_hwirq_and_chip(d, virq, hwirq, &sपंचांग32_gpio_irq_chip,
				      bank);

	वापस irq_करोमुख्य_alloc_irqs_parent(d, virq, nr_irqs, &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sपंचांग32_gpio_करोमुख्य_ops = अणु
	.translate      = sपंचांग32_gpio_करोमुख्य_translate,
	.alloc          = sपंचांग32_gpio_करोमुख्य_alloc,
	.मुक्त           = irq_करोमुख्य_मुक्त_irqs_common,
	.activate	= sपंचांग32_gpio_करोमुख्य_activate,
	.deactivate	= sपंचांग32_gpio_करोमुख्य_deactivate,
पूर्ण;

/* Pinctrl functions */
अटल काष्ठा sपंचांग32_pinctrl_group *
sपंचांग32_pctrl_find_group_by_pin(काष्ठा sपंचांग32_pinctrl *pctl, u32 pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->ngroups; i++) अणु
		काष्ठा sपंचांग32_pinctrl_group *grp = pctl->groups + i;

		अगर (grp->pin == pin)
			वापस grp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool sपंचांग32_pctrl_is_function_valid(काष्ठा sपंचांग32_pinctrl *pctl,
		u32 pin_num, u32 fnum)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->npins; i++) अणु
		स्थिर काष्ठा sपंचांग32_desc_pin *pin = pctl->pins + i;
		स्थिर काष्ठा sपंचांग32_desc_function *func = pin->functions;

		अगर (pin->pin.number != pin_num)
			जारी;

		जबतक (func && func->name) अणु
			अगर (func->num == fnum)
				वापस true;
			func++;
		पूर्ण

		अवरोध;
	पूर्ण

	dev_err(pctl->dev, "invalid function %d on pin %d .\n", fnum, pin_num);

	वापस false;
पूर्ण

अटल पूर्णांक sपंचांग32_pctrl_dt_node_to_map_func(काष्ठा sपंचांग32_pinctrl *pctl,
		u32 pin, u32 fnum, काष्ठा sपंचांग32_pinctrl_group *grp,
		काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps)
अणु
	अगर (*num_maps == *reserved_maps)
		वापस -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)[*num_maps].data.mux.group = grp->name;

	अगर (!sपंचांग32_pctrl_is_function_valid(pctl, pin, fnum))
		वापस -EINVAL;

	(*map)[*num_maps].data.mux.function = sपंचांग32_gpio_functions[fnum];
	(*num_maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pctrl_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा device_node *node,
				      काष्ठा pinctrl_map **map,
				      अचिन्हित *reserved_maps,
				      अचिन्हित *num_maps)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl;
	काष्ठा sपंचांग32_pinctrl_group *grp;
	काष्ठा property *pins;
	u32 pinfunc, pin, func;
	अचिन्हित दीर्घ *configs;
	अचिन्हित पूर्णांक num_configs;
	bool has_config = 0;
	अचिन्हित reserve = 0;
	पूर्णांक num_pins, num_funcs, maps_per_pin, i, err = 0;

	pctl = pinctrl_dev_get_drvdata(pctldev);

	pins = of_find_property(node, "pinmux", शून्य);
	अगर (!pins) अणु
		dev_err(pctl->dev, "missing pins property in node %pOFn .\n",
				node);
		वापस -EINVAL;
	पूर्ण

	err = pinconf_generic_parse_dt_config(node, pctldev, &configs,
		&num_configs);
	अगर (err)
		वापस err;

	अगर (num_configs)
		has_config = 1;

	num_pins = pins->length / माप(u32);
	num_funcs = num_pins;
	maps_per_pin = 0;
	अगर (num_funcs)
		maps_per_pin++;
	अगर (has_config && num_pins >= 1)
		maps_per_pin++;

	अगर (!num_pins || !maps_per_pin) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	reserve = num_pins * maps_per_pin;

	err = pinctrl_utils_reserve_map(pctldev, map,
			reserved_maps, num_maps, reserve);
	अगर (err)
		जाओ निकास;

	क्रम (i = 0; i < num_pins; i++) अणु
		err = of_property_पढ़ो_u32_index(node, "pinmux",
				i, &pinfunc);
		अगर (err)
			जाओ निकास;

		pin = STM32_GET_PIN_NO(pinfunc);
		func = STM32_GET_PIN_FUNC(pinfunc);

		अगर (!sपंचांग32_pctrl_is_function_valid(pctl, pin, func)) अणु
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		grp = sपंचांग32_pctrl_find_group_by_pin(pctl, pin);
		अगर (!grp) अणु
			dev_err(pctl->dev, "unable to match pin %d to group\n",
					pin);
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		err = sपंचांग32_pctrl_dt_node_to_map_func(pctl, pin, func, grp, map,
				reserved_maps, num_maps);
		अगर (err)
			जाओ निकास;

		अगर (has_config) अणु
			err = pinctrl_utils_add_map_configs(pctldev, map,
					reserved_maps, num_maps, grp->name,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GROUP);
			अगर (err)
				जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	kमुक्त(configs);
	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_pctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा device_node *np_config,
				 काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा device_node *np;
	अचिन्हित reserved_maps;
	पूर्णांक ret;

	*map = शून्य;
	*num_maps = 0;
	reserved_maps = 0;

	क्रम_each_child_of_node(np_config, np) अणु
		ret = sपंचांग32_pctrl_dt_subnode_to_map(pctldev, np, map,
				&reserved_maps, num_maps);
		अगर (ret < 0) अणु
			pinctrl_utils_मुक्त_map(pctldev, *map, *num_maps);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->ngroups;
पूर्ण

अटल स्थिर अक्षर *sपंचांग32_pctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित group)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->groups[group].name;
पूर्ण

अटल पूर्णांक sपंचांग32_pctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित group,
				      स्थिर अचिन्हित **pins,
				      अचिन्हित *num_pins)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*pins = (अचिन्हित *)&pctl->groups[group].pin;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops sपंचांग32_pctrl_ops = अणु
	.dt_node_to_map		= sपंचांग32_pctrl_dt_node_to_map,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
	.get_groups_count	= sपंचांग32_pctrl_get_groups_count,
	.get_group_name		= sपंचांग32_pctrl_get_group_name,
	.get_group_pins		= sपंचांग32_pctrl_get_group_pins,
पूर्ण;


/* Pinmux functions */

अटल पूर्णांक sपंचांग32_pmx_get_funcs_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(sपंचांग32_gpio_functions);
पूर्ण

अटल स्थिर अक्षर *sपंचांग32_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित selector)
अणु
	वापस sपंचांग32_gpio_functions[selector];
पूर्ण

अटल पूर्णांक sपंचांग32_pmx_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित function,
				     स्थिर अक्षर * स्थिर **groups,
				     अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctl->grp_names;
	*num_groups = pctl->ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pmx_set_mode(काष्ठा sपंचांग32_gpio_bank *bank,
			      पूर्णांक pin, u32 mode, u32 alt)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);
	u32 val;
	पूर्णांक alt_shअगरt = (pin % 8) * 4;
	पूर्णांक alt_offset = STM32_GPIO_AFRL + (pin / 8) * 4;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	अगर (pctl->hwlock) अणु
		err = hwspin_lock_समयout_in_atomic(pctl->hwlock,
						    HWSPNLCK_TIMEOUT);
		अगर (err) अणु
			dev_err(pctl->dev, "Can't get hwspinlock\n");
			जाओ unlock;
		पूर्ण
	पूर्ण

	val = पढ़ोl_relaxed(bank->base + alt_offset);
	val &= ~GENMASK(alt_shअगरt + 3, alt_shअगरt);
	val |= (alt << alt_shअगरt);
	ग_लिखोl_relaxed(val, bank->base + alt_offset);

	val = पढ़ोl_relaxed(bank->base + STM32_GPIO_MODER);
	val &= ~GENMASK(pin * 2 + 1, pin * 2);
	val |= mode << (pin * 2);
	ग_लिखोl_relaxed(val, bank->base + STM32_GPIO_MODER);

	अगर (pctl->hwlock)
		hwspin_unlock_in_atomic(pctl->hwlock);

	sपंचांग32_gpio_backup_mode(bank, pin, mode, alt);

unlock:
	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	वापस err;
पूर्ण

व्योम sपंचांग32_pmx_get_mode(काष्ठा sपंचांग32_gpio_bank *bank, पूर्णांक pin, u32 *mode,
			u32 *alt)
अणु
	u32 val;
	पूर्णांक alt_shअगरt = (pin % 8) * 4;
	पूर्णांक alt_offset = STM32_GPIO_AFRL + (pin / 8) * 4;
	अचिन्हित दीर्घ flags;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	val = पढ़ोl_relaxed(bank->base + alt_offset);
	val &= GENMASK(alt_shअगरt + 3, alt_shअगरt);
	*alt = val >> alt_shअगरt;

	val = पढ़ोl_relaxed(bank->base + STM32_GPIO_MODER);
	val &= GENMASK(pin * 2 + 1, pin * 2);
	*mode = val >> (pin * 2);

	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);
पूर्ण

अटल पूर्णांक sपंचांग32_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
			    अचिन्हित function,
			    अचिन्हित group)
अणु
	bool ret;
	काष्ठा sपंचांग32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sपंचांग32_pinctrl_group *g = pctl->groups + group;
	काष्ठा pinctrl_gpio_range *range;
	काष्ठा sपंचांग32_gpio_bank *bank;
	u32 mode, alt;
	पूर्णांक pin;

	ret = sपंचांग32_pctrl_is_function_valid(pctl, g->pin, function);
	अगर (!ret)
		वापस -EINVAL;

	range = pinctrl_find_gpio_range_from_pin(pctldev, g->pin);
	अगर (!range) अणु
		dev_err(pctl->dev, "No gpio range defined.\n");
		वापस -EINVAL;
	पूर्ण

	bank = gpiochip_get_data(range->gc);
	pin = sपंचांग32_gpio_pin(g->pin);

	mode = sपंचांग32_gpio_get_mode(function);
	alt = sपंचांग32_gpio_get_alt(function);

	वापस sपंचांग32_pmx_set_mode(bank, pin, mode, alt);
पूर्ण

अटल पूर्णांक sपंचांग32_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_gpio_range *range, अचिन्हित gpio,
			bool input)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = gpiochip_get_data(range->gc);
	पूर्णांक pin = sपंचांग32_gpio_pin(gpio);

	वापस sपंचांग32_pmx_set_mode(bank, pin, !input, 0);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops sपंचांग32_pmx_ops = अणु
	.get_functions_count	= sपंचांग32_pmx_get_funcs_cnt,
	.get_function_name	= sपंचांग32_pmx_get_func_name,
	.get_function_groups	= sपंचांग32_pmx_get_func_groups,
	.set_mux		= sपंचांग32_pmx_set_mux,
	.gpio_set_direction	= sपंचांग32_pmx_gpio_set_direction,
	.strict			= true,
पूर्ण;

/* Pinconf functions */

अटल पूर्णांक sपंचांग32_pconf_set_driving(काष्ठा sपंचांग32_gpio_bank *bank,
				   अचिन्हित offset, u32 drive)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक err = 0;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	अगर (pctl->hwlock) अणु
		err = hwspin_lock_समयout_in_atomic(pctl->hwlock,
						    HWSPNLCK_TIMEOUT);
		अगर (err) अणु
			dev_err(pctl->dev, "Can't get hwspinlock\n");
			जाओ unlock;
		पूर्ण
	पूर्ण

	val = पढ़ोl_relaxed(bank->base + STM32_GPIO_TYPER);
	val &= ~BIT(offset);
	val |= drive << offset;
	ग_लिखोl_relaxed(val, bank->base + STM32_GPIO_TYPER);

	अगर (pctl->hwlock)
		hwspin_unlock_in_atomic(pctl->hwlock);

	sपंचांग32_gpio_backup_driving(bank, offset, drive);

unlock:
	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	वापस err;
पूर्ण

अटल u32 sपंचांग32_pconf_get_driving(काष्ठा sपंचांग32_gpio_bank *bank,
	अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	val = पढ़ोl_relaxed(bank->base + STM32_GPIO_TYPER);
	val &= BIT(offset);

	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	वापस (val >> offset);
पूर्ण

अटल पूर्णांक sपंचांग32_pconf_set_speed(काष्ठा sपंचांग32_gpio_bank *bank,
				 अचिन्हित offset, u32 speed)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक err = 0;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	अगर (pctl->hwlock) अणु
		err = hwspin_lock_समयout_in_atomic(pctl->hwlock,
						    HWSPNLCK_TIMEOUT);
		अगर (err) अणु
			dev_err(pctl->dev, "Can't get hwspinlock\n");
			जाओ unlock;
		पूर्ण
	पूर्ण

	val = पढ़ोl_relaxed(bank->base + STM32_GPIO_SPEEDR);
	val &= ~GENMASK(offset * 2 + 1, offset * 2);
	val |= speed << (offset * 2);
	ग_लिखोl_relaxed(val, bank->base + STM32_GPIO_SPEEDR);

	अगर (pctl->hwlock)
		hwspin_unlock_in_atomic(pctl->hwlock);

	sपंचांग32_gpio_backup_speed(bank, offset, speed);

unlock:
	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	वापस err;
पूर्ण

अटल u32 sपंचांग32_pconf_get_speed(काष्ठा sपंचांग32_gpio_bank *bank,
	अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	val = पढ़ोl_relaxed(bank->base + STM32_GPIO_SPEEDR);
	val &= GENMASK(offset * 2 + 1, offset * 2);

	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	वापस (val >> (offset * 2));
पूर्ण

अटल पूर्णांक sपंचांग32_pconf_set_bias(काष्ठा sपंचांग32_gpio_bank *bank,
				अचिन्हित offset, u32 bias)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(bank->gpio_chip.parent);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक err = 0;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	अगर (pctl->hwlock) अणु
		err = hwspin_lock_समयout_in_atomic(pctl->hwlock,
						    HWSPNLCK_TIMEOUT);
		अगर (err) अणु
			dev_err(pctl->dev, "Can't get hwspinlock\n");
			जाओ unlock;
		पूर्ण
	पूर्ण

	val = पढ़ोl_relaxed(bank->base + STM32_GPIO_PUPDR);
	val &= ~GENMASK(offset * 2 + 1, offset * 2);
	val |= bias << (offset * 2);
	ग_लिखोl_relaxed(val, bank->base + STM32_GPIO_PUPDR);

	अगर (pctl->hwlock)
		hwspin_unlock_in_atomic(pctl->hwlock);

	sपंचांग32_gpio_backup_bias(bank, offset, bias);

unlock:
	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	वापस err;
पूर्ण

अटल u32 sपंचांग32_pconf_get_bias(काष्ठा sपंचांग32_gpio_bank *bank,
	अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	val = पढ़ोl_relaxed(bank->base + STM32_GPIO_PUPDR);
	val &= GENMASK(offset * 2 + 1, offset * 2);

	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	वापस (val >> (offset * 2));
पूर्ण

अटल bool sपंचांग32_pconf_get(काष्ठा sपंचांग32_gpio_bank *bank,
	अचिन्हित पूर्णांक offset, bool dir)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	अगर (dir)
		val = !!(पढ़ोl_relaxed(bank->base + STM32_GPIO_IDR) &
			 BIT(offset));
	अन्यथा
		val = !!(पढ़ोl_relaxed(bank->base + STM32_GPIO_ODR) &
			 BIT(offset));

	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	वापस val;
पूर्ण

अटल पूर्णांक sपंचांग32_pconf_parse_conf(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक pin, क्रमागत pin_config_param param,
		क्रमागत pin_config_param arg)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pinctrl_gpio_range *range;
	काष्ठा sपंचांग32_gpio_bank *bank;
	पूर्णांक offset, ret = 0;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	अगर (!range) अणु
		dev_err(pctl->dev, "No gpio range defined.\n");
		वापस -EINVAL;
	पूर्ण

	bank = gpiochip_get_data(range->gc);
	offset = sपंचांग32_gpio_pin(pin);

	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		ret = sपंचांग32_pconf_set_driving(bank, offset, 0);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		ret = sपंचांग32_pconf_set_driving(bank, offset, 1);
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		ret = sपंचांग32_pconf_set_speed(bank, offset, arg);
		अवरोध;
	हाल PIN_CONFIG_BIAS_DISABLE:
		ret = sपंचांग32_pconf_set_bias(bank, offset, 0);
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		ret = sपंचांग32_pconf_set_bias(bank, offset, 1);
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ret = sपंचांग32_pconf_set_bias(bank, offset, 2);
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		__sपंचांग32_gpio_set(bank, offset, arg);
		ret = sपंचांग32_pmx_gpio_set_direction(pctldev, range, pin, false);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_pconf_group_get(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित group,
				 अचिन्हित दीर्घ *config)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*config = pctl->groups[group].config;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pconf_group_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित group,
				 अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sपंचांग32_pinctrl_group *g = &pctl->groups[group];
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		mutex_lock(&pctldev->mutex);
		ret = sपंचांग32_pconf_parse_conf(pctldev, g->pin,
			pinconf_to_config_param(configs[i]),
			pinconf_to_config_argument(configs[i]));
		mutex_unlock(&pctldev->mutex);
		अगर (ret < 0)
			वापस ret;

		g->config = configs[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			   अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		ret = sपंचांग32_pconf_parse_conf(pctldev, pin,
				pinconf_to_config_param(configs[i]),
				pinconf_to_config_argument(configs[i]));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_pconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा seq_file *s,
				 अचिन्हित पूर्णांक pin)
अणु
	काष्ठा pinctrl_gpio_range *range;
	काष्ठा sपंचांग32_gpio_bank *bank;
	पूर्णांक offset;
	u32 mode, alt, drive, speed, bias;
	अटल स्थिर अक्षर * स्थिर modes[] = अणु
			"input", "output", "alternate", "analog" पूर्ण;
	अटल स्थिर अक्षर * स्थिर speeds[] = अणु
			"low", "medium", "high", "very high" पूर्ण;
	अटल स्थिर अक्षर * स्थिर biasing[] = अणु
			"floating", "pull up", "pull down", "" पूर्ण;
	bool val;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	अगर (!range)
		वापस;

	bank = gpiochip_get_data(range->gc);
	offset = sपंचांग32_gpio_pin(pin);

	sपंचांग32_pmx_get_mode(bank, offset, &mode, &alt);
	bias = sपंचांग32_pconf_get_bias(bank, offset);

	seq_म_लिखो(s, "%s ", modes[mode]);

	चयन (mode) अणु
	/* input */
	हाल 0:
		val = sपंचांग32_pconf_get(bank, offset, true);
		seq_म_लिखो(s, "- %s - %s",
			   val ? "high" : "low",
			   biasing[bias]);
		अवरोध;

	/* output */
	हाल 1:
		drive = sपंचांग32_pconf_get_driving(bank, offset);
		speed = sपंचांग32_pconf_get_speed(bank, offset);
		val = sपंचांग32_pconf_get(bank, offset, false);
		seq_म_लिखो(s, "- %s - %s - %s - %s %s",
			   val ? "high" : "low",
			   drive ? "open drain" : "push pull",
			   biasing[bias],
			   speeds[speed], "speed");
		अवरोध;

	/* alternate */
	हाल 2:
		drive = sपंचांग32_pconf_get_driving(bank, offset);
		speed = sपंचांग32_pconf_get_speed(bank, offset);
		seq_म_लिखो(s, "%d - %s - %s - %s %s", alt,
			   drive ? "open drain" : "push pull",
			   biasing[bias],
			   speeds[speed], "speed");
		अवरोध;

	/* analog */
	हाल 3:
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops sपंचांग32_pconf_ops = अणु
	.pin_config_group_get	= sपंचांग32_pconf_group_get,
	.pin_config_group_set	= sपंचांग32_pconf_group_set,
	.pin_config_set		= sपंचांग32_pconf_set,
	.pin_config_dbg_show	= sपंचांग32_pconf_dbg_show,
पूर्ण;

अटल पूर्णांक sपंचांग32_gpiolib_रेजिस्टर_bank(काष्ठा sपंचांग32_pinctrl *pctl,
	काष्ठा device_node *np)
अणु
	काष्ठा sपंचांग32_gpio_bank *bank = &pctl->banks[pctl->nbanks];
	पूर्णांक bank_ioport_nr;
	काष्ठा pinctrl_gpio_range *range = &bank->range;
	काष्ठा of_phandle_args args;
	काष्ठा device *dev = pctl->dev;
	काष्ठा resource res;
	पूर्णांक npins = STM32_GPIO_PINS_PER_BANK;
	पूर्णांक bank_nr, err;

	अगर (!IS_ERR(bank->rstc))
		reset_control_deनिश्चित(bank->rstc);

	अगर (of_address_to_resource(np, 0, &res))
		वापस -ENODEV;

	bank->base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(bank->base))
		वापस PTR_ERR(bank->base);

	err = clk_prepare(bank->clk);
	अगर (err) अणु
		dev_err(dev, "failed to prepare clk (%d)\n", err);
		वापस err;
	पूर्ण

	bank->gpio_chip = sपंचांग32_gpio_ढाँचा;

	of_property_पढ़ो_string(np, "st,bank-name", &bank->gpio_chip.label);

	अगर (!of_parse_phandle_with_fixed_args(np, "gpio-ranges", 3, 0, &args)) अणु
		bank_nr = args.args[1] / STM32_GPIO_PINS_PER_BANK;
		bank->gpio_chip.base = args.args[1];
	पूर्ण अन्यथा अणु
		bank_nr = pctl->nbanks;
		bank->gpio_chip.base = bank_nr * STM32_GPIO_PINS_PER_BANK;
		range->name = bank->gpio_chip.label;
		range->id = bank_nr;
		range->pin_base = range->id * STM32_GPIO_PINS_PER_BANK;
		range->base = range->id * STM32_GPIO_PINS_PER_BANK;
		range->npins = npins;
		range->gc = &bank->gpio_chip;
		pinctrl_add_gpio_range(pctl->pctl_dev,
				       &pctl->banks[bank_nr].range);
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "st,bank-ioport", &bank_ioport_nr))
		bank_ioport_nr = bank_nr;

	bank->gpio_chip.base = bank_nr * STM32_GPIO_PINS_PER_BANK;

	bank->gpio_chip.ngpio = npins;
	bank->gpio_chip.of_node = np;
	bank->gpio_chip.parent = dev;
	bank->bank_nr = bank_nr;
	bank->bank_ioport_nr = bank_ioport_nr;
	spin_lock_init(&bank->lock);

	/* create irq hierarchical करोमुख्य */
	bank->fwnode = of_node_to_fwnode(np);

	bank->करोमुख्य = irq_करोमुख्य_create_hierarchy(pctl->करोमुख्य, 0,
					STM32_GPIO_IRQ_LINE, bank->fwnode,
					&sपंचांग32_gpio_करोमुख्य_ops, bank);

	अगर (!bank->करोमुख्य)
		वापस -ENODEV;

	err = gpiochip_add_data(&bank->gpio_chip, bank);
	अगर (err) अणु
		dev_err(dev, "Failed to add gpiochip(%d)!\n", bank_nr);
		वापस err;
	पूर्ण

	dev_info(dev, "%s bank added\n", bank->gpio_chip.label);
	वापस 0;
पूर्ण

अटल काष्ठा irq_करोमुख्य *sपंचांग32_pctrl_get_irq_करोमुख्य(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (!of_find_property(np, "interrupt-parent", शून्य))
		वापस शून्य;

	parent = of_irq_find_parent(np);
	अगर (!parent)
		वापस ERR_PTR(-ENXIO);

	करोमुख्य = irq_find_host(parent);
	अगर (!करोमुख्य)
		/* करोमुख्य not रेजिस्टरed yet */
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस करोमुख्य;
पूर्ण

अटल पूर्णांक sपंचांग32_pctrl_dt_setup_irq(काष्ठा platक्रमm_device *pdev,
			   काष्ठा sपंचांग32_pinctrl *pctl)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *rm;
	पूर्णांक offset, ret, i;
	पूर्णांक mask, mask_width;

	pctl->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(pctl->regmap))
		वापस PTR_ERR(pctl->regmap);

	rm = pctl->regmap;

	ret = of_property_पढ़ो_u32_index(np, "st,syscfg", 1, &offset);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u32_index(np, "st,syscfg", 2, &mask);
	अगर (ret)
		mask = SYSCFG_IRQMUX_MASK;

	mask_width = fls(mask);

	क्रम (i = 0; i < STM32_GPIO_PINS_PER_BANK; i++) अणु
		काष्ठा reg_field mux;

		mux.reg = offset + (i / 4) * 4;
		mux.lsb = (i % 4) * mask_width;
		mux.msb = mux.lsb + mask_width - 1;

		dev_dbg(dev, "irqmux%d: reg:%#x, lsb:%d, msb:%d\n",
			i, mux.reg, mux.lsb, mux.msb);

		pctl->irqmux[i] = devm_regmap_field_alloc(dev, rm, mux);
		अगर (IS_ERR(pctl->irqmux[i]))
			वापस PTR_ERR(pctl->irqmux[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pctrl_build_state(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	pctl->ngroups = pctl->npins;

	/* Allocate groups */
	pctl->groups = devm_kसुस्मृति(&pdev->dev, pctl->ngroups,
				    माप(*pctl->groups), GFP_KERNEL);
	अगर (!pctl->groups)
		वापस -ENOMEM;

	/* We assume that one pin is one group, use pin name as group name. */
	pctl->grp_names = devm_kसुस्मृति(&pdev->dev, pctl->ngroups,
				       माप(*pctl->grp_names), GFP_KERNEL);
	अगर (!pctl->grp_names)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctl->npins; i++) अणु
		स्थिर काष्ठा sपंचांग32_desc_pin *pin = pctl->pins + i;
		काष्ठा sपंचांग32_pinctrl_group *group = pctl->groups + i;

		group->name = pin->pin.name;
		group->pin = pin->pin.number;
		pctl->grp_names[i] = pin->pin.name;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pctrl_create_pins_tab(काष्ठा sपंचांग32_pinctrl *pctl,
				       काष्ठा sपंचांग32_desc_pin *pins)
अणु
	स्थिर काष्ठा sपंचांग32_desc_pin *p;
	पूर्णांक i, nb_pins_available = 0;

	क्रम (i = 0; i < pctl->match_data->npins; i++) अणु
		p = pctl->match_data->pins + i;
		अगर (pctl->pkg && !(pctl->pkg & p->pkg))
			जारी;
		pins->pin = p->pin;
		pins->functions = p->functions;
		pins++;
		nb_pins_available++;
	पूर्ण

	pctl->npins = nb_pins_available;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_pctl_get_package(काष्ठा device_node *np,
				   काष्ठा sपंचांग32_pinctrl *pctl)
अणु
	अगर (of_property_पढ़ो_u32(np, "st,package", &pctl->pkg)) अणु
		pctl->pkg = 0;
		dev_warn(pctl->dev, "No package detected, use default one\n");
	पूर्ण अन्यथा अणु
		dev_dbg(pctl->dev, "package detected: %x\n", pctl->pkg);
	पूर्ण
पूर्ण

पूर्णांक sपंचांग32_pctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_pinctrl *pctl;
	काष्ठा pinctrl_pin_desc *pins;
	पूर्णांक i, ret, hwlock_id, banks = 0;

	अगर (!np)
		वापस -EINVAL;

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match || !match->data)
		वापस -EINVAL;

	अगर (!of_find_property(np, "pins-are-numbered", शून्य)) अणु
		dev_err(dev, "only support pins-are-numbered format\n");
		वापस -EINVAL;
	पूर्ण

	pctl = devm_kzalloc(dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pctl);

	/* check क्रम IRQ controller (may require deferred probe) */
	pctl->करोमुख्य = sपंचांग32_pctrl_get_irq_करोमुख्य(np);
	अगर (IS_ERR(pctl->करोमुख्य))
		वापस PTR_ERR(pctl->करोमुख्य);

	/* hwspinlock is optional */
	hwlock_id = of_hwspin_lock_get_id(pdev->dev.of_node, 0);
	अगर (hwlock_id < 0) अणु
		अगर (hwlock_id == -EPROBE_DEFER)
			वापस hwlock_id;
	पूर्ण अन्यथा अणु
		pctl->hwlock = hwspin_lock_request_specअगरic(hwlock_id);
	पूर्ण

	spin_lock_init(&pctl->irqmux_lock);

	pctl->dev = dev;
	pctl->match_data = match->data;

	/*  get package inक्रमmation */
	sपंचांग32_pctl_get_package(np, pctl);

	pctl->pins = devm_kसुस्मृति(pctl->dev, pctl->match_data->npins,
				  माप(*pctl->pins), GFP_KERNEL);
	अगर (!pctl->pins)
		वापस -ENOMEM;

	ret = sपंचांग32_pctrl_create_pins_tab(pctl, pctl->pins);
	अगर (ret)
		वापस ret;

	ret = sपंचांग32_pctrl_build_state(pdev);
	अगर (ret) अणु
		dev_err(dev, "build state failed: %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	अगर (pctl->करोमुख्य) अणु
		ret = sपंचांग32_pctrl_dt_setup_irq(pdev, pctl);
		अगर (ret)
			वापस ret;
	पूर्ण

	pins = devm_kसुस्मृति(&pdev->dev, pctl->npins, माप(*pins),
			    GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctl->npins; i++)
		pins[i] = pctl->pins[i].pin;

	pctl->pctl_desc.name = dev_name(&pdev->dev);
	pctl->pctl_desc.owner = THIS_MODULE;
	pctl->pctl_desc.pins = pins;
	pctl->pctl_desc.npins = pctl->npins;
	pctl->pctl_desc.link_consumers = true;
	pctl->pctl_desc.confops = &sपंचांग32_pconf_ops;
	pctl->pctl_desc.pctlops = &sपंचांग32_pctrl_ops;
	pctl->pctl_desc.pmxops = &sपंचांग32_pmx_ops;
	pctl->dev = &pdev->dev;

	pctl->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, &pctl->pctl_desc,
					       pctl);

	अगर (IS_ERR(pctl->pctl_dev)) अणु
		dev_err(&pdev->dev, "Failed pinctrl registration\n");
		वापस PTR_ERR(pctl->pctl_dev);
	पूर्ण

	क्रम_each_available_child_of_node(np, child)
		अगर (of_property_पढ़ो_bool(child, "gpio-controller"))
			banks++;

	अगर (!banks) अणु
		dev_err(dev, "at least one GPIO bank is required\n");
		वापस -EINVAL;
	पूर्ण
	pctl->banks = devm_kसुस्मृति(dev, banks, माप(*pctl->banks),
			GFP_KERNEL);
	अगर (!pctl->banks)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा sपंचांग32_gpio_bank *bank = &pctl->banks[i];

		अगर (of_property_पढ़ो_bool(child, "gpio-controller")) अणु
			bank->rstc = of_reset_control_get_exclusive(child,
								    शून्य);
			अगर (PTR_ERR(bank->rstc) == -EPROBE_DEFER) अणु
				of_node_put(child);
				वापस -EPROBE_DEFER;
			पूर्ण

			bank->clk = of_clk_get_by_name(child, शून्य);
			अगर (IS_ERR(bank->clk)) अणु
				अगर (PTR_ERR(bank->clk) != -EPROBE_DEFER)
					dev_err(dev,
						"failed to get clk (%ld)\n",
						PTR_ERR(bank->clk));
				of_node_put(child);
				वापस PTR_ERR(bank->clk);
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	क्रम_each_available_child_of_node(np, child) अणु
		अगर (of_property_पढ़ो_bool(child, "gpio-controller")) अणु
			ret = sपंचांग32_gpiolib_रेजिस्टर_bank(pctl, child);
			अगर (ret) अणु
				of_node_put(child);
				वापस ret;
			पूर्ण

			pctl->nbanks++;
		पूर्ण
	पूर्ण

	dev_info(dev, "Pinctrl STM32 initialized\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_pinctrl_restore_gpio_regs(
					काष्ठा sपंचांग32_pinctrl *pctl, u32 pin)
अणु
	स्थिर काष्ठा pin_desc *desc = pin_desc_get(pctl->pctl_dev, pin);
	u32 val, alt, mode, offset = sपंचांग32_gpio_pin(pin);
	काष्ठा pinctrl_gpio_range *range;
	काष्ठा sपंचांग32_gpio_bank *bank;
	bool pin_is_irq;
	पूर्णांक ret;

	range = pinctrl_find_gpio_range_from_pin(pctl->pctl_dev, pin);
	अगर (!range)
		वापस 0;

	pin_is_irq = gpiochip_line_is_irq(range->gc, offset);

	अगर (!desc || (!pin_is_irq && !desc->gpio_owner))
		वापस 0;

	bank = gpiochip_get_data(range->gc);

	alt = bank->pin_backup[offset] & STM32_GPIO_BKP_ALT_MASK;
	alt >>= STM32_GPIO_BKP_ALT_SHIFT;
	mode = bank->pin_backup[offset] & STM32_GPIO_BKP_MODE_MASK;
	mode >>= STM32_GPIO_BKP_MODE_SHIFT;

	ret = sपंचांग32_pmx_set_mode(bank, offset, mode, alt);
	अगर (ret)
		वापस ret;

	अगर (mode == 1) अणु
		val = bank->pin_backup[offset] & BIT(STM32_GPIO_BKP_VAL);
		val = val >> STM32_GPIO_BKP_VAL;
		__sपंचांग32_gpio_set(bank, offset, val);
	पूर्ण

	val = bank->pin_backup[offset] & BIT(STM32_GPIO_BKP_TYPE);
	val >>= STM32_GPIO_BKP_TYPE;
	ret = sपंचांग32_pconf_set_driving(bank, offset, val);
	अगर (ret)
		वापस ret;

	val = bank->pin_backup[offset] & STM32_GPIO_BKP_SPEED_MASK;
	val >>= STM32_GPIO_BKP_SPEED_SHIFT;
	ret = sपंचांग32_pconf_set_speed(bank, offset, val);
	अगर (ret)
		वापस ret;

	val = bank->pin_backup[offset] & STM32_GPIO_BKP_PUPD_MASK;
	val >>= STM32_GPIO_BKP_PUPD_SHIFT;
	ret = sपंचांग32_pconf_set_bias(bank, offset, val);
	अगर (ret)
		वापस ret;

	अगर (pin_is_irq)
		regmap_field_ग_लिखो(pctl->irqmux[offset], bank->bank_ioport_nr);

	वापस 0;
पूर्ण

पूर्णांक __maybe_unused sपंचांग32_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_pinctrl *pctl = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_pinctrl_group *g = pctl->groups;
	पूर्णांक i;

	क्रम (i = g->pin; i < g->pin + pctl->ngroups; i++)
		sपंचांग32_pinctrl_restore_gpio_regs(pctl, i);

	वापस 0;
पूर्ण
