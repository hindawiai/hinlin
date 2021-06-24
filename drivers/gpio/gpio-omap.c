<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support functions क्रम OMAP GPIO
 *
 * Copyright (C) 2003-2005 Nokia Corporation
 * Written by Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 *
 * Copyright (C) 2009 Texas Instruments
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_data/gpio-omap.h>

#घोषणा OMAP4_GPIO_DEBOUNCINGTIME_MASK 0xFF

काष्ठा gpio_regs अणु
	u32 sysconfig;
	u32 irqenable1;
	u32 irqenable2;
	u32 wake_en;
	u32 ctrl;
	u32 oe;
	u32 leveldetect0;
	u32 leveldetect1;
	u32 risingdetect;
	u32 fallingdetect;
	u32 dataout;
	u32 debounce;
	u32 debounce_en;
पूर्ण;

काष्ठा gpio_bank अणु
	व्योम __iomem *base;
	स्थिर काष्ठा omap_gpio_reg_offs *regs;

	पूर्णांक irq;
	u32 non_wakeup_gpios;
	u32 enabled_non_wakeup_gpios;
	काष्ठा gpio_regs context;
	u32 saved_datain;
	u32 level_mask;
	u32 toggle_mask;
	raw_spinlock_t lock;
	raw_spinlock_t wa_lock;
	काष्ठा gpio_chip chip;
	काष्ठा clk *dbck;
	काष्ठा notअगरier_block nb;
	अचिन्हित पूर्णांक is_suspended:1;
	अचिन्हित पूर्णांक needs_resume:1;
	u32 mod_usage;
	u32 irq_usage;
	u32 dbck_enable_mask;
	bool dbck_enabled;
	bool is_mpuio;
	bool dbck_flag;
	bool loses_context;
	bool context_valid;
	पूर्णांक stride;
	u32 width;
	पूर्णांक context_loss_count;

	व्योम (*set_dataout)(काष्ठा gpio_bank *bank, अचिन्हित gpio, पूर्णांक enable);
	पूर्णांक (*get_context_loss_count)(काष्ठा device *dev);
पूर्ण;

#घोषणा GPIO_MOD_CTRL_BIT	BIT(0)

#घोषणा BANK_USED(bank) (bank->mod_usage || bank->irq_usage)
#घोषणा LINE_USED(line, offset) (line & (BIT(offset)))

अटल व्योम omap_gpio_unmask_irq(काष्ठा irq_data *d);

अटल अंतरभूत काष्ठा gpio_bank *omap_irq_data_get_bank(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	वापस gpiochip_get_data(chip);
पूर्ण

अटल अंतरभूत u32 omap_gpio_rmw(व्योम __iomem *reg, u32 mask, bool set)
अणु
	u32 val = पढ़ोl_relaxed(reg);

	अगर (set)
		val |= mask;
	अन्यथा
		val &= ~mask;

	ग_लिखोl_relaxed(val, reg);

	वापस val;
पूर्ण

अटल व्योम omap_set_gpio_direction(काष्ठा gpio_bank *bank, पूर्णांक gpio,
				    पूर्णांक is_input)
अणु
	bank->context.oe = omap_gpio_rmw(bank->base + bank->regs->direction,
					 BIT(gpio), is_input);
पूर्ण


/* set data out value using dedicate set/clear रेजिस्टर */
अटल व्योम omap_set_gpio_dataout_reg(काष्ठा gpio_bank *bank, अचिन्हित offset,
				      पूर्णांक enable)
अणु
	व्योम __iomem *reg = bank->base;
	u32 l = BIT(offset);

	अगर (enable) अणु
		reg += bank->regs->set_dataout;
		bank->context.dataout |= l;
	पूर्ण अन्यथा अणु
		reg += bank->regs->clr_dataout;
		bank->context.dataout &= ~l;
	पूर्ण

	ग_लिखोl_relaxed(l, reg);
पूर्ण

/* set data out value using mask रेजिस्टर */
अटल व्योम omap_set_gpio_dataout_mask(काष्ठा gpio_bank *bank, अचिन्हित offset,
				       पूर्णांक enable)
अणु
	bank->context.dataout = omap_gpio_rmw(bank->base + bank->regs->dataout,
					      BIT(offset), enable);
पूर्ण

अटल अंतरभूत व्योम omap_gpio_dbck_enable(काष्ठा gpio_bank *bank)
अणु
	अगर (bank->dbck_enable_mask && !bank->dbck_enabled) अणु
		clk_enable(bank->dbck);
		bank->dbck_enabled = true;

		ग_लिखोl_relaxed(bank->dbck_enable_mask,
			     bank->base + bank->regs->debounce_en);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम omap_gpio_dbck_disable(काष्ठा gpio_bank *bank)
अणु
	अगर (bank->dbck_enable_mask && bank->dbck_enabled) अणु
		/*
		 * Disable debounce beक्रमe cutting it's घड़ी. If debounce is
		 * enabled but the घड़ी is not, GPIO module seems to be unable
		 * to detect events and generate पूर्णांकerrupts at least on OMAP3.
		 */
		ग_लिखोl_relaxed(0, bank->base + bank->regs->debounce_en);

		clk_disable(bank->dbck);
		bank->dbck_enabled = false;
	पूर्ण
पूर्ण

/**
 * omap2_set_gpio_debounce - low level gpio debounce समय
 * @bank: the gpio bank we're acting upon
 * @offset: the gpio number on this @bank
 * @debounce: debounce समय to use
 *
 * OMAP's debounce समय is in 31us steps
 *   <debounce समय> = (GPIO_DEBOUNCINGTIME[7:0].DEBOUNCETIME + 1) x 31
 * so we need to convert and round up to the बंदst unit.
 *
 * Return: 0 on success, negative error otherwise.
 */
अटल पूर्णांक omap2_set_gpio_debounce(काष्ठा gpio_bank *bank, अचिन्हित offset,
				   अचिन्हित debounce)
अणु
	u32			val;
	u32			l;
	bool			enable = !!debounce;

	अगर (!bank->dbck_flag)
		वापस -ENOTSUPP;

	अगर (enable) अणु
		debounce = DIV_ROUND_UP(debounce, 31) - 1;
		अगर ((debounce & OMAP4_GPIO_DEBOUNCINGTIME_MASK) != debounce)
			वापस -EINVAL;
	पूर्ण

	l = BIT(offset);

	clk_enable(bank->dbck);
	ग_लिखोl_relaxed(debounce, bank->base + bank->regs->debounce);

	val = omap_gpio_rmw(bank->base + bank->regs->debounce_en, l, enable);
	bank->dbck_enable_mask = val;

	clk_disable(bank->dbck);
	/*
	 * Enable debounce घड़ी per module.
	 * This call is mandatory because in omap_gpio_request() when
	 * *_runसमय_get_sync() is called,  _gpio_dbck_enable() within
	 * runसमय callbck fails to turn on dbck because dbck_enable_mask
	 * used within _gpio_dbck_enable() is still not initialized at
	 * that poपूर्णांक. Thereक्रमe we have to enable dbck here.
	 */
	omap_gpio_dbck_enable(bank);
	अगर (bank->dbck_enable_mask) अणु
		bank->context.debounce = debounce;
		bank->context.debounce_en = val;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap_clear_gpio_debounce - clear debounce settings क्रम a gpio
 * @bank: the gpio bank we're acting upon
 * @offset: the gpio number on this @bank
 *
 * If a gpio is using debounce, then clear the debounce enable bit and अगर
 * this is the only gpio in this bank using debounce, then clear the debounce
 * समय too. The debounce घड़ी will also be disabled when calling this function
 * अगर this is the only gpio in the bank using debounce.
 */
अटल व्योम omap_clear_gpio_debounce(काष्ठा gpio_bank *bank, अचिन्हित offset)
अणु
	u32 gpio_bit = BIT(offset);

	अगर (!bank->dbck_flag)
		वापस;

	अगर (!(bank->dbck_enable_mask & gpio_bit))
		वापस;

	bank->dbck_enable_mask &= ~gpio_bit;
	bank->context.debounce_en &= ~gpio_bit;
        ग_लिखोl_relaxed(bank->context.debounce_en,
		     bank->base + bank->regs->debounce_en);

	अगर (!bank->dbck_enable_mask) अणु
		bank->context.debounce = 0;
		ग_लिखोl_relaxed(bank->context.debounce, bank->base +
			     bank->regs->debounce);
		clk_disable(bank->dbck);
		bank->dbck_enabled = false;
	पूर्ण
पूर्ण

/*
 * Off mode wake-up capable GPIOs in bank(s) that are in the wakeup करोमुख्य.
 * See TRM section क्रम GPIO क्रम "Wake-Up Generation" क्रम the list of GPIOs
 * in wakeup करोमुख्य. If bank->non_wakeup_gpios is not configured, assume none
 * are capable waking up the प्रणाली from off mode.
 */
अटल bool omap_gpio_is_off_wakeup_capable(काष्ठा gpio_bank *bank, u32 gpio_mask)
अणु
	u32 no_wake = bank->non_wakeup_gpios;

	अगर (no_wake)
		वापस !!(~no_wake & gpio_mask);

	वापस false;
पूर्ण

अटल अंतरभूत व्योम omap_set_gpio_trigger(काष्ठा gpio_bank *bank, पूर्णांक gpio,
						अचिन्हित trigger)
अणु
	व्योम __iomem *base = bank->base;
	u32 gpio_bit = BIT(gpio);

	omap_gpio_rmw(base + bank->regs->leveldetect0, gpio_bit,
		      trigger & IRQ_TYPE_LEVEL_LOW);
	omap_gpio_rmw(base + bank->regs->leveldetect1, gpio_bit,
		      trigger & IRQ_TYPE_LEVEL_HIGH);

	/*
	 * We need the edge detection enabled क्रम to allow the GPIO block
	 * to be woken from idle state.  Set the appropriate edge detection
	 * in addition to the level detection.
	 */
	omap_gpio_rmw(base + bank->regs->risingdetect, gpio_bit,
		      trigger & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_LEVEL_HIGH));
	omap_gpio_rmw(base + bank->regs->fallingdetect, gpio_bit,
		      trigger & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_LEVEL_LOW));

	bank->context.leveldetect0 =
			पढ़ोl_relaxed(bank->base + bank->regs->leveldetect0);
	bank->context.leveldetect1 =
			पढ़ोl_relaxed(bank->base + bank->regs->leveldetect1);
	bank->context.risingdetect =
			पढ़ोl_relaxed(bank->base + bank->regs->risingdetect);
	bank->context.fallingdetect =
			पढ़ोl_relaxed(bank->base + bank->regs->fallingdetect);

	bank->level_mask = bank->context.leveldetect0 |
			   bank->context.leveldetect1;

	/* This part needs to be executed always क्रम OMAPअणु34xx, 44xxपूर्ण */
	अगर (!bank->regs->irqctrl && !omap_gpio_is_off_wakeup_capable(bank, gpio)) अणु
		/*
		 * Log the edge gpio and manually trigger the IRQ
		 * after resume अगर the input level changes
		 * to aव्योम irq lost during PER RET/OFF mode
		 * Applies क्रम omap2 non-wakeup gpio and all omap3 gpios
		 */
		अगर (trigger & IRQ_TYPE_EDGE_BOTH)
			bank->enabled_non_wakeup_gpios |= gpio_bit;
		अन्यथा
			bank->enabled_non_wakeup_gpios &= ~gpio_bit;
	पूर्ण
