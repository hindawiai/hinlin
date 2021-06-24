<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-tegra/gpio.c
 *
 * Copyright (c) 2010 Google, Inc
 * Copyright (c) 2011-2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author:
 *	Erik Gilling <konkers@google.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm.h>

#घोषणा GPIO_BANK(x)		((x) >> 5)
#घोषणा GPIO_PORT(x)		(((x) >> 3) & 0x3)
#घोषणा GPIO_BIT(x)		((x) & 0x7)

#घोषणा GPIO_REG(tgi, x)	(GPIO_BANK(x) * tgi->soc->bank_stride + \
					GPIO_PORT(x) * 4)

#घोषणा GPIO_CNF(t, x)		(GPIO_REG(t, x) + 0x00)
#घोषणा GPIO_OE(t, x)		(GPIO_REG(t, x) + 0x10)
#घोषणा GPIO_OUT(t, x)		(GPIO_REG(t, x) + 0X20)
#घोषणा GPIO_IN(t, x)		(GPIO_REG(t, x) + 0x30)
#घोषणा GPIO_INT_STA(t, x)	(GPIO_REG(t, x) + 0x40)
#घोषणा GPIO_INT_ENB(t, x)	(GPIO_REG(t, x) + 0x50)
#घोषणा GPIO_INT_LVL(t, x)	(GPIO_REG(t, x) + 0x60)
#घोषणा GPIO_INT_CLR(t, x)	(GPIO_REG(t, x) + 0x70)
#घोषणा GPIO_DBC_CNT(t, x)	(GPIO_REG(t, x) + 0xF0)


#घोषणा GPIO_MSK_CNF(t, x)	(GPIO_REG(t, x) + t->soc->upper_offset + 0x00)
#घोषणा GPIO_MSK_OE(t, x)	(GPIO_REG(t, x) + t->soc->upper_offset + 0x10)
#घोषणा GPIO_MSK_OUT(t, x)	(GPIO_REG(t, x) + t->soc->upper_offset + 0X20)
#घोषणा GPIO_MSK_DBC_EN(t, x)	(GPIO_REG(t, x) + t->soc->upper_offset + 0x30)
#घोषणा GPIO_MSK_INT_STA(t, x)	(GPIO_REG(t, x) + t->soc->upper_offset + 0x40)
#घोषणा GPIO_MSK_INT_ENB(t, x)	(GPIO_REG(t, x) + t->soc->upper_offset + 0x50)
#घोषणा GPIO_MSK_INT_LVL(t, x)	(GPIO_REG(t, x) + t->soc->upper_offset + 0x60)

#घोषणा GPIO_INT_LVL_MASK		0x010101
#घोषणा GPIO_INT_LVL_EDGE_RISING	0x000101
#घोषणा GPIO_INT_LVL_EDGE_FALLING	0x000100
#घोषणा GPIO_INT_LVL_EDGE_BOTH		0x010100
#घोषणा GPIO_INT_LVL_LEVEL_HIGH		0x000001
#घोषणा GPIO_INT_LVL_LEVEL_LOW		0x000000

काष्ठा tegra_gpio_info;

काष्ठा tegra_gpio_bank अणु
	अचिन्हित पूर्णांक bank;

	/*
	 * IRQ-core code uses raw locking, and thus, nested locking also
	 * should be raw in order not to trip spinlock debug warnings.
	 */
	raw_spinlock_t lvl_lock[4];

	/* Lock क्रम updating debounce count रेजिस्टर */
	spinlock_t dbc_lock[4];

#अगर_घोषित CONFIG_PM_SLEEP
	u32 cnf[4];
	u32 out[4];
	u32 oe[4];
	u32 पूर्णांक_enb[4];
	u32 पूर्णांक_lvl[4];
	u32 wake_enb[4];
	u32 dbc_enb[4];
#पूर्ण_अगर
	u32 dbc_cnt[4];
पूर्ण;

काष्ठा tegra_gpio_soc_config अणु
	bool debounce_supported;
	u32 bank_stride;
	u32 upper_offset;