पूर्ण

/*
 * This only applies to chips that can't करो both rising and falling edge
 * detection at once.  For all other chips, this function is a noop.
 */
अटल व्योम omap_toggle_gpio_edge_triggering(काष्ठा gpio_bank *bank, पूर्णांक gpio)
अणु
	अगर (IS_ENABLED(CONFIG_ARCH_OMAP1) && bank->regs->irqctrl) अणु
		व्योम __iomem *reg = bank->base + bank->regs->irqctrl;

		ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) ^ BIT(gpio), reg);
	पूर्ण
पूर्ण

अटल पूर्णांक omap_set_gpio_triggering(काष्ठा gpio_bank *bank, पूर्णांक gpio,
				    अचिन्हित trigger)
अणु
	व्योम __iomem *reg = bank->base;
	u32 l = 0;

	अगर (bank->regs->leveldetect0 && bank->regs->wkup_en) अणु
		omap_set_gpio_trigger(bank, gpio, trigger);
	पूर्ण अन्यथा अगर (bank->regs->irqctrl) अणु
		reg += bank->regs->irqctrl;

		l = पढ़ोl_relaxed(reg);
		अगर ((trigger & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_BOTH)
			bank->toggle_mask |= BIT(gpio);
		अगर (trigger & IRQ_TYPE_EDGE_RISING)
			l |= BIT(gpio);
		अन्यथा अगर (trigger & IRQ_TYPE_EDGE_FALLING)
			l &= ~(BIT(gpio));
		अन्यथा
			वापस -EINVAL;

		ग_लिखोl_relaxed(l, reg);
	पूर्ण अन्यथा अगर (bank->regs->edgectrl1) अणु
		अगर (gpio & 0x08)
			reg += bank->regs->edgectrl2;
		अन्यथा
			reg += bank->regs->edgectrl1;

		gpio &= 0x07;
		l = पढ़ोl_relaxed(reg);
		l &= ~(3 << (gpio << 1));
		अगर (trigger & IRQ_TYPE_EDGE_RISING)
			l |= 2 << (gpio << 1);
		अगर (trigger & IRQ_TYPE_EDGE_FALLING)
			l |= BIT(gpio << 1);
		ग_लिखोl_relaxed(l, reg);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम omap_enable_gpio_module(काष्ठा gpio_bank *bank, अचिन्हित offset)
अणु
	अगर (bank->regs->pinctrl) अणु
		व्योम __iomem *reg = bank->base + bank->regs->pinctrl;

		/* Claim the pin क्रम MPU */
		ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) | (BIT(offset)), reg);
	पूर्ण

	अगर (bank->regs->ctrl && !BANK_USED(bank)) अणु
		व्योम __iomem *reg = bank->base + bank->regs->ctrl;
		u32 ctrl;

		ctrl = पढ़ोl_relaxed(reg);
		/* Module is enabled, घड़ीs are not gated */
		ctrl &= ~GPIO_MOD_CTRL_BIT;
		ग_लिखोl_relaxed(ctrl, reg);
		bank->context.ctrl = ctrl;
	पूर्ण
पूर्ण

अटल व्योम omap_disable_gpio_module(काष्ठा gpio_bank *bank, अचिन्हित offset)
अणु
	अगर (bank->regs->ctrl && !BANK_USED(bank)) अणु
		व्योम __iomem *reg = bank->base + bank->regs->ctrl;
		u32 ctrl;

		ctrl = पढ़ोl_relaxed(reg);
		/* Module is disabled, घड़ीs are gated */
		ctrl |= GPIO_MOD_CTRL_BIT;
		ग_लिखोl_relaxed(ctrl, reg);
		bank->context.ctrl = ctrl;
	पूर्ण
पूर्ण

अटल पूर्णांक omap_gpio_is_input(काष्ठा gpio_bank *bank, अचिन्हित offset)
अणु
	व्योम __iomem *reg = bank->base + bank->regs->direction;

	वापस पढ़ोl_relaxed(reg) & BIT(offset);
पूर्ण

अटल व्योम omap_gpio_init_irq(काष्ठा gpio_bank *bank, अचिन्हित offset)
अणु
	अगर (!LINE_USED(bank->mod_usage, offset)) अणु
		omap_enable_gpio_module(bank, offset);
		omap_set_gpio_direction(bank, offset, 1);
	पूर्ण
	bank->irq_usage |= BIT(offset);
पूर्ण