पूर्ण;

काष्ठा tegra_gpio_info अणु
	काष्ठा device				*dev;
	व्योम __iomem				*regs;
	काष्ठा tegra_gpio_bank			*bank_info;
	स्थिर काष्ठा tegra_gpio_soc_config	*soc;
	काष्ठा gpio_chip			gc;
	काष्ठा irq_chip				ic;
	u32					bank_count;
	अचिन्हित पूर्णांक				*irqs;
पूर्ण;

अटल अंतरभूत व्योम tegra_gpio_ग_लिखोl(काष्ठा tegra_gpio_info *tgi,
				     u32 val, u32 reg)
अणु
	ग_लिखोl_relaxed(val, tgi->regs + reg);
पूर्ण

अटल अंतरभूत u32 tegra_gpio_पढ़ोl(काष्ठा tegra_gpio_info *tgi, u32 reg)
अणु
	वापस पढ़ोl_relaxed(tgi->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक tegra_gpio_compose(अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक port,
				       अचिन्हित पूर्णांक bit)
अणु
	वापस (bank << 5) | ((port & 0x3) << 3) | (bit & 0x7);
पूर्ण

अटल व्योम tegra_gpio_mask_ग_लिखो(काष्ठा tegra_gpio_info *tgi, u32 reg,
				  अचिन्हित पूर्णांक gpio, u32 value)
अणु
	u32 val;

	val = 0x100 << GPIO_BIT(gpio);
	अगर (value)
		val |= 1 << GPIO_BIT(gpio);
	tegra_gpio_ग_लिखोl(tgi, val, reg);
पूर्ण

अटल व्योम tegra_gpio_enable(काष्ठा tegra_gpio_info *tgi, अचिन्हित पूर्णांक gpio)
अणु
	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_CNF(tgi, gpio), gpio, 1);
पूर्ण

अटल व्योम tegra_gpio_disable(काष्ठा tegra_gpio_info *tgi, अचिन्हित पूर्णांक gpio)
अणु
	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_CNF(tgi, gpio), gpio, 0);
पूर्ण

अटल पूर्णांक tegra_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस pinctrl_gpio_request(chip->base + offset);
पूर्ण

अटल व्योम tegra_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);

	pinctrl_gpio_मुक्त(chip->base + offset);
	tegra_gpio_disable(tgi, offset);
पूर्ण

अटल व्योम tegra_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			   पूर्णांक value)
अणु
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);

	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_OUT(tgi, offset), offset, value);
पूर्ण

अटल पूर्णांक tegra_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bval = BIT(GPIO_BIT(offset));

	/* If gpio is in output mode then पढ़ो from the out value */
	अगर (tegra_gpio_पढ़ोl(tgi, GPIO_OE(tgi, offset)) & bval)
		वापस !!(tegra_gpio_पढ़ोl(tgi, GPIO_OUT(tgi, offset)) & bval);

	वापस !!(tegra_gpio_पढ़ोl(tgi, GPIO_IN(tgi, offset)) & bval);
पूर्ण

अटल पूर्णांक tegra_gpio_direction_input(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	पूर्णांक ret;

	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_OE(tgi, offset), offset, 0);
	tegra_gpio_enable(tgi, offset);

	ret = pinctrl_gpio_direction_input(chip->base + offset);
	अगर (ret < 0)
		dev_err(tgi->dev,
			"Failed to set pinctrl input direction of GPIO %d: %d",
			 chip->base + offset, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_gpio_direction_output(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset,
				       पूर्णांक value)
अणु
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	पूर्णांक ret;

	tegra_gpio_set(chip, offset, value);
	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_OE(tgi, offset), offset, 1);
	tegra_gpio_enable(tgi, offset);

	ret = pinctrl_gpio_direction_output(chip->base + offset);
	अगर (ret < 0)
		dev_err(tgi->dev,
			"Failed to set pinctrl output direction of GPIO %d: %d",
			 chip->base + offset, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_gpio_get_direction(काष्ठा gpio_chip *chip,
				    अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	u32 pin_mask = BIT(GPIO_BIT(offset));
	u32 cnf, oe;

	cnf = tegra_gpio_पढ़ोl(tgi, GPIO_CNF(tgi, offset));
	अगर (!(cnf & pin_mask))
		वापस -EINVAL;

	oe = tegra_gpio_पढ़ोl(tgi, GPIO_OE(tgi, offset));

	अगर (oe & pin_mask)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक tegra_gpio_set_debounce(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक debounce)
अणु
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	काष्ठा tegra_gpio_bank *bank = &tgi->bank_info[GPIO_BANK(offset)];
	अचिन्हित पूर्णांक debounce_ms = DIV_ROUND_UP(debounce, 1000);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक port;

	अगर (!debounce_ms) अणु
		tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_DBC_EN(tgi, offset),
				      offset, 0);
		वापस 0;
	पूर्ण

	debounce_ms = min(debounce_ms, 255U);
	port = GPIO_PORT(offset);

	/* There is only one debounce count रेजिस्टर per port and hence
	 * set the maximum of current and requested debounce समय.
	 */
	spin_lock_irqsave(&bank->dbc_lock[port], flags);
	अगर (bank->dbc_cnt[port] < debounce_ms) अणु
		tegra_gpio_ग_लिखोl(tgi, debounce_ms, GPIO_DBC_CNT(tgi, offset));
		bank->dbc_cnt[port] = debounce_ms;
	पूर्ण
	spin_unlock_irqrestore(&bank->dbc_lock[port], flags);

	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_DBC_EN(tgi, offset), offset, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				 अचिन्हित दीर्घ config)
अणु
	u32 debounce;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	वापस tegra_gpio_set_debounce(chip, offset, debounce);
पूर्ण

अटल व्योम tegra_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = d->hwirq;

	tegra_gpio_ग_लिखोl(tgi, 1 << GPIO_BIT(gpio), GPIO_INT_CLR(tgi, gpio));
पूर्ण

अटल व्योम tegra_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = d->hwirq;

	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_INT_ENB(tgi, gpio), gpio, 0);
पूर्ण

अटल व्योम tegra_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = d->hwirq;

	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_INT_ENB(tgi, gpio), gpio, 1);
पूर्ण