अटल पूर्णांक omap_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित type)
अणु
	काष्ठा gpio_bank *bank = omap_irq_data_get_bank(d);
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;
	अचिन्हित offset = d->hwirq;

	अगर (type & ~IRQ_TYPE_SENSE_MASK)
		वापस -EINVAL;

	अगर (!bank->regs->leveldetect0 &&
		(type & (IRQ_TYPE_LEVEL_LOW|IRQ_TYPE_LEVEL_HIGH)))
		वापस -EINVAL;

	raw_spin_lock_irqsave(&bank->lock, flags);
	retval = omap_set_gpio_triggering(bank, offset, type);
	अगर (retval) अणु
		raw_spin_unlock_irqrestore(&bank->lock, flags);
		जाओ error;
	पूर्ण
	omap_gpio_init_irq(bank, offset);
	अगर (!omap_gpio_is_input(bank, offset)) अणु
		raw_spin_unlock_irqrestore(&bank->lock, flags);
		retval = -EINVAL;
		जाओ error;
	पूर्ण
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	अगर (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा अगर (type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		/*
		 * Edge IRQs are alपढ़ोy cleared/acked in irq_handler and
		 * not need to be masked, as result handle_edge_irq()
		 * logic is excessed here and may cause lose of पूर्णांकerrupts.
		 * So just use handle_simple_irq.
		 */
		irq_set_handler_locked(d, handle_simple_irq);

	वापस 0;

error:
	वापस retval;
पूर्ण

अटल व्योम omap_clear_gpio_irqbank(काष्ठा gpio_bank *bank, पूर्णांक gpio_mask)
अणु
	व्योम __iomem *reg = bank->base;

	reg += bank->regs->irqstatus;
	ग_लिखोl_relaxed(gpio_mask, reg);

	/* Workaround क्रम clearing DSP GPIO पूर्णांकerrupts to allow retention */
	अगर (bank->regs->irqstatus2) अणु
		reg = bank->base + bank->regs->irqstatus2;
		ग_लिखोl_relaxed(gpio_mask, reg);
	पूर्ण

	/* Flush posted ग_लिखो क्रम the irq status to aव्योम spurious पूर्णांकerrupts */
	पढ़ोl_relaxed(reg);
पूर्ण

अटल अंतरभूत व्योम omap_clear_gpio_irqstatus(काष्ठा gpio_bank *bank,
					     अचिन्हित offset)
अणु
	omap_clear_gpio_irqbank(bank, BIT(offset));
पूर्ण

अटल u32 omap_get_gpio_irqbank_mask(काष्ठा gpio_bank *bank)
अणु
	व्योम __iomem *reg = bank->base;
	u32 l;
	u32 mask = (BIT(bank->width)) - 1;

	reg += bank->regs->irqenable;
	l = पढ़ोl_relaxed(reg);
	अगर (bank->regs->irqenable_inv)
		l = ~l;
	l &= mask;
	वापस l;
पूर्ण

अटल अंतरभूत व्योम omap_set_gpio_irqenable(काष्ठा gpio_bank *bank,
					   अचिन्हित offset, पूर्णांक enable)
अणु
	व्योम __iomem *reg = bank->base;
	u32 gpio_mask = BIT(offset);

	अगर (bank->regs->set_irqenable && bank->regs->clr_irqenable) अणु
		अगर (enable) अणु
			reg += bank->regs->set_irqenable;
			bank->context.irqenable1 |= gpio_mask;
		पूर्ण अन्यथा अणु
			reg += bank->regs->clr_irqenable;
			bank->context.irqenable1 &= ~gpio_mask;
		पूर्ण
		ग_लिखोl_relaxed(gpio_mask, reg);
	पूर्ण अन्यथा अणु
		bank->context.irqenable1 =
			omap_gpio_rmw(reg + bank->regs->irqenable, gpio_mask,
				      enable ^ bank->regs->irqenable_inv);
	पूर्ण

	/*
	 * Program GPIO wakeup aदीर्घ with IRQ enable to satisfy OMAP4430 TRM
	 * note requiring correlation between the IRQ enable रेजिस्टरs and
	 * the wakeup रेजिस्टरs.  In any हाल, we want wakeup from idle
	 * enabled क्रम the GPIOs which support this feature.
	 */
	अगर (bank->regs->wkup_en &&
	    (bank->regs->edgectrl1 || !(bank->non_wakeup_gpios & gpio_mask))) अणु
		bank->context.wake_en =
			omap_gpio_rmw(bank->base + bank->regs->wkup_en,
				      gpio_mask, enable);
	पूर्ण
पूर्ण

/* Use disable_irq_wake() and enable_irq_wake() functions from drivers */
अटल पूर्णांक omap_gpio_wake_enable(काष्ठा irq_data *d, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा gpio_bank *bank = omap_irq_data_get_bank(d);

	वापस irq_set_irq_wake(bank->irq, enable);
पूर्ण

/*
 * We need to unmask the GPIO bank पूर्णांकerrupt as soon as possible to
 * aव्योम missing GPIO पूर्णांकerrupts क्रम other lines in the bank.
 * Then we need to mask-पढ़ो-clear-unmask the triggered GPIO lines
 * in the bank to aव्योम missing nested पूर्णांकerrupts क्रम a GPIO line.
 * If we रुको to unmask inभागidual GPIO lines in the bank after the
 * line's पूर्णांकerrupt handler has been run, we may miss some nested
 * पूर्णांकerrupts.
 */
अटल irqवापस_t omap_gpio_irq_handler(पूर्णांक irq, व्योम *gpiobank)
अणु
	व्योम __iomem *isr_reg = शून्य;
	u32 enabled, isr, edge;
	अचिन्हित पूर्णांक bit;
	काष्ठा gpio_bank *bank = gpiobank;
	अचिन्हित दीर्घ wa_lock_flags;
	अचिन्हित दीर्घ lock_flags;

	isr_reg = bank->base + bank->regs->irqstatus;
	अगर (WARN_ON(!isr_reg))
		जाओ निकास;

	अगर (WARN_ONCE(!pm_runसमय_active(bank->chip.parent),
		      "gpio irq%i while runtime suspended?\n", irq))
		वापस IRQ_NONE;

	जबतक (1) अणु
		raw_spin_lock_irqsave(&bank->lock, lock_flags);

		enabled = omap_get_gpio_irqbank_mask(bank);
		isr = पढ़ोl_relaxed(isr_reg) & enabled;

		/*
		 * Clear edge sensitive पूर्णांकerrupts beक्रमe calling handler(s)
		 * so subsequent edge transitions are not missed जबतक the
		 * handlers are running.
		 */
		edge = isr & ~bank->level_mask;
		अगर (edge)
			omap_clear_gpio_irqbank(bank, edge);

		raw_spin_unlock_irqrestore(&bank->lock, lock_flags);

		अगर (!isr)
			अवरोध;

		जबतक (isr) अणु
			bit = __ffs(isr);
			isr &= ~(BIT(bit));

			raw_spin_lock_irqsave(&bank->lock, lock_flags);
			/*
			 * Some chips can't respond to both rising and falling
			 * at the same समय.  If this irq was requested with
			 * both flags, we need to flip the ICR data क्रम the IRQ
			 * to respond to the IRQ क्रम the opposite direction.
			 * This will be indicated in the bank toggle_mask.
			 */
			अगर (bank->toggle_mask & (BIT(bit)))
				omap_toggle_gpio_edge_triggering(bank, bit);

			raw_spin_unlock_irqrestore(&bank->lock, lock_flags);

			raw_spin_lock_irqsave(&bank->wa_lock, wa_lock_flags);

			generic_handle_irq(irq_find_mapping(bank->chip.irq.करोमुख्य,
							    bit));

			raw_spin_unlock_irqrestore(&bank->wa_lock,
						   wa_lock_flags);
		पूर्ण
	पूर्ण
निकास:
	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक omap_gpio_irq_startup(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_bank *bank = omap_irq_data_get_bank(d);
	अचिन्हित दीर्घ flags;
	अचिन्हित offset = d->hwirq;

	raw_spin_lock_irqsave(&bank->lock, flags);

	अगर (!LINE_USED(bank->mod_usage, offset))
		omap_set_gpio_direction(bank, offset, 1);
	omap_enable_gpio_module(bank, offset);
	bank->irq_usage |= BIT(offset);

	raw_spin_unlock_irqrestore(&bank->lock, flags);
	omap_gpio_unmask_irq(d);

	वापस 0;
पूर्ण

अटल व्योम omap_gpio_irq_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_bank *bank = omap_irq_data_get_bank(d);
	अचिन्हित दीर्घ flags;
	अचिन्हित offset = d->hwirq;

	raw_spin_lock_irqsave(&bank->lock, flags);
	bank->irq_usage &= ~(BIT(offset));
	omap_set_gpio_triggering(bank, offset, IRQ_TYPE_NONE);
	omap_clear_gpio_irqstatus(bank, offset);
	omap_set_gpio_irqenable(bank, offset, 0);
	अगर (!LINE_USED(bank->mod_usage, offset))
		omap_clear_gpio_debounce(bank, offset);
	omap_disable_gpio_module(bank, offset);
	raw_spin_unlock_irqrestore(&bank->lock, flags);
पूर्ण

अटल व्योम omap_gpio_irq_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_bank *bank = omap_irq_data_get_bank(data);

	pm_runसमय_get_sync(bank->chip.parent);
पूर्ण

अटल व्योम gpio_irq_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_bank *bank = omap_irq_data_get_bank(data);

	pm_runसमय_put(bank->chip.parent);
पूर्ण

अटल व्योम omap_gpio_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_bank *bank = omap_irq_data_get_bank(d);
	अचिन्हित offset = d->hwirq;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_set_gpio_triggering(bank, offset, IRQ_TYPE_NONE);
	omap_set_gpio_irqenable(bank, offset, 0);
	raw_spin_unlock_irqrestore(&bank->lock, flags);
पूर्ण

अटल व्योम omap_gpio_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_bank *bank = omap_irq_data_get_bank(d);
	अचिन्हित offset = d->hwirq;
	u32 trigger = irqd_get_trigger_type(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_set_gpio_irqenable(bank, offset, 1);

	/*
	 * For level-triggered GPIOs, clearing must be करोne after the source
	 * is cleared, thus after the handler has run. OMAP4 needs this करोne
	 * after enabing the पूर्णांकerrupt to clear the wakeup status.
	 */
	अगर (bank->regs->leveldetect0 && bank->regs->wkup_en &&
	    trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW))
		omap_clear_gpio_irqstatus(bank, offset);

	अगर (trigger)
		omap_set_gpio_triggering(bank, offset, trigger);

	raw_spin_unlock_irqrestore(&bank->lock, flags);
पूर्ण

/*---------------------------------------------------------------------*/

अटल पूर्णांक omap_mpuio_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा gpio_bank	*bank = dev_get_drvdata(dev);
	व्योम __iomem		*mask_reg = bank->base +
					OMAP_MPUIO_GPIO_MASKIT / bank->stride;
	अचिन्हित दीर्घ		flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	ग_लिखोl_relaxed(0xffff & ~bank->context.wake_en, mask_reg);
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mpuio_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा gpio_bank	*bank = dev_get_drvdata(dev);
	व्योम __iomem		*mask_reg = bank->base +
					OMAP_MPUIO_GPIO_MASKIT / bank->stride;
	अचिन्हित दीर्घ		flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	ग_लिखोl_relaxed(bank->context.wake_en, mask_reg);
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_mpuio_dev_pm_ops = अणु
	.suspend_noirq = omap_mpuio_suspend_noirq,
	.resume_noirq = omap_mpuio_resume_noirq,
पूर्ण;

/* use platक्रमm_driver क्रम this. */
अटल काष्ठा platक्रमm_driver omap_mpuio_driver = अणु
	.driver		= अणु
		.name	= "mpuio",
		.pm	= &omap_mpuio_dev_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device omap_mpuio_device = अणु
	.name		= "mpuio",
	.id		= -1,
	.dev = अणु
		.driver = &omap_mpuio_driver.driver,
	पूर्ण
	/* could list the /proc/iomem resources */
पूर्ण;

अटल अंतरभूत व्योम omap_mpuio_init(काष्ठा gpio_bank *bank)
अणु
	platक्रमm_set_drvdata(&omap_mpuio_device, bank);

	अगर (platक्रमm_driver_रेजिस्टर(&omap_mpuio_driver) == 0)
		(व्योम) platक्रमm_device_रेजिस्टर(&omap_mpuio_device);
पूर्ण

/*---------------------------------------------------------------------*/

अटल पूर्णांक omap_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_bank *bank = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(chip->parent);

	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_enable_gpio_module(bank, offset);
	bank->mod_usage |= BIT(offset);
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम omap_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_bank *bank = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	bank->mod_usage &= ~(BIT(offset));
	अगर (!LINE_USED(bank->irq_usage, offset)) अणु
		omap_set_gpio_direction(bank, offset, 1);
		omap_clear_gpio_debounce(bank, offset);
	पूर्ण
	omap_disable_gpio_module(bank, offset);
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	pm_runसमय_put(chip->parent);
पूर्ण

अटल पूर्णांक omap_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_bank *bank = gpiochip_get_data(chip);

	अगर (पढ़ोl_relaxed(bank->base + bank->regs->direction) & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक omap_gpio_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_bank *bank;
	अचिन्हित दीर्घ flags;

	bank = gpiochip_get_data(chip);
	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_set_gpio_direction(bank, offset, 1);
	raw_spin_unlock_irqrestore(&bank->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_bank *bank = gpiochip_get_data(chip);
	व्योम __iomem *reg;

	अगर (omap_gpio_is_input(bank, offset))
		reg = bank->base + bank->regs->datain;
	अन्यथा
		reg = bank->base + bank->regs->dataout;

	वापस (पढ़ोl_relaxed(reg) & BIT(offset)) != 0;
पूर्ण

अटल पूर्णांक omap_gpio_output(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा gpio_bank *bank;
	अचिन्हित दीर्घ flags;

	bank = gpiochip_get_data(chip);
	raw_spin_lock_irqsave(&bank->lock, flags);
	bank->set_dataout(bank, offset, value);
	omap_set_gpio_direction(bank, offset, 0);
	raw_spin_unlock_irqrestore(&bank->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_gpio_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				  अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_bank *bank = gpiochip_get_data(chip);
	व्योम __iomem *base = bank->base;
	u32 direction, m, val = 0;

	direction = पढ़ोl_relaxed(base + bank->regs->direction);

	m = direction & *mask;
	अगर (m)
		val |= पढ़ोl_relaxed(base + bank->regs->datain) & m;

	m = ~direction & *mask;
	अगर (m)
		val |= पढ़ोl_relaxed(base + bank->regs->dataout) & m;

	*bits = val;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_gpio_debounce(काष्ठा gpio_chip *chip, अचिन्हित offset,
			      अचिन्हित debounce)
अणु
	काष्ठा gpio_bank *bank;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	bank = gpiochip_get_data(chip);

	raw_spin_lock_irqsave(&bank->lock, flags);
	ret = omap2_set_gpio_debounce(bank, offset, debounce);
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	अगर (ret)
		dev_info(chip->parent,
			 "Could not set line %u debounce to %u microseconds (%d)",
			 offset, debounce, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित offset,
				अचिन्हित दीर्घ config)
अणु
	u32 debounce;
	पूर्णांक ret = -ENOTSUPP;

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ret = gpiochip_generic_config(chip, offset, config);
		अवरोध;
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		debounce = pinconf_to_config_argument(config);
		ret = omap_gpio_debounce(chip, offset, debounce);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम omap_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा gpio_bank *bank;
	अचिन्हित दीर्घ flags;

	bank = gpiochip_get_data(chip);
	raw_spin_lock_irqsave(&bank->lock, flags);
	bank->set_dataout(bank, offset, value);
	raw_spin_unlock_irqrestore(&bank->lock, flags);
पूर्ण

अटल व्योम omap_gpio_set_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				   अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_bank *bank = gpiochip_get_data(chip);
	व्योम __iomem *reg = bank->base + bank->regs->dataout;
	अचिन्हित दीर्घ flags;
	u32 l;

	raw_spin_lock_irqsave(&bank->lock, flags);
	l = (पढ़ोl_relaxed(reg) & ~*mask) | (*bits & *mask);
	ग_लिखोl_relaxed(l, reg);
	bank->context.dataout = l;
	raw_spin_unlock_irqrestore(&bank->lock, flags);
पूर्ण

/*---------------------------------------------------------------------*/

अटल व्योम omap_gpio_show_rev(काष्ठा gpio_bank *bank)
अणु
	अटल bool called;
	u32 rev;

	अगर (called || bank->regs->revision == अच_लघु_उच्च)
		वापस;

	rev = पढ़ोw_relaxed(bank->base + bank->regs->revision);
	pr_info("OMAP GPIO hardware version %d.%d\n",
		(rev >> 4) & 0x0f, rev & 0x0f);

	called = true;
पूर्ण

अटल व्योम omap_gpio_mod_init(काष्ठा gpio_bank *bank)
अणु
	व्योम __iomem *base = bank->base;
	u32 l = 0xffffffff;

	अगर (bank->width == 16)
		l = 0xffff;

	अगर (bank->is_mpuio) अणु
		ग_लिखोl_relaxed(l, bank->base + bank->regs->irqenable);
		वापस;
	पूर्ण

	omap_gpio_rmw(base + bank->regs->irqenable, l,
		      bank->regs->irqenable_inv);
	omap_gpio_rmw(base + bank->regs->irqstatus, l,
		      !bank->regs->irqenable_inv);
	अगर (bank->regs->debounce_en)
		ग_लिखोl_relaxed(0, base + bank->regs->debounce_en);

	/* Save OE शेष value (0xffffffff) in the context */
	bank->context.oe = पढ़ोl_relaxed(bank->base + bank->regs->direction);
	 /* Initialize पूर्णांकerface clk ungated, module enabled */
	अगर (bank->regs->ctrl)
		ग_लिखोl_relaxed(0, base + bank->regs->ctrl);
पूर्ण

अटल पूर्णांक omap_gpio_chip_init(काष्ठा gpio_bank *bank, काष्ठा irq_chip *irqc)
अणु
	काष्ठा gpio_irq_chip *irq;
	अटल पूर्णांक gpio;
	स्थिर अक्षर *label;
	पूर्णांक irq_base = 0;
	पूर्णांक ret;

	/*
	 * REVISIT eventually चयन from OMAP-specअगरic gpio काष्ठाs
	 * over to the generic ones
	 */
	bank->chip.request = omap_gpio_request;
	bank->chip.मुक्त = omap_gpio_मुक्त;
	bank->chip.get_direction = omap_gpio_get_direction;
	bank->chip.direction_input = omap_gpio_input;
	bank->chip.get = omap_gpio_get;
	bank->chip.get_multiple = omap_gpio_get_multiple;
	bank->chip.direction_output = omap_gpio_output;
	bank->chip.set_config = omap_gpio_set_config;
	bank->chip.set = omap_gpio_set;
	bank->chip.set_multiple = omap_gpio_set_multiple;
	अगर (bank->is_mpuio) अणु
		bank->chip.label = "mpuio";
		अगर (bank->regs->wkup_en)
			bank->chip.parent = &omap_mpuio_device.dev;
		bank->chip.base = OMAP_MPUIO(0);
	पूर्ण अन्यथा अणु
		label = devm_kaप्र_लिखो(bank->chip.parent, GFP_KERNEL, "gpio-%d-%d",
				       gpio, gpio + bank->width - 1);
		अगर (!label)
			वापस -ENOMEM;
		bank->chip.label = label;
		bank->chip.base = gpio;
	पूर्ण
	bank->chip.ngpio = bank->width;

#अगर_घोषित CONFIG_ARCH_OMAP1
	/*
	 * REVISIT: Once we have OMAP1 supporting SPARSE_IRQ, we can drop
	 * irq_alloc_descs() since a base IRQ offset will no दीर्घer be needed.
	 */
	irq_base = devm_irq_alloc_descs(bank->chip.parent,
					-1, 0, bank->width, 0);
	अगर (irq_base < 0) अणु
		dev_err(bank->chip.parent, "Couldn't allocate IRQ numbers\n");
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर

	/* MPUIO is a bit dअगरferent, पढ़ोing IRQ status clears it */
	अगर (bank->is_mpuio && !bank->regs->wkup_en)
		irqc->irq_set_wake = शून्य;

	irq = &bank->chip.irq;
	irq->chip = irqc;
	irq->handler = handle_bad_irq;
	irq->शेष_type = IRQ_TYPE_NONE;
	irq->num_parents = 1;
	irq->parents = &bank->irq;
	irq->first = irq_base;

	ret = gpiochip_add_data(&bank->chip, bank);
	अगर (ret)
		वापस dev_err_probe(bank->chip.parent, ret, "Could not register gpio chip\n");

	ret = devm_request_irq(bank->chip.parent, bank->irq,
			       omap_gpio_irq_handler,
			       0, dev_name(bank->chip.parent), bank);
	अगर (ret)
		gpiochip_हटाओ(&bank->chip);

	अगर (!bank->is_mpuio)
		gpio += bank->width;

	वापस ret;
पूर्ण

अटल व्योम omap_gpio_init_context(काष्ठा gpio_bank *p)
अणु
	स्थिर काष्ठा omap_gpio_reg_offs *regs = p->regs;
	व्योम __iomem *base = p->base;

	p->context.sysconfig	= पढ़ोl_relaxed(base + regs->sysconfig);
	p->context.ctrl		= पढ़ोl_relaxed(base + regs->ctrl);
	p->context.oe		= पढ़ोl_relaxed(base + regs->direction);
	p->context.wake_en	= पढ़ोl_relaxed(base + regs->wkup_en);
	p->context.leveldetect0	= पढ़ोl_relaxed(base + regs->leveldetect0);
	p->context.leveldetect1	= पढ़ोl_relaxed(base + regs->leveldetect1);
	p->context.risingdetect	= पढ़ोl_relaxed(base + regs->risingdetect);
	p->context.fallingdetect = पढ़ोl_relaxed(base + regs->fallingdetect);
	p->context.irqenable1	= पढ़ोl_relaxed(base + regs->irqenable);
	p->context.irqenable2	= पढ़ोl_relaxed(base + regs->irqenable2);
	p->context.dataout	= पढ़ोl_relaxed(base + regs->dataout);

	p->context_valid = true;
पूर्ण

अटल व्योम omap_gpio_restore_context(काष्ठा gpio_bank *bank)
अणु
	स्थिर काष्ठा omap_gpio_reg_offs *regs = bank->regs;
	व्योम __iomem *base = bank->base;

	ग_लिखोl_relaxed(bank->context.sysconfig, base + regs->sysconfig);
	ग_लिखोl_relaxed(bank->context.wake_en, base + regs->wkup_en);
	ग_लिखोl_relaxed(bank->context.ctrl, base + regs->ctrl);
	ग_लिखोl_relaxed(bank->context.leveldetect0, base + regs->leveldetect0);
	ग_लिखोl_relaxed(bank->context.leveldetect1, base + regs->leveldetect1);
	ग_लिखोl_relaxed(bank->context.risingdetect, base + regs->risingdetect);
	ग_लिखोl_relaxed(bank->context.fallingdetect, base + regs->fallingdetect);
	ग_लिखोl_relaxed(bank->context.dataout, base + regs->dataout);
	ग_लिखोl_relaxed(bank->context.oe, base + regs->direction);

	अगर (bank->dbck_enable_mask) अणु
		ग_लिखोl_relaxed(bank->context.debounce, base + regs->debounce);
		ग_लिखोl_relaxed(bank->context.debounce_en,
			       base + regs->debounce_en);
	पूर्ण

	ग_लिखोl_relaxed(bank->context.irqenable1, base + regs->irqenable);
	ग_लिखोl_relaxed(bank->context.irqenable2, base + regs->irqenable2);
पूर्ण

अटल व्योम omap_gpio_idle(काष्ठा gpio_bank *bank, bool may_lose_context)
अणु
	काष्ठा device *dev = bank->chip.parent;
	व्योम __iomem *base = bank->base;
	u32 mask, nowake;

	bank->saved_datain = पढ़ोl_relaxed(base + bank->regs->datain);

	/* Save syconfig, it's runसमय value can be dअगरferent from init value */
	अगर (bank->loses_context)
		bank->context.sysconfig = पढ़ोl_relaxed(base + bank->regs->sysconfig);

	अगर (!bank->enabled_non_wakeup_gpios)
		जाओ update_gpio_context_count;

	/* Check क्रम pending EDGE_FALLING, ignore EDGE_BOTH */
	mask = bank->enabled_non_wakeup_gpios & bank->context.fallingdetect;
	mask &= ~bank->context.risingdetect;
	bank->saved_datain |= mask;

	/* Check क्रम pending EDGE_RISING, ignore EDGE_BOTH */
	mask = bank->enabled_non_wakeup_gpios & bank->context.risingdetect;
	mask &= ~bank->context.fallingdetect;
	bank->saved_datain &= ~mask;

	अगर (!may_lose_context)
		जाओ update_gpio_context_count;

	/*
	 * If going to OFF, हटाओ triggering क्रम all wkup करोमुख्य
	 * non-wakeup GPIOs.  Otherwise spurious IRQs will be
	 * generated.  See OMAP2420 Errata item 1.101.
	 */
	अगर (!bank->loses_context && bank->enabled_non_wakeup_gpios) अणु
		nowake = bank->enabled_non_wakeup_gpios;
		omap_gpio_rmw(base + bank->regs->fallingdetect, nowake, ~nowake);
		omap_gpio_rmw(base + bank->regs->risingdetect, nowake, ~nowake);
	पूर्ण

update_gpio_context_count:
	अगर (bank->get_context_loss_count)
		bank->context_loss_count =
				bank->get_context_loss_count(dev);

	omap_gpio_dbck_disable(bank);
पूर्ण

अटल व्योम omap_gpio_unidle(काष्ठा gpio_bank *bank)
अणु
	काष्ठा device *dev = bank->chip.parent;
	u32 l = 0, gen, gen0, gen1;
	पूर्णांक c;

	/*
	 * On the first resume during the probe, the context has not
	 * been initialised and so initialise it now. Also initialise
	 * the context loss count.
	 */
	अगर (bank->loses_context && !bank->context_valid) अणु
		omap_gpio_init_context(bank);

		अगर (bank->get_context_loss_count)
			bank->context_loss_count =
				bank->get_context_loss_count(dev);
	पूर्ण

	omap_gpio_dbck_enable(bank);

	अगर (bank->loses_context) अणु
		अगर (!bank->get_context_loss_count) अणु
			omap_gpio_restore_context(bank);
		पूर्ण अन्यथा अणु
			c = bank->get_context_loss_count(dev);
			अगर (c != bank->context_loss_count) अणु
				omap_gpio_restore_context(bank);
			पूर्ण अन्यथा अणु
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Restore changes करोne क्रम OMAP2420 errata 1.101 */
		ग_लिखोl_relaxed(bank->context.fallingdetect,
			       bank->base + bank->regs->fallingdetect);
		ग_लिखोl_relaxed(bank->context.risingdetect,
			       bank->base + bank->regs->risingdetect);
	पूर्ण

	l = पढ़ोl_relaxed(bank->base + bank->regs->datain);

	/*
	 * Check अगर any of the non-wakeup पूर्णांकerrupt GPIOs have changed
	 * state.  If so, generate an IRQ by software.  This is
	 * horribly racy, but it's the best we can करो to work around
	 * this silicon bug.
	 */
	l ^= bank->saved_datain;
	l &= bank->enabled_non_wakeup_gpios;

	/*
	 * No need to generate IRQs क्रम the rising edge क्रम gpio IRQs
	 * configured with falling edge only; and vice versa.
	 */
	gen0 = l & bank->context.fallingdetect;
	gen0 &= bank->saved_datain;

	gen1 = l & bank->context.risingdetect;
	gen1 &= ~(bank->saved_datain);

	/* FIXME: Consider GPIO IRQs with level detections properly! */
	gen = l & (~(bank->context.fallingdetect) &
					 ~(bank->context.risingdetect));
	/* Consider all GPIO IRQs needed to be updated */
	gen |= gen0 | gen1;

	अगर (gen) अणु
		u32 old0, old1;

		old0 = पढ़ोl_relaxed(bank->base + bank->regs->leveldetect0);
		old1 = पढ़ोl_relaxed(bank->base + bank->regs->leveldetect1);

		अगर (!bank->regs->irqstatus_raw0) अणु
			ग_लिखोl_relaxed(old0 | gen, bank->base +
						bank->regs->leveldetect0);
			ग_लिखोl_relaxed(old1 | gen, bank->base +
						bank->regs->leveldetect1);
		पूर्ण

		अगर (bank->regs->irqstatus_raw0) अणु
			ग_लिखोl_relaxed(old0 | l, bank->base +
						bank->regs->leveldetect0);
			ग_लिखोl_relaxed(old1 | l, bank->base +
						bank->regs->leveldetect1);
		पूर्ण
		ग_लिखोl_relaxed(old0, bank->base + bank->regs->leveldetect0);
		ग_लिखोl_relaxed(old1, bank->base + bank->regs->leveldetect1);
	पूर्ण
पूर्ण

अटल पूर्णांक gpio_omap_cpu_notअगरier(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	काष्ठा gpio_bank *bank;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = NOTIFY_OK;
	u32 isr, mask;

	bank = container_of(nb, काष्ठा gpio_bank, nb);

	raw_spin_lock_irqsave(&bank->lock, flags);
	अगर (bank->is_suspended)
		जाओ out_unlock;

	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		mask = omap_get_gpio_irqbank_mask(bank);
		isr = पढ़ोl_relaxed(bank->base + bank->regs->irqstatus) & mask;
		अगर (isr) अणु
			ret = NOTIFY_BAD;
			अवरोध;
		पूर्ण
		omap_gpio_idle(bank, true);
		अवरोध;
	हाल CPU_CLUSTER_PM_ENTER_FAILED:
	हाल CPU_CLUSTER_PM_EXIT:
		omap_gpio_unidle(bank);
		अवरोध;
	पूर्ण

out_unlock:
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा omap_gpio_reg_offs omap2_gpio_regs = अणु
	.revision =		OMAP24XX_GPIO_REVISION,
	.sysconfig =		OMAP24XX_GPIO_SYSCONFIG,
	.direction =		OMAP24XX_GPIO_OE,
	.datain =		OMAP24XX_GPIO_DATAIN,
	.dataout =		OMAP24XX_GPIO_DATAOUT,
	.set_dataout =		OMAP24XX_GPIO_SETDATAOUT,
	.clr_dataout =		OMAP24XX_GPIO_CLEARDATAOUT,
	.irqstatus =		OMAP24XX_GPIO_IRQSTATUS1,
	.irqstatus2 =		OMAP24XX_GPIO_IRQSTATUS2,
	.irqenable =		OMAP24XX_GPIO_IRQENABLE1,
	.irqenable2 =		OMAP24XX_GPIO_IRQENABLE2,
	.set_irqenable =	OMAP24XX_GPIO_SETIRQENABLE1,
	.clr_irqenable =	OMAP24XX_GPIO_CLEARIRQENABLE1,
	.debounce =		OMAP24XX_GPIO_DEBOUNCE_VAL,
	.debounce_en =		OMAP24XX_GPIO_DEBOUNCE_EN,
	.ctrl =			OMAP24XX_GPIO_CTRL,
	.wkup_en =		OMAP24XX_GPIO_WAKE_EN,
	.leveldetect0 =		OMAP24XX_GPIO_LEVELDETECT0,
	.leveldetect1 =		OMAP24XX_GPIO_LEVELDETECT1,
	.risingdetect =		OMAP24XX_GPIO_RISINGDETECT,
	.fallingdetect =	OMAP24XX_GPIO_FALLINGDETECT,
पूर्ण;

अटल स्थिर काष्ठा omap_gpio_reg_offs omap4_gpio_regs = अणु
	.revision =		OMAP4_GPIO_REVISION,
	.sysconfig =		OMAP4_GPIO_SYSCONFIG,
	.direction =		OMAP4_GPIO_OE,
	.datain =		OMAP4_GPIO_DATAIN,
	.dataout =		OMAP4_GPIO_DATAOUT,
	.set_dataout =		OMAP4_GPIO_SETDATAOUT,
	.clr_dataout =		OMAP4_GPIO_CLEARDATAOUT,
	.irqstatus =		OMAP4_GPIO_IRQSTATUS0,
	.irqstatus2 =		OMAP4_GPIO_IRQSTATUS1,
	.irqstatus_raw0 =	OMAP4_GPIO_IRQSTATUSRAW0,
	.irqstatus_raw1 =	OMAP4_GPIO_IRQSTATUSRAW1,
	.irqenable =		OMAP4_GPIO_IRQSTATUSSET0,
	.irqenable2 =		OMAP4_GPIO_IRQSTATUSSET1,
	.set_irqenable =	OMAP4_GPIO_IRQSTATUSSET0,
	.clr_irqenable =	OMAP4_GPIO_IRQSTATUSCLR0,
	.debounce =		OMAP4_GPIO_DEBOUNCINGTIME,
	.debounce_en =		OMAP4_GPIO_DEBOUNCENABLE,
	.ctrl =			OMAP4_GPIO_CTRL,
	.wkup_en =		OMAP4_GPIO_IRQWAKEN0,
	.leveldetect0 =		OMAP4_GPIO_LEVELDETECT0,
	.leveldetect1 =		OMAP4_GPIO_LEVELDETECT1,
	.risingdetect =		OMAP4_GPIO_RISINGDETECT,
	.fallingdetect =	OMAP4_GPIO_FALLINGDETECT,
पूर्ण;

अटल स्थिर काष्ठा omap_gpio_platक्रमm_data omap2_pdata = अणु
	.regs = &omap2_gpio_regs,
	.bank_width = 32,
	.dbck_flag = false,
पूर्ण;

अटल स्थिर काष्ठा omap_gpio_platक्रमm_data omap3_pdata = अणु
	.regs = &omap2_gpio_regs,
	.bank_width = 32,
	.dbck_flag = true,
पूर्ण;

अटल स्थिर काष्ठा omap_gpio_platक्रमm_data omap4_pdata = अणु
	.regs = &omap4_gpio_regs,
	.bank_width = 32,
	.dbck_flag = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_gpio_match[] = अणु
	अणु
		.compatible = "ti,omap4-gpio",
		.data = &omap4_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap3-gpio",
		.data = &omap3_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap2-gpio",
		.data = &omap2_pdata,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_gpio_match);

अटल पूर्णांक omap_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	स्थिर काष्ठा omap_gpio_platक्रमm_data *pdata;
	काष्ठा gpio_bank *bank;
	काष्ठा irq_chip *irqc;
	पूर्णांक ret;

	pdata = device_get_match_data(dev);

	pdata = pdata ?: dev_get_platdata(dev);
	अगर (!pdata)
		वापस -EINVAL;

	bank = devm_kzalloc(dev, माप(*bank), GFP_KERNEL);
	अगर (!bank)
		वापस -ENOMEM;

	irqc = devm_kzalloc(dev, माप(*irqc), GFP_KERNEL);
	अगर (!irqc)
		वापस -ENOMEM;

	irqc->irq_startup = omap_gpio_irq_startup,
	irqc->irq_shutकरोwn = omap_gpio_irq_shutकरोwn,
	irqc->irq_ack = dummy_irq_chip.irq_ack,
	irqc->irq_mask = omap_gpio_mask_irq,
	irqc->irq_unmask = omap_gpio_unmask_irq,
	irqc->irq_set_type = omap_gpio_irq_type,
	irqc->irq_set_wake = omap_gpio_wake_enable,
	irqc->irq_bus_lock = omap_gpio_irq_bus_lock,
	irqc->irq_bus_sync_unlock = gpio_irq_bus_sync_unlock,
	irqc->name = dev_name(&pdev->dev);
	irqc->flags = IRQCHIP_MASK_ON_SUSPEND;
	irqc->parent_device = dev;

	bank->irq = platक्रमm_get_irq(pdev, 0);
	अगर (bank->irq <= 0) अणु
		अगर (!bank->irq)
			bank->irq = -ENXIO;
		वापस dev_err_probe(dev, bank->irq, "can't get irq resource\n");
	पूर्ण

	bank->chip.parent = dev;
	bank->chip.owner = THIS_MODULE;
	bank->dbck_flag = pdata->dbck_flag;
	bank->stride = pdata->bank_stride;
	bank->width = pdata->bank_width;
	bank->is_mpuio = pdata->is_mpuio;
	bank->non_wakeup_gpios = pdata->non_wakeup_gpios;
	bank->regs = pdata->regs;
#अगर_घोषित CONFIG_OF_GPIO
	bank->chip.of_node = of_node_get(node);
#पूर्ण_अगर

	अगर (node) अणु
		अगर (!of_property_पढ़ो_bool(node, "ti,gpio-always-on"))
			bank->loses_context = true;
	पूर्ण अन्यथा अणु
		bank->loses_context = pdata->loses_context;

		अगर (bank->loses_context)
			bank->get_context_loss_count =
				pdata->get_context_loss_count;
	पूर्ण

	अगर (bank->regs->set_dataout && bank->regs->clr_dataout)
		bank->set_dataout = omap_set_gpio_dataout_reg;
	अन्यथा
		bank->set_dataout = omap_set_gpio_dataout_mask;

	raw_spin_lock_init(&bank->lock);
	raw_spin_lock_init(&bank->wa_lock);

	/* Static mapping, never released */
	bank->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(bank->base)) अणु
		वापस PTR_ERR(bank->base);
	पूर्ण

	अगर (bank->dbck_flag) अणु
		bank->dbck = devm_clk_get(dev, "dbclk");
		अगर (IS_ERR(bank->dbck)) अणु
			dev_err(dev,
				"Could not get gpio dbck. Disable debounce\n");
			bank->dbck_flag = false;
		पूर्ण अन्यथा अणु
			clk_prepare(bank->dbck);
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, bank);

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	अगर (bank->is_mpuio)
		omap_mpuio_init(bank);

	omap_gpio_mod_init(bank);

	ret = omap_gpio_chip_init(bank, irqc);
	अगर (ret) अणु
		pm_runसमय_put_sync(dev);
		pm_runसमय_disable(dev);
		अगर (bank->dbck_flag)
			clk_unprepare(bank->dbck);
		वापस ret;
	पूर्ण

	omap_gpio_show_rev(bank);

	bank->nb.notअगरier_call = gpio_omap_cpu_notअगरier;
	cpu_pm_रेजिस्टर_notअगरier(&bank->nb);

	pm_runसमय_put(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_bank *bank = platक्रमm_get_drvdata(pdev);

	cpu_pm_unरेजिस्टर_notअगरier(&bank->nb);
	gpiochip_हटाओ(&bank->chip);
	pm_runसमय_disable(&pdev->dev);
	अगर (bank->dbck_flag)
		clk_unprepare(bank->dbck);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_gpio_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_bank *bank = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_gpio_idle(bank, true);
	bank->is_suspended = true;
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_gpio_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_bank *bank = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_gpio_unidle(bank);
	bank->is_suspended = false;
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_bank *bank = dev_get_drvdata(dev);

	अगर (bank->is_suspended)
		वापस 0;

	bank->needs_resume = 1;

	वापस omap_gpio_runसमय_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused omap_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_bank *bank = dev_get_drvdata(dev);

	अगर (!bank->needs_resume)
		वापस 0;

	bank->needs_resume = 0;

	वापस omap_gpio_runसमय_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gpio_pm_ops = अणु
	SET_RUNTIME_PM_OPS(omap_gpio_runसमय_suspend, omap_gpio_runसमय_resume,
									शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(omap_gpio_suspend, omap_gpio_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver omap_gpio_driver = अणु
	.probe		= omap_gpio_probe,
	.हटाओ		= omap_gpio_हटाओ,
	.driver		= अणु
		.name	= "omap_gpio",
		.pm	= &gpio_pm_ops,
		.of_match_table = omap_gpio_match,
	पूर्ण,
पूर्ण;

/*
 * gpio driver रेजिस्टर needs to be करोne beक्रमe
 * machine_init functions access gpio APIs.
 * Hence omap_gpio_drv_reg() is a postcore_initcall.
 */
अटल पूर्णांक __init omap_gpio_drv_reg(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_gpio_driver);
पूर्ण
postcore_initcall(omap_gpio_drv_reg);

अटल व्योम __निकास omap_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_gpio_driver);
पूर्ण
module_निकास(omap_gpio_निकास);

MODULE_DESCRIPTION("omap gpio driver");
MODULE_ALIAS("platform:gpio-omap");
MODULE_LICENSE("GPL v2");