अटल पूर्णांक tegra_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक gpio = d->hwirq, port = GPIO_PORT(gpio), lvl_type;
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	काष्ठा tegra_gpio_bank *bank;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 val;

	bank = &tgi->bank_info[GPIO_BANK(d->hwirq)];

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		lvl_type = GPIO_INT_LVL_EDGE_RISING;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		lvl_type = GPIO_INT_LVL_EDGE_FALLING;
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		lvl_type = GPIO_INT_LVL_EDGE_BOTH;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		lvl_type = GPIO_INT_LVL_LEVEL_HIGH;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		lvl_type = GPIO_INT_LVL_LEVEL_LOW;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&bank->lvl_lock[port], flags);

	val = tegra_gpio_पढ़ोl(tgi, GPIO_INT_LVL(tgi, gpio));
	val &= ~(GPIO_INT_LVL_MASK << GPIO_BIT(gpio));
	val |= lvl_type << GPIO_BIT(gpio);
	tegra_gpio_ग_लिखोl(tgi, val, GPIO_INT_LVL(tgi, gpio));

	raw_spin_unlock_irqrestore(&bank->lvl_lock[port], flags);

	tegra_gpio_mask_ग_लिखो(tgi, GPIO_MSK_OE(tgi, gpio), gpio, 0);
	tegra_gpio_enable(tgi, gpio);

	ret = gpiochip_lock_as_irq(&tgi->gc, gpio);
	अगर (ret) अणु
		dev_err(tgi->dev,
			"unable to lock Tegra GPIO %u as IRQ\n", gpio);
		tegra_gpio_disable(tgi, gpio);
		वापस ret;
	पूर्ण

	अगर (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा अगर (type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		irq_set_handler_locked(d, handle_edge_irq);

	अगर (d->parent_data)
		ret = irq_chip_set_type_parent(d, type);

	वापस ret;
पूर्ण

अटल व्योम tegra_gpio_irq_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = d->hwirq;

	tegra_gpio_irq_mask(d);
	gpiochip_unlock_as_irq(&tgi->gc, gpio);
पूर्ण

अटल व्योम tegra_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा tegra_gpio_info *tgi = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irq_करोमुख्य *करोमुख्य = tgi->gc.irq.करोमुख्य;
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा tegra_gpio_bank *bank = शून्य;
	अचिन्हित पूर्णांक port, pin, gpio, i;
	bool unmasked = false;
	अचिन्हित दीर्घ sta;
	u32 lvl;

	क्रम (i = 0; i < tgi->bank_count; i++) अणु
		अगर (tgi->irqs[i] == irq) अणु
			bank = &tgi->bank_info[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(bank == शून्य))
		वापस;

	chained_irq_enter(chip, desc);

	क्रम (port = 0; port < 4; port++) अणु
		gpio = tegra_gpio_compose(bank->bank, port, 0);
		sta = tegra_gpio_पढ़ोl(tgi, GPIO_INT_STA(tgi, gpio)) &
			tegra_gpio_पढ़ोl(tgi, GPIO_INT_ENB(tgi, gpio));
		lvl = tegra_gpio_पढ़ोl(tgi, GPIO_INT_LVL(tgi, gpio));

		क्रम_each_set_bit(pin, &sta, 8) अणु
			tegra_gpio_ग_लिखोl(tgi, 1 << pin,
					  GPIO_INT_CLR(tgi, gpio));

			/* अगर gpio is edge triggered, clear condition
			 * beक्रमe executing the handler so that we करोn't
			 * miss edges
			 */
			अगर (!unmasked && lvl & (0x100 << pin)) अणु
				unmasked = true;
				chained_irq_निकास(chip, desc);
			पूर्ण

			irq = irq_find_mapping(करोमुख्य, gpio + pin);
			अगर (WARN_ON(irq == 0))
				जारी;

			generic_handle_irq(irq);
		पूर्ण
	पूर्ण

	अगर (!unmasked)
		chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक tegra_gpio_child_to_parent_hwirq(काष्ठा gpio_chip *chip,
					    अचिन्हित पूर्णांक hwirq,
					    अचिन्हित पूर्णांक type,
					    अचिन्हित पूर्णांक *parent_hwirq,
					    अचिन्हित पूर्णांक *parent_type)
अणु
	*parent_hwirq = chip->irq.child_offset_to_irq(chip, hwirq);
	*parent_type = type;

	वापस 0;
पूर्ण

अटल व्योम *tegra_gpio_populate_parent_fwspec(काष्ठा gpio_chip *chip,
					       अचिन्हित पूर्णांक parent_hwirq,
					       अचिन्हित पूर्णांक parent_type)
अणु
	काष्ठा irq_fwspec *fwspec;

	fwspec = kदो_स्मृति(माप(*fwspec), GFP_KERNEL);
	अगर (!fwspec)
		वापस शून्य;

	fwspec->fwnode = chip->irq.parent_करोमुख्य->fwnode;
	fwspec->param_count = 3;
	fwspec->param[0] = 0;
	fwspec->param[1] = parent_hwirq;
	fwspec->param[2] = parent_type;

	वापस fwspec;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_gpio_info *tgi = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक b, p;

	क्रम (b = 0; b < tgi->bank_count; b++) अणु
		काष्ठा tegra_gpio_bank *bank = &tgi->bank_info[b];

		क्रम (p = 0; p < ARRAY_SIZE(bank->oe); p++) अणु
			अचिन्हित पूर्णांक gpio = (b << 5) | (p << 3);

			tegra_gpio_ग_लिखोl(tgi, bank->cnf[p],
					  GPIO_CNF(tgi, gpio));

			अगर (tgi->soc->debounce_supported) अणु
				tegra_gpio_ग_लिखोl(tgi, bank->dbc_cnt[p],
						  GPIO_DBC_CNT(tgi, gpio));
				tegra_gpio_ग_लिखोl(tgi, bank->dbc_enb[p],
						  GPIO_MSK_DBC_EN(tgi, gpio));
			पूर्ण

			tegra_gpio_ग_लिखोl(tgi, bank->out[p],
					  GPIO_OUT(tgi, gpio));
			tegra_gpio_ग_लिखोl(tgi, bank->oe[p],
					  GPIO_OE(tgi, gpio));
			tegra_gpio_ग_लिखोl(tgi, bank->पूर्णांक_lvl[p],
					  GPIO_INT_LVL(tgi, gpio));
			tegra_gpio_ग_लिखोl(tgi, bank->पूर्णांक_enb[p],
					  GPIO_INT_ENB(tgi, gpio));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_gpio_info *tgi = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक b, p;

	क्रम (b = 0; b < tgi->bank_count; b++) अणु
		काष्ठा tegra_gpio_bank *bank = &tgi->bank_info[b];

		क्रम (p = 0; p < ARRAY_SIZE(bank->oe); p++) अणु
			अचिन्हित पूर्णांक gpio = (b << 5) | (p << 3);

			bank->cnf[p] = tegra_gpio_पढ़ोl(tgi,
							GPIO_CNF(tgi, gpio));
			bank->out[p] = tegra_gpio_पढ़ोl(tgi,
							GPIO_OUT(tgi, gpio));
			bank->oe[p] = tegra_gpio_पढ़ोl(tgi,
						       GPIO_OE(tgi, gpio));
			अगर (tgi->soc->debounce_supported) अणु
				bank->dbc_enb[p] = tegra_gpio_पढ़ोl(tgi,
						GPIO_MSK_DBC_EN(tgi, gpio));
				bank->dbc_enb[p] = (bank->dbc_enb[p] << 8) |
							bank->dbc_enb[p];
			पूर्ण

			bank->पूर्णांक_enb[p] = tegra_gpio_पढ़ोl(tgi,
						GPIO_INT_ENB(tgi, gpio));
			bank->पूर्णांक_lvl[p] = tegra_gpio_पढ़ोl(tgi,
						GPIO_INT_LVL(tgi, gpio));

			/* Enable gpio irq क्रम wake up source */
			tegra_gpio_ग_लिखोl(tgi, bank->wake_enb[p],
					  GPIO_INT_ENB(tgi, gpio));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_gpio_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);
	काष्ठा tegra_gpio_bank *bank;
	अचिन्हित पूर्णांक gpio = d->hwirq;
	u32 port, bit, mask;
	पूर्णांक err;

	bank = &tgi->bank_info[GPIO_BANK(d->hwirq)];

	port = GPIO_PORT(gpio);
	bit = GPIO_BIT(gpio);
	mask = BIT(bit);

	err = irq_set_irq_wake(tgi->irqs[bank->bank], enable);
	अगर (err)
		वापस err;

	अगर (d->parent_data) अणु
		err = irq_chip_set_wake_parent(d, enable);
		अगर (err) अणु
			irq_set_irq_wake(tgi->irqs[bank->bank], !enable);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (enable)
		bank->wake_enb[port] |= mask;
	अन्यथा
		bank->wake_enb[port] &= ~mask;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tegra_gpio_irq_set_affinity(काष्ठा irq_data *data,
				       स्थिर काष्ठा cpumask *dest,
				       bool क्रमce)
अणु
	अगर (data->parent_data)
		वापस irq_chip_set_affinity_parent(data, dest, क्रमce);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra_gpio_irq_request_resources(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);

	tegra_gpio_enable(tgi, d->hwirq);

	वापस gpiochip_reqres_irq(chip, d->hwirq);
पूर्ण

अटल व्योम tegra_gpio_irq_release_resources(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_gpio_info *tgi = gpiochip_get_data(chip);

	gpiochip_relres_irq(chip, d->hwirq);
	tegra_gpio_enable(tgi, d->hwirq);
पूर्ण

#अगर_घोषित	CONFIG_DEBUG_FS

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

अटल पूर्णांक tegra_dbg_gpio_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा tegra_gpio_info *tgi = dev_get_drvdata(s->निजी);
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < tgi->bank_count; i++) अणु
		क्रम (j = 0; j < 4; j++) अणु
			अचिन्हित पूर्णांक gpio = tegra_gpio_compose(i, j, 0);

			seq_म_लिखो(s,
				"%u:%u %02x %02x %02x %02x %02x %02x %06x\n",
				i, j,
				tegra_gpio_पढ़ोl(tgi, GPIO_CNF(tgi, gpio)),
				tegra_gpio_पढ़ोl(tgi, GPIO_OE(tgi, gpio)),
				tegra_gpio_पढ़ोl(tgi, GPIO_OUT(tgi, gpio)),
				tegra_gpio_पढ़ोl(tgi, GPIO_IN(tgi, gpio)),
				tegra_gpio_पढ़ोl(tgi, GPIO_INT_STA(tgi, gpio)),
				tegra_gpio_पढ़ोl(tgi, GPIO_INT_ENB(tgi, gpio)),
				tegra_gpio_पढ़ोl(tgi, GPIO_INT_LVL(tgi, gpio)));
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tegra_gpio_debuginit(काष्ठा tegra_gpio_info *tgi)
अणु
	debugfs_create_devm_seqfile(tgi->dev, "tegra_gpio", शून्य,
				    tegra_dbg_gpio_show);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम tegra_gpio_debuginit(काष्ठा tegra_gpio_info *tgi)
अणु
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops tegra_gpio_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(tegra_gpio_suspend, tegra_gpio_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_pmc_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-pmc", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_gpio_bank *bank;
	काष्ठा tegra_gpio_info *tgi;
	काष्ठा gpio_irq_chip *irq;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret;

	tgi = devm_kzalloc(&pdev->dev, माप(*tgi), GFP_KERNEL);
	अगर (!tgi)
		वापस -ENODEV;

	tgi->soc = of_device_get_match_data(&pdev->dev);
	tgi->dev = &pdev->dev;

	ret = platक्रमm_irq_count(pdev);
	अगर (ret < 0)
		वापस ret;

	tgi->bank_count = ret;

	अगर (!tgi->bank_count) अणु
		dev_err(&pdev->dev, "Missing IRQ resource\n");
		वापस -ENODEV;
	पूर्ण

	tgi->gc.label			= "tegra-gpio";
	tgi->gc.request			= tegra_gpio_request;
	tgi->gc.मुक्त			= tegra_gpio_मुक्त;
	tgi->gc.direction_input		= tegra_gpio_direction_input;
	tgi->gc.get			= tegra_gpio_get;
	tgi->gc.direction_output	= tegra_gpio_direction_output;
	tgi->gc.set			= tegra_gpio_set;
	tgi->gc.get_direction		= tegra_gpio_get_direction;
	tgi->gc.base			= 0;
	tgi->gc.ngpio			= tgi->bank_count * 32;
	tgi->gc.parent			= &pdev->dev;
	tgi->gc.of_node			= pdev->dev.of_node;

	tgi->ic.name			= "GPIO";
	tgi->ic.irq_ack			= tegra_gpio_irq_ack;
	tgi->ic.irq_mask		= tegra_gpio_irq_mask;
	tgi->ic.irq_unmask		= tegra_gpio_irq_unmask;
	tgi->ic.irq_set_type		= tegra_gpio_irq_set_type;
	tgi->ic.irq_shutकरोwn		= tegra_gpio_irq_shutकरोwn;
#अगर_घोषित CONFIG_PM_SLEEP
	tgi->ic.irq_set_wake		= tegra_gpio_irq_set_wake;
#पूर्ण_अगर
	tgi->ic.irq_request_resources	= tegra_gpio_irq_request_resources;
	tgi->ic.irq_release_resources	= tegra_gpio_irq_release_resources;

	platक्रमm_set_drvdata(pdev, tgi);

	अगर (tgi->soc->debounce_supported)
		tgi->gc.set_config = tegra_gpio_set_config;

	tgi->bank_info = devm_kसुस्मृति(&pdev->dev, tgi->bank_count,
				      माप(*tgi->bank_info), GFP_KERNEL);
	अगर (!tgi->bank_info)
		वापस -ENOMEM;

	tgi->irqs = devm_kसुस्मृति(&pdev->dev, tgi->bank_count,
				 माप(*tgi->irqs), GFP_KERNEL);
	अगर (!tgi->irqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < tgi->bank_count; i++) अणु
		ret = platक्रमm_get_irq(pdev, i);
		अगर (ret < 0)
			वापस ret;

		bank = &tgi->bank_info[i];
		bank->bank = i;

		tgi->irqs[i] = ret;

		क्रम (j = 0; j < 4; j++) अणु
			raw_spin_lock_init(&bank->lvl_lock[j]);
			spin_lock_init(&bank->dbc_lock[j]);
		पूर्ण
	पूर्ण

	irq = &tgi->gc.irq;
	irq->chip = &tgi->ic;
	irq->fwnode = of_node_to_fwnode(pdev->dev.of_node);
	irq->child_to_parent_hwirq = tegra_gpio_child_to_parent_hwirq;
	irq->populate_parent_alloc_arg = tegra_gpio_populate_parent_fwspec;
	irq->handler = handle_simple_irq;
	irq->शेष_type = IRQ_TYPE_NONE;
	irq->parent_handler = tegra_gpio_irq_handler;
	irq->parent_handler_data = tgi;
	irq->num_parents = tgi->bank_count;
	irq->parents = tgi->irqs;

	np = of_find_matching_node(शून्य, tegra_pmc_of_match);
	अगर (np) अणु
		irq->parent_करोमुख्य = irq_find_host(np);
		of_node_put(np);

		अगर (!irq->parent_करोमुख्य)
			वापस -EPROBE_DEFER;

		tgi->ic.irq_set_affinity = tegra_gpio_irq_set_affinity;
	पूर्ण

	tgi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tgi->regs))
		वापस PTR_ERR(tgi->regs);

	क्रम (i = 0; i < tgi->bank_count; i++) अणु
		क्रम (j = 0; j < 4; j++) अणु
			पूर्णांक gpio = tegra_gpio_compose(i, j, 0);

			tegra_gpio_ग_लिखोl(tgi, 0x00, GPIO_INT_ENB(tgi, gpio));
		पूर्ण
	पूर्ण

	ret = devm_gpiochip_add_data(&pdev->dev, &tgi->gc, tgi);
	अगर (ret < 0)
		वापस ret;

	tegra_gpio_debuginit(tgi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_gpio_soc_config tegra20_gpio_config = अणु
	.bank_stride = 0x80,
	.upper_offset = 0x800,
पूर्ण;

अटल स्थिर काष्ठा tegra_gpio_soc_config tegra30_gpio_config = अणु
	.bank_stride = 0x100,
	.upper_offset = 0x80,
पूर्ण;

अटल स्थिर काष्ठा tegra_gpio_soc_config tegra210_gpio_config = अणु
	.debounce_supported = true,
	.bank_stride = 0x100,
	.upper_offset = 0x80,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_gpio_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-gpio", .data = &tegra210_gpio_config पूर्ण,
	अणु .compatible = "nvidia,tegra30-gpio", .data = &tegra30_gpio_config पूर्ण,
	अणु .compatible = "nvidia,tegra20-gpio", .data = &tegra20_gpio_config पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_gpio_of_match);

अटल काष्ठा platक्रमm_driver tegra_gpio_driver = अणु
	.driver = अणु
		.name = "tegra-gpio",
		.pm = &tegra_gpio_pm_ops,
		.of_match_table = tegra_gpio_of_match,
	पूर्ण,
	.probe = tegra_gpio_probe,
पूर्ण;
module_platक्रमm_driver(tegra_gpio_driver);

MODULE_DESCRIPTION("NVIDIA Tegra GPIO controller driver");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_AUTHOR("Erik Gilling <konkers@google.com>");
MODULE_LICENSE("GPL v2");
